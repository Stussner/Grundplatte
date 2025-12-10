//******************************************************************************************************************************************************************************************************
//  Project     : grundplatte
//  Library     : _grundplatte.lib
//  Module      : _datei.hpp
//  Date        : 1.1.2003
//  Description : 
//******************************************************************************************************************************************************************************************************
#ifndef _dateih_included
#define _dateih_included
#include <_text.hpp>

//******************************************************************************************************************************************************************************************************
//                                                              F O R W A R D D E K L A R A T I O N   
//******************************************************************************************************************************************************************************************************
/*template<class T> _dataintegral;
template<class T> _dataexponential;
template<class T> _assoziation;*/
class _bool;
class _char;
class _schar;
class _short;
class _ushort;
class _int;
class _uint;
class _long;
class _ulong;
class _float;
class _double;
class _longdouble;
class _datei;
class _logbuch;
class _dateispeicherbar;
class _dateispeicherbartext;
class _dateispeicherbarbinaer;
class _dateispeicherbarknoten;
class _dateispeicherbarkommentar;
class _dateispeicherbaridentifikation;
namespace _basis{
class _speicherbar;                                                 //basis klasse für implizite stoerables
template<class T>         class _speicherbardynamisch;              //schnittstellen klasse arbeitet mit _sd.inheritanceinterface
template<class T>         class _speicherbarargument;               //BASIS KLASSE für alle objekte , die per argument gespeichert werden sollen
};
template<class T>         class _speicherbardynamisch;              //als argument einer klasse geben, argumentinterface, unabhängiste methode
template<class T>         class _speicherbardynamischvererbungsschnittstelle;
class _speicherint;
class _speicherfloat;
template<class T>         class _speicherassoziationbasis;
template<class T>         class _speicherassoziationschnittstelle;
template<class T>         class _speicherassoziationargument;
template<class T>         _zeichenkette<char> gettypename(T*c);
template<class T>         _zeichenkette<char> gettypename();
template<class T>         char associateassociationbase(_dateispeicherbar*datei,_zeichenkette<char>*name,T*&pointer);
template<class T>         char associateassociationinterface(_dateispeicherbar*datei,_zeichenkette<char>*name,T*&pointer);
template<class T>         char associateassociationargument(_dateispeicherbar*datei,_zeichenkette<char>*name,T*&pointer);
template<class M,class T> char saveassociationargument(_dateispeicherbar*datei,M*manager,T*pointer);
template<class M,class T> char saveassociationinterface(M*manager,T*pointer);
template<class M,class T> char saveassociationbase(M*manager,T*pointer);
bool dateiexistiert(_zeichenkette<char> f);
class _dateispeicherbarbinaer;
class _speicherbarbinaer;


#include <_struktur.hpp>
#include <_vektor.hpp>
#include <string.h>
#include <typeinfo>
#include <vector>
#include <stdlib.h>

#undef schnittstelle
template<class _tg> class _vektor;
template<class _tg> class _vektor2;
template<class _tg> class _vektor3;
template<class _tg> class _vektor4;








//******************************************************************************************************************************************************************************************************
//                                                              D A T A I N T E G R A L 
//******************************************************************************************************************************************************************************************************
template<class T>class _dataintegral{
        public:
                inline _dataintegral(const _dataintegral<T>&);
                inline _dataintegral(const T);
                inline _dataintegral();
                inline T& setzen(const T);
                inline T holen() const;
                //------------------ fundamental--------------
                inline                 operator T()                const;
                inline bool         operator==(const T)         const;
                inline bool         operator!=(const T)         const;
                inline T &        operator=(const T);
                inline T &        operator=(const _dataintegral<T>&);
                //------------------ integral ----------------
                inline T&        operator++();
                inline T&        operator--();
                inline T         operator%(const T)           const;
                inline T&        operator%=(const T);
                inline T        operator<<(const T)        const;
                inline T         operator>>(const T)         const;
                inline T&        operator<<=(const T);
                inline T&        operator>>=(const T);
                //------------------- relational -------------
                inline bool        operator>=(const T)         const;
                inline bool        operator<=(const T)         const;
                inline bool        operator>(const T)         const;
                inline bool        operator<(const T)         const;
                //-----------------arithmetical---------------
                inline T         operator+(const T)         const;
                inline T&        operator+=(const T);
                inline T         operator-(const T)         const;
                inline T         operator-()                       const;
                inline T&        operator-=(const T);
                inline T         operator*(const T)           const;
                inline T&        operator*=(const T);
                inline T         operator/(const T)           const;
                inline T&        operator/=(const T);
                //------------------- logical ----------------
                inline bool        operator&&(const T)         const;
                inline bool        operator||(const T)         const;
                inline bool        operator!()                 const;
        private:
                T daten;
};
template<class T> _dataintegral<T>::_dataintegral(const _dataintegral<T>&d){
                                                                daten=d.daten;
};
template<class T> _dataintegral<T>::_dataintegral(const T d){
                                                                daten=d;
};
template<class T> _dataintegral<T>::_dataintegral(){
                                                                daten=0;
};
template<class T> _dataintegral<T>::operator T() const{
                                                                return(daten);
};
template<class T> bool _dataintegral<T>::operator==(const T t) const{
                                                                return(daten==t);
};
template<class T> bool _dataintegral<T>::operator!=(const T t) const{
                                                                return(daten!=t);
};
template<class T> T& _dataintegral<T>::operator=(const T t){
                                                                daten=t;
                                                                return(daten);
};
template<class T> T& _dataintegral<T>::operator=(const _dataintegral<T>&t){
                                                                daten=t.daten;
                                                                return(daten);
};
template<class T> T& _dataintegral<T>::setzen(const T t){
                                                                daten=t;
                                                                return(daten);
};
template<class T> T _dataintegral<T>::holen() const{
                                                                return(daten);
};
//------------------------------------------------------------- integral ----------------------------------------------------------------------------------------------------------
template<class T> T& _dataintegral<T>::operator++(){
                                                                daten++;
                                                                return(daten);
};
template<class T> T& _dataintegral<T>::operator--(){
                                                                daten--;
                                                                return(daten);
};
template<class T> T  _dataintegral<T>::operator%(const T t) const{
                                                                return((T)(daten%t));
};
template<class T> T& _dataintegral<T>::operator%=(const T t){
                                                                return(daten%=t);
};
template<class T> T  _dataintegral<T>::operator<<(const T t) const{
                                                                return((T)(daten<<t));
};
template<class T> T  _dataintegral<T>::operator>>(const T t) const{
                                                                return((T)(daten>>t));
};
template<class T> T& _dataintegral<T>::operator<<=(const T t){
                                                                return(daten<<=t);
};
template<class T> T& _dataintegral<T>::operator>>=(const T t){
                                                                return(daten>>=t);
};
//------------------------------------------------------------- relational --------------------------------------------------------------------------------------------------------
template<class T> bool _dataintegral<T>::operator<(const T t) const{
                                                                return(daten<t);
};
template<class T> bool _dataintegral<T>::operator>(const T t) const{
                                                                return(daten>t);
};
template<class T> bool _dataintegral<T>::operator<=(const T t) const{
                                                                return(daten<=t);
};
template<class T> bool _dataintegral<T>::operator>=(const T t) const{
                                                                return(daten>=t);
};
//-------------------------------------------------------------- arithmetical -----------------------------------------------------------------------------------------------------
template<class T> T _dataintegral<T>::operator+(const T t) const{
                                                                return((T)(daten+t));
};
template<class T> T& _dataintegral<T>::operator+=(const T t){
                                                                return(daten+=t);
};
template<class T> T _dataintegral<T>::operator-(const T t) const{
                                                                return((T)(daten-t));
};
template<class T> T& _dataintegral<T>::operator-=(const T t){
                                                                return(daten-=t);
};
template<class T> T _dataintegral<T>::operator-() const{
                                                                return((T)(daten*-1));
};
template<class T> T _dataintegral<T>::operator*(const T t) const{
                                                                return((T)(daten*t));
};
template<class T> T& _dataintegral<T>::operator*=(const T t){
                                                                return(daten*=t);
};
template<class T> T _dataintegral<T>::operator/(const T t) const{
                                                                return((T)(daten/t));
};
template<class T> T& _dataintegral<T>::operator/=(const T t){
                                                                return(daten/=t);
};
//------------------------------------------------------------- logical -----------------------------------------------------------------------------------------------------------
template<class T> bool _dataintegral<T>::operator&&(const T t) const{
                                                                return(daten&&t);
};
template<class T> bool _dataintegral<T>::operator||(const T t) const{
                                                                return(daten||t);
};
template<class T> bool _dataintegral<T>::operator!() const{
                                                                return(!daten);
};
//******************************************************************************************************************************************************************************************************
//                                                              D A T A E X P O N E N T I A L 
//******************************************************************************************************************************************************************************************************
template<class T>class _dataexponential{
        public:
                inline _dataexponential(const _dataexponential<T>&);
                inline _dataexponential(const T);
                inline _dataexponential();
                inline T& setzen(const T);
                inline T holen() const;
                //------------------ fundamental--------------
                inline                 operator T()                const;
                inline bool         operator==(const T)         const;
                inline bool         operator!=(const T)         const;
                inline T &        operator=(const T);
                //-----------------arithmetical---------------
                inline T         operator+(const T)         const;
                inline T&        operator+=(const T);
                inline T         operator-(const T)         const;
                inline T         operator-()                       const;
                inline T&        operator-=(const T);
                inline T         operator*(const T)           const;
                inline T&        operator*=(const T);
                inline T         operator/(const T)           const;
                inline T&        operator/=(const T);
                //---------------- relational-----------------
                inline bool        operator>=(const T)         const;
                inline bool        operator<=(const T)         const;
                inline bool        operator>(const T)         const;
                inline bool        operator<(const T)         const;
        private:
                T daten;
};
template<class T> _dataexponential<T>::_dataexponential(const _dataexponential<T>&d){
                                                                daten=d.daten;
                                                                };
