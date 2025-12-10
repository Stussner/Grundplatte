//******************************************************************************************************************************************************************************************************
//  Project     : grundplatte
//  Library     : _grundplatte.lib
//  Module      : _welt.hpp
//  Date        : 28.12.2002
//  Description : 
//******************************************************************************************************************************************************************************************************

#ifndef _welth_included
#define _welth_included

#include <_global.hpp>
//*********************************************************************************************************************************************************************************
//                                                                F O R W A R D D E K L A R A T I O N
//*********************************************************************************************************************************************************************************

class _welt;
class _dreieck;
class _kantedreieck;
class _vertex;
class _verbindervertexpolygon;
class _kugel;

class _kugelschatten;
//-------------------------------------------------------------- strategische------------------------------------------------------------------------------------------------------
class _bewertungpolygonoptimal;
//-------------------------------------------------------------- debug (visualisierung)--------------------------------------------------------------------------------------------
class _weltdebug;



//#include <_struktur.hpp>
//#include <_vektor.hpp>
//#include <_grafik.hpp>
//#include <_bild.hpp>
class _weltdebugpunkt;
class _weltdebugkreuz;
class _weltdebuglinie;
class _weltdebugebene;
class _weltdebugkugel;
class _weltdebugzylinder;
class _weltdebugpfeil;
class _weltdebugtext;
class _weltdebugschirm;
class _weltdebugschirmtext;
class _weltdebugzeichensatz;
class _weltdebugzeichensatzchar;
class _weltdebugzeichensatzseg;
//#include <_weltpolygon.hpp>
#include <_weltfeld.hpp>
#include <_weltkomponente.hpp>
#include <_weltpartition.hpp>
#include <_weltpartikel.hpp>
#include <_weltfigur.hpp>
//#include <_weltoptik.hpp>
#include <_weltnetz.hpp>
#include <_weltmaterial.hpp>
//#include <_weltgeometrie.hpp>
//#include <_weltintersektion.hpp>
//#include <ode.h>


//******************************************************************************************************************************************************************************************************
//                                                              Z Y K L I S C H E 
//******************************************************************************************************************************************************************************************************
class _geometrie;
class _intersektion;
class _verbinderisintro;
//******************************************************************************************************************************************************************************************************
//                                                              W E L T 
//******************************************************************************************************************************************************************************************************
//                                                              zentrales konzept der grundplatte, welches sämtliche geometrischen Repräsenationsformen
//                                                              beherrscht. Diese sind : geometrien, drahtgitterapproximationen, sektordaten
//                                                              die welt besteht aus vier Listen (vom typ _geometrie,_netz,_sektor,_zone) und einem Vektorraum
//                                                              sie enthält weiter eine camera-Liste 
//                                                              operationsschnittstelle ist im wesentlichen:
//                                                              * animieren (mit hilfe der _basis::_animable - Klassen) 
//                                                              * zeichnen, transformieren
//                                                              * speichern (mit hilfe der _basis::_speicherbar - Klassen)
//                                                              * editieren (mit hilfe der _basis::_editierbar - Klassen)
//                                                              * compilieren (um sektordaten und sichtbarkeit zu ermitteln)
//                                                              * sektororientierte Operationen wie sektordetermination
//******************************************************************************************************************************************************************************************************

//**************DEBUG ****************
//extern _welt*W;
//************************************
void weltspeichernbinaer(_zeichenkette<char> fn,_welt*w);
void weltladenbinaer(_zeichenkette<char> fn,_welt*&w,_texturverwaltung<_tb>*tv);
void weltspeichern(_zeichenkette<char> fn,_welt*w);
void weltladen(_zeichenkette<char> fn,_liste<_welt >*lw);


