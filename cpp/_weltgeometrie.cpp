//******************************************************************************************************************************************************************************************************
//  Projekt      : grundplatte
//  Bibliothek   : _grundplatte.lib
//  Modul        : _weltgeometrie.cpp
//  Datum        : 09.01.2006
//  Beschreibung : 
//******************************************************************************************************************************************************************************************************
#include <_welt.hpp>
#include <_weltgeometrie.hpp>
#include <_weltpolygon.hpp>
//******************************************************************************************************************************************************************************************************
//                                                              G E O M E T R I E 
//******************************************************************************************************************************************************************************************************
 
_geometrie::_geometrie(_listebasis<_geometrie >*lg,const _vektor3<_tg> p,_textur<_tb>*tex):_listenknotenbasis<_geometrie >(lg){
                                                                _vektor3<_tg> vz;
                                                                _vektor3<_tg> vy;
                                                                _vektor3<_tg> vx;
                                                                vz.setzen(0,0,1);
                                                                vy.setzen(0,1,0);
                                                                vx.setzen(1,0,0);
                                                                plocus=p;        
                                                                vektor(vx,vy,vz);
                                                                texturvektor(1,1);
                                                                pname="geometrie";
                                                                pcolor.setzen(0.2f,0.2f,0.2f,1);
                                                                pdefaulttexture=tex;
                                                                pdefaulttextureback=tex;
                                                                presolutionscale=1;
                                                                ptexturedivision=true;
                                                                pmarkierung=0;
};
 
_geometrie::_geometrie(_listebasis<_geometrie >*lg,const _vektor3<_tg> p,const _vektor3<_tg> vx,_textur<_tb>*tex):_listenknotenbasis<_geometrie >(lg){
                                                                _vektor3<_tg> vz;
                                                                _vektor3<_tg> vy;
                                                                vz.setzen(0,0,1);
                                                                vy.setzen(0,1,0);
                                                                plocus=p;        
                                                                if(vektor(vx,vy,vz)==false){
                                                                 pvx.setzen(1,0,0);
                                                                 pvy.setzen(0,1,0);
                                                                 pvz.setzen(0,0,1);
                                                                };
                                                                texturvektor(1,1);
                                                                pname="geometrie";
                                                                pcolor.setzen(0.2f,0.2f,0.2f,1);
                                                                pdefaulttexture=tex;
                                                                pdefaulttextureback=tex;
                                                                presolutionscale=1;
                                                                ptexturedivision=true;
                                                                pmarkierung=0;
};
 
_geometrie::_geometrie(_listebasis<_geometrie >*lg,const _vektor3<_tg> p,const _vektor3<_tg> vx,const _vektor3<_tg> vy,_textur<_tb>*tex):_listenknotenbasis<_geometrie >(lg){
                                                                _vektor3<_tg> vz;
                                                                vz=vx%vy;
                                                                plocus=p;        
                                                                if(vektor(vx,vy,vz)==false){
                                                                 pvx.setzen(1,0,0);
                                                                 pvy.setzen(0,1,0);
                                                                 pvz.setzen(0,0,1);
                                                                };
                                                                texturvektor(1,1);
                                                                pname="geometrie";
                                                                pcolor.setzen(0.2f,0.2f,0.2f,1);
                                                                pdefaulttexture=tex;
                                                                pdefaulttextureback=tex;
                                                                presolutionscale=1;
                                                                ptexturedivision=true;
                                                                pmarkierung=0;
};
 
_geometrie::_geometrie(_listebasis<_geometrie >*lg,const _vektor3<_tg> p,const _vektor3<_tg> vx,const _vektor3<_tg> vy,const _vektor3<_tg> vz,_textur<_tb>*tex):_listenknotenbasis<_geometrie >(lg){
                                                                plocus=p;        
                                                                if(vektor(vx,vy,vz)==false){
                                                                 pvx.setzen(1,0,0);
                                                                 pvy.setzen(0,1,0);
                                                                 pvz.setzen(0,0,1);
                                                                };
                                                                texturvektor(1,1);
                                                                pname="geometrie";
                                                                pcolor.setzen(0.2f,0.2f,0.2f,1);
                                                                pdefaulttexture=tex;
                                                                pdefaulttextureback=tex;
                                                                presolutionscale=1;
                                                                ptexturedivision=true;
                                                                pmarkierung=0;
};
 
_geometrie::~_geometrie(){
};
 
_vektor3<_tg> _geometrie::ort() const{
                                                                return(plocus);
};
 
void _geometrie::ort(const _vektor3<_tg> v){
                                                                plocus=v;
};
 
void _geometrie::ort(const _tg x0,const _tg x1,const _tg x2){
                                                                plocus.setzen(x0,x1,x2);
};
void _geometrie::markierung(const int i){
                                                                pmarkierung=i;
};
int _geometrie::markierung()const{
                                                                return(pmarkierung);
};

 
_vektor3<_tg> _geometrie::vektor(const unsigned int i) const{
                                                                if(i==0) return(pvx); else
                                                                if(i==1) return(pvy); else 
                                                                return(pvz);
};
 
bool _geometrie::vektor(const _vektor3<_tg> vx,const _vektor3<_tg> vy,const _vektor3<_tg> vz){
                                                                _tg D;
                                                                _vektoranalysis3<_tg> v3;
                                                                //-----------
                                                                D=v3.determinieren(vx,vy,vz);
                                                                if(fabs(D)<nahenull*4){
                                                                 return(false);
                                                                }else{
                                                                 pvx=vx;
                                                                 pvy=vy;
                                                                 pvz=vz;
                                                                 return(true);
                                                                };
};
 
bool _geometrie::vektor(const unsigned int i,const _vektor3<_tg> v){
                                                                if(i==0) return(vektor0(v)); else
                                                                if(i==1) return(vektor1(v)); else 
                                                                return(vektor2(v));
};
void _geometrie::vektor(const _tg wx,const _tg wy,const _tg wz){
                                                                pvx.setzen(wx,0,0);
                                                                pvy.setzen(0,wy,0);
                                                                pvz.setzen(0,0,wz);
 };
bool _geometrie::vektor0(const _vektor3<_tg> v){
                                                                _tg D;
                                                                _vektoranalysis3<_tg> v3;
                                                                //-----------
                                                                D=v3.determinieren(v,pvy,pvz);
                                                                if(fabs(D)<nahenull*4){
                                                                 return(false);
                                                                }else{
                                                                 pvx=v;
                                                                 return(true);
                                                                };
};
 
bool _geometrie::vektor1(const _vektor3<_tg> v){
                                                                _tg D;
                                                                _vektoranalysis3<_tg> v3;
                                                                //-----------
                                                                D=v3.determinieren(pvx,v,pvz);
                                                                if(fabs(D)<nahenull*4){
                                                                 return(false);
                                                                }else{
                                                                 pvy=v;
                                                                 return(true);
                                                                };
};
 
bool _geometrie::vektor2(const _vektor3<_tg> v){
                                                                _tg D;
                                                                _vektoranalysis3<_tg> v3;
                                                                //-----------
                                                                D=v3.determinieren(pvx,pvy,v);
                                                                if(fabs(D)<nahenull*4){
                                                                 return(false);
                                                                }else{
                                                                 pvz=v;
                                                                 return(true);
                                                                };
};
void _geometrie::texturort(const _vektor2<_tg>&o){
                                                                ptort=o;
};
_vektor2<_tg>&_geometrie::texturort(){
                                                                return(ptort);
};
void _geometrie::texturvektor(const _tg tvx,const _tg tvy){
                                                                ptvx.setzen(tvx,0);
                                                                ptvy.setzen(0,tvy);
};
_vektor2<_tg>&_geometrie::texturvektor(const unsigned int i){
                                                                if(i==0) return(ptvx); else return(ptvy);
};
bool _geometrie::pruefenausrichtung()const{
                                                                _vektor3<_tg> h;
                                                                bool ix;
                                                                bool iy;
                                                                bool iz;
                                                                //----------------
                                                                h=pvy%pvz;
                                                                h.normalisieren();
                                                                if((pvx*h)<0) ix=true; else ix=false;
                                                                
                                                                h=pvx%pvz;
                                                                h.normalisieren();
                                                                if((pvy*h)<0) iy=true; else iy=false;
                                                                
                                                                h=pvx%pvy;
                                                                h.normalisieren();
                                                                if((pvz*h)<0) iz=true; else iz=false;
                                                                
                                                                return(!(ix^iy^iz));//return(not(ix xor iy xor iz));
};                                                                
_vektor4<_to> _geometrie::farbe() const{
                                                                return(pcolor);
};
void _geometrie::farbe(const _vektor4<_to> v){
                                                                pcolor=v;
};
void _geometrie::farbe(const _to c0,const _to c1,const _to c2){
                                                                pcolor.setzen(c0,c1,c2,1);
};
void _geometrie::farbe(const _to c0,const _to c1,const _to c2,const _to c3){
                                                                pcolor.setzen(c0,c1,c2,c3);
};
_zeichenkette<char> _geometrie::name() const{
                                                                return(pname);
};
void _geometrie::name(const _zeichenkette<char> v){
                                                                pname=v;
};
bool _geometrie::aufloesungsskalierung(const _tg s){
                                                                if(s>=1){
                                                                 presolutionscale=s;
                                                                 return(true);
                                                                }else{
                                                                 return(false);
                                                                };
};
_tg _geometrie::aufloesungsskalierung() const{
                                                                return(presolutionscale);
};
/*
 
void _geometrie::scale(_tg s){
                                                                if(s>0){
                                                                 pscale=s;
                                                                };
};
 
_tg _geometrie::scale() const{
                                                                return(pscale);
};
*/
 void _geometrie::textur(_textur<_tb>*t){
                                                                pdefaulttexture=t;
                                                                pdefaulttextureback=t;
 };
 void _geometrie::texturfront(_textur<_tb>*t){
                                                                pdefaulttexture=t;
 };
 void _geometrie::texturrueck(_textur<_tb>*t){
                                                                pdefaulttextureback=t;
 };
_textur<_tb>*_geometrie::standardtextur(){
                                                                return(pdefaulttexture);
};
_textur<_tb>*_geometrie::textur(){
                                                                return(pdefaulttexture);
};
 
bool _geometrie::texturteilung() const{
                                                                return(ptexturedivision);
};
 
void _geometrie::texturteilung(const bool ptd){
                                                                ptexturedivision=ptd;
};
 
void _geometrie::duplizieren(_liste<_schweisskante >*lw,_liste<_schweisskante >*lall){
                                                                _listenknoten<_schweisskante >*lit;
                                                                //---------------------------------------------
                                                                if(lw->anfang(lit))do{
                                                                 lall->einhaengen(lit->objekt());
                                                                }while(lw->naechstes(lit));
};
 
void _geometrie::verschweissen(_netz*m,_schweisskante*lfe0,_schweisskante*lfe1,_liste<_schweisskante >*lall){
                                                                _listenknoten<_vertex >*vit0;
                                                                _listenknoten<_vertex >*vit1;
                                                                _listenknoten<_vertex >*vother;
                                                                _listenknoten<_schweisskante >*lit;
                                                                _vertex*v1;
                                                                _vertex*v0;
                                                                _schweisskante*weother;
                                                                //----------------------------
                                                                if(lfe0->anzahl()==lfe1->anzahl()){
                                                                 if(lfe0->anzahl()>0){
                                                                  lfe0->anfang(vit0);
                                                                  lfe1->anfang(vit1);
                                                                  do{
                                                                   //vit1 wird in vit0 vereinigt, vit1 muss verbogen werden, 
                                                                   //vit1->objekt() bzw v1 nicht mehr existiert
                                                                   v1=vit1->objekt();
                                                                   v0=vit0->objekt();
                                                                   //*************DEBUG : visualisierung der vertexsequenz *********************
                                                                   //_vektor4<_to> col;
                                                                   //col.setzen(0,0,1);
                                                                   //new _weltdebugkreuz(W,v0->ort(),0.02,col);
                                                                   //new _weltdebugkreuz(W,v1->ort(),0.02,col);
                                                                   //***************************************************************************
                                                                   if(v0!=v1){
                                                                    m->verschweissen(v0,v1);
                                                                    vit1->objekt(v0);
                                                                    
                                                                    if(lall->anfang(lit))do{
                                                                     if((lit->objekt()!=lfe0)&&(lit->objekt()!=lfe1)){
                                                                      //untersuchen ob dritte Vertexzeiger verbogen werden müssen
                                                                      weother=lit->objekt();
                                                                      if(weother->anfang(vother))do{
                                                                       if(vother->objekt()==v1) vother->objekt(v0);
                                                                      }while(weother->naechstes(vother));
                                                                     };
                                                                    }while(lall->naechstes(lit));
                                                                    
                                                                   };
                                                                   lfe1->naechstes(vit1);
                                                                  }while(lfe0->naechstes(vit0));
                                                                 };
                                                                };
};
 
_polygon* _geometrie::erzeugendreieck(_netz*netz,_vektor3<_tg>&s0,_vektor3<_tg>&s1,_vektor3<_tg>&s2,_vertexzeiger*v0,_vertexzeiger*v1,_vertexzeiger*v2/*,_vektor3<_tg>*t0,_vektor3<_tg>*t1,_vektor3<_tg>*t2*/,_textur<_tb>*tex){
                                                                _liste<_vektor3<_tg> > slist;
                                                                //_liste<_vektor3<_tg> > tlist;
                                                                _liste<_vertexzeiger > vlist;
                                                                //-----------------------------
                                                                slist.einhaengen(&s0);                                                                                                                                        
                                                                slist.einhaengen(&s1);                                                                                                                                        
                                                                slist.einhaengen(&s2);                                                                                                                                        
                                                                vlist.einhaengen(v0);                                                                                                                                        
                                                                vlist.einhaengen(v1);                                                                                                                                        
                                                                vlist.einhaengen(v2);                                                                                                                                        
                                                                //if(t0)tlist.einhaengen(t0);                                                                                                                                        
                                                                //if(t1)tlist.einhaengen(t1);                                                                                                                                        
                                                                //if(t2)tlist.einhaengen(t2);                                                                                                                 
                                                                return(erzeugenpolygon(netz,slist,vlist,/*tlist,*/tex));
};
 
_polygon* _geometrie::erzeugenrechteck(_netz*netz,_vektor3<_tg>&s0,_vektor3<_tg>&s1,_vektor3<_tg>&s2,_vektor3<_tg>&s3,_vertexzeiger*v0,_vertexzeiger*v1,_vertexzeiger*v2,_vertexzeiger*v3,/*_vektor3<_tg>*t0,_vektor3<_tg>*t1,_vektor3<_tg>*t2,_vektor3<_tg>*t3,*/_textur<_tb>*tex){
                                                                _liste<_vektor3<_tg> > slist;
                                                                //_liste<_vektor3<_tg> > tlist;
                                                                _liste<_vertexzeiger > vlist;
                                                                //-----------------------------
                                                                slist.einhaengen(&s0);                                                                                                                                        
                                                                slist.einhaengen(&s1);                                                                                                                                        
                                                                slist.einhaengen(&s2);                                                                                                                                        
                                                                slist.einhaengen(&s3);                                                                                                   
                                                                vlist.einhaengen(v0);                                                                                                                                        
                                                                vlist.einhaengen(v1);                                                                                                                                        
                                                                vlist.einhaengen(v2);                                                                                                                                        
                                                                vlist.einhaengen(v3);                                                                                                                                        
                                                                //if(t0)tlist.einhaengen(t0);                                                                                                                                        
                                                                //if(t1)tlist.einhaengen(t1);                                                                                                                                        
                                                                //if(t2)tlist.einhaengen(t2);                                                                                                                                        
                                                                //if(t3)tlist.einhaengen(t3);                                                                                                                                        
                                                                return(erzeugenpolygon(netz,slist,vlist,/*tlist,*/tex));
};
 
_polygon* _geometrie::erzeugenpolygon(_netz*netz,_liste<_vektor3<_tg> >&slist,_liste<_vertexzeiger >&vlist/*,_liste<_vektor3<_tg> >&tlist*/,_textur<_tb>*tex){
                                                                _polygon*poly;
                                                                _listenknoten<_vektor3<_tg> >*sit;
                                                                //_listenknoten<_vektor3<_tg> >*tit;
                                                                _listenknoten<_vertexzeiger >*vit;
                                                                //_listenknoten<_vertexzeiger >*vin;
                                                                //bool usetc;
                                                                _verbindervertexpolygon*vcp;
                                                                //_vektor2<_tg> h;
                                                                //-----------------------------
                                                                poly=0;
                                                                if((slist.anzahl()>0)&&(vlist.anzahl()>0)){
                                                                 if((vlist.anzahl()>2)&&(vlist.anzahl()==slist.anzahl())){
                                                                  poly=new _polygon(netz);
                                                                  poly->textur(tex);
                                                                  //neuen vertex erzeugen 
                                                                  slist.anfang(sit);
                                                                  vlist.anfang(vit);
                                                                //  L->schreiben("Polygon");
                                                                  do{

                                                                   if(vit->objekt()->holen()==0){
                                                                    vit->objekt()->setzen(new _vertex(netz,*sit->objekt()));
                                                                    //printf("V");
                                                                    //if(*vit->objekt()==0) printf("error\n");
                                                                   }else{
                                                                    //if(poly->vertex()==0) poly->vertex(vit->objekt()->holen());
                                                                   };
                                                                //   L->schreiben("polygon::vertexposition",*vit->objekt()->holen());

                                                                   slist.naechstes(sit);
                                                                  }while(vlist.naechstes(vit));
                                                                  //bestehenden vertex in das poly integrieren
                                                                  vlist.anfang(vit);
                                                                 // if(tlist.anfang(tit)) usetc=true; else usetc=false;
                                                                  do{
                                                                   //vin=vit->naechstes();
                                                                   vcp=new _verbindervertexpolygon(vit->objekt()->holen(),poly);//,vin->objekt()->holen());
                                                                  // if(usetc){
                                                                  //  h.setzen((*tit->objekt())[0],(*tit->objekt())[1]);
                                                                  //  vcp->einfuegenvektor(0,h);
                                                                  //  tlist.naechstes(tit);
                                                                  // };
                                                                  }while(vlist.naechstes(vit));
                                                                 };
                                                                };
                                                                poly->aktualisieren();
                                                                return(poly);
};
 
_polygon*_geometrie::erzeugennetz(_netz*netz,_vektor3<_tg> o,_vektor3<_tg> a,_vektor3<_tg> b,unsigned int resx,unsigned int resy,_liste<_schweisskante >*lfe){
                                                                _polygon*poly;
                                                                _tg x,y;
                                                                _tg dx,dy;
                                                                _vektor3<_tg> s0;
                                                                _vektor3<_tg> s1;
                                                                _vektor3<_tg> s2;
                                                                _vektor3<_tg> s3;
                                                                _vertexzeiger*v0;
                                                                _vertexzeiger*v1;
                                                                _vertexzeiger*v2;
                                                                _vertexzeiger*v3;
                                                                _polygon*pit;
                                                                _polygon*pstart;
                                                                //_vektor2<_tg> t0;
                                                                //_vektor2<_tg> t1;
                                                                //_vektor2<_tg> t2;
                                                                //_vektor2<_tg> t3;
                                                                _vektor3<_tg> ex;
                                                                _vektor3<_tg> ey;
                                                                _vektor3<_tg> ez;
                                                                _schweisskante*e0;
                                                                _schweisskante*e1;
                                                                _schweisskante*e2;
                                                                _schweisskante*e3;
                                                                unsigned int cx;
                                                                unsigned int cy;
                                                                //----------------------------
                                                                e0=new _schweisskante();
                                                                e1=new _schweisskante();
                                                                e2=new _schweisskante();
                                                                e3=new _schweisskante();
                                                                v0=new _vertexzeiger();
                                                                v1=new _vertexzeiger();
                                                                v2=new _vertexzeiger();
                                                                v3=new _vertexzeiger();
                                                                poly=0;
                                                                pstart=0;
                                                                ex.setzen(1,0,0);
                                                                ey.setzen(0,1,0);
                                                                ez.setzen(0,0,1);
                                                                if(resx<1) resx=1;
                                                                if(resy<1) resy=1;
                                                                dx=_tg(1)/_tg(resx);
                                                                dy=_tg(1)/_tg(resy);
                                                                v0->setzen(0);
                                                                v1->setzen(0);
                                                                v2->setzen(0);
                                                                v3->setzen(0);
                                                                lfe->einhaengen(e0);
                                                                lfe->einhaengen(e1);
                                                                lfe->einhaengen(e2);
                                                                lfe->einhaengen(e3);
                                                                y=0;
                                                                for(cy=0;cy<resy;cy++){
                                                                 x=0;
                                                                 for(cx=0;cx<resx;cx++){
                                                                  s0=o+(a*x)+(b*y);
                                                                  s1=o+(a*(x+dx))+(b*y);
                                                                  s2=o+(a*(x+dx))+(b*(y+dy));
                                                                  s3=o+(a*x)+(b*(y+dy));
                                                                  //t0=(ex*x)+(ey*y);
                                                                  //t1=(ex*(x+dx))+(ey*y);
                                                                  //t2=(ex*(x+dx))+(ey*(y+dy));
                                                                  //t3=(ex*x)+(ey*(y+dy));
                                                                  v2->setzen(0);
                                                                  if(cy==0){
                                                                   v1->setzen(0);
                                                                  }else{
                                                                   v0->setzen(pit->vertex(3));
                                                                   v1->setzen(pit->vertex(2));
                                                                  };
                                                                  poly=erzeugenrechteck(netz,s0,s1,s2,s3,v0,v1,v2,v3/*,t0,t1,t2,t3*/,pdefaulttexture);
                                                                  if((cx==0)&&(cy==0)) {
                                                                   pstart=poly;
                                                                   pit=poly;
                                                                  };
                                                                  if(cy!=0){
                                                                   pit=pit->naechstes();
                                                                  };
                                                                  //------ fusionedge initialization -------------
                                                                  if(cy==0){//unterste zeile
                                                                   e0->einhaengen(poly->vertex());
                                                                   if(cx==0) e3->einhaengen(poly->vertex());
                                                                   if(cx==(resx-1)){
                                                                    e1->einhaengen(poly->vertex(1));
                                                                    e0->einhaengen(poly->vertex(1));
                                                                   };
                                                                  };
                                                                  if(cy==(resy-1)){//oberste zeile
                                                                   e2->einhaengen(poly->vertex(3));
                                                                   if(cx==0) {
                                                                    if(resy>1) e3->einhaengen(poly->vertex());
                                                                    e3->einhaengen(poly->vertex(3));
                                                                   };
                                                                   if(cx==(resx-1)){
                                                                    if(resy>1) e1->einhaengen(poly->vertex(1));
                                                                    e1->einhaengen(poly->vertex(2));
                                                                    e2->einhaengen(poly->vertex(2));
                                                                   };
                                                                  };
                                                                  if((cy!=0)&&(cy!=(resy-1))){//mittelere zeilen
                                                                   if(cx==0) e3->einhaengen(poly->vertex());
                                                                   if(cx==(resx-1)) e1->einhaengen(poly->vertex(1));
                                                                  };
                                                                  //----------------------------------------------
                                                                  v0->setzen(v1->holen());
                                                                  v3->setzen(v2->holen());
                                                                  x+=dx;
                                                                 };
                                                                 v3->setzen(0);
                                                                 v2->setzen(0);
                                                                 v1->setzen(0);
                                                                 v0->setzen(0);
                                                                 y+=dy;
                                                                };
                                                                delete v0;
                                                                delete v1;
                                                                delete v2;
                                                                delete v3;
                                                                return(pstart);
};
 
