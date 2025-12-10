//******************************************************************************************************************************************************************************************************
//  Projekt      : grundplatte
//  Bibliothek   : _grundplatte.lib
//  Modul        : _weltoptik.cpp
//  Datum        : 09.01.2006
//  Beschreibung : 
//******************************************************************************************************************************************************************************************************
#include <_weltoptik.hpp>
#include <_weltpolygon.hpp>
//******************************************************************************************************************************************************************************************************
//                                                              B E S T R A H L E R 
//******************************************************************************************************************************************************************************************************

_bestrahler::_bestrahler(){
                                                                welt=0;
                                                                animcamera=0;
                                                                animmap=0;
                                                                animx=0;
                                                                animy=0;
                                                                animdx=0;
                                                                animdy=0;
                                                                animmapx=0;
                                                                animmapy=0;
                                                                pfarbeambient.setzen(0.02f,0.02f,0.02f);
                                                                farbeundef.setzen(0.1234f,0.2345f,0.3456f);
                                                              //  farbeundef.setzen(1,1,1);
                                                                preflektionstiefe=0;
                                                                prefraktionstiefe=0;
                                                                prefraktiondispersiv=false;
                                                                pdispersionsaufloesung=3;
                                                                pvis=false;
                                                                pvisbild=false;
                                                                pvishalt=false;
                                                                pviszahl=0;
                                                                pvisrate=2;
};

_bestrahler::~_bestrahler(){
                                                                beenden();
                                                                pspektrallinien.loeschen();
                                                                
};

void _bestrahler::visualisierung(bool b){
                                                                pvis=b;                                    
};

void _bestrahler::visualisierungbild(bool b){
                                                                pvisbild=b;
};

void _bestrahler::visualisierungumschalten(){
                                                                if(pvisbild) pvisbild=false; else pvisbild=true;
};

void _bestrahler::visualisierunganhalten(bool b){
                                                                pvishalt=b;
};                                                                

bool _bestrahler::visualisierunganhalten(){
                                                                return(pvishalt);
};                                                                

void _bestrahler::lichtambient(_vektor3<_to> col){
                                                                col.begrenzen(0,1);
                                                                pfarbeambient=col;
};

unsigned int _bestrahler::reflektionstiefe() const{
                                                                return(preflektionstiefe);
};

unsigned int _bestrahler::refraktionstiefe() const{
                                                                return(prefraktionstiefe);
};

void _bestrahler::reflektionstiefe(const unsigned int t){
                                                                preflektionstiefe=t;
};

void _bestrahler::refraktionstiefe(const unsigned int t){
                                                                prefraktionstiefe=t;
};

void _bestrahler::refraktiondispersiv(const bool b){
                                                                prefraktiondispersiv=b; 
};

void _bestrahler::dispersionsaufloesung(const unsigned int i){
                                                                if(i<3) pdispersionsaufloesung=3; else pdispersionsaufloesung=i;
};

void _bestrahler::vorbereiten(){
                                                                if(welt){
                                                                 welt->erzeugentexturraum();
                                                                 welt->erzeugenkante();
                                                                };
                                                                berechnenspektrallinien();
};                                                                

void _bestrahler::nachbereiten(){
                                                                if(welt){
                                                                 welt->loeschenkante();
                                                                 welt->loeschentexturraum();
                                                                };
                                                                pspektrallinien.loeschen();
};

void _bestrahler::berechnenspektrallinien(){
                                                                unsigned int z;
                                                                unsigned int i;
                                                                unsigned int n;
                                                                _vektor3<_to> rgb;
                                                                _tg dl,dr;
                                                                _tg wl,wr;
                                                                _spektrallinie*lit;
                                                                _vektor3<_to> summe;
                                                                //-------------------
                                                                pspektrallinien.loeschen();
                                                                n=pdispersionsaufloesung;
                                                                if(n==3){
                                                                 //feste linienverteilung bei dispersionsaufloesung=3
                                                                 rgb.setzen(1,0,0);
                                                                 new _spektrallinie(&pspektrallinien,650,rgb);
                                                                 rgb.setzen(0,1,0);
                                                                 new _spektrallinie(&pspektrallinien,550,rgb);
                                                                 rgb.setzen(0,0,1);
                                                                 new _spektrallinie(&pspektrallinien,450,rgb);
                                                                }else{
                                                                 //anzahlen holen
                                                                 if((n%2)==1){
                                                                  z=(n-1)/2; 
                                                                  spektralkonversion(550,rgb);
                                                                  new _spektrallinie(&pspektrallinien,550,rgb);
                                                                 }else{
                                                                  z=n/2;
                                                                 };
                                                                 //linien verteilen
                                                                 dl=_tg(550-350)/_tg(z);
                                                                 dr=_tg(750-550)/_tg(z);
                                                                 wl=550-(dl/2);//nach UV
                                                                 wr=550+(dr/2);//nach IR
                                                                 for(i=0;i<z;i++){
                                                                  spektralkonversion(wl,rgb);
                                                                  new _spektrallinie(&pspektrallinien,wl,rgb);
                                                                  spektralkonversion(wr,rgb);
                                                                  new _spektrallinie(&pspektrallinien,wr,rgb);
                                                                  wl-=dl;
                                                                  wr+=dr;
                                                                 };
                                                                };

                                                                //normalisierung vornehmen
                                                                //die summe aller werte eines kanals muss 1 ergeben
                                                                summe.setzen(0,0,0);
                                                                if(pspektrallinien.anfang(lit))do{
                                                                 summe+=lit->rgbwert;
                                                                }while(pspektrallinien.naechstes(lit));
                                                                summe.setzen(1.0f/summe[0],1.0f/summe[1],1.0f/summe[2]);
                                                                if(pspektrallinien.anfang(lit))do{
                                                                 lit->rgbwert.produkt(summe);
                                                                }while(pspektrallinien.naechstes(lit));
                                                                //****** DEBUG **********
                                                                summe.setzen(0,0,0);
                                                                if(pspektrallinien.anfang(lit))do{
                                                                 summe+=lit->rgbwert;
                                                                }while(pspektrallinien.naechstes(lit));
                                                                L->schreiben("Optik : Dispersionssumme = ",summe);
                                                                L->schreiben("Optik : Anzahl der Dispersiven Strahlen : ",(int)pspektrallinien.anzahl());
                                                                //***********************
                                                               
                                                                
};                                                                


void _bestrahler::bestrahlenlightmap(_welt*w,_polygon*p){
                                                                _bild<_tb>*lmap;
                                                                _listenknoten<_bild<_tb> >*lnlmap;
                                                                unsigned int ix,iy;
                                                                _tg tx,ty,dtx,dty;
                                                                _licht<_tg,_to>*lit;
                                                                _strahl*strahl;
                                                                _tg wx,wy;
                                                                //--------------
                                                                welt=w;
                                                                if(p->texturdynamisch()){
                                                                if(p->texturdynamisch()->lightmap()->anfang(lnlmap)){
                                                                 lmap=lnlmap->objekt();
                                                                 vorbereiten();
                                                                 wx=lmap->groesse(0);
                                                                 wy=lmap->groesse(1);
                                                                   
                                                                  //if(p->textur()->lightmap()->anfang(lmap)){
                                                                  //}else{
                                                                  // lmap=new _bildtga<_to>(pname,wx,wy);
                                                                  // lmap->groesse(wx,wy);
                                                                  // p->textur()->einfuegenlightmap(lmap);
                                                                  //};
                                                                  dty=1.0f/wy;
                                                                  dtx=1.0f/wx;
                                                                  ty=dty*0.5f;
                                                                  for(iy=0;iy<(unsigned int)(wy);iy++){
                                                                   tx=dtx*0.5f;;
                                                                   for(ix=0;ix<(unsigned int)(wx);ix++){
                                                                    
                                                                    //_vektor<_to> vo;
                                                                    _vektor3<_to> e;
                                                                    _vektor3<_to> ep;
                                                                    _vektor3<_tg> o;
                                                                    _vektor3<_tg> v;
                                                                    _vektor<_tb> ed;
                                                                    
                                                                    p->texturespace()->konvertierentexturwelt(1,0,tx,ty,o);
                                                                     e.setzen(0,0,0);
                                                                    if(w->anfang(lit))do{
                                                                     v=lit->ort()-o;
                                                                     strahl=erzeugenstrahlbaum(o,v,0,0,1,p); 
                                                                     ep.setzen(0,0,0);
                                                                     berechnenfarbe(strahl,lit,ep);
                                                                     ep*=(_to)berechnenlichtintensitaet(o,p->normale(),lit);
                                                                     e+=ep;
                                                                     // ***** DEBUG *******
                                                                     //_strahlschnitt*ss;
                                                                     //e=lit->farbe();
                                                                     //if(strahl->anfang(ss)){
                                                                    
                                                                       // ************** DEBUG **************
                                                                       //_vektor<_to> col;
                                                                       //col.setzen(0,0,0);
                                                                       //ss->farbetextur(col);
                                                                       //new _weltdebugkreuz(welt,ss->ort,0.01,col);
                                                                      // ***********************************
  
                                                                      //ss->farbetextur(e);
                                                                     //};
                                                                     // *******************
                                                                    
                                                                    
                                                                     delete strahl;
                                                                     // ********** DEBUG *********
                                                                     //vo.setzen(0,1,0);
                                                                     //new _weltdebuglinie( w,o,o+v,vo);
                                                                     // ***************************
                                                                    }while(w->naechstes(lit));
                                                                    e+=pfarbeambient;
                                                                    ed.setzen(_tb(e[0]*255),_tb(e[1]*255),_tb(e[2]*255));//3D!
                                                                    lmap->schreiben(ix,iy,ed);
                                                                    // ********** DEBUG *********
                                                                    //vo.setzen(0,1,0);
                                                                    //new _weltdebugkreuz(w,o,0.08,vo);
                                                                    // **************************
                                                                    tx+=dtx;
                                                                   };
                                                                   ty+=dty;
                                                                  };
                                                                  nachbereiten();
                                                                  lmap->speichern();
                                                                 };
                                                                };
                                                                
                                                                
};   

