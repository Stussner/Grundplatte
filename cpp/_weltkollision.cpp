//******************************************************************************************************************************************************************************************************
//  Projekt      : grundplatte
//  Bibliothek   : _grundplatte.lib
//  Modul        : _weltkollision.cpp
//  Datum        : 09.01.2006
//  Beschreibung : 
//******************************************************************************************************************************************************************************************************
#include <_weltkollision.hpp>
#include <_weltpolygon.hpp>

//*********************************************************************************************************************************************************************************
//                                                                K O L L I D I E R E N
//*********************************************************************************************************************************************************************************
bool _kollidieren(_kollidierbarpunkt*,_kollidierbarkugel*,_vektor<_tg>&){
                                        return(false);
};
bool _kollidieren(_kollidierbarpunkt*,_kollidierbarzylinder*,_vektor<_tg>&){
                                        return(false);
};
//*********************************************************************************************************************************************************************************
//                                                                K O L L I D I E R B A R
//*********************************************************************************************************************************************************************************
_kollidierbar::_kollidierbar(_kollisionskopplung*kk,_welt*w,_partition::_zone*pz,_partition::_sektor*ps,const _vektor3<_tg>&o,const _vektor3<_tg>&v):schnittpunkt(this){
                                        port=o;
                                        pnotort=o;
                                        pvektor=v;
                                        pdrehvektor.setzen(0,0,0);
                                        pvektorlaenge=v.laenge();
                                       // preflektiv=1;
                                       // pabgleitend=0;
                                       // panhaftend=0;
                                        pstatisch=false;
                                        paktiv=true;
                                      //  pemodul=1;
                                      //  phaerte=1;
                                     //   pmasse=1;
                                        pzone=pz;
                                        psektor=ps;//stammsektor
                                        maxrekursion=10;
                                        pzaehler=0;
                                        pwelt=w;
                                        pkollisionintern=true;
                                     //   pwirdkollidiert=true;
                                        kollisionskopplung=kk;
                                        pmarkierung=0;
                                        pmarkierungkollision=0;
};
_kollidierbar::_kollidierbar(_kollisionskopplung*,_welt*,_baumoctal<_polygon,_tg>*                          ,const _vektor3<_tg>&,const _vektor3<_tg>&):schnittpunkt(this){
};
_kollidierbar::_kollidierbar(_kollisionskopplung*,_welt*,_liste<_polygon>*,unsigned int,unsigned int,_tg,_tg,const _vektor3<_tg>&,const _vektor3<_tg>&):schnittpunkt(this){
};

_kollidierbar::~_kollidierbar(){
};
void _kollidierbar::aktivitaet(const bool b){
                                        paktiv=b;
};
bool _kollidierbar::aktivitaet()const{
                                        return(paktiv);
};
const _vektor3<_tg>&_kollidierbar::ort()const{
                                        return(port);
};
_vektor3<_tg>&_kollidierbar::vektor(){
                                        return(pvektor);
};
_vektor3<_tg>&_kollidierbar::drehvektor(){
                                        return(pdrehvektor);
};
_tg _kollidierbar::vektorlaenge() const{
                                        return(pvektorlaenge);
}
void _kollidierbar::vektorlaenge(const _tg l){
                                        if(l>=0) pvektorlaenge=l;
};

void _kollidierbar::vektor(const _vektor3<_tg>&v){
                                        pvektor=v;
                                        pvektorlaenge=v.laenge();
};
void _kollidierbar::ort(const _vektor3<_tg>&o){
                                        pnotort=port;
                                        port=o;            
};
void _kollidierbar::notfallruecksetzen(){
                                        port=pnotort;
};
void _kollidierbar::bewegen(){
                                        port+=pvektor;
};
void _kollidierbar::bewegungsquader(_tg&x0,_tg&x1,_tg&y0,_tg&y1,_tg&z0,_tg&z1){
                                        if(pvektor[0]<0) {
                                          x0=port[0]+pvektor[0]; 
                                          x1=port[0]; 
                                         }else {
                                          x0=port[0];
                                          x1=port[0]+pvektor[0];
                                         };
                                        if(pvektor[1]<0) {
                                          x0=port[1]+pvektor[1]; 
                                          x1=port[1]; 
                                         }else {
                                          x0=port[1];
                                          x1=port[1]+pvektor[1];
                                         };
                                        if(pvektor[2]<0) {
                                          x0=port[2]+pvektor[2]; 
                                          x1=port[2]; 
                                         }else {
                                          x0=port[2];
                                          x1=port[2]+pvektor[2];
                                         };
};
_partition::_sektor*_kollidierbar::stammsektor(){
                                        if(pzone==0) bestimmenzone();

                                        return(psektor);
};
void _kollidierbar::stammsektor(_partition::_sektor*s){
                                        psektor=s;
};
_partition::_zone*_kollidierbar::zone(){
                                        if(pzone==0) bestimmenzone();
                                        return(pzone);
};
void _kollidierbar::zone(_partition::_zone*z){
                                        pzone=z;
};
void _kollidierbar::bestimmenzone(){
                                        _partition::_zone*zit;
                                        if(pwelt->anfang(zit))do{
                                         psektor=zit->sektor(port);
                                         if(psektor) {
                                          pzone=zit;
                                          return;
                                         };
                                        }while(pwelt->naechstes(zit));
};
bool _kollidierbar::maximalerekursion(){//funktion limitiert die rekursionstiefe
                                        if(pzaehler>=maxrekursion) return(false); else {
                                         pzaehler+=1;
                                         return(true);
                                        };
};
void _kollidierbar::vorbereitenbewegen(){
                                        pzaehler=0;
                                        pvektorlaenge=pvektor.laenge();
                                        schnittort.setzen(0,0,0);
                                        schnittpunkt.ruecksetzen();
                                        loeschenschnittpunkt();
                                        pmarkierungkollision=pwelt->neuemarkierungkollision();
                                        
};
void _kollidierbar::vorbereitenschnittstatisch(){
                                        pzaehler=maxrekursion+1;
                                        pvektorlaenge=pvektor.laenge();
                                        schnittort.setzen(0,0,0);
                                        schnittpunkt.ruecksetzen();
                                        loeschenschnittpunkt();
                                        pmarkierungkollision=pwelt->neuemarkierungkollision();

};
unsigned int _kollidierbar::zaehler()const{
                                        return(pzaehler);
};
void _kollidierbar::inkrementierenrekursionszaehler(){
                                        pzaehler++;
};
_welt*_kollidierbar::welt(){
                                        return(pwelt);
};
/*
void _kollidierbar::kollision(_kollidierbar*){//this wurde passiv von einem anderen kollidierbaren kollidiert
};*/
void _kollidierbar::kollisionintern(const bool b){
                                        pkollisionintern=b;
};
bool _kollidierbar::kollisionintern()const{
                                        return(pkollisionintern);
};
/*
void _kollidierbar::wirdkollidiert(const bool b){
                                        pwirdkollidiert=b;
};
bool _kollidierbar::wirdkollidiert()const{
                                        return(pwirdkollidiert);
};
*/
bool _kollidierbar::berechnenausfall(bool schnittpunktaufgetreten,_vektor3<_tg>&o,_vektor3<_tg>&v,const _vektor3<_tg>&beschleunigung,const _tg beschleunigunglaenge,_polygon*&zuletztkollidiert){
                                        _tg sl;
                                        _vektor3<_tg> lot;
                                        _vektor3<_tg> h;
                                        _vektor3<_tg> n;
                                        _tg daempfung;
                                        _vektor3<_tg> daempfungsvektor;
                                        _tg para;
                                        //--------------
                                        if(schnittpunktaufgetreten){
                                         if(schnittpunkt.polygon){//----------------------------------------------------------- KUGEL - POLYGON - KOLLISION ------------------------------------------------


										 L->l("vor reflektion : schnittort =",schnittpunkt.ort);
										 L->l("vor reflektion : schnittkont =",schnittpunkt.kontakt);
										 L->l("vor reflektion : ort =",o);
                                          //schnittvektor ist einfallvektor vom alten ort o bis zum schnittort sit->ort
                                          //anschließende beschleunigungitationsbetrachtung, projektion durchführen, daempfung bestimmen
                                          //einfallsvektor=schnittpunkt.ort-o;//schnittpunkt.kontakt;
                                          //einfallsvektor-=o;
                                          einfallsvektor=v;
                                          sl=einfallsvektor.laenge();
                                          L->schreiben("Einfallsvektor =",einfallsvektor);
                                          //dämpfung nach anteiligmachung des beschleunigungitationsbetrages
                                          para=sl/pvektorlaenge;
                                          _vektor3<_tg> bn=beschleunigung;
                                          bn.normalisieren();
                                          _vektor3<_tg> vn=v-beschleunigung;
                                          vn.normalisieren();
                                          daempfung=beschleunigunglaenge*(1-(para));//*fabs(bn*vn);
                                      /*    L->schreiben("-----------------------------daempfung=",daempfung);
                                          L->schreiben("sl=",sl);
                                          L->schreiben("para=",para);
                                          L->schreiben("pvektorlaenge=",pvektorlaenge);
                                          L->schreiben("beschleulaenge=",beschleunigunglaenge);
                                          L->schreiben("v=",v);
                                          L->schreiben("vn=",vn);
                                          L->schreiben("bn=",bn);*/
                                          //reflektion durchführen ergebnis landet in schnittvektor
                                          //daempfungsvektor bestimmt, er sollte theoretisch nie länger werden
                                          //als der ausfallsvektor (schnittvektor);
                                          //V3.lotpunktgerade(o,o+einfallsvektor,schnittpunkt.normale,lot);
                                          n=schnittpunkt.normale;
                                          _tg nmn=n*n;
                                          h=o+einfallsvektor;
                                          _tg hhh=((o[0]-h[0])*n[0] + (o[1]-h[1])*n[1] + (o[2]-h[2])*n[2])/nmn;
                                          lot.setzenkomponente(0,(h[0]-o[0])+n[0]*hhh);//lot punt auf gerade (o,h,n,lot);
                                          lot.setzenkomponente(1,(h[1]-o[1])+n[1]*hhh);
                                          lot.setzenkomponente(2,(h[2]-o[2])+n[2]*hhh);
                                          //ausfallsvektor=(o+lot*2)-(o+einfallsvektor);
                                          ausfallsvektor.setzenkomponente(0,(o[0]+lot[0]*2)-h[0]);
                                          ausfallsvektor.setzenkomponente(1,(o[1]+lot[1]*2)-h[1]);
                                          ausfallsvektor.setzenkomponente(2,(o[2]+lot[2]*2)-h[2]);
                                          ausfallsvektor.normalisieren();
                                          if(daempfung>=(pvektorlaenge-sl)) daempfung=(pvektorlaenge-sl)*(1-(2*nahenull));
                                          //daempfungsvektor=-ausfallsvektor*daempfung;
                                          daempfungsvektor=ausfallsvektor;
                                          daempfungsvektor*=-daempfung;
                                          vektor()=ausfallsvektor;
                                          vektor()*=pvektorlaenge;
                                          vektor()+=daempfungsvektor;
                                          ausfallsvektor*=pvektorlaenge-sl;
                                          ausfallsvektor+=daempfungsvektor;
                                          //unscharf korrigierte postition für die rekurstionseineitung
                                          //bestimmen (schnittort wird entlang des einfallsvektors um
                                          //den betrag 2*nahenull zurückgesetzt
                                          //_vektor<_tg> zurueck=o-sit->ort;
                                          if(sl<=(nahenull*2)){
                                           schnittort=o+schnittpunkt.kontakt;
                                           L->schreiben("hu.....................");
                                          }else{
                                           einfallsvektor.normalisieren();
                                           schnittort=schnittpunkt.ort;
                                         //  schnittort-=einfallsvektor*2*nahenull;
                                           L->schreiben("haaaa.....................");
                                           //schnittort[0]=schnittpunkt.ort[0]-einfallsvektor[0]*2*nahenull;
                                           //schnittort[1]=schnittpunkt.ort[1]-einfallsvektor[1]*2*nahenull;
                                           //schnittort[2]=schnittpunkt.ort[2]-einfallsvektor[2]*2*nahenull;
                                          };
                                          
                                          

                                          /*zuletztkollidiert=schnittpunkt.polygon;
                                          _listenknoten<_kollisionskopplung> * koit;
                                          if(zuletztkollidiert->anfang(koit))do{
                                           koit->objekt()->kollision(this,zuletztkollidiert);
                                          }while(zuletztkollidiert->naechstes(koit));
                                          */

                                         }else
                                         if(schnittpunkt.kollidierbarkugel){//------------------------------------------------- KUGEL - KUGEL - KOLLISION -------------------------------------------------
                                          //if(sit->gamma!=-3){
                                          //L->schreiben("------------------------------------------------------------");
                                          //L->schreiben("o=",o);
                                          //L->schreiben("v=",v);
                                          //L->schreiben("ort=",port);
                                          //L->schreiben("pvektor=",pvektor);
                                          //L->schreiben("sit->ort           =",sit->ort);
                                          //L->schreiben("sit->normale       =",sit->normale);
                                          //L->schreiben("sit->kugel->pvektor=",sit->kollidierbarkugel->pvektor);
                                          //L->schreiben("sit->kugel->ort    =",sit->kollidierbarkugel->port);
                                          //_vektor<_tg> lot;
                                          //_vektor<_tg> vr=v-schnittpunkt.kollidierbarkugel->pvektor;
                                          //_vektor<_tg> vrn=vr;
                                          //vrn.normalisieren();
                                          _vektor3<_tg> vr;
                                          _vektor3<_tg> vrn;
                                          _vektor3<_tg> vrr;
                                          vr=v-schnittpunkt.kollidierbarkugel->vektor();
                                          vrn=vr;
                                          
                                          //vrn[0]=vr[0]=v[0]-schnittpunkt.kollidierbarkugel->pvektor[0];
                                          //vrn[1]=vr[1]=v[1]-schnittpunkt.kollidierbarkugel->pvektor[1];
                                          //vrn[2]=vr[2]=v[2]-schnittpunkt.kollidierbarkugel->pvektor[2];
                                          vrn.normalisieren();
                                          //Stoßparameter f durch skalarprodukt bestimmen
                                          //_tg f=vrn* -schnittpunkt.normale;
                                          n=schnittpunkt.normale;
                                          _tg f=vrn* -n;
                                          //V3.lotpunktgerade(o,o+vr,schnittpunkt.normale,lot);
                                          h=o+vr;
                                          _tg nmn=n*n;
                                          _tg hhh=(o[0]-h[0])*n[0] + (o[1]-h[1])*n[1] + (o[2]-h[2])*n[2];
                                          lot.setzenkomponente(0,(h[0]-o[0])+n[0]*(hhh/nmn));//lot punt auf gerade (o,h,n,lot);
                                          lot.setzenkomponente(1,(h[1]-o[1])+n[1]*(hhh/nmn));
                                          lot.setzenkomponente(2,(h[2]-o[2])+n[2]*(hhh/nmn));
                                          //vrr=(o+lot*2)-(o+vr);
                                          vrr.setzenkomponente(0,(o[0]+lot[0]*2)-h[0]);
                                          vrr.setzenkomponente(1,(o[1]+lot[1]*2)-h[1]);
                                          vrr.setzenkomponente(2,(o[2]+lot[2]*2)-h[2]);
                                          h=schnittpunkt.ort-o;
                                          sl=h.laenge();
                                          //ausfallsvektoren anhand des parameters f bestimmen
                                          //_vektor<_tg> v1n=(vrr*(1-f))+schnittpunkt.kollidierbarkugel->pvektor;
                                          //_vektor<_tg> v2n=(-schnittpunkt.normale*vr.laenge()*f)+schnittpunkt.kollidierbarkugel->pvektor;
                                          _vektor3<_tg> v1n;
                                          _vektor3<_tg> v2n;
                                          _tg vrlaenge=vr.laenge();
                                          v1n.setzenkomponente(0,(vrr[0]*(1-f))+schnittpunkt.kollidierbarkugel->vektor()[0]);
                                          v1n.setzenkomponente(1,(vrr[1]*(1-f))+schnittpunkt.kollidierbarkugel->vektor()[1]);
                                          v1n.setzenkomponente(2,(vrr[2]*(1-f))+schnittpunkt.kollidierbarkugel->vektor()[2]);
                                          ausfallsvektor=v1n;
                                          v2n.setzenkomponente(0,(-n[0]*vrlaenge*f)+schnittpunkt.kollidierbarkugel->vektor()[0]);
                                          v2n.setzenkomponente(1,(-n[1]*vrlaenge*f)+schnittpunkt.kollidierbarkugel->vektor()[1]);
                                          v2n.setzenkomponente(2,(-n[2]*vrlaenge*f)+schnittpunkt.kollidierbarkugel->vektor()[2]);
                                          ausfallsvektor.normalisieren();
                                          ausfallsvektor*=fabs(pvektorlaenge-sl);
                                          vektor()=v1n;//.setzen(v1n[0],v1n[1],v1n[2]);
                                          schnittpunkt.kollidierbarkugel->vektor()=v2n;//.setzen(v2n[0],v2n[1],v2n[2]);
                                          _vektor3<_tg> zurueck;
                                          zurueck=o-schnittpunkt.ort;
                                          if(zurueck.laenge()<=(nahenull*2)){
                                           schnittort=o;
                                          }else{
                                           zurueck.normalisieren();
                                           zurueck*=nahenull*2;
                                           schnittort=schnittpunkt.ort+zurueck;
                                          };
                                          //if(schnittpunkt.kollidierbarkugel->kollisionskopplung) schnittpunkt.kollidierbarkugel->kollisionskopplung->kollision(this);
                                         }else{
                                         
                                         };
                                         return(true);
                                        };
                                        return(false);
};
void _kollidierbar::aufrufenkopplung(){
                                        if(schnittpunkt.polygon){
                                         _polygon*pit=schnittpunkt.polygon;
                                         aufrufenkopplung(pit);
                                        };
                                        if(schnittpunkt.kollidierbarkugel){
                                         if(schnittpunkt.kollidierbarkugel->kollisionskopplung) schnittpunkt.kollidierbarkugel->kollisionskopplung->kollision(this);
                                        };
};
void _kollidierbar::aufrufenkopplung(_polygon*pit){
                                         _listenknoten<_kollisionskopplung> * koit;
                                         if(pit->anfang(koit))do{
                                          koit->objekt()->kollision(this,pit);
                                         }while(pit->naechstes(koit));
};
void _kollidierbar::markierung(const int i){
                                        pmarkierung=i;
};
int _kollidierbar::markierung()const{
                                        return(pmarkierung);
};
void _kollidierbar::markierungkollision(const unsigned int m){
                                        pmarkierungkollision=m;
};
unsigned int _kollidierbar::markierungkollision()const{
                                        return(pmarkierungkollision);
};
bool _kollidierbar::schnittpunktgleich(const _tg g){
                                        if(schnittpunktliste.anzahl()==0) return(false);
                                        _schnittpunktkollision*sit;
                                        if(schnittpunktliste.anfang(sit))do{
                                         if(fabs(g-sit->gamma)<nahenull) return(true);
                                        }while(schnittpunktliste.naechstes(sit));
                                        return(false);
};
bool _kollidierbar::schnittpunktentfernter(const _tg g){
                                        if(schnittpunktliste.anzahl()==0) return(true);
                                        _schnittpunktkollision*sit;
                                        if(schnittpunktliste.anfang(sit))do{
                                         if(g<sit->gamma) return(true);
                                        }while(schnittpunktliste.naechstes(sit));
                                        return(false);
                                        
};
void _kollidierbar::loeschenschnittpunkt(){
                                        schnittpunktliste.loeschen();
};
void _kollidierbar::erzeugenschnittpunkt(_polygon*p,_verbindervertexpolygon*c,const _vektor3<_tg>&o,const _vektor3<_tg>&v,_tg g,const _vektor3<_tg>&sp,const _vektor3<_tg>&ko,const _vektor3<_tg>&no){
                                        new _schnittpunktkollision(this,p,c,o,v,g,sp,ko,no);
};

