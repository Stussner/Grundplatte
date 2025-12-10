//******************************************************************************************************************************************************************************************************
//  Projekt     : grundplatte
//  Bibliothek  : _grundplatte.lib
//  Modul       : _akustikopenal.hpp
//  Datum       : 6.9.2008
//******************************************************************************************************************************************************************************************************
#ifndef _akustikopenalh_included
#define _akustikopenalh_included
//******************************************************************************************************************************************************************************************************
//                                                                  P R E D E K L A R A T I O N 
//******************************************************************************************************************************************************************************************************
class _tonopenal;
class _tonflussopenal;
class _tonsammlungopenal;
class _musikeintrag;
class _musikverwaltung;

#include <_akustik.hpp>
#include <_system.hpp>
#include <_funktion.hpp>
#include <sound\openal\al.h>
#include <sound\openal\alc.h>
#include <sound\openal\alut.h>

#include <sound\Vorbis\vorbisfile.h>
//******************************************************************************************************************************************************************************************************
//                                                                  S T R U K T U R O G G V O R B I S
//******************************************************************************************************************************************************************************************************
struct _strukturoggvorbis{
                char    *dataPtr;   // Pointer to the data in memory
                size_t  dataSize;   // Size of the data
                size_t  dataRead;   // How much data we have read so far
};
//******************************************************************************************************************************************************************************************************
//                                                                  D A T E I O G G V O R B I S
//******************************************************************************************************************************************************************************************************
class _dateioggvorbis{
        public:
                _dateioggvorbis();
                virtual ~_dateioggvorbis();
                unsigned int anzahlkanal();
                unsigned int rate();
                bool laden(std::vector<unsigned char> &buffer);
                bool decodieren(std::vector<unsigned char> &buffer, int size = -1);  // -1 = komplette Datei einlesen, return value: true = Noch Daten vorhanden, false = Wir sind schon am Ende
        private:
                std::vector<unsigned char> pdaten;
                unsigned int panzahlkanal;
                unsigned int prate;
                _strukturoggvorbis pstruktur;
                OggVorbis_File pdatei;
};
//******************************************************************************************************************************************************************************************************
//                                                                  A K U S T I K O P E N A L 
//******************************************************************************************************************************************************************************************************
class _akustikopenal:public _akustik{
        public:
                _akustikopenal();
                virtual ~_akustikopenal();
                virtual void animieren(_tg seconds);
                //ton parameter
                virtual void zuhoererort(const _vektor3<_tg>&pos);
                virtual void zuhoerergeschwindigkeit(const _vektor3<_tg>&vel);
                virtual void zuhoererrichtung(const _vektor3<_tg>&dir, const _vektor3<_tg>&up);
                virtual _tonsammlung*erzeugentonsammlung(const unsigned int numSources);
                //ton
                virtual _ton*erzeugenton();
                virtual void abspielen(_ton*);
                virtual void abspielen(_ton*,_tg l,_tg b0,_tg b1);
                virtual void abspielen(unsigned int,_ton*,const _vektor3<_tg>&pos,const _vektor3<_tg>&vel,_tg fadeTime=0);
                virtual void anhalten(unsigned int,_ton*,_tg fadeTime=0);
                virtual void stoppen(unsigned int,_ton*,_tg fadeTime=0);
                // Streams
                virtual _tonfluss*erzeugentonfluss();
                virtual void abspielen(_tonfluss*,_tg fadeTime=0);
                virtual void anhalten(_tonfluss*,_tg fadeTime=0);
                virtual void stoppen(_tonfluss*,_tg fadeTime=0);

        
                virtual void stoppenquellemitbuffer(const unsigned int buffer);                
};
//******************************************************************************************************************************************************************************************************
//                                                                  T O N O P E N A L 
//******************************************************************************************************************************************************************************************************
class _tonopenal:public _ton{
        public:
                _tonopenal(_akustik*);
                virtual ~_tonopenal();
                virtual bool laden(std::vector<unsigned char> &buffer);
};
//******************************************************************************************************************************************************************************************************
//                                                                  T O N F L U S S O P E N A L 
//******************************************************************************************************************************************************************************************************
class _tonflussopenal:public _tonfluss,public _dateioggvorbis{
        public:
                _tonflussopenal(_akustik*);
                virtual ~_tonflussopenal();
                virtual unsigned int identifikationquelle()const;
                virtual void identifikationquelle(const unsigned int q);
                virtual unsigned int identifikationstream(const unsigned int)const;
                
