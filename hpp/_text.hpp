//******************************************************************************************************************************************************************************************************
//  Project     : grundplatte
//  Library     : _grundplatte.lib
//  Module      : _text
//  Date        : 18.12.2002
//  Description : 
//******************************************************************************************************************************************************************************************************
#ifndef _texth_included
#define _texth_included
#include <_global.hpp>
#include <_vektor.hpp>
#include <_struktur.hpp>
#include <sstream>
#include <stdarg.h>
#include <vector>

template<class _tg> class _vektor3;
//******************************************************************************************************************************************************************************************************
//                                                              F O R W A R D S
//******************************************************************************************************************************************************************************************************
template<class _tt=typtext>                              class _zeichenkette;
//template<class _typgeometrie=typgeometrie>             class _zeichensatz;
typedef std::basic_stringstream<char> _stream;
typedef std::basic_stringstream<wchar_t> _streamwide;
//******************************************************************************************************************************************************************************************************
//                                                              S T R I N G 
//******************************************************************************************************************************************************************************************************
template<class _tt> class _zeichenkette{
        public:
                inline _zeichenkette();
                inline _zeichenkette(const _tt*);
                inline _zeichenkette(const _zeichenkette<_tt>&);
                inline _zeichenkette(const int i);
                inline _zeichenkette(_zeichenkette<_tt>*);
                //inline _zeichenkette(unsigned long);
                inline virtual ~_zeichenkette();
                void loeschencache();
                inline void erzeugen(const unsigned int);
                inline void setzen(const _tt*);
                inline void setzen(const _zeichenkette<_tt>&);
                inline void setzen(unsigned int,_tt);
                _tt*holen(_tt*,unsigned int) const;
                inline _tt holen(unsigned int) const;
                _zeichenkette<_tt> holen(unsigned int,unsigned int) const;
                const _tt* daten()const;
                _zeichenkette<char> ascii()const;
                template<class T> std::vector<T> stdvector() const;
                //-------------------------
                inline operator _tt*();
                inline _zeichenkette<_tt> operator+(const _tt*) const;
                inline _zeichenkette<_tt> operator+(const _zeichenkette<_tt>&) const;
                inline _zeichenkette<_tt> operator+(const int i) const;
                inline _zeichenkette<_tt>&operator+=(const _tt*);
                inline _zeichenkette<_tt>&operator+=(const _vektor3<_tg>&);
                inline _zeichenkette<_tt>&operator+=(const _zeichenkette<_tt>&);
                inline _zeichenkette<_tt>&operator+=(const int i);
                inline _zeichenkette<_tt>&operator=(const _tt*);
                inline _zeichenkette<_tt>&operator=(const _zeichenkette<_tt>&);
                inline _zeichenkette<_tt>&operator=(const int i);
                inline bool operator==(const _tt*) const;
                inline bool operator==(const _zeichenkette<_tt>&) const;
                inline bool operator!=(const _tt*) const;
                inline bool operator!=(const _zeichenkette<_tt>&) const;
                inline _tt operator[](unsigned int) const;
                //-------------------------
                inline unsigned int groesse() const;
                inline unsigned int speicherlast() const;
                unsigned int groesse(const _tt*) const;
                unsigned int speicherlast(const _tt*) const;
                void kopieren(const _tt*);
                void kopieren(const _zeichenkette<_tt>&);
                void kopierenchar(const char*);
                void kopieren(const int i);
                void anhaengen(const _tt*);
                void anhaengen(const _vektor3<_tg>&);
                void anhaengen(const _zeichenkette<_tt>&);
                void anhaengen(const int i);
                void anhaengenfront(const _tt*);
                void anhaengenfront(const _zeichenkette<_tt>&);
                bool suchen(const _tt*,unsigned int&) const;
                bool suchen(const _zeichenkette<_tt>&,unsigned int&) const;
                bool suchen(unsigned int,unsigned int&,const _tt*...) const;
                bool suchenunsensibel(const _tt*,unsigned int&) const;
                bool suchenunsensibel(const _zeichenkette<_tt>&,unsigned int&) const;
                bool ersetzen(const _zeichenkette<_tt>,const _tt*);
                bool ersetzen(const _zeichenkette<_tt>,const _zeichenkette<_tt>);
                bool zeichenidentifizierer(int i);
                bool ersetzenidentifizierer(const _zeichenkette<_tt>,const _tt*);
                bool ersetzenidentifizierer(const _zeichenkette<_tt>,const _zeichenkette<_tt>);
                bool teilen(const _zeichenkette<_tt> ss,_liste<_zeichenkette<_tt> >*l)const;
                bool replacetabulator(_zeichenkette<_tt>&);
                void konvertiereningross();
                void konvertiereninklein();
                int integer()const;
                bool vergleichen(const _tt*) const;
                bool vergleichen(const _zeichenkette<_tt>&) const;
                inline void einhaengen(const _tt*,unsigned int);
                inline void einhaengen(const _zeichenkette<_tt>&,unsigned int);
                _zeichenkette<_tt> aushaengen(unsigned int,unsigned int);
                //-------------------------------------
                bool entfernenendleerzeichen(unsigned int&,_zeichenkette<_tt>&);
                void entfernenendleerzeichen();
                void entfernenfrontleerzeichen();
                void entfernentrailleerzeichen();
                int anzahlfrontleerzeichen() const;
                
        private:
                inline void loeschen();
                void einhaengen(const _tt*,unsigned int,unsigned int);
                inline bool isunsensibleequal(_tt,_tt) const;
        public:
                _tt*cache;
        private:
                _tt*name;
                unsigned int psize;
};
template<class _tt> _zeichenkette<_tt>::_zeichenkette(){
                                                                name=0;
                                                                psize=0;
                                                                cache=0;
                                                                erzeugen(0);
};
/*
template<class _tt> _zeichenkette<_tt>::_zeichenkette(unsigned long int s){
                                                                name=0;
                                                                psize=s;
                                                                cache=0;
                                                                erzeugen(s);
};*/
template<class _tt> _zeichenkette<_tt>::_zeichenkette(const _zeichenkette<_tt>&s){
                                                                name=0;
                                                                psize=0;
                                                                cache=0;
                                                                erzeugen(0);
                                                                kopieren(s);
};
template<class _tt> _zeichenkette<_tt>::_zeichenkette(const int i){
                                                                name=0;
                                                                psize=0;
                                                                cache=0;
                                                                erzeugen(0);
                                                                kopieren(i);
};
template<class _tt> _zeichenkette<_tt>::_zeichenkette(_zeichenkette<_tt>*s){
                                                                name=0;
                                                                psize=0;
                                                                cache=0;
                                                                erzeugen(0);
                                                                kopieren(*s);
};/*
template<class _tt> _zeichenkette<_tt>::_zeichenkette(const char*c){
                                                                name=0;
                                                                psize=0;
                                                                cache=0;
                                                                erzeugen(0);
                                                                kopieren(c);
};*/
template<class _tt> _zeichenkette<_tt>::_zeichenkette(const _tt*c){
                                                                name=0;
                                                                psize=0;
                                                                cache=0;
                                                                erzeugen(0);
                                                                kopieren(c);
};
template<class _tt> _zeichenkette<_tt>::~_zeichenkette(){
                                                                loeschencache();
                                                                loeschen();
};
template<class _tt> void _zeichenkette<_tt>::loeschen(){
                                                                if(name){
                                                                 delete[] name;
                                                                };
                                                                loeschencache();
                                                                psize=0;
};
template<class _tt> void _zeichenkette<_tt>::loeschencache(){
                                                                if(cache!=0){
                                                                 delete[] cache;
                                                                 cache=0;
                                                                };
};
template<class _tt> void _zeichenkette<_tt>::erzeugen(const unsigned int s){
                                                                psize=s;
                                                                name=new _tt[psize+1];
                                                                name[0]=0;
																name[psize]=0;
};
template<class _tt> void _zeichenkette<_tt>::setzen(const _tt*c){
                                                                kopieren(c);
};
template<class _tt> void _zeichenkette<_tt>::setzen(const _zeichenkette<_tt>&s){
                                                                kopieren(s);
};
template<class _tt> void _zeichenkette<_tt>::setzen(unsigned int i,_tt c){
                                                                if((i>=0)&&(i<psize)){
                                                                 name[i]=c;
                                                                }else{
                                                                 //error 
                                                                };
};
template<class _tt> _tt* _zeichenkette<_tt>::holen(_tt*c,unsigned int externsize) const{
                                                                unsigned int i;
                                                                //------
                                                                i=0;
                                                                while((name[i])&&(i<(externsize-1))) {
                                                                 c[i]=name[i];
                                                                 i++;
                                                                };
                                                                c[i]=0;
                                                                return(c);
};
template<class _tt> _tt _zeichenkette<_tt>::holen(unsigned int i) const{
                                                                if((i>=0)&&(i<psize)){
                                                                 return(name[i]);
                                                                }else{
                                                                 return(69);
                                                                };
};
template<class _tt> _zeichenkette<_tt> _zeichenkette<_tt>::holen(unsigned int in,unsigned int anzahl) const{
                                                                unsigned int i;
                                                                unsigned int nit;
                                                                _zeichenkette s;
                                                                _tt*c=new _tt[abs(anzahl)+2];
                                                                unsigned int cit;
                                                                //-----
                                                                if((in<groesse())&&(anzahl>0)){
                                                                 nit=in;
                                                                 cit=0;
                                                                 for(i=0;i<anzahl;i++){
                                                                  if((nit>=0)&&(nit<groesse())) c[cit++]=name[nit++];
                                                                 };
                                                                 c[cit]=0;
                                                                 s.kopieren(c);
                                                                };
                                                                delete[] c;
                                                                return(s);
};
template<class _tt> const _tt*_zeichenkette<_tt>::daten()const {
                                                                return(name);
};
template<class _tt> _zeichenkette<char> _zeichenkette<_tt>::ascii()const{
                                                                _zeichenkette<char> r;
                                                                r.erzeugen(psize);
                                                                int i=0;
                                                                while(name[i]) {
                                                                 r.setzen(i,(char)name[i]);
                                                                 i++;
                                                                };
                                                                r.setzen(i,(char)0);
                                                                return(r);
};
template<class _tt> template<class T> std::vector<T> _zeichenkette<_tt>::stdvector() const{
                                                                std::vector<T> buffer;
                                                                buffer.resize(psize);
                                                                int n=0;
                                                                while(name[n]) {
                                                                 buffer[n]=T(name[n]);
                                                                 n++;
                                                                };
                                                               // buffer[n]=0;
                                                                return(buffer);
};

