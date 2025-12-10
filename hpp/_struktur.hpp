//******************************************************************************************************************************************************************************************************
//  Project     : grundplatte
//  Library     : _grundplatte.lib
//  Module      : _struktur.hpp
//  Date        : 18.12.2002
//  Description : 
//******************************************************************************************************************************************************************************************************
#ifndef _listsh_included
#define _listsh_included

//******************************************************************************************************************************************************************************************************
//                                                              F O R W A R D S 
//******************************************************************************************************************************************************************************************************

template<class T>                 class _listebasis;
template<class T>                 class _listebasissortierung;
template<class T>                 class _listenknotenbasis;
template<class T,class S>         class _listenknotenbasissortiert;
template<class T>                 class _listelistenknotenbasis;
template<class T,class N>         class _listlistbasisnodeheterogen;
//class _verbinderliste;

template<class T0,class T1>class _verbinder;
template<class T>class _liste;
template<class T>class _listenknoten;
template<class T,class S>class _listesortiert;
template<class T,class S>class _listenknotensortiert;

//--------------------------------------------------------------
//namespace _basis{
template<class T>class _baumbasis;
template<class T>class _baumknotenbasis;
//};

template<class T,class _tg> class _baumoctal;
template<class T,class _tg> class _baumoctalwuerfel;
template<class T,class _tg> class _baumoctalobjekt;
//alt 
template<class t>class _hashscheibe;
template<class t>class _hashscheibeknoten;
template<class t>class _baumbinaer;
template<class t>class _baumbinaerknoten;
//------------ alt aber verwendbar --------------------
template<class a> void einhaengen(a*,a*&);
template<class a> void insertsorted(a*,a*&);
template<class T> void loeschen(T&);
template<class a,class b> void loeschen(a*,b&);
template<class a,class b> void aushaengen(a*,b&);
template<class a> void flag_ring(a*,int);
template<class a,class b> a*swapprev(a*,b&);
template<class a,class b> a*swapnext(a*,b&);
template<class a,class b> b*iterated(a,b*);
template<class a> int indiced(a*,a*);
template<class ring> void clear_ring(ring*&);
template<class T>void kill(T*&);
template<class ring> void unite_ring(ring*,ring*);
template<class ring> void invert_ring(ring*&);
template<class ring> void isolate_ring(ring*,int);


#define iterieren(it,code) if(anfang(it))do{code;}while(naechstes(it))
#define iterierenliste(list,it,code) if((list)->anfang(it))do{code;}while((list)->naechstes(it))

//namespace _basis{
//****************************************************************************************************************************************************************************
//                                                              B A S E :: L I S T
//****************************************************************************************************************************************************************************
template<class T>class _listebasis{
         public:
                 _listebasis();
                 virtual ~_listebasis();
                 inline T*operator[](int)const;
                 T*index(int)const;
                 unsigned int anzahl() const;
                 inline T*erstes();
                 inline T*letztes();
                 inline void erstes(_listenknotenbasis<T>*);
                 inline void rotierenvorheriges();
                 inline void rotierennaechstes();
                 inline bool anfang(T*&)const;
                 inline bool anfang(_listenknotenbasis<T>*&)const;
                 inline bool ende(T*&)const;
                 inline bool ende(_listenknotenbasis<T>*&)const;
                 inline bool naechstes(T*&)const;
                 inline bool naechstes(_listenknotenbasis<T>*&)const;
                 inline bool vorheriges(T*&)const;
                 inline bool vorheriges(_listenknotenbasis<T>*&)const;

                 //inline void einhaengen(T*);
                 //inline void einhaengenerstes(T*);
                 void vereinigen(_listebasis<T>*);
                 void invertieren();
                 void loeschen();
                 void loeschenmarkiert();
         private:
                 _listenknotenbasis<T>*tfirst;
};
template<class T>_listebasis<T>::_listebasis(){
                                                                tfirst=0;
};
template<class T>_listebasis<T>::~_listebasis(){
                                                                loeschen();
};
template<class T>T* _listebasis<T>::operator[](int i)const{
                                                                return(index(i));
};
template<class T>T* _listebasis<T>::index(int i)const{
                                                                T*it;
                                                                int n;
                                                                //-----------
                                                                if(anfang(it)){
                                                                 for(n=0;n<i;n++) it=it->_listenknotenbasis<T>::naechstes();
                                                                 return(it);
                                                                }else{
                                                                 return(0);
                                                                };
};
template<class T>unsigned int _listebasis<T>::anzahl() const{
                                                                int i;
                                                                _listenknotenbasis<T>*it;
                                                                //-----
                                                                i=0;
                                                                if(anfang(it))do{
                                                                 it->anzahl(i);
                                                                }while(naechstes(it));
                                                                return(i);
};
template<class T>void _listebasis<T>::erstes(_listenknotenbasis<T>*l){
                                                                //firt-zeiger setzen
                                                                tfirst=l;
};
template<class T>void _listebasis<T>::rotierenvorheriges(){
                                                                //erstes-zeiger vorheriges-rotation
                                                                tfirst=tfirst->vorheriges();
};
template<class T>void _listebasis<T>::rotierennaechstes(){
                                                                //erstes-zeiger vorheriges-rotation
                                                                tfirst=tfirst->naechstes();
};
template<class T>T* _listebasis<T>::erstes(){
                                                                //erstes-zeiger zurückgeben und in den abgeleiteten Typ T konvertieren
                                                                return((T*)tfirst);
};
template<class T>T* _listebasis<T>::letztes(){
                                                                //letztes objekt zurückgeben und in den abgeleiteten Typ T konvertieren
                                                                if(tfirst){
                                                                 return((T*)tfirst->vorheriges());
                                                                }else{
                                                                 return(0);
                                                                };
};
template<class T>bool _listebasis<T>::anfang(T*&eit)const{
                                                                //externe iterationsinitialisierung
                                                                eit=0;
                                                                if(tfirst){
                                                                 eit=(T*)tfirst;
                                                                 return(true);
                                                                };
                                                                return(false);
};

template<class T>bool _listebasis<T>::anfang(_listenknotenbasis<T>*&eit)const{
                                                                //iterationsinitialisierung
                                                                eit=0;
                                                                if(tfirst){
                                                                 eit=tfirst;
                                                                 return(true);
                                                                };
                                                                return(false);
};
template<class T>bool _listebasis<T>::naechstes(T*&eit)const{
                                                                //naechstes-iterationsschritt
                                                                eit=eit->_listenknotenbasis<T>::naechstes();
                                                                if(eit==tfirst) return(false);
                                                                return(true);
};

template<class T>bool _listebasis<T>::naechstes(_listenknotenbasis<T>*&eit)const{
                                                                //naechstes-iterationsschritt
                                                                eit=eit->_listenknotenbasis<T>::naechstes();
                                                                if(eit==tfirst) return(false);
                                                                return(true);
};

template<class T>bool _listebasis<T>::ende(T*&eit)const{
                                                                //externe iterationsinitialisierung
                                                                eit=0;
                                                                if(tfirst){
                                                                 eit=(T*)tfirst->vorheriges();
                                                                 return(true);
                                                                };
                                                                return(false);
};
template<class T>bool _listebasis<T>::ende(_listenknotenbasis<T>*&eit)const{
                                                                //iterationsinitialisierung
                                                                eit=0;
                                                                if(tfirst){
                                                                 eit=tfirst->vorheriges();
                                                                 return(true);
                                                                };
                                                                return(false);
};
template<class T>bool _listebasis<T>::vorheriges(T*&eit)const{
                                                                //vorheriges-iterationsschritt
                                                                eit=eit->_listenknotenbasis<T>::vorheriges();
                                                                if(eit==tfirst->vorheriges()) return(false);
                                                                return(true);
};

