//******************************************************************************************************************************************************************************************************
//  Projekt      : grundplatte
//  Bibliothek   : _grundplatte.lib
//  Modul        : _weltintersektion.cpp
//  Datum        : 09.01.2006
//  Beschreibung : 
//******************************************************************************************************************************************************************************************************
#include <_weltintersektion.hpp>
#include <_weltpolygon.hpp>
#include <_systemwin.hpp>

_welt*DW=0;
//******************************************************************************************************************************************************************************************************
//                                                              M O D I F I K A T I O N N E T Z I N T E R S E K T I O N 
//******************************************************************************************************************************************************************************************************
/*_modifikationnetzintersektion::_modifikationnetzintersektion(_geometrie*g,unsigned int op):_modifikation(g){
                                                                init(op);
};*/

_modifikationnetzintersektion::_modifikationnetzintersektion():_modifikation(){
                                                                init(0);
};

void _modifikationnetzintersektion::init(unsigned int op){
                                                                DW=0;
                                                                mainoperation=0;
                                                                poperation=0;
                                                                maxgitentry=10;
                                                                pvereinigungohneschnitt=true;
                                                                nearzerovalue(0.00005f);
                                                                operation(op);
                                                                searchiteratorcountmaximal(maxgitentry);
                                                                spreadnexttry=1;
                                                                spreadprevtry=1;
                                                                partitionsequence=new _liste<_ringsektion >();
                                                                meshtointersect=0;
                                                                intersectingmesh=0;
                                                                thismesh=0;
                                                                nointersection=0;
                                                                plog=true;
                                                                S=new _win::_system(0);
                                                                //********* DEBUG **********
                                                                //cam=new _kamera<_tg>(W);
                                                                //cam->setzen(0,0,-20);
                                                                debugskipcount=0;
                                                                dbscreen=0;
                                                                dbcam=0;
                                                                //dbmo=0;
                                                                //dbgra=0;
                                                                pdbcolnote.setzen(0.75f,0.75f,0,0);
                                                                pdbcolerror.setzen(1,0,0,0);
                                                                pdbcolfunc.setzen(0.3f,1.0f,0.15f,0);
};

_modifikationnetzintersektion::~_modifikationnetzintersektion(){
                                                                partitionsequence->loeschen();
                                                                delete partitionsequence;
                                                                partitionsequence=0;
                                                                polygonoptimationlist.loeschen();
                                                                //********* DEBUG **********
                                                                deletesecure(S);
                                                                //if(cam){
                                                                // delete cam;
                                                                // cam=0;
                                                                //};
                                                                cleardebugscreen();
};
void _modifikationnetzintersektion::debugwelt(_welt*w){
                                                                DW=w;
                                                                
};
void _modifikationnetzintersektion::schreibenlogbuch(bool b){
                                                                plog=b;
};
bool _modifikationnetzintersektion::schreibenlogbuch()const{
                                                                return(plog);
};
//**************************************************************  P U B L I C   A P I  ******************************************************************************************************

char _modifikationnetzintersektion::bearbeiten(_netz*_mi){
                                                           /*     _geometrie*git;
                                                                _netz*m;
                                                                char r;
                                                                //---------------------
                                                                r=1;
                                                                if(anfang(git))do{
                                                                 m=git->erzeugen();
                                                                 if(bearbeiten(_mi,m,mainoperation)==0) r=0; 
                                                                 delete m;
                                                                 m=0;
                                                                }while((naechstes(git))&&(r==1));
                                                                */
                                                                return(0);
};

char _modifikationnetzintersektion::bearbeiten(_netz*_mi,_netz*_im,int op){
                                                                //mi: netz to intersekt
                                                                //im: intersecting netz
                                                                //operation : 0 = intersecting
                                                                //            1 = deintersecting
                                                                //            2 = merging/uniting
                                                                //            3 = dividing
                                                                int mistatus;
                                                                int imstatus;
                                                                bool misub;
                                                                bool imsub;
                                                                _netz*tempmesh;
                                                                char r;
                                                                //-------------------------------
                                                                r=1;
                                                                //*********** DEBUG *************
                                                                createdebugscreen();
                                                                //if(dbscreen) dbscreen->schreiben("_modifikationnetzintersektion::bearbeiten(_netz*,_netz*,int) : startet.",pdbcolfunc);
                                                                //if(plog) L->schreiben("_modifikationnetzintersektion::bearbeiten(_netz*,_netz*,int) : startet.");
                                                                //_mi->einhaengen(W);
                                                                //_im->einhaengen(W);
                                                                //*******************************
                                                                poperation=op;   
                                                                meshtointersect=_mi;
                                                                intersectingmesh=_im;
                                                                misub=meshtointersect->subtraktiv();
                                                                imsub=intersectingmesh->subtraktiv();
                                                                meshtointersect->subtraktiv(false);
                                                                intersectingmesh->subtraktiv(false);
                                                                if(poperation==3){
                                                                 tempmesh=meshtointersect->duplizieren();
                                                                 if(bearbeiten(meshtointersect,intersectingmesh,0)==1){
                                                                  if(bearbeiten(tempmesh,intersectingmesh,1)==0){
                                                                   r=0;
                                                                  };
                                                                 }else{
                                                                  r=0;   
                                                                 };
                                                                 meshtointersect=_mi;
                                                                 intersectingmesh=_im;
                                                                 meshtointersect->vereinigen(tempmesh);
                                                                }else{
                                                                 if((poperation>3)||(poperation<0)){
                                                                  fehler("void _modifikationnetzintersektion::bearbeiten(_netz*,_netz*,int)","ungültige Operation");
                                                                  if(dbscreen) dbscreen->schreiben("void _modifikationnetzintersektion::bearbeiten(_netz*,_netz*,int) : ungültige Operation",pdbcolerror);
                                                                 }else{
                                                                  nointersection=1;
                                                                  meshtointersect->vorbereitenintersektion();
                                                                  intersectingmesh->vorbereitenintersektion();
                                                                  meshtointersect->erzeugenkante();
                                                                  intersectingmesh->erzeugenkante(); 
                                                                  determineintersection();
                                                                  // ********************************DEBUG********************
																
                                                                 // visualizeintersection();
                                                                 // visualizeconnectorstruct();
                                                                  //visualizeintroconnectorstruct();
                                                                  //visualizeextroconnectorstruct();
                                                                  //debuganimwait();
                                                                  // *********************************************************
                                                                  if(nointersection==0){
                                                                   polygonoptimationlist.loeschen();
                                                                   thismesh=meshtointersect;
                                                                   createstatusstruct(thismesh);
                                                                   thismesh=intersectingmesh;
																   createstatusstruct(thismesh);
																   
																   
																   
																   /*
																   L->schreiben("HELF");
																   _polygon*pit;
																   _vertex*vit;
																   if(thismesh->anfang(pit))do{
																    if(pit->status()==0){
																     L->schreiben("POLY is am schnitt beteiligt");
																     vit=pit->vertex();
																     if(vit)do{
																      if(vit->intersektion()) {
																       new _statussektion(vit->intersektion(),pit);
																       new _statussektion(vit->intersektion(),pit);
																       new _statussektion(vit->intersektion(),pit);
																       
																       L->schreiben("Virtuelle Intersection liegt vor...");
																       int ii=vit->intersektion()->_listebasis<_statussektion > ::anzahl();
																       L->schreiben("Anzahl der Statussektionen an dieser virutellen Intersektion : ",ii);
																       _statussektion*sit;
																       if(vit->intersektion()->anfang(sit))do{
																        L->schreiben("SS");
																       }while(vit->intersektion()->naechstes(sit));
																      };
																      vit=vit->naechstes(pit);
																     }while(vit!=pit->vertex());
																    };
																   
																   }while(thismesh->naechstes(pit));
																   */
																   
																   
                                                                  
																   // ***************************DEBUG*************************
                                                                   //visualizeintersection();
                                                                   //visualizestatusstruct(meshtointersect);
                                                                   //visualizestatusstruct(intersectingmesh);
                                                                   //debuganimwait();
                                                                   // *********************************************************
                                                                   thismesh=meshtointersect;
                                                                   initintersectionvertices(thismesh);
                                                                   if(createandcoverringpartition(thismesh)==0){
                                                                    fehler("void _modifikationnetzintersektion::bearbeiten(_netz*_mi,_netz*_im,int op)","createandcoverringpartition von meshtointersect war erfolglos. operation wurde abgebrochen");
                                                                    //peep(10);
                                                                    r=0;
                                                                   }else{
                                                                    thismesh=intersectingmesh;
                                                                    intersectingmesh->erzeugenvertexintersektion();
                                                                    intersectingmesh->nullintersektionvertices();
                                                                    if(createandcoverringpartition(thismesh)==0) {
                                                                     fehler("void _modifikationnetzintersektion::bearbeiten(_netz*_mi,_netz*_im,int op)","createandcoverringpartition von intersectingmesh war erfolglos. operation wurde abgebrochen");
                                                                     //peep(10);
                                                                     r=0;
                                                                    };
                                                                   };
                                                                   clearringpartition(meshtointersect);
                                                                   clearringpartition(intersectingmesh);
                                                                   if(r==1){
                                                                    spreadvirtualstatus(meshtointersect);
                                                                    spreadvirtualstatus(intersectingmesh);
                                                                    duplicatepoly(intersectingmesh);
                                                                   };
                                                                   intersectingmesh->loeschenvertexintersektion();
                                                                   clearstatusstruct(meshtointersect);
																   clearstatusstruct(intersectingmesh);
                                                                   clearintersection(meshtointersect);
                                                                   clearintersection(intersectingmesh);
                                                                  };
                                                                  meshtointersect->loeschenkante();
                                                                  intersectingmesh->loeschenkante();
                                                                  if(nointersection==0){
                                                                   if(r==1){
                                                                    destructpoly(meshtointersect);
                                                                    performpolygonoptimation();
                                                                   };
                                                                  }else{
                                                                   if(poperation==2){
                                                                    if(pvereinigungohneschnitt){
                                                                     getstatustotalduplicationanddestruction(mistatus,imstatus);
                                                                     performtotalduplicationanddestruction(mistatus,imstatus);
                                                                    }else{
                                                                     //nichts machen
                                                                    };
                                                                   }else{
                                                                    getstatustotalduplicationanddestruction(mistatus,imstatus);
                                                                    performtotalduplicationanddestruction(mistatus,imstatus);
                                                                   };
                                                                   
                                                                   
                                                                  };
                                                                 };
                                                                };
                                                                meshtointersect->subtraktiv(misub);
                                                                intersectingmesh->subtraktiv(imsub);
                                                                //************************************* DEBUG **********************************
                                                                if(plog) schreiben("_modifikationnetzintersektion::bearbeiten(_netz*,_netz*,int) : beendet.");
                                                                if(dbscreen) dbscreen->schreiben("_modifikationnetzintersektion::bearbeiten(_netz*,_netz*,int) : beendet.",pdbcolfunc);
                                                                cleardebugscreen();
                                                                //******************************************************************************
                                                                return(r);
};
bool _modifikationnetzintersektion::hatintersektion(_netz*test0,_netz*test1){
                                                                bool hasint;
                                                                //----------
                                                                hasint=false;
                                                                meshtointersect=test0;
                                                                intersectingmesh=test1;
                                                                int po=poperation;
                                                                poperation=2;
                                                                nointersection=1;
                                                                meshtointersect->vorbereitenintersektion();
                                                                intersectingmesh->vorbereitenintersektion();
                                                                meshtointersect->erzeugenkante();
                                                                intersectingmesh->erzeugenkante(); 
                                                                determineintersection();
                                                                if(nointersection==0){
                                                                 clearintersection(meshtointersect);
                                                                 clearintersection(intersectingmesh);
                                                                 hasint=true;
                                                                };
                                                                meshtointersect->loeschenkante();
                                                                intersectingmesh->loeschenkante();
                                                                poperation=po;
                                                                meshtointersect=0;
                                                                intersectingmesh=0;
                                                                return(hasint);
};
bool _modifikationnetzintersektion::hatintersektion(_netz*test,_liste<_netz >*incs,_liste<_netz >*excs){
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
                                                                  meshtointersect=test;
                                                                  intersectingmesh=mit->objekt();
                                                                  if((poperation>3)||(poperation<0)){
                                                                   fehler("void _modifikationnetzintersektion::hatintersektion(_netz*,_liste<_netz >*,_liste<_netz >*)","ungültige Operation");
                                                                  }else{
                                                                   nointersection=1;
                                                                   meshtointersect->vorbereitenintersektion();
                                                                   intersectingmesh->vorbereitenintersektion();
                                                                   meshtointersect->erzeugenkante();
                                                                   intersectingmesh->erzeugenkante(); 
                                                                   determineintersection();
                                                                   if(nointersection==0){
                                                                    clearintersection(meshtointersect);
                                                                    clearintersection(intersectingmesh);
                                                                    hasint=true;
                                                                   };
                                                                   meshtointersect->loeschenkante();
                                                                   intersectingmesh->loeschenkante();
                                                                  };
                                                                 };
                                                                }while((incs->naechstes(mit))&(hasint==false));
                                                                return(hasint);
};
bool _modifikationnetzintersektion::netzinnerhalbnetz(_netz*m0,_netz*m1){
                                                                //führt eine punktprüfung eines vertex von this aus
                                                                //ist this innerhalb von m , es wird erwartet,
                                                                //daß vorher eine schnittuntersuchung gemacht wurde,
                                                                //bei der auch komplanarität etc.. ausgeschlossen wurde
                                                                int mistatus,imstatus;
                                                                meshtointersect=m0;
                                                                intersectingmesh=m1;
                                                                int po=poperation;
                                                                poperation=2;
                                                                meshtointersect->vorbereitenintersektion();
                                                                intersectingmesh->vorbereitenintersektion();
                                                                
                                                                getstatustotalduplicationanddestruction(mistatus,imstatus);
                                                                poperation=po;
                                                                meshtointersect=0;
                                                                intersectingmesh=0;
                                                                if(mistatus==-1) return(true); else return(false);
                                                                
};
void _modifikationnetzintersektion::operation(const unsigned int i){
                                                                if((i>=0)&&(i<4)) {
                                                                 mainoperation=i;
                                                                 poperation=i;
                                                                }else{
                                                                 fehler("void _modifikationnetzintersektion::operation(const unsigned int i)","ungültige Wertübergabe");
                                                                };
};

void _modifikationnetzintersektion::searchiteratorcountmaximal(const unsigned int i){
                                                                if(i>3){
                                                                 maxgitentry=i;
                                                                }else{
                                                                 fehler("void _modifikationnetzintersektion::searchiteratorcountmaximal(const unsigned int i)","ungülte Wertübergabe");
                                                                };
};

void _modifikationnetzintersektion::speadpartitiontry(const unsigned int i,const bool b){
                                                                if(i==0){
                                                                 if(b) spreadnexttry=1; else spreadnexttry=0;
                                                                }else{
                                                                 if(b) spreadprevtry=1; else spreadprevtry=0;
                                                                };
};
void _modifikationnetzintersektion::vereinigenohneschnitt(const bool b){
                                                                pvereinigungohneschnitt=b;
};
bool _modifikationnetzintersektion::vereinigenohneschnitt()const{
                                                                return(pvereinigungohneschnitt);
};

void _modifikationnetzintersektion::nearzerovalue(const _tg nz){
                                                                if(nz>=0) nahenull=nz; else fehler("void _modifikationnetzintersektion::nearzerovalue(const _tg nz)","es wurde versucht, einen ungültigen nahenull-wert zu setzten");
};

_tg _modifikationnetzintersektion::nearzerovalue()const{
                                                                return(nahenull);
};

//************************************************************************  G L O B A L M A N A G E R F U N C T I O N *********************************************************************************************************

void _modifikationnetzintersektion::createstatusstruct(_netz*m){
                                                                _polygon*p;
                                                                //---------------
                                                                if(m->anfang(p))do{
                                                                 p->markierungvertexstatus(0);
                                                                 if(p->status()==0){
                                                                  createvertexintersections(m,p);
                                                                  invertisintroconnectorrings(p);
                                                                  formvertexintersectionring(p);
                                                                  integrateintersectionrings(p);
                                                                  uniteintersectionrings(p);
                                                                  //*********************DEBUG******************
                                                                  //visualizeintersectionsequence(p->vertex());
                                                                  //********************************************
                                                                  createstatuscrosses(p);
                                                                 };
                                                                }while(m->naechstes(p));
};

void _modifikationnetzintersektion::clearstatusstruct(_netz*m){
                                                                _polygon*p;
                                                                //-------------
                                                                if(m->anfang(p))do{
                                                                 if(p->status()==0){
                                                                  clearstatuscrosses(p);
                                                                  clearvertexintersections(p);
                                                                 };
                                                                }while(m->naechstes(p));
};
//*************************************************************************  I N T E R S E C T I O N D E T E R M I N A T I O N  ************************************************************************************************

void _modifikationnetzintersektion::determineintersection(){
                                                                _polygon*pi;
                                                                _polygon*ip;
                                                                //--------------
                                                                //********* DEBUG **********
                                                                if(plog) schreiben("_modifikationnetzintersektion::determineintersection ");
                                                                if(dbscreen) dbscreen->schreiben("void determineintersection()",pdbcolfunc);
                                                                //**************************
                                                                meshtointersect->markierungkante(0);
                                                                intersectingmesh->markierungkante(0);
                                                                meshtointersect->markierungpolygonstatus(-2);//0 = am poly liegen schnitte vor / +1 = poly liegt innerhalb des anderen netz
                                                                intersectingmesh->markierungpolygonstatus(-2);//-1 = poly liegt ausserhalb des anderen meshes
                                                                //--------------   poly to intersekt mit intersecting vektor -----------
                                                                if(meshtointersect->anfang(pi))do{
                                                                 if(intersectingmesh->anfang(ip))do{
                                                                  determineintersection(ip,pi);
                                                                 }while(intersectingmesh->naechstes(ip));
                                                                 pi->markierungkante(1);
                                                                }while(meshtointersect->naechstes(pi));
                                                                //--------------   intersecting poly mit vektor to intersekt -----------
                                                                if(intersectingmesh->anfang(ip))do{
                                                                 if(meshtointersect->anfang(pi))do{
                                                                  determineintersection(pi,ip);
                                                                 }while(meshtointersect->naechstes(pi));
                                                                 ip->markierungkante(1);
                                                                }while(intersectingmesh->naechstes(ip));
                                                                //----------------------------------nun introconnectoren für dreiecksflächen ergänzen--------
                                                                meshtointersect->markierungkante(0);
                                                                intersectingmesh->markierungkante(0);
                                                                meshtointersect->markierungvertex(0);
                                                                intersectingmesh->markierungvertex(0);
                                                                //--------------   poly to intersekt mit intersecting vektor -----------
                                                                if(intersectingmesh->anfang(ip))do{
                                                                 completeintersection(ip);
                                                                }while(intersectingmesh->naechstes(ip));
                                                                //--------------   intersecting poly mit vektor to intersekt -----------
                                                                if(meshtointersect->anfang(pi))do{
                                                                 completeintersection(pi);
                                                                }while(meshtointersect->naechstes(pi));
};

void _modifikationnetzintersektion::determineintersection(_polygon*pp,_polygon*pe){
                                                                _kantepolygon*kante;
                                                                _listenknoten<_kantepolygon >*pceit;//_pce*pceit;
                                                                //----------------------
                                                                if(pe->kanten()->anfang(pceit))do{//äussere pedge-iteration
                                                                 kante=pceit->objekt();
                                                                 if(kante->markierung()==0){
                                                                  kante->start(kante->vertex(0));
                                                                  if(determineintersectionoblique(pp,pe,kante)==0){
                                                                   determineintersectionparallel(pp,pe,kante);
                                                                  };
                                                                 };//edgeflag
                                                                }while(pe->kanten()->naechstes(pceit));
};

char _modifikationnetzintersektion::determineintersectionoblique(_polygon*pp,_polygon*pe,_kantepolygon*kante){
                                                                //funktion determiniert intersektion, es wird zunächst von einer schräglage(unparallelität->oblizität)
                                                                //ausgegangen (wenn parallel gibt die funktion null zurück, um anzudeuten, dass parallel untersucht werden muss):
                                                                //1. es erfolgt eine 3x3 - determinante,um schnittpunkt mit der p-ebene zu bestimmen
                                                                //2. sequenzielle p-kante - mitte 2x2 determinante zur bestimmung der p-flächenkoherenz
                                                                _vektor3<_tg> ort;
                                                                _vektor3<_tg> e;
                                                                _vektor3<_tg> va;
                                                                _vektor3<_tg> vb;
                                                                _vektor3<_tg> vc;//negierter richtungsvektor von kante
                                                                _vektor3<_tg> mr;//relativer mittelpunkt
                                                                _vektor3<_tg> s;//schnittpunkt
                                                                _tg b,c;//determinanten vektorenparameter
                                                                _tg D;//hauptdeterminante
                                                                _vektor3<_tg> de;//2D - punktvektor
                                                                _vektor3<_tg> da;//2D - ebenevektor 1
                                                                _vektor3<_tg> db;//2D - ebenevektor 2
                                                                _vektor3<_tg> dv;//abs punkt von eit->vertex[0]
                                                                _vektor2<_tg> de2;//2D - punktvektor
                                                                _vektor2<_tg> da2;//2D - ebenevektor 1
                                                                _vektor2<_tg> db2;//2D - ebenevektor 2
                                                                _vektor2<_tg> dv2;//abs punkt von eit->vertex[0]
                                                                _tg dD;   //2D - hauptdeterminate 
                                                                int c0;
                                                                int c1;
                                                                int c2;
                                                                char innen;
                                                                _listenknoten<_kantepolygon >*pit;
                                                                _kantepolygon*eit;
                                                                bool edgehitplane;
                                                                _tg dis;
                                                                //--------------------------------------------------
                                                                if(dbscreen) dbscreen->schreiben("void determineintersectionoblique()",pdbcolfunc);
                                                                vc=-kante->vektor();
                                                                va=pp->ebene(0);
                                                                vb=pp->ebene(1);
                                                                D=V3.determinieren(va,vb,vc);
                                                                edgehitplane=false;
                                                                if(fabs(D)>nahenull){//--------------------------------------------------------------schräglage
                                                                 e=kante->vertex(0)->ort()-pp->mitte();
                                                                 c=V3.determinieren(va,vb,e)/D;
                                                                 s=kante->vertex(0)->ort()+kante->vektor()*c;
                                                                 if((c>=0)&&(c<=1)){
                                                                  edgehitplane=true;
                                                                 }else{
                                                                  getdistance(s,kante->ort(0),dis);
                                                                  if(dis<=nahenull) edgehitplane=true;
                                                                  getdistance(s,kante->ort(1),dis);
                                                                  if(dis<=nahenull) edgehitplane=true;
                                                                 };
                                                                 if(edgehitplane){
                                                                  mr=pp->mitte();
                                                                  c0=pp->groessterindex(0);
                                                                  c1=pp->groessterindex(1);
                                                                  c2=pp->groessterindex(2);
                                                                  innen=1;
                                                                  if(pp->kanten()->anfang(pit))do{
                                                                   eit=pit->objekt();
                                                                   ort=eit->vertex(0)->ort();
                                                                   de=s-ort;
                                                                   da=eit->vektor();
                                                                   db=pp->mitte()-ort;
                                                                   db.normalisieren();
                                                                   db2.setzen(db[c0],db[c1]);
                                                                   da2.setzen(da[c0],da[c1]);
                                                                   de2.setzen(de[c0],de[c1]);
                                                                   dD=V2.determinieren(da2,db2);
                                                                   if(dD){
                                                                    b=V2.determinieren(da2,de2)/dD;
                                                                    if(b<-nahenull) innen=0;
                                                                   }else{
                                                                    fehler("_modifikationnetzintersektion::determineintersectionoblique()","2D - Hauptdeterminente dD ==0");
                                                                   };
                                                                  }while((pp->kanten()->naechstes(pit))&&(innen==1));
                                                                  if(innen){
                                                                   createintersection(pp,pe,kante,s,c);
                                                                   //************** DEBUG******************
                                                                   //_weltdebugpfeil*wdc;
                                                                   //_vektor4<_to> col;
                                                                   //col.setzen(0,1,0,0);
                                                                   //wdc=new _weltdebugpfeil(W,kante->vertex(0)->ort(),kante->vertex(1)->ort(),0.05,0.02,col);
                                                                   //debuganimwait();
                                                                   //delete wdc;
                                                                  //**************************************
                                                                  };
                                                                 };
                                                                 return(1);
                                                                }else{
                                                                 return(0);//parallel
                                                                };
};

void _modifikationnetzintersektion::determineintersectionparallel(_polygon*pp,_polygon*pe,_kantepolygon*ee){
                                                                char ainner,binner;
                                                                int c0,c1,c2;
                                                                _kantepolygon*ep;
                                                                _listenknoten<_kantepolygon >*pit;
                                                                _vektor2<_tg> peve;
                                                                _vektor2<_tg> pev0;
                                                                _vektor2<_tg> pev1;
                                                                _vektor2<_tg> ppve;
                                                                _vektor2<_tg> ppv0;
                                                                _vektor2<_tg> ppv1;
                                                                _vektor3<_tg> da;
                                                                _vektor3<_tg> db;
                                                                _vektor3<_tg> de;
                                                                _vektor2<_tg> da2;
                                                                _vektor2<_tg> db2;
                                                                _vektor2<_tg> de2;
                                                                _tg D;
                                                                _tg a;
                                                                _tg b;
                                                                _vektor3<_tg> s;
                                                                //_tg gamma[2];
                                                                _vektor3<_tg> lot;
                                                                bool eever[2];
                                                                bool hitep;
                                                                bool hitee;
                                                                bool innen;
                                                                int i;
                                                                _tg dis;
                                                                //---------------------------------
                                                                if(dbscreen) dbscreen->schreiben("void determineintersectionparallel()",pdbcolfunc);
                                                                V3.lotpunktebene(ee->vertex(0)->ort(),pp->mitte(),pp->normale(),lot,a);
                                                                if((a>=-nahenull)&&(a<=nahenull)){//---------------------------------koplamarität
                                                                 eever[0]=false;
                                                                 eever[1]=false;
                                                                 //alles wird ins 2D übertragen und pe-objekt werden relativ zu netz von pp betrachtet
                                                                 c0=pp->groessterindex(0);
                                                                 c1=pp->groessterindex(1);
                                                                 c2=pp->groessterindex(2);
                                                                 pev0.setzen(ee->vertex(0)->ort()[c0],ee->vertex(0)->ort()[c1]);
                                                                 //pev0.setzen(
                                                                 //((ee->vertex(0)->holen(c0)+ pe->netz()->holen(c0)))- pp->netz()->holen(c0),
                                                                 //((ee->vertex(0)->holen(c1)+ pe->netz()->holen(c1)))- pp->netz()->holen(c1));
                                                                 //pev0[0]=ee->vertex[0]->ort[c0]-pp->netz->ort->o[c0];
                                                                 //pev0[1]=ee->vertex[0]->ort[c1]-pp->netz->ort->o[c1];
                                                                 pev1.setzen(ee->vertex(1)->ort()[c0],ee->vertex(1)->ort()[c1]);
                                                                 //pev1.setzen(
                                                                 //(ee->vertex(1)->holen(c0)+(*pe->netz())[c0])-(*pp->netz())[c0],
                                                                 //(ee->vertex(1)->holen(c1)+(*pe->netz())[c1])-(*pp->netz())[c1]);
                                                                 //pev1[0]=ee->vertex[1]->ort[c0]-pp->netz->ort->o[c0];
                                                                 //pev1[1]=ee->vertex[1]->ort[c1]-pp->netz->ort->o[c1];
                                                                 peve=pev1-pev0;
                                                                 if(pp->kanten()->anfang(pit))do{//----------------------------pp - kanten iterieren
                                                                  ep=pit->objekt();
                                                                  ep->alpha(0);
                                                                  ep->betareal(0);
                                                                  ep->parallel(0);
                                                                  ppv0.setzen((ep->vertex(0)->ort())[c0],(ep->vertex(0)->ort())[c1]);
                                                                  ppv1.setzen((ep->vertex(1)->ort())[c0],(ep->vertex(1)->ort())[c1]);
                                                                  ppve=ppv1-ppv0;
                                                                  de2=pev0-ppv0;
                                                                  da2=peve;
                                                                  da2*=-1;
                                                                  db2=ppve;
                                                                  D=V2.determinieren(da2,db2);
                                                                  if(fabs(D)>nahenull){
                                                                   //es liegen schiefe geraden vor , 
                                                                   //untersuchen, ob die schnittpunkt 
                                                                   //unscharf innerhalb der kanten liegen
                                                                   a=V2.determinieren(de2,db2)/D;
                                                                   b=V2.determinieren(da2,de2)/D;
                                                                   ep->alpha(a);
                                                                   ep->betareal(0);
                                                                   hitep=false;
                                                                   hitee=false;
                                                                   s=ee->vektor();//bewegen(ee->vektor,s);
                                                                   s*=a;//mul(a,s);
                                                                   s+=ee->vertex(0)->ort();//add(ee->vertex[0]->o,s);
                                                                   //s+=*pe->netz();//add(pe->netz->ort->o,s);
                                                                   if((b>=0)&&(b<=1)){
                                                                    hitep=true;
                                                                   }else{
                                                                    getdistance(s,ep->ort(0),dis);
                                                                    if(dis<=nahenull) hitep=true;
                                                                    getdistance(s,ep->ort(1),dis);
                                                                    if(dis<=nahenull) hitep=true;
                                                                   };
                                                                   if(hitep){
                                                                    ep->betareal(1);
                                                                    if((a>=0)&&(a<=1)) hitee=true;
                                                                    getdistance(s,ee->ort(0),dis);
                                                                    if(dis<=nahenull) {
                                                                     hitee=true;
                                                                     eever[0]=true;
                                                                    };
                                                                    getdistance(s,ee->ort(1),dis);
                                                                    if(dis<=nahenull){
                                                                     hitee=true;
                                                                     eever[1]=true;
                                                                    };
                                                                    if(hitee){
                                                                     createintersection(pp,pe,ee,s,a);
                                                                    };
                                                                   };
                                                                  }else{
                                                                   //determinante ist nahe null.
                                                                   //es liegen parallele vektoren vor, 
                                                                   //es können 0-2 intersektion auftreten
                                                                   ep->parallel(1);
                                                                   V3.lotpunktgerade(ep->ort(0),ee->ort(0),ee->vektor(),lot);
                                                                   //V3.lotpunktgerade(ep->vertex[0]->ort,ee->vertex[0]->ort,ee->vektor,u);
                                                                   //überprüfen ob die geraden dieser beiden vektoren aufeinanderligen (kolinearität)
                                                                   if(lot.laenge()<=nahenull){
                                                                    ainner=0;
                                                                    binner=0;
                                                                    //1.liegt vertex0 von ep auf pe-kante ?
                                                                    getlineparameter(ep->ort(0),ee->ort(0),ee->vektor(),a);
                                                                    hitee=false;
                                                                    if((a>=0)&&(a<=1)){
                                                                     hitee=true;
                                                                    }else{
                                                                     getdistance(ep->ort(0),ee->ort(0),dis);
                                                                     if(dis<=nahenull) hitee=true;
                                                                     getdistance(ep->ort(0),ee->ort(1),dis);
                                                                     if(dis<=nahenull) hitee=true;
                                                                    };
                                                                    if(hitee){
                                                                     s=ep->ort(0);
                                                                     ainner=1;
                                                                     createintersection(pp,pe,ee,s,a);
                                                                    };
                                                                    //2.liegt vertex1 von ep auf pe-kante ?
                                                                    getlineparameter(ep->ort(1),ee->ort(0),ee->vektor(),b);
                                                                    hitee=false;
                                                                    if((b>=0)&&(b<=1)){
                                                                     hitee=true;
                                                                    }else{
                                                                     getdistance(ep->ort(1),ee->ort(0),dis);
                                                                     if(dis<=nahenull) hitee=true;
                                                                     getdistance(ep->ort(1),ee->ort(1),dis);
                                                                     if(dis<=nahenull) hitee=true;
                                                                    };
                                                                    if(hitee){
                                                                     s=ep->ort(1);
                                                                     binner=1;
                                                                     createintersection(pp,pe,ee,s,b);
                                                                    };
                                                                    //3.wenn ainnen und nicht binnen dann muss einer der ee-vertices referenziert werden
                                                                    if((ainner==1)&&(binner==0)){
                                                                     if(b>0.5){
                                                                      s=ee->ort(1);
                                                                      createintersection(pp,pe,ee,s,a);
                                                                      eever[1]=true;
                                                                     }else{
                                                                      s=ee->ort(0);
                                                                      createintersection(pp,pe,ee,s,a);
                                                                      eever[0]=true;
                                                                     };
                                                                    };
                                                                    //4.wenn nicht ainnen und binnen dann muss einer der ee-vertices referenziert werden
                                                                    if((ainner==0)&&(binner==1)){
                                                                     if(a>0.5){
                                                                      s=ee->ort(1);
                                                                      createintersection(pp,pe,ee,s,a);
                                                                      eever[1]=true;
                                                                     }else{
                                                                      s=ee->ort(0);
                                                                      createintersection(pp,pe,ee,s,a);
                                                                      eever[0]=true;
                                                                     };
                                                                    };
                                                                    //5.wenn ep-vertices beide ausserhalb liegen und ee sich 
                                                                    //innerhalb von ep befindet , dann
                                                                    //beide ee-vertices referenzieren
                                                                    if((ainner==0)&&(binner==0)){
                                                                     if(((a<0.5)&&(b>0.5))||((b<0.5))&&((a>0.5))){
                                                                      s=ee->ort(0);
                                                                      createintersection(pp,pe,ee,s,a);
                                                                      eever[0]=true;
                                                                      s=ee->ort(1);
                                                                      createintersection(pp,pe,ee,s,a);
                                                                      eever[1]=true;
                                                                     };
                                                                    };
                                                                   };//lotpunktgerade
                                                                  };//parallelität
                                                                 }while(pp->kanten()->naechstes(pit));
                                                                 //nun untersuchen, ob ee sich komplett innhalb von p befindet
                                                                 //explizite ee->vertex[0] überprüfung, 
                                                                 //je nachdem ob eever0 und / oder eever1 false sind, müssen
                                                                 //sie noch als intersektion eingefügt werden
                                                                 for(i=0;i<2;i++){
                                                                  if(eever[i]==false){
                                                                   innen=true;
                                                                   if(pp->kanten()->anfang(pit))do{
                                                                     de=ee->ort(i)-pit->objekt()->ort(0);
                                                                     da=pit->objekt()->vektor();
                                                                     da.normalisieren();
                                                                     db=pp->mitte()-pit->objekt()->ort(0);
                                                                     db.normalisieren();
                                                                     db2.setzen(db[c0],db[c1]);
                                                                     da2.setzen(da[c0],da[c1]);
                                                                     de2.setzen(de[c0],de[c1]);
                                                                     D=V2.determinieren(da2,db2);
                                                                     if(D){
                                                                      b=V2.determinieren(da2,de2)/D;
                                                                      if(b<-nahenull) innen=false;
                                                                     }else{
                                                                      fehler("_modifikationnetzintersektion::determineintersectionparallel()","2D - Hauptdeterminente dD ==0");
                                                                     };
                                                                   }while((pp->kanten()->naechstes(pit))&&(innen==true));
                                                                   if(innen==true){
                                                                    createintersection(pp,pe,ee,ee->ort(i),0);
                                                                   };
                                                                  };
                                                                 };

                                         
                                         
                                         
                                                                 //betareal[n] muss 1 sein; alphaparallel[n] muss 0 sein
                                                                 /*p=0;
                                                                 if(pp->kanten()->anfang(pit))do{
                                                                  if((pit->objekt()->parallel()==0)&&(pit->objekt()->betareal()!=0)){
                                                                   a=pit->objekt()->alpha();
                                                                   if(p==0){
                                                                    gamma[p++]=a;
                                                                   }else{
                                                                    if(p<2){
                                                                     if(a!=gamma[p-1]){
                                                                      gamma[p++]=a;
                                                                     };
                                                                    };
                                                                   };
                                                                  };
                                                                 }while(pp->kanten()->naechstes(pit));
                                                                 if(p==2){
                                                                  if(((gamma[0]<0)&&(gamma[1]>0))||((gamma[0]>0)&&(gamma[1]<0))){
                                                                   s=ee->ort(0);//bewegen(ee->vertex[0]->ort,s);
                                                                   createintersection(pp,pe,ee,s,0);
                                                                  };
                                                                  if(((gamma[0]<1)&&(gamma[1]>1))||((gamma[0]>1)&&(gamma[1]<1))){ 
                                                                   s=ee->ort(1);//bewegen(ee->vertex[1]->ort,s);
                                                                   createintersection(pp,pe,ee,s,1);
                                                                  };
                                                                 }else{
                                                                  if(p==1){
                                                                   fehler("void _modifikationnetzintersektion::determineintersectionparallel(_polygon*pp,_polygon*pe,_kantepolygon*ee)","anzahl der kollisionspunkte ist 1 (p==1).");
                                                                  };
                                                                 };*/
                                                                 
                                                                 
                                                                 
                                                                 
                                                                };//koplanarität (hessesche normalform)
};

