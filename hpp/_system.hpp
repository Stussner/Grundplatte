//grundplatte : _system.hpp
#ifndef _systemh_included
#define _systemh_included

#include <_global.hpp>
#include <_text.hpp>

//********************************************************************************************************************************************************************************
//                                                                P R E D E K L A R A T I O N E N
//********************************************************************************************************************************************************************************
class _system;
class _zeit;
class _datum;
template<class _tg=typgeometrie> class _maus;
class _tastatur;
class _pclautsprecher;
class _zeichensatz;
//******************************************************************************************************************************************************************************************************
//                                                              S Y S T E M 
//******************************************************************************************************************************************************************************************************
class _system{//:public _listebasis<_tastatur>{
        public:
                _system();
                virtual ~_system();
                virtual void animieren()=0;
};
extern _system*S;
bool IsLittleEndian();
//******************************************************************************************************************************************************************************************************
//                                                              T I M E 
//******************************************************************************************************************************************************************************************************
class _zeit {
        public:
                _zeit();
                virtual ~_zeit();
                void anfang();
                double holen();
                inline double animieren();
                virtual unsigned int system()=0;
                void delay(int);
        private:
                int s;                  //systemZeitkoordinate
                double t;               //animationsZeitkoordinate
                double a;               //animationsbeschleunigungsfaktor ,vorher vfactor
                double tord[2];         //alte und neue koordinate zur faktorberechnung

};
//******************************************************************************************************************************************************************************************************
//                                                              D A T E 
//******************************************************************************************************************************************************************************************************
class _datum{
        public:
                _datum();
                _datum(int,int,int);
                virtual ~_datum();
                int differenz(_datum*);
                virtual void anfang()=0;
                void setzen(int,int,int);
                void holenzeichenkette();
                char holenindex();
                char zerlegen(char*,int&,int&,int&);
        private:
                int year;
                int month;
                int day;
                int index;
                int daycount[12];
                _zeichenkette<char> string;
};
//******************************************************************************************************************************************************************************************************
//                                                              S P E A K E R 
//******************************************************************************************************************************************************************************************************
class _pclautsprecher{
        public:
                _pclautsprecher();
                virtual ~_pclautsprecher();
                virtual void peep(int)=0;
                virtual void peep(int,int)=0;
};
//******************************************************************************************************************************************************************************************************
//                                                              K E Y B O A R D 
//******************************************************************************************************************************************************************************************************
class _tastatur{//:public _listenknotenbasis<_tastatur>{
        //friend class _system;
        public:
                _tastatur(/*_listebasis<_tastatur>* */);
                virtual ~_tastatur();
                virtual bool leertaste()const=0;
				virtual void ladenfeld(char*feld)=0;
				virtual short status()=0;

                virtual bool enter()const=0;
                virtual bool escape()const=0;
                virtual bool backspace()const=0;
                virtual bool shift()const=0;
                virtual bool control()const=0;
				virtual bool tab()const=0;
                virtual bool pfeillinks()const=0;
                virtual bool pfeilrechts()const=0;
                virtual bool pfeilhoch()const=0;
                virtual bool pfeilrunter()const=0;
                virtual bool knopflinks()const=0;
                virtual bool knopfrechts()const=0;
                virtual bool knopfmitte()const=0;
                virtual bool taste(const unsigned int)const=0;
                virtual bool taste()const=0;


                //void taste(const unsigned int,bool);
        private:
              //  void clearkey();
        private:   
              //  bool pkey[1024];
};
//******************************************************************************************************************************************************************************************************
//                                                              M O U S E 
//******************************************************************************************************************************************************************************************************
template<class _tg>class _maus{
        public:
                _maus(_tg,_tg);
                _maus(_vektor2<_tg>);
                virtual ~_maus();
                virtual _tg x()const=0;
                virtual _tg y()const=0;
                virtual _tg z()const=0;
                virtual void x(const _tg)=0;
                virtual void y(const _tg)=0;
                virtual void z(const _tg)=0;
                virtual _tg holen(const unsigned int)const=0;
                virtual _vektor3<_tg> holen()const=0;
                virtual void zeigen()=0;
                virtual void verstecken()=0;
                inline _vektor3<_tg> ursprung()const;
                inline void ursprung(_vektor3<_tg>);
                virtual void relativ(bool);
                inline bool relativ()const;
                virtual void relativfenster(bool);
                inline bool relativfenster()const;
                
                //_tg relativ(int);
                //_tg absolute(int);
                
        private:       
                _vektor3<_tg> pa;
                bool pisrelative;
                bool pisrelativewindow;
                
};
template<class _tg> _maus<_tg>::_maus(_tg x,_tg y){
                                                                pa.setzen(x,y,0);
                                                                pisrelative=false;
                                                                pisrelativewindow=true;
};
template<class _tg> _maus<_tg>::_maus(_vektor2<_tg> x){
                                                                pa.setzen(x[0],x[1],0);
                                                                pisrelative=false;
                                                                pisrelativewindow=true;
};
template<class _tg> _maus<_tg>::~_maus(){
};
template<class _tg> _vektor3<_tg> _maus<_tg>::ursprung()const{
                                                                return(pa);
};
template<class _tg> void _maus<_tg>::ursprung(_vektor3<_tg> v){
                                                                pa=v;
};
template<class _tg> void _maus<_tg>::relativ(bool b){
                                                                pisrelative=b;
};
template<class _tg> bool _maus<_tg>::relativ() const{
                                                                return(pisrelative);
                                                
};
template<class _tg> void _maus<_tg>::relativfenster(bool b){
                                                                pisrelativewindow=b;
};
template<class _tg> bool _maus<_tg>::relativfenster() const{
                                                                return(pisrelativewindow);
                                                
};




#endif