template<class T>bool _listebasis<T>::vorheriges(_listenknotenbasis<T>*&eit)const{
                                                                //vorheriges-iterationsschritt
                                                                eit=eit->_listenknotenbasis<T>::vorheriges();
                                                                if(eit==tfirst->vorheriges()) return(false);
                                                                return(true);
};
template<class T>void _listebasis<T>::loeschen(){
                                                                //eine liste löscht mit loeschen() ihre listnodes
                                                               /* _listenknotenbasis<T>*act;
                                                                _listenknotenbasis<T>*del;
                                                                //--------------------
                                                                if(tfirst){
                                                                 act=tfirst->vorheriges();
                                                                 if(act!=tfirst)do{
                                                                  del=act;
                                                                  act=act->vorheriges();
                                                                  delete del;
                                                                 }while(act!=tfirst);
                                                                 delete act;
                                                                };
                                                                tfirst=0;*/

                                                                //eine liste löscht mit loeschen() ihre listnodes
                                                                _listenknotenbasis<T>*act;
                                                                _listenknotenbasis<T>*del;
                                                                //--------------------
                                                                if(tfirst){
                                                                 act=tfirst->naechstes();
                                                                 if(act!=tfirst)do{
                                                                  del=act;
                                                                  act=act->naechstes();
                                                                  delete del;
                                                                 }while(act!=tfirst);
                                                                 delete act;
                                                                };
                                                                tfirst=0;
};
template<class T>void _listebasis<T>::loeschenmarkiert(){
                                                                _listenknotenbasis<T>*wit;
                                                                _listenknotenbasis<T>*wn;
                                                                //---------------
                                                                /*
                                                                
                                                                wit=tfirst;
                                                                if(wit)do{
                                                                 if(wit->loeschmarkierung()){
                                                                  wn=wit->naechstes();
                                                                  delete wit;
                                                                  wit=wn;
                                                                  if(tfirst==0) wit=0;
                                                                 }else wit=wit->naechstes();
                                                                }while(wit!=tfirst);
                                                                
                                                                
                                                                
                                                                if(tfirst){
                                                                 if(tfirst->loeschmarkierung()){
                                                                  delete tfirst;
                                                                  //tfirst=0;
                                                                 };
                                                                };
                                                                */

                                                                wit=tfirst;
                                                                if(wit)do{
                                                                 if(wit->loeschmarkierung()){
                                                                  wn=wit->vorheriges();
                                                                  delete wit;
                                                                  wit=wn;
                                                                  if(tfirst==0) wit=0;
                                                                 }else wit=wit->vorheriges();
                                                                }while(wit!=tfirst);
                                                                
                                                                
                                                                
                                                                if(tfirst){
                                                                 if(tfirst->loeschmarkierung()){
                                                                  delete tfirst;
                                                                  //tfirst=0;
                                                                 };
                                                                };

};
template<class T>void _listebasis<T>::vereinigen(_listebasis<T>*o){
                                                                _listenknotenbasis<T>*r0;
                                                                _listenknotenbasis<T>*r1;
                                                                _listenknotenbasis<T>*r0p;
                                                                _listenknotenbasis<T>*it;
                                                                //-----------------
                                                                if(o->tfirst!=0){
                                                                 if(tfirst==0){
                                                                  tfirst=o->tfirst;
                                                                 }else{
                                                                  //--------------- verbiegung vornehmen
                                                                  r0=tfirst;
                                                                  r1=o->tfirst;
                                                                  r0p=r0->pprev;//vorheriges();
                                                                  r0->pprev->pnext=r1;
                                                                  r0->pprev=r1->pprev;
                                                                  r1->pprev->pnext=r0;
                                                                  r1->pprev=r0p;
                                                                 };
                                                                 //---------------- alle listenknoten mit this verwalten 
                                                                 if(anfang(it))do{
                                                                  it->llist=this;
                                                                 }while(naechstes(it));
                                                                 //---------------- argument isolieren , listenknotenassoziation aushaengen
                                                                 o->tfirst=0;
                                                                };
                                                                
};
template<class T>void _listebasis<T>::invertieren(){
                                                                _listenknotenbasis<T>*h;
                                                                _listenknotenbasis<T>*it;
                                                                //-------------
                                                                it=tfirst;
                                                                if(it){
                                                                 do{
                                                                  h=it->naechstes();
                                                                  it->tauschen();
                                                                  it=h;
                                                                 }while(it!=tfirst);
                                                                 tfirst=tfirst->naechstes();
                                                                };
};
/*
template<class T>void _listebasis<T>::einhaengen(T*o){
                                                                o->_listenknotenbasis<T>::einhaengen(this);
};
template<class T>void _listebasis<T>::einhaengenerstes(T*o){
                                                                o->_listenknotenbasis<T>::einhaengenerstes(this);
};*/
//****************************************************************************************************************************************************************************
//                                                              B A S I S :: L I S T E S O R T I E R U N G
//****************************************************************************************************************************************************************************
template<class T>class _listebasissortierung:public _listebasis<T>{
         public:
                 _listebasissortierung();
                 virtual ~_listebasissortierung();
                 void sortieren();
		 private:
                 void sortieren(int links,int rechts);
				 int teilen(int links,int rechts);
				 void tauschen(int x,int y);
				 T**feld;

};                 
template<class T>_listebasissortierung<T>::_listebasissortierung(){
																feld=0;
};
template<class T>_listebasissortierung<T>::~_listebasissortierung(){
};
template<class T>void _listebasissortierung<T>::sortieren(){
																int anz = this->anzahl();
																if(anz>1){
																 feld=new T*[anz];
																 T*it;
																 int i=0;
																 if(anfang(it))do{
															      feld[i++]=it;
																 }while(naechstes(it));

																 sortieren(0,anz-1);
																 for(int n=0;n<i;n++) feld[n]->_listenknotenbasis<T>::aushaengen();
																 for(int n=0;n<i;n++) feld[n]->_listenknotenbasis<T>::einhaengen(this);
																 deletesecure(feld);
																};
};
template<class T>void _listebasissortierung<T>::sortieren(int links,int rechts){
																if(links<rechts){
																 int teiler=teilen(links,rechts);
																 sortieren(links, teiler-1);
																 sortieren(teiler+1, rechts);
																};
};
template<class T>int _listebasissortierung<T>::teilen(int links,int rechts){
																int i=links;
																// Starte mit j links vom Pivotelement
																int j=rechts-1;
															    T*pivot=feld[rechts];
																do{
																 // Suche von links ein Element, welches größer als das Pivotelement ist
																 while((feld[i]->vergleichen(pivot)==false)&&(i<rechts)) i++;
														         // Suche von rechts ein Element, welches kleiner als das Pivotelement ist
														         while((feld[j]->vergleichen(pivot)==true)&&(j>links)) j--;
																 if(i<j) tauschen(i,j);
																}while(i<j); // solange i an j nicht vorbeigelaufen ist 
																  //Tausche Pivotelement (daten[rechts]) mit neuer endgültiger Position (daten[i])
																if(feld[i]->vergleichen(pivot)==true) tauschen(i,rechts);
																// gib die Position des Pivotelements zurück
																return(i);
};
template<class T>void _listebasissortierung<T>::tauschen(int x,int y){
																T*h=feld[x];
																feld[x]=feld[y];
																feld[y]=h;
};
//******************************************************************************************************************************************************************************************************
//                                                              B A S I S :: L I S T E N K N O T E N
//******************************************************************************************************************************************************************************************************
template<class T>class _listenknotenbasis{
    friend class _listebasis<T>;
        public:
                _listenknotenbasis();
                _listenknotenbasis(_listebasis<T>*,bool erstes=false);
                virtual ~_listenknotenbasis();
               // inline void liste(_listebasis<T>*);
                inline T*vorheriges();
                inline T*naechstes();
                inline void vorheriges(_listenknotenbasis<T>*);
                inline void naechstes(_listenknotenbasis<T>*);
                inline _listebasis<T>*liste()const;
                void anzahl(int&);
                void einhaengen(_listebasis<T>*);
                void einhaengenerstes(_listebasis<T>*);
                void einhaengenvor(_listebasis<T>*,_listenknotenbasis<T>*);
                void einhaengennach(_listebasis<T>*,_listenknotenbasis<T>*);
                void loeschmarkierung(bool);
                bool loeschmarkierung() const;
                void tauschen();
        protected://private:
                //void einhaengen(_listebasis<T>*);
                //void einhaengenerstes(_listebasis<T>*);
        public:                
                void aushaengen();
        private:
                _listenknotenbasis<T>*pprev;
                _listenknotenbasis<T>*pnext;
                _listebasis<T>*llist;
                bool pdestruct;
};
template<class T>_listenknotenbasis<T>::_listenknotenbasis(){
                                                                llist=0;
                                                                pdestruct=false;
                                                                pprev=this;
                                                                pnext=this;
};
template<class T>_listenknotenbasis<T>::_listenknotenbasis(_listebasis<T>*l,bool erstes){
                                                                llist=0;
                                                                pdestruct=false;
                                                                pprev=this;
                                                                pnext=this;
                                                                if (erstes==false) einhaengen(l); else einhaengenerstes(l);
};
/*
template<class T>void _listenknotenbasis<T>::liste(_listebasis<T>*l){
                                                                llist=l;
};
*/
template<class T>_listenknotenbasis<T>::~_listenknotenbasis(){
                                                                aushaengen();
};
template<class T> T * _listenknotenbasis<T>::vorheriges(){
                                                                return((T*)pprev);
};
template<class T> T * _listenknotenbasis<T>::naechstes(){
                                                                return((T*)pnext);
};
template<class T> void _listenknotenbasis<T>::naechstes(_listenknotenbasis<T>*pn){
                                                                if(pn!=0) pnext=pn;
};
template<class T> void _listenknotenbasis<T>::vorheriges(_listenknotenbasis<T>*pp){
                                                                if(pp!=0) pprev=pp;
};
template<class T> void _listenknotenbasis<T>::tauschen(){
                                                                _listenknotenbasis<T>*h;
                                                                //-----------------
                                                                h=pnext;
                                                                pnext=pprev;
                                                                pprev=h;
};
template<class T> _listebasis<T> * _listenknotenbasis<T>::liste()const{
                                                                return(llist);
};
template<class T>void _listenknotenbasis<T>::anzahl(int&i){
                                                                i++;
};

template<class T>void _listenknotenbasis<T>::einhaengen(_listebasis<T>*l){//als letzes
                                                                _listenknotenbasis<T>*it;
                                                                //---------------
                                                                aushaengen();
                                                                llist=l;
                                                                if(llist){
                                                                 if(llist->erstes()==0) {
                                                                  pprev=pnext=this;
                                                                  llist->erstes(this);
                                                                 }else{
                                                                  it=llist->erstes();
                                                                  pnext=it;
                                                                  pprev=it->pprev;
                                                                  it->pprev->pnext=this;
                                                                  it->pprev=this;
                                                                 };
                                                                };
};
template<class T>void _listenknotenbasis<T>::einhaengenerstes(_listebasis<T>*l){
                                                                _listenknotenbasis<T>*it;
                                                                //---------------
                                                                aushaengen();
                                                                llist=l;
                                                                if(llist){
                                                                 if(llist->erstes()==0) {
                                                                  pprev=pnext=this;
                                                                  llist->erstes(this);
                                                                 }else{
                                                                  it=llist->erstes();
                                                                  pnext=it;
                                                                  pprev=it->pprev;
                                                                  it->pprev->pnext=this;
                                                                  it->pprev=this;
                                                                  llist->erstes(this);
                                                                 };
                                                                };
};
template<class T>void _listenknotenbasis<T>::einhaengenvor(_listebasis<T>*l,_listenknotenbasis<T>*it){
                                                                aushaengen();
                                                                llist=l;
                                                                if(llist){
                                                                 if(llist->erstes()==0) {
                                                                  pprev=pnext=this;
                                                                  llist->erstes(this);
                                                                 }else{
                                                                  pnext=it;
                                                                  pprev=it->pprev;
                                                                  it->pprev->pnext=this;
                                                                  it->pprev=this;
                                                                  if(it==llist->erstes()) llist->erstes(this);
                                                                 };
                                                                };
};
template<class T>void _listenknotenbasis<T>::einhaengennach(_listebasis<T>*l,_listenknotenbasis<T>*it){
                                                                aushaengen();
                                                                llist=l;
                                                                if(llist){
                                                                 if(llist->erstes()==0) {
                                                                  pprev=pnext=this;
                                                                  llist->erstes(this);
                                                                 }else{
                                                                  pprev=it;
                                                                  pnext=it->pnext;
                                                                  it->pnext->pprev=this;
                                                                  it->pnext=this;
                                                                 };
                                                                };
};

template<class T>void _listenknotenbasis<T>::aushaengen(){
                                                                _listenknotenbasis<T>*f;
                                                                //------------------
                                                                if(llist){
                                                                 f=llist->erstes();
                                                                 if(f!=0){
                                                                  if(f->pnext==f) llist->erstes(0);
                                                                  else{
                                                                   if(f==this) llist->rotierennaechstes();
                                                                   pprev->pnext=pnext;
                                                                   pnext->pprev=pprev;
                                                                  };
                                                                 };
                                                                 pprev=0;
                                                                 pnext=0;
                                                                 llist=0;
                                                                };
};
template<class T>void _listenknotenbasis<T>::loeschmarkierung(bool b){
                                                                pdestruct=b;
};
template<class T>bool _listenknotenbasis<T>::loeschmarkierung() const{
                                                                return(pdestruct);
};