void _modifikationnetzintersektion::completeintersection(_polygon*p){
                                                                //hier prüfen, ob dreieck d eine intersektion i referenziert, wobei das dabei ref. causaldreieck
                                                                //ebenfalls eine i-ref. introconnector auf d hat , also:
                                                                //für d gilt : ic(d)->(i,causaldreieck)
                                                                //für cd muss gelten : ic(cd)->(i,d);
                                                                _listenknoten<_kantepolygon >*pit;
                                                                _vertex*vit;
                                                                _listenknoten<_vertex>*lnvit;
                                                                //---------
                                                                iterierenliste(p,lnvit,
                                                                 vit=lnvit->objekt(); 
                                                                 if(vit->markierung()==0){   
                                                                  completeintersection(p,0,vit,vit->verbinderisintroliste());
                                                                  vit->markierung(1);
                                                                 };
                                                                );
                                                                if(p->kanten()->anfang(pit))do{
                                                                 if(pit->objekt()->markierung()==0){
                                                                  completeintersection(p,pit->objekt(),0,pit->objekt()->verbinderisintroliste());
                                                                  pit->objekt()->markierung(1);
                                                                 };
                                                                }while(p->kanten()->naechstes(pit));
};

void _modifikationnetzintersektion::completeintersection(_polygon*p,_kantepolygon*e,_vertex*v,_listebasis<_verbinderisintro >*isic){
                                                                _verbinderisintro*iit;
                                                                _intersektion*i;
                                                                _polygon*cp;
                                                                _listenknoten<_polygon>*lnp;
                                                                _verbindervertexpolygon*vcp;
                                                                //--------------------
                                                                if(isic->anfang(iit))do{
                                                                 cp=iit->causalpolygon();
                                                                 i=iit->intersektion();
                                                                 if(searchintersection(cp,i,p)==0){
                                                                  if(e){
                                                                   createisintroconnector(iit->causalpolygon(),iit->intersektion(),e->polygon(0),0.5);
                                                                   createisintroconnector(iit->causalpolygon(),iit->intersektion(),e->polygon(1),0.5);
                                                                  };
                                                                  if(v){
                                                                   iterierenliste(v,lnp,//if(v->anfang(vcp))do{
                                                                    vcp=static_cast<_verbindervertexpolygon*>(lnp);
                                                                    createisintroconnector(iit->causalpolygon(),iit->intersektion(),vcp->polygon(),0.5);
                                                                   );
                                                                  };
                                                                 };
                                                                }while(isic->naechstes(iit));
};

void _modifikationnetzintersektion::createintersection(_polygon*pp,_polygon*pe,_kantepolygon*e,_vektor3<_tg> s,_tg c){
                                                                //_tgingpoint unschärfe kompensation für vertex-kante-polygon-intersektion
                                                                //führt eine Betrachtung der alpha-parameter aus unter berücksichtigung
                                                                //der nahenull-konstante
                                                                //für die übergebene kante e wird in jedem fall ein introconnector angelegt,
                                                                //die frage ist, ob das übergebene causaldreieck cd bereits eine vorhandene
                                                                //intersektion zur verfügung stellt, die im nahenull! radius der koordinate
                                                                // o steht; wenn nicht so legt diese funktion auch die notwendige intersektion an
                                                                // desweiteren muss die funktion entscheiden, ob der introconnector
                                                                _intersektion*intersektion;
                                                                _verbinderisintro*ic;
                                                                _kantepolygon*ce;
                                                                _vertex*cv;
                                                                _kantepolygon*kante;
                                                                _vertex*vertex;
                                                                _tg distance;
                                                                char fremdintersection;
                                                                _vertex*v0;
                                                                _vertex*v1;
                                                                _vektor3<_tg> vo0;
                                                                _vektor3<_tg> vo1;
                                                                _vertex*vit;
                                                                _verbindervertexpolygon*vcit;
                                                                _listenknoten<_kantepolygon >*pit;
                                                                _verbinderisintro*isic;
                                                                //-----------------------------------------------
                                                                v0=e->vertex(0);
                                                                v1=e->vertex(1);
                                                                vo0=e->ort(0);
                                                                vo1=e->ort(1);
                                                                vertex=0;
                                                                kante=0;
                                                                cv=0;
                                                                ce=0;
                                                                intersektion=0;
                                                                fremdintersection=0;
                                                                ic=0;
                                                                //----------------------------------------------- EIGENKOMPENSATION -----------------------------------------------------
                                                                //den inhalt des laut alpha in frage kommenden vertex untersuchen und ggf kompensieren, intersektion ist immer vorhanden
                                                                if(getdistance(s,vo0,distance))/*if(a<=nahenull)*/{
                                                                 //****** DEBUG *******
                                                                 if(plog) schreiben("_modifikationnetzintersektion::createintersection : a<nahenull -> vertex0 - kompensation!");
                                                                 //if(dbscreen) dbscreen->schreiben("createintersection : a<nahenull -> vertex0 - kompensation!",pdbcolnote);
                                                                 //********************
                                                                 kante=0;
                                                                 vertex=v0;
                                                                 if(v0->verbinderisintroliste()->anfang(isic)){
                                                                  intersektion=isic->intersektion();//v0->firstisintroconnector->intersektion;
                                                                 };
                                                                }else
                                                                if(getdistance(s,vo1,distance))/*if(a>(1-nahenull))*/{
                                                                 //****** DEBUG *******
                                                                 if(plog) schreiben("_modifikationnetzintersektion::createintersection : a>1-nahenull -> vertex1 - kompensation!");
                                                                 //if(dbscreen) dbscreen->schreiben("createintersection : a>1-nahenull -> vertex1 - kompensation!",pdbcolnote);
                                                                 //********************
                                                                 kante=0;
                                                                 vertex=v1;
                                                                 if(v1->verbinderisintroliste()->anfang(isic)){
                                                                  intersektion=isic->intersektion();//v1->firstisintroconnector->intersektion;
                                                                 };
                                                                }else{//intersektion kann evtl. (für pe) edgereferenziert sein
                                                                 kante=e;
                                                                 vertex=0;
                                                                 //vorh. intersektion suchen : den inhalt der primär schneidenden kante untersuchen und ggf kompensieren, hier sortierung beachten
                                                                 if(e->verbinderisintroliste()->anfang(ic))do{
                                                                  if(getdistance(s,ic->intersektion()->ort(),distance))/*if(fabs(ic->alpha-a)<nahenull)*/ {
                                                                   //****** DEBUG *******
                                                                   if(plog) schreiben("_modifikationnetzintersektion::createintersection : |i->a-a|<nahenull -> kante - kompensation!");       
                                                                   //if(dbscreen) dbscreen->schreiben("createintersection : |i->a-a|<nahenull -> kante - kompensation!",pdbcolnote);       
                                                                   //********************
                                                                   intersektion=ic->intersektion();
                                                                   kante=e;
                                                                   vertex=0;
                                                                  };
                                                                 }while((e->verbinderisintroliste()->naechstes(ic))&&(intersektion==0));
                                                                };
                                                                //--------------------------------------------- FREMDKOMPENSATION -------------------------------------------------------
                                                                //vorh. intersektion suchen : zunächst in othervertices
                                                                //vit=pp->vertex();
                                                                //if(vit)do{
                                                                _listenknoten<_vertex>*lnv;
                                                                if(pp->anfang(lnv))do{
                                                                 vit=lnv->objekt();
                                                                 if(getdistance(s,vit->ort(),distance)) {
                                                                  cv=vit;
                                                                  if(cv->verbinderisintroliste()->anfang(isic)){
                                                                   if(intersektion==0)intersektion=isic->intersektion();
                                                                  };
                                                                  fremdintersection=1;
                                                                 };
                                                                 //vit=vit->naechstes(pp);
                                                                }while((pp->naechstes(lnv))&&(fremdintersection==0));
                                                                //---------------vorh. intersektion suchen : ansonsten in otheredges
                                                                if(cv==0){
                                                                 if(pp->kanten()->anfang(pit))do{
                                                                  ce=pit->objekt();
                                                                  if(ce->verbinderisintroliste()->anfang(ic))do{
                                                                   if(getdistance(s,ic->intersektion()->ort(),distance)) {
                                                                    if(intersektion==0) intersektion=ic->intersektion();
                                                                    fremdintersection=1;
                                                                   };
                                                                  }while((ce->verbinderisintroliste()->naechstes(ic))&&(fremdintersection==0));
                                                                 }while((pp->kanten()->naechstes(pit))&&(fremdintersection==0));
                                                                };
                                                                //-----------------------------------------------------------------------------------------------------------------------
                                                                if((kante==0)&&(vertex==0)) {
                                                                 fehler("_modifikationnetzintersektion::createintersection()","kante && vertex sind beide null; keine primär-referenzierung möglich");
                                                                 if(dbscreen) dbscreen->schreiben("createintersection() : kante und vertex sind beide null; keine primär-referenzierung möglich",pdbcolerror);
                                                                };
                                                                if(intersektion==0){
                                                                 intersektion=new _intersektion(s);
                                                                 //************ DEBUG ***********
                                                                 //intersektion->visualisieren();
                                                                 //debuganimwait();
                                                                 //******************************
                                                                };
                                                                if(kante){
                                                                 createisintroconnector(kante,intersektion,pp,c);
                                                                 kante->polygon(0)->status(0);
                                                                 kante->polygon(1)->status(0);
                                                                }else
                                                                if(vertex){
                                                                 createisintroconnector(vertex,intersektion,pp,c);
                                                                 _listenknoten<_polygon>*lnp;
                                                                 iterierenliste(vertex,lnp,
                                                                 //if(vertex->anfang(vcit))do{
                                                                  vcit=static_cast<_verbindervertexpolygon*>(lnp);
                                                                  vcit->polygon()->status(0);
                                                                 //}while(vertex->naechstes(vcit));
                                                                 );
                                                                };
                                                                nointersection=0;
                                                                pp->status(0);
};

char _modifikationnetzintersektion::createisintroconnector(_vertex*vertex,_intersektion*intersektion,_polygon*causalpoly,_tg a){
                                                                char r;
                                                                //---------
                                                                r=isintroconnectorexists(intersektion,causalpoly,vertex->verbinderisintroliste());
                                                                if(r==0){
                                                                 new _verbinderisintro(vertex,intersektion,causalpoly,0,0,a);
                                                                };
                                                                return(r);
};

char _modifikationnetzintersektion::createisintroconnector(_kantepolygon*kante,_intersektion*intersektion,_polygon*causalpoly,_tg a){
                                                                char r;
                                                                //---------
                                                                r=isintroconnectorexists(intersektion,causalpoly,kante->verbinderisintroliste());
                                                                if(r==0){
                                                                 new _verbinderisintro(kante,intersektion,causalpoly,0,0,a);
                                                                };
                                                                return(r);
};

char _modifikationnetzintersektion::createisintroconnector(_polygon*poly,_intersektion*intersektion,_polygon*causalpoly,_tg a){
                                                                char r;
                                                                //---------
                                                                r=isintroconnectorexists(intersektion,causalpoly,poly->verbinderisintroliste());
                                                                if(r==0){
                                                                 new _verbinderisintro(poly,intersektion,causalpoly,0,0,a);
                                                                };
                                                                return(r);
};

char _modifikationnetzintersektion::isintroconnectorexists(_intersektion*intersektion,_polygon*causalpoly,_listebasis<_verbinderisintro >*isic){
                                                                //sucht in der firstisic-liste den eintrag, dessen die intersektion==intersektion
                                                                //und dessen causalpoly==causalpoly ist
                                                                char r;
                                                                _verbinderisintro*it; 
                                                                //---------
                                                                r=0;
                                                                if(isic->anfang(it))do{
                                                                 if((intersektion==it->intersektion())&&(causalpoly==it->causalpolygon())) r=1;
                                                                }while((isic->naechstes(it))&&(r==0));
                                                                return(r);
};

void _modifikationnetzintersektion::getlineparameter(const _vektor3<_tg>&p,const _vektor3<_tg>&o,const _vektor3<_tg>&v,_tg&a){
                                                                int ct;
                                                                //-------------
                                                                ct=v.groessterindex();
                                                                a=(p[ct]-o[ct])/v[ct];
};
void _modifikationnetzintersektion::getlineparameter2d(const _vektor2<_tg>&p,const _vektor2<_tg>&o,const _vektor2<_tg>&v,_tg&a){
                                                                int ct;
                                                                //-------------
                                                                ct=v.groessterindex();
                                                                a=(p[ct]-o[ct])/v[ct];
};

void _modifikationnetzintersektion::getlotpointline2d(_vektor2<_tg>&x,_vektor2<_tg>&o,_vektor2<_tg>&a,_vektor2<_tg>&e){
                                                                V2.lotpunktgerade(x,o,a,e);
};

char _modifikationnetzintersektion::searchintersection(_polygon*cp,_intersektion*is,_polygon*anderes){
                                                                //eine intersektion is in cp suchen, die auch von anderes referenziert wird
                                                                char r;
                                                                _listenknoten<_kantepolygon >*pit;
                                                                _vertex*vit;
                                                                _listenknoten<_vertex>*lnv;
                                                                //-------------
                                                                r=isintroconnectorexists(is,anderes,cp->verbinderisintroliste());
                                                                if(r==0){
                                                                 if(cp->kanten()->anfang(pit))do{
                                                                  r=isintroconnectorexists(is,anderes,pit->objekt()->verbinderisintroliste());
                                                                 }while((r==0)&&(cp->kanten()->naechstes(pit)));
                                                                 if(r==0){
                                                                  //vit=cp->vertex();
                                                                  //if(vit)do{
                                                                  if(cp->anfang(lnv))do{
                                                                   vit=lnv->objekt();
                                                                   r=isintroconnectorexists(is,anderes,vit->verbinderisintroliste());
                                                                   //vit=vit->naechstes(cp);
                                                                  }while((cp->naechstes(lnv))&&(r==0));
                                                                 };
                                                                };
                                                                return(r);
};

char _modifikationnetzintersektion::getdistance(const _vektor3<_tg>&o0,const _vektor3<_tg>&o1,_tg&d){
                                                                char r;
                                                                _vektor3<_tg> v;
                                                                //-----------
                                                                r=0;
                                                                v=o0-o1;
                                                                d=v.laenge();
                                                                if(d<=nahenull) r=1;
                                                                return(r);
};

void _modifikationnetzintersektion::clearintersection(_netz*m){
                                                                _polygon*p;
                                                                _listenknoten<_vertex>*lnvit;
                                                                _listenknoten<_kantepolygon >*pit;
                                                                //-------------
                                                                iterierenliste(m,p,
                                                                 clearisintroconnectors(p->verbinderisintroliste());
                                                                 //vit=p->vertex();
                                                                 //if(vit)do{
                                                                 iterierenliste(p,lnvit,clearisintroconnectors(lnvit->objekt()->verbinderisintroliste()));   
                                                                 // vit=vit->naechstes(p);
                                                                 //}while(vit!=p->vertex());
                                                                 if(p->kanten()->anfang(pit))do{
                                                                  clearisintroconnectors(pit->objekt()->verbinderisintroliste());
                                                                 }while(p->kanten()->naechstes(pit));
                                                                );
};

void _modifikationnetzintersektion::clearisintroconnectors(_listebasis<_verbinderisintro >*isic){
                                                                _verbinderisintro*iit;
                                                                _verbinderisextro*eit;
                                                                _intersektion*intersektion;
                                                                //-------------------
                                                                while(isic->anfang(iit)){
                                                                 //iit=firstisic;
                                                                 intersektion=iit->intersektion();
                                                                 if(intersektion->anfang(eit))do{
                                                                  eit->clearisintroconnector();
                                                                  //if(eit->isintroconnector()){
                                                                  // delete eit->isintroconnector();
                                                                  // eit->nullisintroconnector();
                                                                  //};
                                                                 }while(intersektion->naechstes(eit));
                                                                 //clear_ring(intersektion->firstisextroconnector);
                                                                 if(intersektion){
                                                                  delete intersektion;
                                                                  intersektion=0;
                                                                 };
                                                                };
};
//*********************************************************************  V I R T U A L I N T E R S E C T I O N G E N E R A T I O N  ********************************************************************************************

void _modifikationnetzintersektion::createvertexintersections(_netz*m,_polygon*p){
                                                                //wichtige funktion, die das isintroconnector-intersektion-isextroconnector-struct für jeden Vertex
                                                                //generiert
                                                                _listenknoten<_vertex>*v;
                                                                iterierenliste(p,v,v->objekt()->erzeugenintersektionsverbinder(m,p));
};
void _modifikationnetzintersektion::clearvertexintersections(_polygon*p){
                                                                _listenknoten<_vertex>*v;
                                                                iterierenliste(p,v,v->objekt()->loeschenintersektionsverbinder());
};
void _modifikationnetzintersektion::initintersectionvertices(_netz*m){
                                                                //funktion gilt für das meshtointersect
                                                                //alle polygoneckpunkte des meshes durchiterieren und
                                                                //die im falle einer reelen vertex-intersektion, über introconnectoren
                                                                //zugriff auf die intersektion bekommen und deren vertex-zeiger setzen
                                                                _polygon*p;
                                                                _vertex*vit;
                                                                _listenknoten<_vertex>*lnvit;
                                                                _intersektion*is;
                                                                _verbinderisintro*isic;
                                                                //-------------------
                                                                iterierenliste(m,p,
                                                                 if(p->status()==0){
                                                                  //vit=p->vertex();
                                                                  //if(vit)do{
                                                                  iterierenliste(p,lnvit,
                                                                   vit=lnvit->objekt();
                                                                   //isic=vit->firstisintroconnector;
                                                                   if(vit->verbinderisintroliste()->anfang(isic)){
                                                                    is=isic->intersektion();
                                                                    is->vertex=vit;
                                                                   };
                                                                   //vit=vit->naechstes(p);
                                                                  );
                                                                 };
                                                                );
};
//*************************************************************************  I N T E R S E C T I O N R I N G P R E P A R E  ****************************************************************************************************

void _modifikationnetzintersektion::invertisintroconnectorrings(_polygon*p){
                                                                //synchroniteration von kanten und vertices in poly p
                                                                //untersucht, ob vit==kante->vertex[0] wenn nicht dann muss invertiert werden
                                                                _kantepolygon*kante;
                                                                _listenknoten<_kantepolygon >*pit;
                                                                _vertex*vit;
                                                                //----------------
                                                                vit=p->vertex();
                                                                if(p->kanten()->anfang(pit))do{
                                                                 kante=pit->objekt();
                                                                 if(vit==kante->vertex(1)){
                                                                  kante->invertieren();
                                                                 };
                                                                 vit=vit->verbinder(p)->naechstervertex();
                                                                }while(p->kanten()->naechstes(pit));
};

void _modifikationnetzintersektion::formvertexintersectionring(_polygon*p){
                                                                //funktion integriert den verterx-intersektion-ring (ohne dabei kante-intersektion zu integrieren)
                                                                //dieser funktion folgt das integrierenn der kante-intersectionringe
                                                                int k;
                                                                _verbinderisintro*isic;
                                                                _intersektion*intersektion[2];
                                                                _listenknoten<_kantepolygon >*pit;
                                                                _listenknoten<_kantepolygon >*pin;
                                                                _kantepolygon*e[2];
                                                                //----------------
                                                                if(p->kanten()->anfang(pit))do{
                                                                 pin=pit->naechstes();
                                                                 e[0]=pit->objekt();
                                                                 e[1]=pin->objekt();
                                                                 for(k=0;k<2;k++){
                                                                  if(e[k]->vertex(0)->verbinderisintroliste()->anfang(isic)){
                                                                   intersektion[k]=isic->intersektion();
                                                                  }else{
                                                                   if(e[k]->vertex(0)->intersektion()){
                                                                    intersektion[k]=e[k]->vertex(0)->intersektion();
                                                                   }else{
                                                                    fehler("_modifikationnetzintersektion::formvertexintersectionring : ERROR : keine virtuelle vertex-intersektion vorhanden an pi-polygon.");
                                                                    if(dbscreen) dbscreen->schreiben("formvertexintersectionring : ERROR : keine virtuelle vertex-intersektion vorhanden an pi-polygon.",pdbcolerror);
                                                                   };
                                                                  };
                                                                 };
                                                                 intersektion[0]->naechstes(intersektion[1]);
                                                                 intersektion[1]->vorheriges(intersektion[0]);
                                                                }while(p->kanten()->naechstes(pit));
};

void _modifikationnetzintersektion::integrateintersectionrings(_polygon*p){
                                                                //funktion berhandelt die kanten in der weise, dass von der kante referenzierte intersektion
                                                                //zu einem ring zusammengeschlossen werden, damit dieser päter mit den vbertex intersectionring
                                                                //vereinige werden kann
                                                                _listenknoten<_kantepolygon >*pit;
                                                                _verbinderisintro*ic;
                                                                _intersektion*in;
                                                                _intersektion*ip;
                                                                _verbinderisintro*icit;
                                                                _kantepolygon*e;
                                                                //-------------------
                                                                //1.alle intersectionflags nullen 
                                                                if(p->kanten()->anfang(pit))do{
                                                                 flagintersection(pit->objekt()->verbinderisintroliste(),0);
                                                                }while(p->kanten()->naechstes(pit));
                                                                //2.alle isintroconnectoren iterieren und für deren intersections die vorheriges naechstes zeiger setzen
                                                                if(p->kanten()->anfang(pit))do{
                                                                 e=pit->objekt();
                                                                 if(e->verbinderisintroliste()->anfang(ic))do{
                                                                  if(ic->intersektion()->markierung==0){
                                                                   //naechstes zeiger bestimmen
                                                                   icit=ic;
                                                                   do{
                                                                    in=icit->intersektion();    
                                                                    icit=icit->naechstes();    
                                                                   }while((icit!=ic)&&(in==ic->intersektion()));
                                                                   //vorheriges zeiger bestimmen
                                                                   icit=ic;
                                                                   do{
                                                                    ip=icit->intersektion();
                                                                    icit=icit->vorheriges();
                                                                   }while((icit!=ic)&&(ip==ic->intersektion()));
                                                                   //zeiger verbigen
                                                                   ic->intersektion()->vorheriges(ip);
                                                                   ic->intersektion()->naechstes(in);
                                                                   //ic->markierung(1);
                                                                  };
                                                                 }while(e->verbinderisintroliste()->naechstes(ic));
                                                                }while(p->kanten()->naechstes(pit));
                                                                
};

void _modifikationnetzintersektion::uniteintersectionrings(_polygon*p){
                                                                //vereinen von kante- und vertex-intersectionringen
                                                                _vertex*vertex;
                                                                _intersektion*intersektion;
                                                                _kantepolygon*kante;
                                                                _listenknoten<_kantepolygon >*pit;
                                                                _verbinderisintro*isic;
                                                                //-------------------
                                                                if(p->kanten()->anfang(pit))do{
                                                                 kante=pit->objekt();
                                                                 vertex=kante->vertex(1);
                                                                 if(kante->verbinderisintroliste()->anzahl()>0){
                                                                  if(vertex->verbinderisintroliste()->anfang(isic)){
                                                                   intersektion=isic->intersektion();
                                                                  }else{
                                                                   if(vertex->intersektion()){
                                                                    intersektion=vertex->intersektion();
                                                                   }else{
                                                                    fehler("_modifikationnetzintersektion::uniteintersectionrings : ERROR : keine virtuelle vertex-intersektion vorhanden an poly p.");   
                                                                    if(dbscreen) dbscreen->schreiben("uniteintersectionrings : ERROR : keine virtuelle vertex-intersektion vorhanden an poly p.",pdbcolerror);   
                                                                   };
                                                                  };
                                                                  kante->verbinderisintroliste()->anfang(isic);
                                                                  uniteintersectionrings(intersektion,isic->intersektion());
                                                                 };
                                                                }while(p->kanten()->naechstes(pit));
};

void _modifikationnetzintersektion::uniteintersectionrings(_intersektion*r0,_intersektion*r1){
                                                                _intersektion*r0p;
                                                                //-----------------
                                                                r0p=r0->vorheriges();
                                                                r0->vorheriges()->naechstes(r1);
                                                                r0->vorheriges(r1->vorheriges());
                                                                r1->vorheriges()->naechstes(r0);
                                                                r1->vorheriges(r0p);
};

void _modifikationnetzintersektion::flagintersection(_netz*m,int f){
                                                                _polygon*p;
                                                                //--------------------
                                                                if(m->anfang(p))do{
                                                                 flagintersection(p,f);
                                                                }while(m->naechstes(p));
};

void _modifikationnetzintersektion::flagintersection(_polygon*p,int f){
                                                                _vertex*vit;
                                                                _listenknoten<_vertex>*lnvit;
                                                                _listenknoten<_kantepolygon >*pit;
                                                                //-------------------
                                                                //vit=p->vertex();
                                                                //if(vit)do{
                                                                iterierenliste(p,lnvit,
                                                                 vit=lnvit->objekt();
                                                                 flagintersection(vit->verbinderisintroliste(),f);
                                                                 if(vit->intersektion()) vit->intersektion()->markierung=f;
                                                                // vit=vit->naechstes(p);
                                                                //}while(vit!=p->vertex());
                                                                );
                                                                if(p->kanten()->anfang(pit))do{
                                                                 flagintersection(pit->objekt()->verbinderisintroliste(),f);
                                                                }while(p->kanten()->naechstes(pit));
                                                                flagintersection(p->verbinderisintroliste(),f);
};

void _modifikationnetzintersektion::flagintersection(_listebasis<_verbinderisintro >*isic,int f){
                                                                _verbinderisintro*iit;
                                                                //-------------------
                                                                if(isic->anfang(iit))do{
                                                                 iit->intersektion()->markierung=f;
                                                                }while(isic->naechstes(iit));
};

//************************************************************************  S T A T U S C R O S S G E N E R A T I O N  *********************************************************************************************************

void _modifikationnetzintersektion::createstatuscrosses(_polygon*p){
                                                                //steuerfunnktion für statuscrossgeneration und statuscrossstatusdetermination
                                                                //wichtig : für alle virtuellen intersektion gilt die regel : ist eine reele intersektion
                                                                //über den intersectionring erreichbar, so kann der status hieraus direkt abgelesen werden,
                                                                //siehe createstatuscrosses(_intersektion*)
                                                                //alle d-relevanten intersektion abiterieren, und zu jeder die statuscrosses anlegen
                                                                _vertex*vit;
                                                                _listenknoten<_vertex>*lnvit;
                                                                _listenknoten<_kantepolygon >*pit;
                                                                //-------------------
                                                                //******** DEBUG ********
                                                                if(plog) L->schreiben("_modifikationnetzintersektion::createstatuscrosses(_polygon*)");
                                                                //if(dbscreen) dbscreen->schreiben("void createstatuscrosses(_polygon*)",pdbcolfunc);
                                                                //***********************
                                                                createstatuscrosses(p,p->verbinderisintroliste());
                                                                //vit=p->vertex();
                                                                //if(vit)do{
                                                                iterierenliste(p,lnvit,
                                                                 vit=lnvit->objekt();
                                                                 createstatuscrosses(p,vit->verbinderisintroliste());
                                                                // vit=vit->naechstes(p);
                                                                //}while(vit!=p->vertex());
                                                                );
                                                                if(p->kanten()->anfang(pit))do{
                                                                 createstatuscrosses(p,pit->objekt()->verbinderisintroliste());
                                                                }while(p->kanten()->naechstes(pit));

																//wenn virtuelle intersektionen vorliegen , dann statuskreuz 
																//mit extra überladung aufrüsten
																//vit=p->vertex();
                                                                //if(vit)do{
																iterierenliste(p,lnvit,
																 vit=lnvit->objekt();
																 if(vit->intersektion()) {
																  createstatuscrosses(p,vit->intersektion());
                                                                  if(plog) L->schreiben("Statussection für virtuelle Intersektion angelegt");
                                                                 };
                                                                );
                                                                // vit=vit->naechstes(p);
                                                                //}while(vit!=p->vertex());
};

void _modifikationnetzintersektion::createstatuscrosses(_polygon*p,_listebasis<_verbinderisintro >*isic){
                                                                _verbinderisintro*iit;
                                                                _statussektion*ss;
                                                                _statuskreuz*sc;
                                                                _statusrelevanz*srit;
                                                                _intersektion*is;
                                                                bool komplanar;
                                                                //----------------------
                                                                flagintersection(isic,0);
                                                                if(isic->anfang(iit))do{
                                                                 is=iit->intersektion();
                                                                 if(is->markierung==0){
                                                                  is->markierung=1;
                                                                  is->clearrelevance();
                                                                  is->getrelevance(this,p,isic);
                                                                  //***************** DEBUG : visulisierung der relevanzliste *****************
                                                                  //if(is->anfang(srit))do{
                                                                  // srit->visualisieren();
                                                                  //}while(is->naechstes(srit));
                                                                  //debuganimation();
                                                                  //if(is->anfang(srit))do{
                                                                  // srit->unvisualisieren();
                                                                  //}while(is->naechstes(srit));
                                                                  //***************************************************************************
                                                                  ss=new _statussektion(is,p);
                                                                  if(is->anfang(srit)){
                                                                   do{
                                                                   if(checkrightsided(p,
                                                                    srit->intersektion,
                                                                    is,
                                                                    srit->naechstes()->intersektion,
                                                                    srit->alpha,
                                                                    srit->naechstes()->alpha,
                                                                    srit->autorelevant,
                                                                    srit->naechstes()->autorelevant)
                                                                   ){
                                                                    //if((srit->intersektion->autorelevant==0)||(srit->naechstes()->intersektion->autorelevant==0)){
                                                                    //ein nicht vollständig oder überhaupt nicht autorelevantes statuscross muss angelegt werden
                                                                    if((srit->komplanar==srit->naechstes())
																	//||(srit->naechstes()->komplanar==srit)
																	) komplanar=true; else komplanar=false;
                                                                    // ******** DEBUG *******
                                                                    //if(dbscreen) dbscreen->schreiben("createstatuscross einer realen Intersektion.",pdbcolnote);
                                                                    // **********************
                                                                    sc=new _statuskreuz(
                                                                     this,
                                                                     ss,
                                                                     srit->intersektion,
                                                                     srit->naechstes()->intersektion,
                                                                     srit->alpha,
                                                                     srit->naechstes()->alpha,
                                                                     srit->causalpoly,
                                                                     komplanar
																	 //&srit->naechstes()->komplanar
																	 );
                                                                    // }else{
                                                                    //if(checkrightsided(p,srit->intersektion,is,srit->naechstes()->intersektion)){
                                                                    // sc=new _statuskreuz(this,ss,srit->intersektion,srit->naechstes()->intersektion,srit->causalpoly,srit->komplanar&srit->naechstes()->komplanar);
                                                                    // };
                                                                   };
                                                                   }while(is->naechstes(srit));
                                                                  }else{//null-relevance (kann nur in der polygonsebene liegen
                                                                   // ******** DEBUG *******
                                                                   //if(dbscreen) dbscreen->schreiben("createstatuscross mit null-relevanz einer realen Intersektion.",pdbcolnote);
                                                                   // **********************
                                                                   new _statuskreuz(this,ss,0,0,0,0,0,0);
                                                                  };
                                                                  is->clearrelevance();
                                                                 };
                                                                }while(isic->naechstes(iit));
};

char _modifikationnetzintersektion::checkrightsided(_polygon*p,_intersektion*i0,_intersektion*im,_intersektion*i1,_tg a0,_tg a1,bool ar0,bool ar1){
                                                                _vektor3<_tg> m;
                                                                _vektor3<_tg> n;
                                                                _tg malpha;
                                                               // _intersektion*i0;
                                                               // _intersektion*i1;
                                                                //--------
                                                              //  i0=s0->intersektion;
                                                              //  i1=s1->intersektion;
                                                                if((ar0)&&(ar1)){
                                                                 n=p->mitte()-im->ort();
                                                                 n.normalisieren();
                                                                 malpha=a0+deltaalpha(a0,a1)*0.5;
                                                                 V3.rotieren(p->normale(),p->ebene(0),malpha,m);
                                                                 m.normalisieren();
                                                                 //**************** DEBUG : visualisierung der vergleichsnormalen ****************
                                                                 //_weltdebugpfeil*an;
                                                                 //_weltdebugpfeil*am;
                                                                 //_weltdebugpfeil*a0;
                                                                 //_weltdebugpfeil*a1;
                                                                 //_vektor4<_to> col;
                                                                 //col.setzen(1,0,0,0);
                                                                 //an=new _weltdebugpfeil(W,p->mitte(),p->mitte()-n,0.05,0.05,col);
                                                                 //col.setzen(0,1,0,0);
                                                                 //am=new _weltdebugpfeil(W,im->ort(),im->ort()+m,0.05,0.05,col);
                                                                 //if(ar0) col.setzen(1,0.5,0.0,0); else col.setzen(0.5,0.5,0.5,0);
                                                                 //a0=new _weltdebugpfeil(W,im->ort(),i0->ort(),0.05,0.05,col);
                                                                 //if(ar1) col.setzen(1,0.5,0.0,0); else col.setzen(0.5,0.5,0.5,0);
                                                                 //a1=new _weltdebugpfeil(W,im->ort(),i1->ort(),0.05,0.05,col);
                                                                 //debuganimation();
                                                                 //delete an;
                                                                 //delete am;
                                                                 //delete a0;
                                                                 //delete a1;
                                                                 //*******************************************************************************
                                                                 n+=m;
                                                                 if(n.laenge()<sqrt(2.0f)){
                                                                  //peep(500);
                                                                  return(0);
                                                                 };
                                                                };
                                                                return(1);
};

void _modifikationnetzintersektion::createstatuscrosses(_polygon*p,_intersektion*intersektion){
                                                                //überladung für virtuelle intersektion
                                                                //hier muss untersucht wertden, ob im intersectionring eine reele intersektion auftritt,
                                                                //wenn ja, dann kann von dieser intersektion das für dieese partition entsprechende
                                                                //statuscross bestimmmmt werden (zeiger arithmetik), wenn nein, dann liegt eine virtuelle äussere
                                                                //ringsequenz vor, die mit einer oder mehreren inneren (isolierten) ringsequennzen später zu einer
                                                                //ringpartition verknüpft werden müssen. der status von solchen rein virtuellen ringsequenzen kann daher
                                                                //erst nach determineouterringpartition bestimmt werden (anhand des 2D-normalenvektors)
                                                                _statuskreuz*sc;
                                                                _statussektion*ss;
                                                                _tg ap,an;
                                                              //  _liste<_intersektion >*il;
                                                                //---------------------
                                                                //**** DEBUG ******
                                                                //schreiben("createstatuscross einer virtuellen Intersektion.");
                                                                //if(dbscreen) dbscreen->schreiben("createstatuscross einer virtuellen Intersection.",pdbcolnote);
                                                                //*****************
                                                                //il=new _liste<_intersektion >();
                                                                //il->einhaengen(intersektion->naechstes());
                                                                //il->einhaengen(intersektion->vorheriges());
                                                                //getintersectionalpha(p,intersektion,il);
                                                                ss=new _statussektion(intersektion,p);
                                                            //    if(deltaalpha(intersektion->vorheriges()->alpha,intersektion->naechstes()->alpha)>180){                                                                                  
                                                                //intersektion->vorheriges()->autorelevant=1;
                                                                //intersektion->naechstes()->autorelevant=1;
                                                                ap=p->berechnenalpha(intersektion->vorheriges()->ort()-intersektion->ort());
                                                                an=p->berechnenalpha(intersektion->naechstes()->ort()-intersektion->ort());
                                                                if(checkrightsided(
                                                                 p,
                                                                 intersektion->vorheriges(),
                                                                 intersektion,
                                                                 intersektion->naechstes(),
                                                                 ap, 
                                                                 an,
                                                                 true,true)
                                                                ){
                                                                 sc=new _statuskreuz(
                                                                 this,
                                                                 ss,
                                                                 intersektion->vorheriges(),
                                                                 intersektion->naechstes(),
                                                                 ap,
                                                                 an,
                                                                 0,
                                                                 0);
                                                                }else{
                                                                 //if(checkrightsided(p,intersektion->vorheriges(),intersektion,intersektion->naechstes())){
                                                                 
                                                            //    }else{
                                                                 sc=new _statuskreuz(
                                                                 this,
                                                                 ss,
                                                                 intersektion->naechstes(),
                                                                 intersektion->vorheriges(),
                                                                 an,
                                                                 ap,
                                                                 0,
                                                                 0);
                                                             //   };
                                                                 //};
                                                                };
                                                                sc->virtualintersection=1;
                                                             //   delete il;
};

