//******************************************************************************************************************************************************************************************************
//  Projekt     : grundplatte
//  Modul       : _editionigg.hpp
//  Datum       : 17.09.2008
//******************************************************************************************************************************************************************************************************
#ifndef _editionigg_included
#define _editionigg_included
#include <stdlib.h>
#include <_global.hpp>
#include <_vektor.hpp>
#include <_struktur.hpp>
#include <_datei.hpp>
#include <_bild.hpp>
#include <_systemwin.hpp>
#include <_grafik.hpp>
#include <_akustik.hpp>
#include <_weltpolygon.hpp>

//*******************************************************************************************************************************************************************************
//										                        P R E D E K L A R A T I O N
//*******************************************************************************************************************************************************************************
bool charactervalid(unsigned char c);
void zeichnenguitext(_grafik*g,_zeichenkette<_tt>const&name,_zeichensatz*zs,_vektor3<_tg>&p,_vektor4<_to>&c);
void zeichnenguibox(_grafik*g,_vektor3<_tg>&p,_tg w,_tg h,_vektor4<_to>&c);
void zeichnenguirectangle(_grafik*g,_vektor3<_tg>&p,_tg w,_tg h,_vektor4<_to>&c);
void zeichnenguiboxinvers(_grafik*g,_vektor3<_tg>&p,_tg w,_tg h,_vektor4<_to>&c);
void zeichnenguirectangleinvers(_grafik*g,_vektor3<_tg>&p,_tg w,_tg h,_vektor4<_to>&c);
void zeichnenguifurche(_grafik*g,_tg x0,_tg y0,_tg x1,_tg y1,_vektor4<_to>&c);

class _iggclip;
class _iggcolor;
class _iggvector;
class _iggvectorentry;
class _iggvectorkondition;
class _iggsize;
class _iggposition;
class _igg;
class _iggsystem;
class _iggbutton;
class _iggcheckbox;
class _iggshiftout;
class _iggcombobox;
class _iggeditbox;
class _iggimage;
class _iggline;
class _igglistbox;
class _iggmesh; 
class _iggscrollbar;
class _iggscrollbarvertical;
class _iggtext;
class _iggtextline;
class _iggtrackbardisplaytext;
class _iggtrackbar;
class _iggwindow;
class _iggmenumanagement;
class _iggmenu;


class _benutzer;
class _benutzerverwaltung;






//*******************************************************************************************************************************************************************************
//										                        G U I C L I P
//*******************************************************************************************************************************************************************************
class _iggclip{
        public:
                _iggclip();
                _tg x0;
                _tg x1;
                _tg y0;
                _tg y1;
};
//*******************************************************************************************************************************************************************************
//										                        G U I C O L O R
//*******************************************************************************************************************************************************************************
class _iggcolor{
        public:
                _iggcolor();
            	_vektor4<_to> std;
	            _vektor4<_to> mark;
	            _vektor4<_to> active;
};
//*******************************************************************************************************************************************************************************
//										                        I G G V E C T O R E N T R Y
//*******************************************************************************************************************************************************************************
class _iggvectorentry:public _vektor3<_tg>,public _listenknotenbasis<_iggvectorentry>{
        public:
	            _iggvectorentry(_iggvector*gv,const _vektor3<_tg>&o,bool dyn);
	            _iggvectorentry(_iggvectorkondition*k,_iggvector*gv,const _vektor3<_tg>&o,bool dyn);
	            virtual ~_iggvectorentry();
        public:	            
	            _iggvector*iggvector;		
	            bool dynamic;
};
//*******************************************************************************************************************************************************************************
//										                        I G G V E C T O R
//*******************************************************************************************************************************************************************************
class _iggvector:public _listebasis<_iggvectorentry>{
        public:
                _iggvector(_igg*g,const _tg x,const _tg y,const _tg z,bool dynamic=false);
                virtual ~_iggvector();
                void setzen(const _tg x,const _tg y,const _tg z,bool dynamic=false);
                _listebasis<_iggvectorkondition>*konditionsliste();
                void x(const _tg x);
                void y(const _tg y);
                void z(const _tg z);
                void setzen(unsigned int vectorindex,const _tg x,const _tg y,const _tg z,bool dynamic=false);
                void dynamik(bool d,int i=0);
                void addieren(const _tg x,const _tg y,const _tg z,bool dynamic=false);
                void addieren(const _vektor3<_tg>&v,bool dynamic=false);
                _vektor3<_tg> lesen()const;
                _tg x()const;
                _tg y(int index=-1)const;
                _tg z()const;
                _iggvectorkondition* kondition(_tg xmin,_tg xmax,_tg ymin,_tg ymax,_tg x,_tg y,_tg z,bool dynamic=false);
        public:
                _igg*igg;
                _iggsystem*iggsystem;
                _listebasis<_iggvectorkondition> pkonditionlist;
};        