//******************************************************************************************************************************************************************************************************
//                                                              B A S E : : L I S T N O D E S O R T 
//******************************************************************************************************************************************************************************************************
template<class T,class S> class _listenknotenbasissortiert:public _listenknotenbasis<T>{
        public:
                _listenknotenbasissortiert(S);
                _listenknotenbasissortiert(_listebasis<T>*,S);
                virtual ~_listenknotenbasissortiert();
                inline S kriterium() const;
                void resort(S);
                void einhaengen(_listebasis<T>*);
        private:                
                S pcriterium;
};
template<class T,class S> _listenknotenbasissortiert<T,S>::_listenknotenbasissortiert(S c):_listenknotenbasis<T>(){
                                                                pcriterium=c;
};
template<class T,class S> _listenknotenbasissortiert<T,S>::_listenknotenbasissortiert(_listebasis<T>*l,S c):_listenknotenbasis<T>(){
                                                                pcriterium=c;
                                                                //liste(l);
                                                                einhaengen(l);
};
template<class T,class S> _listenknotenbasissortiert<T,S>::~_listenknotenbasissortiert(){
};
template<class T,class S> S _listenknotenbasissortiert<T,S>::kriterium() const{
                                                                return(pcriterium);
};
template<class T,class S>void _listenknotenbasissortiert<T,S>::resort(S p){
                                                                pcriterium=p;
                                                                _listebasis<T>*l=this->liste();
                                                                this->aushaengen();
                                                                einhaengen(l);
};                                                                
template<class T,class S>void _listenknotenbasissortiert<T,S>::einhaengen(_listebasis<T>*l){
                                                                _listenknotenbasissortiert<T,S>*it;
                                                                _listenknotenbasissortiert<T,S>*lf;
                                                                char r=0;
                                                                //-------------------
                                                                if(l){
                                                                 lf=dynamic_cast<_listenknotenbasissortiert<T,S>*>(l->erstes());
                                                                 if(lf==0) {
                                                                  _listenknotenbasis<T>::einhaengen(l); 
                                                                 }else{
                                                                  it=lf;
                                                                  do{
                                                                   //if(x->alpha<it->alpha)r=1;   
                                                                   if(kriterium()<it->kriterium()) r=1;
                                                                   if(r==0) it=it->naechstes();   
                                                                  }while((it!=lf)&&(r==0));
                                                                  l->erstes(it);
                                                                  _listenknotenbasis<T>::einhaengen(l);
                                                                  l->erstes(lf);
                                                                  //einhaengen(x,it);
                                                                  //if(lf->alpha>erstes->vorheriges->alpha) {
                                                                  if(lf->kriterium()>lf->vorheriges()->kriterium()){
                                                                   l->rotierenvorheriges();//erstes=erstes->vorheriges;
                                                                  };
                                                                 };
                                                                };
};

//****************************************************************************************************************************************************************************
//                                                              B A S E :: L I S T L I S T N O D E
//****************************************************************************************************************************************************************************
 template<class T>class _listelistenknotenbasis:public _listenknotenbasis<T>,public _listebasis<T>{
	   public:
        //using _listenknotenbasis<T>::einhaengen;
        //using _listebasis<T>::einhaengen;
      //        using _listenknoten<T>::anzahl;
      //  using _liste<T>::anzahl;
        public:
                _listelistenknotenbasis();
                _listelistenknotenbasis(_listebasis<T>*);
                inline bool naechstes();
                inline bool naechstes(T*&);
                inline bool vorheriges();
                inline bool vorheriges(T*&);
                inline T*naechsterknoten();
                inline T*vorherigerknoten();
                void anzahl(int&);

 };
 template<class T>_listelistenknotenbasis<T>::_listelistenknotenbasis():_listenknotenbasis<T>(){

 };
 template<class T>_listelistenknotenbasis<T>::_listelistenknotenbasis(_listebasis<T>*l):_listenknotenbasis<T>(l){
 };
 template<class T>bool _listelistenknotenbasis<T>::naechstes(){
                                                                return(_listebasis<T>::naechstes());
 };
 template<class T>bool _listelistenknotenbasis<T>::naechstes(T*&eit){
                                                                return(_listebasis<T>::naechstes(eit));
 };
 template<class T>bool _listelistenknotenbasis<T>::vorheriges(){
                                                                return(_listebasis<T>::vorheriges());
 };
 template<class T>bool _listelistenknotenbasis<T>::vorheriges(T*&eit){
                                                                return(_listebasis<T>::vorheriges(eit));
 };
 template<class T>T* _listelistenknotenbasis<T>::naechsterknoten(){
                                                                return(_listenknotenbasis<T>::naechstes());
 };
 template<class T>T* _listelistenknotenbasis<T>::vorherigerknoten(){
                                                                return(_listenknotenbasis<T>::vorheriges());
 };
 template<class T>void _listelistenknotenbasis<T>::anzahl(int&i){
                                                                i+=1+_listebasis<T>::anzahl();
 };
//******************************************************************************************************************************************************************************************************
//                                                              B A S E : : L I S T L I S T N O D E H E T E R O G E N 
//******************************************************************************************************************************************************************************************************
 /*template<class T,class N> class _listlistnodeheterogen:public _liste<T>,public _listenknoten<N>{
        public:
                _listlistnodeheterogen();
                _listlistnodeheterogen(_liste<N>*);
                inline bool naechstes();
                inline bool vorheriges();
                inline N*naechsterknoten();
                inline N*vorherigerknoten();
                //inline bool naechsterknoten();
 };
 template<class T,class N>_listlistnodeheterogen<T,N>::_listlistnodeheterogen():_listenknoten<N>(){
 };
 template<class T,class N>_listlistnodeheterogen<T,N>::_listlistnodeheterogen(_liste<N>*l):_listenknoten<N>(l){
 };
 template<class T,class N> bool _listlistnodeheterogen<T,N>::naechstes(){
                                                                return(_liste<T>::naechstes());
 };
 template<class T,class N> bool _listlistnodeheterogen<T,N>::vorheriges(){
                                                                return(_liste<T>::vorheriges());
 };
 template<class T,class N> N* _listlistnodeheterogen<T,N>::naechsterknoten(){
                                                                return(_listenknoten<N>::naechstes());
 };
 template<class T,class N> N* _listlistnodeheterogen<T,N>::vorherigerknoten(){
                                                                return(_listenknoten<N>::vorheriges());
 };*/
//******************************************************************************************************************************************************************************************************
//                                                              B A S E : : C O N N E C T O R L I S T 
//******************************************************************************************************************************************************************************************************
/*class _verbinderliste:public _liste<_verbinder>{
        public:
                _verbinderliste();
                ~_verbinderliste();
};*/
//};//namespace _basis
//****************************************************************************************************************************************************************************
//                                                              V E R B I N D E R
//****************************************************************************************************************************************************************************
template<class T0,class T1> class _verbinder:public _listenknoten<T0>,public _listenknoten<T1>{
        public:
                _verbinder(_liste<T0>*,T0*,_liste<T1>*,T1*);
                virtual ~_verbinder();
};
template<class T0,class T1> _verbinder<T0,T1>::_verbinder(_liste<T0>*l0,T0*o0,_liste<T1>*l1,T1*o1):_listenknoten<T0>(l0,o0),_listenknoten<T1>(l1,o1){};
template<class T0,class T1> _verbinder<T0,T1>::~_verbinder(){};

//********************************************************************************************************************************************************************************************
//                                                              L I S T N O D E
//********************************************************************************************************************************************************************************************
template<class T> class _listenknoten:public _listenknotenbasis<_listenknoten<T> >{
        public:
                _listenknoten(_liste<T>*,T*,bool erstes=false);
                virtual ~_listenknoten();
                unsigned int indexknoten()const;
                inline T*objekt();
                inline void objekt(T*);
                inline void loeschmarkierungobjekt(bool);
                inline bool loeschmarkierungobjekt()const;
        private:
        
                T*obj;
                bool pdestructionobject;
};
template<class T>_listenknoten<T>::_listenknoten(_liste< T >*l,T*o,bool erstes):_listenknotenbasis<_listenknoten<T> >(l,erstes),obj(o){
                                                                pdestructionobject=false;
};
template<class T>_listenknoten<T>::~_listenknoten(){
                                                                if(pdestructionobject){
                                                                 if(obj){
                                                                  delete obj;
                                                                  obj=0;
                                                                 };
                                                                };
};
template<class T> unsigned int _listenknoten<T>::indexknoten()const{
																unsigned int i=0;
																_listenknoten<T>*it;
																if(this->liste()){
																 iterierenliste(this->liste(),it,
																  if(it==this) return(i);
																  i++;
																 );
																};
																return(0);
};
template<class T>T*_listenknoten<T>::objekt(){
                                                                return(obj);
};
template<class T>void _listenknoten<T>::objekt(T*o){
                                                                obj=o;
};
template<class T>void _listenknoten<T>::loeschmarkierungobjekt(bool b){
                                                                this->loeschmarkierung(b);
                                                                pdestructionobject=b;
};
template<class T>bool _listenknoten<T>::loeschmarkierungobjekt() const{
                                                                return(pdestructionobject);
};
//******************************************************************************************************************************************************************************************************
//                                                              L I S T N O D E S O R T 
//******************************************************************************************************************************************************************************************************
template<class T,class S> class _listenknotensortiert:public _listenknotenbasis<_listenknotensortiert<T,S> >{
        public:
                //_listenknotensortiert(S);
                _listenknotensortiert(_listesortiert<T,S>*,T*,S);
                virtual ~_listenknotensortiert();
                inline S kriterium() const;
                void einhaengen(_listesortiert<T,S>*l);
                inline T*objekt() const;
                inline void objekt(T*);

        private:                
                S pcriterium;
                T*obj;

};
/*
template<class T,class S> _listenknotensortiert<T,S>::_listenknotensortiert(S c):_listenknoten<T>(){
                                                                pcriterium=c;
};
*/
template<class T,class S> _listenknotensortiert<T,S>::_listenknotensortiert(_listesortiert<T,S>*l,T*o,S c):_listenknotenbasis<_listenknotensortiert<T,S> >(){
                                                                pcriterium=c;
                                                                einhaengen(l);
                                                                obj=o;
};
template<class T,class S> _listenknotensortiert<T,S>::~_listenknotensortiert(){
};
template<class T,class S> S _listenknotensortiert<T,S>::kriterium() const{
                                                                return(pcriterium);
};
template<class T,class S>void _listenknotensortiert<T,S>::einhaengen(_listesortiert<T,S>*l){
                                                                _listenknotensortiert<T,S>*it;
                                                                _listenknotensortiert<T,S>*lf;
                                                                char r=0;
                                                                //-------------------
                                                                if(l){
                                                                 lf=dynamic_cast<_listenknotensortiert<T,S>*>(l->erstes());
                                                                 if(lf==0) {
                                                                  _listenknotenbasis< ::_listenknotensortiert<T,S> >::einhaengen(l); 
                                                                 }else{
                                                                  it=lf;
                                                                  do{
                                                                   //if(x->alpha<it->alpha)r=1;   
                                                                   if(kriterium()<it->kriterium()) r=1;
                                                                   if(r==0) it=it->naechstes();   
                                                                  }while((it!=lf)&&(r==0));
                                                                  l->erstes(it);
                                                                  _listenknotenbasis< ::_listenknotensortiert<T,S> >::einhaengen(l);
                                                                  l->erstes(lf);
                                                                  //einhaengen(x,it);
                                                                  //if(lf->alpha>erstes->vorheriges->alpha) {
                                                                  if(lf->kriterium()>lf->vorheriges()->kriterium()){
                                                                   l->rotierenvorheriges();//erstes=erstes->vorheriges;
                                                                  };
                                                                 };
                                                                };
};
template<class T,class S>T*_listenknotensortiert<T,S>::objekt() const{
                                                                return(obj);
};
template<class T,class S>void _listenknotensortiert<T,S>::objekt(T*o){
                                                                obj=o;
};

