//******************************************************************************************************************************************************************************************************
//  Project     : grundplatte
//  Library     : _grundplatte.lib
//  Module      : _ton.hpp
//  Date        : 13.6.2003
//  Description : Klangrepräsentation, Klangmodifikation
//******************************************************************************************************************************************************************************************************
#ifndef _tonh_included
#define _tonh_included
#include<_global.hpp>
#include<_funktion.hpp>
#include<_datei.hpp>
#include<_akustik.hpp>
#include<vector>
//#include <BCEngine/Engine.hpp>//für sound
//******************************************************************************************************************************************************************************************************
//                                                              P R E D E K L A R A T I O N 
//******************************************************************************************************************************************************************************************************
class _tonverwaltung;
template<class _tg=typgeometrie,class _ta=typakustik> class _tonschnittstelle;
template<class _tg=typgeometrie>                         class _tontuppel;
template<class _tg=typgeometrie,class _ta=typakustik> class _tonkurvehermite;
template<class _tg=typgeometrie,class _ta=typakustik> class _tonfunktion;
template<class _tg=typgeometrie,class _ta=typakustik> class _tonhuelle;
template<class _tg=typgeometrie,class _ta=typakustik> class _tonbuffer;
template<class _tg=typgeometrie,class _ta=typakustik> class _tonbuffersynthese;
template<class _tg=typgeometrie,class _ta=typakustik> class _tonwelle;
template<class _tg=typgeometrie,class _ta=typakustik> class _tondaten;
template<class _tg=typgeometrie,class _ta=typakustik> class _tondatenwav;
template<class _tg=typgeometrie,class _ta=typakustik> class _soundinversedct;
template<class _tg=typgeometrie,class _ta=typakustik> class _tonkanal;
template<class _tg=typgeometrie,class _ta=typakustik> class _tonton;
template<class _tg=typgeometrie,class _ta=typakustik> class _tonwav;
template<class _tg=typgeometrie,class _ta=typakustik> class _tonmodifikation;
template<class _tg=typgeometrie,class _ta=typakustik> class _tonmodifikationkurve;
template<class _tg=typgeometrie,class _ta=typakustik> class _tonmodifikationbuffer;
template<class _tg=typgeometrie,class _ta=typakustik> class _tonmodifikationbuffernormalisieren;
template<class _tg=typgeometrie,class _ta=typakustik> class _tonmodifikationbufferrauschen;
template<class _tg=typgeometrie,class _ta=typakustik> class _tonmodifikationkanal;
template<class _tg=typgeometrie,class _ta=typakustik> class _tonmodifikationkanalpanorama;









class I_Sample;
class I_Stream ;
class I_SoundPool;
class I_Sound ;
class I_SoundSource;

// -------------------------------------------------------------------------------------------------
//
//  Interface for Samples
//
// -------------------------------------------------------------------------------------------------
class I_Sample {
    public:
                virtual bool Load(std::vector<bcUInt8> &buffer) ;
                virtual void Stop() ;
};


// -------------------------------------------------------------------------------------------------
//
//  Stream Interface for Streams
//
// -------------------------------------------------------------------------------------------------
class I_Stream {
    public:
                virtual bool IsPlaying() const ;
                virtual bool IsPaused() const ;
                virtual bool Loop() const ;
                virtual void Loop(bool loop) ;
                virtual _tg Gain() const ;
                virtual void Gain(_tg gain) ;
                virtual _tg Pitch() const ;
                virtual void Pitch(_tg pitch) ;
                virtual bool Load(std::vector<bcUInt8> &buffer) ;
};

// -------------------------------------------------------------------------------------------------
//
//  I_SoundPool
//
// -------------------------------------------------------------------------------------------------
class I_SoundPool {
   public:
     virtual bcUInt32 NumSources() const ;
     
     virtual I_SoundSource *FreeSource() ;
	   virtual bcUInt32 SourcesWithSample(I_Sample *sample, I_SoundSource *sources[], bcUInt32 num) ;
	   
     virtual void Pause(_tg fadeTime = 0) ;
     virtual void Resume(_tg fadeTime = 0) ;
     virtual void Stop(_tg fadeTime = 0) ;
};

// -------------------------------------------------------------------------------------------------
//
//  Sound-Interface
//
// -------------------------------------------------------------------------------------------------
class I_Sound 
{
   public:
     virtual bool Init() ;
     
     virtual I_SoundPool *CreateSoundPool(bcUInt32 numSources) ;
     virtual I_Sample *CreateSample() ;
     virtual I_Stream *CreateStream() ;
     
     virtual _tg SampleGain() const ;
     virtual void SampleGain(_tg gain) ;
     virtual _tg SamplePitch() const ;
     virtual void SamplePitch(_tg pitch) ;
     
     virtual _tg StreamGain() const ;
     virtual void StreamGain(_tg gain) ;
     virtual _tg StreamPitch() const ;
     virtual void StreamPitch(_tg pitch) ;
     
     virtual _vektor3<> ListenerPosition() const ;
     virtual void ListenerPosition(_vektor3<> const &pos) ;
     virtual _vektor3<> ListenerVelocity() const ;
     virtual void ListenerVelocity(_vektor3<> const &vel) ;
     virtual void ListenerOrientation(_vektor3<> const &dir, _vektor3<> const &up) ;
     
     // Streams
     virtual void PlayStream(I_Stream *stream, _tg fadeTime = 0) ;
     virtual void PauseStream(I_Stream *stream, _tg fadeTime = 0) ;
     virtual void ResumeStream(I_Stream *stream, _tg fadeTime = 0) ;
     virtual void StopStream(I_Stream *stream, _tg fadeTime = 0) ;
     
     virtual void Pause(_tg fadeTime = 0) ;
     virtual void Resume(_tg fadeTime = 0) ;
     virtual void Stop(_tg fadeTime = 0) ;
     
     virtual void Update(_tg seconds) ;
};



// -------------------------------------------------------------------------------------------------
//
//  Interface for SoundSources
//
// -------------------------------------------------------------------------------------------------
class I_SoundSource
{
   public:
     virtual bool Pause() const ;
     virtual void Pause(bool pause) ;
     
     virtual bool Loop() const ;
     virtual void Loop(bool loop) ;
     
     virtual _tg Gain() const ;
     virtual void Gain(_tg gain) ;
     
     virtual _tg Pitch() const ;
     virtual void Pitch(_tg pitch) ;
     
     virtual void Position(_tg x, _tg y, _tg z) ;
     virtual void Velocity(_tg x, _tg y, _tg z) ;
     
     virtual void DistanceAttenuation(bool bAttenuation) ;
     virtual void ReferenceDistance(_tg dist) ;
     virtual void MaxDistance(_tg dist) ;
     
     virtual void Play(I_Sample *sample) ;
     virtual void Stop() ;
};



//******************************************************************************************************************************************************************************************************
//                                                                  T O N V E R W A L T U N G
//******************************************************************************************************************************************************************************************************
class _tonverwaltung{
        public:
                _tonverwaltung(_akustik*);
                virtual ~_tonverwaltung();
                _akustik*akustik();
                void erzeugenton(const unsigned int,const _zeichenkette<char>&);
                void erzeugentonfluss(const unsigned int,const _zeichenkette<char>&);
                _ton*ton(const unsigned int);
                _tonfluss*tonfluss(const unsigned int);
                _tonsammlung*tonsammlung();
        private:
                _akustik*pakustik;
                _tonsammlung*ptonsammlung;
                _ton*pton[128];
                _tonfluss*ptonfluss[16];
        
};
//******************************************************************************************************************************************************************************************************
//                                                              S O U N D D E V I C E 
//******************************************************************************************************************************************************************************************************
template<class _tg,class _ta> class _tonschnittstelle{
        public:
                _tonschnittstelle();
                virtual ~_tonschnittstelle();
                virtual void spielen(_tonton<_tg,_ta>*)=0;
        private:            
};
template<class _tg,class _ta>
_tonschnittstelle<_tg,_ta>::_tonschnittstelle(){
};
template<class _tg,class _ta>
_tonschnittstelle<_tg,_ta>::~_tonschnittstelle(){
};
//******************************************************************************************************************************************************************************************************
//                                                              S O U N D T U P L E 
//******************************************************************************************************************************************************************************************************
template<class _tg> class _tontuppel:public _listenknotenbasis<_tontuppel<_tg> >{
        public:
                inline _tontuppel(_listebasis<_tontuppel<_tg> >*,_tg,_tg);
                virtual ~_tontuppel();
                inline void x(const _tg);
                inline void y(const _tg);
                inline _tg x()const;
                inline _tg y()const;
        private:
                _tg px;
                _tg py;
                
};
template<class _tg> _tontuppel<_tg>::_tontuppel(_listebasis<_tontuppel<_tg> >*l,_tg x,_tg y):_listenknotenbasis<_tontuppel<_tg> >(l){
                                                                px=x;
                                                                py=y;
};
template<class _tg> _tontuppel<_tg>::~_tontuppel(){
};
template<class _tg> void _tontuppel<_tg>::x(const _tg x){
                                                                px=x;
};
template<class _tg> void _tontuppel<_tg>::y(const _tg y){
                                                                py=y;
};

template<class _tg> _tg _tontuppel<_tg>::x()const{
                                                                return(px);
};
template<class _tg> _tg _tontuppel<_tg>::y()const{
                                                                return(py);
};

//******************************************************************************************************************************************************************************************************
//                                                              S O U N D C U R V E H E R M I T E 
//******************************************************************************************************************************************************************************************************
template<class _tg,class _ta> class _tonkurvehermite:public _listenknotenbasis<_tonkurvehermite<_tg,_ta> >,public _kurvehermite2<_tg>{
        friend class _tonmodifikationkurve<_tg,_ta>;
        public:
                _tonkurvehermite(_listebasis<_tonkurvehermite<_tg,_ta> >*);
                _tonkurvehermite(_listebasis<_tonkurvehermite<_tg,_ta> >*,const _vektor<_tg>&,const _vektor<_tg>&,const _vektor<_tg>&,const _vektor<_tg>&);
                _tonkurvehermite(_listebasis<_tonkurvehermite<_tg,_ta> >*,_tonkurvehermite<_tg,_ta>*);
                virtual ~_tonkurvehermite();
                bool hasmodification()const;
                //void setmodification(_tonmodifikationkurve<_tg,_ta>*);
                _tonmodifikationkurve<_tg,_ta>*modification();
                void clearmodification();
        private:
                _tonmodifikationkurve<_tg,_ta>*pmodificationcurve;
};
template<class _tg,class _ta> 
_tonkurvehermite<_tg,_ta>::_tonkurvehermite(_listebasis<_tonkurvehermite<_tg,_ta> >*l):_listenknotenbasis<_tonkurvehermite<_tg,_ta> >(l){
                                                                pmodificationcurve=0;
};
template<class _tg,class _ta> 
_tonkurvehermite<_tg,_ta>::_tonkurvehermite(_listebasis<_tonkurvehermite<_tg,_ta> >*l,const _vektor<_tg>&p0,const _vektor<_tg>&p1,const _vektor<_tg>&v0,const _vektor<_tg>&v1):_listenknotenbasis<_tonkurvehermite<_tg,_ta> >(l),_kurvehermite2<_tg>(p0,p1,v0,v1){
                                                                pmodificationcurve=0;
};
template<class _tg,class _ta> 
_tonkurvehermite<_tg,_ta>::_tonkurvehermite(_listebasis<_tonkurvehermite<_tg,_ta> >*l,_tonkurvehermite<_tg,_ta>*n):_listenknotenbasis<_tonkurvehermite<_tg,_ta> >(l),_kurvehermite2<_tg>(n){
                                                                pmodificationcurve=0;
                                                                if(n->pmodificationcurve) pmodificationcurve=new _tonmodifikationkurve<_tg,_ta>(this,n->pmodificationcurve);
};
template<class _tg,class _ta> 
_tonkurvehermite<_tg,_ta>::~_tonkurvehermite(){
                                                                clearmodification();
};
template<class _tg,class _ta> 
bool _tonkurvehermite<_tg,_ta>::hasmodification()const{
                                                                if(pmodificationcurve) return(true); else return(false);
};
template<class _tg,class _ta> 
_tonmodifikationkurve<_tg,_ta>* _tonkurvehermite<_tg,_ta>::modification(){
                                                                return(pmodificationcurve);
};
template<class _tg,class _ta> 
void _tonkurvehermite<_tg,_ta>::clearmodification(){
                                                                if(pmodificationcurve) {
                                                                 delete pmodificationcurve;
                                                                 pmodificationcurve=0;
                                                                };
};