//-----------------------------------------------------------   S T R I N G - O P E R A T O R Ü B E R L A D U N G E N ---------------------------------------------------------------
template<class _tt> _zeichenkette<_tt>::operator _tt*(){
                                                                unsigned int i;
                                                                //----------
                                                                i=0;
                                                                loeschencache();
                                                                cache=new _tt[psize+1];
                                                                for(i=0;i<psize;i++){
                                                                 cache[i]=name[i];
                                                                };
                                                                cache[i]=0;
                                                                return(cache);
};
template<class _tt> _zeichenkette<_tt> _zeichenkette<_tt>::operator+(const _tt*c) const{
                                                                _zeichenkette<_tt> h=*this;
                                                                return(h+=c);
};
template<class _tt> _zeichenkette<_tt> _zeichenkette<_tt>::operator+(const _zeichenkette<_tt>&s) const{
                                                                _zeichenkette<_tt> h=*this;
                                                                h.anhaengen(s);
                                                                return(h);
};
template<class _tt> _zeichenkette<_tt> _zeichenkette<_tt>::operator+(const int i) const{
                                                                _zeichenkette<_tt> h=*this;
                                                                return(h+=i);
};

template<class _tt> _zeichenkette<_tt>&_zeichenkette<_tt>::operator+=(const _tt*c){
                                                                anhaengen(c);
                                                                return(*this);
};
template<class _tt> _zeichenkette<_tt>&_zeichenkette<_tt>::operator+=(const _vektor3<_tg>&v){
                                                                anhaengen(v);
                                                                return(*this);
};
template<class _tt> _zeichenkette<_tt>&_zeichenkette<_tt>::operator+=(const _zeichenkette<_tt>&s){
                                                                anhaengen(s);
                                                                return(*this);
};
template<class _tt> _zeichenkette<_tt>&_zeichenkette<_tt>::operator+=(const int i){
                                                                anhaengen(i);
                                                                return(*this);
};