void _modifikationnetzintersektion::clearstatuscrosses(_polygon*p){
                                                                _vertex*vit;
                                                                _listenknoten<_vertex>*lnvit;
                                                                _listenknoten<_kantepolygon >*pit;
                                                                //------------------
                                                                clearstatuscrosses(p->verbinderisintroliste());
                                                                //vit=p->vertex();
                                                                //if(vit)do{
                                                                iterierenliste(p,lnvit,
                                                                 vit=lnvit->objekt();
                                                                 clearstatuscrosses(vit->verbinderisintroliste());
																 if(vit->intersektion()){
															      //L->schreiben("Count statussection an virtueller intersektion:",(int)vit->intersektion()->_listebasis<_statussektion >::anzahl());
															      vit->intersektion()->_listebasis<_statussektion >::loeschen();
																 };
                                                                // vit=vit->naechstes(p);
                                                                //}while(vit!=p->vertex());
                                                                );
                                                                if(p->kanten()->anfang(pit))do{
                                                                 clearstatuscrosses(pit->objekt()->verbinderisintroliste());
                                                                }while(p->kanten()->naechstes(pit));
};

void _modifikationnetzintersektion::clearstatuscrosses(_listebasis<_verbinderisintro >*isic){
                                                                _verbinderisintro*iit;
                                                                //--------------------
                                                                flagintersection(isic,0);
                                                                if(isic->anfang(iit))do{
                                                                 if(iit->intersektion()->markierung==0){
                                                                  iit->intersektion()->markierung=1;
                                                                  iit->intersektion()->_listebasis<_statussektion >::loeschen();
                                                                 };
                                                                }while(isic->naechstes(iit));
};

void _modifikationnetzintersektion::getintersectionalpha(_polygon*p,_intersektion*intersektion,_liste<_intersektion >*il){
                                                                _intersektion*iit;
                                                                _listenknoten<_intersektion >*lit;
                                                                _vektor3<_tg> v;
                                                                //----------------
                                                                if(il->anfang(lit))do{
                                                                 iit=lit->objekt();
                                                                 v=iit->ort();
                                                                 v-=intersektion->ort();
                                                                 v.normalisieren();
                                                                 iit->alpha=p->berechnenalpha(v);
                                                                }while(il->naechstes(lit));
};

char _modifikationnetzintersektion::isintersectionreferenzed(_intersektion*i,_polygon*p,_listebasis<_verbinderisintro >*&liste){
                                                                char r;
                                                                _listenknoten<_kantepolygon >*pit;
                                                                _vertex*vit;
                                                                _listenknoten<_vertex>*lnvit;
                                                                //-----
                                                                liste=0;
                                                                r=0;
                                                                r=isintersectionreferenzed(i,p->verbinderisintroliste(),liste);
                                                                if(p->kanten()->anfang(pit))do{
                                                                 r|=isintersectionreferenzed(i,pit->objekt()->verbinderisintroliste(),liste);
                                                                }while((p->kanten()->naechstes(pit))&&(r==0));
                                                                if(r==0){
                                                                 //vit=p->vertex();
                                                                 //if(vit)do{
                                                                 if(p->anfang(lnvit))do{
                                                                  vit=lnvit->objekt();
                                                                  r|=isintersectionreferenzed(i,vit->verbinderisintroliste(),liste);
                                                                 // vit=vit->naechstes(p);
                                                                 }while((p->naechstes(lnvit))&&(r==0));
                                                                };
                                                                return(r);
};

char _modifikationnetzintersektion::isintersectionreferenzed(_intersektion*i,_listebasis<_verbinderisintro >*isic,_listebasis<_verbinderisintro >*&liste){
                                                                char r;
                                                                _verbinderisintro*iit;
                                                                //--------------------
                                                                liste=0;
                                                                r=0;
                                                                //iit=firstisic;
                                                                if(isic->anfang(iit))do{
                                                                 if(iit->intersektion()==i)r=1;//else iit=iit->naechstes;
                                                                }while((isic->naechstes(iit))&&(r==0));
                                                                if(r){
                                                                 liste=isic;//isic->anfang();//=firstisic;
                                                                };
                                                                return(r);
};
//********************************************************************************** P A R T I T I O N C R E A T E I T E R A T I O N *******************************************************************************************

char _modifikationnetzintersektion::createandcoverringpartition(_netz*m){
                                                                _polygon*p;
                                                                char r;
                                                                //--------------
                                                                //******** DEBUG *******
                                                                //L->schreiben("char _modifikationnetzintersektion::createandcoverringpartition(_netz*).");
                                                                //if(dbscreen) dbscreen->schreiben("char createandcoverringpartition(_netz*).",pdbcolfunc);
                                                                //**********************
                                                                
                                                                r=1;
                                                                if(m->anfang(p))do{
                                                                 if(p->status()==0) r=createandcoverringpartition(p);
                                                                }while((m->naechstes(p))&&(r==1));
                                                                return(r);
};

void _modifikationnetzintersektion::clearringpartition(_netz*m){
                                                                _polygon*p;
                                                                //--------------
                                                                if(m->anfang(p))do{
                                                                 p->ringpartitionsliste()->loeschen();
                                                                }while(m->naechstes(p));
};

char _modifikationnetzintersektion::createandcoverringpartition(_polygon*p){
                                                                _ringpartition*rit;
                                                                _vertex*vit;
                                                                _listenknoten<_vertex>*lnvit;
                                                                _listenknoten<_kantepolygon >*pit;//_pce*pit;
                                                                _listebasis<_ringpartition >*lp;
                                                                char r;
                                                                _liste<_polygon >*neuepoly;
                                                                //------------
                                                                //******** DEBUG *******
                                                                //_vektor4<_to> colp;
                                                                //colp.setzen(0,0,1,0);
                                                                //p->visualisieren(colp);
                                                                //debuganimwait();
                                                                //p->unvisualisieren();
                                                                //**********************
                                                                
                                                             
                                                                r=1;
                                                                //zuerst virtuelle intersektion iterieren, damit später bei statuscrossstatus-
                                                                //Initialisierung der virtuellen intersektion schneller iteriert werden kann
                                                                //vit=p->vertex();
                                                                //if(vit)do{
                                                                iterierenliste(p,lnvit,
                                                                 vit=lnvit->objekt();
                                                                 if(vit->intersektion()) createringpartition(p,vit->intersektion());
                                                                );
                                                                // vit=vit->naechstes(p);
                                                                //}while(vit!=p->vertex());
                                                                //dann ringpartitionssequenzen von polygonalen verwaltern
                                                                //aus starten, erst die der Polygonebene, dann die der Kanten
                                                                //und zum schluss die der Eckpunkte
                                                                createringpartition(p,p->verbinderisintroliste());
                                                                if(p->kanten()->anfang(pit))do{
                                                                 createringpartition(p,pit->objekt()->verbinderisintroliste());
                                                                }while(p->kanten()->naechstes(pit));
                                                                //vit=p->vertex();
                                                                //if(vit)do{
                                                                iterierenliste(p,lnvit,
                                                                 vit=lnvit->objekt();
                                                                 createringpartition(p,vit->verbinderisintroliste());
                                                                );
                                                                // vit=vit->naechstes(p);
                                                                //}while(vit!=p->vertex());
                                                                //jetzt müssen die rohen ringpartitionen aufbereitet werden,
                                                                //indem ihr Status bestimmt wird, was
                                                                //letztlich entscheidet, ob sie abgedeckt werden oder nicht
                                                                if(plog) schreiben("_modifikationnetzintersektion::determinevirtualpartitionstatus");
                                                                determinevirtualpartitionstatus(p);
                                                                if(plog) schreiben("_modifikationnetzintersektion::determinevirtualintersectionstatus");
                                                                determinevirtualintersectionstatus(p);
                                                                if(plog) schreiben("_modifikationnetzintersektion::clearnegativepartition");
                                                                clearnegativepartition(p);
                                                                //nun die surroundingringpartitiondetermination ausführen, 
                                                                //danach ist das behandeln der rohen ringpartitionen
                                                                //abgeschlossen, so dass direkt zur cover-funktion gesprungen werden kann
                                                                //***************************DEBUG*************************
                                                                //schreiben("visualizeringpartition(p)");
                                                               // visualizeringpartition(p);
                                                               // debuganimwait();
                                                                //*********************************************************
                                                                lp=p->ringpartitionsliste();
                                                                if(lp->anzahl()>0){//if(p->firstringpartition){
                                                                 if(lp->anfang(rit))do{
                                                                  if(rit->isolated){
                                                                   //L->schreiben("--------------------------------------iso--");
                                                                   //dann muss der surroundingringpartitionzeiger gesetzt werden
                                                                   if(determinesurroundingringpartition(p,rit)){
                                                                   // L->schreiben("--------------------------------------isoliert zugeordnet --");
                                                                    uniteringpartition(rit->surroundingringpartition,rit);
                                                                    rit->loeschmarkierung(true);//rit->killok=1;
                                                                   }else{
                                                                    //fehler("_modifikationnetzintersektion::createringpartition(_dreieck*);","surroundingringpartition konnte nicht determineniert werden.");
                                                                    //!!!!!!!!!!!!! prüfen, ob hier wirklich ein Felher vorliegt !!!!!!!!!!!!!!
                                                                   };
                                                                  };
                                                                 }while(lp->naechstes(rit));
                                                                 lp->loeschenmarkiert();
                                                                 if(lp->anzahl()==0){
                                                                  fehler("_modifikationnetzintersektion::createringpartition(_dreieck*);","Nach vereinigen der isolierten ringpartition und nach abtrennen deren köpfe liegt nun keine ringpartition mehr vor.");
                                                                 }else{
                                                                  //covern ausführen
                                                                  neuepoly=new _liste<_polygon >();
                                                                  //neuepoly->aushaengen();
                                                                  
                                                                  r=coverringpartition(p,neuepoly);
                                                                  //polygonoptimierung eintragen
                                                                  polygonoptimationlist.einhaengen(neuepoly);
                                                                  
                                                                  //hier noch nicht..poly dürfen erst nach abschluss der gesamtoperation
                                                                  //herlöscht werden
                                                                  //optimizepolygon(&neuepoly);
                                                                  //neuepoly.aushaengen();
                                                                 };
                                                                };
                                                                return(r);
};

void _modifikationnetzintersektion::createringpartition(_polygon*p,_intersektion*i){
                                                                //start der iteration von einer virtuellen intersektion aus
                                                                //es kann sein, dass bei der erzeugung der ringpartitionen, die von einer virtuellen intersektion aus gestartet
                                                                //werden, der partitionsstatus nicht bestimmt werden kann, da die ringsectionsequenz sich alleine auf virtuelle
                                                                //intersektion (ohne causaldreieck) stützt.
                                                                _statuskreuz*sc;
                                                                _statussektion*fss;
                                                                //------------------
                                                                i->switchsection(p);
                                                                i->anfang(fss);
                                                                //sc=i->firststatussection->firststatuscross;
                                                                if(fss->anfang(sc)){
                                                                 if(sc->markierung==0) {
                                                                  //********** DEBUG ***********
                                                                  //if(dbscreen) dbscreen->schreiben("void createringpartition(_polygon*,_intersektion*) : createringpartition an virtueller intersektion.",pdbcolnote);
                                                                  //****************************
                                                                  createringpartition(p,sc,0);
                                                                 };
                                                                }else{
                                                                 //peep(1);
                                                                 fehler("_modifikationnetzintersektion::createringpartition(_dreieck*,_intersektion*)","virtuelle intersektion i besitzt kein statuscross.");
                                                                };
};

void _modifikationnetzintersektion::createringpartition(_polygon*p,_listebasis<_verbinderisintro >*isic){
                                                                _verbinderisintro*iit;
                                                                _statuskreuz*sit;
                                                                _statussektion*fss;
                                                                _intersektion*is;
                                                                //---------------------
                                                                flagintersection(isic,0);
                                                                if(isic->anfang(iit))do{
                                                                 is=iit->intersektion();
                                                                 if(is->markierung==0){
                                                                  is->markierung=1;
                                                                  is->switchsection(p);
                                                                  is->anfang(fss);
                                                                  if(fss->anfang(sit))do{
                                                                   if(sit->markierung==0){
                                                                    //********** DEBUG ***********
                                                                    //if(dbscreen) dbscreen->schreiben("void createringpartition(_polygon*,_listebasis<_verbinderisintro >*) : createringpartition an realer intersektion.",pdbcolnote);
                                                                    //****************************
                                                                    createringpartition(p,sit,isic);
                                                                   };
                                                                  }while(fss->naechstes(sit));
                                                                 };
                                                                }while(isic->naechstes(iit));
};

void _modifikationnetzintersektion::createringpartition(_polygon*p,_statuskreuz*sc,_listebasis<_verbinderisintro >*isic){
                                                                //dies ist die eigentliche ringpartitionserzeugungsfunktion,
                                                                //iterationsrichtung it left[0]
                                                                //abbruchbedingung der iteration ist, wenn der startpunkt wieder erreicht wurde
                                                                _ringpartition*rp;
                                                                _statuskreuz*sit;
                                                                _intersektion*in;
                                                                _verbinderisextro*isec;
                                                                char stop;
                                                                //------------------
                                                                rp=new _ringpartition(p);
                                                                sit=sc;
                                                                stop=0;
                                                                do{
                                                                 new _ringsektion(rp,sit);
                                                                 //******************* DEBUG *********************
                                                                 //_weltdebugkreuz*wc;
                                                                 //_vektor4<_to> col;
                                                                 //col.setzen(0,1,1,0);
                                                                 //wc=new _weltdebugkreuz(W,sit->statussection()->intersektion->ort(),0.5,col);
                                                                 //debuganimation();
                                                                 //delete wc;
                                                                 //***********************************************
                                                                 checkringpartitionisolation(p,rp,sit->statussection()->intersektion);
                                                                 sit->markierung=1;
                                                                 //------------------------------------lokale statusdetermination ------------------------------------------------
                                                                 if(rp->status==0){
                                                                  if(sit->statussection()->intersektion->anfang(isec)){//firstisextroconnector){
                                                                   if(isic==0){//if(firstisic==0){
                                                                    //aufruf der funktion stammt von einer virtuellen intersektion
                                                                    //es muss also vorher noch ein intersektion-referenezierender introconnectorring
                                                                    //identifizert werden, der von dreieck d referenziert wird
                                                                    if(isintersectionreferenzed(sit->statussection()->intersektion,p,isic)){
                                                                     sit->determinestatus(p,isic);
                                                                     rp->status=sit->status;
                                                                     if(plog) schreiben("_modifikationnetzintersektion::lokale statusdetermination virtueller intersektion ergab : status=",rp->status);
                                                                    }else{
                                                                     fehler("_modifikationnetzintersektion::createringpartition(_dreieck*,_statuskreuz*,_verbinderisintro*&)","firstisintroconnectorreferenz konnte nicht rückidentifiziert werden.");
                                                                    };
                                                                   }else{
                                                                    //aufruf der funktion stammt von einer reellen intersektion
                                                                    //der vorher iterierte firstisiczeiger wurde initialisiert übergeben
                                                                    sit->determinestatus(p,isic);
                                                                    rp->status=sit->status;
                                                                    if(plog) schreiben("_modifikationnetzintersektion::lokale statusdetermination reeler intersektion ergab : status=",rp->status);
                                                                   };
                                                                  }else{//es muss eine virtuelle intersektion vorliegen
                                                                  };
                                                                 };
                                                                 //---------------------------------------------------------------------------------------------------------------
                                                                 in=sit->left(0);
                                                                 if(in){
                                                                  if(in!=sc->statussection()->intersektion){
                                                                   determinenextstatuscross(p,in,sit);
                                                                   if(isintersectionreferenzed(sit->statussection()->intersektion,p,isic)==0){
                                                                    //!!!!!!!!! was ist mit virtueller interserction??????? 
//                                                                    fehler("void _modifikationnetzintersektion::createringpartition(_polygon*p,_statuskreuz*sc,_listebasis<_verbinderisintro >*isic)","nach determinenextstatuscross : sit->intersektion ist nicht mehr über p erreichbar");

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!   Klären ob dieser fehler so sinnvoll ist !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!   Klären ob dieser fehler so sinnvoll ist !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!   Klären ob dieser fehler so sinnvoll ist !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!   Klären ob dieser fehler so sinnvoll ist !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!   Klären ob dieser fehler so sinnvoll ist !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!   Klären ob dieser fehler so sinnvoll ist !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!   Klären ob dieser fehler so sinnvoll ist !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!   Klären ob dieser fehler so sinnvoll ist !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!   Klären ob dieser fehler so sinnvoll ist !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!   Klären ob dieser fehler so sinnvoll ist !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!   Klären ob dieser fehler so sinnvoll ist !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!   Klären ob dieser fehler so sinnvoll ist !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!   Klären ob dieser fehler so sinnvoll ist !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!   Klären ob dieser fehler so sinnvoll ist !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!




                                                                   };
                                                                  }else{
                                                                   stop=1;
                                                                  };
                                                                 }else{
                                                                  stop=1;
                                                                  fehler("void _modifikationnetzintersektion::createringpartition(_polygon*p,_statuskreuz*sc,_listebasis<_verbinderisintro >*isic)","left(0)==0");
                                                                 };
                                                                }while(stop==0);
                                                                //übrig bleiben sollen nur ringpartitionen mit positiven oder null-status, wobei
                                                                //diese dann direkt mit geoconnectoren integriert werden
                                                                if(rp->status==+1){
                                                                 rp->integrate();
                                                                };
                                                                //********************* DEBUG ******************
                                                               // rp->visualisieren();
                                                               // if(dbscreen) dbscreen->schreiben("Visualisierung einer rohen Ringpartition mit Status=",rp->status,pdbcolnote);
                                                               // debuganimwait();
                                                               // rp->unvisualisieren();
                                                                //**********************************************
};

















void _modifikationnetzintersektion::determinevirtualpartitionstatus(_polygon*p){
                                                                //hier sind nun alle ringpartitionen generiert.
                                                                //bekannt sind zur zeit das isolated-markierung und der partitionstatus( +1 und -1 nicht 0).
                                                                //desweiteren sind die positiven ringpartitionen integriert worden.
                                                                //für eine eventuell auftretende null-status ringpartition müssen analytisch alle isolierten
                                                                //ringpartitionen herangezogen werden (es muss dabei mindestens eine geben, es kann auf irgendeinen
                                                                //ringsectionvector gezielt werdem)
                                                                _ringpartition*rit;
                                                                //-----------------
                                                                if(p->ringpartitionsliste()->anfang(rit))do{
                                                                 if(rit->status==0){
                                                                  determinevirtualpartitionstatus(p,rit);
                                                                 };
                                                                }while(p->ringpartitionsliste()->naechstes(rit));
};

void _modifikationnetzintersektion::determinevirtualpartitionstatus(_polygon*p,_ringpartition*rnull){
                                                                //diese funktion wird nur beim vorhandensein von ringpartitionen, die sich auf
                                                                //komplett virtuelle intersektion abstützen,so dass deren status hiermit bestimmt werden muss
                                                                //bei dieser gelegenheit kann auch der surroundingringpartition-zeiger der isolierten
                                                                //ringpartition, die bei der analytik als koherent identifiziert wird, initialisiert werden
                                                                _ringpartition*rit;
                                                                _ringpartition*lowest;
                                                                _ringsektion*rstarget[2];
                                                                _ringsektion*rs;
                                                                _vektor3<_tg> o;
                                                                _vektor3<_tg> v;
                                                                _vektor3<_tg> t;
                                                                _tg l;
                                                                _intersektion*istarget[2];
                                                                _listebasis<_rpintersektion > rplist;
                                                                //---------------------
                                                                //****** DEBUG *******
                                                                if(dbscreen) dbscreen->schreiben("void determinevirtualpartitionstatus(_polygon*,_ringpartition*)",pdbcolfunc);
                                                                //********************
                                                                //kollisionstarget bestimmen,d.h bis zu irgendeiner isolierten ringpartition iterieren
                                                                //und dann irgendeine ringsectiongerade dieser isolierten partition als target heranziehen
                                                                lowest=0;
                                                                rstarget[0]=0;
                                                                rstarget[1]=0;
                                                                if(p->ringpartitionsliste()->anfang(rit))do{
                                                                 if(rit->isolated){
                                                                  if(rit!=rnull){
                                                                   if(rit->anfang(rstarget[0])){
                                                                    rstarget[1]=rstarget[0]->naechstes();
                                                                   }else{
                                                                    fehler("_modifikationnetzintersektion::determinevirtualpartitionstatus(_polygon*,_ringpartition*)","ringpartition rit besitzt keine ringsektion.");
                                                                    if(dbscreen) dbscreen->schreiben("determinevirtualpartitionstatus : ringpartition rit besitzt keine ringsektion.",pdbcolerror);
                                                                   };
                                                                  }else{
                                                                   fehler("_modifikationnetzintersektion::determinevirtualpartitionstatus(_dreieck*,_ringpartition*)","rnull-ringpartition ist als isoliert geflaggt (unmöglich!).");
                                                                   if(dbscreen) dbscreen->schreiben("determinevirtualpartitionstatus : rnull-ringpartition ist als isoliert geflaggt (unmöglich!).",pdbcolerror);
                                                                  };
                                                                 };
                                                                }while(p->ringpartitionsliste()->naechstes(rit));
                                                                if(rstarget[0]){
                                                                 //an dieser stelle den collisionsvektor im 2dimensionalen aufspannen und mit allen
                                                                 //isolierten ringpartitionen kollidieren
                                                                 istarget[0]=rstarget[0]->intersektion;
                                                                 istarget[1]=rstarget[1]->intersektion;
                                                                 t=istarget[0]->ort()+(istarget[1]->ort()-istarget[0]->ort())*0.5112341;
                                                                 rnull->anfang(rs);
                                                                 o=rs->intersektion->ort();
                                                                 v=t-o;
                                                                 l=v.laenge();
                                                                 if(p->ringpartitionsliste()->anfang(rit))do{
                                                                  if(rit->isolated){
                                                                   collideringpartition(p,rit,o,v,&rplist);
                                                                  };
                                                                 }while(p->ringpartitionsliste()->naechstes(rit));
                                                                 if(rplist.anzahl()==0){
                                                                  fehler("void _modifikationnetzintersektion::determinevirtualpartitionstatus(_polygon*p,_ringpartition*rnull)","rplist.anzahl()==0");
                                                                  if(dbscreen) dbscreen->schreiben("determinevirtualpartitionstatus : rplist.anzahl()==0",pdbcolerror);
                                                                 };
                                                                 filterbackfacedrpintersection(p,v,&rplist);
                                                                 // ***************** DEBUG ***************
                                                                 //_rpintersektion*rpit;
                                                                 //_liste<_weltdebuglinie > llines;
                                                                 //_weltdebugpfeil*da;
                                                                 //_vektor4<_to> col;
                                                                 //_vektor<_tg> vv;
                                                                 //_vektor<_tg> t;
                                                                 //col.setzen(1,1,1,0);
                                                                 //schreiben("Debug:visualisierung des Kollisionsvektors");
                                                                 //if(dbscreen) dbscreen->schreiben("determinevirtualpartitionstatus : Visualisierung des Kollisionsvektors",pdbcolnote);
                                                                 //da=new _weltdebugpfeil(W,o,o+v,0.05,0.05,col);
                                                                 //if(rplist.anfang(rpit))do{
                                                                 // schreiben("Debug:visualisierung des Kollisionsvektors : rpit->alpha  =",(double)rpit->alpha);
                                                                 // schreiben("Debug:visualisierung des Kollisionsvektors : status der rp=",(int)rpit->ringpartition->status);
                                                                 // col.setzen(1,1,0,0);
                                                                 // llines.einhaengen(new _weltdebuglinie(W,rpit->ringsection[0]->intersektion->ort(),rpit->ringsection[1]->intersektion->ort(),col));
                                                                 // vv=rpit->ringsection[1]->intersektion->ort() - rpit->ringsection[0]->intersektion->ort();
                                                                 // V3.rotieren(*p,vv,-90,t);
                                                                 // t.normalisieren();
                                                                 // if(rpit->ringpartition->status==+1) col.setzen(0,1,0,0);
                                                                 // if(rpit->ringpartition->status==0) col.setzen(0.5,0.5,0.5,0);
                                                                 // if(rpit->ringpartition->status==-1) col.setzen(1,0,0,0);
                                                                 // llines.einhaengen(new _weltdebuglinie(W,
                                                                 // rpit->ringsection[0]->intersektion->ort()+vv*0.5,
                                                                 // rpit->ringsection[0]->intersektion->ort()+vv*0.5+t,col));
                                                                 // debuganimation();
                                                                 //}while(rplist.naechstes(rpit));
                                                                 //llines.loeschen();
                                                                 //delete da;
                                                                 // ***************************************
                                                                 determinevirtualpartitionstatus(rnull,&rplist);
                                                                 rplist.loeschen();
                                                                }else{
                                                                 fehler("_modifikationnetzintersektion::determinevirtualpartitionstatus(_dreieck*,_ringpartition*)","keine isolierte ringpartition vorhanden, obwohl eine virtuelle existiert.");
                                                                };
                                                                
};

void _modifikationnetzintersektion::determinevirtualpartitionstatus(_ringpartition*rnull,_listebasis<_rpintersektion >*rplist){
                                                                //die funktion identifiziert die koherenz anhand des niedrigsten positiven
                                                                //schnittparameters (alpha); der status der virtuellen partition wird dann dem status der koherenten partition
                                                                //gleichgesetzt
                                                                _rpintersektion*rpi;
                                                                //----------------------
                                                                if(rplist->anfang(rpi)){
                                                                 rnull->status=rpi/*->ringsection[0]*/->ringpartition->status;
                                                                 // ************ DEBUG ******************
                                                                 if(plog) schreiben("_modifikationnetzintersektion::status der virtuellen partition : status =",rnull->status);
                                                                 if(plog) schreiben("_modifikationnetzintersektion::der dazuhehörige alpha wert ist : alpha  =",rpi->alpha);
                                                                 //rpi->ringsection[0]->ringpartition->visualisieren();
                                                                 //if(dbscreen){
                                                                  //dbscreen->schreiben("Status der virtuellen Partition : ",rnull->status,pdbcolnote);
                                                                  //dbscreen->schreiben("der dazugehörige alpha-wert = ",rpi->alpha,pdbcolnote);
                                                                  //debuganimation();
                                                                 //};
                                                                 // *************************************
                                                                 rpi->ringsection[0]->ringpartition->surroundingringpartition=rnull;
                                                                 if(rnull->status==+1){
                                                                  rnull->integrate();
                                                                  // ************ DEBUG ******************
                                                                  //rnull->visualisieren();
                                                                  //debuganimation();
                                                                  // *************************************
                                                                 };
                                                                }else{
                                                                 fehler("_modifikationnetzintersektion::determinevirtualpartitionstatus(_rinmgpartition*,_rpintersektion*&)","erstes rp-intersectionzeiger = 0");
                                                                };
};

void _modifikationnetzintersektion::determinevirtualintersectionstatus(_polygon*p){
                                                                //jetzt noch sicherstellen, das der intersectionstatus in allen virtuelle intersektion-statuscrosses gesetzt
                                                                //ist, so dass im anschluss an ringpartitioncreate spreadvirtualintersectionflags() ausgeführt werden kann
                                                                _ringpartition*rit;
                                                                _ringsektion*rsit;
                                                                char check;
                                                                _vertex*vit;
                                                                _listenknoten<_vertex>*lnvit;
                                                                _statussektion*ss;
                                                                _statuskreuz*sc;
                                                                //--------------
                                                                check=0;
                                                                //vit=p->vertex();
                                                                //if(vit)do{
                                                                if(p->anfang(lnvit))do{
                                                                 vit=lnvit->objekt();
                                                                 if(vit->intersektion()){
                                                                  vit->intersektion()->switchsection(p);
                                                                  check=1;
                                                                 };
                                                                // vit=vit->naechstes(p);
                                                                }while((p->naechstes(lnvit))&&(check==0));
                                                                if(check){
                                                                 if(p->ringpartitionsliste()->anfang(rit))do{
                                                                  if(rit->anfang(rsit))do{
                                                                   //vit=p->vertex();
                                                                   //if(vit)do{
                                                                   iterierenliste(p,lnvit,
                                                                    vit=lnvit->objekt();
                                                                    if(vit->intersektion()){
                                                                     if(rsit->intersektion==vit->intersektion()){
                                                                      if(vit->intersektion()->anfang(ss)){
                                                                       if(ss->anfang(sc)){
                                                                        sc->status=rit->status;
                                                                       };
                                                                      };
                                                                     };
                                                                    };
                                                                   );
                                                                   // vit=vit->naechstes(p);
                                                                   //}while(vit!=p->vertex());
                                                                  }while(rit->naechstes(rsit));
                                                                 }while(p->ringpartitionsliste()->naechstes(rit));
                                                                };
};

void _modifikationnetzintersektion::clearnegativepartition(_polygon*p){
                                                                //nun können alle negativ geflaggten ringpartitionen
                                                                //gelöscht werden, damit diese nicht mehr bei der surroundingringpartitiondetermination
                                                                //unnötigen rechenaufwnd verursachen
                                                                _ringpartition*rit;
                                                                //-----------------------
                                                                if(p->ringpartitionsliste()->anfang(rit))do{
                                                                 if(rit->status==-1){
                                                                  rit->loeschmarkierung(true);
                                                                  // *************** DEBUG ************
                                                                  //if(dbscreen) dbscreen->schreiben("eine negative ringpartition wurde geloescht",pdbcolnote);
                                                                  // **********************************
                                                                 }else{
                                                                  if(rit->status!=+1){
                                                                   fehler("_modifikationnetzintersektion::createringpartition(_dreieck*)","ringpartitionstatus ist weder +1 noch -1; also wahrscheinlich null.");
                                                                  };
                                                                 };
                                                                }while(p->ringpartitionsliste()->naechstes(rit));
                                                                p->ringpartitionsliste()->loeschenmarkiert();
};
char _modifikationnetzintersektion::determinesurroundingringpartition(_polygon*p,_ringpartition*riso){
                                                                //hier mit allen anderen ringpartitionen kollidieren, bei denen
                                                                //der start punkt o innerhalb ist
                                                                _ringpartition*rit;
                                                                _listebasis<_rpintersektion > rpl;
                                                                _rpintersektion*rpit;
                                                                _vektor3<_tg> o;//(2);
                                                                _vektor3<_tg> v;//(2);
                                                                _vektor3<_tg> w;//(2);
                                                                _intersektion*is;
                                                                _ringsektion*rs;
                                                                int rpcount;
                                                                //------------------
                                                                if(riso->surroundingringpartition==0){
                                                                 //***** DEBUG ******
                                                                 //if(dbscreen) dbscreen->schreiben("Es wird eine äussere Ringpartition zu einer isolierten gesucht.",pdbcolnote);
                                                                 //******************
                                                                 //den startpunkt o der ebene o-v-w initialisieren
                                                                 riso->anfang(rs);
                                                                 is=rs->intersektion;
                                                                 o=is->ort();
                                                                 //iteration ausführen
                                                                 if(p->ringpartitionsliste()->anfang(rit))do{
                                                                  if(rit!=riso){
                                                                   //****** DEBUG ********
                                                                   //_vektor4<_to> col;
                                                                   //_weltdebugpfeil*dbv;
                                                                   //_weltdebugpfeil*dbw;
                                                                   //rit->visualisieren();
                                                                   //v=p->ebene(0)+p->ebene(1);
                                                                   //v.normalisieren();
                                                                  // w=v%p->normale();
                                                                  // col.setzen(1,1,1,0);
                                                                  // dbv=new _weltdebugpfeil(W,o,o+v,0.1,0.05,col);
                                                                  // col.setzen(0,1,1,0);
                                                                 //  dbw=new _weltdebugpfeil(W,o,o+w,0.1,0.05,col);
                                                                 //  debuganimwait();
                                                                 //  rit->unvisualisieren();
                                                                 //  delete dbv;
                                                                  // delete dbw;
                                                                   //*********************
                                                                   if(rit->punktinnerhalb(o)){//punkt innerhalb der partition?
                                                                    //***** DEBUG ******
                                                                    //if(dbscreen) dbscreen->schreiben("Der Startpunk o ist innerhalb einer Partition rit.",pdbcolnote);
                                                                    //******************
                                                                    v=(p->ebene(0)-p->ebene(1))*0.54321113131121f;
                                                                    v.normalisieren();
                                                                    collideringpartition(p,rit,o,v,&rpl);
                                                                   };
                                                                  };
                                                                 }while(p->ringpartitionsliste()->naechstes(rit));
                                                                 //rp-liste nun auswerten
                                                                 if(rpl.anfang(rpit)){
                                                                  rpcount=0;
                                                                  do{
                                                                   rpcount++;
                                                                  }while(rpl.naechstes(rpit));
                                                                  if((rpcount%2)==1){
                                                                   filterbackfacedrpintersection(p,v,&rpl);
                                                                   if(rpl.anfang(rpit)){
                                                                    riso->surroundingringpartition=rpit->ringsection[0]->ringpartition;
                                                                    //***** DEBUG ******
                                                                    //if(dbscreen) dbscreen->schreiben("Es wurde eine äussere Ringpartition identifiziert.",pdbcolnote);
                                                                    //******************
                                                                   }else{
                                                                    fehler("_modifikationnetzintersektion::determinesurroundingringpartition(_dreieck*,_ringpartition*)","Nach filterbackfacedrpintersection ist der erstes rpintersection-zeiger = 0.");
                                                                   };
                                                                  };
                                                                 }else{
                                                                  // !!!!!!!!!!!!!!!!! prüfen ob der Fehler tatsächlich auftreten kann !!!!!!!!!!!!!!!
                                                                  //fehler("_modifikationnetzintersektion::determinesurroundingringpartition(_dreieck*,_ringpartition*)","Die positive Gerade, die von riso ausgeht kollidierte mit keiner surroundingringpartition.");
                                                                 };
                                                                 rpl.loeschen();
                                                                 if(riso->surroundingringpartition) return(1); else return(0);
                                                                }else{
                                                                 return(1);
                                                                };
};
void _modifikationnetzintersektion::filterbackfacedrpintersection(_polygon*p,_vektor3<_tg>&v,_listebasis<_rpintersektion >*rplist){
                                                                //hier müssen alle backfaced ringsectionvektoren aus der rpintersection-liste
                                                                //entfernt werden, was mit hilfe der geoconnector-rightvectoren geschehen kann
                                                                _rpintersektion*rit;
                                                                _vektor3<_tg> t;
                                                                _vektor3<_tg> vv;
                                                                bool stop;
                                                                //-------------------
                                                                if(rplist->anfang(rit))do{
                                                                 //w=rit->ringsection[1]->statuscross->alpha(0)+90;
                                                                 vv=rit->ringsection[1]->intersektion->ort() - rit->ringsection[0]->intersektion->ort();
                                                                 V3.rotieren(p->normale(),vv,-90,t);
                                                                 t.normalisieren();
                                                                 vv=v;
                                                                 vv.normalisieren();
                                                                 t+=vv;
                                                                 if(t.laenge()>sqrt(2.0f)) {
                                                                  rit->loeschmarkierung(true);
                                                                 }else{
                                                                  rit->loeschmarkierung(false);//rit->killok=0;
                                                                 };
                                                                }while(rplist->naechstes(rit));
                                                                rplist->loeschenmarkiert();
                                                                if(rplist->anfang(rit)){
                                                                 stop=false;
                                                                 do{
                                                                  rplist->anfang(rit);
                                                                  if(rit->alpha>rit->vorheriges()->alpha) rplist->rotierenvorheriges(); else stop=true;
                                                                 }while(stop==false);
                                                                 //while(firstrp->alpha>firstrp->vorheriges->alpha) firstrp=firstrp->vorheriges;
                                                                }else{
                                                                 fehler("_modifikationnetzintersektion::filterbackfacedrpintersection('_tg*,_rpintersektion*&)","firstrp == 0 nach selecktiver destruktion.");
                                                                };
};

