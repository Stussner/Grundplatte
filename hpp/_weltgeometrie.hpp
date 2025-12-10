//******************************************************************************************************************************************************************************************************
//  Project     : grundplatte
//  Library     : _grundplatte.lib
//  Module      : _weltgeometrie.hpp
//  Date        : 1.1.2003
//  Description : 
//******************************************************************************************************************************************************************************************************
#ifndef _geometrieh_included
#define _geometrieh_included

//******************************************************************************************************************************************************************************************************
//                                                              F O R W A R D 
//******************************************************************************************************************************************************************************************************
 class _geometrie;
 class _geometrienetz;
 class _geometriescheibe;
 class _geometrieflaechehermite;
 class _geometriequader;
 class _geometriezylinder;
 class _geometriekonus;
 class _geometrietorus;
 class _geometriekreuzdrei;
 class _geometriekreuz;
 class _geometriekreuzbalken;
 class _geometriekugel;
 class _geometriehalbkugel;
 class _geometrietorusknoten;
 class _geometriegang;
 class _geometrieraum;

 class _vertexzeiger;
 class _schweisskante;
 class _modifikation;
//#include <_welt.hpp>
//#include <_weltintersektion.hpp>
//******************************************************************************************************************************************************************************************************
//                                                              Z Y K L I S C H E 
//******************************************************************************************************************************************************************************************************
 class _welt;
 class _netz;
 class _polygon;
 class _vertex;
 class _verbindervertexpolygon;
 class _worldebugcross;


#include <_global.hpp>
#include <_datei.hpp> //temporär : nur für logfile
#include <_editionwin.hpp>
#include <_funktion.hpp>
//******************************************************************************************************************************************************************************************************
//                                                              G E O M E T R I E 
//******************************************************************************************************************************************************************************************************
class _geometrie:public _listebasis<_modifikation >,public _listenknotenbasis<_geometrie >,public _editierbar,public _speicherbarbinaer{
        public:
                _geometrie(_listebasis<_geometrie >*,const _vektor3<_tg>,_textur<_tb>*);
                _geometrie(_listebasis<_geometrie >*,const _vektor3<_tg>,const _vektor3<_tg>,_textur<_tb>*);
                _geometrie(_listebasis<_geometrie >*,const _vektor3<_tg>,const _vektor3<_tg>,const _vektor3<_tg>,_textur<_tb>*);
                _geometrie(_listebasis<_geometrie >*,const _vektor3<_tg>,const _vektor3<_tg>,const _vektor3<_tg>,const _vektor3<_tg>,_textur<_tb>*);
                virtual ~_geometrie();
                virtual _netz* erzeugen()=0;
                virtual void erzeugenstandardtexturkoordinaten(_netz*)=0;

                _vektor3<_tg> ort() const;
                void ort(const _vektor3<_tg>);
                void ort(const _tg,const _tg,const _tg);
                void markierung(const int i);
                int markierung()const;
                
                _vektor3<_tg> vektor(const unsigned int) const;
                bool vektor(const _vektor3<_tg>,const _vektor3<_tg>,const _vektor3<_tg>);
                void vektor(const _tg,const _tg,const _tg);
                bool vektor(const unsigned int,const _vektor3<_tg>);
                bool vektor0(const _vektor3<_tg>);
                bool vektor1(const _vektor3<_tg>);
                bool vektor2(const _vektor3<_tg>);
                
                void texturort(const _vektor2<_tg>&o);
                _vektor2<_tg>&texturort();
                void texturvektor(const _tg,const _tg);
                _vektor2<_tg>&texturvektor(const unsigned int);
                bool pruefenausrichtung() const;
                
                _vektor4<_to> farbe()const;
                void farbe(const _vektor4<_to>);
                void farbe(const _to,const _to,const _to);
                void farbe(const _to,const _to,const _to,const _to);
                
                _zeichenkette<char> name()const;
                void name(const _zeichenkette<char>);
                
                bool aufloesungsskalierung(const _tg);
                _tg aufloesungsskalierung() const;
                
