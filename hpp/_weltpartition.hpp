//******************************************************************************************************************************************************************************************************
//  Project     : grundplatte
//  Library     : _grundplatte.lib
//  Module      : _weltpartition.hpp
//  Date        : 28.12.2002  
//  Description : 
//******************************************************************************************************************************************************************************************************
#ifndef _weltpartitionh_included
#define _weltpartitionh_included
//*********************************************************************************************************************************************************************************
//                                                              P R E D E K L A R A T I O N
//******************************************************************************************************************************************************************************************************
namespace _partition{
  class _zone;
  class _zoneintersektion;
  class _linienintersektion;
  class _ebene;
  class _sektor;
  class _polygon;
  class _kante;
  class _kantenlimitator;
  class _vertex;
  class _sichtbarkeitsvolumen;
  class _sichtbarkeitsebene;
};
#include <_global.hpp>
#include <_struktur.hpp>
#include <_vektor.hpp>
#include <_grafik.hpp>
#include <_bild.hpp>
#include <_weltgeometrie.hpp>
#include <_welt.hpp>
#include <_weltintersektion.hpp>
#include <_weltkollision.hpp>
#include <_system.hpp>
#include <_weltpartikel.hpp>

//******************************************************************************************************************************************************************************************************
//                                                              Z Y K L I S C H E 
//******************************************************************************************************************************************************************************************************
template<class _tg> class _kamera;
template<class _tg,class _to> class _licht;
class _welt;
class _weltdebugebene;
class _weltdebugtext;
class _weltdebugschirm;
class _kollidierbarkugel;
class _kollidierbarpolygontranslation;
class _kollidierbarnetztranslation;
//******************************************************************************************************************************************************************************************************
//                                                              P A R T I T I O N   : :   Z O N E 
//******************************************************************************************************************************************************************************************************
namespace _partition{
 class _zone:
 public _baumbasis<_ebene >,
 public _listenknotenbasis<_zone >,
 public _liste< ::_polygon >,
 public _listebasis<_kamera<_tg> >,
 public _listebasis<_sektor >,
 public _listebasis<_zoneintersektion >,
 public _listebasis<_partikelquelle>,
 public _basis::_speicherbarargument<_partition::_zone>,
 public _speicherbarbinaer{
        public:
        using _baumbasis<_partition::_ebene >::anfang;
        using _baumbasis<_partition::_ebene >::naechstes;
        using _listebasis<_partition::_sektor >::anfang;
        using _listebasis<_partition::_sektor >::naechstes;
        using _listebasis<_partition::_sektor >::vorheriges;
        //using _listebasis<_partition::_sektor >::einhaengen;
        using _liste< ::_polygon >::anfang;
        using _liste< ::_polygon >::naechstes;
        using _liste< ::_polygon >::vorheriges;
        using _liste< ::_polygon >::einhaengen;
        using _listebasis<_kamera<_tg> >::anfang;
        using _listebasis<_kamera<_tg> >::naechstes;
        using _listebasis<_kamera<_tg> >::vorheriges;
        //using _listebasis<_kamera<_tg> >::einhaengen;
        using _listebasis<_partikelquelle>::anfang;
        using _listebasis<_partikelquelle>::naechstes;
        using _listebasis<_partikelquelle>::vorheriges;
        friend class _welt;
        public:
                _zone(_welt*);
                virtual ~_zone();
                _welt*welt();
                void ambientlicht(const _vektor3<_to>&);
                _vektor3<_to>&ambientlicht();
                void pruefenumgebungszone();
                void erzeugensektor();
                void verbindensektor();
                void erzeugensichtbarkeit();
                void loeschenvertexnichtportal();
                void erzeugenvertexlicht();
                void anlegenlightmap(_texturverwaltung<_tb>*,_zeichenkette<char>,_tg);
                void markierung(int);
                int markierung()const;
                void markierungebene(int);
                _sektor*sektor(const _vektor3<_tg>&);//liefert den sektor des punktes
                void einfuegenintern( ::_netz*);   //hängt äußere polygon in die interne sektorliste ein
                void einfuegenintern( ::_polygon*);//hängt äußere polygon in die interne sektorliste ein
                void einfuegeninternrekursiv(::_polygon*poly,_sektor*sektor);
                _liste< ::_polygon>* innerhalbquader(_tg,_tg,_tg,_tg,_tg,_tg)const;
                bool innerhalbquader(_tg x,_tg y,_tg z,_tg wx,_tg wy,_tg wz,::_polygon*p)const;
                void initialisierenzeitfaktor(_zeit*);
                void berechnenzeitfaktor(_zeit*);
                _tg bilderprosekunde();
                inline _tg zeitfaktor();
                void animieren();
                //----------------- debug -------------------
                void visualizetree();
                void visualizetree(_ebene*);
                void visualizeedgescene(_liste<_kante >*);
                void visualisieren(_liste<_partition::_polygon >*,_vektor4<_to>);
                void visualisieren(_partition::_polygon*,_vektor4<_to>,_partition::_polygon*,_vektor4<_to>);
                void debuganimation();
                _weltdebugschirm*debugschirm();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_zone>*);
                void speichern(_speicherbardynamisch<_zone>*);
                char assoziieren(_speicherbardynamisch<_zone>*);
                bool laden(_dateispeicherbarbinaer*d);
				void speichern(_dateispeicherbarbinaer*d);
                bool assoziieren();
        private:
                void checksourroundingzone();
                void uniteinnerzone();
                void erzeugensektor(_ebene*);
                void erzeugensektor(_ebene*,bool);
                bool validsector(_sektor*,_liste<_partition::_ebene >*);
                void createsectorpolygon(_sektor*,_listenknoten<_ebene >*,_liste<_ebene >*,bool);
                _polygon* createsectorpolygon(_sektor*,_ebene*,_liste<_kante >*,bool,bool);
                void createsectoredge(_liste<_kante >*,_listenknoten<_ebene >*,_ebene*,_vektor3<_tg>&,_vektor3<_tg>&,_vektor3<_tg>&,bool&,bool&,bool&);
                bool validtoinsertedge(_kante*,_liste<_kante >*,bool&);
                void insertedge(::_polygon*,_kante*&,_liste<_kante >*);
                void clearinvalidedge(_liste<_kante >*);
                void checkedgeclosity(_liste<_kante >*,bool&,bool&);
                _kantenlimitator*getotherlimitator(_liste<_partition::_kante >*,_listenknoten<_partition::_kante >*,_partition::_kantenlimitator*);
                void subtractkomplanarpolygon(_partition::_polygon*,_liste< ::_polygon >*,_liste<_partition::_polygon >*);//sektorpoly, komplanare, subresult
                void divideworldpolygon(_liste<_partition::_polygon >*,::_polygon*,_liste<_partition::_polygon >*); //subresult,weltpoly, divresult
                void identifyportals(_liste<_partition::_polygon >*,::_polygon*);   //divresult, weltpoly
                void clearoverlayedportals(_liste<_partition::_polygon >*,::_polygon*);
                void multiplyvertexlight(::_polygon*);
        private:
                void subtract(_partition::_polygon*,_liste<_partition::_polygon >*);
                void einfuegeninsektor(_sektor*,_liste<_partition::_polygon >*);
        public:
                void erzeugendebugschirm();
                void loeschendebugschirm();
        private:
                _welt*pworld;
                int pflag;
                _tg pbilderprosek;
                _tg pzeitfaktor;
                unsigned int poldtime;
                _vektor3<_to> pambientlicht;
                //************************ DEBUG *************************
                _liste<_weltdebugpfeil > ptreelines;
                _liste<_weltdebuglinie > pdbedges;
                _liste<_weltdebugebene > pdbplanes;
                _weltdebugschirm*dbscreen;
                _kamera<_tg>*dbcam;
                //_maus<_tg>*dbmo;
                //_grafik<char,_tg,_to>*dbgra;
                _vektor4<_to> pc;
                _vektor4<_to> pc2;
                
