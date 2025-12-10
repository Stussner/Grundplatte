//******************************************************************************************************************************************************************************************************
//  Projekt      : grundplatte
//  Bibliothek   : _grundplatte.lib
//  Modul        : _weltmechanik.cpp
//  Datum        : 09.01.2006
//  Beschreibung : 
//******************************************************************************************************************************************************************************************************
#include <_weltmechanik.hpp>
#include <_weltpolygon.hpp>
//******************************************************************************************************************************************************************************************************
//                                              S K E L E T T
//******************************************************************************************************************************************************************************************************

_skelett::_skelett(_welt*w,const _vektor3<_tg>&o,const _vektor3<_tg>&r,const _vektor3<_tg>&n,const _vektor3<_tg>&s){
                                                plokus=o;
                                                pvektor[0]=r;
                                                pvektor[1]=n;
                                                pvektor[2]=s;
                                                pwelt=w;
                                                pcross=0;
};

_skelett::~_skelett(){
                                                unvisualisieren();
                                                pnetze.loeschen();
};                                     

_welt*_skelett::welt(){
                                                return(pwelt);
};           

_vektor3<_tg> _skelett::ort()const{
                                                return(plokus);
};

void _skelett::ort(_vektor3<_tg> v){
                                                plokus=v;
};
_vektor3<_tg>&_skelett::vektor(const unsigned int i){
                                                return(pvektor[i]);
};
_liste<_netz>*_skelett::netze(){
                                                return(&pnetze);
};
void _skelett::aktualisierennetze(){
                                                _listenknoten<_netz>*n;
                                                if(pnetze.anfang(n))do{
                                                 n->objekt()->aktualisieren();
                                                 n->objekt()->aktualisierenschatten();
                                                }while(pnetze.naechstes(n));    
};
void _skelett::bewegen(const _vektor3<_tg>&v){
                                                plokus+=v;
                                                //orte von allen kurven anpassen
                                                _extremitaet*eit;
                                                //_extremitaetssegment*esit;
                                                if(anfang(eit))do{
                                                // if(eit->anfang(esit))do{
                                                  eit->bewegen(v);
                                                // }while(eit->naechstes(esit));
                                                }while(naechstes(eit));
                                 
};

void _skelett::animieren(){
                                                _knochen*kit;
                                                _extremitaet*eit;
                                                //------------------------
                                                if(anfang(eit))do{
                                                 eit->animieren();
                                                }while(naechstes(eit));
                                                if(anfang(kit))do{
                                                 animieren(kit);
                                                }while(naechstes(kit));
};
void _skelett::animieren(_knochen*kit){
                                                _knochen*kii;
                                                //------------------------
                                                kit->animieren();
                                                if(kit->anfang(kii))do{
                                                 animieren(kii);
                                                }while(kit->naechstes(kii));
};
void _skelett::transformieren(const _vektor3<_tg>&v,_vektor3<_tg>&e){
                                                e=pvektor[0]*v[0] + pvektor[1]*v[1] + pvektor[2]*v[2];
};
void _skelett::nullsetzenvertexort(){
                                                _knochen*kit;
                                                //------------------------
                                                if(anfang(kit))do{
                                                 nullsetzenvertexort(kit);
                                                }while(naechstes(kit));
};
void _skelett::nullsetzenvertexort(_knochen*kit){
                                                _knochen*kii;
                                                _vertexkopplung*vkit;
                                                //------------------------
                                                if(kit->anfang(vkit))do{
                                                 vkit->vertex()->ort(0,0,0);
                                                }while(kit->naechstes(vkit));
                                                if(kit->anfang(kii))do{
                                                 nullsetzenvertexort(kii);
                                                }while(kit->naechstes(kii));
};
void _skelett::transformierenvertex(){
                                                _knochen*kit;
                                                //------------------------
                                                nullsetzenvertexort();
                                                if(anfang(kit))do{
                                                 transformierenvertex(plokus,kit);
                                                }while(naechstes(kit));
};
void _skelett::transformierenvertex(const _vektor3<_tg>&ort,_knochen*kit){
                                                _knochen*kii;
                                                _vertexkopplung*vkit;
                                                //_vertex*vit;
                                                //------------------------
                                                _vektor3<_tg> n;
                                                if(kit->anfang(vkit))do{
                                                 kit->transformieren(ort,vkit);
                                                
                                                
                                                }while(kit->naechstes(vkit));
                                                //rekursion
                                                _vektor3<_tg> o=ort+kit->vektor();
                                                if(kit->anfang(kii))do{
                                                 transformierenvertex(o,kii);
                                                }while(kit->naechstes(kii));
};
void _skelett::assoziieren(_liste<_netz>*ln,const _vektor3<_tg>&ort,_knochen*wurzel,bool rekursiv){
                                                _listenknoten<_netz>*nit;
                                                if(ln->anfang(nit))do{
                                                 assoziieren(nit->objekt(),ort,wurzel,rekursiv);
                                                }while(ln->naechstes(nit));
};
void _skelett::assoziieren(_netz*n,const _vektor3<_tg>&ort,_knochen*wurzel,bool rekursiv){
                                                _polygon*pit;
                                                _vertex*vit;
                                                _listenknoten<_vertex>*lnvit;
                                                _liste<_vertexkopplung> lvk;
                                                //--------------------
                                                pnetze.einhaengen(n);
                                                //n->markierungvertex(0);
                                                 //vit=pit->vertex();
                                                 //if(vit)do{
                                                 //iterierenliste(pit,lnvit,
                                                 // vit=lnvit->objekt();
                                                 // if(vit->markierung()==0){
                                                 //  vit->markierung(1);
                                                iterierenliste(n,vit,
                                                 lvk.aushaengen();
                                                 assoziieren(vit,ort,wurzel,&lvk,rekursiv);
                                                 if(lvk.anzahl()>0){
                                                  if(lvk.anzahl()>1){
                                                   _tg g=0;
                                                   _tg z=0;
                                                   _listenknoten<_vertexkopplung>*vkit;
                                                   if(lvk.anfang(vkit))do{
                                                    g+=vkit->objekt()->anteil();
                                                    z+=1;
                                                   }while(lvk.naechstes(vkit));
                                                   g/=z;
                                                   if(lvk.anfang(vkit))do{
                                                   // vkit->objekt()->anteil(g);
                                                   }while(lvk.naechstes(vkit));
                                                  };
                                                 }else{
                                                  //noch nichts diskretes gefunden
                                                 };
                                                );
                                                 // vit=vit->naechstes(pit);
                                                 //}while(vit!=pit->vertex());
                                                //}while(n->naechstes(pit));
};
void _skelett::assoziieren(_vertex*vit,const _vektor3<_tg>&ort,_knochen*k,_liste<_vertexkopplung>*lvk,bool rekursiv){
                                                _vektor3<_tg> neuort;
                                                _vektor3<_tg> lot;
                                                _tg p;
                                                //assoziation ausführen
                                                neuort=ort+k->vektor();
                                                va.lotpunktgerade(vit->ort(),ort,k->vektor(),lot,p);
                                                if((p>(-nahenull*4))&&(p<(1+nahenull*4))){
                                                 lvk->einhaengen(new _vertexkopplung(k,ort,vit,lot.laenge(),p));
                                                };
                                                //rekursion
                                                if(rekursiv){
                                                 _knochen*kit;
                                                 iterierenliste(k,kit,assoziieren(vit,neuort,kit,lvk,rekursiv));
                                                };
                                                
};
_vektor3<_tg> _skelett::schwerpunkt()const{
                                                _knochen*kit;
                                                _vektor3<_tg> v;
                                                _tg gm;
                                                //----------------
                                                v.setzen(0,0,0);
                                                gm=0;
                                                if(anfang(kit))do{
                                                 schwerpunkt(kit,v,gm);
                                                }while(naechstes(kit));
                                                v*=(1.0f/gm);
                                                //v+=plokus;
                                                return(v);
};                                                