class _welt:
public _listebasis<_geometrie>,
public _listebasis<_netz>,
public _listebasis<_kugel>,
public _listebasis<_partikel >,
public _listebasis<_partikelquelle>, 
public _listebasis<_sprite>,
public _listebasis<_figur>,
public _listebasis<_kamera<_tg> >,
public _listebasis<_licht<_tg,_to> >,
public _listebasis<_schatten<_tg,_to> >,
public _listebasis<_gravitation<_tg> >,
public _listebasis<_feldelektrostatisch<_tg> >,
public _listebasis<_feldmagnetostatisch<_tg> >,
public _listebasis<_textur<_tb> >,
public _listebasis<_partition::_zone>,
public _listebasis<_weltdebug>,
public _basis::_speicherbarargument<_welt>,
public _speicherbarbinaer,
public _material<_tg>
{
        public:
        using _listebasis<_geometrie >           ::anfang;
        using _listebasis<_netz >                ::anfang;
        using _listebasis<_kugel>                ::anfang;
        using _listebasis<_partikelquelle >      ::anfang;
        using _listebasis<_partikel>             ::anfang;
        using _listebasis<_sprite >              ::anfang;
        using _listebasis<_figur >               ::anfang;
        using _listebasis<_kamera<_tg> >         ::anfang;
        using _listebasis<_textur<_tb> >         ::anfang;
        using _listebasis<_licht<_tg,_to> >      ::anfang;
        using _listebasis<_schatten<_tg,_to> >   ::anfang;
        using _listebasis<_gravitation<_tg> >    ::anfang;
        using _listebasis<_feldelektrostatisch<_tg> >    ::anfang;
        using _listebasis<_feldmagnetostatisch<_tg> >    ::anfang;
        using _listebasis<_partition::_zone >    ::anfang;
        using _listebasis<_weltdebug >           ::anfang;
        using _listebasis<_geometrie >           ::naechstes;
        using _listebasis<_netz >                ::naechstes;
        using _listebasis<_kugel>                ::naechstes;
        using _listebasis<_partikelquelle >      ::naechstes;
        using _listebasis<_partikel>             ::naechstes;
        using _listebasis<_sprite >              ::naechstes;
        using _listebasis<_figur >               ::naechstes;
        using _listebasis<_kamera<_tg> >         ::naechstes;
        using _listebasis<_textur<_tb> >         ::naechstes;
        using _listebasis<_licht<_tg,_to> >      ::naechstes;
        using _listebasis<_schatten<_tg,_to> >   ::naechstes;
        using _listebasis<_gravitation<_tg> >    ::naechstes;
        using _listebasis<_feldelektrostatisch<_tg> >    ::naechstes;
        using _listebasis<_feldmagnetostatisch<_tg> >    ::naechstes;
        using _listebasis<_partition::_zone >    ::naechstes;
        using _listebasis<_weltdebug >           ::naechstes;
        using _listebasis<_geometrie >           ::vorheriges;
        using _listebasis<_netz >                ::vorheriges;
        using _listebasis<_kugel>                ::vorheriges;
        using _listebasis<_partikelquelle >      ::vorheriges;
        using _listebasis<_partikel>             ::vorheriges;
        using _listebasis<_sprite >              ::vorheriges;
        using _listebasis<_figur >               ::vorheriges;
        using _listebasis<_kamera<_tg> >         ::vorheriges;
        using _listebasis<_textur<_tb> >         ::vorheriges;
        using _listebasis<_licht<_tg,_to> >      ::vorheriges;
        using _listebasis<_schatten<_tg,_to> >   ::vorheriges;
        using _listebasis<_gravitation<_tg> >    ::vorheriges;
        using _listebasis<_feldelektrostatisch<_tg> >    ::vorheriges;
        using _listebasis<_feldmagnetostatisch<_tg> >    ::vorheriges;
        using _listebasis<_partition::_zone >    ::vorheriges;
        using _listebasis<_weltdebug >           ::vorheriges;
        public:
                _welt();
                virtual ~_welt();
                _vektor3<_to>&lichtambient();
                
                void erzeugentexturliste(_liste<_textur<_tb> >*);
                void erzeugentextur();
                void loeschentextur();
                _textur<_tb>* umbiegentexturzeiger(_textur<_tb>*t,_liste<_textur<_tb> >*lt,_liste<_textur<_tb> >*ltn);
                void globalisierentextur(_texturverwaltung<_tb>*tv);
                
                inline bool eigenetransformation()const;
                void eigenetransformation(const bool);
                void transformierenglobal(_grafik*,_kamera<_tg>*);//überläßt der grafikschnittstelle das transformieren
                void transformieren(_grafik*,_kamera<_tg>*,bool);
                void transformieren(_grafik*,_kamera<_tg>*,_tg,_tg,_tg);//parallelansichtstransformation, 3.:skalierung x,4.:skalierung y,5.:skalierung z,
                void transformieren(_grafik*,_kamera<_tg>*,_tg,_tg    );//parallelansichtstransformation, 3.:skalierung xy, 4.: z-festwert
                void transformierensektor(_grafik*,_kamera<_tg>*,_partition::_sektor*);
                void zeichnen(_grafik*,_kamera<_tg>*);
                void zeichnendebug(_grafik*);
                void zeichnenlinie(_grafik*,bool);
                void zeichnensektor(_grafik*,_kamera<_tg>*,_partition::_sektor*);
                void zeichnensprite(_grafik*,_kamera<_tg>*);
                void zeichnenfigur(_grafik*,_kamera<_tg>*);
                void zeichnenfeld(_feld<_tg>*,_grafik*g,bool,const _zeichenkette<char>&text);
                void zeichnenfeld(_feld<_tg>*git,_grafik*grafik,const _tg divi);
                void animieren();
                void animierensprite();
                void animierenfigur(_partition::_zone*,_tastatur*,_maus<_tg>*);
                void animierenpartikelquelle();
                _tg animationsfaktor()const;
                void initialisierenanimation();
                void aktualisieren();
                _vektor3<_tg> gravitation(const _vektor3<_tg>&);
                //allg modellationsschnittstelle
                void intersekt(_netz*,unsigned int);//const
                void intersekt(_netz*);//const
                void deintersekt(_netz*);//const
                void vereinigen(_netz*);//const
                void erzeugentexturraum();
                void loeschentexturraum();
                void erzeugenkante();
                void loeschenkante();
                //operationsschnittstelle für weltenpartitionierung
				virtual ::_liste<_netz >*uebersetzen();
                virtual void unuebersetzen();
				_netz*compileintersection(::_liste<_netz >*);
                void einfuegenpartitionsnetz();
                void anlegenlightmap(_texturverwaltung<_tb>*,const _zeichenkette<char>&);
                void anlegenlightmapzone(_texturverwaltung<_tb>*,_zeichenkette<char>,_tg);
                void bestrahlenlightmap();
                void bestrahlenlightmapzone();
                void uebergebenlightmap(_grafik*);
                void uebergebenlightmapzone(_grafik*);

                //flagfunktionen
                void markierungnetz(int);
                void markierungzone(int);
                void markierunggeometrie(int);
                void markierungkamera(int);
                //elementschnittstelle
                void textur(_textur<_tb>*);                    //textur setzen
                void verwendentextur(bool);                     //textur verwenden ein,aus
                void verwendentexturdynamisch(bool);            //dynamische textur verwenden ein,aus
                void verwendenverbinderfarbe(bool);             //connectorfarbe verwenden ein,aus
                void zeichnenflaeche(bool);                     //flaeche zeichnen ein,aus
                void zeichnenkante(bool);                       //kanten zeichnen ein aus,
                void zeichnennormale(bool);                     //normale zeichnen ein,aus
                void zweiseitig(bool);                          //zweiseitig zeichnen ein,aus
                void maskiert(bool);                            //maskiert zeichnen ein,aus
                void transparenz(bool);                         //transparent zeichnen ein,aus
                void transparenzfaktor(_tg);                    //transparentsfaktor setzen 0..1
                void farbe(const _vektor4<_to>);                 //farbe aller polygone setzen
                void farbekante(const _vektor4<_to>);            //farbe aller kanten setzen
                void farbeverbinder(const _vektor4<_to>);        //farbe aller verbundelemente im netz setzen
                void anwahl(int);                            //selektionsstatus setzen
                void visualisierensektor(bool);                 //sektoren visualisierung ein/aus
                void brechzahl(const _tg);                      //brechzahl der subtraktiven weltatmosphäre setzen
                _tg brechzahl()const;                           //brechzahl der subtraktiven weltatmosphäre lesen
                _tg brechzahldispersiv(const _tg)const;         //wellenlängenabhängige brechzahl der subtraktiven weltatmosphäre liefern
                void dispersionsskalierung(const _tg);          //skalierungskoeffizient für dispersionsrelation
                unsigned int neuemarkierungkollision();         //gibt eine neue polygonmarkierung für die kollisionsoptimierung zurück
                unsigned int zyklus() const;
                unsigned int zykluszeit() const;                
                //zählfunktionen
                void zeit(_zeit*t);
                unsigned int anzahlnetz()const;
                unsigned int anzahlpolygon()const;
                unsigned int anzahlvertex()const;
                unsigned int anzahlverbindervertexpolygon()const;
                unsigned int anzahlbildvektor()const;
                unsigned int anzahlzone()const;
                unsigned int anzahlbaumknoten()const;
                void anzahlbaumknoten(_partition::_ebene*,unsigned int &)const;
                unsigned int anzahlsektor()const;
                unsigned int anzahlsektorpolygon()const;
                unsigned int anzahlsektorportal()const;
                unsigned int anzahlsektorportalvertex()const;
                unsigned int anzahlsektorsichtbarkeitpolygon()const;
                unsigned int anzahlsektorsichtbarkeitsektor()const;
                //laufzeitmessfunktionen
                unsigned int zeitintersektion() const;
                unsigned int zeitzonenerzeugung() const;
                unsigned int zeitbinaerehalbraumteilung() const;
                unsigned int zeitsektorerzeugung() const;
                unsigned int zeitsektorverbindung() const;
                unsigned int zeitsichtbarkeit() const;
                unsigned int zeitloeschennichtportalvertex() const;
                unsigned int zeitbestrahlung() const;
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_welt>*);
                void speichern(_speicherbardynamisch<_welt>*);
                char assoziieren(_speicherbardynamisch<_welt>*);

                bool laden(_dateispeicherbarbinaer*d);
				void speichern(_dateispeicherbarbinaer*d);
                bool assoziieren();

				
				//*** DEBUG*******
                _weltdebugzeichensatz*debugzeichensatz();
                virtual void uebersetzen0();
                virtual void uebersetzen1();
                void debuggenintersektion(const bool b);
                bool debuggenintersektion()const;
                void debuggensektor(const bool b);
                bool debuggensektor()const;
                void debuggenbsp(const bool b);
                bool debuggenbsp()const;
                void debuggenportal(const bool b);
                bool debuggenportal()const;
                void debuggensichtbarkeit(const bool b);
                bool debuggensichtbarkeit()const;
                void debugmaus(_maus<_tg>*);
                _maus<_tg>*debugmaus();
                void debuggrafik(_grafik*);
                _grafik*debuggrafik();
                void debugtastatur(_tastatur*);
                _tastatur*debugtastatur();
                void debugsystem(_system*);
                _system*debugsystem();
                //****************
        private:
                char erzeugennetz();
                unsigned int erzeugenzone();
                void erzeugenzonenpartition();
                void erzeugenzonenpartition(_partition::_zone*,_partition::_ebene*,bool,_liste<_partition::_polygon >*);
                void erzeugenzonenpartition(_liste<_partition::_polygon >*,_listenknoten<_partition::_polygon >*,_liste<_partition::_polygon >*,_liste<_partition::_polygon >*);
                void polygonoptimaleteilung(_liste<_partition::_polygon >*,_listenknoten<_partition::_polygon >*&);
                void erzeugenzonensektor();
                void verbindenzonesektor();
                void erzeugenzonensichtbarkeit();
                void loeschenzonenichtportalvertex();
                void einfuegenlichtinsektor();
        public://!!!!!!!!!!!!!!!! public nur zum spielen                
                void erzeugenvertexlicht();
                void einfuegenlichtaussektor();
        private:
                _netz*ptm;
                _weltdebugzeichensatz*pdbfont;
                unsigned int ptime[30];
                unsigned int pzyklus;
                unsigned int paltezeit;
                unsigned int pzykluszeit;
                _zeit*ptimer;
                unsigned int pmarkierungkollision;
                _vektor3<_to> plichtambient;
                _tg pbrechzahl;
                _tg pdispersionsskalierung;
                bool peigenetransformation;
                _tg panimationsfaktor;
                _maus<_tg>*pdbmo;
                _grafik*pdbgra;
                _tastatur*pdbtas;
                _system*pdbsystem;
                bool pdbintersektion;
                bool pdbsektor;
                bool pdbbsp;
                bool pdbportal;
                bool pdbsichtbarkeit;                
        private:
				_liste<_textur<_tb> > ptexturliste;
				_liste<_textur<_tb> > ptexturlisteneu;        
        public:
               // unsigned int schattenbild;
                //dWorldID odewelt;   
                //dSpaceID odespace;             
                
                
                
};
bool _welt::eigenetransformation()const{
                                                                return(peigenetransformation);
};
//******************************************************************************************************************************************************************************************************
//                                                              B E W E R T U N G P O L Y G O N O P T I M A L 
//******************************************************************************************************************************************************************************************************

