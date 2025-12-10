//******************************************************************************************************************************************************************************************************
//  Projekt     : grundplatte
//  Modul       : _editionigg.cpp
//  Datum       : 17.09.2008
//******************************************************************************************************************************************************************************************************
#include <_editionigg.hpp>

bool charactervalid(unsigned char c){
                                                                if((c>=48)&&(c<=57)) return(true);
                                                                if((c>=65)&&(c<=90)) return(true);
                                                                if((c>=97)&&(c<=122)) return(true);
                                                                if(c==32) return(true);
                                                                //umlaute
                                                                if(c==0xe4)return(true);//ä
                                                                if(c==0xf6)return(true);//ö
                                                                if(c==0xfc)return(true);//ü
                                                                if(c==0xc4)return(true);//Ä
                                                                if(c==0xd6)return(true);//Ö
                                                                if(c==0xdc)return(true);//Ü
                                                                //éè
                                                                if(c==0xe8)return(true);
                                                                if(c==0xe9)return(true);
                                                                return(false);
};

//*******************************************************************************************************************************************************************************
//										                        G U I C L I P
//*******************************************************************************************************************************************************************************
_iggclip::_iggclip(){
                                                                x0=0;
                                                                x1=100;
                                                                y0=0;
                                                                y1=100;
};				
//*******************************************************************************************************************************************************************************
//										                        G U I C O L O R
//*******************************************************************************************************************************************************************************
_iggcolor::_iggcolor(){
                                                                std.setzen(_to(0.588f),_to(0.588f),_to(0.588f),0);
                                                				mark.setzen(_to(0.784f),_to(-0.686f),_to(0.588f),0);
				                                                active.setzen(1,_to(-0.784f),_to(-0.588f),0);
};
//*******************************************************************************************************************************************************************************
//										D R A W  F U N C T I O N S  -  G U I  S U P P O R T
//*******************************************************************************************************************************************************************************
void zeichnenguitext(_grafik*g,_zeichenkette<_tt>const&name,_zeichensatz*zs,_vektor3<_tg>&p,_vektor4<_to>&c){
                                                                /*
                                                                SetBlend(SOLIDBLEND);
	                                                            SetBlend(MASKBLEND|ALPHABLEND);
	                                                            SetAlpha(c.w());
                                                                if(p.z()>0)	
                                                                 //SetColor(255,255,255)
                                                                 //DrawText(name,Int(p.x()-p.z()),Int(p.y()-p.z()))
	                                                             SetColor(0,0,0);
	                                                             DrawText(name,Int(p.x()+p.z()),Int(p.y()+p.z()));
                                                                };
                                                                SetBlend(MASKBLEND|ALPHABLEND);
                                                                SetColor(c.x()*255,c.y()*255,c.z()*255);
                                                                DrawText(name,Int(p.x()),Int(p.y()));
                                                                */
                                                                if(name!=L""){
                                                                 g->transparenzmultiplikativ();
                                                                 if(p.z()>0){
                                                                  zs->text(name,int(p.x()+p.z()),int(p.y()+p.z()),_vektor4<_to>(0,0,0,c.w()));
                                                                 };
                                                                 zs->text(name,int(p.x()),int(p.y()),c);
                                                                };
};
void zeichnenguibox(_grafik*g,_vektor3<_tg>&p,_tg w,_tg h,_vektor4<_to>&c){
                                                                _vektor4<_to> c0=c*0.5;
                                                                _vektor4<_to> c1=c*2;
                                                                _vektor3<_tg> p10=p;
                                                                _vektor3<_tg> p11=p;
                                                                _vektor3<_tg> p01=p;
                                                                c1.begrenzen(0,1);
                                                                p10.x(p10.x()+w-1);
                                                                p11.x(p11.x()+w-1);
                                                                p11.y(p11.y()+h-1);
                                                                p01.y(p01.y()+h-1);
																g->textur(false);
                                                                g->rechteck(p.x(),p.y(),w-1,h-1,c);
                                                                g->linie(p,p10,c1);
                                                                g->linie(p,p01,c1);
                                                                g->linie(p11,p10,c0);
                                                                g->linie(p11,p01,c0);
																g->textur(true);
                                                                /*
				                                                SetLinebreite(1);
				                                                SetBlend(SOLIDBLEND);
				                                                SetBlend(blend);
				                                                SetAlpha(c.w());
				                                                SetColor(c.x()*255,c.y()*255,c.z()*255);
				                                                DrawRect(p.x(),p.y(),w,h);
				                                                SetColor(c.x()*511,c.y()*511,c.z()*511);
				                                                DrawLine(p.x(),p.y(),p.x()+w-1,p.y());
				                                                DrawLine(p.x(),p.y(),p.x(),p.y()+h-1);
				                                                SetColor(c.x()*127,c.y()*127,c.z()*127);
				                                                SetBlend(SHADEBLEND|ALPHABLEND);
				                                                DrawLine(p.x()+w-1,p.y()+h-1,p.x(),p.y()+h-1);
				                                                DrawLine(p.x()+w-1,p.y()+h-1,p.x()+w-1,p.y());
				                                                */
};
void zeichnenguirectangle(_grafik*g,_vektor3<_tg>&p,_tg w,_tg h,_vektor4<_to>&c){
                                                                _vektor4<_to> c0=c*0.5;
                                                                _vektor4<_to> c1=c*2;
                                                                _vektor3<_tg> p10=p;
                                                                _vektor3<_tg> p11=p;
                                                                _vektor3<_tg> p01=p;
                                                                c1.begrenzen(0,1);
                                                                p10.x(p10.x()+w-1);
                                                                p11.x(p11.x()+w-1);
                                                                p11.y(p11.y()+h-1);
                                                                p01.y(p01.y()+h-1);
																g->textur(false);
                                                                g->linie(p,p10,c1);
                                                                g->linie(p,p01,c1);
                                                                g->linie(p11,p10,c0);
                                                                g->linie(p11,p01,c0);
				                                                /*SetLinebreite(1);
				                                                SetBlend(SOLIDBLEND);
				                                                SetBlend(blend);
				                                                SetAlpha(c.w());
				                                                SetColor(c.x()*511,c.y()*511,c.z()*511);
				                                                DrawLine(p.x(),p.y(),p.x()+w-1,p.y());
				                                                DrawLine(p.x(),p.y(),p.x(),p.y()+h-1);
				                                                SetColor(c.x()*127,c.y()*127,c.z()*127);
				                                                SetBlend(SHADEBLEND);
				                                                DrawLine(p.x()+w-1,p.y()+h-1,p.x(),p.y()+h-1);
				                                                DrawLine(p.x()+w-1,p.y()+h-1,p.x()+w-1,p.y());*/
																g->textur(true);
};
void zeichnenguiboxinvers(_grafik*g,_vektor3<_tg>&p,_tg w,_tg h,_vektor4<_to>&c){
                                                                _vektor4<_to> c0=c*0.5;
                                                                _vektor4<_to> c1=c*2;
                                                                _vektor3<_tg> p10=p;
                                                                _vektor3<_tg> p11=p;
                                                                _vektor3<_tg> p01=p;
                                                                c1.begrenzen(0,1);
                                                                p10.x(p10.x()+w-1);
                                                                p11.x(p11.x()+w-1);
                                                                p11.y(p11.y()+h-1);
                                                                p01.y(p01.y()+h-1);
																g->textur(false);
                                                                g->rechteck(p.x(),p.y(),w-1,h-1,c);
                                                                g->linie(p,p10,c0);
                                                                g->linie(p,p01,c0);
                                                                g->linie(p11,p10,c1);
                                                                g->linie(p11,p01,c1);
																g->textur(true);
				                                                /*SetLinebreite(1);
				                                                SetBlend(SOLIDBLEND);
				                                                SetBlend(blend);
				                                                SetAlpha(c.w());
				                                                SetColor(c.x()*255,c.y()*255,c.z()*255);
				                                                DrawRect(p.x(),p.y(),w,h);
				                                                SetBlend(SHADEBLEND|ALPHABLEND);
				                                                SetColor(c.x()*127,c.y()*127,c.z()*127);
				                                                DrawLine(p.x(),p.y(),p.x()+w-1,p.y());
				                                                DrawLine(p.x(),p.y(),p.x(),p.y()+h-1);
				                                                SetBlend(blend);
				                                                SetColor(c.x()*511,c.y()*511,c.z()*511);
				                                                DrawLine(p.x()+w-1,p.y()+h-1,p.x(),p.y()+h-1);
				                                                DrawLine(p.x()+w-1,p.y()+h-1,p.x()+w-1,p.y());*/
};
void zeichnenguirectangleinvers(_grafik*g,_vektor3<_tg>&p,_tg w,_tg h,_vektor4<_to>&c){
                                                                _vektor4<_to> c0=c*0.5;
                                                                _vektor4<_to> c1=c*2;
                                                                _vektor3<_tg> p10=p;
                                                                _vektor3<_tg> p11=p;
                                                                _vektor3<_tg> p01=p;
                                                                c1.begrenzen(0,1);
                                                                p10.x(p10.x()+w-1);
                                                                p11.x(p11.x()+w-1);
                                                                p11.y(p11.y()+h-1);
                                                                p01.y(p01.y()+h-1);
																g->textur(false);
                                                                g->linie(p,p10,c0);
                                                                g->linie(p,p01,c0);
                                                                g->linie(p11,p10,c1);
                                                                g->linie(p11,p01,c1);
																g->textur(true);
				                                                /*SetLinebreite(1);
				                                                SetBlend(SOLIDBLEND);
				                                                SetBlend(blend);
				                                                SetAlpha(c.w());
				                                                SetBlend(blend);
				                                                SetColor(c.x()*127,c.y()*127,c.z()*127);
				                                                DrawLine(p.x(),p.y(),p.x()+w-1,p.y());
				                                                DrawLine(p.x(),p.y(),p.x(),p.y()+h-1);
				                                                SetBlend(blend);
				                                                SetColor(c.x()*511,c.y()*511,c.z()*511);
				                                                DrawLine(p.x()+w-1,p.y()+h-1,p.x(),p.y()+h-1);
				                                                DrawLine(p.x()+w-1,p.y()+h-1,p.x()+w-1,p.y());*/
};
void zeichnenguifurche(_grafik*g,_tg x0,_tg y0,_tg x1,_tg y1,_vektor4<_to>&c){
                                                                _vektor4<_to> c0=c*0.5;
                                                                _vektor4<_to> c1=c*2;
                                                                _vektor3<_tg> p0(x0,y0,0);
                                                                _vektor3<_tg> p1(x1,y1,0);
                                                                c1.begrenzen(0,1);
				                                                //SetLinebreite(1);
				                                                //SetBlend(SOLIDBLEND);
				                                                //SetBlend(ALPHABLEND);
				                                                if(fabs(x0-x1)<fabs(y0-y1)){
				                                                 g->linie(p0,p1,c0);
				                                                 p0.x(p0.x()+1);
				                                                 p1.x(p1.x()+1);
				                                                 g->linie(p0,p1,c1);
				                                                 /*SetAlpha(c.w());
				                                                 SetColor(c.x()*127,c.y()*127,c.z()*127);
				                                                 DrawLine(x0,y0,x1,y1);
				                                                 SetBlend(blend);
				                                                 SetColor(c.x()*511,c.y()*511,c.z()*511);
				                                                 DrawLine(x0+1,y0,x1+1,y1);*/
				                                                }else{
				                                                 g->linie(p0,p1,c0);
				                                                 p0.y(p0.y()+1);
				                                                 p1.y(p1.y()+1);
				                                                 g->linie(p0,p1,c1);
				                                                 /*SetAlpha(c.w());
				                                                 SetColor(c.x()*127,c.y()*127,c.z()*127);
				                                                 DrawLine(x0,y0,x1,y1);
				                                                 SetBlend(blend);
				                                                 SetColor(c.x()*511,c.y()*511,c.z()*511);
				                                                 DrawLine(x0,y0+1,x1,y1+1);*/
				                                                };
};
//*******************************************************************************************************************************************************************************
//										                        G U I V E C T O R E N T R Y
//*******************************************************************************************************************************************************************************
_iggvectorentry::_iggvectorentry(_iggvector*gv,const _vektor3<_tg>&o,bool dyn):_listenknotenbasis<_iggvectorentry>(gv){
                                                                iggvector=gv;
                                                                dynamic=dyn;
                                                                kopieren(o);
};
_iggvectorentry::_iggvectorentry(_iggvectorkondition*k,_iggvector*gv,const _vektor3<_tg>&o,bool dyn):_listenknotenbasis<_iggvectorentry>(k){
                                                                iggvector=gv;
                                                                dynamic=dyn;
                                                                kopieren(o);
};
_iggvectorentry::~_iggvectorentry(){
};
//******************************************************************************************************************
//										                    I G G V E C T O R K O N D I T I O N
//******************************************************************************************************************
_iggvectorkondition::_iggvectorkondition(_iggvector*gv,_tg xmin,_tg xmax,_tg ymin,_tg ymax):_listenknotenbasis<_iggvectorkondition>(gv->konditionsliste()){
				                                                iggvector=gv;
				                                                bereichxmin=xmin;
				                                                bereichxmax=xmax;
				                                                bereichymin=ymin;
				                                                bereichymax=ymax;
};			
_iggvectorkondition::~_iggvectorkondition(){
};	
_iggvectorentry* _iggvectorkondition::addieren(_tg x,_tg y,_tg z,bool dynamic){
				                                                _vektor3<_tg> v(x,y,z);
				                                                return(new _iggvectorentry(this,iggvector,v,dynamic));
};
//*******************************************************************************************************************************************************************************
//										                        I G G V E C T O R
//*******************************************************************************************************************************************************************************
_iggvector::_iggvector(_igg*g,const _tg x,const _tg y,const _tg z,bool dynamic){
                                                                igg=g;
                                                                iggsystem=igg->iggsystem();
                                                                addieren(x,y,z,dynamic);
};
_iggvector::~_iggvector(){
};
_listebasis<_iggvectorkondition>* _iggvector::konditionsliste(){
                                                                return(&pkonditionlist);
};
void _iggvector::setzen(const _tg x,const _tg y,const _tg z,bool dynamic){
                                                                _iggvectorentry*vit;
                                                                if(anfang(vit)){
                                                                 vit->setzen(x,y,z);
                                                                 vit->dynamic=dynamic;
				                                                };
};
void _iggvector::x(const _tg x){
                                                                _iggvectorentry*vit;
                                                                if(anfang(vit))vit->x(x);
};
void _iggvector::y(const _tg y){
                                                                _iggvectorentry*vit;
                                                                if(anfang(vit))vit->y(y);
};
void _iggvector::z(const _tg z){
                                                                _iggvectorentry*vit;
                                                                if(anfang(vit))vit->z(z);
};
void _iggvector::setzen(unsigned int vectorindex,const _tg x,const _tg y,const _tg z,bool dynamic){
                                                                _iggvectorentry*vit;
                                                                if(anfang(vit)){
                                                                 int i=0;
                                                                 do{
                                                                  if(i==vectorindex){
                                                                   vit->setzen(x,y,z);
                                                                   vit->dynamic=dynamic;
                                                                  };
                                                                  i+=1;
                                                                 }while(naechstes(vit));
                                                                };
};
void _iggvector::dynamik(bool d,int i){
				                                                _iggvectorentry*it=index(i);
				                                                if(it){
				                                                 it->dynamic=d;
				                                                };
};
void _iggvector::addieren(const _tg x,const _tg y,const _tg z,bool dynamic){
                                                                new _iggvectorentry(this,_vektor3<_tg>(x,y,z),dynamic);
};
void _iggvector::addieren(const _vektor3<_tg>&v,bool dynamic){
                                                				new _iggvectorentry(this,v,dynamic);
};
_vektor3<_tg> _iggvector::lesen()const{
				                                                if(pkonditionlist.anzahl()>0){
				                                                 if(iggsystem){
																	
				                                                  int wx=int(iggsystem->breite());
				                                                  int wy=int(iggsystem->hoehe());
				                                                  _iggvectorkondition*kit;
				                                                  if(pkonditionlist.anfang(kit))do{
																	/*   L->schreiben("b xmin ",kit->bereichxmin);
																	   L->schreiben("b ymin ",kit->bereichymin);
																	   L->schreiben("b xmax ",kit->bereichxmax);
																	   L->schreiben("b ymax ",kit->bereichymax);
																	   L->schreiben("wx",wx);
																	   L->schreiben("wy",wy);*/

				                                                   if((wx>=kit->bereichxmin)&&(wy>=kit->bereichymin)&&(wx<=kit->bereichxmax)&&(wy<=kit->bereichymax)){

				                                                    _vektor3<_tg> sp(100,100,0);
				                                                    _vektor3<_tg> v;
				                                                    _vektor3<_tg> u;
				                                                    _iggvectorentry*vit;
				                                                    if(igg->parent) sp=igg->parent->size.lesen();
				                                                    if(kit->anfang(vit))do{
				                                                     if(vit->dynamic){
				                                                      u=*vit;
				                                                      u.x(u[0]*sp[0]);
				                                                      u.y(u[1]*sp[1]);
				                                                      u.z(u[2]*sp[2]);
				                                                      v+=u;
				                                                     }else{
				                                                      v+=*vit;
				                                                     };
				                                                    }while(kit->naechstes(vit));
				                                                    return(v);

				                                                   };
				                                                  }while(pkonditionlist.naechstes(kit));
				                                                 };
				                                                };




				                                                _vektor3<_tg> sp(100,100,0);
				                                                _vektor3<_tg> v;
				                                                _vektor3<_tg> u;
				                                                _iggvectorentry*vit;
				                                                if(igg->parent) sp=igg->parent->size.lesen();
				                                                if(anfang(vit))do{
				                                                 if(vit->dynamic){
				                                                  u=*vit;
				                                                  u.x(u[0]*sp[0]);
				                                                  u.y(u[1]*sp[1]);
				                                                  u.z(u[2]*sp[2]);
				                                                  v+=u;
				                                                 }else{
				                                                  v+=*vit;
				                                                 };
				                                                }while(naechstes(vit));
				                                                return(v);
};
_tg _iggvector::x()const{
				                                                if(pkonditionlist.anzahl()>0){
				                                                 if(iggsystem){
				                                                  int wx=int(iggsystem->breite());
				                                                  int wy=int(iggsystem->hoehe());
				                                                  _iggvectorkondition*kit;
				                                                  if(pkonditionlist.anfang(kit))do{
				                                                   if((wx>=kit->bereichxmin)&&(wy>=kit->bereichymin)&&(wx<=kit->bereichxmax)&&(wy<=kit->bereichymax)){

				                                                    _tg sp=_tg(-1);
				                                                    _tg v=0;
				                                                    _iggvectorentry*vit;
				                                                    if(kit->anfang(vit))do{
				                                                     if(vit->dynamic){
				                                                      if(sp==_tg(-1)) if(igg->parent) sp=igg->parent->size.x(); else sp=100;
				                                                      v+=vit->x()*sp;
				                                                     }else{
				                                                      v+=vit->x();
				                                                     };
				                                                    }while(kit->naechstes(vit));
				                                                    return(v);

				                                                   };
				                                                  }while(pkonditionlist.naechstes(kit));
				                                                 };
				                                                };



				                                                _tg sp=_tg(-1);
				                                                _tg v=0;
				                                                _iggvectorentry*vit;
				                                                if(anfang(vit))do{
				                                                 if(vit->dynamic){
				                                                  if(sp==_tg(-1)) if(igg->parent) sp=igg->parent->size.x(); else sp=100;
				                                                  v+=vit->x()*sp;
				                                                 }else{
				                                                  v+=vit->x();
				                                                 };
				                                                }while(naechstes(vit));
				                                                return(v);
};	
_tg _iggvector::y(int index)const{
				                                                if(pkonditionlist.anzahl()>0){
				                                                 if(iggsystem){
				                                                  int wx=int(iggsystem->breite());
				                                                  int wy=int(iggsystem->hoehe());
				                                                  _iggvectorkondition*kit;
				                                                  if(pkonditionlist.anfang(kit))do{
				                                                   if((wx>=kit->bereichxmin)&&(wy>=kit->bereichymin)&&(wx<=kit->bereichxmax)&&(wy<=kit->bereichymax)){
                                                                   
                                                                    _iggvectorentry*vit;
				                                                    _tg v=0;
				                                                    if(index==-1){
				                                                     _tg sp=-1;
				                                                     if(kit->anfang(vit))do{
				                                                      if(vit->dynamic){
				                                                       if(sp==-1) if(igg->parent) sp=igg->parent->size.y(); else sp=100;
				                                                       v+=vit->y()*sp;
				                                                      }else{
				                                                       v+=vit->y();
				                                                      };
				                                                     }while(kit->naechstes(vit));
				                                                    }else{
				                                                     if(kit->anfang(vit)){
				                                                      int i=0;
				                                                      do{
				                                                       if(i==index) return(vit->y());
				                                                       i++;
				                                                      }while(kit->naechstes(vit));
				                                                     };
				                                                    };
				                                                    return(v);


				                                                   };
				                                                  }while(pkonditionlist.naechstes(kit));
				                                                 };
				                                                };



                                                                _iggvectorentry*vit;
				                                                _tg v=0;
				                                                if(index==-1){
				                                                 _tg sp=-1;
				                                                 if(anfang(vit))do{
				                                                  if(vit->dynamic){
				                                                   if(sp==-1) if(igg->parent) sp=igg->parent->size.y(); else sp=100;
				                                                   v+=vit->y()*sp;
				                                                  }else{
				                                                   v+=vit->y();
				                                                  };
				                                                 }while(naechstes(vit));
				                                                }else{
				                                                 if(anfang(vit)){
				                                                  int i=0;
				                                                  do{
				                                                   if(i==index) return(vit->y());
				                                                   i++;
				                                                  }while(naechstes(vit));
				                                                 };
				                                                };
				                                                return(v);
};	
_tg _iggvector::z()const{
				                                                _tg sp=0;
				                                                _tg v=0;
				                                                if(igg->parent) sp=igg->parent->size.z(); else sp=100;
				                                                
				                                                if(pkonditionlist.anzahl()>0){
				                                                 if(iggsystem){
				                                                  int wx=int(iggsystem->breite());
				                                                  int wy=int(iggsystem->hoehe());
				                                                  _iggvectorkondition*kit;
				                                                  if(pkonditionlist.anfang(kit))do{
				                                                   if((wx>=kit->bereichxmin)&&(wy>=kit->bereichymin)&&(wx<=kit->bereichxmax)&&(wy<=kit->bereichymax)){
				                                                    _iggvectorentry*vit;
				                                                    if(kit->anfang(vit))do{
					                                                 if(vit->dynamic) v+=vit->z()*sp; else v+=vit->z();
					                                                }while(kit->naechstes(vit));
					                                                return(v);
				                                                   };
				                                                  }while(pkonditionlist.naechstes(kit));
				                                                 };
				                                                };
				                                                
				                                                _iggvectorentry*vit;
				                                                if(anfang(vit))do{
				                                                 if(vit->dynamic) v+=vit->z()*sp; else v+=vit->z();
				                                                }while(naechstes(vit));
				                                                return(v);
};		
_iggvectorkondition* _iggvector::kondition(_tg xmin,_tg xmax,_tg ymin,_tg ymax,_tg x,_tg y,_tg z,bool dynamic){
				                                                _iggvectorkondition*k=new _iggvectorkondition(this,xmin,xmax,ymin,ymax);
				                                                k->addieren(x,y,z,dynamic);
				                                                return(k);
};
//*******************************************************************************************************************************************************************************
//                      										G U I S I Z E 
//*******************************************************************************************************************************************************************************
_iggsize::_iggsize(_igg*g,const _tg x,const _tg y,const _tg z,bool d):_iggvector(g,x,y,z,d){
};
_iggsize::~_iggsize(){
};
//*******************************************************************************************************************************************************************************
//						                        				G U I P O S I T I O N
//*******************************************************************************************************************************************************************************
_iggposition::_iggposition(_igg*g,const _tg x,const _tg y,const _tg z,bool d):_iggvector(g,x,y,z,d){
};
_iggposition::~_iggposition(){
};
//*******************************************************************************************************************************************************************************
//                      										G U I
//*******************************************************************************************************************************************************************************
_igg::_igg(_igg*pg,_tg px,_tg py,_tg pz,_tg pw,_tg ph,int pin):_listelistenknotenbasis<_igg>(pg),parent(pg),position(this,px,py,pz,false),size(this,pw,ph,0,false){
                                                                
                                                                linkzeichnen=0;
                                                                //if(parent) linkparent=parent->kindlist.einhaengen(this);
                                                                if(pg){
                                                                 linkzeichnen=iggsystem()->drawlist.einhaengen(this);
                                                                };
                                                                active=true;
                                                                superinactive=false;
                                                                visible=true;	
                                                                superinvisible=false; 
                                                                clipkind=false;
                                                                clipkindhierarchical=false;
                                                                selectable=false;
                                                                marked=0;
                                                                index=pin;
                                                                pfadeopacity=1;
                                                                pfadein=false;
                                                                pfadeout=false;
                                                                pfadeouttosuperinactive=false;
                                                                pfadeouttosuperinvisible=false;
                                                                pfadeouttoclear=false;
                                                                pfadetarget=1;
                                                                font=0;
                                                                shadow=false;
                                                                shadowopacity=_to(0.8f);
                                                                shadowimageboardening=0;
                                                                hilfeparent=0;
                                                                hilfe=0;
                                                                hilfepositionx=0;
                                                                hilfepositiony=0;
                                                                hilfedelaytime=0.4;
                                                                hilfetimefalse=0;
                                                                hilfefont=0;
                                                                fadetimeold=0;
                                                                color.setzen(1,1,1,1);
                                                                colortransformed=color;
                                                                shadowdirection.setzen(5,5,0);
                                                                shadowdirectiontransformed.setzen(5,5,0);
                                                                positiontransformed=position.lesen();
};
_igg::~_igg(){
				                                                if(iggsystem()->focus==this) iggsystem()->focus=0;
				                                                loeschenhilfe();
				                                                deletesecure(linkzeichnen);
};
void _igg::loeschenhilfe(){
                                                                deletesecure(hilfe);
				                                                hilfefont=0;
};		
void _igg::einhaengen(_igg*p){
				                                                _listenknotenbasis<_igg>::aushaengen();
				                                                parent=p;
				                                                _listenknotenbasis<_igg>::einhaengen(p);
};
void _igg::aushaengen(){
                                                                _listenknotenbasis<_igg>::aushaengen();
				                                                parent=0;
};
_iggsystem*_igg::iggsystem(){
				                                                if(parent==0) return(static_cast<_iggsystem*>(this));
				                                                _igg*git=parent;
				                                                while(git->parent){
				                                                 if(git->parent==0) return(static_cast<_iggsystem*>(git)); else git=git->parent;
				                                                };
				                                                return(static_cast<_iggsystem*>(git));
};	
void _igg::dynamisch(_tg wx,_tg wy){
				                                                position.setzen(position.x()/wx,position.y()/wy,position.z(),true);
				                                                size.setzen(size.x()/wx,size.y()/wy,size.z(),true);
};
void _igg::dynamischort(_tg wx,_tg wy){
				                                                position.setzen(position.x()/wx,position.y()/wy,position.z(),true);
};
void _igg::dynamischgroesse(_tg wx,_tg wy){
				                                                size.setzen(size.x()/wx,size.y()/wy,size.z(),true);
};
bool _igg::vergleichen(_igg*g)const{
				                                                if(g){
	 			                                                 if(positiontransformed[2]<g->positiontransformed[2]){
	                                                              return(false);
				                                                 };
				                                                };
				                                                return(true);
};	
_tg _igg::kindbreite()const{
				                                                if(_listebasis<_igg>::anzahl()==0) return(0);
				                                                _tg xmin=+100000;
				                                                _tg xmax=-100000;
				                                                _tg xin,xax;
				                                                _igg*git;
				                                                if(anfang(git))do{
				                                                 _vektor3<_tg> p=git->position.lesen();
				                                                 xin=p[0];
				                                                 xax=p[0]+git->breite();
				                                                 if (xin<xmin) xmin=xin;
				                                                 if (xax>xmax) xmax=xax;
				                                                }while(naechstes(git));				
				                                                return(xmax);
};				
_tg _igg::kindhoehe()const{
				                                                if(_listebasis<_igg>::anzahl()==0) return(0);
				                                                _tg ymin=+100000;
				                                                _tg ymax=-100000;
				                                                _tg yin,yax;
				                                                _igg*git;
				                                                if(anfang(git))do{
				                                                 _vektor3<_tg> p=git->position.lesen();
				                                                 yin=p[1];
				                                                 yax=p[1]+git->hoehe();
				                                                 if (yin<ymin) ymin=yin;
				                                                 if (yax>ymax) ymax=yax;
				                                                }while(naechstes(git));				
				                                                return(ymax);
};				
void _igg::loeschenkind(){
																_listebasis<_igg>::loeschen();
};
_tg _igg::breite()const{
				                                                return(size.x());
};		
_tg _igg::hoehe()const{
				                                                return(size.y());
};		
_tg _igg::tiefe()const{
				                                                return(size.z());
};					
void _igg::zentriert(){
																transformation.setzen(-0.5,0,0);
};
void _igg::rechtsbuendig(){
																transformation.setzen(-1,0,0);
};
void _igg::linksbuendig(){
																transformation.setzen(0,0,0);

};