template<class _tt> _zeichenkette<_tt>&_zeichenkette<_tt>::operator=(const _tt*c){
                                                                kopieren(c);
                                                                return(*this);
};
template<class _tt> _zeichenkette<_tt>&_zeichenkette<_tt>::operator=(const _zeichenkette<_tt>&s){
                                                                kopieren(s);
                                                                return(*this);
};
template<class _tt> _zeichenkette<_tt>&_zeichenkette<_tt>::operator=(const int i){
                                                                kopieren(i);
                                                                return(*this);
};
template<class _tt> bool _zeichenkette<_tt>::operator==(const _tt*c) const{
                                                                return(vergleichen(c));
};
template<class _tt> bool _zeichenkette<_tt>::operator==(const _zeichenkette<_tt>&s) const{
                                                                return(vergleichen(s));
};
template<class _tt> bool _zeichenkette<_tt>::operator!=(const _tt*c) const{
                                                                return(!vergleichen(c));
};
template<class _tt> bool _zeichenkette<_tt>::operator!=(const _zeichenkette<_tt>&s) const{
                                                                return(!vergleichen(s));
};
template<class _tt> _tt _zeichenkette<_tt>::operator[](unsigned int i) const{
                                                                if((i>=0)&&(i<psize)){
                                                                 return(name[i]);
                                                                }else{
                                                                 return(0);
                                                                };
};
//-----------------------------------------------------------   S T R I N G - F U N K T I O N E N -----------------------------------------------------------------------------------
template<class _tt> unsigned int _zeichenkette<_tt>::groesse() const{
                                                                return(psize);
};
template<class _tt> unsigned int _zeichenkette<_tt>::groesse(const _tt*c) const{
                                                                unsigned int i=0;
                                                                //--------
                                                                if(c){
                                                                 while(c[i]!=0) i++;
                                                                };
                                                                return(i);
};
template<class _tt> unsigned int _zeichenkette<_tt>::speicherlast() const{
                                                                return(groesse()*sizeof(_tt));
};
template<class _tt> unsigned int _zeichenkette<_tt>::speicherlast(const _tt*c) const{
                                                                return(groesse()*sizeof(_tt));
};
template<class _tt> void _zeichenkette<_tt>::kopieren(const _tt*s){
                                                                unsigned int i;
                                                                unsigned int l=groesse(s);
                                                                if(l!=psize){
                                                                 loeschen();
                                                                 erzeugen(l);
                                                                };
                                                                i=0;
                                                                while(s[i]!=0) {
                                                                 name[i]=s[i];
                                                                 i++;
                                                                };
                                                                name[i]=0;
};
template<class _tt> void _zeichenkette<_tt>::kopieren(const _zeichenkette<_tt>&s){
                                                                unsigned int i;
                                                                //----------
                                                                if(psize!=s.psize){
                                                                 loeschen();
                                                                 erzeugen(s.psize);
                                                                };
                                                                i=0;
                                                                while(s.name[i]!=0) name[i]=s.name[i++];
                                                                name[i]=0;
};
template<class _tt> void _zeichenkette<_tt>::kopierenchar(const char*c){
                                                                unsigned int i;
                                                                //----------
                                                                unsigned int l=static_cast<unsigned int>(strlen(c));
                                                                if(psize!=l){
                                                                 loeschen();
                                                                 erzeugen(l);
                                                                };
                                                                i=0;
                                                                while(c[i]!=0) name[i]=c[i++];
                                                                name[i]=0;
                                                                
};
template<class _tt> void _zeichenkette<_tt>::kopieren(const int i){
                                                                unsigned int n;
                                                                char buf[128];
                                                                _itoa(i,buf,10);
                                                                unsigned int l=strlen(buf);
                                                                if(l!=psize){
                                                                 loeschen();
                                                                 erzeugen(l);
                                                                };
                                                                n=0;
                                                                while(buf[n]!=0) {
                                                                 name[n]=_tt(buf[n]);
                                                                 n++;
                                                                };
                                                                name[n]=0;
};

template<class _tt> void _zeichenkette<_tt>::anhaengen(const _tt*c){
                                                                _tt*ln;
                                                                unsigned int os;
                                                                unsigned int z;
                                                                unsigned int i;
                                                                //--------
                                                                ln=name;
                                                                os=psize;
                                                                name=0;
                                                                erzeugen(groesse(c)+os);
                                                                i=0;
                                                                z=0;
                                                                while(ln[i]!=0) {
                                                                 name[z++]=ln[i++];
                                                                };
                                                                i=0;
                                                                while(c[i]!=0) name[z++]=c[i++];
                                                                name[z]=0;
                                                                psize=z;
                                                                delete[] ln;
};
template<class _tt> void _zeichenkette<_tt>::anhaengen(const _vektor3<_tg>&v){
                                                                _zeichenkette<_tt> h;
                                                                char c[128];
                                                                unsigned int i;
                                                                //-------------
                                                                h="[";
                                                                for(i=0;i<3;i++){
                                                                 _gcvt(v[i],10,c);
                                                                 h+=c;
                                                                 if(i<(3-1)){
                                                                  h+="; ";
                                                                 };
                                                                };
                                                                h+="]";
                                                                anhaengen(h);
};
template<class _tt> void _zeichenkette<_tt>::anhaengen(const _zeichenkette<_tt>&s){
                                                                _tt*ln;
                                                                unsigned int os;
                                                                unsigned int z;
                                                                unsigned int i;
                                                                //--------
                                                                ln=name;
                                                                os=psize;
                                                                name=0;
                                                                erzeugen(s.psize+os);
                                                                i=0;
                                                                z=0;
                                                                while(ln[i]!=0) name[z++]=ln[i++];
                                                                i=0;
                                                                while(s.name[i]!=0) name[z++]=s.name[i++];
                                                                name[z]=0;
                                                                psize=z;
                                                                delete[] ln;
};
template<class _tt> void _zeichenkette<_tt>::anhaengen(const int i){
                                                                char buf[128];
                                                                _itoa(i,buf,10);
                                                                int n=0;
                                                                _tt tt[128];
                                                                while(buf[n]) {
                                                                 tt[n]=_tt(buf[n]);
																 n++;
                                                                };
                                                                tt[n]=0;
                                                                anhaengen(tt);
};

