//******************************************************************************************************************************************************************************************************
//  Project     : grundplatte
//  Library     : _grundplatte.lib
//  Module      : _datei.cpp
//  Date        : 27.12.2002
//  Description : 
//******************************************************************************************************************************************************************************************************
#include <_struktur.hpp>
#include <_datei.hpp>
#include <stdlib.h>
bool dateiexistiert(_zeichenkette<char> f){
                                                                FILE*a;
                                                                a=fopen(f,"r");
                                                                if(a!=0){
                                                                 fclose(a);
                                                                 a=0;
                                                                 return(true);
                                                                };
                                                                return(false);
};
//char*autotypename=0;
//*********************************************************************************************************************************************************************************
//                                                                D A T A B O O L
//*********************************************************************************************************************************************************************************
_bool::_bool(const _bool&d){
                                                                daten=d.daten;
};
_bool::_bool(const bool d){
                                                                daten=d;
};
_bool::_bool(){
                                                                daten=false;
};
_bool::operator bool() const{
                                                                return(daten);
};
bool _bool::operator==(const bool t) const{
                                                                return(daten==t);

};
bool _bool::operator!=(const bool t) const{
                                                                return(daten!=t);
};
bool& _bool::operator=(const bool t){
                                                                daten=t;
                                                                return(daten);
};
bool& _bool::setzen(const bool t){
                                                                daten=t;
                                                                return(daten);
};
bool _bool::holen() const{
                                                                return(daten);
};
//*********************************************************************************************************************************************************************************
//                                                                D A T A C H A R
//*********************************************************************************************************************************************************************************
_char::_char(const char i){
                                                                setzen(i);
};
_char::_char(){
                                                                setzen(0);
};
char& _char::operator=(const char c){
                                                                return(setzen(c));
};
//*********************************************************************************************************************************************************************************
//                                                                D A T A S C H A R
//*********************************************************************************************************************************************************************************
_schar::_schar(const signed char i){
                                                                setzen(i);
};
_schar::_schar(){
                                                                setzen(0);
};
signed char& _schar::operator=(const signed char c){
                                                                return(setzen(c));
};
//*********************************************************************************************************************************************************************************
//                                                                D A T A S H O R T
//*********************************************************************************************************************************************************************************
_short::_short(const signed short int i){
                                                                setzen(i);
};
_short::_short(){
                                                                setzen(0);
};
signed short int& _short::operator=(const signed short int i){
                                                                return(setzen(i));
};
//*********************************************************************************************************************************************************************************
//                                                                D A T A U S H O R T
//*********************************************************************************************************************************************************************************
_ushort::_ushort(const unsigned short int i){
                                                                setzen(i);
};
_ushort::_ushort(){
                                                                setzen(0);
};
unsigned short int& _ushort::operator=(unsigned short int i){
                                                                return(setzen(i));
};
//*********************************************************************************************************************************************************************************
//                                                                D A T A I N T
//*********************************************************************************************************************************************************************************
_int::_int(const signed int i){
                                                                setzen(i);
};
_int::_int(){
                                                                setzen(0);
};
signed int& _int::operator=(const signed int i){
                                                                return(setzen(i));
};
//*********************************************************************************************************************************************************************************
//                                                                D A T A U I N T
//*********************************************************************************************************************************************************************************
_uint::_uint(const unsigned int i){
                                                                setzen(i);
};
_uint::_uint(){
                                                                setzen(0);
};
unsigned int& _uint::operator=(const unsigned int i){
                                                                return(setzen(i));
};
//*********************************************************************************************************************************************************************************
//                                                                D A T A L O N G
//*********************************************************************************************************************************************************************************
_long::_long(const signed long int i){
                                                                setzen(i);
};
_long::_long(){
                                                                setzen(0);
};
signed long int& _long::operator=(const signed long int i){
                                                                return(setzen(i));
};
//*********************************************************************************************************************************************************************************
//                                                                D A T A U L O N G
//*********************************************************************************************************************************************************************************
_ulong::_ulong(const unsigned long int i){
                                                                setzen(i);
};
_ulong::_ulong(){
                                                                setzen(0);
};
unsigned long int& _ulong::operator=(const unsigned long int i){
                                                                return(setzen(i));
};
//*********************************************************************************************************************************************************************************
//                                                                D A T A F L O A T
//*********************************************************************************************************************************************************************************
_float::_float(const float i){
                                                                setzen(i);
};
_float::_float(){
                                                                setzen(0);
};
float& _float::operator=(const float i){
                                                                return(setzen(i));

};
//*********************************************************************************************************************************************************************************
//                                                                D A T A D O U B L E
//*********************************************************************************************************************************************************************************
_double::_double(const double i){
                                                                setzen(i);
};
_double::_double(){
                                                                setzen(0);
};
double& _double::operator=(const double i){
                                                                return(setzen(i));
};
//*********************************************************************************************************************************************************************************
//                                                                D A T A L O N G D O U B L E
//*********************************************************************************************************************************************************************************
_longdouble::_longdouble(const long double i){
                                                                setzen(i);
};
_longdouble::_longdouble(){
                                                                setzen(0);
};
long double& _longdouble::operator=(const long double i){
                                                                return(setzen(i));
};


//******************************************************************************************************************************************************************************************************
//                                                              F I L E 
//******************************************************************************************************************************************************************************************************
_datei::_datei(_zeichenkette<char> f){
                                                                pfile=0;
                                                                pname=f;
                                                                pposition=0;
                                                                palwaysopen=false;
                                                                pbinaryopen=false;
                                                               
};
_datei::_datei(_zeichenkette<char> p,_zeichenkette<char> f){
                                                                _zeichenkette<char> bs=(char*)"\\";
                                                                pfile=0;
                                                                pname=p+bs+f;
                                                                pposition=0;
                                                                palwaysopen=false;
                                                                pbinaryopen=false;

};
_datei::_datei(_datei*n){
                                                                _zeichenkette<char> bs=(char*)"\\";
                                                                pfile=0;
                                                                pname="datei";
                                                                if(n){
                                                                 pname=n->pname;
                                                                 pposition=n->pposition;
                                                                 palwaysopen=n->palwaysopen;
                                                                 pbinaryopen=n->pbinaryopen;
                                                                };
};
_datei::~_datei(){
                                                                if (palwaysopen) schliessen();
};
FILE*_datei::dateihandle(){
                                                                return(pfile);
};
void _datei::kopieren(_datei*n){
                                                                if(n){
                                                                 pfile=0;
                                                                 pname=n->pname;
                                                                 pposition=n->pposition;
                                                                 palwaysopen=n->palwaysopen;
                                                                 pbinaryopen=n->pbinaryopen;
                                                                };
};
unsigned int _datei::groesse(){
                                                                if(pfile==0)return(0);
                                                                long  oldpos, newpos;
                                                                oldpos = ftell(pfile);
                                                                fseek(pfile, 0, SEEK_END);
                                                                newpos = ftell(pfile);
                                                                fseek(pfile, oldpos, SEEK_SET);
                                                                return((unsigned int)newpos);
};
bool _datei::erzeugen(){
                                                               // char*t=new char[pname.groesse()+16];
                                                                char*c=pname;
                                                                pbinaryopen=false;
                                                                palwaysopen=false;
                                                                pfile=fopen((char*)c,"wb");
                                                                pname.loeschencache();
                                                               // delete[] t;
                                                                if(pfile!=0){
                                                                 position(0);
                                                                 palwaysopen=true;
                                                                 pbinaryopen=true;
                                                                 return(true);
                                                                };
                                                                pfile=0;
                                                                return(false);
};
char _datei::oeffnen(){
                                                               // char*t=new char[pname.groesse()+16];
                                                                char*c=pname;
                                                                pbinaryopen=false;
                                                                palwaysopen=false;
                                                                pfile=fopen((char*)c,"a+b");
                                                                pname.loeschencache();
                                                               // delete[] t;
                                                                if(pfile!=0){
                                                                 position(0);
                                                                 palwaysopen=true;
                                                                 pbinaryopen=true;
                                                                 return(1);
                                                                };
                                                                pfile=0;
                                                                return(0);
};
char _datei::oeffnentext(){
                                                               // char*t=new char[pname.groesse()+16];
                                                                char*c=pname;
                                                                pfile=fopen((char*)c,"rt");
                                                                pbinaryopen=false;
                                                                pname.loeschencache();
                                                               // delete[] t;
                                                                if(pfile!=0){
                                                                 position(0);
                                                                 palwaysopen=true;
                                                                 return(1);
                                                                };
                                                                pfile=0;
                                                                return(0);
};
char _datei::oeffnennurlesen(){
                                                               // char*t=new char[pname.groesse()+16];
                                                                char*c=pname;
                                                                pfile=fopen((char*)c,"rb");
                                                                pname.loeschencache();
                                                                
                                                                
                                                               // delete[] t;
                                                                if(pfile!=0){
                                                                 position(0);
                                                                 palwaysopen=true;
                                                                 pbinaryopen=true;
                                                                 return(1);
                                                                };
                                                                pfile=0;
                                                                return(0);
};
void _datei::schliessen(){
                                                                if(pfile) fclose(pfile);
                                                                palwaysopen=false;
                                                                pbinaryopen=false;
                                                                pfile=0;
};
void _datei::loeschen(){
                                                                //char*t=new char[pname.groesse()+16];
                                                                char*c=pname;
                                                                if(palwaysopen){
                                                                 if(pfile){
                                                                  fclose(pfile);
                                                                  pfile=fopen((char*)c,"wb");
                                                                 }else{
                                                                  pfile=fopen((char*)c,"wb");
                                                                 };
                                                                }else{
                                                                 if(pfile){
                                                                  fclose(pfile);
                                                                  pfile=fopen((char*)c,"wb");
                                                                  fclose(pfile);
                                                                  pfile=0;
                                                                 }else{
                                                                  pfile=fopen((char*)c,"wb");
                                                                  fclose(pfile);
                                                                  pfile=0;
                                                                 };
                                                                };
                                                                pname.loeschencache();
                                                               // delete[] t;
};
void _datei::loeschenphysisch(){
                                                               if((remove(pname)) < 0) {
                                                                L->schreiben("_datei :: Fehler beim Löschen von Datei");
                                                               };
};
_zeichenkette<char> _datei::dateiname() const{
                                                                return(pname);
};
void _datei::dateiname(_zeichenkette<char> s){
                                                                pname=s;
};
void _datei::position(unsigned long int p){
                                                                pposition=p;
                                                                if(pfile){
                                                                 fseek(pfile,p*sizeof(char),SEEK_SET);
                                                                }else{
                                                                 //error:sinnlos
                                                                };
};
unsigned long int _datei::position(){
                                                                unsigned long int i=0;
                                                                if(pfile){
                                                                 pposition=i=ftell(pfile)/sizeof(char);
                                                                }else{
                                                                 i=pposition;
                                                                 //error:sinnlos
                                                                };
                                                                return(i);
};