//******************************************************************************************************************
//										                    I G G V E C T O R K O N D I T I O N
//******************************************************************************************************************
class _iggvectorkondition:public _listenknotenbasis<_iggvectorkondition>,public _listebasis<_iggvectorentry>{
        public:
        using _listebasis<_iggvectorentry>::naechstes;
        using _listebasis<_iggvectorentry>::vorheriges;
        using _listenknotenbasis<_iggvectorkondition>::naechstes;
        using _listenknotenbasis<_iggvectorkondition>::vorheriges;
        public:
                _iggvectorkondition(_iggvector*gv,_tg xmin,_tg xmax,_tg ymin,_tg ymax);
                virtual ~_iggvectorkondition();
                _iggvectorentry*addieren(_tg x,_tg y,_tg z,bool dynamic=false);
        public:
	            _iggvector*iggvector;
	            _tg bereichxmin;
	            _tg bereichxmax;
	            _tg bereichymin;
	            _tg bereichymax;
};	            


//*******************************************************************************************************************************************************************************
//                      										G U I S I Z E 
//*******************************************************************************************************************************************************************************
class _iggsize:public _iggvector{
        public:
                _iggsize(_igg*g,const _tg x,const _tg y,const _tg z,bool dynamic=false);
                virtual ~_iggsize();
};
//*******************************************************************************************************************************************************************************
//						                        				G U I P O S I T I O N
//*******************************************************************************************************************************************************************************
class _iggposition:public _iggvector{
        public:
                _iggposition(_igg*g,const _tg x,const _tg y,const _tg z,bool d);
                virtual ~_iggposition();
};
//*******************************************************************************************************************************************************************************
//                      										G U I
//*******************************************************************************************************************************************************************************
class _igg:public _listelistenknotenbasis<_igg>{
        public:
        using _listebasis<_igg>::naechstes;
        using _listebasis<_igg>::vorheriges;
        public:
                _igg(_igg*pg,_tg px,_tg py,_tg pz,_tg pw,_tg ph,int pin);
                virtual ~_igg();
                void loeschenhilfe();
                void einhaengen(_igg*);
                void aushaengen();
                _iggsystem*iggsystem();
                virtual void dynamisch(_tg wx,_tg wy);
                virtual void dynamischort(_tg wx,_tg wy);
                virtual void dynamischgroesse(_tg wx,_tg wy);           
                virtual bool vergleichen(_igg*)const;
                void loeschenkind();
                _tg kindbreite()const;
                _tg kindhoehe()const;
                _tg breite()const;
                _tg hoehe()const;
                _tg tiefe()const;
				void zentriert();
				void rechtsbuendig();
				void linksbuendig();
                virtual void setzenstatus()=0;
                virtual bool inner(_maus<_tg>*mau);
                virtual bool mouseovergui(_maus<_tg>*mau);     
                _iggtext*inserttext(const _zeichenkette<_tt>&t,_tg x,_tg y,_tg z,_to r,_to g,_to b,_zeichensatz*f,int pp=0,_tg mob=2);
                _iggimage*insertimage(_bild<_tb>*t,_tg x,_tg y,_tg w,_tg h,_to r,_to g,_to b,int pp);
                _iggmesh*insertmesh(_netz*m,_tg x,_tg y,_tg w,_tg h,_to r,_to g,_to b,int pp);
                _iggline*insertline(_tg x0,_tg y0,_tg x1,_tg y1,_to r,_to g,_to b);
                void textsplit(const _zeichenkette<_tt>&t,_tg wx,_zeichensatz*f,_liste<_zeichenkette<_tt> >*l);     
                _iggwindow*createhilfe(const _zeichenkette<_tt>&text,_zeichensatz*fh,_tg dt,_tg ox,_tg oy,int staticbreite=-1,bool noclear=false);
                _iggwindow*addhilfe(const _zeichenkette<_tt>&text0,_zeichensatz*fh,int staticbreite=-1);
                _bild<_tb>*bestbreitematch();
                _bild<_tb>*bestshadowmatch();     
                virtual void zeichnen(_grafik*gra,_kamera<_tg>*cam)=0;
                virtual void zeichnenkind(_grafik*gra,_kamera<_tg>*cam);
                virtual void zeichnenschatten(_grafik*gra,_kamera<_tg>*cam);
                virtual void cliprecursive(_iggclip*cr);
                virtual bool clip(_grafik*gra);
	            virtual void animieren(_maus<_tg>*mau,_tastatur*tas)=0;
                virtual void animierenkind(_maus<_tg>*mau,_tastatur*tas);
	            virtual void animierenhilfe(_maus<_tg>*mau);
            	virtual void animierenhilfefadeout(_maus<_tg>*mau);
            	virtual void hilfefadeout();
	            virtual void animierenfade();
	            virtual void animierenfadekind();
	            virtual void clearbackground();
	            virtual void setshadow(_tg pdx,_tg pdy,_to po=0.3);
	            virtual void deactivate();
	            virtual void activate();
	            virtual bool focus();
	            virtual void setfocus();
	            virtual void updatefadeopacity();			
	            virtual void updatefadeopacityrecursive(_to o);
	            virtual void fadeout(bool tosuperinact=false,bool tosuperinvis=false,bool toclear=false);
	            virtual void fadein();		
	            virtual void fadetarget(_to ft);
	            virtual void fadeoff();
	            virtual bool fading();
	            virtual void activity(bool v);
	            virtual void superinactivity(bool v);
	            virtual void visibility(bool v);
	            virtual void superinvisibility(bool v);
	            virtual void fadeopacity(_to o);
	            virtual void marking(int m);
	            virtual void saveactivityrecursive(_liste<_igg>*l,_igg*exgui=0);
	            virtual unsigned int count();
	            
