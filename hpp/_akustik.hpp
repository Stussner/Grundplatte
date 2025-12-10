//******************************************************************************************************************************************************************************************************
//  Projekt     : grundplatte
//  Bibliothek  : _grundplatte.lib
//  Modul       : _akustik.hpp
//  Datum       : 6.9.2008
//******************************************************************************************************************************************************************************************************
#ifndef _akustikh_included
#define _akustikh_included

#include <_global.hpp>
#include <_struktur.hpp>
#include <_vektor.hpp>
#include <_interpolator.hpp>
#include <vector>
class _akustik;
class _tonsammlung;//=pool
class _ton;        //=sample
class _tonfluss;   //=stream


#define NUM_STREAMBUFFERS 2
#define SIZE_STREAMBUFFER (32768*2)  // 64 kb (Editor)
//******************************************************************************************************************************************************************************************************
//                                                                  A K U S T I K 
//******************************************************************************************************************************************************************************************************
class _akustik{
        public:
                _akustik();
                virtual ~_akustik();
                virtual void animieren(_tg seconds)=0;
                virtual _tonsammlung*erzeugentonsammlung(const unsigned int numSources)=0;
                _tonsammlung*tonsammlung(unsigned int);
				void loeschentonlisten();
                //ton parameter
                _tg lautstaerketon()const;
                void lautstaerketon(_tg);
                _tg lautstaerketonfluss()const;
                void lautstaerketonfluss(_tg);
                _tg beugung()const;
                void beugung(_tg);
                _listebasis<_ton>*listeton();
                _listebasis<_tonfluss>*listetonfluss();
                _listebasis<_tonsammlung>*listetonsammlung();
                
                virtual void zuhoererort(const _vektor3<_tg>&pos)=0;
                virtual void zuhoerergeschwindigkeit(const _vektor3<_tg>&vel)=0;
                virtual void zuhoererrichtung(const _vektor3<_tg>&dir, const _vektor3<_tg>&up)=0;
                
                //ton
                virtual _ton*erzeugenton()=0;
                virtual void abspielen(_ton*)=0;
                virtual void abspielen(_ton*,_tg l,_tg b0,_tg b1)=0;
                virtual void abspielen(unsigned int,_ton*,const _vektor3<_tg>&pos,const _vektor3<_tg>&vel,_tg fadeTime=0)=0;
                virtual void anhalten(unsigned int,_ton*,_tg fadeTime=0)=0;
                virtual void stoppen(unsigned int,_ton*,_tg fadeTime=0)=0;
                // Streams
                virtual _tonfluss*erzeugentonfluss()=0;
                virtual void abspielen(_tonfluss*,_tg fadeTime=0)=0;
                virtual void anhalten(_tonfluss*,_tg fadeTime=0)=0;
                virtual void stoppen(_tonfluss*,_tg fadeTime=0)=0;
                 //laufende
                virtual void anhalten(_tg fadeTime=0);
                virtual void fortsetzen(_tg fadeTime=0);
                virtual void stoppen(_tg fadeTime=0);
                virtual void stoppenquellemitbuffer(const unsigned int buffer)=0;                
                
        private:
                void tonsammlungfunktion(void (_tonsammlung::*func)(_tg fadeTime),_tg fadeTime);   
                                            
        private:
                _listebasis<_ton> plisteton;
                _listebasis<_tonfluss> plistetonfluss;
                _listebasis<_tonsammlung> plistetonsammlung;
                _tg plautstaerketon;
                _tg plautstaerketonfluss;
                _tg pbeugung;                        
};
//******************************************************************************************************************************************************************************************************
//                                                                  T O N
//******************************************************************************************************************************************************************************************************
class _ton:public _listenknotenbasis<_ton>{
        public:
                _ton(_akustik*);
                virtual ~_ton();
                _akustik*akustik();
                unsigned int identifikationbuffer()const;   
                void identifikationbuffer(const unsigned int);             
                bool schleife() const;
                void schleife(const bool loop);
                _tg lautstaerke() const;
                void lautstaerke(const _tg volume);
                _tg beugung() const;
                void beugung(_tg pitch);
                virtual bool laden(std::vector<unsigned char> &buffer)=0;
                
                virtual void abspielen();
                virtual void abspielen(_tg l,_tg b0,_tg b1);