//**********************************************************************************************************************************************************************************************************
//                                                              :: L I S T
//**********************************************************************************************************************************************************************************************************
template<class T>class _liste:public _listebasis<_listenknoten<T> >{
        public:
                inline T*operator[](int i);
                _listenknoten<T>*einhaengen(T*);//einfügen,knoten generieren
                _listenknoten<T>*einhaengenerstes(T*);//einfügen,knoten generieren
                _listenknoten<T>*einhaengenunredundant(T*);
                void aushaengen();//alles aushangen,alle knoten löschen
                char aushaengen(T*);//aushängen knoten löschen
                void loeschen();//alles aushängen,alle knoten löschen, alle objecte löschen
                char loeschen(T*);//aushängen,knoten löschen,objekt löschen
                char suchen(T*,_listenknoten<T>*&);                
                bool suchen(T*);
                void sortieren();
};
//---------------------------------------------------PUBLIC--------------------------------------------------------------------------------------------------------------------------------------
template<class T>_listenknoten<T>*_liste<T>::einhaengen(T*obj){
                                                                return(new _listenknoten<T>(this,obj,false));
};
template<class T>_listenknoten<T>*_liste<T>::einhaengenerstes(T*obj){
                                                                return(new _listenknoten<T>(this,obj,true));
};
template<class T>_listenknoten<T>*_liste<T>::einhaengenunredundant(T*o){
                                                                _listenknoten<T>*x;
                                                                char r;
                                                                //----------------
                                                                r=suchen(o,x);
                                                                if(r==0) return(new _listenknoten<T>(this,o));
                                                                return(x);
};
template<class T>T* _liste<T>::operator[](int i){
                                                                int n;
                                                                _listenknoten<T>*it;
                                                                //------
                                                                if(anfang(it)){
                                                                 for(n=0;n<i;n++) naechstes(it);
                                                                 return(it->objekt());
                                                                }else{
                                                                 return(0);
                                                                };
};
template<class T>void _liste<T>::aushaengen(){
                                                                _listebasis<_listenknoten<T> >::loeschen();
};
template<class T>char _liste<T>::aushaengen(T*o){
                                                                _listenknoten<T>*x;
                                                                //---------------
                                                                while(suchen(o,x)) delete x;
                                                                if(this->erstes()==0) return(0); else return(1);
};
template<class T>void _liste<T>::loeschen(){
                                                                _listenknoten<T>*it;
                                                                if(anfang(it))do{
                                                                 delete it->objekt();
                                                                 it->objekt(0);
                                                                }while(naechstes(it));
                                                                aushaengen();
};
template<class T>char _liste<T>::loeschen(T*o){
                                                                _listenknoten<T>*x;
                                                                //--------------
                                                                while(suchen(o,x)) delete x;
                                                                delete o;
                                                                if(this->erstes()==0) return(0); else return(1);
};
template<class T>char _liste<T>::suchen(T*o,_listenknoten<T>*&x){
                                                                _listenknoten<T>*tit;
                                                                char r;
                                                                //---------------
                                                                r=0;
                                                                x=0;

                                                                if(anfang(tit))do{
                                                                 if(o==tit->objekt()){
                                                                  x=tit;
                                                                  r=1;
                                                                 };
                                                                }while((naechstes(tit))&&(r==0));
                                                                return(r);
};
template<class T>bool _liste<T>::suchen(T*o){
                                                                _listenknoten<T>*tit;
                                                                //---------------
                                                                if(anfang(tit))do{
                                                                 if(o==tit->objekt()) return(true);
                                                                }while(naechstes(tit));
                                                                return(false);
};
//**********************************************************************************************************************************************************************************************************
//                                                              :: L I S T E S O R T I E R U N G
//**********************************************************************************************************************************************************************************************************
template<class T>class _listesortierung:public _liste<T>{
         public:
				_listesortierung();
				~_listesortierung();
                void sortieren();
		 private:
                 void sortieren(int links,int rechts);
				 int teilen(int links,int rechts);
				 void tauschen(int x,int y);
				 T**feld;

};                 
template<class T>_listesortierung<T>::_listesortierung(){
																feld=0;
};
template<class T>_listesortierung<T>::~_listesortierung(){
};
template<class T>void _listesortierung<T>::sortieren(){
																int anz=this->anzahl();
																if(anz>1){
																 feld=new T*[anz];
																 _listenknoten<T>*it;
																 int i=0;
																 if(anfang(it))do{
															      feld[i++]=it->objekt();
																 }while(naechstes(it));
																 sortieren(0,anz-1);
																 _liste<T>::aushaengen();
																 //for(int n=0;n<i;n++) feld[n]->_listenknoten<T>::aushaengen();
																 for(int n=0;n<i;n++) einhaengen(feld[n]);
																 deletesecure(feld);
																};
};
template<class T>void _listesortierung<T>::sortieren(int links,int rechts){
																if(links<rechts){
																 int teiler=teilen(links,rechts);
																 sortieren(links, teiler-1);
																 sortieren(teiler+1, rechts);
																};
};
template<class T>int _listesortierung<T>::teilen(int links,int rechts){
																int i=links;
																// Starte mit j links vom Pivotelement
																int j=rechts-1;
															    T*pivot=feld[rechts];
																do{
																 // Suche von links ein Element, welches größer als das Pivotelement ist
																 while((feld[i]->vergleichen(pivot)==false)&&(i<rechts)) i++;
														         // Suche von rechts ein Element, welches kleiner als das Pivotelement ist
														         while((feld[j]->vergleichen(pivot)==true)&&(j>links)) j--;
																 if(i<j) tauschen(i,j);
																}while(i<j); // solange i an j nicht vorbeigelaufen ist 
																  //Tausche Pivotelement (daten[rechts]) mit neuer endgültiger Position (daten[i])
																if(feld[i]->vergleichen(pivot)==true) tauschen(i,rechts);
																// gib die Position des Pivotelements zurück
																return(i);
};
template<class T>void _listesortierung<T>::tauschen(int x,int y){
																T*h=feld[x];
																feld[x]=feld[y];
																feld[y]=h;
};

//**********************************************************************************************************************************************************************************************************
//                                                              :: L I S T S O R T 
//**********************************************************************************************************************************************************************************************************
template<class T,class S>class _listesortiert:public _listebasis<_listenknotensortiert<T,S> >{
       // using _basis::_liste< ::_listenknoten<T> >::anfang;
       // using _basis::_liste< ::_listenknoten<T> >::naechstes;
        public:
                inline T*iterator();
                inline T*operator[](int i);
                _listenknotensortiert<T,S>*einhaengen(T*,S);//einfügen,knoten generieren
                //_listenknoten<T>*insertsorted(T*,double);//einfügen,knoten generieren
                _listenknotensortiert<T,S>*einfuegenunredundant(T*,S);
                //_listenknoten<T>*insertsortedunredundant(T*,double);
                void aushaengen();//alles aushangen,alle knoten löschen
                char aushaengen(T*);//aushängen knoten löschen
                void loeschen();//alles aushängen,alle knoten löschen, alle objecte löschen
                char loeschen(T*);//aushängen,knoten löschen,objekt löschen
               // char anfang(T*&);
                /*_listenknoten<T>*insertsorted(T*,float*);
                _listenknoten<T>*insertsortedunredundant(T*,float*);
                */
                char suchen(T*,_listenknotensortiert<T,S>*&);
};
//---------------------------------------------------PUBLIC--------------------------------------------------------------------------------------------------------------------------------------
template<class T,class S>_listenknotensortiert<T,S>*_listesortiert<T,S>::einhaengen(T*obj,S d){
                                                                return(new _listenknotensortiert<T,S>(this,obj,d));
};
/*
template<class T>_listenknoten<T>*_liste<T>::insertsorted(T*obj,double d){
                                                                return(new _listenknotensortiert<T,double>(this,obj,d));
};*/
template<class T,class S>_listenknotensortiert<T,S>*_listesortiert<T,S>::einfuegenunredundant(T*o,S d){
                                                                _listenknotensortiert<T,S>*x;
                                                                char r;
                                                                //----------------
                                                                r=suchen(o,x);
                                                                if(r==0) return(new _listenknotensortiert<T,S>(this,o,d));
                                                                return(x);
};
/*
template<class T>_listenknoten<T>*_liste<T>::insertsortedunredundant(T*o,double d){
                                                                _listenknoten<T>*x;
                                                                char r;
                                                                //----------------
                                                                r=suchen(o,x);
                                                                if(r==0) return(new _listenknotensortiert<T,double>(this,o,d));
                                                                return(x);
};
*/
template<class T,class S>T* _listesortiert<T,S>::operator[](int i){
                                                                int n;
                                                                _listenknotensortiert<T,S>*it;
                                                                //------
                                                                if(anfang(it)){
                                                                 for(n=0;n<i;n++) naechstes(it);
                                                                 return(it->objekt());
                                                                }else{
                                                                 return(0);
                                                                };
};
template<class T,class S>T* _listesortiert<T,S>::iterator(){
                                                                return( _listebasis<_listenknotensortiert<T,S> >::iterator()->objekt() );
};
template<class T,class S>void _listesortiert<T,S>::aushaengen(){
                                                               _listebasis<_listenknotensortiert<T,S> >::loeschen();
};
template<class T,class S>char _listesortiert<T,S>::aushaengen(T*o){
                                                                _listenknotensortiert<T,S>*x;
                                                                //---------------
                                                                while(suchen(o,x)) delete x;
                                                                if(this->erstes()==0) return(0); else return(1);
};
template<class T,class S>void _listesortiert<T,S>::loeschen(){
                                                                _listenknotensortiert<T,S>*it;
                                                                if(anfang(it))do{
                                                                 delete it->objekt();
                                                                }while(naechstes(it));
                                                                aushaengen();
};
template<class T,class S>char _listesortiert<T,S>::loeschen(T*o){
                                                                _listenknotensortiert<T,S>*x;
                                                                //--------------
                                                                while(suchen(o,x)) delete x;
                                                                delete o;
                                                                if(this->erstes()==0) return(0); else return(1);
};
/*
template<class T>char _liste<T>::anfang(T*&eit){
                                                                //externe iterationsinitialisierung
                                                                eit=0;
                                                                if(erstes()){
                                                                 eit=erstes()->objekt;
                                                                 return(1);
                                                                };
                                                                return(0);
};  */
template<class T,class S>char _listesortiert<T,S>::suchen(T*o,_listenknotensortiert<T,S>*&x){
                                                                _listenknotensortiert<T,S>*tit;
                                                                char r;
                                                                //---------------
                                                                r=0;
                                                                x=0;

                                                                if(anfang(tit))do{
                                                                 if(o==tit->objekt()){
                                                                  x=tit;
                                                                  r=1;
                                                                 };
                                                                }while((naechstes(tit))&&(r==0));
                                                                return(r);
};

