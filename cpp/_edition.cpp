//grundplatte : edition.cpp
#include <_edition.hpp>

//_fensterverwaltung*W=0;


//*****************************************************************************************************************************************************************************************************
//                                                              W I N D O W M A N A G E R
//*****************************************************************************************************************************************************************************************************
/*
_fensterverwaltung::_fensterverwaltung():lstdcolor(0.2,0.2,0.2){
							        lspace[0]=new _vektor<double>(3);
                                                                lspace[1]=new _vektor<double>(3);
                                                                llocus[0]=new _vektor<double>(3);
                                                                llocus[1]=new _vektor<double>(3);
};
*/
                                                                //WNDCLASS wc;
                                                                //LOGBRUSH brush;
                                                                //-----------
                                                                //W=this;
                                                                //hinstance=hi;
                                                                //graphwindow=0;
                                                                //mainwindow=0;
                                                                //logwindow=0;
                                                                //soundwindow=0;
                                                                //windowheader=new _hashlistheader<_fenster>();
                                                                /*brush.lbStyle   = BS_SOLID;
                                                                brush.lbColor   = RGB(100,100,100);  //Log-Window background farbe !
                                                                brush.lbHatch   = HS_VERTICAL;
                                                                wc.style        = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
                                                                wc.lpfnWndProc  = (WNDPROC)mainwindowprocedure;
                                                                wc.cbClsExtra   = 0;
                                                                wc.cbWndExtra   = 0;//sizeof(LONG);
                                                                wc.hInstance    = (HINSTANCE)hinstance;
                                                                wc.hIcon        = LoadIcon((HINSTANCE)hinstance,MAKEINTRESOURCE(SAICON));
                                                                wc.hCursor      = LoadCursor(NULL, IDC_ARROW);
                                                                //wc.hbrBackground= (HBRUSH) GetStockObject(GRAY_BRUSH);//CreateBrushIndirect(&brush);
                                                                wc.hbrBackground= (HBRUSH) CreateBrushIndirect(&brush);;
                                                                wc.lpszMenuName = MAKEINTRESOURCE(MAINMENU);
                                                                wc.lpszClassName= "ShootAll-Mainwindowclass";
                                                               // if(!RegisterClass(&wc)) MessageBox(0,"Failed0 To Register The ShootAll-Mainwindowclass.","Error",MB_OK|MB_ICONERROR);
                                                                wc.lpfnWndProc  = (WNDPROC)logwindowprocedure;
                                                                wc.lpszMenuName = 0;
                                                                wc.lpszClassName= "ShootAll-Logwindowclass";
                                                                if(!RegisterClass(&wc)) MessageBox(0,"Failed0 To Register The ShootAll-Logwindowclass.","Error",MB_OK|MB_ICONERROR);
                                                                wc.lpfnWndProc  = (WNDPROC)dialogwindowprocedure;
                                                                wc.lpszClassName= "ShootAll-Dialogwindowclass";
                                                                //if(!RegisterClass(&wc)) MessageBox(0,"Failed0 To Register The ShootAll-Dialogwindowclass.","Error",MB_OK|MB_ICONERROR);
                                                                wc.lpfnWndProc  = (WNDPROC)soundeditdialogwindowprocedure;
                                                                wc.lpszClassName= "ShootAll-Soundeditdialogwindowclass";
                                                                if(!RegisterClass(&wc)) MessageBox(0,"Failed0 To Register The ShootAll-Soundeditdialogwindowclass.","Error",MB_OK|MB_ICONERROR);
                                                                brush.lbColor   = RGB(0,0,0);  //Log-Window background farbe !
                                                                wc.hbrBackground= (HBRUSH)CreateBrushIndirect(&brush);
                                                                wc.lpfnWndProc  = (WNDPROC)graphwindowprocedure;
                                                                wc.lpszMenuName = 0;
                                                                wc.lpszClassName= "ShootAll-Graphwindowclass";
                                                               // if(!RegisterClass(&wc)) MessageBox(0,"Failed0 To Register The ShootAll-Graphwindowclass.","Error",MB_OK|MB_ICONERROR);
                                                                wc.lpfnWndProc  = (WNDPROC)childwindowprocedure;
                                                                wc.lpszMenuName = 0;
                                                                wc.cbWndExtra    = sizeof(HANDLE);
                                                                wc.lpszClassName= "ShootAll-Childwindowclass";
                                                              //  if(!RegisterClass(&wc)) MessageBox(0,"Failed0 To Register The ShootAll-Childwindowclass.","Error",MB_OK|MB_ICONERROR);
                                                                resetidentifier();
                                                                //logwindow=new _logwindow();
                                                                //graphwindow=new _graphwindow();
                                                                soundwindow=new _soundwindow();
                                                                getspace();
                                                                */



/*
_fensterverwaltung::~_fensterverwaltung(){
                                                                delete lspace[0];
                                                                delete lspace[1];
                                                                delete llocus[0];
                                                                delete llocus[1];
};
double _fensterverwaltung::leertaste(int i,int j) const{
								if((i>=0)&&(i<2)){
                                                                 return(lspace[i]->holen(j));
                                                                }else{
                                                                 //error
                                                                 return(lspace[0]->holen(0));
                                                                };
};
_vektor<double>&_fensterverwaltung::leertaste(int i){
								if((i>=0)&&(i<2)){
                                                                 return(*lspace[i]);
                                                                }else{
                                                                 //error
                                                                 return(*lspace[0]);
                                                                };
};
_vektor<double>& _fensterverwaltung::standardcolor(){
								return(lstdcolor);
};
char _fensterverwaltung::identifizieren(unsigned long int id,_fenster*&w){
                                                                _fenster*wit;
                                                                char r;
                                                                //-----------
                                                                w=0;
                                                                r=0;
                                                                if(anfang(wit))do{
                                                                 if(id==wit->identifikation()) {
                                                                  r=1;
                                                                  w=wit;
                                                                 }else{
                                                                  r|=wit->identifizieren(id,w);
                                                                 };
                                                                }while((naechstes(wit))&&(r==0));
                                                                return(r);
};
*/