//*********************************************************************************************************************************************************************************
//                                                                K O L L I D I E R B A R P U N K T
//*********************************************************************************************************************************************************************************
 _kollidierbarpunkt::_kollidierbarpunkt(_kollisionskopplung*kk,_partition::_zone*pz,_partition::_sektor*ps):_kollidierbar(kk,0,pz,ps,_vektor3<_tg>(0,0,0),_vektor3<_tg>(0,0,0)){
};
 _kollidierbarpunkt::~_kollidierbarpunkt(){
};
bool _kollidierbarpunkt::bewegen(/*_vektor<_tg> v,_vektor<_tg>&*/){
                                        _kollidierbar*kit=0;
                                        //--------------------------------
                                       // if(psektor->anfang(kit))do {
                                         if(kit!=this){
                                       //   kollidieren(this,kit,v);
                                         };
                                        //}while(psektor->naechstes(kit));
                                        return(false);
};
//*********************************************************************************************************************************************************************************
//                                                                K O L L I D I E R B A R Z Y L I N D E R 
//*********************************************************************************************************************************************************************************
 _kollidierbarzylinder::_kollidierbarzylinder(_kollisionskopplung*kk,_partition::_zone*pz,_partition::_sektor*ps):_kollidierbar(kk,0,pz,ps,_vektor3<_tg>(0,0,0),_vektor3<_tg>(0,0,0)){
};
 _kollidierbarzylinder::~_kollidierbarzylinder(){
};
bool _kollidierbarzylinder::bewegen(/*_vektor<_tg> v,_vektor<_tg>&*/){
                                        _kollidierbar*kit=0;
                                        //--------------------------------
                                        //if(psektor->anfang(kit))do {
                                         if(kit!=this){
                                         // kollidieren(this,kit,v);
                                         };
                                        //}while(psektor->naechstes(kit));
                                        return(false);
};
//*********************************************************************************************************************************************************************************
//                                                                K O L L I D I E R B A R K U G E L 
//*********************************************************************************************************************************************************************************
_kollidierbarkugel::_kollidierbarkugel(_kollisionskopplung*kk,_welt*w,_partition::_zone*pz,_partition::_sektor*ps,const _vektor3<_tg>&o,const _vektor3<_tg>&v,_tg rad):_kollidierbar(kk,w,pz,ps,o,v){
                                        pradius=rad;
                                        //port=o;
                                        //pvektor=v;
                                        wp=0;
                                        plaengevorkollision=0;
                                      /*  odebody=dBodyCreate(w->odewelt);
                                        odegeom=dCreateSphere(w->odespace,pradius);
                                        dGeomSetBody(odegeom,odebody);
                                        dBodySetPosition(odebody,port[0],port[1],port[2]);
                                        dBodySetLinearVel(odebody,pvektor[0],pvektor[1],pvektor[2]);*/
                                        //dBodySetMass(odebody,masse);
};
 _kollidierbarkugel::_kollidierbarkugel(_kollisionskopplung*kk,_welt*w,const _vektor3<_tg>&o,const _vektor3<_tg>&v,_tg rad):_kollidierbar(kk,w,0,0,o,v){
                                        pradius=rad;
                                        //port=o;
                                        //pvektor=v;
                                        wp=0;
                                        plaengevorkollision=0;
                                    /*    odebody=dBodyCreate(w->odewelt);
                                        odegeom=dCreateSphere(w->odespace,pradius);
                                        dGeomSetBody(odegeom,odebody);
                                        dBodySetPosition(odebody,port[0],port[1],port[2]);
                                        dBodySetLinearVel(odebody,pvektor[0],pvektor[1],pvektor[2]);*/
                                        //dBodySetMass(odebody,1);
};
 _kollidierbarkugel::~_kollidierbarkugel(){
                                        if(wp)delete wp;
                                        wp=0;
                                       // dBodyDestroy(odebody);
                                       // dGeomDestroy(odegeom);
};
void _kollidierbarkugel::aktualisieren(){
                                      /*  const dReal*f=dBodyGetPosition(odebody);
                                        port.setzen(f[0],f[1],f[2]);
                                        const dReal*d=dBodyGetLinearVel(odebody);
                                        pvektor.setzen(d[0],d[1],d[2]);*/
};
/*
_vektor3<_tg>&_kollidierbarkugel::ort(){
                                        return(port);
};
*/
/*
void _kollidierbarkugel::vektor(const _vektor3<_tg>&v){
                                        pvektor=v;
                                        //dBodySetLinearVel(odebody,pvektor[0],pvektor[1],pvektor[2]);
};
*/
/*
_vektor3<_tg>& _kollidierbarkugel::vektor(){
                                        return(pvektor);
};
*/
void _kollidierbarkugel::radius(const _tg r){
                                        pradius=r; 
};
_tg _kollidierbarkugel::radius()const{
 
                                        return(pradius);
};
void _kollidierbarkugel::bewegungsquader(const _vektor3<_tg>&o,const _vektor3<_tg>&v,_tg&x0,_tg&x1,_tg&y0,_tg&y1,_tg&z0,_tg&z1){
                                        if(v[0]<0) {
                                         x0=(o[0]+v[0])-pradius; 
                                         x1=o[0]+pradius; 
                                        }else {
                                         x0=o[0]-pradius;
                                         x1=o[0]+v[0]+pradius;
                                        };
                                        if(v[1]<0) {
                                         y0=(o[1]+v[1])-pradius; 
                                         y1=o[1]+pradius; 
                                        }else {
                                         y0=o[1]-pradius;
                                         y1=o[1]+v[1]+pradius;
                                        };
                                        if(v[2]<0) {
                                         z0=(o[2]+v[2])-pradius; 
                                         z1=o[2]+pradius; 
                                        }else {
                                         z0=o[2]-pradius;
                                         z1=o[2]+v[2]+pradius;
                                        };
};
void _kollidierbarkugel::statischerquader(_tg&x0,_tg&x1,_tg&y0,_tg&y1,_tg&z0,_tg&z1){
                                        x0=ort()[0]-pradius; 
                                        x1=ort()[0]+pradius; 
                                        y0=ort()[1]-pradius; 
                                        y1=ort()[1]+pradius; 
                                        z0=ort()[2]-pradius; 
                                        z1=ort()[2]+pradius; 
};
bool _kollidierbarkugel::schnittstatisch(){
                                        vorbereitenschnittstatisch();
                                        aktualisieren();
                                        schnittpunkt.polygon=0;
                                        schnittpunkt.kollidierbarkugel=0;                                        
                                        schnittpunkt.gamma=1002;
                                        if(zone()==0) bestimmenzone();
                                        stammsektor(zone()->sektor(ort()));
                                        if(stammsektor()==0) L->schreiben("Fehler : bool _kollidierbarkugel : sektor nicht bestimmbar");
                                        _liste<_partition::_sektor>::aushaengen();
                                        bool sa=false;
                                        bestimmenschnittstatisch(stammsektor(),sa);  
                                        if(sa){
                                         //wir koppeln dieses kollidierbar an polygon an durch verbinder
                                         if(schnittpunkt.polygon) {
                                          bool exist=false;
                                          _listenknoten<_polygon>*lnpit;
                                          if(_liste<_polygon>::anfang(lnpit))do{
                                           if(lnpit->objekt()==schnittpunkt.polygon) exist=true;
                                          }while((_liste<_polygon>::naechstes(lnpit))&&(exist==false));
                                          if(exist==false) new _verbinder<_polygon,_kollidierbar>(this,schnittpunkt.polygon,schnittpunkt.polygon,this);
                                         };
                                        };
                                        _listenknoten<_polygon>*lnpit;
                                        if(kopplungsaufrufe.anfang(lnpit))do{
                                         aufrufenkopplung(lnpit->objekt());
                                        }while(kopplungsaufrufe.naechstes(lnpit));                                        
                                        if(sa){
                                         aufrufenkopplung();
                                        };                                        
                                        return(sa);
};  
bool _kollidierbarkugel::bewegen(const _vektor3<_tg>&beschleunigung/*_vektor<_tg> v,_vektor<_tg>&vektorneu*/){
                                        _polygon*zuletztkollidiert=0;
                                        bool r;
                                        //--------------------------------
                                        //_vektor<_tg> vektorneu;//ungenutzt
                                        //L->schreiben("zonesektor",(int)zone()->sektor(port));
                                        //   L->schreiben("port vorher=",port);
                                        //_vektor<_tg> arsch;
                                       // arsch=pvektor-grav;
                                        vorbereitenbewegen();
                                        schnittpunkt.polygon=0;
                                        schnittpunkt.kollidierbarkugel=0;
                                        schnittpunkt.gamma=1002;                                        
                                        _vektor3<_tg> o=ort();
                                        _vektor3<_tg> v=vektor();
                                       // _liste<_polygon>::aushaengen();
                                        r=bewegen(o,v,beschleunigung,beschleunigung.laenge(),zuletztkollidiert);
                                        // ***** DEBUG*****
                                        //if(wp) delete wp;
                                        //wp=new _weltdebugpfeil(zone()->welt(),port,port+pvektor,0.005,0.005,_vektor<_to>(1,1,1));
                                        // ****************
                                        if(r==false) _kollidierbar::bewegen();
                                        // dBodySetPosition(odebody,port[0],port[1],port[2]);
                                        return(r);
};      
                    
