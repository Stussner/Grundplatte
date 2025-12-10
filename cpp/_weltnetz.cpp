//******************************************************************************************************************************************************************************************************
//  Projekt      : grundplatte
//  Bibliothek   : _grundplatte.lib
//  Modul        : _weltnetz.cpp
//  Datum        : 09.01.2006
//  Beschreibung : 
//******************************************************************************************************************************************************************************************************
#include <_weltnetz.hpp>
#include <_weltpolygon.hpp>
#include <_weltoptik.hpp>

//NOCH EINGBUNDEN , weil grafik nicht vollständig:
//#include <_grafikopengl.hpp>

//******************************************************************************************************************************************************************************************************
//                                                              N E T Z S C H A T T E N 
//******************************************************************************************************************************************************************************************************
_netzschatten::_netzschatten(_netz*p,_listebasis<_schatten<_tg,_to> >*schattenliste,_licht<_tg,_to>*l,_tg s):_schatten<_tg,_to>(schattenliste,l,s),_listenknotenbasis<_netzschatten>(p){
                                                                pnetz=p;
                                                                aktualisieren();
};
_netzschatten::~_netzschatten(){ 
                                                                _listenknoten<_liste<_vektor3<_tg> > >*lnit;
                                                                if(ppolysvorne.anfang(lnit))do{
                                                                 lnit->objekt()->loeschen();//_liste<_vektor>::löschen
                                                                }while(ppolysvorne.naechstes(lnit));
                                                                ppolysvorne.loeschen();//liste<liste>::loeschen
                                                                if(ppolyshinten.anfang(lnit))do{
                                                                 lnit->objekt()->loeschen();//_liste<_vektor>::löschen
                                                                }while(ppolyshinten.naechstes(lnit));
                                                                ppolyshinten.loeschen();//liste<liste>::loeschen
                                                                pquads.loeschen();
};
void _netzschatten::opazitaet(const _to o){
};
void _netzschatten::zeichnen(_grafik*gra){
                                                                _licht<_tg,_to>*plicht=licht();
                                                                if(plicht){
                                                                if(geaendert()) aktualisieren();
                                                                 _listenknoten<_liste<_vektor3<_tg> > >*lnit;
                                                                 if(ppolysvorne.anfang(lnit)){
                                                                  do{
                                                                   gra->polygon(lnit->objekt());
                                                                   /*glBegin(GL_POLYGON);
                                                                   if(lnit->objekt()->anfang(it))do{
                                                                    glVertex3dv(it->objekt()->daten());
                                                                   }while(lnit->objekt()->naechstes(it));
                                                                   glEnd();*/
                                                                  }while(ppolysvorne.naechstes(lnit));
                                                                 };
                                                                 
                                                                 if(ppolyshinten.anfang(lnit)){
                                                                  do{
                                                                   gra->polygon(lnit->objekt());
                                                                   /*glBegin(GL_POLYGON);
                                                                   if(lnit->objekt()->anfang(it))do{
                                                                    glVertex3dv(it->objekt()->daten());
                                                                   }while(lnit->objekt()->naechstes(it));
                                                                   glEnd();*/
                                                                  }while(ppolyshinten.naechstes(lnit));
                                                                 };
                                                                 
                                                                 gra->rechtecke(&pquads);
                                                                 /*if(pquads.anfang(it)){
                                                                  glBegin(GL_QUADS);
                                                                  do{
                                                                   glVertex3dv(it->objekt()->daten());
                                                                  }while(pquads.naechstes(it));
                                                                  glEnd();
                                                                 };*/
                                                                };
};
void _netzschatten::zeichnendebug(_grafik*gra){
                                                                _licht<_tg,_to>*plicht=licht();
                                                                if(plicht){
                                                                if(geaendert()) aktualisieren();
                                                                _listenknoten<_liste<_vektor3<_tg> > >*lnit;
                                                                _vektor4<_to> col(0,(_to)0.5f,0,(_to)0.3f);
                                                                gra->transparenz(true);//glEnable(GL_BLEND);
                                                                gra->transparenzmultiplikativ();//glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
                                                                gra->textur(false);//glDisable(GL_TEXTURE_2D);
                                                                gra->beleuchtung(false);//glDisable(GL_LIGHTING);
                                                                gra->ausschussflaeche(false);//glDisable(GL_CULL_FACE);

                                                                gra->rechtecke(&pquads,col);    
                                                                /*if(pquads.anfang(it)){
                                                                 glBegin(GL_QUADS);
                                                                 glColor4f(0,0.5,0,0.3);
                                                                 do{
                                                                  glVertex3dv(it->objekt()->daten());
                                                                 }while(pquads.naechstes(it));
                                                                 glEnd();
                                                                };*/
                                                                col.setzen(_to(0.5f),0,0,_to(0.3));
                                                                if(ppolysvorne.anfang(lnit)){
                                                                 do{
                                                                  gra->polygon(lnit->objekt());
                                                                  /*glBegin(GL_POLYGON);
                                                                  glColor4f(0.5,0,0,0.3);
                                                                  if(lnit->objekt()->anfang(it))do{
                                                                   glVertex3dv(it->objekt()->daten());
                                                                  }while(lnit->objekt()->naechstes(it));
                                                                  glEnd();*/
                                                                 }while(ppolysvorne.naechstes(lnit));
                                                                };
                                                                
                                                                col.setzen(0,0,_to(0.5),_to(0.3));
                                                                if(ppolyshinten.anfang(lnit)){
                                                                 do{
                                                                  gra->polygon(lnit->objekt());
                                                                  /*glBegin(GL_POLYGON);
                                                                  glColor4f(0,0,0.5,0.3);
                                                                  if(lnit->objekt()->anfang(it))do{
                                                                   glVertex3dv(it->objekt()->daten());
                                                                  }while(lnit->objekt()->naechstes(it));
                                                                  glEnd();*/
                                                                 }while(ppolyshinten.naechstes(lnit));
                                                                };
                                                                
                                                                
                                                                gra->transparenz(false);//glDisable(GL_BLEND);
                                                                gra->textur(true);//glEnable(GL_TEXTURE_2D);
                                                                gra->beleuchtung(true);//glEnable(GL_LIGHTING);
                                                                gra->ausschussflaeche(true);//glEnable(GL_CULL_FACE);
                                                                gra->transparenzadditiv();//glBlendFunc(GL_ONE,GL_ONE);
                                                                };
};

void _netzschatten::aktualisieren(){
                                                                //iteration der kanten setzt vorraus , 
                                                                //daß netz::verknuepfen aufgerufen wurde
                                                                _polygon*pit;
                                                                _vertex*vit;
                                                                _listenknoten<_vertex>*lnvit;
                                                                _verbindervertexpolygon*cit;
                                                                int markierung=1;//(int)pnetz->welt()->zyklus();
                                                                _vektor3<_tg> lichtv;
                                                                _vektor3<_tg> n;
                                                                _vektor3<_tg> v2;
                                                                _vektor3<_tg> v3;
                                                                _vektor3<_tg> z;
                                                                _polygon*pat;
                                                                _tg pats,pits;
                                                                _listenknoten<_liste<_vektor3<_tg> > >*lnit;
                                                                _liste<_vektor3<_tg> >*neu;
                                                                bool neuverknuepfen;
                                                                _tg plaenge=laenge();
                                                                _licht<_tg,_to> * plicht=licht();
                                                                //-----------
                                                                if(plicht==0)return;
                                                                iterierenliste(&ppolysvorne,lnit,lnit->objekt()->loeschen());
                                                                iterierenliste(&ppolyshinten,lnit,lnit->objekt()->loeschen());
                                                                ppolysvorne.loeschen();
                                                                ppolyshinten.loeschen();
                                                                pquads.loeschen();
                                                                neuverknuepfen=false;
                                                                iterierenliste(pnetz,pit,
                                                                 iterierenliste(pit,lnvit,
                                                                  vit=lnvit->objekt();
                                                                  cit=static_cast<_verbindervertexpolygon*>(lnvit);//->connector(pit);
                                                                  if(cit->gegenkante()==0) neuverknuepfen=true;
                                                                  cit->markierung(0);
                                                                 );
                                                                );
                                                                if(neuverknuepfen) pnetz->verknuepfenverbindervertexpolygon();
                                                                if(pnetz->anfang(pit))do{
                                                                
                                                                
                                                                
                                                                
                                                                
                                                                 
                                                                 if(pit->anfang(lnvit)){//vit=pit->vertex();
                                                                  vit=lnvit->objekt();
                                                                  lichtv=plicht->ort()- vit->ort();
                                                                  lichtv.normalisieren();
                                                                  if((pit->normale()*lichtv)>0){
                                                                   //zum deckel
                                                                 //  L->schreiben("zum deckel");
                                                                   neu=new _liste<_vektor3<_tg> >();
                                                                   ppolysvorne.einhaengen(neu);
                                                                   do{
                                                                    vit=lnvit->objekt();
                                                                    neu->einhaengen(new _vektor3<_tg>(vit->ort()));
                                                                    //vit=vit->naechstes(pit);
                                                                   }while(pit->naechstes(lnvit));//vit!=pit->vertex());
                                                                  }else{
                                                                   //zum boden
                                                                  // L->schreiben("zum boden");
                                                                   neu=new _liste<_vektor3<_tg> >();
                                                                   ppolyshinten.einhaengen(neu);
                                                                   do{
                                                                    vit=lnvit->objekt();
                                                                    z=vit->ort()-plicht->ort();
                                                                    z.normalisieren();
                                                                    z*=plaenge;
                                                                    neu->einhaengen(new _vektor3<_tg>(vit->ort()+z));
                                                                    //vit=vit->naechstes(pit);
                                                                   }while(pit->naechstes(lnvit));//vit!=pit->vertex());
                                                                  };
                                                                  
                                                                  
                                                                  iterierenliste(pit,lnvit,
                                                                   vit=lnvit->objekt();
                                                                   cit=static_cast<_verbindervertexpolygon*>(lnvit);
                                                                   lichtv=plicht->ort()- vit->ort();
                                                                   lichtv.normalisieren();
                                                                   if(cit->markierung()!=markierung){
                                                                    cit->markierung(markierung);
                                                                    if(cit->gegenkante()){
                                                                     cit->gegenkante()->markierung(markierung);
                                                                     //Kante Untersuchen und 
                                                                     //ggf. schattenpolygon erzeugen
                                                                     const _vektor3<_tg>&v0=vit->ort();
                                                                     pat=cit->gegenkante()->polygon();
                                                                     pats=lichtv*pat->normale();
                                                                     pits=lichtv*pit->normale();
                                                                     const _vektor3<_tg>&v1=cit->naechstervertex()->ort();
                                                                     //******** DEBUG **********
                                                                     //_vektor3<_tg> h;
                                                                     //new _weltdebuglinie(pnetz->welt(),v0,v1,_vektor4<_to>(1,1,1,1));
                                                                     //h=v0+(v1-v0)*0.2;
                                                                     //new _weltdebuglinie(pnetz->welt(),h,h+(pit->mitte()-h)*0.5,_vektor4<_to>(1,1,1,1));
                                                                     //new _weltdebuglinie(pnetz->welt(),h,h+(pat->mitte()-h)*0.5,_vektor4<_to>(1,1,1,1));
                                                                     //*************************
                                                                     if( ((pats<=0)&&(pits>0)) || ((pats>0)&&(pits<=0))  ){
                                                                      //schatten umrisskante liegt vor
                                                                      //L->schreiben("schattenkante liegt vor");
                                                                      v2=v1 - plicht->ort();
                                                                      v2.normalisieren();
                                                                      v2*=plaenge;
                                                                      v3=v0 - plicht->ort();
                                                                      v3.normalisieren();
                                                                      v3*=plaenge;
                                                                      n=(v1-v0)%v3;
                                                                      v2+=v1;
                                                                      v3+=v0;
                                                                      if((n*(pit->mitte()-v0))>0){
                                                                       pquads.einhaengen(new _vektor3<_tg>(v0));
                                                                       pquads.einhaengen(new _vektor3<_tg>(v1));
                                                                       pquads.einhaengen(new _vektor3<_tg>(v2));
                                                                       pquads.einhaengen(new _vektor3<_tg>(v3));
                                                                      }else{
                                                                       pquads.einhaengen(new _vektor3<_tg>(v0));
                                                                       pquads.einhaengen(new _vektor3<_tg>(v3));
                                                                       pquads.einhaengen(new _vektor3<_tg>(v2));
                                                                       pquads.einhaengen(new _vektor3<_tg>(v1));
                                                                      };
                                                                     };
                                                                    }else{
                                                                     L->schreiben("WARNUNG : verbinderiterator cit besitzt keine gegenkante"); 
                                                                    };
                                                                   };
                                                                  );
                                                                 };//if vit ?
                                                                }while(pnetz->naechstes(pit));
};
//******************************************************************************************************************************************************************************************************
//                                                              N E T Z
//******************************************************************************************************************************************************************************************************
_netz::_netz():_listenknotenbasis<_netz >(){
                                                                pworld=0;
                                                                psubtractive=false;
                                                                pkeinbsp=false;
                                                                pdynamisch=false;
                                                                pschattenvolumen=false;
                                                                pschattenvolumenlaenge=100;
                                                                pflag=0;
                                                                pbrechzahl=1.544f;//quarz
                                                                pdispersionsskalierung=1;
                                                                pnurkollisionskopplung=false;
                                                                pnichtspeichern=false;
                                                                pschatteniterator=0;
                                                                peditionebene[0].setzen(1,0,0);
                                                                peditionebene[1].setzen(0,1,0);
                                                                //blockdaten
	                                                            
	                                                            panzahlvertex=0;
	                                                            panzahlverbinder=0;
	                                                            pverbinderfeld=0;
	                                                            pblock=0;                                                                
};