        public:
                _igg*parent;
                _listenknoten<_igg>*linkzeichnen;
                bool active;
                bool superinactive;
                bool visible;
                bool superinvisible;
                bool clipkind;
                bool clipkindhierarchical;
                bool selectable;
                int marked;
                int index;
                _vektor3<_tg> positiontransformed;
                _iggposition position;
				_vektor3<_tg> transformation;
                _iggsize size;
                _vektor4<_to> color;
                _vektor4<_to> colortransformed;
                _vektor4<_to> colorhilfe;
                _to pfadeopacity;
                bool pfadein;
                bool pfadeout;
                bool pfadeouttosuperinactive;
                bool pfadeouttosuperinvisible;
                bool pfadeouttoclear;
                _to pfadetarget;
                _zeichensatz*font;
                bool shadow;
                _to shadowopacity;
                _vektor3<_tg> shadowdirection;
                _vektor3<_tg> shadowdirectiontransformed;
                _liste<_bild<_tb> > background[3];
                _liste<_bild<_tb> > shadowimage[3];
                _tg shadowimageboardening;
                _igg*hilfeparent;
                _igg*hilfe;
                _tg hilfepositionx;
                _tg hilfepositiony;
                _tg hilfedelaytime;
                _tg hilfetimefalse;
                _zeichensatz*hilfefont;
                _tg fadetimeold;
                _iggclip cliprect;
};               
//*******************************************************************************************************************************************************************************
//                                                              G U I S Y S T E M 
//*******************************************************************************************************************************************************************************
class _iggsystem:public _igg{
        public:
                _iggsystem(_guifenster*,_tg w,_tg h);
                virtual ~_iggsystem();
				void clearhilfeglobal(_igg*);
                void zeichnen(_grafik*gra,_kamera<_tg>*cam);
                void zeichnenbackground(_grafik*gra,_kamera<_tg>*cam);
                void zeichnencursor(_maus<_tg>*mau,_grafik*gra,_kamera<_tg>*cam);
                void addtoclear(_igg*g);
                void processtoclear();
                void setzenstatus();
                void nullstates(_maus<_tg>*mau,_tastatur*tas);
                void pushstates();
                bool comparestates();
                void animieren(_maus<_tg>*mau,_tastatur*tas);
                void animierenfade();
                void animierenhilfefadeoutglobalrecursive(_igg*gui);
                void animierenhilfefadeoutglobal();
                bool mouseovergui(_maus<_tg>*mau);
                void saveactivitylist(_igg*exgui=0);
                void setactivitylist(bool a);
                void restoreactivitylist();
                unsigned int count();
                _zeichenkette<_tt> clipboardtext();
        public:	
				_guifenster*guifenster;
                _listesortierung<_igg> drawlist;
                _liste<_igg> toclear;
                //uhr
                _win::_zeit*clock;
                //optics
                _iggcolor colors;//:_iggcolor=Null//system color standards, old stuff, better maken
                _bild<_tb>*cursorimage;//mouse cursor image
                _tg fadespeed;//#=2
                //sounds
                _ton*dip[4];
                //focus
                _igg*focus;
                //event states
                _iggbutton*button;
                _iggtrackbar*trackbar;
                _iggscrollbarvertical*scrollbarvertical;
                _igglistbox*listbox;
                _iggcheckbox*checkbox;
                _iggcombobox*combobox;
                _iggeditbox*editbox;
                _iggtext*text;
                _iggimage*image;
                _iggmesh*mesh;
                _iggwindow*window;
                //event states push data
                _iggbutton*buttonpush;
                _iggtrackbar*trackbarpush;
                _iggscrollbarvertical*scrollbarverticalpush;
                _igglistbox*listboxpush;
                _iggcheckbox*checkboxpush;
                _iggcombobox*comboboxpush;
                _iggeditbox*editboxpush;
                _iggtext*textpush;
                _iggimage*imagepush;
                _iggmesh*meshpush;
                _iggwindow*windowpush;
                //event types
                bool doubleclickleft;//:=false
                //input states
                //unsigned char key//=0;
                int mouseposx;
                int mouseposy;
                int mouseposz;
                bool mousebutton[4];
                //track states
                _iggscrollbar*scrollbartrack;
                _iggtrackbar*trackbartrack;
                //activity restore 
                _liste<_igg> psaveactivitylist;
};	
//*******************************************************************************************************************************************************************************
//                                                              B U T T O N
//*******************************************************************************************************************************************************************************
class _iggbutton:public _igg{
        public:
                _iggbutton(_igg*pg,_tg px,_tg py,_tg pw,_tg ph,const _zeichenkette<_tt>&pn,_zeichensatz*zs,int pin=0);
                virtual ~_iggbutton();
                void setimage(_bild<_tb>*b,_tg dx,_tg dy);
                void settextcolor(_vektor4<_to>&t);
                _zeichensatz*bestfontbreite();
                virtual void zeichnenschatten(_grafik*gra,_kamera<_tg>*cam);
                virtual void zeichnen(_grafik*gra,_kamera<_tg>*cam);
                void animierenscale();		
                virtual void animieren(_maus<_tg>*mau,_tastatur*tas);
                void marking(int m);
                void demark();
                void push();
                virtual void setzenstatus();
        public:        
                _vektor4<_to> textcolor;
                _vektor4<_to> textcolororiginal;
                _zeichenkette<_tt> text;
                _bild<_tb>*image;//Null//this is the image, which the button shows in front
                _tg imagedx;
                _tg imagedy;
                bool centric;//=false
                bool centrictext;//=false
                _vektor4<_to> textcolormark;
                _vektor4<_to> textcoloractive;
                _tg textshadow;//#=1
                //dynamische zustands skalierung
                bool dynamicactivityscale;//=false
                _tg dynamicactivityscalevalueactual;//#=0		//actual, displayed and performed rotation value
                _tg dynamicactivityscalevalue;//#=0				//the value that should be matched
                _tg dynamicactivityscalevector;//#=0
                _tg dynamicactivityscalevelocity;//#=6
                _tg dynamicactivityscalefriction;//#=0.8
                _tg dynamicactivityscaletime;//#=0
	            //dynaqmische fonts
	            _liste<_zeichensatz> fontliste;
	            bool benutzenfontliste;
};

	
//*******************************************************************************************************************************************************************************
//                                                              C H E C K B O X
//*******************************************************************************************************************************************************************************
class _iggcheckbox:public _igg{
        public:
                _iggcheckbox(_igg*pg,_tg px,_tg py,_tg pw,_tg ph,int pin=-1);
                virtual ~_iggcheckbox();
                void setcheckimage(_bild<_tb>*t);
                virtual void zeichnen(_grafik*gra,_kamera<_tg>*cam);
                virtual void animieren(_maus<_tg>*mau,_tastatur*tas);
                virtual void setzenstatus();
        public:
	            _bild<_tb>* checkimage;
	            _tg checkimagebreite;//#=10;								
	            _tg checkimagehoehe;//#=10;									
	            bool checked;//=false;		
	            _vektor3<_tg> checkposition;
	            _iggmesh*crosslinkmesh;
	            _iggimage*crosslinkimage;
};
//*******************************************************************************************************************************************************************************
//                                                              G U I S H I F T O U T
//*******************************************************************************************************************************************************************************
class _iggshiftout:public _igg{
        public:
                _iggshiftout(_igg*pg,_tg px,_tg py,_tg pw,_tg ph,_zeichenkette<_tt>&pbuttontext,int pin,_to pr,_to pgr,_to pb,_zeichensatz*f);
                virtual ~_iggshiftout();
                void animierenshift();
                void shiftout();
                void shiftin();
                void setshiftout(bool s);
                virtual bool clip(_grafik*gra);
                virtual void zeichnen(_grafik*gra,_kamera<_tg>*cam);
                virtual void animieren(_maus<_tg>*mau,_tastatur*tas);
                virtual void setzenstatus();
        public:
                _tg orghoehe;//#=0;
	            _iggbutton* button;
	            _iggwindow*window;
	            _igg*positionmatch;
	            bool pshiftin;//=false;
	            bool pshiftout;//=false;
	            bool pshifting;//=false;
	            _kurvehermite3<_tg> pshiftcurve;
	            _tg pshiftt;
	            _tg pshifttime;
	            _tg pshiftspeed;//#=350;
	            _tg windowhoeheminimal;//#=5;
	            _win::_zeit*clock;
};	
//*******************************************************************************************************************************************************************************
//                                                              G U I C O M B O B O X
//*******************************************************************************************************************************************************************************
class _iggcombobox:public _igg{
        public:
                _iggcombobox(_igg*pg,_tg px,_tg py,_tg pw,_tg ph,_tg pbuttonbreite,int pin,_to pr,_to pgr,_to pb,   _tg lbx,_tg lby,_tg lbw,_tg lbh,_tg lbbw, int lbi, _zeichensatz*f);
                virtual ~_iggcombobox();
                virtual void zeichnen(_grafik*gra,_kamera<_tg>*cam);
                virtual void animieren(_maus<_tg>*mau,_tastatur*tas);
                virtual void setzenstatus();
                virtual void dynamisch(_tg wx,_tg wy);
        public:
	            _igglistbox*listbox;
	            _iggbutton*button;
	            _iggtext*text;
	            bool centrictext;
};
//*******************************************************************************************************************************************************************************
//                                                              E D I T B O X
//*******************************************************************************************************************************************************************************
class _iggeditbox:public _igg{
        public:
                _iggeditbox(_igg*pg,_tg px,_tg py,_tg pw,_tg ph,const _zeichenkette<_tt>&t,_zeichensatz*f,_to pr,_to pgr,_to pb);
                virtual ~_iggeditbox();
                void set(_zeichenkette<_tt>&t);
				_zeichenkette<_tt> get()const;
                void setcursorimage(_bild<_tb>*t,_tg w,_tg h);
                virtual void zeichnen(_grafik*gra,_kamera<_tg>*cam);
                virtual void animieren(_maus<_tg>*mau,_tastatur*tas);
                virtual void setzenstatus();
        public:
	            _zeichenkette<_tt> text;
	            int animw;
	            int animc;
	            int animp;
	            _tg animtime;
	            _bild<_tb>*cursorimage;
	            _tg cursorbreite;
	            _tg cursorhoehe;
	            _tg cursoroffsety;
	            _tg cursorsmooth;
	            _to cursoropacity;
	            _vektor4<_to> textcolor;
				_tg textshadowz;
	             int maximumcharacters;
	            bool drawframe;
        private:	            
	            bool keyboarddown;
				char feldalt[1024];
				bool feldaltinitialisiert;
};	            
//*******************************************************************************************************************************************************************************
//                                                              G U I I M A G E
//*******************************************************************************************************************************************************************************
class _iggimage:public _igg{
        public:
                _iggimage(_igg*pg,_tg px,_tg py,_tg pw,_tg ph,_bild<_tb>*img,_to pr,_to pgr,_to pb);
                virtual ~_iggimage();
                virtual void zeichnen(_grafik*gra,_kamera<_tg>*cam);
                virtual void animieren(_maus<_tg>*mau,_tastatur*tas);
                virtual void setzenstatus();
        public:
	            _bild<_tb>*image;
	            bool blendmasked;
	            _iggtext*crosslinktext;
	            _iggcheckbox*crosslinkcheckbox;
};	
//*******************************************************************************************************************************************************************************
//                                                              G U I L I N E
//*******************************************************************************************************************************************************************************
class _iggline:public _igg{
        public:
                _iggline(_igg*pg,_tg px0,_tg py0,_tg px1,_tg py1,_to pr,_to pgr,_to pb);
                virtual ~_iggline();
                virtual void zeichnenschatten(_grafik*gra,_kamera<_tg>*cam);
                virtual void zeichnen(_grafik*gra,_kamera<_tg>*cam);
                virtual void animieren(_maus<_tg>*mau,_tastatur*tas);
                virtual void setzenstatus();
        public:
};
//*******************************************************************************************************************************************************************************
//                                                              L I S T B O X
//*******************************************************************************************************************************************************************************
class _igglistbox:public _igg{
        public:
                _igglistbox(_igg*pg,_tg px,_tg py,_tg pw,_tg ph,_tg pbw,_to pr,_to pgr,_to pb);
                virtual ~_igglistbox();
                void setpositiony(_tg y);				
                virtual void dynamisch(_tg x,_tg wy);
                void setsizey(_tg y);
                void updatescrollbar();				
                _tg contentbreite();
                _tg contenthoehe();
                bool contentbreitetoolarge();
                bool contenthoehetoolarge();
                virtual void zeichnen(_grafik*gra,_kamera<_tg>*cam);
                void cliprecursive(_iggclip*cr);
                virtual bool clip(_grafik*gra);
                //void deinsert();
                void selectbytext(const _zeichenkette<_tt>&t);//searches for a _iggtext object, if its first textline is t , then select this gui object
                _zeichenkette<_tt> selectiontext();// return the string of selected gui object, if this is an _iggtext object
                void scrolltoselection();
                bool mouseoverviewport(_maus<_tg>*mau);
                void animierenkind(_maus<_tg>*mau,_tastatur*tas);
                virtual void animieren(_maus<_tg>*mau,_tastatur*tas);
                void checkboxes(bool c);
                bool enthaeltcheckbox(_iggcheckbox*c)const;
                virtual void setzenstatus();
                
