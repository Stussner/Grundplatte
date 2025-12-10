//******************************************************************************************************************************************************************************************************
//  Projekt      : grundplatte
//  Bibliothek   : _grundplatte.lib
//  Modul        : _weltpolygon.hpp
//  Datum        : 16.5.2005
//  Beschreibung : 
//******************************************************************************************************************************************************************************************************
#ifndef _weltpolygonh_included
#define _weltpolygonh_included
#include <_weltkomponente.hpp>
#include <_welt.hpp>
#include <_weltintersektion.hpp>
#include <_system.hpp>
#include <_editionwin.hpp>

//******************************************************************************************************************************************************************************************************
//                                                              P R E D E K L A R A T I O N 
//******************************************************************************************************************************************************************************************************
class _polygon;
class _polygontexturraum;
class _polygonschatten;
template<class _tg=typgeometrie,class _to=typoptik> class _schatteneinfach;
class _kantepolygon;

//#define iterierenvertex(pit,vit,code) vit=pit->vertex();if(vit)do{code; vit=vit->naechstes(pit);}while(vit!=pit->vertex())
#define iterierendreieck(pit,codeini,codeloop)\
_listenknoten<_vertex>*lnvit0;\
_listenknoten<_vertex>*lnvit1;\
_listenknoten<_vertex>*lnvit2;\
_vertex*vit0;\
_vertex*vit1;\
_vertex*vit2;\
if(pit->anfang(lnvit0)){\
 lnvit1=lnvit0->naechstes();\
 lnvit2=lnvit1->naechstes();\
 vit0=lnvit0->objekt();\
 vit1=lnvit1->objekt();\
 codeini;\
 do{\
  vit2=lnvit2->objekt();\
  codeloop;\
  vit1=vit2;\
  lnvit1=lnvit2;\
  lnvit2=lnvit2->naechstes();\
 }while(lnvit2!=lnvit0);\
};
#define iterierendreieckverbinder(pit,code)\
_listenknoten<_vertex>*lnvit0;\
_listenknoten<_vertex>*lnvit1;\
_listenknoten<_vertex>*lnvit2;\
_vertex*vit0;\
_vertex*vit1;\
_vertex*vit2;\
_verbindervertexpolygon*cit0;\
_verbindervertexpolygon*cit1;\
_verbindervertexpolygon*cit2;\
if(pit->anfang(lnvit0)){\
 lnvit1=lnvit0->naechstes();\
 lnvit2=lnvit1->naechstes();\
 vit0=lnvit0->objekt();\
 vit1=lnvit1->objekt();\
 cit0=static_cast<_verbindervertexpolygon*>(lnvit0);\
 cit1=static_cast<_verbindervertexpolygon*>(lnvit1);\
 do{\
  vit2=lnvit2->objekt();\
  cit2=static_cast<_verbindervertexpolygon*>(lnvit2);\
  code;\
  vit1=vit2;\
  cit1=cit2;\
  lnvit1=lnvit2;\
  lnvit2=lnvit2->naechstes();\
 }while(lnvit2!=lnvit0);\
};
#define iterierendreieckverbindernormaleinterpoliert(pit,code)\
_listenknoten<_vertex>*lnvit0;\
_listenknoten<_vertex>*lnvit1;\
_listenknoten<_vertex>*lnvit2;\
_vertex*vit0;\
_vertex*vit1;\
_vertex*vit2;\
_verbindervertexpolygon*cit0;\
_verbindervertexpolygon*cit1;\
_verbindervertexpolygon*cit2;\
_vektor3<_tg>&n=*this;\
_vektor3<_tg> n0=n;\
_vektor3<_tg> n1=n;\
_vektor3<_tg> n2=n;\
if(pit->anfang(lnvit0)){\
 lnvit1=lnvit0->naechstes();\
 lnvit2=lnvit1->naechstes();\
 vit0=lnvit0->objekt();\
 vit1=lnvit1->objekt();\
 cit0=static_cast<_verbindervertexpolygon*>(lnvit0);\
 cit1=static_cast<_verbindervertexpolygon*>(lnvit1);\
 if(pit->normaleinterpoliert()){\
  n0=vit0->normale();\
  n1=vit1->normale();\
 };\
 do{\
  vit2=lnvit2->objekt();\
  cit2=static_cast<_verbindervertexpolygon*>(lnvit2);\
  if(pit->normaleinterpoliert()) n2=vit2->normale();\
  code;\
  vit1=vit2;\
  cit1=cit2;\
  n1=n2;\
  lnvit1=lnvit2;\
  lnvit2=lnvit2->naechstes();\
 }while(lnvit2!=lnvit0);\
};
                                                        
//******************************************************************************************************************************************************************************************************
//                                                              Z Y K L I S C H E 
//******************************************************************************************************************************************************************************************************
class _welt;
class _netz;
class _dreieck;
class _vertex;
class _kantepolygon;
class _verbindervertexpolygon;
template<class _tg> class _kamera;
class _intersektion;
//******************************************************************************************************************************************************************************************************
//                                                              P O L Y G O N S C H A T T E N 
//******************************************************************************************************************************************************************************************************
class _polygonschatten:public _schatten<_tg,_to>,public _listenknotenbasis<_polygonschatten>{
        public:
                _polygonschatten(_polygon*,_listebasis<_schatten<_tg,_to> >*schattenliste,_licht<_tg,_to>*,_tg);
                virtual ~_polygonschatten();
                virtual void opazitaet(const _to);
                virtual void zeichnen(_grafik*);
                virtual void zeichnendebug(_grafik*);
                virtual void aktualisieren();
        private:
                _polygon*ppolygon;                 //besitzer
                _liste<_vektor3<_tg> > pquadstrip; //quadstrip repräsentation
                _liste<_vektor3<_tg> > pquado;
                _liste<_vektor3<_tg> > pquadu;
};
#define bitverwendentextur				(1<<0)
#define bitverwendentexturdynamisch		(1<<1)
#define bitverwendenconnectorfarbe		(1<<2)
#define bitzeichnenflaeche				(1<<3)
#define bitzeichnenkante				(1<<4)
#define bitzeichnennormale				(1<<5)
#define bitnormaleinterpoliert			(1<<6)
#define bitzweiseitig					(1<<7)
#define bitspiegelnd					(1<<8)
#define bitdynamischschattierend		(1<<9)
#define bitdynamischschattiert			(1<<10)
#define bitmaskiert						(1<<11)
#define bitaufgehellt					(1<<12)
#define bitkollision					(1<<13)
#define bitlightmapschattierung			(1<<14)
#define bittransparent					(1<<15)
#define bittransparenzadditiv			(1<<16)
#define bitdebuggen						(1<<17)
#define bitnurkollisionskopplung		(1<<18)
//******************************************************************************************************************************************************************************************************
//                                                              P O L Y G O N 
//******************************************************************************************************************************************************************************************************