/*
template<class t>_listenknoten<t>*_liste<t>::insertsorted(t*x,float*a){
                                                                _listenknoten<t>*it;
                                                                _listenknoten<t>*oldfirst;
                                                                char r=0;
                                                                _listenknoten<t>*n;
                                                                //---------------------
                                                                if(erstes==0) n=new _listenknoten<t>(x,this,a); else {
                                                                 it=erstes;
                                                                 do{
                                                                  if(it->alpha)if(*a<*it->alpha)r=1;
                                                                  if(r==0) it=it->naechstes;
                                                                 }while((it!=erstes)&&(r==0));
                                                                 oldfirst=erstes;
                                                                 erstes=it;
                                                                 n=new _listenknoten<t>(x,this,a);//einhaengen(x,it);
                                                                 erstes=oldfirst;
                                                                 if(*erstes->alpha>*erstes->vorheriges->alpha) erstes=erstes->vorheriges;
                                                                };
                                                                return(n);
};
template<class t>_listenknoten<t>*_liste<t>::insertsortedunredundant(t*x,float*a){
                                                                _listenknoten<t>*it;
                                                                _listenknoten<t>*oldfirst;
                                                                char r=0;
                                                                _listenknoten<t>*n;
                                                                _listenknoten<t>*y;
                                                                //--------------
                                                                if(seek(x,y)==0){
                                                                if(erstes==0) n=new _listenknoten<t>(x,this,a); else {
                                                                 it=erstes;
                                                                 do{
                                                                  if(it->alpha)if(*a<*it->alpha)r=1;
                                                                  if(r==0) it=it->naechstes;
                                                                 }while((it!=erstes)&&(r==0));
                                                                 oldfirst=erstes;
                                                                 erstes=it;
                                                                 n=new _listenknoten<t>(x,this,a);//einhaengen(x,it);
                                                                 erstes=oldfirst;
                                                                 if(*erstes->alpha>*erstes->vorheriges->alpha) erstes=erstes->vorheriges;
                                                                };
                                                                return(n);
                                                                };
                                                                return(y);
};


*/
//******************************************************************************************************************************************************************************************************
//                                                              B A S E   : :   T R E E 
//******************************************************************************************************************************************************************************************************
//namespace _basis{
 template <class T>class _baumbasis{
        friend class _baumknotenbasis<T>;
        public:
                _baumbasis();
                virtual ~_baumbasis();
                void loeschen();
                bool resetvertical(T*&);
                bool anfang(T*&);
                bool anfang(_baumknotenbasis<T>*&);
                bool naechstes(T*&);
                void root(_baumknotenbasis<T>*);
                T*root();
                unsigned int anzahl();
        private:                
                void flagiteration(char);
        private:
                _baumknotenbasis<T>*proot;
                T*plast;
 };
 template<class T> _baumbasis<T>::_baumbasis(){
                                                                proot=0;
                                                                plast=0;
 };
 template<class T> _baumbasis<T>::~_baumbasis(){
                                                                loeschen();
 };
 template<class T> void _baumbasis<T>::loeschen(){
                                                                delete proot;
                                                                proot=0;
                                                                plast=0;
 };
 template<class T> bool _baumbasis<T>::resetvertical(T*&eit){
                                                                //diese anfang funktion führt folgende Traversionsinitialisierung durch : 
                                                                //eit=root , beabsichtigtes Traversionsschema ist : vorheriges - this - naechstes
                                                                return(false);
 
 };
 template<class T> bool _baumbasis<T>::anfang(T*&eit){
                                                                //diese anfang funktion führt folgende Traversionsinitialisierung durch : 
                                                                //eit=prevest, last=nextest , beabsichtigtes Traversionsschema ist : vorheriges - this - naechstes
                                                                eit=0;
                                                                plast=0;
                                                                if(proot){
                                                                 flagiteration(0);
                                                                 eit=(T*)proot;
                                                                 while(eit->vorheriges()) eit=eit->vorheriges();
                                                                 plast=(T*)proot;
                                                                 while(plast->naechstes()) plast=plast->naechstes();
                                                                 return(true);
                                                                };
                                                                return(false);
 };
 
 template<class T> bool _baumbasis<T>::naechstes(T*&eit){
                                                                //diese naechstes funktion führt folgende Traversion durch : 
                                                                //vorheriges - this - naechstes (horizontale transversion)
                                                                if(plast){
                                                                 if(eit){
                                                                  eit->pitflag=1;
                                                                  if(eit==plast) return(false);//last wurde vorher schon erreicht->schleifen abbruch (false)
                                                                  if(eit->vorheriges()){
                                                                   if(eit->vorheriges()->pitflag==0){
                                                                    while(eit->vorheriges()) eit=eit->vorheriges();
                                                                    return(true);//ein vorheriges zeiger ist gesetzt, das vorheriges objekt ist nullgeflaggt
                                                                   };
                                                                  };
                                                                  if(eit->naechstes()){
                                                                   if(eit->naechstes()->pitflag==0){
                                                                    eit=eit->naechstes();
                                                                    while(eit->vorheriges()) eit=eit->vorheriges();
                                                                    return(true);//ein naechstes zeiger ist gesetzt, das naechstes objekt ist nullgeflaggt
                                                                   };
                                                                  };
                                                                  if(eit->pparent){
                                                                   eit=eit->parent();
                                                                   while(eit->pitflag==1){
                                                                    if(eit->pparent){
                                                                     eit=eit->parent();
                                                                    }else{
                                                                     //error
                                                                     return(false);
                                                                    };
                                                                   };
                                                                   return(true);
                                                                  };
                                                                  return(false);
                                                                 };
                                                                };
                                                                return(false);                   
 };
 template<class T> void _baumbasis<T>::flagiteration(char f){
                                                                if(proot) proot->flagiteration(f);
 };
 template<class T> void _baumbasis<T>::root(_baumknotenbasis<T>*p){
                                                                proot=p;
                                                                plast=0;
 };
 template<class T> T*_baumbasis<T>::root(){
                                                                return((T*)proot);
 };
 template<class T> unsigned int _baumbasis<T>::anzahl(){
                                                                unsigned int i;
                                                                T*it;
                                                                //------------
                                                                i=0;
                                                                if(anfang(it))do{
                                                                 i++;
                                                                }while(naechstes(it));
                                                                return(i);
 };
//};
//******************************************************************************************************************************************************************************************************
//                                                              B A S E   : :   T R E E N O D E 
//******************************************************************************************************************************************************************************************************
//namespace _basis{
 template <class T>class _baumknotenbasis{
        friend class _baumbasis<T>;
        public:
                _baumknotenbasis(_baumbasis<T>*);
                _baumknotenbasis(_baumbasis<T>*, _baumknotenbasis<T>*,bool);
                virtual ~_baumknotenbasis();
                inline T*naechstes();
                inline T*vorheriges();
                inline T*parent();
                void einfuegennaechstes(_baumknotenbasis<T>*);
                void einfuegenvorheriges(_baumknotenbasis<T>*);
                void setzenbestizer(_baumknotenbasis<T>*);
                void setzennaechstes(_baumknotenbasis<T>*);
                void setzenvorheriges(_baumknotenbasis<T>*);
        private:                
                void flagiteration(char);
                char flagiteration() const;
        private:
                _baumknotenbasis<T>*pnext;
                _baumknotenbasis<T>*pprev;
                _baumbasis<T>*ptree;
                _baumknotenbasis<T>*pparent;
                char pitflag;
                
 };
 template <class T>_baumknotenbasis<T>::_baumknotenbasis(_baumbasis<T>*t){
                                                                //ladekonstruktor
                                                                pnext=0;
                                                                pprev=0;
                                                                ptree=t;
                                                                pparent=0;
                                                                pitflag=0;
 };
 
 template <class T>_baumknotenbasis<T>::_baumknotenbasis(_baumbasis<T>*t,_baumknotenbasis<T>*parent, bool dir){
                                                                pnext=0;
                                                                pprev=0;
                                                                ptree=t;
                                                                pparent=parent;
                                                                pitflag=0;
                                                                if(ptree!=0){
                                                                 if(dir==true) einfuegennaechstes(pparent);
                                                                 else einfuegenvorheriges(pparent);
                                                                }
 }
 
 template <class T>_baumknotenbasis<T>::~_baumknotenbasis(){
                                                                if(pprev!=0){
                                                                 delete pprev;
                                                                }
                                                                if(pnext!=0){
                                                                 delete pnext;
                                                                }
 }
 
 template <class T>T* _baumknotenbasis<T>::naechstes(){
                                                                return ((T*)pnext);
 }
 
 template <class T>T* _baumknotenbasis<T>::vorheriges(){
                                                                return ((T*)pprev);
                                                                        
 }
 template <class T>T* _baumknotenbasis<T>::parent(){
                                                                return ((T*)pparent);
                                                                        
 }
 template <class T>void _baumknotenbasis<T>::einfuegennaechstes(_baumknotenbasis<T>*knoten){
                                                                pparent=knoten;
                                                                if(pparent!=0){
                                                                 if(pparent->pnext!=0) delete pparent->pnext;
                                                                 pparent->pnext=this;
                                                                }else{
                                                                 ptree->loeschen();
                                                                 ptree->proot=this;
                                                                }
 }
 
 template <class T>void _baumknotenbasis<T>::einfuegenvorheriges(_baumknotenbasis<T>*knoten){
                                                                pparent=knoten;
                                                                if(pparent!=0){
                                                                 if(pparent->pprev!=0) delete pparent->pprev;
                                                                 pparent->pprev=this;
                                                                }else{
                                                                 ptree->loeschen();
                                                                 ptree->proot=this;
                                                                }

 }
 template <class T>void _baumknotenbasis<T>::setzenbestizer(_baumknotenbasis<T>*p){
                                                                pparent=p;
 };
 template <class T>void _baumknotenbasis<T>::setzennaechstes(_baumknotenbasis<T>*p){
                                                                pnext=p;
 };
 template <class T>void _baumknotenbasis<T>::setzenvorheriges(_baumknotenbasis<T>*p){
                                                                pprev=p;
 };                                                     
 
 template<class T>void _baumknotenbasis<T>::flagiteration(char f){
                                                                pitflag=f;
                                                                if(pnext) pnext->flagiteration(f);
                                                                if(pprev) pprev->flagiteration(f);
 };
 template<class T>char _baumknotenbasis<T>::flagiteration() const{
                                                                return(pitflag);
 };
 
//};
//*****************************************************************************************************************************************************************************************************
//                                                              B A U M O C T A L
//*****************************************************************************************************************************************************************************************************


template<class T,class _tg> class _baumoctal:public _listebasis<_baumoctalwuerfel<T,_tg> >{
        friend class _baumoctalwuerfel<T,_tg>;
        public:
                _baumoctal(_tg,_tg,_tg,_tg,_tg,_tg);
                virtual ~_baumoctal();
                void einhaengen(T*,_tg,_tg,_tg,_tg,_tg,_tg);
                inline _baumoctalwuerfel<T,_tg>*wurzel();
                void setzenhauptwuerfel(const _tg,const _tg,const _tg,const _tg,const _tg,const _tg);
                void lesenhauptwuerfel(_tg&,_tg&,_tg&,_tg&,_tg&,_tg&) const;
                void maximalobjektanzahl(const unsigned int);
                inline unsigned int maximalobjektanzahl()const;
                void minimalwuerfelkante(const unsigned int,const _tg);
                inline _tg minimalwuerfelkante(const unsigned int)const;
                void erstellenobjektliste(::_liste<T>*,_tg,_tg,_tg,_tg,_tg,_tg);
                void aushaengen();
        private:
                _baumoctalwuerfel<T,_tg>*pwurzel;  
                _tg wx0,wx1,wy0,wy1,wz0,wz1;         
                unsigned int pmaximalobjektanzahl;   
                _tg pminimalwuerfelkante[3];  
};

