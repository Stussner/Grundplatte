//******************************************************************************************************************************************************************************************************
//  Projekt      : grundplatte
//  Bibliothek   : grafikopengl.cpp
//  Modul        : grafikopengl
//  Datum        : 15.02.2005
//  Beschreibung : 
//******************************************************************************************************************************************************************************************************
#include <_grafikopengl.hpp>
PFNGLMULTITEXCOORD2FARBPROC		glMultiTexCoord2fARB = 0;
PFNGLACTIVETEXTUREARBPROC		  glActiveTextureARB = 0;
PFNWGLSWAPINTERVALEXTPROC  wglSwapInterval=0;



/*


HFONT          font;                                                  // Windows Font ID 
      HFONT          oldfont;                                             // Used For Good House Keeping 
   TEXTMETRIC  tm; 
 
 
       fontListBase[num] = glGenLists(224);                                // Storage For 224 Characters 
 
   int h = int((float)-height * 96.0f / 72.0f - 0.5f); // <- Version für große Schriftarten; -0.5f für korrektes Runden der Zahl 
   //int h = -MulDiv(height, GetDeviceCaps(hDC, LOGPIXELSY), 72);   
   if(NULL == (font = CreateFont(h,                   // Height Of Font 
                                                   0,                                        // Width Of Font 
                                                   0,                                        // Angle Of Escapement 
                                                   0,                                        // Orientation Angle 
                                                   weight,                              // Font Weight 
                                                   FALSE,                                   // Italic 
                                                   FALSE,                                   // Underline 
                                                   FALSE,                                   // Strikeout 
                                                   DEFAULT_CHARSET,                         // Character Set Identifier 
                                                   OUT_TT_PRECIS,                         // Output Precision 
                                                   CLIP_DEFAULT_PRECIS,               // Clipping Precision 
                                                   ANTIALIASED_QUALITY,               // Output Quality 
                                                   FF_DONTCARE | DEFAULT_PITCH,          // Family And Pitch 
                                                   name)))                         // Font Name 
     { 
        return(FALSE); 
     } 
 
   oldfont = (HFONT)SelectObject(hDC, font);           // Selects The Font We Want 
 
   GetTextMetrics(hDC, &tm);  // Abfrage der Schrift 
 
   fontHeight[num]  = tm.tmHeight - (tm.tmHeight / 3); 
   cxChar[num]      = tm.tmAveCharWidth;  // durchschnittliche Breite 
   cyChar[num]      = tm.tmHeight + tm.tmExternalLeading;  //  Höhe plus Abstand 
   cxCaps[num]      = ((tm.tmPitchAndFamily & 1 ? 3 : 2) * cxChar[num]) >> 1; 
   biggestChar[num] = GetBiggestChar(hDC); 
 
   wglUseFontBitmaps(hDC, 32, 224, fontListBase[num]);               // Builds 224 Characters Starting At Character 32 
 
      SelectObject(hDC, oldfont);                                   // Selects The Font We Want 
      DeleteObject(font);
Out of Sync (07:11 PM) : 
fontListBase[num] = glGenLists(224);                                // Storage For 224 Characters   <-- das hier ist eine unsigned int (wie textur-id)
Out of Sync (07:11 PM) : 
glDeleteLists(fontListBase[num], 224);      // delete font


*/



//*************************************************************************************************************************************************************************
//                                                              W I N  :: G R A F I K O P E N G L 
//*************************************************************************************************************************************************************************
 //vollbildmodus, nutzung interner hdc,hwmd,hrc, die grafik hat fensterkontrolle (groesse und position)
 _grafikopengl::_grafikopengl(): ::_grafik(true,0,0,1024,768,16,60){
                                                                GLuint  PixelFormat;
                                                                unsigned int wx;
                                                                unsigned int wy;
                                                                static  PIXELFORMATDESCRIPTOR pfd={
                                                                sizeof(PIXELFORMATDESCRIPTOR),          // Size Of This Pixel Format Descriptor
                                                                1,                                      // Version Number (?)
                                                                PFD_DRAW_TO_WINDOW |                    // Format Must Support Window
                                                                PFD_SUPPORT_OPENGL |                    // Format Must Support OpenGL
                                                                PFD_DOUBLEBUFFER,                       // Must Support Double Buffering
                                                                PFD_TYPE_RGBA,                          // Request An RGBA Format
                                                                16,                                     // Select A 16Bit Color Depth
                                                                0, 0, 0, 0, 0, 0,                       // Color Bits Ignored (?)
                                                                0,                                      // No Alpha Buffer
                                                                0,                                      // Shift Bit Ignored (?)
                                                                0,                                      // No Accumulation Buffer
                                                                0, 0, 0, 0,                             // Accumulation Bits Ignored (?)
                                                                24,                                     // 16Bit Z-Buffer (Depth Buffer)  
                                                                8,                                      // 8bit Stencil Buffer
                                                                0,                                      // No Auxiliary Buffer (?)
                                                                PFD_MAIN_PLANE,                         // Main Drawing Layer
                                                                0,                                      // Reserved (?)
                                                                0, 0, 0                                 // Layer Masks Ignored (?)
                                                                };
                                                                WNDCLASSA wndclass;
                                                                LOGBRUSH brush;
                                                                RECT r;
                                                                //----------------------------------
                                                                upperleft();
                                                                brush.lbStyle   = BS_SOLID;
                                                                brush.lbColor   = RGB(0,0,0);  
                                                                brush.lbHatch   = HS_VERTICAL;
                                                                wndclass.style=CS_OWNDC|CS_BYTEALIGNWINDOW|CS_BYTEALIGNCLIENT;
                                                                wndclass.lpfnWndProc=prozess;
                                                                wndclass.cbClsExtra=0;
                                                                wndclass.cbWndExtra=sizeof(LONG);
                                                                wndclass.hInstance=0;
                                                                wndclass.hIcon=0;//LoadIcon(hi,MAKEINTRESOURCE(APPICON));
                                                                wndclass.hCursor=0;//LoadCursor(NULL,IDC_CROSS);
                                                                wndclass.hbrBackground=(HBRUSH) CreateBrushIndirect(&brush);
                                                                wndclass.lpszMenuName=0;
                                                                wndclass.lpszClassName="wingraphicopenglclass";
                                                                RegisterClassA(&wndclass); 
                                                                SystemParametersInfo(SPI_GETWORKAREA,0,&r,0);
                                                                wx=abs(r.right-r.left);
                                                                wy=abs(r.top-r.bottom)+32;
                                                                handle=CreateWindowA("wingraphicopenglclass","_grafikopengl",WS_EX_TOPMOST|WS_VISIBLE|WS_POPUP,0,0,wx,wy,NULL,NULL,NULL,NULL);
                                                                kontext((unsigned int(GetDC(handle))));
                                                                PixelFormat = ChoosePixelFormat(HDC(kontext()), &pfd);
                                                                if (!PixelFormat){
                                                                 MessageBoxA(0,"Can't Find A Suitable PixelFormat.","Error",MB_OK|MB_ICONERROR);
                                                                 PostQuitMessage(0);                             // This Sends A 'Message' Telling The Program To Quit
                                                                } else
                                                                if(!SetPixelFormat((HDC)kontext(),PixelFormat,&pfd)){
                                                                 MessageBoxA(0,"Can't Set The PixelFormat.","Error",MB_OK|MB_ICONERROR);
                                                                 PostQuitMessage(0);
                                                                } else {
                                                                 hrc = wglCreateContext((HDC)kontext());
                                                                 if(!hrc){
                                                                  MessageBoxA(0,"Can't Create A GL Rendering Context.","Error",MB_OK|MB_ICONERROR);
                                                                  PostQuitMessage(0);
                                                                 } else 
                                                                 if(!wglMakeCurrent((HDC)kontext(), hrc)){
                                                                  MessageBoxA(0,"Can't activate GLRC.","Error",MB_OK|MB_ICONERROR);
                                                                  PostQuitMessage(0);
                                                                 }else {
                                                                  SetWindowPos(handle,HWND_TOPMOST,0,0,wx,wy,SWP_SHOWWINDOW);
                                                                  groesse(wx,wy);
                                                                  position(0,0);
                                                                  ShowWindow(handle,SW_SHOWNORMAL);
                                                                 // SetForegroundWindow(handle);
                                                                  glViewport(0,0,wx,wy);                                           // Reset The Current Viewport
                                                                  gluPerspective(85.0f,(GLfloat)wx/(GLfloat)wy,0.01f,10000.0f);
                                                                  glShadeModel(GL_SMOOTH);                                                        // Enable Smooth Shading
                                                                  glClearColor(0.0f, 0.0f, 0.0f, 1);                           // Black Background
                                                                  glDisable(GL_DEPTH_TEST);                                                        // Enables Depth Testing
                                                                  glDepthFunc(GL_LEQUAL);                                                         // The Type Of Depth Testing To Do
                                                                  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);      // Really Nice Perspective Calculations
                                                                  glEnable(GL_TEXTURE_2D);
                                                                  ptextur=true;
                                                                  glDisable(GL_BLEND);
                                                                  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
                                                                  //glDepthRange(0,1);
                                                                  glAlphaFunc(GL_GREATER,0.1f);
                                                                  glDisable(GL_ALPHA_TEST);
                                                                  glStencilMask(~0);
                                                                  glEnable(GL_CULL_FACE);
                                                                  int tu;
                                                                  glGetIntegerv(GL_MAX_TEXTURE_UNITS, &tu);
                                                                  L->schreiben("Grafik Opengl : TexturEinheitenanzahl = ",tu);
                                                                  const char*extensions;
                                                                  extensions=(const char*)glGetString(GL_EXTENSIONS);
                                                                  _zeichenkette<char> h(extensions);
                                                                  L->schreiben("Grafik Opengl Extensions : ",h);
                                                             
                                                                  allebufferloeschen();
                                                                  anzeigebufferumschalten(false);
                                                                  allebufferloeschen();
                                                                  anzeigebufferumschalten(false);
                                                                  glMultiTexCoord2fARB = (PFNGLMULTITEXCOORD2FARBPROC) wglGetProcAddress("glMultiTexCoord2fARB");
                                                                  glActiveTextureARB   = (PFNGLACTIVETEXTUREARBPROC)   wglGetProcAddress("glActiveTextureARB");
                                                                   //L->schreiben("funktionswert multi = ",(int)glMultiTexCoord2fARB);
                                                                  //erzeugenschattenbild();
                                                                 };
                                                                };
                                                              //  hatkontrolle=true;
                                                                wglSwapInterval = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");
                                                                wglSwapInterval ( 1 );  // mit sync
                                                                paltebindung=0;
 };
 //fenstermodus,  nutzung interner hdc,hwnd,hrc, die grafik hat fensterkontrolle (groesse und position)
 _grafikopengl::_grafikopengl(unsigned int x,unsigned int y,unsigned int wx,unsigned int wy): ::_grafik(false,x,y,wx,wy,16,60){
                                                                GLuint  PixelFormat;
                                                                static  PIXELFORMATDESCRIPTOR pfd={
                                                                sizeof(PIXELFORMATDESCRIPTOR),          // Size Of This Pixel Format Descriptor
                                                                1,                                      // Version Number (?)
                                                                PFD_DRAW_TO_WINDOW |                    // Format Must Support Window
                                                                PFD_SUPPORT_OPENGL |                    // Format Must Support OpenGL
                                                                PFD_DOUBLEBUFFER,                       // Must Support Double Buffering
                                                                PFD_TYPE_RGBA,                          // Request An RGBA Format
                                                                16,                                     // Select A 16Bit Color Depth
                                                                0, 0, 0, 0, 0, 0,                       // Color Bits Ignored (?)
                                                                0,                                      // No Alpha Buffer
                                                                0,                                      // Shift Bit Ignored (?)
                                                                0,                                      // No Accumulation Buffer
                                                                0, 0, 0, 0,                             // Accumulation Bits Ignored (?)
                                                                24,                                     // 16Bit Z-Buffer (Depth Buffer)  
                                                                8,                                      // 8bit Stencil Buffer
                                                                0,                                      // No Auxiliary Buffer (?)
                                                                PFD_MAIN_PLANE,                         // Main Drawing Layer
                                                                0,                                      // Reserved (?)
                                                                0, 0, 0                                 // Layer Masks Ignored (?)
                                                                };
                                                                WNDCLASSA wndclass;
                                                                LOGBRUSH brush;
                                                                //----------------------------------
                                                                brush.lbStyle   = BS_SOLID;
                                                                brush.lbColor   = RGB(0,0,0);
                                                                brush.lbHatch   = HS_VERTICAL;
                                                                wndclass.style=CS_OWNDC|CS_BYTEALIGNWINDOW|CS_BYTEALIGNCLIENT;
                                                                wndclass.lpfnWndProc=prozess;
                                                                wndclass.cbClsExtra=0;
                                                                wndclass.cbWndExtra=sizeof(LONG);
                                                                wndclass.hInstance=0;
                                                                wndclass.hIcon=0;//LoadIcon(hi,MAKEINTRESOURCE(APPICON));
                                                                wndclass.hCursor=0;//LoadCursor(NULL,IDC_CROSS);
                                                                wndclass.hbrBackground=(HBRUSH) CreateBrushIndirect(&brush);
                                                                wndclass.lpszMenuName=0;
                                                                wndclass.lpszClassName="wingraphicopenglclass";
                                                                RegisterClassA(&wndclass);
                                                                handle=CreateWindowA("wingraphicopenglclass","_grafikopengl",WS_VISIBLE|WS_POPUP,0,0,wx,wy,NULL,NULL,NULL,NULL);
                                                                kontext((unsigned int)GetDC(handle));
                                                                upperleft();
                                                                PixelFormat = ChoosePixelFormat((HDC)kontext(), &pfd);
                                                                if (!PixelFormat){
                                                                 MessageBoxA(0,"Can't Find A Suitable PixelFormat.","Error",MB_OK|MB_ICONERROR);
                                                                 PostQuitMessage(0);                             // This Sends A 'Message' Telling The Program To Quit
                                                                } else
                                                                if(!SetPixelFormat((HDC)kontext(),PixelFormat,&pfd)){
                                                                 MessageBoxA(0,"Can't Set The PixelFormat.","Error",MB_OK|MB_ICONERROR);
                                                                 PostQuitMessage(0);
                                                                } else {
                                                                 hrc = wglCreateContext((HDC)kontext());
                                                                 if(!hrc){
                                                                  MessageBoxA(0,"Can't Create A GL Rendering Context.","Error",MB_OK|MB_ICONERROR);
                                                                  PostQuitMessage(0);
                                                                 } else 
                                                                 if(!wglMakeCurrent((HDC)kontext(), hrc)){
                                                                  MessageBoxA(0,"Can't activate GLRC.","Error",MB_OK|MB_ICONERROR);
                                                                  PostQuitMessage(0);
                                                                 }else{
                                                                  SetWindowPos(handle,0/*HWND_TOPMOST*/,(int)x,(int)y,wx,wy,SWP_SHOWWINDOW);
                                                                  groesse(wx,wy);
                                                                  position(x,y);
                                                                  ShowWindow(handle,SW_SHOWNORMAL);
                                                                //  SetForegroundWindow(handle);
                                                                  aktivitaet(true);
                                                                  glViewport(0,0,wx,wy);                                           // Reset The Current Viewport
                                                                  gluPerspective(45.0f,(GLfloat)wx/(GLfloat)wy,0.01f,10000.0f);
                                                                  glShadeModel(GL_SMOOTH);                                                        // Enable Smooth Shading
                                                                  glClearColor(0, 0, 0, 1);                           // Black Background
                                                                  glEnable(GL_DEPTH_TEST);                                                        // Enables Depth Testing
                                                                  glDepthFunc(GL_LEQUAL);                                                         // The Type Of Depth Testing To Do
                                                                  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);      // Really Nice Perspective Calculations
                                                                  glEnable(GL_TEXTURE_2D);
                                                                  ptextur=true;
                                                                  glDisable(GL_BLEND);
                                                                  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
                                                                 // glDepthRange(0,1);
                                                                  glAlphaFunc(GL_GREATER,0.1f);
                                                                  glDisable(GL_ALPHA_TEST);
                                                                  glStencilMask(~0);
                                                                  glEnable(GL_CULL_FACE);
                                                                  int tu;
                                                                  glGetIntegerv(GL_MAX_TEXTURE_UNITS, &tu);
                                                                  L->schreiben("Grafik Opengl : TexturEinheitenanzahl = ",tu);
                                                                  const char*extensions;
                                                                  extensions=(const char*)glGetString(GL_EXTENSIONS);
                                                                  _zeichenkette<char> h(extensions);
                                                                  L->schreiben("Grafik Opengl Extensions : ",h);
                                                                  //Initialise extgl
                                                                  /*if(extgl_Initialize()!=0){
                                                                   L->schreiben("Grafik OpenGl : Kann extgl nicht initialisieren");
                                                                  };*/
                                                                  allebufferloeschen();
                                                                  anzeigebufferumschalten(false);
                                                                  allebufferloeschen();
                                                                  anzeigebufferumschalten(false);
                                                                  glMultiTexCoord2fARB = (PFNGLMULTITEXCOORD2FARBPROC) wglGetProcAddress("glMultiTexCoord2fARB");
                                                                  glActiveTextureARB   = (PFNGLACTIVETEXTUREARBPROC)   wglGetProcAddress("glActiveTextureARB");
                                                                  //L->schreiben("funktionswert multi = ",(int)glMultiTexCoord2fARB);
                                                                  //erzeugenschattenbild();
                                                                 };
                                                                };
                                                                //hatkontrolle=true;
                                                                wglSwapInterval = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");
                                                                wglSwapInterval ( 1 );  // mit sync      
                                                                 paltebindung=0;
                                                                                                                          
 };