template<class T> _dataexponential<T>::_dataexponential(const T d){
                                                                daten=d;
};
template<class T> _dataexponential<T>::_dataexponential(){
                                                                daten=0;
};
template<class T> _dataexponential<T>::operator T() const{
                                                                return(daten);
};
template<class T> bool _dataexponential<T>::operator==(const T t) const{
                                                                return(daten==t);

};
template<class T> bool _dataexponential<T>::operator!=(const T t) const{
                                                                return(daten!=t);
};
template<class T> T& _dataexponential<T>::operator=(const T t){
                                                                daten=t;
                                                                return(daten);
};
template<class T> T& _dataexponential<T>::setzen(const T t){
                                                                daten=t;
                                                                return(daten);
};
template<class T> T _dataexponential<T>::holen() const{
                                                                return(daten);
};
//------------------------------------------------------------- relational --------------------------------------------------------------------------------------------------------
template<class T> bool _dataexponential<T>::operator<(const T t) const{
                                                                return(daten<t);
};
template<class T> bool _dataexponential<T>::operator>(const T t) const{
                                                                return(daten>t);
};
template<class T> bool _dataexponential<T>::operator<=(const T t) const{
                                                                return(daten<=t);
};
template<class T> bool _dataexponential<T>::operator>=(const T t) const{
                                                                return(daten>=t);
};
//-------------------------------------------------------------- arithmetical -----------------------------------------------------------------------------------------------------
template<class T> T _dataexponential<T>::operator+(const T t) const{
                                                                return(daten+t);
};
template<class T> T& _dataexponential<T>::operator+=(const T t){
                                                                return(daten+=t);
};
template<class T> T _dataexponential<T>::operator-(const T t) const{
                                                                return(daten-t);
};
template<class T> T& _dataexponential<T>::operator-=(const T t){
                                                                return(daten-=t);
};
template<class T> T _dataexponential<T>::operator-() const{
                                                                return(daten*-1);
};
template<class T> T _dataexponential<T>::operator*(const T t) const{
                                                                return(daten*t);
};
template<class T> T& _dataexponential<T>::operator*=(const T t){
                                                                return(daten*=t);
};
template<class T> T _dataexponential<T>::operator/(const T t) const{
                                                                return(daten/t);
};
template<class T> T& _dataexponential<T>::operator/=(const T t){
                                                                return(daten/=t);
};
//******************************************************************************************************************************************************************************************************
//                                                              A S S O C I A T I O N 
//******************************************************************************************************************************************************************************************************
template<class T>class _assoziation{
        public:
                inline _assoziation();
                inline _assoziation(T*);
                inline T*setzen(T*);
                inline T*setzen(_assoziation<T>*);
                inline T*holen() const;
                //----------------- fundamental --------------
                inline                 operator T*()                 const;
                inline T*         operator=(T*);
                inline T*        operator=(_assoziation<T>*);
                inline T*        operator->(){
                                                        return(pointer);
                };
        private:
                T*pointer;
};
template<class T> _assoziation<T>::_assoziation(){
                                                                pointer=0;
};
template<class T> _assoziation<T>::_assoziation(T*p){
                                                                pointer=p;
};
template<class T> T* _assoziation<T>::setzen(T*p){
                                                                pointer=p;
                                                                return(pointer);
};

template<class T> T* _assoziation<T>::setzen(_assoziation<T>*p){
                                                                pointer=p->holen();
                                                                return(pointer);
};

template<class T> T* _assoziation<T>::holen() const{
                                                                return(pointer);
};
template<class T> _assoziation<T>::operator T*() const {
                                                                return(pointer);
};
template<class T> T* _assoziation<T>::operator=(T*p){
                                                                setzen(p);
                                                                return(p);
};
template<class T> T* _assoziation<T>::operator=(_assoziation<T>*p){
                                                                setzen(p);
                                                                return(p->holen());
};
//******************************************************************************************************************************************************************************************************
//                                                              B O O L 
//******************************************************************************************************************************************************************************************************
class _bool{
        public:
                inline _bool(const _bool&);
                inline _bool(const bool);
                inline _bool();
                inline bool& setzen(const bool);
                inline bool holen() const;
                //------------------ fundamental--------------
                inline                 operator bool()                const;
                inline bool         operator==(const bool)         const;
                inline bool         operator!=(const bool)         const;
                inline bool &        operator=(const bool);
                //------------------- logical ----------------
                inline bool        operator&&(const bool)         const;
                inline bool        operator||(const bool)         const;
                inline bool        operator!()                 const;
        private:
                bool daten;
};
//******************************************************************************************************************************************************************************************************
//                                                              C H A R 
//******************************************************************************************************************************************************************************************************
class _char:public _dataintegral<char>{
        public:
                _char();
                _char(const char);
                char& operator=(const char);
};
//******************************************************************************************************************************************************************************************************
//                                                              S C H A R 
//******************************************************************************************************************************************************************************************************
class _schar:public _dataintegral<signed char>{
        public:
                _schar();
                _schar(const signed char);
                signed char& operator=(const signed char);
};
//******************************************************************************************************************************************************************************************************
//                                                              S H O R T 
//******************************************************************************************************************************************************************************************************
class _short:public _dataintegral<signed short int>{
        public:
                _short();
                _short(const signed short int);
                signed short int& operator=(const signed short int);
};
//******************************************************************************************************************************************************************************************************
//                                                              U S H O R T 
//******************************************************************************************************************************************************************************************************
class _ushort:public _dataintegral<unsigned short int>{
        public:
                _ushort();
                _ushort(const unsigned short int);
                unsigned short int& operator=(const unsigned short int);
};
//******************************************************************************************************************************************************************************************************
//                                                              I N T 
//******************************************************************************************************************************************************************************************************
class _int:public _dataintegral<signed int>{
        public:
                _int();
                _int(const signed int);
                signed int& operator=(const signed int);
};
//******************************************************************************************************************************************************************************************************
//                                                              U I N T 
//******************************************************************************************************************************************************************************************************
class _uint:public _dataintegral<unsigned int>{
        public:
                _uint();
                _uint(const unsigned int);
                unsigned int& operator=(const unsigned int);
};
//******************************************************************************************************************************************************************************************************
//                                                              L O N G 
//******************************************************************************************************************************************************************************************************
class _long:public _dataintegral<signed long>{
        public:
                _long();
                _long(const signed long);
                signed long int& operator=(const signed long int);
};
//******************************************************************************************************************************************************************************************************
//                                                              U L O N G 
//******************************************************************************************************************************************************************************************************
class _ulong:public _dataintegral<unsigned long>{
        public:
                _ulong();
                _ulong(const unsigned long);
                unsigned long int& operator=(const unsigned long int);
};
//******************************************************************************************************************************************************************************************************
//                                                              F L O A T 
//******************************************************************************************************************************************************************************************************
class _float:public _dataexponential<float>{
        public:
                _float();
                _float(const float);
                float& operator=(const float);
};
//******************************************************************************************************************************************************************************************************
//                                                              D O U B L E 
//******************************************************************************************************************************************************************************************************
class _double:public _dataexponential<double>{
        public:
                _double();
                _double(const double);
                double& operator=(const double);
};
//******************************************************************************************************************************************************************************************************
//                                                              L O N G D O U B L E 
//******************************************************************************************************************************************************************************************************
class _longdouble:public _dataexponential<long double>{
        public:
                _longdouble();
                _longdouble(const long double);
                long double& operator=(const long double);
};
//******************************************************************************************************************************************************************************************************
//                                                              F I L E 
//******************************************************************************************************************************************************************************************************
class _datei{
        public:
                _datei(_zeichenkette<char>);
                _datei(_zeichenkette<char>,_zeichenkette<char>);
                _datei(_datei*);
                virtual ~_datei();
                FILE*dateihandle();
                void kopieren(_datei*);
                unsigned int groesse();
                bool erzeugen();
                char oeffnen();
                char oeffnennurlesen();
                char oeffnentext();
                void schliessen();
                void loeschen();
                void loeschenphysisch();
                _zeichenkette<char> dateiname() const;
                void dateiname(_zeichenkette<char>);
                void position(unsigned long int);
                unsigned long int position();
                bool ladentext(_zeichenkette<char>&);       //bei text          
                bool laden(char*,unsigned long int,unsigned long int&);
                bool laden(std::vector<unsigned char>&,unsigned int);
                template<class T> void laden(_vektor<T>&v);
                template<class T> void laden(_vektor2<T>&v);
                template<class T> void laden(_vektor3<T>&v);
                template<class T> void laden(_vektor4<T>&v);
                template<class T> bool laden(T&i);
                template<class T> bool laden(_zeichenkette<T>&t);
                void speicherntext(const _zeichenkette<char>&);
                void speicherneol(const _zeichenkette<char>&);
                void speichern(char*,unsigned long int);
                template<class T> void speichern(const _vektor<T>&v);
                template<class T> void speichern(const _vektor2<T>&v);
                template<class T> void speichern(const _vektor3<T>&v);
                template<class T> void speichern(const _vektor4<T>&v);
                template<class T> void speichern(T i);
                template<class T> void speichern(const _zeichenkette<T>&i);
        public:
                _zeichenkette<char> pname;
                FILE*pfile;   
                unsigned long int pposition;
                bool palwaysopen;
                bool pbinaryopen;
};
template<class T> bool _datei::laden(T&i){
                                                                i=0;
                                                                if((pfile)&&(pbinaryopen)){
                                                                 if(fread(&i,sizeof(T),1,pfile)) return(true);
                                                                }else{
                                                                 //error
                                                                };
                                                                return(false);
};
template<class T> void _datei::laden(_vektor<T>&v){
                                                                T x;
                                                                unsigned int d,i;
                                                                laden(d);
                                                                v.redimensionieren(d);
                                                                for(i=0;i<d;i++) {
                                                                 laden(x);
                                                                 v.setzenkomponente(i,x);
                                                                };
};