_netz::~_netz(){
                                                                loeschenindex();
};

_welt*_netz::welt(){
                                                                return(pworld);
};
void _netz::welt(_welt*w){
                                                                pworld=w;
};
_netz* _netz::duplizieren(){
                                                                //funktion dupliziert das thismesh und legt die kopie in das netz mn ab
                                                                _polygon*p;
                                                                _vertex*v;
                                                                _listenknoten<_vertex>*lnv;
                                                                _polygon*np;
                                                                _vertex*nextv;
                                                                _vertex*nv;
                                                                _verbindervertexpolygon*vcp;
                                                                _verbindervertexpolygon*nvcp;
                                                                _vektor3<_tg> o;
                                                                _netz*nm;
                                                                //--------------
                                                                erzeugenvertexintersektion();
                                                                nullintersektionvertices();
                                                                //o=*this;
                                                                nm=new _netz();
                                                                iterieren(p,
																 np=new _polygon(p);//np=new _polygon(nm);
																 np->einhaengen(nm);
                                                                 np->status(+2);
                                                                // np->ausrichtung(p->ausrichtung());
                                                                 iterierenliste(p,lnv,
                                                                  v=lnv->objekt();
                                                                  if(v->intersektion()){
                                                                   nv=v->intersektion()->vertex;
                                                                   if(nv==0){
                                                                    o=v->intersektion()->o;
                                                                    v->intersektion()->vertex=new _vertex(nm,o);
                                                                    nv=v->intersektion()->vertex;
                                                                   };
                                                                   //if(np->vertex()==0) np->vertex(nv);
                                                                  }else{
                                                                   //L->fehler("void _netz::duplizieren(_netz*&)","v->intersektion nicht gesetzt, keine virtuelle intersektion für vertex v vorhanden.");
                                                                  };
                                                                 );
                                                                 //poly p iterieren -> vcp anlegen
                                                                 iterierenliste(p,lnv,
                                                                  v=lnv->objekt();
                                                                  nextv=lnv->naechstes()->objekt();
                                                                  vcp=static_cast<_verbindervertexpolygon*>(lnv);
                                                                  nvcp=new _verbindervertexpolygon(v->intersektion()->vertex,np);//vcp->st[0][0],vcp->st[0][1],vcp->st[1][0],vcp->st[1][1]
                                                                  nvcp->kopieren(vcp);
                                                                  nvcp->farbe(vcp->farbe());
                                                                 );
                                          // np->textur(p->textur());
                                                                 if(p->hatdreieck()) np->erzeugendreieck();
                                                                 if(p->hatkante()) np->erzeugenkante();
                                                                 np->aktualisieren();
                                                                );
                                                                loeschenvertexintersektion();
                                                                nm->psubtractive=psubtractive;
                                                                nm->pkeinbsp=pkeinbsp;
                                                                nm->pdynamisch=pdynamisch;
                                                                nm->pschattenvolumen=pschattenvolumen;
                                                                nm->pschattenvolumenlaenge=pschattenvolumenlaenge;
                                                                nm->pbrechzahl=pbrechzahl;
                                                                nm->pdispersionsskalierung=pdispersionsskalierung;
                                                                nm->pnurkollisionskopplung=pnurkollisionskopplung;
                                                                nm->pnichtspeichern=pnichtspeichern;
                                                                nm->_material<_tg>::kopieren(this);
                                                                nm->aktualisieren();
                                                                return(nm);
};
void _netz::vereinigen(_netz*&om){
                                                                _polygon*op;
                                                                _vertex*ov;
                                                                _listenknoten<_vertex>*lnov;
                                                                //-----------------------------
                                                                om->markierungvertex(0);
                                                                //op=om->firstpoly;
                                                                iterierenliste(om,op,
                                                                 op->netz(this);
                                                                 iterierenliste(op,lnov,
                                                                  ov=lnov->objekt();
                                                                  if(ov->markierung()==0){
                                                                   //*ov+=*om;
                                                                   //*ov-=*this;
                                                                   //add(om->ort->o,ov->o);
                                                                   //sub(ort->o,ov->o);
                                                                   ov->markierung(1);
                                                                  };
                                                                 );
                                                                );
                                                                _listebasis<_polygon >::vereinigen(om);//::unite_ring(firstpoly,om->firstpoly);
                                                                _listebasis<_vertex>::vereinigen((_listebasis<_vertex>*)om);
                                                                //achtung : polygon-objekt mussen ihre netz-rückassoziationen
                                                                //om->firstpoly=0;
                                                                delete om;
                                                                om=0;
                                                                aktualisieren();
};
 
void _netz::transformieren(_grafik*gra,_kamera<_tg>*c,bool backfaceculled){ 
                                                                _polygon*pit; 
                                                                //---------- 
                                                                 if(backfaceculled){
                                                                  iterieren(pit,
                                                                   if(2 == pit->markierung() || ((pit->mitte() - c->ort()) * pit->normale()) < 0){  // 2 = kein culling, sichtbar (frontface)  
                                                                     pit->transformieren(gra,c);
                                                                    pit->markierung(1);  // sichtbar 
                                                                   }else{  // nicht sichtbar (backface) 
                                                                    pit->markierung(0);  // nicht sichtbar 
                                                                   };
                                                                  );
                                                                 }else{
                                                                  iterieren(pit,
                                                                   pit->transformieren(gra,c);
                                                                   pit->markierung(1);  // sichtbar 
                                                                  );
                                                                 };
};
 
void _netz::transformieren(_grafik*gra,_kamera<_tg>*c,_tg xy,_tg wert){ 
                                                                _polygon*pit; 
                                                                //---------- 
                                                                iterieren(pit,
                                                                 pit->transformieren(gra,c,xy,wert);
                                                                 pit->markierung(1);  // sichtbar 
                                                                );
};
 
void _netz::transformieren(_grafik*gra,_kamera<_tg>*c,_tg x,_tg y,_tg z){ 
                                                                _polygon*pit; 
                                                                //---------- 
                                                                if(anfang(pit))do{ 
                                                                 pit->transformieren(gra,c,x,y,z);
                                                                 pit->markierung(1);  // sichtbar 
                                                                }while(naechstes(pit)); 
};

void _netz::zeichnen(_grafik*g){
                                                                _polygon*pit;
                                                                iterieren(pit,pit->zeichnen(g));
};
void _netz::zeichnendebug(_grafik*g){
                                                                _polygon*pit;
                                                                iterieren(pit,pit->zeichnendebug(g));
};

void _netz::zeichnenlinie(_grafik*g,bool backfaceculled){
                                                                _polygon*pit; 
                                                                //---------- 
                                                                if(backfaceculled){
                                                                 iterieren(pit,if(1 == pit->markierung())pit->zeichnenlinie(g));
                                                                }else{
                                                                 iterieren(pit,pit->zeichnenlinie(g));
                                                                };
};
bool _netz::hatintersektion(_liste<_netz >*incs,_liste<_netz >*excs){
                                                                bool hasint;
                                                                _listenknoten<_netz >*mit;
                                                                _listenknoten<_netz >*eit;
                                                                bool ok;
                                                                //-------
                                                                hasint=false;
                                                                if(incs->anfang(mit))do{
                                                                 ok=true;
                                                                 if(excs->anfang(eit))do{
                                                                  if(mit->objekt()==eit->objekt()) ok=false;
                                                                 }while((excs->naechstes(eit))&&(ok==true));
                                                                 if(ok){
                                                                  hasint=hatintersektion(mit->objekt());
                                                                 };
                                                                }while((incs->naechstes(mit))&(hasint==false));
                                                                return(hasint);
};

bool _netz::hatintersektion(_netz*m){
                                                                bool hasint;
                                                                _polygon*pit;
                                                                _polygon*pito;
                                                                //------------
                                                                markierungverbinder(0);
                                                                hasint=false;
                                                                if(anfang(pit))do{
                                                                 if(m->anfang(pito))do{
                                                                  pit->aktualisieren();
                                                                  pito->aktualisieren();
                                                                  pit->berechnengroessterindex();
                                                                  pito->berechnengroessterindex();
                                                                  hasint=pit->hatintersektion(pito);
                                                                 }while((m->naechstes(pito))&&(hasint==false));
                                                                }while((naechstes(pit))&&(hasint==false));
                                                                return(hasint);
};
bool _netz::innerhalb(_netz*m){
                                                                
                                                                _modifikationnetzintersektion ism;
                                                                if(ism.netzinnerhalbnetz(this,m)) return(true);
                                                                return(false);
};
_vertex*_netz::erstervertex(){
                                                                _polygon*pit;
                                                                if(anfang(pit)) return(pit->vertex());
                                                                return(0);
};                                        
bool _netz::additiv()const{
                                                                return(!psubtractive);
};

bool _netz::subtraktiv()const{
                                                                return(psubtractive);
};

void _netz::subtraktiv(bool b){
                                                                _polygon*pit;
                                                                 //----------
                                                                if(b!=psubtractive){
                                                                 psubtractive=b;
                                                                 if(anfang(pit))do{
                                                                  pit->invertieren();
                                                                 }while(naechstes(pit));
                                                                };
};
void _netz::keinbsp(const bool b){//teilnahme am bsp ein/aus
                                                                pkeinbsp=b;
};                             
bool _netz::keinbsp()const{
                                                                return(pkeinbsp);
};
void _netz::dynamisch(const bool b){                            //dynamisch zeichnen ein,aus
                                                                pdynamisch=b;
};
bool _netz::dynamisch()const{
                                                                return(pdynamisch);
};
bool _netz::zonennetz()const{
                                                                if(pworld){
                                                                 _partition::_zone*zit;
                                                                 if(pworld->anfang(zit))do{
                                                                  _partition::_sektor*sit;
                                                                  if(zit->anfang(sit))do{
                                                                   _partition::_polygon*pit;
                                                                   if(sit->anfang(pit))do{
                                                                    if(pit->polygon()->netz()==this) return(true);
                                                                   }while(sit->naechstes(pit));
                                                                  }while(zit->naechstes(sit));
                                                                 }while(pworld->naechstes(zit));
                                                                };
                                                                return(false);
};
void _netz::schattenvolumen(const bool b){                     //erzeugung von schattenvolumen nach übersetzung
                                                                pschattenvolumen=b;
};
bool _netz::schattenvolumen()const{
                                                                return(pschattenvolumen);
};
void _netz::schattenvolumenlaenge(const _tg l){                 
                                                                if(l>nahenull) pschattenvolumenlaenge=l;
};
_tg _netz::schattenvolumenlaenge()const{
                                                                return(pschattenvolumenlaenge);
};