char _modifikationnetzintersektion::collideringpartition(_polygon*p,_ringpartition*rp,_vektor3<_tg>&o,_vektor3<_tg>&v,_listebasis<_rpintersektion >*rpislist){
                                                                //die collision im zweidimensionalen erfolgt ohne verbreiterung
                                                                //der rinsectionvektoren und ohne parallelitätskompensation
                                                                char r;
                                                                _ringsektion*rit;
                                                                _ringsektion*nit;
                                                                _vektor2<_tg> q;
                                                                _vektor2<_tg> w;
                                                                _vektor2<_tg> nv;
                                                                _vektor2<_tg> e;
                                                                int c0,c1;
                                                                _tg D,a,b;
                                                                //-----------
                                                                c0=p->groessterindex(0);
                                                                c1=p->groessterindex(1);
                                                                r=0;
                                                                nv.setzen(-v[c0],-v[c1]);
                                                                nv.normalisieren();
                                                                if(rp->anfang(rit))do{
                                                                 nit=rit->naechstes();
                                                                 q.setzen(rit->intersektion->ort()[c0],rit->intersektion->ort()[c1]);
                                                                 w.setzen(nit->intersektion->ort()[c0],nit->intersektion->ort()[c1]);
                                                                 w-=q;
                                                                 //dilatenearzero(q,w);
                                                                 e.setzen(o[c0]-q[0],o[c1]-q[1]);
                                                                 D=V2.determinieren(nv,w);
                                                                 if(D){//--------------------------------  schräglage -------------------------------
                                                                  b=V2.determinieren(nv,e)/D;
                                                                  if((b>=0)&&(b<=1)){
                                                                   a=V2.determinieren(e,w)/D;
                                                                   if(a>0){
                                                                    new _rpintersektion(rpislist,rp,nit,rit,a);
                                                                   };
                                                                  }
                                                                 }else{//--------------------------------  parallelität -----------------------------
                                                                 };//parallelität
                                                                }while(rp->naechstes(rit));
                                                                return(r);              
};

char _modifikationnetzintersektion::checkringpartitionisolation(_polygon*p,_ringpartition*rp,_intersektion*is){
                                                                char r;
                                                                _verbinderisextro*iet;
                                                                //---------
                                                                r=1;
                                                                if(is->anfang(iet)){
                                                                 if(is->checkedgekoherence(p)) {
                                                                  rp->isolated=0;
                                                                  r=0;
                                                                 };
                                                                }else{//virtuelle intersektion
                                                                 rp->isolated=0;
                                                                 r=0;
                                                                };
                                                                return(r);
};

char _modifikationnetzintersektion::determinenextstatuscross(_polygon*p,_intersektion*in,_statuskreuz*&s){
                                                                _statuskreuz*sit;
                                                                _statuskreuz*nsit;
                                                                _statussektion*fss;
                                                                //----------------
                                                                in->switchsection(p);
                                                                in->anfang(fss);
                                                                nsit=0;
                                                                if(fss->anfang(sit))do{
                                                                 if(sit->left(1)==s->statussection()->intersektion) nsit=sit;
                                                                }while((fss->naechstes(sit))&&(nsit==0));
                                                                if(nsit){
                                                                 s=nsit;
                                                                 return(1);
                                                                }else{
                                                                 return(0);
                                                                };
};

void _modifikationnetzintersektion::uniteringpartition(_ringpartition*rman,_ringpartition*riso){
                                                                _ringsektion*rit;
                                                                //-------------------
                                                                if(riso->anfang(rit))do{
                                                                 rit->ringpartition=rman;
                                                                }while(riso->naechstes(rit));
                                                                rman->vereinigen(riso);
                                                                //unite_ring(rman->firstringsection,riso->firstringsection);
                                                                //riso->firstringsection=0;
};
//***************************************************************************  R I N G P A R T I T I O N P E R F O R M A T I O N   *********************************************************************************

char _modifikationnetzintersektion::coverringpartition(_polygon*p,_liste<_polygon >*neuepoly){
                                                                //iteriert alle partitionen von poly p zum covern
                                                                //strategische steuerfunktion für den cover-algorithmus
                                                                //stellt eine startkante zur verfügung und muss sicherstellen,
                                                                //dass dabei kein geometrischer punkt entsteht!
                                                                _ringpartition*rp;
                                                                _ringsektion*rs;
                                                                _verbindergeometrischiterator*start;
                                                                char r;
                                                                //---------------
                                                                r=1;
                                                                if(p->ringpartitionsliste()->anfang(rp))do{
                                                                 if(plog) schreiben("_modifikationnetzintersektion::coverringpartition : start");
                                                                 p->erzeugentexturraum();
                                                                 
                                                                 while((rp->anfang(rs))&&(r==1)){
                                                                  if(plog) schreiben("_modifikationnetzintersektion::coverringpartition : initstartiterator");
                                                                  initstartiterator(rp,start);
                                                                  if(plog) schreiben("_modifikationnetzintersektion::coverringpartition : getpossibles");
                                                                  getpossiblegeoconnectoriterators(p,rp,start);
                                                                  if(plog) schreiben("_modifikationnetzintersektion::coverringpartition : limitgeoconnectoriterators()");
                                                                  limitgeoconnectoriterators(maxgitentry);
                                                                  if(plog) schreiben("_modifikationnetzintersektion::coverringpartition : sortalpha gits");
                                                                  sortalphageoconnectoriterators(p);
                                                                  if(plog) schreiben("_modifikationnetzintersektion::coverringpartition : searchvalidpartition");
                                                                  if(searchvalidpartition(p,rp)==0) {
                                                                   fehler("void _modifikationnetzintersektion::coverringpartition(_polygon*p)","Searchvalidpartition hat keine gültige konvexe partition von rp gefunden.");
                                                                   r=0;
                                                                  }else{
                                                                   if(plog) schreiben("_modifikationnetzintersektion::coverringpartition : spreadpartiton");
                                                                   spreadpartition(p,rp);
                                                                   if(plog) schreiben("_modifikationnetzintersektion::coverringpartition : createpoly");
                                                                   createpoly(p,rp,neuepoly);
                                                                   geoconnectoriteratorrawlist.loeschen();
                                                                   geoconnectoriteratordistancelist.loeschen();
                                                                   geoconnectoriteratoralphalist.loeschen();
                                                                  };
                                                                 };
                                                                 p->loeschentexturraum();
                                                                 if(plog) schreiben("_modifikationnetzintersektion::coverringpartition : ende");
                                                                }while((p->ringpartitionsliste()->naechstes(rp))&&(r==1));
                                                                return(r);
};

void _modifikationnetzintersektion::initstartiterator(_ringpartition*rp,_verbindergeometrischiterator*&geoit){
                                                                _verbindergeometrisch*g;
                                                                _ringsektion*rs;
                                                                //--------------------------------
                                                                geoit=0;
                                                                geoconnectoriteratorrawlist.loeschen();
                                                                geoconnectoriteratordistancelist.loeschen();
                                                                geoconnectoriteratoralphalist.loeschen();
                                                                rp->anfang(rs);
                                                                if(rs->anfang(g)){
                                                                 while(g->geoconnector[0]==g){
                                                                  fehler("void _modifikationnetzintersektion::initstartiterator(_ringpartition*rp,_verbindergeometrischiterator*&geoit)","Es wurde ein singularer geoconnector als start-kante ausgewählt.");
                                                                  rp->rotierennaechstes();
                                                                  rp->anfang(rs);
                                                                  if(rs->anfang(g)==false){
                                                                   fehler("void _modifikationnetzintersektion::initstartiterator(_ringpartition*rp,_verbindergeometrischiterator*&geoit)","Ringsection ohne geoconnector(1).");
                                                                  };
                                                                 };
                                                                 geoit=new _verbindergeometrischiterator(&geoconnectoriteratordistancelist,0,0,g,g);
                                                                 geoit->spread(0);
                                                                 // ******************* DEBUG:vis. des startiterators*******
                                                                 //_vektor4<_to> col;
                                                                 //col.setzen(0.1,1,0.1,0);
                                                                 //geoit->visualisieren(col);
                                                                 //debuganimwait();
                                                                 // ********************************************************
                                                                }else{
                                                                 fehler("void _modifikationnetzintersektion::initstartiterator(_ringpartition*rp,_verbindergeometrischiterator*&geoit)","Ringsection ohne geoconnector(2).");
                                                                };
};

void _modifikationnetzintersektion::getpossiblegeoconnectoriterators(_polygon*p,_ringpartition*rp,_verbindergeometrischiterator*start){
                                                                //funktion iteriert alle geometrischen ringe (geoconnector-verbund)
                                                                //und lässt diese auf eignung für die start-kante prüfen
                                                                _ringsektion*rit;
                                                                _verbindergeometrisch*git;
                                                                _verbindergeometrisch*ggit;
                                                                _verbindergeometrisch*ggin;
                                                                _ringsektion*or0;
                                                                _ringsektion*or1;
                                                                _ringsektion*r0;
                                                                _ringsektion*r1;
                                                                _tg distance;
                                                                _verbindergeometrischiterator*gn;
                                                                _verbindergeometrischiterator*cit;
                                                                //--------------
                                                                rp->flaggeoconnector(1);
                                                                r0=start->geoconnector(0)->ringsection;
                                                                r1=start->geoconnector(1)->ringsection;
                                                                if(rp->anfang(rit))do{
                                                                 if(rit->anfang(git))do{
                                                                  if(git->markierung==1){
                                                                   ggit=git;
                                                                   do{
                                                                    ggin=ggit->getgeoconnector(0);
                                                                    or0=ggit->ringsection;
                                                                    or1=ggin->ringsection;
                                                                    if((or0!=r0)&&(or0!=r1)){
                                                                     if(checkgeoconnectoriteratorisvalid(p,start,ggit,distance)){
                                                                      gn=new _verbindergeometrischiterator(&geoconnectoriteratordistancelist,distance,0,ggit,ggit);
                                                                      // **************** DEBUG ***********
                                                                      //_vektor4<_to> col;
                                                                      //col.setzen(1,0.1,0.1,0);
                                                                      //gn->visualisieren(col);
                                                                      //debuganimation();
                                                                      // **********************************
                                                                     };
                                                                    };
                                                                    ggit->markierung=0;
                                                                    ggit=ggin;
                                                                   }while(ggit!=git);
                                                                  };
                                                                 }while(rit->naechstes(git));
                                                                }while(rp->naechstes(rit));
                                                                //nun, nachdem die rohe distanzliste aufgebaut worden ist,
                                                                //muss untersucht werden, ob sie singulare geoconnectoren enthält, die 
                                                                //auf dieselbe ringsection zeigen, alle solche gruppen werden durch listen 
                                                                //markiert
                                                                _liste<_liste<_verbindergeometrischiterator > > groups;
                                                                _listenknoten<_liste<_verbindergeometrischiterator > >*grit;
                                                                _liste<_verbindergeometrischiterator >*nl;
                                                                _listenknoten<_verbindergeometrischiterator >*griit;
                                                                _listenknoten<_verbindergeometrischiterator >*keepnode;
                                                                _vektor3<_tg> h;
                                                                _tg min;
                                                                if(geoconnectoriteratordistancelist.anfang(gn))do{
                                                                 gn->markierung(0);
                                                                }while(geoconnectoriteratordistancelist.naechstes(gn));
                                                                if(geoconnectoriteratordistancelist.anfang(gn))do{
                                                                 if(gn!=start){
                                                                  if(gn->markierung()==0){
                                                                   gn->markierung(1);
                                                                   nl=new _liste<_verbindergeometrischiterator >();
                                                                   groups.einhaengen(nl);
                                                                   nl->einhaengen(gn);
                                                                   cit=gn;
                                                                   while(geoconnectoriteratordistancelist.naechstes(cit)){
                                                                    if(gn->geoconnector(0)->ringsection==cit->geoconnector(0)->ringsection){
                                                                     nl->einhaengen(cit);
                                                                     cit->markierung(1);
                                                                    };
                                                                   };
                                                                  };
                                                                 };
                                                                }while(geoconnectoriteratordistancelist.naechstes(gn));
                                                                if(groups.anfang(grit))do{
                                                                 if(grit->objekt()->anzahl()<=1) grit->loeschmarkierungobjekt(true);
                                                                }while(groups.naechstes(grit));
                                                                groups.loeschenmarkiert();
                                                                if(groups.anfang(grit))do{
                                                                 min=10;
                                                                 keepnode=0;
                                                                 if(grit->objekt()->anfang(griit))do{
                                                                  git=griit->objekt()->geoconnector(0);
                                                                  h=start->mitte()-(git->ringsection->intersektion->ort()+git->middleanglevector());
                                                                  if(h.laenge()<min) {
                                                                   min=h.laenge();
                                                                   keepnode=griit;
                                                                  };
                                                                 }while(grit->objekt()->naechstes(griit));
                                                                 if(keepnode){
                                                                  if(grit->objekt()->anfang(griit))do{
                                                                   if(griit!=keepnode) {
                                                                    griit->loeschmarkierungobjekt(true);
                                                                   };
                                                                  }while(grit->objekt()->naechstes(griit));
                                                                  grit->objekt()->loeschenmarkiert();
                                                                 };
                                                                }while(groups.naechstes(grit));
                                                                groups.loeschen();
                                                                //raw liste aufbauen
                                                                geoconnectoriteratorrawlist.loeschen();
                                                                if(geoconnectoriteratordistancelist.anfang(gn))do{
                                                                 new _verbindergeometrischiterator(&geoconnectoriteratorrawlist,gn);
                                                                }while(geoconnectoriteratordistancelist.naechstes(gn));
                                                               
};

char _modifikationnetzintersektion::checkgeoconnectoriteratorisvalid(_polygon*p,_verbindergeometrischiterator*start,_verbindergeometrisch*g,_tg&alpha){
                                                                //funktion uberprüft, ob der singulare geoconnectoriterator(g,g)
                                                                //frontsichtbar ist von der start kante aus
                                                                _ringsektion*ro;
                                                                _verbindergeometrisch*gs[2];
                                                                _ringsektion*rs[2];
                                                                char r;
                                                                _vektor3<_tg> v;
                                                                _tg l;
                                                                //--------------------
                                                                alpha=1e+6;
                                                                gs[0]=start->geoconnector(0);
                                                                gs[1]=start->geoconnector(1);
                                                                rs[0]=gs[0]->ringsection;
                                                                rs[1]=gs[1]->ringsection;
                                                                ro=g->ringsection;
                                                                if((ro==rs[0])||(ro==rs[1])){
                                                                 r=0;
                                                                }else{
                                                                 r=0;
                                                                 v=ro->intersektion->ort()-start->mitte();
                                                                 alpha=v.laenge();
                                                                 if(alpha>0){
                                                                  v.normalisieren();
                                                                  v+=gs[1]->normale;
                                                                  l=v.laenge();
                                                                  if(l>sqrt(2.0f)) {
                                                                   r=1;
                                                                  };
                                                                 }else{
                                                                  fehler("char _modifikationnetzintersektion::checkgeoconnectoriteratorisvalid(_polygon*,_verbindergeometrischiterator*,_verbindergeometrisch*,_tg&)","alpha==0 -> division durch null");
                                                                 };
                                                                };
                                                                return(r);
};

void _modifikationnetzintersektion::limitgeoconnectoriterators(unsigned int mgi){
                                                                //behandlung des reglers mgi :
                                                                //1 bedeutet : nur startkante nicht möglich(!)
                                                                //2 bedeutet : startkante und 1 otherkante
                                                                //3... usw
                                                                unsigned int i;
                                                                _verbindergeometrischiterator*git;
                                                                //-----------
                                                                if(mgi<2){
                                                                 fehler("void _modifikationnetzintersektion::limitgeoconnectoriterators()","maxgitentry<2 wird korrigiert...");
                                                                 mgi=2;
                                                                };
                                                                i=0;
                                                                if(geoconnectoriteratordistancelist.anfang(git)){
                                                                 do{
                                                                  if(i>=mgi){
                                                                   git->loeschmarkierung(true);
                                                                  };
                                                                  i++;
                                                                 }while(geoconnectoriteratordistancelist.naechstes(git));
                                                                }else{
                                                                 fehler("void _modifikationnetzintersektion::limitgeoconnectoriterators()","keine geoconnectoriteratoren vorhanden...");
                                                                };
                                                                geoconnectoriteratordistancelist.loeschenmarkiert();
                                                                //************** DEBUG *****************
                                                                // _vektor4<_to> col;
                                                                // col.setzen(0.4,0.4,1,0);
                                                                //if(geoconnectoriteratordistancelist.anfang(git))do{
                                                                // git->visualisieren(col);
                                                                //}while(geoconnectoriteratordistancelist.naechstes(git));
                                                                //debuganimation();
                                                                //**************************************
};

void _modifikationnetzintersektion::sortalphageoconnectoriterators(_polygon*p){
                                                                //da alle geoconnectoriteratoren zu diesem zeitpunkt nur
                                                                //direkt benachbarte geoconnectoren oder singularer geoconnectoren referenzieren, kann der
                                                                //statistische mittelpunkt mit den mittelpunkten der ersten zwei gits (einschließlich start)
                                                                //bestimmt werden und auch die alpha-bestimmung durchgeführt
                                                                //werden
                                                                _vektor3<_tg> m;
                                                                _vektor3<_tg> v;
                                                                _tg alpha;
                                                                _tg c;
                                                                _verbindergeometrischiterator*git;
                                                                unsigned int i;
                                                                //----------------
                                                                geoconnectoriteratoralphalist.loeschen();
                                                                c=0;
                                                                m.setzen(0,0,0);
                                                                if(geoconnectoriteratordistancelist.anfang(git)){
                                                                 for(i=0;i<2;i++){
                                                                  m+=git->mitte();
                                                                  c++;
                                                                  git=git->naechstes();
                                                                 };
                                                                 m*=1/c;
                                                                 if(geoconnectoriteratordistancelist.anfang(git))do{
                                                                  v=git->mitte()-m;
                                                                  alpha=p->berechnenalpha(v);
                                                                  new _verbindergeometrischiterator(&geoconnectoriteratoralphalist,alpha,0,git->geoconnector(0),git->geoconnector(1));
                                                                 }while(geoconnectoriteratordistancelist.naechstes(git));
                                                                }else{
                                                                 fehler("void _modifikationnetzintersektion::sortalphageoconnectoriterators(_polygon*p,_verbindergeometrischiterator*start)","keine geoconnectoriteratoren vorhanden");
                                                                };
                                                                //************** DEBUG *****************
                                                                //_vektor4<_to> col;
                                                                //_to dec=1/(geoconnectoriteratoralphalist.anzahl()+1);
                                                                //col.setzen(1,1,1,0);
                                                                //if(geoconnectoriteratoralphalist.anfang(git))do{
                                                                // git->visualisieren(col);
                                                                // col.sub(2,dec);
                                                                // col.sub(1,dec);
                                                                // col.sub(0,dec);
                                                                //}while(geoconnectoriteratoralphalist.naechstes(git));
                                                                //debuganimation();
                                                                //**************************************
};

char _modifikationnetzintersektion::searchvalidpartition(_polygon*p,_ringpartition*rp){
                                                                char ok;
                                                                char error;
                                                                unsigned int localmaxgitentry;
                                                                _verbindergeometrischiterator*git;
                                                                _verbindergeometrischiterator*oit;
                                                                //--------
                                                                ok=0;
                                                                error=0;
                                                                localmaxgitentry=maxgitentry;
                                                                do{
                                                                 ok=checkpartitionisvalid(p,rp);
                                                                 if(ok==0){
                                                                  localmaxgitentry--;
                                                                  if(localmaxgitentry==1) {
                                                                   error=1;
                                                                  }else{
                                                                   if(geoconnectoriteratordistancelist.anzahl()<=2){
                                                                    error=1;
                                                                   }else{
                                                                    geoconnectoriteratordistancelist.erstes()->vorheriges()->loeschmarkierung(true);
                                                                    geoconnectoriteratordistancelist.loeschenmarkiert();
                                                                    limitgeoconnectoriterators(localmaxgitentry);
                                                                    sortalphageoconnectoriterators(p);
                                                                   };
                                                                  };
                                                                 };
                                                                }while((ok==0)&&(error==0));
                                                                if(error==1) {
                                                                 ok=0;
                                                                 error=0;
                                                                 geoconnectoriteratorrawlist.anfang(oit);
                                                                 geoconnectoriteratorrawlist.anfang(git);
                                                                 geoconnectoriteratorrawlist.naechstes(oit);
                                                                 do{
                                                                  geoconnectoriteratoralphalist.loeschen();
                                                                  new _verbindergeometrischiterator(&geoconnectoriteratoralphalist,git);
                                                                  new _verbindergeometrischiterator(&geoconnectoriteratoralphalist,oit);
                                                                  ok=checkpartitionisvalid(p,rp);
                                                                  if(ok==0){
                                                                   geoconnectoriteratorrawlist.naechstes(oit);
                                                                   if(oit==git){
                                                                    error=1;
                                                                    ok=0;
                                                                   };
                                                                  };
                                                                 }while((ok==0)&&(error==0));
                                                                 //schreiben("searchaildpartition error");
                                                                };
                                                                //********* DEBUG ************
                                                                //if(ok){
                                                                // _win::_pclautsprecher ss;
                                                                // ss.peep(10000);
                                                                //};
                                                                //****************************
                                                                if(error==1) ok=0;
                                                                return(ok);
};

char _modifikationnetzintersektion::checkpartitionisvalid(_polygon*p,_ringpartition*rp){
                                                                //globale analytische cover funktion liefert 1 wenn
                                                                //die partition, die durch geoconnectoriteratoren beschrieben wird
                                                                //convex ist und keinen schnitt mit einer anderen komponente der
                                                                //ringpartition vorliegt
                                                                char r;
                                                                // *****DEBUG*****
                                                                //_vektor4<_to> col;
                                                                //col.setzen(1,0,0,0);
                                                                //rp->visualisieren();
                                                                // ***************
                                                                //------------------------
                                                                r=0;
                                                                if(getpartitionsequence()){
                                                                 //if(dbscreen) dbscreen->schreiben("partitionsequenz strukturell gueltig",col);
                                                                 if(checkpartitionisconvex(p)){
                                                                 //if(dbscreen) dbscreen->schreiben("partitionsequenz konvex",col);
                                                                  if(checkpartitionhasnohit(p,rp)){
                                                                   //if(dbscreen) dbscreen->schreiben("partitionsequenz schnittfrei",col);
                                                                   r=1;
                                                                  };
                                                                 };
                                                                };
                                                                // ****** DEBUG ******
                                                                //rp->unvisualisieren();
                                                                // *******************
                                                                return(r);
};

char _modifikationnetzintersektion::getpartitionsequence(){
                                                                _verbindergeometrischiterator*git;
                                                                _verbindergeometrisch*g0;
                                                                _verbindergeometrisch*g1;
                                                                _verbindergeometrisch*gs;
                                                                _liste<_ringsektion >*sequence=partitionsequence;
                                                                _liste<_ringsektion > vergleichen;
                                                                char r;
                                                                //--------------------
                                                                r=0;
                                                                sequence->aushaengen();
                                                                if(geoconnectoriteratoralphalist.anfang(git))do{
                                                                 g0=git->geoconnector(0);
                                                                 g1=git->geoconnector(1);
                                                                 if(g0==g1){
                                                                  //dann muss es mindestens einen weiteren
                                                                  //iterator geben, dessen g0!=g1 ist,
                                                                  //oder mehrere weitere singulare iteratoren
                                                                  sequence->einhaengen(g0->ringsection);
                                                                  vergleichen.einhaengenunredundant(g0->ringsection);
                                                                 }else{
                                                                  //dann convexität weiter mit vorheriges-struktur überprüfen,
                                                                  //wichtig : die geoconnectoriteratoren müssen ihren ring
                                                                  //einigermaßen geometrie-repräsentativ halten, sonst wird die
                                                                  //convexbedingung bei mehr als drei Iteratoren eher
                                                                  //zufällig richtig liegen
                                                                  gs=g1;
                                                                  do{
                                                                   sequence->einhaengen(gs->ringsection);
                                                                   vergleichen.einhaengenunredundant(gs->ringsection);
                                                                   gs=gs->getgeoconnector(0);
                                                                  }while(gs!=g0);
                                                                  sequence->einhaengen(gs->ringsection);
                                                                  vergleichen.einhaengenunredundant(gs->ringsection);
                                                                 };
                                                                }while(geoconnectoriteratoralphalist.naechstes(git));
                                                                if(sequence->anzahl()>2){
                                                                 if(sequence->anzahl()==vergleichen.anzahl()){
                                                                  r=1;
                                                                 };
                                                                };
                                                                //************************* DEBUG ******************************
                                                                //_vektor4<_to> col;
                                                                //_vektor3<_tg> off;
                                                                //_listenknoten<_ringsektion >*rit;
                                                                //_listenknoten<_ringsektion >*rin;
                                                                //_liste<_weltdebugpfeil > ll;
                                                                //col.setzen(0,1,0,0);
                                                                //if(sequence->anfang(rit))do{
                                                                // off=*rit->objekt()->ringpartition->poly;
                                                                // off*=0.2;
                                                                // rin=rit->naechstes();
                                                                // ll.einhaengen(
                                                                // new _weltdebugpfeil(DW,
                                                                // rit->objekt()->intersektion->ort()+off,
                                                                // rin->objekt()->intersektion->ort()+off,
                                                                // 0.09,0.01,col
                                                                // ));
                                                                //}while(sequence->naechstes(rit));
                                                               // debuganimwait();
                                                               // ll.loeschen();
                                                                //**************************************************************
                                                                return(r);
};

void _modifikationnetzintersektion::spreadpartition(_polygon*p,_ringpartition*rp){
                                                                //wenn die entsprechenden schalter gesetzt sind, versucht diese funktion
                                                                //die partition in geometrischer vorheriges- und naechstes-richtung zu verbreitern
                                                                _verbindergeometrischiterator*giit;
                                                                char loop;
                                                                char snt;
                                                                char spt;
                                                                //-------------------
                                                                geoconnectoriteratoralphalist.anfang(giit);
                                                                if(giit->naechstes()==giit){
                                                                 snt=1;
                                                                 spt=1;   
                                                                }else{
                                                                 snt=spreadnexttry;
                                                                 spt=spreadprevtry;
                                                                };
                                                                if(snt){
                                                                 //******************* DEBUG *********************
                                                                 //schreiben("geoconnectoriteratoralphalist->anzahl() : ",(int)geoconnectoriteratoralphalist.anzahl());
                                                                 //_win::_pclautsprecher sss;
                                                                 //_vektor4<_to> col;
                                                                 //col.setzen(1,1,0,0);
                                                                 //sss.peep(1000);
                                                                 //if(geoconnectoriteratoralphalist.anfang(giit))do{
                                                                 // giit->visualisieren(col);
                                                                 //}while(geoconnectoriteratoralphalist.naechstes(giit));
                                                                 //debuganimation();
                                                                 //***********************************************
                                                                 if(geoconnectoriteratoralphalist.anfang(giit))do{
                                                                  loop=1;
                                                                  do{
                                                                   if(giit->spread(0)){//try naechstes
                                                                    if(checkpartitionisvalid(p,rp)==0){
                                                                     loop=0;
                                                                     giit->contract(0);//no success
                                                                     getpartitionsequence();
                                                                    };
                                                                   }else{
                                                                    loop=0;
                                                                   };
                                                                  }while(loop);
                                                                 }while(geoconnectoriteratoralphalist.naechstes(giit));
                                                                };
                                                                if(spt){
                                                                 if(geoconnectoriteratoralphalist.anfang(giit))do{
                                                                  loop=1;
                                                                  do{
                                                                   if(giit->spread(1)){//try vorheriges
                                                                    if(checkpartitionisvalid(p,rp)==0){
                                                                     loop=0;
                                                                     giit->contract(1);//no success
                                                                     getpartitionsequence();
                                                                    };
                                                                   }else{
                                                                    loop=0;
                                                                   };
                                                                  }while(loop);
                                                                 }while(geoconnectoriteratoralphalist.naechstes(giit));
                                                                };
};


char _modifikationnetzintersektion::checkpartitionisconvex(_polygon*p){
                                                                //die funktion prüft nicht nur, ob die partitionssequenz konvex ist, 
                                                                //sondern auch ob sie auf der richtigen seite liegt
                                                                char valid;
                                                                _listenknoten<_ringsektion >*rit;
                                                                _listenknoten<_ringsektion >*rin;
                                                                _listenknoten<_ringsektion >*iit;
                                                                _vektor3<_tg> v;
                                                                _vektor3<_tg> a;
                                                                _vektor3<_tg> b;
                                                                _vektor3<_tg> m;
                                                                _tg c;
                                                                _tg D;
                                                                _tg al;
                                                                _tg ao;
                                                                _ringsektion*rsm;
                                                                _ringsektion*rs0;
                                                                _ringsektion*rs1;
                                                                _verbindergeometrisch*git;
                                                                _verbindergeometrisch*git0;
                                                                //_verbindergeometrisch*git1;
                                                                _vektor3<_tg> n;
                                                                //------------------------
                                                                valid=1;
                                                                //konvexität prüfen
                                                                if(partitionsequence->anzahl()>3){
                                                                 if(partitionsequence->anfang(rit))do{
                                                                  rin=rit->naechstes();
                                                                  v=rin->objekt()->intersektion->ort()-rit->objekt()->intersektion->ort();
                                                                  v.normalisieren();
                                                                  a=v% p->normale();
                                                                  a.normalisieren();
                                                                  D=V3.determinieren(p->normale(),v,a);
                                                                  ao=0;
                                                                  if(partitionsequence->anfang(iit))do{
                                                                   if((iit!=rit)&&(iit!=rin)){
                                                                    al=V3.determinieren(p->normale(),v,iit->objekt()->intersektion->ort()-rit->objekt()->intersektion->ort())/D;
                                                                    if(al>+nahenull){
                                                                     if(ao==-1) valid=0; else ao=+1;
                                                                    }else
                                                                    if(al<-nahenull){
                                                                     if(ao==+1) valid=0; else ao=-1;
                                                                    };
                                                                   };
                                                                  }while((partitionsequence->naechstes(iit))&&(valid==1));
                                                                 }while((partitionsequence->naechstes(rit))&&(valid==1));
                                                                };
                                                                if(valid){
                                                                 //prüfen, ob die lage der konvexen partitionsequenz gültig ist
                                                                 //mittelpunkt der partitionssequenz bestimmen 
                                                                 m.setzen(0,0,0);
                                                                 c=0;
                                                                 if(partitionsequence->anfang(rit))do{
                                                                  c+=1;
                                                                  m+=rit->objekt()->intersektion->ort();
                                                                 }while(partitionsequence->naechstes(rit));
                                                                 m*=1/c;
                                                                 //mit hilfe der geoconnector-normalen prüfen, ob
                                                                 //die partitionssequenz gültig ist, vorsicht: die 
                                                                 //geoconnector-normalen sind 2d
                                                                 if(partitionsequence->anfang(rit))do{
                                                                  rsm=rit->objekt();
                                                                  rs0=rit->naechstes()->objekt();
                                                                  rs1=rit->vorheriges()->objekt();
                                                                  //besitzt rsm einen geoconnector der auf rs0
                                                                  //zeigt?
                                                                  git0=0;
                                                                  if(rsm->anfang(git))do{
                                                                   if(git->geoconnector[0]->ringsection==rs0){
                                                                    git0=git;
                                                                   }else if(git->geoconnector[1]->ringsection==rs0){
                                                                    git0=git->geoconnector[1];
                                                                   };
                                                                  }while((rsm->naechstes(git))&&(git0==0));
                                                                  if(git0){
                                                                   //es wurde festgestellt, dass rsm-rs0 eine Kante ist,
                                                                   //an welcher die position der Partition auf gültigkeit
                                                                   //geprüft werden kann,d.h den mittelpunkt m - git->mitte (2d)
                                                                   //mit dem geoconnectornormlenvektor vergleichen
                                                                   n=m-git0->mitte;
                                                                   n.normalisieren();
                                                                   n+=git0->normale;
                                                                   if(n.laenge()<sqrt(2.0f)) valid=0;
                                                                  }else{
                                                                   //zwischen rsm und rs0 existiert keine geometrische Verbindung.
                                                                   //von rsm ausgehend, nun alle geometrischen Verbindungen erfassen und
                                                                   //deren Mittelpunkte darauf hin prüfen, ob sie in der Partitionsequenz
                                                                   //liegen oder nicht
                                                                   if(rsm->anfang(git))do{
                                                                    b=git->geoconnector[0]->ringsection->intersektion->ort()-rsm->intersektion->ort();
                                                                    b*=0.5;
                                                                    b+=rsm->intersektion->ort();
                                                                    if(checkpartitionisuncovered(p,b,m)==0) valid=0;
                                                                   }while((rsm->naechstes(git))&&(valid==1));
                                                                  };
                                                                 }while((partitionsequence->naechstes(rit))&&(valid==1));
                                                                };
                                                                return(valid);
};

char _modifikationnetzintersektion::checkpartitionhasnohit(_polygon*p,_ringpartition*rp){
                                                                char r;
                                                                _liste<_ringsektion >*seq=partitionsequence;
                                                                _listenknoten<_ringsektion >*rsit;
                                                                //---------
                                                                r=checkpartitionisuncovered(p,rp);

                                                                if(r){
                                                                 // *****DEBUG*****
                                                                 //_vektor4<_to> col;
                                                                 //col.setzen(1,0,0,0);
                                                                 //if(dbscreen) dbscreen->schreiben("partitionsequenz unbedeckt",col);
                                                                 // ***************
                                                                 rp->flaggeoconnector(0);    
                                                                 if(seq->anfang(rsit))do{
                                                                  r=checkpartitionhasnohit(p,rp,rsit->objekt(),rsit->naechstes()->objekt());
                                                                 }while((r)&&(seq->naechstes(rsit)));
                                                                 
                                                                };
                                                                return(r);
};

char _modifikationnetzintersektion::checkpartitionhasnohit(_polygon*p,_ringpartition*rp,_ringsektion*r0,_ringsektion*r1){
                                                                char r;
                                                                _ringsektion*rit;
                                                                _verbindergeometrisch*git;
                                                                _verbindergeometrisch*ggit;
                                                                _verbindergeometrisch*ggin;
                                                                _ringsektion*or0;
                                                                _ringsektion*or1;
                                                                int oldflag;
                                                                int newflag;
                                                                //---------
                                                                r=1;
                                                                if(rp->anfang(rit)){
                                                                 if(rit->anfang(git)){
                                                                  oldflag=git->markierung;
                                                                 }else{
                                                                  fehler("checkpartitionhasnohit(_polygon*p,_ringpartition*rp,_ringsektion*r0,_ringsektion*r1) : rit besitzt keinen geoconnector.");
                                                                 };
                                                                }else{
                                                                 fehler("checkpartitionhasnohit(_polygon*p,_ringpartition*rp,_ringsektion*r0,_ringsektion*r1) : rp besitzt keine ringsektionen.");
                                                                };
                                                                newflag=1-oldflag;
                                                                if(rp->anfang(rit))do{
                                                                 if(rit->anfang(git))do{
                                                                  if(git->markierung!=newflag){
                                                                   ggit=git;
                                                                   do{
                                                                    ggin=ggit->getgeoconnector(0);
                                                                    or0=ggit->ringsection;
                                                                    or1=ggin->ringsection;
                                                                    if((or0!=r0)&&(or0!=r1)&&(or1!=r0)&&(or1!=r1)){
                                                                     r=checkpartitionhasnohit(p,r0->intersektion,r1->intersektion,or0->intersektion,or1->intersektion);  
                                                                    };
                                                                    ggit->markierung=newflag;
                                                                    ggit=ggin;
                                                                   }while((ggit!=git)&&(r));
                                                                  };
                                                                 }while((rit->naechstes(git))&&(r));
                                                                }while((rp->naechstes(rit))&&(r));
                                                                return(r);
};