        public:                
                int pdbcount;
                int anzahlsektor;
                int debugsector;
                
 };
 _tg _zone::zeitfaktor(){
                                                                return(pzeitfaktor);
 };
 
};
//******************************************************************************************************************************************************************************************************
//                                                              P A R T I T I O N   : :   Z O N E I N T E R S E C T I O N 
//******************************************************************************************************************************************************************************************************
namespace _partition{
 class _zoneintersektion:public _listenknotenbasissortiert<_zoneintersektion,_tg>{
        friend class _zone;
        private:
                _zoneintersektion(_zone*,::_polygon*,_vektor3<_tg>,_tg);
        private:
                _zone*pzone;
                ::_polygon*ppolygon;
                _vektor3<_tg> plocus;
                _tg palpha;
 };
};
//******************************************************************************************************************************************************************************************************
//                                                              P A R T I T I O N   : :   L I N I E N I N T E R S E K T I O N 
//******************************************************************************************************************************************************************************************************
namespace _partition{
 class _linienintersektion:public _listenknotenbasissortiert<_linienintersektion,_tg>,_vektor3<_tg>{
        friend class _zone;
        friend class _sektor;
        friend class _polygon;
        private:
                _linienintersektion(_listebasis<_linienintersektion >*,_vektor3<_tg>,_tg,_vertex*,_vertex*);
                _tg alpha()const;
        private:
                //_vektor<_tg> plocus;
                _tg palpha;
                _vertex*pvprev;
                _vertex*pvnext;
                
 };
};
//******************************************************************************************************************************************************************************************************
//                                                              P A R T I T I O N   : :   E B E N E
//******************************************************************************************************************************************************************************************************
namespace _partition{
 class _ebene:
 public _baumknotenbasis<_ebene >,
 public _basis::_speicherbarargument<_partition::_ebene>,
 public _speicherbarbinaer{
        public:
			    using _baumknotenbasis<_partition::_ebene>::naechstes;
			    using _baumknotenbasis<_partition::_ebene>::vorheriges;
		public:
                _ebene(_baumbasis<_ebene >*);
                _ebene(_baumbasis<_ebene >*,_baumknotenbasis<_ebene >*,bool,::_polygon*);
                virtual ~_ebene();
                inline ::_polygon*polygon();
                inline _sektor*sektorfront();
                inline _sektor*sektorrueck();
                inline void sektorfront(_sektor*);
                inline void sektorrueck(_sektor*);
                inline bool front(const _vektor3<_tg>&);
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_ebene>*);
                void speichern(_speicherbardynamisch<_ebene>*);
                char assoziieren(_speicherbardynamisch<_ebene>*);
                bool laden(_dateispeicherbarbinaer*d);
				void speichern(_dateispeicherbarbinaer*d);
                bool assoziieren();
        private:
                ::_polygon*ppoly;
                _sektor*psectorfront;
                _sektor*psectorback;
 };
};
//******************************************************************************************************************************************************************************************************
//                                                              P A R T I T I O N   : :   K A N T E 
//******************************************************************************************************************************************************************************************************
namespace _partition{
 class _kante{
        friend class _zone;
        friend class _kantenlimitator;
        private:
                _kante(_ebene*,_ebene*,_vektor3<_tg>,_vektor3<_tg>,_vektor3<_tg>);
        public:               
                virtual ~_kante();
        private:                
                void markierung(int);
                int markierung() const;
                _kantenlimitator*limitator(bool);
                _kantenlimitator*erzeugenlimitator(bool,_tg);
                void loeschenlimitator(bool);
                _vektor3<_tg> ort()const;
                _vektor3<_tg> vektor()const;
                _vektor3<_tg> normale()const;
                void visualisieren(const _vektor4<_to>);
                void unvisualisieren();
        private:
                _ebene*pplane[2];
                _kantenlimitator*pedgelimitator[2];
                _vektor3<_tg> plocus;
                _vektor3<_tg> pvector;
                _vektor3<_tg> pnormal;
                int pflag;
                //**************DEBUG **********************+
                _weltdebuglinie*debugl;
                _weltdebugpfeil*debugav;
                _weltdebugpfeil*debugan;
                _weltdebugpfeil*debuga0;
                _weltdebugpfeil*debuga1;
 };
};
//******************************************************************************************************************************************************************************************************
//                                                              P A R T I T I O N   : :   K A N T E N L I M I T A T O R
//******************************************************************************************************************************************************************************************************
namespace _partition{
 class _kantenlimitator{
        friend class _kante;
        //friend class _zone;
        private:
                _kantenlimitator(_kante*,bool,_tg);
                virtual ~_kantenlimitator();
        public:                
                inline _tg alpha()const;
                inline bool direktion()const;
                bool beweglich(const _tg)const;
                _vektor3<_tg> ort() const;
                _vektor3<_tg> locusvector() const;
                inline _kantenlimitator*anderes();
                inline void anderes(_kantenlimitator*);
                _kante*kante();
        private:                
                _tg palpha;
                bool pdirection;
                _kante*pedge;
                _kantenlimitator*pother;
                bool isclearing;
 };
};
//******************************************************************************************************************************************************************************************************
//                                                              P A R T I T I O N   : :   S E K T O R 
//******************************************************************************************************************************************************************************************************
namespace _partition{
 class _sektor:
 public _listebasis<_polygon >,//statische sektor-partition-polygone, verweisen auf weltpolygone der zone
 public _listebasis<_licht<_tg,_to> >,
 public _listenknotenbasis<_sektor >,
 public _liste<_kollidierbarkugel>,
 public _liste<_kollidierbarpolygontranslation>,
 public _liste<_kollidierbarnetztranslation>,
 public _basis::_speicherbarargument<_partition::_sektor>,
 public _speicherbarbinaer,
 public _baumoctal< ::_polygon,_tg>
 /*
 public _listebasis<_kollidierbarzylinder>,
 public _listebasis<_kollidierbarpunkt>*/
 