template<class _tt> void _zeichenkette<_tt>::anhaengenfront(const _zeichenkette<_tt>&s){
                                                                _tt*ln;
                                                                unsigned int os;
                                                                unsigned int z;
                                                                unsigned int i;
                                                                //--------
                                                                ln=name;
                                                                os=psize;
                                                                name=0;
                                                                erzeugen(s.psize+os);
                                                                i=0;
                                                                z=0;
                                                                while(s.name[i]!=0) name[z++]=s.name[i++];
                                                                i=0;
                                                                while(ln[i]!=0) name[z++]=ln[i++];
                                                                name[z]=0;
                                                                psize=z;
                                                                delete[] ln;
};
template<class _tt> void _zeichenkette<_tt>::anhaengenfront(const _tt*c){
                                                                _tt*ln;
                                                                unsigned int os;
                                                                unsigned int z;
                                                                unsigned int i;
                                                                //--------
                                                                ln=name;
                                                                os=psize;
                                                                name=0;
                                                                erzeugen(groesse(c)+os);
                                                                i=0;
                                                                z=0;
                                                                while(c[i]!=0) name[z++]=c[i++];
                                                                i=0;
                                                                while(ln[i]!=0) name[z++]=ln[i++];
                                                                name[z]=0;
                                                                psize=z;
                                                                delete[] ln;
};
template<class _tt> bool _zeichenkette<_tt>::suchen(const _tt*c,unsigned int&in) const{
                                                                if(c){
                                                                 _zeichenkette h=c;
                                                                 return(suchen(h,in));
                                                                }else{
                                                                 return(false);
                                                                };

};
template<class _tt> bool _zeichenkette<_tt>::suchen(const _zeichenkette<_tt>&s,unsigned int&in) const{
                                                                unsigned int n;
                                                                bool loop=1;
                                                                bool found=0;
                                                                unsigned int lin;
                                                                //----------
                                                                if(in<psize){
                                                                 if((psize>=s.psize)&&(s.psize>0)){
                                                                  do{
                                                                   if(name[in]){
                                                                    n=0;
                                                                    lin=in;
                                                                    while((name[lin])&&(s[n])&&(s[n]==name[lin])){
                                                                     lin++;
                                                                     n++;
                                                                    };
                                                                    if(n==s.psize){
                                                                     found=true;
                                                                     loop=false;
                                                                    }else{
                                                                     in++;
                                                                    };
                                                                   }else{
                                                                    loop=false;
                                                                    found=false;
                                                                   };
                                                                  }while(loop);
                                                                  return(found);
                                                                 }else{
                                                                  return(false);
                                                                 };
                                                                }else{
                                                                 return(false);
                                                                };
};
template<class _tt> bool _zeichenkette<_tt>::suchen(unsigned int anzahl,unsigned int&index,const _tt*start...) const{
                                                                unsigned int sit;
                                                                unsigned int nit;
                                                                bool loop;
                                                                bool found;
                                                                _zeichenkette<_tt>*s;
                                                                _liste<_zeichenkette> liste;
                                                                _listenknoten<_zeichenkette>*lit;
                                                                va_list l;
                                                                unsigned int i;
                                                                //----------
                                                                liste.einhaengen(new _zeichenkette<_tt>(start));
                                                                va_start(l,start);
                                                                for(i=0;i<(anzahl-1);i++) liste.einhaengen(new _zeichenkette<_tt>(va_arg(l,_tt*)));
                                                                va_end(l);
                                                                loop=true;
                                                                found=false;
                                                                do{
                                                                 if(name[index]){
                                                                  if(liste.anfang(lit))do{
                                                                   s=lit->objekt();//liste.iterator();
                                                                   if((psize>=s->psize)&&(s->psize>0)){
                                                                    sit=0;
                                                                    nit=index;
                                                                    while((name[nit])&&(s->holen(sit))&&(s->holen(sit)==name[nit])){
                                                                     sit++;
                                                                     nit++;
                                                                    };
                                                                    if(sit==s->psize){
                                                                     found=true;
                                                                     loop=false;
                                                                    };
                                                                   };
                                                                  }while((liste.naechstes(lit))&&(loop));
                                                                  if(found==false) index++;
                                                                 }else{
                                                                  loop=false;
                                                                 };
                                                                }while(loop);
                                                                liste.loeschen();
                                                                return(found);
};
template<class _tt> bool _zeichenkette<_tt>::suchenunsensibel(const _tt*c,unsigned int&in) const{
                                                                if(c){
                                                                 _zeichenkette<_tt> h=c;
                                                                 return(suchenunsensibel(h,in));
                                                                }else{
                                                                 return(false);
                                                                };
};
template<class _tt> bool _zeichenkette<_tt>::suchenunsensibel(const _zeichenkette<_tt>&s,unsigned int&in) const{
                                                                unsigned int n;
                                                                bool loop=1;
                                                                bool found=0;
                                                                unsigned int lin;
                                                                //----------
                                                                if(in<psize){
                                                                 if((psize>=s.psize)&&(s.psize>0)){
                                                                  do{
                                                                   if(name[in]){
                                                                    n=0;
                                                                    lin=in;
                                                                    while((name[lin])&&(s[n])&&isunsensibleequal(s[n],name[lin])){
                                                                     lin++;
                                                                     n++;
                                                                    };
                                                                    if(n==s.psize){
                                                                     found=true;
                                                                     loop=false;
                                                                    }else{
                                                                     in++;
                                                                    };
                                                                   }else{
                                                                    loop=false;
                                                                    found=false;
                                                                   };
                                                                  }while(loop);
                                                                  return(found);
                                                                 }else{
                                                                  return(false);
                                                                 };
                                                                }else{
                                                                 return(false);
                                                                };
};
template<class _tt> bool _zeichenkette<_tt>::isunsensibleequal(_tt a,_tt b) const{
                                                                if((b>='a')&&(b<='z')) b-=' ';
                                                                if(b=='ä') b='Ä';
                                                                if(b=='ö') b='Ö';
                                                                if(b=='ü') b='Ü';
                                                                if((a>='a')&&(a<='z')) a-=' ';
                                                                if(a=='ä') a='Ä';
                                                                if(a=='ö') a='Ö';
                                                                if(a=='ü') a='Ü';
                                                                if(a==b) return(true); else return(false);
                                                                
};
//-------------------------------------------------------------- ersetzen ohne rückdsicht auf umgebungszeichen -----------------------------------------------
template<class _tt> bool _zeichenkette<_tt>::ersetzen(const _zeichenkette<_tt> ss,const _tt*c){
                                                                if(c==0){
                                                                 _zeichenkette<_tt> h;
                                                                 //L->schreiben("11");
                                                                 return(ersetzen(ss,h));
                                                                }else{
                                                                 if(c[0]==0){
                                                                  _zeichenkette<_tt> h;
                                                                  //L->schreiben("22");
                                                                  return(ersetzen(ss,h));
                                                                  //return(true);
                                                                 }else{
                                                                  _zeichenkette<_tt> h=c;
                                                                  //L->schreiben("33");
                                                                  return(ersetzen(ss,h));
                                                                 };
                                                                };
};
template<class _tt> bool _zeichenkette<_tt>::ersetzen(const _zeichenkette<_tt> ss,const _zeichenkette<_tt> rs){
                                                                _liste<unsigned int> liste;
                                                                _listenknoten<unsigned int>*iit;
                                                                unsigned int i=0;
                                                                unsigned int*ni;
                                                                unsigned int npsize;
                                                                unsigned int c=0;
                                                                _tt*ln;

                                                                unsigned int lnit;
                                                                unsigned int nit;
                                                                unsigned int z;
                                                                unsigned int n;
                                                                //--------------
                                                                while(suchen(ss,i)){
                                                                 ni=new unsigned int;
                                                                 ni[0]=i;
                                                                 liste.einhaengen(ni);
                                                                 c++;
                                                                 i++;
                                                                };
                                                                if(c){
                                                                 npsize=psize+(c*(rs.psize-ss.psize));
                                                                 ln=name;
                                                                 name=0;
                                                                 erzeugen(npsize);
                                                                 lnit=0;
                                                                 nit=0;
                                                                 if(liste.anfang(iit))do{
                                                                  z=*iit->objekt();//liste.iterator();
                                                                  while(lnit<z) name[nit++]=ln[lnit++];
                                                                  lnit+=ss.psize;
                                                                  for(n=0;n<rs.psize;n++) name[nit++]=rs[n];
                                                                 }while(liste.naechstes(iit));
                                                                 while(ln[lnit]) name[nit++]=ln[lnit++];
                                                                 name[nit]=0;
                                                                 liste.loeschen();
                                                                 delete[] ln;
                                                                 return(true);
                                                                }else{
                                                                 return(false);
                                                                };
};
//-------------------------------------------------------------- ersetzen mit rückdsicht auf umgebungszeichen -----------------------------------------------
template<class _tt> bool _zeichenkette<_tt>::zeichenidentifizierer(int i){  
                                                                if(i<0) return(false);
                                                                if(name[i]==0) return(false);
                                                                if((name[i]>='0')&&(name[i]<='9')) return(true);
                                                                if((name[i]>='a')&&(name[i]<='z')) return(true);
                                                                if((name[i]>='A')&&(name[i]<='Z')) return(true);
                                                                if(name[i]=='_') return(true);
                                                                return(false);
                                                                
};
template<class _tt> bool _zeichenkette<_tt>::ersetzenidentifizierer(const _zeichenkette<_tt> ss,const _tt*c){
                                                                if(c==0){
                                                                 _zeichenkette<_tt> h;
                                                                 //L->schreiben("11");
                                                                 return(ersetzenidentifizierer(ss,h));
                                                                }else{
                                                                 if(c[0]==0){
                                                                  _zeichenkette<_tt> h;
                                                                  //L->schreiben("22");
                                                                  return(ersetzenidentifizierer(ss,h));
                                                                  //return(true);
                                                                 }else{
                                                                  _zeichenkette<_tt> h=c;
                                                                  //L->schreiben("33");
                                                                  return(ersetzenidentifizierer(ss,h));
                                                                 };
                                                                };
};
template<class _tt> bool _zeichenkette<_tt>::ersetzenidentifizierer(const _zeichenkette<_tt> ss,const _zeichenkette<_tt> rs){
                                                                _liste<unsigned int> liste;
                                                                _listenknoten<unsigned int>*iit;
                                                                unsigned int i=0;
                                                                unsigned int*ni;
                                                                unsigned int npsize;
                                                                unsigned int c=0;
                                                                _tt*ln;

                                                                unsigned int lnit;
                                                                unsigned int nit;
                                                                unsigned int z;
                                                                unsigned int n;
                                                                //--------------
                                                                while(suchen(ss,i)){
                                                                 if((zeichenidentifizierer(i+ss.psize)==false)&&(zeichenidentifizierer(i-1)==false)){
                                                                  ni=new unsigned int;
                                                                  ni[0]=i;
                                                                  liste.einhaengen(ni);
                                                                  c++;
                                                                 };
                                                                 i++;
                                                                };
                                                                if(c){
                                                                 npsize=psize+(c*(rs.psize-ss.psize));
                                                                 ln=name;
                                                                 name=0;
                                                                 erzeugen(npsize);
                                                                 lnit=0;
                                                                 nit=0;
                                                                 if(liste.anfang(iit))do{
                                                                  z=*iit->objekt();//liste.iterator();
                                                                  while(lnit<z) name[nit++]=ln[lnit++];
                                                                  lnit+=ss.psize;
                                                                  for(n=0;n<rs.psize;n++) name[nit++]=rs[n];
                                                                 }while(liste.naechstes(iit));
                                                                 while(ln[lnit]) name[nit++]=ln[lnit++];
                                                                 name[nit]=0;
                                                                 liste.loeschen();
                                                                 delete[] ln;
                                                                 return(true);
                                                                }else{
                                                                 return(false);
                                                                };
};
//---------------------------------------------------------------------------------------------------------------------------------------------------------
template<class _tt> bool _zeichenkette<_tt>::teilen(const _zeichenkette<_tt> ss,_liste<_zeichenkette<_tt> >*l)const{
                                                                _liste<unsigned int> li;
                                                                _listenknoten<unsigned int>*iit;
                                                                unsigned int i=0;
                                                                unsigned int*ni;
                                                                int sis;
                                                                int sie;
                                                                int di;
                                                                unsigned int ssg=ss.groesse();
                                                                //--------------
                                                                l->aushaengen();
                                                                while(suchen(ss,i)){
                                                                 ni=new unsigned int;
                                                                 ni[0]=i;
                                                                 li.einhaengen(ni);
                                                                 i++;
                                                                };
                                                                if(li.anzahl()>0){
                                                                 _tt*temp=new _tt[psize+1];
                                                                 sis=0;
                                                                 if(li.anfang(iit))do{
                                                                  sie=*iit->objekt();
                                                                  if(sie>0){
                                                                   if((sis)<sie){
                                                                    di=0;
                                                                    for(int si=sis;si<sie;si++){
                                                                     temp[di++]=name[si];
                                                                    };
                                                                    temp[di]=0;
                                                                    l->einhaengen(new _zeichenkette<_tt>(temp));
                                                                   };
                                                                  };
                                                                  sis=sie+ssg;
                                                                 }while(li.naechstes(iit));
                                                                 if(sis<int(psize+1)){
                                                                  di=0;
                                                                  while(name[sis]!=0){
                                                                   temp[di++]=name[sis++];
                                                                  };
                                                                  temp[di]=0;
                                                                  l->einhaengen(new _zeichenkette<_tt>(temp));
                                                                 };
                                                                 delete temp;
                                                                }else{
                                                                 l->einhaengen(new _zeichenkette<_tt>(ss));
                                                                };
                                                                if(l->anzahl()>0) return(true); else return(false);
                                                                
};
//---------------------------------------------------------------------------------------------------------------------------------------------------------
template<class _tt> bool _zeichenkette<_tt>::replacetabulator(_zeichenkette<_tt>&s){
                                                                _tt ctab[4]={0x09,0,0,0};
                                                                _zeichenkette<_tt> tab=ctab;
                                                                return(ersetzen(tab,s));
};
template<class _tt> void _zeichenkette<_tt>::konvertiereningross(){
                                                                unsigned int i;
                                                                //---------
                                                                i=0;
                                                                while(name[i]){
                                                                 if((name[i]>='a')&&(name[i]<='z')) name[i]-=' ';
                                                                 i++;
                                                                };
};
template<class _tt> void _zeichenkette<_tt>::konvertiereninklein(){
                                                                unsigned int i;
                                                                //---------
                                                                i=0;
                                                                while(name[i]){
                                                                 if((name[i]>='A')&&(name[i]<='Z')) name[i]+=' ';
                                                                 i++;
                                                                };
};
template<class _tt> int _zeichenkette<_tt>::integer()const{
                                                                char buf[1024];
                                                                int i=0;
                                                                while(name[i]){
                                                                 buf[i]=(char)name[i];
                                                                 i++;
                                                                 
                                                                };
                                                                buf[i]=0;
                                                                return(atoi(buf));
                                                                
};