template<class T,class _tg> _baumoctal<T,_tg>::_baumoctal(_tg _x0,_tg _x1,_tg _y0,_tg _y1,_tg _z0,_tg _z1){
                                                                pwurzel=0;
                                                                maximalobjektanzahl(1);
                                                                minimalwuerfelkante(0,0.1f);
                                                                minimalwuerfelkante(1,0.1f);
                                                                minimalwuerfelkante(2,0.1f);
                                                                setzenhauptwuerfel(_x0,_x1,_y0,_y1,_z0,_z1);
                                                                
};
template<class T,class _tg> _baumoctal<T,_tg>::~_baumoctal(){
                                                                aushaengen();
};
template<class T,class _tg> void _baumoctal<T,_tg>::aushaengen(){
                                                                if(pwurzel){
                                                                 delete pwurzel;
                                                                };
};

template<class T,class _tg> void _baumoctal<T,_tg>::einhaengen(T*objekt,_tg x0,_tg x1,_tg y0,_tg y1,_tg z0,_tg z1){
                                                                if(pwurzel==0){
                                                                 pwurzel=new _baumoctalwuerfel<T,_tg>(this,0,wx0,wx1,wy0,wy1,wz0,wz1);
                                                                };
                                                                pwurzel->einhaengen(objekt,x0,x1,y0,y1,z0,z1);
};
template<class T,class _tg> _baumoctalwuerfel<T,_tg>* _baumoctal<T,_tg>::wurzel(){
                                                                return(pwurzel);
};
template<class T,class _tg> void _baumoctal<T,_tg>::setzenhauptwuerfel(const _tg x0,const _tg x1,const _tg y0,const _tg y1,const _tg z0,const _tg z1){
                                                                wx0=x0;
                                                                wx1=x1;
                                                                wy0=y0;
                                                                wy1=y1;
                                                                wz0=z0;
                                                                wz1=z1;
                                                                _tg h;
                                                                if(wx1<wx0) {h=wx0;wx0=wx1;wx1=h;};
                                                                if(wy1<wy0) {h=wy0;wy0=wy1;wy1=h;};
                                                                if(wz1<wz0) {h=wz0;wz0=wz1;wz1=h;};
};
template<class T,class _tg> void _baumoctal<T,_tg>::lesenhauptwuerfel(_tg&x0,_tg&x1,_tg&y0,_tg&y1,_tg&z0,_tg&z1) const{
                                                                x0=wx0;
                                                                y0=wy0;
                                                                z0=wz0;
                                                                x1=wx1;
                                                                y1=wy1;
                                                                z1=wz1;
};
template<class T,class _tg> void _baumoctal<T,_tg>::maximalobjektanzahl(const unsigned int m){
                                                                if(m==0) pmaximalobjektanzahl=1; else pmaximalobjektanzahl=m;
};
template<class T,class _tg> unsigned int _baumoctal<T,_tg>::maximalobjektanzahl()const{
                                                                return(pmaximalobjektanzahl);
};
template<class T,class _tg> void _baumoctal<T,_tg>::minimalwuerfelkante(const unsigned int i,const _tg k){
                                                                if(k>0) pminimalwuerfelkante[i]=k; else pminimalwuerfelkante[i]=0.001f;
};
template<class T,class _tg> _tg _baumoctal<T,_tg>::minimalwuerfelkante(const unsigned int i)const{
                                                                return(pminimalwuerfelkante[i]);
};
template<class T,class _tg> void _baumoctal<T,_tg>::erstellenobjektliste(::_liste<T>*l,_tg ox0,_tg ox1,_tg oy0,_tg oy1,_tg oz0,_tg oz1){
                                                                if(l){
                                                                 l->aushaengen();
                                                                 if(pwurzel){
                                                                  pwurzel->erstellenobjektliste(l,ox0,ox1,oy0,oy1,oz0,oz1);
                                                                 };
                                                                };
};
//*****************************************************************************************************************************************************************************************************
//                                                              B A U M O C T A L W U E R F E L
//*****************************************************************************************************************************************************************************************************
template<class T,class _tg>class _baumoctalwuerfel:public _listenknotenbasis<_baumoctalwuerfel<T,_tg> >,public _liste<T>{
        public:
                using _liste<T>::anfang;
                using _liste<T>::naechstes;
                using _liste<T>::vorheriges;
        public:
                _baumoctalwuerfel(_baumoctal<T,_tg>*,_baumoctalwuerfel<T,_tg>*,_tg,_tg,_tg,_tg,_tg,_tg);
                virtual ~_baumoctalwuerfel();
                void einhaengen(T*,_tg,_tg,_tg,_tg,_tg,_tg);
                void zerteilen();
                bool innerhalb(_tg,_tg,_tg,_tg,_tg,_tg);
                bool innerhalb(_tg,_tg,_tg,_tg,_tg,_tg,_tg,_tg,_tg,_tg,_tg,_tg);
                bool kinderlos()const;
                void erstellenobjektliste(::_liste<T>*l,_tg ox0,_tg ox1,_tg oy0,_tg oy1,_tg oz0,_tg oz1);
        public:
                _baumoctal<T,_tg>*baum;
                _baumoctalwuerfel<T,_tg>*besitzer;
                _baumoctalwuerfel<T,_tg>*kind[2][2][2];                                
                _tg x0,x1,y0,y1,z0,z1;
};
template<class T,class _tg> _baumoctalwuerfel<T,_tg>::_baumoctalwuerfel(_baumoctal<T,_tg>*ba,_baumoctalwuerfel<T,_tg>*p,_tg a,_tg b,_tg c,_tg d,_tg e,_tg f):_listenknotenbasis<_baumoctalwuerfel<T,_tg> >(ba){
                                                                baum=ba;
                                                                besitzer=p;
                                                                x0=a;
                                                                x1=b;
                                                                y0=c;
                                                                y1=d;
                                                                z0=e;
                                                                z1=f;
                                                                unsigned int i,j,k;
                                                                for(i=0;i<2;i++)for(j=0;j<2;j++)for(k=0;k<2;k++) kind[i][j][k]=0;
};                                            
template<class T,class _tg> _baumoctalwuerfel<T,_tg>::~_baumoctalwuerfel(){
                                                                unsigned int i,j,k;
                                                                for(i=0;i<2;i++)for(j=0;j<2;j++)for(k=0;k<2;k++)
                                                                if(kind[i][j][k]){
                                                                 kind[i][j][k]->besitzer=0;
                                                                 delete kind[i][j][k];
                                                                 kind[i][j][k]=0;
                                                                };
                                                                if(besitzer){
                                                                 bool kindausserthis=false;
                                                                 for(i=0;i<2;i++)for(j=0;j<2;j++)for(k=0;k<2;k++){
                                                                  if(besitzer->kind[i][j][k]==this) besitzer->kind[i][j][k]=0; else{//endlosrekursion verhindern
                                                                   if(besitzer->kind[i][j][k]!=0) kindausserthis=true;
                                                                  };
                                                                 };
                                                                 if(kindausserthis==false) {
                                                                  if(besitzer->_liste<T>::anzahl()==0) {
                                                                   delete besitzer;
                                                                  };
                                                                 };
                                                                };
                                                                if(this==baum->wurzel()) baum->pwurzel=0;
                                                                _listenknoten<T>*oit;
                                                                if(anfang(oit))do{
                                                                 _baumoctalobjekt<T,_tg>*obj=dynamic_cast<_baumoctalobjekt<T,_tg> * >(oit);
                                                                  if(obj){
                                                                   obj->wuerfel=0;
                                                                  };
                                                                }while(naechstes(oit));
                                                                
};
template<class T,class _tg> void _baumoctalwuerfel<T,_tg>::einhaengen(T*o,_tg ox0,_tg ox1,_tg oy0,_tg oy1,_tg oz0,_tg oz1){
                                                                unsigned int i,j,k;
                                                                //wenn knoten überhaupt noch keine kinder hat, dann objekt hier einfügen und
                                                                //auf zerlegung und neusortierung prüfen
                                                                bool hatkinner=false;
                                                                for(i=0;i<2;i++)for(j=0;j<2;j++)for(k=0;k<2;k++)
                                                                if(kind[i][j][k]){
                                                                 hatkinner=true;
                                                                };
                                                                if(hatkinner==false) {
                                                                 new _baumoctalobjekt<T,_tg>(this,o,ox0,ox1,oy0,oy1,oz0,oz1);
                                                                 if(_liste<T>::anzahl()>baum->maximalobjektanzahl()){
                                                                  zerteilen();
                                                                 };
                                                                }else{
                                                                 _tg hbx=(x1-x0)*0.5f;
                                                                 _tg hby=(y1-y0)*0.5f;
                                                                 _tg hbz=(z1-z0)*0.5f;
                                                                 //prüfen, ob dieser würfel kinder hat, 
                                                                 //wenn ja einhaengen weiterleiten an kind(er)
                                                                 //ggf hier kind erzeugen und objekt einhaengen
                                                                 for(i=0;i<2;i++)for(j=0;j<2;j++)for(k=0;k<2;k++)
                                                                 if(kind[i][j][k]){
                                                                  if(kind[i][j][k]->innerhalb(ox0,ox1,oy0,oy1,oz0,oz1)){
                                                                   kind[i][j][k]->einhaengen(o,ox0,ox1,oy0,oy1,oz0,oz1);
                                                                  };
                                                                 }else{
                                                                  //mit virtuellen kind prüfen, wenn innerhalb kind anlegen und einhaengen
                                                                  _tg px0,px1,py0,py1,pz0,pz1;
                                                                  px0=x0+hbx*_tg(i);
                                                                  py0=y0+hby*_tg(j);
                                                                  pz0=z0+hbz*_tg(k);
                                                                  px1=px0+hbx;
                                                                  py1=py0+hby;
                                                                  pz1=pz0+hbz;
                                                                  if(innerhalb(ox0,ox1,oy0,oy1,oz0,oz1,px0,px1,py0,py1,pz0,pz1)){
                                                                   kind[i][j][k]=new _baumoctalwuerfel(baum,this,px0,px1,py0,py1,pz0,pz1);
                                                                   kind[i][j][k]->einhaengen(o,ox0,ox1,oy0,oy1,oz0,oz1);
                                                                  };
                                                                 };
                                                                };
};       
template<class T,class _tg> void _baumoctalwuerfel<T,_tg>::zerteilen(){
                                                                unsigned int i,j,k;
                                                                _listenknoten<T>*oit;
                                                                _baumoctalobjekt<T,_tg>*obj;
                                                                _tg hbx=(x1-x0)*0.5f;
                                                                _tg hby=(y1-y0)*0.5f;
                                                                _tg hbz=(z1-z0)*0.5f;
                                                                //-------------------------
                                                                if(hbx>=baum->minimalwuerfelkante(0))
                                                                if(hby>=baum->minimalwuerfelkante(1))
                                                                if(hbz>=baum->minimalwuerfelkante(2))
                                                                {
                                                                 if(anfang(oit))do{
                                                                  obj=dynamic_cast<_baumoctalobjekt<T,_tg> * >(oit);
                                                                  if(obj){
                                                                   for(i=0;i<2;i++)for(j=0;j<2;j++)for(k=0;k<2;k++){
                                                                    if(kind[i][j][k]!=0){
                                                                     if(kind[i][j][k]->innerhalb(obj->x0,obj->x1,obj->y0,obj->y1,obj->z0,obj->z1)){
                                                                      kind[i][j][k]->einhaengen(obj->objekt,obj->x0,obj->x1,obj->y0,obj->y1,obj->z0,obj->z1);
                                                                      
                                                                     };
                                                                    }else{
                                                                     _tg px0,px1,py0,py1,pz0,pz1;
                                                                     px0=x0+(hbx*_tg(i));
                                                                     py0=y0+(hby*_tg(j));
                                                                     pz0=z0+(hbz*_tg(k));
                                                                     px1=px0+hbx;
                                                                     py1=py0+hby;
                                                                     pz1=pz0+hbz;
                                                                     if(innerhalb(obj->x0,obj->x1,obj->y0,obj->y1,obj->z0,obj->z1,px0,px1,py0,py1,pz0,pz1)){
                                                                      kind[i][j][k]=new _baumoctalwuerfel<T,_tg>(baum,this,px0,px1,py0,py1,pz0,pz1);
                                                                      kind[i][j][k]->einhaengen(obj->objekt,obj->x0,obj->x1,obj->y0,obj->y1,obj->z0,obj->z1);
                                                                     };
                                                                    };
                                                                   };
                                                                  };
                                                                  obj->wuerfel=0;
                                                                 }while(naechstes(oit));
                                                                _liste<T>::aushaengen();
                                                                };
                                                                
};
template<class T,class _tg> bool _baumoctalwuerfel<T,_tg>::innerhalb(_tg ox0,_tg ox1,_tg oy0,_tg oy1,_tg oz0,_tg oz1){
                                                                if(ox0>x1) return(false);
                                                                if(ox1<x0) return(false);
                                                                if(oy0>y1) return(false);
                                                                if(oy1<y0) return(false);
                                                                if(oz0>z1) return(false);
                                                                if(oz1<z0) return(false);
                                                                return(true);
};
template<class T,class _tg> bool _baumoctalwuerfel<T,_tg>::innerhalb(_tg ox0,_tg ox1,_tg oy0,_tg oy1,_tg oz0,_tg oz1,
                                                                     _tg px0,_tg px1,_tg py0,_tg py1,_tg pz0,_tg pz1){
                                                                if(ox0>px1) return(false);
                                                                if(ox1<px0) return(false);
                                                                if(oy0>py1) return(false);
                                                                if(oy1<py0) return(false);
                                                                if(oz0>pz1) return(false);
                                                                if(oz1<pz0) return(false);
                                                                return(true);
};
template<class T,class _tg> bool _baumoctalwuerfel<T,_tg>::kinderlos()const{
                                                                if(kind[0][0][0]) return(false);
                                                                if(kind[1][0][0]) return(false);
                                                                if(kind[0][1][0]) return(false);
                                                                if(kind[1][1][0]) return(false);
                                                                if(kind[0][0][1]) return(false);
                                                                if(kind[1][0][1]) return(false);
                                                                if(kind[0][1][1]) return(false);
                                                                if(kind[1][1][1]) return(false);
                                                                return(true);
};
template<class T,class _tg> void _baumoctalwuerfel<T,_tg>::erstellenobjektliste(::_liste<T>*l,_tg ox0,_tg ox1,_tg oy0,_tg oy1,_tg oz0,_tg oz1){
                                                                unsigned int i,j,k;
                                                               /* bool hatkinder=false;
                                                                for(i=0;i<2;i++)for(j=0;j<2;j++)for(k=0;k<2;k++){
                                                                 if(kind[i][j][k]) hatkinder=true;
                                                                };
                                                                if(hatkinder){
                                                                }else{*/
                                                                 if(innerhalb(ox0,ox1,oy0,oy1,oz0,oz1)){
                                                                  _listenknoten<T>*oit;
                                                                  if(anfang(oit))do{
                                                                   l->einhaengen(oit->objekt());
                                                                  }while(naechstes(oit));
                                                                  for(i=0;i<2;i++)for(j=0;j<2;j++)for(k=0;k<2;k++){
                                                                   if(kind[i][j][k]) kind[i][j][k]->erstellenobjektliste(l,ox0,ox1,oy0,oy1,oz0,oz1);
                                                                  };
                                                                 };
                                                                //};
};
//*****************************************************************************************************************************************************************************************************
//                                                              B A U M O C T A L O B J E K T 
//*****************************************************************************************************************************************************************************************************
template<class T,class _tg> class _baumoctalobjekt:public _verbinder<T,_baumoctalwuerfel<T,_tg> >{
        public:
                _baumoctalobjekt(_baumoctalwuerfel<T,_tg>*,T*,_tg,_tg,_tg,_tg,_tg,_tg);
                virtual ~_baumoctalobjekt();
                inline void lesen(_tg&,_tg&,_tg&,_tg&,_tg&,_tg&);
        public:
                _baumoctalwuerfel<T,_tg>*wuerfel;
                T*objekt;
                _tg x0,x1,y0,y1,z0,z1;                
};
template<class T,class _tg>_baumoctalobjekt<T,_tg>::_baumoctalobjekt(_baumoctalwuerfel<T,_tg>*w,T*o,_tg ox0,_tg ox1,_tg oy0,_tg oy1,_tg oz0,_tg oz1):_verbinder<T,_baumoctalwuerfel<T,_tg> >(w,o,o,w){
                                                                wuerfel=w;
                                                                objekt=o;
                                                                x0=ox0;
                                                                x1=ox1;
                                                                y0=oy0;
                                                                y1=oy1;
                                                                z0=oz0;
                                                                z1=oz1;
};
template<class T,class _tg>_baumoctalobjekt<T,_tg>::~_baumoctalobjekt(){
                                                                _listenknoten<T>::aushaengen();
                                                                _listenknoten<_baumoctalwuerfel<T,_tg> >::aushaengen();
                                                                if(wuerfel){
                                                                 if(wuerfel->_liste<T>::anzahl()==0){
                                                                  //destruktion von würfel ausführen
                                                                  delete wuerfel;
                                                                  wuerfel=0;
                                                                 };
                                                                };
                                                                
};
template<class T,class _tg>void _baumoctalobjekt<T,_tg>::lesen(_tg&ox0,_tg&ox1,_tg&oy0,_tg&oy1,_tg&oz0,_tg&oz1){
                                                                ox0=x0;
                                                                ox1=x1;
                                                                oy0=y0;
                                                                oy1=y1;
                                                                oz0=z0;
                                                                oz1=z1;
};
//*****************************************************************************************************************************************************************************************************
//                                                                                      H A S H D I S C
//*****************************************************************************************************************************************************************************************************
template<class t> class _hashlistheader{
                public:
                                _hashlistheader(){
                                                                firstobject=0;
                                };
                                ~_hashlistheader(){
                                                                clear_ring(firstobject);
                                };
                public:
                                t*firstobject;
};
template<class t> class _hashscheibeknoten{
                public:
                                _hashscheibeknoten(t*){};
                                ~_hashscheibeknoten(){};
                public:
                                t*objekt;
                                _hashscheibe<t>*disc;
                                _hashscheibeknoten<t>*innercross;
                                _hashscheibeknoten<t>*outercross;
                                _hashscheibeknoten<t>*naechstes;
                                _hashscheibeknoten<t>*vorheriges;
};
template<class t> class _hashscheibe{
                public:
                                _hashscheibe(){};
                                ~_hashscheibe(){};
                public:
                                _hashscheibeknoten<t>*erstes;
};
//***************************************************************************************************************************************************************************************************
//                                                                                            B I N T R E E
//***************************************************************************************************************************************************************************************************
template<class t>class _baumbinaerknoten{
                public:
                                _baumbinaerknoten(t*o,_baumbinaer<t>*b):objekt(o){
                                                                bintree=b;
                                                                left[0]=0;
                                                                left[1]=0;
                                                                parent=0;
                                                                markierung=0;
                                                                //bintree->einhaengen(objekt);
                                };
                                ~_baumbinaerknoten(){
                                                                //bintree->aushaengen(objekt);
                                };
                public:
                                t*objekt;
                                _baumbinaer<t>*bintree;
                                _baumbinaerknoten<t>*parent;
                                _baumbinaerknoten<t>*left[2];
                                int markierung;
};
template<class t>class _baumbinaer{
                public:
                                _baumbinaer();
                                ~_baumbinaer();
                                _baumbinaerknoten<t>*einhaengen(t*);
                                void insertrecursiv(_baumbinaerknoten<t>*,_baumbinaerknoten<t>*);
                                void aushaengen(t*);
                                void aushaengen();
                                void entfernenrekursiv(_baumbinaerknoten<t>*);
                                void loeschen(t*);
                                void loeschen();
                                void loeschenrekursiv(_baumbinaerknoten<t>*);
                                void markierung(int);
                                void markierungrekursiv(_baumbinaerknoten<t>*,int);
                                char anfang();
                                void aktualisieren();
                                void aktualisierenrekursiv(_baumbinaerknoten<t>*);
                                char naechstes();
                                char vorheriges();
                                char rueck();
                                char nextbin();
                public:
                                _baumbinaerknoten<t>*erstes;
                                _baumbinaerknoten<t>*it;
                                _liste<t>*liste;

};
template<class t>_baumbinaer<t>::_baumbinaer(){
                                                                erstes=0;
                                                                liste=new _liste<t>();

};
template<class t>_baumbinaer<t>::~_baumbinaer(){
                                                                ::loeschen(liste);
                                                                aushaengen();
};
template<class t>char _baumbinaer<t>::anfang(){
                                                                it=erstes;
                                                                liste->anfang();
                                                                if(it)return(1);else return(0);
};
template<class t>void _baumbinaer<t>::markierung(int f){
                                                                if(anfang()){
                                                                 markierungrekursiv(erstes,f);
                                                                 anfang();
                                                                };
};
template<class t>void _baumbinaer<t>::markierungrekursiv(_baumbinaerknoten<t>*it,int f){
                                                                if(it->left[0])markierungrekursiv(it->left[0],f);
                                                                if(it->left[1])markierungrekursiv(it->left[1],f);
                                                                it->markierung=f;
};
template<class t>void _baumbinaer<t>::aktualisieren(){
                                                                liste->aushaengen();
                                                                if(erstes){
                                                                 aktualisierenrekursiv(erstes);
                                                                };
};
template<class t>void _baumbinaer<t>::aktualisierenrekursiv(_baumbinaerknoten<t>*i){
                                                                if(i->left[0]) aktualisierenrekursiv(i->left[0]);
                                                                liste->einhaengen(i->objekt);
                                                                if(i->left[1]) aktualisierenrekursiv(i->left[1]);


};
template<class t>char _baumbinaer<t>::naechstes(){
                                                                char r;
                                                                //--------
                                                                r=liste->naechstes();
                                                                return(r);
};
template<class t>char _baumbinaer<t>::nextbin(){
                                                                char r;
                                                                //--------
                                                                r=1;
                                                                it->markierung=1;
                                                                if((it->left[0])&&(it->left[1])){
                                                                 if(it->left[0]->markierung==0) it=it->left[0]; else
                                                                 if(it->left[1]->markierung==0) it=it->left[1]; else r=rueck();
                                                                }else
                                                                if((it->left[0]==0)&&(it->left[1])){
                                                                 if(it->left[1]->markierung==0) it=it->left[1]; else r=rueck();
                                                                }else
                                                                if((it->left[0])&&(it->left[1]==0)){
                                                                 if(it->left[0]->markierung==0) it=it->left[0]; else r=rueck();
                                                                }else
                                                                if((it->left[0]==0)&&(it->left[1]==0)){
                                                                 r=rueck();
                                                                };
                                                                return(r);
};