_vektor3<_tg> _netz::schwerpunkt()const{
                                                                _polygon*pit;
                                                                _tg Agesamt,A;
                                                                _tg x,y,z;
                                                                _vektor3<_tg> r;
                                                                //----------
                                                                x=0;
                                                                y=0;
                                                                z=0;
                                                                Agesamt=0;
                                                                if(anfang(pit))do{
                                                                 A=pit->flaeche();
                                                                 x+=pit->mitte()[0]*A;
                                                                 y+=pit->mitte()[1]*A;
                                                                 z+=pit->mitte()[2]*A;
                                                                 Agesamt+=A;
                                                                }while(naechstes(pit));
                                                                if(Agesamt>0) r.setzen(x/Agesamt,y/Agesamt,z/Agesamt); else r.setzen(0,0,0);
                                                                return(r);
};
_vektor3<_tg> _netz::mitte() {
                                                                _vertex*vit;
                                                                _listenknoten<_vertex>*lnvit;
                                                                _polygon*pit;
                                                                _tg i=0;
                                                                _vektor3<_tg> m;
                                                                //---------
                                                                markierungvertex(1);
                                                                iterieren(pit,
                                                                 iterierenliste(pit,lnvit,
                                                                  vit=lnvit->objekt();
                                                                  if(vit->markierung()==1){
                                                                   vit->markierung(0);
                                                                   m+=vit->ort();
                                                                   i+=1;
                                                                  };
                                                                 );
                                                                );
                                                                if(i>0) m*=1.0f/i;
                                                                return(m);
};
void _netz::umgrenzungsquader(_tg&x0,_tg&x1,_tg&y0,_tg&y1,_tg&z0,_tg&z1)const{
                                                                _polygon*pit;
                                                                _vertex*vit;
                                                                _listenknoten<_vertex>*lnvit;
                                                                //-----------
                                                                if(anfang(pit)){
                                                                 if(pit->vertex()){
                                                                  vit=pit->vertex();
                                                                  x0=x1=(vit->ort())[0];
                                                                  y0=y1=(vit->ort())[1];
                                                                  z0=z1=(vit->ort())[2];
                                                                 };
                                                                 iterieren(pit,
                                                                  iterierenliste(pit,lnvit,
                                                                   vit=lnvit->objekt();
                                                                   _vektor3<_tg> v=vit->ort();
                                                                   if(v[0]<x0) x0=v[0];
                                                                   if(v[0]>x1) x1=v[0];
                                                                   if(v[1]<y0) y0=v[1];
                                                                   if(v[1]>y1) y1=v[1];
                                                                   if(v[2]<z0) z0=v[2];
                                                                   if(v[2]>z1) z1=v[2];
                                                                  );
                                                                 );
                                                                }else{
                                                                 x0=x1=y0=y1=z0=z1=0;
                                                                };
};
bool _netz::diskret()const{
                                                                _polygon*p;
                                                                _vertex*vit;
                                                                _vertex*vin;
                                                                _listenknoten<_vertex>*lnvit;
                                                                //---------------------------
                                                                iterieren(p,iterierenliste(p,lnvit,
                                                                 vit=lnvit->objekt();
                                                                 vin=lnvit->naechstes()->objekt();
                                                                 if(p->nachbar(vit,vin)==0) return(false);
                                                                ));
                                                                return(true);
};
//-------------------------------------------------------------- modifikation ------------------------------------------------------------------------
void _netz::kopierenparameterinort(){
                                                                _vertex*vit;
                                                                _polygon*pit;
                                                                _listenknoten<_vertex>*lnvit;
                                                                //--------
                                                                iterieren(pit,iterierenliste(pit,lnvit,
                                                                 vit=lnvit->objekt();
                                                                 vit->ort(vit->ortparameter());
                                                                ));
};                                                                
void _netz::kopierenortinparameter(){
                                                                _vertex*vit;
                                                                _polygon*pit;
                                                                _listenknoten<_vertex>*lnvit;
                                                                //--------
                                                                iterieren(pit,iterierenliste(pit,lnvit,
                                                                 vit=lnvit->objekt();
                                                                 vit->ortparameter()=vit->ort();
                                                                ));
};
void _netz::verschiebenvertex(const _vektor3<_tg> v){
                                                                _vertex*vit;
                                                                _polygon*pit;
                                                                _listenknoten<_vertex>*lnvit;
                                                                //--------
                                                                markierungvertex(1);
                                                                iterieren(pit,iterierenliste(pit,lnvit,vit=lnvit->objekt();
                                                                 if(vit->markierung()==1){
                                                                  vit->ort(vit->ort()+v);
                                                                  vit->markierung(0);
                                                                 };
                                                                ));
                                                                aktualisieren();
};
void _netz::tauschenxy(){
                                                                _vertex*vit;
                                                                _polygon*pit;
                                                                _listenknoten<_vertex>*lnvit;
                                                                //--------
                                                                markierungvertex(1);
                                                                iterieren(pit,iterierenliste(pit,lnvit,vit=lnvit->objekt();
                                                                 if(vit->markierung()==1){
                                                                  vit->ort((vit->ort())[1],(vit->ort())[0],(vit->ort())[2]);
                                                                  vit->markierung(0);
                                                                 };
                                                                ));
                                                                iterieren(pit,pit->invertieren()); 
                                                                aktualisieren();
};
void _netz::tauschenxz(){
                                                                _vertex*vit;
                                                                _polygon*pit;
                                                                _listenknoten<_vertex>*lnvit;
                                                                //--------
                                                                markierungvertex(1);
                                                                iterieren(pit,iterierenliste(pit,lnvit,vit=lnvit->objekt();
                                                                 if(vit->markierung()==1){
                                                                  vit->ort((vit->ort())[2],(vit->ort())[1],(vit->ort())[0]);
                                                                  vit->markierung(0);
                                                                 };
                                                                ));
                                                                iterieren(pit,pit->invertieren()); 
                                                                aktualisieren();
};
void _netz::tauschenyz(){
                                                                _vertex*vit;
                                                                _polygon*pit;
                                                                _listenknoten<_vertex>*lnvit;
                                                                //--------
                                                                markierungvertex(1);
                                                                iterieren(pit,iterierenliste(pit,lnvit,vit=lnvit->objekt();
                                                                 if(vit->markierung()==1){
                                                                  vit->ort((vit->ort())[0],(vit->ort())[2],(vit->ort())[1]);
                                                                  vit->markierung(0);
                                                                 };
                                                                ));
                                                                iterieren(pit,pit->invertieren());
                                                                aktualisieren();
};
void _netz::spiegelnx(){
                                                                _vertex*vit;
                                                                _polygon*pit;
                                                                _vektor3<_tg> m=mitte();
                                                                _listenknoten<_vertex>*lnvit;
                                                                //--------
                                                                markierungvertex(1);
                                                                iterieren(pit,iterierenliste(pit,lnvit,vit=lnvit->objekt();
                                                                 if(vit->markierung()==1){
                                                                  vit->ort(-(vit->ort())[0],(vit->ort())[1],(vit->ort())[2]);
                                                                  vit->markierung(0);
                                                                 };
                                                                ));
                                                                iterieren(pit,pit->invertieren()); 
                                                                aktualisieren();
};
void _netz::spiegelny(){
                                                                _vertex*vit;
                                                                _polygon*pit;
                                                                _vektor3<_tg> m=mitte();
                                                                _listenknoten<_vertex>*lnvit;
                                                                //--------
                                                                markierungvertex(1);
                                                                iterieren(pit,iterierenliste(pit,lnvit,vit=lnvit->objekt();
                                                                 if(vit->markierung()==1){
                                                                  vit->ort((vit->ort())[0],-(vit->ort())[1],(vit->ort())[2]);
                                                                  vit->markierung(0);
                                                                 };
                                                                ));
                                                                iterieren(pit,pit->invertieren()); 
                                                                aktualisieren();
};
void _netz::spiegelnz(){
                                                                _vertex*vit;
                                                                _polygon*pit;
                                                                _vektor3<_tg> m=mitte();
                                                                _listenknoten<_vertex>*lnvit;
                                                                //--------
                                                                markierungvertex(1);
                                                                iterieren(pit,iterierenliste(pit,lnvit,vit=lnvit->objekt();
                                                                 if(vit->markierung()==1){
                                                                  vit->ort((vit->ort())[0],(vit->ort())[1],-(vit->ort())[2]);
                                                                  vit->markierung(0);
                                                                 };
                                                                ));
                                                                iterieren(pit,pit->invertieren());
                                                                aktualisieren();
};
void _netz::rotierenx(const _tg w){
                                                                _vertex*vit;
                                                                _polygon*pit;
                                                                _listenknoten<_vertex>*lnvit;
                                                                //--------
                                                                markierungvertex(1);
                                                                iterieren(pit,iterierenliste(pit,lnvit,vit=lnvit->objekt();
                                                                 if(vit->markierung()==1){
                                                                  vit->rotierenx(w);
                                                                  vit->markierung(0);
                                                                 };
                                                                ));
                                                                aktualisieren();
};
void _netz::rotiereny(const _tg w){
                                                                _vertex*vit;
                                                                _polygon*pit;
                                                                _listenknoten<_vertex>*lnvit;
                                                                //--------
                                                                markierungvertex(1);
                                                                iterieren(pit,iterierenliste(pit,lnvit,vit=lnvit->objekt();
                                                                 if(vit->markierung()==1){
                                                                  vit->rotiereny(w);
                                                                  vit->markierung(0);
                                                                 };
                                                                ));
                                                                aktualisieren();
};

