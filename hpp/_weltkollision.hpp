//******************************************************************************************************************************************************************************************************
//  Project     : grundplatte
//  Library     : _grundplatte.lib
//  Module      : _weltkollision.hpp
//  Date        : 28.12.2002
//  Description : konzepte zur kollision
//******************************************************************************************************************************************************************************************************
#ifndef _weltkollision_included
#define _weltkollision_included
#include <_welt.hpp>




/*

class _kollisionereignis:public _listenknotenbasis<_kollisionsereignis> {
     virtual void kollidiert(_polygon*,_kollidierbar*)=0;


};




class _polygon : public _basis::_list<_kollisionsereignis> {
            void kollidiert(_kollidierbar*k){
                //wird von kollisionsalgorithmik der kollidierbaren aufgerufen
                _kollisionsereignis*kit;
                 if(anfang(kit))do{
                   kit->kollidiert(
                 }while(naechstes(kit));
            };


};



class _oxydstein : public _kollisionsereignis{
     virtual void kollidiert(_polygon*,_kollidierbar*){
          //irgendwas machen mit dem kollidierbaren oder irgendwas auslösen, schalten in der welt
     };
};



*/






//*********************************************************************************************************************************************************************************
//                                                                P R E D E K L A R A T I O N
//*********************************************************************************************************************************************************************************
class _kollidierbar;
class _kollidierbarpunkt;
class _kollidierbarlinie;
class _kollidierbarlinietranslation;
class _kollidierbarkugel;
class _kollidierbarzylinder;
class _kollidierbarzylindertranslation;
class _kollidierbarquader;
class _kollidierbarquadertranslation;
class _kollidierbarnetz;
class _kollidierbarnetztranslation;
class _kollidierbarpolygon;
class _kollidierbarpolygontranslation;
class _kollisionskopplung;
#include <_weltpartition.hpp>
#include <_weltmaterial.hpp>

//#include <ode.h>

//*********************************************************************************************************************************************************************************
//                                                                Z Y K L I S C H E
//*********************************************************************************************************************************************************************************
class _partition::_sektor;


//*********************************************************************************************************************************************************************************
//                                                                S C H N I T T P U N K T K O L L I S I O N 
//*********************************************************************************************************************************************************************************
class _schnittpunktkollision:public _listenknotenbasis<_schnittpunktkollision>{
      //  friend class ;
        public:
                //_schnittpunktkollision(_polygon*po,_vektor<_tg> o,_vektor<_tg> n, _tg p);
                _schnittpunktkollision(_kollidierbar*k,_polygon*p,_verbindervertexpolygon*c,const _vektor3<_tg>&o,const _vektor3<_tg>&v,_tg g,const _vektor3<_tg>&sp,const _vektor3<_tg>&ko,const _vektor3<_tg>&no);
                _schnittpunktkollision(_kollidierbar*k);
                virtual ~_schnittpunktkollision();
                void kopieren(_schnittpunktkollision*s);
                void setzen(_polygon*p,_verbindervertexpolygon*c,const _vektor3<_tg>&o,const _vektor3<_tg>&v,_tg g,const _vektor3<_tg>&sp,const _vektor3<_tg>&ko,const _vektor3<_tg>&no);
                void ruecksetzen();
                void reflektieren();
                void abgleiten();
                void loggen();
                
             
        public:                
                _kollidierbar*kollidierbar;
                _vektor3<_tg> ort;                              //ort des schnittpunktes
                _vektor3<_tg> kontakt;                          //kontaktvektotr relativ zum ort des kollidierbaren
                _vektor3<_tg> normale;                          //schnittnormale
                _vektor3<_tg> ortalt;
                _vektor3<_tg> vektor;                           //bewegungvektor des kollidierbaren
                _tg gamma;                                      //schnittparameter des bewegungsvektors
                
