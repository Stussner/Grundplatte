//******************************************************************************************************************************************************************************************************
//  Project     : grundplatte
//  Library     : _grundplatte.lib
//  Module      : _feld.hpp
//  Date        : 19.11.2006
//  Description :  
//******************************************************************************************************************************************************************************************************
//*********************************************************************************************************************************************************************************
//                                                                V O R L A G E N D E K L A R A T I O N
//*********************************************************************************************************************************************************************************
template <class _tg>class _feld;

#ifndef _weltfeldh_included
#define _weltfeldh_included

#include <_global.hpp>
#include <_struktur.hpp>
#include <_vektor.hpp>
#include <_editionwin.hpp>
#include <_datei.hpp>
#include <_grafik.hpp>



//******************************************************************************************************************************************************************************************************
//                                                              F E L D 
//******************************************************************************************************************************************************************************************************
template <class _tg>
class _feld:
    public _basis::_speicherbarargument<_feld<_tg> >,
    public virtual _editierbar{
    public:
            _feld();
            virtual ~_feld();
            void loeschen();
            void verschieben(const _vektor3<_tg>&);
            void nichtspeichern(const bool);
            bool nichtspeichern()const;
            void aktiv(const bool);
            bool aktiv()const;
            void ort(const _vektor3<_tg>&v);
            _vektor3<_tg> ort()const;
            void homogen(const _vektor3<_tg>&v);
            _vektor3<_tg> homogen()const;
            
            void divergenz(const _vektor3<_tg>&ort,const _tg staerke);        
            void divergenzort(const unsigned int,const _vektor3<_tg>&);
            _vektor3<_tg> divergenzort(const unsigned int)const;
            void divergenzintensitaet(const unsigned int,const _tg);
            _tg divergenzintensitaet(const unsigned int);
            
            void rotation(const _vektor3<_tg>&ort,const _vektor3<_tg>&achsenrichtung,const _tg staerke);
            
            void blase(const _vektor3<_tg>&ort,const _tg radius,const _tg staerke);
            _tg  blaseradius(const unsigned int i)const;
            void blaseradius(const unsigned int i,const _tg r);
            


            void vektor(const _vektor3<_tg>&ort,_vektor3<_tg>&);
            void umgrenzungsquader(_tg&,_tg&,_tg&,_tg&,_tg&,_tg&);
            //speichern
            char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_feld>*);
            void speichern(_speicherbardynamisch<_feld>*);
            char assoziieren(_speicherbardynamisch<_feld>*);
			bool ladenfeld(_datei*d);
			void speichernfeld(_datei*d);
            //editieren
            
            void beineuedivergenz(_guiereignisdaten*);
            void beiloeschendivergenz(_guiereignisdaten*);
            void beineuerotation(_guiereignisdaten*);
            void beiloeschenrotation(_guiereignisdaten*);
            void beineueblase(_guiereignisdaten*);
            void beiloeschenblase(_guiereignisdaten*);
            virtual void einhaengendialog(_dynamischerdialog*);
            virtual void auslesendialog(_dynamischerdialog*);            
            //zeichnen
            _liste<_vektor3<_tg> >*divergenzort();
            _liste<_tg>*divergenzstaerke();
            _liste<_vektor3<_tg> >*rotationort();
            _liste<_vektor3<_tg> >*rotationachse();
            _liste<_tg>*rotationstaerke();
            _liste<_vektor3<_tg> >*blaseort();
            _liste<_tg>*blaseradius();
            _liste<_tg>*blasestaerke();
    private:
            bool paktiv;
            bool pnichtspeichern;
            //für homogenes feld
            _vektor3<_tg> phomogen;
            //für divergenz
            _liste<_vektor3<_tg> > ortdivergenz;
            _liste<_tg> staerkedivergenz;
            //für rotationsquellen 
            _liste<_vektor3<_tg> > achsenvektorrotation;
            _liste<_vektor3<_tg> > ortrotation;
            _liste<_tg > staerkerotation; 
            //für blasen
            _liste<_vektor3<_tg> > ortblase;
            _liste<_tg> staerkeblase;
            _liste<_tg> radiusblase;
            //edition
            _dynamischerdialog*dialog;
            _vektor3<_tg> port;
};         

