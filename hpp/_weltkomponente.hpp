//******************************************************************************************************************************************************************************************************
//  Project     : grundplatte
//  Library     : _grundplatte.lib
//  Module      : _weltkomponente.hpp
//  Date        : 10.01.2006
//  Description : 
//******************************************************************************************************************************************************************************************************

#ifndef _weltkomponenteh_included
#define _weltkomponenteh_included


template<class _tg=typgeometrie> class _kamera;
template<class _tg=typgeometrie,class _to=typoptik> class _licht;
template<class _tg=typgeometrie,class _to=typoptik> class _schatten;

template<class _tg=typgeometrie> class _gravitation;
template<class _tg=typgeometrie> class _feldmagnetostatisch;
template<class _tg=typgeometrie> class _feldelektrostatisch;

//*********************************************************************************************************************************************************************************
//                                                                F O R W A R D D E K L A R A T I O N
//*********************************************************************************************************************************************************************************
#include <_global.hpp>
#include <_struktur.hpp>
#include <_vektor.hpp>
#include <_grafik.hpp>
#include <_bild.hpp>
#include <_system.hpp>
#include <_editionwin.hpp>
#include <_weltfeld.hpp>


//NOCH EINGBUNDEN , weil grafik nicht vollständig:
#include <_grafikopengl.hpp>

//******************************************************************************************************************************************************************************************************
//                                                              K A M E R A 
//******************************************************************************************************************************************************************************************************
template<class _tg> class _kamera:public _listenknotenbasis<_kamera<_tg> >,public _vektor3<_tg>,public _basis::_speicherbarargument<_kamera<_tg> >,public _speicherbarbinaer{
        public:
                _kamera(_listebasis<_kamera<_tg> >*);
                virtual ~_kamera();
                void markierung(const int i);
                int markierung()const;
                void orthonormal(const bool);
                bool orthonormal()const;
                void aktualisieren();
                void bewegen(_tastatur*,_maus<_tg>*,_tg);
                void bewegen(_tastatur*kb,const _vektor3<_tg>&m,_tg pf);
                void bewegen(_tastatur*kb,const _vektor2<_tg>&m,_tg pf);
                _vektor3<_tg> bewegungsvektor(_tastatur*,_tg);
                _vektor2<_tg> bewegungrotation(_maus<_tg>*);
                void bewegen(const _vektor3<_tg>&);
                
                void rotieren(const _vektor2<_tg>&);
                inline void transformierenparallel(_vektor3<_tg>&)const;
                inline void transformierenperspektive(_vektor3<_tg>&)const;
                template<class _tm> void ladenmatrix(_matrix44<_tm>*,_matrix44<_tm>*,_tg fov0=0,_tg fov1=0)const;
                //lesen
                _vektor3<_tg>&ort();
                _vektor3<_tg>&vektor();
                _vektor3<_tg>&ebene(unsigned int);
                _vektor3<_tg>&ebenenormalisiert(unsigned int);
                _tg laenge() const;
                _tg groesse(unsigned int) const;
               // _tg rot() const;
               // _tg yaw() const;
               // _tg rol() const;
                inline _tg sinrot() const;
                inline _tg sinyaw() const;
                inline _tg sinrol() const;
                inline _tg cosrot() const;
                inline _tg cosyaw() const;
                inline _tg cosrol() const;
                _tg fov(unsigned int i)const;
                //schreiben
                void ort(const _vektor3<_tg>&);
                void vektor(const _vektor3<_tg>&);
                void vektor(const _tg x,const _tg y,const _tg z);
                void ebene0(const _vektor3<_tg>&);
                void ebene(unsigned int i,const _vektor3<_tg>&);
                void ebene(unsigned int i,const _tg x,const _tg y,const _tg z);
                void vektorebene0(const _vektor3<_tg>&v,const _vektor3<_tg>&e0);
                void laenge(_tg);
                void groesse(_tg,_tg);
                void rot(_tg);
                void yaw(_tg);
                void rol(_tg);
              //  void rotation(const _vektor3<_tg>&);
               // inline void rotrelativ(_tg);
               // inline void yawrelativ(_tg);
               // inline void rolrelativ(_tg);
               // inline _tg rotrelativ()const;
               // inline _tg yawrelativ()const;
               // inline _tg rolrelativ()const;
              //  void rotationrelative(const _vektor3<_tg>&);
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_kamera>*);
                void speichern(_speicherbardynamisch<_kamera>*);
                char assoziieren(_speicherbardynamisch<_kamera>*);
                
                bool laden(_dateispeicherbarbinaer*);
                void speichern(_dateispeicherbarbinaer*);
                bool assoziieren();
                
        private:
                //_vektor3<_tg> plocus;         
                _vektor3<_tg> pvector;
                _vektor3<_tg> pplane[2];
                _vektor3<_tg> pplanen[2];
               // _vektor3<_tg> protation;
              //  _vektor3<_tg> protationrelative;
                _tg psinrot;
                _tg psinrol;
                _tg psinyaw;
                _tg pcosrot;
                _tg pcosrol;
                _tg pcosyaw;
                _tg pvectorlength;
                _tg pplanelength[2];
                _tg pspeed;
                unsigned int poldtime;
                _tg pfactor;
                int pmarkierung;
                bool porthonormal;
               
};
template<class _tg> _kamera<_tg>::_kamera(_listebasis<_kamera<_tg> >*lc):_listenknotenbasis<_kamera<_tg> >(lc){    
                                                                poldtime=0;
                                                                pmarkierung=0;                                    
                                                                //plocus.setzen(0,0,0);
                                                                pvectorlength=1;
                                                                pvector.setzen(0,0,pvectorlength);
                                                                pplanelength[0]=0.5;
                                                                pplanelength[1]=0.5;
                                                                pplane[0].setzen(pplanelength[0],0,0);
                                                                pplane[1].setzen(0,pplanelength[1],0);
                                                                pplanen[0]=pplane[0];
                                                                pplanen[0].normalisieren();
                                                                pplanen[1]=pplane[1];
                                                                pplanen[1].normalisieren();
                                                             //   protation.setzen(0,0,0);
                                                              //  protationrelative.setzen(0,0,0);
                                                                aktualisieren();
                                                                pspeed=1;
                                                                pfactor=1;
                                                                porthonormal=false;
};
template<class _tg> _kamera<_tg>::~_kamera(){ 
};
template<class _tg>void _kamera<_tg>::markierung(const int i){
                                                                pmarkierung=i;
};
template<class _tg>int _kamera<_tg>::markierung()const{
                                                                return(pmarkierung);
};
template<class _tg> void _kamera<_tg>::orthonormal(const bool b){
                                                                porthonormal=b;
};
template<class _tg> bool _kamera<_tg>::orthonormal()const{
                                                                return(porthonormal);
};
template<class _tg> void _kamera<_tg>::aktualisieren(){
                                                                //_tg rx,ry,rz;
                                                                //_tg ph=_pi/180.0f;
                                                                
                                                               // _tg lv,lp0,lp1;
                                                                //-------------------------
                                                             /*   pvector.setzen(0,sin(protation[1]*_ph),cos(protation[1]*_ph));
                                                                pplane[1].setzen(0,sin((90+protation[1])*_ph),cos((90+protation[1])*_ph));
                                                                pvector.roty(-protation[0]);
                                                                pplane[1].roty(-protation[0]);
                                                                pplane[0]=pplane[1]%pvector;
                                                                
                                                                pvector*=pvectorlength;
                                                                pplane[0]*=pplanelength[0];
                                                                pplane[1]*=pplanelength[1];
                                                                
                                                                pplanen[0]=pplane[0];
                                                                pplanen[0].normalisieren();
                                                                pplanen[1]=pplane[1];
                                                                pplanen[1].normalisieren();
                                                                
                                                                */
                                                                
                                                          
                                                          //      psinrot=sin(_ph*(protation[0]+protationrelative[0]));                                                                                                 
                                                          //      psinrol=sin(_ph*(protation[2]+protationrelative[2]));                                                                                                 
                                                          //      psinyaw=sin(_ph*(protation[1]+protationrelative[1]));
                                                          //      pcosrot=cos(_ph*(protation[0]+protationrelative[0]));                                                                                               
                                                          //      pcosrol=cos(_ph*(protation[2]+protationrelative[2]));                                                                                               
                                                          //      pcosyaw=cos(_ph*(protation[1]+protationrelative[1]));
                                                              
};
template<class _tg> _vektor3<_tg> _kamera<_tg>::bewegungsvektor(_tastatur*kb,_tg pf){
                                                                //unsigned int nt;
                                                                _tg s=0.08*pspeed;
                                                                _vektor3<_tg> v;
                                                                _vektor3<_tg> r;
                                                                int i=0;
                                                                //unsigned int dt;
                                                                //-------------
                                                                v.setzen(0,0,0);
                                                                r.setzen(0,0,0);

                                                                
                                                                //t->animieren();
                                                                //nt=t->system();
                                                                //dt=(nt-poldtime);
                                                                //poldtime=nt;
                                                                //pfactor=(_tg(dt)/16.666666666666666667f);
                                                                pfactor=pf;
                                                                
                                                                
                                                                s*=pfactor;
                                                                //----------------
                                                                if(kb->shift()) s*=8;
                                                                if(kb->pfeilhoch()){
                                                                 v=pvector;
                                                                 v.normalisieren();
                                                                 v*=s;
                                                                 // *this+=v;
                                                                 i|=1;
                                                                 r+=v;
                                                                };
                                                                if(kb->pfeilrunter()){
                                                                 v=pvector;
                                                                 v.normalisieren();
                                                                 v*=-s;
                                                                 // *this-=v;
                                                                 i|=1;
                                                                 r+=v;
                                                                };
                                                                if(kb->pfeillinks()){
                                                                 v=pplane[0];
                                                                 v.normalisieren();
                                                                 v*=-s;
                                                                 // *this+=v;
                                                                 i|=1;
                                                                 r+=v;
                                                                };
                                                                if(kb->pfeilrechts()){
                                                                 v=pplane[0];
                                                                 v.normalisieren();
                                                                 v*=+s;
                                                                 // *this-=v;
                                                                 i|=1;
                                                                 r+=v;
                                                                };
                                                                if(i==1){
                                                                 pspeed*=1;
                                                                }else{ 
                                                                 pspeed=1;
                                                                };/*
                                                                L->schreiben("rot=",protation[0]);
                                                                L->schreiben("yaw=",protation[1]);
                                                                L->schreiben("pvector  =",pvector);
                                                                L->schreiben("pplane[0]=",pplane[0]);
                                                                L->schreiben("pplane[1]=",pplane[1]);
                                                                */
                                                                return(r);
                                                                
};

