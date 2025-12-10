//******************************************************************************************************************************************************************************************************
//  Project     : grundplatte
//  Library     : _grundplatte.lib
//  Module      : _vektor.hpp
//  Date        : 18.12.2002
//  Description : 
//******************************************************************************************************************************************************************************************************
#ifndef _vektorh_included
#define _vektorh_included

//******************************************************************************************************************************************************************************************************
//                                                              F O R W A R D S 
//******************************************************************************************************************************************************************************************************
template <class _tg=typgeometrie> class _vektoranalysis;
template <class _tg=typgeometrie> class _vektoranalysis2;
template <class _tg=typgeometrie> class _vektoranalysis3;
template <class _tg=typgeometrie> class _vektor;
template <class _tg=typgeometrie> class _vektor2;
template <class _tg=typgeometrie> class _vektor3;
template <class _tg=typgeometrie> class _vektor4;
template <class _tg=typgeometrie> class _vektorraum;


#include <stdarg.h>
#include <stdlib.h>
#include <_global.hpp>




//******************************************************************************************************************************************************************************************************
//                                                              G L O B A L E 
//******************************************************************************************************************************************************************************************************
extern double _pi;
extern double _ph;

//************************************************************************************************************************************************************************************************
//                                                              G L O B A L E  F U N K T I O N T E M P L A T E S 
//************************************************************************************************************************************************************************************************
//template<class _tg
/*template<class _tg> 
inline void setzen(_tg&ex,_tg&ey,_tg x,_tg y){
                                ex=x;
                                ey=y;
};*/

//typedef typgeometrie _vektor3g[3];

template<class _tg> 
inline void setzen(_tg*e,_tg x,_tg y,_tg z){
                                e[0]=x;
                                e[1]=y;
                                e[2]=z;
};
template<class _tg> 
inline void setzen(_tg*e,const _tg*x){
                                e[0]=x[0];
                                e[1]=x[1];
                                e[2]=x[2];
};
template<class _tg> 
inline void setzen2(_tg*e,const _tg*x){
                                e[0]=x[0];
                                e[1]=x[1];
};
/*
inline void setzen(_vektor3g&o,_tg x,_tg y,_tg z){
                                o[0]=x;
                                o[1]=y;
                                o[2]=z;
};
*/
/*
inline void setzen(_tg*o,const _vektor<typgeometrie>&x){
                                o[0]=x[0];
                                o[1]=x[1];
                                o[2]=x[2];
};
*/

template<class _tg> 
inline void setzen(_tg*e,const _vektor<_tg>&x){
                                e[0]=x[0];
                                e[1]=x[1];
                                e[2]=x[2];
};
template<class _tg> 
inline void setzen(_tg*e,const _vektor3<_tg>&x){
                                e[0]=x[0];
                                e[1]=x[1];
                                e[2]=x[2];
};
template<class _tg> 
inline void addieren(_tg*e,const _vektor<_tg>&x){
                                e[0]+=x[0];
                                e[1]+=x[1];
                                e[2]+=x[2];
};
template<class _tg> 
inline void addieren(_tg*e,const _vektor3<_tg>&x){
                                e[0]+=x[0];
                                e[1]+=x[1];
                                e[2]+=x[2];
};
template<class _tg> 
inline void addieren(_tg*e,const _tg*a,const _tg*b){
                                e[0]=a[0]+b[0];
                                e[1]=a[1]+b[1];
                                e[2]=a[2]+b[2];
};
template<class _tg> 
inline void addieren(_tg*e,const _tg*a){
                                e[0]+=a[0];
                                e[1]+=a[1];
                                e[2]+=a[2];
};
template<class _tg> 
inline void subtrahieren(_tg&ex,_tg&ey,_tg x,_tg y){
                                ex-=x;
                                ey-=y;
};
template<class _tg> 
inline void subtrahieren(_tg*e,const _tg*a,const _tg*b){
                                e[0]=a[0]-b[0];
                                e[1]=a[1]-b[1];
                                e[2]=a[2]-b[2];
};
template<class _tg> 
inline void subtrahieren2(_tg*e,const _tg*a,const _tg*b){
                                e[0]=a[0]-b[0];
                                e[1]=a[1]-b[1];
};
template<class _tg> 
inline _tg multiplizieren(_tg ex,_tg ey,_tg x,_tg y){
                                return(ex*x+ey*y);
};
template<class _tg> 
inline void multiplizieren(_tg*e,const _tg x){
                                e[0]*=x;
                                e[1]*=x;
                                e[2]*=x;
                                
};
template<class _tg> 
inline void multiplizieren2(_tg*e,const _tg x){
                                e[0]*=x;
                                e[1]*=x;
};
/*
inline void multiplizieren(_tg*e,const _tg f){
                                e[0]*=f;
                                e[1]*=f;
                                e[2]*=f;
};
*/
/*
inline void multiplizieren(const _vektor3g&a,const _vektor3g&b)const {
                                return(a[0]*b[0]+a[1]*b[1]+a[2]*b[2]);
};
*/
template<class _tg> 
inline _tg produkt(const _tg*a ,const _tg*b){
                                return(a[0]*b[0] + a[1]*b[1] + a[2]*b[2]);
};
template<class _tg> 
inline _tg produkt(const _tg*a ,const _vektor3<_tg>&b){
                                return(a[0]*b[0] + a[1]*b[1] + a[2]*b[2]);
};
template<class _tg> 
inline _tg produkt2(const _tg*a ,const _tg*b){
                                return(a[0]*b[0] + a[1]*b[1]);
};
template<class _tg>
inline _tg magnitude(_tg x,_tg y,_tg z){
                                return(sqrt(x*x+y*y+z*z));
};
/*
template<class _tg>
inline _tg magnitude(_tg*x){
                                return(sqrt(x[0]*x[0] + x[1]*x[1] + x[2]*x[2]));
};*/
template<class _tg> 
inline _tg magnitude(const _tg*x){
                                return(sqrt(x[0]*x[0] + x[1]*x[1]+ x [2]*x[2]));
};
template<class _tg>
inline void normalisieren(_tg*v){
                                _tg l=sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
                                if(l>0){
                                 l=1.0f/l;
                                 v[0]*=l;
                                 v[1]*=l;
                                 v[2]*=l;
                                };
};
template<class _tg>
inline void normalisieren2(_tg*v){
                                _tg l=sqrt(v[0]*v[0] + v[1]*v[1]);
                                if(l>0){
                                 l=1.0f/l;
                                 v[0]*=l;
                                 v[1]*=l;
                                };
};
/*
inline void normalisieren(_vektor3g&v){
                                _tg l=sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);
                                if(l>0){
                                 l=1/l;
                                 v[0]*=l;
                                 v[1]*=l;
                                 v[2]*=l;
                                };
};
*/
template<class _tg>
inline unsigned int groessterindex(_tg*v){
                                _tg a0=fabs(v[0]);
                                _tg a1=fabs(v[1]);
                                _tg a2=fabs(v[2]);
                                if((a0>a1)&&(a0>a2)) return(0);
                                if((a1>a0)&&(a1>a2)) return(1);
                                if((a2>a0)&&(a2>a1)) return(2);
                                return(0);
};
template<class _tg>
inline _tg determinieren2(const _tg*a,const _tg*b){
                                return(a[0]*b[1]-a[1]*b[0]);
};
template<class _tg>
inline _tg determinieren2(const _tg ax,const _tg ay,const _tg bx,const _tg by){
                                return(ax*by-ay*bx);
};
template<class _tg>
inline _tg determinieren(const _tg*a,const _tg*b,const _tg*c){
                                return(
                                +a[0]* ( b[1]*c[2] - c[1]*b[2])
                                +a[1]* (-b[0]*c[2] + c[0]*b[2])
                                +a[2]* ( b[0]*c[1] - c[0]*b[1]));
};
template<class _tg>
_tg determinieren(const _vektor3<_tg>&a,const _vektor3<_tg>&b,const _vektor3<_tg>&c){
                                return(
                                +a[0]* ( b[1]*c[2] - c[1]*b[2])
                                +a[1]* (-b[0]*c[2] + c[0]*b[2])
                                +a[2]* ( b[0]*c[1] - c[0]*b[1]));
};
template<class _tg> 
void rotieren(const _tg*vv,const _tg*p,const _tg w,_tg*e){
                                _tg a,b;
                                _tg v[3];
                                _tg matrix[3][3];
                                _tg sinw,cosw;
                                int x=0,y=1,z=2;
                                int i;
                                //------------
                                v[0]=vv[0];
                                v[1]=vv[1];
                                v[2]=vv[2];
                                normalisieren(v);
                                sinw=sin(w*_ph);
                                cosw=cos(w*_ph);
                                a=sinw;
                                b=1-cosw;
                                matrix[0][0]=cosw+b*v[x]*v[x];
                                matrix[1][0]=     b*v[x]*v[y]+a*+v[z];
                                matrix[2][0]=     b*v[x]*v[z]+a*-v[y];
                                matrix[0][1]=     b*v[y]*v[x]+a*-v[z];
                                matrix[1][1]=cosw+b*v[y]*v[y];
                                matrix[2][1]=     b*v[y]*v[z]+a*+v[x];
                                matrix[0][2]=     b*v[z]*v[x]+a*+v[y];
                                matrix[1][2]=     b*v[z]*v[y]+a*-v[x];
                                matrix[2][2]=cosw+b*v[z]*v[z];
                                for(i=0;i<3;i++) e[i]=matrix[0][i]*p[x]+matrix[1][i]*p[y]+matrix[2][i]*p[z];
};
template<class _tg> 
void rotieren(const _vektor3<_tg>&achse,const _vektor3<_tg>&p,const _tg w,_vektor3<_tg>&e){
                                _tg a,b;
                                _tg v[3];
                                _tg matrix[3][3];
                                _tg sinw,cosw;
                                int x=0,y=1,z=2;
                                int i;
                                //------------
                                v[0]=achse[0];
                                v[1]=achse[1];
                                v[2]=achse[2];
                                normalisieren(v);
                                sinw=sin(w*_ph);
                                cosw=cos(w*_ph);
                                a=sinw;
                                b=1-cosw;
                                matrix[0][0]=cosw+b*v[x]*v[x];
                                matrix[1][0]=     b*v[x]*v[y]+a*+v[z];
                                matrix[2][0]=     b*v[x]*v[z]+a*-v[y];
                                matrix[0][1]=     b*v[y]*v[x]+a*-v[z];
                                matrix[1][1]=cosw+b*v[y]*v[y];
                                matrix[2][1]=     b*v[y]*v[z]+a*+v[x];
                                matrix[0][2]=     b*v[z]*v[x]+a*+v[y];
                                matrix[1][2]=     b*v[z]*v[y]+a*-v[x];
                                matrix[2][2]=cosw+b*v[z]*v[z];
                                for(i=0;i<3;i++) e.setzenkomponente(i,matrix[0][i]*p[x]+matrix[1][i]*p[y]+matrix[2][i]*p[z]);
};

template <class _tg> 
void kreuzprodukt(_tg*e,const _tg*a,const _tg*b){
                                e[0]=b[1]*a[2] - b[2]*a[1];
                                e[1]=b[2]*a[0] - b[0]*a[2];
                                e[2]=b[0]*a[1] - b[1]*a[0];
};
template <class _tg> 
void berechnenorthogonalenvektor2(const _tg*a,_tg*b){
                                //ax*bx+ay*by==0
                                //1) bx=(-ay*by)/ax else
                                //2) by=(-ax*bx)/ay
                                if(fabs(a[0])>fabs(a[1])){
                                 b[1]=1;
                                 b[0]=(-a[1]*b[1])/a[0];
                                }else{
                                 b[0]=1;
                                 b[1]=(-a[0]*b[0])/a[1];
                                };
};
template <class _tg> 
bool schnittpunktgeradekugel(const _tg*go,const _tg*gv,const _tg*ko,_tg r,_tg*e,_tg&parameter){
                                _tg h[3];
                                ::subtrahieren(h,go,ko);
                                _tg hgv=::produkt(h,gv);
                                _tg gvgv=::produkt(gv,gv);
                                _tg d=pow((2*hgv),2) -4*gvgv*(::produkt(h,h)-(r*r));
                                if(d>=0){
                                 _tg t1=(-2*hgv+sqrt(d))/(2*gvgv);
                                 _tg t2=(-2*hgv-sqrt(d))/(2*gvgv);
                                 if((t1>=0)&&(t1<=1)){
                                  if((t2>=0)&&(t2<=1)){
                                   //beide drin
                                   if(t1<t2){
                                    parameter=t1;
                                   }else{
                                    parameter=t2;
                                   };
                                   e[0]=go[0]+gv[0]*parameter;
                                   e[1]=go[1]+gv[1]*parameter;
                                   e[2]=go[2]+gv[2]*parameter;
                                   return(true);
                                  }else{
                                   //t1 drin , t2 draussen
                                   parameter=t1;
                                   e[0]=go[0]+gv[0]*parameter;
                                   e[1]=go[1]+gv[1]*parameter;
                                   e[2]=go[2]+gv[2]*parameter;
                                   return(true);
                                  };
                                 }else{
                                  if((t2>=0)&&(t2<=1)){
                                   //t1 draussen, t2 drin
                                   parameter=t2;
                                   e[0]=go[0]+gv[0]*parameter;
                                   e[1]=go[1]+gv[1]*parameter;
                                   e[2]=go[2]+gv[2]*parameter;
                                   return(true);
                                  }else{
                                   //t1 draussen, t2 draussen
                                   return(false);
                                  };
                                 };
                                }else{
                                 return(false);
                                };
};
//*************************************************************************************************************************************************************************************************
//                                                              V E C T O R A N A L Y S I S
//*************************************************************************************************************************************************************************************************
template<class _tg> class _vektoranalysis{
        public:
                _vektoranalysis(unsigned int);
                void lotpunktgerade(const _vektor<_tg>&,const _vektor<_tg>&,const _vektor<_tg>&,_vektor<_tg>&)const;
                void lotpunktgerade(const _vektor<_tg>&,const _vektor<_tg>&,const _vektor<_tg>&,_vektor<_tg>&,_tg&)const;
                void reflektierenpunktnormale(const _vektor<_tg>&,const _vektor<_tg>&,const _vektor<_tg>&,_vektor<_tg>&);
                char reflektierenvektorkugel(const _vektor<_tg>&,_vektor<_tg>&,const _vektor<_tg>&,_tg);
                char reflektierenvektorrand(const _vektor<_tg>&,_vektor<_tg>&,int,_tg,int,_tg,_tg);
        private:
                unsigned int dim;
};
template<class _tg> _vektoranalysis<_tg>::_vektoranalysis(unsigned int d){
                                                                if(d==0) d=1;
                                                                dim=d;
};
template <class _tg> void _vektoranalysis<_tg>::lotpunktgerade(const _vektor<_tg>&x,const _vektor<_tg>&o,const _vektor<_tg>&v,_vektor<_tg>&e)const{
                                                                //gibt das lot des punktes x auf
                                                                //die gerade g:=o + v*parameter
                                                                //ergebins landet in e
                                                                if(v.laengelaenge()!=0){
                                                                 e=(o-x)+v*(((x-o)*v)/(v*v));
                                                                };
                                                                
                                                                
};
template <class _tg> void _vektoranalysis<_tg>::lotpunktgerade(const _vektor<_tg>&x,const _vektor<_tg>&o,const _vektor<_tg>&v,_vektor<_tg>&e,_tg&parameter)const{
                                                                //gibt das lot des punktes x auf
                                                                //die gerade g:=o + v*parameter
                                                                //ergebins landet in e
                                                                
                                                                if(v.laengelaenge()!=0){
                                                                 parameter=(((x-o)*v)/(v*v));
                                                                 e=(o-x)+v*parameter;
                                                                };
};
template <class _tg> void _vektoranalysis<_tg>::reflektierenpunktnormale(const _vektor<_tg>&x,const _vektor<_tg>&o,const _vektor<_tg>&n,_vektor<_tg>&e){
                                                                lotpunktgerade(x,o,n,e);
                                                                e=(e*2)+x;
};
template <class _tg> char _vektoranalysis<_tg>::reflektierenvektorkugel(const _vektor<_tg>&ort,_vektor<_tg>&vektor,const _vektor<_tg>&mm,_tg radius){
                                                                _tg l;
                                                                _vektor<_tg> e(0);
                                                                e.konvertieren(dim);
                                                                //----------
                                                                l=vektor.laenge();
                                                                if(hitlinesphere(ort,vektor,mm,radius,e)){
                                                                 reflektierenpunktnormale(ort,e,e-mm,vektor);
                                                                 vektor.normalisieren();
                                                                 vektor*=l;
                                                                 return(1);
                                                                };
                                                                return(0);
};
template <class _tg> char _vektoranalysis<_tg>::reflektierenvektorrand(const _vektor<_tg>&ort,_vektor<_tg>&vektor,int i,_tg b,int j,_tg min,_tg max){
                                                                char r;
                                                                _tg a1;
                                                                _tg a2;
                                                                //--------
                                                                r=0;
                                                                if(vektor[i]!=0){
                                                                 a1=(b-ort[i])/vektor[i];
                                                                 if((a1>=0)&&(a1<=1)){
                                                                  a2=ort[j]+a1*vektor[j];
                                                                  if((a2>=min)&&(a2<=max)){
                                                                   vektor.mul(i,-1);
                                                                   r=1;
                                                                  };
                                                                 };
                                                                };
                                                                return(r);
};