bool _igg::inner(_maus<_tg>*mau){
                                                				if((mau->x()>positiontransformed.x())&&(mau->x()<(positiontransformed.x()+breite()))&&(mau->y()>positiontransformed.y())&&(mau->y()<(positiontransformed.y()+hoehe()))) return(true); else return(false);
};
bool _igg::mouseovergui(_maus<_tg>*mau){
				                                                _igg*git;
				                                                if((active)&&(inner(mau))) return(true);
				                                                if(anfang(git))do{
				                                                 if((git->visible)&&(git->active)){ 
				                                                  if(git->mouseovergui(mau)){
				                                                   return(true);
				                                                  };
				                                                 };
				                                                }while(naechstes(git));
				                                                return(false);
};	
_iggtext*_igg::inserttext(const _zeichenkette<_tt>&t,_tg x,_tg y,_tg z,_to r,_to g,_to b,_zeichensatz*f,int pp,_tg mob){//inserts a new _iggtext object in the list
				                                                _iggtext*gt=new _iggtext(this,x,y,z,t,r,g,b,f,mob);
				                                                gt->index=pp;
				                                                gt->selectable=true;
				                                                return(gt);
};
_iggimage*_igg::insertimage(_bild<_tb>*t,_tg x,_tg y,_tg w,_tg h,_to r,_to g,_to b,int pp){//inserts a new _iggimage object in the list
			                                                    _iggimage*gi=new _iggimage(this,x,y,w,h,t,r,g,b);
			                                                    gi->index=pp;
			                                                    gi->selectable=true;
			                                                    return(gi);
};
_iggmesh*_igg::insertmesh(_netz*m,_tg x,_tg y,_tg w,_tg h,_to r,_to g,_to b,int pp){//inserts a new _iggmesh object in the list
				                                                _iggmesh*gi=new _iggmesh(this,x,y,w,h,m,r,g,b,pp);
				                                                gi->selectable=true;
				                                                return(gi);
};				
_iggline*_igg::insertline(_tg x0,_tg y0,_tg x1,_tg y1,_to r,_to g,_to b){//inserts a new _iggline object in the list
				                                                return(new _iggline(this,x0,y0,x1,y1,r,g,b));
};				
void _igg::textsplit(const _zeichenkette<_tt>&t,_tg wx,_zeichensatz*f,_liste<_zeichenkette<_tt> >*l){
                                                                l->loeschen();
				                                                _zeichenkette<_tt> h;
				                                                _zeichenkette<_tt> o;
				                                                _zeichenkette<_tt> sep(L" ");
				                                                _liste<_zeichenkette<_tt> > li;
				                                                unsigned int count;
				                                                unsigned int i;
				                                                //SetImageFont(f);
				                                                t.teilen(sep,&li);
				                                                count=li.anzahl();
				                                               
				                                                i=0;
				                                                while(i<count){
				                                                 h=L"";
				                                                 while((f->breite(h)<wx)&&(i<count)){
				                                                  o=h;
				                                                  h+=(*li[i])+_zeichenkette<_tt>(L" ");
				                                                  i++;
				                                                 };
				                                                 if(f->breite(h)>=wx){
				                                                  h=o;
				                                                  i--;
				                                                 };
				                                                 if((h!=L"")&&(h!=L" ")) l->einhaengen(new _zeichenkette<_tt>(h));
				                                                };
				                                                li.loeschen();
				                                                
};				
_iggwindow*_igg::createhilfe(const _zeichenkette<_tt>&text,_zeichensatz*fh,_tg dt,_tg ox,_tg oy,int staticbreite,bool noclear){
				                                                if((noclear)&&(hilfe)) return(addhilfe(text,fh,staticbreite));
				                                                loeschenhilfe();
				                                                hilfedelaytime=dt;
				                                                hilfefont=fh;
				                                                hilfepositionx=ox;
				                                                hilfepositiony=oy;
				                                                //SetImageFont(hilfefont);
				                                                _iggwindow*w0;
				                                                _tg px=0;
				                                                _tg py=0;
				                                                _tg wy;
				                                                _tg wx=hilfefont->breite(text)+50;
				                                                _tg maxwx=400;
				                                                if(wx<100) wx=100;
				                                                if(wx>maxwx) wx=maxwx;
				                                                if(staticbreite!=-1) wx=staticbreite;
				                                                _liste<_zeichenkette<_tt> > lt;
				                                                textsplit(text,wx-40,hilfefont,&lt);
				                                                wy=20+lt.anzahl()*20;
				                                                w0=new _iggwindow(iggsystem(),px,py,wx,wy,_to(0.5f),_to(0.2f),_to(0.05f));
				                                                w0->position.z(w0->position.z()-10);
				                                                _tg yit=10;
				                                                _listenknoten<_zeichenkette<_tt> >*lnzit;
				                                                if(lt.anfang(lnzit))do{
				                                                 _iggtext*t0=new _iggtext(w0,20,yit,1,lnzit->objekt(),1,_to(0.8f),_to(0.5f),fh);
				                                                 yit+=20;
				                                                }while(lt.naechstes(lnzit));
				                                                w0->hilfeparent=this;
				                                                w0->visibility(false);
				                                                w0->activity(false);
				                                                w0->fadeopacity(0);
				                                                hilfe=w0;
				                                                lt.loeschen();
				                                                return(static_cast<_iggwindow*>(hilfe));
}; 	
_iggwindow*_igg::addhilfe(const _zeichenkette<_tt>&text0,_zeichensatz*fh,int staticbreite){
				                                                //loeschenhilfe()
				                                                _iggwindow*w0=static_cast<_iggwindow*>(hilfe);
				                                                _iggwindow*w1;
				                                                _igg*wn;
				                                                _iggwindow*wit;
				                                                _tg px=0;
				                                                _tg py=0;
				                                                _tg wy;
				                                                _tg wx;
				                                                if(w0==0)return(0);
				                                                if(staticbreite!=-1) wx=staticbreite; else wx=w0->breite();
				                                                px=0;
				                                                py=w0->hoehe()+5;
				                                                if(w0->anfang(wn))do{
				                                                 //For Local wit:_iggwindow=EachIn w0.kindlist, Achtung heterogene Iteration !
				                                                 wit=dynamic_cast<_iggwindow*>(wn);
				                                                 if(wit){
				                                                  py+=wit->hoehe()+5;
				                                                 };
				                                                }while(w0->naechstes(wn));
				                                                _liste<_zeichenkette<_tt> > lt;
				                                                textsplit(text0,wx-40,hilfefont,&lt);
				                                                wy=20+lt.anzahl()*20;
				                                                w1=new _iggwindow(w0,px,py,wx,wy,_to(0.5f),_to(0.2f),_to(0.05f));
				                                                _tg yit=10;
				                                                _listenknoten<_zeichenkette<_tt> > *lntit;
				                                                if(lt.anfang(lntit))do{//For Local tit:String=EachIn lt
				                                                 new _iggtext(w1,20,yit,1,lntit->objekt(),1,_to(0.8f),_to(0.5f),fh);
				                                                 yit+=20;
				                                                }while(lt.naechstes(lntit));
				                                                //w1.hilfeparent=this
				                                                w0->visibility(false);
				                                                w0->activity(false);
				                                                w0->fadeopacity(0);
				                                                lt.loeschen();
				                                                return(w1);

}; 				
_bild<_tb>*_igg::bestbreitematch(){
				                                                //returns best match with the gui-breite
				                                                _tg w=breite();
				                                                _tg dmin=100000;
				                                                _bild<_tb>*b=0;
				                                                _listenknoten<_bild<_tb> >*lnbit=0;
				                                                if(background[marked].anfang(lnbit))do{//For Local tit:_bild<_tb>=EachIn background[marked]
				                                                 _tg d=fabs((w+70)-lnbit->objekt()->groesse(0));
				                                                 if(dmin>d){ 
				                                                  b=lnbit->objekt();
				                                                  dmin=d;
				                                                 };
				                                                }while(background[marked].naechstes(lnbit));
				                                                return(b);
};	
_bild<_tb>*_igg::bestshadowmatch(){
				                                                //returns best match with the gui-breite
				                                                _tg w=breite();
				                                                _tg dmin=100000;
				                                                _bild<_tb>*b=0;
				                                                _listenknoten<_bild<_tb> >*lnbit=0;
				                                                if(shadowimage[marked].anfang(lnbit))do{//For Local tit:_bild<_tb>=EachIn background[marked]
				                                                 _tg d=fabs(w-lnbit->objekt()->groesse(0));
				                                                 if(dmin>d){
				                                                  b=lnbit->objekt();
				                                                  dmin=d;
				                                                 };
				                                                }while(shadowimage[marked].naechstes(lnbit));
                                                				return(b);
};	
void _igg::zeichnenkind(_grafik*gra,_kamera<_tg>*cam){
				                                                if((visible)&&(superinvisible==false)){
				                                                 _igg*git;
				                                                 if(anfang(git))do{
				                                                  git->zeichnen(gra,cam);
				                                                 }while(naechstes(git));
				                                                };
};
void _igg::zeichnenschatten(_grafik*gra,_kamera<_tg>*cam){
				                                                if((visible)&&(superinvisible==false)){
				                                                 if(shadow){
				                                                  _bild<_tb>*bm=bestbreitematch();
				                                                  _bild<_tb>*sm=bestshadowmatch();
				                                                  if((bm)&&(sm==0)){//bildschatten (standard)
				                                                   //SetBlend(SOLIDBLEND);
				                                                   //SetBlend(MASKBLEND|ALPHABLEND);
				                                                   //SetAlpha(shadowopacity*colortransformed.w()*pfadeopacity);
				                                                   //SetColor(0,0,0);
				                                                   gra->transparenzmultiplikativ();
				                                                   gra->rechteck(bm,positiontransformed.x()+shadowdirection.x(),positiontransformed.y()+shadowdirection.y(),breite(),hoehe(),_vektor4<_to>(0,0,0,shadowopacity*colortransformed.w()*pfadeopacity));
				                                                  }else if((sm==0)&&(bm==0)){//provisorischer schatten
				                                                   //SetBlend(SOLIDBLEND);
				                                                   //SetBlend(ALPHABLEND);
				                                                   //SetAlpha(shadowopacity*colortransformed.w()*pfadeopacity);
				                                                   //SetColor(0,0,0);
				                                                   //DrawRect(positiontransformed.x()+shadowdirection.x(),positiontransformed.y()+shadowdirection.y(),breite(),hoehe())
				                                                   gra->transparenzmultiplikativ();
																   gra->textur(false);
				                                                   gra->rechteck(positiontransformed.x()+shadowdirection.x(),positiontransformed.y()+shadowdirection.y(),breite(),hoehe(),_vektor4<_to>(0,0,0,shadowopacity*colortransformed.w()*pfadeopacity));
																   gra->textur(true);
				                                                  }else if(sm){//eigener schatten
				                                                   //SetBlend(SOLIDBLEND);
				                                                   //SetBlend(ALPHABLEND);
				                                                   //SetAlpha(shadowopacity*colortransformed.w()*pfadeopacity);
				                                                   //SetColor(0,0,0);
				                                                   _tg be=shadowimageboardening;
				                                                   gra->rechteck(sm,(positiontransformed.x()+shadowdirection.x())-be,(positiontransformed.y()+shadowdirection.y())-be,breite()+be*2,hoehe()+be*2,_vektor4<_to>(0,0,0,shadowopacity*colortransformed.w()*pfadeopacity));
				                                                  };
				                                                 };
				                                                };
};
void _igg::cliprecursive(_iggclip*cr){
				                                                _tg w,h;
				                                                if((clipkind)||(clipkindhierarchical)){
				                                                 w=breite();
				                                                 h=hoehe();
				                                                 if(positiontransformed.x()>cr->x0) cr->x0=positiontransformed.x();
				                                                 if(positiontransformed.y()>cr->y0) cr->y0=positiontransformed.y();
				                                                 if((positiontransformed.x()+w)<cr->x1) cr->x1=positiontransformed.x()+w;
				                                                 if((positiontransformed.y()+h)<cr->y1) cr->y1=positiontransformed.y()+h;
				                                                };
				                                                if(parent) parent->cliprecursive(cr);
};
bool _igg::clip(_grafik*gra){
	  			
				                                                if((clipkind)&&(clipkindhierarchical==false)){
			 	                                                 gra->sichtbereich(positiontransformed.x(),positiontransformed.y(),breite(),hoehe());
			                                                     return(true);
				                                                }else if(clipkindhierarchical){
				                                                 cliprect.x0=positiontransformed.x();
				                                                 cliprect.x1=cliprect.x0+breite();
				                                                 cliprect.y0=positiontransformed.y();
				                                                 cliprect.y1=cliprect.y0+hoehe();
				                                                 if(parent)parent->cliprecursive(&cliprect);
				                                                 bool valid=true;
				                                                 if(cliprect.x1<cliprect.x0){
				                                                  cliprect.x1=cliprect.x0;
				                                                  valid=false;
				                                                 };
				                                                 if(cliprect.y1<cliprect.y0){
				                                                  cliprect.y1=cliprect.y1;
				                                                  valid=false;
				                                                 };
				                                                 if(valid){
				                                                  gra->sichtbereich(cliprect.x0,cliprect.y0,cliprect.x1-cliprect.x0,cliprect.y1-cliprect.y0);
				                                                  return(true);
				                                                 }else{
				                                                  return(false);
				                                                 };
				                                                }else{
				                                                 _iggsystem*g=iggsystem();
				                                                 if(g) gra->sichtbereich(0,0,g->breite(),g->hoehe());
				                                                 return(true);
				                                                };
				                                                return(true);
};				
void _igg::animierenkind(_maus<_tg>*mau,_tastatur*tas){
				                                                if(visible){//active
				                                                 _igg*git;
				                                                 if(anfang(git))do{
				                                                  if(git->hilfeparent==0){
				                                                   git->positiontransformed=positiontransformed;
				                                                   git->positiontransformed+=git->position.lesen();
																   if(git->transformation.x()!=0){
																	git->positiontransformed.x(git->positiontransformed.x()+git->size.x()*git->transformation.x());
																   };
				                                                  };
				                                                  git->animieren(mau,tas);
				                                                 }while(naechstes(git));
				                                                };
};
void _igg::animierenhilfe(_maus<_tg>*mau){
				                                                if(hilfe){
				                                                 _iggsystem*g=iggsystem();
				                                                 _tg mx=mau->x();
				                                                 _tg my=mau->y();
				                                                 if((active)&&(superinactive==false)&&(visible)&&(superinvisible==false)){
				                                                  bool i=inner(mau);
				                                                  if((i)&&(hilfe->active==false)&&( (g->clock->system()-hilfetimefalse)>(hilfedelaytime*1000) )){
				                                                   hilfe->positiontransformed=positiontransformed;
				                                                   _tg xx=mx-hilfe->breite()/2+hilfepositionx;
				                                                   _tg yy=my+hilfepositiony;
				                                                   if(xx<5) xx=5;
				                                                   if(yy<5) yy=5;
				                                                   if((xx+hilfe->breite())>=(g->breite()-5)) xx=g->breite()-5-hilfe->breite();
				                                                   if((yy+hilfe->hoehe())>=(g->hoehe()-5)) yy=g->hoehe()-5-hilfe->hoehe();
				                                                   hilfe->positiontransformed.x(xx);
				                                                   hilfe->positiontransformed.y(yy);
				                                                   hilfe->positiontransformed.z(positiontransformed.z()-10);
				                                                   hilfe->fadeopacity(0);
				                                                   hilfe->fadein();
				                                                  }else if((i==false)&&(hilfe->active)){
				                                                   hilfe->fadeout();
				                                                  };
				                                                  if(i==false){
				                                                   hilfetimefalse=iggsystem()->clock->system();
				                                                  };
				                                                 };
				                                                };
};	
void _igg::animierenhilfefadeout(_maus<_tg>*mau){
				                                                if(hilfe){
				                                                 _iggsystem*g=iggsystem();
				                                                 _tg mx=mau->x();
				                                                 _tg my=mau->y();
				                                                 bool i=inner(mau);
				                                                 if((active)&&(i)&&(hilfe->active==false)&&( (g->clock->system()-hilfetimefalse)>(hilfedelaytime*1000) )){
                                                				  
				                                                 }else if((i==false)&&(hilfe->active)){
				                                                  hilfe->fadeout();
				                                                 };
				                                                 if(i==false){
				                                                  hilfetimefalse=iggsystem()->clock->system();
				                                                 };
				                                                };
};							
void _igg::hilfefadeout(){
				                                                if(hilfe)hilfe->fadeout();
};				                                                
void _igg::animierenfade(){
				                                                //fadespeed is part/sec
				                                                _iggsystem*g=iggsystem();
				                                                if(g==0){ //***************** DEBUG *************
				                                                 if(hilfeparent){
				                                                  _iggtext*gt=dynamic_cast<_iggtext*>(hilfeparent);
				                                                  if(gt){
				                                                    //Print gt.get()
				                                                  };
				                                                 };
				                                                 //DebugStop
				                                                 return;
				                                                };//*********************************************
				                                                int fadetimenew=g->clock->system();
				                                                _tg ds=_tg(fadetimenew-fadetimeold)*0.001;
				                                                fadetimeold=fadetimenew;
				                                                if(pfadein){
				                                                 //Print "fin"+colortransformed.w()
				                                                 pfadeopacity+=_to(g->fadespeed*ds);
				                                                 if(pfadeopacity>pfadetarget){
				                                                  pfadeopacity=pfadetarget;
				                                                  pfadein=false;
				                                                  //activate()
				                                                  //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! ACHTUNG war voher _: //activity(true)
				                                                 };
				                                                 updatefadeopacity();
				                                                };
				                                                if(pfadeout){
				                                                 //Print "fout"+colortransformed.w()
				                                                 pfadeopacity-=_to(g->fadespeed*ds);
				                                                 if(pfadeopacity<0){
				                                                  pfadeopacity=0;
				                                                  pfadeout=false;
				                                                  visibility(false);
				                                                  deactivate();
				                                                  if(pfadeouttosuperinactive) superinactivity(true);
				                                                  if(pfadeouttosuperinvisible) superinvisibility(true);
				                                                  if(pfadeouttoclear) g->addtoclear(this);
				                                                  pfadeouttosuperinactive=false;
				                                                  pfadeouttosuperinvisible=false;
				                                                 };
				                                                 updatefadeopacity();
				                                                };
				                                                animierenfadekind();
};				
void _igg::animierenfadekind(){
                                                                _igg*git;
				                                                if(anfang(git))do{//For Local git:_igg=EachIn kindlist
				                                                 git->animierenfade();
				                                                }while(naechstes(git));
};
void _igg::clearbackground(){
                                                                for(int i=0;i<3;i++){
                                                                 background[i].aushaengen();
                                                                };
};				
void _igg::setshadow(_tg pdx,_tg pdy,_to po){
				                                                shadowdirection.setzen(pdx,pdy,0);
				                                                shadowdirectiontransformed.setzen(pdx,pdy,0);
				                                                shadowopacity=po;
				                                                shadow=true;
};
void _igg::deactivate(){
				                                                active=false;
				                                                if(iggsystem()->focus==this) iggsystem()->focus=0;
                                                				//animieren(0,0);!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
};						
void _igg::activate(){
				                                                active=true;
				                                                //animieren(0,0);!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
};		
bool _igg::focus(){
				                                                if(iggsystem()->focus==this) return(true); else return(false);
};	
void _igg::setfocus(){
				                                                _iggsystem*g=iggsystem();
				                                                g->focus=this;
};							
void _igg::updatefadeopacity(){			
				                                                fadeopacity(pfadeopacity);
};		
void _igg::updatefadeopacityrecursive(_to o){
				                                                pfadeopacity=o;
				                                                _igg*git;
				                                                if(anfang(git))do{
				                                                 git->updatefadeopacityrecursive(o);
				                                                }while(naechstes(git));
};			
void _igg::fadeout(bool tosuperinact,bool tosuperinvis,bool toclear){
				                                                activity(false);
				                                                pfadein=false;
				                                                pfadeout=true;
				                                                pfadeouttosuperinactive=tosuperinact;
				                                                pfadeouttosuperinvisible=tosuperinvis;
				                                                pfadeouttoclear=toclear;
				                                                fadetimeold=iggsystem()->clock->system();

};
void _igg::fadein(){		
				                                                if(superinvisible==false){
				                                                 visibility(true);
				                                                 activity(true);
				                                                 marking(0);
				                                                 pfadeouttosuperinactive=false;
				                                                 pfadeouttosuperinvisible=false;
				                                                 pfadein=true;
				                                                 pfadeout=false;
				                                                 fadetimeold=iggsystem()->clock->system();
				                                                };
				
};						
void _igg::fadetarget(_to ft){
	 			                                                pfadetarget=ft;
	 			                                                _igg*git;
				                                                if(anfang(git))do{
				                                                 git->fadetarget(ft);
				                                                }while(naechstes(git));
};	
void _igg::fadeoff(){
	 			                                                pfadein=false;
				                                                pfadeout=false;
				                                                _igg*git;
				                                                if(anfang(git))do{
				                                                 git->fadeoff();
				                                                }while(naechstes(git));
};	
bool _igg::fading(){
				                                                if(pfadein) return(true);
				                                                if(pfadeout) return(true);
				                                                return(false);
};
void _igg::activity(bool v){
				                                                active=v;
				                                                if(v==false){
				                                                 if(hilfe){
				                                                  hilfe->fadeout();
				                                                 };	
				                                                };					
                                                  				//animieren(0);!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				                                                _igg*git;
				                                                if(anfang(git))do{
				                                                 git->activity(v);
				                                                }while(naechstes(git));
};				
void _igg::superinactivity(bool v){
				                                                superinactive=v;
				                                                if(v==true){
				                                                 if(hilfe){
				                                                  hilfe->fadeout();
				                                                 };	
				                                                };					
				                                                //animieren(0);!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				                                                _igg*git;
				                                                if(anfang(git))do{
                                               		    		 git->superinactivity(v);
				                                                }while(naechstes(git));
};				
void _igg::visibility(bool v){
				                                                visible=v;
				                                                _igg*git;
				                                                if(anfang(git))do{
                                              				     git->visibility(v);
				                                                }while(naechstes(git));
};				
void _igg::superinvisibility(bool v){
				                                                superinvisible=v;
				                                                _igg*git;
				                                                if(anfang(git))do{
				                                                 git->superinvisibility(v);
				                                                }while(naechstes(git));
};				
void _igg::fadeopacity(_to o){
				                                                pfadeopacity=o;
				                                                _igg*git;
				                                                if(anfang(git))do{
                                                				 git->fadeopacity(o);
				                                                }while(naechstes(git));
};			
void _igg::marking(int m){
				                                                marked=m;
				                                                _igg*git;
				                                                if(anfang(git))do{
                                                				 git->marking(m);
				                                                }while(naechstes(git));
};				
void _igg::saveactivityrecursive(_liste<_igg>*l,_igg*exgui){
                                                				if(active) l->einhaengen(this);
				                                                _igg*git;
				                                                if(anfang(git))do{
				                                                 if(exgui){
				                                                  if(exgui!=git) git->saveactivityrecursive(l,exgui);
				                                                 }else{
				                                                  git->saveactivityrecursive(l);
				                                                 };
				                                                }while(naechstes(git));
};				
unsigned int _igg::count(){
				                                                unsigned int c=1;
				                                                _igg*git;
				                                                if(anfang(git))do{
				                                                 c+=git->count();
				                                                }while(naechstes(git));
				                                                return(c);
};				
//*******************************************************************************************************************************************************************************
//                                                              G U I S Y S T E M 
//*******************************************************************************************************************************************************************************
_iggsystem::_iggsystem(_guifenster*gf,_tg w,_tg h):_igg(0,0,0,0,w,h,0){
																guifenster=gf;
                                                                size.setzen(w,h,1,false);
                                                                nullstates(0,0);
                                                                color.setzen(1,1,1,1);
                                                                colortransformed=color;
                                                                for(int i=0;i<4;i++) dip[i]=0;
                                                                position.setzen(0,0,0);
                                                                positiontransformed.setzen(0,0,0);
                                                                clock=new _win::_zeit();
                                                                mouseposx=0;
                                                                mouseposy=0;
                                                                mouseposz=0;
                                                                mousebutton[0]=false;
                                                                mousebutton[1]=false;
                                                                mousebutton[2]=false;
                                                                mousebutton[3]=false;
                                                                cursorimage=0;
                                                                fadespeed=2;
                                                                focus=0;
                                                                button=0;
                                                                trackbar=0;
                                                                scrollbarvertical=0;
                                                                listbox=0;
                                                                checkbox=0;
                                                                combobox=0;
                                                                editbox=0;
                                                                text=0;
                                                                image=0;
                                                                mesh=0;
                                                                window=0;
                                                                buttonpush=0;
                                                                trackbarpush=0;
                                                                scrollbarverticalpush=0;
                                                                listboxpush=0;
                                                                checkboxpush=0;
                                                                comboboxpush=0;
                                                                editboxpush=0;
                                                                textpush=0;
                                                                imagepush=0;
                                                                meshpush=0;
                                                                windowpush=0;
                                                                doubleclickleft=false;
                                                               // key=0;
                                                                scrollbartrack=0;
                                                                trackbartrack=0;
};
_iggsystem::~_iggsystem(){
                                                                _listenknoten<_igg>*iit;
                                                                _liste<_igg> ll;
                                                                clearhilfeglobal(this);
                                                                if(drawlist.anfang(iit))do{
                                                                 ll.einhaengen(iit->objekt());
                                                                }while(drawlist.naechstes(iit));
                                                                
                                                                if(ll.anfang(iit))do{
                                                                 deletesecure(iit->objekt()->linkzeichnen);
                                                                }while(ll.naechstes(iit));
                                                                
                                                                
                                                                drawlist.aushaengen();
                                                                ll.aushaengen();
				                                                processtoclear();				
};				
void _iggsystem::clearhilfeglobal(_igg*igg){
																igg->loeschenhilfe();
																_igg*it;
																if(igg->anfang(it))do{
															     clearhilfeglobal(it);
																}while(igg->naechstes(it));
};
void _iggsystem::zeichnen(_grafik*gra,_kamera<_tg>*cam){
				                                                gra->orthonormal();
																gra->textur(true);
				                                                gra->ausschussflaeche(false);
																gra->tiefenbufferschreiben(false);
																gra->tiefenbufferkondition(false);
				                                              //  drawlist.sortieren();
				                                                _listenknoten<_igg>*git;
				                                                if(drawlist.anfang(git))do{
				                                                 if(git->objekt()->visible) git->objekt()->zeichnen(gra,cam);
				                                                }while(drawlist.naechstes(git));
				                                                gra->sichtbereich(0,0,breite(),hoehe());
};
void _iggsystem::zeichnenbackground(_grafik*gra,_kamera<_tg>*cam){
				                                                _bild<_tb>*bm=bestbreitematch();
				                                                if(bm){
				                                                 //SetBlend(SOLIDBLEND);
				                                                 //SetAlpha(colortransformed.w()*pfadeopacity);
				                                                 //SetColor(colortransformed.x*255,colortransformed.y*255,colortransformed.z()*255);
				                                                 _vektor4<_to> c=colortransformed;
				                                                 c.w(c.w()*pfadeopacity);
				                                                 gra->transparenz(false);
				                                                 gra->rechteck(bm,0,0,breite(),hoehe(),c);
				                                                }else{
				                                                 //SetClsColor(colortransformed.x*255,colortransformed.y*255,colortransformed.z()*255);
				                                                 //SetAlpha(colortransformed.w()*pfadeopacity);
				                                                 //Cls();				 
				                                                };
};
void _iggsystem::zeichnencursor(_maus<_tg>*mau,_grafik*gra,_kamera<_tg>*cam){
				                                                if(cursorimage){
     			                                                 //SetColor(255,255,255);
     			                                                 //SetBlend(MASKBLEND);
     			                                                 //SetBlend(ALPHABLEND);
				                                                 //SetAlpha(0.5);
				                                                 gra->transparenz(true);
				                                                 gra->transparenzmultiplikativ();
     			                                                 gra->rechteck(cursorimage,mau->x()-64,mau->y()-64,cursorimage->groesse(0),cursorimage->groesse(1),_vektor4<_to>(1,1,1,0.5));
     		                                                     //SetBlend(SOLIDBLEND);
				                                                };
};
void _iggsystem::addtoclear(_igg*g){
				                                                toclear.einhaengen(g);
};			
void _iggsystem::processtoclear(){
                                                                toclear.loeschen();
};				
void _iggsystem::setzenstatus(){
};				
void _iggsystem::nullstates(_maus<_tg>*mau,_tastatur*tas){
				                                                button=0;
				                                                trackbar=0;
				                                                scrollbarvertical=0;
				                                                listbox=0;
				                                                checkbox=0;
				                                                combobox=0;
				                                                editbox=0;
				                                                text=0;
				                                                image=0;
				                                                mesh=0;
				                                                window=0;
				                                                doubleclickleft=false;
				                                                if(mau){
				                                                 mouseposx=int(mau->x());
				                                                 mouseposy=int(mau->y());
				                                                 mouseposz=int(mau->z());
				                                                }else{
				                                                 mouseposx=0;
				                                                 mouseposy=0;
				                                                 mouseposz=0;
				                                                };
				                                                mousebutton[0]=0;
				                                                if(tas){
				                                                 mousebutton[1]=tas->knopflinks();
				                                                 mousebutton[2]=tas->knopfrechts();
				                                                 mousebutton[3]=tas->knopfmitte();
				                                                }else{
				                                                 mousebutton[1]=false;
				                                                 mousebutton[2]=false;
				                                                 mousebutton[3]=false;
				                                                };
};
void _iggsystem::pushstates(){
				                                                buttonpush=button;
				                                                trackbarpush=trackbar;
				                                                scrollbarverticalpush=scrollbarvertical;
				                                                listboxpush=listbox;
				                                                checkboxpush=checkbox;
				                                                comboboxpush=combobox;
				                                                editboxpush=editbox;
				                                                textpush=text;
				                                                imagepush=image;
				                                                meshpush=mesh;
				                                                windowpush=window;
};				
bool _iggsystem::comparestates(){
				                                                if(buttonpush!=button)return(false);
				                                                if(trackbarpush!=trackbar)return(false);
				                                                if(scrollbarverticalpush!=scrollbarvertical) return(false);
				                                                if(listboxpush!=listbox)return(false);
				                                                if(checkboxpush!=checkbox)return(false);
				                                                if(comboboxpush!=combobox)return(false);
				                                                if(editboxpush!=editbox)return(false);
				                                                if(textpush!=text)return(false);
				                                                if(imagepush!=image)return(false);
				                                                if(meshpush!=mesh)return(false);
				                                                if(windowpush!=window)return(false);
				                                                return(true);
};				
void _iggsystem::animieren(_maus<_tg>*mau,_tastatur*tas){
				                                                nullstates(mau,tas);
				                                                animierenkind(mau,tas);
				                                               // animierenhilfe(mau);
				                                              //  processtoclear();
};
void _iggsystem::animierenfade(){
                                                                _igg*git;
                                                                if(anfang(git))do{
                                                                 git->animierenfade();
                                                                }while(naechstes(git));
                                                				processtoclear();
};
void _iggsystem::animierenhilfefadeoutglobalrecursive(_igg*gui){
                                                                _igg*git;
                                                                if(gui->anfang(git))do{
				                                                 git->hilfefadeout();
				                                                 animierenhilfefadeoutglobalrecursive(git);
                                                                }while(gui->naechstes(git));
};
void _iggsystem::animierenhilfefadeoutglobal(){
                                                                _igg*git;
                                                                if(anfang(git))do{
				                                                 git->hilfefadeout();
				                                                 animierenhilfefadeoutglobalrecursive(git);
                                                                }while(naechstes(git));
};				
bool _iggsystem::mouseovergui(_maus<_tg>*mau){
				                                                int mx=int(mau->x());
				                                                int my=int(mau->y());
                                                                _igg*git;
                                                                if(anfang(git))do{
                                                				 if(git->visible) if(git->mouseovergui(mau)) return(true);
                                                                }while(naechstes(git));
				                                                return(false);
};	
void _iggsystem::saveactivitylist(_igg*exgui){
				                                                psaveactivitylist.aushaengen();
                                                                _igg*git;
                                                                if(anfang(git))do{
				                                                 if(exgui){
				                                                  if(git!=exgui) git->saveactivityrecursive(&psaveactivitylist,exgui);
				                                                 }else{
				                                                  git->saveactivityrecursive(&psaveactivitylist);
				                                                 };
                                                                }while(naechstes(git));
};
void _iggsystem::setactivitylist(bool a){
	                                                            _listenknoten<_igg>*git;
	                                                            if(psaveactivitylist.anfang(git))do{
				                                                git->objekt()->active=a;
				                                                }while(psaveactivitylist.naechstes(git));
};
void _iggsystem::restoreactivitylist(){
	                                                            _listenknoten<_igg>*git;
	                                                            if(psaveactivitylist.anfang(git))do{
				                                                 git->objekt()->active=true;
				                                                }while(psaveactivitylist.naechstes(git));
				                                                psaveactivitylist.aushaengen();
};	
unsigned int _iggsystem::count(){
                                                                unsigned int c=1;
                                                                _igg*git;
                                                                if(anfang(git))do{
                                                                 c+=git->count();
                                                                }while(naechstes(git));
                                                                return(c);
};			
_zeichenkette<_tt> _iggsystem::clipboardtext(){
																_zeichenkette<_tt> h;
																if (IsClipboardFormatAvailable(CF_TEXT)) {
																 char*pszData;
																 HANDLE hData;
																 LPVOID pData;
																	
																 OpenClipboard(guifenster->handle());
																 hData = GetClipboardData(CF_TEXT);
																 pData = GlobalLock(hData);
																	
																 pszData = (char*)malloc(strlen((char*)pData) + 1);
																 strcpy(pszData, (LPSTR)pData);
																 GlobalUnlock(hData);
																 CloseClipboard();
																	
																 h.kopierenchar(pszData);
																 
																 delete pszData;
																 pszData=0;
																};
																return(h);
};																 
//*******************************************************************************************************************************************************************************
//                                                              B U T T O N
//*******************************************************************************************************************************************************************************
_iggbutton::_iggbutton(_igg*pg,_tg px,_tg py,_tg pw,_tg ph,const _zeichenkette<_tt>&pn,_zeichensatz*zs,int pin):_igg(pg,px,py,-1,pw,ph,pin){
                                                                text=pn;
                                                                font=zs;
                                                                image=0;
                                                                imagedx=0;
                                                                imagedy=0;
                                                                centric=false;
                                                                centrictext=false;
                                                                textshadow=1;
                                                                //dynamische zustands skalierung
                                                                dynamicactivityscale=false;
                                                                dynamicactivityscalevalueactual=0;		//actual, displayed and performed rotation value
                                                                dynamicactivityscalevalue=0;				//the value that should be matched
                                                                dynamicactivityscalevector=0;
                                                                dynamicactivityscalevelocity=6;
                                                                dynamicactivityscalefriction=0.8;
                                                                dynamicactivityscaletime=0;
                                                                textcolor.setzen(1,1,1,1);
                                                                //textcolororiginal=iggsystem()->colors.std);
                                                                textcolormark.setzen(_to(0.784f),_to(-0.686f),_to(0.588f),0);
                                                                textcoloractive.setzen(1,_to(-0.784f),_to(-0.588f),0);
				                                                color=iggsystem()->colors.std;
				                                                color.w(1);
				                                                colortransformed=color;
				                                                //textcolororingal=copy)
				                                                dynamicactivityscaletime=iggsystem()->clock->system();
				                                                benutzenfontliste=false;
};				
_iggbutton::~_iggbutton(){
};
void _iggbutton::setimage(_bild<_tb>*b,_tg dx,_tg dy){
				                                                imagedx=dx;
				                                                imagedy=dy;
				                                                image=b;
};
void _iggbutton::settextcolor(_vektor4<_to>&t){
				                                                textcolor=t;
				                                                textcolororiginal=t;
};		
_zeichensatz* _iggbutton::bestfontbreite(){
				                                                if(benutzenfontliste){
				                                                 _zeichensatz*f=0;
				                                                 _tg dmin=100000;
				                                                 _tg w=hoehe();
				                                                 _listenknoten<_zeichensatz>*fit;
				                                                 if(fontliste.anfang(fit))do{
				                                                  _tg d=fabs(1- ( (w-50)/fit->objekt()->hoehe(_zeichenkette<_tt>(L"REEFERENZ"))) );
				                                                  if(dmin>d){
				                                                   f=fit->objekt();
				                                                   dmin=d;
				                                                  };
				                                                 }while(fontliste.naechstes(fit));
				                                                 if(f) return(f); else return(font);
				                                                }else{
				                                                 return(font);
				                                                };
};
void _iggbutton::zeichnenschatten(_grafik*gra,_kamera<_tg>*cam){
				                                                if((visible)&&(superinvisible==false)){
				                                                 if(shadow){
				                                                  _bild<_tb>*bm=bestbreitematch();
				                                                  _bild<_tb>*sm=bestshadowmatch();
				                                                  _tg das=dynamicactivityscalevalueactual;
				                                                  if(dynamicactivityscale==false) das=0;				
				                                                  gra->transparenz(true);
				                                                  gra->transparenzmultiplikativ();
				                                                  _vektor4<_to> cc(0,0,0,shadowopacity*colortransformed.w()*pfadeopacity);
				                                                  if((bm)&&(sm==0)){//bildschatten (standard)
				                                                   if(dynamicactivityscale==false){
				                                                    gra->rechteck(bm,positiontransformed.x()+shadowdirectiontransformed.x(),positiontransformed.y()+shadowdirectiontransformed.y(),breite(),hoehe(),cc);
				                                                   }else{
				                                                    _tg ld=4+(das+2)*2;
			 		                                                if(ld<0) ld=0;
				                                                    gra->rechteck(bm,positiontransformed.x()+ld,positiontransformed.y()+ld,breite()+2*das,hoehe()+2*das,cc);
				                                                   };
				                                                  }else if((sm==0)&&(bm==0)){//provisorischer schatten
				                                                   gra->transparenz(true);
				                                                   gra->transparenzmultiplikativ();
																   gra->textur(false);

				                                                   if(dynamicactivityscale==false){
				                                                    gra->rechteck(positiontransformed.x()+shadowdirectiontransformed.x(),positiontransformed.y()+shadowdirectiontransformed.y(),breite(),hoehe(),cc);
				                                                   }else{
				                                                    _tg ld=4+(das+2)*2;
			 		                                                if(ld<0) ld=0;
				                                                    gra->rechteck(positiontransformed.x()+das,positiontransformed.y()+das,breite()+2*das,hoehe()+2*das,cc);
				                                                   };
																   gra->textur(true);

				                                                  }else if(sm){//eigener schatten
				                                                   gra->transparenz(true);
				                                                   gra->transparenzmultiplikativ();
				                                                   _tg be=shadowimageboardening;
				                                                   if(dynamicactivityscale==false){
				                                                    gra->rechteck(sm,(positiontransformed.x()+shadowdirectiontransformed.x())-be,(positiontransformed.y()+shadowdirectiontransformed.y())-be,breite()+be*2,hoehe()+be*2,cc);
				                                                   }else{
			                                                        _tg ld=4+(das+2)*2;
			 		                                                if (ld<0) ld=0;
				                                                    gra->rechteck(sm,(positiontransformed.x()+ld)-be,(positiontransformed.y()+ld)-be,breite()+be*2+das*2,hoehe()+be*2+das*2,cc);
				                                                   };
				                                                  };
				                                                 };
				                                                };
};				
void _iggbutton::zeichnen(_grafik*gra,_kamera<_tg>*cam){
                                                                if((visible)&&(superinvisible==false)){
                                                                 _vektor3<_tg> p;
                                                                 colorhilfe=colortransformed;
                                                                 colorhilfe.w(colorhilfe.w()*pfadeopacity);
                                                                 _tg w=breite();
                                                                 _tg h=hoehe();
                                                                 _tg das=dynamicactivityscalevalueactual;
                                                                 if(dynamicactivityscale==false) das=0;
                                                                 parent->clip(gra);
                                                                 zeichnenschatten(gra,cam);
                                                                 p=positiontransformed;
                                                                 if(centric){
                                                                  p.x(p.x()-w/2);
                                                                  p.y(p.y()-h/2);
                                                                 };				
                                                                 //----------------------background zeichnen------------
                                                                 _bild<_tb>*bm=bestbreitematch();
                                                                 if(bm){
				                                                  gra->transparenz(true);
				                                                  gra->transparenzmultiplikativ();
				                                                  //L->schreiben("button : px=",(_tg)p.x());
                                                                  gra->rechteck(bm,p.x()-das,p.y()-das,w+das*2,h+das*2,colorhilfe);
                                                                 }else{
							                                      gra->transparenz(true);
				                                                  gra->transparenzmultiplikativ();
                                                                  _vektor3<_tg> pdas;
                                                                  pdas=p;
                                                                  pdas.x(pdas.x()-das);
                                                                  pdas.y(pdas.y()-das);
                                                                  colorhilfe=colortransformed;
                                                                  colorhilfe.w(colorhilfe.w()*pfadeopacity);
                                                                  if(marked==2){
                                                                   zeichnenguiboxinvers(gra,pdas,w+das*2,h+das*2,colorhilfe);
                                                                  }else{
                                                                   zeichnenguibox(gra,pdas,w+das*2,h+das*2,colorhilfe);
                                                                  };
                                                                 };
                                                                 //------------------------textzeichnen-----------------
                                                               
																 _zeichensatz*f=bestfontbreite();
                                                                 colorhilfe=textcolor;
                                                                 colorhilfe.w(colorhilfe.w()*pfadeopacity);
                                                                 if(centrictext){
                                                                  p=positiontransformed;
                                                                  p.x(p.x()+(w/2-f->breite(text)/2));
                                                                  p.y(p.y()+(h/2-f->hoehe(text)/2));
                                                                  p.z(textshadow);
                                                                  zeichnenguitext(gra,text,f,p,colorhilfe);
                                                                 }else{
                                                                  p=positiontransformed;
                                                                  p.x(p.x()+5);
                                                                  p.y(p.y()+5);
                                                                  p.z(textshadow);
                                                                  if(text!=L"") zeichnenguitext(gra,text,f,p,colorhilfe);
                                                                 };
                                                                 //----------------------image zeichnen-----------------
                                                                 if(image){
				                                                  gra->transparenz(true);
				                                                  gra->transparenzmultiplikativ();
                                                                  gra->rechteck(image,positiontransformed.x()+imagedx+positiontransformed.z(),positiontransformed.y()+imagedy+positiontransformed.z(),image->groesse(0),image->groesse(1),_vektor4<_to>(0,0,0,_to(0.4f)*colortransformed.w()*pfadeopacity));
				                                                  gra->transparenz(true);
				                                                  gra->transparenzmultiplikativ();
                                                                  gra->rechteck(image,imagedx+positiontransformed.x(),imagedy+positiontransformed.y(),image->groesse(0),image->groesse(1),_vektor4<_to>(1,1,1,colortransformed.w()*pfadeopacity));
                                                                  gra->transparenz(false);
                                                                 };
                                                                 gra->transparenz(false);
                                                                };
};	
void _iggbutton::animierenscale(){		
				                                                if(dynamicactivityscale){
				                                                 _tg nt=iggsystem()->clock->system();
				                                                 _tg dt=nt-dynamicactivityscaletime;
				                                                 dynamicactivityscaletime=nt;
				                                                 _tg d;
				                                                 if(dt>(16*4)) dt=16*4;
				                                                 d=(dynamicactivityscalevalue)-dynamicactivityscalevalueactual;
				                                                 d*=dynamicactivityscalevelocity*(dt*0.001);
				                                                 dynamicactivityscalevector+=d;
				                                                 dynamicactivityscalevalueactual+=dynamicactivityscalevector;
				                                                 dynamicactivityscalevector*=dynamicactivityscalefriction;								
				                                                };
};				
void _iggbutton::animieren(_maus<_tg>*mau,_tastatur*tas){
                                                                _iggsystem*gs=0;
                                                                if(dynamicactivityscale) animierenscale();
                                                                if((active)&&(superinactive==false)){
                                                                 gs=iggsystem();			 
                                                                 if((gs->scrollbartrack==0)&&(gs->trackbartrack==0)){
                                                                  int mx=int(mau->x());
                                                                  int my=int(mau->y());
                                                                  bool gedr=false;
                                                                  int mv=marked;
                                                                  if(marked==2){
                                                                   if(tas->knopflinks()==false){
                                                                    if(inner(mau)){
                                                                     gedr=true;
                                                                     marked=0;
                                                                    }else{
                                                                     marked=0;
                                                                    };
                                                                    textcolor=textcolororiginal;
                                                                    if(dynamicactivityscale==false){
                                                                     shadowdirectiontransformed=shadowdirection;
                                                                    };
                                                                    dynamicactivityscalevalue=0;
                                                                   }else{
                                                                    if(inner(mau)==false){
                                                                     marked=0;
                                                                     textcolor=textcolororiginal;
                                                                     if(dynamicactivityscale==false){ 
                                                                      shadowdirectiontransformed=shadowdirection;
                                                                     };
                                                                     dynamicactivityscalevalue=0;
                                                                    };
                                                                   };
                                                                  };
                                                                  if(marked==1){
                                                                   if(inner(mau)){
                                                                    if(tas->knopflinks()){
                                                                     marked=2;
                                                                     textcolor=textcolororiginal;
                                                                     textcolor+=textcoloractive;
                                                                     textcolor.begrenzen(0,1);
                                                                     if(dynamicactivityscale==false){
                                                                      shadowdirectiontransformed=shadowdirection;
                                                                      shadowdirectiontransformed.mul(0.6);
                                                                     };
                                                                     dynamicactivityscalevalue=-2;
                                                                    };
                                                                   }else{
                                                                    marked=0;
                                                                    textcolor=textcolororiginal;
                                                                    if(dynamicactivityscale==false){ 
                                                                     shadowdirectiontransformed=shadowdirection;
                                                                    };
                                                                    dynamicactivityscalevalue=0;
                                                                   };
                                                                  };				
                                                                  if(marked==0){
                                                                   if(inner(mau)){
                                                                    marked=1;
                                                                    textcolor=textcolororiginal;
                                                                    textcolor+=textcolormark;
                                                                    textcolor.begrenzen(0,1);
                                                                    if(dynamicactivityscale==false){
                                                                     shadowdirectiontransformed=shadowdirection;
                                                                     shadowdirectiontransformed*=0.8;
                                                                    };
                                                                    dynamicactivityscalevalue=2;
                                                                   }; 
                                                                  };
                                                                  if(mv!=marked){
                                                                   //if(mv==0) playsoundstretched(gs->dip[0],1,1,1);!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                                                                   if(mv==1){
                                                                    //if(marked==2) playsoundstretched(gs->dip[1],1,1,1);!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                                                                   };
                                                                  };
                                                                  //if(gedr) playsoundstretched(gs->dip[3],0.5,1,1);!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                                                                  if(gedr) gs->button=this;
                                                                 };
                                                                };
                                                                animierenkind(mau,tas);
                                                                animierenhilfe(mau);
};
void _iggbutton::marking(int m){
                                                                if(superinactive==false){
                                                                 marked=m;
                                                                 if(marked==0){
	                                                              textcolor=textcolororiginal;
	                                                              shadowdirectiontransformed=shadowdirection;
                                                                 };
                                                                 if(marked==1){
	                                                              textcolor=textcolororiginal;
	                                                              textcolor.add(textcolormark);
	                                                              textcolor.begrenzen(0,1);
	                                                              shadowdirectiontransformed=shadowdirection;
	                                                              shadowdirectiontransformed.mul(0.8);
                                                                 };
                                                                 if(marked==2){
	                                                              textcolor=textcolororiginal;
	                                                              textcolor.add(textcoloractive);
	                                                              textcolor.begrenzen(0,1);
	                                                              shadowdirectiontransformed=shadowdirection;
	                                                              shadowdirectiontransformed.mul(0.6);
                                                                 };
                                                                 _igg*git;
                                                                 if(anfang(git))do{
	                                                              git->marking(m);
                                                                 }while(naechstes(git));
                                                                };
};
void _iggbutton::demark(){
                                                                color=iggsystem()->colors.std;
                                                                textcolor.setzen(_to(0.6f),_to(0.6f),_to(0.6f),1);
                                                                marked=0;
};
void _iggbutton::push(){
				                                                marked=2;
};		
void _iggbutton::setzenstatus(){
				                                                iggsystem()->button=this;
};				
//*******************************************************************************************************************************************************************************
//                                                              C H E C K B O X
//*******************************************************************************************************************************************************************************
_iggcheckbox::_iggcheckbox(_igg*pg,_tg px,_tg py,_tg pw,_tg ph,int pin):_igg(pg,px,py,-1,pw,ph,pin){
	                                                            checkimage=0;
	                                                            checkimagebreite=10;								
	                                                            checkimagehoehe=10;									
	                                                            checked=false;		
	                                                            crosslinkmesh=0;
	                                                            crosslinkimage=0;
	                                                            setshadow(10,10,_to(0.3f));
				                                                if(pw<5) pw=5;
				                                                if(ph<5) ph=5;
				                                                color.setzen(1,1,1,color.w());
				                                                colortransformed=color; 
};
_iggcheckbox::~_iggcheckbox(){
};
void _iggcheckbox::setcheckimage(_bild<_tb>*t){
                                                				checkimage=t;
};				
void _iggcheckbox::zeichnen(_grafik*gra,_kamera<_tg>*cam){
                                                                if((visible)&&(superinvisible==false)){
                                                                 parent->clip(gra);
                                                                 zeichnenschatten(gra,cam);
                                                                 if((shadow)&&(checked)&&(checkimage)){
                                                                  _bild<_tb>*bm=checkimage;
                                                                  colorhilfe.setzen(0,0,0,shadowopacity*colortransformed.w()*pfadeopacity);
                                                                  gra->transparenz(true);
                                                                  gra->transparenzmultiplikativ();
                                                                  if(bm){
                                                                   gra->rechteck(bm,positiontransformed.x()+checkposition.x()+shadowdirection.x(),positiontransformed.y()+checkposition.y()+shadowdirection.y(),breite(),hoehe(),colorhilfe);
                                                                  }else{
                                                                   gra->rechteck(positiontransformed.x()+checkposition.x()+shadowdirection.x(),positiontransformed.y()+checkposition.y()+shadowdirection.y(),breite(),hoehe(),colorhilfe);
                                                                  };
                                                                 };
                                                                 _tg w=breite();
                                                                 _tg h=hoehe();
                                                                 _bild<_tb>*bm=bestbreitematch();
                                                                 colorhilfe=colortransformed;
                                                                 colorhilfe.w(colorhilfe.w()*pfadeopacity);
                                                                 if(bm){
                                                                  gra->transparenz(true);
                                                                  gra->transparenzmultiplikativ();
                                                                  gra->rechteck(bm,positiontransformed.x(),positiontransformed.y(),w,h,colorhilfe);
                                                                 }else{
                                                                  zeichnenguibox(gra,positiontransformed,w,h,colorhilfe);
                                                                 };
                                                                 if(checked){
                                                                  if(checkimage){
                                                                   gra->transparenz(true);
                                                                   gra->transparenzmultiplikativ();
                                                                   gra->rechteck(checkimage,positiontransformed.x()+checkposition.x()+w/2-checkimagebreite/2,positiontransformed.y()+checkposition.y()+h/2-checkimagehoehe/2,checkimagebreite,checkimagehoehe,colorhilfe);//-Imagehoehe(checkimage)/2
                                                                  };
                                                                 };
                                                                };
};
void _iggcheckbox::animieren(_maus<_tg>*mau,_tastatur*tas){
				                                                int mx=int(mau->x());
				                                                int my=int(mau->y());
				                                                int mv=marked;
				                                                if((active)&&(superinactive==false)&&(superinvisible==false)){
				                                                 if(marked==2){
				                                                  if(tas->knopflinks()==false){
				                                                   if(inner(mau)){
				                                                    checked=!checked;
				                                                    iggsystem()->checkbox=this;
				                                                    marked=0;
				                                                   }else{
				                                                    marked=0;
				                                                   };
				                                                  }else{
				                                                   if(inner(mau)==false){
				                                                    marked=0;
				                                                   };
				                                                  };
				                                                 };
				                                                 if(marked==1){
				                                                  if(inner(mau)){
				                                                   if(tas->knopflinks()){
				                                                    marked=2;
				                                                   };
				                                                  }else{
				                                                   marked=0;
				                                                  };
				                                                 };
				                                                 if(marked==0){
				                                                  if(inner(mau)){
  				                                                   marked=1;
				                                                  }; 
   			                                                     };
				                                                };	
				                                                animierenkind(mau,tas);
				                                                animierenhilfe(mau);
};		
void _iggcheckbox::setzenstatus(){
				                                                iggsystem()->checkbox=this;
};			
//*******************************************************************************************************************************************************************************
//                                                              G U I S H I F T O U T
//*******************************************************************************************************************************************************************************
_iggshiftout::_iggshiftout(_igg*pg,_tg px,_tg py,_tg pw,_tg ph,_zeichenkette<_tt>&pbuttontext,int pin,_to pr,_to pgr,_to pb,_zeichensatz*f):_igg(pg,px,py,-1,pw,ph,-1){
                                                                orghoehe=ph;
	                                                            button=0;
	                                                            window=0;
	                                                            positionmatch=0;
	                                                            pshiftin=false;
	                                                            pshiftout=false;
	                                                            pshifting=false;
	                                                            pshiftt=0;
	                                                            pshifttime=0;
	                                                            pshiftspeed=350;
	                                                            windowhoeheminimal=5;
	                                                            clock=iggsystem()->clock;
	                                                            font=f;
				                                                color.setzen(pr,pgr,pb,color.w());
				                                                colortransformed=color;				
				                                                button=new _iggbutton(this,0,0,pw,ph,pbuttontext,f,pin);
				                                                button->position.z(button->position.z()-1);
				                                                window=new _iggwindow(this,0,ph,pw,1,pr,pgr,pb);
				                                                window->superinactivity(true);
				                                                window->superinvisibility(true);
				                                                window->activity(false);
				                                                window->visibility(false);
				                                                window->clipkindhierarchical=true;
				                                                window->clipkind=true;
				                                                window->visible=false;
};
_iggshiftout::~_iggshiftout(){
};
void _iggshiftout::animierenshift(){
				                                                if(pshifting){
				                                                 _tg newtime=clock->system();
				                                                 _tg deltat=_tg(newtime-pshifttime)/_tg(1000.0);
				                                                 pshifttime=newtime;
				                                                 if(pshiftt<1){
				                                                  pshiftcurve.berechnen(pshiftt);
				                                                  _tg deltal=pshiftspeed*deltat;
				                                                  _tg dt;
				                                                  if(pshiftcurve.laenge()<nahenull){
				                                                   dt=1;
				                                                  }else{
				                                                   dt=(deltal/pshiftcurve.laenge());
				                                                  };
				                                                  pshiftt+=dt;
				                                                  window->size.y(pshiftcurve.e().y());
				                                                  size.y(pshiftcurve.e().y()+orghoehe);
				                                                 }else{
				                                                  pshiftt=0;
				                                                  window->size.y(pshiftcurve.ort(1).y());
				                                                  size.y(pshiftcurve.ort(1).y()+orghoehe);
				                                                  pshifting=false;
				                                                  if(pshiftin){
				                                                   window->visibility(false);
				                                                   window->visible=false;
				                                                   window->activity(false);
				                                                   //window.superinvisibility(true);
				                                                   window->superinactivity(true);
				                                                  };
				                                                  pshiftin=false;
				                                                  pshiftout=false;
				                                                 };				  
				                                                };
};
void _iggshiftout::shiftout(){
				                                                pshiftout=true;
				                                                pshiftin=false;
				                                                window->visibility(true);
				                                                window->visible=false;
				                                                window->activity(true);
				                                                window->superinactivity(false);
				                                                pshiftcurve.setzen(0,window->size.y(),0, 0,window->kindhoehe()+windowhoeheminimal,0, 0,0,0, 0,0,0);
				                                                pshiftt=0;
				                                                pshifttime=clock->system();
				                                                pshifting=true;
};
void _iggshiftout::shiftin(){
				                                                pshiftout=false;
				                                                pshiftin=true;
				                                                pshiftcurve.setzen(0,window->size.y(),0, 0,1,0, 0,0,0, 0,0,0);
				                                                pshiftt=0;
				                                                pshifttime=clock->system();
				                                                pshifting=true;
};					
void _iggshiftout::setshiftout(bool s){
				                                                pshifting=false;
				                                                pshiftin=false;
				                                                pshiftout=false;
				                                                if(s){
				                                                 window->visibility(true);
				                                                 window->visible=false;
				                                                 window->activity(true);
				                                                 window->superinactivity(false);
				                                                 _tg h=window->kindhoehe()+windowhoeheminimal;
				                                                 window->size.y(h);
				                                                 size.y(h+orghoehe);
				                                                }else{
				                                                 window->visibility(false);
				                                                 window->activity(false);
				                                                 window->superinactivity(true);
				                                                 window->size.y((_tg)1);
				                                                 size.y(orghoehe);
				                                                };
};
bool _iggshiftout::clip(_grafik*gra){
                                                                return(parent->clip(gra));
};				
void _iggshiftout::zeichnen(_grafik*gra,_kamera<_tg>*cam){
};				
void _iggshiftout::animieren(_maus<_tg>*mau,_tastatur*tas){
                                                                if((active)&&(superinactive==false)){
                                                                 animierenshift();
                                                                 animierenkind(mau,tas);
                                                                 if(iggsystem()->button==button){
                                                                  iggsystem()->button=0;
                                                                  if(pshifting==false){
                                                                   if(window->superinactive){
                                                                    shiftout();
                                                                   }else{
                                                                    shiftin();
                                                                   };
                                                                  }else{
                                                                   if(pshiftin){
                                                                    shiftout();
                                                                   }else{
                                                                    shiftin();
                                                                   };
                                                                  };
                                                                 };
                                                                };
                                                                animierenhilfe(mau);
                                                                if(positionmatch) position.y(positionmatch->position.y()+positionmatch->hoehe());
};	
void _iggshiftout::setzenstatus(){
};				
//*******************************************************************************************************************************************************************************
//                                                              G U I C O M B O B O X
//*******************************************************************************************************************************************************************************
_iggcombobox::_iggcombobox(_igg*pg,_tg px,_tg py,_tg pw,_tg ph,_tg pbuttonbreite,int pin,_to pr,_to pgr,_to pb,   _tg lbx,_tg lby,_tg lbw,_tg lbh,_tg lbbw,int lbi, _zeichensatz*f):_igg(pg,px,py,-1,pw-pbuttonbreite,ph,0){
	                                                            listbox=0;
	                                                            button=0;
	                                                            text=0;
	                                                            centrictext=true;
				                                                setshadow(10,10,_to(0.3f));
				                                                font=f;
				                                                color.setzen(pr,pgr,pb,color.w());
				                                                colortransformed=color;
				                                                listbox=new _igglistbox(pg,lbx,lby,lbw,lbh,lbbw,1,1,1);
				                                                listbox->index=lbi;
				                                                listbox->superinvisibility(true);
				                                                listbox->superinactivity(true);
				                                                listbox->activity(false);
				                                                listbox->setshadow(10,10,_to(0.3f));
				                                                button=new _iggbutton(pg,px+(pw-pbuttonbreite),py,pbuttonbreite,ph,L"...",font,pin);
				                                                text=new _iggtext(this,10,10,0,L"init",0,0,0,font);


};
_iggcombobox::~_iggcombobox(){
};
void _iggcombobox::zeichnen(_grafik*gra,_kamera<_tg>*cam){
				                                                if((visible)&&(superinvisible==false)){
				                                                 if(parent) parent->clip(gra);
				                                                 _tg w=breite();
				                                                 _tg h=hoehe();
				                                                 _bild<_tb>*bm=bestbreitematch();
				                                                 zeichnenschatten(gra,cam);
				                                                 colorhilfe=colortransformed;
				                                                 colorhilfe.w(colorhilfe.w()*pfadeopacity);
                                                                 gra->transparenz(true);
                                                                 gra->transparenzmultiplikativ();
				                                                 if(bm){
				                                                  gra->rechteck(bm,positiontransformed.x(),positiontransformed.y(),w,h,colorhilfe);
				                                                 }else{
				                                                  zeichnenguibox(gra,positiontransformed,w,h,colorhilfe);
				                                                 };
				                                                 
				                                                };
};
void _iggcombobox::animieren(_maus<_tg>*mau,_tastatur*tas){
                                                                if((active)&&(superinactive==false)){
                                                                 if(centrictext){
                                                                  //SetImageFont(text->font);
                                                                  _zeichenkette<_tt> h=text->lesen();
                                                                  _tg w=text->font->breite(h)/2;
                                                                  text->position.x(breite()/2-w);
                                                                 };

                                                                 button->animieren(mau,tas);
                                                                 listbox->animieren(mau,tas);
                                                                 if(iggsystem()->button==button){
                                                                  iggsystem()->button=0;
                                                                  if(listbox->superinactive){
                                                                   listbox->superinactivity(false);
                                                                   listbox->superinvisibility(false);
                                                                   listbox->fadeopacity(0);
                                                                   iggsystem()->saveactivitylist(this);
                                                                   iggsystem()->setactivitylist(false);
                                                                   if(button->hilfe) button->hilfe->fadeout();
                                                                   listbox->fadein();
                                                                  }else{
                                                                   listbox->superinactivity(false);
                                                                   listbox->superinvisibility(false);			
                                                                   listbox->fadeout(true,true);
                                                                   iggsystem()->restoreactivitylist();
                                                                  };
                                                                 };
                                                                 if(iggsystem()->listbox==listbox){
                                                                  iggsystem()->listbox=0;
                                                                  _iggtext*gt=dynamic_cast<_iggtext*>(listbox->selection);
                                                                  if(gt){
                                                                   text->setzen(gt->lesen());
                                                                   iggsystem()->combobox=this;
                                                                   listbox->superinactivity(false);
                                                                   listbox->superinvisibility(false);			
                                                                   listbox->fadeout(true,true);
                                                                   iggsystem()->restoreactivitylist();			
                                                                  };
                                                                 };
                                                                 if(( (listbox->inner(mau)==false) )&&( (tas->knopfrechts() || tas->knopflinks()) )&&( iggsystem()->button==0 )){
                                                                  if(listbox->superinactive==false){
                                                                   listbox->superinactivity(false);
                                                                   listbox->superinvisibility(false);			
                                                                   listbox->fadeout(true,true);	
                                                                   iggsystem()->restoreactivitylist();		
                                                                  }; 
                                                                 };
                                                                };
                                                                animierenkind(mau,tas);
                                                                animierenhilfe(mau);
};
void _iggcombobox::setzenstatus(){
				                                                iggsystem()->combobox=this;
};			
void _iggcombobox::dynamisch(_tg wx,_tg wy){
                                                				_igg::dynamisch(wx,wy);
				                                                button->dynamisch(wx,wy);
};
//*******************************************************************************************************************************************************************************
//                                                              E D I T B O X
//*******************************************************************************************************************************************************************************
_iggeditbox::_iggeditbox(_igg*pg,_tg px,_tg py,_tg pw,_tg ph,const _zeichenkette<_tt>&t,_zeichensatz*f,_to pr,_to pgr,_to pb):_igg(pg,px,py,-1,pw,ph,0){
	                                                            text=t;
																textshadowz=1;
				                                                font=f;
	                                                            animw=10;
	                                                            animc=0;
	                                                            animp=0;
	                                                            animtime=0;
	                                                            cursorimage=0;
	                                                            cursorbreite=20;
	                                                            cursorhoehe=8;
	                                                            cursoroffsety=0;
	                                                            cursorsmooth=false;
	                                                            cursoropacity=1;
	                                                            maximumcharacters=-1;
	                                                            drawframe=true;
				                                                textcolor.setzen(1,1,1,1);
				                                                color.setzen(pr,pgr,pb,color.w());
				                                                colortransformed=color;
				                                                animtime=iggsystem()->clock->system();
																setfocus();
				                                                keyboarddown=false;
																feldaltinitialisiert=false;
																for(int i=0;i<1024;i++) feldalt[i]=0;

};
_iggeditbox::~_iggeditbox(){
};
void _iggeditbox::set(_zeichenkette<_tt>&t){
                                                				text=t;
};
_zeichenkette<_tt> _iggeditbox::get()const{
																return(text);
};
void _iggeditbox::setcursorimage(_bild<_tb>*t,_tg w,_tg h){
				                                                cursorimage=t;	
				                                                cursorbreite=w;
				                                                cursorhoehe=h;
};			
void _iggeditbox::zeichnen(_grafik*gra,_kamera<_tg>*cam){
				                                                if((visible)&&(superinvisible==false)){
				                                                 parent->clip(gra);
				                                                 _vektor3<_tg> p;
				                                                 _tg w=breite();
				                                                 _tg h=hoehe();			
				                                                 if(drawframe){
				                                                  zeichnenschatten(gra,cam);
				                                                  _bild<_tb>*bm=bestbreitematch();
				                                                  colorhilfe=colortransformed;
				                                                  colorhilfe.w(colorhilfe.w()*pfadeopacity);
                                                                  gra->transparenz(true);
                                                                  gra->transparenzmultiplikativ();
				                                                  if(bm){
				                                                   gra->rechteck(bm,positiontransformed.x(),positiontransformed.y(),w,h,colorhilfe);
				                                                  }else{
				                                                   zeichnenguirectangleinvers(gra,positiontransformed,w,h,colorhilfe);
				                                                  };
				                                                 };
				                                                gra->sichtbereich(positiontransformed.x(),positiontransformed.y(),w,h);
				                                                 p=positiontransformed;
				                                                 p.x(p.x()+25);
				                                                 p.y(p.y()+5);
				                                                 p.z(textshadowz);
				                                                
				                                                 colorhilfe=textcolor;
				                                                 colorhilfe.w(colorhilfe.w()*pfadeopacity);
				                                                 zeichnenguitext(gra,text,font,p,colorhilfe);
				                                                 p.z(positiontransformed.z());
				                                                 p=positiontransformed;
				                                                 p.x(p.x()+font->breite(text)+25);
				                                                 p.y(p.y()+font->hoehe(text)+cursoroffsety);
				                                                 colorhilfe=colortransformed;
																 colorhilfe.w(colorhilfe.w()*pfadeopacity);
				                                                 if((animp)&&(focus())){
                                                                  gra->transparenz(true);
                                                                  gra->transparenzmultiplikativ();
				                                                  if(cursorimage){
                                                                   colorhilfe=colortransformed;
                                                                   colorhilfe.w(colorhilfe.w()*cursoropacity*pfadeopacity);
				                                                   gra->rechteck(cursorimage,p.x(),p.y(),cursorbreite,cursorhoehe,colorhilfe);
				                                                  }else{
																   colorhilfe.w(colorhilfe.w()*cursoropacity*pfadeopacity);
				                                                   zeichnenguibox(gra,p,cursorbreite,cursorhoehe,colorhilfe);
				                                                  };
				                                                 };
				                                                 gra->sichtbereich(0,0,iggsystem()->breite(),iggsystem()->hoehe());
																 gra->orthonormal();
				                                                };
};
void _iggeditbox::animieren(_maus<_tg>*mau,_tastatur*tas){
				                                                if((active)&&(focus())){
																 /*if(feldaltinitialisiert==false){
																  tas->ladenfeld(feldalt);
																  feldaltinitialisiert=true;
																 };*/
				                                                 bool akt=false;
				                                                 
				                                                 //if(tas->taste()){
																  char*f=feldalt;
															//	  tas->ladenfeld(f);
																  if((tas->knopflinks()==false)&&(tas->knopfrechts()==false)){
				                                                  // if(keyboarddown==false){
				                                                  //  keyboarddown=true;

																	if(tas->backspace()){
																 	 if(f[VK_BACK]==0){
																	  if(text.groesse()>0) text.aushaengen(text.groesse()-1,1);
																	  f[VK_BACK]=1;
																	 };
																    }else{
																	 f[VK_BACK]=0;
																	 bool ok=false;
																	 if(maximumcharacters==-1) ok=true; else{
																	  if(int(text.groesse())<maximumcharacters) ok=true; 
																	 };
				                                                     if(ok){
																      //zeichenanhängen
																	  
																	  if(tas->taste(65)) {if(f[65]==0) {text+=L"a";f[65]=1;};} else f[65]=0;
				                                                      if(tas->taste(66)) {if(f[66]==0) {text+=L"b";f[66]=1;};} else f[66]=0;
																	  if(tas->taste(67)) {if(f[67]==0) {text+=L"c";f[67]=1;};} else f[67]=0;
				                                                      if(tas->taste(68)) {if(f[68]==0) {text+=L"d";f[68]=1;};} else f[68]=0;
				                                                      if(tas->taste(69)) {if(f[69]==0) {text+=L"e";f[69]=1;};} else f[69]=0;
				                                                      if(tas->taste(70)) {if(f[70]==0) {text+=L"f";f[70]=1;};} else f[70]=0;
				                                                      if(tas->taste(71)) {if(f[71]==0) {text+=L"g";f[71]=1;};} else f[71]=0;
				                                                      if(tas->taste(72)) {if(f[72]==0) {text+=L"h";f[72]=1;};} else f[72]=0;
				                                                      if(tas->taste(73)) {if(f[73]==0) {text+=L"i";f[73]=1;};} else f[73]=0;
				                                                      if(tas->taste(74)) {if(f[74]==0) {text+=L"j";f[74]=1;};} else f[74]=0;
				                                                      if(tas->taste(75)) {if(f[75]==0) {text+=L"k";f[75]=1;};} else f[75]=0;
				                                                      if(tas->taste(76)) {if(f[76]==0) {text+=L"l";f[76]=1;};} else f[76]=0;
				                                                      if(tas->taste(77)) {if(f[77]==0) {text+=L"m";f[77]=1;};} else f[77]=0;
				                                                      if(tas->taste(78)) {if(f[78]==0) {text+=L"n";f[78]=1;};} else f[78]=0;
				                                                      if(tas->taste(79)) {if(f[79]==0) {text+=L"o";f[79]=1;};} else f[79]=0;
				                                                      if(tas->taste(80)) {if(f[80]==0) {text+=L"p";f[80]=1;};} else f[80]=0;
				                                                      if(tas->taste(81)) {if(f[81]==0) {text+=L"q";f[81]=1;};} else f[81]=0;
				                                                      if(tas->taste(82)) {if(f[82]==0) {text+=L"r";f[82]=1;};} else f[82]=0;
				                                                      if(tas->taste(83)) {if(f[83]==0) {text+=L"s";f[83]=1;};} else f[83]=0;
				                                                      if(tas->taste(84)) {if(f[84]==0) {text+=L"t";f[84]=1;};} else f[84]=0;
				                                                      if(tas->taste(85)) {if(f[85]==0) {text+=L"u";f[85]=1;};} else f[85]=0;
				                                                      if(tas->taste(86)) {if(f[86]==0) {text+=L"v";f[86]=1;};} else f[86]=0;
				                                                      if(tas->taste(87)) {if(f[87]==0) {text+=L"w";f[87]=1;};} else f[87]=0;
				                                                      if(tas->taste(88)) {if(f[88]==0) {text+=L"x";f[88]=1;};} else f[88]=0;
				                                                      if(tas->taste(89)) {if(f[89]==0) {text+=L"y";f[89]=1;};} else f[89]=0;
				                                                      if(tas->taste(90)) {if(f[90]==0) {text+=L"z";f[90]=1;};} else f[90]=0;

																	  if((tas->taste(48))||(tas->taste(96))) {if(f[48]==0) {text+=L"0";f[48]=1;};} else f[48]=0;
																	  if((tas->taste(49))||(tas->taste(97))) {if(f[49]==0) {text+=L"1";f[49]=1;};} else f[49]=0;
																	  if((tas->taste(50))||(tas->taste(98))) {if(f[50]==0) {text+=L"2";f[50]=1;};} else f[50]=0;
																	  if((tas->taste(51))||(tas->taste(99))) {if(f[51]==0) {text+=L"3";f[51]=1;};} else f[51]=0;
																	  if((tas->taste(52))||(tas->taste(100))) {if(f[52]==0) {text+=L"4";f[52]=1;};} else f[52]=0;
																	  if((tas->taste(53))||(tas->taste(101))) {if(f[53]==0) {text+=L"5";f[53]=1;};} else f[53]=0;
																	  if((tas->taste(54))||(tas->taste(102))) {if(f[54]==0) {text+=L"6";f[54]=1;};} else f[54]=0;
																	  if((tas->taste(55))||(tas->taste(103))) {if(f[55]==0) {text+=L"7";f[55]=1;};} else f[55]=0;
																	  if((tas->taste(56))||(tas->taste(104))) {if(f[56]==0) {text+=L"8";f[56]=1;};} else f[56]=0;
																	  if((tas->taste(57))||(tas->taste(105))) {if(f[57]==0) {text+=L"9";f[57]=1;};} else f[57]=0;

																	  if(tas->taste(VK_OEM_MINUS)) {if(f[VK_OEM_MINUS]==0) {text+=L"-";f[VK_OEM_MINUS]=1;};} else f[VK_OEM_MINUS]=0;

																	  if(tas->leertaste()) {if(f[VK_SPACE]==0) {text+=L" ";f[VK_SPACE]=1;};} else f[VK_SPACE]=0;
																	  /*
																	  for(int i=0;i<256;i++){
																	   L->schreiben("TAS=",i);
																	   if(f[i]) L->schreiben("f[i]=true");
																	  };
																	  */
																	 
				                                                     };
																	  if(tas->taste(VK_DELETE)) {if(f[VK_DELETE]==0) {text=L"";f[VK_DELETE]=1;};} else f[VK_DELETE]=0;
																	  if(tas->taste(VK_INSERT)) {if(f[VK_INSERT]==0) {text+=iggsystem()->clipboardtext();f[VK_INSERT]=1;};} else f[VK_INSERT]=0;
				                                                     
																    };
				                                                   //};
																  };


																  /*bool anders=false;
																  for(int i=0;i<256;i++) {
																   if(feldalt[i]!=f[i]) anders=true;	 
																   feldalt[i]=f[i];
																  };
																  if(anders) keyboarddown=false;
																  */
				                                                 //};
				                                                 
				                                                 
				                                                 if(animc==0){
				                                                  animc=animw;
				                                                  animp=1-animp;
				                                                 }else{
				                                                  animc-=1;
				                                                 };
				                                                 if(cursorsmooth){
				                                                  animp=1;
				                                                  cursoropacity=_to(sin(_ph*iggsystem()->clock->system()*1))*_to(0.5f)+_to(0.5f);
				                                                 };
				                                                 animierenkind(mau,tas);
				                                                 animierenhilfe(mau);
																}else{
																 if((active)&&(visible)){
															      if((inner(mau))&&((tas->knopflinks())||(tas->knopfrechts()))){
																   setfocus();
																  };
																 };
																};
};
void _iggeditbox::setzenstatus(){
				                                                iggsystem()->editbox=this;
};				
//*******************************************************************************************************************************************************************************
//                                                              G U I I M A G E
//*******************************************************************************************************************************************************************************
_iggimage::_iggimage(_igg*pg,_tg px,_tg py,_tg pw,_tg ph,_bild<_tb>*img,_to pr,_to pgr,_to pb):_igg(pg,px,py,-1,pw,ph,0){
	                                                            image=img;
	                                                            blendmasked=true;
	                                                            crosslinktext=0;
	                                                            crosslinkcheckbox=0;
				                                                color.setzen(pr,pgr,pb,1);
				                                                colortransformed=color;
};
_iggimage::~_iggimage(){
};
void _iggimage::zeichnen(_grafik*gra,_kamera<_tg>*cam){
				                                                if((visible)&&(superinvisible==false)){
				                                                 parent->clip(gra);
				                                                 zeichnenschatten(gra,cam);
                                                                 gra->transparenz(true);
                                                                 gra->transparenzmultiplikativ();
				                                                 colorhilfe=color;
				                                                 colorhilfe.w(colorhilfe.w()*pfadeopacity);
				                                                 gra->rechteck(image,positiontransformed.x(),positiontransformed.y(),breite(),hoehe(),colorhilfe);			 
				                                                };
};
void _iggimage::animieren(_maus<_tg>*mau,_tastatur*tas){
				                                                _tg mx=mau->x();
				                                                _tg my=mau->y();
				                                                if(active){
				                                                 if(marked==2){
				                                                  if(tas->knopflinks()==false){
				                                                   if(inner(mau)){
				                                                    if(selectable) iggsystem()->image=this;
				                                                    marked=0;
				                                                   }else{
				                                                    marked=0;
				                                                   };
				                                                  }else{
				                                                   if(inner(mau)==false){
				                                                    marked=0;
				                                                   };
				                                                  };
				                                                 };
				                                                 if(marked==1){
				                                                  if(inner(mau)){
				                                                   if(tas->knopflinks()){
				                                                    marked=2;
				                                                   };
				                                                  }else{
				                                                   marked=0;
				                                                  };
				                                                 };				
				                                                 if(marked==0){
				                                                  if(inner(mau)){
  				                                                   marked=1;
				                                                  }; 
   			                                                     };
				                                                 animierenkind(mau,tas);
				                                                 animierenhilfe(mau);
				                                                };
};
void _iggimage::setzenstatus(){
				                                                iggsystem()->image=this;
};				
//*******************************************************************************************************************************************************************************
//                                                              G U I L I N E
//*******************************************************************************************************************************************************************************
_iggline::_iggline(_igg*pg,_tg px0,_tg py0,_tg px1,_tg py1,_to pr,_to pgr,_to pb):_igg(pg,px0,py0,-1,px1-px0,py1-py0,0){
				                                                color.setzen(pr,pgr,pb,1);
				                                                colortransformed=color;
				                                                selectable=false;
				                                                shadow=false;
};
_iggline::~_iggline(){
};
void _iggline::zeichnenschatten(_grafik*gra,_kamera<_tg>*cam){
				                                                if((visible)&&(superinvisible==false)){
				                                                 if(shadow){
				                                                  colorhilfe.setzen(0,0,0,shadowopacity*colortransformed.w()*pfadeopacity);
				                                                  _tg x0=positiontransformed.x()+shadowdirection.x();
				                                                  _tg y0=positiontransformed.y()+shadowdirection.y();
				                                                  zeichnenguifurche(gra,x0,y0,x0+breite(),y0+hoehe(),colorhilfe);
				                                                 };
				                                                };
};				
void _iggline::zeichnen(_grafik*gra,_kamera<_tg>*cam){
				                                                if((visible)&&(superinvisible==false)){
				                                                 parent->clip(gra);
				                                                 zeichnenschatten(gra,cam);
				                                                 colorhilfe=colortransformed;
				                                                 colorhilfe.w(color.w()*pfadeopacity);
				                                                 _tg x0=positiontransformed.x();
				                                                 _tg y0=positiontransformed.y();
				                                                 zeichnenguifurche(gra,x0,y0,x0+breite(),y0+hoehe(),colorhilfe);
				                                                };
};
void _iggline::animieren(_maus<_tg>*mau,_tastatur*tas){
				                                                if(active){
				                                                 colortransformed=color;
				                                                 animierenkind(mau,tas);
				                                                 animierenhilfe(mau);
				                                                };
};
void _iggline::setzenstatus(){
};				
//*******************************************************************************************************************************************************************************
//                                                              L I S T B O X
//*******************************************************************************************************************************************************************************
_igglistbox::_igglistbox(_igg*pg,_tg px,_tg py,_tg pw,_tg ph,_tg pbw,_to pr,_to pgr,_to pb):_igg(pg,px,py,-1,pw,ph,-1){
	                                                            scrollbarvertical=0;
	                                                            scrollbarverticalbreite=20;
	                                                            scrollstepwheel=5;
	                                                            scrollfriction=0.8;
	                                                            drawframe=true;
	                                                            frameimage=0;
	                                                            frameimagevertical=0;
	                                                            frameimagehorizontal=0;
	                                                            innershadow=true;
	                                                            backgroundopacity=_to(0.4f);
	                                                            doubleclicktime=500;
	                                                            pcontentbreite=0;
	                                                            pcontenthoehe=0;
	                                                            mousezvector=0;
	                                                            moverviewport=false;
	                                                            lasthoehe=1;
	                                                            lastclick=0;
	                                                            statuskeydown=false;
	                                                            statuskeyup=false;
	                                                            selection=0;
	                                                            selectionrect=false;
	                                                            selectionrectbild=0;
	                                                            selectionrectopacity=0;
	                                                            selectionrectx=0;
	                                                            selectionrecty=0;
	                                                            selectionrectw=0;
	                                                            selectionrecth=0;
	                                                            moverrect=false;
	                                                            moverrectbild=0;
	                                                            moverrecttimeold=0;
	                                                            moverrectopacity=0;
	                                                            moverrectx=0;
	                                                            moverrecty=0;
	                                                            moverrectw=0;
	                                                            moverrecth=0;
	                                                            moverrecttargetx=0;
	                                                            moverrecttargety=0;
	                                                            moverrecttargetw=0;
	                                                            moverrecttargeth=0;
				                                                setshadow(10,10,_to(0.3f));
				                                                mousezold=0;//mau->z();
				                                                moverrectcolor.setzen(_to(0.8f),_to(0.5f),_to(0.1f),_to(0.5f));
				                                                selectioncolor.setzen(1,1,_to(0.5f),0);
				                                                selectionrectcolor.setzen(_to(0.9f),_to(0.7f),_to(0.1f),_to(0.7f));	                                                            
                                                                borderbreite=pbw;
				                                                //if pw<50 pw=50;
				                                                //if ph<70 ph=70;
				                                                color.setzen(pr,pgr,pb,color.w());
				                                                colortransformed=color;
				                                                _vektor3<_tg> p=position.lesen();
				                                                scrollbarvertical=new _iggscrollbarvertical(pg,p.x()+breite()-borderbreite-scrollbarverticalbreite,p.y()+borderbreite,scrollbarverticalbreite,hoehe()-2*borderbreite,scrollbarverticalbreite,scrollbarverticalbreite,1,1,1,0,0);
				                                                scrollbarvertical->position.z(scrollbarvertical->position.z()-1.5);
				                                                clipkind=true;
};
_igglistbox::~_igglistbox(){
};
void _igglistbox::setpositiony(_tg y){				
				                                                position.y(y);
				                                                scrollbarvertical->position.y(y+borderbreite);
				                                                _tg bh=scrollbarvertical->borderhoehe;
				                                                _tg h=scrollbarvertical->hoehe();
				                                                _tg w=scrollbarvertical->breite();
				                                                scrollbarvertical->buttonup->position.y((bh/2)-scrollbarvertical->buttonup->hoehe()/2);
				                                                scrollbarvertical->buttondown->position.y((h-bh/2)-scrollbarvertical->buttonup->hoehe()/2);			
				
};
void _igglistbox::setsizey(_tg y){				
				                                                size.y(y);
				                                                scrollbarvertical->size.y(y-2*borderbreite);
				                                                _tg bh=scrollbarvertical->borderhoehe;
				                                                _tg h=scrollbarvertical->hoehe();
				                                                _tg w=scrollbarvertical->breite();
				                                                scrollbarvertical->buttonup->position.y((bh/2)-scrollbarvertical->buttonup->hoehe()/2);
				                                                scrollbarvertical->buttondown->position.y((h-bh/2)-scrollbarvertical->buttonup->hoehe()/2);				
};
void _igglistbox::dynamisch(_tg wx,_tg wy){
				                                                _igg::dynamisch(wx,wy);
				                                                updatescrollbar();
};
void _igglistbox::updatescrollbar(){		
				                                                _tg y=size.y();
				                                                scrollbarvertical->size.y(y-2*borderbreite);
				                                                _tg bh=scrollbarvertical->borderhoehe;
				                                                _tg h=scrollbarvertical->hoehe();
				                                                _tg w=scrollbarvertical->breite();
				                                                _tg xl=position.x();
				                                                _tg wl=breite();
				                                                y=position.y();
				                                                scrollbarvertical->position.y(y+borderbreite);
				                                                scrollbarvertical->position.x(xl+wl-borderbreite-w);
				                                                scrollbarvertical->buttonup->position.y((bh/2)-scrollbarvertical->buttonup->hoehe()/2);
				                                                scrollbarvertical->buttondown->position.y((h-bh/2)-scrollbarvertical->buttonup->hoehe()/2);
};
_tg _igglistbox::contentbreite(){
				                                                _tg xmax=kindbreite();
				                                                //lasthoehe=ymax;
				                                                //scrollbarvertical->controllength=lasthoehe-(hoehe()-2*borderbreite);
				                                                pcontentbreite=xmax;
				                                                return(xmax);
				                                                /*
				                                                if(_listebasis<_igg>::anzahl()==0) return(0);
				                                                _tg xmin=+100000;
				                                                _tg xmax=-100000;
				                                                _tg xin,xax;
				                                                _igg*git;
				                                                if(anfang(git))do{
				                                                 _vektor3<_tg> p=git->position.lesen();
				                                                 xin=p.x();
				                                                 xax=p.x()+git->breite();
				                                                 if(xin<xmin) xmin=xin;
				                                                 if(xax>xmax) xmax=xax;
				                                                }while(naechstes(git));
				                                                return(xmax);
				                                                */
};

