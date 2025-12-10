//******************************************************************************************************************************************************************************************************
//  Projekt      : grundplatte.lib
//  Bibliothek   : welt
//  Modul        : _weltpartikel.hpp
//  Datum        : 27.2.2004
//  Beschreibung : 
//******************************************************************************************************************************************************************************************************
#ifndef _weltpartikelh_included
#define _weltpartikelh_included
//******************************************************************************************************************************************************************************************************
//                                                              P R E D E K L A R A T I O N 
//******************************************************************************************************************************************************************************************************
class _partikelquelle;
class _partikelquellesprite;
class _partikelquellespritephysikalisch;
class _partikel;
class _partikelsprite;
class _partikelspritephysikalisch;
class _sprite;
#include <_global.hpp>
#include <_funktion.hpp>
#include <_welt.hpp>
#include <_weltpartition.hpp>
#include <_akustik.hpp>






//******************************************************************************************************************************************************************************************************
//                                                              P A R T I K E L Q U E L L E 
//******************************************************************************************************************************************************************************************************

class _partikelquelle:
public _listenknotenbasis<_partikelquelle >,
public virtual _editierbar,
public _basis::_speicherbarargument<_partikelquelle>,
public _speicherbarbinaer{
        public:
                friend class _partikel;
        public:
                _partikelquelle(_welt*,_zeit*,_listebasis<_partikelquelle>*,_listebasis<_partikel>*);
                _partikelquelle(_welt*,_zeit*,_listebasis<_partikelquelle>*,_listebasis<_partikel>*,const _vektor3<_tg>&o,const _vektor3<_tg>&v,_tg,_textur<_tb>*);
                _partikelquelle(const _partikelquelle*p);
                virtual ~_partikelquelle();
                void kopieren(const _partikelquelle*);
                _welt*welt();
                _zeit*zeit();
                _partition::_zone*zone();

                virtual void animieren();
                void animierenlichtliste();
                virtual void generieren();
                virtual _partikel*erzeugenpartikel(const _vektor3<_tg>&pos);

                
                bool aktiv()const;
                void aktiv(const bool);

                void listepartikel(_listebasis<_partikel>*);
                _listebasis<_partikel>*listepartikel();
                _liste<_partikel>*listepartikelintern();
                void listepartikeleinhaengenerstes(const bool);
                bool listepartikeleinhaengenerstes()const;
                
                void partikelquellegeburt(_partikelquelle*);
                void partikelquelleleben(_partikelquelle*);
                void partikelquelletod(_partikelquelle*);
                _partikelquelle*partikelquellegeburt();
                _partikelquelle*partikelquelleleben();
                _partikelquelle*partikelquelletod();

                void name(const _zeichenkette<char>&);
                _zeichenkette<char> name()const;
                
                _textur<_tb>*textur();
                _liste<_textur<_tb> >*listetextur();
                _liste<_zeichenkette<char> >*texturstrings();
                void einfuegentextur(_textur<_tb>*);

                _netz*netz();
                _liste<_netz>*listenetz();
                void einfuegennetz(_netz*);
                void erzeugenstandardnetz();

                void kollision(const bool);
                bool kollision()const;
                void kollisionreflektierend(const _tg);
                void kollisionabgleitend(const _tg);
                void kollisionanhaftend(const _tg);
                _tg kollisionreflektierend()const;
                _tg kollisionabgleitend()const;
                _tg kollisionanhaftend()const;
	            void kollisionz(const bool);
	            void kollisionzort(const _tg);
                
                
                void ort(const _vektor3<_tg>&);
                void ort(const _tg x,const _tg y,const _tg  z);
                _vektor3<_tg>&ort();
                _vektor3<_tg> ortpartikel()const;
                void ortraum(const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor3<_tg>&);
                void ortraum(const unsigned int i,const _tg x,const _tg y,const _tg z);
                void ortraum(const unsigned int i,const _vektor3<_tg>&);
                _vektor3<_tg>&ortraum(const unsigned int i);
                void orttoleranz(const _tg);
                _tg orttoleranz()const;

                void vektor(const _vektor3<_tg>&);
                void vektor(const _tg x,const _tg y,const _tg z);
                _vektor3<_tg>&vektor();
                void vektortoleranz(const _tg);
                _vektor3<_tg> vektorpartikel()const;
                
                void rotation(const _tg);
	            void rotationvektor(const _tg);
	            void rotationreibung(const _tg);
	            void rotationtoleranz(const _tg t);
	            _vektor3<_tg>&rotationachse();   
	            void rotationachsetoleranz(const _tg v);
	            _vektor3<_tg> rotationachsepartikel()const;
	            _tg rotationpartikel()const;
                
                void lebensdauer(const _tg);//der partikelquelle
                void lebensdauerpartikel(const _tg);//der partikel
                void lebensdauerpartikeltoleranz(const _tg);//der partikel
                _tg lebensdauerpartikel() const;
                
                void generationsrate(const _tg);
                _tg generationsrate()const;
                void generationsratetoleranz(const _tg);
	            void generationsdichtedynamisch(const _tg);
	            _tg  generationsdichtedynamisch()const;
	            void generationsrateletztegenerierung(const _tg t);
	            _tg generationsrateletztegenerierung()const;
	            void generationsrateletzterort(const _vektor3<_tg>&);
	            _vektor3<_tg>&generationsrateletzterort();
	            void generationsratesollpartikel(const _tg);
	            _tg generationsratesollpartikel()const;
	            void generationsratesollpartikelinkrementieren(const _tg i);
	            void generationsratesollpartikeldekrementieren(const _tg i);
                
                void masse(const _tg);
                
                void groesse(const _tg);
                _tg groesse() const;
                _tg groessepartikel()const;
                void groessetoleranz(const _tg);
	            void skalierung(const bool);
	            void skalierung(const _tg);
	            
                _tg tolerierenkraft(const _tg a,const _tg t)const;
                _tg feldkraftg()const;
                _tg feldkraftgtoleranz()const;
                _tg feldkrafte()const;               
                _tg feldkraftetoleranz()const;
                _tg feldkraftb()const;
                _tg feldkraftbtoleranz()const;
                _tg feldkraftm()const;
                _tg feldkraftmtoleranz()const;
                void feldkraftg(const _tg);
                void feldkraftgtoleranz(const _tg);
                void feldkrafte(const _tg);               
                void feldkraftetoleranz(const _tg);
                void feldkraftb(const _tg);
                void feldkraftbtoleranz(const _tg);
                void feldkraftm(const _tg);
                void feldkraftmtoleranz(const _tg);
                _vektor3<_tg>&feldkraftghomogen();	            

	            void farbe(const _vektor4<_to>&);
	            _vektor4<_to>&farbe();
	            void opazitaet(const _to);
	            void kurvefarbe(const bool);
	            _kurvehermite4<_to>&kurvefarbe();
	            void einblenden(const bool);
	            void ausblenden(const bool);
	            void transparenzadditiv();
	            void transparenzmultiplikativ();
	            

	            void planarydivergenz(const bool);
	            void planarydivergenzort(const _tg);
	            void planarydivergenzintensitaet(const _tg);
	            
	            void axialdivergenz(const bool);
	            void axialdivergenzort(const _vektor3<_tg>&);
	            void axialdivergenzort(const _tg x,const _tg y,const _tg z);
	            _vektor3<_tg>&axialdivergenzort();
	            void axialdivergenzvektor(const _vektor3<_tg>&);
	            void axialdivergenzvektor(const _tg x,const _tg y,const _tg z);
	            _vektor3<_tg>&axialdivergenzvektor();
	            
	            
	            void schattenz(const bool);
	            void schattenzopazitaet(const _tg);
	            void schattenztextur(_textur<_tb>*);
	            
	            void opazitaetsinus(const bool);
	            void opazitaetsinusrate(const _tg);
	            void opazitaetsinusphase(const _tg);
	            void opazitaetsinusphasetoleranz(const _tg);
	            void opazitaetsinusratedelta(const _tg);
	            void opazitaetsinusratedeltatoleranz(const _tg);
	            _tg opazitaetsinusphasepartikel()const;
	            _tg opazitaetsinusratedeltapartikel()const;
                
	            void tontod(_ton*);
	            void tontodlautstaerke(const _tg);
	            void tontodlautstaerketoleranz(const _tg);
	            void tontodbeugung(const _tg);
	            void tontodbeugungtoleranz(const _tg);
	            void tontodbeugungdoppler(const bool);
                _tg tontodlautstaerkepartikel()const;
                _tg tontodbeugungpartikel()const;
                _vektor3<_tg>&tontodletzterort();
                void tontodletzterortgueltig(bool);
                bool tontodletzterortgueltig()const;
	            
                
	            void lichtgeburt(_licht<_tg,_to>*);
	            _licht<_tg,_to>*lichtgeburt();
                void lichtgeburtliste(_liste<_licht<_tg,_to> >*l);
	            _liste<_licht<_tg,_to> >*lichtgeburtliste();
	            void lichtgeburtaddition(const _tg);
	            _tg lichtgeburtaddition()const;
	            void lichtgeburtmultiplikation(const _tg);
	            void lichttod(_licht<_tg,_to>*);
	            _licht<_tg,_to>*lichttod();
	            void lichttodliste(_liste<_licht<_tg,_to> >*);
	            _liste<_licht<_tg,_to> >*lichttodliste();
	            void lichttodaddition(const _tg);
	            void lichttodmultiplikation(const _tg);
                

                //speichern
                void speichern(_dateispeicherbarbinaer*d);
                bool laden(_dateispeicherbarbinaer*d);
                bool assoziieren();
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_partikelquelle>*);
                void speichern(_speicherbardynamisch<_partikelquelle>*);
                char assoziieren(_speicherbardynamisch<_partikelquelle>*);
                //editieren
                virtual void einhaengendialog(_dynamischerdialog*);
                virtual void auslesendialog(_dynamischerdialog*);

        private:
                void init(_welt*w,_zeit*z,_listebasis<_partikelquelle>*lpq,_listebasis<_partikel>*lpt,const _vektor3<_tg>&o,const _vektor3<_tg>&v,_tg lifetime,_textur<_tb>*tex);
        private:
                _welt*pwelt;
                _zeit*pzeit;
                _partition::_zone*pzone;
                _zeichenkette<char> pname;
                _listebasis<_partikel>*plistepartikel;  //hier werden die partikel eingehängt
                _liste<_partikel> plistepartikelintern; //hier ebenfalls, assoziativ und intern zur Modifikation
                _listebasis<_partikelquelle>*plistepartikelquelle;//hier wird die quelle eingehaengt
	            bool plistepartikeleinhaengenerstes;//die partikel werden als erstes oder (standard) als letztes einhaengt
                _partikelquelle*ppartikelquellegeburt;//zur assoziation mit den partikeln
                _partikelquelle*ppartikelquelleleben;//partikelinterne partikelquellen
                _partikelquelle*ppartikelquelletod;
                
                _liste<_textur<_tb> > ptexturliste;
                _liste<_zeichenkette<char> > ptexturstrings;
                _listenknoten<_textur<_tb> >*ptexturiterator;
                unsigned int ptexturanzahl;            
                
	            _liste<_netz> pnetzliste;
	            _listenknoten<_netz>*pnetziterator;
                
                bool paktiv;
                bool pkollision;
                _tg pkollisionreflektierend;
                _tg pkollisionabgleitend;
                _tg pkollisionanhaftend;
	            bool pkollisionz;
	            _tg pkollisionzort;
                
                _vektor3<_tg> port;
                _tg porttoleranz;
                _vektor3<_tg> portraum[3];
                _vektor3<_tg> pvektor;
                _tg pvektortoleranz;
                bool pzentrumbenutzen;
                _vektor3<_tg> pzentrum;
                _tg protation;
                _tg protationtoleranz;
	            _tg protationvektor;
	            _tg protationreibung;
	            _vektor3<_tg> protationachse;      
	            _tg protationachsetoleranz;          
                bool plebensdauerbegrenzt;
                _tg plebensdauer;//lebensdauer der partikelquelle
                _tg plebensdauerletzteaktivierung;
                _tg plebensdauerpartikel;
                _tg plebensdauerpartikeltoleranz;
                _tg pgenerationsrate;
                _tg pgenerationsratetoleranz;
	            _tg pgenerationsdichtedynamisch;
	            _tg pgenerationsratesollpartikel;
	            _tg pgenerationsrateletztegenerierung;    
	            _vektor3<_tg> pgenerationsrateletzterort;
                _tg pmasse;	                        
                _tg pgroesse;
                _tg pgroessetoleranz;
	            bool pskalierung;
	            _tg pskalierungwert;
                _tg pfeldkraftg;
                _tg pfeldkraftgtoleranz;
                _tg pfeldkrafte;               
                _tg pfeldkraftetoleranz;
                _tg pfeldkraftb;
                _tg pfeldkraftbtoleranz;
                _tg pfeldkraftm;
                _tg pfeldkraftmtoleranz;
                _vektor3<_tg> pfeldkraftghomogen;
	            _vektor4<_to> pfarbe;
	            bool pkurvefarbebenutzen;
	            _kurvehermite4<_to> pkurvefarbe;
                bool pausblenden;
	            bool peinblenden;
	            bool ptransparenzadditiv;
	            bool ptransparenzmultiplikativ;

	            bool pplanarydivergenz;
	            _tg pplanarydivergenzort;
	            _tg pplanarydivergenzintensitaet;
	            bool paxialdivergenz;
	            _vektor3<_tg> paxialdivergenzort;
	            _vektor3<_tg> paxialdivergenzvektor;
	            bool pschattenz;
	            _tg pschattenzopazitaet;
	            _textur<_tb>*pschattenztextur;
				_zeichenkette<char> pschattenztexturstring;
	            bool popazitaetsinus;
	            _tg popazitaetsinusrate;
	            _tg popazitaetsinusphase;
	            _tg popazitaetsinusphasetoleranz;//absolut
	            _tg popazitaetsinusratedelta;
	            _tg popazitaetsinusratedeltatoleranz;//absolut
	            _ton*ptontod;
	            _tg ptontodlautstaerke;
	            _tg ptontodlautstaerketoleranz;
	            _tg ptontodbeugung;
	            _tg ptontodbeugungtoleranz;
	            bool ptontodbeugungdoppler;
	            _vektor3<_tg> ptontodletzterort;
	            bool ptontodletzterortgueltig;
	            _licht<_tg,_to>*plichtgeburt;
	            _liste<_licht<_tg,_to> >*plichtgeburtliste;
	            _tg plichtgeburtaddition;
	            _tg plichtgeburtmultiplikation;
	            _licht<_tg,_to>*plichttod;
	            _liste<_licht<_tg,_to> >*plichttodliste;
	            _tg plichttodaddition;
	            _tg plichttodmultiplikation;

                _zufallsgenerator<_tg> prand;
	            _kurvehermite3<_tg> hc;//curve=New _hermitecurve
	            _vektor3<_tg> pparticlegenerationpositionold;

};


                
                
                
                