class _polygon:
        public _listenknotenbasis<_polygon >,
        public _liste<_vertex>,
        public _liste<_baumoctalwuerfel<_polygon,_tg> >,
        public _liste<_kollisionskopplung>,
        public _listebasis<_polygonschatten>, 
        public _listebasis<_dreieck >,
        private _vektor3<_tg>,
        public _liste<_partition::_sektor>,
        public _liste<_kollidierbar>,
        public virtual _editierbar,
        public _basis::_speicherbarargument<_polygon>,
		public _speicherbarbinaer,
        public _oberflaeche<_tg>{
        public:
                using _liste<_vertex>::anfang;
                using _listebasis<_dreieck >::anfang;
                using _liste<_kollisionskopplung >::anfang;
                using _listebasis<_polygonschatten>::anfang;
                using _liste<_partition::_sektor>::anfang;
                using _liste<_kollidierbar>::anfang;
                using _liste<_vertex>::naechstes;
                using _listenknotenbasis<_polygon>::naechstes;
                using _listebasis<_dreieck >::naechstes;
                using _liste<_kollisionskopplung >::naechstes;
                using _listebasis<_polygonschatten >::naechstes;
                using _liste<_partition::_sektor>::naechstes;
                using _liste<_kollidierbar>::naechstes;
                using _liste<_vertex>::vorheriges;
                using _listenknotenbasis<_polygon>::vorheriges;
                using _listebasis<_dreieck >::vorheriges;
                using _liste<_kollisionskopplung >::vorheriges;
                using _listebasis<_polygonschatten >::vorheriges;
                using _liste<_partition::_sektor>::vorheriges;
                using _liste<_kollidierbar>::vorheriges;
                using _oberflaeche<_tg>::kopieren;
                using _vektor3<_tg>::kopieren;
               /* using _listenknotenbasis<_polygon>::anzahl;
                using _listebasis<_dreieck >::anzahl;*/
        public:
                //grundoperationen
                _polygon(_netz*);
                _polygon(_polygon*);
                //_polygon(_sektor*);
                virtual ~_polygon();
                void netz(_netz*);
                inline _netz*netz();
                bool vergleichen(_polygon*p);
                void knotenzeichnung(_liste<_polygon>*l);
                void loeschenknotenzeichnung();
                void transformieren(_grafik*,_kamera<_tg>*);
                void transformieren(_grafik*,_kamera<_tg>*,_tg,_tg,_tg);//parallelansichtstransformation, 3.:skalierung x,4.:skalierung y,5.:skalierung z,
                void transformieren(_grafik*,_kamera<_tg>*,_tg,_tg    );//parallelansichtstransformation, 3.:skalierung xy, 4.: z-festwert
                void zeichnen(_grafik*);
                void zeichnen(_grafik*,const _vektor4<_to>&,int markverb);
                void zeichnen(_grafik*,const _vektor3<_to>&,int markverb);
                void zeichnendebug(_grafik*);
                void zeichnenlinie(_grafik*);
                void bindentextur(_grafik*,_bild<_tb>*&,_bild<_tb>*&,_bild<_tb>*&);
                void bindentransparenz(_grafik*);
                void bindenmaskierung(_grafik*);
                void bindenzweiseitigkeit(_grafik*);
                void bindenmaterialoptik(_grafik*);
                bool hatintersektion(_polygon*);
                //innerhalb statisch
                bool innerhalbpunkt(const _vektor3<_tg>&p,const _tg nz,_vertex*&v0,_vertex*&v1,_vertex*&v2,_tg&a,_tg&b);//2D beschleunigt
                bool innerhalbpunkt(const _vektor3<_tg>&);
                bool innerhalbkugel(_vektor3<_tg>,_tg);
                bool innerhalbtexturraum(unsigned int,unsigned int,_tg,_tg);//punkt innerhalb ?  
                //innerhalb translation
                bool innerhalbkugeltranslation(const _vektor3<_tg>&start,const _vektor3<_tg>&vektor,_tg r,bool);
                bool innerhalbpolygontranslation(_polygon*,const _vektor3<_tg>&start,_liste<_vektor3<_tg> >*orte,const _vektor3<_tg>&vektor,bool);
                bool innerhalbnetztranslation(_netz*,const _vektor3<_tg>&start,const _vektor3<_tg>&vektor,bool);
                bool innerhalbnetztranslationrekursiv(_vertex*,const _vektor3<_tg>&ortschieb,const _vektor3<_tg>&vektor);
                bool innerhalbnetztranslationebenerekursiv(_vertex*,const _vektor3<_tg>&ortschieb,const _vektor3<_tg>&vektor);
                //innerhalb rotation
                bool innerhalbpunktrotation(const _vektor3<_tg>&punkt,const _vektor3<_tg>&achsenort,const _vektor3<_tg>&achse,const _tg winkelschritt);
                bool innerhalbkugelrotation(const _vektor3<_tg>&ort,  const _vektor3<_tg>&achsenort,const _vektor3<_tg>&achse,const _tg winkelschritt,const _tg radius);
                //schnittpunkt statisch
                bool schnittpunkt(_vektor3<_tg>&,_vektor3<_tg>&,_tg,_tg,_tg,_tg&,_tg&,_tg&);//beschleunigt
                bool schnittpunkt(_vektor3<_tg>&,_vektor3<_tg>&,_tg,bool,_tg&,_tg&,_tg&);//beschleunigt
                bool schnittpunkt(_vektor3<_tg>&,_vektor3<_tg>&,_tg,bool,_vertex*&,_vertex*&,_vertex*&,_tg&,_tg&,_tg&);
                bool schnittpunkt(_vektor3<_tg>&,_vektor3<_tg>&,_tg,_tg,_tg,_vertex*&,_vertex*&,_vertex*&,_tg&,_tg&,_tg&);
                bool schnittpunkt(_vektor3<_tg>&,_vektor3<_tg>&,_tg,_tg,_tg);
                //schnittpunkt translation
                bool schnittpunktkugeltranslation(const _vektor3<_tg>&ort,const _vektor3<_tg>&vektor,const _tg radius,_vektor3<_tg>&normale,_vektor3<_tg>&schnittpunkt,_tg&parameter);
                bool schnittpunktpolygontranslation(_polygon*,const _vektor3<_tg>&start,_liste<_vektor3<_tg> >*orte,const _vektor3<_tg>&vektor,_vektor3<_tg>&normale,_vektor3<_tg>&schnittpunkt,_tg&parameter);
                bool schnittpunktnetztranslation(_kollidierbarnetztranslation*,const _vektor3<_tg>&start,const _vektor3<_tg>&vektor);//,_vektor3<_tg>&normale,_vektor3<_tg>&schnittpunkt,_vektor3<_tg>&schnittpunktrelativ,_tg&parameter);
                void schnittpunktnetztranslationrekursiv(_kollidierbarnetztranslation*,_vertex*vertex,const _vektor3<_tg>&ortschieb,const _vektor3<_tg>&start,const _vektor3<_tg>&vektor,bool&r);
                void schnittpunktnetztranslationebenerekursiv(_kollidierbarnetztranslation*,_vertex*vertex,const _vektor3<_tg>&ortschieb,const _vektor3<_tg>&start,const _vektor3<_tg>&vektor,bool&r);
                //schnittpunkt rotation
                bool schnittpunktpunktrotation(const _vektor3<_tg>&ort,const _vektor3<_tg>&achsenort,const _vektor3<_tg>&achse,const _tg winkelschritt,_vektor3<_tg>&normale,_vektor3<_tg>&schnittpunkt,_tg&parameter);
                bool schnittpunktkugelrotation(const _vektor3<_tg>&ort,const _vektor3<_tg>&achsenort,const _vektor3<_tg>&achse,const _tg winkelschritt,const _tg radius,_vektor3<_tg>&normale,_vektor3<_tg>&schnittpunkt,_tg&parameter);
                
                
                
                _tg flaeche() const;                                  //gibt flaecheninhalt zurück
                void spiegelmatrix(float*m);
                void normalform(_tg*nf);
                bool polygondavor(const _polygon*p)const;
                bool abgedeckt(_polygon*p);//ist es komplanar und sind alle punkte innerhalb
                void umgrenzungsquader(_tg&,_tg&,_tg&,_tg&,_tg&,_tg&)const;
                bool rueckseitig(_kamera<_tg>*kam,unsigned int zyklus);
                //invarianz
                bool invarianteintegritaet()const;
                bool invarianteanzahl()const;
                bool invariantenichtkolinearitaet()const;
                bool invarianteplanaritaet()const;
                bool invarianteconvexitaet()const;
                bool invariantetexturkoordinaten()const;
                bool invariant()const;
                bool erzwingeninvarianz();
                void erzwingeninvarianzplanaritaet();
                void erzwingeninvarianzkonvexitaet();
                void erzwingeninvarianztexturkoorindaten();
                //flagfunktionen
                inline void markierung(int);
                void markierungrekursiv(int);
                inline int markierung() const;
                void markierungkante(int);
                void markierungvertex(int);
                void markierungvertex(int,int);
                void markierungvertexstatus(int);
                void markierungverbinder(int);
                //elementschnittstelle
                inline _vertex*vertex();                        //ersten vertex der sequenz zurückgeben
                inline _vertex*vertex(unsigned int);            //vertex indiziert aus der sequenz zurückgeben
                //inline void vertex(_vertex*);                   //vertex setzen
                inline _textur<_tb>*textur();                   //textur zurückgeben
                inline void textur(_textur<_tb>*);              //textur setzen
                inline _textur<_tb>*texturfront();                   //textur zurückgeben
                inline void texturfront(_textur<_tb>*);              //textur setzen
                inline _textur<_tb>*texturrueck();                   //textur zurückgeben
                inline void texturrueck(_textur<_tb>*);              //textur setzen
                void loeschentextur();
                inline void verwendentextur(bool);              //textur verwenden ein,aus
                inline bool verwendentextur()const;
                _zeichenkette<char> texturstring() const;       //texturstring zurückgeben, für laden
                inline _textur<_tb>*texturdynamisch();          //dynamische textur zurückgeben
                inline void texturdynamisch(_textur<_tb>*);     //dynamische textur setzen
                inline void verwendentexturdynamisch(bool);     //dynamische textur verwenden ein,aus
                inline bool verwendentexturdynamisch()const;    //dynamische textur verwendet ?
                _zeichenkette<char> texturdynamischstring() const;//dynamischen texturstring zurückgeben, für laden
                inline void lightmaptexelgroesse(const _tg);    //bestimmt die auflösung der zu generierenden lightmap
                inline _tg lightmaptexelgroesse()const;
                inline void verwendenverbinderfarbe(bool);      //connectorfarbe verwenden ein,aus
                inline bool verwendenverbinderfarbe()const;      //connectorfarbe verwenden ein,aus
                inline void zeichnenflaeche(bool);              //flaeche zeichnen ein,aus
                inline bool zeichnenflaeche()const;
                inline void zeichnenkante(bool);                //kanten zeichnen ein aus,
                inline bool zeichnenkante()const;
                inline void zeichnennormale(bool);              //normale zeichnen ein,aus
                inline bool zeichnennormale()const;
                inline void normaleinterpoliert(bool);                   //normaleinterpoliert zeichnen ein,aus
                inline bool normaleinterpoliert();                       //normaleinterpoliert lesen
                inline void zweiseitig(bool);                   //zweiseitig zeichnen ein,aus
                inline bool zweiseitig();                       //zweiseitig lesen
                inline void maskiert(bool);                     //maskiert zeichnen ein,aus
                inline bool maskiert()const;
                inline void aufgehellt(bool);                     //aufgehellt zeichnen ein,aus
                inline bool aufgehellt()const;
                inline void kollision(bool);                 //kollision ein,aus
                inline bool kollision() const;               //kollidierend ?
                inline void lightmapschattierung(const bool);   //lightmaposchattierung (schatten senden) ein/aus
                inline bool lightmapschattierung()const;        //werden schatten gesendet ?
                inline void spiegelnd(bool);                    //spiegelnd zeichnen ein,aus
                inline bool spiegelnd() const;                  //spiegelnd ?
                inline void dynamischschattierend(const bool);  //schattierenden zustand setzen
                inline bool dynamischschattierend()const;       //schattierender zustand?
                inline void dynamischschattiert(const bool);    //schattierenden zustand setzen
                inline bool dynamischschattiert()const;         //schattierender zustand?
                
                inline void transparenz(bool);                  //transparent zeichnen ein,aus
                inline bool transparenz();                      //transparent ?
                inline void transparenzadditiv(bool);           //additiv transparent zeichnen ein,aus
                inline bool transparenzadditiv()const;          //additiv transparent ?
                inline void transparenzfaktor(_tg);             //transparentsfaktor setzen 0..1
                inline _tg transparenzfaktor();                 //transparentsfaktor lesen
                inline void debuggen(const bool);
                inline bool debuggen()const;
                inline void nurkollisionskopplung(const bool);
                inline bool nurkollisionskopplung()const;
                void farbe(const _vektor4<_to>);                //polygonfarbe setzen
                inline _vektor4<_to>&farbe();                   //polygonfarbe zurückgeben
                void farbekante(const _vektor4<_to>);           //kantenfarbe setzen
                inline _vektor4<_to>&farbekante();              //kantenfarbe zurückgeben        
                void farbeverbinder(const _vektor4<_to>&);      //verbinderfarbesetzen  
                void glanz(const _vektor4<_to>&);                //polygonglanz setzen
                inline _vektor4<_to>&glanz();                   //polygonglanz zurückgeben
                void emission(const _vektor4<_to>&);             //polygonemission setzen
                inline _vektor4<_to>&emission();                //polygonemission zurückgeben
                void glanzbreite(const _to);                //polygonglanzbreite setzen
                inline _to glanzbreite();                   //polygonglanzbreite zurückgeben
                
                
           //     inline _tg invertierenausrichtung();            //normale invertieren durch inversion der reihenfolgen vertex
           //     inline _tg ausrichtung()const;                  //normalenflip zurückgeben
                inline void invertieren();
                inline void ausrichtung(bool);                   //normalenausrichtung setzen durch vertexreihenfolge (bool imuhrzeigersinn)
                inline const _vektor3<_tg>&normale()const;       //normale zurüclgeben
                _vektor3<_tg> normale(const _vektor3<_tg>,const _vektor3<_tg>);//normale mit nicht kolinearen vektoren ermitteln
                inline const _vektor3<_tg>&mitte()const;         //mittelpunkt zurückgeben
                inline void mitte(const _vektor3<_tg>&);
                inline const _vektor3<_tg>&ebene(unsigned int)const;//ebenenvektoren zurückgeben (0,1)
                inline _tg determinante() const;                //Hauptdeterminate zurückgeben
                inline void anwahl(int);                        //selektionsstatus setzen
                inline int anwahl() const;                      //selektionsstatus zurückgeben
                //index operationen
                void erzeugenindex();
                void loeschenindex();     
                unsigned int anzahlvertex()const;           
                //aktualisation
                void aktualisieren();
                void aktualisierenmitte();
                void aktualisierenebene();
                void aktualisierendeterminante();
                void aktualisierenschatten();
                void aktualisierenvertexinterpoliertenormale();
                void optimierenstartvertex();
                //strukturoperationen
                void einhaengen(_netz*);
               // void anpassenvertexreihenfolge(bool uhrzeiger);//an gegebene normale anpassen
                _polygon*nachbar(_vertex*,_vertex*);
                bool nachbar(_vertex*,_vertex*,_polygon*&);
                _polygon*nachbar(_kantepolygon*);
                bool nachbar(_kantepolygon*,_polygon*&);
                bool optimieren(_polygon*);
                void anlegentexturkoordinaten(unsigned int);
                void loeschentexturkoordinaten(unsigned int);
                void verschiebentexturkoordinaten(const _vektor2<_tg>&v,unsigned int);
                void skalierentexturkoordinaten(const _vektor2<_tg>&v,unsigned int);
                void rotierentexturkoordinaten(const _tg,unsigned int);
                void spiegelntexturkoordinatenx(unsigned int);
                void spiegelntexturkoordinateny(unsigned int);
                void neusetzentexturkoordinatennormalisiert(unsigned int);
                void neusetzentexturkoordinatenskaliert(unsigned int);
                void anlegenlightmap(_texturverwaltung<_tb>*,_zeichenkette<char>,unsigned int,unsigned int);
                void anlegenlightmap(_texturverwaltung<_tb>*,_zeichenkette<char>,_tg);
                //void loeschenlightmap();
                void anpassenlightmapsize(unsigned int&);
                //schatten 
                void schattenvolumenlaenge(const _tg);
                _tg schattenvolumenlaenge();
                void erzeugenschatten(_licht<_tg,_to>*,_tg);
                void loeschenschatten();
                void anfangschatten();
                void naechsterschatten();
                _polygonschatten*schatteniterator();
                void zeichnenschatten(_grafik*,_licht<_tg,_to>*);      
                //kanten
                inline _liste<_kantepolygon >*kanten();
                bool hatkante()const;
                void erzeugenkante();
                void loeschenkante();
                char holenkante(_vertex*,_vertex*,_kantepolygon*&)const;
                //dreieck
                void erzeugendreieck();
                void loeschendreieck();
                bool hatdreieck() const;
                //ism-supply
                void vorbereitenintersektion();
                _vektor<unsigned int> berechnengroessterindex();
                int groessterindex(unsigned int) const;
                _tg berechnenalpha(const _vektor3<_tg>&)const;
                void status(int);
                int status()const;
                void erzeugentexturraum();
                void loeschentexturraum();
                inline _polygontexturraum*texturespace();
                inline _listebasis<_verbinderisintro >*verbinderisintroliste();
                inline _listebasis<_ringpartition >*ringpartitionsliste();
                //geometrische
                void verschiebennormal(_tg);
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_polygon>*);
                void speichern(_speicherbardynamisch<_polygon>*);
                char assoziieren(_speicherbardynamisch<_polygon>*);
				bool laden(_dateispeicherbarbinaer*d);
				void speichern(_dateispeicherbarbinaer*d);
                bool assoziieren();
				//editieren
                virtual void einhaengendialog(_dynamischerdialog*);
                virtual void auslesendialog(_dynamischerdialog*);
                //debug
                void visualisieren();
                void visualisieren(_vektor4<_to>);
                void unvisualisieren();
                
                void speicherkonversion();
        private:
                bool hatintersektionschraeg(_polygon*,bool&);
        public:
                unsigned int markierungkollisionobjekt;
                unsigned int markierungkollisionrekursion;
                unsigned int markierungkollisionzyklus;
                unsigned int markierungzeichnenzyklus;
                unsigned int markierungzeichnenpass;
                unsigned int markierungzeichnenrueckseitigzyklus;
        private:
				__int32 pstatusbit;
				__int8 paenderung;//wenn bit gesetzt, dann muss aktualisiert werden, 0=strukturaenderung, 1=geometrieaenderung
                //_vertex*pvertex;
               // void*pextrainfo;
                _textur<_tb>*ptextur;
                _textur<_tb>*ptexturrueck;
                _zeichenkette<char> ptexturstring;
                //bool pverwendentextur;							//bit 0
                _textur<_tb>*ptexturdynamisch;
                _zeichenkette<char> ptexturdynamischstring;
                //bool pverwendentexturdynamisch;					//bit 1
                _tg plightmaptexelgroesse;
                //bool pverwendenconnectorfarbe;					//bit 2
                //bool pzeichnenflaeche;							//bit 3
                //bool pzeichnenkante;							//bit 4
                //bool pzeichnennormale;							//bit 5
                //bool pnormaleinterpoliert;						//bit 6
                //bool pzweiseitig;								//bit 7
                //bool pspiegelnd;								//bit 8
                //bool pdynamischschattierend;					//bit 9
                //bool pdynamischschattiert;						//bit 10
                //bool pmaskiert;                                 //bit 11,benutzt alpha maskierung, 
                //bool paufgehellt;                               //bit 12,erzwingt volles vertexlicht
                //bool pkollision;                                //bit 13,polygon macht kollision
                //bool plightmapschattierung;                     //bit 14,polygon schattiert lightmaps
                //bool ptransparent;                              //bit 15,flächentransparenz ja nein
                //bool ptransparenzadditiv;                       //bit 16,true = additiv , false = multiplikativ
                //bool pdebuggen;                                 //bit 17,nur zum internen gebrauch
                //bool pnurkollisionskopplung;					//bit 18
                _to  ptransparentfaktor;                        //transparenzfaktor 0..1
                _vektor4<_to> pfarbe;                            //zeichenfarbe der fläche
                _vektor4<_to> pglanz;                            //glanz material farbe 
                _vektor4<_to> pemission;                        //emmissions material farbe
                _to pglanzbreite;                                 //glanzbreite von glanz
                _vektor4<_to> pfarbekante;                       //zeichenfarbe der kante
                _liste<_kantepolygon > pedges;                   //kantenliste
                _vektor3<_tg> pmiddle;                           //mittelpunkt
                _vektor3<_tg> pplane[2];                         //ebenenvektoren
                _netz*pmesh;                                    //rückzeiger auf das gitter
                _listenknoten<_polygon>*pknotenzeichnung;
                _polygonschatten*pschatteniterator;             //iterator für schattenvolumen
               // _tg pflip;                                     //inversionsflag für die normale
                _tg pdeterminante;                              //hauptdeterminante aus (normale,ebene[0],ebene[1])
                int pflag;                                      //markierung
                int pselection;                                 //selektion        
                _vektor4<_to> phc;                               //allg. farbhilfsvariable
                _tg pschattenvolumenlaenge;                     //laenge der schattenvolumen bei dyn. schattierend ein
                //_liste<_polygonschatten> pschatten;
                unsigned short int*pindexbuffer;
                unsigned int pindexanzahl;
                //***********+ ISM SUPPLY ****************
                _vektor<unsigned int> pcomponent;
                _listebasis<_verbinderisintro > plistisintroconnector;
                _listebasis<_ringpartition > plistringpartition;
                _polygontexturraum*ptexturespace;
                int pstatus;
                _vektoranalysis3<_tg> V3;
                _vektoranalysis2<_tg> V2;
                _vektor3<_tg> ph;                                //enthält die partielle ebene-determinante
                //*********DEBUG**********
                _liste<_weltdebugpfeil > pdbarrows;
                _liste<_weltdebugkreuz > pdbcrosses;
                //************************
                
        private:
                _vektor3<_tg> pmiddleparallel;
                _vektor3<_tg> pmiddleperspective;
                _vektor3<_tg> pmiddlenormalparallel;
                _vektor3<_tg> pmiddlenormalperspective;
};
_netz* _polygon::netz(){
                                                                return(pmesh);
};