        private:
                _akustik*pakustik;
                bool pschleife;
                _tg plautstaerke;
                _tg pbeugung;
                unsigned int pidbuffer;                
};
//******************************************************************************************************************************************************************************************************
//                                                                  T O N F L U S S 
//******************************************************************************************************************************************************************************************************
class _tonfluss:public _ton,public _listenknotenbasis<_tonfluss>{
        public:
                _tonfluss(_akustik*);
                virtual ~_tonfluss();
                virtual unsigned int identifikationquelle()const=0;
                virtual void identifikationquelle(const unsigned int q)=0;
                virtual unsigned int identifikationstream(const unsigned int)const=0;             
                
                virtual bool laden(std::vector<unsigned char>&buffer)=0;
                virtual void animieren(_tg seconds)=0;
                virtual bool spielt()const=0;
                virtual bool angehalten()const=0;    
                virtual void aktiv(const bool)=0;                            
                virtual bool aktiv() const=0;                            
                virtual void schleife(const bool)=0;                            
                virtual bool schleife() const=0;                            
                virtual void fuellenbuffer(unsigned int id)=0;
                  
                
};
//******************************************************************************************************************************************************************************************************
//                                                                  T O N S A M M L U N G 
//******************************************************************************************************************************************************************************************************
class _tonsammlung:public _listenknotenbasis<_tonsammlung>{
        
        public:
                _tonsammlung(_akustik*,unsigned int numSources);
                virtual ~_tonsammlung();
                _akustik*akustik();
                unsigned int anzahlquelle() const;
                unsigned int quelle(unsigned int) const;
                unsigned int*quelle();
                _interpolator<_tg>*interpolator();
                virtual void anhalten(_tg fadeTime)=0;
                virtual void fortsetzen(_tg fadeTime)=0;
                virtual void stoppen(_tg fadeTime)=0;
                
                void ausblendenanhalten(const bool);
                bool ausblendenanhalten()const;
                void ausblendenstoppen(const bool);
                bool ausblendenstoppen()const;
        public:
                virtual unsigned int findenfreiequelle()=0;
                virtual void stoppenquellemitbuffer(unsigned int buffer)=0;
                virtual void lautstaerkespielendequelle(_tg value)=0;
                virtual void animieren(_tg seconds)=0;                 
        private:
                _akustik*pakustik;                
                unsigned int panzahlquelle;
                unsigned int pquelle[32];
                bool pfadetopause;
                bool pfadetostop;
                _interpolatorlinear<_tg> pinterpolator;  
};
/*
'******************************************************************************************************************
'										 G L O B A L   D A T A
'******************************************************************************************************************
Global channelambience:TChannel=AllocChannel()
Global channelmusic:TChannel=AllocChannel()
Global volumeambience#=1'user defined
Global volumesound#=0.4'user defined
Global volumesoundfadein#=0
Global volumemusic#=0.3'user defined
'******************************************************************************************************************
'										 S O U N D  F U N C T I O N S 
'******************************************************************************************************************
Function loadsoundassert:TSound(name$,looped:Int=False)
				Local t:TSound
				t=LoadSound (name,looped)
				Assert t<>Null,"Counld not load "+name+"."
				Return(t)
				EndFunction
				
Function playambiencestretched:TChannel(t:TSound,vol#,stretchmin#,stretchmax#)
				If t
				 Local channel:TChannel=AllocChannel()
				 channel.setvolume(vol*volumeambience*volumesoundfadein)
				 channel.setrate(Rnd(stretchmin,stretchmax))
				 PlaySound(t,channel)
				 Return(channel)
				EndIf
				Return(Null)
				EndFunction
Function Playambiencenormal:TChannel(t:TSound,vol#)
				If t
				 Local channel:TChannel=AllocChannel()
				 channel.setvolume(vol*volumeambience*volumesoundfadein)
				 channel.setrate(1)
				 PlaySound(t,channel)
				 Return(channel)
				EndIf
				Return(Null)
				EndFunction				
				
Function playsoundstretched:TChannel(t:TSound,vol#,stretchmin#,stretchmax#)
				If t
				 Local channel:TChannel=AllocChannel()
				 channel.setvolume(vol*volumesound*volumesoundfadein)
				 channel.setrate(Rnd(stretchmin,stretchmax))
				 PlaySound(t,channel)
				 Return(channel)
				EndIf
				Return(Null)
				EndFunction
Function PlaySoundnormal:TChannel(t:TSound,vol#)
				If t
				 Local channel:TChannel=AllocChannel()
				 channel.setvolume(vol*volumesound*volumesoundfadein)
				 channel.setrate(1)
				 PlaySound(t,channel)
				 Return(channel)
				EndIf
				Return(Null)
				EndFunction
				*/

#endif