void _netz::rotierenz(const _tg w){
                                                                _vertex*vit;
                                                                _polygon*pit;
                                                                _listenknoten<_vertex>*lnvit;
                                                                //--------
                                                                markierungvertex(1);
                                                                iterieren(pit,iterierenliste(pit,lnvit,vit=lnvit->objekt();
                                                                 if(vit->markierung()==1){
                                                                  vit->rotierenz(w);
                                                                  vit->markierung(0);
                                                                 };
                                                                ));
                                                                aktualisieren();
};
void _netz::rotieren(const _vektor3<_tg>&o,const _vektor3<_tg>&a,const _tg w){
                                                                _polygon*pit;
                                                                _vertex*vit;
                                                                _vektoranalysis3<_tg> v3;
                                                                _vektor3<_tg> e,h;
                                                                _listenknoten<_vertex>*lnvit;
                                                                //--------------
                                                                markierungvertex(1);
                                                                iterieren(pit,iterierenliste(pit,lnvit,vit=lnvit->objekt();
                                                                 if(vit->markierung()==1){
                                                                  v3.rotieren(a,(vit->ort()-o),w,e);
                                                                  h=o+e;
                                                                  vit->ort(h);
                                                                  vit->markierung(0);
                                                                 };
                                                                ));
                                                                aktualisieren();
};
void _netz::rotieren(const _vektor3<_tg>&a,const _tg w){
                                                                _vektor3<_tg> m;
                                                                _polygon*pit;
                                                                _tg c=0;
                                                                //--------------
                                                                if(anfang(pit))do{
                                                                 m+=pit->mitte();
                                                                 c+=1;
                                                                }while(naechstes(pit));
                                                                if(c>1) m.mul(1.0f/c);
                                                                rotieren(m,a,w);
};
void _netz::verschiebennormal(_tg s){
                                                                _polygon*pit;
                                                                iterieren(pit,pit->verschiebennormal(s));
                                                                aktualisieren();
};
void _netz::verschiebenzumraster(const _tg r){
                                                                _vertex*vit;
                                                                _polygon*pit;
                                                                _listenknoten<_vertex>*lnvit;
                                                                int di;
                                                                _tg dx,dy,dz;
                                                                //--------
                                                                markierungvertex(1);
                                                                iterieren(pit,iterierenliste(pit,lnvit,
                                                                 vit=lnvit->objekt();
                                                                 if(vit->markierung()==1){
                                                                  dx=(vit->ort())[0];
                                                                  dx/=r;
                                                                  di=(int)dx;
                                                                  dx=di;
                                                                  dx*=r;
                                                                  dy=(vit->ort())[1];
                                                                  dy/=r;
                                                                  di=(int)dy;
                                                                  dy=di;
                                                                  dy*=r;
                                                                  dz=(vit->ort())[2];
                                                                  dz/=r;
                                                                  di=(int)dz;
                                                                  dz=di;
                                                                  dz*=r;
                                                                  vit->ort(dx,dy,dz);
                                                                  vit->markierung(0);
                                                                 };
                                                                ));
                                                                aktualisieren();
};
void _netz::skalierenkonisch(const _vektor3<_tg>&ort,const _vektor3<_tg>&vektor,_tg startskalierung,_tg endskalierung){
                                                                _polygon*pit;
                                                                _vertex*vit;
                                                                _vektoranalysis3<_tg> v3;
                                                                _vektor3<_tg> lot;
                                                                _vektor3<_tg> e;
                                                                _tg p;
                                                                _tg s;
                                                                _listenknoten<_vertex>*lnvit;
                                                                //--------------
                                                                markierungvertex(1);
                                                                iterieren(pit,iterierenliste(pit,lnvit,vit=lnvit->objekt();
                                                                 if(vit->markierung()==1){
                                                                  v3.lotpunktgerade(vit->ort(),ort,vektor,lot,p);
                                                                  if((p>-nahenull)&&(p<(1+nahenull))){
                                                                   s=startskalierung+(endskalierung-startskalierung)*p;//linear
                                                                   vit->ort((vit->ort()+lot) - lot*s);
                                                                  };
                                                                  vit->markierung(0);
                                                                 };
                                                                ));
                                                                aktualisieren();
};
void _netz::skalieren(const _tg f){
                                                                _vertex*vit;
                                                                _polygon*pit;
                                                                _listenknoten<_vertex>*lnvit;
                                                                //--------
                                                                markierungvertex(1);
                                                                iterieren(pit,iterierenliste(pit,lnvit,vit=lnvit->objekt();
                                                                 if(vit->markierung()==1){
                                                                  vit->ort(vit->ort()*f);
                                                                  vit->markierung(0);
                                                                 };
                                                                ));
                                                                aktualisieren();
};
void _netz::skalieren(const _vektor3<_tg>&mitte,const _tg f){
                                                                _vertex*vit;
                                                                _polygon*pit;
                                                                _listenknoten<_vertex>*lnvit;
                                                                //--------
                                                                markierungvertex(1);
                                                                iterieren(pit,iterierenliste(pit,lnvit,vit=lnvit->objekt();
                                                                 if(vit->markierung()==1){
                                                                  vit->ort(mitte+ (vit->ort()-mitte)*f);
                                                                  vit->markierung(0);
                                                                 };
                                                                ));
                                                                aktualisieren();
};
void _netz::biegen(const _vektor3<_tg>&origin,const _vektor3<_tg>&rotaxis,const _vektor3<_tg>&waxis,const _tg w){
																//origin ist der biege mittelpunkt
																//rotaxis ist die achse, um die gebogen wird
																//waxis legt die biegungsebene fest (steht gewöhnlich rechtwinklig zu rotaxis)
																_tg a,b,c,bogen,radius,DR;
																_vektor3<_tg> la,lb,lc,tr,bender_mp,ma,e;
																_vertex*vit;
																_polygon*pit;
                                                                _listenknoten<_vertex>*lnvit;
																//----------------------------------------
																markierungvertex(1);
                                                                iterieren(pit,iterierenliste(pit,lnvit,vit=lnvit->objekt();
																 if(vit->markierung()==1){
																  vit->markierung(0);
																  bogen=waxis.laenge();
																  radius=(180*bogen)/(_pi*w);
																  bender_mp=rotaxis%waxis;
																  bender_mp.normalisieren();
																  bender_mp*=radius;  
								                                 
																  DR=determinieren(waxis,rotaxis,bender_mp);
																  e=vit->ort()-origin;
																  a=determinieren(e,rotaxis,bender_mp)/DR;
																  b=determinieren(waxis,e,bender_mp)/DR;
																  c=determinieren(waxis,rotaxis,e)/DR;
																 
																  la=waxis*a;
																  lb=rotaxis*b;
																  lc=bender_mp*c;
																  tr=bender_mp*-1;
																  tr.rotieren(rotaxis,-w*a);
																  lb.rotieren(rotaxis,-w*a);
																  lc.rotieren(rotaxis,-w*a);
																  tr+=origin+bender_mp+lb+lc;
																  vit->ort(tr);//tr-v);																  
																 };
																));
																aktualisieren();
};                                 
void _netz::verdrehen(const _vektor3<_tg>&o,const _vektor3<_tg>&a,const _tg w){
                                                                _polygon*pit;
                                                                _vertex*vit;
                                                                _vektoranalysis3<_tg> v3;
                                                                _vektor3<_tg> e,h;
                                                                _vektor3<_tg> lot;
                                                                _tg para;
                                                                _listenknoten<_vertex>*lnvit;
                                                                //--------------
                                                                markierungvertex(1);
                                                                iterieren(pit,iterierenliste(pit,lnvit,vit=lnvit->objekt();
                                                                 if(vit->markierung()==1){
                                                                  v3.lotpunktgerade(vit->ort(),o,a,lot,para);
                                                                  v3.rotieren(a,(vit->ort()-o),w*para,e);
                                                                  h=o+e;
                                                                  vit->ort(h);
                                                                  vit->markierung(0);
                                                                 };
                                                                ));
                                                                aktualisieren();
};
//------------------------------------------------------------- markierungsmethoden ------------------------------------------------------------------



void _netz::markierungkante(int s){
                                                                _polygon*pit;
                                                                //--------
                                                                if(anfang(pit))do{
                                                                 pit->markierungkante(s);
                                                                }while(naechstes(pit));
};

void _netz::markierungvertex(int f){
                                                                _polygon*pit;
                                                                //------------------------
                                                                if(anfang(pit))do{
                                                                 pit->markierungvertex(f);
                                                                }while(naechstes(pit));
};

void _netz::markierungverbinder(int f)const{
                                                                _polygon*pit;
                                                                //------------------------
                                                                if(anfang(pit))do{
                                                                 pit->markierungverbinder(f);
                                                                }while(naechstes(pit));
};

void _netz::markierungpolygon(int f){
                                                                _polygon*pit;
                                                                //-------
                                                                if(anfang(pit))do{
                                                                 pit->markierung(f);
                                                                }while(naechstes(pit));
};
void _netz::markierungpolygon(_polygon*pit,unsigned int anzahl,int f){
                                                                unsigned int i;
                                                                //-------
                                                                for(i=0;i<anzahl;i++){
                                                                 pit->markierung(f);
                                                                 pit=pit->naechstes();
                                                                };
};

void _netz::markierungpolygonstatus(int s){
                                                                _polygon*pit;
                                                                //-----------
                                                                if(anfang(pit))do{
                                                                 pit->status(s);
                                                                }while(naechstes(pit));
};

void _netz::markierungpolygonanwahl(int s){
                                                                _polygon*pit;
                                                                //-----------
                                                                if(anfang(pit))do{
                                                                 pit->anwahl(s);
                                                                }while(naechstes(pit));
};

void _netz::markierungvertexstatus(int s){
                                                                _polygon*pit;
                                                                //--------
                                                                if(anfang(pit))do{
                                                                 pit->markierungvertexstatus(s);
                                                                }while(naechstes(pit));
};
void _netz::kollisionszaehlerverbinder(unsigned int i){
                                                                _polygon*pit;
                                                                _listenknoten<_vertex>*lnvit;
                                                                _listenknoten<_polygon>*lnpit;
                                                                _verbindervertexpolygon*cit;
                                                                //--------
                                                                iterieren(pit,iterierenliste(pit,lnvit,iterierenliste(lnvit->objekt(),lnpit, 
                                                                 cit=static_cast<_verbindervertexpolygon*>(lnpit);
                                                                 cit->kollisionszaehler(i);
                                                                )));
};

//------------------------------------------------------------- elementschnittstelle ------------------------------------------------------------------

void _netz::textur(_textur<_tb>*t){               //textur setzen
                                                                _polygon*pit;
                                                                //----------
                                                                if(anfang(pit))do{
                                                                 pit->textur(t);
                                                                }while(naechstes(pit));
};             

void _netz::verwendentextur(const bool b){               //textur verwenden ein,aus
                                                                _polygon*pit;
                                                                //----------
                                                                if(anfang(pit))do{
                                                                 pit->verwendentextur(b);
                                                                }while(naechstes(pit));
};

void _netz::verwendentexturdynamisch(const bool b){      //dynamische textur verwenden ein,aus
                                                                _polygon*pit;
                                                                //----------
                                                                if(anfang(pit))do{
                                                                 pit->verwendentexturdynamisch(b);
                                                                }while(naechstes(pit));
};
void _netz::lightmaptexelgroesse(const _tg t){
                                                                _polygon*pit;
                                                                //----------
                                                                if(anfang(pit))do{
                                                                 pit->lightmaptexelgroesse(t);
                                                                }while(naechstes(pit));
};
void _netz::verwendenverbinderfarbe(const bool b){       //connectorfarbe verwenden ein,aus
                                                                _polygon*pit;
                                                                //----------
                                                                if(anfang(pit))do{
                                                                 pit->verwendenverbinderfarbe(b);
                                                                }while(naechstes(pit));
};

void _netz::zeichnenflaeche(const bool b){               //flaeche zeichnen ein,aus
                                                                _polygon*pit;
                                                                //----------
                                                                if(anfang(pit))do{
                                                                 pit->zeichnenflaeche(b);
                                                                }while(naechstes(pit));
};

void _netz::zeichnenkante(const bool b){                        //kanten zeichnen ein aus,
                                                                _polygon*pit;
                                                                //----------
                                                                if(anfang(pit))do{
                                                                 pit->zeichnenkante(b);
                                                                }while(naechstes(pit));
};
void _netz::zeichnennormale(const bool b){                      //normale zeichnen ein,aus
                                                                _polygon*pit;
                                                                //----------
                                                                if(anfang(pit))do{
                                                                 pit->zeichnennormale(b);
                                                                }while(naechstes(pit));
};
void _netz::normaleinterpoliert(const bool b){                   //normaleinterpoliert ein,aus
                                                                _polygon*pit;
                                                                //----------
                                                                if(anfang(pit))do{
                                                                 pit->normaleinterpoliert(b);
                                                                }while(naechstes(pit));
};
void _netz::zweiseitig(const bool b){                           //zweiseitig zeichnen ein,aus
                                                                _polygon*pit;
                                                                //----------
                                                                if(anfang(pit))do{
                                                                 pit->zweiseitig(b);
                                                                }while(naechstes(pit));
};
void _netz::maskiert(const bool b){                             //maskiert zeichnen ein,aus
                                                                _polygon*pit;
                                                                //----------
                                                                if(anfang(pit))do{
                                                                 pit->maskiert(b);
                                                                }while(naechstes(pit));
};
void _netz::aufgehellt(const bool b){                           //aufgehellt zeichnen ein,aus
                                                                _polygon*pit;
                                                                //----------
                                                                if(anfang(pit))do{
                                                                 pit->aufgehellt(b);
                                                                }while(naechstes(pit));
};
void _netz::kollision(const bool b){                           //spiegelnder ein,aus
                                                                _polygon*pit;
                                                                //----------
                                                                if(anfang(pit))do{
                                                                 pit->kollision(b);
                                                                }while(naechstes(pit));
};
void _netz::lightmapschattierung(const bool b){
                                                                _polygon*pit;
                                                                //----------
                                                                if(anfang(pit))do{
                                                                 pit->lightmapschattierung(b);
                                                                }while(naechstes(pit));
};
void _netz::spiegelnd(const bool b){                           //spiegelnder ein,aus
                                                                _polygon*pit;
                                                                //----------
                                                                if(anfang(pit))do{
                                                                 pit->spiegelnd(b);
                                                                }while(naechstes(pit));
};
void _netz::dynamischschattierend(const bool b){               //schattierend ein,aus           
                                                                _polygon*pit;
                                                                //----------
                                                                if(anfang(pit))do{
                                                                 pit->dynamischschattierend(b);
                                                                }while(naechstes(pit));
};
void _netz::dynamischschattiert(const bool b){                 //schattiert ein,aus
                                                                _polygon*pit;
                                                                //----------
                                                                if(anfang(pit))do{
                                                                 pit->dynamischschattiert(b);
                                                                }while(naechstes(pit));
};

void _netz::transparenz(const bool b){                   //transparent zeichnen ein,aus
                                                                _polygon*pit;
                                                                //----------
                                                                if(anfang(pit))do{
                                                                 pit->transparenz(b);
                                                                }while(naechstes(pit));
};
void _netz::transparenzadditiv(const bool b){                   //transparent zeichnen ein,aus
                                                                _polygon*pit;
                                                                //----------
                                                                if(anfang(pit))do{
                                                                 pit->transparenzadditiv(b);
                                                                }while(naechstes(pit));
};