_tg _igglistbox::contenthoehe(){
				                                                _tg ymax=kindhoehe();
				                                                lasthoehe=ymax;
				                                                scrollbarvertical->controllength=lasthoehe-(hoehe()-2*borderbreite);
				                                                pcontenthoehe=ymax;
				                                                return(ymax);
};
bool _igglistbox::contentbreitetoolarge(){
				                                                _tg g=contentbreite();
				                                                if(g>(breite()-2*borderbreite)){
				                                                 return(true);
				                                                }else{
				                                                 return(false);
				                                                };
};
bool _igglistbox::contenthoehetoolarge(){
				                                                _tg g=pcontenthoehe;
				                                                if(g>(hoehe()-2*borderbreite) ){
				                                                 return(true);
				                                                }else{
				                                                 return(false);
				                                                };
};
void _igglistbox::zeichnen(_grafik*gra,_kamera<_tg>*cam){
				                                                if((visible)&&(superinvisible==false)){
				                                                 parent->clip(gra);
				                                                 // zeichnen shadow
                                                                 gra->transparenz(true);
                                                                 gra->transparenzmultiplikativ();
				                                                 
				                                                 if(shadow){
				                                                  _bild<_tb>*bm=frameimage;
				                                                  _bild<_tb>*sm=bestshadowmatch();
				                                                  colorhilfe.setzen(0,0,0,shadowopacity*colortransformed.w()*pfadeopacity);
				                                                  if((bm)&&(sm==0)){//bildschatten (standard)
				                                                   gra->rechteck(bm,positiontransformed.x()+shadowdirection.x(),positiontransformed.y()+shadowdirection.y(),breite(),hoehe(),colorhilfe);
				                                                  }else if((sm==0)&&(bm==0)){//provisorischer schatten
				                                                   gra->rechteck(positiontransformed.x()+shadowdirection.x(),positiontransformed.y()+shadowdirection.y(),breite(),hoehe(),colorhilfe);
				                                                  }else if(sm){//eigener schatten
				                                                   _tg be=shadowimageboardening;
				                                                   gra->rechteck(sm,(positiontransformed.x()+shadowdirection.x())-be,(positiontransformed.y()+shadowdirection.y())-be,breite()+be*2,hoehe()+be*2,colorhilfe);
				                                                  };
				                                                 };
				                                                 _vektor3<_tg> p;
				                                                 _tg w=breite();
				                                                 _tg h=hoehe();
				                                                 _tg lw=borderbreite;
				                                                 _tg sw=scrollbarverticalbreite;
				                                                 _bild<_tb>*bm=bestbreitematch();
				                                                 _tg ch=pcontenthoehe;
				                                                 _tg fy=ch-(h-2*lw-5);//5 noch so einfach
				                                                 if(bm){
				                                                  _tg iw=bm->groesse(0);
				                                                  _tg ih=bm->groesse(1);
				                                                  _tg iy=fy*scrollbarvertical->value;
				                                                  while(iy>ih){
				                                                   iy-=ih;
				                                                  };
				                                                  colorhilfe=colortransformed;
				                                                  colorhilfe.w(colortransformed.w()*backgroundopacity*pfadeopacity);
				                                                  gra->sichtbereich(positiontransformed.x()+lw/2,positiontransformed.y()+lw/2,w-lw,h-lw);
				                                                  for(_tg ux=0;ux<=1.5;ux+=1){ 
				                                                   for(_tg uy=0;uy<=1.5;uy+=1){
				                                                    gra->rechteck(bm,(ux*iw)+positiontransformed.x()+lw/2,(uy*ih)+positiontransformed.y()+lw/2-iy,bm->groesse(0),bm->groesse(1),colorhilfe);
				                                                   };
				                                                  };
				                                                  gra->sichtbereich(0,0,iggsystem()->breite(),iggsystem()->hoehe());
				                                                 };
                                                				 if(drawframe){
                                                				  colorhilfe=colortransformed;
                                                				  colorhilfe.w(colorhilfe.w()*pfadeopacity);
				                                                  if(frameimage){
				                                                   gra->rechteck(frameimage,positiontransformed.x(),positiontransformed.y(),w,h,colorhilfe);
				                                                  }else if(frameimagehorizontal){
				                                                   gra->rechteck(frameimagehorizontal,positiontransformed.x(),positiontransformed.y(),w,lw,colorhilfe);
				                                                   gra->rechteck(frameimagehorizontal,positiontransformed.x(),positiontransformed.y()+h-lw,w,lw,colorhilfe);
				                                                  }else{ 
				                                                   zeichnenschatten(gra,cam);
				                                                   colorhilfe=colortransformed;
				                                                   colorhilfe.w(colorhilfe.w()*pfadeopacity);
				                                                   p=positiontransformed;
				                                                   zeichnenguibox(gra,p,w,lw,colorhilfe);
				                                                   p=positiontransformed;
				                                                   p.y(p.y()+(h-lw));
				                                                   zeichnenguibox(gra,p,w,lw,colorhilfe);
				                                                   p=positiontransformed;
				                                                   p.y(p.y()+lw);
				                                                   zeichnenguibox(gra,p,lw,h-2*lw,colorhilfe);
				                                                   p=positiontransformed;
				                                                   p.x(p.x()+(w-lw));
				                                                   p.y(p.y()+lw);
				                                                   zeichnenguibox(gra,p,lw,h-2*lw,colorhilfe);
				                                                  };
				                                                 };
				                                                 if((moverrect)&&(moverrectopacity>0)){
				                                                  clip(gra);
				                                                  colorhilfe=moverrectcolor;		  
				                                                  colorhilfe.w(moverrectopacity*colortransformed.w()*moverrectcolor.w()*pfadeopacity);
				                                                  p.setzen(moverrectx,moverrecty,0);
				                                                  
				                                                  if(moverrectbild){
				                                                   gra->rechteck(moverrectbild,p.x(),p.y(),moverrectw,moverrecth,colorhilfe);
				                                                  }else{
				                                                   gra->textur(false);
				                                                   zeichnenguiboxinvers(gra,p,moverrectw,moverrecth,colorhilfe);
																   gra->textur(true);
				                                                  };
				                                                  
				                                                  gra->sichtbereich(0,0,iggsystem()->breite(),iggsystem()->hoehe());
				                                                 };

				                                                 if((selectionrect)&&(selectionrectopacity>0)){
				                                                  clip(gra);
				                                                  colorhilfe=selectionrectcolor;		  
				                                                  colorhilfe.w(selectionrectopacity*colortransformed.w()*selectionrectcolor.w()*pfadeopacity);
				                                                  p.setzen(selectionrectx,selectionrecty,0);
				                                                  if(selectionrectbild){
				                                                   gra->rechteck(selectionrectbild,p.x(),p.y(),selectionrectw,selectionrecth,colorhilfe);
				                                                  }else{
				                                                   gra->textur(false);
				                                                   zeichnenguiboxinvers(gra,p,selectionrectw,selectionrecth,colorhilfe);
																   gra->textur(true);		
				                                                  };
				                                                  
				                                                  gra->sichtbereich(0,0,iggsystem()->breite(),iggsystem()->hoehe());
				                                                 };
				                                                };
};
void _igglistbox::cliprecursive(_iggclip*cr){
				                                                if((clipkind)||(clipkindhierarchical)){
				                                                 _tg w=breite();
				                                                 _tg h=hoehe();
				                                                 _tg lw=borderbreite;
				                                                 _tg sw=scrollbarverticalbreite;
				                                                 _tg x0,y0,x1,y1;
				                                                 if(contenthoehetoolarge()){
				                                                  x0=positiontransformed.x()+lw;
				                                                  y0=positiontransformed.y()+lw+1;
				                                                  x1=x0+(w-(2*lw+sw)-1);
				                                                  y1=y0+(h-2*lw-1);
				                                                 }else{
				                                                  x0=positiontransformed.x()+lw;
				                                                  y0=positiontransformed.y()+lw+1;
				                                                  x1=x0+(w-(2*lw)-1);
				                                                  y1=y0+(h-2*lw-1);
				                                                 };
				                                                 if(x0>cr->x0) cr->x0=x0;
				                                                 if(y0>cr->y0) cr->y0=y0;
				                                                 if(x1<cr->x1) cr->x1=x1;
				                                                 if(y1<cr->y1) cr->y1=y1;
				                                                };
				                                                if(parent) parent->cliprecursive(cr);
};
bool _igglistbox::clip(_grafik*gra){
				                                                if((clipkind)&&(clipkindhierarchical==false)){//-------------------------------------------------
				                                                 _tg w=breite();
				                                                 _tg h=hoehe();
				                                                 _tg lw=borderbreite;
				                                                 _tg sw=scrollbarverticalbreite;
				                                                 if(contenthoehetoolarge()){
				                                                  gra->sichtbereich(positiontransformed.x()+lw,positiontransformed.y()+lw+1,w-(2*lw+sw)-1,h-2*lw-1);
				                                                 }else{
				                                                  gra->sichtbereich(positiontransformed.x()+lw,positiontransformed.y()+lw+1,w-(2*lw)-1,h-2*lw-1);
				                                                 };
				                                                }else if(clipkindhierarchical){//---------------------------------------------------------------
				                                                 _tg w=breite();
				                                                 _tg h=hoehe();
				                                                 _tg lw=borderbreite;
				                                                 _tg sw=scrollbarverticalbreite;
				                                                 _bild<_tb>*bm=bestbreitematch();		
				                                                 if(contenthoehetoolarge()){
				                                                  cliprect.x0=positiontransformed.x()+lw;
				                                                  cliprect.y0=positiontransformed.y()+lw+1;
				                                                  cliprect.x1=cliprect.x0+(w-(2*lw+sw)-1);
				                                                  cliprect.y1=cliprect.y0+(h-2*lw-1);
				                                                 }else{
				                                                  cliprect.x0=positiontransformed.x()+lw;
				                                                  cliprect.y0=positiontransformed.y()+lw+1;
				                                                  cliprect.x1=cliprect.x0+(w-(2*lw)-1);
				                                                  cliprect.y1=cliprect.y0+(h-2*lw-1);
				                                                 };
				                                                 if(parent) parent->cliprecursive(&cliprect);
				                                                 bool valid=true;
				                                                 if(cliprect.x1<cliprect.x0){
				                                                  cliprect.x1=cliprect.x0;
				                                                  valid=false;
				                                                 };
				                                                 if(cliprect.y1<cliprect.y0){
				                                                  cliprect.y1=cliprect.y1;
				                                                  valid=false;
				                                                 };
				                                                 if(valid){
				                                                  gra->sichtbereich(cliprect.x0,cliprect.y0,cliprect.x1-cliprect.x0,cliprect.y1-cliprect.y0);
				                                                  return(true);
				                                                 }else{
				                                                  return(false);
				                                                 };
				                                                }else{//-----------------------------------------------------------------------------------------
				                                                 _iggsystem*g=iggsystem();
				                                                 if(g) gra->sichtbereich(0,0,g->breite(),g->hoehe());
				                                                 return(true);
				                                                };		
				                                                return(true);	
};
/*
void _igglistbox::deinsert(){
				                                                _listebasis<_igg>::aushaengen();
				                                                selection=0;
};
*/
void _igglistbox::selectbytext(const _zeichenkette<_tt>&t){//searches for a _iggtext object, if its first textline is t , then select this gui object
				                                                _igg*tit;
				                                                _iggtext*gt;
				                                               // int i=0;
				                                                if(anfang(tit))do{
				                                                 gt=dynamic_cast<_iggtext*>(tit);
				                                                 if(gt){
				                                                  //_listenknoten<_iggtextline>*link;
				                                                 // if(gt->lines.anfang(link)){
				                                                  // _iggtextline*gtl=link->objekt();
				                                                   if(gt->lesen()==t) selection=tit;
				                                                 // }; 
				                                                 };
 			                                                     //i++;
				                                                }while(naechstes(tit));
};
_zeichenkette<_tt> _igglistbox::selectiontext(){// return the string of selected gui object, if this is an _iggtext object
				                                                if(selection){
				                                                 _iggtext*gt=dynamic_cast<_iggtext*>(selection);
				                                                 if(gt){
				                                                 // _listenknoten<_iggtextline>*link;
				                                                  //if(gt->lines.anfang(link)){
				                                                   //_iggtextline*gtl=link->objekt();
				                                                   return(gt->lesen());
				                                                  //};
				                                                 };
				                                                };
				                                                return(L"");
};
void _igglistbox::scrolltoselection(){
				                                                if(selection){
				                                                 _tg y=selection->position.y()+selection->hoehe()/2;
				                                                 scrollbarvertical->value=y/contenthoehe();
				                                                };
};
bool _igglistbox::mouseoverviewport(_maus<_tg>*mau){
				                                                _tg lw=borderbreite;
				                                                _tg w=breite();
				                                                _tg h=hoehe();
				                                                _tg x=positiontransformed.x();
				                                                _tg y=positiontransformed.y();
				                                                int mx=int(mau->x());
				                                                int my=int(mau->y());
				                                                if((mx>=(x+lw))&&(mx<=((x+w)-(lw)))&&(my>=(y+lw))&&(my<=(y+h-lw))) return(true); else return(false);
};
void _igglistbox::animierenkind(_maus<_tg>*mau,_tastatur*tas){
				                                                if((visible)&&(superinvisible==false)){
				                                                 bool mov=mouseoverviewport(mau);
				                                                 _igg*tit;
				                                                 _tg xit=positiontransformed.x()+1*borderbreite;
				                                                 _tg yit=positiontransformed.y()+1*borderbreite;
				                                                 _tg ch=pcontenthoehe;
				                                                 _tg h=hoehe();
				                                                 _tg fy=ch-(h-2*borderbreite-5);//5 noch so einfach
				                                                
				                                                 if(anfang(tit))do{
				                                                  tit->positiontransformed=tit->position.lesen();
				                                                  tit->positiontransformed.x(tit->positiontransformed.x()+xit);
				                                                  tit->positiontransformed.y(tit->positiontransformed.y()+yit-scrollbarvertical->value*fy);
		                                                          tit->positiontransformed.z(positiontransformed.z()-1.5);
																  if(tit->transformation.x()!=0){
																   tit->positiontransformed.x(tit->positiontransformed.x()+tit->size.x()*tit->transformation.x());
																  };

				                                                  if( ((tit->positiontransformed.y()+tit->hoehe())<positiontransformed.y()) || (tit->positiontransformed.y()>(positiontransformed.y()+h)) ){
				                                                   tit->visibility(false);
				                                                  }else{
				                                                   tit->visible=true;
				                                                  };
				                                                  if(tit->visible){
				                                                   if(tit==selection){
				                                                    tit->colortransformed=tit->color;
				                                                    tit->colortransformed.add(selectioncolor);
				                                                    tit->colortransformed.begrenzen(0,1);
				                                                   }else{
				                                                    tit->colortransformed=tit->color;
				                                                   };
				                                                   tit->colortransformed.w(colortransformed.w()*tit->color.w());	
				                                                  }else{
				                                                   tit->animierenhilfefadeout(mau);
				                                                  };
				                                                  _iggshiftout*tits=dynamic_cast<_iggshiftout*>(tit);
				                                                  if(tits){
				                                                   tits->window->visible=true;
				                                                   tits->animieren(mau,tas);
				                                                   tits->window->visible=false;
				                                                   if(tits->visible){
				                                                    tits->button->visible=true;
				                                                    if(tits->window->superinactive==false){
				                                                     _igg*xitn;
				                                                     if(tits->window->anfang(xitn))do{
				                                                      _iggtext*xit=dynamic_cast<_iggtext*>(xitn);
				                                                      if(xit){
				                                                       if( ((xit->positiontransformed.y()+xit->hoehe())<positiontransformed.y()) || (xit->positiontransformed.y()>(positiontransformed.y()+h)) ){ 
				 	                                                    xit->visible=false;
				                                                        xit->superinvisible=true;
		   			                                                   }else{
  				                                                        xit->visible=true;
					                                                    xit->superinvisible=false;
				                                                        if(xit==selection){
   				                                                         xit->colortransformed=xit->color;
  				                                                         xit->colortransformed.add(selectioncolor);
				                                                         xit->colortransformed.begrenzen(0,1);
				                                                        }else{
				                                                         xit->colortransformed=xit->color;
				                                                        };
				                                                        xit->colortransformed.w(colortransformed.w()*xit->color.w());
				                                                       };				  
				                                                      };
				                                                     }while(tits->window->naechstes(xitn));
				                                                    }else{
				                                                     tits->window->visibility(false);
				                                                    };   
				                                                   };
				                                                  };
				                                                  if(tits==0) if((tit->visible)&&(mov)) tit->animieren(mau,tas);
				                                                  if(mov==false){
				                                                   tit->animierenhilfefadeout(mau);
				                                                   _iggbutton*gb=dynamic_cast<_iggbutton*>(tit);
				                                                   if(gb) gb->animierenscale();
				                                                  };
				                                                 }while(naechstes(tit));
				                                                };
};
void _igglistbox::animieren(_maus<_tg>*mau,_tastatur*tas){
				                                                _iggsystem*gs=iggsystem();
				                                                int mx=gs->mouseposx;
				                                                int my=gs->mouseposy;
				                                                int mz=gs->mouseposz;
				                                                bool ml=gs->mousebutton[1];
				                                                bool mr=gs->mousebutton[2];
				                                                bool mm=gs->mousebutton[3];
				                                                _tg lw=borderbreite;
				                                                _tg sw=scrollbarverticalbreite;
				                                                bool gedr=false;
				                                                _tg w=breite();
				                                                _tg h=hoehe();
				                                                _tg x=positiontransformed.x();
				                                                _tg y=positiontransformed.y();
				                                                bool cttl=false;
																//L->l("listbox animieren val=",scrollbarvertical->value);

				                                                colortransformed=color;
				                                                if((active)&&(visible)&&(superinvisible==false)){
				                                                 contenthoehe();
				                                                 animierenhilfe(mau);
				                                                 gs->pushstates();
				                                                 animierenkind(mau,tas);
				                                                 if(gs->comparestates()==false){//es hat sich was geändert
				                                                  gedr=true;
				                                                 };	
				                                                };
															//	L->l("listbox animieren vale0=",scrollbarvertical->value);

				                                                if((active)&&(visible)){
			                                                     if(contenthoehetoolarge()){//(list.count()*29)>(h-2*lw)
				                                                  cttl=true;
				                                                  if(active) scrollbarvertical->activity(true);
				                                                  if(visible) scrollbarvertical->visibility(true);
				                                                 }else{
  				                                                  scrollbarvertical->value=0;
				                                                  scrollbarvertical->visibility(false);
				                                                  scrollbarvertical->activity(false);
				                                                 };
				                                                };
																//L->l("listbox animieren vale1=",scrollbarvertical->value);

				                                                if((active)&&(superinactive==false)){
				                                                 if( (mx>=x+lw) && (mx<=(x+w)-(lw)) && (my>=y+lw) && (my<=y+h-lw) ){//viewport
				                                                  if(moverviewport==false){
				                                                   mousezold=mz;
				                                                   moverviewport=true;
				                                                  };
																 // L->l("listbox animieren mousezold 111=",mousezold);
																  //L->l("listbox animieren mz 12=",mz);
				                                                  _tg dz=mz-mousezold;
				                                                  mousezold=mz;
				                                                  if(lasthoehe>0) mousezvector+=dz*(scrollstepwheel/lasthoehe); 
																  //L->l("listbox animieren last hoehe 12=",lasthoehe);
																 // L->l("listbox animieren dz 13=",dz);
				                                                  if(cttl) scrollbarvertical->value-=mousezvector;
				                                                  if(scrollbarvertical->value>1) scrollbarvertical->value=1;
				                                                  if(scrollbarvertical->value<0) scrollbarvertical->value=0;
				                                                 }else{
				                                                  moverviewport=false;
				                                                 };
																//L->l("listbox animieren vale2=",scrollbarvertical->value);

				                                                 if(cttl) scrollbarvertical->value-=mousezvector;
																//L->l("listbox animieren vale22=",mousezvector);

				                                                 if(scrollbarvertical->value>1) scrollbarvertical->value=1;
				                                                 if(scrollbarvertical->value<0) scrollbarvertical->value=0;
																//L->l("listbox animieren vale3=",scrollbarvertical->value);

				                                                 mousezvector*=scrollfriction;
				                                                 if(marked==2){
				                                                  if(ml==false){
				                                                   if(inner(mau)){
				                                                    gedr=true;
				                                                    marked=0;
				                                                   }else{
				                                                    marked=0;
				                                                   };
				                                                  }else{
				                                                   if(inner(mau)==false){
				                                                    marked=0;
				                                                   };
				                                                  };
				                                                 };
				                                                 if(marked==1){
				                                                  if(inner(mau)){
				                                                   if(ml){
				                                                    marked=2;
				                                                   };
				                                                  }else{
				                                                   marked=0;
				                                                  };
				                                                 };				
				                                                 if(marked==0){
				                                                  if(inner(mau)){
  				                                                   marked=1;
				                                                  }; 
   			                                                     };			
				                                                };
				                                                if(marked==0) shadowdirection.setzen(10,10,0);
				                                                if(marked==1) shadowdirection.setzen(9,9,0);
				                                                if(marked==2) shadowdirection.setzen(8,8,0);
				                                                if((active)&&(superinactive==false)){
				                                                 int moverrecttimenew=iggsystem()->clock->system();
				                                                 _tg ds=_tg(moverrecttimenew-moverrecttimeold)*0.001;
				                                                 moverrecttimeold=moverrecttimenew;	
				                                                 _tg ww=0.3;
				                                                 _tg qq=1-ww;		  
				                                                 if(moverrect){
				                                                  bool tinnen=false;
				                                                  _igg*tit;
				                                                  if(anfang(tit))do{
				                                                  //For Local tit:_igg=EachIn kindlist
				                                                   if((tit->selectable)&&(tit->visible)){
				                                                    _tg mob=0;
				                                                    if( (mx>(tit->positiontransformed.x()-mob)) && (mx<(tit->positiontransformed.x()+tit->breite()+mob)) && (my>(tit->positiontransformed.y()-mob)) && (my<(tit->positiontransformed.y()+tit->hoehe()+mob)) ){
				                                                     moverrecttargetx=tit->positiontransformed.x()-mob;
				                                                     moverrecttargety=tit->positiontransformed.y()-mob;
				                                                     moverrecttargetw=tit->breite()+2*mob;
				                                                     moverrecttargeth=tit->hoehe()+2*mob;
				                                                     tinnen=true;
				                                                    };	
				                                                   };
				                                                   _iggshiftout*tits=dynamic_cast<_iggshiftout*>(tit);
				                                                   if(tits){
				                                                    if(tits->window->superinactive==false){
				                                                     _igg*xitn;
				                                                     if(tits->window->anfang(xitn))do{
				                                                      _iggtext*xit=dynamic_cast<_iggtext*>(xitn);//For Local xit:_iggtext=EachIn tits.window.kindlist
				                                                      if(xit){
				                                                       if((xit->visible)&&(xit->selectable)){
					                                                    _tg mob=0;
					                                                    if( (mx>(xit->positiontransformed.x()-mob)) && (mx<(xit->positiontransformed.x()+xit->breite()+mob)) && (my>(xit->positiontransformed.y()-mob)) && (my<(xit->positiontransformed.y()+xit->hoehe()+mob)) ){
					                                                     moverrecttargetx=xit->positiontransformed.x()-mob;
				    	                                                 moverrecttargety=xit->positiontransformed.y()-mob;
					                                                     moverrecttargetw=xit->breite()+2*mob;
					                                                     moverrecttargeth=xit->hoehe()+2*mob;
					                                                     tinnen=true;
					                                                    };	
				                                                       };
				                                                      };
				                                                     }while(tits->window->naechstes(xitn));
				                                                    };
				                                                   };
				                                                  //Next
                                                				  }while(naechstes(tit));
				                                                  moverrectx=moverrectx*qq+moverrecttargetx*ww;
				                                                  moverrecty=moverrecty*qq+moverrecttargety*ww;
				                                                  moverrectw=moverrectw*qq+moverrecttargetw*ww;
				                                                  moverrecth=moverrecth*qq+moverrecttargeth*ww;
				                                                  if(tinnen){
				                                                   moverrectopacity+=_to(1*ds);
				                                                   if(moverrectopacity>1) moverrectopacity=1;
				                                                  }else{
				                                                   moverrectopacity-=_to(1*ds);
				                                                   if(moverrectopacity<0) moverrectopacity=0;
				                                                  };	
				                                                 };
				                                                 if(selectionrect){
				                                                  ww=0.4;
				                                                  qq=1-ww;
				                                                  if(selection){
				                                                   if(selection->visible){
				                                                    selectionrectx=selectionrectx*qq+selection->positiontransformed.x()*ww;
				                                                    selectionrecty=selectionrecty*qq+selection->positiontransformed.y()*ww;
				                                                    selectionrectw=selectionrectw*qq+selection->breite()*ww;
				                                                    selectionrecth=selectionrecth*qq+selection->hoehe()*ww;  
				                                                    selectionrectopacity+=_to(1*ds);
				                                                    if(selectionrectopacity>1) selectionrectopacity=1;
				                                                   }else{
				                                                    selectionrectopacity-=_to(1*ds);
				                                                    if(selectionrectopacity<0) selectionrectopacity=0;
				                                                   };
				                                                  }else{
				                                                   selectionrectopacity-=_to(1*ds);
				                                                   if(selectionrectopacity<0) selectionrectopacity=0;
				                                                  };
				                                                 };
				                                                 if(gedr){
				                                                  if( (mx>=x+lw) && (mx<=(x+w)-(lw+sw)) && (my>=y+lw) && (my<=y+h-lw) ){//viewport
				                                                   _igg*tit;
				                                                   if(anfang(tit))do{//For tit=EachIn kindlist
				                                                    if(tit->selectable){
				                                                     if( (mx>tit->positiontransformed.x()) && (mx<(tit->positiontransformed.x()+tit->breite())) && (my>tit->positiontransformed.y()) && (my<(tit->positiontransformed.y()+tit->hoehe())) ){
				                                                      if(selection!=tit){
			 		                                                   selection=tit;
			                                                           tit->setzenstatus();
			  		                                                   //playsoundstretched(gs->dip[3],0.5,1,1);!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		  			                                                   lastclick=gs->clock->system();
				                                                      }else{
				                                                       int thisclick=gs->clock->system();
				  	                                                   if ((thisclick-lastclick)<doubleclicktime){
				  		                                                gs->doubleclickleft=true;
					                                                   };		
					                                                   lastclick=thisclick;
		  			                                                  };
				                                                     };	
				                                                    };
				                                                    _iggshiftout*tits=dynamic_cast<_iggshiftout*>(tit);
				                                                    if(tits){
				                                                     if(tits->window->superinactive==false){
				                                                      //For Local xit:_iggtext=EachIn tits.window.kindlist
				                                                      _igg*xitn;
				                                                      if(tits->window->anfang(xitn))do{
				                                                       _iggtext*xit=dynamic_cast<_iggtext*>(xitn);
				                                                       if(xit){
				                                                        if((xit->visible)&&(xit->selectable)){
				                                                         if((mx>xit->positiontransformed.x()) && (mx<(xit->positiontransformed.x()+xit->breite())) && (my>xit->positiontransformed.y()) && (my<(xit->positiontransformed.y()+xit->hoehe())) ){
				                                                          if(selection!=xit){
			 		                                                       selection=xit;
			                                                               xit->setzenstatus();
		 			                                                      // playsoundstretched(gs->dip[3],0.5,1,1); !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		  			                                                       lastclick=gs->clock->system();
				                                                          }else{
				                                                           int thisclick=gs->clock->system();
				  	                                                       if((thisclick-lastclick)<doubleclicktime){
				  		                                                    gs->doubleclickleft=true;
					                                                       };		
					                                                       lastclick=thisclick;
		  			                                                      };
				                                                         };	
				                                                        };
				                                                       };
				                                                      }while(tits->window->naechstes(xitn));
				  	                                                 };
				                                                    };
				                                                   }while(naechstes(tit));
				                                                  };
				                                                 };
				                                                 if(gedr) gs->listbox=this;
				                                                 if((gs->focus==this)&&(selection)){
				                                                  if((tas->pfeilrunter())&&(statuskeydown==false)){
				                                                   statuskeydown=true;
				                                                   _igg*erstes;
				                                                   _igg*naechstes;
				                                                   selection->liste()->anfang(erstes);
				                                                   naechstes=selection->_listenknotenbasis<_igg>::naechstes();
				                                                   if(naechstes!=erstes) selection=naechstes;
				                                                   scrolltoselection();
				                                                   gs->listbox=this;
				                                                  };
				                                                  if(tas->pfeilrunter()==false) statuskeydown=false;
                                                				  if((tas->pfeilhoch())&&(statuskeyup==false)){
				                                                   statuskeyup=true;
				                                                   _igg*erstes;
				                                                   selection->liste()->anfang(erstes);
				                                                   if(selection!=erstes) selection=selection->_listenknotenbasis<_igg>::vorheriges();
				                                                   scrolltoselection();
				                                                   gs->listbox=this;
				                                                  };
				                                                  if(tas->pfeilhoch()==false) statuskeyup=false;
				                                                 };
																//L->l("listbox animieren vale=",scrollbarvertical->value);

				                                                };
																
};
void _igglistbox::checkboxes(bool c){
                                                                _igg*git;
                                                                _iggcheckbox*cit;
                                                                if(anfang(git))do{
                                                                 cit=dynamic_cast<_iggcheckbox*>(git);
                                                                 if(cit){
                                                                  cit->checked=c;
                                                                 };
                                                                }while(naechstes(git));
};			
bool _igglistbox::enthaeltcheckbox(_iggcheckbox*c)const{
                                                                _igg*iit;
                                                                _iggcheckbox*cit;
                                                                if(anfang(iit))do{
                                                                 cit=dynamic_cast<_iggcheckbox*>(iit);
                                                                 if(cit){
                                                                  if(cit==c) return(true);
                                                                 };
                                                                }while(naechstes(iit));
                                                                return(false);
};
	