bool _kollidierbarkugel::testen(){

                                        vorbereitenbewegen();
                                        aktualisieren();
                                        schnittpunkt.polygon=0;
                                        schnittpunkt.kollidierbarkugel=0;                                        
                                        schnittpunkt.gamma=1002;
                                        if(zone()==0) bestimmenzone();
                                        
                                        stammsektor(zone()->sektor(ort()));
                                        if(stammsektor()==0) L->schreiben("Fehler : bool _kollidierbarkugel : sektor nicht bestimmbar");
                                        _liste<_partition::_sektor>::aushaengen();
                                        
                                        bool sa=false;
                                        bestimmenschnittpunkt(ort(),vektor(),stammsektor(),sa);
                                        _listenknoten<_polygon>*lnpit;
                                        if(kopplungsaufrufe.anfang(lnpit))do{
                                         aufrufenkopplung(lnpit->objekt());
                                        }while(kopplungsaufrufe.naechstes(lnpit));                                        
                                        if(sa){
                                         aufrufenkopplung();
                                        };
                                        
                                        if(sa) return(false); else return(true);
};                            

//bool _kollidierbarkugel::bewegen(const _vektor<_tg>&grav,_vektor<_tg> o,_vektor<_tg> v,const _tg vl,_polygon*&zuletztkollidiert,_vektor<_tg>&){
bool _kollidierbarkugel::bewegen(_vektor3<_tg>&o,_vektor3<_tg>&v,const _vektor3<_tg>&beschleunigung,const _tg beschleunigunglaenge,_polygon*&zuletztkollidiert){
                                        //-------------------------
                                        
                                        schnittpunkt.gamma=1002;
                                        zuletztkollidiert=0;
                                        if(zone()==0) bestimmenzone();
                                        stammsektor(zone()->sektor(o));
                                        if(stammsektor()==0) {
                                         L->schreiben("Fehler : bool _kollidierbarkugel : sektor nicht bestimmbar");
                                         L->schreiben("Mit dem Ort : o=",o);
                                         notfallruecksetzen();
                                         return(false);
                                        };
                                        _liste<_partition::_sektor>::aushaengen();
                                        bool sa=false;
                                        bestimmenschnittpunkt(o,v,stammsektor(),sa);
                                        if(sa){
                                         //wir koppeln dieses kollidierbar an polygon an durch verbinder
                                         if(schnittpunkt.polygon) {
                                          bool exist=false;
                                          _listenknoten<_polygon>*lnpit;
                                          if(_liste<_polygon>::anfang(lnpit))do{
                                           if(lnpit->objekt()==schnittpunkt.polygon) exist=true;
                                          }while((_liste<_polygon>::naechstes(lnpit))&&(exist==false));
                                          if(exist==false) new _verbinder<_polygon,_kollidierbar>(this,schnittpunkt.polygon,schnittpunkt.polygon,this);
                                         };
                                        };
                                        _listenknoten<_polygon>*lnpit;
                                        if(kopplungsaufrufe.anfang(lnpit))do{
                                         aufrufenkopplung(lnpit->objekt());
                                        }while(kopplungsaufrufe.naechstes(lnpit));
                                        if(berechnenausfall(sa,o,v,beschleunigung,beschleunigunglaenge,zuletztkollidiert)){
                                         aufrufenkopplung();
                                         //kugel bereits innerhalb kugel, was nun ?
                                         /*schnittvektor=sit->ort-o;
                                         schnittort=sit->ort;
                                         if(bewegen(schnittort,schnittvektor,vl,zuletztkollidiert,unnuetz)==false) {
                                         port=sit->ort;
                                         pvektor*=-1;
                                         };
                                         return(true);
                                         };*/
                                         //};
                                         //new _weltdebugpfeil(pwelt,sit->ort,sit->ort+schnittvektor,0.02,0.015,_vektor<float>(1,1,1));
                                         //rekursion enleiten
                                         //stammsektor(0);
                                         //L->schreiben("pvektor",pvektor);
                                         //L->schreiben("schnittvektor=",schnittvektor);
                                         //L->schreiben("rekursion ort=",sit->ort+sit->normale *nahenull*2);
                                         //if(sit->gamma==-3) schnittort=sit->ort;
                                         //schnittort=o;
                                         //_vektor<_tg> schnittort=sit->ort-zurueck*nearzero;//sit->normale*nahenull*2;
                                         //L->schreiben("neuepos für rekursion=",schnittort);
                                         //L->schreiben("neuevek für rekursion=",schnittvektor);
                                         //new _weltdebugkugel(zone()->welt(),schnittort,pradius,_vektor<_to>(1,0,0));
                                         //new _weltdebugpfeil(zone()->welt(),schnittort,schnittort+schnittvektor,0.0001,0.00005,_vektor<_to>(1,0,0));
                                         //new _weltdebugpfeil(zone()->welt(),schnittort,schnittort+pvektor,0.0001,0.00005,_vektor<_to>(0,1,0));
                                         //if(sit->kollidierbarkugel) {
                                         //new _weltdebugpfeil(zone()->welt(),sit->kollidierbarkugel->port,sit->kollidierbarkugel->port+sit->kollidierbarkugel->pvektor,0.0001,0.00005,_vektor<_to>(1,1,1));
                                         //new _weltdebugkugel(zone()->welt(),sit->kollidierbarkugel->port,sit->kollidierbarkugel->pradius,_vektor<_to>(1,1,1));
                                         //};
                                         
                                         
                                         
                                         if(maximalerekursion()) {
                                          _vektor3<_tg> reko=schnittort;
                                          _vektor3<_tg> rekv=ausfallsvektor;
                                          
                                          if(bewegen(reko,rekv,beschleunigung,beschleunigunglaenge,zuletztkollidiert)==false) {
                                           //port.setzen(schnittort[0]+ausfallsvektor[0],schnittort[1]+ausfallsvektor[1],schnittort[2]+ausfallsvektor[2]);
                                           L->l("Schnittort = ",schnittort);
                                           L->l("Ausfall    = ",ausfallsvektor);
                                           ort(schnittort+ausfallsvektor);
                                           //_vektor<_tg> vv=port-sit->kollidierbarkugel->port;
                                          //new _weltdebugkugel(zone()->welt(),port,pradius,_vektor<_to>(1,0,0));
                                          //L->schreiben("rekursion beendet");
                                          };
                                         }else{
                                          //maximale rekursionstiefe erreciht 
                                          //maßnahmen einleiten
                                          ort(schnittort);//.setzen(schnittort[0],schnittort[1],schnittort[2]);
                                         };
                                         //L->schreiben("port=",port);
                                         //zuletztkollidiert=sit->polygon;
                                         return(true);
                                         
                                         
                                         
                                         
                                         
                                        };
                                        return(false);
};
void _kollidierbarkugel::bestimmenschnittpunkt(const _vektor3<_tg>&o,const _vektor3<_tg>&v,_partition::_sektor*sektor,bool&schnittpunktaufgetreten){
                                        _partition::_polygon*pit;
                                        _partition::_polygon*pitn;
                                        _partition::_sektor*sit;
                                        _listenknoten<_partition::_polygon >*lnpit;
                                        _listenknoten<_partition::_sektor >*lnsit;
                                        _listenknoten<_polygon> * ipit;
                                        _polygon*ipoly;
                                        _tg parameter;
                                        _vektor3<_tg> n;
                                        _vektor3<_tg> sp;
                                        _polygon*poly;
                                        _tg x0,x1,y0,y1,z0,z1;
                                        //-----------------------
                                        kopplungsaufrufe.aushaengen();
                                        if(sektor->wurzel()) bewegungsquader(o,v,x0,x1,y0,y1,z0,z1);
                                        new _verbinder<_partition::_sektor,_kollidierbarkugel>(this,sektor,sektor,this);
                                        //untersuchung, ob ein schnitt mit einem polygon oder einem portal erfolgt
                                        if(sektor->anfang(pit))do{
                                         if(pit->portal()){//-------------------------------------- portale untersuchen ----------------------------------------
                                          if((pit->markierungkollisionobjekt!=markierungkollision())||(pit->markierungkollisionrekursion!=zaehler())){
                                           pit->markierungkollisionobjekt=markierungkollision();
                                           pit->markierungkollisionrekursion=zaehler();
                                           if(pit->innerhalbkugeltranslation(o,v,pradius)){
                                            if(pit->anfang(lnpit))do{
                                             pitn=lnpit->objekt();
                                             if((pitn->markierungkollisionobjekt!=markierungkollision())||(pitn->markierungkollisionrekursion!=zaehler())){
                                              //nachbarportal ist unmarkiert un gültig
                                              //rekursion für sektoriteration einleiten
                                              pitn->markierungkollisionobjekt=markierungkollision();
                                              pitn->markierungkollisionrekursion=zaehler();
                                              if(pitn->innerhalbkugeltranslation(o,v,pradius)){    
                                               bestimmenschnittpunkt(o,v,pitn->sektor(),schnittpunktaufgetreten);
                                              };
                                             };
                                            }while(pit->naechstes(lnpit));//nachbarportaliteration
                                           };//inmnerhalb kugel verschiebungvolumen?
                                          };//portaalmarkierung gesetzt ?
                                         }else{// pit ist kein portal
                                          //------------------------------------- zonenpolygone untersuchen  -------------------------------------------
                                          poly=pit->polygon();
                                          if(poly->kollision()){
                                           if((poly->markierungkollisionobjekt!=markierungkollision())||(poly->markierungkollisionrekursion!=zaehler())){
                                            poly->markierungkollisionobjekt=markierungkollision();
                                            poly->markierungkollisionrekursion=zaehler();
                                            if(poly->innerhalbkugeltranslation(o,v,pradius,true)){
                                             if(poly->schnittpunktkugeltranslation(o,v,pradius,n,sp,parameter)){
                                              if(schnittpunkt.gamma>parameter){
                                               schnittpunktaufgetreten=true;
                                               schnittpunkt.gamma=parameter;
                                               schnittpunkt.polygon=poly;
                                               schnittpunkt.kollidierbarkugel=0;
                                               schnittpunkt.normale=n;
                                               schnittpunkt.ort=sp;
                                               schnittpunkt.kontakt=sp-n*(pradius-nahenull*4);
                                               schnittpunkt.vektor=v;
                                              };
                                             };
                                            };
                                           };
                                          };
                                         };
                                        }while(sektor->naechstes(pit));
                                        //---------------------------------------interne sektorpolygone abiterieren----------------------------------
                                        if(kollisionintern()){
                                         if(sektor->wurzel()){
                                          bestimmenschnittpunktmitbaum(sektor->wurzel(),sektor,o,v,x0,x1,y0,y1,z0,z1,schnittpunktaufgetreten);
                                         }else{
                                         
                                          if(sektor->internepolygonestatisch()->anfang(ipit))do{
                                           ipoly=ipit->objekt();
                                           if(ipoly->kollision()){
                                            if((ipoly->markierungkollisionobjekt!=markierungkollision())||(ipoly->markierungkollisionrekursion!=zaehler())){
                                             ipoly->markierungkollisionobjekt=markierungkollision();
                                             ipoly->markierungkollisionrekursion=zaehler();
                                             if(ipoly->innerhalbkugeltranslation(o,v,pradius,true)){
                                              if(ipoly->nurkollisionskopplung()){
                                               kopplungsaufrufe.einhaengen(ipoly);
                                              }else{
                                               if(ipoly->schnittpunktkugeltranslation(o,v,pradius,n,sp,parameter)){
                                                if(schnittpunkt.gamma>parameter){
                                                 schnittpunktaufgetreten=true;
                                                 schnittpunkt.gamma=parameter;
                                                 schnittpunkt.polygon=ipoly;
                                                 schnittpunkt.kollidierbarkugel=0;
                                                 schnittpunkt.normale=n;
                                                 schnittpunkt.ort=sp;
                                                 schnittpunkt.kontakt=sp-n*(pradius-nahenull*4);
                                                 schnittpunkt.vektor=v;
                                                };
                                               };
                                              };
                                             };
                                            };
                                           };
                                          }while(sektor->internepolygonestatisch()->naechstes(ipit));
                                          
                                          if(sektor->internepolygonedynamisch()->anfang(ipit))do{
                                           ipoly=ipit->objekt();
                                           if(ipoly->kollision()){
                                            if((ipoly->markierungkollisionobjekt!=markierungkollision())||(ipoly->markierungkollisionrekursion!=zaehler())){
                                             ipoly->markierungkollisionobjekt=markierungkollision();
                                             ipoly->markierungkollisionrekursion=zaehler();
                                             if(ipoly->innerhalbkugeltranslation(o,v,pradius,true)){
                                              if(ipoly->nurkollisionskopplung()){
                                               kopplungsaufrufe.einhaengen(ipoly);
                                              }else{
                                               if(ipoly->schnittpunktkugeltranslation(o,v,pradius,n,sp,parameter)){
                                                if(schnittpunkt.gamma>parameter){
                                                 schnittpunktaufgetreten=true;
                                                 schnittpunkt.gamma=parameter;
                                                 schnittpunkt.polygon=ipoly;
                                                 schnittpunkt.kollidierbarkugel=0;
                                                 schnittpunkt.normale=n;
                                                 schnittpunkt.ort=sp;
                                                 schnittpunkt.kontakt=sp-n*(pradius-nahenull*4);
                                                 schnittpunkt.vektor=v;
                                                };
                                               };
                                              };
                                             };
                                            };
                                           };
                                          }while(sektor->internepolygonedynamisch()->naechstes(ipit));
                                         };
                                        };
                                        //----------------------------------------untersuchung mit den sektorinternen kollidierbaren--------------------
                                        _listenknoten<_kollidierbarkugel>*kkit;
                                        if(anfang(lnsit))do{
                                         sit=lnsit->objekt();
                                         if(sit->anfang(kkit ))do{
                                         
                                           
                                           if(kkit->objekt()->aktivitaet()){
                                            if(kkit->objekt()!=this){
                                             if(kollision(kkit->objekt(),o,v,n,sp,parameter)){
                                              if(schnittpunkt.gamma>parameter){
                                               schnittpunktaufgetreten=true;
                                               schnittpunkt.gamma=parameter;
                                               schnittpunkt.polygon=0;
                                               schnittpunkt.kollidierbarkugel=kkit->objekt();
                                               schnittpunkt.normale=n;
                                               schnittpunkt.ort=sp;
                                               schnittpunkt.vektor=v;
                                              };
                                             };
                                            };
                                           };
                                          
                                          
                                         }while(sit->naechstes(kkit));
                                        }while(naechstes(lnsit));
};  
void _kollidierbarkugel::bestimmenschnittpunktmitbaum(_baumoctalwuerfel<_polygon,_tg>*w,_partition::_sektor*sektor,const _vektor3<_tg>&o,const _vektor3<_tg>&v,const _tg x0,const _tg x1,const _tg y0,const _tg y1,const _tg z0,const _tg z1,bool&schnittpunktaufgetreten){
                                    /*     L->schreiben("hhhx",w->x0);
                                         L->schreiben("hhhx",w->x1);
                                         L->schreiben("hhhy",w->y0);
                                         L->schreiben("hhhy",w->y1);
                                         L->schreiben("hhhz",w->z0);
                                         L->schreiben("hhhz",w->z1);*/
                                        if(w->innerhalb(x0,x1,y0,y1,z0,z1)){
                                         if(w->kinderlos()){
                                          //objekte prüfen
                                          _polygon*ipoly;
                                          _listenknoten<_polygon>*oit; 
                                          if(w->anfang(oit))do{
                                           ipoly=oit->objekt();
                                           if(ipoly->kollision()){
                                            if((ipoly->markierungkollisionobjekt!=markierungkollision())||(ipoly->markierungkollisionrekursion!=zaehler())){
                                             ipoly->markierungkollisionobjekt=markierungkollision();
                                             ipoly->markierungkollisionrekursion=zaehler();
                                             if(ipoly->innerhalbkugeltranslation(o,v,pradius,true)){
                                              if(ipoly->nurkollisionskopplung()){
                                               kopplungsaufrufe.einhaengen(ipoly);
                                              }else{
                                               _vektor3<_tg> n; 
                                               _vektor3<_tg> sp;
                                               _tg parameter;
                                               if(ipoly->schnittpunktkugeltranslation(o,v,pradius,n,sp,parameter)){
                                                if(schnittpunkt.gamma>parameter){
                                                 schnittpunktaufgetreten=true;
                                                 schnittpunkt.gamma=parameter;
                                                 schnittpunkt.polygon=ipoly;
                                                 schnittpunkt.kollidierbarkugel=0;
                                                 schnittpunkt.normale=n;
                                                 schnittpunkt.ort=sp;
                                                 schnittpunkt.kontakt=sp-n*(pradius-nahenull*4);
                                                 schnittpunkt.vektor=v;
                                                };
                                               };
                                              };
                                             };
                                            };
                                           };
                                          }while(w->naechstes(oit));                                          
                                         }else{
                                          int i,j,k;
                                          for(i=0;i<2;i++)for(j=0;j<2;j++)for(k=0;k<2;k++) if(w->kind[i][j][k]) bestimmenschnittpunktmitbaum(w->kind[i][j][k],sektor,o,v,x0,x1,y0,y1,z0,z1,schnittpunktaufgetreten);
                                         };
                                        };
};
bool _kollidierbarkugel::kollision(_kollidierbarkugel*kugel,const _vektor3<_tg>&o1,const _vektor3<_tg>&v1,_vektor3<_tg>&n,_vektor3<_tg>&schnittpunkt,_tg&parameter){
                                        _vektoranalysis3<_tg> V3;
                                        bool r=false;
                                        //------------
                                    /*  _vektor<_tg> vv=o1-kugel->port;
                                        if(vv.laenge()<kugel->pradius+pradius+nahenull){
                                        vv.normalisieren();
                                        n=vv;
                                        vv*=kugel->pradius+pradius+nahenull;
                                        schnittpunkt=kugel->port+vv;
                                        parameter=-3;
                                        return(true);
                                        };*/
                                        if(v1.laenge()!=0){
                                         //_vektor<_tg> vr=v1-(kugel->pvektor*(v1.laenge()/pvektor.laenge()));
                                         _vektor3<_tg> vr=v1;
                                         //::setzen(vr,v1);
                                         // L->schreiben("kollision : vr =",vr);
                                         r=V3.schnittpunktgeradekugel(o1,vr,kugel->ort(),kugel->pradius+pradius,schnittpunkt,parameter);
                                         if((r)/*&&(parameter>=0)*/){
                                          n=schnittpunkt-kugel->ort();
                                          //::subtrahieren(n,schnittpunkt,kugel->port);
                                          n.normalisieren();
                                          if((n*vr)>0) return(false);
                                          return(true);
                                         };
                                        };
                                        return(false);
};
 void _kollidierbarkugel::bestimmenschnittstatisch(_partition::_sektor*sektor,bool&sa){
                                        _partition::_polygon*pit;
                                        _partition::_polygon*pitn;
                                        _listenknoten<_partition::_polygon >*lnpit;
                                        _listenknoten<_polygon> * ipit;
                                        _polygon*ipoly;
                                        _tg parameter;
                                        _vektor3<_tg> n;
                                        _vektor3<_tg> sp;
                                        _polygon*poly;
                                        _tg x0,x1,y0,y1,z0,z1;
                                        //-----------------------
                                        kopplungsaufrufe.aushaengen();
                                        if(sektor->wurzel()) statischerquader(x0,x1,y0,y1,z0,z1);
                                        new _verbinder<_partition::_sektor,_kollidierbarkugel>(this,sektor,sektor,this);
                                        //untersuchung, ob ein schnitt mit einem polygon oder einem portal erfolgt
                                        if(sektor->anfang(pit))do{
                                         if(pit->portal()){//-------------------------------------- portale untersuchen ----------------------------------------
                                          if((pit->markierungkollisionobjekt!=markierungkollision())||(pit->markierungkollisionrekursion!=zaehler())){
                                           pit->markierungkollisionobjekt=markierungkollision();
                                           pit->markierungkollisionrekursion=zaehler();
                                           if(pit->innerhalbkugel(ort(),pradius)){
                                            if(pit->anfang(lnpit))do{
                                             pitn=lnpit->objekt();
                                             if((pitn->markierungkollisionobjekt!=markierungkollision())||(pitn->markierungkollisionrekursion!=zaehler())){
                                              //nachbarportal ist unmarkiert un gültig
                                              //rekursion für sektoriteration einleiten
                                              pitn->markierungkollisionobjekt=markierungkollision();
                                              pitn->markierungkollisionrekursion=zaehler();
                                              if(pitn->innerhalbkugel(ort(),pradius)){    
                                               bestimmenschnittstatisch(pitn->sektor(),sa);
                                              };
                                             };
                                            }while(pit->naechstes(lnpit));//nachbarportaliteration
                                           };//inmnerhalb kugel verschiebungvolumen?
                                          };//portaalmarkierung gesetzt ?
                                         }else{// pit ist kein portal
                                          //------------------------------------- zonenpolygone untersuchen  -------------------------------------------
                                          poly=pit->polygon();
                                          if(poly->kollision()){
                                           if((poly->markierungkollisionobjekt!=markierungkollision())||(poly->markierungkollisionrekursion!=zaehler())){
                                            poly->markierungkollisionobjekt=markierungkollision();
                                            poly->markierungkollisionrekursion=zaehler();
                                            if(poly->innerhalbkugel(ort(),pradius)){
                                             _vektoranalysis3<_tg> va;
                                             _vektor3<_tg> lot;
                                             va.lotpunktebene(ort(),poly->vertex()->ort(),poly->normale(),lot,parameter);
                                             if(schnittpunkt.gamma>parameter){
                                              schnittpunkt.gamma=parameter;
                                              schnittpunkt.polygon=poly;
                                              schnittpunkt.kollidierbarkugel=0;
                                              schnittpunkt.normale=poly->normale();
                                              schnittpunkt.ort=ort()+lot;
                                              schnittpunkt.kontakt=ort()+lot;
                                              schnittpunkt.vektor.setzen(0,0,0);
                                              sa=true;
                                             };
                                            };
                                           };
                                          };
                                         };
                                        }while(sektor->naechstes(pit));
                                        //---------------------------------------interne sektorpolygone abiterieren----------------------------------
                                        if(kollisionintern()){
                                         if(sektor->wurzel()){
                                          bestimmenschnittstatischmitbaum(sektor->wurzel(),sektor,x0,x1,y0,y1,z0,z1,sa);
                                         }else{
                                          if(sektor->internepolygonestatisch()->anfang(ipit))do{
                                           ipoly=ipit->objekt();
                                           if(ipoly->kollision()){
                                            if((ipoly->markierungkollisionobjekt!=markierungkollision())||(ipoly->markierungkollisionrekursion!=zaehler())){
                                             ipoly->markierungkollisionobjekt=markierungkollision();
                                             ipoly->markierungkollisionrekursion=zaehler();
                                             if(ipoly->innerhalbkugel(ort(),pradius)){
                                              if(ipoly->nurkollisionskopplung()){
                                               kopplungsaufrufe.einhaengen(ipoly);
                                              }else{
                                               _vektoranalysis3<_tg> va;
                                               _vektor3<_tg> lot;
                                               va.lotpunktebene(ort(),ipoly->vertex()->ort(),ipoly->normale(),lot,parameter);
                                               if(schnittpunkt.gamma>parameter){
                                                schnittpunkt.gamma=parameter;
                                                schnittpunkt.polygon=ipoly;
                                                schnittpunkt.kollidierbarkugel=0;
                                                schnittpunkt.normale=ipoly->normale();
                                                schnittpunkt.ort=ort()+lot;
                                                schnittpunkt.kontakt=ort()+lot;
                                                schnittpunkt.vektor.setzen(0,0,0);
                                                sa=true;
                                               };
                                              };
                                             };
                                            };
                                           };
                                          }while(sektor->internepolygonestatisch()->naechstes(ipit));
                                          
                                          if(sektor->internepolygonedynamisch()->anfang(ipit))do{
                                           ipoly=ipit->objekt();
                                           if(ipoly->kollision()){
                                            if((ipoly->markierungkollisionobjekt!=markierungkollision())||(ipoly->markierungkollisionrekursion!=zaehler())){
                                             ipoly->markierungkollisionobjekt=markierungkollision();
                                             ipoly->markierungkollisionrekursion=zaehler();
                                             if(ipoly->innerhalbkugel(ort(),pradius)){
                                              if(ipoly->nurkollisionskopplung()){
                                               kopplungsaufrufe.einhaengen(ipoly);
                                              }else{
                                               _vektoranalysis3<_tg> va;
                                               _vektor3<_tg> lot;
                                               va.lotpunktebene(ort(),ipoly->vertex()->ort(),ipoly->normale(),lot,parameter);
                                               if(schnittpunkt.gamma>parameter){
                                                schnittpunkt.gamma=parameter;
                                                schnittpunkt.polygon=ipoly;
                                                schnittpunkt.kollidierbarkugel=0;
                                                schnittpunkt.normale=ipoly->normale();
                                                schnittpunkt.ort=ort()+lot;
                                                schnittpunkt.kontakt=ort()+lot;
                                                schnittpunkt.vektor.setzen(0,0,0);
                                                sa=true;
                                               };
                                              };
                                             };
                                            };
                                           };
                                          }while(sektor->internepolygonedynamisch()->naechstes(ipit));
                                          
                                          
                                         };
                                        };
                                        //----------------------------------------untersuchung mit den sektorinternen kollidierbaren--------------------
                                        /*_listenknoten<_kollidierbarkugel>*kkit;
                                        if(anfang(lnsit))do{
                                         sit=lnsit->objekt();
                                         if(sit->anfang(kkit ))do{
                                          if(kkit->objekt()->aktivitaet()){
                                           if(kkit->objekt()!=this){
                                            if(kollision(kkit->objekt(),o,v,n,sp,parameter)){
                                             if(schnittpunkt.gamma>parameter){
                                              schnittpunktaufgetreten=true;
                                              schnittpunkt.gamma=parameter;
                                              schnittpunkt.polygon=0;
                                              schnittpunkt.kollidierbarkugel=kkit->objekt();
                                              schnittpunkt.normale=n;
                                              schnittpunkt.ort=sp;
                                             };
                                            };
                                           };
                                          };
                                         }while(sit->naechstes(kkit));
                                        }while(naechstes(lnsit));
                                        */
                                        
 };
 void _kollidierbarkugel::bestimmenschnittstatischmitbaum(_baumoctalwuerfel<_polygon,_tg>*w,_partition::_sektor*sektor,const _tg x0,const _tg x1,const _tg y0,const _tg y1,const _tg z0,const _tg z1,bool&sa){
                                        if(w->innerhalb(x0,x1,y0,y1,z0,z1)){
                                         if(w->kinderlos()){
                                          //objekte prüfen
                                          _polygon*ipoly;
                                          _listenknoten<_polygon>*oit; 
                                          if(w->anfang(oit))do{
                                          
                                           ipoly=oit->objekt();
                                           if(ipoly->kollision()){
                                            if((ipoly->markierungkollisionobjekt!=markierungkollision())||(ipoly->markierungkollisionrekursion!=zaehler())){
                                             ipoly->markierungkollisionobjekt=markierungkollision();
                                             ipoly->markierungkollisionrekursion=zaehler();
                                             if(ipoly->innerhalbkugel(ort(),pradius)){
                                              if(ipoly->nurkollisionskopplung()){
                                               kopplungsaufrufe.einhaengen(ipoly);
                                              }else{
                                               _tg parameter;
                                               _vektoranalysis3<_tg> va;
                                               _vektor3<_tg> lot;
                                               va.lotpunktebene(ort(),ipoly->vertex()->ort(),ipoly->normale(),lot,parameter);
                                               if(schnittpunkt.gamma>parameter){
                                                schnittpunkt.gamma=parameter;
                                                schnittpunkt.polygon=ipoly;
                                                schnittpunkt.kollidierbarkugel=0;
                                                schnittpunkt.normale=ipoly->normale();
                                                schnittpunkt.ort=ort()+lot;
                                                schnittpunkt.kontakt=ort()+lot;
                                                schnittpunkt.vektor.setzen(0,0,0);
                                                sa=true;
                                               };
                                              };
                                             };
                                            };
                                           };
                                          }while(w->naechstes(oit));                                          
                                         }else{
                                          int i,j,k;
                                          for(i=0;i<2;i++)for(j=0;j<2;j++)for(k=0;k<2;k++) if(w->kind[i][j][k]) bestimmenschnittstatischmitbaum(w->kind[i][j][k],sektor,x0,x1,y0,y1,z0,z1,sa);
                                         };
                                        };
 };