int _polygon::markierung() const{
                                                                return(pflag);
};
void _polygon::markierung(int f){
                                                                pflag=f;
};

_vertex*_polygon::vertex(){
                                                                return(_liste<_vertex>::erstes()->objekt());
};


_vertex*_polygon::vertex(unsigned int i){
                                                                _listenknoten<_vertex>*lnvit;
                                                                unsigned int n;
                                                                //------------------------
                                                                if(anfang(lnvit)){
                                                                 for(n=0;n<i;n++) lnvit=lnvit->naechstes();
                                                                 return(lnvit->objekt());
                                                                }else{
                                                                 return(0);
                                                                };
};
/*
void _polygon::vertex(_vertex*v){
                                                                pvertex=v;
};
*/
void _polygon::textur(_textur<_tb>*t){
                                                                ptextur=t;
                                                                if(t) ptexturstring=t->name(); else ptexturstring="";
};
_textur<_tb>*_polygon::textur(){
                                                                return(ptextur);
};
void _polygon::texturfront(_textur<_tb>*t){
                                                                ptextur=t;
                                                                ptexturstring=t->name();
};
_textur<_tb>*_polygon::texturfront(){
                                                                return(ptextur);
};
void _polygon::texturrueck(_textur<_tb>*t){
                                                                ptexturrueck=t;
};
_textur<_tb>*_polygon::texturrueck(){
                                                                return(ptexturrueck);
};
void _polygon::texturdynamisch(_textur<_tb>*t){
                                                                ptexturdynamisch=t;
};
_textur<_tb>*_polygon::texturdynamisch(){
                                                                return(ptexturdynamisch);
};
void _polygon::verwendentextur(bool b){
                                                                if(b) pstatusbit|=bitverwendentextur; else pstatusbit&=~bitverwendentextur;
};
bool _polygon::verwendentextur()const{
                                                                return((pstatusbit&bitverwendentextur)>0);
};
void _polygon::verwendentexturdynamisch(bool b){
																if(b) pstatusbit|=bitverwendentexturdynamisch; else pstatusbit&=~bitverwendentexturdynamisch;
};
bool _polygon::verwendentexturdynamisch()const{
                                                                return((pstatusbit&bitverwendentexturdynamisch)>0);
};
void _polygon::lightmaptexelgroesse(const _tg t){
                                                                if(t>0) plightmaptexelgroesse=t;
};
_tg _polygon::lightmaptexelgroesse()const{
                                                                return(plightmaptexelgroesse);
};
void _polygon::verwendenverbinderfarbe(bool b){                 //connectorfarbe verwenden ein,aus
																if(b) pstatusbit|=bitverwendenconnectorfarbe; else pstatusbit&=~bitverwendenconnectorfarbe;
};
bool _polygon::verwendenverbinderfarbe()const{                  //connectorfarbe verwenden ein,aus
                                                                return((pstatusbit&bitverwendenconnectorfarbe)>0);
};
void _polygon::zeichnenflaeche(bool b){                         //flaeche zeichnen ein,aus
																if(b) pstatusbit|=bitzeichnenflaeche; else pstatusbit&=~bitzeichnenflaeche;
};
bool _polygon::zeichnenflaeche()const{   
                                                                return((pstatusbit&bitzeichnenflaeche)>0);
};
void _polygon::zeichnenkante(bool b){                           //kanten zeichnen ein aus,
																if(b) pstatusbit|=bitzeichnenkante; else pstatusbit&=~bitzeichnenkante;
};
bool _polygon::zeichnenkante()const{
                                                                return((pstatusbit&bitzeichnenkante)>0);
};
void _polygon::zeichnennormale(bool b){                         //normale zeichnen ein,aus
																if(b) pstatusbit|=bitzeichnennormale; else pstatusbit&=~bitzeichnennormale;
};
bool _polygon::zeichnennormale()const{
                                                                return((pstatusbit&bitzeichnennormale)>0);
};
void _polygon::normaleinterpoliert(bool b){                     //normaleinterpoliert zeichnen ein,aus
																if(b) pstatusbit|=bitnormaleinterpoliert; else pstatusbit&=~bitnormaleinterpoliert;
};
bool _polygon::normaleinterpoliert(){                           //normaleinterpoliert zeichnen ein,aus
                                                                return((pstatusbit&bitnormaleinterpoliert)>0);
};
void _polygon::zweiseitig(bool b){                              //zweiseitig zeichnen ein,aus
																if(b) pstatusbit|=bitzweiseitig; else pstatusbit&=~bitzweiseitig;
};
bool _polygon::zweiseitig(){                                    //zweiseitig zeichnen ein,aus
                                                                return((pstatusbit&bitzweiseitig)>0);
};
void _polygon::maskiert(bool b){                                //maskiert zeichnen ein,aus
																if(b) pstatusbit|=bitmaskiert; else pstatusbit&=~bitmaskiert;
};
bool _polygon::maskiert()const{
                                                                return((pstatusbit&bitmaskiert)>0);
};
void _polygon::aufgehellt(bool b){                              //aufgehellt zeichnen ein,aus
																if(b) pstatusbit|=bitaufgehellt; else pstatusbit&=~bitaufgehellt;
};
bool _polygon::aufgehellt()const{
                                                                return((pstatusbit&bitaufgehellt)>0);
};
void _polygon::transparenz(bool b){                             //transparent zeichnen ein,aus
																if(b) pstatusbit|=bittransparent; else pstatusbit&=~bittransparent;
};
bool _polygon::transparenz(){                                   //transparent zeichnen?
                                                                return((pstatusbit&bittransparent)>0);
};
void _polygon::transparenzadditiv(bool b){                      //additiv transparent zeichnen ein,aus
																if(b) pstatusbit|=bittransparenzadditiv; else pstatusbit&=~bittransparenzadditiv;
};
bool _polygon::transparenzadditiv()const{                       //additiv transparent ?
                                                                return((pstatusbit&bittransparenzadditiv)>0);
};
void _polygon::kollision(bool b){                               //kollision ein,aus
																if(b) pstatusbit|=bitkollision; else pstatusbit&=~bitkollision;
};
bool _polygon::kollision() const{                               //kollidierend ?
                                                                return((pstatusbit&bitkollision)>0);
};
void _polygon::lightmapschattierung(const bool b){
																if(b) pstatusbit|=bitlightmapschattierung; else pstatusbit&=~bitlightmapschattierung;
};
bool _polygon::lightmapschattierung()const{
                                                                return((pstatusbit&bitlightmapschattierung)>0);
};
void _polygon::spiegelnd(bool b){                               //spiegelnd zeichnen ein,aus
																if(b) pstatusbit|=bitspiegelnd; else pstatusbit&=~bitspiegelnd;
};
bool _polygon::spiegelnd()const{                                //spiegelnd zeichnen?
                                                                return((pstatusbit&bitspiegelnd)>0);
};
void _polygon::dynamischschattierend(const bool b){             //schattierenden zustand setzen
																if(b) pstatusbit|=bitdynamischschattierend; else pstatusbit&=~bitdynamischschattierend;
};
bool _polygon::dynamischschattierend()const{                    //schattierender zustand?
                                                                return((pstatusbit&bitdynamischschattierend)>0);
};
void _polygon::dynamischschattiert(const bool b){               //schattierenden zustand setzen
																if(b) pstatusbit|=bitdynamischschattiert; else pstatusbit&=~bitdynamischschattiert;
};
bool _polygon::dynamischschattiert()const{                      //schattierender zustand?
                                                                return((pstatusbit&bitdynamischschattiert)>0);
};
void _polygon::transparenzfaktor(_tg f){                        //transparentsfaktor setzen 0..1
                                                                _vektor4<_to> c;
                                                                //_vertex*v;
                                                                _verbindervertexpolygon*vcp;
                                                                _listenknoten<_vertex>*lnv;
                                                                //------------------------------
                                                                c.setzen(0,0,0,0);
                                                                if(f<0) f=0;
                                                                if(f>1) f=1;
                                                                ptransparentfaktor=_to(f);
                                                                //v=pvertex;
                                                                //if(v)do{
                                                                 //if(v->anfang(vcp))do{
                                                                iterieren(lnv,
                                                                 vcp=static_cast<_verbindervertexpolygon*>(lnv);
                                                                 c=vcp->farbe();
                                                                 c.setzenkomponente(3,_to(f));
                                                                 vcp->farbe(c);
                                                                );
                                                                 //}while(v->naechstes(vcp));
                                                                // v=v->naechstes(this);
                                                                //}while(v!=pvertex);
};
_tg _polygon::transparenzfaktor(){                              //transparentsfaktor lesen
                                                                return(ptransparentfaktor);
};
void _polygon::debuggen(const bool b){
																if(b) pstatusbit|=bitdebuggen; else pstatusbit&=~bitdebuggen;
};
bool _polygon::debuggen()const{
                                                                return((pstatusbit&bitdebuggen)>0);
};
void _polygon::nurkollisionskopplung(const bool b){
																if(b) pstatusbit|=bitnurkollisionskopplung; else pstatusbit&=~bitnurkollisionskopplung;
};
bool _polygon::nurkollisionskopplung()const{
                                                                return((pstatusbit&bitnurkollisionskopplung)>0);
};
_vektor4<_to>& _polygon::farbe(){                               //polygonfarbe zurückgeben
                                                                return(pfarbe);
};
_vektor4<_to>& _polygon::farbekante(){                          //polygonfarbe zurückgeben
                                                                return(pfarbekante);
};
_vektor4<_to>&_polygon::glanz(){                                //polygonglanz zurückgeben
                                                                return(pglanz);
};
_vektor4<_to>&_polygon::emission(){                             //polygonemission zurückgeben
                                                                return(pemission);
};
_to _polygon::glanzbreite(){                                    //polygonglanzbreite zurückgeben
                                                                return(pglanzbreite);
};