        public:
	            _iggscrollbarvertical*scrollbarvertical;
	            _tg borderbreite;//#=4;//breite of the listbox border elements
	            _tg scrollbarverticalbreite;//#=20;
	            _tg scrollstepwheel;//#=5;
	            _tg scrollfriction;//#=0.8;
	            bool drawframe;//=true;
            	
	            _bild<_tb>*frameimage;
	            _bild<_tb>*frameimagevertical;
	            _bild<_tb>*frameimagehorizontal;
	            bool innershadow;//=true;
	            _to backgroundopacity;//#=0.4;
	            int doubleclicktime;//=500;
            	
	            //private
	            _tg pcontenthoehe;//#=0;
	            _tg pcontentbreite;
	            _tg mousezold;//#=0;
	            _tg mousezvector;//#=0;
	            bool moverviewport;//=0;
	            _tg lasthoehe;//#=0;
	            int lastclick;//=0;
	            bool statuskeydown;//=false;
	            bool statuskeyup;//=false;

	            _igg*selection;//selected gui element of the list
	            _vektor4<_to> selectioncolor;//:=Null;
	            bool selectionrect;//=false;
	            _bild<_tb>*selectionrectbild;
	            _to selectionrectopacity;//#=0;
	            _vektor4<_to> selectionrectcolor;//:=Null;
	            _tg selectionrectx;//#=0;
	            _tg selectionrecty;//#=0;
	            _tg selectionrectw;//#=0;
	            _tg selectionrecth;//#=0;