/*
template<class _tg> class _vectoranalysis1d:public _vektoranalysis<_tg>{
        public:
                _vectoranalysis1d();
};
template<class _tg> _vectoranalysis1d<_tg>::_vectoranalysis1d():_vektoranalysis<_tg>(1){
};
*/
//*************************************************************************************************************************************************************************************************
//                                                              V E C T O R A N A L Y S I S  -  2D
//*************************************************************************************************************************************************************************************************
template<class _tg> class _vektoranalysis2{
        public:
                _vektoranalysis2();
                void berechnenorthogonalenvektor(const _vektor2<_tg>&,_vektor2<_tg>&);
                _tg determinieren(const _vektor2<_tg>&,const _vektor2<_tg>&);
                void lotpunktgerade(const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&,_vektor2<_tg>&)const;
                void lotpunktgerade(const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&,_vektor2<_tg>&,_tg&)const;
                
};
template<class _tg> _vektoranalysis2<_tg>::_vektoranalysis2(){
};
template <class _tg> void _vektoranalysis2<_tg>::berechnenorthogonalenvektor(const _vektor2<_tg>&a,_vektor2<_tg>&b){
                                                                //ax*bx+ay*by==0
                                                                //1) bx=(-ay*by)/ax else
                                                                //2) by=(-ax*bx)/ay
                                                                if(fabs(a[0])>fabs(a[1])){
                                                                 b.setzen((-a[1]*b[1])/a[0],1);
                                                                }else{
                                                                 b.setzen(1,(-a[0]*b[0])/a[1]);
                                                                };
};
template<class _tg>_tg _vektoranalysis2<_tg>::determinieren(const _vektor2<_tg>&a,const _vektor2<_tg>&b){
                                                                                        return(a[0]*b[1]-a[1]*b[0]);
};
template <class _tg> void _vektoranalysis2<_tg>::lotpunktgerade(const _vektor2<_tg>&x,const _vektor2<_tg>&o,const _vektor2<_tg>&v,_vektor2<_tg>&e)const{
                                                                //gibt das lot des punktes x auf
                                                                //die gerade g:=o + v*parameter
                                                                //ergebins landet in e
                                                                if(v.laengelaenge()!=0){
                                                                 e=(o-x)+v*(((x-o)*v)/(v*v));
                                                                };
                                                                
                                                                
};
template <class _tg> void _vektoranalysis2<_tg>::lotpunktgerade(const _vektor2<_tg>&x,const _vektor2<_tg>&o,const _vektor2<_tg>&v,_vektor2<_tg>&e,_tg&parameter)const{
                                                                //gibt das lot des punktes x auf
                                                                //die gerade g:=o + v*parameter
                                                                //ergebins landet in e
                                                                
                                                                if(v.laengelaenge()!=0){
                                                                 parameter=(((x-o)*v)/(v*v));
                                                                 e=(o-x)+v*parameter;
                                                                };
};

//*************************************************************************************************************************************************************************************************
//                                                              V E C T O R A N A L Y S I S  -  3D
//*************************************************************************************************************************************************************************************************
template<class _tg> class _vektoranalysis3{
        public:
                _vektoranalysis3();
                _tg determinieren(const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor3<_tg>&);
                void berechnenorthogonalenvektor(const _vektor3<_tg>&,_vektor3<_tg>&);
                void lotpunktgerade(const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor3<_tg>&,_vektor3<_tg>&)const;
                void lotpunktgerade(const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor3<_tg>&,_vektor3<_tg>&,_tg&)const;
                char vektorraumparameter(const _vektor3<_tg>&,const _vektorraum<_tg>*,_tg[3]);
                char innerhalbvektorraum(const _vektor3<_tg>&,const _vektorraum<_tg>*);
                void rotieren(_vektor3<_tg>,const _vektor3<_tg>&,_tg,_vektor3<_tg>&);
                void lotpunktebene(const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor3<_tg>&,_vektor3<_tg>&,_tg&);
                _tg lotgeradegerade(const _vektor3<_tg>&x1,const _vektor3<_tg>&v1,const _vektor3<_tg>&x2,const _vektor3<_tg>&v2,_vektor3<_tg>&e);
                bool schnittpunktgeradezylinder(const _vektor3<_tg>&ort,const _vektor3<_tg>&vektor,const _vektor3<_tg>& zylort,const _vektor3<_tg>&zylachse,const _tg&zylradius,_tg&parameterg,_tg&parameterz,_vektor3<_tg>&normale,_vektor3<_tg>&ortneu);
                bool schnittpunktgeradekugel(const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor3<_tg>&,_tg,_vektor3<_tg>&,_tg&);
                void reflektierenpunktnormale(const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor3<_tg>&,_vektor3<_tg>&);
                bool kugelinnerhalbpunktrotation(const _vektor3<_tg>&kugelort,const _tg radius,const _vektor3<_tg>&punkt,const _vektor3<_tg>&achsenort,const _vektor3<_tg>&achse,const _tg winkelschritt);
                bool zylinderinnerhalbpunktrotation(const _vektor3<_tg>&zylinderort,const _vektor3<_tg>&zylinderachse,const _tg radius,const _vektor3<_tg>&punkt,const _vektor3<_tg>&achsenort,const _vektor3<_tg>&achse,const _tg winkelschritt);
};
template<class _tg>_vektoranalysis3<_tg>::_vektoranalysis3(){
};
template <class _tg> void _vektoranalysis3<_tg>::berechnenorthogonalenvektor(const _vektor3<_tg>&v,_vektor3<_tg>&e){
                                                               // _vektor3<_tg> n;
                                                                e.setzen(0,0,0);
                                                                e.setzenkomponente(v.niedrigsterindex(),1);
                                                                e= e % v;
                                                                e.normalisieren();
};
template<class _tg> _tg _vektoranalysis3<_tg>::determinieren(const _vektor3<_tg>&a,const _vektor3<_tg>&b,const _vektor3<_tg>&c){
                                                                return(
                                                                +a[0]* ( b[1]*c[2] - c[1]*b[2])
                                                                +a[1]* (-b[0]*c[2] + c[0]*b[2])
                                                                +a[2]* ( b[0]*c[1] - c[0]*b[1]));
};
template <class _tg> void _vektoranalysis3<_tg>::lotpunktgerade(const _vektor3<_tg>&x,const _vektor3<_tg>&o,const _vektor3<_tg>&v,_vektor3<_tg>&e)const{
                                                                //gibt das lot des punktes x auf
                                                                //die gerade g:=o + v*parameter
                                                                //ergebins landet in e
                                                                if(v.laengelaenge()!=0){
                                                                 e=(o-x)+v*(((x-o)*v)/(v*v));
                                                                };
};
template <class _tg> void _vektoranalysis3<_tg>::lotpunktgerade(const _vektor3<_tg>&x,const _vektor3<_tg>&o,const _vektor3<_tg>&v,_vektor3<_tg>&e,_tg&parameter)const{
                                                                //gibt das lot des punktes x auf
                                                                //die gerade g:=o + v*parameter
                                                                //ergebins landet in e
                                                                if(v.laengelaenge()!=0){
                                                                 parameter=(((x-o)*v)/(v*v));
                                                                 e=(o-x)+v*parameter;
                                                                };
};
template <class _tg> char _vektoranalysis3<_tg>::vektorraumparameter(const _vektor3<_tg>&p,const _vektorraum<_tg>*r,_tg a[3]){
                                                                _tg D;
                                                                _vektor3<_tg> h=p-*r;
                                                                //------
                                                                a[0]=0;
                                                                a[1]=0;
                                                                a[2]=0;
                                                                D=determinieren(r->x(),r->y(),r->z());
                                                                if(D){
                                                                 a[0]=determinieren(h,r->y(),r->z())/D;
                                                                 a[1]=determinieren(r->x(),h,r->z())/D;
                                                                 a[2]=determinieren(r->x(),r->y(),h)/D;
                                                                 return(1);
                                                                };
                                                                return(0);
};
template <class _tg> char _vektoranalysis3<_tg>::innerhalbvektorraum(const _vektor3<_tg>&p,const _vektorraum<_tg>*r){
                                                                _tg a[3];
                                                                //------
                                                                if(vektorraumparameter(p,r,a)){
                                                                 if((a[0]>0)&&(a[0]<=1)&&(a[1]>0)&&(a[1]<=1)&&(a[2]>0)&&(a[2]<=1)) return(1);
                                                                };
                                                                return(0);
};
template <class _tg> void _vektoranalysis3<_tg>::rotieren(_vektor3<_tg> v,const _vektor3<_tg>&p,_tg w,_vektor3<_tg>&e){
                                                                _tg a,b;
                                                                _tg matrix[3][3];
                                                                _tg sinw,cosw;
                                                                int x=0,y=1,z=2;
                                                                int i;
                                                                //------------
                                                                v.normalisieren();
                                                                sinw=sin(w*_ph);
                                                                cosw=cos(w*_ph);
                                                                a=sinw;
                                                                b=1-cosw;
                                                                matrix[0][0]=cosw+b*v[x]*v[x];
                                                                matrix[1][0]=     b*v[x]*v[y]+a*+v[z];
                                                                matrix[2][0]=     b*v[x]*v[z]+a*-v[y];
                                                                matrix[0][1]=     b*v[y]*v[x]+a*-v[z];
                                                                matrix[1][1]=cosw+b*v[y]*v[y];
                                                                matrix[2][1]=     b*v[y]*v[z]+a*+v[x];
                                                                matrix[0][2]=     b*v[z]*v[x]+a*+v[y];
                                                                matrix[1][2]=     b*v[z]*v[y]+a*-v[x];
                                                                matrix[2][2]=cosw+b*v[z]*v[z];
                                                                for(i=0;i<3;i++) e.setzenkomponente(i,(matrix[0][i]*p[x]+matrix[1][i]*p[y]+matrix[2][i]*p[z]));
};
template <class _tg> void _vektoranalysis3<_tg>::lotpunktebene(const _vektor3<_tg>&x,const _vektor3<_tg>&o,const _vektor3<_tg>&n,_vektor3<_tg>&l,_tg&a){
                                                                _vektor3<_tg> h;
                                                                //--------------
                                                                h=x-o;
                                                                a=h*n;
                                                                l=n*-a;
};
template <class _tg> _tg _vektoranalysis3<_tg>::lotgeradegerade(const _vektor3<_tg>&x1,const _vektor3<_tg>&v1,const _vektor3<_tg>&x2,const _vektor3<_tg>&v2,_vektor3<_tg>&lot){
                                                                _vektor3<_tg> n=v1%v2;
                                                                _tg nl=n.laenge();
                                                                _tg abstand=(n*(x2-x1))/nl;
                                                                lot=n*(abstand/nl);
                                                                return(abstand);
};
template <class _tg> bool _vektoranalysis3<_tg>::schnittpunktgeradezylinder(
                                                                
                                                                const _vektor3<_tg>&ort,
                                                                const _vektor3<_tg>&vektor,
                                                                const _vektor3<_tg>&zylort,
                                                                const _vektor3<_tg>&zylachse,
                                                                const _tg&zylradius,
                                                                _tg&parameterg,
                                                                _tg&parameterz,
                                                                _vektor3<_tg>&normale,
                                                                _vektor3<_tg>&ortneu){
                                                                /*
                                                                _vektor3<_tg> diff;
                                                                _vektor3<_tg> U;
                                                                _vektor3<_tg> V;
                                                                _vektor3<_tg> W;
                                                                unsigned int gi;
                                                                _vektor3<_tg> p;
                                                                _vektor3<_tg> d;
                                                                
                                                                //------------------------------
                                                                W=zylachse;
                                                                diff=ort-zylort;
                                                                gi=zylachse.groessterindex();
                                                                if(gi==0) {
                                                                 //gesucht ist UX
                                                                 U.setzen(0,1,1); 
                                                                 U.setzenkomponente(0,(-zylachse[1]*U[1] - zylachse[2]*U[2])/zylachse[0]);
                                                                }else
                                                                if(gi==1) {
                                                                 //gesucht ist UY
                                                                 U.setzen(1,0,1); 
                                                                 U.setzenkomponente(1,(-zylachse[0]*U[0] - zylachse[2]*U[2])/zylachse[1]);
                                                                }else{
                                                                 //gesucht ist UZ
                                                                 U.setzen(1,1,0);
                                                                 U.setzenkomponente(2,(-zylachse[0]*U[0] - zylachse[1]*U[1])/zylachse[2]);
                                                                };
                                                                U.normalisieren();
                                                                V=U%zylachse;
                                                                V.normalisieren();
                                                                W.normalisieren();
                                                                L->schreiben("Gi=",(int)gi);
                                                                L->schreiben("U=",U);
                                                                L->schreiben("V=",V);
                                                                L->schreiben("W=",W);
                                                                //die vektoren diff und vektor in das zylinderkoordinaten system transformieren
                                                                p.setzen(diff*U,diff*V,diff*W);
                                                                _vektor3<_tg> vn=vektor;
                                                                vn.normalisieren();
                                                                //_tg vektorW=vn*W;
                                                                if(fabs(vn*W)>=(1-nahenull)){
                                                                 //parallelität zwischen zylachse und vektor
                                                                 //genauer untersuchen, ob punkt den kreis berührt !!!!!!!!!!!!!!!!!!!!!!!!!!
                                                                 L->schreiben("Parallel");

                                                                 return(false);
                                                                }else{
                                                                 //nicht parallel, diskriminante bestimmen etc... (carmen hat gemacht und ist verantwortlich)
                                                                 
                                                                 d.setzen(vektor*U,vektor*V,vektor*W);
                                                                 L->schreiben("nicht parallel");
                                                                 L->schreiben("d=",d);
                                                                 L->schreiben("p=",p);
                                                                 _tg D,px,py,dx,dy,l0,l1,r,fA0,fA1,fA2,fRoot,fInv;                                                                 
                                                                 px=p[0];
                                                                 py=p[1];
                                                                 dx=d[0];
                                                                 dy=d[1];
                                                                 r=zylradius;
                                                                 
                                                                 
                                                                 //fA0 = px*px + py*py - r*r;
                                                                 //fA1 = px*dx + py*dy;
                                                                 //fA2 = dx*dx + dy*dy;//kD.X()*kD.X() + kD.Y()*kD.Y();                                                       
                                                                 //D= fA1*fA1 - fA0*fA2;
                                                                 //if(D<0.0f){
                                                                 // fRoot = sqrt(D);
                                                                 // fInv = 1.0f/fA2;
                                                                 // l0=(-fA1-fRoot)*fInv;
                                                                 // l1=(-fA1+fRoot)*fInv;
                                                                 
                                                                 D=8*px*dx*py*dy-4*dx*dx*py*py+4*dx*dx*r*r-4*dy*dy*px*px+4*dy*dy*r*r;
                                                                 L->schreiben("D=",D);
                                                                 if(D>=0.0f){
                                                                  
                                                                  l0=(-2*(px*dx+py*dy) + sqrt(D))/(2*(dx*dx+dy*dy));
                                                                  l1=(-2*(px*dx+py*dy) - sqrt(D))/(2*(dx*dx+dy*dy));
                                                                  L->schreiben("L0=",l0);
                                                                  L->schreiben("L1=",l1);


                                                                  if((l0>=0)&&(l0<=1)){
                                                                   if((l1>=0)&&(l1<=1)){
                                                                    //beide drin
                                                                    if(l0<l1){
                                                                     parameterg=l0;
                                                                    }else{
                                                                     parameterg=l1;
                                                                    };
                                                                   }else{
                                                                    //l0 drin , l1 draussen
                                                                    parameterg=l0;
                                                                   };
                                                                  }else{
                                                                   if((l1>=0)&&(l1<=1)){
                                                                    //l0 draussen, l1 drin
                                                                    parameterg=l1;
                                                                   }else{
                                                                    //l0 draussen, l1 draussen
                                                                    return(false);
                                                                   };
                                                                  };
                                                                 
                                                                 
                                                                  ortneu=ort+vektor*parameterg;
                                                                  lotpunktgerade(ortneu,zylort,zylachse,normale,parameterz);
                                                                  normale*=-1.0f;
                                                                  normale.normalisieren();
                                                                  return(true);
                                                                  
                                                                 
                                                                 }else{
                                                                  //kein schnitt
                                                                  return(false);
                                                                 };
                                                                };
                                                                
                                                                return(false);//ende
                                                               
                                                                */
                                                                _vektor3<_tg> RC;
	                                                            _tg d;
	                                                            _tg t,s;
	                                                            _vektor3<_tg> n,D,O;
	                                                            _tg ln;
	                                                            _tg in,out;
	                                                            //---------------------
	                                                            RC=ort-zylort;//TVector::subtract(position,cylinder._Position,RC);
	                                                            n=vektor%zylachse;//TVector::cross(direktion,cylinder._Axis,n);
                                                                ln=n.laenge();//ln=n.mag();
                                                            	if((ln<nahenull)&&(ln>-nahenull)) return false;
                                                            	n.normalisieren();//n.unit();
	                                                            d=fabs(RC*n);
                                                                if(d<=zylradius){
		                                                         O=RC%zylachse;//TVector::cross(RC,cylinder._Axis,O);
		                                                         t=-(O*n)/ln;
		                                                         O=n%zylachse;//TVector::cross(n,cylinder._Axis,O);
		                                                         O.normalisieren();
		                                                         s=fabs( sqrt(zylradius*zylradius - d*d) / (vektor*O));
		                                                         
		                                                         
		                                                         _tg l0,l1;
		                                                         l0=in=t-s;
		                                                         l1=out=t+s;
		                                                         //L->schreiben("d<=radius");
		                                                         //peep(10);
		                                                         
		                                                          if((l0>=0)&&(l0<=1)){
                                                                   if((l1>=0)&&(l1<=1)){
                                                                    //beide drin
                                                                    if(l0<l1){
                                                                     parameterg=l0;
                                                                    }else{
                                                                     parameterg=l1;
                                                                    };
                                                                   }else{
                                                                    //l0 drin , l1 draussen
                                                                    parameterg=l0;
                                                                   };
                                                                  }else{
                                                                   if((l1>=0)&&(l1<=1)){
                                                                    //l0 draussen, l1 drin
                                                                    parameterg=l1;
                                                                   }else{
                                                                    //l0 draussen, l1 draussen
                                                                    return(false);
                                                                   };
                                                                  };     
		                                                         
                                                         		/* if(in<-nahenull){
			                                                      if(out<-nahenull) return false; else parameterg=out;
		                                                         }else if (out<-nahenull){
			                                                      parameterg=in;
		                                                         }else if (in<out) parameterg=in; else parameterg=out;
		                                                         */
		                                    
		                                                         
                                                             	 ortneu=ort+vektor*parameterg;//newposition=position+direktion*lamda;
		                                                         //_vektor3<_tg> HB=ortneu-zylort;//TVector HB=newposition-cylinder._Position;
		                                                         //normale=HB-zylachse*(HB*zylachse);
		                                                         //normale.normalisieren();
                                                         		 return true;
	                                                            };
                                                              	return false;
                                                              	
                                                              	
                                                               
};                                                               
                                                               