_polygon*_geometrie::erzeugenrohr(_netz*netz,_vektor3<_tg> o,_vektor3<_tg> rx,_vektor3<_tg> v,_vektor3<_tg> rz,unsigned int resx,unsigned int resy,_liste<_schweisskante >*lfe){ 
                                                                _polygon*poly;
                                                                _tg x,y;
                                                                _tg dx,dy;
                                                                _vektor3<_tg> s0;
                                                                _vektor3<_tg> s1;
                                                                _vektor3<_tg> s2;
                                                                _vektor3<_tg> s3;
                                                                _vertexzeiger*v0;
                                                                _vertexzeiger*v1;
                                                                _vertexzeiger*v2;
                                                                _vertexzeiger*v3;
                                                                _polygon*pit;
                                                                _polygon*px0;
                                                                _polygon*pstart;
                                                                //_vektor3<_tg> t0;
                                                                //_vektor3<_tg> t1;
                                                                //_vektor3<_tg> t2;
                                                                //_vektor3<_tg> t3;
                                                                _vektor3<_tg> ex;
                                                                _vektor3<_tg> ey;
                                                                _schweisskante*e0;
                                                                _schweisskante*e2;
                                                                unsigned int cx;
                                                                unsigned int cy;
                                                                _vektor3<_tg> a;
                                                                //------------------------------------
                                                                e0=new _schweisskante();
                                                                e2=new _schweisskante();
                                                                v0=new _vertexzeiger();
                                                                v1=new _vertexzeiger();
                                                                v2=new _vertexzeiger();
                                                                v3=new _vertexzeiger();
                                                                poly=0;
                                                                pstart=0;
                                                                ex.setzen(1,0,0);
                                                                ey.setzen(0,1,0);
                                                                if(resx<1) resx=1;
                                                                if(resy<1) resy=1;
                                                                dx=_tg(_pi*2)/_tg(resx);
                                                                dy=_tg(1)/_tg(resy);
                                                                v0->setzen(0);
                                                                v1->setzen(0);
                                                                v2->setzen(0);
                                                                v3->setzen(0);
                                                                lfe->einhaengen(e0);
                                                                lfe->einhaengen(e2);
                                                                y=0;
                                                                for(cy=0;cy<resy;cy++){
                                                                 x=0;
                                                                 for(cx=0;cx<resx;cx++){

                                                                  a.setzen(cos(x),sin(x),y);
                                                                  s0=o + rx*a[0] + rz*a[1] + v*a[2];
                                                                  a.setzen(cos(x+dx),sin(x+dx),y);
                                                                  s1=o + rx*a[0] + rz*a[1] + v*a[2];
                                                                  a.setzen(cos(x+dx),sin(x+dx),y+dy);
                                                                  s2=o + rx*a[0] + rz*a[1] + v*a[2];
                                                                  a.setzen(cos(x),sin(x),y+dy);
                                                                  s3=o + rx*a[0] + rz*a[1] + v*a[2];
                                                                  //t0=(ex*x)+(ey*y);
                                                                  //t1=(ex*(x+dx))+(ey*y);
                                                                  //t2=(ex*(x+dx))+(ey*(y+dy));
                                                                  //t3=(ex*x)+(ey*(y+dy));
                                                                  
                                                                  v2->setzen(0);
                                                                  if(cy==0){
                                                                   v1->setzen(0);
                                                                  }else{
                                                                   v0->setzen(pit->vertex(3));
                                                                   v1->setzen(pit->vertex(2));
                                                                  };
                                                                  if(cx==(resx-1)) {
                                                                   v1->setzen(px0->vertex());
                                                                   v2->setzen(px0->vertex(3));
                                                                  };
                                                                  poly=erzeugenrechteck(netz,s0,s1,s2,s3,v0,v1,v2,v3,/*t0,t1,t2,t3,*/pdefaulttexture);
                                                                  if((cx==0)&&(cy==0)) {
                                                                   pstart=poly;
                                                                   pit=poly;
                                                                  };
                                                                  if(cx==0){
                                                                   px0=poly;
                                                                  };
                                                                  if(cy!=0){
                                                                   pit=pit->naechstes();
                                                                  };
                                                                  //------ fusionedge initialization -------------
                                                                  if(cy==0){//unterste zeile
                                                                   e0->einhaengen(poly->vertex());
                                                                  // if(cx==(resx-1)){
                                                                  //  e0->einhaengen(poly->vertex(1));
                                                                  // };
                                                                  };
                                                                  if(cy==(resy-1)){//oberste zeile
                                                                   e2->einhaengen(poly->vertex(3));
                                                                  // if(cx==(resx-1)){
                                                                  //  e2->einhaengen(poly->vertex(2));
                                                                  // };
                                                                  };
                                                                  //----------------------------------------------
                                                                  v0->setzen(v1->holen());
                                                                  v3->setzen(v2->holen());
                                                                  x+=dx;
                                                                 };
                                                                 v3->setzen(0);
                                                                 v2->setzen(0);
                                                                 v1->setzen(0);
                                                                 v0->setzen(0);
                                                                 y+=dy;
                                                                };
                                                                delete v0;
                                                                delete v1;
                                                                delete v2;
                                                                delete v3;
                                                                return(pstart);
};
_polygon*_geometrie::erzeugenkonus(_netz*netz,_vektor3<_tg> o,_vektor3<_tg> rx,_vektor3<_tg> v,_vektor3<_tg> rz,unsigned int resx,unsigned int resy,_liste<_schweisskante >*lfe){ 
                                                                _polygon*poly;
                                                                _tg x,y;
                                                                _tg dx,dy,f,df;
                                                                _vektor3<_tg> s0;
                                                                _vektor3<_tg> s1;
                                                                _vektor3<_tg> s2;
                                                                _vektor3<_tg> s3;
                                                                _vertexzeiger*v0;
                                                                _vertexzeiger*v1;
                                                                _vertexzeiger*v2;
                                                                _vertexzeiger*v3;
                                                                _polygon*pit;
                                                                _polygon*px0;
                                                                _polygon*pstart;
                                                                _vektor3<_tg> ex;
                                                                _vektor3<_tg> ey;
                                                                _schweisskante*e0;
                                                                unsigned int cx;
                                                                unsigned int cy;
                                                                _vektor3<_tg> a;
                                                                //------------------------------------
                                                                e0=new _schweisskante();
                                                               
                                                                v0=new _vertexzeiger();
                                                                v1=new _vertexzeiger();
                                                                v2=new _vertexzeiger();
                                                                v3=new _vertexzeiger();
                                                                poly=0;
                                                                pstart=0;
                                                                ex.setzen(1,0,0);
                                                                ey.setzen(0,1,0);
                                                                if(resx<1) resx=1;
                                                                if(resy<1) resy=1;
                                                                dx=_tg(_pi*2)/_tg(resx);
                                                                dy=_tg(1)/_tg(resy);
                                                                df=_tg(1)/_tg(resy);
                                                                v0->setzen(0);
                                                                v1->setzen(0);
                                                                v2->setzen(0);
                                                                v3->setzen(0);
                                                                lfe->einhaengen(e0);
                                                                f=1;
                                                                y=0;
                                                                for(cy=0;cy<resy;cy++){
                                                                 x=0;
                                                                 for(cx=0;cx<resx;cx++){

                                                                  a.setzen(cos(x),sin(x),y);
                                                                  s0=o + rx*a[0]*f    + rz*a[1]*f + v*a[2];
                                                                  a.setzen(cos(x+dx),sin(x+dx),y);
                                                                  s1=o + rx*a[0]*f    + rz*a[1]*f + v*a[2];
                                                                  a.setzen(cos(x+dx),sin(x+dx),y+dy);
                                                                  s2=o + rx*a[0]*(f-df) + rz*a[1]*(f-df) + v*a[2];
                                                                  a.setzen(cos(x),sin(x),y+dy);
                                                                  s3=o + rx*a[0]*(f-df) + rz*a[1]*(f-df) + v*a[2];

                                                                  if(cy<(resy-1)) v2->setzen(0);
                                                                  if(cy==0){
                                                                   v1->setzen(0);
                                                                  }else{
                                                                   v0->setzen(pit->vertex(3));
                                                                   v1->setzen(pit->vertex(2));
                                                                  };
                                                                  if(cx==(resx-1)) {
                                                                   v1->setzen(px0->vertex());
                                                                   if(cy<(resy-1)) v2->setzen(px0->vertex(3));
                                                                  };
                                                                  
                                                                  if(cy==(resy-1))
                                                                  poly=erzeugendreieck(netz,s0,s1,s2,v0,v1,v2,pdefaulttexture);
                                                                  else
                                                                  poly=erzeugenrechteck(netz,s0,s1,s2,s3,v0,v1,v2,v3,pdefaulttexture);
                                                                  if((cx==0)&&(cy==0)) {
                                                                   pstart=poly;
                                                                   pit=poly;
                                                                  };
                                                                  if(cx==0){
                                                                   px0=poly;
                                                                  };
                                                                  if(cy!=0){
                                                                   pit=pit->naechstes();
                                                                  };
                                                                  //------ fusionedge initialization -------------
                                                                  if(cy==0){//unterste zeile
                                                                   e0->einhaengen(poly->vertex());
                                                                  };
                                                                  //----------------------------------------------
                                                                  if(cy==(resy-1)){
                                                                   v0->setzen(v1->holen());
                                                                  }else{
                                                                   v0->setzen(v1->holen());
                                                                   v3->setzen(v2->holen());
                                                                  };
                                                                  x+=dx;
                                                                 };
                                                                 v3->setzen(0);
                                                                 v2->setzen(0);
                                                                 v1->setzen(0);
                                                                 v0->setzen(0);
                                                                 y+=dy;
                                                                 f-=df;
                                                                };
                                                                delete v0;
                                                                delete v1;
                                                                delete v2;
                                                                delete v3;
                                                                return(pstart);
};
_polygon*_geometrie::erzeugentorus(_netz*netz,_vektor3<_tg> o,_vektor3<_tg> vek0,_vektor3<_tg> vek1,_vektor3<_tg> vek2,_tg r0,_tg r1,_tg anteil0start,_tg anteil0ende,_tg anteil1start,_tg anteil1ende,unsigned int resx,unsigned int resy,_liste<_schweisskante >*lfe){ 
                                                                _polygon*poly;
                                                                _tg x,y;
                                                                _tg dx,dy;
                                                                _vektor3<_tg> s0;
                                                                _vektor3<_tg> s1;
                                                                _vektor3<_tg> s2;
                                                                _vektor3<_tg> s3;
                                                                _vertexzeiger*v0;
                                                                _vertexzeiger*v1;
                                                                _vertexzeiger*v2;
                                                                _vertexzeiger*v3;
                                                                _polygon*pit;
                                                                _polygon*px0;
                                                                _polygon*pstart;
                                                                //_vektor3<_tg> t0;
                                                                //_vektor3<_tg> t1;
                                                                //_vektor3<_tg> t2;
                                                                //_vektor3<_tg> t3;
                                                                _vektor3<_tg> ex;
                                                                _vektor3<_tg> ey;
                                                                _schweisskante*e0;
                                                                _schweisskante*e2;
                                                                unsigned int cx;
                                                                unsigned int cy;
                                                                _vektor3<_tg> a;
                                                                //------------------------------------
                                                                e0=new _schweisskante();
                                                                e2=new _schweisskante();
                                                                v0=new _vertexzeiger();
                                                                v1=new _vertexzeiger();
                                                                v2=new _vertexzeiger();
                                                                v3=new _vertexzeiger();
                                                                poly=0;
                                                                pstart=0;
                                                                ex.setzen(1,0,0);
                                                                ey.setzen(0,1,0);
                                                                if(resx<3) resx=3;
                                                                if(resy<3) resy=3;
                                                                dx=_tg(360.0f*(anteil0ende-anteil0start))/_tg(resx);
                                                                dy=_tg(360.0f*(anteil1ende-anteil1start))/_tg(resy);
                                                                v0->setzen(0);
                                                                v1->setzen(0);
                                                                v2->setzen(0);
                                                                v3->setzen(0);
                                                                lfe->einhaengen(e0);
                                                                lfe->einhaengen(e2);
                                                                y=anteil1start;
                                                                for(cy=0;cy<resy;cy++){
                                                                 x=anteil0start;
                                                                 for(cx=0;cx<resx;cx++){
                                                                 
                                                                 
                                                                  //kreis machen auf x,y
                                                                  //x ist kreis abschnitt
                                                                  
                                                                  a.setzen(cos(x*_ph)*r0,sin(x*_ph)*r1,0);
                                                                  a.roty(y);
                                                                  s0.setzen(cos(y*_ph),0,sin(y*_ph));
                                                                  s0=a + o + vek0*s0[0] + vek1*s0[1] + vek2*s0[2];
                                                                  
                                                                  a.setzen(cos((x+dx)*_ph)*r0,sin((x+dx)*_ph)*r1,0);
                                                                  a.roty(y);
                                                                  s1.setzen(cos(y*_ph),0,sin(y*_ph));
                                                                  s1=a + o + vek0*s1[0] + vek1*s1[1] + vek2*s1[2];
                                                                  
                                                                  a.setzen(cos((x+dx)*_ph)*r0,sin((x+dx)*_ph)*r1,0);
                                                                  a.roty(y+dy);
                                                                  s2.setzen(cos((y+dy)*_ph),0,sin((y+dy)*_ph));
                                                                  s2=a + o + vek0*s2[0] + vek1*s2[1] + vek2*s2[2];
                                                                  
                                                                  a.setzen(cos(x*_ph)*r0,sin(x*_ph)*r1,0);
                                                                  a.roty(y+dy);
                                                                  s3.setzen(cos((y+dy)*_ph),0,sin((y+dy)*_ph));
                                                                  s3=a + o + vek0*s3[0] + vek1*s3[1] + vek2*s3[2];

                                                                  /*a.setzen(cos(x),sin(x),y);
                                                                  s0=o + rx*a[0] + rz*a[1] + v*a[2];
                                                                  a.setzen(cos(x+dx),sin(x+dx),y);
                                                                  s1=o + rx*a[0] + rz*a[1] + v*a[2];
                                                                  a.setzen(cos(x+dx),sin(x+dx),y+dy);
                                                                  s2=o + rx*a[0] + rz*a[1] + v*a[2];
                                                                  a.setzen(cos(x),sin(x),y+dy);
                                                                  s3=o + rx*a[0] + rz*a[1] + v*a[2];*/
                                                                  
                                                                  v2->setzen(0);
                                                                  if(cy==0){
                                                                   v1->setzen(0);
                                                                  }else{
                                                                   v0->setzen(pit->vertex(3));
                                                                   v1->setzen(pit->vertex(2));
                                                                  };
                                                                  if(cx==(resx-1)) {
                                                                   v1->setzen(px0->vertex());
                                                                   v2->setzen(px0->vertex(3));
                                                                  };
                                                                  poly=erzeugenrechteck(netz,s0,s1,s2,s3,v0,v1,v2,v3,pdefaulttexture);
                                                                  if((cx==0)&&(cy==0)) {
                                                                   pstart=poly;
                                                                   pit=poly;
                                                                  };
                                                                  if(cx==0){
                                                                   px0=poly;
                                                                  };
                                                                  if(cy!=0){
                                                                   pit=pit->naechstes();
                                                                  };
                                                                  //------ fusionedge initialization -------------
                                                                  if(cy==0){//unterste zeile
                                                                   e0->einhaengen(poly->vertex());
                                                                  // if(cx==(resx-1)){
                                                                  //  e0->einhaengen(poly->vertex(1));
                                                                  // };
                                                                  };
                                                                  if(cy==(resy-1)){//oberste zeile
                                                                   e2->einhaengen(poly->vertex(3));
                                                                  // if(cx==(resx-1)){
                                                                  //  e2->einhaengen(poly->vertex(2));
                                                                  // };
                                                                  };
                                                                  //----------------------------------------------
                                                                  v0->setzen(v1->holen());
                                                                  v3->setzen(v2->holen());
                                                                  x+=dx;
                                                                 };
                                                                 v3->setzen(0);
                                                                 v2->setzen(0);
                                                                 v1->setzen(0);
                                                                 v0->setzen(0);
                                                                 y+=dy;
                                                                };
                                                                delete v0;
                                                                delete v1;
                                                                delete v2;
                                                                delete v3;
                                                                return(pstart);
};
 
_polygon*_geometrie::erzeugenscheibe(_netz*netz,_vektor3<_tg> o,_vektor3<_tg> rx,_vektor3<_tg> rz,unsigned int res,_liste<_schweisskante >*lfe){
                                                                _polygon*pstart;
                                                                _polygon*poly;
                                                                _schweisskante*e0;
                                                                _liste<_vektor3<_tg> > slist;
                                                                _liste<_vertexzeiger > vlist;
                                                                //_liste<_vektor2<_tg> > tlist;
                                                                _listenknoten<_vertexzeiger >*vit;
                                                                unsigned int i;
                                                                _vektor3<_tg> s0;
                                                                //_vektor2<_tg> t0;
                                                                _tg x,dx;
                                                                _vektor2<_tg> a;
                                                                _vektor3<_tg> h;
                                                                //--------------------------------
                                                                e0=new _schweisskante();
                                                                lfe->einhaengen(e0);
                                                                h.setzen(0.5,0.5,0.5);
                                                                if(res<3) res=3;
                                                                x=0;
                                                                dx=_tg(_pi*2)/_tg(res);
                                                                for(i=0;i<res;i++){
                                                                 a.setzen(cos(x),sin(x));
                                                                 s0=o + rx*a[0] + rz*a[1];
                                                                 //t0=s0-o;
                                                                 //t0.normalisieren();
                                                                 //t0*=0.5;
                                                                 //t0+=h;
                                                                 slist.einhaengen(new _vektor3<_tg>(s0));
                                                                 vlist.einhaengen(new _vertexzeiger());
                                                                 //tlist.einhaengen(new _vektor2<_tg>(t0));
                                                                 x+=dx;
                                                                };
                                                                poly=erzeugenpolygon(netz,slist,vlist,/*tlist,*/pdefaulttexture);
                                                                pstart=poly;
                                                                if(vlist.anfang(vit))do{
                                                                 e0->einhaengen(vit->objekt()->holen());
                                                                }while(vlist.naechstes(vit));
                                                                slist.loeschen();
                                                                vlist.loeschen();
                                                                //tlist.loeschen();
                                                                return(pstart);
};
 
_polygon*_geometrie::erzeugenkugelschale(_netz*netz,_vektor3<_tg> o,_vektor3<_tg> rx,_vektor3<_tg> ry,_vektor3<_tg> rz,unsigned int resx,unsigned int resy,_liste<_schweisskante >*lfe){
                                                                _polygon*poly;
                                                                _tg x,y;
                                                                _tg dx,dy;
                                                                _vektor3<_tg> s0;
                                                                _vektor3<_tg> s1;
                                                                _vektor3<_tg> s2;
                                                                _vektor3<_tg> s3;
                                                                _vertexzeiger*v0;
                                                                _vertexzeiger*v1;
                                                                _vertexzeiger*v2;
                                                                _vertexzeiger*v3;
                                                                _polygon*pit;
                                                                _polygon*px0;
                                                                _polygon*pstart;
                                                                //_vektor2<_tg> t0;
                                                                //_vektor2<_tg> t1;
                                                                //_vektor2<_tg> t2;
                                                                //_vektor2<_tg> t3;
                                                                _vektor3<_tg> ex;
                                                                _vektor3<_tg> ey;
                                                                _schweisskante*e0;
                                                                _schweisskante*e2;
                                                                unsigned int cx;
                                                                unsigned int cy;
                                                                _vektor3<_tg> a;
                                                                //------------------------------------
                                                                e0=new _schweisskante();
                                                                e2=new _schweisskante();
                                                                v0=new _vertexzeiger();
                                                                v1=new _vertexzeiger();
                                                                v2=new _vertexzeiger();
                                                                v3=new _vertexzeiger();
                                                                poly=0;
                                                                pstart=0;
                                                                ex.setzen(1,0,0);
                                                                ey.setzen(0,1,0);
                                                                if(resx<1) resx=1;
                                                                if(resy<1) resy=1;
                                                                dx=_tg(_pi*2)/_tg(resx);
                                                                dy=_tg(_pi/2)/_tg(resy);
                                                                v0->setzen(0);
                                                                v1->setzen(0);
                                                                v2->setzen(0);
                                                                v3->setzen(0);
                                                                lfe->einhaengen(e0);
                                                                lfe->einhaengen(e2);
                                                                y=0;
                                                                for(cy=0;cy<resy;cy++){
                                                                 x=0;
                                                                 for(cx=0;cx<resx;cx++){

                                                                  
                                                                  a.setzen(cos(x)*cos(y),sin(y),sin(x)*cos(y));
                                                                  s0=o + rx*a[0] + ry*a[1] + rz*a[2];
                                                                  a.setzen(cos(x+dx)*cos(y),sin(y),sin(x+dx)*cos(y));
                                                                  s1=o + rx*a[0] + ry*a[1] + rz*a[2];
                                                                  a.setzen(cos(x+dx)*cos(y+dy),sin(y+dy),sin(x+dx)*cos(y+dy));
                                                                  s2=o + rx*a[0] + ry*a[1] + rz*a[2];
                                                                  a.setzen(cos(x)*cos(y+dy),sin(y+dy),sin(x)*cos(y+dy));
                                                                  s3=o + rx*a[0] + ry*a[1] + rz*a[2];
                                                                  
                                                                  
                                                                  /*a.setzen(cos(x+dx),sin(x+dx),y);
                                                                  s1=o + rx*a[0] + rz*a[1] + v*a[2];
                                                                  a.setzen(cos(x+dx),sin(x+dx),y+dy);
                                                                  s2=o + rx*a[0] + rz*a[1] + v*a[2];
                                                                  a.setzen(cos(x),sin(x),y+dy);
                                                                  s3=o + rx*a[0] + rz*a[1] + v*a[2];*/
                                                                  //t0=(ex*x)+(ey*y);
                                                                  //t1=(ex*(x+dx))+(ey*y);
                                                                  //t2=(ex*(x+dx))+(ey*(y+dy));
                                                                  //t3=(ex*x)+(ey*(y+dy));
                                                                  
                                                                  
                                                                  if(cy==(resy-1)){
                                                                  
                                                                   if(cx==0) v2->setzen(0);
                                                                   if(cy==0){
                                                                    v1->setzen(0);
                                                                   }else{
                                                                    v0->setzen(pit->vertex(3));
                                                                    v1->setzen(pit->vertex(2));
                                                                   };
                                                                   if(cx==(resx-1)) {
                                                                    v1->setzen(px0->vertex());
                                                                    //v2->setzen(px0->vertex(2));
                                                                   };
                                                                   poly=erzeugendreieck(netz,s0,s1,s2,v0,v1,v2,/*t0,t1,t2,*/pdefaulttexture);
                                                                   v0->setzen(v1->holen());
                                                                   //v2->setzen(v2->holen());
                                                                   
                                                                  }else{
                                                                   v2->setzen(0);
                                                                   if(cy==0){
                                                                    v1->setzen(0);
                                                                   }else{
                                                                    v0->setzen(pit->vertex(3));
                                                                    v1->setzen(pit->vertex(2));
                                                                   };
                                                                   if(cx==(resx-1)) {
                                                                    v1->setzen(px0->vertex());
                                                                    v2->setzen(px0->vertex(3));
                                                                   };
                                                                   poly=erzeugenrechteck(netz,s0,s1,s2,s3,v0,v1,v2,v3,/*t0,t1,t2,t3,*/pdefaulttexture);
                                                                   v0->setzen(v1->holen());
                                                                   v3->setzen(v2->holen());
                                                                  };
                                                                  
                                                                  if((cx==0)&&(cy==0)) {
                                                                   pstart=poly;
                                                                   pit=poly;
                                                                  };
                                                                  if(cx==0){
                                                                   px0=poly;
                                                                  };
                                                                  if(cy!=0){
                                                                   pit=pit->naechstes();
                                                                  };
                                                                  //------ fusionedge initialization -------------
                                                                  if(cy==0){//unterste zeile
                                                                   e0->einhaengen(poly->vertex());
                                                                   //if(cx==(resx-1)){
                                                                   // e0->einhaengen(poly->vertex(1));
                                                                   //};
                                                                  };
                                                                  //----------------------------------------------
                                                                  x+=dx;
                                                                 };
                                                                 v3->setzen(0);
                                                                 v2->setzen(0);
                                                                 v1->setzen(0);
                                                                 v0->setzen(0);
                                                                 y+=dy;
                                                                };
                                                                delete v0;
                                                                delete v1;
                                                                delete v2;
                                                                delete v3;
                                                                return(pstart);
};
 
_polygon*_geometrie::erzeugentorusknoten(_netz*netz,_vektor3<_tg> o,_vektor3<_tg> vx,_vektor3<_tg> vy,_vektor3<_tg> vz,unsigned int resx,unsigned int resy,_liste<_schweisskante >*lfe){                                                               
                                                                _polygon*poly;
                                                                _tg x,y;
                                                                _tg dx,dy=0;
                                                                _vektor3<_tg> s0;
                                                                _vektor3<_tg> s1;
                                                                _vektor3<_tg> s2;
                                                                _vektor3<_tg> s3;
                                                                _vertexzeiger*v0;
                                                                _vertexzeiger*v1;
                                                                _vertexzeiger*v2;
                                                                _vertexzeiger*v3;
                                                                //_polygon*pit;
                                                                //_polygon*px0;
                                                                _polygon*pstart;
                                                                //_vektor2<_tg> t0;
                                                                //_vektor2<_tg> t1;
                                                                //_vektor2<_tg> t2;
                                                                //_vektor2<_tg> t3;
                                                                _vektor3<_tg> ex;
                                                                _vektor3<_tg> ey;
                                                                _schweisskante*e0;
                                                                _schweisskante*e2;
                                                                unsigned int cx;
                                                                //unsigned int cy;
                                                                _vektor3<_tg> a;
                                                                
                                                                //------------------------------------
                                                                e0=new _schweisskante();
                                                                e2=new _schweisskante();
                                                                v0=new _vertexzeiger();
                                                                v1=new _vertexzeiger();
                                                                v2=new _vertexzeiger();
                                                                v3=new _vertexzeiger();
                                                                poly=0;
                                                                pstart=0;
                                                                ex.setzen(1,0,0);
                                                                ey.setzen(0,1,0);
                                                                if(resx<1) resx=1;
                                                                if(resy<1) resy=1;
                                                                dx=_tg(2*_pi)/_tg(resx);
                                                               // dy=_tg(1)/_tg(resy);
                                                                v0->setzen(0);
                                                                v1->setzen(0);
                                                                v2->setzen(0);
                                                                v3->setzen(0);
                                                                lfe->einhaengen(e0);
                                                                lfe->einhaengen(e2);
                                                                
                                                                y=0;
                                                               // for(cy=0;cy<resy;cy++){
                                                                 x=0;
                                                                 for(cx=0;cx<resx;cx++){

                                                                 /* a.setzen(cos(x),sin(x),y);
                                                                  s0=o + rx*a[0] + rz*a[1] + v*a[2];
                                                                  a.setzen(cos(x+dx),sin(x+dx),y);
                                                                  s1=o + rx*a[0] + rz*a[1] + v*a[2];
                                                                  a.setzen(cos(x+dx),sin(x+dx),y+dy);
                                                                  s2=o + rx*a[0] + rz*a[1] + v*a[2];
                                                                  a.setzen(cos(x),sin(x),y+dy);
                                                                  s3=o + rx*a[0] + rz*a[1] + v*a[2];
                                                                  */
                                                                  //ff=  2*_pi*(2.0f/3.0f);
                                                                  
                                                                  _tg ff;
                                                                  ff=0;
                                                                  a.setzen((2*x),1.5+sin(    (1+ff*2)*2*x*1.5f-(_pi/2)   )               ,0);
                                                                  s0.setzen(cos(a[0])*a[1],sin(a[0])*a[1],sin((1+ff*2)*x*3));
                                                                  
                                                                  //a.setzen((2*x)-(_pi/2),1.5+cos(x*4),0);
                                                                  //s0.setzen(cos(a[0])*a[1],0,sin(a[0])*a[1]);
                                                                  
                                                                  s1=s0+ex*0.1;
                                                                  s2=s0+ex*0.1+ey*0.1;
                                                                  s3=s0+ey*0.1;
                                                                  //t0=(ex*x)+(ey*y);
                                                                  //t1=(ex*(x+dx))+(ey*y);
                                                                  //t2=(ex*(x+dx))+(ey*(y+dy));
                                                                  //t3=(ex*x)+(ey*(y+dy));
                                                                  
                                                              v0->setzen(0);
                                                              v1->setzen(0);
                                                              v2->setzen(0);
                                                              v3->setzen(0);
                                                                  
                                                                  
                                                                  /*v2->setzen(0);
                                                                  if(cy==0){
                                                                   v1->setzen(0);
                                                                  }else{
                                                                   v0->setzen(pit->vertex(3));
                                                                   v1->setzen(pit->vertex(2));
                                                                  };
                                                                  if(cx==(resx-1)) {
                                                                   v1->setzen(px0->vertex());
                                                                   v2->setzen(px0->vertex(3));
                                                                  };*/
                                                                  poly=erzeugenrechteck(netz,s0,s1,s2,s3,v0,v1,v2,v3,/*t0,t1,t2,t3,*/pdefaulttexture);
                                                                  /*if((cx==0)&&(cy==0)) {
                                                                   pstart=poly;
                                                                   pit=poly;
                                                                  };
                                                                  if(cx==0){
                                                                   px0=poly;
                                                                  };
                                                                  if(cy!=0){
                                                                   pit=pit->naechstes();
                                                                  };*/
                                                                  //------ fusionedge initialization -------------
                                                                  /*if(cy==0){//unterste zeile
                                                                   e0->einhaengen(poly->vertex());
                                                                  };
                                                                  if(cy==(resy-1)){//oberste zeile
                                                                   e2->einhaengen(poly->vertex(3));
                                                                  };
                                                                  */
                                                                  //----------------------------------------------
                                                                  v0->setzen(v1->holen());
                                                                  v3->setzen(v2->holen());
                                                                  x+=dx;
                                                                 };
                                                                 v3->setzen(0);
                                                                 v2->setzen(0);
                                                                 v1->setzen(0);
                                                                 v0->setzen(0);
                                                                 y+=dy;
                                                              //  };
                                                                delete v0;
                                                                delete v1;
                                                                delete v2;
                                                                delete v3;
                                                                return(pstart);
};
//------------------------------------------------------------  AUTOTEXTUREKOORDINATEN -----------------------------------------------------------------------------------------------------------------
 
_polygon*_geometrie::erzeugentexturkoordinatennetz(_polygon* start,_vektor2<_tg> o,_vektor2<_tg> a,_vektor2<_tg> b,unsigned int rx,unsigned int ry){
                                                                _polygon*pit;
                                                                _vertex*vit;
                                                                _verbindervertexpolygon*vcp;
                                                                unsigned int cx;
                                                                unsigned int cy;
                                                                _tg x,y,dx,dy;
                                                                _vektor2<_tg> t[4];
                                                                _vektor2<_tg> h;
                                                                int i;
                                                                //----------------------------
                                                                pit=start;
                                                                t[0].setzen(0,0);
                                                                t[1].setzen(1,0);
                                                                t[2].setzen(1,1);
                                                                t[3].setzen(0,1);
                                                                if(rx<1) rx=1;
                                                                if(ry<1) ry=1;
                                                                dx=_tg(1)/_tg(rx);
                                                                dy=_tg(1)/_tg(ry);
                                                                y=0;
                                                                for(cy=0;cy<ry;cy++){
                                                                 x=0;
                                                                 for(cx=0;cx<rx;cx++){
                                                                  t[0]=o+(a*x)     +(b*y);
                                                                  t[1]=o+(a*(x+dx))+(b*y);
                                                                  t[2]=o+(a*(x+dx))+(b*(y+dy));
                                                                  t[3]=o+(a*x)     +(b*(y+dy));
                                                                  _listenknoten<_vertex>*lnvit;
                                                                  //vit=pit->vertex();
                                                                  //if(vit){
                                                                  if(pit->anfang(lnvit)){
                                                                   for(i=0;i<4;i++){
                                                                    vit=lnvit->objekt();
                                                                    vcp=static_cast<_verbindervertexpolygon*>(lnvit);//vit->connector(pit);
                                                                    h.setzen(t[i][0],t[i][1]);
                                                                    vcp->einfuegenvektor(0,h);
                                                                    lnvit=lnvit->naechstes();
                                                                   };
                                                                  };
                                                                  pit=pit->naechstes();
                                                                  x+=dx;
                                                                 };
                                                                 y+=dy;
                                                                };
                                                                return(pit);
};
_polygon*_geometrie::erzeugentexturkoordinatenkonus(_polygon* start,_vektor2<_tg> o,_vektor2<_tg> a,_vektor2<_tg> b,unsigned int rx,unsigned int ry){
                                                                _polygon*pit;
                                                                _vertex*vit;
                                                                _verbindervertexpolygon*vcp;
                                                                unsigned int cx;
                                                                unsigned int cy;
                                                                _tg x,y,dx,dy;
                                                                _vektor2<_tg> t[4];
                                                                _vektor2<_tg> h;
                                                                int i;
                                                                //----------------------------
                                                                pit=start;
                                                                t[0].setzen(0,0);
                                                                t[1].setzen(1,0);
                                                                t[2].setzen(1,1);
                                                                t[3].setzen(0,1);
                                                                if(rx<1) rx=1;
                                                                if(ry<1) ry=1;
                                                                dx=_tg(1)/_tg(rx);
                                                                dy=_tg(1)/_tg(ry);
                                                                y=0;
                                                                for(cy=0;cy<ry;cy++){
                                                                 x=0;
                                                                 for(cx=0;cx<rx;cx++){
                                                                  t[0]=o+(a*x)     +(b*y);
                                                                  t[1]=o+(a*(x+dx))+(b*y);
                                                                  t[2]=o+(a*(x+dx))+(b*(y+dy));
                                                                  t[3]=o+(a*x)     +(b*(y+dy));
                                                                  _listenknoten<_vertex>*lnvit;
                                                                  //vit=pit->vertex();
                                                                  //if(vit){
                                                                  if(pit->anfang(lnvit)){
                                                                   int va=4;
                                                                   if(cy==(ry-1)) va=3;//oben dreiecke
                                                                   for(i=0;i<va;i++){
                                                                    vit=lnvit->objekt();
                                                                    vcp=static_cast<_verbindervertexpolygon*>(lnvit);//vit->connector(pit);
                                                                    h.setzen(t[i][0],t[i][1]);
                                                                    vcp->einfuegenvektor(0,h);
                                                                    lnvit=lnvit->naechstes();
                                                                   };
                                                                  };
                                                                  pit=pit->naechstes();
                                                                  x+=dx;
                                                                 };
                                                                 y+=dy;
                                                                };
                                                                return(pit);
};
_polygon*_geometrie::erzeugentexturkoordinatenscheibe(_polygon* start,_vektor2<_tg> o,_vektor2<_tg> a,_vektor2<_tg> b,unsigned int rx){
                                                                unsigned int i=0;
                                                                _tg w,dw,aa,bb;
                                                                _polygon*pit;
                                                                _vertex*vit;
                                                                _verbindervertexpolygon*vcp;
                                                                _listenknoten<_vertex>*lnvit;
                                                                _vektor2<_tg> h;
                                                                //-----------
                                                                pit=start;
                                                                dw=360.0f/_tg(rx);
                                                                w=0;
                                                                if(pit->anfang(lnvit)){
                                                                 for(i=0;i<rx;i++){
                                                                  vit=lnvit->objekt();
                                                                  vcp=static_cast<_verbindervertexpolygon*>(lnvit);//vit->connector(pit);
                                                                  aa=sin(_ph*w);
                                                                  bb=cos(_ph*w);
                                                                  h=o+a*aa+b*bb;
                                                                  vcp->einfuegenvektor(0,h);
                                                                  lnvit=lnvit->naechstes();
                                                                  w+=dw;
                                                                 };
                                                                };
                                                                pit=pit->naechstes();
                                                                return(pit);
};
_polygon*_geometrie::erzeugentexturkoordinatenscheibe(_polygon* start,_vektor2<_tg> o,_vektor2<_tg> a,_vektor2<_tg> b,unsigned int rx,unsigned int ry){
                                                                unsigned int i=0;
                                                                unsigned int irx,iry;
                                                                _tg w,dw,aa0,bb0,aa1,bb1,dr,r;
                                                                _polygon*pit;
                                                                _vertex*vit;
                                                                _verbindervertexpolygon*vcp;
                                                                _listenknoten<_vertex>*lnvit;
                                                                _vektor2<_tg> h0,h1,h2,h3;
                                                                //-----------
                                                                pit=start;
                                                                
                                                                dr=1.0f/_tg(ry);
                                                                r=1;
                                                                for(iry=0;iry<ry;iry++){
                                                                 dw=360.0f/_tg(rx);
                                                                 w=0;
                                                                 for(irx=0;irx<rx;irx++){
                                                                
                                                                  if(pit->anfang(lnvit)){
                                                                   //for(i=0;i<4;i++){
                                                                    aa0=sin(_ph*w);
                                                                    bb0=cos(_ph*w);
                                                                    aa1=sin(_ph*(w+dw));
                                                                    bb1=cos(_ph*(w+dw));
                                                                    h0=o+a*aa0*r+b*bb0*r;
                                                                    h1=o+a*aa1*r+b*bb1*r;
                                                                    h2=o+a*aa1*(r-dr)+b*bb1*(r-dr);
                                                                    h3=o+a*aa0*(r-dr)+b*bb0*(r-dr);
                                                                    
                                                                    vcp=static_cast<_verbindervertexpolygon*>(lnvit);
                                                                    vcp->einfuegenvektor(0,h0);
                                                                    lnvit=lnvit->naechstes();
                                                                   
                                                                    vcp=static_cast<_verbindervertexpolygon*>(lnvit);
                                                                    vcp->einfuegenvektor(0,h1);
                                                                    lnvit=lnvit->naechstes();
                                                                   
                                                                    vcp=static_cast<_verbindervertexpolygon*>(lnvit);
                                                                    vcp->einfuegenvektor(0,h2);
                                                                    lnvit=lnvit->naechstes();
                                                                    
                                                                    if(iry<(ry-1)){
                                                                     vcp=static_cast<_verbindervertexpolygon*>(lnvit);
                                                                     vcp->einfuegenvektor(0,h3);
                                                                     lnvit=lnvit->naechstes();
                                                                    };

                                                                  };
                                                                  w+=dw;
                                                                  pit=pit->naechstes();
                                                                 };
                                                                 r-=dr;
                                                                };
                                                                
                                                                return(pit);
};
void _geometrie::einhaengendialog(_dynamischerdialog*){
};
void _geometrie::auslesendialog(_dynamischerdialog*){
};
bool _geometrie::laden(_datei*d){
																ladenbeginn();
																return(true);
};
void _geometrie::speichern(_datei*d){
};
bool _geometrie::assoziieren(){
																if(zeigergeladen()){
																 loeschenzeiger();
																};
																return(true);
};
//******************************************************************************************************************************************************************************************************
//                                                              G E O M E T R I E N E T Z
//******************************************************************************************************************************************************************************************************
 
