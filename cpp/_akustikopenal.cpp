
//******************************************************************************************************************************************************************************************************
//  Projekt     : grundplatte
//  Bibliothek  : _grundplatte.lib
//  Modul       : _akustikopenal.cpp
//  Datum       : 6.9.2008
//******************************************************************************************************************************************************************************************************
#include <_akustikopenal.hpp>

/*


#ifdef _DEBUG

   #pragma message("Linking with 'Ogg_Static_d.lib'...")
   #pragma comment(lib4, "Ogg_Static_d.lib")
   
   #pragma message("Linking with 'Vorbis_Static_d.lib'...")
   #pragma comment(lib, "Vorbis_Static_d.lib")
   
   #pragma message("Linking with 'VorbisFile_Static_d.lib'...")
   #pragma comment(lib, "VorbisFile_Static_d.lib")
   
#else

   #pragma message("Linking with 'Ogg_Static_r.lib'...")
   #pragma comment(lib, "Ogg_Static_r.lib")
   
   #pragma message("Linking with 'Vorbis_Static_r.lib'...")
   #pragma comment(lib, "Vorbis_Static_r.lib")
   
   #pragma message("Linking with 'VorbisFile_Static_r.lib'...")
   #pragma comment(lib, "VorbisFile_Static_r.lib")
   
#endif
*/
//******************************************************************************************************************************************************************************************************
//                                                              D A T E I O G G V O R B I S (Hilfsfunktionen)
//******************************************************************************************************************************************************************************************************
static int VorbisSeek(void *datasource, ogg_int64_t offset, int whence){
                                                                size_t				spaceToEOF;		// How much more we can read till we hit the EOF marker
                                                                ogg_int64_t	actualOffset;	// How much we can actually offset it by
                                                                _strukturoggvorbis*vorbisData;		// The data we passed in (for the typecast)
                                                            	// Get the data in the right format
	                                                            vorbisData = static_cast<_strukturoggvorbis*>(datasource);
                                                            	// Goto where we wish to seek to
	                                                            switch(whence){
	                                                             case SEEK_SET: // Seek to the start of the data file
		                                                          // Make sure we are not going to the end of the file
		                                                          if(vorbisData->dataSize >= offset) actualOffset = offset; else actualOffset = vorbisData->dataSize;
		                                                          // Set where we are now
		                                                          vorbisData->dataRead = static_cast<size_t>(actualOffset);
		                                                          break;
                                                        	     case SEEK_CUR: // Seek from where we are
		                                                          // Make sure we dont go past the end
		                                                          spaceToEOF = vorbisData->dataSize - vorbisData->dataRead;
		                                                          if(offset < spaceToEOF) actualOffset = (offset); else actualOffset = spaceToEOF;	
		                                                          // Seek from our currrent location
		                                                          vorbisData->dataRead += static_cast<size_t>(actualOffset);
		                                                          break;
                                                        	     case SEEK_END: // Seek from the end of the file
		                                                          vorbisData->dataRead = vorbisData->dataSize + 1;
		                                                          break;
	                                                            };
                                                            	return(0);
};
static long VorbisTell(void *datasource){
                                                                return((long)static_cast<_strukturoggvorbis*>(datasource)->dataRead);
};
static size_t VorbisRead(void *ptr, size_t byteSize, size_t sizeToRead, void *datasource){ 
                                                                size_t  actualRead, sizeToEOF;
                                                                sizeToEOF = static_cast<_strukturoggvorbis*>(datasource)->dataSize - static_cast<_strukturoggvorbis*>(datasource)->dataRead;
                                                                if((sizeToRead * byteSize) < sizeToEOF) actualRead = sizeToRead * byteSize; else actualRead = sizeToEOF;
                                                                // A simple copy of the data from memory to the datastruct that the vorbis libs will use
	                                                            if(actualRead){
		                                                         // Copy the data from the start of the file PLUS how much we have already read in
		                                                         memcpy(ptr, static_cast<_strukturoggvorbis*>(datasource)->dataPtr + static_cast<_strukturoggvorbis*>(datasource)->dataRead, actualRead);
		                                                         static_cast<_strukturoggvorbis*>(datasource)->dataRead += actualRead;
	                                                            };
                                                                return(actualRead);
};
static int VorbisClose(void *datasource){
                                                                return(1);
};
//******************************************************************************************************************************************************************************************************
//                                                              D A T E I O G G V O R B I S 
//******************************************************************************************************************************************************************************************************
_dateioggvorbis::_dateioggvorbis(){
                                                                panzahlkanal = 0;
                                                                prate = 0;
                                                                memset(&pdatei, 0, sizeof(pdatei));
}
_dateioggvorbis::~_dateioggvorbis(){
                                                                ov_clear(&pdatei);
}
unsigned int _dateioggvorbis::anzahlkanal(){
                                                                return(panzahlkanal);
};
unsigned int _dateioggvorbis::rate(){
                                                                return(prate);
};
bool _dateioggvorbis::laden(std::vector<unsigned char>&buffer){
                                                                ov_callbacks callbacks;
                                                                vorbis_info*vorbisInfo;
   
                                                                pdaten=buffer;
                                                                pstruktur.dataPtr=reinterpret_cast<char *>(&pdaten[0]);
                                                                pstruktur.dataSize = pdaten.size();
                                                                pstruktur.dataRead = 0;
   
                                                                callbacks.seek_func=VorbisSeek;
                                                                callbacks.tell_func=VorbisTell;
                                                                callbacks.read_func=VorbisRead;
                                                                callbacks.close_func=VorbisClose;
                                                                ov_open_callbacks(&pstruktur,&pdatei,0,0,callbacks);
                                                                if(!(vorbisInfo=ov_info(&pdatei,-1))) return(false);
                                                                panzahlkanal=vorbisInfo->channels;
                                                                prate=vorbisInfo->rate;
                                                                return(true);
};
bool _dateioggvorbis::decodieren(std::vector<unsigned char>&buffer,int size){
                                                                //  -1 = read whole file
                                                                //  return value: true = Noch Daten vorhanden, false = Wir sind schon am Ende
                                                                if(size==0)return(false);
                                                                int  bytes;
                                                                unsigned char array[4096];  // Local fixed size array
                                                                int bitStream;
                                                                int endian=!IsLittleEndian();  // 0 for Little-Endian, 1 for Big-Endian
                                                                // ----------------------------------------------------
                                                                buffer.clear();
                                                                if(size==-1){  // -1 = read whole file
                                                                 do{
                                                                  // Read up to a buffer's worth of decoded sound data
                                                                  bytes = ov_read(&pdatei, reinterpret_cast<char *>(array), 4096, endian, 2, 1, &bitStream);
                                                                  if(bytes < 0) throw L"_dateioggvorbis::decodieren():Fehler";
                                                                  // Append to end of buffer
                                                                  buffer.insert(buffer.end(), array, array + bytes);
                                                                 }while(bytes>0);
                                                                 return(false);
                                                                }else{//read a part of file
                                                                 do{
                                                                  // Read up to a buffer's worth of decoded sound data
                                                                  if(size > 4096)
                                                                   bytes = ov_read(&pdatei, reinterpret_cast<char *>(array), 4096, endian, 2, 1, &bitStream);
                                                                  else
                                                                   bytes = ov_read(&pdatei, reinterpret_cast<char *>(array), size, endian, 2, 1, &bitStream);
                                                                  if(bytes < 0) throw L"_dateioggvorbis::decodieren():Fehler";
                                                                  // Append to end of buffer
                                                                  buffer.insert(buffer.end(), array, array + bytes);
                                                                  size -= bytes;
                                                                 }while((bytes>0)&&(size>0));
                                                                 if(0 == bytes){  // Stream wieder von vorne beginnen lassen
                                                                  ov_raw_seek(&pdatei, 0);
                                                                  return(false);
                                                                 };
                                                                };
                                                                return(true);
}
//******************************************************************************************************************************************************************************************************
//                                                                  A K U S T I K O P E N A L 
//******************************************************************************************************************************************************************************************************
_akustikopenal::_akustikopenal(){
                                                                ALCdevice*device;
                                                                ALCcontext*context;
                                                                // --------------------
                                                                alListenerf(AL_GAIN, 1.0f);

                                                                // Init Device
                                                                if(!(device=alcOpenDevice("DirectSound"))) { // 0, DirectSound, DirectSound3D
                                                                };
                                                                // Create Context
                                                                if(!(context=alcCreateContext(device,0))){
                                                                };
                                                                alcMakeContextCurrent(context);
                                                                // Set default values for the Listener (Camera-Position for example)
                                                                zuhoererort(_vektor3<_tg>(0,0,0));
                                                                zuhoerergeschwindigkeit(_vektor3<_tg>(0,0,0));
                                                                zuhoererrichtung(_vektor3<_tg>(0,0,1),_vektor3<_tg>(0,1,0));                                                                
                                                                
};
_akustikopenal::~_akustikopenal(){
                                                                ALCdevice*device;
                                                                ALCcontext*context;
                                                                // -------------------
                                                                // Close Device
																loeschentonlisten();
                                                                context=alcGetCurrentContext();
                                                                device=alcGetContextsDevice(context);
                                                                alcMakeContextCurrent(0);
                                                                alcDestroyContext(context);
                                                                alcCloseDevice(device);
};
void _akustikopenal::animieren(_tg seconds){
                                                                _tonsammlung*sit;
                                                                _tonfluss*fit;
                                                                //---------------------
                                                                // animieren Sammlungen
                                                                if(listetonsammlung()->anfang(sit))do{
                                                                 sit->animieren(seconds);
                                                                }while(listetonsammlung()->naechstes(sit));
                                                                // animieren Fluesse
                                                                if(listetonfluss()->anfang(fit))do{
                                                                 fit->animieren(seconds);
                                                                }while(listetonfluss()->naechstes(fit));
                                                                // Fehlerprüfung
                                                                if(alGetError()) throw L"_akustikopenal::animieren(_tg seconds):Fehler";
};
void _akustikopenal::stoppenquellemitbuffer(const unsigned int buffer){
                                                                _tonsammlung*sit;
                                                                if(listetonsammlung()->anfang(sit))do{
                                                                 sit->stoppenquellemitbuffer(buffer);
                                                                }while(listetonsammlung()->naechstes(sit));
};

