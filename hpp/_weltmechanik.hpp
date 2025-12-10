//******************************************************************************************************************************************************************************************************
//  Project     : grundplatte
//  Library     : _grundplatte.lib
//  Module      : _weltmechanik.hpp
//  Date        : 1.1.2003
//  Description : 
//******************************************************************************************************************************************************************************************************
#ifndef _mechanikh_included
#define _mechanikh_included

//******************************************************************************************************************************************************************************************************
//                                              P R E D E K L A R A T I O N      
//******************************************************************************************************************************************************************************************************
 class _skelett;
 class _knochen;
 class _vertexkopplung;
 class _extremitaet;
 class _extremitaetssegment;
 class _gelenk;


#include <_global.hpp>
#include <_struktur.hpp>
#include <_welt.hpp>




//******************************************************************************************************************************************************************************************************
//                                              S K E L E T T
//******************************************************************************************************************************************************************************************************
class _skelett:public _listebasis<_knochen >,public _listebasis<_extremitaet>{
    public:
            using _listebasis<_knochen>::anfang;
            using _listebasis<_knochen>::naechstes;
            using _listebasis<_knochen>::vorheriges;
            using _listebasis<_extremitaet>::anfang;
            using _listebasis<_extremitaet>::naechstes;
            using _listebasis<_extremitaet>::vorheriges;
    public:
            _skelett(_welt*,const _vektor3<_tg>&o,const _vektor3<_tg>&r,const _vektor3<_tg>&n,const _vektor3<_tg>&s);
            virtual ~_skelett();
            _welt*welt();
            _vektor3<_tg> ort()const;
            void ort(_vektor3<_tg>);
            _vektor3<_tg>&vektor(const unsigned int);
            _liste<_netz>*netze();
            void aktualisierennetze();
            virtual void animieren();
            void bewegen(const _vektor3<_tg>&v);
            void animieren(_knochen*);
            void transformieren(const _vektor3<_tg>&v,_vektor3<_tg>&e);
            void nullsetzenvertexort();
            void nullsetzenvertexort(_knochen*);
            void transformierenvertex();
            void transformierenvertex(const _vektor3<_tg>&ort,_knochen*);
            void assoziieren(_liste<_netz>*ln,const _vektor3<_tg>&ort,_knochen*wurzel,bool rekursiv);
            void assoziieren(_netz*n,const _vektor3<_tg>&ort,_knochen*wurzel,bool rekursiv);
            void assoziieren(_vertex*vit,const _vektor3<_tg>&ort,_knochen*wurzel,_liste<_vertexkopplung>*lvk,bool rekursiv);
            void visualisieren();
            void unvisualisieren();
            _vektor3<_tg> schwerpunkt()const;
            _vektor3<_tg> schwerpunkt(_knochen*,_vektor3<_tg>&,_tg&)const;
    private:
            _vektor3<_tg> plokus;
            _vektor3<_tg> pvektor[3];//0=richtung, 1=normale, 2=seite
            _liste<_netz> pnetze;
            _welt*pwelt;
            _vektoranalysis3<_tg> va;
            //**************DEBUG***********
            _weltdebugkreuz*pcross;
};
//******************************************************************************************************************************************************************************************************
//                                              K N O C H E N
//******************************************************************************************************************************************************************************************************
class _knochen:public _listelistenknotenbasis<_knochen >,public _listebasis<_vertexkopplung>,public _listebasis<_gelenk >{
    friend class _skelett;
    friend class _extremitaet;
    public:
            using _listelistenknotenbasis<_knochen >::anfang;
            using _listelistenknotenbasis<_knochen >::naechstes;
            using _listelistenknotenbasis<_knochen >::vorheriges;
            using _listebasis<_gelenk >::anfang;
            using _listebasis<_gelenk >::naechstes;
            using _listebasis<_gelenk >::vorheriges;
            using _listebasis<_vertexkopplung >::anfang;
            using _listebasis<_vertexkopplung >::naechstes;
            using _listebasis<_vertexkopplung >::vorheriges;
    public:
            _knochen(_skelett*,_listebasis<_knochen >*,_knochen*,_vektor3<_tg>);
            virtual ~_knochen();
            void animieren();
            void transformieren(const _vektor3<_tg>&ort,_vertexkopplung*vk);
            _skelett*skelett();
            _knochen*knochen();
            _vektor3<_tg> ort();
            _vektor3<_tg> ortspitze();
            _tg masse()const;
            void masse(const _tg);
            void speichernort();
            void speichernort(_knochen*);
            void ladenort();
            void ladenort(_knochen*);
            void rotierenx(_tg);
            void visualisieren();
            void unvisualisieren();            
    public:            
            inline _vektor3<_tg>&vektororiginal();
            inline _tg laengeoriginal()const;
            inline _vektor3<_tg>&vektor();
            inline _vektor3<_tg>&ebene0();
            inline _vektor3<_tg>&ebene1();
            inline void vektor(const _vektor3<_tg>&);
            inline void ebene0(const _vektor3<_tg>&);
            inline void ebene1(const _vektor3<_tg>&);
            inline _tg rollwert()const;
            inline void rollwert(const _tg);
    private:
            _knochen*pknochen;
            _skelett*pskelett;
            _tg pmasse;
            _vektor3<_tg> pvektor;
           // _vektor3<_tg> pvektorneu;
            _vektor3<_tg> pvektororiginal;
            _tg plaengeoriginal;
            bool pkollision;
            _vektor3<_tg> pva;
            _vektor3<_tg> pvb;
            _vektor3<_tg> plokus;
            _vektor3<_tg> plokusspitze;
            _tg prollwert;
            bool plokusaktuell;
            bool plokusspitzeaktuell;
            _vektor3<_tg> pparameter;
            // **** DEBUG ****
            _weltdebugpfeil*parrow;
            _weltdebugpfeil*parrowa;
            _weltdebugpfeil*parrowb;
};
_vektor3<_tg>&_knochen::vektororiginal(){
                                                return(pvektororiginal);
};
_tg _knochen::laengeoriginal()const{
                                                return(plaengeoriginal);
};
_vektor3<_tg>&_knochen::vektor(){
                                                return(pvektor);
};
_vektor3<_tg>&_knochen::ebene0(){   
                                                return(pva);
};
_vektor3<_tg>&_knochen::ebene1(){
                                                return(pvb);
};

