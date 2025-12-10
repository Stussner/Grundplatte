//******************************************************************************************************************************************************************************************************
//  Projekt      : grundplatte
//  Bibliothek   : _grundplatte.lib
//  Modul        : _weltfigur.cpp
//  Datum        : 09.01.2006
//  Beschreibung : 
//******************************************************************************************************************************************************************************************************
#include <_weltfigur.hpp>
#include <_weltpolygon.hpp>
//******************************************************************************************************************************************************************************************************
//                                                              F I G U R 
//******************************************************************************************************************************************************************************************************

_figur::_figur(_listebasis<_figur >*l,_welt*w,const _vektor3<_tg> o,_textur<_tb>*t):_listenknotenbasis<_figur >(l){
                                                                
                                                                plokus=o;
                                                                plokusalt=o;
                                                                pwelt=w;
                                                                ptextur=t;
                                                                pziel.setzen(0,0,0);
                                                                pstart.setzen(0,0,0);
                                                                unterwegs=false;
                                                                psectoraktuell=0;
                                                                pradius=0.75;
                                                                pgesundheit=1;
                                                                ppartei=1;
                                                                
};

_figur::~_figur(){
};

void _figur::bewegenplanlos(_partition::_zone*z){
                                                                //_partition::_polygon*pit;
                                                                //_partition::_polygon*portal;
                                                                _vektor3<_tg> i;
                                                                //bool loop;
                                                                //unsigned int pc;
                                                                //_tg zuf;
                                                                //----------------------------------------
                                                                
                                                                
                                                                


                                                                if(psectoraktuell==0){
                                                                 psectoraktuell=z->sektor(plokus);
                                                                };
                                                                
                                                                
                                                               /*
                                                                
                                                                if(unterwegs==true){
                                                                 //plokus+=pvektor;
                                                                 h=plokus-pstart;
                                                                 i=pziel-pstart;
                                                                 if(h.laenge()>i.laenge()) {
                                                                  unterwegs=false;
                                                                  psectoraktuell=0;
                                                                 };
                                                                };
                                                                if(unterwegs==false){
                                                                 //psectoraktuell=z->sektor(plokus);
                                                                 //if(psectoraktuell){
                                                                  pc=psectoraktuell->_listebasis<_partition::_polygon >::anzahl();
                                                                  zuf=pzufall.berechnen(0,pc+1);
                                                                  loop=true;
                                                                  if(psectoraktuell->anfang(pit)) for(n=0;n<(pc+int(zuf));n++){
                                                                   if(pit->portal()==true){
                                                                    unterwegs=true;
                                                                    portal=pit;
                                                                    //loop=false;
                                                                   };
                                                                   psectoraktuell->naechstes(pit);
                                                                  };
                                                                  if(unterwegs){
                                                                    h=portal->mitte()-plokus;
                                                                    h.normalisieren();
                                                                    pstart=plokus;
                                                                    pvektor=h*(0.08+(0.5-pgesundheit*0.5));
                                                                    pziel=portal->mitte()+h*0.0001;
                                                                  };
                                                                 //};
                                                                };
                                                                
                                                                
                                                                
                                                                */
                                                                
                                                                
                                                                
                                                                
                                                                
                                                                bool ref;
                                                                if(psectoraktuell) pvektor=psectoraktuell->bewegungsvektorreflektiv(plokus,pvektor,ref);
                                                                plokusalt=plokus;
                                                                plokus+=pvektor;
                                                                psectoraktuell=z->sektor(plokus);
                                                                if(psectoraktuell==0){
                                                                 plokus=plokusalt;
                                                                 psectoraktuell=z->sektor(plokus);
                                                                };


};                                                                