_geometrienetz::_geometrienetz(_listebasis<_geometrie >*lg,const _vektor3<_tg>&o,const _vektor3<_tg>&vx,const _vektor3<_tg>&vy,_textur<_tb>*tex):_geometrie(lg,o,vx,vy,tex){
                                                                presolution.setzen(1,1);
                                                                name("geometrienetz");
                                                                ptclength.setzen(1,1);
};
_geometrienetz::_geometrienetz(_listebasis<_geometrie >*lg,const _vektor3<_tg>&o,const _tg wx,const _tg wy,_textur<_tb>*tex):_geometrie(lg,o,_vektor3<_tg>(wx,0,0),_vektor3<_tg>(0,wy,0),tex){
                                                                presolution.setzen(1,1);
                                                                name("geometrienetz");
                                                                ptclength.setzen(1,1);
};
_geometrienetz::~_geometrienetz(){
};
 _netz* _geometrienetz::erzeugen(){
                                                                unsigned int rx;
                                                                unsigned int ry;
                                                                _liste<_schweisskante > lwebot;
                                                                _vektor3<_tg> o;
                                                                _vektor3<_tg> m;
                                                                _netz*netz;
                                                                _polygon*poly;
                                                                //---------------------------------------
                                                                netz=new _netz();
                                                                rx=(unsigned int)(_tg(presolution[0])*aufloesungsskalierung());
                                                                ry=(unsigned int)(_tg(presolution[1])*aufloesungsskalierung());
                                                                m.setzen(0,0,0);
                                                                //-------------------------- BOT -----------------------------
                                                                o.setzen(0,0,0);
                                                                poly=erzeugennetz(netz,o,vektor(0),vektor(1),rx,ry,&lwebot);
                                                                //netz->invertieren();
                                                                netz->aktualisieren(); 
                                                                lwebot.loeschen();
                                                                netz->farbe(farbe());
                                                                netz->farbeverbinder(farbe());
                                                                
                                                                if(standardtextur()) erzeugenstandardtexturkoordinaten(netz);
                                                                netz->verschiebenvertex(ort());
                                                                return(netz);
};
 
void _geometrienetz::erzeugenstandardtexturkoordinaten(_netz*netz){
                                                                unsigned int rx;
                                                                unsigned int ry;
                                                                _polygon*poly;
                                                                _vektor2<_tg> o;
                                                                _vektor2<_tg> a;
                                                                _vektor2<_tg> b;
                                                                //-------------------
                                                                rx=(unsigned int)(_tg(presolution[0])*aufloesungsskalierung());
                                                                ry=(unsigned int)(_tg(presolution[1])*aufloesungsskalierung());
                                                                //i=0;
                                                                if(netz->anfang(poly)){
                                                                 o.setzen(0,0);
                                                                 a.setzen(1*ptclength[0],0);
                                                                 b.setzen(0,1*ptclength[1]);
                                                                 poly=erzeugentexturkoordinatennetz(poly,o,a,b,rx,ry);                                                                
                                                                };
};

void _geometrienetz::aufloesung(_vektor2<unsigned int> r){
                                                                if(r[0]<1) r.setzenkomponente(0,1);
                                                                if(r[1]<1) r.setzenkomponente(1,1);
                                                                presolution=r;
};
void _geometrienetz::aufloesung(unsigned int ax,unsigned int ay){
                                                                presolution.setzen(ax,ay);
};
unsigned int _geometrienetz::aufloesung(const unsigned int i){
                                                                if(i==0) return(presolution[0]); else return(presolution[1]);
};
void _geometrienetz::groesse(const _tg wx,const _tg wy){
                                                                vektor(wx,wy,1);
};
void _geometrienetz::groesse(const _vektor3<_tg>&wx,const _vektor3<_tg>&wy){
                                                                vektor(0,wx);
                                                                vektor(1,wy);
                                                                vektor(2,_vektor3<_tg>(0,0, 1));
};

void _geometrienetz::texturkoordinatenlaenge(const _tg lx,const _tg ly){
                                                                ptclength.setzen(lx,ly);
};   
void _geometrienetz::einhaengendialog(_dynamischerdialog*d){
                                                                d->editierbar(this);
                                                                d->neusetzen(L"Netz erzeugen");
                                                                d->einhaengen(L"Konstruktionsparameter",L"Position",ort());
                                                                d->einhaengen(L"Konstruktionsparameter",L"Vektor Achse 0",vektor(0));
                                                                d->einhaengen(L"Konstruktionsparameter",L"Vektor Achse 1",vektor(1));
                                                                d->einhaengen(L"Konstruktionsparameter",L"Texturkoordinaten Skalierung",ptclength);
                                                                d->einhaengen(L"Konstruktionsparameter",L"Geometrische Auflösung",presolution);
                                                                d->einhaengen(L"Konstruktionsparameter",L"Geometrische Auflösungsskalierung",aufloesungsskalierung());
                                                                d->einhaengen(L"Konstruktionsparameter",L"Farbe",farbe());
                                                                _zeichenkette<char> k="ni";
                                                                if(standardtextur()) d->einhaengen(L"Konstruktionsparameter",L"Textur",standardtextur()->name()); else d->einhaengen(L"Konstruktionsparameter",L"Textur",k);
};
void _geometrienetz::auslesendialog(_dynamischerdialog*d){
                                                                _vektor3<_tg> v,v0,v1,v2;
                                                                _vektor4<_to> f;
                                                                _tg sk;
                                                                d->auslesen(L"Konstruktionsparameter",L"Position",v);
                                                                ort(v);
                                                                d->auslesen(L"Konstruktionsparameter",L"Vektor Achse 0",v0);
                                                                d->auslesen(L"Konstruktionsparameter",L"Vektor Achse 1",v1);
                                                                vektor(v0,v1,v1%v0);
                                                                d->auslesen(L"Konstruktionsparameter",L"Texturkoordinaten Skalierung",ptclength);
                                                                d->auslesen(L"Konstruktionsparameter",L"Geometrische Auflösung",presolution);
                                                                d->auslesen(L"Konstruktionsparameter",L"Geometrische Auflösungsskalierung",sk);
                                                                aufloesungsskalierung(sk);
                                                                d->auslesen(L"Konstruktionsparameter",L"Farbe",f);
                                                                farbe(f);
                                                               // _zeichenkette<char> k="ni";
                                                               // if(standardtextur()) d->einhaengen(L"Konstruktionsparameter",L"Textur",standardtextur()->name()); else d->einhaengen(L"Konstruktionsparameter",L"Textur",k);
};
//******************************************************************************************************************************************************************************************************
//                                                              G E O M E T R I E S C H E I B E
//******************************************************************************************************************************************************************************************************
_geometriescheibe::_geometriescheibe(_listebasis<_geometrie >*lg,const _vektor3<_tg>&loc,const _vektor3<_tg>&radx,const _vektor3<_tg>&radz,_textur<_tb>*tex):_geometrie(lg,loc,radx,radx%radz,radz,tex){
                                                                name("Scheibe");
                                                                presolution=6;
                                                                ptclength.setzen(1,1);
                                                                ptcoffset.setzen(0,0);
};
_geometriescheibe::~_geometriescheibe(){
};
void _geometriescheibe::radius(const _tg rx,const _tg rz){
																_vektor3<_tg> v0=vektor(0);
																_vektor3<_tg> v2=vektor(2);
																v0.normalisieren();
																v2.normalisieren();
																v0*=rx;
																v2*=rz;
                                                                _geometrie::vektor(v0,v0%v2,v2);
};
void _geometriescheibe::radius(const _vektor3<_tg>&rx,const _vektor3<_tg>&rz){
                                                                _geometrie::vektor(rx,rx%rz,rz);
};
 _vektor3<_tg> _geometriescheibe::radius(const unsigned int i) const{
                                                                if(i==0) return(_geometrie::vektor(0)); else return(_geometrie::vektor(2));
};
_netz* _geometriescheibe::erzeugen(){
                                                                unsigned int rx;
                                                                _vektor3<_tg> o;
                                                                _netz*netz;
                                                                _liste<_schweisskante > lwedis;
                                                                //---------------------------------------
                                                                netz=new _netz();
                                                                rx=(unsigned int)(_tg(presolution)*aufloesungsskalierung());
                                                                o.setzen(0,0,0);
                                                                erzeugenscheibe(netz,o,radius(0),radius(1),rx,&lwedis);
                                                                lwedis.loeschen();
                                                                netz->aktualisieren(); 
                                                                netz->farbe(farbe());
                                                                netz->farbeverbinder(farbe());
                                                                if(standardtextur()) erzeugenstandardtexturkoordinaten(netz);
                                                                netz->verschiebenvertex(ort());
                                                                return(netz);
};
void _geometriescheibe::erzeugenstandardtexturkoordinaten(_netz*netz){
                                                                unsigned int rx;
                                                                _polygon*poly;
                                                                _vektor2<_tg> o;
                                                                _vektor2<_tg> a;
                                                                _vektor2<_tg> b;
                                                                //-------------------
                                                                rx=(unsigned int)(_tg(presolution)*aufloesungsskalierung());
                                                                if(netz->anfang(poly)){
                                                                 o.setzen(ptcoffset[0],ptcoffset[1]);
                                                                 a.setzen(ptclength[0],0);
                                                                 b.setzen(0,ptclength[1]);
                                                                 erzeugentexturkoordinatenscheibe(poly,o,a,b,rx);
                                                                };
};
void _geometriescheibe::aufloesung(unsigned int r){
                                                                if(r<3) r=3;
                                                                presolution=r;
};
void _geometriescheibe::texturkoordinatenverschiebung(const _tg lx,const _tg ly){
                                                                ptcoffset.setzen(lx,ly);
};
void _geometriescheibe::texturkoordinatenlaenge(const _tg lx,const _tg ly){
                                                                ptclength.setzen(lx,ly);
};
void _geometriescheibe::einhaengendialog(_dynamischerdialog*d){
                                                                d->editierbar(this);
                                                                d->neusetzen(L"Scheibe erzeugen");
                                                                
                                                                d->einhaengen(L"Konstruktionsparameter",L"Position",ort());
                                                                d->einhaengen(L"Konstruktionsparameter",L"Radiusvektor 0",radius(0));
                                                                d->einhaengen(L"Konstruktionsparameter",L"Radiusvektor 1",radius(1));
                                                                d->einhaengen(L"Konstruktionsparameter",L"Texturkoordinaten Skalierung",ptclength);
                                                                d->einhaengen(L"Konstruktionsparameter",L"Texturkoordinaten Verschiebung",ptcoffset);
                                                                d->einhaengen(L"Konstruktionsparameter",L"Geometrische Auflösung",presolution);
                                                                d->einhaengen(L"Konstruktionsparameter",L"Farbe",farbe());
                                                                _zeichenkette<char> k="ni";
                                                                if(standardtextur()) d->einhaengen(L"Konstruktionsparameter",L"Textur",standardtextur()->name()); else d->einhaengen(L"Konstruktionsparameter",L"Textur",k);
};
void _geometriescheibe::auslesendialog(_dynamischerdialog*d){
                                                                _vektor3<_tg> v,v0,v2;
                                                                _vektor4<_to> f;
                                                                _tg sk;
                                                                d->auslesen(L"Konstruktionsparameter",L"Position",v);
                                                                ort(v);
                                                                d->auslesen(L"Konstruktionsparameter",L"Radiusvektor 0",v0);
                                                                d->auslesen(L"Konstruktionsparameter",L"Radiusvektor 1",v2);
                                                                vektor(v0,v0%v2,v2);
                                                                d->auslesen(L"Konstruktionsparameter",L"Texturkoordinaten Skalierung",ptclength);
                                                                d->auslesen(L"Konstruktionsparameter",L"Texturkoordinaten Verschiebung",ptcoffset);
                                                                d->auslesen(L"Konstruktionsparameter",L"Geometrische Auflösung",presolution);
                                                                d->auslesen(L"Konstruktionsparameter",L"Geometrische Auflösungsskalierung",sk);
                                                                aufloesungsskalierung(sk);
                                                                d->auslesen(L"Konstruktionsparameter",L"Farbe",f);
                                                                farbe(f);
                                                               // _zeichenkette<char> k="ni";
                                                               // if(standardtextur()) d->einhaengen(L"Konstruktionsparameter",L"Textur",standardtextur()->name()); else d->einhaengen(L"Konstruktionsparameter",L"Textur",k);
};
//******************************************************************************************************************************************************************************************************
//                                                              G E O M E T R I E F L A E C H E H E R M I T E 
//******************************************************************************************************************************************************************************************************
_geometrieflaechehermite::_geometrieflaechehermite(_listebasis<_geometrie >*lg,_textur<_tb>*tex):_geometrie(lg,_vektor3<_tg>(0,0,0),_vektor3<_tg>(1,0,0),_vektor3<_tg>(0,0,1),tex){
                                                                presolution.setzen(1,1);
                                                                name("flaechehermite");
                                                                ptclength.setzen(1,1);
                                                                //vx=vex;
                                                                //vy=vey;
                                                                
};
 
_geometrieflaechehermite::~_geometrieflaechehermite(){
};
_flaechehermite<_tg>*_geometrieflaechehermite::flaeche(){
                                                                return(&pflaeche);
};
_netz* _geometrieflaechehermite::erzeugen(){
                                                                unsigned int rx;
                                                                unsigned int ry;
                                                                _liste<_schweisskante > lwebot;
                                                                _vektor3<_tg> o;
                                                                _vektor3<_tg> m;
                                                                _netz*netz;
                                                                _polygon*poly;
                                                                //---------------------------------------
                                                                netz=new _netz();
                                                                rx=(unsigned int)(_tg(presolution[0])*aufloesungsskalierung());
                                                                ry=(unsigned int)(_tg(presolution[1])*aufloesungsskalierung());
                                                                m.setzen(0,0,0);
                                                                //-------------------------- BOT -----------------------------
                                                                o.setzen(0,0,0);
                                                                poly=erzeugennetz(netz,o,vektor(0),vektor(1),rx,ry,&lwebot);
                                                                //hermitische flaeche abbilden
                                                                netz->markierungvertex(1);
                                                                _polygon*pit;
                                                                if(netz->anfang(pit))do{
                                                                 _vertex*vit;
                                                                 _listenknoten<_vertex>*lnvit;
                                                                 iterierenliste(pit,lnvit,
                                                                  vit=lnvit->objekt();
                                                                  //vit=pit->vertex();
                                                                  //if(vit)do{
                                                                  if(vit->markierung()==1){
                                                                   vit->markierung(0);
                                                                   vit->ort(pflaeche.berechnen((vit->ort())[0],(vit->ort())[2]));
                                                                  };
                                                                  //vit=vit->naechstes(pit);
                                                                 //}while(vit!=pit->vertex());
                                                                 );
                                                                }while(netz->naechstes(pit));
                                                                //netz->invertieren();
                                                                netz->aktualisieren(); 
                                                                lwebot.loeschen();
                                                                netz->farbe(farbe());
                                                                netz->farbeverbinder(farbe());
                                                                
                                                                if(standardtextur()) erzeugenstandardtexturkoordinaten(netz);
                                                                netz->verschiebenvertex(ort());
                                                                return(netz);
};
 
void _geometrieflaechehermite::erzeugenstandardtexturkoordinaten(_netz*netz){
                                                                unsigned int rx;
                                                                unsigned int ry;
                                                                _polygon*poly;
                                                                _vektor2<_tg> o;
                                                                _vektor2<_tg> a;
                                                                _vektor2<_tg> b;
                                                                //-------------------
                                                                rx=(unsigned int)(_tg(presolution[0])*aufloesungsskalierung());
                                                                ry=(unsigned int)(_tg(presolution[1])*aufloesungsskalierung());
                                                                //i=0;
                                                                if(netz->anfang(poly)){
                                                                 o.setzen(0,0);
                                                                 a.setzen(1*ptclength[0],0);
                                                                 b.setzen(0,1*ptclength[1]);
                                                                 poly=erzeugentexturkoordinatennetz(poly,o,a,b,rx,ry);                                                                
                                                                };
};

void _geometrieflaechehermite::aufloesung(_vektor2<unsigned int> r){
                                                                if(r[0]<1) r.setzenkomponente(0,1);
                                                                if(r[1]<1) r.setzenkomponente(1,1);
                                                                presolution=r;
};
void _geometrieflaechehermite::texturkoordinatenlaenge(const _tg lx,const _tg ly){
                                                                ptclength.setzen(lx,ly);
};   
void _geometrieflaechehermite::einhaengendialog(_dynamischerdialog*d){
                                                                d->editierbar(this);
                                                                d->neusetzen(L"Netz erzeugen");
                                                                d->einhaengen(L"Konstruktionsparameter",L"Ortort 0",pflaeche.ortort(0));
                                                                d->einhaengen(L"Konstruktionsparameter",L"Ortort 1",pflaeche.ortort(1));
                                                                d->einhaengen(L"Konstruktionsparameter",L"Ortort 2",pflaeche.ortort(2));
                                                                d->einhaengen(L"Konstruktionsparameter",L"Ortort 3",pflaeche.ortort(3));
                                                                new _editionskopplungort(d,L"Konstruktionsparameter",L"Ortort 0");
                                                                new _editionskopplungort(d,L"Konstruktionsparameter",L"Ortort 1");
                                                                new _editionskopplungort(d,L"Konstruktionsparameter",L"Ortort 2");
                                                                new _editionskopplungort(d,L"Konstruktionsparameter",L"Ortort 3");
                                                                d->einhaengen(L"Konstruktionsparameter",L"Ortvektor 0",pflaeche.ortvektor(0));
                                                                d->einhaengen(L"Konstruktionsparameter",L"Ortvektor 1",pflaeche.ortvektor(1));
                                                                d->einhaengen(L"Konstruktionsparameter",L"Ortvektor 2",pflaeche.ortvektor(2));
                                                                d->einhaengen(L"Konstruktionsparameter",L"Ortvektor 3",pflaeche.ortvektor(3));
                                                                d->einhaengen(L"Konstruktionsparameter",L"Vektorort 0",pflaeche.vektorort(0));
                                                                d->einhaengen(L"Konstruktionsparameter",L"Vektorort 1",pflaeche.vektorort(1));
                                                                d->einhaengen(L"Konstruktionsparameter",L"Vektorort 2",pflaeche.vektorort(2));
                                                                d->einhaengen(L"Konstruktionsparameter",L"Vektorort 3",pflaeche.vektorort(3));
                                                                d->einhaengen(L"Konstruktionsparameter",L"Vektorvektor 0",pflaeche.vektorvektor(0));
                                                                d->einhaengen(L"Konstruktionsparameter",L"Vektorvektor 1",pflaeche.vektorvektor(1));
                                                                d->einhaengen(L"Konstruktionsparameter",L"Vektorvektor 2",pflaeche.vektorvektor(2));
                                                                d->einhaengen(L"Konstruktionsparameter",L"Vektorvektor 3",pflaeche.vektorvektor(3));
                                                                d->einhaengen(L"Konstruktionsparameter",L"Texturkoordinaten Skalierung",ptclength);
                                                                d->einhaengen(L"Konstruktionsparameter",L"Geometrische Auflösung",presolution);
                                                                d->einhaengen(L"Konstruktionsparameter",L"Geometrische Auflösungsskalierung",aufloesungsskalierung());
                                                                d->einhaengen(L"Konstruktionsparameter",L"Farbe",farbe());
                                                                _zeichenkette<char> k="ni";
                                                                if(standardtextur()) d->einhaengen(L"Konstruktionsparameter",L"Textur",standardtextur()->name()); else d->einhaengen(L"Konstruktionsparameter",L"Textur",k);
};
void _geometrieflaechehermite::auslesendialog(_dynamischerdialog*d){
                                                                _vektor3<_tg> v,v0,v1,v2;
                                                                _vektor4<_to> f;
                                                                _tg sk;
                                                                d->auslesen(L"Konstruktionsparameter",L"Ortort 0",pflaeche.ortort(0));
                                                                d->auslesen(L"Konstruktionsparameter",L"Ortort 1",pflaeche.ortort(1));
                                                                d->auslesen(L"Konstruktionsparameter",L"Ortort 2",pflaeche.ortort(2));
                                                                d->auslesen(L"Konstruktionsparameter",L"Ortort 3",pflaeche.ortort(3));
                                                                d->auslesen(L"Konstruktionsparameter",L"Ortvektor 0",pflaeche.ortvektor(0));
                                                                d->auslesen(L"Konstruktionsparameter",L"Ortvektor 1",pflaeche.ortvektor(1));
                                                                d->auslesen(L"Konstruktionsparameter",L"Ortvektor 2",pflaeche.ortvektor(2));
                                                                d->auslesen(L"Konstruktionsparameter",L"Ortvektor 3",pflaeche.ortvektor(3));
                                                                d->auslesen(L"Konstruktionsparameter",L"Vektorort 0",pflaeche.vektorort(0));
                                                                d->auslesen(L"Konstruktionsparameter",L"Vektorort 1",pflaeche.vektorort(1));
                                                                d->auslesen(L"Konstruktionsparameter",L"Vektorort 2",pflaeche.vektorort(2));
                                                                d->auslesen(L"Konstruktionsparameter",L"Vektorort 3",pflaeche.vektorort(3));
                                                                d->auslesen(L"Konstruktionsparameter",L"Vektorvektor 0",pflaeche.vektorvektor(0));
                                                                d->auslesen(L"Konstruktionsparameter",L"Vektorvektor 1",pflaeche.vektorvektor(1));
                                                                d->auslesen(L"Konstruktionsparameter",L"Vektorvektor 2",pflaeche.vektorvektor(2));
                                                                d->auslesen(L"Konstruktionsparameter",L"Vektorvektor 3",pflaeche.vektorvektor(3));
                                                                d->auslesen(L"Konstruktionsparameter",L"Texturkoordinaten Skalierung",ptclength);
                                                                d->auslesen(L"Konstruktionsparameter",L"Geometrische Auflösung",presolution);
                                                                d->auslesen(L"Konstruktionsparameter",L"Geometrische Auflösungsskalierung",sk);
                                                                aufloesungsskalierung(sk);
                                                                d->auslesen(L"Konstruktionsparameter",L"Farbe",f);
                                                                farbe(f);
                                                               // _zeichenkette<char> k="ni";
                                                               // if(standardtextur()) d->einhaengen(L"Konstruktionsparameter",L"Textur",standardtextur()->name()); else d->einhaengen(L"Konstruktionsparameter",L"Textur",k);
};

//******************************************************************************************************************************************************************************************************
//                                                              G E O M E T R I E Q U A D E R
//******************************************************************************************************************************************************************************************************
_geometriequader::_geometriequader(_listebasis<_geometrie >*lg,_vektor3<_tg> p,_tg w0,_tg w1,_tg w2,_textur<_tb>*tex):_geometrie(lg,p,tex){
                                                                presolution.setzen(1,1,1);
                                                                laenge(w0,w1,w2);
                                                                name("box");
                                                                ptclength.setzen(1,1,1);
};
 
_geometriequader::_geometriequader(_listebasis<_geometrie >*lg,_vektor3<_tg> p,_vektor3<_tg> vx,_vektor3<_tg> vy,_vektor3<_tg> vz,_textur<_tb>*tex):_geometrie(lg,p,vx,vy,vz,tex){
                                                                presolution.setzen(1,1,1);
                                                                name("box");
                                                                ptclength.setzen(1,1,1);
};
 
_geometriequader::~_geometriequader(){
};

void _geometriequader::laenge(_tg w0,_tg w1,_tg w2){
                                                                _vektor3<_tg> vx;
                                                                _vektor3<_tg> vy;
                                                                _vektor3<_tg> vz;
                                                                //-----------------
                                                                vx.setzen(w0,0,0);
                                                                vy.setzen(0,w1,0);
                                                                vz.setzen(0,0,w2);
                                                                vektor(vx,vy,vz);
};

void _geometriequader::aufloesung(_vektor<unsigned int> r){
                                                                if(r[0]<1) r.setzenkomponente(0,1);
                                                                if(r[1]<1) r.setzenkomponente(1,1);
                                                                if(r[2]<1) r.setzenkomponente(2,1);
                                                                presolution=r;
};
 
_netz* _geometriequader::erzeugen(){
                                                                unsigned int rx;
                                                                unsigned int ry;
                                                                unsigned int rz;
                                                                _liste<_schweisskante > lwebot;
                                                                _liste<_schweisskante > lwetop;
                                                                _liste<_schweisskante > lwefro;
                                                                _liste<_schweisskante > lwebac;
                                                                _liste<_schweisskante > lwelef;
                                                                _liste<_schweisskante > lwerig;
                                                                _liste<_schweisskante > lall;
                                                                _vektor3<_tg> pvx;
                                                                _vektor3<_tg> pvy;
                                                                _vektor3<_tg> pvz;
                                                                _vektor3<_tg> a;
                                                                _vektor3<_tg> b;
                                                                _vektor3<_tg> o;
                                                                _netz*netz;
                                                                _polygon*poly;
                                                                //---------------------------------------
                                                                netz=new _netz();
                                                                pvx=vektor(0);
                                                                pvy=vektor(1);
                                                                pvz=vektor(2);
                                                                rx=(unsigned int)(_tg(presolution[0])*aufloesungsskalierung());
                                                                ry=(unsigned int)(_tg(presolution[1])*aufloesungsskalierung());
                                                                rz=(unsigned int)(_tg(presolution[2])*aufloesungsskalierung());
                                                                //-------------------------- BOT -----------------------------
                                                                o.setzen(0,0,0);
                                                                a=pvx;
                                                                b=pvz;
                                                                poly=erzeugennetz(netz,o,a,b,rx,rz,&lwebot);
                                                                netz->markierungpolygon(poly,rx*rz,1);
                                                                
                                                                //-------------------------- TOP -----------------------------
                                                                o=pvy;
                                                                a=pvx;
                                                                b=pvz;
                                                                poly=erzeugennetz(netz,o,a,b,rx,rz,&lwetop);
                                                                //-------------------------- LEF -----------------------------
                                                                o.setzen(0,0,0);
                                                                a=pvy;
                                                                b=pvz;
                                                                poly=erzeugennetz(netz,o,a,b,ry,rz,&lwelef);
                                                                //-------------------------- RIG -----------------------------
                                                                o=pvx;
                                                                a=pvy;
                                                                b=pvz;
                                                                poly=erzeugennetz(netz,o,a,b,ry,rz,&lwerig);
                                                                netz->markierungpolygon(poly,ry*rz,1);
                                                                //-------------------------- FRO -----------------------------
                                                                o.setzen(0,0,0);
                                                                a=pvx;
                                                                b=pvy;
                                                                erzeugennetz(netz,o,a,b,rx,ry,&lwefro);
                                                                //-------------------------- BAC -----------------------------
                                                                o=pvz;
                                                                a=pvx;
                                                                b=pvy;
                                                                poly=erzeugennetz(netz,o,a,b,rx,ry,&lwebac);
                                                                netz->markierungpolygon(poly,rx*ry,1);
                                                                //-------------------------- WELD ----------------------------
                                                                duplizieren(&lwebot,&lall);
                                                                duplizieren(&lwetop,&lall);
                                                                duplizieren(&lwerig,&lall);
                                                                duplizieren(&lwelef,&lall);
                                                                duplizieren(&lwefro,&lall);
                                                                duplizieren(&lwebac,&lall);
                                                                verschweissen(netz,lwebot[0],lwefro[0],&lall);  
                                                                verschweissen(netz,lwebot[1],lwerig[3],&lall);
                                                                verschweissen(netz,lwebot[2],lwebac[0],&lall);
                                                                verschweissen(netz,lwebot[3],lwelef[3],&lall);
                                                                verschweissen(netz,lwetop[0],lwefro[2],&lall);
                                                                verschweissen(netz,lwetop[1],lwerig[1],&lall);
                                                                verschweissen(netz,lwetop[2],lwebac[2],&lall);
                                                                verschweissen(netz,lwetop[3],lwelef[1],&lall);
                                                                verschweissen(netz,lwebac[3],lwelef[2],&lall);
                                                                verschweissen(netz,lwefro[1],lwerig[0],&lall);
                                                                verschweissen(netz,lwerig[2],lwebac[1],&lall);
                                                                verschweissen(netz,lwelef[0],lwefro[3],&lall);
                                                                if(pruefenausrichtung()) {
                                                                 if(netz->anfang(poly))do{
                                                                  poly->invertieren();
                                                                 }while(netz->naechstes(poly));
                                                                };//netz->invertierenausrichtung();
                                                                netz->aktualisieren(); 
                                                                lall.aushaengen();
                                                                lwebot.loeschen();
                                                                lwetop.loeschen();
                                                                lwefro.loeschen();
                                                                lwebac.loeschen();
                                                                lwelef.loeschen();
                                                                lwerig.loeschen();
                                                                netz->farbe(farbe());
                                                                netz->farbeverbinder(farbe());
                                                                
                                                                if(standardtextur()) erzeugenstandardtexturkoordinaten(netz);
                                                                if(netz->anfang(poly))do{
                                                                 if(poly->markierung()==1){
                                                                  poly->markierung(0);
                                                                  poly->invertieren();
                                                                 };
                                                                }while(netz->naechstes(poly));
                                                                netz->verschiebenvertex(ort());
                                                                return(netz);
};
 
