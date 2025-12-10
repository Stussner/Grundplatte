//******************************************************************************************************************************************************************************************************
//  Projekt      : grundplatte
//  Bibliothek   : grafikdirectx.cpp
//  Modul        : grafikdirectx
//  Datum        : 24.08.2008
//  Beschreibung : 
//******************************************************************************************************************************************************************************************************
#include <_grafikdirectx.hpp>


//********************************************************************************************************************************************************************************
//	                        									G R A F I K M O D U S
//********************************************************************************************************************************************************************************
_grafikmodus::_grafikmodus(_listebasis<_grafikmodus>*l,unsigned int wx,unsigned int wy,unsigned int bpp,unsigned int r):_listenknotenbasis<_grafikmodus>(l){
                                                                breite=wx;
                                                                hoehe=wy;
                                                                tiefe=bpp;
                                                                rate=r;
};
_grafikmodus::~_grafikmodus(){
};
void grafikmodusaktuell(unsigned int&wx,unsigned int&wy,unsigned int&bpp,unsigned int&rate){
                                                                HRESULT hr;
                                                                if( FAILED( hr = D3DXInitialize() ) ) {
                                                                 MessageBoxA(NULL,"D3DX Initialization failed.","grafikmodusaktuell()",MB_OK);
                                                                };
                                                                D3DX_VIDMODEDESC vm;
                                                                D3DXGetCurrentVideoMode(0,&vm);
                                                                wx=vm.width;
                                                                wy=vm.height;
                                                                bpp=vm.bpp;
                                                                rate=vm.refreshRate;
                                                                
};    
void lesengrafikmodus(_listebasis<_grafikmodus>*l){//returns list of propably supported videomodes
                                                                D3DX_VIDMODEDESC vm;
				                                                l->loeschen();
				                                                int nvm;
                                                                nvm=D3DXGetMaxNumVideoModes(0,D3DX_GVM_REFRESHRATE);
				                                                L->schreiben("Available graphics modes : ",nvm);
                                                                for(int i=0;i<nvm;i++){
                                                                 D3DXGetVideoMode(0,D3DX_GVM_REFRESHRATE,i,&vm);
                                                                 _grafikmodus*m=new _grafikmodus(l,vm.width,vm.height,vm.bpp,vm.refreshRate);
			 	                                                 L->schreiben("Grafikmodus : ");
			 	                                                 L->schreiben("Breite : ",(int)m->breite);
			 	                                                 L->schreiben("Hoehe : ",(int)m->hoehe);
			 	                                                 L->schreiben("Tiefe : ",(int)m->tiefe);
			 	                                                 L->schreiben("Rate : ",(int)m->rate);
				                                                };
};