//externer modus,keine nutzung interner hdc,hwnd,hrc, keine fensterkontrolle  
 _grafikopengl::_grafikopengl(unsigned int dc,unsigned int x,unsigned int y,unsigned int wx,unsigned int wy): ::_grafik(false,x,y,wx,wy,16,60){ 
                                                                kontext(dc); 
                                                                 
                                                                 
                                                                 
                                                                GLuint  PixelFormat;
                                                                static  PIXELFORMATDESCRIPTOR pfd={
                                                                sizeof(PIXELFORMATDESCRIPTOR),          // Size Of This Pixel Format Descriptor
                                                                1,                                      // Version Number (?)
                                                                PFD_DRAW_TO_WINDOW |                    // Format Must Support Window
                                                                PFD_SUPPORT_OPENGL |                    // Format Must Support OpenGL
                                                                PFD_DOUBLEBUFFER,                       // Must Support Double Buffering
                                                                PFD_TYPE_RGBA,                          // Request An RGBA Format
                                                                16,                                     // Select A 16Bit Color Depth
                                                                0, 0, 0, 0, 0, 0,                       // Color Bits Ignored (?)
                                                                0,                                      // No Alpha Buffer
                                                                0,                                      // Shift Bit Ignored (?)
                                                                0,                                      // No Accumulation Buffer
                                                                0, 0, 0, 0,                             // Accumulation Bits Ignored (?)
                                                                24,                                     // 16Bit Z-Buffer (Depth Buffer)  
                                                                8,                                      // 8bit Stencil Buffer
                                                                0,                                      // No Auxiliary Buffer (?)
                                                                PFD_MAIN_PLANE,                         // Main Drawing Layer
                                                                0,                                      // Reserved (?)
                                                                0, 0, 0                                 // Layer Masks Ignored (?)
                                                                };
                                                                //WNDCLASSA wndclass;
                                                                //LOGBRUSH brush;
                                                                 
                                                                PixelFormat = ChoosePixelFormat((HDC)kontext(), &pfd);
                                                                if (!PixelFormat){
                                                                 MessageBoxA(0,"Can't Find A Suitable PixelFormat.","Error",MB_OK|MB_ICONERROR);
                                                                 PostQuitMessage(0);                             // This Sends A 'Message' Telling The Program To Quit
                                                                } else
                                                                if(!SetPixelFormat((HDC)kontext(),PixelFormat,&pfd)){
                                                                 MessageBoxA(0,"Can't Set The PixelFormat.","Error",MB_OK|MB_ICONERROR);
                                                                 PostQuitMessage(0);
                                                                } else {
                                                                 
                                                                 
                                                                 if(!(hrc = wglCreateContext((HDC)kontext()))){ 
                                                                  MessageBoxA(0,"Can't Create A GL Rendering Context.","Error",MB_OK|MB_ICONERROR); 
                                                                  PostQuitMessage(0); 
                                                                 }else{ 
                                                                  if(!wglMakeCurrent((HDC)kontext(), hrc)){ 
                                                                   MessageBoxA(0,"Can't activate GLRC.","Error",MB_OK|MB_ICONERROR); 
                                                                   PostQuitMessage(0); 
                                                                  };
                                                                 };
                                                                };
                                                                 //hatkontrolle = false; 
                                                                 aktivitaet(true);
                                                                 glViewport(0,0,wx,wy);                                           // Reset The Current Viewport
                                                                 gluPerspective(45.0f,(GLfloat)wx/(GLfloat)wy,0.01f,10000.0f);
                                                                 glShadeModel(GL_SMOOTH);                                                        // Enable Smooth Shading
                                                                 glClearColor(0, 0, 0, 1);                           // Black Background
                                                                 glEnable(GL_DEPTH_TEST);                                                        // Enables Depth Testing
                                                                 glDepthFunc(GL_LEQUAL);                                                         // The Type Of Depth Testing To Do
                                                                 glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);      // Really Nice Perspective Calculations
                                                                 glEnable(GL_TEXTURE_2D);
                                                                  ptextur=true;
                                                                 glDisable(GL_BLEND);
                                                                 glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
                                                                // glDepthRange(0,1);
                                                                 glAlphaFunc(GL_GREATER,0.1f);
                                                                 glDisable(GL_ALPHA_TEST);
                                                                 glStencilMask(~0);
                                                                 glEnable(GL_CULL_FACE);
                                                                 int tu;
                                                                 glGetIntegerv(GL_MAX_TEXTURE_UNITS, &tu);
                                                                 L->schreiben("Grafik Opengl : TexturEinheitenanzahl = ",tu);
                                                                 const char*extensions;
                                                                 extensions=(const char*)glGetString(GL_EXTENSIONS);
                                                                 _zeichenkette<char> h(extensions);
                                                                 L->schreiben("Grafik Opengl Extensions : ",h);
                                                                 allebufferloeschen();
                                                                 anzeigebufferumschalten(false);
                                                                 allebufferloeschen();
                                                                 anzeigebufferumschalten(false);
                                                                 glMultiTexCoord2fARB = (PFNGLMULTITEXCOORD2FARBPROC) wglGetProcAddress("glMultiTexCoord2fARB");
                                                                 glActiveTextureARB   = (PFNGLACTIVETEXTUREARBPROC)   wglGetProcAddress("glActiveTextureARB");
                                                                 wglSwapInterval = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");
                                                                 wglSwapInterval ( 1 );  // mit sync
                                                                 paltebindung=0;
 };
 _grafikopengl::~_grafikopengl(){
                                                                wglMakeCurrent((HDC)kontext(),NULL);
                                                                wglDeleteContext(hrc);
                                                                //if(fensterkontrolle()){
                                                                // ReleaseDC(handle,(HDC)kontext());
                                                                 //DestroyWindow(handle);
                                                                //};
 };
 LRESULT PASCAL _grafikopengl::prozess(HWND hw,UINT m,WPARAM w,LPARAM l){
                                                                return(DefWindowProc(hw,m,w,l));                                                                        
 };
 bool _grafikopengl::validieren(){  
                                                                return(true);
 };
 void _grafikopengl::gemeinsamedaten(_grafik*g){
																_grafikopengl*go=dynamic_cast<_grafikopengl*>(g);
																if(go){
																 wglShareLists(go->hrc,hrc);//ansicht[0]->grafik->rendercontext(), ansicht[3]->grafik->rendercontext()
																};
 };
 