void _igglistbox::setzenstatus(){
                                                				iggsystem()->listbox=this;
};				
//*******************************************************************************************************************************************************************************
//                                                              G U I M E S H
//*******************************************************************************************************************************************************************************
_iggmesh::_iggmesh(_igg*pg,_tg px,_tg py,_tg pw,_tg ph,_netz*m,_to pr,_to pgr,_to pb, int pp):_igg(pg,px,py,-3,pw,ph,pp){
	                                                            mesh=m;
	                                                            crosslinkcheckbox=0;
	                                                            crosslinkname=L"";
                                                				mesh->farbeverbinder(color);
	                                                            meshtransformed=mesh->duplizieren();
				                                                color.setzen(pr,pgr,pb,1);
				                                                colortransformed=color;
};
_iggmesh::~_iggmesh(){
};
void _iggmesh::zeichnen(_grafik*gra,_kamera<_tg>*cam){
				                                                if((visible)&&(superinvisible==false)){
				                                                 parent->clip(gra);
				                                                 //gra->orthonormal();
				                                                 updatemesh();
				                                                 colorhilfe=colortransformed;
				                                                 colorhilfe.w(colorhilfe.w()*pfadeopacity);
				                                                 colorhilfe.begrenzen(0,1);
																 gra->textur(true);
																 gra->transparenz(true);
																 gra->transparenzmultiplikativ();
				                                                 meshtransformed->farbeverbinder(colorhilfe); 
				                                                 meshtransformed->zeichnen(gra);
				                                                 //gra->orthonormal(); 
																 gra->transparenz(false);
																 gra->textur(true);
				                                                };
};
void _iggmesh::updatemesh(){
				                                                _vektor3<_tg> h;
				                                                _vektor3<_tg> d;
				                                                d=positiontransformed;
				                                                d.z(0);
				                                                mesh->markierungvertex(1);
				                                                _polygon*pits;
				                                                _polygon*pitd;
				                                                _vertex*vits;
				                                                _vertex*vitd;
				                                                meshtransformed->anfang(pitd);
                                                                if(mesh->anfang(pits))do{
                                                                 vits=pits->vertex();
                                                                 vitd=pitd->vertex();
                                                                 if(vits)do{
                                                                  if(vits->markierung()==1){
                                                                   vits->markierung(0);
                                                                   vitd->ort(vits->ort()+d);
                                                                  };
                                                                  vits=vits->naechstes(pits);
                                                                  vitd=vitd->naechstes(pitd);
                                                                 }while(vits!=pits->vertex());
                                                                 meshtransformed->naechstes(pitd);
                                                                }while(mesh->naechstes(pits));				                                                
				                                                meshtransformed->aktualisieren();
};
void _iggmesh::animieren(_maus<_tg>*mau,_tastatur*tas){
				                                                _iggsystem*gs=iggsystem();
				                                                int mx=gs->mouseposx;
				                                                int my=gs->mouseposy;
				                                                int mz=gs->mouseposz;
				                                                bool ml=gs->mousebutton[1];
				                                                bool mr=gs->mousebutton[2];
				                                                bool mm=gs->mousebutton[3];
				                                                if(active){
				                                                 if(marked==2){
				                                                  if(ml==false){
				                                                   if(inner(mau)){
				                                                    if(selectable){
				                                                     iggsystem()->mesh=this;
					                                                };
				                                                    marked=0;
				                                                   }else{
				                                                    marked=0;
				                                                   };
				                                                  }else{
				                                                   if(inner(mau)==false){
				                                                    marked=0;
				                                                   };
				                                                  };
				                                                 };
				                                                 if(marked==1){
				                                                  if(inner(mau)){
				                                                   if(ml){
				                                                    marked=2;
				                                                   };
				                                                  }else{
				                                                   marked=0;
				                                                  };
				                                                 };				
				                                                 if(marked==0){
				                                                  if(inner(mau)){
  				                                                   marked=1;
				                                                  }; 
   			                                                     };
				                                                 animierenkind(mau,tas);
				                                                 animierenhilfe(mau);
				                                                };
};
void _iggmesh::setzenstatus(){
				                                                iggsystem()->mesh=this;
};
//*******************************************************************************************************************************************************************************
//                                                              S C R O L L B A R
//*******************************************************************************************************************************************************************************
_iggscrollbar::_iggscrollbar(_igg*pg,_tg px,_tg py,_tg pz,_tg pw,_tg ph,int pin):_igg(pg,px,py,pz,pw,ph,pin){
};
_iggscrollbar::~_iggscrollbar(){
};
//*******************************************************************************************************************************************************************************
//                                                              S C R O L L B A R V E R T I C A L
//*******************************************************************************************************************************************************************************
_iggscrollbarvertical::_iggscrollbarvertical(_igg*pg,_tg px,_tg py,_tg pw,_tg ph,_tg pbuttonw,_tg pbuttonh,_to pr,_to pgr,_to pb,_tg s,int pp):_iggscrollbar(pg,px,py,-1,pw,ph,pp){
	                                                            value=s;     
	                                                            scrollstepbutton=20;
	                                                            scrollstepwheel=5;
	                                                            scrollstepbar=10;
	                                                            scrollfriction=0.8;
	                                                            scrollbuttonsmooth=false;
	                                                            controllength=100;
	                                                            borderhoehe=20;
	                                                            hoeheratio=0.05;
	                                                            stretchsliderimagebyratio=false;
	                                                            sliderimage=0;
	                                                            barimage=0;
	                                                            barimagebreite=20;
	                                                            barsmooth=true;
	                                                            buttonup=0;
	                                                            buttondown=0;
	                                                            mousezold=0;
	                                                            mousezvector=0;
	                                                            mover=false;
				                                                sliderimagebreite=20;
				                                                sliderimagehoehe=20;
				                                                setshadow(10,10,_to(0.3f));
				                                                color.setzen(pr,pgr,pb,color.w());
				                                                colortransformed=color;
				                                                _tg bh=borderhoehe;
				                                                _tg h=hoehe();
				                                                _tg w=breite();
				                                                buttonup=new _iggbutton(this,(w/2)-pbuttonw/2,(bh/2)-pbuttonh/2,pbuttonw,pbuttonh,L"",0);
				                                                buttondown=new _iggbutton(this,(w/2)-pbuttonw/2,(h-bh/2)-pbuttonh/2,pbuttonw,pbuttonh,L"",0);
				                                                buttonup->color=colortransformed;
				                                                buttondown->color=colortransformed;
				                                                buttonup->colortransformed=colortransformed;
				                                                buttondown->colortransformed=colortransformed;
};
_iggscrollbarvertical::~_iggscrollbarvertical(){
};
void _iggscrollbarvertical::zeichnen(_grafik*gra,_kamera<_tg>*cam){	
				                                                if((visible)&&(superinvisible==false)){
				                                                 gra->sichtbereich(0,0,iggsystem()->breite(),iggsystem()->hoehe());
				                                                 _vektor3<_tg> p;
				                                                 _vektor4<_to> c;
				                                                 _tg w=breite();
				                                                 _tg h=hoehe();
				                                                 _tg bh=borderhoehe;
				                                                 _tg sbh=(h-2*bh)*hoeheratio;
				                                                 _tg sby=positiontransformed.y()+bh+value*(h-2*bh-sbh);
                                                                 gra->transparenz(true);
                                                                 gra->transparenzmultiplikativ();
				                                                 //----------------------------------------------- zeichnen shadow ------------------------------------
				                                                 if(shadow){
				                                                  _tg dx=shadowdirectiontransformed.x();
				                                                  _tg dy=shadowdirectiontransformed.y();
				                                                  colorhilfe.setzen(0,0,0,colortransformed.w()*shadowopacity*pfadeopacity);
				                                                  if(barimage){
				                                                   _tg iw=barimage->groesse(0);
				                                                   _tg ih=barimage->groesse(1);
				                                                   p=positiontransformed;
				                                                   p.y(p.y()+bh);
				                                                   gra->rechteck(barimage,dx+p.x()+w/2-barimagebreite/2,dy+p.y(),barimagebreite,h-2*bh,colorhilfe);
				                                                  }else{
				                                                   //c.setzen(0,0,0,0.5*pfadeopacity);
				                                                   if(sby>(positiontransformed.y()+bh)){
				                                                    p=positiontransformed;
				                                                    p.y(p.y()+bh);
  				                                                    gra->rechteck(dx+p.x(),dy+p.y(),w,sby-(positiontransformed.y()+bh),colorhilfe);
				                                                   };
				                                                   if(sby<(positiontransformed.y()+h-bh-sbh)){
				                                                    p.setzen(positiontransformed.x(),sby+sbh,0);
				                                                    gra->rechteck(dx+p.x(),dy+p.y(),w,(positiontransformed.y()+h-bh)-(sby+sbh),colorhilfe);
				                                                   };
				                                                  };
				                                                  if(sliderimage){
				                                                   if(stretchsliderimagebyratio){
				                                                    gra->rechteck(sliderimage,dx+p.x()+w/2-sliderimagebreite/2,   dy+sby,sliderimagebreite,sbh,colorhilfe);
				                                                   }else{
				                                                    gra->rechteck(sliderimage,dx+p.x()+w/2-sliderimagebreite/2,   dy+sby+sbh/2-sliderimagehoehe/2,sliderimagebreite,sliderimagehoehe,colorhilfe);
				                                                   };
				                                                  }else{
				                                                   p.setzen(positiontransformed.x(),sby,0);
				                                                   gra->rechteck(p.x()+dx,p.y()+dy,w,sbh,colorhilfe);
 				                                                  };
				                                                 };
				                                                 //----------------------------------------------- zeichnen normal ------------------------------------
				                                                 colorhilfe=colortransformed;
				                                                 colorhilfe.w(colorhilfe.w()*pfadeopacity);
                                                                 gra->transparenz(true);
                                                                 gra->transparenzmultiplikativ();
				                                                 if(barimage){
				                                                  _tg iw=barimage->groesse(0);
				                                                  _tg ih=barimage->groesse(1);
				                                                  p=positiontransformed;
				                                                  p.y(p.y()+bh);
				                                                  gra->rechteck(barimage,p.x()+w/2-barimagebreite/2,p.y(),barimagebreite,h-2*bh,colorhilfe);
				                                                 }else{
				                                                  c=colorhilfe;
				                                                  //c.w(c.w()*0.5);
				                                                  if(sby>(positiontransformed.y()+bh)){
				                                                   p=positiontransformed;
				                                                   p.y(p.y()+bh);
  				                                                   zeichnenguibox(gra,p,w,sby-(positiontransformed.y()+bh),colorhilfe);
				                                                   if(sby>(positiontransformed.y()+bh+10 )){
				                                                    zeichnenguifurche(gra,positiontransformed.x()+w*0.5-1,5+positiontransformed.y()+bh,positiontransformed.x()+w*0.5-1,sby-5,c);
				                                                   };
				                                                  };
				                                                  if(sby<(positiontransformed.y()+h-bh-sbh)){
				                                                   p.setzen(positiontransformed.x(),sby+sbh,0);
				                                                   zeichnenguibox(gra,p,w,(positiontransformed.y()+h-bh)-(sby+sbh),colorhilfe);
				                                                   if(sby<(positiontransformed.y()+h-bh-sbh-10)){
				                                                    zeichnenguifurche(gra,positiontransformed.x()+w*0.5-1,sby+sbh+5,positiontransformed.x()+w*0.5-1,positiontransformed.y()+h-1*bh-5,c);	
				                                                   };
				                                                  };
				                                                 };
				                                                 if(sliderimage){
				                                                  if(stretchsliderimagebyratio){
				                                                   gra->rechteck(sliderimage,p.x()+w/2-sliderimagebreite/2,   sby,sliderimagebreite,sbh,colorhilfe);
				                                                  }else{
				                                                   gra->rechteck(sliderimage,p.x()+w/2-sliderimagebreite/2,   sby+sbh/2-sliderimagehoehe/2,sliderimagebreite,sliderimagehoehe,colorhilfe);
				                                                  };
				                                                 }else{
																  gra->textur(false);
																  gra->tiefenbufferkondition(false);
																  gra->tiefenbufferschreiben(false);
																  gra->transparenzmultiplikativ();

				                                                  p.setzen(positiontransformed.x(), sby,0);
				                                                  zeichnenguibox(gra,p,w,sbh,colorhilfe);
				                                                  p.setzen(positiontransformed.x()+4, sby+4,0);
				                                                  colorhilfe.w(colorhilfe.w()*_to(0.5f));
																//  L->l("hscrollbar ",p.y());
																//  L->l("hscrollbar w",w);
																//  L->l("hscrollbar val",value);
																//  L->l("hscrollbar sbh ",sbh);
				                                                 // zeichnenguirectangleinvers(gra,p,w-8,sbh-8,colorhilfe);		
 				                                                 };
				                                                };
};				
void _iggscrollbarvertical::animieren(_maus<_tg>*mau,_tastatur*tas){
				                                                int mx=int(mau->x());
				                                                int my=int(mau->y());
				                                                int mz=int(mau->z());
				                                                _tg bh=borderhoehe;
				                                                _tg sw=sliderimagebreite;
				                                                _tg sh=sliderimagehoehe;
				                                                _tg w=breite();
				                                                _tg h=hoehe();
				                                                _tg x=positiontransformed.x();
				                                                _tg y=positiontransformed.y();
				                                                _tg sbh=(h-2*bh)*hoeheratio;
				                                                bool gedr=false;
				                                                bool cttl=false;
															//	L->l("scrollbar animieren",value);
				                                                _iggsystem*gs=iggsystem();
				                                                if(active){
				                                                 if(barsmooth){
				                                                  if((mx>=x) && (mx<=x+w) && (my>=y+bh) && (my<=(y+h)-bh) ){// scrollbar
				                                                   if((tas->knopflinks())&&(gs->scrollbartrack==0)){
				                                                    gs->scrollbartrack=this;
				                                                   };
				                                                  };
				                                                  if(gs->scrollbartrack==this){
				                                                   _tg py=((my-sbh/2)-bh/2)-y;
				                                                   if(py<0) py=0;
				                                                   py/=(h-2*bh-sbh);
				                                                   if(py>1) py=1;
				                                                   if(py<0) py=0;
 				                                                   value=(py+value)*0.5;
 				                                                   if(tas->knopflinks()==false) gs->scrollbartrack=0;
				                                                  };
				                                                 }else{
				                                                  _tg ty=y+bh+(h-2*bh)*value;
				                                                  if( (mx>=x) && (mx<=x+w) && (my>=ty-sh) && (my<=ty+sh)){ // scrollbar
				                                                   if((tas->knopflinks())&&(gs->scrollbartrack==0)){
				                                                    gs->scrollbartrack=this;
				                                                   };
				                                                  };
				                                                  if(gs->scrollbartrack==this){
				                                                   _tg py=(((my-sh/2)-sbh/2)-bh/2)-y;
				                                                   if(py<0) py=0;
				                                                   py/=(h-2*bh-sbh);
				                                                   if(py>1) py=1;
				                                                   if(py<0) py=0;
 				                                                   value=(py+value)*0.5;
 				                                                   if(tas->knopflinks()==false) gs->scrollbartrack=0;
				                                                  };				  
				                                                 };
				                                                 cttl=true;
				                                                 if((mx>=x) && (mx<=x+w) && (my>=y) && (my<=y+h)){ //viewport
				                                                  if(mover==false){
				                                                   mousezold=mz;
				                                                   mover=true;
				                                                  };
				                                                  _tg dz=mz-mousezold;
				                                                  mousezold=mz;
				                                                  mousezvector+=dz*(scrollstepwheel/controllength);
				                                                  if(cttl) value-=mousezvector;
				                                                  if(value>1) value=1;
				                                                  if(value<0) value=0;
				                                                 }else{
				                                                  mover=false;
				                                                 };
				                                                 if(cttl) value-=mousezvector;
				                                                 mousezvector*=scrollfriction;				
				                                                 animierenkind(mau,tas);		
				                                                 animierenhilfe(mau);
				                                                 if(value>1) value=1;
				                                                 if(value<0) value=0;
				                                                 bool inn=false;
				                                                 if((mx>=x) && (mx<=x+w) && (my>=y+bh) && (my<=(y+h)-bh)) inn=true;
				                                                 if((marked==2)&&(gs->scrollbartrack!=this)){
				                                                  if(tas->knopflinks()==false){
				                                                   if(inn){
				                                                    gedr=true;	
				                                                    marked=0;
				                                                   }else{
				                                                    marked=0;
				                                                   };
				                                                  }else{
				                                                   if(inn==false){
				                                                    marked=0;
				                                                   };
				                                                  };
				                                                 };
				                                                 if((marked==1)&&(gs->scrollbartrack!=this)){
				                                                  if(inn){
				                                                   if(tas->knopflinks()){
				                                                    marked=2;
				                                                   };
				                                                  }else{
				                                                   marked=0;
				                                                  };
				                                                 };				
				                                                 if((marked==0)&&(gs->scrollbartrack!=this)){
				                                                  if(inn){
  				                                                   marked=1;
				                                                  }; 
   			                                                     };                                             				
				                                                 if(scrollbuttonsmooth){
				                                                  if(tas->knopflinks()) if(buttonup->inner(mau)){
				                                                   value-=(scrollstepbutton/controllength);
				                                                   if(value<0) value=0;
				                                                   if(value>1) value=1;
				                                                   gs->button=0;
				                                                   gs->scrollbarvertical=this;
				                                                   marked=0;
				                                                   gedr=false;
				                                                  };
				                                                  if(tas->knopflinks()) if(buttondown->inner(mau)){
				                                                   value+=(scrollstepbutton/controllength);
				                                                   if(value<0) value=0;
				                                                   if(value>1) value=1;
				                                                   gs->button=0;
				                                                   gs->scrollbarvertical=this;
				                                                   marked=0;
				                                                   gedr=false;
				                                                  };
			 	                                                 }else{
				                                                  if(gs->button==buttonup){
				                                                   value-=(scrollstepbutton/controllength);
				                                                   if(value<0) value=0;
				                                                   if(value>1) value=1;
				                                                   gs->button=0;
				                                                   gs->scrollbarvertical=this;
				                                                   marked=0;
				                                                   gedr=false;
				                                                  };
				                                                  if(gs->button==buttondown){
				                                                   value+=(scrollstepbutton/controllength);
				                                                   if(value<0) value=0;
				                                                   if(value>1) value=1;
				                                                   gs->button=0;
				                                                   gs->scrollbarvertical=this;
				                                                   marked=0;
				                                                   gedr=false;
				                                                  };
				                                                 };
				                                                 if((gs->button==buttonup)||( gs->button==buttondown)){
				                                                  if(scrollbuttonsmooth){
				                                                   gs->button=0;
				                                                   gedr=false;
				                                                   marked=0;
				                                                  };
				                                                 };
                                                                };
 				                                                if(visible){
				                                                 if(marked==0){
				                                                  color=iggsystem()->colors.std;
				                                                  shadowdirectiontransformed=shadowdirection;
				                                                 };
				                                                 if(marked==1){
				                                                  color=iggsystem()->colors.mark;
    				                                              shadowdirectiontransformed=shadowdirection;
		    		                                              shadowdirectiontransformed.mul(0.9);
				                                                 };
				                                                 if(marked==2){
				                                                  color=iggsystem()->colors.active;
    				                                              shadowdirectiontransformed=shadowdirection;
	    			                                              shadowdirectiontransformed.mul(0.8);
		    		                                             };
				                                                 if(gedr){
				                                                  gs->scrollbarvertical=this;
				                                                  if(barsmooth==false){
				                                                   _tg py=((my-sbh/2)-bh/2)-y;
				                                                   if(py<0) py=0;
				                                                   py/=(h-2*bh-sbh);
				                                                   if(py>1) py=1;
				                                                   if(py<0) py=0;
 				                                                   if((py-value)<0){
				                                                    value-=(scrollstepbar/controllength);
				                                                    if(value<0) value=0;	
				                                                   }else if((py-value)>0){
				                                                    value+=(scrollstepbar/controllength);
				                                                    if(value>1) value=1;
				                                                   };
				                                                  };
 				                                                 };

																};//active
															//	L->l("scrollbar animieren2",value);

};				
void _iggscrollbarvertical::setzenstatus(){
                                                                iggsystem()->scrollbarvertical=this;
};				
//*******************************************************************************************************************************************************************************
//                                                              G U I T E X T
//*******************************************************************************************************************************************************************************
_iggtext::_iggtext(_igg*pg,_tg px,_tg py,_tg sz,_zeichenkette<_tt> t,_to pr,_to pgr,_to pb,_zeichensatz*f,_tg mob):_igg(pg,px,py,-1,f->breite(t)+2*mob,f->hoehe(t)+2*mob,0){
	                                                            textshadow=1;
	                                                            border=0;
	                                                            crosslinkimage=0;
				                                                border=mob;
				                                                font=f;
																text=t;
	                                                            ht=L"";
	                                                            textshadow=sz;
	                                                            color.setzen(pr,pgr,pb,1);
				                                                colortransformed=color;

};
_iggtext::~_iggtext(){
};
void _iggtext::setzen(const _zeichenkette<_tt>&t){
				                                                text=t;
																_iggvectorentry*vit;
																if(size.anfang(vit)){
																 if(vit->dynamic){
																  size.x((font->breite(text)+2*border)/parent->breite());
																 }else{
																  size.x(font->breite(text)+2*border);
																 };
																};
};
_zeichenkette<_tt> _iggtext::lesen()const{
				                                                return(text);
};
void _iggtext::zeichensatz(_zeichensatz*zs){
																font=zs;
																_iggvectorentry*vit;
																if(size.anfang(vit)){
																 if(vit->dynamic){
																  size.x((font->breite(text)+2*border)/parent->breite());
																  size.y((font->hoehe(text) +2*border)/parent->hoehe());
																 }else{
																  size.x(font->breite(text)+2*border);
																  size.y(font->hoehe(text) +2*border);
																 };
																};
};
void _iggtext::zeichnen(_grafik*gra,_kamera<_tg>*cam){
				                                                if((visible)&&(superinvisible==false)){
				                                                 if (parent->clip(gra)){
				                                                  //if(font) SetImageFont(font);
				                                                  //_listenknoten<_iggtextline>*it;
				                                                  //if(lines.anfang(it))do{
				                                                  // _iggtextline*gz=it->objekt();
																   _vektor4<_to> hc=colortransformed;
																   _vektor3<_tg> hp(positiontransformed.x()+border,positiontransformed.y()+border,textshadow);
				                                                   hc.w(hc.w()*pfadeopacity);
																   //if(transformation.x()!=0){
																	//gz->position.x(gz->position.x()+size.x()*transformation.x());
																   //};
				                                                   /*if(pzentrieren){
				                                                    gz->position.x(gz->position.x()-font->breite(gz->text)*0.5);
				                                                   }else if(prechtsbuendig){
				                                                    gz->position.x(gz->position.x()-font->breite(gz->text));
				                                                   };*/
			                                                       //hp.x(hp.x()+border);
				                                                   //hp.y(hp.y()+border);
				                                                   //hp.z(textshadow);
				                                                   zeichnenguitext(gra,text,font,hp,hc);
				                                                   //gz->zeichnen(gra,cam);

				                                                  //}while(lines.naechstes(it));
				                                                 };
				                                                };
};
void _iggtext::animieren(_maus<_tg>*mau,_tastatur*tas){
				                                                if((active)&&(visible)){
				                                                 animierenhilfe(mau);
				                                                };
};
void _iggtext::setzenstatus(){
				                                                iggsystem()->text=this;
};				
//*******************************************************************************************************************************************************************************
//                                                              G U I T E X T L I N E
//*******************************************************************************************************************************************************************************
/*
_iggtextline::_iggtextline(_zeichenkette<_tt>&t,_iggtext*gt,_tg px,_tg py,_tg pz,_to pr,_to pg,_to pb){
				                                                text=t;
				                                                guitext=gt;
				                                                color.setzen(pr,pg,pb,1);
				                                                position.setzen(px,py,pz);
				                                                
};	
_iggtextline::~_iggtextline(){
};				
void _iggtextline::zeichnen(_grafik*gra,_kamera<_tg>*cam){
				                                                hp=position;
				                                                hp.z(guitext->textshadow);
				                                                zeichnenguitext(gra,text,guitext->font,hp,color);
};
void _iggtextline::animieren(){
};
*/
//*******************************************************************************************************************************************************************************
//										                        T R A C K B A R D I S P L A Y T E X T
//*******************************************************************************************************************************************************************************
_iggtrackbardisplaytext::_iggtrackbardisplaytext(_tg min,_tg max,const _zeichenkette<_tt>&t,_zeichensatz*f){
                                                                font=f;
                                                                text=t;
                                                                vmin=min;
                                                                vmax=max;
};
//*******************************************************************************************************************************************************************************
//                                                              T R A C K B A R
//*******************************************************************************************************************************************************************************
_iggtrackbar::_iggtrackbar(_igg*pg,_tg px,_tg py,_tg pw,_tg ph,_zeichensatz*f,_to pr,_to pgr,_to pb,_tg w,_tg mi,_tg ma):_igg(pg,px,py,-1,pw,ph,-1){
                                                                font=f;
				                                                rmin=mi;
				                                                rmax=ma;
				                                                setshadow(10,10,_to(0.3f));
	                                                            sliderimage=0;
	                                                            sliderimagebreite=32;
	                                                            sliderimagehoehe=32;
	                                                            sliderimageindex=0;
	                                                            displaymultiplier=1;
	                                                            displayaddition=L"";
	                                                            displayrounding=false;
                                                                setzen(w);
				                                                color.setzen(pr,pgr,pb,color.w());
				                                                colortransformed=color;

};
_iggtrackbar::~_iggtrackbar(){
};
void _iggtrackbar::text(_zeichenkette<_tt>&t,_zeichensatz*f,_tg mi,_tg ma){			
				                                                _iggtrackbardisplaytext*e=new _iggtrackbardisplaytext(mi,ma,t,f);
				                                                displaytextlist.einhaengen(e);
};
_zeichenkette<_tt> _iggtrackbar::text(_zeichensatz*&zs){
				                                                _iggtrackbardisplaytext*found=0;
				                                                _listenknoten<_iggtrackbardisplaytext>*eit;
				                                                zs=0;
				                                                if(displaytextlist.anfang(eit))do{
				                                                 //For Local eit:_iggtrackbardisplaytext=EachIn displaytextlist
				                                                 if(found==0){ 
				                                                  if((pvalue>=eit->objekt()->vmin)&&(pvalue<=eit->objekt()->vmax)) found=eit->objekt();
				                                                 };
				                                                }while(displaytextlist.naechstes(eit));
				                                                if(found){
				                                                 zs=found->font;
				                                                 return(found->text);
				                                                }else{
				                                                 return(L"-");
				                                                };
};				
void _iggtrackbar::minimum(_tg m){
				                                                rmin=m;	
				                                                if(pvalue<rmin) pvalue=rmin;
};
void _iggtrackbar::maximum(_tg m){
				                                                rmax=m;
				                                                if(pvalue>rmax) pvalue=rmax;
};
void _iggtrackbar::setzen(_tg v){	
				                                                _tg p=v;
				                                                if(p>rmax) p=rmax;
				                                                if(p<rmin) p=rmin;			
				                                                pvalue=p;
};
_tg _iggtrackbar::lesen(){
                                                				return(pvalue);
};
void _iggtrackbar::zeichnen(_grafik*gra,_kamera<_tg>*cam){
				                                                if((visible)&&(superinvisible==false)){
				                                                 parent->clip(gra);
				                                                 zeichnenschatten(gra,cam);
				                                                 _tg w=breite();
				                                                 _tg h=hoehe();
		                                                         _vektor4<_to> c;
		                                                         _vektor3<_tg> p;
		                                                         c=colortransformed;
		 		                                                 c.w(c.w()*pfadeopacity);
				                                                 p=positiontransformed;
				                                                 _bild<_tb>*bm=bestbreitematch();
                                                                 gra->transparenz(true);
                                                                 gra->transparenzmultiplikativ();
				                                                 if(bm){
				                                                  c.setzen(1,1,1,c.w());
				                                                  gra->rechteck(bm,positiontransformed.x(),positiontransformed.y()+(h/2)-(bm->groesse(1)/2),w,bm->groesse(1),c);
				                                                 }else{
				                                                 /*
				                                                  SetAlpha(c.w());
				                                                  SetColor(c.x()*255,c.y()*255,c.z()*255);
				                                                  zeichnenRect(p.x(),p.y(),w,h);
				                                                  SetColor(c.x()*511,c.y()*511,c.z()*511);
				                                                  zeichnenLine(p.x(),p.y(),p.x()+w,p.y());
				                                                  zeichnenLine(p.x(),p.y(),p.x(),p.y()+h);
				                                                  zeichnenLine(p.x()+10,p.y()+h/2,p.x()+w-10,p.y()+h/2);
				                                                  SetColor(c.x()*127,c.y()*127,c.z()*127);
				                                                  zeichnenLine(p.x()+w,p.y()+h,p.x(),p.y()+h);
				                                                  zeichnenLine(p.x()+w,p.y()+h,p.x()+w,p.y());
				                                                  //SetBlend(SHADEBLEND);
				                                                  zeichnenLine(p.x()+10,p.y()+h/2+1,p.x()+w-10,p.y()+h/2+1);
				                                                  */
				                                                 };
				                                                 _tg px,py;
				                                                 px=(p.x()+10) + (w-20)*((pvalue-rmin)/fabs(rmax-rmin));
				                                                 py=p.y()+h/2;
				                                                 p.setzen(px-4,p.y()+2,0);
				                                                 c=colortransformed;
				                                                 c.w(c.w()*2*pfadeopacity);
				                                                 if(sliderimage){
				                                                  c.w(colortransformed.w()*pfadeopacity);
				                                                  gra->rechteck(sliderimage,p.x()+4-((sliderimagebreite)/2),p.y()+((h-4)/2)-(sliderimagehoehe/2),sliderimagebreite,sliderimagehoehe,c);
				                                                 }else{
				                                                  zeichnenguibox(gra,p,8,h-4,c);
				                                                 };
				                                                 if(marked==2){
				                                                  _zeichensatz*zs;
				                                                  _zeichenkette<_tt> dt=text(zs);
				                                                  _zeichenkette<_tt> hv;
				                                                  p.setzen(px+10,py-20,1);
				                                                  c.setzen(1,1,1,pfadeopacity);
				                                                  //if font SetImageFont(font);
				                                                  if(dt==L"-"){
				                                                   _tg n=pvalue*displaymultiplier;
				                                                   int ni=int(n);
				                                                   char buf[128];
				                                                   if(displayrounding){
				                                                    _itoa(ni,buf,10);
				                                                    hv.kopierenchar(buf);
				                                                   }else{
				                                                    _gcvt(n,4,buf);
				                                                    hv.kopierenchar(buf);
				                                                   };
				                                                   zeichnenguitext(gra,hv+displayaddition,font,p,c);
				                                                  }else{
				                                                   zeichnenguitext(gra,dt+displayaddition,zs,p,c);
				                                                  };
				                                                 };
				                                                };
};
void _iggtrackbar::animieren(_maus<_tg>*mau,_tastatur*tas){
				                                                int mx=int(mau->x());
				                                                int my=int(mau->y());
				                                                _iggsystem*gs=iggsystem();
				                                                if((active)&&(superinactive==false)&&(superinvisible==false)){
			 	                                                 if(marked==2){
				                                                  if((tas->knopflinks()==false)&&(gs->trackbartrack==this)){
			  	                                                   marked=0;
			  	                                                   gs->trackbartrack=0;
			                                                      };
			                                                     };
				                                                 if(marked==0){
				                                                  if(inner(mau)){
  				                                                   marked=1;
				                                                  }; 
   			                                                     };
				                                                 if(marked==1){
				                                                  if(inner(mau)){
				                                                   if((tas->knopflinks())&&(gs->trackbartrack==0)){
				                                                    marked=2;
				                                                    gs->trackbartrack=this;
				                                                   };
				                                                  }else{
				                                                   marked=0;
				                                                  };
				                                                 };	
				                                                };			
				                                                if(marked==0) shadowdirection.setzen(10,10,0);
				                                                if(marked==1) shadowdirection.setzen(9,9,0);
				                                                if(marked==2) shadowdirection.setzen(8,8,0);
				                                                if((active)&&(superinactive==false)&&(superinvisible==false)){
			 	                                                 animierenkind(mau,tas);
			                                                     animierenhilfe(mau);
				                                                 if(marked==2){
				                                                  _tg pix=mx-(positiontransformed.x()+10);
				                                                  pix/=(breite()-20);//normalisiert
				                                                  pix*=(rmax-rmin);
				                                                  pix+=rmin;
				                                                  pvalue=(pix+pvalue)*0.5;
				                                                  if(pvalue>rmax) pvalue=rmax;
				                                                  if(pvalue<rmin) pvalue=rmin;
				                                                  gs->trackbar=this;
				                                                 };
				                                                };
};
void _iggtrackbar::setzenstatus(){
				                                                iggsystem()->trackbar=this;
};				
//*******************************************************************************************************************************************************************************
//                                                              W I N D O W 
//*******************************************************************************************************************************************************************************
_iggwindow::_iggwindow(_igg*pg,_tg px,_tg py,_tg pw,_tg ph,_to pr,_to pgr,_to pb):_igg(pg,px,py,-1,pw,ph,0){
				                                                color.setzen(pr,pgr,pb,color.w());
				                                                colortransformed=color;
};
_iggwindow::~_iggwindow(){
};
void _iggwindow::zeichnen(_grafik*gra,_kamera<_tg>*cam){
				                                                if((visible)&&(superinvisible==false)){
				                                                 parent->clip(gra);
				                                                 zeichnenschatten(gra,cam);
				                                                 _tg w=breite();
				                                                 _tg h=hoehe();
				                                                 _bild<_tb>*bm=bestbreitematch();
				                                                 colorhilfe=colortransformed;
				                                                 colorhilfe.w(colorhilfe.w()*pfadeopacity);
                                                                 gra->transparenz(true);
                                                                 gra->transparenzmultiplikativ();
				                                                 if(bm){
				                                                  gra->rechteck(bm,positiontransformed.x(),positiontransformed.y(),w,h,colorhilfe);
				                                                 }else{
				                                                  zeichnenguibox(gra,positiontransformed,w,h,colorhilfe);
				                                                 };
				                                                };
};
void _iggwindow::animieren(_maus<_tg>*mau,_tastatur*tas){
				                                                animierenkind(mau,tas);
				                                                animierenhilfe(mau);
};
void _iggwindow::setzenstatus(){
				                                                iggsystem()->window=this;
};				
//*******************************************************************************************************************************************************************************
//                                                              M E N U M A N A G E M E N T 
//*******************************************************************************************************************************************************************************
_iggmenumanagement::_iggmenumanagement(){
                                                                popacity=1;

};
_iggmenumanagement::~_iggmenumanagement(){
};	
void _iggmenumanagement::opazitaet(const _tg o){    
                                                                popacity=o;
                                                                if(popacity<0)popacity=0;
                                                                if(popacity>1)popacity=1;
                                                            
};
_tg _iggmenumanagement::opazitaet()const{
                                                                return(popacity);
};
_iggmenu*_iggmenumanagement::createmenu(){
				                                                return(new _iggmenu(this));
};				
_iggmenu* _iggmenumanagement::menu(int index){
                                                                return((*this)[index]);
};				
void _iggmenumanagement::add(int menuindex,_igg*g)	{						
				                                                _iggmenu*m=menu(menuindex);
				                                                if(m){
				                                                 m->_liste<_igg>::einhaengen(g);
				                                                };
};
void _iggmenumanagement::show(_iggmenu*m,bool fade){
                                                                _iggmenu*mit;
				                                                if(fade){
				                                                 if(anfang(mit))do{
				                                                  mit->fadeout();
				                                                 }while(naechstes(mit));
				                                                 if(m) m->fadein();
				                                                }else{
				                                                 if(anfang(mit))do{
				                                                  mit->visibility(false);
				                                                  mit->activity(false);
				                                                  mit->fadeopacity(0);
				                                                 }while(naechstes(mit));
				                                                 if(m){ 
				                                                  _listenknoten<_igg>*lngit;
				                                                  if(m->anfang(lngit)){//;guilist.firstlink().value())
				                                                   m->visibility(true);
				                                                   m->activity(true);
				                                                   m->fadeopacity(lngit->objekt()->pfadetarget);
				                                                  };
				                                                 };
				                                                };				
};
//*******************************************************************************************************************************************************************************
//                                                              M E N U
//*******************************************************************************************************************************************************************************
_iggmenu::_iggmenu(_iggmenumanagement*mm):_listenknotenbasis<_iggmenu>(mm){
};
_iggmenu::~_iggmenu(){
};