_tonsammlung*_akustikopenal::erzeugentonsammlung(const unsigned int numSources){
                                                                return(new _tonsammlungopenal(this,32));
};

//--------------------------------------------------------------ton parameter--------------------------------------------------------------------------------------------------------

void _akustikopenal::zuhoererort(const _vektor3<_tg>&pos){
                                                                alListener3f(AL_POSITION,(ALfloat)pos[0],(ALfloat)pos[1],(ALfloat)-pos[2]);
};
void _akustikopenal::zuhoerergeschwindigkeit(const _vektor3<_tg>&vel){
                                                                alListener3f(AL_VELOCITY,(ALfloat)vel[0],(ALfloat)vel[1],(ALfloat)-vel[2]);
};
void _akustikopenal::zuhoererrichtung(const _vektor3<_tg>&dir, const _vektor3<_tg>&up){
                                                                ALfloat orientation[]={(ALfloat)dir[0],(ALfloat)dir[1],(ALfloat)-dir[2],(ALfloat)up[0],(ALfloat)up[1],(ALfloat)-up[2]};
                                                                alListenerfv(AL_ORIENTATION,orientation);
};

//--------------------------------------------------------------ton------------------------------------------------------------------------------------------------------------------
_ton*_akustikopenal::erzeugenton(){
                                                                return(new _tonopenal(this));
};
void _akustikopenal::abspielen(_ton*sample){
                                                                _vektor3<_tg> pos;
                                                                _vektor3<_tg> vel;
                                                                // ----------------------------------------------------------------------------
                                                                unsigned int source=tonsammlung(0)->findenfreiequelle();
                                                                if(source){
                                                                 ALfloat position[] = {(ALfloat)pos[0],(ALfloat)pos[1],(ALfloat)-pos[2]};
                                                                 ALfloat velocity[] = {(ALfloat)vel[0],(ALfloat)vel[1],(ALfloat)-vel[2]};
                                                                 alSourcei(source,AL_BUFFER,(ALint)sample->identifikationbuffer());
                                                                 alSourcef(source,AL_GAIN,(ALfloat)(lautstaerketon()*sample->lautstaerke()));
                                                                 alSourcef(source,AL_PITCH,(ALfloat)(beugung()*sample->beugung()));
                                                                 alSourcei(source,AL_LOOPING,(ALint)sample->schleife());
                                                                 alSourcefv(source,AL_POSITION,position);
                                                                 alSourcefv(source,AL_VELOCITY,velocity);
                                                                 alSourcePlay(source);
                                                                };
};
void _akustikopenal::abspielen(_ton*sample,_tg l,_tg b0,_tg b1){
                                                                _vektor3<_tg> pos;
                                                                _vektor3<_tg> vel;
                                                                // ----------------------------------------------------------------------------
                                                                unsigned int source=tonsammlung(0)->findenfreiequelle();
                                                                if(source){
                                                                 ALfloat position[] = {(ALfloat)pos[0],(ALfloat)pos[1],(ALfloat)-pos[2]};
                                                                 ALfloat velocity[] = {(ALfloat)vel[0],(ALfloat)vel[1],(ALfloat)-vel[2]};
                                                                 alSourcei(source,AL_BUFFER,(ALint)sample->identifikationbuffer());
                                                                 alSourcef(source,AL_GAIN,(ALfloat)(lautstaerketon()*l));
                                                                 alSourcef(source,AL_PITCH,(ALfloat)(beugung()/* *zufall<_tg>(b0,b1)*/));
                                                                 alSourcei(source,AL_LOOPING,(ALint)sample->schleife());
                                                                 alSourcefv(source,AL_POSITION,position);
                                                                 alSourcefv(source,AL_VELOCITY,velocity);
                                                                 alSourcePlay(source);
                                                                };
};
void _akustikopenal::abspielen(unsigned int pool,_ton*sample,const _vektor3<_tg>&pos,const _vektor3<_tg>&vel,_tg fadeTime){
                                                                unsigned int source=tonsammlung(pool)->findenfreiequelle();
                                                                // ----------------------------------------------------------------------------
                                                                if(source){
                                                                 ALfloat position[] = {(ALfloat)pos[0],(ALfloat)pos[1],(ALfloat)-pos[2]};
                                                                 ALfloat velocity[] = {(ALfloat)vel[0],(ALfloat)vel[1],(ALfloat)-vel[2]};
                                                                 alSourcei(source,AL_BUFFER,(ALint)sample->identifikationbuffer());
                                                                 alSourcef(source,AL_GAIN,(ALfloat)(lautstaerketon()*sample->lautstaerke()));
                                                                 alSourcef(source,AL_PITCH,(ALfloat)(beugung()*sample->beugung()));
                                                                 alSourcei(source,AL_LOOPING,(ALint)sample->schleife());
                                                                 alSourcefv(source,AL_POSITION,position);
                                                                 alSourcefv(source,AL_VELOCITY,velocity);
                                                                 alSourcePlay(source);
                                                                };
};
void _akustikopenal::anhalten(unsigned int pool,_ton*,_tg fadeTime){
};
void _akustikopenal::stoppen(unsigned int pool,_ton*,_tg fadeTime){
};
//--------------------------------------------------------------Streams--------------------------------------------------------------------------------------------------------------
_tonfluss*_akustikopenal::erzeugentonfluss(){
                                                            
                                                                return(new _tonflussopenal(this));
};
void _akustikopenal::abspielen(_tonfluss*stream,_tg fadeTime){
                                                                //_tonflussopenal*alstream=static_cast<C_StreamOpenAL *>(stream);
                                                                if(stream->angehalten()) {
                                                                 alSourcePlay(stream->identifikationquelle());
                                                                 return;
                                                                };
                                                                if(stream->spielt()) return;
                                                                stream->aktiv(true);//m_bActive = true;
                                                                // Alle Buffer einhängen
                                                                for(unsigned int i=0;i<NUM_STREAMBUFFERS;i++) stream->fuellenbuffer(stream->identifikationstream(i));
                                                                alSourcePlay(stream->identifikationquelle());
};
void _akustikopenal::anhalten(_tonfluss*stream,_tg fadeTime){
                                                                alSourcePause(stream->identifikationquelle());
};
void _akustikopenal::stoppen(_tonfluss*stream,_tg fadeTime){
                                                                ALint  queued;
                                                                alSourceStop(stream->identifikationquelle());
                                                                alGetSourcei(stream->identifikationquelle(),AL_BUFFERS_QUEUED,&queued);
                                                                while(queued--){
                                                                 ALuint buffer;
                                                                 alSourceUnqueueBuffers(stream->identifikationquelle(),1,&buffer);
                                                                };

};