template<class T> void _datei::laden(_vektor2<T>&v){
                                                                T x;
                                                                T y;
                                                                laden(x);
                                                                laden(y);
                                                                v.setzen(x,y);
};
template<class T> void _datei::laden(_vektor3<T>&v){
                                                                T x;
                                                                T y;
                                                                T z;
                                                                laden(x);
                                                                laden(y);
                                                                laden(z);
                                                                v.setzen(x,y,z);
};
template<class T> void _datei::laden(_vektor4<T>&v){
                                                                T x;
                                                                T y;
                                                                T z;
                                                                T w;
                                                                laden(x);
                                                                laden(y);
                                                                laden(z);
                                                                laden(w);
                                                                v.setzen(x,y,z,w);
};

template<class T> bool _datei::laden(_zeichenkette<T>&t){
                                                                bool r=false;
                                                                if(pfile){
                                                                 if(!pbinaryopen){//wie gewohnt mit eol lesen
                                                                  char b[8192];
                                                                  if(fgets(b,8191,pfile)) r=true;
                                                                  t.kopierenchar(b);
                                                                  T eof[3]={13,10,0};
                                                                  _zeichenkette<T> hh;
                                                                  t.ersetzen(
                                                                  _zeichenkette<T>(eof),
                                                                  hh
                                                                  );
                                                                  r=true;
                                                                 }else{// binäres lesen mit null-terminator
                                                                  T b[8192];
                                                                  T h;
                                                                  unsigned int ti=0;
                                                                   size_t  fe;
                                                                  do{
                                                                  fe=fread(&h,sizeof(T),1,pfile);
                                                                   b[ti++]=h;
                                                                  }while((h!=0)&&(fe));
                                                                  t.kopieren(b);
                                                                  r=true;
                                                                 };
                                                                }else{
                                                                 //error
                                                                };
                                                                return(r);
};



template <class T> void _datei::speichern(T i){
                                                                if((pfile)&&(pbinaryopen)){
                                                                 fwrite(&i,sizeof(T),1,pfile);
                                                                }else{
                                                                 //error
                                                                };
};
template<class T> void _datei::speichern(const _vektor<T>&v){
																speichern(v.dimension());
																for(unsigned int i=0;i<v.dimension();i++) speichern(v[i]);
};
template<class T> void _datei::speichern(const _vektor2<T>&v){
                                                                speichern(v[0]);
                                                                speichern(v[1]);
};
template<class T> void _datei::speichern(const _vektor3<T>&v){
                                                                speichern(v[0]);
                                                                speichern(v[1]);
                                                                speichern(v[2]);
};
template<class T> void _datei::speichern(const _vektor4<T>&v){
                                                                speichern(v[0]);
                                                                speichern(v[1]);
                                                                speichern(v[2]);
                                                                speichern(v[3]);
};
template <class T> void _datei::speichern(const _zeichenkette<T>&t){
                                                                if(pfile){ 
                                                                 if(!pbinaryopen){
                                                                  fwrite(t.daten(),t.speicherlast(),1,pfile);
                                                                 }else{
                                                                  T h=0;
                                                                  unsigned int i=t.groesse();
                                                                  for(unsigned int n=0;n<i;n++){
                                                                   h=t[n];
                                                                   fwrite(&h,sizeof(T),1,pfile);
                                                                  };
                                                                  h=0;
                                                                  fwrite(&h,sizeof(T),1,pfile);
                                                                 };
                                                                }else{
                                                                };
};




//******************************************************************************************************************************************************************************************************
//                                                              F I L E L O G 
//******************************************************************************************************************************************************************************************************
class _logbuch:public _datei{
        public:
                _logbuch(_zeichenkette<char>);
                virtual ~_logbuch();
                void aktiv(bool);
                bool aktiv()const;
        public:
                void l(_zeichenkette<char>);
                void l(_zeichenkette<char>,_zeichenkette<char>);
                void l(_zeichenkette<char>,_zeichenkette<unsigned short int>);
                void l(_zeichenkette<char>,int);
                void l(_zeichenkette<char>,float);
                void l(_zeichenkette<char>,double);
                void l(_zeichenkette<char>,_vektor<float>);
                void l(_zeichenkette<char>,_vektor2<float>);
                void l(_zeichenkette<char>,_vektor3<float>);
                void l(_zeichenkette<char>,_vektor4<float>);
                void l(_zeichenkette<char>,_vektor<double>);
                void l(_zeichenkette<char>,_vektor2<double>);
                void l(_zeichenkette<char>,_vektor3<double>);
                void l(_zeichenkette<char>,_vektor4<double>);


               // void schreiben(_zeichenkette<char>,_zeichenkette<char>);
                void schreiben(_zeichenkette<char>);
                void schreiben(_zeichenkette<char>,_zeichenkette<char>);
                void schreiben(_zeichenkette<char>,_zeichenkette<unsigned short int>);
                void schreiben(_zeichenkette<char>,int);
                void schreiben(_zeichenkette<char>,float);
                void schreiben(_zeichenkette<char>,double);
                void schreiben(_zeichenkette<char>,_vektor<float>);
                void schreiben(_zeichenkette<char>,_vektor2<float>);
                void schreiben(_zeichenkette<char>,_vektor3<float>);
                void schreiben(_zeichenkette<char>,_vektor4<float>);
                void schreiben(_zeichenkette<char>,_vektor<double>);
                void schreiben(_zeichenkette<char>,_vektor2<double>);
                void schreiben(_zeichenkette<char>,_vektor3<double>);
                void schreiben(_zeichenkette<char>,_vektor4<double>);
                void fehler(_zeichenkette<char>);
                void fehler(_zeichenkette<char>,_zeichenkette<char>);
                void fehler(_zeichenkette<char>,int);
                void fehler(_zeichenkette<char>,double);
                void fehler(_zeichenkette<char>,_vektor<double>);
                void fehler(_zeichenkette<char>,_vektor2<double>);
                void fehler(_zeichenkette<char>,_vektor3<double>);
                void fehler(_zeichenkette<char>,_vektor4<double>);
               /* void schreiben(_zeichenkette,_zeichenkette);
                void schreiben(char*,float);
                void schreiben(char*,float*);
                void schreiben(char*,float*,int);
                void schreiben(char*,float,char*,int);
                void schreiben(char*,int);
                void fehler(char*,char*);
                */
        private:
                bool paktiv;
};
extern _logbuch*L;
//******************************************************************************************************************************************************************************************************
//                                                              F I L E S T O R E A B L E 
//******************************************************************************************************************************************************************************************************
class _dateispeicherbar:public _datei,public _listebasis<_basis::_speicherbar >{
        public:
        using _datei::laden;
        using _datei::speichern;
        public:
                _dateispeicherbar(_zeichenkette<char>);
                virtual ~_dateispeicherbar();
                //char oeffnen(const char*);
                //void schliessen();
                virtual void speichern()=0;
                void schreiben(const char*);
                void schreiben(const _zeichenkette<char>&);
               // void writevalue(const _zeichenkette&,_basis::_speicherbar*);
                void schreibenreturn();
                void schreibenleerraum();
                void inkleerraum();
                void dekleerraum();
                virtual char laden()=0;
                void zerlegen(const _zeichenkette<char>&name,_liste<_zeichenkette<char> >*lz)const;
                char holenuebertyp(const _zeichenkette<char>&,_liste<_dateispeicherbarknoten >&) const;
                char holenuebername(const _zeichenkette<char>&,_liste<_dateispeicherbarknoten >&) const;
                char holenspeicherbaruebermodus(char,_liste<_basis::_speicherbar >&);
                char holenspeicherbaruebertyp(const _zeichenkette<char>&,_liste<_basis::_speicherbar >&);
                char holenspeicherbaruebername(const _zeichenkette<char>&,_liste<_basis::_speicherbar >&);
                //void setpos(unsigned long);
                int lesen(char&);
                char assoziieren();
                char lesenzeile(_zeichenkette<char>&,unsigned long int&);
        protected:
                //unsigned long int getpos();
                _listebasis<_dateispeicherbarknoten >*nodes() const;
        private:
                _zeichenkette<char> name;
                int leertaste;
                FILE*datei;
                _listebasis<_dateispeicherbarknoten >*lnodes;
                bool bblockmodus();
};