                _polygon*polygon;                               //verursachende
                _verbindervertexpolygon*verbinder;        
                _kollidierbarkugel*kollidierbarkugel;
                //ergebnisse
                _vektor3<_tg> einfallnormal;
                _vektor3<_tg> ausfallnormal;
                _vektor3<_tg> einfall;
                _vektor3<_tg> ausfall;
                _vektor3<_tg> ortabstand;                       //schnittpunkt in richtung -einfallnormal*2*nahenull
                _vektor3<_tg> ortneu;                          //neuer ort des kollidierbaren

                
};
//*********************************************************************************************************************************************************************************
//                                                                K O L L I D I E R E N
//*********************************************************************************************************************************************************************************
bool _kollidieren(_kollidierbarpunkt*,_kollidierbarzylinder*,_vektor<_tg>&);
bool _kollidieren(_kollidierbarpunkt*,_kollidierbarkugel*,_vektor<_tg>&);
//*********************************************************************************************************************************************************************************
//                                                                K O L L I D I E R B A R
//*********************************************************************************************************************************************************************************
 class _kollidierbar:public _liste<_polygon>,public _liste<_partition::_sektor>
 
 /*:public _oberflaeche<_tg>,public _material<_tg>*/{
        public:
                using _liste<_polygon>::anfang;
                using _liste<_polygon>::vorheriges;
                using _liste<_polygon>::naechstes;
                using _liste<_partition::_sektor>::anfang;
                using _liste<_partition::_sektor>::vorheriges;
                using _liste<_partition::_sektor>::naechstes;
        public:
                _kollidierbar(_kollisionskopplung*,_welt*,_partition::_zone*,_partition::_sektor*            ,const _vektor3<_tg>&,const _vektor3<_tg>&);
                _kollidierbar(_kollisionskopplung*,_welt*,_baumoctal<_polygon,_tg>*                              ,const _vektor3<_tg>&,const _vektor3<_tg>&);
                _kollidierbar(_kollisionskopplung*,_welt*,_liste<_polygon>*,unsigned int,unsigned int,_tg,_tg,const _vektor3<_tg>&,const _vektor3<_tg>&);
                virtual ~_kollidierbar();
                void aktivitaet(const bool);
                bool aktivitaet()const;
                const _vektor3<_tg>&ort()const;
                inline _vektor3<_tg>&vektor();
                 _vektor3<_tg>&drehvektor();
                void vektor(const _vektor3<_tg>&);
                _tg vektorlaenge() const;
                void vektorlaenge(const _tg);
                virtual bool bewegen(const _vektor3<_tg>&)=0;
                virtual void bewegungsquader(_tg&,_tg&,_tg&,_tg&,_tg&,_tg&);
                _partition::_sektor*stammsektor();
                _partition::_zone*zone();
                void stammsektor(_partition::_sektor*);
                void zone(_partition::_zone*);
                void bestimmenzone();
                bool maximalerekursion();
                void vorbereitenbewegen();
                void vorbereitenschnittstatisch();
                unsigned int zaehler()const;
                void inkrementierenrekursionszaehler();
                _welt*welt();
               // virtual void kollision(_kollidierbar*);
                void kollisionintern(const bool);
                bool kollisionintern()const;
              //  void wirdkollidiert(const bool);
              //  bool wirdkollidiert()const;
                void ort(const _vektor3<_tg>&);
                void notfallruecksetzen();
                void markierung(const int);
                int markierung()const;
                void markierungkollision(const unsigned int);
                unsigned int markierungkollision()const;
                bool schnittpunktgleich(const _tg g);
                bool schnittpunktentfernter(const _tg g);
                void loeschenschnittpunkt();
                void erzeugenschnittpunkt(_polygon*p,_verbindervertexpolygon*c,const _vektor3<_tg>&o,const _vektor3<_tg>&v,_tg g,const _vektor3<_tg>&sp,const _vektor3<_tg>&ko,const _vektor3<_tg>&no);
              //  virtual void erstellenkollisionssequenz(_vektor<double> o,_vektor<double> v,_partition::_sektor*sektor,_liste<_partition::_sektor >*sektorliste,_liste<_polygon >*polygonliste,_listebasis<_schnittpunktkollision>*schnitte)=0;
        protected:
                void bewegen();
                bool berechnenausfall(bool schnittpunktaufgetreten,_vektor3<_tg>&o,_vektor3<_tg>&v,const _vektor3<_tg>&,const _tg,_polygon*&zuletztkollidiert);
                void aufrufenkopplung();
                void aufrufenkopplung(_polygon*);
        private:                
                _vektor3<_tg> port;
                _vektor3<_tg> pnotort;
                _vektor3<_tg> pvektor;
                _vektor3<_tg> pdrehvektor;
                _tg pvektorlaenge;
                //_tg preflektiv;
                //_tg pabgleitend;
                //_tg panhaftend;
                bool pstatisch;
                bool paktiv;
                //_tg pemodul;
                //_tg phaerte;
                //_tg pmasse;
                //_tg pdichte;
                //_tg preibung;
                unsigned int maxrekursion;
                unsigned int pzaehler;
                _welt*pwelt;                                //welt zeiger
                _partition::_zone*pzone;                    //zonen  zeiger, kollidierbar benutzt sektoren
                _partition::_sektor*psektor;                //sektor zeiger, kollidierbar benutzt sektoren
                _liste<_polygon> * pmatrix;                 //matrix zeiger             , kollidierbar benutzt 2D matrix
                _tg pmatrixwx;                              //matrix geometrische breite, kollidierbar benutzt 2D matrix
                _tg pmatrixwy;                              //matrix geometrische hoehe , kollidierbar benutzt 2D matrix
                unsigned int pmatrixtx;                     //matrix feld breite x      , kollidierbar benutzt 2D matrix
                unsigned int pmatrixty;                     //matrix feld breite y      , kollidierbar benutzt 2D matrix
                _baumoctal<_polygon,_tg> * pbaum;               //baum   zeiger, kollidierbar benutzt den baum
                bool pkollisionintern;                      //schaltet die kollision mit sektorinteren polygonen ein und aus
                int pmarkierung;
                unsigned int pmarkierungkollision;
                
                
        public:               
                _kollisionskopplung*kollisionskopplung; 
                _liste<_polygon> kopplungsaufrufe;
                _schnittpunktkollision schnittpunkt;
                _listebasis<_schnittpunktkollision> schnittpunktliste;
                _vektor3<_tg> einfallsvektor;
                _vektor3<_tg> ausfallsvektor;
                _vektor3<_tg> schnittort;
                
};

