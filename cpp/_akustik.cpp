//******************************************************************************************************************************************************************************************************
//  Projekt     : grundplatte
//  Bibliothek  : _grundplatte.lib
//  Modul       : _akustik.cpp
//  Datum       : 6.9.2008
//******************************************************************************************************************************************************************************************************
#include <_akustik.hpp>


//******************************************************************************************************************************************************************************************************
//                                                              A K U S T I K 
//******************************************************************************************************************************************************************************************************
_akustik::_akustik(){
                                                                plautstaerketon=1;
                                                                plautstaerketonfluss=1;
                                                                pbeugung=1;
};
_akustik::~_akustik(){
};
void _akustik::tonsammlungfunktion(void (_tonsammlung::*func)(_tg fadeTime),_tg fadeTime){
                                                                _tonsammlung*sit;
                                                                if(plistetonsammlung.anfang(sit))do{
                                                                 (sit->*func)(fadeTime);
                                                                }while(plistetonsammlung.naechstes(sit));
};
_tonsammlung*_akustik::tonsammlung(unsigned int index){
                                                                return((plistetonsammlung[index]));
};
void _akustik::loeschentonlisten(){
																plistetonsammlung.loeschen();
																plistetonfluss.loeschen();
																plisteton.loeschen();
};

_tg _akustik::lautstaerketon()const{
                                                                return(plautstaerketon);
};
void _akustik::lautstaerketon(_tg l){
                                                                if(l<0) l=0;
                                                                if(l>1) l=1;
                                                                plautstaerketon=l;
};
_tg _akustik::lautstaerketonfluss()const{
                                                                return(plautstaerketonfluss);
};
void _akustik::lautstaerketonfluss(_tg l){
                                                                if(l<0) l=0;
                                                                if(l>1) l=1;
                                                                plautstaerketonfluss=l;
};
_tg _akustik::beugung()const{
                                                                return(pbeugung);
};
void _akustik::beugung(_tg b){
                                                                if(b<0) b=0;
                                                                if(b>1) b=1;
                                                                pbeugung=b;
};
_listebasis<_ton>*_akustik::listeton(){
                                                                return(&plisteton);
};
_listebasis<_tonfluss>*_akustik::listetonfluss(){
                                                                return(&plistetonfluss);
};
_listebasis<_tonsammlung>*_akustik::listetonsammlung(){
                                                                return(&plistetonsammlung);
};
//--------------------------------------------------------------laufende-------------------------------------------------------------------------------------------------------------
void _akustik::anhalten(_tg fadeTime){
                                                                tonsammlungfunktion(&_tonsammlung::anhalten,fadeTime);    
};
void _akustik::fortsetzen(_tg fadeTime){
                                                                tonsammlungfunktion(&_tonsammlung::fortsetzen,fadeTime);    
};
void _akustik::stoppen(_tg fadeTime){
                                                                tonsammlungfunktion(&_tonsammlung::stoppen,fadeTime);    

};
//******************************************************************************************************************************************************************************************************
//                                                              T O N 
//******************************************************************************************************************************************************************************************************
_ton::_ton(_akustik*a):_listenknotenbasis<_ton>(a->listeton()){
                                                                pakustik=a;
                                                                pbeugung=1;
                                                                plautstaerke=1;
                                                                pschleife=false;
                                                                pidbuffer=0;
};
_ton::~_ton(){
};
_akustik*_ton::akustik(){
                                                                return(pakustik);
};
unsigned int _ton::identifikationbuffer()const{
                                                                return(pidbuffer);
};
void _ton::identifikationbuffer(const unsigned int id){
                                                                pidbuffer=id;
};
bool _ton::schleife() const{
                                                                return(pschleife);
};
void _ton::schleife(const bool loop){
                                                                pschleife=loop;
};
_tg _ton::lautstaerke() const{
                                                                return(plautstaerke);
};
void _ton::lautstaerke(const _tg volume){
                                                                plautstaerke=begrenzen<_tg>(volume,0,1);
};
_tg _ton::beugung() const{
                                                                return(pbeugung);
};
void _ton::beugung(_tg pitch){
                                                                pbeugung=begrenzen<_tg>(pitch,0,1);
};
void _ton::abspielen(){
                                                                pakustik->abspielen(this);
};
void _ton::abspielen(_tg l,_tg b0,_tg b1){
                                                                pakustik->abspielen(this,l,b0,b1);
};
//******************************************************************************************************************************************************************************************************
//                                                              T O N F L U S S
//******************************************************************************************************************************************************************************************************
_tonfluss::_tonfluss(_akustik*a):_listenknotenbasis<_tonfluss>(a->listetonfluss()),_ton(a){
                                                                //pakustik=a;
                                                                _listenknotenbasis<_ton>::aushaengen();
};
_tonfluss::~_tonfluss(){
};
//******************************************************************************************************************************************************************************************************
//                                                              T O N S A M M L U N G
//******************************************************************************************************************************************************************************************************
_tonsammlung::_tonsammlung(_akustik*a,unsigned int numSources):_listenknotenbasis<_tonsammlung>(a->listetonsammlung()){
                                                                pakustik=a;
                                                                panzahlquelle=numSources;
                                                                pfadetopause=false;
                                                                pfadetostop=false;                                                                
};
_tonsammlung::~_tonsammlung(){
};
_akustik*_tonsammlung::akustik(){
                                                                return(pakustik);
};
unsigned int _tonsammlung::anzahlquelle() const{
                                                                return(panzahlquelle);
};
unsigned int _tonsammlung::quelle(unsigned int i) const{
                                                                if(i<0)i=0;
                                                                if(i>=panzahlquelle) i=panzahlquelle-1;
                                                                return(pquelle[i]);
                                                                
};
unsigned int*_tonsammlung::quelle(){
                                                                return(pquelle);
};
_interpolator<_tg>*_tonsammlung::interpolator(){
                                                                return(&pinterpolator);
};
void _tonsammlung::ausblendenanhalten(const bool b){
                                                                pfadetopause=b;
};
bool _tonsammlung::ausblendenanhalten()const{
                                                                return(pfadetopause);
};
void _tonsammlung::ausblendenstoppen(const bool b){
                                                                pfadetostop=b;
};
bool _tonsammlung::ausblendenstoppen()const{
                                                                return(pfadetostop);
};