template <class _tg> bool _vektoranalysis3<_tg>::schnittpunktgeradekugel(const _vektor3<_tg>&go,const _vektor3<_tg>&gv,const _vektor3<_tg>&ko,_tg r,_vektor3<_tg>&e,_tg&parameter){
                                                                
                                                                _vektor3<_tg> h=go-ko;
                                                                _tg d=pow((2*(h*gv)),2) -4*(gv*gv)*((h*h)-(r*r));
                                                                if(d>=0){
                                                                
                                                                 _tg t1=(-2*(h*gv)+sqrt(d))/(2*(gv*gv));
                                                                 _tg t2=(-2*(h*gv)-sqrt(d))/(2*(gv*gv));
                                                                  
                                                                 if((t1>=0)&&(t1<=1)){
                                                                  if((t2>=0)&&(t2<=1)){
                                                                   //beide drin
                                                                   if(t1<t2){
                                                                    parameter=t1;
                                                                   }else{
                                                                    parameter=t2;
                                                                   };
                                                                   e=go+gv*parameter;
                                                                   return(true);
                                                                  }else{
                                                                   //t1 drin , t2 draussen
                                                                   parameter=t1;
                                                                   e=go+gv*parameter;
                                                                   return(true);
                                                                  };
                                                                 }else{
                                                                  if((t2>=0)&&(t2<=1)){
                                                                   //t1 draussen, t2 drin
                                                                   parameter=t2;
                                                                   e=go+gv*parameter;
                                                                   return(true);
                                                                  }else{
                                                                   //t1 draussen, t2 draussen
                                                                   return(false);
                                                                  };
                                                                 };
                                                                }else{
                                                                 return(false);
                                                                };
                                                                
                                                                
                                                                
                                                                
                                                                
                                                                
                                                                
                                                                
                                                                
                                                                
                                                                
                                                                
                                                                
                                                                
                                                                
                                                                
                                                                
                                                                /*
                                                                
                                                                
                                                                
                                                                
                                                                _vektor3<_tg> diff=o-m;//Vector3<Real> kDiff = m_rkLine.Origin - m_rkSphere.Center;
                                                                _tg fA0=diff*diff-r*r;//fA0=Diff.Dot(kDiff) - m_rkSphere.Radius*m_rkSphere.Radius;
                                                                _tg fA1=a*diff;// fA1 = m_rkLine.Direction.Dot(kDiff);
                                                                _tg fDiscr=fA1*fA1 - fA0;//Real fDiscr = fA1*fA1 - fA0;

                                                                if(fDiscr<(_tg)0.0f){//if (fDiscr < (Real)0.0){
                                                                 return(false);//m_iQuantity = 0;
                                                                }else if(fDiscr >= nahenull){//Math<Real>::ZERO_TOLERANCE){
                                                                 _tg fRoot=sqrt(fDiscr);//Real fRoot = Math<Real>::Sqrt(fDiscr);
                                                                 _tg t0=-fA1-fRoot;//m_afLineT[0] = -fA1 - fRoot;
                                                                 _tg t1=-fA1+fRoot;//m_afLineT[1] = -fA1 + fRoot;
                                                                 _tg h;
                                                                 L->schreiben("T0=",t0);
                                                                 L->schreiben("T1=",t1);
                                                                // if(t0>t1) {h=t0;t0=t1;t1=h;};
                                                                 e=o+a*t0;//m_akPoint[0] = m_rkLine.Origin + m_afLineT[0]*m_rkLine.Direction;
                                                                          //m_akPoint[1] = m_rkLine.Origin + m_afLineT[1]*m_rkLine.Direction;
                                                                 parameter=t0;
                                                                 //m_iQuantity = 2;
                                                                 //L->schreiben("schnittpunktkugel");
                                                                 return(true);
                                                                }else{
                                                                 parameter=-fA1;//m_afLineT[0] = -fA1;
                                                                 e=o+a*parameter;//m_akPoint[0] = m_rkLine.Origin + m_afLineT[0]*m_rkLine.Direction;
                                                                 return(true);
                                                                 //m_iQuantity = 1;
                                                                };
                                                                //return m_iQuantity > 0;
                                                                */
};
                                                                
                                                                
                                                                
                                                                
                                                                
                                                                
                                                                
                                                                
  /*                                                              
                                                                
                                                                
                                                                bool ret;
                                                                _tg aa;
                                                                _tg p;
                                                                _tg ph;
                                                                _tg q;
                                                                _tg term;
                                                                _tg f;
                                                                _tg a0;
                                                                _tg a1;
                                                                //----------
                                                                f=2;
                                                                ret=false;
                                                                
                                                                aa=a*a;
                                                                p=(+f*(o*a) - f*(a*m))/aa;
                                                                q=(-f*(m*o)+(o*o)+(m*m)-(r*r))/aa;
                                                                ph=p/f;
                                                                term=ph*ph-q;
                                                                if(term>=0){
                                                                 term=sqrt(term);
                                                                 a0=-ph+term;
                                                                 a1=-ph-term;
                                                                 if((a1<a0)&&(a1>-nahenull)) a0=a1;
                                                                 if((a0>-nahenull)&&(a0<=nahenull)){
                                                                  parameter=a0;
                                                                  e=o+a*a0;
                                                                  L->schreiben("schnittpunktkugel");
                                                                  ret=true;
                                                                 };
                                                                };
                                                                return(ret);
};
*/
template <class _tg> void _vektoranalysis3<_tg>::reflektierenpunktnormale(const _vektor3<_tg>&x,const _vektor3<_tg>&o,const _vektor3<_tg>&n,_vektor3<_tg>&e){
                                                                lotpunktgerade(x,o,n,e);
                                                                e=(e*2)+x;
};
template <class _tg> bool _vektoranalysis3<_tg>::kugelinnerhalbpunktrotation(const _vektor3<_tg>&kugelort,const _tg radius,const _vektor3<_tg>&punkt,const _vektor3<_tg>&achsenort,const _vektor3<_tg>&achse,const _tg winkelschritt){
                                                                //vorab-prüfungen zur beschleunigung
                                                                //achse sollte normalisiert sein !
                                                                //1. lot auf die rotationsebene:
                                                                _vektor3<_tg> rotebenenlot;
                                                                _tg para;
                                                                lotpunktebene(kugelort,punkt,achse,rotebenenlot,para);
                                                                if(fabs(para)>(radius+nahenull)) return(false);//zu weit von der ebene
                                                                //vorab-prüfungen zur beschleunigung
                                                                //2. lot auf die rotationsachse
                                                                _vektor3<_tg> rotachsenlot;
                                                                _vektor3<_tg> punktvektor=punkt-achsenort;
                                                            //    punktvektor.projizieren(achse);
                                                                _tg punktradius=punktvektor.laenge();
                                                                lotpunktgerade(kugelort,achsenort,achse,rotachsenlot,para);
                                                                para=rotachsenlot.laenge();
                                                                if(fabs(para-punktradius)>(radius+nahenull)) return(false);//zu weit von der kreisbahn 
                                                                //es wurde bereits eine art "quadertorus" abgefangen
                                                                //nun genauere lotprüfuungen des kugelorts auf die kreisbahn
                                                                //und winkelschrittdiskretion prüfen
                                                                _vektor3<_tg> raln=-rotachsenlot;
                                                                raln.normalisieren();
                                                                raln*=punktradius;
                                                                _vektor3<_tg> kokb=kugelort+rotachsenlot+rotebenenlot+raln;
                                                                _vektor3<_tg> abstandkugelkreis=kokb-kugelort;
                                                                para=abstandkugelkreis.laenge();
                                                                if(para>(radius+nahenull)) return(false);//zu weit von der kreisbahn
                                                                //diskretion des abschnitts 
                                                                //ohne kugelenden prüfen
                                                                _tg ws=punktvektor.winkel(raln);
                                                                _vektor3<_tg> r90;
                                                                _vektor3<_tg> pvn=punktvektor;
                                                                pvn.normalisieren();
                                                                r90=achse%pvn;
                                                                if((raln*r90)<0) ws=(180-ws)+180;
                                                                if(ws<=fabs(winkelschritt)) return(true);//innerhalb der diskreten kreisbahn
                                                                //kugelenden prüfen
                                                                _vektor3<_tg> h=kugelort-punkt;
                                                                if(h.laenge()<(radius+nahenull)) return(true);//innerhalb startpunkt
                                                                rotieren(achse,punktvektor,ws,h);//kostet viel zeit
                                                                h=(punkt-punktvektor)+h;
                                                                h-=kugelort;
                                                                if(h.laenge()<(radius+nahenull)) return(true);//innerhalb endepunkt
                                                                return(false);
};
template <class _tg> bool _vektoranalysis3<_tg>::zylinderinnerhalbpunktrotation(const _vektor3<_tg>&zylinderort,const _vektor3<_tg>&zylinderachse,const _tg radius,const _vektor3<_tg>&punkt,const _vektor3<_tg>&achsenort,const _vektor3<_tg>&achse,const _tg winkelschritt){
                                                                return(false);
};


//*************************************************************************************************************************************************************************************************
//                                                              D Y N A M I S C H E R   V E C T O R 
//*************************************************************************************************************************************************************************************************
template <class _tg> class _vektor{
        public:
                inline _vektor();
                inline _vektor(const _vektor&);
                inline _vektor(unsigned int);
              //  inline _vektor(_tg);
                inline _vektor(_tg,_tg);
                inline _vektor(_tg,_tg,_tg);
                _vektor(_tg,_tg,_tg,_tg);
                inline void setzen(const _vektor&);
               // inline void setzen(_tg);
                inline void setzen(_tg,_tg);
                inline void setzen(_tg,_tg,_tg);
                void setzen(_tg,_tg,_tg,_tg);
                inline void setzenkomponente(unsigned int,_tg);
                inline _tg holen(unsigned int i) const;
                inline unsigned int holendimension() const;
                inline unsigned int dimension() const;
                inline void redimensionieren(unsigned int);
                unsigned int groessterindex() const;
                unsigned int niedrigsterindex() const;
                inline virtual ~_vektor();
                inline void kopieren(const _vektor&);
                inline _tg*daten();
                //------------------------------
        protected:
                inline void init();
                inline void loeschen();
                inline void erzeugen(unsigned int);
        public:
                inline _vektor operator+(const _vektor&) const;
                inline _vektor& operator+=(const _vektor&);
                inline _vektor operator-(const _vektor&) const;
                inline _vektor& operator-=(const _vektor&);
                inline _vektor operator-() const;
                inline _tg operator*(const _vektor&) const;
                inline _vektor operator*(_tg) const;
                inline _vektor&operator*=(_tg);
                inline _vektor&operator=(const _vektor&);
                inline bool operator==(const _vektor&) const;
                inline _tg operator[](unsigned int) const;
                inline _vektor operator%(const _vektor&) const;
                inline _vektor& operator%=(const _vektor&);
                //----------------------------------
                inline void add(const _vektor&);
                inline void add(unsigned int,_tg);
                inline void sub(const _vektor&);
                inline void subinv(const _vektor&);
                inline void sub(unsigned int,_tg);
                inline void subinv(unsigned int,_tg);
                inline _tg mul(const _vektor&) const;
                inline void mul(_tg);
                inline void mul(unsigned int,_tg);
                inline _tg normalisieren();
                inline _tg laenge() const;
                inline _tg laengelaenge() const;
                inline void kreuzprodukt(const _vektor&);
                inline _tg produkt(const _vektor&);
                inline void rotx(_tg);
                inline void roty(_tg);
                inline void rotz(_tg);
                inline void begrenzen(_tg,_tg);
                inline void zufall();
                inline _tg winkel(const _vektor&) const;
                inline void tauschen(unsigned int,unsigned int);
                char konvertieren(unsigned int);
                char konvertieren(unsigned int,const _vektor<unsigned int>&);
                char konvertierenniedriger(unsigned int,const _vektor<unsigned int>&);
                char konvertierenhoeher(unsigned int,const _vektor<unsigned int>&);
        private:
                _tg*o;
                unsigned int dim;
};
//************************************************************* V E C T O R :: B A S I S O P E R A T I O N E N *********************************************************************
template <class _tg>_vektor<_tg>::_vektor(){
                                                                init();
                                                                setzen(0,0,0);
};
template <class _tg>_vektor<_tg>::_vektor(const _vektor<_tg>&x){
                                                                init();
                                                                kopieren(x);
};
template <class _tg>_vektor<_tg>::_vektor(unsigned int x){
                                                                init();
                                                                if(x<1) x=1;
                                                                redimensionieren(x);
};
/*
template <class _tg>_vektor<_tg>::_vektor(_tg x){
                                                                init();
                                                                setzen(x);
};
*/
template <class _tg>_vektor<_tg>::_vektor(_tg x,_tg y){
                                                                init();
                                                                setzen(x,y);
};
template <class _tg>_vektor<_tg>::_vektor(_tg x,_tg y,_tg z){
                                                                init();
                                                                setzen(x,y,z);
};
template <class _tg>_vektor<_tg>::_vektor(_tg x,_tg y,_tg z,_tg a){
                                                                init();
                                                                redimensionieren(4);
                                                                o[0]=x;
                                                                o[1]=y;
                                                                o[2]=z;
                                                                o[3]=a;
};
template <class _tg> void _vektor<_tg>::setzen(const _vektor<_tg>&x){
                                                                kopieren(x);
};
/*
template <class _tg> void _vektor<_tg>::setzen(_tg x){
                                                                redimensionieren(1);
                                                                o[0]=x;

};
*/
template <class _tg> void _vektor<_tg>::setzen(_tg x,_tg y){
                                                                redimensionieren(2);
                                                                o[0]=x;
                                                                o[1]=y;

};
template <class _tg> void _vektor<_tg>::setzen(_tg x,_tg y,_tg z){
                                                                redimensionieren(3);
                                                                o[0]=x;
                                                                o[1]=y;
                                                                o[2]=z;
};
template <class _tg> void _vektor<_tg>::setzen(_tg x,_tg y,_tg z,_tg a){
                                                                redimensionieren(4);
                                                                o[0]=x;
                                                                o[1]=y;
                                                                o[2]=z;
                                                                o[3]=a;
};
template <class _tg>void _vektor<_tg>::setzenkomponente(unsigned int i,_tg x){
                                                                if(i<dim){
                                                                 o[i]=x;
                                                                };
};
template <class _tg>_vektor<_tg>::~_vektor(){
                                                                loeschen();
};
template<class _tg> _tg _vektor<_tg>::holen(unsigned int i) const{
                                                                if(i>=dim){
                                                                 return(0);
                                                                };
                                                                if(o){
                                                                 return(o[i]);
                                                                }else{
                                                                 return(0);
                                                                };
};
template <class _tg> unsigned int _vektor<_tg>::holendimension() const{
                                                                return(dim);
};
template <class _tg> unsigned int _vektor<_tg>::dimension() const{
                                                                return(dim);
};
template <class _tg> unsigned int _vektor<_tg>::groessterindex() const{
                                                                unsigned int max;
                                                                unsigned int i;
                                                                _tg maxvalue;
                                                                _tg t;
                                                                //---------------
                                                                max=0;
                                                                maxvalue=0;
                                                                for(i=0;i<dim;i++){
                                                                 if(o[i]<0) t=-o[i]; else t=o[i];
                                                                 if(t>maxvalue) {
                                                                  maxvalue=t;
                                                                  max=i;
                                                                 };
                                                                };
                                                                return(max);
};
template <class _tg> unsigned int _vektor<_tg>::niedrigsterindex() const{
                                                                unsigned int min;
                                                                unsigned int i;
                                                                _tg minvalue;
                                                                _tg t;
                                                                //---------------
                                                                if(o[0]<0) t=-o[0]; else t=o[0];
                                                                min=0;
                                                                minvalue=t;
                                                                for(i=1;i<dim;i++){
                                                                 if(o[i]<0) t=-o[i]; else t=o[i];
                                                                 if(t<minvalue) {
                                                                  minvalue=t;
                                                                  min=i;
                                                                 };
                                                                };
                                                                return(min);
};
template <class _tg> void _vektor<_tg>::kopieren(const _vektor<_tg>&x){
                                                                redimensionieren(x.dim);
                                                                for(unsigned int i=0;i<dim;i++) o[i]=x.o[i];
};
template <class _tg>void _vektor<_tg>::init(){
                                                                o=0;
                                                                dim=0;
};
template <class _tg>void _vektor<_tg>::redimensionieren(unsigned int nd){
                                                                if(dim!=nd){
                                                                  if(o){
                                                                  loeschen();
                                                                  erzeugen(nd);
                                                                 }else{
                                                                  erzeugen(nd);
                                                                 };
                                                                };
};
template <class _tg>void _vektor<_tg>::loeschen(){
                                                                if(o){
                                                                 delete o;
                                                                 o=0;
                                                                };
};
template <class _tg>void _vektor<_tg>::erzeugen(unsigned int nd){
                                                                if(nd==0){
                                                                 nd=1;
                                                                };
                                                                dim=nd;
                                                                o=new _tg[dim];
                                                                for(unsigned int i=0;i<dim;i++) o[i]=0;
};
template <class _tg>_tg * _vektor<_tg>::daten(){
                                                                return(o);
};

