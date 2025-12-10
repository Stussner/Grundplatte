//******************************************************************************************************************************************************************************************************
//  Project     : grundplatte
//  Library     : _grundplatte.lib
//  Module      : _weltmaterial.hpp
//  Date        : 14.11.2006
//  Description : konzepte zur physikalische Repräsentation
//******************************************************************************************************************************************************************************************************
#ifndef _weltmaterial_included
#define _weltmaterial_included

//*********************************************************************************************************************************************************************************
//                                                                P R E D E K L A R A T I O N
//*********************************************************************************************************************************************************************************
template<class _tg>class _oberflaeche;
template<class _tg>class _material;


#include <_global.hpp>
#include <_editionwin.hpp>
#include <_datei.hpp>
//*********************************************************************************************************************************************************************************
//                                                                Z Y K L I S C H E
//*********************************************************************************************************************************************************************************



//*********************************************************************************************************************************************************************************
//                                                                O B E R F L A E C H E
//*********************************************************************************************************************************************************************************
template <class _tg> class _oberflaeche:public virtual _editierbar,public _basis::_speicherbarargument<_oberflaeche<_tg> >{
        public:
                _oberflaeche();
                _oberflaeche(const _tg,const _tg,const _tg);
                virtual ~_oberflaeche();
                void kopieren(_oberflaeche<_tg>*);
                void haftreibung(const _tg);
                void rollreibung(const _tg);
                void gleitreibung(const _tg);
                _tg haftreibung()const;
                _tg rollreibung()const;
                _tg gleitreibung()const;
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_oberflaeche>*);
                void speichern(_speicherbardynamisch<_oberflaeche>*);
                char assoziieren(_speicherbardynamisch<_oberflaeche>*);
                bool ladenoberflaeche(_datei*d);
				void speichernoberflaeche(_datei*d);
                bool assoziieren();
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);                
        private:
                _tg phaftreibung;
                _tg prollreibung;
                _tg pgleitreibung;
                
                                
};
template <class _tg> _oberflaeche<_tg>::_oberflaeche(){
                                                                phaftreibung=0.97;
                                                                prollreibung=0.99;
                                                                pgleitreibung=0.95;
};
template <class _tg> _oberflaeche<_tg>::_oberflaeche(const _tg h,const _tg r,const _tg g){
                                                                phaftreibung=h;
                                                                prollreibung=r;
                                                                pgleitreibung=g;
};
template <class _tg> _oberflaeche<_tg>::~_oberflaeche(){
};
template <class _tg> void _oberflaeche<_tg>::kopieren(_oberflaeche<_tg>*m){
                                                                phaftreibung=m->phaftreibung;
                                                                prollreibung=m->prollreibung;
                                                                pgleitreibung=m->pgleitreibung;
};
template <class _tg> void _oberflaeche<_tg>::haftreibung(const _tg r){
                                                                phaftreibung=r;
};
template <class _tg> void _oberflaeche<_tg>::rollreibung(const _tg r){
                                                                prollreibung=r;
};
template <class _tg> void _oberflaeche<_tg>::gleitreibung(const _tg r){
                                                                pgleitreibung=r;
};
template <class _tg> _tg _oberflaeche<_tg>::haftreibung()const{
                                                                return(phaftreibung);
};
template <class _tg> _tg _oberflaeche<_tg>::rollreibung()const{
                                                                return(prollreibung);
};
template <class _tg> _tg _oberflaeche<_tg>::gleitreibung()const{
                                                                return(pgleitreibung);
};
template <class _tg> char _oberflaeche<_tg>::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_oberflaeche<_tg> >*sd){
                                                                char r=1;
                                                                r^=sd->ladenbeginn(fn);
                                                                r^=sd->ladenverschachtelung(fn);
                                                                r^=sd->ladenwert(phaftreibung);
                                                                r^=sd->ladenwert(prollreibung);
                                                                r^=sd->ladenwert(pgleitreibung);
                                                                sd->ladenende();
                                                                return(r);

};
template <class _tg> void _oberflaeche<_tg>::speichern(_speicherbardynamisch<_oberflaeche<_tg> >*sd){
                                                                sd->speichernbeginnblock();
                                                                sd->speichernverschachtelung();    
                                                                sd->speichernwert(phaftreibung);
                                                                sd->speichernwert(prollreibung);
                                                                sd->speichernwert(pgleitreibung);
                                                                sd->speichernendeblock();
};
template <class _tg> char _oberflaeche<_tg>::assoziieren(_speicherbardynamisch<_oberflaeche<_tg> >*sd){
                                                                sd->assoziierenverschachtelung();
                                                                return(1);
};
template <class _tg> bool _oberflaeche<_tg>::ladenoberflaeche(_datei*d){
																d->laden(phaftreibung);
																d->laden(prollreibung);
																d->laden(pgleitreibung);
																return(true);
};
template <class _tg> void _oberflaeche<_tg>::speichernoberflaeche(_datei*d){
																d->speichern(phaftreibung);
																d->speichern(prollreibung);
																d->speichern(pgleitreibung);
};