bool _datei::laden(char*t,unsigned long int anzahl,unsigned long int&geladen){
                                                                bool r=false;
                                                                char*b=new char[anzahl];
                                                                //-----------
                                                                if(pfile){
                                                                 geladen=(unsigned long int)fread(b,sizeof(char),anzahl,pfile);
                                                                 memcpy(t,b,geladen*sizeof(char));
                                                                 if(geladen==anzahl) r=true; else r=false;
                                                                }else{
                                                                 //error
                                                                };
                                                                delete[] b;
                                                                return(r);
};

bool _datei::laden(std::vector<unsigned char> &buffer, unsigned int size){
                                                                if(pfile==0)return(false);
                                                                buffer.resize(size);
                                                                return(1==fread(&buffer[0], size,1,pfile) || 0 == size);
};
bool _datei::ladentext(_zeichenkette<char>&s){
                                                                bool r=false;
                                                                char*b=new char[8194];
                                                                //-----------
                                                                if(pfile){
                                                                 s=(char*)"";
                                                                 if(fgets(b,8191,pfile)) r=true;
                                                                 s=b;
                                                                 char eof[3]={13,10,0};
                                                                 s.ersetzen(_zeichenkette<char>(eof),"");
                                                                }else{
                                                                 //error
                                                                };
                                                                delete[] b;
                                                                return(r);
};
void _datei::speicherneol(const _zeichenkette<char>&s){
                                                                _zeichenkette<char> t=s;
                                                                char*c=pname;
                                                                char eol[3]={13,10,0};
                                                                //---------------------------
                                                                t+=eol;
                                                                if(palwaysopen){
                                                                 if(pfile==0) pfile=fopen((char*)c,"a+b");
                                                                 fwrite(t,t.speicherlast(),1,pfile);
                                                                }else{
                                                                 if(pfile==0) pfile=fopen((char*)c,"a+b");
                                                                 fwrite(t,t.speicherlast(),1,pfile);                                                                 
                                                                 fclose(pfile);
                                                                 pfile=0;
                                                                };
                                                                pname.loeschencache();
};
void _datei::speichern(char*t,unsigned long int anzahl){
                                                                char*c=pname;
                                                                //--------------------
                                                                if(palwaysopen){
                                                                 if(pfile==0) pfile=fopen((char*)c,"a+b");
                                                                 fwrite(t,sizeof(char),anzahl,pfile);
                                                                }else{
                                                                 if(pfile==0) pfile=fopen((char*)c,"a+b");
                                                                 fwrite(t,sizeof(char),anzahl,pfile);                                                                 
                                                                 fclose(pfile);
                                                                 pfile=0;
                                                                };
                                                                pname.loeschencache();
};
void _datei::speicherntext(const _zeichenkette<char>&s){
                                                                //_zeichenkette<char> t=s;
                                                                //char*c=pname;
                                                                
                                                                //---------------------------
                                                               // pname.holen(c,8192);        
                                                                if(pfile==0) {
                                                                 char*c=pname;
                                                                 pfile=fopen((char*)c,"a+b");
                                                                 pname.loeschencache();
                                                                };
                                                                if(palwaysopen){
                                                                 fwrite(s.daten(),s.speicherlast(),1,pfile);
                                                                }else{
                                                                 fwrite(s.daten(),s.speicherlast(),1,pfile);                                                                 
                                                                 fclose(pfile);
                                                                 pfile=0;
                                                                };
                                                                
};

//*********************************************************************************************************************************************************************************
//                                                                F I L E L O G  (Logdatei)
//*********************************************************************************************************************************************************************************
_logbuch*L=0;
_logbuch::_logbuch(_zeichenkette<char> fn):_datei(fn){
                                                               // L=this;
                                                                oeffnen();
                                                                loeschen();
                                                                schliessen();
                                                                paktiv=true;
};
_logbuch::~_logbuch(){
                                                               // L=0;
};
void _logbuch::aktiv(bool a){
                                                                paktiv=a;
};
bool _logbuch::aktiv()const{
                                                                return(paktiv);
};
void _logbuch::schreiben(_zeichenkette<char> s){
                                                                if(paktiv){
                                                                 oeffnen();
                                                                 speicherneol(s);
                                                                 schliessen();
                                                                };
};
void _logbuch::schreiben(_zeichenkette<char> s,_zeichenkette<char> t){
                                                                if(paktiv){
                                                                 _zeichenkette<char> h;
                                                                 //-----------
                                                                 oeffnen();
                                                                 h=s+t;
                                                                 speicherneol(h);
                                                                 schliessen();
                                                                };
};
void _logbuch::schreiben(_zeichenkette<char> s,_zeichenkette<unsigned short int> t){
                                                                if(paktiv){
 
                                                                 char*c=new char[t.groesse()+1];
                                                                 _zeichenkette<char> h;
                                                                 //-----------
                                                                 oeffnen();
                                                                 int i;
                                                                 for(i=0;i<t.groesse();i++) c[i]=(char)t.holen(i);
                                                                 c[i]=0;
                                                                 
                                                                 h=s + c;
                                                                 speicherneol(h);
                                                                 schliessen();
                                                                 delete c;
                                                                };
                                                                
};

void _logbuch::schreiben(_zeichenkette<char> s,int i){
                                                                if(paktiv){
                                                                 _zeichenkette<char> h;
                                                                 char c[128];
                                                                 //-------------
                                                                 oeffnen();
                                                                 _itoa(i,c,10);
                                                                 h=s;
                                                                 h+=c;
                                                                 //s+=h;
                                                                 speicherneol(h);
                                                                 schliessen();
                                                                };
};
void _logbuch::schreiben(_zeichenkette<char> s,float f){
                                                                if(paktiv){
                                                                 _zeichenkette<char> h;
                                                                 char c[128];
                                                                 //-------------
                                                                 oeffnen();
                                                                 _gcvt(f,100,c);
                                                                 h=s+c;
                                                                 //s+=h;
                                                                 speicherneol(h);
                                                                 schliessen();
                                                                };
};
void _logbuch::schreiben(_zeichenkette<char> s,double f){
                                                                if(paktiv){
                                                                 _zeichenkette<char> h;
                                                                 char c[128];
                                                                 //-------------
                                                                 oeffnen();
                                                                 //fprintf(pfile,"------------------------------------------ %f\n",f);
                                                                 _gcvt(f,100,c);
                                                                 h=s+c;
                                                                 //s+=h;
                                                                 speicherneol(h);
                                                                 schliessen();
                                                                };
};
void _logbuch::schreiben(_zeichenkette<char> s,_vektor<float> v){
                                                                if(paktiv){
                                                                 _zeichenkette<char> h;
                                                                 char c[128];
                                                                 unsigned int i;
                                                                 //-------------
                                                                 oeffnen();
                                                                 h=s;
                                                                 h+="[";
                                                                 for(i=0;i<v.holendimension();i++){
                                                                  _gcvt(v[i],10,c);
                                                                  h+=c;
                                                                  if(i<(v.holendimension()-1)){
                                                                   h+="; ";
                                                                  };
                                                                 };
                                                                 h+="]";
                                                                 speicherneol(h);
                                                                 schliessen();
                                                                };
};
void _logbuch::schreiben(_zeichenkette<char> s,_vektor2<float> v){
                                                                if(paktiv){
                                                                 _vektor<float> h;
                                                                 h.setzen(v[0],v[1]);
                                                                 schreiben(s,h);
                                                                };
};
void _logbuch::schreiben(_zeichenkette<char> s,_vektor3<float> v){
                                                                if(paktiv){
                                                                 _vektor<float> h;
                                                                 h.setzen(v[0],v[1],v[2]);
                                                                 schreiben(s,h);
                                                                };
};
void _logbuch::schreiben(_zeichenkette<char> s,_vektor4<float> v){
                                                                if(paktiv){
                                                                 _vektor<float> h;
                                                                 h.setzen(v[0],v[1],v[2],v[3]);
                                                                 schreiben(s,h);
                                                                };
};

void _logbuch::schreiben(_zeichenkette<char> s,_vektor<double> v){
                                                                if(paktiv){
                                                                 _zeichenkette<char> h;
                                                                 char c[128];
                                                                 unsigned int i;
                                                                 //-------------
                                                                 oeffnen();
                                                                 h=s;
                                                                 h+="[";
                                                                 for(i=0;i<v.holendimension();i++){
                                                                  _gcvt(v[i],10,c);
                                                                  h+=c;
                                                                  if(i<(v.holendimension()-1)){
                                                                   h+="; ";
                                                                  };
                                                                 };
                                                                 h+="]";
                                                                 speicherneol(h);
                                                                 schliessen();
                                                                };
};
void _logbuch::schreiben(_zeichenkette<char> s,_vektor2<double> v){
                                                                if(paktiv){
                                                                 _vektor<double> h;
                                                                 h.setzen(v[0],v[1]);
                                                                 schreiben(s,h);
                                                                };
};
void _logbuch::schreiben(_zeichenkette<char> s,_vektor3<double> v){
                                                                if(paktiv){
                                                                 _vektor<double> h;
                                                                 h.setzen(v[0],v[1],v[2]);
                                                                 schreiben(s,h);
                                                                };
};
void _logbuch::schreiben(_zeichenkette<char> s,_vektor4<double> v){
                                                                if(paktiv){
                                                                 _vektor<double> h;
                                                                 h.setzen(v[0],v[1],v[2],v[3]);
                                                                 schreiben(s,h);
                                                                };
};