//************************************************************* V E C T O R :: O P E R A T O R Ü B E R L A D U N G E N *********************************************************************
template <class _tg>_vektor<_tg> _vektor<_tg>::operator+(const _vektor&v) const{//addition
                                                                _vektor<_tg> h=v;
                                                                return(h+=*this);
};
template <class _tg>_vektor<_tg>&_vektor<_tg>::operator+=(const _vektor&v){//addition
                                                                add(v);
                                                                return(*this);
};
template <class _tg>_vektor<_tg> _vektor<_tg>::operator-(const _vektor&v) const{//subtraktion
                                                                _vektor<_tg> h=*this;
                                                                h.sub(v);
                                                                return(h);
};
template <class _tg>_vektor<_tg>&_vektor<_tg>::operator-=(const _vektor&v){//subtraktion
                                                                sub(v);
                                                                return(*this);
};
template <class _tg>_vektor<_tg> _vektor<_tg>::operator-() const{//inversion
                                                                _vektor<_tg> h=*this;
                                                                h.mul(-1.0);
                                                                return(h);
};
template <class _tg>_tg _vektor<_tg>::operator*(const _vektor&v) const{//vektormultiplikation
                                                                return(mul(v));
};
template <class _tg>_vektor<_tg> _vektor<_tg>::operator*(_tg x) const{//skalarmultiplikation
                                                                _vektor<_tg> h=*this;
                                                                h*=x;
                                                                return(h);
};
template <class _tg>_vektor<_tg>&_vektor<_tg>::operator*=(_tg x){//skalarmultiplikation
                                                                mul(x);
                                                                return(*this);
};
template <class _tg>_vektor<_tg>& _vektor<_tg>::operator=(const _vektor&v){//zuweisung
                                                                redimensionieren(v.dim);
                                                                for(unsigned int i=0;i<dim;i++) o[i]=v.o[i];
                                                                return(*this);
};
template <class _tg>bool _vektor<_tg>::operator==(const _vektor&v) const{//vergleich
                                                                bool b=true;
                                                                unsigned int i;
                                                                //-----------
                                                                if(dim!=v.dim) b=false; else{
                                                                 for(i=0;i<dim;i++){
                                                                  if(o[i]!=v.o[i]) {
                                                                   b=false;
                                                                   //i=dim+1;
                                                                  };
                                                                 };
                                                                };
                                                                return(b);
};
template <class _tg>_tg _vektor<_tg>::operator[](unsigned int i) const{//indexzugriff
                                                                if(i<dim){
                                                                 if(i>=0){
                                                                  return(o[i]);
                                                                 };
                                                                };
                                                                return(0);
};
template <class _tg>_vektor<_tg> _vektor<_tg>::operator%(const _vektor&v) const{//kreuzprodukt
                                                                _vektor<_tg> h=v;
                                                                return(h%=*this);
};
template <class _tg>_vektor<_tg>&_vektor<_tg>::operator%=(const _vektor&v){//kreuzprodukt
                                                                kreuzprodukt(v);
                                                                return(*this);
};
//************************************************************* V E C T O R :: F U N K T I O N E N   *********************************************************************
template <class _tg> void _vektor<_tg>::add(const _vektor<_tg>&v){
                                                                for(unsigned int i=0;i<dim;i++) o[i]+=v.o[i];
};
template <class _tg> void _vektor<_tg>::add(unsigned int i,_tg x){
                                                                if((i<dim)&&(i>=0)){
                                                                 o[i]+=x;
                                                                };
};
template <class _tg> void _vektor<_tg>::sub(const _vektor<_tg>&v){
                                                                for(unsigned int i=0;i<dim;i++) o[i]-=v.o[i];
};
template <class _tg> void _vektor<_tg>::subinv(const _vektor<_tg>&v){
                                                                  for(unsigned int i=0;i<dim;i++) o[i]=v.o[i]-o[i];
};
template <class _tg> void _vektor<_tg>::sub(unsigned int i,_tg x){
                                                                if((i<dim)&&(i>=0)){
                                                                 o[i]-=x;
                                                                };
};
template <class _tg> void _vektor<_tg>::subinv(unsigned int i,_tg x){
                                                                if((i<dim)&&(i>=0)){
                                                                 o[i]=x-o[i];
                                                                };
};
template <class _tg> _tg _vektor<_tg>::mul(const _vektor<_tg>&v) const{
                                                                _tg r=0;
                                                                //--------
                                                                for(unsigned int i=0;i<dim;i++) r+=o[i]*v.o[i];
                                                                return(r);
};
template <class _tg> void _vektor<_tg>::mul(_tg x){
                                                                for(unsigned int i=0;i<dim;i++) o[i]*=x;
};
template <class _tg> void _vektor<_tg>::mul(unsigned int i,_tg x){
                                                                if((i<dim)&&(i>=0)){
                                                                 o[i]*=x;
                                                                };
};
template <class _tg> _tg _vektor<_tg>::laengelaenge() const{
                                                                _tg r=0;
                                                                unsigned int i;
                                                                //-------
                                                                for(i=0;i<dim;i++) r+=(o[i]*o[i]);
                                                                return(r);
};
template <class _tg> _tg _vektor<_tg>::laenge() const{
                                                                return(sqrt(laengelaenge()));
};
template <class _tg> _tg _vektor<_tg>::normalisieren(){
                                                                _tg l;
                                                                //-----
                                                                l=laenge();
                                                                if(l!=0){
                                                                 for(unsigned int i=0;i<dim;i++) o[i]/=l;
                                                                }else{
                                                                 //error div(0)
                                                                };
                                                                return(l);
};
template <class _tg> void _vektor<_tg>::kreuzprodukt(const _vektor<_tg>&v){
                                                                if(v.dim==3)
                                                                if(dim==3){
                                                                 _tg e[2];
                                                                 e[0]=v.o[1]*o[2] - v.o[2]*o[1];
                                                                 e[1]=v.o[2]*o[0] - v.o[0]*o[2];
                                                                 o[2]=v.o[0]*o[1] - v.o[1]*o[0];
                                                                 o[0]=e[0];
                                                                 o[1]=e[1];
                                                                };
};
template <class _tg> void _vektor<_tg>::rotx(_tg w){
                                                                if(dim==3){
                                                                 _tg y,z;
                                                                 y=o[1]*cos(w*_ph)-o[2]*sin(w*_ph);
                                                                 z=o[1]*sin(w*_ph)+o[2]*cos(w*_ph);
                                                                 o[1]=y;
                                                                 o[2]=z;
                                                                };

};
template <class _tg> void _vektor<_tg>::roty(_tg w){
                                                                if(dim==3){
                                                                 _tg y,z;
                                                                 y=o[0]*cos(w*_ph)-o[2]*sin(w*_ph);
                                                                 z=o[0]*sin(w*_ph)+o[2]*cos(w*_ph);
                                                                 o[0]=y;
                                                                 o[2]=z;
                                                                };
};
template <class _tg> void _vektor<_tg>::rotz(_tg w){
                                                                //if(dim==3){
                                                                 _tg y,z;
                                                                 y=o[0]*cos(w*_ph)-o[1]*sin(w*_ph);
                                                                 z=o[0]*sin(w*_ph)+o[1]*cos(w*_ph);
                                                                 o[0]=y;
                                                                 o[1]=z;
                                                                //};
};
template <class _tg> void _vektor<_tg>::begrenzen(_tg min,_tg max){
                                                                for(unsigned int i=0;i<dim;i++){
                                                                 if(o[i]>max) o[i]=max;
                                                                 if(o[i]<min) o[i]=min;
                                                                };
};
template <class _tg> void _vektor<_tg>::zufall(){
                                                                unsigned int i;
                                                                //---------------
                                                                do{
                                                                 for(i=0;i<dim;i++){
                                                                  o[i]=_tg(rand())/_tg(RAND_MAX);
                                                                  o[i]-=0.5;
                                                                 };
                                                                }while(laengelaenge()==0);
                                                                normalisieren();
};
template <class _tg> _tg _vektor<_tg>::winkel(const _vektor<_tg>&v) const{
                                                                if((v.dim==dim)&&(dim>1)){
                                                                 _tg n=laenge()*v.laenge();
                                                                 //_vektor<_tg> h=*this;
                                                                 if(n>0){
                                                                  n=(*this*v)/n;
                                                                  if(n<-1)n=-1;
                                                                  if(n>+1)n=+1;
                                                                  return((acos(n)*180)/_pi);
                                                                 }else{
                                                                  //error
                                                                  return(0);
                                                                 };
                                                                }else{
                                                                 //error
                                                                 return(0);
                                                                };
};
template <class _tg> void _vektor<_tg>::tauschen(unsigned int i0,unsigned int i1){
                                                                _tg h;
                                                                //-------
                                                                if(i0!=i1){
                                                                 if(i0<dim){
                                                                  if(i1<dim){
                                                                   h=o[i1];
                                                                   o[i1]=o[i0];
                                                                   o[i0]=h;
                                                                  };
                                                                 };
                                                                };
};
template <class _tg> _tg _vektor<_tg>::produkt(const _vektor<_tg>&v){
                                                                _tg r=0;
                                                                unsigned int i;
                                                                //-----
                                                                if(v.dim==dim){
                                                                 for(i=0;i<dim;i++){
                                                                  o[i]*=v.o[i];
                                                                  r+=o[i];
                                                                 };
                                                                };
                                                                return(r);

};
template <class _tg> char _vektor<_tg>::konvertieren(unsigned int nd){
                                                                unsigned int od=dim;
                                                                _tg*lo;
                                                                unsigned int i;
                                                                //-----------
                                                                if(dim!=nd){
                                                                 lo=new _tg[dim];
                                                                 for(i=0;i<dim;i++) lo[i]=o[i];
                                                                 redimensionieren(nd);
                                                                 for(i=0;i<dim;i++){
                                                                  if(i<od){
                                                                   o[i]=lo[i];
                                                                  }else{
                                                                   o[i]=0;
                                                                  };
                                                                 };
                                                                 delete[] lo;
                                                                 return(1);
                                                                };
                                                                return(0);
};

template <class _tg> char _vektor<_tg>::konvertieren(unsigned int nd,const _vektor<unsigned int>&c){
                                                                char r;
                                                                //--------
                                                                r=konvertierenniedriger(nd,c);
                                                                if(r==0){
                                                                 r=konvertierenhoeher(nd,c);
                                                                };
                                                                return(r);
};
template <class _tg> char _vektor<_tg>::konvertierenniedriger(unsigned int nd,const _vektor<unsigned int>&c){
                                                                if(nd<dim){
                                                                 if(c.holendimension()>=nd){
                                                                      _vektor<_tg> h=*this;
                                                                  redimensionieren(nd);
                                                                  for(unsigned int i=0;i<dim;i++) o[i]=h[c[i]];
                                                                  return(1);
                                                                 }else{
                                                                  //error : c.dim zu klein
                                                                 };
                                                                };
                                                                return(0);
};
template <class _tg> char _vektor<_tg>::konvertierenhoeher(unsigned int nd,const _vektor<unsigned int>&c){
                                                                if(nd>dim){
                                                                 if(c.holendimension()>=nd){
                                                                  _vektor<_tg> h=*this;
                                                                  redimensionieren(nd);
                                                                  for(unsigned int i=0;i<dim;i++) o[c[i]]=h[i];
                                                                  return(1);
                                                                 }else{
                                                                  //error : c.dim zu klein
                                                                 };
                                                                };
                                                                return(0);
};
//*************************************************************************************************************************************************************************************************
//                                                              V E K T O R  2 D
//*************************************************************************************************************************************************************************************************
template <class _tg> class _vektor2{
        public:
                inline _vektor2();
                inline _vektor2(const _vektor2&);
                inline _vektor2(_tg,_tg);
                inline void setzen(const _vektor2<_tg>&);
                inline void setzen(_tg,_tg);
                inline void setzenkomponente(unsigned int,_tg);
                inline void x(const _tg);
                inline void y(const _tg);
                inline _tg holen(unsigned int i) const;
                inline _tg x()const;
                inline _tg y()const;                
                unsigned int groessterindex() const;
                unsigned int niedrigsterindex() const;
                inline virtual ~_vektor2();
                inline void kopieren(const _vektor2&);
                inline const _tg*daten()const;
        public:
                inline _vektor2 operator+(const _vektor2&) const;
                inline _vektor2& operator+=(const _vektor2&);
                inline _vektor2 operator-(const _vektor2&) const;
                inline _vektor2& operator-=(const _vektor2&);
                inline _vektor2 operator-() const;
                inline _tg operator*(const _vektor2&) const;
                inline _vektor2 operator*(_tg) const;
                inline _vektor2&operator*=(_tg);
                inline _vektor2&operator=(const _vektor2&);
                inline bool operator==(const _vektor2&) const;
                inline _tg operator[](unsigned int) const;
                //inline _vektor2 operator%(const _vektor2&) const;
                //inline _vektor2& operator%=(const _vektor2&);
                //----------------------------------
                inline void add(const _vektor2&);
                inline void add(unsigned int,_tg);
                inline void sub(const _vektor2&);
                inline void subinv(const _vektor2&);
                inline void sub(unsigned int,_tg);
                inline void subinv(unsigned int,_tg);
                inline _tg mul(const _vektor2&) const;
                inline void mul(_tg);
                inline void mul(unsigned int,_tg);
                inline _tg normalisieren();
                inline _tg laenge() const;
                inline _tg laengelaenge() const;
                //inline void kreuzprodukt(const _vektor2&);
                inline _tg produkt(const _vektor2&);
                //inline void rotx(_tg);
                //inline void roty(_tg);
                inline void rot(_tg);
                inline void begrenzen(_tg,_tg);
                inline void zufall();
                inline _tg winkel(const _vektor2&) const;
                inline void tauschen(unsigned int,unsigned int);
                //void speichern(_datei*d);
                //void laden(_datei*d);
        private:
                _tg o[2];
};
//************************************************************* V E C T O R :: B A S I S O P E R A T I O N E N *********************************************************************
template <class _tg>_vektor2<_tg>::_vektor2(){
                                                                o[0]=o[1]=0;
};
template <class _tg>_vektor2<_tg>::_vektor2(const _vektor2<_tg>&x){
                                                                kopieren(x);
};
template <class _tg>_vektor2<_tg>::_vektor2(_tg x,_tg y){
                                                                o[0]=x;
                                                                o[1]=y;
};
template <class _tg> void _vektor2<_tg>::setzen(const _vektor2<_tg>&x){
                                                                kopieren(x);
};
template <class _tg> void _vektor2<_tg>::setzen(_tg x,_tg y){
                                                                o[0]=x;
                                                                o[1]=y;
};
template <class _tg>void _vektor2<_tg>::setzenkomponente(unsigned int i,_tg x){
                                                                o[i]=x;
};
template <class _tg>void _vektor2<_tg>::x(const _tg x){
                                                                o[0]=x;
};
template <class _tg>void _vektor2<_tg>::y(const _tg y){
                                                                o[1]=y;
};
template <class _tg>_vektor2<_tg>::~_vektor2(){
};
template<class _tg> _tg _vektor2<_tg>::holen(unsigned int i) const{
                                                                return(o[i]);
};
template<class _tg> _tg _vektor2<_tg>::x() const{
                                                                return(o[0]);
};
template<class _tg> _tg _vektor2<_tg>::y() const{
                                                                return(o[1]);
};

