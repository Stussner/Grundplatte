//grundplatte : druckerwindows.hpp
#ifndef _druckerwindowsh_included
#define _druckerwindowsh_included
#include <_global.hpp>
#ifdef GRUNDPLATTE_UNTER_WINDOWS
#include <_drucker.hpp>

//******************************************************************************************************************************************************************************
//								P R E D E K L A R A T I O N
//******************************************************************************************************************************************************************************
namespace _win{
template<class _coordinate=double,class _color=float> class _drucker;
};
//******************************************************************************************************************************************************************************
//								D E K L A R A T I O N
//******************************************************************************************************************************************************************************

namespace _win{
template<class _coordinate,class _color> class _drucker:public ::_drucker<_coordinate,_color>{
	public:
        	_drucker();
                virtual ~_drucker();
        private:

};
};










#endif
#endif