void _logbuch::l(_zeichenkette<char> z){
																schreiben(z);
};
void _logbuch::l(_zeichenkette<char> z,_zeichenkette<char> x){
																schreiben(z,x);
};
void _logbuch::l(_zeichenkette<char> z,_zeichenkette<unsigned short int> x){
																schreiben(z,x);
};
void _logbuch::l(_zeichenkette<char> z,int x){
																schreiben(z,x);
};
void _logbuch::l(_zeichenkette<char> z,float x){
																schreiben(z,x);
};
void _logbuch::l(_zeichenkette<char> z,double x){
																schreiben(z,x);
};
void _logbuch::l(_zeichenkette<char> z,_vektor<float> x){
																schreiben(z,x);
};
void _logbuch::l(_zeichenkette<char> z,_vektor2<float> x){
																schreiben(z,x);
};
void _logbuch::l(_zeichenkette<char> z,_vektor3<float> x){
																schreiben(z,x);
};
void _logbuch::l(_zeichenkette<char> z,_vektor4<float> x){
																schreiben(z,x);
};
void _logbuch::l(_zeichenkette<char> z,_vektor<double> x){
																schreiben(z,x);
};
void _logbuch::l(_zeichenkette<char> z,_vektor2<double> x){
																schreiben(z,x);
};
void _logbuch::l(_zeichenkette<char> z,_vektor3<double> x){
																schreiben(z,x);
};
void _logbuch::l(_zeichenkette<char> z,_vektor4<double> x){
																schreiben(z,x);
};
















void _logbuch::fehler(_zeichenkette<char> s){
                                                                _zeichenkette<char> h;
                                                                //-----------
                                                                oeffnen();
                                                                h="ERROR : ";
                                                                h+=s;
                                                                speicherneol(h);
                                                                schliessen();
};
void _logbuch::fehler(_zeichenkette<char> s,_zeichenkette<char> t){
                                                                _zeichenkette<char> h;
                                                                //-----------
                                                                oeffnen();
                                                                h="ERROR : ";
                                                                h+=s+"  : "+t;
                                                                speicherneol(h);
                                                                schliessen();
};
void _logbuch::fehler(_zeichenkette<char> s,int i){
                                                                _zeichenkette<char> h;
                                                                char c[128];
                                                                //-------------
                                                                oeffnen();
                                                                _itoa(i,c,10);
                                                                h="ERROR : ";
                                                                h+=s;
                                                                h+=c;
                                                                //s+=h;
                                                                speicherneol(h);
                                                                schliessen();
};
void _logbuch::fehler(_zeichenkette<char> s,double d){
                                                                _zeichenkette<char> h;
                                                                char c[256];
                                                                //-------------
                                                                oeffnen();
                                                                _gcvt(d,10,c);
                                                                h="ERROR : ";
                                                                h+=s+c;
                                                                //s+=h;
                                                                speicherneol(h);
                                                                schliessen();
};
void _logbuch::fehler(_zeichenkette<char> s,_vektor<double> vd){
                                                                /*_zeichenkette<char> h;
                                                                char c[128];
                                                                //-------------
                                                                oeffnen();
                                                                _itoa(i,c,10);
                                                                h="ERROR : ";
                                                                h+=s+" : ";
                                                                h+=vd;
                                                                //s+=h;
                                                                speicherneol(h);
                                                                schliessen();*/
};
void _logbuch::fehler(_zeichenkette<char> s,_vektor2<double> vd){
                                                                _vektor<double> v;
                                                                v.setzen(vd[0],vd[1]);
                                                                fehler(s,v);
};                                                               
void _logbuch::fehler(_zeichenkette<char> s,_vektor3<double> vd){
                                                                _vektor<double> v;
                                                                v.setzen(vd[0],vd[1],vd[2]);
                                                                fehler(s,v);
};                                                               
void _logbuch::fehler(_zeichenkette<char> s,_vektor4<double> vd){
                                                                _vektor<double> v;
                                                                v.setzen(vd[0],vd[1],vd[2],vd[3]);
                                                                fehler(s,v);
};                                                               