_vektor3<_tg> _skelett::schwerpunkt(_knochen*kit,_vektor3<_tg>&v,_tg&gm)const{
                                                _knochen*kii;
                                                //--------------------
                                                if(kit->anfang(kii))do{
                                                 schwerpunkt(kii,v,gm);
                                                }while(kit->naechstes(kii));
                                                gm+=kit->masse();
                                                v+=kit->ort()*kit->masse();
                                                return(v);
};
void _skelett::visualisieren(){
                                                _knochen*kit;
                                                _vektor4<_to> col;
                                                //-----------------
                                                unvisualisieren();
                                                if(anfang(kit))do{
                                                 kit->visualisieren(/*plokus*/);
                                                }while(naechstes(kit));
                                                col.setzen(0,0,1,0);
                                                pcross=new _weltdebugkreuz(pwelt,schwerpunkt(),0.04,col);
};                                
void _skelett::unvisualisieren(){
                                                _knochen*kit;
                                                //-----------------
                                                if(anfang(kit))do{
                                                 kit->unvisualisieren();
                                                }while(naechstes(kit));
                                                if(pcross) delete pcross;
                                                pcross=0;
};                
//******************************************************************************************************************************************************************************************************
//                                              K N O C H E N
//******************************************************************************************************************************************************************************************************
_knochen::_knochen(_skelett*s,_listebasis<_knochen >*l,_knochen*k,_vektor3<_tg> v):_listelistenknotenbasis<_knochen >(l){
                                                pknochen=k;
                                                pvektor=v;
                                                pvektororiginal=v;
                                                plaengeoriginal=pvektororiginal.laenge();
                                                pkollision=false;
                                                pskelett=s;
                                                prollwert=0;
                                                _vektoranalysis3<_tg> V3;
                                                V3.berechnenorthogonalenvektor(pvektor,pva);
                                                pva.normalisieren();
                                                pvb=pva % pvektor;
                                                pvb.normalisieren();
                                                pmasse=1;
                                                plokusaktuell=false;
                                                plokusspitzeaktuell=false;
                                                ort();
                                                ortspitze();
                                                //zu diesem zeitpunkt liegt der knochenraum in form von pvektor,pva,pvb vor
                                                parrow=0;
                                                parrowa=0;
                                                parrowb=0;
};
_knochen::~_knochen(){
                                                unvisualisieren();
};
void _knochen::animieren(){
};