//******************************************************************************************************************************************************************************************************
//                                                              P A R T I K E L 
//******************************************************************************************************************************************************************************************************

class _partikel:public _listenknotenbasis<_partikel >{
        public:
                _partikel(_welt*,_zeit*,_partikelquelle*);
                virtual ~_partikel();
                void bestimmensektor();
                virtual void animieren();
                virtual void animierenbewegung();
                virtual void animierenoptik();
                virtual void animierenlebensdauer();
                virtual void zeichnen(_grafik*g);
                virtual void zeichnenschatten(_grafik*g);
                bool pruefenlebensdauer();
                _tg alterprozent();

                void partikelquelleleben(_partikelquelle*pql);
                void partikelquelletod(_partikelquelle*pqt);

                void kollision(const bool,const _tg,const _tg,const _tg);
                void kollisionz(const _tg o);
                
                void textur(_textur<_tb>*t);
                void netz(_netz*n);
                _netz*netz();
                
                void ort(const _vektor3<_tg>&);
                inline _vektor3<_tg>&ort();
                void vektor(const _vektor3<_tg>&);
                inline _vektor3<_tg>&vektor();
                void zentrum(const _vektor3<_tg>&z);
                void rotation(const _tg);
                _tg rotation()const;
	            void rotationvektor(const _tg);
	            void rotationreibung(const _tg);
	            _vektor3<_tg>&rotationachse();  
                void lebensdauer(const _tg);
                void groesse(const _tg);
                void masse(const _tg);
	            void skalierung(const _tg);
	             void feldkraftg(const _tg);
                void feldkrafte(const _tg);               
                void feldkraftb(const _tg);
                void feldkraftm(const _tg);
	            