void _netz::transparenzfaktor(_tg f){              //transparentsfaktor setzen 0..1
                                                                _polygon*pit;
                                                                //----------
                                                                if(anfang(pit))do{
                                                                 pit->transparenzfaktor(f);
                                                                }while(naechstes(pit));
};
void _netz::debuggen(const bool b){
                                                                _polygon*pit;
                                                                //----------
                                                                if(anfang(pit))do{
                                                                 pit->debuggen(b);
                                                                }while(naechstes(pit));
};
void _netz::farbe(const _vektor4<_to> c){
                                                                _polygon*pit;
                                                                //----------
                                                                if(anfang(pit))do{
                                                                 pit->farbe(c);
                                                                }while(naechstes(pit));
};

void _netz::farbekante(const _vektor4<_to> c){
                                                                _polygon*pit;
                                                                //----------
                                                                if(anfang(pit))do{
                                                                 pit->farbekante(c);
                                                                }while(naechstes(pit));
};

void _netz::farbeverbinder(const _vektor4<_to> c){
                                                                _polygon*p;
                                                                _listenknoten<_vertex>*lnv;
                                                                _verbindervertexpolygon*vcp;
                                                                //--------
                                                                iterieren(p,iterierenliste(p,lnv,
                                                                 vcp=static_cast<_verbindervertexpolygon*>(lnv);
                                                                 vcp->farbe(c);
                                                                ));
};
void _netz::opazitaetverbinder(const _tg o){
                                                                _polygon*p;
                                                                _listenknoten<_vertex>*lnv;
                                                                _verbindervertexpolygon*vcp;
                                                                //--------
                                                                iterieren(p,iterierenliste(p,lnv,
                                                                 vcp=static_cast<_verbindervertexpolygon*>(lnv);
                                                                 vcp->opazitaet(o);
                                                                ));
};
void _netz::multiplizierenfarbeverbinder(const _to f){
                                                                _polygon*p;
                                                                _listenknoten<_vertex>*lnv;
                                                                _verbindervertexpolygon*vcp;
                                                                //--------
                                                                iterieren(p,iterierenliste(p,lnv,
                                                                 vcp=static_cast<_verbindervertexpolygon*>(lnv);
                                                                 vcp->multiplizierenfarbe(f);
                                                                ));
};
void _netz::glanz(const _vektor4<_to>&f){//glanz aller polygone setzen
                                                                _polygon*pit;
                                                                iterieren(pit,pit->glanz(f));
};
void _netz::glanzbreite(const _to c){//glanzbreite aller polygone setzen
                                                                _polygon*pit;
                                                                 iterieren(pit,pit->glanzbreite(c));
};
void _netz::emission(const _vektor4<_to>&f){//emission aller polygone setzen
                                                                _polygon*pit;
                                                                iterieren(pit,pit->emission(f));
};
void _netz::invertieren(){
                                                                _polygon*pit;
                                                                iterieren(pit,pit->invertieren());
                                                                if(psubtractive) psubtractive=false; else psubtractive=true;
};
void _netz::invertierenausrichtung(_polygon*p,unsigned int anzahl){//nicht empfohlen
                                                                _polygon*pit;
                                                                unsigned int n;
                                                                //----------
                                                                pit=p;
                                                                for(n=0;n<anzahl;n++){
                                                                 pit->invertieren();
                                                                 pit=pit->naechstes();
                                                                };
};

void _netz::anwahl(int i){ //selektionsstatus setzen
                                                                _polygon*pit;
                                                                iterieren(pit,pit->anwahl(i));
};
_tg _netz::brechzahl()const{ //brechzahl zurückgeben
                                                                return(pbrechzahl);
};
void _netz::brechzahl(_tg b){ //brechzahl setzen
                                                                if(b<1) b=1;
                                                                pbrechzahl=b;
};
void _netz::dispersionsskalierung(_tg b){                  
                                                                pdispersionsskalierung=b;
};
_tg _netz::dispersionsskalierung()const{                  
                                                                return(pdispersionsskalierung);
};
void _netz::nurkollisionskopplung(const bool b){
                                                                pnurkollisionskopplung=b;
                                                                _polygon*pit;
                                                                iterieren(pit,pit->nurkollisionskopplung(b));
};
bool _netz::nurkollisionskopplung()const{
                                                                return(pnurkollisionskopplung);
};
void _netz::nichtspeichern(const bool b){
                                                                pnichtspeichern=b;
};
bool _netz::nichtspeichern()const{
                                                                return(pnichtspeichern);
};
_tg _netz::brechzahldispersiv(const _tg nm)const{     
                                                                _tg lnm=nm;
                                                                if(lnm<350) lnm=350;
                                                                if(lnm>750) lnm=750;
                                                                lnm-=350;
                                                                lnm=lnm/_tg(750-350);
                                                                lnm+=1.5;
                                                                lnm=1.0f/lnm;
                                                                lnm-=0.5;
                                                                lnm*=pdispersionsskalierung;
                                                                lnm+=pbrechzahl;
                                                                if(lnm<1) lnm=1;
                                                                return(lnm);
};
void _netz::erzeugenvertexlicht(){
                                                                _polygon*pit;
                                                                _licht<_tg,_to>*lit;
                                                                _vertex*vit;
                                                                _verbindervertexpolygon*vp;
                                                                _verbindervertexpolygon*bit;
                                                                _to t;
                                                                _vektor4<_to> c;
                                                                _vektor3<_to> c3;
                                                                _listenknoten<_vertex>*lnv;
                                                                _listenknoten<_polygon>*lnp;
                                                                _vektor3<_tg> d;
                                                                _vektor3<_tg> dn;
                                                                _tg sp;
                                                                _vektor3<_tg> n;
                                                                //------------
                                                                iterieren(pit,
                                                                 iterierenliste(pit,lnv,
                                                                  vit=lnv->objekt();
                                                                  vp=static_cast<_verbindervertexpolygon*>(lnv);
                                                                  t=vp->farbe()[3];
                                                                  vp->farbe(_vektor4<_to>(0.05f,0.05f,0.05f,t));
                                                                 );
                                                                 if(pworld){
                                                                  iterierenliste(pworld,lit,
                                                                   //funktion führt bestrahlung aus
                                                                   iterierenliste(pit,lnv,
                                                                    vit=lnv->objekt();
                                                                    vp=static_cast<_verbindervertexpolygon*>(lnv);
                                                                    t=vp->farbe()[3];
                                                                    d=vit->ort() - lit->ort();
                                                                    dn=d;
                                                                    dn.normalisieren();
                                                                    if(pit->normaleinterpoliert()){
                                                                     iterierenliste(vit,lnp,
                                                                      bit=static_cast<_verbindervertexpolygon*>(lnp);
                                                                      if(bit->polygon()->normaleinterpoliert()) n+=bit->polygon()->normale();
                                                                     );
                                                                     n.normalisieren();
                                                                     sp=dn*n;
                                                                    }else{
                                                                     sp=dn*pit->normale();
                                                                    };
                                                                    if(sp<0){
                                                                     c3=lit->farbedynamisch();
                                                                     c.setzenkomponente(0,c3[0]);
                                                                     c.setzenkomponente(1,c3[1]);
                                                                     c.setzenkomponente(2,c3[2]);
                                                                     c*=_to(-sp)*lit->intensitaetdynamisch()/_to(pow((_to(d.laenge())+1),1.3f));
                                                                     vp->farbe(vp->farbe()+_vektor4<_to>(c[0],c[1],c[2],t));
                                                                    };
                                                                   );
                                                                  );
                                                                  iterierenliste(pit,lnv,
                                                                   vit=lnv->objekt();
                                                                   vp=static_cast<_verbindervertexpolygon*>(lnv);
                                                                   c=vp->farbe();
                                                                   c.begrenzen(0,1);
                                                                   vp->farbe(c);
                                                                  );
                                                                 };
                                                                );
                                                                
};
void _netz::erzeugenvertexlicht(_licht<_tg,_to>*lit){
                                                                _polygon*pit;
                                                                _vertex*vit;
                                                                _verbindervertexpolygon*bit;                                                                
                                                                _verbindervertexpolygon*vp;
                                                                _listenknoten<_vertex>*lnv;
                                                                _listenknoten<_polygon>*lnp;
                                                                _to t;
																_vektor3<_tg> n;
                                                                _vektor4<_to> c;
                                                                _vektor3<_to> c3;
                                                                _vektor3<_tg> d;
                                                                _vektor3<_tg> dn;
                                                                _tg sp;
                                                                //------------
                                                                iterieren(pit, 
                                                                 //funktion führt bestrahlung aus, einzel- beleuchtungspass mit lit
                                                                 iterierenliste(pit,lnv,
                                                                  vit=lnv->objekt();
                                                                  vp=static_cast<_verbindervertexpolygon*>(lnv);
                                                                  t=vp->farbe()[3];
                                                                  d=vit->ort()-lit->ort();
                                                                  dn=d;
                                                                  dn.normalisieren();
                                                                  if(pit->normaleinterpoliert()){
                                                                   iterierenliste(vit,lnp,
                                                                    bit=static_cast<_verbindervertexpolygon*>(lnp);
                                                                    if(bit->polygon()->normaleinterpoliert()) n+=bit->polygon()->normale();
                                                                   );
                                                                   n.normalisieren();
                                                                   sp=dn*n;
                                                                  }else{
                                                                   sp=dn*pit->normale();
                                                                  };
                                                                  if(sp<0){
                                                                   c3=lit->farbedynamisch();
                                                                   c.setzenkomponente(0,c3[0]);
                                                                   c.setzenkomponente(1,c3[1]);
                                                                   c.setzenkomponente(2,c3[2]);
                                                                   c*=_to(-sp)*lit->intensitaetdynamisch()/_to(pow((_to(d.laenge())+1),1.3f));
                                                                   vp->farbe(vp->farbe()+_vektor4<_to>(c[0],c[1],c[2],t));
                                                                  };
                                                                  c=vp->farbe();
                                                                  c.begrenzen(0,1);
                                                                  vp->farbe(c);
                                                                 );
                                                                );
};
void _netz::erzeugenvertexlicht(_partition::_zone*z){
                                                                _polygon*pit;
                                                                _partition::_sektor*sit;
                                                                _licht<_tg,_to>*lit;
                                                                _vertex*vit;
                                                                _verbindervertexpolygon*vp;
                                                                _to t;
                                                                _vektor4<_to> c;
                                                                _vektor3<_to> c3;
                                                                _vektor3<_tg> d;
                                                                _vektor3<_tg> dn;
                                                                _tg sp;
                                                                _vektor3<_tg> n;
                                                                _verbindervertexpolygon*bit;
                                                                _listenknoten<_vertex>*lnv;
                                                                _listenknoten<_polygon>*lnp;
                                                                //------------
                                                                iterieren(pit,
                                                                 iterierenliste(pit,lnv,
                                                                  vit=lnv->objekt();
                                                                  vp=static_cast<_verbindervertexpolygon*>(lnv);
                                                                  t=vp->farbe()[3];
                                                                  vp->farbe(_vektor4<_to>(0.05f,0.05f,0.05f,t));
                                                                 );
                                                                 iterierenliste(z,sit,iterierenliste(sit,lit,
                                                                  //funktion führt bestrahlung aus
                                                                  iterierenliste(pit,lnv,
                                                                   vit=lnv->objekt();
                                                                   vp=static_cast<_verbindervertexpolygon*>(lnv);
                                                                   t=vp->farbe()[3];
                                                                   d=vit->ort()-lit->ort();
                                                                   dn=d;
                                                                   dn.normalisieren();
                                                                   if(pit->normaleinterpoliert()){
                                                                    iterierenliste(vit,lnp,
                                                                     bit=static_cast<_verbindervertexpolygon*>(lnp);
                                                                     if(bit->polygon()->normaleinterpoliert()) n+=bit->polygon()->normale();
                                                                    );
                                                                    n.normalisieren();
                                                                    sp=dn*n;
                                                                   }else{
                                                                    sp=dn*pit->normale();
                                                                   };
                                                                   if(sp<0){
                                                                    c3=lit->farbedynamisch();
                                                                    c.setzenkomponente(0,c3[0]);
                                                                    c.setzenkomponente(1,c3[1]);
                                                                    c.setzenkomponente(2,c3[2]);
                                                                    c*=_to(-sp)*lit->intensitaetdynamisch()/_to(pow((_to(d.laenge())+1),1.3f));
                                                                    vp->farbe(vp->farbe()+_vektor4<_to>(c[0],c[1],c[2],t));
                                                                   };
                                                                  );
                                                                 ));
                                                                 //normalisierung ?
                                                                 iterierenliste(pit,lnv,
                                                                  vit=lnv->objekt();
                                                                  vp=static_cast<_verbindervertexpolygon*>(lnv);
                                                                  c=vp->farbe();
                                                                  c.begrenzen(0,1);
                                                                  vp->farbe(c);                                                                  
                                                                 );
                                                                );
};
//------------------------------------------------------------- struktoroperationen ------------------------------------------------------------------
void _netz::verschweissen(_vertex*v0,_vertex*vm){
                                                                _liste<_verbindervertexpolygon > connectors;
                                                                _liste<_polygon> vmpolygons;
                                                                _listenknoten<_polygon >*lnp;
                                                                _listenknoten<_verbindervertexpolygon >*lncit;
                                                                //------------------------
                                                                iterierenliste(vm,lnp,
                                                                 connectors.einhaengen(static_cast<_verbindervertexpolygon*>(lnp));
                                                                 vmpolygons.einhaengen(lnp->objekt());
                                                                );
                                                                iterierenliste(&connectors,lncit,lncit->objekt()->_listenknoten<_vertex>::objekt(v0));
                                                                v0->_liste<_polygon>::vereinigen(vm);
                                                                connectors.aushaengen();
                                                                /*
                                                                iterierenliste(vm,lnp,//if(vm->anfang(cit))do{
                                                                 cit=static_cast<_verbindervertexpolygon*>(lnp);
                                                                 //zeigen beteiligte poly auf vm ?
                                                                 //alle polygone, der
                                                                 pit=cit->polygon();
                                                                 vmpolygons.einhaengen(pit);
                                                                 if(pit->vertex()==vm){
                                                                  polygons.einhaengen(pit);
                                                                 };
                                                                 //zeigen connectoren auf vm ?
                                                                 iterierenliste(pit,lnvit,
                                                                  vit=lnvit->objekt();
                                                                  iterierenliste(vit,lniit,
                                                                   iit=static_cast<_verbindervertexpolygon*>(lniit);
                                                                   if(iit->naechstervertex()==vm) connectors.einhaengen(iit);
                                                                  );
                                                                 );
                                                                );
                                                                //------------------------ alle objekte, die auf vm zeigen nun auf v0 verbiegen
                                                                //nicht mehr nötig, seitdem es den firstvertex zeiger (pvertex) in polygon nicht mehr gibt
                                                                if(polygons.anfang(lnpit))do{
                                                                 lnpit->objekt()->vertex(v0);
                                                                }while(polygons.naechstes(lnpit));
                                                                if(connectors.anfang(lncit))do{
                                                                 lncit->objekt()->naechstervertex(v0);
                                                                }while(connectors.naechstes(lncit));
                                                                //------------------------ die vm-connectoren in v0 übertragen
                                                                v0->vereinigen(vm);*/
                                                                //------------------------ vm löschen
                                                                delete vm;
                                                                vm=0;
                                                                //------------------------ erzwingeninvarianz
                                                                iterierenliste(&vmpolygons,lnp,lnp->objekt()->erzwingeninvarianz());
};

