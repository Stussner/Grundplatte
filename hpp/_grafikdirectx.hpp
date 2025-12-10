//******************************************************************************************************************************************************************************************************
//  Projekt     : grundplatte
//  Modul       : _grafikdirectx.hpp
//  Datum       : 24.08.2008
//******************************************************************************************************************************************************************************************************

#ifndef _grafikdirectxh_included
#define _grafikdirectxh_included
#include <_global.hpp>
#include <_system.hpp>
#include <_grafik.hpp>
#include <_text.hpp>
#include <_vektor.hpp>
#include <_bild.hpp>
#include <_datei.hpp>
#include <math.h>
#ifdef GRUNDPLATTE_UNTER_WINDOWS
#include <windows.h>
#include "d3dx.h"
//#define DXAPPLICATIONNAME L"Dx7 <-> G - Test"
//******************************************************************************************************************************************************************************************************
//                                                              F O R W A R D S 
//******************************************************************************************************************************************************************************************************


class _grafikmodus;
class _grafikdirectx;
class _bildhardwaredirectx;


void grafikmodusaktuell(unsigned int&wx,unsigned int&wy,unsigned int&bpp,unsigned int&rate);
void lesengrafikmodus(_listebasis<_grafikmodus>*l);
_grafikmodus* bestergrafikmodus(_listebasis<_grafikmodus>*l,unsigned int near_width,unsigned int near_height);



