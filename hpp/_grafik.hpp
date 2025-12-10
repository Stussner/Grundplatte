//******************************************************************************************************************************************************************************************************
//  Projekt     : grundplatte
//  Bilbliothek : _grundplatte.lib
//  Modul       : _grafik.hpp
//  Datum       : 28.12.2002
//  Änderung    : 29.08.2008
//******************************************************************************************************************************************************************************************************
#ifndef _grafikh_included
#define _grafikh_included

//******************************************************************************************************************************************************************************************************
//                                                              F O R W A R D S 
//******************************************************************************************************************************************************************************************************
class _grafik;
class _renderkontext;
class _zeichensatz;
class _zeichen;
class _zeichenkernel;
class _zeichensatzkernel;
class _zeichensatzbild;

#include <_global.hpp>
#include <_vektor.hpp>
#include <_bild.hpp>
#include <_text.hpp>
#include <_system.hpp>


//******************************************************************************************************************************************************************************************************
//                                                              G R A F I K
//******************************************************************************************************************************************************************************************************
class _grafik{
        public: //grundfunktionen
                _grafik(bool fullscreen,unsigned int x,unsigned int y,unsigned int sx,unsigned int sy,unsigned int sz,unsigned int ra);
                virtual ~_grafik();      
				void loeschenbildhardwareliste();
				virtual void gemeinsamedaten(_grafik*g)=0;
				
				
                virtual bool validieren()=0;
                virtual bool initialisieren()=0;
                virtual bool reinitialisieren()=0;
                virtual bool uninitialisieren()=0;
				virtual void vollbildwechsel(bool full)=0;
                virtual bool unterstuetzttexturnichthochzwei()=0;
				virtual bool unterstuetzttexturrechteckig()=0;