void _geometriequader::erzeugenstandardtexturkoordinaten(_netz*netz){
                                                                unsigned int rx;
                                                                unsigned int ry;
                                                                unsigned int rz;
                                                                _polygon*poly;
                                                                _vektor2<_tg> o;
                                                                _vektor2<_tg> a;
                                                                _vektor2<_tg> b;
                                                                //-------------------
                                                                rx=(unsigned int)(_tg(presolution[0])*aufloesungsskalierung());
                                                                ry=(unsigned int)(_tg(presolution[1])*aufloesungsskalierung());
                                                                rz=(unsigned int)(_tg(presolution[2])*aufloesungsskalierung());
                                                                //i=0;
                                                                if(netz->anfang(poly)){
                                                                 o.setzen(0,0);
                                                                // a.setzen(10,0);
                                                                // b.setzen(0,1);
                                                                 a.setzen(1*ptclength[0],0);
                                                                 b.setzen(0,1*ptclength[2]);
                                                                 poly=erzeugentexturkoordinatennetz(poly,o,a,b,rx,rz);
                                                                 poly=erzeugentexturkoordinatennetz(poly,o,a,b,rx,rz);
                                                                 a.setzen(0,1*ptclength[1]);
                                                                 b.setzen(1*ptclength[2],0);
                                                                 poly=erzeugentexturkoordinatennetz(poly,o,a,b,ry,rz);
                                                                 poly=erzeugentexturkoordinatennetz(poly,o,a,b,ry,rz);
                                                                 a.setzen(1*ptclength[0],0);
                                                                 b.setzen(0,1*ptclength[1]);
                                                                 poly=erzeugentexturkoordinatennetz(poly,o,a,b,rx,ry);
                                                                 poly=erzeugentexturkoordinatennetz(poly,o,a,b,rx,ry);
                                                                };
                                                                
};
 
void _geometriequader::texturkoordinatenlaenge(const _tg lx,const _tg ly,const _tg lz){
                                                                ptclength.setzen(lx,ly,lz);
};                                                                
void _geometriequader::einhaengendialog(_dynamischerdialog*d){
                                                                d->editierbar(this);
                                                                d->neusetzen(L"Quader erzeugen");
                                                                
                                                                d->einhaengen(L"Konstruktionsparameter",L"Position",ort());
                                                                d->einhaengen(L"Konstruktionsparameter",L"Vektor Achse 0",vektor(0));
                                                                d->einhaengen(L"Konstruktionsparameter",L"Vektor Achse 1",vektor(1));
                                                                d->einhaengen(L"Konstruktionsparameter",L"Vektor Achse 2",vektor(2));
                                                                d->einhaengen(L"Konstruktionsparameter",L"Texturkoordinaten Skalierung",ptclength);
                                                                d->einhaengen(L"Konstruktionsparameter",L"Geometrische Auflösung",presolution);
                                                                d->einhaengen(L"Konstruktionsparameter",L"Geometrische Auflösungsskalierung",aufloesungsskalierung());
                                                                d->einhaengen(L"Konstruktionsparameter",L"Farbe",farbe());
                                                                _zeichenkette<char> k="ni";
                                                                if(standardtextur()) d->einhaengen(L"Konstruktionsparameter",L"Textur",standardtextur()->name()); else d->einhaengen(L"Konstruktionsparameter",L"Textur",k);
                                                               
                                                                
};
void _geometriequader::auslesendialog(_dynamischerdialog*d){
                                                                _vektor3<_tg> v,v0,v1,v2;
                                                                _vektor4<_to> f;
                                                                _tg sk;
                                                                d->auslesen(L"Konstruktionsparameter",L"Position",v);
                                                                ort(v);
                                                                d->auslesen(L"Konstruktionsparameter",L"Vektor Achse 0",v0);
                                                                d->auslesen(L"Konstruktionsparameter",L"Vektor Achse 1",v1);
                                                                d->auslesen(L"Konstruktionsparameter",L"Vektor Achse 2",v2);
                                                                vektor(v0,v1,v2);
                                                                d->auslesen(L"Konstruktionsparameter",L"Texturkoordinaten Skalierung",ptclength);
                                                                d->auslesen(L"Konstruktionsparameter",L"Geometrische Auflösung",presolution);
                                                                d->auslesen(L"Konstruktionsparameter",L"Geometrische Auflösungsskalierung",sk);
                                                                aufloesungsskalierung(sk);
                                                                d->auslesen(L"Konstruktionsparameter",L"Farbe",f);
                                                                farbe(f);
                                                               // _zeichenkette<char> k="ni";
                                                               // if(standardtextur()) d->einhaengen(L"Konstruktionsparameter",L"Textur",standardtextur()->name()); else d->einhaengen(L"Konstruktionsparameter",L"Textur",k);
};

//******************************************************************************************************************************************************************************************************
//                                                              G E O M E T R I E Z Y L I N D E R 
//******************************************************************************************************************************************************************************************************
_geometriezylinder::_geometriezylinder(_listebasis<_geometrie >*lg,_vektor3<_tg> loc,_vektor3<_tg> radx,_vektor3<_tg> vec,_textur<_tb>*tex):_geometrie(lg,loc,radx,vec,radx,tex),presolution(2){
                                                                //L->schreiben("geometrycylinder:vektor rax: ",radx);
                                                                radiussingle(radx);
                                                                presolution.setzen(6,1);
                                                                name("Zylinder");
                                                                ptclength.setzen(1,1,1,1);
                                                                ptcoffset.setzen(0,0,0,0);
                                                                poffen=false;
};
 
_geometriezylinder::_geometriezylinder(_listebasis<_geometrie >*lg,_vektor3<_tg> loc,_vektor3<_tg> radx,_vektor3<_tg> vec,_vektor3<_tg> radz,_textur<_tb>*tex):_geometrie(lg,loc,radx,vec,radz,tex),presolution(2){
                                                                //_vektor3<_tg> rad;
                                                                //rad.setzen(radx,0,0);
                                                                presolution.setzen(6,1);
                                                                //radiussingle(radx);
                                                                name("Zylinder");
                                                                ptclength.setzen(1,1,1,1);
                                                                ptcoffset.setzen(0,0,0,0);
                                                                poffen=false;

};
 
_geometriezylinder::~_geometriezylinder(){
};
 
void _geometriezylinder::vektor(const _vektor3<_tg> v){
                                                                _geometrie::vektor(1,v);
};
 
_vektor3<_tg> _geometriezylinder::vektor() const{
                                                                return(_geometrie::vektor(1));
};
void _geometriezylinder::offen(const bool b){
																poffen= b;
};
bool _geometriezylinder::offen()const{
																return(poffen);
};

 
void _geometriezylinder::radiussingle(const _vektor3<_tg> rx){
                                                                _vektor3<_tg> rz;
                                                                //----------------
                                                                rz=_geometrie::vektor(1) % rx;
                                                                rz.normalisieren();
                                                                rz*=rx.laenge();
                                                                //L->schreiben("geometrycylinder:vektor rx : ",rx);
                                                                //L->schreiben("geometrycylinder:vektor ry : ",_geometrie::vektor(1));
                                                                //L->schreiben("geometrycylinder:vektor rz : ",rz);
                                                                _geometrie::vektor(rx,_geometrie::vektor(1),rz);
};
 
void _geometriezylinder::radius(const _vektor3<_tg> rx,const _vektor3<_tg> rz){
                                                                _geometrie::vektor(rx,_geometrie::vektor(1),rz);
};
 
_vektor3<_tg> _geometriezylinder::radius(const unsigned int i) const{
                                                                if(i==0) return(_geometrie::vektor(0)); else return(_geometrie::vektor(2));
};
 
_netz* _geometriezylinder::erzeugen(){
                                                                unsigned int rx;
                                                                unsigned int ry;
                                                                _liste<_schweisskante > lwetub;
                                                                _liste<_schweisskante > lwedis;
                                                                _liste<_schweisskante > lall;
                                                                _vektor3<_tg> o;
                                                                _netz*netz;
                                                                _polygon*poly;
                                                                //---------------------------------------
                                                                netz=new _netz();
                                                                rx=(unsigned int)(_tg(presolution[0])*aufloesungsskalierung());
                                                                ry=(unsigned int)(_tg(presolution[1])*aufloesungsskalierung());
                                                                //-------------------------- tube -----------------------------
                                                                o.setzen(0,0,0);
                                                                poly=erzeugenrohr(netz,o,radius(0),vektor(),radius(1),rx,ry,&lwetub);
                                                                //-------------------------- discs ----------------------------
                                                                if(!poffen){
                                                                 o.setzen(0,0,0);
                                                                 poly=erzeugenscheibe(netz,o,radius(0),radius(1),rx,&lwedis);
                                                                 netz->invertierenausrichtung(poly,1);
                                                                 o=vektor();
                                                                 poly=erzeugenscheibe(netz,o,radius(0),radius(1),rx,&lwedis);
                                                                 //-------------------------- WELD -----------------------------
                                                                 duplizieren(&lwetub,&lall);
                                                                 duplizieren(&lwedis,&lall);
                                                                 verschweissen(netz,lwetub[0],lwedis[0],&lall);
                                                                 verschweissen(netz,lwetub[1],lwedis[1],&lall);
                                                                };
                                                                if(pruefenausrichtung()) {
                                                                 if(netz->anfang(poly))do{
                                                                  poly->invertieren();
                                                                 }while(netz->naechstes(poly));
                                                                };
                                                                //if(pruefenausrichtung()) netz->invertierenausrichtung();
                                                                netz->aktualisieren(); 
                                                                lall.aushaengen();
                                                                lwetub.loeschen();
                                                                lwedis.loeschen();
                                                                netz->farbe(farbe());
                                                                netz->farbeverbinder(farbe());
                                                                if(standardtextur()) erzeugenstandardtexturkoordinaten(netz);
                                                                netz->verschiebenvertex(ort());
                                                                return(netz);
};
 
void _geometriezylinder::erzeugenstandardtexturkoordinaten(_netz*netz){
                                                                unsigned int rx;
                                                                unsigned int ry;
                                                                //unsigned int rz;
                                                                //unsigned int rw;
                                                                _polygon*poly;
                                                                _vektor2<_tg> o;
                                                                _vektor2<_tg> a;
                                                                _vektor2<_tg> b;
                                                                //-------------------
                                                                rx=(unsigned int)(_tg(presolution[0])*aufloesungsskalierung());
                                                                ry=(unsigned int)(_tg(presolution[1])*aufloesungsskalierung());
                                                            //    rz=(unsigned int)(_tg(presolution[2])*aufloesungsskalierung());
                                                                //i=0;
                                                                if(netz->anfang(poly)){
                                                                 o.setzen(ptcoffset[0],ptcoffset[1]);
                                                                 a.setzen(1*ptclength[0],0);
                                                                 b.setzen(0,1*ptclength[1]);
                                                                 poly=erzeugentexturkoordinatennetz(poly,o,a,b,rx,ry);
                                                                 if(!poffen){
                                                                  o.setzen(ptcoffset[2],ptcoffset[3]);
                                                                  a.setzen(1*ptclength[2],0);
                                                                  b.setzen(0,1*ptclength[3]);
                                                                  poly=erzeugentexturkoordinatenscheibe(poly,o,a,b,rx);
                                                                  poly=erzeugentexturkoordinatenscheibe(poly,o,a,b,rx);
                                                                 };

                                                                 
                                                                 
                                                                 /*poly=erzeugentexturkoordinatennetz(poly,o,a,b,rx,rz);
                                                                 a.setzen(0,1*ptclength[1]);
                                                                 b.setzen(1*ptclength[2],0);
                                                                 poly=erzeugentexturkoordinatennetz(poly,o,a,b,ry,rz);
                                                                 poly=erzeugentexturkoordinatennetz(poly,o,a,b,ry,rz);
                                                                 a.setzen(1*ptclength[0],0);
                                                                 b.setzen(0,1*ptclength[1]);
                                                                 poly=erzeugentexturkoordinatennetz(poly,o,a,b,rx,ry);
                                                                 poly=erzeugentexturkoordinatennetz(poly,o,a,b,rx,ry);*/
                                                                };
                                                                
                                                                
};

void _geometriezylinder::aufloesung(_vektor<unsigned int> r){
                                                                if(r[0]<3) r.setzenkomponente(0,3);
                                                                if(r[1]<1) r.setzenkomponente(1,1);
                                                                presolution=r;
};
void _geometriezylinder::aufloesung(unsigned int ax,unsigned int ay){
																if(ax==0) ax=1;
																if(ay==0) ay=1;
																presolution=_vektor<unsigned int>(ax,ay,1);
};
void _geometriezylinder::texturkoodinatenverschiebung(const _tg ox,const _tg oy,const _tg oz,const _tg ow){
                                                                ptcoffset.setzen(ox,oy,oz,ow);
};
void _geometriezylinder::texturkoordinatenlaenge(const _tg lx,const _tg ly,const _tg lz,const _tg lw){
                                                                ptclength.setzen(lx,ly,lz,lw);
};       
void _geometriezylinder::texturkoordinatenlaenge(const _tg lx,const _tg ly,const _tg lz){
                                                                ptclength.setzen(lx,ly,lz,lz);
};       
void _geometriezylinder::einhaengendialog(_dynamischerdialog*d){
                                                                d->editierbar(this);
                                                                d->neusetzen(L"Zylinder erzeugen");
                                                                
                                                                d->einhaengen(L"Konstruktionsparameter",L"Position",ort());
                                                                d->einhaengen(L"Konstruktionsparameter",L"Achse",vektor(1));
                                                                d->einhaengen(L"Konstruktionsparameter",L"Radiusvektor 0",radius(0));
                                                                d->einhaengen(L"Konstruktionsparameter",L"Radiusvektor 1",radius(1));
                                                                d->einhaengen(L"Konstruktionsparameter",L"Texturkoordinaten Skalierung (Mantel (x,y),Scheibe (x,y))",ptclength);
                                                                d->einhaengen(L"Konstruktionsparameter",L"Texturkoordinaten Verschiebung (Mantel (x,y),Scheibe (x,y))",ptcoffset);
                                                                d->einhaengen(L"Konstruktionsparameter",L"Geometrische Auflösung",presolution);
                                                                d->einhaengen(L"Konstruktionsparameter",L"Geometrische Auflösungsskalierung",aufloesungsskalierung());
                                                                d->einhaengen(L"Konstruktionsparameter",L"Farbe",farbe());
                                                                _zeichenkette<char> k="ni";
                                                                if(standardtextur()) d->einhaengen(L"Konstruktionsparameter",L"Textur",standardtextur()->name()); else d->einhaengen(L"Konstruktionsparameter",L"Textur",k);
                                                               
                                                                
};
void _geometriezylinder::auslesendialog(_dynamischerdialog*d){
                                                                _vektor3<_tg> v,v0,v1,v2;
                                                                _vektor4<_to> f;
                                                                _tg sk;
                                                                d->auslesen(L"Konstruktionsparameter",L"Position",v);
                                                                ort(v);
                                                                d->auslesen(L"Konstruktionsparameter",L"Achse",v1);
                                                                d->auslesen(L"Konstruktionsparameter",L"Radiusvektor 0",v0);
                                                                d->auslesen(L"Konstruktionsparameter",L"Radiusvektor 1",v2);
                                                                vektor(v0,v1,v2);
                                                                d->auslesen(L"Konstruktionsparameter",L"Texturkoordinaten Skalierung (Mantel (x,y),Scheibe (x,y))",ptclength);
                                                                d->auslesen(L"Konstruktionsparameter",L"Texturkoordinaten Verschiebung (Mantel (x,y),Scheibe (x,y))",ptcoffset);
                                                                d->auslesen(L"Konstruktionsparameter",L"Geometrische Auflösung",presolution);
                                                                d->auslesen(L"Konstruktionsparameter",L"Geometrische Auflösungsskalierung",sk);
                                                                aufloesungsskalierung(sk);
                                                                d->auslesen(L"Konstruktionsparameter",L"Farbe",f);
                                                                farbe(f);
                                                               // _zeichenkette<char> k="ni";
                                                               // if(standardtextur()) d->einhaengen(L"Konstruktionsparameter",L"Textur",standardtextur()->name()); else d->einhaengen(L"Konstruktionsparameter",L"Textur",k);
};                                                         
//******************************************************************************************************************************************************************************************************
//                                                              G E O M E T R I E K O N U S
//******************************************************************************************************************************************************************************************************
_geometriekonus::_geometriekonus(_listebasis<_geometrie >*lg,_vektor3<_tg> loc,_vektor3<_tg> radx,_vektor3<_tg> vec,_vektor3<_tg> radz,_textur<_tb>*tex):_geometrie(lg,loc,radx,vec,radz,tex),presolution(2){
                                                                //_vektor3<_tg> rad;
                                                                //rad.setzen(radx,0,0);
                                                                presolution.setzen(6,1);
                                                                //radiussingle(radx);
                                                                name("konus");
                                                                ptclength.setzen(1,1,1,1);
                                                                ptcoffset.setzen(0,0,0,0);
};
_geometriekonus::~_geometriekonus(){
};
 
void _geometriekonus::vektor(const _vektor3<_tg> v){
                                                                _geometrie::vektor(1,v);
};
 
_vektor3<_tg> _geometriekonus::vektor() const{
                                                                return(_geometrie::vektor(1));
};
 
void _geometriekonus::radiussingle(const _vektor3<_tg> rx){
                                                                _vektor3<_tg> rz;
                                                                //----------------
                                                                rz=_geometrie::vektor(1) % rx;
                                                                rz.normalisieren();
                                                                rz*=rx.laenge();
                                                                //L->schreiben("geometrycylinder:vektor rx : ",rx);
                                                                //L->schreiben("geometrycylinder:vektor ry : ",_geometrie::vektor(1));
                                                                //L->schreiben("geometrycylinder:vektor rz : ",rz);
                                                                _geometrie::vektor(rx,_geometrie::vektor(1),rz);
};
 
void _geometriekonus::radius(const _vektor3<_tg> rx,const _vektor3<_tg> rz){
                                                                _geometrie::vektor(rx,_geometrie::vektor(1),rz);
};
 
_vektor3<_tg> _geometriekonus::radius(const unsigned int i) const{
                                                                if(i==0) return(_geometrie::vektor(0)); else return(_geometrie::vektor(2));
};
 
_netz* _geometriekonus::erzeugen(){
                                                                unsigned int rx;
                                                                unsigned int ry;
                                                                _liste<_schweisskante > lwetub;
                                                                _liste<_schweisskante > lwedis;
                                                                _liste<_schweisskante > lall;
                                                                _vektor3<_tg> o;
                                                                _netz*netz;
                                                                _polygon*poly;
                                                                //---------------------------------------
                                                                netz=new _netz();
                                                                rx=(unsigned int)(_tg(presolution[0])*aufloesungsskalierung());
                                                                ry=(unsigned int)(_tg(presolution[1])*aufloesungsskalierung());
                                                                //-------------------------- tube -----------------------------
                                                                o.setzen(0,0,0);
                                                                poly=erzeugenkonus(netz,o,radius(0),vektor(),radius(1),rx,ry,&lwetub);
                                                                //-------------------------- discs ----------------------------
                                                                o.setzen(0,0,0);
                                                                poly=erzeugenscheibe(netz,o,radius(0),radius(1),rx,&lwedis);
                                                                netz->invertierenausrichtung(poly,1);
                                                                //-------------------------- WELD -----------------------------
                                                                duplizieren(&lwetub,&lall);
                                                                duplizieren(&lwedis,&lall);
                                                                verschweissen(netz,lwetub[0],lwedis[0],&lall);
                                                                if(pruefenausrichtung()) {
                                                                 if(netz->anfang(poly))do{
                                                                  poly->invertieren();
                                                                 }while(netz->naechstes(poly));
                                                                };
                                                                //if(pruefenausrichtung()) netz->invertierenausrichtung();
                                                                netz->aktualisieren(); 
                                                                lall.aushaengen();
                                                                lwetub.loeschen();
                                                                lwedis.loeschen();
                                                                netz->farbe(farbe());
                                                                netz->farbeverbinder(farbe());
                                                                if(standardtextur()) erzeugenstandardtexturkoordinaten(netz);
                                                                netz->verschiebenvertex(ort());
                                                                return(netz);
};
 
void _geometriekonus::erzeugenstandardtexturkoordinaten(_netz*netz){
                                                                unsigned int rx;
                                                                unsigned int ry;
                                                                //unsigned int rz;
                                                                //unsigned int rw;
                                                                _polygon*poly;
                                                                _vektor2<_tg> o;
                                                                _vektor2<_tg> a;
                                                                _vektor2<_tg> b;
                                                                //-------------------
                                                                rx=(unsigned int)(_tg(presolution[0])*aufloesungsskalierung());
                                                                ry=(unsigned int)(_tg(presolution[1])*aufloesungsskalierung());
                                                            //    rz=(unsigned int)(_tg(presolution[2])*aufloesungsskalierung());
                                                                //i=0;
                                                                if(netz->anfang(poly)){
                                                                 o.setzen(ptcoffset[0],ptcoffset[1]);
                                                                 a.setzen(1*ptclength[0],0);
                                                                 b.setzen(0,1*ptclength[1]);
                                                                 poly=erzeugentexturkoordinatenkonus(poly,o,a,b,rx,ry);
                                                                 o.setzen(ptcoffset[2],ptcoffset[3]);
                                                                 a.setzen(1*ptclength[2],0);
                                                                 b.setzen(0,1*ptclength[3]);
                                                                 poly=erzeugentexturkoordinatenscheibe(poly,o,a,b,rx);
                                                             //    poly=erzeugentexturkoordinatenscheibe(poly,o,a,b,rx);

                                                                 
                                                                 
                                                                 /*poly=erzeugentexturkoordinatennetz(poly,o,a,b,rx,rz);
                                                                 a.setzen(0,1*ptclength[1]);
                                                                 b.setzen(1*ptclength[2],0);
                                                                 poly=erzeugentexturkoordinatennetz(poly,o,a,b,ry,rz);
                                                                 poly=erzeugentexturkoordinatennetz(poly,o,a,b,ry,rz);
                                                                 a.setzen(1*ptclength[0],0);
                                                                 b.setzen(0,1*ptclength[1]);
                                                                 poly=erzeugentexturkoordinatennetz(poly,o,a,b,rx,ry);
                                                                 poly=erzeugentexturkoordinatennetz(poly,o,a,b,rx,ry);*/
                                                                };
                                                                
                                                                
};

void _geometriekonus::aufloesung(unsigned int rx,unsigned int ry){
                                                                if(rx<3) rx=3;
                                                                if(ry<1) ry=1;
                                                                presolution.setzen(rx,ry);
};
void _geometriekonus::texturkoodinatenverschiebung(const _tg ox,const _tg oy,const _tg oz,const _tg ow){
                                                                ptcoffset.setzen(ox,oy,oz,ow);
};
void _geometriekonus::texturkoordinatenlaenge(const _tg lx,const _tg ly,const _tg lz,const _tg lw){
                                                                ptclength.setzen(lx,ly,lz,lw);
};       
void _geometriekonus::texturkoordinatenlaenge(const _tg lx,const _tg ly,const _tg lz){
                                                                ptclength.setzen(lx,ly,lz,lz);
};       
void _geometriekonus::einhaengendialog(_dynamischerdialog*d){
                                                                d->editierbar(this);
                                                                d->neusetzen(L"Konus erzeugen");
                                                                d->einhaengen(L"Konstruktionsparameter",L"Position",ort());
                                                                d->einhaengen(L"Konstruktionsparameter",L"Achse",vektor(1));
                                                                d->einhaengen(L"Konstruktionsparameter",L"Radiusvektor 0",radius(0));
                                                                d->einhaengen(L"Konstruktionsparameter",L"Radiusvektor 1",radius(1));
                                                                d->einhaengen(L"Konstruktionsparameter",L"Texturkoordinaten Skalierung (Mantel (x,y),Scheibe (x,y))",ptclength);
                                                                d->einhaengen(L"Konstruktionsparameter",L"Texturkoordinaten Verschiebung (Mantel (x,y),Scheibe (x,y))",ptcoffset);
                                                                d->einhaengen(L"Konstruktionsparameter",L"Geometrische Auflösung",presolution);
                                                                d->einhaengen(L"Konstruktionsparameter",L"Geometrische Auflösungsskalierung",aufloesungsskalierung());
                                                                d->einhaengen(L"Konstruktionsparameter",L"Farbe",farbe());
                                                                _zeichenkette<char> k="ni";
                                                                if(standardtextur()) d->einhaengen(L"Konstruktionsparameter",L"Textur",standardtextur()->name()); else d->einhaengen(L"Konstruktionsparameter",L"Textur",k);
};
void _geometriekonus::auslesendialog(_dynamischerdialog*d){
                                                                _vektor3<_tg> v,v0,v1,v2;
                                                                _vektor4<_to> f;
                                                                _tg sk;
                                                                d->auslesen(L"Konstruktionsparameter",L"Position",v);
                                                                ort(v);
                                                                d->auslesen(L"Konstruktionsparameter",L"Achse",v1);
                                                                d->auslesen(L"Konstruktionsparameter",L"Radiusvektor 0",v0);
                                                                d->auslesen(L"Konstruktionsparameter",L"Radiusvektor 1",v2);
                                                                vektor(v0,v1,v2);
                                                                d->auslesen(L"Konstruktionsparameter",L"Texturkoordinaten Skalierung (Mantel (x,y),Scheibe (x,y))",ptclength);
                                                                d->auslesen(L"Konstruktionsparameter",L"Texturkoordinaten Verschiebung (Mantel (x,y),Scheibe (x,y))",ptcoffset);
                                                                d->auslesen(L"Konstruktionsparameter",L"Geometrische Auflösung",presolution);
                                                                d->auslesen(L"Konstruktionsparameter",L"Geometrische Auflösungsskalierung",sk);
                                                                aufloesungsskalierung(sk);
                                                                d->auslesen(L"Konstruktionsparameter",L"Farbe",f);
                                                                farbe(f);
                                                               // _zeichenkette<char> k="ni";
                                                               // if(standardtextur()) d->einhaengen(L"Konstruktionsparameter",L"Textur",standardtextur()->name()); else d->einhaengen(L"Konstruktionsparameter",L"Textur",k);
};   
//******************************************************************************************************************************************************************************************************
//                                                              G E O M E T R I E T O R U S 
//******************************************************************************************************************************************************************************************************
_geometrietorus::_geometrietorus(_listebasis<_geometrie >*lg,const _vektor3<_tg>&o,const _vektor3<_tg>&v0,const _vektor3<_tg>&v1,const _vektor3<_tg>&v2,const _tg r0,const _tg r1,_textur<_tb>*tex):_geometrie(lg,o,v0,v1,v2,tex),presolution(2){
                                                                pradius[0]=r0;
                                                                pradius[1]=r1;
                                                                panteil0start=0;//sek
                                                                panteil0ende=1;
                                                                panteil1start=0;//prim
                                                                panteil1ende=1;
                                                                presolution.setzen(6,6);
                                                                name("torus");
                                                                ptclength.setzen(1,1);
                                                                ptcoffset.setzen(0,0);
};
_geometrietorus::~_geometrietorus(){
};
void _geometrietorus::radius(const _tg r){
                                                                pradius[0]=pradius[1]=fabs(r);
};
 