void _figur::bewegendefensiv(_partition::_zone*z){
                                                                _partition::_polygon*pit;
                                                                _partition::_polygon*portal;
                                                                _figur*fig;
                                                                _vektor3<_tg> i;
                                                                _vektor3<_tg> erwuenscht;
                                                                _tg c,bestes,nc;
                                                                _listesortiert<_partition::_polygon,_tg > lp;
                                                                _listenknotensortiert<_partition::_polygon,_tg >*lpit;
                                                                //----------------------------------------
                                                               
                                                                if(unterwegs==true){
                                                                 plokus+=pvektor;
                                                                 h=plokus-pstart;
                                                                 i=pziel-pstart;
                                                                 if(h.laenge()>i.laenge()) {
                                                                  plokus=pziel;
                                                                  unterwegs=false;
                                                                  psectoraktuell=0;
                                                                 };
                                                                };
                                                                if(unterwegs==false){
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 psectoraktuell=z->sektor(plokus);
                                                                 if(psectoraktuell){
                                                                  //erwuenscht-vektor berechnen
                                                                  erwuenscht.setzen(0,0,0);
                                                                  c=0;
                                                                  if(pwelt->anfang(fig))do{
                                                                   if(fig->partei()!=ppartei){
                                                                    h=plokus-fig->ort();
                                                                    h.normalisieren();
                                                                    erwuenscht+=h;
                                                                    c+=1;
                                                                   };
                                                                  }while(pwelt->naechstes(fig));
                                                                  if(c>0) erwuenscht*=_tg(1)/c; else erwuenscht.setzen(1,0,0);
                                                                  //bestes portal bestimmen
                                                                  lp.aushaengen();
                                                                  c=0;
                                                                  bestes=-1;
                                                                  portal=0;
                                                                  if(psectoraktuell->anfang(pit))do{
                                                                   if(pit->portal()==true){
                                                                    h=pit->mitte()-plokus;
                                                                    h.normalisieren();
                                                                    nc=h*erwuenscht;
                                                                    lp.einhaengen(pit,nc);
                                                                    if(nc>bestes){
                                                                     portal=pit;
                                                                     bestes=nc;
                                                                    };
                                                                   };
                                                                  }while(psectoraktuell->naechstes(pit));
                                                                  
                                                                  if(portal){
                                                                   lp.anfang(lpit);
                                                                   lp.vorheriges(lpit);
                                                                   if(zufall().berechnen(0,1)>0.5) lp.vorheriges(lpit);
                                                                   portal=lpit->objekt();
                                                                   
                                                                   unterwegs=true;
                                                                   h=portal->mitte()-plokus;
                                                                   h.normalisieren();
                                                                   pstart=plokus;
                                                                   pvektor=h*(0.08+(0.5-pgesundheit*0.5));
                                                                   pziel=portal->mitte()+h*0.0001;
                                                                  };
                                                                  lp.aushaengen();
                                                                 }else{
                                                                 };
                                                                };
};                                                                

void _figur::bewegenaggressiv(_partition::_zone*z){
                                                                _partition::_polygon*pit;
                                                                _partition::_polygon*portal;
                                                                _figur*fig;
                                                                _vektor3<_tg> i;
                                                                _vektor3<_tg> erwuenscht;
                                                                _tg c,bestes,nc;
                                                                //----------------------------------------
                                                               
                                                                if(unterwegs==true){
                                                                 plokus+=pvektor;
                                                                 h=plokus-pstart;
                                                                 i=pziel-pstart;
                                                                 if(h.laenge()>i.laenge()) {
                                                                  unterwegs=false;
                                                                  psectoraktuell=0;
                                                                 };
                                                                };
                                                                if(unterwegs==false){
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 psectoraktuell=z->sektor(plokus);
                                                                 if(psectoraktuell){
                                                                  //erwuenscht-vektor berechnen
                                                                  erwuenscht.setzen(0,0,0);
                                                                  c=0;
                                                                  if(pwelt->anfang(fig))do{
                                                                   if(fig->partei()!=ppartei){
                                                                    h=plokus-fig->ort();
                                                                    h.normalisieren();
                                                                    erwuenscht+=h;
                                                                    c+=1;
                                                                   };
                                                                  }while(pwelt->naechstes(fig));
                                                                  if(c>0) erwuenscht*=_tg(1)/c; else erwuenscht.setzen(1,0,0);
                                                                  erwuenscht*=-1;
                                                                  //bestes portal bestimmen
                                                                  c=0;
                                                                  bestes=-1;
                                                                  portal=0;
                                                                  if(psectoraktuell->anfang(pit))do{
                                                                   if(pit->portal()==true){
                                                                    h=pit->mitte()-plokus;
                                                                    h.normalisieren();
                                                                    nc=h*erwuenscht;
                                                                    if(nc>bestes){
                                                                     portal=pit;
                                                                     bestes=nc;
                                                                    };
                                                                   };
                                                                  }while(psectoraktuell->naechstes(pit));
                                                                  if(portal){
                                                                   unterwegs=true;
                                                                   h=portal->mitte()-plokus;
                                                                   h.normalisieren();
                                                                   pstart=plokus;
                                                                   pvektor=h*(0.08+(0.5-pgesundheit*0.5));
                                                                   pziel=portal->mitte()+h*0.0001;
                                                                  };
                                                                 };
                                                                };
};                                                                