template <class _tg>
_feld<_tg>::_feld(){
                                dialog=0;
                                pnichtspeichern=false;
                                paktiv=true;
                                port.setzen(-2,0,0);
};
template <class _tg>
_feld<_tg>::~_feld(){
                                loeschen();
};
template<class _tg>
void _feld<_tg>::loeschen(){
                                ortdivergenz.loeschen();                    
                                staerkedivergenz.loeschen();
                                achsenvektorrotation.loeschen();
                                ortrotation.loeschen();
                                staerkerotation.loeschen();
};
template<class _tg>
void _feld<_tg>::nichtspeichern(const bool b){
                                pnichtspeichern=b;
};
template<class _tg>
bool _feld<_tg>::nichtspeichern()const{
                                return(pnichtspeichern);
};
template<class _tg>
void _feld<_tg>::aktiv(const bool b){
                                paktiv=b;
};
template<class _tg>
bool _feld<_tg>::aktiv()const{
                                return(paktiv);
};
template<class _tg>
void _feld<_tg>::verschieben(const _vektor3<_tg>&v){
                                _listenknoten<_vektor3<_tg> >*oit;
                                //------------------
                                port+=v;
                                if(ortdivergenz.anfang(oit))do{
                                 (*oit->objekt())+=v;
                                }while(ortdivergenz.naechstes(oit));
                                if(ortrotation.anfang(oit))do{
                                 (*oit->objekt())+=v;
                                }while(ortrotation.naechstes(oit));
};
template<class _tg>
void _feld<_tg>::ort(const _vektor3<_tg>&v){
                                port=v;
};
template<class _tg>
_vektor3<_tg> _feld<_tg>::ort()const{
                                return(port);
};
template<class _tg>
void _feld<_tg>::homogen(const _vektor3<_tg>&v){
                                phomogen=v;
};
template<class _tg>
_vektor3<_tg> _feld<_tg>::homogen()const{
                                return(phomogen);
};
template <class _tg>
void _feld<_tg>::divergenz(const _vektor3<_tg>&ort,const _tg staerke){//legt neue divergenz an
                                ortdivergenz.einhaengen(new _vektor3<_tg>(ort));
                                _tg*t=new _tg;
                                *t=staerke;
                                staerkedivergenz.einhaengen(t);
};
template <class _tg>
void _feld<_tg>::divergenzort(const unsigned int i,const _vektor3<_tg>&v){
                                _listenknoten<_vektor3<_tg> >*oit;
                                if(ortdivergenz.anfang(oit)){
                                 for(unsigned int n=0;n<i;n++) ortdivergenz.naechstes(oit);
                                 oit->objekt()->setzen(v);
                                };
};
template <class _tg>
_vektor3<_tg> _feld<_tg>::divergenzort(const unsigned int i)const{
                                _listenknoten<_vektor3<_tg> >*oit;
                                if(ortdivergenz.anfang(oit)){
                                 for(unsigned int n=0;n<i;n++) ortdivergenz.naechstes(oit);
                                 return(*oit->objekt());
                                }else return(_vektor3<_tg>(0,0,0));
};
template <class _tg>
void _feld<_tg>::divergenzintensitaet(const unsigned int i,const _tg v){
                                _listenknoten<_tg >*oit;
                                if(staerkedivergenz.anfang(oit)){
                                 for(unsigned int n=0;n<i;n++) staerkedivergenz.naechstes(oit);
                                 (*oit->objekt())=v;
                                };
};
template <class _tg>
_tg _feld<_tg>::divergenzintensitaet(const unsigned int i){
                                _listenknoten<_tg>*oit;
                                if(staerkedivergenz.anfang(oit)){
                                 for(unsigned int n=0;n<i;n++) staerkedivergenz.naechstes(oit);
                                 return(*oit->objekt());
                                }else return(0);
};

template <class _tg>
void _feld<_tg>::rotation(const _vektor3<_tg>&ort,const _vektor3<_tg>&achsenrichtung,const _tg staerke){
                               achsenvektorrotation.einhaengen(new _vektor3<_tg>(achsenrichtung));
                               ortrotation.einhaengen(new _vektor3<_tg>(ort));
                               _tg*t=new _tg;
                               *t=staerke;
                               staerkerotation.einhaengen(t);
};

template <class _tg>
void _feld<_tg>::blase(const _vektor3<_tg>&ort,const _tg radius,const _tg staerke){
                               ortblase.einhaengen(new _vektor3<_tg>(ort));
                               _tg*t=new _tg;
                               *t=staerke;
                               staerkeblase.einhaengen(t);
                               t=new _tg;
                               *t=radius;
                               radiusblase.einhaengen(t);
};
template <class _tg>
_tg _feld<_tg>::blaseradius(const unsigned int i)const{
                                _listenknoten<_tg>*rit;
                                if(radiusblase.anfang(rit)){
                                 for(unsigned int u=0;u<i;u++) radiusblase.naechstes(rit);
                                 return(*rit->objekt());
                                };
                                return(0);
};