/*
_tg _polygon::invertierenausrichtung(){
                                                                pflip*=-1;
                                                                aktualisieren();
                                                                return(pflip);
};

_tg _polygon::ausrichtung()const{
                                                                return(pflip);
};
*/
void _polygon::ausrichtung(bool imuhrzeigersinn){
};
void _polygon::invertieren(){
																/*
                                                               _vertex*v;
                                                               _vertex*vn;
                                                               _verbindervertexpolygon*c;
                                                               _liste<_vertex> l;
                                                               _listenknoten<_vertex>*lit;
                                                               //-----------------------------
                                                               iterieren(lit,l.einhaengen(lit->objekt()));
                                                               l.anfang(lit);
                                                               lit=lit->vorheriges();
                                                               v=pvertex;
                                                               if(v)do{
                                                                c=v->connector(this);
                                                                vn=c->naechstervertex();
                                                                c->naechstervertex(lit->objekt());
                                                                lit=lit->naechstes();
                                                                v=vn;
                                                               }while(v!=pvertex);
                                                               */
                                                               _liste<_vertex>::invertieren();
                                                               aktualisieren();
};
const _vektor3<_tg>&_polygon::normale()const{
                                                                return(*this);
};
const _vektor3<_tg>&_polygon::ebene(unsigned int i)const{
                                                                if(i==0){
                                                                 return(pplane[0]);
                                                                }else{
                                                                 return(pplane[1]);
                                                                };
};
const _vektor3<_tg>&_polygon::mitte()const{
                                                                return(pmiddle);
};
void _polygon::mitte(const _vektor3<_tg>&m){
                                                                pmiddle=m;
};
_tg _polygon::determinante()const{
                                                                return(pdeterminante);
};
void _polygon::anwahl(int ps){
                                                                pselection=ps;
};
int _polygon::anwahl() const{
                                                                return(pselection);
};
_polygontexturraum*_polygon::texturespace(){
                                                                return(ptexturespace);
};
_listebasis<_verbinderisintro >*_polygon::verbinderisintroliste(){
                                                                return(&plistisintroconnector);
};
_listebasis<_ringpartition >*_polygon::ringpartitionsliste(){
                                                                return(&plistringpartition);
};
//******************************************************************************************************************************************************************************************************
//                                                              P O L Y G O N T E X T U R E S P A C E 
//******************************************************************************************************************************************************************************************************