class _bewertungpolygonoptimal:public _listenknotenbasissortiert<_bewertungpolygonoptimal,_tg>{
        friend class _welt;
        private:
                _bewertungpolygonoptimal(_listebasis<_bewertungpolygonoptimal >*,_tg,_listenknoten<_partition::_polygon >*,_tg,_tg,_tg);
                virtual ~_bewertungpolygonoptimal();
        private:
                _tg pkriterium;
                _tg anzahlvorne;
                _tg anzahlhinten;
                _tg zerteilung;
                _listenknoten<_partition::_polygon >*listnode;
};
//******************************************************************************************************************************************************************************************************
//                                                              D R E I E C K
//******************************************************************************************************************************************************************************************************

class _dreieck:public _listenknotenbasis<_dreieck >{
        public:
                _dreieck(_polygon*,_vertex*,_vertex*,_vertex*);
                virtual ~_dreieck();
                inline void markierung(int);
                inline int markierung() const;
                void markierungvertex(int);
                void aktualisieren();
        private:
                _vertex*pvertex[3];
                _kantedreieck*pedge[3];
                _polygon*ppolygon;
                int pflag;

};


//******************************************************************************************************************************************************************************************************
//                                                              K A N T E D R E I E C K
//******************************************************************************************************************************************************************************************************