template <class _tg>
void _feld<_tg>::blaseradius(const unsigned int i,const _tg r){
                                _listenknoten<_tg>*rit;
                                if(radiusblase.anfang(rit)){
                                 for(unsigned int u=0;u<i;u++) radiusblase.naechstes(rit);
                                 *rit->objekt()=r;
                                };
};


template <class _tg>
void _feld<_tg>::vektor(const _vektor3<_tg>&ort,_vektor3<_tg>&e){
                                if(paktiv==false){
                                 e.setzen(0,0,0);
                                 return;
                                };
                                //für homogenität
                                e=phomogen;
                                //für divergenz 
                                _listenknoten<_vektor3<_tg> >*oit;
                                _listenknoten<_tg>           *sit;
                                _listenknoten<_tg>           *rit;
                                if(ortdivergenz.anfang(oit)){
                                 staerkedivergenz.anfang(sit);
                                 do{
                                  _vektor3<_tg> h= *oit->objekt() - ort;
                                  _tg l=h.laenge();
                                  h.normalisieren();
                                  _tg s=*sit->objekt()/(1+l)/(1+l);
                                  h*=s;
                                  e+=h;
                                  staerkedivergenz.naechstes(sit);
                                 }while(ortdivergenz.naechstes(oit));
                                };
                                //für rotation
                                _vektoranalysis3<_tg> V3;
                                _vektor3<_tg> lot;
                                _tg para;
                                _listenknoten<_vektor3<_tg> >*arit;
                                _listenknoten<_vektor3<_tg> >*orit;
                                _listenknoten<_tg>           *srit;
                                if(ortrotation.anfang(orit)){
                                 achsenvektorrotation.anfang(arit);
                                 staerkerotation.anfang(srit);
                                 do{
                                  V3.lotpunktgerade(ort,*orit->objekt(),*arit->objekt(),lot,para);
                                  if((para>=0)&&(para<=1)){
                                   _vektor3 <_tg> kreuz=lot%*arit->objekt();
                                   _tg l=lot.laenge();
                                   kreuz.normalisieren();
                                   _tg s=*srit->objekt()/(1+l)/(1+l);
                                   kreuz*=s;
                                   e+=kreuz;
                                  }else{
                                   //para ist ausserhalb des liniensegments
                                   _vektor3<_tg> d; 
                                   if(para<0){
                                    d=ort-*orit->objekt();
                                   }else{
                                    d=ort-(*orit->objekt()+*arit->objekt());
                                   };
                                   _tg dl=d.laenge();
                                   _vektor3<_tg> kreuzR=(*arit->objekt()%d);
                                   kreuzR.normalisieren();
                                   _tg s=*srit->objekt()/(1+dl)/(1+dl);
                                   kreuzR*=s;
                                   e+=kreuzR;
                                   
                                  };
                                  staerkerotation.naechstes(srit);
                                  achsenvektorrotation.naechstes(arit);
                                 }while(ortrotation.naechstes(orit));
                                };
                                //für blasen
                                _tg rad;
                                if(ortblase.anfang(oit)){
                                 staerkeblase.anfang(sit);
                                 radiusblase.anfang(rit);
                                 do{
                                  rad=*rit->objekt();
                                  
                                  _vektor3<_tg> h= *oit->objekt() - ort;
                                  _tg b=h.laenge();
                                  _tg r=fabs(rad-h.laenge());
                                  h.normalisieren();
                                  _tg s=(*sit->objekt())/(1+b);///(1+b);
                                  s*=1.0f/pow(1+r,3);
                                  h*=s;
                                  e+=h;
                                  
                                  staerkeblase.naechstes(sit);
                                  radiusblase.naechstes(rit);
                                 }while(ortblase.naechstes(oit));
                                };
                                
                               // return(e);
};
template<class _tg>
void _feld<_tg>::umgrenzungsquader(_tg&x0,_tg&x1,_tg&y0,_tg&y1,_tg&z0,_tg&z1){
                                _listenknoten<_vektor3<_tg> >*arit;
                                _listenknoten<_vektor3<_tg> >*orit;
                                _listenknoten<_tg>*rrit;
                                _tg x,y,z,r;
                                //--------------------------------
                                /*ortdivergenz.anfang(orit);
                                ortrotation.anfang(arit);
                                if((orit)||(arit)){
                                 if(orit){
                                  x0=x1=(*orit->objekt())[0];
                                  y0=y1=(*orit->objekt())[1];
                                  z0=z1=(*orit->objekt())[2];
                                 };
                                 if(arit){
                                  x0=x1=(*arit->objekt())[0];
                                  y0=y1=(*arit->objekt())[1];
                                  z0=z1=(*arit->objekt())[2];
                                 };
                                 */
                                 x0=x1=port[0];
                                 y0=y1=port[1];
                                 z0=z1=port[2];
                                 
                                 if(ortdivergenz.anfang(orit))do{
                                  x=(*orit->objekt())[0];
                                  y=(*orit->objekt())[1];
                                  z=(*orit->objekt())[2];
                                  if(x>x1) x1=x;
                                  if(x<x0) x0=x;
                                  if(y>y1) y1=y;
                                  if(y<y0) y0=y;
                                  if(z>z1) z1=z;
                                  if(z<z0) z0=z;
                                 }while(ortdivergenz.naechstes(orit));
                                 
                                 achsenvektorrotation.anfang(arit);
                                 if(ortrotation.anfang(orit))do{
                                  x=(*orit->objekt())[0];
                                  y=(*orit->objekt())[1];
                                  z=(*orit->objekt())[2];
                                  if(x>x1) x1=x;
                                  if(x<x0) x0=x;
                                  if(y>y1) y1=y;
                                  if(y<y0) y0=y;
                                  if(z>z1) z1=z;
                                  if(z<z0) z0=z;
                                  x+=(*arit->objekt())[0];
                                  y+=(*arit->objekt())[1];
                                  z+=(*arit->objekt())[2];
                                  if(x>x1) x1=x;
                                  if(x<x0) x0=x;
                                  if(y>y1) y1=y;
                                  if(y<y0) y0=y;
                                  if(z>z1) z1=z;
                                  if(z<z0) z0=z;
                                  achsenvektorrotation.naechstes(arit);
                                 }while(ortrotation.naechstes(orit));

                                 radiusblase.anfang(rrit);
                                 if(ortblase.anfang(orit))do{
                                  r=*rrit->objekt();
                                  x=(*orit->objekt())[0];
                                  y=(*orit->objekt())[1];
                                  z=(*orit->objekt())[2];
                                  if((x+r)>x1) x1=x+r;
                                  if((x-r)<x0) x0=x-r;
                                  if((y+r)>y1) y1=y+r;
                                  if((y-r)<y0) y0=y-r;
                                  if((z+r)>z1) z1=z+r;
                                  if((z-r)<z0) z0=z-r;
                                  radiusblase.naechstes(rrit);
                                 }while(ortblase.naechstes(orit));


                                /*}else{
                                 x0=-10;
                                 y0=-10;
                                 z0=-10;
                                 x1=10;
                                 y1=10;
                                 z1=10;
                                };*/
                          
                                
};

