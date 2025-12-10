//******************************************************************************************************************************************************************************************************
//  Project     : grundplatte
//  Library     : _grundplatte.lib
//  Module      : _weltoptik.hpp
//  Date        : 1.1.2003
//  Description : 
//******************************************************************************************************************************************************************************************************
#ifndef _optikh_included
#define _optikh_included
#include<_global.hpp>
#include<_system.hpp>
#include<_vektor.hpp>
#include<_bild.hpp>
#include<_welt.hpp>

//******************************************************************************************************************************************************************************************************
//                                                              P R E D E K L A R A T I O N 
//******************************************************************************************************************************************************************************************************
class _bestrahler;
class _strahl;
class _strahlschnitt;
class _spektrallinie;
//******************************************************************************************************************************************************************************************************
//                                                              Z Y K L I S C H E 
//******************************************************************************************************************************************************************************************************
class _system;
class _tastatur;
//class _maus;
template<class _tg>class _kamera;
template<class _tg,class _to> class _licht;

//******************************************************************************************************************************************************************************************************
//                                                              B E S T R A H L E R 
//******************************************************************************************************************************************************************************************************
class _bestrahler{
        friend class _strahl;
        friend class _strahlschnitt;
        public:
                _bestrahler();
                virtual ~_bestrahler();
                void bestrahlenlightmap(_welt*,_polygon*);
                void bestrahlenlightmapzone(_welt*);
                void bestrahlenlightmappolygon(_partition::_zone*zone,_netz*n);
                void nachbearbeitenlightmap(_bild<_tb>*bild);
                void betrachtennachbar(int,int,_bild<_tb>*,bool&,_vektor3<_to>&);
                void starten(_welt*,_kamera<_tg>*,_bild<_tb>*);
                bool animieren(_system*,_tastatur*,_maus<_tg>*,_grafik*,_kamera<_tg>*);
                void beenden();
                void lichtambient(_vektor3<_to>);
                unsigned int reflektionstiefe() const;
                unsigned int refraktionstiefe() const;
                void reflektionstiefe(const unsigned int);
                void refraktionstiefe(const unsigned int);
                void refraktiondispersiv(const bool);
                void dispersionsaufloesung(const unsigned int);

                unsigned int bilditeratorx()const;
                void visualisierung(bool);
                void visualisierungbild(bool);
                void visualisierungumschalten();
                void visualisierunganhalten(bool);
                bool visualisierunganhalten();
                void zeichnen(_grafik*);
                void zeichnenzeile(_grafik*);
                void visualisieren(_system*,_tastatur*,_maus<_tg>*,_grafik*,_kamera<_tg>*);
                void devisualisieren();
        private:                
                void vorbereiten();
                void nachbereiten();
                void berechnenspektrallinien();
                void bestrahlenlightmappolygon(_polygon*,_bild<_tb>*,_liste<_polygon>*,_liste<_licht<_tg,_to> >*,const _vektor3<_to>&);
                _strahl* erzeugenstrahlbaum(_vektor3<_tg>,_vektor3<_tg>,unsigned int,unsigned int);//strahlwurzel
                _strahl* erzeugenstrahlbaum(_vektor3<_tg>,_vektor3<_tg>,unsigned int,_tg,_tg,_polygon*);//lichtberechnung
                _strahl* erzeugenstrahlbaumreflektion(_strahlschnitt*,_vektor3<_tg>,_vektor3<_tg>,unsigned int);//refelktionsrekursion
                _strahl* erzeugenstrahlbaumrefraktion(_strahlschnitt*,unsigned int);//refraktionsrekursion
                bool berechnenfarbe(_strahl*,_vektor3<_to>&);//baumfarbe
                bool berechnenfarbe(_strahl*,_licht<_tg,_to>*,_vektor3<_to>&);//lichtberechnung
                _tg  berechnenlichtintensitaet(const _vektor3<_tg>&o,const _vektor3<_tg>&n,_licht<_tg,_to>*lit);
                void spektralkonversion(_tg,_vektor3<_to>&);
                void spektralkonversion(unsigned int,_tg,_tg,_tg,_tg,_tg,_vektor3<_to>&);
                void anpassenmonochromfilter(_strahl*);
                void anpassenmonochromfilter(_strahl*,_vektor3<_to>);
                void visualisieren(_strahl*);
                