class _kantedreieck{
        public:
                _kantedreieck(_dreieck*,_dreieck*,_vertex*,_vertex*);
                virtual ~_kantedreieck();
                inline void markierung(int);
                inline int markierung() const;
                void invertierenvertex();
                void invertierendreieck();
                inline _vertex*vertex(int);
                inline _dreieck*dreieck(int);
        private:
                _dreieck*ptriangle[2];
                _vertex*pvertex[2];
                _vektor3<_tg> pvector;
                int pflag;
};


//******************************************************************************************************************************************************************************************************
//                                                              V E R B I N D E R V E R T E X P O L Y G O N 
//******************************************************************************************************************************************************************************************************
class _verbindervertexpolygon:
public _verbinder<_vertex,_polygon>,
public _texturvektor<_tg>,
public _basis::_speicherbarargument<_verbindervertexpolygon>,
public _speicherbarbinaer{
        friend class _polygon;
        public:
				//using _listenknotenbasis<_verbindervertexpolygon>::naechstes;
				//using _listenknotenbasis<_verbindervertexpolygon>::vorheriges;
        public:
                _verbindervertexpolygon(_vertex*,_polygon*);
                virtual ~_verbindervertexpolygon();
                inline _polygon*polygon();
                inline _vertex*vertex();
                inline _vertex*naechstervertex();
                inline _vertex*vorherigervertex();
               // void naechstervertex(_vertex*);
               // void polygon(_polygon*);
                bool verknuepfen();
                void blockzeiger(_tg*);
                void blockort(const _vektor3<_tg>&);
                void blocknormale(const _vektor3<_tg>&);
                _verbindervertexpolygon*gegenkante();
                inline int markierung()const;
                inline void markierung(int);
                inline unsigned int kollisionszaehler()const;
                inline void kollisionszaehler(unsigned int);
                void multiplizierenfarbe(const _to f);
                void berechnenlicht(_licht<_tg,_to>*l,_polygon*poly);
                void aktualisierenlichtergebnis();
                void farbe(const _vektor4<_to>&);
                void farbe(const _vektor3<_to>&);
                void opazitaet(const _tg o);
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_verbindervertexpolygon>*);
                void speichern(_speicherbardynamisch<_verbindervertexpolygon>*);
                char assoziieren(_speicherbardynamisch<_verbindervertexpolygon>*);
                bool laden(_dateispeicherbarbinaer*d);
				void speichern(_dateispeicherbarbinaer*d);
                bool assoziieren();

        public:                
                _vektor4<_to> farbe() const;
        private:
                //_polygon*ppolygon;
                
                
                
                
                _verbindervertexpolygon*pgegenkante;
                _vektor4<_to> pcolor;
                int pflag;
                unsigned int pkollisionszaehler;
                //block zeiger
                _tg*pblockzeiger;
public:
                _vertex*pnextvertex;//nur temporär zur konversion
                
                
};
_vertex*_verbindervertexpolygon::vertex(){
                                                                return(_listenknoten<_vertex>::objekt());
};

_polygon*_verbindervertexpolygon::polygon(){
                                                                return(_listenknoten<_polygon>::objekt());
};
_vertex*_verbindervertexpolygon::naechstervertex(){
                                                                return(_listenknoten<_vertex>::naechstes()->objekt());
};
_vertex*_verbindervertexpolygon::vorherigervertex(){
                                                                return(_listenknoten<_vertex>::vorheriges()->objekt());
};