template <class _tg> unsigned int _vektor2<_tg>::groessterindex() const{
                                                                unsigned int max;
                                                                unsigned int i;
                                                                _tg maxvalue;
                                                                _tg t;
                                                                //---------------
                                                                max=0;
                                                                maxvalue=0;
                                                                for(i=0;i<2;i++){
                                                                 if(o[i]<0) t=-o[i]; else t=o[i];
                                                                 if(t>maxvalue) {
                                                                  maxvalue=t;
                                                                  max=i;
                                                                 };
                                                                };
                                                                return(max);
};
template <class _tg> unsigned int _vektor2<_tg>::niedrigsterindex() const{
                                                                unsigned int min;
                                                                unsigned int i;
                                                                _tg minvalue;
                                                                _tg t;
                                                                //---------------
                                                                if(o[0]<0) t=-o[0]; else t=o[0];
                                                                min=0;
                                                                minvalue=t;
                                                                for(i=1;i<2;i++){
                                                                 if(o[i]<0) t=-o[i]; else t=o[i];
                                                                 if(t<minvalue) {
                                                                  minvalue=t;
                                                                  min=i;
                                                                 };
                                                                };
                                                                return(min);
};
template <class _tg> void _vektor2<_tg>::kopieren(const _vektor2<_tg>&x){
                                                                o[0]=x.o[0];
                                                                o[1]=x.o[1];
};
template <class _tg>const _tg * _vektor2<_tg>::daten()const {
                                                                return(o);
};

//************************************************************* V E C T O R :: O P E R A T O R Ü B E R L A D U N G E N *********************************************************************
template <class _tg>_vektor2<_tg> _vektor2<_tg>::operator+(const _vektor2&v) const{//addition
                                                                _vektor2<_tg> h=v;
                                                                return(h+=*this);
};
template <class _tg>_vektor2<_tg>&_vektor2<_tg>::operator+=(const _vektor2&v){//addition
                                                                add(v);
                                                                return(*this);
};
template <class _tg>_vektor2<_tg> _vektor2<_tg>::operator-(const _vektor2&v) const{//subtraktion
                                                                _vektor2<_tg> h=*this;
                                                                h.sub(v);
                                                                return(h);
};
template <class _tg>_vektor2<_tg>&_vektor2<_tg>::operator-=(const _vektor2&v){//subtraktion
                                                                sub(v);
                                                                return(*this);
};
template <class _tg>_vektor2<_tg> _vektor2<_tg>::operator-()const{//inversion
                                                                _vektor2<_tg> h=*this;
                                                                h.mul(-1.0);
                                                                return(h);
};
template <class _tg>_tg _vektor2<_tg>::operator*(const _vektor2&v) const{//vektormultiplikation
                                                                return(mul(v));
};
template <class _tg>_vektor2<_tg> _vektor2<_tg>::operator*(_tg x) const{//skalarmultiplikation
                                                                _vektor2<_tg> h=*this;
                                                                h*=x;
                                                                return(h);
};
template <class _tg>_vektor2<_tg>&_vektor2<_tg>::operator*=(_tg x){//skalarmultiplikation
                                                                mul(x);
                                                                return(*this);
};
template <class _tg>_vektor2<_tg>& _vektor2<_tg>::operator=(const _vektor2&v){//zuweisung
                                                                o[0]=v.o[0];
                                                                o[1]=v.o[1];
                                                                return(*this);
};
template <class _tg>bool _vektor2<_tg>::operator==(const _vektor2&v) const{//vergleich
                                                                bool b=true;
                                                                unsigned int i;
                                                                //-----------
                                                                for(i=0;i<2;i++){
                                                                 if(o[i]!=v.o[i]) return(false);
                                                                };
                                                                return(true);
};
template <class _tg>_tg _vektor2<_tg>::operator[](unsigned int i) const{//indexzugriff
                                                                return(o[i]);
};
/*
template <class _tg>_vektor2<_tg> _vektor2<_tg>::operator%(const _vektor2&v) const{//kreuzprodukt
                                                                _vektor2<_tg> h=v;
                                                                return(h%=*this);
};
template <class _tg>_vektor2<_tg>&_vektor2<_tg>::operator%=(const _vektor2&v){//kreuzprodukt
                                                                kreuzprodukt(v);
                                                                return(*this);
};
*/
//************************************************************* V E C T O R :: F U N K T I O N E N   *********************************************************************
template <class _tg> void _vektor2<_tg>::add(const _vektor2<_tg>&v){
                                                                o[0]+=v.o[0];
                                                                o[1]+=v.o[1];
};
template <class _tg> void _vektor2<_tg>::add(unsigned int i,_tg x){
                                                                o[i]+=x;
};
template <class _tg> void _vektor2<_tg>::sub(const _vektor2<_tg>&v){
                                                                o[0]-=v.o[0];
                                                                o[1]-=v.o[1];
};
template <class _tg> void _vektor2<_tg>::subinv(const _vektor2<_tg>&v){
                                                                o[0]=v.o[0]-o[0];
                                                                o[1]=v.o[1]-o[1];
};
template <class _tg> void _vektor2<_tg>::sub(unsigned int i,_tg x){
                                                                o[i]-=x;
};
template <class _tg> void _vektor2<_tg>::subinv(unsigned int i,_tg x){
                                                                o[i]=x-o[i];
};
template <class _tg> _tg _vektor2<_tg>::mul(const _vektor2<_tg>&v) const{
                                                                return(o[0]*v.o[0] + o[1]*v.o[1]);
};
template <class _tg> void _vektor2<_tg>::mul(_tg x){
                                                                o[0]*=x;
                                                                o[1]*=x;
};
template <class _tg> void _vektor2<_tg>::mul(unsigned int i,_tg x){
                                                                o[i]*=x;
};
template <class _tg> _tg _vektor2<_tg>::laengelaenge() const{
                                                                return(o[0]*o[0] + o[1]*o[1] );
};
template <class _tg> _tg _vektor2<_tg>::laenge() const{
                                                                return(sqrt(laengelaenge()));
};
template <class _tg> _tg _vektor2<_tg>::normalisieren(){
                                                                _tg l;
                                                                //-----
                                                                l=laenge();
                                                                if(l!=0){
                                                                 o[0]/=l;
                                                                 o[1]/=l;
                                                                }else{
                                                                 //error div(0)
                                                                };
                                                                return(l);
};
template <class _tg> void _vektor2<_tg>::rot(_tg w){
                                                                _tg y,z;
                                                                y=o[0]*cos(w*_ph)-o[1]*sin(w*_ph);
                                                                z=o[0]*sin(w*_ph)+o[1]*cos(w*_ph);
                                                                o[0]=y;
                                                                o[1]=z;
};

/*
template <class _tg> void _vektor2<_tg>::kreuzprodukt(const _vektor2<_tg>&v){
                                                                _tg e[2];
                                                                e[0]=v.o[1]*o[2] - v.o[2]*o[1];
                                                                e[1]=v.o[2]*o[0] - v.o[0]*o[2];
                                                                o[2]=v.o[0]*o[1] - v.o[1]*o[0];
                                                                o[0]=e[0];
                                                                o[1]=e[1];
};

template <class _tg> void _vektor2<_tg>::rotx(_tg w){
                                                                _tg y,z;
                                                                y=o[1]*cos(w*_ph)-o[2]*sin(w*_ph);
                                                                z=o[1]*sin(w*_ph)+o[2]*cos(w*_ph);
                                                                o[1]=y;
                                                                o[2]=z;
};
template <class _tg> void _vektor2<_tg>::roty(_tg w){
                                                                _tg y,z;
                                                                y=o[0]*cos(w*_ph)-o[2]*sin(w*_ph);
                                                                z=o[0]*sin(w*_ph)+o[2]*cos(w*_ph);
                                                                o[0]=y;
                                                                o[2]=z;
};
template <class _tg> void _vektor2<_tg>::rotz(_tg w){
                                                                _tg y,z;
                                                                y=o[0]*cos(w*_ph)-o[1]*sin(w*_ph);
                                                                z=o[0]*sin(w*_ph)+o[1]*cos(w*_ph);
                                                                o[0]=y;
                                                                o[1]=z;
};
*/
template <class _tg> void _vektor2<_tg>::begrenzen(_tg min,_tg max){
                                                                for(unsigned int i=0;i<2;i++){
                                                                 if(o[i]>max) o[i]=max;
                                                                 if(o[i]<min) o[i]=min;
                                                                };
};
template <class _tg> void _vektor2<_tg>::zufall(){
                                                                unsigned int i;
                                                                //---------------
                                                                do{
                                                                 for(i=0;i<2;i++){
                                                                  o[i]=_tg(rand())/_tg(RAND_MAX);
                                                                  o[i]-=0.5;
                                                                 };
                                                                }while(laengelaenge()==0);
                                                                normalisieren();
};
template <class _tg> _tg _vektor2<_tg>::winkel(const _vektor2<_tg>&v) const{
                                                                _tg n=laenge()*v.laenge();
                                                                if(n>0){
                                                                 n=(*this*v)/n;
                                                                 if(n<-1)n=-1;
                                                                 if(n>+1)n=+1;
                                                                 return((acos(n)*180)/_pi);
                                                                }else{
                                                                  //error
                                                                 return(0);
                                                                };
};
template <class _tg> void _vektor2<_tg>::tauschen(unsigned int i0,unsigned int i1){
                                                                _tg h;
                                                                //-------
                                                                if(i0!=i1){
                                                                 if(i0<2){
                                                                  if(i1<2){
                                                                   h=o[i1];
                                                                   o[i1]=o[i0];
                                                                   o[i0]=h;
                                                                  };
                                                                 };
                                                                };
};
template <class _tg> _tg _vektor2<_tg>::produkt(const _vektor2<_tg>&v){
                                                                _tg r=0;
                                                                unsigned int i;
                                                                //-----
                                                                for(i=0;i<2;i++){
                                                                 o[i]*=v.o[i];
                                                                 r+=o[i];
                                                                };
                                                                return(r);
};
/*template <class _tg> void _vektor2<_tg>::speichern(_datei*d){
                                                                d->speichern(o[0]);
                                                                d->speichern(o[1]);
};
template <class _tg> void _vektor2<_tg>::laden(_datei*d){
                                                                d->laden(o[0]);
                                                                d->laden(o[1]);
};*/

//*************************************************************************************************************************************************************************************************
//                                                              V E K T O R  3 D
//*************************************************************************************************************************************************************************************************
template <class _tg> class _vektor3{
        public:
                inline _vektor3();
                inline _vektor3(const _vektor3&);
                //inline _vektor3(const _vektor3&);
                inline _vektor3(_tg,_tg,_tg);
                inline void setzen(const _vektor3&);
                //inline void setzen(const _vektor4&);
                inline void setzen(_tg,_tg,_tg);
                inline void setzenkomponente(unsigned int,_tg);
                inline void x(const _tg);
                inline void y(const _tg);
                inline void z(const _tg);
                inline _tg holen(unsigned int i) const;
                inline _tg x()const;
                inline _tg y()const;
                inline _tg z()const;
                unsigned int groessterindex() const;
                unsigned int niedrigsterindex() const;
                inline virtual ~_vektor3();
                inline void kopieren(const _vektor3&);
                //inline void kopieren(const _vektor4&);
                inline const _tg*daten()const;
        public:
                inline _vektor3 operator+(const _vektor3&) const;
                inline _vektor3& operator+=(const _vektor3&);
                inline _vektor3 operator-(const _vektor3&) const;
                inline _vektor3& operator-=(const _vektor3&);
                inline _vektor3 operator-() const;
                inline _tg operator*(const _vektor3&) const;
                inline _vektor3 operator*(_tg) const;
                inline _vektor3&operator*=(_tg);
                inline _vektor3&operator=(const _vektor3&);
                inline bool operator==(const _vektor3&) const;
                inline _tg operator[](unsigned int) const;
                inline _vektor3 operator%(const _vektor3&) const;
                inline _vektor3& operator%=(const _vektor3&);
                //----------------------------------
                inline void add(const _vektor3&);
                inline void add(unsigned int,_tg);
                inline void sub(const _vektor3&);
                inline void subinv(const _vektor3&);
                inline void sub(unsigned int,_tg);
                inline void subinv(unsigned int,_tg);
                inline _tg mul(const _vektor3&) const;
                inline void mul(_tg);
                inline void mul(unsigned int,_tg);
                inline _tg normalisieren();
                inline _tg laenge() const;
                inline _tg laengelaenge() const;
                inline _tg laengelaengexy() const;
                inline void kreuzprodukt(const _vektor3&);
                inline _tg produkt(const _vektor3&);
                inline _tg abstand(const _vektor3&);
                inline _tg abstandabstand(const _vektor3&);
                inline _tg abstandabstandxy(const _vektor3&);
                void rotieren(const _vektor3<_tg>&a,const _tg w);
                inline void rotx(_tg);
                inline void roty(_tg);
                inline void rotz(_tg);
                inline void begrenzen(_tg,_tg);
                inline void zufall();
                inline _tg winkel(const _vektor3&) const;
                inline void projizierenebene(const _vektor3<_tg>&n);
                inline void tauschen(unsigned int,unsigned int);
                void reflektieren(const _vektor3<_tg>&n);
                //void speichern(_datei*d);
                //void laden(_datei*d);
        private:
                _tg o[3];
};
//************************************************************* V E C T O R :: B A S I S O P E R A T I O N E N *********************************************************************
template <class _tg>_vektor3<_tg>::_vektor3(){
                                                                o[0]=o[1]=o[2]=0;
};
template <class _tg>_vektor3<_tg>::_vektor3(const _vektor3<_tg>&x){
                                                                kopieren(x);
};
template <class _tg>_vektor3<_tg>::_vektor3(_tg x,_tg y,_tg z){
                                                                o[0]=x;
                                                                o[1]=y;
                                                                o[2]=z;
};
template <class _tg> void _vektor3<_tg>::setzen(const _vektor3<_tg>&x){
                                                                kopieren(x);
};
template <class _tg> void _vektor3<_tg>::setzen(_tg x,_tg y,_tg z){
                                                                o[0]=x;
                                                                o[1]=y;
                                                                o[2]=z;
};
template <class _tg>void _vektor3<_tg>::setzenkomponente(unsigned int i,_tg x){
                                                                o[i]=x;
};
template <class _tg>void _vektor3<_tg>::x(const _tg x){
                                                                o[0]=x;
};
template <class _tg>void _vektor3<_tg>::y(const _tg y){
                                                                o[1]=y;
};
template <class _tg>void _vektor3<_tg>::z(const _tg z){
                                                                o[2]=z;
};