template<class _tg>
char _feld<_tg>::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_feld>*sd){
                                char r=1;
                                unsigned int i,n;
                                _vektor3<_tg> o;
                                _vektor3<_tg> a;
                                _tg s,rad;
                                //------------------------------
                                loeschen();
                                r^=sd->ladenbeginn(fn);
                                r^=sd->ladenverschachtelung(fn);
                                r^=sd->ladenwert(paktiv);
                                r^=sd->ladenwert(port);
                                r^=sd->ladenwert(phomogen);
                                //------------------------------
                                r^=sd->ladenwert(i);
                                for(n=0;n<i;n++){
                                 r^=sd->ladenwert(o);
                                 r^=sd->ladenwert(s);
                                 divergenz(o,s);
                                };
                                //------------------------------
                                r^=sd->ladenwert(i);
                                for(n=0;n<i;n++){
                                 r^=sd->ladenwert(o);
                                 r^=sd->ladenwert(a);
                                 r^=sd->ladenwert(s);
                                 rotation(o,a,s);
                                };
                                //------------------------------
                                r^=sd->ladenwert(i);
                                for(n=0;n<i;n++){
                                 r^=sd->ladenwert(o);
                                 r^=sd->ladenwert(rad);
                                 r^=sd->ladenwert(s);
                                 blase(o,rad,s);
                                };


                                sd->ladenende();
                                return(r);
};
template<class _tg>
void _feld<_tg>::speichern(_speicherbardynamisch<_feld>*sd){
                                unsigned int i,n;
                                _listenknoten<_vektor3<_tg> >*oit;
                                _listenknoten<_vektor3<_tg> >*ait;
                                _listenknoten<_tg>*sit;
                                _listenknoten<_tg>*rit;
                                sd->speichernbeginnblock();
                                sd->speichernverschachtelung();
                                sd->speichernwert(paktiv);
                                sd->speichernwert(port);
                                sd->speichernwert(phomogen);
                                //---------------------------------
                                i=ortdivergenz.anzahl();
                                sd->speichernwert(i); 
                                ortdivergenz.anfang(oit);
                                staerkedivergenz.anfang(sit);
                                for(n=0;n<i;n++){
                                 sd->speichernwert(*oit->objekt());
                                 sd->speichernwert(*sit->objekt());
                                 oit=oit->naechstes();
                                 sit=sit->naechstes();
                                };
                                //---------------------------------
                                i=ortrotation.anzahl();
                                sd->speichernwert(i); 
                                ortrotation.anfang(oit);
                                achsenvektorrotation.anfang(ait);
                                staerkerotation.anfang(sit);
                                for(n=0;n<i;n++){
                                 sd->speichernwert(*oit->objekt());
                                 sd->speichernwert(*ait->objekt());
                                 sd->speichernwert(*sit->objekt());
                                 oit=oit->naechstes();
                                 ait=ait->naechstes();
                                 sit=sit->naechstes();
                                };
                                //---------------------------------
                                i=ortblase.anzahl();
                                sd->speichernwert(i); 
                                ortblase.anfang(oit);
                                radiusblase.anfang(rit);
                                staerkeblase.anfang(sit);
                                for(n=0;n<i;n++){
                                 sd->speichernwert(*oit->objekt());
                                 sd->speichernwert(*rit->objekt());
                                 sd->speichernwert(*sit->objekt());
                                 oit=oit->naechstes();
                                 rit=rit->naechstes();
                                 sit=sit->naechstes();
                                };
                                sd->speichernendeblock();
                                
};
template<class _tg>
char _feld<_tg>::assoziieren(_speicherbardynamisch<_feld>*sd){
                                sd->assoziierenverschachtelung();
                                return(1);
};
template<class _tg>
bool _feld<_tg>::ladenfeld(_datei*d){
	                             unsigned int i,n;
                                _vektor3<_tg> o;
                                _vektor3<_tg> a;
                                _tg s,rad;
                                //------------------------------
                                loeschen();
                                d->laden(paktiv);
                                d->laden(port);
                                d->laden(phomogen);
                                //------------------------------
                                d->laden(i);
                                for(n=0;n<i;n++){
                                 d->laden(o);
                                 d->laden(s);
                                 divergenz(o,s);
                                };
                                //------------------------------
                                d->laden(i);
                                for(n=0;n<i;n++){
                                 d->laden(o);
                                 d->laden(a);
                                 d->laden(s);
                                 rotation(o,a,s);
                                };
                                //------------------------------
                                d->laden(i);
                                for(n=0;n<i;n++){
                                 d->laden(o);
                                 d->laden(rad);
                                 d->laden(s);
                                 blase(o,rad,s);
                                };
								return(true);
};
template<class _tg>
void _feld<_tg>::speichernfeld(_datei*d){
                                unsigned int i,n;
                                _listenknoten<_vektor3<_tg> >*oit;
                                _listenknoten<_vektor3<_tg> >*ait;
                                _listenknoten<_tg>*sit;
                                _listenknoten<_tg>*rit;
                                d->speichern(paktiv);
                                d->speichern(port);
                                d->speichern(phomogen);
                                //---------------------------------
                                i=ortdivergenz.anzahl();
                                d->speichern(i); 
                                ortdivergenz.anfang(oit);
                                staerkedivergenz.anfang(sit);
                                for(n=0;n<i;n++){
                                 d->speichern(*oit->objekt());
                                 d->speichern(*sit->objekt());
                                 oit=oit->naechstes();
                                 sit=sit->naechstes();
                                };
                                //---------------------------------
                                i=ortrotation.anzahl();
                                d->speichern(i); 
                                ortrotation.anfang(oit);
                                achsenvektorrotation.anfang(ait);
                                staerkerotation.anfang(sit);
                                for(n=0;n<i;n++){
                                 d->speichern(*oit->objekt());
                                 d->speichern(*ait->objekt());
                                 d->speichern(*sit->objekt());
                                 oit=oit->naechstes();
                                 ait=ait->naechstes();
                                 sit=sit->naechstes();
                                };
                                //---------------------------------
                                i=ortblase.anzahl();
                                d->speichern(i); 
                                ortblase.anfang(oit);
                                radiusblase.anfang(rit);
                                staerkeblase.anfang(sit);
                                for(n=0;n<i;n++){
                                 d->speichern(*oit->objekt());
                                 d->speichern(*rit->objekt());
                                 d->speichern(*sit->objekt());
                                 oit=oit->naechstes();
                                 rit=rit->naechstes();
                                 sit=sit->naechstes();
                                };
                               
};