_tg _kollidierbarkugel::laengevorkollision()const{
                                        return(plaengevorkollision);
};
//*********************************************************************************************************************************************************************************
//                                                                K O L L I D I E R B A R P O L Y G O N T R A N S L A T I O N 
//*********************************************************************************************************************************************************************************
_kollidierbarpolygontranslation::_kollidierbarpolygontranslation(_kollisionskopplung*kk,_welt*w,_partition::_zone*pz,_partition::_sektor*ps,_polygon*p,const _vektor3<_tg>&v):_kollidierbar(kk,w,pz,ps,p->vertex()->ort(),v){
                                        ppolygon=p;
                                        plaengevorkollision=0;
                                        aktualisieren();
};
_kollidierbarpolygontranslation::~_kollidierbarpolygontranslation(){
                                        if(wp)delete wp;
                                        wp=0;
                                        pvektoren.loeschen();
};
void _kollidierbarpolygontranslation::aktualisieren(){
                                        pvektoren.loeschen();
                                        _vertex*vit;
                                        //_listenknoten<_vertex>*lnvit;
                                        vit=ppolygon->vertex();
                                        vit=vit->naechstes(ppolygon);
                                        do{
                                         pvektoren.einhaengen(new _vektor3<_tg>(vit->ort()- ppolygon->vertex()->ort()));
                                         vit=vit->naechstes(ppolygon); 
                                        }while(vit!=ppolygon->vertex());
                                        
};
bool _kollidierbarpolygontranslation::bewegen(const _vektor3<_tg>&beschleunigung){
                                        _polygon*zuletztkollidiert=0;
                                        bool r;
                                        //--------------------------------
                                        vorbereitenbewegen();
                                        schnittpunkt.polygon=0;
                                        schnittpunkt.kollidierbarkugel=0;
                                        schnittpunkt.gamma=1002;
                                        _vektor3<_tg> o=ort();
                                        _vektor3<_tg> v=vektor();
                                        
                                        r=bewegen(o,v,beschleunigung,beschleunigung.laenge(),zuletztkollidiert);
                                        // ***** DEBUG*****
                                        //if(wp) delete wp;
                                        //wp=new _weltdebugpfeil(zone()->welt(),port,port+pvektor,0.005,0.005,_vektor<_to>(1,1,1));
                                        // ****************
                                        if(r==false) _kollidierbar::bewegen();
                                        return(r);
};                            
bool _kollidierbarpolygontranslation::bewegen(_vektor3<_tg>&o,_vektor3<_tg>&v,const _vektor3<_tg>&beschleunigung,const _tg beschleunigunglaenge,_polygon*&zuletztkollidiert){
                                        //-------------------------
                                        schnittpunkt.gamma=1002;
                                        zuletztkollidiert=0;
                                        if(zone()==0) bestimmenzone();
                                        stammsektor(zone()->sektor(o));
                                        if(stammsektor()==0) {
                                         L->schreiben("Fehler : bool _kollidierbarpolygontranslation : sektor nicht bestimmbar");
                                         notfallruecksetzen();
                                         return(false);
                                        };
                                        _liste<_partition::_sektor>::aushaengen();
                                        bool sa=false;
                                        bestimmenschnittpunkt(o,v,stammsektor(),sa);
                                        if(berechnenausfall(sa,o,v,beschleunigung,beschleunigunglaenge,zuletztkollidiert)){
                                         aufrufenkopplung();
                                         if(maximalerekursion()) {
                                          _vektor3<_tg> reko=schnittort;
                                          _vektor3<_tg> rekv=ausfallsvektor;
                                          if(bewegen(reko,rekv,beschleunigung,beschleunigunglaenge,zuletztkollidiert)==false) {
                                           ort(schnittort+ausfallsvektor);
                                          };
                                         }else{
                                          //maximale rekursionstiefe erreciht 
                                          //maßnahmen einleiten
                                          ort(schnittort);
                                         };
                                         return(true);
                                        };
                                        return(false);
};
void _kollidierbarpolygontranslation::bestimmenschnittpunkt(const _vektor3<_tg>&o,const _vektor3<_tg>&v,_partition::_sektor*sektor,bool&schnittpunktaufgetreten){
                                        _partition::_polygon*pit;
                                        _partition::_polygon*pitn;
                                        _listenknoten<_partition::_polygon >*lnpit;
                                        _listenknoten<_polygon> * ipit;
                                        _polygon*ipoly;
                                        _tg parameter;
                                        _vektor3<_tg> n;
                                        _vektor3<_tg> sp;
                                        _polygon*poly;
                                        //-----------------------
                                        new _verbinder<_partition::_sektor,_kollidierbarpolygontranslation>(this,sektor,sektor,this);
                                        //untersuchung, ob ein schnitt mit einem polygon oder einem portal erfolgt
                                        if(sektor->anfang(pit))do{
                                         if(pit->portal()){//-------------------------------------- portale untersuchen ----------------------------------------
                                          if((pit->markierungkollisionobjekt!=markierungkollision())||(pit->markierungkollisionrekursion!=zaehler())){
                                           pit->markierungkollisionobjekt=markierungkollision();
                                           pit->markierungkollisionrekursion=zaehler();
                                           if(pit->innerhalbpolygontranslation(ppolygon,o,&pvektoren,v)){
                                            if(pit->anfang(lnpit))do{
                                             pitn=lnpit->objekt();
                                             if((pitn->markierungkollisionobjekt!=markierungkollision())||(pitn->markierungkollisionrekursion!=zaehler())){
                                              //nachbarportal ist unmarkiert un gültig
                                              //rekursion für sektoriteration einleiten
                                              pitn->markierungkollisionobjekt=markierungkollision();
                                              pitn->markierungkollisionrekursion=zaehler();
                                              if(pitn->innerhalbpolygontranslation(ppolygon,o,&pvektoren,v)){    
                                               bestimmenschnittpunkt(o,v,pitn->sektor(),schnittpunktaufgetreten);
                                              };
                                             };
                                            }while(pit->naechstes(lnpit));//nachbarportaliteration
                                           };//inmnerhalb kugel verschiebungvolumen?
                                          };//portalmarkierung gesetzt ?
                                         }else{// pit ist kein portal
                                          //------------------------------------- zonenpolygone untersuchen -------------------------------------------
                                          poly=pit->polygon();
                                          if(poly->kollision()){
                                           if((poly->markierungkollisionobjekt!=markierungkollision())||(poly->markierungkollisionrekursion!=zaehler())){
                                            poly->markierungkollisionobjekt=markierungkollision();
                                            poly->markierungkollisionrekursion=zaehler();
                                            if(poly->innerhalbpolygontranslation(ppolygon,o,&pvektoren,v,true)){
                                             if(poly->schnittpunktpolygontranslation(ppolygon,o,&pvektoren,v,n,sp,parameter)){
                                              if(schnittpunkt.gamma>parameter){
                                               schnittpunktaufgetreten=true;
                                               schnittpunkt.gamma=parameter;
                                               schnittpunkt.polygon=poly;
                                               schnittpunkt.kollidierbarkugel=0;
                                               schnittpunkt.normale=n;
                                               schnittpunkt.ort=sp;
                                               schnittpunkt.kontakt=sp;//-n*(pradius-nahenull*4);
                                               schnittpunkt.vektor=v;
                                              };
                                             };
                                            };
                                           };
                                          };
                                         };
                                        }while(sektor->naechstes(pit));
                                        //---------------------------------------interne sektorpolygone abiterieren----------------------------------
                                        if(kollisionintern()){
                                         if(sektor->internepolygonestatisch()->anfang(ipit))do{
                                          ipoly=ipit->objekt();
                                          if(ipoly->kollision()){
                                           if((ipoly->markierungkollisionobjekt!=markierungkollision())||(ipoly->markierungkollisionrekursion!=zaehler())){
                                            ipoly->markierungkollisionobjekt=markierungkollision();
                                            ipoly->markierungkollisionrekursion=zaehler();
                                            if(ipoly->innerhalbpolygontranslation(ppolygon,o,&pvektoren,v,true)){
                                             if(ipoly->schnittpunktpolygontranslation(ppolygon,o,&pvektoren,v,n,sp,parameter)){
                                              if(schnittpunkt.gamma>parameter){
                                               schnittpunktaufgetreten=true;
                                               schnittpunkt.gamma=parameter;
                                               schnittpunkt.polygon=ipoly;
                                               schnittpunkt.kollidierbarkugel=0;
                                               schnittpunkt.normale=n;
                                               schnittpunkt.ort=sp;
                                               schnittpunkt.kontakt=sp;//-n*(pradius-nahenull*4);
                                               schnittpunkt.vektor=v;
                                              };
                                             };
                                            };
                                           };
                                          };
                                         }while(sektor->internepolygonestatisch()->naechstes(ipit));
                                         if(sektor->internepolygonedynamisch()->anfang(ipit))do{
                                          ipoly=ipit->objekt();
                                          if(ipoly->kollision()){
                                           if((ipoly->markierungkollisionobjekt!=markierungkollision())||(ipoly->markierungkollisionrekursion!=zaehler())){
                                            ipoly->markierungkollisionobjekt=markierungkollision();
                                            ipoly->markierungkollisionrekursion=zaehler();
                                            if(ipoly->innerhalbpolygontranslation(ppolygon,o,&pvektoren,v,true)){
                                             if(ipoly->schnittpunktpolygontranslation(ppolygon,o,&pvektoren,v,n,sp,parameter)){
                                              if(schnittpunkt.gamma>parameter){
                                               schnittpunktaufgetreten=true;
                                               schnittpunkt.gamma=parameter;
                                               schnittpunkt.polygon=ipoly;
                                               schnittpunkt.kollidierbarkugel=0;
                                               schnittpunkt.normale=n;
                                               schnittpunkt.ort=sp;
                                               schnittpunkt.kontakt=sp;//-n*(pradius-nahenull*4);
                                               schnittpunkt.vektor=v;
                                              };
                                             };
                                            };
                                           };
                                          };
                                         }while(sektor->internepolygonedynamisch()->naechstes(ipit));
                                        };
                                        //----------------------------------------untersuchung mit den sektorinternen kollidierbaren--------------------
                                       /* _listenknoten<_kollidierbarkugel>*kkit;
                                        if(anfang(lnsit))do{
                                         sit=lnsit->objekt();
                                         if(sit->anfang(kkit ))do{
                                          //if(kkit->objekt()!=this){
                                           //if(kollision(kkit->objekt(),o,v,n,sp,parameter)){
                                            if(schnittpunkt.gamma>parameter){
                                             schnittpunktaufgetreten=true;
                                             schnittpunkt.gamma=parameter;
                                             schnittpunkt.polygon=0;
                                             schnittpunkt.kollidierbarkugel=kkit->objekt();
                                             schnittpunkt.normale=n;
                                             schnittpunkt.ort=sp;
                                            };
                                           //};
                                          //};
                                         }while(sit->naechstes(kkit));
                                        }while(naechstes(lnsit));*/
};  
//*********************************************************************************************************************************************************************************
//                                                                K O L L I D I E R B A R N E T Z T R A N S L A T I O N 
//*********************************************************************************************************************************************************************************
_kollidierbarnetztranslation::_kollidierbarnetztranslation(_kollisionskopplung*kk,_welt*w,_partition::_zone*pz,_partition::_sektor*ps,_netz*n,const _vektor3<_tg>&v):_kollidierbar(kk,w,pz,ps,_vektor3<_tg>(0,0,0),v){
                                        pnetz=n;
                                        aktualisieren();
                                        pkollisionszaehlerkante=0;
};
_kollidierbarnetztranslation::~_kollidierbarnetztranslation(){
};
void _kollidierbarnetztranslation::aktualisieren(){
                                        _polygon*pit;
                                        if(pnetz->anfang(pit)) ort(pit->vertex()->ort());
                                     //   L->schreiben("_kollid.netztransl.:aktualisiere: ort =",ort());
};
_netz* _kollidierbarnetztranslation::netz(){
                                        return(pnetz);
};