template <class _tg>_vektor3<_tg>::~_vektor3(){
};
template<class _tg> _tg _vektor3<_tg>::holen(unsigned int i) const{
                                                                return(o[i]);
};
template<class _tg> _tg _vektor3<_tg>::x() const{
                                                                return(o[0]);
};
template<class _tg> _tg _vektor3<_tg>::y() const{
                                                                return(o[1]);
};
template<class _tg> _tg _vektor3<_tg>::z() const{
                                                                return(o[2]);
};
template <class _tg> unsigned int _vektor3<_tg>::groessterindex() const{
                                                                unsigned int max;
                                                                unsigned int i;
                                                                _tg maxvalue;
                                                                _tg t;
                                                                //---------------
                                                                max=0;
                                                                maxvalue=0;
                                                                for(i=0;i<3;i++){
                                                                 if(o[i]<0) t=-o[i]; else t=o[i];
                                                                 if(t>maxvalue) {
                                                                  maxvalue=t;
                                                                  max=i;
                                                                 };
                                                                };
                                                                return(max);
};
template <class _tg> unsigned int _vektor3<_tg>::niedrigsterindex() const{
                                                                unsigned int min;
                                                                unsigned int i;
                                                                _tg minvalue;
                                                                _tg t;
                                                                //---------------
                                                                if(o[0]<0) t=-o[0]; else t=o[0];
                                                                min=0;
                                                                minvalue=t;
                                                                for(i=1;i<3;i++){
                                                                 if(o[i]<0) t=-o[i]; else t=o[i];
                                                                 if(t<minvalue) {
                                                                  minvalue=t;
                                                                  min=i;
                                                                 };
                                                                };
                                                                return(min);
};
template <class _tg> void _vektor3<_tg>::kopieren(const _vektor3<_tg>&x){
                                                                o[0]=x.o[0];
                                                                o[1]=x.o[1];
                                                                o[2]=x.o[2];
};
template <class _tg>const _tg * _vektor3<_tg>::daten()const {
                                                                return(o);
};

//************************************************************* V E C T O R :: O P E R A T O R Ü B E R L A D U N G E N *********************************************************************
template <class _tg>_vektor3<_tg> _vektor3<_tg>::operator+(const _vektor3&v) const{//addition
                                                                _vektor3<_tg> h=v;
                                                                return(h+=*this);
};
template <class _tg>_vektor3<_tg>&_vektor3<_tg>::operator+=(const _vektor3&v){//addition
                                                                add(v);
                                                                return(*this);
};
template <class _tg>_vektor3<_tg> _vektor3<_tg>::operator-(const _vektor3&v) const{//subtraktion
                                                                _vektor3<_tg> h=*this;
                                                                h.sub(v);
                                                                return(h);
};
template <class _tg>_vektor3<_tg>&_vektor3<_tg>::operator-=(const _vektor3&v){//subtraktion
                                                                sub(v);
                                                                return(*this);
};
template <class _tg>_vektor3<_tg> _vektor3<_tg>::operator-()const{//inversion
                                                                _vektor3<_tg> h=*this;
                                                                h.mul(-1.0);
                                                                return(h);
};
template <class _tg>_tg _vektor3<_tg>::operator*(const _vektor3&v) const{//vektormultiplikation
                                                                return(mul(v));
};
template <class _tg>_vektor3<_tg> _vektor3<_tg>::operator*(_tg x) const{//skalarmultiplikation
                                                                _vektor3<_tg> h=*this;
                                                                h*=x;
                                                                return(h);
};
template <class _tg>_vektor3<_tg>&_vektor3<_tg>::operator*=(_tg x){//skalarmultiplikation
                                                                mul(x);
                                                                return(*this);
};
template <class _tg>_vektor3<_tg>& _vektor3<_tg>::operator=(const _vektor3&v){//zuweisung
                                                                o[0]=v.o[0];
                                                                o[1]=v.o[1];
                                                                o[2]=v.o[2];
                                                                return(*this);
};
template <class _tg>bool _vektor3<_tg>::operator==(const _vektor3&v) const{//vergleich
                                                                bool b=true;
                                                                unsigned int i;
                                                                //-----------
                                                                for(i=0;i<3;i++){
                                                                 if(o[i]!=v.o[i]) return(false);
                                                                };
                                                                return(true);
};
template <class _tg>_tg _vektor3<_tg>::operator[](unsigned int i) const{//indexzugriff
                                                                return(o[i]);
};
template <class _tg>_vektor3<_tg> _vektor3<_tg>::operator%(const _vektor3&v) const{//kreuzprodukt
                                                                _vektor3<_tg> h=v;
                                                                return(h%=*this);
};
template <class _tg>_vektor3<_tg>&_vektor3<_tg>::operator%=(const _vektor3&v){//kreuzprodukt
                                                                kreuzprodukt(v);
                                                                return(*this);
};
//************************************************************* V E C T O R :: F U N K T I O N E N   *********************************************************************
template <class _tg> void _vektor3<_tg>::add(const _vektor3<_tg>&v){
                                                                o[0]+=v.o[0];
                                                                o[1]+=v.o[1];
                                                                o[2]+=v.o[2];
};
template <class _tg> void _vektor3<_tg>::add(unsigned int i,_tg x){
                                                                o[i]+=x;
};
template <class _tg> void _vektor3<_tg>::sub(const _vektor3<_tg>&v){
                                                                o[0]-=v.o[0];
                                                                o[1]-=v.o[1];
                                                                o[2]-=v.o[2];
};
template <class _tg> void _vektor3<_tg>::subinv(const _vektor3<_tg>&v){
                                                                o[0]=v.o[0]-o[0];
                                                                o[1]=v.o[1]-o[1];
                                                                o[2]=v.o[2]-o[2];
};
template <class _tg> void _vektor3<_tg>::sub(unsigned int i,_tg x){
                                                                o[i]-=x;
};
template <class _tg> void _vektor3<_tg>::subinv(unsigned int i,_tg x){
                                                                o[i]=x-o[i];
};
template <class _tg> _tg _vektor3<_tg>::mul(const _vektor3<_tg>&v) const{
                                                                return(o[0]*v.o[0] + o[1]*v.o[1] + o[2]*v.o[2]);
};
template <class _tg> void _vektor3<_tg>::mul(_tg x){
                                                                o[0]*=x;
                                                                o[1]*=x;
                                                                o[2]*=x;
};
template <class _tg> void _vektor3<_tg>::mul(unsigned int i,_tg x){
                                                                o[i]*=x;
};
template <class _tg> _tg _vektor3<_tg>::laengelaenge() const{
                                                                return(o[0]*o[0] + o[1]*o[1] + o[2]*o[2]);
};
template <class _tg> _tg _vektor3<_tg>::laengelaengexy() const{
                                                                return(o[0]*o[0] + o[1]*o[1]);
};
template <class _tg> _tg _vektor3<_tg>::laenge() const{
                                                                return(sqrt(laengelaenge()));
};
template <class _tg> _tg _vektor3<_tg>::normalisieren(){
                                                                _tg l;
                                                                //-----
                                                                l=laenge();
                                                                if(l!=0){
                                                                 o[0]/=l;
                                                                 o[1]/=l;
                                                                 o[2]/=l;
                                                                }else{
                                                                 //error div(0)
                                                                };
                                                                return(l);
};
template <class _tg> void _vektor3<_tg>::kreuzprodukt(const _vektor3<_tg>&v){
                                                                _tg e[2];
                                                                e[0]=v.o[1]*o[2] - v.o[2]*o[1];
                                                                e[1]=v.o[2]*o[0] - v.o[0]*o[2];
                                                                o[2]=v.o[0]*o[1] - v.o[1]*o[0];
                                                                o[0]=e[0];
                                                                o[1]=e[1];
};
template <class _tg> void _vektor3<_tg>::rotieren(const _vektor3<_tg>&a,const _tg w){
                                                				_vektor3<_tg> e;
				                                                ::rotieren(a,*this,w,e);
				                                                *this=e;
};

template <class _tg> void _vektor3<_tg>::rotx(_tg w){
                                                                _tg y,z;
                                                                y=o[1]*cos(w*_ph)-o[2]*sin(w*_ph);
                                                                z=o[1]*sin(w*_ph)+o[2]*cos(w*_ph);
                                                                o[1]=y;
                                                                o[2]=z;
};
template <class _tg> void _vektor3<_tg>::roty(_tg w){
                                                                _tg y,z;
                                                                y=o[0]*cos(w*_ph)-o[2]*sin(w*_ph);
                                                                z=o[0]*sin(w*_ph)+o[2]*cos(w*_ph);
                                                                o[0]=y;
                                                                o[2]=z;
};
template <class _tg> void _vektor3<_tg>::rotz(_tg w){
                                                                _tg y,z;
                                                                y=o[0]*cos(w*_ph)-o[1]*sin(w*_ph);
                                                                z=o[0]*sin(w*_ph)+o[1]*cos(w*_ph);
                                                                o[0]=y;
                                                                o[1]=z;
};
template <class _tg> void _vektor3<_tg>::begrenzen(_tg min,_tg max){
                                                                for(unsigned int i=0;i<3;i++){
                                                                 if(o[i]>max) o[i]=max;
                                                                 if(o[i]<min) o[i]=min;
                                                                };
};
template <class _tg> void _vektor3<_tg>::zufall(){
                                                                unsigned int i;
                                                                //---------------
                                                                do{
                                                                 for(i=0;i<3;i++){
                                                                  o[i]=_tg(rand())/_tg(RAND_MAX);
                                                                  o[i]-=0.5;
                                                                 };
                                                                }while(laengelaenge()==0);
                                                                normalisieren();
};
template <class _tg> _tg _vektor3<_tg>::winkel(const _vektor3<_tg>&v) const{
                                                                _tg n=laenge()*v.laenge();
                                                                //_vektor3<_tg> h=*this;
                                                                if(n>0){
                                                                 n=(*this*v)/n;
                                                                 if(n<-1)n=-1;
                                                                 if(n>+1)n=+1;
                                                                 return((acos(n)*180)/_pi);
                                                                }else{
                                                                  //error
                                                                 return(0);
                                                                };
};
template <class _tg> void _vektor3<_tg>::tauschen(unsigned int i0,unsigned int i1){
                                                                _tg h;
                                                                //-------
                                                                if(i0!=i1){
                                                                 if(i0<3){
                                                                  if(i1<3){
                                                                   h=o[i1];
                                                                   o[i1]=o[i0];
                                                                   o[i0]=h;
                                                                  };
                                                                 };
                                                                };
};
template <class _tg> _tg _vektor3<_tg>::produkt(const _vektor3<_tg>&v){
                                                                _tg r=0;
                                                                unsigned int i;
                                                                //-----
                                                                for(i=0;i<3;i++){
                                                                 o[i]*=v.o[i];
                                                                 r+=o[i];
                                                                };
                                                                return(r);
};
template <class _tg> _tg _vektor3<_tg>::abstand(const _vektor3<_tg>&v){
                                                                _vektor3<_tg> h=*this-v;
                                                                return(h.laenge());
};
template <class _tg> _tg _vektor3<_tg>::abstandabstand(const _vektor3<_tg>&v){
                                                                _vektor3<_tg> h=*this-v;
                                                                return(h.laengelaenge());
};
template <class _tg> _tg _vektor3<_tg>::abstandabstandxy(const _vektor3<_tg>&v){
                                                                _vektor3<_tg> h=*this-v;
                                                                return(h.laengelaengexy());
};
template <class _tg> void _vektor3<_tg>::projizierenebene(const _vektor3<_tg>&n){
                                                                *this+=n*-(*this*n);
};
template <class _tg> void _vektor3<_tg>::reflektieren(const _vektor3<_tg>&n){
                                                                //n=schnittpunkt.normale;
                                                                _tg lot[3];
                                                                _tg nmn=n*n;
                                                                //h=o+einfallsvektor;
                                                                _tg hhh=(-o[0]*n[0] - o[1]*n[1] - o[2]*n[2])/nmn;//((o[0]-h[0])*n[0] + (o[1]-h[1])*n[1] + (o[2]-h[2])*n[2])/nmn;
                                                                lot[0]=o[0]+n[0]*hhh;//,(h[0]-o[0])+n[0]*hhh);//lot punt auf gerade (o,h,n,lot);
                                                                lot[1]=o[1]+n[1]*hhh;//,(h[0]-o[0])+n[0]*hhh);//lot punt auf gerade (o,h,n,lot);
                                                                lot[2]=o[2]+n[2]*hhh;//,(h[0]-o[0])+n[0]*hhh);//lot punt auf gerade (o,h,n,lot);
                                                                lot[0]*=2;
                                                                lot[1]*=2;
                                                                lot[2]*=2;
                                                                o[0]=lot[0]-o[0];
                                                                o[1]=lot[1]-o[1];
                                                                o[1]=lot[1]-o[1];
};                                                                
/*template <class _tg> void _vektor3<_tg>::speichern(_datei*d){
                                                                d->speichern(o[0]);
                                                                d->speichern(o[1]);
                                                                d->speichern(o[2]);
};
template <class _tg> void _vektor3<_tg>::laden(_datei*d){
                                                                d->laden(o[0]);
                                                                d->laden(o[1]);
                                                                d->laden(o[2]);
};
*/
//*************************************************************************************************************************************************************************************************
//                                                              V E K T O R  4 D
//*************************************************************************************************************************************************************************************************
template <class _tg> class _vektor4{
        public:
                inline _vektor4();
                inline _vektor4(const _vektor4&);
                //inline _vektor4(const _vektor3&);
                inline _vektor4(_tg,_tg,_tg,_tg);
                inline void setzen(const _vektor4&);
                //inline void setzen(const _vektor3&);
                inline void setzen(_tg,_tg,_tg,_tg);
                inline void setzenkomponente(unsigned int,_tg);
                inline void x(const _tg);
                inline void y(const _tg);
                inline void z(const _tg);
                inline void w(const _tg);
                inline _tg holen(unsigned int i) const;
                inline _tg x()const;
                inline _tg y()const;
                inline _tg z()const;
                inline _tg w()const;
                
                unsigned int groessterindex() const;
                unsigned int niedrigsterindex() const;
                inline virtual ~_vektor4();
                inline void kopieren(const _vektor4&);
                //inline void kopieren(const _vektor3&);
                inline const _tg*daten() const;
        public:
                inline _vektor4 operator+(const _vektor4&) const;
                inline _vektor4& operator+=(const _vektor4&);
                inline _vektor4 operator-(const _vektor4&) const;
                inline _vektor4& operator-=(const _vektor4&);
                inline _vektor4 operator-() const;
                inline _tg operator*(const _vektor4&) const;
                inline _vektor4 operator*(_tg) const;
                inline _vektor4&operator*=(_tg);
                inline _vektor4&operator=(const _vektor4&);
                inline bool operator==(const _vektor4&) const;
                inline _tg operator[](unsigned int) const;
                //inline _vektor4 operator%(const _vektor4&) const;
                //inline _vektor4& operator%=(const _vektor4&);
                //----------------------------------
                inline void add(const _vektor4&);
                inline void add(unsigned int,_tg);
                inline void sub(const _vektor4&);
                inline void subinv(const _vektor4&);
                inline void sub(unsigned int,_tg);
                inline void subinv(unsigned int,_tg);
                inline _tg mul(const _vektor4&) const;
                inline void mul(_tg);
                inline void mul(unsigned int,_tg);
                inline _tg normalisieren();
                inline _tg laenge() const;
                inline _tg laengelaenge() const;
                //inline void kreuzprodukt(const _vektor4&);
                inline _tg produkt(const _vektor4&);
                //inline void rotx(_tg);
                //inline void roty(_tg);
                //inline void rotz(_tg);
                inline void begrenzen(_tg,_tg);
                inline void zufall();
                inline _tg winkel(const _vektor4&) const;
                inline void tauschen(unsigned int,unsigned int);
                inline __int32 intargb()const;              
                //void speichern(_datei*d);
                //void laden(_datei*d);
        private:
                _tg o[4];
};
//************************************************************* V E C T O R :: B A S I S O P E R A T I O N E N *********************************************************************
template <class _tg>_vektor4<_tg>::_vektor4(){
                                                                o[0]=o[1]=o[2]=o[3]=0;
};
template <class _tg>_vektor4<_tg>::_vektor4(const _vektor4<_tg>&x){
                                                                kopieren(x);
};
/*
template <class _tg>_vektor4<_tg>::_vektor4(const _vektor3<_tg>&x){
                                                                kopieren(x);
};*/
template <class _tg>_vektor4<_tg>::_vektor4(_tg x,_tg y,_tg z,_tg w){
                                                                o[0]=x;
                                                                o[1]=y;
                                                                o[2]=z;
                                                                o[3]=w;
};
template <class _tg> void _vektor4<_tg>::setzen(const _vektor4<_tg>&x){
                                                                kopieren(x);
};
/*
template <class _tg> void _vektor4<_tg>::setzen(const _vektor3<_tg>&x){
                                                                kopieren(x);
};*/
template <class _tg> void _vektor4<_tg>::setzen(_tg x,_tg y,_tg z,_tg w){
                                                                o[0]=x;
                                                                o[1]=y;
                                                                o[2]=z;
                                                                o[3]=w;
};
template <class _tg>void _vektor4<_tg>::setzenkomponente(unsigned int i,_tg x){
                                                                o[i]=x;
};
template <class _tg>void _vektor4<_tg>::x(const _tg x){
                                                                o[0]=x;
};
template <class _tg>void _vektor4<_tg>::y(const _tg y){
                                                                o[1]=y;
};
template <class _tg>void _vektor4<_tg>::z(const _tg z){
                                                                o[2]=z;
};
template <class _tg>void _vektor4<_tg>::w(const _tg w){
                                                                o[3]=w;
};
template <class _tg>_vektor4<_tg>::~_vektor4(){
};
template<class _tg> _tg _vektor4<_tg>::holen(unsigned int i) const{
                                                                return(o[i]);
};
template<class _tg> _tg _vektor4<_tg>::x() const{
                                                                return(o[0]);
};
template<class _tg> _tg _vektor4<_tg>::y() const{
                                                                return(o[1]);
};
template<class _tg> _tg _vektor4<_tg>::z() const{
                                                                return(o[2]);
};
template<class _tg> _tg _vektor4<_tg>::w() const{
                                                                return(o[3]);
};