void _knochen::transformieren(const _vektor3<_tg>&ort,_vertexkopplung*vk){
                                                 vk->vertex()->ort(vk->vertex()->ort()+ort+( pvektor*vk->alpha() + pva*vk->beta() + pvb*vk->gamma())*vk->anteil());
};                                                 
_skelett*_knochen::skelett(){
                                                return(pskelett);
};
_knochen*_knochen::knochen(){
                                                return(pknochen);
};
_vektor3<_tg> _knochen::ort(){
                                                /*if(plokusaktuell){
                                                 return(plokus);
                                                }else*/{
                                                 _vektor3<_tg> v;
                                                 _knochen*kit;  
                                                 _vektor3<_tg> kitvn;  
                                                 //------------------------
                                                 //v=pvektor;
                                                 v.setzen(0,0,0);
                                                 kit=pknochen;
                                                 while(kit){
                                                  //v+=_vektor3<_tg>(1,0,0);
                                                /*  kitvn=kit->pvektor;
                                                  kitvn.normalisieren();
                                                  v= kitvn*v[0] + kit->pva*v[1] + kit->pvb*v[2];*/
                                                  v+=kit->pvektor;
                                                  kit=kit->pknochen;
                                                 };
                                                 v+=pskelett->ort();
                                                 /*
                                                 _vektor3<_tg> v;
                                                 _knochen*kit;    
                                                 //------------------------
                                                 v.setzen(0,0,0);
                                                 kit=pknochen;
                                                 while(kit){
                                                  v=v+pknochen->pvektortrans;
                                                  kit=kit->pknochen;
                                                 };*/
                                                 plokus=v;
                                                 plokusaktuell=true;
                                                 return(v);
                                                };
};
_vektor3<_tg> _knochen::ortspitze(){
                                               /* if(plokusspitzeaktuell){
                                                 return(plokusspitze);
                                                }else*/{
                                                 _vektor3<_tg> v;
                                                 _knochen*kit;    
                                                 _vektor3<_tg> kitvn;  
                                                 //------------------------
                                                 v=pvektor;
                                                 kit=pknochen;
                                                 while(kit){
                                                 /* kitvn=kit->pvektor;
                                                  kitvn.normalisieren();
                                                  v= kitvn*v[0] + kit->pva*v[1] + kit->pvb*v[2];*/
                                                  v+=kit->pvektor;
                                                  kit=kit->pknochen;
                                                 };
                                                 v+=pskelett->ort();
                                                 plokusspitze=v;
                                                 plokusspitzeaktuell=true;
                                                 return(v);
                                                };
};
_tg _knochen::masse()const{
                                                return(pmasse);
};
void _knochen::masse(const _tg m){
                                                pmasse=m;
};
void _knochen::speichernort(_knochen*kit){
                                                //funktion speichert die koordinaten des knochens this
                                                //in form von parametern des knochens kit ab
                                                _vektor3<_tg> e;
                                                _vektor3<_tg> vn;
                                                _vektoranalysis3<_tg> V3;
                                                _tg D;
                                                //--------------------
                                                vn=kit->pvektor;
                                                vn.normalisieren();
                                                D=V3.determinieren(vn,kit->pva,kit->pvb);
                                                e=pvektor;
                                                pparameter.setzen(
                                                V3.determinieren(e,kit->pva,kit->pvb)/D,
                                                V3.determinieren(vn,e,kit->pvb)/D,
                                                V3.determinieren(vn,kit->pva,e)/D);
                                                _knochen*kii;
                                                if(anfang(kii))do{
                                                 kii->speichernort(kit);
                                                }while(naechstes(kii));
};
void _knochen::speichernort(){
                                                _knochen*kit;
                                                //-------------
                                                if(anfang(kit))do{
                                                 kit->speichernort(this);
                                                }while(naechstes(kit));
};
void _knochen::ladenort(_knochen*kit){
                                                //funktion lädt die koordinaten des knochens this
                                                //anhand der vorher festgelegt parameter des knochens kit
                                                _vektor3<_tg> vn;
                                                _vektor3<_tg> l;
                                                _vektor3<_tg> ls;
                                                //------------------
                                                vn=kit->pvektor;
                                                vn.normalisieren();
                                                pvektor=vn*pparameter[0] + kit->pva*pparameter[1] + kit->pvb*pparameter[2];
                                                _knochen*kii;
                                                if(anfang(kii))do{
                                                 kii->ladenort(kit);
                                                }while(naechstes(kii));
};
void _knochen::ladenort(){
                                                _knochen*kit;
                                                //-------------
                                                if(anfang(kit))do{
                                                 kit->ladenort(this);
                                                }while(naechstes(kit));
};
void _knochen::rotierenx(_tg w){
                                                speichernort();
                                                pvektor.rotx(w);
                                                ladenort();
};
void _knochen::visualisieren(){
                                                _knochen*kit;
                                                _gelenk*git;
                                                _vektor3<_tg> o;
                                                _vektor3<_tg> om;
                                                //---------------
                                                unvisualisieren();
                                                o=ort();
                                                om=o+pvektor*0.5;
                                                parrow =new _weltdebugpfeil(pskelett->welt(),o,o+pvektor,0.03,0.02,_vektor4<_to>(0.3f,1,0.05f,0));
                                                parrowa=new _weltdebugpfeil(pskelett->welt(),om,om+pva*0.22,0.01,0.0031,_vektor4<_to>(1,0.5,0,1));
                                                parrowb=new _weltdebugpfeil(pskelett->welt(),om,om+pvb*0.22,0.01,0.0031,_vektor4<_to>(0,0.5,1,1));
                                                if(anfang(kit))do{
                                                 kit->visualisieren(/*o+pvektortrans*/);
                                                }while(naechstes(kit));
                                                if(anfang(git))do{
                                                 git->visualisieren(o);
                                                }while(naechstes(git));
};