                void standardtextur(_textur<_tb> *tex)  { pdefaulttexture = tex; }  // added by OoS (25.03.2005)
                _textur<_tb>*standardtextur();
                _textur<_tb>*textur();
                void textur(_textur<_tb>*);
                void texturfront(_textur<_tb>*);
                void texturrueck(_textur<_tb>*);
                bool texturteilung() const;
                void texturteilung(const bool);
                //void scale(_tg);
                //_tg scale() const;

                virtual void einhaengendialog(_dynamischerdialog*);
                virtual void auslesendialog(_dynamischerdialog*);
				//speicherung
                bool laden(_datei*d);
				void speichern(_datei*d);
                bool assoziieren();


                
        protected:
                void duplizieren(_liste<_schweisskante >*,_liste<_schweisskante >*);
                void verschweissen(_netz*,_schweisskante*,_schweisskante*,_liste<_schweisskante >*);
                _polygon*erzeugendreieck(_netz*,_vektor3<_tg>&,_vektor3<_tg>&,_vektor3<_tg>&,_vertexzeiger*,_vertexzeiger*,_vertexzeiger*,/*_vektor3<_tg>&,_vektor3<_tg>&,_vektor3<_tg>&,*/_textur<_tb>*);
                _polygon*erzeugenrechteck(_netz*,_vektor3<_tg>&,_vektor3<_tg>&,_vektor3<_tg>&,_vektor3<_tg>&,_vertexzeiger*,_vertexzeiger*,_vertexzeiger*,_vertexzeiger*,/*_vektor3<_tg>&,_vektor3<_tg>&,_vektor3<_tg>&,_vektor3<_tg>&,*/_textur<_tb>*);
                _polygon*erzeugenpolygon(_netz*,_liste<_vektor3<_tg> >&,_liste<_vertexzeiger >&,/*_liste<_vektor3<_tg> >&,*/_textur<_tb>*);
                
                _polygon*erzeugennetz(_netz*,_vektor3<_tg>,_vektor3<_tg>,_vektor3<_tg>,unsigned int,unsigned int,_liste<_schweisskante >*);
                _polygon*erzeugennetzdreieckig(_netz*,_vektor3<_tg>,_vektor3<_tg>,_vektor3<_tg>,unsigned int,unsigned int,_liste<_schweisskante >*);
                _polygon*erzeugenrohr(_netz*,_vektor3<_tg>,_vektor3<_tg>,_vektor3<_tg>,_vektor3<_tg>,unsigned int,unsigned int,_liste<_schweisskante >*);
                _polygon*erzeugenkonus(_netz*,_vektor3<_tg>,_vektor3<_tg>,_vektor3<_tg>,_vektor3<_tg>,unsigned int,unsigned int,_liste<_schweisskante >*);
                _polygon*erzeugentorus(
                _netz*netz,
                _vektor3<_tg> o,
                _vektor3<_tg> v0,
                _vektor3<_tg> v1,
                _vektor3<_tg> v2,
                _tg r0,
                _tg r1,
                _tg anteil0start,
                _tg anteil0ende,
                _tg anteil1start,
                _tg anteil1ende,
                unsigned int resx,
                unsigned int resy,
                _liste<_schweisskante>*lfe);
                _polygon*erzeugenscheibe(_netz*,_vektor3<_tg>,_vektor3<_tg>,_vektor3<_tg>,unsigned int,_liste<_schweisskante >*);
                _polygon*erzeugenkugelschale(_netz*,_vektor3<_tg>,_vektor3<_tg>,_vektor3<_tg>,_vektor3<_tg>,unsigned int,unsigned int,_liste<_schweisskante >*);
                _polygon*erzeugentorusknoten(_netz*,_vektor3<_tg>,_vektor3<_tg>,_vektor3<_tg>,_vektor3<_tg>,unsigned int,unsigned int,_liste<_schweisskante >*);
                