bool _kollidierbarnetztranslation::berechnenausfall(bool schnittpunktaufgetreten,_vektor3<_tg>&o,_vektor3<_tg>&v,const _vektor3<_tg>&beschleunigung,const _tg beschleunigunglaenge,_polygon*&zuletztkollidiert){
                                        //_tg sl;
                                        _vektor3<_tg> lot;
                                        _vektor3<_tg> h;
                                        _vektor3<_tg> n;
                                        //_tg daempfung;
                                        _vektor3<_tg> daempfungsvektor;
                                        //_tg para;
                                        //--------------
                                        if(schnittpunktaufgetreten){
                                         if(schnittpunkt.polygon){//-----------------------------------------------------------  POLYGON - KOLLISION ------------------------------------------------
                                          //schnittpunkt.reflektieren();
                                          schnittpunkt.abgleiten();
                                         
                                         
                                         /*
                                          //schnittvektor ist einfallvektor vom alten ort o bis zum schnittort sit->ort
                                          //anschließende beschleunigungitationsbetrachtung, projektion durchführen, daempfung bestimmen
                                          einfallsvektor=schnittpunkt.ort-schnittpunkt.kontakt;
                                          einfallsvektor-=o;
                                          sl=einfallsvektor.laenge();
                                          //dämpfung nach anteiligmachung des beschleunigungitationsbetrages
                                          para=sl/pvektorlaenge;
                                          _vektor3<_tg> bn=beschleunigung;
                                          bn.normalisieren();
                                          _vektor3<_tg> vn=v-beschleunigung;
                                          vn.normalisieren();
                                          daempfung=beschleunigunglaenge*(1-(para));//*fabs(bn*vn);
                                          //reflektion durchführen ergebnis landet in schnittvektor
                                          //daempfungsvektor bestimmt, er sollte theoretisch nie länger werden
                                          //als der ausfallsvektor (schnittvektor);
                                          //V3.lotpunktgerade(o,o+einfallsvektor,schnittpunkt.normale,lot);
                                          n=schnittpunkt.normale;
                                          _tg nmn=n*n;
                                          h=o+einfallsvektor;
                                          _tg hhh=((o[0]-h[0])*n[0] + (o[1]-h[1])*n[1] + (o[2]-h[2])*n[2])/nmn;
                                          lot.setzenkomponente(0,(h[0]-o[0])+n[0]*hhh);//lot punt auf gerade (o,h,n,lot);
                                          lot.setzenkomponente(1,(h[1]-o[1])+n[1]*hhh);
                                          lot.setzenkomponente(2,(h[2]-o[2])+n[2]*hhh);
                                          //ausfallsvektor=(o+lot*2)-(o+einfallsvektor);
                                          ausfallsvektor.setzenkomponente(0,(o[0]+lot[0]*2)-h[0]);
                                          ausfallsvektor.setzenkomponente(1,(o[1]+lot[1]*2)-h[1]);
                                          ausfallsvektor.setzenkomponente(2,(o[2]+lot[2]*2)-h[2]);
                                          ausfallsvektor.normalisieren();
                                          if(daempfung>=(pvektorlaenge-sl)) daempfung=(pvektorlaenge-sl)*(1-(2*nahenull));
                                          //daempfungsvektor=-ausfallsvektor*daempfung;
                                          daempfungsvektor=ausfallsvektor;
                                          daempfungsvektor*=-daempfung;
                                          vektor()=ausfallsvektor;
                                          vektor()*=pvektorlaenge;
                                          vektor()+=daempfungsvektor;
                                          ausfallsvektor*=pvektorlaenge-sl;
                                          ausfallsvektor+=daempfungsvektor;
                                          //unscharf korrigierte postition für die rekurstionseineitung
                                          //bestimmen (schnittort wird entlang des einfallsvektors um
                                          //den betrag 2*nahenull zurückgesetzt
                                          //_vektor<_tg> zurueck=o-sit->ort;
                                          if(sl<=(nahenull*2)){
                                           schnittort=o+schnittpunkt.kontakt;
                                           L->schreiben("hu.....................");
                                          }else{
                                           einfallsvektor.normalisieren();
                                           schnittort=schnittpunkt.ort;
                                           schnittort-=einfallsvektor*2*nahenull;
                                           L->schreiben("haaaa.....................");
                                          };
                                          */
                                         }else
                                         if(schnittpunkt.kollidierbarkugel){//------------------------------------------------- KUGEL - KUGEL - KOLLISION -------------------------------------------------
                                         }else{
                                         
                                         };
                                         return(true);
                                        };
                                        return(false);
};
void _kollidierbarnetztranslation::auswertenschnittpunkt(){
                                        
                            
                                       //  L->schreiben("--------------------- Schnittpunkt auswertung ---------------- "); 
                                        //_polygon*pit;
                                        //_vertex*vit;
                                        //_verbindervertexpolygon*cit;
                                        _schnittpunktkollision*sit;
                                        unsigned int c=schnittpunktliste.anzahl();
                                        if(c==0) return;
                                        if(c==1) {
                                         schnittpunktliste.anfang(sit);
                                         schnittpunkt.kopieren(sit);
                                        }else if(c>1){
                                         _vektor3<_tg> n;
                                         if(schnittpunktliste.anfang(sit))do{
                                          n+=sit->normale;
                                          //L->schreiben("addiert normale =",*sit->verbinder->polygon());
                                          //L->schreiben("n =",n);
                                         }while(schnittpunktliste.naechstes(sit));                                         
                                         n.normalisieren();
                                         schnittpunktliste.anfang(sit);
                                         schnittpunkt.kopieren(sit);
                                         schnittpunkt.normale=n;
                                         return;
                                        
                            /*             //eine Kantenschnittsituation liegt vor
                                         //wenn nur eine kante betroffen ist
                                         L->schreiben("Kollisionszaehlerkante : ",(int)pkollisionszaehlerkante);
                                         if(pkollisionszaehlerkante==4){
                                          _vektor3<_tg> n;
                                          if(schnittpunktliste.anfang(sit))do{
                                           if(sit->verbinder){
                                            n += *sit->verbinder->polygon();
                                            L->schreiben("addiert normale =",*sit->verbinder->polygon());
                                            L->schreiben("n =",n);
                                           };
                                          }while(schnittpunktliste.naechstes(sit));
                                          //n*=1.0f/_tg(c);
                                          n.normalisieren();
                                          schnittpunktliste.anfang(sit);
                                          schnittpunkt.kopieren(sit);
                                          schnittpunkt.normale=n;
                                          return;
                                         };

                                         //die anzahl der schnitte an den kanten in
                                         //eine anzahl des polygons überführen
                                         pnetz->markierungpolygon(0);
                                         if(pnetz->anfang(pit))do{
                                          vit=pit->vertex();
                                          if(vit)do{
                                           cit=vit->connector(pit);
                                           pit->markierung(pit->markierung()+cit->kollisionszaehler());
                                           vit=cit->naechstervertex();
                                          }while(vit!=pit->vertex());
                                         }while(pnetz->naechstes(pit));
                                         //polygonmarkierungen untersuchen
                                         //das polygon mit der höchsten markierung 
                                         //bestimmt die normale
                                         unsigned int hm=0;
                                         if(pnetz->anfang(pit))do{
                                          if (pit->markierung()>hm) hm=pit->markierung();
                                         }while(pnetz->naechstes(pit));
                                         //gibt es mehr als ein polygon mit der höchsten markierung
                                         //dann kann die normale eines cau
                                         unsigned int ahm=0;
                                         _polygon*mp=0;
                                         if(pnetz->anfang(pit))do{
                                          if (pit->markierung()==hm) {
                                           ahm++;
                                           mp=pit;
                                          };
                                         }while(pnetz->naechstes(pit));
                                         L->schreiben("hoechste Kollisionszahl an einem Polygon : ",(int)hm);
                                         L->schreiben("das haben Anzahl poly : ",(int)ahm);
                                         
                                         if(ahm==1){
                                          schnittpunktliste.anfang(sit);
                                          schnittpunkt.kopieren(sit);
                                          schnittpunkt.normale=-*mp;
                                          L->schreiben ("Schnittpunkt normale =",schnittpunkt.normale);
                                         }else{
                                          
                                         
                                          schnittpunktliste.anfang(sit);
                                          schnittpunkt.kopieren(sit);
                                          schnittpunkt.normale.setzen(0,0,0);
                                         };
                                         
                                         
                                        */ 
                                        };
                                        
};