	            void farbe(const _vektor4<_to>&);
	            _vektor4<_to>&farbe();
	            void opazitaet(const _to);
	            void opazitaetexternekontrolle(const _to);
                void kurvefarbe(const _kurvehermite4<_to>&);
	            void einblenden(const bool);
	            void ausblenden(const bool);
	            void transparenz(bool additiv,bool multiplikativ);
	            
	            void planarydivergenz(const _tg o,const _tg i);
                void axialdivergenz(const _vektor3<_tg>&o,const _vektor3<_tg>&v);
                void schattenz(_textur<_tb>*st,_listebasis<_licht<_tg,_to> >*lichtliste);
	            void opazitaetsinus(const _tg rate,const _tg ratedelta,const _tg phase);
                void tontod(_ton*t,_tg l,_tg b,bool d);
                void lichttod(_licht<_tg,_to>*l,_listebasis<_licht<_tg,_to> >*ll,const _tg a);
        protected:
                //void bewegen();
                //void beschleunigengravitation();
                inline _partikelquelle*partikelquelle();
               
        private:
                _welt*pwelt;
                _zeit*pzeit;
                _tg pzeitletzte;
	            _tg pfanim;
	            _tg pfanimnorm;
                _partition::_zone*pzone;
                _partition::_sektor*psektor;
                _partikelquelle*ppartikelquelle;
                _listenknoten<_partikel>*pknotenintern;
                _partikelquelle*ppartikelquelleleben;
                _partikelquelle*ppartikelquelletod;