char _modifikationnetzintersektion::checkpartitionhasnohit(_polygon*p,_intersektion*i0,_intersektion*i1,_intersektion*o0,_intersektion*o1){
                                                                //funktion prüft, ob die gerade i0-i1 einen
                                                                //diskreten schnitt mit der geraden o0-o1 aufweist
                                                                char r;
                                                                _tg a,b,D;
                                                                _vektor2<_tg> e;
                                                                _vektor2<_tg> x;
                                                                _vektor2<_tg> o;
                                                                _vektor2<_tg> va;
                                                                _vektor2<_tg> vb;
                                                                int c0,c1;
                                                                bool schraeg;
                                                                //-----------
                                                                c0=p->groessterindex(0);
                                                                c1=p->groessterindex(1);
                                                                r=1;
                                                                va.setzen(i1->ort()[c0]-i0->ort()[c0],i1->ort()[c1]-i0->ort()[c1]);
                                                                vb.setzen(-(o1->ort()[c0]-o0->ort()[c0]),-(o1->ort()[c1]-o0->ort()[c1]));
                                                                D=V2.determinieren(va,vb);
                                                                if(fabs(D)>=nahenull){//schräglage
                                                                 schraeg=true;
                                                                 e.setzen(o0->ort()[c0]-i0->ort()[c0],o0->ort()[c1]-i0->ort()[c1]);
                                                                 a=V2.determinieren(e,vb)/D;
                                                                 if((a>=0)&&(a<=1)){
                                                                  b=V2.determinieren(va,e)/D;
                                                                  if((b>=0)&&(b<=1)){
                                                                   r=0;
                                                                  };
                                                                 };
                                                                }else{//parallelität
                                                                 schraeg=false;
                                                                 x.setzen(o0->ort()[c0]-i0->ort()[c0],o0->ort()[c1]-i0->ort()[c1]);
                                                                 o.setzen(0,0);
                                                                 getlotpointline2d(x,o,va,e);
                                                                 a=e.laenge();
                                                                 if(a<=nahenull){
                                                                  getlineparameter2d(x,o,va,a);
                                                                  if((a>=0)&&(a<=1)) r=0;
                                                                  x.setzen(o1->ort()[c0]-i0->ort()[c0],o1->ort()[c1]-i0->ort()[c1]);
                                                                  getlineparameter2d(x,o,va,b);
                                                                  if((b>=0)&&(b<=0)) r=0;
                                                                 };
                                                                };
                                                                // *************** DEBUG : schnittgeradensituation *********
                                                                /*_vektor4<_to> col;
                                                                if(r==0) {
                                                                 col.setzen(1,0,0,0);
                                                                 if(dbscreen) dbscreen->schreiben("diese szene hat einen schnittpunkt",col);
                                                                }else{
                                                                 col.setzen(1,1,0,0);
                                                                 if(dbscreen) dbscreen->schreiben("diese szene hat keinen schnittpunkt",col);
                                                                };
                                                                if(schraeg) {
                                                                 if(dbscreen) dbscreen->schreiben("schraeg bestimmt",col);
                                                                }else{
                                                                 if(dbscreen) dbscreen->schreiben("parallel bestimmt",col);
                                                                };
                                                                _weltdebugpfeil*a0;
                                                                _weltdebugpfeil*a1;
                                                                a0=new _weltdebugpfeil(W,i0->ort(),i1->ort(),0.02,0.01,col);
                                                                a1=new _weltdebugpfeil(W,o0->ort(),o1->ort(),0.02,0.01,col*0.6f);
                                                                debuganimwait();
                                                                delete a0;
                                                                delete a1;*/
                                                                // *********************************************************
                                                                return(r);
};

char _modifikationnetzintersektion::checkpartitionisuncovered(_polygon*p,_ringpartition*rp){
                                                                char r;
                                                                char ok;
                                                                _vektor3<_tg> mitte;//[3];
                                                                _tg anzahl;
                                                                _liste<_ringsektion >*seq=partitionsequence;
                                                                _listenknoten<_ringsektion >*rs;
                                                                _ringsektion*rit;
                                                                _intersektion*iit;
                                                                _verbindergeometrisch*gi;
                                                                _verbindergeometrisch*git;
                                                                _verbindergeometrisch*gin;
                                                                
                                                                //-------------
                                                                rp->flaggeoconnector(0);
                                                                anzahl=0;
                                                                mitte.setzen(0,0,0);
                                                                //setzen(0.0f,0.0f,0.0f,mitte);
                                                                if(seq->anfang(rs))do{
                                                                 mitte+=rs->objekt()->intersektion->ort();
                                                                 //add(seq->it->objekt->intersektion->o,mitte);
                                                                 anzahl++;
                                                                }while(seq->naechstes(rs));
                                                                if(anzahl){
                                                                 mitte*=1/anzahl;//mul(1.0f/anzahl,mitte);
                                                                }else{
                                                                 fehler("char _modifikationnetzintersektion::checkpartitionisuncovered(_polygon*,_ringpartition*,_liste<_ringsektion >*)","anzahl==0");
                                                                };
                                                                //--------------
                                                                r=1;
                                                                //rit=rp->firstringsection;
                                                                if(rp->anfang(rit))do{
                                                                
                                                                 iit=rit->intersektion;
                                                                 ok=1;
                                                                 if(seq->anfang(rs))do{
                                                                  if(rs->objekt()->intersektion==iit) ok=0;
                                                                  //if(seq->it->objekt->intersektion==iit) ok=0;
                                                                 }while((ok)&&(seq->naechstes(rs)));
                                                                 //valid intersektion iit , mitte - deteriminaten statusüberprüfung
                                                                 if(ok){
                                                                  r=checkpartitionisuncovered(p,iit->ort(),mitte);
                                                                  //if(r){
                                                                  // r=checkpartitionisuncovered(p,(iit->ort()+rit->naechstes()->intersektion->ort())*0.5,mitte);
                                                                  //};
                                                                 };
                                                                 //rit=rit->naechstes;
                                                                }while((rp->naechstes(rit))&&(r));
                                                                //if(r==0) peep(10000);
                                                                if(r){
                                                                 rp->flaggeoconnector(1);
                                                                 if(rp->anfang(rit))do{
                                                                  if(rit->anfang(gi))do{
                                                                   if(gi->markierung==1){
                                                                    git=gi;
                                                                    do{
                                                                     gin=git->geoconnector[0];
                                                                     git->markierung=0;

                                                                     ok=1;
                                                                     if(seq->anfang(rs))do{
                                                                      if(rs->objekt()==git->ringsection) ok=0;
                                                                      if(rs->objekt()==gin->ringsection) ok=0;
                                                                      //if(seq->it->objekt->intersektion==iit) ok=0;
                                                                     }while((ok)&&(seq->naechstes(rs)));
                                                                     if(ok) r=checkpartitionisuncovered(p,(git->ringsection->intersektion->ort()+gin->ringsection->intersektion->ort())*0.5,mitte); 
                                                                     git=gin;
                                                                    }while((git!=gi)&&(r==1));
                                                                   };
                                                                  }while((rit->naechstes(gi))&&(r==1));
                                                                 }while((rp->naechstes(rit))&&(r==1));
                                                                };
                                                                return(r);
                                                                
};

char _modifikationnetzintersektion::checkpartitionisuncovered(_polygon*p,_vektor3<_tg> test,_vektor3<_tg>&mitte){
                                                                char r;
                                                                char innen;
                                                                _vektor2<_tg> va;
                                                                _vektor2<_tg> vb;
                                                                _vektor2<_tg> e;
                                                                _tg b,D;
                                                                _liste<_ringsektion >*seq=partitionsequence;
                                                                _listenknoten<_ringsektion >*rs;
                                                                _intersektion*i0;
                                                                _intersektion*i1;
                                                                int c0,c1;
                                                                //----------
                                                                c0=p->groessterindex(0);
                                                                c1=p->groessterindex(1);
                                                                r=1;
                                                                innen=1;
                                                                if(seq->anfang(rs))do{
                                                                 i0=rs->objekt()->intersektion;
                                                                 i1=rs->naechstes()->objekt()->intersektion;
                                                                 va.setzen(
                                                                 i1->ort()[c0]-i0->ort()[c0],
                                                                 i1->ort()[c1]-i0->ort()[c1]);
                                                                 //va[0]=i1->o[c0]-i0->o[c0];
                                                                 //va[1]=i1->o[c1]-i0->o[c1];
                                                                 vb.setzen(
                                                                 mitte[c0]-i0->ort()[c0],
                                                                 mitte[c1]-i0->ort()[c1]);
                                                                 //vb[0]=mitte[c0]-i0->o[c0];
                                                                 //vb[1]=mitte[c1]-i0->o[c1];
                                                                 D=V2.determinieren(va,vb);
                                                                 if(D){
                                                                  e.setzen(
                                                                  test[c0]-i0->ort()[c0],
                                                                  test[c1]-i0->ort()[c1]);
                                                                  //e[0]=iit->o[c0]-i0->o[c0];
                                                                  //e[1]=iit->o[c1]-i0->o[c1];
                                                                  b=V2.determinieren(va,e)/D;
                                                                  if(b<0) innen=0;
                                                                 }else{
                                                                  //fehler("char _modifikationnetzintersektion::checkpartitionisuncovered(_liste<_ringsektion >*seq,_intersektion*iit,_tg*mitte)","Hauptdeterinante in 2D ist 0");
                                                                 };
                                                                }while((innen)&&(seq->naechstes(rs)));
                                                                r=1-innen;
                                                                return(r);
};

void _modifikationnetzintersektion::createpoly(_polygon*p,_ringpartition*rp,_liste<_polygon >*neuepoly){
                                                                //funktion legt ein neues poly an, welches über die geoconnectoriterator-
                                                                //partitionsequence gelegt wird
                                                                _listenknoten<_ringsektion >*rs;
                                                                _ringsektion*ringsection;
                                                                _intersektion*intersektion;
                                                                _polygon*np;
                                                                _vertex*nv;
                                                                _vertex*nextnv;
                                                                _verbindervertexpolygon*nvcp;
                                                                _vektor3<_tg> o;
                                                                _vektor3<_tg> t;
                                                                _tg l;
                                                                _verbindergeometrisch*git;
                                                                //------------------------
                                                                //struktur verbiegen / destruieren / erweitern
                                                                performconnectorstruct();
                                                                //************** DEBUG ************
                                                                //schreiben("createpoly : rp-visualizierung.");
                                                                //rp->visualisieren();
                                                                //debuganimwait();
                                                                //rp->unvisualisieren();
                                                                //*********************************
                                                                //polygon anlegen
                                 np=new _polygon(p);//np=new _polygon(meshtointersect);
                                 np->einhaengen(meshtointersect);
                                                               // ahctung änderung 16.05.06 : entfernung von pflip : vorher :np->ausrichtung(p->ausrichtung());
                                                                np->status(+2);
                                                                //um vor dieser algorithmik zu schützen
                                                                //vertex anlegen
                                                                if(partitionsequence->anfang(rs))do{
                                                                 ringsection=rs->objekt();
                                                                 intersektion=ringsection->intersektion;
                                                                 if(intersektion->vertex==0){
                                                                  o=intersektion->ort();//-*meshtointersect;
                                                                  intersektion->vertex=new _vertex(meshtointersect/*p->netz()*/,o);
                                                                 };
                                                                }while(partitionsequence->naechstes(rs));
                                                                //vcp anlegen
                                                                if(partitionsequence->anfang(rs))do{
                                                                 nv=rs->objekt()->intersektion->vertex;
                                                                 //poly-firstvertex explizit ausrichten, 
                                                                 //falls kein neuer vertex oben angelegt wurde
                                                                 //if(np->vertex()==0) np->vertex(nv);
                                                                 nextnv=rs->naechstes()->objekt()->intersektion->vertex;
                                                                 nvcp=new _verbindervertexpolygon(nv,np);//,nextnv);
                                                                }while(partitionsequence->naechstes(rs));
                                                                // ************ DEBUG : testiteration ***************
                                                                //schreiben("denbugiteration wird gestartet");                                                                                        
                                                                //nv=np->vertex();
                                                                //if(nv)do{
                                                                // schreiben("vertex-debugiteration : ",(int)nv);
                                                                // nv=nv->naechstes(np);
                                                                //}while(nv!=np->vertex());
                                                                // **************************************************
                                                                np->aktualisieren();
                                                                //normalen angleichen, neues poly updaten
                                                                if(plog) schreiben("_modifikationnetzintersektion::Polygon wurde angelegt.");
                                                                t=p->normale()+np->normale();//add(p->normale->o,np->normale->o,t);
                                                                l=t.laenge();
                                                                if(l<1){
                                                                 np->invertieren();
                                                                };
                                                                //ahctung änderung 16.05.06 : entfernung von pflip : vorher :np->ausrichtung(np->ausrichtung()*invertnormalstatus(thismesh) );
                                                                if(invertnormalstatus(thismesh)==-1) np->invertieren();
                                                                
                                                                //texturecoordinaten interpolieren
                                                // np->textur(p->textur());
                                                                interpolatetexturecoordinates(p,np);
                                                                if(p->hatdreieck()) np->erzeugendreieck();
                                                                np->aktualisieren();  
                                                                neuepoly->einhaengen(np);
                                                                //ringsection ohne geocnnector löschen
                                                                if(plog) schreiben("_modifikationnetzintersektion::ringsektionsdestruktion wird ausgeführt.");
                                                                if(partitionsequence->anfang(rs))do{
                                                                 ringsection=rs->objekt();
                                                                 if(ringsection->anfang(git)==false){
                                                                  rs->loeschmarkierungobjekt(true);
                                                                 };
                                                                }while(partitionsequence->naechstes(rs));
                                                                //partitionsequencen aushängen
                                                                partitionsequence->loeschenmarkiert();
                                                                partitionsequence->aushaengen();
                                                                //************* DEBUG ******************
                                                                //_win::_pclautsprecher ss;
                                                                //ss.peep(10000);
                                                                //debuganimation();
                                                                //**************************************
};

void _modifikationnetzintersektion::performconnectorstruct(){
                                                                _verbindergeometrischiterator*git;
                                                                _verbindergeometrisch*g0;
                                                                _verbindergeometrisch*g1;
                                                                _verbindergeometrisch*gs;
                                                                _verbindergeometrisch*gn;
                                                                _verbindergeometrisch*old;
                                                                char v0;
                                                                char v1;
                                                                _liste<_verbindergeometrisch > conseq;
                                                                _listenknoten<_verbindergeometrisch >*cit;
                                                                //------------------------
                                                                if(plog) schreiben("_modifikationnetzintersektion::bearbeiten der Verbundstruktur beginnt.");
                                                                if(geoconnectoriteratoralphalist.anfang(git))do{
                                                                 g0=git->geoconnector(0);
                                                                 g1=git->geoconnector(1);
                                                                 if(g0==g1){
                                                                  conseq.einhaengenunredundant(g0);
                                                                 }else{
                                                                  gs=g1;
                                                                  do{
                                                                   conseq.einhaengenunredundant(gs);
                                                                   gs=gs->getgeoconnector(0);
                                                                  }while(gs!=g0);
                                                                  conseq.einhaengenunredundant(g0);
                                                                 };
                                                                }while(geoconnectoriteratoralphalist.naechstes(git));
                                                                geoconnectoriteratoralphalist.loeschen();
                                                                //**************** DEBUG : vis. von conseq ***************
                                                               // _liste<_weltdebugpfeil > la;
                                                               // _vektor3<_tg> x;
                                                               // _vektor3<_tg> y;
                                                               // _vektor4<_to> col;
                                                               // _tg ccc=1;
                                                               // if(conseq.anfang(cit))do{
                                                               //  y=cit->objekt()->ringsection->intersektion->ort();
                                                               //  x=y+ *cit->objekt()->ringsection->ringpartition->poly * ccc;
                                                               //  col.setzen(0,0.5,1,0);
                                                               //  la.einhaengen(new _weltdebugpfeil(DW,x,y,0.3,0.2,col));
                                                               //  ccc+=1;
                                                               // }while(conseq.naechstes(cit));
                                                               // debuganimation();
                                                               // la.loeschen();
                                                                //*******************************************************
                                                                //den status der geoconnectoren bestimmen :
                                                                //es gibt fünf berschiedene zustände :
                                                                //1. totalkohärenz
                                                                //2. singularität
                                                                //3. inkohärenz
                                                                //4. naechstes-kohärenz
                                                                //5. vorheriges-kohärenz
                                                                if(conseq.anfang(cit))do{
                                                                 g1=cit->vorheriges()->objekt();
                                                                 gs=cit->objekt();
                                                                 g0=cit->naechstes()->objekt();
                                                                 if(gs->geoconnector[0]==g0) v0=1; else v0=0;
                                                                 if(gs->geoconnector[1]==g1) v1=1; else v1=0;
                                                                 gs->markierung=0;
                                                                 if((v0)&&(v1)){
                                                                  //geoconnector ist totalkoherent mit connectorsequenz
                                                                  //und wird im anschluss gelöscht
                                                                  gs->markierung=1;
                                                                 }else
                                                                 if((v0==0)&&(v1==0)){
                                                                  if(gs->geoconnector[0]==gs){
                                                                   //es liegt ein singularer geoconnector vor
                                                                   gs->markierung=2;
                                                                  }else{
                                                                   //geoconnector ist inkoherent mit der connectorsequenz
                                                                   gs->markierung=3;
                                                                  };
                                                                 }else
                                                                 if((v0==1)&&(v1==0)){
                                                                  //geoconnector ist koherent mit naechstes connector (in sequenz)
                                                                  gs->markierung=4;
                                                                 }else
                                                                 if((v0==0)&&(v1==1)){
                                                                  //geoconnector ist koherent mit vorheriges connector (in sequenz)
                                                                  gs->markierung=5;
                                                                 };
                                                                }while(conseq.naechstes(cit));
                                                                //den oben ermittelten status der geoconnectoren bearbeiten 
                                                                if(conseq.anfang(cit))do{
                                                                 g1=cit->vorheriges()->objekt();
                                                                 gs=cit->objekt();
                                                                 g0=cit->naechstes()->objekt();
                                                                 switch(gs->markierung){
                                                                  case 0:
                                                                   fehler("void _modifikationnetzintersektion::performconnectorstruct()","der status eines geoconnectors konnte nicht bestimmt werden.");
                                                                  case 1:
                                                                   //geoconnector ist totalkoherent mit connectorsequenz
                                                                   //und wird im anschluss gelöscht
                                                                   cit->loeschmarkierungobjekt(true);//gs->loeschenmarkiert=1;
                                                                   break;
                                                                  case 2:
                                                                   //es liegt ein singularer geoconnector vor
                                                                   //hier keine konstruktion durchführen, sondern
                                                                   //nur [0] in naechstes und [1] in vorheriges verbiegen 
                                                                   gs->geoconnector[0]=g0;
                                                                   gs->geoconnector[1]=g1;
                                                                   gs->aktualisieren();
                                                                   break;
                                                                  case 3:
                                                                   //geoconnector ist inkoherent mit der connectorsequenz
                                                                   //[0]- nach vorheriges verbiegen
                                                                   //konstruktion : [0] nach alt [0] ; [1] nach naechstes verbiegen
                                                                   old=gs->geoconnector[0];
                                                                   gs->geoconnector[0]=g1;
                                                                   gs->aktualisieren();
                                                                   gn=new _verbindergeometrisch(gs->ringsection,old,g0);
                                                                   gn->geoconnector[1]->geoconnector[0]=gn;
                                                                   gn->geoconnector[0]->geoconnector[1]=gn;
                                                                   gn->aktualisieren();
                                                                   gn->geoconnector[1]->aktualisieren();
                                                                   gn->geoconnector[0]->aktualisieren();
                                                                   g0->markierung=6;
                                                                   break;
                                                                  case 4:
                                                                   //geoconnector ist koherent mit naechstes connector (in sequenz)
                                                                   //[0] nach vorheriges verbiegen, aktualisieren
                                                                   gs->geoconnector[0]=g1;
                                                                   gs->aktualisieren();
                                                                   break;
                                                                  case 5:
                                                                   //geoconnector ist koherent mit vorheriges connector (in sequenz)
                                                                   //[1] nach naechstes verbiegen, kein aktualisieren
                                                                   gs->geoconnector[1]=g0;
                                                                   break;
                                                                  case 6:
                                                                   break;
                                                                 };
                                                                 
                                                                 
                                                                 /*if(gs->geoconnector[0]==g0) v0=1; else v0=0;
                                                                 if(gs->geoconnector[1]==g1) v1=1; else v1=0;
                                                                 if((v0)&&(v1)){
                                                                 }else
                                                                 if((v0==0)&&(v1==0)){
                                                                  if(gs->geoconnector[0]==gs){
                                                                  }else{
                                                                  };
                                                                 }else
                                                                 if((v0==1)&&(v1==0)){
                                                                 }else
                                                                 if((v0==0)&&(v1==1)){
                                                                 };*/
                                                                }while(conseq.naechstes(cit));
                                                                conseq.loeschenmarkiert();
                                                                if(plog) schreiben("_modifikationnetzintersektion::bearbeiten der Verbundstruktur beendet.");

};

void _modifikationnetzintersektion::interpolatetexturecoordinates(_polygon*p,_polygon*np){
                                                                _vertex*nv;
                                                                _listenknoten<_vertex>*lnv;
                                                                _verbindervertexpolygon*nvcp;
                                                                int c0,c1;
                                                                _polygontexturraum*ts=p->texturespace();
                                                                _tg a,b;
                                                                _vektor2<_tg> e;
                                                                _texturvektor<_tg> tva;
                                                                _texturvektor<_tg> tvb;
                                                                //------------------------------------------------------------
                                                                c0=p->groessterindex(0);
                                                                c1=p->groessterindex(1);
                                                                if(ts){
                                                                 //nv=np->vertex();
                                                                 //if(nv)do{
                                                                 iterierenliste(np,lnv,
                                                                  nv=lnv->objekt();
                                                                  //ebenenparameter im ts::weltkoordinaten errechnen
                                                                  e.setzen(nv->ort()[c0],nv->ort()[c1]);
                                                                  e-=ts->mitte;
                                                                  a=V2.determinieren(e,ts->vb)/ts->Dv;
                                                                  b=V2.determinieren(ts->va,e)/ts->Dv;
                                                                  //diese auf die texturekoordinaten beziehen
                                                                  nvcp=static_cast<_verbindervertexpolygon*>(lnv);//=nv->connector(np);
                                                                  tva.kopieren(&ts->tva);
                                                                  tvb.kopieren(&ts->tvb);
                                                                  tva.mul(a);
                                                                  tvb.mul(b);
                                                                  tva.add(&tvb);
                                                                  tva.add(&ts->tvm);
                                                                  nvcp->kopieren(&tva);
                                                                 );
                                                                 // nv=nv->naechstes(np);
                                                                 //}while(nv!=np->vertex());
                                                                }else{
                                                                 fehler("void _modifikationnetzintersektion::interpolatetexturecoordinates(_polygon*p,_polygon*np)","poly p besitzt keinen texturespace");
                                                                };
};
//***********************************************************************   D U P L I C A T I N G  &  D E L E T I N G   **************************************************************************

void _modifikationnetzintersektion::duplicatemesh(){
                                                                _polygon*p;
                                                                //-----------
                                                              
                                                                if(intersectingmesh->anfang(p))do{
                                                                 duplicatepoly(p);
                                                                }while(intersectingmesh->naechstes(p));
};

void _modifikationnetzintersektion::duplicatepoly(_netz*m){
                                                                //diese funktion wird nur für das intersecingmesh aufgerufen
                                                                //dupliziert werden alle poly mit positivem status
                                                                _polygon*p;
                                                                //---------------
                                                                if(m->anfang(p))do{
                                                                 if(p->status()==+1){
                                                                  duplicatepoly(p);
                                                                 };
                                                                }while(m->naechstes(p));
};

void _modifikationnetzintersektion::duplicatepoly(_polygon*p){
                                                                _polygon*np;
                                                                _vertex*v;
                                                                _vertex*nextv;
                                                                _vertex*nv;
                                                                _listenknoten<_vertex>*lnv;
                                                                _verbindervertexpolygon*vcp;
                                                                _verbindervertexpolygon*nvcp;
                                                                _vektor3<_tg> o;//[3];
                                                                //------------
                                                                //poly np anlegen
                                                                if(plog) schreiben("_modifikationnetzintersektion::duplicatepoly(_polygon*p)");
                                              np=new _polygon(p);//np=new _polygon(meshtointersect);
                                              np->einhaengen(meshtointersect);
                                                                np->status(+2);
                                                               // np->maske=p->maske;
                                                                //np->nflip=invertnormalstatus(intersectingmesh)*p->nflip;
                                                                //ahctung änderung 16.05.06 : entfernung von pflip : vorher :np->ausrichtung(invertnormalstatus(intersectingmesh)*p->ausrichtung());
                                                                
                                                                //np->mulflip(p->ausrichtung());
                                                                //poly p iterieren -> vertexen anlegen
                                                                //v=p->vertex();
                                                                //if(v)do{
                                                                iterierenliste(p,lnv,
                                                                 v=lnv->objekt();
                                                                 if(v->intersektion()){
                                                                  nv=v->intersektion()->vertex;
                                                                  if(nv==0) {
                                                                   o=v->intersektion()->ort();//-*meshtointersect;//sub(v->intersektion->o,meshtointersect->ort->o,o);
                                                                   v->intersektion()->vertex=new _vertex(meshtointersect/*p->netz()*/,o);
                                                                   //if(np->vertex()==0) np->vertex(v->intersektion()->vertex);
                                                                   //schreiben("vertex wurde angelegt.");
                                                                  }else{
                                                                   //if(np->vertex()==0) np->vertex(nv);
                                                                  };
                                                                 }else{
                                                                  fehler("void _modifikationnetzintersektion::duplicatepoly(_polygon*p)","v->intersektion nicht gesetzt, keine virtuelle intersektion für vertex v vorhanden.");
                                                                 };
                                                                );
                                                                // v=v->naechstes(p);
                                                                //}while(v!=p->vertex());
                                                                
                                                                //poly p iterieren -> vcp anlegen, dh verbund herstellen zwischen meshtointersect
                                                                //und neuen vertexen, die noch manuell vom intersecting netz verwaltet werden
                                                                //v=p->vertex();
                                                                //if(v)do{
                                                                iterierenliste(p,lnv,
                                                                 v=lnv->objekt();
                                                                 vcp=static_cast<_verbindervertexpolygon*>(lnv);//=v->connector(p);
                                                                 nextv=lnv->naechstes()->objekt();//=v->naechstes(p);
                                                                 nvcp=new _verbindervertexpolygon(v->intersektion()->vertex,np);//,nextv->intersektion()->vertex);
                                                                 nvcp->kopieren(vcp);
                                                                 //if(plog) schreiben("vcp wurde angelegt.");
                                                                );
                                                                // v=nextv;
                                                                //}while(v!=p->vertex());
                                                    //np->textur(p->textur());
                                                                if(p->hatdreieck()) np->erzeugendreieck();
                                                                if(invertnormalstatus(intersectingmesh)==-1) np->invertieren();
                                                                np->aktualisieren();
};

void _modifikationnetzintersektion::destructpoly(_netz*m){
                                                                //funktion wird nur auf das netz to intersekt angewendet
                                                                //hierbei alle negativ und null geflaggten polygone löschen
                                                                //es kann passieren, das von dem meshtointersect nach
                                                                //dieser funktion nichts mehr übrig bleibt -> zeiger nullen
                                                                _polygon*p;
                                                                //------------
                                                               // L->l("POlygonanzahl vor ",(int)m->_listebasis<_polygon>::anzahl());
                                                                if(m->anfang(p))do{
                                                                 if((p->status()==-1)||(p->status()==0)){
															      p->_listenknotenbasis<_polygon>::loeschmarkierung(true);
                                                                 // L->l("POlygon wurde gelöschet");
                                                                 };
                                                                }while(m->naechstes(p));
                                                                m->_listebasis<_polygon >::loeschenmarkiert();
                                                               // L->l("POlygonanzahl nach ",(int)m->_listebasis<_polygon>::anzahl());
};

void _modifikationnetzintersektion::spreadvirtualstatus(_netz*m){
                                                                _polygon*p;
                                                                int inistatus;
                                                                _statussektion*ss;
                                                                _statuskreuz*sc;
                                                                _verbindervertexpolygon*vcp;
                                                                _vertex*vit;
                                                                _listenknoten<_vertex>*lnvit;
                                                                //-------------
                                                                m->markierungvertex(0);    
                                                                if(m->anfang(p))do{
                                                                 if(p->status()==0){
                                                                  //vit=p->vertex();
                                                                  //if(vit)do{
                                                                  iterierenliste(p,lnvit,
                                                                   vit=lnvit->objekt();
                                                                   if(vit->markierung()==0){
                                                                    vit->markierung(1);
                                                                    if(vit->intersektion()){//es handelt sich um eine virtuelle intersektion
                                                                     vit->intersektion()->switchsection(p);
                                                                     vit->intersektion()->anfang(ss);
                                                                     ss->anfang(sc);
                                                                     inistatus=sc->status;
                                                                     //inistatus=vit->intersektion->firststatussection->firststatuscross->status;
                                                                     //koherentes dreieck suchen mit
                                                                     //intersectionstatus ==-2 (uninitialisiert)
                                                                     
                                                                     //if(vit->anfang(vcp))do{
                                                                     _listenknoten<_polygon>*lnp;
                                                                     iterierenliste(vit,lnp,vcp=static_cast<_verbindervertexpolygon*>(lnp);
                                                                      if(vcp->polygon()!=p){
                                                                       if(vcp->polygon()->status()==-2){
                                                                        spreadvirtualstatus(vcp->polygon(),inistatus);
                                                                       };
                                                                      };
                                                                     //}while(vit->naechstes(vcp));
                                                                     );
                                                                    };
                                                                   };
                                                                  );
                                                                  // vit=vit->naechstes(p);
                                                                  //}while(vit!=p->vertex());
                                                                 };
                                                                }while(m->naechstes(p));
};

void _modifikationnetzintersektion::spreadvirtualstatus(_polygon*p,int s){
                                                                _polygon*ps;
                                                                _vertex*v0;
                                                                _vertex*v1;
                                                                _listenknoten<_vertex>*ln;
                                                                //-----------
                                                                p->status(s);
                                                                //v0=p->vertex();
                                                                //if(v0)do{
                                                                iterierenliste(p,ln,
                                                                 v0=ln->objekt();
                                                                 v1=ln->naechstes()->objekt();
                                                                 //v1=v0->naechstes(p);
                                                                 ps=p->nachbar(v0,v1);
                                                                 if(ps)if(ps->status()==-2) spreadvirtualstatus(ps,s);
                                                                );
                                                                // v0=v1;
                                                                //}while(v0!=p->vertex());
};

void _modifikationnetzintersektion::getstatustotalduplicationanddestruction(int&mistatus,int&imstatus){
                                                                //es wurde keine intersektion festgestellt, diese funktion stellt noch sicher, dass
                                                                //die intersecting-poly dupliziertr werden, wenn intersecting netz innerhalb von
                                                                //meshtointersect sich befindet
                                                                _vektor3<_tg> e;
                                                                _vektor3<_tg> o;
                                                                _vektor3<_tg> va;
                                                                _vektor3<_tg> vb;
                                                                _vektor3<_tg> vc;
                                                                _vektor3<_tg> mr;//relativer mittelpunkt
                                                                _vektor3<_tg> s;//schnittpunkt
                                                                _vektor3<_tg> t;
                                                                _tg b,c;//determinanten vektorenparameter
                                                                _tg D;//hauptdeterminante
                                                                _vektor2<_tg> de;//2D - punktvektor
                                                                _vektor2<_tg> da;//2D - ebenevektor 1
                                                                _vektor2<_tg> db;//2D - ebenevektor 2
                                                                _vektor2<_tg> dv;//abs punkt von eit->vertex[0]
                                                                _tg dD;   //2D - hauptdeterminate 
                                                                int c0;
                                                                int c1;
                                                                char innen;
                                                                char r;
                                                                _tg lowc;
                                                                _polygon*lowp;
                                                                _polygon*p;
                                                                _vertex*vit;
                                                                _vertex*vin;
                                                                int anzahl;
                                                                _netz*m[2];
                                                                int n;
                                                                //----------------------------
                                                                m[0]=meshtointersect;
                                                                m[1]=intersectingmesh;
                                                                for(n=0;n<2;n++){
                                                                 anzahl=0;
                                                                 r=0;
                                                                 lowp=0;
                                                                 lowc=1e+6;
                                                                 if(m[1-n]->anfang(p)){
                                                                  o=p->mitte();
                                                                 }else{
                                                                  fehler("checktotalduplicationanddestruction(int&,int&) : m[1-n] hat keine poly mehr mit n=",n);
                                                                 };
                                                                 if(m[n]->anfang(p)){
                                                                  t=p->mitte();
                                                                 }else{
                                                                  fehler("checktotalduplicationanddestruction(int&,int&) : m[n] hat keine poly mehr mit n=",n);
                                                                 };
                                                                 vc=o-t;
                                                                 vc.normalisieren();
                                                                 if(m[n]->anfang(p))do{
                                                                  va=p->ebene(0);
                                                                  vb=p->ebene(1);
                                                                  D=V3.determinieren(va,vb,vc);
                                                                  if(fabs(D)>nahenull){//schräglage
                                                                   e=o-p->mitte();
                                                                   c=V3.determinieren(va,vb,e)/D;
                                                                   s=(vc*-c)+o;
                                                                   mr=p->mitte();
                                                                   c0=p->groessterindex(0);
                                                                   c1=p->groessterindex(1);
                                                                   innen=1;

                                                                   //vit=p->vertex();
                                                                   //if(vit)do{
                                                                   // vin=vit->naechstes(p);
                                                                   _listenknoten<_vertex>*lnvit;
                                                                   iterierenliste(p,lnvit,
                                                                    vit=lnvit->objekt();
                                                                    vin=lnvit->naechstes()->objekt();
                                                                    dv.setzen(vit->ort()[c0],vit->ort()[c1]);
                                                                    de.setzen(s[c0],s[c1]);
                                                                    de-=dv;
                                                                    da.setzen(vin->ort()[c0] - vit->ort()[c0], vin->ort()[c1] - vit->ort()[c1]);
                                                                    db.setzen(mr[c0],mr[c1]);
                                                                    db-=dv;
                                                                    dD=V2.determinieren(da,db);
                                                                    if(dD){
                                                                     b=V2.determinieren(da,de)/dD;
                                                                      if(b<0) innen=0;
                                                                    }else{
                                                                     fehler("_modifikationnetzintersektion::checktotalduplication()","2D - Hauptdeterminente dD ==0");
                                                                    };
                                                                   // vit=vin;
                                                                   //}while(vit!=p->vertex());
                                                                   );
                                                                   if(innen){
                                                                    if(c>0){
                                                                     anzahl++;
                                                                     if(c<lowc){
                                                                      lowc=c;
                                                                      lowp=p;
                                                                     };
                                                                    };
                                                                   };
                                                                  }else{
                                                                   //parallelität ignorieren
                                                                  };
                                                                 }while(m[n]->naechstes(p));
                                                                 if(lowp){
                                                                  if((anzahl%2)==0) {
                                                                   if(n==0) imstatus=+1; else mistatus=+1;
                                                                  }else{
                                                                   if(n==0) imstatus=-1; else mistatus=-1;
                                                                  };
                                                                 };
                                                                };
                                                                //if((mistatus==+1)&&(imstatus==+1)) return(0); else return(1);
};

