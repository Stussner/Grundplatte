//******************************************************************************************************************************************************************************************************
//  Projekt     : grundplatte
//  Modul       : _grafikwindows.hpp
//  Datum       : 24.08.2008
//******************************************************************************************************************************************************************************************************
#ifndef _grafikwindowsh_included
#define _grafikwindowsh_included
#include <_global.hpp>
#include <_system.hpp>
#include <_grafik.hpp>
#include <_text.hpp>
#include <_vektor.hpp>
#include <_bild.hpp>
#include <math.h>
#ifdef GRUNDPLATTE_UNTER_WINDOWS
#include <windows.h>
//******************************************************************************************************************************************************************************************************
//                                                              F O R W A R D S 
//******************************************************************************************************************************************************************************************************
namespace _win{
 template<class _tt=typtext,class _tg=typgeometrie,class _to=typoptik> class _grafik;
 template<class _tt=typtext,class _tg=typgeometrie,class _to=typoptik> class _grafikgdi;
};

//******************************************************************************************************************************************************************************************************
//                                                              W I N : : G R A P H I C 
//******************************************************************************************************************************************************************************************************
namespace _win{
 template<class _tt,class _tg,class _to> class _grafik:public ::_grafik<_tt,_tg,_to>{
        public:
                _grafik();
                virtual ~_grafik();
                static LRESULT PASCAL prozess(HWND,UINT,WPARAM,LPARAM);
                //virtual void clearscreen();
                void reskalieren();
                void loeschenseite();
                void umschaltenseite();

                virtual void materialfarbe(const _vektor4<_to>&);
                virtual void materialemission(const _vektor4<_to>&);
                virtual void materialglanz(const _vektor4<_to>&);
                virtual void materialglanzbreite(_tg);
                
                
                virtual void tiefenbuffertesten(const bool);
                virtual void tiefenbufferschreiben(const bool);
                virtual void cull(const bool);
                
                virtual void blend(const bool);
                virtual void stencil(const bool);
                virtual void textur(const bool);
                
                virtual void pixel(const _vektor3<_tg>&,const _vektor4<_to>&);
                virtual void linie(const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor4<_to>&);
                virtual void text(const _zeichenkette<_tt>&,const ::_zeichensatz*,const _vektor3<_tg>&,const _vektor4<_to>&);
                virtual void zeichnen(const _vektor3<_tg>&,const _vektor4<_to>&);
                virtual void zeichnen(const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor4<_to>&);
                virtual void zeichnen(const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor4<_to>&,const _vektor4<_to>&);
                virtual void zeichnen(const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor4<_to>&,const _vektor4<_to>&,const _vektor4<_to>&);
                virtual void zeichnen(const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor4<_to>&,const _vektor4<_to>&,const _vektor4<_to>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&);
                virtual void zeichnendebug(const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor4<_to>&,const _vektor4<_to>&,const _vektor4<_to>&);
                virtual void zeichnenabgeschnitten(const _vektor3<_tg>&,const _vektor4<_to>&);
                virtual void zeichnenabgeschnitten(const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor4<_to>&);
        private:
                void init(_tg,_tg,_tg,_tg,bool,bool,bool,bool);
                void reskalieren(const unsigned int,const unsigned int);
                
        private:
                HDC hdc;
                HWND handle;
                _vektor4<_to> textcolor;
                int hbitmap;
                int old;
                char*screen;
                _tg*zbuffer;
                int hdcmem;
                unsigned int planes;
                unsigned int bitspixel;
                int xoffset;
                int yoffset;
                int bitmapinfo;
                
 };
 template<class _tt,class _tg,class _to> _grafik<_tt,_tg,_to>::_grafik(): ::_grafik<_tt,_tg,_to>(2048,2048,1){
                                                                WNDCLASS wndclass;
                                                                LOGBRUSH brush;
                                                                RECT r;
                                                                brush.lbStyle   = BS_SOLID;
                                                                brush.lbColor   = RGB(0,0,0);  //Log-Window background farbe !
                                                                brush.lbHatch   = HS_VERTICAL;
                                                                wndclass.style=/*CS_HREDRAW | CS_VREDRAW|*/CS_OWNDC|CS_BYTEALIGNWINDOW|CS_BYTEALIGNCLIENT;
                                                                wndclass.lpfnWndProc=prozess;
                                                                wndclass.cbClsExtra=0;
                                                                wndclass.cbWndExtra=sizeof(LONG);
                                                                wndclass.hInstance=0;
                                                                wndclass.hIcon=0;//LoadIcon(hi,MAKEINTRESOURCE(APPICON));
                                                                wndclass.hCursor=0;//LoadCursor(NULL,IDC_CROSS);
                                                                wndclass.hbrBackground=(HBRUSH) CreateBrushIndirect(&brush);
                                                                wndclass.lpszMenuName=0;
                                                                wndclass.lpszClassName="wingraphicclass";
                                                                RegisterClass(&wndclass);
                                                                SystemParametersInfo(SPI_GETWORKAREA,0,&r,0);
                                                                handle=CreateWindow("wingraphicclass","_win::_grafik (low level gdi)",WS_VISIBLE|WS_POPUP,0,0,abs(r.right-r.left),abs(r.top-r.bottom),NULL,NULL,NULL,NULL);
                                                                hdc=GetDC(handle);
                                                                init(0,0,1,1,true,true,true,true);
                                                                upperleft();

 };
 template<class _tt,class _tg,class _to> _grafik<_tt,_tg,_to>::~_grafik(){
                                                                delete[] screen;
                                                                delete[] zbuffer;
                                                                //loeschen(ort[0]);
                                                                //loeschen(ort[1]);
                                                                ReleaseDC(handle,hdc);
                                                                DestroyWindow(handle);
 };
 template<class _tt,class _tg,class _to>LRESULT PASCAL _grafik<_tt,_tg,_to>::prozess(HWND hw,UINT m,WPARAM w,LPARAM l){
                                                                return(DefWindowProc(hw,m,w,l));                                                                        
 };
 /*
_gdisoft::_gdisoft(_fenster*w,float x0,float y0,float x1,float y1){
                                                                init(w,x0,y0,x1,y1,1,1,1,1);
};
_gdisoft::_gdisoft(_fenster*w,float x0,float y0,float x1,float y1,char dx0,char dy0,char dx1,char dy1){
                                                                init(w,x0,y0,x1,y1,dx0,dy0,dx1,dy1);
};
*/
 template<class _tt,class _tg,class _to>
 void _grafik<_tt,_tg,_to>::init(_tg x0,_tg y0,_tg x1,_tg y1,bool dx0,bool dy0,bool dx1,bool dy1){
                                                                BITMAPINFOHEADER*h;
                                                                RECT r;
                                                                unsigned int sx;
                                                                _vektor<unsigned int> ss;
                                                                //------------------------------------
                                                                //window=w;
                                                                //w->getwidth();
                                                                //ort[0]=new _windowcoordinate(window,x0,y0,dx0,dy0);
                                                                //ort[1]=new _windowcoordinate(window,x1,y1,dx1,dy1);
                                                                if(GetDeviceCaps(hdc,PLANES)==0) {};//MessageBox("WindowDevice is not capable to blit RGB daten in graphic device context.");                                                             
                                                                GetWindowRect(handle,&r);
                                                                lowerleft();//swaporigin=0;
                                                                sx=(unsigned int)fabs(r.right-r.left);
                                                                sx-=sx%4;
                                                                sx+=4;
                                                                groesse(sx,(unsigned int)fabs(r.bottom-r.top),1);
                                                                //res[0]=(unsigned int)fabs(ort[1]->getx()-ort[0]->getx());//w->clientarea[1]->o[0]*(x1-x0);
                                                                //res[1]=fabs(ort[1]->gety()-ort[0]->gety());//w->clientarea[1]->o[1]*(y1-y0);
                                                                ss=groesse();
                                                                normallowest(0,0,0.01);
                                                                normalhighest(ss[0],ss[1],1000000);
                                                                //range[0][0]=0;
                                                                //range[0][1]=res[0];
                                                                //range[1][0]=0;
                                                                //range[1][1]=res[1];
                                                                //xoffset=ort[0]->getx();//w->clientarea[0]->o[0]+(ort[0]->o[0])*w->clientarea[1]->o[0];
                                                                //yoffset=ort[0]->gety();//w->clientarea[0]->o[1]+(ort[0]->o[1])*w->clientarea[1]->o[1];
                                                                xoffset=0;
                                                                yoffset=0;
                                                                //range[2][0]=0.01;
                                                                //range[2][1]=1000000;
                                                                zbuffer=new _tg[ss[0]*ss[1]];
                                                                screen=new char[ss[0]*ss[1]*3];
                                                                planes=GetDeviceCaps(hdc,PLANES);
                                                                bitspixel=GetDeviceCaps(hdc,BITSPIXEL);
                                                                bitmapinfo=(int)new (BITMAPINFO);
                                                                h=&(((BITMAPINFO*)(bitmapinfo))->bmiHeader);
                                                                h->biSize=sizeof(BITMAPINFOHEADER);
                                                                h->biWidth=ss[0];
                                                                if(lowerleftis()==false) h->biHeight=-ss[1]; else h->biHeight=ss[1];
                                                                h->biPlanes=1;
                                                                h->biBitCount=24;//bitspixel;
                                                                h->biCompression=BI_RGB;
                                                                h->biSizeImage=0;//3*res[0]*res[1];
                                                                h->biXPelsPerMeter=0;
                                                                h->biYPelsPerMeter=0;
                                                                h->biClrUsed=0;
                                                                h->biClrImportant=0;
                                                                loeschenseite();
                                                                umschaltenseite();
                                                                //printf("groessex=%i\n",groessex());
                                                                //printf("groessey=%i\n",groessey());

 };
 template<class _tt,class _tg,class _to>
 void _grafik<_tt,_tg,_to>::reskalieren(const unsigned int nx,const unsigned int ny){
                                                                BITMAPINFOHEADER*h;
                                                                delete screen;
                                                                delete zbuffer;
                                                                //------------------
                                                                ss[0]=nx;
                                                                ss[1]=ny;
                                                                ss[0]-=ss[0]%4;
                                                                ss[0]+=4;
                                                                zbuffer=new float[ss[0]*ss[1]];
                                                                screen=new char[ss[0]*ss[1]*3];
                                                                h=&(((BITMAPINFO*)(bitmapinfo))->bmiHeader);
                                                                h->biWidth=ss[0];
                                                                if(swaporigin) h->biHeight=-ss[1]; else h->biHeight=ss[1];
                                                                h->biSizeImage=0;
                                                                loeschenseite();
                                                                umschaltenseite();
 };
 template<class _tt,class _tg,class _to>
 void _grafik<_tt,_tg,_to>::reskalieren(){
                                                                _vektor<unsigned int> ss;
                                                                RECT r;
                                                                //--------------------------
                                                                xoffset=0;//ort[0]->getx();//window->clientarea[0]->o[0]+ort[0]->o[0]*window->clientarea[1]->o[0];
                                                                yoffset=0;//ort[0]->gety();//window->clientarea[0]->o[1]+ort[0]->o[1]*window->clientarea[1]->o[1];
                                                                ss=groesse();
                                                                GetWindowRect(handle,&r);
                                                                sx=(unsigned int)fabs(r.right-r.left);
                                                                sx-=sx%4;
                                                                sx+=4;
                                                                groesse(sx,(unsigned int)fabs(r.bottom-r.top),1);
                                                                //res[0]=(unsigned int)fabs(ort[1]->getx()-ort[0]->getx());//w->clientarea[1]->o[0]*(x1-x0);
                                                                //res[1]=fabs(ort[1]->gety()-ort[0]->gety());//w->clientarea[1]->o[1]*(y1-y0);
                                                                ss=groesse();
                                                                normallowest(0,0,0.01);
                                                                normalhighest(ss[0],ss[1],1000000);
                                                                reskalieren(ss[0],ss[1]);
 };
 template<class _tt,class _tg,class _to>
 void _grafik<_tt,_tg,_to>::loeschenseite(){
                                                                unsigned int i;
                                                                unsigned int max;
                                                                //------------------
                                                                max=groessex()*groessey();
                                                                for(i=0;i<max;i++){
                                                                 screen[i*3+0]=0;
                                                                 screen[i*3+1]=0;
                                                                 screen[i*3+2]=0;
                                                                 zbuffer[i]=normalhighestz();
                                                                };
 };
 template<class _tt,class _tg,class _to>
 void _grafik<_tt,_tg,_to>::umschaltenseite(){
                                                                _vektor<unsigned int> ss;
                                                                //-----------------------
                                                                ss=groesse();
                                                                SetDIBitsToDevice(hdc,xoffset,yoffset,ss[0],ss[1],0,0,0,ss[1],screen,(BITMAPINFO*)bitmapinfo,DIB_RGB_COLORS);
 };
 template<class _tt,class _tg,class _to>
 void _grafik<_tt,_tg,_to>::materialfarbe(const _vektor4<_to>&){
 };
 template<class _tt,class _tg,class _to>
 void _grafik<_tt,_tg,_to>::materialemission(const _vektor4<_to>&){
 };
 template<class _tt,class _tg,class _to>
 void _grafik<_tt,_tg,_to>::materialglanz(const _vektor4<_to>&){
 };
 template<class _tt,class _tg,class _to>
 void _grafik<_tt,_tg,_to>::materialglanzbreite(_tg){
 };