void _figur::bewegen(const _vektor3<_tg>&vektor){
                                                                pvektor=vektor;
                                                                plokus+=vektor;
};

_tg _figur::kollidierenpartikel(_vektor3<_tg>&v){
                                                                _tg treffer;
                                                                _partikelquelle*qit;
                                                                //_partikel*pat;
                                                                
                                                                //--------------
                                                                v.setzen(0,0,0);
                                                                treffer=0;
                                                                if(pwelt->anfang(qit))do{
                                                                 /*if(qit->anfang(pat))do{
                                                                  if(pat->projektil()==true){
                                                                   h=pat->ort()-plokus;
                                                                   if(h.laenge()<=pradius){
                                                                    _vektoranalysis3<_tg> v3;
                                                                    _vektor3<_tg> e;
                                                                    v+=-h;
                                                                    v3.lotpunktgerade(pat->ort()-pat->vektor(),pat->ort(),h,e);
                                                                    //h=e+pat->vektor();
                                                                    pat->vektor()=e;
                                                                    treffer+=1;
                                                                   };
                                                                  };
                                                                 }while(qit->naechstes(pat));
                                                                 */
                                                                }while(pwelt->naechstes(qit));
                                                                return(treffer);
};


void _figur::einfuegentexturdetonation(_textur<_tb>*t){
                                                                ptexlistdetonation.einhaengen(t);
};

void _figur::einfuegentexturprojektil(_textur<_tb>*t){
                                                                ptexlistprojektil.einhaengen(t);
};

_tg _figur::partei()const{
                                                                return(ppartei);
};

void _figur::partei(const _tg p){
                                                                _tg t;
                                                                //--------
                                                                t=p;
                                                                ppartei=t;
};

_vektor3<_tg>&_figur::ort(){
                                                                return(plokus);
};

_vektor3<_tg>&_figur::vektor(){
                                                                return(pvektor);
};

void _figur::vektor(const _vektor3<_tg>&v){
                                                                pvektor=v;
}; 

_welt*_figur::welt(){
                                                                return(pwelt);
};

_zufallsgenerator<_tg>&_figur::zufall(){
                                                                return(pzufall);
};

_tg _figur::gesundheit()const{
                                                                return(pgesundheit);
};

void _figur::gesundheit(const _tg p){
                                                                if(p>1) pgesundheit=1; else pgesundheit=p;
};

void _figur::reduzierengesundheit(_tg red){
                                                                pgesundheit-=red;
};

_liste<_textur<_tb> >*_figur::texturdetonation(){
                                                                return(&ptexlistdetonation);
};

_liste<_textur<_tb> >*_figur::texturprojektil(){
                                                                return(&ptexlistprojektil);
};

_partition::_sektor*_figur::sektoraktuell(){
                                                                return(psectoraktuell);
};

void _figur::sektoraktuell(_partition::_sektor*s){
                                                                psectoraktuell=s;
};

_partition::_sektor*_figur::aktualisierensektor(_partition::_zone*z){
                                                                psectoraktuell=z->sektor(plokus);
                                                                return(psectoraktuell);
};