//******************************************************************************************************************************************************************************************************
//                                                              T O N O P E N A L 
//******************************************************************************************************************************************************************************************************
_tonopenal::_tonopenal(_akustik*a):_ton(a){
                                                                unsigned int m;
                                                                alGenBuffers(1, &m);
                                                                identifikationbuffer(m);
};
_tonopenal::~_tonopenal(){
                                                                unsigned int m=identifikationbuffer();
                                                                akustik()->stoppenquellemitbuffer(m);
                                                                alDeleteBuffers(1, &m);
                                                               // identifikationbuffer(m);
};
#include <_datei.hpp>
bool _tonopenal::laden(std::vector<unsigned char> &buffer){
                                                                std::vector<unsigned char>  data;
                                                                _dateioggvorbis file;
                                                                //------------------
                                                                if(!file.laden(buffer)) {
                                                                 L->schreiben("_tonopenal::laden : Fehler beim laden des Buffers.");
                                                                 return(false);
                                                                }else{
                                                                 L->schreiben("_tonopenal::laden : erfolgreich.");
                                                                };
                                                                
                                                                file.decodieren(data,-1);  // -1 = read whole file
                                                                alBufferData(identifikationbuffer(),1==file.anzahlkanal()?AL_FORMAT_MONO16:AL_FORMAT_STEREO16,&data[0], static_cast<ALsizei>(data.size()), file.rate());
   
                                                                return(true);
};
//******************************************************************************************************************************************************************************************************
//                                                              T O N F L U S S O P E N A L 
//******************************************************************************************************************************************************************************************************
_tonflussopenal::_tonflussopenal(_akustik*a):_tonfluss(a){
                                                                paktiv=false;
                                                                pschleife=false;
                                                                pausblendenanhalten=false;
                                                                pausblendenstoppen=false;
                                                                unsigned int t;
                                                                alGenSources(1, &t);
                                                                identifikationquelle(t);
                                                                alGenBuffers(NUM_STREAMBUFFERS, pidentifikationbuffer);
                                                                // Set default values for source
                                                                ALfloat SourcePos[]={0.0,0.0,0.0};
                                                                ALfloat SourceVel[]={0.0,0.0,0.0};
                                                                alSourcef (identifikationquelle(),AL_PITCH,   1.0f     );
                                                                alSourcef (identifikationquelle(),AL_GAIN,    0.5f     );
                                                                alSourcefv(identifikationquelle(),AL_POSITION,SourcePos);
                                                                alSourcefv(identifikationquelle(),AL_VELOCITY,SourceVel);
                                                                alSourcei (identifikationquelle(),AL_LOOPING, AL_FALSE ); 
};
_tonflussopenal::~_tonflussopenal(){
                                                                alSourceStop(identifikationquelle());
                                                                ALint queued;
                                                                alGetSourcei(identifikationquelle(),AL_BUFFERS_QUEUED,&queued);
                                                                while(queued--){
                                                                 ALuint buffer;
                                                                 alSourceUnqueueBuffers(identifikationquelle(),1,&buffer);
                                                                };
                                                                unsigned int t=identifikationquelle();
                                                                alDeleteSources(1,&t);
                                                                identifikationquelle(t);
                                                                alDeleteBuffers(NUM_STREAMBUFFERS,pidentifikationbuffer);
};
unsigned int _tonflussopenal::identifikationquelle()const{
                                                                return(pidentifikationquelle);
};
void _tonflussopenal::identifikationquelle(const unsigned int q){
                                                                pidentifikationquelle=q;
};
unsigned int _tonflussopenal::identifikationstream(const unsigned int i)const{
                                                                return(pidentifikationbuffer[i]);
};
bool _tonflussopenal::laden(std::vector<unsigned char>&buffer){
                                                                return(_dateioggvorbis::laden(buffer));
};
void _tonflussopenal::animieren(_tg seconds){
                                                                if(!paktiv)return;
                                                                ALuint bufferid;
                                                                ALint processed;
                                                                bool bNeedRestart=false;
                                                                alGetSourcei(identifikationquelle(),AL_BUFFERS_PROCESSED,&processed);
                                                                if(NUM_STREAMBUFFERS==processed) bNeedRestart=true; // Any error, we must restart...
                                                                while(processed--){
                                                                 alSourceUnqueueBuffers(identifikationquelle(),1,&bufferid);
                                                                 fuellenbuffer(bufferid);
                                                                };
                                                                if(bNeedRestart) alSourcePlay(identifikationquelle());
};
bool _tonflussopenal::spielt()const{
                                                                ALint state;
                                                                alGetSourcei(identifikationquelle(),AL_SOURCE_STATE,&state);
                                                                return(AL_PLAYING==state);
};
bool _tonflussopenal::angehalten()const{
                                                                ALint state;
                                                                alGetSourcei(identifikationquelle(),AL_SOURCE_STATE,&state);
                                                                return(AL_PAUSED==state);
};                
void _tonflussopenal::aktiv(const bool b){
                                                                paktiv=b;
};
bool _tonflussopenal::aktiv() const{
                                                                return(paktiv);
};
void _tonflussopenal::schleife(const bool b){
                                                                pschleife=b;
};
bool _tonflussopenal::schleife() const{
                                                                return(pschleife);
};
void _tonflussopenal::fuellenbuffer(unsigned int id){
                                                                std::vector<unsigned char> buffer;
                                                                // Decode next chunk from Ogg-File
                                                                if(!decodieren(buffer, SIZE_STREAMBUFFER)){
                                                                 if(!pschleife){
                                                                  paktiv=false;
                                                                 }else{
                                                                  while(!decodieren(buffer,SIZE_STREAMBUFFER-static_cast<int>(buffer.size())));
                                                                 };
                                                                };
                                                                if(buffer.size()){
                                                                 alBufferData(id,1==anzahlkanal()?AL_FORMAT_MONO16:AL_FORMAT_STEREO16,&buffer[0],static_cast<ALsizei>(buffer.size()),rate());
                                                                 alSourceQueueBuffers(identifikationquelle(),1,&id);
                                                                };
};
//******************************************************************************************************************************************************************************************************
//                                                              T O N S A M M L U N G O P E N A L 
//******************************************************************************************************************************************************************************************************
_tonsammlungopenal::_tonsammlungopenal(_akustik*a,unsigned int numSources):_tonsammlung(a,numSources){
                                                                //m_RefCount = 1;



                        

                                                                // Create all Sources
                                                                alGenSources(anzahlquelle(), quelle());

                                                                // Set default values for all Sources
                                                                ALfloat  SourcePos[] = { 0.0, 0.0, 0.0 };
                                                                ALfloat  SourceVel[] = { 0.0, 0.0, 0.0 };

                                                                for(unsigned int i=0;i<anzahlquelle();i++){
                                                                 alSourcef (quelle(i),AL_GAIN,1.0f);  // Volume (0-1)
                                                                 alSourcef (quelle(i),AL_PITCH,1.0f);  // Speed (0.5 = half)
                                                                 alSourcefv(quelle(i),AL_POSITION,SourcePos);
                                                                 alSourcefv(quelle(i),AL_VELOCITY,SourceVel);
                                                                 alSourcef (quelle(i),AL_REFERENCE_DISTANCE, 4);
                                                                 alSourcei (quelle(i),AL_LOOPING,AL_FALSE );
                                                                };

};
_tonsammlungopenal::~_tonsammlungopenal(){
                                                                // Stop all Sources
                                                                for(unsigned int i=0;i<anzahlquelle();i++) alSourceStop(quelle(i));
                                                                // Free all Sources
                                                                alDeleteSources(anzahlquelle(), quelle());
};
void _tonsammlungopenal::anhalten(_tg fadeTime){
                                                                if(0==fadeTime){
                                                                 int  state;
                                                                 for(unsigned int i=0;i<anzahlquelle();i++){
                                                                  alGetSourcei(quelle(i), AL_SOURCE_STATE, &state);
                                                                  if(AL_PLAYING==state) alSourcePause(quelle(i));
                                                                 };
                                                                 ausblendenanhalten(false);
                                                                }else{
                                                                 interpolator()->setzen(1, 0, fadeTime);
                                                                 ausblendenanhalten(true);
                                                                };
                                                                ausblendenstoppen(false);
};
void _tonsammlungopenal::fortsetzen(_tg fadeTime){
                                                                int  state;
                                                                for(unsigned int i=0;i<anzahlquelle();i++){
                                                                 alGetSourcei(quelle(i), AL_SOURCE_STATE, &state);
                                                                 if(AL_PAUSED==state) alSourcePlay(quelle(i));
                                                                };
};
void _tonsammlungopenal::stoppen(_tg fadeTime){
                                                                if(0==fadeTime){
                                                                 int  state;
                                                                 for(unsigned int i=0;i<anzahlquelle();i++){
                                                                  alGetSourcei(quelle(i), AL_SOURCE_STATE, &state);
                                                                  if(AL_PLAYING == state)
                                                                  alSourceStop(quelle(i));
                                                                 };
                                                                 ausblendenstoppen(false);
                                                                }else{
                                                                 interpolator()->setzen(1,0,fadeTime);
                                                                 ausblendenstoppen(true);
                                                                };
                                                                ausblendenanhalten(false);
};
unsigned int _tonsammlungopenal::findenfreiequelle(){
                                                                int state;
                                                                for(unsigned int i=0;i<anzahlquelle();i++){
                                                                 alGetSourcei(quelle(i),AL_SOURCE_STATE,&state);
                                                                 if(AL_STOPPED==state||AL_INITIAL==state) return(quelle(i));
                                                                };
                                                                return(0);
};
void _tonsammlungopenal::stoppenquellemitbuffer(unsigned int buffer){
                                                                int state;
                                                                for(unsigned int i=0;i<anzahlquelle();i++){
                                                                 alGetSourcei(quelle(i),AL_BUFFER,&state);
                                                                 if(state==buffer) alSourceStop(quelle(i));
                                                                };
};