bool _grafikopengl::initialisieren(){
																return(true);
};
bool _grafikopengl::uninitialisieren(){
																return(true);
};
bool _grafikopengl::reinitialisieren(){
																return(true);
};
                
void _grafikopengl::vollbildwechsel(bool full){
};
bool _grafikopengl::unterstuetzttexturnichthochzwei(){
																return(false);
};
bool _grafikopengl::unterstuetzttexturrechteckig(){
																return(true);
};
void _grafikopengl::setzen(bool fullscr,unsigned int wx,unsigned int wy,unsigned int de,unsigned int ra){
};

 bool _grafikopengl::szenebeginn(){
																//glBegin();
                                                                return(true);
};
void _grafikopengl::szeneende(){
                                                                
};
 void _grafikopengl::erzeugenschattenbild(){
                                                               
                                                             
                                                                 //Create the shadow map texture
                                                                glActiveTextureARB(GL_TEXTURE3_ARB);
                                                                glGenTextures(1, &schattenbild);
                                                                glBindTexture(GL_TEXTURE_2D, schattenbild);
                                                                glTexImage2D( GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 2048, 2048, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);
                                                                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                                                                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                                                                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
                                                                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
                                                                glActiveTextureARB(GL_TEXTURE0_ARB);
 };                                                                
 void _grafikopengl::aktivitaet(const bool b){
                                                                if(b) {
                                                                 wglMakeCurrent((HDC)kontext(),hrc);
                                                                 paltebindung=0;
                                                                };
                                                                ::_grafik::aktivitaet(b);
 };
 bool _grafikopengl::aktivitaet() const{
                                                                return( ::_grafik::aktivitaet());
 };
 void _grafikopengl::groesse(unsigned int wx, unsigned int wy){
                                                               // if(fensterkontrolle()) SetWindowPos(handle,0,(int)positionx(),(int)positiony(),wx,wy,0);
                                                                ::_grafik::groesse(wx,wy);
                                                                glViewport(0,0,wx,wy);
 };

 void _grafikopengl::position(_tg x,_tg y){
                                                               // if(fensterkontrolle()) SetWindowPos(handle,0,(int)x,(int)y,groessex(),groessey(),0);
                                                                ::_grafik::position(x,y);
                                                                
 };

 HGLRC _grafikopengl::rendercontext() const{
                                                               return(hrc);
 };

 /*HDC _grafikopengl::devicecontext()const{
                                                                return(hdc);
 };*/
 //------------------------------------------------------------ Transformation ------------------------------------------------------------------------------------------------------
 void _grafikopengl::ladenmatrixprojektion(_matrix44<_tm>*m){
                                                                //pdevice->GetTransform(D3DTRANSFORMSTATE_PROJECTION,(LPD3DMATRIX)m->daten());
};
void _grafikopengl::ladenmatrixwelt(_matrix44<_tm>*m){
                                                                //pdevice->GetTransform(D3DTRANSFORMSTATE_WORLD,(LPD3DMATRIX)m->daten());
};
void _grafikopengl::ladenmatrixmodell(_matrix44<_tm>*m){
                                                                //pdevice->GetTransform(D3DTRANSFORMSTATE_VIEW,(LPD3DMATRIX)m->daten());
};
void _grafikopengl::matrixprojektion(_matrix44<_tm>*m){
                                                               // pdevice->SetTransform(D3DTRANSFORMSTATE_PROJECTION,(LPD3DMATRIX)m->daten());
};
void _grafikopengl::matrixwelt(_matrix44<_tm>*m){
                                                               //// pdevice->SetTransform(D3DTRANSFORMSTATE_WORLD,(LPD3DMATRIX)m->daten());
};
void _grafikopengl::matrixmodell(_matrix44<_tm>*m){
                                                               // pdevice->SetTransform(D3DTRANSFORMSTATE_VIEW,(LPD3DMATRIX)m->daten());
};
void _grafikopengl::orthonormal(){
                                                                orthonormal(0,groessex(),0,groessey(),-100,+100);
};
void _grafikopengl::orthonormal(const _tg x0,const _tg x1,const _tg y0,const _tg y1,const _tg z0,const _tg z1){
                                                                glMatrixMode(GL_MODELVIEW);  
                                                                glLoadIdentity();  
                                                                glMatrixMode(GL_PROJECTION);  
                                                                glLoadIdentity();   
                                                                glOrtho(x0,x1,y0,y1,z0,z1);
};
void _grafikopengl::transformierenrueck(const _vektor3<_tg>&geraet,_vektor3<_tg>&welt){
                                                                _tg umx,umy,umz;
                                                                _tg mvMatrix[16],projMatrix[16];
                                                                int viewport[4];
                                                                
                                                                glGetIntegerv(GL_VIEWPORT, viewport); 
                                                                glGetDoublev(GL_MODELVIEW_MATRIX, mvMatrix); 
                                                                glGetDoublev(GL_PROJECTION_MATRIX, projMatrix); 
                                                                gluUnProject((double)geraet[0], (double)(viewport[3] - geraet[1]), geraet[2], mvMatrix, projMatrix, viewport, &umx, &umy, &umz);  
                                                                welt.setzen(umx,umy,umz);
};              
void _grafikopengl::sichtbereich(_tg x,_tg y,_tg w,_tg h){
                                                                glViewport(x,y,w,h);
                                                                
};

 //------------------------------------------------------------ Material und Livht ------------------------------------------------------------------------------------------------------
 void _grafikopengl::licht(const unsigned int i,const bool b){  
                                                                if(i<8){
                                                                 if (b) glEnable((GL_LIGHT0)+i); else glDisable(GL_LIGHT0+i);
                                                                };
 }; 
 void _grafikopengl::beleuchtung(const bool b){
                                                                if (b) glEnable(GL_LIGHTING); else glDisable(GL_LIGHTING);
 };
 bool _grafikopengl::beleuchtung()const{
                                                                return((bool) glIsEnabled(GL_LIGHTING));
 };
 void _grafikopengl::beleuchtungflach(){
                                                                glShadeModel(GL_FLAT);
 };
 void _grafikopengl::beleuchtungrund(){
                                                                glShadeModel(GL_SMOOTH);
 };
 void _grafikopengl::material(const bool b){
                                                                if (b) glEnable(GL_COLOR_MATERIAL); else glDisable(GL_COLOR_MATERIAL);
 };
 void _grafikopengl::materialfarbe(const _vektor4<_to>&p){
                                                                float lc[4];
                                                                lc[0]=p[0];
                                                                lc[1]=p[1];
                                                                lc[2]=p[2];
                                                                lc[3]=1;
                                                                glMaterialfv(GL_FRONT,GL_DIFFUSE,lc);	 
 };

 void _grafikopengl::materialemission(const _vektor4<_to>&p){
                                                                float lc[4];
                                                                lc[0]=p[0];
                                                                lc[1]=p[1];
                                                                lc[2]=p[2];
                                                                lc[3]=1;
                                                                glMaterialfv(GL_FRONT,GL_EMISSION,lc);                                                                
 };

 void _grafikopengl::materialglanz(const _vektor4<_to>&p){
			                                                    float lc[4];
                                                                lc[0]=p[0];
                                                                lc[1]=p[1];
                                                                lc[2]=p[2];
                                                                lc[3]=1;
                                                                glMaterialfv(GL_FRONT,GL_SPECULAR,lc);	 
 };

 void _grafikopengl::materialglanzbreite(_tg p){
                                                                glMaterialf(GL_FRONT,GL_SHININESS,(GLfloat)p);  
 };
 //------------------------------------------------------------ Texturen und Einheiten ----------------------------------------------------------------------------------------
 void _grafikopengl::textureinheit(unsigned int i){
                                                                if (i==0) glActiveTextureARB(GL_TEXTURE0_ARB); else
                                                                if (i==1) glActiveTextureARB(GL_TEXTURE1_ARB); else
                                                                if (i==2) glActiveTextureARB(GL_TEXTURE2_ARB);
 };
 void _grafikopengl::texturoperationadditiv(){
                                                                glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ADD);
 };
 void _grafikopengl::texturoperationmultiplikativ(){
                                                                glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);//GL_DECAL);
 };
 
 void _grafikopengl::textur(const bool b){
                                                                if(b!=ptextur){
                                                                 if(b){
                                                                  glEnable(GL_TEXTURE_2D); 
                                                                  ptextur=true;
                                                                 }else{
                                                                  glDisable(GL_TEXTURE_2D);
                                                                  ptextur=false;
                                                                 };
                                                                };
 };
 void _grafikopengl::erzeugentexturen(_listebasis<_textur<_tb> >*tl){
                                                                _textur<_tb>*tit;
                                                                //--------------
                                                                if(tl->anfang(tit))do{
                                                                 erzeugenbilder(tit->bitmap());
                                                                 erzeugenbilder(tit->lightmap());
                                                                 erzeugenbilder(tit->shadowmap());
                                                                 erzeugenbilder(tit->bumpmap());
                                                                 erzeugenbilder(tit->translightmap());
                                                                 erzeugenbilder(tit->detailmap());
                                                                 erzeugenbilder(tit->maskmap());
                                                                 erzeugenbilder(tit->specularmap());
                                                                }while(tl->naechstes(tit));
 };

 void _grafikopengl::erzeugenbilder(_liste<_bild<_tb> >*ml){
                                                                _listenknoten<_bild<_tb> >*mit;
                                                                //--------------
                                                                if(ml->anfang(mit))do{
                                                                 erzeugenbild(mit->objekt());
                                                                }while(ml->naechstes(mit));
 };

 void _grafikopengl::erzeugenbild(_bild<_tb>*mit){
                                                                mit->loeschenbildhardware();
                                                                mit->bildhardware(new _bildhardwareopengl(this,mit));
 };                                                                   

 void _grafikopengl::loeschentexturen(_listebasis<_textur<_tb> >*tl){
                                                                _textur<_tb>*tit;
                                                                //--------------
                                                                if(tl->anfang(tit))do{
                                                                 loeschenbilder(tit->bitmap());
                                                                 loeschenbilder(tit->lightmap());
                                                                 loeschenbilder(tit->shadowmap());
                                                                 loeschenbilder(tit->bumpmap());
                                                                 loeschenbilder(tit->translightmap());
                                                                 loeschenbilder(tit->detailmap());
                                                                 loeschenbilder(tit->maskmap());
                                                                 loeschenbilder(tit->specularmap());
                                                                }while(tl->naechstes(tit));
 };

 void _grafikopengl::loeschenbilder(_liste<_bild<_tb> >*ml){
                                                                _listenknoten<_bild<_tb> >*mit;
                                                                //--------------
                                                                if(ml->anfang(mit))do{
                                                                 loeschenbild(mit->objekt());
                                                                }while(ml->naechstes(mit));
 };

 void _grafikopengl::loeschenbild(_bild<_tb>*mit){
 
                                                                mit->loeschenbildhardware();
 };                                                                   



 void _grafikopengl::bindenbild(_bild<_tb>*m){
                                                                if(m->bildhardware()==0) m->bildhardware(new _bildhardwareopengl(this,m));
                                                                if(paltebindung!=m->bildhardware()) {
                                                                 m->bildhardware()->binden();
                                                                 //paltebildid=m->bildidentifikation();
                                                                 //glBindTexture(GL_TEXTURE_2D,paltebildid);
                                                                };
 };
 /*_zeichensatzbild*_grafikopengl::erzeugenzeichensatz(int size,int weight,_zeichenkette<char>const&name){
                                                                return(0);
 };*/
 //------------------------------------------------------------ Ausschuss --------------------------------------------------------------------------------------------------------
 void _grafikopengl::ausschussflaeche(const bool c){
                                                                if(c) glEnable(GL_CULL_FACE); else glDisable(GL_CULL_FACE);
 };
 void _grafikopengl::ausschussflaechefront(){
                                                                glCullFace(GL_FRONT);
 };
 void _grafikopengl::ausschussflaecherueck(){
                                                                glCullFace(GL_BACK);
 };
 //------------------------------------------------------------ Buffer --------------------------------------------------------------------------------------------------------
 bool _grafikopengl::allebufferloeschen(){
                                                                //glFlush();
                                                               // glClearDepth(1);
                                                               // tiefenbufferschreiben(true);
                                                                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
                                                                //glLoadIdentity();
                                                                return(true);
 };
 void _grafikopengl::anzeigebufferloeschfarbe(const _to r,const _to g,const _to b,const _to a){
                                                                glClearColor(r,g,b,a);
                                                                
 };
 void _grafikopengl::anzeigebufferumschalten(const bool sync){
                                                                glFinish();
                                                                SwapBuffers((HDC)kontext());
 };
 void _grafikopengl::anzeigebufferschreiben(const bool b){
                                                                if(b) glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE); else glColorMask(GL_FALSE,GL_FALSE,GL_FALSE,GL_FALSE);
 };                                                                
 void _grafikopengl::tiefenbufferkondition(const bool b){
                                                                if(b) glEnable(GL_DEPTH_TEST); else glDisable(GL_DEPTH_TEST);
 };
 void _grafikopengl::tiefenbufferschreiben(const bool b){
                                                                if(b) glDepthMask(GL_TRUE); else glDepthMask(GL_FALSE);
 };
 void _grafikopengl::tiefenbufferkonditiongleich(){
                                                                glDepthFunc(GL_EQUAL);
 };
 void _grafikopengl::tiefenbufferkonditionkleiner(){
                                                                glDepthFunc(GL_LESS);
 }; 
 void _grafikopengl::tiefenbufferkonditionkleinergleich(){
                                                                glDepthFunc(GL_LEQUAL);
 };
 
 
 void _grafikopengl::schablonenbufferkondition(const bool b){
                                                                if(b) glEnable(GL_STENCIL_TEST); else glDisable(GL_STENCIL_TEST);
 };
 void _grafikopengl::schablonenbufferkonditiongleich(const int ref,const unsigned int mask){
                                                                glStencilFunc(GL_EQUAL,ref,mask);
 };
 void _grafikopengl::schablonenbufferkonditionungleich(const int ref,const unsigned int mask){
                                                                glStencilFunc(GL_NOTEQUAL,ref,mask);
 };
 void _grafikopengl::schablonenbufferkonditionimmer(const int ref,const unsigned int mask){
                                                                glStencilFunc(GL_ALWAYS,ref,mask);
 };
 void _grafikopengl::schablonenbufferoperation(const int fail,const signed int zfail,const signed int zpass){
                                                                GLenum f=0;
                                                                GLenum zf=0;
                                                                GLenum zp=0;
                                                                if(fail==0) f=GL_KEEP; else if (fail==1) f=GL_INCR; else if (fail==-1) f=GL_DECR;
                                                                if(zfail==0) zf=GL_KEEP; else if (zfail==1) zf=GL_INCR; else if (zfail==-1) zf=GL_DECR;
                                                                if(zpass==0) zp=GL_KEEP; else if (zpass==1) zp=GL_INCR; else if (zpass==-1) zp=GL_DECR;
                                                                glStencilOp(f,zf,zp);
 };
 void _grafikopengl::schablonenbufferloeschen(){
                                                                glClear(GL_STENCIL_BUFFER_BIT);
 };
 void _grafikopengl::schablonenbufferschreiben(const bool b){
                                                                if (b) glStencilMask(~0); else glStencilMask(0);
};



 void _grafikopengl::maske(const bool b){
                                                                if(b) glEnable(GL_ALPHA_TEST); else glDisable(GL_ALPHA_TEST);
 };                                                                  
 //------------------------------------------------------------ Nebel ---------------------------------------------------------------------------------------------------------
 void _grafikopengl::nebel(bool b){
                                                                if(b) glEnable(GL_FOG);	else glDisable(GL_FOG);
 };
 void _grafikopengl::nebelmodus(unsigned int i){
                                                                if(i==0) glFogi(GL_FOG_MODE,GL_EXP);
                                                                if(i==1) glFogi(GL_FOG_MODE,GL_EXP2);
                                                                if(i==2) glFogi(GL_FOG_MODE,GL_LINEAR);
 };
 void _grafikopengl::nebelfarbe(const _vektor4<_to>&r){
                                                                GLfloat f[]={r[0],r[1],r[2],r[3]};
                                                                glFogfv(GL_FOG_COLOR,f);
 };
 void _grafikopengl::nebeldichte(_tg d){
                                                                glFogf(GL_FOG_DENSITY,d);
 };
 void _grafikopengl::nebeldistanz(_tg min,_tg max){
                                                                glFogf(GL_FOG_START,min);
                                                                glFogf(GL_FOG_END,max);
 };