void _knochen::unvisualisieren(){
                                                if(parrow) delete parrow;
                                                parrow=0;
                                                if(parrowa) delete parrowa;
                                                parrowa=0;
                                                if(parrowb) delete parrowb;
                                                parrowb=0;
};
/*
void _knochen::bewegen(){
                                                pvektor=pvektorneu;
};*/
/*

void _knochen::transformieren(){
                                                _gelenk*git;
                                                _knochen*kit;
                                                _vektoranalysis3<_tg> V3;
                                                _vektor3<_tg> e;
                                                //--------- vektorraumtransformation von pvektor, pva , pvb
                                                pvektortrans=pvektor;//ruecksetzen();
                                                pvatrans=pva;
                                                pvbtrans=pvb;
                                                if(anfang(git))do{
                                                 V3.rotieren(git->pachse,pvektortrans,git->pwinkel,e);
                                                 pvektortrans=e;
                                                 V3.rotieren(git->pachse,pvatrans,git->pwinkel,e);
                                                 pvatrans=e;
                                                 V3.rotieren(git->pachse,pvbtrans,git->pwinkel,e);
                                                 pvbtrans=e;
                                                }while(naechstes(git));
                                                kit=this;
                                                while(kit->pknochen!=0){
                                                 kit=kit->pknochen;
                                                 if(kit->anfang(git))do{
                                                  V3.rotieren(git->pachse,pvektortrans,git->pwinkel,e);
                                                  pvektortrans=e;
                                                  V3.rotieren(git->pachse,pvatrans,git->pwinkel,e);
                                                  pvatrans=e;
                                                  V3.rotieren(git->pachse,pvbtrans,git->pwinkel,e);
                                                  pvbtrans=e;
                                                 }while(kit->naechstes(git));
                                                };
                                                //gelenke transformieren, nur zur visualisierung
                                                if(anfang(git))do{
                                                 git->transformieren();
                                                }while(naechstes(git));
};*/
//******************************************************************************************************************************************************************************************************
//                                               V E R T E X K O P P L U N G
//******************************************************************************************************************************************************************************************************
_vertexkopplung::_vertexkopplung(_knochen*k,const _vektor3<_tg>&ort,_vertex*v,_tg abstand,_tg para):_listenknotenbasis<_vertexkopplung>(k){
                                                _tg D;
                                                _vektoranalysis3<_tg> va;
                                                //-----------------------
                                                pvertex=v;
                                                panteil=1;
                                                pabstand=abstand;
                                                palpha=para;
                                                pbeta=0.5;
                                                pgamma=0.4;
                                                D=va.determinieren(k->vektor(),k->ebene0(),k->ebene1());
                                                if(fabs(D)<nahenull) L->schreiben("Fehler : Hauptdeterminate eines Knochenraumes ist zu klein"); else{
                                                 pbeta= va.determinieren(k->vektor(),v->ort()-ort,k->ebene1())/D;
                                                 pgamma=va.determinieren(k->vektor(),k->ebene0(),v->ort()-ort)/D;
                                                };
};
_vertexkopplung::~_vertexkopplung(){
};
_vertex*_vertexkopplung::vertex(){
                                                return(pvertex);
};
void _vertexkopplung::anteil(const _tg a){
                                                panteil=a;
};
_tg _vertexkopplung::anteil()const{
                                                return(panteil);
};
_tg _vertexkopplung::abstand()const{
                                                return(pabstand);
};
_tg _vertexkopplung::alpha()const{
                                                return(palpha);
};
_tg _vertexkopplung::beta()const{
                                                return(pbeta);
};
_tg _vertexkopplung::gamma()const{
                                                return(pgamma);
};
//******************************************************************************************************************************************************************************************************
//                                             E X T R E M I T A E T 
//******************************************************************************************************************************************************************************************************