void _bestrahler::bestrahlenlightmapzone(_welt*w){
                                                                _partition::_zone*zit;
                                                                _polygon*p;
                                                                _partition::_sektor*sit;
                                                                _partition::_polygon*ppit;
                                                                _bild<_tb>*lmap;
                                                                _licht<_tg,_to>*lit;
                                                                _liste<_licht<_tg,_to> > lichtliste;
                                                                _liste<_partition::_sektor > sektorliste;
                                                                _liste<_polygon > polygonliste;
                                                                _listenknoten<_polygon >*lnpit;
                                                                _listenknoten<_polygon >*lnpii;
                                                                _listenknoten<_partition::_sektor>*lnsit;
                                                                _listenknoten<_partition::_sektor>*lnsii;
                                                                _listenknoten<_partition::_sektor>*lnsss;
                                                                //unsigned int ix,iy;
                                                                //_tg tx,ty;
                                                                //_tg wx,wy;
                                                                _liste<_bild<_tb> > mapliste;
                                                                _listenknoten<_bild<_tb> >*lnmap;
                                                                _vektor3<_to> farbe;
                                                                _vektor<_to> farbed;
                                                                _vektor<_tb> ed;
                                                                _vektor3<_to> ambient=pfarbeambient;

                                                                //-----------------------------
                                                                welt=w;
                                                                vorbereiten();
                                                                //zunächst alle lighmap in eine liste holen
                                                                if(welt->anfang(zit))do{
                                                                 //alle zonen poly prüfen
                                                                 if(zit->anfang(lnpit))do{
                                                                  p=lnpit->objekt();
                                                                  if(p->texturdynamisch()){
                                                                   _listenknoten<_bild<_tb> >*lnlmap;
                                                                   if(p->texturdynamisch()->lightmap()->anfang(lnlmap)){ 
                                                                    lmap=lnlmap->objekt();
                                                                    mapliste.einhaengenunredundant(lmap);
                                                                   };
                                                                  };
                                                                 }while(zit->naechstes(lnpit));
                                                                 //alle internen sektorpoly prüfen
                                                                 if(zit->anfang(sit))do{
                                                                  if(sit->internepolygonestatisch()->anfang(lnpit))do{
                                                                   p=lnpit->objekt();
                                                                   if(p->texturdynamisch()){
                                                                    _listenknoten<_bild<_tb> >*lnlmap;
                                                                    if(p->texturdynamisch()->lightmap()->anfang(lnlmap)){ 
                                                                     lmap=lnlmap->objekt();
                                                                     mapliste.einhaengenunredundant(lmap);
                                                                    };
                                                                   };
                                                                  }while(sit->internepolygonestatisch()->naechstes(lnpit));
                                                                 }while(zit->naechstes(sit));
                                                                }while(welt->naechstes(zit));
                                                                
                                                                //alle lightmap mit undef-fabre füllen
                                                                if(mapliste.anfang(lnmap))do{
                                                                 ed.setzen(_tb(farbeundef[0]*255),_tb(farbeundef[1]*255),_tb(farbeundef[2]*255));//3D!
                                                                 lnmap->objekt()->schreiben(ed);
                                                                }while(mapliste.naechstes(lnmap));
                                                                
                                                                
                                                                
                                                                
                                                                
                                                                
                                                                //beginn der bestrahlung
                                                                if(welt->anfang(zit))do{
                                                                 //-----------------------------------------------------------------------------bestrahlung der zonenpolygone
                                                                 if(zit->anfang(lnpit))do{
                                                                  p=lnpit->objekt();
                                                                  if(p->texturdynamisch()){
                                                                    
                                                                   _listenknoten<_bild<_tb> > *lnlmap;
                                                                   if(p->texturdynamisch()->lightmap()->anfang(lnlmap)){                                                               
                                                                    lmap=lnlmap->objekt();                                                                   
                                                                    //L->schreiben("Optik : Zonenbestrahlung : polygon = ",(int)int(p));
                                                                    //1. eine unredundante liste aus sektoren betimmen, die auf das polygon
                                                                    //p zeigen und nicht portal sind (sektorliste)
                                                                    _partition::_sektor*besitzer=0;
                                                                    bool ambientgefunden=false;
                                                                    _licht<_tg,_to>*llit;
                                                                    sektorliste.aushaengen();
                                                                    if(zit->anfang(sit))do{//-----------------------
                                                                     bool dabei=false;
                                                                     if(sit->anfang(ppit))do{
                                                                      if(ppit->portal()==false){
                                                                       if(ppit->polygon()==p){
                                                                        sektorliste.einhaengenunredundant(sit);
                                                                        dabei=true;
                                                                        besitzer=sit;
                                                                       };
                                                                      };
                                                                     }while(sit->naechstes(ppit));
                                                                     if(dabei){
                                                                      if(ambientgefunden==false){
                                                                       if(sit->anfang(llit))do{
                                                                        ambient=llit->farbeambientstatisch();
                                                                        ambientgefunden=true;
                                                                       }while(sit->naechstes(llit));
                                                                      };
                                                                     };
                                                                     if(dabei){//sit assoziiert das zonenpoly p
                                                                      if(sit->sichtbarkeitsektor()->anfang(lnsss))do{
                                                                       sektorliste.einhaengenunredundant(lnsss->objekt());
                                                                      }while(sit->sichtbarkeitsektor()->naechstes(lnsss));
                                                                     };
                                                                    }while(zit->naechstes(sit));//---------------------
                                                                    if((ambientgefunden==false)&&(besitzer!=0)){
                                                                     //dann innerhalb der sichtbarkeit 1.grades suchen
                                                                     if(besitzer->sichtbarkeitsektor()->anfang(lnsss))do{
                                                                      if(lnsss->objekt()->anfang(llit))do{
                                                                       ambient=llit->farbeambientstatisch();
                                                                       ambientgefunden=true;
                                                                      }while(lnsss->objekt()->naechstes(llit));
                                                                     }while(besitzer->sichtbarkeitsektor()->naechstes(lnsss));
                                                                     if(ambientgefunden==false){
                                                                      //dann innerhalb der sichtbarkeit 2.grades suchen
                                                                      if(besitzer->sichtbarkeitsektor2tergrad()->anfang(lnsss))do{
                                                                       if(lnsss->objekt()->anfang(llit))do{
                                                                        ambient=llit->farbeambientstatisch();
                                                                       }while(lnsss->objekt()->naechstes(llit));
                                                                      }while(besitzer->sichtbarkeitsektor2tergrad()->naechstes(lnsss));
                                                                     };
                                                                    };
                                                                    //2. eine nicht redundante liste aller impliziten und expliziten und addierten
                                                                    //polygone aus den sichtbarkeiten der oben ermittelten
                                                                    //sektorenliste erstllen (polygonliste)
                                                                    polygonliste.aushaengen();
                                                                    if(sektorliste.anfang(lnsit))do{
                                                                     sit=lnsit->objekt();
                                                                     if(sit->anfang(ppit))do{
                                                                      if(ppit->portal()==false){
                                                                       if(ppit->polygon()!=p){
                                                                        polygonliste.einhaengenunredundant(ppit->polygon());
                                                                       };
                                                                      };
                                                                     }while(sit->naechstes(ppit));
                                                                     if(sit->sichtbarkeitextern()->anfang(lnpii))do{
                                                                      if(lnpii->objekt()!=p){
                                                                       polygonliste.einhaengenunredundant(lnpii->objekt());
                                                                      };
                                                                     }while(sit->sichtbarkeitextern()->naechstes(lnpii));
                                                                     if(sit->internepolygonestatisch()->anfang(lnpii))do{
                                                                      if(lnpii->objekt()!=p){
                                                                       polygonliste.einhaengenunredundant(lnpii->objekt());
                                                                      };
                                                                     }while(sit->internepolygonestatisch()->naechstes(lnpii));
                                                                    }while(sektorliste.naechstes(lnsit));
                                                                    //3. aus der sektorliste mit Hilfe der sektorensichtbarkeit eine
                                                                    //liste aus lichtquellen anlegen (lichtliste)
                                                                    lichtliste.aushaengen();
                                                                    if(sektorliste.anfang(lnsit))do{
                                                                     sit=lnsit->objekt();
                                                                     if(sit->anfang(lit))do{
                                                                      lichtliste.einhaengenunredundant(lit);
                                                                     }while(sit->naechstes(lit));
                                                                     if(sit->sichtbarkeitsektor()->anfang(lnsii))do{
                                                                      if(lnsii->objekt()->anfang(lit))do{
                                                                       lichtliste.einhaengenunredundant(lit);
                                                                      }while(lnsii->objekt()->naechstes(lit));
                                                                     }while(sit->sichtbarkeitsektor()->naechstes(lnsii));
                                                                    }while(sektorliste.naechstes(lnsit));
                                                                    bestrahlenlightmappolygon(p,lmap,&polygonliste,&lichtliste,ambient);
                                                                   };
                                                                  };
                                                                 }while(zit->naechstes(lnpit));
                                                                 //----------------------------bestrahlung der sektorinternen,statischen polygone
                                                                 //erstmal eine zonen interne polygone liste addierter poly erstellen
                                                                 _liste<_polygon> zonenpolygonaddiertliste;
                                                                 zonenpolygonaddiertliste.aushaengen();
                                                                 if(zit->anfang(sit))do{
                                                                  if(sit->internepolygonestatisch()->anfang(lnpit))do{
                                                                   zonenpolygonaddiertliste.einhaengenunredundant(lnpit->objekt());
                                                                  }while(sit->internepolygonestatisch()->naechstes(lnpit));
                                                                 }while(zit->naechstes(sit));
                                                                 //diese polygone zur bestrahlung abiterieren
                                                                 if(zonenpolygonaddiertliste.anfang(lnpit))do{
                                                                  p=lnpit->objekt();
                                                                  if(p->texturdynamisch()){
                                                                   _listenknoten<_bild<_tb> >*lnlmap;
                                                                   if(p->texturdynamisch()->lightmap()->anfang(lnlmap)){                                                               
                                                                   lmap=lnlmap->objekt();
                                                                    //0. ambientes licht holen
                                                                    bool ambientgefunden=false;
                                                                    _licht<_tg,_to>*llit;
                                                                    _partition::_sektor*besitzer=0;
                                                                    if(p->anfang(lnsit))do{
                                                                     if(besitzer==0) besitzer=lnsit->objekt();
                                                                     if(lnsit->objekt()->anfang(llit))do{
                                                                      ambient=llit->farbeambientstatisch();
                                                                      ambientgefunden=true;
                                                                     }while(lnsit->objekt()->naechstes(llit));
                                                                    }while(p->naechstes(lnsit));
                                                                    if((ambientgefunden==false)&&(besitzer!=0)){
                                                                     //dann innerhalb der sichtbarkeit 1.grades suchen
                                                                     if(besitzer->sichtbarkeitsektor()->anfang(lnsss))do{
                                                                      if(lnsss->objekt()->anfang(llit))do{
                                                                       ambient=llit->farbeambientstatisch();
                                                                       ambientgefunden=true;
                                                                      }while(lnsss->objekt()->naechstes(llit));
                                                                     }while(besitzer->sichtbarkeitsektor()->naechstes(lnsss));
                                                                     if(ambientgefunden==false){
                                                                      //dann innerhalb der sichtbarkeit 2.grades suchen
                                                                      if(besitzer->sichtbarkeitsektor2tergrad()->anfang(lnsss))do{
                                                                       if(lnsss->objekt()->anfang(llit))do{
                                                                        ambient=llit->farbeambientstatisch();
                                                                       }while(lnsss->objekt()->naechstes(llit));
                                                                      }while(besitzer->sichtbarkeitsektor2tergrad()->naechstes(lnsss));
                                                                     };
                                                                    };
                                                                    //1. eine liste aus sektoren erstellen, die auf dieses polygon p zeigen
                                                                    sektorliste.aushaengen();
                                                                    if(zit->anfang(sit))do{
                                                                     if(sit->internepolygonestatisch()->anfang(lnpii))do{
                                                                      if(lnpii->objekt()==p) {
                                                                       sektorliste.einhaengenunredundant(sit);
                                                                       _listenknoten<_partition::_sektor>*lnsss;
                                                                       if(sit->sichtbarkeitsektor()->anfang(lnsss))do{
                                                                        sektorliste.einhaengenunredundant(lnsss->objekt());
                                                                       }while(sit->sichtbarkeitsektor()->naechstes(lnsss));
                                                                      };
                                                                     }while(sit->internepolygonestatisch()->naechstes(lnpii));
                                                                    }while(zit->naechstes(sit));
                                                                    //2. nicht redundante polygone liste erstellen aus der oben
                                                                    //ermittelten sektorliste
                                                                    polygonliste.aushaengen();
                                                                    if(sektorliste.anfang(lnsit))do{
                                                                     sit=lnsit->objekt();
                                                                     if(sit->anfang(ppit))do{
                                                                      if(ppit->portal()==false){
                                                                       if(ppit->polygon()!=p){
                                                                        polygonliste.einhaengenunredundant(ppit->polygon());
                                                                       };
                                                                      };
                                                                     }while(sit->naechstes(ppit));
                                                                     if(sit->sichtbarkeitextern()->anfang(lnpii))do{
                                                                      if(lnpii->objekt()!=p)polygonliste.einhaengenunredundant(lnpii->objekt());
                                                                     }while(sit->sichtbarkeitextern()->naechstes(lnpii));
                                                                     if(sit->internepolygonestatisch()->anfang(lnpii))do{
                                                                      if(lnpii->objekt()!=p) polygonliste.einhaengenunredundant(lnpii->objekt());
                                                                     }while(sit->internepolygonestatisch()->naechstes(lnpii));
                                                                    }while(sektorliste.naechstes(lnsit));
                                                                    //3. lichtliste erstellen
                                                                    lichtliste.aushaengen();
                                                                    if(sektorliste.anfang(lnsit))do{
                                                                     sit=lnsit->objekt();
                                                                     if(sit->anfang(lit))do{
                                                                      lichtliste.einhaengenunredundant(lit);
                                                                     }while(sit->naechstes(lit));
                                                                     if(sit->sichtbarkeitsektor()->anfang(lnsii))do{
                                                                      if(lnsii->objekt()->anfang(lit))do{
                                                                       lichtliste.einhaengenunredundant(lit);
                                                                      }while(lnsii->objekt()->naechstes(lit));
                                                                     }while(sit->sichtbarkeitsektor()->naechstes(lnsii));
                                                                    }while(sektorliste.naechstes(lnsit));
                                                                    bestrahlenlightmappolygon(p,lmap,&polygonliste,&lichtliste,ambient);
                                                                   };
                                                                  };
                                                                 }while(zonenpolygonaddiertliste.naechstes(lnpit));
                                                                }while(welt->naechstes(zit));
                                                                
                                                                if(mapliste.anfang(lnmap))do{
                                                                 L->schreiben("Optik : Zonenbestrahlung, Bildnachbearbeitung");
                                                                 nachbearbeitenlightmap(lnmap->objekt());
                                                                 lnmap->objekt()->speichern();
                                                                }while(mapliste.naechstes(lnmap));
                                                                nachbereiten();
};   