//******************************************************************************************************************************************************************************************************
//                                                              F I L E S T O R E A B L E T E X T 
//******************************************************************************************************************************************************************************************************
class _dateispeicherbartext:public _dateispeicherbar{
        public:
                _dateispeicherbartext(_zeichenkette<char>);
                virtual char laden();
                virtual void speichern();
        private:
                void ladenidentifikation(_dateispeicherbarknoten*);
                void ladenidentifikation(unsigned long int,unsigned long int,_dateispeicherbarknoten*,char);
                char lesenkommentare(bool,_zeichenkette<char>&,unsigned int&,unsigned long int&,unsigned long int,_liste<_dateispeicherbarkommentar >&,bool&,bool);
                void lesenkommentarehinten(unsigned long int,_liste<_dateispeicherbarkommentar >&);
};
/*
//******************************************************************************************************************************************************************************************************
//                                                              F I L E S T O R E A B L E B I N A R Y 
//******************************************************************************************************************************************************************************************************
class _dateispeicherbarbinaer:public _dateispeicherbar{
        public:
                _dateispeicherbarbinaer(_zeichenkette<char>);
                virtual char laden();
                virtual void speichern();
};*/
//******************************************************************************************************************************************************************************************************
//                                                              F I L E S T O R E A B L E I D E N T I F I C A T I O N 
//******************************************************************************************************************************************************************************************************
class _dateispeicherbaridentifikation{
        public:
                ~_dateispeicherbaridentifikation();
                void name(const _zeichenkette<char>);
                void typ(const _zeichenkette<char>);
                void format(const _zeichenkette<char>);
                void filter(_zeichenkette<char>&);
                const _zeichenkette<char>& typ() const;
                const _zeichenkette<char>& name() const;
                const _zeichenkette<char>& format() const;
                void kommentar(const _zeichenkette<char>);
                void kommentar(const _zeichenkette<char>,char);
                _liste<_dateispeicherbarkommentar >*comments();
                void kopieren(_dateispeicherbaridentifikation*);
        private:
                _zeichenkette<char> stype;
                _zeichenkette<char> sname;
                _zeichenkette<char> sformat;
                _liste<_dateispeicherbarkommentar > coms;
};
//******************************************************************************************************************************************************************************************************
//                                                              F I L E S T O R E A B L E N O D E 
//******************************************************************************************************************************************************************************************************
class _dateispeicherbarknoten:public _dateispeicherbaridentifikation,public _listelistenknotenbasis<_dateispeicherbarknoten >{
        
        public:
                _dateispeicherbarknoten(_listebasis<_dateispeicherbarknoten >*,unsigned long int);
                _dateispeicherbarknoten(_dateispeicherbarknoten*,unsigned long int);
                ~_dateispeicherbarknoten();