//******************************************************************************************************************************************************************************************************
//                                                              F I L E S T O R E A B L E 
//******************************************************************************************************************************************************************************************************
_dateispeicherbar::_dateispeicherbar(_zeichenkette<char> c):_datei(c),name(c),leertaste(0){
                                                                lnodes=new _listebasis<_dateispeicherbarknoten >();
};
_dateispeicherbar::~_dateispeicherbar(){
                                                                delete lnodes;
                                                                //loeschen();
};
/*
 char _dateispeicherbar::oeffnen(const char*c){
                                                                datei=fopen(name,c);
                                                                name.loeschencache();
                                                                if(datei!=0){
                                                                 return(1);
                                                                };
                                                                return(0);
};
*/
/*
 void _dateispeicherbar::setpos(unsigned long p){
                                                                fseek(datei,p*sizeof(char),SEEK_SET);
};
 unsigned long int _dateispeicherbar::getpos(){
                                                                unsigned long int i;
                                                                i=ftell(datei)/sizeof(char);//fgetpos(datei,&pos);
                                                                return(i);
};
*/
/* void _dateispeicherbar::schliessen(){
                                                                fclose(datei);
};
*/
void _dateispeicherbar::inkleerraum(){
                                                                leertaste++;
};
void _dateispeicherbar::dekleerraum(){
                                                                leertaste--;
};
void _dateispeicherbar::schreiben(const char*c){
                                                                _zeichenkette<char> h=c;
                                                                //fwrite(c,h.groesse(),1,datei);
                                                                speicherntext(h);
};
void _dateispeicherbar::schreiben(const _zeichenkette<char>&s){
                                                                //fwrite(s,s.groesse(),1,datei);
                                                                speicherntext(s);
};
void _dateispeicherbar::schreibenreturn(){
                                                                //char eol[3]={13,10,0};
                                                                //schreiben(eol);
                                                                _zeichenkette<char> h;
                                                                speicherneol(h);
};
void _dateispeicherbar::schreibenleerraum(){
                                                                _zeichenkette<char> h=(char*)" ";
                                                                for(int i=0;i<leertaste;i++) speicherntext(h);//schreiben(" ");
};
//-----------------------------------
int _dateispeicherbar::lesen(char&r){
                                                                unsigned long readed;
                                                                laden(&r,1,readed);
                                                                return(readed);
                                                               // return(fread(&r,1,1,datei));
};
char _dateispeicherbar::lesenzeile(_zeichenkette<char>&s,unsigned long int & oldposition){
                                                                //char*c=new char[8192];
                                                                char r;
                                                                
                                                                //char lf[2]={10,0};
                                                                //char lr[2]={13,0};
                                                                //-----------
                                                                oldposition=position();
                                                                if(ladentext(s)) r=1; else r=0;
                                                               // r=1;
                                                               // fgets(c,8192,datei);
                                                               // if(feof(datei)){
                                                               //  r=0;
                                                               // };
                                                               // s=c;
                                                               // s.ersetzen(lf,"");
                                                               // s.ersetzen(lr,"");

                                                               // delete[] c;
                                                                return(r);
};
_listebasis<_dateispeicherbarknoten >*_dateispeicherbar::nodes() const{
                                                                return(lnodes);
};
void _dateispeicherbar::zerlegen(const _zeichenkette<char>&name,_liste<_zeichenkette<char> >*lz)const{
                                                                unsigned int i=0;
                                                                char c[1024];
                                                                unsigned int cc=0;
                                                                lz->loeschen();
                                                                do{
                                                                 cc=0;
                                                                 while((name[i]!=':')&&(name[i]!=0)) {
                                                                  c[cc++]=name[i++];
                                                                 };
                                                                 c[cc]=0;
                                                                 lz->einhaengen(new _zeichenkette<char>(c));
                                                                 while(name[i]==':') i++;
                                                                }while(name[i]!=0);
                                                                
                                                                
                                                                
};
char _dateispeicherbar::holenuebertyp(const _zeichenkette<char>&s,_liste<_dateispeicherbarknoten >&l) const{
                                                                _liste<_zeichenkette<char> > lz;
                                                                _listenknoten<_zeichenkette<char> >*lit;
                                                                char r=0;
                                                                _dateispeicherbarknoten *it;
                                                                //---------
                                                                zerlegen(s,&lz);
                                                                l.aushaengen();
                                                                if(lz.anfang(lit)){
                                                                 if(lnodes->anfang(it))do{
                                                                  r|=it->holenuebertyp(s,l,&lz,lit);
                                                                 }while(lnodes->naechstes(it));
                                                                };
                                                                
                                                                /*
                                                                l.aushaengen();
                                                                if(lnodes->anfang(it))do{
                                                                 r|=it->holenuebertyp(s,l);
                                                                }while(lnodes->naechstes(it));
                                                                */
                                                                return(r);
};
char _dateispeicherbar::holenuebername(const _zeichenkette<char>&s,_liste<_dateispeicherbarknoten >&l) const{
                                                                _liste<_zeichenkette<char> > lz;
                                                                _listenknoten<_zeichenkette<char> >*lit;
                                                                char r=0;
                                                                _dateispeicherbarknoten*it;
                                                                //---------
                                                                zerlegen(s,&lz);
                                                                l.aushaengen();
                                                                if(lz.anfang(lit)){
                                                                 if(lnodes->anfang(it))do{
                                                                  r|=it->holenuebername(s,l,&lz,lit);
                                                                 }while(lnodes->naechstes(it));
                                                                };
                                                                
                                                                /*
                                                                if(lnodes->anfang(it))do{
                                                                 r|=it->holenuebername(s,l);
                                                                }while(lnodes->naechstes(it));
                                                                */
                                                                return(r);
};
char _dateispeicherbar::holenspeicherbaruebermodus(char m,_liste<_basis::_speicherbar >&l){
                                                                char r=0;
                                                                _basis::_speicherbar*eit;
                                                                //---------
                                                                l.aushaengen();
                                                                if(anfang(eit))do{
                                                                 if(eit->aktiv()) r|=eit->holenuebermodus(m,l);
                                                                }while(naechstes(eit));
                                                                return(r);
};
char _dateispeicherbar::holenspeicherbaruebertyp(const _zeichenkette<char>&s,_liste<_basis::_speicherbar >&l){
                                                                char r=0;
                                                                _basis::_speicherbar*eit;
                                                                //---------
                                                                l.aushaengen();
                                                                if(anfang(eit))do{
                                                                 if(eit->aktiv()) r|=eit->holenuebertyp(s,l);
                                                                }while(naechstes(eit));
                                                                return(r);
};
char _dateispeicherbar::holenspeicherbaruebername(const _zeichenkette<char>&s,_liste<_basis::_speicherbar >&l){
                                                                char r=0;
                                                                _basis::_speicherbar*eit;
                                                                _liste<_zeichenkette<char> > lz;
                                                                _listenknoten<_zeichenkette<char> >*lit;
                                                                //---------
                                                                zerlegen(s,&lz);
                                                                l.aushaengen();
                                                                if(lz.anfang(lit)){
                                                                 if(anfang(eit))do{
                                                                  if(eit->aktiv()) r|=eit->holenuebername(s,l,&lz,lit);
                                                                 }while(naechstes(eit));
                                                                };
                                                                return(r);
};
char _dateispeicherbar::assoziieren(){
                                                                char r;
                                                                //-------
                                                                r=1;
                                                                _basis::_speicherbar*it;
                                                                if(anfang(it))do{
                                                                 if(it->aktiv()) if(it->assoziieren()==0) r=0;
                                                                }while(naechstes(it));
                                                                return(r);

};
//******************************************************************************************************************************************************************************************************
//                                                              F I L E S T O R E A B L E T E X T 
//******************************************************************************************************************************************************************************************************
_dateispeicherbartext::_dateispeicherbartext(_zeichenkette<char> c):_dateispeicherbar(c){
                                                                laden();
};
char _dateispeicherbartext::laden(){
                                                                _zeichenkette<char> linie;
                                                                unsigned long int oldpos;
                                                                unsigned int i;
                                                                _liste<_dateispeicherbarknoten > begins;
                                                                _listenknoten<_dateispeicherbarknoten >*itr;
                                                                _dateispeicherbarknoten*last;
                                                                _zeichenkette<char> name;
                                                                _zeichenkette<char> typ;
                                                                _zeichenkette<char> format;
                                                                //-----------------
                                                                nodes()->loeschen();
                                                                
                                                               // if(oeffnen("rb")){
                                                                if(oeffnen()){
                                                                 position(0);
                                                                 //suche nach blöcken
                                                                 last=0;
                                                                 //setpos(0);
                                                                 while(lesenzeile(linie,oldpos)){
                                                                  i=0;
                                                                  while(linie.suchen(2,i,(char*)"{",(char*)"}")){
                                                                   if(linie[i]=='{'){ //   printf("{");
                                                                   //noch ist last die verschachteln...
                                                                  //  printf("oldpos=%i\n",oldpos);
                                                                 
                                                                    if(last==0) last=new _dateispeicherbarknoten(nodes(),oldpos+i); else last=new _dateispeicherbarknoten(last,oldpos+i);
                                                                    begins.einhaengen(last);
                                                                    begins.anfang(itr);
                                                                    begins.vorheriges(itr);
                                                                  //  printf("begins-vorheriges=%i",begins.getobject()->begin());
                                                                   };
                                                                   if(linie[i]=='}'){
                                                                   // printf("}");
                                                                    if(last){
                                                                     last->end(oldpos+i);
                                                                     while((last->end()!=0)&&(begins.vorheriges(itr))) {
                                                                      last=itr->objekt();//begins.iterator();
                                                                     };
                                                                     last=itr->objekt();//begins.iterator();
                                                                     if(last->end()!=0) {last=0;/*printf("last=0!");*/};
                                                                    }else{
                                                                     //printf("ERROR\n");
                                                                     //error } ohne vorher {
                                                                    };
                                                                   };
                                                                   i++;
                                                                  };
                                                                 };
                                                                 if(begins.anfang(itr))do{
                                                                  ladenidentifikation(itr->objekt());//begins.iterator());
                                                                 }while(begins.naechstes(itr));
                                                                 //printf("Anzahl der filenodes gesamt : %i\n",nodes()->anzahl());
                                                                 schliessen();
                                                                 return(1);
                                                                };
                                                                return(0);
};
void _dateispeicherbartext::ladenidentifikation(_dateispeicherbarknoten*f){
                                                                if(f->liste()->erstes()==f){
                                                                 if(f->liste()==nodes()){
                                                                  //suche von dateianfang an
                                                                  ladenidentifikation(0,f->begin(),f,0);
                                                                 }else{
                                                                  //suche ab verwalter->begin
                                                                  _dateispeicherbarknoten*v=f->dateiknoten();
                                                                  if(v){
                                                                   ladenidentifikation(v->begin()+1,f->begin(),f,0);
                                                                  }else{
                                                                   //error : kein manager vorhanden
                                                                  };
                                                                 };
                                                                }else{
                                                                 //suche ab vorherigerknoten->end
                                                                 _dateispeicherbarknoten*p=f->vorherigerknoten();
                                                                 ladenidentifikation(p->end()+1,f->begin(),f,1);
                                                                };
};
void _dateispeicherbartext::ladenidentifikation(unsigned long int start,unsigned long int end,_dateispeicherbarknoten*f,char notfirst){
                                                                _zeichenkette<char> linie;
                                                                _zeichenkette<char> typ;
                                                                _zeichenkette<char> name;
                                                                _zeichenkette<char> format;
                                                                char loop;
                                                                unsigned long int oldpos;
                                                                unsigned long int knoten;
                                                                char nodeset;
                                                                unsigned int i;
                                                                unsigned int j;
                                                                char h[8192];
                                                                char hset;
                                                                _liste<_dateispeicherbarkommentar > fc;
                                                                _listenknoten<_dateispeicherbarkommentar >*it;
                                                                bool firstline;
                                                                //----------------
                                                                nodeset=0;
                                                                knoten=0;
                                                                position(start);
                                                                loop=1;
                                                                firstline=true;
                                                                do{
                                                                 if(lesenzeile(linie,oldpos)==0) loop=0;
                                                                 if((oldpos+linie.groesse())>=end) loop=0;
                                                                 i=0;
                                                                 while((i<linie.groesse())&&(i+oldpos<end)){
                                                                  loop=lesenkommentare(false,linie,i,oldpos,end,fc,firstline,notfirst&&firstline);
                                                                  j=0;
                                                                  hset=0;
                                                                  while((oldpos+i<end)&&(linie[i]==' ')) i++;
                                                                  while((oldpos+i<end)&&(linie[i]!=' ')&&(i<linie.groesse())) {
                                                                   if(nodeset==0){
                                                                    nodeset=1;
                                                                    knoten=oldpos+i;
                                                                   };
                                                                   if(linie[i]=='/'){
                                                                    loop=lesenkommentare(false,linie,i,oldpos,end,fc,firstline,notfirst&&firstline);
                                                                   }else{
                                                                    h[j++]=linie[i++];
                                                                   };
                                                                   hset=1;
                                                                  };
                                                                  if(hset){
                                                                   h[j]=0;
                                                                   //printf("h=%s    ",h);
                                                                   if(typ.groesse()==0) typ=h; else
                                                                   if(name.groesse()==0) name=h; else
                                                                   if(format.groesse()==0) format=h;
                                                                   //if(typ==(char*)"") typ=h; else
                                                                   //if(name==(char*)"") name=h; else
                                                                   //if(format==(char*)"") format=h;
                                                                  };
                                                                 };
                                                                 firstline=0;
                                                                }while(loop);
                                                                if(nodeset==0) {/*printf("NODESET==0");*/knoten=end;};
                                                                f->knoten(knoten);
                                                                f->typ(typ);
                                                                f->name(name);
                                                             //    L->schreiben("Fazrozrz eitrf hrölsfren<§ ",typ);
                                                                f->format(format);
                                                                //hintenangestellt - commentare einlesen
                                                                lesenkommentarehinten(f->end(),fc);
                                                                //commentare übertragen
                                                                if(fc.anfang(it))do{
                                                                 f->kommentar(it->objekt()->kommentar(),it->objekt()->hintenangestellt());
                                                                }while(fc.naechstes(it));
                                                                fc.loeschen();
};
char _dateispeicherbartext::lesenkommentare(bool bs,_zeichenkette<char>&linie,unsigned int&i,unsigned long int&oldpos,unsigned long int end,_liste<_dateispeicherbarkommentar >&fc,bool&firstline,bool isother){
                                                                int j;
                                                                char*t;
                                                                char r;
                                                                char loop;
                                                                //------
                                                                r=1;
                                                                if(isother){
                                                                 if(lesenzeile(linie,oldpos)==0) r=0;
                                                                 firstline=false;
                                                                 return(r);
                                                                };
                                                                while((oldpos+i<end)&&(linie[i]==' ')) i++;
                                                                //printf(">%c",linie[i]);
                                                                if(linie[i]=='/'){
                                                                 //printf("'/' gefunden\n");
                                                                 if(linie[i+1]=='/'){
                                                                  t=new char[8192];
                                                                  i+=2;
                                                                  j=0;
                                                                  while((i<linie.groesse())&&(linie[i]!='{')&&(linie[i]!='}')&& (i+oldpos<end)){
                                                                   t[j++]=linie[i++];
                                                                  };
                                                                  t[j]=0;
                                                                  if (t[0]!=0) fc.einhaengen(new _dateispeicherbarkommentar(t,bs));
                                                                  delete[] t;
                                                                 }else
                                                                 if(linie[i+1]=='*'){
                                                                  //printf("/ * * / - commentar gefunden\n");
                                                                  t=new char[8192];
                                                                  i+=2;
                                                                  j=0;
                                                                  loop=1;
                                                                  do{
                                                                   if(i<linie.groesse()){
                                                                    if(i+oldpos<end){
                                                                     if((linie[i]!='*')&&(linie[i+1]!='/')){
                                                                      if((linie[i]!='{')&&(linie[i]!='}')){
                                                                       t[j++]=linie[i++];
                                                                      }else loop=0;
                                                                     }else loop=0;
                                                                    }else loop=0;
                                                                   }else{
                                                                    if(lesenzeile(linie,oldpos)==0) r=0;
                                                                    firstline=false;
                                                                    if((oldpos+linie.groesse())>=end) {
                                                                     r=0;
                                                                    };
                                                                    i=0;
                                                                   };
                                                                  }while(loop);
                                                                  t[j]=0;
                                                                  if(t[0]!=0) {
                                                                   fc.einhaengen(new _dateispeicherbarkommentar(t,bs));
                                                                   //printf("filecomment=%s\n",t);
                                                                   };
                                                                  delete[] t;
                                                                 };
                                                                };
                                                                return(r);

};
void _dateispeicherbartext::lesenkommentarehinten(unsigned long int start,_liste<_dateispeicherbarkommentar >&fc){
                                                                unsigned long int oldpos;
                                                                unsigned long int end=(unsigned long int)0xffffffffffffffff;
                                                                _zeichenkette<char> linie;
                                                                unsigned int i;
                                                                bool firstline=false;
                                                                //-----------------------
                                                                position(start+1);
                                                                lesenzeile(linie,oldpos);
                                                                i=0;
                                                                while((i<linie.groesse())&&(linie[i]!=' ')) i++;
                                                                oldpos=0;
                                                                lesenkommentare(true,linie,i,oldpos,end,fc,firstline,false);
};
void _dateispeicherbartext::speichern(){
                                                                _basis::_speicherbar*it;
                                                                //oeffnen("wb");
                                                                oeffnen();
                                                                _datei::loeschen();
                                                                if(anfang(it))do{
                                                                 if(it->aktiv()) {
                                                                  it->speichern();
                                                                 };
                                                                }while(naechstes(it));
                                                                schliessen();
};