	            _textur<_tb>*ptextur;
	            _netz*pnetz;
	            _liste<_schatten<_tg,_to> > pschattenliste;

                bool pkollision;
                _tg pkollisionreflektierend;
                _tg pkollisionabgleitend;
                _tg pkollisionanhaftend;
	            bool pkollisionz;
	            _tg pkollisionzort;                

                _vektor3<_tg> port;
                _vektor3<_tg> pvektor;
                bool pzentrumbenutzen;
                _vektor3<_tg> pzentrum;
                
                _tg palter;
                _tg plebensdauermaximal;
                _tg plebensdauerstart;
              
                _tg protation;
	            _tg protationvektor;
	            _tg protationreibung;
	            _vektor3<_tg> protationachse;
	            
	            _tg pmasse;
                _tg pgroesse;
	            bool pskalierung;
	            _tg pskalierungwert;
                
                _tg pfeldkraftg;
                _tg pfeldkrafte;               
                _tg pfeldkraftb;
                _tg pfeldkraftm;     
                _vektor3<_tg> pfeldkraftghomogen;         

	            _vektor4<_to> pfarbe;
	            bool pkurvefarbebenutzen;
	            _kurvehermite4<_to> pkurvefarbe;
                bool pausblenden;
	            bool peinblenden;
	            _to popazitaetzeichnung;
	            _to popazitaetexternekontrolle;	       
	            bool ptransparenzadditiv;     
	            bool ptransparenzmultiplikativ;     
	            