void _iggmenu::add(_igg*g){
				                                                _liste<_igg>::einhaengen(g);
};				
void _iggmenu::visibility(bool v){
                                                                _listenknoten<_igg>*git;
                                                                if(_liste<_igg>::anfang(git))do{
                                                				 git->objekt()->visibility(v);
                                                                }while(_liste<_igg>::naechstes(git));
};	
void _iggmenu::activity(bool a){
                                                                _listenknoten<_igg>*git;
                                                                if(_liste<_igg>::anfang(git))do{
                                                				 git->objekt()->activity(a);
                                                                }while(_liste<_igg>::naechstes(git));
};	
void _iggmenu::fadeopacity(_to o){
                                                                _listenknoten<_igg>*git;
                                                                if(_liste<_igg>::anfang(git))do{
                                                				 git->objekt()->fadeopacity(o);
                                                                }while(_liste<_igg>::naechstes(git));
};	
void _iggmenu::fadeout(){
                                                                _listenknoten<_igg>*git;
                                                                if(_liste<_igg>::anfang(git))do{
                                                				 git->objekt()->fadeout();
                                                                }while(_liste<_igg>::naechstes(git));
};				
void _iggmenu::fadein(){
                                                                _listenknoten<_igg>*git;
                                                                if(_liste<_igg>::anfang(git))do{
                                                				 git->objekt()->fadein();
                                                                }while(_liste<_igg>::naechstes(git));
};
void _iggmenu::fadeoff(){
                                                                _listenknoten<_igg>*git;
                                                                if(_liste<_igg>::anfang(git))do{
                                                				 git->objekt()->fadeoff();
                                                                }while(_liste<_igg>::naechstes(git));
};
void _iggmenu::fadetarget(_to ft){
                                                                _listenknoten<_igg>*git;
                                                                if(_liste<_igg>::anfang(git))do{
                                                				 git->objekt()->fadetarget(ft);
                                                                }while(_liste<_igg>::naechstes(git));
};				
bool _iggmenu::active(){
                                                                _listenknoten<_igg>*git;
                                                                if(_liste<_igg>::anfang(git))do{
                                                				 if(git->objekt()->active) return(true);
                                                                }while(_liste<_igg>::naechstes(git));
                                                				return(false);
};				
bool _iggmenu::visible(){
                                                                _listenknoten<_igg>*git;
                                                                if(_liste<_igg>::anfang(git))do{
				                                                 if(git->objekt()->visible) return(true);
                                                                }while(_liste<_igg>::naechstes(git));
				                                                return(false);
};				
bool _iggmenu::fading(){
                                                                _listenknoten<_igg>*git;
                                                                if(_liste<_igg>::anfang(git))do{
                                                				 if(git->objekt()->fading()) return(true);
                                                                }while(_liste<_igg>::naechstes(git));
                                                				return(false);
};				
//*******************************************************************************************************************************************************************************
//                                                              B E N U T Z E R
//*******************************************************************************************************************************************************************************
_benutzer::_benutzer(_benutzerverwaltung*b,const _zeichenkette<_tt>&name,unsigned int bildindex,_tg punkte):_listenknotenbasis<_benutzer>(b){
                                                                pname=name;
                                                                pbildindex=bildindex;
                                                                ppunkte=punkte;
                                                                pbenutzerverwaltung=b;
};
_benutzer::~_benutzer(){
};
bool _benutzer::vergleichen(_benutzer*b){
				                                                if(b){
				                                                 if(b->ppunkte>ppunkte) return(true);
				                                                };
				                                                return(false);
};
void _benutzer::punkte(const _tg p){
                                                                ppunkte=p;
};
_tg _benutzer::punkte()const{
                                                                return(ppunkte);
};
void _benutzer::bildindex(unsigned int i){
                                                                pbildindex=i;
};
unsigned int _benutzer::bildindex()const{
                                                                return(pbildindex);
};
_bild<_tb>*_benutzer::bild(){
                                                                return(pbenutzerverwaltung->bild(pbildindex));
};
void _benutzer::name(const _zeichenkette<_tt>&n){
                                                                pname=n;
};
const _zeichenkette<_tt>&_benutzer::name()const{
                                                                return(pname);
};
void _benutzer::laden(_datei*d){
                                                                L->schreiben("BENUTZER WIRD GELADEN");
                                                                d->laden(pname);
                                                                d->laden(pbildindex);
                                                                d->laden(ppunkte);
};
void _benutzer::speichern(_datei*d){
                                                                L->schreiben("BENUTZER WIRD GESPEICHERT");
                                                                d->speichern(pname);
                                                                d->speichern(pbildindex);
                                                                d->speichern(ppunkte);
};