void _tonsammlungopenal::lautstaerkespielendequelle(_tg value){
                                                                int state;
                                                                for(unsigned int i=0;i<anzahlquelle();i++) {
                                                                 alGetSourcei(quelle(i),AL_SOURCE_STATE,&state);
                                                                 if(AL_PLAYING==state) alSourcef(quelle(i),AL_GAIN,ALfloat(value));
                                                                };
};
void _tonsammlungopenal::animieren(_tg seconds){
                                                                // Fade and pause...
                                                                if(ausblendenanhalten()){
                                                                 int state;
                                                                 _tg frac=interpolator()->berechnen(seconds);
                                                                 if(frac<0.0001){
                                                                  for(unsigned int i=0;i<anzahlquelle(); i++){
                                                                   alGetSourcei(quelle(i),AL_SOURCE_STATE,&state);
                                                                   if(AL_PLAYING==state) alSourcePause(quelle(i));
                                                                  };
                                                                  ausblendenanhalten(false);
                                                                 }else{
                                                                  lautstaerkespielendequelle(frac);
                                                                 };
                                                                };
                                                                // Fade and stop...
                                                                if(ausblendenstoppen()){
                                                                 int state;
                                                                 _tg frac=interpolator()->berechnen(seconds);
                                                                 if(frac<0.0001){
                                                                  for(unsigned int i=0;i<anzahlquelle();i++){
                                                                   alGetSourcei(quelle(i),AL_SOURCE_STATE,&state);
                                                                   if(AL_PLAYING==state) alSourceStop(quelle(i));
                                                                  };
                                                                  ausblendenstoppen(false);
                                                                 }else{
                                                                  lautstaerkespielendequelle(frac);
                                                                 };
                                                                };
};
//******************************************************************************************************************
//										M U S I K E I N T R A G 
//******************************************************************************************************************
_musikeintrag::_musikeintrag(_musikverwaltung*m,const _zeichenkette<char>&datei):_listenknotenbasis<_musikeintrag>(m){
                                pmusikverwaltung=m;
                                pakustik=m->akustik();
                                pdatei=datei;
                                pspieldauer=10000;//!!!!!!
                                ptonfluss=new _tonflussopenal(m->akustik());
                                pausblenden=false;
                                peinblenden=false;
                                pblendwert=0;
                                
};
_musikeintrag::~_musikeintrag(){
                                delete ptonfluss;
};
bool _musikeintrag::laden(){
                                ptonfluss->laden(pdatei.stdvector<unsigned char>());
                                return(true);
};
void _musikeintrag::animieren(){
                                if(pausblenden){
                                 pblendwert-=pmusikverwaltung->blendgeschwindigkeit();
                                 if(pblendwert<0){
                                  pblendwert=0;
                                  ptonfluss->lautstaerke(0);
                                  pakustik->anhalten(ptonfluss);
                                  pausblenden=false;
                                 };
                                };

                                if(peinblenden){
                                 pblendwert+=pmusikverwaltung->blendgeschwindigkeit();
                                 if(pblendwert>1){
                                  pblendwert=1;
                                  peinblenden=false;
                                 };
                                };
                                ptonfluss->lautstaerke(pblendwert*pmusikverwaltung->lautstaerke());
                                
};
void _musikeintrag::einblenden(){
                                peinblenden=true;
                                pausblenden=false;
                                ptonfluss->lautstaerke(pblendwert*pmusikverwaltung->lautstaerke());
                                pakustik->abspielen(ptonfluss);
};
void _musikeintrag::ausblenden(){
                                if(ptonfluss->spielt()==false) return;
                                peinblenden=false;
                                pausblenden=false;
                                if(pblendwert>0) pausblenden=true;
};
//******************************************************************************************************************
//										M U S I K V E R W A L T U N G
//******************************************************************************************************************
_musikverwaltung::_musikverwaltung(_akustik*a,_zeit*z){
                                pzeit=z;
                                pakustik=a;
                                pladeniterator=0;
                                pblendgeschwindigkeit=0.05;
                                plautstaerke=0.5;
                              /*  paktuell=0;
                                pnaechstes=0;
                                starttime=0;
                                status=0;
                                switchindex=-1;
                                spielmode=false;
	                            quellemenuefadeswitch=false;
	                            quellemenuefadedown=false;
	                            quellemenuefadeup=false;
	                            quellespielfadeswitch=false;
	                            quellespielfadedown=false;
	                            quellespielfadeup=false;
	                            menueindex=-1;
	                            spielindex=-1;
	                            menuefade=0;
	                            spielfade=0;
	                            menuefadespeed=0.05;
	                            spielfadespeed=0.05;
	                            quellemenueswitchto=0;
	                            quellespielswitchto=0;
				                quellespiel=0;//Allocquelle()
				                quellemenue=0;//llocquelle()
				                //quellemenue.setvolume(0)
				                //quellespiel.setvolume(0)
				                //quellemenue.setpaused(True)
				                //quellespiel.setpaused(True)
*/
};
_musikverwaltung::~_musikverwaltung(){
};
_akustik*_musikverwaltung::akustik(){
                                return(pakustik);
};
_musikeintrag* _musikverwaltung::erzeugenmusik(const _zeichenkette<char>&datei){
                                _musikeintrag*e=new _musikeintrag(this,datei);
                                anfang(pladeniterator);
                                return(e);
                               
};	
void _musikverwaltung::laden(){
                                _musikeintrag*eit;
                                if(anfang(eit))do{
                                 eit->laden();
                                }while(naechstes(eit));
};
bool _musikverwaltung::ladenschritt(){
                                if(pladeniterator) pladeniterator->laden();
                                pladeniterator=pladeniterator->naechstes();
                                if(pladeniterator==erstes()) pladeniterator=0; 
                                if(pladeniterator==0) return(false);
				                return(true);
};
_tg _musikverwaltung::blendgeschwindigkeit()const{
                                return(pblendgeschwindigkeit);
};
void _musikverwaltung::lautstaerke(const _tg l){
                                plautstaerke=begrenzen<_tg>(l,0,1);
};
_tg _musikverwaltung::lautstaerke()const{
                                return(plautstaerke);
};