                _polygon*erzeugentexturkoordinatennetz(_polygon*,_vektor2<_tg>,_vektor2<_tg>,_vektor2<_tg>,unsigned int,unsigned int);
                _polygon*erzeugentexturkoordinatenkonus(_polygon*,_vektor2<_tg>,_vektor2<_tg>,_vektor2<_tg>,unsigned int,unsigned int);
                _polygon*erzeugentexturkoordinatenscheibe(_polygon*,_vektor2<_tg>,_vektor2<_tg>,_vektor2<_tg>,unsigned int);
                _polygon*erzeugentexturkoordinatenscheibe(_polygon*,_vektor2<_tg>,_vektor2<_tg>,_vektor2<_tg>,unsigned int,unsigned int);
                
        private:
                _vektor3<_tg> plocus;
                _vektor3<_tg> pvx;
                _vektor3<_tg> pvy;
                _vektor3<_tg> pvz;
                
                _vektor2<_tg> ptort;
                _vektor2<_tg> ptvx;
                _vektor2<_tg> ptvy;
                
                _vektor4<_to> pcolor;
                _zeichenkette<char> pname;
                _textur<_tb>*pdefaulttexture;
                _textur<_tb>*pdefaulttextureback;
                _tg presolutionscale; 
               // _tg pscale;
                bool ptexturedivision;
                int pmarkierung;
                
};
//******************************************************************************************************************************************************************************************************
//                                                              G E O M E T R I E N E T Z
//******************************************************************************************************************************************************************************************************
class _geometrienetz:public _geometrie{
        public:
                _geometrienetz(_listebasis<_geometrie >*,const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor3<_tg>&,_textur<_tb>*);
                _geometrienetz(_listebasis<_geometrie >*,const _vektor3<_tg>&o,const _tg wx,const _tg wy,_textur<_tb>*);
                virtual ~_geometrienetz();
                virtual _netz* erzeugen();
                virtual void erzeugenstandardtexturkoordinaten(_netz*);
                void aufloesung(_vektor2<unsigned int>);
                void aufloesung(unsigned int ax,unsigned int ay);
                unsigned int aufloesung(const unsigned int i);
                void groesse(const _tg wx,const _tg wy);
                void groesse(const _vektor3<_tg>&wx,const _vektor3<_tg>&wy);
                
                void texturkoordinatenlaenge(const _tg,const _tg);
                virtual void einhaengendialog(_dynamischerdialog*);
                virtual void auslesendialog(_dynamischerdialog*);
        private:                
                _vektor2<unsigned int> presolution;
                _vektor2<_tg> ptclength;
                
};
//******************************************************************************************************************************************************************************************************
//                                                              G E O M E T R I E S C H E I B E
//******************************************************************************************************************************************************************************************************
class _geometriescheibe:public _geometrie{
        public:
                _geometriescheibe(_listebasis<_geometrie >*,const _vektor3<_tg>&loc,const _vektor3<_tg>&radx,const _vektor3<_tg>&radz,_textur<_tb>*);
                virtual ~_geometriescheibe();
                virtual _netz* erzeugen();
                virtual void erzeugenstandardtexturkoordinaten(_netz*);

                void aufloesung(unsigned int ax);
				void radius(const _tg rx,const _tg rz);
                void radius(const _vektor3<_tg>&rx,const _vektor3<_tg>&rz);
                 _vektor3<_tg> radius(const unsigned int) const;