//*********************************************************************************************************************************************************************************
//                                                                K O L L I D I E R B A R P U N K T
//*********************************************************************************************************************************************************************************
class _kollidierbarpunkt:public _kollidierbar{
        public:
                _kollidierbarpunkt(_kollisionskopplung*kk,_partition::_zone*,_partition::_sektor*);
                virtual ~_kollidierbarpunkt();
                virtual bool bewegen(/*_vektor<_tg>,_vektor<_tg>&*/);
               // virtual void erstellenkollisionssequenz(_vektor<double> o,_vektor<double> v,_partition::_sektor*sektor,_liste<_partition::_sektor >*sektorliste,_liste<_polygon >*polygonliste,_listebasis<_schnittpunktkollision>*schnitte);
        private:
                //_vektor3<_tg> port;
};
//*********************************************************************************************************************************************************************************
//                                                                K O L L I D I E R B A R Z Y L I N D E R 
//*********************************************************************************************************************************************************************************
class _kollidierbarzylinder:public _kollidierbar{
        public:
                _kollidierbarzylinder(_kollisionskopplung*kk,_partition::_zone*,_partition::_sektor*);
                virtual ~_kollidierbarzylinder();
                virtual bool bewegen(/*_vektor<_tg>,_vektor<_tg>&*/);
                //virtual void erstellenkollisionssequenz(_vektor<double> o,_vektor<double> v,_partition::_sektor*sektor,_liste<_partition::_sektor >*sektorliste,_liste<_polygon >*polygonliste,_listebasis<_schnittpunktkollision>*schnitte);
        private:
               // _vektor3<_tg> port;
                _vektor3<_tg> pachse;
                _tg pradius;
};
//*********************************************************************************************************************************************************************************
//                                                                K O L L I D I E R B A R K U G E L
//*********************************************************************************************************************************************************************************
class _kollidierbarkugel:public _kollidierbar{
        public:
                using _kollidierbar::bewegen;
        public:
                _kollidierbarkugel(_kollisionskopplung*kk,_welt*,const _vektor3<_tg>&,const _vektor3<_tg>&,_tg);
                _kollidierbarkugel(_kollisionskopplung*kk,_welt*,_partition::_zone*,_partition::_sektor*,const _vektor3<_tg>&,const _vektor3<_tg>&v,_tg);
                virtual ~_kollidierbarkugel();
                //_vektor3<_tg>&ort();
                //void vektor(const _vektor3<_tg>&);
                //_vektor3<_tg>&vektor();
                void radius(const _tg); 
                _tg radius()const; 
                virtual void bewegungsquader(const _vektor3<_tg>&o,const _vektor3<_tg>&v,_tg&x0,_tg&x1,_tg&y0,_tg&y1,_tg&z0,_tg&z1);
                virtual void statischerquader(_tg&x0,_tg&x1,_tg&y0,_tg&y1,_tg&z0,_tg&z1);
                void aktualisieren();
                virtual bool schnittstatisch();
                virtual bool testen();
                virtual bool bewegen(const _vektor3<_tg>&);
                bool bewegen(_vektor3<_tg>&o,_vektor3<_tg>&v,const _vektor3<_tg>&,const _tg,_polygon*&zuletztkollidiert);
                virtual void bestimmenschnittpunkt(const _vektor3<_tg>&o,const _vektor3<_tg>&v,_partition::_sektor*sektor,bool&schnittpunktaufgetreten);
                void bestimmenschnittpunktmitbaum(_baumoctalwuerfel<_polygon,_tg>*w,_partition::_sektor*sektor,const _vektor3<_tg>&o,const _vektor3<_tg>&v,const _tg x0,const _tg x1,const _tg y0,const _tg y1,const _tg z0,const _tg z1,bool&schnittpunktaufgetreten);
                virtual void bestimmenschnittstatisch(_partition::_sektor*sektor,bool&);
                void bestimmenschnittstatischmitbaum(_baumoctalwuerfel<_polygon,_tg>*w,_partition::_sektor*sektor,const _tg x0,const _tg x1,const _tg y0,const _tg y1,const _tg z0,const _tg z1,bool&);
                bool kollision(_kollidierbarkugel*kugel,const _vektor3<_tg>&o,const _vektor3<_tg>&v,_vektor3<_tg>&n,_vektor3<_tg>&schnittpunkt,_tg&parameter);
                _tg laengevorkollision()const;
        private:
                _tg pradius;
                _weltdebugpfeil*wp;
                _tg plaengevorkollision;
};
//*********************************************************************************************************************************************************************************
//                                                                K O L L I D I E R B A R P O L Y G O N F E S T
//*********************************************************************************************************************************************************************************
class _kollidierbarpolygontranslation:public _kollidierbar{
        public:
                using _kollidierbar::bewegen;
                using _liste<_partition::_sektor>::anfang;
        public:
                _kollidierbarpolygontranslation(_kollisionskopplung*kk,_welt*,_partition::_zone*,_partition::_sektor*,_polygon*,const _vektor3<_tg>&v);
                virtual ~_kollidierbarpolygontranslation();
                void aktualisieren();
                