                virtual bool laden(std::vector<unsigned char>&buffer);
                virtual void animieren(_tg seconds);
                virtual bool spielt()const;
                virtual bool angehalten()const;    
                
                virtual void aktiv(const bool);
                virtual bool aktiv() const;
                virtual void schleife(const bool);
                virtual bool schleife() const;
                               
                virtual void fuellenbuffer(unsigned int id);
       private:
                unsigned int pidentifikationquelle;  // Streams have their own Sound-Source
                unsigned int pidentifikationbuffer[NUM_STREAMBUFFERS];
                bool paktiv;
                bool pschleife;
                bool pausblendenanhalten;
                bool pausblendenstoppen;
                _interpolatorlinear<_tg> pinterpolator;      
};
//******************************************************************************************************************************************************************************************************
//                                                                  T O N S A M M L U N G O P E N A L 
//******************************************************************************************************************************************************************************************************
class _tonsammlungopenal:public _tonsammlung{
        public:
                _tonsammlungopenal(_akustik*a,unsigned int numSources);
                virtual ~_tonsammlungopenal();
                virtual void anhalten(_tg fadeTime);
                virtual void fortsetzen(_tg fadeTime);
                virtual void stoppen(_tg fadeTime);
        public:
                unsigned int findenfreiequelle();
                void stoppenquellemitbuffer(unsigned int buffer);
                void lautstaerkespielendequelle(_tg value);
                void animieren(_tg seconds);  
        private:
             
                   
                         
        
};

//******************************************************************************************************************
//										M U S I K E I N T R A G 
//******************************************************************************************************************
class _musikeintrag:public _listenknotenbasis<_musikeintrag>{
        public:
                _musikeintrag(_musikverwaltung*m,const _zeichenkette<char>&datei);
                virtual ~_musikeintrag();
                bool laden();
                void animieren();
                void einblenden();
                void ausblenden();
        private:
                _akustik*pakustik;
                _musikverwaltung*pmusikverwaltung;
                _tg pspieldauer;
                _zeichenkette<char> pdatei;
                _tonfluss*ptonfluss;
                bool pausblenden;
                bool peinblenden;
                _tg pblendwert;
};


//******************************************************************************************************************
//										M U S I K V E R W A L T U N G
//******************************************************************************************************************
class _musikverwaltung:public _listebasis<_musikeintrag>{
        public:
                _musikverwaltung(_akustik*a,_zeit*z);
                virtual ~_musikverwaltung();
                _akustik*akustik();
                _musikeintrag*erzeugenmusik(const _zeichenkette<char>&datei);
                void laden();
                bool ladenschritt();
                _tg blendgeschwindigkeit()const;
                void lautstaerke(const _tg);
                _tg lautstaerke()const;
                void abspielen(int i,bool restart=false);
                void ausblenden();
                void einblenden(int i);
              //  void einblendenmenue();				
               // void aktualisierenspiel(int i);
               // void aktualisierenmenue(int i);
                void animieren(bool paused);
        public:
	            _akustik*pakustik;
	            _zeit*pzeit;
	            _musikeintrag*pladeniterator;
	            _tg pblendgeschwindigkeit;
	            _tg plautstaerke;
	           /* _musikeintrag*paktuell;
	            _musikeintrag*pnaechstes;

	            int menueindex;
	            unsigned int quellemenue;
	            int quellemenueswitchto;
	            bool quellemenuefadeswitch;
	            bool quellemenuefadedown;
	            bool quellemenuefadeup;
	            _tg menuefade;
	            _tg menuefadespeed;
            	
	            int spielindex;
	            unsigned int quellespiel; 
	            int quellespielswitchto;
	            bool quellespielfadeswitch;
	            bool quellespielfadedown;
	            bool quellespielfadeup;
	            _tg spielfade;
	            _tg spielfadespeed;
            	
	            bool spielmode;
	            int switchindex;
	            int status;
	            _tg starttime;*/
};	
		








#endif