                void texturkoordinatenlaenge(const _tg lx,const _tg ly);
                void texturkoordinatenverschiebung(const _tg lx,const _tg ly);
                virtual void einhaengendialog(_dynamischerdialog*);
                virtual void auslesendialog(_dynamischerdialog*);
        private:
                unsigned int presolution;
                _vektor2<_tg> ptclength;
                _vektor2<_tg> ptcoffset;
                
};
//******************************************************************************************************************************************************************************************************
//                                                              G E O M E T R I E F L A E C H E H E R M I T E 
//******************************************************************************************************************************************************************************************************
class _geometrieflaechehermite:public _geometrie{
        public:
                _geometrieflaechehermite(_listebasis<_geometrie >*,_textur<_tb>*);
                virtual ~_geometrieflaechehermite();
                virtual _netz*erzeugen();
                virtual void erzeugenstandardtexturkoordinaten(_netz*);
                void aufloesung(_vektor2<unsigned int>);
                void texturkoordinatenlaenge(const _tg,const _tg);
                virtual void einhaengendialog(_dynamischerdialog*);
                virtual void auslesendialog(_dynamischerdialog*);
                _flaechehermite<_tg>*flaeche();
        private:                
                _vektor2<unsigned int> presolution;
                _vektor2<_tg> ptclength;
                _flaechehermite<_tg> pflaeche;
                
};
//******************************************************************************************************************************************************************************************************
//                                                              G E O M E T R I E Q U A D E R
//******************************************************************************************************************************************************************************************************
class _geometriequader:public _geometrie{
        public:
                _geometriequader(_listebasis<_geometrie >*,_vektor3<_tg>,_tg,_tg,_tg,_textur<_tb>*);
                _geometriequader(_listebasis<_geometrie >*,_vektor3<_tg>,_vektor3<_tg>,_vektor3<_tg>,_vektor3<_tg>,_textur<_tb>*);
                virtual ~_geometriequader();
                virtual _netz* erzeugen();
                virtual void erzeugenstandardtexturkoordinaten(_netz*);
                void aufloesung(_vektor<unsigned int>);
                void laenge(_tg,_tg,_tg);
                void texturkoordinatenlaenge(const _tg,const _tg,const _tg);
                virtual void einhaengendialog(_dynamischerdialog*);
                virtual void auslesendialog(_dynamischerdialog*);
                
        private:                
                _vektor<unsigned int> presolution;
                _vektor3<_tg> ptclength;
};
//******************************************************************************************************************************************************************************************************
//                                                              G E O M E T R I E Z Y L I N D E R 
//******************************************************************************************************************************************************************************************************
class _geometriezylinder:public _geometrie{
        using _geometrie::vektor;
        public:
                _geometriezylinder(_listebasis<_geometrie >*,_vektor3<_tg>,_vektor3<_tg>,_vektor3<_tg>,_textur<_tb>*);
                _geometriezylinder(_listebasis<_geometrie >*,_vektor3<_tg>,_vektor3<_tg>,_vektor3<_tg>,_vektor3<_tg>,_textur<_tb>*);
                virtual ~_geometriezylinder();
                virtual _netz* erzeugen();
                virtual void erzeugenstandardtexturkoordinaten(_netz*);

                void aufloesung(_vektor<unsigned int>);
                void aufloesung(unsigned int ax,unsigned int ay);
                void offen(const bool);
                bool offen()const;
                void vektor(const _vektor3<_tg>);
                _vektor3<_tg> vektor() const;
                void radiussingle(const _vektor3<_tg>);
                void radius(const _vektor3<_tg>,const _vektor3<_tg>);
                _vektor3<_tg> radius(const unsigned int) const;
                void texturkoordinatenlaenge(const _tg lx,const _tg ly,const _tg lz,const _tg lw);
                void texturkoodinatenverschiebung(const _tg ox,const _tg oy,const _tg oz,const _tg ow);
                void texturkoordinatenlaenge(const _tg,const _tg,const _tg);
                virtual void einhaengendialog(_dynamischerdialog*);
                virtual void auslesendialog(_dynamischerdialog*);                
        private:                
                _vektor<unsigned int> presolution;
                bool poffen;
                _vektor4<_tg> ptclength;
                _vektor4<_tg> ptcoffset;
                
};
//******************************************************************************************************************************************************************************************************
//                                                              G E O M E T R I E K O N U S
//******************************************************************************************************************************************************************************************************
class _geometriekonus:public _geometrie{
        using _geometrie::vektor;
        public:
                _geometriekonus(_listebasis<_geometrie >*,_vektor3<_tg>,_vektor3<_tg>,_vektor3<_tg>,_vektor3<_tg>,_textur<_tb>*);
                virtual ~_geometriekonus();
                virtual _netz* erzeugen();
                virtual void erzeugenstandardtexturkoordinaten(_netz*);

                void aufloesung(unsigned int rx,unsigned int ry);
                