_extremitaet::_extremitaet(_skelett*s,_knochen*w):_listenknotenbasis<_extremitaet>(s){
                                                pskelett=s;
                                                pwurzel=w;                                                
                                                plaengemax=0;
                                                _kurvehermite3<_tg>::vektor(0,_vektor3<_tg>(0,0,0));
                                                _kurvehermite3<_tg>::vektor(1,_vektor3<_tg>(0,0,0));
                                            /*    prichtung[0]=prichtungtransformiert[0]=v0;
                                                prichtung[1]=prichtungtransformiert[1]=v1;
                                                prichtung[2]=prichtungtransformiert[2]=v2;       */
                                                
                                                for(int i=0;i<2;i++){
                                                 panimationortaktivitaet[i]=false;//schaltet die jeweiligen animation aktiv
                                                 panimationvektoraktivitaet[i]=false;
                                                 panimationortiterator[2]=0;
                                                 panimationvektoriterator[2]=0;
                                                 panimationortschritt[i]=0.1;
                                                 panimationvektorschritt[i]=0.1;
                                                };
                                                pinterpolationsmodus=0;

};
_extremitaet::~_extremitaet(){
                                                pks.loeschen();
                                                pkd.loeschen();
                                                unvisualisieren();
};
void _extremitaet::einhaengen(_knochen*k){
                                                psequenz.einhaengen(k);
                                                plaengemax+=k->laengeoriginal();
                                                pks.einhaengen(new _kurvehermite3<_tg>());
                                                pkd.einhaengen(new _kurvehermite3<_tg>());
};
_liste<_knochen>*_extremitaet::knochenliste(){
                                                return(&psequenz);
};
void _extremitaet::initialisierenraum(const _tg laenge){
                                                _listenknoten<_knochen>*kit;
                                                //---------------------------
                                                
                                                prichtung[0].setzen(0,0,0);
                                                if(psequenz.anfang(kit))do{
                                                 prichtung[0]+=kit->objekt()->vektor();
                                                }while(psequenz.naechstes(kit));
                                                prichtung[0].normalisieren();
                                                prichtung[0]*=laenge;
                                                _vektoranalysis3<_tg> va;
                                                va.berechnenorthogonalenvektor(prichtung[0],prichtung[1]);
                                                prichtung[2]=prichtung[0]%prichtung[1];
                                                prichtung[1].normalisieren();
                                                prichtung[2].normalisieren();
                                                for(int i=0;i<3;i++) prichtungoriginal[i]=prichtung[i];
                                                prichtung0normal=prichtung[0];
                                                prichtung0normal.normalisieren();
                                                /*pkurvetransformiert.ort(0,ort(0));
                                                pkurvetransformiert.ort(1,ort(1));
                                                pkurvetransformiert.vektor(0,vektor(0));
                                                pkurvetransformiert.vektor(1,vektor(1));*/
};
void _extremitaet::reinitialisierenknochen(){
                                                _listenknoten<_knochen>*kit;
                                                //--------------------------
                                                if(psequenz.anfang(kit))do{
                                                 kit->objekt()->plaengeoriginal=kit->objekt()->vektor().laenge();
                                                 kit->objekt()->pvektororiginal=kit->objekt()->vektor();
                                                }while(psequenz.naechstes(kit));
                                                

};
void _extremitaet::initialisierengammaortnormal(){
                                                _listenknoten<_knochen>*kit;
                                                _listenknoten<_kurvehermite3<_tg> >*sit;
                                                _listenknoten<_kurvehermite3<_tg> >*dit;
                                                _vektor3<_tg> o;
                                                pks.anfang(sit);
                                                pkd.anfang(dit);
                                                if(psequenz.anfang(kit))do{
                                                 o+=kit->objekt()->vektor();
                                                 sit->objekt()->ort(1,o);
                                                 dit->objekt()->ort(0,o);
                                                 pks.naechstes(sit);
                                                 pkd.naechstes(dit);
                                                }while(psequenz.naechstes(kit));
};
void _extremitaet::initialisierengammaortgestaucht(){
                                                _listenknoten<_knochen>*kit;
                                                _listenknoten<_kurvehermite3<_tg> >*sit;
                                                _vektor3<_tg> o;
                                                pks.anfang(sit);
                                                if(psequenz.anfang(kit))do{
                                                 o+=kit->objekt()->vektor();
                                                 sit->objekt()->ort(0,o);
                                                 pks.naechstes(sit);
                                                }while(psequenz.naechstes(kit));
};
void _extremitaet::initialisierengammaortgestreckt(){
                                                _listenknoten<_knochen>*kit;
                                                _listenknoten<_kurvehermite3<_tg> >*dit;
                                                _vektor3<_tg> o;
                                                pkd.anfang(dit);
                                                if(psequenz.anfang(kit))do{
                                                 o+=kit->objekt()->vektor();
                                                 dit->objekt()->ort(1,o);
                                                 pkd.naechstes(dit);
                                                }while(psequenz.naechstes(kit));
};
void _extremitaet::initialisierengammavektoren(){
                                                _listenknoten<_kurvehermite3<_tg> >*dit;
                                                _listenknoten<_kurvehermite3<_tg> >*sit;
                                                _vektor3<_tg> vs;
                                                _vektor3<_tg> vd;
                                                _vektor3<_tg> vn;
                                                
                                                //-------------------------------------
                                                pks.anfang(sit);
                                                if(pkd.anfang(dit))do{
                                                 vs=sit->objekt()->ort(1) - sit->objekt()->ort(0);
                                                 vd=dit->objekt()->ort(1) - dit->objekt()->ort(0);
                                                 vs.normalisieren();
                                                 vd.normalisieren();
                                                 vn=(vs+vd)*0.5f;
                                                 vn.normalisieren();
                                                 vn*=0.25;
                                                 
                                                 
                                             vs.setzen(0,0,0);
                                             vd.setzen(0,0,0);
                                                 
                                                 
                                                 sit->objekt()->vektor(0,vs);
                                                 sit->objekt()->vektor(1,vn);
                                                 
                                                 dit->objekt()->vektor(0,vn);
                                                 dit->objekt()->vektor(1,vd);
                                                 pks.naechstes(sit);
                                                }while(pkd.naechstes(dit));
                                
};
void _extremitaet::interpolationnormal(){
                                                pinterpolationsmodus=0;
};
void _extremitaet::interpolationgamma(){
                                                pinterpolationsmodus=1;
};
void _extremitaet::bewegen(const _vektor3<_tg>&v){
};
void _extremitaet::animieren(){
                                                 
                                               
                                                for(int i=0;i<2;i++){
                                                
                                                 if(panimationortaktivitaet[i]){
                                                  
                                                  ort(i,panimationort[i].berechnen(panimationortiterator[i]));
                                                 // new _weltdebugkreuz(pextremitaet->pskelett->welt(),pkurvetransformiert.ort(1),0.01,_vektor4<_to>(1,0,0,1));
                                                 //  L->schreiben("pkrtr ort 1",pkurvetransformiert.ort(1));
                                                  
                                                  panimationortiterator[i]+=panimationortschritt[i];
                                                  if(panimationortschritt[i]>0){
                                                   if(panimationortiterator[i]>1)  panimationortaktivitaet[i]=false;
                                                  }else{
                                                   if(panimationortiterator[i]<0) panimationortaktivitaet[i]=false;
                                                  };
                                                 };
                                                 
                                                 if(panimationvektoraktivitaet[i]){
                                                  vektor(i,panimationvektor[i].berechnen(panimationvektoriterator[i]));
                                                  panimationvektoriterator[i]+=panimationvektorschritt[i];
                                                  if(panimationvektorschritt[i]>0){
                                                   if(panimationvektoriterator[i]>1) panimationvektoraktivitaet[i]=false;
                                                  }else{
                                                   if(panimationvektoriterator[i]<0) panimationvektoraktivitaet[i]=false;
                                                  };
                                                 };
                                                 
                                                 
                                                };
                                                //---rekursion---
                                               // _extremitaet*esit;
                                               // if(anfang(esit))do{
                                               //  esit->animieren();
                                               // }while(naechstes(esit));
};
void _extremitaet::transformieren(){

                                                unsigned int n=psequenz.anzahl();
                                                _listenknoten<_knochen>*kit;
                                                _vektor3<_tg> o;
                                                //_tg it;
                                                //-------------------------------
                                                if(n>0){
                                                 psequenz.anfang(kit);
                                                 if(kit->objekt()->knochen()) {
                                                  o=kit->objekt()->knochen()->ortspitze();
                                                 }else{
                                                  o=pskelett->ort();
                                                 };
                                                 if(pinterpolationsmodus==0) transformierennormal(o,n);
                                                 if(pinterpolationsmodus==1) transformierengamma(o,n);
                                                }else{
                                                };
};                                              
void _extremitaet::transformierengamma(_vektor3<_tg> o,const unsigned int n){
                                                _listenknoten<_knochen>*kit;
                                                _vektor3<_tg> v;
                                                _tg gamma;
                                                _tg rl;
                                                _liste<_kurvehermite3<_tg> >*pk;
                                                _listenknoten<_kurvehermite3<_tg> >*it;
                                                _vektor3<_tg> oo=o;
                                                _vektor3<_tg> vsoll;
                                                _vektor3<_tg> osoll;
                                                _vektor3<_tg> osollw;
                                                _tg korrektor=2;
                                                //-------------------------
                                                if(n>0){
                                                 v=ort(1)-ort(0);
                                                 rl=prichtung[0].laenge();
                                                 gamma=v.laenge()/rl;
                                                 prichtung[0]=v;
                                                 prichtung[0].normalisieren();
                                                 prichtung[0]*=rl;
                                                 
                                                 
                                                 
                                                _vektoranalysis3<_tg> va;
                                                va.berechnenorthogonalenvektor(prichtung[0],prichtung[1]);
                                                prichtung[2]=prichtung[0]%prichtung[1];
                                                prichtung[1].normalisieren();
                                                prichtung[2].normalisieren();
                                              //  for(int i=0;i<3;i++) prichtungoriginal[i]=prichtung[i];
                                                prichtung0normal=prichtung[0];
                                                prichtung0normal.normalisieren();                                                 
                                                 
                                                 
                                                 
                                                 
                                                 
                                                 
                                                 
                                                 L->schreiben("gamma=?",gamma);
                                                 if(gamma>=1){//streckung, interpolation mit pkd
                                                  pk=&pkd;
                                                  gamma-=1;
                                                  //gamma=1-gamma;
                                                 }else{//stauchung, interpolation mit pks
                                                  pk=&pks;
                                                  //gamma=1-gamma;
                                                 };
                                                 //ermitteln, wo die spitze der knochensequenz bei diesem gamma liegen würde ohne korrektor
                                                 _vektor3<_tg> os,osw;
                                                 pk->anfang(it);
                                                 if(psequenz.anfang(kit))do{//knocheninterpolatieren mit pk(gamma)
                                                  os=it->objekt()->berechnen(gamma);
                                                  transformieren(os,osw);
                                                  osw+=oo;
                                                  vsoll=os-o;
                                                  vsoll.normalisieren();
                                                  vsoll*=kit->objekt()->laengeoriginal();
                                                  o+=vsoll;
                                                  pk->naechstes(it);
                                                 }while(psequenz.naechstes(kit));                                                 
                                                 _vektor3<_tg> h1=oo-o;
                                                 _vektor3<_tg> h0=oo-ort(1);
                                                 korrektor=h0.laenge()/h1.laenge();
                                                 
                                                 
                                                 o=oo;
                                                 pk->anfang(it);
                                                 
                                                 if(psequenz.anfang(kit))do{//knocheninterpolatieren mit pk(gamma)
                                                  osoll=it->objekt()->berechnen(gamma);
                                                  osoll.setzenkomponente(0,osoll[0]*korrektor);
                                                  transformieren(osoll,osollw);
                                                  osollw+=oo;
                                                  vsoll=osollw-o;
                                                  vsoll.normalisieren();
                                                  kit->objekt()->vektor()=vsoll*kit->objekt()->laengeoriginal();
                                                  o+=kit->objekt()->vektor();
                                                  pk->naechstes(it);
                                                 }while(psequenz.naechstes(kit));

                                                 //******* DEBUG ********
                                                 psequenz.anfang(kit);
                                                 psequenz.vorheriges(kit);                                                 
                                                 unvisualisieren();
                                                 lwc.einhaengen(new _weltdebugkreuz(pskelett->welt(),ort(1),0.4,_vektor4<_to>(0,1,0,1)));
                                                 lwc.einhaengen(new _weltdebugkreuz(pskelett->welt(),kit->objekt()->ortspitze(),0.4,_vektor4<_to>(1,0,0,1)));
                                                 visualisieren();
                                                 //**********************
                                                };
};                                                
void _extremitaet::transformierennormal(_vektor3<_tg> o,const unsigned int n){
                                               // _extremitaet*esit;
                                                _listenknoten<_knochen>*kit;
                                                _tg it;
                                                //-----------------------------

                                                if(n>0){
                                                 if(n==1){//genau 1 knochen drin
                                                  psequenz.anfang(kit);
                                              //    pextremitaet->pskelett->transformieren(_kurvehermite3<_tg>::ort(1),pkurvetransformiert.ort(1));//!!!!!!!!!!!!!!!
                                                  kit->objekt()->vektor(ort(1)-o);
                                                  o+=kit->objekt()->vektor();
                                                 }else{ //mehr als 1 knochen drin
                                                //  pextremitaet->pskelett->transformieren(_kurvehermite3<_tg>::ort(0),pkurvetransformiert.ort(0));//!!!!!!!!!!!!!!!
                                              //    pextremitaet->pskelett->transformieren(_kurvehermite3<_tg>::ort(1),pkurvetransformiert.ort(1));//!!!!!!!!!!!!!!!
                                              //    pextremitaet->pskelett->transformieren(_kurvehermite3<_tg>::vektor(0),pkurvetransformiert.vektor(0));
                                              //    pextremitaet->pskelett->transformieren(_kurvehermite3<_tg>::vektor(1),pkurvetransformiert.vektor(1));
                                                  it=0;

                                                  if(psequenz.anfang(kit))do{
                                                   it+=kit->objekt()->laengeoriginal()/plaengemax;// pkurvetransformiert.ort(1,_vektor3<_tg>(0,0,100));
                                                   kit->objekt()->vektor((berechnen(it)/*+pextremitaet->pskelett->ort()*/)-o);
                                                   o+=kit->objekt()->vektor();
                                                  }while(psequenz.naechstes(kit));
                                                 };
                                                }else{
                                                 //keine knochen drin
                                                // _vektor3<_tg> h;
                                          //       pextremitaet->pskelett->transformieren(_kurvehermite3<_tg>::ort(1),h);//!!!!!!!!!!!!!!!
                                                // h=h-o;
                                                // e+=h;
                                                };
                                                // if(anfang(esit))do{
                                                //  esit->transformieren();
                                                // }while(naechstes(esit));
};
void _extremitaet::transformieren(const _vektor3<_tg>&v,_vektor3<_tg>&e){
                                                e=prichtung0normal*v[0] + prichtung[1]*v[1] + prichtung[2]*v[2];
};
void _extremitaet::ausrichtenknochen(const _vektor3<_tg>&v){
                                                _listenknoten<_knochen>*kit;
                                                _tg lm=0;;
                                                //--------------------------
                                                if(psequenz.anfang(kit))do{
                                                 lm+=kit->objekt()->laengeoriginal();
                                                }while(psequenz.naechstes(kit));
                                                if(psequenz.anfang(kit))do{
                                                 kit->objekt()->vektor()=v;
                                                 //kit->objekt()->vektor().normalisisern();
                                                 kit->objekt()->vektor()*=/*1.0f/lm;//*/kit->objekt()->laengeoriginal();
                                                }while(psequenz.naechstes(kit));
};
void _extremitaet::ausrichtenknochensinus(const _vektor3<_tg>&amplitude,const _tg freqskalierung){
                                                _listenknoten<_knochen>*kit;
                                                _tg x=0;
                                                _vektor3<_tg> d;
                                                _vektor3<_tg> o;
                                                _vektor3<_tg> n;
                                                //--------------------------
                                                o.setzen(0,0,0);
                                                n=amplitude;
                                                n.normalisieren();
                                                if(psequenz.anfang(kit))do{
                                                 x+=1;//kit->objekt()->laengeoriginal();
                                                 d=(amplitude*sin(x*freqskalierung*_ph)/*+_vektor3<_tg>(1,0,0)*/)-o;
                                                 //if(d.laenge()<nahenull) d=
                                                 d.normalisieren();
                                                 kit->objekt()->vektor()=d*kit->objekt()->laengeoriginal();
                                                 o+=kit->objekt()->vektor();
                                                 
                                                 
                                                 //kit->objekt()->vektor()=v;
                                                 //kit->objekt()->vektor()*=kit->objekt()->laengeoriginal();
                                                 
                                                }while(psequenz.naechstes(kit));
                                                
};
void _extremitaet::ausrichten(){
};
void _extremitaet::fixieren(_polygon*){
};
void _extremitaet::loesen(){
};
bool _extremitaet::animationortaktivitaet(const unsigned int i)const{
                                                return(panimationortaktivitaet[i]);
};
void _extremitaet::animationortaktivitaet(const unsigned int i,const bool b){
                                                panimationortaktivitaet[i]=b;
};
bool _extremitaet::animationvektoraktivitaet(const unsigned int i)const{
                                                return(panimationvektoraktivitaet[i]);
};
void _extremitaet::animationvektoraktivitaet(const unsigned int i,const bool b){
                                                panimationvektoraktivitaet[i]=b;
};
_tg  _extremitaet::animationortiterator(const unsigned int i)const{
                                                return(panimationortiterator[i]);
};
void _extremitaet::animationortiterator(const unsigned int i,const _tg  b){
                                                panimationortiterator[i]=b;
};
_tg  _extremitaet::animationvektoriterator(const unsigned int i)const{
                                                return(panimationvektoriterator[i]);
};
void _extremitaet::animationvektoriterator(const unsigned int i,const _tg  b){
                                                panimationvektoriterator[i]=b;
};
_tg  _extremitaet::animationortschritt(const unsigned int i)const{
                                                return(panimationortschritt[i]);
};
void _extremitaet::animationortschritt(const unsigned int i,const _tg  b){
                                                panimationortschritt[i]=b;
};
_tg  _extremitaet::animationvektorschritt(const unsigned int i)const{
                                                return(panimationvektorschritt[i]);
};
void _extremitaet::animationvektorschritt(const unsigned int i,const _tg  b){
                                                panimationvektorschritt[i]=b;
};
_kurvehermite3<_tg>*_extremitaet::animationort(const unsigned int i){
                                                return(&panimationort[i]);
};
_kurvehermite3<_tg>*_extremitaet::animationvektor(const unsigned int i){
                                                return(&panimationvektor[i]);
};