_grafikmodus* bestergrafikmodus(_listebasis<_grafikmodus>*l,unsigned int near_width,unsigned int near_height){
				                                                lesengrafikmodus(l);
				
                                                                //get selection by width
                                                                _liste<_grafikmodus> selectionwidth;
                                                                _grafikmodus*mit;
                                                                if(l->anfang(mit))do{
                                                                 if((near_width==mit->breite)&&(near_height==mit->hoehe)) selectionwidth.einhaengen(mit);
                                                                }while(l->naechstes(mit));
                                                                if(selectionwidth.anzahl()==0){
                                                                //find next lower resolution than near_width
                                                                 int d=100000;
                                                                 if(l->anfang(mit))do{
                                                                  if(mit->breite<near_width){
                                                                   if((int(near_width)-int(mit->breite))<d) d=int(near_width)-int(mit->breite);
                                                                  };
                                                                 }while(l->naechstes(mit));
                                                                 int nextlower=int(near_width)-d;
                                                                 if(l->anfang(mit))do{
                                                                  if(mit->breite==nextlower) selectionwidth.einhaengen(mit);
                                                                 }while(l->naechstes(mit));
                                                                };

                                                                //get selection by maximum color depth
                                                                _listenknoten<_grafikmodus>*lnmit;
                                                                if(selectionwidth.anzahl()>0){
                                                                 _liste<_grafikmodus> selectiondepth;
                                                                 int b=0;
                                                                 _grafikmodus*mode=0;
                                                                 if(selectionwidth.anfang(lnmit))do{
                                                                  if(int(lnmit->objekt()->tiefe)>b){
                                                                   b=int(lnmit->objekt()->tiefe);
                                                                  };
                                                                 }while(selectionwidth.naechstes(lnmit));
                                                                 if(selectionwidth.anfang(lnmit))do{
                                                                  if(lnmit->objekt()->tiefe==b) selectiondepth.einhaengen(lnmit->objekt());
                                                                 }while(selectionwidth.naechstes(lnmit));

                                                                 //get mode by minimum hertz
                                                                 _grafikmodus*bestmode=0;
                                                                 int h=100000;
                                                                 if(selectiondepth.anfang(lnmit))do{
                                                                  if(int(lnmit->objekt()->rate)<h){
                                                                   h=int(lnmit->objekt()->rate);
                                                                   bestmode=lnmit->objekt();
                                                                  };
                                                                 }while(selectiondepth.naechstes(lnmit));
                                                                 return(bestmode);
                                                                };
                                                                return(0);
};
//********************************************************************************************************************************************************************************
//                                                              G R A F I K D I R E C T X
//********************************************************************************************************************************************************************************
//vollbildmodus, nutzung interner hdc,hwmd,hrc, die grafik hat fensterkontrolle (groesse und position)
 _grafikdirectx::_grafikdirectx(void*ha,bool fullscreen,unsigned int x,unsigned int y,unsigned int width,unsigned int height,unsigned int depth,unsigned int rate,HINSTANCE hi,HINSTANCE prev): ::_grafik(fullscreen,x,y,width,height,depth,rate){
                                                                phandle=(HWND)ha;  
																paltebindung=0;
                                                                //pfullscreen=fullscreen;
                                                                //pfullscreenwidth=fullscreenwidth;
                                                                //pfullscreenheight=fullscreenheight;
                                                                //pfullscreendepth=fullscreendepth;
                                                                //pfullscreenrate=fullscreenrate;
                                                                phithis=hi;
                                                                phiprev=prev;
                                                                initialisieren();
 };

 _grafikdirectx::~_grafikdirectx(){
																loeschenbildhardwareliste();
                                                                //if(fensterkontrolle()){
                                                                 //ReleaseDC(handle,hdc);
                                                                // DestroyWindow(phandle);
                                                                //};
                                                                uninitialisieren();
 };
 bool _grafikdirectx::initialisieren(){
                                                                HRESULT     hr;    
                                                                //MSG         msg; 
                                                                //WNDCLASS    wc; 
                                                                //HACCEL      hAccelApp;
                                                                //HCURSOR     hcur = NULL;
                                                                int         ret = 0;
                                                                if( FAILED( hr = D3DXInitialize() ) ) MessageBoxA(NULL,"D3DX Initialization failed.","Dx7 constructor",MB_OK);

                                                                if(vollbildmodus()==false){
                                                                 D3DXCreateContextEx(   D3DX_DEFAULT,          
                                                                 0,
                                                                 phandle,
                                                                 NULL,                   // focusWnd
                                                                 D3DX_DEFAULT,           // colorbits
                                                                 D3DX_DEFAULT,           // alphabits
                                                                 D3DX_DEFAULT,           // numdepthbits
                                                                 0,                      // numstencilbits
                                                                 D3DX_DEFAULT,           // numbackbuffers
                                                                 breite(),				 // width
																 hoehe(),				 // height
                                                                 D3DX_DEFAULT,           // refresh rate
                                                                 &pcontext); 
                                                                }else{
                                                                 D3DXCreateContextEx(   D3DX_DEFAULT ,         
                                                                 D3DX_CONTEXT_FULLSCREEN, 
                                                                 phandle,
                                                                 NULL,                   // focusWnd
                                                                 tiefe(),           // colorbits
                                                                 D3DX_DEFAULT,           // alphabits
                                                                 D3DX_DEFAULT,           // numdepthbits
                                                                 0,                      // numstencilbits
                                                                 D3DX_DEFAULT,           // numbackbuffers
                                                                 breite(),
																 hoehe(),
                                                                 D3DX_DEFAULT,           // refresh rate
                                                                 &pcontext); 
                                                                };
                                                                //hatkontrolle=false;
                                                                pdevice=pcontext->GetD3DDevice();
                                                                if(pdevice==NULL) MessageBoxA(NULL,"Device not valid.","Dx7 constructor",MB_OK);
                                                                pd3d=pcontext->GetD3D();
                                                                if(pd3d==NULL) MessageBoxA(NULL,"D3D Device not valid.","Dx7 constructor",MB_OK);
                                                                pdd=pcontext->GetDD();
                                                                if(pdd==NULL) MessageBoxA(NULL,"DD Device not valid.","Dx7 constructor",MB_OK);
																if(D3D_OK != pdevice->GetCaps(&pcaps)) MessageBoxA(NULL,"Device Caps read error.","Dx7 constructor",MB_OK);
                                                                       
				                                                pdevice->SetRenderState(D3DRENDERSTATE_ALPHATESTENABLE,false);
				                                                pdevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE,true);
				                                                pdevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE,true);
				                                                pdevice->SetRenderState(D3DRENDERSTATE_ALPHAREF,0x080);
				                                                pdevice->SetRenderState(D3DRENDERSTATE_ALPHAFUNC,D3DCMP_GREATEREQUAL);
				                                                pdevice->SetRenderState(D3DRENDERSTATE_LIGHTING,false); 
				                                                
				                                                transparenzmultiplikativ();
				                                                
			                                                    pdevice->SetTextureStageState(0,D3DTSS_COLOROP,D3DTOP_MODULATE);
			                                                    pdevice->SetTextureStageState(0,D3DTSS_COLORARG1,D3DTA_TEXTURE);	
				                                                pdevice->SetTextureStageState(0,D3DTSS_COLORARG2,D3DTA_DIFFUSE);

   			                                                    pdevice->SetTextureStageState(0,D3DTSS_ALPHAOP,D3DTOP_MODULATE);
				                                                pdevice->SetTextureStageState(0,D3DTSS_ALPHAARG1,D3DTA_DIFFUSE);		                                                
				                                                pdevice->SetTextureStageState(0,D3DTSS_ALPHAARG2,D3DTA_TEXTURE);
				                                                                  
   			                                                  //  pdevice->SetTextureStageState(0,D3DTSS_ALPHAOP,D3DTOP_MODULATE);
				                                              //  pdevice->SetTextureStageState(0,D3DTSS_ALPHAARG1,D3DTA_DIFFUSE);		                                                
				                                              //  pdevice->SetTextureStageState(0,D3DTSS_ALPHAARG2,D3DTA_TEXTURE);
				                                                pdevice->SetRenderState(D3DRENDERSTATE_CULLMODE ,D3DCULL_CW);
				                                                return(true);                   
 };
 void _grafikdirectx::vollbildwechsel(bool full){
																vollbildmodus(full);
																reinitialisieren();
 };
 bool _grafikdirectx::unterstuetzttexturnichthochzwei(){ 
																//return(false);
																return(0 == (pcaps.dpcTriCaps.dwTextureCaps & D3DPTEXTURECAPS_POW2)); 
};

 bool _grafikdirectx::unterstuetzttexturrechteckig(){ 
																return(0 == (pcaps.dpcTriCaps.dwTextureCaps & D3DPTEXTURECAPS_SQUAREONLY)); 
};
 LPDIRECT3DDEVICE7 _grafikdirectx::device(){
                                                                return(pdevice);
 };
 LRESULT PASCAL _grafikdirectx::prozess(HWND hw,UINT m,WPARAM w,LPARAM l){
                                                                return(DefWindowProc(hw,m,w,l));                                                                        
 };
 void _grafikdirectx::fehler(char*l,HRESULT hr){
                                                                char errStr[100];
                                                                D3DXGetErrorString(hr,100,errStr);
                                                                MessageBoxA(NULL,errStr,l,MB_OK);
 };
 bool _grafikdirectx::validieren(){
                                                                // Call the app specific function to framemove (animate) the scene
                                                                // Check the cooperative level before rendering
                                                                if( DD_OK!=pdd->TestCooperativeLevel() ) {
                                                                 L->schreiben("VALIDATION IST NEGATIV");
																_bildhardware*bit;
                                                                 if(listebildhardware()->anfang(bit))do{
                                                                  bit->loeschen();
                                                                 }while(listebildhardware()->naechstes(bit));
                                                                 reinitialisieren();

                                                                };
                                                                /*

                                                                // FrameMove (animate) the scene
                                                                if( FAILED( App_FrameMove( g_pd3dDevice, timeGetTime() * 0.001f ) ) )
                                                                    return E_FAIL;

                                                                // Call the app specific function to render the scene
                                                                App_Render( g_pd3dDevice );

                                                                // Show the frame on the primary surface. Note: this is the best place to
                                                                // check for "lost" surfaces. Surfaces can be lost if something caused
                                                                // them to temporary lose their video memory. "Lost" surfaces simply
                                                                // need to be restored before continuing.
                                                                if( DDERR_SURFACELOST == ShowFrame() )
                                                                    RestoreSurfaces();

                                                                return S_OK;
                                                                */
                                                                return(true);
 };    
 HRESULT _grafikdirectx::modusgeaendert(){
																HRESULT hr;
																hr=pdd->TestCooperativeLevel();
																if(SUCCEEDED(hr)||hr==DDERR_WRONGMODE){
																 reinitialisieren();
																 L->schreiben("Grafik wurde reinitialisiert");
																 return(S_OK);
																}else if( hr!=DDERR_EXCLUSIVEMODEALREADYSET && hr!=DDERR_NOEXCLUSIVEMODE ){
																 // Busted!!
																 L->schreiben("Busted");
																 return hr;
																}
																return S_OK;
}

 void _grafikdirectx::setzen(bool fullscr,unsigned int wx,unsigned int wy,unsigned int de,unsigned int ra){
                                                                
																_grafik::groesse(wx,wy,de);
																vollbildmodus(fullscr);
																rate(ra);
                                                                reinitialisieren();
 };
 void _grafikdirectx::erzeugenschattenbild(){
 };                                                                
 void _grafikdirectx::gemeinsamedaten(_grafik*g){
 };
 void _grafikdirectx::aktivitaet(const bool b){
                                                                if(b) {
                                                                // wglMakeCurrent(hdc,hrc);
                                                                };
                                                                ::_grafik::aktivitaet(b);
 };

 bool _grafikdirectx::aktivitaet() const{
                                                                return( ::_grafik::aktivitaet());
 };

 void _grafikdirectx::groesse(unsigned int wx, unsigned int wy){
                                                                //if(fensterkontrolle()) SetWindowPos(phandle,0,(int)positionx(),(int)positiony(),wx,wy,0);

                                                                 if((pdd)&&(pdevice)){
                                                                // pdd->RestoreAllSurfaces();
                                                                 _bildhardware*bit;
                                                                 if(listebildhardware()->anfang(bit))do{
                                                                  bit->loeschen();
                                                                //  L->schreiben("G");
                                                                 }while(listebildhardware()->naechstes(bit));
                                                                // DWORD pass=1;
                                                                // if(pdevice->ValidateDevice(&pass)!=D3D_OK) L->schreiben("SHIT");
                                                                 //pcontext->DrawDebugText(0.8,0.5,D3DRGB(255,1,1),"test");;
                                                                 };

                                                                ::_grafik::groesse(wx,wy);
                                                                
                                                                if((wx>0)&&(wy>0)){
                                                                 HRESULT hr;
                                                                 if( FAILED(hr = pcontext->Resize(wx,wy))){
                                                                  fehler("grosse",hr);
                                                                  PostQuitMessage(0);
                                                                 };    
                                                                 
                                                                 pdevice=pcontext->GetD3DDevice();
                                                                 if(pdevice==NULL) MessageBoxA(NULL,"Device not valid.","Dx7 constructor",MB_OK);

                                                                 pd3d=pcontext->GetD3D();
                                                                 if(pd3d==NULL) MessageBoxA(NULL,"D3D Device not valid.","Dx7 constructor",MB_OK);

                                                                 pdd=pcontext->GetDD();
                                                                 if(pdd==NULL)MessageBoxA(NULL,"DD Device not valid.","Dx7 constructor",MB_OK);     
                                                                                                                            

                                                                };
                                                                                                               
                                                                //reinitialisieren();
 };
 void _grafikdirectx::position(_tg x,_tg y){
                                                                //if(fensterkontrolle()) SetWindowPos(phandle,0,(int)x,(int)y,groessex(),groessey(),0);
                                                                ::_grafik::position(x,y);
 };
 bool _grafikdirectx::uninitialisieren(){
	                                                             _bildhardware*bit;
                                                                 if(listebildhardware()->anfang(bit))do{
                                                                  bit->loeschen();
                                                                //  L->schreiben("G");
                                                                 }while(listebildhardware()->naechstes(bit));
                                                                if(pdevice){
                                                                 if(pdevice) pdevice->Release();
                                                                 if(pd3d) pd3d->Release();
                                                                 if(pdd) pdd->Release();
                                                                 if(pcontext) pcontext->Release();
                                                                 pdevice=NULL;
                                                                 pd3d=NULL;
                                                                 pdd=NULL;
                                                                 pcontext=NULL;
                                                                 D3DXUninitialize();
                                                                };
                                                                return(true);

};
bool _grafikdirectx::reinitialisieren(){
                                                                uninitialisieren();
                                                                return(initialisieren());
                                                                
};
bool _grafikdirectx::szenebeginn(){
                                                                HRESULT hr= pdevice->BeginScene();
                                                                 if ( SUCCEEDED(hr) ) return(true); else return(false);
};
void _grafikdirectx::szeneende(){
                                                                pdevice->EndScene();
};