                void vektor(const _vektor3<_tg>);
                _vektor3<_tg> vektor() const;
                void radiussingle(const _vektor3<_tg>);
                void radius(const _vektor3<_tg>,const _vektor3<_tg>);
                _vektor3<_tg> radius(const unsigned int) const;
                void texturkoordinatenlaenge(const _tg lx,const _tg ly,const _tg lz,const _tg lw);
                void texturkoodinatenverschiebung(const _tg ox,const _tg oy,const _tg oz,const _tg ow);
                void texturkoordinatenlaenge(const _tg,const _tg,const _tg);
                virtual void einhaengendialog(_dynamischerdialog*);
                virtual void auslesendialog(_dynamischerdialog*);                
        private:                
                _vektor<unsigned int> presolution;
                _vektor4<_tg> ptclength;
                _vektor4<_tg> ptcoffset;
                
};
//******************************************************************************************************************************************************************************************************
//                                                              G E O M E T R I E T O R U S 
//******************************************************************************************************************************************************************************************************
class _geometrietorus:public _geometrie{
        using _geometrie::vektor;
        public:
                _geometrietorus(_listebasis<_geometrie >*,const _vektor3<_tg>&o,const _vektor3<_tg>&v0,const _vektor3<_tg>&v1,const _vektor3<_tg>&v2,const _tg r0,const _tg r1,_textur<_tb>*);
                virtual ~_geometrietorus();
                virtual _netz* erzeugen();
                virtual void erzeugenstandardtexturkoordinaten(_netz*);
                void aufloesung(_vektor<unsigned int>);
                void radius(_tg);///beide setzen
                void radius(const unsigned int i,const _tg r);//eins setzen
                _tg radius(const unsigned int) const;//lesen
                void texturkoordinatenlaenge(const _tg lx,const _tg ly);
                void texturkoodinatenverschiebung(const _tg ox,const _tg oy);
                virtual void einhaengendialog(_dynamischerdialog*);
                virtual void auslesendialog(_dynamischerdialog*);                
        private:                
                _vektor<unsigned int> presolution;
                _vektor2<_tg> ptclength;
                _vektor2<_tg> ptcoffset;
                _tg pradius[2];
                _tg panteil0start;
                _tg panteil0ende;
                _tg panteil1start;
                _tg panteil1ende;
};
//******************************************************************************************************************************************************************************************************
//                                                              G E O M E T R I E K R E U Z D R E I
//******************************************************************************************************************************************************************************************************
class _geometriekreuzdrei:public _geometrie{
        public:
                _geometriekreuzdrei(_listebasis<_geometrie >*,
                _vektor3<_tg>,_vektor3<_tg>,_vektor3<_tg>,_vektor3<_tg>, //gesamter vektorraum
                _tg,_tg, //x-teiler
                _tg,_tg, //y-teiler
                _textur<_tb>*);
                virtual ~_geometriekreuzdrei();
                virtual _netz* erzeugen();
                virtual void erzeugenstandardtexturkoordinaten(_netz*);
                void aufloesung(_vektor<unsigned int>);
               /* void vektor0(_vektor3<_tg>);
                void vektor1(_vektor3<_tg>);
                void vektor2(_vektor3<_tg>);*/
                void tile0(_tg,_tg);
                void tile1(_tg,_tg);
        //protected:
        //        bool pruefenausrichtung()const;
        private:                
                _vektor<unsigned int> presolution;
                /*_vektor3<_tg> pvx;
                _vektor3<_tg> pvy;
                _vektor3<_tg> pvz;*/
                _vektor2<_tg> ptx;
                _vektor2<_tg> pty;
};
//******************************************************************************************************************************************************************************************************
//                                                              G E O M E T R I E K R E U Z
//******************************************************************************************************************************************************************************************************
class _geometriekreuz:public _geometrie{
        public:
                _geometriekreuz(_listebasis<_geometrie >*,
                _vektor3<_tg>,_vektor3<_tg>,_vektor3<_tg>,_vektor3<_tg>, //gesamter vektorraum
                _tg,_tg, //x-teiler
                _tg,_tg, //y-teiler
                _tg,_tg, //z-teiler
                _textur<_tb>*);
                virtual ~_geometriekreuz();
                virtual _netz* erzeugen();
                virtual void erzeugenstandardtexturkoordinaten(_netz*);
                void aufloesung(_vektor<unsigned int>);
                /*void vektor0(_vektor3<_tg>);
                void vektor1(_vektor3<_tg>);
                void vektor2(_vektor3<_tg>);*/
                void tile0(_tg,_tg);
                void tile1(_tg,_tg);
                void tile2(_tg,_tg);
                //bool pruefenausrichtung()const;
        private:                
                _vektor<unsigned int> presolution;
                /*_vektor3<_tg> pvx;
                _vektor3<_tg> pvy;
                _vektor3<_tg> pvz;*/
                _vektor2<_tg> ptx;
                _vektor2<_tg> pty;
                _vektor2<_tg> ptz;
};
//******************************************************************************************************************************************************************************************************
//                                                              G E O M E T R I E K R E U Z B A L K E N
//******************************************************************************************************************************************************************************************************
class _geometriekreuzbalken:public _geometrie{
        public:
                _geometriekreuzbalken(_listebasis<_geometrie >*,_vektor3<_tg>,_vektor3<_tg>,_vektor3<_tg>,_vektor3<_tg>,_tg,_textur<_tb>*);
                virtual ~_geometriekreuzbalken();
                virtual _netz* erzeugen();
                virtual void erzeugenstandardtexturkoordinaten(_netz*);
                void aufloesung(_vektor<unsigned int>);
                void breite(_tg);
                virtual void einhaengendialog(_dynamischerdialog*);
                virtual void auslesendialog(_dynamischerdialog*);                
                