void _bestrahler::bestrahlenlightmappolygon(_partition::_zone*zone,_netz*n){
                                                                _bild<_tb>*lmap;
                                                                _liste<_licht<_tg,_to> > lichtliste;
                                                                _liste<_polygon> polyliste;
                                                                _partition::_sektor*sit;
                                                                _licht<_tg,_to>*lit;
                                                                _polygon*p;
                                                                //---------------------------------------
                                                                vorbereiten();
                                                                if(n->anfang(p))do{
                                                                 if(p->texturdynamisch()){
                                                                 _listenknoten<_bild<_tb> >*lnlmap;
                                                                  if(p->texturdynamisch()->lightmap()->anfang(lnlmap)){ 
                                                                   lmap=lnlmap->objekt();
                                                                   if(zone->anfang(sit))do{
                                                                    if(sit->anfang(lit))do{
                                                                     lichtliste.einhaengen(lit);
                                                                    }while(sit->naechstes(lit));
                                                                   // if(sit->internepolygonestatisch()->anfang(lnpit))do{
                                                                   //  polyliste.einhaengen(lnpit->objekt());
                                                                   // }while(sit->internepolygonestatisch()->naechstes(lnpit));
                                                                   }while(zone->naechstes(sit));
                                                                   
                                                                   bestrahlenlightmappolygon(p,lmap,sit->internepolygonestatisch(),&lichtliste,pfarbeambient);
                                                                   nachbearbeitenlightmap(lmap);
                                                                   
                                                                  };
                                                                 };
                                                                }while(n->naechstes(p));
                                                                nachbereiten();
};
void _bestrahler::bestrahlenlightmappolygon(_polygon*p,_bild<_tb>*lmap,_liste<_polygon>*polygonliste,_liste<_licht<_tg,_to> >*lichtliste,const _vektor3<_to>&ambient){
                                                                _listenknoten<_polygon >*lnpii;
                                                                _listenknoten<_licht<_tg,_to> >*lnlit;
                                                                unsigned int ix,iy;
                                                                _tg tx,ty,dtx,dty;
                                                                _tg wx,wy;
                                                                _vektor<_tb> ed;
                                                                _strahl*strahl;
                                                                _licht<_tg,_to>*lit;
                                                                
                                                                //4. bestrahlung des polygons p durchführen mit der lichtliste und der polygonliste
                                                                //p ist bei der schnittbestimmung das exklusive polygon 
                                                                wx=lmap->groesse(0);
                                                                wy=lmap->groesse(1);
                                                                dty=1.0f/wy;
                                                                dtx=1.0f/wx;
                                                                ty=dty*0.5f;
                                                                for(iy=0;iy<(unsigned int)(wy);iy++){
                                                                 tx=dtx*0.5f;
                                                                 for(ix=0;ix<(unsigned int)(wx);ix++){
                                                                  if(p->texturespace()->innerhalb(1,0,tx,ty)){
                                                                  _vektor3<_to> vo;
                                                                  _vektor3<_to> e;
                                                                  _vektor3<_to> ep;
                                                                  _vektor3<_tg> o;
                                                                  _vektor3<_tg> v;
                                                                  p->texturespace()->konvertierentexturwelt(1,0,tx,ty,o);
                                                                  e.setzen(0,0,0);
                                                                  if(lichtliste->anfang(lnlit))do{
                                                                   lit=lnlit->objekt();
                                                                   v=lit->ort()-o;
                                                                   _tg alpha;
                                                                   _tg beta;
                                                                   _tg gamma;
                                                                   _polygon*pit;
                                                                   strahl=new _strahl(this,welt,o,v);
                                                                   if(polygonliste->anfang(lnpii))do{
                                                                    pit=lnpii->objekt();
                                                                    if(pit->lightmapschattierung()==true){
                                                                     if(pit!=p){
                                                                      if(((pit->normale()*v)<nahenull)||(pit->zweiseitig())){
                                                                       if(pit->schnittpunkt(o,v,nahenull,0,1,alpha,beta,gamma)){
                                                                        new _strahlschnitt(strahl,strahl->ort+strahl->vektor*gamma,pit,0,0,0,alpha,beta,gamma);
                                                                       };
                                                                      };
                                                                     };
                                                                    };
                                                                   }while(polygonliste->naechstes(lnpii)); 
                                                                   ep.setzen(0,0,0);
                                                                   berechnenfarbe(strahl,lit,ep);
                                                                   //ep=lit->farbe();
                                                                   ep*=(_to)berechnenlichtintensitaet(o,p->normale(),lit);
                                                                   e+=ep;
                                                                   delete strahl;
                                                                  }while(lichtliste->naechstes(lnlit));
                                                                  e+=ambient;
                                                                  e.begrenzen(0,1);
                                                                  ed.setzen(_tb(e[0]*255),_tb(e[1]*255),_tb(e[2]*255));
                                                                  lmap->schreiben(ix,iy,ed);
                                                                 };
                                                                 // ********** DEBUG *********
                                                                 //new _weltdebugkreuz(w,o,0.08,_vektor4<_to>(0,1,0,0));
                                                                 // **************************
                                                                 tx+=dtx;
                                                                };
                                                                ty+=dty;
                                                               };
                                                               lmap->speichern();
};
void _bestrahler::nachbearbeitenlightmap(_bild<_tb>*bild){
                                                              
                                                                //nun die lightmap nachbearbeiten (verbreitung in nicht berechnete
                                                                //bereiche hinein)
                                                                _liste<int> listx;
                                                                _liste<int> listy;
                                                                _liste<_vektor3<_to> > listfarbe;
                                                                _listenknoten<int>*itx;
                                                                _listenknoten<int>*ity;
                                                                _listenknoten<_vektor3<_to> >*itv;
                                                                _vektor3<_to> farbenachbar[9];
                                                                _vektor3<_to> fn[3][3];
                                                                _vektor3<_to> hh;
                                                                bool nachbardefiniert[9];
                                                                bool nd[3][3];
                                                                _to fk[3][3];
                                                                _to fm[3][3]={{0.025f,0.150f,0.025f},
                                                                              {0.150f,0.300f,0.150f},
                                                                              {0.025f,0.150f,0.025f}};
                                                                int i;
                                                                _tg anzahlnachbar;
                                                                unsigned int ix,iy;
                                                                _tg wx,wy;
                                                                _vektor3<_to> farbe;
                                                                _vektor<_tb> farbed;
                                                                _vektor<_tb> ed;                                                                
                                                                //--------------------------
                                                                listx.loeschen();
                                                                listy.loeschen();
                                                                listfarbe.loeschen();
                                                                // lmap=lnmap->objekt();
                                                                wx=bild->groesse(0);
                                                                wy=bild->groesse(1);
                                                                for(iy=0;iy<(unsigned int)(wy);iy++){//markieren zum verbreitern
                                                                 for(ix=0;ix<(unsigned int)(wx);ix++){
                                                                  bild->lesen(ix,iy,farbed);
                                                                  farbe.setzenkomponente(0,farbed[0]);
                                                                  farbe.setzenkomponente(1,farbed[1]);
                                                                  farbe.setzenkomponente(2,farbed[2]);
                                                                  farbe.mul(1.0f/255.0f);
                                                                  //if(farbe==farbeundef){
                                                                  if((farbe[0]==farbeundef[0])&&(farbe[1]==farbeundef[1])&&(farbe[2]==farbeundef[2])){
                                                                  //L->schreiben("undef texel gefunden");
                                                                   betrachtennachbar(ix-1,iy-1,bild,nachbardefiniert[0],farbenachbar[0]);
                                                                   betrachtennachbar(ix  ,iy-1,bild,nachbardefiniert[1],farbenachbar[1]);
                                                                   betrachtennachbar(ix+1,iy-1,bild,nachbardefiniert[2],farbenachbar[2]);
                                                                   betrachtennachbar(ix-1,iy  ,bild,nachbardefiniert[3],farbenachbar[3]);
                                                                   betrachtennachbar(ix+1,iy  ,bild,nachbardefiniert[4],farbenachbar[4]);
                                                                   betrachtennachbar(ix-1,iy+1,bild,nachbardefiniert[5],farbenachbar[5]);
                                                                   betrachtennachbar(ix  ,iy+1,bild,nachbardefiniert[6],farbenachbar[6]);
                                                                   betrachtennachbar(ix+1,iy+1,bild,nachbardefiniert[7],farbenachbar[7]);
                                                                   if(
                                                                   (nachbardefiniert[0])||
                                                                   (nachbardefiniert[1])||
                                                                   (nachbardefiniert[2])||
                                                                   (nachbardefiniert[3])||
                                                                   (nachbardefiniert[4])||
                                                                   (nachbardefiniert[5])||
                                                                   (nachbardefiniert[6])||
                                                                   (nachbardefiniert[7])
                                                                   ){
                                                                    int*iix=new int;
                                                                    *iix=ix;
                                                                    listx.einhaengen(iix);
                                                                    int*iiy=new int;
                                                                    *iiy=iy;
                                                                    listy.einhaengen(iiy);
                                                                    _vektor3<_to>*c=new _vektor3<_to>();
                                                                    c->setzen(0,0,0);
                                                                    anzahlnachbar=0;
                                                                    for(i=0;i<8;i++){
                                                                     if(nachbardefiniert[i]){
                                                                      anzahlnachbar+=1;
                                                                      *c+=farbenachbar[i];
                                                                     };
                                                                    };
                                                                    if(anzahlnachbar>0){
                                                                     c->mul(1.0f/_to(anzahlnachbar));
                                                                    };
                                                                    listfarbe.einhaengen(c);
                                                                   };
                                                                  };
                                                                 };
                                                                };
                                                                
                                                                //weichzeichnen
                                                                _bild<_tb>*hmap=new _bild<_tb>(bild);
                                                                for(iy=0;iy<(unsigned int)(wy);iy++){
                                                                 for(ix=0;ix<(unsigned int)(wx);ix++){
                                                                  int rx,ry;
                                                                  _to defcount=0;
                                                                  for(ry=0;ry<3;ry++)
                                                                  for(rx=0;rx<3;rx++){
                                                                   betrachtennachbar(rx+(ix-1),ry+(iy-1),hmap,nd[rx][ry],fn[rx][ry]);
                                                                   if(nd[rx][ry]==false) defcount+=1;
                                                                   fk[rx][ry]=fm[rx][ry];
                                                                  };
                                                                  if(defcount==0) {
                                                                   for(ry=0;ry<3;ry++)
                                                                   for(rx=0;rx<3;rx++){
                                                                    if(nd[rx][ry]==false){
                                                                     _to ff=fm[rx][ry]/defcount;
                                                                     fk[rx][ry]=0;
                                                                     //auf definierte verteilen
                                                                     int qx,qy;
                                                                     for(qy=0;qy<3;qy++)
                                                                     for(qx=0;qx<3;qx++){
                                                                      if(nd[qx][qy]) {
                                                                       fk[qx][qy]+=ff;
                                                                      };
                                                                     };
                                                                    };
                                                                   };
                                                                   hh.setzen(0,0,0);
                                                                   for(ry=0;ry<3;ry++)
                                                                   for(rx=0;rx<3;rx++){
                                                                    if(nd[rx][ry]){
                                                                     hh+=fn[rx][ry]*fk[rx][ry];
                                                                    };
                                                                   };
                                                                   ed.setzen(_tb(hh[0]*255),_tb(hh[1]*255),_tb(hh[2]*255));
                                                                   bild->schreiben(ix,iy,ed);
                                                                  };
                                                                 };
                                                                };
                                                                delete hmap;
                                                                
                                                                //kanten verbreitern : ausführen
                                                                if(listfarbe.anfang(itv)){
                                                                 listx.anfang(itx);
                                                                 listy.anfang(ity);
                                                                 do{
                                                                  bild->schreiben(*itx->objekt(),*ity->objekt(),_vektor<_tb>(_tb((*itv->objekt())[0]*255),_tb((*itv->objekt())[1]*255),_tb((*itv->objekt())[2]*255)));
                                                                  listx.naechstes(itx);
                                                                  listy.naechstes(ity);
                                                                 }while(listfarbe.naechstes(itv));
                                                                };
                                                                
                                                               
                                                               
                                                               listx.loeschen();
                                                               listy.loeschen();
                                                               listfarbe.loeschen();
};
void _bestrahler::betrachtennachbar(int x,int y,_bild<_tb>*bild,bool&r,_vektor3<_to>&f){
                                                                r=true;
                                                                if(x<0) {r=false;};
                                                                if(y<0) {r=false;};
                                                                if(x>=int(bild->groesse(0))) {r=false;};
                                                                if(y>=int(bild->groesse(1))) {r=false;};
                                                                _vektor<_tb> fd;
                                                                bild->lesen(x,y,fd);
                                                                f.setzenkomponente(0,fd[0]);
                                                                f.setzenkomponente(1,fd[1]);
                                                                f.setzenkomponente(2,fd[2]);
                                                                f.mul(1.0f/255.0f);
                                                                if(f==farbeundef) {r=false;};
};