void _modifikationnetzintersektion::performtotalduplicationanddestruction(int mis,int ims){
                                                                if(plog) schreiben("_modifikationnetzintersektion::performtotalduplicationanddestruction");
                                                                switch(poperation){
                                                                 case(0)://------------intersecting
                                                                  if((mis==+1)&&(ims==-1)){
                                                                   //totalduplication
                                                                   intersectingmesh->erzeugenvertexintersektion();
                                                                   intersectingmesh->nullintersektionvertices();
                                                                   duplicatemesh();
                                                                   intersectingmesh->loeschenvertexintersektion();
                                                                  }else
                                                                  if((mis==-1)&&(ims==+1)){
                                                                   //totaldestruktion
                                                                   meshtointersect->markierungpolygonstatus(-1);
                                                                   destructpoly(meshtointersect);
                                                                  }else{
                                                                   fehler("void _modifikationnetzintersektion::performtotalduplicationanddestruction(int mis,int ims)","poperation:0;statuskonfiguration ist ungültig");
                                                                  };
                                                                  break;
                                                                 case(1)://------------deintersecting
                                                                  if((mis==+1)&&(ims==-1)){
                                                                   //totalduplication und totaldestruction
                                                                   meshtointersect->markierungpolygonstatus(-1);
                                                                   intersectingmesh->erzeugenvertexintersektion();
                                                                   intersectingmesh->nullintersektionvertices();
                                                                   duplicatemesh();
                                                                   intersectingmesh->loeschenvertexintersektion();
                                                                   destructpoly(meshtointersect);
                                                                  }else
                                                                  if((mis==-1)&&(ims==+1)){
                                                                   //nichts machen
                                                                  }else{
                                                                   fehler("void _modifikationnetzintersektion::performtotalduplicationanddestruction(int mis,int ims)","poperation:1;statuskonfiguration ist ungültig");
                                                                  };
                                                                  break;
                                                                 case(2)://--------------merging
                                                                  if((mis==+1)&&(ims==-1)){
                                                                   //nichts machen   
                                                                  }else
                                                                  if((mis==-1)&&(ims==+1)){
                                                                   //totalduplication und totaldestruction
                                                                   meshtointersect->markierungpolygonstatus(-1);
                                                                   intersectingmesh->erzeugenvertexintersektion();
                                                                   intersectingmesh->nullintersektionvertices();
                                                                   duplicatemesh();
                                                                   intersectingmesh->loeschenvertexintersektion();
                                                                   destructpoly(meshtointersect);
                                                                  }else
                                                                  if((mis==+1)&&(ims==+1)){
                                                                   //totalduplication
                                                                   intersectingmesh->erzeugenvertexintersektion();
                                                                   intersectingmesh->nullintersektionvertices();
                                                                   duplicatemesh();
                                                                   intersectingmesh->loeschenvertexintersektion();
                                                                  }else{
                                                                   fehler("void _modifikationnetzintersektion::performtotalduplicationanddestruction(int mis,int ims)","poperation:2;statuskonfiguration ist ungültig");
                                                                  };
                                                                  break;
                                                                };
};

void _modifikationnetzintersektion::performpolygonoptimation(){
                                                                _listenknoten<_liste<_polygon > >*lit;
                                                                //--------------------
                                                                if(polygonoptimationlist.anfang(lit))do{
                                                                 performpolygonoptimation(lit->objekt());
                                                                }while(polygonoptimationlist.naechstes(lit));
                                                                polygonoptimationlist.loeschen();
};

void _modifikationnetzintersektion::performpolygonoptimation(_liste<_polygon >*pl){
                                                                //funktion optimiert neu angelegt polygonstruktur 
                                                                //nachträglich durch vereinigung von benachbarten
                                                                //polygonen. dies geschieht iterativ
                                                                bool loop;
                                                                bool vereinigt;
                                                                _listenknoten<_polygon >*pit;
                                                                _listenknoten<_polygon >*pii;
                                                                //----------------------------------------
                                                                loop=true;
                                                                do{
                                                                 if(pl->anfang(pit))do{
                                                                  vereinigt=false;
                                                                  pii=pit->naechstes();
                                                                  if(pii!=pl->erstes())do{
                                                                   //************* DEBUG ***********
                                                                   // if(dbscreen) dbscreen->schreiben("polygonoptimierung : Visualisierung zu pruefender Polygone",pdbcolnote);
                                                                   // pit->objekt()->visualisieren();
                                                                   // pii->objekt()->visualisieren();
                                                                   // debuganimwait();
                                                                   // pit->objekt()->unvisualisieren();
                                                                   // pii->objekt()->unvisualisieren();
                                                                   //*******************************
                                                                   if(pit->objekt()->optimieren(pii->objekt())){
                                                                    pii->loeschmarkierung(true);
                                                                    vereinigt=true;
                                                                   };
                                                                  }while((pl->naechstes(pii))&&(vereinigt==false));
                                                                 }while((pl->naechstes(pit))&&(vereinigt==false));
                                                                 pl->loeschenmarkiert();
                                                                 if(vereinigt==false){
                                                                  //keine weitere optimierung möglich
                                                                  loop=false;
                                                                 };
                                                                }while(loop);
};
//******************************************************************************     H E L P E R S  ************************************************************************************************
/*
void _modifikationnetzintersektion::dilatenearzero(_vektor<_tg>&q,_vektor<_tg>&w){
                                                                //funktion ??? dehnt die vectoren um nahenull absolut?
                                                                _vektor<_tg> nq(2);
                                                                _vektor<_tg> nw(2);
                                                                _vektor<_tg> n(2);
                                                                //_tg l;
                                                                //----------------
                                                                n=w;
                                                                n.normalisieren();
                                                                n*=nahenull;
                                                                nq=q-n;
                                                                nw=w+n;
                                                                q=nq;
                                                                w=nw;
                                                                
                                                                n[0]=w[0];
                                                                n[1]=w[1];
                                                                l=sqrt(n[0]*n[0]+n[1]*n[1]);
                                                                n[0]/=l;
                                                                n[1]/=l;
                                                                n[0]*=nahenull;
                                                                n[1]*=nahenull;
                                                                nq[0]=q[0]-n[0];
                                                                nq[1]=q[1]-n[1];
                                                                nw[0]=w[0]+n[0];
                                                                nw[1]=w[1]+n[1];
                                                                q[0]=nq[0];
                                                                q[1]=nq[1];
                                                                w[0]=nw[0];
                                                                w[1]=nw[1];
                                                                
};
*/
int _modifikationnetzintersektion::invertnormalstatus(_netz*m){
                                                                //ein poly des netz m wird gerade gecovert oder dupliziert,
                                                                //so hängt die ausrichtung des normalenvektors von der poperation und vom netz ab
                                                                if(m==meshtointersect){
                                                                 switch(poperation){
                                                                  case(0):return(+1);
                                                                  case(1):return(+1);
                                                                  case(2):return(+1);
                                                                 };
                                                                }else
                                                                if(m==intersectingmesh){
                                                                 switch(poperation){
                                                                  case(0):return(-1);
                                                                  case(1):return(+1);
                                                                  case(2):return(+1);
                                                                 };
                                                                }else{
                                                                 fehler("int _modifikationnetzintersektion::invertnormalstatus(_netz*)","ungültiger netz-zeiger");
                                                                };
                                                                fehler("int _modifikationnetzintersektion::invertnormalstatus(_netz*)","ungülitge operation");
                                                                return(+1);
};

_tg _modifikationnetzintersektion::deltaalpha(_tg a,_tg b){
                                                                //ermittelt die direktionale absolutdifferenz zwischen den beiden absolutwinkelargumenten a und b
                                                                _tg delta;
                                                                //---------
                                                                if(b<a) b+=360;
                                                                delta=b-a;
                                                                return(delta);
                                                                
};
//******************************************************************************     D E B U G     ************************************************************************************************

void _modifikationnetzintersektion::createdebugscreen(){
                                                                _vektor3<_tg> o0;
                                                                _vektor3<_tg> o1;
                                                                _vektor4<_to> col;
                                                                //---------------------
                                                                if(DW){
                                                                cleardebugscreen();
                                                                o0.setzen(-0.53,0.07,1);
                                                                o1.setzen(+0.53,0.41,1);
                                                                col.setzen(1,1,1,0);
                                                                dbscreen=new _weltdebugschirm(DW,o0,o1,80,15,col);
                                                                col.setzen(0.99f,0.6f,0.65f,0);
                                                                if(dbscreen) dbscreen->schreiben("INTERSEKTIONSALGORITHMIK (durchschreiten mit ENTER oder LEERTASTE)",col);
                                                                dbcam=new _kamera<_tg>(DW);
                                                                dbcam->setzen(-45,20,-45);
                                                                dbcam->vektorebene0(_vektor3<_tg>(0,-1,0),_vektor3<_tg>(1,0,0));
                                                                dbcam->aktualisieren();
                                                                //dbmo=new _win::_maus<_tg>(300,300);
                                                                //dbmo->relativ(true);
                                                                //dbgra=new _win::_grafikopengl<char,_tg,_to>();
                                                                //dbgra->aktivitaet(true);
                                                                //dbgra->allebufferloeschen();
                                                                //dbgra->anzeigebufferumschalten();
                                                                //dbgra->allebufferloeschen();
                                                                //dbgra->anzeigebufferumschalten();
                                                                };
};

void _modifikationnetzintersektion::cleardebugscreen(){
                                                                if(dbscreen){
                                                                 delete dbscreen;
                                                                 dbscreen=0;
                                                                };
                                                                if(dbcam){
                                                                 delete dbcam;
                                                                 dbcam=0;
                                                                };
                                                                /*if(dbgra){
                                                                 delete dbgra;
                                                                 dbgra=0;
                                                                };
                                                                if(dbmo){
                                                                 delete dbmo;
                                                                 dbmo=0;
                                                                };*/

};                                                                

void _modifikationnetzintersektion::visualizeintersection(){
                                                                flagintersection(meshtointersect,0);
                                                                flagintersection(intersectingmesh,0);
                                                                visualizeintersection(meshtointersect);
                                                                visualizeintersection(intersectingmesh);
};

void _modifikationnetzintersektion::visualizeintersection(_netz*m){
                                                                _polygon*p;
                                                                _vertex*vit;
                                                                _listenknoten<_kantepolygon >*pit;
                                                                //--------------------
                                                                m->markierungkante(0);
                                                                m->markierungvertex(0);
                                                                if(m->anfang(p))do{
                                                                 visualizeintersection(p->verbinderisintroliste());
                                                                 vit=p->vertex();
                                                                 if(p->kanten()->anfang(pit))do{
                                                                  if(pit->objekt()->markierung()==0){
                                                                   visualizeintersection(pit->objekt()->verbinderisintroliste());
                                                                   pit->objekt()->markierung(1);
                                                                  };
                                                                  if(vit->markierung()==0){
                                                                   visualizeintersection(vit->verbinderisintroliste());
                                                                   vit->markierung(1);
                                                                  };
                                                                  vit=vit->verbinder(p)->naechstervertex();
                                                                 }while(p->kanten()->naechstes(pit));
                                                                 
                                                                 _listenknoten<_vertex>*lnv;
                                                                 //vit=p->vertex();
                                                                 //if(vit)do{
                                                                 iterierenliste(p,lnv,
                                                                  vit=lnv->objekt();
                                                                  if(vit->intersektion()) vit->intersektion()->visualisieren();
                                                                 );
                                                                 // vit=vit->naechstes(p);
                                                                 //}while(vit!=p->vertex());
                                                                }while(m->naechstes(p));
};

void _modifikationnetzintersektion::visualizeintersection(_listebasis<_verbinderisintro >*l){
                                                                _verbinderisintro*iit;
                                                                //---------------
                                                                if(l->anfang(iit))do{
                                                                 if(iit->intersektion()->markierung==0){
                                                                  iit->intersektion()->markierung=1;
                                                                  iit->intersektion()->visualisieren();
                                                                 };
                                                                }while(l->naechstes(iit));

};

void _modifikationnetzintersektion::visualizeconnectorstruct(){
                                                                visualizeintroconnectorstruct();
                                                                visualizeextroconnectorstruct();
};

void _modifikationnetzintersektion::visualizeintroconnectorstruct(){
                                                                visualizeintroconnectorstruct(meshtointersect);
                                                                visualizeintroconnectorstruct(intersectingmesh);
};

void _modifikationnetzintersektion::visualizeextroconnectorstruct(){
                                                                flagintersection(meshtointersect,0);
                                                                flagintersection(intersectingmesh,0);
                                                                visualizeextroconnectorstruct(meshtointersect);
                                                                visualizeextroconnectorstruct(intersectingmesh);
};

void _modifikationnetzintersektion::visualizeintroconnectorstruct(_netz*m){
                                                                _polygon*p;
                                                                _vektor3<_tg> oo;
                                                                _vektor3<_tg> ee;
                                                                _vektor3<_tg> dd;
                                                                _vektor3<_tg> h;
                                                                _vertex*v;
                                                                _listenknoten<_kantepolygon >*pit;
                                                                _vertex*vit;
                                                                //--------------------
                                                                flagintersection(m,0);
                                                                m->markierungkante(0);
                                                                m->markierungvertex(0);
                                                                if(m->anfang(p))do{
                                                                 oo=p->normale();
                                                                 oo*=0.1;
                                                                 oo+=p->mitte();
                                                                 v=p->vertex();
                                                                 dd=v->ort();
                                                                 dd-=p->mitte();
                                                                 dd.normalisieren();
                                                                 dd*=0.15;
                                                                 visualizeintroconnectorstruct(m,p->verbinderisintroliste(),p->normale(),oo,dd);
                                                                 vit=p->vertex();
                                                                 if(p->kanten()->anfang(pit))do{
                                                                  if(pit->objekt()->markierung()==0){
                                                                   oo=p->normale();
                                                                   oo.normalisieren();
                                                                   oo*=0.1;
                                                                   ee=p->mitte();
                                                                   h=(pit->objekt()->vertex(0)->ort() + pit->objekt()->vertex(1)->ort() )*0.5;
                                                                   h.setzen(0,0,0);//=*m;
                                                                   ee=h;
                                                                   oo+=ee;
                                                                   oo=pit->objekt()->ort(0) + pit->objekt()->vektor()*0.5;
                                                                   dd.normalisieren();
                                                                   dd*=0.1;
                                                                   visualizeintroconnectorstruct(m,pit->objekt()->verbinderisintroliste(),p->normale(),oo,dd);
                                                                   pit->objekt()->markierung(1);
                                                                  };
                                                                  if(vit->markierung()==0){
                                                                   oo=p->normale();
                                                                   oo.normalisieren();
                                                                   oo*=0.05;
                                                                   oo+=vit->ort();
                                                                   dd.normalisieren();
                                                                   dd*=0.125;
                                                                   visualizeintroconnectorstruct(m,vit->verbinderisintroliste(),p->normale(),oo,dd);
                                                                   vit->markierung(1);
                                                                  };
                                                                  vit=vit->verbinder(p)->naechstervertex();
                                                                 }while(p->kanten()->naechstes(pit));
                                                                }while(m->naechstes(p));
};

void _modifikationnetzintersektion::visualizeintroconnectorstruct(_netz*m,_listebasis<_verbinderisintro >*isic,const _vektor3<_tg>&nn,const _vektor3<_tg>&oo,const _vektor3<_tg>&dd){
                                                                int anzahl;
                                                                _tg delt;
                                                                _tg winkel;
                                                                _verbinderisintro*iit;
                                                                _vektor3<_tg> pp;
                                                                _vektor3<_tg> e;
                                                                _vektor4<_to> rand;
                                                                //--------------------------------------------
                                                                anzahl=isic->anzahl();
                                                                if(anzahl){
                                                                 delt=(360/anzahl)/1;
                                                                 winkel=0;
                                                                 if(m==intersectingmesh) winkel+=delt/2;
                                                                 rand.zufall();
                                                                 if(isic->anfang(iit))do{
                                                                  V3.rotieren(nn,dd,winkel,e);
                                                                  pp=oo+e;
                                                                  iit->visualisieren(m,pp,rand);
                                                                  winkel+=delt;
                                                                 }while(isic->naechstes(iit));
                                                                };
};

void _modifikationnetzintersektion::visualizeextroconnectorstruct(_netz*m){
                                                                _polygon*p;
                                                                _vektor3<_tg> oo;
                                                                _vektor3<_tg> ee;
                                                                _vektor3<_tg> dd;
                                                                _vertex*v;
                                                                _vertex*vit;
                                                                _listenknoten<_kantepolygon >*pit;
                                                                //--------------------
                                                                m->markierungkante(0);
                                                                m->markierungvertex(0);
                                                                if(m->anfang(p))do{
                                                                 v=p->vertex();
                                                                 dd=v->ort();
                                                                 dd-=p->mitte();
                                                                 dd.normalisieren();
                                                                 dd*=0.2;
                                                                 visualizeextroconnectorstruct(p->verbinderisintroliste(),p->normale(),dd);
                                                                 vit=p->vertex();
                                                                 if(p->kanten()->anfang(pit))do{
                                                                  if(pit->objekt()->markierung()==0){
                                                                   visualizeextroconnectorstruct(pit->objekt()->verbinderisintroliste(),p->normale(),dd);
                                                                   pit->objekt()->markierung(1);
                                                                  };
                                                                  if(vit->markierung()==0){
                                                                   visualizeextroconnectorstruct(vit->verbinderisintroliste(),p->normale(),dd);
                                                                   vit->markierung(1);
                                                                  };
                                                                  vit=vit->verbinder(p)->naechstervertex();
                                                                 }while(p->kanten()->naechstes(pit));
                                                                }while(m->naechstes(p));
};

void _modifikationnetzintersektion::visualizeextroconnectorstruct(_listebasis<_verbinderisintro >*isic,const _vektor3<_tg>&nn,const _vektor3<_tg>&dd){
                                                                int anzahl;
                                                                _tg delt;
                                                                _tg winkel;
                                                                _verbinderisintro*iit;
                                                                _verbinderisextro*iet;
                                                                _vektor3<_tg> pp;
                                                                _vektor3<_tg> e;
                                                                //---------------
                                                                if(isic->anfang(iit))do{
                                                                 if(iit->intersektion()->markierung==0){
                                                                  iit->intersektion()->markierung=1;
                                                                  anzahl=iit->intersektion()->_listebasis<_verbinderisextro >::anzahl();
                                                                  delt=360/anzahl;
                                                                  winkel=0;
                                                                  if(iit->intersektion()->anfang(iet))do{
                                                                   V3.rotieren(nn,dd,winkel,e);
                                                                   pp=iit->intersektion()->ort()+e;
                                                                   iet->visualisieren(pp);
                                                                   winkel+=delt;
                                                                  }while(iit->intersektion()->naechstes(iet));
                                                                 };
                                                                }while(isic->naechstes(iit));
};

void _modifikationnetzintersektion::visualizestatusstruct(_netz*m){
                                                                _polygon*p;
                                                                _listenknoten<_kantepolygon >*pit;
                                                                _vertex*vit;
                                                                //-------------
                                                                flagintersection(m,0);
                                                                if(m->anfang(p))do{
                                                                 visualizestatusstruct(p->verbinderisintroliste());
                                                                 vit=p->vertex();
                                                                 if(p->kanten()->anfang(pit))do{
                                                                  visualizestatusstruct(pit->objekt()->verbinderisintroliste());
                                                                  visualizestatusstruct(vit->verbinderisintroliste());
                                                                  vit=vit->verbinder(p)->naechstervertex();
                                                                 }while(p->kanten()->naechstes(pit));
                                                                 //vit=p->vertex();
                                                                 //if(vit)do{
                                                                 _listenknoten<_vertex>*lnvit;
                                                                 iterierenliste(p,lnvit,
                                                                  vit=lnvit->objekt();
                                                                  if(vit->intersektion()){
                                                                   if(vit->intersektion()->markierung==0){
                                                                    vit->intersektion()->visualizestatusstruct();
                                                                    vit->intersektion()->markierung=1;
                                                                   };
                                                                  };
                                                                 );
                                                                 // vit=vit->naechstes(p);
                                                                 //}while(vit!=p->vertex());
                                                                }while(m->naechstes(p));
};

void _modifikationnetzintersektion::visualizestatusstruct(_listebasis<_verbinderisintro >*isic){
                                                                _verbinderisintro*iit;
                                                                //---------------------
                                                                if(isic->anfang(iit))do{
                                                                 if(iit->intersektion()->markierung==0){
                                                                  iit->intersektion()->markierung=1;
                                                                  iit->intersektion()->visualizestatusstruct();
                                                                 };
                                                                }while(isic->naechstes(iit));
};

void _modifikationnetzintersektion::visualizeintersectionsequence(_vertex*){
};

void _modifikationnetzintersektion::visualizeringpartition(_polygon*p){
                                                                _ringpartition*rit;
                                                                //-----------------
                                                                if(p->ringpartitionsliste()->anfang(rit))do{
                                                                 rit->visualisieren();
                                                                }while(p->ringpartitionsliste()->naechstes(rit));
};


void _modifikationnetzintersektion::debuganimwait(){
                                                               // _win::_tastatur kb;
                                                               // _win::_zeit t;
                                                                //---------------------
                                                               
                                                                if((DW)&&(dbcam))
                                                                if((DW->debugmaus())&&(DW->debuggrafik())&&(DW->debugtastatur())){
                                                                 if(debugskipcount==0){
                                                                  _maus<_tg>*maus=DW->debugmaus();
                                                                  if(maus->relativ()==false) maus->relativ(true);
                                                                  if(DW->debugtastatur()->leertaste()==false){
                                                                    
                                                                   while((DW->debugtastatur()->enter()==false)&&(DW->debugtastatur()->leertaste()==false)){
                                                                    S->animieren();
                                                                    DW->debuggrafik()->allebufferloeschen();
                                                                    dbcam->bewegen(DW->debugtastatur(),DW->debugmaus(),0.1);
                                                                    //DW->transformieren(DW->debuggrafik(),dbcam, false);
                                _matrix44<float> mw;
                                _matrix44<float> mm;
                                _matrix44<float> mp;
                                mw.setzenidentitaet();
                                mm.setzenidentitaet();
                                mp.setzenidentitaet();
                                dbcam->ladenmatrix<float>(&mm,&mp);
                                DW->debuggrafik()->matrixwelt(&mw); 
                                DW->debuggrafik()->matrixprojektion(&mp);
                                DW->debuggrafik()->matrixmodell(&mm);
                                                                    
                                                                    DW->zeichnendebug(DW->debuggrafik()); 
                                                                    DW->debuggrafik()->anzeigebufferumschalten();
                                                                   };
                                                                   while(DW->debugtastatur()->enter());
                                                                  }else{
                                                                   DW->debuggrafik()->allebufferloeschen();
                                                                   dbcam->bewegen(DW->debugtastatur(),DW->debugmaus(),1);
                                                                   DW->transformieren(DW->debuggrafik(),dbcam, false);
                                                                   DW->zeichnendebug(DW->debuggrafik()); 
                                                                   DW->debuggrafik()->anzeigebufferumschalten();
                                                                   S->animieren();
                                                                  };
                                                                 }else{
                                                                  debugskipcount--;
                                                                 };
                                                                };
};


void _modifikationnetzintersektion::debuganimation(){
                                                              //  debuganimwait();
                                                               // _win::_tastatur kb;
                                                               // _win::_zeit timer;
                                                                //---------------------
                                                                if(DW){
                                                                 if((DW->debugmaus())&&(DW->debuggrafik())&&(DW->debugtastatur())){
                                                                  DW->debuggrafik()->allebufferloeschen();
                                                                  dbcam->bewegen(DW->debugtastatur(),DW->debugmaus(),1);
                                                                  DW->transformieren(DW->debuggrafik(),dbcam,false);
                                                                  DW->zeichnendebug(DW->debuggrafik()); 
                                                                  DW->debuggrafik()->anzeigebufferumschalten();
                                                                  S->animieren();
                                                                 };
                                                                };
                                                                
};
//******************************************************************************************************************************************************************************************************
//                                                              V E R B I N D E R I S I N T R O 
//******************************************************************************************************************************************************************************************************

_verbinderisintro::_verbinderisintro(_polygon*d,_intersektion*i,_polygon*cd,_kantepolygon*ce,_vertex*cv,_tg a):_listenknotenbasissortiert<_verbinderisintro,_tg>(d->verbinderisintroliste(),a){
                                                                //Introconnector-constructor für poly 
                                                                palpha=a;
                                                                pcausalpoly=cd;
                                                                pcausaledge=ce;
                                                                pcausalvertex=cv;
                                                                pvertex=0;
                                                                pedge=0;
                                                                ppoly=d;
                                                                pintersection=i;
                                                                pisextroconnector=new _verbinderisextro(i,this);
                                                               //*******************  D E B U G ************************
                                                                pdbcross=0;
                                                                pdbtointersection=0;
                                                                pdbtopolyowner=0;
                                                                pdbtopolycausal=0;
};

_verbinderisintro::_verbinderisintro(_kantepolygon*e,_intersektion*i,_polygon*cd,_kantepolygon*ce,_vertex*cv,_tg a):_listenknotenbasissortiert<_verbinderisintro,_tg>(e->verbinderisintroliste(),a){
                                                                //Introconnector-constructor für kante  
                                                                palpha=a;
                                                                pcausalpoly=cd;
                                                                pcausaledge=ce;
                                                                pcausalvertex=cv;
                                                                pvertex=0;
                                                                pedge=e;
                                                                ppoly=0;
                                                                pintersection=i;
                                                                e->inkrementierenanzahlverbinderisintro();
                                                                pisextroconnector=new _verbinderisextro(i,this);
                                                                //*******************  D E B U G ************************
                                                                pdbcross=0;
                                                                pdbtointersection=0;
                                                                pdbtopolyowner=0;
                                                                pdbtopolycausal=0;
};

_verbinderisintro::_verbinderisintro(_vertex*v,_intersektion*i,_polygon*cd,_kantepolygon*ce,_vertex*cv,_tg a):_listenknotenbasissortiert<_verbinderisintro,_tg>(v->verbinderisintroliste(),a){
                                                                //Introconnector-constructor für vertex
                                                                palpha=a;
                                                                pcausalpoly=cd;
                                                                pcausaledge=ce;
                                                                pcausalvertex=cv;
                                                                pvertex=v;
                                                                pedge=0;
                                                                ppoly=0;
                                                                pintersection=i;
                                                                pisextroconnector=new _verbinderisextro(i,this);
                                                                //*******************  D E B U G ************************
                                                                pdbcross=0;
                                                                pdbtointersection=0;
                                                                pdbtopolyowner=0;
                                                                pdbtopolycausal=0;
};

_verbinderisintro::~_verbinderisintro(){
                                                                if(pedge) pedge->dekrementierenanzahlverbinderisintro();
                                                                if(pdbcross) delete pdbcross;
                                                                if(pdbtointersection) delete pdbtointersection;
                                                                if(pdbtopolyowner) delete pdbtopolyowner;
                                                                if(pdbtopolycausal) delete pdbtopolycausal;
                                                                pdbcross=0;
                                                                pdbtointersection=0;
                                                                pdbtopolyowner=0;
                                                                pdbtopolycausal=0;
};

bool _verbinderisintro::polygonedgebounded()const{
                                                                if((pedge!=0)||(pvertex!=0)) return(true); else return(false);
};

_intersektion* _verbinderisintro::intersektion(){
                                                                return(pintersection);
};

_polygon* _verbinderisintro::causalpolygon(){
                                                                return(pcausalpoly);
};

void _verbinderisintro::visualisieren(_netz*m,_vektor3<_tg>&o,_vektor4<_to>&rand){
                                                                _vektor4<_to> gelb;
                                                                _vektor4<_to> weiss;
                                                                _vektor4<_to> rot;
                                                                _vektor4<_to> grau;
                                                                //-----------
                                                                if(pdbcross) delete pdbcross;
                                                                if(pdbtointersection) delete pdbtointersection;
                                                                if(pdbtopolyowner) delete pdbtopolyowner;
                                                                if(pdbtopolycausal) delete pdbtopolycausal;
                                                                pdbcross=0;
                                                                pdbtointersection=0;
                                                                pdbtopolyowner=0;
                                                                pdbtopolycausal=0;
                                                                if(DW){
                                                                if(pedge) gelb.setzen(0.6f,0.6f,0.0f,0); else gelb.setzen(1.0f,1.0f,0.0f,0);
                                                                gelb=gelb*0.5f + rand*0.5f;
                                                                weiss.setzen(1,1,1,0);
                                                                rot.setzen(0.8f,0,0,0);
                                                                grau.setzen(0.4f,1,0.4f,0);
                                                                pdbcross=new _weltdebugkreuz(DW,o,0.05,gelb);
                                                                pdbtointersection=new _weltdebuglinie(DW,o,pintersection->ort(),gelb);
                                                                //pdbtopolyowner=new _weltdebugpfeil(W,o,);
                                                                pdbtopolycausal=new _weltdebugpfeil(DW,o,pcausalpoly->mitte(),0.04,0.02,rot);
                                                                };
};
//******************************************************************************************************************************************************************************************************
//                                                              V E R B I N D E R I S E X T R O
//******************************************************************************************************************************************************************************************************

_verbinderisextro::_verbinderisextro(_intersektion*i,_verbinderisintro*isic):_listenknotenbasis<_verbinderisextro >(i){
                                                                pisintroconnector=isic;
                                                                pintersection=i;
                                                                debug=0;
                                                                debugic=0;
                                                                debugis=0;
};

_verbinderisextro::~_verbinderisextro(){
                                                                if(debug) delete debug;
                                                                if(debugic) delete debugic;
                                                                if(debugis) delete debugis;
                                                                debug=0;
                                                                debugic=0;
                                                                debugis=0;
};

void _verbinderisextro::clearisintroconnector(){
                                                                if(pisintroconnector){
                                                                 delete pisintroconnector;
                                                                 pisintroconnector=0;
                                                                };
};                                                                

void _verbinderisextro::visualisieren(_vektor3<_tg> o){
                                                                _vektor4<_to> col;
                                                                col.setzen(1,0.1f,1,0);
                                                                if(debug) delete debug;
                                                                if(debugic) delete debugic;
                                                                if(debugis) delete debugis;
                                                                debugic=0;
                                                                debugis=0;
                                                                debug=0;
                                                                if(DW){
                                                                debug=new _weltdebugkreuz(DW,o,0.02,col);
                                                                if(pisintroconnector->pdbcross){
                                                                 debugic=new _weltdebuglinie(DW,pisintroconnector->pdbcross->ort(),o,col);
                                                                };
                                                                debugis=new _weltdebuglinie(DW,pintersection->ort(),o,col);
                                                                };
};
//******************************************************************************************************************************************************************************************************
//                                                              S T A T U S K R E U Z
//******************************************************************************************************************************************************************************************************

_statuskreuz::_statuskreuz(_modifikationnetzintersektion*mi,_statussektion*ss,_intersektion*l0,_intersektion*l1,_tg a0,_tg a1,_polygon*cp,char k):_listenknotenbasis<_statuskreuz >(ss){
                                                                //int n;
                                                                //-------
                                                                mmi=mi;
                                                                virtualintersection=0;
                                                                pstatussection=ss;
                                                                markierung=0;
                                                                status=0;
                                                                rawstatus=0;
                                                                pleft[0]=l0;
                                                                pleft[1]=l1;
                                                                palpha[0]=a0;
                                                                palpha[1]=a1;
                                                                pcausalpoly=cp;
                                                              //  for(n=0;n<2;n++) if(pleft[n]) palpha[n]=pleft[n]->alpha; else palpha[n]=0;
                                                                pstatussection->erstes(this);//statuscross=this;
                                                                if(k){
                                                                 //achtung:prügen, ob komplanarität gültig ist,
                                                                 //d.h. untersuchen ob pmiddle - statussection->intersektion->ort 
                                                                 //in richtung causalpolymittelpunkt geht 
                                                                };
                                                                komplanar=k;

                                                                debugcross=0;
                                                                debugis=0;
                                                                debugle[0]=0;
                                                                debugle[1]=0;
                                                                getmiddle();
};

_statuskreuz::~_statuskreuz(){
                                                                if(debugcross) delete debugcross;
                                                                if(debugis) delete debugis;
                                                                if(debugle[0]) delete debugle[0];
                                                                if(debugle[1]) delete debugle[1];
                                                                debugcross=0;
                                                                debugis=0;
                                                                debugle[0]=0;
                                                                debugle[1]=0;
};

_statussektion*_statuskreuz::statussection(){
                                                                return(pstatussection);
};

_vektor3<_tg> _statuskreuz::mitte() const{
                                                                return(pmiddle);        
};

_intersektion*_statuskreuz::left(const unsigned int i){
                                                                if(i==0) return(pleft[0]); else return(pleft[1]);
};

_tg _statuskreuz::alpha(const unsigned int i) const{
                                                                if(i==0) return(palpha[0]); else return(palpha[1]);
};

void _statuskreuz::getmiddle(){
                                                                _tg malpha,da;
                                                                _vektor3<_tg> h;
                                                                _vektor3<_tg> e;
                                                                _tg a,b;
                                                                _polygon*p;
                                                                _intersektion*i;
                                                                _vektoranalysis3<_tg> V3;
                                                                //-----------------
                                                                //das statuscross sc kann in 3 situationen vorliegen:
                                                                //1. sc mit nullrelevanz dh.left[1]==0 und left[0]==0 -> dreiecksvector, um in die fläche zu kommen
                                                                //2. sc mit singularer relevanz dh. left[1]==left[2]!=0 -> malpha=left[0]+90°
                                                                //3. sc mit multipler relevanz dh .left[1]!=0 != left[2]!=0 -> malpha=(left[0]+left[1])*0.5
                                                                p=pstatussection->poly;
                                                                i=pstatussection->intersektion;
                                                                malpha=0;
                                                                if((pleft[0]==0)&&(pleft[1]==0)){//nullrelevanz ->irgendein punkt (dreiecksvektor)
                                                                 h=p->vertex()->ort()-p->mitte();
                                                                 h.normalisieren();
                                                                 pmiddle=i->ort();
                                                                 pmiddle+=h;
                                                                }else
                                                                if((pleft[1]==pleft[0])&&(pleft[0]!=0)){//singluare relevanz,left[0]+rightangle
                                                                 h=pleft[0]->ort();
                                                                 h-=i->ort();
                                                                 V3.rotieren(p->normale(),h,90,e);
                                                                 pmiddle=i->ort()+e;
                                                                }else
                                                                if((pleft[1])&&(pleft[0])&&(pleft[0]!=pleft[1])){//multiple relevanz
                                                                 a=palpha[0];
                                                                 b=palpha[1];
                                                                 if(b<a) b+=360;
                                                                 da=b-a;
                                                                 h=p->ebene(0);
                                                                 h.normalisieren();
                                                                 V3.rotieren(p->normale(),h,+(a+da*0.5),e);
                                                                 pmiddle=i->ort()+e;
                                                                 //************************ DEBUG ***********************
                                                                 //L->schreiben("winkel a=",a);
                                                                 //L->schreiben("winkel b=",b);
                                                                 //L->schreiben("winkel da=",da);
                                                                 //visualisieren();
                                                                 //mmi->debuganimation();
                                                                 //unvisualisieren();
                                                                 //******************************************************
                                                                };
};