 {
        public: 
        using _listebasis<_polygon >::anfang;
        using _listebasis<_polygon >::vorheriges;
        using _listebasis<_polygon >::naechstes;
        using _listebasis<_licht<_tg,_to> >::anfang;
        using _listebasis<_licht<_tg,_to> >::vorheriges;
        using _listebasis<_licht<_tg,_to> >::naechstes;
        using _liste<_kollidierbarkugel>::anfang;
        using _liste<_kollidierbarkugel>::naechstes;
        using _liste<_kollidierbarkugel>::vorheriges;
        using _liste<_kollidierbarpolygontranslation>::anfang;
        using _liste<_kollidierbarpolygontranslation>::naechstes;
        using _liste<_kollidierbarpolygontranslation>::vorheriges;
        using _liste<_kollidierbarnetztranslation>::anfang;
        using _liste<_kollidierbarnetztranslation>::naechstes;
        using _liste<_kollidierbarnetztranslation>::vorheriges;
		using _baumoctal< ::_polygon,_tg>::anfang;
		using _baumoctal< ::_polygon,_tg>::naechstes;

        
        public:
                _sektor(_zone*);
                virtual ~_sektor();
                _zone*zone();
                void rueckgeschlossen();
                void aktualisieren();
                void verbinden();
                void verbinden(_sektor*);
                inline _vektor3<_tg> mitte()const;
                _vektor3<_tg> kollidierendervektor(const _vektor3<_tg>&,const _vektor3<_tg>&,_partition::_sektor*&,bool&,::_polygon*&);
                _vektor3<_tg> bewegungsvektor(const _vektor3<_tg>&,const _vektor3<_tg>&,_sektor*&,bool&);
                _vektor3<_tg> bewegungsvektor(const _vektor3<_tg>&,const _vektor3<_tg>&,_sektor*&,bool&,::_polygon*&);
                inline _vektor3<_tg> bewegungsvektorrekursiv(const _vektor3<_tg>&,const _vektor3<_tg>&,_sektor*&,bool&,::_polygon*&);
                _vektor3<_tg> bewegungsvektorreflektiv(const _vektor3<_tg>&,const _vektor3<_tg>&,bool&) const;
                void transformieren(_grafik*,_kamera<_tg>*);
                void zeichnen(_grafik*,_kamera<_tg>*);
                void zeichnenambient(_grafik*gra,_kamera<_tg>*,::_polygon*poly,unsigned int zyklus,unsigned int pass,bool nutzetransparenz);
                void zeichnenadditiv(_grafik*gra,_kamera<_tg>*,::_polygon*poly,unsigned int zyklus,unsigned int pass);
                void zeichnennichtdynamischschattiert(_grafik*gra,_kamera<_tg>*,::_polygon*poly,unsigned int zyklus,unsigned int pass);
                void zeichnenadditiv(_grafik*gra,_kamera<_tg>*,_licht<_tg,_to>*lit,unsigned int is);
                void zeichnensubtraktiv(_grafik*gra,_kamera<_tg>*,_licht<_tg,_to>*lit,unsigned int is);
                void loeschenvertexnichtportal();                    //vertexstructur für nicht portale aushaengen
                inline ::_liste< ::_polygon >*sichtbarkeitextern();
                inline ::_liste<_sektor >*sichtbarkeitsektor();
                inline ::_liste<_sektor >*sichtbarkeitsektor2tergrad();
                inline ::_liste< ::_polygon >*internepolygonestatisch();
                inline ::_liste< ::_polygon >*internepolygonedynamisch();
                inline ::_liste< ::_netz >*internenetze();
                void erzeugenvertexlicht();
                void erzeugenvertexlicht(::_polygon*);
                void erzeugenvertexlicht(::_polygon*poly,_licht<_tg,_to>*lit);
                void erzeugenbaum(const _tg,const _tg);
                void erzeugensichtbarkeit();                        //sichtbarkeit berechnen
                void erzeugensichtbarkeit2tergrad();
                bool istsichtbarsektor(_partition::_sektor*);
                bool istsichtbarsektor(_partition::_polygon*,_partition::_polygon*);                
                bool istsichtbarsektor(_partition::_polygon*,_vektor3<_tg>,_partition::_polygon*,_partition::_polygon*,_vektor3<_tg>,const bool);
                bool istsichtbarsektor(_partition::_polygon*,_partition::_polygon*,_vektor3<_tg>,_partition::_polygon*,_partition::_polygon*,_vektor3<_tg>);  
                bool istsichtbarsektor(_partition::_polygon*portalthis,_partition::_polygon*portalother,_sichtbarkeitsvolumen*vv,_liste<_sektor>*lsectorgesperrt);
                bool istsichtbar(_partition::_polygon*,::_polygon*);//weltpoly an portalebene abschneiden
                bool istsichtbar(_partition::_polygon*,::_polygon*,_partition::_polygon*,const bool);//portal an weltpolyebene abschneiden
                bool istsichtbar(_partition::_polygon*,::_polygon*,_partition::_polygon*,_partition::_polygon*);//kernfunktion polygonale sichtbarkeit
                bool istsichtbar(_partition::_polygon*portal,_partition::_polygon*welt,_sichtbarkeitsvolumen*vv,_liste<_sektor>*lsectorgesperrt,_liste<_sektor>*targetsectors);
                unsigned int anzahlpolygon() const;
                unsigned int anzahlportal() const;
                unsigned int countnonportal() const;
                unsigned int anzahlvertex() const;
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_sektor>*);
                void speichern(_speicherbardynamisch<_sektor>*);
                char assoziieren(_speicherbardynamisch<_sektor>*);
                bool laden(_dateispeicherbarbinaer*d);
				void speichern(_dateispeicherbarbinaer*d);
                bool assoziieren();
                //debug
                void unvisualisieren();
                void visualisieren();
                void visualisieren(_vektor4<_to>);
        private:
                bool pbackclosed;
                ::_liste< ::_polygon > pinternstatisch;//dem sektor zugefügte polygone (alles was in dem sektor drin ist)
                ::_liste< ::_polygon > pinterndynamisch;//dem sektor zugefügte polygone (alles was in dem sektor drin ist)
                ::_liste< ::_netz> pinternnetz;//dem sektor zugefügte netze (wie oben)
                ::_liste< ::_polygon > pvisibilityextern;//sichtbarkeit von (statischen) Polygonen anderer sektoren (zonenpolygone)
                ::_liste< ::_polygon > pvisibilityintern;//sichtbarkeit von (statischen) Polygonen , die in anderen sektoren enthalten sind 
                ::_liste<_sektor > pvisibilitysector;//sichtbarkeit von Sektoren 
                ::_liste<_sektor > pvisibilitysector2tergrad;//sichtbarkeit von sektoren 2. grades (enthält die primäre Sektorsichtbarkeit)
                _zone*pzone;
                _vektor3<_tg> pmiddle;
                //*********DEBUG**********
                _weltdebugkreuz*pdbcross;
                //************************
 };
 ::_liste< ::_polygon >*_sektor::sichtbarkeitextern(){
                                                                return(&pvisibilityextern);
 };
 ::_liste<_sektor >*_sektor::sichtbarkeitsektor(){
                                                                return(&pvisibilitysector);
 };
 ::_liste<_sektor >*_sektor::sichtbarkeitsektor2tergrad(){
                                                                return(&pvisibilitysector2tergrad);
 };
 ::_liste< ::_polygon>*_sektor::internepolygonestatisch(){
                                                                return(&pinternstatisch);
 };
 ::_liste< ::_polygon>*_sektor::internepolygonedynamisch(){
                                                                return(&pinterndynamisch);
 };
 ::_liste< ::_netz >*_sektor::internenetze(){
                                                                return(&pinternnetz);
 };
};