/*
 bool   gp;						// G Pressed? ( New )
GLuint filter;						// Which Filter To Use
GLuint fogMode[]= { GL_EXP, GL_EXP2, GL_LINEAR };	// Storage For Three Types Of Fog
GLuint fogfilter= 0;					// Which Fog To Use
GLfloat fogColor[4]= {0.5f, 0.5f, 0.5f, 1.0f};		// Fog Color



glClearColor(0.5f,0.5f,0.5f,1.0f);			// We'll Clear To The Color Of The Fog ( Modified )

glFogi(GL_FOG_MODE, fogMode[fogfilter]);		// Fog Mode
glFogfv(GL_FOG_COLOR, fogColor);			// Set Fog Color
glFogf(GL_FOG_DENSITY, 0.35f);				// How Dense Will The Fog Be
glHint(GL_FOG_HINT, GL_DONT_CARE);			// Fog Hint Value
glFogf(GL_FOG_START, 1.0f);				// Fog Start Depth
glFogf(GL_FOG_END, 5.0f);				// Fog End Depth
glEnable(GL_FOG);	
*/


 //------------------------------------------------------------ Zeichnungsstatus -----------------------------------------------------------------------------------------------
 void _grafikopengl::transparenz(const bool b){
                                                                if(b) glEnable(GL_BLEND); else glDisable(GL_BLEND);
 };
 void _grafikopengl::transparenzadditiv(){
                                                                glBlendFunc(GL_ONE,GL_ONE);
 };
 void _grafikopengl::transparenzmultiplikativ(){
                                                                glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
 };
 void _grafikopengl::polygonverschiebung(const bool b){
                                                                if(b) glEnable(GL_POLYGON_OFFSET_FILL); else glDisable(GL_POLYGON_OFFSET_FILL);
 };
 void _grafikopengl::polygonverschiebung(const _tg a,const _tg b){
                                                                glPolygonOffset(a,b);
 };


 //------------------------------------------------------------ Zeichnung ------------------------------------------------------------------------------------------------------
 void _grafikopengl::vollbild(const _vektor4<_to>&c){
 
                                                                glPushMatrix();
                                                                glLoadIdentity();
	                                                            glOrtho(0, 100, 0,100, 0, 100);
                                                                glColor4f(c[0],c[1],c[2],c[3]);
	                                                            glBegin(GL_QUADS);
		                                                        glVertex3f(0 , 0, 1);  
		                                                        glVertex3f(100, 0, 1);
		                                                        glVertex3f(100,100, 1);
		                                                        glVertex3f(0, 100, 1);
                                	                            glEnd();
                                                                glPopMatrix();	                           
 };                                                                 
 void _grafikopengl::pixel(const _vektor3<_tg>&x,const _vektor4<_to>&c){
                                                                zeichnen(x,c);
 };
 void _grafikopengl::linie(const _vektor3<_tg>&x,const _vektor3<_tg>&y,const _vektor4<_to>&c){
                                                                zeichnen(x,y,c);
 };
 void _grafikopengl::kugel(const _vektor3<_tg>&o,const _vektor4<_to>&c,const _tg radius,const unsigned int resx,const unsigned int resy){ 
                                                                glColor4f(c[0],c[1],c[2],c[3]);
			                                                    //glFrontFace(GL_CW);
			                                                    glTranslatef(o[0],o[1],o[2]);
			                                                    glutSolidSphere(radius, resx,resy);
			                                                    glTranslatef(-o[0],-o[1],-o[2]);
};			                      
 
 void _grafikopengl::polygon(_liste<_vektor3<_tg> >*l){
                                                                _listenknoten<_vektor3<_tg> >*it;
                                                                if(l->anfang(it)){
                                                                 glBegin(GL_POLYGON);
                                                                 do{
                                                                  glVertex3dv(it->objekt()->daten());
                                                                 }while(l->naechstes(it));
                                                                 glEnd();
                                                                };

 };
 void _grafikopengl::polygon(_liste<_vektor3<_tg> >*l,const _vektor4<_to>&col){
                                                                _listenknoten<_vektor3<_tg> >*it;
                                                                if(l->anfang(it)){
                                                                 glBegin(GL_POLYGON);
                                                                 glColor4f(col[0],col[1],col[2],col[3]);
                                                                 do{
                                                                  glVertex3dv(it->objekt()->daten());
                                                                 }while(l->naechstes(it));
                                                                 glEnd();
                                                                };
 };