void _statuskreuz::determinestatus(_polygon*p,_listebasis<_verbinderisintro >*listisic){
                                                                _vektor3<_tg> h;
                                                                _tg x;
                                                                _verbinderisintro*isic;
                                                                _vektor3<_tg> target;
                                                                char stop;
                                                                _tg lalpha;
                                                                int lrawstatus;
                                                                _tg sp;
                                                                //-------------
                                                                //dies ist eine sehr wichtige intersectingfunktion; gilt nur für reele intersektion mit causaldreiecken
                                                                //vor der causalcollision muss festgestellt werden, ob ein koplanares dreieck das statuscross sc komplett alleine aufspannt
                                                                //Status muss anhand des normalenvektors erkannt werden (vereinfachte culled methode)
                                                                if(komplanar){
                                                                 if(pcausalpoly==0){
                                                                  mmi->fehler("void _statuskreuz::determinestatus(_polygon*p,_statuskreuz*sc,_verbinderisintro*firstisic)","statusscross sc ist zwar komplanar geflaggt hat aber keinen initialisierten causalpoly-zeiger.");
                                                                 }else{
                                                                  sp=pcausalpoly->normale() * p->normale();
                                                                  if(sp<0){//(h[0]*h[0]+h[1]*h[1]+h[2]*h[2])<0.5){//inverse normalen -> raw : aussen
                                                                   //****************** DEBUG *******************
                                                                   //_win::_pclautsprecher ss;//debug
                                                                   //ss.peep(1000);
                                                                   //mmi->schreiben("determinestatus komplanar");
                                                                   //visualisieren();
                                                                   //pleft[0]->visualisieren();
                                                                   //pleft[1]->visualisieren();
                                                                   //mmi->debuganimation();
                                                                   //unvisualisieren();
                                                                   //********************************************
                                                                   //sc->rawstatus=+1;
                                                                   /*sc->status=konvertieren*/setstatuskomplanar(+1);
                                                                  }else{
                                                                   //sc->rawstatus=-1;
                                                                   /*sc->status=konvertieren*/setstatuskomplanar(-1);
                                                                  };
                                                                 };
                                                                 
                                                                }else{
                                                                 //nun in irgendein causaldreieckmittelpunkt zielen , diese darf aber nicht koplanar sein,
                                                                 //so dass zwangsweise parallel geschnitten werden müsste
                                                                 //****************** DEBUG *******************
                                                                 //ss.peep(1000);
                                                                 //mmi->schreiben("determinestatus unkomplanar");
                                                                 //********************************************
                                                                 target.setzen(0,0,0);
                                                                 stop=0;
                                                                 if(listisic->anfang(isic))do{
                                                                  if(isic->intersektion()==pstatussection->intersektion){
                                                                   
                                                                   target=isic->causalpolygon()->mitte();//bewegen(isic->causalpoly->mitte->o,target);
                                                                   h=target-mitte();
                                                                   h.normalisieren();
                                                                   x=isic->causalpolygon()->normale()*h;//x=mul(isic->causalpoly->normale->o,h);
                                                                   if(fabs(x)>nahenull) stop=1;
                                                                  };
                                                                  /*if(isic->parallel==0)   
                                                                  if(isic->intersektion==sc->pstatussection->intersektion){
                                                                   bewegen(isic->causalpoly->mitte->o,target);
                                                                   stop=1;
                                                                  };*/
                                                                 }while((listisic->naechstes(isic))&&(stop==0));
                                                                 //************************************* DEBUG : visualisierung der collisionsgeraden ******************
                                                                 //_weltdebugpfeil*dar;
                                                                 //_vektor4<_to> col;
                                                                 //if(stop==0) col.setzen(1,0.5,0.5); else
                                                                 //col.setzen(1,0,1);
                                                                 //dar=new _weltdebugpfeil(W,mitte(),target,0.1,0.1,col);
                                                                 //visualisieren();
                                                                 //mmi->debuganimation();
                                                                 //unvisualisieren();
                                                                 //delete dar;
                                                                 //*****************************************************************************************************
                                                                 if(stop==0){
                                                                  mmi->fehler("_statuskreuz::determinestatus(_dreieck*,_statuskreuz*,_verbinderisintro*)","Es konnte kein Target bestimmt werden. Prozess wird fortgesetzt");
                                                                 };                                                                                         
                                                                 //source : sc->mitte ; target : target
                                                                 lalpha=1e+6;
                                                                 lrawstatus=0;
                                                                 if(listisic->anfang(isic))do{
                                                                  
                                                                  if(isic->intersektion()==pstatussection->intersektion){
                                                                   if(isic->causalpolygon()==0) mmi->fehler("void _statuskreuz::determinestatus(_polygon*p,_listebasis<_verbinderisintro >*listisic)","isic->causalpolygon()==0");
                                                                   collideinfinitiv(target,isic->causalpolygon(),lalpha,lrawstatus);
                                                                  };
                                                                 }while(listisic->naechstes(isic));
                                                                 if(lrawstatus==0){
                                                                  mmi->fehler("_statuskreuz::determinestatus(_dreieck*,_statuskreuz*,_verbinderisintro*)","Es konnte kein rawstatus anhand der causaldreieckgruppe bestimmt werden.");
                                                                 }else{
                                                                  //rawstatus auswerten
                                                                  //sc->rawstatus=lrawstatus;
                                                                  /*sc->status=konvertieren*/setstatus(lrawstatus);
                                                                 };
                                                                };
};

int _statuskreuz::setstatus(int rwst){
                                                                int s;
                                                                //------
                                                                s=0;
                                                                rawstatus=rwst;
                                                                if(mmi->thismesh==mmi->meshtointersect){        
                                                                 if(rawstatus==+1){
                                                                  switch(mmi->poperation){
                                                                   case(0):s=+1;break;//intersecting 
                                                                   case(1):s=-1;break;//deintersecting 
                                                                   case(2):s=+1;break;//merging
                                                                   //case(3):return(+1);//dividing
                                                                  };
                                                                 }else if(rawstatus==-1){
                                                                  switch(mmi->poperation){
                                                                   case(0):s=-1;break;//intersecting 
                                                                   case(1):s=+1;break;//deintersecting 
                                                                   case(2):s=-1;break;//merging
                                                                   //case(3):return(-1);//dividing
                                                                  };
                                                                 };
                                                                 if(s==0) mmi->fehler("_statuskreuz::setstatus(int)","operation oder rawstatus sind ungültig (thismesh=meshtointersect)");
                                                                }else{
                                                                 if(rawstatus==+1){
                                                                  switch(mmi->poperation){
                                                                   case(0):s=-1;break;//intersecting 
                                                                   case(1):s=-1;break;//deintersecting 
                                                                   case(2):s=+1;break;//merging
                                                                   //case(3):return(-1);//dividing
                                                                  };
                                                                 }else if(rawstatus==-1){
                                                                  switch(mmi->poperation){
                                                                   case(0):s=+1;break;//intersecting 
                                                                   case(1):s=+1;break;//deintersecting 
                                                                   case(2):s=-1;break;//merging
                                                                   //case(3):return(+1);//dividing
                                                                  };
                                                                 };
                                                                 if(s==0) mmi->fehler("_statuskreuz::setstatus(int)","operation oder rawstatus sind ungültig (thismesh==INTERSECTINGMESH)");
                                                                };
                                                                status=s;
                                                                return(status);
};

int _statuskreuz::setstatuskomplanar(int rwst){
                                                                int s;
                                                                //-------
                                                                rawstatus=rwst;
                                                                s=0;
                                                                if(mmi->thismesh==mmi->intersectingmesh){
                                                                 if(rawstatus==+1){
                                                                  switch(mmi->poperation){
                                                                   case(0):s=+1;break;//intersecting 
                                                                   case(1):s=-1;break;//deintersecting 
                                                                   case(2):s=-1;break;//merging
                                                                   //case(3):return(-1);//dividing
                                                                  };
                                                                 }else if(rawstatus==-1){
                                                                  switch(mmi->poperation){
                                                                   case(0):s=-1;break;//intersecting 
                                                                   case(1):s=-1;break;//deintersecting 
                                                                   case(2):s=-1;break;//merging
                                                                   //case(3):return(-1);//dividing
                                                                  };
                                                                 };
                                                                 if(s==0) mmi->fehler("_statuskreuz::setstatuskoplanar(int)","thismesh==intersectingmesh:operation oder rawstatus sind ungültig");
                                                                }else{
                                                                 if(rawstatus==+1){
                                                                  switch(mmi->poperation){
                                                                   case(0):s=-1;break;//intersecting 
                                                                   case(1):s=-1;break;//deintersecting 
                                                                   case(2):s=-1;break;//merging
                                                                   //case(3):return(+1);//dividing
                                                                  };
                                                                 }else if(rawstatus==-1){
                                                                  switch(mmi->poperation){
                                                                   case(0):s=-1;break;//intersecting 
                                                                   case(1):s=+1;break;//deintersecting 
                                                                   case(2):s=+1;break;//merging
                                                                   //case(3):return(-1);//dividing
                                                                  };
                                                                 };
                                                                 if(s==0) mmi->fehler("_statuskreuz::setstatuskoplanar(int)","operation oder rawstatus sind ungültig");
                                                                };
                                                                status=s;
                                                                return(status);
};

char _statuskreuz::determinecausalitytype(_intersektion*is,_polygon*cp,_kantepolygon*&e,_vertex*&vm,_vertex*&v0,_vertex*&v1){
                                                                char r;
                                                                char q;
                                                                _listenknoten<_kantepolygon >*pit;
                                                                _vertex*vit;
                                                                //----------
                                                                r=0;
                                                                q=0;
                                                                e=0;
                                                                v0=0;
                                                                v1=0;
                                                                vm=0;
                                                                if(determinecausalitytype(is,cp->verbinderisintroliste())){
                                                                 //ebenecausalität
                                                                 r=1;
                                                                }else{
                                                                 q=0;
                                                                 if(cp->kanten()->anfang(pit))do{
                                                                  q|=determinecausalitytype(is,pit->objekt()->verbinderisintroliste());
                                                                  //kante-causalität
                                                                  if(q)e=pit->objekt();
                                                                 }while((cp->kanten()->naechstes(pit))&&(q==0));
                                                                 
                                                                 if(q==0){
                                                                  //vit=cp->vertex();
                                                                  //if(vit)do{
                                                                  _listenknoten<_vertex>*lnvit;
                                                                  if(cp->anfang(lnvit))do{
                                                                   vit=lnvit->objekt();
                                                                   q|=determinecausalitytype(is,vit->verbinderisintroliste());
                                                                   if(q){
                                                                    //vertex-causalität
                                                                    v0=vit->verbinder(cp)->vorherigervertex();//vorheriges(cp);
                                                                    vm=vit;
                                                                    v1=vit->verbinder(cp)->naechstervertex();//naechstes(cp);
                                                                   };
                                                                  // vit=vit->naechstes(cp);
                                                                  }while((cp->naechstes(lnvit))&&(q==0));
                                                                  if(q==0){
                                                                   mmi->fehler("_statuskreuz::determinecausalitytype(_intersektion*,_dreieck*,_kante*&,_vertex*&,_vertex*&)","Es konnte die Art der Causalität nicht bestimmt werden.");
                                                                  };
                                                                 };
                                                                };
                                                                return(r);
};

char _statuskreuz::determinecausalitytype(_intersektion*is,_listebasis<_verbinderisintro >*isic){
                                                                char r;
                                                                _verbinderisintro*iit;
                                                                //------------------
                                                                r=0;
                                                                //iit=firstisic;
                                                                if(isic->anfang(iit))do{
                                                                 if(iit->intersektion()==is) r=1;// else iit=iit->naechstes;
                                                                }while((isic->naechstes(iit))&&(r==0));
                                                                return(r);
};

void _statuskreuz::collideinfinitiv(_vektor3<_tg>&t,_polygon*cp,_tg&lowesta,int&lowestrawstatus){
                                                                //achtung : hier muss die parallelität ignoriert werden;
                                                                //ein paralleler schnitt kann nicht mehr auftreten, ausser bei null - relevanz und bei ?
                                                                //aufgabe dieser funktion ist es, die geometrische lage des causaldreiecks an der intersektion
                                                                //zu bestimmen, wovon grundsätzlich die art der causalinfinitation abhängt
                                                                _vektor3<_tg> o;
                                                                _vektor3<_tg> s;
                                                                _vektor3<_tg> va;
                                                                _kantepolygon*kante;
                                                                _vertex*vertex[2];
                                                                _vertex*vm;
                                                                _intersektion*is;
                                                                //------------
                                                                is=pstatussection->intersektion;
                                                                s=mitte();
                                                                va=s-t;
                                                                o=s-is->ort();
                                                                //gerade : o + a*va
                                                                //ebene : b*vb + c*vc
                                                                //************** DEBUG : visualisierung der kollisionsszene ***********
                                                                //visualisieren();
                                                                //int of;
                                                                //_weltdebugpfeil*dar;
                                                                //_weltdebugkreuz*dcr;
                                                                //_vektor4<_to> col;
                                                                //col.setzen(1,1,1);
                                                                //dar=new _weltdebugpfeil(W,mitte(),t,0.04,0.01,col);
                                                                //dcr=new _weltdebugkreuz(W,cp->mitte(),0.1,col);
                                                                //of=cp->markierung();
                                                                //cp->markierung(1);
                                                                //mmi->debuganimation();
                                                                //unvisualisieren();
                                                                //cp->markierung(of);
                                                                //delete dar;
                                                                //delete dcr;
                                                                //*********************************************************************
                                                                if(determinecausalitytype(is,cp,kante,vm,vertex[0],vertex[1])){
                                                                 if(mmi->schreibenlogbuch()) mmi->schreiben("_statuskreuz::collidetotalplanar");
                                                                 collidetotalplanar(cp,va,s,t,o,lowesta,lowestrawstatus);
                                                                }else{
                                                                 if(kante){
                                                                  if(mmi->schreibenlogbuch()) mmi->schreiben("_statuskreuz::collidesemiplanar");
                                                                  collidesemiplanar(cp,kante,va,s,t,o,lowesta,lowestrawstatus);
                                                                 }else{
                                                                  if(mmi->schreibenlogbuch()) mmi->schreiben("_statuskreuz::collidedoublesemiplanar");                                                                                          
                                                                  collidedoublesemiplanar(cp,vm,vertex[0],vertex[1],va,s,t,o,lowesta,lowestrawstatus);
                                                                 };
                                                                };
};

void _statuskreuz::collidetotalplanar(_polygon*cp,_vektor3<_tg>&va,_vektor3<_tg>&s,_vektor3<_tg>&t,_vektor3<_tg>&o,_tg&lowesta,int&lowestrawstatus){
                                                                //funktion determinatcausalitytype() liefert true wenn das causaldreieck mit seiner ebene schneidet...
                                                                //d.h. hier kann einfach mit der ebene geschnitten werden
                                                                //parallelität ist eigentlich ausgeschlossen
                                                                _vektor3<_tg> vb;
                                                                _vektor3<_tg> vc;
                                                                _vektor3<_tg> h;
                                                                _vektor3<_tg> e;
                                                                _tg D,a;
                                                                
                                                                //----------------------
                                                                vb=cp->ebene(0);
                                                                vc=cp->ebene(1);
                                                                D=mmi->V3.determinieren(va,vb,vc);
                                                                if(D){
                                                                 a=mmi->V3.determinieren(o,vb,vc)/D;
                                                                 if((a>0)&&(a<lowesta)){
                                                                  lowesta=a;
                                                                  h=t-s;
                                                                  h.normalisieren();
                                                                  e=h+cp->normale();
                                                                  if(sqrt(e[0]*e[0]+e[1]*e[1]+e[2]*e[2])<sqrt(2.0)){
                                                                   lowestrawstatus=+1;
                                                                  }else{
                                                                   lowestrawstatus=-1;
                                                                  };
                                                                 };
                                                                }else{
                                                                 mmi->fehler("_statuskreuz::collidetotalplanar()","Hauptdeterminante bei causalebenencollision ist null (parallelität).");
                                                                };
};                                                                                         

void _statuskreuz::collidesemiplanar(_polygon*cp,_kantepolygon*kante,_vektor3<_tg>&va,_vektor3<_tg>&s,_vektor3<_tg>&t,_vektor3<_tg>&o,_tg&lowesta,int&lowestrawstatus){
                                                                //hier liegt kante causalität vor es brauch also nur eine halbebene aufgespannt zu werden
                                                                //dabei ist die aufspannrichtung abhängig von irgendeinem anderem dreiecksvektor von
                                                                //dem kante-vektor ausgehend
                                                                _vektor3<_tg> vb;
                                                                _vektor3<_tg> vc;
                                                                _vektor3<_tg> h;
                                                                _vektor3<_tg> e;
                                                                _tg D,a,c;
                                                                //------------------
                                                                vb=kante->vektor();//+,-
                                                                vc=cp->mitte()-kante->ort(0);//nur +
                                                                D=mmi->V3.determinieren(va,vb,vc);
                                                                if(D){
                                                                 a=mmi->V3.determinieren(o,vb,vc)/D;
                                                                 if((a>0)&&(a<lowesta)){
                                                                  c=mmi->V3.determinieren(va,vb,o)/D;
                                                                  if(c>=0){
                                                                   lowesta=a;
                                                                   h=t-s;
                                                                   h.normalisieren();
                                                                   e=h+cp->normale();
                                                                   if(sqrt(e[0]*e[0]+e[1]*e[1]+e[2]*e[2])<sqrt(2.0f)){
                                                                    lowestrawstatus=+1;
                                                                   }else{
                                                                    lowestrawstatus=-1;
                                                                   };
                                                                  };
                                                                 };  
                                                                }else{
                                                                 mmi->fehler("_statuskreuz::collidesemiplanar()","Hauptdeterminante bei causalhalbebenencollision ist null . dieser fall ist theoretisch nicht möglich .(parallelität).");
                                                                };
};

void _statuskreuz::collidedoublesemiplanar(_polygon*cp,_vertex*vm,_vertex*v0,_vertex*v1,_vektor3<_tg>&va,_vektor3<_tg>&s,_vektor3<_tg>&t,_vektor3<_tg>&o,_tg&lowesta,int&lowestrawstatus){
                                                                //hier liegt vertex-causalität vor
                                                                //die infinitation der ebene erfolgt nur ins positive (am besten keine nahenull-kompensation,
                                                                //bei parallelität poly semiplanar collidieren
                                                                _vektor3<_tg> vb;
                                                                _vektor3<_tg> vc;
                                                                _vektor3<_tg> h;
                                                                _vektor3<_tg> e;
                                                                _tg D,a,b,c;
                                                                _kantepolygon*kante;
                                                                //------------------
                                                                
                                                                vb=v0->ort()-vm->ort();
                                                                vc=v1->ort()-vm->ort();
                                                                D=mmi->V3.determinieren(va,vb,vc);
                                                                if(D){//wenn parallel dann semiplanar collidieren
                                                                 a=mmi->V3.determinieren(o,vb,vc)/D;
                                                                 if((a>0)&&(a<lowesta)){
                                                                  b=mmi->V3.determinieren(va,o,vc)/D;
                                                                  if((b>=0)/*&&(b<=1)*/){
                                                                   c=mmi->V3.determinieren(va,vb,o)/D;
                                                                   if((c>=0)/*&&(c<=1)*/){
                                                                    lowesta=a;
                                                                    h=t-s;
                                                                    h.normalisieren();
                                                                    e=h+cp->normale();
                                                                    if(sqrt(e[0]*e[0]+e[1]*e[1]+e[2]*e[2])<sqrt(2.0f)){
                                                                     lowestrawstatus=+1;
                                                                    }else{
                                                                     lowestrawstatus=-1;
                                                                    };
                                                                   };
                                                                  };
                                                                 };
                                                                }else{
                                                                 if(mmi->schreibenlogbuch()) mmi->schreiben("collidedoublesemiplanar : semiplanar weil parallel");
                                                                 cp->holenkante(vm,v0,kante);
                                                                 collidesemiplanar(cp,kante,va,s,t,o,lowesta,lowestrawstatus);
                                                                };
};
void _statuskreuz::unvisualisieren(){
                                                                if(debugcross) delete debugcross;
                                                                if(debugis) delete debugis;
                                                                if(debugle[0]) delete debugle[0];
                                                                if(debugle[1]) delete debugle[1];
                                                                debugcross=0;
                                                                debugis=0;
                                                                debugle[0]=0;
                                                                debugle[1]=0;
};
void _statuskreuz::visualisieren(){
                                                                _vektor4<_to> col;
                                                                unvisualisieren();
                                                                if(DW){
                                                                if(komplanar==0) col.setzen(0,1,0,0); else col.setzen(0.7f,1,0.7f,0);
                                                                debugcross=new _weltdebugkreuz(DW,pmiddle,0.05,col);
                                                                if(komplanar==0) col.setzen(0,1,0,0); else col.setzen(0.7f,1,0.7f,0);
                                                                debugis=new _weltdebugpfeil(DW,pmiddle,pstatussection->intersektion->ort(),0.01,0.01,col);
                                                                if(pleft[0]){
                                                                 if(komplanar==0) col.setzen(1,0.5f,0,0); else col.setzen(1,1,0,0);
                                                                 debugle[0]=new _weltdebugpfeil(DW,pmiddle,pleft[0]->ort(),0.07,0.03,col);
                                                                };
                                                                if(pleft[1]){
                                                                 if(komplanar==0) col.setzen(0,0.5f,1,0); else col.setzen(0,1,1,0);
                                                                 debugle[1]=new _weltdebugpfeil(DW,pmiddle,pleft[1]->ort(),0.07,0.03,col);
                                                                };
                                                                };
};
//******************************************************************************************************************************************************************************************************
//                                                              S T A T U S R E L E V A N Z
//******************************************************************************************************************************************************************************************************
_statusrelevanz::_statusrelevanz(_intersektion*v,_intersektion*i,_polygon*cp,_statusrelevanz*kp,bool ar,_tg a):_listenknotenbasissortiert<_statusrelevanz,_tg>(v,a){
                                                                causalpoly=cp;
                                                                autorelevant=ar;
                                                                alpha=a;
                                                                intersektion=i;
                                                                pwl=0;
                                                                verwalter=v;
                                                                komplanar=kp;
                                                                
};

_statusrelevanz::~_statusrelevanz(){
                                                                unvisualisieren();
};

void _statusrelevanz::visualisieren(){
                                                                _vektor4<_to> col;
                                                                //---------------
                                                                if(komplanar==false) col.setzen(0,0.4f,1,0); else col.setzen(1,0.4f,0,0);
                                                                unvisualisieren();
                                                                if(DW) pwl=new _weltdebugpfeil(DW,verwalter->ort(),intersektion->ort(),0.1,0.1,col);
};

void _statusrelevanz::unvisualisieren(){
                                                                if(pwl){
                                                                 delete pwl;
                                                                 pwl=0;
                                                                };
};
//******************************************************************************************************************************************************************************************************
//                                                              S T A T U S S E K T I O N 
//******************************************************************************************************************************************************************************************************

_statussektion::_statussektion(_intersektion*i,_polygon*p):_listenknotenbasis<_statussektion >(i){
                                                                intersektion=i;
                                                                poly=p;
};

_statussektion::~_statussektion(){
};
//******************************************************************************************************************************************************************************************************
//                                                              I N T E R S E K T I O N 
//******************************************************************************************************************************************************************************************************

_intersektion::_intersektion(_vektor3<_tg> _o):_listenknotenbasis<_intersektion >(){
                                                                //intersectionconstructor verwaltet koordinaten,markierung,isflag, vertex-Zeiger
                                                                //vorheriges und naechstes zeiger brauchen nicht initialisiert zu werden
                                                                markierung=0;
                                                                status=0;
                                                                o=_o;
                                                                vertex=0;
                                                                alpha=0;
                                                                //autorelevant=0;
                                                                debug=0;
                                                                //L->schreiben("_intersektion::reale Intersektion konstruiert.");
};

_intersektion::_intersektion(_vektor3<_tg> _o,_vertex*v):_listenknotenbasis<_intersektion >(){
                                                                markierung=0;
                                                                alpha=0;
                                                                vertex=v;
                                                                status=v->status();
                                                                //autorelevant=0;
                                                                o=_o;
                                                                debug=0;
                                                                //L->schreiben("_intersektion::vituelle Intersektion konstruiert.");

};

_intersektion::_intersektion(_listebasis<_intersektion >*li,_vektor3<_tg> _o,_tg s):_listenknotenbasis<_intersektion >(li){
                                                                //konstruktor für temporäre intersektion (z.B. zur fließkommaunschärfekompensation)
                                                                //intersectionconstructor verwaltet koordinaten,markierung,isflag, vertex-Zeiger
                                                                //vorheriges und naechstes zeiger brauchen nicht initialisiert zu werden
                                                                alpha=s;
                                                                o=_o;
                                                                markierung=0;
                                                                status=0;
                                                                vertex=0;
                                                                //autorelevant=0;
                                                                debug=0;
};

_intersektion::~_intersektion(){
                                                                //clear_ring(firststatussection);
                                                                if(debug) delete debug;
                                                                debug=0;
};

_vektor3<_tg>& _intersektion::ort(){
                                                                return(o);
};


void _intersektion::clearrelevance(){
                                                                _listebasis<_statusrelevanz >::loeschen();        
};

void _intersektion::getrelevance(_modifikationnetzintersektion*mmi,_polygon*p,_listebasis<_verbinderisintro >*isic){
                                                                //relevant heißt, dreieck d referenziert diese intersektion über den connector isic,
                                                                //wobei dann alle an der intersektion hängenden anderes-causaldreiecke abiteriert werden...
                                                                //tritt dann eine weitere intersektion mit dreieck d auf, so wurde diese intersektion als 
                                                                //relevant identifiziert
                                                                _verbinderisintro*iit;
                                                                _listesortiert<_intersektion,_tg> ll;
                                                                _liste<_tg> la;
                                                                char alarm;
                                                                bool iskoplanar;
                                                                _vektor3<_tg> v;
                                                                //--------------------
                                                                clearrelevance();
                                                                //causalpolygon iterierenen und mit denen relevante intersektion suchen
                                                                //
                                                                if(isic->anfang(iit))do{
                                                                 //iit->intersektion()->autorelevant=0;
                                                                 if(iit->intersektion()==this){
                                                                  ll.aushaengen();
                                                                  la.aushaengen();
                                                                  searchrelevance(p,iit->causalpolygon(),&ll);
                                                                  determinealphagroups(mmi,&ll,&la);
                                                                  limitrelevance(mmi,p,&ll,&la,iit->causalpolygon(),iit->polygonedgebounded(),iskoplanar);
                                                                  transferrelevance(mmi,&ll,iit->causalpolygon(),iskoplanar,false);
                                                                 };
                                                                 //dthisit=dthisit->naechstes;
                                                                }while(isic->naechstes(iit));//------------------------------------------------------------------------
                                                                //autorelevance,d-h wenn kante oder vertex intersektion, 
                                                                //dann vorheriges und naechstes-intersektion ebenfalls einhängen
                                                                alarm=0;
                                                                iskoplanar=false;
                                                                isic->anfang(iit);
                                                                if(iit->polygonedgebounded()){//if((iit->vertex())||(iit->kante())){
                                                                //if((firstisic->vertex)||(firstisic->kante)){
                                                                 if(naechstes()){
                                                                  ll.aushaengen();
                                                                  v=naechstes()->o-o;
                                                                  naechstes()->alpha=p->berechnenalpha(v);
                                                                  ll.einhaengen(naechstes(),naechstes()->alpha);
                                                                  transferrelevance(mmi,&ll,0,0,1);
                                                                 }else alarm=1;
                                                                 if(vorheriges()){
                                                                  ll.aushaengen();
                                                                  v=vorheriges()->o-o;
                                                                  vorheriges()->alpha=p->berechnenalpha(v);
                                                                  ll.einhaengen(vorheriges(),vorheriges()->alpha);
                                                                  transferrelevance(mmi,&ll,0,0,1);
                                                                 }else alarm=1;
                                                                 if(alarm){
                                                                  //peep(1);
                                                                  mmi->fehler("void _intersektion::getrelevance(_modifikationnetzintersektion*mmi,_polygon*p,_listebasis<_verbinderisintro >*isic)","kante-oder vertex-intersektion besitzt keine strukturelle integrität.");
                                                                 };
                                                                };
};

void _intersektion::transferrelevance(_modifikationnetzintersektion*mmi,_listesortiert<_intersektion,_tg>*ll,_polygon*causalpoly,bool iskoplanar,bool autorelevant){
                                                                //funktion hängt die objecte der localen liste ll in die statusrelevance-liste ein
                                                                //dabei wird nach alpha sortiert unredundant eingefügt, komplanarität besitzt überschreibende
                                                                //eigenschaft
                                                                _statusrelevanz*is0;
                                                                _statusrelevanz*is1;
                                                                _statusrelevanz*ist;
                                                                _statusrelevanz*srit;
                                                                _listenknotensortiert<_intersektion,_tg>*iit;
                                                                _tg a0;
                                                                _tg a1;
                                                                //_tg delta;
                                                                _vektor3<_tg> v0;
                                                                _vektor3<_tg> v1;
                                                                char code;
                                                                //------------------
                                                                code=0;
                                                                is0=0;
                                                                is1=0;
                                                                if(ll->anfang(iit))do{
                                                                 ist=0;
                                                                 if(anfang(srit))do{
                                                                  if(srit->intersektion==iit->objekt()){
                                                                   //dieselbs intersektion it schon relevant,
                                                                   //nur komplanarflags verodern
                                                                   //autorelevant flags verodern
                                                                   ist=srit; 
                                                                   code=0;
                                                                  }else{
                                                                   a0=srit->intersektion->alpha;
                                                                   a1=iit->objekt()->alpha;
                                                                   if(fabs(differenz(a0,a1))<=mmi->nearzerovalue()){
                                                                    //intersektion ii->objekt und srite->intersektion sind zu nahe zusammen,
                                                                    //es muss anhand des abstandes entschieden werden, welche in der relevanzliste bleibt
                                                                    v0=srit->intersektion->ort()-o;
                                                                    v1=iit->objekt()->ort()-o;
                                                                    if(v1.laenge()<v0.laenge()){
                                                                     //neue intersectionn rein , alte raus
                                                                     //komplanar flags verodern
                                                                     //autorelevant falgs verodern
                                                                     code=1;
                                                                     ist=srit;
                                                                    }else{
                                                                     //alte intersektion bleibt drin
                                                                     //komplanar flags verodern
                                                                     //autorelevant falgs verodern
                                                                     code=2;
                                                                     ist=srit;
                                                                    };
                                                                   };
                                                                  };
                                                                 }while((naechstes(srit))&&(ist==0));
                                                                 if(ist==0) {
                                                                  ist=new _statusrelevanz(this,iit->objekt(),causalpoly,0/*iskoplanar*/,autorelevant,iit->objekt()->alpha);
                                                                 }else{
                                                                  /*if(iskoplanar){
                                                                   ist->komplanar=true;
                                                                   ist->causalpoly=causalpoly;
                                                                  };*/
                                                                  if(autorelevant){
                                                                   ist->autorelevant=true;
                                                                  };
                                                                  switch(code){
                                                                   case(0):
                                                                    //if(autorelevant){
                                                                    // ist->autorelevant=true;
                                                                    //};
                                                                    break;
                                                                   case(1):
                                                                    ist->intersektion=iit->objekt();
                                                                   // if(iskoplanar){
                                                                   //  ist->komplanar=true;
                                                                   //  ist->causalpoly=causalpoly;
                                                                   // };
                                                                   // if(autorelevant){
                                                                   //  ist->autorelevant=true;
                                                                   // };
                                                                    break;
                                                                   case(2):
                                                                    //if(iskoplanar){
                                                                    // ist->komplanar=true;
                                                                    // ist->causalpoly=causalpoly;
                                                                    //};
                                                                    //if(autorelevant){
                                                                    // ist->autorelevant=true;
                                                                    //};
                                                                    break;
                                                                  };
                                                                  //if(iit->objekt()->autorelevant==0){
                                                                  // ist->intersektion->autorelevant=0;
                                                                  //};
                                                                 };
                                                                 if(is0==0){
                                                                  is0=ist; 
                                                                 }else{
                                                                  if(is1==0) is1=ist;
                                                                 };
                                                                }while(ll->naechstes(iit));
                                                                if(iskoplanar){
                                                                 if(deltaalpha(is0->alpha,is1->alpha)<deltaalpha(is1->alpha,is0->alpha)){
                                                                  is0->komplanar=is1;
                                                                 }else{
                                                                  is1->komplanar=is0;
                                                                 };
                                                                 is0->causalpoly=causalpoly;
                                                                 is1->causalpoly=causalpoly;
                                                                };
};

void _intersektion::searchrelevance(_polygon*p,_polygon*cp,_listesortiert<_intersektion,_tg>*ll){
                                                                //das oben identifizierte causaldreieck kann nun eine weitere intersektion ausser dieser
                                                                //mit dreieck d haben, dabei dreieck-,kante- und vertexintroconnectoren untersuchen (virtuelle
                                                                //intersektion brauchen nicht iteriert zu werden, da sie keine connectorstruktur
                                                                //besitzen)
                                                                _vertex*vit;
                                                                _listenknoten<_vertex>*lnvit;
                                                                _listenknoten<_kantepolygon >*pit;
                                                                //------------
                                                                searchrelevance(p,cp->verbinderisintroliste(),ll);
                                                                if(cp->kanten()->anfang(pit))do{
                                                                 searchrelevance(p,pit->objekt()->verbinderisintroliste(),ll);
                                                                }while(cp->kanten()->naechstes(pit));
                                                               // vit=cp->vertex();
                                                                //if(vit)do{
                                                                iterierenliste(cp,lnvit,
                                                                 vit=lnvit->objekt();
                                                                 searchrelevance(p,vit->verbinderisintroliste(),ll);
                                                                );
                                                                // vit=vit->naechstes(cp);
                                                                //}while(vit!=cp->vertex());
};

void _intersektion::searchrelevance(_polygon*p,_listebasis<_verbinderisintro >*isiccd,_listesortiert<_intersektion,_tg >*ll){
                                                                //hier untersuchen,ob die causalintroconnectoren wiederum dreieck d
                                                                //als causaldreieck identifizieren
                                                                _verbinderisintro*cdtestit;
                                                                _vektor3<_tg> v;
                                                                //---------------------
                                                                if(isiccd->anfang(cdtestit))do{
                                                                 //cdtestit->intersektion()->autorelevant=0;
                                                                 if(cdtestit->intersektion()!=this)
                                                                 if(cdtestit->causalpolygon()==p) {
                                                                  v=cdtestit->intersektion()->o-o;
                                                                  cdtestit->intersektion()->alpha=p->berechnenalpha(v);
                                                                  ll->einhaengen(cdtestit->intersektion(),cdtestit->intersektion()->alpha);
                                                                 };
                                                                }while(isiccd->naechstes(cdtestit));
};

char _intersektion::getcorrespondingisintroconnector(_polygon*p,_verbinderisintro*dit,_verbinderisintro*&cit){
                                                                char r;
                                                                _polygon*cp;
                                                                _listenknoten<_kantepolygon >*pit;
                                                                _vertex*vit;
                                                                _listenknoten<_vertex>*lnvit;
                                                                //---------
                                                                r=0;
                                                                cit=0;
                                                                cp=dit->causalpolygon();
                                                                r=getcorrespondingisintroconnector(p,dit,cp->verbinderisintroliste(),cit);
                                                                if(r==0){
                                                                 if(cp->kanten()->anfang(pit))do{
                                                                  r=getcorrespondingisintroconnector(p,dit,pit->objekt()->verbinderisintroliste(),cit);
                                                                 }while((r==0)&&(cp->kanten()->naechstes(pit)));
                                                                 if(r==0){
                                                                  //vit=cp->vertex();
                                                                  //if(vit)do{
                                                                  if(cp->anfang(lnvit))do{
                                                                   vit=lnvit->objekt();
                                                                   r=getcorrespondingisintroconnector(p,dit,vit->verbinderisintroliste(),cit);
                                                                  // vit=vit->naechstes(cp);
                                                                  }while((cp->naechstes(lnvit))&&(r==0));
                                                                 };
                                                                };
                                                                if(r==0){
                                                                // peep(1);
                                                                // fehler("_intersektion::getcorrespondingisintroconnector(_verbinderisintro*,_verbinderisintro*&)","correspondierender introconnector konnte im causaldreieck nicht identifiziert werden.");
                                                                };
                                                                return(r);
};

char _intersektion::getcorrespondingisintroconnector(_polygon*p,_verbinderisintro*dit,_listebasis<_verbinderisintro >*isic,_verbinderisintro*&cit){
                                                                _verbinderisintro*iit;
                                                                char r;
                                                                //--------------------
                                                                r=0;
                                                                cit=0;
                                                                if(isic->anfang(iit))do{
                                                                 if((iit->pcausalpoly==p)&&(iit->intersektion()==dit->intersektion())){
                                                                  cit=iit;
                                                                  r=1;
                                                                 };
                                                                }while((isic->naechstes(iit))&&(cit==0));
                                                                return(r);
};

