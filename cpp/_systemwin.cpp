//grundplatte : systemwindows.cpp
#include <_systemwin.hpp>
#ifdef GRUNDPLATTE_UNTER_WINDOWS
#include <windows.h>
#include <mmsystem.h> //timegettime
#include <commctrl.h>

namespace _win{
 //******************************************************************************************************************************************************************************************************
 //                                                              W I N   : :   S Y S T E M 
 //******************************************************************************************************************************************************************************************************
 _system::_system(HINSTANCE hi){
                                                                //WNDCLASSA wndclass;
                                                                //RECT r;
                                                                //--------------
                                                                //InitCommonControls();
                                                                hinstance=hi;
                                                                /*wndclass.style=0;//CS_GLOBALCLASS|CS_BYTEALIGNWINDOW|CS_BYTEALIGNCLIENT;
                                                                wndclass.lpfnWndProc=prozess;
                                                                wndclass.cbClsExtra=0;
                                                                wndclass.cbWndExtra=sizeof(LONG);
                                                                wndclass.hInstance=hi;
                                                                wndclass.hIcon=0;//LoadIcon(hi,MAKEINTRESOURCE(APPICON));
                                                                wndclass.hCursor=0;//LoadCursor(NULL,IDC_CROSS);
                                                                wndclass.hbrBackground=0;
                                                                wndclass.lpszMenuName=0;
                                                                wndclass.lpszClassName="winsystemclass";
                                                                RegisterClassA(&wndclass);
                                                                //SystemParametersInfo(SPI_GETWORKAREA,0,&r,0);
                                                                handle=CreateWindowA("winsystemclass","_win::_system",0,0,0,100,100,NULL,NULL,hi,NULL);
                                                                SetFocus(handle);
                                                                ShowWindow(handle,SW_HIDE);*/
 };
 _system::~_system(){
//                                                                DestroyWindow(handle);
 };
 LRESULT PASCAL _system::prozess(HWND hw,UINT m,WPARAM w,LPARAM l){
                                                                //switch(m){
                                                                // default:
                                                                 return(DefWindowProc(hw,m,w,l));                                                                        
                                                                //};
                                                                //return(0L);
 };
 void _system::animieren(){
                                                                MSG m;
                                                              //  ::_tastatur*kit;
                                                                //_pclautsprecher ss;
                                                                //----------------
                                                                while(PeekMessage(&m,NULL,0,0,PM_NOREMOVE)){
                                                                 if(GetMessage(&m,NULL,0,0)){
                                                                  TranslateMessage(&m);
                                                                /*  switch(m.schreiben){
                                                                    case WM_CHAR:
                                                                     break;
                                                                    case WM_KEYDOWN:
                                                                     if(anfang(kit))do{
                                                                      //ss.peep(10);
                                                                      kit->taste(m.wParam,true);
                                                                     }while(naechstes(kit));
                                                                     break;
                                                                    case WM_KEYUP:
                                                                     if(anfang(kit))do{
                                                                      kit->taste(m.wParam,false);
                                                                     }while(naechstes(kit));
                                                                     break;
                                                                    case WM_MOUSEMOVE:
                                                                     break;
                                                                   };*/
                                                                   DispatchMessage(&m);
                                                                 };
                                                                };
 };
 //*********************************************************************************************************************************************************************************
 //                                                              T I M E
 //*********************************************************************************************************************************************************************************
 unsigned int _zeit::system(){
                                                                return(timeGetTime());
 };
 //*********************************************************************************************************************************************************************************
 //                                                              D A T E 
 //*********************************************************************************************************************************************************************************
 void _datum::anfang(){
                                                                
 };
 //*********************************************************************************************************************************************************************************
 //                                                              S P E A K E R
 //*********************************************************************************************************************************************************************************
 void _pclautsprecher::peep(int i){
                                                                int n;
                                                                //--------
                                                                for(n=0;n<i;n++) MessageBeep(0xffffffff);
 };
 void _pclautsprecher::peep(int i,int j){
                                                                _zeit t;
                                                                int n;
                                                                //------
                                                                for(n=0;n<i;n++){
                                                                 MessageBeep(0xffffffff);
                                                                 t.delay(j);
                                                                };
 
 
 };
 //******************************************************************************************************************************************************************************************************
 //                                                              K E Y B O A R D 
 //******************************************************************************************************************************************************************************************************
 _tastatur::_tastatur(){
                                                                //a=SHORT(1)<<((sizeof(SHORT)*SHORT(8))-SHORT(1));
                                                                
 };
 bool _tastatur::taste(const unsigned int i)const{
                                                                SHORT s;
                                                                if(i<256){
                                                                 s=GetAsyncKeyState(i)&0x8000;
                                                                 if(s!=0) return(true); else return(false);
                                                                }else{
                                                                 return(false);
                                                                };
															    
 };
 short _tastatur::status(){
                                                                return(0);
 
 };
 void _tastatur::ladenfeld(char*feld){
																GetKeyboardState((PBYTE)feld);
																/*
                                                                for(int i=0;i<256;i++){
																 if(GetAsyncKeyState(i)&a) {
															      feld[i]=true;
																 }else{
															      feld[i]=false;
																 };

                                                                };
																*/
 };
 bool _tastatur::taste()const{
                                                                //BYTE vk[256];
                                                                for(int i=0;i<256;i++){
																 if(GetAsyncKeyState(i)&0x8000) {
																  return(true);
																 };
                                                                };
                                                                return(false);
 };