bool _figur::sichtbar(_figur*f){
                                                                _listenknoten<_partition::_sektor >*lsit;
                                                                bool vis;
                                                                //--------------
                                                                if((psectoraktuell)&&(f->sektoraktuell())){
                                                                 if(f->sektoraktuell()==psectoraktuell){
                                                                  return(true);
                                                                 }else{
                                                                  vis=false;
                                                                  if(psectoraktuell->sichtbarkeitsektor()->anfang(lsit))do{
                                                                   if(lsit->objekt()==f->sektoraktuell()){
                                                                    vis=true;
                                                                   };
                                                                  }while((psectoraktuell->sichtbarkeitsektor()->naechstes(lsit))&&(vis==false));
                                                                  return(vis);
                                                                 };
                                                                }else{
                                                                 return(false);
                                                                };
};
bool _figur::laden(_datei*d){
																ladenbeginn();
																return(true);
};
void _figur::speichern(_datei*d){
};
bool _figur::assoziieren(){
																if(zeigergeladen()){
																 loeschenzeiger();
																};
																return(true);
};
//******************************************************************************************************************************************************************************************************
//                                                              F I G U R S P R I T E 
//******************************************************************************************************************************************************************************************************

_figursprite::_figursprite(_listebasis<_figur >*l,_welt*w,_zeit*z,const _vektor3<_tg> o,_textur<_tb>*t):_figur(l,w,o,t){
                                                                _vektor3<_tg> vx;
                                                                _vektor3<_tg> vy;
                                                                _vektor3<_tg> vz;
                                                                _vektor3<_tg> h;
                                                                //----------------
                                                                pzeit=z;
                                                                plength[0]=0.1;
                                                                plength[1]=0.1;
                                                                vx.setzen(plength[0],0,0);
                                                                vy.setzen(0,plength[1],0);
                                                                psprite=new _sprite(w,w,o,vx,vy,t);
                                                                prot=0;
                                                                protvec=0;
                                                                partei(1);
                                                                h.setzen(0,0,0);
                                                                vx.setzen(0,1,0);
                                                                pwaffeq=new _partikelquellesprite(w,w,w,z,h,vx,100,0);
                                                                vx.setzen(0.0001,0,0);
                                                                vy.setzen(0,-0.0001,0);
                                                                vz.setzen(0,0,0.0001);
                                                                pwaffeq->ortraum(vx,vy,vz);
                                                                pwaffeq->vektortoleranz(0);
                                                                pwaffeq->groesse(0.3);
                                                                pwaffeq->groessetoleranz(0.7);
                                                                pwaffeq->aktiv(false);
                                                                pwaffeq->ort(h);
                                                                pwaffeq->vektor(h);
                                                                pwaffeq->kollisionreflektierend(1);
                                                              //  pwaffeq->projektil(true);
                                                                
};

_figursprite::~_figursprite(){
                                                                if(psprite) delete psprite;
                                                                if(pwaffeq) delete pwaffeq;
};

_partikelquelle*_figursprite::waffe(){
                                                                return(pwaffeq);
};


void _figursprite::zeichnen(_grafik*g,_kamera<_tg>*c){
                                                                if(psprite) psprite->zeichnen(g,c);
                                                                
};