                void end(unsigned long int);
                void knoten(unsigned long int);
                unsigned long int end() const;
                unsigned long int knoten() const;
                unsigned long int begin() const;
                _dateispeicherbarknoten*dateiknoten() const;
                char holenuebername(const _zeichenkette<char>&,_liste<_dateispeicherbarknoten >&);
                char holenuebername(const _zeichenkette<char>&t,_liste<_dateispeicherbarknoten >&l,_liste<_zeichenkette<char> >*lz,_listenknoten<_zeichenkette<char> >*lit);
                char holenuebertyp(const _zeichenkette<char>&,_liste<_dateispeicherbarknoten >&);
                char holenuebertyp(const _zeichenkette<char>&t,_liste<_dateispeicherbarknoten >&l,_liste<_zeichenkette<char> >*lz,_listenknoten<_zeichenkette<char> >*lit);
                void holennamenqualifikation(_zeichenkette<char>&);
                void holentypqualifikation(_zeichenkette<char>&);
                void bereitsgeladen(const bool b);
                bool bereitsgeladen()const;
        private:
                unsigned long int lnode;
                unsigned long int lbegin;
                unsigned long int lend;
                _dateispeicherbarknoten*pfilenode;//rückzeiger
                bool pbereitsgeladen;
};
//******************************************************************************************************************************************************************************************************
//                                                              F I L E S T O R E A B L E C O M M E N T 
//******************************************************************************************************************************************************************************************************
class _dateispeicherbarkommentar{
        public:
                _dateispeicherbarkommentar(const _zeichenkette<char>);
                _dateispeicherbarkommentar(const _zeichenkette<char>,bool);
                _zeichenkette<char> kommentar() const;
                bool hintenangestellt() const;
        private:
                void filter();
        private:
                _zeichenkette<char> com;
                bool bs;
};
//******************************************************************************************************************************************************************************************************
//                                                              B A S E : : S T O R E A B L E 
//******************************************************************************************************************************************************************************************************
namespace _basis{
 class _speicherbar:public _dateispeicherbaridentifikation,public _listelistenknotenbasis<_speicherbar >{
        public:
                using _dateispeicherbaridentifikation::typ;
        public://Grundfunktionen
                _speicherbar(_dateispeicherbar*);                                         //anlegen: oberste Hierarchieebene der Datei
                _speicherbar(_dateispeicherbar*,_speicherbar*);                  //anlegen: verschachtelte Hierachieebene der Datei                        
                virtual ~_speicherbar();
                _speicherbar*speicherbar() const;
                _dateispeicherbar*datei();
                //schnittstelle
                virtual char laden(_dateispeicherbarknoten*);
                virtual void speichern();
                virtual char assoziieren();
                //suche- und qualifikationesfunktionen
                char holenuebermodus(char,::_liste<_speicherbar >&);
                char holenuebername(const _zeichenkette<char>&n,::_liste<_speicherbar >&l,::_liste<_zeichenkette<char> >*lz,::_listenknoten<_zeichenkette<char> >*lit);
                char holenuebername(const _zeichenkette<char>&,::_liste<_speicherbar >&);
                char holenuebertyp(const _zeichenkette<char>&,::_liste<_speicherbar >&);
                void holennamenqualifikation(_zeichenkette<char>&);
                void holentypqualifikation(_zeichenkette<char>&);
        public://speichern/laden-Funktionen, die nicht redefiniert werden
                void speichernbeginn();
                void speichernbeginnblock();
                void speichernverschachtelung();
                void speichernwert(bool);
                void speichernwert(int);
                void speichernwert(unsigned int);
                void speichernwert(float);
                void speichernwert(double);
                void speichernwert(_vektor<float>);
                void speichernwert(_vektor2<float>);
                void speichernwert(_vektor3<float>);
                void speichernwert(_vektor4<float>);
                void speichernwert(_vektor<double>);
                void speichernwert(_vektor2<double>);
                void speichernwert(_vektor3<double>);
                void speichernwert(_vektor4<double>);
                void speichernwert(_zeichenkette<char>&);
                void speichernwertroh(_zeichenkette<char>);
                void speichernende();
                void speichernendeblock();
                char ladenbeginn(_dateispeicherbarknoten*);
                char ladenverschachtelung(_dateispeicherbarknoten*);
                char ladenwerte(::_liste<_zeichenkette<char> >&);
                char ladenassoziation();
                char ladenwert(bool&);
                char ladenwert(int&);
                char ladenwert(unsigned int&);
                char ladenwert(float&);
                char ladenwert(double&);
                char ladenwert(_vektor<float>&);
                char ladenwert(_vektor2<float>&);
                char ladenwert(_vektor3<float>&);
                char ladenwert(_vektor4<float>&);
                char ladenwert(_vektor<double>&);
                char ladenwert(_vektor2<double>&);
                char ladenwert(_vektor3<double>&);
                char ladenwert(_vektor4<double>&);
                char ladenwert(_zeichenkette<char>&);
                void ladenende();
                char assoziierenverschachtelung();
                _zeichenkette<char>*assoziation();
        private:
                void speichernhintenangestelltekommentare();
                char ladenwerte(_dateispeicherbarknoten*);
                char ladenwerte(unsigned long int,unsigned long int);
        public://statusfunktionen
                char basis() const;
                char schnittstelle() const;
                char argument() const;
                char modus() const;
                bool aktiv() const;
                void aktivitaet(bool);
               /* void firstvalue(bool);
                bool firstvalue() const;  */
                bool blockmodus() const;
        protected://statusfunktionen
                void modusbasis();
                void modusschnittstelle();
                void modusargument();
        private:
                _speicherbar*pstoreable;//rückassoviatiob zu dem verwaltenden speicherbar, kann demnach auch null sein
                _dateispeicherbar*ffile;//Zeiger auf die Datei muss gesetzt sein
                bool bactive;//Aktivität
                char cmode;//Modus 0 = _basis::speicherbar , 1 = _speicherbardynamischvererbungsschnittstelle<T> , 2 = _speicherbardynamisch<T>
                bool bblockmodus;
                ::_liste<_zeichenkette<char> > values;
                ::_liste<_zeichenkette<char> > valueassociations;
                ::_listenknoten<_zeichenkette<char> >*sit;
                ::_listenknoten<_zeichenkette<char> >*ait;
                //bool fvalue;
 };
};
//******************************************************************************************************************************************************************************************************
//                                                              B A S E : : S T O R E A B L E D Y N A M I C 
//******************************************************************************************************************************************************************************************************
namespace _basis{
 template<class T>class _speicherbardynamisch{
        public://Grundfunktionen
                _speicherbardynamisch();
                ~_speicherbardynamisch();
                void null();
                _speicherbardynamischvererbungsschnittstelle<T>*speicherbar() const;
                _dateispeicherbar*datei();
                void speicherbarkeit(_dateispeicherbar*,T*);
                void speicherbarkeit(_dateispeicherbar*,_basis::_speicherbar*,T*);
                void speicherbarkeitaus();
                void speicherbarkeit();
        public://identificationsfunktionen
                void name(const _zeichenkette<char>&);
                void typ(const _zeichenkette<char>&);
                void format(const _zeichenkette<char>&);
                _zeichenkette<char> typ() const;
                _zeichenkette<char> name() const;
                _zeichenkette<char> format() const;
                void kommentar(const _zeichenkette<char>&);
                void kommentar(const _zeichenkette<char>&,char);
                ::_liste<_dateispeicherbarkommentar >*comments();
        public://schnittstelle
                virtual char laden(_dateispeicherbarknoten*);
                virtual void speichern();
                virtual char assoziieren();
                //suche- und qualifikationesfunktionen
                char holenuebermodus(char,::_liste<_speicherbar >&);
                char holenuebername(const _zeichenkette<char>&,::_liste<_speicherbar >&);
                char holenuebertyp(const _zeichenkette<char>&,::_liste<_speicherbar >&);
                void holennamenqualifikation(_zeichenkette<char>&);
                void holentypqualifikation(_zeichenkette<char>&);
        public://laden/speichern - funktionen, die nicht redefiniert werden
                void speichernbeginn();
                void speichernbeginnblock();
                void speichernverschachtelung();
                void speichernwert(int);
                void speichernwert(float);
                void speichernwert(_zeichenkette<char>&);
                void speichernwertroh(_zeichenkette<char>);
                void speichernende();
                void speichernendeblock();
                char ladenbeginn(_dateispeicherbarknoten*);
                char ladenverschachtelung(_dateispeicherbarknoten*);
                char ladenwerte(::_liste<_zeichenkette<char> >&);
                char ladenassoziation();
                char ladenwert(int&);
                char ladenwert(float&);
                char ladenwert(_zeichenkette<char>&);
                void ladenende();
                char assoziierenverschachtelung();
                _zeichenkette<char>*assoziation();
        public://statusfunkttionen
                char basis() const;
                char schnittstelle() const;
                char argument() const;
                char modus() const;
                bool aktiv() const;
               /* void firstvalue(bool);
                bool firstvalue() const;*/
                bool blockmodus() const;
        protected://statusfunktionen
                void aktivitaet(bool);
        private:
                _speicherbardynamischvererbungsschnittstelle<T>*pstoreable;//Zeiger auf die speicherbar-schnittstelle

 };
 template<class T>_speicherbardynamisch<T>::_speicherbardynamisch(){
                                                                null();
 
 };
 template<class T>_speicherbardynamisch<T>::~_speicherbardynamisch(){
                                                                speicherbarkeitaus();
 };
 template<class T>void _speicherbardynamisch<T>::null(){
                                                                pstoreable=0;
 };
 //------------------------------------------------------------- SCHNITTSTELLE -----------------------------------------------------------------------------------------------------
 template<class T>::_speicherbardynamischvererbungsschnittstelle<T>*_speicherbardynamisch<T>::speicherbar() const{
                                                                return(pstoreable);
 };
 template<class T>_dateispeicherbar* _speicherbardynamisch<T>::datei(){
                                                                if(pstoreable) return(pstoreable->datei()); else return(0);
 };
 template<class T>void _speicherbardynamisch<T>::speicherbarkeit(_dateispeicherbar*f,T*o){
                                                                speicherbarkeitaus();
                                                                pstoreable=new ::_speicherbardynamischvererbungsschnittstelle<T>(f,o,this);
 };
 template<class T>void _speicherbardynamisch<T>::speicherbarkeit(_dateispeicherbar*f,_basis::_speicherbar*s,T*o){
                                                                speicherbarkeitaus();
                                                                pstoreable=new ::_speicherbardynamischvererbungsschnittstelle<T>(f,s,o,this);
 };
 template<class T>void _speicherbardynamisch<T>::speicherbarkeit(){
                                                                if(pstoreable){
                                                                 delete pstoreable;
                                                                 null();
                                                                };
 };
 template<class T>void _speicherbardynamisch<T>::speicherbarkeitaus(){
                                                                speicherbarkeit();
 };
 template<class T>char _speicherbardynamisch<T>::laden(_dateispeicherbarknoten*f){
                                                                char r;
                                                                //-----
                                                                r=0;
                                                                 if(pstoreable){
                                                                 r|=pstoreable->ladenbeginn(f);
                                                                 r|=pstoreable->ladenverschachtelung(f);
                                                                 pstoreable->ladenende();
                                                                };
                                                                return(r);
 };
 template<class T>void _speicherbardynamisch<T>::speichern(){
                                                                if(pstoreable){
                                                                 pstoreable->speichernbeginnblock();
                                                                 pstoreable->speichernverschachtelung();
                                                                 pstoreable->speichernendeblock();
                                                                };
 };
 template<class T>char _speicherbardynamisch<T>::assoziieren(){
                                                                return(assoziierenverschachtelung());
 };
 //------------------------------------------------------------- IDENTIFIKATIONSFUNKTIONEN -----------------------------------------------------------------------------------------
 template<class T>char _speicherbardynamisch<T>::holenuebermodus(char m,::_liste<_speicherbar >&l){
                                                                if(pstoreable) return(pstoreable->holenuebermodus(m,l)); else return(0);
 };
 template<class T>char _speicherbardynamisch<T>::holenuebername(const _zeichenkette<char>&s,::_liste<_speicherbar >&l){
                                                                if(pstoreable) return(pstoreable->holenuebername(s,l)); else return(0);
 };
 template<class T>char _speicherbardynamisch<T>::holenuebertyp(const _zeichenkette<char>&s,::_liste<_speicherbar >&l){
                                                                if(pstoreable) return(pstoreable->holenuebertyp(s,l)); else return(0);
 };
 template<class T>void _speicherbardynamisch<T>::holennamenqualifikation(_zeichenkette<char>&s){
                                                                if(pstoreable) pstoreable->holennamenqualifikation(s);
 };
 template<class T>void _speicherbardynamisch<T>::holentypqualifikation(_zeichenkette<char>&s){
                                                                if(pstoreable) pstoreable->holentypqualifikation(s);
 };
 template<class T>_zeichenkette<char> _speicherbardynamisch<T>::typ() const{
                                                                if(pstoreable) return(pstoreable->typ()); else return((char*)"");
 };
 template<class T>_zeichenkette<char> _speicherbardynamisch<T>::name() const{
                                                                if(pstoreable) return(pstoreable->name()); else return((char*)"");
 };
 template<class T>_zeichenkette<char> _speicherbardynamisch<T>::format() const{
                                                                if(pstoreable) return(pstoreable->format()); else return((char*)"");
 };
 template<class T>void _speicherbardynamisch<T>::typ(const _zeichenkette<char>&s){
                                                                if(pstoreable) pstoreable->typ(s);
 };
 template<class T>void _speicherbardynamisch<T>::name(const _zeichenkette<char>&s){
                                                                if(pstoreable) pstoreable->name(s);
 };
 template<class T>void _speicherbardynamisch<T>::format(const _zeichenkette<char>&s){
                                                                if(pstoreable) pstoreable->format(s);
 };
 template<class T>void _speicherbardynamisch<T>::kommentar(const _zeichenkette<char>&s){
                                                                if(pstoreable) pstoreable->kommentar(s);
 };
 template<class T>void _speicherbardynamisch<T>::kommentar(const _zeichenkette<char>&s,char c){
                                                                if(pstoreable) pstoreable->kommentar(s,c);
 };
 template<class T>::_liste<_dateispeicherbarkommentar >*_speicherbardynamisch<T>::comments(){
                                                                if(pstoreable) return(pstoreable->comments()); else return(0);
 };
 //------------------------------------------------------------- LOAD/SAVE-FUNKTIONEN, DIE NICHT REDEFINIERT WERDEN --------------------------------------------------------------
 template<class T>void _speicherbardynamisch<T>::speichernbeginn(){
                                                                if(pstoreable) pstoreable->speichernbeginn();
 };
 template<class T>void _speicherbardynamisch<T>::speichernbeginnblock(){
                                                                if(pstoreable) pstoreable->speichernbeginnblock();
 };
 template<class T>void _speicherbardynamisch<T>::speichernverschachtelung(){
                                                                if(pstoreable) pstoreable->speichernverschachtelung();
 };
 template<class T>void _speicherbardynamisch<T>::speichernwert(int i){
                                                                if(pstoreable) pstoreable->speichernwert(i);
 };
 template<class T>void _speicherbardynamisch<T>::speichernwert(float f){
                                                                if(pstoreable) pstoreable->speichernwert(f);
 };
 template<class T>void _speicherbardynamisch<T>::speichernwert(_zeichenkette<char>&s){
                                                                if(pstoreable) pstoreable->speichernwert(s);
 };
 template<class T>void _speicherbardynamisch<T>::speichernwertroh(_zeichenkette<char> s){
                                                                if(pstoreable) pstoreable->speichernwertroh(s);
 };
 template<class T>void _speicherbardynamisch<T>::speichernende(){
                                                                if(pstoreable) pstoreable->speichernende();
 };
 template<class T>void _speicherbardynamisch<T>::speichernendeblock(){
                                                                if(pstoreable) pstoreable->speichernendeblock();
 };
 template<class T>char _speicherbardynamisch<T>::ladenbeginn(_dateispeicherbarknoten*f){
                                                                if(pstoreable) return(pstoreable->ladenbeginn(f)); else return(0);
 };
 template<class T>char _speicherbardynamisch<T>::ladenverschachtelung(_dateispeicherbarknoten*f){
                                                                if(pstoreable) return(pstoreable->ladenverschachtelung(f)); else return(0);
 };
 template<class T>char _speicherbardynamisch<T>::ladenassoziation(){
                                                                if(pstoreable) return(pstoreable->ladenassoziation()); else return(0);
 };
 template<class T>char _speicherbardynamisch<T>::ladenwerte(::_liste<_zeichenkette<char> >&l){
                                                                if(pstoreable) return(pstoreable->ladenwerte(l)); else return(0);
 };
 template<class T>char _speicherbardynamisch<T>::ladenwert(int&i){
                                                                if(pstoreable) return(pstoreable->ladenwert(i)); else return(0);
 };
 template<class T>char _speicherbardynamisch<T>::ladenwert(float&f){
                                                                if(pstoreable) return(pstoreable->ladenwert(f)); else return(0);
 };
 template<class T>char _speicherbardynamisch<T>::ladenwert(_zeichenkette<char>&s){
                                                                if(pstoreable) return(pstoreable->ladenwert(s)); else return(0);
 };
 template<class T>void _speicherbardynamisch<T>::ladenende(){
                                                                if(pstoreable) pstoreable->ladenende();
 };
 template<class T>char _speicherbardynamisch<T>::assoziierenverschachtelung(){
                                                                if(pstoreable) return(pstoreable->assoziierenverschachtelung()); else return(0);
 };
 template<class T>_zeichenkette<char>* _speicherbardynamisch<T>::assoziation(){
                                                                if(pstoreable) return(pstoreable->assoziation()); else return(0);
 };
 //------------------------------------------------------------- STATUSFUNKTIONEN --------------------------------------------------------------------------------------------------
 template<class T> char _speicherbardynamisch<T>::basis() const{
                                                                if(pstoreable) return(pstoreable->basis()); else return(0);
 };
 template<class T> char _speicherbardynamisch<T>::schnittstelle() const{
                                                                if(pstoreable) return(pstoreable->schnittstelle()); else return(0);
 };
 template<class T> char _speicherbardynamisch<T>::argument() const{
                                                                if(pstoreable) return(pstoreable->argument()); else return(0);
 };
 template<class T> char _speicherbardynamisch<T>::modus() const{
                                                                if(pstoreable) return(pstoreable->modus()); else return(0);
 };
 template<class T> bool _speicherbardynamisch<T>::blockmodus() const{
                                                                if(pstoreable) return(pstoreable->blockmodus()); else return(0);
 };
 template<class T> bool _speicherbardynamisch<T>::aktiv() const{
                                                                if(pstoreable) return(pstoreable->aktiv()); else return(0);
 };
 template<class T> void _speicherbardynamisch<T>::aktivitaet(bool b){
                                                                if(pstoreable) pstoreable->aktivitaet(b);
 };
};
//******************************************************************************************************************************************************************************************************
//                                                              B A S I S :: S P E I C H E R B A R A R G U M E N T 
//******************************************************************************************************************************************************************************************************
namespace _basis{
 template<class T>class _speicherbarargument{
        friend class ::_speicherbardynamisch<T>;
        public:
                _speicherbarargument();
                virtual ~_speicherbarargument();
                _basis::_speicherbar*speicherbar();
        public:
                void speicherbar(_basis::_speicherbar*);                
        private:
                _basis::_speicherbar*pspeicherbar;
 };
};
//******************************************************************************************************************************************************************************************************
//                                                              B A S I S :: S P E I C H E R B A R A R G U M E N T 
//******************************************************************************************************************************************************************************************************
namespace _basis{
 template<class T>_speicherbarargument<T>::_speicherbarargument(){
                                                                pspeicherbar=0;
 };
 template<class T>_speicherbarargument<T>::~_speicherbarargument(){
 };
 template<class T>void _speicherbarargument<T>::speicherbar(_basis::_speicherbar*s){
                                                                pspeicherbar=s;
 };
 template<class T>_basis::_speicherbar*_speicherbarargument<T>::speicherbar(){
                                                                return(pspeicherbar);
 };
};

