//******************************************************************************************************************************************************************************************************
//  Project     : grundplatte
//  Library     : _grundplatte.lib
//  Module      : system.hpp
//  Date        : 3.5.2003
//  Description : 
//******************************************************************************************************************************************************************************************************
#ifndef _systemwindows_included
#define _systemwindows_included
#include <_global.hpp>
#ifdef GRUNDPLATTE_UNTER_WINDOWS
#include <_system.hpp>
#include <windows.h>
//******************************************************************************************************************************************************************************
//                                                                P R E D E K L A R A T I O N
//******************************************************************************************************************************************************************************
namespace _win{
 class _system;
 class _zeit;
 class _datum;
 template<class _tg=typgeometrie> class _maus;
 class _tastatur;
 class _pclautsprecher;
 class _zeichensatz;
};


namespace _win{
//******************************************************************************************************************************************************************************************************
//                                                              S Y S T E M 
//******************************************************************************************************************************************************************************************************
 class _system:public ::_system{
        public:
                _system(HINSTANCE);
                virtual ~_system();
                void animieren();
        private:
                static LRESULT PASCAL prozess(HWND,UINT,WPARAM,LPARAM);
        private:
                HWND handle;
                HINSTANCE hinstance;
 };
//******************************************************************************************************************************************************************************************************
//                                                              T I M E 
//******************************************************************************************************************************************************************************************************
 class _zeit:public ::_zeit{
        public:
                virtual unsigned int system();
 };
//******************************************************************************************************************************************************************************************************
//                                                              D A T E 
//******************************************************************************************************************************************************************************************************
 class _datum:public ::_datum{
        public:
                virtual void anfang();
 };
//******************************************************************************************************************************************************************************************************
//                                                              S P E A K E R 
//******************************************************************************************************************************************************************************************************
 class _pclautsprecher{
        public:
                virtual void peep(int);
                virtual void peep(int,int);
 };
//******************************************************************************************************************************************************************************************************
//                                                              T A S T A T U R 
//******************************************************************************************************************************************************************************************************
 class _tastatur:public ::_tastatur{
        //friend class _system;
        public:
                _tastatur(/*_listebasis< ::_tastatur>* */);
                bool taste(const unsigned int)const;
                bool taste()const;
				void ladenfeld(char*feld);
				short status();

                bool leertaste()const;
                bool enter()const;
                bool escape()const;
                bool backspace()const;
                bool shift()const;
                bool control()const;
				bool tab()const;
                bool pfeillinks()const;
                bool pfeilrechts()const;
                bool pfeilhoch()const;
                bool pfeilrunter()const;
                bool knopflinks()const;
                bool knopfrechts()const;
                bool knopfmitte()const;
        private:
                //SHORT a;
                
 };
//******************************************************************************************************************************************************************************************************
//                                                              M O U S E 
//******************************************************************************************************************************************************************************************************
 template<class _tg>class _maus:public ::_maus<_tg>{
        public:
                using ::_maus<_tg>::relativ;       
        public:                
				_maus();
                _maus(_tg,_tg);
                _maus(_vektor2<_tg>);
                virtual _tg x()const;
                virtual _tg y()const;
                virtual _tg z()const;
                virtual void x(const _tg);
                virtual void y(const _tg);
                virtual void z(const _tg);
                
                _tg holen(const unsigned int)const;
                _vektor3<_tg> holen()const;
                void zeigen();
                void verstecken();
                void relativ(bool);
        private:
                _vektor3<_tg> palt;
 };
 template<class _tg> _maus<_tg>::_maus(): ::_maus<_tg>(0,0){
 };
 template<class _tg> _maus<_tg>::_maus(_tg x,_tg y): ::_maus<_tg>(x,y){
                                                                SetCursorPos(int(x),int(y));
                                                                palt.setzen(x,y,0);
 };
 template<class _tg> _maus<_tg>::_maus(_vektor2<_tg> x): ::_maus<_tg>(x){
                                                                SetCursorPos(int(x[0]),int(x[1]));
                                                                palt.setzen(x[0],x[1],0);
 };
 template<class _tg> _tg _maus<_tg>::x()const{
                                                                return(palt[0]);
 };
 template<class _tg> _tg _maus<_tg>::y()const{
                                                                return(palt[1]);
 };
 template<class _tg> _tg _maus<_tg>::z()const{
                                                                return(palt[2]);
};
template<class _tg> void _maus<_tg>::x(const _tg x){
                                                                palt.setzenkomponente(0,x);
};
template<class _tg> void _maus<_tg>::y(const _tg y){
                                                                palt.setzenkomponente(1,y);
};
template<class _tg> void _maus<_tg>::z(const _tg z){
                                                                palt.setzenkomponente(2,z);
};

 template<class _tg> _tg _maus<_tg>::holen(const unsigned int i)const{
                                                                POINT p;
                                                                _vektor3<_tg> o;
                                                                //---------------
                                                                o=ursprung();
                                                                GetCursorPos(&p);
                                                                if(relativ()){
                                                                 SetCursorPos(int(o[0]),int(o[1]));
                                                                 if(i==0){
                                                                  return(_tg(p.x)-o[0]);
                                                                 }else if(i==1){
                                                                  return(_tg(p.y)-o[1]);
                                                                 }else{
                                                                  return(_tg(palt[2]));
                                                                 };
                                                                }else if(relativfenster()){
                                                                 if(i==0){
                                                                  return(p.x-o.x());
                                                                 }else if(i==1){
                                                                  return(p.y-o.y());
                                                                 }else{
                                                                  return(palt[2]);
                                                                 };
                                                                }else{
                                                                 //if(i==0) return(_tg(p.x)); else if (i==1) return(_tg(p.y)); else return(palt[2]);
                                                                 return(palt[i]);
																};
																return(0);
 };
 template<class _tg> _vektor3<_tg> _maus<_tg>::holen()const{
                                                                POINT p;
                                                                _vektor3<_tg> v;
                                                                _vektor3<_tg> o;
                                                                //---------------
                                                                o=ursprung();
                                                                GetCursorPos(&p);
                                                                
                                                                if(relativ()){
                                                                 SetCursorPos(int(o[0]),int(o[1]));
                                                                 v.setzen(p.x,p.y,0);
                                                                 v-=o;
                                                                 return(v);   
                                                                }else if(relativfenster()){
                                                                 v.setzen(p.x-o.x(),p.y-o.y(),0);
                                                                 return(v);
                                                                }else{
                                                                 //v.setzen(p.x,p.y);
                                                                 //return(v);
                                                                 return(_vektor3<_tg>(palt[0],palt[1],palt[2]));
                                                                };
 };
 template<class _tg> void _maus<_tg>::zeigen(){
                                                                ShowCursor(TRUE);
 };
 template<class _tg> void _maus<_tg>::verstecken(){
                                                                ShowCursor(FALSE);
 };
 template<class _tg> void _maus<_tg>::relativ(bool b){
                                                                if(b==true){
                                                                 //war false,alte maus sichern
                                                                 POINT p;
                                                                 GetCursorPos(&p);
                                                                 palt.setzen(p.x,p.y,0);
                                                                 ursprung(palt);
                                                                 ::_maus<_tg>::relativ(true);
                                                                }else{
                                                                 //war true,neue maus sichern
                                                                 SetCursorPos(int(palt[0]),int(palt[1]));
                                                                 ::_maus<_tg>::relativ(false);
                                                                };
 };
};


#endif
#endif