void _grafikopengl::rechteck(_bild<_tb>*b,_tg x,_tg y,_tg w,_tg h,const _vektor4<_to>&c,bool){};
void _grafikopengl::rechteck(_tg x,_tg y,_tg w,_tg h,const _vektor4<_to>&c){};

 void _grafikopengl::rechtecke(_liste<_vektor3<_tg> >*l){
                                                                _listenknoten<_vektor3<_tg> >*it;
                                                                if(l->anfang(it)){
                                                                 glBegin(GL_QUADS);
                                                                 do{
                                                                  glVertex3dv(it->objekt()->daten());
                                                                 }while(l->naechstes(it));
                                                                 glEnd();
                                                                };
 };                                                                 
 void _grafikopengl::rechtecke(_liste<_vektor3<_tg> >*l,const _vektor4<_to>&col){
                                                                _listenknoten<_vektor3<_tg> >*it;
                                                                if(l->anfang(it)){
                                                                 glBegin(GL_QUADS);
                                                                 glColor4f(col[0],col[1],col[2],col[3]);
                                                                 do{
                                                                  glVertex3dv(it->objekt()->daten());
                                                                 }while(l->naechstes(it));
                                                                 glEnd();
                                                                };
 }; 
 void _grafikopengl::rechteckstreifenzyklisch(_liste<_vektor3<_tg> >*l){
                                                                _listenknoten<_vektor3<_tg> >*it;
                                                                if(l->anfang(it)){
                                                                 glBegin(GL_QUAD_STRIP);
                                                                 do{
                                                                  glVertex3dv(it->objekt()->daten());
                                                                 }while(l->naechstes(it));
                                                                 glVertex3dv(it->objekt()->daten());
                                                                 it=it->naechstes();
                                                                 glVertex3dv(it->objekt()->daten());
                                                                 glEnd();
                                                                };

 };
 void _grafikopengl::rechteckstreifenzyklisch(_liste<_vektor3<_tg> >*l0,_liste<_vektor3<_tg> >*l1){
                                                                _listenknoten<_vektor3<_tg> >*ito;
                                                                _listenknoten<_vektor3<_tg> >*itu;
 
                                                                l0->anfang(ito);
                                                                l1->anfang(itu);
                                                                if((ito)&&(itu)){
                                                                 glBegin(GL_QUAD_STRIP);
                                                                 do{
                                                                  glVertex3dv(itu->objekt()->daten());
                                                                  glVertex3dv(ito->objekt()->daten());
                                                                  l1->naechstes(itu);
                                                                 }while(l0->naechstes(ito));
                                                                 glVertex3dv(itu->objekt()->daten());
                                                                 glVertex3dv(ito->objekt()->daten());
                                                                
                                                                 glEnd();
                                                                };
 
 };

 void _grafikopengl::rechteckstreifenzyklisch(_liste<_vektor3<_tg> >*l,const _vektor4<_to>&col){
                                                                _listenknoten<_vektor3<_tg> >*it;
                                                                if(l->anfang(it)){
                                                                 glBegin(GL_QUAD_STRIP);
                                                                 glColor4f(col[0],col[1],col[2],col[3]);
                                                                 do{
                                                                  glVertex3dv(it->objekt()->daten());
                                                                 }while(l->naechstes(it));
                                                                 glVertex3dv(it->objekt()->daten());
                                                                 it=it->naechstes();
                                                                 glVertex3dv(it->objekt()->daten());
                                                                 glEnd();
                                                                };

 };
 void _grafikopengl::rechteckstreifenzyklisch(_liste<_vektor3<_tg> >*l0,_liste<_vektor3<_tg> >*l1,const _vektor4<_to>&col){
                                                                _listenknoten<_vektor3<_tg> >*ito;
                                                                _listenknoten<_vektor3<_tg> >*itu;
 
                                                                l0->anfang(ito);
                                                                l1->anfang(itu);
                                                                if((ito)&&(itu)){
                                                                 glBegin(GL_QUAD_STRIP);
                                                                 glColor4f(col[0],col[1],col[2],col[3]);
                                                                 do{
                                                                  glVertex3dv(itu->objekt()->daten());
                                                                  glVertex3dv(ito->objekt()->daten());
                                                                  l1->naechstes(itu);
                                                                 }while(l0->naechstes(ito));
                                                                 glVertex3dv(itu->objekt()->daten());
                                                                 glVertex3dv(ito->objekt()->daten());
                                                                
                                                                 glEnd();
                                                                };
};                                                                
 void _grafikopengl::text(const _zeichenkette<_tt>&s,const ::_zeichensatz*z,const _vektor3<_tg>&o,const _vektor4<_to>&c){
                                                                //float  coords[4]; 
                                                                //glDisable(GL_TEXTURE_2D); 
                                                                glPushAttrib(GL_LIST_BIT | GL_CURRENT_BIT);                 // Pushes The Display List Bits 
                                                                glColor4f(c[0],c[1],c[2],c[3]); 
                                                                glRasterPos2d(o[0], o[1] + z->charhoehe());//fontHeight[num]); 
                                                                glListBase(z->identifikation()-32);//fontListBase[num] - 32);                                        // Sets The Base Character to 32 
                                                                glCallLists(s.groesse(), GL_UNSIGNED_BYTE, s.daten());     // Draws The Display List Text 
                                                                //glGetFloatv(GL_CURRENT_RASTER_POSITION, coords); 
                                                                
                                                                glPopAttrib();                                                               // Pops The Display List Bits 
                                                                //glEnable(GL_TEXTURE_2D); 
                                                                // return(coords[0]);  // return x-position
                                                                
 };


 void _grafikopengl::zeichnen(const _vektor3<_tg>&x,const _vektor4<_to>&c){
                                                                glBegin(GL_POINTS);
                                                                glColor4fv(c.daten());
                                                                glVertex3dv(x.daten());
                                                                glEnd();
 };                              

 void _grafikopengl::zeichnen(_tg*x,_to*c){
                                                               // glDisable(GL_TEXTURE_2D);
                                                                glBegin(GL_POINTS);
                                                                glColor3f(c[0],c[1],c[2]);
                                                                glVertex3f(float(x[0]),float(x[1]),float(x[2]));
                                                                glEnd();
                                                            
 };
 void _grafikopengl::zeichnen(_tg*x,_tg*y,_to*c){
                                                              //  glDisable(GL_TEXTURE_2D);
                                                                glBegin(GL_LINES);
                                                                glColor3f(c[0],c[1],c[2]);
                                                                glVertex3f(float(x[0]),float(x[1]),float(x[2]));
                                                                glVertex3f(float(y[0]),float(y[1]),float(y[2]));
                                                                glEnd();
 };
 void _grafikopengl::zeichnen(const _vektor3<_tg>&x,const _vektor3<_tg>&y,const _vektor4<_to>&c){
                                                              //  glDisable(GL_TEXTURE_2D);
                                                                glBegin(GL_LINES);
                                                                glColor4fv((c.daten()));
                                                                glVertex3dv((x.daten()));
                                                                glColor4fv((c.daten()));
                                                                glVertex3dv((y.daten()));
                                                                glEnd();
 };                                                               
//linie
 void _grafikopengl::zeichnen(const _vektor3<_tg>&x,const _vektor3<_tg>&y,const _vektor4<_to>&c0,const _vektor4<_to>&c1){
                                                               // glDisable(GL_TEXTURE_2D);
                                                                glBegin(GL_LINES);
                                                                glColor4fv((c0.daten()));
                                                                glVertex3dv((x.daten()));
                                                                glColor4fv((c1.daten()));
                                                                glVertex3dv((y.daten()));
                                                                glEnd();
 }; 
//dreieck ohne texcoords
 void _grafikopengl::zeichnen(const _vektor3<_tg>&p0,const _vektor3<_tg>&p1,const _vektor3<_tg>&p2,const _vektor4<_to>&c0,const _vektor4<_to>&c1,const _vektor4<_to>&c2){
                                                                //glDisable(GL_TEXTURE_2D);
                                                                glBegin(GL_TRIANGLES);
                                                                glColor4fv(c0.daten());
                                                                glVertex3dv(p0.daten());
                                                                glColor4fv(c1.daten());
                                                                glVertex3dv(p1.daten());
                                                                glColor4fv(c2.daten());
                                                                glVertex3dv(p2.daten());
                                                                glEnd();
 };                                                               
//dreieck MIT texcoords
 void _grafikopengl::zeichnen(const _vektor3<_tg>&p0,const _vektor3<_tg>&p1,const _vektor3<_tg>&p2,const _vektor4<_to>&c0,const _vektor4<_to>&c1,const _vektor4<_to>&c2,const _vektor2<_tg>&tc0,const _vektor2<_tg>&tc1,const _vektor2<_tg>&tc2){
                                                                glBegin(GL_TRIANGLES);
                                                                glColor4fv(c0.daten());
                                                                glTexCoord2dv(tc0.daten());
                                                                glVertex3dv(p0.daten());
                                                                glColor4fv(c1.daten());
                                                                glTexCoord2dv(tc1.daten());
                                                                glVertex3dv(p1.daten());
                                                                glColor4fv(c2.daten());
                                                                glTexCoord2dv(tc2.daten());
                                                                glVertex3dv(p2.daten());
                                                                glEnd();
 }; 
 