template<class _tg> _vektor2<_tg> _kamera<_tg>::bewegungrotation(_maus<_tg>*mo){
                                                                _vektor3<_tg> m;
                                                                _tg ms=0.1;
                                                               //------------
                                                                m=mo->holen()*ms;//*pfactor;
																return(_vektor2<_tg>(m[0],m[1]));
};
template<class _tg> void _kamera<_tg>::bewegen(_tastatur*kb,_maus<_tg>*mo,_tg pf){
                                                                _vektor2<_tg> m;
                                                                _vektoranalysis3<_tg> V3;
                                                                _vektor3<_tg> e;
                                                                _vektor3<_tg> vektoralt=pvector;
                                                                _vektor3<_tg> plane0alt=pplanen[0];
                                                                _vektor3<_tg> plane1alt=pplanen[1];
                                                                _vektor3<_tg> ya(0,1,0);
                                                                //-----------------
                                                                *this+=bewegungsvektor(kb,pf);    
                                                                m=bewegungrotation(mo);
                                                                V3.rotieren(plane0alt,pvector,m[1],e);
                                                                pvector=e;
                                                                V3.rotieren(ya,pvector,-m[0],e);
                                                                pvector=e;
                                                                V3.rotieren(ya,pplanen[0],-m[0],e);
                                                                pplanen[0]=e;
                                                                pplanen[0].setzenkomponente(1,0);
                                                                V3.rotieren(ya,pplanen[1],-m[0],e);
                                                                pplanen[1]=e;
                                                                
                                                                
                                                                V3.rotieren(plane0alt,pplanen[1],m[1],e);
                                                                pplanen[1]=e;
                                                                pplanen[1].normalisieren();
                                                                
                                                            /*    V3.rotieren(plane1alt,pplanen[1],-m[0],e);
                                                                pplanen[1]=e;
                                                                pplanen[1].normalisieren();
                                                                */
                                                                
                                                                
                                                                //unschärfe kompensieren
                                                                pvector.normalisieren();
                                                                pplanen[1]=pvector%pplanen[0];
                                                                pplanen[1].normalisieren();
                                                                pplanen[0]=pplanen[1]%pvector;
                                                                pplanen[0].normalisieren();
                                                               
                                                                pvector*=pvectorlength;
                                                                pplane[0]=pplanen[0]*pplanelength[0];
                                                                pplane[1]=pplanen[1]*pplanelength[1];
                                                                
                                                                
                                                                //V3.rotieren(pvector,plane1alt,m[0],e);
                                                                //pvector=e;
                                                                
                                                                
                                                                //pvector.rotx(m[1]);
                                                                //pvector.roty(m[0]);
                                                                //pplane[0].rotx(m[1]);
                                                                //pplane[0].roty(m[0]);
                                                                //pplane[1].rotx(m[1]);
                                                                //pplane[1].roty(m[0]);
                                                                
                                                                //pplanen[0].normalisieren();
                                                                //pplanen[1].normalisieren();
                                                               // protation.add(0,m[0]);
                                                                //protation.add(1,m[1]);
                                                                aktualisieren();
                                                                
};
template<class _tg> void _kamera<_tg>::bewegen(_tastatur*kb,const _vektor3<_tg>&m,_tg pf){
																_vektor2<_tg> v(m[0],m[1]);
																bewegen(kb,v,pf);
};
template<class _tg> void _kamera<_tg>::bewegen(_tastatur*kb,const _vektor2<_tg>&m,_tg pf){
                                                                _vektoranalysis3<_tg> V3;
                                                                _vektor3<_tg> e;
                                                                _vektor3<_tg> vektoralt=pvector;
                                                                _vektor3<_tg> plane0alt=pplanen[0];
                                                                _vektor3<_tg> plane1alt=pplanen[1];
                                                                _vektor3<_tg> ya(0,1,0);
                                                                //-----------------
                                                                *this+=bewegungsvektor(kb,pf);    
                                                               // m=bewegungrotation(mo);
                                                                V3.rotieren(plane0alt,pvector,m[1],e);
                                                                pvector=e;
                                                                V3.rotieren(ya,pvector,-m[0],e);
                                                                pvector=e;
                                                                V3.rotieren(ya,pplanen[0],-m[0],e);
                                                                pplanen[0]=e;
                                                                pplanen[0].setzenkomponente(1,0);
                                                                V3.rotieren(ya,pplanen[1],-m[0],e);
                                                                pplanen[1]=e;
                                                                V3.rotieren(plane0alt,pplanen[1],m[1],e);
                                                                pplanen[1]=e;
                                                                pplanen[1].normalisieren();
                                                                
                                                                //unschärfe kompensieren
                                                                pvector.normalisieren();
                                                                pplanen[1]=pvector%pplanen[0];
                                                                pplanen[1].normalisieren();
                                                                pplanen[0]=pplanen[1]%pvector;
                                                                pplanen[0].normalisieren();
                                                                pvector*=pvectorlength;
                                                                pplane[0]=pplanen[0]*pplanelength[0];
                                                                pplane[1]=pplanen[1]*pplanelength[1];
                                                                aktualisieren();
                                                                
};
template<class _tg> void _kamera<_tg>::bewegen(const _vektor3<_tg>&m){
                                                                
          
                                                                *this+=m;
};
template<class _tg> void _kamera<_tg>::rotieren(const _vektor2<_tg>&r){
                                                                //protation.add(0,r[0]);
                                                                //protation.add(1,r[1]);
                                                             /*   pvector.rotx(r[1]);
                                                                pvector.roty(r[0]);
                                                                pplane[0].rotx(r[1]);
                                                                pplane[0].roty(r[0]);
                                                                pplane[1].rotx(r[1]);
                                                                pplane[1].roty(r[0]);
                                                                pplanen[0]=pplane[0];
                                                                pplanen[1]=pplane[1];
                                                                pplanen[0].normalisieren();
                                                                pplanen[1].normalisieren();*/
};
template<class _tg> _vektor3<_tg>&_kamera<_tg>::ort(){
                                                                return(*this);   
};
template<class _tg> _vektor3<_tg>&_kamera<_tg>::vektor(){
                                                                return(pvector);   
};
template<class _tg> _vektor3<_tg>&_kamera<_tg>::ebene(unsigned int i){
                                                                if(i==0) return(pplane[0]); else return(pplane[1]);
};
template<class _tg> _vektor3<_tg>&_kamera<_tg>::ebenenormalisiert(unsigned int i){
                                                                if(i==0) return(pplanen[0]); else return(pplanen[1]);
};
template<class _tg> _tg _kamera<_tg>::laenge() const{
                                                                return(pvector.laenge());
};
template<class _tg> _tg _kamera<_tg>::groesse(unsigned int i) const{
                                                                if(i==0) return(pplane[0].laenge()); else return(pplane[1].laenge());
};
/*
template<class _tg> _tg _kamera<_tg>::rot() const{
                                                                return(protation[0]+protationrelative[0]);
};
template<class _tg> _tg _kamera<_tg>::yaw() const{
                                                                return(protation[1]+protationrelative[1]);
};
template<class _tg> _tg _kamera<_tg>::rol() const{
                                                                return(protation[2]+protationrelative[2]);
};*/
template<class _tg> _tg _kamera<_tg>::sinrot() const{
                                                                return(psinrot);
};
template<class _tg> _tg _kamera<_tg>::sinyaw() const{
                                                                return(psinyaw);
};
template<class _tg> _tg _kamera<_tg>::sinrol() const{
                                                                return(psinrol);
};
template<class _tg> _tg _kamera<_tg>::cosrot() const{
                                                                return(pcosrot);
};
template<class _tg> _tg _kamera<_tg>::cosyaw() const{
                                                                return(pcosyaw);
};
template<class _tg> _tg _kamera<_tg>::cosrol() const{
                                                                return(pcosrol);
};
template<class _tg> _tg _kamera<_tg>::fov(unsigned int i)const{
                                                                _tg f;
                                                                _vektor3<_tg> h;
                                                                if(i==0){
                                                                 h=pvector+pplane[1];
                                                                 f=pvector.winkel(h)*2;
				                                                 return(f);
                                                                }else{
                                                                 h=pvector+pplane[0];
                                                                 f=pvector.winkel(h)*2;
                                                                 return(f);
                                                                };
};