 bool _tastatur::leertaste()const{
                                                                if((GetAsyncKeyState(VK_SPACE)&0x8000)!=0) return(true); else return(false);
 };
 bool _tastatur::enter()const{
                                                                if((GetAsyncKeyState(VK_RETURN)&0x8000)!=0) return(true); else return(false);
 };
 bool _tastatur::escape()const{
                                                                if((GetAsyncKeyState(VK_ESCAPE)&0x8000)!=0) return(true); else return(false);
 };
 bool _tastatur::backspace()const{
                                                                if((GetAsyncKeyState(VK_BACK)&0x8000)!=0) return(true); else return(false);
 };
 bool _tastatur::shift()const{
                                                                if((GetAsyncKeyState(VK_SHIFT)&0x8000)!=0) return(true); else return(false);
 };
 bool _tastatur::control()const{
                                                                if((GetAsyncKeyState(VK_CONTROL)&0x8000)!=0) return(true); else return(false);
 };
 bool _tastatur::tab()const{
                                                                if((GetAsyncKeyState(VK_TAB)&0x8000)!=0) return(true); else return(false);
 };
 bool _tastatur::pfeillinks()const{
                                                                if((GetAsyncKeyState(VK_LEFT)&0x8000)!=0) return(true); else return(false);
 };
 bool _tastatur::pfeilrechts()const{
                                                                if((GetAsyncKeyState(VK_RIGHT)&0x8000)!=0) return(true); else return(false);
 };
 bool _tastatur::pfeilhoch()const{
                                                                if((GetAsyncKeyState(VK_UP)&0x8000)!=0) return(true); else return(false);
 };
 bool _tastatur::pfeilrunter()const{
                                                                if((GetAsyncKeyState(VK_DOWN)&0x8000)!=0) return(true); else return(false);
 };
 bool _tastatur::knopflinks()const{
                                                                if((GetAsyncKeyState(VK_LBUTTON)&0x8000)!=0) return(true); else return(false);
 };
 bool _tastatur::knopfrechts()const{
                                                                if((GetAsyncKeyState(VK_RBUTTON)&0x8000)!=0) return(true); else return(false);
 };
 bool _tastatur::knopfmitte()const{
                                                                if((GetAsyncKeyState(VK_MBUTTON)&0x8000)!=0) return(true); else return(false);
 };

};


#endif