/*
_vertex*_verbindervertexpolygon::naechstervertex(){
                                                                return(pvertexnext);
};
*/
int _verbindervertexpolygon::markierung()const{
                                                                return(pflag);
};
void _verbindervertexpolygon::markierung(int f){
                                                                pflag=f;
};
unsigned int _verbindervertexpolygon::kollisionszaehler()const{
                                                                return(pkollisionszaehler);
};
void _verbindervertexpolygon::kollisionszaehler(unsigned int i){
                                                                pkollisionszaehler=i;
};

//******************************************************************************************************************************************************************************************************
//                                                              V E R T E X 
//******************************************************************************************************************************************************************************************************
class _vertex:
public _listenknotenbasis<_vertex>,
private _vektor3<_tg>,
public _liste<_polygon>,
public _basis::_speicherbarargument<_vertex>,
public _speicherbarbinaer,
public _editierbar{
        public:
		        using _liste<_polygon>::anfang;
		        using _liste<_polygon>::ende;
		        using _liste<_polygon>::naechstes;
		        using _liste<_polygon>::vorheriges;
				using _liste<_polygon>::anzahl;
        public:
                _vertex(_netz*,_vektor3<_tg>&);
                virtual ~_vertex();
                
                void aktualisierenblockort();
                void aktualisierenblocknormale();
                
                inline const _vektor3<_tg>&ort() const;
                inline void ort(const _vektor3<_tg>&);
                inline void ort(_tg,_tg,_tg);
                void rotierenx(const _tg w);
                void rotiereny(const _tg w);
                void rotierenz(const _tg w);
                inline _tg operator[](const unsigned int) const;//loesst nach dem vektor-operator auf
                void opazitaetverbinder(const _to o);
                            
                inline void orttransformation(const _vektor3<_tg>&);
                inline void ortparameter(const _vektor3<_tg>&);
                inline void normale(const _vektor3<_tg>&);
                void aktualisiereninterpoliertenormale();
                inline _vektor3<_tg>&orttransformation();
                inline _vektor3<_tg>&ortparameter();
                inline _vektor3<_tg>&normale();
                inline _tg alpha()const;
                inline _tg beta()const;
                inline _tg gamma()const;
                //flagging
                inline void markierung(int);
                inline int markierung() const;
                void markierungverbinder(int);
                //struktur
                inline _vertex*naechstes(const _polygon*);
                inline _vertex*vorheriges(const _polygon*);
                _verbindervertexpolygon*verbinder(const _polygon*);
                _netz*netz();
                //ism-supply
                void erzeugenintersektionsverbinder(_netz*,_polygon*);
                void loeschenintersektionsverbinder();
                _intersektion*intersektion();
                inline void status(int);
                inline int status() const;
                _listebasis<_verbinderisintro >*verbinderisintroliste();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_vertex>*);
                void speichern(_speicherbardynamisch<_vertex>*);
                char assoziieren(_speicherbardynamisch<_vertex>*);
                bool laden(_dateispeicherbarbinaer*d);
				void speichern(_dateispeicherbarbinaer*d);
                bool assoziieren();
                //edition
                virtual void einhaengendialog(_dynamischerdialog*);
                virtual void auslesendialog(_dynamischerdialog*);
        private:
                int pflag;
                _vektor3<_tg> ptransformed;
                _vektor3<_tg> pparameter;
                _vektor3<_tg> pnormale;
                //*************************** ISM supply *******************
                _listebasis<_verbinderisintro > plistisintroconnector;
                _intersektion*pintersection;
                int pstatus;
};

const _vektor3<_tg>&_vertex::ort()const{
                                                                return(*this);
};
void _vertex::ort(const _vektor3<_tg>&o){
                                                                _vektor3<_tg>::setzen(o);
                                                                aktualisierenblockort();
};
void _vertex::ort(_tg x,_tg y,_tg z){
                                                                _vektor3<_tg>::setzen(x,y,z);
                                                                aktualisierenblockort();
};

void _vertex::orttransformation(const _vektor3<_tg>&p){
                                                                ptransformed=p;
};

void _vertex::ortparameter(const _vektor3<_tg>&p){
                                                                pparameter=p;
};

void _vertex::normale(const _vektor3<_tg>&n){
                                                                pnormale=n;
                                                                aktualisierenblocknormale();
};                                                                
_tg _vertex::operator[](const unsigned int i)const{
                                                                return(_vektor3<_tg>::holen(i));
};
_vektor3<_tg>&_vertex::orttransformation(){
                                                                return(ptransformed);
};
_vektor3<_tg>&_vertex::ortparameter(){
                                                                return(pparameter);
};
_vektor3<_tg>&_vertex::normale(){
                                                                return(pnormale);
};
_tg _vertex::alpha()const{
                                                                return(pparameter[0]);
};
_tg _vertex::beta()const{
                                                                return(pparameter[1]);
};
_tg _vertex::gamma()const{
                                                                return(pparameter[2]);
};

void _vertex::markierung(int f){
                                                                pflag=f;
};

int _vertex::markierung() const{
                                                                return(pflag);
};

_vertex*_vertex::naechstes(const _polygon*p){
                                                                _verbindervertexpolygon*it;
                                                                //-------------------------------------
                                                                it=verbinder(p);
                                                                if(it){
                                                                 return(it->naechstervertex());
                                                                }else{
                                                                 return(this);
                                                                };
};

_vertex*_vertex::vorheriges(const _polygon*p){
                                                                _verbindervertexpolygon*it;
                                                                //----------
                                                                it=verbinder(p);
                                                                if(it){
                                                                 return(it->vorherigervertex());
                                                                }else{
                                                                 return(this);
                                                                };
};
void _vertex::status(int s){
                                                                pstatus=s;
};

int _vertex::status() const{
                                                                return(pstatus);
};