template<class _tt> bool _zeichenkette<_tt>::vergleichen(const _tt*c) const{
                                                                unsigned int i;
                                                                //-----
                                                                if(psize==groesse(c)){
                                                                 i=0;
                                                                 while((name[i])&&(c[i])&&(name[i]==c[i])) i++;
                                                                 if((name[i]==0)&&(c[i]==0)) return(true);
                                                                 return(false);
                                                                }else{
                                                                 return(false);
                                                                };
};
template<class _tt> bool _zeichenkette<_tt>::vergleichen(const _zeichenkette<_tt>&s) const{
                                                                unsigned int i;
                                                                //-----
                                                                if(psize==s.psize){
                                                                 i=0;
                                                                 while((name[i])&&(s.name[i])&&(name[i]==s.name[i])) i++;
                                                                 if((name[i]==0)&&(s.name[i]==0)) return(true);
                                                                 return(false);
                                                                }else{
                                                                 return(false);
                                                                };
};
template<class _tt> void _zeichenkette<_tt>::einhaengen(const _tt*c,unsigned int in){
                                                                einhaengen(c,groesse(c),in);
};
template<class _tt> void _zeichenkette<_tt>::einhaengen(const _zeichenkette<_tt>&s,unsigned int in){
                                                                einhaengen(s.name,s.psize,in);
};
template<class _tt> void _zeichenkette<_tt>::einhaengen(const _tt*c,unsigned int l,unsigned int in){
                                                                _tt*ln;
                                                                unsigned int lnit;
                                                                unsigned int nit;
                                                                unsigned int n;
                                                                //---------
                                                                if(in<psize){
                                                                 ln=name;
                                                                 name=0;
                                                                 erzeugen(psize+l);
                                                                 lnit=0;
                                                                 nit=0;
                                                                 n=0;
                                                                 while(lnit<in) name[nit++]=ln[lnit++];
                                                                 while(c[n])    name[nit++]=c[n++];
                                                                 while(ln[lnit])name[nit++]=ln[lnit++];
                                                                 name[nit]=0;
                                                                }else{
                                                                 if(in==psize)anhaengen(c);
                                                                };
};
template<class _tt> _zeichenkette<_tt> _zeichenkette<_tt>::aushaengen(unsigned int in,unsigned int anzahl){
                                                                _tt*ln;
                                                                unsigned int nit;
                                                                unsigned int lnit;
                                                                _zeichenkette<_tt> s;
                                                                _tt ad[2];
                                                                unsigned int i;
                                                                //-------
                                                                ad[0]=0;
                                                                if((in<psize)&&(anzahl>0)&&(anzahl<=psize)){
                                                                 if(anzahl>(psize-in)) anzahl=psize-in;
                                                                 ln=name;
                                                                 name=0;
                                                                 erzeugen(psize-anzahl);
                                                                 nit=0;
                                                                 lnit=0;
                                                                 while(lnit<in) name[nit++]=ln[lnit++];
                                                                 //lnit+=anzahl;
                                                                 for(i=0;i<anzahl;i++){
                                                                  ad[0]=ln[lnit++];
                                                                  ad[1]=0;
                                                                  s+=ad;
                                                                  ad[0]=0;
                                                                 };
                                                                 while(ln[lnit])name[nit++]=ln[lnit++];
                                                                 name[nit]=0;
                                                                };
                                                                return(s);
};
//------------------------------------------------------------- leertaste manipulation --------------------------------------------------------------------------
template<class _tt> bool _zeichenkette<_tt>::entfernenendleerzeichen(unsigned int&start,_zeichenkette<_tt>&rem){
                                                                unsigned int nit;
                                                                unsigned int i;
                                                                //-----------
                                                                if(psize>0){
                                                                 nit=psize-1;
                                                                 i=0;
                                                                 rem="";
                                                                 while(name[nit]==32) {
                                                                  nit--;
                                                                  i++;
                                                                  rem+=(_tt*)" ";
                                                                 };
                                                                 if(i>0){
                                                                  nit++;
                                                                  aushaengen(nit,i);
                                                                  start=nit;
                                                                  return(true);
                                                                 }else return(false);
                                                                }else return(false);
};
template<class _tt> void _zeichenkette<_tt>::entfernenendleerzeichen(){
                                                                _zeichenkette<_tt> h;
                                                                unsigned int i;
                                                                //---------
                                                                i=0;
                                                                entfernenendleerzeichen(i,h);
};
template<class _tt> void _zeichenkette<_tt>::entfernenfrontleerzeichen(){
                                                                unsigned int i;
                                                                //-------
                                                                i=anzahlfrontleerzeichen();
                                                                if(i>0){
                                                                 aushaengen(0,i);
                                                                };
                                                                
};
template<class _tt> void _zeichenkette<_tt>::entfernentrailleerzeichen(){
                                                                entfernenfrontleerzeichen();
                                                                entfernenendleerzeichen();
};
template<class _tt> int _zeichenkette<_tt>::anzahlfrontleerzeichen() const{
                                                                unsigned int c=0;
                                                                unsigned int nit=0;
                                                                while(name[nit]==32) {
                                                                 nit++;
                                                                 c++;
                                                                };
                                                                return(c);
};