        private:
                _welt*welt;
                _kamera<_tg>*animcamera;
                _bild<_tb>*animmap;
                _tg animx,animy,animdx,animdy;
                unsigned int animmapx;
                unsigned int animmapy;
                _vektor3<_to> pfarbeambient;
                unsigned int preflektionstiefe;
                unsigned int prefraktionstiefe;
                bool prefraktiondispersiv;
                _vektoranalysis3<_tg> V3;
                unsigned int pdispersionsaufloesung;
                _listebasis<_spektrallinie > pspektrallinien;
                _liste<_weltdebugpfeil > pdbarrows;
                bool pvis;
                bool pvisbild;
                bool pvishalt;
                unsigned int pviszahl;
                unsigned int pvisrate;
                _vektor3<_to> farbeundef;

};
//******************************************************************************************************************************************************************************************************
//                                                              S T R A H L
//******************************************************************************************************************************************************************************************************
class _strahl:public _listebasis<_strahlschnitt >,public _listenknotenbasis<_strahl >{
        friend class _bestrahler;
        friend class _strahlschnitt;
        public:
                using _listebasis<_strahlschnitt >::anfang;
                using _listebasis<_strahlschnitt >::vorheriges;
                using _listebasis<_strahlschnitt >::naechstes;
                using _listenknotenbasis<_strahl >::vorheriges;
                using _listenknotenbasis<_strahl >::naechstes;
        private:
                _strahl(_bestrahler*,_welt*,const _vektor3<_tg>&,const _vektor3<_tg>&);//startstrahl
                _strahl(_bestrahler*,_welt*,_strahlschnitt*,const _vektor3<_tg>&,const _vektor3<_tg>&);//angehängte strahle
        public:                
                virtual ~_strahl();
        private:                
                void loeschenschnittpunktverdeckt();
                void loeschenschnittpunktaussererster();
        private:
                _vektor3<_tg> ort;
                _vektor3<_tg> vektor;
                _welt*welt;
                _bestrahler*bestrahler;
                _vektor3<_to> filter;
                _vektor3<_to> filterroh;
                _to blende;
                bool monochrom;
                _tg wellenlaenge;
};
//******************************************************************************************************************************************************************************************************
//                                                              S T R A H L S C H N I T T 
//******************************************************************************************************************************************************************************************************
class _strahlschnitt:public _listenknotenbasissortiert<_strahlschnitt,_tg>,public _listebasis<_strahl >{
        friend class _strahl;
        friend class _bestrahler;
        public:
                using _listenknotenbasissortiert<_strahlschnitt,_tg>::naechstes;
                using _listenknotenbasissortiert<_strahlschnitt,_tg>::vorheriges;
                using _listebasis<_strahl >::anfang;
                using _listebasis<_strahl >::naechstes;
                using _listebasis<_strahl >::vorheriges;
                
        private:
                _strahlschnitt(_strahl*,_vektor3<_tg> ,_polygon*,_vertex*,_vertex*,_vertex*,_tg,_tg,_tg);
                ~_strahlschnitt();
                void farbetextur(_vektor<_tb>&);
                void farbelicht(_vektor3<_to>&);
                bool schatten(_licht<_tg,_to>*,_vektor3<_to>&);
                _to transparenz(_vektor<_tb>&);
                _vektor3<_tg> reflektionsvektor();
               // _vektor3<_tg> normale();
        private:                
                _strahl*strahl;//rueckzeiger
                _vektor3<_tg> ort;
                _polygon*polygon;
                _vertex*vertex[3];
                _vektor3<_tg> normale;
                _tg a;
                _tg b;
                _tg c;
                _to ptransparenz;
                bool ptransparenzupdated;
                _vektor<_tb> pfarbetextur;
                bool pfarbetexturupdated;
};
//******************************************************************************************************************************************************************************************************
//                                                              S P E K T R A L L I N I E 
//******************************************************************************************************************************************************************************************************
class _spektrallinie:public _listenknotenbasis<_spektrallinie >{
        friend class _bestrahler;
        private:
                _spektrallinie(_listebasis<_spektrallinie >*,_tg,_vektor3<_to>);
        public:                
                ~_spektrallinie();
        private:                
                _tg wellenlaenge;
                _vektor3<_to> rgbwert;
                _vektor3<_to> rgbwertroh;
};
#endif