//******************************************************************************************************************************************************************************************************
//                                                              P A R T I T I O N   : :   P O L Y G O N 
//******************************************************************************************************************************************************************************************************
namespace _partition{
 class _polygon:
 public _listenknotenbasis<_polygon >,
 public _listebasis<_vertex >,
 public _liste<_partition::_polygon >,
 public _basis::_speicherbarargument<_partition::_polygon>,
 public _speicherbarbinaer{
        friend class _vertex;
        public:
        //using _listebasis<_vertex >::einhaengen;
        using _listebasis<_vertex >::anfang;
        using _listebasis<_vertex >::naechstes;
        using _listebasis<_vertex >::vorheriges;
        using _liste<_partition::_polygon >::einhaengen;
        using _liste<_partition::_polygon >::anfang;
        using _liste<_partition::_polygon >::naechstes;
        using _liste<_partition::_polygon >::vorheriges;

        public:
             //   _polygon();
                //_polygon(_sektor*,::_polygon*,const bool);
                _polygon(::_polygon*);
                _polygon(const _partition::_polygon*);
                virtual ~_polygon();
                ::_polygon*polygon();
                _sektor*sektor();
                _sektor*holennaechstersektor(const _vektor3<_tg>&);
                
                void loeschenvertex();
                void einfuegeninsektor(_sektor*);
                bool portal() const;
                void portal(const bool);
                void aktualisieren();
                void aktualisierengroessterindex();
                bool gueltig();
                _vektor3<_tg> mitte();
                _vektor3<_tg> normalsector(const _vektor3<_tg>);
                _vektor3<_tg> normale()const;
                _vektor3<_tg> normale(const _vertex*,const _vertex*);
                void umgrenzungsquader(_tg&,_tg&,_tg&,_tg&,_tg&,_tg&)const;
                //bool innerhalbpunkt(const _vektor3<_tg>);
                bool innerhalbpunkt(const _vektor3<_tg>&);
                bool innerhalbkugel(_vektor3<_tg>,_tg);
                bool innerhalbkugeltranslation(const _vektor3<_tg>&start,const _vektor3<_tg>&vektor,_tg r);
                bool innerhalbquadertranslation(const _vektor3<_tg>&start,const _vektor3<_tg>&vektor,const _tg wx,const _tg wy,const _tg wz);
                bool innerhalbpolygontranslation(::_polygon*,const _vektor3<_tg>&start,_liste<_vektor3<_tg> >*orte,const _vektor3<_tg>&vektor);
                bool innerhalbnetztranslation(::_netz*,const _vektor3<_tg>&start,const _vektor3<_tg>&vektor);
                bool innerhalbpolygon( ::_polygon*);
                bool kanteinnerhalbpolygon(const _vektor3<_tg>,const _vektor3<_tg>);
                void markierungvertex(const int);
                void visualisieren(_partition::_zone*,_vektor4<_to> col);
                void unvisualisieren();
                void teilen(_partition::_polygon*,_liste<_partition::_polygon >*);
                void teilen(const _vektor3<_tg>,const _vektor3<_tg>,const _vektor3<_tg>,const _vektor3<_tg>,_partition::_polygon*&,_partition::_polygon*&);
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_polygon>*);
                void speichern(_speicherbardynamisch<_polygon>*);
                char assoziieren(_speicherbardynamisch<_polygon>*);
                bool laden(_dateispeicherbarbinaer*d);
				void speichern(_dateispeicherbarbinaer*d);
                bool assoziieren();
        private:
                void teilen(_listebasis<_linienintersektion >*,_partition::_polygon*&,_partition::_polygon*&);
                void unaktualisieren();
        public:
                unsigned int markierungkollisionobjekt;
                unsigned int markierungkollisionrekursion;
                unsigned int markierungkollisionzyklus;                
        private:
                _sektor*psector;
                ::_polygon*ppoly;
                bool pisportal;
                bool updated;
                _vektor3<_tg> pmiddle;//absolut
                _vektor3<_tg> pnormale;//sektornormale, zeigt immer nach aussen !
                unsigned int pgi[3];//wie bei weltpoly : groessterindex 
                //*********DEBUG**********
                _liste<_weltdebugpfeil > pdbarrows;
                _liste<_weltdebugkreuz > pdbcrosses;
                //************************
 };
};
//******************************************************************************************************************************************************************************************************
//                                                              P A R T I T I O N   : :   V E R T E X 
//******************************************************************************************************************************************************************************************************
namespace _partition{
 class _vertex:
 public _vektor3<_tg>,
 public _listenknotenbasis<_vertex >,
 public _basis::_speicherbarargument<_partition::_vertex>,
 public _speicherbarbinaer{
 friend class _partition::_polygon;
	    public:
				using _listenknotenbasis<_vertex>::naechstes;
				using _listenknotenbasis<_vertex>::vorheriges;
        public:
                _vertex(_polygon*,_vektor3<_tg>);
                virtual ~_vertex();
                void markierung(const int);
                int markierung()const;
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_vertex>*);
                void speichern(_speicherbardynamisch<_vertex>*);
                char assoziieren(_speicherbardynamisch<_vertex>*);
                bool laden(_dateispeicherbarbinaer*d);
				void speichern(_dateispeicherbarbinaer*d);
                bool assoziieren();
        private:
                _polygon*ppoly;
                int pflag;
                //vorberechnete zur innerhalb-prüfung
                _tg determinante;
                _tg kantenormale[2];
                _tg kantevektor[2];
                _tg kantemitte[2];
 };
};
//******************************************************************************************************************************************************************************************************
//                                                              P A R T I T I O N   : :   S I C H T B A R K E I T S V O L U M E N
//******************************************************************************************************************************************************************************************************
namespace _partition{
 class _sichtbarkeitsvolumen:public _listebasis<_sichtbarkeitsebene >{
        friend  class _sektor;
        private:
                _sichtbarkeitsvolumen(_zone*,_polygon*,_vektor3<_tg>,_polygon*,_vektor3<_tg>);
                virtual ~_sichtbarkeitsvolumen();
                