template<class _tg> void _kamera<_tg>::ort(const _vektor3<_tg>&l){
                                                                kopieren(l);
};
template<class _tg> void _kamera<_tg>::vektor(const _tg x,const _tg y,const _tg z){
                                                                vektor(_vektor3<_tg>(x,y,z));
};
template<class _tg> void _kamera<_tg>::vektor(const _vektor3<_tg>&v){
                                                                _vektor3<_tg> xa(1,0,0);
                                                                _vektor3<_tg> ya(0,1,0);
                                                                _vektor3<_tg> za(0,0,1);
                                                                _vektor3<_tg> t;
                                                                //_tg w;
                                                                //----------------
                                                                pvector=v;
                                                                
                                                                //unschärfe kompensieren
                                                                pvector.normalisieren();
                                                                pplanen[1]=pvector%pplanen[0];
                                                                pplanen[1].normalisieren();
                                                                pplanen[0]=pplanen[1]%pvector;
                                                                //pplanen[0].setzenkomponente(1,0);
                                                                pplanen[0].normalisieren();
                                                                pplanen[1]=pvector%pplanen[0];
                                                                pplanen[1].normalisieren();
                                                               
                                                                pvector*=pvectorlength;
                                                                pplane[0]=pplanen[0]*pplanelength[0];
                                                                pplane[1]=pplanen[1]*pplanelength[1];
                                                               // protation.setzenkomponente(1,-w);
                                                                aktualisieren();
};
template<class _tg> void _kamera<_tg>::ebene0(const _vektor3<_tg>&v){
                                                                _vektor3<_tg> xa(1,0,0);
                                                                _vektor3<_tg> ya(0,1,0);
                                                                _vektor3<_tg> za(0,0,1);
                                                                _vektor3<_tg> t;
                                                                //_tg w;
                                                                //----------------
                                                                pplanen[0]=v;
                                                                
                                                                //unschärfe kompensieren
                                                                pplanen[0].normalisieren();
                                                                pvector=pplanen[0]%pplanen[1];
                                                                pvector.normalisieren();
                                                                
                                                                
                                                                pplanen[1]=pvector%pplanen[0];
                                                                pplanen[1].normalisieren();
                                                                //pplanen[0]=pplanen[1]%pvector;
                                                                pplanen[0].setzenkomponente(1,0);
                                                                pplanen[0].normalisieren();
                                                                pplanen[1]=pvector%pplanen[0];
                                                                pplanen[1].normalisieren();
                                                               
                                                                pvector*=pvectorlength;
                                                                pplane[0]=pplanen[0]*pplanelength[0];
                                                                pplane[1]=pplanen[1]*pplanelength[1];
                                                               // protation.setzenkomponente(1,-w);
                                                                aktualisieren();
};
template<class _tg> void _kamera<_tg>::ebene(const unsigned int i,const _tg x,const _tg y,const _tg z){//nur setzen, nicht aktualisieren
                                                                ebene(i,_vektor3<_tg>(x,y,z));
};
template<class _tg> void _kamera<_tg>::ebene(const unsigned int i,const _vektor3<_tg>&v){//nur setzen, nicht aktualisieren
                                                                if(i==0){
                                                                 pplanen[0]=v;
                                                                 pplanen[0].normalisieren();
                                                                 pplane[0]=pplanen[0]*pplanelength[0];
                                                                }else{
                                                                 pplanen[1]=v;
                                                                 pplanen[1].normalisieren();
                                                                 pplane[1]=pplanen[1]*pplanelength[1];
                                                                };
};
template<class _tg> void _kamera<_tg>::vektorebene0(const _vektor3<_tg>&v,const _vektor3<_tg>&e0){
                                                                pvector=v;
                                                                pvector.normalisieren();
                                                                pplanen[0]=e0;
                                                                pplanen[0].normalisieren();
                                                                pplanen[1]=pvector%pplanen[0];
                                                                pplanen[1].normalisieren();
                                                                
                                                                pvector*=pvectorlength;
                                                                pplane[0]=pplanen[0]*pplanelength[0];
                                                                pplane[1]=pplanen[1]*pplanelength[1];
                                                                aktualisieren();
};
template<class _tg> void _kamera<_tg>::laenge(_tg l){
                                                                if(l!=0){
                                                                 pvectorlength=l;
                                                                 pvector.normalisieren();
                                                                 pvector*=l;
                                                                };
};
template<class _tg> void _kamera<_tg>::groesse(_tg wx,_tg wy){
                                                                if(wx!=0){
                                                                 pplanelength[0]=wx;
                                                                 pplane[0].normalisieren();
                                                                 pplanen[0]=pplane[0];
                                                                 pplane[0]*=wx;
                                                                };
                                                                if(wy!=0){
                                                                 pplanelength[1]=wy;
                                                                 pplane[1].normalisieren();
                                                                 pplanen[1]=pplane[1];
                                                                 pplane[1]*=wy;
                                                                };
};
template<class _tg> void _kamera<_tg>::rot(_tg r){
                                                                pvector.roty(r);
                                                                pplane[0].roty(r);
                                                                pplane[1].roty(r);
                                                                pplanen[0]=pplane[0];
                                                                pplanen[1]=pplane[1];
                                                                pplanen[0].normalisieren();
                                                                pplanen[1].normalisieren();
                                                                //protation.setzenkomponente(0,r);
                                                                aktualisieren();
};
template<class _tg> void _kamera<_tg>::yaw(_tg r){
                                                                pvector.rotx(r);
                                                                pplane[0].rotx(r);
                                                                pplane[1].rotx(r);
                                                                pplanen[0]=pplane[0];
                                                                pplanen[1]=pplane[1];
                                                                pplanen[0].normalisieren();
                                                                pplanen[1].normalisieren();
                                                                //protation.setzenkomponente(1,r);
                                                                aktualisieren();
};
template<class _tg> void _kamera<_tg>::rol(_tg r){
                                                               // protation.setzenkomponente(2,r);
                                                                aktualisieren();
};/*
template<class _tg> void _kamera<_tg>::rotation(const _vektor3<_tg>&r){
                                                                protation=r;
                                                                aktualisieren();
};
template<class _tg> void _kamera<_tg>::rotrelativ(_tg r){
                                                                protationrelative.setzenkomponente(0,r);
                                                                aktualisieren();
};
template<class _tg> void _kamera<_tg>::yawrelativ(_tg r){
                                                                protationrelative.setzenkomponente(1,r);
                                                                aktualisieren();
};
template<class _tg> void _kamera<_tg>::rolrelativ(_tg r){
                                                                protationrelative.setzenkomponente(2,r);
                                                                aktualisieren();
};
template<class _tg> _tg _kamera<_tg>::rotrelativ()const{
                                                                return(protationrelative[0]);
};
template<class _tg> _tg _kamera<_tg>::yawrelativ()const{
                                                                return(protationrelative[1]);
};
template<class _tg> _tg _kamera<_tg>::rolrelativ()const{
                                                                return(protationrelative[2]);
};
template<class _tg> void _kamera<_tg>::rotationrelative(const _vektor3<_tg>&r){
                                                                protationrelative=r;
                                                                aktualisieren();
};*/
template<class _tg> void _kamera<_tg>::transformierenparallel(_vektor3<_tg>&x) const{
                                                                //_tg rx,ry,rz;
                                                               
                                                                x-=*this;
                                                                /*
                                                                rx=x[0]*cos(_ph*protation[0])-x[2]*sin(_ph*protation[0]);
                                                                rz=x[0]*sin(_ph*protation[0])+x[2]*cos(_ph*protation[0]);

                                                                x.setzenkomponente(0,rx);//w[0]=rx;
                                                                x.setzenkomponente(2,rz);//w[2]=rz;       
                                                                
                                                                ry=x[1]*cosyaw()-x[2]*sinyaw();
                                                                rz=x[1]*sinyaw()+x[2]*cosyaw();
                                                                x.setzenkomponente(1,ry);//w[1]=ry;
                                                                x.setzenkomponente(2,-rz);//w[2]=rz;
                                                                
                                                                rx=x[0]*cosrol()-x[1]*sinrol();
                                                                ry=x[0]*sinrol()+x[1]*cosrol();
                                                                x.setzenkomponente(0,rx);//p[0]=w[0]=rx;
                                                                x.setzenkomponente(1,ry);//p[1]=w[1]=ry;                                                                
                                                                */
                                                                //vit->orttransformation(x);
};                                                                 
template<class _tg> void _kamera<_tg>::transformierenperspektive(_vektor3<_tg>&x) const{
                                                                _tg qx,qy;
                                                                //hier muss später das clipping an z ausgeführt werden.!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                                                                if(x[2]!=0){
                                                                 qx=(laenge()/(groesse(0)*2))/x[2];
                                                                 qy=(laenge()/(groesse(1)*2))/x[2];
                                                                 x.mul(0,qx);
                                                                 x.mul(1,qy);;
                                                                }else{
                                                                };
};
template<class _tg> template<class _tm> void _kamera<_tg>::ladenmatrix(_matrix44<_tm>*m,_matrix44<_tm>*p,_tg fov0,_tg fov1)const{
                                                                if(fov0==0) fov0=fov(0);
                                                                if(fov1==0) fov1=fov(1);
                                                                p->setzenprojektion(_tm(0.01f),_tm(1000),_tm(fov0),_tm(fov1));
                                                                /*
                                                                m->pdaten[0 ]=pplanen[0][0];
                                                                m->pdaten[1 ]=pplanen[0][1];
                                                                m->pdaten[2 ]=pplanen[0][2];
                                                                m->pdaten[3 ]=-(*this)*pplanen[0];
                                                                m->pdaten[4 ]=pplanen[1][0];
                                                                m->pdaten[5 ]=pplanen[1][1];
                                                                m->pdaten[6 ]=pplanen[1][2];
                                                                m->pdaten[7 ]=-(*this)*pplanen[1];
                                                                m->pdaten[8 ]=pvector[0];
                                                                m->pdaten[9 ]=pvector[1];
                                                                m->pdaten[10]=pvector[2];
                                                                m->pdaten[11]=-(*this)*pvector;
                                                                m->pdaten[12]=0;
                                                                m->pdaten[13]=0;
                                                                m->pdaten[14]=0;
                                                                m->pdaten[15]=1;
                                                                */
                                                             
                                                                
                                                                
                                                                m->pdaten[0 ]=(_tm)pplanen[0][0];
                                                                m->pdaten[4 ]=(_tm)pplanen[0][1];
                                                                m->pdaten[8 ]=(_tm)pplanen[0][2];
                                                                m->pdaten[12]=(_tm)(-(*this)*pplanen[0]);
                                                                m->pdaten[1 ]=(_tm)pplanen[1][0];
                                                                m->pdaten[5 ]=(_tm)pplanen[1][1];
                                                                m->pdaten[9 ]=(_tm)pplanen[1][2];
                                                                m->pdaten[13]=(_tm)(-(*this)*pplanen[1]);
                                                                m->pdaten[2 ]=(_tm)pvector[0];
                                                                m->pdaten[6 ]=(_tm)pvector[1];
                                                                m->pdaten[10]=(_tm)pvector[2];
                                                                m->pdaten[14]=(_tm)(-(*this)*pvector);
                                                                m->pdaten[3 ]=0;
                                                                m->pdaten[7 ]=0;
                                                                m->pdaten[11]=0;
                                                                m->pdaten[15]=1;
                                                                
                                                                
                                                                
                                                                
/*
				Local xax:_vector3=New _vector3
				Local yax:_vector3=New _vector3
				Local zax:_vector3=New _vector3
				'Local npos:_vector3=New _vector3


				Rem
					vorher:
				zax.copy(view)
				zax.norm()

				xax.copy(up)
				xax.crossproduct(zax)
				xax.norm()

				yax.copy(zax)
				yax.crossproduct(xax)
				EndRem
				
				zax.copy(view)
				xax.copy(side)
				yax.copy(up)
				xax.norm()
				yax.norm()
				zax.norm()
				
				
				
				
				'npos.setzen(position)
				'npos.mul(-1)
				m._11=xax.x
				m._21=xax.y
				m._31=xax.z
				m._41=-position.product(xax)
				m._12=yax.x
				m._22=yax.y
				m._32=yax.z
				m._42=-position.product(yax)
				m._13=zax.x
				m._23=zax.y
				m._33=zax.z
				m._43=-position.product(zax)
				m._14=0
				m._24=0
				m._34=0	
				m._44=1	
				'm.translate(npos)
				
				Local ah#,av#
				Local h:_vector3=New _vector3
				h.copy(view)
				h.add(side)
				
				ah=view.angle(h)*2
				Print "ah="+ah
				h.copy(view)
				h.add(up)
				av=view.angle(h)*2
				Print "av="+av

				'Print av+"  "+ah+"   "+view.x+"  "+view.y+"   "+view.z
				p.project(0.1,1000.0,ah,av)				
				'p.init()
				EndMethod
				*/
};				
template<class _tg> char _kamera<_tg>::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_kamera>*sd){
                                                                char r=1;
                                                                r^=sd->ladenbeginn(fn);
                                                                r^=sd->ladenverschachtelung(fn);
                                                                r^=sd->ladenwert(*this);
                                                                r^=sd->ladenwert(pvector);
                                                                r^=sd->ladenwert(pplane[0]);
                                                                r^=sd->ladenwert(pplane[1]);
                                                               // r^=sd->ladenwert(protation);
                                                               // r^=sd->ladenwert(protationrelative);
                                                               /* r^=sd->ladenwert(psinrot);
                                                                r^=sd->ladenwert(psinrol);
                                                                r^=sd->ladenwert(psinyaw);
                                                                r^=sd->ladenwert(pcosrot);
                                                                r^=sd->ladenwert(pcosrol);
                                                                r^=sd->ladenwert(pcosyaw);*/
                                                                r^=sd->ladenwert(pvectorlength);
                                                                r^=sd->ladenwert(pplanelength[0]);
                                                                r^=sd->ladenwert(pplanelength[1]);
                                                                r^=sd->ladenwert(pspeed);
                                                                r^=sd->ladenwert(poldtime);
                                                                r^=sd->ladenwert(pfactor);
                                                                r^=sd->ladenwert(pmarkierung);
                                                                r^=sd->ladenwert(porthonormal);                                                                  
                                                                sd->ladenende();
                                                                return(r);
};
template<class _tg> void _kamera<_tg>::speichern(_speicherbardynamisch<_kamera>*sd){
                                                                sd->speichernbeginnblock();
                                                                sd->speichernverschachtelung();
                                                                sd->speichernwert(*this);
                                                                sd->speichernwert(pvector);
                                                                sd->speichernwert(pplane[0]);
                                                                sd->speichernwert(pplane[1]);
                                                               // sd->speichernwert(protation);
                                                               // sd->speichernwert(protationrelative);
                                                                /*sd->speichernwert(psinrot);
                                                                sd->speichernwert(psinrol);
                                                                sd->speichernwert(psinyaw);
                                                                sd->speichernwert(pcosrot);
                                                                sd->speichernwert(pcosrol);
                                                                sd->speichernwert(pcosyaw);*/
                                                                sd->speichernwert(pvectorlength);
                                                                sd->speichernwert(pplanelength[0]);
                                                                sd->speichernwert(pplanelength[1]);
                                                                sd->speichernwert(pspeed);
                                                                sd->speichernwert(poldtime);
                                                                sd->speichernwert(pfactor);
                                                                sd->speichernwert(pmarkierung);
                                                                sd->speichernwert(porthonormal);                                                                
                                                                sd->speichernendeblock();
};
template<class _tg> char _kamera<_tg>::assoziieren(_speicherbardynamisch<_kamera>*sd){
                                                                sd->assoziierenverschachtelung();
                                                                return(1);
};
template<class _tg> bool _kamera<_tg>::laden(_dateispeicherbarbinaer*d){
																einhaengenspeicherung(d);
																ladenbeginn();
																d->laden(speichername());
																_vektor3<_tg> v;
																d->laden(v);
																_vektor3<_tg>::setzen(v);
																d->laden(pvector);
																d->laden(pplane[0]);
																d->laden(pplane[1]);
																d->laden(pplanen[0]);
																d->laden(pplanen[1]);
																d->laden(psinrot);
																d->laden(psinrol);
																d->laden(psinyaw);
																d->laden(pcosrot);
																d->laden(pcosrol);
																d->laden(pcosyaw);
																d->laden(pvectorlength);
																d->laden(pplanelength[0]);
																d->laden(pplanelength[1]);
																d->laden(pspeed);
																d->laden(poldtime);
																d->laden(pfactor);
																d->laden(pmarkierung);
																d->laden(porthonormal);
																return(true);
};
template<class _tg> void _kamera<_tg>::speichern(_dateispeicherbarbinaer*d){
																d->speichern(speichername());
																_vektor3<_tg> v=*this;
																d->speichern(v);
																d->speichern(pvector);
																d->speichern(pplane[0]);
																d->speichern(pplane[1]);
																d->speichern(pplanen[0]);
																d->speichern(pplanen[1]);
																d->speichern(psinrot);
																d->speichern(psinrol);
																d->speichern(psinyaw);
																d->speichern(pcosrot);
																d->speichern(pcosrol);
																d->speichern(pcosyaw);
																d->speichern(pvectorlength);
																d->speichern(pplanelength[0]);
																d->speichern(pplanelength[1]);
																d->speichern(pspeed);
																d->speichern(poldtime);
																d->speichern(pfactor);
																d->speichern(pmarkierung);
																d->speichern(porthonormal);

																
};
template<class _tg> bool _kamera<_tg>::assoziieren(){
																if(zeigergeladen()){
																 loeschenzeiger();
																};
																return(true);
};
//******************************************************************************************************************************************************************************************************
//                                                              S C H A T T E N
//******************************************************************************************************************************************************************************************************
template<class _tg,class _to> class _schatten:public _listenknotenbasis<_schatten<_tg,_to> >,public _liste<_licht<_tg,_to> >{
        public:
                _schatten(_listebasis<_schatten<_tg,_to> >*schattenliste,_licht<_tg,_to>*li,_tg lang);
                virtual ~_schatten();
                void laenge(const _tg);
                _tg laenge()const;
                virtual void opazitaet(const _to)=0;
                virtual void zeichnen(_grafik*)=0;
                virtual void zeichnendebug(_grafik*)=0;
                virtual void aktualisieren()=0;
                _licht<_tg,_to>*licht();
                bool geaendert();
                void gueltig(bool);
                bool gueltig()const;
        private:
                _tg plaenge;
                _vektor3<_tg> palterort;           //automatisch aktualisierung bei änderung
                bool pgueltig;

};
template<class _tg,class _to> _schatten<_tg,_to>::_schatten(_listebasis<_schatten<_tg,_to> >*schattenliste,_licht<_tg,_to>*li,_tg lang):_listenknotenbasis<_schatten<_tg,_to> >(schattenliste){
                                                                plaenge=lang;
                                                                new _verbinder<_licht<_tg,_to>,_schatten>(this,li,li,this);
                                                                palterort=li->ort();
                                                                pgueltig=true;
};
template<class _tg,class _to> _schatten<_tg,_to>::~_schatten(){
                                                                _liste<_licht<_tg,_to> >::aushaengen();
};
template<class _tg,class _to> _licht<_tg,_to>* _schatten<_tg,_to>::licht(){
                                                                _listenknoten<_licht<_tg,_to> >*it;
                                                                if(anfang(it)){
                                                                 return(it->objekt());
                                                                }else return(0);
};
template<class _tg,class _to> void _schatten<_tg,_to>::laenge(const _tg l){
                                                                plaenge=l;
};
template<class _tg,class _to> _tg _schatten<_tg,_to>::laenge()const{
                                                                return(plaenge);
};
template<class _tg,class _to> bool _schatten<_tg,_to>::geaendert(){
                                                                _listenknoten<_licht<_tg,_to> >*it;
                                                                if(anfang(it)){
                                                                 _licht<_tg,_to>*l=it->objekt();
                                                                 if(palterort==l->ort()) return(false);
                                                                 palterort=l->ort();
                                                                 return(true);
                                                                }else return(false);
};