//******************************************************************************************************************************************************************************************************
//                                                              K U G E L S C H A T T E N
//******************************************************************************************************************************************************************************************************
class _kugelschatten:public _schatten<_tg,_to>,public _listenknotenbasis<_kugelschatten>{
        public:
                _kugelschatten(_kugel*,_listebasis<_schatten<_tg,_to> >*schattenliste,_licht<_tg,_to>*,_tg);
                virtual ~_kugelschatten();
                virtual void opazitaet(const _to);
                virtual void zeichnen(_grafik*);
                virtual void zeichnendebug(_grafik*);
                virtual void aktualisieren();
        private:
                _kugel*pkugel;                     //besitzer
                _liste<_vektor3<_tg> > pquadstrip; //quadstrip repräsentation
                _liste<_vektor3<_tg> > pquado;
                _liste<_vektor3<_tg> > pquadu;
};
//******************************************************************************************************************************************************************************************************
//                                                              K U G E L
//******************************************************************************************************************************************************************************************************
class _kugel:public _listenknotenbasis<_kugel>,public _listebasis<_kugelschatten>,public _speicherbarbinaer{
        public:
                using _listebasis<_kugelschatten>::anfang;
                using _listebasis<_kugelschatten>::naechstes;
                using _listebasis<_kugelschatten>::vorheriges;
        public:
                _kugel(_welt*w,_listebasis<_kugel>*,const _vektor3<_tg>,const _tg,const _vektor4<_to>,unsigned int );
                virtual ~_kugel();
                void erzeugenschatten(_licht<_tg,_to>*,_tg);
                void loeschenschatten();
                _vektor3<_tg> transformieren(const _vektor3<_tg>&);
                void setzenstandardausrichtung();
                void rotierenabsolut(const _vektor3<_tg>&a,const _tg winkel);
                void rotieren(const _vektor3<_tg>&a,const _tg winkel);
                
                virtual void zeichnen(_grafik*);
                virtual void zeichnenschatten(_grafik*);
                virtual void zeichnenschatten(_grafik*,_licht<_tg,_to>*);
                void anfangschatten();
                void naechsterschatten();
                _vektor3<_tg> ort()const;
                void ort(const _vektor3<_tg>&);
                _vektor4<_to> farbe()const;
                void farbe(const _vektor4<_to>&);
                void radius(const _tg);
                _tg radius()const;
                unsigned int aufloesung()const;
                void aktualisieren();
				//speicherung
                bool laden(_dateispeicherbarbinaer*d);
				void speichern(_dateispeicherbarbinaer*d);
                bool assoziieren();
        private:
                _welt*pwelt;
                _kugelschatten*pschatteniterator;
                _tg pradius;
                _vektor3<_tg> port;      
                _vektor3<_tg> pvektor[3];
                _vektor4<_to> pfarbe;     
                _licht<_tg,_to>*plicht[2];  
                _vektor3<_tg> vl0;
                _vektor3<_tg> vl1;
                   
                unsigned int paufloesung;
};
//******************************************************************************************************************************************************************************************************
//                                                              W E L T D E B U G 
//******************************************************************************************************************************************************************************************************

class _weltdebug:public _listenknotenbasis<_weltdebug >{
        public:
                _weltdebug(_welt*,const _vektor4<_to>);
                virtual ~_weltdebug();
                void farbe(const _vektor4<_to>);
                _vektor4<_to> farbe() const;
                _welt*welt();
                virtual void transformieren(_grafik*,_kamera<_tg>*)=0;
                virtual void zeichnen(_grafik*)=0;
                virtual void animieren()=0;
        private:
                _welt*pworld;
                _vektor4<_to> pcolor;
                
};


//******************************************************************************************************************************************************************************************************
//                                                              W E L T D E B U G P U N K T
//******************************************************************************************************************************************************************************************************

class _weltdebugpunkt:public _weltdebug{
        public:
                _weltdebugpunkt(_welt*,const _vektor3<_tg>,const _vektor4<_to>);
                virtual ~_weltdebugpunkt();
                virtual void transformieren(_grafik*,_kamera<_tg>*);
                virtual void zeichnen(_grafik*);
                virtual void animieren();
                void ort(const _vektor3<_tg>);
                _vektor3<_tg> ort() const;
        private:
                _vektor3<_tg> plocus;
                _vektor3<_tg> plocusperspective;
};

//******************************************************************************************************************************************************************************************************
//                                                              W E L T D E B U G L I N I E 
//******************************************************************************************************************************************************************************************************

class _weltdebuglinie:public _weltdebug{
        public:
                _weltdebuglinie(_welt*,const _vektor3<_tg>,const _vektor3<_tg>,const _vektor4<_to>);
                virtual ~_weltdebuglinie();
                virtual void transformieren(_grafik*,_kamera<_tg>*);
                virtual void zeichnen(_grafik*);
                virtual void animieren();
                void ort(const unsigned int,const _vektor3<_tg>);
                _vektor3<_tg> ort(const unsigned int) const;
        private:
                _vektor3<_tg> plocus[2];
                _vektor3<_tg> plocusperspective[2];
                        
};


//******************************************************************************************************************************************************************************************************
//                                                              W E L T D E B U G E B E N E
//******************************************************************************************************************************************************************************************************