void _figursprite::animieren(_partition::_zone*z,_tastatur*,_maus<_tg>*){
                                                                _figur*fig;
                                                                _tg treffer,wi,wi90;
                                                                _vektor3<_tg> vx;
                                                                _vektor3<_tg> vy;
                                                                _vektor3<_tg> h;
                                                                _vektor3<_tg> kollvek;
                                                                bool aktualisieren;
                                                                bool loop;
                                                                //-----------

                                                              /*  if(gesundheit()<0.2) {
                                                                 if(zufall().berechnen(0,1)<0.3) bewegenplanlos(z); else bewegendefensiv(z); 
                                                                }else{
                                                                 if(gesundheit()<0.95) {
                                                                  if(zufall().berechnen(0,1)<0.3) bewegenplanlos(z); else bewegenaggressiv(z);                                                                  
                                                                 }else{
                                                                 // if(zufall().berechnen(0,1)<0.5) bewegenplanlos(z); else bewegendefensiv(z);
                                                                  bewegenplanlos(z);
                                                                 };
                                                                };*/
                                                                bewegenplanlos(z);
                                                                treffer=kollidierenpartikel(kollvek);
                                                                vektor(vektor()+kollvek);
                                                                vektor(vektor()*0.99);
                                                                if(treffer>0){
                                                                  reduzierengesundheit(treffer*0.01);
                                                                  protvec+=zufall().berechnen(-10*treffer,10*treffer);
                                                                };
                                                                
                                                                aktualisieren=false;
                                                                if(fabs(protvec)<nahenull){
                                                                 protvec=0;
                                                                 if(fabs(prot)>10){
                                                                  if(prot<0) prot+=2; else prot-=2;
                                                                  aktualisieren=true;
                                                                 };
                                                                }else{
                                                                 prot+=protvec;
                                                                 protvec*=0.98;
                                                                 aktualisieren=true;
                                                                };
                                                                
                                                                if(aktualisieren){
                                                                 wi=prot*_ph;
                                                                 wi90=(prot+90)*_ph;
                                                                 vx.setzen(cos(wi)*plength[0],sin(wi)*plength[0],0);
                                                                 vy.setzen(cos(wi90)*plength[1],sin(wi90)*plength[1],0);
                                                                 psprite->ebene(vx,vy);
                                                                };
                                                                
                                                                
  
                                                                if(gesundheit()<=0){
                                                                 sprengen();
                                                                };

                                                                if(psprite){
                                                                 psprite->ort(ort());
                                                                };
                                                                
                                                                
                                                                //--------------------------------------- schusskontrolle --------------------------
                                                                if(pwaffeq->aktiv()){
                                                                 pwaffezeit-=1;
                                                                 if(pwaffezeit<0) {
                                                                  pwaffeq->aktiv(false);
                                                                 };
                                                                }else{
                                                                 
                                                                 if(gesundheit()<zufall().berechnen(0,1)){
                                                                  if(zufall().berechnen(0,1)<0.05){
                                                                   _figur*ziel;
                                                                   ziel=0;
                                                                   loop=true;
                                                                   if(welt()->anfang(fig))do{
                                                                    if(fig->partei()!=partei()){
                                                                     loop=false;
                                                                     ziel=fig;
                                                                     h=fig->ort()-ort();
                                                                     h.normalisieren();
                                                                     pwaffeq->vektor(h);
                                                                    };
                                                                   }while((welt()->naechstes(fig))&&(loop));
                                                                   if(ziel){
                                                                    if(sichtbar(ziel)){
                                                                     //feuer
                                                                     pwaffezeit=1;
                                                                     pwaffeq->aktiv(true);
                                                                     pwaffeq->ort(ort());
                                                                    };
                                                                   };
                                                                   
                                                                  };
                                                                 };
                                                                };
};

void _figursprite::sprengen(){
                                                                _partikelquellesprite*pq;
                                                                _listenknoten<_textur<_tb> >*tit;
                                                                _vektor3<_tg> vx;
                                                                _vektor3<_tg> h;
                                                                //------------------------------
																_listenknotenbasis<_figur>::loeschmarkierung(true);
                                                                 h=vektor();
                                                                 if(h.laenge()>(nahenull*2)) h.normalisieren(); else h.setzen(0,1,0);
                                                                 
                                                                 vx=h*zufall().berechnen(0.1,1);
                                                                 pq=new _partikelquellesprite(welt(),welt(),welt(),pzeit,ort(),vx,150,0);
                                                                 pq->generationsrate(10);
                                                                 pq->groesse(0.25);
                                                                 pq->groessetoleranz(0.6);
                                                                 pq->lebensdauer(3);
                                                                 pq->vektortoleranz(0.8);
                                                                 pq->kollisionreflektierend(1);
                                                                 pq->rotation(zufall().berechnen(-20,20));
                                                                 pq->rotationtoleranz(zufall().berechnen(0,1));
                                                                 if(texturdetonation()->anfang(tit))do{
                                                                  pq->einfuegentextur(tit->objekt());
                                                                 }while(texturdetonation()->naechstes(tit));
  };
//******************************************************************************************************************************************************************************************************
//                                                              F I G U R S P I E L E R 
//******************************************************************************************************************************************************************************************************