                virtual void setzen(bool fullscr,unsigned int wx,unsigned int wy,unsigned int de,unsigned int ra)=0;
                unsigned int kontext()const;
                void kontext(unsigned int);
                _listebasis<_bildhardware>*listebildhardware();
                _listebasis<_zeichensatz>*listezeichensatz();
                virtual void aktivitaet(const bool);
                virtual bool aktivitaet() const;
              //  void fensterkontrolle(const bool b);
              //  bool fensterkontrolle()const;
                virtual void groesse(unsigned int,unsigned int,unsigned int);
                virtual void groesse(unsigned int, unsigned int);
				virtual void rate(unsigned int);
				virtual void vollbildmodus(bool);
                virtual void position(_tg,_tg);
                _tg positionx() const;
                _tg positiony() const;
                _vektor3<unsigned int> groesse() const;                          //groesse auslesen
                inline unsigned int groessex() const;
                inline unsigned int groessey() const;
				inline unsigned int breite() const;
				inline unsigned int hoehe() const;
				inline unsigned int tiefe() const;
				inline unsigned int rate() const;
				inline bool vollbildmodus() const;
                void upperleft();                                               //ursprung upper left setzen
                bool upperleftis() const;                                       //ist ursprung upper left ?
                void lowerleft();                                               //lowerleft (DEFAULT)
                bool lowerleftis() const;                                       //ist lowerleft ?
                void normale(bool);                                             //normalisierungsmodus setzen
                bool normale() const;                                           //normalisierungsmodus auslesen
                void normallowest(_tg,_tg,_tg);                                 //normalisierungsbereich niedrig, zuerst benutzen !!!
                void normalhighest(_tg,_tg,_tg);                                //normalisierungsbereich hoch
                inline _tg normallowestx() const;
                inline _tg normalhighestx() const;
                inline _tg normallowesty() const;
                inline _tg normalhighesty() const;
                inline _tg normallowestz() const;
                inline _tg normalhighestz() const;
                virtual bool szenebeginn()=0;
                virtual void szeneende()=0;
                //transformation und viewport
                virtual void ladenmatrixprojektion(_matrix44<_tm>*)=0;
                virtual void ladenmatrixwelt(_matrix44<_tm>*)=0;
                virtual void ladenmatrixmodell(_matrix44<_tm>*)=0;
                virtual void matrixprojektion(_matrix44<_tm>*);
                virtual void matrixwelt(_matrix44<_tm>*);
                virtual void matrixmodell(_matrix44<_tm>*);
                inline void transformieren(_vektor3<_tg>&) const;
                virtual void orthonormal()=0;
                virtual void orthonormal(const _tg,const _tg,const _tg,const _tg ,const _tg,const _tg)=0;
                virtual void transformierenrueck(const _vektor3<_tg>&geraet,_vektor3<_tg>&welt)=0;                
                virtual void sichtbereich(_tg x,_tg y,_tg w,_tg h)=0;
                //Material und Licht
                virtual void licht(const unsigned int,const bool b)=0;
                virtual void beleuchtung(const bool b)=0;
                virtual bool beleuchtung()const=0;
                virtual void beleuchtungflach()=0;
                virtual void beleuchtungrund()=0;
                virtual void material(const bool b)=0;
                virtual void materialfarbe(const _vektor4<_to>&)=0;
                virtual void materialemission(const _vektor4<_to>&)=0;
                virtual void materialglanz(const _vektor4<_to>&)=0;
                virtual void materialglanzbreite(_tg)=0;
                //Texturen und Einheiten
                virtual void textureinheit(unsigned int)=0;
                virtual void texturoperationmultiplikativ()=0;
                virtual void texturoperationadditiv()=0;
                virtual void textur(const bool)=0;
                virtual void erzeugentexturen(_listebasis<_textur<_tb> >*)=0;
                virtual void erzeugenbild(_bild<_tb>*)=0;
                virtual void loeschentexturen(_listebasis<_textur<_tb> >*)=0;
                virtual void loeschenbild(_bild<_tb>*)=0;
                virtual void bindenbild(_bild<_tb>*)=0;
                virtual _zeichensatzbild*erzeugenzeichensatz(int size,int weight,_zeichenkette<char>const&name);
                //Ausschuss
                virtual void ausschussflaeche(const bool)=0;
                virtual void ausschussflaechefront()=0;
                virtual void ausschussflaecherueck()=0;
                //Buffer
                virtual bool allebufferloeschen()=0;
                virtual void anzeigebufferloeschfarbe(const _to,const _to,const _to,const _to)=0;
                virtual void anzeigebufferumschalten(const bool sync=true)=0;
                virtual void anzeigebufferschreiben(const bool)=0;
                virtual void tiefenbufferkondition(const bool)=0;
                virtual void tiefenbufferschreiben(const bool)=0;
                virtual void tiefenbufferkonditiongleich()=0;
                virtual void tiefenbufferkonditionkleiner()=0;
                virtual void tiefenbufferkonditionkleinergleich()=0;
                virtual void schablonenbufferkondition(const bool)=0;
                virtual void schablonenbufferkonditiongleich(const signed int,const unsigned int)=0;
                virtual void schablonenbufferkonditionungleich(const signed int,const unsigned int)=0;
                virtual void schablonenbufferkonditionimmer(const signed int,const unsigned int)=0;
                virtual void schablonenbufferschreiben(const bool)=0;
                virtual void schablonenbufferoperation(const signed int,const signed int,const signed int)=0;
                virtual void schablonenbufferloeschen()=0; 
                virtual void maske(const bool)=0;
                //Nebel
                virtual void nebel(bool)=0;
                virtual void nebelmodus(unsigned int)=0;
                virtual void nebelfarbe(const _vektor4<_to>&)=0;
                virtual void nebeldichte(_tg d)=0;
                virtual void nebeldistanz(_tg min,_tg max)=0;
                //Zeichnungsstatus
                virtual void transparenz(const bool)=0;
                virtual void transparenzadditiv()=0; 
                virtual void transparenzmultiplikativ()=0; 
                virtual void polygonverschiebung(const bool)=0;
                virtual void polygonverschiebung(const _tg, const _tg)=0;
                //Zeichnung
                virtual void vollbild(const _vektor4<_to>&)=0;                     
                virtual void pixel(const _vektor3<_tg>&,const _vektor4<_to>&)=0;                     
                virtual void linie(const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor4<_to>&)=0;
                virtual void kugel(const _vektor3<_tg>&o,const _vektor4<_to>&c,const _tg radius,const unsigned int resx,const unsigned int resy)=0; 
                