template<class t>char _baumbinaer<t>::rueck(){
                                                                char stop;
                                                                char r=1;
                                                                //----------------
                                                                if(it->parent==0){
                                                                 if(it->left[0]) if(it->left[0]->markierung==0) it=it->left[0]; else
                                                                 if(it->left[1]) if(it->left[1]->markierung==0) it=it->left[1]; else r=0;
                                                                }else{
                                                                 it=it->parent;
                                                                 stop=0;
                                                                 do{
                                                                  if(it->left[0]) if(it->left[0]->markierung==0) stop=1;
                                                                  if(it->left[1]) if(it->left[1]->markierung==0) stop=1;
                                                                  if(it->markierung==0) stop=1;
                                                                  if(stop==0) {
                                                                   if(it->parent){
                                                                    it=it->parent;
                                                                   }else{
                                                                    r=0;
                                                                    stop=1;
                                                                   };
                                                                  };
                                                                 }while(stop==0);
                                                                };
                                                                if(r==0) {
                                                                };//resetsequence();!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                                                                return(r);
};

template<class t>_baumbinaerknoten<t>* _baumbinaer<t>::einhaengen(t*o){
                                                                _baumbinaerknoten<t>*b;
                                                                //------------------
                                                                b=new _baumbinaerknoten<t>(o,this);
                                                                if(erstes){
                                                                 insertrecursiv(b,erstes);
                                                                }else{
                                                                 erstes=b;
                                                                 anfang();
                                                                };
                                                               // aktualisieren();
                                                                return(b);
};
template<class t>void _baumbinaer<t>::insertrecursiv(_baumbinaerknoten<t>*b,_baumbinaerknoten<t>*par){
                                                                if(par->objekt->alpha>b->objekt->alpha){
                                                                 if(par->left[0]){
                                                                  insertrecursiv(b,par->left[0]);
                                                                 }else{
                                                                  par->left[0]=b;
                                                                  b->parent=par;
                                                                 };
                                                                }else{
                                                                 if(par->left[1]){
                                                                  insertrecursiv(b,par->left[1]);
                                                                 }else{
                                                                  par->left[1]=b;
                                                                  b->parent=par;
                                                                 };
                                                                };
};
template<class t>void _baumbinaer<t>::aushaengen(t*){
};
template<class t>void _baumbinaer<t>::aushaengen(){
                                                                if(erstes){
                                                                 entfernenrekursiv(erstes);
                                                                };
};
template<class t>void _baumbinaer<t>::entfernenrekursiv(_baumbinaerknoten<t>*it){
                                                                if(it->left[0])entfernenrekursiv(it->left[0]);
                                                                if(it->left[1])entfernenrekursiv(it->left[1]);
                                                                ::loeschen(it);
};
template<class t>void _baumbinaer<t>::loeschen(t*){
};
template<class t>void _baumbinaer<t>::loeschen(){
                                                                if(erstes){
                                                                 loeschenrekursiv(erstes);
                                                                };
};
template<class t>void _baumbinaer<t>::loeschenrekursiv(_baumbinaerknoten<t>*it){
                                                                if(it->left[0])loeschenrekursiv(it->left[0]);
                                                                if(it->left[1])loeschenrekursiv(it->left[1]);
                                                                ::loeschen(it->objekt);
                                                                ::loeschen(it);


};




