//******************************************************************************************************************
//	                        									G R A F I K M O D U S
//******************************************************************************************************************
class _grafikmodus:public _listenknotenbasis<_grafikmodus>{
        public:
                _grafikmodus(_listebasis<_grafikmodus>*l,unsigned int wx,unsigned int wy,unsigned int bpp,unsigned int r);
                virtual ~_grafikmodus();
        public:
                unsigned int breite;
                unsigned int hoehe;
                unsigned int tiefe;
                unsigned int rate;                
};


 
//*************************************************************************************************************************************************************************
//                                                              W I N  :: G R A P H I C D I R E C T X
//*************************************************************************************************************************************************************************

 class _grafikdirectx:public ::_grafik{
        public:
                _grafikdirectx(void*ha,bool fullscreen,unsigned int x,unsigned int y,unsigned int fullscreenwidth,unsigned int fullscreenheight,unsigned int fullscreendepth,unsigned int fullscreenrate,HINSTANCE hi,HINSTANCE prev);
            
                virtual ~_grafikdirectx();
                void gemeinsamedaten(_grafik*g);
				void vollbildwechsel(bool full);
                bool unterstuetzttexturnichthochzwei();
				bool unterstuetzttexturrechteckig();
                virtual bool validieren();
				HRESULT modusgeaendert();
                static LRESULT PASCAL prozess(HWND,UINT,WPARAM,LPARAM);
                virtual void setzen(bool fullscr,unsigned int wx,unsigned int wy,unsigned int de,unsigned int ra);
                void aktivitaet(const bool);
                bool aktivitaet() const;
                void groesse(unsigned int, unsigned int);
                void position(_tg,_tg);
                virtual bool szenebeginn();
                virtual void szeneende();
                //Transformation
                virtual void ladenmatrixprojektion(_matrix44<_tm>*);
                virtual void ladenmatrixwelt(_matrix44<_tm>*);
                virtual void ladenmatrixmodell(_matrix44<_tm>*);                
                virtual void matrixprojektion(_matrix44<_tm>*);
                virtual void matrixwelt(_matrix44<_tm>*);
                virtual void matrixmodell(_matrix44<_tm>*);    
                virtual void orthonormal();
                virtual void orthonormal(const _tg,const _tg,const _tg,const _tg ,const _tg,const _tg);
                virtual void transformierenrueck(const _vektor3<_tg>&geraet,_vektor3<_tg>&welt);                
                virtual void sichtbereich(_tg x,_tg y,_tg w,_tg h);
                
                //Material und Licht
                virtual void licht(const unsigned int,const bool b);
                virtual void beleuchtung(const bool b);
                virtual bool beleuchtung()const;
                virtual void beleuchtungflach();
                virtual void beleuchtungrund();
                
                virtual void material(const bool b);
                virtual void materialfarbe(const _vektor4<_to>&);
                virtual void materialemission(const _vektor4<_to>&);
                virtual void materialglanz(const _vektor4<_to>&);
                virtual void materialglanzbreite(_tg);
                //Texturen und Einheiten
                virtual void textureinheit(unsigned int);
                virtual void texturoperationmultiplikativ();
                virtual void texturoperationadditiv();
                virtual void textur(const bool);
                virtual void erzeugentexturen(_listebasis<_textur<_tb> >*);
                virtual void erzeugenbild(_bild<_tb>*);
                virtual void loeschentexturen(_listebasis<_textur<_tb> >*);
                virtual void loeschenbild(_bild<_tb>*);
                virtual void bindenbild(_bild<_tb>*);
               // virtual _zeichensatzbild*erzeugenzeichensatz(int size,int weight,_zeichenkette<char>const&name);
                //Ausschuss
                virtual void ausschussflaeche(const bool);
                virtual void ausschussflaechefront();
                virtual void ausschussflaecherueck();
                
                //Buffer
                virtual bool allebufferloeschen();
                virtual void anzeigebufferloeschfarbe(const _to,const _to,const _to,const _to);
                virtual void anzeigebufferumschalten(const bool sync);
                virtual void anzeigebufferschreiben(const bool);
                virtual void tiefenbufferkondition(const bool);
                virtual void tiefenbufferschreiben(const bool);
                virtual void tiefenbufferkonditiongleich();
                virtual void tiefenbufferkonditionkleiner();
                virtual void tiefenbufferkonditionkleinergleich();
                virtual void schablonenbufferkondition(const bool);
                virtual void schablonenbufferkonditiongleich(const signed int,const unsigned int);
                virtual void schablonenbufferkonditionungleich(const signed int,const unsigned int);
                virtual void schablonenbufferkonditionimmer(const signed int,const unsigned int);
                virtual void schablonenbufferschreiben(const bool);
                virtual void schablonenbufferoperation(const signed int,const signed int,const signed int);
                virtual void schablonenbufferloeschen(); 
                virtual void maske(const bool);
                //Nebel
                virtual void nebel(bool);
                virtual void nebelmodus(unsigned int);
                virtual void nebelfarbe(const _vektor4<_to>&);
                virtual void nebeldichte(_tg d);
                virtual void nebeldistanz(_tg min,_tg max);
                //Zeichnungsstatus
                virtual void transparenz(const bool);
                virtual void transparenzadditiv(); 
                virtual void transparenzmultiplikativ(); 
                virtual void polygonverschiebung(const bool);
                virtual void polygonverschiebung(const _tg, const _tg);
                //Zeichnung
                virtual void vollbild(const _vektor4<_to>&);                     
                virtual void pixel(const _vektor3<_tg>&,const _vektor4<_to>&);
                virtual void linie(const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor4<_to>&);
                virtual void kugel(const _vektor3<_tg>&o,const _vektor4<_to>&c,const _tg radius,const unsigned int resx,const unsigned int resy); 
                virtual void polygon(_liste<_vektor3<_tg> >*);
                virtual void polygon(_liste<_vektor3<_tg> >*,const _vektor4<_to>&);
                virtual void rechteck(_bild<_tb>*b,_tg x,_tg y,_tg w,_tg h,const _vektor4<_to>&c,bool inversetexy=true);
                virtual void rechteck(_tg x,_tg y,_tg w,_tg h,const _vektor4<_to>&c);
                virtual void rechtecke(_liste<_vektor3<_tg> >*l);
                virtual void rechtecke(_liste<_vektor3<_tg> >*l,const _vektor4<_to>&col);
                virtual void rechteckstreifenzyklisch(_liste<_vektor3<_tg> >*);
                virtual void rechteckstreifenzyklisch(_liste<_vektor3<_tg> >*,_liste<_vektor3<_tg> >*);
                virtual void rechteckstreifenzyklisch(_liste<_vektor3<_tg> >*,const _vektor4<_to>&);
                virtual void rechteckstreifenzyklisch(_liste<_vektor3<_tg> >*,_liste<_vektor3<_tg> >*,const _vektor4<_to>&);
                virtual void text(const _zeichenkette<_tt>&,const ::_zeichensatz*,const _vektor3<_tg>&,const _vektor4<_to>&);
                virtual void zeichnen(const _vektor3<_tg>&,const _vektor4<_to>&);
                virtual void zeichnen(_tg*x,_to*c);
                virtual void zeichnen(_tg*x,_tg*y,_to*c);
                virtual void zeichnen(const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor4<_to>&);
                virtual void zeichnen(const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor4<_to>&,const _vektor4<_to>&);
                virtual void zeichnen(const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor4<_to>&,const _vektor4<_to>&,const _vektor4<_to>&);
                //3 punkte
                //3 4D farben
                //3,6,9 texturvektoren
                virtual void zeichnen(const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor4<_to>&,const _vektor4<_to>&,const _vektor4<_to>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&);
                virtual void zeichnen(const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor4<_to>&,const _vektor4<_to>&,const _vektor4<_to>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&);
                virtual void zeichnen(const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor4<_to>&,const _vektor4<_to>&,const _vektor4<_to>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&);
                //3 punkte
                //3 normalen
                //3 4D farben
                //3,6,9 texturvektoren
                virtual void zeichnen(const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor4<_to>&,const _vektor4<_to>&,const _vektor4<_to>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&);
                virtual void zeichnen(const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor4<_to>&,const _vektor4<_to>&,const _vektor4<_to>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&);
                virtual void zeichnen(const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor4<_to>&,const _vektor4<_to>&,const _vektor4<_to>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&);

                virtual void zeichnendebug(const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor4<_to>&,const _vektor4<_to>&,const _vektor4<_to>&);
                virtual void zeichnenabgeschnitten(const _vektor3<_tg>&,const _vektor4<_to>&);
                virtual void zeichnenabgeschnitten(const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor4<_to>&);
        public: 
                LPDIRECT3DDEVICE7 device();
                void fehler(char*,HRESULT hr);
        public:
                void erzeugenbilder(_liste<_bild<_tb> >*);
                void loeschenbilder(_liste<_bild<_tb> >*);
                void erzeugenschattenbild();
                virtual bool initialisieren();
                virtual bool uninitialisieren();
                virtual bool reinitialisieren();
       public:                
                
                
                ID3DXContext*pcontext;
                LPDIRECT3DDEVICE7 pdevice;
                LPDIRECT3D7 pd3d;
                LPDIRECTDRAW7 pdd;                
				D3DDEVICEDESC7 pcaps;

                HWND phandle;
                HINSTANCE phithis;
                HINSTANCE phiprev;
                bool pfullscreen;
                unsigned int pfullscreenwidth;
                unsigned int pfullscreenheight;
                unsigned int pfullscreendepth;
                unsigned int pfullscreenrate;
                

               _bildhardwaredirectx*paltebindung;
              //  HDC hdc;
 };
 