void _bestrahler::starten(_welt*w,_kamera<_tg>*c,_bild<_tb>*m){
                                                                welt=w;
                                                                animcamera=c;
                                                                animmap=m;
                                                                vorbereiten();
                                                                animmap->tiefereskalieren(1);
                                                                animdy=2.0f/m->groesse(1);
                                                                animdx=2.0f/m->groesse(0);
                                                                animmapx=0;
                                                                animmapy=0;
                                                                animy=1;
                                                                animx=-1;
};   
                                                             

void _bestrahler::zeichnenzeile(_grafik*animgraphic){
                                                                _vektor3<_tg> p0;
                                                                _vektor3<_tg> p1;
                                                                _vektor3<_tg> p2;
                                                                _vektor3<_tg> p3;
                                                                _vektor4<_to> co;
                                                                _vektor<_tb> cod;
                                                                unsigned int mx;
                                                                unsigned int i;
                                                                _tg scx=1;
                                                                _tg scy=0.75;
                                                                _tg xx;
                                                                //--------------
                                                                animgraphic->aktivitaet(true);
                                                                animgraphic->transparenz(false);
                                                                animgraphic->textur(false);
                                                                animgraphic->tiefenbufferkondition(false);
                                                                animgraphic->tiefenbufferschreiben(false);
                                                                animgraphic->maske(false);
                                                                for(i=0;i<2;i++){
                                                                 xx=-1;
                                                                 for(mx=0;mx<animmap->groesse(0);mx++){
                                                                  animmap->lesen(mx,animmapy-1,cod);
                                                                  //co.konvertieren(4);
                                                                  
                                                                  co.setzenkomponente(0,cod[0]);
                                                                  co.setzenkomponente(1,cod[1]);
                                                                  co.setzenkomponente(2,cod[2]);
                                                                  co.mul(1.0f/255.0f);
                                                                  co.setzenkomponente(3,0.5);
                                                                  p0.setzen((xx+     0)*scx,-(animy+     0)*scy,1);
                                                                  p1.setzen((xx+animdx)*scx,-(animy+     0)*scy,1);
                                                                  p2.setzen((xx+animdx)*scx,-(animy-animdy)*scy,1);
                                                                  p3.setzen((xx+     0)*scx,-(animy-animdy)*scy,1);
                                                                  animgraphic->zeichnen(p0,p1,p2,co,co,co);
                                                                  animgraphic->zeichnen(p0,p2,p3,co,co,co);
                                                                  xx+=animdx;
                                                                 };
                                                                 animgraphic->anzeigebufferumschalten(false);
                                                                };
};                                                                

void _bestrahler::zeichnen(_grafik*animgraphic){
                                                                _vektor3<_tg> p0;
                                                                _vektor3<_tg> p1;
                                                                _vektor3<_tg> p2;
                                                                _vektor3<_tg> p3;
                                                                _vektor4<_to> co;
                                                                _vektor<_tb> cod;
                                                                unsigned int mx;
                                                                unsigned int my;
                                                                unsigned int i;
                                                                _tg scx=1;
                                                                _tg scy=0.75;
                                                                _tg xx,yy;
                                                                //--------------
                                                                animgraphic->aktivitaet(true);
                                                                animgraphic->transparenz(false);
                                                                animgraphic->textur(false);
                                                                animgraphic->tiefenbufferkondition(false);
                                                                animgraphic->tiefenbufferschreiben(false);
                                                                animgraphic->allebufferloeschen();
                                                                animgraphic->anzeigebufferumschalten();
                                                                animgraphic->allebufferloeschen();
                                                                animgraphic->anzeigebufferumschalten();
                                                                for(i=0;i<2;i++){
                                                                 yy=1;
                                                                 for(my=0;my<animmap->groesse(1);my++){
                                                                  xx=-1;
                                                                  for(mx=0;mx<animmap->groesse(0);mx++){
                                                                   animmap->lesen(mx,my,cod);
                                                                   co.setzenkomponente(0,cod[0]);
                                                                   co.setzenkomponente(1,cod[1]);
                                                                   co.setzenkomponente(2,cod[2]);
                                                                   co.mul(1.0f/255.0f);
                                                                   co.setzenkomponente(3,1);
                                                                   //co.konvertieren(4);
                                                                   //co.setcomponent(3,1);
                                                                   p0.setzen((xx+     0)*scx,-(yy+     0)*scy,1);
                                                                   p1.setzen((xx+animdx)*scx,-(yy+     0)*scy,1);
                                                                   p2.setzen((xx+animdx)*scx,-(yy-animdy)*scy,1);
                                                                   p3.setzen((xx+     0)*scx,-(yy-animdy)*scy,1);
                                                                   animgraphic->zeichnen(p0,p1,p2,co,co,co);
                                                                   animgraphic->zeichnen(p0,p2,p3,co,co,co);
                                                                   xx+=animdx;
                                                                  };
                                                                  yy-=animdy;
                                                                 };
                                                                 animgraphic->anzeigebufferumschalten();
                                                                };
};                                                                