//------------------------------------------------------------ Transformation ------------------------------------------------------------------------------------------------
void _grafikdirectx::ladenmatrixprojektion(_matrix44<_tm>*m){
                                                                pdevice->GetTransform(D3DTRANSFORMSTATE_PROJECTION,(LPD3DMATRIX)m->daten());
};
void _grafikdirectx::ladenmatrixwelt(_matrix44<_tm>*m){
                                                                pdevice->GetTransform(D3DTRANSFORMSTATE_WORLD,(LPD3DMATRIX)m->daten());
};
void _grafikdirectx::ladenmatrixmodell(_matrix44<_tm>*m){
                                                                pdevice->GetTransform(D3DTRANSFORMSTATE_VIEW,(LPD3DMATRIX)m->daten());
};
void _grafikdirectx::matrixprojektion(_matrix44<_tm>*m){
                                                                pdevice->SetTransform(D3DTRANSFORMSTATE_PROJECTION,(LPD3DMATRIX)m->daten());
};
void _grafikdirectx::matrixwelt(_matrix44<_tm>*m){
                                                                pdevice->SetTransform(D3DTRANSFORMSTATE_WORLD,(LPD3DMATRIX)m->daten());
};
void _grafikdirectx::matrixmodell(_matrix44<_tm>*m){
                                                                pdevice->SetTransform(D3DTRANSFORMSTATE_VIEW,(LPD3DMATRIX)m->daten());
};
void _grafikdirectx::orthonormal(){
                                                                _matrix44<float> mw;
                                                                _matrix44<float> mm;
                                                                _matrix44<float> mp;
                                                                D3DXMATRIX m;
                                                                D3DXMatrixOrtho(&m,float(groessex()),float(groessey()),-10,+10);
                                                             
                                                                mp.daten()[0]=m.m[0][0];
                                                                mp.daten()[1]=m.m[0][1];
                                                                mp.daten()[2]=m.m[0][2];
                                                                mp.daten()[3]=m.m[0][3];
                                                                
                                                                mp.daten()[4]=m.m[1][0];
                                                                mp.daten()[5]=m.m[1][1];
                                                                mp.daten()[6]=m.m[1][2];
                                                                mp.daten()[7]=m.m[1][3];
                                                                
                                                                mp.daten()[8]=m.m[2][0];
                                                                mp.daten()[9]=m.m[2][1];
                                                                mp.daten()[10]=m.m[2][2];
                                                                mp.daten()[11]=m.m[2][3];
                                                                
                                                                mp.daten()[12]=m.m[3][0];
                                                                mp.daten()[13]=m.m[3][1];
                                                                mp.daten()[14]=m.m[3][2];
                                                                mp.daten()[15]=m.m[3][3];

                                                                D3DXMatrixScaling(&m,1,-1,1);
                                                                _matrix44<float> mh;

                                                                mh.daten()[0]=m.m[0][0];
                                                                mh.daten()[1]=m.m[0][1];
                                                                mh.daten()[2]=m.m[0][2];
                                                                mh.daten()[3]=m.m[0][3];
                                                                
                                                                mh.daten()[4]=m.m[1][0];
                                                                mh.daten()[5]=m.m[1][1];
                                                                mh.daten()[6]=m.m[1][2];
                                                                mh.daten()[7]=m.m[1][3];
                                                                
                                                                mh.daten()[8]=m.m[2][0];
                                                                mh.daten()[9]=m.m[2][1];
                                                                mh.daten()[10]=m.m[2][2];
                                                                mh.daten()[11]=m.m[2][3];
                                                                
                                                                mh.daten()[12]=m.m[3][0];
                                                                mh.daten()[13]=m.m[3][1];
                                                                mh.daten()[14]=m.m[3][2];
                                                                mh.daten()[15]=m.m[3][3];
                                                                
                                                                mm*=mh;
                                                                float ggx=float(groessex());
                                                                float ggy=float(groessey());
                                                                ggx*=0.5;
                                                                ggy*=0.5;
                                                                _vektor3<float> hh(-ggx,ggy,0);
                                                                //_vektor3<float> hh(-512,384,0);
                                                                mm.verschieben(hh);

                                                                matrixwelt(&mw); 
                                                                matrixprojektion(&mp);
                                                                matrixmodell(&mm);
};
void _grafikdirectx::orthonormal(const _tg x0,const _tg x1,const _tg y0,const _tg y1,const _tg z0,const _tg z1){
};
void _grafikdirectx::transformierenrueck(const _vektor3<_tg>&geraet,_vektor3<_tg>&welt){
};
void _grafikdirectx::sichtbereich(_tg x,_tg y,_tg w,_tg h){
                                                                D3DVIEWPORT7 v;
                                                                v.dwX=DWORD(x);
                                                                v.dwY=DWORD(y);
                                                                v.dwWidth=DWORD(w);
                                                                v.dwHeight=DWORD(h); 
                                                                v.dvMinZ=0;
                                                                v.dvMaxZ=+1;
                                                               pdevice->SetViewport(&v);





                                                                _matrix44<float> mw;
                                                                _matrix44<float> mm;
                                                                _matrix44<float> mp;
                                                                D3DXMATRIX m;
                                                                D3DXMatrixOrtho(&m,float(w),float(h),-10,+10);
                                                             
                                                                mp.daten()[0]=m.m[0][0];
                                                                mp.daten()[1]=m.m[0][1];
                                                                mp.daten()[2]=m.m[0][2];
                                                                mp.daten()[3]=m.m[0][3];
                                                                
                                                                mp.daten()[4]=m.m[1][0];
                                                                mp.daten()[5]=m.m[1][1];
                                                                mp.daten()[6]=m.m[1][2];
                                                                mp.daten()[7]=m.m[1][3];
                                                                
                                                                mp.daten()[8]=m.m[2][0];
                                                                mp.daten()[9]=m.m[2][1];
                                                                mp.daten()[10]=m.m[2][2];
                                                                mp.daten()[11]=m.m[2][3];
                                                                
                                                                mp.daten()[12]=m.m[3][0];
                                                                mp.daten()[13]=m.m[3][1];
                                                                mp.daten()[14]=m.m[3][2];
                                                                mp.daten()[15]=m.m[3][3];

                                                                D3DXMatrixScaling(&m,1,-1,1);
                                                                _matrix44<float> mh;

                                                                mh.daten()[0]=m.m[0][0];
                                                                mh.daten()[1]=m.m[0][1];
                                                                mh.daten()[2]=m.m[0][2];
                                                                mh.daten()[3]=m.m[0][3];
                                                                
                                                                mh.daten()[4]=m.m[1][0];
                                                                mh.daten()[5]=m.m[1][1];
                                                                mh.daten()[6]=m.m[1][2];
                                                                mh.daten()[7]=m.m[1][3];
                                                                
                                                                mh.daten()[8]=m.m[2][0];
                                                                mh.daten()[9]=m.m[2][1];
                                                                mh.daten()[10]=m.m[2][2];
                                                                mh.daten()[11]=m.m[2][3];
                                                                
                                                                mh.daten()[12]=m.m[3][0];
                                                                mh.daten()[13]=m.m[3][1];
                                                                mh.daten()[14]=m.m[3][2];
                                                                mh.daten()[15]=m.m[3][3];
                                                                
                                                                mm*=mh;
                                                                float ggx=float(w);
                                                                float ggy=float(h);
                                                                ggx*=0.5;
                                                                ggy*=0.5;
                                                                _vektor3<float> hh(-ggx-float(x),ggy+float(y),0);
                                                                //_vektor3<float> hh(-512,384,0);
                                                                mm.verschieben(hh);

                                                                matrixwelt(&mw); 
                                                                matrixprojektion(&mp);
                                                                matrixmodell(&mm);








                                                          /*  pdevice->SetRenderState(D3DRENDERSTATE_CLIPPING,true);
                                                                D3DCLIPSTATUS d;
                                                                
                                                                d.dwFlags=D3DCLIPSTATUS_STATUS;
                                                                d.dwStatus=D3DSTATUS_DEFAULT;
                                                                d.minx=x;
                                                                d.maxx=x+w;
                                                                d.miny=y;
                                                                d.maxy=y+h;
                                                                pdevice->SetClipStatus(&d);*/
                                                                
                                                                
};