template<class _tg>
void _feld<_tg>::beineuedivergenz(_guiereignisdaten*){
                                divergenz(_vektor3<_tg>(2,2,2),0.01);
                                if(dialog){
                                 _zeichenkette<char> h;
                                 char buf[1280];
                                 unsigned int i=ortdivergenz.anzahl()-1;        
								 _itoa_s(i,buf,10);
                                 h="Ort der Divergenz ";h+=buf;                           
                                 dialog->einhaengen(L"Feld",ANSIToUnicode(h.daten()),_vektor3<_tg>(2,2,2));
                                 h="Stärke der Divergenz ";h+=buf;   
                                 dialog->einhaengen(L"Feld",ANSIToUnicode(h.daten()),(_tg)0.01f);    
                                 dialog->zeigen();                            
                                };
};
template<class _tg>
void _feld<_tg>::beiloeschendivergenz(_guiereignisdaten*){
                                //letzte gruppe löschen
                                _listenknoten<_vektor3<_tg> >*orit;
                                _listenknoten<_tg >*stit;
                                if(ortdivergenz.anfang(orit)){
                                 orit=orit->vorheriges();
                                 orit->loeschmarkierungobjekt(true);
                                 delete orit;
                                };
                                if(staerkedivergenz.anfang(stit)){
                                 stit=stit->vorheriges();
                                 stit->loeschmarkierungobjekt(true);
                                 delete stit;
                                };
};
template<class _tg>
void _feld<_tg>::beineuerotation(_guiereignisdaten*){
                                rotation(_vektor3<_tg>(2,2,4),_vektor3<_tg>(2,0,0),0.01);
                                if(dialog){
                                 _zeichenkette<char> h;
                                 char buf[1280];
                                 unsigned int i=ortrotation.anzahl()-1;        
                                 _itoa_s(i,buf,10);
                                 h="Ort der Rotation ";h+=buf;                           
                                 dialog->einhaengen(L"Feld",ANSIToUnicode(h.daten()),_vektor3<_tg>(2,2,4));
                                 h="Achse der Rotation ";h+=buf;                           
                                 dialog->einhaengen(L"Feld",ANSIToUnicode(h.daten()),_vektor3<_tg>(2,0,0));
                                 h="Stärke der Rotation ";h+=buf;   
                                 dialog->einhaengen(L"Feld",ANSIToUnicode(h.daten()),(_tg)0.01f);    
                                 dialog->zeigen();                            
                                };
};
template<class _tg>
void _feld<_tg>::beiloeschenrotation(_guiereignisdaten*){
                                //letzte gruppe löschen
                                _listenknoten<_vektor3<_tg> >*orit;
                                _listenknoten<_vektor3<_tg> >*acit;
                                _listenknoten<_tg >*stit;
                                if(ortrotation.anfang(orit)){
                                 orit=orit->vorheriges();
                                 orit->loeschmarkierungobjekt(true);
                                 delete orit;
                                };
                                if(achsenvektorrotation.anfang(acit)){
                                 acit=acit->vorheriges();
                                 acit->loeschmarkierungobjekt(true);
                                 delete acit;
                                };
                                if(staerkerotation.anfang(stit)){
                                 stit=stit->vorheriges();
                                 stit->loeschmarkierungobjekt(true);
                                 delete stit;
                                };

};
template<class _tg>
void _feld<_tg>::beineueblase(_guiereignisdaten*){
                                blase(_vektor3<_tg>(2,2,2),5,0.01);
                                if(dialog){
                                 _zeichenkette<char> h;
                                 char buf[1280];
                                 unsigned int i=ortblase.anzahl()-1;        
                                 _itoa_s(i,buf,10);
                                 h="Ort der Blase ";h+=buf;                           
                                 dialog->einhaengen(L"Feld",ANSIToUnicode(h.daten()),_vektor3<_tg>(2,2,2));
                                 h="Radius der Blase ";h+=buf;   
                                 dialog->einhaengen(L"Feld",ANSIToUnicode(h.daten()),(_tg)5.0f);    
                                 h="Stärke der Blase ";h+=buf;   
                                 dialog->einhaengen(L"Feld",ANSIToUnicode(h.daten()),(_tg)0.01f);    
                                 dialog->zeigen();                            
                                };
};
template<class _tg>
void _feld<_tg>::beiloeschenblase(_guiereignisdaten*){
                                //letzte gruppe löschen
                                _listenknoten<_vektor3<_tg> >*orit;
                                _listenknoten<_tg >*stit;
                                if(ortblase.anfang(orit)){
                                 orit=orit->vorheriges();
                                 orit->loeschmarkierungobjekt(true);
                                 delete orit;
                                };
                                if(radiusblase.anfang(stit)){
                                 stit=stit->vorheriges();
                                 stit->loeschmarkierungobjekt(true);
                                 delete stit;
                                };
                                if(staerkeblase.anfang(stit)){
                                 stit=stit->vorheriges();
                                 stit->loeschmarkierungobjekt(true);
                                 delete stit;
                                };
};