//******************************************************************************************************************************************************************************************************
//                                                              : : S T O R E A B L E D Y N A M I C 
//******************************************************************************************************************************************************************************************************
template<class T>class _speicherbardynamisch:public _basis::_speicherbar{
        public:
                _speicherbardynamisch(_dateispeicherbar*,T*);
                _speicherbardynamisch(_dateispeicherbar*,_basis::_speicherbar*,T*);
                virtual ~_speicherbardynamisch();                
                T*objekt() const;
                virtual char laden(_dateispeicherbarknoten*);
                virtual void speichern();
                virtual char assoziieren();
        private:
                T*pobject;
};
template<class T>_speicherbardynamisch<T>::_speicherbardynamisch(_dateispeicherbar*f,T*o):_basis::_speicherbar(f),pobject(o){
                                                                typ(::gettypename<T>(/*o*/));
                                                                modusargument();
                                                                o->_basis::_speicherbarargument<T>::speicherbar(this);
};
template<class T>_speicherbardynamisch<T>::_speicherbardynamisch(_dateispeicherbar*f,_basis::_speicherbar*s,T*o):_basis::_speicherbar(f,s),pobject(o){
                                                                typ(::gettypename<T>(/*o*/));
                                                                modusargument();
                                                                o->_basis::_speicherbarargument<T>::speicherbar(this);
};
template<class T>_speicherbardynamisch<T>::~_speicherbardynamisch(){
                                                                pobject->_basis::_speicherbarargument<T>::speicherbar(0);
};

template<class T> T * _speicherbardynamisch<T>::objekt() const{
                                                                return(pobject);
};
template<class T>char _speicherbardynamisch<T>::laden(_dateispeicherbarknoten*f){
                                                                return(pobject->laden(f,this));
};
template<class T>void _speicherbardynamisch<T>::speichern(){
 
                                                                pobject->speichern(this);
};
template<class T>char _speicherbardynamisch<T>::assoziieren(){
                                                                return(pobject->assoziieren(this));
};
//******************************************************************************************************************************************************************************************************
//                                                              S T O R E A B L E I N H E R I T A N C E I N T E R F A C E 
//******************************************************************************************************************************************************************************************************
template<class T>class _speicherbardynamischvererbungsschnittstelle:public _basis::_speicherbar{
        public:
                _speicherbardynamischvererbungsschnittstelle(_dateispeicherbar*,T*,_basis::_speicherbardynamisch<T>*);
                _speicherbardynamischvererbungsschnittstelle(_dateispeicherbar*,_basis::_speicherbar*,T*,_basis::_speicherbardynamisch<T>*);
                virtual ~_speicherbardynamischvererbungsschnittstelle();
                T*objekt() const;
                _basis::_speicherbardynamisch<T>*speicherbar() const;
                virtual char laden(_dateispeicherbarknoten*);
                virtual void speichern();
                virtual char assoziieren();
        private:
                T*pobject;
                _basis::_speicherbardynamisch<T>*pstoreable;
};
template<class T>_speicherbardynamischvererbungsschnittstelle<T>::_speicherbardynamischvererbungsschnittstelle(_dateispeicherbar*f,T*o,_basis::_speicherbardynamisch<T>*ps):_basis::_speicherbar(f),pobject(o),pstoreable(ps){
                                                                typ(::gettypename<T>(/*o*/));
                                                                modusschnittstelle();
};
template<class T>_speicherbardynamischvererbungsschnittstelle<T>::_speicherbardynamischvererbungsschnittstelle(_dateispeicherbar*f,_basis::_speicherbar*s,T*o,_basis::_speicherbardynamisch<T>*ps):_basis::_speicherbar(f,s),pobject(o),pstoreable(ps){
                                                                typ(::gettypename<T>(/*o*/));
                                                                modusschnittstelle();
};
template<class T>_speicherbardynamischvererbungsschnittstelle<T>::~_speicherbardynamischvererbungsschnittstelle(){
                                                                if(pstoreable){
                                                                 pstoreable->null();
                                                                 pstoreable=0;
                                                                };
};
template<class T>T* _speicherbardynamischvererbungsschnittstelle<T>::objekt() const{
                                                                return(pobject);
};
template<class T>_basis::_speicherbardynamisch<T>*_speicherbardynamischvererbungsschnittstelle<T>::speicherbar() const{
                                                                return(pstoreable);
};
template<class T>char _speicherbardynamischvererbungsschnittstelle<T>::laden(_dateispeicherbarknoten*f){
                                                                if(pstoreable){
                                                                 return(pstoreable->laden(f));
                                                                }else{
                                                                 //error
                                                                 return(0);
                                                                };
};
template<class T>void _speicherbardynamischvererbungsschnittstelle<T>::speichern(){
                                                                if(pstoreable){
                                                                 pstoreable->speichern();
                                                                }else{
                                                                 //error
                                                                };
};
template<class T>char _speicherbardynamischvererbungsschnittstelle<T>::assoziieren(){
                                                                if(pstoreable){
                                                                 return(pstoreable->assoziieren());
                                                                }else{
                                                                 return(0);
                                                                 //error
                                                                };
};
//******************************************************************************************************************************************************************************************************
//                                                              S T O R E I N T 
//******************************************************************************************************************************************************************************************************
 class _speicherint:public virtual _int,public _basis::_speicherbar{
        public:
                _speicherint(_dateispeicherbar*);
                _speicherint(_dateispeicherbar*,_basis::_speicherbar*);
                _speicherint(_dateispeicherbar*,int);
                virtual ~_speicherint();
                int& operator=(const int);
                virtual char laden(_dateispeicherbarknoten*);
                virtual void speichern();
};
//******************************************************************************************************************************************************************************************************
//                                                              S T O R E F L O A T 
//******************************************************************************************************************************************************************************************************
class _speicherfloat:public virtual _float,public _basis::_speicherbar{
        public:
                _speicherfloat(_dateispeicherbar*);
                _speicherfloat(_dateispeicherbar*,_basis::_speicherbar*);
                float& operator=(const float);
                virtual char laden(_dateispeicherbarknoten*);
                virtual void speichern();
};
//******************************************************************************************************************************************************************************************************
//                                                              S T O R E A S S O C I A T I O N B A S E 
//******************************************************************************************************************************************************************************************************
template<class T>class _speicherassoziationbasis:public _basis::_speicherbar,public virtual _assoziation<T>{
        public:
                _speicherassoziationbasis(_dateispeicherbar*);
                _speicherassoziationbasis(_dateispeicherbar*,_basis::_speicherbar*);
                inline operator T*() const;
                inline T*        operator=(T*);
                virtual char laden(_dateispeicherbarknoten*);
                virtual void speichern();
                virtual char assoziieren();
        private:
                char suchen(_zeichenkette<char>,_basis::_speicherbar*&);
};
template<class T>_speicherassoziationbasis<T>::_speicherassoziationbasis(_dateispeicherbar*f):_basis::_speicherbar(f){
                                                                typ(::gettypename<_speicherassoziationbasis<T> >());
};
template<class T>_speicherassoziationbasis<T>::_speicherassoziationbasis(_dateispeicherbar*f,_basis::_speicherbar*s):_basis::_speicherbar(f,s){
                                                                typ(::gettypename<_speicherassoziationbasis<T> >());
};

