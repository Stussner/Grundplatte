//******************************************************************************************************************************************************************************************************
//  Project     : grundplatte
//  Library     : _grundplatte.lib
//  Module      : _funktion.hpp
//  Date        : 1.1.2003
//  Description : 
//******************************************************************************************************************************************************************************************************
#ifndef _funktionh_included
#define _funktionh_included
#include <_global.hpp>
#include <_vektor.hpp>
#include <_struktur.hpp>
//******************************************************************************************************************************************************************************************************
//                                                              F O R W A R D   D E C L A R A T I O N 
//******************************************************************************************************************************************************************************************************
template<class _tg=typgeometrie> class _funktion;
template<class _tg=typgeometrie> class _funktionsinus;
template<class _tg=typgeometrie> class _operation;
template<class _tg=typgeometrie> class _operationmultiplication;
template<class _tg=typgeometrie> class _fraktal;
template<class _tg=typgeometrie> class _kurvehermite1;
template<class _tg=typgeometrie> class _kurvehermite2;
template<class _tg=typgeometrie> class _kurvehermite3;
template<class _tg=typgeometrie> class _kurvehermite4;
template<class _tg=typgeometrie> class _flaechehermite;
template<class _tg=typgeometrie> class _zufallsgenerator;
//******************************************************************************************************************************************************************************************************
//                                                              B E G R E N Z E N 
//******************************************************************************************************************************************************************************************************
template<class _tg> inline _tg begrenzen(_tg x,_tg g0,_tg g1){
                                                                if(x<g0) return(g0); 
                                                                if(x>g1) return(g1);
                                                                return(x);
};
template <class _tg> inline _tg minimum(_tg a,_tg b){
                                                                return(a<b?a:b);
};
template <class _tg> inline _tg minimum(_tg a,_tg b,_tg c,_tg d){
																_tg m=a;
																if(m>b) m=b;
																if(m>c) m=c;
																if(m>d) m=d;
																return(m);
};
template <class _tg> inline _tg maximum(_tg a,_tg b){
                                                                return(a>b?a:b);
};
template <class _tg> inline _tg maximum(_tg a,_tg b,_tg c,_tg d){
																_tg m=a;
																if(m<b) m=b;
																if(m<c) m=c;
																if(m<d) m=d;
																return(m);
};
template <class _tg> inline _tg signum(_tg val){
                                                                if(val<0) return(-1);
                                                                if(val>0) return(+1);
                                                                return(0);
};
template <class _tg> _tg zufall(_tg g0,_tg g1){
                                                                
                                                                double e=double(rand())/double(RAND_MAX);
                                                                e=double(g0)+e*double(g1-g0);
                                                                return(_tg(e));
};
template <class _tg> _tg gauss(_tg x,_tg s){
				                                                return(exp(-(x*x)/(2*s*s)));
};
//******************************************************************************************************************************************************************************************************
//                                                              F U N C T I O N 
//******************************************************************************************************************************************************************************************************
template<class _tg> class _funktion{
        public:
                _funktion();
                virtual ~_funktion();
                void loeschen();
                virtual _funktion<_tg>*duplizieren()=0;
                void duplizieren(_funktion<_tg>*);
                virtual _tg berechnen(const _tg)const=0;
                inline _tg operieren(const _tg,const _tg)const;
                void setzenoperation(_operation<_tg>*);
                void setzenfunktionverschiebungx(_funktion<_tg>*);
                void setzenfunktionverschiebungy(_funktion<_tg>*);
                void setzenfunktionfaktorx(_funktion<_tg>*);
                void setzenfunktionfaktory(_funktion<_tg>*);
        protected:
                _tg berechnenverschiebungx(const _tg)const;
                _tg berechnenverschiebungy(const _tg)const;
                _tg berechnenfaktorx(const _tg)const;
                _tg berechnenfaktory(const _tg)const;
        private:                
                _funktion<_tg>*pfuncxoff;
                _funktion<_tg>*pfuncyoff;
                _funktion<_tg>*pfuncxfac;
                _funktion<_tg>*pfuncyfac;
                _operation<_tg>*poeration;
};