//******************************************************************************************************************************************************************************************************
//                                                              F I L E S T O R E A B L E N O D E 
//******************************************************************************************************************************************************************************************************
_dateispeicherbarknoten::_dateispeicherbarknoten(_listebasis<_dateispeicherbarknoten >*l,unsigned long be):_listelistenknotenbasis<_dateispeicherbarknoten >(l){
                                                                lnode=0;
                                                                lbegin=be;
                                                                lend=0;
                                                                pfilenode=0;
                                                                pbereitsgeladen=false;
};
_dateispeicherbarknoten::_dateispeicherbarknoten(_dateispeicherbarknoten*f,unsigned long be):_listelistenknotenbasis<_dateispeicherbarknoten >(f){
                                                                lnode=0;
                                                                lbegin=be;
                                                                lend=0;
                                                                pfilenode=f;
                                                                pbereitsgeladen=false;
};
_dateispeicherbarknoten::~_dateispeicherbarknoten(){
};
void _dateispeicherbarknoten::end(unsigned long int i){
                                                                lend=i;
};
void _dateispeicherbarknoten::knoten(unsigned long int i){
                                                                lnode=i;
};
unsigned long int _dateispeicherbarknoten::end() const{
                                                                return(lend);
};
unsigned long int _dateispeicherbarknoten::knoten() const{
                                                                return(lnode);
};
unsigned long int _dateispeicherbarknoten::begin() const{
                                                                return(lbegin);
};
_dateispeicherbarknoten* _dateispeicherbarknoten::dateiknoten() const{
                                                                return(pfilenode);
};

char _dateispeicherbarknoten::holenuebertyp(const _zeichenkette<char>&t,_liste<_dateispeicherbarknoten >&l){
                                                                char r=0;
                                                                _dateispeicherbarknoten*nit;
                                                                //---------
                                                                _zeichenkette<char> qt;
                                                                holentypqualifikation(qt);
                                                                if(t==qt){
                                                                 l.einhaengen(this);
                                                                 r|=1;
                                                                };
                                                                if(anfang(nit))do{
                                                                 r|=nit->holenuebertyp(t,l);
                                                                }while(naechstes(nit));
                                                                return(r);
                                                                
};
 char _dateispeicherbarknoten::holenuebertyp(const _zeichenkette<char>&t,_liste<_dateispeicherbarknoten >&l,_liste<_zeichenkette<char> >*lz,_listenknoten<_zeichenkette<char> >*lit){
                                                                char r=0;
                                                                //---------
                                                                if(*lit->objekt()==typ()){
                                                                 if(lz->erstes()==lit->naechstes()){
                                                                  l.einhaengen(this);
                                                                  return(1);
                                                                 }else{
                                                                  _dateispeicherbarknoten*it;
                                                                  ::_listenknoten<_zeichenkette<char> >*nit=lit->naechstes();
                                                                  if(anfang(it))do{
                                                                   r|=it->holenuebertyp(t,l,lz,nit);
                                                                  }while(naechstes(it));
                                                                 };
                                                                };
                                                                return(r);
 };

char _dateispeicherbarknoten::holenuebername(const _zeichenkette<char>&n,_liste<_dateispeicherbarknoten >&l){
                                                                char r=0;
                                                                _dateispeicherbarknoten*nit;
                                                                //---------
                                                                _zeichenkette<char> qn;
                                                                holentypqualifikation(qn);
                                                                if(n==qn){
                                                                 l.einhaengen(this);
                                                                 r|=1;
                                                                };
                                                                if(anfang(nit))do{
                                                                 r|=nit->holenuebertyp(n,l);
                                                                }while(naechstes(nit));
                                                                return(r);
};
char _dateispeicherbarknoten::holenuebername(const _zeichenkette<char>&t,_liste<_dateispeicherbarknoten >&l,_liste<_zeichenkette<char> >*lz,_listenknoten<_zeichenkette<char> >*lit){
                                                                char r=0;
                                                                //---------
                                                                if(*lit->objekt()==name()){
                                                                 if(lz->erstes()==lit->naechstes()){
                                                                  l.einhaengen(this);
                                                                  return(1);
                                                                 }else{
                                                                  _dateispeicherbarknoten*it;
                                                                  ::_listenknoten<_zeichenkette<char> >*nit=lit->naechstes();
                                                                  if(anfang(it))do{
                                                                   r|=it->holenuebername(t,l,lz,nit);
                                                                  }while(naechstes(it));
                                                                 };
                                                                };
                                                                return(r);
};

void _dateispeicherbarknoten::holennamenqualifikation(_zeichenkette<char>&s){
                                                                _dateispeicherbarknoten*sit;
                                                                _zeichenkette<char> nb=(char*)"::";
                                                                //-----------
                                                                s=name();
                                                                sit=this;
                                                                while(sit->pfilenode){
                                                                 sit=sit->pfilenode;
                                                                 s.anhaengenfront(sit->name()+nb);
                                                                };
};
void _dateispeicherbarknoten::holentypqualifikation(_zeichenkette<char>&s){
                                                                _dateispeicherbarknoten*sit;
                                                                _zeichenkette<char> nb=(char*)"::";
                                                                //--------------
                                                                s=typ();
                                                                sit=this;
                                                                while(sit->pfilenode){
                                                                 sit=sit->pfilenode;
                                                                 s.anhaengenfront(sit->typ()+nb);
                                                                };
};
void _dateispeicherbarknoten::bereitsgeladen(const bool b){
                                                                pbereitsgeladen=b;
};
bool _dateispeicherbarknoten::bereitsgeladen()const{
                                                                return(pbereitsgeladen);
};
//******************************************************************************************************************************************************************************************************
//                                                              F I L E S T O R E A B L E C O M M E N T 
//******************************************************************************************************************************************************************************************************
_dateispeicherbarkommentar::_dateispeicherbarkommentar(const _zeichenkette<char> s){

                                                                bs=0;
                                                                com=s;
                                                                filter();
};
_dateispeicherbarkommentar::_dateispeicherbarkommentar(const _zeichenkette<char> s,bool b){
                                                                bs=b;
                                                                com=s;
                                                                filter();
};
void _dateispeicherbarkommentar::filter(){
                                                                com.ersetzen((char*)"}",(char*)"");
                                                                com.ersetzen((char*)"{",(char*)"");
                                                                com.ersetzen((char*)"//",(char*)"");
                                                                com.ersetzen((char*)"/*",(char*)"");
                                                                com.ersetzen((char*)"*/",(char*)"");
};
_zeichenkette<char> _dateispeicherbarkommentar::kommentar() const{
                                                                return(com);
};
bool _dateispeicherbarkommentar::hintenangestellt() const{
                                                                return(bs);
};
//******************************************************************************************************************************************************************************************************
//                                                              F I L E S T O R E A B L E I D E N T I F I C A T I O N 
//******************************************************************************************************************************************************************************************************
_dateispeicherbaridentifikation::~_dateispeicherbaridentifikation(){
                                                                coms.loeschen();
};
void _dateispeicherbaridentifikation::kopieren(_dateispeicherbaridentifikation*f){
                                                                _listenknoten<_dateispeicherbarkommentar >*it;
                                                                //------------------------
                                                                name(f->name());
                                                                typ(f->typ());
                                                                format(f->format());
                                                                coms.loeschen();
                                                                if(f->comments()->anfang(it))do{
                                                                 coms.einhaengen(new _dateispeicherbarkommentar(it->objekt()->kommentar(),it->objekt()->hintenangestellt()));
                                                                }while(f->comments()->naechstes(it));

};
void _dateispeicherbaridentifikation::typ(const _zeichenkette<char> s){
                                                                stype=s;
                                                                filter(stype);
};
void _dateispeicherbaridentifikation::name(const _zeichenkette<char> s){
                                                                sname=s;
                                                                filter(sname);
};
void _dateispeicherbaridentifikation::format(const _zeichenkette<char> s){
                                                                sformat=s;
                                                                filter(sformat);
};
void _dateispeicherbaridentifikation::filter(_zeichenkette<char>&s){
                                                                //char*c;
                                                                //c=s;
                                                                //L->schreiben("typ=",(char*)c);
                                                                s.ersetzen((char*)"}",(char*)"");
                                                                s.ersetzen((char*)"{",(char*)"");
                                                                s.ersetzen((char*)"//",(char*)"");
                                                                s.ersetzen((char*)"/*",(char*)"");
                                                                s.ersetzen((char*)"*/",(char*)"");
};
const _zeichenkette<char>&_dateispeicherbaridentifikation::typ() const{
                                                                return(stype);
};
const _zeichenkette<char>&_dateispeicherbaridentifikation::name() const{
                                                                return(sname);
};
const _zeichenkette<char>&_dateispeicherbaridentifikation::format() const{
                                                                return(sformat);
};
_liste<_dateispeicherbarkommentar >*_dateispeicherbaridentifikation::comments(){
                                                                return(&coms);
};
void _dateispeicherbaridentifikation::kommentar(const _zeichenkette<char> s){
                                                                coms.einhaengen(new _dateispeicherbarkommentar(s,0));
};
void _dateispeicherbaridentifikation::kommentar(const _zeichenkette<char> s,char c){
                                                                coms.einhaengen(new _dateispeicherbarkommentar(s,c));
};