void _netz::einhaengen(_welt*w){
                                                                _listenknotenbasis<_netz >::einhaengen(w);
                                                                pworld=w;
};

void _netz::anlegentexturkoordinaten(unsigned int li){
                                                                _polygon*p;
                                                                iterieren(p,p->anlegentexturkoordinaten(li));
};
void _netz::verschiebentexturkoordinaten(const _vektor2<_tg>&v,unsigned int li){
                                                                _polygon*p;
                                                                iterieren(p,p->verschiebentexturkoordinaten(v,li));
};
void _netz::loeschentexturkoordinaten(unsigned int li){
                                                                _polygon*p;
                                                                iterieren(p,p->loeschentexturkoordinaten(li));
};

void _netz::anlegenlightmap(_texturverwaltung<_tb>*tv,_zeichenkette<char> name,unsigned int wx,unsigned int wy){
                                                                _polygon*p;
                                                                int i;
                                                                _zeichenkette<char> e;
                                                                _zeichenkette<char> tga=".tga";
                                                                _zeichenkette<char> h;
                                                                char buff[1024];
                                                                //------------
                                                                i=0;
                                                                if(anfang(p))do{
                                                                 _itoa(i,buff,16);
                                                                 h=buff;
                                                                 while(h.groesse()<8) h.anhaengenfront("0");
                                                                 e=name;
                                                                 e+=h;
                                                                 e+=tga;                                                                
                                                                 p->anlegenlightmap(tv,e,wx,wy);
                                                                 i++;
                                                                }while(naechstes(p));
                                                        
};

void _netz::anlegenlightmap(_texturverwaltung<_tb>*tv,_zeichenkette<char> name,_tg sk){
                                                                _polygon*p;
                                                                int i;
                                                                _zeichenkette<char> e;
                                                                _zeichenkette<char> tga=".tga";
                                                                _zeichenkette<char> h;
                                                                char buff[1024];
                                                                //------------
                                                                i=0;
                                                                if(anfang(p))do{
                                                                 _itoa(i,buff,16);
                                                                 h=buff;
                                                                 while(h.groesse()<8) h.anhaengenfront("0");
                                                                 e=name;
                                                                 e+=h;
                                                                 e+=tga;                                                                
                                                                 p->anlegenlightmap(tv,e,sk);
                                                                 i++;
                                                                }while(naechstes(p));
                                                        
};
/*
void _netz::loeschenlightmap(){
                                                                _polygon*p;
                                                                //------------
                                                                if(anfang(p))do{
                                                                 p->loeschenlightmap();
                                                                }while(naechstes(p));
};
*/
void _netz::bestrahlenlightmap(){
                                                                _polygon*p;
                                                                _bestrahler B;  
                                                                iterieren(p,B.bestrahlenlightmap(pworld,p));
};

void _netz::uebergebenlightmap(_grafik*g){
                                                                _bild<_tb>*lmap;
                                                                _polygon*p;
                                                                //------------
                                                                iterieren(p,
                                                                 if(p->texturdynamisch()){
                                                                  _listenknoten<_bild<_tb> >*lnlmap;
                                                                  p->texturdynamisch()->lightmap()->anfang(lnlmap);
                                                                  lmap=lnlmap->objekt();
                                                                  g->erzeugenbild(lmap);
                                                                 };
                                                                );
                                                                
                                                                
};
//-------------------------------------------------------------- schattenvolumen ---------------------------------------------------------------------------------------------
void _netz::erzeugenschatten(_licht<_tg,_to>*l,_tg laenge){
                                                                //1. kante ungültig aufgrund der geometrischen lage
                                                                //2. kante gültig aufgrund der geometrischen lage
                                                                //3. kante hat keinen nachbarn, ist gültig
                                                                _netzschatten*it;
                                                                if(l->schattenvolumen()){
                                                                 if(anfang(it))do{
                                                                  if(it->licht()==l) return;
                                                                 }while(naechstes(it));
														 		 new _netzschatten(this,pworld,l,laenge);
																};
};
void _netz::loeschenschatten(){
																_listebasis<_netzschatten>::loeschen();
};
void _netz::anfangschatten(){
                                                                anfang(pschatteniterator);                      
};
void _netz::naechsterschatten(){
                                                                naechstes(pschatteniterator);
};
_netzschatten*_netz::schatteniterator(){
                                                                return(pschatteniterator);
};
void _netz::zeichnenschatten(_grafik*gra,_licht<_tg,_to>*lit){
                                                                _netzschatten*it;
                                                                //----------------
                                                                if(anfang(it))do{
                                                                 if(it->licht()==lit) {
                                                                  it->zeichnen(gra);
                                                                  return;
                                                                 };
                                                                }while(naechstes(it));
};  

//-------------------------------------------------------------- kanten ---------------------------------------------------------------------------------------------
void _netz::verknuepfenverbindervertexpolygon(){
                                                                _polygon*p;
                                                                _listenknoten<_vertex>*lnv;
                                                                _verbindervertexpolygon*cit;
                                                                //-----------
                                                                iterieren(p,iterierenliste(p,lnv,
                                                                 cit=static_cast<_verbindervertexpolygon*>(lnv);
                                                                 cit->verknuepfen();
                                                                ));
};
void _netz::erzeugenkante(){
                                                                _polygon*p;
                                                                iterieren(p,p->erzeugenkante());
};
void _netz::loeschenkante(){
                                                                _polygon*p;
                                                                iterieren(p,p->loeschenkante());
};
void _netz::erzeugendreieck(){
                                                                _polygon*p;
                                                                iterieren(p,p->erzeugendreieck());
};
//------------------------------------------------------------- Block funktionen ---------------------------------------------------------------------------------------------------
bool _netz::indiziert()const{
                                                                if(pblock) return(true); else return(false);
};
void _netz::erzeugenindex(){
                                                                _polygon*pit;
                                                                _vertex*vit;
                                                                _listenknoten<_vertex>*lnv;
                                                                //------------------------------
                                                                loeschenindex();
                                                                markierungvertex(1);
                                                                iterieren(pit,iterierenliste(pit,lnv,
                                                                 panzahlverbinder++;
                                                                 vit=lnv->objekt();
                                                                 if(vit->markierung()==1){
                                                                  vit->markierung(0);
                                                                  //_listebasis<_vertex>::einhaengen(vit); sind schon drinnen
                                                                  panzahlvertex++;
                                                                 };
                                                                )); 
                                                                
                                                                if(panzahlverbinder>0){
                                                                 pverbinderfeld=new _verbindervertexpolygon*[panzahlverbinder];
                                                                 pblock=new _tg[panzahlverbinder*(3+3+4+2*2)];
                                                                 unsigned int i=0;
                                                                 iterieren(pit,iterierenliste(pit,lnv,pverbinderfeld[i++]=static_cast<_verbindervertexpolygon*>(lnv)));
                                                                 //folgende initialisierung setzt blockformat 
                                                                 //xyz, nx,ny,nz, r,g,b,a, tx0,ty0,tx1,ty1 voraus
                                                                 unsigned int bmi=0;
                                                                 for (unsigned int n=0;n<panzahlverbinder;n++){
                                                                  *(pblock+n*14+0)=(*pverbinderfeld[n]->vertex())[0];
                                                                  *(pblock+n*14+1)=(*pverbinderfeld[n]->vertex())[1];
                                                                  *(pblock+n*14+2)=(*pverbinderfeld[n]->vertex())[2];
                                                                  *(pblock+n*14+3)=pverbinderfeld[n]->vertex()->normale()[0];
                                                                  *(pblock+n*14+4)=pverbinderfeld[n]->vertex()->normale()[1];
                                                                  *(pblock+n*14+5)=pverbinderfeld[n]->vertex()->normale()[2];
                                                                  *(pblock+n*14+6)=pverbinderfeld[n]->farbe()[0];
                                                                  *(pblock+n*14+7)=pverbinderfeld[n]->farbe()[1];
                                                                  *(pblock+n*14+8)=pverbinderfeld[n]->farbe()[2];
                                                                  *(pblock+n*14+9)=pverbinderfeld[n]->farbe()[3];
                                                                  *(pblock+n*14+10)=pverbinderfeld[n]->holenvektor(bmi,0)[0];
                                                                  *(pblock+n*14+11)=pverbinderfeld[n]->holenvektor(bmi,0)[1];
                                                                  *(pblock+n*14+12)=0;
                                                                  *(pblock+n*14+13)=0;
                                                                  //nun die zeiger in folgenden klassen setzen
                                                                  //_verbindervertexpolygon,_bildvektor
                                                                  pverbinderfeld[n]->blockzeiger(pblock+n*14);
                                                                  pverbinderfeld[n]->holenvektor(bmi,0).blockzeiger(pblock+n*14+10);
                                                                  pverbinderfeld[n]->holenvektor(bmi,1).blockzeiger(pblock+n*14+12);
                                                                 };
                                                                 iterieren(pit,pit->erzeugenindex());
                                                                };
};
void _netz::loeschenindex(){
                                                                _listenknoten<_vertex>*lnv;
                                                                _polygon*pit;
                                                                _vertex*vit;
                                                                _verbindervertexpolygon*cit;
                                                                unsigned int bmi=0;
                                                                //----------------------------
                                                                if(pblock){
                                                                 delete[] pblock;
                                                                 //_liste<_vertex>::aushaengen(); bleiben drinnen
                                                                 if(pverbinderfeld) delete[] pverbinderfeld;
                                                                 panzahlvertex=0;
                                                                 panzahlverbinder=0;
                                                                 iterieren(pit,
                                                                  pit->loeschenindex();
                                                                  iterierenliste(pit,lnv,
                                                                   vit=lnv->objekt();
                                                                   cit=static_cast<_verbindervertexpolygon*>(lnv);
                                                                   cit->blockzeiger(0);
                                                                   cit->holenvektor(bmi,0).blockzeiger(0);
                                                                   cit->holenvektor(bmi,1).blockzeiger(0);
                                                                  );
                                                                 );
                                                                };
};
int _netz::indexverbinder(_verbindervertexpolygon*cit){
                                                                if(pverbinderfeld) for(unsigned int n=0;n<panzahlverbinder;n++) if(pverbinderfeld[n]==cit) return(n);
                                                                return(-1);
};
//------------------------------------------------------------- Aktualisierung ---------------------------------------------------------------------------------------------------
void _netz::aktualisieren() {
                                                                _polygon*p;
                                                                iterieren(p,p->aktualisieren());
                                                                iterieren(p,if(p->normaleinterpoliert()) p->aktualisierenvertexinterpoliertenormale());
                                                                
};
void _netz::aktualisierenpolygonmitte(){
                                                                _polygon*p;
                                                                iterieren(p,p->aktualisierenmitte());
};
void _netz::aktualisierensektor(_partition::_zone*zone){
                                                                _polygon*p;
                                                                _liste<_partition::_sektor>::aushaengen();
                                                                iterieren(p,p->_liste<_partition::_sektor>::aushaengen());
                                                                zone->einfuegenintern(this);
};
void _netz::aktualisierenschatten(){
                                                                aktualisierennetzschatten();
                                                                aktualisierenpolygonschatten();
};
void _netz::aktualisierennetzschatten(){
                                                                _netzschatten*nsit;
                                                                iterieren(nsit,nsit->aktualisieren());
};
void _netz::aktualisierenpolygonschatten(){
                                                                _polygon*p;
                                                                iterieren(p,p->aktualisierenschatten());
};
void _netz::aktualisierenbaum(){
                                                                _polygon*p;
                                                                _tg x0,x1,y0,y1,z0,z1;
                                                                _listenknoten<_partition::_sektor>*lnsit;
                                                                //--------------------------------------------
                                                                if(anfang(p))do{
                                                                 p->_liste<_baumoctalwuerfel<_polygon,_tg> >::aushaengen();
                                                                 p->umgrenzungsquader(x0,x1,y0,y1,z0,z1);
                                                                 if(p->_liste<_partition::_sektor>::anfang(lnsit))do{
                                                                  lnsit->objekt()->_baumoctal<_polygon,_tg>::einhaengen(p,x0,x1,y0,y1,z0,z1);
                                                                 }while(p->_liste<_partition::_sektor>::naechstes(lnsit));
                                                                }while(naechstes(p)); 
};
void _netz::optimierenpolygonstartvertex(){
                                                                _polygon*p;
                                                                iterieren(p,p->optimierenstartvertex());
};
void _netz::erzeugenvertexintersektion(){
                                                                //poly benötigen zur geweldeten duplication
                                                                //vertex-intersektion-vertex-pointer, diese intersektion werden hier angelegt
                                                                _polygon*p;
                                                                _listenknoten<_vertex>*lnv;
                                                                iterieren(p,iterierenliste(p,lnv,lnv->objekt()->erzeugenintersektionsverbinder(this,p)));
};
void _netz::loeschenvertexintersektion(){
                                                                _polygon*p;
                                                                _listenknoten<_vertex>*lnv;
                                                                iterieren(p,iterierenliste(p,lnv,lnv->objekt()->loeschenintersektionsverbinder()));
};

