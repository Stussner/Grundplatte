//******************************************************************************************************************************************************************************************************
//  Project     : grundplatte
//  Library     : _grundplatte.lib
//  Module      : _global.hpp
//  Date        : 18.12.2002
//  Description : 
//******************************************************************************************************************************************************************************************************
#ifndef _global_included
#define _global_included
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
//******************************************************************************************************************************************************************************************************
//                                                              GLOBALER GRUNDPLATTENSCHALTER
//******************************************************************************************************************************************************************************************************
//#define GRUNDPLATTE_UNTER_LINUX
  #define GRUNDPLATTE_UNTER_WINDOWS
//#define GRUNDPLATTE_UNTER_TOS
//******************************************************************************************************************************************************************************************************
//                                                              GLOBALE TEMPLATE-DEFAULT-ARGUMENTE
//******************************************************************************************************************************************************************************************************
typedef wchar_t            typtext;
typedef double             typgeometrie;
typedef float              typoptik;
typedef unsigned short int typakustik;
typedef float              typgrafikmatrix;
typedef unsigned char      typbild;

typedef typtext _tt;
typedef typgeometrie _tg;
typedef typakustik _ta;
typedef typoptik _to;
typedef typbild _tb;
typedef typgrafikmatrix _tm;

//******************************************************************************************************************************************************************************************************
//                                                              GLOBALE KONSTANTEN
//******************************************************************************************************************************************************************************************************
extern typgeometrie nahenull;



/*

template<class T>void SAFERELEASE(T*&o){
                                                                if(o)delete o;
                                                                o=0;
};
template<class T>void SAFE_RELEASE(T*&o){
                                                                if(o)delete o;
                                                                o=0;
};*/
template<class T>void deletesecure(T*&o){
                                                                if(o)delete o;
                                                                o=0;
};


//
//  Basic Types
//

typedef bool bcBool;

typedef __int8 bcInt8;
typedef unsigned __int8 bcUInt8;

typedef __int16 bcInt16;
typedef unsigned __int16 bcUInt16;

typedef __int32 bcInt32;
typedef unsigned __int32 bcUInt32;

typedef __int64 bcInt64;
typedef unsigned __int64 bcUInt64;

typedef float bcFloat32;
typedef double bcFloat64;

typedef bcFloat32 bcScalar;

typedef char     bcChar;
typedef bcUInt16 bcWideChar;




#endif