void _geometrietorus::radius(const unsigned int i,const _tg r){
                                                                pradius[i]=fabs(r);
};
_tg _geometrietorus::radius(const unsigned int i)const{
                                                                if(i==0) return(pradius[0]); else return(pradius[1]);
};
_netz* _geometrietorus::erzeugen(){
                                                                unsigned int rx;
                                                                unsigned int ry;
                                                                _liste<_schweisskante > lwetub;
                                                                _liste<_schweisskante > lall;
                                                                _vektor3<_tg> o;
                                                                _netz*netz;
                                                                _polygon*poly;
                                                                //---------------------------------------
                                                                netz=new _netz();
                                                                rx=(unsigned int)(_tg(presolution[0])*aufloesungsskalierung());
                                                                ry=(unsigned int)(_tg(presolution[1])*aufloesungsskalierung());
                                                                //-------------------------- roher torus -----------------------------
                                                                o.setzen(0,0,0);
                                                                poly=erzeugentorus(netz,o,vektor(0),vektor(1),vektor(2),pradius[0],pradius[1],panteil0start,panteil0ende,panteil1start,panteil1ende,rx,ry,&lwetub);
                                                                //-------------------------- WELD -----------------------------
                                                                duplizieren(&lwetub,&lall);
                                                                verschweissen(netz,lwetub[0],lwetub[1],&lall);//könnte klappen
                                                                if(standardtextur()) erzeugenstandardtexturkoordinaten(netz);

                                                                if(pruefenausrichtung()==false) {
                                                                 if(netz->anfang(poly))do{
                                                                  poly->invertieren();
                                                                 }while(netz->naechstes(poly));
                                                                };
                                                                netz->aktualisieren(); 
                                                                lall.aushaengen();
                                                                lwetub.loeschen();
                                                                netz->farbe(farbe());
                                                                netz->farbeverbinder(farbe());
                                                                
                                                                netz->verschiebenvertex(ort());
                                                                return(netz);
};
 
void _geometrietorus::erzeugenstandardtexturkoordinaten(_netz*netz){
                                                                unsigned int rx;
                                                                unsigned int ry;
                                                                //unsigned int rz;
                                                                //unsigned int rw;
                                                                _polygon*poly;
                                                                _vektor2<_tg> o;
                                                                _vektor2<_tg> a;
                                                                _vektor2<_tg> b;
                                                                //-------------------
                                                                rx=(unsigned int)(_tg(presolution[0])*aufloesungsskalierung());
                                                                ry=(unsigned int)(_tg(presolution[1])*aufloesungsskalierung());
                                                                if(netz->anfang(poly)){
                                                                 o.setzen(ptcoffset[0],ptcoffset[1]);
                                                                 a.setzen(1*ptclength[0],0);
                                                                 b.setzen(0,1*ptclength[1]);
                                                                 poly=erzeugentexturkoordinatennetz(poly,o,a,b,rx,ry);
                                                                };
};
void _geometrietorus::aufloesung(_vektor<unsigned int> r){
                                                                if(r[0]<3) r.setzenkomponente(0,3);
                                                                if(r[1]<1) r.setzenkomponente(1,1);
                                                                presolution=r;
};
void _geometrietorus::texturkoodinatenverschiebung(const _tg ox,const _tg oy){
                                                                ptcoffset.setzen(ox,oy);
};
void _geometrietorus::texturkoordinatenlaenge(const _tg lx,const _tg ly){
                                                                ptclength.setzen(lx,ly);
};       
void _geometrietorus::einhaengendialog(_dynamischerdialog*d){
                                                                d->editierbar(this);
                                                                d->neusetzen(L"Torus erzeugen");
                                                                
                                                                d->einhaengen(L"Konstruktionsparameter",L"Position",ort());
                                                                d->einhaengen(L"Konstruktionsparameter",L"Vektor Achse 0",vektor(0));
                                                                d->einhaengen(L"Konstruktionsparameter",L"Vektor Achse 1",vektor(1));
                                                                d->einhaengen(L"Konstruktionsparameter",L"Vektor Achse 2",vektor(2));
                                                                d->einhaengen(L"Konstruktionsparameter",L"Radius 0",pradius[0]);
                                                                d->einhaengen(L"Konstruktionsparameter",L"Radius 1",pradius[1]);
                                                                d->einhaengen(L"Konstruktionsparameter",L"Primärer Bogen Start [0..1]",panteil1start);
                                                                d->einhaengen(L"Konstruktionsparameter",L"Primärer Bogen Ende [0..1]",panteil1ende);
                                                                d->einhaengen(L"Konstruktionsparameter",L"Sekundärer Bogen Start [0..1]",panteil0start);
                                                                d->einhaengen(L"Konstruktionsparameter",L"Sekundärer Bogen Ende [0..1]",panteil0ende);
                                                                d->einhaengen(L"Konstruktionsparameter",L"Texturkoordinaten Skalierung",ptclength);
                                                                d->einhaengen(L"Konstruktionsparameter",L"Texturkoordinaten Verschiebung",ptcoffset);
                                                                d->einhaengen(L"Konstruktionsparameter",L"Geometrische Auflösung",presolution);
                                                                d->einhaengen(L"Konstruktionsparameter",L"Geometrische Auflösungsskalierung",aufloesungsskalierung());
                                                                d->einhaengen(L"Konstruktionsparameter",L"Farbe",farbe());
                                                                _zeichenkette<char> k="ni";
                                                                if(standardtextur()) d->einhaengen(L"Konstruktionsparameter",L"Textur",standardtextur()->name()); else d->einhaengen(L"Konstruktionsparameter",L"Textur",k);
};
void _geometrietorus::auslesendialog(_dynamischerdialog*d){
                                                                _vektor3<_tg> v,v0,v1,v2;
                                                                _vektor4<_to> f;
                                                                _tg sk;
                                                                d->auslesen(L"Konstruktionsparameter",L"Position",v);
                                                                ort(v);
                                                                d->auslesen(L"Konstruktionsparameter",L"Vektor Achse 0",v0);
                                                                d->auslesen(L"Konstruktionsparameter",L"Vektor Achse 1",v1);
                                                                d->auslesen(L"Konstruktionsparameter",L"Vektor Achse 2",v2);
                                                                vektor(v0,v1,v2);
                                                                d->auslesen(L"Konstruktionsparameter",L"Radius 0",pradius[0]);
                                                                d->auslesen(L"Konstruktionsparameter",L"Radius 1",pradius[1]);
                                                                d->auslesen(L"Konstruktionsparameter",L"Primärer Bogen Start [0..1]",panteil1start);
                                                                d->auslesen(L"Konstruktionsparameter",L"Primärer Bogen Ende [0..1]",panteil1ende);
                                                                d->auslesen(L"Konstruktionsparameter",L"Sekundärer Bogen Start [0..1]",panteil0start);
                                                                d->auslesen(L"Konstruktionsparameter",L"Sekundärer Bogen Ende [0..1]",panteil0ende);
                                                                d->auslesen(L"Konstruktionsparameter",L"Texturkoordinaten Skalierung",ptclength);
                                                                d->auslesen(L"Konstruktionsparameter",L"Texturkoordinaten Verschiebung",ptcoffset);
                                                                d->auslesen(L"Konstruktionsparameter",L"Geometrische Auflösung",presolution);
                                                                d->auslesen(L"Konstruktionsparameter",L"Geometrische Auflösungsskalierung",sk);
                                                                aufloesungsskalierung(sk);
                                                                d->auslesen(L"Konstruktionsparameter",L"Farbe",f);
                                                                farbe(f);
                                                               // _zeichenkette<char> k="ni";
                                                               // if(standardtextur()) d->einhaengen(L"Konstruktionsparameter",L"Textur",standardtextur()->name()); else d->einhaengen(L"Konstruktionsparameter",L"Textur",k);
};                                                         
//******************************************************************************************************************************************************************************************************
//                                                              G E O M E T R I E K R E U Z D R E I
//******************************************************************************************************************************************************************************************************
 
_geometriekreuzdrei::_geometriekreuzdrei(_listebasis<_geometrie >*lg,_vektor3<_tg> lo,_vektor3<_tg> vx,_vektor3<_tg> vy,_vektor3<_tg> vz,_tg x0,_tg x1,_tg y0,_tg y1,_textur<_tb>*tex):_geometrie(lg,lo,vx,vy,vz,tex){
                                                                presolution.konvertieren(7);
                                                                for(int n=0;n<7;n++) presolution.setzenkomponente(n,1);
                                                                //presolution.setzen(7,1,1,1,1,1,1,1);
                                                                /*if(vx.holendimension()!=3) vx.setzen(vx[0],vx[1],vx[2]);
                                                                if(vy.holendimension()!=3) vy.setzen(vy[0],vy[1],vy[2]);
                                                                if(vz.holendimension()!=3) vz.setzen(vz[0],vz[1],vz[2]);
                                                                vektor0(vx);
                                                                vektor1(vy);
                                                                vektor2(vz);*/
                                                                tile0(x0,x1);
                                                                tile1(y0,y1);
                                                                name("crossbar");
};
 
_geometriekreuzdrei::~_geometriekreuzdrei(){
};

void _geometriekreuzdrei::aufloesung(_vektor<unsigned int> r){
                                                                int i;
                                                                if(r.holendimension()!=7) {
                                                                 r.konvertieren(7);
                                                                 for(int n=0;n<7;n++) r.setzenkomponente(n,r[n]);
                                                                 //r.setzen(7,r[0],r[1],r[2],r[3],r[4],r[5],r[6]);
                                                                };
                                                                for(i=0;i<7;i++) if(r[i]<1) r.setzenkomponente(i,1);
                                                                presolution=r;
};
/*
 
void _geometriekreuzdrei::vektor0(_vektor3<_tg> l){
                                                                if(l.holendimension()!=3) l.setzen(l[0],l[1],l[2]);
                                                                pvx=l;
};
 
void _geometriekreuzdrei::vektor1(_vektor3<_tg> l){
                                                                if(l.holendimension()!=3) l.setzen(l[0],l[1],l[2]);
                                                                pvy=l;
};
 
void _geometriekreuzdrei::vektor2(_vektor3<_tg> l){
                                                                if(l.holendimension()!=3) l.setzen(l[0],l[1],l[2]);
                                                                pvz=l;
};
*/
 
void _geometriekreuzdrei::tile0(_tg x0,_tg x1){
                                                                _tg h;
                                                                if(x0<0) x0=0;
                                                                if(x0>1) x0=1;
                                                                if(x1<0) x1=0;
                                                                if(x1>1) x1=1;
                                                                if(x0>x1) {
                                                                 h=x0;
                                                                 x0=x1;
                                                                 x1=h;
                                                                };
                                                                if(x0==x1){
                                                                 if(x0<0.5){
                                                                  x1+=nahenull*2;
                                                                 }else{
                                                                  x0-=nahenull*2;
                                                                 };
                                                                };
                                                                ptx.setzen(x0,x1);
};
 
void _geometriekreuzdrei::tile1(_tg x0,_tg x1){
                                                                _tg h;
                                                                if(x0<0) x0=0;
                                                                if(x0>1) x0=1;
                                                                if(x1<0) x1=0;
                                                                if(x1>1) x1=1;
                                                                if(x0>x1) {
                                                                 h=x0;
                                                                 x0=x1;
                                                                 x1=h;
                                                                };
                                                                if(x0==x1){
                                                                 if(x0<0.5){
                                                                  x1+=nahenull*2;
                                                                 }else{
                                                                  x0-=nahenull*2;
                                                                 };
                                                                };
                                                                pty.setzen(x0,x1);
};
/*
 
bool _geometriekreuzdrei::pruefenausrichtung()const{
                                                                _vektor3<_tg> h;
                                                                bool ix;
                                                                bool iy;
                                                                bool iz;
                                                                //----------------
                                                                h=pvy%pvz;
                                                                h.normalisieren();
                                                                if((pvx*h)<0) ix=true; else ix=false;
                                                                
                                                                h=pvx%pvz;
                                                                h.normalisieren();
                                                                if((pvy*h)<0) iy=true; else iy=false;
                                                                
                                                                h=pvx%pvy;
                                                                h.normalisieren();
                                                                if((pvz*h)<0) iz=true; else iz=false;
                                                                
                                                                return(not(ix xor iy xor iz));
};
*/                                                                
 
_netz* _geometriekreuzdrei::erzeugen(){
                                                                unsigned int rxl;
                                                                unsigned int rxm;
                                                                unsigned int rxr;
                                                                unsigned int ryd;
                                                                unsigned int rym;
                                                                unsigned int ryu;
                                                                unsigned int rz;
                                                                _liste<_schweisskante > lwefrol;
                                                                _liste<_schweisskante > lwefror;
                                                                _liste<_schweisskante > lwefrou;
                                                                _liste<_schweisskante > lwefrod;
                                                                _liste<_schweisskante > lwefrom;

                                                                _liste<_schweisskante > lwebacl;
                                                                _liste<_schweisskante > lwebacr;
                                                                _liste<_schweisskante > lwebacu;
                                                                _liste<_schweisskante > lwebacd;
                                                                _liste<_schweisskante > lwebacm;
                                                                
                                                                _liste<_schweisskante > lwelefd;
                                                                _liste<_schweisskante > lwelefm;
                                                                _liste<_schweisskante > lwelefu;

                                                                _liste<_schweisskante > lwerigd;
                                                                _liste<_schweisskante > lwerigm;
                                                                _liste<_schweisskante > lwerigu;
                                                                
                                                                _liste<_schweisskante > lwetopl;
                                                                _liste<_schweisskante > lwetopm;
                                                                _liste<_schweisskante > lwetopr;
                                                                
                                                                _liste<_schweisskante > lwebotl;
                                                                _liste<_schweisskante > lwebotm;
                                                                _liste<_schweisskante > lwebotr;
                                                                
                                                                _liste<_schweisskante > lall;
                                                                _vektor3<_tg> a;
                                                                _vektor3<_tg> b;
                                                                _vektor3<_tg> o;
                                                                _netz*netz;
                                                                _polygon*poly;
                                                                _vektor3<_tg> pvx;
                                                                _vektor3<_tg> pvy;
                                                                _vektor3<_tg> pvz;
                                                                //---------------------------------------
                                                                netz=new _netz();
                                                                rxl=(unsigned int)(_tg(presolution[0])*aufloesungsskalierung());
                                                                rxm=(unsigned int)(_tg(presolution[1])*aufloesungsskalierung());
                                                                rxr=(unsigned int)(_tg(presolution[2])*aufloesungsskalierung());
                                                                ryd=(unsigned int)(_tg(presolution[3])*aufloesungsskalierung());
                                                                rym=(unsigned int)(_tg(presolution[4])*aufloesungsskalierung());
                                                                ryu=(unsigned int)(_tg(presolution[5])*aufloesungsskalierung());
                                                                rz=(unsigned int)(_tg(presolution[6])*aufloesungsskalierung());
                                                                pvx=vektor(0);
                                                                pvy=vektor(1);
                                                                pvz=vektor(2);
                                                                //frol
                                                                o=pvy*pty[0];
                                                                a=pvx*ptx[0];
                                                                b=pvy*(pty[1]-pty[0]);
                                                                poly=erzeugennetz(netz,o,a,b,rxl,rym,&lwefrol);
                                                                //from
                                                                o=pvx*ptx[0]+pvy*pty[0];
                                                                a=pvx*(ptx[1]-ptx[0]);
                                                                b=pvy*(pty[1]-pty[0]);
                                                                poly=erzeugennetz(netz,o,a,b,rxm,rym,&lwefrom);
                                                                //fror
                                                                o=pvx*ptx[1]+pvy*pty[0];
                                                                a=pvx*(1-ptx[1]);
                                                                b=pvy*(pty[1]-pty[0]);
                                                                poly=erzeugennetz(netz,o,a,b,rxr,rym,&lwefror);
                                                                //frod
                                                                o=pvx*ptx[0];
                                                                a=pvx*(ptx[1]-ptx[0]);
                                                                b=pvy*pty[0];
                                                                poly=erzeugennetz(netz,o,a,b,rxm,ryd,&lwefrod);
                                                                //frou
                                                                o=pvx*ptx[0]+pvy*pty[1];
                                                                a=pvx*(ptx[1]-ptx[0]);
                                                                b=pvy*(1-pty[1]);
                                                                poly=erzeugennetz(netz,o,a,b,rxm,ryu,&lwefrou);
                                                                
                                                                //bacl
                                                                o=pvy*pty[0]+pvz;
                                                                a=pvx*ptx[0];
                                                                b=pvy*(pty[1]-pty[0]);
                                                                poly=erzeugennetz(netz,o,a,b,rxl,rym,&lwebacl);
                                                                netz->invertierenausrichtung(poly,rxl*rym);
                                                                //bacm
                                                                o=pvx*ptx[0]+pvy*pty[0]+pvz;
                                                                a=pvx*(ptx[1]-ptx[0]);
                                                                b=pvy*(pty[1]-pty[0]);
                                                                poly=erzeugennetz(netz,o,a,b,rxm,rym,&lwebacm);
                                                                netz->invertierenausrichtung(poly,rxm*rym);
                                                                //bacr
                                                                o=pvx*ptx[1]+pvy*pty[0]+pvz;
                                                                a=pvx*(1-ptx[1]);
                                                                b=pvy*(pty[1]-pty[0]);
                                                                poly=erzeugennetz(netz,o,a,b,rxr,rym,&lwebacr);
                                                                netz->invertierenausrichtung(poly,rxr*rym);
                                                                //bacd
                                                                o=pvx*ptx[0]+pvz;
                                                                a=pvx*(ptx[1]-ptx[0]);
                                                                b=pvy*pty[0];
                                                                poly=erzeugennetz(netz,o,a,b,rxm,ryd,&lwebacd);
                                                                netz->invertierenausrichtung(poly,rxm*ryd);
                                                                //bacu
                                                                o=pvx*ptx[0]+pvy*pty[1]+pvz;
                                                                a=pvx*(ptx[1]-ptx[0]);
                                                                b=pvy*(1-pty[1]);
                                                                poly=erzeugennetz(netz,o,a,b,rxm,ryu,&lwebacu);
                                                                netz->invertierenausrichtung(poly,rxm*ryu);
                                                                
                                                                //lefd
                                                                o=pvx*ptx[0];
                                                                a=pvy*pty[0];
                                                                b=pvz;
                                                                poly=erzeugennetz(netz,o,a,b,ryd,rz,&lwelefd);
                                                                //lefm
                                                                o=pvy*pty[0];
                                                                a=pvy*(pty[1]-pty[0]);
                                                                b=pvz;
                                                                poly=erzeugennetz(netz,o,a,b,rym,rz,&lwelefm);
                                                                //lefu
                                                                o=pvx*ptx[0]+pvy*pty[1];
                                                                a=pvy*(1-pty[1]);
                                                                b=pvz;
                                                                poly=erzeugennetz(netz,o,a,b,ryu,rz,&lwelefu);
                                                                
                                                                //rigd
                                                                o=pvx*ptx[1];
                                                                a=pvy*pty[0];
                                                                b=pvz;
                                                                poly=erzeugennetz(netz,o,a,b,ryd,rz,&lwerigd);
                                                                netz->invertierenausrichtung(poly,ryd*rz);
                                                                //rigm
                                                                o=pvx+pvy*pty[0];
                                                                a=pvy*(pty[1]-pty[0]);
                                                                b=pvz;
                                                                poly=erzeugennetz(netz,o,a,b,rym,rz,&lwerigm);
                                                                netz->invertierenausrichtung(poly,rym*rz);
                                                                //rigu
                                                                o=pvx*ptx[1]+pvy*pty[1];
                                                                a=pvy*(1-pty[1]);
                                                                b=pvz;
                                                                poly=erzeugennetz(netz,o,a,b,ryu,rz,&lwerigu);
                                                                netz->invertierenausrichtung(poly,ryu*rz);
                                                                
                                                                //topl
                                                                o=pvy*pty[1];
                                                                a=pvx*ptx[0];
                                                                b=pvz;
                                                                poly=erzeugennetz(netz,o,a,b,rxl,rz,&lwetopl);
                                                                //topm
                                                                o=pvy+pvx*ptx[0];
                                                                a=pvx*(ptx[1]-ptx[0]);
                                                                b=pvz;
                                                                poly=erzeugennetz(netz,o,a,b,rxm,rz,&lwetopm);
                                                                //topr
                                                                o=pvx*ptx[1]+pvy*pty[1];
                                                                a=pvx*(1-ptx[1]);
                                                                b=pvz;
                                                                poly=erzeugennetz(netz,o,a,b,rxr,rz,&lwetopr);
                                                                
                                                                //botl
                                                                o=pvy*pty[0];
                                                                a=pvx*ptx[0];
                                                                b=pvz;
                                                                poly=erzeugennetz(netz,o,a,b,rxl,rz,&lwebotl);
                                                                netz->invertierenausrichtung(poly,rxl*rz);
                                                                //botm
                                                                o=pvx*ptx[0];
                                                                a=pvx*(ptx[1]-ptx[0]);
                                                                b=pvz;
                                                                poly=erzeugennetz(netz,o,a,b,rxm,rz,&lwebotm);
                                                                netz->invertierenausrichtung(poly,rxm*rz);
                                                                //botr
                                                                o=pvx*ptx[1]+pvy*pty[0];
                                                                a=pvx*(1-ptx[1]);
                                                                b=pvz;
                                                                poly=erzeugennetz(netz,o,a,b,rxr,rz,&lwebotr);
                                                                netz->invertierenausrichtung(poly,rxr*rz);
                                                                //-------------------------- WELD ----------------------------
                                                                duplizieren(&lwefrol,&lall);
                                                                duplizieren(&lwefrom,&lall);
                                                                duplizieren(&lwefror,&lall);
                                                                duplizieren(&lwefrod,&lall);
                                                                duplizieren(&lwefrou,&lall);
                                                                duplizieren(&lwebacl,&lall);
                                                                duplizieren(&lwebacm,&lall);
                                                                duplizieren(&lwebacr,&lall);
                                                                duplizieren(&lwebacd,&lall);
                                                                duplizieren(&lwebacu,&lall);
                                                                duplizieren(&lwelefd,&lall);
                                                                duplizieren(&lwelefm,&lall);
                                                                duplizieren(&lwelefu,&lall);
                                                                duplizieren(&lwerigd,&lall);
                                                                duplizieren(&lwerigm,&lall);
                                                                duplizieren(&lwerigu,&lall);
                                                                duplizieren(&lwetopl,&lall);
                                                                duplizieren(&lwetopm,&lall);
                                                                duplizieren(&lwetopr,&lall);
                                                                duplizieren(&lwebotl,&lall);
                                                                duplizieren(&lwebotm,&lall);
                                                                duplizieren(&lwebotr,&lall);
                                                                //links schweißen
                                                                verschweissen(netz,lwefrol[3],lwelefm[0],&lall);
                                                                verschweissen(netz,lwetopl[3],lwelefm[1],&lall);
                                                                verschweissen(netz,lwebacl[3],lwelefm[2],&lall);
                                                                verschweissen(netz,lwebotl[3],lwelefm[3],&lall);
                                                                verschweissen(netz,lwefrol[2],lwetopl[0],&lall);
                                                                verschweissen(netz,lwetopl[2],lwebacl[2],&lall);
                                                                verschweissen(netz,lwebacl[0],lwebotl[2],&lall);
                                                                verschweissen(netz,lwebotl[0],lwefrol[0],&lall);
                                                                //rechts schweißen
                                                                verschweissen(netz,lwefror[1],lwerigm[0],&lall);
                                                                verschweissen(netz,lwetopr[1],lwerigm[1],&lall);
                                                                verschweissen(netz,lwebacr[1],lwerigm[2],&lall);
                                                                verschweissen(netz,lwebotr[1],lwerigm[3],&lall);
                                                                verschweissen(netz,lwefror[2],lwetopr[0],&lall);
                                                                verschweissen(netz,lwetopr[2],lwebacr[2],&lall);
                                                                verschweissen(netz,lwebacr[0],lwebotr[2],&lall);
                                                                verschweissen(netz,lwebotr[0],lwefror[0],&lall);
                                                                //oben schweißen
                                                                verschweissen(netz,lwefrou[2],lwetopm[0],&lall);
                                                                verschweissen(netz,lwerigu[1],lwetopm[1],&lall);
                                                                verschweissen(netz,lwebacu[2],lwetopm[2],&lall);
                                                                verschweissen(netz,lwelefu[1],lwetopm[3],&lall);
                                                                verschweissen(netz,lwefrou[1],lwerigu[0],&lall);
                                                                verschweissen(netz,lwerigu[2],lwebacu[1],&lall);
                                                                verschweissen(netz,lwebacu[3],lwelefu[2],&lall);
                                                                verschweissen(netz,lwelefu[0],lwefrou[3],&lall);
                                                                //unten schweißen
                                                                verschweissen(netz,lwefrod[0],lwebotm[0],&lall);
                                                                verschweissen(netz,lwerigd[3],lwebotm[1],&lall);
                                                                verschweissen(netz,lwebacd[0],lwebotm[2],&lall);
                                                                verschweissen(netz,lwelefd[3],lwebotm[3],&lall);
                                                                verschweissen(netz,lwefrod[1],lwerigd[0],&lall);
                                                                verschweissen(netz,lwerigd[2],lwebacd[1],&lall);
                                                                verschweissen(netz,lwebacd[3],lwelefd[2],&lall);
                                                                verschweissen(netz,lwelefd[0],lwefrod[3],&lall);
                                                                //mitte-vorne schweißen
                                                                verschweissen(netz,lwefrom[0],lwefrod[2],&lall);
                                                                verschweissen(netz,lwefrom[1],lwefror[3],&lall);
                                                                verschweissen(netz,lwefrom[2],lwefrou[0],&lall);
                                                                verschweissen(netz,lwefrom[3],lwefrol[1],&lall);
                                                                //mitte-hinten schweißen
                                                                verschweissen(netz,lwebacm[0],lwebacd[2],&lall);
                                                                verschweissen(netz,lwebacm[1],lwebacr[3],&lall);
                                                                verschweissen(netz,lwebacm[2],lwebacu[0],&lall);
                                                                verschweissen(netz,lwebacm[3],lwebacl[1],&lall);
                                                                //rest schweißen
                                                                verschweissen(netz,lwetopl[1],lwelefu[3],&lall);
                                                                verschweissen(netz,lwerigu[3],lwetopr[3],&lall);
                                                                verschweissen(netz,lwebotr[3],lwerigd[1],&lall);
                                                                verschweissen(netz,lwelefd[1],lwebotl[1],&lall);
                                                                if(pruefenausrichtung()) {
                                                                 if(netz->anfang(poly))do{
                                                                  poly->invertieren();
                                                                 }while(netz->naechstes(poly));
                                                                };//netz->invertierenausrichtung();
                                                                netz->aktualisieren(); 
                                                                lall.aushaengen();
                                                                lwefrol.loeschen();
                                                                lwefrom.loeschen();
                                                                lwefror.loeschen();
                                                                lwefrod.loeschen();
                                                                lwefrou.loeschen();
                                                                lwebacl.loeschen();
                                                                lwebacm.loeschen();
                                                                lwebacr.loeschen();
                                                                lwebacd.loeschen();
                                                                lwebacu.loeschen();
                                                                lwelefd.loeschen();
                                                                lwelefm.loeschen();
                                                                lwelefu.loeschen();
                                                                lwerigd.loeschen();
                                                                lwerigm.loeschen();
                                                                lwerigu.loeschen();
                                                                lwetopl.loeschen();
                                                                lwetopm.loeschen();
                                                                lwetopr.loeschen();
                                                                lwebotl.loeschen();
                                                                lwebotm.loeschen();
                                                                lwebotr.loeschen();
                                                                netz->farbe(farbe());
                                                                netz->farbeverbinder(farbe());
                                                                
                                                                if(standardtextur()) erzeugenstandardtexturkoordinaten(netz);
                                                                netz->verschiebenvertex(ort());
                                                                return(netz);
};
 
void _geometriekreuzdrei::erzeugenstandardtexturkoordinaten(_netz*){
                                                                
};
//******************************************************************************************************************************************************************************************************
//                                                              G E O M E T R I E K R E U Z
//******************************************************************************************************************************************************************************************************
 
_geometriekreuz::_geometriekreuz(_listebasis<_geometrie >*lg,_vektor3<_tg> lo,_vektor3<_tg> vx,_vektor3<_tg> vy,_vektor3<_tg> vz,_tg x0,_tg x1,_tg y0,_tg y1,_tg z0,_tg z1,_textur<_tb>*tex):_geometrie(lg,lo,vx,vy,vz,tex){
                                                                presolution.konvertieren(9);
                                                                for(int i=0;i<9;i++) presolution.setzenkomponente(i,1);
                                                                //presolution.setzen(9,1,1,1, 1,1,1, 1,1,1);
                                                                /*if(vx.holendimension()!=3) vx.setzen(vx[0],vx[1],vx[2]);
                                                                if(vy.holendimension()!=3) vy.setzen(vy[0],vy[1],vy[2]);
                                                                if(vz.holendimension()!=3) vz.setzen(vz[0],vz[1],vz[2]);
                                                                vektor0(vx);
                                                                vektor1(vy);
                                                                vektor2(vz);*/
                                                                tile0(x0,x1);
                                                                tile1(y0,y1);
                                                                tile2(z0,z1);
                                                                name("crossbar");
};
 
_geometriekreuz::~_geometriekreuz(){
};

void _geometriekreuz::aufloesung(_vektor<unsigned int> r){
                                                                int i;
                                                                if(r.holendimension()!=9) {
                                                                 r.konvertieren(9);
                                                                 for(i=0;i<9;i++) r.setzenkomponente(i,r[i]);
                                                                 //r.setzen(7,r[0],r[1],r[2],r[3],r[4],r[5],r[6],r[7],r[8]);
                                                                };
                                                                for(i=0;i<9;i++) if(r[i]<1) r.setzenkomponente(i,1);
                                                                presolution=r;
};
/*
 
void _geometriekreuz::vektor0(_vektor3<_tg> l){
                                                                if(l.holendimension()!=3) l.setzen(l[0],l[1],l[2]);
                                                                pvx=l;
};
 
void _geometriekreuz::vektor1(_vektor3<_tg> l){
                                                                if(l.holendimension()!=3) l.setzen(l[0],l[1],l[2]);
                                                                pvy=l;
};
 
void _geometriekreuz::vektor2(_vektor3<_tg> l){
                                                                if(l.holendimension()!=3) l.setzen(l[0],l[1],l[2]);
                                                                pvz=l;
};
*/
 