bool _bestrahler::animieren(_system*sys,_tastatur*kb,_maus<_tg>*mo,_grafik*gravis,_kamera<_tg>*camvis){
                                                                bool raus;
                                                                //-----------------
                                                                if(animmap!=0){
                                                                 //bedingung prüfen
                                                                 if((animmapx>=0)&&(animmapy>=0)&&(animmapx<animmap->groesse(0))&&(animmapy<animmap->groesse(1))){
                                                                  //einen punkt des bildes bestrahlen
                                                                  _strahl*strahl;
                                                                  _vektor3<_to> ergebnis;
                                                                  strahl=erzeugenstrahlbaum(animcamera->ort(),animcamera->vektor()+animcamera->ebene(1)*-animy+animcamera->ebene(0)*-animx,preflektionstiefe,prefraktionstiefe);
                                                                  anpassenmonochromfilter(strahl);
                                                                  berechnenfarbe(strahl,ergebnis);
                                                                  _vektor<_tb> ed(_tb(ergebnis[0]*255),_tb(ergebnis[1]*255),_tb(ergebnis[2]*255));
                                                                  animmap->schreiben(animmapx,animmapy,ed);
                                                                  // *********** DEBUG ***********
                                                                  if(pvis){
                                                                   if(pvisbild){
                                                                    if(animmapx==(animmap->groesse(0)-1)) zeichnenzeile(gravis);
                                                                   }else{
                                                                    visualisieren(strahl);
                                                                    gravis->aktivitaet(true);
                                                                    if(pvishalt==false){
                                                                     if(pviszahl>=pvisrate){
                                                                      gravis->allebufferloeschen();
                                                                      camvis->bewegen(kb,mo,1);
                                                                      welt->transformieren(gravis,camvis,false);
                                                                      welt->zeichnen(gravis,camvis); 
                                                                      gravis->anzeigebufferumschalten();
                                                                      sys->animieren();
                                                                      pviszahl=0;
                                                                     }else pviszahl++;
                                                                    }else{
                                                                     raus=false;
                                                                     do{
                                                                      gravis->allebufferloeschen();
                                                                      camvis->bewegen(kb,mo,1);
                                                                      welt->transformieren(gravis,camvis,false);
                                                                      welt->zeichnen(gravis,camvis); 
                                                                      gravis->anzeigebufferumschalten();
                                                                      sys->animieren();
                                                                      if(kb->escape()) {raus=true;while(kb->escape()) sys->animieren();};
                                                                      if(kb->taste(65)) {raus=true;pvishalt=false;while(kb->taste(65)) sys->animieren();};
                                                                     }while(raus==false);
                                                                     
                                                                    };
                                                                    devisualisieren();
                                                                   };
                                                                  };
                                                                  // *****************************
                                                                  delete strahl;
                                                                  strahl=0;
                                                                  //iteratoren bearbeiten
                                                                  if(animmapx<(animmap->groesse(0)-1)){
                                                                   animx+=animdx;
                                                                   animmapx++;
                                                                  }else{
                                                                   animx=-1;
                                                                   animmapx=0;
                                                                   if(animmapy<(animmap->groesse(1)-1)){
                                                                    animy-=animdy;
                                                                    animmapy++;
                                                                   }else{
                                                                    beenden();
                                                                    return(false);
                                                                   };
                                                                  };
                                                                  return(true);
                                                                 }else{
                                                                  return(false);
                                                                 };
                                                                }else{
                                                                 return(false);
                                                                };
};                                                               

void _bestrahler::beenden(){
                                                                devisualisieren();
                                                                nachbereiten();
                                                                welt=0;
                                                                animcamera=0;
                                                                animmap=0;
};                                                               

unsigned int  _bestrahler::bilditeratorx()const{   
                                                                return(animmapx);
};

_strahl* _bestrahler::erzeugenstrahlbaum(_vektor3<_tg> ort,_vektor3<_tg> vektor,unsigned int lreflektionstiefe,unsigned int lrefraktionstiefe){ 
                                                                //hauptstrahlgerüsterzeugungsfunktion
                                                                //steuert die primär strahlkonstruktion und -schnittbestimmung
                                                                //steuert die reflektionsstrahlgerüstkonstruktion
                                                                //steuert die refraktionsstrahlgerüstkonstruktion
                                                                _tg alpha;
                                                                _tg beta;
                                                                _tg gamma;
                                                                _netz*mit; //netz-iterator
                                                                _polygon*pit;
                                                                _strahl*strahl;
                                                                //_vertex< _tg, _to, _ta>*v1;
                                                                //_vertex< _tg, _to, _ta>*v2;
                                                                //_vertex< _tg, _to, _ta>*v0;
                                                                _strahlschnitt*sit;
                                                                //bool opak;
                                                                //----------------------------------
                                                                strahl=new _strahl(this,welt,ort,vektor);
                                                                if(welt->anfang(mit))do{
                                                                 if(mit->anfang(pit))do{
                                                                  if(  ((pit->normale()*vektor)<nahenull) ||(pit->zweiseitig())  ){
                                                                   if(pit->schnittpunkt(ort,vektor,nahenull,true,alpha,beta,gamma)){
                                                                    new _strahlschnitt(strahl,strahl->ort+strahl->vektor*gamma,pit,0,0,0,alpha,beta,gamma);
                                                                   };
                                                                  };
                                                                 }while(mit->naechstes(pit));
                                                                }while(welt->naechstes(mit)); 
                                                                //---------- opazitäten aushaengen ------------------
                                                                strahl->loeschenschnittpunktverdeckt();
                                                                //---------- refraktion konstruieren ---------------
                                                                if(lrefraktionstiefe>0){
                                                                 strahl->loeschenschnittpunktaussererster();
                                                                 if(strahl->anfang(sit)){
                                                                  erzeugenstrahlbaumrefraktion(sit,lrefraktionstiefe-1);
                                                                 };
                                                                };
                                                                //---------- reflektion konstruieren ---------------
                                                                if(lreflektionstiefe>0){
                                                                 if(strahl->anfang(sit))do{
                                                                  erzeugenstrahlbaumreflektion(sit,sit->ort,sit->reflektionsvektor(),lreflektionstiefe-1);
                                                                 }while(strahl->naechstes(sit));
                                                                };
                                                                return(strahl);
};

void _bestrahler::anpassenmonochromfilter(_strahl*s){ 
                                                                _strahlschnitt*sit;
                                                                _strahl*rit;
                                                                _vektor3<_to> weiss;
                                                                //---------------------------------
                                                                weiss.setzen(1,1,1);
                                                                if(s->monochrom){
                                                                 if(s->anfang(sit))do{
                                                                  if(sit->anfang(rit))do{
                                                                   anpassenmonochromfilter(rit,weiss);
                                                                  }while(sit->naechstes(rit));
                                                                 }while(s->naechstes(sit));
                                                                }else{
                                                                 //weitersuchen
                                                                 if(s->anfang(sit))do{
                                                                  if(sit->anfang(rit))do{
                                                                   anpassenmonochromfilter(rit);
                                                                  }while(sit->naechstes(rit));
                                                                 }while(s->naechstes(sit));
                                                                };
                                                                
};

void _bestrahler::anpassenmonochromfilter(_strahl*s,_vektor3<_to> f){ 
                                                                _strahlschnitt*sit;
                                                                _strahl*rit;
                                                                //---------------------------------
                                                                s->filter=f;
                                                                if(s->anfang(sit))do{
                                                                 if(sit->anfang(rit))do{
                                                                  anpassenmonochromfilter(rit,f);
                                                                 }while(sit->naechstes(rit));
                                                                }while(s->naechstes(sit));
};

void _bestrahler::visualisieren(_system*sys,_tastatur*kb,_maus<_tg>*mo,_grafik*gra,_kamera<_tg>*cam){
                                                                bool raus;
                                                                //---------
                                                                devisualisieren();
                                                                if(animmap!=0){
                                                                 raus=false;
                                                                 //temporäres strahlbündel erzeugen
                                                                 _strahl*strahl;
                                                                 _vektor3<_to> ergebnis;
                                                                 strahl=erzeugenstrahlbaum(animcamera->ort(),animcamera->vektor()+animcamera->ebene(1)*-animy+animcamera->ebene(0)*-animx,preflektionstiefe,prefraktionstiefe);
                                                                 visualisieren(strahl);
                                                                 delete strahl;
                                                                 strahl=0;
                                                                 //darstellen
                                                                 gra->aktivitaet(true);
                                                                 do{
                                                                  gra->allebufferloeschen();
                                                                  cam->bewegen(kb,mo,1);
                                                                  welt->transformieren(gra,cam,false);
                                                                  welt->zeichnen(gra,cam); 
                                                                  gra->anzeigebufferumschalten();
                                                                  sys->animieren();
                                                                  if(kb->escape()) raus=true;
                                                                 }while(raus==false);
                                                                 devisualisieren();
                                                                 while(kb->escape()) sys->animieren();
                                                                 zeichnen(gra);                                                                        
                                                                };
};

void _bestrahler::visualisieren(_strahl*strahl){
                                                                _strahlschnitt*sit;
                                                                _strahl*rit;
                                                                _weltdebugpfeil*a;
                                                                _vektor3<_tg> v;
                                                                _vektor3<_tg> old;
                                                                _vektor4<_to> hc;
                                                                //--------------------------------
                                                                if(strahl->anfang(sit)){
                                                                 old=strahl->ort;
                                                                 do{
                                                                  hc.setzen(strahl->filterroh[0],strahl->filterroh[1],strahl->filterroh[2],0);
                                                                  a=new _weltdebugpfeil(welt,old,sit->ort,0.02,0.005,hc);
                                                                  pdbarrows.einhaengen(a);
                                                                  old=sit->ort;
                                                                  if(sit->anfang(rit))do{
                                                                   visualisieren(rit);
                                                                  }while(sit->naechstes(rit));
                                                                 }while(strahl->naechstes(sit));
                                                                }else{
                                                                 v=strahl->vektor;
                                                                 v.normalisieren();
                                                                 v*=1000;
                                                                 hc.setzen(strahl->filterroh[0],strahl->filterroh[1],strahl->filterroh[2],0);
                                                                 a=new _weltdebugpfeil(welt,strahl->ort,strahl->ort+v,0.2,0.01,hc);
                                                                 pdbarrows.einhaengen(a);
                                                                };
};

void _bestrahler::devisualisieren(){
                                                                pdbarrows.loeschen();
};