//****************************************************************************************************************************************************************************************************
//                      T E M P L A T E F U N K T I O N E N   F Ü R   I M P L I Z I T   D O P P E L T    V E R K E T T E T E   R I N G L I S T E N
//****************************************************************************************************************************************************************************************************
template<class a> void einhaengen(a * x,a*&y){
                                                                if(y==0) y=x->vorheriges=x->naechstes=x;
                                                                else{
                                                                 x->naechstes=y;
                                                                 x->vorheriges=y->vorheriges;
                                                                 y->vorheriges->naechstes=x;
                                                                 y->vorheriges=x;
                                                                };
};
template<class a> void insertsorted(a*x,a*&erstes){
                                                                a*it;
                                                                char r=0;
                                                                if(erstes==0) einhaengen(x,erstes); else {
                                                                 it=erstes;
                                                                 do{
                                                                  if(x->alpha<it->alpha)r=1;
                                                                  if(r==0) it=it->naechstes;
                                                                 }while((it!=erstes)&&(r==0));
                                                                 einhaengen(x,it);
                                                                 if(erstes->alpha>erstes->vorheriges->alpha) erstes=erstes->vorheriges;
                                                                };
};
template <class T> void loeschen(T&x){
                                                                if(x){
                                                                 delete x;
                                                                 x=0;
                                                                };
};
template <class a,class b> void loeschen(a * x,b & y){
                                                                if(y!=0){
                                                                 if(y->naechstes==y)y=0;
                                                                 else{
                                                                  if(y==x) y=y->vorheriges;
                                                                  x->vorheriges->naechstes=x->naechstes;
                                                                  x->naechstes->vorheriges=x->vorheriges;
                                                                 };
                                                                 delete x;
                                                                };
};
template <class a,class b> void aushaengen(a * x,b & y){
                                                                if(y!=0){
                                                                 if(y->naechstes==y)y=0;
                                                                 else{
                                                                  if(y==x) y=y->vorheriges;
                                                                  x->vorheriges->naechstes=x->naechstes;
                                                                  x->naechstes->vorheriges=x->vorheriges;
                                                                 };
                                                                };
                                                                x->vorheriges=0;
                                                                x->naechstes=0;
};
template <class a> void flag_ring(a*erstes,int f){
                                                                a*it;
                                                                //--------
                                                                it=erstes;
                                                                if(it)do{
                                                                 it->markierung=f;
                                                                 it=it->naechstes;
                                                                }while(it!=erstes);
};
template <class a,class b> a*swapprev(a*it,b&erstes){
                                                                a*o0;
                                                                a*o1;
                                                                //-------
                                                                o0=it;
                                                                o1=it->vorheriges;
                                                                if(o1->vorheriges==o0) erstes=erstes->naechstes; else{
                                                                 if(erstes==o0) erstes=o1; else if(erstes==o1) erstes=o0;
                                                                 o0->naechstes->vorheriges=o1;
                                                                 o1->vorheriges->naechstes=o0;
                                                                 o0->vorheriges=o1->vorheriges;
                                                                 o1->vorheriges=o0;
                                                                 o1->naechstes=o0->naechstes;
                                                                 o0->naechstes=o1;
                                                                };
                                                                return(it);
};
template <class a,class b> a*swapnext(a*it,b&erstes){
                                                                a*o0;
                                                                a*o1;
                                                                //---------
                                                                o0=it;
                                                                o1=it->naechstes;
                                                                if(o1->naechstes==o0) erstes=erstes->naechstes; else{
                                                                 if(erstes==o0) erstes=o1; else if(erstes==o1) erstes=o0;
                                                                 o1->naechstes->vorheriges=o0;
                                                                 o0->vorheriges->naechstes=o1;
                                                                 o0->naechstes=o1->naechstes;
                                                                 o1->naechstes=o0;
                                                                 o1->vorheriges=o0->vorheriges;
                                                                 o0->vorheriges=o1;
                                                                };
                                                                return(it);
};
template <class a,class b> b * iterated(a i,b * erstes){
                                                                for(int n=0;n<i;n++) erstes=erstes->naechstes;
                                                                return(erstes);
};
template <class a> int indiced(a*x,a*erstes){
                                                                a*i=erstes;
                                                                int r=-1;
                                                                int c=0;
                                                                if(i)do{
                                                                 if(x==i) r=c;
                                                                 c++;
                                                                 i=i->naechstes;
                                                                }while((i!=erstes)&&(r==-1));
                                                                return(r);
};
template <class ring> void clear_ring(ring*&or_first){
                                                                if(or_first){
                                                                 ring*or_act=or_first->vorheriges;
                                                                 ring*or_del;
                                                                 if(or_act!=or_first)do{
                                                                  or_del=or_act;
                                                                  or_act=or_act->vorheriges;
                                                                  delete or_del;
                                                                 }while(or_act!=or_first);
                                                                 delete or_act;
                                                                };
                                                                or_first=0;
};
template <class T>void kill(T*&erstes){
                                                                T*wit;
                                                                T*wn;
                                                                //---------------
                                                                wit=erstes;
                                                                if(wit)do{
                                                                 if(wit->killok){
                                                                  wn=wit->naechstes;
                                                                  delete wit;
                                                                  wit=wn;
                                                                  if(erstes==0) wit=0;
                                                                 }else wit=wit->naechstes;
                                                                }while(wit!=erstes);
                                                                if(erstes)if(erstes->killok){
                                                                 delete erstes;
                                                                };
};
template <class ring> void unite_ring(ring*r0,ring*r1){
                                                                ring*r0p;
                                                                //-----------------
                                                                r0p=r0->vorheriges;
                                                                r0->vorheriges->naechstes=r1;
                                                                r0->vorheriges=r1->vorheriges;
                                                                r1->vorheriges->naechstes=r0;
                                                                r1->vorheriges=r0p;
};
template <class ring> void invert_ring(ring*&f){
                                                                ring*h;
                                                                ring*tauschen;
                                                                ring*it=f;
                                                                //-------------
                                                                if(it)do{
                                                                 h=it->naechstes;
                                                                 tauschen=it->vorheriges;it->vorheriges=it->naechstes;it->naechstes=tauschen;
                                                                 it=h;
                                                                }while(it!=f);
                                                                f=f->naechstes;
};
template <class ring> void isolate_ring(ring*f,int c){
                                                                int i;
                                                                ring*h=f;
                                                                for(i=1;i<c;i++)h=h->naechstes;
                                                                f->vorheriges->naechstes=h->naechstes;
                                                                h->naechstes->vorheriges=f->vorheriges;
                                                                f->vorheriges=h;
                                                                h->naechstes=f;
};

#endif