void _knochen::vektor(const _vektor3<_tg>&v){
                                                pvektor=v;
};
void _knochen::ebene0(const _vektor3<_tg>&e){
                                                pva=e;
};
void _knochen::ebene1(const _vektor3<_tg>&e){
                                                pvb=e;
};
_tg _knochen::rollwert()const{
                                                return(prollwert);
};
void _knochen::rollwert(const _tg p){
                                                prollwert=p;
};

//******************************************************************************************************************************************************************************************************
//                                               V E R T E X K O P P L U N G
//******************************************************************************************************************************************************************************************************
class _vertexkopplung:public _listenknotenbasis<_vertexkopplung>{
    public:
            _vertexkopplung(_knochen*,const _vektor3<_tg>&ort,_vertex*,_tg abstand,_tg para);
            virtual ~_vertexkopplung();
            _vertex* vertex();
            void anteil(const _tg);
            _tg anteil()const;
            _tg abstand()const;
            _tg alpha()const;
            _tg beta()const;
            _tg gamma()const;                        
    private:
            _vertex*pvertex;
            _tg panteil;            
            _tg pabstand;
            _tg palpha;
            _tg pbeta;
            _tg pgamma;
};
//******************************************************************************************************************************************************************************************************
//                                             E X T R E M I T A E T 
//******************************************************************************************************************************************************************************************************
class _extremitaet:public _listenknotenbasis<_extremitaet>,public _kurvehermite3<_tg>{
    public:
            _extremitaet(_skelett*s,_knochen*w);
            virtual ~_extremitaet();
            void einhaengen(_knochen*);
            _liste<_knochen>*knochenliste();
            void initialisierenraum(const _tg laenge);//globale richtungen initialisieren (rechtssystem wichtig!)
            void reinitialisierenknochen();
            void initialisierengammaortnormal();
            void initialisierengammaortgestaucht();
            void initialisierengammaortgestreckt();
            void initialisierengammavektoren();
            void interpolationnormal();
            void interpolationgamma();
            inline _vektor3<_tg>&richtung(const unsigned int i);
            inline _vektor3<_tg>&richtung0normal();
            inline _vektor3<_tg>&richtungoriginal(const unsigned int i);            
            virtual void bewegen(const _vektor3<_tg>&v);
            virtual void animieren();
            void transformierengamma(_vektor3<_tg> o,const unsigned int n);
            void transformierennormal(_vektor3<_tg> o,const unsigned int n);
            virtual void transformieren();//knochen sequenz transformieren
            virtual void transformieren(const _vektor3<_tg>&o,_vektor3<_tg>&e);//nur einen vektor transformieren
            virtual void ausrichtenknochen(const _vektor3<_tg>&);
            virtual void ausrichtenknochensinus(const _vektor3<_tg>&amplitude,const _tg freqskalierung);
            virtual void ausrichten();
            virtual void fixieren(_polygon*);
            virtual void loesen();    
            bool animationortaktivitaet(const unsigned int i)const;
            void animationortaktivitaet(const unsigned int i,const bool b);
            bool animationvektoraktivitaet(const unsigned int i)const;
            void animationvektoraktivitaet(const unsigned int i,const bool b);
            _tg  animationortiterator(const unsigned int i)const;
            void animationortiterator(const unsigned int i,const _tg  b);
            _tg  animationvektoriterator(const unsigned int i)const;
            void animationvektoriterator(const unsigned int i,const _tg  b);
            _tg  animationortschritt(const unsigned int i)const;
            void animationortschritt(const unsigned int i,const _tg  b);
            _tg  animationvektorschritt(const unsigned int i)const;
            void animationvektorschritt(const unsigned int i,const _tg  b);
            _kurvehermite3<_tg>*animationort(const unsigned int i);
            _kurvehermite3<_tg>*animationvektor(const unsigned int i);
            void visualisieren();
            void unvisualisieren();