void _geometriekreuz::tile0(_tg x0,_tg x1){
                                                                _tg h;
                                                                if(x0<0) x0=0;
                                                                if(x0>1) x0=1;
                                                                if(x1<0) x1=0;
                                                                if(x1>1) x1=1;
                                                                if(x0>x1) {
                                                                 h=x0;
                                                                 x0=x1;
                                                                 x1=h;
                                                                };
                                                                if(x0==x1){
                                                                 if(x0<0.5){
                                                                  x1+=nahenull*2;
                                                                 }else{
                                                                  x0-=nahenull*2;
                                                                 };
                                                                };
                                                                ptx.setzen(x0,x1);
};
 
void _geometriekreuz::tile1(_tg x0,_tg x1){
                                                                _tg h;
                                                                if(x0<0) x0=0;
                                                                if(x0>1) x0=1;
                                                                if(x1<0) x1=0;
                                                                if(x1>1) x1=1;
                                                                if(x0>x1) {
                                                                 h=x0;
                                                                 x0=x1;
                                                                 x1=h;
                                                                };
                                                                if(x0==x1){
                                                                 if(x0<0.5){
                                                                  x1+=nahenull*2;
                                                                 }else{
                                                                  x0-=nahenull*2;
                                                                 };
                                                                };
                                                                pty.setzen(x0,x1);
};
 
void _geometriekreuz::tile2(_tg x0,_tg x1){
                                                                _tg h;
                                                                if(x0<0) x0=0;
                                                                if(x0>1) x0=1;
                                                                if(x1<0) x1=0;
                                                                if(x1>1) x1=1;
                                                                if(x0>x1) {
                                                                 h=x0;
                                                                 x0=x1;
                                                                 x1=h;
                                                                };
                                                                if(x0==x1){
                                                                 if(x0<0.5){
                                                                  x1+=nahenull*2;
                                                                 }else{
                                                                  x0-=nahenull*2;
                                                                 };
                                                                };
                                                                ptz.setzen(x0,x1);
};
/*
 
bool _geometriekreuz::pruefenausrichtung()const{
                                                                _vektor3<_tg> h;
                                                                bool ix;
                                                                bool iy;
                                                                bool iz;
                                                                //----------------
                                                                h=pvy%pvz;
                                                                h.normalisieren();
                                                                if((pvx*h)<0) ix=true; else ix=false;
                                                                
                                                                h=pvx%pvz;
                                                                h.normalisieren();
                                                                if((pvy*h)<0) iy=true; else iy=false;
                                                                
                                                                h=pvx%pvy;
                                                                h.normalisieren();
                                                                if((pvz*h)<0) iz=true; else iz=false;
                                                                
                                                                return(not(ix xor iy xor iz));
};
*/                                                                
 
_netz* _geometriekreuz::erzeugen(){
                                                                unsigned int rxl;
                                                                unsigned int rxm;
                                                                unsigned int rxr;
                                                                unsigned int ryd;
                                                                unsigned int rym;
                                                                unsigned int ryu;
                                                                unsigned int rzf;
                                                                unsigned int rzm;
                                                                unsigned int rzb;
                                                                _liste<_schweisskante > lwefrol;
                                                                _liste<_schweisskante > lwefror;
                                                                _liste<_schweisskante > lwefrou;
                                                                _liste<_schweisskante > lwefrod;
                                                                _liste<_schweisskante > lwefrom;

                                                                _liste<_schweisskante > lwebacl;
                                                                _liste<_schweisskante > lwebacr;
                                                                _liste<_schweisskante > lwebacu;
                                                                _liste<_schweisskante > lwebacd;
                                                                _liste<_schweisskante > lwebacm;
                                                                
                                                                _liste<_schweisskante > lwelefd;
                                                                _liste<_schweisskante > lwelefm;
                                                                _liste<_schweisskante > lwelefu;
                                                                _liste<_schweisskante > lweleff;
                                                                _liste<_schweisskante > lwelefb;

                                                                _liste<_schweisskante > lwerigd;
                                                                _liste<_schweisskante > lwerigm;
                                                                _liste<_schweisskante > lwerigu;
                                                                _liste<_schweisskante > lwerigf;
                                                                _liste<_schweisskante > lwerigb;
                                                                
                                                                _liste<_schweisskante > lweuppl;
                                                                _liste<_schweisskante > lweuppm;
                                                                _liste<_schweisskante > lweuppr;
                                                                _liste<_schweisskante > lweuppf;
                                                                _liste<_schweisskante > lweuppb;
                                                                
                                                                _liste<_schweisskante > lwedowl;
                                                                _liste<_schweisskante > lwedowm;
                                                                _liste<_schweisskante > lwedowr;
                                                                _liste<_schweisskante > lwedowf;
                                                                _liste<_schweisskante > lwedowb;
                                                                
                                                                _liste<_schweisskante > lall;
                                                                _vektor3<_tg> a;
                                                                _vektor3<_tg> b;
                                                                _vektor3<_tg> o;
                                                                _netz*netz;
                                                                _polygon*poly;
                                                                _vektor3<_tg> pvx;
                                                                _vektor3<_tg> pvy;
                                                                _vektor3<_tg> pvz;
                                                                //---------------------------------------
                                                                netz=new _netz();
                                                                rxl=(unsigned int)(_tg(presolution[0])*aufloesungsskalierung());
                                                                rxm=(unsigned int)(_tg(presolution[1])*aufloesungsskalierung());
                                                                rxr=(unsigned int)(_tg(presolution[2])*aufloesungsskalierung());
                                                                ryd=(unsigned int)(_tg(presolution[3])*aufloesungsskalierung());
                                                                rym=(unsigned int)(_tg(presolution[4])*aufloesungsskalierung());
                                                                ryu=(unsigned int)(_tg(presolution[5])*aufloesungsskalierung());
                                                                rzf=(unsigned int)(_tg(presolution[6])*aufloesungsskalierung());
                                                                rzm=(unsigned int)(_tg(presolution[7])*aufloesungsskalierung());
                                                                rzb=(unsigned int)(_tg(presolution[8])*aufloesungsskalierung());
                                                                pvx=vektor(0);
                                                                pvy=vektor(1);
                                                                pvz=vektor(2);
                                                                //frol
                                                                o=pvy*pty[0]+pvz*ptz[0];
                                                                a=pvx*ptx[0];
                                                                b=pvy*(pty[1]-pty[0]);
                                                                poly=erzeugennetz(netz,o,a,b,rxl,rym,&lwefrol);
                                                                //from
                                                                o=pvx*ptx[0]+pvy*pty[0];
                                                                a=pvx*(ptx[1]-ptx[0]);
                                                                b=pvy*(pty[1]-pty[0]);
                                                                poly=erzeugennetz(netz,o,a,b,rxm,rym,&lwefrom);
                                                                //fror
                                                                o=pvx*ptx[1]+pvy*pty[0]+pvz*ptz[0];
                                                                a=pvx*(1-ptx[1]);
                                                                b=pvy*(pty[1]-pty[0]);
                                                                poly=erzeugennetz(netz,o,a,b,rxr,rym,&lwefror);
                                                                //frod
                                                                o=pvx*ptx[0]+pvz*ptz[0];
                                                                a=pvx*(ptx[1]-ptx[0]);
                                                                b=pvy*pty[0];
                                                                poly=erzeugennetz(netz,o,a,b,rxm,ryd,&lwefrod);
                                                                //frou
                                                                o=pvx*ptx[0]+pvy*pty[1]+pvz*ptz[0];
                                                                a=pvx*(ptx[1]-ptx[0]);
                                                                b=pvy*(1-pty[1]);
                                                                poly=erzeugennetz(netz,o,a,b,rxm,ryu,&lwefrou);
                                                                
                                                                //bacl
                                                                o=pvy*pty[0]+pvz*ptz[1];
                                                                a=pvx*ptx[0];
                                                                b=pvy*(pty[1]-pty[0]);
                                                                poly=erzeugennetz(netz,o,a,b,rxl,rym,&lwebacl);
                                                                netz->invertierenausrichtung(poly,rxl*rym);
                                                                //bacm
                                                                o=pvx*ptx[0]+pvy*pty[0]+pvz;
                                                                a=pvx*(ptx[1]-ptx[0]);
                                                                b=pvy*(pty[1]-pty[0]);
                                                                poly=erzeugennetz(netz,o,a,b,rxm,rym,&lwebacm);
                                                                netz->invertierenausrichtung(poly,rxm*rym);
                                                                //bacr
                                                                o=pvx*ptx[1]+pvy*pty[0]+pvz*ptz[1];
                                                                a=pvx*(1-ptx[1]);
                                                                b=pvy*(pty[1]-pty[0]);
                                                                poly=erzeugennetz(netz,o,a,b,rxr,rym,&lwebacr);
                                                                netz->invertierenausrichtung(poly,rxr*rym);
                                                                //bacd
                                                                o=pvx*ptx[0]+pvz*ptz[1];
                                                                a=pvx*(ptx[1]-ptx[0]);
                                                                b=pvy*pty[0];
                                                                poly=erzeugennetz(netz,o,a,b,rxm,ryd,&lwebacd);
                                                                netz->invertierenausrichtung(poly,rxm*ryd);
                                                                //bacu
                                                                o=pvx*ptx[0]+pvy*pty[1]+pvz*ptz[1];
                                                                a=pvx*(ptx[1]-ptx[0]);
                                                                b=pvy*(1-pty[1]);
                                                                poly=erzeugennetz(netz,o,a,b,rxm,ryu,&lwebacu);
                                                                netz->invertierenausrichtung(poly,rxm*ryu);
                                                                
                                                                //lefd
                                                                o=pvx*ptx[0]+pvz*ptz[0];
                                                                a=pvy*pty[0];
                                                                b=pvz*(ptz[1]-ptz[0]);
                                                                poly=erzeugennetz(netz,o,a,b,ryd,rzm,&lwelefd);
                                                                //lefm
                                                                o=pvy*pty[0]+pvz*ptz[0];
                                                                a=pvy*(pty[1]-pty[0]);
                                                                b=pvz*(ptz[1]-ptz[0]);
                                                                poly=erzeugennetz(netz,o,a,b,rym,rzm,&lwelefm);
                                                                //lefu
                                                                o=pvx*ptx[0]+pvy*pty[1]+pvz*ptz[0];
                                                                a=pvy*(1-pty[1]);
                                                                b=pvz*(ptz[1]-ptz[0]);
                                                                poly=erzeugennetz(netz,o,a,b,ryu,rzm,&lwelefu);
                                                                //leff
                                                                o=pvx*ptx[0]+pvy*pty[0];
                                                                a=pvy*(pty[1]-pty[0]);
                                                                b=pvz*ptz[0];
                                                                poly=erzeugennetz(netz,o,a,b,rym,rzf,&lweleff);
                                                                //lefb
                                                                o=pvx*ptx[0]+pvy*pty[0]+pvz*ptz[1];
                                                                a=pvy*(pty[1]-pty[0]);
                                                                b=pvz*(1-ptz[1]);
                                                                poly=erzeugennetz(netz,o,a,b,rym,rzb,&lwelefb);
                                                                
                                                                //rigd
                                                                o=pvx*ptx[1]+pvz*ptz[0];
                                                                a=pvy*pty[0];
                                                                b=pvz*(ptz[1]-ptz[0]);
                                                                poly=erzeugennetz(netz,o,a,b,ryd,rzm,&lwerigd);
                                                                netz->invertierenausrichtung(poly,ryd*rzm);
                                                                //rigm
                                                                o=pvx+pvy*pty[0]+pvz*ptz[0];
                                                                a=pvy*(pty[1]-pty[0]);
                                                                b=pvz*(ptz[1]-ptz[0]);
                                                                poly=erzeugennetz(netz,o,a,b,rym,rzm,&lwerigm);
                                                                netz->invertierenausrichtung(poly,rym*rzm);
                                                                //rigu
                                                                o=pvx*ptx[1]+pvy*pty[1]+pvz*ptz[0];
                                                                a=pvy*(1-pty[1]);
                                                                b=pvz*(ptz[1]-ptz[0]);
                                                                poly=erzeugennetz(netz,o,a,b,ryu,rzm,&lwerigu);
                                                                netz->invertierenausrichtung(poly,ryu*rzm);
                                                                //rigf
                                                                o=pvx*ptx[1]+pvy*pty[0];
                                                                a=pvy*(pty[1]-pty[0]);
                                                                b=pvz*ptz[0];
                                                                poly=erzeugennetz(netz,o,a,b,rym,rzf,&lwerigf);
                                                                netz->invertierenausrichtung(poly,rym*rzf);
                                                                //rigb
                                                                o=pvx*ptx[1]+pvy*pty[0]+pvz*ptz[1];
                                                                a=pvy*(pty[1]-pty[0]);
                                                                b=pvz*(1-ptz[1]);
                                                                poly=erzeugennetz(netz,o,a,b,rym,rzb,&lwerigb);
                                                                netz->invertierenausrichtung(poly,rym*rzb);
                                                                
                                                                //uppl
                                                                o=pvy*pty[1]+pvz*ptz[0];
                                                                a=pvx*ptx[0];
                                                                b=pvz*(ptz[1]-ptz[0]);
                                                                poly=erzeugennetz(netz,o,a,b,rxl,rzm,&lweuppl);
                                                                //uppm
                                                                o=pvy+pvx*ptx[0]+pvz*ptz[0];
                                                                a=pvx*(ptx[1]-ptx[0]);
                                                                b=pvz*(ptz[1]-ptz[0]);
                                                                poly=erzeugennetz(netz,o,a,b,rxm,rzm,&lweuppm);
                                                                //uppr
                                                                o=pvx*ptx[1]+pvy*pty[1]+pvz*ptz[0];
                                                                a=pvx*(1-ptx[1]);
                                                                b=pvz*(ptz[1]-ptz[0]);
                                                                poly=erzeugennetz(netz,o,a,b,rxr,rzm,&lweuppr);
                                                                //uppf
                                                                o=pvx*ptx[0]+pvy*pty[1];
                                                                a=pvx*(ptx[1]-ptx[0]);
                                                                b=pvz*ptz[0];
                                                                poly=erzeugennetz(netz,o,a,b,rxm,rzf,&lweuppf);
                                                                //uppb
                                                                o=pvx*ptx[0]+pvy*pty[1]+pvz*ptz[1];
                                                                a=pvx*(ptx[1]-ptx[0]);
                                                                b=pvz*(1-ptz[1]);
                                                                poly=erzeugennetz(netz,o,a,b,rxm,rzb,&lweuppb);
                                                                
                                                                //dowl
                                                                o=pvy*pty[0]+pvz*ptz[0];
                                                                a=pvx*ptx[0];
                                                                b=pvz*(ptz[1]-ptz[0]);
                                                                poly=erzeugennetz(netz,o,a,b,rxl,rzm,&lwedowl);
                                                                netz->invertierenausrichtung(poly,rxl*rzm);
                                                                //dowm
                                                                o=pvx*ptx[0]+pvz*ptz[0];
                                                                a=pvx*(ptx[1]-ptx[0]);
                                                                b=pvz*(ptz[1]-ptz[0]);
                                                                poly=erzeugennetz(netz,o,a,b,rxm,rzm,&lwedowm);
                                                                netz->invertierenausrichtung(poly,rxm*rzm);
                                                                //dowr
                                                                o=pvx*ptx[1]+pvy*pty[0]+pvz*ptz[0];
                                                                a=pvx*(1-ptx[1]);
                                                                b=pvz*(ptz[1]-ptz[0]);
                                                                poly=erzeugennetz(netz,o,a,b,rxr,rzm,&lwedowr);
                                                                netz->invertierenausrichtung(poly,rxr*rzm);
                                                                //dowf
                                                                o=pvx*ptx[0]+pvy*pty[0];
                                                                a=pvx*(ptx[1]-ptx[0]);
                                                                b=pvz*ptz[0];
                                                                poly=erzeugennetz(netz,o,a,b,rxm,rzf,&lwedowf);
                                                                netz->invertierenausrichtung(poly,rxm*rzf);
                                                                //dowb
                                                                o=pvx*ptx[0]+pvy*pty[0]+pvz*ptz[1];
                                                                a=pvx*(ptx[1]-ptx[0]);
                                                                b=pvz*(1-ptz[1]);
                                                                poly=erzeugennetz(netz,o,a,b,rxm,rzb,&lwedowb);
                                                                netz->invertierenausrichtung(poly,rxm*rzb);

                                                                
                                                                //-------------------------- WELD ----------------------------
                                                                duplizieren(&lwefrol,&lall);
                                                                duplizieren(&lwefrom,&lall);
                                                                duplizieren(&lwefror,&lall);
                                                                duplizieren(&lwefrod,&lall);
                                                                duplizieren(&lwefrou,&lall);
                                                                
                                                                duplizieren(&lwebacl,&lall);
                                                                duplizieren(&lwebacm,&lall);
                                                                duplizieren(&lwebacr,&lall);
                                                                duplizieren(&lwebacd,&lall);
                                                                duplizieren(&lwebacu,&lall);
                                                                
                                                                duplizieren(&lwelefd,&lall);
                                                                duplizieren(&lwelefm,&lall);
                                                                duplizieren(&lwelefu,&lall);
                                                                duplizieren(&lweleff,&lall);
                                                                duplizieren(&lwelefb,&lall);
                                                                
                                                                duplizieren(&lwerigd,&lall);
                                                                duplizieren(&lwerigm,&lall);
                                                                duplizieren(&lwerigu,&lall);
                                                                duplizieren(&lwerigf,&lall);
                                                                duplizieren(&lwerigb,&lall);
                                                                
                                                                duplizieren(&lweuppl,&lall);
                                                                duplizieren(&lweuppm,&lall);
                                                                duplizieren(&lweuppr,&lall);
                                                                duplizieren(&lweuppf,&lall);
                                                                duplizieren(&lweuppb,&lall);

                                                                duplizieren(&lwedowl,&lall);
                                                                duplizieren(&lwedowm,&lall);
                                                                duplizieren(&lwedowr,&lall);
                                                                duplizieren(&lwedowf,&lall);
                                                                duplizieren(&lwedowb,&lall);
                                                                
                                                                //links schweißen
                                                                verschweissen(netz,lwefrol[3],lwelefm[0],&lall);
                                                                verschweissen(netz,lweuppl[3],lwelefm[1],&lall);
                                                                verschweissen(netz,lwebacl[3],lwelefm[2],&lall);
                                                                verschweissen(netz,lwedowl[3],lwelefm[3],&lall);
                                                                verschweissen(netz,lwefrol[2],lweuppl[0],&lall);
                                                                verschweissen(netz,lweuppl[2],lwebacl[2],&lall);
                                                                verschweissen(netz,lwebacl[0],lwedowl[2],&lall);
                                                                verschweissen(netz,lwedowl[0],lwefrol[0],&lall);
                                                                //rechts schweißen
                                                                verschweissen(netz,lwefror[1],lwerigm[0],&lall);
                                                                verschweissen(netz,lweuppr[1],lwerigm[1],&lall);
                                                                verschweissen(netz,lwebacr[1],lwerigm[2],&lall);
                                                                verschweissen(netz,lwedowr[1],lwerigm[3],&lall);
                                                                verschweissen(netz,lwefror[2],lweuppr[0],&lall);
                                                                verschweissen(netz,lweuppr[2],lwebacr[2],&lall);
                                                                verschweissen(netz,lwebacr[0],lwedowr[2],&lall);
                                                                verschweissen(netz,lwedowr[0],lwefror[0],&lall);
                                                                //oben schweißen
                                                                verschweissen(netz,lwefrou[2],lweuppm[0],&lall);
                                                                verschweissen(netz,lwerigu[1],lweuppm[1],&lall);
                                                                verschweissen(netz,lwebacu[2],lweuppm[2],&lall);
                                                                verschweissen(netz,lwelefu[1],lweuppm[3],&lall);
                                                                verschweissen(netz,lwefrou[1],lwerigu[0],&lall);
                                                                verschweissen(netz,lwerigu[2],lwebacu[1],&lall);
                                                                verschweissen(netz,lwebacu[3],lwelefu[2],&lall);
                                                                verschweissen(netz,lwelefu[0],lwefrou[3],&lall);
                                                                //unten schweißen
                                                                verschweissen(netz,lwefrod[0],lwedowm[0],&lall);
                                                                verschweissen(netz,lwerigd[3],lwedowm[1],&lall);
                                                                verschweissen(netz,lwebacd[0],lwedowm[2],&lall);
                                                                verschweissen(netz,lwelefd[3],lwedowm[3],&lall);
                                                                verschweissen(netz,lwefrod[1],lwerigd[0],&lall);
                                                                verschweissen(netz,lwerigd[2],lwebacd[1],&lall);
                                                                verschweissen(netz,lwebacd[3],lwelefd[2],&lall);
                                                                verschweissen(netz,lwelefd[0],lwefrod[3],&lall);
                                                                //vorne schweißen
                                                                verschweissen(netz,lwedowf[0],lwefrom[0],&lall);
                                                                verschweissen(netz,lwerigf[0],lwefrom[1],&lall);
                                                                verschweissen(netz,lweuppf[0],lwefrom[2],&lall);
                                                                verschweissen(netz,lweleff[0],lwefrom[3],&lall);
                                                                verschweissen(netz,lwedowf[1],lwerigf[3],&lall);
                                                                verschweissen(netz,lwerigf[1],lweuppf[1],&lall);
                                                                verschweissen(netz,lweuppf[3],lweleff[1],&lall);
                                                                verschweissen(netz,lweleff[3],lwedowf[3],&lall);
                                                                //hinten schweißen
                                                                verschweissen(netz,lwedowb[2],lwebacm[0],&lall);
                                                                verschweissen(netz,lwerigb[2],lwebacm[1],&lall);
                                                                verschweissen(netz,lweuppb[2],lwebacm[2],&lall);
                                                                verschweissen(netz,lwelefb[2],lwebacm[3],&lall);
                                                                verschweissen(netz,lwedowb[1],lwerigb[3],&lall);
                                                                verschweissen(netz,lwerigb[1],lweuppb[1],&lall);
                                                                verschweissen(netz,lweuppb[3],lwelefb[1],&lall);
                                                                verschweissen(netz,lwelefb[3],lwedowb[3],&lall);
                                                                //rest vorne schweißen
                                                                verschweissen(netz,lweuppf[2],lwefrou[0],&lall);
                                                                verschweissen(netz,lwerigf[2],lwefror[3],&lall);
                                                                verschweissen(netz,lwedowf[2],lwefrod[2],&lall);
                                                                verschweissen(netz,lweleff[2],lwefrol[1],&lall);
                                                                //rest hinten schweißen
                                                                verschweissen(netz,lweuppb[0],lwebacu[0],&lall);
                                                                verschweissen(netz,lwerigb[0],lwebacr[3],&lall);
                                                                verschweissen(netz,lwedowb[0],lwebacd[2],&lall);
                                                                verschweissen(netz,lwelefb[0],lwebacl[1],&lall);
                                                                //rest drumherum schweißen
                                                                verschweissen(netz,lweuppl[1],lwelefu[3],&lall);
                                                                verschweissen(netz,lwerigu[3],lweuppr[3],&lall);
                                                                verschweissen(netz,lwedowr[3],lwerigd[1],&lall);
                                                                verschweissen(netz,lwelefd[1],lwedowl[1],&lall);

                                                                
                                                                //if(pruefenausrichtung()) netz->invertierenausrichtung();
                                                                if(pruefenausrichtung()) {
                                                                 if(netz->anfang(poly))do{
                                                                  poly->invertieren();
                                                                 }while(netz->naechstes(poly));
                                                                };//netz->invertierenausrichtung();
                                                                
                                                                
                                                                netz->aktualisieren(); 
                                                                lall.aushaengen();
                                                                
                                                                lwefrol.loeschen();
                                                                lwefrom.loeschen();
                                                                lwefror.loeschen();
                                                                lwefrod.loeschen();
                                                                lwefrou.loeschen();
                                                                
                                                                lwebacl.loeschen();
                                                                lwebacm.loeschen();
                                                                lwebacr.loeschen();
                                                                lwebacd.loeschen();
                                                                lwebacu.loeschen();
                                                                
                                                                lwelefd.loeschen();
                                                                lwelefm.loeschen();
                                                                lwelefu.loeschen();
                                                                lweleff.loeschen();
                                                                lwelefb.loeschen();
                                                                
                                                                lwerigd.loeschen();
                                                                lwerigm.loeschen();
                                                                lwerigu.loeschen();
                                                                lwerigf.loeschen();
                                                                lwerigb.loeschen();
                                                                
                                                                lweuppl.loeschen();
                                                                lweuppm.loeschen();
                                                                lweuppr.loeschen();
                                                                lweuppf.loeschen();
                                                                lweuppb.loeschen();
                                                                
                                                                lwedowl.loeschen();
                                                                lwedowm.loeschen();
                                                                lwedowr.loeschen();
                                                                lwedowf.loeschen();
                                                                lwedowb.loeschen();
                                                                netz->farbe(farbe());
                                                                netz->farbeverbinder(farbe());
                                                                
                                                                if(standardtextur()) erzeugenstandardtexturkoordinaten(netz);
                                                                netz->verschiebenvertex(ort());
                                                                return(netz);
};
 
void _geometriekreuz::erzeugenstandardtexturkoordinaten(_netz*){
                                                                
};
//******************************************************************************************************************************************************************************************************
//                                                              G E O M E T R I E K R E U Z B A L K E N 
//******************************************************************************************************************************************************************************************************
 
_geometriekreuzbalken::_geometriekreuzbalken(_listebasis<_geometrie >*lg,_vektor3<_tg> lo,_vektor3<_tg> vx,_vektor3<_tg> vy,_vektor3<_tg> vz,_tg pb,_textur<_tb>*tex):_geometrie(lg,lo,vx,vy,vz,tex){
                                                                int i;
                                                                presolution.konvertieren(5);
                                                                for(i=0;i<5;i++) presolution.setzenkomponente(i,1);
                                                                //presolution.setzen(5,1,1,1,1,1);
                                                                breite(pb);
                                                                name("kreuzbalken");
};
 
_geometriekreuzbalken::~_geometriekreuzbalken(){
};

void _geometriekreuzbalken::aufloesung(_vektor<unsigned int> r){
                                                                int i;
                                                                if(r.holendimension()!=5) {
                                                                 r.konvertieren(5);
                                                                 for(i=0;i<5;i++) r.setzenkomponente(i,r[i]);
                                                                };
                                                                //if(r.holendimension()!=5) r.setzen(5,r[0],r[1],r[2],r[3],r[4]);
                                                                for(i=0;i<5;i++) if(r[i]<1) r.setzenkomponente(i,1);
                                                                presolution=r;
};
 
void _geometriekreuzbalken::breite(_tg x){
                                                                if(x<0) x*=-1;
                                                                if(x<nahenull*4) x=nahenull*4;
                                                                if(x>((1.0/3.0)-nahenull*16)) x=(1.0/3.0)-nahenull*16;
                                                                pwidth=x;
};
 