template<class _tg,class _to> void _schatten<_tg,_to>::gueltig(bool b){
                                                                pgueltig=b;
};
template<class _tg,class _to> bool _schatten<_tg,_to>::gueltig()const{
                                                                return(pgueltig);
};

//******************************************************************************************************************************************************************************************************
//                                                              L I G H T 
//******************************************************************************************************************************************************************************************************
template<class _tg,class _to>
class _licht:public _listenknotenbasis<_licht<_tg,_to> >,public _liste<_schatten<_tg,_to> >,public _basis::_speicherbarargument<_licht<_tg,_to> >,public _speicherbarbinaer,public virtual _editierbar{
        public:
                _licht(_listebasis<_licht<_tg,_to> >*,const _vektor3<_tg>,const _vektor3<_to>,const _to);
                _licht(_listebasis<_licht<_tg,_to> >*,const _tg x,const _tg y,const _tg z,const _to r,const _to g,const _to b,const _to intens,bool shadow=true);
                _licht(const _licht<_tg,_to>*l);
                virtual ~_licht();
                virtual void kopieren(_licht<_tg,_to>*&)const;
                
                void ort(const _vektor3<_tg>&);
                _vektor3<_tg> ort() const;
                void schatten(const bool b);
                bool schatten()const;
                void schattenvolumen(const bool b);
                bool schattenvolumen()const;
                void statisch(const bool b);
                bool statisch()const;
                void dynamisch(const bool b);
                bool dynamisch()const;
                void dynamischadditiv(const bool b);
                bool dynamischadditiv()const;
                void farbestatisch(const _vektor3<_to>&l);
                _vektor3<_to> farbestatisch() const;
                void farbeambientstatisch(const _vektor3<_to>&l);
                _vektor3<_to> farbeambientstatisch()const;
                void intensitaetstatisch(const _to i);
                _to intensitaetstatisch() const;
                void farbedynamisch(const _vektor3<_to>&l);
                void farbedynamisch(const _to x,const _to y,const _to z);
                _vektor3<_to> farbedynamisch() const;
                void farbeglanz(const _vektor3<_to>&l);
                _vektor3<_to> farbeglanz()const;
                void farbeambientdynamisch(const _vektor3<_to>&l);
                _vektor3<_to> farbeambientdynamisch()const;
                void intensitaetdynamisch(const _to i);
                _to intensitaetdynamisch() const;
                _vektor3<_to>&farbeopazitaet();
                _to limitopazitaet()const;
                _to intensitaetopazitaet()const;
                                