/*
//******************************************************************************************************************************************************************************************************
//                                                              F O N T 
//******************************************************************************************************************************************************************************************************
template<class _coordinate> class _zeichensatz{
        public:
                        _zeichensatz();
                        virtual ~_zeichensatz();
        private:
};
template<class _coordinate> _zeichensatz<_coordinate>::_zeichensatz(){
};
template<class _coordinate> _zeichensatz<_coordinate>::~_zeichensatz(){
}; 

*/

//
//  Macros
//

#define STRING_COPYANDRETURN(__data1, __len1, __data2, __len2) \
   T  *tempdata = new T[(__len1) + (__len2) + 1]; \
   \
   memcpy(tempdata, (__data1), sizeof(T) * (__len1)); \
   memcpy(&tempdata[(__len1)], (__data2), sizeof(T) * (__len2)); \
   tempdata[(__len1) + (__len2)] = 0; \
   \
   T_String<T>  newstr(tempdata); \
   delete[] tempdata; \
   \
   return(newstr)
// end STRING_COPYANDRETURN


#define STRING_COPYANDRETURNINPLACE(__data1, __len1, __data2, __len2) \
   T  *tempdata = new T[(__len1) + (__len2) + 1]; \
   \
   memcpy(tempdata, (__data1), sizeof(T) * (__len1)); \
   memcpy(&tempdata[(__len1)], (__data2), sizeof(T) * (__len2)); \
   tempdata[(__len1) + (__len2)] = 0; \
   \
   *this = tempdata; \
   delete[] tempdata; \
   \
   return(*this)
// end STRING_COPYANDRETURNINPLACE


// Forwards
template <class T = wchar_t> class T_String;