void _intersektion::determinealphagroups(_modifikationnetzintersektion*mmi,_listesortiert<_intersektion,_tg>*ll,_liste<_tg>*la){
                                                                //funktion untersucht unscharf, welche winkelgruppen die intersektion liste ll liefert
                                                                //d.h unredundantes übertragen der alpha von ll nach la 
                                                                _tg nz=mmi->nearzerovalue();
                                                                _listenknotensortiert<_intersektion,_tg>*it;
                                                                ::_listenknoten<_tg>*fit;
                                                                char ok;
                                                                //--------------------------
                                                                if(ll->anfang(it))do{
                                                                 if(la->anfang(fit)){
                                                                  ok=1;
                                                                  do{
                                                                   if(fabs(*fit->objekt()-it->objekt()->alpha)<=nz) ok=0;
                                                                  }while(la->naechstes(fit));
                                                                  if(ok)la->einhaengen(&it->objekt()->alpha);
                                                                 }else{
                                                                  la->einhaengen(&it->objekt()->alpha);
                                                                 };
                                                                }while(ll->naechstes(it));
};

_tg _intersektion::deltaalpha(_tg a,_tg b)const{
                                                                //ermittelt die direktionale absolutdifferenz zwischen den beiden absolutwinkelargumenten a und b
                                                                _tg delta;
                                                                //---------
                                                                if(b<a) b+=360;
                                                                delta=b-a;
                                                                return(delta);
};

_tg _intersektion::differenz(_tg a0,_tg a1)const{
                                                                _tg delta;
                                                                //---------
                                                                if(a0>360) a0-=360;
                                                                if(a1>360) a1-=360;
                                                                if(a0<0) a0+=360;
                                                                if(a1<0) a1+=360;
                                                                if(a0>a1) delta=a0-a1; else delta=a1-a0;
                                                                if(delta>180) delta=(180-delta)+180;
                                                                return(delta);
};

void _intersektion::limitrelevance(_modifikationnetzintersektion*mmi,_polygon*p,_listesortiert<_intersektion,_tg>*ll,_liste<_tg>*la,_polygon*cp,bool edgebounded,bool&iskoplanar){
                                                                //wenn liste->anzahl > 2 funktion eliminiert unrelevante intersectioneinträge
                                                                //funktion muss minimum und maximum eintrag der liste ll identifizieren
                                                                //d.h. primärsortieren nach winkel und sekundärbewerten nach abstand
                                                                //es entsteht ein minimum winkel und ein maximum winkel, gibt es noch andere ist koplanar zu flaggen
                                                                _intersektion*i[2];
                                                                _listenknotensortiert<_intersektion,_tg>*iit;
                                                                _tg alpha[2];
                                                                _intersektion*ih;
                                                                _listenknotensortiert<_intersektion,_tg>*it;
                                                                _listenknotensortiert<_intersektion,_tg>*itmaxdelta;
                                                                _listenknotensortiert<_intersektion,_tg>*ip;
                                                                _listenknotensortiert<_intersektion,_tg>*in;
                                                                _tg maxdelta;
                                                                _tg lowd;
                                                                _tg d;
                                                                _vektor3<_tg> v;
                                                                _vektor3<_tg> w;
                                                                _tg nz=mmi->nearzerovalue();
                                                                int n;
                                                                int e;
                                                                _tg lowest[2];
                                                                char cond0;
                                                                char cond1;
                                                                char cond2;
                                                                _tg D;
                                                                _vertex*vit;
                                                                _listenknoten<_vertex>*lnvit;
                                                                //----------------------------------------------------
                                                                iskoplanar=0;
                                                                i[0]=0;
                                                                i[1]=0;
                                                                n=la->anzahl();
                                                                if(n>2){
                                                                 //-----------------------------------------------------------------------------------------------------
                                                                 //ist jedenfalls komplanar
                                                                 //den firstzeiger der sortierten liste ll so setzen, das hinter disem sich der
                                                                 //größte delta-alpha winkel liegt, es kann bei la->anzahl()>2 davon ausgegangen werden,
                                                                 // dass dieser auch im bereich der unschärfe eindeutig ist
                                                                 itmaxdelta=0;
                                                                 maxdelta=0;
                                                                 if(ll->anfang(it))do{
                                                                  if(itmaxdelta==0){
                                                                   itmaxdelta=it;
                                                                   maxdelta=deltaalpha(it->objekt()->alpha,it->naechstes()->objekt()->alpha);
                                                                  }else{
                                                                   d=deltaalpha(it->objekt()->alpha,it->naechstes()->objekt()->alpha);
                                                                   if(d>maxdelta){
                                                                    itmaxdelta=it;
                                                                    maxdelta=d;
                                                                   };
                                                                  };
                                                                 }while(ll->naechstes(it));
                                                                 if(itmaxdelta){
                                                                  while(ll->erstes()!=itmaxdelta->naechstes()) ll->rotierennaechstes();
                                                                 }else{
                                                                  mmi->fehler("void _intersektion::limitrelevance(_polygon*p,_listesortiert<_intersektion,_tg>*ll,_liste<_tg>*la,char&iskoplanar)","itmaxdelta==0");
                                                                 };
                                                                 //while(deltaalpha(ll->erstes()->objekt()->alpha,ll->erstes()->naechstes()->objekt()->alpha)<180){
                                                                 // ll->rotierennaechstes();//ll->erstes=ll->erstes->naechstes;
                                                                 // L->schreiben("w3");
                                                                 //};
                                                                 //ll->rotierennaechstes();
                                                                 iskoplanar=1;
                                                                 //i[0] bestimmen
                                                                 ll->anfang(it);
                                                                 i[0]=it->objekt();
                                                                 v=i[0]->ort()-o;
                                                                 lowd=d=v.laenge();
                                                                 while(fabs(differenz(it->naechstes()->objekt()->alpha,it->objekt()->alpha))<=nz){
                                                                  ih=it->objekt();
                                                                  in=it;
                                                                  v=ih->ort()-o;
                                                                  d=v.laenge();
                                                                  if(d<lowd){
                                                                   lowd=d;
                                                                   i[0]=ih;
                                                                  };
                                                                  it=it->naechstes();
                                                                 };
                                                                 //i[1] bestimmen
                                                                 ll->anfang(it);
                                                                 ll->vorheriges(it);
                                                                 i[1]=it->objekt();
                                                                 v=i[1]->ort()-o;
                                                                 lowd=d=v.laenge();
                                                                 while(fabs(differenz(it->objekt()->alpha,it->vorheriges()->objekt()->alpha))<=nz){
                                                                  ih=it->objekt();
                                                                  ip=it;
                                                                  v=ih->ort()-o;
                                                                  d=v.laenge();
                                                                  if(d<lowd){
                                                                   lowd=d;
                                                                   i[1]=ih;
                                                                  };
                                                                  it=it->vorheriges();
                                                                 };
                                                                }else
                                                                if(n==2){
                                                                 //-----------------------------------------------------------------------------------------------------
                                                                 //ist vielleicht komplanar, i[0] und i[1] können anhand des abstandes
                                                                 //bestimmt werden (in der jeweiligen winkelgruppe)
                                                                 alpha[0]=*la->erstes()->objekt();//1.winkelgruppe;
                                                                 alpha[1]=*la->erstes()->naechstes()->objekt();//2.winkelgruppe
                                                                 i[0]=0;
                                                                 i[1]=0;
                                                                 if(ll->anfang(iit))do{
                                                                  for(e=0;e<2;e++){
                                                                   if(fabs(differenz(iit->objekt()->alpha,alpha[e]))<=nz){
                                                                    if(i[e]==0){
                                                                     i[e]=iit->objekt();
                                                                     v=i[e]->ort()-o;
                                                                     lowest[e]=v.laenge();
                                                                    }else{
                                                                     ih=iit->objekt();
                                                                     v=ih->ort()-o;
                                                                     d=v.laenge();
                                                                     if(d<lowest[e]){
                                                                      i[e]=ih;
                                                                      lowest[e]=d;
                                                                     };
                                                                    };
                                                                   };
                                                                  };
                                                                 }while(ll->naechstes(iit));
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 //komplanarität bestimmen, dazu folgende untersuchungen machen:
                                                                 //1. liegen alle drei intersektion auf einer linie ? (cond0)
                                                                 //2. liegen punkte des causalpolygons ausserhalb der ebene von p ? (cond1)
                                                                 //3. ist this edgebounded an p (cond2)
                                                                 
                                                                 cond0=0;
                                                                 v=i[0]->o-o;
                                                                 w=i[1]->o-o;
                                                                 v.normalisieren();
                                                                 w.normalisieren();
                                                                 v+=w;
                                                                 if(v.laenge()<=nz){
                                                                  cond0=1;
                                                                 };
                                                                 //causaliteration
                                                                 cond1=0;
                                                                 D=mmi->V3.determinieren(p->ebene(0),p->ebene(1),p->normale());
                                                                 //vit=cp->vertex();
                                                                 //if(vit)do{
                                                                 iterierenliste(cp,lnvit,
                                                                  vit=lnvit->objekt();
                                                                  d=fabs(mmi->V3.determinieren(p->ebene(0),p->ebene(1),vit->ort()-p->mitte() )/D);
                                                                  if(d>nz) cond1=1;
                                                                  //vit=vit->naechstes(cp);
                                                                 //}while(cp->vertex()!=vit);
                                                                 );
                                                                 if(edgebounded) cond2=1; else cond2=0;
                                                                 //auswerten
                                                                 if(cond1==1){
                                                                  iskoplanar=0;
                                                                 }else{
                                                                  if(cond0==1){//auf einer linie
                                                                   if(cond2==1){
                                                                    iskoplanar=0;//edgebounded, auf einer linie, sonst keine intersektion->unkomplanar
                                                                   }else{
                                                                    iskoplanar=1;//sehr unwahrscheinlich:this in der p-ebene, auf einer linie, aber sonst keine weiteren intersektion relevant
                                                                   };
                                                                  }else{//nicht auf einer linie
                                                                   if(cond2==1){
                                                                    iskoplanar=1;//ok kommt vor: edgebounded, nicht auf einer linie
                                                                   }else{
                                                                    iskoplanar=1;//ok kommt vor: nicht auf einer linie und in der ebene mit zwei gruppen 
                                                                   };
                                                                  };
                                                                 };
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 /*d=fabs(differenz(i[0]->alpha,i[1]->alpha));
                                                                
                                                                 if(d>nz){
                                                                  iskoplanar=1;
                                                                  mmi->schreiben("d=",d);
                                                                 }else{
                                                                  iskoplanar=0;
                                                                 };*/
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 
                                                                }else
                                                                if(n==1){
                                                                 //---------------------------------------------ist nicht komplanar, i[0] anhand des abstands bestimmen
                                                                 iskoplanar=0;
                                                                 alpha[0]=*(la->erstes()->objekt());
                                                                 i[0]=0;
                                                                 i[1]=0;
                                                                 if(ll->anfang(iit))do{
                                                                  if(fabs(differenz(iit->objekt()->alpha,alpha[0]))<=nz){
                                                                   if(i[0]==0){
                                                                    i[0]=iit->objekt();
                                                                    v=i[0]->ort()-o;
                                                                    lowest[0]=v.laenge();
                                                                   }else{
                                                                    ih=iit->objekt();
                                                                    v=ih->ort()-o;
                                                                    d=v.laenge();
                                                                    if(d<lowest[0]){
                                                                     i[0]=ih;
                                                                     lowest[0]=d;
                                                                    };
                                                                   };
                                                                  };
                                                                 }while(ll->naechstes(iit));
                                                                };
                                                                //ll bearbeiten
                                                                ll->aushaengen();
                                                                if(i[0]) ll->einhaengen(i[0],i[0]->alpha);
                                                                if(i[1]) ll->einhaengen(i[1],i[1]->alpha);
};

void _intersektion::switchsection(_polygon*p){
                                                                _statussektion*ss;
                                                                _statussektion*sf;
                                                                //-----------------
                                                                sf=0;
                                                                if(anfang(ss))do{
                                                                 if(ss->poly==p) sf=ss;
                                                                }while((naechstes(ss))&&(sf==0));
                                                                if(sf){
                                                                 _listebasis<_statussektion >::erstes(sf);
                                                                };
};

char _intersektion::checkedgekoherence(_polygon*p){
                                                                //funktion liefert 1,wenn intersektion von poly p über kante oder vertex verwaltet wird
                                                                //also wird besser geprüft, ob intersektion von ebene aus refernziert wird, planekoherenz überprüfen
                                                                _verbinderisintro*iit;
                                                                char r;
                                                                //----------------
                                                                r=0;
                                                                if(p->verbinderisintroliste()->anfang(iit))do{
                                                                 if(iit->intersektion()==this) r=1;
                                                                }while((p->verbinderisintroliste()->naechstes(iit))&&(r==0));
                                                                return(1-r);
};

void _intersektion::visualisieren(){
                                                                _vektor4<_to> col;
                                                                //----------------
                                                                if(vertex) col.setzen(1,0.6f,0.5f,0); else col.setzen(0.2f,1,1,0);
                                                                if(debug) delete debug;
                                                                if(DW) debug=new _weltdebugkreuz(DW,o,0.1,col);
};

void _intersektion::visualizestatusstruct(){
                                                                _statussektion*ss;
                                                                _statuskreuz*sc;
                                                                //---------------
                                                                if(anfang(ss))do{
                                                                 if(ss->anfang(sc))do{
                                                                  sc->visualisieren();
                                                                 }while(ss->naechstes(sc));
                                                                }while(naechstes(ss));
};
//******************************************************************************************************************************************************************************************************
//                                                              R I N G P A R T I T I O N 
//******************************************************************************************************************************************************************************************************

_ringpartition::_ringpartition(_polygon*p):_listenknotenbasis<_ringpartition >(p->ringpartitionsliste()){
                                                                isolated=1;
                                                                status=0;
                                                                surroundingringpartition=0;
                                                                poly=p;
};

_ringpartition::~_ringpartition(){
                                                                unvisualisieren();
};

_polygon *_ringpartition::polygon(){
                                                                return(poly);        
};

void _ringpartition::setangle(_tg a){
                                                                rightangle=a;
};

void _ringpartition::integrate(){
                                                                _ringsektion*ri;
                                                                _verbindergeometrisch*g;
                                                                //--------------
                                                                //richtet innerhalb der ringpartition die geoconnectoren ein
                                                                //es darf keine vereinigte ringpartition übergeben werden !
                                                                if(anfang(ri))do{
                                                                 ri->loeschen();
                                                                 new _verbindergeometrisch(ri);
                                                                }while(naechstes(ri));
                                                                if(anfang(ri))do{
                                                                 g=ri->erstes();
                                                                 g->geoconnector[0]=ri->naechstes()->erstes();
                                                                 g->geoconnector[1]=ri->vorheriges()->erstes();
                                                                 g->aktualisieren();
                                                                }while(naechstes(ri));
};

void _ringpartition::flaggeoconnector(int f){
                                                                _ringsektion*rit;
                                                                _verbindergeometrisch*git;
                                                                //--------------
                                                                if(anfang(rit))do{
                                                                 if(rit->anfang(git))do{
                                                                  git->markierung=f;
                                                                 }while(rit->naechstes(git));
                                                                }while(naechstes(rit));
};


bool _ringpartition::punktinnerhalb(_vektor3<_tg> go){
                                                                //funktion stellt fest, ob der punkt go sich
                                                                //geometrisch innerhalb der ringpartition befindet
                                                                //und liefert dann true zurück
                                                                bool r;
                                                                _vektor3<_tg> gv;
                                                                _vektor3<_tg> eo;
                                                                _vektor3<_tg> ea;
                                                                _vektor3<_tg> eb;
                                                                _vektor3<_tg> h;
                                                                _vektor3<_tg> s;
                                                                int hc;
                                                                _tg D,c,a;
                                                                _ringsektion*rit;
                                                                _vektoranalysis3<_tg> V3;
                                                                //-------
                                                                r=false;
                                                                eb=poly->normale();
                                                                gv=poly->ebene(0)+poly->ebene(1);
                                                                gv.normalisieren();
                                                                if(anfang(rit)){//gv optimieren
                                                                 h=rit->intersektion->ort();
                                                                 rit=rit->naechstes();
                                                                 h=rit->intersektion->ort()-h;
                                                                 h*=0.498765;
                                                                 gv=h-go;
                                                                 gv.normalisieren();
                                                                };
                                                                
                                                                hc=0;
                                                                s=go;
                                                                if(anfang(rit))do{
                                                                 eo=rit->intersektion->ort();
                                                                 ea=rit->naechstes()->intersektion->ort() - eo;
                                                                 D=V3.determinieren(ea,eb,-gv);
                                                                 if(fabs(D)>nahenull){
                                                                  c=V3.determinieren(ea,eb,go-eo)/D;
                                                                  if(c>=0){
                                                                   a=V3.determinieren(go-eo,eb,-gv)/D;
                                                                   if((a>=0)&&(a<1)){
                                                                    s=go+gv*c;
                                                                    hc++;
                                                                   };
                                                                  };
                                                                 };
                                                                 
                                                                 
                                                                }while(naechstes(rit));
                                                                
                                                                
/*
                                                                
                                                                c0=poly->groessterindex(0);
                                                                c1=poly->groessterindex(1);
                                                                nv.setzen(-gv[c0],-gv[c1]);
                                                                nw.setzen(gw[c0],gw[c1]);
                                                                currentstate=0;
                                                                switchcount=0;
                                                                
                                                                if(anfang(rit))do{
                                                                 e.setzen(
                                                                 rit->intersektion->ort()[c0]-go[c0],
                                                                 rit->intersektion->ort()[c1]-go[c1]);
                                                                 D=V2.determinieren(nv,nw);
                                                                 if(D){
                                                                 
                                                                 
                                                                  
                                                                  
                                                                  vv=V2.determinieren(e,nw)/D;
                                                                  ww=V2.determinieren(nv,e)/D;
                                                                  if(currentstate==0){
                                                                  
                                                                   
                                                                   if(ww>=0) currentstate=+1; else currentstate=-1;
                                                                  
                                                                  
                                                                  }else{
                                                                   
                                                                   
                                                                   if(ww>=0) {
                                                                    if(currentstate==-1){
                                                                     currentstate=+1;
                                                                     if(vv>=0) switchcount++;
                                                                    };
                                                                   }else{
                                                                    if(currentstate==+1){
                                                                     currentstate=-1;
                                                                     if(vv>=0) switchcount++;
                                                                    };
                                                                   };
                                                                  
                                                                  
                                                                  };
                                                                  
                                                                  
                                                                  
                                                                 };
                                                                }while(naechstes(rit));
                                                                
                                                                
                                                                if((switchcount%2)==1) r=true; else r=false;
                                                                L->schreiben("SWITCHCOUNT : ",(int)switchcount);
                                                                */
                                                                if((hc%2)==1) r=true; else r=false;
                                                                return(r);
};










/*

char _modifikationnetzintersektion::pointinpartition(_polygon*p,_ringpartition*rp,_vektor<_tg>&o,_vektor<_tg>&v,_vektor<_tg>&w,int&switchcount){
                                                                //dies ist eine in bezug auf fließkommaunschärfe relativ sichere
                                                                //funktion zur surroundingringpartitiondetermination-> sie arbeitet
                                                                //lediglich mit ebeneparametern (+/-) und stellt so richtungsinversionen
                                                                //des gedachten lotvektors auf die gerade o-v fest; d.h die funktion bestimmt
                                                                //nur, ob der punkt o sich innerhalb oder ausserhalb der ringpartition rp befindet
                                                                //zur koherenzdetermination muss wiederrum collisionsanalytik angewandt werden...
                                                                char r;
                                                                _ringsektion*rit;
                                                                int currentstate;
                                                                _vektor<_tg> e(2);
                                                                int c0,c1;
                                                                _tg D,vv,ww;
                                                                _vektor<_tg> nv(2);
                                                                _vektor<_tg> nw(2);
                                                                //---------
                                                                // ********** DEBUG ***********
                                                                if(dbscreen) dbscreen->schreiben("Punkt innerhalb von rp?",pdbcolfunc);
                                                                // ****************************
                                                                c0=p->groessterindex(0);
                                                                c1=p->groessterindex(1);
                                                                nv.setzen(-v[c0],-v[c1]);
                                                                nw.setzen(w[c0],w[c1]);
                                                                currentstate=0;
                                                                switchcount=0;
                                                                r=0;
                                                                if(rp->anfang(rit))do{
                                                                 e.setzen(
                                                                 rit->intersektion->ort()[c0]-o[c0],
                                                                 rit->intersektion->ort()[c1]-o[c1]);
                                                                 D=V2.determinieren(nv,nw);
                                                                 if(D){
                                                                 
                                                                 
                                                                  
                                                                  
                                                                  vv=V2.determinieren(e,nw)/D;
                                                                  ww=V2.determinieren(nv,e)/D;
                                                                  if(currentstate==0){
                                                                  
                                                                   
                                                                   if(ww>=0) currentstate=+1; else currentstate=-1;
                                                                  
                                                                  
                                                                  }else{
                                                                   
                                                                   
                                                                   if(ww>=0) {
                                                                    if(currentstate==-1){
                                                                     currentstate=+1;
                                                                     if(vv>=0) switchcount++;
                                                                    };
                                                                   }else{
                                                                    if(currentstate==+1){
                                                                     currentstate=-1;
                                                                     if(vv>=0) switchcount++;
                                                                    };
                                                                   };
                                                                  
                                                                  
                                                                  };
                                                                  
                                                                  
                                                                  
                                                                 };
                                                                }while(rp->naechstes(rit));
                                                                r=(char)switchcount&2;
                                                                return(r);
};


*/















void _ringpartition::unvisualisieren(){
                                                                pdbcrosses.loeschen();
                                                                pdbarrows.loeschen();
};

void _ringpartition::visualisieren(){
                                                                _vektor4<_to> col;
                                                                _vektor3<_tg> x;
                                                                _vektor3<_tg> y;
                                                                _ringsektion*rit;
                                                                _ringsektion*rn;
                                                                _verbindergeometrisch*git;
                                                                _verbindergeometrisch*giit;
                                                                _verbindergeometrisch*giin;
                                                                _vektor3<_tg> off;
                                                                //----------
                                                                if(DW){
                                                                flaggeoconnector(1);
                                                                unvisualisieren();
                                                                off=poly->normale()*0.06;
                                                                if(anfang(rit))do{
                                                                 col.setzen(0.1f,0.1f,1,0);
                                                                 x=rit->intersektion->ort();
                                                                 //pdbcrosses.einhaengen(new _weltdebugkreuz(W,x+off,0.03,col));
                                                                 rn=rit->naechstes();
                                                                 col.setzen(0.6f,0.4f,0.8f,0);
                                                                 pdbarrows.einhaengen(new _weltdebugpfeil(DW,x+off,off+rn->intersektion->ort(),0.1,0.04,col));
                                                                }while(naechstes(rit));
                                                                if(anfang(rit))do{
                                                                 if(rit->anfang(git))do{
                                                                  if(git->markierung==1){
                                                                   giit=git;
                                                                   do{
                                                                    giin=giit->geoconnector[0];
                                                                    x=giit->ringsection->intersektion->ort();
                                                                    y=giin->ringsection->intersektion->ort();
                                                                    col.setzen(1,0,0.9f,0);
                                                                    pdbarrows.einhaengen(new _weltdebugpfeil(DW,x+off*2,y+off*2,0.04,0.03,col));
                                                                    x=giit->mitte;
                                                                    y=giit->mitte+giit->normale;
                                                                    col.setzen(1,0.1f,0.1f,0);
                                                                    pdbarrows.einhaengen(new _weltdebugpfeil(DW,x+off*2,y+off*2,0.04,0.03,col));
                                                                    giit->markierung=0;
                                                                    giit=giin;
                                                                   }while(giit!=git);
                                                                  };
                                                                 }while(rit->naechstes(git));
                                                                }while(naechstes(rit));
                                                                };
};
//******************************************************************************************************************************************************************************************************
//                                                              R I N G S E K T I O N 
//******************************************************************************************************************************************************************************************************
_ringsektion::_ringsektion(_ringpartition*rp,_statuskreuz*s):_listenknotenbasis<_ringsektion >(rp){
                                                                statuscross=s;
                                                                intersektion=statuscross->statussection()->intersektion;
                                                                ringpartition=rp;
                                                                performed=0;
}; 

_ringsektion::~_ringsektion(){
};
//******************************************************************************************************************************************************************************************************
//                                                              V E R B I N D E R G E O M E T R I S C H
//******************************************************************************************************************************************************************************************************

_verbindergeometrisch::_verbindergeometrisch(_ringsektion*r):_listenknotenbasis<_verbindergeometrisch >(r){
                                                                init(r,this,this);
};

_verbindergeometrisch::_verbindergeometrisch(_ringsektion*r,_verbindergeometrisch*n,_verbindergeometrisch*p):_listenknotenbasis<_verbindergeometrisch >(r){
                                                                init(r,n,p);
};

void _verbindergeometrisch::init(_ringsektion*r,_verbindergeometrisch*n,_verbindergeometrisch*p){
                                                                ringsection=r;
                                                                geoconnector[0]=n;
                                                                geoconnector[1]=p;
                                                                aktualisieren();
};

_verbindergeometrisch::~_verbindergeometrisch(){
                                                                unvisualisieren();
};

void _verbindergeometrisch::aktualisieren(){
                                                                _intersektion*is;
                                                                _intersektion*io;
                                                                _polygon*p;
                                                                _vektoranalysis3<_tg> V3;
                                                                //----------
                                                                if(geoconnector[0]==0){
                                                                 //fehler("void _verbindergeometrisch::aktualisieren()","geoconnector[0] == 0.");
                                                                };
                                                                if(geoconnector[1]==0){
                                                                 //fehler("void _verbindergeometrisch::aktualisieren()","geoconnector[1] == 0.");
                                                                };
                                                                p=ringsection->ringpartition->poly;
                                                                is=ringsection->intersektion;
                                                                if(geoconnector[0]==this){
                                                                 mitte=is->ort();
                                                                 vektor=p->ebene(0);
                                                                 normale=p->ebene(1);
                                                                 normale.normalisieren();
                                                                 alpha=90;
                                                                }else{
                                                                 io=geoconnector[0]->ringsection->intersektion;
                                                                 //if(io==0) fehler("_verbindergeometrisch::aktualisieren()","io==0.");
                                                                 vektor=io->ort()-is->ort();
                                                                 mitte=is->ort()+vektor*0.5;
                                                                 
                                                                 /*
                                                                //_tg _polygon::berechnenalpha(const _vektor<_tg>&v)const{
                                                                //_tg alpha;
                                                                _tg beta;
                                                                _vektor<_tg> a0;
                                                                _vektor<_tg> a1;
                                                                _vektor<_tg> v;
                                                                //---------------
                                                                v=vektor;
                                                                v.normalisieren();
                                                                L->schreiben("vektor p->plane0 = ",p->ebene(0));
                                                                L->schreiben("vektor p->plane1 = ",p->ebene(1));
                                                                L->schreiben("vektor vektor    = ",v);
                                                                if(v.holendimension()==3){
                                                                 a0=p->ebene(0);
                                                                 a1=v;
                                                                 a0.normalisieren();
                                                                 a1.normalisieren();
                                                                 alpha=a0.winkel(a1);
                                                                 L->schreiben("geoupdate:alpha=",alpha);
                                                                 a0=p->ebene(1);
                                                                 a0.normalisieren();
                                                                 
                                                                 
                                                               //  beta=a0.winkel(a1);
                                                                 _tg n=a0.laenge()*a1.laenge();
                                                                 //_vektor<_typgeometrie> h=*this;
                                                                 if(n>0){
                                                                  n=(a0 * a1)/n;
                                                                  L->schreiben("nnnnnnnnnnn=",n);
                                                                  beta=((acos(n)*180)/_pi);
                                                                 };

                                                                 
                                                                 
                                                                 L->schreiben("geoupdate:beta=",beta);
                                                                 if(beta>90) alpha=(180-alpha)+180;
                                                                 L->schreiben("geoupdate:alpha=",alpha);
                                                                }else{
                                                                 L->schreiben("ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ");
                                                                 alpha=0;
                                                                };

                                                                 
                                                                                                 
                                                                 
                                                                 alpha+=90;*/
                                                                 
                                                                 alpha=p->berechnenalpha(vektor)+90;
                                                                 V3.rotieren(p->normale(),p->ebene(0),alpha,normale);
                                                                 normale.normalisieren();
                                                                };
                                                                //visualisieren();
};

_vektor3<_tg> _verbindergeometrisch::middleanglevector(){
                                                                _vektor3<_tg> v;
                                                                _intersektion*is;
                                                                _intersektion*io;
                                                                _polygon*p;
                                                                _vektoranalysis3<_tg> V3;
                                                                _tg beta,delta;
                                                                //----------
                                                                if(geoconnector[0]==0){
                                                                 //fehler("void _verbindergeometrisch::aktualisieren()","geoconnector[0] == 0.");
                                                                 return(v);
                                                                };
                                                                if(geoconnector[1]==0){
                                                                 //fehler("void _verbindergeometrisch::aktualisieren()","geoconnector[1] == 0.");
                                                                 return(v);
                                                                };
                                                                p=ringsection->ringpartition->poly;
                                                                is=ringsection->intersektion;
                                                                if(geoconnector[0]==this){
                                                                 return(p->ebene(0));
                                                                }else{
                                                                 io=geoconnector[1]->ringsection->intersektion;
                                                                 beta=p->berechnenalpha(io->ort()-is->ort());
                                                                 if(beta<alpha) beta+=360;
                                                                 delta=beta-alpha;
                                                                 V3.rotieren(p->normale(),p->ebene(0),alpha+delta*0.5,v);
                                                                 v.normalisieren();
                                                                 return(v);
                                                                };
};

_verbindergeometrisch*_verbindergeometrisch::getgeoconnector(int i){
                                                                return(geoconnector[i]);
};

void _verbindergeometrisch::visualisieren(){
};

void _verbindergeometrisch::unvisualisieren(){
};
//******************************************************************************************************************************************************************************************************
//                                                              V E R B I N D E R G E O M E T R I S C H I T E R A T O R 
//******************************************************************************************************************************************************************************************************

_verbindergeometrischiterator::_verbindergeometrischiterator(_listebasis<_verbindergeometrischiterator >*l,_verbindergeometrischiterator*g):_listenknotenbasissortiert<_verbindergeometrischiterator,_tg>(l,0){//erstes(G->ism->firstgeoconnectoriterator){
                                                                pgeoconnector[0]=g->pgeoconnector[0];
                                                                pgeoconnector[1]=g->pgeoconnector[1];
                                                                alpha=g->alpha;
                                                                issave=g->issave;
                                                                singular[0]=g->singular[0];
                                                                singular[1]=g->singular[1];
                                                                pdbcross=0;
};

_verbindergeometrischiterator::_verbindergeometrischiterator(_listebasis<_verbindergeometrischiterator >*l,_verbindergeometrisch*g):_listenknotenbasissortiert<_verbindergeometrischiterator,_tg>(l,0){//erstes(G->ism->firstgeoconnectoriterator){
                                                                pgeoconnector[0]=g;
                                                                pgeoconnector[1]=g;
                                                                init(0,0);
};

_verbindergeometrischiterator::_verbindergeometrischiterator(_listebasis<_verbindergeometrischiterator >*l,_tg a,char is,_verbindergeometrisch*g0,_verbindergeometrisch*g1):_listenknotenbasissortiert<_verbindergeometrischiterator,_tg>(l,a){//:erstes(G->ism->firstgeoconnectoriterator){
                                                                pgeoconnector[0]=g0;
                                                                pgeoconnector[1]=g1;
                                                                init(a,is);
};

_verbindergeometrischiterator::~_verbindergeometrischiterator(){
                                                                if(pdbcross) delete pdbcross;
                                                                pdbcross=0;
                                                                listline.loeschen();
};

_verbindergeometrisch*_verbindergeometrischiterator::geoconnector(const unsigned int i){
                                                                if(i==0) return(pgeoconnector[0]); else return(pgeoconnector[1]);
};

void _verbindergeometrischiterator::init(_tg a,char s){
                                                                pdbcross=0;
                                                                alpha=a;
                                                                issave=s;
                                                                if(pgeoconnector[0]==pgeoconnector[1]){
                                                                 singular[1]=1;
                                                                 singular[0]=1;
                                                                }else{
                                                                 singular[1]=0;
                                                                 singular[0]=0;
                                                                };
};

_vektor3<_tg> _verbindergeometrischiterator::mitte()const{
                                                                _vektor3<_tg> m;
                                                                _polygon*poly;
                                                               // _vektor<_tg> r;
                                                                //------------
                                                                poly=pgeoconnector[0]->ringsection->ringpartition->polygon();
                                                                m=(pgeoconnector[0]->ringsection->intersektion->ort()+ pgeoconnector[1]->ringsection->intersektion->ort())*0.5;
                                                                return(m);
};

char _verbindergeometrischiterator::spread(int i){
                                                                char step;
                                                                //--------
                                                                step=1;
                                                                if(i==0){//naechstes-richtung
                                                                 if(this!=naechstes()){
                                                                  if(pgeoconnector[0]->geoconnector[0]==naechstes()->pgeoconnector[1]){
                                                                   step=0;
                                                                  };
                                                                 }else{
                                                                  if(pgeoconnector[0]->getgeoconnector(0)==pgeoconnector[1]) step=0;
                                                                 };
                                                                 if(step){
                                                                  pgeoconnector[0]=pgeoconnector[0]->geoconnector[0];
                                                                  singular[0]=0;
                                                                  singular[1]=0;
                                                                  return(1);
                                                                 };
                                                                }else{//vorheriges-richtung
                                                                 if(this!=vorheriges()){
                                                                  if(pgeoconnector[1]->geoconnector[1]==vorheriges()->pgeoconnector[0]){
                                                                   step=0;
                                                                  };
                                                                 }else{
                                                                  if(pgeoconnector[1]->getgeoconnector(1)==pgeoconnector[0]) step=0;
                                                                 };
                                                                 if(step){
                                                                  pgeoconnector[1]=pgeoconnector[1]->geoconnector[1];
                                                                  singular[0]=0;
                                                                  singular[1]=0;
                                                                  return(1);
                                                                 };
                                                                };
                                                                return(0);
};

char _verbindergeometrischiterator::contract(int i){
                                                                if(pgeoconnector[0]!=pgeoconnector[1]){
                                                                 if(i==0){//naechstes-richtung
                                                                  pgeoconnector[0]=pgeoconnector[0]->getgeoconnector(1);
                                                                  if(pgeoconnector[0]==pgeoconnector[1]){
                                                                   singular[0]=0;
                                                                   singular[1]=1;
                                                                  };
                                                                  return(1);
                                                                 }else{//vorheriges-richtung
                                                                  pgeoconnector[1]=pgeoconnector[1]->getgeoconnector(0);
                                                                  if(pgeoconnector[0]==pgeoconnector[1]){
                                                                   singular[0]=1;
                                                                   singular[1]=0;
                                                                  };
                                                                  return(1);
                                                                 };
                                                                };
                                                                return(0);
};

void _verbindergeometrischiterator::markierung(int f){
                                                                pflag=f;
};                                                                

int _verbindergeometrischiterator::markierung()const{
                                                                return(pflag);
};                                                                

void _verbindergeometrischiterator::visualisieren(_vektor4<_to> col){
                                                                _intersektion*i0;
                                                                _intersektion*i1;
                                                               // _welt*W=pgeoconnector[0]->ringsection->ringpartition->polygon()->netz()->welt();
                                                                
                                                                //-----------------
                                                                if(DW){
                                                                listline.loeschen();
                                                                if(pdbcross) delete pdbcross;
                                                                pdbcross=0;
                                                                i0=pgeoconnector[0]->ringsection->intersektion;
                                                                i1=pgeoconnector[1]->ringsection->intersektion;
                                                                if(i0!=i1){
                                                                 listline.einhaengen(
                                                                  new _weltdebuglinie(DW,i0->ort(),i1->ort(),col)
                                                                 );
                                                                }else{
                                                                 pdbcross=new _weltdebugkreuz(DW,i0->ort(),0.05,col);
                                                                };
                                                                };
};
//******************************************************************************************************************************************************************************************************
//                                                              R P I N T E R S E K T I O N 
//******************************************************************************************************************************************************************************************************
_rpintersektion::_rpintersektion(_listebasis<_rpintersektion >*l,_ringpartition*rp,_ringsektion*n,_ringsektion*p,_tg a):_listenknotenbasissortiert<_rpintersektion,_tg >(l,a){
                                                                ringpartition=rp;
                                                                ringsection[0]=n;
                                                                ringsection[1]=p;
                                                                alpha=a;
};