/*
void _fensterverwaltung::initwindow(){
                                                                //mainwindow=new _mainwindow();
                                                                //mainwindow->fokus();
};

void _fensterverwaltung::clearallwindow(){

                                                                //loeschen(graphwindow);
                                                                loeschen(logwindow);
                                                                loeschen(soundwindow);
                                                                //loeschen(mainwindow);
                                                                loeschen(windowheader);
};

void _fensterverwaltung::updatespace(){
                                                                RECT r;
                                                                //---------
                                                                SystemParametersInfo(SPI_GETWORKAREA,0,&r,0);
                                                                leertaste[0][0]=r.left;
                                                                leertaste[0][1]=r.top;
                                                                leertaste[1][0]=r.right;
                                                                leertaste[1][1]=r.bottom;
};
/*
void _fensterverwaltung::fokus(int h){
                                                                SetFocus(HWND(h));
};
char _fensterverwaltung::identifizieren(int handle,_fenster*&w){
                                                                _fenster*wit;
                                                                char r=0;
                                                                //-----------
                                                                w=0;
                                                           //     G->fim->schreiben("wim::Identify ",handle);
                                                                wit=windowheader->firstobject;
                                                                if(wit)do{
                                                                 if(wit->handle==handle) {r=1;w=wit;} else
                                                                 if(wit->firstwindow) r|=identifyrecursiv(wit->firstwindow,handle,w);
                                                                 wit=wit->naechstes;
                                                                }while((r==0)&&(wit!=windowheader->firstobject));
                                                           //     if(r==0) {G->fim->schreiben("wim::identifizieren fehlgeschlagen.");};
                                                                return(r);
};
char _fensterverwaltung::identifyrecursiv(_fenster*erstes,int handle,_fenster*&w){
                                                                _fenster*wit;
                                                                char r=0;
                                                                //-----------
                                                                wit=erstes;
                                                                if(wit)do{
                                                                 if(wit->handle==handle) {r=1;w=wit;} else
                                                                 if(wit->firstwindow) r|=identifyrecursiv(wit->firstwindow,handle,w);
                                                                 wit=wit->naechstes;
                                                                }while((r==0)&&(wit!=erstes));
                                                                return(r);
};
void _fensterverwaltung::resetidentifier(){
                                                                identifier=0;
};
int _fensterverwaltung::getidentifier(){
                                                                int r=identifier;
                                                                seeknextfreeidentifier();
                                                                return(r);
};
void _fensterverwaltung::seeknextfreeidentifier(){

                                                                char ok;
                                                                _fenster*wit;
                                                                //----------
                                                                do{
                                                                 ok=1;
                                                                 identifier++;
                                                                 wit=windowheader->firstobject;
                                                                 if(wit){
                                                                  do{
                                                                   if(identifier==wit->identifier) ok=0;
                                                                   wit=wit->naechstes;
                                                                  }while(wit!=windowheader->firstobject);
                                                                 };
                                                                }while(ok==0);
};

void _fensterverwaltung::animieren(){
                                                                MSG msg;
                                                                _fenster*w;
                                                                char d;
                                                                char stop;
                                                                //------
                                                                stop=0;
                                                                while((PeekMessage(&msg,NULL,0,0,PM_NOREMOVE))){
                                                                d=1;
                                                                 if(GetMessage(&msg, NULL, 0, 0)){
                                                                  if(identifizieren((int)msg.hwnd,w)){
                                                                   w->msg=&msg;
                                                                   switch(msg.schreiben){
                                                                    case WM_CHAR:
                                                                     break;
                                                                    case WM_KEYDOWN:
                                                                     G->kb->taste[msg.wParam]=1;
                                                                     d=w->keydown();
                                                                    break;
                                                                    case WM_KEYUP:
                                                                     G->kb->taste[msg.wParam]=0;
                                                                     d=w->keyup();
                                                                    break;
                                                                    case WM_MOUSEMOVE:
                                                                    break;
                                                                   };
                                                                  };
                                                                  if(d){
                                                                   TranslateMessage(&msg);
                                                                   DispatchMessage(&msg);
                                                                  };
                                                                 };//else stop=1;
                                                                };
};

void _fensterverwaltung::fullscreen(int wx,int wy){
                                                                DEVMODE ds;
                                                                //-------------------------
                                                                ds.dmSize         = sizeof(DEVMODE);                          // Storage Size
                                                                ds.dmPelsWidth    = wx;                                      // Width
                                                                ds.dmPelsHeight   = wy;                                      // Height
                                                                ds.dmFields       = DM_PELSWIDTH | DM_PELSHEIGHT;             // Color Depth
                                                                ChangeDisplaySettings(&ds, CDS_FULLSCREEN);                   // Switch To Fullscreen Mode
};
*/