	            //mouseoverrectangle daten
	            bool moverrect;//=false;
	            _bild<_tb>*moverrectbild;
	            _tg moverrecttimeold;//#=0;
	            _to moverrectopacity;//#=0;
	            _vektor4<_to> moverrectcolor;//:=Null;
	            _tg moverrectx;//#=0;
	            _tg moverrecty;//#=0;
	            _tg moverrectw;//#=0;
	            _tg moverrecth;//#=0;
	            _tg moverrecttargetx;//#=0;
	            _tg moverrecttargety;//#=0;
	            _tg moverrecttargetw;//#=0;
	            _tg moverrecttargeth;//#=0;
};	
//*******************************************************************************************************************************************************************************
//                                                              G U I M E S H
//*******************************************************************************************************************************************************************************
class _iggmesh:public _igg{
        public:
                _iggmesh(_igg*pg,_tg px,_tg py,_tg pw,_tg ph,_netz*m,_to pr,_to pgr,_to pb, int pp);
                virtual ~_iggmesh();
                virtual void zeichnen(_grafik*gra,_kamera<_tg>*cam);
                virtual void updatemesh();
                virtual void animieren(_maus<_tg>*mau,_tastatur*tas);
                virtual void setzenstatus();
        public:                    
	            _netz*mesh;
	            _netz*meshtransformed;
	            _iggcheckbox*crosslinkcheckbox;
	            _zeichenkette<_tt> crosslinkname;
};