//dreieck MIT multitexcoords
 void _grafikopengl::zeichnen(const _vektor3<_tg>&p0,
                                        const _vektor3<_tg>&p1,
                                        const _vektor3<_tg>&p2,
                                        
                                        const _vektor4<_to>&c0,
                                        const _vektor4<_to>&c1,
                                        const _vektor4<_to>&c2,
                                        
                                        const _vektor2<_tg>&tc0,
                                        const _vektor2<_tg>&tc1,
                                        const _vektor2<_tg>&tc2,
                                        const _vektor2<_tg>&tc3,
                                        const _vektor2<_tg>&tc4,
                                        const _vektor2<_tg>&tc5){
                                                                glBegin(GL_TRIANGLES);
                                                                //glMultiTexCoord2f();
                                                                
                                                                
                                                                
                                                                glColor4f(c0[0],c0[1],c0[2],c0[3]);
                                                                glMultiTexCoord2fARB(GL_TEXTURE0_ARB, float(tc0[0]), float(tc0[1])); 
                                                                glMultiTexCoord2fARB(GL_TEXTURE1_ARB, float(tc3[0]), float(tc3[1])); 
                                                                glVertex3f(float(p0[0]),float(p0[1]),float(p0[2]));
                                                                glColor4f(c1[0],c1[1],c1[2],c1[3]);
                                                                glMultiTexCoord2fARB(GL_TEXTURE0_ARB, float(tc1[0]), float(tc1[1])); 
                                                                glMultiTexCoord2fARB(GL_TEXTURE1_ARB, float(tc4[0]), float(tc4[1])); 
                                                                glVertex3f(float(p1[0]),float(p1[1]),float(p1[2]));
                                                                glColor4f(c2[0],c2[1],c2[2],c2[3]);
                                                                glMultiTexCoord2fARB(GL_TEXTURE0_ARB, float(tc2[0]), float(tc2[1])); 
                                                                glMultiTexCoord2fARB(GL_TEXTURE1_ARB, float(tc5[0]), float(tc5[1])); 
                                                                glVertex3f(float(p2[0]),float(p2[1]),float(p2[2]));
                                                                glEnd();
 };                                                               
//dreieck MIT multitexcoords
void _grafikopengl::zeichnen(const _vektor3<_tg>&p0,
                                        const _vektor3<_tg>&p1,
                                        const _vektor3<_tg>&p2,
                                        
                                        const _vektor4<_to>&c0,
                                        const _vektor4<_to>&c1,
                                        const _vektor4<_to>&c2,
                                        
                                        const _vektor2<_tg>&tc0,
                                        const _vektor2<_tg>&tc1,
                                        const _vektor2<_tg>&tc2,
                                        const _vektor2<_tg>&tc3,
                                        const _vektor2<_tg>&tc4,
                                        const _vektor2<_tg>&tc5,
                                        const _vektor2<_tg>&tc6,
                                        const _vektor2<_tg>&tc7,
                                        const _vektor2<_tg>&tc8){
                                                                glBegin(GL_TRIANGLES);
                                                                //glMultiTexCoord2f();
                                                                glColor4f(c0[0],c0[1],c0[2],c0[3]);
                                                                glMultiTexCoord2fARB(GL_TEXTURE0_ARB, float(tc0[0]), float(tc0[1])); 
                                                                glMultiTexCoord2fARB(GL_TEXTURE1_ARB, float(tc3[0]), float(tc3[1])); 
                                                                glMultiTexCoord2fARB(GL_TEXTURE2_ARB, float(tc6[0]), float(tc6[1])); 
                                                                glVertex3f(float(p0[0]),float(p0[1]),float(p0[2]));
                                                                glColor4f(c1[0],c1[1],c1[2],c1[3]);
                                                                glMultiTexCoord2fARB(GL_TEXTURE0_ARB, float(tc1[0]), float(tc1[1])); 
                                                                glMultiTexCoord2fARB(GL_TEXTURE1_ARB, float(tc4[0]), float(tc4[1])); 
                                                                glMultiTexCoord2fARB(GL_TEXTURE2_ARB, float(tc7[0]), float(tc7[1])); 
                                                                glVertex3f(float(p1[0]),float(p1[1]),float(p1[2]));
                                                                glColor4f(c2[0],c2[1],c2[2],c2[3]);
                                                                glMultiTexCoord2fARB(GL_TEXTURE0_ARB, float(tc2[0]), float(tc2[1])); 
                                                                glMultiTexCoord2fARB(GL_TEXTURE1_ARB, float(tc5[0]), float(tc5[1])); 
                                                                glMultiTexCoord2fARB(GL_TEXTURE2_ARB, float(tc8[0]), float(tc8[1])); 
                                                                glVertex3f(float(p2[0]),float(p2[1]),float(p2[2]));
                                                                glEnd();
 };                                                               
                          
 void _grafikopengl::zeichnen(const _vektor3<_tg>&p0,
                                           const _vektor3<_tg>&p1,
                                           const _vektor3<_tg>&p2,
                                           const _vektor3<_tg>&n0,
                                           const _vektor3<_tg>&n1,
                                           const _vektor3<_tg>&n2,
                                           const _vektor4<_to>&c0,
                                           const _vektor4<_to>&c1,
                                           const _vektor4<_to>&c2,
                                           const _vektor2<_tg>&tc0,
                                           const _vektor2<_tg>&tc1,
                                           const _vektor2<_tg>&tc2){
                                                                glBegin(GL_TRIANGLES);
                                                                glColor4f(c0[0],c0[1],c0[2],c0[3]);
                                                               // glColor4f(1,1,0,1);
                                                                glNormal3f(float(n0[0]),float(n0[1]),float(n0[2]));
                                                                glTexCoord2f(float(tc0[0]),float(tc0[1]));
                                                                glVertex3f(float(p0[0]),float(p0[1]),float(p0[2]));
                                                                glColor4f(c1[0],c1[1],c1[2],c1[3]);
                                                                glNormal3f(float(n1[0]),float(n1[1]),float(n1[2]));
                                                                glTexCoord2f(float(tc1[0]),float(tc1[1]));
                                                                glVertex3f(float(p1[0]),float(p1[1]),float(p1[2]));
                                                                glColor4f(c2[0],c2[1],c2[2],c2[3]);
                                                                glNormal3f(float(n2[0]),float(n2[1]),float(n2[2]));
                                                                glTexCoord2f(float(tc2[0]),float(tc2[1]));
                                                                glVertex3f(float(p2[0]),float(p2[1]),float(p2[2]));
                                                                glEnd();
 };                                           

 void _grafikopengl::zeichnen(const _vektor3<_tg>&p0,
                                           const _vektor3<_tg>&p1,
                                           const _vektor3<_tg>&p2,
                                           const _vektor3<_tg>&n0,
                                           const _vektor3<_tg>&n1,
                                           const _vektor3<_tg>&n2,
                                           const _vektor4<_to>&c0,
                                           const _vektor4<_to>&c1,
                                           const _vektor4<_to>&c2,
                                           const _vektor2<_tg>&tc0,
                                           const _vektor2<_tg>&tc1,
                                           const _vektor2<_tg>&tc2,
                                           const _vektor2<_tg>&tc3,
                                           const _vektor2<_tg>&tc4,
                                           const _vektor2<_tg>&tc5){
                                                                glBegin(GL_TRIANGLES);
                                                                glColor4f(c0[0],c0[1],c0[2],c0[3]);
                                                                glNormal3f(float(n0[0]),float(n0[1]),float(n0[2]));
                                                                glMultiTexCoord2fARB(GL_TEXTURE0_ARB, float(tc0[0]), float(tc0[1])); 
                                                                glMultiTexCoord2fARB(GL_TEXTURE1_ARB, float(tc3[0]), float(tc3[1])); 
                                                                glVertex3f(float(p0[0]),float(p0[1]),float(p0[2]));
                                                                glColor4f(c1[0],c1[1],c1[2],c1[3]);
                                                                glNormal3f(float(n1[0]),float(n1[1]),float(n1[2]));
                                                                glMultiTexCoord2fARB(GL_TEXTURE0_ARB, float(tc1[0]), float(tc1[1])); 
                                                                glMultiTexCoord2fARB(GL_TEXTURE1_ARB, float(tc4[0]), float(tc4[1])); 
                                                                glVertex3f(float(p1[0]),float(p1[1]),float(p1[2]));
                                                                glColor4f(c2[0],c2[1],c2[2],c2[3]);
                                                                glNormal3f(float(n2[0]),float(n2[1]),float(n2[2]));
                                                                glMultiTexCoord2fARB(GL_TEXTURE0_ARB, float(tc2[0]), float(tc2[1])); 
                                                                glMultiTexCoord2fARB(GL_TEXTURE1_ARB, float(tc5[0]), float(tc5[1])); 
                                                                glVertex3f(float(p2[0]),float(p2[1]),float(p2[2]));
                                                                glEnd();
 };                                           
                                          

 void _grafikopengl::zeichnen(const _vektor3<_tg>&p0,
                                           const _vektor3<_tg>&p1,
                                           const _vektor3<_tg>&p2,
                                           const _vektor3<_tg>&n0,
                                           const _vektor3<_tg>&n1,
                                           const _vektor3<_tg>&n2,
                                           const _vektor4<_to>&c0,
                                           const _vektor4<_to>&c1,
                                           const _vektor4<_to>&c2,
                                           const _vektor2<_tg>&tc0,
                                           const _vektor2<_tg>&tc1,
                                           const _vektor2<_tg>&tc2,
                                           const _vektor2<_tg>&tc3,
                                           const _vektor2<_tg>&tc4,
                                           const _vektor2<_tg>&tc5,
                                           const _vektor2<_tg>&tc6,
                                           const _vektor2<_tg>&tc7,
                                           const _vektor2<_tg>&tc8){
                                                                 glBegin(GL_TRIANGLES);
                                                                //glMultiTexCoord2f();
                                                                glColor4f(c0[0],c0[1],c0[2],c0[3]);
                                                                glNormal3f(float(n0[0]),float(n0[1]),float(n0[2]));
                                                                glMultiTexCoord2fARB(GL_TEXTURE0_ARB, float(tc0[0]), float(tc0[1])); 
                                                                glMultiTexCoord2fARB(GL_TEXTURE1_ARB, float(tc3[0]), float(tc3[1])); 
                                                                glMultiTexCoord2fARB(GL_TEXTURE2_ARB, float(tc6[0]), float(tc6[1])); 
                                                                glVertex3f(float(p0[0]),float(p0[1]),float(p0[2]));
                                                                glColor4f(c1[0],c1[1],c1[2],c1[3]);
                                                                glNormal3f(float(n1[0]),float(n1[1]),float(n1[2]));
                                                                glMultiTexCoord2fARB(GL_TEXTURE0_ARB, float(tc1[0]), float(tc1[1])); 
                                                                glMultiTexCoord2fARB(GL_TEXTURE1_ARB, float(tc4[0]), float(tc4[1])); 
                                                                glMultiTexCoord2fARB(GL_TEXTURE2_ARB, float(tc7[0]), float(tc7[1])); 
                                                                glVertex3f(float(p1[0]),float(p1[1]),float(p1[2]));
                                                                glColor4f(c2[0],c2[1],c2[2],c2[3]);
                                                                glNormal3f(float(n2[0]),float(n2[1]),float(n2[2]));
                                                                glMultiTexCoord2fARB(GL_TEXTURE0_ARB, float(tc2[0]), float(tc2[1])); 
                                                                glMultiTexCoord2fARB(GL_TEXTURE1_ARB, float(tc5[0]), float(tc5[1])); 
                                                                glMultiTexCoord2fARB(GL_TEXTURE2_ARB, float(tc8[0]), float(tc8[1])); 
                                                                glVertex3f(float(p2[0]),float(p2[1]),float(p2[2]));
                                                                glEnd();
 };                                           
 //DEBUG

 void _grafikopengl::zeichnendebug(const _vektor3<_tg>&p0,const _vektor3<_tg>&p1,const _vektor3<_tg>&p2,const _vektor4<_to>&c0,const _vektor4<_to>&c1,const _vektor4<_to>&c2){
                                                                _to q0,q1,q2;
                                                                glDisable(GL_TEXTURE_2D);
                                                                glEnable(GL_BLEND);
                                                                glDisable(GL_DEPTH_TEST);
                                                                q0=1.0f/(1.0f+pow(float(p0[2])*0.03f,2));
                                                                q1=1.0f/(1.0f+pow(float(p1[2])*0.03f,2));
                                                                q2=1.0f/(1.0f+pow(float(p2[2])*0.03f,2));
                                                                glBegin(GL_TRIANGLES);
                                                                glColor4f(c0[0]*q0,c0[1]*q0,c0[2]*q0,0.6f);
                                                                glVertex3f(float(p0[0]),float(p0[1]),float(p0[2]));
                                                                glColor4f(c1[0]*q1,c1[1]*q1,c1[2]*q1,0.6f);
                                                                glVertex3f(float(p1[0]),float(p1[1]),float(p1[2]));
                                                                glColor4f(c2[0]*q2,c2[1]*q2,c2[2]*q2,0.6f);
                                                                glVertex3f(float(p2[0]),float(p2[1]),float(p2[2]));
                                                                glEnd();
                                                              //  glEnable(GL_DEPTH_TEST);
                                                               // MessageBeep(0xffffffff);
 };                                     

 void _grafikopengl::zeichnenabgeschnitten(const _vektor3<_tg>&,const _vektor4<_to>&){};

 void _grafikopengl::zeichnenabgeschnitten(const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor4<_to>&){};