void _musikverwaltung::abspielen(int i,bool restart){
                                index(i)->einblenden();
                                /*
                				if(gm){//-----------------------------spiel music control 
				                 if(quellemenue->playing()) quellemenuefadedown=true;
				                 quellemenuefadeup=false;
				                 quellemenuefadeswitch=false;
				                 if(quellespiel->playing()){
				                  quellespielfadeswitch=true;
				                  quellespielswitchto=i;
				                  quellespielfadeup=false;
				                  quellespielfadedown=false;
				                 }else{
				                  quellespielfadeup=true;
				                  quellespielfadedown=false;
				                  quellespielfadeswitch=false;
				                  quellespiel->setvolume(0);
				                  quellespiel->setpaused(false);
				                  aktualisierenspiel(i);
				                 };
            				    }else{//------------------------------menue music control
				                 if(quellespiel->playing()) quellespielfadedown=true;
				                 quellespielfadeup=false;
				                 quellespielfadeswitch=false;
				                 if(quellemenue->playing()){
				                  quellemenuefadeswitch=true;
				                  quellemenueswitchto=i;
				                  quellemenuefadedown=false;
				                  quellemenuefadeup=false;
				                 }else{
				                  quellemenuefadeup=true;
				                  quellemenuefadedown=false;
				                  quellemenuefadeswitch=false;
				                  quellemenue->setvolume(0);
				                  quellemenue->setpaused(false);
				                  aktualisierenmenue(i);
				                 };
				                };*/
};
void _musikverwaltung::ausblenden(){
                                _musikeintrag*eit;
                                if(anfang(eit))do{
                                 eit->ausblenden();
                                }while(naechstes(eit));
                                /*
                                if(quellespiel->playing()) quellespielfadedown=true;
                                quellespielfadeup=false;
                                quellespielfadeswitch=false;
                                if(quellemenue->playing()) quellemenuefadedown=true;
                                quellemenuefadeup=false;
                                quellemenuefadeswitch=false;
                                */
};
void _musikverwaltung::einblenden(int i){
                                ausblenden();
                                _listebasis<_musikeintrag>::index(i)->einblenden();
};

