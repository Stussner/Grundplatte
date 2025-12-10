//******************************************************************************************************************************************************************************************************
//  Projekt      : grundplatte
//  Bibliothek   : _grundplatte.lib
//  Modul        : _weltpartition.cpp
//  Datum        : 09.01.2006
//  Beschreibung : 
//******************************************************************************************************************************************************************************************************

#include <_weltpartition.hpp>
#include <_weltpolygon.hpp>

#include <_grafikopengl.hpp>//nur temporär debug !!!!!!!!!
//******************************************************************************************************************************************************************************************************
//                                                              P A R T I T I O N   : :   Z O N E 
//******************************************************************************************************************************************************************************************************
namespace _partition{
 _zone::_zone(_welt*w):_listenknotenbasis<_zone >(w){
                                                                pflag=0;
                                                                pworld=w;
                                                                pbilderprosek=16;
                                                                pzeitfaktor=1;
                                                                poldtime=0;
                                                                pambientlicht.setzen(0,0,0);
                                                                //***************************** DEBUG ********************************
                                                                L->schreiben("Zone wurde konstruiert.");
                                                                dbscreen=0;
                                                                dbcam=0;
                                                                //dbmo=0;
                                                                //dbgra=0;
                                                                //********************************************************************
 };
 
 _zone::~_zone(){
                                                                ptreelines.loeschen();        
                                                                loeschendebugschirm();
                                                                pdbedges.loeschen();
 };
 
 _welt*_zone::welt(){
                                                                return(pworld);
 }; 
 void _zone::ambientlicht(const _vektor3<_to>&v){
                                                                pambientlicht=v;
 };
 _vektor3<_to>&_zone::ambientlicht(){
                                                                return(pambientlicht);
 };
 void _zone::animieren(){
                                                                _partikelquelle*pit; 
                                                                if(anfang(pit))do{
                                                                 pit->animieren();
                                                                }while(naechstes(pit));
 };
 void _zone::erzeugendebugschirm(){
                                                                _vektor3<_tg> o0;
                                                                _vektor3<_tg> o1;
                                                                _vektor4<_to> col;
                                                                //---------------------
                                                                loeschendebugschirm();
                                                                o0.setzen(-0.53,0.07,1);
                                                                o1.setzen(+0.53,0.41,1);
                                                                col.setzen(1,1,1,0.5);
                                                                dbscreen=new _weltdebugschirm(pworld,o0,o1,80,15,col);
                                                                col.setzen(0.99f,0.6f,0.65f,1);
                                                                if(dbscreen) dbscreen->schreiben("ZONEN - ALGORITHMIK (durchschreiten mit ENTER, ueberspringen mit LEERTASTE, am Ende ESC)",col);
                                                                pc.setzen((_to)0.7f,(_to)1,(_to)0.65f,(_to)0.9f);
                                                                pc2.setzen((_to)0.99f,(_to)0.65f,(_to)0.7f,(_to)0.9f);
                                                                dbcam=new _kamera<_tg>(pworld);
                                                                dbcam->setzen(15,5,-15);
                                                                dbcam->rot(-20);
                                                                dbcam->yaw(-20);
                                                                dbcam->aktualisieren();
                                                                L->l("debugschirm wurde erzeugt");
                                                                //dbmo=new _win::_maus<_tg>(300,300);
                                                                //dbmo->relativ(true);
                                                                //dbgra=new _win::_grafikopengl<char,_tg,_to>();
                                                                
 };
 void _zone::loeschendebugschirm(){
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
 
 void _zone::visualizetree(){
                                                                ptreelines.loeschen();
                                                                visualizetree(root());
 };
 
 void _zone::visualizetree(_ebene*p){
                                                                _vektor4<_to> coln;
                                                                _vektor4<_to> colp;
                                                                //----------------
                                                                colp.setzen(1,0.5,0,0.5);
                                                                coln.setzen(0,0.5,1,0.5);
                                                                if(p){
                                                                  if(p->naechstes()){
                                                                  ptreelines.einhaengen(new _weltdebugpfeil(pworld,p->polygon()->mitte(),p->naechstes()->polygon()->mitte(),0.03,0.03,coln));
                                                                  visualizetree(p->naechstes());
                                                                 };
                                                                 if(p->vorheriges()){
                                                                  ptreelines.einhaengen(new _weltdebugpfeil(pworld,p->polygon()->mitte(),p->vorheriges()->polygon()->mitte(),0.03,0.03,colp));
                                                                  visualizetree(p->vorheriges());
                                                                 };
                                                                };
 };
 
 void _zone::visualizeedgescene(_liste<_kante >*el){
                                                                _listenknoten<_kante >*it;
                                                                _kante*kante;
                                                                _kantenlimitator*l[2];
                                                                _vektor4<_to> col;
                                                                _vektor3<_tg> x;
                                                                _vektor3<_tg> y;
                                                                //--------------
                                                                pdbedges.loeschen();
                                                                col.setzen(0,1,0,0);
                                                                if(el->anfang(it))do{
                                                                 kante=it->objekt();
                                                                 l[0]=kante->limitator(true);
                                                                 l[1]=kante->limitator(false);
                                                                 if((l[0])&&(l[1])){
                                                                  x=l[0]->ort();
                                                                  y=l[1]->ort();
                                                                  pdbedges.einhaengen(new _weltdebuglinie(pworld,x,y,col));
                                                                 }else{
                                                                  if(l[0]){
                                                                   x=l[0]->ort();
                                                                   y=l[0]->locusvector();
                                                                   pdbedges.einhaengen(new _weltdebuglinie(pworld,x,y,col));
                                                                  };
                                                                  if(l[1]){
                                                                   x=l[1]->ort();
                                                                   y=l[1]->locusvector();
                                                                   pdbedges.einhaengen(new _weltdebuglinie(pworld,x,y,col));
                                                                  };
                                                                 };
                                                                }while(el->naechstes(it));
 }; 
 
 void _zone::visualisieren(_liste<_partition::_polygon >*l,_vektor4<_to> col){
                                                                _listenknoten<_partition::_polygon >*it;
                                                                //---------------------
                                                                if(l->anfang(it))do{
                                                                 it->objekt()->visualisieren(this,col);
                                                                }while(l->naechstes(it));
                                                                debuganimation();
                                                                if(l->anfang(it))do{
                                                                 it->objekt()->unvisualisieren();
                                                                }while(l->naechstes(it));
 };
 
 void _zone::visualisieren(_partition::_polygon*f,_vektor4<_to> colf,_partition::_polygon*b,_vektor4<_to> colb){
                                                                //_listenknoten<_partition::_polygon >*it;
                                                                //---------------------
                                                                f->visualisieren(this,colf);
                                                                b->visualisieren(this,colb);
                                                                //debuganimation();
                                                                f->unvisualisieren();
                                                                b->unvisualisieren();
 };
 /*
 
 
 void _zone::debuganimation(){
                                                                _win::_tastatur*kb;
                                                                //---------------------
                                                                kb=new _win::_tastatur();
                                                                if(kb->leertaste()==false){
                                                                 while((kb->enter()==false)&&(kb->leertaste()==false)){
                                                                  dbgra->loeschenseite();
                                                                  dbcam->bewegen(kb,dbmo,1);
                                                                  W->transformieren(dbgra,dbcam);
                                                                  W->zeichnendebug(dbgra); 
                                                                  dbgra->umschaltenseite();
                                                                  S->animieren();
                                                                 };
                                                                 while(kb->enter());
                                                                }else{
                                                                 dbgra->loeschenseite();
                                                                 dbcam->bewegen(kb,dbmo,1);
                                                                 W->transformieren(dbgra,dbcam);
                                                                 W->zeichnendebug(dbgra); 
                                                                 dbgra->umschaltenseite();
                                                                 S->animieren();
                                                                };
                                                                delete kb;
 };
 
*/


 void _zone::debuganimation(){
                                                                _tastatur*kb;
                                                                //_win::_zeit timer;
                                                                
                                                                //---------------------
                                                                if((dbcam)&&(dbscreen)&&(pworld->debugtastatur())&&(pworld->debugmaus())&&(pworld->debuggrafik())&&(pworld->debugsystem())){
                                                                 kb=pworld->debugtastatur();
																_maus<_tg>*maus=pworld->debugmaus();
                                                                  if(maus->relativ()==false) maus->relativ(true);                                                                 
                                                          
                                                                 while((kb->enter()==false)&&(kb->leertaste()==false)){
                                                                 
                                                                  pworld->debuggrafik()->allebufferloeschen();
                                                                  dbcam->bewegen(pworld->debugtastatur(),pworld->debugmaus(),1);

																_matrix44<float> mw;
																_matrix44<float> mm;
																_matrix44<float> mp;
																mw.setzenidentitaet();
																mm.setzenidentitaet();
																mp.setzenidentitaet();
																dbcam->ladenmatrix<float>(&mm,&mp);
																pworld->debuggrafik()->matrixwelt(&mw); 
																pworld->debuggrafik()->matrixprojektion(&mp);
																pworld->debuggrafik()->matrixmodell(&mm);
                                
                                                                  pworld->zeichnendebug(pworld->debuggrafik()); 
                                                                  pworld->debuggrafik()->anzeigebufferumschalten(true);
                                                                  pworld->debugsystem()->animieren();
                                                                 };
                                                                 while(kb->enter());
                                                                 
                                                                };
 };
 
  
 _weltdebugschirm* _zone::debugschirm(){
                                                                return(dbscreen);
 };
  
 void _zone::pruefenumgebungszone(){
                                                                //eine andere zone ist dann eine surroundingzone, wenn die Anzahl der Schnittpunkte
                                                                //in positiver Richtung eine ungerade Anzahl ist und wenn der niedrigste Schnittpunkt
                                                                //dieser ungeraden Kollisionen eine Fläche identifiziert, die einen dem 
                                                                //kollisionsvektor entgegengerichteten normalenvektor aufweist.
                                                                _zone*zit;
                                                                _zoneintersektion*ziz;
                                                                _listenknoten< ::_polygon >*ps;
                                                                _listenknoten< ::_polygon >*pe;
                                                                _listenknoten< ::_polygon >*lnpit;
                                                                ::_polygon*pit;
                                                                _vektor3<_tg> v;
                                                                _vektor3<_tg> o;
                                                                _vektor3<_tg> iv;
                                                                _vektor3<_tg> e;
                                                                _vektor3<_tg> s;
                                                                _vektor3<_tg> h;
                                                                _tg D,c;
                                                                _vektoranalysis3<_tg> V3;
                                                                _listenknoten< ::_vertex>*lnv;
                                                                ::_vertex*v0;
                                                                ::_vertex*v1;
                                                                _vektor2<_tg> eva;
                                                                _vektor2<_tg> evb;
                                                                _vektor2<_tg> eve;
                                                                _tg eb;
                                                                _vektoranalysis2<_tg> V2;
                                                                unsigned int c0;
                                                                unsigned int c1;
                                                                bool aussen;
                                                                unsigned int cz;
                                                                //-----------------------
                                                                if(pworld->anfang(zit))do{
                                                                 if(zit!=this){
                                                                  if( (anfang(ps)) && (zit->anfang(pe)) ){
                                                                   o=ps->objekt()->mitte();
                                                                   v=pe->objekt()->mitte()-o;
                                                                   v.normalisieren();
                                                                   //v ist kollisionsvektor
                                                                   //und muss mit allen poly von zit kollidieren
                                                                   if(zit->anfang(lnpit))do{
                                                                    pit=lnpit->objekt();
                                                                    iv=v*-1;
                                                                    D=V3.determinieren(pit->ebene(0),pit->ebene(1),iv);
                                                                    if(D){
                                                                     e=o-pit->mitte();
                                                                     c=V3.determinieren(pit->ebene(0),pit->ebene(1),e)/D;
                                                                     if(c>0){
                                                                      //in - poly pit bestimmung im 2d
                                                                      pit->berechnengroessterindex();
                                                                      aussen=false;
                                                                      iterierenliste(pit,lnv,
                                                                       v0=lnv->objekt();
                                                                       v1=lnv->naechstes()->objekt();
                                                                       //v0=pit->vertex();
                                                                       //if(v0)do{
                                                                       // v1=v0->naechstes(pit);
                                                                       c0=pit->groessterindex(0);
                                                                       c1=pit->groessterindex(1);
                                                                       eva.setzen(v1->ort()[c0]-v0->ort()[c0],v1->ort()[c1]-v0->ort()[c1]);
                                                                       evb.setzen(pit->mitte()[c0]-v0->ort()[c0],pit->mitte()[c1]-v0->ort()[c1]);
                                                                       //schnittpunkt bestimmen
                                                                       s=o+(v*c);
                                                                       D=V2.determinieren(eva,evb);
                                                                       if(D!=0){
                                                                        eve.setzen(-s[c0],-s[c1]);
                                                                        eb=V2.determinieren(eva,eve)/D;
                                                                        if(eb<-nahenull){
                                                                         aussen=true;
                                                                        };
                                                                       }else{
                                                                        //extremer fehler : polygon pit ist kolinear (invariant)
                                                                       };
                                                                      );
                                                                      // v0=v1;
                                                                      //}while(v0!=pit->vertex());
                                                                      
                                                                      
                                                                      if(aussen==false){
                                                                       //schnittpunkt liegt vor bei s durch pit
                                                                       //kompensation vornehmen !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                                                                       //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                                                                       new _partition::_zoneintersektion(this,pit,s,c);
                                                                      };
                                                                     };
                                                                    }else{
                                                                     //parallelität ignorieren
                                                                    };
                                                                   }while(zit->naechstes(lnpit));
                                                                   //schauen, ob die schnittpunkt konfiguration eine surrounding zone ergibt
                                                                   cz=_listebasis<_zoneintersektion >::anzahl();
                                                                   if(cz>0){
                                                                    if(cz%2==1){
                                                                     _listebasis<_zoneintersektion >::anfang(ziz);
                                                                     h=ziz->ppolygon->normale()+v;
                                                                     if(h.laenge()<sqrt(2.0f)){
                                                                      //zit ist surroundingzone von this
                                                                      //alle polygone von this in zit vereinen
                                                                      //alle polygone von this löschen
                                                                      if(anfang(lnpit))do{
                                                                       pit=lnpit->objekt();
                                                                       zit->einhaengen(pit);
                                                                      }while(naechstes(lnpit));
                                                                      _liste< ::_polygon >::aushaengen();
                                                                     };
                                                                    };
                                                                   };
                                                                   //evtl. vorhandene schnittpunkte löschen
                                                                   _listebasis<_zoneintersektion >::loeschen();
                                                                  };
                                                                 };
                                                                }while(pworld->naechstes(zit));
 };
  
 void _zone::erzeugensektor(){
                                                                _sektor*sit;
                                                                
                                                                if(pworld->debuggenbsp()||pworld->debuggensektor()) erzeugendebugschirm();
                                                                //************ DEBUG ***********
                                                                if(pworld->debuggenbsp()) {
                                                                 visualizetree();
                                                                 debuganimation();
                                                                 if(dbscreen) dbscreen->schreiben("Sie sehen die Baumstruktur des BSP",pc);
                                                                };
                                                                if(dbscreen) dbscreen->schreiben("Erzeugung konvexer Sektoren.",pc);
                                                                debuganimation();
                                                                //******************************
                                                                anzahlsektor=0;
                                                                debugsector=13;
                                                                if(root()) erzeugensektor(root()); 
                                                                //************ DEBUG ***********
                                                                loeschendebugschirm();
                                                                if(anfang(sit))do{
                                                                 sit->unvisualisieren();
                                                                }while(naechstes(sit));
                                                                //******************************
 };
 
 void _zone::erzeugensektor(_ebene*pit){
                                                                if(pit->naechstes()) erzeugensektor(pit->naechstes()); else erzeugensektor(pit,false);
                                                                if(pit->vorheriges()) erzeugensektor(pit->vorheriges());// else erzeugensektor(pit,true);// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                                                                //!!!!!!!!!! test muss verifizieren !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 };
 
 void _zone::erzeugensektor(_ebene*pb,bool rueckseitig){
                                                                _ebene*pit;
                                                                _liste<_ebene > pl;
                                                                _listenknoten<_ebene >*lnpit;
                                                                //_listenknoten<_ebene >*lnpin;
                                                                _sektor*s;
                                                                //*********** DEBUG ***********
                                                                _liste<_weltdebugpfeil > dbseq;
                                                                //*****************************
                                                                //------------------------
                                                                s=new _sektor(this);
                                                                anzahlsektor++;
                                                                if(rueckseitig==false) pb->sektorfront(s);
                                                                L->schreiben("Sektor wurde konstruiert");
                                                                //wurzel - blatt - sequenz anlegen (pl)
                                                                pit=pb;
                                                                if(pit)do{
                                                                 pl.einhaengen(pit);
                                                                 pit=pit->parent();
                                                                }while(pit);
                                                                pl.invertieren();
                                                                //***********DEBUG*****************
                                                                //_vektor4<_to> col;
                                                                //if(pl.anfang(lnpit))do{
                                                                // lnpin=lnpit->naechstes();
                                                                // if(lnpin!=pl.erstes()){
                                                                //  if(lnpin->objekt()==lnpit->objekt()->vorheriges()){
                                                                //   col.setzen(1,1,0);
                                                                //  }else{
                                                                //   col.setzen(0,1,1);
                                                                //  };
                                                                //  dbseq.einhaengen(new _weltdebugpfeil(W,lnpit->objekt()->polygon()->mitte(),lnpit->naechstes()->objekt()->polygon()->mitte(),0.2,0.1,col));
                                                                // };
                                                                //}while(pl.naechstes(lnpit));
                                                                //if(pl.anfang(lnpit))do{
                                                                // lnpit->objekt()->polygon()->markierung(1);
                                                                //}while(pl.naechstes(lnpit));
                                                                //*********************************
                                                                //Wurzel - Blatt - Iteration (pit init) und schnitt mit qit aufrufen
                                                                if(pl.anfang(lnpit))do{
                                                                 lnpit->objekt()->polygon()->markierung(0);
                                                                }while(pl.naechstes(lnpit));
                                                                if(pl.anfang(lnpit))do{
                                                                 createsectorpolygon(s,lnpit,&pl,rueckseitig);
                                                                }while(pl.naechstes(lnpit));
                                                                if(pl.anfang(lnpit))do{
                                                                 lnpit->objekt()->polygon()->markierung(0);
                                                                }while(pl.naechstes(lnpit));
                                                                //-**********DEBUG*****************
                                                                //if(pl.anfang(lnpit))do{
                                                                // lnpit->objekt()->polygon()->berechnengroessterindex();
                                                                //}while(pl.naechstes(lnpit));
                                                                //*********************************
                                                                s->aktualisieren();
                                                                //***********DEBUG*****************
                                                                s->visualisieren();
                                                                if(dbscreen) dbscreen->schreiben("Sie sehen einen Sektor.",pc);
                                                                debuganimation();
                                                                s->unvisualisieren();
                                                                //dbseq.loeschen();
                                                                //*********************************
                                                                //wenn rückseitiger sektor vorliegt, dann 
                                                                //muss geprüft werden, ob dieser gültig ist
                                                                if(rueckseitig){
                                                                 if(validsector(s,&pl)==false){
                                                                  delete s;
                                                                  s=0;
                                                                 }else{
                                                                  s->rueckgeschlossen();
                                                                  pb->sektorrueck(s);
                                                                 };
                                                                };
                                                                //rückseitig abgeschlossenen sektor anlegen
                                                             /*   s=new _sektor(this);
                                                                pb->sektorrueck(0);
                                                                if(pl.anfang(lnpit))do{
                                                                 lnpit->objekt()->polygon()->markierung(0);
                                                                }while(pl.naechstes(lnpit));
                                                                if(pl.anfang(lnpit))do{
                                                                 createsectorpolygon(s,lnpit,&pl,true);
                                                                }while(pl.naechstes(lnpit));
                                                                if(pl.anfang(lnpit))do{
                                                                 lnpit->objekt()->polygon()->markierung(0);
                                                                }while(pl.naechstes(lnpit));
                                                                if(validsector(s,&pl)==false){
                                                                 delete s;
                                                                 s=0;
                                                                }else{
                                                                 s->aktualisieren();
                                                                 pb->sektorrueck(s);
                                                                };*/
 };
 
 bool _zone::validsector(_sektor*s,_liste<_partition::_ebene >*pl){
                                                                //achtung : funktion gilt nur für rückseitig abgeschlossene
                                                                //sektoren
                                                                bool r;
                                                                _partition::_polygon*pit;
                                                                _listenknoten<_ebene >*plit;
                                                                //-----------------
                                                                r=true;
                                                                if(s->anzahlpolygon()<4) r=false; else{
                                                                 if(s->anfang(pit))do{
                                                                  if(pit->portal()==false){
                                                                   if(pl->anfang(plit))do{
                                                                    if(pit->polygon()==plit->objekt()->polygon()){
                                                                     //prüfen ob dieses poly pit ein vorheriges-eingeordnetes ebene objekt ist
                                                                     if(plit==pl->erstes()->vorheriges()){//pit bezeichnet ist blattfläche
                                                                      r=false;
                                                                     }else{
                                                                      if(plit->naechstes()->objekt()==plit->objekt()->vorheriges()) r=false;
                                                                     };
                                                                    };
                                                                   }while((pl->naechstes(plit))&&(r==true));
                                                                  };
                                                                 }while((s->naechstes(pit))&&(r==true));
                                                                };
                                                                return(r);
 };
 
 void _zone::createsectorpolygon(_sektor*sektor,_listenknoten<_ebene >*lnpit,_liste<_ebene >*pl,bool rueckseitig){
                                                                //kernalgorithmik der Weltenpartitionierung, steuerfunktion zur polygonbestimmung
                                                                //führt schnittgeradenbestimmung aus mit allen poly in der liste pl (ausser lnpit)
                                                                //entsteht eine neue schnittgerade (ok=true) wird sie in die szene el eingefuegt
                                                                _listenknoten<_ebene >*lnqit;
                                                                _ebene*pit;
                                                                _ebene*qit;
                                                                _liste<_kante > el;
                                                                ::_polygon*p;
                                                                ::_polygon*q;
                                                                _liste< ::_polygon > komplanares;
                                                                _polygon*spoly;
                                                                _vektor3<_tg> o;
                                                                _vektor3<_tg> v;
                                                                _vektor3<_tg> n;
                                                                _vektor3<_tg> e;
                                                                _vektor3<_tg> h;
                                                                _vektor3<_tg> pp0;
                                                                _vektor3<_tg> pp1;
                                                                _vektor3<_tg> pp;
                                                                _vektoranalysis3<_tg> V3;
                                                                _tg D,d,D0,D1;
                                                                _tg gamma;
                                                                _vektor3<_tg> c;
                                                                bool schnitt;
                                                                bool areaisclosed;
                                                                bool areaisbad;
                                                                bool stop;
                                                                bool polygongesperrt;
                                                                _liste<_partition::_polygon > subtractionresult;
                                                                _liste<_partition::_polygon > divisionresult;
                                                                //*******************DEBUG********************
                                                                _zeichenkette<char> sh;
                                                                //********************************************
                                                                //****************************************** DEBUG ********************************
                                                                sh="----------------------- START createsectorpolygon ------------------";
                                                                //L->schreiben(sh);
                                                                if(dbscreen) dbscreen->schreiben(sh,pc2);
                                                                //*********************************************************************************
                                                                polygongesperrt=false;
                                                                areaisclosed=false;
                                                                areaisbad=false;
                                                                pit=lnpit->objekt();
                                                                p=pit->polygon();
                                                                stop=false;
                                                                komplanares.aushaengen();
                                                                if(pl->anfang(lnqit))do{
                                                                 if(lnqit->objekt()!=pit){
                                                                  qit=lnqit->objekt();
                                                                  q=qit->polygon();
                                                                  //berechnug der schnittgeraden zwischen pit und qit
                                                                  //p mit q schneiden
                                                                  pp0=p->ebene(0);
                                                                  pp1=p->ebene(1);
                                                                  //c=p->ebene(0);
                                                                  //c*=-1;
                                                                  e=p->mitte()-q->mitte();
                                                                  D0=V3.determinieren(q->ebene(0),q->ebene(1),-pp0);
                                                                  D1=V3.determinieren(q->ebene(0),q->ebene(1),-pp1);
                                                                  if(fabs(D0)>fabs(D1)){
                                                                   D=D0;
                                                                   pp=pp0;
                                                                  }else{
                                                                   D=D1;
                                                                   pp=pp1;
                                                                  };
                                                                  if(fabs(D)>(2*nahenull)){
                                                                   d=V3.determinieren(q->ebene(0),q->ebene(1),e)/D; 
                                                                   o=p->mitte()+pp*d;
                                                                   schnitt=true;
                                                                  }else{
                                                                   //parallele ebenen
                                                                   //wenn parallele ebenen vorliegen, dann muss untersucht werden, ob die normale
                                                                   //von poly p vor oder hinter poly q liegt (1.fall).
                                                                   //liegt p hinter q , dann muss die sektor-polygonbestimmung für q abgerbrochen werden,
                                                                   //da ein poly der sektorsequenz dieses vollkommen wegschneidet
                                                                   //wenn eine ebene genau parallel mit mit einer anderen komplanar schneidet , dann....(fall 2)
                                                                   schnitt=false;
                                                                   //*********** DEBUG ***********
                                                                   if(dbscreen) dbscreen->schreiben("Parallelitaet erkannt.",pc);
                                                                    //*****************************
                                                                   h=p->mitte()-q->mitte();
                                                                   h.normalisieren();
                                                                   if(lnqit->naechstes()->objekt()==qit->vorheriges()) h*=-1;// inversionsbedingung
                                                                   d=h*q->normale();
                                                                   if(fabs(d)<=nahenull){
                                                                    //pit komplanar mit qit
                                                                    //L->schreiben("Komplanarschnitt");
                                                                    //ok=false;
                                                                    //stop=true;
                                                                    //el.loeschen();
                                                                    //*********** DEBUG **********
                                                                    _vektor4<_to> pcc;
                                                                    pcc.setzen(1,0,0,0);
                                                                    if(dbscreen) dbscreen->schreiben("parallele Ebenen : komplanare Flaeche erkannt (qit zu pit)",pcc);
                                                                    //****************************
                                                                    komplanares.einhaengen(q);
                                                                    q->markierung(3);
                                                                   }else{
                                                                    if(d<0){
                                                                     //pit ist hinter qit
                                                                     //die qit Ebene schneidet so
                                                                     //die szene el komplett weg
                                                                     //ok=false;
                                                                     stop=true;
                                                                     polygongesperrt=true;
                                                                     //*********** DEBUG ***********
                                                                     _vektor4<_to> pcc;
                                                                     pcc.setzen(1,0,0,0);
                                                                     if(dbscreen) dbscreen->schreiben("parallele Ebenen : el wird geloescht (rueckseitig) zu qit",pcc);
                                                                     //*****************************
                                                                     el.loeschen();
                                                                    }else{
                                                                     //pit ist vor qit
                                                                     //es muss nichts gemacht werden
                                                                    };
                                                                   };
                                                                   //ok=false;
                                                                   //};
                                                                  };
                                                                  if(schnitt){
                                                                   //------------------------ SCHNITT EINHÄNGEN -----------------
                                                                   //schnittgerade ist o+a*v; 
                                                                   //normalenvektor der schnittgeraden bestimmen
                                                                   //durch E=n : 
                                                                   //o0 + alpha*a0 + beta*b0 = n1 + gamma*n0 mit o0=(0,0,0)
                                                                   c=p->normale();
                                                                   c*=-1;
                                                                   D=V3.determinieren(p->ebene(0),p->ebene(1),c);
                                                                   if(D){
                                                                    e=q->normale();
                                                                    gamma=V3.determinieren(p->ebene(0),p->ebene(1),e)/D;
                                                                    n=q->normale()+ (p->normale()*gamma);
                                                                    //projizierten normalen vektor invertieren ?
                                                                    if(lnqit==pl->erstes()->vorheriges()){//ist das letzte (blatt)
                                                                     if(rueckseitig){
                                                                      n*=-1;
                                                                     };
                                                                    }else{
                                                                     if(lnqit->naechstes()->objekt()==qit->vorheriges()){//achtung!!!! war vorher lnpit->pit->naechstes und wahrscheinlich falsch
                                                                      //L->schreiben("Es wurde die kante normale invertiert");
                                                                      n*=-1;
                                                                     };
                                                                    };
                                                                    
                                                                    
                                                                    
                                                                    
                                                                    //gerade liegt komplett vor als o + a*v + b*n und kann eingefügt werden
                                                                    v=p->normale();
                                                                    v%=q->normale();
                                                                    v.normalisieren();
                                                                    createsectoredge(&el,lnpit,qit,o,v,n,areaisclosed,areaisbad,polygongesperrt);
                                                                   }else{
                                                                    //error p ist variant
                                                                   };
                                                                  };
                                                                  //************************DEBUG************************
                                                                  //if(anzahlsektor==debugsector){
                                                                   _listenknoten<_kante >*deit;
                                                                   _vektor4<_to> qcol;
                                                                   _vektor4<_to> pcol;
                                                                   _vektor4<_to> col;
                                                                   pcol=p->farbe();
                                                                   col.setzen(1,0,0,1);
                                                                   p->farbe(col);
                                                                   qcol=q->farbe();
                                                                   col.setzen(0,0,1,1);
                                                                   q->farbe(col);
                                                                   col.setzen(0.5,0,1,1);
                                                                   _vektor4<_to> colp(1,1,0,1);
                                                                   _vektor4<_to> colq(1,0,0,1);
                                                                   lnpit->objekt()->polygon()->visualisieren(colp);
                                                                   lnqit->objekt()->polygon()->visualisieren(colq);
                                                                   if(el.anfang(deit))do{
                                                                    deit->objekt()->visualisieren(col);
                                                                   }while(el.naechstes(deit));
                                                                   debuganimation();
                                                                   lnpit->objekt()->polygon()->unvisualisieren();
                                                                   lnqit->objekt()->polygon()->unvisualisieren();
                                                                   p->farbe(pcol);
                                                                   q->farbe(qcol);
                                                                   if(el.anfang(deit))do{
                                                                    deit->objekt()->unvisualisieren();
                                                                   }while(el.naechstes(deit));
                                                                  //};
                                                                  //*****************************************************
                                                                 };
                                                                }while((pl->naechstes(lnqit))&&(stop==false)&&(polygongesperrt==false));
                                                                if(polygongesperrt==false){
                                                                 if(el.anzahl()<3) {
                                                                  areaisbad=true;
                                                                  areaisclosed=false;
                                                                 };
                                                                 if(areaisclosed) if(dbscreen) dbscreen->schreiben("Flaeche wurde geschlossen.",pc); else if(dbscreen) dbscreen->schreiben("Flaeche wurde nicht geschlossen.",pc);
                                                                 spoly=createsectorpolygon(sektor,pit,&el,areaisclosed,areaisbad);//sektorpolygon anlegen
                                                                  //********** DEBUG **********
                                                                  //_vektor4<_to> coll;
                                                                  //coll.setzen(1,1,0,1);
                                                                  //spoly->visualisieren(this,coll);
                                                                  //debuganimation();
                                                                  //spoly->unvisualisieren();
                                                                  //***************************
                                                                 if(spoly) {
                                                                  subtractionresult.aushaengen();
                                                                  divisionresult.aushaengen();
                                                                  subtractkomplanarpolygon(spoly,&komplanares,&subtractionresult);//komplanaritäten aushaengen
                                                                  //****** DEBUG ******
                                                                  //_vektor4<_to> colo;
                                                                  //colo.setzen(1,0,0);
                                                                  //visualisieren(&subtractionresult,colo);
                                                                  //*******************
                                                                  divideworldpolygon(&subtractionresult,p,&divisionresult);       //zerlegung mit weltpoly p
                                                                  identifyportals(&divisionresult,p);                             //portale identifizieren
                                                                  //****** DEBUG ******
                                                                  //_vektor4<_to> colo;
                                                                  //colo.setzen(0,1,0);
                                                                  //visualisieren(&divisionresult,colo);
                                                                  //*******************
                                                                  clearoverlayedportals(&divisionresult,p);
                                                                  einfuegeninsektor(sektor,&divisionresult);
                                                                  delete spoly;spoly=0;
                                                                  subtractionresult.loeschen();
                                                                  divisionresult.aushaengen();
                                                                 };
                                                                };
                                                                
                                                                
                                                                komplanares.aushaengen();
                                                                el.loeschen();
                                                                //****************************************** DEBUG ********************************
                                                                sh="----------------------- ENDE  createsectorpolygon ------------------";
                                                                //L->schreiben(sh);
                                                                if(dbscreen) dbscreen->schreiben(sh,pc2);
                                                                //*********************************************************************************
 };
 
 _polygon* _zone::createsectorpolygon(_sektor*sektor,_ebene*pit,_liste<_kante >*el,bool areaisclosed,bool areaisbad){
                                                                //_vektor<_tg> v;
                                                                _polygon*partitionpoly;
                                                                _kantenlimitator*lit;
                                                                _kantenlimitator*litstart;
                                                                _kante*eit;
                                                                _listenknoten<_kante >*elit;
                                                                //--------------
                                                                partitionpoly=0;
                                                                if(areaisbad==false){
                                                                 if(areaisclosed==true){
                                                                  //******************* DEBUG **************
                                                                  if(dbscreen) dbscreen->schreiben("SEKTOR POLYGON WIRD KONSTRUIERT",pc);
                                                                  //****************************************
                                                                  //el - iteration
                                                                  if(el->anfang(elit)){
                                                                   partitionpoly=new _partition::_polygon(pit->polygon());
                                                                   partitionpoly->loeschenvertex();
                                                                   lit=elit->objekt()->limitator(true);
                                                                   litstart=lit;
                                                                   if(lit)do{
                                                                    new _partition::_vertex(partitionpoly,lit->ort());
                                                                    lit=lit->anderes();
                                                                    if(lit){
                                                                     eit=lit->kante();
                                                                     if(lit==eit->limitator(true)){
                                                                      lit=eit->limitator(false);
                                                                     }else{
                                                                      lit=eit->limitator(true);
                                                                     };
                                                                    }else{
                                                                     //error : lit anderes ist null im geschlossenen ring
                                                                    };
                                                                    if(lit==0) lit=litstart;
                                                                   }while(lit!=litstart);
                                                                  };
                                                                 };
                                                                };
                                                                partitionpoly->aktualisieren();
                                                                return(partitionpoly);
 };
 
 void _zone::createsectoredge(_liste<_kante >*el,_listenknoten<_ebene >*lnpit,_ebene*qit,_vektor3<_tg>&o,_vektor3<_tg>&v,_vektor3<_tg>&n,bool&areaisclosed,bool&areaisbad,bool&polygongesperrt){
                                                                //kante in eine vorhandene Szene (el) einfügen, dabei
                                                                //halbräumlich schneiden. 
                                                                _kante*ovn;
                                                                //---------------------------------------------------------
                                                                //************************ DEBUG **************************
                                                                _zeichenkette<char> sh;
                                                                //sh="------------ START createsectoredge ---------------";
                                                                //L->schreiben(sh);
                                                                //dbscreen->schreiben(sh,col);
                                                                //*********************************************************
                                                                if(areaisbad==false){
                                                                 n.normalisieren();
                                                                 ovn=new _kante(lnpit->objekt(),qit,o,v,n);
                                                                 if(validtoinsertedge(ovn,el,polygongesperrt)){
                                                                  insertedge(lnpit->objekt()->polygon(),ovn,el);
                                                                  clearinvalidedge(el);
                                                                  checkedgeclosity(el,areaisclosed,areaisbad);
                                                                 }else{
                                                                  delete ovn;
                                                                  ovn=0;
                                                                 };
                                                                };
                                                                //************************ DEBUG **************************
                                                                //sh="------------ ENDE  createsectoredge ---------------";
                                                                //L->schreiben(sh);
                                                                //dbscreen->schreiben(sh,col);
                                                                //*********************************************************
 };
 
 bool _zone::validtoinsertedge(_kante*ovn,_liste<_kante >*el,bool&polygongesperrt){
                                                                _listenknoten<_kante >*eit;
                                                                _kante*tst;
                                                                bool valid;
                                                                _vektor3<_tg> e;
                                                                _tg D;
                                                                bool kolinear;
                                                                bool parallel;
                                                                int statusmin;
                                                                int statusmax;
                                                                _kantenlimitator*l0;
                                                                _kantenlimitator*l1;
                                                                //--------------------------------------
                                                                valid=true;
                                                                if(el->anzahl()>0){
                                                                 //--------------------------------------init
                                                                 //--------------------------------------status bestimmen
                                                                 statusmin=0;
                                                                 statusmax=0;
                                                                 if(el->anfang(eit))do{
                                                                  tst=eit->objekt();
                                                                  l0=tst->limitator(true);
                                                                  l1=tst->limitator(false);
                                                                  if((l0)&&(l1)){
                                                                   //l0 und l1 limitatoren sind gesetzt
                                                                   //status von beiden holen
                                                                   e=l0->ort()-ovn->ort();
                                                                   if(e.laenge()>nahenull){
                                                                    e.normalisieren();
                                                                    D=e*ovn->normale();
                                                                    if(fabs(D)>nahenull) {
                                                                     if(D>0) statusmax=+1; else statusmin=-1;
                                                                    };
                                                                   };
                                                                   e=l1->ort()-ovn->ort();
                                                                   if(e.laenge()>nahenull){
                                                                    e.normalisieren();
                                                                    D=e*ovn->normale();
                                                                    if(fabs(D)>nahenull) {
                                                                     if(D>0) statusmax=+1; else statusmin=-1;
                                                                    };
                                                                   };
                                                                  }else
                                                                  if((l0)&&(l1==0)){
                                                                   //l0 limitator gesetzt
                                                                   //status des limitators holen
                                                                   //richtung der infiniten gerade bestimmen ,
                                                                   //und dafür den status holen
                                                                   e=l0->ort()-ovn->ort();
                                                                   if(e.laenge()>nahenull){
                                                                    e.normalisieren();
                                                                    D=e*ovn->normale();
                                                                    if(fabs(D)>nahenull) {
                                                                     if(D>0) statusmax=+1; else statusmin=-1;
                                                                    };
                                                                   };
                                                                   //richtung ist positiv l(true)
                                                                   //produkt mit der ovn-normalen
                                                                   D=tst->vektor()*ovn->normale();
                                                                   if(fabs(D)>nahenull){
                                                                    if(D>0) statusmax=+1; else statusmin=-1;
                                                                   };
                                                                  }else
                                                                  if((l1)&&(l0==0)){
                                                                   //l1 limitator gesetzt
                                                                   //status des limitators holen
                                                                   //richtung der infiniten gerade bestimmen ,
                                                                   //und dafür den status holen
                                                                   e=l1->ort()-ovn->ort();
                                                                   if(e.laenge()>nahenull){
                                                                    e.normalisieren();
                                                                    D=e*ovn->normale();
                                                                    if(fabs(D)>nahenull) {
                                                                     if(D>0) statusmax=+1; else statusmin=-1;
                                                                    };
                                                                   };
                                                                   //richtung ist negativ l(false)
                                                                   //produkt mit der ovn-normalen
                                                                   D=(tst->vektor()*-1)*ovn->normale();
                                                                   if(fabs(D)>nahenull){
                                                                    if(D>0) statusmax=+1; else statusmin=-1;
                                                                   };
                                                                  }else
                                                                  if((l0==0)&&(l1==0)){
                                                                   //es ist kein limitator gesetzt
                                                                   //gerade als solche untersuchen :
                                                                   //ist sie parallel, status holen 
                                                                   //ist sie schräg , beide statusflags setzen
                                                                   D=tst->vektor()*ovn->normale();
                                                                   if(fabs(D)<=nahenull){
                                                                    //parallel
                                                                   }else{
                                                                    //schräg
                                                                    statusmin=-1;
                                                                    statusmax=+1;
                                                                   };
                                                                  };
                                                                  //jetzt noch mal nachträglich eine generelle
                                                                  //parallelitätsprüfung durchführen
                                                                  D=ovn->normale()*tst->vektor();
                                                                  if(fabs(D)<=nahenull) parallel=true; else parallel=false;
                                                                  //und , wenn parallel, eine generelle
                                                                  //kolinearitätsprüfung durchfürhren
                                                                  if(parallel){
                                                                   e=tst->ort()-ovn->ort();
                                                                   kolinear=false;
                                                                   if(e.laenge()<=nahenull){
                                                                    kolinear=true;
                                                                   }else{
                                                                    e.normalisieren();
                                                                    D=e*ovn->normale();
                                                                    if(fabs(D)<=nahenull) kolinear=true;
                                                                   };
                                                                   if(kolinear){
                                                                    //parallel - kolinear
                                                                    if(dbscreen) dbscreen->schreiben("tst ist parallel, kolinear mit ovn",pc);
                                                                    D=ovn->normale()*tst->normale();
                                                                    if(D>0){
                                                                     valid=false;
                                                                     //statusmax=+1; 
                                                                    }else{
                                                                     //statusmin=-1;
                                                                     polygongesperrt=true;
                                                                     valid=false;
                                                                    };
                                                                   }else{
                                                                    //parallel nicht kolinear
                                                                    if(dbscreen) dbscreen->schreiben("tst ist parallel, nicht kolinear zu ovn",pc);
                                                                    e=tst->ort()-ovn->ort();
                                                                    e.normalisieren();
                                                                    D=e*ovn->normale();
                                                                    if(D>0){
                                                                     //parallel nicht kolinear,tst vor onv
                                                                     if(dbscreen) dbscreen->schreiben("tst ist parallel, nicht kolinear vor ovn",pc);
                                                                     D=tst->normale()*ovn->normale();
                                                                     if(D>0){
                                                                      //statusmax=+1;
                                                                      if(dbscreen) dbscreen->schreiben("tst ist parallel, nicht kolinear vor ovn, normalen gleichgerichtet, ovn wird geloescht",pc);
                                                                      valid=false;
                                                                     }else{
                                                                      if(dbscreen) dbscreen->schreiben("tst ist parallel, nicht kolinear vor ovn, normalen entgegengerichtet",pc);
                                                                      //statusmax=+1;
                                                                      //statusmin=-1;
                                                                     };
                                                                    }else{
                                                                     //parallel nicht kolinear, tst hinter ovn
                                                                     if(dbscreen) dbscreen->schreiben("tst ist parallel, nicht kolinear hinter ovn",pc);
                                                                     D=tst->normale()*ovn->normale();
                                                                     if(D>0){
                                                                      if(dbscreen) dbscreen->schreiben("tst ist parallel, nicht kolinear, hinter ovn, gleiche normalen",pc);
                                                                      eit->loeschmarkierungobjekt(true);
                                                                      //statusmin=-1;
                                                                      //statusmax=+1;
                                                                     }else{
                                                                      //statusmin=-1;
                                                                      polygongesperrt=true;
                                                                      valid=false;
                                                                     };
                                                                    };
                                                                   };
                                                                  
                                                                  };
                                                                 }while(el->naechstes(eit));
                                                                 //--------------------------------------status auswerten
                                                                // if(dbscreen) dbscreen->schreiben("statusmin =",statusmin,pc);
                                                                // if(dbscreen) dbscreen->schreiben("statusmax =",statusmax,pc);
                                                                 if((statusmin==0)&&(statusmax==+1)){
                                                                  valid=false;
                                                                 };
                                                                 if((statusmin==-1)&&(statusmax==0)){
                                                                  polygongesperrt=true;
                                                                 };
                                                                };
                                                                if(polygongesperrt) valid=false;
                                                                if(valid) el->loeschenmarkiert();
                                                                return(valid);
 };
 
 void _zone::insertedge(::_polygon*poly,_kante*&ovn,_liste<_kante >*el){
                                                                //schnittpunkte holen zwischen test und der neuen kante o,v,n
                                                                //untersuchen, ob test limitatoren (edgevertex) besitzt und wenn 
                                                                //ja dann untersuchen, ob diese vor oder hinter der neuen
                                                                //kante-ebene liegen
                                                                _listenknoten<_kante >*eit;
                                                                _kante*test;
                                                                _kantenlimitator*tlimit;
                                                                _kantenlimitator*nlimit;
                                                                //_vektor<unsigned int> mei;
                                                                _vektor3<_tg> e;
                                                                _vektor3<_tg> v0;
                                                                _vektor3<_tg> v1;
                                                                _vektor2<_tg> e2;
                                                                _vektor2<_tg> v02;
                                                                _vektor2<_tg> v12;
                                                                _vektor3<_tg> h;
                                                                _tg alpha;
                                                                _tg beta;
                                                                bool alphadir;
                                                                bool betadir;
                                                                _vektoranalysis2<_tg> V2;
                                                                _tg D;
                                                                //bool kolinear;
                                                                _zeichenkette<char> sh;
                                                                //--------------------
                                                                if(el->anfang(eit))do{
                                                                 test=eit->objekt();
                                                                 poly->berechnengroessterindex();
                                                                 e=test->ort()-ovn->ort();
                                                                 v0=-test->vektor();
                                                                 v1=ovn->vektor();
                                                                 
                                                                 
                                                                 e2.setzen(e[poly->groessterindex(0)],e[poly->groessterindex(1)]);
                                                                 v02.setzen(v0[poly->groessterindex(0)],v0[poly->groessterindex(1)]);
                                                                 v12.setzen(v1[poly->groessterindex(0)],v1[poly->groessterindex(1)]);
                                                                 D=V2.determinieren(v02,v12);
                                                                 if(fabs(D)>nahenull){
                                                                  //------------------------------------------- SCHRÄGLAGE ------------------------------------.
                                                                  //schnittpunkt ist bestimmbar, keine parallelität  
                                                                  alpha=V2.determinieren(e2,v12)/D;//alpha ist test-parameter
                                                                  beta=V2.determinieren(v02,e2)/D;//beta ist o,v,n- parameter
                                                                  //ausrichtung von alpha bestimmen mit test-vektor ovn-normale
                                                                  h=test->vektor();
                                                                  h.normalisieren();
                                                                  h+=ovn->normale();
                                                                  if(h.laenge()>=sqrt(2.0f)) alphadir=true; else alphadir=false;
                                                                  //ausrichtung von beta bestimmen mit ovn-vektor test-normale
                                                                  h=ovn->vektor();
                                                                  h.normalisieren();
                                                                  h+=test->normale();
                                                                  if(h.laenge()>=sqrt(2.0f)) betadir=true; else betadir=false;
                                                                  //prüfen ob limitatoren vorhanden usw... anlegen in test mit alpha
             
                                                                  tlimit=0;
                                                                  nlimit=0;
                                                                  if(test->limitator(alphadir)){
                                                                   if(
                                                                   ((alphadir==true )&&(alpha>=test->limitator(alphadir)->alpha())) ||
                                                                   ((alphadir==false)&&(alpha<=test->limitator(alphadir)->alpha()))   ){
                                                                    test->loeschenlimitator(alphadir); //nicht nötig
                                                                    tlimit=test->erzeugenlimitator(alphadir,alpha);
                                                                    //link=true;
                                                                    //******************* DEBUG ******************
                                                                    //L->schreiben("_zone::einfuegenkante : Löschen und Erzeugen Kantenlimitator an der szenengeraden test.");
                                                                    //********************************************
                                                                   };
                                                                  }else{
                                                                   tlimit=test->erzeugenlimitator(alphadir,alpha);
                                                                   //link=true;
                                                                   //******************* DEBUG ******************
                                                                   //sh="_zone::einfuegenkante : konstruktion kantenlimitator an test.alpha = ";
                                                                   //L->schreiben(sh,alpha);
                                                                   //if(dbscreen) dbscreen->schreiben(sh,alpha,pc);
                                                                   //******************* DEBUG ******************
                                                                  };
                                                                  //prüfen ob limitatoren vorhanden usw... anlegen in ovn mit beta
                                                                  if(tlimit){
                                                                   if(ovn->limitator(betadir)){
                                                                    if(
                                                                    ((betadir==true )&&(beta>=ovn->limitator(betadir)->alpha())) ||
                                                                    ((betadir==false)&&(beta<=ovn->limitator(betadir)->alpha()))   ){
                                                                     ovn->loeschenlimitator(betadir); //nicht nötig
                                                                     nlimit=ovn->erzeugenlimitator(betadir,beta);
                                                                     //link=true;
                                                                     //L->schreiben("_zone::einfuegenkante : Löschen und Erzeugen Kantenlimitator an der neuen geraden ovn.");
                                                                    };
                                                                   }else{
                                                                    nlimit=ovn->erzeugenlimitator(betadir,beta);
                                                                    //link=true;
                                                                    //******************* DEBUG ******************
                                                                    //sh="_zone::einfuegenkante : Konstruktion kantenlimitator an ovn.beta = ";
                                                                    //L->schreiben(sh,beta);
                                                                    //if(dbscreen) dbscreen->schreiben(sh,beta,pc);
                                                                    //L->schreiben("_zone::einfuegenkante : erzeugen edgelimitator an der neuen geraden ovn.beta=",beta);
                                                                    //********************************************
                                                                   };
                                                                  };
                                                                  //verknüpfung vornehmen
                                           //                       if((tlimit)&&(nlimit)){
                                           //                        tlimit->anderes(nlimit);
                                           //                        nlimit->anderes(tlimit);
                                           //                        if(dbscreen) dbscreen->schreiben("VERKNUEPFUNG VORGENOMMEN",pc);
                                           //                       };
                                                                 };
                                                                }while(el->naechstes(eit));
                                                                //******************* DEBUG ******************
                                                                //if(dbscreen) dbscreen->schreiben("el - anzahl = ",(int)el->anzahl(),pc);
                                                                //********************************************
                                                                el->einhaengen(ovn);
 };                                                                
 void _zone::clearinvalidedge(_liste<_kante >*el){
                                                                 //el von ungültigen kanten befreien
                                                                 //das sind solche, die zwei limitatoren haben , die nicht 
                                                                 //auf sich gegenseitig verweisen
                                                                _kantenlimitator*l[2];
                                                                _listenknoten<_kante >*lneit;
                                                                _kante*e;
                                                                _tg a0,a1;
                                                                //----------------
                                                                //el->loeschenmarkiert(); braucht nicht
                                                                if(el->anfang(lneit))do{
                                                                 e=lneit->objekt();
                                                                 l[0]=e->limitator(true);
                                                                 l[1]=e->limitator(false);
                                                                 if((l[0]!=0)&&(l[1]!=0)){
                                                                  a0=l[0]->alpha();
                                                                  a1=l[1]->alpha();
                                                                  if(a0<a1){
                                                                   if((l[0]->direktion()==true)&&(l[1]->direktion()==false)){
                                                                    //alles ok
                                                                   }else{
                                                                    //ungültig
                                                                    lneit->loeschmarkierungobjekt(true);
                                                                   };
                                                                  };
                                                                  if(a0>a1){
                                                                   if((l[0]->direktion()==false)&&(l[1]->direktion()==true)){
                                                                    //alles ok
                                                                   }else{
                                                                    //ungültig
                                                                    lneit->loeschmarkierungobjekt(true);
                                                                   };
                                                                  };
                                                                  if(fabs(a0-a1)<=nahenull ){
                                                                   lneit->loeschmarkierungobjekt(true);
                                                                  };
                                                                 };
                                                                }while(el->naechstes(lneit));
                                                                el->loeschenmarkiert();
 };
 void _zone::checkedgeclosity(_liste<_kante >*el,bool&areaisclosed,bool&areaisbad){
                                                                bool closed;
                                                                bool error;
                                                                unsigned int anzahl;
                                                                unsigned int countmax=100000000;
                                                                //_vektor<_tg> v;
                                                                _kantenlimitator*l0;
                                                                _kantenlimitator*l1;
                                                                _kantenlimitator*lit;
                                                                _kantenlimitator*lito;
                                                                _kantenlimitator*litstart;
                                                                _kante*eit;
                                                                _listenknoten<_kante >*elit;
                                                                //strukturverbund der edgelimitatoren untereinander mit 
                                                                //geometrischer abstandsprüfung einrichten
                                                                error=false;
                                                                if(el->anfang(elit))do{
                                                                 l0=elit->objekt()->limitator(true);
                                                                 if(l0) l0->anderes(0);
                                                                 l1=elit->objekt()->limitator(false);
                                                                 if(l1) l1->anderes(0);
                                                                }while(el->naechstes(elit));
                                                                //----------------------
                                                                if(el->anfang(elit))do{
                                                                 lit=elit->objekt()->limitator(true);
                                                                 if(lit){
                                                                  if(lit->anderes()==0){
                                                                   lito=getotherlimitator(el,elit,lit);
                                                                   if(lito){
                                                                    lit->anderes(lito);
                                                                    lito->anderes(lit);
                                                                   }else error=true; 
                                                                  };
                                                                 };
                                                                 lit=elit->objekt()->limitator(false);
                                                                 if(lit){
                                                                  if(lit->anderes()==0){
                                                                   lito=getotherlimitator(el,elit,lit);
                                                                   if(lito){
                                                                    lit->anderes(lito);
                                                                    lito->anderes(lit);
                                                                   }else error=true; 
                                                                  };
                                                                 };
                                                                }while(el->naechstes(elit));
                                                                if(error==false){
                                                                 //integrität von el prüfen
                                                                 //d.h. an einem beliebeigen limitator starten und einen zeiger
                                                                 //auf diesen ausrichten (start). 
                                                                 closed=false;
                                                                 error=false;
                                                                 anzahl=0;
                                                                 if(areaisbad==false){
                                                                  if(el->anfang(elit)){
                                                                   lit=elit->objekt()->limitator(true);
                                                                   litstart=lit;
                                                                   if(lit){
                                                                    do{
                                                                     //...
                                                                     lit=lit->anderes();
                                                                     
                                                                     if(lit){
                                                                      eit=lit->kante();
                                                                      if((eit->limitator(true)==0)||(eit->limitator(false)==0)){
                                                                       error=true;
                                                                      }else{
                                                                       if(lit==eit->limitator(true)){
                                                                        lit=eit->limitator(false);
                                                                       }else{
                                                                        lit=eit->limitator(true);
                                                                       };
                                                                      };
                                                                     }else{
                                                                      //error : lit anderes ist null im geschlossenen ring
                                                                      error=true;
                                                                      //if(dbscreen) dbscreen->schreiben("checkedgeclosity : anderes == null",pc2);
                                                                     };
                                                                     anzahl++;
                                                                     if(anzahl>countmax) error=true;
                                                                    }while((lit!=litstart)&&(error==false));
                                                                   }else{
                                                                    error=true;
                                                                   };
                                                                   if(error){
                                                                    closed=false;
                                                                   }else{
                                                                    closed=true;
                                                                   };
                                                                  };
                                                                 };
                                                                 //ungültige area ist : eine abgeschlossene area ist entstanden. nach hinzufügen einer neuen 
                                                                 //kante ist keine abgeschlossene area mehr vorhanden. in dem fall darf für das polygon kein 
                                                                 //_partition::_polygon angewendet werden, auch wenn später noch eine abgeschlossene area entsteht.
                                                                 if(closed==true){
                                                                  areaisclosed=true;
                                                                  //if(dbscreen) dbscreen->schreiben("Flaeche wurde geschlossen !",pc);
                                                                 }else{
                                                                  areaisclosed=false;
                                                                  //if(dbscreen) dbscreen->schreiben("Flaeche wurde nicht geschlossen !",pc2);
                                                                 };
                                                                };
 }; 
 
 _partition::_kantenlimitator* _zone::getotherlimitator(_liste<_partition::_kante >*el,_listenknoten<_partition::_kante >*elit,_partition::_kantenlimitator*lit){
                                                                _partition::_kantenlimitator*r;
                                                                _listenknoten<_partition::_kante >*eit;
                                                                _partition::_kante*e;
                                                                _vektor3<_tg> x;
                                                                _vektor3<_tg> v;
                                                                //-----------------------
                                                                r=0;
                                                                x=lit->ort();
                                                                if(el->anfang(eit))do{
                                                                 if(eit!=elit){
                                                                  e=eit->objekt();
                                                                  if(e->limitator(true)){
                                                                   v=e->limitator(true)->ort()-x;
                                                                   if(v.laenge()<=nahenull) r=e->limitator(true);
                                                                  };
                                                                  if(e->limitator(false)){
                                                                   v=e->limitator(false)->ort()-x;
                                                                   if(v.laenge()<=nahenull) r=e->limitator(false);
                                                                  };
                                                                 };
                                                                }while((el->naechstes(eit))&&(r==0));
                                                                return(r);
 };
 
 void _zone::subtractkomplanarpolygon(_partition::_polygon*spoly,_liste< ::_polygon >*komplanares,_liste<_partition::_polygon >*subresult){
                                                                _partition::_polygon*kpoly;
                                                                ::_polygon*kwelt;
                                                                _listenknoten< ::_polygon >*kit;
                                                                _liste<_partition::_polygon > result0;
                                                                _liste<_partition::_polygon >*result1;
                                                                _listenknoten<_partition::_polygon >*rit;
                                                                _liste<_liste<_partition::_polygon > > result1list;
                                                                _listenknoten<_liste<_partition::_polygon > >*lit;
                                                                //------------------------------------------
                                                                //*****DEBUG*****
                                                                //if(dbscreen) dbscreen->schreiben("Es wird ein neues, rohes Sektorpolygon visualisiert (rot), weiter mit Enter",_vektor4<_to>(1,0,0,1));
                                                                //_vektor4<_to> colo;
                                                                //colo.setzen(1,0,0,1);
                                                                //spoly->visualisieren(this,colo);
                                                                //debuganimation();
                                                                //***************
                                                                
                                                                
                                                                
                                                                if(komplanares->anfang(kit)){
                                                                 //komplanare fläche herausiterieren
                                                                 result0.einhaengen(new _partition::_polygon(spoly));       
                                                                 do{
                                                                  kwelt=kit->objekt();
                                                                  if(result0.anfang(rit))do{
                                                                   result1=new _liste<_partition::_polygon >();
                                                                   kpoly=new _partition::_polygon(kwelt);
                                                                   kpoly->aktualisieren();
                                                                   rit->objekt()->teilen(kpoly,result1);
                                                                   //****** DEBUG ******
                                                                   if(dbscreen) dbscreen->schreiben("Komplanarer Schnitt : Es wird ein Divisionsergebnis visualisiert (cyan)",_vektor4<_to>(1,0,0,1));
                                                                   if(dbscreen) dbscreen->schreiben("Komplanarer Schnitt : Das teilende Polygon ist (gruen) markiert",_vektor4<_to>(1,0,0,1));
                                                                   _vektor4<_to> colo;
                                                                   colo.setzen(0,1,0,1);
                                                                   kpoly->visualisieren(this,colo);
                                                                   colo.setzen(0,1,1,1);
                                                                   visualisieren(result1,colo);
                                                                   kpoly->unvisualisieren();
                                                                   //*******************
                                                                   subtract(kpoly,result1);
                                                                   //****** DEBUG ******
                                                                   if(dbscreen) dbscreen->schreiben("Komplanarer Schnitt : Es wird ein Subtraktionsergebnis visualisiert (rot)",_vektor4<_to>(1,0,0,1));
                                                                   if(dbscreen) dbscreen->schreiben("Komplanarer Schnitt : Das teilende Polygon ist (gruen) markiert",_vektor4<_to>(1,0,0,1));
                                                                   colo.setzen(0,1,0,1);
                                                                   kpoly->visualisieren(this,colo);
                                                                   colo.setzen(1,0,0,1);
                                                                   visualisieren(result1,colo);
                                                                   kpoly->unvisualisieren();
                                                                   //*******************
                                                                   delete kpoly;
                                                                   result1list.einhaengen(result1);
                                                                  }while(result0.naechstes(rit));
                                                                  //alle objecte von result0 löschen
                                                                  //alle result1 in result0 überschreiben
                                                                  result0.loeschen();
                                                                  if(result1list.anfang(lit))do{
                                                                   if(lit->objekt()->anfang(rit))do{
                                                                    result0.einhaengen(rit->objekt());
                                                                   }while(lit->objekt()->naechstes(rit));
                                                                  }while(result1list.naechstes(lit));
                                                                  //result1 löschen (nur die liste)
                                                                  result1list.loeschen();
                                                                 }while(komplanares->naechstes(kit));
                                                                 //den result0 in die subresultliste ubertrage
                                                                 subresult->aushaengen();
                                                                 if(result0.anfang(rit))do{
                                                                  subresult->einhaengen(rit->objekt());
                                                                 }while(result0.naechstes(rit));
                                                                 result0.aushaengen();
                                                                }else{
                                                                 subresult->einhaengen(new _partition::_polygon(spoly));
                                                                };
 };
 
 void _zone::divideworldpolygon(_liste<_partition::_polygon >*subresult,::_polygon*p,_liste<_partition::_polygon >*divresult){
                                                                //der funktion werden eine liste von polygonen und
                                                                //ein weltpolygon p übergeben. Alle Polygone der Liste 
                                                                //werden am Weltpolygon p zerteilt. Das Ergebnis landet
                                                                //in der divresult-liste.
                                                                _partition::_polygon*wpoly;
                                                                _listenknoten<_partition::_polygon >*rit;
                                                                _liste<_partition::_polygon >*result1;
                                                                _liste<_liste<_partition::_polygon > > result1list;
                                                                _listenknoten<_liste<_partition::_polygon > >*lit;
                                                                //------------------------------------
                                                                if(subresult->anfang(rit))do{
                                                                 result1=new _liste<_partition::_polygon >();
                                                                 wpoly=new _partition::_polygon(p);
                                                                 rit->objekt()->teilen(wpoly,result1);
                                                                 //****** DEBUG ******
                                                                 //_vektor4<_to> colo;
                                                                 //colo.setzen(0,1,1);
                                                                 //visualisieren(result1,colo);
                                                                 //*******************
                                                                 delete wpoly;
                                                                 result1list.einhaengen(result1);
                                                                }while(subresult->naechstes(rit));
                                                                //alle result1list in divresult überschreiben
                                                                divresult->aushaengen();
                                                                if(result1list.anfang(lit))do{
                                                                 if(lit->objekt()->anfang(rit))do{
                                                                  divresult->einhaengen(rit->objekt());
                                                                 }while(lit->objekt()->naechstes(rit));
                                                                }while(result1list.naechstes(lit));
                                                                //result1listen löschen (aber nur die listenobjekte)
                                                                result1list.loeschen();
 };
 
 void _zone::identifyportals(_liste<_partition::_polygon >*divresult,::_polygon*p){
                                                                //funktion kennzeichnet die divresult-liste.
                                                                //ein polygon ist nur dann ein portal,
                                                                //wenn dessen mittelpunkt sich nicht
                                                                //innerhalb des weltpolygons p befindet
                                                                _listenknoten<_partition::_polygon >*it;
                                                                //---------------------------
                                                                if(divresult->anfang(it))do{
                                                                 p->berechnengroessterindex();
                                                                 if(p->innerhalbpunkt(it->objekt()->mitte())){
                                                                  it->objekt()->portal(false);
                                                                 }else{
                                                                  it->objekt()->portal(true);
                                                                 };
                                                                 //************* DEBUG ********************
                                                                 if(dbscreen) {
                                                                  dbscreen->schreiben("Portalpruefung : gelbes polygon, blauer punkt",_vektor4<_to>(1,1,0,1));
                                                                  if(it->objekt()->portal()==false) dbscreen->schreiben("Portalpruefung : ist kein Portal",_vektor4<_to>(1,1,0,1)); else dbscreen->schreiben("Portalpruefung : ist Portal",_vektor4<_to>(1,1,0,1));
                                                                 };
                                                                 p->visualisieren(_vektor4<_to>(1,1,0,1));
                                                                 _weltdebugkreuz*wk=new _weltdebugkreuz(pworld,it->objekt()->mitte(),1,_vektor4<_to>(0,0,1,1));
                                                                 debuganimation();
                                                                 delete wk;
                                                                 p->unvisualisieren();
                                                                 //****************************************
                                                                }while(divresult->naechstes(it));
 };
 
 void _zone::clearoverlayedportals(_liste<_partition::_polygon >*divresult,::_polygon*p){
                                                                //alle weltpolygone, die vorher als qit-assoziiertes objekt 
                                                                //teil einer komplanaern szene waren , haben den markierung ==3
                                                                //und dürfen keine weiteren portale mehr verursachen
                                                                _listenknoten<_partition::_polygon >*it;
                                                                //------------------------
                                                                if(p->markierung()==3){
                                                                 if(divresult->anfang(it))do{
                                                                  if(it->objekt()->portal()==true) it->loeschmarkierungobjekt(true);
                                                                 }while(divresult->naechstes(it));
                                                                 divresult->loeschenmarkiert();
                                                                };
                                                                
 };
 
 void _zone::subtract(_partition::_polygon*poly,_liste<_partition::_polygon >*polylist){
                                                                //diejenigen poly der liste, deren mittelpunkt in der poly-fläche
                                                                //sind, sind fremd-komplanare bruchstücke und müssen glöscht werden
                                                                _listenknoten<_partition::_polygon >*pit;
                                                                //---------------------
                                                                poly->aktualisieren();
                                                                if(polylist->anfang(pit))do{
                                                                 pit->objekt()->aktualisieren();
                                                                 if(poly->innerhalbpunkt(pit->objekt()->mitte())){
                                                                  pit->loeschmarkierungobjekt(true);
                                                                 };
                                                                }while(polylist->naechstes(pit));
                                                                polylist->loeschenmarkiert();
 };
 
 void _zone::einfuegeninsektor(_sektor*s,_liste<_partition::_polygon >*polylist){
                                                                _listenknoten<_partition::_polygon >*pit;
                                                                //-----------------------
                                                                if(polylist->anfang(pit))do{
                                                                 pit->objekt()->einfuegeninsektor(s);
                                                                 //****************** DEBUG ********************
                                                                 if(dbscreen) dbscreen->schreiben("Polygon in den Sektor eingefuegt.",pc);
                                                                 pit->objekt()->visualisieren(this,pc);
                                                                 debuganimation();
                                                                 pit->objekt()->unvisualisieren();
                                                                 //*********************************************
                                                                }while(polylist->naechstes(pit));
 };
 void _zone::verbindensektor(){
                                                                _sektor*sit;
                                                                //------------------
                                                                if(anfang(sit))do{
                                                                 sit->verbinden();
                                                                }while(naechstes(sit));
 };
 void _zone::erzeugensichtbarkeit(){
                                                                _sektor*sit;
                                                                //------------------
                                                                //************ DEBUG ***********
                                                                erzeugendebugschirm();
                                                                if(dbscreen) dbscreen->schreiben("Visualisierung von Umspannvolumen fuer die Bestimmung der portalen Sichtbarkeit.",pc);
                                                                pdbcount=0;
                                                                //******************************
                                                                if(anfang(sit))do{
                                                                 sit->sichtbarkeitextern()->aushaengen();
                                                                 sit->sichtbarkeitsektor()->aushaengen();
                                                                }while(naechstes(sit));
                                                                if(anfang(sit))do{
                                                                 sit->erzeugensichtbarkeit();
                                                                }while(naechstes(sit));
                                                                if(anfang(sit))do{
                                                                 sit->erzeugensichtbarkeit2tergrad();
                                                                }while(naechstes(sit));
                                                               // _liste< ::_polygon >::aushaengen(); noch nicht !!!!!!!!!!!!!!!!!!!!!!!!!!!!
                                                                //************ DEBUG ***********
                                                                loeschendebugschirm();
                                                                if(anfang(sit))do{
                                                                 //sit->visualisieren();
                                                                }while(naechstes(sit));
                                                                //******************************
 };
 void _zone::loeschenvertexnichtportal(){
                                                                _sektor*sit;
                                                                //------------------
                                                                if(anfang(sit))do{
                                                                 //überlagerte portale aushaengen ? nein, brauch nicht mehr.
                                                                 //überlagerte portale werden ab nun durch einen markierung mechanismus ersetzt
                                                                 sit->loeschenvertexnichtportal();
                                                                }while(naechstes(sit));
 };                                                                
 void _zone::erzeugenvertexlicht(){
                                                                _sektor*sit;
                                                                _listenknoten< ::_polygon >*pit;
                                                                ::_polygon*poly;
                                                                _listenknoten<::_vertex>*lnvit;
                                                                _verbindervertexpolygon*vcp;
                                                                _vektor4<_to> null;
                                                                //------------------
                                                                //funktion setzt die gesamte statische lichtinformation
                                                                //der connectoren der weltpoly auf null
                                                                null.setzen(0,0,0,0);
                                                                if(anfang(pit))do{
                                                                 poly=pit->objekt();
                                                                 if(poly->verwendentexturdynamisch()==false){
                                                                  poly->markierung(1);
                                                                  //vit=poly->vertex();
                                                                  //if(vit)do{
                                                                  iterierenliste(poly,lnvit,
                                                                   vcp=static_cast<_verbindervertexpolygon*>(lnvit);
                                                                   //vcp=vit->connector(poly);
                                                                   if(poly->aufgehellt()==false) vcp->farbe(null); else vcp->farbe(_vektor4<_to>(1,1,1,1)); 
                                                                  // vit=vit->naechstes(poly);
                                                                  //}while(vit!=poly->vertex());
                                                                  );
                                                                 };
                                                                 
                                                                }while(naechstes(pit));
                                                                //dann wird die lichtinformation 
                                                                //über sektoren additiv berechnet           
                                                                if(anfang(sit))do{
                                                                 sit->erzeugenvertexlicht();
                                                                }while(naechstes(sit));
                                                                
                                                                if(anfang(pit))do{
                                                                 
                                                                }while(naechstes(pit));
                                                                
                                                                //dann die polygonfarbe mit dem
                                                                //vcp-licht multiplizieren
                                                                /*
                                                                if(anfang(pit))do{
                                                                 if(pit->objekt()->textur()==0) multiplyvertexlight(pit->objekt());
                                                                }while(naechstes(pit));
                                                                */
 };                                                                
 void _zone::anlegenlightmap(_texturverwaltung<_tb>*tv,_zeichenkette<char> name,_tg sk){
                                                                ::_listenknoten< ::_polygon >*lnpit;
                                                                int i;
                                                                _zeichenkette<char> e;
                                                                _zeichenkette<char> tga=".tga";
                                                                _zeichenkette<char> h;
                                                                char buff[1024];
                                                                //_polygon*p;
                                                                //------------
                                                                i=0;
                                                                if(anfang(lnpit))do{
                                                                 _itoa(i,buff,16);
                                                                 h=buff;
                                                                 while(h.groesse()<8) h.anhaengenfront("0");
                                                                 e=name;
                                                                 e+=h;
                                                                 e+=tga;                                                                
                                                                 lnpit->objekt()->anlegenlightmap(tv,e,sk);
                                                                 i++;
                                                                }while(naechstes(lnpit));
 }; 
 void _zone::multiplyvertexlight(::_polygon*poly){
                                                                //funktion führt multiplikation mit polyfarbe aus
                                                                _vektor4<_to> c;
                                                                _vektor4<_to> p;
                                                                ::_vertex*vit;
                                                                _listenknoten<::_vertex>*lnvit;
                                                                _verbindervertexpolygon*vcp;
                                                                _to x0;
                                                                _to x1;
                                                                _to x2;
                                                                _to x3;
                                                                //-------------------------------------------
                                                                 if(poly->verwendentexturdynamisch()==false){
                                                                iterierenliste(poly,lnvit,
                                                                 vit=lnvit->objekt();
                                                                 //vit=poly->vertex();
                                                                 //if(vit)do{
                                                                 //if(poly->textur()==0){
                                                                 
                                                                 //vcp=vit->connector(poly);
                                                                 vcp=static_cast<_verbindervertexpolygon*>(lnvit);
                                                                 p=poly->farbe();
                                                                 c=vcp->farbe();
                                                                 x0=c[0]*p[0];
                                                                 x1=c[1]*p[1];
                                                                 x2=c[2]*p[2];
                                                                 x3=c[3]*p[3];
                                                                 c.setzen(x0,x1,x2,x3);
                                                                 c.begrenzen(0,1);
                                                                 vcp->farbe(c);
                                                                 //vit=vit->naechstes(poly);
                                                                //}while(vit!=poly->vertex());
                                                                );
                                                                }else{
                                                                 poly->farbeverbinder(_vektor4<_to>(0,0,0,0));
                                                                };
 };
 void _zone::markierung(int f){
                                                                pflag=f;        
 };
 int _zone::markierung()const{
                                                                return(pflag);
 };
 void _zone::markierungebene(int f){
                                                                _ebene*pit;
                                                                //-------------------------
                                                                if(anfang(pit))do{
                                                                 //pit->markierung(f); ne ist zu unnötig speicherlastig
                                                                }while(naechstes(pit));
 };
 _sektor*_zone::sektor(const _vektor3<_tg>&p){
                                                                _sektor*r;
                                                                _ebene*pit;
                                                                bool stop;
                                                                bool frontstop;
                                                                bool backstop;
                                                                //--------------------------
                                                                r=0;
                                                                pit=root();
                                                                if(pit){
                                                                //*********** DEBUG ***********
                                                                //_win::_pclautsprecher sp;
                                                                //sp.peep(1);
                                                                //*****************************
                                                                 stop=false;
                                                                 frontstop=false;
                                                                 backstop=false;
                                                                 do{
                                                                  if(pit->front(p)){
                                                                   frontstop=true;
                                                                   backstop=false;
                                                                   if(pit->naechstes()){
                                                                    pit=pit->naechstes();
                                                                   }else{
                                                                    stop=true;
                                                                   };
                                                                  }else{
                                                                   frontstop=false;
                                                                   backstop=true;
                                                                   if(pit->vorheriges()){
                                                                    pit=pit->vorheriges();
                                                                   }else {
                                                                    stop=true;
                                                                   }
                                                                  };
                                                                  //if((pit->vorheriges()==0)&&(pit->naechstes()==0)) stop=true;
                                                                 }while(stop==false);
                                                                 if(frontstop) r=pit->sektorfront(); else
                                                                 if(backstop)  r=pit->sektorrueck();
                                                                };
                                                                return(r);
 };
 void _zone::einfuegenintern(_netz*n){
                                                                ::_polygon*pit;
                                                                if(n->anfang(pit))do{
                                                                 einfuegenintern(pit);
                                                                }while(n->naechstes(pit));
 };
 void _zone::einfuegenintern(::_polygon*poly){
                                                                _sektor*sit;
                                                                _polygon*pit;
                                                                _listenknoten<_sektor>*lnsit;
                                                                _listenknoten<_polygon>*lnpit;
                                                                //------------
                                                                sit=sektor(poly->mitte());
                                                                if(sit){
                                                                 if(poly->_liste<_sektor>::suchen(sit,lnsit)==false) 
                                                                  if(poly->netz()->dynamisch()) 
                                                                   new _verbinder< ::_polygon,_sektor>(sit->internepolygonedynamisch(),poly,poly,sit); 
                                                                  else 
                                                                   new _verbinder< ::_polygon,_sektor>(sit->internepolygonestatisch(),poly,poly,sit);
                                                                 if(poly->netz()->_liste<_sektor>::suchen(sit,lnsit)==false) 
                                                                  new _verbinder< ::_netz,   _sektor>(sit->internenetze(),poly->netz(),poly->netz(),sit);
                                                                 if(sit->anfang(pit))do{
                                                                  if(pit->portal()){
                                                                   if(pit->innerhalbpolygon(poly)) {
                                                                    if(pit->anfang(lnpit))do{
                                                                     if(lnpit->objekt()->innerhalbpolygon(poly)){
                                                                      if(poly->_liste<_sektor>::suchen(lnpit->objekt()->sektor(),lnsit)==false) 
                                                                       einfuegeninternrekursiv(poly,lnpit->objekt()->sektor());
                                                                     };
                                                                    }while(pit->naechstes(lnpit));
                                                                   };
                                                                  };
                                                                 }while(sit->naechstes(pit));
                                                                }else{
                                                                 //versuchen, das polygon über eine der vertex in die zone zu bekommen
                                                                 sit=0;
                                                                 ::_vertex*vit;
                                                                 _listenknoten<::_vertex>*lnvit;
                                                                 //vit=poly->vertex();
                                                                 if(poly->anfang(lnvit))do{
                                                                  vit=lnvit->objekt();
                                                                  sit=sektor(vit->normale());
                                                                 // vit=vit->naechstes(poly);
                                                                 }while((poly->naechstes(lnvit))&&(sit==0));
                                                                 if(sit){//sektor doch noch gefunden
                                                                  if(poly->_liste<_sektor>::suchen(sit,lnsit)==false) 
                                                                   if(poly->netz()->dynamisch()) 
                                                                    new _verbinder< ::_polygon,_sektor>(sit->internepolygonedynamisch(),poly,poly,sit); 
                                                                   else 
                                                                    new _verbinder< ::_polygon,_sektor>(sit->internepolygonestatisch(),poly,poly,sit);
                                                                  if(poly->netz()->_liste<_sektor>::suchen(sit,lnsit)==false) 
                                                                   new _verbinder< ::_netz,   _sektor>(sit->internenetze(),poly->netz(),poly->netz(),sit);
                                                                  if(sit->anfang(pit))do{
                                                                   if(pit->portal()){
                                                                    if(pit->innerhalbpolygon(poly)) {
                                                                     if(pit->anfang(lnpit))do{
                                                                      if(lnpit->objekt()->innerhalbpolygon(poly)){
                                                                       if(poly->_liste<_sektor>::suchen(lnpit->objekt()->sektor(),lnsit)==false) 
                                                                        einfuegeninternrekursiv(poly,lnpit->objekt()->sektor());
                                                                      };
                                                                     }while(pit->naechstes(lnpit));
                                                                    };
                                                                   };
                                                                  }while(sit->naechstes(pit));
                                                                 };
                                                                };
 };
 void _zone::einfuegeninternrekursiv(::_polygon*poly,_sektor*sektor){
                                                                _polygon*pit;
                                                                _listenknoten<_sektor>*lnsit;
                                                                _listenknoten<_polygon>*lnpit;
                                                                //---------------------------
                                                                if(poly->netz()->dynamisch()) 
                                                                 new _verbinder< ::_polygon,_sektor>(sektor->internepolygonedynamisch(),poly,poly,sektor); 
                                                                else 
                                                                 new _verbinder< ::_polygon,_sektor>(sektor->internepolygonestatisch(),poly,poly,sektor);
                                                                if(poly->netz()->_liste<_sektor>::suchen(sektor,lnsit)==false) new _verbinder< ::_netz,_sektor>(sektor->internenetze(),poly->netz(),poly->netz(),sektor);
                                                              
                                                                if(sektor->anfang(pit))do{
                                                                 if(pit->portal()){
                                                                  if(pit->innerhalbpolygon(poly)) {
                                                                   if(pit->anfang(lnpit))do{
                                                                    
                                                                    if(lnpit->objekt()->innerhalbpolygon(poly)){
                                                                     if(poly->_liste<_sektor>::suchen(lnpit->objekt()->sektor(),lnsit)==false) 
                                                                      einfuegeninternrekursiv(poly,lnpit->objekt()->sektor());
                                                                    };
                                                                    
                                                                   }while(pit->naechstes(lnpit));
                                                                  };
                                                                 };
                                                                }while(sektor->naechstes(pit));
                                                                
};                                                                     


_liste< ::_polygon>* _zone::innerhalbquader(_tg x,_tg y,_tg z,_tg wx,_tg wy,_tg wz)const{
                                                                _sektor*sit;
                                                                _polygon*pit;
                                                                _liste< ::_polygon>*lp;
                                                                _listenknoten< ::_polygon>*lnpit;
                                                                //-------------------
                                                                lp=new _liste< ::_polygon>();
                                                                if(anfang(sit))do{
                                                                 
                                                                 if(sit->anfang(pit))do{
                                                                  if(pit->portal()==false){
                                                                   
                                                                   if(innerhalbquader(x,y,z,wx,wy,wz,pit->polygon())) {
                                                                    lp->einhaengenunredundant(pit->polygon());
                                                                   // pit->polygon()->visualisieren(_vektor4<_to>(0,1,0,1));
                                                                   };
                                                                  };
                                                                 }while(sit->naechstes(pit));
                                                                 
                                                                 if(sit->internepolygonestatisch()->anfang(lnpit))do{
                                                                  if(innerhalbquader(x,y,z,wx,wy,wz,lnpit->objekt())) lp->einhaengenunredundant(lnpit->objekt());                                                                 
                                                                 }while(sit->internepolygonestatisch()->naechstes(lnpit));
                                                                 if(sit->internepolygonedynamisch()->anfang(lnpit))do{
                                                                  if(innerhalbquader(x,y,z,wx,wy,wz,lnpit->objekt())) lp->einhaengenunredundant(lnpit->objekt());                                                                 
                                                                 }while(sit->internepolygonedynamisch()->naechstes(lnpit));
                                                                 
                                                                }while(naechstes(sit));
                                                                return(lp);
                                                                
};
bool _zone::innerhalbquader(_tg x,_tg y,_tg z,_tg wx,_tg wy,_tg wz,::_polygon*p)const{
                                                                
                                                                _vektor3<_tg> m=p->mitte();
                                                                if(m[0]<(x-nahenull)) return(false);
                                                                if(m[0]>(x+wx+nahenull)) return(false);
                                                                if(m[1]<(y-nahenull)) return(false);
                                                                if(m[1]>(y+wy+nahenull)) return(false);
                                                                if(m[2]<(z-nahenull)) return(false);
                                                                if(m[2]>(z+wz+nahenull)) return(false);
                                                                return(true);
                                                                
};

 void _zone::initialisierenzeitfaktor(_zeit*t){
                                                                poldtime=t->system();
                                                                pbilderprosek=16;
                                                                pzeitfaktor=1;
 };
 void _zone::berechnenzeitfaktor(_zeit*t){
                                                                unsigned int nt;
                                                                unsigned int dt;
                                                                //------------------
                                                                t->animieren();
                                                                nt=t->system();
                                                                dt=(nt-poldtime);
                                                                poldtime=nt;
                                                                pzeitfaktor=(_tg(dt)/16.666666666666666667f);
                                                                pbilderprosek=_tg(1000)/_tg(dt);
 };
 _tg _zone::bilderprosekunde(){
                                                                return(pbilderprosek);
 };
 char _zone::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_zone>*sd){
                                                                unsigned int pc=0;
                                                                unsigned int i=0;
                                                                char r=1;
                                                                //-----------------
                                                                r^=sd->ladenbeginn(fn);
                                                                r^=sd->ladenverschachtelung(fn);
                                                                r^=sd->ladenassoziation();
                                                                r^=sd->ladenwert(pc);
                                                                _liste< ::_polygon >::loeschen();
                                                                for(i=0;i<pc;i++){
                                                                 r^=sd->ladenassoziation();
                                                                 _liste< ::_polygon >::einhaengen((::_polygon*)1);//ein pseudowert für einen polygonzeiger, der später durch assoziation geladen wird
                                                                };
                                                                sd->ladenende();
                                                                return(r);
 };
 void _zone::speichern(_speicherbardynamisch<_zone>*sd){
                                                                _listenknoten< ::_polygon >*pit;
                                                             //   _ebene* plit;
                                                                //-----------------
                                                                sd->speichernbeginnblock();
                                                                sd->speichernverschachtelung();
                                                                saveassociationargument(sd->datei(),sd,root());
                                                                sd->speichernwert(_liste< ::_polygon >::anzahl());
                                                                if(anfang(pit))do{
                                                                 saveassociationargument(sd->datei(),sd,pit->objekt());
                                                                }while(naechstes(pit));
                                                               // sd->speichernwert(_baumbasis<_ebene >::anzahl());
                                                                sd->speichernendeblock();
 };
 char _zone::assoziieren(_speicherbardynamisch<_zone>*sd){
                                                                unsigned int i;
                                                                _listenknoten< ::_polygon >*pit;
                                                                ::_polygon*poly;
                                                                _ebene*r;
                                                                //--------------
                                                                sd->assoziierenverschachtelung();
                                                                associateassociationargument(sd->datei(),sd->assoziation(),r);
                                                                root(r);
                                                                if(anfang(pit)){
                                                                 for(i=0;i<_liste< ::_polygon >::anzahl();i++){
                                                                  associateassociationargument(sd->datei(),sd->assoziation(),poly);
                                                                  pit->objekt(poly);
                                                                  naechstes(pit);
                                                                 };
                                                                };
                                                                return(1);
 };
 bool _zone::laden(_dateispeicherbarbinaer*d){
																einhaengenspeicherung(d);
																ladenbeginn();
																d->laden(speichername());
																d->laden(pflag);
																d->laden(pbilderprosek);
																d->laden(pzeitfaktor);
																d->laden(poldtime);
																d->laden(pambientlicht);
																d->laden(pc);
																d->laden(pc2);
																d->laden(pdbcount);
																d->laden(anzahlsektor);
																d->laden(debugsector);

																unsigned int i,a;

																_ebene*e;
																_baumbasis<_ebene>::loeschen();
																d->laden(a);
																for(i=0;i<a;i++){
																 e=new _partition::_ebene(this);
																 e->laden(d);
																};

																_liste<::_polygon>::aushaengen();
																a=ladenanzahl(d);
																for(i=0;i<a;i++){
																 ladenzeiger(d);
																};

																_kamera<_tg>*mit;
																_listebasis<_kamera<_tg> >::loeschen();
																d->laden(a);
																for(i=0;i<a;i++){
																 mit=new _kamera<_tg>(this);
																 mit->laden(d);
																};
																
																_sektor*sit;
																_listebasis<_sektor>::loeschen();
																d->laden(a);
																for(i=0;i<a;i++){
																 sit=new _partition::_sektor(this);
																 sit->laden(d);
																};

																_partikelquelle*qit;
																_listebasis<_partikelquelle>::loeschen();
																d->laden(a);
																for(i=0;i<a;i++){
																 qit=new _partikelquelle(pworld,0,this,pworld);
																 qit->laden(d);
																};

																return(true);
 };
 void _zone::speichern(_dateispeicherbarbinaer*d){
																d->speichern(speichername());
																d->speichern(pflag);
																d->speichern(pbilderprosek);
																d->speichern(pzeitfaktor);
																d->speichern(poldtime);
																d->speichern(pambientlicht);
																d->speichern(pc);
																d->speichern(pc2);
																d->speichern(pdbcount);
																d->speichern(anzahlsektor);
																d->speichern(debugsector);

																_ebene*eit;
																d->speichern(_baumbasis<_ebene>::anzahl());
																iterieren(eit,eit->speichern(d));

																_listenknoten<::_polygon>*lnpit;
																d->speichern(_liste<::_polygon>::anzahl());
																iterieren(lnpit,speichernzeiger(d,lnpit->objekt()));

																_kamera<_tg>*mit;
																d->speichern(_listebasis<_kamera<_tg> >::anzahl());
																iterieren(mit,mit->speichern(d));
																
																_sektor*sit;
																d->speichern(_listebasis<_sektor>::anzahl());
																iterieren(sit,sit->speichern(d));

																_partikelquelle*qit;
																d->speichern(_listebasis<_partikelquelle>::anzahl());
																iterieren(qit,qit->speichern(d));
 };
 bool _zone::assoziieren(){
																if(zeigergeladen()){
																 unsigned int a=ladenanzahl();
																 unsigned int i;
																 for(i=0;i<a;i++){
																  ::_polygon*poly;
																  assoziierenzeiger(poly);
																  _liste<::_polygon>::einhaengen(poly);
																 };
																 loeschenzeiger();
																 loeschenanzahl();
																};
																return(true);
 };
};
//******************************************************************************************************************************************************************************************************
//                                                              P A R T I T I O N   : :   Z O N E I N T E R S E K T I O N 
//******************************************************************************************************************************************************************************************************
namespace _partition{
 _zoneintersektion::_zoneintersektion(_zone*z,::_polygon*p,_vektor3<_tg> l,_tg a):_listenknotenbasissortiert<_zoneintersektion,_tg>(z,a){
                                                                pzone=z;
                                                                ppolygon=p;
                                                                plocus=l;
                                                                palpha=a;
 };
};
//******************************************************************************************************************************************************************************************************
//                                                              P A R T I T I O N   : :   L I N I E N I N T E R S E K T I O N 
//******************************************************************************************************************************************************************************************************
namespace _partition{
 _linienintersektion::_linienintersektion(_listebasis<_linienintersektion >*l,_vektor3<_tg> o,_tg a,_vertex*vv,_vertex*vn):_listenknotenbasissortiert<_linienintersektion,_tg>(l,a),_vektor3<_tg>(o){
                                                                pvprev=vv;
                                                                pvnext=vn;
                                                                palpha=a;
 };
 _tg _linienintersektion::alpha()const{
                                                                return(palpha);
 };
};
//******************************************************************************************************************************************************************************************************
//                                                              P A R T I T I O N   : :   E B E N E
//******************************************************************************************************************************************************************************************************
namespace _partition{
 _ebene::_ebene(_baumbasis<_ebene >*t):_baumknotenbasis<_ebene >(t){
                                                                //ladekonstruktor
                                                                ppoly=0;
                                                                psectorfront=0;
                                                                psectorback=0;
 };                                                                
 _ebene::_ebene(_baumbasis<_ebene >*t,_baumknotenbasis<_ebene >*parent,bool dir,::_polygon*p):_baumknotenbasis<_ebene >(t,parent,dir){
                                                                ppoly=p;
                                                                psectorfront=0;
                                                                psectorback=0;
                                                                //L->schreiben("Plane mit parent wurde kontruiert.");
 };
 _ebene::~_ebene(){
 };
  ::_polygon*_ebene::polygon(){
                                                                return(ppoly);
 };
 
 _sektor*_ebene::sektorfront(){
                                                                return(psectorfront);
 };
 
 _sektor*_ebene::sektorrueck(){
                                                                return(psectorback);
 };
 
 void _ebene::sektorfront(_sektor*s){
                                                                psectorfront=s;
 };
 
 void _ebene::sektorrueck(_sektor*s){
                                                                psectorback=s;
 };
 
 bool _ebene::front(const _vektor3<_tg>&p){
                                                                _vektor3<_tg> h=p-ppoly->mitte();
                                                                _tg l=h.laenge();
                                                                if(l<=nahenull) return(true); else{
                                                                 h*=1/l;
                                                                 if((h*ppoly->normale())>0) return(true); else return(false);
                                                                };
                                                                return(true);
 };
 
 char _ebene::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_ebene>*sd){
                                                                char r=1;
                                                                r^=sd->ladenbeginn(fn);
                                                                r^=sd->ladenverschachtelung(fn);
                                                                r^=sd->ladenassoziation();
                                                                r^=sd->ladenassoziation();
                                                                r^=sd->ladenassoziation();
                                                                r^=sd->ladenassoziation();
                                                                r^=sd->ladenassoziation();
                                                                r^=sd->ladenassoziation();
                                                                sd->ladenende();
                                                                return(r);
 };
 
 void _ebene::speichern(_speicherbardynamisch<_ebene>*sd){
                                                                sd->speichernbeginn();
                                                                sd->speichernverschachtelung();
                                                                saveassociationargument(sd->datei(),sd,ppoly);
                                                                saveassociationargument(sd->datei(),sd,psectorfront);
                                                                saveassociationargument(sd->datei(),sd,psectorback);
                                                                saveassociationargument(sd->datei(),sd,parent());
                                                                saveassociationargument(sd->datei(),sd,vorheriges());
                                                                saveassociationargument(sd->datei(),sd,naechstes());
                                                                sd->speichernende();
                                                                
 };
 
 char _ebene::assoziieren(_speicherbardynamisch<_ebene>*sd){
                                                                _ebene*pa=0;
                                                                _ebene*pn=0;
                                                                _ebene*pp=0;
                                                                sd->assoziierenverschachtelung();
                                                                
                                                                //L->schreiben("ACHTUNG : PLANE WIRD ASSOZIIERT");
                                                              /*  L->schreiben("sd->assoziation() = ",*sd->assoziation());
                                                                L->schreiben("sd->assoziation() = ",*sd->assoziation());
                                                                L->schreiben("sd->assoziation() = ",*sd->assoziation());
                                                                L->schreiben("sd->assoziation() = ",*sd->assoziation());
                                                                L->schreiben("sd->assoziation() = ",*sd->assoziation());
                                                                L->schreiben("sd->assoziation() = ",*sd->assoziation());*/
                                                                associateassociationargument(sd->datei(),sd->assoziation(),ppoly);
                                                                associateassociationargument(sd->datei(),sd->assoziation(),psectorfront);
                                                                associateassociationargument< _partition::_sektor >(sd->datei(),sd->assoziation(),psectorback);
                                                                associateassociationargument< _ebene >(sd->datei(),sd->assoziation(),pa);
                                                                setzenbestizer(pa);
                                                                associateassociationargument< _ebene >(sd->datei(),sd->assoziation(),pp);
                                                                setzenvorheriges(pp);
                                                                associateassociationargument< _ebene >(sd->datei(),sd->assoziation(),pn);
                                                                setzennaechstes(pn);
                                                                return(1);
 };
 bool _ebene::laden(_dateispeicherbarbinaer*d){
																einhaengenspeicherung(d);
																ladenbeginn();
																d->laden(speichername());
																ladenzeiger(d);
																ladenzeiger(d);
																ladenzeiger(d);
																return(true);
 };
 void _ebene::speichern(_dateispeicherbarbinaer*d){
																d->speichern(speichername());
																speichernzeiger(d,ppoly);
																speichernzeiger(d,psectorfront);
																speichernzeiger(d,psectorback);

 };
 bool _ebene::assoziieren(){
																if(zeigergeladen()){
																 assoziierenzeiger(ppoly);
																 assoziierenzeiger(psectorfront);
																 assoziierenzeiger(psectorback);
																 loeschenzeiger();
																};
																return(true);
 };
};
//******************************************************************************************************************************************************************************************************
//                                                              P A R T I T I O N   : :   K A N T E 
//******************************************************************************************************************************************************************************************************
namespace _partition{
 _kante::_kante(_ebene*p0,_ebene*p1,_vektor3<_tg> o,_vektor3<_tg> v,_vektor3<_tg> n){
                                                                pplane[0]=p0;
                                                                pplane[1]=p1;
                                                                plocus=o;
                                                                pvector=v;
                                                                pnormal=n;
                                                                pedgelimitator[0]=0;
                                                                pedgelimitator[1]=0;
                                                                pflag=0;
                                                                //*********DEBUG*********
                                                                debugl=0;
                                                                debugav=0;
                                                                debugan=0;
                                                                debuga0=0;
                                                                debuga1=0;
                                                                //***********************
 };
  _kante::~_kante(){
                                                                loeschenlimitator(true);
                                                                loeschenlimitator(false);
                                                                unvisualisieren();
 };
 void _kante::markierung(int f){
                                                                pflag=f;
 };
 int _kante::markierung() const{
                                                                return(pflag);
 };
 _kantenlimitator* _kante::limitator(bool i){
                                                                if(i){
                                                                 return(pedgelimitator[0]);
                                                                }else{
                                                                 return(pedgelimitator[1]);
                                                                };
 };
 _kantenlimitator*_kante::erzeugenlimitator(bool dir,_tg alp){
                                                                loeschenlimitator(dir);
                                                                if(dir){
                                                                 pedgelimitator[0]=new _partition::_kantenlimitator(this,dir,alp);
                                                                 return(pedgelimitator[0]);
                                                                }else{
                                                                 pedgelimitator[1]=new _partition::_kantenlimitator(this,dir,alp);
                                                                 return(pedgelimitator[1]);
                                                                };
 };
 void _kante::loeschenlimitator(bool b){
                                                                int i;
                                                                if(b){
                                                                 i=0;
                                                                }else{
                                                                 i=1;
                                                                };
                                                                if(pedgelimitator[i]){
                                                                 delete pedgelimitator[i];
                                                                 pedgelimitator[i]=0;
                                                                };
 };
 _vektor3<_tg> _kante::ort()const{
                                                                return(plocus);
 };
 _vektor3<_tg> _kante::vektor()const{
                                                                return(pvector);
 };
 _vektor3<_tg> _kante::normale()const{
                                                                return(pnormal);
 };
 void _kante::visualisieren(const _vektor4<_to> col){
                                                                _vektor4<_to> ccol(0.5,0.5,0.5,0.5);
                                                                _welt*W=pplane[0]->polygon()->netz()->welt();
                                                                //-----------------
                                                                unvisualisieren();
                                                                debugl=new _weltdebuglinie(W,plocus-pvector*20,plocus+pvector*20,col);
                                                                debugan=new _weltdebugpfeil(W,plocus,plocus+pnormal,0.1,0.07,col);
                                                                debugav=new _weltdebugpfeil(W,plocus,plocus+pvector,0.1,0.07,col*0.4f);
                                                                
                                                                if(pedgelimitator[0]){
                                                                 if(pedgelimitator[0]->anderes()) ccol.setzen(1,0,1,0); else ccol.setzen(1,0,0,(_to)0.6);
                                                                 debuga0=new _weltdebugpfeil(W,pedgelimitator[0]->ort(),pedgelimitator[0]->locusvector(),0.1,0.07,ccol);
                                                                };
                                                                if(pedgelimitator[1]){
                                                                 if(pedgelimitator[1]->anderes()) ccol.setzen(1,0,1,0); else ccol.setzen(1,0,0,(_to)0.6);
                                                                 debuga1=new _weltdebugpfeil(W,pedgelimitator[1]->ort(),pedgelimitator[1]->locusvector(),0.1,0.07,ccol);
                                                                };
 };                                                                    
 void _kante::unvisualisieren(){
                                                                if(debugl) {
                                                                 delete debugl;
                                                                 debugl=0;
                                                                };
                                                                if(debugav) {
                                                                 delete debugav;
                                                                 debugav=0;
                                                                };
                                                                if(debugan) {
                                                                 delete debugan;
                                                                 debugan=0;
                                                                };
                                                                if(debuga0) {
                                                                 delete debuga0;
                                                                 debuga0=0;
                                                                };
                                                                if(debuga1){
                                                                 delete debuga1;
                                                                 debuga1=0;
                                                                };
 };                                                                    
};
//******************************************************************************************************************************************************************************************************
//                                                              P A R T I T I O N   : :   K A N T E N L I M I T A T O R
//******************************************************************************************************************************************************************************************************
namespace _partition{
 _kantenlimitator::_kantenlimitator(_kante*e,bool d,_tg a){
                                                                //L->schreiben("EDGELIMITATOR wird KONSTRUIERT : ");
                                                                pedge=e;
                                                                palpha=a;
                                                                pdirection=d;
                                                                isclearing=false;
                                                                pother=0;
 };
  _kantenlimitator::~_kantenlimitator(){
                                                                //L->schreiben("EDGELIMITATOR wird DESTRUIERT : ");
                                                                isclearing=true;
                                                                if(pother){
                                                                 //if(pother->isclearing==false){
                                                                 pother->pother=0;//delete pother;
                                                                 //};
                                                                 pother=0;
                                                                };
 };
  _tg _kantenlimitator::alpha()const{
                                                                return(palpha);
 };                                                                
  bool _kantenlimitator::direktion()const{
                                                                return(pdirection);
 };                           
  bool _kantenlimitator::beweglich(const _tg nalpha)const{
                                                                if(
                                                                ((pdirection==true)&&(nalpha>=palpha))
                                                                ||((pdirection==false)&&(nalpha<=palpha))
                                                                ){
                                                                 return(true);
                                                                }else{
                                                                 return(false);
                                                                };
 };                                      
  _vektor3<_tg> _kantenlimitator::ort()const{
                                                                _vektor3<_tg> r;
                                                                r=pedge->plocus+(pedge->pvector*palpha);
                                                                return(r);
 };
  _vektor3<_tg> _kantenlimitator::locusvector()const{
                                                                _vektor3<_tg> vn;
                                                                _vektor3<_tg> r;
                                                                vn=pedge->vektor();
                                                                vn.normalisieren();
                                                                if(pdirection==false){
                                                                 vn*=-1;
                                                                };
                                                                vn*=0.25;
                                                                r=pedge->plocus+(pedge->pvector*palpha)+vn;
                                                                return(r);
 };
  _kantenlimitator* _kantenlimitator::anderes(){
                                                                return(pother);
 };
  void _kantenlimitator::anderes(_kantenlimitator*o){
                                                                pother=o;
 };
  _kante* _kantenlimitator::kante(){
                                                                return(pedge);
 };
};
//******************************************************************************************************************************************************************************************************
//                                                              P A R T I T I O N   : :   S E K T O R 
//******************************************************************************************************************************************************************************************************
namespace _partition{
 _sektor::_sektor(_zone*z):_listenknotenbasis<_sektor >(z),_baumoctal< ::_polygon,_tg>(0,1,0,1,0,1){
                                                                pzone=z;
                                                                pdbcross=0;
                                                                pbackclosed=false;
 };
 
 _sektor::~_sektor(){
                                                                _listenknoten<_kollidierbarkugel>*k;
                                                                _listenknoten<_kollidierbarpolygontranslation>*n;
                                                                _listenknoten<_kollidierbarnetztranslation>*p;
                                                                if(anfang(k))do{
                                                                 k->objekt()->stammsektor(0);
                                                                 k->objekt()->zone(0);
                                                                }while(naechstes(k));
                                                                if(anfang(n))do{
                                                                 n->objekt()->stammsektor(0);
                                                                 n->objekt()->zone(0);
                                                                }while(naechstes(n));
                                                                if(anfang(p))do{
                                                                 p->objekt()->stammsektor(0);
                                                                 p->objekt()->zone(0);
                                                                }while(naechstes(p));
                                                                
                                                                unvisualisieren();
                                                                
 };
 
 _zone* _sektor::zone(){
                                                                return(pzone);
 };
 
 void _sektor::rueckgeschlossen(){
                                                                pbackclosed=true;
 };
 
 void _sektor::aktualisieren(){
                                                                _polygon*pit;
                                                                _tg c;
                                                                //---------------------
                                                                c=0;
                                                                pmiddle.setzen(0,0,0);
                                                                if(anfang(pit))do{
                                                                 pit->aktualisieren();
                                                                 pmiddle+=pit->mitte();
                                                                 c+=1;
                                                                }while(naechstes(pit));
                                                                if(c>0){
                                                                 pmiddle*=1/c;
                                                                };
 };
 
 void _sektor::verbinden(){
                                                                //steuerung für sektorverknüpfung mit this
                                                                _sektor*sit;
                                                                //--------------------------
                                                                if(pzone->anfang(sit))do{
                                                                 if(sit!=this){
                                                                  verbinden(sit);
                                                                 };
                                                                }while(pzone->naechstes(sit));
 };
 
 void _sektor::verbinden(_sektor*sit){
                                                                //funktion prüft, ob ein sektor sit mit dem sektor this 
                                                                //benachbart ist, es muss untersucht werden, ob portale 
                                                                //des this-sektors diskret komplanar sind mit portalen
                                                                //des sektors sit
                                                                _polygon*pit;
                                                                _polygon*pis;
                                                                _vektor3<_tg> n;
                                                                _tg c;
                                                                _vektor3<_tg> h;
                                                                bool komplanar;
                                                                bool portalconnect;
                                                                _liste<_partition::_polygon > divisionresult;
                                                                _listenknoten<_partition::_polygon >*bit;
                                                                //----------------------------
                                                                if(anfang(pit))do{
                                                                 if(pit->portal()){
                                                                  n=pit->normalsector(pmiddle);
                                                                  n*=-1;
                                                                  if(sit->anfang(pis))do{
                                                                   if(pis->portal()){
                                                                    c=n*pis->normalsector(sit->pmiddle);
                                                                    c-=1;
                                                                    if(fabs(c)<=nahenull){
                                                                     //parallelität
                                                                     komplanar=false;
                                                                     h=pit->mitte()-pis->mitte();
                                                                     if(h.laenge()<=nahenull) komplanar=true;
                                                                     else{
                                                                      h.normalisieren();
                                                                      c=h*n;
                                                                      if(fabs(c)<=nahenull) komplanar=true;
                                                                     };
                                                                     if(komplanar){
                                                                      //komplanarität, es muss das pit-portal konvex zerlegt werden,
                                                                      //wenn es ein divres-bruchstrück gibt, dessen mittelpunkt innerhalb 
                                                                      //des pis-portals liegen, dann muss pis als nachbar für pit eingeordnet werden
                                                                      portalconnect=false;
                                                                      pit->teilen(pis,&divisionresult);
                                                                      if(divisionresult.anfang(bit))do{
                                                                       if(pis->innerhalbpunkt(bit->objekt()->mitte())) portalconnect=true;
                                                                      }while((divisionresult.naechstes(bit))&&(portalconnect==false));
                                                                      if(portalconnect) pit->einhaengen(pis);
                                                                      divisionresult.loeschen();
                                                                     };
                                                                    };
                                                                   };
                                                                  }while(sit->naechstes(pis));
                                                                 };
                                                                }while(naechstes(pit));
 }; 
 
 _vektor3<_tg> _sektor::mitte()const{
                                                                return(pmiddle);
 };



 //------------------------------------------------------------- für tastende figuren ------------------------------------------------------------------------------------------------
 /*
 
 _vektor<_tg> _sektor::kollidierendervektor(const _vektor<_tg>&p,const _vektor<_tg>&v,_partition::_sektor*&ppsector,::_polygon*&polygon){
                                                                bool koll=false;
                                                                polygon=0;
                                                                return(kollidierendervektor(p,v,ppsector,koll,polygon));
 };*/
 
 _vektor3<_tg> _sektor::kollidierendervektor(const _vektor3<_tg>&p,const _vektor3<_tg>&v,_partition::_sektor*&ppsector,bool&koll,::_polygon*&polygon){
                                                                //_vektor<_tg> r;
                                                                _polygon*pit;
                                                                _tg c,D;
                                                                _vektor3<_tg> nv;
                                                                _vektor3<_tg> pn;
                                                                ::_polygon*welt;
                                                                ::_vertex*vit;
                                                                ::_vertex*vin;
                                                                _listenknoten<::_vertex>*lnvit;
                                                                _vertex*pvit;
                                                                _vertex*pvin;
                                                                //bool reflected;
                                                                _vektoranalysis3<_tg> V3;
                                                                _vektor3<_tg> e;
                                                                _vektor3<_tg> h;
                                                                //_vektor<_tg> onv;
                                                                _vektor3<_tg> s;
                                                                _vektor3<_tg> wm;
                                                                //int cc;
                                                                bool diskret;
                                                                _tg rad=0.1;
                                                                //--------------
                                                                koll=false;
                                                                polygon=0;
                                                                ppsector=this;
                                                                nv=v;
                                                                if(v.laenge()>0){
                                                                
                                                                 //cc=0;
                                                                 
                                                                 //do{
                                                                 
                                                                  //reflected=false;
                                                                  if(anfang(pit))do{
                                                                   
                                                                   
                                                                   
                                                                   
                                                                   
                                                                   if(pit->portal()==false){
                                                                    //nichtportal wird geprüft
                                                                    welt=pit->polygon();
                                                                    c=welt->normale()*v;
                                                                    if(c<0){
                                                                     wm=welt->mitte()+welt->normale()*rad;
                                                                     h=wm-(p+v);  
                                                                     c=welt->normale()*h;
                                                                     if(c>=0){
                                                                      //schnittpunkt holen
                                                                      D=V3.determinieren(welt->ebene(0),welt->ebene(1),-v);
                                                                      c=V3.determinieren(welt->ebene(0),welt->ebene(1),p-wm)/D;
                                                                      s=p+v*c;
                                                                      //diskretion prüfen
                                                                      diskret=true;
                                                                      
                                                                      //vit=welt->vertex();
                                                                      //if(vit)do{
                                                                      // vin=vit->naechstes(welt);
                                                                      if(welt->anfang(lnvit))do{
                                                                       vit=lnvit->objekt();
                                                                       vin=lnvit->naechstes()->objekt();
                                                                       h=(vin->ort()-vit->ort())% welt->normale();
                                                                       h.normalisieren();
                                                                       if(  ((wm-vit->ort()) * h)<0) h*=-1;
                                                                       //h=pit->normale(*vit,*vin);
                                                                       //h=wm-vit->ort();
                                                                       //h.normalisieren();
                                                                       D=V3.determinieren(vin->ort()-vit->ort(),welt->normale(),h);
                                                                       if(D!=0){
                                                                        c=V3.determinieren(vin->ort()-vit->ort(),welt->normale(),s-vit->ort())/D;
                                                                        if(c<-(rad+2*nahenull)){
                                                                         diskret=false;
                                                                        };
                                                                       };
                                                                      // vit=vin;
                                                                      }while((welt->naechstes(lnvit))&&(diskret));
                                                                      if(diskret){
                                                                       koll=true;
                                                                       polygon=welt;
                                                                       nv=s-p;
                                                                      };
                                                                     };
                                                                    };
                                                                   }else{
                                                                    //portal wird geprüft 
                                                                    //wenn vektor portal durchdringt, 
                                                                    //dann rekursion einleiten, es ändert sich der sektor
                                                                    pn=pit->normalsector(pmiddle)*-1;
                                                                    if((pn*v)<0){//vektor kommt von hinten ins portal rein
                                                                     wm=pit->mitte();
                                                                     h=wm-(p+v);  
                                                                     if((pn*h)>=0){//endpunkt taucht durch portalkebene durch
                                                                      //schnittpunkt holen
                                                                      welt=pit->polygon();
                                                                      D=V3.determinieren(welt->ebene(0),welt->ebene(1),-v);
                                                                      c=V3.determinieren(welt->ebene(0),welt->ebene(1),p-wm)/D;
                                                                      s=p+v*c;
                                                                      //diskretion prüfen
                                                                      diskret=true;
                                                                      if(pit->anfang(pvit))do{
																	   pvin=pvit->_listenknotenbasis<_vertex>::naechstes();
                                                                       h=wm-*pvit;
                                                                       h.normalisieren();
                                                                       D=V3.determinieren(*pvin-*pvit,welt->normale(),h);
                                                                       if(D!=0){
                                                                        c=V3.determinieren(*pvin-*pvit,welt->normale(),s-*pvit)/D;
                                                                        if(c<-2*nahenull){
                                                                         diskret=false;
                                                                        };
                                                                       };
                                                                      }while((pit->naechstes(pvit))&&(diskret));
                                                                      if(diskret){
                                                                       ppsector=pit->holennaechstersektor(s);
                                                                       if(ppsector==0){
                                                                        //error : kein nachbarsektor gefunden
                                                                        // ********DEBUG*******
                                                                        //_win::_pclautsprecher sp;
                                                                        //sp.peep(20000);
                                                                        // ********************
                                                                        L->schreiben("error sektor::bewegungsvektor : kein nachbarsektor gefunden");
                                                                       }else{
                                                                        nv=ppsector->kollidierendervektor(p,v,ppsector,koll,polygon);
                                                                       };
                                                                      };
                                                                     };
                                                                    };
                                                                   };
                                                                   
                                                                   
                                                                   
                                                                   
                                                                  }while((naechstes(pit))&&(koll==false));
                                                                
                                                                };
                                                              
                                                                return(nv);
 };











 //------------------------------------------------------------- abgleitende kollision ------------------------------------------------------------------------------------------------

 
 _vektor3<_tg> _sektor::bewegungsvektor(const _vektor3<_tg>&p,const _vektor3<_tg>&v,_partition::_sektor*&ppsector,bool&koll){
                                                                ::_polygon*polygon;
                                                                koll=false;
                                                                return(bewegungsvektorrekursiv(p,v,ppsector,koll,polygon));
 };
 
 _vektor3<_tg> _sektor::bewegungsvektor(const _vektor3<_tg>&p,const _vektor3<_tg>&v,_partition::_sektor*&ppsector,bool&koll,::_polygon*&polygon){
                                                                koll=false;
                                                                polygon=0;
                                                                return(bewegungsvektorrekursiv(p,v,ppsector,koll,polygon));
 };
 
 _vektor3<_tg> _sektor::bewegungsvektorrekursiv(const _vektor3<_tg>&p,const _vektor3<_tg>&v,_partition::_sektor*&ppsector,bool&koll,::_polygon*&polygon){
                                                                //_vektor<_tg> r;
                                                                _polygon*pit;
                                                                _tg c,D;
                                                                _vektor3<_tg> nv;
                                                                _vektor3<_tg> pn;
                                                                ::_polygon*welt;
                                                                ::_vertex*vit;
                                                                ::_vertex*vin;
                                                                _listenknoten<::_vertex>*lnvit;
                                                                _vertex*pvit;
                                                                _vertex*pvin;
                                                                bool reflected;
                                                                _vektoranalysis3<_tg> V3;
                                                                _vektor3<_tg> e;
                                                                _vektor3<_tg> h;
                                                                _vektor3<_tg> onv;
                                                                _vektor3<_tg> s;
                                                                _vektor3<_tg> wm;
                                                                int cc;
                                                                bool diskret;
                                                                _tg rad=0.1;
                                                                //--------------
                                                              //  L->schreiben("getmovevectorrec. start");
                                                                ppsector=this;
                                                                
                                                                if(v.laenge()>0){
                                                                
                                                                 nv=v;
                                                                 cc=0;
                                                                 
                                                                 do{
                                                                 
                                                                  reflected=false;
                                                                  if(anfang(pit))do{
                                                                   
                                                                   
                                                                   
                                                                   
                                                                   
                                                                   if(pit->portal()==false){
                                                                    //nichtportal wird geprüft
                                                                    welt=pit->polygon();
                                                                    c=welt->normale()*nv;
                                                                    if(c<0){
                                                                     wm=welt->mitte()+welt->normale()*rad;
                                                                     h=wm-(p+nv);  
                                                                     c=welt->normale()*h;
                                                                     if(c>=0){
                                                                      //schnittpunkt holen
                                                                      D=V3.determinieren(welt->ebene(0),welt->ebene(1),-nv);
                                                                      c=V3.determinieren(welt->ebene(0),welt->ebene(1),p-wm)/D;
                                                                      s=p+nv*c;
                                                                      //diskretion prüfen
                                                                      diskret=true;
                                                                      //vit=welt->vertex();
                                                                      //if(vit)do{
                                                                      // vin=vit->naechstes(welt);
                                                                      if(welt->anfang(lnvit))do{
                                                                       vit=lnvit->objekt();
                                                                       vin=lnvit->naechstes()->objekt();
                                                                       h=(vin->ort()-vit->ort())% welt->normale();
                                                                       h.normalisieren();
                                                                       if(  ((wm-vit->ort()) * h)<0) h*=-1;
                                                                       //h=pit->normale(*vit,*vin);
                                                                       //h=wm-vit->ort();
                                                                       //h.normalisieren();
                                                                       D=V3.determinieren(vin->ort()-vit->ort(),welt->normale(),h);
                                                                       if(D!=0){
                                                                        c=V3.determinieren(vin->ort()-vit->ort(),welt->normale(),s-vit->ort())/D;
                                                                        if(c<-(rad+2*nahenull)){
                                                                         diskret=false;
                                                                        };
                                                                       };
                                                                      // vit=vin;
                                                                      }while((welt->naechstes(lnvit))&&(diskret));
                                                                      if(diskret){
                                                                     
                                                                     
                                                                     
                                                                      //abgleiten von nv an welt ebene duirchführen
                                                                      
                                                                      //if(cc==0){
                                                                       V3.reflektierenpunktnormale(p,p+nv,welt->normale(),e);
                                                                       onv=nv;
                                                                       nv=e-(p+onv);
                                                                       nv=(onv*0.9999999+nv)*0.5;
                                                                       reflected=true;
                                                                       koll=true;
                                                                       polygon=welt;
                                                                      /*if(cc>0){
                                                                       if((nv*v)<0){
                                                                        
                                                                        nv.setzen(0,0,0);
                                                                       };
                                                                      };*/
                                                                      
                                                                      };
                                                                     };
                                                                    };
                                                                   }else{
                                                                    //portal wird geprüft 
                                                                    //wenn vektor portal durchdringt, 
                                                                    //dann rekursion einleiten, es ändert sich der sektor
                                                                    pn=pit->normalsector(pmiddle)*-1;
                                                                    if((pn*nv)<0){
                                                                     wm=pit->mitte();
                                                                     h=wm-(p+nv);  
                                                                     if((pn*h)>=0){
                                                                      //schnittpunkt holen
                                                                      welt=pit->polygon();
                                                                      D=V3.determinieren(welt->ebene(0),welt->ebene(1),-nv);
                                                                      c=V3.determinieren(welt->ebene(0),welt->ebene(1),p-wm)/D;
                                                                      s=p+nv*c;
                                                                      //diskretion prüfen
                                                                      diskret=true;
                                                                      if(pit->anfang(pvit))do{
																	   pvin=pvit->_listenknotenbasis<_vertex>::naechstes();
                                                                       h=wm-*pvit;
                                                                       h.normalisieren();
                                                                       D=V3.determinieren(*pvin-*pvit,welt->normale(),h);
                                                                       if(D!=0){
                                                                        c=V3.determinieren(*pvin-*pvit,welt->normale(),s-*pvit)/D;
                                                                        if(c<-2*nahenull){
                                                                         diskret=false;
                                                                        };
                                                                       };
                                                                      }while((pit->naechstes(pvit))&&(diskret));
                                                                      if(diskret){
                                                                       ppsector=pit->holennaechstersektor(s);
                                                                       if(ppsector==0){
                                                                        //error : kein nachbarsektor gefunden
                                                                        // ********DEBUG*******
                                                                        //_win::_pclautsprecher sp;
                                                                        //sp.peep(20000);
                                                                        // ********************
                                                                        L->schreiben("error sektor::bewegungsvektor : kein nachbarsektor gefunden");
                                                                       }else{
                                                                        nv=ppsector->bewegungsvektorrekursiv(p,nv,ppsector,koll,polygon);
                                                                       };
                                                                      };
                                                                     };
                                                                    };
                                                                   };
                                                                   
                                                                   
                                                                   
                                                                   
                                                                  }while((naechstes(pit))&&(reflected==false));
                                                                  cc++;
                                                                 }while(reflected);
                                                                };
                                                          //      L->schreiben("getmovevectorrec. ende");
                                                               
                                                                return(nv);
 };
 
 _vektor3<_tg> _sektor::bewegungsvektorreflektiv(const _vektor3<_tg>&p,const _vektor3<_tg>&v,bool&koll) const{
                                                                //_vektor<_tg> r;
                                                                _polygon*pit;
                                                                _tg c,D;
                                                                _vektor3<_tg> nv;
                                                                ::_polygon*welt;
                                                                ::_vertex*vit;
                                                                ::_vertex*vin;
                                                                _listenknoten<::_vertex>*lnvit;
                                                                bool reflected;
                                                                _vektoranalysis3<_tg> V3;
                                                                _vektor3<_tg> e;
                                                                _vektor3<_tg> h;
                                                                _vektor3<_tg>  onv;
                                                                _vektor3<_tg> s;
                                                                _vektor3<_tg> wm;
                                                                int cc;
                                                                bool diskret;
                                                                bool brems;
                                                                //--------------
                                                                brems=false;
                                                                koll=false;
                                                                
                                                                if(v.laenge()>0){
                                                                 nv=v;
                                                                 cc=0;
                                                                 
                                                                 do{
                                                                 
                                                                  reflected=false;
                                                                  if(anfang(pit))do{
                                                                   if(pit->portal()==false){
                                                                    welt=pit->polygon();
                                                                    c=welt->normale()*nv;
                                                                    if(c<0){
                                                                     wm=welt->mitte();
                                                                     h=wm-(p+nv);  
                                                                     c=welt->normale()*h;
                                                                     if(c>=0){
                                                                      //schnittpunkt holen
                                                                      D=V3.determinieren(welt->ebene(0),welt->ebene(1),-nv);
                                                                      c=V3.determinieren(welt->ebene(0),welt->ebene(1),p-wm)/D;
                                                                      s=p+nv*c;
                                                                      //diskretion prüfen
                                                                      diskret=true;
                                                                      //vit=welt->vertex();
                                                                      //if(vit)do{
                                                                      // vin=vit->naechstes(welt);
                                                                      if(welt->anfang(lnvit))do{
                                                                       vit=lnvit->objekt();
                                                                       vin=lnvit->naechstes()->objekt();
                                                                       h=wm-vit->ort();
                                                                       h.normalisieren();
                                                                       D=V3.determinieren(vin->ort()-vit->ort(),welt->normale(),wm-vit->ort());
                                                                       if(D!=0){
                                                                        c=V3.determinieren(vin->ort()-vit->ort(),welt->normale(),s-vit->ort())/D;
                                                                        if(c<-2*nahenull){
                                                                         diskret=false;
                                                                        };
                                                                       };
                                                                      // vit=vin;
                                                                      }while((welt->naechstes(lnvit))&&(diskret));
                                                                      if(diskret){
                                                                     
                                                                     
                                                                     
                                                                      //reflektion von nv an welt ebene durchführen
                                                                      //if(cc==0){
                                                                       V3.reflektierenpunktnormale(p,p+nv,welt->normale(),e);
                                                                       //onv=nv;
                                                                       //nv=e-(p+onv);
                                                                       //nv=(onv*0.9999999+nv)*0.5;
                                                                       nv=e-(p+nv);
                                                                       reflected=true;
                                                                       koll=true;
                                                                       brems=true;
                                                                       nv*=0.8;
                                                                      /*if(cc>0){
                                                                       if((nv*v)<0){
                                                                        
                                                                        nv.setzen(0,0,0);
                                                                       };
                                                                      };*/
                                                                      
                                                                      };
                                                                     };
                                                                    };
                                                                   }else{
                                                                    //portal
                                                                   };
                                                                  }while((naechstes(pit))&&(reflected==false));
                                                                  cc++;
                                                                 }while(reflected);
                                                                 
                                                                 
                                                                };
                                                                //if(brems) 
                                                                return(nv);
 };
 
 void _sektor::transformieren(_grafik*gra,_kamera<_tg>*cam){
                                                                _polygon*pit;
                                                                _listenknoten< ::_polygon >*wit;
                                                                ::_polygon*poly;
                                                                //----------------------------
                                                                if(pzone->welt()->eigenetransformation()){
                                                                 //alle flags  nullen
                                                                 if(anfang(pit))do{
                                                                  if(pit->portal()==false) {
                                                                   pit->polygon()->markierung(0);
                                                                   pit->polygon()->markierungvertex(0);
                                                                  };
                                                                 }while(naechstes(pit));
                                                                 if(pvisibilityextern.anfang(wit))do{
                                                                  wit->objekt()->markierung(0);
                                                                  wit->objekt()->markierungvertex(0);
                                                                 }while(pvisibilityextern.naechstes(wit));
                                                                 //interne transformieren
                                                                 if(anfang(pit))do{
                                                                  if(pit->portal()==false) {
                                                                   poly=pit->polygon();
                                                                   if(poly->markierung()==0){
                                                                    poly->transformieren(gra,cam);
                                                                    poly->markierung(1);
                                                                   };
                                                                  };
                                                                 }while(naechstes(pit));
                                                                 //externe transformieren
                                                                 if(pvisibilityextern.anfang(wit))do{
                                                                  poly=wit->objekt();
                                                                  if(poly->markierung()==0){
                                                                   poly->transformieren(gra,cam);
                                                                   poly->markierung(1); 
                                                                  };
                                                                 }while(pvisibilityextern.naechstes(wit));
                                                                }else{
                                                                 pzone->welt()->transformierenglobal(gra,cam);
                                                                };
 };
//*********************************************************************************************************************************************************
//*                 H A U P T Z E I C H N U N G S F U N K T I O N   F Ü R   S E K T O R B A S I E R T E S   Z E I C H N E N 
//*********************************************************************************************************************************************************
 void _sektor::zeichnenambient(_grafik*gra,_kamera<_tg>*cam,::_polygon*poly,unsigned int zyklus,unsigned int pass,bool nutzetransparenz){
                                                                if((poly->markierungzeichnenzyklus==zyklus)&&(poly->markierungzeichnenpass==pass)){
                                                                 //schon gezeichnet
                                                                }else{
                                                               //  if(poly->rueckseitig(cam,zyklus)==false){
                                                                  if(poly->dynamischschattiert()){
                                                                   if(((nutzetransparenz)&&(poly->transparenz())) ||  ((!nutzetransparenz)&&(!poly->transparenz())) )  {
                                                                    poly->bindentransparenz(gra);
                                                                    poly->bindenmaskierung(gra);
                                                                    poly->bindenzweiseitigkeit(gra);//pzone->ambientlicht().setzen(1,1,1);
                                                                    if(poly->verwendentexturdynamisch()==true){
                                                                     //poly->verwendentexturdynamisch(true);//neu, wird doch nicht gemacht
                                                                     poly->zeichnen(gra,pzone->ambientlicht(),0);
                                                                     //poly->verwendentexturdynamisch(true);
                                                                    }else{
                                                                     poly->zeichnen(gra);//,pzone->ambientlicht());//!!!!!!!!!!!!!!!!!!!!!!!!!!!!! wieder einkommetiweren 12.10.2008
                                                                    };
                                                                    poly->markierungzeichnenzyklus=zyklus; 
                                                                    poly->markierungzeichnenpass=pass;
                                                                   };
                                                                  };
                                                                // };
                                                                };
 };
 void _sektor::zeichnenadditiv(_grafik*gra,_kamera<_tg>*cam,::_polygon*poly,unsigned int zyklus,unsigned int pass){
                                                                bool td;
                                                                if((poly->markierungzeichnenzyklus==zyklus)&&(poly->markierungzeichnenpass==pass)){
                                                                 //schon gezeichnet
                                                                }else{
                                                                 if(poly->rueckseitig(cam,zyklus)==false){
                                                                  if(poly->dynamischschattiert()){
                                                                   td=poly->verwendentexturdynamisch();
                                                                   if(td){
                                                                    gra->beleuchtung(true);//glEnable(GL_LIGHTING);
                                                                    poly->bindenmaterialoptik(gra);
                                                                    poly->bindenmaskierung(gra);
                                                                    poly->bindenzweiseitigkeit(gra);
                                                                    poly->zeichnen(gra);
                                                                   }else{
                                                                    gra->beleuchtung(true);//glEnable(GL_LIGHTING);
                                                                    poly->bindenmaterialoptik(gra);
                                                                    //glDisable(GL_LIGHTING);
                                                                    poly->bindenmaskierung(gra);
                                                                    poly->bindenzweiseitigkeit(gra);
                                                                    poly->zeichnen(gra);
                                                                    //glEnable(GL_LIGHTING);
                                                                   };
                                                                   poly->markierungzeichnenzyklus=zyklus; 
                                                                   poly->markierungzeichnenpass=pass;
                                                                  };
                                                                 };
                                                                };
 };
 void _sektor::zeichnennichtdynamischschattiert(_grafik*gra,_kamera<_tg>*cam,::_polygon*poly,unsigned int zyklus,unsigned int pass){
                                                                if(poly->dynamischschattiert()==false){
                                                                 if((poly->markierungzeichnenzyklus==zyklus)&&(poly->markierungzeichnenpass==pass)){
                                                                  //schon gezeichnet
                                                                 }else{
                                                                  if(poly->rueckseitig(cam,zyklus)==false){                                                                  
                                                                   poly->bindentransparenz(gra);
                                                                   poly->bindenmaskierung(gra);
                                                                   poly->bindenzweiseitigkeit(gra);
                                                                   poly->zeichnen(gra);
                                                                   poly->markierungzeichnenzyklus=zyklus; 
                                                                   poly->markierungzeichnenpass=pass;
                                                                  };
                                                                 };
                                                                };
 };
 void _sektor::zeichnen(_grafik*gra,_kamera<_tg>*cam){
                                                                _polygon*pit;
                                                                _listenknoten< ::_polygon >*wit;
                                                                _listenknoten< _sektor>*sit;
                                                                 _sektor*sektor;
                                                                _licht<_tg,_to>*lit;
                                                                unsigned int zyklus=pzone->welt()->zyklus();
                                                                unsigned int is;
                                                                _kugel*kit;
                                                                //-------------------------------------------
                                                                gra->allebufferloeschen();//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
                                                                //*********************************************************************************************************************************************************
                                                                //*                       SZENE MIT AMBIENTER BELEUCHTUNG ZEICHNEN                                                     
                                                                //*********************************************************************************************************************************************************
                                                                gra->schablonenbufferkondition(false);//glDisable(GL_STENCIL_TEST);
                                                                gra->beleuchtung(false);//glDisable(GL_LIGHTING);
                                                                gra->licht(0,false);//glDisable(GL_LIGHT0);
                                                                gra->licht(1,false);//glDisable(GL_LIGHT1);
                                                                gra->licht(2,false);//glDisable(GL_LIGHT2);
                                                                gra->licht(3,false);//glDisable(GL_LIGHT3);
                                                                gra->licht(4,false);//glDisable(GL_LIGHT4);
                                                                gra->licht(5,false);//glDisable(GL_LIGHT5);
                                                                gra->licht(6,false);//glDisable(GL_LIGHT6);
                                                                gra->licht(7,false);//glDisable(GL_LIGHT7);
                                                                gra->tiefenbufferkondition(true);//glEnable(GL_DEPTH_TEST);
                                                                gra->tiefenbufferschreiben(true);
                                                                gra->transparenz(false);//glDisable(GL_BLEND);
                                                                gra->maske(false);//glDisable(GL_ALPHA_TEST);
                                                                gra->tiefenbufferkonditionkleinergleich();//glDepthFunc(GL_LEQUAL);
                                                                //-------------------- kugeln zeichnen -------------------------------------
                                                                gra->ausschussflaeche(true);//glEnable(GL_CULL_FACE);
                                                                gra->transparenz(false);
                                                                gra->tiefenbufferschreiben(true);
                                                                if(pzone->welt()->anfang(kit))do{
                                                                 kit->zeichnen(gra);
                                                                }while(pzone->welt()->naechstes(kit));
                                                                //------------- externe zeichnen (polygonale sichtbarkeit 1.greades --------
                                                                if(pvisibilityextern.anfang(wit))do{
                                                                 zeichnenambient(gra,cam,wit->objekt(),zyklus,0,false);
                                                                }while(pvisibilityextern.naechstes(wit));
                                                                //--------------- die statischen, internen der sichtbarkeit 1. grades zeichnen ---
                                                                if(pvisibilityintern.anfang(wit))do{
                                                                 zeichnenambient(gra,cam,wit->objekt(),zyklus,0,false);
                                                                }while(pvisibilityintern.naechstes(wit));
                                                                //--------------- die dynamisch internen der sektorsichtbarkeit 1.grades zeichnen
                                                                if(pvisibilitysector.anfang(sit))do{
                                                                 if(sit->objekt()->internepolygonedynamisch()->anfang(wit))do{
                                                                  zeichnenambient(gra,cam,wit->objekt(),zyklus,0,false);
                                                                 }while(sit->objekt()->internepolygonedynamisch()->naechstes(wit));
                                                                }while(pvisibilitysector.naechstes(sit));
                                                                //------------------- implizite zeichnen ---------------------------------
                                                                if(anfang(pit))do{
                                                                 if(pit->portal()==false) zeichnenambient(gra,cam,pit->polygon(),zyklus,0,false);
                                                                }while(naechstes(pit));
                                                                //-------------------- die internen von diesem sektor zeichnen ------------
                                                                if(pinternstatisch.anfang(wit))do{
                                                                 zeichnenambient(gra,cam,wit->objekt(),zyklus,0,false);
                                                                }while(pinternstatisch.naechstes(wit));
                                                                if(pinterndynamisch.anfang(wit))do{
                                                                 zeichnenambient(gra,cam,wit->objekt(),zyklus,0,false);
                                                                }while(pinterndynamisch.naechstes(wit));
                                                                
                                                                //----------------------------------- TRANSPARENZ ------------------------------------------------
                                                                //------------- externe zeichnen (polygonale sichtbarkeit 1.greades --------
                                                                if(pvisibilityextern.anfang(wit))do{
                                                                 zeichnenambient(gra,cam,wit->objekt(),zyklus,0,true);
                                                                }while(pvisibilityextern.naechstes(wit));
                                                                //--------------- die statischen, internen der sichtbarkeit 1. grades zeichnen ---
                                                                if(pvisibilityintern.anfang(wit))do{
                                                                 zeichnenambient(gra,cam,wit->objekt(),zyklus,0,true);
                                                                }while(pvisibilityintern.naechstes(wit));
                                                                //--------------- die dynamisch internen der sektorsichtbarkeit 1.grades zeichnen
                                                                if(pvisibilitysector.anfang(sit))do{
                                                                 if(sit->objekt()->internepolygonedynamisch()->anfang(wit))do{
                                                                  zeichnenambient(gra,cam,wit->objekt(),zyklus,0,true);
                                                                 }while(sit->objekt()->internepolygonedynamisch()->naechstes(wit));
                                                                }while(pvisibilitysector.naechstes(sit));
                                                                //------------------- implizite zeichnen ---------------------------------
                                                                if(anfang(pit))do{
                                                                 if(pit->portal()==false) zeichnenambient(gra,cam,pit->polygon(),zyklus,0,true);
                                                                }while(naechstes(pit));
                                                                //-------------------- die internen von diesem sektor zeichnen ------------
                                                                if(pinternstatisch.anfang(wit))do{
                                                                 zeichnenambient(gra,cam,wit->objekt(),zyklus,0,true);
                                                                }while(pinternstatisch.naechstes(wit));
                                                                if(pinterndynamisch.anfang(wit))do{
                                                                 zeichnenambient(gra,cam,wit->objekt(),zyklus,0,true);
                                                                }while(pinterndynamisch.naechstes(wit));
                                                                
                                                                //*********************************************************************************************************************************************************
                                                                //                BELEUCHTUNGSPASS DURCHFÜHREN : this zeichnen ohne ext. poly                                                     *
                                                                //*********************************************************************************************************************************************************
                                                                gra->maske(false);//glDisable(GL_ALPHA_TEST);
                                                                is=1;
                                                                if(anfang(lit))do{
                                                                 if(lit->dynamisch()) if(lit->dynamischadditiv()) zeichnenadditiv(gra,cam,lit,is++); else zeichnensubtraktiv(gra,cam,lit,is++);
                                                                }while(naechstes(lit));
                                                                //if(pvisibilitysector.anfang(sit))do{
                                                                // sektor=sit->objekt();
                                                                // if(sektor->anfang(lit))do{
                                                                //  zeichnen(gra,cam,lit,is++);
                                                                // }while(sektor->naechstes(lit));
                                                                //}while(pvisibilitysector.naechstes(sit));   
                                                                if(pvisibilitysector2tergrad.anfang(sit))do{
                                                                 sektor=sit->objekt();
                                                                 if(sektor->anfang(lit))do{
                                                                  if(lit->dynamisch()) if(lit->dynamischadditiv()) zeichnenadditiv(gra,cam,lit,is++); else zeichnensubtraktiv(gra,cam,lit,is++);
                                                                 }while(sektor->naechstes(lit));
                                                                }while(pvisibilitysector2tergrad.naechstes(sit));   
                                                                gra->tiefenbufferkonditionkleinergleich();//glDepthFunc(GL_LEQUAL);
                                                                gra->licht(0,false);//glDisable(GL_LIGHT0);
                                                                gra->schablonenbufferkondition(false);//glDisable(GL_STENCIL_TEST);                                                                 
                                                                gra->beleuchtung(false);//glDisable(GL_LIGHTING);
                                                                
                                                                //*********************************************************************************************************************************************************
                                                                //                 NICHT SCHATTIERTE ZEICHNEN AUCH Sprites und debugs zeichnen 
                                                                //*********************************************************************************************************************************************************
                                                                is++;
                                                                gra->schablonenbufferkondition(false);//glDisable(GL_STENCIL_TEST);
                                                                gra->beleuchtung(false);//glDisable(GL_LIGHTING);
                                                                gra->tiefenbufferkondition(true);//glEnable(GL_DEPTH_TEST);
                                                                gra->tiefenbufferkonditionkleinergleich();//glDepthFunc(GL_LEQUAL);
                                                                //------------- externe zeichnen (polygonale sichtbarkeit 1.greades --------
                                                                if(pvisibilityextern.anfang(wit))do{
                                                                 zeichnennichtdynamischschattiert(gra,cam,wit->objekt(),zyklus,is);
                                                                }while(pvisibilityextern.naechstes(wit));
                                                                //--------------- die statischen, internen der sichtbarkeit 1. grades zeichnen ---
                                                                if(pvisibilityintern.anfang(wit))do{
                                                                 zeichnennichtdynamischschattiert(gra,cam,wit->objekt(),zyklus,is);
                                                                }while(pvisibilityintern.naechstes(wit));
                                                                //--------------- die dynamisch internen der sektorsichtbarkeit 1.grades zeichnen
                                                                if(pvisibilitysector.anfang(sit))do{
                                                                 if(sit->objekt()->internepolygonedynamisch()->anfang(wit))do{
                                                                  zeichnennichtdynamischschattiert(gra,cam,wit->objekt(),zyklus,is);
                                                                 }while(sit->objekt()->internepolygonedynamisch()->naechstes(wit));
                                                                }while(pvisibilitysector.naechstes(sit));
                                                                //------------------- implizite zeichnen ---------------------------------
                                                                if(anfang(pit))do{
                                                                 if(pit->portal()==false) zeichnennichtdynamischschattiert(gra,cam,pit->polygon(),zyklus,is);
                                                                }while(naechstes(pit));
                                                                //-------------------- die internen von diesem sektor zeichnen ------------
                                                                if(pinternstatisch.anfang(wit))do{
                                                                 zeichnennichtdynamischschattiert(gra,cam,wit->objekt(),zyklus,is);
                                                                }while(pinternstatisch.naechstes(wit));
                                                                if(pinterndynamisch.anfang(wit))do{
                                                                 zeichnennichtdynamischschattiert(gra,cam,wit->objekt(),zyklus,is);
                                                                }while(pinterndynamisch.naechstes(wit));
                                                                gra->tiefenbufferschreiben(true);
                                                                gra->transparenz(false);
                                                                //-------------------- debugs zeichnen ---------------------------------------
                                                                
                                                                gra->ausschussflaeche(true);//glEnable(GL_CULL_FACE);
                                                                gra->tiefenbufferkonditionkleinergleich();//glDepthFunc(GL_LEQUAL);
                                                                gra->licht(0,false);//glDisable(GL_LIGHT0);
                                                                gra->schablonenbufferkondition(false);//glDisable(GL_STENCIL_TEST);                                                                 
                                                                gra->beleuchtung(false);//glDisable(GL_LIGHTING);
                                                                gra->transparenz(true);//glEnable(GL_BLEND);
                                                                gra->maske(false);//glDisable(GL_ALPHA_TEST);
                                                                _weltdebug*dit;
                                                                if(pzone->welt()->anfang(dit))do{
                                                                 dit->zeichnen(gra);
                                                                }while(pzone->welt()->naechstes(dit));
                                                                //-------------------- sprites zeichnen -------------------------------------
                                                                pzone->welt()->zeichnensprite(gra,cam);
                                                                //------------------- schattenvolumen debug -----------------------------------
                                                                //if(anfang(pit))do{
                                                                // if(pit->portal()==false){
                                                                //  _polygonschatten*psit;
                                                                //  if(pit->polygon()->anfang(psit))do{
                                                                //   psit->zeichnendebug(gra);
                                                                //  }while(pit->polygon()->naechstes(psit));
                                                                // };
                                                                //}while(naechstes(pit));
                                                                _netzschatten*nsit;
                                                                _listenknoten<_netz>*nit;
                                                                if(pinternnetz.anfang(nit))do{
                                                                 if(nit->objekt()->anfang(nsit))do{
                                                                  nsit->zeichnendebug(gra);
                                                                 }while(nit->objekt()->naechstes(nsit));
                                                                }while(pinternnetz.naechstes(nit));
                                                                
                                                                
 };
 void _sektor::zeichnenadditiv(_grafik*gra,_kamera<_tg>*cam,_licht<_tg,_to>*lit,unsigned int is){
                                                                _listenknoten<_schatten<_tg,_to> >*schit;
                                                                _kugel*kit;
                                                                _polygon*pit;
                                                                _listenknoten< ::_polygon >*wit;
                                                                _listenknoten< _sektor>*sit;
                                                                unsigned int zyklus=pzone->welt()->zyklus();
                                                                //------------- 2. PASS : SCHATTENVOLUMEN IN DEN STENCIL BUFFER SCHREIBEN ----------------------------------------------
                                                                if(lit->_liste<_schatten<_tg,_to> >::anfang(schit)){
                                                                
                                                                 glClear(GL_STENCIL_BUFFER_BIT);
                                                                 glDepthFunc(GL_LESS);
                                                                 glEnable(GL_POLYGON_OFFSET_FILL);
                                                                 glPolygonOffset(0.1,10);
                                                                 glDisable(GL_TEXTURE_2D);
                                                                 glColorMask(0,0,0,0);
                                                                 glDepthMask(0);
                                                                 glEnable(GL_STENCIL_TEST);
                                                                 glEnable(GL_CULL_FACE);
                                                                 glCullFace(GL_FRONT);
                                                                 glShadeModel(GL_FLAT);
                                                                 glStencilFunc(GL_ALWAYS,0,0xff);
                                                                 glStencilMask(~0);
                                                                 glStencilOp(GL_KEEP,GL_INCR,GL_KEEP);
                                                                 
                                                                 /*
                                                                 gra->schablonenbufferloeschen();//glClear(GL_STENCIL_BUFFER_BIT);
                                                                 gra->tiefenbufferkonditionkleiner();//glDepthFunc(GL_LESS);
                                                                 gra->polygonverschiebung(true);//glEnable(GL_POLYGON_OFFSET_FILL);
                                                                 gra->polygonverschiebung(0.1,10);//glPolygonOffset(0.1,10);	
                                                                 gra->textur(false);//glDisable(GL_TEXTURE_2D);
                                                                 gra->anzeigebufferschreiben(false);//glColorMask(0,0,0,0);
                                                                 gra->tiefenbufferschreiben(false);//glDepthMask(0);
                                                                 gra->schablonenbufferkondition(true);//glEnable(GL_STENCIL_TEST);
                                                                 gra->ausschussflaeche(true);//glEnable(GL_CULL_FACE);
                                                                 gra->ausschussflaechefront();//glCullFace(GL_FRONT);
                                                                 gra->beleuchtungflach();//glShadeModel(GL_FLAT);

                                                                 gra->schablonenbufferkonditionimmer(0,0xff);//glStencilFunc(GL_ALWAYS,0,0xff);
                                                                 gra->schablonenbufferschreiben(true);//glStencilMask(~0);
                                                                 gra->schablonenbufferoperation(0,1,0);//glStencilOp(GL_KEEP,GL_INCR,GL_KEEP);
                                                                 */
                                                                 //---------zur kamera backfaced schattenpolygone zeichnen
                                                                 if(lit->_liste<_schatten<_tg,_to> >::anfang(schit))do{
                                                                  schit->objekt()->zeichnen(gra);
                                                                 }while(lit->_liste<_schatten<_tg,_to> >::naechstes(schit));
                                                                 /*_listenknoten<_netz>*lknit;
                                                                 _listenknoten< ::_polygon>*lkpit;
                                                                 //_netz*nit; 
                                                                 //_netzschatten*nsit;
                                                                 //_kugelschatten*ksit;
                                                                 //schatten der internen netze
                                                                 if(pinternnetz.anfang(lknit))do{
                                                                  lknit->objekt()->zeichnenschatten(gra,lit);
                                                                 }while(pinternnetz.naechstes(lknit));
                                                                 //schatten der internen polygone
                                                                 //if(pintern.anfang(lkpit))do{
                                                                 // lkpit->objekt()->zeichnenschatten(gra,lit);
                                                                 //}while(pintern.naechstes(lkpit));
                                                                 //schatten der internen netze der externen sektoren und
                                                                 //schatten der internen polygone der externen sektoren
                                                                 if(pvisibilitysector.anfang(sit))do{
                                                                  sektor=sit->objekt();
                                                                  if(sektor->pinternnetz.anfang(lknit))do{
                                                                   lknit->objekt()->zeichnenschatten(gra,lit);
                                                                  }while(sektor->pinternnetz.naechstes(lknit));
                                                                  //if(sektor->pintern.anfang(lkpit))do{
                                                                  // lkpit->objekt()->zeichnenschatten(gra,lit);
                                                                  //}while(sektor->pintern.naechstes(lkpit));
                                                                 }while(pvisibilitysector.naechstes(sit));   
                                                                 //schatten der impliziten
                                                                 if(anfang(pit))do{
                                                                  pit->polygon()->zeichnenschatten(gra,lit);
                                                                 }while(naechstes(pit));
                                                                 //schatten der externen
                                                                 if(pvisibilitysector.anfang(sit))do{
                                                                  sektor=sit->objekt();
                                                                  if(sektor->anfang(pit))do{
                                                                   pit->polygon()->zeichnenschatten(gra,lit);
                                                                  }while(sektor->naechstes(pit));
                                                                 }while(pvisibilitysector.naechstes(sit));
                                                                 //kugelschateen zeichnen
                                                                 if(pzone->welt()->anfang(kit))do{
                                                                   kit->zeichnenschatten(gra,lit);
                                                                  }while(pzone->welt()->naechstes(kit));*/
                                                                  //---------zur kamera frontfaced schattenpolygone zeichnen
                                                                  glCullFace(GL_BACK);
                                                                  glStencilFunc(GL_ALWAYS, 0x0, 0xff);
                                                                  glStencilOp(GL_KEEP,GL_DECR,GL_KEEP);
                                                                  
			                                                      /*gra->ausschussflaecherueck();//glCullFace(GL_BACK);
                                                           		  gra->schablonenbufferkonditionimmer(0,0xff);//glStencilFunc(GL_ALWAYS, 0x0, 0xff);
			                                                      gra->schablonenbufferoperation(0,-1,0);//glStencilOp(GL_KEEP,GL_DECR,GL_KEEP);
			                                                      */
                                                                  if(lit->_liste<_schatten<_tg,_to> >::anfang(schit))do{
                                                                   schit->objekt()->zeichnen(gra);
                                                                  }while(lit->_liste<_schatten<_tg,_to> >::naechstes(schit));
			                                                      /*
                                                                  //schatten der internen
                                                                  if(pinternnetz.anfang(lknit))do{
                                                                   lknit->objekt()->zeichnenschatten(gra,lit);
                                                                  }while(pinternnetz.naechstes(lknit));
                                                                  //schatten der internen der externen
                                                                  if(pvisibilitysector.anfang(sit))do{
                                                                   sektor=sit->objekt();
                                                                   if(sektor->pinternnetz.anfang(lknit))do{
                                                                    lknit->objekt()->zeichnenschatten(gra,lit);
                                                                   }while(sektor->pinternnetz.naechstes(lknit));
                                                                  }while(pvisibilitysector.naechstes(sit));   
                                                                  //schatten der impliziten
                                                                  if(anfang(pit))do{
                                                                   pit->polygon()->zeichnenschatten(gra,lit);
                                                                  }while(naechstes(pit));
                                                                  //schatten der externen
                                                                  if(pvisibilitysector.anfang(sit))do{
                                                                  sektor=sit->objekt();
                                                                   if(sektor->anfang(pit))do{
                                                                    pit->polygon()->zeichnenschatten(gra,lit);
                                                                   }while(sektor->naechstes(pit));
                                                                  }while(pvisibilitysector.naechstes(sit));
                                                                  //kugelschateen zeichnen
                                                                  if(pzone->welt()->anfang(kit))do{
                                                                   kit->zeichnenschatten(gra,lit);
                                                                 }while(pzone->welt()->naechstes(kit));
                                                                 */
                                                                 
                                                                 glDisable(GL_POLYGON_OFFSET_FILL);
                                                                 glShadeModel(GL_SMOOTH);
                                                                /* gra->polygonverschiebung(false);//glDisable(GL_POLYGON_OFFSET_FILL);
                                                                 gra->beleuchtungrund();//glShadeModel(GL_SMOOTH);*/
                                                                };
                                                                //---------------------------------3. pass : hell zeichnen  --------------------------------------------
                                                                glDepthFunc(GL_EQUAL);
                                                                glEnable(GL_BLEND);
                                                                glBlendFunc(GL_ONE,GL_ONE);
                                                                glEnable(GL_LIGHT0);
                                                                glEnable(GL_LIGHTING);
                                                                glStencilFunc(GL_EQUAL,0,~0);
                                                                glEnable(GL_CULL_FACE);
                                                                glEnable(GL_STENCIL_TEST);
                                                                glEnable(GL_DEPTH_TEST);
                                                                glEnable(GL_TEXTURE_2D);
                                                                glStencilOp(GL_KEEP,GL_KEEP,GL_KEEP);
                                                                glColorMask(1,1,1,1);
                                                                glDepthMask(1);
                                                                /*
                                                                gra->tiefenbufferkonditiongleich();//glDepthFunc(GL_EQUAL);
                                                                gra->transparenz(true);//glEnable(GL_BLEND);
                                                                gra->transparenzadditiv();//glBlendFunc(GL_ONE,GL_ONE);
                                                                gra->licht(0,true);//glEnable(GL_LIGHT0);
                                                                gra->beleuchtung(true);//glEnable(GL_LIGHTING);
                                                                gra->schablonenbufferkonditiongleich(0,~0);//glStencilFunc(GL_EQUAL,0,~0);
                                                                
                                                                gra->ausschussflaeche(true);//glEnable(GL_CULL_FACE);
                                                                gra->schablonenbufferkondition(true);//glEnable(GL_STENCIL_TEST);
                                                                gra->tiefenbufferkondition(true);//glEnable(GL_DEPTH_TEST);
                                                                gra->textur(true);//glEnable(GL_TEXTURE_2D);
                                                                gra->schablonenbufferoperation(0,0,0);//glStencilOp(GL_KEEP,GL_KEEP,GL_KEEP);
                                                                gra->anzeigebufferschreiben(true);//glColorMask(1,1,1,1);
                                                                gra->tiefenbufferschreiben(true);//glDepthMask(1);          
                                                                */ 
                                                                lit->binden(gra,0);
                                                               // glClear(GL_COLOR_BUFFER_BIT);
                                                                //-------------------- kugeln zeichnen -------------------------------------
                                                                if(pzone->welt()->anfang(kit))do{
                                                                 kit->zeichnen(gra);
                                                                }while(pzone->welt()->naechstes(kit));
                                                                gra->transparenz(true);//glEnable(GL_BLEND);
                                                                gra->beleuchtung(true);//glEnable(GL_LIGHTING);
                                                                //------------- externe zeichnen (polygonale sichtbarkeit 1.greades --------
                                                                if(pvisibilityextern.anfang(wit))do{
                                                                 zeichnenadditiv(gra,cam,wit->objekt(),zyklus,is);
                                                                }while(pvisibilityextern.naechstes(wit));
                                                                //--------------- die statischen, internen der sichtbarkeit 1. grades zeichnen ---
                                                                if(pvisibilityintern.anfang(wit))do{
                                                                 zeichnenadditiv(gra,cam,wit->objekt(),zyklus,is);
                                                                }while(pvisibilityintern.naechstes(wit));
                                                                //--------------- die dynamisch internen der sektorsichtbarkeit 1.grades zeichnen
                                                                if(pvisibilitysector.anfang(sit))do{
                                                                 if(sit->objekt()->internepolygonedynamisch()->anfang(wit))do{
                                                                  zeichnenadditiv(gra,cam,wit->objekt(),zyklus,is);
                                                                 }while(sit->objekt()->internepolygonedynamisch()->naechstes(wit));
                                                                }while(pvisibilitysector.naechstes(sit));
                                                                //------------------- implizite zeichnen ---------------------------------
                                                                if(anfang(pit))do{
                                                                 if(pit->portal()==false) zeichnenadditiv(gra,cam,pit->polygon(),zyklus,is);
                                                                }while(naechstes(pit));
                                                                //-------------------- die internen von diesem sektor zeichnen ------------
                                                                if(pinternstatisch.anfang(wit))do{
                                                                 zeichnenadditiv(gra,cam,wit->objekt(),zyklus,is);
                                                                }while(pinternstatisch.naechstes(wit));
                                                                if(pinterndynamisch.anfang(wit))do{
                                                                 zeichnenadditiv(gra,cam,wit->objekt(),zyklus,is);
                                                                }while(pinterndynamisch.naechstes(wit));
 };
 void _sektor::zeichnensubtraktiv(_grafik*gra,_kamera<_tg>*cam,_licht<_tg,_to>*lit,unsigned int is){
                                                                _listenknoten<_schatten<_tg,_to> >*schit;
                                                                _kugel*kit;
                                                                unsigned int zyklus=pzone->welt()->zyklus();
                                                                //------------- 2. PASS : SCHATTENVOLUMEN IN DEN STENCIL BUFFER SCHREIBEN ----------------------------------------------
                                                                if(lit->_liste<_schatten<_tg,_to> >::anfang(schit)){
                                                                 gra->schablonenbufferloeschen();//glClear(GL_STENCIL_BUFFER_BIT);
                                                                 gra->tiefenbufferkonditionkleiner();//glDepthFunc(GL_LESS);
                                                                 gra->polygonverschiebung(true);//glEnable(GL_POLYGON_OFFSET_FILL);
                                                                 gra->polygonverschiebung(0.1,10);//glPolygonOffset(0.1,10);	
                                                                 gra->textur(false);//glDisable(GL_TEXTURE_2D);
                                                                 gra->anzeigebufferschreiben(false);//glColorMask(0,0,0,0);
                                                                 gra->tiefenbufferschreiben(false);//glDepthMask(0);
                                                                 gra->schablonenbufferkondition(true);//glEnable(GL_STENCIL_TEST);
                                                                 gra->ausschussflaeche(true);//glEnable(GL_CULL_FACE);
                                                                 gra->ausschussflaechefront();//glCullFace(GL_FRONT);
                                                                 gra->beleuchtungflach();//glShadeModel(GL_FLAT);
                                                                 gra->schablonenbufferkonditionimmer(0,0xff);//glStencilFunc(GL_ALWAYS,0,0xff);
                                                                 gra->schablonenbufferschreiben(true);//glStencilMask(~0);
                                                                 gra->schablonenbufferoperation(0,1,0);//glStencilOp(GL_KEEP,GL_INCR,GL_KEEP);
                                                                 //---------zur kamera backfaced schattenpolygone zeichnen
                                                                 if(lit->_liste<_schatten<_tg,_to> >::anfang(schit))do{
                                                                  schit->objekt()->zeichnen(gra);
                                                                 }while(lit->_liste<_schatten<_tg,_to> >::naechstes(schit));
                                                                 //---------zur kamera frontfaced schattenpolygone zeichnen
			                                                     gra->ausschussflaecherueck();//glCullFace(GL_BACK);
                                                      		     gra->schablonenbufferkonditionimmer(0x0,0xff);//glStencilFunc(GL_ALWAYS, 0x0, 0xff);
			                                                     gra->schablonenbufferoperation(0,-1,0);//glStencilOp(GL_KEEP,GL_DECR,GL_KEEP);
                                                                 if(lit->_liste<_schatten<_tg,_to> >::anfang(schit))do{
                                                                  schit->objekt()->zeichnen(gra);
                                                                 }while(lit->_liste<_schatten<_tg,_to> >::naechstes(schit));
                                                                 gra->polygonverschiebung(false);//glDisable(GL_POLYGON_OFFSET_FILL);
                                                                 gra->beleuchtungrund();//glShadeModel(GL_SMOOTH);
                                                                 //---------------------------------3. pass : dunkles rechteck zeichnen --------------------------------------------
                                                                 gra->tiefenbufferkonditiongleich();//glDepthFunc(GL_EQUAL);
                                                                 gra->transparenz(true);//glEnable(GL_BLEND);
                                                                 gra->transparenzadditiv();//glBlendFunc(GL_ONE,GL_ONE);
                                                                 gra->licht(0,true);//glEnable(GL_LIGHT0);
                                                                 gra->beleuchtung(false);//glDisable(GL_LIGHTING);
                                                                 gra->schablonenbufferkonditionungleich(0,~0);//glStencilFunc(GL_NOTEQUAL,0,~0);
                                                                 gra->textur(false);//glDisable(GL_TEXTURE_2D);
                                                                 gra->ausschussflaeche(true);//glEnable(GL_CULL_FACE);
                                                                 gra->schablonenbufferkondition(true);//glEnable(GL_STENCIL_TEST);
                                                                 gra->tiefenbufferkondition(false);//glDisable(GL_DEPTH_TEST);
                                                                 gra->schablonenbufferoperation(0,0,0);//glStencilOp(GL_KEEP,GL_KEEP,GL_KEEP);
                                                                 gra->anzeigebufferschreiben(true);//glColorMask(1,1,1,1);
                                                                 gra->tiefenbufferschreiben(true);//glDepthMask(1);           
	                                                             gra->tiefenbufferkondition(false);//glDisable(GL_DEPTH_TEST);
	                                                             gra->transparenz(true);//glEnable(GL_BLEND);
 	                                                             gra->transparenzmultiplikativ();//glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	                                                             gra->ausschussflaeche(false);//glDisable(GL_CULL_FACE);
	                                                             gra->beleuchtung(false);//glDisable(GL_LIGHTING);
	                                                             _to dd=_to(lit->intensitaetopazitaet())/_to(pow((*cam-lit->ort()).laenge(),2));
	                                                             if(dd>lit->limitopazitaet()) dd=lit->limitopazitaet();
	                                                             _vektor4<_to> col( lit->farbeopazitaet()[0],lit->farbeopazitaet()[1],lit->farbeopazitaet()[2],dd);
	                                                            
                                                                 gra->vollbild(col);
	                                                             
	                                                             gra->tiefenbufferkondition(true);//glEnable(GL_DEPTH_TEST);
	                                                             gra->beleuchtung(true);//glEnable(GL_LIGHTING);
	                                                             gra->ausschussflaeche(true);//glEnable(GL_CULL_FACE);
                                                                 gra->textur(true);//glEnable(GL_TEXTURE_2D);
                                                                 gra->transparenz(false);//glDisable(GL_BLEND); 
	                                                             gra->transparenzadditiv();//glBlendFunc(GL_ONE,GL_ONE);
                                                                };
                                                                
                                                                
                                                                
                                                                //-----!!!!!!!!!!!!!!!!!!!!-- kugeln zeichnen --!!!!!!!!!!!!---- gehört eigentlich nicht hier hin !---------------
                                                                gra->tiefenbufferkondition(true);//glEnable(GL_DEPTH_TEST);
                                                                gra->transparenz(true);//glEnable(GL_BLEND);
                                                                lit->binden(gra,0);
                                                                gra->beleuchtung(true);//glEnable(GL_LIGHTING);
                                                                gra->licht(0,true);//glEnable(GL_LIGHT0);
                                                                gra->schablonenbufferkonditiongleich(0,~0);//glStencilFunc(GL_EQUAL,0,~0);
                                                                if(pzone->welt()->anfang(kit))do{
                                                                 kit->zeichnen(gra);
                                                                }while(pzone->welt()->naechstes(kit));
                                                                gra->schablonenbufferkondition(false);//glDisable(GL_STENCIL_TEST);
                                                                gra->beleuchtung(false);//glDisable(GL_LIGHTING);
                                                                gra->licht(0,false);//glDisable(GL_LIGHT0);
                                                                gra->transparenz(true);//glEnable(GL_BLEND);
 };
 /*
 
 void _sektor::clearoverlayedportals(){
                                                                //wenn im sektor portale, vorliegen, die übereinanderliegen, 
                                                                //dann werden portale so gelöscht, dass nur eines 
                                                                //an der stelle übrigbleibt
                                                                _polygon*pit;
                                                                _liste<_vektor<_tg> > lv;
                                                                _listenknoten<_vektor<_tg> >*vit;
                                                                _vektor<_tg>*o;
                                                                _vektor<_tg> m;
                                                                _vektor<_tg> h;
                                                                bool exist;
                                                                //---------------------------
                                                                if(anfang(pit))do{
                                                                 if(pit->portal()==true){
                                                                  m=pit->mitte();
                                                                  exist=false;
                                                                  if(lv.anfang(vit))do{
                                                                   h=*vit->objekt() - m;
                                                                   if(h.laenge()<(nahenull*4)) exist=true;
                                                                  }while(lv.naechstes(vit));
                                                                  if(exist){
                                                                   pit->loeschmarkierung(true);
                                                                  }else{
                                                                   o=new _vektor<_tg>(m);
                                                                   lv.einhaengen(o);
                                                                  };
                                                                 };
                                                                }while(naechstes(pit));
                                                                _listebasis<_polygon >::loeschenmarkiert();
                                                                lv.loeschen();
 };
 */
 
 void _sektor::loeschenvertexnichtportal(){
                                                                _polygon*pit;
                                                                //---------------------------
                                                                if(anfang(pit))do{
                                                                 if(pit->portal()==false) pit->_listebasis<_vertex >::loeschen();
                                                                }while(naechstes(pit));
 };
 
 void _sektor::erzeugenvertexlicht(){
                                                                //alle internen und exteren weltpoly 
                                                                //mit den lichtern des sektors bestrahlen
                                                                _polygon*pit;
                                                                _listenknoten< ::_polygon >*wit;
                                                                ::_polygon*poly;
                                                                //--------------------------------------------
                                                               // if(anfang(lit)){
                                                                 /*if(anfang(pit))do{
                                                                  if(pit->portal()==false) {
                                                                   pit->polygon()->markierung(0);
                                                                  };
                                                                 }while(naechstes(pit));
                                                                 */
                                                                 /*if(pvisibilityextern.anfang(wit))do{
                                                                  wit->objekt()->markierung(0);
                                                                 }while(pvisibilityextern.naechstes(wit));*/
                                                                 //interne bestrahlung
                                                                 if(anfang(pit))do{
                                                                  if(pit->portal()==false) {
                                                                   poly=pit->polygon();
                                                                   
                                                                   if(poly->markierung()==1){
                                                                    erzeugenvertexlicht(poly);
                                                                    poly->markierung(0);
                                                                   };
                                                                  };
                                                                 }while(naechstes(pit));
                                                                 //externe bestrahlung
                                                                 if(pvisibilityextern.anfang(wit))do{
                                                                  poly=wit->objekt();
                                                                  if(poly->markierung()==1){
                                                                   erzeugenvertexlicht(poly);
                                                                   poly->markierung(0); 
                                                                  };
                                                                 }while(pvisibilityextern.naechstes(wit));
                                                              //  };
 };
 
 void _sektor::erzeugenvertexlicht(::_polygon*poly){
                                                                //funktion führt bestrahlung aus
                                                                _licht<_tg,_to>*lit;
                                                                if((poly->verwendentexturdynamisch()==false)&&(poly->aufgehellt()==false)){
                                                                 if(anfang(lit))do{
																  erzeugenvertexlicht(poly,lit);
                                                                 }while(naechstes(lit));
                                                                 _listenknoten<_sektor>*lnsit;
                                                                 if(pvisibilitysector.anfang(lnsit))do{
                                                                  if(lnsit->objekt()->anfang(lit))do{
																   erzeugenvertexlicht(poly,lit);
                                                                  }while(lnsit->objekt()->naechstes(lit));
                                                                 }while(pvisibilitysector.naechstes(lnsit));
                                                                };
 };
 void _sektor::erzeugenvertexlicht(::_polygon*poly,_licht<_tg,_to>*lit){
                                                                _vektor3<_tg> d;
                                                                _vektor3<_tg> dn;
                                                                _vektor3<_to> c;
                                                                _vektor4<_to> c4;
                                                                ::_vertex*vit;
                                                                _verbindervertexpolygon*vcp;
                                                                _listenknoten<::_vertex>*lnvit;
                                                                _tg sp;
                                                                //-------------------- 
                                                                iterierenliste(poly,lnvit,
                                                                 vit=lnvit->objekt();
                                                                 vcp=static_cast<_verbindervertexpolygon*>(lnvit);
                                                                 //  vit=poly->vertex();
                                                                 // if(vit)do{
                                                                 //  vcp=vit->connector(poly);
                                                                   d=vit->ort()-lit->ort();
                                                                   dn=d;
                                                                   dn.normalisieren();
                                                                   sp=dn*poly->normale();
                                                                   if(sp < 0){
                                                                    c=lit->farbedynamisch();
                                                                    c*=_to(-sp)*lit->intensitaetdynamisch()/_to(pow((_to(d.laenge())+1),1.3f));
                                                                    //c4=c;
                                                                    c4.setzenkomponente(0,c[0]);
                                                                    c4.setzenkomponente(1,c[1]);
                                                                    c4.setzenkomponente(2,c[2]);
                                                                    c4.setzenkomponente(3,0);
                                                                    vcp->farbe(vcp->farbe()+c4);
                                                                   };
                                                                   c4=vcp->farbe();
                                                                   c4.begrenzen(0,1);
                                                                   vcp->farbe(c4);
                                                                 );
                                                                 //  vit=vit->naechstes(poly);
                                                                 // }while(vit!=poly->vertex());
 };
 void _sektor::erzeugenbaum(const _tg maxobj,const _tg minkant){
                                                                _listenknoten< ::_polygon>*lnpit;
                                                                _polygon*pit;
                                                                _tg x0,x1,y0,y1,z0,z1;
                                                                _tg wx0,wx1,wy0,wy1,wz0,wz1;                                                                
                                                                //--------------------------------
                                                                _baumoctal< ::_polygon,_tg>::aushaengen();
                                                                _baumoctal< ::_polygon,_tg>::maximalobjektanzahl(((unsigned int)(maxobj)));
                                                                _baumoctal< ::_polygon,_tg>::minimalwuerfelkante(0,minkant);
                                                                _baumoctal< ::_polygon,_tg>::minimalwuerfelkante(1,minkant);
                                                                _baumoctal< ::_polygon,_tg>::minimalwuerfelkante(2,minkant);                                                                
                                                                wx0=-100;
                                                                wx1=+100;
                                                                wy0=-100;
                                                                wy1=+100;
                                                                wz0=-100;
                                                                wz1=+100;
                                                                bool init=true;
                                                                /*
                                                                //hier wird die baumabmessung durch die interenne polygone bestimmt , nicht gut
                                                                if(internepolygone()->anfang(lnpit))do{
                                                                 if(lnpit->objekt()->markierung()==0){
                                                                  lnpit->objekt()->markierung(1);
                                                                  lnpit->objekt()->umgrenzungsquader(x0,x1,y0,y1,z0,z1);
                                                                  if(init){
                                                                   wx0=x0;
                                                                   wx1=x1;
                                                                   wy0=y0;
                                                                   wy1=y1;
                                                                   wz0=z0;
                                                                   wz1=z1;
                                                                   init=false;
                                                                  }else{
                                                                   if(x0<wx0) wx0=x0;
                                                                   if(x1>wx1) wx1=x1;
                                                                   if(y0<wy0) wy0=y0;
                                                                   if(y1>wy1) wy1=y1;
                                                                   if(z0<wz0) wz0=z0;
                                                                   if(z1>wz1) wz1=z1;
                                                                  };
                                                                 };
                                                                }while(internepolygone()->naechstes(lnpit));
                                                                */
                                                                //baumabmessung durch die sektorpolygone bestimmen
                                                                if(anfang(pit))do{
                                                                 if(pit->portal()){
                                                                  pit->umgrenzungsquader(x0,x1,y0,y1,z0,z1);
                                                                 }else{
                                                                  pit->polygon()->umgrenzungsquader(x0,x1,y0,y1,z0,z1);
                                                                 };
                                                                 if(init){
                                                                  wx0=x0;
                                                                  wx1=x1;
                                                                  wy0=y0;
                                                                  wy1=y1;
                                                                  wz0=z0;
                                                                  wz1=z1;
                                                                  init=false;
                                                                 }else{
                                                                  if(x0<wx0) wx0=x0;
                                                                  if(x1>wx1) wx1=x1;
                                                                  if(y0<wy0) wy0=y0;
                                                                  if(y1>wy1) wy1=y1;
                                                                  if(z0<wz0) wz0=z0;
                                                                  if(z1>wz1) wz1=z1;
                                                                 };
                                                                }while(naechstes(pit));
                                                                _baumoctal< ::_polygon,_tg>::setzenhauptwuerfel(wx0,wx1,wy0,wy1,wz0,wz1);
                                                                //und schon mal das einfügen was drin ist (statische und dynamische)
                                                                if(internepolygonestatisch()->anfang(lnpit))do{
                                                                 lnpit->objekt()->markierung(1);
                                                                }while(internepolygonestatisch()->naechstes(lnpit));
                                                                if(internepolygonestatisch()->anfang(lnpit))do{
                                                                 if(lnpit->objekt()->markierung()==1){
                                                                  lnpit->objekt()->markierung(0);
                                                                  lnpit->objekt()->umgrenzungsquader(x0,x1,y0,y1,z0,z1);
                                                                  _baumoctal< ::_polygon,_tg>::einhaengen(lnpit->objekt(),x0,x1,y0,y1,z0,z1);
                                                                 };
                                                                }while(internepolygonestatisch()->naechstes(lnpit));
                                                                if(internepolygonedynamisch()->anfang(lnpit))do{
                                                                 lnpit->objekt()->markierung(1);
                                                                }while(internepolygonedynamisch()->naechstes(lnpit));
                                                                if(internepolygonedynamisch()->anfang(lnpit))do{
                                                                 if(lnpit->objekt()->markierung()==1){
                                                                  lnpit->objekt()->markierung(0);
                                                                  lnpit->objekt()->umgrenzungsquader(x0,x1,y0,y1,z0,z1);
                                                                  _baumoctal< ::_polygon,_tg>::einhaengen(lnpit->objekt(),x0,x1,y0,y1,z0,z1);
                                                                 };
                                                                }while(internepolygonedynamisch()->naechstes(lnpit));
 };
 
 
 
 /*
 
 
 
 
 void _sektor::multiplyvertexlight(){
                                                                //alle internen und exteren weltpoly 
                                                                //iteren , deren vcp-lichtinfo mit 
                                                                //ihrer farbew multiplizieren
                                                                _polygon*pit;
                                                                _listenknoten< ::_polygon >*wit;
                                                                ::_polygon*poly;
                                                                //--------------------------------------------
                                                                if(anfang(pit))do{
                                                                 if(pit->portal()==false) {
                                                                  pit->polygon()->markierung(0);
                                                                 };
                                                                }while(naechstes(pit));
                                                                if(pvisibilityextern.anfang(wit))do{
                                                                 wit->objekt()->markierung(0);
                                                                }while(pvisibilityextern.naechstes(wit));
                                                                //interne multiplikation
                                                                if(anfang(pit))do{
                                                                 if(pit->portal()==false) {
                                                                  poly=pit->polygon();
                                                                  if(poly->markierung()==0){
                                                                   multiplyvertexlight(poly);
                                                                   poly->markierung(1);
                                                                  };
                                                                 };
                                                                }while(naechstes(pit));
                                                                //externe mulitplikation
                                                                if(pvisibilityextern.anfang(wit))do{
                                                                 poly=wit->objekt();
                                                                 if(poly->markierung()==0){
                                                                  multiplyvertexlight(poly);
                                                                  poly->markierung(1); 
                                                                 };
                                                                }while(pvisibilityextern.naechstes(wit));
 };
 
 
 void _sektor::multiplyvertexlight(::_polygon*poly){
                                                                //funktion führt multiplikation mit polyfarbe aus
                                                                _vektor4<_to> c;
                                                                _vektor4<_to> p;
                                                                ::_vertex*vit;
                                                                _verbindervertexpolygon*vcp;
                                                                _to x0;
                                                                _to x1;
                                                                _to x2;
                                                                //-------------------------------------------
                                                                vit=poly->vertex();
                                                                if(vit)do{
                                                                 vcp=vit->connector(poly);
                                                                 p=poly->farbe();
                                                                 c=vcp->farbe();
                                                                 L->schreiben("C[0]=",c[0]);
                                                                 L->schreiben("C[1]=",c[1]);
                                                                 L->schreiben("C[2]=",c[2]);
                                                                 x0=c[0]*p[0];
                                                                 x1=c[1]*p[1];
                                                                 x2=c[2]*p[2];
                                                                 L->schreiben("xC[0]*P[0]=",x0);
                                                                 L->schreiben("xC[0]*P[0]=",x1);
                                                                 L->schreiben("xC[0]*P[0]=",x2);
                                                                 c.setzen(x0,x1,x2);
                                                                 c.begrenzen(0,1);
                                                                 vcp->farbe(c);
                                                                 vit=vit->naechstes(poly);
                                                                }while(vit!=poly->vertex());
 };

 
 
 
 
 
 
*/ 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 //------------------------------------------------------------- sichtbarkeitsberechnung ----------------------------------------------------------------------------- 
 
 void _sektor::erzeugensichtbarkeit(){
                                                                //hauptsteuerfunktion zur sichtbarkeitsbestimmung
                                                                _sektor*sit;
                                                                _listenknoten<_sektor >*lsit;
                                                               
                                                                _polygon*pit;
                                                                _listenknoten<_polygon >*lpit;
                                                                _polygon*piit;
                                                                _listenknoten< ::_polygon >*zpit;
                                                                _listenknoten< ::_polygon >*vispit;
                                                                bool isextern;
                                                                bool exist;
                                                                bool nachbar;
                                                                bool isvisiblebysector;
                                                                //***********DEBUG**********
                                                                _liste< _polygon > visext;
                                                                _vektor4<_to> col;
                                                                _polygon*dbp;
                                                                ///*************************
                                                                //---------------------------
                                                                aktualisieren();
                                                                //***********DEBUG**********
                                                                visualisieren();
                                                                //**************************
                                                                //------------------------------------------------sichtbarkeit von sektoren ermitteln ----------------
                                                                //pvisibilitysector.aushaengen();
                                                                //direkt benachbarte sektoren ermitteln
                                                                if(pzone->anfang(sit))do{
                                                                 if(sit!=this){
                                                                  nachbar=false;
                                                                  if(anfang(pit))do{
                                                                   if(pit->portal()){
                                                                    if(pit->anfang(lpit))do{
                                                                     if(lpit->objekt()->sektor()==sit) nachbar=true;
                                                                    }while((pit->naechstes(lpit))&&(nachbar==false));
                                                                   };
                                                                  }while((naechstes(pit))&&(nachbar==false));
                                                                  if(nachbar){
                                                                   pvisibilitysector.einhaengenunredundant(sit);
                                                                   sit->sichtbarkeitsektor()->einhaengenunredundant(this);
                                                                  };
                                                                 };
                                                                }while(pzone->naechstes(sit));
                                                                //sonstige sektoren mit portal-portal-spannvolumen prüfen
                                                                if(pzone->anfang(sit))do{
                                                                 if(sit!=this){
                                                                  exist=false;
                                                                  if(pvisibilitysector.anfang(lsit))do{
                                                                   if(sit==lsit->objekt()) exist=true;
                                                                  }while((pvisibilitysector.naechstes(lsit))&&(exist==false));
                                                                  if(exist==false){
                                                                   if(istsichtbarsektor(sit)) {
                                                                    pvisibilitysector.einhaengenunredundant(sit);
                                                                    sit->sichtbarkeitsektor()->einhaengenunredundant(this);
                                                                   };
                                                                  };
                                                                 };
                                                                }while(pzone->naechstes(sit));
                                                                //**************** DEBUG ****************
                                                              /*  col.setzen(0,0.6,1);
                                                                visualisieren();
                                                                if(pvisibilitysector.anfang(lsit))do{
                                                                 lsit->objekt()->visualisieren(col);
                                                                }while(pvisibilitysector.naechstes(lsit));
                                                                pzone->debuganimation();
                                                                if(pvisibilitysector.anfang(lsit))do{
                                                                 lsit->objekt()->unvisualisieren();
                                                                }while(pvisibilitysector.naechstes(lsit));
                                                                unvisualisieren();*/
                                                                //***************************************
                                                                //------------------------------------------------sichtbarkeit von weltpolygonen ermitteln -----------
                                                            //    pvisibilityextern.aushaengen();
                                                                if(anfang(pit))do{
                                                                 if(pit->portal()==true){
                                                                  if(pzone->anfang(zpit))do{
                                                                   isvisiblebysector=false;
                                                                   if(pvisibilitysector.anfang(lsit))do{
                                                                    if(lsit->objekt()->anfang(piit))do{
                                                                     if(piit->portal()==false){
                                                                      if(zpit->objekt()==piit->polygon()) isvisiblebysector=true;
                                                                     };
                                                                    }while((lsit->objekt()->naechstes(piit))&&(isvisiblebysector==false));
                                                                   }while((pvisibilitysector.naechstes(lsit))&&(isvisiblebysector==false));
                                                                   //isvisiblebysector=true;//!!!!!!!!!!!!!!!
                                                                   if(isvisiblebysector){
                                                                    isextern=true;
                                                                    if(anfang(piit))do{
                                                                     if(piit->portal()==false) if(piit->polygon()==zpit->objekt()) isextern=false;
                                                                    }while((naechstes(piit))&&(isextern==true));
                                                                    if(isextern){
                                                                     exist=false;
                                                                     if(pvisibilityextern.anfang(vispit))do{
                                                                      if(vispit->objekt()==zpit->objekt()) exist=true;
                                                                     }while( (pvisibilityextern.naechstes(vispit)) && (exist==false) );
                                                                     if(exist==false) {
                                                                      if(istsichtbar(pit,zpit->objekt())) {
                                                                       pvisibilityextern.einhaengen(zpit->objekt());
                                                                       //********** DEBUG ***********
                                                                       if(pzone->welt()->debuggensichtbarkeit()){
                                                                        if(zpit->objekt()->debuggen()){
                                                                         col.setzen(0.1f,0.95f,0.2f,0);
                                                                         if(pzone->debugschirm()) pzone->debugschirm()->schreiben("ist sichtbar",col);
                                                                         pzone->debuganimation();
                                                                        };
                                                                       };
                                                                       //****************************
                                                                       //exist=false;
                                                                       //if(pvisibilityextern.anfang(vispit))do{
                                                                       // if(vispit->objekt()==zpit->objekt()) exist=true;
                                                                       //}while( (pvisibilityextern.naechstes(vispit)) && (exist==false) );
                                                                       //if(exist==false) {
                                                                       //pvisibilityextern.einhaengen(zpit->objekt());
                                                                       //********** DEBUG ***********
                                                                       if(pzone->welt()->debuggensichtbarkeit()){
                                                                        dbp=new _polygon(zpit->objekt());
                                                                        col.setzen(1,0,1,0);
                                                                        dbp->visualisieren(pzone,col);
                                                                        visext.einhaengen(dbp);
                                                                       };
                                                                       //****************************
                                                                       //};
                                                                      }else{//ist nicht sichtbar
                                                                       //********** DEBUG ***********
                                                                       if(pzone->welt()->debuggensichtbarkeit()){
                                                                        if(zpit->objekt()->debuggen()){
                                                                         col.setzen(0.8f,0.95f,0.2f,0);
                                                                         if(pzone->debugschirm()) pzone->debugschirm()->schreiben("ist nicht sichtbar",col);
                                                                         pzone->debuganimation();
                                                                        };
                                                                       };
                                                                       //****************************
                                                                      };
                                                                     }//existiert noch nicht
                                                                    };//ist extern
                                                                   };//sichtbar durch sektorsichtbarkeit
                                                                  }while(pzone->naechstes(zpit));
                                                                 };//pit ost portal
                                                                }while(naechstes(pit));
                                                                //***********DEBUG**********
                                                                unvisualisieren();
                                                                visext.loeschen();
                                                                //**************************
                                                                //---------------- sichtbarkeiten der internen,statischen polygon ermitteln -------------------------------
                                                                if(anfang(pit))do{
                                                                 if(pit->portal()){
                                                                  if(pvisibilitysector.anfang(lsit))do{
                                                                   sit=lsit->objekt();
                                                                   if(sit->pinternstatisch.anfang(vispit))do{
                                                                    bool exist=false;
                                                                    _listenknoten< ::_polygon>*lnpit;
                                                                    if(pinternstatisch.anfang(lnpit))do{
                                                                     if(vispit->objekt()==lnpit->objekt()) exist=true;
                                                                    }while((pinternstatisch.naechstes(lnpit))&&(exist==false));
                                                                    if(exist==false){
                                                                     if(istsichtbar(pit,vispit->objekt())) {
                                                                      pvisibilityintern.einhaengenunredundant(vispit->objekt()); 
                                                                     };
                                                                    };
                                                                   }while(sit->pinternstatisch.naechstes(vispit));
                                                                  }while(pvisibilitysector.naechstes(lsit));
                                                                 };
                                                                }while(naechstes(pit));
 };
 void _sektor::erzeugensichtbarkeit2tergrad(){ 
                                                                _listenknoten<_sektor>*lsit;
                                                                _sektor*sit;
                                                                 //---------------- sichtbarkeiten 2. grades zwischen sektoren ermitteln ----------------------
                                                                 pvisibilitysector2tergrad.aushaengen();
                                                                if(pvisibilitysector.anfang(lsit))do{
                                                                 sit=lsit->objekt();
                                                                 pvisibilitysector2tergrad.einhaengenunredundant(sit);
                                                                 _listenknoten<_sektor>*lsiit;
                                                                 if(sit->pvisibilitysector.anfang(lsiit))do{
                                                                  if(lsiit->objekt()!=this) pvisibilitysector2tergrad.einhaengenunredundant(lsiit->objekt());
                                                                 }while(sit->pvisibilitysector.naechstes(lsiit));
                                                                }while(pvisibilitysector.naechstes(lsit));
};
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
//                                                              sektor-sichtbarkeitsberechnung                                                               
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
 bool _sektor::istsichtbarsektor(_partition::_sektor*sektor){
                                                                //ist der sektor sektor vom this-sektor aus sichtbar
                                                                //jedes this-portal mit jedem sektor-portal prüfen
                                                                bool visible;
                                                                _polygon*pthis;
                                                                _polygon*pother;
                                                                //-------------
                                                                visible=false;
                                                                if(anfang(pthis))do{
                                                                 if(pthis->portal()){
                                                                  if(sektor->anfang(pother))do{
                                                                   if(pother->portal()){
                                                                    if(istsichtbarsektor(pthis,pother)) {
                                                                     visible=true;
                                                                    };
                                                                   };
                                                                  }while((sektor->naechstes(pother))&&(visible==false));
                                                                 };
                                                                }while((naechstes(pthis))&&(visible==false));
                                                                if(visible){
                                                                  if(pzone->debugschirm()) pzone->debugschirm()->schreiben("Sektor wurde als sichtbar erkannt.",_vektor4<_to>(1,1,1,1));
                                                                 }else{ 
                                                                  if(pzone->debugschirm()) pzone->debugschirm()->schreiben("Sektor wurde als NICHT sichtbar erkannt.",_vektor4<_to>(1,1,1,1));
                                                                 };
                                                                return(visible);
 };
 bool _sektor::istsichtbarsektor(_partition::_polygon*portalthis,_partition::_polygon*portalother){
                                                                //ist das portalother vom portalthis aus sichtbar?r
                                                                //ggf. portalother an portalthis abschneiden
                                                                bool visible;
                                                                bool frontfaced;
                                                                bool backfaced;
                                                                _vertex*vit;
                                                                _vektor3<_tg> v;
                                                                _tg D0;
                                                                _tg D1;
                                                                _tg D;
                                                                _vektor3<_tg> pm;
                                                                _vektor3<_tg> pp0;
                                                                _vektor3<_tg> pp1;
                                                                _vektor3<_tg> tn;//normale von portalthis
                                                                _vektor3<_tg> on;//normale von portalother
                                                                _vektor3<_tg> wm;
                                                                _vektor3<_tg> wp;
                                                                _vektor3<_tg> wp0;
                                                                _vektor3<_tg> wp1;
                                                                _vektor3<_tg> schnitt;
                                                                _vektor3<_tg> vektor;
                                                                _vektoranalysis3<_tg> V3;
                                                                _tg s;
                                                                _partition::_polygon*pother;
                                                                _partition::_polygon*frontpoly;
                                                                _partition::_polygon*backpoly;
                                                                //---------------
                                                                visible=true;
                                                                on=portalother->normalsector(portalother->sektor()->pmiddle);
                                                                //frontfaceprüfung
                                                                //prüfen, ob das portalother
                                                                //gütlig ist, bzw. prüfen ob es frontfaced ist
                                                                frontfaced=false;
                                                                backfaced=false;
                                                                if(portalthis->anfang(vit))do{
                                                                 v=portalother->mitte()-*vit;//wit=portalother->mitte();//->vertex();
                                                                 v.normalisieren();
                                                                 s=v*on;//welt->normale();
                                                                 if(s<-nahenull) frontfaced=true; else backfaced=true;
                                                                }while(portalthis->naechstes(vit));
                                                                if(frontfaced==true){
                                                                 //an der portalthis-ebene abschneiden
                                                                 //schnittgerade bestimmen und teilen aufrufen
                                                                 wm=portalother->mitte();
                                                                 wp0=portalother->polygon()->ebene(0);
                                                                 wp1=portalother->polygon()->ebene(1);
                                                                 pm=portalthis->mitte();
                                                                 tn=portalthis->normalsector(pmiddle);
                                                                 pp0=portalthis->polygon()->ebene(0);
                                                                 pp1=portalthis->polygon()->ebene(1);
                                                                 D0=V3.determinieren(pp0,pp1,-wp0);
                                                                 D1=V3.determinieren(pp0,pp1,-wp1);
                                                                 if(fabs(D0)>fabs(D1)){ 
                                                                  D=D0; 
                                                                  wp=wp0;
                                                                 }else{
                                                                  D=D1;
                                                                  wp=wp1;
                                                                 };
                                                                 if(fabs(D)>nahenull){
                                                                  //schräg
                                                                  s=V3.determinieren(pp0,pp1,wm-pm)/D;
                                                                  schnitt=wm+wp*s;
                                                                  vektor=tn%on;//welt->normale();
                                                                  vektor.normalisieren();
                                                                  pother=new _partition::_polygon(portalother);
                                                                  pother->teilen(schnitt,schnitt+vektor,tn,on,frontpoly,backpoly);
                                                                  delete pother;
                                                                  pother=0;
                                                                  if(frontpoly){
                                                                   visible=istsichtbarsektor(portalthis,tn,portalother,frontpoly,on,frontfaced&&backfaced);
                                                                  }else{
                                                                   visible=false;
                                                                  };
                                                                  if(backpoly){delete backpoly;backpoly=0;};
                                                                  if(frontpoly){delete frontpoly;frontpoly=0;};
                                                                 }else{
                                                                  //parallel
                                                                  //wm=pm+a*pnormalsector+b*pp0+c*pp1
                                                                  D=V3.determinieren(tn,pp0,pp1);
                                                                  if(D){
                                                                   s=V3.determinieren(wm-pm,pp0,pp1)/D;
                                                                   if(s<+nahenull) {
                                                                    //komplanar oder dahinter
                                                                    visible=false;
                                                                   }else{
                                                                    //parallel davor
                                                                    pother=new _partition::_polygon(portalother);
                                                                    visible=istsichtbarsektor(portalthis,tn,portalother,pother,on,false);
                                                                    delete pother;
                                                                    pother=0;
                                                                   };
                                                                  }else{
                                                                   //error
                                                                  }
                                                                 };
                                                                }else{
                                                                 visible=false;
                                                                };
                                                                return(visible);
 };
 bool _sektor::istsichtbarsektor(_partition::_polygon*portalthis,_vektor3<_tg> tn,_partition::_polygon*portalotherorg,_partition::_polygon*portalother,_vektor3<_tg> on,const bool multifaced){
 //bool _sektor::istsichtbarsektor(_partition::_polygon*portal,::_polygon*orgwelt,_partition::_polygon*welt,const bool multifaced){
                                                                //funktion stellt fest, ob das potentiell sichtbare polygon welt
                                                                //auch wirklich von portal aus sichtbar ist
                                                                //zunächst das portal poly
                                                                //so anpassen, dass bei multifaced welt-
                                                                //polygon, das portal an der welteben abgeschnitten wird
                                                                _partition::_polygon*frontpoly;
                                                                _partition::_polygon*backpoly;
                                                                bool visible;
                                                                _tg D0;
                                                                _tg D1;
                                                                _tg D,s;
                                                                _vektor3<_tg> pm;
                                                                _vektor3<_tg> pp0;
                                                                _vektor3<_tg> pp1;
                                                               // _vektor3<_tg> pn;
                                                                _vektor3<_tg> wm;
                                                                _vektor3<_tg> wp;
                                                                _vektor3<_tg> wp0;
                                                                _vektor3<_tg> wp1;
                                                                _vektoranalysis3<_tg> V3;
                                                                _vektor3<_tg> schnitt;
                                                                _vektor3<_tg> vektor;
                                                                //--------------
                                                                visible=false;
                                                                if(multifaced){
                                                                 wm=portalother->mitte();
                                                                 wp0=portalother->polygon()->ebene(0);
                                                                 wp1=portalother->polygon()->ebene(1);
                                                                 pm=portalthis->mitte();
                                                                 //pn=portalthis->normalsector(pmiddle);
                                                                 pp0=portalthis->polygon()->ebene(0);
                                                                 pp1=portalthis->polygon()->ebene(1);
                                                                 D0=V3.determinieren(pp0,pp1,-wp0);
                                                                 D1=V3.determinieren(pp0,pp1,-wp1);
                                                                 if(fabs(D0)>fabs(D1)){ 
                                                                  D=D0; 
                                                                  wp=wp0;
                                                                 }else{
                                                                  D=D1;
                                                                  wp=wp1;
                                                                 };
                                                                 if(fabs(D)>nahenull){
                                                                  s=V3.determinieren(pp0,pp1,wm-pm)/D;
                                                                  schnitt=wm+wp*s;
                                                                  vektor=tn%on;
                                                                  vektor.normalisieren();
                                                                  portalthis->teilen(schnitt,schnitt+vektor,on,tn,frontpoly,backpoly);
                                                                  if(frontpoly){
                                                                   visible=istsichtbarsektor(portalthis,frontpoly,tn,portalotherorg,portalother,on);
                                                                  }else{
                                                                   visible=false;
                                                                  };
                                                                  if(backpoly){delete backpoly;backpoly=0;};
                                                                  if(frontpoly){delete frontpoly;frontpoly=0;};
                                                                 }else{
                                                                  //error
                                                                 };
                                                                }else{//nicht multifaced, nur frontfaced
                                                                 visible=istsichtbarsektor(portalthis,portalthis,tn,portalotherorg,portalother,on);
                                                                };
                                                                return(visible);
 };
 bool _sektor::istsichtbarsektor(_partition::_polygon*portalthisorg,_partition::_polygon*portalthis,_vektor3<_tg> tn,_partition::_polygon*portalotherorg,_partition::_polygon*portalother,_vektor3<_tg> on){
                                                                //hier läuft die sichtbarkeitbestimmung an
                                                                //sichtbarkeitsvolumen werden angelegt und getestet
                                                                bool visible;
                                                                _sichtbarkeitsvolumen*vv;
                                                                _vektor3<_tg> h;
                                                                //_polygon*pit;
                                                                _liste<_sektor > targetsectors;
                                                                _liste<_polygon > lportalinput;
                                                                _liste<_polygon > lportaloutput;
                                                                _liste<_sektor > lsectorit;
                                                                _liste<_sektor > lsectorgesperrt;
                                                                _listenknoten<_polygon >*lnpit;
                                                                bool vvalid;
                                                                //--------------------------------
                                                                visible=false;
                                                                //sichtbarkeitsvolumen anlegen
                                                                //volumen sind nur dann gültig, wenn ihr 
                                                                //zentralvertex nicht in der anderes-ebene liegt
                                                                vvalid=true;
                                                                h=portalthis->mitte()-portalother->mitte();
                                                                if(h.laenge()<=nahenull){
                                                                 vvalid=false;
                                                                }else{
                                                                 h.normalisieren();
                                                                 if( fabs(h*on)<=nahenull ) vvalid=false;
                                                                };
                                                                if(vvalid) {
                                                                 vv=new _sichtbarkeitsvolumen(pzone,portalthis,tn,portalother,on);
                                                                 //******************** DEBUG **************************************************************************
                                                                 /*if(pzone->pdbcount>573){
                                                                  _sektor*sectorother=portalotherorg->sektor();
                                                                  _vektor4<_to> colore;
                                                                  colore.setzen(0.7,0.55,0.2,1);
                                                                  if(pzone->debugschirm()) pzone->debugschirm()->schreiben("PortalVolumen Nr.:",pzone->pdbcount,colore);
                                                                  _vektor4<_to> col;
                                                                  _vektor4<_to> colr;
                                                                  _vektor4<_to> coln;
                                                                  col.setzen(1,0.1,0.1,1);
                                                                  colr.setzen(0.23,0.2,0.8,1);
                                                                  coln.setzen(0,0.5,1,1);
                                                                  vv->visualisieren(coln,col,colr);
                                                                  sectorother->visualisieren(col);
                                                                  pzone->debuganimation();
                                                                  sectorother->unvisualisieren();
                                                                  //sectorother->visualisieren();
                                                                  //vv->unvisualisieren();
                                                                 };
                                                                 pzone->pdbcount++;*/
                                                                 //*****************************************************************************************************


                                                                 //if(pzone->anfang(sit))do{
                                                                 // if(sit!=this){
                                                                 //  stop=false;
                                                                 //  if(sit->anfang(pit))do{
                                                                 //   if(pit->portal()==false){
                                                                 //    if(pit->polygon()==orgwelt){
                                                                 //     targetsectors.einhaengenunredundant(sit);
                                                                 //     stop=true;
                                                                 //    };
                                                                 //  };
                                                                 //  }while((sit->naechstes(pit))&&(stop==false));
                                                                 // };
                                                                 //}while(pzone->naechstes(sit));
                                                                 //targetsector=sectorother;
                                                                 
                                                                 //******* DEBUG **********
                                                                 //if(targetsectors.anfang(lnsit))do{
                                                                 // lnsit->objekt()->visualisieren();
                                                                 //}while(targetsectors.naechstes(lnsit));
                                                                 //pzone->debuganimation();
                                                                 //if(targetsectors.anfang(lnsit))do{
                                                                 // lnsit->objekt()->unvisualisieren();
                                                                 //}while(targetsectors.naechstes(lnsit));
                                                                 //************************
                                                                 //hauptschleife
                                                                 //liste von portaliteratoren laufen lassen
                                                                 
                                                                 lsectorgesperrt.einhaengen(this);
                                                                 targetsectors.einhaengen(portalotherorg->sektor());
                                                                 //neue änderung : 20.09.2006:
                                                                 //starten mit der iteration des portalausgangs von orgportal
                                                                 if(portalthisorg->anfang(lnpit))do{
                                                                  if(lnpit->objekt()->sektor()->istsichtbarsektor(portalthisorg,portalotherorg,vv,&lsectorgesperrt)) {
                                                                   delete vv;     
                                                                   return(true);                                              
                                                                  };           
                                                                 }while(portalthisorg->naechstes(lnpit));
                                                                 delete vv;
                                                                };
                                                                return(false);
 };                                                                
  bool _sektor::istsichtbarsektor(_partition::_polygon*portalthis,_partition::_polygon*portalother,_sichtbarkeitsvolumen*vv,_liste<_sektor>*lsectorgesperrt){       
                                                                bool sichtbar=false;
                                                                //rekursive funktion, die sektoren abiteriert
                                                                //sichtbar ist der targetsektor dann, 
                                                                //wenn ein sektor erreicht wurde (this),
                                                                //der einen portalausgang hat, der das zielportal identifiziert
                                                                _polygon*pit;
                                                                _listenknoten<_polygon>*lnpit;
                                                                if(anfang(pit))do{
                                                                 if(pit->portal()){
                                                                  if(pit->anfang(lnpit))do{
                                                                   if(lnpit->objekt()==portalother) return(true);
                                                                  }while(pit->naechstes(lnpit));
                                                                 };
                                                                }while(naechstes(pit));
                                                                
                                                                
                                                                _listenknoten<_sektor>*lnsit;
                                                                lsectorgesperrt->einhaengenunredundant(this);
                                                                //ansonsten die portale dieses sektors itereieren
                                                                //den portal ausgang dieses sektors iterieren
                                                                //sperrung prüfen
                                                                _polygon*innenpoly0;
                                                                _polygon*innenpoly1;
                                                                _sichtbarkeitsvolumen*vv0;
                                                                _sichtbarkeitsvolumen*vv1;
                                                                _vektor3<_tg> n;
                                                                _vektor3<_tg> h;
                                                                bool gesperrt;
                                                                if(anfang(pit))do{
                                                                 if(pit->portal()){
                                                                  innenpoly0=vv->innerhalb(pit);
                                                                  if(innenpoly0){
                                                                  
                                                                  
                                                                   h=vv->ziel()->mitte()-innenpoly0->mitte();
                                                                   h.normalisieren();
                                                                   n=pit->normale();
                                                                   if((n*h)<0) n*=-1;
                                                                   vv0=new _sichtbarkeitsvolumen(pzone,innenpoly0,n,vv->ziel(),vv->zielnormale());
                                                                  
                                                                   if(pit->anfang(lnpit))do{
                                                                    gesperrt=false;
                                                                    if(lsectorgesperrt->anfang(lnsit))do{
                                                                     if(lnsit->objekt()==lnpit->objekt()->sektor()) gesperrt=true;
                                                                    }while((lsectorgesperrt->naechstes(lnsit))&&(gesperrt==false));
                                                                    if(gesperrt==false){
                                                                     innenpoly1=vv0->innerhalb(lnpit->objekt());
                                                                     if(innenpoly1){
                                                                     
                                                                      h=vv->ziel()->mitte()-innenpoly1->mitte();
                                                                      h.normalisieren();
                                                                      n=lnpit->objekt()->normale();
                                                                      if((n*h)<0) n*=-1;
                                                                      vv1=new _sichtbarkeitsvolumen(pzone,innenpoly1,n,vv->ziel(),vv->zielnormale());
                                                                     
                                                                      if(lnpit->objekt()->sektor()->istsichtbarsektor(portalthis,portalother,vv1,lsectorgesperrt)) sichtbar=true;
                                                                      
                                                                      delete vv1;
                                                                      delete innenpoly1;
                                                                      innenpoly1=0;
                                                                     };
                                                                    };
                                                                   }while((pit->naechstes(lnpit))&&(sichtbar==false));

                                                                   delete vv0;
                                                                   delete innenpoly0;
                                                                   innenpoly0=0; 
                                                                  };
                                                                 };
                                                                }while((naechstes(pit))&&(sichtbar==false));
                                                                return(sichtbar);
};
/*
                                                                 
                                                                 stop=false;
                                                                 lportalinput.einhaengen(portalthisorg);
                                                                 if(portalotherorg->anfang(lnpit))do{
                                                                  targetsectors.einhaengenunredundant(lnpit->objekt()->sektor());
                                                                 }while(portalotherorg->naechstes(lnpit));

                                                                 do{
                                                                  //-------------------------------------------------portaleingang in portalausgang übersetzen
                                                                  lportaloutput.aushaengen();
                                                                  if(lportalinput.anfang(lnpit))do{
                                                                   if(lnpit->objekt()->anfang(pnext))do{
                                                                    lportaloutput.einhaengenunredundant(pnext->objekt());
                                                                   }while(lnpit->objekt()->naechstes(pnext));
                                                                  }while(lportalinput.naechstes(lnpit));
                                                                  lportalinput.aushaengen();
                                                                  //-------------------------------------------------iterierte sektoren identifizieren 
                                                                  lsectorit.aushaengen();
                                                                  if(lportaloutput.anfang(lnpit))do{
                                                                   nextsector=lnpit->objekt()->sektor();
                                                                   if(nextsector==0){
                                                                    //error, portal muss sektor haben
                                                                    _vektor4<_to> col;
                                                                    col.setzen(1,0.45f,0,0);
                                                                    if(pzone->debugschirm()) pzone->debugschirm()->schreiben("Error : Portal muss Sektorzeiger haben.",col);
                                                                   }else{
                                                                    svalid=true;
                                                                    if(lsectorgesperrt.anfang(lnsit))do{
                                                                     if(lnsit->objekt()==nextsector) svalid=false;
                                                                    }while((lsectorgesperrt.naechstes(lnsit))&&(svalid==true));
                                                                    if(svalid){
                                                                     lsectorit.einhaengenunredundant(nextsector);
                                                                     lsectorgesperrt.einhaengen(nextsector);
                                                                    };
                                                                   };
                                                                  }while(lportaloutput.naechstes(lnpit));
                                                                  //-------------------------------------------------targetsektoren erreicht ?
                                                                  if(lsectorit.anzahl()==0){
                                                                   stop=true;
                                                                   visible=false;
                                                                  }else{
                                                                   if(lsectorit.anfang(lnsit))do{
                                                                    if(targetsectors.anfang(lntit))do{
                                                                     if(lnsit->objekt()==lntit->objekt()){
                                                                      //zielsektor erreicht
                                                                      // ******* DEBUG **********
                                                                      //_vektor4<_to> col;
                                                                      //col.setzen(0,0.7,0.3,0);
                                                                      //pzone->debugschirm()->schreiben("Zielsektor erreicht.",col);
                                                                      // ************************
                                                                      visible=true;
                                                                      stop=true;
                                                                     };
                                                                    }while((targetsectors.naechstes(lntit))&&(stop==false));
                                                                   }while((lsectorit.naechstes(lnsit))&&(stop==false));
                                                                  };
                                                                  //-------------------------------------------------portaleingabe neuladen, mit volumen schneiden
                                                                  if(stop==false){
                                                                   if(lsectorit.anfang(lnsit))do{
                                                                    if(lnsit->objekt()->anfang(pit))do{
                                                                     if(pit->portal()){
                                                                      pvalid=true;
                                                                      if(lportaloutput.anfang(lnpit))do{
                                                                       if(pit==lnpit->objekt()) pvalid=false;
                                                                      }while(lportaloutput.naechstes(lnpit));
                                                                      if(pvalid){
                                                                       innerportal=vv->innerhalb(pit);
                                                                       if(innerportal){
                                                                        lportalinput.einhaengenunredundant(pit);
                                                                        delete innerportal;
                                                                        innerportal=0;
                                                                       };
                                                                      };
                                                                     };
                                                                    }while(lnsit->objekt()->naechstes(pit));
                                                                   }while(lsectorit.naechstes(lnsit));
                                                                  };
                                                                  //-------------------------------------------------wenn kein portalinput vorhanden, dann stoppen (unsichtbar)
                                                                  if(stop==false){
                                                                   if(lportalinput.anfang(lnpit)){
                                                                   // do{
                                                                   //  if(lnpit->objekt()->anfang(pnext))do{
                                                                   //   if(pnext->objekt()->sektor()==targetsector){
                                                                   //    stop=true;
                                                                   //    visible=true;
                                                                   //   };
                                                                   //  }while((lnpit->objekt()->naechstes(pnext))&&(stop==false));
                                                                   // }while((lportalinput.naechstes(lnpit))&&(stop==false));
                                                                   }else{
                                                                    visible=false;
                                                                    stop=true;
                                                                   };
                                                                  };
                                                                  //----------------------------------------------------------------------------------------------------
                                                                 }while(stop==false);
                                                                 
                                                                 
                                                                 lportalinput.aushaengen();
                                                                 lportaloutput.aushaengen();
                                                                 lsectorit.aushaengen();
                                                                 delete vv;
                                                                };
                                                                return(visible);
 };*/
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
//                                                              polygon-sichtbarkeitsberechnung                                                               
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
 bool _sektor::istsichtbar(_partition::_polygon*portal,::_polygon*welt){
                                                                //ist das weltpolygon vom portal aus sichtbar?
                                                                bool visible;
                                                                bool frontfaced;
                                                                bool backfaced;
                                                                _vertex*vit;
                                                                ::_vertex*wit;
                                                                _vektor3<_tg> v;
                                                                _tg D0;
                                                                _tg D1;
                                                                _tg D;
                                                                _vektor3<_tg> pm;
                                                                _vektor3<_tg> pp0;
                                                                _vektor3<_tg> pp1;
                                                                _vektor3<_tg> pn;
                                                                _vektor3<_tg> wm;
                                                                _vektor3<_tg> wp;
                                                                _vektor3<_tg> wp0;
                                                                _vektor3<_tg> wp1;
                                                                _vektor3<_tg> schnitt;
                                                                _vektor3<_tg> vektor;
                                                                _vektoranalysis3<_tg> V3;
                                                                _tg s;
                                                                _partition::_polygon*pwelt;
                                                                _partition::_polygon*frontpoly;
                                                                _partition::_polygon*backpoly;
                                                                //---------------
                                                                visible=true;
                                                                //frontfaceprüfung
                                                                //prüfen, ob das weltpolygon
                                                                //gütlig ist, bzw. prüfen ob es frontfaced ist
                                                                frontfaced=false;
                                                                backfaced=false;
                                                                if(portal->anfang(vit))do{
                                                                 wit=welt->vertex();
                                                                 v=wit->ort()-*vit;
                                                                 v.normalisieren();
                                                                 s=v*welt->normale();
                                                                 if(welt->zweiseitig()){
                                                                  frontfaced=true;
                                                                 }else{
                                                                  if(s<-nahenull) frontfaced=true; else backfaced=true;
                                                                 };
                                                                }while(portal->naechstes(vit));
                                                                if(frontfaced==true){
                                                                 //an der portalebeneebene abschneiden
                                                                 //schnittgerade bestimmen und teilen aufrufen
                                                                 wm=welt->mitte();
                                                                 wp0=welt->ebene(0);
                                                                 wp1=welt->ebene(1);
                                                                 pm=portal->mitte();
                                                                 pn=portal->normalsector(pmiddle);
                                                                 pp0=portal->polygon()->ebene(0);
                                                                 pp1=portal->polygon()->ebene(1);
                                                                 D0=V3.determinieren(pp0,pp1,-wp0);
                                                                 D1=V3.determinieren(pp0,pp1,-wp1);
                                                                 if(fabs(D0)>fabs(D1)){ 
                                                                  D=D0; 
                                                                  wp=wp0;
                                                                 }else{
                                                                  D=D1;
                                                                  wp=wp1;
                                                                 };
                                                                 if(fabs(D)>nahenull){
                                                                  //schräg
                                                                  s=V3.determinieren(pp0,pp1,wm-pm)/D;
                                                                  schnitt=wm+wp*s;
                                                                  vektor=pn%welt->normale();
                                                                  vektor.normalisieren();
                                                                  pwelt=new _partition::_polygon(welt);
                                                                  pwelt->teilen(schnitt,schnitt+vektor,pn,welt->normale(),frontpoly,backpoly);
                                                                  delete pwelt;
                                                                  pwelt=0;
                                                                  if(frontpoly){
                                                                   visible=istsichtbar(portal,welt,frontpoly,frontfaced&&backfaced);
                                                                  }else{
                                                                   visible=false;
                                                                  };
                                                                  if(backpoly){
                                                                   delete backpoly;
                                                                   backpoly=0;
                                                                  };
                                                                  if(frontpoly){
                                                                   delete frontpoly;
                                                                   frontpoly=0;
                                                                  };
                                                                 }else{
                                                                  //parallel
                                                                  //wm=pm+a*pnormalsector+b*pp0+c*pp1
                                                                  D=V3.determinieren(pn,pp0,pp1);
                                                                  if(D){
                                                                   s=V3.determinieren(wm-pm,pp0,pp1)/D;
                                                                   if(s<+nahenull) {
                                                                    //komplanar oder dahinter
                                                                    visible=false;
                                                                   }else{
                                                                    //parallel davor
                                                                    pwelt=new _partition::_polygon(welt);
                                                                    visible=istsichtbar(portal,welt,pwelt,false);
                                                                    delete pwelt;
                                                                    pwelt=0;
                                                                   };
                                                                  }else{
                                                                   //error
                                                                  }
                                                                 };
                                                                }else{
                                                                 visible=false;
                                                                };
                                                                return(visible);
 };
 
 bool _sektor::istsichtbar(_partition::_polygon*portal,::_polygon*orgwelt,_partition::_polygon*welt,const bool multifaced){
                                                                //funktion stellt fest, ob das potentiell sichtbare polygon welt
                                                                //auch wirklich von portal aus sichtbar ist
                                                                //zunächst das portal poly
                                                                //so anpassen, dass bei multifaced welt-
                                                                //polygon, das portal an der welteben abgeschnitten wird
                                                                _partition::_polygon*frontpoly;
                                                                _partition::_polygon*backpoly;
                                                                bool visible;
                                                                _tg D0;
                                                                _tg D1;
                                                                _tg D,s;
                                                                _vektor3<_tg> pm;
                                                                _vektor3<_tg> pp0;
                                                                _vektor3<_tg> pp1;
                                                                _vektor3<_tg> pn;
                                                                _vektor3<_tg> wm;
                                                                _vektor3<_tg> wp;
                                                                _vektor3<_tg> wp0;
                                                                _vektor3<_tg> wp1;
                                                                _vektoranalysis3<_tg> V3;
                                                                _vektor3<_tg> schnitt;
                                                                _vektor3<_tg> vektor;
                                                                //--------------
                                                                visible=false;
                                                                if(multifaced){
                                                                 
                                                                 wm=welt->mitte();
                                                                 wp0=welt->polygon()->ebene(0);
                                                                 wp1=welt->polygon()->ebene(1);
                                                                 pm=portal->mitte();
                                                                 pn=portal->normalsector(pmiddle);
                                                                 pp0=portal->polygon()->ebene(0);
                                                                 pp1=portal->polygon()->ebene(1);
                                                                 D0=V3.determinieren(pp0,pp1,-wp0);
                                                                 D1=V3.determinieren(pp0,pp1,-wp1);
                                                                 if(fabs(D0)>fabs(D1)){ 
                                                                  D=D0; 
                                                                  wp=wp0;
                                                                 }else{
                                                                  D=D1;
                                                                  wp=wp1;
                                                                 };
                                                                 if(fabs(D)>nahenull){
                                                                  s=V3.determinieren(pp0,pp1,wm-pm)/D;
                                                                  schnitt=wm+wp*s;
                                                                  vektor=pn%welt->normale();
                                                                  vektor.normalisieren();
                                                                  portal->teilen(schnitt,schnitt+vektor,welt->normale(),pn,frontpoly,backpoly);
                                                                  if(frontpoly){
                                                                   visible=istsichtbar(portal,orgwelt,frontpoly,welt);
                                                                  }else{
                                                                   visible=false;
                                                                  };
                                                                  if(backpoly){
                                                                   delete backpoly;
                                                                   backpoly=0;
                                                                  };
                                                                  if(frontpoly){
                                                                   delete frontpoly;
                                                                   frontpoly=0;
                                                                  };
                                                                 }else{
                                                                  //error
                                                                 };
                                                                }else{
                                                                 visible=istsichtbar(portal,orgwelt,portal,welt);
                                                                };
                                                                return(visible);
 };
 
 bool _sektor::istsichtbar(_partition::_polygon*orgportal,::_polygon*orgwelt,_partition::_polygon*portal,_partition::_polygon*welt){
                                                                //hier läuft die sichtbarkeitbestimmung an
                                                                //sichtbarkeitsvolumen werden angelegt und getestet
                                                                bool visible;
                                                                //bool error;
                                                                bool stop;
                                                                _sichtbarkeitsvolumen*vv;
                                                                _vektor3<_tg> h;
                                                                _polygon*pit;
                                                                //_polygon*innerportal;
                                                                _sektor*sit;
                                                                //_sektor*nextsector;
                                                                _liste<_sektor > targetsectors;
                                                                _liste<_polygon > lportalinput;
                                                                _liste<_polygon > lportaloutput;
                                                                _liste<_sektor > lsectorit;
                                                                _liste<_sektor > lsectorgesperrt;
                                                                //_listenknoten<_sektor >*lntit;
                                                                //_listenknoten<_polygon >*pnext;
                                                                _listenknoten<_polygon >*lnpit;
                                                                _listenknoten<_sektor >*lnsit;
                                                                //bool pvalid;
                                                                bool vvalid;
                                                                //bool svalid;
                                                                _vektor3<_tg> weltnormale;
                                                                //--------------------------------
                                                                visible=false;
                                                                //sichtbarkeitsvolumen anlegen
                                                                //volumen sind nur dann gültig, wenn ihr 
                                                                //zentralvertex nicht in der anderes-ebene liegt
                                                                vvalid=true;
                                                                h=portal->mitte()-welt->mitte();
                                                                if(h.laenge()<=nahenull){
                                                                 vvalid=false;
                                                                }else{
                                                                 h.normalisieren();
                                                                 weltnormale=welt->normale();
                                                                 if(orgwelt->zweiseitig()){
                                                                  vvalid=true;
                                                                  if( fabs(h*welt->polygon()->normale())<=nahenull ) weltnormale*=-1;
                                                                 }else{
                                                                  if( fabs(h*welt->polygon()->normale())<=nahenull ) vvalid=false;
                                                                 };
                                                                };
                                                                if(vvalid) {
                                                                 vv=new _sichtbarkeitsvolumen(pzone,portal,portal->normalsector(pmiddle),welt,weltnormale);
                                                                 //******************** DEBUG *********************
                                                                 if(pzone->welt()->debuggensichtbarkeit()){
                                                                  pzone->pdbcount++;
                                                                  if(orgwelt->debuggen()){
                                                                   _vektor4<_to> colore;
                                                                   colore.setzen(0.8f,0.45f,0.2f,0);
                                                                   if(pzone->debugschirm()) pzone->debugschirm()->schreiben("Volumen Nr.:",pzone->pdbcount,colore);
                                                                   _vektor4<_to> col;
                                                                   _vektor4<_to> colr;
                                                                   _vektor4<_to> coln;
                                                                   col.setzen(1,0.1f,0.1f,0);
                                                                   colr.setzen(0.23f,0.2f,0.8f,0);
                                                                   coln.setzen(0,0.5f,1,0);
                                                                   vv->visualisieren(coln,col,colr);
                                                                   pzone->debuganimation();
                                                                  };
                                                                 };
                                                                 //************************************************
                                                                 //nun alle anderen externen zonenpolygone
                                                                 //herausiterieren, die nicht zum sektor this
                                                                 //gehören oder welt->polygon() sind, und mit den 
                                                                 //einzelnen volumen schneiden
                                                                 //liste von zielsektoren determinieren
                                                                 //d.h. alle sektoren von orgwelt identifizieren
                                                                 //wenn das orgwelt polygon am bsp teilgenommen hat:
                                                                 if(pzone->anfang(sit))do{
                                                                  if(sit!=this){
                                                                   stop=false;
                                                                   if(sit->anfang(pit))do{
                                                                    if(pit->portal()==false){
                                                                     if(pit->polygon()==orgwelt){
                                                                      targetsectors.einhaengenunredundant(sit);
                                                                      stop=true;
                                                                     };
                                                                    };
                                                                   }while((sit->naechstes(pit))&&(stop==false));
                                                                  };
                                                                 }while(pzone->naechstes(sit));
                                                                 //wenn das orgpoly ein internes ist:
                                                                 if(orgwelt->anfang(lnsit))do{
                                                                  targetsectors.einhaengenunredundant(lnsit->objekt());
                                                                 }while(orgwelt->naechstes(lnsit));
                                                                 
                                                                 
                                                                 //******* DEBUG **********
                                                                 //if(pzone->pdbcount>177){
                                                                 // _vektor4<_to> colore;
                                                                 // colore.setzen(0.8f,0.45f,0.2f,0);
                                                                 // if(pzone->debugschirm()) pzone->debugschirm()->schreiben("Zielsektoren werden visualisiert",colore);
                                                                 // if(targetsectors.anfang(lnsit))do{
                                                                 //  lnsit->objekt()->visualisieren();
                                                                 // }while(targetsectors.naechstes(lnsit));
                                                                 // pzone->debuganimation();
                                                                 // if(targetsectors.anfang(lnsit))do{
                                                                 //  lnsit->objekt()->unvisualisieren();
                                                                 // }while(targetsectors.naechstes(lnsit));
                                                                 //};
                                                                 //************************
                                                                 //hauptschleife
                                                                 //liste von portaliteratoren laufen lassen
                                                                 lsectorgesperrt.einhaengen(this);
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 
                                                                   
                                                                 
                                                                 ///starten mit der iteration des portalausgangs von orgportal
                                                                 if(orgportal->anfang(lnpit))do{
                                                                  if(lnpit->objekt()->sektor()->istsichtbar(portal,welt,vv,&lsectorgesperrt,&targetsectors)) {
                                                                   //************* DEBUG **************
                                                                   vv->unvisualisieren();
                                                                   //**********************************    
                                                                   delete vv;     
                                                                   return(true);                                              
                                                                  };           
                                                                 }while(orgportal->naechstes(lnpit));
                                                                 

                                                                 //************* DEBUG **************
                                                                 vv->unvisualisieren();
                                                                 //**********************************
                                                                 delete vv;
                                                                };
                                                                return(false);
                                                                 
 };                                                                


                                                                 
                                                                 
  bool _sektor::istsichtbar(_partition::_polygon*portal,_partition::_polygon*welt,_sichtbarkeitsvolumen*vv,_liste<_sektor>*lsectorgesperrt,_liste<_sektor>*targetsectors){       
                                                                bool sichtbar=false;
                                                                //rekursive funktion, die sektoren abiteriert
                                                                //sichtbar ist das welt poylgon dann, 
                                                                //wenn einer der target sektoren erreicht wurde
                                                                _listenknoten<_sektor>*lnsit;
                                                                if(targetsectors->anfang(lnsit))do{
                                                                 if(lnsit->objekt()==this) return(true);
                                                                }while(targetsectors->naechstes(lnsit));
                                                                lsectorgesperrt->einhaengenunredundant(this);
                                                                //ansonsten die portale dieses sektors itereieren
                                                                //den portal ausgang dieses sektors iterieren
                                                                //sperrung prüfen
                                                                _polygon*pit;
                                                                _polygon*innenpoly;
                                                                _listenknoten<_polygon>*lnpit;
                                                                bool gesperrt;
                                                                if(anfang(pit))do{
                                                                 if(pit->portal()){


                                                                  innenpoly=vv->innerhalb(pit);
                                                                  if(innenpoly){
                                                                   delete innenpoly;
                                                                   innenpoly=0; 


                                                                   if(pit->anfang(lnpit))do{
                                                                    gesperrt=false;
                                                                    if(lsectorgesperrt->anfang(lnsit))do{
                                                                     if(lnsit->objekt()==lnpit->objekt()->sektor()) gesperrt=true;
                                                                    }while((lsectorgesperrt->naechstes(lnsit))&&(gesperrt==false));
                                                                    if(gesperrt==false){
                                                                     innenpoly=vv->innerhalb(lnpit->objekt());
                                                                     if(innenpoly){
                                                                      delete innenpoly;
                                                                      innenpoly=0;
                                                                      if(lnpit->objekt()->sektor()->istsichtbar(portal,welt,vv,lsectorgesperrt,targetsectors)) return(true);
                                                                     };
                                                                    };
                                                                   }while(pit->naechstes(lnpit));
                                                                  };
                                                                 };
                                                                }while(naechstes(pit));
                                                                return(sichtbar);
};

                                                                 
                                                                 
                                                                 
            /*                                                     
                                                                 
                                                                 
                                                                 
                                                                 lportalinput.einhaengen(orgportal);
                                                                 stop=false;
                                         
                                                                 
                                                                 
                                                                       
                                                                 do{
                                                                  //-------------------------------------------------portaleingang in portalausgang übersetzen
                                                                  lportaloutput.aushaengen();
                                                                  if(lportalinput.anfang(lnpit))do{
                                                                   if(lnpit->objekt()->anfang(pnext))do{
                                                                    lportaloutput.einhaengenunredundant(pnext->objekt());
                                                                   }while(lnpit->objekt()->naechstes(pnext));
                                                                  }while(lportalinput.naechstes(lnpit));
                                                                  lportalinput.aushaengen();
                                                                  //-------------------------------------------------iterierte sektoren identifizieren 
                                                                  lsectorit.aushaengen();
                                                                  if(lportaloutput.anfang(lnpit))do{
                                                                   nextsector=lnpit->objekt()->sektor();
                                                                   if(nextsector==0){
                                                                    //error, portal muss sektor haben
                                                                    _vektor4<_to> col;
                                                                    col.setzen(1,0.45f,0,0);
                                                                    if(pzone->debugschirm()) pzone->debugschirm()->schreiben("Error : Portal muss Sektorzeiger haben.",col);
                                                                   }else{
                                                                    svalid=true;
                                                                    if(lsectorgesperrt.anfang(lnsit))do{
                                                                     if(lnsit->objekt()==nextsector) svalid=false;
                                                                    }while((lsectorgesperrt.naechstes(lnsit))&&(svalid==true));
                                                                    if(svalid){
                                                                     lsectorit.einhaengenunredundant(nextsector);
                                                                     lsectorgesperrt.einhaengen(nextsector);
                                                                    };
                                                                   };
                                                                  }while(lportaloutput.naechstes(lnpit));
                                                                  //-------------------------------------------------targetsektoren erreicht ?
                                                                  if(lsectorit.anzahl()==0){
                                                                   stop=true;
                                                                   visible=false;
                                                                  }else{
                                                                   if(lsectorit.anfang(lnsit))do{
                                                                    if(targetsectors.anfang(lntit))do{
                                                                     if(lnsit->objekt()==lntit->objekt()){
                                                                      //zielsektor erreicht
                                                                      //******* DEBUG **********
                                                                      //_vektor4<_to> col;
                                                                      //col.setzen(0,0.7,0.3,0);
                                                                      //if(pzone->debugschirm()) pzone->debugschirm()->schreiben("Zielsektor erreicht.",col);
                                                                      //************************
                                                                      visible=true;
                                                                      stop=true;
                                                                     };
                                                                    }while((targetsectors.naechstes(lntit))&&(stop==false));
                                                                   }while((lsectorit.naechstes(lnsit))&&(stop==false));
                                                                  };
                                                                  //-------------------------------------------------portaleingabe neuladen, mit volumen schneiden
                                                                  if(stop==false){
                                                                   if(lsectorit.anfang(lnsit))do{
                                                                    if(lnsit->objekt()->anfang(pit))do{
                                                                     if(pit->portal()){
                                                                      pvalid=true;
                                                                      if(lportaloutput.anfang(lnpit))do{
                                                                       if(pit==lnpit->objekt()) pvalid=false;
                                                                      }while(lportaloutput.naechstes(lnpit));
                                                                      if(pvalid){
                                                                       innerportal=vv->innerhalb(pit);
                                                                       if(innerportal) {
                                                                        lportalinput.einhaengenunredundant(pit);
                                                                        delete innerportal;
                                                                        innerportal=0;
                                                                       };
                                                                      };
                                                                     };
                                                                    }while(lnsit->objekt()->naechstes(pit));
                                                                   }while(lsectorit.naechstes(lnsit));
                                                                  };
                                                                  //-------------------------------------------------wenn kein portalinput vorhanden, dann stoppen (unsichtbar)
                                                                  if(stop==false){
                                                                   if(lportalinput.anfang(lnpit)){
                                                                    //weitermachen
                                                                   }else{
                                                                    visible=false;
                                                                    stop=true;
                                                                   };
                                                                  };
                                                                  //----------------------------------------------------------------------------------------------------
                                                                 }while(stop==false);
                                                                 
                                                                 
                                                                 lportalinput.aushaengen();
                                                                 lportaloutput.aushaengen();
                                                                 lsectorit.aushaengen();
                                                                 
                                                                 
                                                                 //************* DEBUG **************
                                                                 vv->unvisualisieren();
                                                                 //**********************************



                                                                 delete vv;
                                                                };
                                                                return(visible);
 };
 
 
 */
 
 
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 
 
                                                              
                                                                 
                                                                 
                                            
 unsigned int _sektor::anzahlpolygon() const{
                                                                unsigned int i;
                                                                _polygon*pit;
                                                                //--------------
                                                                i=0;
                                                                if(anfang(pit))do{
                                                                 i++;
                                                                }while(naechstes(pit));
                                                                return(i);
 };
 
 unsigned int _sektor::anzahlportal() const{
                                                                unsigned int i;
                                                                _polygon*pit;
                                                                //--------------
                                                                i=0;
                                                                if(anfang(pit))do{
                                                                 if(pit->portal()) i++;
                                                                }while(naechstes(pit));
                                                                return(i);
 };
 
 unsigned int _sektor::countnonportal() const{
                                                                unsigned int i;
                                                                _polygon*pit;
                                                                //--------------
                                                                i=0;
                                                                if(anfang(pit))do{
                                                                 if(pit->portal()==false) i++;
                                                                }while(naechstes(pit));
                                                                return(i);
 };
 
 unsigned int _sektor::anzahlvertex() const{
                                                                unsigned int i;
                                                                _polygon*pit;
                                                                _vertex*vit;
                                                                //--------------
                                                                i=0;
                                                                if(anfang(pit))do{
                                                                 if(pit->anfang(vit))do{
                                                                  i++;
                                                                 }while(pit->naechstes(vit));
                                                                }while(naechstes(pit));
                                                                return(i);
 };
 
 char _sektor::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_sektor>*sd){
                                                                unsigned int visextcount=0;
                                                                unsigned int visseccount=0;
                                                                unsigned int i;
                                                                char r=1;
                                                                //------------------------------------
                                                                r^=sd->ladenbeginn(fn);
                                                                r^=sd->ladenverschachtelung(fn);
                                                                r^=sd->ladenwert(pbackclosed);
                                                                r^=sd->ladenwert(pmiddle);
                                                                r^=sd->ladenwert(visextcount);
                                                                pvisibilityextern.loeschen();
                                                                for(i=0;i<visextcount;i++) {
                                                                 r^=sd->ladenassoziation();
                                                                 pvisibilityextern.einhaengen((::_polygon*)1);//ein pseudowert für einen polygonzeiger, der später durch assoziation geladen wird
                                                                };
                                                                r^=sd->ladenwert(visseccount);
                                                                pvisibilitysector.loeschen();
                                                                for(i=0;i<visseccount;i++) {
                                                                 r^=sd->ladenassoziation();
                                                                 pvisibilitysector.einhaengen((_sektor*)1);//ein pseudowert für einen sectorzeiger, der später durch assoziation geladen wird
                                                                };
                                                                sd->ladenende();
                                                                return(r);
 };
 
 void _sektor::speichern(_speicherbardynamisch<_sektor>*sd){
                                                                _listenknoten< ::_polygon >*pit;
                                                                _listenknoten<_sektor >*sit;
                                                                //--------------------------------------
                                                                sd->speichernbeginnblock();
                                                                sd->speichernverschachtelung();
                                                                sd->speichernwert(pbackclosed);
                                                                sd->speichernwert(pmiddle);
                                                                sd->speichernwert(pvisibilityextern.anzahl());
                                                                if(pvisibilityextern.anfang(pit))do{
                                                                 saveassociationargument(sd->datei(),sd,pit->objekt());
                                                                }while(pvisibilityextern.naechstes(pit));
                                                                sd->speichernwert(pvisibilitysector.anzahl());
                                                                if(pvisibilitysector.anfang(sit))do{
                                                                 saveassociationargument(sd->datei(),sd,sit->objekt());
                                                                }while(pvisibilitysector.naechstes(sit));
                                                                sd->speichernendeblock();
 };
 
 char _sektor::assoziieren(_speicherbardynamisch<_sektor>*sd){
                                                                unsigned int i;
                                                                _listenknoten< ::_polygon >*pit;
                                                                _listenknoten<_sektor >*sit;
                                                                ::_polygon*poly;
                                                                _sektor*sektor;
                                                                //--------------
                                                                sd->assoziierenverschachtelung();
                                                                if(pvisibilityextern.anfang(pit)){
                                                                 for(i=0;i<pvisibilityextern.anzahl();i++){
                                                                  associateassociationargument(sd->datei(),sd->assoziation(),poly);
                                                                  pit->objekt(poly);
                                                                  pvisibilityextern.naechstes(pit);
                                                                 };
                                                                };

                                                                if(pvisibilitysector.anfang(sit)){
                                                                 for(i=0;i<pvisibilitysector.anzahl();i++){
                                                                  associateassociationargument(sd->datei(),sd->assoziation(),sektor);
                                                                  sit->objekt(sektor);
                                                                  pvisibilitysector.naechstes(sit);
                                                                 };
                                                                };
                                                                
                                                                return(1);
 };
 bool _sektor::laden(_dateispeicherbarbinaer*d){
																einhaengenspeicherung(d);
																ladenbeginn();
																d->laden(speichername());
																unsigned int i,a;
																_vektor3<_tg> vn(0,0,0);
																_vektor3<_to> cn(1,1,1);

																_partition::_polygon*ppit;
																d->laden(a);
																for(i=0;i<a;i++){
																 ppit=new _partition::_polygon((::_polygon*)0);
																 ppit->einfuegeninsektor(this);
																 ppit->laden(d);
																};



																_licht<_tg,_to>*lit;
																d->laden(a);
																for(i=0;i<a;i++){
																 lit=new _licht<_tg,_to>(this,vn,cn,1);
																 lit->laden(d);
																};

																//_baumoctalwuerfel<::_polygon,_tg>*wit;
																//_listenknoten<::_polygon>*lnpit;

																a=ladenanzahl(d);
																_baumoctal<::_polygon,_tg>::aushaengen();
																for(i=0;i<a;i++) ladenzeiger(d);
													


																d->laden(pbackclosed);
																d->laden(pmiddle);
																
																a=ladenanzahl(d);
																pinternstatisch.aushaengen();
																for(i=0;i<a;i++) ladenzeiger(d);

																a=ladenanzahl(d);
																pinterndynamisch.aushaengen();
																for(i=0;i<a;i++) ladenzeiger(d);

																a=ladenanzahl(d);
																pinternnetz.aushaengen();
																for(i=0;i<a;i++) ladenzeiger(d);

																a=ladenanzahl(d);
																pvisibilityextern.aushaengen();
																for(i=0;i<a;i++) ladenzeiger(d);

																a=ladenanzahl(d);
																pvisibilityintern.aushaengen();
																for(i=0;i<a;i++) ladenzeiger(d);

																a=ladenanzahl(d);
																pvisibilitysector.aushaengen();
																for(i=0;i<a;i++) ladenzeiger(d);

																a=ladenanzahl(d);
																pvisibilitysector2tergrad.aushaengen();
																for(i=0;i<a;i++) ladenzeiger(d);
																return(true);


 };
 void _sektor::speichern(_dateispeicherbarbinaer*d){
																d->speichern(speichername());

																_partition::_polygon*ppit;
																d->speichern(_listebasis<_partition::_polygon>::anzahl());
																iterieren(ppit,ppit->speichern(d));

																_licht<_tg,_to>*lit;
																d->speichern(_listebasis<_licht<_tg,_to> >::anzahl());
																iterieren(lit,lit->speichern(d));

																_baumoctalwuerfel<::_polygon,_tg>*wit;
																_listenknoten<::_polygon>*lnpit;
																_listenknoten<_netz>*lnnit;
																_listenknoten<_sektor>*lnsit;

																_liste<::_polygon> lp;
																iterieren(wit,iterierenliste(wit,lnpit,lp.einhaengenunredundant(lnpit->objekt())));
																d->speichern(lp.anzahl());
																iterierenliste((&lp),lnpit,speichernzeiger(d,lnpit->objekt()));

																d->speichern(pbackclosed);
																d->speichern(pmiddle);
																d->speichern(pinternstatisch.anzahl());
																iterierenliste((&pinternstatisch),lnpit,speichernzeiger(d,lnpit->objekt()));
																d->speichern(pinterndynamisch.anzahl());
																iterierenliste((&pinterndynamisch),lnpit,speichernzeiger(d,lnpit->objekt()));
																d->speichern(pinternnetz.anzahl());
																iterierenliste((&pinternnetz),lnnit,speichernzeiger(d,lnnit->objekt()));
																d->speichern(pvisibilityextern.anzahl());
																iterierenliste((&pvisibilityextern),lnpit,speichernzeiger(d,lnpit->objekt()));
																d->speichern(pvisibilityintern.anzahl());
																iterierenliste((&pvisibilityintern),lnpit,speichernzeiger(d,lnpit->objekt()));
																d->speichern(pvisibilitysector.anzahl());
																iterierenliste((&pvisibilitysector),lnsit,speichernzeiger(d,lnsit->objekt()));
																d->speichern(pvisibilitysector2tergrad.anzahl());
																iterierenliste((&pvisibilitysector2tergrad),lnsit,speichernzeiger(d,lnsit->objekt()));

 };
 bool _sektor::assoziieren(){
																if(zeigergeladen()){
															     unsigned int i,a;
																 ::_polygon*p;
																 _netz*n;
																 _sektor*s;

																 a=ladenanzahl();
																 for(i=0;i<a;i++) {
																  assoziierenzeiger(p);
																  _tg x0,x1,y0,y1,z0,z1;
																  p->umgrenzungsquader(x0,x1,y0,y1,z0,z1);
																  _baumoctal<::_polygon,_tg>::einhaengen(p,x0,x1,y0,y1,z0,z1);
															     };
													
																 a=ladenanzahl();
																 for(i=0;i<a;i++) {
																  assoziierenzeiger(p);
																  pinternstatisch.einhaengen(p);
																 };

																 a=ladenanzahl();
																 for(i=0;i<a;i++) {
																  assoziierenzeiger(p);
																  pinterndynamisch.einhaengen(p);
																 };

																 a=ladenanzahl();
																 for(i=0;i<a;i++) {
																  assoziierenzeiger(n);
																  pinternnetz.einhaengen(n);
																 };

																 a=ladenanzahl();
																 for(i=0;i<a;i++) {
																  assoziierenzeiger(p);
																  pvisibilityextern.einhaengen(p);
																 };

																 a=ladenanzahl();
																 for(i=0;i<a;i++) {
																  assoziierenzeiger(p);
																  pvisibilityintern.einhaengen(p);
																 };

																 a=ladenanzahl();
																 for(i=0;i<a;i++) {
																  assoziierenzeiger(s);
																  pvisibilitysector.einhaengen(s);
																 };

																 a=ladenanzahl();
																 for(i=0;i<a;i++) {
																  assoziierenzeiger(s);
																  pvisibilitysector2tergrad.einhaengen(s);
																 };
																 loeschenzeiger();
																 loeschenanzahl();
																};
																return(true);
 }; 
 void _sektor::visualisieren(){
                                                                _vektor4<_to> col;
                                                                col.setzen(1,1,0,1);
                                                                visualisieren(col);
 };
 
 void _sektor::visualisieren(_vektor4<_to> col){
                                                                
                                                                _polygon*pit;
                                                                _vektor3<_tg> mitte;
                                                                //_vektor4<_to> col;
                                                                
                                                                _tg c;
                                                                //-----------------------------
                                                                mitte.setzen(0,0,0);
                                                                c=0;
                                                                if(pbackclosed) col.setzen(1,0,1,1); 
                                                                if(anfang(pit))do{
                                                                 mitte+=pit->mitte();
                                                                 pit->visualisieren(pzone,col);
                                                                 c+=1;
                                                                }while(naechstes(pit));
                                                                if(c>0){
                                                                 mitte*=1/c;
                                                                 //col.setzen(1,1,0);
                                                                 if(pdbcross) delete pdbcross;
                                                                 pdbcross=new _weltdebugkreuz(pzone->welt(),mitte,0.15,col);
                                                                }else{
                                                                 //error . kein polygon 
                                                                };
 };
 
 void _sektor::unvisualisieren(){
                                                                _polygon*pit;
                                                                //-------------------------
                                                                if(anfang(pit))do{
                                                                 pit->unvisualisieren();
                                                                }while(naechstes(pit));
                                                                if(pdbcross){
                                                                 delete pdbcross;
                                                                 pdbcross=0;
                                                                };
                                                                
 };
};
//******************************************************************************************************************************************************************************************************
//                                                              P A R T I T I O N   : :   P O L Y G O N 
//******************************************************************************************************************************************************************************************************
namespace _partition{
 /*
 _polygon::_polygon(_sektor*s,::_polygon*p,const bool isp):_listenknotenbasis<_polygon >(s){
                                                                //regulärer konstruktor
                                                                psector=s;
                                                                ppoly=p;
                                                                pisportal=isp;
                                                                updated=false;
                                                                L->schreiben("Sektorpolygon wurde angelegt");
 };
 */
 _polygon::_polygon(::_polygon*p):_listenknotenbasis<_polygon >(0){
                                                                //konstruktor für intersektionsoperationen
                                                                ::_vertex*vit;
                                                                _listenknoten<::_vertex>*lnvit;
                                                                //------------------------------
                                                                psector=0;
                                                                ppoly=p;
                                                                pisportal=false;
                                                                updated=false;
                                                                if(p){//ist somit für den ladeprozess gültig
                                                                 //vit=p->vertex();
                                                                 //if(vit)do{
                                                                 iterierenliste(p,lnvit,
                                                                  vit=lnvit->objekt();
                                                                  new _partition::_vertex(this,vit->ort());
                                                                 );
                                                                 // vit=vit->naechstes(p);
                                                                 //}while(vit!=p->vertex());
                                                                 aktualisieren();
                                                                };
                                                                markierungkollisionobjekt=0;
                                                                markierungkollisionrekursion=0;
                                                                markierungkollisionzyklus=0;
 };
  
 _polygon::_polygon(const _partition::_polygon*p):_listenknotenbasis<_polygon >(0){
                                                                //konstruktor für intersektionsoperationen
                                                                _vertex*vit;
                                                                //------------------------------
                                                                psector=0;
                                                                ppoly=p->ppoly;
                                                                pisportal=p->pisportal;
                                                                updated=false;
                                                                if(p->anfang(vit))do{
                                                                 new _partition::_vertex(this,*vit);
                                                                }while(p->naechstes(vit));
                                                                aktualisieren();
                                                                markierungkollisionobjekt=0;
                                                                markierungkollisionrekursion=0;
                                                                markierungkollisionzyklus=0;
 };
  
 _polygon::~_polygon(){
                                                                unvisualisieren();
 }; 
  
 ::_polygon* _polygon::polygon(){
                                                                return(ppoly);
 };
  
 _sektor* _polygon::sektor(){
                                                                return(psector);
 };
  
 _sektor*_polygon::holennaechstersektor(const _vektor3<_tg>&schnitt){
                                                                _listenknoten<_polygon >*lpit;
                                                                _sektor*r;
                                                                //_polygon*prt;
                                                                //_vertex*vit;
                                                                //_vertex*vin;
                                                                //bool diskret;
                                                                //_vektoranalysis3<_tg> V3;
                                                                //_vektor3<_tg> h;
                                                                //_tg c,D;
                                                                //------------
                                                                r=0;
                                                                //************** DEBUG **************
                                                                //_vektor4<_to> col;
                                                                //col.setzen(0,1,0);
                                                                //new _weltdebugkreuz(W,schnitt,0.1,col);
                                                                //if(anfang(lpit))do{
                                                                // lpit->objekt()->visualisieren(pzone,col);
                                                                //}while(naechstes(lpit));
                                                                //visualisieren(col);
                                                                //***********************************
                                                                if(anfang(lpit))do{
                                                                 if(lpit->objekt()->innerhalbpunkt(schnitt)){
                                                                  r=lpit->objekt()->sektor();
                                                                  if(r==0) L->schreiben("ERROR : _partition::_polygon::holennaechstersektor(const _vektor<_tg>&) : portal->sektor()==0");
                                                                 };
                                                                }while((naechstes(lpit))&&(r==0));
                                                                if(r==0) L->schreiben("ERROR : _partition::_polygon::holennaechstersektor(const _vektor<_tg>&) : kein Nachbarsektor eines Portals gefunden. Anzahl der Polygoneintraege = ",(int)_liste<_polygon >::anzahl());
                                                                return(r);
 };

  
 void _polygon::loeschenvertex(){
                                                                _listebasis<_vertex >::loeschen();
 };
  
 void _polygon::einfuegeninsektor(_sektor*s){
                                                                _listenknotenbasis<_polygon >::einhaengen(s);
                                                                psector=s;
 };
  
 bool _polygon::portal() const{
                                                                return(pisportal);
 };
  
 void _polygon::portal(const bool b){
                                                                pisportal=b;
 };
  
 void _polygon::aktualisieren(){
                                                                _vertex*vit;
                                                                _vertex*vin;
                                                                _tg c;
                                                                //--------------- mitte vorberechnen -----------------------
                                                                updated=false;


                                                                pmiddle.setzen(0,0,0);
                                                                c=0;
                                                                if(anfang(vit))do{
                                                                 pmiddle+=*vit;
                                                                 c+=1;
                                                                }while(naechstes(vit));
                                                                if(c>0){
                                                                 pmiddle*=1/c;
                                                                 updated=true; 
                                                                }else{
                                                                 //error kein vertex
                                                                };
                                                                //--------------- sektornormale vorberechnen ----------------
                                                                if(psector){
                                                                 _vektor3<_tg> n;
                                                                 _vektor3<_tg> v;
                                                                 _tg d;
                                                                 //-------------------
                                                                 pnormale=ppoly->normale();
                                                                 v=pmiddle-psector->mitte();
                                                                 v.normalisieren();
                                                                 d=v[0]*pnormale[0] + v[1]*pnormale[1] + v[2]*pnormale[2];
                                                                 if(d<0) pnormale*=-1.0f;
                                                                }else{
                                                                 pnormale=ppoly->normale();
                                                                };
                                                                //---------------- vertexdeterminanten vorberechnen --------
                                                                _tg h[2];
                                                                aktualisierengroessterindex();
                                                                if(anfang(vit))do{
																 vin=vit->_listenknotenbasis<_vertex>::naechstes();
                                                                 vit->kantevektor[0]=(*vin)[pgi[0]] - (*vit)[pgi[0]];
                                                                 vit->kantevektor[1]=(*vin)[pgi[1]] - (*vit)[pgi[1]];
                                                                 ::setzen2(vit->kantemitte,vit->kantevektor);
                                                                 ::normalisieren2(vit->kantevektor);
                                                                 ::berechnenorthogonalenvektor2(vit->kantevektor,vit->kantenormale);
                                                                 ::normalisieren2(vit->kantenormale);
                                                                 
                                                                 ::multiplizieren2<_tg>(vit->kantemitte,0.5);
                                                                 vit->kantemitte[0]+=(*vit)[pgi[0]];
                                                                 vit->kantemitte[1]+=(*vit)[pgi[1]];
                                                                 h[0]=pmiddle[pgi[0]]- vit->kantemitte[0];
                                                                 h[1]=pmiddle[pgi[1]]- vit->kantemitte[1];
                                                                 if(::produkt2(h,vit->kantenormale)<0) ::multiplizieren2<_tg>(vit->kantenormale,-1.0f);
                                                                 vit->determinante=::determinieren2(vit->kantenormale,vit->kantevektor);
                                                                }while(naechstes(vit));
 };
  
 void _polygon::unaktualisieren(){
                                                                updated=false;
 };
 void _polygon::aktualisierengroessterindex(){
                                                                //ermittelt die bestmöglichen komponenten der ebenenvektoren im poly p
                                                                int c0;
                                                                int c1;
                                                                int c2;
                                                                _partition::_vertex*v;
                                                                _partition::_vertex*v0;
                                                                _partition::_vertex*v1;
                                                                int i;
                                                                _tg A[3];
                                                                _vektor3<_tg> a;
                                                                _vektor3<_tg> o;
                                                                _vektor3<_tg> p;
                                                                _vektor3<_tg> h;
                                                                _vektoranalysis3<_tg> V3;
                                                                //------------------
                                                                A[0]=0;
                                                                A[1]=0;
                                                                A[2]=0;
                                                                v=0;
                                                                if(anfang(v)){
                                                                 v0=v->_listenknotenbasis<_vertex>::naechstes();
                                                                 v1=v0->_listenknotenbasis<_vertex>::naechstes();
                                                                 do{
                                                                  //temp dreieck : v,v0,v1
                                                                  for(i=0;i<3;i++){
                                                                   p=*v;
                                                                   a=*v1-*v0;
                                                                   o=*v0;
                                                                   p.setzenkomponente(i,0);
                                                                   a.setzenkomponente(i,0);
                                                                   o.setzenkomponente(i,0);
                                                                   V3.lotpunktgerade(p,o,a,h);
                                                                   A[i]+=0.5*h.laenge()*a.laenge();
                                                                  };
                                                                  v0=v1;
                                                                  v1=v1->_listenknotenbasis<_vertex>::naechstes();
                                                                 }while(v1!=v);
                                                                };
                                                                if(A[0]>A[1]){
                                                                 if(A[0]>A[2]){//A0
                                                                  c0=1;
                                                                  c1=2;
                                                                  c2=0;
                                                                 }else{//A2
                                                                  c0=0;
                                                                  c1=1;
                                                                  c2=2;
                                                                 };
                                                                }else{
                                                                 if(A[1]>A[2]){//A1
                                                                  c0=0;
                                                                  c1=2;
                                                                  c2=1;
                                                                 }else{//A2
                                                                  c0=0;
                                                                  c1=1;
                                                                  c2=2;
                                                                 };
                                                                };
                                                                pgi[0]=c0;
                                                                pgi[1]=c1;
                                                                pgi[2]=c2;
};
bool _polygon::gueltig(){
                                                                _vertex*vit0;
                                                                _vertex*vit1;
                                                                _vektor3<_tg> h;
                                                                //---------------------------
                                                               
                                                                if(anfang(vit0))do{
                                                                 vit1=vit0->_listenknotenbasis<_vertex>::naechstes();
                                                                 h=*vit1-*vit0;
                                                                 if(h.laenge()<(nahenull*10)) return(false);
                                                                 //vit0=vit1;
                                                                }while(naechstes(vit0));
                                                                return(true);
                                                                
};

 _vektor3<_tg> _polygon::mitte(){
                                                                if(updated==false){
                                                                 aktualisieren();
                                                                };
                                                                return(pmiddle);
 };
 
  
 _vektor3<_tg> _polygon::normalsector(const _vektor3<_tg> sectormiddle){
                                                                //funktion liefert portalnormale
                                                                //die protalnormale ist so eingestellt,
                                                                //dass sie nach aussen zeigen
                                                                _vektor3<_tg> n;
                                                                _vektor3<_tg> v;
                                                                _tg d;
                                                                //-------------------
                                                                n=ppoly->normale();
                                                                v=mitte()-sectormiddle;
                                                                v.normalisieren();
                                                                d=v*n;
                                                                if(d<0) n*=-1;
                                                                return(n);
 };
 
 _vektor3<_tg> _polygon::normale()const{
                                                                return(ppoly->normale());
 };
  
 _vektor3<_tg> _polygon::normale(const _vertex*vv0,const _vertex*vv1){
                                                                //edgenormale berechnen
                                                                //edgenormalen liegen in der polygonebene 
                                                                //und zeigen immer ins innere
                                                                _vektor3<_tg> v0;
                                                                _vektor3<_tg> v1;
                                                                _vektor3<_tg> n;
                                                                _vektor3<_tg> v;
                                                                _vektor3<_tg> h;
                                                                _vektor3<_tg> dp;
                                                                _vektor3<_tg> dn;
                                                                //-------------
                                                                v0=*vv0;
                                                                v1=*vv1;
                                                                n.setzen(0,0,0);
                                                                v=v1-v0;
                                                                h=mitte()-(v0 + v*0.5);
                                                                v.normalisieren();
                                                                h.normalisieren();
                                                                n=v%ppoly->normale();
                                                                n.normalisieren();
                                                                dp=(n* +1)+h;
                                                                dn=(n* -1)+h;
                                                                if(dn.laenge()>dp.laenge()) n*=-1;
                                                                return(n);
 };
 void _polygon::umgrenzungsquader(_tg&x0,_tg&x1,_tg&y0,_tg&y1,_tg&z0,_tg&z1)const{
                                                                bool init=true;
                                                                _vertex*v;
                                                                if(anfang(v)){
                                                                 do{
                                                                  if(init){
                                                                   init=false;
                                                                   x0=x1=(*v)[0];
                                                                   y0=y1=(*v)[1];
                                                                   z0=z1=(*v)[2];
                                                                  }else{
                                                                   if((*v)[0]<x0) x0=(*v)[0];
                                                                   if((*v)[1]<y0) y0=(*v)[1];
                                                                   if((*v)[2]<z0) z0=(*v)[2];
                                                                   if((*v)[0]>x1) x1=(*v)[0];
                                                                   if((*v)[1]>y1) y1=(*v)[1];
                                                                   if((*v)[2]>z1) z1=(*v)[2];
                                                                  };
                                                                 }while(naechstes(v));
                                                                }else L->schreiben("Fehler : _partition::_polygon::umgrenzungsquader, keine Vertexen vorhanden.");
                                                                
 };
 /*
 bool _polygon::innerhalbpunkt(const _vektor3<_tg>&p){
                                                                bool drin;
                                                                _vektoranalysis3<_tg> V3;
                                                                _vertex*vit;
                                                                _vertex*vin;
                                                                _vektor3<_tg> vn;
                                                                _vektor3<_tg> pn;
                                                                _vektor3<_tg> en;
                                                                _vektor3<_tg> h;
                                                                _tg D,c;
                                                                //-----------------
                                                                drin=true;
                                                                pn=ppoly->normale();
                                                                if(anfang(vit))do{
                                                                 vin=vit->naechstes();
                                                                 vn=*vin-*vit;
                                                                 h=p-(*vit+vn*0.5);
                                                                 vn.normalisieren();
                                                                 en=normale(vit,vin);
                                                                 D=V3.determinieren(vn,pn,en);
                                                                 c=V3.determinieren(vn,pn,h)/D;
                                                                 if(c<0) drin=false;
                                                                }while((naechstes(vit))&&(drin));
                                                                return(drin);
 };
 */
 
 bool _polygon::innerhalbpunkt(const _vektor3<_tg>&p){
                                                                //prüft ob punkt p innerhalb des polygons liegt, 
                                                                //es werden vorberechnete daten benutzt
                                                                //diese funktion ist schnell
                                                                _vertex*vit;
                                                                _tg h[2];
                                                                //-----------------
                                                               // L->schreiben("innerhalbpunkt ------------------------------ start");
                                                                //L->schreiben("p=",p);
                                                                //L->schreiben("pgi[0]=",(int)pgi[0]);
                                                                //L->schreiben("pgi[1]=",(int)pgi[1]);
                                                                //L->schreiben("this->mitte",pmiddle);
                                                                if(anfang(vit))do{
                                                                 //L->schreiben("vit=",(*vit));
                                                                 //L->schreiben("vit.kantemitte0=", vit->kantemitte[0]);
                                                                 //L->schreiben("vit.kantemitte1=", vit->kantemitte[1]);
                                                                 //L->schreiben("vit.kantevektor0=", vit->kantevektor[0]);
                                                                 //L->schreiben("vit.kantevektor1=", vit->kantevektor[1]);
                                                                 //L->schreiben("vit.kantenormale0=", vit->kantenormale[0]);
                                                                 //L->schreiben("vit.kantenormale1=", vit->kantenormale[1]);
                                                                 h[0]=p[pgi[0]] - vit->kantemitte[0];
                                                                 h[1]=p[pgi[1]] - vit->kantemitte[1];
                                                                 //L->schreiben("h[0]=",h[0]);
                                                                 //L->schreiben("h[1]=",h[1]);
                                                                 if((::determinieren2(h,vit->kantevektor)/vit->determinante)<0) {
                                                                  //L->schreiben("innerhalbpunkt ------------------------------ ende false");
                                                                  return(false);
                                                                 };
                                                                }while(naechstes(vit));
                                                                //L->schreiben("innerhalbpunkt ------------------------------ ende true");
                                                                return(true);
 };
  
 bool _polygon::innerhalbkugel(_vektor3<_tg> kugelmitte,_tg radius){
                                                                _vektor3<_tg> lot;
                                                                _vektor3<_tg> lotebene;
                                                                _tg normalenparameter;
                                                                _tg kantenparameter;
                                                                _partition::_vertex*vit;
                                                                _partition::_vertex*vin;
                                                                _vektoranalysis3<_tg> V3;
                                                                //--------
                                                                //1. abstand kugelmitte und ebene : wenn größer radius außerhalb, raus
                                                                V3.lotpunktebene(kugelmitte,mitte(),normale(),lotebene,normalenparameter);
                                                                if(fabs(normalenparameter)>radius) return false;//außerhalb
                                                                //2./3. abstand kugelmitte und vertex und gültiges kantenlot: wenn kleiner radius innerhalb, raus
                                                                if(anfang(vit))do{
                                                                 lot=*vit-kugelmitte;
                                                                 if(lot.laenge()<=radius) return true;//innerhalb
                                                                 vin=vit->naechstes();
                                                                 V3.lotpunktgerade(kugelmitte,*vit,*vin-*vit,lot,kantenparameter);
                                                                 if((kantenparameter>=0)&&(kantenparameter<=1)) if(lot.laenge()<=radius) return true;//innerhalb
                                                                }while(naechstes(vit));
                                                                //4. ebenenlotpunkt prüfen, ob er innerhalb von this ist : wenn ja innerhalb sonst außerhalb
                                                                return(innerhalbpunkt(kugelmitte+lotebene));
 };
 bool _polygon::innerhalbpolygon(::_polygon*poly){
                                                                //untersucht, ob this (portal) in irgendeiner form mit poly schneidet
                                                                //funktion wird zB benutzt um eine polygon - zonen zuordung 
                                                                //durchzuführen für interne additive Sektorpolygonen
                                                                _partition::_vertex*vit;
                                                                _partition::_vertex*vin;
                                                                ::_vertex*pvit;
                                                                ::_vertex*pvin;
                                                                _listenknoten<::_vertex>*lnv;
                                                                _vektor3<_tg> h;
                                                                //_vektor3<_tg> mp;
                                                                _vektor3<_tg> ap;
                                                                _vektor3<_tg> bp;
                                                                //_vektor3<_tg> np;
                                                                _vektor3<_tg> kv;
                                                                _vektor3<_tg> kvi;
                                                                _vektor3<_tg> ko;
                                                                _tg d,HD;
                                                                _tg dstatus=-2;
                                                                _tg gamma;
                                                                _vektoranalysis3<_tg> V3;
                                                                bool schneidetebene=false;
                                                                //untersuchen, ob punkte von this vor UND hinter poly liegen
                                                                //wenn ja genauer untersuchen mit schnittgerade
                                                              
                                                              //aktualisieren();
                                                              
                                                              /*
                                                                np=poly->normale();
                                                                mp=poly->mitte();
                                                                if(anfang(vit))do{
                                                                 //::subtrahieren<_tg>(h,(*vit),mp);
                                                                 h= *vit - mp;
                                                                 d=h*np;
                                                                 if(dstatus==-2){
                                                                  if(fabs(d)<nahenull){
                                                                   schneidetebene=true;
                                                                  }else{
                                                                   if(d>0) dstatus=+1; else dstatus=-1;
                                                                  };
                                                                 }else{
                                                                  if(fabs(d)<=nahenull) schneidetebene=true;
                                                                  if(dstatus==+1){
                                                                   if(d<0) schneidetebene=true;
                                                                  }else{
                                                                   if(d>0) schneidetebene=true;
                                                                  };
                                                                 };
                                                                }while((naechstes(vit))&&(schneidetebene==false));
                                                                */
                                                                
                                                                
                                                                //wir betrachten die ebene des püortals (this) und 
                                                                //die lote der vertex von poly auf this
                                                                //np=poly->normale();
                                                                //mp=poly->mitte();
                                                                //pvit=poly->vertex();
                                                                //if(pvit)do{
                                                                if(poly->anfang(lnv))do{
                                                                 pvit=lnv->objekt();
                                                                
                                                                 h= pvit->ort() - pmiddle;
                                                                 d=h*pnormale;
                                                                 if(dstatus==-2){
                                                                  if(fabs(d)<nahenull){
                                                                   schneidetebene=true;
                                                                  }else{
                                                                   if(d>0) dstatus=+1; else dstatus=-1;
                                                                  };
                                                                 }else{
                                                                  if(fabs(d)<=nahenull) schneidetebene=true;
                                                                  if(dstatus==+1){
                                                                   if(d<0) schneidetebene=true;
                                                                  }else{
                                                                   if(d>0) schneidetebene=true;
                                                                  };
                                                                 };
                                                                 
                                                                 
                                                                // pvit=pvit->naechstes(poly);
                                                                }while((poly->naechstes(lnv))&&(schneidetebene==false));
                                                                
                                                                
                                                                
                                                                
                                                                
                                                                if(schneidetebene){
                                                                 //L->schreiben("einfuegen intern : schneidet ebene");

                                                                      //*********** DEBUG *************
                                                                      /*if(poly->debuggen()){
                                                                       poly->visualisieren();
                                                                       ppoly->visualisieren(_vektor4<_to>(1,0,0,1));
                                                                       visualisieren(psector->zone(),_vektor4<_to>(0,1,1,1));
                                                                       if(psector){
                                                                        if(psector->zone()->debugschirm()) {
                                                                         psector->zone()->debugschirm()->schreiben("Die Normale des Portals (cyan) = ",pnormale,_vektor4<_to>(1,1,1,1));
                                                                         psector->zone()->debugschirm()->schreiben("Die Normale des Polygons (blau) = ",np,_vektor4<_to>(1,1,1,1));
                                                                         psector->zone()->debugschirm()->schreiben("fabs(np*pnromale) = ",fabs(np*pnormale),_vektor4<_to>(1,1,1,1));
                                                                        };
                                                                        psector->zone()->debuganimation();
                                                                       };
                                                                       unvisualisieren();
                                                                       poly->unvisualisieren();
                                                                       ppoly->unvisualisieren();
                                                                      };*/
                                                                      //*******************************                                                                


                                                                 if((fabs(poly->normale()*pnormale))>(1-nahenull)){
                                                                  //---------------------------------------------------------ebenen sind komplanar , gefahr gefahr!----------------------------------------
                                                                  //erstmal prüfen ob punkte innerhalb des anderen poly sind
                                                                  if(anfang(vit))do{
                                                                   if(poly->innerhalbpunkt(*vit))return(true);//nicht optimierte funktion
                                                                  }while(naechstes(vit));
                                                                  //pvit=poly->vertex();
                                                                  //if(pvit)do{
                                                                  iterierenliste(poly,lnv,
                                                                   pvit=lnv->objekt();
                                                                   h=pvit->ort();
                                                                   if(innerhalbpunkt(h)) return(true);
                                                                  );
                                                                  // pvit=pvit->naechstes(poly);
                                                                  //}while(pvit!=poly->vertex());
                                                                  //prüfen ob schnittpunkte zwischen geraden vorliegen
                                                                  _tg k0o[2];
                                                                  _tg k0v[2];
                                                                  _tg k1o[2];
                                                                  _tg k1v[2];
                                                                  _tg kvi2[2];
                                                                  _tg h2[2];
                                                                  _tg g0,g1;
                                                                  if(anfang(vit))do{
                                                                   vin=vit->naechstes();
                                                                   k0o[0]=(*vit)[pgi[0]];
                                                                   k0o[1]=(*vit)[pgi[1]];
                                                                   
                                                                   k0v[0]=(*vin)[pgi[0]]-k0o[0];
                                                                   k0v[1]=(*vin)[pgi[1]]-k0o[1];
                                                                   
                                                                   //pvit=poly->vertex();
                                                                   //if(pvit)do{
                                                                   //pvin=pvit->naechstes(poly);
                                                                   iterierenliste(poly,lnv,
                                                                    pvit=lnv->objekt();
                                                                    pvin=lnv->naechstes()->objekt();
                                                                    k1o[0]=pvit->ort()[pgi[0]];
                                                                    k1o[1]=pvit->ort()[pgi[1]];
                                                                    
                                                                    k1v[0]=pvin->ort()[pgi[0]] - k1o[0];
                                                                    k1v[1]=pvin->ort()[pgi[1]] - k1o[1];
                                                                    
                                                                    kvi2[0]=-k0v[0];
                                                                    kvi2[1]=-k0v[1];
                                                                    HD=::determinieren2<_tg>(k1v,kvi2);
                                                                    if(fabs(HD)>nahenull){
                                                                     ::subtrahieren2<_tg>(h2,k0o,k1o);
                                                                     g0=::determinieren2<_tg>(k1v,h2)/HD;
                                                                     g1=::determinieren2<_tg>(h2,kvi2)/HD;
                                                                     if((g0>=0)&&(g0<=1)){
                                                                      if((g1>=0)&&(g1<=1)){
                                                                       return(true);
                                                                      };
                                                                     };
                                                                    };
                                                                   ); 
                                                                   // pvit=pvin;  
                                                                   //}while(pvit!=poly->vertex());
                                                                   
                                                                  }while(naechstes(vit));
                                                                 }else{
                                                                  //---------------------------------------------------------ebenen sind NICHT komplanar ----------------------------------------

                                                                
                                                                
                                                                  //schneiden die this-kanten (portal kanten) diskret das poly ?
                                                                  ap=poly->ebene(0);
                                                                  bp=poly->ebene(1);
                                                                  if(anfang(vit))do{
                                                                   vin=vit->naechstes();
                                                                   ko=*vit;
                                                                   kv=*vin - *vit;
                                                                   //kv[0]=(*vin)[0]-(*vit)[0];
                                                                   //kv[1]=(*vin)[1]-(*vit)[1];
                                                                   //kv[2]=(*vin)[2]-(*vit)[2];
                                                                   kvi=kv*-1;
                                                                   HD=V3.determinieren(ap,bp,kvi);
                                                                   if(fabs(HD)>nahenull){
                                                                    h=ko-poly->mitte();//::subtrahieren<_tg>(h,ko,mp);
                                                                    gamma=V3.determinieren(ap,bp,h)/HD;
                                                                    if((gamma>=0)&&(gamma<=1)){
                                                                     h=ko+kv*gamma;
                                                                     //::setzen<_tg>(h,kv);
                                                                     //::multiplizieren<_tg>(h,gamma);
                                                                     //::addieren<_tg>(h,ko);
                                                                     //h ist schnittpunkt, prüfen, ob h innerhalb von poly ist
                                                                     if(poly->innerhalbpunkt(h)){

                                                                      return(true);
                                                                     };
                                                                     
                                                                    };
                                                                   };
                                                                  }while(naechstes(vit));
                                                                  //schneiden die poly-kanten die this-fläche (portal-fläche) diskret ?
                                                                  ap=ppoly->ebene(0);
                                                                  bp=ppoly->ebene(1);
                                                                  //mp=pmiddle;
                                                                  //pvit=poly->vertex();
                                                                  //if(pvit)do{
                                                                  // pvin=pvit->naechstes(poly);
                                                                  iterierenliste(poly,lnv,
                                                                   pvit=lnv->objekt();
                                                                   pvin=lnv->naechstes()->objekt();
                                                                   ko=pvit->ort();
                                                                   kv=pvin->ort()-pvit->ort();
                                                                   kvi=kv*-1.0f;
                                                                   //kv[0]=pvin->ort()[0]-pvit->ort()[0];
                                                                   //kv[1]=pvin->ort()[1]-pvit->ort()[1];
                                                                   //kv[2]=pvin->ort()[2]-pvit->ort()[2];
                                                                   //::setzen<_tg>(kvi,kv);
                                                                   //::multiplizieren<_tg>(kvi,-1.0f);
                                                                   HD=V3.determinieren(ap,bp,kvi);
                                                                   if(fabs(HD)>nahenull){
                                                                    //h=ko-pmiddle;//::subtrahieren<_tg>(h,ko,mp);
                                                                    gamma=V3.determinieren(ap,bp,ko-pmiddle)/HD;
                                                                    if((gamma>=0)&&(gamma<=1)){
                                                                     h=ko+kv*gamma;
                                                                     //L->schreiben("dflgjdfklgjfdklgj");
                                                                     //::setzen<_tg>(h,kv);
                                                                     //::multiplizieren<_tg>(h,gamma);
                                                                     //::addieren<_tg>(h,ko);
                                                                     //h ist schnittpunkt, prüfen, ob h innerhalb von poly ist
                                                                     if(innerhalbpunkt(h)) return(true);
                                                                    };
                                                                   };
                                                                  );
                                                                  // pvit=pvin;
                                                                  //}while(pvit!=poly->vertex());
                                                                 };
                                                       
                                                                };
                                                                return(false);
 };
 bool _polygon::innerhalbquadertranslation(const _vektor3<_tg>&start,const _vektor3<_tg>&vektor,const _tg wx,const _tg wy,const _tg wz){
                                                                //untersucht, ob this innerhalb des verschiebungsvolumens ist
                                                                //start ist mittelpunkt des quaders,
                                                                //vektor ist seine bewegung
                                                                //wx,wy,wz ist breite des quaders mit fester ausrichtung an den karthesischen ebenen
                                                                
                                                                
                                                                if((vektor*pnormale)<0) return(false);
                                                                
                                                                
                                                                
                                                                
                                                                return(false);
 };
 bool _polygon::innerhalbkugeltranslation(const _vektor3<_tg>&start,const _vektor3<_tg>&vektor,_tg r){
                                                                if(vektor.laenge()<=0) return(false);
                                                                _tg d1,d2,para,hl,hn,vvv;
                                                                _vektor3<_tg> ende;
                                                                ende=start;
                                                                ende+=vektor;
                                                                //:addieren(ende,start,vektor);
                                                                //-------------------------------------- ebenensabstand untersuchen----------------------------------------
                                                               // ::setzen(n,ppoly->normale());
                                                                //::setzen(m,pmiddle);
                                                                //V3.lotpunktebene(start,pmiddle,ppoly->normale(),startlot,d1);
                                                                //V3.lotpunktebene(ende ,pmiddle,ppoly->normale(),endlot,d2);
                                                                d1=((start[0]-pmiddle[0])*pnormale[0] + (start[1]-pmiddle[1])*pnormale[1] + (start[2]-pmiddle[2])*pnormale[2]);
                                                                d2=((ende[0]-pmiddle[0])*pnormale[0] + (ende[1]-pmiddle[1])*pnormale[1] + (ende[2]-pmiddle[2])*pnormale[2]);
                                                                if((d1>+r)&&(d2>+r)) return(false);//kein schnitt
                                                                if((d1<-r)&&(d2<-r)) return(false);//kein schnitt
                                                                //genauer untersuchen 
                                                                _vektor3<_tg> vertexkante;
                                                                _partition::_vertex*vit;
                                                                _partition::_vertex*vin;
                                                                _tg vix,viy,viz;
                                                                _tg vnx,vny,vnz;
                                                                _vektor3<_tg> lot;
                                                                _vektor3<_tg> h;
                                                                if(anfang(vit))do{
                                                                 //-------------------------------------vertexabstand betrachten--------------------------------------------
                                                                 //l=*vit-ende;
                                                                 //if(l.laenge()<=r) return(true);//Schnitt
                                                                 vix=(*vit)[0];
                                                                 viy=(*vit)[1];
                                                                 viz=(*vit)[2];
                                                                 lot.setzen(vix-ende[0],viy-ende[1],viz-ende[2]);
                                                                 if(lot.laenge()<=r) return(true);//schnitt an polyecke
                                                                 //V3.lotpunktgerade(*vit,start,vektor,l,para);//p ist achsen parameter, ist nur gültig von 0 bis 1
                                                                 //if(l.laenge()<=r) if((para>=0)&&(para<=1)) return(true);//schnitt
                                                                 vvv=vektor.laengelaenge();
                                                                 //vektor[0]*vektor[0] + vektor[1]*vektor[1] + vektor[2]*vektor[2];
                                                                 h.setzen(vix-start[0],viy-start[1],viz-start[2]);
                                                                 para=(h*vektor)/vvv;
                                                                 if((para>=0)&&(para<=1)) {
                                                                  lot.setzen(-h[0]+vektor[0]*para,-h[1]+vektor[1]*para,-h[2]+vektor[2]*para);
                                                                  if(lot.laenge()<=r) return(true);
                                                                 };
                                                                 //---------------------------------vertexkantenabstand betrachten------------------------------------------
                                                                 vin=vit->naechstes();
                                                                 vnx=(*vin)[0];
                                                                 vny=(*vin)[1];
                                                                 vnz=(*vin)[2];
                                                                 //vertexkante=*vin-*vit;
                                                                 vertexkante.setzen(vnx-vix,vny-viy,vnz-viz);
                                                                 //geradenparallelität abfangen
                                                                 //l=vektor%vertexkante;
                                                                 lot=vektor%vertexkante;//::kreuzprodukt<_tg>(l,vektor,vertexkante);
                                                                 if(lot.laenge()>nahenull) {
                                                                  //para=V3.lotgeradegerade(*vit,vertexkante,start,vektor,l);//windschiefes lot
                                                                  h=vertexkante%vektor;//::kreuzprodukt<_tg>(h,vertexkante,vektor);
                                                                  hl=h.laenge();//::magnitude(h);
                                                                  para=((start[0]-vix)*h[0] + (start[1]-viy)*h[1] + (start[2]-viz)*h[2])/hl;
                                                                  if(fabs(para)<=r){
                                                                   hn=para/hl;
                                                                   lot.setzen(h[0]*hn,h[1]*hn,h[2]*hn);
                                                                   unsigned int li=lot.groessterindex();
                                                                   unsigned int i0,i1;
                                                                   if(li==0) {i0=1;i1=2;} else
                                                                   if(li==1) {i0=2;i1=0;} else
                                                                   if(li==2) {i0=0;i1=1;};
                                                                   _tg v0x=vektor[i0]      ,v0y=vektor[i1];
                                                                   _tg v1x=vertexkante[i0], v1y=vertexkante[i1];
                                                                   _tg D2=v1x*-v0y - v1y*-v0x;// D2=|v1,-v0|
                                                                   if(fabs(D2)>nahenull){
                                                                    //_tg o0x=start[i0],       o0y=start[i1];
                                                                    //_tg o1x=(*vit)[i0],        o1y=(*vit)[i1];
                                                                    _tg ex=start[i0]-(*vit)[i0];
                                                                    _tg ey=start[i1]-(*vit)[i1];
                                                                    _tg gamma0=(v1x*ey -  v1y*ex )/D2;
                                                                    if((gamma0>=0)&&(gamma0<=1)){
                                                                     _tg gamma1=(ex*-v0y - ey*-v0x)/D2;
                                                                     if((gamma1>=0)&&(gamma1<=1)) return(true);//schnitt
                                                                    };
                                                                   }else{
                                                                    //parallelität
                                                                    //kann nicht sein, wird vorher abgefangen
                                                                   };
                                                                  };
                                                                 }else{
                                                                  //wird schon vorher gemacht : 
                                                                  //V3.lotpunktgerade(*vit,start,vektor,l,para);
                                                                  //if((para>=0)&&(para<=1)) if(l.laenge()<r) return(true);
                                                                 };
                                                                 //nun kugel ende auf vertexkanten loten
                                                                 //V3.lotpunktgerade(ende,*vit,vertexkante,l,para);
                                                                 //if((para>=0)&&(para<=1)) if(l.laenge()<=r) return(true);//innerhalb
                                                                 vvv=vertexkante.laengelaenge();//vertexkante[0]*vertexkante[0] + vertexkante[1]*vertexkante[1] + vertexkante[2]*vertexkante[2];
                                                                 h.setzen(ende[0]-vix,ende[1]-viy,ende[2]-viz);
                                                                 para=(h*vertexkante)/vvv;
                                                                 if((para>=0)&&(para<=1)) {
                                                                  lot.setzen(-h[0]+vertexkante[0]*para,-h[1]+vertexkante[1]*para,-h[2]+vertexkante[2]*para);
                                                                  if(lot.laenge()<=r) return(true);
                                                                 };
                                                                }while(naechstes(vit));
                                                                //----------------------------- diskretion des reinen ebenenschnitts prüfen ---------------------------
                                                                if(fabs(d1)<fabs(d2)){
                                                                 if(fabs(d1)<=r){
                                                                  _vektor3<_tg> startlot(start[0]+pnormale[0]*-d1,start[1]+pnormale[1]*-d1,start[2]+pnormale[2]*-d1);
                                                                  if(innerhalbpunkt(startlot)) return(true);
                                                                 };
                                                                }else{
                                                                 if(fabs(d2)<=r){
                                                                  _vektor3<_tg> endlot(ende[0]+pnormale[0]*-d2,ende[1]+pnormale[1]*-d2,ende[2]+pnormale[2]*-d2);
                                                                  if(innerhalbpunkt(endlot)) return(true);
                                                                 };
                                                                };
                                                                if(((d1<-r)&&(d2>+r))||((d2<-r)&&(d1>+r))){
                                                                 //es liegt ein ebenen schnitt vor, 
                                                                 //diskretion prüfen
                                                                 _tg inv[3];
                                                                 inv[0]=-vektor[0];
                                                                 inv[1]=-vektor[1];
                                                                 inv[2]=-vektor[2];
                                                                 _tg HD=::determinieren(ppoly->ebene(0).daten(),ppoly->ebene(1).daten(),inv); 
                                                                 if(fabs(HD)>nahenull){//nicht parallel, schnittpunkt holen
                                                                  _tg erg[3];
                                                                  erg[0]=start[0]-pmiddle[0];
                                                                  erg[1]=start[1]-pmiddle[1];
                                                                  erg[2]=start[2]-pmiddle[2];
                                                                  //::subtrahieren(erg,start,m);
                                                                  _tg gamma=::determinieren(ppoly->ebene(0).daten(),ppoly->ebene(1).daten(),erg)/HD;
                                                                  if((gamma>=0)&&(gamma<=1)){
                                                                   _vektor3<_tg> schnitt(start[0]+vektor[0]*gamma,start[1]+vektor[1]*gamma,start[2]+vektor[2]*gamma);
                                                                   if(innerhalbpunkt(schnitt)) return(true);//SCHNITT!!!
                                                                  };
                                                                 }else{
                                                                  //kann eigentlich nicht sein:
                                                                  //parallelität zwischen vektor und polygonebene liegt vor
                                                                  //es reicht EINEN PUNKT ZU PRÜFEN, da vorher keine kanten oder punkteschnitt auftrat !:
                                                                  //V3.lotpunktebene(start,pmiddle,ppoly->normale(),l,para);
                                                                  //if(innerhalbpunkt(start+l)) return(true);//SCHNITT !!
                                                                 };
                                                                };
                                                                /*
                                                                //Es liegt unbedingt ein schnitt mit der ebene vor , es muss diskretion mit der polygonfläche geprüft werden
                                                                _tg HD=V3.determinieren(ppoly->ebene(0),ppoly->ebene(1),-vektor);
                                                                if(fabs(HD)>nahenull){//nicht parallel, schnittpunkt holen
                                                                 _vektor<_tg> nr=-normalsector(psector->mitte())*r;
                                                                 _tg gamma=V3.determinieren(ppoly->ebene(0),ppoly->ebene(1),start-(pmiddle+nr))/HD;
                                                                 _vektor<_tg> schnitt=start+vektor*gamma;
                                                                 //new _weltdebugkreuz(psector->zone()->welt(),schnitt,0.03,_vektor4<_to>(0,0,1,0));
                                                                 if(innerhalbpunkt(schnitt-nr)) return(true);//SCHNITT!!!
                                                                }else{
                                                                 //parallelität zwischen vektor und polygonebene liegt vor
                                                                 //es reicht EINEN PUNKT ZU PRÜFEN, da vorher keine kanten oder punkteschnitt auftrat !:
                                                                 V3.lotpunktebene(start,pmiddle,ppoly->normale(),l,para);
                                                                 if(innerhalbpunkt(start+l)) return(true);//SCHNITT !!
                                                                 
                                                                };*/
                                                                return(false);//KEIN SCHNITT
 };
 bool _polygon::innerhalbpolygontranslation(::_polygon*,const _vektor3<_tg>&start,_liste<_vektor3<_tg> >*orte,const _vektor3<_tg>&vektor){
                                                                return(false);
 };
 bool _polygon::innerhalbnetztranslation(::_netz*,const _vektor3<_tg>&start,const _vektor3<_tg>&vektor){
                                                                return(false);
 };


 bool _polygon::kanteinnerhalbpolygon(const _vektor3<_tg> v0,const _vektor3<_tg> v1){
                                                                //egdev-v1 ist nur dann im poly, 
                                                                //wenn es einen punkt innerhalb der kante gibt, der unscharf
                                                                //innerhalb des polygons liegt
                                                                _vektoranalysis3<_tg> V3;
                                                                _vertex*vit;
                                                                _vertex*vin;
                                                                _vektor3<_tg> vito;
                                                                _vektor3<_tg> vino;
                                                                _vektor3<_tg> av;
                                                                _vektor3<_tg> v;
                                                                _vektor3<_tg> an;
                                                                _vektor3<_tg> e;
                                                                _vektor3<_tg> en;
                                                                _vektor3<_tg> m;
                                                                _vektor3<_tg> h;
                                                                _vektor3<_tg> s;
                                                                _vektor3<_tg> o;
                                                                _tg D;
                                                                _tg c,a;
                                                                _listebasis<_linienintersektion > lislist;
                                                                _linienintersektion*iit;
                                                                bool drin;
                                                                bool exist;
                                                                bool greins;
                                                                bool klnull;
                                                                //--------------------------
                                                                drin=true;
                                                                av=v1-v0;
                                                                an=ppoly->normale();
                                                                m=mitte();
                                                                if(anfang(vit))do{
                                                                 vin=vit->naechstes();
                                                                 e=m-*vit;
                                                                 e.normalisieren();
                                                                 e*=nahenull*2;
                                                                 vito=*vit+e;
                                                                 e=m-*vin;
                                                                 e.normalisieren();
                                                                 e*=nahenull*2;
                                                                 vino=*vin+e;
                                                                 v=vino-vito;
                                                                 D=V3.determinieren(av,an,-v);
                                                                 if(fabs(D)>nahenull){
                                                                  e=vito - v0;
                                                                  c=V3.determinieren(av,an,e)/D;
                                                                  if((c>=0)&&(c<=1)){
                                                                   //schnittpunkt ist diskret mit der kante vito-vino
                                                                   //schnittpunkt einhängen
                                                                   a=V3.determinieren(e,an,-v)/D;
                                                                   s=v0+av*a;
                                                                   exist=false;
                                                                   if(lislist.anfang(iit))do{
                                                                    h=s- *iit;
                                                                    if(h.laenge()<=nahenull) exist=true;
                                                                   }while((lislist.naechstes(iit))&&(exist==false));
                                                                   if(exist==false){
                                                                    new _linienintersektion(&lislist,s,a,0,0);
                                                                   };
                                                                  };
                                                                 }else{
                                                                  //parallel
                                                                  v= *vin - *vit;
                                                                  v.normalisieren();
                                                                  en=v%ppoly->normale();//normale(*vit,*vin);
                                                                  en.normalisieren();
                                                                  D=V3.determinieren(v,ppoly->normale(),en);
                                                                  o=*vit + v*0.5;
                                                                  e=v0 - o;
                                                                  c=V3.determinieren(v,ppoly->normale(),e)/D;
                                                                  if(fabs(c)<=nahenull){
                                                                   //kolinear
                                                                   drin=false;
                                                                  };
                                                                 };
                                                                }while((naechstes(vit))&&(drin));
                                                                if(drin){
                                                                 //schnittpunkte untersuchen
                                                                 if(lislist.anzahl()==0) drin=false; else
                                                                 if(lislist.anzahl()==1) drin=false; else
                                                                 if(lislist.anzahl()>=2){
                                                                  greins=true;
                                                                  klnull=true;
                                                                  if(lislist.anfang(iit))do{
                                                                   if(iit->alpha()<1) greins=false;
                                                                   if(iit->alpha()>0) klnull=false;
                                                                  }while(lislist.naechstes(iit));
                                                                  if((greins==true)&&(klnull==false)) drin=false;
                                                                  if((greins==false)&&(klnull==true)) drin=false;
                                                                 };
                                                                };
                                                                return(drin);
 };
  
 void _polygon::markierungvertex(const int i){
                                                                _vertex*vit;
                                                                //--------------------------
                                                                if(anfang(vit))do{
                                                                 vit->markierung(i);
                                                                }while(naechstes(vit));
 };                                                                
 
 
 
 
 
 void _polygon::teilen(_partition::_polygon*ip,_liste<_partition::_polygon >*divresult){
                                                                //elementare funktion, die sowohl der portalbestimmung dient als auch der sichtbarkeitsermittlung
                                                                //funktion überlagert das intersekting-poly ip mit dem poly-to-intersekt this
                                                                //der schnitt zwischen beiden polygonen ergeben eine liste von konvexen
                                                                //bruchstücken, die, zusammengesetzt die form von this haben 
                                                                //diese liste wird als ergebnis in divresult geschrieben
                                                                _vertex*ivs;
                                                                _vertex*iv0;
                                                                _vertex*iv1;
                                                                _polygon*poly;
                                                                _polygon*frontpoly;
                                                                _polygon*backpoly;
                                                               // bool keinschnitt;
                                                                //-------------------------------
                                                                if((divresult)&&(ip)){
                                                                 divresult->aushaengen();
                                                                 poly=new _partition::_polygon(this);
                                                                 
                                                                 
                                                                // keinschnitt=true;
                                                                 if(ip->anfang(iv0)){
                                                                  ivs=iv0;
                                                                  do{
                                                                   iv1=iv0->naechstes();
                                                                   if(poly->kanteinnerhalbpolygon(*iv0,*iv1)){
                                                                  //  keinschnitt=false;
                                                                    poly->teilen(*iv0,*iv1,ip->normale(iv0,iv1),ip->normale(),frontpoly,backpoly);
                                                                    if((frontpoly)&&(backpoly)){
                                                                     if(iv1==ivs){//letzte kante von ip
                                                                      divresult->einhaengen(backpoly);
                                                                      divresult->einhaengen(frontpoly);
                                                                     }else{
                                                                      divresult->einhaengen(backpoly);
                                                                     };
                                                                     delete poly;
                                                                     poly=frontpoly;
                                                                    }else{
                                                                     //error,sollte nicht passieren
                                                                    };
                                                                   }else{
                                                                    if(iv1==ivs){//letzte kante von ip
                                                                     if(poly) divresult->einhaengen(poly);
                                                                    };
                                                                   };
                                                                  }while(ip->naechstes(iv0));
                                                                 };
                                                                 
                                                                // if(keinschnitt){
                                                                //  divresult->einhaengen(poly);
                                                                // };
                                                                 
                                                                };
 }; 
 
 void _polygon::teilen(const _vektor3<_tg> v0,const _vektor3<_tg> v1,const _vektor3<_tg> en,const _vektor3<_tg> pn,_partition::_polygon*&frontpoly,_partition::_polygon*&backpoly){
                                                                //funktion teilt ein polygon (poly) in zwei Hälften durch
                                                                //die gegebene gerade v0,v1 mit der Kantennormalen en und der polygonnormalen pn
                                                                //es müssen hier zwei polygone rauskommen, die in die resultliste gesteckt werden
                                                                _vektor3<_tg> v;
                                                                _vektor3<_tg> vn;
                                                                _vertex*vit;
                                                                _vertex*vin;
                                                                _vektor3<_tg> schnitt;
                                                                _tg param;
                                                                _vertex*vor;
                                                                _vertex*nach;
                                                                _vektor3<_tg> s;
                                                                _vektor3<_tg> h;
                                                                _tg D,Dv;
                                                                _tg c;
                                                                _vektor3<_tg> e;
                                                                _vektoranalysis3<_tg> V3;
                                                                bool sok;
                                                                bool iok;
                                                                _listebasis<_linienintersektion > lineis;
                                                                _linienintersektion*iit;
                                                                //-----------------------------
                                                                param=0;
                                                                schnitt.setzen(0,0,0);
                                                                vor=0;
                                                                nach=0;
                                                                //result->aushaengen();
                                                                v=v1-v0;
                                                                v.normalisieren();
                                                                vn=v;
                                                                markierungvertex(-2);
                                                                D=V3.determinieren(vn,pn,en);
                                                                Dv=D;
                                                                //--------------------------------------------status bestimmen----------------------------------
                                                                if(anfang(vit))do{
                                                                 e=*vit - v0;
                                                                 c=V3.determinieren(v,pn,e)/D;
                                                                 if(fabs(c)<(nahenull)){
                                                                  vit->markierung(0);
                                                                 }else{
                                                                  if(c>0){
                                                                   vit->markierung(+1);
                                                                  }else{
                                                                   vit->markierung(-1);
                                                                  };
                                                                 };
                                                                }while(naechstes(vit));
                                                                //********** DEBUG **********
                                                                //_vektor4<_to> coll;
                                                                //coll.setzen(1,0,0.5,0);
                                                                //poly->visualisieren(coll);
                                                                //debuganimation();
                                                                //poly->unvisualisieren();
                                                                //***************************
                                                                //--------------------------------------------schnittpunkte bestimmen---------------------------
                                                                //vit + (vin-vit)*c = v0 + pn*a + vn*b
                                                                if(anfang(vit))do{
                                                                 vin=vit->_listenknotenbasis<_vertex>::naechstes();
                                                                 v=*vin - *vit;
                                                                 //v.normalisieren();
                                                                 v*=-1;
                                                                 e=*vit - v0;
                                                                 D=V3.determinieren(pn,vn,v);
                                                                 if(fabs(D)>(nahenull)){
                                                                  //schnittpunkt eindeutig
                                                                  sok=false;
                                                                  c=V3.determinieren(pn,vn,e)/D;
                                                                  v*=-1;
                                                                  s=*vit + v*c;
                                                                  if((c>=0)&&(c<=1)){
                                                                   sok=true;
                                                                   schnitt=s;
                                                                   vor=vit;
                                                                   nach=vin;
                                                                   param=V3.determinieren(schnitt-v0,pn,en)/Dv;
                                                                  };
                                                                  h=s-*vit;
                                                                  if(h.laenge()<=nahenull) {
                                                                   sok=true;
                                                                   schnitt=*vit;
                                                                   vor=vit;
                                                                   nach=vit;
                                                                   param=V3.determinieren(schnitt-v0,pn,en)/Dv;
                                                                  };
                                                                  h=s-*vin;
                                                                  if(h.laenge()<=nahenull) {
                                                                   sok=true;
                                                                   schnitt=*vin;
                                                                   vor=vin;
                                                                   nach=vin;
                                                                   param=V3.determinieren(schnitt-v0,pn,en)/Dv;
                                                                  };
                                                                  if(sok) {
                                                                   iok=true;
                                                                   if(lineis.anfang(iit))do{
                                                                    h=*iit - schnitt;
                                                                    if(h.laenge()<=nahenull) iok=false;
                                                                   }while((lineis.naechstes(iit))&&(iok==true));
                                                                   if(iok) new _linienintersektion(&lineis,schnitt,param,vor,nach);
                                                                  };
                                                                 }else{
                                                                  //parallel
                                                                  c=V3.determinieren(vn,pn,*vit-v0)/Dv;
                                                                  if(fabs(c)<=nahenull){
                                                                   //kolinear - vit einfügen
                                                                   schnitt=*vit;
                                                                   param=V3.determinieren(schnitt-v0,pn,en)/Dv;
                                                                   vor=vit;
                                                                   nach=vit;
                                                                   iok=true;
                                                                   if(lineis.anfang(iit))do{
                                                                    h=*iit - schnitt;
                                                                    if(h.laenge()<=nahenull) iok=false;
                                                                   }while((lineis.naechstes(iit))&&(iok==true));
                                                                   if(iok) new _linienintersektion(&lineis,schnitt,param,vor,nach);
                                                                   //kolinear - vin einfügen
                                                                   schnitt=*vin;
                                                                   param=V3.determinieren(schnitt-v0,pn,en)/Dv;
                                                                   vor=vin;
                                                                   nach=vin;
                                                                   iok=true;
                                                                   if(lineis.anfang(iit))do{
                                                                    h=*iit - schnitt;
                                                                    if(h.laenge()<=nahenull) iok=false;
                                                                   }while((lineis.naechstes(iit))&&(iok==true));
                                                                   if(iok) new _linienintersektion(&lineis,schnitt,param,vor,nach);
                                                                  };
                                                                 };
                                                                }while(naechstes(vit));
                                                                //------------------------------------------auswerten--------------------------------------------
                                                                teilen(&lineis,frontpoly,backpoly);
                                                                //*********** DEBUG ********
                                                                /*_liste<_weltdebugkreuz > lc;
                                                                _vektor4<_to> colf;
                                                                _vektor4<_to> colb;
                                                                colf.setzen(1,0,1,0.8);
                                                                if(lineis.anfang(iit))do{
                                                                 lc.einhaengen(new _weltdebugkreuz(psector->zone()->welt(),*iit,0.1,colf));
                                                                 if(psector->zone()->debugschirm()) psector->zone()->debugschirm()->schreiben("linie-is",colf);
                                                                }while(lineis.naechstes(iit));
                                                                colf.setzen(1,1,0,0.8);
                                                                colb.setzen(0,1,1,0.8);
                                                                frontpoly->visualisieren(psector->zone(),colf);
                                                                backpoly->visualisieren(psector->zone(),colb);
                                                                lc.loeschen();*/
                                                                //**************************
                                                                lineis.loeschen();
                                                               // if(frontpoly) if(!frontpoly->gueltig()) deletesecure(frontpoly);
                                                                //if(backpoly) if(!backpoly->gueltig()) deletesecure(backpoly);
 };
 
 void _polygon::teilen(_listebasis<_linienintersektion >*lineis,_partition::_polygon*&frontpoly,_partition::_polygon*&backpoly){
                                                                _linienintersektion*iit;
                                                                _linienintersektion*s0;
                                                                _linienintersektion*s1;
                                                                _vertex*vit;
                                                                _vertex*vitneg;
                                                                _vertex*vitpos;
                                                                //--------------------------------------
                                                                frontpoly=0;
                                                                backpoly=0;
                                                                if(lineis->anzahl()>=2){//------------------------------- anzahl der intersektion >=2 --------------------------
                                                                 lineis->anfang(iit);
                                                                 s0=iit;
                                                                 lineis->vorheriges(iit);
                                                                 s1=iit;
                                                                 vitneg=0;
                                                                 vitpos=0;
                                                                 if(anfang(vit))do{
                                                                  if(vit->markierung()==-1) if(vitneg==0) vitneg=vit;
                                                                  if(vit->markierung()==+1) if(vitpos==0) vitpos=vit;
                                                                 }while(naechstes(vit));
                                                                 if((vitpos==0)&&(vitneg==0)){
                                                                  //error , unmöglich
                                                                  frontpoly=0;
                                                                  backpoly=0;
                                                                 };
                                                                 if((vitneg!=0)&&(vitpos==0)){
                                                                  //backpoly komplett laden
                                                                  frontpoly=0;
                                                                  backpoly=new _partition::_polygon(this);
                                                                 };
                                                                 if((vitneg==0)&&(vitpos!=0)){
                                                                  //frontpoly komplett laden
                                                                  backpoly=0;
                                                                  frontpoly=new _partition::_polygon(this);
                                                                 };
                                                                 if((vitneg!=0)&&(vitpos!=0)){
                                                                  //positve polygonhälfe herausiterieren
                                                                  frontpoly=new _partition::_polygon(this);
                                                                  frontpoly->loeschenvertex();
                                                                  vit=vitpos;
                                                                  do{
                                                                   new _partition::_vertex(frontpoly,*vit);
                                                                   //nextiteration
                                                                   if(s0->pvprev==vit){
                                                                    if(s0->pvnext==vit){
                                                                     new _partition::_vertex(frontpoly,*s1);
                                                                     if(s1->pvprev==s1->pvnext) {
                                                                      vit=s1->pvnext->_listenknotenbasis<_vertex>::naechstes();
                                                                     }else{
                                                                      vit=s1->pvnext;
                                                                     };
                                                                    }else{
                                                                     new _partition::_vertex(frontpoly,*s0);
                                                                     new _partition::_vertex(frontpoly,*s1);
                                                                     if(s1->pvprev==s1->pvnext) {
                                                                      vit=s1->pvnext->_listenknotenbasis<_vertex>::naechstes();
                                                                     }else{
                                                                      vit=s1->pvnext;
                                                                     };
                                                                    };
                                                                   }else{
                                                                    if(s1->pvprev==vit){
                                                                     if(s1->pvnext==vit){
                                                                      new _partition::_vertex(frontpoly,*s0);
                                                                      if(s0->pvprev==s0->pvnext) {
                                                                       vit=s0->pvnext->_listenknotenbasis<_vertex>::naechstes();
                                                                      }else{
                                                                       vit=s0->pvnext;
                                                                      };
                                                                     }else{
                                                                      new _partition::_vertex(frontpoly,*s1);
                                                                      new _partition::_vertex(frontpoly,*s0);
                                                                      if(s0->pvprev==s0->pvnext) {
                                                                       vit=s0->pvnext->_listenknotenbasis<_vertex>::naechstes();
                                                                      }else{
                                                                       vit=s0->pvnext;
                                                                      };
                                                                     };
                                                                    }else{
                                                                     vit=vit->_listenknotenbasis<_vertex>::naechstes();
                                                                    };
                                                                   };
                                                                  }while(vit!=vitpos);
                                                                  //negative polygonhälfe herausiterieren
                                                                  backpoly=new _partition::_polygon(this);
                                                                  backpoly->loeschenvertex();
                                                                  vit=vitneg;
                                                                  do{
                                                                   new _partition::_vertex(backpoly,*vit);
                                                                   //nextiteration
                                                                   if(s0->pvprev==vit){
                                                                    if(s0->pvnext==vit){
                                                                     new _partition::_vertex(backpoly,*s1);
                                                                     if(s1->pvprev==s1->pvnext) {
                                                                      vit=s1->pvnext->_listenknotenbasis<_vertex>::naechstes();
                                                                     }else{
                                                                      vit=s1->pvnext;
                                                                     };
                                                                    }else{
                                                                     new _partition::_vertex(backpoly,*s0);
                                                                     new _partition::_vertex(backpoly,*s1);
                                                                     if(s1->pvprev==s1->pvnext) {
                                                                      vit=s1->pvnext->_listenknotenbasis<_vertex>::naechstes();
                                                                     }else{
                                                                      vit=s1->pvnext;
                                                                     };
                                                                    };
                                                                   }else{
                                                                    if(s1->pvprev==vit){
                                                                     if(s1->pvnext==vit){
                                                                      new _partition::_vertex(backpoly,*s0);
                                                                      if(s0->pvprev==s0->pvnext) {
                                                                       vit=s0->pvnext->_listenknotenbasis<_vertex>::naechstes();
                                                                      }else{
                                                                       vit=s0->pvnext;
                                                                      };
                                                                     }else{
                                                                      new _partition::_vertex(backpoly,*s1);
                                                                      new _partition::_vertex(backpoly,*s0);
                                                                      if(s0->pvprev==s0->pvnext) {
                                                                       vit=s0->pvnext->_listenknotenbasis<_vertex>::naechstes();
                                                                      }else{
                                                                       vit=s0->pvnext;
                                                                      };
                                                                     };
                                                                    }else{
																	 vit=vit->_listenknotenbasis<_vertex>::naechstes();
                                                                    };
                                                                   };
                                                                  }while(vit!=vitneg);
                                                                 };
                                                                }else{//------------------------------------ anzahl der ontersections <2 ----------------------------
                                                                 vitneg=0;
                                                                 vitpos=0;
                                                                 if(anfang(vit))do{
                                                                  if(vit->markierung()==-1) if(vitneg==0) vitneg=vit;
                                                                  if(vit->markierung()==+1) if(vitpos==0) vitpos=vit;
                                                                 }while(naechstes(vit));
                                                                 if((vitpos==0)&&(vitneg==0)){
                                                                  //error , unmöglich
                                                                  frontpoly=0;
                                                                  backpoly=0;
                                                                 };
                                                                 if((vitneg!=0)&&(vitpos==0)){
                                                                  //backpoly komplett laden
                                                                  frontpoly=0;
                                                                  backpoly=new _partition::_polygon(this);
                                                                 };
                                                                 if((vitneg==0)&&(vitpos!=0)){
                                                                  //frontpoly komplett laden
                                                                  backpoly=0;
                                                                  frontpoly=new _partition::_polygon(this);
                                                                 };
                                                                };
                                                                //---------------------------------------------------------------------------------------------------
                                                                if(frontpoly) frontpoly->aktualisieren();
                                                                if(backpoly) backpoly->aktualisieren();
 }; 
 
 char _polygon::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_polygon>*sd){
                                                                char r=1;
                                                                unsigned int cp,i;
                                                                r^=sd->ladenbeginn(fn);
                                                                r^=sd->ladenverschachtelung(fn);
                                                                r^=sd->ladenwert(pisportal);
                                                                //r^=sd->ladenwert(updated);
                                                                r^=sd->ladenwert(pmiddle);
                                                                _liste<_partition::_polygon >::aushaengen();
                                                                r^=sd->ladenwert(cp);
                                                                for(i=0;i<cp;i++){
                                                                 r^=sd->ladenassoziation();
                                                                 _liste<_partition::_polygon >::einhaengen(0);
                                                                };
                                                                r^=sd->ladenassoziation();
                                                                sd->ladenende();
                                                                return(r);
 };
 
 void _polygon::speichern(_speicherbardynamisch<_polygon>*sd){
                                                                unsigned int cp,i;
                                                                _listenknoten<_polygon >*pit;
                                                                //------------------------
                                                                sd->speichernbeginnblock();
                                                                sd->speichernverschachtelung();
                                                                sd->speichernwert(pisportal);
                                                                //sd->speichernwert(updated);
                                                                sd->speichernwert(pmiddle);
                                                                cp=_liste<_partition::_polygon >::anzahl();
                                                                sd->speichernwert(cp);
                                                                anfang(pit);
                                                                for(i=0;i<cp;i++){
                                                                 saveassociationargument(sd->datei(),sd,pit->objekt());
                                                                 naechstes(pit);
                                                                };
                                                                saveassociationargument(sd->datei(),sd,ppoly);
                                                                sd->speichernendeblock();
                                                                 
 };
 
 char _polygon::assoziieren(_speicherbardynamisch<_polygon>*sd){
                                                                unsigned int cp,i;
                                                                _listenknoten<_polygon >*pit;
                                                                _polygon*p;
                                                                //-----------------
                                                                sd->assoziierenverschachtelung();
                                                                cp=_liste<_partition::_polygon >::anzahl();
                                                                anfang(pit);
                                                                for(i=0;i<cp;i++){
                                                                 associateassociationargument(sd->datei(),sd->assoziation(),p);
                                                                 pit->objekt(p);
                                                                 naechstes(pit);
                                                                };
                                                                associateassociationargument(sd->datei(),sd->assoziation(),ppoly);
                                                                return(1);
 };
 bool _polygon::laden(_dateispeicherbarbinaer*d){
																einhaengenspeicherung(d);
																ladenbeginn();
																d->laden(speichername());
																unsigned int a,i;

																a=ladenanzahl(d);
																for(i=0;i<a;i++) ladenzeiger(d);

																ladenzeiger(d);
																d->laden(pisportal);
																d->laden(updated);
																d->laden(pmiddle);
																d->laden(pnormale);
																d->laden(pgi[0]);
																d->laden(pgi[1]);
																d->laden(pgi[2]);

																d->laden(a);
																_listebasis<_partition::_vertex>::loeschen();
																for(i=0;i<a;i++){
																 _vertex*vit=new _partition::_vertex(this,_vektor3<_tg>(0,0,0));
																 vit->laden(d);
																};

																return(true);
 };
 void _polygon::speichern(_dateispeicherbarbinaer*d){
																d->speichern(speichername());


																_listenknoten<_partition::_polygon>*lnpit;
																d->speichern(_liste<_partition::_polygon >::anzahl());
																iterieren(lnpit,speichernzeiger(d,lnpit->objekt()));

																speichernzeiger(d,ppoly);
																d->speichern(pisportal);
																d->speichern(updated);
																d->speichern(pmiddle);
																d->speichern(pnormale);
																d->speichern(pgi[0]);
																d->speichern(pgi[1]);
																d->speichern(pgi[2]);


																_partition::_vertex*vit;
																d->speichern(_listebasis<_partition::_vertex>::anzahl());
																iterieren(vit,vit->speichern(d));

 };
 bool _polygon::assoziieren(){
																if(zeigergeladen()){
																 unsigned int i,a;
																 a=ladenanzahl();
																 for(i=0;i<a;i++) {
																  _partition::_polygon*p;
																  assoziierenzeiger(p);
																  _liste<_partition::_polygon>::einhaengen(p);
																 };
																 assoziierenzeiger(ppoly);
																 loeschenzeiger();
																};
																return(true);
 };  
  
 void _polygon::visualisieren(_zone*zit,_vektor4<_to> col){
                                                                //ifpsector->zone()->debugschirm()->schreiben("fff",_vektor4<_to>(1,0,0,1));
                                                                _vertex*vit;
                                                                _vertex*vin;
                                                                _vektor4<_to> pcol;
                                                                _vektor3<_tg> vt;
                                                                _vektor3<_tg> vn;
                                                                _vektor3<_tg> n;
                                                                _listenknoten<_polygon >*lpit;
                                                                //-------------
                                                                //col.setzen(1,1,0);
                                                                if(pisportal) {
                                                                 //col.setzen(col[0],1,col[2]);
                                                                 if(anfang(lpit)==false){//verknüpfung fehlt
                                                                  col.setzen(1,0,1,0.5);
                                                                 };
                                                                };
                                                                
                                                                
                                                                unvisualisieren();
                                                                if(anfang(vit)){
                                                                 do{
                                                                  vin=vit;
                                                                  naechstes(vin);
                                                                  vt=mitte()-*vit;
                                                                  vt.normalisieren();
                                                                  vt*=0.05;
                                                                  vn=mitte()-*vin;
                                                                  vn.normalisieren();
                                                                  vn*=0.05;
                                                                  if(psector){
                                                                   if(pisportal){
                                                                    n=normalsector(psector->mitte())*-1;
                                                                   }else{
                                                                    n=ppoly->normale();
                                                                   };
                                                                  }else{
                                                                   n.setzen(0,0,0);
                                                                  };
                                                                 
                                                                  pdbarrows.einhaengen(new _weltdebugpfeil(zit->welt(),*vit+vt+n*0.02,*vin+vn+n*0.02,0.03,0.01,col));
                                                               //   pdbarrows.einhaengen(new _weltdebugpfeil(zit->welt(),*vit+vt+n*0.02,mitte()+n*0.02,0.03,0.01,col));
                                                                  if(vit->markierung()==-1) pcol.setzen(0,0,1,0.5);
                                                                  if(vit->markierung()==0) pcol.setzen(0.5f,0.5f,0.5f,0.5);
                                                                  if(vit->markierung()==+1) pcol.setzen(1,0,0,0.5);
                                                                  //pdbcrosses.einhaengen(new _weltdebugkreuz(W,*vit,0.1,pcol));
                                                                 
                                                                 }while(naechstes(vit));
                                                                }else{
                                                                 if(zit->debugschirm()) zit->debugschirm()->schreiben("Fehler : beim Versuch ein partition::polygon zu visualisieren : keine Vertex vvorhanden.",_vektor4<_to>(1,0,0,1));
                                                                 
                                                                };
                                                                col.setzen(0.7f,0.7f,0.7f,0.5);
                                                                if(psector)pdbcrosses.einhaengen(new _weltdebugkreuz(psector->zone()->welt(),mitte()+n*0.02,0.1,pcol));

 };
  
 void _polygon::unvisualisieren(){
                                                                pdbarrows.loeschen();
                                                                pdbcrosses.loeschen();
 };
};
//******************************************************************************************************************************************************************************************************
//                                                              P A R T I T I O N   : :   V E R T E X 
//******************************************************************************************************************************************************************************************************
namespace _partition{
 _vertex::_vertex(_polygon*p,_vektor3<_tg> o):_vektor3<_tg>(o),_listenknotenbasis<_vertex >(p){
                                                                ppoly=p;
                                                                pflag=0;
                                                                ppoly->unaktualisieren();
                                                              //  L->schreiben("sektorvertex wurde angelegt");
 };
  _vertex::~_vertex(){
 };
 int _vertex::markierung()const{
                                                                return(pflag);
 };
 void _vertex::markierung(const int i){
                                                                pflag=i;
 };
 char _vertex::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_vertex>*sd){
                                                                char r=1;
                                                                r^=sd->ladenbeginn(fn);
                                                                r^=sd->ladenverschachtelung(fn);
                                                                r^=sd->ladenwert(*this);
                                                                r^=sd->ladenwert(pflag);
                                                                sd->ladenende();
                                                                return(r);
 };
 void _vertex::speichern(_speicherbardynamisch<_vertex>*sd){
                                                                sd->speichernbeginn();
                                                                sd->speichernverschachtelung();
                                                                sd->speichernwert(*this);
                                                                sd->speichernwert(pflag);
                                                                sd->speichernende();
 };
 char _vertex::assoziieren(_speicherbardynamisch<_vertex>*sd){
                                                                sd->assoziierenverschachtelung();
                                                                return(1);
 };
 bool _vertex::laden(_dateispeicherbarbinaer*d){
																einhaengenspeicherung(d);
																ladenbeginn();
																d->laden(speichername());
																d->laden((_vektor3<_tg>)(*this));
																d->laden(pflag);
																d->laden(determinante);
																d->laden(kantenormale[0]);
																d->laden(kantenormale[1]);
																d->laden(kantevektor[0]);
																d->laden(kantevektor[1]);
																d->laden(kantemitte[0]);
																d->laden(kantemitte[1]);
																return(true);
 };
 void _vertex::speichern(_dateispeicherbarbinaer*d){
																d->speichern(speichername());
																d->speichern((_vektor3<_tg>)(*this));
																d->speichern(pflag);
																d->speichern(determinante);
																d->speichern(kantenormale[0]);
																d->speichern(kantenormale[1]);
																d->speichern(kantevektor[0]);
																d->speichern(kantevektor[1]);
																d->speichern(kantemitte[0]);
																d->speichern(kantemitte[1]);
 };
 bool _vertex::assoziieren(){
																if(zeigergeladen()){
																 loeschenzeiger();
																};
																return(true);
 }; 
};
//******************************************************************************************************************************************************************************************************
//                                                              P A R T I T I O N   : :   S I C H T B A R K E I T S V O L U M E N
//******************************************************************************************************************************************************************************************************
namespace _partition{
 _sichtbarkeitsvolumen::_sichtbarkeitsvolumen(_zone*z,_polygon*pv,_vektor3<_tg> ns,_polygon*p,_vektor3<_tg> nt){
                                                                pzone=z;
                                                                ppolygontarget=p;
                                                                ppolygonsource=pv;
                                                                pnsource=ns;
                                                                pntarget=nt;
                                                                pmiddle=(ppolygontarget->mitte()+ppolygonsource->mitte())*0.5;
                                                                createplane(ppolygonsource,pnsource,ppolygontarget,pntarget);//dreiecke von source nach target
                                                                createplane(ppolygontarget,pntarget,ppolygonsource,pnsource);//dreiecke von target nach source
                                                                clearredundantplane();
 };                                                                
 
 void _sichtbarkeitsvolumen::createplane(_polygon*psource,_vektor3<_tg> nsource,_polygon*ptarget,_vektor3<_tg> ntarget){
                                                                _vektor3<_tg> h;
                                                                _vektor3<_tg> n;
                                                                _vektor3<_tg> ev;
                                                                _vektor3<_tg> em;
                                                                _vektor3<_tg> en;
                                                                _vektor3<_tg> eb;
                                                                _partition::_vertex*v0;
                                                                _partition::_vertex*v1;
                                                                _partition::_vertex*vit;
                                                                _partition::_vertex*vib;
                                                                _tg c;
                                                                _listesortiert<_vertex,_tg> lvn;
                                                                _listesortiert<_vertex,_tg> lvd;
                                                                _listenknotensortiert<_vertex,_tg>*lvfi;
                                                                _listenknotensortiert<_vertex,_tg>*lvit;
                                                                bool triok;
                                                                //----------------------------
                                                                if(psource->anfang(v0))do{
                                                                 v1=v0;
                                                                 psource->naechstes(v1);
                                                                 ev=*v1-*v0;
                                                                 ev.normalisieren();
                                                                 em=(*v0+(*v1-*v0)*0.5);
                                                                 en=ev%nsource;
                                                                 en.normalisieren();
                                                                 h=em-psource->mitte();
                                                                 h.normalisieren();
                                                                 if((en*h)<0) en*=-1;
                                                                 vib=0;
                                                                 if(ptarget->anfang(vit))do{
                                                                  eb=*vit-*v0;
                                                                  if(eb.laenge()>nahenull){
                                                                   eb.normalisieren();
                                                                   n=eb%ev;
                                                                   if(n.laenge()>nahenull){
                                                                    n.normalisieren();
                                                                    h=((*v0+*v1+*vit)*(_tg(1)/_tg(3)))-psource->mitte();
                                                                    h.normalisieren();
                                                                    c=h*n;
                                                                    if(c<-nahenull){
                                                                     n*=-1;
                                                                    }else
                                                                    if((c>=-nahenull)&&(c<nahenull)){
                                                                     //das dreieck v0-v1-vit ist komplanar zu polygonsource, 
                                                                     //untersuchen ob vit vor oder
                                                                     //hinter der kante v0 - v1 liegt, wenns dahinter
                                                                     //liegt, muss die normale nsource sein , sonst nsource*-1
                                                                     h=*vit-em;
                                                                     h.normalisieren();
                                                                     if((en*h)<0) n=nsource; else n=nsource*-1;
                                                                    };
                                                                    //achtung: nun die komplanarität des dreiecks mit dem target 
                                                                    //untersuchen, wenn komplanarität auftritt, dann wird untersucht, 
                                                                    //ob das dreieck vor oder hinter der vertexnormalen liegt. 
                                                                    //wenn dahinter, dreiecki sperren
                                                                    h=*vit-em;
                                                                    if(h.laenge()>nahenull){
                                                                     triok=true;
                                                                     h.normalisieren();
                                                                     c=h*ntarget;
                                                                     if(fabs(c)<nahenull){
                                                                      //dreieck ist definitiv komplanar mit target polygon
                                                                      if(prufengueltigkeit(v0,v1,vit,n,ptarget)==false) triok=false;
                                                                     };
                                                                     if(triok){
                                                                      c=n*(nsource*-1);
                                                                      lvn.einhaengen(vit,c);
                                                                     };
                                                                    };
                                                                   };
                                                                  };
                                                                 }while(ptarget->naechstes(vit));
                                                                 if(lvn.anfang(lvfi)){
                                                                  lvn.vorheriges(lvfi);//den größten holen
                                                                  if(lvn.anfang(lvit))do{
                                                                   c=lvit->kriterium()-lvfi->kriterium();
                                                                   if(fabs(c)<=nahenull){
                                                                    h=*lvit->objekt()-em;
                                                                    lvd.einhaengen(lvit->objekt(),h.laenge());
                                                                    //****************** DEBUG *****************
                                                                    //_vektor4<_to> col;
                                                                    //col.setzen(1,1,0,0);
                                                                    //pzone->debugschirm()->schreiben("B",col);
                                                                    //******************************************
                                                                   };
                                                                  }while(lvn.naechstes(lvit));
                                                                 };
                                                                 if(lvd.anfang(lvfi)){
                                                                  vib=lvfi->objekt();
                                                                 };
                                                                 lvn.aushaengen();
                                                                 lvd.aushaengen();
                                                                 if(vib){
                                                                  new _sichtbarkeitsebene(this,v0,v1,vib);
                                                                 }else{
                                                                  _vektor4<_to> col;
                                                                  col.setzen(0.3f,0.7f,0.6f,0);
                                                                  if(pzone->debugschirm()) pzone->debugschirm()->schreiben("zu einer Portalkante konnte kein dreieck aufgespannt werden.",col);
                                                                 };
                                                                }while(psource->naechstes(v0));
 };                                             
 
 _sichtbarkeitsvolumen::~_sichtbarkeitsvolumen(){
                                                                unvisualisieren();
 };
 
 _zone*_sichtbarkeitsvolumen::zone(){
                                                                return(pzone);
 };
_polygon*_sichtbarkeitsvolumen::ziel(){
                                                                return(ppolygontarget);
};
_vektor3<_tg> _sichtbarkeitsvolumen::zielnormale()const{
                                                                return(pntarget);
};

 
 bool _sichtbarkeitsvolumen::prufengueltigkeit(_vertex*v0,_vertex*v1,_vertex*vt,_vektor3<_tg> normale,_polygon*pt){
                                                                //nur für komplanare situationen gedacht
                                                                bool valid;
                                                                bool inner;
                                                                _vektoranalysis3<_tg> V3;
                                                                _vektor3<_tg> e;
                                                                _vektor3<_tg> m;
                                                                _vektor3<_tg> mt;
                                                                //---------
                                                                //prüfen, ob vt auf der geraden v0-v1 liegt
                                                                V3.lotpunktgerade(*vt,*v0,*v1-*v0,e);
                                                                if(e.laenge()>nahenull){
                                                                 valid=true;
                                                                 if(pt->kanteinnerhalbpolygon(*v0,*vt)) valid=false; else
                                                                 if(pt->kanteinnerhalbpolygon(*v1,*vt)) valid=false; else{
                                                                  //ist polygon mitte innerhalb des dreiecks?
                                                                  //raumgleichung m=o+ev*a+normale
                                                                  mt=pt->mitte();
                                                                  m =((*v0+*v1+*vt)*(_tg(1)/_tg(3)));
                                                                  inner=true;
                                                                  if(pruefenfront(mt,*v0,*v1,normale,m)==false) inner=false; else
                                                                  if(pruefenfront(mt,*v1,*vt,normale,m)==false) inner=false; else
                                                                  if(pruefenfront(mt,*vt,*v0,normale,m)==false) inner=false; 
                                                                  if(inner) valid=false;
                                                                 };
                                                                 return(valid);
                                                                }else{
                                                                 return(false);
                                                                };
 };
 
 bool _sichtbarkeitsvolumen::pruefenfront(_vektor3<_tg> p,_vektor3<_tg> v0,_vektor3<_tg> v1,_vektor3<_tg> n,_vektor3<_tg> m){
                                                                //nur für komplanare situationen gedacht
                                                                //ist punkt p vor der kante v0-v1 mit n und m ?
                                                                bool front;
                                                                _vektor3<_tg> en;
                                                                _vektor3<_tg> v;
                                                                _vektor3<_tg> h;
                                                                //---------------
                                                                v=v1-v0;
                                                                en=v%n;
                                                                en.normalisieren();
                                                                h=v0-m;
                                                                h.normalisieren();
                                                                if((h*en)>0) en*=-1;
                                                                h=v0-p;
                                                                h.normalisieren();
                                                                if((en*h)>0) front=true; else front=false;
                                                                return(front);
 };
 
 void _sichtbarkeitsvolumen::clearredundantplane(){
                                                                _liste<_liste<_sichtbarkeitsebene > > llvp;
                                                                _listenknoten<_liste<_sichtbarkeitsebene > >*llvpit;
                                                                _sichtbarkeitsebene*pit;
                                                                _liste<_sichtbarkeitsebene >*exist;
                                                                _listenknoten<_sichtbarkeitsebene >*lit;
                                                                int c;
                                                                //-------------------------
                                                                if(anfang(pit))do{
                                                                 exist=0;
                                                                 if(llvp.anfang(llvpit))do{
                                                                  if(llvpit->objekt()->anfang(lit))do{
                                                                   if(fabs((lit->objekt()->pnormal*pit->pnormal)-1)<=nahenull) exist=llvpit->objekt();
                                                                  }while((llvpit->objekt()->naechstes(lit))&&(exist==0));
                                                                 }while((llvp.naechstes(llvpit))&&(exist==0));
                                                                 if(exist){
                                                                  exist->einhaengen(pit);
                                                                 }else{
                                                                  exist=new _liste<_sichtbarkeitsebene >();
                                                                  llvp.einhaengen(exist);
                                                                  exist->einhaengen(pit);
                                                                 };
                                                                }while(naechstes(pit));
                                                                //redundante löschen
                                                                if(llvp.anfang(llvpit))do{
                                                                 exist=llvpit->objekt();
                                                                 c=0;
                                                                 if(exist->anfang(lit))do{
                                                                  if(c>0) lit->loeschmarkierungobjekt(true);
                                                                  c++;
                                                                 }while(exist->naechstes(lit));
                                                                 exist->loeschenmarkiert();
                                                                }while(llvp.naechstes(llvpit));
                                                                llvp.aushaengen();
 };
 
 _partition::_polygon* _sichtbarkeitsvolumen::innerhalb(_partition::_polygon*portal){
                                                                //weltpoly poly an der polygonsource-ebene abschneiden
                                                                //weltpoly poly an der polygontarget-ebene abschneiden
                                                                //weltpoly poly iterativ an den volumen-ebenen abschneiden
                                                                _polygon*phs;
                                                                _polygon*ph0;
                                                                _polygon*ph1;
                                                                _polygon*ph2;
                                                                _sichtbarkeitsebene*vit;
                                                                _vektor3<_tg> h;
                                                                _vektor3<_tg> o;
                                                                _vektor3<_tg> n;
                                                                _vektor3<_tg> p0;
                                                                _vektor3<_tg> p1;
                                                                bool stop;
                                                                _vektor<_tg> proj;
                                                                //********DEBUG************
                                                                _vektor4<_to> col;
                                                                bool vis=pzone->welt()->debuggensichtbarkeit();
                                                                if(vis) visualisieren(_vektor4<_to>(1,0,0,1),_vektor4<_to>(1,0,0,1),_vektor4<_to>(1,0,0,1));
                                                                //if(ppolygontarget->polygon()->debuggen()) vis=true;
                                                                //_vektor4<_to> pc;
                                                                //*************************
                                                                //----------------------------
                                                                phs=0;
                                                                ph0=0;
                                                                ph1=0;
                                                                ph2=0;
                                                                phs=new _partition::_polygon(portal);
                                                                phs->portal(false);
                                                                //********DEBUG************
                                                                if(vis){
                                                                 col.setzen(1,0,1,0);
                                                                 phs->visualisieren(pzone,col);
                                                                 pzone->debuganimation();
                                                                 phs->unvisualisieren();
                                                                };
                                                                //*************************
                                                                ph0=schneidenebene(phs,ppolygonsource->mitte(),pnsource,ppolygonsource->polygon()->ebene(0),ppolygonsource->polygon()->ebene(1));
                                                                //L->schreiben("schneidenebene pnsource=",pnsource);
                                                                if(ph0){
                                                                 //********DEBUG************
                                                                 if(vis){
                                                                  col.setzen(0,1,0,0);
                                                                  ph0->visualisieren(pzone,col);
                                                                  pzone->debugschirm()->schreiben("Schnitt mit Quell-Ebene passiert.",col);
                                                                  pzone->debuganimation();
                                                                  ph0->unvisualisieren();
                                                                 };
                                                                 //*************************
                                                                 ph1=schneidenebene(ph0,ppolygontarget->mitte(),pntarget,ppolygontarget->polygon()->ebene(0),ppolygontarget->polygon()->ebene(1));
                                                                 if(ph1){
                                                                  //********DEBUG************
                                                                  if(vis){
                                                                   col.setzen(0,0,1,0);
                                                                   pzone->debugschirm()->schreiben("Schnitt mit Ziel-Ebene passiert.",col);
                                                                   ph1->visualisieren(pzone,col);
                                                                   pzone->debuganimation();
                                                                   ph1->unvisualisieren();
                                                                  };
                                                                  //*************************
                                                                  stop=false;
                                                                  if(anfang(vit))do{
                                                                   ph2=schneidenebene(ph1,vit->pmiddle,vit->pnormal,vit->pplane[0],vit->pplane[1]);
                                                                   if(ph2){
                                                                    delete ph1;
                                                                    ph1=ph2;
                                                                    ph2=0;
                                                                   }else{
                                                                    stop=true;
                                                                   };
                                                                  }while((naechstes(vit))&&(stop==false));
                                                                  if(stop==false){
                                                                   ph2=new _partition::_polygon(ph1);
                                                                   //********DEBUG************
                                                                   if(vis){
                                                                    col.setzen(1,0,0,0);
                                                                    pzone->debugschirm()->schreiben("Schnitt mit Konus-Ebenen passiert.",col);
                                                                    ph2->visualisieren(pzone,col);
                                                                    pzone->debuganimation();
                                                                    ph2->unvisualisieren();
                                                                   };
                                                                   //*************************
                                                                  }; 
                                                                  delete ph1;ph1=0;
                                                                 };
                                                                 delete ph0;ph0=0;
                                                                };
                                                                //********DEBUG************
                                                                //col.setzen(1,0.5,1,0);
                                                                //visualisieren(col);
                                                                //pzone->debuganimation();
                                                                //pwelt->unvisualisieren();
                                                                if(vis)unvisualisieren();
                                                                //*************************
                                                                delete phs;phs=0;
                                                                //ja: deep into the code, das ist hier !
                                                                return(ph2);                
 };
 
 _polygon*  _sichtbarkeitsvolumen::schneidenebene(_partition::_polygon*welt,_vektor3<_tg> o,_vektor3<_tg> n,_vektor3<_tg> p0,_vektor3<_tg> p1){
                                                                _partition::_polygon*frontpoly;
                                                                _partition::_polygon*backpoly;
                                                                _tg D0;
                                                                _tg D1;
                                                                _tg D,a;
                                                                _vektor3<_tg> wp;
                                                                _vektoranalysis3<_tg> V3;
                                                                _vektor3<_tg> schnitt;
                                                                _vektor3<_tg> vektor;
                                                                //---------------------------------
                                                                frontpoly=0;
                                                                backpoly=0;
                                                                D0=V3.determinieren(p0,p1,-welt->polygon()->ebene(0));
                                                                D1=V3.determinieren(p0,p1,-welt->polygon()->ebene(1));
                                                                if(fabs(D0)>fabs(D1)){ 
                                                                 D=D0; 
                                                                 wp=welt->polygon()->ebene(0);
                                                                }else{
                                                                 D=D1;
                                                                 wp=welt->polygon()->ebene(1);
                                                                };
                                                                if(fabs(D)>nahenull){
                                                                 //schräg
                                                                 a=V3.determinieren(p0,p1,welt->mitte()-o)/D;
                                                                 schnitt=welt->mitte()+wp*a;
                                                                 vektor=n%welt->normale();
                                                                 vektor.normalisieren();
                                                                 welt->teilen(schnitt,schnitt+vektor,n,welt->normale(),frontpoly,backpoly);
                                                                }else{
                                                                 //parallel
                                                                 D=V3.determinieren(n,p0,p1);
                                                                 if(D){
                                                                  a=V3.determinieren(welt->mitte()-o,p0,p1)/D;
                                                                  if(a<-nahenull) {
                                                                   //komplanar oder dahinter
                                                                   frontpoly=0;
                                                                  }else{
                                                                   //parallel davor
                                                                   frontpoly=new _partition::_polygon(welt);
                                                                  };
                                                                 }else{
                                                                  //error
                                                                 };
                                                                };
                                                                if(backpoly){
                                                                 delete backpoly;
                                                                 backpoly=0;
                                                                };
                                                                 //******DEBUG**********
                                                                 //_vektor4<_to> col;
                                                                 //col.setzen(1,1,1,0);
                                                                 //pzone->debugschirm()->schreiben("teilen ueberlebt",col);
                                                                 //if(frontpoly) pzone->debugschirm()->schreiben("frontpolygesetzt",col);
                                                                 //if(backpoly) pzone->debugschirm()->schreiben("rueck polygesetzt",col);
                                                                 //pzone->debuganimation();
                                                                 //********************* 
                                                                return(frontpoly);
 };
 
 _vektor3<_tg> _sichtbarkeitsvolumen::mitte() const{
                                                                return(pmiddle);
 };
 
 void  _sichtbarkeitsvolumen::visualisieren(_vektor4<_to> coln,_vektor4<_to> col,_vektor4<_to> colr){
                                                                _sichtbarkeitsebene*pit;
                                                                //----------------------------------------------------
                                                                unvisualisieren();
                                                                ppolygontarget->visualisieren(pzone,coln);
                                                                ppolygonsource->visualisieren(pzone,coln);
                                                                if(anfang(pit))do{
                                                                 pit->visualisieren(colr);
                                                                }while(naechstes(pit));
 };
 
 void _sichtbarkeitsvolumen::unvisualisieren(){
                                                                _sichtbarkeitsebene*pit;
                                                                //----------------------------------------------------
                                                                if(anfang(pit))do{
                                                                 pit->unvisualisieren();
                                                                }while(naechstes(pit));
                                                                ppolygontarget->unvisualisieren();
                                                                ppolygonsource->unvisualisieren();
 };

};
//******************************************************************************************************************************************************************************************************
//                                                              P A R T I T I O N   : :   S I C H T B A R K E I T S E B E N E 
//******************************************************************************************************************************************************************************************************
namespace _partition{
 _sichtbarkeitsebene::_sichtbarkeitsebene(_sichtbarkeitsvolumen*v,_vertex*pv0,_vertex*pv1,_vertex*pv2):_listenknotenbasis<_sichtbarkeitsebene >(v){
                                                                pvertex[0]=pv0;
                                                                pvertex[1]=pv1;
                                                                pvertex[2]=pv2;
                                                                pvolume=v;
                                                                aktualisieren();
 };
 _sichtbarkeitsebene::~_sichtbarkeitsebene(){
                                                                unvisualisieren();
 };
 void _sichtbarkeitsebene::aktualisieren(){
                                                                _vektor3<_tg> v[3];
                                                                _vektor3<_tg> h;
                                                                //------------------
                                                                pmiddle=(*pvertex[0]+*pvertex[1]+*pvertex[2])*(_tg(1)/_tg(3));
                                                                v[0]=*pvertex[1]-*pvertex[0];
                                                                v[1]=*pvertex[2]-*pvertex[1];
                                                                v[2]=*pvertex[0]-*pvertex[2];
                                                                v[0].normalisieren();
                                                                v[1].normalisieren();
                                                                v[2].normalisieren();
                                                                if(fabs(v[0]*v[1])<fabs(v[0]*v[2])){
                                                                 pnormal=v[0]%v[1];
                                                                }else{
                                                                 pnormal=v[0]%v[2];
                                                                };
                                                                pnormal.normalisieren();
                                                                h=pmiddle-pvolume->mitte();
                                                                h.normalisieren();
                                                                if((h*pnormal)>0) pnormal*=-1;
                                                                pplane[0]=pnormal%v[0];
                                                                pplane[0].normalisieren();
                                                                pplane[1]=pnormal%pplane[0];
                                                                pplane[1].normalisieren();
 };
 
 void _sichtbarkeitsebene::visualisieren(_vektor4<_to> col){
                                                                _vektor3<_tg> s;
                                                                _tg c;
                                                                _vektor3<_tg> v;
                                                                _vektor4<_to> coln;
                                                                //---------------
                                                                unvisualisieren();
                                                                coln.setzen(1,0.1f,0.1f,0);
                                                                v=*pvertex[1]-*pvertex[0];
                                                                for(c=0;c<=1;c+=0.05){
                                                                 s=*pvertex[0]+v*c;
                                                                 pdblines.einhaengen(new _weltdebuglinie(pvolume->zone()->welt(),s,*pvertex[2],col));
                                                                };
                                                                pdblines.einhaengen(new _weltdebuglinie(pvolume->zone()->welt(),pmiddle,pmiddle+pnormal*0.2,coln));
 };
 
 void _sichtbarkeitsebene::unvisualisieren(){
                                                                pdblines.loeschen();
 };
};