// -------------------------------------------------------------------------------------------------
//
//  T_String
//
// -------------------------------------------------------------------------------------------------
template <class T> class T_String
{
   public:
     enum
     {
        npos = 0xFFFFFFFF
     };
   
   
   public:
     T_String();
     T_String(T const *str);
     T_String(T_String<T> const &other);
     virtual ~T_String();
     
     T const *Data() const         { return(m_Data); }
     bcUInt32 Length() const       { return(m_Length); }
     bcUInt32 ElementSize() const  { return(sizeof(T)); }
     
     bcUInt32 CountChars(T const &ch) const;
     void ReplaceChar(bcUInt32 pos, T const &ch);
     void Replace(T const &ch1, T const &ch2);
     bcUInt32 Find(T const &ch, bcUInt32 offset = 0) const;
     bcUInt32 Find(T_String<T> const &str, bcUInt32 offset = 0) const;
     bcUInt32 RFind(T const &ch, bcUInt32 offset = npos) const;
     bcUInt32 RFind(T_String<T> const &str, bcUInt32 offset = npos) const;
     T_String<T> SubString(bcUInt32 start, bcUInt32 count = npos) const;
     
     void ToLower();
     void ToUpper();
     
     bcBool Bool() const;
     bcInt32 Int32() const;
     bcInt64 Int64() const;
     bcFloat32 Float32() const;
     bcFloat64 Float64() const;
     void Split(bcWideChar separator, T_String<> *parts, bcUInt32 numparts) const;
     
     T_String<T> &operator = (T const *str);
     T_String<T> &operator = (T_String<T> const &other);
     T_String<T> operator + (T const *str) const;
     T_String<T> operator + (T_String<T> const &other) const;
     T_String<T> &operator += (T_String<T> const &other);
     bcBool operator == (T_String<T> const &other) const;
     bcBool operator != (T_String<T> const &other) const;
     bcBool operator < (T_String<T> const &other) const;
     bcBool operator > (T_String<T> const &other) const;
     
     T const operator [] (bcUInt32 index) const;
     //T &operator [] (bcUInt32 index);
     
   
   private:
     void CreateData(T const *data, bcUInt32 len = npos);
     
   
   private:
     T         *m_Data;
     bcUInt32  m_Length;
};


// ==============
//  Constructors
// ==============
template <class T> T_String<T>::T_String()
{
   m_Data = 0;
   CreateData(0, 1);
}

template <class T> T_String<T>::T_String(T const *str)
{
   bcUInt32  len = 0;
   T const   *temp = str;
   // -------------------------------------------------------
   
   
   m_Data = 0;
   
   if(!str)
     {
        CreateData(0, 1);
        return;
     }
   
   while(*temp)
     {
        temp++;
        len++;
     }
   
   CreateData(str, len + 1);
}

template <class T> T_String<T>::T_String(T_String<T> const &other)
{
   m_Data = 0;
   *this = other;
}

// ============
//  Destructor
// ============
template <class T> T_String<T>::~T_String()
{
   delete[] m_Data;
}

// =================
//  Create the Data
// =================
template <class T> void T_String<T>::CreateData(T const *data, bcUInt32 len)
{
   delete[] m_Data;
   m_Data = new T[len];
   m_Data[len - 1] = 0;
   m_Length = len - 1;
   
   if(data && m_Length > 0)
     memcpy(m_Data, data, sizeof(T) * m_Length);
}

// =============================================
//  Count all matching characters in the String
// =============================================
template <class T> bcUInt32 T_String<T>::CountChars(T const &ch) const
{
   bcUInt32  count = 0;
   // ----------------------------------------------------
   
   
   for(T *data = m_Data; *data; data++)
     if(ch == *data)
       count++;
   
   return(count);
}

// =========================================
//  Replace a Character at a given Position
// =========================================
template <class T> void T_String<T>::ReplaceChar(bcUInt32 pos, T const &ch)
{
   if(pos < m_Length && ch)  // 0 is not allowed...
     m_Data[pos] = ch;
}

// ======================================
//  Replace all Characters in the String
// ======================================
template <class T> void T_String<T>::Replace(T const &ch1, T const &ch2)
{
   for(T *data = m_Data; *data; data++)
     if(ch1 == *data)
       *data = ch2;
}

// =================================
//  Find a String inside the String
// =================================
template <class T> bcUInt32 T_String<T>::Find(T const &ch, bcUInt32 offset) const
{
   if(offset >= m_Length)
     return(npos);
   
   for(; m_Data[offset]; offset++)
     if(ch == m_Data[offset])
       return(offset);
   
   return(npos);
}

template <class T> bcUInt32 T_String<T>::Find(T_String<T> const &str, bcUInt32 offset) const
{
   if(offset >= m_Length || 0 == str.Length())
     return(npos);
   
   bcUInt32  i;
   
   for(; m_Data[offset]; offset++)
     {
        if(str[0] == m_Data[offset])
          {
             if(offset + str.Length() <= m_Length)
               {
                  for(i = 0; i < str.Length(); i++)
                    if(str[i] != m_Data[offset + i])
                      break;
                  
                  if(i >= str.Length())
                    return(offset);
               }
          }
     }
   
   return(npos);
}

// ================================================
//  Find a String inside the String (from the end)
// ================================================
template <class T> bcUInt32 T_String<T>::RFind(T const &ch, bcUInt32 offset) const
{
   if(0 == Length())
     return(npos);
     
   if(offset >= m_Length)
     offset = m_Length - 1;
   
   while(true)
     {
        if(ch == m_Data[offset])
          return(offset);
        
        if(0 == offset)
          break;
        offset--;
     }
   
   return(npos);
}

template <class T> bcUInt32 T_String<T>::RFind(T_String<T> const &str, bcUInt32 offset) const
{
   if(0 == Length() || 0 == str.Length() || str.Length() > Length())
     return(npos);
   
   if(offset >= m_Length)
     offset = m_Length - 1;
   
   bcUInt32  i;
   while(true)
     {
        if(str[0] == m_Data[offset])
          {
             if(offset + str.Length() <= m_Length)
               {
                  for(i = 0; i < str.Length(); i++)
                    if(str[i] != m_Data[offset + i])
                      break;
                  
                  if(i >= str.Length())
                    return(offset);
               }
          }
        
        if(0 == offset)
          break;
        offset--;
     }
   
   return(npos);
}

// =====================
//  Return a Sub-String
// =====================
template <class T> T_String<T> T_String<T>::SubString(bcUInt32 start, bcUInt32 count) const
{
   if(start >= m_Length)
     return(T_String<T>());
   
   bcUInt64  end = start;  // need 64 bit for npos (overflow)
   end += count;
   if(end > m_Length)
     end = m_Length;
   end = (end - start);
   
   T  *tempdata = new T[end + 1];
   tempdata[end] = 0;
   memcpy(tempdata, &m_Data[start], sizeof(T) * end);
   
   T_String<T>  newstring(tempdata);
   delete[] tempdata;
   
   return(newstring);
}