class _weltdebugebene:public _weltdebug{
        public:
                _weltdebugebene(_welt*,const _vektor3<_tg>,const _vektor3<_tg>,const _vektor3<_tg>,const _tg,const _vektor4<_to>);
                virtual ~_weltdebugebene();
                virtual void transformieren(_grafik*,_kamera<_tg>*);
                virtual void zeichnen(_grafik*);
                virtual void animieren();
                void ort(const _vektor3<_tg>);
                _vektor3<_tg> ort() const;
        private:
                _vektor3<_tg> plocus;
                _vektor3<_tg> pvec0;
                _vektor3<_tg> pvec1;
                _tg plen;
                _liste<_vektor3<_tg> > plist;
                _liste<_vektor3<_tg> > pplist;
                        
};

//******************************************************************************************************************************************************************************************************
//                                                              W E L T D E B U G K U G E L 
//******************************************************************************************************************************************************************************************************

class _weltdebugkugel:public _weltdebug{
        public:
                _weltdebugkugel(_welt*,const _vektor3<_tg>,const _tg,const _vektor4<_to>);
                virtual ~_weltdebugkugel();
                void aktualisieren();
                virtual void transformieren(_grafik*,_kamera<_tg>*);
                virtual void zeichnen(_grafik*);
                virtual void animieren();
                void ort(const _vektor3<_tg>);
                _vektor3<_tg> ort() const;
                void radius(const _tg);
                _tg radius()const;
                void drehimpuls(const _vektor3<_tg>);
                void addierendrehimpuls(const _vektor3<_tg>);
                void multiplizierendrehimpuls(const _tg);
        private:
                _tg plocus[3];
                _tg plocuspersective[3];
                _tg pnormale[3];
                _tg prichtung[2][3];
                _tg pdrehimpuls[3];
                _tg ppunkt[4000][3];
                _tg ppunktpers[4000][3];
                _vektoranalysis3<_tg> V3;
                _tg pradius;
                unsigned int ppunktanzahl;
};

//******************************************************************************************************************************************************************************************************
//                                                              W E L T D E B U G Z Y L I N D E R
//******************************************************************************************************************************************************************************************************

class _weltdebugzylinder:public _weltdebug{
        public:
                _weltdebugzylinder(_welt*,const _vektor3<_tg>,const _vektor3<_tg>, const _tg,const _vektor4<_to>);
                virtual ~_weltdebugzylinder();
                virtual void aktualisieren();
                virtual void transformieren(_grafik*,_kamera<_tg>*);
                virtual void zeichnen(_grafik*);
                virtual void animieren();
                void ort(const _vektor3<_tg>);
                _vektor3<_tg> ort() const;
                void vektor(const _vektor3<_tg>);
                _vektor3<_tg> vektor() const;                
        private:
                _vektor3<_tg> plocus;
                _vektor3<_tg> plocuspersective;
                _vektor3<_tg> pvektor;
                _vektor3<_tg> pnormale;
                _vektor3<_tg> prichtung[2];
                _vektor3<_tg> ppunkt[4000];
                _vektor3<_tg> ppunktpers[4000];
                _vektoranalysis3<_tg> V3;
                _tg pradius;
                unsigned int ppunktanzahl;
};

//******************************************************************************************************************************************************************************************************
//                                                              W E L T D E B U G P F E I L
//******************************************************************************************************************************************************************************************************

class _weltdebugpfeil:public _weltdebug{
        public:
                _weltdebugpfeil(_welt*,const _vektor3<_tg>,const _vektor3<_tg>,const _tg,const _tg,const _vektor4<_to>);
                virtual ~_weltdebugpfeil();
                virtual void transformieren(_grafik*,_kamera<_tg>*);
                virtual void zeichnen(_grafik*);
                virtual void animieren();
                void ort(const unsigned int,const _vektor3<_tg>&);
                void ort(const _vektor3<_tg>&p0,const _vektor3<_tg>&p1);
                _vektor3<_tg> ort(const unsigned int) const;
        private:
                void aktualisieren();
        private:
                _vektor3<_tg> plocus[2];
                _vektor3<_tg> plocusperspective[2];
                _vektor3<_tg> parrs[4];
                _vektor3<_tg> parrsperspective[4];
                _vektor4<_to> pcolor2;
                _vektor4<_to> pcol0;
                _vektor4<_to> pcol1;
                _tg plaenge;
                _tg pbreite;
                        
};

//******************************************************************************************************************************************************************************************************
//                                                              W E L T D E B U G K R E U Z
//******************************************************************************************************************************************************************************************************

class _weltdebugkreuz:public _weltdebug{
        public:
                _weltdebugkreuz(_welt*,const _vektor3<_tg>,const _tg,const _vektor4<_to>);
                virtual ~_weltdebugkreuz();
                virtual void transformieren(_grafik*,_kamera<_tg>*);
                virtual void zeichnen(_grafik*);
                virtual void animieren();
                void ort(const _vektor3<_tg>);
                _vektor3<_tg> ort() const;
        private:
                void aktualisieren();
        private:
                _vektor3<_tg> plocus;
                _vektor3<_tg> plocusperspective;
                _vektor3<_tg> pnetz[8];
                _vektor3<_tg> pnetzperspective[8];
                _tg pradius;
                        
};

//******************************************************************************************************************************************************************************************************
//                                                              W E L T D E B U G T E X T 
//******************************************************************************************************************************************************************************************************

class _weltdebugtext:public _weltdebug{
        public:
                _weltdebugtext(_welt*,const _zeichenkette<char>,const _vektor2<_tg>,const _vektor4<_to>);
                _weltdebugtext(_welt*,const _zeichenkette<char>,const _vektor3<_tg>,const _vektor3<_tg> ,const _vektor3<_tg>,const _vektor4<_to>);
                virtual ~_weltdebugtext();
                virtual void transformieren(_grafik*,_kamera<_tg>*);
                virtual void zeichnen(_grafik*);
                