_strahl* _bestrahler::erzeugenstrahlbaumrefraktion(_strahlschnitt*ss,unsigned int tiefe){ 
                                                                //refraktionsrekursion
                                                                _tg n1;
                                                                _tg n2;
                                                                _tg w1;
                                                                _tg w2;
                                                                _tg wg;
                                                                //_tg d1;
                                                                //_tg d2;
                                                                //_tg d3;
                                                                _vektor3<_tg> l1;
                                                                _vektor3<_tg> lot;
                                                                //_vektor3<_tg> vb;
                                                                _vektor3<_tg> v;
                                                                _vektor3<_tg> h;
                                                                _vektor3<_tg> null;
                                                                _vektor3<_tg> rnormal;
                                                                _tg sc;
                                                                _tg alpha;
                                                                _tg beta;
                                                                _tg gamma;
                                                                _netz*mit; //netz-iterator
                                                                _polygon*pit;
                                                                _strahl*strahl;
                                                                //_strahl*strahlr;
                                                                //_strahl*strahlb;
                                                                _strahlschnitt*sit;
                                                                _liste<_strahl > neustrahlen;
                                                                _listenknoten<_strahl >*stt;
                                                                _tg wl;
                                                                _vektor3<_to> filter;
                                                                _vektor3<_to> filterroh;
                                                                _vektor<_tb> tex;
                                                                _to trans;
                                                                //---------------------------------------------
                                                                //wenn ss ein polygon beschreibt, das nicht transparent ist,
                                                                //so wird die funktion ohne weiteres beendet
                                                                null.setzen(0,0,0);
                                                                strahl=0;
                                                                trans=ss->transparenz(tex);
                                                                if(trans>0){
                                                                 
                                                                 
 
                                                                  //feststellend, ob ss einen eintretenden oder
                                                                  //einen austretenden strahl beschreibt, reflektionsnormale bestimmen
                                                                  h=ss->strahl->vektor;
                                                                  h.normalisieren();
                                                                  sc=h*ss->polygon->normale();
                                                                  if(sc<nahenull) rnormal=ss->normale; else rnormal=-ss->normale;
                                                                  //reflektion durchführen
                                                                  //reflektierten vektor berechnen                                                                        
                                                                  h=-ss->strahl->vektor;
                                                                  h.normalisieren();
                                                                  V3.lotpunktgerade(h,null,rnormal,lot);
                                                                  v=h+lot*2;
                                                                  strahl=new _strahl(this,welt,ss,ss->ort,v);
                                                                  strahl->monochrom=ss->strahl->monochrom;
                                                                  strahl->filter=ss->strahl->filter;
                                                                  strahl->filterroh=ss->strahl->filterroh;
                                                                  neustrahlen.einhaengen(strahl);
                                                                  if(welt->anfang(mit))do{
                                                                   if(mit->anfang(pit))do{
                                                                    if(  ((pit->normale()*strahl->vektor)<nahenull)||(pit->zweiseitig()) ) {
                                                                     if(pit->schnittpunkt(strahl->ort,strahl->vektor,nahenull,true,alpha,beta,gamma)){
                                                                      new _strahlschnitt(strahl,strahl->ort+strahl->vektor*gamma,pit,0,0,0,alpha,beta,gamma);
                                                                     };
                                                                    };
                                                                   }while(mit->naechstes(pit));
                                                                  }while(welt->naechstes(mit)); 
                                                                  //nur ersten übrig lassen
                                                                  strahl->loeschenschnittpunktaussererster();
                                                                  if(strahl->anfang(sit)){
                                                                   if(tiefe>0) {
                                                                    erzeugenstrahlbaumrefraktion(sit,tiefe-1);
                                                                   };
                                                                  };
                                                                  
                                                                  
                                                                  
                                                                  unsigned int bsa;
                                                                  unsigned int i;
                                                                  if(prefraktiondispersiv) {
                                                                   bsa=pdispersionsaufloesung; 
                                                                   if(ss->strahl->monochrom) bsa=1;//monochromer einfallsstrahl
                                                                  }else bsa=1;
                                                                  for(i=0;i<bsa;i++){
                                                                  
                                                                   if(ss->strahl->monochrom){
                                                                    wl=ss->strahl->wellenlaenge;
                                                                    filter=ss->strahl->filter;
                                                                    filterroh=ss->strahl->filterroh;
                                                                   }else{
                                                                    filter=pspektrallinien[i]->rgbwert;
                                                                    filterroh=pspektrallinien[i]->rgbwertroh;
                                                                    wl=pspektrallinien[i]->wellenlaenge;
                                                                   };
                                                                   //brechung durchführen
                                                                   //zunächst brechzahlen holen                                                                 
                                                                   if(prefraktiondispersiv==false){
                                                                    if(sc<nahenull){//eintretend
                                                                     n1=welt->brechzahl();
                                                                     n2=ss->polygon->netz()->brechzahl();
                                                                    }else{//austretend
                                                                     n1=ss->polygon->netz()->brechzahl();
                                                                     n2=welt->brechzahl();
                                                                    };
                                                                   }else{
                                                                    if(sc<nahenull){//eintretend
                                                                     n1=welt->brechzahldispersiv(wl);
                                                                     n2=ss->polygon->netz()->brechzahldispersiv(wl);
                                                                    }else{//austretend
                                                                     n1=ss->polygon->netz()->brechzahldispersiv(wl);
                                                                     n2=welt->brechzahldispersiv(wl);
                                                                    };
                                                                   };
                                                                   //winkelbestimmen, wg=grenzwinkel der totalreflektion
                                                                   wg=((asin(n2/n1)*180)/_pi)-0;
                                                                   w1=rnormal.winkel(-ss->strahl->vektor);
                                                                   //brechbedingung prüfen
                                                                   if((n1>n2)&&(w1>=wg)){//nicht brechen
                                                                   }else{
                                                                    /*_tg tet=asin( (n1*sin(w1*_ph))/n2);;
                                                                    if(isnan(tet)){
                                                                     _win::_pclautsprecher sss;
                                                                     sss.peep(100);
                                                                    };*/
                                                                    w2=asin( (n1*sin(w1*_ph))/n2);
                                                                    w2=(w2*180)/_pi;
                                                                    //w2-=90;
                                                                    l1=lot;
                                                                    l1.normalisieren();
                                                                    v=-rnormal*cos(w2*_ph)+l1*sin(w2*_ph);
                                                                    strahl=new _strahl(this,welt,ss,ss->ort,v);
                                                                    neustrahlen.einhaengen(strahl);
                                                                    if(prefraktiondispersiv) {
                                                                     strahl->monochrom=true;
                                                                     strahl->wellenlaenge=wl;
                                                                     strahl->filter=filter;
                                                                     strahl->filterroh=filterroh;
                                                                    };
                                                                    
                                                                    if(welt->anfang(mit))do{
                                                                     if(mit->anfang(pit))do{
                                                                      if(  ((pit->normale()*strahl->vektor)<nahenull)||(pit->zweiseitig()) ) {
                                                                       if(pit->schnittpunkt(strahl->ort,strahl->vektor,nahenull,true,alpha,beta,gamma)){
                                                                        new _strahlschnitt(strahl,strahl->ort+strahl->vektor*gamma,pit,0,0,0,alpha,beta,gamma);
                                                                       };
                                                                      };
                                                                     }while(mit->naechstes(pit));
                                                                    }while(welt->naechstes(mit)); 
                                                                    //nur ersten übrig lassen
                                                                    strahl->loeschenschnittpunktaussererster();
                                                                    if(strahl->anfang(sit)){
                                                                     if(tiefe>0) {
                                                                      erzeugenstrahlbaumrefraktion(sit,tiefe-1);
                                                                     };
                                                                    };
                                                                   };
                                                                  
                                                                  
                                                                  
                                                                  };//for schleife
 
 
 
 
                                                                  
                                                                  //strahlenintensitäten verteilen
                                                                  if(neustrahlen.anzahl()>1){
                                                                   //sd=0.5f/_tg(neustrahlen.anzahl()-1);
                                                                   neustrahlen.anfang(stt);
                                                                   stt->objekt()->blende=1-trans;
                                                                   stt=stt->naechstes();
                                                                   do{
                                                                    stt->objekt()->blende=trans;
                                                                   }while(neustrahlen.naechstes(stt));
                                                                  };
 
                                                                  
                                                                  
                                                                  
                                                                  
                                                                  
                                                                  
                                                                  
                                                                  
                                                                  
                                                                  
                                                                  
                                                                  
                                                                  
                                                                  
                                                                  
                                                                  
                                                                  /*bool neuemonochrom=false;
                                                                  unsigned int sanzahl;
                                                                  unsigned int si;
                                                                  if(prefraktiondispersiv) neuemonochrom=true;
                                                                  for(si=0;si<sanzahl;si++){*/
                                                                  
                                                                  
                                                                  
                                                                  
                                                                  
                                                                  
                                                                  /*if(sc<nahenull){
                                                                   //eintretend, keine totalreflektion, nur teilrefelektion
                                                                   if(prefraktiondispersiv==false){
                                                                    n1=welt->brechzahl();//vakuum
                                                                    n2=ss->polygon->netz()->brechzahl();//optische dichte des netz, in das eingetaucht wird
                                                                   }else{
                                                                    
                                                                    n1=welt->brechzahldispersiv(wl);//vakuum
                                                                    n2=ss->polygon->netz()->brechzahldispersiv(wl);//optische dichte des netz, in das eingetaucht wird
                                                                   };
                                                                   w1=ss->normale.winkel(-ss->strahl->vektor);
                                                                   w2=asin( (n1*sin(w1*_ph))/n2);
                                                                   w2=(w2*180)/_pi;
                                                                   //d1,d2 holen
                                                                   d1=cos((90-w1)*_ph);
                                                                   d2=sin(w2*_ph);
                                                                   d3=cos(w2*_ph);
                                                                   //l1 holen
                                                                   h=-ss->strahl->vektor;
                                                                   h.normalisieren();
                                                                   V3.lotpunktgerade(h,null,ss->normale,lot);
                                                                   l1=lot;
                                                                   l1.normalisieren();
                                                                   //gebrochenen vektor holen
                                                                   vb= -ss->normale*d3 + l1*d2;
                                                                   //reflektierten vektor holen
                                                                   h=-ss->strahl->vektor;
                                                                   h.normalisieren();
                                                                   vr=h+lot*2;
                                                                  }else{
                                                                   //austretend evtl nur totalreflektion
                                                                   n1=ss->polygon->netz()->brechzahl();//optische dichte des netz, in das eingetaucht wird
                                                                   n2=welt->brechzahl();//vakuum
                                                                   w1=ss->normale.winkel(ss->strahl->vektor);
                                                                   wg=(asin(n2/n1)*180)/_pi;
                                                                   //totalreflektion 
                                                                   h=-ss->strahl->vektor;
                                                                   h.normalisieren();
                                                                   V3.lotpunktgerade(h,null,-ss->normale,lot);
                                                                   vr=h+lot*2;
                                                                   if(w1<wg){//brechung
                                                                    w2=asin( (n1*sin(w1*_ph))/n2);
                                                                    w2=(w2*180)/_pi;
                                                                    l1=lot;
                                                                    l1.normalisieren();
                                                                    d1=sin(w2*_ph);
                                                                    d2=cos(w2*_ph);
                                                                    vb=l1*d1 + ss->normale*d2;
                                                                   };
                                                                  };*/
                                                                  
                                                                  /*vrs=true;
                                                                  if(vr.laenge()>0){
                                                                   strahl=new _strahl(this,welt,ss,ss->ort,vr);
                                                                   strahlr=strahl;
                                                                   vrs=true;
                                                                   if(welt->anfang(mit))do{
                                                                    if(mit->anfang(pit))do{
                                                                     if(pit->schnittpunkt(strahl->ort,strahl->vektor,nahenull,true,alpha,beta,gamma)){
                                                                      new _strahlschnitt(strahl,strahl->ort+strahl->vektor*gamma,pit,0,0,0,alpha,beta,gamma);
                                                                     };
                                                                    }while(mit->naechstes(pit));
                                                                   }while(welt->naechstes(mit)); 
                                                                   //nur ersten übrig lassen
                                                                   strahl->loeschenschnittpunktaussererster();
                                                                   if(strahl->anfang(sit)){
                                                                    if(tiefe>0) {
                                                                     erzeugenstrahlbaumrefraktion(sit,tiefe-1);
                                                                    };
                                                                   };
                                                                  };*/
                                                                  
  
                                                                 /* if(vb.laenge()>0){
                                                                   strahl=new _strahl(this,welt,ss,ss->ort,vb);
                                                                   neustrahlen.einhaengen(strahl);
                                                                   if(welt->anfang(mit))do{
                                                                    if(mit->anfang(pit))do{
                                                                     if(pit->schnittpunkt(strahl->ort,strahl->vektor,nahenull,true,alpha,beta,gamma)){
                                                                      new _strahlschnitt(strahl,strahl->ort+strahl->vektor*gamma,pit,0,0,0,alpha,beta,gamma);
                                                                     };
                                                                    }while(mit->naechstes(pit));
                                                                   }while(welt->naechstes(mit)); 
                                                                   //nur ersten übrig lassen
                                                                   strahl->loeschenschnittpunktaussererster();
                                                                   if(strahl->anfang(sit)){
                                                                    if(tiefe>0) {
                                                                     erzeugenstrahlbaumrefraktion(sit,tiefe-1);
                                                                    };
                                                                   };
                                                                  };*/
                                                                  
                                                                  //if((vrs)&&(vbs)) sd=0.75; else sd=1;
                                                                  //if(vrs)strahlr->blende=sd;
                                                                  //if(vbs)strahlb->blende=sd;
                                                                  
                                                                  
                                                                  
 
 
 
 
                                                                 //};
                                                                };
                                                                return(strahl);
};                                                                