//******************************************************************************************************************************************************************************************************
//                                                              B I L D H A R D W A R E D I R E C T X
//******************************************************************************************************************************************************************************************************
class _bildhardwaredirectx:public _bildhardware{
        public:
                _bildhardwaredirectx(_grafikdirectx*,_bild<_tb>*);
                virtual ~_bildhardwaredirectx();
                virtual void loeschen();
                virtual void wiederherstellen();
                virtual bool binden();
                virtual void lesen(_to*t);
                virtual bool oeffnen();
                virtual _tb*daten();
                virtual void schliessen();
        private:
                _grafikdirectx*pgrafik;
                LPDIRECTDRAWSURFACE7 pddstextur;
                DDSURFACEDESC2 pdescriptor;
};
//*****************************************************************************************************************************************************************************************************+
//                                                              D A T E I L E S E   H I L F S S T R U K T U R E N 
//*****************************************************************************************************************************************************************************************************+





/*
template<class _tt> void _zeichensatzdirectx::text<_tt>(const _zeichenkette<_tt>&t,_tg x,_tg y,const _vektor4<_to>&color){
                                                                unsigned int s=t.groesse();
                                                                unsigned int prev=1e+8;
                                                                _tt old;
                                                                _tg xit=x;
                                                                _tg yit=y;
                                                                for(int n=0;n<s;n++){
                                                                 unsigned int i=(unsigned int)t.daten()[n];
                                                                 _zeichen*z=pzeichen[i];
                                                                 if(z){
                                                                 
                                                                  //zeichnung
                                                                  pgrafik->rechteck(z->bild(),xit+z->versatzx(),yit+z->versatzy()-_tg(pbase),z->breite(),z->hoehe(),color);


                                                                  xit+=z->deltax();
                                                                  if(prev!=1e+8){
                                                                   xit+=z->kernel(prev);
                                                                  };
                                                                  prev=pzeichen[i]->identifikation();
                                                                 };
                                                                };
                                                                                                                     
                                                                
};


template<class _tt> _tg _zeichensatzdirectx::breite<_tt>(_zeichenkette<_tt>&t){
                                                                unsigned int s=t.groesse();
                                                                unsigned int prev=1e+8;
                                                                _tt old;
                                                                _tg x=0;
                                                                for(int n=0;n<s;n++){
                                                                 unsigned int i=(unsigned int)t.daten()[n];
                                                                 if(pzeichen[i]){
                                                                  x+=pzeichen[i]->deltax();
                                                                  if(prev!=1e+8){
                                                                   x+=pzeichen[i]->kernel(prev);
                                                                  };
                                                                  prev=pzeichen[i]->identifikation();
                                                                 };
                                                                };
                                                                return(x);
};
template<class _tt> _tg _zeichensatzdirectx::hoehe<_tt>(_zeichenkette<_tt>&){
                                                                return((_tg)pgroesse);
};*/
#endif
#endif
