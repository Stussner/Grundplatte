//******************************************************************************************************************************************************************************************************
//  Project     : grundplatte
//  Library     : _grundplatte.lib
//  Module      : _drucker.hpp
//  Date        : 1.1.2003
//  Description : 
//******************************************************************************************************************************************************************************************************
#ifndef _druckerh_included
#define _druckerh_included
#include <_struktur.hpp>
#include <_grafik.hpp>

template<class _coordinate=double,class _color=float> class _drucker;


template<class _coordinate,class _color> class _drucker{
	public:
        	_drucker();
                virtual ~_drucker();
                _grafik<_coordinate,_color>*graphic();
        private:
        	_grafik<_coordinate,_color>*g;
};





//********************************************************************************************************************************************************************************
//								P R I N T E R
//********************************************************************************************************************************************************************************
template<class _coordinate,class _color> _drucker<_coordinate,_color>::_drucker(){
};
template<class _coordinate,class _color> _drucker<_coordinate,_color>::~_drucker(){
};




#endif