template<class _tg> _funktion<_tg>::_funktion(){
                                                                pfuncxoff=0;
                                                                pfuncyoff=0;
                                                                pfuncxfac=0;
                                                                pfuncyfac=0;
                                                                poperation=new _operationmultiplication<_tg>();
};
template<class _tg> _funktion<_tg>::~_funktion(){
                                                                loeschen();
                                                                if(poperation){
                                                                 delete poperation;
                                                                 poperation=0;
                                                                };
};
template<class _tg> void _funktion<_tg>::loeschen(){
                                                                if(pfuncxoff){
                                                                 delete pfuncxoff;
                                                                 pfuncxoff=0;
                                                                };
                                                                if(pfuncyoff){
                                                                 delete pfuncyoff;
                                                                 pfuncyoff=0;
                                                                };
                                                                if(pfuncxfac){
                                                                 delete pfuncxfac;
                                                                 pfuncxfac=0;
                                                                };
                                                                if(pfuncyfac){
                                                                 delete pfuncyfac;
                                                                 pfuncyfac=0;
                                                                };
};
template<class _tg> void _funktion<_tg>::duplizieren(_funktion<_tg>*f){
                                                                f->loeschen();
                                                                if(poperation) f->setzenoperation(poperation->duplizieren());
                                                                if(pfuncxoff) f->setzenfunktionverschiebungx(pfuncxoff->duplizieren());
                                                                if(pfuncyoff) f->setzenfunktionverschiebungy(pfuncyoff->duplizieren());
                                                                if(pfuncxfac) f->setzenfunktionfaktorx(pfuncxfac->duplizieren());
                                                                if(pfuncyfac) f->setzenfunktionfaktory(pfuncyfac->duplizieren());
};
template<class _tg> _tg _funktion<_tg>::operieren(const _tg a,const _tg b)const{
                                                                if(poperation){
                                                                 return(poperation->operieren(a,b));
                                                                }else{
                                                                 //error
                                                                 return(a*b);
                                                                };
};
template<class _tg> void _funktion<_tg>::setzenoperation(_operation<_tg>*o){
                                                                if(poperation){
                                                                 delete poperation;
                                                                 poperation=0;
                                                                };
                                                                if(o){
                                                                 poperation=o;
                                                                };
};
template<class _tg> void _funktion<_tg>::setzenfunktionverschiebungx(_funktion<_tg>*f){
                                                                if(f!=0){
                                                                 if(f->pfuncxoff==0){
                                                                  if(pfuncxoff){
                                                                   f->pfuncxoff=pfuncxoff->pfuncxoff;
                                                                   pfuncxoff->pfuncxoff=0;
                                                                  };
                                                                 };
                                                                 if(f->pfuncyoff==0){
                                                                  if(pfuncxoff){
                                                                   f->pfuncyoff=pfuncxoff->pfuncyoff;
                                                                   pfuncxoff->pfuncyoff=0;
                                                                  };
                                                                 };
                                                                 if(f->pfuncxfac==0){
                                                                  if(pfuncxoff){
                                                                   f->pfuncxfac=pfuncxoff->pfuncxfac;
                                                                   pfuncxoff->pfuncxfac=0;
                                                                  };
                                                                 };
                                                                 if(f->pfuncyfac==0){
                                                                  if(pfuncxoff){
                                                                   f->pfuncyfac=pfuncxoff->pfuncyfac;
                                                                   pfuncxoff->pfuncyfac=0;
                                                                  };
                                                                 };
                                                                };
                                                                if(pfuncxoff){
                                                                 delete pfuncxoff;
                                                                 pfuncxoff=0;
                                                                };
                                                                pfuncxoff=f;
};
template<class _tg> void _funktion<_tg>::setzenfunktionverschiebungy(_funktion<_tg>*f){
                                                                if(f!=0){
                                                                 if(f->pfuncxoff==0){
                                                                  if(pfuncyoff){
                                                                   f->pfuncxoff=pfuncyoff->pfuncxoff;
                                                                   pfuncyoff->pfuncxoff=0;
                                                                  };
                                                                 };
                                                                 if(f->pfuncyoff==0){
                                                                  if(pfuncyoff){
                                                                   f->pfuncyoff=pfuncyoff->pfuncyoff;
                                                                   pfuncyoff->pfuncyoff=0;
                                                                  };
                                                                 };
                                                                 if(f->pfuncxfac==0){
                                                                  if(pfuncyoff){
                                                                   f->pfuncxfac=pfuncyoff->pfuncxfac;
                                                                   pfuncyoff->pfuncxfac=0;
                                                                  };
                                                                 };
                                                                 if(f->pfuncyfac==0){
                                                                  if(pfuncyoff){
                                                                   f->pfuncyfac=pfuncyoff->pfuncyfac;
                                                                   pfuncyoff->pfuncyfac=0;
                                                                  };
                                                                 };
                                                                };
                                                                if(pfuncyoff){
                                                                 delete pfuncyoff;
                                                                 pfuncyoff=0;
                                                                };
                                                                pfuncyoff=f;
};
template<class _tg> void _funktion<_tg>::setzenfunktionfaktorx(_funktion<_tg>*f){
                                                                if(f!=0){
                                                                 if(f->pfuncxoff==0){
                                                                  if(pfuncxfac){
                                                                   f->pfuncxoff=pfuncxfac->pfuncxoff;
                                                                   pfuncxfac->pfuncxoff=0;
                                                                  };
                                                                 };
                                                                 if(f->pfuncyoff==0){
                                                                  if(pfuncxfac){
                                                                   f->pfuncyoff=pfuncxfac->pfuncyoff;
                                                                   pfuncxfac->pfuncyoff=0;
                                                                  };
                                                                 };
                                                                 if(f->pfuncxfac==0){
                                                                  if(pfuncxfac){
                                                                   f->pfuncxfac=pfuncxfac->pfuncxfac;
                                                                   pfuncxfac->pfuncxfac=0;
                                                                  };
                                                                 };
                                                                 if(f->pfuncyfac==0){
                                                                  if(pfuncxfac){
                                                                   f->pfuncyfac=pfuncxfac->pfuncyfac;
                                                                   pfuncxfac->pfuncyfac=0;
                                                                  };
                                                                 };
                                                                };
                                                                if(pfuncxfac){
                                                                 delete pfuncxfac;
                                                                 pfuncxfac=0;
                                                                };
                                                                pfuncxfac=f;
};
template<class _tg> void _funktion<_tg>::setzenfunktionfaktory(_funktion<_tg>*f){
                                                                if(f!=0){
                                                                 if(f->pfuncxoff==0){
                                                                  if(pfuncyfac){
                                                                   f->pfuncxoff=pfuncyfac->pfuncxoff;
                                                                   pfuncyfac->pfuncxoff=0;
                                                                  };
                                                                 };
                                                                 if(f->pfuncyoff==0){
                                                                  if(pfuncyfac){
                                                                   f->pfuncyoff=pfuncyfac->pfuncyoff;
                                                                   pfuncyfac->pfuncyoff=0;
                                                                  };
                                                                 };
                                                                 if(f->pfuncxfac==0){
                                                                  if(pfuncyfac){
                                                                   f->pfuncxfac=pfuncyfac->pfuncxfac;
                                                                   pfuncyfac->pfuncxfac=0;
                                                                  };
                                                                 };
                                                                 if(f->pfuncyfac==0){
                                                                  if(pfuncyfac){
                                                                   f->pfuncyfac=pfuncyfac->pfuncyfac;
                                                                   pfuncyfac->pfuncyfac=0;
                                                                  };
                                                                 };
                                                                };
                                                                if(pfuncyfac){
                                                                 delete pfuncyfac;
                                                                 pfuncyfac=0;
                                                                };
                                                                pfuncyfac=f;
};
template<class _tg> _tg _funktion<_tg>::berechnenverschiebungx(const _tg x)const{
                                                                if(pfuncxoff){
                                                                 return(pfuncxoff->calcuate(x));
                                                                }else{
                                                                 return(0);
                                                                };
};
template<class _tg> _tg _funktion<_tg>::berechnenverschiebungy(const _tg x)const{
                                                                if(pfuncyoff){
                                                                 return(pfuncyoff->calcuate(x));
                                                                }else{
                                                                 return(0);
                                                                };
};
template<class _tg> _tg _funktion<_tg>::berechnenfaktorx(const _tg x)const{
                                                                if(pfuncxfac){
                                                                 return(pfuncxfac->calcuate(x));
                                                                }else{
                                                                 return(1);
                                                                };
};
template<class _tg> _tg _funktion<_tg>::berechnenfaktory(const _tg x)const{
                                                                if(pfuncyfac){
                                                                 return(pfuncyfac->calcuate(x));
                                                                }else{
                                                                 return(1);
                                                                };
};
//******************************************************************************************************************************************************************************************************
//                                                              F U N C T I O N S I N U S
//******************************************************************************************************************************************************************************************************
template<class _tg> class _funktionsinus:public _funktion<_tg>{
        public:
                _funktionsinus();
                virtual ~_funktionsinus();
                _funktion<_tg>*duplizieren();
                _tg berechnen(const _tg)const;                
};
template<class _tg> _funktionsinus<_tg>::_funktionsinus(){
};
template<class _tg> _funktionsinus<_tg>::~_funktionsinus(){
};
template<class _tg> _funktion<_tg>* _funktionsinus<_tg>::duplizieren(){
                                                                _funktionsinus<_tg>*f;
                                                                //--------------------
                                                                f=new _funktionsinus<_tg>();
                                                                duplizieren(f);
                                                                return(f);
};
template<class _tg> _tg _funktionsinus<_tg>::berechnen(const _tg x)const{
                                                                return(
                                                                berechnenverschiebungy(x)+
                                                                sin( (x*2*_pi) * berechnenfaktorx(x) + caluculateoffsetx(x) )*
                                                                berechnenfaktory(x)
                                                                );
                                                                
};
//******************************************************************************************************************************************************************************************************
//                                                              O P E R A T I O N 
//******************************************************************************************************************************************************************************************************
template<class _tg> class _operation{
        public:
                _operation();
                virtual ~_operation();
                virtual _tg operieren(const _tg,const _tg)const=0;
};
template<class _tg> _operation<_tg>::_operation(){
};
template<class _tg> _operation<_tg>::~_operation(){
};
//******************************************************************************************************************************************************************************************************
//                                                              O P E R A T I O N M U L T I P L I C A T I O N 
//******************************************************************************************************************************************************************************************************
template<class _tg> class _operationmultiplication:public _operation<_tg>{
        public:
                _operationmultiplication();
                virtual ~_operationmultiplication();
                _tg operieren(const _tg,const _tg)const;
};
template<class _tg> _operationmultiplication<_tg>::_operationmultiplication(){
};
template<class _tg> _operationmultiplication<_tg>::~_operationmultiplication(){
};
template<class _tg> _tg _operationmultiplication<_tg>::operieren(const _tg a,const _tg b)const{
                                                                return(a*b);
};
//******************************************************************************************************************************************************************************************************
//                                                              F R A C T A L 
//******************************************************************************************************************************************************************************************************
template<class _tg> class _fraktal{
        public:
                _fraktal(_tg,_tg);
                virtual ~_fraktal();
                void imaginaer(const _tg);
                void real(const _tg);
                _tg&imaginaer();
                _tg&real();
                unsigned int methode()const;
                void methode(const unsigned int);
                _tg berechnen(const _tg,const _tg,const unsigned int);
        private:
                _tg ci,cr;
                unsigned int pmethode;
};
template<class _tg> _fraktal<_tg>::_fraktal(_tg r,_tg i){
                                                                cr=r;
                                                                ci=i;
                                                                pmethode=0;
};
template<class _tg> _fraktal<_tg>::~_fraktal(){
};
template<class _tg> void _fraktal<_tg>::imaginaer(const _tg i){
                                                                ci=i;
};
template<class _tg> void _fraktal<_tg>::real(const _tg r){
                                                                cr=r;
};
template<class _tg> _tg&_fraktal<_tg>::imaginaer(){
                                                                return(ci);    
};
template<class _tg> _tg&_fraktal<_tg>::real(){
                                                                return(cr);    
};
template<class _tg> void _fraktal<_tg>::methode(const unsigned int i){
                                                                pmethode=i;
};
template<class _tg> unsigned int _fraktal<_tg>::methode()const{
                                                                return(pmethode);
};