/*
void _musikverwaltung::einblendenmenue(){				
				                quellemenuefadedown=false;
				                quellemenuefadeup=true;
				                quellemenuefadeswitch=false;
				                quellemenue->setpaused(false);
};

void _musikverwaltung::aktualisierenspiel(i){
				                if(spielindex!=i){
				                 spielindex=i;
				                 PlaySound(sound[spielindex],quellespiel);//!!!!!!!!!!!!!!!!!!!!!!!
				                 starttime=pzeit->system();
				                };
};
void _musikverwaltung::aktualisierenmenue(int i){
                                if(menueindex!=i){
                                 menueindex=i;
                                 PlaySound(sound[menueindex],quellemenue);//!!!!!!!!!!!!!!!!!!!!!!!
                                 starttime=pzeit->system();
                                };
};
*/
void _musikverwaltung::animieren(bool paused){
                                _musikeintrag*eit;
                                if(anfang(eit))do{
                                 eit->animieren();
                                }while(naechstes(eit));
                                /*
                                if(quellespielfadeswitch){
                                 spielfade-=spielfadespeed;
                                 if(spielfade<0){
                                  spielfade=0;
                                  quellespiel->setvolume(0);
                                  quellespielfadeswitch=false;
                                  quellespielfadedown=false;
                                  quellespielfadeup=true;
                                  aktualisierenspiel(quellespielswitchto);
                                 };
                                };

                                if(quellespielfadedown){
                                 spielfade-=spielfadespeed;
                                 if(spielfade<0){
                                  spielfade=0;
                                  quellespiel->setvolume(0);
                                  quellespiel->setpaused(true);
                                  quellespielfadedown=false;
                                 };
                                };

                                if(quellespielfadeup){
                                 spielfade+=spielfadespeed;
                                 if(spielfade>1){
                                  spielfade=1;
                                  quellespiel->setvolume(volumemusic);
                                  quellespielfadeup=false;
                                 };
                                };
                                quellespiel->setvolume(spielfade*volumemusic);
                                
                                if(quellemenuefadeswitch){
                                 menuefade-=menuefadespeed;
                                 if(menuefade<0){
                                  menuefade=0;
                                  quellemenue->setvolume(0);
                                  quellemenuefadeswitch=false;
                                  quellemenuefadedown=false;
                                  quellemenuefadeup=true;
                                  aktualisierenmenue(quellemenueswitchto);
                                 };
                                };

                                if(quellemenuefadedown){
                                 menuefade-=menuefadespeed;
                                 if(menuefade<0){
                                  menuefade=0;
                                  quellemenue->setvolume(0);
                                  quellemenue->setpaused(true);
                                  quellemenuefadedown=false;
                                 };
                                };

                                if(quellemenuefadeup){
                                 menuefade+=menuefadespeed;
                                 if(menuefade>1){
                                  menuefade=1;
                                  quellemenue->setvolume(volumemusic);
                                  quellemenuefadeup=false;
                                 };
                                };
                                quellemenue->setvolume(menuefade*volumemusic);
                                */
};