//------------------------------------------------------------ Texturen und Einheiten ----------------------------------------------------------------------------------------
void _grafikdirectx::textureinheit(unsigned int i){
};
void _grafikdirectx::texturoperationadditiv(){
};
void _grafikdirectx::texturoperationmultiplikativ(){
};
 
void _grafikdirectx::textur(const bool b){
                                                                if(b){
			                                                    pdevice->SetTextureStageState(0,D3DTSS_COLOROP,D3DTOP_MODULATE);
			                                                    pdevice->SetTextureStageState(0,D3DTSS_COLORARG1,D3DTA_TEXTURE);	
				                                                pdevice->SetTextureStageState(0,D3DTSS_COLORARG2,D3DTA_DIFFUSE);

   			                                                    pdevice->SetTextureStageState(0,D3DTSS_ALPHAOP,D3DTOP_MODULATE);
				                                                pdevice->SetTextureStageState(0,D3DTSS_ALPHAARG1,D3DTA_DIFFUSE);		                                                
				                                                pdevice->SetTextureStageState(0,D3DTSS_ALPHAARG2,D3DTA_TEXTURE);                                                                 
                                                                 
                                                                 
                                                                }else{
                                                                 pdevice->SetTexture(0,NULL);
                                                                 paltebindung=0;
			                                                    pdevice->SetTextureStageState(0,D3DTSS_COLOROP,D3DTOP_SELECTARG1);
			                                                    pdevice->SetTextureStageState(0,D3DTSS_COLORARG1,D3DTA_DIFFUSE);	
				                                               // pdevice->SetTextureStageState(0,D3DTSS_COLORARG2,D3DTA_DIFFUSE);

   			                                                    pdevice->SetTextureStageState(0,D3DTSS_ALPHAOP,D3DTOP_SELECTARG2);
				                                                pdevice->SetTextureStageState(0,D3DTSS_ALPHAARG1,D3DTA_DIFFUSE);		                                                
				                                                //pdevice->SetTextureStageState(0,D3DTSS_ALPHAARG2,D3DTA_DIFFUSE);                                                                 
                                                                };
                                                                
};
 
 
 void _grafikdirectx::erzeugentexturen(_listebasis<_textur<_tb> >*tl){
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

 void _grafikdirectx::erzeugenbilder(_liste<_bild<_tb> >*ml){
                                                                _listenknoten<_bild<_tb> >*mit;
                                                                //--------------
                                                                if(ml->anfang(mit))do{
                                                                 erzeugenbild(mit->objekt());
                                                                }while(ml->naechstes(mit));
 };

 void _grafikdirectx::erzeugenbild(_bild<_tb>*mit){
                                                                mit->loeschenbildhardware();
                                                                mit->bildhardware(new _bildhardwaredirectx(this,mit));
 };                                                                   

 void _grafikdirectx::loeschentexturen(_listebasis<_textur<_tb> >*tl){
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

 void _grafikdirectx::loeschenbilder(_liste<_bild<_tb> >*ml){
                                                                _listenknoten<_bild<_tb> >*mit;
                                                                //--------------
                                                                if(ml->anfang(mit))do{
                                                                 loeschenbild(mit->objekt());
                                                                }while(ml->naechstes(mit));
 };

 void _grafikdirectx::loeschenbild(_bild<_tb>*mit){
                                                                mit->loeschenbildhardware();
 };                                                                   

 void _grafikdirectx::bindenbild(_bild<_tb>*m){
                                                                if(m->bildhardware()==0) m->bildhardware(new _bildhardwaredirectx(this,m));
                                                               // if(paltebindung!=m->bildhardware()) {
                                                                 m->bildhardware()->binden();
                                                                 if((m->wiederholung(0))||(m->wiederholung(1))){
				                                                  pdevice->SetTextureStageState(0,D3DTSS_ADDRESS,D3DTADDRESS_WRAP);
                                                                 }else{
				                                                  pdevice->SetTextureStageState(0,D3DTSS_ADDRESS,D3DTADDRESS_CLAMP);
				                                                 };
				                                                pdevice->SetTextureStageState(0,D3DTSS_MAGFILTER,D3DTFG_LINEAR);
				                                                pdevice->SetTextureStageState(0,D3DTSS_MINFILTER,D3DTFN_LINEAR);
				                                                pdevice->SetTextureStageState(0,D3DTSS_MIPFILTER,D3DTFP_LINEAR);			                                                                                                                                                        
                                                                 
                                                               // };
 };

 
 
 
 
//------------------------------------------------------------ Material und Livht ------------------------------------------------------------------------------------------------------
void _grafikdirectx::licht(const unsigned int i,const bool b){  
}; 
  
void _grafikdirectx::beleuchtung(const bool b){
};
bool _grafikdirectx::beleuchtung()const{
                                                                return(false);
};
void _grafikdirectx::beleuchtungflach(){
};
void _grafikdirectx::beleuchtungrund(){
};
void _grafikdirectx::material(const bool b){
};
void _grafikdirectx::materialfarbe(const _vektor4<_to>&){
};

void _grafikdirectx::materialemission(const _vektor4<_to>&){
};

void _grafikdirectx::materialglanz(const _vektor4<_to>&){
};

void _grafikdirectx::materialglanzbreite(_tg){
};
//------------------------------------------------------------ Ausschuss -----------------------------------------------------------------------------------------------------
void _grafikdirectx::ausschussflaeche(const bool b){
                                                                if(!b){
                                                                 pdevice->SetRenderState(D3DRENDERSTATE_CULLMODE ,D3DCULL_NONE);
                                                                }else{
                                                                 pdevice->SetRenderState(D3DRENDERSTATE_CULLMODE ,D3DCULL_CW);
                                                                };
};
void _grafikdirectx::ausschussflaechefront(){
};
void _grafikdirectx::ausschussflaecherueck(){
};
//------------------------------------------------------------ Buffer --------------------------------------------------------------------------------------------------------
bool _grafikdirectx::allebufferloeschen(){
                                                                HRESULT hr = pcontext->Clear(D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER);
																if(FAILED(hr)) return(false);
																return(true);
                                                                
                                                                
};
void _grafikdirectx::anzeigebufferloeschfarbe(const _to r,const _to g,const _to b,const _to a){
																 pcontext->SetClearColor(D3DRGBA(r,g,b,a));
																
                                                                
};
void _grafikdirectx::anzeigebufferumschalten(const bool sync){
																HRESULT hr;
                                                                if(sync) hr=pcontext->UpdateFrame(0); else hr=pcontext->UpdateFrame(-1);

																//HRESULT hr=->pcontext->UpdateFrame(DDFLIP_NOVSYNC);
																if(hr==DDERR_SURFACELOST||hr==DDERR_SURFACEBUSY) hr=modusgeaendert();

};
void _grafikdirectx::anzeigebufferschreiben(const bool b){
};                                                                
void _grafikdirectx::tiefenbufferkondition(const bool b){
                                                                if(b){
                                                                 pdevice->SetRenderState(D3DRENDERSTATE_ZENABLE,D3DZB_TRUE);
                                                                }else{
                                                                 pdevice->SetRenderState(D3DRENDERSTATE_ZENABLE,D3DZB_FALSE);
                                                                };
};
void _grafikdirectx::tiefenbufferschreiben(const bool b){
                                                                if(b){
				                                                 pdevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE,D3DZB_TRUE);
                                                                }else{
				                                                 pdevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE,D3DZB_FALSE);
                                                                };
};
void _grafikdirectx::tiefenbufferkonditiongleich(){
};
void _grafikdirectx::tiefenbufferkonditionkleiner(){
}; 
void _grafikdirectx::tiefenbufferkonditionkleinergleich(){
};
void _grafikdirectx::schablonenbufferkondition(const bool b){
};
void _grafikdirectx::schablonenbufferkonditiongleich(const int ref,const unsigned int mask){
};
void _grafikdirectx::schablonenbufferkonditionungleich(const int ref,const unsigned int mask){
};
void _grafikdirectx::schablonenbufferkonditionimmer(const int ref,const unsigned int mask){
};
void _grafikdirectx::schablonenbufferoperation(const int fail,const signed int zfail,const signed int zpass){
};
void _grafikdirectx::schablonenbufferloeschen(){
};
void _grafikdirectx::schablonenbufferschreiben(const bool b){
};
 