//*******************************************************************************************************************************************************************************
//                                                              S C R O L L B A R
//*******************************************************************************************************************************************************************************
class _iggscrollbar:public _igg{
        public:
                _iggscrollbar(_igg*pg,_tg px,_tg py,_tg pz,_tg pw,_tg ph,int pin);
                virtual ~_iggscrollbar();
};
//*******************************************************************************************************************************************************************************
//                                                              S C R O L L B A R V E R T I C A L
//*******************************************************************************************************************************************************************************
class _iggscrollbarvertical:public _iggscrollbar{
        public:
                _iggscrollbarvertical(_igg*pg,_tg px,_tg py,_tg pw,_tg ph,_tg pbuttonw,_tg pbuttonh,_to pr,_to pgr,_to pb,_tg s,int pp);
                virtual ~_iggscrollbarvertical();
                virtual void zeichnen(_grafik*gra,_kamera<_tg>*cam);
                virtual void animieren(_maus<_tg>*mau,_tastatur*tas);
                virtual void setzenstatus();
        public:
	            _tg value;     //normalized scrollparameter for y
	            _tg scrollstepbutton;
	            _tg scrollstepwheel;
	            _tg scrollstepbar;
	            _tg scrollfriction;
	            bool scrollbuttonsmooth;
	            _tg controllength;
	            _tg borderhoehe;//breite of the border up/down 
	            _tg hoeheratio;//% of h-2*borderhoehe
	            bool stretchsliderimagebyratio;
	            _bild<_tb>*sliderimage;//0=middle,1=up,2=down
	            _tg sliderimagebreite;
	            _tg sliderimagehoehe;
	            _bild<_tb>*barimage;
	            _tg barimagebreite;
	            bool barsmooth;
	            _iggbutton*buttonup;
	            _iggbutton*buttondown;
	    private:
	            _tg mousezold;
	            _tg mousezvector;
	            bool mover;
};	
//*******************************************************************************************************************************************************************************
//                                                              G U I T E X T
//*******************************************************************************************************************************************************************************
class _iggtext :public _igg{
        public:
                _iggtext(_igg*pg,_tg px,_tg py,_tg sz,_zeichenkette<_tt> t,_to pr,_to pgr,_to pb,_zeichensatz*f,_tg mob=0);
                virtual ~_iggtext();        
                void setzen(const _zeichenkette<_tt>&t);
                _zeichenkette<_tt> lesen()const;
				void zeichensatz(_zeichensatz*zs);
               // void centerx(_tg x);
                virtual void zeichnen(_grafik*gra,_kamera<_tg>*cam);
                virtual void animieren(_maus<_tg>*mau,_tastatur*tas);
                virtual void setzenstatus();
                //void zentrieren(const bool b=true);
                //void rechtsbuendig(const bool b=true);
        public:
	            //_liste<_iggtextline> lines;
	            _tg textshadow;//#=1;
	            _tg border;//#=0;
	            _iggimage*crosslinkimage;
	            _zeichenkette<_tt> ht;
				_zeichenkette<_tt> text;
};	
//*******************************************************************************************************************************************************************************
//                                                              G U I T E X T L I N E
//*******************************************************************************************************************************************************************************
/*
class _iggtextline{
        public:
                _iggtextline(_zeichenkette<_tt>&t,_iggtext*gt,_tg px,_tg py,_tg pz,_to pr,_to pg,_to pb);
                virtual ~_iggtextline();
                virtual void zeichnen(_grafik*gra,_kamera<_tg>*cam);
                virtual void animieren();
        public:
	            _vektor3<_tg> hp;
	            _iggtext*guitext;
	            _zeichenkette<_tt> text;
	            _vektor3<_tg> position;
	            _vektor4<_to> color;
	};*/
