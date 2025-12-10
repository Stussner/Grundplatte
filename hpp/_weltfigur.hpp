//******************************************************************************************************************************************************************************************************
//  Projekt      : grundplatte
//  Bibliothek   : grundplatte.lib
//  Modul        : _weltfigur.hpp
//  Datum        : 29.2.2004
//  Beschreibung : 
//******************************************************************************************************************************************************************************************************
#ifndef _figurh_included
#define _figurh_included
//******************************************************************************************************************************************************************************************************
//                                                              P R E D E K L A R A T I O N 
//******************************************************************************************************************************************************************************************************
class _figur;
class _figursprite;
class _figurspieler;

#include <_global.hpp>
#include <_funktion.hpp>
#include <_welt.hpp>
#include <_weltpartition.hpp>
#include <_system.hpp>
#include <_weltpartikel.hpp>
//******************************************************************************************************************************************************************************************************
//                                                              Z Y K L I S C H E 
//******************************************************************************************************************************************************************************************************
class _welt;
template<class _to> class _textur;
//******************************************************************************************************************************************************************************************************
//                                                              F I G U R 
//******************************************************************************************************************************************************************************************************
class _figur:public _listenknotenbasis<_figur >,public _speicherbarbinaer{
        public:
                _figur(_listebasis<_figur >*,_welt*,const _vektor3<_tg>,_textur<_tb>*);
                virtual ~_figur();
                virtual void zeichnen(_grafik*,_kamera<_tg>*)=0;
                virtual void animieren(_partition::_zone*,_tastatur*,_maus<_tg>*)=0;
                virtual void sprengen()=0;
                void einfuegentexturdetonation(_textur<_tb>*);
                void einfuegentexturprojektil(_textur<_tb>*);
                void bewegenplanlos(_partition::_zone*);
                void bewegendefensiv(_partition::_zone*);
                void bewegenaggressiv(_partition::_zone*);
                void bewegen(const _vektor3<_tg>&);
                _tg kollidierenpartikel(_vektor3<_tg>&);
                _tg partei()const;
                void partei(const _tg);
                _partition::_sektor*sektoraktuell();
                void sektoraktuell(_partition::_sektor*);
                _partition::_sektor*aktualisierensektor(_partition::_zone*);
                _vektor3<_tg>&ort();//eigentlich protected
                bool sichtbar(_figur*);
				//speicherung
                bool laden(_datei*d);
				void speichern(_datei*d);
                bool assoziieren();
        protected:                
                _vektor3<_tg>&vektor();
                void vektor(const _vektor3<_tg>&);
                _welt*welt();
                _zufallsgenerator<_tg>&zufall();
                _tg gesundheit()const;
                void gesundheit(const _tg p);
                void reduzierengesundheit(_tg);
                _liste<_textur<_tb> >*texturdetonation();
                _liste<_textur<_tb> >*texturprojektil();
                
                
        private:
                _welt*pwelt;
                _vektor3<_tg> plokus;
                _vektor3<_tg> plokusalt;
                _vektor3<_tg> pvektor;
                _textur<_tb>*ptextur;
                _liste<_textur<_tb> > ptexlistdetonation;
                _liste<_textur<_tb> > ptexlistprojektil;
                _vektor3<_tg> pstart;
                _vektor3<_tg> pziel;
                _partition::_sektor*psectoraktuell;
                bool unterwegs;
                _zufallsgenerator<_tg> pzufall;
                _tg pradius;
                _tg pgesundheit;
                _tg ppartei;
                _vektor3<_tg> h;
};
//******************************************************************************************************************************************************************************************************
//                                                              F I G U R S P R I T E 
//******************************************************************************************************************************************************************************************************
class _figursprite:public _figur{
        public:
                _figursprite(_listebasis<_figur >*,_welt*,_zeit*z,const _vektor3<_tg>,_textur<_tb>*);
                virtual ~_figursprite();
                virtual void zeichnen(_grafik*,_kamera<_tg>*);
                virtual void animieren(_partition::_zone*,_tastatur*,_maus<_tg>*);
                virtual void sprengen();
                 _partikelquelle*waffe();
        private:
                _sprite*psprite;
                _partikelquelle*pwaffeq;
                _tg pwaffezeit;
                _tg plength[2];
                _tg prot;
                _tg protvec;
                _zeit*pzeit;
                
};
//******************************************************************************************************************************************************************************************************
//                                                              F I G U R S P I E L E R 
//******************************************************************************************************************************************************************************************************
class _figurspieler:public _figur{
        public:
                _figurspieler(_listebasis<_figur >*,_welt*,_zeit*z,const _vektor3<_tg>&);
                virtual ~_figurspieler();
                virtual void zeichnen(_grafik*,_kamera<_tg>*);
                _vektor3<_tg> berechnenbewegung(_tastatur*,_tg);
                _vektor2<_tg> berechnenrotation(_maus<_tg>*);
                virtual void animieren(_partition::_zone*,_tastatur*,_maus<_tg>*);
                virtual void sprengen();
                _kamera<_tg>*kamera();
                _partikelquelle*partikelquelle();
        private:
                _zeit*pzeit;
                _kamera<_tg>*pcam;
                _partikelquellesprite*pq;
                _vektor3<_tg> mv;
                _vektor2<_tg> rv;
                _tg pspeed;
                _tg prot;
                _tg protvec;
                _vektor3<_tg> kollvektor;
};
#endif