 template<class _tt,class _tg,class _to>
 void _grafik<_tt,_tg,_to>::tiefenbuffertesten(const bool ){
 };
 template<class _tt,class _tg,class _to>
 void _grafik<_tt,_tg,_to>::tiefenbufferschreiben(const bool ){
 };
 template<class _tt,class _tg,class _to>
 void _grafik<_tt,_tg,_to>::cull(const bool ){
 };
 template<class _tt,class _tg,class _to>
 void _grafik<_tt,_tg,_to>::stencil(const bool ){
 };
 template<class _tt,class _tg,class _to>
 void _grafik<_tt,_tg,_to>::blend(const bool ){
 };
 template<class _tt,class _tg,class _to>
 void _grafik<_tt,_tg,_to>::textur(const bool ){
 };
 template<class _tt,class _tg,class _to> 
 void _grafik<_tt,_tg,_to>::pixel(const _vektor3<_tg>&x,const _vektor4<_to>&c){
                                                                zeichnenabgeschnitten(x,c);
 };
 template<class _tt,class _tg,class _to> 
 void _grafik<_tt,_tg,_to>::linie(const _vektor3<_tg>&x,const _vektor3<_tg>&y,const _vektor4<_to>&c){
                                                                zeichnenabgeschnitten(x,y,c);
 };
 template<class _tt,class _tg,class _to>
 void _grafik<_tt,_tg,_to>::text(const _zeichenkette<_tt>&,const ::_zeichensatz*,const _vektor3<_tg>&,const _vektor4<_to>&){
 };

