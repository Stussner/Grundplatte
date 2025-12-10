
//******************************************************************************************************************************************************************************************************
//  Projekt     : grundplatte
//  Bilbliothek : _grundplatte.lib
//  Modul       : _grafik.cpp
//  Datum       : 29.08.2008
//  Änderung    : 29.08.2008
//******************************************************************************************************************************************************************************************************
#include <_grafik.hpp>

_grafik::_grafik(bool fullscreen,unsigned int x,unsigned int y,unsigned int sx,unsigned int sy,unsigned int sz,unsigned int ra){
																pfullscreen=fullscreen;
																prate=ra;
                                                                groesse(sx,sy,sz);
																position(x,y);
                                                                normale(true);
                                                               // normallowest(0,0,0);
                                                               // normalhighest(1,1,1);
                                                              //  lowerleft();
                                                                pactivity=true;
                                                                schattenbild=0;
                                                                pkontext=0;
                                                                //pfensterkontrolle=kontrollefenster;
};

_grafik::~_grafik(){
                                                                //plistebildhardware.loeschen();
                                                               // plistezeichensatz.loeschen();
};
void _grafik::loeschenbildhardwareliste(){
																plistebildhardware.loeschen();
};
_listebasis<_bildhardware>*_grafik::listebildhardware(){
                                                                return(&plistebildhardware);
};
_listebasis<_zeichensatz>*_grafik::listezeichensatz(){
                                                                return(&plistezeichensatz);
};
 _zeichensatzbild*_grafik::erzeugenzeichensatz(int size,int weight,_zeichenkette<char>const&name){
                                                                return(new _zeichensatzbild(this,name));
};
unsigned int _grafik::kontext()const{
                                                                return(pkontext);
};
void _grafik::kontext(unsigned int k){
                                                                pkontext=k;
};
/*
void _grafik::fensterkontrolle(const bool b){
																pfensterkontrolle=b;
};
bool _grafik::fensterkontrolle()const{
																return(pfensterkontrolle);
};
*/

void _grafik::aktivitaet(const bool b){
                                                                pactivity=b;
};
bool _grafik::aktivitaet() const{
                                                                return(pactivity);
};

void _grafik::groesse(unsigned int sx,unsigned int sy,unsigned int sz){
                                                                if(sx<1) sx=1;
                                                                if(sy<1) sy=1;
                                                                if(sz<1) sz=1;
                                                                psize.setzen(sx,sy,sz);
};
void _grafik::groesse(unsigned int sx,unsigned int sy){
                                                                if(sx<1) sx=1;
                                                                if(sy<1) sy=1;
                                                                psize.setzen(sx,sy,psize[2]);
};
void _grafik::rate(unsigned int r){
																prate=r;
};
void _grafik::vollbildmodus(bool f){
																pfullscreen=f;
};

_vektor3<unsigned int> _grafik::groesse() const{
                                                                return(psize);
};
void _grafik::position(_tg x,_tg y){
                                                                plowest.setzen(x,y,plowest[2]);
};
_tg _grafik::positionx() const{
                                                                return(plowest[0]);
};
_tg _grafik::positiony() const{
                                                                return(plowest[1]);
};

void _grafik::upperleft(){
                                                                porigin=1;
};
bool _grafik::upperleftis() const{
                                                                if(porigin==1) return(true);
                                                                return(false);
};
void _grafik::lowerleft(){
                                                                porigin=0;
};
bool _grafik::lowerleftis() const{
                                                                if(porigin==0) return(true);
                                                                return(false);
};
void _grafik::normale(bool b){
                                                                pnormal=b;
};
bool _grafik::normale() const{
                                                                return(pnormal);
};
void _grafik::normallowest(_tg x,_tg y,_tg z){
                                                                plowest.setzen(x,y,z);
};
void _grafik::normalhighest(_tg x,_tg y,_tg z){
                                                                if(x<=plowest[0]) x=plowest[0]+1;
                                                                if(y<=plowest[1]) y=plowest[1]+1;
                                                                if(z<=plowest[2]) z=plowest[2]+1;
                                                                phighest.setzen(x,y,z);
};
_tg _grafik::normallowestx() const{
                                                                return(plowest[0]);
};
_tg _grafik::normalhighestx() const{
                                                                return(phighest[0]);
};
_tg _grafik::normallowesty() const{
                                                                return(plowest[1]);
};
_tg _grafik::normalhighesty() const{
                                                                return(phighest[1]);
};
_tg _grafik::normallowestz() const{
                                                                return(plowest[2]);
};
_tg _grafik::normalhighestz() const{
                                                                return(phighest[2]);
};