class _polygontexturraum{
        friend class _polygon;
        friend class _modifikationnetzintersektion;
        
        private:
                _polygontexturraum(_polygon*p);
                virtual ~_polygontexturraum();
        public:
                void interpolieren(unsigned int,unsigned int,_tg,_tg,_vektor2<_tg>&);
                void konvertierentexturwelt(unsigned int,unsigned int,_tg,_tg,_vektor3<_tg>&);
                bool innerhalb(unsigned int,unsigned int,_tg,_tg);
                void vorberechnenpolygon(unsigned int,unsigned int);
        private:
                _tg Dv; //zweidimensionale Hauptdeterminante folgender Ebenendarstellung
                _vektor2<_tg> mitte;//zweidimensionale geometrische mitte
                _vektor2<_tg> va;//zweidimensionaler geom. ebenenvektor a gebildet durch vertexvectoren
                _vektor2<_tg> vb;//zweidimensionaler geom. ebenenvektor b gebildet durch vertexvectoren
              //  _vektor3<_tg> vpa;//zweidimensionaler geom. ebenenvektor a gebildet durch planevektoren
              //  _vektor3<_tg> vpb;//zweidimensionaler geom. ebenenvektor b gebildet durch planevektoren
                _texturvektor<_tg> tvm;
                _texturvektor<_tg> tva;
                _texturvektor<_tg> tvb;
                _texturvektor<_tg> tvplane[2];
                _polygon*poly;
                _vektoranalysis2<_tg> V2;
                _liste<_tg> ox;
                _liste<_tg> oy;
                _liste<_tg> nx;
                _liste<_tg> ny;
                _listenknoten<_tg>*iox;
                _listenknoten<_tg>*ioy;
                _listenknoten<_tg>*inx;
                _listenknoten<_tg>*iny;
                unsigned int vbvi;
                unsigned int vbli;
                
};
//******************************************************************************************************************************************************************************************************
//                                                              K A N T E P O L Y G O N
//******************************************************************************************************************************************************************************************************