_netz* _geometriekreuzbalken::erzeugen(){
                                                                unsigned int rxm;
                                                                unsigned int rxq;
                                                                unsigned int rxw;
                                                                unsigned int rym;
                                                                unsigned int ryq;
                                                                unsigned int ryw;
                                                                unsigned int rz;
                                                                _liste<_schweisskante > lwe00f;
                                                                _liste<_schweisskante > lwe00b;
                                                                _liste<_schweisskante > lwe00l;
                                                                _liste<_schweisskante > lwe00r;
                                                                _liste<_schweisskante > lwe00u;

                                                                _liste<_schweisskante > lwe01f;
                                                                _liste<_schweisskante > lwe01b;
                                                                _liste<_schweisskante > lwe01l;
                                                                _liste<_schweisskante > lwe01u;

                                                                _liste<_schweisskante > lwe02f;
                                                                _liste<_schweisskante > lwe02b;
                                                                _liste<_schweisskante > lwe02r;
                                                                _liste<_schweisskante > lwe02u;
                                                                _liste<_schweisskante > lwe02d;

                                                                _liste<_schweisskante > lwe03f;
                                                                _liste<_schweisskante > lwe03b;
                                                                _liste<_schweisskante > lwe03l;
                                                                _liste<_schweisskante > lwe03r;

                                                                _liste<_schweisskante > lwe04f;
                                                                _liste<_schweisskante > lwe04b;
                                                                _liste<_schweisskante > lwe04l;
                                                                _liste<_schweisskante > lwe04d;

                                                                _liste<_schweisskante > lwe05f;
                                                                _liste<_schweisskante > lwe05b;
                                                                _liste<_schweisskante > lwe05u;
                                                                _liste<_schweisskante > lwe05d;

                                                                _liste<_schweisskante > lwe06f;
                                                                _liste<_schweisskante > lwe06b;

                                                                _liste<_schweisskante > lwe07f;
                                                                _liste<_schweisskante > lwe07b;
                                                                _liste<_schweisskante > lwe07u;
                                                                _liste<_schweisskante > lwe07d;

                                                                _liste<_schweisskante > lwe08f;
                                                                _liste<_schweisskante > lwe08b;
                                                                _liste<_schweisskante > lwe08r;
                                                                _liste<_schweisskante > lwe08u;

                                                                _liste<_schweisskante > lwe09f;
                                                                _liste<_schweisskante > lwe09b;
                                                                _liste<_schweisskante > lwe09l;
                                                                _liste<_schweisskante > lwe09r;

                                                                _liste<_schweisskante > lwe10f;
                                                                _liste<_schweisskante > lwe10b;
                                                                _liste<_schweisskante > lwe10l;
                                                                _liste<_schweisskante > lwe10u;
                                                                _liste<_schweisskante > lwe10d;

                                                                _liste<_schweisskante > lwe11f;
                                                                _liste<_schweisskante > lwe11b;
                                                                _liste<_schweisskante > lwe11r;
                                                                _liste<_schweisskante > lwe11d;

                                                                _liste<_schweisskante > lwe12f;
                                                                _liste<_schweisskante > lwe12b;
                                                                _liste<_schweisskante > lwe12l;
                                                                _liste<_schweisskante > lwe12r;
                                                                _liste<_schweisskante > lwe12d;
                                                                
                                                                _liste<_schweisskante > lall;
                                                                _vektor3<_tg> a;
                                                                _vektor3<_tg> b;
                                                                _vektor3<_tg> o;
                                                                _netz*netz;
                                                                _polygon*poly;
                                                                _tg geswidth;
                                                                _tg q;
                                                                _tg w;
                                                                _tg x0,x1,x2,x3,x4,x5;
                                                                _vektor3<_tg> pvx;
                                                                _vektor3<_tg> pvy;
                                                                _vektor3<_tg> pvz;
                                                                //---------------------------------------
                                                                netz=new _netz();
                                                                pvx=vektor(0);
                                                                pvy=vektor(1);
                                                                pvz=vektor(2);
                                                                rxm=(unsigned int)(_tg(presolution[0])*aufloesungsskalierung());
                                                                rxq=(unsigned int)(_tg(presolution[1])*aufloesungsskalierung());
                                                                rym=(unsigned int)(_tg(presolution[2])*aufloesungsskalierung());
                                                                ryq=(unsigned int)(_tg(presolution[3])*aufloesungsskalierung());
                                                                rz =(unsigned int)(_tg(presolution[4])*aufloesungsskalierung());
                                                                //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                                                                rxw=(rxq+rxm)*1;
                                                                ryw=(ryq+rym)*1;
                                                                geswidth=pvx.laenge();
                                                                w=(1-pwidth)*0.5;
                                                                q=w-pwidth;

                                                                rxq=(unsigned int)(((1.0/pwidth)*rxm)*q); 
                                                                if(rxq<1) rxq=1;   
                                                                ryq=(unsigned int)(((1.0/pwidth)*rym)*q); 
                                                                if(ryq<1) ryq=1;
                                                                rxw=(unsigned int)(((1.0/pwidth)*rxm)*w); 
                                                                if(rxw<1) rxw=1;   
                                                                ryw=(unsigned int)(((1.0/pwidth)*rym)*w); 
                                                                if(ryw<1) ryw=1;   
                                                                
                                                                x0=0;
                                                                x1=pwidth;
                                                                x2=pwidth+q;
                                                                x3=pwidth+q+pwidth;
                                                                x4=pwidth+q+pwidth+q;
                                                                x5=pwidth+q+pwidth+q+pwidth;

                                                                //00
                                                                poly=erzeugennetz(netz,       pvy*x3,    pvx*(x1-x0),pvy*(x5-x3),rxm,ryw,&lwe00f);
                                                                poly=erzeugennetz(netz,       pvy*x3+pvz,pvx*(x1-x0),pvy*(x5-x3),rxm,ryw,&lwe00b);netz->invertierenausrichtung(poly,rxm*ryw);
                                                                poly=erzeugennetz(netz,       pvy*x3,    pvy*(x5-x3),pvz        ,ryw,rz ,&lwe00l);
                                                                poly=erzeugennetz(netz,pvx*x1+pvy*x3,    pvy*(x5-x3),pvz        ,ryw,rz ,&lwe00r);netz->invertierenausrichtung(poly,ryw*rz);
                                                                poly=erzeugennetz(netz,       pvy*x5,    pvx*(x1-x0),pvz        ,rxm,rz ,&lwe00u);
                                                                //01
                                                                poly=erzeugennetz(netz,pvx*x2+pvy*x4,    pvx*(x3-x2),pvy*(x5-x4),rxm,rym,&lwe01f);
                                                                poly=erzeugennetz(netz,pvx*x2+pvy*x4+pvz,pvx*(x3-x2),pvy*(x5-x4),rxm,rym,&lwe01b);netz->invertierenausrichtung(poly,rxm*rym);
                                                                poly=erzeugennetz(netz,pvx*x2+pvy*x4,    pvy*(x5-x4),pvz        ,rym,rz ,&lwe01l);
                                                                poly=erzeugennetz(netz,pvx*x2+pvy*x5,    pvx*(x3-x2),pvz        ,rxm,rz ,&lwe01u);
                                                                //02
                                                                poly=erzeugennetz(netz,pvx*x3+pvy*x4,    pvx*(x5-x3),pvy*(x5-x4),rxw,rym,&lwe02f);
                                                                poly=erzeugennetz(netz,pvx*x3+pvy*x4+pvz,pvx*(x5-x3),pvy*(x5-x4),rxw,rym,&lwe02b);netz->invertierenausrichtung(poly,rxw*rym);
                                                                poly=erzeugennetz(netz,pvx*x5+pvy*x4,    pvy*(x5-x4),pvz        ,rym,rz ,&lwe02r);netz->invertierenausrichtung(poly,rym*rz);
                                                                poly=erzeugennetz(netz,pvx*x3+pvy*x5,    pvx*(x5-x3),pvz        ,rxw,rz ,&lwe02u);
                                                                poly=erzeugennetz(netz,pvx*x3+pvy*x4,    pvx*(x5-x3),pvz        ,rxw,rz ,&lwe02d);netz->invertierenausrichtung(poly,rxw*rz);
                                                                //03
                                                                poly=erzeugennetz(netz,pvx*x2+pvy*x3,    pvx*(x3-x2),pvy*(x4-x3),rxm,ryq,&lwe03f);
                                                                poly=erzeugennetz(netz,pvx*x2+pvy*x3+pvz,pvx*(x3-x2),pvy*(x4-x3),rxm,ryq,&lwe03b);netz->invertierenausrichtung(poly,rxm*ryq);
                                                                poly=erzeugennetz(netz,pvx*x2+pvy*x3,    pvy*(x4-x3),pvz        ,ryq,rz ,&lwe03l);
                                                                poly=erzeugennetz(netz,pvx*x3+pvy*x3,    pvy*(x4-x3),pvz        ,ryq,rz ,&lwe03r);netz->invertierenausrichtung(poly,ryq*rz);
                                                                //04
                                                                poly=erzeugennetz(netz,       pvy*x2,    pvx*(x1-x0),pvy*(x3-x2),rxm,rym,&lwe04f);
                                                                poly=erzeugennetz(netz,       pvy*x2+pvz,pvx*(x1-x0),pvy*(x3-x2),rxm,rym,&lwe04b);netz->invertierenausrichtung(poly,rxm*rym);
                                                                poly=erzeugennetz(netz,       pvy*x2,    pvy*(x3-x2),pvz        ,rym,rz ,&lwe04l);
                                                                poly=erzeugennetz(netz,       pvy*x2,    pvx*(x1-x0),pvz        ,rxm,rz ,&lwe04d);netz->invertierenausrichtung(poly,rxm*rz);
                                                                //05
                                                                poly=erzeugennetz(netz,pvx*x1+pvy*x2,    pvx*(x2-x1),pvy*(x3-x2),rxq,rym,&lwe05f);
                                                                poly=erzeugennetz(netz,pvx*x1+pvy*x2+pvz,pvx*(x2-x1),pvy*(x3-x2),rxq,rym,&lwe05b);netz->invertierenausrichtung(poly,rxq*rym);
                                                                poly=erzeugennetz(netz,pvx*x1+pvy*x3,    pvx*(x2-x1),pvz        ,rxq,rz ,&lwe05u);
                                                                poly=erzeugennetz(netz,pvx*x1+pvy*x2,    pvx*(x2-x1),pvz        ,rxq,rz ,&lwe05d);netz->invertierenausrichtung(poly,rxq*rz);
                                                                //06
                                                                poly=erzeugennetz(netz,pvx*x2+pvy*x2,    pvx*(x3-x2),pvy*(x3-x2),rxm,rym,&lwe06f);
                                                                poly=erzeugennetz(netz,pvx*x2+pvy*x2+pvz,pvx*(x3-x2),pvy*(x3-x2),rxm,rym,&lwe06b);netz->invertierenausrichtung(poly,rxm*rym);
                                                                //07
                                                                poly=erzeugennetz(netz,pvx*x3+pvy*x2,    pvx*(x4-x3),pvy*(x3-x2),rxq,rym,&lwe07f);
                                                                poly=erzeugennetz(netz,pvx*x3+pvy*x2+pvz,pvx*(x4-x3),pvy*(x3-x2),rxq,rym,&lwe07b);netz->invertierenausrichtung(poly,rxq*rym);
                                                                poly=erzeugennetz(netz,pvx*x3+pvy*x3,    pvx*(x4-x3),pvz        ,rxq,rz ,&lwe07u);
                                                                poly=erzeugennetz(netz,pvx*x3+pvy*x2,    pvx*(x4-x3),pvz        ,rxq,rz ,&lwe07d);netz->invertierenausrichtung(poly,rxq*rz);
                                                                //08
                                                                poly=erzeugennetz(netz,pvx*x4+pvy*x2,    pvx*(x5-x4),pvy*(x3-x2),rxm,rym,&lwe08f);
                                                                poly=erzeugennetz(netz,pvx*x4+pvy*x2+pvz,pvx*(x5-x4),pvy*(x3-x2),rxm,rym,&lwe08b);netz->invertierenausrichtung(poly,rxm*rym);
                                                                poly=erzeugennetz(netz,pvx*x5+pvy*x2,    pvy*(x3-x2),pvz        ,rym,rz ,&lwe08r);netz->invertierenausrichtung(poly,rxm*rz);
                                                                poly=erzeugennetz(netz,pvx*x4+pvy*x3,    pvx*(x5-x4),pvz        ,rxm,rz ,&lwe08u);
                                                                //09
                                                                poly=erzeugennetz(netz,pvx*x2+pvy*x1,    pvx*(x3-x2),pvy*(x2-x1),rxm,ryq,&lwe09f);
                                                                poly=erzeugennetz(netz,pvx*x2+pvy*x1+pvz,pvx*(x3-x2),pvy*(x2-x1),rxm,ryq,&lwe09b);netz->invertierenausrichtung(poly,rxm*ryq);
                                                                poly=erzeugennetz(netz,pvx*x2+pvy*x1,    pvy*(x2-x1),pvz        ,ryq,rz ,&lwe09l);
                                                                poly=erzeugennetz(netz,pvx*x3+pvy*x1,    pvy*(x2-x1),pvz        ,ryq,rz ,&lwe09r);netz->invertierenausrichtung(poly,ryq*rz);
                                                                //10
                                                                poly=erzeugennetz(netz,pvz*x0,           pvx*(x2-x0),pvy*(x1-x0),rxw,rym,&lwe10f);
                                                                poly=erzeugennetz(netz,pvz,              pvx*(x2-x0),pvy*(x1-x0),rxw,rym,&lwe10b);netz->invertierenausrichtung(poly,rxw*rym);
                                                                poly=erzeugennetz(netz,pvz*x0,           pvy*(x1-x0),pvz        ,rym,rz ,&lwe10l);
                                                                poly=erzeugennetz(netz,pvy*x1,           pvx*(x2-x0),pvz        ,rxw,rz ,&lwe10u);
                                                                poly=erzeugennetz(netz,pvy*x0,           pvx*(x2-x0),pvz        ,rxw,rz ,&lwe10d);netz->invertierenausrichtung(poly,rxw*rz);
                                                                //11
                                                                poly=erzeugennetz(netz,pvx*x2,           pvx*(x3-x2),pvy*(x1-x0),rxm,rym,&lwe11f);
                                                                poly=erzeugennetz(netz,pvx*x2+pvz,       pvx*(x3-x2),pvy*(x1-x0),rxm,rym,&lwe11b);netz->invertierenausrichtung(poly,rxm*rym);
                                                                poly=erzeugennetz(netz,pvx*x3,           pvy*(x1-x0),pvz        ,rym,rz ,&lwe11r);netz->invertierenausrichtung(poly,rym*rz);
                                                                poly=erzeugennetz(netz,pvx*x2,           pvx*(x3-x2),pvz        ,rxm,rz ,&lwe11d);netz->invertierenausrichtung(poly,rxm*rz);
                                                                //12
                                                                poly=erzeugennetz(netz,pvx*x4,           pvx*(x5-x4),pvy*(x2-x0),rxm,ryw,&lwe12f);
                                                                poly=erzeugennetz(netz,pvx*x4+pvz,       pvx*(x5-x4),pvy*(x2-x0),rxm,ryw,&lwe12b);netz->invertierenausrichtung(poly,rxm*ryw);
                                                                poly=erzeugennetz(netz,pvx*x4,           pvy*(x2-x0),pvz        ,ryw,rz ,&lwe12l);
                                                                poly=erzeugennetz(netz,pvx*x5,           pvy*(x2-x0),pvz        ,ryw,rz ,&lwe12r);netz->invertierenausrichtung(poly,ryw*rz);
                                                                poly=erzeugennetz(netz,pvx*x4,           pvx*(x5-x4),pvz        ,rxm,rz ,&lwe12d);netz->invertierenausrichtung(poly,rxm*rz);
                                                                //-------------------------- WELD ----------------------------
                                                                duplizieren(&lwe00f,&lall);
                                                                duplizieren(&lwe00b,&lall);
                                                                duplizieren(&lwe00l,&lall);
                                                                duplizieren(&lwe00r,&lall);
                                                                duplizieren(&lwe00u,&lall);
                                                                duplizieren(&lwe01f,&lall);
                                                                duplizieren(&lwe01b,&lall);
                                                                duplizieren(&lwe01l,&lall);
                                                                duplizieren(&lwe01u,&lall);
                                                                duplizieren(&lwe02f,&lall);
                                                                duplizieren(&lwe02b,&lall);
                                                                duplizieren(&lwe02r,&lall);
                                                                duplizieren(&lwe02u,&lall);
                                                                duplizieren(&lwe02d,&lall);
                                                                duplizieren(&lwe03f,&lall);
                                                                duplizieren(&lwe03b,&lall);
                                                                duplizieren(&lwe03l,&lall);
                                                                duplizieren(&lwe03r,&lall);
                                                                duplizieren(&lwe04f,&lall);
                                                                duplizieren(&lwe04b,&lall);
                                                                duplizieren(&lwe04l,&lall);
                                                                duplizieren(&lwe04d,&lall);
                                                                duplizieren(&lwe05f,&lall);
                                                                duplizieren(&lwe05b,&lall);
                                                                duplizieren(&lwe05u,&lall);
                                                                duplizieren(&lwe05d,&lall);
                                                                duplizieren(&lwe06f,&lall);
                                                                duplizieren(&lwe06b,&lall);
                                                                duplizieren(&lwe07f,&lall);
                                                                duplizieren(&lwe07b,&lall);
                                                                duplizieren(&lwe07u,&lall);
                                                                duplizieren(&lwe07d,&lall);
                                                                duplizieren(&lwe08f,&lall);
                                                                duplizieren(&lwe08b,&lall);
                                                                duplizieren(&lwe08r,&lall);
                                                                duplizieren(&lwe08u,&lall);
                                                                duplizieren(&lwe09f,&lall);
                                                                duplizieren(&lwe09b,&lall);
                                                                duplizieren(&lwe09l,&lall);
                                                                duplizieren(&lwe09r,&lall);
                                                                duplizieren(&lwe10f,&lall);
                                                                duplizieren(&lwe10b,&lall);
                                                                duplizieren(&lwe10l,&lall);
                                                                duplizieren(&lwe10u,&lall);
                                                                duplizieren(&lwe10d,&lall);
                                                                duplizieren(&lwe11f,&lall);
                                                                duplizieren(&lwe11b,&lall);
                                                                duplizieren(&lwe11r,&lall);
                                                                duplizieren(&lwe11d,&lall);
                                                                duplizieren(&lwe12f,&lall);
                                                                duplizieren(&lwe12b,&lall);
                                                                duplizieren(&lwe12l,&lall);
                                                                duplizieren(&lwe12r,&lall);
                                                                duplizieren(&lwe12d,&lall);
                                                                //00
                                                                verschweissen(netz,lwe00f[0],lwe04f[2],&lall);
                                                                verschweissen(netz,lwe00f[1],lwe00r[0],&lall);
                                                                verschweissen(netz,lwe00f[2],lwe00u[0],&lall);
                                                                verschweissen(netz,lwe00f[3],lwe00l[0],&lall);
                                                                verschweissen(netz,lwe00b[0],lwe04b[2],&lall);
                                                                verschweissen(netz,lwe00b[1],lwe00r[2],&lall);
                                                                verschweissen(netz,lwe00b[2],lwe00u[2],&lall);
                                                                verschweissen(netz,lwe00b[3],lwe00l[2],&lall);
                                                                verschweissen(netz,lwe00l[1],lwe00u[3],&lall);
                                                                verschweissen(netz,lwe00l[3],lwe04l[1],&lall);
                                                                verschweissen(netz,lwe00r[1],lwe00u[1],&lall);
                                                                verschweissen(netz,lwe00r[3],lwe05u[3],&lall);
                                                                //02
                                                                verschweissen(netz,lwe02f[0],lwe02d[0],&lall);
                                                                verschweissen(netz,lwe02f[1],lwe02r[0],&lall);
                                                                verschweissen(netz,lwe02f[2],lwe02u[0],&lall);
                                                                verschweissen(netz,lwe02f[3],lwe01f[1],&lall);
                                                                verschweissen(netz,lwe02b[0],lwe02d[2],&lall);
                                                                verschweissen(netz,lwe02b[1],lwe02r[2],&lall);
                                                                verschweissen(netz,lwe02b[2],lwe02u[2],&lall);
                                                                verschweissen(netz,lwe02b[3],lwe01b[1],&lall);
                                                                verschweissen(netz,lwe02u[1],lwe02r[1],&lall);
                                                                verschweissen(netz,lwe02u[3],lwe01u[1],&lall);
                                                                verschweissen(netz,lwe02d[1],lwe02r[3],&lall);
                                                                verschweissen(netz,lwe02d[3],lwe03r[1],&lall);
                                                                //10
                                                                verschweissen(netz,lwe10f[0],lwe10d[0],&lall);
                                                                verschweissen(netz,lwe10f[1],lwe11f[3],&lall);
                                                                verschweissen(netz,lwe10f[2],lwe10u[0],&lall);
                                                                verschweissen(netz,lwe10f[3],lwe10l[0],&lall);
                                                                verschweissen(netz,lwe10b[0],lwe10d[2],&lall);
                                                                verschweissen(netz,lwe10b[1],lwe11b[3],&lall);
                                                                verschweissen(netz,lwe10b[2],lwe10u[2],&lall);
                                                                verschweissen(netz,lwe10b[3],lwe10l[2],&lall);
                                                                verschweissen(netz,lwe10u[1],lwe09l[3],&lall);
                                                                verschweissen(netz,lwe10u[3],lwe10l[1],&lall);
                                                                verschweissen(netz,lwe10d[1],lwe11d[3],&lall);
                                                                verschweissen(netz,lwe10d[3],lwe10l[3],&lall);
                                                                //12
                                                                verschweissen(netz,lwe12f[0],lwe12d[0],&lall);
                                                                verschweissen(netz,lwe12f[1],lwe12r[0],&lall);
                                                                verschweissen(netz,lwe12f[2],lwe08f[0],&lall);
                                                                verschweissen(netz,lwe12f[3],lwe12l[0],&lall);
                                                                verschweissen(netz,lwe12b[0],lwe12d[2],&lall);
                                                                verschweissen(netz,lwe12b[1],lwe12r[2],&lall);
                                                                verschweissen(netz,lwe12b[2],lwe08b[0],&lall);
                                                                verschweissen(netz,lwe12b[3],lwe12l[2],&lall);
                                                                verschweissen(netz,lwe12l[1],lwe07d[1],&lall);
                                                                verschweissen(netz,lwe12l[3],lwe12d[3],&lall);
                                                                verschweissen(netz,lwe12r[1],lwe08r[3],&lall);
                                                                verschweissen(netz,lwe12r[3],lwe12d[1],&lall);
                                                                //04
                                                                verschweissen(netz,lwe04f[0],lwe04d[0],&lall);
                                                                verschweissen(netz,lwe04f[1],lwe05f[3],&lall);
                                                                verschweissen(netz,lwe04f[3],lwe04l[0],&lall);
                                                                verschweissen(netz,lwe04b[0],lwe04d[2],&lall);
                                                                verschweissen(netz,lwe04b[1],lwe05b[3],&lall);
                                                                verschweissen(netz,lwe04b[3],lwe04l[2],&lall);
                                                                verschweissen(netz,lwe04l[3],lwe04d[3],&lall);
                                                                verschweissen(netz,lwe04d[1],lwe05d[3],&lall);
                                                                //01
                                                                verschweissen(netz,lwe01f[0],lwe03f[2],&lall);
                                                                verschweissen(netz,lwe01f[2],lwe01u[0],&lall);
                                                                verschweissen(netz,lwe01f[3],lwe01l[0],&lall);
                                                                verschweissen(netz,lwe01b[0],lwe03b[2],&lall);
                                                                verschweissen(netz,lwe01b[2],lwe01u[2],&lall);
                                                                verschweissen(netz,lwe01b[3],lwe01l[2],&lall);
                                                                verschweissen(netz,lwe01l[1],lwe01u[3],&lall);
                                                                verschweissen(netz,lwe01l[3],lwe03l[1],&lall);
                                                                //11
                                                                verschweissen(netz,lwe11f[0],lwe11d[0],&lall);
                                                                verschweissen(netz,lwe11f[1],lwe11r[0],&lall);
                                                                verschweissen(netz,lwe11f[2],lwe09f[0],&lall);
                                                                verschweissen(netz,lwe11b[0],lwe11d[2],&lall);
                                                                verschweissen(netz,lwe11b[1],lwe11r[2],&lall);
                                                                verschweissen(netz,lwe11b[2],lwe09b[0],&lall);
                                                                verschweissen(netz,lwe11r[1],lwe09r[3],&lall);
                                                                verschweissen(netz,lwe11r[3],lwe11d[1],&lall);
                                                                //08
                                                                verschweissen(netz,lwe08f[1],lwe08r[0],&lall);
                                                                verschweissen(netz,lwe08f[2],lwe08u[0],&lall);
                                                                verschweissen(netz,lwe08f[3],lwe07f[1],&lall);
                                                                verschweissen(netz,lwe08b[1],lwe08r[2],&lall);
                                                                verschweissen(netz,lwe08b[2],lwe08u[2],&lall);
                                                                verschweissen(netz,lwe08b[3],lwe07b[1],&lall);
                                                                verschweissen(netz,lwe08u[1],lwe08r[1],&lall);
                                                                verschweissen(netz,lwe08u[3],lwe07u[1],&lall);
                                                                //05
                                                                verschweissen(netz,lwe05f[0],lwe05d[0],&lall);
                                                                verschweissen(netz,lwe05f[1],lwe06f[3],&lall);
                                                                verschweissen(netz,lwe05f[2],lwe05u[0],&lall);
                                                                verschweissen(netz,lwe05b[0],lwe05d[2],&lall);
                                                                verschweissen(netz,lwe05b[1],lwe06b[3],&lall);
                                                                verschweissen(netz,lwe05b[2],lwe05u[2],&lall);
                                                                verschweissen(netz,lwe05u[1],lwe03l[3],&lall);
                                                                verschweissen(netz,lwe05d[1],lwe09l[1],&lall);
                                                                //07
                                                                verschweissen(netz,lwe07f[0],lwe07d[0],&lall);
                                                                verschweissen(netz,lwe07f[2],lwe07u[0],&lall);
                                                                verschweissen(netz,lwe07f[3],lwe06f[1],&lall);
                                                                verschweissen(netz,lwe07b[0],lwe07d[2],&lall);
                                                                verschweissen(netz,lwe07b[2],lwe07u[2],&lall);
                                                                verschweissen(netz,lwe07b[3],lwe06b[1],&lall);
                                                                verschweissen(netz,lwe07u[3],lwe03r[3],&lall);
                                                                verschweissen(netz,lwe07d[3],lwe09r[1],&lall);
                                                                //03
                                                                verschweissen(netz,lwe03f[0],lwe06f[2],&lall);
                                                                verschweissen(netz,lwe03f[1],lwe03r[0],&lall);
                                                                verschweissen(netz,lwe03f[3],lwe03l[0],&lall);
                                                                verschweissen(netz,lwe03b[0],lwe06b[2],&lall);
                                                                verschweissen(netz,lwe03b[1],lwe03r[2],&lall);
                                                                verschweissen(netz,lwe03b[3],lwe03l[2],&lall);
                                                                //09
                                                                verschweissen(netz,lwe09f[1],lwe09r[0],&lall);
                                                                verschweissen(netz,lwe09f[2],lwe06f[0],&lall);
                                                                verschweissen(netz,lwe09f[3],lwe09l[0],&lall);
                                                                verschweissen(netz,lwe09b[1],lwe09r[2],&lall);
                                                                verschweissen(netz,lwe09b[2],lwe06b[0],&lall);
                                                                verschweissen(netz,lwe09b[3],lwe09l[2],&lall);
                                                                //if(pruefenausrichtung()) netz->invertierenausrichtung();
                                                                if(pruefenausrichtung()) {
                                                                 if(netz->anfang(poly))do{
                                                                  poly->invertieren();
                                                                 }while(netz->naechstes(poly));
                                                                };//netz->invertierenausrichtung();
                                                                netz->aktualisieren(); 
                                                                lall.aushaengen();
                                                                lwe00f.loeschen();
                                                                lwe00b.loeschen();
                                                                lwe00l.loeschen();
                                                                lwe00r.loeschen();
                                                                lwe00u.loeschen();
                                                                lwe01f.loeschen();
                                                                lwe01b.loeschen();
                                                                lwe01l.loeschen();
                                                                lwe01u.loeschen();
                                                                lwe02f.loeschen();
                                                                lwe02b.loeschen();
                                                                lwe02r.loeschen();
                                                                lwe02u.loeschen();
                                                                lwe02d.loeschen();
                                                                lwe03f.loeschen();
                                                                lwe03b.loeschen();
                                                                lwe03l.loeschen();
                                                                lwe03r.loeschen();
                                                                lwe04f.loeschen();
                                                                lwe04b.loeschen();
                                                                lwe04l.loeschen();
                                                                lwe04d.loeschen();
                                                                lwe05f.loeschen();
                                                                lwe05b.loeschen();
                                                                lwe05u.loeschen();
                                                                lwe05d.loeschen();
                                                                lwe06f.loeschen();
                                                                lwe06b.loeschen();
                                                                lwe07f.loeschen();
                                                                lwe07b.loeschen();
                                                                lwe07u.loeschen();
                                                                lwe07d.loeschen();
                                                                lwe08f.loeschen();
                                                                lwe08b.loeschen();
                                                                lwe08r.loeschen();
                                                                lwe08u.loeschen();
                                                                lwe09f.loeschen();
                                                                lwe09b.loeschen();
                                                                lwe09l.loeschen();
                                                                lwe09r.loeschen();
                                                                lwe10f.loeschen();
                                                                lwe10b.loeschen();
                                                                lwe10l.loeschen();
                                                                lwe10u.loeschen();
                                                                lwe10d.loeschen();
                                                                lwe11f.loeschen();
                                                                lwe11b.loeschen();
                                                                lwe11r.loeschen();
                                                                lwe11d.loeschen();
                                                                lwe12f.loeschen();
                                                                lwe12b.loeschen();
                                                                lwe12l.loeschen();
                                                                lwe12r.loeschen();
                                                                lwe12d.loeschen();
                                                                netz->farbe(farbe());
                                                                netz->farbeverbinder(farbe());
                                                                
                                                                if(standardtextur()) erzeugenstandardtexturkoordinaten(netz);
                                                                netz->verschiebenvertex(ort());
                                                                return(netz);
};
 