                //virtual void rechteck(_vektor3<_tg>&,_vektor3<_tg>&,_vektor4<_to>&)=0;        
                //virtual void kreis(_vektor3<_tg>&,_tg,_vektor4<_to>&)=0;                      
                //virtual void liquid(_vektor3<_tg>&,_vektor4<_to>&,_vektor4<_to>&);            
                //virtual void bild(_bild<_tb>&,_vektor3<_tg>&,_vektor3<_tg>&)=0;               
                virtual void text(const _zeichenkette<_tt>&,const ::_zeichensatz*,const _vektor3<_tg>&,const _vektor4<_to>&)=0;    
                virtual void polygon(_liste<_vektor3<_tg> >*)=0;
                virtual void polygon(_liste<_vektor3<_tg> >*,const _vektor4<_to>&)=0;
                virtual void rechteck(_bild<_tb>*b,_tg x,_tg y,_tg w,_tg h,const _vektor4<_to>&c,bool inversetexy=true)=0;
                virtual void rechteck(_tg x,_tg y,_tg w,_tg h,const _vektor4<_to>&c)=0;
                virtual void rechtecke(_liste<_vektor3<_tg> >*l)=0;
                virtual void rechtecke(_liste<_vektor3<_tg> >*l,const _vektor4<_to>&col)=0;
                virtual void rechteckstreifenzyklisch(_liste<_vektor3<_tg> >*)=0;
                virtual void rechteckstreifenzyklisch(_liste<_vektor3<_tg> >*,_liste<_vektor3<_tg> >*)=0;
                virtual void rechteckstreifenzyklisch(_liste<_vektor3<_tg> >*,const _vektor4<_to>&)=0;
                virtual void rechteckstreifenzyklisch(_liste<_vektor3<_tg> >*,_liste<_vektor3<_tg> >*,const _vektor4<_to>&)=0;
                //virtual void beginndreieck()=0;
                //virtual void endedreieck()=0;
                
                //-------------------------------
                virtual void zeichnen(const _vektor3<_tg>&,const _vektor4<_to>&)=0;
                virtual void zeichnen(_tg*,_to*)=0;
                virtual void zeichnen(_tg*,_tg*,_to*)=0;
                virtual void zeichnen(const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor4<_to>&)=0;
                virtual void zeichnen(const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor4<_to>&,const _vektor4<_to>&)=0;
                virtual void zeichnen(const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor4<_to>&,const _vektor4<_to>&,const _vektor4<_to>&)=0;
                virtual void zeichnen(const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor4<_to>&,const _vektor4<_to>&,const _vektor4<_to>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&)=0;
                virtual void zeichnen(const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor4<_to>&,const _vektor4<_to>&,const _vektor4<_to>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&)=0;
                virtual void zeichnen(const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor4<_to>&,const _vektor4<_to>&,const _vektor4<_to>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&)=0;
            
                virtual void zeichnen(const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor4<_to>&,const _vektor4<_to>&,const _vektor4<_to>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&)=0;
                virtual void zeichnen(const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor4<_to>&,const _vektor4<_to>&,const _vektor4<_to>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&)=0;
                virtual void zeichnen(const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor4<_to>&,const _vektor4<_to>&,const _vektor4<_to>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&)=0;

                virtual void zeichnendebug(const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor4<_to>&,const _vektor4<_to>&,const _vektor4<_to>&)=0;
                virtual void zeichnenabgeschnitten(const _vektor3<_tg>&,const _vektor4<_to>&)=0;
                virtual void zeichnenabgeschnitten(const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor4<_to>&)=0;
                