class _kantepolygon{
        public:
                _kantepolygon(_polygon*,_polygon*,_vertex*,_vertex*);
                virtual ~_kantepolygon();
                void aktualisieren();
                inline void markierung(int);
                inline int markierung() const;
                void invertierenvertex();
                void invertierenpolygon();
                inline _vertex*vertex(int);
                inline _polygon*polygon(int);
                inline _vektor3<_tg> vektor();
                inline _vektor2<_tg>&vektor2d(_polygon*);//für kollision
                inline _vektor2<_tg>&mitte2d(_polygon*);//für kollision
                inline _tg determinante2d(_polygon*);//für kollision
                inline _vektor3<_tg> ort(int);
                //ism-supply
                void start(_vertex*);
                void invertieren();
                inline void betareal(_tg);
                inline _tg betareal() const;
                inline void alpha(_tg);
                inline _tg alpha() const;
                inline void parallel(char);
                inline char parallel() const;
                _listebasis<_verbinderisintro >*verbinderisintroliste();
                void inkrementierenanzahlverbinderisintro();
                void dekrementierenanzahlverbinderisintro();
        private:
                _polygon*ppolygon[2];
                _vertex*pvertex[2];
                _vektor3<_tg> pvector;
                _vektor2<_tg> pvector2d[2];
                _vektor3<_tg> pnormal[2];
                _vektor2<_tg> pnormal2d[2];
                _vektor3<_tg> pmiddle;
                _vektor2<_tg> pmiddle2d[2];
                _tg pdeterminante2d[2];
                int pflag;
                //*********************** ISM supply *********************
                _listebasis<_verbinderisintro > plistisintroconnector;
                int pintersectioncount;
                int pisintroconnectorcount;
                _vertex*pvertexstart;
                _tg palpha;
                _tg pbetareal;
                char pparallel;
};
_polygon*_kantepolygon::polygon(int i){
                                                                if((i>=0)&&(i<2)){
                                                                 return(ppolygon[i]);
                                                                }else{
                                                                 return(0);
                                                                };
};
_vertex*_kantepolygon::vertex(int i){
                                                                if((i>=0)&&(i<2)){
                                                                 return(pvertex[i]);
                                                                }else{
                                                                 return(0);
                                                                };
};
void _kantepolygon::markierung(int f){
                                                                pflag=f;
};