void _grafikdirectx::maske(const bool b){
};                                                                  
//------------------------------------------------------------ Nebel ---------------------------------------------------------------------------------------------------------
void _grafikdirectx::nebel(bool b){
                                                                if(b){
                                                                 pdevice->SetRenderState(D3DRENDERSTATE_FOGENABLE,TRUE);
                                                                }else{
                                                                 pdevice->SetRenderState(D3DRENDERSTATE_FOGENABLE,false);
                                                                };
														//		pdevice->SetRenderState(D3DRENDERSTATE_RANGEFOGENABLE,TRUE);


};
void _grafikdirectx::nebelmodus(unsigned int i){
																if(i==0) {
																 pdevice->SetRenderState(D3DRENDERSTATE_FOGVERTEXMODE, D3DFOG_LINEAR);
																}else{
																  pdevice->SetRenderState(D3DRENDERSTATE_FOGVERTEXMODE, D3DFOG_EXP2);
																};

};
void _grafikdirectx::nebelfarbe(const _vektor4<_to>&r){
																pdevice->SetRenderState(D3DRENDERSTATE_FOGCOLOR,r.intargb());
};
void _grafikdirectx::nebeldichte(_tg d){
																float f=(float)d;
																pdevice->SetRenderState(D3DRENDERSTATE_FOGDENSITY, *(DWORD *)(&f));

};
void _grafikdirectx::nebeldistanz(_tg min,_tg max){
																pdevice->SetRenderState(D3DRENDERSTATE_FOGSTART, *(DWORD *)(&min));
																pdevice->SetRenderState(D3DRENDERSTATE_FOGEND,   *(DWORD *)(&max));

};
//------------------------------------------------------------ Zeichnungsstatus -----------------------------------------------------------------------------------------------
void _grafikdirectx::transparenz(const bool b){
                                                                if(b){
                                                                 pdevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE,true);
                                                                }else{
                                                                 pdevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE,false);
                                                                };
};
void _grafikdirectx::transparenzadditiv(){
				                                                pdevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE,true);
				                                                pdevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);
   				                                                pdevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_ONE); 
};
void _grafikdirectx::transparenzmultiplikativ(){




				                                                pdevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE,true);
				                                                pdevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);
   				                                                pdevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);
};
void _grafikdirectx::polygonverschiebung(const bool b){
};
void _grafikdirectx::polygonverschiebung(const _tg a,const _tg b){
};
//------------------------------------------------------------ Zeichnung ------------------------------------------------------------------------------------------------------
void _grafikdirectx::vollbild(const _vektor4<_to>&c){
};
void _grafikdirectx::pixel(const _vektor3<_tg>&x,const _vektor4<_to>&c){
};
void _grafikdirectx::linie(const _vektor3<_tg>&x,const _vektor3<_tg>&y,const _vektor4<_to>&c){
                                                               float f[8];
                                                                __int32*i=(__int32*)f;
                                                                __int32 col=c.intargb();
                                                                f[0]=float(x[0]);
                                                                f[1]=float(x[1]);
                                                                f[2]=float(x[2]);
                                                                i[3]=col;
                                                                f[4]=float(y[0]);
                                                                f[5]=float(y[1]);
                                                                f[6]=float(y[2]);
                                                                i[7]=col;
                                                                pdevice->DrawPrimitive(D3DPT_LINELIST,D3DFVF_XYZ|D3DFVF_DIFFUSE,f,2,0);
};
void _grafikdirectx::kugel(const _vektor3<_tg>&o,const _vektor4<_to>&c,const _tg radius,const unsigned int resx,const unsigned int resy){ 
};			                      
void _grafikdirectx::polygon(_liste<_vektor3<_tg> >*l){
};
void _grafikdirectx::polygon(_liste<_vektor3<_tg> >*l,const _vektor4<_to>&col){
};
void _grafikdirectx::rechteck(_bild<_tb>*b,_tg x,_tg y,_tg w,_tg h,const _vektor4<_to>&c,bool inversetexy){
																//L->l("_grafikdirectx::rechteck : textur soll eingeschaltet werden");
																textur(true);
																//L->l("_grafikdirectx::rechteck : textur soll gebunden werden");
                                                               bindenbild(b);
															   //		L->l("_grafikdirectx::rechteck : textur soll gezeichnet werden");

															   _tg xs=1;
															   _tg ys=1;
															   if(b->bildhardware()){
															    xs=b->bildhardware()->skalierungx();
															    ys=b->bildhardware()->skalierungy();
															   };
                                                               float f[4*6];
                                                                __int32 col=c.intargb();
                                                                __int32*i=(__int32*)f;
                                                                f[0]=float(x);
                                                                f[1]=float(y);
                                                                f[2]=0;
                                                                i[3]=col;
                                                                    
                                                                f[6]=float(x+w);
                                                                f[7]=float(y);
                                                                f[8]=0;
                                                                i[9]=col;
                                                                
                                                                f[12]=float(x+w);
                                                                f[13]=float(y+h);
                                                                f[14]=0;
                                                                i[15]=col;
                                                                
                                                                f[18]=float(x);
                                                                f[19]=float(y+h);
                                                                f[20]=0;
                                                                i[21]=col;
                                                                if(inversetexy){
                                                                 f[4]=float(0*xs);
                                                                 f[5]=float(1*ys);
                                                                 f[10]=float(1*xs);
                                                                 f[11]=float(1*ys);
                                                                 f[16]=float(1*xs);
                                                                 f[17]=float(0*ys);
                                                                 f[22]=float(0*xs);
                                                                 f[23]=float(0*ys);
                                                                }else{
                                                                 f[4]=float(0*xs);
                                                                 f[5]=float(0*ys);
                                                                 f[10]=float(1*xs);
                                                                 f[11]=float(0*ys);
                                                                 f[16]=float(1*xs);
                                                                 f[17]=float(1*ys);
                                                                 f[22]=float(0*xs);
                                                                 f[23]=float(1*ys);
                                                                };
                                                                
                                                                
                                                                
                                                                pdevice->DrawPrimitive(D3DPT_TRIANGLEFAN,D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1,f,4,0);
                                                                
};
void _grafikdirectx::rechteck(_tg x,_tg y,_tg w,_tg h,const _vektor4<_to>&c){
																textur(false);
                                                               float f[4*4];
                                                                __int32*i=(__int32*)f;
                                                                __int32 col=c.intargb();
                                                                f[0]=float(x);
                                                                f[1]=float(y);
                                                                f[2]=0;
                                                                i[3]=col;
                                                                f[4]=float(x+w);
                                                                f[5]=float(y);
                                                                f[6]=0;
                                                                i[7]=col;
                                                                f[8]=float(x+w);
                                                                f[9]=float(y+h);
                                                                f[10]=0;
                                                                i[11]=col;
                                                                f[12]=float(x);
                                                                f[13]=float(y+h);
                                                                f[14]=0;
                                                                i[15]=col;
                                                                pdevice->DrawPrimitive(D3DPT_TRIANGLEFAN,D3DFVF_XYZ|D3DFVF_DIFFUSE,f,4,0);
};
void _grafikdirectx::rechtecke(_liste<_vektor3<_tg> >*l){
};                                                                 
void _grafikdirectx::rechtecke(_liste<_vektor3<_tg> >*l,const _vektor4<_to>&col){
}; 
void _grafikdirectx::rechteckstreifenzyklisch(_liste<_vektor3<_tg> >*l){
};
void _grafikdirectx::rechteckstreifenzyklisch(_liste<_vektor3<_tg> >*l0,_liste<_vektor3<_tg> >*l1){
};
void _grafikdirectx::rechteckstreifenzyklisch(_liste<_vektor3<_tg> >*l,const _vektor4<_to>&col){
};
void _grafikdirectx::rechteckstreifenzyklisch(_liste<_vektor3<_tg> >*l0,_liste<_vektor3<_tg> >*l1,const _vektor4<_to>&col){
};
void _grafikdirectx::text(const _zeichenkette<_tt>&s,const ::_zeichensatz*z,const _vektor3<_tg>&o,const _vektor4<_to>&c){
};
void _grafikdirectx::zeichnen(const _vektor3<_tg>&x,const _vektor4<_to>&c){
};                              
void _grafikdirectx::zeichnen(_tg*x,_to*c){
};
void _grafikdirectx::zeichnen(_tg*x,_tg*y,_to*c){
};
void _grafikdirectx::zeichnen(const _vektor3<_tg>&x,const _vektor3<_tg>&y,const _vektor4<_to>&c){
                                                               float f[8];
                                                                __int32*i=(__int32*)f;
                                                                __int32 col=c.intargb();
                                                                f[0]=float(x[0]);
                                                                f[1]=float(x[1]);
                                                                f[2]=float(x[2]);
                                                                i[3]=col;
                                                                f[4]=float(y[0]);
                                                                f[5]=float(y[1]);
                                                                f[6]=float(y[2]);
                                                                i[7]=col;
                                                                pdevice->DrawPrimitive(D3DPT_LINELIST,D3DFVF_XYZ|D3DFVF_DIFFUSE,f,2,0);

};                                                               
//linie
void _grafikdirectx::zeichnen(const _vektor3<_tg>&x,const _vektor3<_tg>&y,const _vektor4<_to>&c0,const _vektor4<_to>&c1){
                                                               
                                                               float f[8];
                                                                __int32*i=(__int32*)f;
                                                                __int32 colx=c0.intargb();
                                                                __int32 coly=c1.intargb();
                                                                f[0]=float(x[0]);
                                                                f[1]=float(x[1]);
                                                                f[2]=float(x[2]);
                                                                i[3]=colx;
                                                                f[4]=float(y[0]);
                                                                f[5]=float(y[1]);
                                                                f[6]=float(y[2]);
                                                                i[7]=coly;
                                                                pdevice->DrawPrimitive(D3DPT_LINELIST,D3DFVF_XYZ|D3DFVF_DIFFUSE,f,2,0);

}; 
//dreieck ohne texcoords
void _grafikdirectx::zeichnen(const _vektor3<_tg>&p0,const _vektor3<_tg>&p1,const _vektor3<_tg>&p2,const _vektor4<_to>&c0,const _vektor4<_to>&c1,const _vektor4<_to>&c2){
};                                                               
//dreieck MIT texcoords
void _grafikdirectx::zeichnen(const _vektor3<_tg>&p0,const _vektor3<_tg>&p1,const _vektor3<_tg>&p2,const _vektor4<_to>&c0,const _vektor4<_to>&c1,const _vektor4<_to>&c2,const _vektor2<_tg>&tc0,const _vektor2<_tg>&tc1,const _vektor2<_tg>&tc2){
                                                               float f[6*3];
                                                               __int32*i=(__int32*)f;
															   _tg xs=1;
															   _tg ys=1;
															   if(paltebindung){
																xs=paltebindung->skalierungx();
																ys=paltebindung->skalierungy();
															   };
                                                                f[0+0]=float(p0[0]);
                                                                f[0+1]=float(p0[1]);
                                                                f[0+2]=float(p0[2]);
                                                                i[0+3]=c0.intargb();
                                                                f[0+4]=float(tc0[0]*xs);
                                                                f[0+5]=float(tc0[1]*ys);
                                                                    
                                                                f[6+0]=float(p1[0]);
                                                                f[6+1]=float(p1[1]);
                                                                f[6+2]=float(p1[2]);
                                                                i[6+3]=c1.intargb();
                                                                f[6+4]=float(tc1[0]*xs);
                                                                f[6+5]=float(tc1[1]*ys);
                                                                
                                                                f[12+0]=float(p2[0]);
                                                                f[12+1]=float(p2[1]);
                                                                f[12+2]=float(p2[2]);
                                                                i[12+3]=c2.intargb();
                                                                f[12+4]=float(tc2[0]*xs);
                                                                f[12+5]=float(tc2[1]*ys);
                                                                pdevice->DrawPrimitive(D3DPT_TRIANGLELIST,D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1,f,3,0);          
}; 
//dreieck MIT multitexcoords
void _grafikdirectx::zeichnen(const _vektor3<_tg>&p0,
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
};                                                               
//dreieck MIT multitexcoords
void _grafikdirectx::zeichnen(const _vektor3<_tg>&p0,
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
};                                                               
void _grafikdirectx::zeichnen(const _vektor3<_tg>&p0,
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
															   _tg xs=1;
															   _tg ys=1;
															   if(paltebindung){
																xs=paltebindung->skalierungx();
																ys=paltebindung->skalierungy();
															   };
                                                               float f[6*3];
                                                                __int32*i=(__int32*)f;
                                                                f[0+0]=float(p0[0]);
                                                                f[0+1]=float(p0[1]);
                                                                f[0+2]=float(p0[2]);
                                                                i[0+3]=c0.intargb();
                                                                f[0+4]=float(tc0[0]*xs);
                                                                f[0+5]=float(tc0[1]*ys);
                                                                    
                                                                f[6+0]=float(p1[0]);
                                                                f[6+1]=float(p1[1]);
                                                                f[6+2]=float(p1[2]);
                                                                i[6+3]=c1.intargb();
                                                                f[6+4]=float(tc1[0]*xs);
                                                                f[6+5]=float(tc1[1]*ys);
                                                                
                                                                f[12+0]=float(p2[0]);
                                                                f[12+1]=float(p2[1]);
                                                                f[12+2]=float(p2[2]);
                                                                i[12+3]=c2.intargb();
                                                                f[12+4]=float(tc2[0]*xs);
                                                                f[12+5]=float(tc2[1]*ys);
                                                                pdevice->DrawPrimitive(D3DPT_TRIANGLELIST,D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1,f,3,0);          


};                                           
void _grafikdirectx::zeichnen(const _vektor3<_tg>&p0,
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
															   _tg xs=1;
															   _tg ys=1;
															   if(paltebindung){
																xs=paltebindung->skalierungx();
																ys=paltebindung->skalierungy();
															   };
                                           
                                                               float f[6*3];
                                                                __int32*i=(__int32*)f;
                                                                f[0+0]=float(p0[0]);
                                                                f[0+1]=float(p0[1]);
                                                                f[0+2]=float(p0[2]);
                                                                i[0+3]=c0.intargb();
                                                                f[0+4]=float(tc0[0]*xs);
                                                                f[0+5]=float(tc0[1]*ys);
                                                                    
                                                                f[6+0]=float(p1[0]);
                                                                f[6+1]=float(p1[1]);
                                                                f[6+2]=float(p1[2]);
                                                                i[6+3]=c1.intargb();
                                                                f[6+4]=float(tc1[0]*xs);
                                                                f[6+5]=float(tc1[1]*ys);
                                                                
                                                                f[12+0]=float(p2[0]);
                                                                f[12+1]=float(p2[1]);
                                                                f[12+2]=float(p2[2]);
                                                                i[12+3]=c2.intargb();
                                                                f[12+4]=float(tc2[0]*xs);
                                                                f[12+5]=float(tc2[1]*ys);
                                                                pdevice->DrawPrimitive(D3DPT_TRIANGLELIST,D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1,f,3,0);          
};                                           
void _grafikdirectx::zeichnen(const _vektor3<_tg>&p0,
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
};                                           
void _grafikdirectx::zeichnendebug(const _vektor3<_tg>&p0,const _vektor3<_tg>&p1,const _vektor3<_tg>&p2,const _vektor4<_to>&c0,const _vektor4<_to>&c1,const _vektor4<_to>&c2){
};                                     
void _grafikdirectx::zeichnenabgeschnitten(const _vektor3<_tg>&,const _vektor4<_to>&){};
void _grafikdirectx::zeichnenabgeschnitten(const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor4<_to>&){};
//-----------------------------------------------------------------------------
// Name: TextureSearchCallback()
// Desc: Enumeration callback routine to find a 16-bit texture format. This
//       function is invoked by the ID3DDevice::EnumTextureFormats() function
//       to sort through all the available texture formats for a given device.
//       The pixel format of each enumerated texture format is passed into the
//       "pddpf" parameter. The 2nd parameter is to be used however the app
//       sees fit. In this case, we are using it as an output parameter to 
//       return a normal 16-bit texture format.
//-----------------------------------------------------------------------------
static HRESULT CALLBACK TextureSearchCallback( DDPIXELFORMAT* pddpf,VOID* param ){
                                                                // Note: Return with DDENUMRET_OK to continue enumerating more formats.
                                                                // Skip any funky modes
                                                                if(pddpf->dwFlags&(DDPF_LUMINANCE|DDPF_BUMPLUMINANCE|DDPF_BUMPDUDV) )return DDENUMRET_OK;
                                                                // Skip any FourCC formats
                                                                if(pddpf->dwFourCC != 0 )return DDENUMRET_OK;
                                                                // Skip alpha modes
                                                                if(pddpf->dwFlags&DDPF_ALPHAPIXELS)return DDENUMRET_OK;
                                                                // We only want 16-bit formats, so skip all others
                                                                if(pddpf->dwRGBBitCount!=16)return DDENUMRET_OK;
                                                                // We found a good match. Copy the current pixel format to our output
                                                                // parameter
                                                                memcpy( (DDPIXELFORMAT*)param, pddpf, sizeof(DDPIXELFORMAT) );
                                                                // Return with DDENUMRET_CANCEL to end enumeration.
                                                                return DDENUMRET_CANCEL;
};
/*

 // =========================================== 
//  To enumerate the Texture-Formats (static) 
// =========================================== 
static HRESULT WINAPI enumTextureFormats(DDPIXELFORMAT *format, void *dest) 
{ 
   if((format->dwFlags & DDPF_RGB) && (format->dwFlags & DDPF_ALPHAPIXELS) && 32 == format->dwRGBBitCount) 
     { 
        memcpy(dest, format, sizeof(DDPIXELFORMAT)); 
        for(int32 i = 0; i < 32; i += 8) 
          { 
             if((255 << i) == format->dwRBitMask) 
               s_rShift = i; 
             if((255 << i) == format->dwGBitMask) 
               s_gShift = i; 
             if((255 << i) == format->dwBBitMask) 
               s_bShift = i; 
             if((255 << i) == format->dwRGBAlphaBitMask) 
               s_aShift = i; 
          } 
        return(D3DENUMRET_CANCEL); 
     } 
    
   return(D3DENUMRET_OK); 
} 

 
// ========================================= 
//  Get a supported Texture-Format (static) 
// ========================================= 
static DDPIXELFORMAT *getTextureFormat() 
{ 
   static DDPIXELFORMAT  format; 
   static bool           pixelFormatFound = false; 
   if(!pixelFormatFound) 
     { 
        g_D3DDevice->EnumTextureFormats(enumTextureFormats, &format); 
        pixelFormatFound = true; 
     } 
   return(&format); 
}


bool Texture::upload(Image const *image) 
{ 
   int32  realWidth = image->getWidth(), realHeight = image->getHeight(); 
    
    
   _width  = image->getWidth(); 
   _height = image->getHeight(); 
    
   // Test if we need Power-of-Two-Textures 
   if(!nonPowerOfTwoTexturesSupported()) 
     { 
        for(int32 i = 1; ; i <<= 1) 
          { 
             if(i >= image->getWidth()) 
               { 
                  realWidth = i; 
                  break; 
               } 
          } 
         
        for(int32 i = 1; ; i <<= 1) 
          { 
             if(i >= image->getHeight()) 
               { 
                  realHeight = i; 
                  break; 
               } 
          } 
     } 
    
   // Test if we need square Textures 
   if(!rectangularTexturesSupported()) 
     realWidth = realHeight = max(realWidth, realHeight); 
    
   // Create our DirectDraw-Surface 
   DDSURFACEDESC2  ddsd; 
   ZeroMemory(&ddsd, sizeof(DDSURFACEDESC2)); 
   ddsd.dwSize          = sizeof(DDSURFACEDESC2); 
   ddsd.dwFlags         = DDSD_WIDTH | DDSD_HEIGHT | DDSD_CAPS | DDSD_PIXELFORMAT | DDSD_TEXTURESTAGE; 
   ddsd.ddsCaps.dwCaps  = DDSCAPS_TEXTURE; 
   ddsd.dwWidth         = realWidth; 
   ddsd.dwHeight        = realHeight; 
   ddsd.ddsCaps.dwCaps2 = DDSCAPS2_TEXTUREMANAGE; 
   memcpy(&ddsd.ddpfPixelFormat, getTextureFormat(), sizeof(DDPIXELFORMAT)); 
    
   // Release our old Surface 
   if(_surface) 
     _surface->Release(); 
    
   // Create a new Surface 
   if(DD_OK != g_DD->CreateSurface(&ddsd, &_surface, NULL)) 
     return(false); 
    
   // Blit our Image into the Surface 
   if(blitToSurface(ddsd, image)) 
     { 
        _minU = 0.5f / float32(realWidth); 
        _minV = 0.5f / float32(realHeight); 
        _maxU = _minU + image->getWidth()  / float32(realWidth); 
        _maxV = _minV + image->getHeight() / float32(realHeight); 
        return(true); 
     } 
   else 
     { 
        _surface->Release(); 
        _surface = 0; 
        return(false); 
     } 
}


bool Texture::blitToSurface(DDSURFACEDESC2 &ddsd, Image const *image) 
{ 
   if(DD_OK == _surface->Lock(NULL, &ddsd, DDLOCK_WAIT | DDLOCK_WRITEONLY, NULL)) 
     { 
        uint32       r, g, b, a; 
        uint32       *dest = (uint32 *)ddsd.lpSurface; 
        uint32       step = (ddsd.lPitch >> 2) - ddsd.dwWidth + (ddsd.dwWidth - image->getWidth()); 
        uint8 const  *src = image->getData(); 
         
        for(int32 y = 0; y < image->getHeight(); y++) 
          { 
             for(int32 x = 0; x < image->getWidth(); x++) 
               { 
                  r = *(src++); 
                  g = *(src++); 
                  b = *(src++); 
                  if(3 == image->getNumComponents()) 
                    a = 255; 
                  else 
                    a = *(src++); 
                  *(dest++) = (r << s_rShift) | (g << s_gShift) | (b << s_bShift) | (a << s_aShift); 
               } 
              
             if(uint32(image->getWidth()) < ddsd.dwWidth) 
               memset(dest, 0, (ddsd.dwWidth - uint32(image->getWidth())) << 2); 
              
             dest += step; 
          } 
         
        for(uint32 y = image->getHeight(); y < ddsd.dwHeight; y++) 
          { 
             memset(dest, 0, ddsd.dwWidth << 2); 
             dest += ddsd.lPitch >> 2; 
          } 
         
        _surface->Unlock(NULL); 
        return(true); 
     } 
    
   return(false); 
}
*/



                                                                  /*
                                                                  //-------------------------
                                                                  D3DDEVICEDESC7 ddDesc;
                                                                  if( FAILED( pgrafik->device()->GetCaps( &ddDesc ) ) ) return(false);
                                                                  DWORD dwWidth  = (DWORD)pbild->groesse(0);
                                                                  DWORD dwHeight = (DWORD)pbild->groesse(1);
                                                                  // Setup the new surface desc for the texture. Note how we are using the
                                                                  // texture manage attribute, so Direct3D does alot of dirty work for us
                                                                  DDSURFACEDESC2 ddsd;
                                                                  ZeroMemory( &ddsd, sizeof(DDSURFACEDESC2) );
                                                                  ddsd.dwSize          = sizeof(DDSURFACEDESC2);
                                                                  ddsd.dwFlags         = DDSD_CAPS|DDSD_HEIGHT|DDSD_WIDTH|DDSD_PIXELFORMAT|DDSD_TEXTURESTAGE;
                                                                  ddsd.ddsCaps.dwCaps  = DDSCAPS_TEXTURE;
                                                                  ddsd.dwWidth         = dwWidth;
                                                                  ddsd.dwHeight        = dwHeight;  
                                                                  // Turn on texture management for hardware devices
                                                                  if(ddDesc.deviceGUID==IID_IDirect3DHALDevice) ddsd.ddsCaps.dwCaps2 = DDSCAPS2_TEXTUREMANAGE;
                                                                  else if(ddDesc.deviceGUID==IID_IDirect3DTnLHalDevice) ddsd.ddsCaps.dwCaps2 = DDSCAPS2_TEXTUREMANAGE;
                                                                  else ddsd.ddsCaps.dwCaps|=DDSCAPS_SYSTEMMEMORY;     
                                                                  // Adjust width and height, if the driver requires it
                                                                  if(ddDesc.dpcTriCaps.dwTextureCaps & D3DPTEXTURECAPS_POW2){
                                                                   for(ddsd.dwWidth=1;dwWidth>ddsd.dwWidth;ddsd.dwWidth<<=1);
                                                                   for(ddsd.dwHeight=1;dwHeight>ddsd.dwHeight;ddsd.dwHeight<<=1);
                                                                  };
                                                                  if(ddDesc.dpcTriCaps.dwTextureCaps & D3DPTEXTURECAPS_SQUAREONLY){
                                                                   if(ddsd.dwWidth>ddsd.dwHeight) ddsd.dwHeight=ddsd.dwWidth; else ddsd.dwWidth=ddsd.dwHeight;
                                                                  };
                                                                  // Enumerate the texture formats, and find the closest device-supported
                                                                  // texture pixel format. The TextureSearchCallback function for this
                                                                  // tutorial is simply looking for a 16-bit texture. Real apps may be
                                                                  // interested in other formats, for alpha textures, bumpmaps, etc..
                                                                  pgrafik->device()->EnumTextureFormats(TextureSearchCallback,&ddsd.ddpfPixelFormat);
                                                                  if(0L==ddsd.ddpfPixelFormat.dwRGBBitCount)return(false);      
                                                                  // Get the device's render target, so we can then use the render target to
                                                                  // get a ptr to a DDraw object. We need the DirectDraw interface for
                                                                  // creating surfaces.
                                                                  LPDIRECTDRAWSURFACE7 pddsRender;
                                                                  LPDIRECTDRAW7        pDD;
                                                                  pgrafik->device()->GetRenderTarget(&pddsRender);
                                                                  pddsRender->GetDDInterface((VOID**)&pDD);
                                                                  pddsRender->Release();            
                                                                  // Create a new surface for the texture
                                                                  if(FAILED(hr=pDD->CreateSurface(&ddsd,&pddstextur,NULL))){
                                                                   pDD->Release();
                                                                   pgrafik->fehler("surfacebind",hr);
                                                                   return(false);
                                                                  };
                                                                  // Done with DDraw
                                                                  pDD->Release();     
                                                                  
                                                                  
                                                                  
                                                                  */


