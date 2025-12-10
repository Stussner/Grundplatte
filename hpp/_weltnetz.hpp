//******************************************************************************************************************************************************************************************************
//  Projekt      : grundplatte
//  Bibliothek   : grundplatte.lib
//  Modul        : _weltnetz.hpp
//  Datum        : 16.5.2005
//  Beschreibung : 
//******************************************************************************************************************************************************************************************************
#ifndef _weltdrahtgitterh_included
#define _weltdrahtgitterh_included

#include <_struktur.hpp>
#include <_vektor.hpp>
#include <_datei.hpp>
#include <_grafik.hpp>
#include <_weltpartition.hpp>
#include <_weltmaterial.hpp>
//******************************************************************************************************************************************************************************************************
//                                                              P R E D E K L A R A T I O N 
//******************************************************************************************************************************************************************************************************
class _netz;
class _netzschatten;
//******************************************************************************************************************************************************************************************************
//                                                              Z Y K L I S C H E 
//******************************************************************************************************************************************************************************************************
 class _welt;
 class _polygon;
 class _vertex;
 class _verbindervertexpolygon;
template<class _tg                    > class _kamera;
 class _intersektion;


//******************************************************************************************************************************************************************************************************
//                                                              N E T Z S C H A T T E N
//******************************************************************************************************************************************************************************************************
class _netzschatten:public _schatten<_tg,_to>,public _listenknotenbasis<_netzschatten>{
        public:
                _netzschatten(_netz*,_listebasis<_schatten<_tg,_to> >*schattenliste,_licht<_tg,_to>*,_tg);
                virtual ~_netzschatten();
                virtual void opazitaet(const _to);
                virtual void zeichnen(_grafik*);
                virtual void zeichnendebug(_grafik*);
                virtual void aktualisieren();
                //_licht<_tg,_to>*licht();
        private:
                _netz*pnetz;                       //besitzer
                _liste<_vektor3<_tg> > pquads; 
                _liste<_liste<_vektor3<_tg> > > ppolysvorne;
                _liste<_liste<_vektor3<_tg> > > ppolyshinten;
};
//******************************************************************************************************************************************************************************************************
//                                                              N E T Z
//******************************************************************************************************************************************************************************************************
class _netz:
        public _listenknotenbasis<_netz >,
        public _listebasis<_polygon >,
        public _listebasis<_vertex>,
        public _listebasis<_netzschatten>,
        public _liste<_partition::_sektor>,
        public _basis::_speicherbarargument<_netz>,
		public _speicherbarbinaer,
        public virtual _editierbar,
        public _material<_tg>{
        
        public:
                using _listebasis<_polygon >::anfang; 
                using _listebasis<_vertex>::anfang; 
				using _liste<_partition::_sektor>::anfang; 
                using _listebasis<_netzschatten >::anfang; 
                using _listenknotenbasis<_netz>::anzahl;
                using _listebasis<_polygon >::anzahl; 
                using _listebasis<_vertex>::anzahl; 
				using _liste<_partition::_sektor>::anzahl; 
                using _listebasis<_netzschatten >::anzahl; 
                using _listenknotenbasis<_netz>::naechstes;
                using _listebasis<_polygon >::naechstes; 
                using _listebasis<_vertex>::naechstes; 
				using _liste<_partition::_sektor>::naechstes; 
                using _listebasis<_netzschatten >::naechstes; 
                using _listenknotenbasis<_netz>::vorheriges;
                using _listebasis<_polygon >::vorheriges; 
                using _listebasis<_vertex>::vorheriges; 
				using _liste<_partition::_sektor>::vorheriges; 
                using _listebasis<_netzschatten >::vorheriges; 
        public:
                _netz();
                virtual ~_netz();
                _welt*welt();
                void welt(_welt*w);
                virtual _netz*duplizieren();
                void vereinigen(_netz*&);
                void transformieren(_grafik*,_kamera<_tg>*,bool);
                void transformieren(_grafik*,_kamera<_tg>*,_tg,_tg,_tg);//parallelansichtstransformation, 3.:skalierung x,4.:skalierung y,5.:skalierung z,
                void transformieren(_grafik*,_kamera<_tg>*,_tg,_tg    );//parallelansichtstransformation, 3.:skalierung xy, 4.: z-festwert
                void zeichnen(_grafik*);
                void zeichnendebug(_grafik*);
                void zeichnenlinie(_grafik*,bool);
                //_tg operator[](const unsigned int)const;
                bool hatintersektion(_liste<_netz >*,_liste<_netz >*);
                bool hatintersektion(_netz*);
                bool innerhalb(_netz*);
                _vertex*_netz::erstervertex();
                _vektor3<_tg> schwerpunkt() const;
                _vektor3<_tg> mitte();
               // void mitte(const _vektor3<_tg>&m);
               // void mitte(const _tg x,const _tg y,const _tg z);
                void umgrenzungsquader(_tg&,_tg&,_tg&,_tg&,_tg&,_tg&)const;
                bool diskret()const;
                //modifikation
                void kopierenparameterinort();
                void kopierenortinparameter();
                virtual void verschiebenvertex(const _vektor3<_tg>);
                void tauschenxy();
                void tauschenxz();
                void tauschenyz();
                void spiegelnx();
                void spiegelny();
                void spiegelnz();
                void rotierenx(const _tg);
                void rotiereny(const _tg);
                void rotierenz(const _tg);
                void rotieren(const _vektor3<_tg>&o,const _vektor3<_tg>&a,const _tg w);
                void rotieren(const _vektor3<_tg>&a,const _tg w);
                void verschiebenzumraster(const _tg r);
                void verschiebennormal(_tg s);
                void skalierenkonisch(const _vektor3<_tg>&ort,const _vektor3<_tg>&vektor,_tg startskalierung,_tg endskalierung);
                void skalieren(const _tg f);
                void skalieren(const _vektor3<_tg>&mitte,const _tg f);
                
                void biegen(const _vektor3<_tg>&origin,const _vektor3<_tg>&rotaxis,const _vektor3<_tg>&waxis,const _tg w);
                void verdrehen(const _vektor3<_tg>&o,const _vektor3<_tg>&a,const _tg w);
                //flagging
                inline void markierung(int);
                inline int markierung() const;
                void markierungkante(int);
                void markierungvertex(int);
                void markierungverbinder(int)const;
                void markierungpolygon(int);
                void markierungpolygon(_polygon*,unsigned int,int);
                void markierungpolygonstatus(int);
                void markierungpolygonanwahl(int);
                void markierungvertexstatus(int);
                void kollisionszaehlerverbinder(unsigned int);
                //elementschnittstelle
                
                bool additiv() const;                                 //modellationsstatus des meshes auslesen
                bool subtraktiv() const;                              //modellationsstatus des meshes auslesen
                void subtraktiv(bool);                                //mopdellationsstatus setzen, invertiert ggf. normalen
                void keinbsp(const bool);                             //teilnahme am bsp ein/aus
                bool keinbsp()const;
                void dynamisch(const bool);                           //dynamische poly ein, aus
                bool dynamisch()const;
                bool zonennetz()const;                                //ist es von einer zone assozieertes netz?

                void schattenvolumen(const bool);                     //erzeugung von schattenvolumen nach übersetzung
                bool schattenvolumen()const;
                void schattenvolumenlaenge(const _tg);
                _tg schattenvolumenlaenge()const;

                void textur(_textur<_tb>*);                           //textur setzen
                void verwendentextur(const bool);                     //textur verwenden ein,aus
                void verwendentexturdynamisch(const bool);            //dynamische textur verwenden ein,aus
                void lightmaptexelgroesse(const _tg);
                void verwendenverbinderfarbe(const bool);             //connectorfarbe verwenden ein,aus
                void zeichnenflaeche(const bool);                     //flaeche zeichnen ein,aus
                void zeichnenkante(const bool);                       //kanten zeichnen ein aus,
                void zeichnennormale(const bool);                     //normale zeichnen ein,aus
                void normaleinterpoliert(const bool);                 //normaleinterpoliert zeichnen ein,aus
                void zweiseitig(const bool);                          //zweiseitig zeichnen ein,aus
                void maskiert(const bool);                            //maskiert zeichnen ein,aus
                void aufgehellt(const bool);                          //aufgehellt zeichnen ein,aus
                void spiegelnd(const bool);                           //spiegelnder ein,aus
                void kollision(const bool);
                void lightmapschattierung(const bool);                //netz senden schatten auf lightmaps ein/aus
                void dynamischschattierend(const bool);               //schattierend ein,aus           
                void dynamischschattiert(const bool);                 //wird netz in der zeichenfunktion dem stencil pass unterworfen  ein,aus
                void transparenz(const bool);                         //transparent zeichnen ein,aus
                void transparenzadditiv(const bool);                  //transparent zeichnen ein,aus
                void transparenzfaktor(_tg);                          //transparentsfaktor setzen 0..1
                void debuggen(const bool);
                void farbe(const _vektor4<_to>);                      //farbe aller polygone setzen
                void farbekante(const _vektor4<_to>);                 //farbe aller kanten setzen
                void farbeverbinder(const _vektor4<_to>);             //farbe aller verbundelemente im netz setzen
                void opazitaetverbinder(const _tg o);                //w komponente aller verbinder setzen
                void multiplizierenfarbeverbinder(const _to f);
                void glanz(const _vektor4<_to>&);                      //glanz aller polygone setzen
                void glanzbreite(const _to);                          //glanzbreite aller polygone setzen
                void emission(const _vektor4<_to>&);                   //emission aller polygone setzen
                void invertieren();                        //alle polynormalen invertiern, invertiert den modellationsstatus
                void invertierenausrichtung(_polygon*,unsigned int);  //nicht empfohlen!
                void anwahl(int);                                     //selektionsstatus setzen
                _tg  brechzahl()const;                                //brechzahl zurückgeben
                void brechzahl(_tg);                                  //brechzahl setzen
                _tg  brechzahldispersiv(const _tg nm)const;           //wellenlängenabhängige brechzahl des meshmediums lesen
                void dispersionsskalierung(_tg);                      //skalierung der dispersionrealtion setzen
                _tg dispersionsskalierung() const;
                void nurkollisionskopplung(const bool);
                bool nurkollisionskopplung()const;
                void nichtspeichern(const bool);
                bool nichtspeichern()const;
                //strukturoperationen
                void verschweissen(_vertex*,_vertex*);
                void einhaengen(_welt*);
                void anlegentexturkoordinaten(unsigned int);//standardkoordinaten
                void verschiebentexturkoordinaten(const _vektor2<_tg>&v,unsigned int);
                void loeschentexturkoordinaten(unsigned int);
                void anlegenlightmap(_texturverwaltung<_tb>*,_zeichenkette<char>,unsigned int,unsigned int);
                void anlegenlightmap(_texturverwaltung<_tb>*,_zeichenkette<char>,_tg);
               // void loeschenlightmap();
                void bestrahlenlightmap();
                void uebergebenlightmap(_grafik*);
                void erzeugenvertexlicht();
                void erzeugenvertexlicht(_licht<_tg,_to>*lit);       //einuzel-beleuchtungspass mit lit
                void erzeugenvertexlicht(_partition::_zone*);
                //schatten
                void erzeugenschatten(_licht<_tg,_to>*,_tg);
                void loeschenschatten();
                void anfangschatten();
                void naechsterschatten();   
                _netzschatten*schatteniterator();  
                void zeichnenschatten(_grafik*,_licht<_tg,_to>*);           
                //kanten    
                void verknuepfenverbindervertexpolygon();            
                void erzeugenkante();
                void loeschenkante();
                //triangles
                void erzeugendreieck();
                void loeschendreieck();
                //block funktionen, für alternative argumentübergabe an grafikschnittstelle
                bool indiziert()const;
                void erzeugenindex();
                void loeschenindex();
                int indexverbinder(_verbindervertexpolygon*);
                //updates            
                void aktualisieren();                                   //aktualisierung der polygone
                void aktualisierenpolygonmitte();
                void aktualisierensektor(_partition::_zone*);           //muss zuerst aufgerufen werden, richtet verbinder auf sektoren ein
                void aktualisierenschatten();                           //aktualisiert beide (netz- und polygonschatten);
                void aktualisierennetzschatten();                       //aktualisiert netzschatten
                void aktualisierenpolygonschatten();                    //aktualisiert polygonschatten
                void aktualisierenbaum();                               //hängt die polygone um im sektorbaum, sektorverbund muss vorher bestehen
                void optimierenpolygonstartvertex();                    //zur besseren lichtstetigkeit beim polygon zeichnen
                //ism - supply
                void erzeugenvertexintersektion();
                void loeschenvertexintersektion();
                void nullintersektionvertices();
                void vorbereitenintersektion();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_netz>*);
                void speichern(_speicherbardynamisch<_netz>*);
                char assoziieren(_speicherbardynamisch<_netz>*);
                bool laden(_dateispeicherbarbinaer*d);
				void speichern(_dateispeicherbarbinaer*d);
                bool assoziieren();
                //edition
                virtual void einhaengendialog(_dynamischerdialog*);
                virtual void auslesendialog(_dynamischerdialog*);
                _vektor3<_tg>&editionort();
                _vektor3<_tg>&editionebene(const unsigned int i);
                //debugging und messung
                unsigned int anzahlvertex();
                unsigned int anzahlverbindervertexpolygon();
                unsigned int anzahlbildvektor();
                unsigned int anzahlpolygon() const;
                unsigned int speicherlast() const;
        private:
                bool psubtractive;
                bool pkeinbsp;                                          //nimmt am bsp teil ?
                bool pdynamisch;
                bool pschattenvolumen;                                  //erzuegt schattenvolumen nach uebersetzung der welt
                _tg pschattenvolumenlaenge;
                int pflag;
                _tg pbrechzahl;
                _tg pdispersionsskalierung;
                bool pnurkollisionskopplung;
                bool pnichtspeichern;
                _welt*pworld;
                _netzschatten*pschatteniterator;
                _vektor3<_tg> peditionort;
                _vektor3<_tg> peditionebene[2];
                //block daten                    
	            //_liste<_vertex> pvertexliste; ist ab jetzt in der basis 
	            unsigned int panzahlverbinder;
	            unsigned int panzahlvertex;
	            _verbindervertexpolygon**pverbinderfeld;//Field vertexmap:_vertex[]=Null
	            _tg*pblock;
				//nicht speichern, zur speicherunterstützung
                
                
};
void _netz::markierung(int f){
                                                                pflag=f;
};

int _netz::markierung() const{
                                                                return(pflag);
};
#endif