int _kantepolygon::markierung() const{
                                                                return(pflag);
};


void _kantepolygon::betareal(_tg x){
                                                                pbetareal=x;
};

_tg _kantepolygon::betareal() const{
                                                                return(pbetareal);
};

void _kantepolygon::alpha(_tg x){
                                                                palpha=x;
};

_tg _kantepolygon::alpha() const{
                                                                return(palpha);
};

void _kantepolygon::parallel(char x){
                                                                pparallel=x;
};

char _kantepolygon::parallel() const{
                                                                return(pparallel);
};
_vektor2<_tg>&_kantepolygon::vektor2d(_polygon*p){           //für kollision
                                                                if(ppolygon[0]==p) return(pvector2d[0]); else return(pvector2d[1]);
};

_vektor2<_tg>&_kantepolygon::mitte2d(_polygon*p){//für kollision
                                                                if(ppolygon[0]==p) return(pmiddle2d[0]); else return(pmiddle2d[1]);
};

_tg _kantepolygon::determinante2d(_polygon*p){//für kollision
                                                                if(ppolygon[0]==p) return(pdeterminante2d[0]); else return(pdeterminante2d[1]);
};

_vektor3<_tg> _kantepolygon::vektor(){
                                                                return(pvector);
};

_vektor3<_tg> _kantepolygon::ort(int i){
                                                                int c;
                                                                //------------
                                                                if(i==0) c=0; else c=1;
                                                                return(pvertex[c]->ort());
};
//******************************************************************************************************************************************************************************************************
//                                                              S C H A T T E N E I N F A C H
//******************************************************************************************************************************************************************************************************
template<class _tg,class _to> class _schatteneinfach:public _schatten<_tg,_to>{
        public:
                _schatteneinfach(_listebasis<_schatten<_tg,_to> >*schattenliste,_licht<_tg,_to>*li,_netz*ow,_textur<_tb>*tex);
                virtual ~_schatteneinfach();
                virtual void opazitaet(const _to o);
                virtual void aktualisieren();
                virtual void zeichnen(_grafik*);
                virtual void zeichnendebug(_grafik*);
                void aktualisierenarray();
                void berechnenopazitaet(int quant=0);
        public:
	            _netz*mesh;
	            _polygon*poly;
	            
	            _to opacity;
	            _netz*owner;
	            _vertex*vertex[4];
	            _vertex*vertexmesh[4];
	            _polygon*polygon;
	            _schatteneinfach<_tg,_to>*shadowother[1000];
	            int shadowothercount;
	            _tg ldis;
	            _vektor3<_tg> hh;
	            _vektor3<_tg> hm;
	            _vektor3<_tg> hs;
	            _vektor3<_tg> hd;
};
template<class _tg,class _to> _schatteneinfach<_tg,_to>::_schatteneinfach(_listebasis<_schatten<_tg,_to> >*schattenliste,_licht<_tg,_to>*li,_netz*ow,_textur<_tb>*tex):_schatten<_tg,_to>(schattenliste,li,1){
	            gueltig(true);
	            opacity=1;
	            shadowothercount=0;
	            ldis=0;
				owner=ow;
				_geometrienetz gg(0,_vektor3<_tg>(-12,11,0),14,-12,tex);
				gg.farbe(1,1,1,0.6f);
				mesh=gg.erzeugen();
				//mesh->dynamicvertexlight=False;//!!!!!!!!!!!!!!!!!!!!!!!!
				mesh->zweiseitig(true);
				mesh->transparenz(true);
				mesh->transparenzadditiv(false);
				int i,j;
				i=0;
				_polygon*pit;
				_vertex*vit;
				if(owner->anfang(pit))do{
				 vit=pit->vertex();
				 if(vit)do{
				  j=i;
				  if(i==2) j=3;
				  if(i==3) j=2;
				  vertex[j]=vit;
				  i++;
				  vit=vit->naechstes(pit);
			 	 }while(vit!=pit->vertex());
	            }while(owner->naechstes(pit));
				mesh->anfang(polygon);
				i=0;
				if(mesh->anfang(pit))do{
				 poly=pit;
				 vit=pit->vertex();
				 if(vit)do{
				  j=i;
				  if(i==2) j=3;
				  if(i==3) j=2;
				  vertexmesh[j]=vit;
				  i++;
				  vit=vit->naechstes(pit);
			 	 }while(vit!=pit->vertex());
				}while(mesh->naechstes(pit));
};
template<class _tg,class _to> _schatteneinfach<_tg,_to>::~_schatteneinfach(){
				owner=0;
				deletesecure(mesh);
				for(int i=0;i<4;i++){
				 vertex[i]=0;
				 vertexmesh[i]=0;
				};
				polygon=0;
				for(int i=0;i<1000;i++) shadowother[i]=0;
};
template<class _tg,class _to> void _schatteneinfach<_tg,_to>::opazitaet(const _to o){
                mesh->opazitaetverbinder(o);
};
template<class _tg,class _to> void _schatteneinfach<_tg,_to>::aktualisierenarray(){
				shadowothercount=0;
				_schatten<_tg,_to>*sit;
				_schatteneinfach<_tg,_to>*eit;
				if(liste()->anfang(sit))do{
				 eit=dynamic_cast<_schatteneinfach<_tg,_to>*>(sit);
				 if(eit){
				  _listenknoten<_licht<_tg,_to> >*it;
				  if((eit->anfang(it))&&(eit!=this)){
				   if(it->objekt()==licht()){
				    shadowother[shadowothercount]=eit;
				    shadowothercount++;
				   };
				  };
				 };
				}while(liste()->naechstes(sit));
};
template<class _tg,class _to> void _schatteneinfach<_tg,_to>::berechnenopazitaet(int quant=0){
				if(gueltig()){
				 _tg c=0;
				 _tg a=1;
				 _vektor3<_tg> m=polygon->mitte();
				 for(int i=0;i<shadowothercount;i++){
				  _schatteneinfach<_tg,_to>*sit=shadowother[i];
				  if(sit->gueltig()){
				   _tg d=(m.abstandabstandxy(sit->polygon->mitte()))*0.3+1;
				   if(d<20){
				    a=a+(1/d)*0.2*(1+ldis*0.5);
				   };
				  };
				 };
				 _to oo=1/_to(a);
				 if(oo<0.1){
				  oo=0.1;
				  if(quant>0){
				   oo=0;
				   gueltig(false);
				  };
				 };
				 opacity=(opacity+oo)*0.5;
			 	};
};
template<class _tg,class _to> void _schatteneinfach<_tg,_to>::aktualisieren(){
				if((owner)&&(mesh)){
				 _tg gamma;
				 gueltig(true);
			     hm.setzen(0,0,0);
				 hd.setzen(0,0,0);
				 _vektor3<_tg> lo=licht()->ort();
				 for(int i=0;i<4;i++){
				  if(gueltig()){
				   hh=vertex[i]->ort()-lo;
				   hd+=hh;
				   gamma=-lo.z()/hh.z();
				   if(gamma>0){
				    hs.setzen(lo.x()+hh.x()*gamma,lo.y()+hh.y()*gamma,0);
				    hm.x(hm.x()+hs.x());
				    hm.y(hm.y()+hs.y());
				    vertexmesh[i]->ort(hs);
				   }else{
				    gueltig(false);
				   };
				  };
				 };
				 if(gueltig()){
				  hm.x(hm.x()*0.25);
				  hm.y(hm.y()*0.25);
				  hd*=0.25;
				  ldis=hd.laenge()/_tg(25);
				  polygon->mitte(hm);
				 };
				};
};
template<class _tg,class _to> void _schatteneinfach<_tg,_to>::zeichnen(_grafik*g){
				if(gueltig()) if(opacity>0) poly->zeichnen(g);
};
template<class _tg,class _to> void _schatteneinfach<_tg,_to>::zeichnendebug(_grafik*g){
				if(gueltig()) if(opacity>0) poly->zeichnendebug(g);
};

#endif