//******************************************************************************************************************************************************************************************************
//                                                              B I L D H A R D W A R E D I R E C T X 
//******************************************************************************************************************************************************************************************************
_bildhardwaredirectx::_bildhardwaredirectx(_grafikdirectx*pg,_bild<_tb>*pb):_bildhardware(pg,pb){
                                                                pgrafik=pg;
															//	bild()->bildhardware(this);
                                                                pddstextur=0;
                                                                ZeroMemory( &pdescriptor, sizeof(DDSURFACEDESC2) );
															    unsigned int realwidth=bild()->groesse(0);
															    unsigned int realheight=bild()->groesse(1);
																if(!pgrafik->unterstuetzttexturnichthochzwei()){  
																 for(unsigned int i=1;;i<<=1) if(i>=bild()->groesse(0)){
																  realwidth=i; 
																  break; 
																 } ;
														         for(unsigned int i=1;;i<<=1) if(i>=bild()->groesse(1)){
																  realheight=i; 
																  break; 
																 };
																};
    
															    // Test if we need square Textures 
																if(!pgrafik->unterstuetzttexturrechteckig()) realwidth=realheight=max(realwidth,realheight); 

																skalierungx(_tg(bild()->groesse(0))/_tg(realwidth));
																skalierungy(_tg(bild()->groesse(1))/_tg(realheight));


                                                                //pgrafik->listebildhardware()->einhaengen(this);
};

