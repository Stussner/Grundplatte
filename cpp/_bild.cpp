//******************************************************************************************************************************************************************************************************
//  Projekt      : grundplatte
//  Bibliothek   : grundplatte.lib
//  Modul        : _bild.cpp
//  Datum        : 10.2.2005
//  Beschreibung : 
//******************************************************************************************************************************************************************************************************
#include <_bild.hpp>


//******************************************************************************************************************************************************************************************************
//                                                              B I L D H A R D W A R E
//******************************************************************************************************************************************************************************************************
_bildhardware::_bildhardware(_grafik*g,_bild<_tb>*b):_listenknotenbasis<_bildhardware>(g->listebildhardware()){
																pgrafik=g;
																pbild=b;
																pxscale=1;
																pyscale=1;
}; 
_bildhardware::~_bildhardware(){
};
void _bildhardware::bild(_bild<_tb>*b){
                                                                pbild=b;
};
_bild<_tb>* _bildhardware::bild(){
																return(pbild);
};
_tg _bildhardware::skalierungx()const{
																return(pxscale);
};
_tg _bildhardware::skalierungy()const{
																return(pyscale);
};
void _bildhardware::skalierungx(const _tg x){
																pxscale=x;
};
void _bildhardware::skalierungy(const _tg y){
																pyscale=y;
};