                //virtual void zeichnen(_vertex*);
                //virtual void zeichnen(_vertex*,_vertex*);
                //virtual void zeichnen(_vertex*,_vertex*,_vertex*);
        private://nicht relevant : private daten !
                _vektor3<unsigned int> psize;
				unsigned int prate;
				bool pfullscreen;
                char porigin;
                bool pnormal;
                _vektor3<_tg> plowest;
                _vektor3<_tg> phighest;
                bool pactivity;
                unsigned int pkontext;//zB HDC
                _listebasis<_bildhardware> plistebildhardware;
                _listebasis<_zeichensatz> plistezeichensatz;
                bool pfensterkontrolle;
        public:
                unsigned int schattenbild;                
};
unsigned int _grafik::groessex() const{
                                                                return(psize[0]);
};
unsigned int _grafik::groessey() const{
                                                                return(psize[1]);
};
unsigned int _grafik::breite() const{
                                                                return(psize[0]);
};
unsigned int _grafik::hoehe() const{
                                                                return(psize[1]);
};
unsigned int _grafik::tiefe() const{
                                                                return(psize[2]);
};
unsigned int _grafik::rate() const{
                                                                return(prate);
};
bool _grafik::vollbildmodus() const{
																return(pfullscreen);
};
void _grafik::transformieren(_vektor3<_tg>&x) const{
                                                                x.mul(0,+(groessex()/2));
                                                                x.mul(1,+(groessey()/2));
                                                                x.add(0,+(groessex()/2));
                                                                x.add(1,+(groessey()/2));
                                                                if(upperleftis()) {
                                                                 x.setzenkomponente(1,groessey()-x[1]);
                                                                };
}; 
//******************************************************************************************************************************************************************************************************
//                                                              R E N D E R C O N T E X T 
//******************************************************************************************************************************************************************************************************
class _renderkontext{
};
//*****************************************************************************************************************************************************************************************************+
//                                                              Z E I C H E N 
//*****************************************************************************************************************************************************************************************************+
class _zeichen:public _listebasis<_zeichenkernel>{
        public:
                _zeichen(_zeichensatz*zs,_bild<_tb>*src,unsigned int id,unsigned short x,unsigned short y,unsigned short w,unsigned short h,_tg dx,_tg drawoffsetx,_tg drawoffsety);
                virtual ~_zeichen();
                unsigned int identifikation()const;
                _bild<_tb>*bild();
                _tg breite()const;
                _tg hoehe()const;
                _tg versatzx()const;
                _tg versatzy()const;
                _tg deltax()const;
                _tg kernel(unsigned int previd)const;
        private:
                _zeichensatz*pzeichensatz;
                _bild<_tb>*pbild;
                
                unsigned int pid;
                
                unsigned short psourcex;
                unsigned short psourcey;
                unsigned short psourcew;
                unsigned short psourceh;
                
                _tg pdrawoffsetx;
                _tg pdrawoffsety;
                _tg pdeltax;
                
                char ptexture;
                char pchannel;
              
                
};
//*****************************************************************************************************************************************************************************************************+
//                                                              Z E I C H E N K E R N E L 
//*****************************************************************************************************************************************************************************************************+
class _zeichenkernel:public _listenknotenbasis<_zeichenkernel>{
        public:
                _zeichenkernel(_zeichen*z,unsigned int previd,_tg dx);    
                virtual ~_zeichenkernel();
                unsigned int vorheriges()const;
                _tg deltax()const;
        private:
                _zeichen*pzeichen;
                unsigned int pprevid;
                _tg pdx;                
};
//*****************************************************************************************************************************************************************************************************+
//                                                              Z E I C H E N S A T Z K E R N E L 
//*****************************************************************************************************************************************************************************************************+
class _zeichensatzkernel:public _listenknotenbasis<_zeichensatzkernel>{
        public:
                _zeichensatzkernel(_zeichensatz*zs,unsigned int i0,unsigned int i1,signed short dx);
                virtual ~_zeichensatzkernel();
                unsigned int erstes()const;
                unsigned int zweites()const;
                _tg deltax()const;
        private:
                _zeichensatz*pzeichensatz;
                unsigned int pi0;
                unsigned int pi1;
                signed short pdx;
                
};
//*****************************************************************************************************************************************************************************************************+
//                                                              Z E I C H E N S A T Z 
//*****************************************************************************************************************************************************************************************************+