                void createplane(_polygon*,_vektor3<_tg>,_polygon*,_vektor3<_tg>);
                bool prufengueltigkeit(_vertex*,_vertex*,_vertex*,_vektor3<_tg>,_polygon*);
                bool pruefenfront(_vektor3<_tg>,_vektor3<_tg>,_vektor3<_tg>,_vektor3<_tg>,_vektor3<_tg>);
                void clearredundantplane();
                _polygon*innerhalb(_polygon*);
                void schneidenszene(::_polygon*);
                _polygon*schneidenebene(_partition::_polygon*,_vektor3<_tg>,_vektor3<_tg>,_vektor3<_tg>,_vektor3<_tg>);
        public:                
                _vektor3<_tg> mitte() const;
                _zone*zone();
                _polygon*ziel();
                _vektor3<_tg> zielnormale()const;
        private:                
                //DEBUG
                void visualisieren(_vektor4<_to>,_vektor4<_to>,_vektor4<_to>);
                void unvisualisieren();
        private:
                _zone*pzone;  
                _polygon*ppolygontarget;
                _vektor3<_tg> pntarget;
                _polygon*ppolygonsource;
                _vektor3<_tg> pnsource;
                _vektor3<_tg> pmiddle;
                //DEBUG
                _liste<_weltdebuglinie > pdblines;
 };
};
//******************************************************************************************************************************************************************************************************
//                                                              P A R T I T I O N   : :   S I C H T B A R K E I T S E B E N E 
//******************************************************************************************************************************************************************************************************
namespace _partition{
 class _sichtbarkeitsebene:public _listenknotenbasis<_sichtbarkeitsebene >{
        friend class _sichtbarkeitsvolumen;
        private:
                _sichtbarkeitsebene(_sichtbarkeitsvolumen*,_vertex*,_vertex*,_vertex*);
        public:                
                virtual ~_sichtbarkeitsebene();
        private:                
                void aktualisieren();
                //DEBUG
                void visualisieren(_vektor4<_to>);
                void unvisualisieren();
        private:
                _sichtbarkeitsvolumen*pvolume;
                _vertex*pvertex[3];
                _vektor3<_tg> pnormal;
                _vektor3<_tg> pmiddle;
                _vektor3<_tg> pplane[2];
                //DEBUG
                _liste<_weltdebuglinie > pdblines;
 };
};
#endif