bool _kollidierbarnetztranslation::bewegen(const _vektor3<_tg>&beschleunigung){
                                        _polygon*zuletztkollidiert=0;
                                        bool r=false;
                                        //--------------------------------
                                    //    L->schreiben("Kollidierbarnetztranslation");
                                        vorbereitenbewegen();
                                        pnetz->kollisionszaehlerverbinder(0);
                                        aktualisieren();
                                        _vektor3<_tg> o=ort();
                                        _vektor3<_tg> v=vektor();
                                        r=bewegen(o,v,beschleunigung,beschleunigung.laenge(),zuletztkollidiert);
                                        if(r==false) _kollidierbar::bewegen();
                                        return(r);
};                            
bool _kollidierbarnetztranslation::testen(){
                                        vorbereitenbewegen();
                                        aktualisieren();
                                        if(zone()==0) bestimmenzone();
                                        stammsektor(zone()->sektor(ort()));
                                        if(stammsektor()==0) L->schreiben("Fehler : bool _kollidierbarpolygonfest : sektor nicht bestimmbar");
                                        _liste<_partition::_sektor>::aushaengen();
                                        bool sa=false;
                                        bestimmenschnittpunkt(ort(),vektor(),stammsektor(),sa);
                                        if(sa) return(false); else return(true);
};
bool _kollidierbarnetztranslation::bewegen(_vektor3<_tg>&o,_vektor3<_tg>&v,const _vektor3<_tg>&beschleunigung,const _tg beschleunigunglaenge,_polygon*&zuletztkollidiert){
                                        //-------------------------
                                        zuletztkollidiert=0;
                                        if(zone()==0) bestimmenzone();
                                        stammsektor(zone()->sektor(o));
                                        if(stammsektor()==0){
                                         L->schreiben("Fehler : bool _kollidierbarnetzfest : sektor nicht bestimmbar");
                                         notfallruecksetzen();
                                         return(false);
                                        };
                                        _liste<_partition::_sektor>::aushaengen();
                                        schnittpunkt.ruecksetzen();
                                        loeschenschnittpunkt();   
                                        ruecksetzenkollisionszaehlerkante();                                                                             
                                        bool sa=false;
                                        bestimmenschnittpunkt(o,v,stammsektor(),sa);
                                        auswertenschnittpunkt();
                                        if(berechnenausfall(sa,o,v,beschleunigung,beschleunigunglaenge,zuletztkollidiert)){
                                         aufrufenkopplung();
                                         if(maximalerekursion()) {
                                          //schnittpunkt.loggen();
                                          _vektor3<_tg> reko=schnittpunkt.ortabstand-schnittpunkt.kontakt;
                                          _vektor3<_tg> rekv=schnittpunkt.ausfall;
                                          if(bewegen(reko,rekv,beschleunigung,beschleunigunglaenge,zuletztkollidiert)==false) {
                                           ort((schnittpunkt.ortabstand-schnittpunkt.kontakt)+schnittpunkt.ausfall);
                                        //   L->schreiben("Ergebnis ort = ",ort());
                                          };
                                         }else{
                                          //maximale rekursionstiefe erreciht 
                                          //maßnahmen einleiten
                                          ort(schnittpunkt.ortabstand-schnittpunkt.kontakt);
                                       //   L->schreiben("Ergebnismaxrek ort = ",ort());
                                         };
                                         return(true);
                                        };
                                        return(false);
};
void _kollidierbarnetztranslation::bestimmenschnittpunkt(const _vektor3<_tg>&o,const _vektor3<_tg>&v,_partition::_sektor*sektor,bool&schnittpunktaufgetreten){
                                        _partition::_polygon*pit;
                                        _partition::_polygon*pitn;
                                        _listenknoten<_partition::_polygon >*lnpit;
                                        _listenknoten<_polygon> * ipit;
                                        _polygon*ipoly;
                                        //_tg parameter;
                                        _vektor3<_tg> n;
                                        _vektor3<_tg> sp;
                                        _vektor3<_tg> spr;
                                        _polygon*poly;
                                        //-----------------------
                                        new _verbinder<_partition::_sektor,_kollidierbarnetztranslation>(this,sektor,sektor,this);
                                        //untersuchung, ob ein schnitt mit einem polygon oder einem portal erfolgt
                                        if(sektor->anfang(pit))do{
                                         if(pit->portal()){//-------------------------------------- portale untersuchen ----------------------------------------
                                          if((pit->markierungkollisionobjekt!=markierungkollision())||(pit->markierungkollisionrekursion!=zaehler())){
                                           pit->markierungkollisionobjekt=markierungkollision();
                                           pit->markierungkollisionrekursion=zaehler();
                                           if(pit->innerhalbnetztranslation(pnetz,o,v)){
                                            if(pit->anfang(lnpit))do{
                                             pitn=lnpit->objekt();
                                             if((pitn->markierungkollisionobjekt!=markierungkollision())||(pitn->markierungkollisionrekursion!=zaehler())){
                                              //nachbarportal ist unmarkiert und gültig
                                              //rekursion für sektoriteration einleiten
                                              pitn->markierungkollisionobjekt=markierungkollision();
                                              pitn->markierungkollisionrekursion=zaehler();
                                              if(pitn->innerhalbnetztranslation(pnetz,o,v)){    
                                               bestimmenschnittpunkt(o,v,pitn->sektor(),schnittpunktaufgetreten);
                                              };
                                             };
                                            }while(pit->naechstes(lnpit));//nachbarportaliteration
                                           };//inmnerhalb kugel verschiebungvolumen?
                                          };//portalmarkierung gesetzt ?
                                         }else{// pit ist kein portal
                                          //------------------------------------- zonenpolygone untersuchen -------------------------------------------
                                          poly=pit->polygon();
                                          if(poly->netz()!=pnetz){//eigenkollision verhindern
                                           if(poly->kollision()){
                                            if((poly->markierungkollisionobjekt!=markierungkollision())||(poly->markierungkollisionrekursion!=zaehler())){
                                             poly->markierungkollisionobjekt=markierungkollision();
                                             poly->markierungkollisionrekursion=zaehler();
                                           //  if(poly->innerhalbnetztranslation(pnetz,o,v,true)){
                                              if(poly->schnittpunktnetztranslation(this,o,v)){
                                                schnittpunktaufgetreten=true;
                                               //if(schnittpunkt.gamma>parameter) setzenschnittpunkt(poly,o,v,parameter,sp,spr,n,schnittpunktaufgetreten);
                                              };
                                             };
                                            //};
                                           };
                                          };
                                         };
                                        }while(sektor->naechstes(pit));
                                        //---------------------------------------interne sektorpolygone abiterieren----------------------------------
                                        if(kollisionintern()){
                                         if(sektor->internepolygonestatisch()->anfang(ipit))do{
                                          ipoly=ipit->objekt();
                                          if(ipoly->netz()!=pnetz){//eigenkollision verhindern
                                           if(ipoly->kollision()){
                                            if((ipoly->markierungkollisionobjekt!=markierungkollision())||(ipoly->markierungkollisionrekursion!=zaehler())){
                                             ipoly->markierungkollisionobjekt=markierungkollision();
                                             ipoly->markierungkollisionrekursion=zaehler();
                                             //if(ipoly->innerhalbnetztranslation(pnetz,o,v,true)){
                                              if(ipoly->schnittpunktnetztranslation(this,o,v)){
                                                schnittpunktaufgetreten=true;
                                               //if(schnittpunkt.gamma>parameter) 
                                               //setzenschnittpunkt(ipoly,o,v,parameter,sp,spr,n,schnittpunktaufgetreten);
                                              };
                                             //};
                                            };
                                           };
                                          };
                                         }while(sektor->internepolygonestatisch()->naechstes(ipit));
                                         if(sektor->internepolygonedynamisch()->anfang(ipit))do{
                                          ipoly=ipit->objekt();
                                          if(ipoly->netz()!=pnetz){//eigenkollision verhindern
                                           if(ipoly->kollision()){
                                            if((ipoly->markierungkollisionobjekt!=markierungkollision())||(ipoly->markierungkollisionrekursion!=zaehler())){
                                             ipoly->markierungkollisionobjekt=markierungkollision();
                                             ipoly->markierungkollisionrekursion=zaehler();
                                             //if(ipoly->innerhalbnetztranslation(pnetz,o,v,true)){
                                              if(ipoly->schnittpunktnetztranslation(this,o,v)){
                                               //if(schnittpunkt.gamma>parameter) setzenschnittpunkt(ipoly,o,v,parameter,sp,spr,n,schnittpunktaufgetreten);
                                               schnittpunktaufgetreten=true;
                                              };
                                             //};
                                            };
                                           };
                                          };
                                         }while(sektor->internepolygonedynamisch()->naechstes(ipit));
                                        };
                                        //----------------------------------------untersuchung mit den sektorinternen kollidierbaren--------------------
                                       /* _listenknoten<_kollidierbarkugel>*kkit;
                                        if(anfang(lnsit))do{
                                         sit=lnsit->objekt();
                                         if(sit->anfang(kkit ))do{
                                          //if(kkit->objekt()!=this){
                                           //if(kollision(kkit->objekt(),o,v,n,sp,parameter)){
                                            if(schnittpunkt.gamma>parameter){
                                             schnittpunktaufgetreten=true;
                                             schnittpunkt.gamma=parameter;
                                             schnittpunkt.polygon=0;
                                             schnittpunkt.kollidierbarkugel=kkit->objekt();
                                             schnittpunkt.normale=n;
                                             schnittpunkt.ort=sp;
                                            };
                                           //};
                                          //};
                                         }while(sit->naechstes(kkit));
                                        }while(naechstes(lnsit));*/
};  
void _kollidierbarnetztranslation::ruecksetzenkollisionszaehlerkante(){
                                        pkollisionszaehlerkante=0;
};
void _kollidierbarnetztranslation::inkrementierenkollisionszaehlerkante(){
                                        pkollisionszaehlerkante++;
};