_bildhardwaredirectx::~_bildhardwaredirectx(){
                                                                loeschen();
																if(bild()) bild()->bildhardware(0);
};

void _bildhardwaredirectx::wiederherstellen(){
                                                                if(pddstextur){
                                                                 if(pddstextur->IsLost()) pddstextur->Restore();
                                                                };
};
void _bildhardwaredirectx::loeschen(){
                                                                if(pgrafik->paltebindung==this){
                                                                 pgrafik->paltebindung=0;        
                                                                 pgrafik->device()->SetTexture(0,NULL);
                                                                };
                                                                if(pddstextur)pddstextur->Release();
                                                                pddstextur=0;
                                                                //bild()->bildhardware(0);
};
bool _bildhardwaredirectx::binden(){
                                                                //if(pgrafik->paltebindung!=this){
																pgrafik->paltebindung=this;
                                                                if(pddstextur==0){

																 // Test if we need Power-of-Two-Textures 
															     unsigned int realwidth=bild()->groesse(0);
															     unsigned int realheight=bild()->groesse(1);
																 if(!pgrafik->unterstuetzttexturnichthochzwei()){  
																  for(unsigned int i=1;;i<<=1) if(i>=bild()->groesse(0)){
																   realwidth=i; 
																   break; 
																  } ;
														          for(unsigned int i=1;;i<<=1) if(i>=bild()->groesse(1)){
																   realheight=i; 
																   break; 
																  };
																 };
    
															     // Test if we need square Textures 
																 if(!pgrafik->unterstuetzttexturrechteckig()) realwidth=realheight=max(realwidth,realheight); 

                                                                 DWORD wx=realwidth;
                                                                 DWORD wy=realheight;
																 DWORD nom=0;
#
                                                                 DWORD fl=D3DX_TEXTURE_NOMIPMAP;
                                                                 D3DX_SURFACEFORMAT f=D3DX_SF_A8R8G8B8;
																// L->l("_bildhardwaredirectx : binden : Texture soll erzeugt werden mit");
																// L->l("wx=",realwidth);
																// L->l("wy=",realheight);

																 if(S_OK!=D3DXCreateTexture( pgrafik->device(),&fl,&wx,&wy,&f,0,&pddstextur,&nom)){
																	 L->l("_bildhardwaredirectx : binden : DxD3CreateTexture failed.");
																	  return(false);
																 };

                                                                 DDSURFACEDESC2 ddsd;
                                                                 ZeroMemory( &ddsd, sizeof(DDSURFACEDESC2) );
																 if(pddstextur->Lock(NULL,&ddsd,DDLOCK_WAIT| DDLOCK_WRITEONLY,NULL)==DD_OK){
                                                                  _tb*dest=(_tb*)ddsd.lpSurface;
																  unsigned int step = (ddsd.lPitch >> 2) - ddsd.dwWidth + (ddsd.dwWidth - bild()->groesse(0)); 
																//  L->l("pitch=",(int)ddsd.lPitch);
                                                                  
                                                                  unsigned int si=0;
                                                                  for (unsigned int yi=0;yi<bild()->groesse(1);yi++){
                                                                   for (unsigned int xi=0;xi<bild()->groesse(0);xi++){
                                                                    if(bild()->kanaele()==4){
                                                                     //int si=(yi*+xi)*4;
                                                                     dest[xi*4+0]=bild()->daten()[si+2];//*255;
                                                                     dest[xi*4+1]=bild()->daten()[si+1];//*255;
                                                                     dest[xi*4+2]=bild()->daten()[si+0];//*255;
                                                                     dest[xi*4+3]=bild()->daten()[si+3];//*255;
																	 si+=4;
                                                                    }else if(bild()->kanaele()==3){
                                                                     //int si=(yi*wx+xi)*3;
                                                                     dest[xi*4+0]=bild()->daten()[si+2];//*255;
                                                                     dest[xi*4+1]=bild()->daten()[si+1];//*255;
                                                                     dest[xi*4+2]=bild()->daten()[si+0];//*255;
                                                                     dest[xi*4+3]=255;//alpha
																	 si+=3;
                                                                    };
																	
                                                                   };
													              // if(((unsigned int)(bild()->groesse(0)))<ddsd.dwWidth) memset(dest, 0, (ddsd.dwWidth - unsigned int(bild()->groesse(0))) << 2); 
                                                                  // dest+=step;
																   dest+=ddsd.lPitch;
                                                                  };
                                                                  pddstextur->Unlock(NULL);
                                                                  
																 }else{
															      L->l("_bildhardwaredirectx : binden : Lock failed.");
															      return(false);
																 }; 
																};
															//	L->l("_bildhardwaredirectx : binden : Textur soll gesetzt werden.");
                                                                pgrafik->device()->SetTexture(0,pddstextur);
															//	L->l("_bildhardwaredirectx : binden : wird verlassen.");
                                                                return(true);
                                                                
};
void _bildhardwaredirectx::lesen(_to*t){
                                                                DDSURFACEDESC2 ddsd;
                                                                ZeroMemory( &ddsd, sizeof(DDSURFACEDESC2) );
                                                                pddstextur->Lock(NULL,&ddsd,DDLOCK_WAIT,NULL);
                                                                _tb*src=(_tb*)ddsd.lpSurface;
                                                                unsigned int wx=bild()->groesse(0);
                                                                unsigned int wy=bild()->groesse(1);
                                                                for (unsigned int yi=0;yi<wy;yi++){
                                                                 for (unsigned int xi=0;xi<wx;xi++){
																  unsigned int di=(yi*ddsd.dwWidth+xi)*4;
                                                                  t[di+2]=_to(src[xi*4+0])/_to(255);
                                                                  t[di+1]=_to(src[xi*4+1])/_to(255);
                                                                  t[di+0]=_to(src[xi*4+2])/_to(255);
                                                                  t[di+3]=_to(src[xi*4+3])/_to(255);
                                                                 };
                                                                 src+=ddsd.lPitch;
                                                                };
                                                                pddstextur->Unlock(NULL);

};
bool _bildhardwaredirectx::oeffnen(){
                                                                ZeroMemory( &pdescriptor, sizeof(DDSURFACEDESC2) );
																binden();
                                                                pddstextur->Lock(NULL,&pdescriptor,DDLOCK_WAIT,NULL);
                                                                return(true);
};
_tb* _bildhardwaredirectx::daten(){
                                                                return((_tb*)pdescriptor.lpSurface);
};
void _bildhardwaredirectx::schliessen(){
                                                                pddstextur->Unlock(NULL);
};