//*******************************************************************************************************************************************************************************
//                                                              B E N U T Z E R V E R W A L T U N G 
//*******************************************************************************************************************************************************************************
_benutzerverwaltung::_benutzerverwaltung(const _zeichenkette<char>&datei,const _zeichenkette<_tt>&beschreibung){
                                                                pdatei=datei;
                                                                pbeschreibung=beschreibung;
                                                                paktuell=0;
                                                                FILE*f;
				                                                f=fopen(pdatei,"rb");
				                                                if(f==0){// leeres anlegen	
				                                                 speichern();
				                                                }else{
				                                                 fclose(f);
				                                                 laden();
				                                                };
};
_benutzerverwaltung::~_benutzerverwaltung(){
                                                                speichern();
                                                                pbildliste.loeschen();
};
_benutzer*_benutzerverwaltung::aktuell(){
                                                                return(paktuell);
};
void _benutzerverwaltung::aktuell(_benutzer*b){
                                                                paktuell=b;
};
void _benutzerverwaltung::aktuell(unsigned int i){
                                                                paktuell=_listebasis<_benutzer>::index(i);
};
_bild<_tb>* _benutzerverwaltung::ladenbild(_zeichenkette<char> s,bool clamp){
                                                                _bild<_tb>*b=new _bild<_tb>(s);
                                                            //    b->tiefereskalieren(1);
                                                              //  b->datentausch(0,2);
                                                                b->wiederholung(0,clamp);
                                                                b->wiederholung(1,clamp);
                                                                pbildliste.einhaengen(b);
                                                                return(b);
                                
};
_bild<_tb>*_benutzerverwaltung::bild(unsigned int i){
                                                                return(pbildliste[i]);
};
unsigned int _benutzerverwaltung::bildindex(const _bild<_tb>*b){
                                                                unsigned int i=0;
                                                                _listenknoten<_bild<_tb> >*bit;
                                                                if(pbildliste.anfang(bit))do{
                                                                 if(bit->objekt()==b) return(i);
                                                                 i++;
                                                                }while(pbildliste.naechstes(bit));
                                                                return(0);
};
_liste<_bild<_tb> >*_benutzerverwaltung::bildliste(){
                                                                return(&pbildliste);
};