//******************************************************************************************************************************************************************************************************
//                                                              B A S E : : S T O R E A B L E 
//******************************************************************************************************************************************************************************************************
namespace _basis{
 _speicherbar::_speicherbar(_dateispeicherbar*f):_listelistenknotenbasis<_speicherbar >(f){
                                                                 ffile=f;
                                                                 pstoreable=0;
                                                                 bactive=true;
                                                                 cmode=0;
                                                                 bblockmodus=false;
 };
 _speicherbar::_speicherbar(_dateispeicherbar*f,_speicherbar*s):_listelistenknotenbasis<_speicherbar >(s){
                                                                 ffile=f;
                                                                 pstoreable=s;
                                                                 bactive=true;
                                                                 cmode=0;
                                                                 bblockmodus=false;
 };
 _speicherbar::~_speicherbar(){
                                                                values.loeschen();
                                                                valueassociations.loeschen();
                                                                // printf("speicherbar-destruktor\n");
 };
 _dateispeicherbar*_speicherbar::datei(){
                                                                return(ffile);
 };
 _speicherbar*_speicherbar::speicherbar() const{
                                                                return(pstoreable);
 };
 //------------------------------------------------------------- SCHNITTSTELLE -----------------------------------------------------------------------------------------------------
 char _speicherbar::laden(_dateispeicherbarknoten*f){
                                                                char r;
                                                                //--------------
                                                                ladenbeginn(f);
                                                                r=ladenverschachtelung(f);
                                                                ladenende();
                                                                return(r);
 };
 void _speicherbar::speichern(){
                                                                speichernbeginnblock();
                                                                speichernverschachtelung();
                                                                speichernendeblock();
                                                                 
 };
 char _speicherbar::assoziieren(){
                                                                 return(assoziierenverschachtelung());
 };
 char _speicherbar::holenuebermodus(char m,::_liste<_speicherbar >&l){
                                                                char r=0;
                                                                //---------
                                                                if(m==modus()){
                                                                 l.einhaengen(this);
                                                                 r|=1;
                                                                };
                                                                _speicherbar*it;
                                                                if(anfang(it))do{
                                                                 if(it->aktiv()) r|=it->holenuebermodus(m,l);
                                                                }while(naechstes(it));
                                                                return(r);
 };
 char _speicherbar::holenuebertyp(const _zeichenkette<char>&t,::_liste<_speicherbar >&l){
                                                                char r=0;
                                                                //---------
                                                                _zeichenkette<char> qt;
                                                                holentypqualifikation(qt);
                                                                if(t==qt){
                                                                 l.einhaengen(this);
                                                                 r|=1;
                                                                };
                                                                _speicherbar*it;
                                                                if(anfang(it))do{
                                                                 if(it->aktiv()) r|=it->holenuebertyp(t,l);
                                                                }while(naechstes(it));
                                                                return(r);
 };
 char _speicherbar::holenuebername(const _zeichenkette<char>&n,::_liste<_speicherbar >&l,::_liste<_zeichenkette<char> >*lz,::_listenknoten<_zeichenkette<char> >*lit){
                                                                char r=0;
                                                                //---------
                                                                if(*lit->objekt()==name()){
                                                                 if(lz->erstes()==lit->naechstes()) {
                                                                  l.einhaengen(this);
                                                                  return(1);
                                                                 }else{
                                                                  _speicherbar*it;
                                                                  ::_listenknoten<_zeichenkette<char> >*nit=lit->naechstes();
                                                                  if(anfang(it))do{
                                                                   if(it->aktiv()) r|=it->holenuebername(n,l,lz,nit);
                                                                  }while(naechstes(it));
                                                                 };
                                                                };
                                                                return(r);
 };
 char _speicherbar::holenuebername(const _zeichenkette<char>&n,::_liste<_speicherbar >&l){
 
                                                                char r=0;
                                                                //---------
                                                                _zeichenkette<char> qn;
                                                                holennamenqualifikation(qn);
                                                                if(n==qn){
                                                                 l.einhaengen(this);
                                                                 r|=1;
                                                                };
                                                                _speicherbar*it;
                                                                if(anfang(it))do{
                                                                 if(it->aktiv()) r|=it->holenuebername(n,l);
                                                                }while(naechstes(it));
                                                                return(r);
 };
 void _speicherbar::holennamenqualifikation(_zeichenkette<char>&s){
                                                                _speicherbar*sit;
                                                                //------------
                                                                s=name();
                                                                sit=this;
                                                                while(sit->pstoreable){
                                                                 sit=sit->pstoreable;
                                                                 s.anhaengenfront(sit->name()+(char*)"::");
                                                                };
 };
 void _speicherbar::holentypqualifikation(_zeichenkette<char>&s){
                                                                _speicherbar*sit;
                                                                //--------------
                                                                s=typ();
                                                                sit=this;
                                                                while(sit->pstoreable){
                                                                 sit=sit->pstoreable;
                                                                 s.anhaengenfront(sit->typ()+(char*)"::");
                                                                };
 };
 //------------------------------------------------------------- lade-,speicher- und assoziierungsfunktionen, die nicht redefiniert werden ----------------------------------------
 void _speicherbar::speichernbeginnblock(){
                                                                speichernbeginn();
                                                                ffile->schreibenreturn();
                                                                ffile->inkleerraum();
                                                                bblockmodus=true;
                                                                
 };
 void _speicherbar::speichernbeginn(){
                                                                _zeichenkette<char> h=(char*)"//";
                                                                ::_listenknoten<_dateispeicherbarkommentar >*it;
                                                                //-----------
                                                                if(comments()->anfang(it))do{
                                                                 if(it->objekt()->hintenangestellt()==0){
                                                                  ffile->schreibenleerraum();
                                                                  ffile->schreiben(h+it->objekt()->kommentar());
                                                                  ffile->schreibenreturn();
                                                                 };
                                                                }while(comments()->naechstes(it));
                                                                ffile->schreibenleerraum();
                                                                ffile->schreiben(typ());
                                                                //if(format()!=(char*)""){
                                                                if(format().groesse()!=0){
                                                                 ffile->schreiben((char*)" ");
                                                                 ffile->schreiben(format());
                                                                };
                                                                //if(name()!=(char*)""){
                                                                if(name().groesse()!=0){
                                                                 ffile->schreiben((char*)" ");
                                                                 ffile->schreiben(name());
                                                                };
                                                                ffile->schreiben((char*)"{");
                                                                // L->schreiben("fstext : basis::speicherbar");
                                                                values.loeschen();
                                                                // firstvalue(true);
 };
 void _speicherbar::speichernverschachtelung(){
                                                                 _speicherbar*it;
                                                                 if(anfang(it))do{
                                                                  it->speichern();
                                                                 }while(naechstes(it));
 };
 void _speicherbar::speichernwert(bool b){
                                                                 if(b) speichernwertroh("true"); else speichernwertroh("false");
 };
 void _speicherbar::speichernwert(int i){
                                                                 char s[128];
                                                                 //-------------
                                                                 _itoa(i,s,10);
                                                                 speichernwertroh(s);
 };
 void _speicherbar::speichernwert(unsigned int i){
                                                                 char s[128];
                                                                 //-------------
                                                                 _itoa(i,s,10);
                                                                 speichernwertroh(s);
 };
 void _speicherbar::speichernwert(float f){
                                                                char s[128];
                                                                //-------------
                                                                _gcvt(f,100,s);
                                                                speichernwertroh(s);
 };
 void _speicherbar::speichernwert(double d){
                                                                char s[128];
                                                                //-------------
                                                                _gcvt(d,100,s);
                                                                speichernwertroh(s);
 };
 void _speicherbar::speichernwert(_vektor<float> d){
                                                                char s[128];
                                                                unsigned int i;
                                                                _zeichenkette<char> ss;
                                                                //-------------
                                                                for(i=0;i<d.holendimension();i++){
                                                                 _gcvt(d[i],100,s);
                                                                 ss+=s;
                                                                 if(i!=d.holendimension()-1) ss+=";"; 
                                                                };
                                                                speichernwertroh(ss);
                                                                
 };
 void _speicherbar::speichernwert(_vektor2<float> d){
                                                                _vektor<float> dd;
                                                                dd.setzen(d[0],d[1]);
                                                                speichernwert(dd);
 };
 void _speicherbar::speichernwert(_vektor3<float> d){
                                                                _vektor<float> dd;
                                                                dd.setzen(d[0],d[1],d[2]);
                                                                speichernwert(dd);
 };
 void _speicherbar::speichernwert(_vektor4<float> d){
                                                                _vektor<float> dd;
                                                                dd.setzen(d[0],d[1],d[2],d[3]);
                                                                speichernwert(dd);
 };
 void _speicherbar::speichernwert(_vektor<double> d){
                                                                char s[128];
                                                                unsigned int i;
                                                                _zeichenkette<char> ss;
                                                                //-------------
                                                                for(i=0;i<d.holendimension();i++){
                                                                 _gcvt(d[i],100,s);
                                                                 ss+=s;
                                                                 if(i!=d.holendimension()-1) ss+=";"; 
                                                                };
                                                                speichernwertroh(ss);
                                                                
 };
 void _speicherbar::speichernwert(_vektor2<double> d){
                                                                _vektor<double> dd;
                                                                dd.setzen(d[0],d[1]);
                                                                speichernwert(dd);
 };
 void _speicherbar::speichernwert(_vektor3<double> d){
                                                                _vektor<double> dd;
                                                                dd.setzen(d[0],d[1],d[2]);
                                                                speichernwert(dd);
 };
 void _speicherbar::speichernwert(_vektor4<double> d){
                                                                _vektor<double> dd;
                                                                dd.setzen(d[0],d[1],d[2],d[3]);
                                                                speichernwert(dd);
 };
 void _speicherbar::speichernwert(_zeichenkette<char>&s){
                                                                _zeichenkette<char> h=s;
                                                                h.anhaengen((char*)"\"");
                                                                h.anhaengenfront((char*)"\"");
                                                                speichernwertroh(h);
 };
 void _speicherbar::speichernwertroh(_zeichenkette<char> s){
                                                                _zeichenkette<char>*h;
                                                                //---------
                                                                h=new _zeichenkette<char>(s);
                                                                values.einhaengen(h);
 };
 void _speicherbar::speichernendeblock(){
                                                                int i;
                                                                int c;
                                                                ::_listenknoten<_zeichenkette<char> >*it;
                                                                //erst alle werte aus der values liste schreiben
                                                                if(values.anfang(it)){
                                                                 i=0;
                                                                 c=values.anzahl();
                                                                 do{
                                                                  i++;
                                                                  if(bblockmodus){
                                                                   datei()->schreibenleerraum();
                                                                   datei()->schreiben(it->objekt());
                                                                   if(i!=c) datei()->schreiben((char*)",");
                                                                   datei()->schreibenreturn();
                                                                  };
                                                                 }while(values.naechstes(it));
                                                                };
                                                                values.loeschen();
                                                                ffile->dekleerraum();
                                                                ffile->schreibenleerraum();
                                                                ffile->schreiben((char*)"}");
                                                                speichernhintenangestelltekommentare();
 };
 void _speicherbar::speichernende(){
                                                                 int i;
                                                                 int c;
                                                                 ::_listenknoten<_zeichenkette<char> >*it;
                                                                //-----------
                                                                //erst alle werte aus der values liste schreiben
                                                                if(values.anfang(it)){
                                                                 i=0;
                                                                 c=values.anzahl();
                                                                 do{
                                                                  i++;
                                                                  datei()->schreiben(it->objekt());
                                                                  if(i!=c) datei()->schreiben((char*)",");
                                                                 }while(values.naechstes(it));
                                                                };
                                                                values.loeschen();
                                                                //jetzt block abschliessen, kommentare schreiben
                                                                ffile->schreiben((char*)"}");
                                                                speichernhintenangestelltekommentare();
                                                                //ffile->blockmodus(false);
 };
 void _speicherbar::speichernhintenangestelltekommentare(){
                                                                 ::_listenknoten<_dateispeicherbarkommentar >*it;
                                                                 _zeichenkette<char> co=(char*)"/*";
                                                                 _zeichenkette<char> cc=(char*)"*/";
                                                                 _zeichenkette<char> h=co;
                                                                 //---------------------------
                                                                 if(comments()->anfang(it))do{
                                                                  if(it->objekt()->hintenangestellt()){
                                                                   if(h==co){
                                                                    h+=it->objekt()->kommentar();
                                                                   }else{
                                                                    h+=(char*)"; ";
                                                                    h+=it->objekt()->kommentar();
                                                                   };
                                                                  };
                                                                 }while(comments()->naechstes(it));
                                                                 if(h!=co){
                                                                  h+=cc;
                                                                  ffile->schreibenleerraum();
                                                                  ffile->schreiben(h);
                                                                  //ffile->schreibenreturn();
                                                                 };
                                                                 ffile->schreibenreturn();
                                                                 bblockmodus=false;
 };
 char _speicherbar::ladenbeginn(_dateispeicherbarknoten*f){
                                                                 kopieren(f);
                                                                 f->bereitsgeladen(true);
                                                                 //erst alle values einlesen von der Datei
                                                                 valueassociations.loeschen();
                                                                 ladenwerte(f);
                                                                 values.anfang(sit);
                                                                 return(1);
 };
 char _speicherbar::ladenwerte(_dateispeicherbarknoten*f){
                                                                 //funktion ließt alle werte zwischen den
                                                                 //verschachtelten Blöcken und überträgt alle werte als strings
                                                                 //in die werte-liste values
                                                                 _dateispeicherbarknoten*fit;
                                                                 unsigned long int begin;
                                                                 char r;
                                                                 //------------------------
                                                                 r=1;
                                                                 values.loeschen();
                                                                 if(f->anfang(fit)){
                                                                  begin=f->begin()+1;
                                                                  do{
                                                                   if(ladenwerte(begin,fit->knoten())==0) r=0;
                                                                   begin=fit->end()+1;
                                                                  }while(f->naechstes(fit));
                                                                  if(ladenwerte(begin,f->end())==0) r=0;
                                                                 }else{
                                                                  if(ladenwerte(f->begin()+1,f->end())==0) r=0;
                                                                 };
                                                                 return(r);
 };
 char _speicherbar::ladenwerte(unsigned long int begin,unsigned long int end){
                                                                 char r;
                                                                 unsigned int vit;
                                                                 unsigned int lit;
                                                                 unsigned int forend;
                                                                 char loop;
                                                                 _zeichenkette<char> linie;
                                                                 char*s=new char[8192];
                                                                 unsigned int stringon;
                                                                 _zeichenkette<char>*h;
                                                                 unsigned long int oldpos;
                                                                 unsigned int c;
                                                                 char re;
                                                                 //--------
                                                                 //printf("BEGIN=%i  END=%i\n",begin,end);
                                                                 re=0;
                                                                 if(begin<end){
                                                                  ffile->oeffnen();//ffile->oeffnen("rb");
                                                                  ffile->position(begin);//ffile->setpos(begin);
                                                                  vit=0;
                                                                  loop=1;
                                                                  stringon=0;
                                                                  oldpos=begin;
                                                                  do{
                                                                   c=ffile->lesenzeile(linie,oldpos);
                                                                   //L->schreiben("linie! = ",linie);
                                                                   if(c==0) loop=0;
                                                                   if((oldpos+linie.groesse())>=end) {
                                                                    forend=end-oldpos;
                                                                    loop=0;
                                                                   }else{
                                                                    forend=linie.groesse();
                                                                   };
                                                                   //printf("FOREND=%i\n",forend);
                                                                   //if(oldpos+forend>end
                                                                   //if(forend>linie.groesse()) forend=linie.groesse();
                                                                   for(lit=0;lit<forend;lit++){
                                                                    r=linie[lit];
                                                                    //printf("%c",r);
                                                                    if(stringon==0){
                                                                     //es wird momentan kein string-wert gelesen);
                                                                     if((r!='}')&&(r!=',')&&(r!=10)&&(r!=13)&&(r!=0)&&(r!=' ')){
                                                                      s[vit++]=r;
                                                                     }else{
                                                                      s[vit]=0;
                                                                      vit=0;
                                                                      if(s[0]!=0){
                                                                       h=new _zeichenkette<char>(s);
                                                                       values.einhaengen(h); //L->schreiben("eingefügt1 = ",s);
                                                                       re=1;
                                                                      };
                                                                     };
                                                                    }else{
                                                                     //es wird momentan ein string-wert eingelesen
                                                                     if(r!='"'){
                                                                      s[vit++]=r;
                                                                     }else{
                                                                      s[vit]=0;
                                                                      vit=0;
                                                                      h=new _zeichenkette<char>(s);
                                                                      h->ersetzen((char*)"\"",(char*)"");
                                                                      values.einhaengen(h);  // printf("eingefügt=%s\n",s);
                                                                      re=1;
                                                                     };
                                                                    };
                                                                    if(r=='"') stringon=1-stringon;
                                                                   };
                                                                  }while(loop);
                                                                  s[vit]=0;
                                                                  if(stringon==0){
                                                                   if(s[0]!=0){
                                                                    h=new _zeichenkette<char>(s);
                                                                    values.einhaengen(h); //L->schreiben("eingefügt1 = ",s);
                                                                    re=1;
                                                                   };
                                                                  }else{
                                                                   h=new _zeichenkette<char>(s);
                                                                   h->ersetzen((char*)"\"",(char*)"");
                                                                   values.einhaengen(h); //  printf("eingefügt=%s\n",s);
                                                                   re=1;
                                                                  };
                                                                  ffile->schliessen();
                                                                  delete[] s;
                                                                 };
                                                                 //printf("EXIT\n");
                                                                 return(re);
 };
 char _speicherbar::ladenverschachtelung(_dateispeicherbarknoten*f){
                                                                 _dateispeicherbarknoten*fit;
                                                                 _speicherbar*sit;
                                                                 char r;
                                                                 //--------------
                                                                 r=0;
                                                                 f->anfang(fit);
                                                                 if(anfang(sit))do{
                                                                  r|=sit->laden(fit);
                                                                  f->naechstes(fit);
                                                                 }while(naechstes(sit));
                                                                 return(r);
 };
 char _speicherbar::ladenwerte(::_liste<_zeichenkette<char> >&sl){
                                                                 ::_listenknoten<_zeichenkette<char> >*vit;
                                                                 _zeichenkette<char>*h;
                                                                 //-------------
                                                                 sl.loeschen();
                                                                 if(values.anfang(vit))do{
                                                                  h=new _zeichenkette<char>(vit->objekt());
                                                                  sl.einhaengen(h);
                                                                 }while(values.naechstes(vit));
                                                                 return(1);
 };
 char _speicherbar::ladenassoziation(){
                                                                 _zeichenkette<char>*h=new _zeichenkette<char>(sit->objekt());
                                                                // L->schreiben("loadasssociation : h=",*h);
                                                                 valueassociations.einhaengen(h);
                                                                 //char t[1024];
                                                                 //printf("ASSOCIATION ==== %s\n",h->holen(t));
                                                                 valueassociations.anfang(ait);
                                                                 return(values.naechstes(sit));
 };
 char _speicherbar::ladenwert(bool&i){
 
                                                                 _zeichenkette<char> h=*sit->objekt();
                                                                 if(h=="true") i=true; else i=false;
                                                                 return(values.naechstes(sit));
 };
 char _speicherbar::ladenwert(int&i){
 
                                                                 char s[128];
                                                                 _zeichenkette<char>*h;
                                                                 h=sit->objekt();//values.iterator();
                                                                 h->holen(s,128);
                                                                 i=atoi((char*)s);
                                                                 return(values.naechstes(sit));
 };
 char _speicherbar::ladenwert(unsigned int&i){
 
                                                                 char s[128];
                                                                 _zeichenkette<char>*h;
                                                                 h=sit->objekt();//values.iterator();
                                                                 h->holen(s,128);
                                                                 i=atoi((char*)s);
                                                                 return(values.naechstes(sit));
 };
 char _speicherbar::ladenwert(float&f){
                                                                 char s[128];
                                                                 _zeichenkette<char>*h;
                                                                 h=sit->objekt();//values.iterator();
                                                                 h->holen(s,128);
                                                                 f=(float)atof((char*)s);
                                                                 return(values.naechstes(sit));
 };
 char _speicherbar::ladenwert(double&d){
                                                                 char s[128];
                                                                 _zeichenkette<char>*h;
                                                                 h=sit->objekt();//values.iterator();
                                                                 h->holen(s,128);
                                                                 d=atof((char*)s);
                                                                 return(values.naechstes(sit));
 };
 char _speicherbar::ladenwert(_vektor<float>&d){
                                                                 char s[128];
                                                                 _zeichenkette<char> h;
                                                                 unsigned int si;
                                                                 unsigned int hi;
                                                                 unsigned int vi;
                                                                 //----------------
                                                                 h=*sit->objekt();
                                                                 hi=0;
                                                                 vi=0;
                                                                 do{
                                                                  si=0;
                                                                  while((h[hi]!=';')&&(h[hi]!=0)&&(vi<d.holendimension())) s[si++]=h[hi++];
                                                                  s[si]=0;
                                                                  if(h[hi]!=0) hi++;
                                                                  d.setzenkomponente(vi++,(float)atof(s));
                                                                 }while(h[hi]!=0);
                                                                 return(values.naechstes(sit));
 };
 char _speicherbar::ladenwert(_vektor2<float>&d){
                                                                _vektor<float> v(d[0],d[1]);
                                                                char c=ladenwert(v);
                                                                d.setzen(v[0],v[1]);
                                                                return(c);
 };
 char _speicherbar::ladenwert(_vektor3<float>&d){
                                                                _vektor<float> v(d[0],d[1],d[2]);
                                                                char c=ladenwert(v);
                                                                d.setzen(v[0],v[1],v[2]);
                                                                return(c);
 };
 char _speicherbar::ladenwert(_vektor4<float>&d){
                                                                _vektor<float> v(d[0],d[1],d[2],d[3]);
                                                                char c=ladenwert(v);
                                                                d.setzen(v[0],v[1],v[2],v[3]);
                                                                return(c);
 };
 