//******************************************************************************************************************************************************************************************************
//                                                              S O U N D F U N C T I O N 
//******************************************************************************************************************************************************************************************************
template<class _tg,class _ta> class _tonfunktion:public _listebasis<_tonkurvehermite<_tg,_ta> >{
        public:
                _tonfunktion();
                _tonfunktion(_tonfunktion<_tg,_ta>*);
                virtual ~_tonfunktion();
                void kopieren(_tonfunktion<_tg,_ta>*);
                _tg dauer()const;
                _tg createbuffer(const unsigned int,const unsigned int);
                _tg updatebuffer(const unsigned int);
                void clearbuffer();
                inline _tonbuffer<_tg,_ta>*buffer(const unsigned int);
                bool hasmodification()const;
                _tg solvecurvesequence(const _tg)const;
        private:
                _tonbuffer<_tg,_ta>*pbuffery;
                _tonbuffer<_tg,_ta>*pbufferz;
                
};
template<class _tg,class _ta> _tonfunktion<_tg,_ta>::_tonfunktion(){
                                                                pbuffery=0;
                                                                pbufferz=0;
};
template<class _tg,class _ta> _tonfunktion<_tg,_ta>::_tonfunktion(_tonfunktion<_tg,_ta>*n){
                                                                pbuffery=0;
                                                                pbufferz=0;
                                                                kopieren(n);
};
template<class _tg,class _ta> _tonfunktion<_tg,_ta>::~_tonfunktion(){
                                                                clearbuffer();
};
template<class _tg,class _ta> void _tonfunktion<_tg,_ta>::kopieren(_tonfunktion<_tg,_ta>*n){
                                                                _tonkurvehermite<_tg,_ta>*nit;
                                                                //-------------------------
                                                                if(n){
                                                                 loeschen();
                                                                 clearbuffer();
                                                                 if(n->anfang(nit))do{
                                                                  new _tonkurvehermite<_tg,_ta>(this,nit);
                                                                 }while(n->naechstes(nit));
                                                                 if(n->pbuffery) pbuffery=new _tonbuffer<_tg,_ta>(n->pbuffery);
                                                                 if(n->pbufferz) pbufferz=new _tonbuffer<_tg,_ta>(n->pbufferz);
                                                                };
};
template<class _tg,class _ta> _tg _tonfunktion<_tg,_ta>::dauer()const{
                                                                _tonkurvehermite<_tg,_ta>*s0;
                                                                _tonkurvehermite<_tg,_ta>*s1;
                                                                //------------------
                                                                if(anfang(s0)){
                                                                 s1=s0->vorheriges();
                                                                 return(s1->ort(1)[0]-s0->ort(0)[0]);
                                                                }else{
                                                                 //error
                                                                 return(0);
                                                                };
};
template<class _tg,class _ta> _tg _tonfunktion<_tg,_ta>::createbuffer(const unsigned int rate,const unsigned int tres){
                                                                //_tonbuffer<_tg,_ta>*b;
                                                                _tonkurvehermite<_tg,_ta>*cit;
                                                                _tg s;
                                                                _tg t0;
                                                                _tg t1;
                                                                unsigned int i;
                                                                unsigned int ttres;
                                                                unsigned int bsize;
                                                                _vektor<_tg> p0;
                                                                _vektor<_tg> p1;
                                                                unsigned int x0;
                                                                unsigned int x1;
                                                                unsigned int xi;
                                                                unsigned int xd;
                                                                _tg f0;
                                                                _tg f1;
                                                                _tg i0;
                                                                _tg i1;
                                                                _tg y;
                                                                _tg z;
                                                                _tg dur;
                                                                //--------------------------------
                                                                clearbuffer();
                                                                dur=0;
                                                                if(anfang(cit)){
                                                                 dur=dauer();
                                                                 bsize=(unsigned int)(1+_tg(rate)*dur);
                                                                 pbuffery=new _tonbuffer<_tg,_ta>(bsize,rate);
                                                                 pbufferz=new _tonbuffer<_tg,_ta>(bsize,rate);
                                                                 ttres=tres/anzahl();
                                                                 if(ttres<2) ttres=2;
                                                                 s=_tg(1)/_tg(ttres);
                                                                 if(anfang(cit))do{
                                                                  for(i=0;i<ttres;i++){
                                                                   t0=s*_tg(i);
                                                                   p0=cit->berechnen(t0);
                                                                   t1=s*_tg(i+1);
                                                                   p1=cit->berechnen(t1);
                                                                   i0=p0[1];
                                                                   i1=p1[1];
                                                                   f0=p0[2];
                                                                   f1=p1[2];
                                                                   x0=(unsigned int)(p0[0]*_tg(rate));//bsize=brate !!!!!!!!!!!!!!??????????!!!!!!!!!
                                                                   x1=(unsigned int)(p1[0]*_tg(rate));
                                                                   xd=x1-x0;
                                                                   if(xd<1) xd=1;
                                                                   for(xi=x0;xi<=x1;xi++){
                                                                    y=i0+((i1-i0)*(_tg(xi-x0)/_tg(xd)));
                                                                    z=f0+((f1-f0)*(_tg(xi-x0)/_tg(xd)));
                                                                    pbuffery->setzen(xi,y);
                                                                    pbufferz->setzen(xi,z);
                                                                   };
                                                                  };
                                                                 }while(naechstes(cit));
                                                                };
                                                                return(dur);
};
template<class _tg,class _ta> _tg _tonfunktion<_tg,_ta>::updatebuffer(const unsigned int tres){
                                                                _tonkurvehermite<_tg,_ta>*cit;
                                                                _tg s;
                                                                //_tg t0;
                                                                _tg t1;
                                                                unsigned int i;
                                                                unsigned int ttres;
                                                                unsigned int brate;
                                                                _vektor<_tg> p0;
                                                                _vektor<_tg> p1;
                                                                unsigned int x0;
                                                                unsigned int x1;
                                                                unsigned int xi;
                                                                unsigned int xd;
                                                                _tg f0;
                                                                _tg f1;
                                                                _tg i0;
                                                                _tg i1;
                                                                _tg y;
                                                                _tg z;
                                                                _tg dur;
                                                                //--------------------------------
                                                                //clearbuffer();
                                                                dur=0;
                                                                if(anfang(cit)){
                                                                 dur=dauer();
                                                                 if((pbuffery)&&(pbufferz)){
                                                                  brate=pbuffery->rate();//(unsigned int)(1+_tg(rate)*dur);
                                                                  pbuffery->zero();//=new _tonbuffer<_tg,_ta>(bsize,rate);
                                                                  pbufferz->zero();//=new _tonbuffer<_tg,_ta>(bsize,rate);
                                                                  ttres=tres/anzahl();
                                                                  if(ttres<2) ttres=2;
                                                                  s=_tg(1)/_tg(ttres);
                                                                  if(anfang(cit))do{
                                                                   p1=cit->berechnen(0);
                                                                   for(i=0;i<ttres;i++){
                                                                    //t0=s*_tg(i);
                                                                    p0=p1;//cit->berechnen(t0);
                                                                    t1=s*_tg(i+1);
                                                                    p1=cit->berechnen(t1);
                                                                    i0=p0[1];
                                                                    i1=p1[1];
                                                                    f0=p0[2];
                                                                    f1=p1[2];
                                                                    x0=(unsigned int)(p0[0]*_tg(brate));
                                                                    x1=(unsigned int)(p1[0]*_tg(brate));
                                                                    xd=x1-x0;
                                                                    if(xd<1) xd=1;
                                                                    for(xi=x0;xi<=x1;xi++){
                                                                     y=i0+((i1-i0)*(_tg(xi-x0)/_tg(xd)));
                                                                     z=f0+((f1-f0)*(_tg(xi-x0)/_tg(xd)));
                                                                     pbuffery->setzen(xi,y);
                                                                     pbufferz->setzen(xi,z);
                                                                    };
                                                                   };
                                                                  }while(naechstes(cit));
                                                                 };
                                                                };
                                                                return(dur);
};
template<class _tg,class _ta> void _tonfunktion<_tg,_ta>::clearbuffer(){
                                                                if(pbuffery){
                                                                 delete pbuffery;
                                                                 pbuffery=0;
                                                                };
                                                                if(pbufferz){
                                                                 delete pbufferz;
                                                                 pbufferz=0;
                                                                };
};
template<class _tg,class _ta> _tonbuffer<_tg,_ta>* _tonfunktion<_tg,_ta>::buffer(const unsigned int i){
                                                                if(i==0){
                                                                 return(pbuffery);
                                                                }else{
                                                                 return(pbufferz);
                                                                };
};
template<class _tg,class _ta> bool _tonfunktion<_tg,_ta>::hasmodification()const{
                                                                _tonkurvehermite<_tg,_ta>*cit;
                                                                bool r;
                                                                //-----------
                                                                r=false;
                                                                if(anfang(cit))do{
                                                                 if(cit->hasmodification()) r=true;
                                                                }while((naechstes(cit))&&(r==false));
                                                                return(r);
};
template<class _tg,class _ta>
_tg _tonfunktion<_tg,_ta>::solvecurvesequence(const _tg x)const{
                                                                _tonkurvehermite<_tg,_ta>*c;
                                                                _tonkurvehermite<_tg,_ta>*cit;
                                                                _tg t;
                                                                _tg tmin;
                                                                _tg tmax;
                                                                _tg nz=0.001;
                                                                _vektor<_tg> o;
                                                                //--------------------------------
                                                                //die kurve ermittlen, die mit ihren stützpunkten 
                                                                //den punkt x überdeckt (==c)
                                                                c=0;
                                                                if(anfang(cit))do{
                                                                 if((x>=cit->ort(0)[0])&&(x<cit->ort(1)[0])){
                                                                  c=cit;
                                                                 };
                                                                }while(naechstes(cit));
                                                                //c ist diejenige kurve, die mindestens 
                                                                //ein y - wert für x aufweisen muss
                                                                //dabei mit t annähern, starten mit t=0.5
                                                                if(c!=0){
                                                                 tmin=0;
                                                                 tmax=1;
                                                                 t=0.5;
                                                                 do{
                                                                  o=c->berechnen(t);
                                                                  if(o[0]>x) {
                                                                   tmax=t;
                                                                   t-=(tmax-tmin)*0.5;
                                                                  }else{
                                                                   tmin=t;
                                                                   t+=(tmax-tmin)*0.5;
                                                                  };
                                                                 }while(fabs(o[0]-x)>nz);
                                                                };
                                                                return(o[1]);
};
//******************************************************************************************************************************************************************************************************
//                                                              S O U N D C O V E R
//******************************************************************************************************************************************************************************************************
template<class _tg,class _ta> class _tonhuelle:public _tonfunktion<_tg,_ta>{
        public:
                _tonhuelle();
                _tonhuelle(_tonhuelle<_tg,_ta>*);
                virtual ~_tonhuelle();
                void kopieren(_tonhuelle<_tg,_ta>*);
};
template<class _tg,class _ta> 
_tonhuelle<_tg,_ta>::_tonhuelle(){
};
template<class _tg,class _ta> 
_tonhuelle<_tg,_ta>::_tonhuelle(_tonhuelle<_tg,_ta>*n):_tonfunktion<_tg,_ta>(n){
};
template<class _tg,class _ta> 
_tonhuelle<_tg,_ta>::~_tonhuelle(){
};
template<class _tg,class _ta> 
void _tonhuelle<_tg,_ta>::kopieren(_tonhuelle<_tg,_ta>*n){
                                                                _tonfunktion<_tg,_ta>::kopieren(n);
};
//******************************************************************************************************************************************************************************************************
//                                                              S O U N D B U F F E R 
//******************************************************************************************************************************************************************************************************
template<class _tg,class _ta> class _tonbuffer{
        public:
                _tonbuffer();
                _tonbuffer(_tonbuffer<_tg,_ta>*);
                _tonbuffer(const unsigned int,const unsigned int);
                virtual ~_tonbuffer();
                void kopieren(_tonbuffer<_tg,_ta>*);
                void konvertieren(_tonbuffer<_tg,_ta>*,const unsigned int,const unsigned int);
                void erzeugen(const unsigned int,const unsigned int);
                void loeschen();
                void zero();
                void clip(_tg);
                inline unsigned int groesse()const;
                inline unsigned int rate()const;
                inline void setzen(const unsigned int,_tg);
                inline _tg holen(const unsigned int)const;
                inline _tg dauer()const;
        private:
                _tg*pbuffer;
                unsigned int psize;
                unsigned int prate;
};
template<class _tg,class _ta> 
_tonbuffer<_tg,_ta>::_tonbuffer(){
                                                                pbuffer=0;
                                                                psize=0;
                                                                prate=1;
};
template<class _tg,class _ta> 
_tonbuffer<_tg,_ta>::_tonbuffer(_tonbuffer<_tg,_ta>*n){
                                                                pbuffer=0;
                                                                psize=0;
                                                                prate=1;
                                                                kopieren(n);        
};
template<class _tg,class _ta> 
_tonbuffer<_tg,_ta>::_tonbuffer(const unsigned int groesse,const unsigned int rate){
                                                                if(groesse!=0){
                                                                 pbuffer=new _tg[groesse];
                                                                 psize=groesse;
                                                                 prate=rate;
                                                                 if(prate<1) prate=1;
                                                                 zero();
                                                                }else{
                                                                 pbuffer=0;
                                                                 psize=0;
                                                                 prate=1;
                                                                };
};
template<class _tg,class _ta> 
_tonbuffer<_tg,_ta>::~_tonbuffer(){
                                                                loeschen();
};
template<class _tg,class _ta> 
void _tonbuffer<_tg,_ta>::kopieren(_tonbuffer<_tg,_ta>*n){
                                                                unsigned int i;
                                                                if(n){
                                                                 loeschen();
                                                                 psize=n->psize;
                                                                 pbuffer=new _tg[psize];
                                                                 for(i=0;i<psize;i++){
                                                                  pbuffer[i]=n->pbuffer[i];
                                                                 };
                                                                 prate=n->prate;
                                                                };
};
template<class _tg,class _ta> 
void _tonbuffer<_tg,_ta>::konvertieren(_tonbuffer<_tg,_ta>*n,const unsigned int groesse,const unsigned int rate){
                                                                _tg tit;
                                                                _tg nit;
                                                                _tg f;
                                                                //-----------------
                                                                if((n)&&(groesse>0)&&(rate>0)){
                                                                 loeschen();
                                                                 erzeugen(groesse,rate);
                                                                 for(tit=0;tit<groesse;tit+=1){
                                                                  nit=n->groesse()*(tit/(_tg(groesse)-1));
                                                                  f=nit-floor(nit);
                                                                  pbuffer[(unsigned int)tit]=n->holen((unsigned int)nit)*(1-f) + n->holen((unsigned int)(nit+1))*f;
                                                                 };
                                                                };
};
template<class _tg,class _ta> 
void _tonbuffer<_tg,_ta>::erzeugen(const unsigned int groesse,const unsigned int rate){
                                                                loeschen();
                                                                if((groesse>0)&&(rate>0)){
                                                                 psize=groesse;
                                                                 prate=rate;
                                                                 pbuffer=new _tg[psize];
                                                                 zero();
                                                                };
};
template<class _tg,class _ta> 
void _tonbuffer<_tg,_ta>::loeschen(){
                                                                if(pbuffer){
                                                                 delete pbuffer;
                                                                 pbuffer=0;
                                                                 psize=0;
                                                                 prate=1;
                                                                };
};
template<class _tg,class _ta> 
_tg _tonbuffer<_tg,_ta>::dauer()const{
                                                                _tg t;
                                                                t=_tg(psize)/_tg(prate);
                                                                return(t);
};
template<class _tg,class _ta> 
void _tonbuffer<_tg,_ta>::zero(){
                                                                unsigned int i;
                                                                //-------------
                                                                for(i=0;i<psize;i++){
                                                                 pbuffer[i]=0;
                                                                };
};
template<class _tg,class _ta> 
void _tonbuffer<_tg,_ta>::clip(_tg r){
                                                                unsigned int i;
                                                                //-------------
                                                                for(i=0;i<psize;i++){
                                                                 if(pbuffer[i]>+r) pbuffer[i]=+r; else
                                                                 if(pbuffer[i]<-r) pbuffer[i]=-r; 
                                                                };
};
template<class _tg,class _ta> 
unsigned int _tonbuffer<_tg,_ta>::groesse()const{
                                                                return(psize);
};
template<class _tg,class _ta> 
unsigned int _tonbuffer<_tg,_ta>::rate()const{
                                                                return(prate);
};
template<class _tg,class _ta> 
_tg _tonbuffer<_tg,_ta>::holen(const unsigned int i)const{
                                                                if(i<psize){
                                                                 if(pbuffer) return(pbuffer[i]);
                                                                };
                                                                //error
                                                                return(0);
};
template<class _tg,class _ta> 
void _tonbuffer<_tg,_ta>::setzen(const unsigned int i,_tg x){
                                                                if(i<psize){
                                                                 if(pbuffer){
                                                                  pbuffer[i]=x;
                                                                 };
                                                                }else{
                                                                 //error
                                                                };
};
//******************************************************************************************************************************************************************************************************
//                                                              S O U N D B U F F E R S Y N T H E S I S 
//******************************************************************************************************************************************************************************************************
template<class _tg,class _ta> class _tonbuffersynthese:
public _tonbuffer<_tg,_ta>,
public _listebasis<_tonmodifikationbuffer<_tg,_ta> >{
        public:
                _tonbuffersynthese();
                _tonbuffersynthese(_tonbuffersynthese<_tg,_ta>*);
                virtual ~_tonbuffersynthese();
                void kopieren(_tonbuffersynthese<_tg,_ta>*);
                void setcoverintensity(_tonhuelle<_tg,_ta>*);
                void setcoverfrequency(_tonhuelle<_tg,_ta>*);
                _tonhuelle<_tg,_ta>*coverintensity();
                _tonhuelle<_tg,_ta>*coverfrequency();
                void clearcoverintensity();
                void clearcoverfrequency();
                virtual void synthesize(const unsigned int)=0;
                void modifybuffer();
                void clearbuffer();
        private:
                _tonhuelle<_tg,_ta>*phuellei;
                _tonhuelle<_tg,_ta>*phuellef;
};
template<class _tg,class _ta> 
_tonbuffersynthese<_tg,_ta>::_tonbuffersynthese(){
                                                                phuellei=0;
                                                                phuellef=0;
};
template<class _tg,class _ta> 
_tonbuffersynthese<_tg,_ta>::_tonbuffersynthese(_tonbuffersynthese<_tg,_ta>*n):_tonbuffer<_tg,_ta>(n){
                                                                _tonmodifikationbuffer<_tg,_ta>*mit;
                                                                //----------------------------------------
                                                                phuellei=0;
                                                                phuellef=0;
                                                                if(n){
                                                                 if(n->phuellei) phuellei=new _tonhuelle<_tg,_ta>(n->phuellei);
                                                                 if(n->phuellef) phuellef=new _tonhuelle<_tg,_ta>(n->phuellef);
                                                                 if(n->anfang(mit))do{
                                                                  //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                                                                 }while(n->naechstes(mit));
                                                                };
};
template<class _tg,class _ta> 
_tonbuffersynthese<_tg,_ta>::~_tonbuffersynthese(){
                                                                clearcoverintensity();
                                                                clearcoverfrequency();
};
template<class _tg,class _ta> 
void _tonbuffersynthese<_tg,_ta>::kopieren(_tonbuffersynthese<_tg,_ta>*n){
                                                                _tonmodifikationbuffer<_tg,_ta>*mit;
                                                                //----------------------------------------
                                                                if(n){
                                                                 clearcoverintensity();
                                                                 clearcoverfrequency();
                                                                 clearmodification();
                                                                 if(n->phuellei) phuellei=new _tonhuelle<_tg,_ta>(n->phuellei);
                                                                 if(n->phuellef) phuellef=new _tonhuelle<_tg,_ta>(n->phuellef);
                                                                 if(n->anfang(mit))do{
                                                                  //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                                                                 }while(n->naechstes(mit));
                                                                };
};
template<class _tg,class _ta> 
void _tonbuffersynthese<_tg,_ta>::setcoverintensity(_tonhuelle<_tg,_ta>*sh){
                                                                if(sh!=0){
                                                                 clearcoverintensity();
                                                                 phuellei=sh;//new _tonhuelle<_tg,_ta>(sh);
                                                                };
};
template<class _tg,class _ta> 
void _tonbuffersynthese<_tg,_ta>::setcoverfrequency(_tonhuelle<_tg,_ta>*sh){
                                                                if(sh!=0){
                                                                 clearcoverfrequency();
                                                                 phuellef=sh;//new _tonhuelle<_tg,_ta>(sh);
                                                                };
};
template<class _tg,class _ta> 
_tonhuelle<_tg,_ta>*_tonbuffersynthese<_tg,_ta>::coverintensity(){
                                                                return(phuellei);
};
template<class _tg,class _ta> 
_tonhuelle<_tg,_ta>*_tonbuffersynthese<_tg,_ta>::coverfrequency(){
                                                                return(phuellef);
};
template<class _tg,class _ta> 
void _tonbuffersynthese<_tg,_ta>::clearcoverintensity(){
                                                                if(phuellei){
                                                                 delete phuellei;
                                                                 phuellei=0;
                                                                };
};
template<class _tg,class _ta> 
void _tonbuffersynthese<_tg,_ta>::clearcoverfrequency(){
                                                                if(phuellef){
                                                                 delete phuellef;
                                                                 phuellef=0;
                                                                };
};
template<class _tg,class _ta> 
void _tonbuffersynthese<_tg,_ta>::modifybuffer(){
                                                                _tonmodifikationbuffer<_tg,_ta>*sit;
                                                                //------------------
                                                                if(groesse()>0){
                                                                 if(anfang(sit))do{
                                                                  sit->bearbeiten(this);
                                                                 }while(naechstes(sit));
                                                                };
};
template<class _tg,class _ta> 
void _tonbuffersynthese<_tg,_ta>::clearbuffer(){
                                                                _tonbuffer<_tg>::loeschen();            
};
//******************************************************************************************************************************************************************************************************
//                                                              S O U N D W A V E 
//******************************************************************************************************************************************************************************************************
template<class _tg,class _ta> class _tonwelle:
public _tonfunktion<_tg,_ta>,
public _tonbuffersynthese<_tg,_ta>,
public _listenknotenbasis<_tonwelle<_tg,_ta> >{
        using _tonfunktion<_tg,_ta>::buffer;
        using _listebasis<_tonkurvehermite<_tg,_ta> >::anfang;
        using _listebasis<_tonkurvehermite<_tg,_ta> >::naechstes;
        using _listebasis<_tonkurvehermite<_tg,_ta> >::vorheriges;
        using _listebasis<_tonmodifikationbuffer<_tg,_ta> >::anfang;
        using _listebasis<_tonmodifikationbuffer<_tg,_ta> >::naechstes;
        using _listebasis<_tonmodifikationbuffer<_tg,_ta> >::vorheriges;
        public:
                _tonwelle(_listebasis<_tonwelle<_tg,_ta> >*);
                _tonwelle(_listebasis<_tonwelle<_tg,_ta> >*,_tonwelle<_tg,_ta>*);
                virtual ~_tonwelle();
                void kopieren(_tonwelle<_tg,_ta>*);
                virtual void synthesize(const unsigned int);
};
template<class _tg,class _ta> 
_tonwelle<_tg,_ta>::_tonwelle(_listebasis<_tonwelle<_tg,_ta> >*l):_listenknotenbasis<_tonwelle<_tg,_ta> >(l){
                                                                //presult=0;
};
template<class _tg,class _ta> 
_tonwelle<_tg,_ta>::_tonwelle(_listebasis<_tonwelle<_tg,_ta> >*l,_tonwelle<_tg,_ta>*n):_listenknotenbasis<_tonwelle<_tg,_ta> >(l),_tonfunktion<_tg,_ta>(n){
                                                                //phuellei=0;
                                                                //phuellef=0;
                                                                //presult=0;
                                                                //if(n){
                                                                // if(n->phuellei) phuellei=new _tonhuelle<_tg,_ta>(n->phuellei);
                                                                // if(n->phuellef) phuellef=new _tonhuelle<_tg,_ta>(n->phuellef);
                                                                // if(n->presult) presult=new _tonbuffer<_tg,_ta>(n->presult);
                                                                //};
};
template<class _tg,class _ta> 
_tonwelle<_tg,_ta>::~_tonwelle(){
                                                                //clearbufferwave();
                                                                //clearcoverintensity();
                                                                //clearcoverfrequency();
};
template<class _tg,class _ta> 
void _tonwelle<_tg,_ta>::kopieren(_tonwelle<_tg,_ta>*n){
                                                                _tonkurvehermite<_tg,_ta>*cit;
                                                                //------------------------------
                                                                if(n){
                                                                 _tonfunktion<_tg,_ta>::kopieren(n);
                                                                 _tonbuffersynthese<_tg,_ta>::kopieren(n);
                                                                 //clearbufferwave();
                                                                 //clearcoverintensity();
                                                                 //clearcoverfrequency();
                                                                 //if(n->phuellei) phuellei=new _tonhuelle<_tg,_ta>(n->phuellei);
                                                                 //if(n->phuellef) phuellef=new _tonhuelle<_tg,_ta>(n->phuellef);
                                                                 //if(n->presult) presult=new _tonbuffer<_tg,_ta>(n->presult);
                                                                };
                                                                
};

template<class _tg,class _ta> 
void _tonwelle<_tg,_ta>::synthesize(const unsigned int rate){
                                                                //funktion nutzt die buffer der hüllkurve
                                                                //um damit die Basisfunktionen der welle zu
                                                                //modellieren, das ergebnis ist result
                                                                _tonkurvehermite<_tg,_ta>*cit;
                                                                unsigned int groesse;
                                                                unsigned int i;
                                                                //unsigned int ir;   //resultiterator
                                                                _tg ib;   //basisiterator
                                                                unsigned int ibui;
                                                                _tg y,x;
                                                                _tg intensitaet;
                                                                _tg frequency;
                                                                _tg durmax;
                                                                //-----------------------
                                                                if((coverintensity())&&(coverfrequency())){
                                                                 _tonfunktion<_tg,_ta>::clearbuffer();//alten schrott löschen
                                                                 _tonfunktion<_tg,_ta>::createbuffer(rate*2,1000);//basisfunktionsbuffer holen
                                                                 if(coverintensity()->dauer()>coverfrequency()->dauer()) durmax=coverintensity()->dauer(); else durmax=coverfrequency()->dauer();
                                                                 groesse=(unsigned int)(1+_tg(rate)*durmax);
                                                                 coverintensity()->createbuffer(rate,1000);//hüllenbuffer holen
                                                                 coverfrequency()->createbuffer(rate,1000);//hüllenbuffer holen
                                                                 _tonbuffer<_tg,_ta>::erzeugen(groesse,rate);//presult=new _tonbuffer<_tg,_ta>(groesse,rate);
                                                                 if(_tonfunktion<_tg,_ta>::hasmodification()==false){//---basisfunktion ohne curvenmodification
                                                                  ib=0;
                                                                  for(i=0;i<groesse;i++){
                                                                   intensitaet=coverintensity()->buffer(0)->holen(i);
                                                                   frequency=coverfrequency()->buffer(0)->holen(i);
                                                                   ibui=(unsigned int)ib;
                                                                   y=_tonfunktion<_tg,_ta>::buffer(0)->holen(ibui);
                                                                   y*=intensitaet;
                                                                   setzen(i,y);
                                                                   ib+=(unsigned int)(2*frequency);
                                                                   while(ib>=(rate*2)) ib-=rate*2;
                                                                  };
                                                                 }else{//------------------------------------------------------primäre/tertiäre modifikation
                                                               
                                                                  
                                                                  
                                                                  
                                                                   
                                                                  
                                                                  
                                                                  
                                                                  
                                                                  
                                                                  
                                                                  //für alle curvenmodifikationen buffer anlegen
                                                                  if(anfang(cit))do{
                                                                   if(cit->hasmodification()) {
                                                                    cit->modification()->createbuffer(rate,1000);
                                                                    cit->modification()->resetiterator();
                                                                   };
                                                                  }while(naechstes(cit));
                                                                  //sampling und curvenmodificationsbuffer bearbeiten
                                                                  ib=0;
                                                                  for(i=0;i<groesse;i++){
                                                                   if(anfang(cit))do{//modification durchführen
                                                                    if(cit->hasmodification()) cit->modification()->bearbeiten();
                                                                   }while(naechstes(cit));
                                                                   intensitaet=coverintensity()->buffer(0)->holen(i);
                                                                   frequency=coverfrequency()->buffer(0)->holen(i);
                                                                   x=ib/_tg(rate*2);
                                                                   y=solvecurvesequence(x);
                                                                   y*=intensitaet;
                                                                   setzen(i,y);
                                                                   ib+=2*frequency;
                                                                   while(ib>=(rate*2)) ib-=rate*2;
                                                                  };
                                                                  //alle curvenmodificationsbuffer löschen und basisfunktion rücksetzen
                                                                  if(anfang(cit))do{
                                                                   if(cit->hasmodification()){
                                                                    cit->modification()->clearbuffer();
                                                                    cit->modification()->restorecurve();
                                                                   };
                                                                  }while(naechstes(cit));
                                                                 };
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 _tonfunktion<_tg,_ta>::clearbuffer();//basisfunctionsbuffer  löschen
                                                                 coverintensity()->clearbuffer();//hüllebuffer löschen
                                                                 coverfrequency()->clearbuffer();//hüllebuffer löschen
                                                                };
                                                                modifybuffer();
};

//******************************************************************************************************************************************************************************************************
//                                                              S O U N D S A M P L E 
//******************************************************************************************************************************************************************************************************
template<class _tg,class _ta> class _tondaten:
public _tonbuffersynthese<_tg,_ta>,
public _listenknotenbasis<_tondaten<_tg,_ta> >{
        public:
                _tondaten(_listebasis<_tondaten<_tg,_ta> >*,_zeichenkette<char>,const unsigned int);
                _tondaten(_listebasis<_tondaten<_tg,_ta> >*,_tondaten<_tg,_ta>*);
                virtual ~_tondaten();
                void kopieren(_tondaten<_tg,_ta>*);
                virtual void synthesize(const unsigned int);
                unsigned int channelindex()const;
                void channelindex(const unsigned int);
                virtual bool loadsample(const unsigned int)=0;
                void clearsample();
                _datei*datei();
        protected:                
                _tonbuffer<_tg,_ta>*samplebuffer();
        private:
                _datei pfile;
                _tonbuffer<_tg,_ta> psample;
                unsigned int pchannelindex;
};
template<class _tg,class _ta>
_tondaten<_tg,_ta>::_tondaten(_listebasis<_tondaten<_tg,_ta> >*l,_zeichenkette<char> datei,const unsigned int ci):_listenknotenbasis<_tondaten<_tg,_ta> >(l),pfile(datei){
                                                                //pfile=datei;
                                                                pchannelindex=ci;
};
template<class _tg,class _ta>
_tondaten<_tg,_ta>::_tondaten(_listebasis<_tondaten<_tg,_ta> >*l,_tondaten<_tg,_ta>*n):_listenknotenbasis<_tondaten<_tg,_ta> >(l),_tonbuffersynthese<_tg,_ta>(n),pfile(&n->pfile){
                                                                pchannelindex=0;
                                                                if(n){
                                                                 //pfile=n->pfile;
                                                                 pchannelindex=n->ci;
                                                                 psample.kopieren(&n->psample);
                                                                };
};
template<class _tg,class _ta>
_tondaten<_tg,_ta>::~_tondaten(){
};
template<class _tg,class _ta>
void _tondaten<_tg,_ta>::kopieren(_tondaten<_tg,_ta>*n){
                                                                if(n){
                                                                 pfile->kopieren(n->pfile);
                                                                 pchannelindex=n->ci;
                                                                 psample.kopieren(&n->psample);
                                                                };
}; 
/*
template<class _tg,class _ta>
void _tondaten<_tg,_ta>::synthesize(const unsigned int rate){
                                                                unsigned int i;
                                                                unsigned int x;
                                                                unsigned int bs;
                                                                unsigned int rs;
                                                                unsigned int us;

                                                                unsigned int xi;
                                                                
                                                                unsigned int s0;
                                                                unsigned int s1;
                                                                unsigned int s2;
                                                                unsigned int s3;
                                                                _tg y;
                                                                
                                                                //---------------------
                                                                if(loadsample(rate)){
                                                                 if((coverintensity()==0)&&(coverfrequency()==0)){
                                                                  _tonbuffer<_tg,_ta>::kopieren(samplebuffer());
                                                                 }else{
                                                                  
                                                                  _tonbuffer<_tg,_ta>::erzeugen(samplebuffer()->groesse(),rate);//samplebuffer ist der quellbuffer
                                                                  bs=1000;
                                                                  rs=250;
                                                                  us=5;
                                                                  xi=0;
                                                                  for(i=0;i<samplebuffer()->groesse();i+=2*rs+bs){
                                                                   s0=i+rs-us;
                                                                   s1=s0+us;
                                                                   s2=s1+bs;
                                                                   s3=s2+us;
                                                                   for(x=s0;x<s1;x++){//aufblenden
                                                                    y=samplebuffer()->holen(x)*(  _tg(x-s0)/_tg(us)   );
                                                                    setzen(xi,(holen(xi)+y));
                                                                    xi++;
                                                                   };
                                                                   for(x=s1;x<s2;x++){//füllen
                                                                    setzen(xi,(holen(xi)+samplebuffer()->holen(x)));
                                                                    xi++;
                                                                   };
                                                                   for(x=s2;x<s3;x++){//ausblenden
                                                                    y=samplebuffer()->holen(x)*(1-_tg(x-s2)/_tg(us)   );
                                                                    setzen(xi,(holen(xi)+y));
                                                                    xi++;
                                                                   };
                                                                   xi-=us;
                                                                  };
                                                                 };
                                                                 modifybuffer();
                                                                 clearsample();
                                                                };
};
*/
template<class _tg,class _ta>
void _tondaten<_tg,_ta>::synthesize(const unsigned int rate){
                                                                _tg bxsize;
                                                                _tg x;
                                                                unsigned int i;
                                                                _tg sx;
                                                                _tg su;
                                                                //_tg bu[22000];
                                                                //_tg bs[22000];
                                                                _tg uk[1024];
                                                                _tg u;
                                                                //_tg cu;
                                                               _tg busize;
                                                                _listebasis<_tontuppel<_tg> > tl;
                                                                _tontuppel<_tg>*tit;
                                                                //---------------------
                                                                
                                                             /*   uk[0]=1;
                                                                uk[1]=2;
                                                                uk[2]=4;
                                                                uk[3]=8;
                                                                uk[4]=16;
                                                                uk[5]=32;
                                                                uk[6]=64;
                                                                uk[7]=128;
                                                                uk[8]=256;
                                                                uk[9]=512;
                                                                uk[10]=1024;
                                                                uk[11]=2048;
                                                                uk[12]=4096;
                                                                uk[13]=8192;
                                                                uk[14]=16384;
                                                                uk[15]=32768;
                                                                uk[16]=65536;*/
                                                                for(i=0;i<128;i++){
                                                                 uk[i]=i;//pow(2.71,_tg(i)/_tg(100));
                                                                };
                                                                if(loadsample(rate)){
                                                                 if((coverintensity()==0)&&(coverfrequency()==0)){
                                                                  _tonbuffer<_tg,_ta>::kopieren(samplebuffer());
                                                                 }else{
                                                                  _tonbuffer<_tg,_ta>::erzeugen(samplebuffer()->groesse(),rate);//samplebuffer ist der quellbuffer
                                                                  bxsize=4000;//ortsbuffergröße
                                                                  busize=4000;//koeffizientenbuffergröße
                                                                  
                                                               
                                                                  for(i=0;i<samplebuffer()->groesse();i+=((unsigned int)(bxsize))){//den ortsbuffer in blöcke zerlegen
                                                                   
                                                                  // for(u=0;u<22000;u++){//koeffizientenbuffer leeren
                                                                  //  bu[int(u)]=0;
                                                                  //  bs[int(u)]=0;
                                                                  // };
                                                                   
                                                                   
                                                                   
                                                                   
                                                                   
                                                                   
                                                                   
                                                                   for(u=0;u<busize;u++){//dct -transformation
                                                                    su=0;
                                                                  //  if(u==0) cu=1/sqrt(2); else cu=1;
                                                                    for(x=0;x<bxsize;x++){
                                                                     sx=samplebuffer()->holen((unsigned int)(i+x));//quellbuffer auslesen    
                                                                     su+=sx*cos(((2*x+1)*u*_pi)/(bxsize*2));
                                                                    };
                                                               //     su*=cu;///sqrt(2*bxsize);//???????????????????????????
                                                                    
                                                                    //bu[int(u)]=su;
                                                                    //su/=busize;
                                                                    new _tontuppel<_tg>(&tl,u,su);
                                                                   };
                                                                   
                                                                   
                                                                   
                                                                   /* for(i=0;i<10000;i++){
                                                                    L->schreiben("y-wert =",bu[i]);
                                                                   };*/
                                                                   
                                                                   /*for(x=0;x<busize;x++){
                                                                    u=x*0.8;
                                                                    f0=u-floor(u);
                                                                    f0=1-ur;
                                                                    
                                                                    u0=int(u);
                                                                    u1=int(u)+1;
                                                                    
                                                                    bs[u0]=f0*bu[int(x)];
                                                                    bs[u1]=f1*bu[int(x)];
                                                                   };*/
                                                                   if(tl.anfang(tit))do{
                                                                    tit->x(tit->x()*1.5);
                                                                   }while(tl.naechstes(tit));
                                                                   
                                                                   
                                                                   
                                                                   
                                                                   
                                                                   
                                                                  //for(u=0;u<busize;u+=1){
                                                                  //  bu[int(u)]*=1.9-((u/busize)*1.8);
                                                                 //   bu[int(u)]=(0.2*bu[int(u)])+(0.8*bu[int(u)+1] );
                                                                  // };
                                                                 /*  bu[0]*=1.1;
                                                                   bu[1]*=1.5;
                                                                   bu[2]*=2;
                                                                   bu[3]*=1.5;
                                                                   bu[4]*=1.1;*/
                                                                  
                                                                   
                                                                   
                                                                   
                                                                   
                                                                   
                                                                   
                                                                   
                                                                   
                                                                   
                                                                   for(x=0;x<bxsize;x++){//inverse dct-transformation
                                                                    sx=0;
                                                                    if(tl.anfang(tit))do{
                                                                    //for(u=0;u<busize;u++){
                                                                  //   if(u==0) cu=1/sqrt(2); else cu=1;
                                                                     //su=tit->y();//bs[int(u)];
                                                                     sx+=tit->y()*cos(((2*x+1)*tit->x()*_pi)/(bxsize*2));
                                                                    }while(tl.naechstes(tit));
                                                                    sx/=busize+bxsize;  //auskommentiert : ergibt zu wenig pegel ????????????????????
                                                                    setzen((unsigned int)x+i,sx);//zielbuffer beladen
                                                                   };
                                                                  
                                                                  
                                                                  tl.loeschen();
                                                                  
                                                                  
                                                                  
                                                                  
                                                                  
                                                                  
                                                                  };
                                                                 };
                                                                 modifybuffer();
                                                                 clearsample();
                                                                };






                                                                  /* for(u=100;u<busize;u++){
                                                                    bu[int(u)-100]=bu[int(u)-1];
                                                                   };
                                                                   for(u=busize-100;u<busize;u++){
                                                                    bu[int(u)]=0;
                                                                   };*/
                                                                //   for(u=0;u<busize;u++){
                                                               //     bu[int(u)]*=1-1*(u/busize);
                                                               //    };








};



template<class _tg,class _ta>
unsigned int _tondaten<_tg,_ta>::channelindex()const{
                                                                return(pchannelindex);
};
template<class _tg,class _ta>
void _tondaten<_tg,_ta>::channelindex(const unsigned int ci){
                                                                pchannelindex=ci;
};
template<class _tg,class _ta>
void _tondaten<_tg,_ta>::clearsample(){
                                                                psample.loeschen();
};
template<class _tg,class _ta>
_datei* _tondaten<_tg,_ta>::datei(){
                                                                return(&pfile);
};
template<class _tg,class _ta>
_tonbuffer<_tg,_ta>* _tondaten<_tg,_ta>::samplebuffer(){
                                                                return(&psample);
};
//******************************************************************************************************************************************************************************************************
//                                                              S O U N D S A M P L E W A V 
//******************************************************************************************************************************************************************************************************
template<class _tg,class _ta> class _tondatenwav:
public _tondaten<_tg,_ta>{
        public:
                _tondatenwav(_listebasis<_tondaten<_tg,_ta> >*,_zeichenkette<char>,const unsigned int);
                _tondatenwav(_listebasis<_tondaten<_tg,_ta> >*,_tondatenwav<_tg,_ta>*);
                virtual ~_tondatenwav();
                void kopieren(_tondatenwav<_tg,_ta>*);
                virtual bool loadsample(const unsigned int);
};
template<class _tg,class _ta>
_tondatenwav<_tg,_ta>::_tondatenwav(_listebasis<_tondaten<_tg,_ta> >*l,_zeichenkette<char> datei,const unsigned int ci):_tondaten<_tg,_ta>(l,datei,ci){
};
template<class _tg,class _ta>
_tondatenwav<_tg,_ta>::_tondatenwav(_listebasis<_tondaten<_tg,_ta> >*l,_tondatenwav<_tg,_ta>*n):_tondaten<_tg,_ta>(l,n){
};
template<class _tg,class _ta>
_tondatenwav<_tg,_ta>::~_tondatenwav(){
};
template<class _tg,class _ta>
void _tondatenwav<_tg,_ta>::kopieren(_tondatenwav<_tg,_ta>*n){
                                                                if(n) _tondaten<_tg,_ta>::kopieren(n);
}; 
template<class _tg,class _ta>
bool _tondatenwav<_tg,_ta>::loadsample(const unsigned int ratefuersample){
                                                                unsigned char h[44];
                                                                unsigned int kanaele;
                                                                unsigned int rate;
                                                                unsigned int bytepsec;
                                                                unsigned int sota;
                                                                unsigned int s;
                                                                unsigned int c;
                                                                unsigned int i;
                                                                unsigned int i0;
                                                                unsigned int i1;
                                                                unsigned int i2;
                                                                unsigned int i3;
                                                                unsigned char*temp;
                                                                unsigned int groesse;
                                                                _tg sec;
                                                                _tg y;
                                                                signed int kanval;
                                                                unsigned long int geladen;
                                                                unsigned int sizefuersample;
                                                                _tonbuffer<_tg,_ta> tempbuffer;
                                                                //----------------------
                                                                L->schreiben("loadsample_");
                                                                if(datei()->oeffnen()){
                                                                 L->schreiben("openeed");
                                                                 datei()->laden(h,44,geladen);
                                                                 if(geladen==44){
                                                                  L->schreiben("geladen");
                                                                  //h untersuchen 
                                                                  if((h[0]=='R')&&(h[1]=='I')&&(h[2]=='F')&&(h[3]=='F')&&(h[8]=='W')&&(h[9]=='A')&&(h[10]=='V')&&(h[11]=='E')){
                                                                   L->schreiben("passed");
                                                                   kanaele=h[22];
                                                                   i0=h[24];
                                                                   i1=h[25];
                                                                   i2=h[26];
                                                                   i3=h[27];
                                                                   rate=i0|(i1<<8)|(i2<<16)|(i3<<24);
                                                                   i0=h[28];
                                                                   i1=h[29];
                                                                   i2=h[30];
                                                                   i3=h[31];
                                                                   bytepsec=i0|(i1<<8)|(i2<<16)|(i3<<24);
                                                                   sota=(bytepsec/rate)/kanaele;
                                                                   i0=h[40];
                                                                   i1=h[41];
                                                                   i2=h[42];
                                                                   i3=h[43];
                                                                   groesse=i0|(i1<<8)|(i2<<16)|(i3<<24);
                                                                   groesse=(groesse/kanaele)/sota;
                                                                   sec=_tg(groesse)/_tg(rate);
                                                                   temp=new unsigned char[groesse*kanaele*sota];
                                                                   for(i0=0;i0<groesse*kanaele*sota;i0++) temp[i0]=0;
                                                                   datei()->laden(temp,groesse*kanaele*sota,geladen);
                                                                   //**************** DEBUG *********************************************
                                                                   L->schreiben("Soundsamplewav::loadsample() : groesse     = ",(int)groesse);
                                                                   L->schreiben("Soundsamplewav::loadsample() : rate     = ",(int)rate);
                                                                   L->schreiben("Soundsamplewav::loadsample() : sota     = ",(int)sota);
                                                                   L->schreiben("Soundsamplewav::loadsample() : kanaele = ",(int)kanaele);
                                                                   //********************************************************************
                                                                   if(rate==ratefuersample){//-------rate == ratefuersample , eins zu eins übernehemen
                                                                    sizefuersample=groesse;
                                                                    samplebuffer()->erzeugen(sizefuersample,ratefuersample);
                                                                    for(i=0;i<groesse;i++){
                                                                     for(c=0;c<kanaele;c++){ 
                                                                      if(c==channelindex()) {
                                                                       kanval=0;
                                                                       for(s=0;s<sota;s++){
                                                                        i0=(unsigned int)temp[i*kanaele*sota+c*sota+s];
                                                                        kanval|=(signed int)(i0<<(s*8));
                                                                       };
                                                                       y=(_tg)kanval;
                                                                       if(sota!=1){
                                                                        if(y>_tg((1<<(sota*8-1))-1)){
                                                                         y=y-_tg(1<<(sota*8));
                                                                        };
                                                                       };
                                                                       if(sota==1){
                                                                        y=y-128;
                                                                       };
                                                                       y/=_tg(1<<(sota*8-1));
                                                                       samplebuffer()->setzen(i,y);
                                                                      };
                                                                     };
                                                                    };
                                                                   }else{//---------------------------rate != ratefuersample , konversion durchführen
                                                                    sizefuersample=(unsigned int)(sec*_tg(ratefuersample));
                                                                    tempbuffer.erzeugen(groesse,rate);
                                                                    for(i=0;i<groesse;i++){
                                                                     for(c=0;c<kanaele;c++){ 
                                                                      if(c==channelindex()) {
                                                                       kanval=0;
                                                                       for(s=0;s<sota;s++){
                                                                        i0=(unsigned int)temp[i*kanaele*sota+c*sota+s];
                                                                        kanval|=(signed int)(i0<<(s*8));
                                                                       };
                                                                       y=(_tg)kanval;
                                                                       if(sota!=1){
                                                                        if(y>_tg((1<<(sota*8-1))-1)){
                                                                         y=y-_tg(1<<(sota*8));
                                                                        };
                                                                       };
                                                                       if(sota==1){
                                                                        y=y-128;
                                                                       };
                                                                       y/=_tg(1<<(sota*8-1));
                                                                       tempbuffer.setzen(i,y);
                                                                      };
                                                                     };
                                                                    };
                                                                    samplebuffer()->konvertieren(&tempbuffer,sizefuersample,ratefuersample);
                                                                   };
                                                                   delete[] temp;
                                                                   datei()->schliessen();
                                                                   return(true);
                                                                  }else{//riffwave
                                                                   datei()->schliessen();return(false);
                                                                  };
                                                                 }else{//geladen==44
                                                                  datei()->schliessen();return(false);
                                                                 };
                                                                };
                                                                return(false);
};
//******************************************************************************************************************************************************************************************************
//                                                              S O U N D I N V E R S E D C T 
//******************************************************************************************************************************************************************************************************
template<class _tg,class _ta> class _tonfunktioninversedct{
};


//******************************************************************************************************************************************************************************************************
//                                                              S O U N D C H A N N E L 
//******************************************************************************************************************************************************************************************************
template<class _tg,class _ta> 
class _tonkanal:
public _listenknotenbasis<_tonkanal<_tg,_ta> >,
public _listebasis<_tonwelle<_tg,_ta> >,
public _listebasis<_tondaten<_tg,_ta> >,
public _listebasis<_tonmodifikationbuffer<_tg,_ta> >{
        using _listebasis<_tonwelle<_tg,_ta> >::anfang;
        using _listebasis<_tonwelle<_tg,_ta> >::naechstes;
        using _listebasis<_tonwelle<_tg,_ta> >::vorheriges;
        using _listebasis<_tondaten<_tg,_ta> >::anfang;
        using _listebasis<_tondaten<_tg,_ta> >::naechstes;
        using _listebasis<_tondaten<_tg,_ta> >::vorheriges;
        using _listebasis<_tonmodifikationbuffer<_tg,_ta> >::anfang;
        using _listebasis<_tonmodifikationbuffer<_tg,_ta> >::naechstes;
        using _listebasis<_tonmodifikationbuffer<_tg,_ta> >::vorheriges;
        public:
                _tonkanal(_listebasis<_tonkanal<_tg,_ta> >*);
                virtual ~_tonkanal();
                void loeschen();
                void modify();
                void clip();
                void erzeugen(const unsigned int,const unsigned int);
                _tonbuffer<_tg,_ta>*buffer();
                void synthesize(const unsigned int rate);
        private:
                _tonbuffer<_tg,_ta>*pchannelbuffer;
};
template<class _tg,class _ta> 
_tonkanal<_tg,_ta>::_tonkanal(_listebasis<_tonkanal<_tg,_ta> >*l):_listenknotenbasis<_tonkanal<_tg,_ta> >(l){
                                                                pchannelbuffer=0;
};
template<class _tg,class _ta> 
_tonkanal<_tg,_ta>::~_tonkanal(){
                                                                loeschen();
};
template<class _tg,class _ta>
void _tonkanal<_tg,_ta>::loeschen(){
                                                                if(pchannelbuffer){
                                                                 delete pchannelbuffer;
                                                                 pchannelbuffer=0;
                                                                };
};
template<class _tg,class _ta>
void _tonkanal<_tg,_ta>::modify(){
                                                                _tonmodifikationbuffer<_tg,_ta>*sit;
                                                                //------------------
                                                                if(pchannelbuffer){
                                                                 if(anfang(sit))do{
                                                                  sit->bearbeiten(pchannelbuffer);
                                                                 }while(naechstes(sit));
                                                                };
};
template<class _tg,class _ta>
void _tonkanal<_tg,_ta>::clip(){
                                                                if(pchannelbuffer){
                                                                 pchannelbuffer->clip(1);
                                                                };
};
template<class _tg,class _ta>
void _tonkanal<_tg,_ta>::erzeugen(const unsigned int groesse,const unsigned int rate){
                                                                //--------------        
                                                                loeschen();
                                                                if(groesse>0){
                                                                 pchannelbuffer=new _tonbuffer<_tg,_ta>(groesse,rate);
                                                                 pchannelbuffer->zero();
                                                                };
};
template<class _tg,class _ta>
_tonbuffer<_tg,_ta>*_tonkanal<_tg,_ta>::buffer(){
                                                                return(pchannelbuffer);
};
template<class _tg,class _ta>
void _tonkanal<_tg,_ta>::synthesize(const unsigned int rate){
                                                                _tonwelle<_tg,_ta>*wit;        
                                                                _tondaten<_tg,_ta>*sit;
                                                                _tonbuffer<_tg,_ta>*temp;
                                                                _tonbuffer<_tg,_ta>*temp2;
                                                                unsigned int sizemax;
                                                                unsigned int i;
                                                                _tg y;
                                                                _tg buffercount;
                                                                //------------------------------
                                                                //channelwavebuffer und samplewavebuffer erzeugen und dabei tertiäre modifikation durchführen
                                                                //quartiäre modifikation auf channelwave- und channelsample buffer durchführen
                                                                if(anfang(wit))do{
                                                                 wit->synthesize(rate);
                                                                }while(naechstes(wit));
                                                                if(anfang(sit))do{
                                                                 sit->synthesize(rate);
                                                                }while(naechstes(sit));
                                                                //channelfunktionsbuffer miteinander verrechnen und
                                                                //anschließend das ergebnis mit den haupt channelbuffer verrechnen
                                                                //maximale funktionsbuffergröße des kanals ermitteln
                                                                //und temp buffer anlegen
                                                                buffercount=0;
                                                                sizemax=0;
                                                                if(anfang(wit))do{
                                                                 if(wit->groesse()>0){
                                                                  if(wit->groesse()>sizemax) sizemax=wit->groesse();
                                                                  buffercount+=1;
                                                                 };
                                                                }while(naechstes(wit));
                                                                if(anfang(sit))do{
                                                                 if(sit->groesse()>0){
                                                                  if(sit->groesse()>sizemax) sizemax=sit->groesse();
                                                                  buffercount+=1;
                                                                 };
                                                                }while(naechstes(sit));
                                                                if(sizemax!=0){
                                                                 temp=new _tonbuffer<_tg,_ta>(sizemax,rate);
                                                                 //channelfunktionsbuffer in temp buffer übertragen
                                                                 for(i=0;i<sizemax;i++){
                                                                  y=0;
                                                                  if(anfang(wit))do{
                                                                   if(wit->groesse()>0){
                                                                    y+=wit->holen(i);
                                                                   };
                                                                  }while(naechstes(wit));
                                                                  if(anfang(sit))do{
                                                                   if(sit->groesse()>0){
                                                                    y+=sit->holen(i);
                                                                   };
                                                                  }while(naechstes(sit));
                                                                  if(buffercount>0){
                                                                   y=y/buffercount;
                                                                   temp->setzen(i,y);
                                                                  };
                                                                 };
                                                                 //temp buffer in den kanalbuffer per addition übertragen
                                                                 if(temp->groesse()<=buffer()->groesse()){
                                                                  for(i=0;i<temp->groesse();i++){
                                                                   y=buffer()->holen(i) + temp->holen(i);
                                                                   buffer()->setzen(i,y);
                                                                  };
                                                                 }else{
                                                                  //vorher den kanalbuffer in temp2 sichern, kanalbuffermit neuer größe anlegen
                                                                  //und kanalbuffer=temp+temp2 durchführen
                                                                  temp2=new _tonbuffer<_tg,_ta>(buffer());
                                                                  loeschen();
                                                                  erzeugen(temp->groesse(),rate);
                                                                  for(i=0;i<temp->groesse();i++){
                                                                   y=temp2->holen(i) + temp->holen(i);
                                                                   buffer()->setzen(i,y);
                                                                  };
                                                                  delete temp2;
                                                                  temp2=0;
                                                                 };
                                                                 delete temp;
                                                                 temp=0;
                                                                };
                                                                
                                                                //channelwavebuffer löschen
                                                                if(anfang(wit))do{
                                                                 wit->_tonbuffer<_tg,_ta>::loeschen();
                                                                }while(naechstes(wit));
                                                                //channelsamplebuffer löschen
                                                                if(anfang(sit))do{
                                                                 sit->_tonbuffer<_tg,_ta>::loeschen();
                                                                }while(naechstes(sit));
                                                                //quintäre modifikationen auf den channelbuffer durchführen
                                                                modify();
};                                                  

//******************************************************************************************************************************************************************************************************
//                                                              S O U N D 
//******************************************************************************************************************************************************************************************************
template<class _tg,class _ta> class _tonton:
public _listebasis<_tonwelle<_tg,_ta> >,              // basisfunktionen
public _listebasis<_tondaten<_tg,_ta> >,              // basisfunktionen
public _listebasis<_tonkanal<_tg,_ta> >,                   // kanäle mit ihren buffern
public _listebasis<_tonmodifikationkanal<_tg,_ta> >,       // sextäre modifikationsliste
public _listenknotenbasis<_tonton<_tg,_ta> >                   // knoten
{
        using _listebasis<_tonwelle<_tg,_ta> >::anfang;
        using _listebasis<_tonwelle<_tg,_ta> >::naechstes;
        using _listebasis<_tonwelle<_tg,_ta> >::vorheriges;
        using _listebasis<_tondaten<_tg,_ta> >::anfang;
        using _listebasis<_tondaten<_tg,_ta> >::naechstes;
        using _listebasis<_tondaten<_tg,_ta> >::vorheriges;
        using _listebasis<_tonkanal<_tg,_ta> >::anfang;
        using _listebasis<_tonkanal<_tg,_ta> >::naechstes;
        using _listebasis<_tonkanal<_tg,_ta> >::vorheriges;
        using _listebasis<_tonmodifikationkanal<_tg,_ta> >::anfang;
        using _listebasis<_tonmodifikationkanal<_tg,_ta> >::naechstes;
        using _listebasis<_tonmodifikationkanal<_tg,_ta> >::vorheriges;
        public:
                _tonton(_zeichenkette<char>,_listebasis<_tonton<_tg,_ta> >*);
                virtual ~_tonton();
                void loeschen();
                void ort(const _vektor<_tg>&);
                _vektor<_tg> ort() const;
                void synthesize(const unsigned int);
                void clearbufferall();
                void clearbufferfunctionwave();
                void savestructure();
        private:
                _vektor<_tg> plocus;
                _zeichenkette<char> pname;
                _datei pfile;                     // die datenstruktur des sound speichern

};
template<class _tg,class _ta> 
_tonton<_tg,_ta>::_tonton(_zeichenkette<char> f,_listebasis<_tonton<_tg,_ta> >*l):_listenknotenbasis<_tonton<_tg,_ta> >(l),pfile(f){
                                                                pname="sound";
                                                                plocus.setzen(0,0,0);
};
template<class _tg,class _ta>
_tonton<_tg,_ta>::~_tonton(){
                                                                clearbufferall();
};
template<class _tg,class _ta>
void _tonton<_tg,_ta>::clearbufferall(){
};
template<class _tg,class _ta>
void _tonton<_tg,_ta>::ort(const _vektor<_tg>&o){
                                                                plocus=o;
};
template<class _tg,class _ta>
_vektor<_tg> _tonton<_tg,_ta>::ort() const{
                                                                return(plocus);
};
template<class _tg,class _ta>
void _tonton<_tg,_ta>::synthesize(const unsigned int rate){
                                                                _tonwelle<_tg,_ta>*wit;        
                                                                _tondaten<_tg,_ta>*sit;
                                                                _tonkanal<_tg,_ta>*cit;
                                                                _tonmodifikationkanal<_tg,_ta>*cmit;
                                                                unsigned int sizemax;
                                                                unsigned int i;
                                                                _tg y;
                                                                _tg buffercount;
                                                                //--------------------------
                                                                //functionsbuffer erzeugen, dabei primäre modifikation durchführen 
                                                                //sekundäre modifikation auf primäre wave und sample  buffer durchführen
                                                                if(anfang(wit))do{
                                                                 wit->synthesize(rate);
                                                                }while(naechstes(wit));
                                                                if(anfang(sit))do{
                                                                 sit->synthesize(rate);
                                                                }while(naechstes(sit));
                                                                //primäre functionwavebuffer miteinander verrechnen und
                                                                //in die channelbuffer übertragen
                                                                //maximale buffergröße ermitteln
                                                                sizemax=0;
                                                                buffercount=0;
                                                                if(anfang(wit))do{//wave buffer 
                                                                 if(wit->groesse()>0){
                                                                  if(wit->groesse()>sizemax) sizemax=wit->groesse();
                                                                  buffercount+=1;
                                                                 };
                                                                }while(naechstes(wit));
                                                                if(anfang(sit))do{//sample buffer
                                                                 if(sit->groesse()>0){
                                                                  if(sit->groesse()>sizemax) sizemax=sit->groesse();
                                                                  buffercount+=1;
                                                                 };
                                                                }while(naechstes(sit));
                                                                //für jeden soundchannel einen buffer
                                                                //mit der vorherermittelten sizemax anlegen
                                                                if(anfang(cit))do{
                                                                 cit->erzeugen(sizemax,rate);
                                                                }while(naechstes(cit));
                                                                //prim. wavebuffer und sampleuffer in die 
                                                                //kanalbuffer übertragen
                                                                for(i=0;i<sizemax;i++){
                                                                 if(anfang(cit))do{
                                                                  y=0;
                                                                  if(anfang(wit))do{//wave buffer
                                                                   if(wit->groesse()>0){
                                                                    y+=wit->holen(i);
                                                                   };
                                                                  }while(naechstes(wit));
                                                                  if(anfang(sit))do{//sample buffer
                                                                   if(sit->groesse()>0){
                                                                    y+=sit->holen(i);
                                                                   };
                                                                  }while(naechstes(sit));
                                                                  if(buffercount>0){
                                                                   y=y/buffercount;
                                                                   cit->buffer()->setzen(i,y);
                                                                  };
                                                                 }while(naechstes(cit));
                                                                };
                                                                //prim. wavebuffer löschen
                                                                if(anfang(wit))do{
                                                                 wit->_tonbuffer<_tg,_ta>::loeschen();
                                                                }while(naechstes(wit));
                                                                //prim. samplebuffer löschen
                                                                if(anfang(sit))do{
                                                                 sit->_tonbuffer<_tg,_ta>::loeschen();
                                                                }while(naechstes(sit));
                                                                //kanalsynthese durchführen
                                                                if(anfang(cit))do{
                                                                 cit->synthesize(rate);
                                                                }while(naechstes(cit));
                                                                //sextäre modifikationen auf alle channelbuffer durchführen
                                                                if(anfang(cmit))do{
                                                                 cmit->bearbeiten();
                                                                }while(naechstes(cmit));
                                                                //und alle kanalbuffer sauber clippen
                                                                if(anfang(cit))do{
                                                                 cit->clip();
                                                                }while(naechstes(cit));
                                                                //synthese beendet
};
template<class _tg,class _ta>
void _tonton<_tg,_ta>::clearbufferfunctionwave(){                                                                
                                                                //funktionsbuffer löschen 
                                                                if(anfang(wit))do{
                                                                 wit->clearbufferwave();
                                                                }while(naechstes(wit));
                                                                
                                                                
};
template<class _tg,class _ta>
void _tonton<_tg,_ta>::savestructure(){
                                                                //nutzt pfile
                                                                //!!!!!!!!!!!!!!!!!!!!!!!!!
                                                                
};
//******************************************************************************************************************************************************************************************************
//                                                              S O U N D W A V 
//******************************************************************************************************************************************************************************************************
template<class _tg,class _ta> class _tonwav:public _tonton<_tg,_ta>,public _datei{
        public:
                _tonwav(_zeichenkette<char>,_zeichenkette<char>,_listebasis<_tonton<_tg,_ta> >*);
                virtual ~_tonwav();
                void savebuffer();     
                void bindbuffertochannel(_zeichenkette<char>);
                void bindbuffertomainwave(_zeichenkette<char>);
};
template<class _tg,class _ta> 
_tonwav<_tg,_ta>::_tonwav(_zeichenkette<char> fwav,_zeichenkette<char> f,_listebasis<_tonton<_tg,_ta> >*l):_tonton<_tg,_ta>(f,l),_datei(fwav){
};
template<class _tg,class _ta>
_tonwav<_tg,_ta>::~_tonwav(){
};
template<class _tg,class _ta>
void _tonwav<_tg,_ta>::savebuffer(){
                                                                _tonbuffer<_tg,_ta>*buffer;
                                                                _tonkanal<_tg,_ta>*cit;
                                                                _tg yoffset;
                                                                unsigned int i;
                                                                _ta*temp;
                                                                unsigned char h[44];
                                                                unsigned int rate;
                                                                unsigned int kanaele;
                                                                unsigned int sizemax;
                                                                unsigned int buffercount;
                                                                unsigned int offset;
                                                                unsigned int sota;
                                                                //-----------------------------------
                                                                if(anfang(cit)){
                                                                 sizemax=0;
                                                                 buffercount=0;
                                                                 if(anfang(cit))do{
                                                                  if(cit->buffer()){
                                                                   if(sizemax<cit->buffer()->groesse()) sizemax=cit->buffer()->groesse();
                                                                   buffercount++;
                                                                   rate=cit->buffer()->rate();
                                                                  };
                                                                 }while(naechstes(cit));
                                                                 kanaele=_listebasis<_tonkanal<_tg,_ta> >::anzahl();
                                                                 sota=sizeof(_ta);
                                                                 h[0]='R';
                                                                 h[1]='I';
                                                                 h[2]='F';
                                                                 h[3]='F';
                                                                 h[4]=((44+sizemax*kanaele*sota)&0x000000ff);
                                                                 h[5]=((44+sizemax*kanaele*sota)&0x0000ff00)>>8;
                                                                 h[6]=((44+sizemax*kanaele*sota)&0x00ff0000)>>16;
                                                                 h[7]=((44+sizemax*kanaele*sota)&0xff000000)>>24;
                                                                 h[8]='W';
                                                                 h[9]='A';
                                                                 h[10]='V';
                                                                 h[11]='E';
                                                                 h[12]='f';
                                                                 h[13]='m';
                                                                 h[14]='t';
                                                                 h[15]=32;//leerzeichen
                                                                 h[16]=16;//fmtchunk-groesse
                                                                 h[17]=0;
                                                                 h[18]=0;
                                                                 h[19]=0;
                                                                 h[20]=1;//kanaele;//fmt-tag (mono=1,stereo =2 ???)
                                                                 h[21]=0;
                                                                 h[22]=kanaele;//kanalanzahl
                                                                 h[23]=0;
                                                                 h[24]=(rate&0x000000ff)>>0;//sample rate
                                                                 h[25]=(rate&0x0000ff00)>>8;
                                                                 h[26]=(rate&0x00ff0000)>>16;
                                                                 h[27]=(rate&0xff000000)>>24;
                                                                 h[28]=((rate*kanaele*sota)&0x000000ff)>>0;//byte pro sec
                                                                 h[29]=((rate*kanaele*sota)&0x0000ff00)>>8;
                                                                 h[30]=((rate*kanaele*sota)&0x00ff0000)>>16;
                                                                 h[31]=((rate*kanaele*sota)&0xff000000)>>24;
                                                                 h[32]=kanaele* sota;//byte pro sample
                                                                 h[33]=0;
                                                                 h[34]=sota*8;//bits pro sample
                                                                 h[35]=0;
                                                                 h[36]='d';
                                                                 h[37]='a';
                                                                 h[38]='t';
                                                                 h[39]='a';
                                                                 h[40]=((sizemax*kanaele*sota)&0x000000ff)>>0;
                                                                 h[41]=((sizemax*kanaele*sota)&0x0000ff00)>>8;
                                                                 h[42]=((sizemax*kanaele*sota)&0x00ff0000)>>16;
                                                                 h[43]=((sizemax*kanaele*sota)&0xff000000)>>24;
                                                                 //------------------
                                                                 if(oeffnen()){
                                                                  _datei::loeschen();
                                                                  speichern(h,44);
                                                                  temp=new _ta[sizemax*kanaele];
                                                                  if(sota==1){
                                                                   yoffset=(1<<(sota*8-1));
                                                                  }else{
                                                                   yoffset=0;
                                                                  };
                                                                  for(i=0;i<sizemax;i++){
                                                                   offset=0;
                                                                   if(anfang(cit))do{
                                                                    buffer=cit->buffer();
                                                                    if(buffer){
                                                                     temp[i*kanaele+offset]=(_ta)(yoffset+buffer->holen(i)*_tg((1<<(sota*8-1))-1));
                                                                    }else{
                                                                     temp[i*kanaele+offset]=(_ta)(yoffset);
                                                                    };
                                                                    offset++;
                                                                   }while(naechstes(cit));
                                                                  };
                                                                  speichern((unsigned char*)temp,sizemax*kanaele*sota);
                                                                  schliessen();
                                                                  delete[] temp;
                                                                 };
                                                                 
                                                                };
                                                                
};
template<class _tg,class _ta>
void _tonwav<_tg,_ta>::bindbuffertomainwave(_zeichenkette<char> datei){
                                                                
};
template<class _tg,class _ta>
void _tonwav<_tg,_ta>::bindbuffertochannel(_zeichenkette<char> datei){
};
//******************************************************************************************************************************************************************************************************
//                                                              S O U N D M O D I F I C A T I O N 
//******************************************************************************************************************************************************************************************************
template<class _tg,class _ta> class _tonmodifikation/*:public _listenknotenbasis<_tonmodifikation<_tg,_ta> >*/{
        public:
                _tonmodifikation(/*_listebasis<_tonmodifikation<_tg,_ta> >* */);
           //     _tonmodifikation();
                virtual ~_tonmodifikation();
                //virtual char bearbeiten()=0;
        protected:
                void schreiben(_zeichenkette<char>);
                void schreiben(_zeichenkette<char>,int);
                void schreiben(_zeichenkette<char>,_tg);
                void schreiben(_zeichenkette<char>,_zeichenkette<char>);
                void schreiben(_zeichenkette<char>,_vektor<_tg>);
                void fehler(_zeichenkette<char>);
                void fehler(_zeichenkette<char>,_zeichenkette<char>);
                void fehler(_zeichenkette<char>,int);
                void fehler(_zeichenkette<char>,_tg);
                void fehler(_zeichenkette<char>,_vektor<_tg>);
};
template<class _tg,class _ta> _tonmodifikation<_tg,_ta>::_tonmodifikation(/*_listebasis<_tonmodifikation<_tg,_ta> >*l*/)/*:_listenknotenbasis<_tonmodifikation<_tg,_ta> >(l)*/{
};
/*template<class _tg,class _ta> _tonmodifikation<_tg,_ta>::_tonmodifikation():_listenknotenbasis<_tonmodifikation<_tg,_ta> >(){
};*/
template<class _tg,class _ta> _tonmodifikation<_tg,_ta>::~_tonmodifikation(){
};
template<class _tg,class _ta> void _tonmodifikation<_tg,_ta>::schreiben(_zeichenkette<char> m0){
                                                                L->schreiben(m0);
};
template<class _tg,class _ta> void _tonmodifikation<_tg,_ta>::schreiben(_zeichenkette<char> m0,_zeichenkette<char> m1){
                                                                L->schreiben(m0,m1);
};
template<class _tg,class _ta> void _tonmodifikation<_tg,_ta>::schreiben(_zeichenkette<char> m0,int i0){
                                                                L->schreiben(m0,i0);
};
template<class _tg,class _ta> void _tonmodifikation<_tg,_ta>::schreiben(_zeichenkette<char> m0,_tg g){
                                                                L->schreiben(m0,g);
};
template<class _tg,class _ta> void _tonmodifikation<_tg,_ta>::schreiben(_zeichenkette<char> m0,_vektor<_tg> v){
                                                                L->schreiben(m0,v);
};
template<class _tg,class _ta> void _tonmodifikation<_tg,_ta>::fehler(_zeichenkette<char> m0){
                                                                L->fehler(m0);
};
template<class _tg,class _ta> void _tonmodifikation<_tg,_ta>::fehler(_zeichenkette<char> m0,_zeichenkette<char> m1){
                                                                L->fehler(m0,m1);
};
template<class _tg,class _ta> void _tonmodifikation<_tg,_ta>::fehler(_zeichenkette<char> m0,int i0){
                                                                L->fehler(m0,i0);
};
template<class _tg,class _ta> void _tonmodifikation<_tg,_ta>::fehler(_zeichenkette<char> m0,_tg g){
                                                                L->fehler(m0,g);
};
template<class _tg,class _ta> void _tonmodifikation<_tg,_ta>::fehler(_zeichenkette<char> m0,_vektor<_tg> i0){
                                                                L->fehler(m0,i0);
};
//******************************************************************************************************************************************************************************************************
//                                                              S O U N D M O D I F I C A T I O N C U R V E  (erste und dritte Modifikation, kurvenmodifikation)
//******************************************************************************************************************************************************************************************************
template<class _tg,class _ta> class _tonmodifikationkurve:public _tonmodifikation<_tg,_ta>{
        public:
                _tonmodifikationkurve(_tonkurvehermite<_tg,_ta>*);
                _tonmodifikationkurve(_tonkurvehermite<_tg,_ta>*,_tonmodifikationkurve<_tg,_ta>*);
                virtual ~_tonmodifikationkurve();
                void resetiterator();
                void savecurve();
                char bearbeiten();
                void restorecurve()const;
                void createbuffer(const unsigned int,const unsigned int);
                void clearbuffer();
                _tonfunktion<_tg,_ta>*functionlocus (const unsigned int);
                _tonfunktion<_tg,_ta>*functionvector(const unsigned int);
                void cycliclocus(const unsigned int,const bool);
                void cyclicvector(const unsigned int,const bool);
        private:
                _tonkurvehermite<_tg,_ta>*pcurve;         //hermite-kurven modifikation
                _tonfunktion<_tg,_ta> plocus0;
                _tonfunktion<_tg,_ta> plocus1;
                _tonfunktion<_tg,_ta> pvector0;
                _tonfunktion<_tg,_ta> pvector1;
                unsigned int itlocus0;
                unsigned int itlocus1;
                unsigned int itvector0;
                unsigned int itvector1;
                bool plocuscyclic[2];
                bool pvectorcyclic[2];
                _vektor<_tg> prclocus0;
                _vektor<_tg> prclocus1;
                _vektor<_tg> prcvector0;
                _vektor<_tg> prcvector1;
};
template<class _tg,class _ta> 
_tonmodifikationkurve<_tg,_ta>::_tonmodifikationkurve(_tonkurvehermite<_tg,_ta>*c){
                                                                pcurve=c;
                                                                pcurve->pmodificationcurve=this;
                                                                plocuscyclic[0]=true;
                                                                plocuscyclic[1]=true;
                                                                pvectorcyclic[0]=true;
                                                                pvectorcyclic[1]=true;
                                                                resetiterator();
};
template<class _tg,class _ta> 
_tonmodifikationkurve<_tg,_ta>::_tonmodifikationkurve(_tonkurvehermite<_tg,_ta>*c,_tonmodifikationkurve<_tg,_ta>*n){
                                                                pcurve=c;
                                                                pcurve->pmodificationcurve=this;
                                                                plocus0.kopieren(&n->plocus0);
                                                                plocus1.kopieren(&n->plocus1);
                                                                pvector0.kopieren(&n->pvector0);
                                                                pvector1.kopieren(&n->pvector1);
                                                                plocuscyclic[0]=n->plocuscyclic[0];
                                                                plocuscyclic[1]=n->plocuscyclic[1];
                                                                pvectorcyclic[0]=n->pvectorcyclic[0];
                                                                pvectorcyclic[1]=n->pvectorcyclic[1];
                                                                resetiterator();
};
template<class _tg,class _ta> 
_tonmodifikationkurve<_tg,_ta>::~_tonmodifikationkurve(){
                                                                clearbuffer();
};
template<class _tg,class _ta> 
void _tonmodifikationkurve<_tg,_ta>::resetiterator(){
                                                                itlocus0=0;
                                                                itlocus1=0;
                                                                itvector0=0;
                                                                itvector1=0;
                                                                savecurve();
};
template<class _tg,class _ta> 
void _tonmodifikationkurve<_tg,_ta>::savecurve(){
                                                                prclocus0=pcurve->ort(0);
                                                                prclocus1=pcurve->ort(1);
                                                                prcvector0=pcurve->vektor(0);
                                                                prcvector1=pcurve->vektor(1);
};
template<class _tg,class _ta> 
char _tonmodifikationkurve<_tg,_ta>::bearbeiten(){
                                                                _tg x,y;
                                                                _vektor<_tg> h;
                                                                unsigned int s;
                                                                //------------------
                                                                if(plocus0.buffer(0)){//ort 0 modification
                                                                 x=plocus0.buffer(0)->holen(itlocus0);
                                                                 y=plocus0.buffer(1)->holen(itlocus0);
                                                                 h=pcurve->ort(0);
                                                                 h.setzen(x,y,h[2]);
                                                                 pcurve->ort(0,h);
                                                                 s=plocus0.buffer(0)->groesse();
                                                                 itlocus0++;
                                                                 if(plocuscyclic[0]==true){
                                                                  while(itlocus0>=s) itlocus0-=s;
                                                                 }else{
                                                                  if(itlocus0>=s) itlocus0=s-1;
                                                                 };
                                                                };
                                                                if(plocus1.buffer(0)){//ort 1 modification
                                                                 x=plocus1.buffer(0)->holen(itlocus1);
                                                                 y=plocus1.buffer(1)->holen(itlocus1);
                                                                 h=pcurve->ort(1);
                                                                 h.setzen(x,y,h[2]);
                                                                 pcurve->ort(1,h);
                                                                 s=plocus1.buffer(0)->groesse();
                                                        //   L->schreiben("buffersize = ",(int)s);
                                                        //   L->schreiben("iterator   = ",(int)itlocus1);
                                                        //   L->schreiben("x  = ",x);
                                                                 itlocus1++;
                                                                 if(plocuscyclic[1]==true){
                                                                  while(itlocus1>=s) itlocus1-=s;
                                                                 }else{
                                                                  if(itlocus1>=s) itlocus1=s-1;
                                                                 };
                                                                };
                                                                if(pvector0.buffer(0)){//vektor 0 modification
                                                                 x=pvector0.buffer(0)->holen(itvector0);
                                                                 y=pvector0.buffer(1)->holen(itvector0);
                                                                 h=pcurve->vektor(0);
                                                                 h.setzen(x,y,h[2]);
                                                                 pcurve->vektor(0,h);
                                                                 s=pvector0.buffer(0)->groesse();
                                                                 itvector0++;
                                                                 if(pvectorcyclic[0]==true){
                                                                  while(itvector0>=s) itvector0-=s;
                                                                 }else{
                                                                  if(itvector0>=s) itvector0=s-1;
                                                                 };
                                                                };
                                                                if(pvector1.buffer(0)){//vektor 1 modification
                                                                 x=pvector1.buffer(0)->holen(itvector1);
                                                                 y=pvector1.buffer(1)->holen(itvector1);
                                                                 h=pcurve->vektor(1);
                                                                 h.setzen(x,y,h[2]);
                                                                 pcurve->vektor(1,h);
                                                                 s=pvector1.buffer(0)->groesse();
                                                                 itvector1++;
                                                                 if(pvectorcyclic[1]==true){
                                                                  while(itvector1>=s) itvector1-=s;
                                                                 }else{
                                                                  if(itvector1>=s) itvector1=s-1;
                                                                 };
                                                                };
                                                                //******************* DEBUG *********************
                                                                //_win::_pclautsprecher ss;
                                                                //ss.peep(1);
                                                                //***********************************************
                                                                return(1);
};
template<class _tg,class _ta> 
void _tonmodifikationkurve<_tg,_ta>::restorecurve()const{
                                                                pcurve->ort(0)=prclocus0;
                                                                pcurve->ort(1)=prclocus1;
                                                                pcurve->vektor(0)=prcvector0;
                                                                pcurve->vektor(1)=prcvector1;
};
template<class _tg,class _ta> 
void _tonmodifikationkurve<_tg,_ta>::createbuffer(const unsigned int rate,const unsigned int tres){
                                                                plocus0.createbuffer(rate,tres);
                                                                plocus1.createbuffer(rate,tres);
                                                                pvector0.createbuffer(rate,tres);
                                                                pvector1.createbuffer(rate,tres);
};
template<class _tg,class _ta> 
void _tonmodifikationkurve<_tg,_ta>::clearbuffer(){
                                                                plocus0.clearbuffer();
                                                                plocus1.clearbuffer();
                                                                pvector0.clearbuffer();
                                                                pvector1.clearbuffer();
};
template<class _tg,class _ta> 
_tonfunktion<_tg,_ta>*_tonmodifikationkurve<_tg,_ta>::functionlocus (const unsigned int i){
                                                                if(i==0) return(&plocus0); else return(&plocus1);
};
template<class _tg,class _ta> 
_tonfunktion<_tg,_ta>*_tonmodifikationkurve<_tg,_ta>::functionvector(const unsigned int i){
                                                                if(i==0) return(&pvector0); else return(&pvector1);
};
template<class _tg,class _ta> 
void _tonmodifikationkurve<_tg,_ta>::cycliclocus (const unsigned int i,const bool b){
                                                                if(i==0){
                                                                 plocuscyclic[0]=b;
                                                                }else{
                                                                 if(i==1){
                                                                  plocuscyclic[1]=b;
                                                                 };
                                                                };
};
template<class _tg,class _ta> 
void _tonmodifikationkurve<_tg,_ta>::cyclicvector(const unsigned int i,const bool b){
                                                                if(i==0){
                                                                 pvectorcyclic[0]=b;
                                                                }else{
                                                                 if(i==1){
                                                                  pvectorcyclic[1]=b;
                                                                 };
                                                                };
};
//******************************************************************************************************************************************************************************************************
//                                                              S O U N D M O D I F I C A T I O N B U F F E R (zweite, vierte und fünfte Modifikation,buffermodifikation)
//******************************************************************************************************************************************************************************************************
template<class _tg,class _ta> class _tonmodifikationbuffer:public _tonmodifikation<_tg,_ta>,public _listenknotenbasis<_tonmodifikationbuffer<_tg,_ta> >{
        public:
                _tonmodifikationbuffer(_tonwelle<_tg,_ta>*);
                _tonmodifikationbuffer(_tonkanal<_tg,_ta>*);
                virtual ~_tonmodifikationbuffer();
                virtual void bearbeiten(_tonbuffer<_tg,_ta>*)=0;
                
        private:
                _tonwelle<_tg,_ta>*pwave;              //resultbuffer modification
                _tonkanal<_tg,_ta>*pchannel;                //channelbuffer modifikation
};
template<class _tg,class _ta> 
_tonmodifikationbuffer<_tg,_ta>::_tonmodifikationbuffer(_tonwelle<_tg,_ta>*w):_listenknotenbasis<_tonmodifikationbuffer<_tg,_ta> >(w){
                                                                pwave=w;
                                                                pchannel=0;
};
template<class _tg,class _ta> 
_tonmodifikationbuffer<_tg,_ta>::_tonmodifikationbuffer(_tonkanal<_tg,_ta>*c):_listenknotenbasis<_tonmodifikationbuffer<_tg,_ta> >(c){
                                                                pwave=0;
                                                                pchannel=c;
};
template<class _tg,class _ta> 
_tonmodifikationbuffer<_tg,_ta>::~_tonmodifikationbuffer(){
};
//******************************************************************************************************************************************************************************************************
//                                                              S O U N D M O D I F I C A T I O N B U F F E R N O R M A L I Z E 
//******************************************************************************************************************************************************************************************************
template<class _tg,class _ta>class _tonmodifikationbuffernormalisieren:public _tonmodifikationbuffer<_tg,_ta>{
        public:
                _tonmodifikationbuffernormalisieren(_tonwelle<_tg,_ta>*);
                _tonmodifikationbuffernormalisieren(_tonkanal<_tg,_ta>*);
                virtual ~_tonmodifikationbuffernormalisieren();
                _tg intensitaet()const;
                void intensitaet(const _tg);
                void bearbeiten(_tonbuffer<_tg,_ta>*);
        private:
                _tg plevel;
};
template<class _tg,class _ta> 
_tonmodifikationbuffernormalisieren<_tg,_ta>::_tonmodifikationbuffernormalisieren(_tonwelle<_tg,_ta>*w):_tonmodifikationbuffer<_tg,_ta>(w){
                                                                plevel=1;
};
template<class _tg,class _ta> 
_tonmodifikationbuffernormalisieren<_tg,_ta>::_tonmodifikationbuffernormalisieren(_tonkanal<_tg,_ta>*c):_tonmodifikationbuffer<_tg,_ta>(c){
                                                                plevel=1;
};
template<class _tg,class _ta> 
_tonmodifikationbuffernormalisieren<_tg,_ta>::~_tonmodifikationbuffernormalisieren(){
};
template<class _tg,class _ta> 
void _tonmodifikationbuffernormalisieren<_tg,_ta>::intensitaet(const _tg l){
                                                                _tg ll;
                                                                //---------
                                                                if(l<0) ll=-l; else ll=l;
                                                                if(ll>1) ll=1;
                                                                plevel=ll;
};
template<class _tg,class _ta> 
_tg _tonmodifikationbuffernormalisieren<_tg,_ta>::intensitaet()const{
                                                                return(plevel);
};
template<class _tg,class _ta> 
void _tonmodifikationbuffernormalisieren<_tg,_ta>::bearbeiten(_tonbuffer<_tg,_ta>*b){
                                                                _tg min;
                                                                _tg max;
                                                                _tg m;
                                                                _tg factor;
                                                                _tg y;
                                                                unsigned int i;
                                                                unsigned int groesse;
                                                                //------
                                                                max=0;
                                                                min=0;
                                                                groesse=b->groesse();
                                                                for(i=0;i<groesse;i++){
                                                                 y=b->holen(i);
                                                                 if(y>max) max=y;
                                                                 if(y<min) min=y;
                                                                };
                                                                if((max==0)&&(min==0)){
                                                                 schreiben("void _tonmodifikationbuffernormalisieren<_tg,_ta>::bearbeiten(_tonbuffer<_tg,_ta>*b) : Kann nicht normalisieren, da kein pegel vorhanden ist");
                                                                }else{
                                                                 if(fabs(min)>fabs(max)) m=fabs(min); else m=fabs(max);
                                                                 factor=plevel/m;
                                                                 for(i=0;i<groesse;i++){
                                                                  y=b->holen(i);
                                                                  b->setzen(i,y*factor);
                                                                 };
                                                                };
};
//******************************************************************************************************************************************************************************************************
//                                                              S O U N D M O D I F I C A T I O N B U F F E R N O I S E 
//******************************************************************************************************************************************************************************************************
template<class _tg,class _ta>class _tonmodifikationbufferrauschen:public _tonmodifikationbuffer<_tg,_ta>{
        public:
                _tonmodifikationbufferrauschen(_tonwelle<_tg,_ta>*);
                _tonmodifikationbufferrauschen(_tonkanal<_tg,_ta>*);
                virtual ~_tonmodifikationbufferrauschen();
                _tg intensitaet()const;
                void intensitaet(const _tg);
                _tg frequency()const;
                void frequency(const _tg);
                _tg tolerancevertical()const;
                void tolerancevertical(const _tg);
                _tg tolerancehorizontal()const;
                void tolerancehorizontal(const _tg);
                void bearbeiten(_tonbuffer<_tg,_ta>*);
        private:
                _tg plevel;//mischintensität
                _tg pht;//horizontaltoleranz 
                _tg pfreq;//frequenz 1..50000
                _tg pvt;//vertikaltolerance 0..1
};
template<class _tg,class _ta> 
_tonmodifikationbufferrauschen<_tg,_ta>::_tonmodifikationbufferrauschen(_tonwelle<_tg,_ta>*w):_tonmodifikationbuffer<_tg,_ta>(w){
                                                                plevel=1;
                                                                pht=0.00004;
                                                                pfreq=25;
                                                                pvt=1;
};
template<class _tg,class _ta> 
_tonmodifikationbufferrauschen<_tg,_ta>::_tonmodifikationbufferrauschen(_tonkanal<_tg,_ta>*c):_tonmodifikationbuffer<_tg,_ta>(c){
                                                                plevel=1;
                                                                pht=0.00004;
                                                                pfreq=25;
                                                                pvt=1;
};
template<class _tg,class _ta> 
_tonmodifikationbufferrauschen<_tg,_ta>::~_tonmodifikationbufferrauschen(){
};
template<class _tg,class _ta> 
void _tonmodifikationbufferrauschen<_tg,_ta>::intensitaet(const _tg l){
                                                                _tg ll;
                                                                //---------
                                                                if(l<0) ll=-l; else ll=l;
                                                                if(ll>1) ll=1;
                                                                plevel=ll;
};
template<class _tg,class _ta> 
_tg _tonmodifikationbufferrauschen<_tg,_ta>::intensitaet()const{
                                                                return(plevel);
};
template<class _tg,class _ta> 
void _tonmodifikationbufferrauschen<_tg,_ta>::frequency(const _tg l){
                                                                if(l<50000) pfreq=l; else pfreq=50000;
};
template<class _tg,class _ta> 
_tg _tonmodifikationbufferrauschen<_tg,_ta>::frequency()const{
                                                                return(pfreq);
};
template<class _tg,class _ta> 
void _tonmodifikationbufferrauschen<_tg,_ta>::tolerancevertical(const _tg l){
                                                                if((l>=0)&&(l<=1)) pvt=l;
};
template<class _tg,class _ta> 
_tg _tonmodifikationbufferrauschen<_tg,_ta>::tolerancevertical()const{
                                                                return(pvt);
};
template<class _tg,class _ta> 
void _tonmodifikationbufferrauschen<_tg,_ta>::tolerancehorizontal(const _tg l){
                                                                if((l>=0)&&(l<=1)) pht=l;
};
template<class _tg,class _ta> 
_tg _tonmodifikationbufferrauschen<_tg,_ta>::tolerancehorizontal()const{
                                                                return(pht);
};

template<class _tg,class _ta> 
void _tonmodifikationbufferrauschen<_tg,_ta>::bearbeiten(_tonbuffer<_tg,_ta>*bx){
                                                                _tg sx;
                                                                _tg y;
                                                                _tg it;
                                                                _tg pmm;
                                                                _tg dir;
                                                                _tg rmax;
                                                                _tg rmin;
                                                                unsigned int x;
                                                                unsigned int groesse;
                                                                _zufallsgenerator<_tg> r;
                                                                //------
                                                                if(bx){
                                                                 groesse=bx->groesse();
                                                                 it=0;
                                                                 dir=+1;
                                                                 rmax=r.berechnen(0,+1);
                                                                 rmin=r.berechnen(-1,0);
                                                                 pmm=4*pfreq/_tg(bx->rate());
                                                                 //f=r.berechnen(1-pmstreu,1+pmstreu);
                                                                 for(x=0;x<groesse;x++){
                                                                  sx=it;
                                                                  y=bx->holen(x);
                                                                  if(dir==+1){
                                                                   it+=r.berechnen(+pmm-pht,+pmm+pht);
                                                                  }else{
                                                                   it+=r.berechnen(-pmm-pht,-pmm+pht);
                                                                  };
                                                                  if(dir==+1){
                                                                   if(it> rmax){
                                                                    dir=-1;
                                                                    rmax=r.berechnen(-1  +(1-pvt)*2  ,+1);
                                                                    schreiben("rmax=",rmax);
                                                                   };
                                                                  }else{
                                                                   if(dir==-1){
                                                                    if(it< rmin) {
                                                                     dir=+1;
                                                                     rmin=r.berechnen(-1,+1  -(1-pvt)*2  );
                                                                     schreiben("rmin=",rmin);
                                                                    };
                                                                   };
                                                                  };
                                                                  sx=(y*(1-plevel))+(sx*plevel);
                                                                  bx->setzen(x,sx);
                                                                 };
                                                                };
};

//******************************************************************************************************************************************************************************************************
//                                                              S O U N D M O D I F I C A T I O N C H A N N E L (sechste Modifikation, buffermodifikation)
//******************************************************************************************************************************************************************************************************
template<class _tg,class _ta> 
class _tonmodifikationkanal:
public _tonmodifikation<_tg,_ta>,
public _listenknotenbasis<_tonmodifikationkanal<_tg,_ta> >{
        public:
                _tonmodifikationkanal(_tonton<_tg,_ta>*);
                virtual ~_tonmodifikationkanal();
                virtual void bearbeiten()=0;
        protected:
                _tonton<_tg,_ta>*sound();
        private:
                _tonton<_tg,_ta>*psound;                     //channelbuffer modifikation
};
template<class _tg,class _ta> 
_tonmodifikationkanal<_tg,_ta>::_tonmodifikationkanal(_tonton<_tg,_ta>*s):_listenknotenbasis<_tonmodifikationkanal<_tg,_ta> >(s){
                                                                psound=s;
};
template<class _tg,class _ta> 
_tonmodifikationkanal<_tg,_ta>::~_tonmodifikationkanal(){
};
template<class _tg,class _ta> 
_tonton<_tg,_ta>*_tonmodifikationkanal<_tg,_ta>::sound(){
                                                                return(psound);
};
//******************************************************************************************************************************************************************************************************
//                                                              S O U N D M O D I F I A C T I O N C H A N N E L P A N O R A M A 
//******************************************************************************************************************************************************************************************************
template<class _tg,class _ta> 
class _tonmodifikationkanalpanorama:public _tonmodifikationkanal<_tg,_ta>{
        public:
                _tonmodifikationkanalpanorama(_tonton<_tg,_ta>*);
                virtual ~_tonmodifikationkanalpanorama();
                void bearbeiten();
                _tg intensitaet()const;
                void intensitaet(_tg);
                _tg frequency()const;
                void frequency(_tg);
        private:
                _tg pint;
                _tg pfre;
};
template<class _tg,class _ta> 
_tonmodifikationkanalpanorama<_tg,_ta>::_tonmodifikationkanalpanorama(_tonton<_tg,_ta>*s):_tonmodifikationkanal<_tg,_ta>(s){
                                                                pint=1;
                                                                pfre=2;
};
template<class _tg,class _ta> 
_tonmodifikationkanalpanorama<_tg,_ta>::~_tonmodifikationkanalpanorama(){
};
template<class _tg,class _ta> 
void _tonmodifikationkanalpanorama<_tg,_ta>::bearbeiten(){
                                                                unsigned int i;
                                                                unsigned int sizemax;
                                                                unsigned int rate;
                                                                _tg piit;
                                                                _tg offset;
                                                                _tonkanal<_tg,_ta>*cit;
                                                                _tg factor;
                                                                _tg y;
                                                                //--------------
                                                                piit=0;
                                                                sizemax=0;
                                                                if(sound()->anfang(cit))do{
                                                                 if(sizemax<cit->buffer()->groesse()) {
                                                                  sizemax=cit->buffer()->groesse();
                                                                  rate=cit->buffer()->rate();
                                                                 };
                                                                }while(sound()->naechstes(cit));
                                                                if(sizemax>0){
                                                                 for(i=0;i<sizemax;i++){
                                                                  offset=0;
                                                                  if(sound()->anfang(cit))do{
                                                                   if(i<cit->buffer()->groesse()){
                                                                    y=cit->buffer()->holen(i);
                                                                    factor=sin(2*_pi*(piit+offset))*pint*0.5;
                                                                    factor=(1-pint) + pint*0.5 + factor; 
                                                                    y*=factor;
                                                                    cit->buffer()->setzen(i,y);
                                                                   };
                                                                   offset+=0.5;//achtung konstante 
                                                                  }while(sound()->naechstes(cit));
                                                                  piit+=pfre/_tg(rate);
                                                                 };
                                                                };
};
template<class _tg,class _ta> 
_tg _tonmodifikationkanalpanorama<_tg,_ta>::intensitaet()const{
                                                                return(pint);
};
template<class _tg,class _ta> 
void _tonmodifikationkanalpanorama<_tg,_ta>::intensitaet(_tg i){
                                                                if(i<0) i=0;
                                                                if(i>1) i=1;
                                                                pint=i;
};
template<class _tg,class _ta> 
_tg _tonmodifikationkanalpanorama<_tg,_ta>::frequency()const{
                                                                return(pfre);
};
template<class _tg,class _ta> 
void _tonmodifikationkanalpanorama<_tg,_ta>::frequency(_tg f){
                                                                if(f<=0) f=0.00001; 
                                                                pfre=f;
};

#endif