_figurspieler::_figurspieler(_listebasis<_figur >*l,_welt*w,_zeit*z,const _vektor3<_tg>&o):_figur(l,w,o,0){
                                                                _vektor3<_tg> h;
                                                                _vektor3<_tg> vx;
                                                                _vektor3<_tg> vy;
                                                                _vektor3<_tg> vz;
                                                                //----------
                                                                pzeit=z;
																pcam=new _kamera<_tg>(0);
                                                                pcam->ort(o);
                                                                pcam->aktualisieren();
                                                                h.setzen(-7,20,-7);
                                                                vx.setzen(0.2,-0.1,0.1);
                                                                pq=new _partikelquellesprite(w,w,w,z,0,h,vx,2400,0);
                                                                vx.setzen(0.0001,0,0);
                                                                vy.setzen(0,-0.0001,0);
                                                                vz.setzen(0,0,0.0001);
                                                                pq->ortraum(vx,vy,vz);
                                                                pq->vektortoleranz(0.1);
                                                                pq->groesse(0.3);
                                                                pq->groessetoleranz(0.7);
                                                                pspeed=0.1;
                                                                partei(0);
                                                                prot=0;
                                                                protvec=0;
};

_figurspieler::~_figurspieler(){
																delete pcam;
                                                                if(pq) delete pq;
};

void _figurspieler::zeichnen(_grafik*,_kamera<_tg>*){
};

_vektor3<_tg> _figurspieler::berechnenbewegung(_tastatur*kb,_tg pf){
                                                                _tg s=pspeed;
                                                                _vektor3<_tg> v;
                                                                _vektor3<_tg> r;
                                                                int i=0;
                                                                _tg pfactor;
                                                                //-------------
                                                                v.setzen(0,0,0);
                                                                r.setzen(0,0,0);
                                                                pfactor=pf;
                                                                s*=pfactor;
                                                                //----------------
                                                                if(kb->shift()) s*=8;
                                                                if(kb->pfeilhoch()){
                                                                 v=pcam->vektor();
                                                                 v.normalisieren();
                                                                 v*=s;
                                                                 i|=1;
                                                                 r+=v;
                                                                };
                                                                if(kb->pfeilrunter()){
                                                                 v=pcam->vektor();
                                                                 v.normalisieren();
                                                                 v*=-s;
                                                                 i|=1;
                                                                 r+=v;
                                                                };
                                                                if(kb->pfeillinks()){
                                                                 v=pcam->ebene(0);
                                                                 v.normalisieren();
                                                                 v*=-s;
                                                                 i|=1;
                                                                 r+=v;
                                                                };
                                                                if(kb->pfeilrechts()){
                                                                 v=pcam->ebene(0);
                                                                 v.normalisieren();
                                                                 v*=s;
                                                                 i|=1;
                                                                 r+=v;
                                                                };
                                                                /*if(i==1){
                                                                 pspeed*=1;
                                                                }else{ 
                                                                 pspeed=1;
                                                                };*/
                                                                return(r);
};

_vektor2<_tg> _figurspieler::berechnenrotation(_maus<_tg>*mo){
                                                                _vektor3<_tg> m;
                                                                _tg ms=0.1;
                                                               //------------
                                                                m=mo->holen()*ms;//*pfactor;
                                                                //protation.add(0,ms*m[0]);
                                                                //protation.add(1,ms*m[1]);
                                                                // aktualisieren();
                                                                return( _vektor2<_tg>(m[0],m[1]));
};