template<class _tg>_tg _fraktal<_tg>::berechnen(const _tg x,const _tg y,const unsigned int wide){
                                                                _tg xx;
                                                                _tg x1;
                                                                _tg y1;
                                                                _tg cnt;
                                                                //--------
                                                                x1=x;
                                                                y1=y;
                                                                cnt=0;
                                                                switch(pmethode){                                                             
                                                                case 0:
                                                                while ((cnt<=wide)&&(sqrt(x1*x1+y1*y1)<2)) {
                                                                 xx=x1*x1-y1*y1+cr;
                                                                 y1=2*x1*y1+ci;
                                                                 x1=xx;
                                                                 cnt+=1;
                                                                };
                                                                break;
                                                                case 1:
                                                                while ((cnt<=wide)&&(sqrt(x1*x1+y1*y1)<2)) {
                                                                 xx=(x1*x1*tan(1/(x1+0.000001))-y1*y1+cr);
                                                                 y1=(2*x1*y1+ci);
                                                                 x1=xx;
                                                                 cnt+=1;
                                                                };
                                                                break;
                                                                case 2:
                                                                while ((cnt<=wide)&&(sqrt(x1*x1+y1*y1)<2)) {
                                                                xx=sin(x1*x1)*x1-cos(y1*y1)*y1+cr;
                                                                y1=2*y1*x1+ci;
                                                                 x1=xx;
                                                                 cnt+=1;
                                                                };
                                                                break;
                                                                case 3:
                                                                while ((cnt<=wide)&&(sqrt(x1*x1+y1*y1)<2)) {
                                                                xx=(x1+y1)+cr;
                                                                y1=(y1-x1)+ci;
                                                                 x1=xx;
                                                                 cnt+=1;
                                                                };
                                                                break;
                                                                case 4:
                                                                while ((cnt<=wide)&&(sqrt(x1*x1+y1*y1)<2)) {
                                                                xx=x1*cos(abs(1-x1*x1))-y1*sqrt(0.5+abs(y1*y1))+cr;
                                                                y1=2*x1*x1*y1+ci;
                                                                 x1=xx;
                                                                 cnt+=1;
                                                                };
                                                                break;
                                                                case 5:
                                                                while ((cnt<=wide)&&(sqrt(x1*x1+y1*y1)<2)) {
                                                                xx=x1*x1*sin(x1*cr*100)-y1*y1+cr;
                                                                y1=2*x1*y1*(0.5+cos(y1*ci*100))+ci;
                                                                 x1=xx;
                                                                 cnt+=1;
                                                                };
                                                                break;
                                                                case 6:
                                                                while ((cnt<=wide)&&(sqrt(x1*x1+y1*y1)<2)) {
                                                                xx=x1*x1-y1*y1+cr;
                                                                y1=2*x1*y1+sin((x1*40*_pi)/180)+ci;
                                                                 x1=xx;
                                                                 cnt+=1;
                                                                };
                                                                break;
                                                                case 7:
                                                                while ((cnt<=wide)&&(sqrt(x1*x1+y1*y1)<2)) {
                                                                xx=x1*y1+y1*(2*y1)+ci;
                                                                y1=2*(cr-0)*x1+y1-ci/x1;
                                                                 x1=xx;
                                                                 cnt+=1;
                                                                };
                                                                break;
                                                                case 8:
                                                                while ((cnt<=wide)&&(sqrt(x1*x1+y1*y1)<2)) {
                                                                xx=x1+log(abs(x1))-log(abs(y1))*y1+pow(cr+0.2,3);
                                                                y1=xx*x1*tan(ci)+y1;
                                                                 x1=xx;
                                                                 cnt+=1;
                                                                };
                                                                break;
                                                                case 9:
                                                                while ((cnt<=wide)&&(sqrt(x1*x1+y1*y1)<2)) {
                                                                xx=x1*x1-y1*y1*x1+cr;
                                                                y1=2*x1*y1*x1+ci;
                                                                 x1=xx;
                                                                 cnt+=1;
                                                                };
                                                                break;
                                                                case 10:
                                                                while ((cnt<=wide)&&(sqrt(x1*x1+y1*y1)<2)) {
                                                                xx=x1*tan(x1-y1)*(y1-x1*y1)-y1*y1+cr;
                                                                y1=1.86*x1*y1+ci;
                                                                 x1=xx;
                                                                 cnt+=1;
                                                                };
                                                                break;
                                                                case 11:
                                                                while ((cnt<=wide)&&(sqrt(x1*x1+y1*y1)<2)) {
                                                                xx=2*x1*y1+ci;
                                                                y1=x1*x1+y1*y1+cr;
                                                                 x1=xx;
                                                                 cnt+=1;
                                                                };
                                                                break;
                                                                case 12:
                                                                while ((cnt<=wide)&&(sqrt(x1*x1+y1*y1)<2)) {
                                                                xx=x1*x1+y1*y1*x1+ci;
                                                                y1=1.9*x1*y1+y1-x1+cr;
                                                                 x1=xx;
                                                                 cnt+=1;
                                                                };
                                                                break;
                                                                case 13:
                                                                while ((cnt<=wide)&&(sqrt(x1*x1+y1*y1)<2)) {
                                                                xx=x1*y1*y1+pow(cr,2);
                                                                y1=(x1*y1+cr+cr)+ci-tan(x1);
                                                                 x1=xx;
                                                                 cnt+=1;
                                                                };
                                                                break;
                                                                case 14:
                                                                while ((cnt<=wide)&&(sqrt(x1*x1+y1*y1)<2)) {
                                                                xx=x1*y1+tan(cr)*y1/tan(y1);
                                                                y1=(x1*y1+cr/ci)-ci+tan(x1);
                                                                 x1=xx;
                                                                 cnt+=1;
                                                                };
                                                                break;
                                                                case 15:
                                                                while ((cnt<=wide)&&(sqrt(x1*x1+y1*y1)<2)) {
                                                                xx=x1*y1*y1+pow(cr,2)+tan(y1);
                                                                y1=(x1*y1+cr+cr)+ci-tan(x1);
                                                                 x1=xx;
                                                                 cnt+=1;
                                                                };
                                                                break;
                                                                case 16:
                                                                while ((cnt<=wide)&&(sqrt(x1*x1+y1*y1)<2)) {
                                                                xx=x1/y1*y1*y1+-0.04+tan(4*y1+cr);
                                                                y1=tan(x1*y1-0.4)+0.11-tan(x1*2+ci);
                                                                 x1=xx;
                                                                 cnt+=1;
                                                                };
                                                                break;
                                                                case 17:
                                                                while ((cnt<=wide)&&(sqrt(x1*x1+y1*y1)<2)) {
                                                                xx=x1*x1+y1*y1+(cr-1.75);
                                                                y1=tan(x1*y1-0.4)+ci+0.11-tan(x1*2+ci);
                                                                 x1=xx;
                                                                 cnt+=1;
                                                                };
                                                                break;
                                                                case 18:
                                                                while ((cnt<=wide)&&(sqrt(x1*x1+y1*y1)<2)) {
                                                                xx=(-x1*x1+y1*y1)+(cr);
                                                                y1=2*x1*y1+ci-tan(x1*2+ci);
                                                                 x1=xx;
                                                                 cnt+=1;
                                                                };
                                                                break;
                                                                case 19:
                                                                while (   (cnt<=wide)&&(sqrt(x1*x1+y1*y1)<2)   ) {
                                                                if (x1!=0) xx=x1*x1/tan(x1)+y1*y1*tan(y1)+cr;
                                                                y1=2*x1*y1+ci;
                                                                 x1=xx;
                                                                 cnt+=1;
                                                                };
                                                                break;
                                                                case 20:
                                                                xx=0;
                                                                while ((cnt<=wide)&&(sqrt(x1*x1+y1*y1)<2)) {
                                                                xx=2*x1*y1+xx*ci+ci;
                                                                y1=x1*log10(abs(0.1+abs(xx)))+y1*xx+cr+(_tg(cnt)/wide);
                                                                 x1=xx;
                                                                 cnt+=1;
                                                                };
                                                                break;
                                                                case 21:
                                                                while ((cnt<=wide)&&(sqrt(x1*x1+y1*y1)<2)) {
                                                                xx=x1*cos(ci*y1-x1)+y1+cr;
                                                                y1=y1*x1*1.9+ci;
                                                                 x1=xx;
                                                                 cnt+=1;
                                                                };
                                                                break;
                                                                case 22:
                                                                while ((cnt<=wide)&&(sqrt(x1*x1+y1*y1)<2)) {
                                                                xx=x1*cos((x1*45*_pi)/180)-y1*y1+cr;
                                                                y1=y1*x1*1.9+ci;
                                                                 x1=xx;
                                                                 cnt+=1;
                                                                };
                                                                break;
                                                                case 23:
                                                                while ((cnt<=wide)&&(sqrt(x1*x1+y1*y1)<2)) {
                                                                if ((x1!=0)&&(y1!=0)) xx=(y1/x1)*(x1/y1)-x1*y1*y1+cr;
                                                                y1=x1*y1*x1*1.99+ci;
                                                                 x1=xx;
                                                                 cnt+=1;
                                                                };
                                                                break;
                                                                case 24:
                                                                while ((cnt<=wide)&&(sqrt(x1*x1+y1*y1)<2)) {
                                                                xx=sqrt(pow(x1,2))-sqrt(pow(y1,2))+cr;
                                                                y1=2*x1*y1+ci;
                                                                 x1=xx;
                                                                 cnt+=1;
                                                                };
                                                                break;
                                                                case 25:
                                                                while ((cnt<=wide)&&(sqrt(x1*x1+y1*y1)<2)) {
                                                                xx=(x1*x1+sin(x1*90*_ph)*0.1)-(y1*y1+cos(y1*90*_ph)*0.1)+cr;
                                                                y1=2*x1*y1+ci;
                                                                 x1=xx;
                                                                 cnt+=1;
                                                                };
                                                                break;
                                                                case 26:
                                                                while ((cnt<=wide)&&(sqrt(x1*x1+y1*y1)<2)) {
                                                                xx=(1+sin(x1*_ph)*0.1)*x1+cos(x1*_ph)-y1*y1+(cr-1);
                                                                y1=2*x1*abs(y1)+ci;
                                                                 x1=xx;
                                                                 cnt+=1;
                                                                };
                                                                break;
                                                                case 27:
                                                                while ((cnt<=wide)&&(sqrt(x1*x1+y1*y1)<2)) {
                                                                xx=x1-(log(0.000000000001+abs(x1))-log(0.0000000000001+abs(y1))*y1+pow(cr+0.2,3));
                                                                y1=xx*x1+sin(y1*10*_ph)*tan(ci*cr*y1*ci)+(_tg(cnt)/wide);
                                                                 x1=xx;
                                                                 cnt+=1;
                                                                };
                                                                break;
                                                                };
                                                                return(cnt);
};
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 
                                                                 //xx=x1*x1-pow(y1,2)+cr+pow(sin(y1*1000*ci),2)-pow(sin(x1*1000*ci),2);
                                                                 //y1=(2*x1*y1)+ci;
                                                                 //xx=x1*x1+sin(y1*x1+x1*x1)*0.5-pow(y1,2)+cr;
                                                                 //y1=(2*x1*y1)+ci;
                                                                 //xx=pow(x1,2.0)-pow(y1,3)+cr;
                                                                 //y1=(2*x1*y1)+ci;
                                                                 //xx=x1*x1-y1*y1+cr;
                                                                 //y1=2*x1*y1+ci;
                                                                 //xx=0.03*abs(sin(x1*50))+x1*x1-pow(y1,2)+0.025*abs(tan(y1*y1*50))+cr;
                                                                 //y1=2*x1*y1+ci;
                                                                 //xx=0.01*abs(sin(x1*50))+x1*x1*y1-pow(y1,2.2)+0.01*abs(tan(y1*50))+cr; //krass beim einzoomen
                                                                 //y1=2*x1*y1+ci;
                                    /*    xx=x1*y1+tan(ca)*y1/tan(y1);
                                        y1=(x1*y1+ca/cb)-cb+tan(x1);
                                        xx=x1*y1*y1+pow(ca,2);
                                        y1=(x1*y1+ca+ca)+cb-tan(x1);
                                        xx=x1*x1+y1*y1*x1+ci;
                                        y1=1.9*x1*y1+y1-x1+cr;
                                        xx=2*x1*y1+ci; //kubisch
                                        y1=x1*x1+y1*y1+cr;
                                        xx=x1*tan(x1-y1)*(y1-x1*y1)-y1*y1+cr;
                                        y1=1.86*x1*y1+ci;
                                        xx=x1*x1-y1*y1*x1+cr;//sehr schee
                                        y1=2*x1*y1*x1+ci;
                                        xx=x1+log(abs(x1))-log(abs(y1))*y1+pow(cr+0.2,3);
                                        y1=xx*x1*tan(ci)+y1;
                                        xx=x1*y1+y1*(2*y1)+ci;//sehr schee
                                        y1=2*(cr-0)*x1+y1-ci/x1;
                                        xx=x1*x1-y1*y1+cr;
                                        y1=2*x1*y1+sin((x1*40*_pi)/180)+ci;
                                        xx=x1*x1*sin(x1*cr*100)-y1*y1+cr;
                                        y1=2*x1*y1*(0.5+cos(y1*ci*100))+ci;
                                        xx=x1*cos(abs(1-x1*x1))-y1*sqrt(0.5+abs(y1*y1))+cr;
                                        y1=2*x1*x1*y1+ci;
                                        xx=sin(x1*x1)*x1-cos(y1*y1)*y1+cr;
                                        y1=2*y1*x1+ci;
                                        xx=(x1*x1*tan(1/(x1+0.000001))-y1*y1+cr);
                                        y1=(2*x1*y1+ci);*/

          /*      if (method==fractalejm) {
                                        x1=xx;
                                        };
                if (method==fractaleejm) {
                                        x1=xx;
                                        }; 
                if (method==fractalsjm) {
                                        x1=xx;
                                        };
                if (method==fractale00) {
                                        x1=xx;
                                        };
                if (method==fractale01) {
                                        x1=xx;
                                        };
                if (method==fractale02) {
                                        x1=xx;
                                        };
                if (method==geisfrac1) {
                                        x1=xx;
                                        };
                if (method==geisfrac2) {
                                        x1=xx;
                                        };
                if (method==geisfrac3) {
                                        x1=xx;
                                        };
                if (method==fractale03) {
                                        x1=xx;
                                        };
                if (method==geisfrac4) {
                                        
                                        x1=xx;
                                        };
                if (method==geisfrac5) {
                                        x1=xx;
                                        };
                if (method==geisfrac6) {
                                        x1=xx;
                                        };
                if (method==geisfrac7) {
                                        x1=xx;
                                        };
                if (method==geisfrac8) {
                                        x1=xx;
                                        };
                if (method==16) {
                                        x1=xx;
                                        };
                if (method==17) {
                                        x1=xx;
                                        };
                if (method==18) {
                                        x1=xx;
                                        };
                if (method==19){
                                        x1=xx;
                                        };
                if (method==20){
                                        
                                        x1=xx;
                                        };
                if (method==21) {
                                        x1=xx;
                                        };
                if (method==22) {
                                        x1=xx;
                                        };
                if (method==23) {
                                        x1=xx;
                                        };
               if (method==24) {
                                        x1=xx;
                                        };
                if (method==25) {
                                        x1=xx;
                                        };
                if (method==26) {
                                        x1=xx;
                                        };
                if (method==27) {
                                        x1=xx;
                                        };




*/
//******************************************************************************************************************************************************************************************************
//                                                              K U R V E H E R M I T E 1
//******************************************************************************************************************************************************************************************************
template<class _tg> class _kurvehermite1{
        public:
                _kurvehermite1();
                _kurvehermite1(const _kurvehermite1<_tg>&);
                _kurvehermite1(_tg o0,_tg o1,_tg v0,_tg v1);
                virtual ~_kurvehermite1();
                void kopieren(const _kurvehermite1<_tg>&);
                void setzen(_tg o0,_tg o1,_tg v0,_tg v1);
                void ort(const unsigned int,_tg);
                void vektor(const unsigned int,_tg);
                _tg e();
                _tg ort(const unsigned int);
                _tg vektor(const unsigned int);
                _tg berechnen(_tg);
                void aktualisieren();
                _tg laenge()const;
        private:
                _tg pp0;
                _tg pp1;
                _tg pv0;
                _tg pv1;
                _tg pe;
                _tg plaenge;
         
};
template<class _tg> _kurvehermite1<_tg>::_kurvehermite1(){
                                                                pp0=0;
                                                                pp1=1;
                                                                pv0=1;
                                                                pv1=1;
                                                                plaenge=1;
};
template<class _tg> _kurvehermite1<_tg>::_kurvehermite1(const _kurvehermite1<_tg>&n){
                                                                kopieren(n);
};
template<class _tg> _kurvehermite1<_tg>::_kurvehermite1(_tg o0,_tg o1,_tg v0,_tg v1){
                                                                pp0=o0;
                                                                pp1=o1;
                                                                pv0=v0;
                                                                pv1=v1;
                                                                aktualisieren();
};
template<class _tg> _kurvehermite1<_tg>::~_kurvehermite1(){
};
template<class _tg> void _kurvehermite1<_tg>::kopieren(const _kurvehermite1<_tg>&n){
                                                                pp0=n.pp0;
                                                                pp1=n.pp1;
                                                                pv0=n.pv0;
                                                                pv1=n.pv1;
                                                                plaenge=n.plaenge;
};
template<class _tg> void _kurvehermite1<_tg>::setzen(_tg o0,_tg o1,_tg v0,_tg v1){
                                                                pp0=o0;
                                                                pp1=o1;
                                                                pv0=v0;
                                                                pv1=v1;
                                                                aktualisieren();
};
template<class _tg> void _kurvehermite1<_tg>::ort(const unsigned int i,_tg n){
                                                                if(i==0){
                                                                 pp0=n;
                                                                }else{
                                                                 pp1=n;
                                                                };
                                                                aktualisieren();
};
template<class _tg> void _kurvehermite1<_tg>::vektor(const unsigned int i,_tg n){
                                                                if(i==0){
                                                                 pv0=n;
                                                                }else{
                                                                 pv1=n;
                                                                };
                                                                aktualisieren();
};
template<class _tg> _tg _kurvehermite1<_tg>::e(){
                                                                return(pe);
};
template<class _tg> _tg _kurvehermite1<_tg>::ort(const unsigned int i){
                                                                if(i==0){
                                                                 return(pp0);
                                                                }else{
                                                                 return(pp1);
                                                                };
};
template<class _tg>_tg _kurvehermite1<_tg>::vektor(const unsigned int i){
                                                                if(i==0){
                                                                 return(pv0);
                                                                }else{
                                                                 return(pv1);
                                                                };
};
template<class _tg> void _kurvehermite1<_tg>::aktualisieren(){
				                                                plaenge=0;
				                                                _tg n;
				                                                _tg h;
				                                                h=pp0;
				                                                for(n=_tg(0.02);n<_tg(1.01);n=n+_tg(0.02)){
 				                                                 berechnen(n);
				                                                 h=pe-h;
				                                                 plaenge+=fabs(h);
				                                                 h=pe;
				                                                };
};
template<class _tg> _tg _kurvehermite1<_tg>::laenge()const{
                                                                return(plaenge);
};
template<class _tg> _tg _kurvehermite1<_tg>::berechnen(_tg t){
                                                                _tg t2;
                                                                _tg t3;
                                                                _tg cp0,cp1,cv0,cv1;
                                                                //--------------
                                                                t2=t*t;
                                                                t3=t2*t;
                                                                cp0=2*t3-3*t2+1;
                                                                cp1=-2*t3+3*t2;
                                                                cv0=t3-2*t2+t;
                                                                cv1=t3-t2;
                                                                pe=pp0*cp0 + pp1*cp1 + pv0*cv0 + pv1*cv1;
                                                                return(pe);
};
//******************************************************************************************************************************************************************************************************
//                                                              K U R V E H E R M I T E 2
//******************************************************************************************************************************************************************************************************
template<class _tg> class _kurvehermite2{
        public:
                _kurvehermite2();
                _kurvehermite2(const _kurvehermite2<_tg>&);
                _kurvehermite2(const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&);
                virtual ~_kurvehermite2();
                void kopieren(const _kurvehermite2<_tg>&);
                void setzen(_tg o0x,_tg o0y, _tg o1x,_tg o1y, _tg v0x,_tg v0y, _tg v1x,_tg v1y);
                void setzen(const _vektor2<_tg>&o0,const _vektor2<_tg>&o1,const _vektor2<_tg>&v0,const _vektor2<_tg>&v1);
                void setzen(const _vektor2<_tg>&o0,const _vektor2<_tg>&o1, _tg v0x,_tg v0y, _tg v1x,_tg v1y);
                void setzen(const _vektor2<_tg>&o0,_tg o1x,_tg o1y, _tg v0x,_tg v0y, _tg v1x,_tg v1y);
                void ort(const unsigned int,const _vektor2<_tg>&);
                void vektor(const unsigned int,const _vektor2<_tg>&);
                _vektor2<_tg>&e();
                _vektor2<_tg>&ort(const unsigned int);
                _vektor2<_tg>&vektor(const unsigned int);
                _vektor2<_tg>&berechnen(_tg);
                void aktualisieren();
                _tg laenge()const;
        private:
                _vektor2<_tg> pp0;
                _vektor2<_tg> pp1;
                _vektor2<_tg> pv0;
                _vektor2<_tg> pv1;
                _vektor2<_tg> pe;
                _tg plaenge;
         
};
template<class _tg> _kurvehermite2<_tg>::_kurvehermite2(){
                                                                pp0.setzen(0,0);
                                                                pp1.setzen(1,0);
                                                                pv0.setzen(1,0);
                                                                pv1.setzen(1,0);
                                                                plaenge=1;
};
template<class _tg> _kurvehermite2<_tg>::_kurvehermite2(const _kurvehermite2<_tg>&n){
                                                                kopieren(n);
};
template<class _tg> _kurvehermite2<_tg>::_kurvehermite2(const _vektor2<_tg>&p0,const _vektor2<_tg>&p1,const _vektor2<_tg>&v0,const _vektor2<_tg>&v1){
                                                                pp0=p0;
                                                                pp1=p1;
                                                                pv0=v0;
                                                                pv1=v1;
                                                                aktualisieren();
};
template<class _tg> _kurvehermite2<_tg>::~_kurvehermite2(){
};
template<class _tg> void _kurvehermite2<_tg>::kopieren(const _kurvehermite2<_tg>&n){
                                                                pp0=n.pp0;
                                                                pp1=n.pp1;
                                                                pv0=n.pv0;
                                                                pv1=n.pv1;
                                                                plaenge=n.plaenge;
};
template<class _tg> void _kurvehermite2<_tg>::setzen(_tg o0x,_tg o0y, _tg o1x,_tg o1y, _tg v0x,_tg v0y, _tg v1x,_tg v1y){
                                                                pp0.setzen(o0x,o0y);
                                                                pp1.setzen(o1x,o1y);
                                                                pv0.setzen(v0x,v0y);
                                                                pv1.setzen(v1x,v1y);
                                                                aktualisieren();
                                                                
};
template<class _tg> void _kurvehermite2<_tg>::setzen(const _vektor2<_tg>&o0,const _vektor2<_tg>&o1,const _vektor2<_tg>&v0,const _vektor2<_tg>&v1){
                                                                pp0=o0;
                                                                pp1=o1;
                                                                pv0=v0;
                                                                pv1=v1;
                                                                aktualisieren();
};
template<class _tg> void _kurvehermite2<_tg>::setzen(const _vektor2<_tg>&o0,const _vektor2<_tg>&o1, _tg v0x,_tg v0y, _tg v1x,_tg v1y){
                                                                pp0=o0;
                                                                pp1=o1;
                                                                pv0.setzen(v0x,v0y);
                                                                pv1.setzen(v1x,v1y);
                                                                aktualisieren();
};
template<class _tg> void _kurvehermite2<_tg>::setzen(const _vektor2<_tg>&o0,_tg o1x,_tg o1y, _tg v0x,_tg v0y, _tg v1x,_tg v1y){
                                                                pp0=o0;
                                                                pp1.setzen(o1x,o1y);
                                                                pv0.setzen(v0x,v0y);
                                                                pv1.setzen(v1x,v1y);
                                                                aktualisieren();
};
template<class _tg> void _kurvehermite2<_tg>::ort(const unsigned int i,const _vektor2<_tg>&n){
                                                                if(i==0){
                                                                 pp0=n;
                                                                }else{
                                                                 pp1=n;
                                                                };
                                                                aktualisieren();
};
template<class _tg> void _kurvehermite2<_tg>::vektor(const unsigned int i,const _vektor2<_tg>&n){
                                                                if(i==0){
                                                                 pv0=n;
                                                                }else{
                                                                 pv1=n;
                                                                };
                                                                aktualisieren();
};
template<class _tg> _vektor2<_tg>& _kurvehermite2<_tg>::e(){
                                                                return(pe);
};
template<class _tg> _vektor2<_tg>& _kurvehermite2<_tg>::ort(const unsigned int i){
                                                                if(i==0){
                                                                 return(pp0);
                                                                }else{
                                                                 return(pp1);
                                                                };
};
template<class _tg> _vektor2<_tg>&_kurvehermite2<_tg>::vektor(const unsigned int i){
                                                                if(i==0){
                                                                 return(pv0);
                                                                }else{
                                                                 return(pv1);
                                                                };
};
template<class _tg> void _kurvehermite2<_tg>::aktualisieren(){
				                                                plaenge=0;
				                                                _tg n;
				                                                _vektor2<_tg> h;
				                                                h=pp0;
				                                                for(n=_tg(0.02);n<_tg(1.01);n=n+_tg(0.02)){
 				                                                 berechnen(n);
				                                                 h=pe-h;
				                                                 plaenge+=h.laenge();
				                                                 h=pe;
				                                                };
};
template<class _tg> _tg _kurvehermite2<_tg>::laenge()const{
                                                                return(plaenge);
};
template<class _tg> _vektor2<_tg>&_kurvehermite2<_tg>::berechnen(_tg t){
                                                                _tg t2;
                                                                _tg t3;
                                                                _tg cp0,cp1,cv0,cv1;
                                                                //--------------
                                                                t2=t*t;
                                                                t3=t2*t;
                                                                cp0=2*t3-3*t2+1;
                                                                cp1=-2*t3+3*t2;
                                                                cv0=t3-2*t2+t;
                                                                cv1=t3-t2;
                                                                pe=pp0*cp0 + pp1*cp1 + pv0*cv0 + pv1*cv1;
                                                                return(pe);
};
//******************************************************************************************************************************************************************************************************
//                                                              K U R V E H E R M I T E 3
//******************************************************************************************************************************************************************************************************
template<class _tg> class _kurvehermite3{
        public:
                _kurvehermite3();
                _kurvehermite3(const _kurvehermite3<_tg>&);
                _kurvehermite3(const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor3<_tg>&);
                virtual ~_kurvehermite3();
                void kopieren(const _kurvehermite3<_tg>&);
                void setzen(_tg o0x,_tg o0y,_tg o0z, _tg o1x,_tg o1y,_tg o1z, _tg v0x,_tg v0y,_tg v0z, _tg v1x,_tg v1y,_tg v1z);
                void setzen(const _vektor3<_tg>&o0,const _vektor3<_tg>&o1,const _vektor3<_tg>&v0,const _vektor3<_tg>&v1);
                void setzen(const _vektor3<_tg>&o0,const _vektor3<_tg>&o1,const _vektor3<_tg>&v0, _tg v1x,_tg v1y,_tg v1z);
                void setzen(const _vektor3<_tg>&o0,const _vektor3<_tg>&o1, _tg v0x,_tg v0y,_tg v0z, _tg v1x,_tg v1y,_tg v1z);
                void setzen(const _vektor3<_tg>&o0,_tg o1x,_tg o1y,_tg o1z, _tg v0x,_tg v0y,_tg v0z, _tg v1x,_tg v1y,_tg v1z);
                void invertieren();
                void invertiereninvariant();
                void ort(const unsigned int,const _vektor3<_tg>&);
                void vektor(const unsigned int,const _vektor3<_tg>&);
                void vektor(const unsigned int,const _tg,const _tg,const _tg,bool update=true);
                _vektor3<_tg>&e();
                _vektor3<_tg>&ort(const unsigned int);
                _vektor3<_tg>&vektor(const unsigned int);
                _vektor3<_tg>&berechnen(_tg);
                void aktualisieren();
                _tg laenge()const;
        private:
                _vektor3<_tg> pp0;
                _vektor3<_tg> pp1;
                _vektor3<_tg> pv0;
                _vektor3<_tg> pv1;
                _vektor3<_tg> pe;
                _tg plaenge;
         
};
template<class _tg> _kurvehermite3<_tg>::_kurvehermite3(){
                                                                pp0.setzen(0,0,0);
                                                                pp1.setzen(1,0,0);
                                                                pv0.setzen(1,0,0);
                                                                pv1.setzen(1,0,0);
                                                                plaenge=1;
};
template<class _tg> _kurvehermite3<_tg>::_kurvehermite3(const _kurvehermite3<_tg>&n){
                                                                kopieren(n);
};
template<class _tg> _kurvehermite3<_tg>::_kurvehermite3(const _vektor3<_tg>&p0,const _vektor3<_tg>&p1,const _vektor3<_tg>&v0,const _vektor3<_tg>&v1){
                                                                pp0=p0;
                                                                pp1=p1;
                                                                pv0=v0;
                                                                pv1=v1;
                                                                aktualisieren();
};
template<class _tg> _kurvehermite3<_tg>::~_kurvehermite3(){
};
template<class _tg> void _kurvehermite3<_tg>::kopieren(const _kurvehermite3<_tg>&n){
                                                                pp0=n.pp0;
                                                                pp1=n.pp1;
                                                                pv0=n.pv0;
                                                                pv1=n.pv1;
                                                                plaenge=n.plaenge;
};
template<class _tg> void _kurvehermite3<_tg>::setzen(_tg o0x,_tg o0y,_tg o0z, _tg o1x,_tg o1y,_tg o1z, _tg v0x,_tg v0y,_tg v0z, _tg v1x,_tg v1y,_tg v1z){
                                                                pp0.setzen(o0x,o0y,o0z);
                                                                pp1.setzen(o1x,o1y,o1z);
                                                                pv0.setzen(v0x,v0y,v0z);
                                                                pv1.setzen(v1x,v1y,v1z);
                                                                aktualisieren();
                                                                
};
template<class _tg> void _kurvehermite3<_tg>::setzen(const _vektor3<_tg>&o0,const _vektor3<_tg>&o1,const _vektor3<_tg>&v0,const _vektor3<_tg>&v1){
                                                                pp0=o0;
                                                                pp1=o1;
                                                                pv0=v0;
                                                                pv1=v1;
                                                                aktualisieren();
};
template<class _tg> void _kurvehermite3<_tg>::setzen(const _vektor3<_tg>&o0,const _vektor3<_tg>&o1,const _vektor3<_tg>&v0, _tg v1x,_tg v1y,_tg v1z){
                                                                pp0=o0;
                                                                pp1=o1;
                                                                pv0=v0;
                                                                pv1.setzen(v1x,v1y,v1z);
                                                                aktualisieren();
};
template<class _tg> void _kurvehermite3<_tg>::setzen(const _vektor3<_tg>&o0,const _vektor3<_tg>&o1, _tg v0x,_tg v0y,_tg v0z, _tg v1x,_tg v1y,_tg v1z){
                                                                pp0=o0;
                                                                pp1=o1;
                                                                pv0.setzen(v0x,v0y,v0z);
                                                                pv1.setzen(v1x,v1y,v1z);
                                                                aktualisieren();
};
template<class _tg> void _kurvehermite3<_tg>::setzen(const _vektor3<_tg>&o0,_tg o1x,_tg o1y,_tg o1z, _tg v0x,_tg v0y,_tg v0z, _tg v1x,_tg v1y,_tg v1z){
                                                                pp0=o0;
                                                                pp1.setzen(o1x,o1y,o1z);
                                                                pv0.setzen(v0x,v0y,v0z);
                                                                pv1.setzen(v1x,v1y,v1z);
                                                                aktualisieren();
};
template<class _tg> void _kurvehermite3<_tg>::invertieren(){
				                                                _vektor3<_tg> h;
				                                                h=pp0;
				                                                pp0=pp1;
				                                                pp1=h;
};
template<class _tg> void _kurvehermite3<_tg>::invertiereninvariant(){
				                                                invertieren();
				                                                _vektor3<_tg> h;
				                                                h=pv0;
				                                                pv0=pv1;
				                                                pv1=h;
};
template<class _tg> void _kurvehermite3<_tg>::ort(const unsigned int i,const _vektor3<_tg>&n){
                                                                if(i==0){
                                                                 pp0=n;
                                                                }else{
                                                                 pp1=n;
                                                                };
                                                                aktualisieren();
};
template<class _tg> void _kurvehermite3<_tg>::vektor(const unsigned int i,const _vektor3<_tg>&n){
                                                                if(i==0){
                                                                 pv0=n;
                                                                }else{
                                                                 pv1=n;
                                                                };
                                                                aktualisieren();

};
template<class _tg> void _kurvehermite3<_tg>::vektor(const unsigned int i,const _tg x,const _tg y,const _tg z,bool update){
                                                                if(i==0){
                                                                 pv0.setzen(x,y,z);
                                                                }else{
                                                                 pv1.setzen(x,y,z);
                                                                };
                                                                if(update) aktualisieren();
};
template<class _tg> _vektor3<_tg>& _kurvehermite3<_tg>::e(){
                                                                return(pe);
};
template<class _tg> _vektor3<_tg>& _kurvehermite3<_tg>::ort(const unsigned int i){
                                                                if(i==0){
                                                                 return(pp0);
                                                                }else{
                                                                 return(pp1);
                                                                };
};
template<class _tg> _vektor3<_tg>&_kurvehermite3<_tg>::vektor(const unsigned int i){
                                                                if(i==0){
                                                                 return(pv0);
                                                                }else{
                                                                 return(pv1);
                                                                };
};
template<class _tg> void _kurvehermite3<_tg>::aktualisieren(){
				                                                plaenge=0;
				                                                _tg n;
				                                                _vektor3<_tg> h;
				                                                h=pp0;
				                                                for(n=_tg(0.02);n<_tg(1.01);n=n+_tg(0.02)){
 				                                                 berechnen(n);
				                                                 h=pe-h;
				                                                 //calculate(n+0.02)
				                                                 //h.sub(e)
				                                                 plaenge+=h.laenge();
				                                                 h=pe;
				                                                };
                                                                
};
template<class _tg> _tg _kurvehermite3<_tg>::laenge()const{
                                                                return(plaenge);
};
template<class _tg> _vektor3<_tg>&_kurvehermite3<_tg>::berechnen(_tg t){
                                                                _tg t2;
                                                                _tg t3;
                                                                _tg cp0,cp1,cv0,cv1;
                                                                //--------------
                                                                t2=t*t;
                                                                t3=t2*t;
                                                                cp0=2*t3-3*t2+1;
                                                                cp1=-2*t3+3*t2;
                                                                cv0=t3-2*t2+t;
                                                                cv1=t3-t2;
                                                                pe=pp0*cp0 + pp1*cp1 + pv0*cv0 + pv1*cv1;
                                                                return(pe);
};
//******************************************************************************************************************************************************************************************************
//                                                              K U R V E H E R M I T E 4
//******************************************************************************************************************************************************************************************************
template<class _tg> class _kurvehermite4{
        public:
                _kurvehermite4();
                _kurvehermite4(const _kurvehermite4<_tg>&);
                _kurvehermite4(const _vektor4<_tg>&,const _vektor4<_tg>&,const _vektor4<_tg>&,const _vektor4<_tg>&);
                virtual ~_kurvehermite4();
                void kopieren(const _kurvehermite4<_tg>&);
                void setzen(_tg o0x,_tg o0y,_tg o0z,_tg o0w, _tg o1x,_tg o1y,_tg o1z,_tg o1w, _tg v0x,_tg v0y,_tg v0z,_tg v0w, _tg v1x,_tg v1y,_tg v1z,_tg v1w);
                void setzen(const _vektor4<_tg>&o0,const _vektor4<_tg>&o1,const _vektor4<_tg>&v0,const _vektor4<_tg>&v1);
                void setzen(const _vektor4<_tg>&o0,const _vektor4<_tg>&o1, _tg v0x,_tg v0y,_tg v0z,_tg v0w, _tg v1x,_tg v1y,_tg v1z,_tg v1w);
                void setzen(const _vektor4<_tg>&o0,_tg o1x,_tg o1y,_tg o1z,_tg o1w, _tg v0x,_tg v0y,_tg v0z,_tg v0w, _tg v1x,_tg v1y,_tg v1z,_tg v1w);
                void ort(const unsigned int,const _vektor4<_tg>&);
                void vektor(const unsigned int,const _vektor4<_tg>&);
                _vektor4<_tg>&e();
                _vektor4<_tg>&ort(const unsigned int);
                _vektor4<_tg>&vektor(const unsigned int);
                _vektor4<_tg>&berechnen(_tg);
                void aktualisieren();
                _tg laenge()const;
        private:
                _vektor4<_tg> pp0;
                _vektor4<_tg> pp1;
                _vektor4<_tg> pv0;
                _vektor4<_tg> pv1;
                _vektor4<_tg> pe;
                _tg plaenge;
         
};
template<class _tg> _kurvehermite4<_tg>::_kurvehermite4(){
                                                                pp0.setzen(0,0,0,0);
                                                                pp1.setzen(1,0,0,1);
                                                                pv0.setzen(1,0,0,0);
                                                                pv1.setzen(1,0,0,0);
                                                                plaenge=1;
};
template<class _tg> _kurvehermite4<_tg>::_kurvehermite4(const _kurvehermite4<_tg>&n){
                                                                kopieren(n);
};
template<class _tg> _kurvehermite4<_tg>::_kurvehermite4(const _vektor4<_tg>&p0,const _vektor4<_tg>&p1,const _vektor4<_tg>&v0,const _vektor4<_tg>&v1){
                                                                pp0=p0;
                                                                pp1=p1;
                                                                pv0=v0;
                                                                pv1=v1;
                                                                aktualisieren();
};
template<class _tg> _kurvehermite4<_tg>::~_kurvehermite4(){
};
template<class _tg> void _kurvehermite4<_tg>::kopieren(const _kurvehermite4<_tg>&n){
                                                                pp0=n.pp0;
                                                                pp1=n.pp1;
                                                                pv0=n.pv0;
                                                                pv1=n.pv1;
                                                                plaenge=n.plaenge;
};
template<class _tg> void _kurvehermite4<_tg>::setzen(_tg o0x,_tg o0y,_tg o0z,_tg o0w, _tg o1x,_tg o1y,_tg o1z,_tg o1w, _tg v0x,_tg v0y,_tg v0z,_tg v0w, _tg v1x,_tg v1y,_tg v1z,_tg v1w){
                                                                pp0.setzen(o0x,o0y,o0z,o0w);
                                                                pp1.setzen(o1x,o1y,o1z,o1w);
                                                                pv0.setzen(v0x,v0y,v0z,v0w);
                                                                pv1.setzen(v1x,v1y,v1z,v1w);
                                                                aktualisieren();
                                                                
};
template<class _tg> void _kurvehermite4<_tg>::setzen(const _vektor4<_tg>&o0,const _vektor4<_tg>&o1,const _vektor4<_tg>&v0,const _vektor4<_tg>&v1){
                                                                pp0=o0;
                                                                pp1=o1;
                                                                pv0=v0;
                                                                pv1=v1;
                                                                aktualisieren();
};
template<class _tg> void _kurvehermite4<_tg>::setzen(const _vektor4<_tg>&o0,const _vektor4<_tg>&o1, _tg v0x,_tg v0y,_tg v0z,_tg v0w, _tg v1x,_tg v1y,_tg v1z,_tg v1w){
                                                                pp0=o0;
                                                                pp1=o1;
                                                                pv0.setzen(v0x,v0y,v0z,v0w);
                                                                pv1.setzen(v1x,v1y,v1z,v1w);
                                                                aktualisieren();
};
template<class _tg> void _kurvehermite4<_tg>::setzen(const _vektor4<_tg>&o0,_tg o1x,_tg o1y,_tg o1z,_tg o1w, _tg v0x,_tg v0y,_tg v0z,_tg v0w, _tg v1x,_tg v1y,_tg v1z,_tg v1w){
                                                                pp0=o0;
                                                                pp1.setzen(o1x,o1y,o1z,o1w);
                                                                pv0.setzen(v0x,v0y,v0z,v0w);
                                                                pv1.setzen(v1x,v1y,v1z,v1w);
                                                                aktualisieren();
};
template<class _tg> void _kurvehermite4<_tg>::ort(const unsigned int i,const _vektor4<_tg>&n){
                                                                if(i==0){
                                                                 pp0=n;
                                                                }else{
                                                                 pp1=n;
                                                                };
                                                                aktualisieren();
};
template<class _tg> void _kurvehermite4<_tg>::vektor(const unsigned int i,const _vektor4<_tg>&n){
                                                                if(i==0){
                                                                 pv0=n;
                                                                }else{
                                                                 pv1=n;
                                                                };
                                                                aktualisieren();

};
template<class _tg> _vektor4<_tg>& _kurvehermite4<_tg>::e(){
                                                                return(pe);
};
template<class _tg> _vektor4<_tg>& _kurvehermite4<_tg>::ort(const unsigned int i){
                                                                if(i==0){
                                                                 return(pp0);
                                                                }else{
                                                                 return(pp1);
                                                                };
};
template<class _tg> _vektor4<_tg>&_kurvehermite4<_tg>::vektor(const unsigned int i){
                                                                if(i==0){
                                                                 return(pv0);
                                                                }else{
                                                                 return(pv1);
                                                                };
};
template<class _tg> void _kurvehermite4<_tg>::aktualisieren(){
				                                                plaenge=0;
				                                                _tg n;
				                                                _vektor4<_tg> h;
				                                                h=pp0;
				                                                for(n=_tg(0.02);n<_tg(1.01);n=n+_tg(0.02)){
 				                                                 berechnen(n);
				                                                 h=pe-h;
				                                                 //calculate(n+0.02)
				                                                 //h.sub(e)
				                                                 plaenge+=h.laenge();
				                                                 h=pe;
				                                                };
                                                                
};
template<class _tg> _tg _kurvehermite4<_tg>::laenge()const{
                                                                return(plaenge);
};
template<class _tg> _vektor4<_tg>&_kurvehermite4<_tg>::berechnen(_tg t){
                                                                _tg t2;
                                                                _tg t3;
                                                                _tg cp0,cp1,cv0,cv1;
                                                                //--------------
                                                                t2=t*t;
                                                                t3=t2*t;
                                                                cp0=2*t3-3*t2+1;
                                                                cp1=-2*t3+3*t2;
                                                                cv0=t3-2*t2+t;
                                                                cv1=t3-t2;
                                                                pe=pp0*cp0 + pp1*cp1 + pv0*cv0 + pv1*cv1;
                                                                return(pe);
};
//******************************************************************************************************************************************************************************************************
//                                                              F L A E C H E H E R M I T E 
//******************************************************************************************************************************************************************************************************
template<class _tg> class _flaechehermite{
        public:
                _flaechehermite();
                _flaechehermite(_flaechehermite<_tg>*);
                //_flaechehermite(const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor3<_tg>&);
                virtual ~_flaechehermite();
                void kopieren(_flaechehermite<_tg>*);
                void ortort(const unsigned int,const _vektor3<_tg>&);
                void ortvektor(const unsigned int,const _vektor3<_tg>&);
                void vektorort(const unsigned int,const _vektor3<_tg>&);
                void vektorvektor(const unsigned int,const _vektor3<_tg>&);
                _vektor3<_tg>&ortort(const unsigned int);
                _vektor3<_tg>&ortvektor(const unsigned int);
                _vektor3<_tg>&vektorort(const unsigned int);
                _vektor3<_tg>&vektorvektor(const unsigned int);
                _vektor3<_tg> berechnen(const _tg s,const _tg t)const;
        private:
                _vektor3<_tg> portort[4];//vier stützvektoren 
                _vektor3<_tg> portvektor[4];//und die dazugehörigen primärtangenten
                _vektor3<_tg> pvektorort[4];//vier sekundäre tangentenorte
                _vektor3<_tg> pvektorvektor[4];//und die dazugehörigen sekundären tangententangenten
         
};
template<class _tg> _flaechehermite<_tg>::_flaechehermite(){
                                                                portort[0].setzen(0,0,0);
                                                                portort[1].setzen(1,0,0);
                                                                portort[2].setzen(1,0,1);
                                                                portort[3].setzen(0,0,1);
                                                                portvektor[0].setzen(0,0,0);
                                                                portvektor[1].setzen(0,0,0);
                                                                portvektor[2].setzen(0,0,0);
                                                                portvektor[3].setzen(0,0,0);
                                                                pvektorort[0].setzen(0,0,0);
                                                                pvektorort[1].setzen(0,0,0);
                                                                pvektorort[2].setzen(0,0,0);
                                                                pvektorort[3].setzen(0,0,0);
                                                                pvektorvektor[0].setzen(0,0,0);
                                                                pvektorvektor[1].setzen(0,0,0);
                                                                pvektorvektor[2].setzen(0,0,0);
                                                                pvektorvektor[3].setzen(0,0,0);
};
template<class _tg> _flaechehermite<_tg>::_flaechehermite(_flaechehermite<_tg>*n){
                                                                kopieren(n);
};
template<class _tg> _flaechehermite<_tg>::~_flaechehermite(){
};
template<class _tg> void _flaechehermite<_tg>::kopieren(_flaechehermite<_tg>*n){
                                                                for(int i=0;i<4;i++){
                                                                 portort[i]=n->portort[i];
                                                                 portvec[i]=n->portvec[i];
                                                                 pvecort[i]=n->pvecort[i];
                                                                 pvecvec[i]=n->pvecvec[i];
                                                                };
};
template<class _tg> void _flaechehermite<_tg>::ortort(const unsigned int i,const _vektor3<_tg>&n){
                                                                if(i<4) portort[i]=n;
};
template<class _tg> void _flaechehermite<_tg>::ortvektor(const unsigned int i,const _vektor3<_tg>&n){
                                                                if(i<4) portvektor[i]=n;
};
template<class _tg> void _flaechehermite<_tg>::vektorort(const unsigned int i,const _vektor3<_tg>&n){
                                                                if(i<4) pvektorort[i]=n;
};
template<class _tg> void _flaechehermite<_tg>::vektorvektor(const unsigned int i,const _vektor3<_tg>&n){
                                                                if(i<4) pvektorvektor[i]=n;
};
template<class _tg> _vektor3<_tg>& _flaechehermite<_tg>::ortort(const unsigned int i){
                                                                if(i<4) return(portort[i]); else return(portort[0]);
};
template<class _tg> _vektor3<_tg>& _flaechehermite<_tg>::ortvektor(const unsigned int i){
                                                                if(i<4) return(portvektor[i]); else return(portvektor[0]);
};
template<class _tg> _vektor3<_tg>& _flaechehermite<_tg>::vektorort(const unsigned int i){
                                                                if(i<4) return(pvektorort[i]); else return(pvektorort[0]);
};
template<class _tg> _vektor3<_tg>& _flaechehermite<_tg>::vektorvektor(const unsigned int i){
                                                                if(i<4) return(pvektorvektor[i]); else return(pvektorvektor[0]);
};
template<class _tg> _vektor3<_tg> _flaechehermite<_tg>::berechnen(const _tg s,const _tg t)const{
                                                                _tg t2,t3,tc0,tc1,tc2,tc3;
                                                                _tg s2,s3,sc0,sc1,sc2,sc3;
                                                                _vektor3<_tg> p0;
                                                                _vektor3<_tg> p1;
                                                                _vektor3<_tg> v0;
                                                                _vektor3<_tg> v1;
                                                                //--------------
                                                                s2=s*s;
                                                                s3=s2*s;
                                                                sc0=2*s3-3*s2+1;
                                                                sc1=-2*s3+3*s2;
                                                                sc2=s3-2*s2+s;
                                                                sc3=s3-s2;
                                                                t2=t*t;
                                                                t3=t2*t;
                                                                tc0=2*t3-3*t2+1;
                                                                tc1=-2*t3+3*t2;
                                                                tc2=t3-2*t2+t;
                                                                tc3=t3-t2;
                                                                //Hermite-t-kurven
                                                                p0 = portort[0]*tc0    + portort[3]*tc1    + portvektor[0]*tc2    + portvektor[3]*tc3;
                                                                p1 = portort[1]*tc0    + portort[2]*tc1    + portvektor[1]*tc2    + portvektor[2]*tc3;
                                                                v0 = pvektorort[0]*tc0 + pvektorort[3]*tc1 + pvektorvektor[0]*tc2 + pvektorvektor[3]*tc3;
                                                                v1 = pvektorort[1]*tc0 + pvektorort[2]*tc1 + pvektorvektor[1]*tc2 + pvektorvektor[2]*tc3;
                                                                return(p0*sc0 + p1*sc1 + v0*sc2 + v1*sc3);
};
//******************************************************************************************************************************************************************************************************
//                                                              R A N D O M I Z E R 
//******************************************************************************************************************************************************************************************************
template<class _tg> class _zufallsgenerator{
        public:
                _zufallsgenerator();
                virtual ~_zufallsgenerator();
                inline _tg berechnen(_tg,_tg)const;                
};
template<class _tg> _zufallsgenerator<_tg>::_zufallsgenerator(){
};
template<class _tg> _zufallsgenerator<_tg>::~_zufallsgenerator(){
};
template<class _tg> _tg _zufallsgenerator<_tg>::berechnen(_tg min,_tg max)const{
                                                                _tg x;
                                                                _tg h;
                                                                _tg rm=(_tg)RAND_MAX;
                                                                _tg r;
                                                                _tg f;
                                                                //--------
                                                                if(max<min) {
                                                                 h=max;
                                                                 max=min;
                                                                 min=h;
                                                                };
                                                                f=max-min;
                                                                r=(_tg)rand();
                                                                x=min+((r/rm)*f);
                                                                return(x);
};

#endif