void _netz::nullintersektionvertices(){
                                                                //alle virtuellen intersektion werden durchiteriert
                                                                //und deren vertex-zeiger genullt, um sicherzugehen, dass
                                                                //beim duplizieren der intersectingmesh-dreiecke nicht an das
                                                                //intersectingmesh angebaut wird
                                                                _polygon*p;
                                                                _vertex*vit;
                                                                _intersektion*is;
                                                                _listenknoten<_vertex>*lnv;
                                                                //-------------------
                                                                iterieren(p,iterierenliste(p,lnv,
                                                                 vit=lnv->objekt();
                                                                 is=vit->intersektion();
                                                                 if(is)is->vertex=0;
                                                                ));
};
void _netz::vorbereitenintersektion() {
                                                                _polygon*p;
                                                                iterieren(p,p->vorbereitenintersektion());
};
unsigned int _netz::anzahlpolygon() const{
                                                                return(_listebasis<_polygon>::anzahl());
};
unsigned int _netz::anzahlvertex(){
                                                                _polygon*p;
                                                                _vertex*v;
                                                                _listenknoten<_vertex>*lnv;
                                                                unsigned int i;
                                                                //--------
                                                                markierungvertex(0);
                                                                i=0;
                                                                iterieren(p,iterierenliste(p,lnv,v=lnv->objekt();
                                                                 if(v->markierung()==0){
                                                                  v->markierung(1);
                                                                  i++;
                                                                 };
                                                                ));
                                                                return(i);
};

unsigned int _netz::anzahlverbindervertexpolygon(){
                                                                _polygon*p;
                                                                _listenknoten<_vertex>*lnv;
                                                                unsigned int i;
                                                                //--------
                                                                i=0;
                                                                iterieren(p,iterierenliste(p,lnv,i++));
                                                                return(i);
};

unsigned int _netz::anzahlbildvektor(){
                                                                _polygon*p;
                                                                _listenknoten<_vertex>*lnv;
                                                                _verbindervertexpolygon*vcpit;
                                                                unsigned int i;
                                                                //--------
                                                                markierungvertex(0);
                                                                i=0;
                                                                iterieren(p,iterierenliste(p,lnv,
                                                                 vcpit=static_cast<_verbindervertexpolygon*>(lnv);
                                                                 i+=vcpit->anzahlbildvektor();
                                                                ));
                                                                return(i);
};

unsigned int _netz::speicherlast() const{
                                                                _polygon*p;
                                                                unsigned int i;
                                                                //--------
                                                                i=0;
                                                                iterieren(p,
                                                                 i++;
                                                                );
                                                                return(i);
};