	            bool pplanarydivergenz;
	            _tg pplanarydivergenzort;
	            _tg pplanarydivergenzintensitaet;

	            bool paxialdivergenz;
	            _vektor3<_tg> paxialdivergenzort;
	            _vektor3<_tg> paxialdivergenzvektor;	            
	            
	            bool pschattenz;
	            
	            bool popazitaetsinus;
	            _tg popazitaetsinusrate;
	            _tg popazitaetsinusphase;
	            _tg popazitaetsinusratedelta;

	            _ton*ptontod;
	            _tg ptontodlautstaerke;
	            _tg ptontodbeugung;
	            bool ptontodbeugungdoppler;
	            
	            _licht<_tg,_to>*plichttod;
	            _liste<_licht<_tg,_to> >*plichttodliste;
	            _tg plichttodaddition;
};
_vektor3<_tg>&_partikel::ort(){
                                                                return(port);
};
_vektor3<_tg>&_partikel::vektor(){
                                                                return(pvektor);
};
_partikelquelle* _partikel::partikelquelle(){
                                                                return(ppartikelquelle);
};





























//******************************************************************************************************************************************************************************************************
//                                                              P A R T I K E L Q U E L L E S P R I T E 
//******************************************************************************************************************************************************************************************************

class _partikelquellesprite:public _partikelquelle,public virtual _editierbar,public _basis::_speicherbarargument<_partikelquellesprite>{
        public:
                _partikelquellesprite(_listebasis<_partikelquelle >*l,_listebasis<_partikel>*lp,_welt*w,_zeit*z,_vektor3<_tg> o,_vektor3<_tg> v,_tg life,_textur<_tb>*tex);
                _partikelquellesprite(_listebasis<_partikelquelle >*l,_listebasis<_partikel>*lp,_welt*w,_zeit*z,_partition::_zone*zone,_vektor3<_tg> o,_vektor3<_tg> v,_tg life,_textur<_tb>*tex);
                virtual ~_partikelquellesprite();
                void spriteliste(_listebasis<_sprite>*);
                _listebasis<_sprite>*spriteliste();
                void kopieren(const _partikelquellesprite*);
                virtual void generieren(); 
               // void rotation(const _tg);
               //void rotationtoleranz(const _tg);
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_partikelquellesprite>*);
                void speichern(_speicherbardynamisch<_partikelquellesprite>*);
                char assoziieren(_speicherbardynamisch<_partikelquellesprite>*);
                //editieren
                virtual void einhaengendialog(_dynamischerdialog*);
                virtual void auslesendialog(_dynamischerdialog*);                
        private:
               // _tg prot;
               // _tg prottol;
                _listebasis<_sprite>*pspriteliste; //hier werden die sprites eingehängt
};                