                virtual void animieren();
                void ort(const _vektor3<_tg>);
                _vektor3<_tg> ort() const;
                void text(const _zeichenkette<char>&);
                void text(const int);
        private:
                void clearlocusperspectivelist();
                virtual void zeichnen2d(_grafik*);
        private:
                _vektor3<_tg> plocus;
                _vektor3<_tg> pa;
                _vektor3<_tg> pb;
                _zeichenkette<char> ptext;
                _liste<_liste<_vektor3<_tg> > > plocuspers;
                bool pzeichnen2d;
                        
};

//******************************************************************************************************************************************************************************************************
//                                                              W E L T D E B U G S C H I R M
//******************************************************************************************************************************************************************************************************

class _weltdebugschirm:public _weltdebug{
        friend class _weltdebugschirmtext;
        public:
                _weltdebugschirm(_welt*,const _vektor3<_tg>,const _vektor3<_tg>,_tg,_tg,const _vektor4<_to>);
                virtual ~_weltdebugschirm();
                virtual void transformieren(_grafik*,_kamera<_tg>*);
                virtual void zeichnen(_grafik*);
                virtual void animieren();
                void ort(const _vektor3<_tg>,const _vektor3<_tg>);
                _vektor3<_tg> ort(const unsigned int) const;
                void loeschen();
                void schreiben(const _zeichenkette<char>);
                void schreiben(const _zeichenkette<char>,const int);
                void schreiben(const _zeichenkette<char>,const double);
                void schreiben(const _zeichenkette<char>,const _vektor3<_tg>);
                void schreiben(const _zeichenkette<char>,const _vektor4<_to>);
                void schreiben(const _zeichenkette<char>,const int,const _vektor4<_to>);
                void schreiben(const _zeichenkette<char>,const double,const _vektor4<_to>);
                void schreiben(const _zeichenkette<char>,const _vektor3<_tg>,const _vektor4<_to>);
        private:
                _vektor3<_tg> plocus[2];
                _tg psx;
                _tg psy;
                _tg pyoffs;
                _tg pxoffs;
                _listebasis<_weltdebugschirmtext > ptextlist;
                        
};

//******************************************************************************************************************************************************************************************************
//                                                              W E L T D E B U G S C H I R M T E X T 
//******************************************************************************************************************************************************************************************************

class _weltdebugschirmtext:public _listenknotenbasis<_weltdebugschirmtext >{
        friend class _weltdebugschirm;
        private:
                _weltdebugschirmtext(_weltdebugschirm*,_listebasis<_weltdebugschirmtext >*,_zeichenkette<char>,_vektor4<_to>);
                virtual ~_weltdebugschirmtext();
                virtual void transformieren(_grafik*,_kamera<_tg>*,_vektor3<_tg>&);
                virtual void zeichnen(_grafik*,const _vektor3<_tg>&);
        private:
                void clearlocusperspectivelist();
        private:
                _zeichenkette<char> ptext;
                _vektor4<_to> pcolor;
                _liste<_liste<_vektor3<_tg> > > plocuspers;
                _weltdebugschirm*pscreen;

};

//******************************************************************************************************************************************************************************************************
//                                                              W E L T D E B U G Z E I C H E N S A T Z
//******************************************************************************************************************************************************************************************************

class _weltdebugzeichensatz{
        friend class _welt;
        friend class _weltdebugzeichensatzchar;
        friend class _weltdebugzeichensatzseg;
        private:
                _weltdebugzeichensatz(_welt*);                
                virtual ~_weltdebugzeichensatz();
                void init();
                void loeschen();
        public:                        
                _weltdebugzeichensatzchar*character(int);
        private:
                _weltdebugzeichensatzchar*cot[256];
                _welt*pworld;
                float scale;
                float height;
};

//******************************************************************************************************************************************************************************************************
//                                                              W E L T D E B U G Z E I C H E N S A T Z C H A R
//******************************************************************************************************************************************************************************************************

class _weltdebugzeichensatzchar:public _listebasis<_weltdebugzeichensatzseg >{
        friend class _weltdebugzeichensatz;
        friend class _weltdebugzeichensatzseg;
        
        private:
                _weltdebugzeichensatzchar(_weltdebugzeichensatz*,int,_tg);
                virtual ~_weltdebugzeichensatzchar();
        public:
                _tg breite() const;
        private:
                _weltdebugzeichensatz*pfont;
                int pindex;
                _tg pwx;
};


//******************************************************************************************************************************************************************************************************
//                                                              W E L T D E B U G Z E I C H E N S A T Z S E G
//******************************************************************************************************************************************************************************************************

class _weltdebugzeichensatzseg:public _listenknotenbasis<_weltdebugzeichensatzseg >{
        friend class _weltdebugzeichensatz;
        friend class _weltdebugzeichensatzchar;
        public:
        using _listenknotenbasis<_weltdebugzeichensatzseg >::einhaengen;
        private:
                _weltdebugzeichensatzseg(_weltdebugzeichensatzchar*);
                virtual ~_weltdebugzeichensatzseg();
        public:                
                _liste<_vektor2<_tg> >*liste();
                void einhaengen(_tg,_tg);
                void einhaengen(_tg,_tg,_tg,_tg);
                void einhaengen(_tg,_tg,_tg,_tg,_tg,_tg);
                void einhaengen(_tg,_tg,_tg,_tg,_tg,_tg,_tg,_tg);
        private:
                _weltdebugzeichensatzchar*pchar;
                _vektor2<_tg> pvo;
                _vektor2<_tg> pvd;
                _liste<_vektor2<_tg> > plist;
};



#endif