 template<class _tt,class _tg,class _to>
 void _grafik<_tt,_tg,_to>::zeichnen(const _vektor3<_tg>&w,const _vektor4<_to>&c){
                                                                unsigned int off;
                                                                unsigned int offp;
                                                                
                                                                //-------------
                                                             /*   for(off=0;off<1000;off+=3){
                                                                  screen[0]=255;
                                                                  screen[1]=255;
                                                                  screen[2]=255;
                                                                  };*/
                                                                
                                                                off=(groessey()-(unsigned int)w[1])*groessex() + (unsigned int)(w[0]);
                                                                offp=off*3;
                                                                if( (off>=0)&&(off<( groessex()*groessey() ) )){                                                                
                                                                 if(zbuffer[off]>=w[2]){
                                                                  screen[offp+0]=char(c[2]*255);
                                                                  screen[offp+1]=char(c[1]*255);
                                                                  screen[offp+2]=char(c[0]*255);
                                                                  zbuffer[off]=w[2];
                                                                 };
                                                                }else{
                                                                // G->peep(1,30000,0);
                                                                };
 };
 template<class _tt,class _tg,class _to>
 void _grafik<_tt,_tg,_to>::zeichnen(const _vektor3<_tg>&vx,const _vektor3<_tg>&vy,const _vektor4<_to>&c){
                                                                _vektor3<_tg> v0;
                                                                _vektor3<_tg> v1;
                                                                _vektor3<_tg> vh;
                                                                int dx;
                                                                int dy;
                                                                int inc[2];
                                                                int d,x,y;
                                                                unsigned int off;
                                                                short int w;
                                                                float tinc;
                                                                char r,g,b;
                                                                unsigned int res[3];
                                                                //-----------
                                                                v0=vx;
                                                                v1=vy;
                                                                res[0]=groessex();
                                                                res[1]=groessey();
                                                                if(fabs(v0[0]-v1[0])>=fabs(v0[1]-v1[1])){
                                                                 if(v0[0]>v1[0]) {vh=v1;v1=v0;v0=vh;};
                                                                 r=(char)(c[0]*255);
                                                                 g=(char)(c[1]*255);
                                                                 b=(char)(c[2]*255);
                                                               //  a=v0->c[3];
                                                                 w=b>>3;
                                                                 w|=int(g>>2)<<5;
                                                                 w|=int(r>>3)<<11;
                                                                
                                                                 if(v0[1]>v1[1]) tinc=-1; else tinc=+1;
                                                                 off=((int(res[1]-v0[1])*res[0]+int(v0[0])))*3;
                                                                 dx=abs(int(v1[0]-v0[0]));
                                                                 dy=abs(int(v1[1]-v0[1]));
                                                                 d=2*dy-dx;
                                                                 inc[0]=2*dy;
                                                                 inc[1]=(dy-dx)*2;
                                                                 x=(int)v0[0];
                                                                 y=(int)v0[1];
                                                                 do{// while(x<v1->w[0]){
                                                                  if((off>=0)&&(off<(res[0]*res[1]*3))) {
                                                                   screen[off+0]=b;
                                                                   screen[off+1]=g;
                                                                   screen[off+2]=r;
                                                                  };
                                                                  x++;
                                                                  off+=3;
                                                                  if(d<=0){
                                                                   d+=inc[0];
                                                                  }else{
                                                                   d+=inc[1];
                                                                   y++;
                                                                   off-=(res[0]*((unsigned int)(tinc)))*3;
                                                                  };
                                                                 }while(x<v1[0]);
                                                                }else{//--------------------------------------------------------------------------
                                                                 if(v0[1]>v1[1]) {vh=v1;v1=v0;v0=vh;};
                                                                 r=(char)(c[0]*255);
                                                                 g=(char)(c[1]*255);
                                                                 b=(char)(c[2]*255);
                                                                // a=c[3];
                                                                 w=b>>3;
                                                                 w|=int(g>>2)<<5;
                                                                 w|=int(r>>3)<<11;
                                                                 if(v0[0]>v1[0]) tinc=-1; else tinc=+1;
                                                                 off=((int(res[1]-v0[1])*res[0]+int(v0[0])))*3;
                                                                 dx=abs(int(v1[1]-v0[1]));
                                                                 dy=abs(int(v1[0]-v0[0]));
                                                                 d=2*dy-dx;
                                                                 inc[0]=2*dy;
                                                                 inc[1]=(dy-dx)*2;
                                                                 x=(int)v0[1];
                                                                 y=(int)v0[0];
                                                                 do{//while(x<v1->w[1]){
                                                                  if((off>=0)&&(off<(res[0]*res[1]*3))){
                                                                   screen[off+0]=b;
                                                                   screen[off+1]=g;
                                                                   screen[off+2]=r;
                                                                  };
                                                                  x++;
                                                                  off-=(res[0])*3;
                                                                  if(d<=0){
                                                                   d+=inc[0];
                                                                  }else{
                                                                   d+=inc[1];
                                                                   y++;
                                                                   off+=((unsigned int)(tinc))*3;
                                                                  };
                                                                 }while(x<v1[1]);
                                                                 };
                                                                
 };
 template<class _tt,class _tg,class _to>
 void _grafik<_tt,_tg,_to>::zeichnen(const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor4<_to>&,const _vektor4<_to>&){
 };
 template<class _tt,class _tg,class _to>
 void _grafik<_tt,_tg,_to>::zeichnen(const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor4<_to>&,const _vektor4<_to>&,const _vektor4<_to>&){
 };
 template<class _tt,class _tg,class _to>
 void _grafik<_tt,_tg,_to>::zeichnendebug(const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor4<_to>&,const _vektor4<_to>&,const _vektor4<_to>&){
 };
 template<class _tt,class _tg,class _to>
 void _grafik<_tt,_tg,_to>::zeichnen(const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor4<_to>&,const _vektor4<_to>&,const _vektor4<_to>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&){
 };
 template<class _tt,class _tg,class _to>
 void _grafik<_tt,_tg,_to>::zeichnenabgeschnitten(const _vektor3<_tg>&w,const _vektor4<_to>&c){
                                                                if(w[2]>normallowestz()){
                                                                 if(w[0]>=normallowestx()){
                                                                  if(w[0]<normalhighestx()){
                                                                   if(w[1]>=normallowesty()){
                                                                    if(w[1]<normalhighesty()){
                                                                     zeichnen(w,c);
                                                                    };
                                                                   };
                                                                  };
                                                                 };
                                                                };
                                                                /*if(v->w[2]>range[2][0]){
                                                                 if(v->w[0]>=range[0][0]){
                                                                  if(v->w[0]<range[0][1]){
                                                                   if(v->w[1]>=range[1][0]){
                                                                    if(v->w[1]<range[1][1]){
                                                                     zeichnen(v);
                                                                    };
                                                                   };
                                                                  };
                                                                 };
                                                                };*/
 };
 template<class _tt,class _tg,class _to>
 void _grafik<_tt,_tg,_to>::zeichnenabgeschnitten(const _vektor3<_tg>&v0,const _vektor3<_tg>&v1,const _vektor4<_to>&c){
                                                                _tg alpha[2];
                                                                _tg m[2];
                                                                _tg o[3];
                                                                _tg v[3];
                                                                //_vertex*vh;
                                                                int i;
                                                                int j;
                                                                char ok[3];
                                                                _vektor3<_tg> nv0;
                                                                _vektor3<_tg> nv1;
                                                                //-------------------
                                                                /*bewegen(v0->w,vertex[0]->w);
                                                                bewegen(v1->w,vertex[1]->w);
                                                                bewegen(v0->p,vertex[0]->p);
                                                                bewegen(v1->p,vertex[1]->p);
                                                                bewegen(v0->c,vertex[0]->c);
                                                                bewegen(v1->c,vertex[1]->c);*/
                                                                nv0=v0;
                                                                nv1=v1;
                                                                ok[0]=1;
                                                                ok[1]=1;
                                                                ok[2]=1;
                                                               /* for(i=2;i>=0;i--){
                                                                 m[0]=range[i][0];
                                                                 m[1]=range[i][1];
                                                                 if(vertex[0]->w[i]>vertex[1]->w[i]){vh=vertex[1];vertex[1]=vertex[0];vertex[0]=vh;};
                                                                 bewegen(vertex[0]->w,o);
                                                                 bewegen(vertex[1]->w,v);
                                                                 sub(o,v);
                                                                 if(v[i]){
                                                                  alpha[0]=(m[0]-o[i])/v[i];
                                                                  alpha[1]=(m[1]-o[i])/v[i];
                                                                 }else{
                                                                  if((vertex[0]->w[i]>=m[0])&&(vertex[0]->w[i]<m[1])){
                                                                   alpha[0]=-2;
                                                                   alpha[1]=+3;
                                                                  }else{
                                                                   alpha[0]=-3;
                                                                   alpha[1]=-2;
                                                                  };
                                                                 };
                                                                 if(((alpha[0]>1)&&(alpha[1]>1))||((alpha[0]<0)&&(alpha[1]<0))){ ok[i]=0;}
                                                                 else{
                                                                  if((alpha[0]>=0)&&(alpha[1]<=1)) {
                                                                   for(j=0;j<3;j++)vertex[0]->w[j]=o[j]+alpha[0]*v[j];
                                                                   for(j=0;j<3;j++)vertex[1]->w[j]=o[j]+alpha[1]*v[j];
                                                                  }else{
                                                                   if((alpha[0]>=0)&&(alpha[0]<=1)&&(alpha[1]>1)){
                                                                    if(i==2){
                                                                      vertex[0]->w[2]=o[2]+alpha[0]*v[2];
                                                                      vertex[0]->w[1]=vertex[0]->p[1]+alpha[0]*(vertex[1]->p[1]-vertex[0]->p[1]);
                                                                      vertex[0]->w[0]=vertex[0]->p[0]+alpha[0]*(vertex[1]->p[0]-vertex[0]->p[0]);
                                                                      vertex[0]->perspective_transform();
                                                                     }else
                                                                     for(j=0;j<3;j++)vertex[0]->w[j]=o[j]+alpha[0]*v[j];
                                                                    }else{
                                                                    if((alpha[0]<0)&&(alpha[1]>=0)&&(alpha[1]<=1)){
                                                                     if(i==2){
                                                                      vertex[1]->w[2]=o[2]+alpha[0]*v[2];
                                                                      vertex[1]->w[1]=vertex[0]->p[1]+alpha[1]*(vertex[1]->p[1]-vertex[0]->p[1]);
                                                                      vertex[1]->w[0]=vertex[0]->p[0]+alpha[1]*(vertex[1]->p[0]-vertex[0]->p[0]);
                                                                      vertex[1]->perspective_transform();
                                                                     }else
                                                                     for(j=0;j<3;j++)vertex[1]->w[j]=o[j]+alpha[1]*v[j];
                                                                    };
                                                                   };
                                                                  };
                                                                 };
                                                                };*/
                                                                if(ok[0]&&ok[1]&&ok[2])zeichnen(nv0,nv1,c);
 };

 
 