void _extremitaet::visualisieren(){
                                                _listenknoten<_knochen>*kit;
                                                _listenknoten<_kurvehermite3<_tg> >*sit;
                                                _listenknoten<_kurvehermite3<_tg> >*dit;
                                                _listenknoten<_kurvehermite3<_tg> >*it;
                                                //_liste<_kurvehermite3<_tg> >*pk;
                                                
                                                _vektor3<_tg> o;
                                                _vektor3<_tg> o0;
                                                _vektor3<_tg> o1;
                                                _vektor3<_tg> o0w;
                                                _vektor3<_tg> o1w;
                                                _tg g,gamma;
                                                _vektor4<_to> cc;
                                                //----------------------------------
                                                if(psequenz.anfang(kit)){
                                                 pks.anfang(sit);
                                                 pkd.anfang(dit);
                                                 if(kit->objekt()->pknochen) o=kit->objekt()->pknochen->ortspitze(); else o=pskelett->ort();
                                                 lwp.einhaengen(new _weltdebugpfeil(pskelett->welt(),o,o+prichtung[0],0.1,0.05,_vektor4<_to>(1,0,0,1)));
                                                 lwp.einhaengen(new _weltdebugpfeil(pskelett->welt(),o,o+prichtung[1],0.1,0.05,_vektor4<_to>(0,0,1,1)));
                                                 lwp.einhaengen(new _weltdebugpfeil(pskelett->welt(),o,o+prichtung[2],0.1,0.05,_vektor4<_to>(0,0,1,1)));
                                                 if(pinterpolationsmodus==1){
                                                  do{
                                                   for(g=0;g<2;g+=0.05){
                                                   
                                                 gamma=g;
                                                 if(gamma>=1){//streckung, interpolation mit pkd
                                                  it=dit;
                                                  cc.setzen(1,_to(0.2f),0,1);
                                                  
                                                  gamma-=1;
                                                  //gamma=1-gamma;
                                                 }else{//stauchung, interpolation mit pks
                                                  it=sit;
                                                  cc.setzen(0,_to(0.45f),1,1);
                                                  //gamma=1-gamma;
                                                 };                                                   
                                                    o0=it->objekt()->berechnen(gamma);
                                                    o1=it->objekt()->berechnen(gamma+0.05);
                                                    transformieren(o0,o0w);
                                                    transformieren(o1,o1w);
                                                    lwp.einhaengen(new _weltdebugpfeil(pskelett->welt(),o+o0w,o+o1w,0.001f,0.0005f,cc));
                                                    
                                                    
                                                   };
                                                   pks.naechstes(sit);
                                                   pkd.naechstes(dit);
                                                  }while(psequenz.naechstes(kit));
                                                 };
                                                };
};
void _extremitaet::unvisualisieren(){
                                                lwp.loeschen();
                                                lwc.loeschen();
};