template <class _tg> unsigned int _vektor4<_tg>::groessterindex() const{
                                                                unsigned int max;
                                                                unsigned int i;
                                                                _tg maxvalue;
                                                                _tg t;
                                                                //---------------
                                                                max=0;
                                                                maxvalue=0;
                                                                for(i=0;i<4;i++){
                                                                 if(o[i]<0) t=-o[i]; else t=o[i];
                                                                 if(t>maxvalue) {
                                                                  maxvalue=t;
                                                                  max=i;
                                                                 };
                                                                };
                                                                return(max);
};
template <class _tg> unsigned int _vektor4<_tg>::niedrigsterindex() const{
                                                                unsigned int min;
                                                                unsigned int i;
                                                                _tg minvalue;
                                                                _tg t;
                                                                //---------------
                                                                if(o[0]<0) t=-o[0]; else t=o[0];
                                                                min=0;
                                                                minvalue=t;
                                                                for(i=1;i<4;i++){
                                                                 if(o[i]<0) t=-o[i]; else t=o[i];
                                                                 if(t<minvalue) {
                                                                  minvalue=t;
                                                                  min=i;
                                                                 };
                                                                };
                                                                return(min);
};
template <class _tg> void _vektor4<_tg>::kopieren(const _vektor4<_tg>&x){
                                                                o[0]=x.o[0];
                                                                o[1]=x.o[1];
                                                                o[2]=x.o[2];
                                                                o[3]=x.o[3];
};
/*
template <class _tg> void _vektor4<_tg>::kopieren(const _vektor3<_tg>&x){
                                                                o[0]=x.o[0];
                                                                o[1]=x.o[1];
                                                                o[2]=x.o[2];
                                                                o[3]=0;
};*/
template <class _tg>const _tg * _vektor4<_tg>::daten()const{
                                                                return(o);
};

//************************************************************* V E C T O R :: O P E R A T O R Ü B E R L A D U N G E N *********************************************************************
template <class _tg>_vektor4<_tg> _vektor4<_tg>::operator+(const _vektor4&v) const{//addition
                                                                _vektor4<_tg> h=v;
                                                                return(h+=*this);
};
template <class _tg>_vektor4<_tg>&_vektor4<_tg>::operator+=(const _vektor4&v){//addition
                                                                add(v);
                                                                return(*this);
};
template <class _tg>_vektor4<_tg> _vektor4<_tg>::operator-(const _vektor4&v) const{//subtraktion
                                                                _vektor4<_tg> h=*this;
                                                                h.sub(v);
                                                                return(h);
};
template <class _tg>_vektor4<_tg>&_vektor4<_tg>::operator-=(const _vektor4&v){//subtraktion
                                                                sub(v);
                                                                return(*this);
};
template <class _tg>_vektor4<_tg> _vektor4<_tg>::operator-()const{//inversion
                                                                _vektor4<_tg> h=*this;
                                                                h.mul(-1.0);
                                                                return(h);
};
template <class _tg>_tg _vektor4<_tg>::operator*(const _vektor4&v) const{//vektormultiplikation
                                                                return(mul(v));
};
template <class _tg>_vektor4<_tg> _vektor4<_tg>::operator*(_tg x) const{//skalarmultiplikation
                                                                _vektor4<_tg> h=*this;
                                                                h*=x;
                                                                return(h);
};
template <class _tg>_vektor4<_tg>&_vektor4<_tg>::operator*=(_tg x){//skalarmultiplikation
                                                                mul(x);
                                                                return(*this);
};
template <class _tg>_vektor4<_tg>& _vektor4<_tg>::operator=(const _vektor4&v){//zuweisung
                                                                o[0]=v.o[0];
                                                                o[1]=v.o[1];
                                                                o[2]=v.o[2];
                                                                o[3]=v.o[3];
                                                                return(*this);
};
template <class _tg>bool _vektor4<_tg>::operator==(const _vektor4&v) const{//vergleich
                                                                bool b=true;
                                                                unsigned int i;
                                                                //-----------
                                                                for(i=0;i<4;i++){
                                                                 if(o[i]!=v.o[i]) return(false);
                                                                };
                                                                return(true);
};
template <class _tg>_tg _vektor4<_tg>::operator[](unsigned int i) const{//indexzugriff
                                                                return(o[i]);
};
/*
template <class _tg>_vektor4<_tg> _vektor4<_tg>::operator%(const _vektor4&v) const{//kreuzprodukt
                                                                _vektor4<_tg> h=v;
                                                                return(h%=*this);
};
template <class _tg>_vektor4<_tg>&_vektor4<_tg>::operator%=(const _vektor4&v){//kreuzprodukt
                                                                kreuzprodukt(v);
                                                                return(*this);
};*/
//************************************************************* V E C T O R :: F U N K T I O N E N   *********************************************************************
template <class _tg> void _vektor4<_tg>::add(const _vektor4<_tg>&v){
                                                                o[0]+=v.o[0];
                                                                o[1]+=v.o[1];
                                                                o[2]+=v.o[2];
                                                                o[3]+=v.o[3];
};
template <class _tg> void _vektor4<_tg>::add(unsigned int i,_tg x){
                                                                o[i]+=x;
};
template <class _tg> void _vektor4<_tg>::sub(const _vektor4<_tg>&v){
                                                                o[0]-=v.o[0];
                                                                o[1]-=v.o[1];
                                                                o[2]-=v.o[2];
                                                                o[3]-=v.o[3];
};
template <class _tg> void _vektor4<_tg>::subinv(const _vektor4<_tg>&v){
                                                                o[0]=v.o[0]-o[0];
                                                                o[1]=v.o[1]-o[1];
                                                                o[2]=v.o[2]-o[2];
                                                                o[3]=v.o[3]-o[3];
};
template <class _tg> void _vektor4<_tg>::sub(unsigned int i,_tg x){
                                                                o[i]-=x;
};
template <class _tg> void _vektor4<_tg>::subinv(unsigned int i,_tg x){
                                                                o[i]=x-o[i];
};
template <class _tg> _tg _vektor4<_tg>::mul(const _vektor4<_tg>&v) const{
                                                                return(o[0]*v.o[0] + o[1]*v.o[1] + o[2]*v.o[2] + o[3]*v.o[3]);
};
template <class _tg> void _vektor4<_tg>::mul(_tg x){
                                                                o[0]*=x;
                                                                o[1]*=x;
                                                                o[2]*=x;
                                                                o[3]*=x;
};
template <class _tg> void _vektor4<_tg>::mul(unsigned int i,_tg x){
                                                                o[i]*=x;
};
template <class _tg> _tg _vektor4<_tg>::laengelaenge() const{
                                                                return(o[0]*o[0] + o[1]*o[1] + o[2]*o[2] + o[3]*o[3]);
};
template <class _tg> _tg _vektor4<_tg>::laenge() const{
                                                                return(sqrt(laengelaenge()));
};
template <class _tg> _tg _vektor4<_tg>::normalisieren(){
                                                                _tg l;
                                                                //-----
                                                                l=laenge();
                                                                if(l!=0){
                                                                 o[0]/=l;
                                                                 o[1]/=l;
                                                                 o[2]/=l;
                                                                 o[3]/=l;
                                                                }else{
                                                                 //error div(0)
                                                                };
                                                                return(l);
};
/*
template <class _tg> void _vektor4<_tg>::kreuzprodukt(const _vektor4<_tg>&v){
                                                                _tg e[2];
                                                                e[0]=v.o[1]*o[2] - v.o[2]*o[1];
                                                                e[1]=v.o[2]*o[0] - v.o[0]*o[2];
                                                                o[2]=v.o[0]*o[1] - v.o[1]*o[0];
                                                                o[0]=e[0];
                                                                o[1]=e[1];
};

template <class _tg> void _vektor4<_tg>::rotx(_tg w){
                                                                _tg y,z;
                                                                y=o[1]*cos(w*_ph)-o[2]*sin(w*_ph);
                                                                z=o[1]*sin(w*_ph)+o[2]*cos(w*_ph);
                                                                o[1]=y;
                                                                o[2]=z;
};
template <class _tg> void _vektor4<_tg>::roty(_tg w){
                                                                _tg y,z;
                                                                y=o[0]*cos(w*_ph)-o[2]*sin(w*_ph);
                                                                z=o[0]*sin(w*_ph)+o[2]*cos(w*_ph);
                                                                o[0]=y;
                                                                o[2]=z;
};
template <class _tg> void _vektor4<_tg>::rotz(_tg w){
                                                                _tg y,z;
                                                                y=o[0]*cos(w*_ph)-o[1]*sin(w*_ph);
                                                                z=o[0]*sin(w*_ph)+o[1]*cos(w*_ph);
                                                                o[0]=y;
                                                                o[1]=z;
};
*/
template <class _tg> void _vektor4<_tg>::begrenzen(_tg min,_tg max){
                                                                for(unsigned int i=0;i<4;i++){
                                                                 if(o[i]>max) o[i]=max;
                                                                 if(o[i]<min) o[i]=min;
                                                                };
};
template <class _tg> void _vektor4<_tg>::zufall(){
                                                                unsigned int i;
                                                                //---------------
                                                                do{
                                                                 for(i=0;i<4;i++){
                                                                  o[i]=_tg(rand())/_tg(RAND_MAX);
                                                                  o[i]-=0.5;
                                                                 };
                                                                }while(laengelaenge()==0);
                                                                normalisieren();
};
template <class _tg> _tg _vektor4<_tg>::winkel(const _vektor4<_tg>&v) const{
                                                                _tg n=laenge()*v.laenge();
                                                                //_vektor4<_tg> h=*this;
                                                                if(n>0){
                                                                 n=(*this*v)/n;
                                                                 if(n<-1)n=-1;
                                                                 if(n>+1)n=+1;
                                                                 return((acos(n)*180)/_pi);
                                                                }else{
                                                                  //error
                                                                 return(0);
                                                                };
};
template <class _tg> void _vektor4<_tg>::tauschen(unsigned int i0,unsigned int i1){
                                                                _tg h;
                                                                //-------
                                                                if(i0!=i1){
                                                                 if(i0<4){
                                                                  if(i1<4){
                                                                   h=o[i1];
                                                                   o[i1]=o[i0];
                                                                   o[i0]=h;
                                                                  };
                                                                 };
                                                                };
};
template <class _tg> _tg _vektor4<_tg>::produkt(const _vektor4<_tg>&v){
                                                                _tg r=0;
                                                                unsigned int i;
                                                                //-----
                                                                for(i=0;i<4;i++){
                                                                 o[i]*=v.o[i];
                                                                 r+=o[i];
                                                                };
                                                                return(r);
};
template <class _tg> __int32 _vektor4<_tg>::intargb()const{
                                                                __int32 i;
                                                                int a=int(o[3]*255);
                                                                int r=int(o[0]*255);
                                                                int g=int(o[1]*255);
                                                                int b=int(o[2]*255);
                                                                i=(a<<24)|(r<<16)|(g<<8)|b;
                                                                return(i);
};
/*template <class _tg> void _vektor4<_tg>::speichern(_datei*d){
                                                                d->speichern(o[0]);
                                                                d->speichern(o[1]);
                                                                d->speichern(o[2]);
                                                                d->speichern(o[3]);
};
template <class _tg> void _vektor4<_tg>::laden(_datei*d){
                                                                d->laden(o[0]);
                                                                d->laden(o[1]);
                                                                d->laden(o[2]);
                                                                d->laden(o[3]);
};*/



//*************************************************************************************************************************************************************************************************
//                                                              M A T R I X 4 4 
//*************************************************************************************************************************************************************************************************
template <class _tg> class _matrix44{
        public:
                _matrix44();
                _matrix44(const _matrix44&);
                _matrix44(const _tg ,const _tg,const _tg,const _tg,const _tg,const _tg,const _tg,const _tg,const _tg,const _tg,const _tg,const _tg,const _tg,const _tg,const _tg,const _tg);
                virtual ~_matrix44();
                 _tg*daten();
                _tg*setzendaten();
                void setzenidentitaet();
                void setzenprojektion(const _tg near_plane,const _tg far_plane,const _tg fov_horiz,const _tg fov_vert);
                void verschieben(const _vektor3<_tg>&v);
                inline const _tg*zeile(const unsigned int)const;
                inline _vektor4<_tg> vektor(const unsigned int);
                inline _tg spur()const;
                inline _matrix44<_tg>&operator=(const _matrix44<_tg>&);
                inline bool operator==(const _matrix44<_tg>&)const;
                inline _tg operator[](const unsigned int)const;
                inline _matrix44<_tg> operator*(const _tg) const;
                inline _matrix44<_tg>&operator*=(const _tg);                
                inline _matrix44<_tg> operator*(const _matrix44<_tg>&) const;
                inline _matrix44<_tg>&operator*=(const _matrix44<_tg>&);      
                inline _matrix44<_tg> operator+(const _matrix44<_tg>&) const;
                inline _matrix44<_tg>&operator+=(const _matrix44<_tg>&);      
                inline _matrix44<_tg> operator-(const _matrix44<_tg>&) const;
                inline _matrix44<_tg>&operator-=(const _matrix44<_tg>&);      
                inline void add(const _matrix44<_tg>&);
                inline void sub(const _matrix44<_tg>&);
                inline void mul(const _matrix44<_tg>&);
                inline void mul(const _tg);
        public:
                _tg pdaten[16];
                //_tg hdat[4];
};
template <class _tg> _matrix44<_tg>::_matrix44(){
                                                                setzenidentitaet();
                                                                //unsigned int i;
                                                                //for(i=0;i<16;i++) pdaten[i]=0;
};
template <class _tg> _matrix44<_tg>::_matrix44(const _matrix44<_tg>&m){
                                                                unsigned int i;
                                                                for(i=0;i<16;i++) pdaten[i]=m.pdaten[i];
};
template <class _tg> _matrix44<_tg>::_matrix44(const _tg x0,const _tg x1,const _tg x2,const _tg x3,const _tg y0,const _tg y1,const _tg y2,const _tg y3,const _tg z0,const _tg z1,const _tg z2,const _tg z3,const _tg w0,const _tg w1,const _tg w2,const _tg w3){
                                                                pdaten[0]=x0;
                                                                pdaten[1]=x1;
                                                                pdaten[2]=x2;
                                                                pdaten[3]=x3;
                                                                
                                                                pdaten[4]=y0;
                                                                pdaten[5]=y1;
                                                                pdaten[6]=y2;
                                                                pdaten[7]=y3;
                                                                
                                                                pdaten[8]= z0;
                                                                pdaten[9]= z1;
                                                                pdaten[10]=z2;
                                                                pdaten[11]=z3;
                                                                
                                                                pdaten[12]=w0;
                                                                pdaten[13]=w1;
                                                                pdaten[14]=w2;
                                                                pdaten[15]=w3;
                                                                
};
template <class _tg> _matrix44<_tg>::~_matrix44(){
};
template <class _tg>_tg* _matrix44<_tg>::setzendaten(){
                                                                return(pdaten);
};
template <class _tg> _tg* _matrix44<_tg>::daten(){
                                                                return(pdaten);
};
template <class _tg>void _matrix44<_tg>::setzenidentitaet(){

                                                                pdaten[0]=1;
                                                                pdaten[1]=0;
                                                                pdaten[2]=0;
                                                                pdaten[3]=0;
                                                                
                                                                pdaten[4]=0;
                                                                pdaten[5]=1;
                                                                pdaten[6]=0;
                                                                pdaten[7]=0;
                                                                
                                                                pdaten[8]= 0;
                                                                pdaten[9]= 0;
                                                                pdaten[10]=1;
                                                                pdaten[11]=0;
                                                                
                                                                pdaten[12]=0;
                                                                pdaten[13]=0;
                                                                pdaten[14]=0;
                                                                pdaten[15]=1;

};
template <class _tg>void _matrix44<_tg>::setzenprojektion(const _tg near_plane,const _tg far_plane,const _tg fov_horiz,const _tg fov_vert){
				                                                _tg h;
				                                                _tg w;
				                                                _tg Q;
			                                                    w = _tg(double(1.0f)/tan((double(fov_horiz)/2.0f)*double(_ph)));
			                                                    h = _tg(double(1.0f)/tan((double(fov_vert)/2.0f)*double(_ph)));
			                                                    Q = far_plane/(far_plane - near_plane);

                                                                pdaten[0]=0;
                                                                pdaten[1]=0;
                                                                pdaten[2]=0;
                                                                pdaten[3]=0;
                                                                
                                                                pdaten[4]=0;
                                                                pdaten[5]=0;
                                                                pdaten[6]=0;
                                                                pdaten[7]=0;
                                                                
                                                                pdaten[8]= 0;
                                                                pdaten[9]= 0;
                                                                pdaten[10]=0;
                                                                pdaten[11]=0;
                                                                
                                                                pdaten[12]=0;
                                                                pdaten[13]=0;
                                                                pdaten[14]=0;
                                                                pdaten[15]=0;

			                                                    pdaten[0]=w;
			                                                    pdaten[5]=h;
			                                                    pdaten[10]=Q;
			                                                    /*
			                                                    pdaten[11]=-Q*near_plane;//_43
			                                                    pdaten[14]=1;//_34
			                                                    */
			                                                    
			                                                    pdaten[14]=-Q*near_plane;//_43
			                                                    pdaten[11]=1;//_34
			                                                    
			                                                    };