class _zeichensatz:public _listenknotenbasis<_zeichensatz>{
        friend class _zeichenkernel;
        public:
                _zeichensatz(_grafik*g);
                virtual ~_zeichensatz();
                virtual void text(const _zeichenkette<char>&,_tg x,_tg y,const _vektor4<_to>&color)=0;
                virtual void text(const _zeichenkette<wchar_t>&,_tg x,_tg y,const _vektor4<_to>&color)=0;
                
                virtual _tg breite(const _zeichenkette<_tt>&)=0;
                virtual _tg hoehe(const _zeichenkette<_tt>&)=0;
                _listebasis<_zeichensatzkernel>*kernelliste();
                virtual _zeichen*zeichen(unsigned int)=0;
                void skalierung(_tg);
                inline _tg skalierung()const;
                

				//old shit
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
                unsigned int identifikation() const;
        protected:
                void identifikation(const unsigned int);                
        private:
                unsigned int pid;
                _grafik*pg;
                _listebasis<_zeichensatzkernel> pkernelliste;
                _tg pskalierung;
};
_tg _zeichensatz::skalierung()const{
                                                                return(pskalierung);
};
//*****************************************************************************************************************************************************************************************************+
//                                                              Z E I C H E N S A T Z D I R E C T X 
//*****************************************************************************************************************************************************************************************************+
class _zeichensatzbild:public _zeichensatz{
       
        public:
                _zeichensatzbild(_grafik*,const _zeichenkette<char> file);
                ~_zeichensatzbild();

                virtual void text(const _zeichenkette<char>&,_tg x,_tg y,const _vektor4<_to>&color);
                virtual void text(const _zeichenkette<wchar_t>&,_tg x,_tg y,const _vektor4<_to>&color);
                virtual _tg breite(const _zeichenkette<_tt>&);
                virtual _tg hoehe(const _zeichenkette<_tt>&);
                virtual _zeichen*zeichen(unsigned int);
                _bild<_tb>*bild();
                

                //void anwaehlen(HDC); old shit
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
                bool blockreadheader(FILE*f,char&blocktype,int&blocksize);
                void blockread1(FILE*f,unsigned int size);
                void blockread2(FILE*f,unsigned int size);
                void blockread3(FILE*f,unsigned int size);
                void blockread4(FILE*f,unsigned int size);
                void blockread5(FILE*f,unsigned int size);
        private:
                _grafik*pgrafik;
                _zeichenkette<char> pfile;
                _bild<_tb>*psource;
                char pheader[4];
                char pversion;
                unsigned int pzeichenanzahl;
                unsigned int pkernelanzahl;
                //block 1
                unsigned short pgroesse;
                char pstil;
                char poemname;
                unsigned short pstretchy;
                char psupersamlinglevel;
                char ppadup;
                char ppadright;
                char ppaddown;
                char ppadleft;
                char pspacingx;
                char pspacingy;
                char poutline;
                char*pfontname;
                //block 2
                unsigned short plinedistance;
                unsigned short pbase;
                unsigned short ptexwidth;
                unsigned short ptexheight;
                unsigned short ptexanzahl;
                char ppacked;
                char pchannelalpha;
                char pchannelred;
                char pchannelgreen;
                char pchannelblue;
                //block 3
                char*ptexturname;
                
                
                _zeichen*pzeichen[16384];
                
                
};
#endif