    private:
            _skelett*pskelett;
            _knochen*pwurzel;
            _liste<_knochen> psequenz;//eine lineare sequenz der knochen
            _polygon*pfussfixierung;
            _vektor3<_tg> pziel;           
            bool panimationortaktivitaet[2];//schaltet die jeweiligen animation aktiv
            bool panimationvektoraktivitaet[2];
            _tg panimationortiterator[2];
            _tg panimationvektoriterator[2];
            _tg panimationortschritt[2];
            _tg panimationvektorschritt[2];
            _kurvehermite3<_tg> panimationort[2];
            _kurvehermite3<_tg> panimationvektor[2];
            _vektor3<_tg> prichtung[3];//optimale(originale) ausrichtung (konstruktionszustand) 
            _vektor3<_tg> prichtung0normal;
            _vektor3<_tg> prichtungoriginal[3];//optimale(originale) ausrichtung nach wurzeltransformation
            _tg plaengemax;
            unsigned int pinterpolationsmodus;
            _liste<_kurvehermite3<_tg> >pks;
            _liste<_kurvehermite3<_tg> >pkd;
            _liste<_weltdebugpfeil> lwp;
            _liste<_weltdebugkreuz> lwc;
};
_vektor3<_tg>&_extremitaet::richtung(const unsigned int i){
                                                return(prichtung[i]);
};
_vektor3<_tg>&_extremitaet::richtungoriginal(const unsigned int i){
                                                return(prichtungoriginal[i]);
};
_vektor3<_tg>&_extremitaet::richtung0normal(){
                                                return(prichtung0normal);
};
//******************************************************************************************************************************************************************************************************
//                                             E X T R E M I T A E T S S E G M E N T 
//******************************************************************************************************************************************************************************************************
/*class _extremitaetssegment:public _listelistenknotenbasis<_extremitaetssegment>,public _kurvehermite3<_tg>{
    public:
            _extremitaetssegment(_extremitaet*,_listebasis<_extremitaetssegment>* );
            virtual ~_extremitaetssegment();

    private:
            _extremitaet*pextremitaet;
            _extremitaetssegment*pextremitaetssegment;
            //_kurvehermite3<_tg> pkurve;


};*/

//******************************************************************************************************************************************************************************************************
//                                              G E L E N K
//******************************************************************************************************************************************************************************************************
class _gelenk:public _listenknotenbasis<_gelenk >{
    friend class _knochen;
    public:
            _gelenk(_knochen*,_vektor3<_tg>,_tg);
            virtual ~_gelenk();
            void transformieren();
            void winkel(_tg);
            _tg winkel() const;
            void visualisieren(_vektor3<_tg>);
            void unvisualisieren();
    private:
            _vektor3<_tg> pachse;
            _vektor3<_tg> pachsetrans;
            _tg pwinkel;
            _knochen*pknochen;
            // ***** DEBUG *****
            _weltdebugpfeil*parrow;
};

#endif