template <class _tg> void _oberflaeche<_tg>::einhaengendialog(_dynamischerdialog*d){
                                                                d->addierensektion(L"Physikalische Oberfläche");
                                                                d->einhaengen(L"Physikalische Oberfläche",L"Haftreibung [Anteil]", phaftreibung);
                                                                d->einhaengen(L"Physikalische Oberfläche",L"Rollreibung [Anteil]", prollreibung);
                                                                d->einhaengen(L"Physikalische Oberfläche",L"Gleitreibung [Anteil]",pgleitreibung);
                                
};
template <class _tg> void _oberflaeche<_tg>::auslesendialog(_dynamischerdialog*d){
                                                                d->auslesen(L"Physikalische Oberfläche",L"Haftreibung [Anteil]", phaftreibung);
                                                                d->auslesen(L"Physikalische Oberfläche",L"Rollreibung [Anteil]", prollreibung);
                                                                d->auslesen(L"Physikalische Oberfläche",L"Gleitreibung [Anteil]",pgleitreibung);
};
//*********************************************************************************************************************************************************************************
//                                                                M A T E R I A L 
//*********************************************************************************************************************************************************************************
template <class _tg> class _material:public virtual _editierbar,public _basis::_speicherbarargument<_material<_tg> >{
        public:
                _material();
                _material(const _tg,const _tg,const _tg);
                virtual ~_material();
                void kopieren(_material<_tg>*);
                void viskositaet(const _tg);
                void elastizitaet(const _tg);
                void masse(const _tg);
                _tg viskositaet()const;
                _tg elastizitaet()const;
                _tg masse()const;
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_material>*);
                void speichern(_speicherbardynamisch<_material>*);
                char assoziieren(_speicherbardynamisch<_material>*);
                bool ladenmaterial(_datei*d);
				void speichernmaterial(_datei*d);
                //editierbar
                void einhaengendialog(_dynamischerdialog*);
                void auslesendialog(_dynamischerdialog*);                
                
        private:
                _tg pviskositaet;
                _tg pelastizitaet;
                _tg pmasse;
                
                                
};
template <class _tg> _material<_tg>::_material(){
                                                                pviskositaet=0.99;
                                                                pelastizitaet=0.99;
                                                                pmasse=1;
};
template <class _tg> _material<_tg>::_material(const _tg v,const _tg e,const _tg m){
                                                                pviskositaet=v;
                                                                pelastizitaet=e;
                                                                pmasse=m;
};
template <class _tg> _material<_tg>::~_material(){
};
template <class _tg> void _material<_tg>::kopieren(_material<_tg>*m){
                                                                pviskositaet=m->pviskositaet;
                                                                pelastizitaet=m->pelastizitaet;
                                                                pmasse=m->pmasse;
};
template <class _tg> void _material<_tg>::viskositaet(const _tg v){
                                                                pviskositaet=v;
};
template <class _tg> void _material<_tg>::elastizitaet(const _tg e){
                                                                pelastizitaet=e;
};
template <class _tg> void _material<_tg>::masse(const _tg m){
                                                                pmasse=m;
};
template <class _tg> _tg _material<_tg>::viskositaet()const{
                                                                return(pviskositaet);
};
template <class _tg> _tg _material<_tg>::elastizitaet()const{
                                                                return(pelastizitaet);
};
template <class _tg> _tg _material<_tg>::masse()const{
                                                                return(pmasse);
};
template <class _tg> char _material<_tg>::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_material<_tg> >*sd){
                                                                char r=1;
                                                                r^=sd->ladenbeginn(fn);
                                                                r^=sd->ladenverschachtelung(fn);
                                                                r^=sd->ladenwert(pviskositaet);
                                                                r^=sd->ladenwert(pelastizitaet);
                                                                r^=sd->ladenwert(pmasse);
                                                                sd->ladenende();
                                                                return(r);

};
template <class _tg> void _material<_tg>::speichern(_speicherbardynamisch<_material<_tg> >*sd){
                                                                sd->speichernbeginnblock();
                                                                sd->speichernverschachtelung();    
                                                                sd->speichernwert(pviskositaet);
                                                                sd->speichernwert(pelastizitaet);
                                                                sd->speichernwert(pmasse);
                                                                sd->speichernendeblock();
};
template <class _tg> char _material<_tg>::assoziieren(_speicherbardynamisch<_material<_tg> >*sd){
                                                                sd->assoziierenverschachtelung();
                                                                return(1);
};
template <class _tg> bool _material<_tg>::ladenmaterial(_datei*d){
																d->laden(pviskositaet);
																d->laden(pelastizitaet);
																d->laden(pmasse);
																return(true);
};
template <class _tg> void _material<_tg>::speichernmaterial(_datei*d){
																d->speichern(pviskositaet);
																d->speichern(pelastizitaet);
																d->speichern(pmasse);
};
template <class _tg> void _material<_tg>::einhaengendialog(_dynamischerdialog*d){
                                                                d->addierensektion(L"Physikalisches Material");
                                                                d->einhaengen(L"Physikalisches Material",L"Viskosität [Anteil]", pviskositaet);
                                                                d->einhaengen(L"Physikalisches Material",L"Elastizität [Anteil]", pelastizitaet);
                                                                d->einhaengen(L"Physikalisches Material",L"Masse",pmasse);
                                
};
template <class _tg> void _material<_tg>::auslesendialog(_dynamischerdialog*d){
                                                                d->auslesen(L"Physikalisches Material",L"Viskosität [Anteil]", pviskositaet);
                                                                d->auslesen(L"Physikalisches Material",L"Elastizität [Anteil]", pelastizitaet);
                                                                d->auslesen(L"Physikalisches Material",L"Masse",pmasse);
};
#endif