void _geometriekreuzbalken::erzeugenstandardtexturkoordinaten(_netz*m){
                                                                _polygon*pit;
                                                                _vertex*vit;
                                                                _listenknoten<_vertex>*lnvit;
                                                                _verbindervertexpolygon*cvp[4];
                                                                int i;
                                                                _vektor2<_tg> h;
                                                                //-----------------------------
                                                                if(m->anfang(pit))do{
                                                                 i=0;
                                                                 //vit=pit->vertex();
                                                                 //do{
                                                                 iterierenliste(pit,lnvit,
                                                                  vit=lnvit->objekt();
                                                                  cvp[i]=static_cast<_verbindervertexpolygon*>(lnvit);//vit->connector(pit);
                                                                  i++;
                                                                 );
                                                                 // vit=vit->naechstes(pit);
                                                                 //}while(vit!=pit->vertex());
                                                                 
                                                                 h.setzen(0,0);
                                                                 cvp[0]->einfuegenvektor(0,h);
                                                                 h.setzen(1,0);
                                                                 cvp[1]->einfuegenvektor(0,h);
                                                                 h.setzen(1,1);
                                                                 cvp[2]->einfuegenvektor(0,h);
                                                                 h.setzen(0,1);
                                                                 cvp[3]->einfuegenvektor(0,h);
                                                                 
                                                                 
                                                                 
                                                                }while(m->naechstes(pit));
                                                                
                                                                
};
void _geometriekreuzbalken::einhaengendialog(_dynamischerdialog*d){
                                                                d->editierbar(this);
                                                                d->neusetzen(L"Kreuzbalken erzeugen");
                                                                
                                                                d->einhaengen(L"Konstruktionsparameter",L"Position",ort());
                                                                d->einhaengen(L"Konstruktionsparameter",L"Vektor Achse 0",vektor(0));
                                                                d->einhaengen(L"Konstruktionsparameter",L"Vektor Achse 1",vektor(1));
                                                                d->einhaengen(L"Konstruktionsparameter",L"Vektor Achse 2",vektor(2));
                                                                d->einhaengen(L"Konstruktionsparameter",L"Balkenbreite",pwidth);
                                                                //d->einhaengen(L"Konstruktionsparameter",L"Texturkoordinaten Verschiebung",ptcoffset);
                                                                d->einhaengen(L"Konstruktionsparameter",L"Geometrische Auflösung",presolution);
                                                                d->einhaengen(L"Konstruktionsparameter",L"Geometrische Auflösungsskalierung",aufloesungsskalierung());
                                                                d->einhaengen(L"Konstruktionsparameter",L"Farbe",farbe());
                                                                _zeichenkette<char> k="ni";
                                                                if(standardtextur()) d->einhaengen(L"Konstruktionsparameter",L"Textur",standardtextur()->name()); else d->einhaengen(L"Konstruktionsparameter",L"Textur",k);
};
void _geometriekreuzbalken::auslesendialog(_dynamischerdialog*d){
                                                                _vektor3<_tg> v,v0,v1,v2;
                                                                _vektor4<_to> f;
                                                                _tg sk;
                                                                d->auslesen(L"Konstruktionsparameter",L"Position",v);
                                                                ort(v);
                                                                d->auslesen(L"Konstruktionsparameter",L"Vektor Achse 0",v0);
                                                                d->auslesen(L"Konstruktionsparameter",L"Vektor Achse 1",v1);
                                                                d->auslesen(L"Konstruktionsparameter",L"Vektor Achse 2",v2);
                                                                vektor(v0,v1,v2);
                                                                d->auslesen(L"Konstruktionsparameter",L"Balkenbreite",pwidth);
                                                                //d->auslesen(L"Konstruktionsparameter",L"Texturkoordinaten Skalierung",ptclength);
                                                                //d->auslesen(L"Konstruktionsparameter",L"Texturkoordinaten Verschiebung",ptcoffset);
                                                                d->auslesen(L"Konstruktionsparameter",L"Geometrische Auflösung",presolution);
                                                                d->auslesen(L"Konstruktionsparameter",L"Geometrische Auflösungsskalierung",sk);
                                                                aufloesungsskalierung(sk);
                                                                d->auslesen(L"Konstruktionsparameter",L"Farbe",f);
                                                                farbe(f);
                                                               // _zeichenkette<char> k="ni";
                                                               // if(standardtextur()) d->einhaengen(L"Konstruktionsparameter",L"Textur",standardtextur()->name()); else d->einhaengen(L"Konstruktionsparameter",L"Textur",k);
};   
//******************************************************************************************************************************************************************************************************
//                                                              G E O M E T R I E K U G E L
//******************************************************************************************************************************************************************************************************
_geometriekugel::_geometriekugel(_listebasis<_geometrie >*lg,_vektor3<_tg> loc,_vektor3<_tg> vx,_vektor3<_tg> vy,_vektor3<_tg> vz,_textur<_tb>*tex):_geometrie(lg,loc,vx,vy,vz,tex),presolution(2){
                                                                presolution.setzen(3,3);
                                                                name("sphere");
};
 
_geometriekugel::~_geometriekugel(){
};

void _geometriekugel::aufloesung(unsigned int rx,unsigned int ry){
                                                                presolution.setzen(rx,ry);
                                                                if(presolution[0]<3) presolution.setzenkomponente(0,3);
                                                                if(presolution[1]<2) presolution.setzenkomponente(1,2);
                                                              //  presolution=r;
};
 
_netz* _geometriekugel::erzeugen(){
                                                                unsigned int rx;
                                                                unsigned int ry;
                                                                _liste<_schweisskante > lwecap0;
                                                                _liste<_schweisskante > lwecap1;
                                                                _liste<_schweisskante > lall;
                                                                _vektor3<_tg> o;
                                                                _netz*netz;
                                                                _polygon*poly;
                                                                //---------------------------------------
                                                                netz=new _netz();
                                                                rx=(unsigned int)(_tg(presolution[0])*aufloesungsskalierung());
                                                                ry=(unsigned int)(_tg(presolution[1])*aufloesungsskalierung());
                                                                o.setzen(0,0,0);
                                                                poly=erzeugenkugelschale(netz,o,vektor(0), vektor(1),vektor(2),rx,ry,&lwecap0);
                                                                o.setzen(0,0,0);
                                                                poly=erzeugenkugelschale(netz,o,vektor(0),-vektor(1),vektor(2),rx,ry,&lwecap1);
                                                                if(standardtextur()) erzeugenstandardtexturkoordinaten(netz);
                                                                netz->invertierenausrichtung(poly,rx*ry);
                                                                duplizieren(&lwecap0,&lall);
                                                                duplizieren(&lwecap1,&lall);
                                                                verschweissen(netz,lwecap0[0],lwecap1[0],&lall);
                                                               
                                                                
                                                                if(pruefenausrichtung()) {
                                                                 if(netz->anfang(poly))do{
                                                                  poly->invertieren();
                                                                 }while(netz->naechstes(poly));
                                                                };//netz->invertierenausrichtung();
                                                                netz->aktualisieren(); 
                                                                lall.aushaengen();
                                                                lwecap0.loeschen();
                                                                lwecap1.loeschen();
                                                                netz->farbe(farbe());
                                                                netz->farbeverbinder(farbe());
                                                                
                                                                netz->verschiebenvertex(ort());
                                                                return(netz);
};
 
void _geometriekugel::erzeugenstandardtexturkoordinaten(_netz*n){
																_vektor2<_tg> o(0.5f,0.5f);
																_vektor2<_tg> a(0.0f,0.5f);
																_vektor2<_tg> b(0.5f,0.0f);
                                                                unsigned int rx=(unsigned int)(_tg(presolution[0])*aufloesungsskalierung());
                                                                unsigned int ry=(unsigned int)(_tg(presolution[1])*aufloesungsskalierung());
																_polygon*p;
																if(n->anfang(p)){
																 p=erzeugentexturkoordinatenscheibe(p,o,a,b,rx,ry);
																 p=erzeugentexturkoordinatenscheibe(p,o,a,b,rx,ry);
																};
                                                                
};
void _geometriekugel::einhaengendialog(_dynamischerdialog*d){
                                                                d->editierbar(this);
                                                                d->neusetzen(L"Kreuzbalken erzeugen");
                                                                
                                                                d->einhaengen(L"Konstruktionsparameter",L"Position",ort());
                                                                d->einhaengen(L"Konstruktionsparameter",L"Vektor Achse 0",vektor(0));
                                                                d->einhaengen(L"Konstruktionsparameter",L"Vektor Achse 1",vektor(1));
                                                                d->einhaengen(L"Konstruktionsparameter",L"Vektor Achse 2",vektor(2));
                                                                d->einhaengen(L"Konstruktionsparameter",L"Geometrische Auflösung",presolution);
                                                                d->einhaengen(L"Konstruktionsparameter",L"Geometrische Auflösungsskalierung",aufloesungsskalierung());
                                                                d->einhaengen(L"Konstruktionsparameter",L"Farbe",farbe());
                                                                _zeichenkette<char> k="ni";
                                                                if(standardtextur()) d->einhaengen(L"Konstruktionsparameter",L"Textur",standardtextur()->name()); else d->einhaengen(L"Konstruktionsparameter",L"Textur",k);
};
void _geometriekugel::auslesendialog(_dynamischerdialog*d){
                                                                _vektor3<_tg> v,v0,v1,v2;
                                                                _vektor4<_to> f;
                                                                _tg sk;
                                                                d->auslesen(L"Konstruktionsparameter",L"Position",v);
                                                                ort(v);
                                                                d->auslesen(L"Konstruktionsparameter",L"Vektor Achse 0",v0);
                                                                d->auslesen(L"Konstruktionsparameter",L"Vektor Achse 1",v1);
                                                                d->auslesen(L"Konstruktionsparameter",L"Vektor Achse 2",v2);
                                                                vektor(v0,v1,v2);
                                                                d->auslesen(L"Konstruktionsparameter",L"Geometrische Auflösung",presolution);
                                                                d->auslesen(L"Konstruktionsparameter",L"Geometrische Auflösungsskalierung",sk);
                                                                aufloesungsskalierung(sk);
                                                                d->auslesen(L"Konstruktionsparameter",L"Farbe",f);
                                                                farbe(f);
                                                               // _zeichenkette<char> k="ni";
                                                               // if(standardtextur()) d->einhaengen(L"Konstruktionsparameter",L"Textur",standardtextur()->name()); else d->einhaengen(L"Konstruktionsparameter",L"Textur",k);
};   
//******************************************************************************************************************************************************************************************************
//                                                              G E O M E T R I E H A L B K U G E L
//******************************************************************************************************************************************************************************************************
_geometriehalbkugel::_geometriehalbkugel(_listebasis<_geometrie >*lg,_vektor3<_tg> loc,_vektor3<_tg> vx,_vektor3<_tg> vy,_vektor3<_tg> vz,_textur<_tb>*tex):_geometrie(lg,loc,vx,vy,vz,tex),presolution(2){
                                                                presolution.setzen(3,3);
                                                                name("hemisphere");
};
_geometriehalbkugel::~_geometriehalbkugel(){
};
void _geometriehalbkugel::aufloesung(_vektor<unsigned int> r){
                                                                if(r.holendimension()!=2) r.setzen(r[0],r[1]);
                                                                if(r[0]<3) r.setzenkomponente(0,3);
                                                                if(r[1]<2) r.setzenkomponente(1,2);
                                                                presolution=r;
};
_netz* _geometriehalbkugel::erzeugen(){
                                                                unsigned int rx;
                                                                unsigned int ry;
                                                                _liste<_schweisskante > lwecap0;
                                                                _liste<_schweisskante > lwedisc;
                                                                _liste<_schweisskante > lall;
                                                                _vektor3<_tg> o;
                                                                _netz*netz;
                                                                _polygon*poly;
                                                                //---------------------------------------
                                                                netz=new _netz();
                                                                rx=(unsigned int)(_tg(presolution[0])*aufloesungsskalierung());
                                                                ry=(unsigned int)(_tg(presolution[1])*aufloesungsskalierung());
                                                                o.setzen(0,0,0);
                                                                poly=erzeugenkugelschale(netz,o,vektor(0), vektor(1),vektor(2),rx,ry,&lwecap0);
                                                                o.setzen(0,0,0);
                                                                poly=erzeugenscheibe(netz,o,vektor(0),vektor(2),rx,&lwedisc);
                                                                netz->invertierenausrichtung(poly,rx);
                                                                duplizieren(&lwecap0,&lall);
                                                                duplizieren(&lwedisc,&lall);
                                                                verschweissen(netz,lwecap0[0],lwedisc[0],&lall);
                                                                if(pruefenausrichtung()) {
                                                                 if(netz->anfang(poly))do{
                                                                  poly->invertieren();
                                                                 }while(netz->naechstes(poly));
                                                                };//netz->invertierenausrichtung();
                                                                netz->aktualisieren(); 
                                                                lall.aushaengen();
                                                                lwecap0.loeschen();
                                                                lwedisc.loeschen();
                                                                netz->farbe(farbe());
                                                                netz->farbeverbinder(farbe());
                                                                
                                                                if(standardtextur()) erzeugenstandardtexturkoordinaten(netz);
                                                                netz->verschiebenvertex(ort());
                                                                return(netz);
};
 
void _geometriehalbkugel::erzeugenstandardtexturkoordinaten(_netz*){
                                                                
};
//******************************************************************************************************************************************************************************************************
//                                                              G E O M E T R I E T O R U S K N O T E N
//******************************************************************************************************************************************************************************************************
_geometrietorusknoten::_geometrietorusknoten(_listebasis<_geometrie >*lg,_vektor3<_tg> loc,_vektor3<_tg> vx,_vektor3<_tg> vy,_vektor3<_tg> vz,_textur<_tb>*tex):_geometrie(lg,loc,vx,vy,vz,tex),presolution(2){
                                                                presolution.setzen(3,3);
                                                                name("torusnode");
};
 
_geometrietorusknoten::~_geometrietorusknoten(){
};

void _geometrietorusknoten::aufloesung(_vektor<unsigned int> r){
                                                                if(r.holendimension()!=2) r.setzen(r[0],r[1]);
                                                                if(r[0]<3) r.setzenkomponente(0,3);
                                                                if(r[1]<2) r.setzenkomponente(1,2);
                                                                presolution=r;
};
 
_netz* _geometrietorusknoten::erzeugen(){
                                                                unsigned int rx;
                                                                unsigned int ry;
                                                                _liste<_schweisskante > lwecap0;
                                                                _liste<_schweisskante > lwedisc;
                                                                _liste<_schweisskante > lall;
                                                                _vektor3<_tg> o;
                                                                _netz*netz;
                                                                _polygon*poly;
                                                                //---------------------------------------
                                                                netz=new _netz();
                                                                rx=(unsigned int)(_tg(presolution[0])*aufloesungsskalierung());
                                                                ry=(unsigned int)(_tg(presolution[1])*aufloesungsskalierung());
                                                                o.setzen(0,0,0);
                                                                poly=erzeugentorusknoten(netz,o,vektor(0), vektor(1),vektor(2),rx,ry,&lwecap0);
                                                                /*
                                                                o.setzen(0,0,0);
                                                                poly=erzeugenscheibe(netz,o,vektor(0),vektor(2),rx,&lwedisc);
                                                                netz->invertierenausrichtung(poly,rx);
                                                                */
                                                                duplizieren(&lwecap0,&lall);
                                                                duplizieren(&lwedisc,&lall);
                                                                //verschweissen(netz,lwecap0[0],lwedisc[0],&lall);
                                                                if(pruefenausrichtung()) {
                                                                 if(netz->anfang(poly))do{
                                                                  poly->invertieren();
                                                                 }while(netz->naechstes(poly));
                                                                };//netz->invertierenausrichtung();
                                                                netz->aktualisieren(); 
                                                                lall.aushaengen();
                                                                lwecap0.loeschen();
                                                                lwedisc.loeschen();
                                                                netz->farbe(farbe());
                                                                netz->farbeverbinder(farbe());
                                                                
                                                                if(standardtextur()) erzeugenstandardtexturkoordinaten(netz);
                                                                netz->verschiebenvertex(ort());
                                                                return(netz);
};
 
void _geometrietorusknoten::erzeugenstandardtexturkoordinaten(_netz*){
                                                                
};
//******************************************************************************************************************************************************************************************************
//                                                              G E O M E T R I E G A N G
//******************************************************************************************************************************************************************************************************
 
_geometriegang::_geometriegang(_listebasis<_geometrie >*lg,_vektor3<_tg> p,_tg w0,_tg w1,_tg w2,_textur<_tb>*tex,_textur<_tb>*boden,_textur<_tb>*decke,_textur<_tb>*decke2):_geometrie(lg,p,tex){
                                                                presolution.setzen(1,1,1);
                                                                laenge(w0,w1,w2);
                                                                name("gang");
                                                                ptclength.setzen(1,1,1);
                                                                pboden=boden;
                                                                pdecke=decke;
                                                                pdeckenpanel=decke2;
                                                                prepeatx=1;
};
 
_geometriegang::_geometriegang(_listebasis<_geometrie >*lg,_vektor3<_tg> p,_vektor3<_tg> vx,_vektor3<_tg> vy,_vektor3<_tg> vz,_textur<_tb>*tex,_textur<_tb>*boden,_textur<_tb>*decke,_textur<_tb>*decke2):_geometrie(lg,p,vx,vy,vz,tex){
                                                                presolution.setzen(1,1,1);
                                                                name("gang");
                                                                ptclength.setzen(1,1,1);
                                                                pboden=boden;
                                                                pdecke=decke;
                                                                pdeckenpanel=decke2;
                                                                prepeatx=1;
};
 
_geometriegang::~_geometriegang(){
};

void _geometriegang::laenge(_tg w0,_tg w1,_tg w2){
                                                                _vektor3<_tg> vx;
                                                                _vektor3<_tg> vy;
                                                                _vektor3<_tg> vz;
                                                                //-----------------
                                                                vx.setzen(w0,0,0);
                                                                vy.setzen(0,w1,0);
                                                                vz.setzen(0,0,w2);
                                                                vektor(vx,vy,vz);
};

void _geometriegang::aufloesung(_vektor<unsigned int> r){
                                                                if(r[0]<1) r.setzenkomponente(0,1);
                                                                if(r[1]<1) r.setzenkomponente(1,1);
                                                                if(r[2]<1) r.setzenkomponente(2,1);
                                                                presolution=r;
};

void _geometriegang::iteration(const unsigned int r){
                                                                unsigned int i;
                                                                i=r;
                                                                if(i==0) i=1;
                                                                prepeatx=i;
};
 
_netz* _geometriegang::erzeugen(){
                                                                _geometriequader*gb;
                                                                _geometriequader*gsf;
                                                                _geometriequader*gsb;
                                                                _geometriequader*gsd;
                                                                _listebasis<_geometrie >*lgeometrie;
                                                                _netz*result;
                                                                _netz*netz;
                                                                _netz*meshf;
                                                                _netz*meshb;
                                                                _polygon*poly;
                                                                _tg f;
                                                                unsigned int dx;
                                                                _vektor<unsigned int> res;
                                                                _vektor3<_tg> ol;
                                                                _modifikationnetzintersektion ism;
                                                                _tg facx;
                                                                //---------------------------------
                                                                lgeometrie=_listenknotenbasis<_geometrie >::liste();
                                                                facx=(_tg(1.0f)/_tg(prepeatx));
                                                                gb=new _geometriequader(lgeometrie,ort(),vektor(0)*facx,vektor(1),vektor(2),standardtextur());
                                                                gb->aufloesung(presolution);
                                                                gb->texturkoordinatenlaenge(ptclength[0],ptclength[1],ptclength[2]);
                                                                gb->farbe(farbe());
                                                                gb->aufloesungsskalierung(aufloesungsskalierung());
                                                                
                                                                gsf=new _geometriequader(lgeometrie,ort(),vektor(0)*0.2*facx,vektor(1),vektor(2)*0.1,standardtextur());
                                                                res.setzen(1,presolution[1],1);
                                                                gsf->aufloesung(res);
                                                                gsf->texturkoordinatenlaenge(1,ptclength[1],1);
                                                                gsf->farbe(farbe());
                                                                gsf->aufloesungsskalierung(aufloesungsskalierung());
                                                                
                                                                gsb=new _geometriequader(lgeometrie,ort(),vektor(0)*0.2*facx,vektor(1),vektor(2)*0.1,standardtextur());
                                                                res.setzen(1,presolution[1],1);
                                                                gsb->aufloesung(res);
                                                                gsb->texturkoordinatenlaenge(ptclength[0]*0.2,ptclength[1],ptclength[2]*0.1);
                                                                gsb->farbe(farbe());
                                                                gsb->aufloesungsskalierung(aufloesungsskalierung());
                                                                
                                                                gsd=new _geometriequader(lgeometrie,ort(),vektor(0)*facx*(_tg(1.0f)/_tg(1.0f)),vektor(1)*0.05,vektor(2)*0.5,pdeckenpanel);
                                                                res.setzen(presolution[0],1,1);
                                                                gsd->aufloesung(res);
                                                                gsd->texturkoordinatenlaenge(ptclength[0],ptclength[1]*0.05,ptclength[2]*0.5);
                                                                gsd->farbe(farbe());
                                                                gsd->aufloesungsskalierung(aufloesungsskalierung());
                                                                
                                                                ol=ort();
                                                                result=0; 
                                                                for(dx=0;dx<prepeatx;dx++){
                                                                 f=_tg(dx)/_tg(prepeatx);
                                                                 gb->ort(ol+vektor(0)*f);
                                                                 netz=gb->erzeugen();
                                                                 netz->anfang(poly);
                                                                 poly->textur(pboden);
                                                                 poly=poly->naechstes();
                                                                 poly->textur(pdecke);
                                                                 
                                                                 gsf->ort(ol+vektor(0)*f+vektor(0)*facx*0.4);
                                                                 meshf=gsf->erzeugen();
                                                                 
                                                                 gsb->ort(ol+vektor(0)*f+vektor(0)*facx*0.4+vektor(2)*0.9);
                                                                 meshb=gsb->erzeugen();
                                                                 meshf->vereinigen(meshb);
                                                                 
                                                                 meshb=0;
                                                                 gsd->ort(ol+vektor(0)*(f/*-facx*0.2*/) + vektor(1)*0.95f+  vektor(2)*0.25f);
                                                                 meshb=gsd->erzeugen();
                                                                 
                                                                 ism.bearbeiten(meshf,meshb,2);
                                                                 delete meshb;
                                                                 meshb=0;
                                                                 
                                                                 
                                                                 ism.bearbeiten(netz,meshf,0);
                                                                 delete meshf;
                                                                 meshf=0;
                                                                 
                                                                 
                                                                 
                                                                 if(result==0) result=netz; else{
                                                                  ism.bearbeiten(result,netz,2);
                                                                  delete netz;
                                                                 };
                                                                 netz=0;
                                                                };
                                                                
                                                                
                                                                
                                                                
                                                                
                                                                
                                                                
                                                                result->subtraktiv(true);
                                                                delete gb;
                                                                delete gsf;
                                                                delete gsb;
                                                                delete gsd;
                                                                gb=0;
                                                                gsf=0;
                                                                gsb=0;
                                                                gsd=0;
                                                                return(result);
                                                                
};
 
void _geometriegang::erzeugenstandardtexturkoordinaten(_netz*){
};
 
void _geometriegang::texturkoordinatenlaenge(const _tg lx,const _tg ly,const _tg lz){
                                                                ptclength.setzen(lx,ly,lz);
};                                                                
//******************************************************************************************************************************************************************************************************
//                                                              G E O M E T R I E R A U M
//******************************************************************************************************************************************************************************************************
 
_geometrieraum::_geometrieraum(_listebasis<_geometrie >*lg,_vektor3<_tg> p,_tg w0,_tg w1,_tg w2,_textur<_tb>*tex,_textur<_tb>*boden,_textur<_tb>*decke,_textur<_tb>*decke2,_textur<_tb>*saeule):_geometrie(lg,p,tex){
                                                                presolution.setzen(1,1,1);
                                                                laenge(w0,w1,w2);
                                                                name("gang");
                                                                ptclength.setzen(1,1,1);
                                                                pboden=boden;
                                                                pdecke=decke;
                                                                pdeckenpanel=decke2;
                                                                psaeule=saeule;
};
 
_geometrieraum::_geometrieraum(_listebasis<_geometrie >*lg,_vektor3<_tg> p,_vektor3<_tg> vx,_vektor3<_tg> vy,_vektor3<_tg> vz,_textur<_tb>*tex,_textur<_tb>*boden,_textur<_tb>*decke,_textur<_tb>*decke2,_textur<_tb>*saeule):_geometrie(lg,p,vx,vy,vz,tex){
                                                                presolution.setzen(1,1,1);
                                                                name("gang");
                                                                ptclength.setzen(1,1,1);
                                                                pboden=boden;
                                                                pdecke=decke;
                                                                pdeckenpanel=decke2;
                                                                psaeule=saeule;
};
 
_geometrieraum::~_geometrieraum(){
};

void _geometrieraum::laenge(_tg w0,_tg w1,_tg w2){
                                                                _vektor3<_tg> vx;
                                                                _vektor3<_tg> vy;
                                                                _vektor3<_tg> vz;
                                                                //-----------------
                                                                vx.setzen(w0,0,0);
                                                                vy.setzen(0,w1,0);
                                                                vz.setzen(0,0,w2);
                                                                vektor(vx,vy,vz);
};

void _geometrieraum::aufloesung(_vektor<unsigned int> r){
                                                                if(r[0]<1) r.setzenkomponente(0,1);
                                                                if(r[1]<1) r.setzenkomponente(1,1);
                                                                if(r[2]<1) r.setzenkomponente(2,1);
                                                                presolution=r;
};
 
_netz* _geometrieraum::erzeugen(){
                                                                _geometriequader*gb;
                                                                _geometriequader*gsf;
                                                                _geometriequader*gsd;
                                                                _listebasis<_geometrie >*lgeometrie;
                                                                _netz*result;
                                                                _netz*netz;
                                                                _netz*meshf;
                                                                _netz*meshb;
                                                                //_netz*meshd;
                                                                _polygon*poly;
                                                                _vektor<unsigned int> res;
                                                                _modifikationnetzintersektion ism;
                                                                //---------------------------------
                                                                lgeometrie=_listenknotenbasis<_geometrie >::liste();
                                                                gb=new _geometriequader(lgeometrie,ort(),vektor(0),vektor(1)*0.875,vektor(2),standardtextur());
                                                                gb->aufloesung(presolution);
                                                                gb->texturkoordinatenlaenge(ptclength[0],ptclength[1],ptclength[2]);
                                                                gb->farbe(farbe());
                                                                gb->aufloesungsskalierung(aufloesungsskalierung());
                                                                
                                                                gsf=new _geometriequader(lgeometrie,ort(),vektor(0)*0.125,vektor(1)*0.875,vektor(2)*0.125,psaeule);
                                                                res.setzen(1,presolution[1],1);
                                                                gsf->aufloesung(res);
                                                                gsf->texturkoordinatenlaenge(ptclength[0]*0.125,ptclength[1],ptclength[2]*0.125);
                                                                gsf->farbe(farbe());
                                                                gsf->aufloesungsskalierung(aufloesungsskalierung());
                                                                
                                                                
                                                                gsd=new _geometriequader(lgeometrie,ort(),vektor(0)*0.75,vektor(1)*0.125,vektor(2)*0.75,pdeckenpanel);
                                                                res.setzen(presolution[0],1,1);
                                                                gsd->aufloesung(res);
                                                                gsd->texturkoordinatenlaenge(ptclength[0],ptclength[1]*0.125,ptclength[2]);
                                                                gsd->farbe(farbe());
                                                                gsd->aufloesungsskalierung(aufloesungsskalierung());
                                                                
                                                                result=0; 
                                                                gb->ort(ort());
                                                                netz=gb->erzeugen();
                                                                netz->anfang(poly);
                                                                poly->textur(pboden);
                                                                poly=poly->naechstes();
                                                                poly->textur(pdecke);
                                                                 
                                                                gsf->ort(ort());
                                                                meshf=gsf->erzeugen();
                                                                gsf->ort(ort()+vektor(0)*0.875);
                                                                meshb=gsf->erzeugen();
                                                                meshf->vereinigen(meshb);
                                                                gsf->ort(ort()+vektor(0)*0.875+vektor(2)*0.875);
                                                                meshb=gsf->erzeugen();
                                                                meshf->vereinigen(meshb);
                                                                gsf->ort(ort()+vektor(2)*0.875);
                                                                meshb=gsf->erzeugen();
                                                                meshf->vereinigen(meshb);
                                                                 
                                                                ism.bearbeiten(netz,meshf,0);
                                                                delete meshf;
                                                                meshf=0;
                                                                
                                                                gsd->ort(ort()+vektor(0)*0.125 + vektor(1)*0.875+  vektor(2)*0.125f);
                                                                meshb=gsd->erzeugen();
                                                                ism.bearbeiten(netz,meshb,2);
                                                                delete meshb;
                                                                meshb=0;
                                                                 
                                                                 
                                                                result=netz;                                                                 
                                                                netz=0;
                                                                result->subtraktiv(true);
                                                                delete gb;
                                                                delete gsf;
                                                                delete gsd;
                                                                gb=0;
                                                                gsf=0;
                                                                gsd=0;
                                                                return(result);
                                                                
};
 
void _geometrieraum::erzeugenstandardtexturkoordinaten(_netz*){
};
 
void _geometrieraum::texturkoordinatenlaenge(const _tg lx,const _tg ly,const _tg lz){
                                                                ptclength.setzen(lx,ly,lz);
};                                                                
//******************************************************************************************************************************************************************************************************
//                                                              V E R T E X Z E I G E R 
//******************************************************************************************************************************************************************************************************
_vertexzeiger::_vertexzeiger(){
                                                                pvertex=0;
};
 
void _vertexzeiger::setzen(_vertex*v){
                                                                pvertex=v;
};
 
_vertex* _vertexzeiger::holen(){
                                                                return(pvertex);
};
//******************************************************************************************************************************************************************************************************
//                                                              S C H W E I S S K A N T E
//******************************************************************************************************************************************************************************************************
_schweisskante::_schweisskante(){
};
 
_schweisskante::~_schweisskante(){
};
/*
 
void _schweisskante::einhaengen(_vertex*v){
                                                                if(v!=0) plist.einhaengen(v);
};
 
unsigned int _schweisskante::anzahl(){
                                                                return(plist.anzahl());
};*/
//******************************************************************************************************************************************************************************************************
//                                                              M O D I F I K A T I O N 
//******************************************************************************************************************************************************************************************************
/*_modifikation::_modifikation(_geometrie*g):_listenknotenbasis<_modifikation>(g){
                                                                pgeometry=g;
};*/
 _modifikation::_modifikation():_listenknotenbasis<_modifikation>(){
                                                                //pgeometry=0;
};
 _modifikation::~_modifikation(){
};
 void _modifikation::schreiben(_zeichenkette<char> m0){
                                                                L->schreiben(m0);
};
 void _modifikation::schreiben(_zeichenkette<char> m0,_zeichenkette<char> m1){
                                                                L->schreiben(m0,m1);
};
 void _modifikation::schreiben(_zeichenkette<char> m0,int i0){
                                                                L->schreiben(m0,i0);
};
 void _modifikation::schreiben(_zeichenkette<char> m0,_tg g){
                                                                L->schreiben(m0,g);
};
 void _modifikation::schreiben(_zeichenkette<char> m0,_vektor3<_tg> v){
                                                                L->schreiben(m0,v);
};
 void _modifikation::fehler(_zeichenkette<char> m0){
                                                                L->fehler(m0);
};
 void _modifikation::fehler(_zeichenkette<char> m0,_zeichenkette<char> m1){
                                                                L->fehler(m0,m1);
};
 void _modifikation::fehler(_zeichenkette<char> m0,int i0){
                                                                L->fehler(m0,i0);
};
 void _modifikation::fehler(_zeichenkette<char> m0,_tg g){
                                                                L->fehler(m0,g);
};
 void _modifikation::fehler(_zeichenkette<char> m0,_vektor3<_tg> i0){
                                                                L->fehler(m0,i0);
                                                             
};