void _grafik::matrixprojektion(_matrix44<_tm>*){
};
void _grafik::matrixwelt(_matrix44<_tm>*){
};
void _grafik::matrixmodell(_matrix44<_tm>*){
};
//*****************************************************************************************************************************************************************************************************+
//                                                              Z E I C H E N 
//*****************************************************************************************************************************************************************************************************+
_zeichen::_zeichen(_zeichensatz*zs,_bild<_tb>*src,unsigned int id,unsigned short x,unsigned short y,unsigned short w,unsigned short h,_tg dx,_tg drawoffsetx,_tg drawoffsety){
                                                                pzeichensatz=zs;
                                                                pid=id;
                                                                pdeltax=dx;
                                                                pdrawoffsetx=drawoffsetx;
                                                                pdrawoffsety=drawoffsety;
                                                                w++;
																h++;
                                                                if(w==0) w=1;
                                                                if(h==0) h=1;
                                                                pbild=new _bild<_tb>(w,h,4);
                                                                _tb*dest=pbild->daten();
                                                                _tb*sour=  src->daten();
                                                                unsigned int si=0;//(y*src->groesse(0)+x)*4;
                                                                unsigned int di=0;
                                                                unsigned int inv=src->groesse(0)-1;
                                                                for(int yy=0;yy<h;yy++){
                                                                 for(int xx=0;xx<w;xx++){
                                                                  if(src->ursprungunten()){
                                                                   si=((inv-(y+yy))*src->groesse(0)+(x+xx))*4;
                                                                  }else{
                                                                   si=((y+yy)*src->groesse(0)+(x+xx))*4;
                                                                  };
                                                                  di=(yy*w+xx)*4;
                                                                  dest[di+0]=sour[si+0];
                                                                  dest[di+1]=sour[si+1];
                                                                  dest[di+2]=sour[si+2];
                                                                  dest[di+3]=sour[si+3];
                                                                 };
                                                                };
};
_zeichen::~_zeichen(){
                                                                deletesecure(pbild);

};
_bild<_tb>*_zeichen::bild(){
                                                                return(pbild);
};
_tg _zeichen::breite()const{
                                                                return(pbild->groesse(0));
};
_tg _zeichen::hoehe()const{
                                                                return(pbild->groesse(1));
};

_tg _zeichen::versatzx()const{
                                                                return(pdrawoffsetx);
};
_tg _zeichen::versatzy()const{
                                                                return(pdrawoffsety);
};

unsigned int _zeichen::identifikation()const{
                                                                return(pid);
};
_tg _zeichen::deltax()const{
                                                                return(pdeltax);
};
_tg _zeichen::kernel(unsigned int previd)const{
                                                                _tg k=0;
                                                                _zeichenkernel*kit;
                                                                if(anfang(kit))do{
                                                                 if(kit->vorheriges()==previd) return(kit->deltax());
                                                                }while(naechstes(kit));
                                                                return(k);
};

//*****************************************************************************************************************************************************************************************************+
//                                                              Z E I C H E N K E R N E L 
//*****************************************************************************************************************************************************************************************************+
_zeichenkernel::_zeichenkernel(_zeichen*z,unsigned int previd,_tg dx):_listenknotenbasis<_zeichenkernel>(z){
                                                                pdx=dx;
                                                                pprevid=previd;
};
_zeichenkernel::~_zeichenkernel(){
};
unsigned int _zeichenkernel::vorheriges()const{
                                                                return(pprevid);
};
_tg _zeichenkernel::deltax()const{
                                                                return(pdx);
};

//*****************************************************************************************************************************************************************************************************+
//                                                              Z E I C H E N S A T Z K E R N E L 
//*****************************************************************************************************************************************************************************************************+
_zeichensatzkernel::_zeichensatzkernel(_zeichensatz*zs,unsigned int i0,unsigned int i1,signed short dx):_listenknotenbasis<_zeichensatzkernel>(zs->kernelliste()){
                                                                pzeichensatz=zs;
                                                                pi0=i0;
                                                                pi1=i1;
                                                                pdx=dx;
};
_zeichensatzkernel::~_zeichensatzkernel(){
};
unsigned int _zeichensatzkernel::erstes()const{
                                                                return(pi0);
};
unsigned int _zeichensatzkernel::zweites()const{
                                                                return(pi1);
};
_tg _zeichensatzkernel::deltax()const{
                                                                return(pdx);
};