                void binden(_grafik*,unsigned int);
                
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_licht>*);
                void speichern(_speicherbardynamisch<_licht>*);
                char assoziieren(_speicherbardynamisch<_licht>*);

                bool laden(_dateispeicherbarbinaer*);
                void speichern(_dateispeicherbarbinaer*);
                bool assoziieren();
                //editieren
                virtual void einhaengendialog(_dynamischerdialog*);
                virtual void auslesendialog(_dynamischerdialog*);
        private:
                _vektor3<_tg> port;
                //schalter
                bool pschatten;
                bool pschattenvolumen;//kann von aussen auch ignoriert werden... noch unklar
                bool pstatisch;//zb lightmaps
                bool pdynamisch;//dynamischen beleuchtungspass durchführen?
                bool pdynamischadditiv;//additiv oder subtraktiv?
                //statische Elemente (meist für lightmaps)
                _vektor3<_to> pfarbestatisch;
                _vektor3<_to> pfarbeambientstatisch;
                _to pintensitaetstatisch;
                //dynamische Elemente
                _vektor3<_to> pfarbedynamisch;
                _vektor3<_to> pfarbeglanz;
                _vektor3<_to> pfarbeambientdynamisch;//noch ungenutzt
                _to pintensitaetdynamisch;
                _tg plinear;
                _tg pkonstant;
                _tg pquadratisch;
                //dynamische elemente für den subtraktiven beleuchtungspass
                _vektor3<_to> pfarbeopazitaet;//meistens 0,0,0
                _to plimitopazitaet;//zB 0.7
                _to pintensitaetopazitaet;//zB 50
                
};
template<class _tg,class _to>
_licht<_tg,_to>::_licht(_listebasis<_licht<_tg,_to> >*l,const _vektor3<_tg> lo,_vektor3<_to> co,const _to i):_listenknotenbasis<_licht<_tg,_to> >(l){
                                                                port=lo;
                                                                pschattenvolumen=true;
                                                                pschatten=true;
                                                                pstatisch=false;
                                                                pdynamisch=true;
                                                                pdynamischadditiv=true;
                                                                pfarbestatisch=co;
                                                                pfarbeambientstatisch.setzen(0,0,0);
                                                                pintensitaetstatisch=i;
                                                                pfarbedynamisch=co;
                                                                pfarbeglanz=co;
                                                                pfarbeambientdynamisch.setzen(0,0,0);
                                                                pintensitaetdynamisch=i;
                                                                plinear=0;
                                                                pkonstant=0.1;
                                                                pquadratisch=0.001;
                                                                pfarbeopazitaet.setzen(0,0,0);
                                                                plimitopazitaet=_to(0.7f);
                                                                pintensitaetopazitaet=50;
};
template<class _tg,class _to>
_licht<_tg,_to>::_licht(_listebasis<_licht<_tg,_to> >*l,const _tg x,const _tg y,const _tg z,const _to r,const _to g,const _to b,const _to intens,bool shadow):_listenknotenbasis<_licht<_tg,_to> >(l){
                                                                port.setzen(x,y,z);
                                                                pschattenvolumen=true;
                                                                pschatten=shadow;
                                                                pstatisch=false;
                                                                pdynamisch=true;
                                                                pdynamischadditiv=true;
                                                                pfarbestatisch.setzen(r,g,b);
                                                                pfarbeambientstatisch.setzen(0,0,0);
                                                                pintensitaetstatisch=intens;
                                                                pfarbedynamisch.setzen(r,g,b);
                                                                pfarbeglanz.setzen(r,g,b);
                                                                pfarbeambientdynamisch.setzen(0,0,0);
                                                                pintensitaetdynamisch=intens;
                                                                plinear=0;
                                                                pkonstant=0.1;
                                                                pquadratisch=0.001;
                                                                pfarbeopazitaet.setzen(0,0,0);
                                                                plimitopazitaet=_to(0.7f);
                                                                pintensitaetopazitaet=50;
};

template<class _tg,class _to>
_licht<_tg,_to>::_licht(const _licht<_tg,_to>*l):_listenknotenbasis<_licht<_tg,_to> >(l->_listenknotenbasis<_licht<_tg,_to> >::liste()){
                                                                port=l->port;
                                                                pschatten=l->pschatten;
                                                                pschattenvolumen=l->pschattenvolumen;
                                                                pstatisch=l->pstatisch;
                                                                pdynamisch=l->pdynamisch;
                                                                pdynamischadditiv=l->pdynamischadditiv;
                                                                pfarbestatisch=l->pfarbestatisch;
                                                                pfarbeambientstatisch=l->pfarbeambientstatisch;
                                                                pintensitaetstatisch=l->pintensitaetstatisch;
                                                                pfarbedynamisch=l->pfarbedynamisch;
                                                                pfarbeglanz=l->pfarbeglanz;
                                                                pfarbeambientdynamisch=l->pfarbeambientdynamisch;
                                                                pintensitaetdynamisch=l->pintensitaetdynamisch;
                                                                plinear=l->plinear;
                                                                pkonstant=l->pkonstant;
                                                                pquadratisch=l->pquadratisch;
                                                                pfarbeopazitaet=l->pfarbeopazitaet;
                                                                plimitopazitaet=l->plimitopazitaet;
                                                                pintensitaetopazitaet=l->pintensitaetopazitaet;

};
template<class _tg,class _to>
_licht<_tg,_to>::~_licht(){
                                                                _liste<_schatten<_tg,_to> >::aushaengen();
};
template<class _tg,class _to>
void _licht<_tg,_to>::kopieren(_licht<_tg,_to>*&l)const{
                                                                l=new _licht<_tg,_to>(this);
};