        private:                
                _vektor<unsigned int> presolution;
                _tg pwidth;
};
//******************************************************************************************************************************************************************************************************
//                                                              G E O M E T R I E K U G E L
//******************************************************************************************************************************************************************************************************
class _geometriekugel:public _geometrie{
        public:
                _geometriekugel(_listebasis<_geometrie >*,_vektor3<_tg>,_vektor3<_tg>,_vektor3<_tg>,_vektor3<_tg>,_textur<_tb>*);
                virtual ~_geometriekugel();
                virtual _netz* erzeugen();
                virtual void erzeugenstandardtexturkoordinaten(_netz*);
                void aufloesung(unsigned int,unsigned int);
                virtual void einhaengendialog(_dynamischerdialog*);
                virtual void auslesendialog(_dynamischerdialog*);                         
        private:                
                _vektor<unsigned int> presolution;
                
};
//******************************************************************************************************************************************************************************************************
//                                                              G E O M E T R I E H A L B K U G E L
//******************************************************************************************************************************************************************************************************
class _geometriehalbkugel:public _geometrie{
        public:
                _geometriehalbkugel(_listebasis<_geometrie >*,_vektor3<_tg>,_vektor3<_tg>,_vektor3<_tg>,_vektor3<_tg>,_textur<_tb>*);
                virtual ~_geometriehalbkugel();
                virtual _netz* erzeugen();
                virtual void erzeugenstandardtexturkoordinaten(_netz*);
                void aufloesung(_vektor<unsigned int>);
        private:                
                _vektor<unsigned int> presolution;
                
};
//******************************************************************************************************************************************************************************************************
//                                                              G E O M E T R I E T O R U S K N O T E N
//******************************************************************************************************************************************************************************************************
class _geometrietorusknoten:public _geometrie{
        public:
                _geometrietorusknoten(_listebasis<_geometrie >*,_vektor3<_tg>,_vektor3<_tg>,_vektor3<_tg>,_vektor3<_tg>,_textur<_tb>*);
                virtual ~_geometrietorusknoten();
                virtual _netz* erzeugen();
                virtual void erzeugenstandardtexturkoordinaten(_netz*);
                void aufloesung(_vektor<unsigned int>);
        private:                
                _vektor<unsigned int> presolution;
                
};
//******************************************************************************************************************************************************************************************************
//                                                              G E O M E T R I E G A N G
//******************************************************************************************************************************************************************************************************
class _geometriegang:public _geometrie{
        public:
                _geometriegang(_listebasis<_geometrie >*,_vektor3<_tg>,_tg,_tg,_tg,_textur<_tb>*,_textur<_tb>*,_textur<_tb>*,_textur<_tb>*);
                _geometriegang(_listebasis<_geometrie >*,_vektor3<_tg>,_vektor3<_tg>,_vektor3<_tg>,_vektor3<_tg>,_textur<_tb>*,_textur<_tb>*,_textur<_tb>*,_textur<_tb>*);
                virtual ~_geometriegang();
                virtual _netz* erzeugen();
                virtual void erzeugenstandardtexturkoordinaten(_netz*);
                void aufloesung(_vektor<unsigned int>);
                void laenge(_tg,_tg,_tg);
                void texturkoordinatenlaenge(const _tg,const _tg,const _tg);
                void iteration(const unsigned int);
        private:                
                _vektor<unsigned int> presolution;
                _vektor3<_tg> ptclength;
                _textur<_tb>*pboden;
                _textur<_tb>*pdecke;
                _textur<_tb>*pdeckenpanel;
                unsigned int prepeatx;
};
//******************************************************************************************************************************************************************************************************
//                                                              G E O M E T R I E R A U M
//******************************************************************************************************************************************************************************************************
class _geometrieraum:public _geometrie{
        public:
                _geometrieraum(_listebasis<_geometrie >*,_vektor3<_tg>,_tg,_tg,_tg,_textur<_tb>*,_textur<_tb>*,_textur<_tb>*,_textur<_tb>*,_textur<_tb>*);
                _geometrieraum(_listebasis<_geometrie >*,_vektor3<_tg>,_vektor3<_tg>,_vektor3<_tg>,_vektor3<_tg>,_textur<_tb>*,_textur<_tb>*,_textur<_tb>*,_textur<_tb>*,_textur<_tb>*);
                virtual ~_geometrieraum();
                virtual _netz* erzeugen();
                virtual void erzeugenstandardtexturkoordinaten(_netz*);
                void aufloesung(_vektor<unsigned int>);
                void laenge(_tg,_tg,_tg);
                void texturkoordinatenlaenge(const _tg,const _tg,const _tg);
        private:                
                _vektor<unsigned int> presolution;
                _vektor3<_tg> ptclength;
                _textur<_tb>*pboden;
                _textur<_tb>*pdecke;
                _textur<_tb>*pdeckenpanel;
                _textur<_tb>*psaeule;
};
//******************************************************************************************************************************************************************************************************
//                                                              V E R T E X Z E I G E R 
//******************************************************************************************************************************************************************************************************
class _vertexzeiger{
        friend class _geometrie;
        private:
                _vertexzeiger();
                void setzen(_vertex*);
                _vertex*holen();
                