//******************************************************************************************************************************************************************************************************
//                                                              Z E I C H E N S A T Z 
//******************************************************************************************************************************************************************************************************
_zeichensatz::_zeichensatz(_grafik*g):_listenknotenbasis<_zeichensatz>(g->listezeichensatz()){
                                                                pg=g;
                                                                pid=0;
                                                                pskalierung=1;
};
_zeichensatz::~_zeichensatz(){
};
_listebasis<_zeichensatzkernel>*_zeichensatz::kernelliste(){
                                                                return(&pkernelliste);
};
void _zeichensatz::skalierung(_tg s){
                                                                pskalierung=s;
};
void _zeichensatz::anwaehlen(){};
void _zeichensatz::abwaehlen(){};
void _zeichensatz::text(char*,int,int,char,char,char){};
void _zeichensatz::text(char*,int,int,char,char,char,char,char,char){};
void _zeichensatz::text(char*,int,int,_vektor<unsigned char>&){};
void _zeichensatz::text(char*,int,int,_vektor<unsigned char>&,_vektor<unsigned char>&){};
void _zeichensatz::schnellvorbereiten(){};
void _zeichensatz::textschnell(char*,int,int,int,_vektor<unsigned char>&,_vektor<unsigned char>&){};
int _zeichensatz::charbreite() const{return(0);};
int _zeichensatz::charhoehe() const{return(0);};
void _zeichensatz::breite(char*,int&,int&){};
unsigned int _zeichensatz::identifikation()const{
                                                                return(pid);
};
void _zeichensatz::identifikation(const unsigned int id){
                                                                pid=id;
};
//*****************************************************************************************************************************************************************************************************+
//                                                              Z E I C H E N S A T Z D I R E C T X 
//*****************************************************************************************************************************************************************************************************+
_zeichensatzbild::_zeichensatzbild(_grafik*g,const _zeichenkette<char> file):_zeichensatz(g){
                                                                pgrafik=g;
                                                                pfile=file;
                                                                psource=0;
                                                                pfontname=0;
                                                                ptexturname=0;
                                                                for(int i=0;i<16384;i++) pzeichen[i]=0;
                                                                psource=new _bild<_tb>(file+".tga");
                                                            //    psource->tiefereskalieren(1);
                                                                psource->datentausch(0,2);
                                                                FILE*f=fopen(file+".fnt","rb");
                                                                if(f){
                                                                 L->schreiben("Font laden : ");
                                                                 fread(pheader,sizeof(char),3,f);
                                                                 pheader[3]=0;
                                                                 L->schreiben("Font Header = ",pheader);
                                                                 fread(&pversion,sizeof(char),1,f);
                                                                 L->schreiben("Font Version = ",(int)pversion);
                                                                 char blocktype;
                                                                 int blocksize;
                                                                 blockreadheader(f,blocktype,blocksize);
                                                                 if(blocktype==1) blockread1(f,blocksize);
                                                                 blockreadheader(f,blocktype,blocksize);
                                                                 if(blocktype==2) blockread2(f,blocksize);
                                                                 blockreadheader(f,blocktype,blocksize);
                                                                 if(blocktype==3) blockread3(f,blocksize);
                                                                 blockreadheader(f,blocktype,blocksize);
                                                                 if(blocktype==4) blockread4(f,blocksize);
                                                                 blockreadheader(f,blocktype,blocksize);
                                                                 if(blocktype==5) blockread5(f,blocksize);
                                                                 _zeichensatzkernel*zskit;
                                                                 if(kernelliste()->anfang(zskit))do{
                                                                  if(pzeichen[zskit->zweites()]){
                                                                   new _zeichenkernel(pzeichen[zskit->zweites()],zskit->erstes(),(_tg)zskit->deltax());
                                                                  };
                                                                 }while(kernelliste()->naechstes(zskit));
                                                                 fclose(f);
                                                                };
                                                                
};
_zeichensatzbild::~_zeichensatzbild(){
                                                                deletesecure(psource);
                                                                deletesecure(pfontname);
                                                                deletesecure(ptexturname);
                                                                for(int i=0;i<16384;i++){
                                                                 deletesecure(pzeichen[i]);
                                                                };
};
_bild<_tb>* _zeichensatzbild::bild(){
                                                                return(psource);
};
bool _zeichensatzbild::blockreadheader(FILE*f,char&blocktype,int&blocksize){
                                                                 size_t i;
                                                                 i=fread(&blocktype,sizeof(char),1,f);
                                                                 if(i){
                                                                  L->schreiben("blocktype ======================= ",(int)blocktype);
                                                                  fread(&blocksize,sizeof(char),4,f);
                                                                  L->schreiben("blocksize = ",blocksize);
                                                                  return(true);
                                                                 }else{
                                                                  return(false);
                                                                 };
};
void _zeichensatzbild::blockread1(FILE*f,unsigned int size){
                                                                fread(&pgroesse,sizeof(unsigned short),1,f);
                                                                fread(&pstil,sizeof(char),1,f);
                                                                fread(&poemname,sizeof(char),1,f);
                                                                fread(&pstretchy,sizeof(unsigned short),1,f);
                                                                fread(&psupersamlinglevel,sizeof(char),1,f);
                                                                fread(&ppadup,sizeof(char),1,f);
                                                                fread(&ppadright,sizeof(char),1,f);
                                                                fread(&ppaddown,sizeof(char),1,f);
                                                                fread(&ppadleft,sizeof(char),1,f);
                                                                fread(&pspacingx,sizeof(char),1,f);
                                                                fread(&pspacingy,sizeof(char),1,f);
                                                                fread(&poutline,sizeof(char),1,f);
                                                                deletesecure(pfontname);
                                                                pfontname=new char[(size-14)];//dauphin
                                                                fread(pfontname,sizeof(char),(size-14),f);  
                                                                L->schreiben("Fontname = ",pfontname);
                                                                L->schreiben("Fontgroesse = ",(int)pgroesse);
};
void _zeichensatzbild::blockread2(FILE*f,unsigned int size){
                                                                fread(&plinedistance,sizeof(unsigned short),1,f);
                                                                fread(&pbase,sizeof(unsigned short),1,f);
                                                                fread(&ptexwidth,sizeof(unsigned short),1,f);
                                                                fread(&ptexheight,sizeof(unsigned short),1,f);
                                                                fread(&ptexanzahl,sizeof(unsigned short),1,f);
                                                                fread(&ppacked,sizeof(char),1,f);
                                                                fread(&pchannelalpha,sizeof(char),1,f);
                                                                fread(&pchannelred,sizeof(char),1,f);
                                                                fread(&pchannelgreen,sizeof(char),1,f);
                                                                fread(&pchannelblue,sizeof(char),1,f);
                                                                L->schreiben("Font Zeilen Abstand = ",(int)plinedistance); 
                                                                
};
void _zeichensatzbild::blockread3(FILE*f,unsigned int size){
                                                                ptexturname=new char[(size)];
                                                                fread(ptexturname,sizeof(char),(size),f); 
                                                                L->schreiben("Font Textur Name = ",ptexturname);
};
void _zeichensatzbild::blockread4(FILE*f,unsigned int size){
                                                                pzeichenanzahl=size/20;
                                                                L->schreiben("Font Anzahl Zeichen = ",(int)pzeichenanzahl);
                                                                for(unsigned int n=0;n<pzeichenanzahl;n++){
                                                                 unsigned int lid;
                                                                 unsigned short lx;
                                                                 unsigned short ly;
                                                                 unsigned short lw;
                                                                 unsigned short lh;
                                                                 signed short loffsetx;
                                                                 signed short loffsety;
                                                                 signed short ldeltax;
                                                                 char ltexture;
                                                                 char lchannel;
                                                                 fread(&lid,sizeof(unsigned int),1,f);
                                                                 fread(&lx,sizeof(unsigned short),1,f);
                                                                 fread(&ly,sizeof(unsigned short),1,f);
                                                                 fread(&lw,sizeof(unsigned short),1,f);
                                                                 fread(&lh,sizeof(unsigned short),1,f);
                                                                 fread(&loffsetx,sizeof(signed short),1,f);
                                                                 fread(&loffsety,sizeof(signed short),1,f);
                                                                 fread(&ldeltax,sizeof(signed short),1,f);
                                                                 fread(&ltexture,sizeof(char),1,f);
                                                                 fread(&lchannel,sizeof(char),1,f);
                                                                 
                                                                 pzeichen[lid]=new _zeichen(this,psource,lid,lx,ly,lw,lh,(_tg)ldeltax,(_tg)loffsetx,(_tg)loffsety);
                                                               //  L->schreiben("Font Zeichen Ident = ",(int)lid);
                                                               //  L->schreiben("Font Zeichen Ident x = ",(int)lx);
                                                               //  L->schreiben("Font Zeichen Ident y = ",(int)ly);
                                                               //  L->schreiben("Font Zeichen Ident w = ",(int)lw);
                                                               //  L->schreiben("Font Zeichen Ident h = ",(int)lh);
                                                                 
                                                                };
};
void _zeichensatzbild::blockread5(FILE*f,unsigned int size){
                                                                pkernelanzahl=size/10;
                                                             //   L->schreiben("Font Anzahl Kernel = ",(int)pkernelanzahl);
                                                                for(unsigned int n=0;n<pkernelanzahl;n++){
                                                                 unsigned int lkernel0;
                                                                 unsigned int lkernel1;
                                                                 signed short lkerneldx;
                                                                 fread(&lkernel0,sizeof(unsigned int),1,f);
                                                                 fread(&lkernel1,sizeof(unsigned int),1,f);
                                                                 fread(&lkerneldx,sizeof(signed short),1,f);
                                                                 new _zeichensatzkernel(this,lkernel0,lkernel1,lkerneldx);
                                                                };
};
_zeichen*_zeichensatzbild::zeichen(unsigned int i){
                                                                return(pzeichen[i]);
};
void _zeichensatzbild::text(const _zeichenkette<char>&t,_tg x,_tg y,const _vektor4<_to>&color){
                                                                unsigned int s=t.groesse();
                                                                unsigned int prev=0xffffffff;//1e+8;
                                                                _tg xit=x;
                                                                _tg yit=y;
                                                                for(unsigned int n=0;n<s;n++){
                                                                 unsigned int i=(unsigned int)t.daten()[n];
                                                                 _zeichen*z=pzeichen[i];
                                                                 if(z){
                                                                  pgrafik->rechteck(z->bild(),xit+z->versatzx()*skalierung(),yit+z->versatzy()*skalierung()/*-_tg(pbase)*/,z->breite()*skalierung(),z->hoehe()*skalierung(),color,false);
                                                                  xit+=z->deltax()*skalierung();
                                                                  if(prev!=0xffffffff){
                                                                   xit+=z->kernel(prev)*skalierung();
                                                                  };
                                                                  prev=pzeichen[i]->identifikation();
                                                                 };
                                                                };
};
void _zeichensatzbild::text(const _zeichenkette<wchar_t>&t,_tg x,_tg y,const _vektor4<_to>&color){
                                                                unsigned int s=t.groesse();
                                                                unsigned int prev=0xffffffff;
                                                                _tg xit=x;
                                                                _tg yit=y;
                                                                for(unsigned int n=0;n<s;n++){
                                                                 unsigned int i=(unsigned int)t.daten()[n];
                                                                 _zeichen*z=pzeichen[i];
                                                                 if(z){
                                                                  pgrafik->rechteck(z->bild(),xit+(z->versatzx()*skalierung()),yit+(z->versatzy()*skalierung())/*-_tg(pbase)*/,z->breite()*skalierung(),z->hoehe()*skalierung(),color,false);
                                                                  xit+=z->deltax()*skalierung();
                                                                  if(prev!=0xffffffff){
                                                                   xit+=z->kernel(prev)*skalierung();
                                                                  };
                                                                  prev=pzeichen[i]->identifikation();
                                                                 };
                                                                };
};
_tg _zeichensatzbild::breite(const _zeichenkette<_tt>&t){
                                                                unsigned int s=t.groesse();
                                                                unsigned int prev=0xffffffff;
                                                                _tg x=0;
                                                                for(unsigned int n=0;n<s;n++){
                                                                 unsigned int i=(unsigned int)t.daten()[n];
                                                                 if(pzeichen[i]){
                                                                  x+=pzeichen[i]->deltax()*skalierung();
                                                                  if(prev!=0xffffffff){
                                                                   x+=pzeichen[i]->kernel(prev)*skalierung();
                                                                  };
                                                                  prev=pzeichen[i]->identifikation();
                                                                 };
                                                                };
                                                                return(x);
};
_tg _zeichensatzbild::hoehe(const _zeichenkette<_tt>&){
                                                                return((_tg)pgroesse*skalierung());
};



void _zeichensatzbild::anwaehlen(){
};
void _zeichensatzbild::abwaehlen(){
};
void _zeichensatzbild::text(char*,int,int,char,char,char){
};
void _zeichensatzbild::text(char*,int,int,char,char,char,char,char,char){
};
void _zeichensatzbild::text(char*,int,int,_vektor<unsigned char>&){
};
void _zeichensatzbild::text(char*,int,int,_vektor<unsigned char>&,_vektor<unsigned char>&){
};
void _zeichensatzbild::schnellvorbereiten(){
};
void _zeichensatzbild::textschnell(char*,int,int,int,_vektor<unsigned char>&,_vektor<unsigned char>&){
};
int _zeichensatzbild::charbreite() const{
                                                                return(0);
};
int _zeichensatzbild::charhoehe() const{
                                                                return(0);
};
void _zeichensatzbild::breite(char*,int&,int&){
};