template<class _tg,class _to>
void _licht<_tg,_to>::ort(const _vektor3<_tg>&l){
                                                                port=l;
};
template<class _tg,class _to>
_vektor3<_tg> _licht<_tg,_to>::ort() const{
                                                                return(port);
};


template<class _tg,class _to>
void _licht<_tg,_to>::schatten(const bool b){
                                                                pschatten=b;
};
template<class _tg,class _to>
bool _licht<_tg,_to>::schatten()const{
                                                                return(pschatten);
};
template<class _tg,class _to>
void _licht<_tg,_to>::schattenvolumen(const bool b){
                                                                pschattenvolumen=b;
};
template<class _tg,class _to>
bool _licht<_tg,_to>::schattenvolumen()const{
                                                                return(pschattenvolumen);
};
template<class _tg,class _to>
void _licht<_tg,_to>::statisch(const bool b){
                                                                pstatisch=b;
};
template<class _tg,class _to>
bool _licht<_tg,_to>::statisch()const{
                                                                return(pstatisch);
};
template<class _tg,class _to>
void _licht<_tg,_to>::dynamisch(const bool b){
                                                                pdynamisch=b;
};
template<class _tg,class _to>
bool _licht<_tg,_to>::dynamisch()const{
                                                                return(pdynamisch);
};
template<class _tg,class _to>
void _licht<_tg,_to>::dynamischadditiv(const bool b){
                                                                pdynamischadditiv=b;
};
template<class _tg,class _to>
bool _licht<_tg,_to>::dynamischadditiv()const{
                                                                return(pdynamischadditiv);
};




template<class _tg,class _to>
void _licht<_tg,_to>::farbestatisch(const _vektor3<_to>&l){
                                                                pfarbestatisch=l;
};
template<class _tg,class _to>
_vektor3<_to> _licht<_tg,_to>::farbestatisch() const{
                                                                return(pfarbestatisch);
};
template<class _tg,class _to>
void _licht<_tg,_to>::farbeambientstatisch(const _vektor3<_to>&l){
                                                                pfarbeambientstatisch=l;
};
template<class _tg,class _to>
_vektor3<_to> _licht<_tg,_to>::farbeambientstatisch()const{
                                                                return(pfarbeambientstatisch);
};
template<class _tg,class _to>
void _licht<_tg,_to>::intensitaetstatisch(const _to i){
                                                                if(i<0) pintensitaetstatisch=0; else pintensitaetstatisch=i;
};
template<class _tg,class _to>
_to _licht<_tg,_to>::intensitaetstatisch() const{
                                                                return(pintensitaetstatisch);
};
template<class _tg,class _to>
void _licht<_tg,_to>::farbedynamisch(const _vektor3<_to>&l){
                                                                pfarbedynamisch=l;
};
template<class _tg,class _to>
void _licht<_tg,_to>::farbedynamisch(const _to x,const _to y,const _to z){
                                                                pfarbedynamisch.setzen(x,y,z);
};
template<class _tg,class _to>
_vektor3<_to> _licht<_tg,_to>::farbedynamisch() const{
                                                                return(pfarbedynamisch);
};
template<class _tg,class _to>
void _licht<_tg,_to>::farbeglanz(const _vektor3<_to>&l){
                                                                pfarbeglanz=l;
};
template<class _tg,class _to>
_vektor3<_to> _licht<_tg,_to>::farbeglanz()const{
                                                                return(pfarbeglanz);
};
template<class _tg,class _to>
void _licht<_tg,_to>::farbeambientdynamisch(const _vektor3<_to>&l){
                                                                pfarbeambientdynamisch=l;
};
template<class _tg,class _to>
_vektor3<_to> _licht<_tg,_to>::farbeambientdynamisch()const{
                                                                return(pfarbeambientdynamisch);
};
template<class _tg,class _to>
void _licht<_tg,_to>::intensitaetdynamisch(const _to i){
                                                                if(i<0) pintensitaetdynamisch=0; else pintensitaetdynamisch=i;
};
template<class _tg,class _to>
_to _licht<_tg,_to>::intensitaetdynamisch() const{
                                                                return(pintensitaetdynamisch);
};


template<class _tg,class _to>
_vektor3<_to>&_licht<_tg,_to>::farbeopazitaet(){
                                                                return(pfarbeopazitaet);
};
template<class _tg,class _to>
_to _licht<_tg,_to>::limitopazitaet()const{
                                                                return(plimitopazitaet);
};
template<class _tg,class _to>
_to _licht<_tg,_to>::intensitaetopazitaet()const{
                                                                return(pintensitaetopazitaet);
};

template<class _tg,class _to>
void _licht<_tg,_to>::binden(_grafik*g,unsigned int is){
                                                                
                                                                
                                                             //   MUSS NOCH GEKAPSELT WERDEN     !!!!!!!!!!!!!!!!!!!!!!!
                                                                
                                                                GLfloat lp[4];
                                                                GLfloat lc[4];
                                                                GLfloat lv[4];
                                                                //--------------
                                                                lp[0]=port[0];
                                                                lp[1]=port[1];
                                                                lp[2]=port[2];
                                                                lp[3]=1;
                                                                glLightfv(GL_LIGHT0+(GLenum)is,GL_POSITION,lp);
                                                                lc[0]=pfarbeambientdynamisch[0];
                                                                lc[1]=pfarbeambientdynamisch[1];
                                                                lc[2]=pfarbeambientdynamisch[2];
                                                                lc[3]=1;
                                                                glLightfv(GL_LIGHT0+(GLenum)is,GL_AMBIENT,lc);
                                                                lc[0]=pfarbedynamisch[0]*pintensitaetdynamisch;
                                                                lc[1]=pfarbedynamisch[1]*pintensitaetdynamisch;
                                                                lc[2]=pfarbedynamisch[2]*pintensitaetdynamisch;
                                                                lc[3]=1;
                                                                glLightfv(GL_LIGHT0+(GLenum)is,GL_DIFFUSE,lc);
                                                                glLightf(GL_LIGHT0+(GLenum)is,GL_SPOT_CUTOFF,(GLfloat)180.0f);
                                                                glLightf(GL_LIGHT0+(GLenum)is,GL_CONSTANT_ATTENUATION,(GLfloat)pkonstant);
                                                                glLightf(GL_LIGHT0+(GLenum)is,GL_LINEAR_ATTENUATION,(GLfloat)plinear);
                                                                glLightf(GL_LIGHT0+(GLenum)is,GL_QUADRATIC_ATTENUATION,(GLfloat)pquadratisch);
                                                                lv[0]=1;
                                                                lv[1]=0;
                                                                lv[2]=0;
                                                                lv[3]=0;
                                                                glLightfv(GL_LIGHT0+(GLenum)is,GL_SPOT_DIRECTION,lv);
                                                                lc[0]=pfarbeglanz[0]*pintensitaetdynamisch;
                                                                lc[1]=pfarbeglanz[1]*pintensitaetdynamisch;
                                                                lc[2]=pfarbeglanz[2]*pintensitaetdynamisch;
                                                                lc[3]=1;
                                                                glLightfv(GL_LIGHT0+(GLenum)is,GL_SPECULAR,lc);
                                                                glLightf(GL_LIGHT0+(GLenum)is,GL_SPOT_EXPONENT,(GLfloat)2);
                                                                glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER,(GLfloat)1);
                                                                glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL,GL_SEPARATE_SPECULAR_COLOR);
                                                                
};
template<class _tg,class _to>
char _licht<_tg,_to>::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_licht>*sd){
                                                                char r=1;
                                                                r^=sd->ladenbeginn(fn);
                                                                r^=sd->ladenverschachtelung(fn);
                                                                r^=sd->ladenwert(port);
                                                                r^=sd->ladenwert(pschattenvolumen);
                                                                r^=sd->ladenwert(pstatisch);
                                                                r^=sd->ladenwert(pfarbestatisch);
                                                                r^=sd->ladenwert(pfarbeambientstatisch);
                                                                r^=sd->ladenwert(pintensitaetstatisch);
                                                                r^=sd->ladenwert(pdynamisch);
                                                                r^=sd->ladenwert(pdynamischadditiv);
                                                                r^=sd->ladenwert(pfarbedynamisch);
                                                                r^=sd->ladenwert(pfarbeglanz);
                                                                r^=sd->ladenwert(pfarbeambientdynamisch);
                                                                r^=sd->ladenwert(pintensitaetdynamisch);
                                                                r^=sd->ladenwert(pkonstant);
                                                                r^=sd->ladenwert(plinear);
                                                                r^=sd->ladenwert(pquadratisch);
                                                                r^=sd->ladenwert(pfarbeopazitaet);
                                                                r^=sd->ladenwert(plimitopazitaet);
                                                                r^=sd->ladenwert(pintensitaetopazitaet);                                                                
                                                                sd->ladenende();
                                                                return(r);
};
template<class _tg,class _to>
void _licht<_tg,_to>::speichern(_speicherbardynamisch<_licht>*sd){
                                                                sd->speichernbeginnblock();
                                                                sd->speichernverschachtelung();
                                                                sd->speichernwert(port);
                                                                sd->speichernwert(pschattenvolumen);
                                                                sd->speichernwert(pstatisch);
                                                                sd->speichernwert(pfarbestatisch);
                                                                sd->speichernwert(pfarbeambientstatisch);
                                                                sd->speichernwert(pintensitaetstatisch);
                                                                sd->speichernwert(pdynamisch);
                                                                sd->speichernwert(pdynamischadditiv);
                                                                sd->speichernwert(pfarbedynamisch);
                                                                sd->speichernwert(pfarbeglanz);
                                                                sd->speichernwert(pfarbeambientdynamisch);
                                                                sd->speichernwert(pintensitaetdynamisch);
                                                                sd->speichernwert(pkonstant);
                                                                sd->speichernwert(plinear);
                                                                sd->speichernwert(pquadratisch);
                                                                sd->speichernwert(pfarbeopazitaet);
                                                                sd->speichernwert(plimitopazitaet);
                                                                sd->speichernwert(pintensitaetopazitaet);
                                                                sd->speichernendeblock();
};
template<class _tg,class _to>
char _licht<_tg,_to>::assoziieren(_speicherbardynamisch<_licht>*sd){
                                                                sd->assoziierenverschachtelung();
                                                                return(1);
};
template<class _tg,class _to>
bool _licht<_tg,_to>::laden(_dateispeicherbarbinaer*d){
																einhaengenspeicherung(d);
																ladenbeginn();
																d->laden(speichername());
																d->laden(port);
																d->laden(pschatten);
																d->laden(pschattenvolumen);
																d->laden(pstatisch);
																d->laden(pdynamisch);
																d->laden(pdynamischadditiv);
																d->laden(pfarbestatisch);
																d->laden(pfarbeambientstatisch);
																d->laden(pintensitaetstatisch);
																d->laden(pfarbedynamisch);
																d->laden(pfarbeglanz);
																d->laden(pfarbeambientdynamisch);
																d->laden(pintensitaetdynamisch);
																d->laden(plinear);
																d->laden(pkonstant);
																d->laden(pquadratisch);
																d->laden(pfarbeopazitaet);
																d->laden(plimitopazitaet);
																d->laden(pintensitaetopazitaet);
																return(true);
};
template<class _tg,class _to>
void _licht<_tg,_to>::speichern(_dateispeicherbarbinaer*d){
																d->speichern(speichername());
																d->speichern(port);
																d->speichern(pschatten);
																d->speichern(pschattenvolumen);
																d->speichern(pstatisch);
																d->speichern(pdynamisch);
																d->speichern(pdynamischadditiv);
																d->speichern(pfarbestatisch);
																d->speichern(pfarbeambientstatisch);
																d->speichern(pintensitaetstatisch);
																d->speichern(pfarbedynamisch);
																d->speichern(pfarbeglanz);
																d->speichern(pfarbeambientdynamisch);
																d->speichern(pintensitaetdynamisch);
																d->speichern(plinear);
																d->speichern(pkonstant);
																d->speichern(pquadratisch);
																d->speichern(pfarbeopazitaet);
																d->speichern(plimitopazitaet);
																d->speichern(pintensitaetopazitaet);
};
template<class _tg,class _to>
bool _licht<_tg,_to>::assoziieren(){
																if(zeigergeladen()){
																 loeschenzeiger();
																};
																return(true);
};