//*******************************************************************************************************************************************************************************
//										                        T R A C K B A R D I S P L A Y T E X T
//*******************************************************************************************************************************************************************************
class _iggtrackbardisplaytext{
        public:
                _iggtrackbardisplaytext(_tg min,_tg max,const _zeichenkette<_tt>&t,_zeichensatz*f);
        public:
	            _tg vmin;
	            _tg vmax;
	            _zeichensatz*font;
	            _zeichenkette<_tt> text;
};
//*******************************************************************************************************************************************************************************
//                                                              T R A C K B A R
//*******************************************************************************************************************************************************************************
class _iggtrackbar:public _igg{
        public:
                _iggtrackbar(_igg*pg,_tg px,_tg py,_tg pw,_tg ph,_zeichensatz*f,_to pr,_to pgr,_to pb,_tg w,_tg mi,_tg ma);
                virtual ~_iggtrackbar();
                void text(_zeichenkette<_tt>&t,_zeichensatz*f,_tg mi,_tg ma);
                _zeichenkette<_tt> text(_zeichensatz*&zs);
                void minimum(_tg m);
                void maximum(_tg m);
                void setzen(_tg v);
                _tg lesen();
                virtual void zeichnen(_grafik*gra,_kamera<_tg>*cam);
                virtual void animieren(_maus<_tg>*mau,_tastatur*tas);
                virtual void setzenstatus();
                