template<class T>_speicherassoziationbasis<T>::operator T*() const{

                                                                return(this->holen());
};

template<class T> T* _speicherassoziationbasis<T>::operator=(T*p){
                                                                setzen(p);
                                                                return(p);
};

template<class T>char _speicherassoziationbasis<T>::laden(_dateispeicherbarknoten*f){
                                                                _liste<_zeichenkette<char> > sl;
                                                                char r;
                                                                //----------
                                                                ladenbeginn(f);
                                                                ladenverschachtelung(f);
                                                                r=ladenassoziation();
                                                                ladenende();
                                                                return(r);
};
template<class T>void _speicherassoziationbasis<T>::speichern(){
                                                                speichernbeginn();
                                                                if(this->holen()) saveassociationbase<_speicherassoziationbasis<T>,T>(this,this->holen());
                                                                speichernende();
};
template<class T>char _speicherassoziationbasis<T>::assoziieren(){
                                                                T*anderes;
                                                                _basis::_speicherbar*found;
                                                                char r;
                                                                _zeichenkette<char> value=assoziation();
                                                                //---------
                                                                r=0;
                                                                if(value!=(char*)""){
                                                                 //char t[128];
                                                                 //printf("will %s assoziieren...\n",value.holen(t));
                                                                 if(suchen(value,found)){
                                                                  //printf("suche erfolgreich!!!!\n");
                                                                  anderes=dynamic_cast<T*>(found);
                                                                  if(anderes){
                                                                   //printf("dynaimc_cast erfolgreich!!!!!\n");
                                                                   setzen(anderes);
                                                                   r=1;
                                                                  }else{
                                                                   //error
                                                                  };
                                                                 };
                                                                }else{
                                                                 //error kann nicht assoziieren
                                                                };
                                                                return(r);
};
template<class T>char _speicherassoziationbasis<T>::suchen(_zeichenkette<char> value,_basis::_speicherbar*&found) {
                                                                _liste<_basis::_speicherbar > fl;
                                                               // _basis::_speicherbar*it;
                                                                //-----------------
                                                                datei()->holenspeicherbaruebername(value,fl);
                                                                if(fl.anfang()){
                                                                 found=fl.anfang();
                                                                 return(1);
                                                                };
                                                                return(0);
};
//******************************************************************************************************************************************************************************************************
//                                                              S T O R E A S S O C I A T I O N I N T E R F A C E 
//******************************************************************************************************************************************************************************************************
template<class T>class _speicherassoziationschnittstelle:public _basis::_speicherbar,public virtual _assoziation<T>{
        public:
                _speicherassoziationschnittstelle(_dateispeicherbar*);
                _speicherassoziationschnittstelle(_dateispeicherbar*,_basis::_speicherbar*);
                inline operator T*() const;
                inline T*        operator=(T*);
                virtual char laden(_dateispeicherbarknoten*);
                virtual char assoziieren();
                virtual void speichern();
};
template<class T> _speicherassoziationschnittstelle<T>::_speicherassoziationschnittstelle(_dateispeicherbar*f):_basis::_speicherbar(f){
                                                                typ(::gettypename<_speicherassoziationschnittstelle<T> >());
};
template<class T> _speicherassoziationschnittstelle<T>::_speicherassoziationschnittstelle(_dateispeicherbar*f,_basis::_speicherbar*s):_basis::_speicherbar(f,s){
                                                                typ(::gettypename<_speicherassoziationschnittstelle<T> >());
};
template<class T>_speicherassoziationschnittstelle<T>::operator T*() const{
                                                                return(this->holen());
};
template<class T> T* _speicherassoziationschnittstelle<T>::operator=(T*p){
                                                                setzen(p);
                                                                return(p);
};

template<class T>char _speicherassoziationschnittstelle<T>::laden(_dateispeicherbarknoten*f){
                                                                char r;
                                                                ladenbeginn(f);
                                                                ladenverschachtelung(f);
                                                                r=ladenassoziation();
                                                                ladenende();
                                                                return(r);
};
template<class T>void _speicherassoziationschnittstelle<T>::speichern(){
                                                                speichernbeginn();
                                                                if(this->holen()) saveassociationinterface<_speicherassoziationschnittstelle<T>,T>(this, this->holen());
                                                                speichernende();
};
template<class T>char _speicherassoziationschnittstelle<T>::assoziieren(){
                                                                T*anderes;
                                                                _speicherbardynamischvererbungsschnittstelle<T>*stdii;
                                                                _basis::_speicherbar*found;
                                                                _zeichenkette<char> value=assoziation();
                                                                char r;
                                                                _liste<_basis::_speicherbar > fl;
                                                                //---------
                                                                r=0;
                                                                if(value!=(char*)""){
                                                                 datei()->holenspeicherbaruebername(value,fl);
                                                                 if(fl.anfang()){
                                                                  found=fl.anfang();
                                                                  stdii=dynamic_cast<_speicherbardynamischvererbungsschnittstelle<T>*>(found);
                                                                  if(stdii){
                                                                   anderes=stdii->objekt();
                                                                   setzen(anderes);
                                                                   r=1;
                                                                  }else{
                                                                   //error
                                                                   r=0;
                                                                  };
                                                                 };
                                                                }else{
                                                                r=0;
                                                                 //error kann nicht assoziieren
                                                                };
                                                                return(r);
};
//******************************************************************************************************************************************************************************************************
//                                                              S T O R E A S S O C I A T I O N A R G U M E N T 
//******************************************************************************************************************************************************************************************************
template<class T>class _speicherassoziationargument:public _basis::_speicherbar,public virtual _assoziation<T>{
        public:
                _speicherassoziationargument(_dateispeicherbar*f);
                _speicherassoziationargument(_dateispeicherbar*f,_basis::_speicherbar*);
                inline operator T*() const;
                inline T*        operator=(T*);
                virtual char laden(_dateispeicherbarknoten*);
                virtual char assoziieren();
                virtual void speichern();
};
template<class T> _speicherassoziationargument<T>::_speicherassoziationargument(_dateispeicherbar*f):_basis::_speicherbar(f){
                                                                typ(::gettypename<_speicherassoziationargument<T> >());
};
template<class T> _speicherassoziationargument<T>::_speicherassoziationargument(_dateispeicherbar*f,_basis::_speicherbar*s):_basis::_speicherbar(f,s){
                                                                typ(::gettypename<_speicherassoziationargument<T> >());
};
template<class T>_speicherassoziationargument<T>::operator T*() const{
                                                                return(this->holen());
};
template<class T> T* _speicherassoziationargument<T>::operator=(T*p){
                                                                setzen(p);
                                                                return(p);
};
template<class T>char _speicherassoziationargument<T>::laden(_dateispeicherbarknoten*f){
                                                                char r;
                                                                ladenbeginn(f);
                                                                ladenverschachtelung(f);
                                                                r=ladenassoziation();
                                                                ladenende();
                                                                return(r);
};
template<class T>void _speicherassoziationargument<T>::speichern(){
                                                                speichernbeginn();
                                                                if(this->holen()) saveassociationargument<_speicherassoziationargument<T>,T>(datei(),this, this->holen());
                                                                speichernende();
};
template<class T>char _speicherassoziationargument<T>::assoziieren(){
                                                                T*anderes;
                                                                _speicherbardynamisch<T>*std;
                                                                _basis::_speicherbar*found;
                                                                _zeichenkette<char> value=assoziation();
                                                                char r;
                                                                _liste<_basis::_speicherbar > fl;
                                                                //---------
                                                                r=0;
                                                                if(value!=(char*)""){
                                                                 datei()->holenspeicherbaruebername(value,fl);
                                                                 if(fl.anfang()){
                                                                  found=fl.anfang();
                                                                  std=dynamic_cast<_speicherbardynamisch<T>*>(found);
                                                                  if(std){
                                                                   anderes=std->objekt();
                                                                   setzen(anderes);
                                                                   r=1;
                                                                  }else{
                                                                   r=0;
                                                                   //error
                                                                  };
                                                                 };
                                                                }else{
                                                                 r=0;
                                                                 //error kann nicht assoziieren
                                                                };
                                                                return(r);
};