/*
void _gdiopengl::depthbuffer(char c){
};
void _gdiopengl::current(){
};
void _gdiopengl::reskalieren(int,int){
};
void _gdiopengl::reskalieren(){
};
void _gdiopengl::vertexlayout(){
};
void _gdiopengl::vispipe(int m){
                                                                if(m|G->pf->TRANSLUCENT){
                                                                 glDisable(GL_DEPTH_TEST);   
                                                                 glEnable(GL_BLEND);
                                                                }else{
                                                                 glEnable(GL_DEPTH_TEST);   
                                                                 glDisable(GL_BLEND);
                                                                };
};
void _gdiopengl::init(_bitmap*b){
                                                                int typ=GL_RGBA;
                                                                //------------
                                                                if(b->gdiinit==0){
                                                                 glGenTextures(1,&b->id);
                                                                 glBindTexture(GL_TEXTURE_2D, b->id);
                                                                 glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
                                                                 glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
                                                                 glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
                                                                 glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
                                                                 if(b->bpp==24)typ=GL_RGB; else if(b->bpp==32) typ=GL_RGBA;
                                                                 glTexImage2D(GL_TEXTURE_2D,0,typ,b->wx,b->wy,0,typ,GL_UNSIGNED_BYTE,b->daten);
                                                                 G->fim->schreiben("gdi::bind() ausgeführt mit ",b->name);
                                                                };
                                                                b->gdiinit=1;
                                                               // G->peep(1,10000,0);
};
void _gdiopengl::exit(_bitmap*b){
                                                                b->gdiinit=0;
                                                               // G->peep(1,10000,0);
};
void _gdiopengl::bind(_bitmap*b){
                                                                glBindTexture(GL_TEXTURE_2D,(GLuint)b->id);    
};
void _gdiopengl::unbind(){
};
void _gdiopengl::zeichnen(int m,_vertex*v0,_vertex*v1,_vertex*v2){
                                                                glBegin(GL_TRIANGLES);
                                                                //v0
                                                                glColor3f(v0->c[0],v0->c[1],v0->c[2]);
                                                                glTexCoord2f(v0->st[0][0],v0->st[0][1]);
                                                                glVertex3f(v0->p[0],v0->p[1],-v0->p[2]);        
                                                                //v1
                                                                glColor3f(v1->c[0],v1->c[1],v1->c[2]);
                                                                glTexCoord2f(v1->st[0][0],v1->st[0][1]);
                                                                glVertex3f(v1->p[0],v1->p[1],-v1->p[2]);        
                                                                //v2
                                                                glColor3f(v2->c[0],v2->c[1],v2->c[2]);
                                                                glTexCoord2f(v2->st[0][0],v2->st[0][1]);
                                                                glVertex3f(v2->p[0],v2->p[1],-v2->p[2]);        
                                                                glEnd();
                                                                if(m|G->pf->WIRED){
                                                                glBegin(GL_LINES);
                                                                //v0
                                                                 glColor3f(v0->c[0],v0->c[1],v0->c[2]);
                                                                 glTexCoord2f(v0->st[0][0],v0->st[0][1]);
                                                                 glVertex3f(v0->p[0],v0->p[1],-v0->p[2]);        
                                                                 //v1
                                                                 glColor3f(v1->c[0],v1->c[1],v1->c[2]);
                                                                 glTexCoord2f(v1->st[0][0],v1->st[0][1]);
                                                                 glVertex3f(v1->p[0],v1->p[1],-v1->p[2]);        
                                                                 //v2
                                                                 glColor3f(v2->c[0],v2->c[1],v2->c[2]);
                                                                 glTexCoord2f(v2->st[0][0],v2->st[0][1]);
                                                                 glVertex3f(v2->p[0],v2->p[1],-v2->p[2]);        
                                                                //v0
                                                                 glColor3f(v0->c[0],v0->c[1],v0->c[2]);
                                                                 glTexCoord2f(v0->st[0][0],v0->st[0][1]);
                                                                 glVertex3f(v0->p[0],v0->p[1],-v0->p[2]);        
                                                                glEnd();
                                                                
                                                                };
};
void _gdiopengl::zeichnen(int m,_vertex*v0,_vertex*v1,_vertex*v2,_vertex*v3){
                                                                glBegin(GL_QUADS);
                                                                //v0
                                                                glColor3f(v0->c[0],v0->c[1],v0->c[2]);
                                                                glTexCoord2f(v0->st[0][0],v0->st[0][1]);
                                                                glVertex3f(v0->p[0],v0->p[1],-v0->p[2]);        
                                                                //v1
                                                                glColor3f(v1->c[0],v1->c[1],v1->c[2]);
                                                                glTexCoord2f(v1->st[0][0],v1->st[0][1]);
                                                                glVertex3f(v1->p[0],v1->p[1],-v1->p[2]);        
                                                                //v2
                                                                glColor3f(v2->c[0],v2->c[1],v2->c[2]);
                                                                glTexCoord2f(v2->st[0][0],v2->st[0][1]);
                                                                glVertex3f(v2->p[0],v2->p[1],-v2->p[2]);        
                                                                //v3
                                                                glColor3f(v3->c[0],v3->c[1],v3->c[2]);
                                                                glTexCoord2f(v3->st[0][0],v3->st[0][1]);
                                                                glVertex3f(v3->p[0],v3->p[1],-v3->p[2]);        
                                                                glEnd();
};
void _gdiopengl::zeichnen(_poly*p){
                                                                _vertex*v;
                                                                //---------
                                                                glBegin(GL_POLYGON);
                                                                v=p->firstvertex;
                                                                if(v)do{
                                                                 glColor3f(v->c[0],v->c[1],v->c[2]);
                                                                 glTexCoord2f(v->st[0][0],v->st[0][1]);
                                                                 glVertex3f(v->p[0],v->p[1],-v->p[2]);
                                                                 v=v->naechstes(p);
                                                                }while(v!=p->firstvertex);
                                                                glEnd();

};

void _gdiopengl::zeichnen(_vertex*v0,_vertex*v1){
                                                                glBegin(GL_LINES);
                                                                //v0
                                                                glColor3f(v0->c[0],v0->c[1],v0->c[2]);
                                                                glTexCoord2f(v0->st[0][0],v0->st[0][1]);
                                                                glVertex3f(v0->p[0],v0->p[1],-v0->p[2]);        
                                                                //v1
                                                                glColor3f(v1->c[0],v1->c[1],v1->c[2]);
                                                                glTexCoord2f(v1->st[0][0],v1->st[0][1]);
                                                                glVertex3f(v1->p[0],v1->p[1],-v1->p[2]);        
                                                                glEnd();
};
void _gdiopengl::zeichnen(_vertex*v0){
                                                                glBegin(GL_POINTS);
                                                                //v0
                                                                glColor3f(v0->c[0],v0->c[1],v0->c[2]);
                                                                glTexCoord2f(v0->st[0][0],v0->st[0][1]);
                                                                glVertex3f(v0->p[0],v0->p[1],-v0->p[2]);
                                                                glEnd();
                                                                
};
void _gdiopengl::zeichnenabgeschnitten(_vertex*v0){
                                                                zeichnen(v0);
};
void _gdiopengl::zeichnenabgeschnitten(_vertex*v0,_vertex*v1){
                                                                zeichnen(v0,v1);
};
void _gdiopengl::zeichnenabgeschnitten(int maske,_vertex*v0,_vertex*v1,_vertex*v2){
                                                                zeichnen(maske,v0,v1,v2);
};
void _gdiopengl::zeichnenabgeschnitten(int maske,_vertex*v0,_vertex*v1,_vertex*v2,_vertex*v3){
                                                                zeichnen(maske,v0,v1,v2,v3);
};
void _gdiopengl::zeichnenabgeschnitten(_poly*p){
                                                                zeichnen(p);
                                                                
};

 */
 