//*********************************************************************************************************************************************************************************
//                                                                S C H N I T T P U N K T K O L L I S I O N 
//*********************************************************************************************************************************************************************************
_schnittpunktkollision::_schnittpunktkollision(_kollidierbar*k,_polygon*p,_verbindervertexpolygon*c,const _vektor3<_tg>&o,const _vektor3<_tg>&v,_tg g,const _vektor3<_tg>&sp,const _vektor3<_tg>&ko,const _vektor3<_tg>&no):_listenknotenbasis<_schnittpunktkollision>(&k->schnittpunktliste){
                                            kollidierbar=k;
                                            verbinder=c;
                                            ortalt=o;
                                            vektor=v;
                                            gamma=g;
                                            polygon=p;
                                            normale=no;
                                            kontakt=ko;
                                            ort=sp;
                                            kollidierbarkugel=0;
};
_schnittpunktkollision::_schnittpunktkollision(_kollidierbar*k){
                                            kollidierbar=k;
                                            normale.setzen(1,0,0);
                                            gamma=1001;
                                            polygon=0;
                                            verbinder=0;
                                            kollidierbarkugel=0;
};
_schnittpunktkollision::~_schnittpunktkollision(){
};
void _schnittpunktkollision::setzen(_polygon*p,_verbindervertexpolygon*c,const _vektor3<_tg>&o,const _vektor3<_tg>&v,_tg g,const _vektor3<_tg>&sp,const _vektor3<_tg>&ko,const _vektor3<_tg>&no){
                                            ortalt=o;
                                            vektor=v;
                                            gamma=g;
                                            polygon=p;
                                            verbinder=c;
                                            normale=no;
                                            kontakt=ko;
                                            ort=sp;
                                            kollidierbarkugel=0;
};
void _schnittpunktkollision::kopieren(_schnittpunktkollision*s){
                                            ortalt=s->ortalt;
                                            vektor=s->vektor;
                                            gamma=s->gamma;
                                            polygon=s->polygon;
                                            verbinder=s->verbinder;
                                            normale=s->normale;
                                            kontakt=s->kontakt;
                                            ort=s->ort;
                                            kollidierbarkugel=s->kollidierbarkugel;
};