template<class _tg,class _to>
void _licht<_tg,_to>::einhaengendialog(_dynamischerdialog*d){
                                                                d->editierbar(this);
                                                                d->loeschensektion(); 
                                                                d->addierensektion(L"Allgemein");
                                                                d->addierensektion(L"Optische Statik");
                                                                d->addierensektion(L"Optische Dynamik");
                                                                d->sektion(L"Allgemein")->offen(true);
                                                                d->sektion(L"Optische Statik")->offen(true);
                                                                d->sektion(L"Optische Dynamik")->offen(true);
                                                                d->einhaengen(L"Allgemein",L"Position",port);
                                                                d->einhaengen(L"Allgemein",L"Schattenvolumen",pschattenvolumen);
                                                                d->einhaengen(L"Optische Statik",L"Statisch",pstatisch);
                                                                d->einhaengen(L"Optische Statik",L"Farbe",pfarbestatisch);
                                                                d->einhaengen(L"Optische Statik",L"Farbe Ambienz",pfarbeambientstatisch);
                                                                d->einhaengen(L"Optische Statik",L"Intensität",pintensitaetstatisch);
                                                                d->einhaengen(L"Optische Dynamik",L"Dynamisch",pdynamisch);
                                                                d->einhaengen(L"Optische Dynamik",L"Additive Dynamik",pdynamischadditiv);
                                                                d->einhaengen(L"Optische Dynamik",L"Farbe",pfarbedynamisch);
                                                                d->einhaengen(L"Optische Dynamik",L"Farbe Glanz",pfarbeglanz);
                                                                d->einhaengen(L"Optische Dynamik",L"Farbe Ambienz",pfarbeambientdynamisch);
                                                                d->einhaengen(L"Optische Dynamik",L"Intensität",pintensitaetdynamisch);
                                                                d->einhaengen(L"Optische Dynamik",L"Konstante Betonung",pkonstant);
                                                                d->einhaengen(L"Optische Dynamik",L"Lineare Betonung",plinear);
                                                                d->einhaengen(L"Optische Dynamik",L"Quadratische Betonung",pquadratisch);
                                                                d->einhaengen(L"Optische Dynamik",L"Subtraktive Opazität : Farbe",pfarbeopazitaet);
                                                                d->einhaengen(L"Optische Dynamik",L"Subtraktive Opazität : Limit",plimitopazitaet);
                                                                d->einhaengen(L"Optische Dynamik",L"Subtraktive Opazität : Intensität",pintensitaetopazitaet);
};
template<class _tg,class _to>
void _licht<_tg,_to>::auslesendialog(_dynamischerdialog*d){
                                                                d->auslesen(L"Allgemein",L"Position",port);
                                                                d->auslesen(L"Allgemein",L"Schattenvolumen",pschattenvolumen);
                                                                d->auslesen(L"Optische Statik",L"Statisch",pstatisch);
                                                                d->auslesen(L"Optische Statik",L"Farbe",pfarbestatisch);
                                                                d->auslesen(L"Optische Statik",L"Farbe Ambienz",pfarbeambientstatisch);
                                                                d->auslesen(L"Optische Statik",L"Intensität",pintensitaetstatisch);
                                                                d->auslesen(L"Optische Dynamik",L"Dynamisch",pdynamisch);
                                                                d->auslesen(L"Optische Dynamik",L"Additive Dynamik",pdynamischadditiv);
                                                                d->auslesen(L"Optische Dynamik",L"Farbe",pfarbedynamisch);
                                                                d->auslesen(L"Optische Dynamik",L"Farbe Glanz",pfarbeglanz);
                                                                d->auslesen(L"Optische Dynamik",L"Farbe Ambienz",pfarbeambientdynamisch);
                                                                d->auslesen(L"Optische Dynamik",L"Intensität",pintensitaetdynamisch);
                                                                d->auslesen(L"Optische Dynamik",L"Konstante Betonung",pkonstant);
                                                                d->auslesen(L"Optische Dynamik",L"Lineare Betonung",plinear);
                                                                d->auslesen(L"Optische Dynamik",L"Quadratische Betonung",pquadratisch);
                                                                d->auslesen(L"Optische Dynamik",L"Subtraktive Opazität : Farbe",pfarbeopazitaet);
                                                                d->auslesen(L"Optische Dynamik",L"Subtraktive Opazität : Limit",plimitopazitaet);
                                                                d->auslesen(L"Optische Dynamik",L"Subtraktive Opazität : Intensität",pintensitaetopazitaet);
};
//******************************************************************************************************************************************************************************************************
//                                                              G R A V I T A T I O N 
//******************************************************************************************************************************************************************************************************
template<class _tg>
class _gravitation:
        public _feld<_tg>,
        public _listenknotenbasis<_gravitation<_tg> >,
        public _basis::_speicherbarargument<_gravitation<_tg> >,
		public _speicherbarbinaer,
        public virtual _editierbar{
        public:
                _gravitation(_listebasis<_gravitation<_tg> >*,const _vektor3<_tg>,const _tg);
                _gravitation(_listebasis<_gravitation<_tg> >*,const _vektor3<_tg>&,const _vektor3<_tg>&);
                virtual ~_gravitation();
                inline _vektor3<_tg> ort() const;
                void ort(const _vektor3<_tg>);
                inline _tg intensitaet() const;
                inline void intensitaet(const _tg);
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_gravitation>*);
                void speichern(_speicherbardynamisch<_gravitation>*);
                char assoziieren(_speicherbardynamisch<_gravitation>*);
                bool laden(_dateispeicherbarbinaer*d);
				void speichern(_dateispeicherbarbinaer*d);
                bool assoziieren();
                //editieren
                virtual void einhaengendialog(_dynamischerdialog*);
                virtual void auslesendialog(_dynamischerdialog*);
        private:
};
template<class _tg>
_gravitation<_tg>::_gravitation(_listebasis<_gravitation<_tg> >*l,const _vektor3<_tg> lo,const _tg i):_listenknotenbasis<_gravitation<_tg> >(l){
                                                                homogen(lo);
};
template<class _tg>
_gravitation<_tg>::_gravitation(_listebasis<_gravitation<_tg> >*l,const _vektor3<_tg>&o,const _vektor3<_tg>&h):_listenknotenbasis<_gravitation<_tg> >(l){
                                                                homogen(h);
                                                                _feld<_tg>::ort(o);
};
template<class _tg>
_gravitation<_tg>::~_gravitation(){
};
template<class _tg>
_vektor3<_tg> _gravitation<_tg>::ort() const{
                                                                return(divergenzort(0));
};
template<class _tg>
void _gravitation<_tg>::ort(const _vektor3<_tg> l){
                                                                divergenzort(0,l);
};
template<class _tg>
_tg _gravitation<_tg>::intensitaet() const{
                                                                return(divergenzintensitaet(0));
};
template<class _tg>
void _gravitation<_tg>::intensitaet(const _tg i){
                                                                divergenzintensitaet(0,i);
};
template<class _tg>
char _gravitation<_tg>::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_gravitation>*sd){
                                                                char r=1;
                                                                r^=sd->ladenbeginn(fn);
                                                                r^=sd->ladenverschachtelung(fn);
                                                                sd->ladenende();
                                                                return(r);
};
template<class _tg>
void _gravitation<_tg>::speichern(_speicherbardynamisch<_gravitation>*sd){
                                                                sd->speichernbeginnblock();
                                                                sd->speichernverschachtelung();
                                                                sd->speichernendeblock();
};
template<class _tg>
char _gravitation<_tg>::assoziieren(_speicherbardynamisch<_gravitation>*sd){
                                                                sd->assoziierenverschachtelung();
                                                                return(1);
};
template<class _tg>
bool _gravitation<_tg>::laden(_dateispeicherbarbinaer*d){
																einhaengenspeicherung(d);
																ladenbeginn();
																d->laden(speichername());
																ladenfeld(d);
																return(true);
};
template<class _tg>
void _gravitation<_tg>::speichern(_dateispeicherbarbinaer*d){
																d->speichern(speichername());
																speichernfeld(d);
};
template<class _tg>
bool _gravitation<_tg>::assoziieren(){
																if(zeigergeladen()){
																 loeschenzeiger();
																};
																return(true);
};
template<class _tg>
void _gravitation<_tg>::einhaengendialog(_dynamischerdialog*d){
                                                                _feld<_tg>::einhaengendialog(d);
                                                                d->addierensektion(L"Gravitation");
                                                                d->sektion(L"Gravitation")->offen(true);
};
template<class _tg>
void _gravitation<_tg>::auslesendialog(_dynamischerdialog*d){
                                                                _feld<_tg>::auslesendialog(d);
};