 char _speicherbar::ladenwert(_vektor<double>&d){
                                                                 char s[128];
                                                                 _zeichenkette<char> h;
                                                                 unsigned int si;
                                                                 unsigned int hi;
                                                                 unsigned int vi;
                                                                 //----------------
                                                                 h=*sit->objekt();
                                                                 hi=0;
                                                                 vi=0;
                                                                 do{
                                                                  si=0;
                                                                  while((h[hi]!=';')&&(h[hi]!=0)&&(vi<d.holendimension())) s[si++]=h[hi++];
                                                                  s[si]=0;
                                                                  if(h[hi]!=0) hi++;
                                                                  d.setzenkomponente(vi++,atof(s));
                                                                 }while(h[hi]!=0);
                                                                 return(values.naechstes(sit));
 };
 char _speicherbar::ladenwert(_vektor2<double>&d){
                                                                _vektor<double> v(d[0],d[1]);
                                                                char c=ladenwert(v);
                                                                d.setzen(v[0],v[1]);
                                                                return(c);
 };
 char _speicherbar::ladenwert(_vektor3<double>&d){
                                                                _vektor<double> v(d[0],d[1],d[2]);
                                                                char c=ladenwert(v);
                                                                d.setzen(v[0],v[1],v[2]);
                                                                return(c);
 };
 char _speicherbar::ladenwert(_vektor4<double>&d){
                                                                _vektor<double> v(d[0],d[1],d[2],d[3]);
                                                                char c=ladenwert(v);
                                                                d.setzen(v[0],v[1],v[2],v[3]);
                                                                return(c);
 };
 char _speicherbar::ladenwert(_zeichenkette<char>&s){
                                                                 s=*sit->objekt();//values.iterator();
                                                                 return(values.naechstes(sit));
 };
 void _speicherbar::ladenende(){
                                                                 values.loeschen();
                                                                 valueassociations.anfang(ait);
 
 };
 char _speicherbar::assoziierenverschachtelung(){
                                                                 _speicherbar*it;
                                                                 char r;
                                                                 //------------
                                                                 r=1;
                                                                 if(anfang(it))do{
                                                                  if(it->assoziieren()==0) r=0;
                                                                 }while(naechstes(it));
                                                                 return(r);
 };
 _zeichenkette<char>*_speicherbar::assoziation(){
                                                                 if(valueassociations.anzahl()>0){
                                                                  _zeichenkette<char>*h=ait->objekt();//valueassociations.iterator();
                                                                  valueassociations.naechstes(ait);
                                                                  return(h);
                                                                 }else{
                                                                  L->schreiben("error : _zeichenkette<char>*_basis::_speicherbar::assoziation() : valueassociation.anzahl()==0");
                                                                  return(0);
                                                                 };
 
 };
 //-------------------------------------------------------------        STATUSFUNKTIONEN --------------------------------------------------------------------------------------------------
 char _speicherbar::basis() const{
                                                                 if(cmode==0) return(1); else return(0);
 };
 char _speicherbar::schnittstelle() const{
                                                                 if(cmode==1) return(1); else return(0);
 };
 char _speicherbar::argument() const{
                                                                 if(cmode==2) return(1); else return(0);
 };
 char _speicherbar::modus() const{
                                                                 return(cmode);
 };
 bool _speicherbar::aktiv() const{
                                                                 return(bactive);
 };
 void _speicherbar::aktivitaet(bool m){
                                                                 bactive=m;
 };
 bool _speicherbar::blockmodus() const{
                                                                 return(bblockmodus);
 };
 void _speicherbar::modusbasis(){
                                                                 cmode=0;
 };
 void _speicherbar::modusschnittstelle(){
                                                                 cmode=1;
 };
 void _speicherbar::modusargument(){
                                                                 cmode=2;
 };
};