template<class _tg>
void _feld<_tg>::einhaengendialog(_dynamischerdialog*d){
                                dialog=d;
                                d->editierbar(this);
                                d->loeschensektion(); 
                                d->addierensektion(L"Feld");
                                d->sektion(L"Feld")->offen(true);
                                d->einhaengenknopf<_feld<_tg> >(L"Feld",L"Neue Divergenz",L"erzeugen",this,&_feld<_tg>::beineuedivergenz);
                                d->einhaengenknopf<_feld<_tg> >(L"Feld",L"Letzte Divergenz",L"löschen",this,&_feld<_tg>::beiloeschendivergenz);
                                d->einhaengenknopf<_feld<_tg> >(L"Feld",L"Neue Rotation",L"erzeugen",this,&_feld<_tg>::beineuerotation);
                                d->einhaengenknopf<_feld<_tg> >(L"Feld",L"Letzte Rotation",L"löschen",this,&_feld<_tg>::beiloeschenrotation);
                                d->einhaengenknopf<_feld<_tg> >(L"Feld",L"Neue Blase",L"erzeugen",this,&_feld<_tg>::beineueblase);
                                d->einhaengenknopf<_feld<_tg> >(L"Feld",L"Letzte Blase",L"löschen",this,&_feld<_tg>::beiloeschenblase);
                                d->einhaengen(L"Feld",L"Homogener Vektor",phomogen);
                                //---------------------------------------------------------------
                                _listenknoten<_tg>*stit;                               
                                _listenknoten<_tg>*rtit;
                                _listenknoten<_vektor3<_tg> >*veit;
                                _zeichenkette<char> h;
                                char buf[1280];
                                unsigned int i=0;        
                                staerkedivergenz.anfang(stit);
                                if(ortdivergenz.anfang(veit))do{
                                 _itoa_s(i++,buf,10);
                                 h="Ort der Divergenz ";h+=buf;                                      
                                 d->einhaengen(L"Feld",ANSIToUnicode(h.daten()),*veit->objekt());
                                 h="Stärke der Divergenz ";h+=buf;   
                                 d->einhaengen(L"Feld",ANSIToUnicode(h.daten()),*stit->objekt());
                                 staerkedivergenz.naechstes(stit);
                                }while(ortdivergenz.naechstes(veit));
                                //---------------------------------------------------------------
                                _listenknoten<_vektor3<_tg> >*acit;
                                _listenknoten<_vektor3<_tg> >*orit;
                                i=0;
                                staerkerotation.anfang(stit);
                                achsenvektorrotation.anfang(acit);
                                if(ortrotation.anfang(orit))do{
                                 _itoa_s(i++,buf,10);
                                 h="Ort der Rotation ";h+=buf;
                                 d->einhaengen(L"Feld",ANSIToUnicode(h.daten()),*orit->objekt());
                                 h="Achse der Rotation ";h+=buf;
                                 d->einhaengen(L"Feld",ANSIToUnicode(h.daten()),*acit->objekt());
                                 h="Stärke der Rotation ";h+=buf;
                                 d->einhaengen(L"Feld",ANSIToUnicode(h.daten()),*stit->objekt());
                                 staerkerotation.naechstes(stit);
                                 achsenvektorrotation.naechstes(acit);
                                }while(ortrotation.naechstes(orit));
                                //---------------------------------------------------------------
                                radiusblase.anfang(rtit);
                                staerkeblase.anfang(stit);
                                if(ortblase.anfang(veit))do{
                                 _itoa_s(i++,buf,10);
                                 h="Ort der Blase ";h+=buf;                                      
                                 d->einhaengen(L"Feld",ANSIToUnicode(h.daten()),*veit->objekt());
                                 h="Radius der Blase ";h+=buf;   
                                 d->einhaengen(L"Feld",ANSIToUnicode(h.daten()),*rtit->objekt());
                                 h="Stärke der Blase ";h+=buf;   
                                 d->einhaengen(L"Feld",ANSIToUnicode(h.daten()),*stit->objekt());
                                 staerkeblase.naechstes(stit);
                                 radiusblase.naechstes(rtit);                                 
                                }while(ortblase.naechstes(veit));
                                d->einhaengen(L"Feld",L"Nicht speichern",pnichtspeichern);

};
template<class _tg>
void _feld<_tg>::auslesendialog(_dynamischerdialog*d){
                                _listenknoten<_tg>*stit;
                                _listenknoten<_tg>*rtit;
                                _listenknoten<_vektor3<_tg> >*veit;
                                _listenknoten<_vektor3<_tg> >*acit;
                                _listenknoten<_vektor3<_tg> >*orit;
                                _zeichenkette<char> h;
                                char buf[1280];
                                unsigned int i=0;        
                                d->auslesen(L"Feld",L"Homogener Vektor",phomogen);
                                //---------------------------------------------------------------
                                i=0;
                                staerkedivergenz.anfang(stit);
                                if(ortdivergenz.anfang(veit))do{
                                 _itoa_s(i++,buf,10);
                                 h="Ort der Divergenz ";h+=buf;
                                 d->auslesen(L"Feld",ANSIToUnicode(h.daten()),*veit->objekt());
                                 h="Stärke der Divergenz ";h+=buf;
                                 d->auslesen(L"Feld",ANSIToUnicode(h.daten()),*stit->objekt());
                                 staerkedivergenz.naechstes(stit);
                                }while(ortdivergenz.naechstes(veit));
                                //---------------------------------------------------------------
                                i=0;
                                staerkerotation.anfang(stit);
                                achsenvektorrotation.anfang(acit);
                                if(ortrotation.anfang(orit))do{
                                 _itoa_s(i++,buf,10);
                                 h="Ort der Rotation ";h+=buf;
                                 d->auslesen(L"Feld",ANSIToUnicode(h.daten()),*orit->objekt());
                                 h="Achse der Rotation ";h+=buf;
                                 d->auslesen(L"Feld",ANSIToUnicode(h.daten()),*acit->objekt());
                                 h="Stärke der Rotation ";h+=buf;
                                 d->auslesen(L"Feld",ANSIToUnicode(h.daten()),*stit->objekt());
                                 staerkerotation.naechstes(stit);
                                 achsenvektorrotation.naechstes(acit);
                                }while(ortrotation.naechstes(orit));
                                //---------------------------------------------------------------
                                i=0;
                                staerkeblase.anfang(stit);
                                radiusblase.anfang(rtit);
                                if(ortblase.anfang(veit))do{
                                 _itoa_s(i++,buf,10);
                                 h="Ort der Blase ";h+=buf;
                                 d->auslesen(L"Feld",ANSIToUnicode(h.daten()),*veit->objekt());
                                 h="Radius der Blase ";h+=buf;
                                 d->auslesen(L"Feld",ANSIToUnicode(h.daten()),*rtit->objekt());
                                 h="Stärke der Blase ";h+=buf;
                                 d->auslesen(L"Feld",ANSIToUnicode(h.daten()),*stit->objekt());
                                 staerkeblase.naechstes(stit);
                                 radiusblase.naechstes(rtit);
                                }while(ortblase.naechstes(veit));
                                d->auslesen(L"Feld",L"Nicht speichern",pnichtspeichern);

};
template<class _tg>
_liste<_vektor3<_tg> >*_feld<_tg>::divergenzort(){
                                return(&ortdivergenz);
};
template<class _tg>
_liste<_tg>*_feld<_tg>::divergenzstaerke(){
                                return(&staerkedivergenz);
};
template<class _tg>
_liste<_vektor3<_tg> >*_feld<_tg>::rotationort(){
                                return(&ortrotation);
};
template<class _tg>
_liste<_vektor3<_tg> >*_feld<_tg>::rotationachse(){
                                return(&achsenvektorrotation);
};
template<class _tg>
_liste<_tg>*_feld<_tg>::rotationstaerke(){
                                return(&staerkerotation);
};
template<class _tg>
_liste<_vektor3<_tg> >*_feld<_tg>::blaseort(){
                                return(&ortblase);
};
template<class _tg>
_liste<_tg>*_feld<_tg>::blaseradius(){
                                return(&radiusblase);
};
template<class _tg>
_liste<_tg>*_feld<_tg>::blasestaerke(){
                                return(&staerkeblase);
};

#endif