//*****************************************************************************************************************************************************************************************************
//								W I N D O W A R E A
//*****************************************************************************************************************************************************************************************************
/*
_windowspace::_windowspace(_fenster*w){
								lwindow=w;
								llocus[0]=new _windowcoordinate(lwindow,0,0,0,0,0,0);
								llocus[1]=new _windowcoordinate(lwindow,0xff,0xff,1,0,0,0);
};
_windowspace::_windowspace(_fenster*w,double x0,double y0,double z0,double x1,double y1,double z1,bool a,bool b,bool c,bool d,bool e,bool f){
								lwindow=w;
                                                                llocus[0]=new _windowcoordinate(lwindow,x0,y0,z0,a,b,c);
                                                                llocus[1]=new _windowcoordinate(lwindow,x1,y1,z1,d,e,f);
};
_windowspace::~_windowspace(){
								delete llocus[0];
                                                                delete llocus[1];
};
_windowcoordinate& _windowspace::operator[](int i){
								_windowcoordinate*wc=holen(i);
                                                                return(*wc);
};
_windowcoordinate* _windowspace::holen(int i){
								if((i>=0)&&(i<3)){
								 return(llocus[i]);
                                                                }else{
                                                                 //error
                                                                 return(llocus[0]);
                                                                };
};
*/
//*****************************************************************************************************************************************************************************************************
//								W I N D O W A R E A N O D E
//*****************************************************************************************************************************************************************************************************
/*
_windowspacenode::_windowspacenode(_basis::_liste<_windowspacenode>*l,_fenster*w):_basis::_listenknoten<_windowspacenode>(l),_windowspace(w){
};
_windowspacenode::_windowspacenode(_basis::_liste<_windowspacenode>*l,_fenster*w,double x0,double y0,double z0,double x1,double y1,double z1,bool a,bool b,bool c,bool d,bool e,bool f):_basis::_listenknoten<_windowspacenode>(l),_windowspace(w,x0,y0,z0,x1,y1,z1,a,b,c,d,e,f){
};
*/
//*****************************************************************************************************************************************************************************************************
//								W I N D O W C O O R D I N A T E
//*****************************************************************************************************************************************************************************************************
/*
_windowcoordinate::_windowcoordinate(_fenster*w,double x,double y,double z,bool a,bool b,bool c){
                                                                window=w;
                                                                vectorcreate(x,y,z,a,b,c);
};
_windowcoordinate::~_windowcoordinate(){
};
_windowvector& _windowcoordinate::operator[](int i){
								return(*vektor(i));
};
_windowvector* _windowcoordinate::vectorcreate(){
								return(new _windowvector(this,0,0,0,0,0,0));
};
_windowvector* _windowcoordinate::vectorcreate(double x,double y,double z,bool a,bool b,bool c){
								return(new _windowvector(this,x,y,z,a,b,c));
};
void _windowcoordinate::vectorclear(){
								while(anzahl()>1){
                                                                 delete vektor(1);
                                                                };
};
_windowvector* _windowcoordinate::vektor(int i){
                                                                int n;
                                                                _windowvector*wv;
                                                                //-------------------------
                                                                if(anfang()){
                                                                 wv=iterator();
                                                                 for(n=0;n<i;n++) wv=wv->naechstes();
                                                                };
                                                                return(wv);
};
double _windowcoordinate::holen(int i){
                                                                _windowvector*vit;
                                                                double r;
                                                                //--------------------------
                                                                r=0;
                                                                if(anfang())do{
                                                                 vit=iterator();
                                                                 if(vit->dynamic(i)){
                                                                  if(window){
                                                                   r+=vit->holen(i)*(window->leertaste(1)->holen(i) - window->leertaste(0)->holen(i));
                                                                  }else{
                                                                   r+=vit->holen(i)*(W->leertaste(1,i) - W->leertaste(0,i));
                                                                  };
                                                                 }else{
                                                                  r+=vit->holen(i);
                                                                 };
                                                                }while(naechstes());
                                                                if(window){
                                                                 r+=window->leertaste(0)->holen(i);
                                                                }else{
                                                                 r+=W->leertaste(0,i);
                                                                };
                                                                return(r);
};
double _windowcoordinate::z(){
                                                                return(holen(2));
};
double _windowcoordinate::y(){
                                                                return(holen(1));
};
double _windowcoordinate::x(){
                                                                return(holen(0));
};
void _windowcoordinate::addx(double ax){
                                                                vektor(0)->add(0,ax);
};
void _windowcoordinate::addy(double ay){
                                                                vektor(0)->add(1,ay);
};
void _windowcoordinate::addx(int i,double ax){
                                                                vektor(i)->add(0,ax);
};
void _windowcoordinate::addy(int i,double ay){
                                                                vektor(i)->add(1,ay);
};
void _windowcoordinate::setzen(double x,double y){
                                                                vektor(0)->setzen(x,y);
};
void _windowcoordinate::setzen(int i,double x,double y){
                                                                vektor(i)->setzen(x,y);
};
*/
//*****************************************************************************************************************************************************************************************************
//								W I N D O W V E C T O R
//*****************************************************************************************************************************************************************************************************
/*
_windowvector::_windowvector(_windowcoordinate*wc,double x,double y,double z,bool dx,bool dy,bool dz):_basis::_listenknoten<_windowvector>(wc),_vektor<double>(x,y,z){
                                                                windowcoordinate=wc;
                                                                bdynamic[0]=dx;
                                                                bdynamic[1]=dy;
                                                                bdynamic[2]=dz;
                                                                //vvector.setzen(x,y);
};
_vektor<double>& _windowvector::operator=(const _vektor<double>&v){
								kopieren(v);
                                                                return(*this);
};
bool _windowvector::dynamic(int i) const{
								if((i>=0)&&(i<3)){
                                                                 return(bdynamic[i]);
                                                                }else{
                                                                 //error
                                                                 return(0);
                                                                };
};
void _windowvector::dynamic(int i,bool b){
								if((i>=0)&&(i<3)){
                                                                 bdynamic[i]=b;
                                                                }else{
                                                                 //error
                                                                };
};
void _windowvector::dynamic(bool a,bool b,bool c){
								bdynamic[0]=a;
                                                                bdynamic[1]=b;
                                                                bdynamic[2]=c;
};
*/
//*****************************************************************************************************************************************************************************************************
//							        W I N D O W D R A W A B L E
//*****************************************************************************************************************************************************************************************************
/*
_windowdrawable::_windowdrawable(_fenster*w):_basis::_listenknoten<_windowdrawable>(w->drawentries()),_windowspace(w){
                                                                lcolor[0]=new _vektor<double>(1,1,1);
                                                                lcolor[1]=new _vektor<double>(0,0,0);
};
_windowdrawable::~_windowdrawable(){
								delete lcolor[0];
                                                                delete lcolor[1];
};
_vektor<double>& _windowdrawable::farbe(int i){
								if((i>=0)&&(i<=2)){
                                                                 return(*lcolor[i]);
                                                                }else{
                                                                 //error
                                                                 return(*lcolor[0]);
                                                                };
};
*/
//*****************************************************************************************************************************************************************************************************
//							        W I N D O W P O I N T
//*****************************************************************************************************************************************************************************************************
/*
_windowpoint::_windowpoint(_fenster*w,double x,double y,double r,double g,double b):_windowdrawable(w){
								init(x,y,0,0);
                                                                farbe(0).setzen(r,g,b);
                                                                farbe(1).setzen(r,g,b);
};
_windowpoint::_windowpoint(_fenster*w,double x,double y,_vektor<double>&c):_windowdrawable(w){
								init(x,y,0,0);
                                                                farbe(0).kopieren(c);
                                                                farbe(1).kopieren(c);
};
_windowpoint::_windowpoint(_fenster*w,double x,double y,bool xd,bool yd,_vektor<double>&c):_windowdrawable(w){
								init(x,y,xd,yd);
                                                                farbe(0).kopieren(c);
                                                                farbe(1).kopieren(c);
};
void _windowpoint::init(double x,double y,bool a,bool b){
								holen(0)->setzen(x,y);
                                                                holen(1)->setzen(x,y);
                                                                holen(0)->vektor(0)->dynamic(a,b);
                                                                holen(1)->vektor(0)->dynamic(a,b);
};
*/
//*****************************************************************************************************************************************************************************************************
//							        W I N D O W L I N E
//*****************************************************************************************************************************************************************************************************
/*
_windowline::_windowline(_fenster*w,double x0,double y0,double x1,double y1,double r,double g,double b):_windowdrawable(w){
								init(x0,y0,x1,y1,0,0,0,0);
                                                                farbe(0).setzen(r,g,b);
                                                                farbe(1).setzen(r,g,b);
};
_windowline::_windowline(_fenster*w,double x0,double y0,double x1,double y1,_vektor<double>&c):_windowdrawable(w){
								init(x0,y0,x1,y1,0,0,0,0);
                                                                farbe(0).kopieren(c);
                                                                farbe(1).kopieren(c);
};
_windowline::_windowline(_fenster*w,double x0,double y0,double x1,double y1,bool a,bool b,bool c,bool d,_vektor<double>&col):_windowdrawable(w){
								init(x0,y0,x1,y1,a,b,c,d);
                                                                farbe(0).kopieren(col);
                                                                farbe(1).kopieren(col);
};
void _windowline::init(double x0,double y0,double x1,double y1,bool a,bool b,bool c,bool d){
								holen(0)->setzen(x0,y0);
                                                                holen(1)->setzen(x1,y1);
                                                                holen(0)->vektor(0)->dynamic(a,b);
                                                                holen(1)->vektor(0)->dynamic(c,d);
};
*/
//*****************************************************************************************************************************************************************************************************
//							        W I N D O W R E C T
//*****************************************************************************************************************************************************************************************************
/*
_windowrectangle::_windowrectangle(_fenster*w,double x0,double y0,double x1,double y1,double r,double g,double b):_windowline(w,x0,y0,x1,y1,r,g,b){
};
_windowrectangle::_windowrectangle(_fenster*w,double x0,double y0,double x1,double y1,_vektor<double>&c):_windowline(w,x0,y0,x1,y1,c){
};
_windowrectangle::_windowrectangle(_fenster*w,double x0,double y0,double x1,double y1,bool a,bool b,bool c,bool d,_vektor<double>&col):_windowline(w,x0,y0,x1,y1,a,b,c,d,col){
};
*/
//*****************************************************************************************************************************************************************************************************
//							        W I N D O W B I T M A P
//*****************************************************************************************************************************************************************************************************
/*
_windowbitmap::_windowbitmap(_fenster*w,_zeichenkette&s,double x0,double y0,double x1,double y1):_windowdrawable(w),_bitmap(s){
								init(x0,y0,x1,y1,0,0,0,0);
};
_windowbitmap::_windowbitmap(_fenster*w,_zeichenkette&s,double x0,double y0,double x1,double y1,bool a,bool b,bool c,bool d):_windowdrawable(w),_bitmap(s){
								init(x0,y0,x1,y1,a,b,c,d);
};
void _windowbitmap::init(double x0,double y0,double x1,double y1,bool a,bool b,bool c,bool d){
								holen(0)->setzen(x0,y0);
                                                                holen(1)->setzen(x1,y1);
                                                                holen(0)->vektor(0)->dynamic(a,b);
                                                                holen(1)->vektor(0)->dynamic(c,d);
                                                                farbe(0).setzen(1,1,1);
                                                                farbe(1).setzen(0,0,0);
};
*/
//*****************************************************************************************************************************************************************************************************
//							        W I N D O W B I T M A P A S S O C I A T I O N
//*****************************************************************************************************************************************************************************************************
/*
_windowbitmapassociation::_windowbitmapassociation(_fenster*w,_bitmap*bm,double x0,double y0,double x1,double y1):_windowdrawable(w){
								init(x0,y0,x1,y1,0,0,0,0);
                                                                lbitmap=bm;
};
_windowbitmapassociation::_windowbitmapassociation(_fenster*w,_bitmap*bm,double x0,double y0,double x1,double y1,bool a,bool b,bool c,bool d):_windowdrawable(w){
								init(x0,y0,x1,y1,a,b,c,d);
                                                                lbitmap=bm;
};
void _windowbitmapassociation::init(double x0,double y0,double x1,double y1,bool a,bool b,bool c,bool d){
								holen(0)->setzen(x0,y0);
                                                                holen(1)->setzen(x1,y1);
                                                                holen(0)->vektor(0)->dynamic(a,b);
                                                                holen(1)->vektor(0)->dynamic(c,d);
                                                                farbe(0).setzen(1,1,1);
                                                                farbe(1).setzen(0,0,0);
};
_bitmap* _windowbitmapassociation::bitmap(){
								return(lbitmap);
};
*/
//*****************************************************************************************************************************************************************************************************
//							        W I N D O W S T R I N G
//*****************************************************************************************************************************************************************************************************
/*
_windowstring::_windowstring(_fenster*w,_zeichenkette&s,double x,double y,double r,double g,double b):_windowdrawable(w){
								init(s,x,y,0,0);
                                                                farbe(0).setzen(r,g,b);
                                                                farbe(1).setzen(0,0,0);
};
_windowstring::_windowstring(_fenster*w,_zeichenkette&s,double x,double y,_vektor<double>&v):_windowdrawable(w){
								init(s,x,y,0,0);
                                                                farbe(0).kopieren(v);
};
_windowstring::_windowstring(_fenster*w,_zeichenkette&s,double x,double y,_vektor<double>&v,_vektor<double>&h):_windowdrawable(w){
								init(s,x,y,0,0);
                                                                farbe(0).kopieren(v);
                                                                farbe(1).kopieren(h);
};
_windowstring::_windowstring(_fenster*w,_zeichenkette&s,double x,double y,bool a,bool b,_vektor<double>&v):_windowdrawable(w){
								init(s,x,y,a,b);
                                                                farbe(0).kopieren(v);
                                                                farbe(1).setzen(0,0,0);
};
_windowstring::_windowstring(_fenster*w,_zeichenkette&s,double x,double y,bool a,bool b,_vektor<double>&v,_vektor<double>&h):_windowdrawable(w){
								init(s,x,y,a,b);
                                                                farbe(0).kopieren(v);
                                                                farbe(1).kopieren(h);
};
void _windowstring::init(_zeichenkette&s,double x,double y,bool a,bool b){
								kopieren(s);
								_windowspace::holen(0)->setzen(x,y);
                                                                _windowspace::holen(1)->setzen(x,y);
                                                                _windowspace::holen(0)->vektor(0)->dynamic(a,b);
                                                                _windowspace::holen(1)->vektor(0)->dynamic(a,b);
};
*/
//*****************************************************************************************************************************************************************************************************
//							        W I N D O W S T R I N G A S S O C I A T I O N
//*****************************************************************************************************************************************************************************************************
/*
_windowstringassociation::_windowstringassociation(_fenster*w,_zeichenkette&s,double x,double y,double r,double g,double b):_windowdrawable(w){
								init(s,x,y,0,0);
                                                                farbe(0).setzen(r,g,b);
                                                                farbe(1).setzen(0,0,0);
};
_windowstringassociation::_windowstringassociation(_fenster*w,_zeichenkette&s,double x,double y,_vektor<double>&v):_windowdrawable(w){
								init(s,x,y,0,0);
                                                                farbe(0).kopieren(v);
};
_windowstringassociation::_windowstringassociation(_fenster*w,_zeichenkette&s,double x,double y,_vektor<double>&v,_vektor<double>&h):_windowdrawable(w){
								init(s,x,y,0,0);
                                                                farbe(0).kopieren(v);
                                                                farbe(1).kopieren(h);
};
_windowstringassociation::_windowstringassociation(_fenster*w,_zeichenkette&s,double x,double y,bool a,bool b,_vektor<double>&v):_windowdrawable(w){
								init(s,x,y,a,b);
                                                                farbe(0).kopieren(v);
                                                                farbe(1).setzen(0,0,0);
};
_windowstringassociation::_windowstringassociation(_fenster*w,_zeichenkette&s,double x,double y,bool a,bool b,_vektor<double>&v,_vektor<double>&h):_windowdrawable(w){
								init(s,x,y,a,b);
                                                                farbe(0).kopieren(v);
                                                                farbe(1).kopieren(h);
};
void _windowstringassociation::init(_zeichenkette&s,double x,double y,bool a,bool b){
								lstring=&s;
								_windowspace::holen(0)->setzen(x,y);
                                                                _windowspace::holen(1)->setzen(x,y);
                                                                _windowspace::holen(0)->vektor(0)->dynamic(a,b);
                                                                _windowspace::holen(1)->vektor(0)->dynamic(a,b);
};
_zeichenkette& _windowstringassociation::string(){
								return(*lstring);
};*/
//*****************************************************************************************************************************************************************************************************
//							        W I N D O W
//*****************************************************************************************************************************************************************************************************
/*
_fenster::_fenster():_basis::_listelistenknoten<_fenster>(W),lspace(this),llocus(0),lcolor(0.2,0.2,0.2),lspacemin(0,0),lspacemax(0xff,0xff){
								init();
};
_fenster::_fenster(_fenster*w):_basis::_listelistenknoten<_fenster>(W),lspace(this),llocus(w),lcolor(0.2,0.2,0.2),lspacemin(0,0),lspacemax(0xff,0xff){
								init();
                                                                lwindow=w;
};
void _fenster::init(){
                                                                lflag=0;
                                                                lwindow=0;
                                                                clipactivity(false);
                                                                aktivitaet(true);
                                                                fokus(false);
                                                                sichtbarkeit(true);
};
_fenster::~_fenster(){
};
_fenster* _fenster::window(){
								return(lwindow);
};
char _fenster::identifizieren(unsigned long int id,_fenster*&w){
								_fenster*wit;
                                                                char r;
                                                                //---------------
                                                                r=0;
                                                                w=0;
								if(anfang(wit))do{
                                                                 if(id==wit->identifikation()){
                                                                  r=1;
                                                                  w=wit;
                                                                 }else{
                                                                  r|=wit->identifizieren(id,w);
                                                                 };
                                                                }while((naechstes(wit))&&(r==0));
                                                                return(r);
};
_windowcoordinate* _fenster::ort(int i){
								if((i>=0)&&(i<=2)){
                                                                 return(&llocus[i]);
                                                                }else{
                                                                 //error
                                                                 return(&llocus[0]);
                                                                };
};
_windowvector* _fenster::locusvectorcreate(int i){
								if((i>=0)&&(i<=2)){
                                                                 return(llocus[i].vectorcreate());
                                                                }else{
                                                                 //error
                                                                 return(0);
                                                                };

};
void _fenster::locusvectorclear(int i){
								if((i>=0)&&(i<=2)){
                                                                 llocus[i].vectorclear();
                                                                }else{
                                                                 //error
                                                                };
};
void _fenster::ort(double x,double y){
								double wx;
                                                                double wy;
                                                                //----------
                                                                wx=ort(1)->x()-ort(0)->x();
                                                                wy=ort(1)->y()-ort(0)->y();
                                                                locusvectorclear(0);
                                                                locusvectorclear(1);
                                                                ort(0)->vektor(0)->setzen(x,y);
                                                                ort(1)->vektor(0)->setzen(x+wx,y+wy);
};
_windowcoordinate* _fenster::leertaste(int i){
								if((i>=0)&&(i<=2)){
                                                                 return(&lspace[i]);
                                                                }else{
                                                                 //error
                                                                 return(&lspace[0]);
                                                                };
};
void _fenster::leertaste(double,double){
								//muss indirekt ein locusupdate() aufrufen
};
void _fenster::spaceminimal(double x,double y){
								lspacemin.setzen(x,y);
};
void _fenster::spacemaximal(double x,double y){
								lspacemax.setzen(x,y);
};
_windowcoordinate* _fenster::clipspace(int i,int j){
								_windowcoordinate*wc;
                                                                //-------------------
                                                                if((i<0)||(i>2)) {
                                                                 //error
                                                                 i=0;
                                                                };
                                                                if((j<0)||(j>2)) {
                                                                 //error
                                                                 j=0;
                                                                };
                                                                if(lclipspaces.anzahl()>0){
                                                                 wc=lclipspaces[i]->holen(j);
                                                                 return(wc);
                                                                }else{
                                                                 return(0);
                                                                };
};
_windowspace* _fenster::clipspacecreate(double x0,double y0,double z0,double x1,double y1,double z1){
								return(new _windowspacenode(&lclipspaces,this,x0,y0,z0,x1,y1,z1,0,0,0,0,0,0));
};
bool _fenster::clipactivity() const{
								return(lclip);
};
void _fenster::clipactivity(bool b){
								lclip=b;
};
void _fenster::clipspaceclear(){
								lclipspaces.loeschen();
                                                                clipactivity(false);
};
_vektor<double>&_fenster::farbe(){
								return(lcolor);
};
void _fenster::farbe(double r,double g,double b){
								lcolor.setzen(r,g,b);
};
void _fenster::farbe(_vektor<double>&c){
								lcolor.kopieren(c);
};
void _fenster::aktivitaet(bool b){
								lactive=b;
};
bool _fenster::aktivitaet() const {
								return(lactive);
};
void _fenster::sichtbarkeit(bool b){
								lvisible=b;
};
bool _fenster::sichtbarkeit() const{
								return(lvisible);
};
void _fenster::fokus(bool b){
								lfocus=b;
};
bool _fenster::fokus() const {
								return(lfocus);
};


 */