 /*
 template<class _tt,class _tg,class _to>
 void _gdisoft::vertexlayout(){
 };
 template<class _tt,class _tg,class _to>
 void _gdisoft::vispipe(int m){
 };
 template<class _tt,class _tg,class _to>
 void _gdisoft::init(_bitmap*b){
                                                                b->gdiinit=1;
 };
 template<class _tt,class _tg,class _to>
 void _gdisoft::exit(_bitmap*b){
                                                                b->gdiinit=0;
 };
 template<class _tt,class _tg,class _to>
 void _gdisoft::bind(_bitmap*b){
                                                                G->tm->currentbitmap=b;
                                                                G->tm->currenttexture=b->textur;
 };
 template<class _tt,class _tg,class _to>
 void _gdisoft::unbind(){
                                                                //_textur*t;
                                                                //----------
                                                                //t=G->tm->currenttexture->naechstes;
                                                                //if(t==G-currenttexture) currenttexture=0; else currenttexture=t;
                                                                
 };
 */
 
 
 
 
 /*
 template<class _tt,class _tg,class _to>
 void _gdisoft::zeichnen(_gradients*gra,_triangleedgeiterator*pLeft,_triangleedgeiterator*pRight){
                                                                int off;
                                                                int off3;
                                                                int XStart;
                                                                float XPreStep;
                                                                int Width;
                                                                float z,a;
                                                                char r,g,b;
                                                                int s,t;
                                                                float ooz,soz,toz;
                                                                float coz[4];
                                                                float vooz,vsoz,vtoz;
                                                                float vcoz[4];
                                                                int n;
                                                                short int c;
                                                                int bmwx;
                                                                int bmwxd;
                                                                int bmwyd;
                                                                char*daten;
                                                                float rd;
                                                                int offinc;
                                                                //-----------
                                                                XStart=pLeft->x;
                                                                XPreStep=XStart - pLeft->x;
                                                                off=((res[1]-pLeft->y)*res[0] + XStart);
                                                                Width=pRight->x - XStart;
                                                                if(Width>0){
                                                                 rd=+1;
                                                                 offinc=+1;
                                                                }else{
                                                                 rd=-1;
                                                                 offinc=-1;
                                                                 Width*=-1;
                                                                };
                                                                vooz=gra->doozodx*rd;
                                                                vsoz=gra->dsozodx*rd;
                                                                vtoz=gra->dtozodx*rd;
                                                                vcoz[0]=gra->dcozodx[0]*rd;
                                                                vcoz[1]=gra->dcozodx[1]*rd;
                                                                vcoz[2]=gra->dcozodx[2]*rd;
                                                                vcoz[3]=gra->dcozodx[3]*rd;
                                                                ooz=pLeft->ooz;//+XPreStep*vooz;//float OneOverZ = pLeft->OneOverZ +XPrestep * Gradients.dOneOverZdX;
                                                                soz=pLeft->soz;//+XPreStep*vsoz;//float UOverZ = pLeft->UOverZ +XPrestep * Gradients.dUOverZdX;
                                                                toz=pLeft->toz;//+XPreStep*vtoz;//float VOverZ = pLeft->VOverZ +XPrestep * Gradients.dVOverZdX;
                                                                coz[0]=pLeft->coz[0];//+XPreStep*vcoz[0];
                                                                coz[1]=pLeft->coz[1];//+XPreStep*vcoz[1];
                                                                coz[2]=pLeft->coz[2];//+XPreStep*vcoz[2];
                                                                coz[3]=pLeft->coz[3];//+XPreStep*vcoz[3];
                                                                bmwx=G->tm->currentbitmap->wx;
                                                                bmwxd=bmwx-1;
                                                                bmwyd=G->tm->currentbitmap->wy-1;
                                                                daten=G->tm->currentbitmap->daten;
                                                                while(Width--){
                                                                 //   G->peep(1);
                                                                 z=1/ooz;
                                                                 if(zbuffer[off]>=z){
                                                                  off3=off*3;
                                                                  s=soz*z;
                                                                  t=toz*z;
                                                                  n=((t&bmwyd)*bmwx+(s&bmwxd))<<2;
                                                                  r=(coz[0]*z)*(daten[n++]);
                                                                  g=(coz[1]*z)*(daten[n++]);
                                                                  b=(coz[2]*z)*(daten[n]);
                                                                 // a=coz[3]*z;
                                                                  screen[off3++]=b;
                                                                  screen[off3++]=g;
                                                                  screen[off3++]=r;
                                                                  zbuffer[off]=z;
                                                                 };
                                                                 off+=offinc;
                                                                 ooz+=vooz;//Gradients.dOneOverZdX;
                                                                 soz+=vsoz;//UOverZ += Gradients.dUOverZdX;
                                                                 toz+=vtoz;//VOverZ += Gradients.dVOverZdX;
                                                                 coz[0]+=vcoz[0];
                                                                 coz[1]+=vcoz[1];
                                                                 coz[2]+=vcoz[2];
                                                               //  coz[3]+=vcoz[3];
                                                              // G->peep(1);
                                                                };
 };
 template<class _tt,class _tg,class _to>
 void _gdisoft::zeichnen(int m,_vertex*v0,_vertex*v1,_vertex*v2){
                                                                int top,mid,bot;
                                                                int midcomp,botcomp;
                                                                _gradients*gra;
                                                                _triangleedgeiterator*tb;
                                                                _triangleedgeiterator*tm;
                                                                _triangleedgeiterator*mb;
                                                                _triangleedgeiterator*left;
                                                                _triangleedgeiterator*right;
                                                                _vertex*v[3];
                                                                float y0;
                                                                float y1;
                                                                float y2;
                                                                int MiddleIsLeft;
                                                                int height;
                                                                //--------------------------
                                                                m=m;
                                                                v[0]=v0;
                                                                v[1]=v1;
                                                                v[2]=v2;
                                                                y0=v[0]->w[1];
                                                                y1=v[1]->w[1];
                                                                y2=v[2]->w[1];
                                                                //--- sort vertices in y ---
                                                                if(y0<y1){
                                                                 if(y2<y0){
                                                                  top=2;
                                                                  mid=0;
                                                                  bot=1;
                                                                  midcomp=0;
                                                                  botcomp=1;
                                                                 }else{
                                                                  top=0;
                                                                  if(y1<y2){
                                                                   mid=1;
                                                                   bot=2;
                                                                   midcomp=1;
                                                                   botcomp=2;
                                                                  }else{
                                                                   mid=2;
                                                                   bot=1;
                                                                   midcomp=2;
                                                                   botcomp=1;
                                                                  };
                                                                 };
                                                                }else{
                                                                 if(y2<y1){
                                                                  top=2;
                                                                  mid=1;
                                                                  bot=0;
                                                                  midcomp=1;
                                                                  botcomp=0;
                                                                 }else{
                                                                  top=1;
                                                                  if(y0<y2){
                                                                   mid=0;
                                                                   bot=2;
                                                                   midcomp=3;
                                                                   botcomp=2;
                                                                  }else{
                                                                   mid=2;
                                                                   bot=0;
                                                                   midcomp=2;
                                                                   botcomp=3;
                                                                  };
                                                                 };
                                                                };
                                                           

                                                                gra=new _gradients(v);
                                                                
                                                                
                                                                tb =new _triangleedgeiterator(gra,v,top,bot);// TopToBottom(Gradients,pVertices,Top,Bottom);
                                                                tm =new _triangleedgeiterator(gra,v,top,mid);// TopToMiddle(Gradients,pVertices,Top,Middle);
                                                                mb =new _triangleedgeiterator(gra,v,mid,bot);// MiddleToBottom(Gradients,pVertices,Middle,Bottom);
                                                                
                                                                if(botcomp>midcomp){
                                                                 MiddleIsLeft=0;
                                                                 left=tb;
                                                                 right=tm;//&TopToBottom; pRight = &TopToMiddle;
                                                                }else{
                                                                 MiddleIsLeft=1;
                                                                 left=tm;
                                                                 right=tb;
                                                                };
                                                                height=tm->height;// TopToMiddle.Height;
                                                                while(height--) {
                                                                 zeichnen(gra,left,right);
                                                                 tm->iterate();
                                                                 tb->iterate();
                                                                };
                                                                height=mb->height;// MiddleToBottom.Height;
                                                                if(MiddleIsLeft){
                                                                 left=mb;
                                                                 right=tb;
                                                                }else{
                                                                 left=tb;
                                                                 right=mb;//pLeft = &TopToBottom; pRight = &MiddleToBottom;
                                                                };
                                                                while(height--){
                                                                 zeichnen(gra,left,right); 
                                                                 mb->iterate();
                                                                 tb->iterate();
                                                                };
                                                               
                                                                delete gra;
                                                                delete tb;
                                                                delete mb;
                                                                delete tm;

 };
 template<class _tt,class _tg,class _to>
 void _gdisoft::zeichnen(int m,_vertex*v0,_vertex*v1,_vertex*v2,_vertex*v3){
                                                                zeichnen(m,v0,v1,v2);
                                                                zeichnen(m,v0,v2,v3);
 };
 template<class _tt,class _tg,class _to>
 void _gdisoft::zeichnen(_poly*p){
                                                                
 };
 template<class _tt,class _tg,class _to>
 void _gdisoft::zeichnen(_vertex*v0,_vertex*v1){
                                                                int dx;
                                                                int dy;
                                                                int inc[2];
                                                                int d,x,y;
                                                                int off;
                                                                int offz;
                                                                short int w;
                                                                _vertex*vh;
                                                                int axis;
                                                                float ad[3];
                                                                float tinc;
                                                                char r,g,b,a;
                                                                //-----------
                                                                if(fabs(v0->w[0]-v1->w[0])>=fabs(v0->w[1]-v1->w[1])){
                                                                 if(v0->w[0]>v1->w[0]) {vh=v1;v1=v0;v0=vh;};
                                                                 r=v0->c[0];
                                                                 g=v0->c[1];
                                                                 b=v0->c[2];
                                                                 a=v0->c[3];
                                                                 w=b>>3;
                                                                 w|=int(g>>2)<<5;
                                                                 w|=int(r>>3)<<11;
                                                                
                                                                 if(v0->w[1]>v1->w[1]) tinc=-1; else tinc=+1;
                                                                 off=((int(res[1]-v0->w[1])*res[0]+int(v0->w[0])))*3;
                                                                 dx=abs(int(v1->w[0]-v0->w[0]));
                                                                 dy=abs(int(v1->w[1]-v0->w[1]));
                                                                 d=2*dy-dx;
                                                                 inc[0]=2*dy;
                                                                 inc[1]=(dy-dx)*2;
                                                                 x=v0->w[0];
                                                                 y=v0->w[1];
                                                                 do{// while(x<v1->w[0]){
                                                                  if((off>=0)&&(off<(res[0]*res[1]*3))) {
                                                                   screen[off+0]=b;
                                                                   screen[off+1]=g;
                                                                   screen[off+2]=r;
                                                                  };
                                                                  x++;
                                                                  off+=3;
                                                                  if(d<=0){
                                                                   d+=inc[0];
                                                                  }else{
                                                                   d+=inc[1];
                                                                   y++;
                                                                   off-=(res[0]*tinc)*3;
                                                                  };
                                                                 }while(x<v1->w[0]);
                                                                }else{//--------------------------------------------------------------------------
                                                                 if(v0->w[1]>v1->w[1]) {vh=v1;v1=v0;v0=vh;};
                                                                 r=v0->c[0];
                                                                 g=v0->c[1];
                                                                 b=v0->c[2];
                                                                 a=v0->c[3];
                                                                 w=b>>3;
                                                                 w|=int(g>>2)<<5;
                                                                 w|=int(r>>3)<<11;
                                                                 if(v0->w[0]>v1->w[0]) tinc=-1; else tinc=+1;
                                                                 off=((int(res[1]-v0->w[1])*res[0]+int(v0->w[0])))*3;
                                                                 dx=abs(int(v1->w[1]-v0->w[1]));
                                                                 dy=abs(int(v1->w[0]-v0->w[0]));
                                                                 d=2*dy-dx;
                                                                 inc[0]=2*dy;
                                                                 inc[1]=(dy-dx)*2;
                                                                 x=v0->w[1];
                                                                 y=v0->w[0];
                                                                 do{//while(x<v1->w[1]){
                                                                  if((off>=0)&&(off<(res[0]*res[1]*3))){
                                                                   screen[off+0]=b;
                                                                   screen[off+1]=g;
                                                                   screen[off+2]=r;
                                                                  };
                                                                  x++;
                                                                  off-=(res[0])*3;
                                                                  if(d<=0){
                                                                   d+=inc[0];
                                                                  }else{
                                                                   d+=inc[1];
                                                                   y++;
                                                                   off+=(tinc)*3;
                                                                  };
                                                                 }while(x<v1->w[1]);
                                                                 };
 };
 template<class _tt,class _tg,class _to>
 void _gdisoft::zeichnenabgeschnitten(_vertex*v0,_vertex*v1){
                                                                float alpha[2];
                                                                float m[2];
                                                                float o[3];
                                                                float v[3];
                                                                _vertex*vh;
                                                                int i;
                                                                int j;
                                                                char ok[3];
                                                                //-------------------
                                                                bewegen(v0->w,vertex[0]->w);
                                                                bewegen(v1->w,vertex[1]->w);
                                                                bewegen(v0->p,vertex[0]->p);
                                                                bewegen(v1->p,vertex[1]->p);
                                                                bewegen(v0->c,vertex[0]->c);
                                                                bewegen(v1->c,vertex[1]->c);
                                                                ok[0]=1;
                                                                ok[1]=1;
                                                                ok[2]=1;
                                                                for(i=2;i>=0;i--){
                                                                 m[0]=range[i][0];
                                                                 m[1]=range[i][1];
                                                                 if(vertex[0]->w[i]>vertex[1]->w[i]){vh=vertex[1];vertex[1]=vertex[0];vertex[0]=vh;};
                                                                 bewegen(vertex[0]->w,o);
                                                                 bewegen(vertex[1]->w,v);
                                                                 sub(o,v);
                                                                 if(v[i]){
                                                                  alpha[0]=(m[0]-o[i])/v[i];
                                                                  alpha[1]=(m[1]-o[i])/v[i];
                                                                 }else{
                                                                  if((vertex[0]->w[i]>=m[0])&&(vertex[0]->w[i]<m[1])){
                                                                   alpha[0]=-2;
                                                                   alpha[1]=+3;
                                                                  }else{
                                                                   alpha[0]=-3;
                                                                   alpha[1]=-2;
                                                                  };
                                                                 };
                                                                 if(((alpha[0]>1)&&(alpha[1]>1))||((alpha[0]<0)&&(alpha[1]<0))){ ok[i]=0;}
                                                                 else{
                                                                  if((alpha[0]>=0)&&(alpha[1]<=1)) {
                                                                   for(j=0;j<3;j++)vertex[0]->w[j]=o[j]+alpha[0]*v[j];
                                                                   for(j=0;j<3;j++)vertex[1]->w[j]=o[j]+alpha[1]*v[j];
                                                                  }else{
                                                                   if((alpha[0]>=0)&&(alpha[0]<=1)&&(alpha[1]>1)){
                                                                    if(i==2){
                                                                      vertex[0]->w[2]=o[2]+alpha[0]*v[2];
                                                                      vertex[0]->w[1]=vertex[0]->p[1]+alpha[0]*(vertex[1]->p[1]-vertex[0]->p[1]);
                                                                      vertex[0]->w[0]=vertex[0]->p[0]+alpha[0]*(vertex[1]->p[0]-vertex[0]->p[0]);
                                                                      vertex[0]->perspective_transform();
                                                                     }else
                                                                     for(j=0;j<3;j++)vertex[0]->w[j]=o[j]+alpha[0]*v[j];
                                                                    }else{
                                                                    if((alpha[0]<0)&&(alpha[1]>=0)&&(alpha[1]<=1)){
                                                                     if(i==2){
                                                                      vertex[1]->w[2]=o[2]+alpha[0]*v[2];
                                                                      vertex[1]->w[1]=vertex[0]->p[1]+alpha[1]*(vertex[1]->p[1]-vertex[0]->p[1]);
                                                                      vertex[1]->w[0]=vertex[0]->p[0]+alpha[1]*(vertex[1]->p[0]-vertex[0]->p[0]);
                                                                      vertex[1]->perspective_transform();
                                                                     }else
                                                                     for(j=0;j<3;j++)vertex[1]->w[j]=o[j]+alpha[1]*v[j];
                                                                    };
                                                                   };
                                                                  };
                                                                 };
                                                                };
                                                                if(ok[0]&&ok[1]&&ok[2])zeichnen(vertex[0],vertex[1]);
 };
 template<class _tt,class _tg,class _to>
 void _gdisoft::clip(char unperspectiv,int i,float nn,float q){
                                                                _vertexreference*vr0;
                                                                _vertexreference*vr1;
                                                                _vertexreference*oldfirst;
                                                                _vertexreference*vrs[2];
                                                                _vertexreference*it;
                                                                _vertexreference*itn;
                                                                float d;
                                                                float n[3]={0,0,0};
                                                                float o[3];
                                                                float a[3];
                                                                float alpha;
                                                                char allnegative;
                                                                char allpositive;
                                                                //-----------
                                                                allnegative=1;
                                                                allpositive=1;
                                                                n[i]=nn;
                                                                vr0=firstvertexreference;
                                                                if(vr0)do{
                                                                 vr1=vr0->naechstes;
                                                                 //(x-o)*n=d
                                                                 if(unperspectiv){
                                                                  d=n[i]*(vr0->vertex->p[i]-q);
                                                                  if(d>=0) {vr0->vertex->status=+1;allnegative=0;} else {vr0->vertex->status=-1;allpositive=0;};
                                                                  bewegen(vr0->vertex->p,o);
                                                                  sub(vr1->vertex->p,o,a);
                                                                  if(a[i]) alpha=(q-o[i])/a[i]; else alpha=-1;
                                                                 }else{
                                                                  d=n[i]*(vr0->vertex->w[i]-q);
                                                                  if(d>=0) {vr0->vertex->status=+1;allnegative=0;} else {vr0->vertex->status=-1;allpositive=0;};
                                                                  bewegen(vr0->vertex->w,o);
                                                                  sub(vr1->vertex->w,o,a);
                                                                  if(a[i]) alpha=(q-o[i])/a[i]; else alpha=-1;
                                                                 };
                                                                 //-----------------------------------------------------------------------------
                                                                 if((alpha>=0)&&(alpha<1)){
                                                                  interpolate(unperspectiv,vr0->vertex,vr1->vertex,i,alpha,vertex[vertexcount]);
                                                                  oldfirst=firstvertexreference;
                                                                  firstvertexreference=vr1;
                                                                  new _vertexreference(this,vertex[vertexcount]);
                                                                  firstvertexreference=oldfirst;
                                                                  vertexcount++;
                                                                 };
                                                                 //-----------------------------------------------------------------------------
                                                                 vr0=vr1;
                                                                }while(vr0!=firstvertexreference);
                                                                //alle -1-geflaggten vertices löschen , kann nur eine zusammenhängende sequenz sein
                                                                if(allpositive==0){
                                                                 if(allnegative){
                                                                  clear_ring(firstvertexreference);
                                                                 }else{
                                                                  if(firstvertexreference){
                                                                   while(firstvertexreference->vertex->status==-1) firstvertexreference=firstvertexreference->naechstes;
                                                                   it=firstvertexreference;
                                                                   do{
                                                                    itn=it->naechstes;
                                                                    if(it->vertex->status==-1) delete it;
                                                                    it=itn;
                                                                   }while(it!=firstvertexreference);
                                                                  };
                                                                 };
                                                                };
                                                                
                                                                
 };
 template<class _tt,class _tg,class _to>
 void _gdisoft::interpolate(char unperspectiv,_vertex*v0,_vertex*v1,int i,float alpha,_vertex*vr){
                                                                int j;
                                                                float oozr,ooz1,ooz0;
                                                                float cozr,coz1,coz0;
                                                                float tozr,toz1,toz0;
                                                                //----------------------
                                                                vr->status=+1;
                                                                if(unperspectiv){//alpha ist unperspectifisch
                                                                 for(j=0;j<3;j++) vr->w[j]=v0->p[j]+alpha*(v1->p[j]-v0->p[j]);
                                                                 for(j=0;j<4;j++) vr->c[j]=v0->c[j]+alpha*(v1->c[j]-v0->c[j]);
                                                                 for(j=0;j<2;j++) vr->st[0][j]=v0->st[0][j]+alpha*(v1->st[0][j]-v0->st[0][j]);
                                                                 vr->perspective_transform();
                                                                }else{//           alpha ist perspectifisch
                                                                 vr->w[0]=v0->w[0]+alpha*(v1->w[0]-v0->w[0]);
                                                                 vr->w[1]=v0->w[1]+alpha*(v1->w[1]-v0->w[1]);
                                                                 if(v0->w[2]>0) ooz0=1/v0->w[2];// else G->peep(1,1000,0);
                                                                 if(v1->w[2]>0) ooz1=1/v1->w[2];// else G->peep(1,1000,0);
                                                                 oozr=ooz0+alpha*(ooz1-ooz0);
                                                                 vr->w[2]=1/oozr;
                                                                 if((v0->w[2]>0)&&(v1->w[2]>0)){
                                                                  for(j=0;j<4;j++){
                                                                   coz0=v0->c[j]/v0->w[2];
                                                                   coz1=v1->c[j]/v1->w[2];
                                                                   cozr=coz0+alpha*(coz1-coz0);
                                                                   vr->c[j]=cozr*vr->w[2];
                                                                  };
                                                                  for(j=0;j<2;j++){
                                                                   toz0=v0->st[0][j]/v0->w[2];
                                                                   toz1=v1->st[0][j]/v1->w[2];
                                                                   tozr=toz0+alpha*(toz1-toz0);
                                                                   vr->st[0][j]=tozr*vr->w[2];
                                                                  };
                                                                 };//else G->peep(1,1000,0);
                                                                };
 };
 template<class _tt,class _tg,class _to>
 void _gdisoft::zeichnenabgeschnitten(int maske,_vertex*v0,_vertex*v1,_vertex*v2){
                                                                _vertexreference*it;
                                                                _vertex*vs;
                                                                //--------------
                                                                //bitmap=G->tm->currenttexture->firstbitmap;
                                                                //function=zeichnen;//(_gradients*,_triangleedgeiterator*,_trieangleedgeiterator*);
                                                                vertexcount=0;
                                                                clear_ring(firstvertexreference);
                                                                new _vertexreference(this,v0);
                                                                new _vertexreference(this,v1);
                                                                new _vertexreference(this,v2);
                                                                clip(1,2,+1,range[2][0]);
                                                                clip(0,0,+1,range[0][0]+2);
                                                                clip(0,0,-1,range[0][1]-2);
                                                                clip(0,1,+1,range[1][0]+2);
                                                                clip(0,1,-1,range[1][1]-2);
                                                                it=firstvertexreference;
                                                                if(it){
                                                                 
                                                                 vs=it->vertex;
                                                                 it=it->naechstes;
                                                                 do{      
                                                                  zeichnen(maske,vs,it->vertex,it->naechstes->vertex);
                                                                  it=it->naechstes;
                                                                 }while(it->naechstes!=firstvertexreference);
                                                                };
                                                                clear_ring(firstvertexreference);
 };
 template<class _tt,class _tg,class _to>
 void _gdisoft::zeichnenabgeschnitten(int maske,_vertex*v0,_vertex*v1,_vertex*v2,_vertex*v3){
                                                                zeichnenabgeschnitten(maske,v0,v1,v2);
                                                                zeichnenabgeschnitten(maske,v0,v2,v3);
 };
 template<class _tt,class _tg,class _to>
 void _gdisoft::zeichnenabgeschnitten(_poly*p){
 };
 */

 
 
//******************************************************************************************************************************************************************************************************
//                                                            W I N : : G R A P H I C G D I
//******************************************************************************************************************************************************************************************************
 template<class _tt,class _tg,class _to> class _grafikgdi:public ::_grafik<_tt,_tg,_to>{
    public:
                _grafikgdi(HDC,unsigned int,unsigned int);
                ~_grafikgdi();
                  
                virtual void tiefenbuffertesten(const bool);
                virtual void tiefenbufferschreiben(const bool);
                virtual void cull(const bool);
                virtual void blend(const bool);
                virtual void maske(const bool);
                virtual void textur(const bool);
                virtual void umschaltenseite();
                virtual void loeschenseite();
                  
                virtual void texturen(_basis::_liste<_textur<_to> >*);
                virtual void bild(_bild<_to>*);
                virtual void bindenbild(_bild<_to>*);
      
                virtual void materialfarbe(const _vektor4<_to>&);
                virtual void materialemission(const _vektor4<_to>&);
                virtual void materialglanz(const _vektor4<_to>&);
                virtual void materialglanzbreite(_tg);
      
      
                  
                virtual void pixel(const _vektor3<_tg>&,const _vektor4<_to>&);                                   //punkt zeichen, auch räumlich
                virtual void linie(const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor4<_to>&);      //linie zeichnen, auch räumlich
                virtual void rechteck(_vektor3<_tg>&,_vektor3<_tg>&,_vektor4<_to>&);         //kasten , räumlich quader
                virtual void kreis(_vektor3<_tg>&,_tg,_vektor4<_to>&);                      //kreis, räumlich kugel
                virtual void bild(_bild<_to>*,_vektor3<_tg>&,_vektor3<_tg>&);                  //bild zeichnen (in dieser überladung nur entlang x und y und auf einer z-ebene)
                virtual void bild(_bild<unsigned char>*,_vektor3<_tg>&,_vektor3<_tg>&);
                virtual void text(_zeichenkette<_tt> ,_vektor3<_tg>&,_vektor4<_to>&);     //text zeichnen (in dieser überladung nur entlang x (und y) auf einer z-ebene)
                //-------------------------------
                virtual void zeichnen(const _vektor3<_tg>&,const _vektor4<_to>&);
                virtual void zeichnen(const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor4<_to>&);
                virtual void zeichnen(const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor4<_to>&,const _vektor4<_to>&);
                virtual void zeichnen(const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor4<_to>&,const _vektor4<_to>&,const _vektor4<_to>&);
                virtual void zeichnen(const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor4<_to>&,const _vektor4<_to>&,const _vektor4<_to>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&);
                virtual void zeichnen(const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor4<_to>&,const _vektor4<_to>&,const _vektor4<_to>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&);
                virtual void zeichnen(const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor4<_to>&,const _vektor4<_to>&,const _vektor4<_to>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&);


                virtual void zeichnendebug(const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor4<_to>&,const _vektor4<_to>&,const _vektor4<_to>&);
                virtual void zeichnenabgeschnitten(const _vektor3<_tg>&,const _vektor4<_to>&);
                virtual void zeichnenabgeschnitten(const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor4<_to>&);
                  
                HDC hdc();
                //void hdc(HDC);
                  
                  
    private:
                HDC  phdc;
};

template<class _tt,class _tg,class _to> _grafikgdi<_tt,_tg,_to>::_grafikgdi(HDC h,unsigned int xs,unsigned int ys): ::_grafik<_tt,_tg,_to>(xs,ys,1) {
    phdc=h;
 }
 
