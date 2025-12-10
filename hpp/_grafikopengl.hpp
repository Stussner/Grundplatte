//******************************************************************************************************************************************************************************************************
//  Projekt     : grundplatte
//  Modul       : _grafikopengl.hpp
//  Datum       : 24.08.2008
//******************************************************************************************************************************************************************************************************
#ifndef _grafikopenglh_included
#define _grafikopenglh_included
#include <_global.hpp>
#include <_system.hpp>
#include <_grafik.hpp>
#include <_text.hpp>
#include <_vektor.hpp>
#include <_bild.hpp>
#include <math.h>
#ifdef GRUNDPLATTE_UNTER_WINDOWS
#include <windows.h>
//#include <gl/gl.h>
//#include <gl/glu.h>
#include <gl/glut.h>
#include <gl/glew.h>
//#include <gl/glaux.h>
#include <gl/glext.h>
//#include "extgl/extgl.h"
//#include  "glext/glext.h"



//******************************************************************************************************************************************************************************************************
//                                                              F O R W A R D S 
//******************************************************************************************************************************************************************************************************

class _grafikopengl;
class _renderkontextopengl;
class _bildhardwareopengl;


// MultiTexture-Extension Function Pointers
typedef BOOL (WINAPI *PFNWGLSWAPINTERVALEXTPROC)(int interval);
extern PFNGLMULTITEXCOORD2FARBPROC glMultiTexCoord2fARB;
extern PFNGLACTIVETEXTUREARBPROC glActiveTextureARB;
extern PFNWGLSWAPINTERVALEXTPROC wglSwapInterval;


//*************************************************************************************************************************************************************************
//                                                              W I N  :: G R A F I K O P E N G L 
//*************************************************************************************************************************************************************************


 class _grafikopengl:public ::_grafik{
        public:
        friend class _bildhardwareopengl;
                _grafikopengl();                                      //vollbildmodus, nutzung interner hdc,hwmd,hrc, die grafik hat fensterkontrolle (groesse und position)
                _grafikopengl(unsigned int,unsigned int,unsigned int,unsigned int);     //fenstermodus,  nutzung interner hdc,hwnd,hrc, die grafik hat fensterkontrolle (groesse und position)
                _grafikopengl(unsigned int,unsigned int,unsigned int,unsigned int,unsigned int); //externer modus,keine nutzung interner hdc,hwnd,hrc, keine fensterkontrolle 
                virtual ~_grafikopengl();
                static LRESULT PASCAL prozess(HWND,UINT,WPARAM,LPARAM);
                void gemeinsamedaten(_grafik*g);
                virtual bool validieren();

                virtual bool initialisieren();
                virtual bool uninitialisieren();
                virtual bool reinitialisieren();
                
				void vollbildwechsel(bool full);
                bool unterstuetzttexturnichthochzwei();
				bool unterstuetzttexturrechteckig();
                virtual void setzen(bool fullscr,unsigned int wx,unsigned int wy,unsigned int de,unsigned int ra);
                
                
                void aktivitaet(const bool);
                bool aktivitaet() const;
                void groesse(unsigned int, unsigned int);
                void position(_tg,_tg);
                HGLRC rendercontext() const;
                HDC devicecontext() const;
                virtual bool szenebeginn();
                virtual void szeneende();                
                //transformation
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
                void erzeugentexturen(_listebasis<_textur<_tb> >*);
                void erzeugenbild(_bild<_tb>*);
                void loeschentexturen(_listebasis<_textur<_tb> >*);
                void loeschenbild(_bild<_tb>*);
                void bindenbild(_bild<_tb>*);
               // virtual _zeichensatzbil*erzeugenzeichensatz(int size,int weight,_zeichenkette<char>const&name);
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
                virtual void rechteck(_bild<_tb>*b,_tg x,_tg y,_tg w,_tg h,const _vektor4<_to>&c,bool);
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
        private:
                void erzeugenbilder(_liste<_bild<_tb> >*);
                void loeschenbilder(_liste<_bild<_tb> >*);
                void erzeugenschattenbild();
        private:                
               // HDC hdc;
                HWND handle;
                HGLRC hrc;
               // bool hatkontrolle;
                _bildhardwareopengl*paltebindung;
                bool ptextur;
                
        public:                
               // GLuint schattenbild;

 };
 //******************************************************************************************************************************************************************************************************
//                                                              W I N : : R E N D E R C O N T E X T O P E N G L 
//******************************************************************************************************************************************************************************************************
 class _renderkontextopengl:public _renderkontext{
        public:
                _renderkontextopengl();
                ~_renderkontextopengl();
                HGLRC handle();
        private:
                HDC hdc;
                HWND phandle;
                HGLRC hrc;
 };

//******************************************************************************************************************************************************************************************************
//                                                              B I L D H A R D W A R E O P E N G L
//******************************************************************************************************************************************************************************************************
class _bildhardwareopengl:public _bildhardware{
        public:
                _bildhardwareopengl(_grafikopengl*,_bild<_tb>*);
                virtual ~_bildhardwareopengl();
                virtual void loeschen();
                virtual void wiederherstellen();
                virtual bool binden();
                
                virtual void lesen(_to*t);
                virtual bool oeffnen();
                virtual _tb*daten();
                virtual void schliessen();                
        private:
                unsigned int pid;                
                _grafikopengl*pgrafik;
};
//*****************************************************************************************************************************************************************************************************+
//                                                              Z E I C H E N S A T Z O P E N G L 
//*****************************************************************************************************************************************************************************************************+
/*
class _zeichensatzopengl:public ::_zeichensatz{
        public:
                _zeichensatzopengl(HDC,char*,int,int,bool italic=false,bool underline=false,bool strikeout=false);
                ~_zeichensatzopengl();

                virtual void text(const _zeichenkette<char>&,_tg x,_tg y,const _vektor4<_to>&color);
                virtual void text(const _zeichenkette<unsigned short>&,_tg x,_tg y,const _vektor4<_to>&color);
                virtual _tg breite(const _zeichenkette<_tt>&);
                virtual _tg hoehe(const _zeichenkette<_tt>&);
                virtual _zeichen*zeichen(unsigned int);
                
                
                
                //void anwaehlen(HDC);
                virtual void anwaehlen();
                virtual void abwaehlen();
                virtual void text(char*,int,int,char,char,char);
                virtual void text(char*,int,int,char,char,char,char,char,char);
                virtual void text(char*,int,int,_vektor<unsigned char>&);
                virtual void text(char*,int,int,_vektor<unsigned char>&,_vektor<unsigned char>&);
                virtual void schnellvorbereiten();
                virtual void textschnell(char*,int,int,int,_vektor<unsigned char>&,_vektor<unsigned char>&);
                virtual int charbreite() const;
                virtual int charhoehe() const;
                virtual void breite(char*,int&,int&);
        private:
                HFONT handle, oldhandle;
                int pwidth;
                int pheight;
                HDC phdc;          
};
*/
#endif
#endif