/*
_zeichenkette _fenster::titel() const{
								return(ltitle);
};
void _fenster::titel(_zeichenkette t){
                             					ltitle=t;
};
*/
/*
void _fenster::enable(){
                                                                EnableWindow((HWND)handle,TRUE);
};
void _fenster::disable(){
                                                                EnableWindow((HWND)handle,FALSE);
};
char _fenster::keydown(){
                                                                //if(G->kb->taste[VK_TAB]) naechstes->fokus();
                                                                return(1);
};
char _fenster::keyup(){
                                                                return(1);
};

void _fenster::link(_hashlistheader<_fenster>*h,_fenster*w){
                                                                header=h;
                                                                window=w;
                                                                if(window==0){
                                                                 einhaengen(this,header->firstobject);
                                                                }else{
                                                                 einhaengen(this,window->firstwindow);
                                                                };
};

void _fenster::updatewidth(){
                                                                RECT r;
                                                                float sx,sy,vx,vy,tx,ty;
                                                                //-----------
                                                                GetClientRect(HWND(handle),&r);
                                                                wy=abs(r.bottom-r.top);
                                                                wx=abs(r.right-r.left);
                                                                sx=0;
                                                                sy=0;
                                                                tx=wx;
                                                                ty=wy;
                                                                if(toolbar){
                                                                 sy+=toolbar->wy+3;
                                                                };
                                                                if(statusbar){
                                                                 ty-=statusbar->wy+1;
                                                                };
                                                                vx=tx-sx;
                                                                vy=ty-sy;
                                                                clientspace[0]->setzen(sx,sy);
                                                                clientspace[1]->setzen(vx,vy);
};
void _fenster::fokus(){
                                                                SetFocus((HWND)handle);
};
void _fenster::zeigen(){
                                                                showwindow();
                                                                showtaskbarbutton();
};
void _fenster::verstecken(){
                                                                hidewindow();
                                                                hidetaskbarbutton();
};
void _fenster::showwindow(){
                                                                ShowWindow((HWND)handle,SW_SHOWNORMAL);
};
void _fenster::hidewindow(){
                                                                ShowWindow((HWND)handle,SW_HIDE);
};
void _fenster::showtaskbarbutton(){
};
void _fenster::hidetaskbarbutton(){
};
*/
/*
void _fenster::setzenvektor(int i,float x,float y,char dx,char dy){
                                                                if(llocus[i]==0) {
                                                                 if(lwindow) llocus[i]=new _windowcoordinate(lwindow,x,y,dx,dy); else llocus[i]=new _windowcoordinate(this,x,y,dx,dy);
                                                                }else{
                                                                 llocus[i]->firstwindowcoordinatevector->vektor->setzen(x,y);
                                                                 llocus[i]->firstwindowcoordinatevector->dynamic[0]=dx;
                                                                 llocus[i]->firstwindowcoordinatevector->dynamic[1]=dy;
                                                                };

};
void _fenster::setvectornull(int i,float x,float y,char dx,char dy){
                                                                if(llocus[i]==0) {
                                                                 llocus[i]=new _windowcoordinate(0,x,y,dx,dy);
                                                                }else{
                                                                 ort[i]->firstwindowcoordinatevector->vektor->setzen(x,y);
                                                                 ort[i]->firstwindowcoordinatevector->dynamic[0]=dx;
                                                                 ort[i]->firstwindowcoordinatevector->dynamic[1]=dy;
                                                                };

};
void _fenster::addvector(int i,float x,float y,char dx,char dy){
                                                                if(ort[i]){
                                                                 new _windowcoordinatevector(ort[i],x,y,dx,dy);
                                                                };
}; */
/*
void _fenster::minsize(int ,int ){
                                                            ///    SendMessage((HWND)handle,WM_SIZEMIN,0,0);
};
void _fenster::maxsize(int ,int ){
};
*/
/*
void _fenster::updatesize(){
                                                                float cx,cy,x,y;
                                                                //----------------
                                                                if(formal==0){
                                                                 if((ort[0])&&(ort[1])){
                                                                  x=ort[0]->getx();
                                                                  y=ort[0]->gety();
                                                                  cx=(ort[1]->getx()-x);
                                                                  cy=(ort[1]->gety()-y);
                                                                  MoveWindow((HWND)handle,x,y,cx,cy,TRUE);
                                                                  getwidth();
                                                                 };
                                                                };

};
void _fenster::reskalieren(){
                                                                _fenster*wit;
                                                                //-------------
                                                                if(formal==0){
                                                                 wit=firstwindow;
                                                                 if(wit)do{
                                                                  wit->updatesize();
                                                                  wit=wit->naechstes;
                                                                 }while(wit!=firstwindow);
                                                                };

}; */
/*
void _fenster::aktualisieren(){
                                                                RECT r;
                                                                if(formal==0){
                                                                 getwidth();
                                                                 r.left=clientspace[0]->o[0];
                                                                 r.right=r.left+clientspace[1]->o[0];
                                                                 r.top=clientspace[0]->o[1];
                                                                 r.bottom=r.top+clientspace[1]->o[1];
                                                                 InvalidateRect((HWND)handle,&r,TRUE);
                                                                 UpdateWindow((HWND)handle);
                                                                };
};
void _fenster::aktualisieren(float x0,float y0,float x1,float y1){
                                                                RECT r;
                                                                float sx,sy,vx,vy;
                                                                //--------------------
                                                                if(formal==0){
                                                                 sx=clientspace[0]->o[0];
                                                                 sy=clientspace[0]->o[1];
                                                                 vx=clientspace[1]->o[0];
                                                                 vy=clientspace[1]->o[1];
                                                                 r.left=sx+x0*vx;
                                                                 r.right=sx+x1*vx;
                                                                 r.top=sy+y0*vy;
                                                                 r.bottom=sy+y1*vy;
                                                                 InvalidateRect((HWND)handle,&r,TRUE);
                                                                 UpdateWindow((HWND)handle);
                                                                };
};
void _fenster::aktualisieren(_windowcoordinate*w0,_windowcoordinate*w1){
                                                                RECT r;
                                                                float sx,sy,vx,vy;
                                                                //--------------------
                                                                if((w0)&&(w1))
                                                                if(formal==0){
                                                                 sx=w0->getx();//clientspace[0]->o[0];
                                                                 sy=w0->gety();//clientspace[0]->o[1];
                                                                 vx=w1->getx();
                                                                 vy=w1->gety();
                                                                 r.left=sx;
                                                                 r.right=vx;
                                                                 r.top=sy;
                                                                 r.bottom=vy;
                                                                 InvalidateRect((HWND)handle,&r,TRUE);
                                                                 UpdateWindow((HWND)handle);
                                                                };
};
void _fenster::initdc(){
                                                                hdc=(int)GetDC((HWND)handle);
                                                                if(hdc==0) schreiben("Couldn't initialize graphic device context for window.");
                                                                SetBkColor((HDC)hdc,RGB(128,128,128));
};
void _fenster::exitdc(){
                                                                ReleaseDC((HWND)handle,(HDC)hdc);
};
void _fenster::foreground(){
                                                                SetForegroundWindow((HWND)handle);
};
void _fenster::schreiben(char*t){
                                                                MessageBox((HWND)(handle),(LPCSTR)t,(LPCSTR)titel,MB_OK);
};
char _fenster::casebox(char*t,char*c,char*,char*){
                                                                if(IDYES==MessageBox((HWND)(handle),(LPCSTR)c,t,MB_YESNO|MB_ICONWARNING)) return(1); else return(0);
};
char _fenster::casebox(char*c){
                                                                if(IDYES==MessageBox((HWND)(handle),(LPCSTR)c,(LPCSTR)titel,MB_YESNO|MB_ICONWARNING)) return(1); else return(0);
};
char _fenster::casebox(char*t,char*c){
                                                                if(IDYES==MessageBox((HWND)(handle),(LPCSTR)c,(LPCSTR)t,MB_YESNO|MB_ICONWARNING)) return(1); else return(0);
};
char _fenster::filebox(char*&t,_zeichenkette*extdes,_zeichenkette*ext){
                                                                char r;
                                                                OPENFILENAME o;
                                                                char dir[256];
                                                                char olddir[256];
                                                                char extensions[2560];
                                                                _zeichenkette*dit;
                                                                _zeichenkette*eit;
                                                                int cnt1,cnt2;
                                                                char temp[1024];
                                                                //-------------
                                                                cnt2=0;
                                                                strcpy(extensions,"");
                                                                eit=ext;
                                                                dit=extdes;
                                                                if(dit)do{


                                                                 cnt1=0;

                                                                 while(dit->name[cnt1]!='\0') extensions[cnt2++]=dit->name[cnt1++];
                                                                 extensions[cnt2++]='\0';
                                                                 //G->fim->schreiben("dit=",dit->name);
                                                                 cnt1=0;
                                                                 while(eit->name[cnt1]!='\0') extensions[cnt2++]=eit->name[cnt1++];
                                                                 extensions[cnt2++]='\0';
                                                                 //G->fim->schreiben("eit=",eit->name);


                                                                 eit=eit->naechstes;
                                                                 dit=dit->naechstes;
                                                                }while(dit!=extdes);
                                                                 extensions[cnt2++]='\0';
                                                                 extensions[cnt2++]='\0';
                                                             //    char szFilter[] = "Text Files (*.TXT)\0*.txt\0ASCII Files (*.ASC)\0*.asc\0All Files (*.*)\0*.*\0\0";
                                                               // strcpy(extensions,"Alle Dateien   ");
                                                               // strcat(extensions,"\0");
                                                               // strcat(extensions,"*.*");

                                                                strcpy(temp,t);
                                                              //  t=new char[1024];
                                                                //strcpy(t,"thfghgfh");
                                                                GetCurrentDirectory(sizeof(dir), dir);
                                                                strcpy(olddir,dir);
                                                                r=0;
                                                                o.lStructSize=sizeof(OPENFILENAME);
                                                                o.hwndOwner=(HWND)handle;
                                                                o.hInstance=(HINSTANCE)G->wim->hinstance;
                                                                o.lpstrFilter=extensions;
                                                                o.lpstrCustomFilter=0;
                                                                o.nMaxCustFilter=0;
                                                                o.nFilterIndex=0;
                                                                o.lpstrFile=temp;
                                                                o.nMaxFile=1024;
                                                                o.lpstrFileTitle=0;
                                                                o.nMaxFileTitle=0;
                                                                o.lpstrInitialDir=dir;
                                                                o.lpstrTitle="Choose a datei";
                                                                o.Flags= OFN_SHOWHELP | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
                                                                o.nFileOffset=0;
                                                                o.nFileExtension=0;
                                                                o.lpstrDefExt=0;
                                                                o.lCustData=0;
                                                                o.lpfnHook=0;
                                                                o.lpTemplateName=0;
                                                                r=GetOpenFileName(&o);
                                                                //schreiben(dir);
                                                                G->stm->setzen(temp,t);
                                                                SetCurrentDirectory(olddir);
                                                                return(r);
}; */
/*
void _fenster::zeichnen(){
                                                                _windowdrawable*wit;
                                                                //--------------
                                                                if(ldrawables.anfang(wit))do{
                                                                 wit->zeichnen();
                                                                }while(ldrawables.naechstes(wit));
};
_basis::_liste<_windowdrawable>* _fenster::drawentries(){
								return(&ldrawables);
};
*/
/*
void _fenster::drawpixel(float x,float y,float r,float g,float b){
                                                                SetPixel((HDC)hdc,x,y,RGB(char(r*255),char(g*255),char(b*255)));
};
void _fenster::drawline(float x0,float y0,float x1,float y1,float r,float g,float b){
                                                                HPEN curpen=CreatePen(PS_SOLID,0,RGB(char(r*255),char(g*255),char(b*255)));
                                                                HPEN old=SelectObject((HDC)hdc, curpen);
                                                                MoveToEx((HDC)hdc,x0,y0,NULL);
                                                                LineTo((HDC)hdc,x1,y1);
                                                                SelectObject((HDC)hdc,old);
                                                                DeleteObject(curpen);
};
void _fenster::drawrect(float x0,float y0,float x1,float y1,float r,float g,float b){
                                                                char cr,cg,cb;
                                                                HDC dc;
                                                                POINT p[2];
                                                                //---------------
                                                                dc=(HDC)hdc;
                                                                cr=char(r*255);
                                                                cg=char(g*255);
                                                                cb=char(b*255);
                                                                HPEN curpen = CreatePen(PS_SOLID, 0, RGB(cr,cg,cb));
                                                                HPEN old=SelectObject(dc, curpen);
                                                                HBRUSH fillbrush = CreateSolidBrush(RGB(cr,cg,cb));

                                                                HBRUSH hold=SelectObject(dc, fillbrush);
                                                                p[0].x=x0;
                                                                p[0].y=y0;
                                                                p[1].x=x1;
                                                                p[1].y=y1;
                                                                LPtoDP(dc, p, 2);
                                                                Rectangle(dc,p[0].x,p[0].y,p[1].x,p[1].y);
                                                                SelectObject(dc,old);
                                                                DeleteObject(curpen);

                                                                SelectObject(dc,hold);
                                                                DeleteObject(fillbrush);
};
void _fenster::drawbitmap(float,float,float,float){

};
void _fenster::drawtext(char*t,float x0,float y0, float rf,float gf,float bf,float rb,float gb,float bb,char tr){
                                                                SetTextColor((HDC)hdc,RGB(char(rf*255),char(gf*255),char(bf*255)));
                                                                SetBkColor((HDC)hdc,RGB(char(rb*255),char(gb*255),char(bb*255)));
                                                                if(tr) SetBkMode((HDC)hdc,TRANSPARENT); else SetBkMode((HDC)hdc,OPAQUE);
                                                                TextOut((HDC)hdc,x0,y0, t, strlen(t));
};
void _fenster::tile(float x0,float y0,float x1,float y1,_vektor<float>*c,int w){
                                                                tile(x0,y0,x1,y1,c,w,0);
};
void _fenster::tile(float x0,float y0,float x1,float y1,_vektor<float>*c,int w,_liste<_windowline>*linelist){
                                                                int i,j;
                                                                float fac;
                                                                _vektor<float>*a=new _vektor<float>(x1-x0,y1-y0);
                                                                _vektor<float>*b=new _vektor<float>(0,0);
                                                                _vektor<float>*lc=new _vektor<float>(0,0,0);
                                                                _windowline*wl;
                                                                float dir;
                                                                //-------------------
                                                                G->va2f->berechnenorthogonalenvektor(a,b);
                                                                b->normalisieren();
                                                                if(b->o[0]>b->o[1]){
                                                                 if(b->o[0]>0) dir=-1; else dir=+1;
                                                                }else{
                                                                 if(b->o[1]>0) dir=-1; else dir=+1;
                                                                };

                                                                for(i=-w;i<=w;i++){
                                                                 if((i)<=0){
                                                                  fac=float(i)/float(w);
                                                                  lc->kopieren(c);
                                                                  lc->mul(1+fac);
                                                                 }else{
                                                                  fac=float(i)/float(w);
                                                                  lc->o[0]=c->o[0]+(1-c->o[0])*fac;
                                                                  lc->o[1]=c->o[1]+(1-c->o[1])*fac;
                                                                  lc->o[2]=c->o[2]+(1-c->o[2])*fac;
                                                                 };
                                                                 for(j=0;j<3;j++) lc->o[j]=1-lc->o[j];
                                                                 wl=new _windowline(this,x0,y0,x1,y1,lc);
                                                                 if(linelist)linelist->einhaengen(wl);
                                                                 wl->addvector(0,b->o[0]*i*dir,b->o[1]*i*dir,0,0);
                                                                 wl->addvector(1,b->o[0]*i*dir,b->o[1]*i*dir,0,0);

                                                                };




                                                                loeschen(a);
                                                                loeschen(b);
};
void _fenster::tile(float x0,float y0,float x1,float y1,float x2,float y2,float x3,float y3,char dx2,char dy2,char dx3,char dy3,_vektor<float>*c,int w){
                                                                tile(x0,y0,x1,y1,x2,y2,x3,y3,dx2,dy2,dx3,dy3,c,w,0);
};
void _fenster::tile(float x0,float y0,float x1,float y1,float x2,float y2,float x3,float y3,char dx2,char dy2,char dx3,char dy3,_vektor<float>*c,int w,_liste<_windowline>*linelist){
                                                                int i,j;
                                                                float fac;
                                                                _vektor<float>*a=new _vektor<float>(x1-x0,y1-y0);
                                                                _vektor<float>*b=new _vektor<float>(0,0);
                                                                _vektor<float>*lc=new _vektor<float>(0,0,0);
                                                                _windowline*wl;
                                                                float dir;
                                                                //-------------------
                                                                //tiler erhält noch zusätz
                                                                G->va2f->berechnenorthogonalenvektor(a,b);
                                                                b->normalisieren();
                                                                if(b->o[0]>b->o[1]){
                                                                 if(b->o[0]>0) dir=-1; else dir=+1;
                                                                }else{
                                                                 if(b->o[1]>0) dir=-1; else dir=+1;
                                                                };

                                                                for(i=-w;i<=w;i++){
                                                                 if((i)<=0){
                                                                  fac=float(i)/float(w);
                                                                  lc->kopieren(c);
                                                                  lc->mul(1+fac);
                                                                 }else{
                                                                  fac=float(i)/float(w);
                                                                  lc->o[0]=(c->o[0]+(1-c->o[0])*fac);
                                                                  lc->o[1]=(c->o[1]+(1-c->o[1])*fac);
                                                                  lc->o[2]=(c->o[2]+(1-c->o[2])*fac);
                                                                 };

                                                                 for(j=0;j<3;j++) lc->o[j]=1-lc->o[j];
                                                                 wl=new _windowline(this,x0,y0,x1,y1,lc);
                                                                 if(linelist)linelist->einhaengen(wl);
                                                                 wl->addvector(0,x2,y2,dx2,dy2);
                                                                 wl->addvector(1,x3,y3,dx3,dy3);
                                                                 wl->addvector(0,b->o[0]*i*dir,b->o[1]*i*dir,0,0);
                                                                 wl->addvector(1,b->o[0]*i*dir,b->o[1]*i*dir,0,0);

                                                                };




                                                                loeschen(a);
                                                                loeschen(b);
};    */
//*****************************************************************************************************************************************************************************************************
//							        W I N D O W S I N G L E
//*****************************************************************************************************************************************************************************************************
/*
_fenstereinzel::_fenstereinzel(_zeichenkette t,double x,double y,double w,double h):ltitle(t){
								farbe(W->standardcolor());
                                                                ort(0)->setzen(x,y);
                                                                ort(1)->setzen(x+w,y+h);
};
_fenstereinzel::_fenstereinzel(_zeichenkette t,double x,double y,double w,double h,double r,double g,double b):ltitle(t){
								farbe(r,g,b);
                                                                ort(0)->setzen(x,y);
                                                                ort(1)->setzen(x+w,y+h);
};
_fenstereinzel::_fenstereinzel(_zeichenkette t,double x,double y,double w,double h,_vektor<double>&col):ltitle(t){
								farbe(col);
                                                                ort(0)->setzen(x,y);
                                                                ort(1)->setzen(x+w,y+h);
};
_fenstereinzel::_fenstereinzel(_fenster*wi,_zeichenkette t,double x,double y,double w,double h,_vektor<double>&col):_fenster(wi),ltitle(t){
								farbe(col);
                                                                ort(0)->setzen(x,y);
                                                                ort(1)->setzen(x+w,y+h);
};
_zeichenkette& _fenstereinzel::titel(){
								return(ltitle);
};
void _fenstereinzel::titel(_zeichenkette&t){
								ltitle=t;
};
*/
//*****************************************************************************************************************************************************************************************************
//							        W I N D O W M U L T I
//*****************************************************************************************************************************************************************************************************





