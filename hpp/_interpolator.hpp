//******************************************************************************************************************************************************************************************************
//  Projekt     : grundplatte
//  Bibliothek  : _grundplatte.lib
//  Modul       : _interpolator.hpp
//  Datum       : 6.9.2008
//******************************************************************************************************************************************************************************************************
#ifndef _interpolatorh_included
#define _interpolatorh_included
#include <_funktion.hpp>
//******************************************************************************************************************************************************************************************************
//                                                              P R E D E K L A R A T I O N 
//******************************************************************************************************************************************************************************************************
template <class _tg=typgeometrie> class _interpolatorlinear;
template <class _tg=typgeometrie> class _interpolatorpolynominal;
//******************************************************************************************************************************************************************************************************
//                                                              I N T E R P O L A T O R
//******************************************************************************************************************************************************************************************************
template <class _tg> class _interpolator{
        public:
                _interpolator(_tg start,_tg end,_tg time);
                virtual ~_interpolator();
                bool beendet(){ return(pzeitalt==pzeit); };
                void setzen(_tg start,_tg end,_tg time);
                virtual _tg berechnen(_tg time)=0;
        protected:
                _tg pstart;
                _tg pende;      
                _tg pzeit;
                _tg pzeitalt; 
};
template <class _tg> _interpolator<_tg>::_interpolator(_tg start,_tg end,_tg time){
                                                                setzen(start,end,time);
};
template <class _tg> _interpolator<_tg>::~_interpolator(){

};
template <class _tg> void _interpolator<_tg>::setzen(_tg start,_tg end,_tg time){
                                                                pstart=start;
                                                                pende=end;
                                                                pzeit=time;
                                                                if(0==pzeit) pzeit=1;
                                                                pzeitalt=0;
};
//******************************************************************************************************************************************************************************************************
//                                                              I N T E R P O L A T O R L I N E A R 
//******************************************************************************************************************************************************************************************************
template <class _tg> class _interpolatorlinear : public _interpolator<_tg>{
        public:
                _interpolatorlinear(_tg start=0,_tg end=0,_tg time=1);
                _tg berechnen(_tg time);
};
template <class _tg> _interpolatorlinear<_tg>::_interpolatorlinear(_tg start,_tg end,_tg time):_interpolator<_tg>(start,end,time){

};
template <class _tg> _tg _interpolatorlinear<_tg>::berechnen(_tg time){
                                                                pzeitalt+=time;
                                                                if(pzeitalt>pzeit) pzeitalt=pzeit;
                                                                return(pstart+(pende-pstart)*begrenzen<_tg>(pzeitalt/pzeit,0,1));
}


//******************************************************************************************************************************************************************************************************
//                                                              I N T E R P O L A T O R P O L Y N O M I N A L 
//******************************************************************************************************************************************************************************************************
template <class _tg> class _interpolatorpolynominal : public _interpolator<_tg>{
        public:
                _interpolatorpolynominal(_tg start=0,_tg end=0,_tg time=1);
                _tg berechnen(_tg time);
};
template <class _tg> _interpolatorpolynominal<_tg>::_interpolatorpolynominal(_tg start,_tg end,_tg time):_interpolator<_tg>(start,end,time){
};
template <class _tg> _tg _interpolatorpolynominal<_tg>::berechnen(_tg time){
                                                                pzeitalt+=time;
                                                                if(pzeitalt>pzeit)pzeitalt=pzeit;
                                                                _tg frac=begrenzen<_tg>(pzeitalt/pzeit,0,1);
                                                                _tg f3=frac*frac*frac, f4=f3*frac;
                                                                return( 6 * (pende - pstart) * (f4 * frac) +
                                                                        15 * (pstart - pende) * f4 +
                                                                        10 * (pende - pstart) * f3 + pstart);
}


#endif