_strahl* _bestrahler::erzeugenstrahlbaumreflektion(_strahlschnitt*ss,_vektor3<_tg> ort,_vektor3<_tg> vektor,unsigned int tiefe){ 
                                                                //reflektionsrekursion
                                                                _tg alpha;
                                                                _tg beta;
                                                                _tg gamma;
                                                                _netz*mit; //netz-iterator
                                                                _polygon*pit;
                                                                _strahl*strahl;
                                                                _strahlschnitt*sit;
                                                                //------------------------------
                                                                strahl=new _strahl(this,welt,ss,ort,vektor);
                                                                if(welt->anfang(mit))do{
                                                                 if(mit->anfang(pit))do{
                                                                  if(pit->schnittpunkt(ort,vektor,nahenull,true,alpha,beta,gamma)){
                                                                   new _strahlschnitt(strahl,strahl->ort+strahl->vektor*gamma,pit,0,0,0,alpha,beta,gamma);
                                                                  };
                                                                 }while(mit->naechstes(pit));
                                                                }while(welt->naechstes(mit)); 
                                                                if(tiefe>0){
                                                                 if(strahl->anfang(sit))do{
                                                                  erzeugenstrahlbaumreflektion(sit,sit->ort,sit->reflektionsvektor(),tiefe-1);
                                                                 }while(strahl->naechstes(sit));
                                                                };
                                                                return(strahl);
};                                                                  

bool _bestrahler::berechnenfarbe(_strahl*s,_vektor3<_to>&e){
                                                                _strahlschnitt*sit;
                                                                _strahlschnitt*letzer;
                                                                _vektor3<_to> l;
                                                                _vektor<_tb> et4(4);
                                                                _vektor3<_to> et;
                                                                //_to texalpha;
                                                                bool r;
                                                                _strahl*stit;
                                                                _vektor3<_to> reflektionsanteil;
                                                                _vektor3<_to> h;
                                                                _to trans;
                                                                //--------------------------------
                                                                e.setzen(0,0,0);
                                                                if(s->anfang(sit)){
                                                                 if(sit->transparenz(et4)>0){
                                                                  letzer=sit->vorheriges();
                                                                  sit=letzer;
                                                                  do{
                                                                   trans=sit->transparenz(et4);
                                                                   //et.setzen(0,0,0,0);
                                                                   //sit->farbetextur(et);
                                                                   //et.konvertieren(3);
                                                                   et.setzenkomponente(0,et4[0]);
                                                                   et.setzenkomponente(1,et4[1]);
                                                                   et.setzenkomponente(2,et4[2]);
                                                                   l.setzen(0,0,0);
                                                                   sit->farbelicht(l);
                   //                 l+=pfarbeambient;  mal rausgenommen, da ambient eigentlich zuletzt draufaddiert wird
                                                                   l.begrenzen(0,1);
                                                                   et.produkt(l);
                                                                   e=(e*trans)+(et*(1-trans));
                                                                   //------ reflektionsfarbe berechnen---------
                                                                   reflektionsanteil.setzen(0,0,0);
                                                                   if(sit->anfang(stit)){
                                                                    do{
                                                                     berechnenfarbe(stit,h);
                                                                     reflektionsanteil+=h;
                                                                    }while(sit->naechstes(stit));
                                                                    e+=reflektionsanteil;//*0.8;//achtung empirische konstante !!!!!!!!!!!!!!;//*0.5+e*0.5;
                                                                    e.begrenzen(0,1);
                                                                   };
                                                                   sit=sit->vorheriges();
                                                                  }while(sit!=letzer);
                                                                  e*=s->blende;
                                                                  if(s->monochrom) e.produkt(s->filter);
                                                                  e.begrenzen(0,1);
                                                                 }else{
                                                                  //------------------------------------------
                                                                  //e.setzen(0,0,0);
                                                                  //sit->farbetextur(e);
                                                                  //et.konvertieren(3);
                                                                  et.setzenkomponente(0,et4[0]);
                                                                  et.setzenkomponente(1,et4[1]);
                                                                  et.setzenkomponente(2,et4[2]);
                                                                  e=et;
                                                                  sit->farbelicht(l);
//                 l+=pfarbeambient;  mal rausgenommen, da ambient eigentlich zuletzt draufaddiert wird                                                                  
                                                                  l.begrenzen(0,1);
                                                                  e.produkt(l);
                                                                  //------ reflektionsfarbe berechnen---------
                                                                  reflektionsanteil.setzen(0,0,0);
                                                                  if(sit->anfang(stit)){
                                                                   do{
                                                                    berechnenfarbe(stit,h);
                                                                    reflektionsanteil+=h;
                                                                   }while(sit->naechstes(stit));
                                                                   e+=reflektionsanteil;//*0.8;//achtung empirische konstante !!!!!!!!!!!!!!
                                                                  };
                                                                  e*=s->blende;
                                                                  if(s->monochrom) e.produkt(s->filter);
                                                                  e.begrenzen(0,1);
                                                                 };
                                                                 r=true;
                                                                }else{
                                                                 r=false;
                                                                };
                                                                return(r);
};

_strahl* _bestrahler::erzeugenstrahlbaum(_vektor3<_tg> ort,_vektor3<_tg> vektor,unsigned int tiefe,_tg min,_tg max,_polygon*pex){ 
                                                                //für lichtintensitätsberechnung        
                                                                _tg alpha;
                                                                _tg beta;
                                                                _tg gamma;
                                                                _netz*mit; //netz-iterator
                                                                _polygon*pit;
                                                                _strahl*strahl;
                                                                //----------------------------------
                                                                strahl=new _strahl(this,welt,ort,vektor);
                                                                if(welt->anfang(mit))do{
                                                                 if(mit->anfang(pit))do{
                                                                  if(pit!=pex){
                                                                   if(  ((pit->normale()*vektor)<nahenull)||(pit->zweiseitig()) ) {
                                                                    if(pit->schnittpunkt(ort,vektor,nahenull,min,max,alpha,beta,gamma)){
                                                                     //_strahlschnitt*ss;
                                                                     //ss=
                                                                     new _strahlschnitt(strahl,strahl->ort+strahl->vektor*gamma,pit,0,0,0,alpha,beta,gamma);
                                                                     // ************** DEBUG **************
                                                                     //_vektor<_to> col;
                                                                     //col.setzen(1,0,0);
                                                                     //new _weltdebugkreuz(welt,ss->ort,0.01,col);
                                                                     // ***********************************
                                                                    };
                                                                   };
                                                                  };
                                                                 }while(mit->naechstes(pit));
                                                                }while(welt->naechstes(mit)); 
                                                                return(strahl);
};

bool _bestrahler::berechnenfarbe(_strahl*s,_licht<_tg,_to>*lit,_vektor3<_to>&e){
                                                                _strahlschnitt*sit;
                                                                _vektor<_to> l;
                                                                _vektor3<_to> et;
                                                                _vektor<_tb> et4(4);
                                                                _vektor3<_to> eins;
                                                                _vektor3<_to> texl;
                                                                _to t;
                                                                _to texalpha;
                                                                _to tp;
                                                                bool r;
                                                                bool opak;
                                                                //--------------------------------
                                                                if(s->anfang(sit)){
                                                                 opak=false;
                                                                 do{
                                                                  if(sit->transparenz(et4)==0) opak=true;
                                                                 }while((s->naechstes(sit))&&(opak==false));
                                                                 if(opak==false){
                                                                  e=lit->farbestatisch();
                                                                  eins.setzen(1,1,1);
                                                                  s->anfang(sit);
                                                                  do{
                                                                   et4.setzen(0,0,0,_tb(0.5f*255));
                                                                   //sit->farbetextur(et);
                                                                   t=sit->transparenz(et4);
                                                                  /* et4.setzenkomponente(0,0.4);
                                                                   et4.setzenkomponente(1,0.4);
                                                                   et4.setzenkomponente(2,0.4);*/
                                                                   texalpha=1-_to(et4[3])/_to(255);
                                                                   //et.konvertieren(3);
                                                                   et.setzenkomponente(0,et4[0]);
                                                                   et.setzenkomponente(1,et4[1]);
                                                                   et.setzenkomponente(2,et4[2]);
                                                                   et.mul(1.0f/255.0f);
                                                                   //t=sit->polygon->transparentfaktor();
                                                                   //t=texalpha;
                                                                   //e*=texalpha;
                                                                   //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! ACHTUNG BAUSTELLE
                                                                   tp=(_to)sit->polygon->transparenzfaktor();
                                                                   texl=e;
                                                                   texl.produkt(et);
                                                                   texl*=(texalpha); 
                                                                   e=((e*tp)+(texl*(1-tp)))*t;
                                                                   //(texl*t)+
                                                                   //(texl*

                                                                   
                                                                   
                                                                   
                                                               //    e.produkt(et);
                                                               //    t=sit->transparenz(et);
                                                                //   e*=t; 
                                                                   //e=((e*t)+(et*(1-t)))*t;
                                                                   //e.produkt(et);
                                                                  //e*=t;
                                                                   //e.produkt(et*(sit->polygon->transparentfaktor()));
                                                                 //  et.produkt(l);
                                                                  // e=(e*sit->polygon->transparentfaktor())+(et*(1-sit->polygon->transparentfaktor()));
                                                                   //e=(e*0.98)+(et*0.02);
                                                                  // sit=sit->vorheriges();
                                                                  }while(s->naechstes(sit));
                                                                 }else{
                                                                  e.setzen(0,0,0);
                                                                 };
                                                                 r=true;
                                                                }else{
                                                                 e=lit->farbestatisch();
                                                                 r=false;
                                                                };
                                                                return(r);
};

_tg _bestrahler::berechnenlichtintensitaet(const _vektor3<_tg>&o,const _vektor3<_tg>&n,_licht<_tg,_to>*lit){
                                                                _vektor3<_tg> v;
                                                                _tg s;
                                                                _tg d;
                                                                _tg e;
                                                                //-------------
                                                                v=lit->ort()-o;
                                                                d=v.laenge();
                                                                v.normalisieren();
                                                                s=n*v;
                                                                e=lit->intensitaetstatisch()*s*(1.0f/(1.0f+(d*d)));
                                                                if(e<0) e=0;
                                                              //  if(e>1) e=1;
                                                                return(e);
};