                virtual bool bewegen(const _vektor3<_tg>&);
                bool bewegen(_vektor3<_tg>&o,_vektor3<_tg>&v,const _vektor3<_tg>&,const _tg,_polygon*&zuletztkollidiert);
                virtual void bestimmenschnittpunkt(const _vektor3<_tg>&o,const _vektor3<_tg>&v,_partition::_sektor*sektor,bool&schnittpunktaufgetreten);
                //bool kollision(_kollidierbarpolygontranslation*kugel,const _vektor3<_tg>&o,const _vektor3<_tg>&v,_vektor3<_tg>&n,_vektor3<_tg>&schnittpunkt,_tg&parameter);
                //_tg laengevorkollision()const;
        private:
                _polygon*ppolygon;
                _liste<_vektor3<_tg> > pvektoren;
                _weltdebugpfeil*wp;
                _tg plaengevorkollision;
                
        public:                
};
//*********************************************************************************************************************************************************************************
//                                                                K O L L I D I E R B A R N E T Z F E S T
//*********************************************************************************************************************************************************************************
class _kollidierbarnetztranslation:public _kollidierbar{
        public:
                using _kollidierbar::bewegen;

        public:
                _kollidierbarnetztranslation(_kollisionskopplung*kk,_welt*,_partition::_zone*,_partition::_sektor*,_netz*,const _vektor3<_tg>&v);
                virtual ~_kollidierbarnetztranslation();
                _netz* netz();
                void aktualisieren();
                virtual bool berechnenausfall(bool schnittpunktaufgetreten,_vektor3<_tg>&o,_vektor3<_tg>&v,const _vektor3<_tg>&beschleunigung,const _tg beschleunigunglaenge,_polygon*&zuletztkollidiert);
                virtual bool bewegen(const _vektor3<_tg>&);
                virtual bool testen();
                bool bewegen(_vektor3<_tg>&o,_vektor3<_tg>&v,const _vektor3<_tg>&,const _tg,_polygon*&zuletztkollidiert);
                void setzenschnittpunkt(_polygon*p,_verbindervertexpolygon*c,const _vektor3<_tg>&o,const _vektor3<_tg>&v,_tg gamma,const _vektor3<_tg>&sp,const _vektor3<_tg>&ko,const _vektor3<_tg>&no,bool&schnittpunktaufgetreten);
                virtual void bestimmenschnittpunkt(const _vektor3<_tg>&o,const _vektor3<_tg>&v,_partition::_sektor*sektor,bool&schnittpunktaufgetreten);
                void auswertenschnittpunkt();
                void ruecksetzenkollisionszaehlerkante();
                void inkrementierenkollisionszaehlerkante();
                
                
        private:
                _netz*pnetz;                    
                unsigned int pkollisionszaehlerkante;//an wievielen kanten des netzes sind kollisionen aufgetreten
};
//*********************************************************************************************************************************************************************************
//                                                                K O L L I S I O N S K O P P L U N G 
//*********************************************************************************************************************************************************************************
class _kollisionskopplung{
        public:
                _kollisionskopplung();
                virtual ~_kollisionskopplung();
                virtual void kollision(_kollidierbar*,_polygon*);
                virtual void kollision(_kollidierbar*);
                //virtual void kollision
               
};
#endif