// =========================================
//  Converts the whole String to lower-case
// =========================================
template <class T> void T_String<T>::ToLower()
{
   for(bcUInt32 i = 0; m_Data[i]; i++)
     m_Data[i] = towlower(m_Data[i]);
}

// =========================================
//  Converts the whole String to upper-case
// =========================================
template <class T> void T_String<T>::ToUpper()
{
   for(bcUInt32 i = 0; m_Data[i]; i++)
     m_Data[i] = toupper(m_Data[i]);
}

// =====================
//  Conversion routines
// =====================
template <class T> bcBool T_String<T>::Bool() const
{
   if(1 == Length())  // 0 or 1
     return(0 != _wtoi(Data()));
   
   T_String<>  temp(*this);
   temp.ToLower();
   if(L"true" == temp)
     return(true);
   if(L"false" == temp)
     return(false);
   
   return(0 != _wtoi(Data()));
}

template <class T> bcInt32 T_String<T>::Int32() const
{
   return(_wtoi(Data()));
}

template <class T> bcInt64 T_String<T>::Int64() const
{
   return(_wtoi64(Data()));
}

template <class T> bcFloat32 T_String<T>::Float32() const
{
   return((bcFloat32)_wtof(Data()));
}

template <class T> bcFloat64 T_String<T>::Float64() const
{
   return(_wtof(Data()));
}

// ==================
//  Split the String
// ==================
template <class T> void T_String<T>::Split(bcWideChar separator, T_String<> *parts, bcUInt32 numparts) const
{
   bcUInt32  pos[2];
   // ---------------------------------------------------------
   
   
   if(0 == parts)
     return;
   
   pos[0] = Find(separator);
   parts[0] = SubString(0, pos[0]++);
   
   for(bcUInt32 i = 1; i < numparts; i++)
     {
        pos[i & 1] = Find(separator, pos[(i + 1) & 1]);
        parts[i] = SubString(pos[(i + 1) & 1], pos[i & 1]++ - pos[(i + 1) & 1]);
     }
}

// ============
//  operator =
// ============
template <class T> T_String<T> &T_String<T>::operator = (T const *str)
{
   bcUInt32  len = 0;
   T const   *temp = str;
   // -------------------------------------------
   
   
   if(!str)
     {
        CreateData(0, 1);
        return(*this);
     }
   
   if(str == m_Data)
     return(*this);  // For Sanity
    
   while(*temp)
     {
        temp++;
        len++;
     }
   
   CreateData(str, len + 1);
   return(*this);
}

template <class T> T_String<T> &T_String<T>::operator = (T_String<T> const &other)
{
   if(this == &other)
     return(*this);  // For Sanity
   
   CreateData(other.m_Data, other.m_Length + 1);
   return(*this);
}

// ============
//  operator +
// ============
template <class T> T_String<T> T_String<T>::operator + (T const *str) const
{
   bcUInt32  len = 0;
   T const   *temp = str;
   // -------------------------------------------
   
   
   while(*temp)
     {
        temp++;
        len++;
     }
   
   STRING_COPYANDRETURN(m_Data, m_Length, str, len);
}

template <class T> T_String<T> T_String<T>::operator + (T_String<T> const &other) const
{
   STRING_COPYANDRETURN(m_Data, m_Length, other.m_Data, other.m_Length);
}

template <class T> T_String<T> &T_String<T>::operator += (T_String<T> const &other)
{
   STRING_COPYANDRETURNINPLACE(m_Data, m_Length, other.m_Data, other.m_Length);
}

// =============
//  operator ==
// =============
template <class T> bcBool T_String<T>::operator == (T_String<T> const &other) const
{
   if(m_Length != other.m_Length)
     return(false);
   
   for(bcUInt32 i = 0; i < m_Length; i++)
     if(m_Data[i] != other.m_Data[i])
       return(false);
   
   return(true);
}

// =============
//  operator !=
// =============
template <class T> bcBool T_String<T>::operator != (T_String<T> const &other) const
{
   return(!(*this == other));
}

// ============
//  operator <
// ============
template <class T> bcBool T_String<T>::operator < (T_String<T> const &other) const
{
   bcUInt32  len = Min(m_Length, other.m_Length);
   // ---------------------------------------------------
   
   
   for(bcUInt32 i = 0; i < len; i++)
     {
        if(m_Data[i] < other.m_Data[i])
          return(true);
        
        if(m_Data[i] > other.m_Data[i])
          return(false);
     }
   
   if(m_Length < other.m_Length)
     return(true);
   
   return(false);
}

// ============
//  operator >
// ============
template <class T> bcBool T_String<T>::operator > (T_String<T> const &other) const
{
   bcUInt32  len = Min(m_Length, other.m_Length);
   // ---------------------------------------------------
   
   
   for(bcUInt32 i = 0; i < len; i++)
     {
        if(m_Data[i] < other.m_Data[i])
          return(false);
        
        if(m_Data[i] > other.m_Data[i])
          return(true);
     }
   
   if(m_Length > other.m_Length)
     return(true);
   
   return(false);
}

// =============
//  operator []
// =============
template <class T> T const T_String<T>::operator [] (bcUInt32 index) const
{
   //assert(index <= m_Length);
   return(m_Data[index]);
}
/*
template <class T> T &T_String<T>::operator [] (bcUInt32 index)
{
   assert(index < m_Length);
   return(m_Data[index]);
}
*/

// ===================
//  Global operator +
// ===================
template <class T> _zeichenkette<T> operator + (T const *str1, _zeichenkette<T> const &str2){
                                                                _zeichenkette<T> hh=str1;
                                                                hh+=str2;
                                                                return(hh);
};                                                                
template <class T> T_String<T> operator + (T const *str1, T_String<T> const &str2){
                                                                bcUInt32 len=0;
                                                                T const*temp=str1;
                                                                // -------------------------------------------
                                                                while(*temp){
                                                                 temp++;
                                                                 len++;
                                                                };
                                                                STRING_COPYANDRETURN(str1, len, str2.Data(), str2.Length());
};

// ====================
//  Global operator ==
// ====================
template <class T> bcBool operator == (T const *str1, T_String<T> const &str2)
{
   return(str2 == str1);  // call member function
}

// ====================
//  Global operator !=
// ====================
template <class T> bcBool operator != (T const *str1, T_String<T> const &str2)
{
   return(str2 != str1);  // call member function
};

// ===========================
//  Global Stream-Overloading
// ===========================
template <class T> _stream &operator << (_stream &stream, T_String<T> const &str)
{
   stream << str.Data();
   return(stream);
};

template <class T> _streamwide &operator << (_streamwide &stream, T_String<T> const &str)
{
   stream << str.Data();
   return(stream);
};



#endif
