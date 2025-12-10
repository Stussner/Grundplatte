#include <_ton.hpp>

// -------------------------------------------------------------------------------------------------
//
//  Interface for Samples
//
// -------------------------------------------------------------------------------------------------
 


bool I_Sample::Load(std::vector<bcUInt8> &buffer) {
                                                                return(true);
};

void I_Sample::Stop() {
};



// -------------------------------------------------------------------------------------------------
//
//  Stream Interface for Streams
//
// -------------------------------------------------------------------------------------------------
bool I_Stream::IsPlaying() const {
                                                                return(true);
};
bool I_Stream::IsPaused() const {
                                                                return(true);
};
bool I_Stream::Loop() const {
                                                                return(true);
};
 void I_Stream::Loop(bool loop) {
};
 _tg I_Stream::Gain() const {
                                                                return(0);
};
 void I_Stream::Gain(_tg gain) {
};
 _tg I_Stream::Pitch() const {
                                                                return(0);
};
 void I_Stream::Pitch(_tg pitch) {
};
bool I_Stream::Load(std::vector<bcUInt8> &buffer) {
                                                                return(true);
};
// -------------------------------------------------------------------------------------------------
//
//  I_SoundPool
//
// -------------------------------------------------------------------------------------------------
bcUInt32 I_SoundPool::NumSources() const {
                                                                return(0);
};
I_SoundSource *I_SoundPool::FreeSource() {
                                                                return(0);
};
bcUInt32 I_SoundPool::SourcesWithSample(I_Sample *sample, I_SoundSource *sources[], bcUInt32 num) {
                                                                return(0);
};
void I_SoundPool::Pause(_tg fadeTime){
};
void I_SoundPool::Resume(_tg fadeTime){
};
void I_SoundPool::Stop(_tg fadeTime){
};
// -------------------------------------------------------------------------------------------------
//
//  Sound-Interface
//
// -------------------------------------------------------------------------------------------------
bool I_Sound::Init() {
                                                                return(0);
};
I_SoundPool *I_Sound::CreateSoundPool(bcUInt32 numSources) {
                                                                return(0);
};
I_Sample *I_Sound::CreateSample() {
                                                                return(0);
};
I_Stream *I_Sound::CreateStream() {
                                                                return(0);
};
_tg I_Sound::SampleGain() const {
                                                                return(0);
};
void I_Sound::SampleGain(_tg gain) {
};
_tg I_Sound::SamplePitch() const {
                                                                return(0);
};
void I_Sound::SamplePitch(_tg pitch) {
};
_tg I_Sound::StreamGain() const {
                                                                return(0);
};
void I_Sound::StreamGain(_tg gain) {
};
_tg I_Sound::StreamPitch() const {
                                                                return(0);
};
void I_Sound::StreamPitch(_tg pitch) {
};
_vektor3<> I_Sound::ListenerPosition() const {
                                                                return(_vektor3<>(0,0,0));
};
void I_Sound::ListenerPosition(_vektor3<> const &pos) {
};
_vektor3<> I_Sound::ListenerVelocity() const {
                                                                return(_vektor3<>(0,0,0));
};
void I_Sound::ListenerVelocity(_vektor3<> const &vel) {
};
void I_Sound::ListenerOrientation(_vektor3<> const &dir, _vektor3<> const &up) {
};
// Streams
void I_Sound::PlayStream(I_Stream *stream, _tg fadeTime) {
};
void I_Sound::PauseStream(I_Stream *stream, _tg fadeTime) {
};
void I_Sound::ResumeStream(I_Stream *stream, _tg fadeTime) {
};
void I_Sound::StopStream(I_Stream *stream, _tg fadeTime) {
};
void I_Sound::Pause(_tg fadeTime) {
};
void I_Sound::Resume(_tg fadeTime) {
};
void I_Sound::Stop(_tg fadeTime) {
};

void I_Sound::Update(_tg seconds) {
};
// -------------------------------------------------------------------------------------------------
//
//  Interface for SoundSources
//
// -------------------------------------------------------------------------------------------------
bool I_SoundSource::Pause() const {
                                                                return(true);
};
void I_SoundSource::Pause(bool pause) {
};

bool I_SoundSource::Loop() const {
                                                                return(true);
};
void I_SoundSource::Loop(bool loop) {
};
_tg I_SoundSource::Gain() const {
                                                                return(0);
};
void I_SoundSource::Gain(_tg gain) {
};
_tg I_SoundSource::Pitch() const {
                                                                return(0);
};
void I_SoundSource::Pitch(_tg pitch) {
};

void I_SoundSource::Position(_tg x, _tg y, _tg z) {
};
void I_SoundSource::Velocity(_tg x, _tg y, _tg z) {
};

void I_SoundSource::DistanceAttenuation(bool bAttenuation) {
};
void I_SoundSource::ReferenceDistance(_tg dist) {
};
void I_SoundSource::MaxDistance(_tg dist) {
};

void I_SoundSource::Play(I_Sample *sample) {
};
void I_SoundSource::Stop() {
};


//******************************************************************************************************************************************************************************************************
//                                                                  T O N V E R W A L T U N G
//******************************************************************************************************************************************************************************************************
_tonverwaltung::_tonverwaltung(_akustik*s){
                                pakustik=s;
                                ptonsammlung=pakustik->erzeugentonsammlung(128);
                                unsigned int i;
                                for(i=0;i<128;i++) pton[i]=0;
                                for(i=0;i<16;i++) ptonfluss[i]=0;
};
_tonverwaltung::~_tonverwaltung(){
                                unsigned int i;
                                for(i=0;i<128;i++) deletesecure(pton[i]);
                                for(i=0;i<16;i++) deletesecure(ptonfluss[i]);
                                deletesecure(ptonsammlung);
                                
};
_akustik*_tonverwaltung::akustik(){
                                return(pakustik);
};
void _tonverwaltung::erzeugenton(const unsigned int i,const _zeichenkette<char>&s){
                                std::vector<unsigned char> buffer;                          
                                pton[i]=pakustik->erzeugenton();
                                if(pton[i]==0) {
                                 L->schreiben("_tonverwaltung : erzeugenton() fehlgeschlagen.");
                                 throw("_tonverwaltung : erzeugenton() fehlgeschlagen.");
                                };
                                _datei file(s.daten());
                                file.oeffnennurlesen();
                                file.laden(buffer,file.groesse());
                                pton[i]->laden(buffer);
                                file.schliessen();
                                
                                
};
void _tonverwaltung::erzeugentonfluss(const unsigned int i,const _zeichenkette<char>&s){
                                std::vector<unsigned char> buffer;            
                                ptonfluss[i]=pakustik->erzeugentonfluss();
                                if(ptonfluss[i]==0){
                                 L->schreiben("_tonverwaltung : erzeugentonfluss() fehlgeschlagen.");
                                 throw("_tonverwaltung : erzeugentonfluss() fehlgeschlagen.");
                                };
                                _datei file(s.daten());
                                file.oeffnennurlesen();
                                file.laden(buffer,file.groesse());
                                ptonfluss[i]->laden(buffer);
                                file.schliessen();
};
_ton* _tonverwaltung::ton(const unsigned int i){
                                return(pton[i]);
};
_tonfluss* _tonverwaltung::tonfluss(const unsigned int i){
                                return(ptonfluss[i]);
};
_tonsammlung* _tonverwaltung::tonsammlung(){
                                return(ptonsammlung);
};