_benutzer*_benutzerverwaltung::erzeugenbenutzer(const _zeichenkette<_tt>&t,unsigned int i,_tg s){
				                                                _benutzer*b=new _benutzer(this,t,i,s);
				                                                paktuell=b;
				                                                return(b);
};				
_benutzer*_benutzerverwaltung::erzeugenbenutzer(const _zeichenkette<_tt>&t,_bild<_tb>*b,_tg s){
                                                                unsigned int i=0;
                                                                unsigned int index=0;
                                                                _listenknoten<_bild<_tb> >*bit;
                                                                if(pbildliste.anfang(bit))do{
                                                                 if(bit->objekt()==b) index=i;
                                                                 i++;
                                                                }while(pbildliste.naechstes(bit));
				                                                _benutzer*bn=new _benutzer(this,t,index,s);
				                                                paktuell=bn;
				                                                return(bn);
};				
_benutzer*_benutzerverwaltung::existiert(const _zeichenkette<_tt>&t){
				                                                _benutzer*bit;
				                                                _benutzer*r=0;
				                                                if(anfang(bit))do{
				                                                 if(bit->name()==t) r=bit;
				                                                }while(naechstes(bit));
				                                                return(r);
};				
_benutzer*_benutzerverwaltung::benutzer(const _zeichenkette<_tt>&t){
				                                                _benutzer*bit;
				                                                if(anfang(bit))do{
				                                                 if(bit->name()==t) return(bit);
				                                                }while(naechstes(bit));
                                                				return(0);
};
void _benutzerverwaltung::setzenbenutzer(const _zeichenkette<_tt>&t){
				                                                _benutzer*bit;
				                                                if(anfang(bit))do{
				                                                 if(bit->name()==t) {
				                                                  paktuell=bit;
				                                                 };
				                                                }while(naechstes(bit));
};
void _benutzerverwaltung::loeschenbenutzer(const _zeichenkette<_tt>&t){
				                                                _benutzer*bit;
				                                                _liste<_benutzer> lh;
				                                                _listenknoten<_benutzer>*lnbit;
				                                                if(anfang(bit))do{
				                                                 if(bit->name()==t){
				                                                  lh.einhaengen(bit);
				                                                  if(paktuell=bit) paktuell=0;
				                                                 };
				                                                }while(naechstes(bit));
				                                                if(lh.anfang(lnbit))do{
				                                                 delete lnbit->objekt();
				                                                 lnbit->objekt(0);
				                                                }while(lh.naechstes(lnbit));
				                                                lh.aushaengen();
				                                                if(paktuell==0){
				                                                 if(anfang(paktuell)){
				                                                  vorheriges(paktuell);
				                                                 };
				                                                };
};						
void _benutzerverwaltung::speichern(){
                                                                _datei d(pdatei);
                                                                if(d.erzeugen()){
                                                                /* unsigned int c;
                                                                 c=anzahl();
                                                                 fwrite(&c,sizeof(unsigned int),1,d.pfile);
                                                                 L->schreiben("BENUTZERVERWALTUNG : speichern anzahl user = ",(int)c);*/
                                                                 d.speichern(pbeschreibung);
                                                                 
                                                                 if(paktuell){
                                                                  d.speichern(paktuell->name());
                                                                 }else{
                                                                  d.speichern(_zeichenkette<_tt>(L""));
                                                                 };
                                                                 
                                                                 unsigned int c;
                                                                 c=anzahl();
                                                                 L->schreiben("BENUTZERVERWALTUNG : speichern anzahl user = ",(int)c);
                                                                 d.speichern(c);
                                                                
                                                                
                                                                 
                                                                 _benutzer*git;
                                                                 if(anfang(git))do{
                                                                  git->speichern(&d);
                                                                 }while(naechstes(git));
                                                                 
                                                                 d.schliessen();
                                                                };
				/*Local s:TStream
				s=WriteFile(filename)
				If Not s RuntimeError "failed to open the user file for write" 
				WriteLine(s,description)
				//WriteFloat(s,systemperformance)
				If actual
				 WriteLine(s,actual.name)
				Else
				 WriteLine(s,"")
				EndIf
				WriteInt(s,list.count())
				Local bit:_user
				For bit=EachIn list
				 bit.save(s)
				Next
				CloseStream(s)*/
                                                                
};
void _benutzerverwaltung::laden(){
				                                                _listebasis<_benutzer>::loeschen();
				                                                _datei d(pdatei);
				                                                if(d.oeffnennurlesen()){
				                                                 d.laden(pbeschreibung);
				                                                /* unsigned int c;
				                                                 fread(&c,sizeof(unsigned int),1,d.pfile);
				                                                 L->schreiben("BENUTZERVERWALTUNG LADEN usercount =",(int)c);*/

				                                                 _zeichenkette<_tt> username;
				                                                 d.laden(username);
				                                                 
				                                                 unsigned int c;
				                                                 d.laden(c);
				                                                 L->schreiben("BENUTZERVERWALTUNG LADEN usercount =",(int)c);
				                                                 
				                                                 for(unsigned int n=0;n<c;n++){
				                                                  _benutzer*b=new _benutzer(this,L"",0,0);
				                                                  b->laden(&d);
				                                                 };
				                                                 L->schreiben("BENUTZERVERWALTUNG LADEN USERBNAME =",username.ascii());
				                                                 paktuell=benutzer(username);
				                                                 
				                                                 d.schliessen();
				                                                };
				                                                
				/*Local s:TStream
				s=ReadFile(filename)
				If Not s RuntimeError "failed to open the user file for read" 
				description=ReadLine(s)
				//systemperformance=ReadFloat(s)
				Local username$=ReadLine(s)
				Local anz=ReadInt(s)
				For Local i=0 To anz-1
				 Local bit:_user
				 bit=New _user
				 bit.Load(s)
				 bit.link=list.addlast(bit)
				Next
				CloseStream(s)
				actual=user(username)
				*/
};