//******************************************************************************************************************
//										D A T E I S P E I C H E R B A R B I N A E R
//******************************************************************************************************************
class _dateispeicherbarbinaer:public _datei,public _listebasis<_speicherbarbinaer>{
		public:
				_dateispeicherbarbinaer(_zeichenkette<char>);
				virtual ~_dateispeicherbarbinaer();

};
//******************************************************************************************************************
//										S P E I C H E R B A R B I N A E R
//******************************************************************************************************************
class _speicherbarbinaer:public _listenknotenbasis<_speicherbarbinaer>{
        public:
                _speicherbarbinaer();
                _speicherbarbinaer(_listebasis<_speicherbarbinaer>*liste);
                virtual ~_speicherbarbinaer();
				void einhaengenspeicherung(_listebasis<_speicherbarbinaer>*liste,const _zeichenkette<char>&n,unsigned int in);
				void einhaengenspeicherung(_listebasis<_speicherbarbinaer>*liste);
				void aushaengenspeicherung();
                _zeichenkette<char>&speichername();

				unsigned int ladenanzahl(_datei*d);
				unsigned int ladenanzahl();
				void loeschenanzahl();

                void ladenzeiger(_datei*d);
                void ladenbeginn();
				void speichernbeginn();
                bool zeigergeladen();
                template<class T> void speichernzeiger(_datei*d,T*o);
                void loeschenzeiger();
                template<class T> T*assoziierenzeiger(T*&o);

				virtual bool assoziieren();

        private:
                _listebasis<_speicherbarbinaer>*pliste;
	            _zeichenkette<char> pname;
	            _liste<_zeichenkette<char> > pzeigerliste;
	            _listenknoten<_zeichenkette<char> >*pzeigeriterator;
	            _liste<unsigned int> panzahlliste;
	            _listenknoten<unsigned int>*panzahliterator;
	            bool pzeigergeladen;
};        

template<class T> void _speicherbarbinaer::speichernzeiger(_datei*d,T*o){
				_zeichenkette<char> h;
				if(o==0){
				 h="null";
				 d->speichern(h);
				}else{
				 _speicherbarbinaer*sb=dynamic_cast<_speicherbarbinaer*>(o);
				 if(sb){
				  d->speichern<char>(sb->speichername());
				 }else{
				  h="nullerror";
                  d->speichern(h);
				 };
				};
};
template<class T> T* _speicherbarbinaer::assoziierenzeiger(T*&o){
                _zeichenkette<char>*t=0;
                o=0;
                if(pzeigeriterator){
			     t=pzeigeriterator->objekt();
				 pzeigeriterator=pzeigeriterator->naechstes();
				};
				if((*t)=="null") return(0);
				//suchen von savename t in den listen
				_speicherbarbinaer*sit;
				if(liste()->anfang(sit))do{
				 if(sit->pname==(*t)) {
				  o=dynamic_cast<T*>(sit);
				  return(o);
				 };
				}while(liste()->naechstes(sit));
				return(0);
};
#endif




//******************************************************************************************************************************************************************************************************
//                                                              G L O B A L E   F U N K T I O N S T E M P L A T E S 
//******************************************************************************************************************************************************************************************************
//extern char*autotypename;

template<class T> _zeichenkette<char> gettypename() {
    _zeichenkette<char> autotypename;
    char c[1024];
    T* objekt = 0;
    strcpy(c, typeid(objekt).name());
    autotypename.kopieren(c);
    return(autotypename);
};
template<class T> _zeichenkette<char> gettypename(T* objekt) {
    _zeichenkette<char> autotypename;
    char c[1024];
    strcpy(c, typeid(objekt).name());
    autotypename.kopieren(c);
    return(autotypename);
};
template<class T>char associateassociationbase(_dateispeicherbar* datei, _zeichenkette<char>* name, T*& pointer) {
    _basis::_speicherbar* found;
    _liste<_basis::_speicherbar > results;
    T* t;
    char e;
    //--------------------
    e = 1;
    if (name) {
        if (*name == "0") {
            //nullzeiger
            pointer = 0;
            return(1);
        }
        else {
            datei->holenspeicherbaruebername(*name, results);
            if (results.anfang()) {
                if (results.anzahl() != 1) {
                    //warnung : namens-mehrdeutigkeit in der datei
                    e = 2;
                };
                found = results.anfang();
                t = dynamic_cast<T*>(found);
                if (t) {//ist es ein _basis::_Storeable selbst ?
                    pointer = t;
                    //L->schreiben("Association auf ein basis::speicherbar war erfolgreich!!!");
                }
                else {
                    //error : keine übereinstimmung
                    pointer = 0;
                    e = 0;
                };
            }
            else {
                //error kein objekt mit name s in f vorhanden
                pointer = 0;
                e = 0;
            };
            return(e);
        };
    }
    else {
        return(0);
    };
};
template<class T>char associateassociationinterface(_dateispeicherbar* datei, _zeichenkette<char>* name, T*& pointer) {
    _basis::_speicherbar* found;
    _liste<_basis::_speicherbar > results;
    _speicherbardynamischvererbungsschnittstelle<T>* stdii;
    char e;
    //--------------------
    e = 1;
    if (name) {
        if (*name == "0") {
            //nullzeiger
            pointer = 0;
            return(1);
        }
        else {
            datei->holenspeicherbaruebername(*name, results);
            if (results.anfang()) {
                if (results.anzahl() != 1) {
                    //warnung : namens-mehrdeutigkeit in der datei
                    e = 2;
                };
                found = results.anfang();
                stdii = dynamic_cast<_speicherbardynamischvererbungsschnittstelle<T>*>(found);
                if (stdii) {//ist es ein inheritanceinterface ?
                    pointer = stdii->objekt();
                    //L->schreiben("Association auf ein schnittstelle war erfolgreich!!!");
                }
                else {
                    //error : keine übereinstimmung
                    pointer = 0;
                    e = 0;
                };
            }
            else {
                //error kein objekt mit name s in f vorhanden
                pointer = 0;
                e = 0;
            };
            return(e);
        };
    }
    else {
        return(0);
    };
};
template<class T>char associateassociationargument(_dateispeicherbar* datei, _zeichenkette<char>* name, T*& pointer) {
    _basis::_speicherbar* found;
    _liste<_basis::_speicherbar > results;
    _listenknoten<_basis::_speicherbar >* sit;
    _speicherbardynamisch<T>* stda;
    char e;
    //--------------------
    e = 1;
    if (name) {
        if (*name == "0") {
            //nullzeiger
            pointer = 0;
            return(1);
        }
        else {
            // L->schreiben("holeanf");
            datei->holenspeicherbaruebername(*name, results);
            //  L->schreiben("holend");
            if (results.anfang(sit)) {
                // L->schreiben("holl");
                if (results.anzahl() != 1) {
                    //L->schreiben("warnung : namens-mehrdeutigkeit in der datei");
                    e = 2;
                };
                found = sit->objekt();
                stda = dynamic_cast<_speicherbardynamisch<T>*>(found);
                if (stda) {//ist es ein argumentinterface ?
                    pointer = stda->objekt();
                    // L->schreiben("Association auf ein argument war erfolgreich!!!");
                }
                else {
                    //L->schreiben("error : keine übereinstimmung");
                    pointer = 0;
                    e = 0;
                };
            }
            else {
                //L->schreiben("error kein objekt mit name s in f vorhanden : ",*name);
                pointer = 0;
                e = 0;
            };
            return(e);
        };

    }
    else {
        return(0);
    };
};

template<class M, class T>char saveassociationbase(M* manager, T* pointer) {
    _zeichenkette<char> tn;
    //---------
    if (pointer) {
        pointer->holennamenqualifikation(tn);
        manager->speichernwertroh(tn);
        return(1);
    }
    else {
        //nullzeiger
        manager->speichernwertroh("0");
        return(1);
    };

};
template<class M, class T>char saveassociationinterface(M* manager, T* pointer) {
    _zeichenkette<char> tn;
    //---------
    if (pointer) {
        pointer->holennamenqualifikation(tn);
        manager->speichernwertroh(tn);
        return(1);
    }
    else {
        //nullzeiger
        manager->speichernwertroh("0");
        return(1);
    };
};

template<class M, class T>char saveassociationargument(_dateispeicherbar* datei, M/*_speicherbardynamisch<T>*/* manager, T* pointer) {
    _zeichenkette<char> tn;
    //---------
    if (pointer) {
        //  L->schreiben("saa0");
        if (pointer->_basis::_speicherbarargument<T>::speicherbar()) {
            pointer->_basis::_speicherbarargument<T>::speicherbar()->holennamenqualifikation(tn);
            manager->speichernwertroh(tn);
            return(1);
        }
        else {
            //schwerer fehler
            L->schreiben("FEHLER :template<class M,class T>char saveassociationargument(_dateispeicherbar*datei,M*manager,T*pointer) : das zu assozierende Objekt hat seinen Argumentzeifger nicht geladen.");
            manager->speichernwertroh("0");
            return(0);
        };
    }
    else {
        //nullzeiger
       // L->schreiben("saa1");
        manager->speichernwertroh("0");
        return(1);
    };
    /*_zeichenkette<char> tn;
    _liste<_basis::_speicherbar > results;
    _listenknoten<_basis::_speicherbar > * sit;
    _basis::_speicherbar*found;
    _speicherbardynamisch<T>*x;
    //-------------------------
    if(pointer){
     datei->holenspeicherbaruebermodus(2,results);
     found=0;
     if(results.anfang(sit))do{
      x=dynamic_cast<_speicherbardynamisch<T>*>(sit->objekt());
      if(x){
       if(x->objekt()==pointer){
        found=sit->objekt();
       };
      };
     }while((results.naechstes(sit))&&(found==0));
     if(found){
      found->holennamenqualifikation(tn);
      manager->speichernwertroh(tn);
      return(1);
     };
     //error
     return(0);
    }else{
     //nullzeiger
     manager->speichernwertroh("0");
     return(1);
    };
    return(0);*/
};