void _figurspieler::animieren(_partition::_zone*z,_tastatur*kb,_maus<_tg>*mo){

                                                                
                                                                
                                                                
                                                                _tg treffer;
                                                                bool aktualisieren;
                                                                bool kollidiert;
                                                                _vektor3<_tg> kollvek;
                                                                //----------------------------- spieler steuerung ------------------------------

                                                                treffer=kollidierenpartikel(kollvek);
                                                                kollvektor+=kollvek;
                                                                if(treffer>0){
                                                                  reduzierengesundheit(treffer*0.1);
                                                                //  pcam->rotrelativ(pcam->rotrelativ()+zufall().berechnen(-10*treffer,10*treffer));
                                                                //  pcam->yawrelativ(pcam->yawrelativ()+zufall().berechnen(-10*treffer,10*treffer));
                                                                  
                                                                };
                                                                
                                                                aktualisieren=false;
                                                                if(fabs(protvec)<(nahenull*100)){
                                                                 protvec=0;
                                                                 if(fabs(prot)>2){
                                                                  while(prot>360) prot-=360;
                                                                  while(prot<-360) prot+=360;
                                                                  if(prot<0) prot+=2; else prot-=2;
                                                                  aktualisieren=true;
                                                                 };
                                                                }else{
                                                                 prot+=protvec;
                                                                 protvec*=0.90;
                                                                 aktualisieren=true;
                                                                };
                                                                
                                                                if(aktualisieren){
                                                                 pcam->rol(prot);
                                                                };
                                                                
                                                                
                                                                
                                                                
                                                                
                                                                mv=berechnenbewegung(kb,z->zeitfaktor());
                                                                mv+=kollvektor;
                                                                kollvektor*=0.95;
                                                                rv=berechnenrotation(mo);
                                                                if(sektoraktuell()){
                                                                 _partition::_sektor*se;
                                                                 
                                                                 bewegen(   sektoraktuell()->bewegungsvektor(ort(),mv,se,kollidiert)    );
                                                                 sektoraktuell(se);
                                                                }else{
                                                                 bewegen(mv);
                                                                };
                                                                
                                                                pcam->ort(ort());
                                                                pcam->rotieren(rv);
																pcam->aktualisieren();
                                                                
                                                                pq->aktiv(false);
                                                                if(kb->knopflinks()) {
                                                                 pq->aktiv(true); 
                                                                 pq->vektortoleranz(0);
                                                                 pq->ort(*pcam - pcam->ebene(1)+pcam->vektor());
                                                                 _vektor3<_tg> hh=pcam->vektor();
                                                                 pq->vektor(hh*0.4f);
                                                                 pq->kollisionreflektierend(1);
                                                                 pq->kollisionabgleitend(0);
                                                                 //pq->projektil(true);
                                                                // pcam->yawrelativ(pcam->yawrelativ()+2);
                                                               //  pcam->yawrelativ(pcam->yawrelativ()*0.6);
                                                                 
                                                                };

                                                                if(kb->knopfrechts()) {
                                                                 pq->aktiv(true); 
                                                                 pq->vektortoleranz(0.05);
                                                                 pq->ort(*pcam - pcam->ebene(1)+pcam->vektor());
                                                                 pq->vektor(pcam->vektor()*0.4f);
                                                                 pq->kollisionreflektierend(0);
                                                                 pq->kollisionabgleitend(1);
                                                                 //projektil(true);
                                                               //  pcam->yawrelativ(2);
                                                               //  pcam->yawrelativ(pcam->yawrelativ()*0.6);
                                                                };
                                                                
                                                                
                                                                //------------------------------------------------------------------------------
                                                                if(gesundheit()<=0){
                                                                 protvec+=zufall().berechnen(-10*treffer,10*treffer);
                                                                 sprengen();
                                                                 gesundheit(1);
                                                                };
                                                                
                                                               // pcam->yawrelativ(pcam->yawrelativ()*0.8);
                                                               // pcam->rotrelativ(pcam->rotrelativ()*0.8);
};

void _figurspieler::sprengen(){
                                                                _partikelquellesprite*pqt;
                                                                _listenknoten<_textur<_tb> >*tit;
                                                                _vektor3<_tg> vx;
                                                                _vektor3<_tg> h;
                                                                //-------------------
                                                                  //loeschmarkierung(true);
                                                                 h=vektor();
                                                                 if(h.laenge()>(nahenull*2)) h.normalisieren(); else h.setzen(0,1,0);
                                                                 
                                                                 vx=h*zufall().berechnen(0.4,0.8);
                                                                 pqt=new _partikelquellesprite(welt(),welt(),welt(),pzeit,ort(),vx,180,0);
                                                                 pqt->generationsrate(30);
                                                                 pqt->groesse(0.25);
                                                                 pqt->groessetoleranz(0.6);
                                                                 pqt->lebensdauer(3);
                                                                 pqt->vektortoleranz(0.8);
                                                                 pqt->kollisionreflektierend(1);
                                                                 pqt->kollisionabgleitend(0);
                                                                 pqt->rotation(zufall().berechnen(-40,+40));
                                                                 pqt->rotationtoleranz(zufall().berechnen(0,1));
                                                                 if(texturdetonation()->anfang(tit))do{
                                                                  pqt->einfuegentextur(tit->objekt());
                                                                 }while(texturdetonation()->naechstes(tit));
};

_kamera<_tg>*_figurspieler::kamera(){
                                                                return(pcam);
};

_partikelquelle*_figurspieler::partikelquelle(){
                                                                return(pq);
};