//******************************************************************************************************************************************************************************************************
//                                                              R E N D E R C O N T E X T O P E N G L
//******************************************************************************************************************************************************************************************************
 _renderkontextopengl::_renderkontextopengl(){
                                                                /*GLuint  PixelFormat;
                                                                static  PIXELFORMATDESCRIPTOR pfd={
                                                                sizeof(PIXELFORMATDESCRIPTOR),          // Size Of This Pixel Format Descriptor
                                                                1,                                      // Version Number (?)
                                                                PFD_DRAW_TO_WINDOW |                    // Format Must Support Window
                                                                PFD_SUPPORT_OPENGL |                    // Format Must Support OpenGL
                                                                PFD_DOUBLEBUFFER,                       // Must Support Double Buffering
                                                                PFD_TYPE_RGBA,                          // Request An RGBA Format
                                                                16,                                     // Select A 16Bit Color Depth
                                                                0, 0, 0, 0, 0, 0,                       // Color Bits Ignored (?)
                                                                0,                                      // No Alpha Buffer
                                                                0,                                      // Shift Bit Ignored (?)
                                                                0,                                      // No Accumulation Buffer
                                                                0, 0, 0, 0,                             // Accumulation Bits Ignored (?)
                                                                16,                                     // 16Bit Z-Buffer (Depth Buffer)  
                                                                0,                                      // No Stencil Buffer
                                                                0,                                      // No Auxiliary Buffer (?)
                                                                PFD_MAIN_PLANE,                         // Main Drawing Layer
                                                                0,                                      // Reserved (?)
                                                                0, 0, 0                                 // Layer Masks Ignored (?)
                                                                };
                                                                WNDCLASS wndclass;
                                                                LOGBRUSH brush;
                                                                //----------------------------------
                                                                brush.lbStyle   = BS_SOLID;
                                                                brush.lbColor   = RGB(0,0,0); 
                                                                brush.lbHatch   = HS_VERTICAL;
                                                                wndclass.style=CS_OWNDC|CS_BYTEALIGNWINDOW|CS_BYTEALIGNCLIENT;
                                                                wndclass.lpfnWndProc=NULL;
                                                                wndclass.c#lsExtra=0;
                                                                wndclass.cbWndExtra=sizeof(LONG);
                                                                wndclass.hInstance=0;
                                                                wndclass.hIcon=0;
                                                                wndclass.hCursor=0;
                                                                wndclass.hbrBackground=(HBRUSH) CreateBrushIndirect(&brush);
                                                                wndclass.lpszMenuName=0;
                                                                wndclass.lpszClassName="wingraphicopenglclass";
                                                                RegisterClass(&wndclass);
                                                                phandle=CreateWindow("wingraphicopenglclass","_grafikopengl",WS_VISIBLE,0,0,10,10,NULL,NULL,NULL,NULL);
                                                                hdc=GetDC(phandle);
                                                                PixelFormat = ChoosePixelFormat(hdc, &pfd);
                                                                if (!PixelFormat){
                                                                 MessageBox(0,"Can't Find A Suitable PixelFormat.","Error",MB_OK|MB_ICONERROR);
                                                                 PostQuitMessage(0);                             // This Sends A 'Message' Telling The Program To Quit
                                                                } else
                                                                if(!SetPixelFormat(hdc,PixelFormat,&pfd)){
                                                                 MessageBox(0,"Can't Set The PixelFormat.","Error",MB_OK|MB_ICONERROR);
                                                                 PostQuitMessage(0);
                                                                } else {
                                                                 hrc = wglCreateContext(hdc);
                                                                 if(!hrc){
                                                                  MessageBox(0,"Can't Create A GL Rendering Context.","Error",MB_OK|MB_ICONERROR);
                                                                  PostQuitMessage(0);
                                                                 } else 
                                                                 if(!wglMakeCurrent(hdc, hrc)){
                                                                  MessageBox(0,"Can't activate GLRC.","Error",MB_OK|MB_ICONERROR);
                                                                  PostQuitMessage(0);
                                                                 }else {
                                                                  SetWindowPos(phandle,0,0,0,10,10,0);
                                                                  //ShowWindow(phandle,SW_HIDE);
                                                                 
                                                                 };
                                                                };*/
                                                                //ReleaseDC(phandle,hdc);
 };

 _renderkontextopengl::~_renderkontextopengl(){
                                                              /*  wglDeleteContext(hrc);
                                                                ReleaseDC(phandle,hdc);
                                                                DestroyWindow(phandle);*/
 };
 HGLRC _renderkontextopengl::handle(){
                                                                return(hrc);
 };


//******************************************************************************************************************************************************************************************************
//                                                              B I L D H A R D W A R E O P E N G L
//******************************************************************************************************************************************************************************************************
_bildhardwareopengl::_bildhardwareopengl(_grafikopengl*pg,_bild<_tb>*pb):_bildhardware(pg,pb){
                                                                pgrafik=pg;
                                                                //pgrafik->listebildhardware()->einhaengen(this);
                                                                
                                                                glGenTextures(1,&pid);
                                                                //mit->bildidentifikation(texid,this);
                                                                glBindTexture(GL_TEXTURE_2D,pid);
                                                                pgrafik->paltebindung=this;
                                                                if(bild()->mipmap()){
                                                                 glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
                                                                 glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                                                                }else{
                                                                 glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
                                                                 glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
                                                                };
                                                                if(bild()->wiederholung(0)){
                                                                 glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
                                                                }else{
                                                                 glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
                                                                };
                                                                if(bild()->wiederholung(1)){
                                                                 glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
                                                                }else{
                                                                 glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
                                                                };
                                                                if(bild()->kanaele()==3){
                                                                 if(bild()->mipmap()){
                                                                  gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, bild()->groesse(0), bild()->groesse(1), GL_RGB, GL_UNSIGNED_BYTE, (GLvoid*)bild()->daten());
                                                                 }else{
                                                                  glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,bild()->groesse(0),bild()->groesse(1),0,GL_RGB,GL_UNSIGNED_BYTE,(GLvoid*)bild()->daten());
                                                                 };
                                                                }else{
                                                                 if(bild()->kanaele()==4){
                                                                  if(bild()->mipmap()){
                                                                   gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, bild()->groesse(0), bild()->groesse(1), GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)bild()->daten());
                                                                  }else{
                                                                    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,bild()->groesse(0),bild()->groesse(1),0,GL_RGBA,GL_UNSIGNED_BYTE,(GLvoid*)bild()->daten());
                                                                  };
                                                                 };
                                                                };                                                                
};
_bildhardwareopengl::~_bildhardwareopengl(){
                                                                //pgrafik->listebildhardware()->aushaengen(this);
                                                                loeschen();
                                                                if(pgrafik->paltebindung==this) pgrafik->paltebindung=0;

};
void _bildhardwareopengl::loeschen(){
                                                                glDeleteTextures(1,&pid);
                                                                pid=0;//mit->bildidentifikation(0,this);
};
void _bildhardwareopengl::wiederherstellen(){
};
bool _bildhardwareopengl::binden(){
                                                                pgrafik->paltebindung=this;
                                                                glBindTexture(GL_TEXTURE_2D,pid);
                                                                return(true);
                                                                
};
void _bildhardwareopengl::lesen(_to*t){
};
bool _bildhardwareopengl::oeffnen(){
																return(false);
};
_tb* _bildhardwareopengl::daten(){
																return(0);
};
void _bildhardwareopengl::schliessen(){
};

/*
//*****************************************************************************************************************************************************************************************************+
//                                                              Z E I C H E N S A T Z O P E N G L 
//*****************************************************************************************************************************************************************************************************+

_zeichensatzopengl::_zeichensatzopengl(HDC hdc,char*c,int hei,int fat,bool italic,bool underline,bool strikeout) {
                                                                phdc=hdc;
                                                                TEXTMETRIC tm;
                                                                hei = -MulDiv(hei, GetDeviceCaps(phdc, LOGPIXELSY), 72);
                                                                handle=CreateFontA(
                                                                hei,
                                                                0,
                                                                0,
                                                                0,
                                                                fat,
                                                                italic,
                                                                underline,
                                                                strikeout,
                                                                DEFAULT_CHARSET,
                                                                OUT_DEFAULT_PRECIS,
                                                                CLIP_DEFAULT_PRECIS,
                                                                ANTIALIASED_QUALITY,
                                                                DEFAULT_PITCH|FF_DONTCARE,
                                                                c);
                                                                SetMapMode(phdc,MM_TEXT);
                                                                GetTextMetrics(phdc,&tm);
                                                                pheight=tm.tmHeight-1;//tm.tmExternalLeading;
                                                                //pheight=hei;
                                                                pwidth=(pheight+1)/2;
                                                                anwaehlen();
                                                                
                                                                
                                                                unsigned int id = glGenLists(224);
                                                                identifikation(id);
                                                                wglUseFontBitmaps(hdc, 32, 224, identifikation());
                                                                
                                                                
};
_zeichensatzopengl::~_zeichensatzopengl(){
                                                                abwaehlen();
                                                                DeleteObject(handle);
                                                                glDeleteLists(identifikation(), 224);
};


void _zeichensatzopengl::text(const _zeichenkette<char>&,_tg x,_tg y,const _vektor4<_to>&color){
};
void _zeichensatzopengl::text(const _zeichenkette<unsigned short>&,_tg x,_tg y,const _vektor4<_to>&color){
};
_tg _zeichensatzopengl::breite(const _zeichenkette<_tt>&){
                                                                return(0);
};
_tg _zeichensatzopengl::hoehe(const _zeichenkette<_tt>&){
                                                                return(0);
};
_zeichen*_zeichensatzopengl::zeichen(unsigned int){
                                                                return(0);
};




void _zeichensatzopengl::anwaehlen(){
                                                                oldhandle = (HFONT)SelectObject(phdc,handle);
};
void _zeichensatzopengl::abwaehlen(){
                                                                SelectObject(phdc,oldhandle);
};
void _zeichensatzopengl::text(char*c,int x,int y,char r,char g,char b){
                                                                anwaehlen();
                                                                SetBkMode(phdc,TRANSPARENT);
                                                                SetTextColor(phdc,RGB(r,g,b));
                                                                TextOutA(phdc,x, y, c, (int)strlen(c));
                                                                abwaehlen();
};
void _zeichensatzopengl::text(char*c,int x,int y,char r,char g,char b,char hr,char hg,char hb){
                                                                anwaehlen();
                                                                SetBkMode(phdc,OPAQUE);//peep(10);
                                                                SetBkColor(phdc,RGB(hr,hg,hb));
                                                                SetTextColor(phdc,RGB(r,g,b));
                                                                TextOutA(phdc,x, y, c, (int)strlen(c));
                                                                abwaehlen();
};
void _zeichensatzopengl::text(char*c,int x,int y,_vektor<unsigned char>&v){
                                                                anwaehlen();
                                                                SetBkMode(phdc,TRANSPARENT);
                                                                SetTextColor(phdc,RGB(v[0],v[1],v[2]));
                                                                TextOutA(phdc,x, y, c, (int)strlen(c));
                                                                abwaehlen();
};
void _zeichensatzopengl::text(char*c,int x,int y,_vektor<unsigned char>&v,_vektor<unsigned char>&h){
                                                                anwaehlen();
                                                                SetBkMode(phdc,OPAQUE);//peep(10);
                                                                SetBkColor(phdc,RGB(h[0],h[1],h[2]));
                                                                SetTextColor(phdc,RGB(v[0],v[1],v[2]));
                                                                TextOutA(phdc,x, y, c, (int)strlen(c));
                                                                abwaehlen();
};
void _zeichensatzopengl::schnellvorbereiten(){
                                                                SetBkMode(phdc,OPAQUE);//peep(10);
};
void _zeichensatzopengl::textschnell(char*c,int x,int y,int l,_vektor<unsigned char>&v,_vektor<unsigned char>&h){
                                                                anwaehlen();
                                                                SetBkColor(phdc,RGB(h[0],h[1],h[2]));
                                                                SetTextColor(phdc,RGB(v[0],v[1],v[2]));
                                                                TextOutA(phdc,x, y, c,l);
                                                                abwaehlen();
};
int _zeichensatzopengl::charbreite() const{
                                                        
                                                                return(pwidth);
};
int _zeichensatzopengl::charhoehe() const{
                                                                return(pheight);
};
void _zeichensatzopengl::breite(char*c,int&w,int&h){
                                                                SIZE s;
                                                                GetTextExtentPoint32A(phdc,c,(int)strlen(c),&s);
                                                                w=s.cx;
                                                                h=s.cy;
                                                                
};
*/