//******************************************************************************************************************************************************************************************************
//                                                              P A R T I K E L Q U E L L E S P R I T E P H Y S I K A L I S C H 
//******************************************************************************************************************************************************************************************************

class _partikelquellespritephysikalisch:public _partikelquellesprite{
        public:
                _partikelquellespritephysikalisch(_listebasis<_partikelquelle >*l,_listebasis<_partikel>*lp,_welt*w,_zeit*z,_partition::_zone*zone,_vektor3<_tg> o,_vektor3<_tg> v,_tg life,_textur<_tb>*tex);
                virtual ~_partikelquellespritephysikalisch();
                virtual void animieren();
                virtual void generieren(); 
                void feld(const bool);
                bool feld() const;
                void feldfrequenz(const _tg);
                _tg  feldfrequenz() const;
                void reibung(const _tg);
                _tg  reibung() const;
                void temperatur(const _tg);
                _tg  temperatur() const;
                _vektor3<_tg> feldvektor();
                void visualisieren();
                void devisualisieren();
        private:
                _tg pdichte;                                    //g/cm3
                _tg pdichtetoleranz;                            //g/cm3
                _tg pdurchmesser;                               //mykrometer
                _tg pdurchmessertoleranz;                       //mykrometer
                _tg pladungsdichte;                             //1.602e-19 C/pm2
                _tg pladungsdichtetoleranz;                     //1.602e-19 C/pm2
                bool pfeld;
                _weltdebugpfeil*parrow;
                _tg pfeldfreq;
                _tg preibung;
                _tg ptemperatur;
};

//******************************************************************************************************************************************************************************************************
//                                                              S P R I T E 
//******************************************************************************************************************************************************************************************************

class _sprite:public _listenknotenbasis<_sprite >{
        public:
                _sprite(_welt*,_listebasis<_sprite >*,_vektor3<_tg>,_vektor3<_tg>,_vektor3<_tg>,_textur<_tb>*);
                virtual ~_sprite();
                void zeichnen(_grafik*,_kamera<_tg>*);
                void animieren();
                void ort(const _vektor3<_tg>);
                void rotation(const _tg);
                void farbe(const _vektor4<_to>&);
                void ebene(const _vektor3<_tg>,const _vektor3<_tg>);
        private:
                _welt*pwelt;
                _vektor3<_tg> port;
                _vektor3<_tg> pebene[2];
                _tg plaenge[2];
                _textur<_tb>*ptextur;
                _vektor2<_tg> ptexvec[4];
                _vektor4<_to> pfarbe;
                _tg protation;
};


//******************************************************************************************************************************************************************************************************
//                                                              P A R T I K E L S P R I T E 
//******************************************************************************************************************************************************************************************************

class _partikelsprite:public _partikel,public _sprite{
        public:
                _partikelsprite(_welt*,_zeit*,_partikelquelle*,_listebasis<_sprite >*,_vektor3<_tg>,_vektor3<_tg>,_vektor3<_tg>,_vektor3<_tg>,_tg,_textur<_tb>*);
                virtual ~_partikelsprite();
               // virtual void animieren();
        protected:
                virtual void animierendarstellung();
        private:
};                

//******************************************************************************************************************************************************************************************************
//                                                              P A R T I K E L S P R I T E P H Y S I K A L I S C H 
//******************************************************************************************************************************************************************************************************

class _partikelspritephysikalisch:public _partikelsprite{
        public:
                _partikelspritephysikalisch(_welt*,_zeit*,_partikelquelle*,_listebasis<_sprite >*,_vektor3<_tg>,_vektor3<_tg>,_vektor3<_tg>,_vektor3<_tg>,_tg,_textur<_tb>*,_tg,_tg,_tg);
                virtual ~_partikelspritephysikalisch();
                virtual void animieren();
        private:
                _tg pdichte;                                    //g/cm3
                _tg pdurchmesser;                              //mykrometer
                _tg pladungsdichte;                             //1.602e-19 C/pm2
                _tg pladung;
                _tg poberflaeche;
                _partikelquellespritephysikalisch*pqsp;
};





#endif