        public:
	            _tg pvalue;
	            _tg rmin;
	            _tg rmax;
	            _bild<_tb>*sliderimage;
	            _tg sliderimagebreite;
	            _tg sliderimagehoehe;
	            int sliderimageindex;
	            _tg displaymultiplier;
	            _liste<_iggtrackbardisplaytext> displaytextlist;
	            _zeichenkette<_tt> displayaddition;
	            bool displayrounding;
};	            
//*******************************************************************************************************************************************************************************
//                                                              W I N D O W 
//*******************************************************************************************************************************************************************************
class _iggwindow:public _igg{
        public:
                _iggwindow(_igg*pg,_tg px,_tg py,_tg pw,_tg ph,_to pr,_to pgr,_to pb);
                virtual ~_iggwindow();
                virtual void zeichnen(_grafik*gra,_kamera<_tg>*cam);
                virtual void animieren(_maus<_tg>*mau,_tastatur*tas);
                virtual void setzenstatus();
        public:
};
//*******************************************************************************************************************************************************************************
//                                                              M E N U M A N A G E M E N T 
//*******************************************************************************************************************************************************************************
class _iggmenumanagement:public _listebasis<_iggmenu>{
        public:    
                _iggmenumanagement();
                virtual ~_iggmenumanagement();
                _iggmenu*createmenu();
                _iggmenu*menu(int index);
                void add(int menuindex,_igg*g);
                void show(_iggmenu*m,bool fade=true);
                void opazitaet(const _tg);
                _tg opazitaet()const;
        private:
                _tg popacity;                
};
//*******************************************************************************************************************************************************************************
//                                                              M E N U
//*******************************************************************************************************************************************************************************
class _iggmenu:public _listenknotenbasis<_iggmenu>,public _liste<_igg>{
        public:
        using _listenknotenbasis<_iggmenu>::naechstes;
        using _liste<_igg>::naechstes;
        public:
                _iggmenu(_iggmenumanagement*mm);
                virtual ~_iggmenu();
                void add(_igg*g);
                void visibility(bool v);
                void activity(bool a);
                void fadeopacity(_to o);
                void fadeout();
                void fadein();
                void fadeoff();
                void fadetarget(_to ft);
                bool active();
                bool visible();
                bool fading();               
};	
//*******************************************************************************************************************************************************************************
//                                                              B E N U T Z E R
//*******************************************************************************************************************************************************************************
class _benutzer:public _listenknotenbasis<_benutzer>{
        public:
                _benutzer(_benutzerverwaltung*,const _zeichenkette<_tt>&name,unsigned int bildindex,_tg punkte);
                virtual ~_benutzer();
                bool vergleichen(_benutzer*b);
                void punkte(const _tg);
                _tg punkte()const;
                void bildindex(unsigned int);
                unsigned int bildindex()const;
                _bild<_tb>*bild();
                const _zeichenkette<_tt>&name()const;
                void name(const _zeichenkette<_tt>&n);
                void laden(_datei*);
                void speichern(_datei*);
                
        private:
                _benutzerverwaltung*pbenutzerverwaltung;
                _zeichenkette<_tt> pname;
                unsigned int pbildindex;
                _tg ppunkte;
};


//*******************************************************************************************************************************************************************************
//                                                              B E N U T Z E R V E R W A L T U N G 
//*******************************************************************************************************************************************************************************
class _benutzerverwaltung:public _listebasis<_benutzer>{
        public:
                _benutzerverwaltung(const _zeichenkette<char>&datei,const _zeichenkette<_tt>&beschreibung);
                virtual ~_benutzerverwaltung();
                _benutzer*aktuell();
                void aktuell(_benutzer*);
                void aktuell(unsigned int);
                _bild<_tb>*ladenbild(_zeichenkette<char> s,bool clamp=true);
                _bild<_tb>*bild(unsigned int i);
                unsigned int bildindex(const _bild<_tb>*);
                _liste<_bild<_tb> >*bildliste();
                void loeschenbenutzer(const _zeichenkette<_tt>&t);
                _benutzer*erzeugenbenutzer(const _zeichenkette<_tt>&t,unsigned int i,_tg s=0);
                _benutzer*erzeugenbenutzer(const _zeichenkette<_tt>&t,_bild<_tb>*,_tg s=0);
                _benutzer*existiert(const _zeichenkette<_tt>&t);
                _benutzer*benutzer(const _zeichenkette<_tt>&t);
                void setzenbenutzer(const _zeichenkette<_tt>&t);
                void speichern();
                void laden();
        private:
                _zeichenkette<char> pdatei;
            	_zeichenkette<_tt> pbeschreibung;
	            _benutzer*paktuell;
	            _liste<_bild<_tb> > pbildliste;
};


#endif