//******************************************************************************************************************************************************************************************************
//                                             E X T R E M I T A E T S S E G M E N T 
//******************************************************************************************************************************************************************************************************
/*_extremitaetssegment::_extremitaetssegment(_extremitaet*e,_listebasis<_extremitaetssegment>*les):_listelistenknotenbasis<_extremitaetssegment>(les){
                                                pextremitaet=e;
                                                pextremitaetssegment=dynamic_cast<_extremitaetssegment*>(les);

                                                                                         
};
_extremitaetssegment::~_extremitaetssegment(){

};
*/
//******************************************************************************************************************************************************************************************************
//                                              G E L E N K
//******************************************************************************************************************************************************************************************************

_gelenk::_gelenk(_knochen*k,_vektor3<_tg> v,_tg w):_listenknotenbasis<_gelenk >(k){
                                                v.setzen(0,0,1);
                                                if(v.laenge()<=nahenull) v.setzen(0,0,1);
                                                v.normalisieren();
                                                pachse=v;
                                                pachsetrans=v;
                                                pwinkel=w;
                                                pknochen=k;
                                                parrow=0;
};

_gelenk::~_gelenk(){
                                                unvisualisieren();
};

void _gelenk::transformieren(){
                                                _gelenk*git;
                                                _knochen*kit;
                                                _vektoranalysis3<_tg> V3;
                                                _vektor3<_tg> e;
                                                //---------------------
                                                pachsetrans=pachse;
                                                kit=pknochen;
                                                while(kit->knochen()!=0){
                                                 kit=kit->knochen();
                                                 if(kit->anfang(git))do{
                                                  V3.rotieren(git->pachse,pachsetrans,git->pwinkel,e);
                                                  pachsetrans=e;
                                                 }while(kit->naechstes(git));
                                                };
};                                                

void _gelenk::winkel(_tg w){
                                                pwinkel=w;
};

_tg _gelenk::winkel() const{
                                                return(pwinkel);
};

void _gelenk::visualisieren(_vektor3<_tg> o){
                                                //_knochen*kit;
                                                //_gelenk*git;
                                                //---------------
                                                unvisualisieren();
                                                parrow=new _weltdebugpfeil(pknochen->skelett()->welt(),o,o+pachsetrans,0.03,0.02,_vektor4<_to>(1,0,0,0));
                                              /*  if(anfang(kit))do{
                                                 kit->visualisieren(o+pvektortrans);
                                                }while(naechstes(kit));
                                                if(anfang(git))do{
                                                 git->visualisieren(o);
                                                }while(naechstes(git));*/
};

void _gelenk::unvisualisieren(){
                                                if(parrow) delete parrow;
                                                parrow=0;
};