 template<class _tt,class _tg,class _to> _grafikgdi<_tt,_tg,_to>::~_grafikgdi() {
 
 }

 template<class _tt,class _tg,class _to>
 void _grafikgdi<_tt,_tg,_to>::materialfarbe(const _vektor4<_to>&){
 };
 template<class _tt,class _tg,class _to>
 void _grafikgdi<_tt,_tg,_to>::materialemission(const _vektor4<_to>&){
 };
 template<class _tt,class _tg,class _to>
 void _grafikgdi<_tt,_tg,_to>::materialglanz(const _vektor4<_to>&){
 };
 template<class _tt,class _tg,class _to>
 void _grafikgdi<_tt,_tg,_to>::materialglanzbreite(_tg){
 };

template<class _tt,class _tg,class _to> void _grafikgdi<_tt,_tg,_to>::tiefenbuffertesten(const bool) {
}

template<class _tt,class _tg,class _to> void _grafikgdi<_tt,_tg,_to>::tiefenbufferschreiben(const bool) {
}
 template<class _tt,class _tg,class _to>
 void _grafikgdi<_tt,_tg,_to>::cull(const bool){
 };

template<class _tt,class _tg,class _to> void _grafikgdi<_tt,_tg,_to>::blend(const bool) {
}

template<class _tt,class _tg,class _to> void _grafikgdi<_tt,_tg,_to>::maske(const bool) {
}

template<class _tt,class _tg,class _to> void _grafikgdi<_tt,_tg,_to>::textur(const bool) {
}

template<class _tt,class _tg,class _to> void _grafikgdi<_tt,_tg,_to>::umschaltenseite() {
}

template<class _tt,class _tg,class _to> void _grafikgdi<_tt,_tg,_to>::loeschenseite() {
}


template<class _tt,class _tg,class _to> void _grafikgdi<_tt,_tg,_to>::texturen(_basis::_liste<_textur<_to> >*){};
template<class _tt,class _tg,class _to> void _grafikgdi<_tt,_tg,_to>::bild(_bild<_to>*){};
template<class _tt,class _tg,class _to> void _grafikgdi<_tt,_tg,_to>::bindenbild(_bild<_to>*){};



      
template<class _tt,class _tg,class _to> void _grafikgdi<_tt,_tg,_to>::pixel(const _vektor3<_tg>&l,const _vektor4<_to>&c) {
   SetPixel(phdc, (int)l[0], (int)l[1], RGB(char(c[0]*255),char(c[1]*255),char(c[2]*255)));
}

template<class _tt,class _tg,class _to> void _grafikgdi<_tt,_tg,_to>::linie(const _vektor3<_tg>&x,const _vektor3<_tg>&y,const _vektor4<_to>&c) {
   HPEN curpen=CreatePen(PS_SOLID,0,RGB(char(c[0]*255),char(c[1]*255),char(c[2]*255)));
   HPEN old=(HPEN)SelectObject(phdc, curpen);
   
   MoveToEx(phdc,(int)x[0],(int)x[1],NULL);
   LineTo(phdc,(int)y[0],(int)y[1]);
   
   SelectObject(phdc,old);
   DeleteObject(curpen);
}

template<class _tt,class _tg,class _to> void _grafikgdi<_tt,_tg,_to>::rechteck(_vektor3<_tg>&x,_vektor3<_tg>&y,_vektor4<_to>&c) { /*
                                                                char cr,cg,cb;
                                                                POINT p[2];
                                                                //---------------
                                                                cr=char(c[0]*255);
                                                                cg=char(c[1]*255);
                                                                cb=char(c[2]*255);
                                                                
                                                                HPEN curpen = CreatePen(PS_SOLID, 0, RGB(cr,cg,cb));
                                                                HPEN old = (HPEN)SelectObject(phdc, curpen);
                                                                HBRUSH fillbrush = CreateSolidBrush(RGB(cr,cg,cb));

                                                                HBRUSH hold= (HBRUSH)SelectObject(phdc, fillbrush);
                                                                p[0].x=x[0];
                                                                p[0].y=x[1];
                                                                p[1].x=y[0];
                                                                p[1].y=y[1];
                                                                LPtoDP(phdc, p, 2);
                                                                Rectangle(phdc,p[0].x,p[0].y,p[1].x,p[1].y);
                                                                SelectObject(phdc,old);
                                                                DeleteObject(curpen);
                                                                
                                                                SelectObject(phdc,hold);
                                                                DeleteObject(fillbrush);*/
                                                                
                                                                RECT  r;
                                                                
                                                                r.left   = (LONG)x[0];
                                                                r.top    = (LONG)x[1];
                                                                r.right  = (LONG)y[0];
                                                                r.bottom = (LONG)y[1];
                                                                
                                                                HBRUSH  hold, fillbrush = CreateSolidBrush(RGB((unsigned char)(c[0]*255),
                                                                                                               (unsigned char)(c[1]*255),
                                                                                                               (unsigned char)(c[2]*255)));
                                                                hold = (HBRUSH)SelectObject(phdc, fillbrush);
                                                                FillRect(phdc,&r,fillbrush);
                                                                
                                                                SelectObject(phdc,hold);
                                                                DeleteObject(fillbrush);
}

template<class _tt,class _tg,class _to> void _grafikgdi<_tt,_tg,_to>::kreis(_vektor3<_tg>&,_tg,_vektor4<_to>&) {
}

template<class _tt,class _tg,class _to> void _grafikgdi<_tt,_tg,_to>::bild(_bild<_to>*bild,_vektor3<_tg>&,_vektor3<_tg>&) {
   
}

template<class _tt,class _tg,class _to> void _grafikgdi<_tt,_tg,_to>::bild(_bild<unsigned char>*bild,_vektor3<_tg>&ort,_vektor3<_tg>&)
{
   HDC  hDC = GetDC(0);
   BITMAPINFO BitmapInfo;
   ZeroMemory(&BitmapInfo, sizeof(BITMAPINFO));
   BitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
   BitmapInfo.bmiHeader.biWidth = bild->groesse(0);
   BitmapInfo.bmiHeader.biHeight = bild->groesse(1);
   BitmapInfo.bmiHeader.biPlanes = 1;
   BitmapInfo.bmiHeader.biBitCount = bild->kanaele() << 3;
   BitmapInfo.bmiHeader.biCompression = BI_RGB;
 
   unsigned char  *bits = bild->daten();
   HBITMAP hBitmap = CreateDIBSection(hDC, &BitmapInfo, DIB_RGB_COLORS, (void **)&bits, NULL, 0);
   ReleaseDC(0, hDC);
/*
   return hBitmap;
   
   
   BITMAPINFO  bmi;
   
   memset(&bmi, 0, sizeof(bmi));
   bmi.bmiHeader.biSize  = sizeof(BITMAPINFOHEADER);
   bmi.bmiHeader.biWidth = bild->groesse(0);
   bmi.bmiHeader.biHeight = -bild->groesse(1);
   bmi.bmiHeader.biBitCount = 24;
   bmi.bmiHeader.biPlanes = 1;
   bmi.bmiHeader.biCompression = BI_RGB;
   
   HDC  hdcMemory = CreateCompatibleDC(0);
   HBITMAP  holdbmp, hbmp = CreateCompatibleBitmap(0, bild->groesse(0), bild->groesse(1));*/
  /* 
   HBITMAP CreateDIBSection(

    HDC hdc,	// handle to device context
    CONST BITMAPINFO *pbmi,	// pointer to structure containing bitmap groesse, format, and farbe daten
    UINT iUsage,	// farbe daten typ indicator: RGB values or palette indices
    VOID *ppvBits,	// pointer to variable to receive a pointer to the bitmap’s bit values
    HANDLE hSection,	// optional handle to a datei mapping objekt
    DWORD dwOffset	// offset to the bitmap bit values within the datei mapping objekt
   );	
*/
   
   //holdbmp = (HBITMAP)SelectObject(hdcMemory, hbmp);
   
   
   //SetDIBitsToDevice(phdc, (int)ort[0],(int)ort[1], /*bild->groesse(0),bild->groesse(1)*/15,13, 0,0, 0,13/*bild->groesse(1)*/, bild->daten(), &bmi, DIB_RGB_COLORS);
   
   
   //DeleteObject(hbmp);
   //DeleteDC(hdcMemory);
}

template<class _tt,class _tg,class _to> void _grafikgdi<_tt,_tg,_to>::text(_zeichenkette<_tt> s,_vektor3<_tg>&x,_vektor4<_to>&c) {
                                                                //if(f) f->anwaehlen();
                                                                SetTextColor(phdc,RGB(char(c[0]*255),char(c[1]*255),char(c[2]*255)));
                                                                SetBkColor(phdc,RGB(char(c[0]*255),char(c[1]*255),char(c[2]*255)));
                                                                SetBkMode(phdc,TRANSPARENT);
                                                                //if(tr) SetBkMode(phdc,TRANSPARENT); else SetBkMode(phdc,OPAQUE);
                                                                TextOut(phdc,(int)x[0],(int)x[1], s, s.groesse());
}
template<class _tt,class _tg,class _to> void _grafikgdi<_tt,_tg,_to>::zeichnen(const _vektor3<_tg>&,const _vektor4<_to>&) {
}
template<class _tt,class _tg,class _to> void _grafikgdi<_tt,_tg,_to>::zeichnen(const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor4<_to>&) {
}
template<class _tt,class _tg,class _to> void _grafikgdi<_tt,_tg,_to>::zeichnen(const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor4<_to>&,const _vektor4<_to>&) {
}
template<class _tt,class _tg,class _to> void _grafikgdi<_tt,_tg,_to>::zeichnen(const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor4<_to>&,const _vektor4<_to>&,const _vektor4<_to>&) {
}
template<class _tt,class _tg,class _to> void _grafikgdi<_tt,_tg,_to>::zeichnen(const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor4<_to>&,const _vektor4<_to>&,const _vektor4<_to>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&) {
}
template<class _tt,class _tg,class _to> void _grafikgdi<_tt,_tg,_to>::zeichnen(const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor4<_to>&,const _vektor4<_to>&,const _vektor4<_to>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&) {
}
template<class _tt,class _tg,class _to> void _grafikgdi<_tt,_tg,_to>::zeichnen(const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor4<_to>&,const _vektor4<_to>&,const _vektor4<_to>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&){
};
template<class _tt,class _tg,class _to> void _grafikgdi<_tt,_tg,_to>::zeichnendebug(const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor4<_to>&,const _vektor4<_to>&,const _vektor4<_to>&) {
}
template<class _tt,class _tg,class _to> void _grafikgdi<_tt,_tg,_to>::zeichnenabgeschnitten(const _vektor3<_tg>&,const _vektor4<_to>&) {
}
template<class _tt,class _tg,class _to> void _grafikgdi<_tt,_tg,_to>::zeichnenabgeschnitten(const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor4<_to>&) {
}
template<class _tt,class _tg,class _to> HDC _grafikgdi<_tt,_tg,_to>::hdc() {
  return(phdc);
}
};
#endif
#endif