//******************************************************************************************************************************************************************************************************
//                                                              S T O R E I N T 
//******************************************************************************************************************************************************************************************************
_speicherint::_speicherint(_dateispeicherbar*f):_basis::_speicherbar(f){
                                                                setzen(0);
                                                                typ(::gettypename<_speicherint >());
};
_speicherint::_speicherint(_dateispeicherbar*f,_basis::_speicherbar*s):_basis::_speicherbar(f,s){
                                                                setzen(0);
                                                                typ(::gettypename<_speicherint >());
};
_speicherint::_speicherint(_dateispeicherbar*s,int i):_basis::_speicherbar(s){
                                                                setzen(i);
                                                                typ(::gettypename<_speicherint >());
};
_speicherint::~_speicherint(){
                                                                //printf("storeint des\n");
};
int& _speicherint::operator=(const int i){
                                                                return(setzen(i));
};
char _speicherint::laden(_dateispeicherbarknoten*f){
                                                                int i;
                                                                //--------
                                                                i=0;
                                                                ladenbeginn(f);
                                                                ladenwert(i);
                                                                setzen(i);
                                                                ladenende();
                                                                return(1);
};
void _speicherint::speichern(){
                                                                speichernbeginn();
                                                                speichernwert(holen());
                                                                speichernende();
};
//******************************************************************************************************************************************************************************************************
//                                                              S T O R E F L O A T 
//******************************************************************************************************************************************************************************************************
_speicherfloat::_speicherfloat(_dateispeicherbar*f):_basis::_speicherbar(f){
                                                                setzen(0);
                                                                typ(::gettypename<_speicherfloat>());
};
_speicherfloat::_speicherfloat(_dateispeicherbar*f,_basis::_speicherbar*s):_basis::_speicherbar(f,s){
                                                                setzen(0);
                                                                typ(::gettypename<_speicherfloat>());
};
float& _speicherfloat::operator=(const float i){
                                                                return(setzen(i));
};
char _speicherfloat::laden(_dateispeicherbarknoten*f){
                                                                float v;
                                                                //--------
                                                               // v=0;
                                                                ladenbeginn(f);
                                                                ladenwert(v);
                                                                setzen(v);
                                                                ladenende();
                                                                return(1);
};
void _speicherfloat::speichern(){
                                                                speichernbeginn();
                                                                speichernwert(holen());
                                                                speichernende();
};
//******************************************************************************************************************
//										D A T E I S P E I C H E R B A R B I N A E R
//******************************************************************************************************************
_dateispeicherbarbinaer::_dateispeicherbarbinaer(_zeichenkette<char> fn):_datei(fn){
};
_dateispeicherbarbinaer::~_dateispeicherbarbinaer(){
																while(erstes()) erstes()->aushaengen();
};
//******************************************************************************************************************
//										S P E I C H E R B A R B I N A E R
//******************************************************************************************************************
_speicherbarbinaer::_speicherbarbinaer():_listenknotenbasis<_speicherbarbinaer>(0){
																pzeigergeladen=false;
																pname="";
																pliste=0;
};
_speicherbarbinaer::_speicherbarbinaer(_listebasis<_speicherbarbinaer>*liste):_listenknotenbasis<_speicherbarbinaer>(liste){
																pzeigergeladen=false;
																pname="";
																pliste=liste;
};
_speicherbarbinaer::~_speicherbarbinaer(){
																loeschenzeiger();
																loeschenanzahl();
};
void _speicherbarbinaer::einhaengenspeicherung(_listebasis<_speicherbarbinaer>*liste,const _zeichenkette<char>&n,unsigned int in){
																pliste=liste;
																if(pliste){
																 _listenknotenbasis<_speicherbarbinaer>::einhaengen(pliste);
																 pname=n+in;
																}else{
																 _listenknotenbasis<_speicherbarbinaer>::aushaengen();
																};
};
void _speicherbarbinaer::einhaengenspeicherung(_listebasis<_speicherbarbinaer>*liste){
																pliste=liste;
																if(pliste){
																 _listenknotenbasis<_speicherbarbinaer>::einhaengen(pliste);
																}else{
																 _listenknotenbasis<_speicherbarbinaer>::aushaengen();
																};
};
void _speicherbarbinaer::aushaengenspeicherung(){
																pliste=0;
																_listenknotenbasis<_speicherbarbinaer>::aushaengen();
																pname="";
};
void _speicherbarbinaer::ladenzeiger(_datei*d){
																_zeichenkette<char>*h=new _zeichenkette<char>();
																d->laden(*h);
																pzeigerliste.einhaengen(h);
																pzeigerliste.anfang(pzeigeriterator);
																pzeigergeladen=true;
};
unsigned int _speicherbarbinaer::ladenanzahl(_datei*d){
																unsigned int*i=new unsigned int[1];
																unsigned int a;
																d->laden(a);
																(*(i))=a;
																panzahlliste.einhaengen(i);
																panzahlliste.anfang(panzahliterator);
																return(a);
};
unsigned int _speicherbarbinaer::ladenanzahl(){
																unsigned int i=*(panzahliterator->objekt()); 
																panzahliterator=panzahliterator->naechstes();
																return(i);
};

void _speicherbarbinaer::ladenbeginn(){
																loeschenzeiger();
																loeschenanzahl();
};
/*void _speichernbeginn(_datei*d){
				d->speichern(pname);
};*/
bool _speicherbarbinaer::zeigergeladen(){
																return(pzeigergeladen);
};
_zeichenkette<char>&_speicherbarbinaer::speichername(){
																return(pname);
};
void _speicherbarbinaer::loeschenzeiger(){
																pzeigerliste.loeschen();
																pzeigergeladen=false;
																pzeigeriterator=0;
};
void _speicherbarbinaer::loeschenanzahl(){
																panzahlliste.loeschen();
																panzahliterator=0;
};
bool _speicherbarbinaer::assoziieren(){
																return(true);
};
/*
template<class T> void _speicherbarbinaer::speichernzeiger(_datei*d,T*o){
				_zeichenkette<char> h;
				if(o==0){
				 h="null";
				 d->speichern(h);
				}else{
				 _spoeicherbarbinar*sb=dnymaic_cast<_speicherbarbinaer*>(o);
				 if(sb){
				  d->speichern(sb->name());
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
				if(liste->anfang(sit))do{
				 if(sit->pname==(*t)) {
				  o=dynamic_cast<T*>(sit);
				  return(o);
				 };
				}while(liste->naechstes(sit));
				return(0);
};*/