char _netz::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_netz>*sd){
                                                                char r=1;
                                                                r^=sd->ladenbeginn(fn);
                                                                r^=sd->ladenverschachtelung(fn);
                                                                r^=sd->ladenwert(psubtractive);
                                                                r^=sd->ladenwert(pflag);
                                                                r^=sd->ladenwert(pkeinbsp);
                                                                r^=sd->ladenwert(pdynamisch);
                                                                r^=sd->ladenwert(pschattenvolumen);
                                                                r^=sd->ladenwert(pschattenvolumenlaenge);
                                                                r^=sd->ladenwert(pbrechzahl);
                                                                r^=sd->ladenwert(pdispersionsskalierung);
                                                                r^=sd->ladenwert(pnurkollisionskopplung);
                                                                r^=sd->ladenwert(pnichtspeichern);
                                                                r^=sd->ladenwert(peditionort);
                                                                r^=sd->ladenwert(peditionebene[0]);
                                                                r^=sd->ladenwert(peditionebene[1]);
                                                                sd->ladenende();
                                                                return(r);
};
void _netz::speichern(_speicherbardynamisch<_netz>*sd){
                                                                sd->speichernbeginnblock();
                                                                sd->speichernverschachtelung();
                                                                sd->speichernwert(psubtractive);
                                                                sd->speichernwert(pflag);
                                                                sd->speichernwert(pkeinbsp);
                                                                sd->speichernwert(pdynamisch);
                                                                sd->speichernwert(pschattenvolumen);
                                                                sd->speichernwert(pschattenvolumenlaenge);
                                                                sd->speichernwert(pbrechzahl);
                                                                sd->speichernwert(pdispersionsskalierung);
                                                                sd->speichernwert(pnurkollisionskopplung);
                                                                sd->speichernwert(pnichtspeichern);
                                                                sd->speichernwert(peditionort);
                                                                sd->speichernwert(peditionebene[0]);
                                                                sd->speichernwert(peditionebene[1]);
                                                                sd->speichernendeblock();
};
char _netz::assoziieren(_speicherbardynamisch<_netz>*sd){
                                                                sd->assoziierenverschachtelung();
                                                                return(1);
};
void _netz::einhaengendialog(_dynamischerdialog*d){
                                                                d->editierbar(this);
                                                                d->loeschensektion(); 
                                                                _material<_tg>::einhaengendialog(d);
                                                                d->addierensektion(L"Netz");
                                                                d->sektion(L"Netz")->offen(true);
                                                                d->einhaengen(L"Netz",L"Subtraktiv",psubtractive);
                                                                d->einhaengen(L"Netz",L"Keine Teilnahme am Zonen BSP",pkeinbsp);
                                                                d->einhaengen(L"Netz",L"Dynamisch",pdynamisch);
                                                                d->einhaengen(L"Netz",L"Schattenvolumen",pschattenvolumen);
                                                                d->einhaengen(L"Netz",L"Schattenvolumenlänge",pschattenvolumenlaenge);
                                                                d->einhaengen(L"Netz",L"Markierung",pflag);
                                                                d->einhaengen(L"Netz",L"Brechzahl",pbrechzahl);
                                                                d->einhaengen(L"Netz",L"Dispersionsskalierung",pdispersionsskalierung); 
                                                                d->einhaengen(L"Netz",L"Nur Kollisionskopplung aufrufen",pnurkollisionskopplung); 
                                                                d->einhaengen(L"Netz",L"Nicht speichern",pnichtspeichern); 
                                                                _polygon*p;
                                                                if(anfang(p)){
                                                                
                                                                
                                                                
                                                                 _verbindervertexpolygon*v=p->vertex()->verbinder(p);
                                                                 d->einhaengen(L"Netz",L"Polygon : Verbinderfarbe",v->farbe()); 
                                                                 d->einhaengen(L"Netz",L"Polygon : Dynamische Textur verwenden",p->verwendentexturdynamisch());
                                                                 d->einhaengen(L"Netz",L"Polygon : Größe der Lightmaptexel",p->lightmaptexelgroesse());
                                                                 d->einhaengen(L"Netz",L"Polygon : Verbinderfarbe verwenden",p->verwendenverbinderfarbe());
                                                                 d->einhaengen(L"Netz",L"Polygon : Fläche zeichnen",p->zeichnenflaeche());
                                                                 d->einhaengen(L"Netz",L"Polygon : Kanten zeichnen",p->zeichnenkante());
                                                                 d->einhaengen(L"Netz",L"Polygon : Normale zeichnen",p->zeichnennormale());
                                                                 d->einhaengen(L"Netz",L"Polygon : Normale interpolieren",p->normaleinterpoliert());
                                                                 d->einhaengen(L"Netz",L"Polygon : Zweiseitig",p->zweiseitig());
                                                                 d->einhaengen(L"Netz",L"Polygon : Spiegelnd",p->spiegelnd());
                                                                 d->einhaengen(L"Netz",L"Polygon : Dynamisch schattierend",p->dynamischschattierend());
                                                                 d->einhaengen(L"Netz",L"Polygon : Dynamisch schattiert",p->dynamischschattiert());
                                                                 d->einhaengen(L"Netz",L"Polygon : Maskiert",p->maskiert());
                                                                 d->einhaengen(L"Netz",L"Polygon : Aufgehellt",p->aufgehellt());
                                                                 d->einhaengen(L"Netz",L"Polygon : Kollisionsteilnahme",p->kollision());
                                                                 d->einhaengen(L"Netz",L"Polygon : Schattierung von Lightmaps",p->lightmapschattierung());
                                                                 d->einhaengen(L"Netz",L"Polygon : Transparenz",p->transparenz());                              
                                                                 d->einhaengen(L"Netz",L"Polygon : Additive Transparenz",p->transparenzadditiv());                              
                                                                 d->einhaengen(L"Netz",L"Polygon : Debugschalter",p->debuggen());
                                                                 d->einhaengen(L"Netz",L"Polygon : Nur Kollisionskopplung",p->nurkollisionskopplung());
                                                                 d->einhaengen(L"Netz",L"Polygon : Transparentfaktor",p->transparenzfaktor()); 
                                                                 d->einhaengen(L"Netz",L"Polygon : Farbe",p->farbe());                         
                                                                 d->einhaengen(L"Netz",L"Polygon : Kantenfarbe",p->farbekante());              
                                                                 d->einhaengen(L"Netz",L"Polygon : Glanz",p->glanz());                         
                                                                 d->einhaengen(L"Netz",L"Polygon : Glanzbreite",p->glanzbreite());                         
                                                                 d->einhaengen(L"Netz",L"Polygon : Emission",p->emission());                         
                                                                 d->einhaengen(L"Netz",L"Polygon : Markierung",p->markierung());                     
                                                                };
};
void _netz::auslesendialog(_dynamischerdialog*d){
                                                                bool b;
                                                                _tg tg;
                                                                _vektor4<_to> c;
                                                                _to tof;
                                                                int i;
                                                                _material<_tg>::auslesendialog(d);
                                                                d->auslesen(L"Netz",L"Subtraktiv",b);
                                                                subtraktiv(b);
                                                                d->auslesen(L"Netz",L"Keine Teilnahme am Zonen BSP",pkeinbsp);
                                                                d->auslesen(L"Netz",L"Dynamisch",pdynamisch);
                                                                d->auslesen(L"Netz",L"Schattenvolumen",pschattenvolumen);
                                                                d->auslesen(L"Netz",L"Schattenvolumenlänge",pschattenvolumenlaenge);
                                                                d->auslesen(L"Netz",L"Markierung",pflag);
                                                                d->auslesen(L"Netz",L"Brechzahl",pbrechzahl);
                                                                d->auslesen(L"Netz",L"Dispersionsskalierung",pdispersionsskalierung); 
                                                                d->auslesen(L"Netz",L"Nur Kollisionskopplung aufrufen",pnurkollisionskopplung); 
                                                                d->auslesen(L"Netz",L"Nicht speichern",pnichtspeichern); 
                                                                
                                                                
                                                                if(d->beruehrt(L"Netz",L"Polygon : Verbinderfarbe")){
                                                                 d->auslesen(L"Netz",L"Polygon : Verbinderfarbe",c); 
                                                                 farbeverbinder(c);
                                                                };
                                                                if(d->beruehrt(L"Netz",L"Polygon : Dynamische Textur verwenden")){
                                                                 d->auslesen(L"Netz",L"Polygon : Dynamische Textur verwenden",b); 
                                                                 verwendentexturdynamisch(b);
                                                                };
                                                                if(d->beruehrt(L"Netz",L"Polygon : Größe der Lightmaptexel")){
                                                                 d->auslesen(L"Netz",L"Polygon : Größe der Lightmaptexel",tg); 
                                                                 lightmaptexelgroesse(tg);
                                                                };
                                                                if(d->beruehrt(L"Netz",L"Polygon : Verbinderfarbe verwenden")){
                                                                 d->auslesen(L"Netz",L"Polygon : Verbinderfarbe verwenden",b); 
                                                                 verwendenverbinderfarbe(b);
                                                                };
                                                                if(d->beruehrt(L"Netz",L"Polygon : Fläche zeichnen")){
                                                                 d->auslesen(L"Netz",L"Polygon : Fläche zeichnen",b); 
                                                                 zeichnenflaeche(b);
                                                                };
                                                                if(d->beruehrt(L"Netz",L"Polygon : Kanten zeichnen")){
                                                                 d->auslesen(L"Netz",L"Polygon : Kanten zeichnen",b); 
                                                                 zeichnenkante(b);
                                                                };
                                                                if(d->beruehrt(L"Netz",L"Polygon : Normale zeichnen")){
                                                                 d->auslesen(L"Netz",L"Polygon : Normale zeichnen",b); 
                                                                 zeichnennormale(b);
                                                                };
                                                                if(d->beruehrt(L"Netz",L"Polygon : Zweiseitig")){
                                                                 d->auslesen(L"Netz",L"Polygon : Zweiseitig",b); 
                                                                 zweiseitig(b);
                                                                };
                                                                if(d->beruehrt(L"Netz",L"Polygon : Normale interpolieren")){
                                                                 d->auslesen(L"Netz",L"Polygon : Normale interpolieren",b); 
                                                                 normaleinterpoliert(b);
                                                                };
                                                                if(d->beruehrt(L"Netz",L"Polygon : Spiegelnd")){
                                                                 d->auslesen(L"Netz",L"Polygon : Spiegelnd",b); 
                                                                 spiegelnd(b);
                                                                };
                                                                if(d->beruehrt(L"Netz",L"Polygon : Dynamisch schattierend")){
                                                                 d->auslesen(L"Netz",L"Polygon : Dynamisch schattierend",b); 
                                                                 dynamischschattierend(b);
                                                                };
                                                                if(d->beruehrt(L"Netz",L"Polygon : Dynamisch schattiert")){
                                                                 d->auslesen(L"Netz",L"Polygon : Dynamisch schattiert",b); 
                                                                 dynamischschattiert(b);
                                                                };
                                                                if(d->beruehrt(L"Netz",L"Polygon : Maskiert")){
                                                                 d->auslesen(L"Netz",L"Polygon : Maskiert",b); 
                                                                 maskiert(b);
                                                                };
                                                                if(d->beruehrt(L"Netz",L"Polygon : Aufgehellt")){
                                                                 d->auslesen(L"Netz",L"Polygon : Aufgehellt",b); 
                                                                 aufgehellt(b);
                                                                };
                                                                if(d->beruehrt(L"Netz",L"Polygon : Kollisionsteilnahme")){
                                                                 d->auslesen(L"Netz",L"Polygon : Kollisionsteilnahme",b); 
                                                                 kollision(b);
                                                                };
                                                                if(d->beruehrt(L"Netz",L"Polygon : Schattierung von Lightmaps")){
                                                                 d->auslesen(L"Netz",L"Polygon : Schattierung von Lightmaps",b); 
                                                                 lightmapschattierung(b);
                                                                };
                                                                if(d->beruehrt(L"Netz",L"Polygon : Transparenz")){
                                                                 d->auslesen(L"Netz",L"Polygon : Transparenz",b); 
                                                                 transparenz(b);
                                                                };                                               
                                                                if(d->beruehrt(L"Netz",L"Polygon : Additive Transparenz")){
                                                                 d->auslesen(L"Netz",L"Polygon : Additive Transparenz",b); 
                                                                 transparenzadditiv(b);
                                                                };
                                                                if(d->beruehrt(L"Netz",L"Polygon : Debugschalter")){
                                                                 d->auslesen(L"Netz",L"Polygon : Debugschalter",b); 
                                                                 debuggen(b);
                                                                };
                                                                if(d->beruehrt(L"Netz",L"Polygon : Nur Kollisionskopplung")){
                                                                 d->auslesen(L"Netz",L"Polygon : Nur Kollisionskopplung",b); 
                                                                 nurkollisionskopplung(b);
                                                                };
                                                                if(d->beruehrt(L"Netz",L"Polygon : Transparentfaktor")){
                                                                 d->auslesen(L"Netz",L"Polygon : Transparentfaktor",tg); 
                                                                 transparenzfaktor(tg);
                                                                };
                                                                if(d->beruehrt(L"Netz",L"Polygon : Farbe")){
                                                                 d->auslesen(L"Netz",L"Polygon : Farbe",c); 
                                                                 farbe(c);
                                                                };
                                                                if(d->beruehrt(L"Netz",L"Polygon : Kantenfarbe")){
                                                                 d->auslesen(L"Netz",L"Polygon : Kantenfarbe",c); 
                                                                 farbekante(c);
                                                                };
                                                                if(d->beruehrt(L"Netz",L"Polygon : Glanz")){
                                                                 d->auslesen(L"Netz",L"Polygon : Glanz",c); 
                                                                 glanz(c);
                                                                };
                                                                if(d->beruehrt(L"Netz",L"Polygon : Glanzbreite")){
                                                                 d->auslesen(L"Netz",L"Polygon : Glanzbreite",tof); 
                                                                 glanzbreite(tof);
                                                                };
                                                                if(d->beruehrt(L"Netz",L"Polygon : Emission")){
                                                                 d->auslesen(L"Netz",L"Polygon : Emission",c); 
                                                                 emission(c);
                                                                };
                                                                if(d->beruehrt(L"Netz",L"Polygon : Markierung")){
                                                                 d->auslesen(L"Netz",L"Polygon : Markierung",i); 
                                                                 markierung(i);
                                                                };
                                                                
};
_vektor3<_tg>&_netz::editionort(){
																return(peditionort);
};
_vektor3<_tg>&_netz::editionebene(const unsigned int i){
																if(i==0) return(peditionebene[0]); else return(peditionebene[1]);
};
bool _netz::laden(_dateispeicherbarbinaer*d){
																einhaengenspeicherung(d);
																ladenbeginn();
																d->laden(speichername());
																d->laden(psubtractive);
																d->laden(pkeinbsp);
																d->laden(pdynamisch);
																d->laden(pschattenvolumen);
																d->laden(pschattenvolumenlaenge);
																d->laden(pflag);
																d->laden(pbrechzahl);
																d->laden(pdispersionsskalierung);
																d->laden(pnurkollisionskopplung);
																d->laden(pnichtspeichern);
																d->laden(peditionort);
																d->laden(peditionebene[0]);
																d->laden(peditionebene[1]);
																
																ladenmaterial(d);
																unsigned int a,i;
																_vektor3<_tg> vn(0,0,0);
																
																_polygon*pit;
																_listebasis<_polygon>::loeschen();
																d->laden(a);
																L->l("Netz laden : Polygone werden geladen , Anzahl = ",(int)a);
																for(i=0;i<a;i++){
																 pit=new _polygon(this);
																 pit->laden(d);
																};

																_vertex*vit;
																d->laden(a);
																L->l("Netz laden : Vertex werden geladen , Anzahl = ",(int)a);
																for(i=0;i<a;i++){
																 vit=new _vertex(this,vn);
																 vit->laden(d);
																};
																
																_liste<_partition::_sektor>::aushaengen();
																a=ladenanzahl(d);
																L->l("Netz laden : Sektorverbinder werden geladen , Anzahl = ",(int)a);
																for(i=0;i<a;i++) ladenzeiger(d);
																return(true);
};
void _netz::speichern(_dateispeicherbarbinaer*d){
																d->speichern(speichername());
																d->speichern(psubtractive);
																d->speichern(pkeinbsp);
																d->speichern(pdynamisch);
																d->speichern(pschattenvolumen);
																d->speichern(pschattenvolumenlaenge);
																d->speichern(pflag);
																d->speichern(pbrechzahl);
																d->speichern(pdispersionsskalierung);
																d->speichern(pnurkollisionskopplung);
																d->speichern(pnichtspeichern);
																d->speichern(peditionort);
																d->speichern(peditionebene[0]);
																d->speichern(peditionebene[1]);
																
																speichernmaterial(d);

																_polygon*pit;
																d->speichern(_listebasis<_polygon>::anzahl());
																iterieren(pit,pit->speichern(d));

																d->speichern(anzahlvertex());
																_vertex*vit;
																iterieren(vit,vit->speichern(d));
																
																/*markierungvertex(1);
																_vertex*vit;
																_listenknoten<_vertex>*lnvit;
																iterieren(pit,
																 iterierenliste(pit,lnvit,
																  vit=lnvit->objekt();
																  if(vit->markierung()==1){
																   vit->markierung(0);
																   vit->speichern(d);
																   //L->l("Vertex wurde gespeichert");
																  };
																 );
																);*/
																

																_listenknoten<_partition::_sektor>*lnsit;
																d->speichern(_liste<_partition::_sektor>::anzahl());
																iterieren(lnsit,speichernzeiger(d,lnsit->objekt()));
};
bool _netz::assoziieren(){
																if(zeigergeladen()){
																 unsigned int a=ladenanzahl();
																 unsigned int i;
																 for(i=0;i<a;i++) {
															      _partition::_sektor*sit;
																  assoziierenzeiger(sit);
																  new _verbinder< _netz,_partition::_sektor>(sit->internenetze(),this,this,sit);
																 };
																 loeschenzeiger();
																};
																return(true);
};