        private:
                _vertex*pvertex;
                
};
//******************************************************************************************************************************************************************************************************
//                                                              S C H W E I S S K A N T E
//******************************************************************************************************************************************************************************************************
 class _schweisskante:public _liste<_vertex >{
        public:
                _schweisskante();
                virtual ~_schweisskante();
               /*void einhaengen(_vertex*);
                unsigned int anzahl();*/
        private:
                //_liste<_vertex > plist;
};
//******************************************************************************************************************************************************************************************************
//                                                              M O D I F I K A T I O N 
//******************************************************************************************************************************************************************************************************
 class _modifikation:public _listenknotenbasis<_modifikation >/*,public _listebasis<_geometrie >*/{
        public:
              //  _modifikation(_geometrie*);
                _modifikation();
                virtual ~_modifikation();
                virtual char bearbeiten(_netz*)=0;
        protected:
                void schreiben(_zeichenkette<char>);
                void schreiben(_zeichenkette<char>,int);
                void schreiben(_zeichenkette<char>,_tg);
                void schreiben(_zeichenkette<char>,_zeichenkette<char>);
                void schreiben(_zeichenkette<char>,_vektor3<_tg>);
                
                void fehler(_zeichenkette<char>);
                void fehler(_zeichenkette<char>,_zeichenkette<char>);
                void fehler(_zeichenkette<char>,int);
                void fehler(_zeichenkette<char>,_tg);
                void fehler(_zeichenkette<char>,_vektor3<_tg>);
        private:
             //   _geometrie*pgeometry;
               // bool puseselection;
                _liste<_netz > pmeshes;
};
 
#endif  