void _bestrahler::spektralkonversion(_tg wl,_vektor3<_to>&rgb){
                                                                rgb.setzen(0,0,0);
                                                                //rgb peak
                                                                spektralkonversion(0,550,650,750,1.00,wl,rgb);
                                                                spektralkonversion(1,450,550,650,1.00,wl,rgb);
                                                                spektralkonversion(2,350,450,550,1.00,wl,rgb);
                                                                //cyan peak
                                                                spektralkonversion(1,450,500,550,0.50,wl,rgb);
                                                                spektralkonversion(2,450,500,550,0.50,wl,rgb);
                                                                //gelb peak
                                                                spektralkonversion(0,550,600,650,0.50,wl,rgb);
                                                                spektralkonversion(1,550,600,650,0.50,wl,rgb);
                                                                
                                                                //uv peak
                                                                spektralkonversion(0,350,400,450,0.23,wl,rgb);
};

void _bestrahler::spektralkonversion(unsigned int kanal,_tg anf,_tg max,_tg end,_tg scale,_tg wl,_vektor3<_to>&rgb){
                                                                _tg a;
                                                                _to o;
                                                                _vektor3<_to> v;
                                                                //---------
                                                                if((wl>=anf)&&(wl<=end)){
                                                                 if(wl<max){
                                                                  a=(wl-anf)/(max-anf);
                                                                 }else{
                                                                  a=1-((wl-max)/(end-max));
                                                                 };
                                                                 a*=scale;
                                                                 o=(_to)a;//konversion
                                                                 v.setzen(0,0,0);
                                                                 v.setzenkomponente(kanal,o);
                                                                 rgb+=v;
                                                                };
};
//******************************************************************************************************************************************************************************************************
//                                                              S T R A H L
//******************************************************************************************************************************************************************************************************

_strahl::_strahl(_bestrahler*b,_welt*w,const _vektor3<_tg>&o,const _vektor3<_tg>&v){
                                                                vektor=v;
                                                                ort=o;
                                                                welt=w;
                                                                bestrahler=b;
                                                                filter.setzen(1,1,1);
                                                                filterroh.setzen(1,1,1);
                                                                blende=1;
                                                                monochrom=false;
                                                                wellenlaenge=535;//absolut grün
};

_strahl::_strahl(_bestrahler*b,_welt*w,_strahlschnitt*ss,const _vektor3<_tg>&o,const _vektor3<_tg>&v):_listenknotenbasis<_strahl >(ss){
                                                                vektor=v;
                                                                ort=o;
                                                                welt=w;
                                                                bestrahler=b;
                                                                filter.setzen(1,1,1);
                                                                filterroh.setzen(1,1,1);
                                                                blende=1;
                                                                monochrom=false;
};

_strahl::~_strahl(){
};


void _strahl::loeschenschnittpunktverdeckt(){
                                                                _strahlschnitt*sit;
                                                                _vektor<_tb> tex;
                                                                bool opak;
                                                                //-------------------------------
                                                                opak=false;
                                                                if(anfang(sit))do{
                                                                 if(opak==true){
                                                                  sit->loeschmarkierung(true);
                                                                 }else{
                                                                  if(sit->transparenz(tex)==0) opak=true;
                                                                  //if(sit->polygon->transparent()==false) opak=true;
                                                                  //if(sit->polygon->transparentfaktor()==0) opak=true;
                                                                 };
                                                                }while(naechstes(sit));
                                                                loeschenmarkiert();//verdeckte schnittpunkte löschen
};

void _strahl::loeschenschnittpunktaussererster(){
                                                                bool erster=true;
                                                                _strahlschnitt*sit;
                                                                //---------------------------------
                                                                if(anfang(sit))do{
                                                                 if(erster==false) sit->loeschmarkierung(true);
                                                                 erster=false;
                                                                }while(naechstes(sit));
                                                                loeschenmarkiert();
};                                                                
//******************************************************************************************************************************************************************************************************
//                                                              S T R A H L S C H N I T T 
//******************************************************************************************************************************************************************************************************

_strahlschnitt::_strahlschnitt(_strahl*s,_vektor3<_tg> o,_polygon*p,_vertex*v0,_vertex*v1,_vertex*v2,_tg pa,_tg pb,_tg pc):_listenknotenbasissortiert<_strahlschnitt,_tg>(s,pc){
                                                                strahl=s;
                                                                ort=o;
                                                                polygon=p;
                                                                normale=polygon->normale();
                                                                vertex[0]=v0;
                                                                vertex[1]=v1;
                                                                vertex[2]=v2;
                                                                a=pa;
                                                                b=pb;
                                                                c=pc;
                                                                ptransparenz=0;
                                                                ptransparenzupdated=false;
                                                                pfarbetextur.setzen(1,1,1,0);
                                                                pfarbetexturupdated=false;
};

_strahlschnitt::~_strahlschnitt(){
};

bool _strahlschnitt::schatten(_licht<_tg,_to>*lit,_vektor3<_to>&farbe){
                                                                //funktion gibt die lichtstrahlung zurück, 
                                                                //die an diesem strahlschnitt auftritt
                                                                _strahl*s;
                                                                //_strahlschnitt*sit;
                                                                bool r;
                                                                //---------------
                                                                farbe=lit->farbestatisch();
                                                                s=strahl->bestrahler->erzeugenstrahlbaum(ort,lit->ort()-ort,0,0,1,polygon);
                                                                r=strahl->bestrahler->berechnenfarbe(s,lit,farbe);
                                                                delete s;
                                                                
                                                                /*
                                                                if(welt->anfang(mit))do{
                                                                 if(mit->anfang(pit))do{
                                                                  if(pit!=polygon){
                                                                   if(pit->schnittpunkt(ort,v,nahenull,0,1)){
                                                                    r=true;
                                                                   };
                                                                  };
                                                                 }while((mit->naechstes(pit))&&(r==false));
                                                                }while((welt->naechstes(mit))&&(r==false));
                                                                */
                                                                return(r);
};


void _strahlschnitt::farbelicht(_vektor3<_to>&e){
                                                                _vektor3<_tg> v;
                                                                _vektor3<_tg> n;
                                                                _tg s;
                                                                _tg d;
                                                                _welt*welt;
                                                                _licht<_tg,_to>*lit;
                                                                _vektor3<_to> farbe;
                                                                //---------------
                                                                welt=strahl->welt;
                                                                e.setzen(0,0,0);
                                                                if(welt->anfang(lit))do{
                                                                  v=lit->ort()-ort;
                                                                  d=v.laenge();
                                                                  v.normalisieren();
                                                                  s=normale*v;
                                                                  if(s<=0){
                                                                   
                                                                   if((normale*strahl->vektor)>0) s=-normale *v;
                                                                  };
                                                                  if(s>0){
                                                                   schatten(lit,farbe);
                                                                   e+=(farbe*lit->intensitaetstatisch())*float(s)*(1.0f/(1.0f+float(d*d)));
                                                                  };
                                                                 
                                                                }while(welt->naechstes(lit));
                                                                e.begrenzen(0,1);
};

void _strahlschnitt::farbetextur(_vektor<_tb>&e){
                                                                _bild<_tb>*m;
                                                                //_texturvektor<_tg>*tv;
                                                                //_bildvektor<_tg>*mv;
                                                                //_verbindervertexpolygon*c0;
                                                                //_verbindervertexpolygon*c1;
                                                                //_verbindervertexpolygon*c2;
                                                                _vektor2<_tg> ve;
                                                                int tx,ty;
                                                                unsigned int mx,my;
                                                                //------------
                                                                if(polygon->textur()){
                                                                 _listenknoten<_bild<_tb> >*lnm;
                                                                 if(polygon->textur()->bitmap()->anfang(lnm)){
                                                                  m=lnm->objekt();
                                                                 
                                                                  if(pfarbetexturupdated==false){
                                                                  /*
                                                                   c0=vertex[0]->connector(polygon);
                                                                   c1=vertex[1]->connector(polygon);
                                                                   c2=vertex[2]->connector(polygon);
                                                                   _vektor3<_tg>&v0=c0->holenvektor((unsigned int)0,(unsigned int)0);
                                                                   _vektor3<_tg>&v1=c1->holenvektor((unsigned int)0,(unsigned int)0);
                                                                   _vektor3<_tg>&v2=c2->holenvektor((unsigned int)0,(unsigned int)0);
                                                                   ve=v0+(v1-v0)*b+(v2-v0)*a;*/
                                                                   
                                                                   if(polygon->texturespace()) polygon->texturespace()->interpolieren(0,0,a,b,ve); else ve.setzen(0.1,0.1);
                                                                   //ve.setzen(0.1,0.1);
                                                                   
                                                                   tx=int(ve[0]*_tg(m->groesse(0)));
                                                                   ty=int(ve[1]*_tg(m->groesse(1)));
                                                                   while(tx<0) tx+=int(m->groesse(0));
                                                                   while(tx>=int(m->groesse(0))) tx-=(int)m->groesse(0);
                                                                   while(ty<0) ty+=int(m->groesse(1));
                                                                   while(ty>=int(m->groesse(1))) ty-=(int)m->groesse(1);
                                                                   mx=(unsigned int)tx;
                                                                   my=(unsigned int)ty;
                                                                   m->lesen(mx,my,e);
                                                                   pfarbetextur=e;
                                                                   pfarbetexturupdated=true;
                                                                  }else{
                                                                   e=pfarbetextur;
                                                                  };
                                                                  
                                                                 };
                                                                };
};
_vektor3<_tg> _strahlschnitt::reflektionsvektor(){
                                                                _vektor3<_tg> e;
                                                                strahl->bestrahler->V3.reflektierenpunktnormale(ort-strahl->vektor,ort,polygon->normale(),e);
                                                                return(e-ort);
};
_to _strahlschnitt::transparenz(_vektor<_tb>&tex){//vektor muss dynamsich bleiben
                                                                tex.setzen(0,0,0,1);
                                                                farbetextur(tex);
                                                                if(ptransparenzupdated==false){
                                                                 if(polygon->transparenz()){
                                                                  ptransparenz=1-((1-(_to)polygon->transparenzfaktor())*(1-tex[3]));
                                                                 }else{
                                                                  ptransparenz=0;
                                                                 };
                                                                 ptransparenzupdated=true;
                                                                };
                                                                return(ptransparenz);
};

/*
_vektor3<_tg> _strahlschnitt::normale(){
                                                                return(polygon->normale());
};*/
//******************************************************************************************************************************************************************************************************
//                                                              S P E K T R A L L I N I E 
//******************************************************************************************************************************************************************************************************
_spektrallinie::_spektrallinie(_listebasis<_spektrallinie >*l,_tg wl,_vektor3<_to> rgb):_listenknotenbasis<_spektrallinie >(l){
                                                                wellenlaenge=wl;
                                                                rgbwert=rgb;
                                                                rgbwertroh=rgb;
};

_spektrallinie::~_spektrallinie(){
};