void _schnittpunktkollision::ruecksetzen(){
                                            gamma=1000;
                                            polygon=0;
                                            kollidierbarkugel=0;
                                            verbinder=0;
};

void _schnittpunktkollision::reflektieren(){
                                            einfall=vektor;
                                            einfallnormal=einfall;
                                            einfallnormal.normalisieren();
                                            if(normale.laenge()>nahenull){
                                             ausfallnormal=einfallnormal;
                                             ausfallnormal.reflektieren(normale);
                                             ausfallnormal.normalisieren();
                                             ausfall=ausfallnormal;
                                             einfall*=gamma;
                                             ausfall*=(1-gamma)*einfall.laenge();
                                             ortabstand=ort;
                                             ortabstand-=einfallnormal*2*nahenull;
                                             ortneu=(ortabstand-kontakt)+ausfall;
                                            }else{
                                             ausfall.setzen(0,0,0);
                                             ausfallnormal.setzen(0,0,0);
                                             ortabstand=ort;
                                             ortabstand-=einfallnormal*2*nahenull;
                                             ortneu=(ortabstand-kontakt);
                                            };
};                                          
void _schnittpunktkollision::abgleiten(){
                                            einfall=vektor;
                                            einfallnormal=einfall;
                                            einfallnormal.normalisieren();
                                            if(normale.laenge()>nahenull){
                                             ausfall=einfall;
                                             einfall*=gamma;
                                             ausfall*=1-gamma;
                                             ausfallnormal=ausfall;//()einfallnormal;//*(1-gamma);
                                             //ausfallnormal.normalisieren();
                                             ausfall.projizierenebene(normale);
                                             ortabstand=ort;
                                             ortabstand-=einfallnormal*2*nahenull;
                                             ortneu=(ortabstand-kontakt)+ausfall;
                                            }else{
                                             ausfall.setzen(0,0,0);
                                             ausfallnormal.setzen(0,0,0);
                                             ortabstand=ort;
                                             ortabstand-=einfallnormal*2*nahenull;
                                             ortneu=(ortabstand-kontakt);
                                            };
};
void _schnittpunktkollision::loggen(){                                          
                                            L->schreiben("-------------------------- Schnittpunkt Kollisionskontakt ---------------------------");
                                            L->schreiben("ort = ",ort);
                                            L->schreiben("normale = ",normale);
                                            L->schreiben("vektor = ",vektor);
                                            L->schreiben("gamma = ",gamma);
                                            L->schreiben("kontakt = ",kontakt);
                                            L->schreiben("ortabstand = ",ortabstand);
                                            L->schreiben("einfall = "   ,einfall);
                                            L->schreiben("ausfall = "   ,ausfall);
                                            L->schreiben("einfallnormal = ",einfallnormal);
                                            L->schreiben("ausfallnormal = ",ausfallnormal);
                                            L->schreiben("ortabstand-kontakt = ",ortabstand-kontakt);
                                            L->schreiben("-------------------------------------------------------------------------------------");
};                                          

//*********************************************************************************************************************************************************************************
//                                                                K O L L I S I O N S K O P P L U N G
//*********************************************************************************************************************************************************************************
_kollisionskopplung::_kollisionskopplung(){
};
_kollisionskopplung::~_kollisionskopplung(){
};
void _kollisionskopplung::kollision(_kollidierbar*,_polygon*){
};
void _kollisionskopplung::kollision(_kollidierbar*){
};