template <class _tg> const _tg*_matrix44<_tg>::zeile(const unsigned int i)const{
                                                                unsigned int j=i;
                                                                if(j>3) j=3;
                                                                j*=4;
                                                                return(&pdaten[j]);
};
template <class _tg> _vektor4<_tg> _matrix44<_tg>::vektor(const unsigned int i){
                                                                unsigned int j=i;
                                                                if(j>3) j=3;
                                                                _vektor4<_tg> v(
                                                                pdaten[j+0],
                                                                pdaten[j+4],
                                                                pdaten[j+8],
                                                                pdaten[j+12]);
                                                                return(v);
};
template <class _tg> void _matrix44<_tg>::verschieben(const _vektor3<_tg>&v){
				                                                _matrix44<_tg> m;
				                                                
				                                                m.pdaten[12]=v.x();
				                                                m.pdaten[13]=v.y();
				                                                m.pdaten[14]=v.z();
				                                                (*this)*=m;
};	/*
			                                                
template <class _tg> void _matrix44<_tg>::skalieren(_tg f){
				                                                _matrix44<_tg> m;
				                                                
				                                                m.pdaten[0]=1*f;
				                                                m.pdaten[13]=v.y();
				                                                m.pdaten[14]=v.z();
				                                                (*this)*=m;
};	*/			                                                
template <class _tg> _tg _matrix44<_tg>::spur()const{
                                                                return(pdaten[0]+pdaten[5]+pdaten[10]+pdaten[15]);
};
template <class _tg> _matrix44<_tg>&_matrix44<_tg>::operator=(const _matrix44<_tg>&m){
                                                                unsigned int i;
                                                                for(i=0;i<16;i++)pdaten[i]=m.pdaten[i];
                                                                return(*this);
};
template <class _tg> bool _matrix44<_tg>::operator==(const _matrix44<_tg>&m)const{
                                                                for(unsigned int i=0;i<16;i++){
                                                                 if(pdaten[i]!=m.pdaten[i]) return(false);
                                                                };
                                                                return(true);
};
template <class _tg> _matrix44<_tg>  _matrix44<_tg>::operator*(const _tg x) const{
                                                                _matrix44<_tg> h(*this);
                                                                h.mul(x);
                                                                return(h);
};
template <class _tg> _matrix44<_tg>& _matrix44<_tg>::operator*=(const _tg x){
                                                                mul(x);
                                                                return(*this);
};
template <class _tg>_matrix44<_tg> _matrix44<_tg>::operator*(const _matrix44<_tg>&v) const{
	return (_matrix44<_tg>(	pdaten[0]*v.pdaten[0]+pdaten[4]*v.pdaten[1]+pdaten[8]*v.pdaten[2]+pdaten[12]*v.pdaten[3],
						    pdaten[1]*v.pdaten[0]+pdaten[5]*v.pdaten[1]+pdaten[9]*v.pdaten[2]+pdaten[13]*v.pdaten[3],
					    	pdaten[2]*v.pdaten[0]+pdaten[6]*v.pdaten[1]+pdaten[10]*v.pdaten[2]+pdaten[14]*v.pdaten[3],
						    pdaten[3]*v.pdaten[0]+pdaten[7]*v.pdaten[1]+pdaten[11]*v.pdaten[2]+pdaten[15]*v.pdaten[3],
						    pdaten[0]*v.pdaten[4]+pdaten[4]*v.pdaten[5]+pdaten[8]*v.pdaten[6]+pdaten[12]*v.pdaten[7],
						    pdaten[1]*v.pdaten[4]+pdaten[5]*v.pdaten[5]+pdaten[9]*v.pdaten[6]+pdaten[13]*v.pdaten[7],
						    pdaten[2]*v.pdaten[4]+pdaten[6]*v.pdaten[5]+pdaten[10]*v.pdaten[6]+pdaten[14]*v.pdaten[7],
						    pdaten[3]*v.pdaten[4]+pdaten[7]*v.pdaten[5]+pdaten[11]*v.pdaten[6]+pdaten[15]*v.pdaten[7],
					    	pdaten[0]*v.pdaten[8]+pdaten[4]*v.pdaten[9]+pdaten[8]*v.pdaten[10]+pdaten[12]*v.pdaten[11],
					    	pdaten[1]*v.pdaten[8]+pdaten[5]*v.pdaten[9]+pdaten[9]*v.pdaten[10]+pdaten[13]*v.pdaten[11],
					    	pdaten[2]*v.pdaten[8]+pdaten[6]*v.pdaten[9]+pdaten[10]*v.pdaten[10]+pdaten[14]*v.pdaten[11],
					    	pdaten[3]*v.pdaten[8]+pdaten[7]*v.pdaten[9]+pdaten[11]*v.pdaten[10]+pdaten[15]*v.pdaten[11],
					    	pdaten[0]*v.pdaten[12]+pdaten[4]*v.pdaten[13]+pdaten[8]*v.pdaten[14]+pdaten[12]*v.pdaten[15],
					    	pdaten[1]*v.pdaten[12]+pdaten[5]*v.pdaten[13]+pdaten[9]*v.pdaten[14]+pdaten[13]*v.pdaten[15],
					    	pdaten[2]*v.pdaten[12]+pdaten[6]*v.pdaten[13]+pdaten[10]*v.pdaten[14]+pdaten[14]*v.pdaten[15],
					    	pdaten[3]*v.pdaten[12]+pdaten[7]*v.pdaten[13]+pdaten[11]*v.pdaten[14]+pdaten[15]*v.pdaten[15]));                                                                
};                                                                
template <class _tg>_matrix44<_tg>&_matrix44<_tg>::operator*=(const _matrix44<_tg>&v){
                                                                mul(v);
                                                                return(*this);
};
template <class _tg> _matrix44<_tg>  _matrix44<_tg>::operator+(const _matrix44<_tg>&v) const{
                                                                _matrix44<_tg> h(*this);
                                                                h.add(v);
                                                                return(h);
};
template <class _tg> _matrix44<_tg>& _matrix44<_tg>::operator+=(const _matrix44<_tg>&v){
                                                                add(v);
                                                                return(*this);
};
template <class _tg> _matrix44<_tg>  _matrix44<_tg>::operator-(const _matrix44<_tg>&v) const{
                                                                _matrix44<_tg> h(*this);
                                                                h.sub(v);
                                                                return(h);
};
template <class _tg> _matrix44<_tg>& _matrix44<_tg>::operator-=(const _matrix44<_tg>&v){
                                                                sub(v);
                                                                return(*this);
};
template <class _tg> _tg _matrix44<_tg>::operator[](const unsigned int i)const{
                                                                return(pdaten[i]);
};
template <class _tg> void _matrix44<_tg>::mul(const _matrix44<_tg>&v){
                                                                _matrix44<_tg> h(*this);
                                                                unsigned int j,o;
                                                                for(o=0;o<16;o+=4)//zeile
                                                                for(j=0;j<4;j++){//spalte
                                                                 pdaten[j+o]=h.pdaten[o+0]*v.pdaten[j+0] + 
                                                                             h.pdaten[o+1]*v.pdaten[j+4] + 
                                                                             h.pdaten[o+2]*v.pdaten[j+8] + 
                                                                             h.pdaten[o+3]*v.pdaten[j+12];
                                                                };
};
template <class _tg> void _matrix44<_tg>::mul(const _tg x){
                                                                unsigned int i;
                                                                for(i=0;i<16;i++) pdaten[i]*=x;
};                                                                
template <class _tg> void _matrix44<_tg>::add(const _matrix44<_tg>&v){
                                                                unsigned int i;
                                                                for(i=0;i<16;i++) pdaten[i]+=v.pdaten[i];
};
template <class _tg> void _matrix44<_tg>::sub(const _matrix44<_tg>&v){
                                                                unsigned int i;
                                                                for(i=0;i<16;i++) pdaten[i]-=v.pdaten[i];
};
//*************************************************************************************************************************************************************************************************
//                                                              V E C T O R R O O M
//*************************************************************************************************************************************************************************************************
template <class _tg> class _vektorraum:public _vektor<_tg>{
        using _vektor<_tg>::setzen;
        public:
                _vektorraum();
                _vektorraum(_vektor<_tg>&,_vektor<_tg>&,_vektor<_tg>&,_vektor<_tg>&);
                //_vektorraum(_tg,_tg,_tg, _tg,_tg,_tg, _tg,_tg,_tg, _tg,_tg,_tg);
                //_vektorraum(_vektor<_tg>&,_vektor<_tg>&,_vektor<_tg>&,_vektor<_tg>&);

                virtual ~_vektorraum();
                /*
                void setzen(_tg,_tg,_tg, _tg,_tg,_tg, _tg,_tg,_tg, _tg,_tg,_tg);
                void setzen(_vektor<_tg>&,_vektor<_tg>&,_vektor<_tg>&,_vektor<_tg>&);
                */
                //_vektor<_tg> o() const;
                _vektor<_tg> x() const;
                _vektor<_tg> y() const;
                _vektor<_tg> z() const;
                //void o(_vektor<_tg>&);
                void x(_vektor<_tg>&);
                void y(_vektor<_tg>&);
                void z(_vektor<_tg>&);
                void setzen(_vektor<_tg>&,_vektor<_tg>&,_vektor<_tg>&,_vektor<_tg>&);

                inline void exportvector(_vektor<_tg>&) const;         //konversion von normalen (statischen) vektor<> zu vektor<> des ausseren systems
              // inline void exportvector(_vectordynamic<_tg>&) const; //konversion von _vectordynamiclist<> zu _vektor<> des äusseren systems
                inline void importvector(_vektor<_tg>&) const;         //konversion eines _vektor<> des äusseren system zu vektor<> der verschachtelung
               // void importvector(_vectordynamic<_tg>&) const; //konversion eines _vectordynamiclist<> des äusseren system zu vektor<> der verschachtelung

                bool transformation() const;
                void transformation(bool);

        private:
               //_vektor<_tg> po;
                _vektor<_tg> px;
                _vektor<_tg> py;
                _vektor<_tg> pz;
                bool ptransformate;
};

template <class _tg> _vektorraum<_tg>::_vektorraum(){
                                                                _vektor<_tg>::setzen(0,0,0);
                                                                px.setzen(1,0,0);
                                                                py.setzen(0,1,0);
                                                                pz.setzen(0,0,1);
                                                                ptransformate=false;
};
template <class _tg> _vektorraum<_tg>::_vektorraum(_vektor<_tg>&oo,_vektor<_tg>&xx,_vektor<_tg>&yy,_vektor<_tg>&zz):_vektor<_tg>(oo),px(xx),py(yy),pz(zz){
                                                                ptransformate=false;
};
/*template <class _tg> _vektorraum<_tg>::_vektorraum(_tg ox,_tg oy,_tg oz, _tg ax,_tg ay, _tg az, _tg bx,_tg by,_tg bz, _tg cx,_tg cy,_tg cz):o(ox,oy,oz),x(ax,ay,az),y(bx,by,bz),z(cx,cy,cz){
};
template <class _tg> _vektorraum<_tg>::_vektorraum(_vektor<_tg>&_o,_vektor<_tg>&_a,_vektor<_tg>&_b,_vektor<_tg>&_c):o(_o),x(_a),y(_b),z(_c){
};
*/
template <class _tg> _vektorraum<_tg>::~_vektorraum(){
};

/*
template <class _tg> _vektor<_tg> _vektorraum<_tg>::o() const{
                                                                return(o);
};
*/
template <class _tg> _vektor<_tg> _vektorraum<_tg>::x() const{
                                                                return(px);
};
template <class _tg> _vektor<_tg> _vektorraum<_tg>::y() const{
                                                                return(py);
};
template <class _tg> _vektor<_tg> _vektorraum<_tg>::z() const{
                                                                return(pz);
};

/*
template <class _tg> void _vektorraum<_tg>::o(_vektor<_tg>&oo){
                                                                o=oo;
};
*/
template <class _tg> void _vektorraum<_tg>::x(_vektor<_tg>&xx){
                                                                px=xx;
};
template <class _tg> void _vektorraum<_tg>::y(_vektor<_tg>&yy){
                                                                py=yy;
};
template <class _tg> void _vektorraum<_tg>::z(_vektor<_tg>&zz){
                                                                pz=zz;
};
template <class _tg> void _vektorraum<_tg>::setzen(_vektor<_tg>&oo,_vektor<_tg>&xx,_vektor<_tg>&yy,_vektor<_tg>&zz){
                                                                setzen(oo);
                                                                px=xx;
                                                                py=yy;
                                                                pz=zz;
};
template <class _tg> void _vektorraum<_tg>::exportvector(_vektor<_tg>&v) const{
                                                                if(ptransformate) {
                                                                }else{
                                                                 v+=*this;
                                                                };
};
template <class _tg> void _vektorraum<_tg>::importvector(_vektor<_tg>&v) const{
                                                                if(ptransformate) {
                                                                }else{
                                                                 v-=*this;
                                                                };
};
template <class _tg> bool _vektorraum<_tg>::transformation() const{
                                                                return(ptransformate);
};
template <class _tg> void _vektorraum<_tg>::transformation(bool b){
                                                                ptransformate=b;
};











                 /*


template <class _tg> void _vektorraum<_tg>::setzen(_tg ox,_tg oy,_tg oz, _tg ax,_tg ay, _tg az, _tg bx,_tg by,_tg bz, _tg cx,_tg cy,_tg cz){
                                                                o.setzen(ox,oy,oz);
                                                                x.setzen(ax,ay,az);
                                                                y.setzen(bx,by,bz);
                                                                z.setzen(cx,cy,cz);
};
template <class _tg> void _vektorraum<_tg>::setzen(_vektor<_tg>&_o,_vektor<_tg>&_a,_vektor<_tg>&_b,_vektor<_tg>&_c){
                                                                o.kopieren(_o);
                                                                x.kopieren(_a);
                                                                y.kopieren(_b);
                                                                z.kopieren(_c);
};
template <class _tg> _vektor<_tg> _vektorraum<_tg>::o() const{
                                                                return(po);
};
template <class _tg> _vektor<_tg> _vektorraum<_tg>::x() const{
                                                                return(px);
};
template <class _tg> _vektor<_tg> _vektorraum<_tg>::y() const{
                                                                return(py);
};
template <class _tg> _vektor<_tg> _vektorraum<_tg>::z() const{
                                                                return(pz);
};     */

#endif