//******************************************************************************************************************************************************************************************************
//                                                              F E L D E L E K T R O S T A T I S C H 
//******************************************************************************************************************************************************************************************************
template<class _tg>
class _feldelektrostatisch:
        public _feld<_tg>,
        public _listenknotenbasis<_feldelektrostatisch<_tg> >,
        public _basis::_speicherbarargument<_feldelektrostatisch<_tg> >,
		public _speicherbarbinaer,
        public virtual _editierbar{
        public:
                _feldelektrostatisch(_listebasis<_feldelektrostatisch<_tg> >*,const _vektor3<_tg>,const _vektor3<_tg>&);
                virtual ~_feldelektrostatisch();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_feldelektrostatisch>*);
                void speichern(_speicherbardynamisch<_feldelektrostatisch>*);
                char assoziieren(_speicherbardynamisch<_feldelektrostatisch>*);
                bool laden(_dateispeicherbarbinaer*d);
				void speichern(_dateispeicherbarbinaer*d);
                bool assoziieren();
                //editieren
                virtual void einhaengendialog(_dynamischerdialog*);
                virtual void auslesendialog(_dynamischerdialog*);
        private:
};
template<class _tg>
_feldelektrostatisch<_tg>::_feldelektrostatisch(_listebasis<_feldelektrostatisch<_tg> >*l,const _vektor3<_tg> o,const _vektor3<_tg>&h):_listenknotenbasis<_feldelektrostatisch<_tg> >(l){
                                                                homogen(h);
                                                                ort(o);
};
template<class _tg>
_feldelektrostatisch<_tg>::~_feldelektrostatisch(){
};
template<class _tg>
char _feldelektrostatisch<_tg>::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_feldelektrostatisch>*sd){
                                                                char r=1;
                                                                r^=sd->ladenbeginn(fn);
                                                                r^=sd->ladenverschachtelung(fn);
                                                                sd->ladenende();
                                                                return(r);
};
template<class _tg>
void _feldelektrostatisch<_tg>::speichern(_speicherbardynamisch<_feldelektrostatisch>*sd){
                                                                sd->speichernbeginnblock();
                                                                sd->speichernverschachtelung();
                                                                sd->speichernendeblock();
};
template<class _tg>
char _feldelektrostatisch<_tg>::assoziieren(_speicherbardynamisch<_feldelektrostatisch>*sd){
                                                                sd->assoziierenverschachtelung();
                                                                return(1);
};
template<class _tg>
bool _feldelektrostatisch<_tg>::laden(_dateispeicherbarbinaer*d){
																einhaengenspeicherung(d);
																ladenbeginn();
																d->laden(speichername());
																ladenfeld(d);
																return(true);
};
template<class _tg>
void _feldelektrostatisch<_tg>::speichern(_dateispeicherbarbinaer*d){
																d->speichern(speichername());
																speichernfeld(d);

};
template<class _tg>
bool _feldelektrostatisch<_tg>::assoziieren(){
																if(zeigergeladen()){
																 loeschenzeiger();
																};
																return(true);
};
template<class _tg>
void _feldelektrostatisch<_tg>::einhaengendialog(_dynamischerdialog*d){
                                                                _feld<_tg>::einhaengendialog(d);
                                                                d->addierensektion(L"Feldelektrostatisch");
                                                                d->sektion(L"Feldelektrostatisch")->offen(true);
};
template<class _tg>
void _feldelektrostatisch<_tg>::auslesendialog(_dynamischerdialog*d){
                                                                _feld<_tg>::auslesendialog(d);
};
//******************************************************************************************************************************************************************************************************
//                                                              F E L D M A G N E T O S T A T I S C H 
//******************************************************************************************************************************************************************************************************
template<class _tg>
class _feldmagnetostatisch:
        public _feld<_tg>,
        public _listenknotenbasis<_feldmagnetostatisch<_tg> >,
        public _basis::_speicherbarargument<_feldmagnetostatisch<_tg> >,
		public _speicherbarbinaer,
        public virtual _editierbar{
        public:
                _feldmagnetostatisch(_listebasis<_feldmagnetostatisch<_tg> >*,const _vektor3<_tg>,const _vektor3<_tg>&);
                virtual ~_feldmagnetostatisch();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_feldmagnetostatisch>*);
                void speichern(_speicherbardynamisch<_feldmagnetostatisch>*);
                char assoziieren(_speicherbardynamisch<_feldmagnetostatisch>*);
                bool laden(_dateispeicherbarbinaer*d);
				void speichern(_dateispeicherbarbinaer*d);
                bool assoziieren();
                //editieren
                virtual void einhaengendialog(_dynamischerdialog*);
                virtual void auslesendialog(_dynamischerdialog*);
        private:
};
template<class _tg>
_feldmagnetostatisch<_tg>::_feldmagnetostatisch(_listebasis<_feldmagnetostatisch<_tg> >*l,const _vektor3<_tg> o,const _vektor3<_tg>&h):_listenknotenbasis<_feldmagnetostatisch<_tg> >(l){
                                                                homogen(h);
                                                                ort(o);
};
template<class _tg>
_feldmagnetostatisch<_tg>::~_feldmagnetostatisch(){
};
template<class _tg>
char _feldmagnetostatisch<_tg>::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_feldmagnetostatisch>*sd){
                                                                char r=1;
                                                                r^=sd->ladenbeginn(fn);
                                                                r^=sd->ladenverschachtelung(fn);
                                                                sd->ladenende();
                                                                return(r);
};
template<class _tg>
void _feldmagnetostatisch<_tg>::speichern(_speicherbardynamisch<_feldmagnetostatisch>*sd){
                                                                sd->speichernbeginnblock();
                                                                sd->speichernverschachtelung();
                                                                sd->speichernendeblock();
};
template<class _tg>
char _feldmagnetostatisch<_tg>::assoziieren(_speicherbardynamisch<_feldmagnetostatisch>*sd){
                                                                sd->assoziierenverschachtelung();
                                                                return(1);
};
template<class _tg>
bool _feldmagnetostatisch<_tg>::laden(_dateispeicherbarbinaer*d){
																einhaengenspeicherung(d);
																ladenbeginn();
																d->laden(speichername());
																ladenfeld(d);
																return(true);
};
template<class _tg>
void _feldmagnetostatisch<_tg>::speichern(_dateispeicherbarbinaer*d){
																d->speichern(speichername());
																speichernfeld(d);
};
template<class _tg>
bool _feldmagnetostatisch<_tg>::assoziieren(){
																if(zeigergeladen()){
																 loeschenzeiger();
																};
																return(true);
};
template<class _tg>
void _feldmagnetostatisch<_tg>::einhaengendialog(_dynamischerdialog*d){
                                                                _feld<_tg>::einhaengendialog(d);
                                                                d->addierensektion(L"Feldmagnetostatisch");
                                                                d->sektion(L"Feldmagnetostatisch")->offen(true);
};
template<class _tg>
void _feldmagnetostatisch<_tg>::auslesendialog(_dynamischerdialog*d){
                                                                _feld<_tg>::auslesendialog(d);
};



#endif