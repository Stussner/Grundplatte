//******************************************************************************************************************************************************************************************************
//  Projekt      : grundplatte
//  Bibliothek   : _grundplatte.lib
//  Modul        : _weltpartikel.cpp
//  Datum        : 09.01.2006
//  Beschreibung : 
//******************************************************************************************************************************************************************************************************
#include <_weltpartikel.hpp>
#include <_weltpolygon.hpp>

//NOCH EINGBUNDEN , weil grafik nicht vollständig:
//#include <_grafikopengl.hpp>
//******************************************************************************************************************************************************************************************************
//                                                              P A R T I K E L Q U E L L E 
//******************************************************************************************************************************************************************************************************
_partikelquelle::_partikelquelle(_welt*w,_zeit*z,_listebasis<_partikelquelle >*lpq,_listebasis<_partikel>*lpt):_listenknotenbasis<_partikelquelle>(lpq){
                                                                _vektor3<_tg> o;
                                                                _vektor3<_tg> v;
                                                                init(w,z,lpq,lpt,o,v,1000,0);
};
_partikelquelle::_partikelquelle(_welt*w,_zeit*z,_listebasis<_partikelquelle >*lpq,_listebasis<_partikel>*lpt,const _vektor3<_tg>&o,const _vektor3<_tg>&v,_tg lifetime,_textur<_tb>*tex):_listenknotenbasis<_partikelquelle>(lpq){
                                                                init(w,z,lpq,lpt,o,v,lifetime,tex);
};
_partikelquelle::_partikelquelle(const _partikelquelle*p):_listenknotenbasis<_partikelquelle>(p->plistepartikelquelle){
                                                                kopieren(p);
};
void _partikelquelle::init(_welt*w,_zeit*z,_listebasis<_partikelquelle >*lpq,_listebasis<_partikel>*lpt,const _vektor3<_tg>&o,const _vektor3<_tg>&v,_tg lifetime,_textur<_tb>*tex){
                                                                
                                                                pwelt=w;
                                                                pzeit=z;
                                                                pzone=0;
                                                                pname="null";                                                                
                                                                
                                                                plistepartikel=lpt;
                                                                plistepartikelquelle=lpq;
                                                                plistepartikeleinhaengenerstes=false;
                                                                ppartikelquellegeburt=0;
                                                                ppartikelquelleleben=0;
                                                                ppartikelquelletod=0;
                                                                
                                                                
                                                                ptexturliste.aushaengen();
                                                                ptexturstrings.loeschen();
                                                                ptexturiterator=0;
                                                                ptexturanzahl=0;
                                                                if(tex){
                                                                 ptexturliste.einhaengen(tex);
                                                                 ptexturliste.anfang(ptexturiterator);
                                                                 ptexturanzahl=1;
                                                                };                                                                
                                                                
	                                                            pnetzliste.aushaengen();
	                                                            pnetziterator=0;                                                                
                                                                
                                                                paktiv=false;
                                                                
                                                                pkollision=false;
                                                                pkollisionreflektierend=1;
                                                                pkollisionabgleitend=0;
                                                                pkollisionanhaftend=0;  
                                                                
                                                                port=o;
                                                                porttoleranz=0;
                                                                portraum[0].setzen(0,0,0);
                                                                portraum[1].setzen(0,0,0);
                                                                portraum[2].setzen(0,0,0);
                                                                                                                              
                                                                pvektor=v;
                                                                pvektortoleranz=0;
                                                                pzentrumbenutzen=false;
                                                                protation=0;
                                                                protationtoleranz=0;
	                                                            protationvektor=0;
	                                                            protationreibung=1;
	                                                            protationachse.setzen(1,1,1);    
	                                                            protationachsetoleranz=0;                                                                 
                                                                
                                                                plebensdauerbegrenzt=false;
                                                                plebensdauer=1000;
                                                                plebensdauerletzteaktivierung=pzeit->system();
                                                                plebensdauerpartikel=lifetime;
                                                                plebensdauerpartikeltoleranz=0;   
                                                                
                                                                pgenerationsrate=1;
                                                                pgenerationsratetoleranz=0;
	                                                            pgenerationsdichtedynamisch=0;
	                                                            pgenerationsratesollpartikel=0;
	                                                            pgenerationsrateletztegenerierung=0;  

                                                                pmasse=1;
                                                                pgroesse=1;
                                                                pgroessetoleranz=0;
                                                                
                                                                pfeldkraftg=1;
                                                                pfeldkraftgtoleranz=0;
                                                                pfeldkrafte=1;               
                                                                pfeldkraftetoleranz=0;
                                                                pfeldkraftb=1;
                                                                pfeldkraftbtoleranz=0;
                                                                pfeldkraftm=1;
                                                                pfeldkraftmtoleranz=0;  
                                                                pfeldkraftghomogen.setzen(0,1,0);
                                                            
	                                                            pplanarydivergenz=false;
	                                                            pplanarydivergenzort=300;
	                                                            pplanarydivergenzintensitaet=0.0001;
	                                                            
	                                                            paxialdivergenz=false;
				                                                paxialdivergenzort.setzen(0,0,0);
				                                                paxialdivergenzvektor.setzen(0,0,-1);

                                                                pfarbe.setzen(1,1,1,1);
				                                                pkurvefarbebenutzen=false;
				                                                pkurvefarbe.setzen(1,1,1,1, 1,1,1,1, 0,0,0,0, 0,0,0,0);
				                                                pausblenden=false;
				                                                peinblenden=false;
				                                                ptransparenzadditiv=true;
	                                                            ptransparenzmultiplikativ=false;

				                                                
	                                                            pkollisionz=false;
	                                                            pkollisionzort=0;
	                                                            
	                                                            pschattenz=false;
	                                                            pschattenzopazitaet=0;
	                                                            pschattenztextur=0;
	                                                            
	                                                            pskalierung=false;
	                                                            pskalierungwert=1.1;
	                                                            
	                                                            popazitaetsinus=false;
	                                                            popazitaetsinusrate=3;
	                                                            popazitaetsinusphase=0;
	                                                            popazitaetsinusphasetoleranz=0;
	                                                            popazitaetsinusratedelta=0.5;
	                                                            popazitaetsinusratedeltatoleranz=0.1;

	                                                            ptontod=0;
	                                                            ptontodlautstaerke=1;
	                                                            ptontodlautstaerketoleranz=0;
	                                                            ptontodbeugung=1;
	                                                            ptontodbeugungtoleranz=0;
	                                                            ptontodbeugungdoppler=false;
	                                                            ptontodletzterortgueltig=false;

	                                                            plichttod=0;
	                                                            plichttodliste=0;
	                                                            plichttodaddition=1;
	                                                            plichttodmultiplikation=0.95;
	                                                            plichtgeburt=0;
	                                                            plichtgeburtliste=0;
	                                                            plichtgeburtaddition=1;
	                                                            plichtgeburtmultiplikation=0.95;

};
_partikelquelle::~_partikelquelle(){
};
void _partikelquelle::kopieren(const _partikelquelle*p){

                                                                pwelt=p->pwelt;
                                                                pzone=p->pzone;
                                                                pname=p->pname; 
                                                                _listenknotenbasis<_partikelquelle>::aushaengen();
                                                                plistepartikel=p->plistepartikel;
                                                                plistepartikelquelle=p->plistepartikelquelle;
                                                                plistepartikeleinhaengenerstes=p->plistepartikeleinhaengenerstes;
                                                                ppartikelquellegeburt=p->ppartikelquellegeburt;
                                                                ppartikelquelleleben=p->ppartikelquelleleben;
                                                                ppartikelquelletod=p->ppartikelquelletod;
                                                                _listenknotenbasis<_partikelquelle>::einhaengen(plistepartikelquelle);
                                                                
                                                                ptexturliste.aushaengen();
                                                                ptexturstrings.loeschen();
                                                                ptexturiterator=0;
                                                                ptexturanzahl=0;
                                                                _listenknoten<_textur<_tb> >*tit;
                                                                if(p->ptexturliste.anfang(tit))do{
                                                                 ptexturliste.einhaengen(tit->objekt());
                                                                 ptexturliste.anfang(ptexturiterator);
                                                                }while(p->ptexturliste.naechstes(tit));
                                                                
                                                                pnetzliste.aushaengen();
                                                                pnetziterator=0;
                                                                _listenknoten<_netz>*nit;
                                                                if(p->pnetzliste.anfang(nit))do{
                                                                 pnetzliste.einhaengen(nit->objekt());
                                                                 pnetzliste.anfang(pnetziterator);
                                                                }while(p->pnetzliste.naechstes(nit));
                                                                
                                                                paktiv=p->paktiv;
                                                                
                                                                pkollision=p->pkollision;
                                                                pkollisionreflektierend=p->pkollisionreflektierend;
                                                                pkollisionabgleitend=p->pkollisionabgleitend;
                                                                pkollisionanhaftend=p->pkollisionanhaftend;  
                                                                
                                                                port=p->port;
                                                                porttoleranz=p->porttoleranz;
                                                                portraum[0]=p->portraum[0];
                                                                portraum[1]=p->portraum[1];
                                                                portraum[2]=p->portraum[2];
                                                                                                                              
                                                                pvektor=p->pvektor;
                                                                pvektortoleranz=p->pvektortoleranz;
                                                                pzentrum=p->pzentrum;
                                                                pzentrumbenutzen=p->pzentrumbenutzen;
                                                                protation=p->protation;
                                                                protationtoleranz=p->protationtoleranz;
	                                                            protationvektor=p->protationvektor;
	                                                            protationreibung=p->protationreibung;
	                                                            protationachse=p->protationachse;   
	                                                            protationachsetoleranz=p->protationachsetoleranz;                                                                  
                                                                
                                                                plebensdauerbegrenzt=p->plebensdauerbegrenzt;
                                                                plebensdauer=p->plebensdauer;
                                                                plebensdauerletzteaktivierung=p->plebensdauerletzteaktivierung;
                                                                plebensdauerpartikel=p->plebensdauerpartikel;
                                                                plebensdauerpartikeltoleranz=p->plebensdauerpartikeltoleranz;   
                                                                
                                                                pgenerationsrate=p->pgenerationsrate;
                                                                pgenerationsratetoleranz=p->pgenerationsratetoleranz;
	                                                            pgenerationsdichtedynamisch=p->pgenerationsdichtedynamisch;
	                                                            pgenerationsratesollpartikel=p->pgenerationsratesollpartikel;
	                                                            pgenerationsrateletztegenerierung=p->pgenerationsrateletztegenerierung;  
	                                                            pgenerationsrateletzterort=p->pgenerationsrateletzterort;

                                                                pmasse=p->pmasse;
                                                                pgroesse=p->pgroesse;
                                                                pgroessetoleranz=p->pgroessetoleranz;
                                                                
                                                                pfeldkraftg=p->pfeldkraftg;
                                                                pfeldkraftgtoleranz=p->pfeldkraftgtoleranz;
                                                                pfeldkrafte=p->pfeldkrafte;               
                                                                pfeldkraftetoleranz=p->pfeldkraftetoleranz;
                                                                pfeldkraftb=p->pfeldkraftb;
                                                                pfeldkraftbtoleranz=p->pfeldkraftbtoleranz;
                                                                pfeldkraftm=p->pfeldkraftm;
                                                                pfeldkraftmtoleranz=p->pfeldkraftmtoleranz;  
                                                                pfeldkraftghomogen=p->pfeldkraftghomogen;
                                                            
	                                                            pplanarydivergenz=p->pplanarydivergenz;
	                                                            pplanarydivergenzort=p->pplanarydivergenzort;
	                                                            pplanarydivergenzintensitaet=p->pplanarydivergenzintensitaet;
	                                                            
	                                                            paxialdivergenz=p->paxialdivergenz;
				                                                paxialdivergenzort=p->paxialdivergenzort;
				                                                paxialdivergenzvektor=p->paxialdivergenzvektor;

                                                                pfarbe=p->pfarbe;
				                                                pkurvefarbebenutzen=p->pkurvefarbebenutzen;
				                                                pkurvefarbe.kopieren(p->pkurvefarbe);
				                                                peinblenden=p->peinblenden;
				                                                pausblenden=p->pausblenden;
				                                                ptransparenzadditiv=p->ptransparenzadditiv;
	                                                            ptransparenzmultiplikativ=p->ptransparenzmultiplikativ;
				                                                
				                                                
	                                                            pkollisionz=p->pkollisionz;
	                                                            pkollisionzort=p->pkollisionzort;
	                                                            
	                                                            pschattenz=p->pschattenz;
	                                                            pschattenzopazitaet=p->pschattenzopazitaet;
	                                                            pschattenztextur=p->pschattenztextur;
	                                                            
	                                                            pskalierung=p->pskalierung;
	                                                            pskalierungwert=p->pskalierungwert;
	                                                            
	                                                            popazitaetsinus=p->popazitaetsinus;
	                                                            popazitaetsinusrate=p->popazitaetsinusrate;
	                                                            popazitaetsinusphase=p->popazitaetsinusphase;
	                                                            popazitaetsinusphasetoleranz=p->popazitaetsinusphasetoleranz;
	                                                            popazitaetsinusratedelta=p->popazitaetsinusratedelta;
	                                                            popazitaetsinusratedeltatoleranz=p->popazitaetsinusratedeltatoleranz;

	                                                            ptontod=p->ptontod;
	                                                            ptontodlautstaerke=p->ptontodlautstaerke;
	                                                            ptontodlautstaerketoleranz=p->ptontodlautstaerketoleranz;
	                                                            ptontodbeugung=p->ptontodbeugung;
	                                                            ptontodbeugungtoleranz=p->ptontodbeugungtoleranz;
	                                                            ptontodbeugungdoppler=p->ptontodbeugungdoppler;
	                                                            ptontodletzterortgueltig=p->ptontodletzterortgueltig;

	                                                            plichttod=p->plichttod;
	                                                            plichttodliste=p->plichttodliste;
	                                                            plichttodaddition=p->plichttodaddition;
	                                                            plichttodmultiplikation=p->plichttodmultiplikation;
	                                                            plichtgeburt=p->plichtgeburt;
	                                                            plichtgeburtliste=p->plichtgeburtliste;
	                                                            plichtgeburtaddition=p->plichtgeburtaddition;
	                                                            plichtgeburtmultiplikation=p->plichtgeburtmultiplikation;
};
_welt* _partikelquelle::welt(){
                                                                return(pwelt);
};
_zeit* _partikelquelle::zeit(){
                                                                return(pzeit);
};
_partition::_zone*_partikelquelle::zone(){
                                                                return(pzone);
};
/*
void _partikelquelle::animieren(){

                                                                if(pzone==0){
                                                                 pwelt->anfang(pzone);
                                                                };

                                                                //--------------------------------
                                                                if(plebenbegrenzt){
                                                                 if(plife>0) if(paktiv) generieren();
                                                                }else{
                                                                 if(paktiv) generieren();
                                                                };

                                                                if(plebenbegrenzt){
                                                                 plife-=1;
                                                                 if(plife<=0) {
                                                                  loeschmarkierung(true);
                                                                 };
                                                                };
                                                                pc+=1;
};
*/
void _partikelquelle::animieren(){
                                                                if(plebensdauerbegrenzt){
                                                                 if((pzeit->system()-plebensdauerletzteaktivierung)<plebensdauer) if(paktiv) generieren();
                                                                }else{
                                                                 if(paktiv) generieren();
                                                                };
                                                                if(plebensdauerbegrenzt){
																 if((pzeit->system()-plebensdauerletzteaktivierung)>=plebensdauer) _listenknotenbasis<_partikelquelle>::loeschmarkierung(true);
                                                                };
                                                                animierenlichtliste();
};
void _partikelquelle::animierenlichtliste(){
                                                                _listenknoten<_licht<_tg,_to> >*lit;
                                                                if(plichtgeburtliste){
                                                                 if(plichtgeburtliste->anfang(lit))do{
                                                                  lit->objekt()->intensitaetdynamisch(lit->objekt()->intensitaetdynamisch()*_to(plichtgeburtmultiplikation));
                                                                  if(lit->objekt()->intensitaetdynamisch()<0.001f){
                                                                   lit->loeschmarkierung(true);
                                                                   lit->loeschmarkierungobjekt(true);
                                                                  };
                                                                 }while(plichtgeburtliste->naechstes(lit));
                                                                 plichtgeburtliste->loeschenmarkiert();
                                                                };
                                                                if(plichttodliste){
                                                                 if(plichttodliste->anfang(lit))do{
                                                                  lit->objekt()->intensitaetdynamisch(lit->objekt()->intensitaetdynamisch()*_to(plichttodmultiplikation));
                                                                  if(lit->objekt()->intensitaetdynamisch()<0.001f){
                                                                   lit->loeschmarkierung(true);
                                                                   lit->loeschmarkierungobjekt(true);
                                                                  };
                                                                 }while(plichttodliste->naechstes(lit));
                                                                 plichttodliste->loeschenmarkiert();
                                                                };
};
void _partikelquelle::generieren(){
                                                                _partikel*ps;
                                                                _tg n=pgenerationsrate;
				                                                _tg u=pzeit->system();
				                                                _tg dt=(u-pgenerationsrateletztegenerierung);///Float(1000)
				                                                _tg anz=dt*n*0.001;
				                                                pgenerationsratesollpartikel=pgenerationsratesollpartikel+anz;
				                                                bool particlegenerated=false;
				                                                _vektor3<_tg> particlegeneratedposition;
				                                                if(pgenerationsdichtedynamisch==0){
				                                                 int i=int(floor(pgenerationsratesollpartikel));
				                                                 //Print "partikel soll anzahl i="+i
				                                                 if(i>2000)i=2000;
				                                                 if(i>0){
                                                                  for(int j=0;j<i;j++){
   				                                                   ps=erzeugenpartikel(ortpartikel());
                                                                  };
				                                                  pgenerationsratesollpartikel=pgenerationsratesollpartikel-_tg(i);
				                                                 };
				                                                }else{
				                                                 ps=erzeugenpartikel(ortpartikel());
				                                                 particlegeneratedposition=ps->ort();
				                                                 _tg d=pgenerationsrateletzterort.abstand(particlegeneratedposition);
				                                                 if(d>=pgenerationsdichtedynamisch){
				                                                  int ic=int(d/pgenerationsdichtedynamisch);
				                                                  _vektor3<_tg> h;
				                                                  _vektor3<_tg> pit;
				                                                  pit=pgenerationsrateletzterort;
				                                                  h=particlegeneratedposition-pit;
				                                                  _tg dh=_tg(1)/_tg(ic+1);
				                                                  h*=dh;
				                                                  pit+=h;
				                                                  for(int n=0;n<ic;n++){
				                                                   erzeugenpartikel(pit);
				                                                   pit+=h;
				                                                  };
				                                                 };
				                                                 pgenerationsrateletzterort=particlegeneratedposition;
				                                                };
			                                                    pgenerationsrateletztegenerierung=u;
};
_partikel*_partikelquelle::erzeugenpartikel(const _vektor3<_tg>&pos){
                                                                _partikel*ps;
            	                                                ps=new _partikel(pwelt,pzeit,this);
				                                                if(ptexturiterator){
				                                                 ps->textur(ptexturiterator->objekt());
				                                                 ptexturiterator=ptexturiterator->naechstes();
                                                				};     
            	                                                ps->kollision(pkollision,pkollisionreflektierend,pkollisionabgleitend,pkollisionanhaftend);
                                                                ps->ort(pos);
				                                                if(pnetziterator){
				                                                 ps->netz(pnetziterator->objekt()->duplizieren());
				                                                 ps->netz()->skalieren(groessepartikel());
				                                                 pnetziterator=pnetziterator->naechstes();
				                                                 ps->netz()->verschiebenvertex(pos);
				                                                };
                                                                ps->vektor(vektorpartikel());
                                                                ps->lebensdauer(lebensdauerpartikel());
                                                                ps->rotation(rotationpartikel());
                                                                ps->rotationvektor(protationvektor);
                                                                ps->rotationreibung(protationreibung);
                                                                ps->rotationachse()=rotationachsepartikel();
                                                                
				                                                ps->farbe(pfarbe);
				                                                ps->einblenden(peinblenden);
				                                                ps->ausblenden(pausblenden);
				                                                if(pkurvefarbebenutzen) ps->kurvefarbe(pkurvefarbe);
				                                                ps->transparenz(ptransparenzadditiv,ptransparenzmultiplikativ);
				                                                
				                                                ps->masse(pmasse);
                                                				ps->groesse(groessepartikel());
				                                                if(pzentrumbenutzen) ps->zentrum(pzentrum);
				                                                if((ps->netz())&&(ps->rotation()!=0)){
				                                                 ps->netz()->rotieren(protationachse,ps->rotation());
				                                                 ps->netz()->aktualisieren();
				                                                };
                                                                ps->feldkraftg(tolerierenkraft(pfeldkraftg,feldkraftgtoleranz()));
                                                                ps->feldkrafte(tolerierenkraft(pfeldkrafte,feldkraftetoleranz()));
                                                                ps->feldkraftb(tolerierenkraft(pfeldkraftb,feldkraftbtoleranz()));
                                                                ps->feldkraftm(tolerierenkraft(pfeldkraftm,feldkraftmtoleranz()));
                                                                if(ptontod) ps->tontod(ptontod,tontodlautstaerkepartikel(),tontodbeugungpartikel(),ptontodbeugungdoppler);
				                                                if(pplanarydivergenz) ps->planarydivergenz(pplanarydivergenzort,pplanarydivergenzintensitaet);
				                                                if(paxialdivergenz) ps->axialdivergenz(paxialdivergenzort,paxialdivergenzvektor);
                                                                if(pschattenz) ps->schattenz(pschattenztextur,pwelt);
                                                                if(pkollisionz) ps->kollisionz(pkollisionzort);
                                                                if(popazitaetsinus) ps->opazitaetsinus(popazitaetsinusrate,opazitaetsinusratedeltapartikel(),opazitaetsinusphasepartikel());
                                                                if(pskalierung) ps->skalierung(pskalierungwert);
                                                                if(plichttod) ps->lichttod(plichttod,pwelt,plichttodaddition);

				                                                if(ppartikelquelleleben) ps->partikelquelleleben(ppartikelquelleleben);//kopieren
				                                                if(ppartikelquelletod) ps->partikelquelletod(ppartikelquelletod);//kopieren, war vorher nicht kopieren !!!!!!

				                                                return(ps);
};
void _partikelquelle::aktiv(const bool o){
                                                                if((o)&(!paktiv)){
                                                                 plebensdauerletzteaktivierung=pzeit->system();
  				                                                 pgenerationsrateletztegenerierung=pzeit->system();
				                                                 pgenerationsrateletzterort=port;
				                                                 ptontodletzterortgueltig=false;
                                                                };
                                                                paktiv=o;
};
bool _partikelquelle::aktiv()const{
                                                                return(paktiv);
};



void _partikelquelle::listepartikel(_listebasis<_partikel>*l){
                                                                plistepartikel=l;
};
_listebasis<_partikel>*_partikelquelle::listepartikel(){
                                                                return(plistepartikel);
};
_liste<_partikel>*_partikelquelle::listepartikelintern(){
                                                                return(&plistepartikelintern);
};
void _partikelquelle::listepartikeleinhaengenerstes(const bool b){
                                                                plistepartikeleinhaengenerstes=b;
};
bool _partikelquelle::listepartikeleinhaengenerstes()const{
                                                                return(plistepartikeleinhaengenerstes);
};

void _partikelquelle::partikelquellegeburt(_partikelquelle*p){
                                                                ppartikelquellegeburt=p;
};
void _partikelquelle::partikelquelleleben(_partikelquelle*p){
                                                                ppartikelquelleleben=p;
};
void _partikelquelle::partikelquelletod(_partikelquelle*p){
                                                                ppartikelquelletod=p;
};
_partikelquelle*_partikelquelle::partikelquellegeburt(){
                                                                return(ppartikelquellegeburt);
};
_partikelquelle*_partikelquelle::partikelquelleleben(){
                                                                return(ppartikelquelleleben);
};
_partikelquelle*_partikelquelle::partikelquelletod(){
                                                                return(ppartikelquelletod);
};



void _partikelquelle::name(const _zeichenkette<char>&z){
                                                                pname=z;
};
_zeichenkette<char> _partikelquelle::name()const{
                                                                return(pname);
};

//-------------------------------------------------------------- TEXTURFUNKTIONEN ----------------------------------------------------------------------------------
_textur<_tb>* _partikelquelle::textur(){
                                                                _textur<_tb>*i=0;
                                                                //--------------------
                                                                if(ptexturiterator){
                                                                 i=ptexturiterator->objekt();
                                                                 ptexturiterator=ptexturiterator->naechstes();
                                                                };
                                                                return(i);
};     
_liste<_textur<_tb> >*_partikelquelle::listetextur(){
																return(&ptexturliste);
};
_liste<_zeichenkette<char> >*_partikelquelle::texturstrings(){
                                                                return(&ptexturstrings);
};
void _partikelquelle::einfuegentextur(_textur<_tb>*t){
                                                                if(t){
                                                                 ptexturliste.einhaengen(t);
                                                                 ptexturliste.anfang(ptexturiterator);
                                                                };
};
//-------------------------------------------------------------- NETZFUNKTIONEN ----------------------------------------------------------------------------------
_netz*_partikelquelle::netz(){
                                                                _netz*i=0;
                                                                //--------------------
                                                                if(pnetziterator){
                                                                 i=pnetziterator->objekt();
                                                                 pnetziterator=pnetziterator->naechstes();
                                                                };
                                                                return(i);
};
_liste<_netz>*_partikelquelle::listenetz(){
                                                                return(&pnetzliste);
};
void _partikelquelle::einfuegennetz(_netz*n){
                                                                if(n){
                                                                 pnetzliste.einhaengen(n);
                                                                 pnetzliste.anfang(pnetziterator);
                                                                };
};
void _partikelquelle::erzeugenstandardnetz(){
};
//------------------------------------------------------------- KOLLISION ---------------------------------------------------------------------------------------
void _partikelquelle::kollision(const bool k){
                                                                pkollision=k;
};
bool _partikelquelle::kollision()const{
                                                                return(pkollision);
};
void _partikelquelle::kollisionreflektierend(const _tg t){
                                                                pkollisionreflektierend=t;
};
_tg _partikelquelle::kollisionreflektierend()const{
                                                                return(pkollisionreflektierend);
};
void _partikelquelle::kollisionabgleitend(const _tg t){
                                                                pkollisionabgleitend=t;
};
_tg _partikelquelle::kollisionabgleitend()const{
                                                                return(pkollisionabgleitend);
};
void _partikelquelle::kollisionanhaftend(const _tg t){
                                                                pkollisionanhaftend=t;
};
_tg _partikelquelle::kollisionanhaftend()const{
                                                                return(pkollisionanhaftend);
};
//-------------------------------------------------------------- ORTSFUNKTIONEN ----------------------------------------------------------------------------------
void _partikelquelle::ort(const _vektor3<_tg>&o){
                                                                port=o;
};
void _partikelquelle::ort(const _tg x,const _tg y,const _tg  z){
                                                                port.setzen(x,y,z);
};
_vektor3<_tg>&_partikelquelle::ort(){
                                                                return(port);
};
_vektor3<_tg> _partikelquelle::ortpartikel()const{
                                                                
                                                                _vektor3<_tg> r;
                                                                //-------------
                                                                r.zufall();
                                                                r*=prand.berechnen(0,porttoleranz);
                                                                r+=port + (portraum[0]*prand.berechnen(0,2)-portraum[0])+ (portraum[1]*prand.berechnen(0,2)-portraum[1]) + (portraum[2]*prand.berechnen(0,2)-portraum[2]);
                                                                return(r);
};

void _partikelquelle::ortraum(const _vektor3<_tg>&vx,const _vektor3<_tg>&vy,const _vektor3<_tg>&vz){
                                                                portraum[0]=vx;
                                                                portraum[1]=vy;
                                                                portraum[2]=vz;
};
void _partikelquelle::ortraum(const unsigned int i,const _tg x,const _tg y,const _tg z){
                                                                if(i==0) portraum[0].setzen(x,y,z); else if(i==1) portraum[1].setzen(x,y,z); else portraum[2].setzen(x,y,z);
};
void _partikelquelle::ortraum(const unsigned int i,const _vektor3<_tg>&o){
                                                                if(i==0) portraum[0]=o; else if(i==1) portraum[1]=o; else portraum[2]=o;
};

_vektor3<_tg>&_partikelquelle::ortraum(const unsigned int i){   
                                                               if(i>2) return(portraum[0]); else return(portraum[i]);
};
void _partikelquelle::orttoleranz(const _tg lt){
                                                                _tg t;
                                                                //------
                                                                t=lt;
                                                                if(t<0) t=0;
                                                                porttoleranz=t;
};
_tg _partikelquelle::orttoleranz()const{
                                                                return(porttoleranz);
};

//-------------------------------------------------------------- VEKTORFUNKTIONEN ----------------------------------------------------------------------------------
void _partikelquelle::vektor(const _vektor3<_tg>&v){
                                                                pvektor=v;
};
void _partikelquelle::vektor(const _tg x,const _tg y,const _tg z){
                                                                pvektor.setzen(x,y,z);
};

_vektor3<_tg>&_partikelquelle::vektor(){
                                                                return(pvektor);
};
void _partikelquelle::vektortoleranz(const _tg vt){
                                                                _tg t;
                                                                //------
                                                                t=vt;
                                                                if(t<0) t=0;
                                                                if(t>1) t=1;
                                                                pvektortoleranz=t;
};
_vektor3<_tg> _partikelquelle::vektorpartikel()const{
                                                                _vektor3<_tg> v;
                                                                //----------------
                                                                v.zufall();
                                                                v*=pvektor.laenge();
                                                                return(v*pvektortoleranz + pvektor*(1-pvektortoleranz));
};
//-------------------------------------------------------------- ROTATION ----------------------------------------------------------------------------------

void _partikelquelle::rotation(const _tg t){
                                                                protation=t;
};
void _partikelquelle::rotationtoleranz(const _tg t){
                                                                protationtoleranz=t;
};
void _partikelquelle::rotationvektor(const _tg t){
                                                                protationvektor=t;
};
void _partikelquelle::rotationreibung(const _tg t){
                                                                protationreibung=t;
};
_vektor3<_tg>&_partikelquelle::rotationachse(){
                                                                return(protationachse);
};
void _partikelquelle::rotationachsetoleranz(const _tg v){
                                                                _tg t;
                                                                //------
                                                                t=v;
                                                                if(t<0) t=0;
                                                                if(t>1) t=1;
                                                                protationachsetoleranz=t;
};
_vektor3<_tg> _partikelquelle::rotationachsepartikel()const{
                                                                _vektor3<_tg> v;
                                                                //----------------
                                                                v.zufall();
                                                                v*=protationachse.laenge();
                                                                return(v*protationachsetoleranz + protationachse*(1-protationachsetoleranz));
};
_tg _partikelquelle::rotationpartikel()const{
                                                                return(protation+prand.berechnen(-protationtoleranz,+protationtoleranz));
};

//-------------------------------------------------------------- LEBENSDAUERFUNKTIONEN ----------------------------------------------------------------------------------
void _partikelquelle::lebensdauer(const _tg l){
                                                                _tg t;
                                                                //-------
                                                                plebensdauerbegrenzt=true;
                                                                t=l;
                                                                if(t<0) t=0;
                                                                plebensdauer=t;
                                                                
};

void _partikelquelle::lebensdauerpartikel(const _tg l){
                                                                _tg t;
                                                                //-------
                                                                t=l;
                                                                if(t<0) t=0;
                                                                plebensdauerpartikel=t;
                                                                
};

void _partikelquelle::lebensdauerpartikeltoleranz(const _tg lt){
                                                                _tg t;
                                                                //------
                                                                t=lt;
                                                                if(t<0) t=0;
                                                                if(t>1) t=1;
                                                                plebensdauerpartikeltoleranz=t;
};

_tg _partikelquelle::lebensdauerpartikel() const{
                                                                _tg r,plt;
                                                                //-----------
                                                                plt=plebensdauerpartikeltoleranz;
                                                                r=plebensdauerpartikel*(1-plt)+(plebensdauerpartikel*prand.berechnen(0,2))*plt;
                                                                return(r);      
};
//-------------------------------------------------------------- GENERATIONSFUNKTIONEN ----------------------------------------------------------------------------------
void _partikelquelle::generationsrate(const _tg freq){
                                                                _tg t;
                                                                 //-----
                                                                 t=freq;
                                                                 if(t<0) t=0;
                                                                 pgenerationsrate=t;
};
void _partikelquelle::generationsratetoleranz(const _tg i){
                                                                _tg t;
                                                                //-----
                                                                t=i;
                                                                if(t<0) t=0;
                                                                if(t>1) t=1;
                                                                pgenerationsratetoleranz=t;
};
_tg _partikelquelle::generationsrate() const{
                                                                _tg r;
                                                                //-----------
                                                                r=pgenerationsrate;
                                                                //r=plifepartikel*(1-plt)+(plifepartikel*prand.berechnen(0,2))*plt;
                                                                return(r);      
};
void _partikelquelle::generationsdichtedynamisch(const _tg d){
                                                                pgenerationsdichtedynamisch=d;
};
_tg _partikelquelle::generationsdichtedynamisch()const{
                                                                return(pgenerationsdichtedynamisch);
};
void _partikelquelle::generationsrateletztegenerierung(const _tg t){
                                                                pgenerationsrateletztegenerierung=t;
};
_tg _partikelquelle::generationsrateletztegenerierung()const{
                                                                return(pgenerationsrateletztegenerierung);
};
void _partikelquelle::generationsrateletzterort(const _vektor3<_tg>&o){
                                                                pgenerationsrateletzterort=o;
};
_vektor3<_tg>&_partikelquelle::generationsrateletzterort(){
                                                                return(pgenerationsrateletzterort);
};

void _partikelquelle::generationsratesollpartikel(const _tg t){
                                                                pgenerationsratesollpartikel=t;
};
_tg _partikelquelle::generationsratesollpartikel()const{
                                                                return(pgenerationsratesollpartikel);
};
void _partikelquelle::generationsratesollpartikelinkrementieren(const _tg t){
                                                                pgenerationsratesollpartikel+=t;
};
void _partikelquelle::generationsratesollpartikeldekrementieren(const _tg t){
                                                                pgenerationsratesollpartikel-=t;

};

//-------------------------------------------------------------- MASSE ----------------------------------------------------------------------------------
void _partikelquelle::masse(const _tg t){
                                                                pmasse=t;
};
//-------------------------------------------------------------- GRÖSSE ----------------------------------------------------------------------------------
void _partikelquelle::groesse(const _tg x){
                                                                _tg t;
                                                                //-------
                                                                t=x;
                                                                if(t<nahenull) t=nahenull;
                                                                pgroesse=t;
};
_tg _partikelquelle::groesse()const{
                                                                return(pgroesse);
};

void _partikelquelle::groessetoleranz(const _tg i){
                                                                _tg t;
                                                                //-----
                                                                t=i;
                                                                if(t<0) t=0;
                                                                if(t>1) t=1;
                                                                pgroessetoleranz=t;
};
_tg _partikelquelle::groessepartikel() const{
                                                                _tg r,plt;
                                                                //-----------
                                                                plt=pgroessetoleranz;
                                                                r=pgroesse*(1-plt)+(pgroesse*prand.berechnen(0,2))*plt;
                                                                return(r);      
};
//-------------------------------------------------------------- Skalierung ----------------------------------------------------------------------------------
void _partikelquelle::skalierung(const bool b){
                                                                pskalierung=b;
};
void _partikelquelle::skalierung(const _tg t){
                                                                pskalierungwert=t;
};
//-------------------------------------------------------------- planardivergenz ----------------------------------------------------------------------------------
void _partikelquelle::planarydivergenz(const bool b){
                                                                pplanarydivergenz=b;
};
void _partikelquelle::planarydivergenzort(const _tg t){
                                                                pplanarydivergenzort=t;
};
void _partikelquelle::planarydivergenzintensitaet(const _tg t){
                                                                pplanarydivergenzintensitaet=t;
};
//-------------------------------------------------------------- axialdivergenz ----------------------------------------------------------------------------------
void _partikelquelle::axialdivergenz(const bool b){
                                                                paxialdivergenz=b;
};
void _partikelquelle::axialdivergenzort(const _vektor3<_tg>&o){
                                                                paxialdivergenzort=o;
};
void _partikelquelle::axialdivergenzort(const _tg x,const _tg y,const _tg z){
                                                                paxialdivergenzort.setzen(x,y,z);
};

_vektor3<_tg>&_partikelquelle::axialdivergenzort(){
                                                                return(paxialdivergenzort);
};
void _partikelquelle::axialdivergenzvektor(const _vektor3<_tg>&v){

                                                                paxialdivergenzvektor=v;
};
void _partikelquelle::axialdivergenzvektor(const _tg x,const _tg y,const _tg z){
                                                                paxialdivergenzvektor.setzen(x,y,z);
};

_vektor3<_tg>&_partikelquelle::axialdivergenzvektor(){
                                                                return(paxialdivergenzvektor);
};

//-------------------------------------------------------------- farbe, kurve farbe ----------------------------------------------------------------------------------
void _partikelquelle::farbe(const _vektor4<_to>&f){
                                                                pfarbe=f;
};
_vektor4<_to>&_partikelquelle::farbe(){
                                                                return(pfarbe);
};
void _partikelquelle::opazitaet(const _to w){
                                                                _to t=w;
                                                                if(t<0) t=0;
                                                                pfarbe.w(t);
};
void _partikelquelle::kurvefarbe(const bool b){
                                                                pkurvefarbebenutzen=b;
};
_kurvehermite4<_to>&_partikelquelle::kurvefarbe(){
                                                                return(pkurvefarbe);
};
void _partikelquelle::einblenden(const bool b){
                                                                peinblenden=b;
};
void _partikelquelle::ausblenden(const bool b){
                                                                pausblenden=b;
};
void _partikelquelle::transparenzadditiv(){
                                                                ptransparenzadditiv=true;
                                                                ptransparenzmultiplikativ=false;
};
void _partikelquelle::transparenzmultiplikativ(){
                                                                ptransparenzadditiv=false;
                                                                ptransparenzmultiplikativ=true;
};
//--------------------------------------------------------------  kollision z ----------------------------------------------------------------------------------
void _partikelquelle::kollisionz(const bool b){
                                                                pkollisionz=b;
};
void _partikelquelle::kollisionzort(const _tg t){
                                                                pkollisionzort=t;
};
//-------------------------------------------------------------- schatten Z ----------------------------------------------------------------------------------
void _partikelquelle::schattenz(const bool b){
                                                                pschattenz=b;
};
void _partikelquelle::schattenzopazitaet(const _tg t){
                                                                pschattenzopazitaet=t;
};
void _partikelquelle::schattenztextur(_textur<_tb>*t){
                                                                pschattenztextur=t;
};
//-------------------------------------------------------------- sinus opazität ----------------------------------------------------------------------------------
void _partikelquelle::opazitaetsinus(const bool b){
                                                                popazitaetsinus=b;
};
void _partikelquelle::opazitaetsinusrate(const _tg t){
                                                                popazitaetsinusrate=t;
};
void _partikelquelle::opazitaetsinusphase(const _tg t){
                                                                popazitaetsinusphase=t;
};
void _partikelquelle::opazitaetsinusphasetoleranz(const _tg t){
                                                                popazitaetsinusphasetoleranz=t;
};
void _partikelquelle::opazitaetsinusratedelta(const _tg t){
                                                                popazitaetsinusratedelta=t;
};
void _partikelquelle::opazitaetsinusratedeltatoleranz(const _tg t){
                                                                popazitaetsinusratedeltatoleranz=t;
};
_tg _partikelquelle::opazitaetsinusphasepartikel()const{
				                                                return(popazitaetsinusphase+prand.berechnen(-popazitaetsinusphasetoleranz,+popazitaetsinusphasetoleranz));
};				                                                
_tg _partikelquelle::opazitaetsinusratedeltapartikel()const{
				                                                return(popazitaetsinusratedelta+prand.berechnen(-popazitaetsinusratedeltatoleranz,+popazitaetsinusratedeltatoleranz));
};				                                                
	            

//------------------------------------------------------------- TON ----------------------------------------------------------------------------------
void _partikelquelle::tontod(_ton*t){
                                                                ptontod=t;
};
void _partikelquelle::tontodlautstaerke(const _tg t){
                                                                _tg p=t;
                                                                if(p<0) p=0;
                                                                if(p>1) p=1;
                                                                ptontodlautstaerke=p;
};
void _partikelquelle::tontodlautstaerketoleranz(const _tg t){
                                                                ptontodlautstaerketoleranz=t;
};
void _partikelquelle::tontodbeugung(const _tg t){
                                                                ptontodbeugung=t;
};
void _partikelquelle::tontodbeugungtoleranz(const _tg t){
                                                                ptontodbeugungtoleranz=t;
};
void _partikelquelle::tontodbeugungdoppler(const bool b){
                                                                ptontodbeugungdoppler=b;
};
_tg _partikelquelle::tontodlautstaerkepartikel()const{
                                                                _tg l=ptontodlautstaerke+prand.berechnen(-ptontodlautstaerketoleranz,+ptontodlautstaerketoleranz);
                                                                if(l>1) l=1;
                                                                if(l<0) l=0;
                                                                return(l);
};
_tg _partikelquelle::tontodbeugungpartikel()const{
                                                                return(ptontodbeugung+prand.berechnen(-ptontodbeugungtoleranz,+ptontodbeugungtoleranz));
};
_vektor3<_tg>&_partikelquelle::tontodletzterort(){
                                                                return(ptontodletzterort);
};
void _partikelquelle::tontodletzterortgueltig(bool b){
                                                                ptontodletzterortgueltig=b;
};
bool _partikelquelle::tontodletzterortgueltig()const{
                                                                return(ptontodletzterortgueltig);
};

//------------------------------------------------------------- LICHT ----------------------------------------------------------------------------------
void _partikelquelle::lichtgeburt(_licht<_tg,_to>*l){
                                                                plichtgeburt=l;
};
_licht<_tg,_to>*_partikelquelle::lichtgeburt(){
                                                                return(plichtgeburt);
};
void _partikelquelle::lichtgeburtliste(_liste<_licht<_tg,_to> >*l){
                                                                plichtgeburtliste=l;
};
_liste<_licht<_tg,_to> >*_partikelquelle::lichtgeburtliste(){
                                                                return(plichtgeburtliste);
};
void _partikelquelle::lichtgeburtaddition(const _tg t){
                                                                plichtgeburtaddition=t;
};
_tg _partikelquelle::lichtgeburtaddition()const{
                                                                return(plichtgeburtaddition);
};
void _partikelquelle::lichtgeburtmultiplikation(const _tg t){
                                                                plichtgeburtmultiplikation=t;
};
void _partikelquelle::lichttod(_licht<_tg,_to>*l){
                                                                plichttod=l;
};
_licht<_tg,_to>*_partikelquelle::lichttod(){
                                                                return(plichttod);
};
void _partikelquelle::lichttodliste(_liste<_licht<_tg,_to> >*l){
                                                                plichttodliste=l;
};
_liste<_licht<_tg,_to> >*_partikelquelle::lichttodliste(){
                                                                return(plichttodliste);
};
void _partikelquelle::lichttodaddition(const _tg t){
                                                                plichttodaddition=t;
};
void _partikelquelle::lichttodmultiplikation(const _tg t){
                                                                plichttodmultiplikation=t;
};
//-------------------------------------------------------------- Feldfunktionen ----------------------------------------------------------------------------------
_tg _partikelquelle::tolerierenkraft(const _tg a,const _tg t)const {
                                                                _zufallsgenerator<_tg> ra;
                                                                _tg e=ra.berechnen(-t*0.5,+t*0.5);
                                                                e+=a;
                                                                if(e<0) e=0;
                                                                if(e>1) e=1;
                                                                return(e);
};
_tg _partikelquelle::feldkraftg()const{
                                                                return(pfeldkraftg);
};
_tg _partikelquelle::feldkraftgtoleranz()const{
                                                                return(pfeldkraftgtoleranz);
};
_tg _partikelquelle::feldkrafte()const{
                                                                return(pfeldkrafte);
};               
_tg _partikelquelle::feldkraftetoleranz()const{
                                                                return(pfeldkraftetoleranz);
};
_tg _partikelquelle::feldkraftb()const{
                                                                return(pfeldkraftb);
};
_tg _partikelquelle::feldkraftbtoleranz()const{
                                                                return(pfeldkraftbtoleranz);
};
_tg _partikelquelle::feldkraftm()const{
                                                                return(pfeldkraftm);
};
_tg _partikelquelle::feldkraftmtoleranz()const{
                                                                return(pfeldkraftmtoleranz);
};
void _partikelquelle::feldkraftg(const _tg f){
                                                                pfeldkraftg=f;
};
void _partikelquelle::feldkraftgtoleranz(const _tg f){
                                                                pfeldkraftgtoleranz=f;
};
void _partikelquelle::feldkrafte(const _tg f){
                                                                pfeldkrafte=f;
};               
void _partikelquelle::feldkraftetoleranz(const _tg f){
                                                                pfeldkraftetoleranz=f;
};
void _partikelquelle::feldkraftb(const _tg f){
                                                                pfeldkraftb=f;
};
void _partikelquelle::feldkraftbtoleranz(const _tg f){
                                                                pfeldkraftbtoleranz=f;
};
void _partikelquelle::feldkraftm(const _tg f){
                                                                pfeldkraftm=f;
};
void _partikelquelle::feldkraftmtoleranz(const _tg f){
                                                                pfeldkraftmtoleranz=f;
};
_vektor3<_tg>&_partikelquelle::feldkraftghomogen(){
                                                                return(pfeldkraftghomogen);
};

//-------------------------------------------------------------- VERSCHACHTELTE PARTIKELQUELLEN --------------------------------------------------------------------



char _partikelquelle::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_partikelquelle>*sd){
                                                                char r=1;
                                                                r^=sd->ladenbeginn(fn);
                                                                r^=sd->ladenverschachtelung(fn);
                                                                r^=sd->ladenwert(pname);
                                                                r^=sd->ladenwert(port);
                                                                r^=sd->ladenwert(porttoleranz);
                                                                r^=sd->ladenwert(portraum[0]);
                                                                r^=sd->ladenwert(portraum[1]);
                                                                r^=sd->ladenwert(portraum[2]);
                                                                r^=sd->ladenwert(pvektor);
                                                                r^=sd->ladenwert(pvektortoleranz);
                                                                r^=sd->ladenwert(plebensdauer);//lebensdauer der partikelquelle
                                                                r^=sd->ladenwert(plebensdauerpartikel);
                                                                r^=sd->ladenwert(plebensdauerpartikeltoleranz);
                                                                r^=sd->ladenwert(pgenerationsrate);
                                                                r^=sd->ladenwert(pgenerationsratetoleranz);
                                                                r^=sd->ladenwert(pgroesse);
                                                                r^=sd->ladenwert(pgroessetoleranz);
                                                                r^=sd->ladenwert(pfeldkraftg);
                                                                r^=sd->ladenwert(pfeldkraftgtoleranz);
                                                                r^=sd->ladenwert(pfeldkrafte);               
                                                                r^=sd->ladenwert(pfeldkraftetoleranz);
                                                                r^=sd->ladenwert(pfeldkraftb);
                                                                r^=sd->ladenwert(pfeldkraftbtoleranz);
                                                                r^=sd->ladenwert(pfeldkraftm);
                                                                r^=sd->ladenwert(pfeldkraftmtoleranz);
                                                                r^=sd->ladenwert(paktiv);
                                                                r^=sd->ladenwert(pkollisionreflektierend);
                                                                r^=sd->ladenwert(pkollisionabgleitend);
                                                                r^=sd->ladenwert(pkollisionanhaftend);
                                                                r^=sd->ladenwert(plebensdauerbegrenzt);
                                                                unsigned int ui,n;
                                                                r^=sd->ladenwert(ui);
                                                                ptexturliste.aushaengen();
                                                                ptexturstrings.loeschen();
                                                                ptexturanzahl=ui;
                                                                for(n=0;n<ui;n++){
                                                                 _zeichenkette<char>*h=new _zeichenkette<char>();
                                                                 r^=sd->ladenwert(*h);
                                                                 ptexturstrings.einhaengen(h);
                                                                };
                                                                r^=sd->ladenassoziation();
                                                                r^=sd->ladenassoziation();
                                                                sd->ladenende();
                                                                return(r);
};
void _partikelquelle::speichern(_speicherbardynamisch<_partikelquelle>*sd){
                                                                sd->speichernbeginnblock();
                                                                sd->speichernverschachtelung();    
                                                                sd->speichernwert(pname);
                                                                sd->speichernwert(port);
                                                                sd->speichernwert(porttoleranz);
                                                                sd->speichernwert(portraum[0]);
                                                                sd->speichernwert(portraum[1]);
                                                                sd->speichernwert(portraum[2]);
                                                                sd->speichernwert(pvektor);
                                                                sd->speichernwert(pvektortoleranz);
                                                                sd->speichernwert(plebensdauer);//lebensdauer der partikelquelle
                                                                sd->speichernwert(plebensdauerpartikel);
                                                                sd->speichernwert(plebensdauerpartikeltoleranz);
                                                                sd->speichernwert(pgenerationsrate);
                                                                sd->speichernwert(pgenerationsratetoleranz);
                                                                sd->speichernwert(pgroesse);
                                                                sd->speichernwert(pgroessetoleranz);
                                                                sd->speichernwert(pfeldkraftg);
                                                                sd->speichernwert(pfeldkraftgtoleranz);
                                                                sd->speichernwert(pfeldkrafte);               
                                                                sd->speichernwert(pfeldkraftetoleranz);
                                                                sd->speichernwert(pfeldkraftb);
                                                                sd->speichernwert(pfeldkraftbtoleranz);
                                                                sd->speichernwert(pfeldkraftm);
                                                                sd->speichernwert(pfeldkraftmtoleranz);
                                                                sd->speichernwert(paktiv);
                                                                sd->speichernwert(pkollisionreflektierend);
                                                                sd->speichernwert(pkollisionabgleitend);
                                                                sd->speichernwert(pkollisionanhaftend);
                                                                sd->speichernwert(plebensdauerbegrenzt);
                                                                unsigned int ui=ptexturliste.anzahl();
                                                                ptexturanzahl=ui;
                                                                sd->speichernwert(ui);
                                                                _listenknoten<_textur<_tb> >*tit;
                                                                if(ptexturliste.anfang(tit))do{
                                                                 _zeichenkette<char> h=tit->objekt()->name();
                                                                 sd->speichernwert(h);
                                                                }while(ptexturliste.naechstes(tit));
                                                                saveassociationargument(sd->datei(),sd,ppartikelquelleleben);
                                                                saveassociationargument(sd->datei(),sd,ppartikelquelletod);
                                                                sd->speichernendeblock();
};
char _partikelquelle::assoziieren(_speicherbardynamisch<_partikelquelle>*sd){
                                                                sd->assoziierenverschachtelung();
                                                                associateassociationargument(sd->datei(),sd->assoziation(),ppartikelquelleleben);
                                                                associateassociationargument(sd->datei(),sd->assoziation(),ppartikelquelletod);
                                                                return(1);
};

bool _partikelquelle::laden(_dateispeicherbarbinaer*d){
																unsigned int i,n;
																_vektor3<_tg> go0,go1,gv0,gv1;
																_vektor4<_to> oo0,oo1,ov0,ov1;

																pzone=0;	
																einhaengenspeicherung(d);
																ladenbeginn();
																d->laden(speichername());

																
																//pzeit;


																
																d->laden(pname);

																
																d->laden(plistepartikeleinhaengenerstes);
												                
																/*_liste<_textur<_tb> > ptexturliste;
																_liste<_zeichenkette<char> > ptexturstrings;
																_listenknoten<_textur<_tb> >*ptexturiterator;
																unsigned int ptexturanzahl;            */
                                                                i=ladenanzahl(d);
                                                                ptexturliste.aushaengen();
                                                                ptexturstrings.loeschen();
																ptexturiterator=0;
                                                                ptexturanzahl=i;
                                                                for(n=0;n<i;n++){
                                                                 //_zeichenkette<char>*h=new _zeichenkette<char>();
                                                                 //d->laden(*h);
                                                                 //ptexturstrings.einhaengen(h);
                                                                 ladenzeiger(d);
                                                                };
												                
																/*_liste<_netz> pnetzliste;
																_listenknoten<_netz>*pnetziterator;*/
																pnetzliste.loeschen();
																pnetziterator=0;
																d->laden(i);
																for(n=0;n<i;n++){
															     _netz*n=new _netz();
																 n->laden(d);
																 pnetzliste.einhaengen(n);
																};
																pnetzliste.anfang(pnetziterator);
												                
																d->laden(paktiv);
																d->laden(pkollision);
																d->laden(pkollisionreflektierend);
																d->laden(pkollisionabgleitend);
																d->laden(pkollisionanhaftend);
																d->laden(pkollisionz);
																d->laden(pkollisionzort);
												                
																d->laden(port);
																d->laden(porttoleranz);
																d->laden(portraum[0]);
																d->laden(portraum[1]);
																d->laden(portraum[2]);
																d->laden(pvektor);
																d->laden(pvektortoleranz);
																d->laden(pzentrumbenutzen);
																d->laden(pzentrum);
																d->laden(protation);
																d->laden(protationtoleranz);
																d->laden(protationvektor);
																d->laden(protationreibung);
																d->laden(protationachse);      
																d->laden(protationachsetoleranz);
																d->laden(plebensdauerbegrenzt);
																d->laden(plebensdauer);
																d->laden(plebensdauerletzteaktivierung);
																d->laden(plebensdauerpartikel);
																d->laden(plebensdauerpartikeltoleranz);
																d->laden(pgenerationsrate);
																d->laden(pgenerationsratetoleranz);
																d->laden(pgenerationsdichtedynamisch);
																d->laden(pgenerationsratesollpartikel);
																d->laden(pgenerationsrateletztegenerierung);    
																d->laden(pgenerationsrateletzterort);
																d->laden(pmasse);
																d->laden(pgroesse);
																d->laden(pgroessetoleranz);
																d->laden(pskalierung);
																d->laden(pskalierungwert);
																d->laden(pfeldkraftg);
																d->laden(pfeldkraftgtoleranz);
																d->laden(pfeldkrafte);               
																d->laden(pfeldkraftetoleranz);
																d->laden(pfeldkraftb);
																d->laden(pfeldkraftbtoleranz);
																d->laden(pfeldkraftm);
																d->laden(pfeldkraftmtoleranz);
																d->laden(pfeldkraftghomogen);
																d->laden(pfarbe);
																d->laden(pkurvefarbebenutzen);
																d->laden(oo0);
																d->laden(oo1);
																d->laden(ov0);
																d->laden(ov1);
																pkurvefarbe.setzen(oo0,oo1,ov0,ov1);
																d->laden(pausblenden);
																d->laden(peinblenden);
																d->laden(ptransparenzadditiv);
																d->laden(ptransparenzmultiplikativ);

																d->laden(pplanarydivergenz);
																d->laden(pplanarydivergenzort);
																d->laden(pplanarydivergenzintensitaet);
																d->laden(paxialdivergenz);
																d->laden(paxialdivergenzort);
																d->laden(paxialdivergenzvektor);
																d->laden(pschattenz);
																d->laden(pschattenzopazitaet);

																//d->laden(pschattenztexturstring);
																//pschattenztextur=0;
																ladenzeiger(d);


																d->laden(popazitaetsinus);
																d->laden(popazitaetsinusrate);
																d->laden(popazitaetsinusphase);
																d->laden(popazitaetsinusphasetoleranz);//absolut
																d->laden(popazitaetsinusratedelta);
																d->laden(popazitaetsinusratedeltatoleranz);
																ptontod=0;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
																d->laden(ptontodlautstaerke);
																d->laden(ptontodlautstaerketoleranz);
																d->laden(ptontodbeugung);
																d->laden(ptontodbeugungtoleranz);
																d->laden(ptontodbeugungdoppler);
																d->laden(ptontodletzterort);
																d->laden(ptontodletzterortgueltig);

																d->laden(i);
																plichtgeburt=0;
																if(i){
																 plichtgeburt=new _licht<_tg,_to>(0,_vektor3<_tg>(0,0,0),_vektor3<_to>(1,1,1),1);
																 plichtgeburt->laden(d);
																};
																d->laden(plichtgeburtaddition);
																d->laden(plichtgeburtmultiplikation);
																d->laden(i);
																plichttod=0;
																if(i){
																 plichttod=new _licht<_tg,_to>(0,_vektor3<_tg>(0,0,0),_vektor3<_to>(1,1,1),1);
																 plichttod->laden(d);
																};
																d->laden(plichttodaddition);
																d->laden(plichttodmultiplikation);
																d->laden(go0);
																d->laden(go1);
																d->laden(gv0);
																d->laden(gv1);
																hc.setzen(go0,go1,gv0,gv1);
																d->laden(pparticlegenerationpositionold);


																//plistepartikel;
																//plistepartikelintern; 

																d->laden(i);
																ppartikelquellegeburt=0;
																if(i){
															     ppartikelquellegeburt=new _partikelquelle(pwelt,0,plistepartikelquelle,plistepartikel);
																 ppartikelquellegeburt->laden(d);
																};

																d->laden(i);
																ppartikelquelleleben=0;
																if(i){
															     ppartikelquelleleben=new _partikelquelle(pwelt,0,plistepartikelquelle,plistepartikel);
																 ppartikelquelleleben->laden(d);
																};

																d->laden(i);
																ppartikelquelletod=0;
																if(i){
															     ppartikelquelletod=new _partikelquelle(pwelt,0,plistepartikelquelle,plistepartikel);
																 ppartikelquelletod->laden(d);
																};
																return(true);
};
void _partikelquelle::speichern(_dateispeicherbarbinaer*d){
																unsigned int i=0;
																d->speichern(speichername());
																d->laden(pname);
																
																d->speichern(plistepartikeleinhaengenerstes);
												                
																_listenknoten<_textur<_tb> >*ptit;
                                                                d->speichern(ptexturliste.anzahl());
																iterierenliste((&ptexturliste),ptit,
                                                                 //_zeichenkette<char> h=ptit->objekt()->name();
                                                                 //d->speichern(h);
                                                                 speichernzeiger(d,ptit->objekt());
                                                                );

																_listenknoten<_netz>*pnit;
																d->speichern(pnetzliste.anzahl());
																iterierenliste((&pnetzliste),pnit,pnit->objekt()->speichern(d));

																d->speichern(paktiv);
																d->speichern(pkollision);
																d->speichern(pkollisionreflektierend);
																d->speichern(pkollisionabgleitend);
																d->speichern(pkollisionanhaftend);
																d->speichern(pkollisionz);
																d->speichern(pkollisionzort);
												                
																d->speichern(port);
																d->speichern(porttoleranz);
																d->speichern(portraum[0]);
																d->speichern(portraum[1]);
																d->speichern(portraum[2]);
																d->speichern(pvektor);
																d->speichern(pvektortoleranz);
																d->speichern(pzentrumbenutzen);
																d->speichern(pzentrum);
																d->speichern(protation);
																d->speichern(protationtoleranz);
																d->speichern(protationvektor);
																d->speichern(protationreibung);
																d->speichern(protationachse);      
																d->speichern(protationachsetoleranz);
																d->speichern(plebensdauerbegrenzt);
																d->speichern(plebensdauer);
																d->speichern(plebensdauerletzteaktivierung);
																d->speichern(plebensdauerpartikel);
																d->speichern(plebensdauerpartikeltoleranz);
																d->speichern(pgenerationsrate);
																d->speichern(pgenerationsratetoleranz);
																d->speichern(pgenerationsdichtedynamisch);
																d->speichern(pgenerationsratesollpartikel);
																d->speichern(pgenerationsrateletztegenerierung);    
																d->speichern(pgenerationsrateletzterort);
																d->speichern(pmasse);
																d->speichern(pgroesse);
																d->speichern(pgroessetoleranz);
																d->speichern(pskalierung);
																d->speichern(pskalierungwert);
																d->speichern(pfeldkraftg);
																d->speichern(pfeldkraftgtoleranz);
																d->speichern(pfeldkrafte);               
																d->speichern(pfeldkraftetoleranz);
																d->speichern(pfeldkraftb);
																d->speichern(pfeldkraftbtoleranz);
																d->speichern(pfeldkraftm);
																d->speichern(pfeldkraftmtoleranz);
																d->speichern(pfeldkraftghomogen);
																d->speichern(pfarbe);
																d->speichern(pkurvefarbebenutzen);
																d->speichern(pkurvefarbe.ort(0));
																d->speichern(pkurvefarbe.ort(1));
																d->speichern(pkurvefarbe.vektor(0));
																d->speichern(pkurvefarbe.vektor(1));
																d->speichern(pausblenden);
																d->speichern(peinblenden);
																d->speichern(ptransparenzadditiv);
																d->speichern(ptransparenzmultiplikativ);

																d->speichern(pplanarydivergenz);
																d->speichern(pplanarydivergenzort);
																d->speichern(pplanarydivergenzintensitaet);
																d->speichern(paxialdivergenz);
																d->speichern(paxialdivergenzort);
																d->speichern(paxialdivergenzvektor);
																d->speichern(pschattenz);
																d->speichern(pschattenzopazitaet);

																//if(pschattenztextur==0) pschattenztexturstring="null"; else pschattenztexturstring=pschattenztextur->name();
																//d->speichern(pschattenztexturstring);
																speichernzeiger(d,pschattenztextur);

																d->speichern(popazitaetsinus);
																d->speichern(popazitaetsinusrate);
																d->speichern(popazitaetsinusphase);
																d->speichern(popazitaetsinusphasetoleranz);//absolut
																d->speichern(popazitaetsinusratedelta);
																d->speichern(popazitaetsinusratedeltatoleranz);
																//ptontod=0;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
																d->speichern(ptontodlautstaerke);
																d->speichern(ptontodlautstaerketoleranz);
																d->speichern(ptontodbeugung);
																d->speichern(ptontodbeugungtoleranz);
																d->speichern(ptontodbeugungdoppler);
																d->speichern(ptontodletzterort);
																d->speichern(ptontodletzterortgueltig);

																if(plichtgeburt) i=1; else i=0;
																d->speichern(i);
																if(i) plichtgeburt->speichern(d);
																d->speichern(plichtgeburtaddition);
																d->speichern(plichtgeburtmultiplikation);

																if(plichttod) i=1; else i=0;
																d->speichern(i);
																if(i) plichttod->speichern(d);
																d->speichern(plichttodaddition);
																d->speichern(plichttodmultiplikation);
																d->speichern(hc.ort(0));
																d->speichern(hc.ort(1));
																d->speichern(hc.vektor(0));
																d->speichern(hc.vektor(1));
																d->speichern(pparticlegenerationpositionold);


																//plistepartikel;
																//plistepartikelintern; 
																if(ppartikelquellegeburt) i=1; else i=0;
																d->speichern(i);
																if(i) ppartikelquellegeburt->speichern(d);

																if(ppartikelquelleleben) i=1; else i=0;
																d->speichern(i);
																if(i) ppartikelquelleleben->speichern(d);

																if(ppartikelquelletod) i=1; else i=0;
																d->speichern(i);
																if(i) ppartikelquelletod->speichern(d);
};
bool _partikelquelle::assoziieren(){
																if(zeigergeladen()){
																 loeschenzeiger();
																 unsigned i,a;
																 a=ladenanzahl();
																 for(i=0;i<a;i++){
																  _textur<_tb>*t;
																  assoziierenzeiger(t);
																  ptexturliste.einhaengen(t);
																 };
																 ptexturliste.anfang(ptexturiterator);
																 assoziierenzeiger(pschattenztextur);
																};
																return(true);
};
void _partikelquelle::einhaengendialog(_dynamischerdialog*d){
                                                                d->editierbar(this);
                                                                d->loeschensektion();
                                                                d->addierensektion(L"Partikelquelle");
                                                                d->sektion(L"Partikelquelle")->offen(true);
                                                                d->einhaengen(L"Partikelquelle",L"Name",pname);
                                                                d->einhaengen(L"Partikelquelle",L"Ort",port);
                                                                d->einhaengen(L"Partikelquelle",L"Ort Toleranz [0..1]",porttoleranz);
                                                                d->einhaengen(L"Partikelquelle",L"Ort Raum Achse 0",portraum[0]);
                                                                d->einhaengen(L"Partikelquelle",L"Ort Raum Achse 1",portraum[1]);
                                                                d->einhaengen(L"Partikelquelle",L"Ort Raum Achse 2",portraum[2]);
                                                                d->einhaengen(L"Partikelquelle",L"Richtung",pvektor);
                                                                d->einhaengen(L"Partikelquelle",L"Richtung Toleranz [0..1]",pvektortoleranz);
                                                                d->einhaengen(L"Partikelquelle",L"Lebensdauer begrenzt",plebensdauerbegrenzt);
                                                                d->einhaengen(L"Partikelquelle",L"Lebensdauer [f]",plebensdauer);//lebensdauer der partikelquelle
                                                                d->einhaengen(L"Partikelquelle",L"Lebensdauer der Partikel [f]",plebensdauerpartikel);
                                                                d->einhaengen(L"Partikelquelle",L"Lebensdauer der Partikel Toleranz [0..1]",plebensdauerpartikeltoleranz);
                                                                d->einhaengen(L"Partikelquelle",L"Generationsrate [objekt/f]",pgenerationsrate);
                                                                d->einhaengen(L"Partikelquelle",L"Generationsrate Toleranz [0..1]",pgenerationsratetoleranz);
                                                                d->einhaengen(L"Partikelquelle",L"Partikelgröße [m]",pgroesse);
                                                                d->einhaengen(L"Partikelquelle",L"Partikelgröße Toleranz [0..1]",pgroessetoleranz);
                                                                d->einhaengen(L"Partikelquelle",L"Gravitationsanteil [0..1]",pfeldkraftg);
                                                                d->einhaengen(L"Partikelquelle",L"Gravitationsanteil Toleranz [0..1]",pfeldkraftgtoleranz);
                                                                d->einhaengen(L"Partikelquelle",L"Elektrischer Feldanteil [0..1]",pfeldkrafte);               
                                                                d->einhaengen(L"Partikelquelle",L"Elektrischer Feldanteil Toleranz [0..1]",pfeldkraftetoleranz);
                                                                d->einhaengen(L"Partikelquelle",L"Magnetfeldanteil [0..1]",pfeldkraftb);
                                                                d->einhaengen(L"Partikelquelle",L"Magnetfeldanteil Toleranz [0..1]",pfeldkraftbtoleranz);
                                                                d->einhaengen(L"Partikelquelle",L"Mechanischer Feldanteil [0..1]",pfeldkraftm);
                                                                d->einhaengen(L"Partikelquelle",L"Mechanischer Feldanteil Toleranz [0..1]",pfeldkraftmtoleranz);
                                                                d->einhaengen(L"Partikelquelle",L"Aktivitaet",paktiv);
                                                                d->einhaengen(L"Partikelquelle",L"Kollision reflektierend",pkollisionreflektierend);
                                                                d->einhaengen(L"Partikelquelle",L"Kollision abgleitend",pkollisionabgleitend);
                                                                d->einhaengen(L"Partikelquelle",L"Kollision anhaftend",pkollisionanhaftend);
                                
};
void _partikelquelle::auslesendialog(_dynamischerdialog*d){
                                                                d->auslesen(L"Partikelquelle",L"Name",pname);
                                                                d->auslesen(L"Partikelquelle",L"Ort",port);
                                                                d->auslesen(L"Partikelquelle",L"Ort Toleranz [0..1]",porttoleranz);
                                                                d->auslesen(L"Partikelquelle",L"Ort Raum Achse 0",portraum[0]);
                                                                d->auslesen(L"Partikelquelle",L"Ort Raum Achse 1",portraum[1]);
                                                                d->auslesen(L"Partikelquelle",L"Ort Raum Achse 2",portraum[2]);
                                                                d->auslesen(L"Partikelquelle",L"Richtung",pvektor);
                                                                d->auslesen(L"Partikelquelle",L"Richtung Toleranz [0..1]",pvektortoleranz);
                                                                d->auslesen(L"Partikelquelle",L"Lebensdauer begrenzt",plebensdauerbegrenzt);
                                                                d->auslesen(L"Partikelquelle",L"Lebensdauer [f]",plebensdauer);//lebensdauer der partikelquelle
                                                                d->auslesen(L"Partikelquelle",L"Lebensdauer der Partikel [f]",plebensdauerpartikel);
                                                                d->auslesen(L"Partikelquelle",L"Lebensdauer der Partikel Toleranz [0..1]",plebensdauerpartikeltoleranz);
                                                                d->auslesen(L"Partikelquelle",L"Generationsrate [objekt/f]",pgenerationsrate);
                                                                d->auslesen(L"Partikelquelle",L"Generationsrate Toleranz [0..1]",pgenerationsratetoleranz);
                                                                d->auslesen(L"Partikelquelle",L"Partikelgröße [m]",pgroesse);
                                                                d->auslesen(L"Partikelquelle",L"Partikelgröße Toleranz [0..1]",pgroessetoleranz);
                                                                d->auslesen(L"Partikelquelle",L"Gravitationsanteil [0..1]",pfeldkraftg);
                                                                d->auslesen(L"Partikelquelle",L"Gravitationsanteil Toleranz [0..1]",pfeldkraftgtoleranz);
                                                                d->auslesen(L"Partikelquelle",L"Elektrischer Feldanteil [0..1]",pfeldkrafte);   
                                                                d->auslesen(L"Partikelquelle",L"Elektrischer Feldanteil Toleranz [0..1]",pfeldkraftetoleranz);
                                                                d->auslesen(L"Partikelquelle",L"Magnetfeldanteil [0..1]",pfeldkraftb);
                                                                d->auslesen(L"Partikelquelle",L"Magnetfeldanteil Toleranz [0..1]",pfeldkraftbtoleranz);
                                                                d->auslesen(L"Partikelquelle",L"Mechanischer Feldanteil [0..1]",pfeldkraftm);
                                                                d->auslesen(L"Partikelquelle",L"Mechanischer Feldanteil Toleranz [0..1]",pfeldkraftmtoleranz);
                                                                d->auslesen(L"Partikelquelle",L"Aktivitaet",paktiv);
                                                                d->auslesen(L"Partikelquelle",L"Kollision reflektierend",pkollisionreflektierend);
                                                                d->auslesen(L"Partikelquelle",L"Kollision abgleitend",pkollisionabgleitend);
                                                                d->auslesen(L"Partikelquelle",L"Kollision anhaftend",pkollisionanhaftend);

};

//******************************************************************************************************************************************************************************************************
//                                                              P A R T I K E L Q U E L L E S P R I T E 
//******************************************************************************************************************************************************************************************************
_partikelquellesprite::_partikelquellesprite(_listebasis<_partikelquelle >*l,_listebasis<_partikel>*lp,_welt*w,_zeit*z,_vektor3<_tg> o,_vektor3<_tg> v,_tg life,_textur<_tb>*tex):_partikelquelle(w,z,l,lp,o,v,life,tex){
                                                                //prot=0;
                                                                //prottol=0;
                                                                pspriteliste=w;
};
_partikelquellesprite::_partikelquellesprite(_listebasis<_partikelquelle >*l,_listebasis<_partikel>*lp,_welt*w,_zeit*z,_partition::_zone*zone,_vektor3<_tg> o,_vektor3<_tg> v,_tg life,_textur<_tb>*tex):_partikelquelle(w,z,l,lp,o,v,life,tex){
                                                                //prot=0;
                                                                //prottol=0;
                                                                pspriteliste=w;
};

_partikelquellesprite::~_partikelquellesprite(){
};
void _partikelquellesprite::spriteliste(_listebasis<_sprite>*l){
                                                                pspriteliste=l;
};
_listebasis<_sprite>*_partikelquellesprite::spriteliste(){
                                                                return(pspriteliste);
};
void _partikelquellesprite::kopieren(const _partikelquellesprite*p){
                                                                _partikelquelle::kopieren(p);
                                                                //prot=p->prot;
                                                                //prottol=p->prottol;
                                                                pspriteliste=p->pspriteliste;
                                                                
};
void _partikelquellesprite::generieren(){
                                                                _tg l;
                                                                _vektor3<_tg> vx;
                                                                _vektor3<_tg> vy;
                                                                _partikelsprite*ps;
                                                                _tg n,i;
                                                                _zufallsgenerator<_tg> ra;
                                                                //-------------------------------------
                                                                n=generationsrate();
                                                                for(i=0;i<=n;i+=1){
                                                                 l=groessepartikel();
                                                                 vx.setzen(l,0,0);
                                                                 vy.setzen(0,l,0);
                                                                 ps=new _partikelsprite(welt(),zeit(),this,pspriteliste,ortpartikel(),vektorpartikel(),vx,vy,lebensdauerpartikel(),textur());
                                                                 //ps->rotationvektor(  prot*(1-prottol)  + ra.berechnen(0,prot)*prottol);
                                                                 ps->_sprite::rotation(rotationpartikel());
                                                                 //if(reflektiv()) ps->reflektiv(true); else ps->reflektiv(false);
                                                                 //if(projektil()) ps->projektil(true); else ps->projektil(false);
                                                                 ps->kollision(kollision(),kollisionreflektierend(),kollisionabgleitend(),kollisionanhaftend());
                                                                 ps->feldkraftg(tolerierenkraft(feldkraftg(),feldkraftgtoleranz()));
                                                                 ps->feldkrafte(tolerierenkraft(feldkrafte(),feldkraftetoleranz()));
                                                                 ps->feldkraftb(tolerierenkraft(feldkraftb(),feldkraftbtoleranz()));
                                                                 ps->feldkraftm(tolerierenkraft(feldkraftm(),feldkraftmtoleranz()));
                                                                 if(partikelquelleleben()) ps->partikelquelleleben(partikelquelleleben());
                                                                 if(partikelquelletod()) ps->partikelquelletod(partikelquelletod());
                                                                 //n-=1;
                                                                 //generationszaehlerdekrementieren();
                                                                };
};
//void _partikelquellesprite::rotation(const _tg r){
//                                                                prot=r;
//};
/*
void _partikelquellesprite::rotationtoleranz(const _tg rv){
                                                                _tg i;
                                                                //---------
                                                                i=rv;
                                                                if(i<0) i=0;
                                                                if(i>1) i=1;
                                                                prottol=i;
};*/
char _partikelquellesprite::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_partikelquellesprite>*sd){
                                                                char r=1;
                                                                r^=sd->ladenbeginn(fn);
                                                                r^=sd->ladenverschachtelung(fn);
                                                                //r^=sd->ladenwert(prot);
                                                                //r^=sd->ladenwert(prottol);
                                                                sd->ladenende();
                                                                return(r);

};
void _partikelquellesprite::speichern(_speicherbardynamisch<_partikelquellesprite>*sd){
                                                                sd->speichernbeginnblock();
                                                                sd->speichernverschachtelung();    
                                                                //sd->speichernwert(prot);
                                                                //sd->speichernwert(prottol);
                                                                sd->speichernendeblock();
};
char _partikelquellesprite::assoziieren(_speicherbardynamisch<_partikelquellesprite>*sd){
                                                                sd->assoziierenverschachtelung();
                                                                return(1);
};
void _partikelquellesprite::einhaengendialog(_dynamischerdialog*d){
                                                                _partikelquelle::einhaengendialog(d);
                                                                d->addierensektion(L"Partikelquellesprite");
                                                                d->sektion(L"Partikelquellesprite")->offen(true);
                                                                //d->einhaengen(L"Partikelquellesprite",L"Rotation [w/f]",prot);
                                                                //d->einhaengen(L"Partikelquellesprite",L"Rotation Toleranz [0..1]",prottol);
                                                                
};
void _partikelquellesprite::auslesendialog(_dynamischerdialog*d){
                                                                _partikelquelle::auslesendialog(d);
                                                                //d->auslesen(L"Partikelquellesprite",L"Rotation [w/f]",prot);
                                                                //d->auslesen(L"Partikelquellesprite",L"Rotation Toleranz [0..1]",prottol);
};
//******************************************************************************************************************************************************************************************************
//                                                              P A R T I K E L Q U E L L E S P R I T E P H Y S I K A L I S C H 
//******************************************************************************************************************************************************************************************************

_partikelquellespritephysikalisch::_partikelquellespritephysikalisch(_listebasis<_partikelquelle >*l,_listebasis<_partikel>*lp,_welt*w,_zeit*z,_partition::_zone*zone,_vektor3<_tg> o,_vektor3<_tg> v,_tg life,_textur<_tb>*tex):_partikelquellesprite(l,lp,w,z,o,v,life,tex){
                                                                pdichte=4;
                                                                pdichtetoleranz=0;
                                                                pdurchmesser=4;
                                                                pdurchmessertoleranz=0;
                                                                pladungsdichte=0.01;
                                                                pladungsdichtetoleranz=0;
                                                                pfeld=true;
                                                                parrow=0;
                                                                pfeldfreq=0.08;
                                                                preibung=1;
                                                                ptemperatur=0.001;
};

_partikelquellespritephysikalisch::~_partikelquellespritephysikalisch(){
                                                                devisualisieren();
};

void _partikelquellespritephysikalisch::animieren(){
                                                                _partikelquelle::animieren();
                                                                if(pfeld){
                                                                 if(parrow){
                                                                  _vektor3<_tg> v;
                                                                  v=feldvektor();
                                                                  parrow->ort(0,ort()-v*4);
                                                                  parrow->ort(1,ort()+v*4);
                                                                 };
                                                                };
};

void _partikelquellespritephysikalisch::generieren(){
                                                                _tg l;
                                                                _vektor3<_tg> vx;
                                                                _vektor3<_tg> vy;
                                                                _partikelspritephysikalisch*ps;
                                                                _tg n;
                                                                _zufallsgenerator<_tg> ra;
                                                                _tg d;
                                                                _tg dm;
                                                                _tg ld;
                                                                //-------------------------------------
                                                                for(n=0;n<generationsrate();n+=1){
                                                                 l=groessepartikel();
                                                                 vx.setzen(l,0,0);
                                                                 vy.setzen(0,l,0);
                                                                 d=pdichte;
                                                                 dm=pdurchmesser;
                                                                 ld=pladungsdichte;
                                                                 ps=new _partikelspritephysikalisch(welt(),zeit(),this,spriteliste(),ortpartikel(),vektorpartikel(),vx,vy,lebensdauerpartikel(),textur(),d,dm,ld);
                                                                 //ps->rotationvektor(prot*(1-prottol)  + ra.berechnen(0,prot)*prottol);
                                                                 //if(reflektiv()) ps->reflektiv(true); else ps->reflektiv(false);
                                                                 //if(projektil()) ps->projektil(true); else ps->projektil(false);
                                                                };
};
void _partikelquellespritephysikalisch::feld(const bool b){
                                                                pfeld=b;
};
bool _partikelquellespritephysikalisch::feld() const{
                                                                return(pfeld);
};

void _partikelquellespritephysikalisch::feldfrequenz(const _tg b){
                                                                pfeldfreq=b;
};

_tg  _partikelquellespritephysikalisch::feldfrequenz() const{
                                                                return(pfeldfreq);
};

void _partikelquellespritephysikalisch::reibung(const _tg b){
                                                                preibung=b;
};

_tg  _partikelquellespritephysikalisch::reibung() const{
                                                                return(preibung);
};

void _partikelquellespritephysikalisch::temperatur(const _tg b){
                                                                ptemperatur=b;
};

_tg  _partikelquellespritephysikalisch::temperatur() const{
                                                                return(ptemperatur);
};

_vektor3<_tg> _partikelquellespritephysikalisch::feldvektor() {
                                                                _vektor3<_tg> v;
                                                                //------------------
                                                                v.setzen(cos(_partikelquelle::zeit()->system()*pfeldfreq),0,sin(_partikelquelle::zeit()->system()*pfeldfreq));//B-feld;
                                                                return(v);
};
void _partikelquellespritephysikalisch::visualisieren(){
                                                                _vektor4<_to> col;
                                                                _vektor3<_tg> v;
                                                                devisualisieren();
                                                                col.setzen(0,0.6f,1,0);
                                                                v=feldvektor();
                                                                parrow=new _weltdebugpfeil(welt(),ort()-v*4,ort()+v*4,0.2,0.1,col);
};
void _partikelquellespritephysikalisch::devisualisieren(){
                                                                if(parrow){
                                                                 delete parrow;
                                                                 parrow=0;
                                                                };
};
//******************************************************************************************************************************************************************************************************
//                                                              P A R T I K E L 
//******************************************************************************************************************************************************************************************************

_partikel::_partikel(_welt*w,_zeit*z,_partikelquelle*pq):_listenknotenbasis<_partikel >(){
                                                                pwelt=w;
                                                                pzeit=z;
                                                                pzeitletzte=pzeit->system();
                                                                pzone=0;
                                                                psektor=0;
	                                                            pfanim=1;
	                                                            pfanimnorm=1;                                                                
                                                                ppartikelquelle=pq;
 				                                                if(ppartikelquelle->listepartikeleinhaengenerstes()){
				                                                 _listenknotenbasis<_partikel>::einhaengenerstes(ppartikelquelle->listepartikel());
				                                                }else{
				                                                 _listenknotenbasis<_partikel>::einhaengen(ppartikelquelle->listepartikel());
				                                                };
                                                				pknotenintern=ppartikelquelle->listepartikelintern()->einhaengen(this);
                                                				ppartikelquelleleben=0;
                                                				ppartikelquelletod=0;
                                                				
                                                				//pschattenliste=ppartikelquelle->schattenliste();
	                                                            ptextur=0;
	                                                            pnetz=0;

                                                                pkollision=false;
	                                                            pkollisionz=false;
                                                                palter=0;
                                                                plebensdauermaximal=1000;
                                                                pzentrumbenutzen=false;
                                                                protation=0;
	                                                            protationvektor=0;
	                                                            protationreibung=0.97;
	                                                            protationachse.setzen(0,0,1);
	            
                                                                pgroesse=1;
	                                                            pskalierung=false;
	                                                            pfeldkraftg=1;
	                                                            pfeldkraftg=0;
	                                                            pfeldkraftg=0;
	                                                            pfeldkraftg=0;
                                                                pfeldkraftghomogen.setzen(0,-1,0); 

	                                                            pfarbe.setzen(1,1,1,1);
	                                                            pkurvefarbebenutzen=false;
                                                                pausblenden=false;
	                                                            peinblenden=false;
	                                                            popazitaetzeichnung=1;
	                                                            popazitaetexternekontrolle=1; 
	                                                            ptransparenzmultiplikativ=false;
	                                                            ptransparenzadditiv=true;
	                                                            
                                                                pplanarydivergenz=false;
                                                                paxialdivergenz=false;
	                                                            pschattenz=false;
	                                                            popazitaetsinus=false;
	                                                            ptontod=0;
                                                                plichttod=0;
                                                                bestimmensektor();
                                                                plebensdauerstart=pzeit->system();
};
_partikel::~_partikel(){
                                                                deletesecure(pknotenintern);
                                                                deletesecure(pnetz);
                                                                pschattenliste.loeschen();
                                                                deletesecure(ppartikelquelleleben);
                                                                deletesecure(ppartikelquelletod);
};
void _partikel::partikelquelleleben(_partikelquelle*pql){
                                                                deletesecure(ppartikelquelleleben);
                                                                ppartikelquelleleben=new _partikelquelle(pql);
};
void _partikel::partikelquelletod(_partikelquelle*pqt){
                                                                deletesecure(ppartikelquelletod);
                                                                ppartikelquelletod=new _partikelquelle(pqt);
};

void _partikel::bestimmensektor(){
                                                                _partition::_zone*zit;
                                                                _partition::_sektor*sit;
                                                                _partition::_sektor*sektor;
                                                                if(pwelt->anfang(zit))do{
                                                                 if(zit->anfang(sit))do{
                                                                  sektor=zit->sektor(port);
                                                                  if(sektor){
                                                                   pzone=zit;
                                                                   psektor=sit;
                                                                  };
                                                                 }while(zit->naechstes(sit));
                                                                }while(pwelt->naechstes(zit));
                                                                
};
/*
void _partikel::beschleunigengravitation(){
                                                                _vektor3<_tg> g;
                                                                //--------------------------------
                                                                g=pwelt->gravitation(port);
                                                                pvektor+=g;
};
*/
void _partikel::animieren(){
				                                                if(ppartikelquelleleben) ppartikelquelleleben->ort(port);
                                                                animierenbewegung();
                                                                animierenlebensdauer();
                                                                animierenoptik();
};
void _partikel::animierenbewegung(){
				                                                _tg timenew=pzeit->system();
				                                                _tg timed=timenew-pzeitletzte;
				                                                pfanim=timed/1000;
				                                                pfanimnorm=pfanim/_tg(0.0166666666);
				                                                pfanimnorm*=pfanimnorm;
				                                                if(pfanimnorm<0.05) pfanimnorm=0.05;
				                                                if(pfanimnorm>4) pfanimnorm=4;
				                                                pzeitletzte=timenew;
				                                                _vektor3<_tg> grav;
				                                                _tg reibung=(1-0.0001)*60;//'1%/ 16.66msec
                                                				
				                                                pvektor*=(pmasse*0.97);//'friction*fanim)//exp(0.97,fanimnorm)?
			                                                    //vector.mul(mass*friction*fanim)
				                                                if(pfeldkraftg!=0){
				                                                 grav+=pfeldkraftghomogen;
				                                                 if(pwelt) grav+=pwelt->gravitation(port);
				                                                 grav*=_tg(0.016666)*pfanimnorm;
				                                                 pvektor+=grav;
				                                                };
				                                                if(pplanarydivergenz){
				                                                 _tg d=port.y()-pplanarydivergenzort;
				                                                 d=pplanarydivergenzintensitaet*d;
				                                                 grav.setzen(0,-d,0);
				                                                 grav*=_tg(0.016666)*pfanimnorm;
				                                                 pvektor+=grav;
				                                                };
				                                                if((paxialdivergenz)&&(ppartikelquelle)){
				                                                 _vektor3<_tg> h;
				                                                 _tg l=paxialdivergenzvektor.laenge();
				                                                 _vektoranalysis3<_tg> V3;
				                                                 _tg para;
				                                                 V3.lotpunktgerade(port,ppartikelquelle->axialdivergenzort(),ppartikelquelle->axialdivergenzvektor(),h,para);
				                                                 h*=l;
				                                                 grav+=h*(_tg(0.016666)*pfanimnorm);
				                                                 pvektor+=grav;
				                                                };
				                                                if(pkollisionz){
				                                                 _tg sz=pkollisionzort;
				                                                 if(port.z()>sz){
				                                                  if((port.z()+pvektor.z())<=sz){ 
				                                                   pvektor.z(pvektor.z()*-1);
				                                                   pvektor*=0.5;
				                                                   protationvektor*=(0.8*pfanimnorm);
				                                                  };
				                                                 }else{
				                                                  if((port.z()+pvektor.z())>=sz){
				                                                   pvektor.z(pvektor.z()*-1);
				                                                   pvektor*=0.5;
				                                                   protationvektor*=(0.8*pfanimnorm);
				                                                  };
				                                                 };
				                                                };
				                                                if(pnetz){
				                                                 pnetz->verschiebenvertex(pvektor);
				                                                 //pnetz->verschiebenmitte(middle.add(vector)
				                                                };
				                                                port+=pvektor;
};
				/*
void _partikel::bewegen(){
                                                                _partition::_sektor*s;
                                                                _vektor3<_tg> g;
                                                                bool kollidiert;
                                                                //--------------------------------
                                                                pvector*=pwelt->viskositaet()*pmasse;
                                                                if((pzone!=0)&&(pkollision==true)){
                                                                 s=pzone->sektor(plocus);
                                                                 if(s) {
                                                                  if(preflektiv){
                                                                   pvector=s->bewegungsvektorreflektiv(plocus,pvector,kollidiert);
                                                                  }else{
                                                                   pvector=s->bewegungsvektor(plocus,pvector,s,kollidiert);
                                                                  };
                                                                  if(kollidiert){
                                                                   if(ppqdeath){
                                                                    ppqdeath->ort(plocus);
                                                                    ppqdeath->vektor(pvector);
                                                                    ppqdeath->generieren();
                                                                    loeschmarkierung(true);
                                                                   };
                                                                  };
                                                                 };
                                                                };
                                                                plocus+=pvector;
                                                                if(ppqlife){
                                                                 ppqlife->ort(plocus);
                                                                 ppqlife->vektor(pvector*0.5);
                                                                 ppqlife->generieren();
                                                                };
};*/
void _partikel::animierenoptik(){
				                                                if(fabs(protationvektor)>nahenull){
				                                                 protation+=protationvektor*_tg(0.01666666)*pfanimnorm;
				                                                 if(pnetz){ 
				                                                  pnetz->rotieren(protationachse,protationvektor*_tg(0.01666666)*pfanimnorm);
                                                				  pnetz->aktualisieren();
				                                                 };
				                                                 protationvektor*=(1-protationreibung);
				                                                };
				                                                if((peinblenden)&&(pausblenden)){
				                                                 popazitaetzeichnung=_to(sin(_ph*alterprozent()*180))*pfarbe.w();
                                                				}else if((peinblenden==false)&&(pausblenden)){
				                                                 popazitaetzeichnung=pfarbe.w();
				                                                 if(alterprozent()>0.5){
				                                                  popazitaetzeichnung=_to(sin(_ph*alterprozent()*180))*pfarbe.w();
                                                				 };
                                                				}else if((peinblenden)&&(pausblenden==false)){
                                                 				 popazitaetzeichnung=pfarbe.w();
				                                                 if(alterprozent()<0.5){
				                                                  popazitaetzeichnung=_to(sin(_ph*(1-alterprozent())*180))*pfarbe.w();
                                                				 };
				                                                };

				                                                if(pkurvefarbebenutzen){
				                                                 pkurvefarbe.berechnen(_to(alterprozent()));
				                                                };
				                                                _listenknoten<_schatten<_tg,_to> >*sit;
				                                                if(pschattenliste.anfang(sit))do{
				                                                 sit->objekt()->aktualisieren();
				                                                 sit->objekt()->opazitaet(_to(0.2f)*popazitaetzeichnung*popazitaetexternekontrolle);
                                                				}while(pschattenliste.naechstes(sit));
				                                                if(pskalierung){
				                                                 if(pnetz){
				                                                  pnetz->aktualisierenpolygonmitte();
				                                                  _polygon*pit;
				                                                  pnetz->anfang(pit);
				                                                  pnetz->skalieren(pit->mitte(),pskalierungwert);
				                                                 }else{
				                                                  pgroesse+=pskalierungwert;
				                                                 };
				                                                };
};
void _partikel::zeichnen(_grafik*g){
                                                                if(pnetz) pnetz->zeichnen(g);
};
void _partikel::zeichnenschatten(_grafik*g){
                                                                _listenknoten<_schatten<_tg,_to> >*sit;
                                                                if(pschattenliste.anfang(sit))do{
                                                                 sit->objekt()->zeichnen(g);
                                                                }while(pschattenliste.naechstes(sit));
};
_tg _partikel::alterprozent(){//von 0 bis eins
                                                                _tg t=pzeit->system();
                                                                palter=t-plebensdauerstart;
                                                                return(palter/plebensdauermaximal);
};
bool _partikel::pruefenlebensdauer(){
                                                                
                                                                if(alterprozent()>=1){
                                                                 return(false);
                                                                };
                                                                return(true);
};
void _partikel::animierenlebensdauer(){
				                                                if(pruefenlebensdauer()==false){
                                                                 loeschmarkierung(true);
				                                                 //------------------ 
				                                                 if(ptontod){
				                                                  if(ptontodbeugungdoppler==false){
				                                                   //playsoundstretched(sounddeath,sounddeathvolume,sounddeathpitch,sounddeathpitch)
				                                                  }else{
				                                                   _tg doppler=0;
				                                                   if(ppartikelquelle){
				                                                    if(ppartikelquelle->tontodletzterortgueltig()){
				                                                     _vektor3<_tg> d;
				                                                     _vektor3<_tg> n;
                                                				  	 d=port-ppartikelquelle->tontodletzterort();
                                                					 _tg dl=d.laenge();
					                                                 n=d;
					                                                 n*=0.5;
					                                                 n+=ppartikelquelle->tontodletzterort();
                                                				   	 n*=-1;
					                                                 n.normalisieren();
					                                                 d.normalisieren();
					                                                 if(dl>2) dl=2;
					                                                 doppler=(n*d)*0.4*dl;
				                                                    };
                                                				   };
				                                                   //playsoundstretched(ptontod,ptontodlautstaerke,ptontodbeugung+doppler,ptontodbeugung+doppler);//!!!!!!!!!!!!!!!!
				                                                  };
				                                                  
				                                                 };
                                                                 //---------------------
				                                                 
                                                				 if(ppartikelquelle){ 
				                                                  ppartikelquelle->tontodletzterort()=port;
				                                                  ppartikelquelle->tontodletzterortgueltig(true);
                                                				 };

                                                				 if(ppartikelquelletod){
				                                                  ppartikelquelletod->ort(port);
                                                				  ppartikelquelletod->aktiv(true);
				                                                  ppartikelquelletod->generationsrateletztegenerierung(pzeit->system()-1000);
                                                				  ppartikelquelletod->generieren();
				                                                  ppartikelquelletod->aktiv(false);
				                                                  deletesecure(ppartikelquelletod);
				                                                 };
				                                                 
				                                                 if(plichttod){
				                                                  _licht<_tg,_to>*lit=new _licht<_tg,_to>(plichttod);
				                                                  //lit->kopieren(plichttod); 
					                                              //lit.insert()
				                                                  if(ppartikelquelle) ppartikelquelle->lichttodliste()->einhaengen(lit);
				                                                  lit->intensitaetdynamisch(lit->intensitaetdynamisch()+_to(plichttodaddition));
				                                                  lit->ort(port);
				                                                 };
                                                				};
};

void _partikel::kollision(const bool k,const _tg kr,const _tg kg,const _tg ka){
                                                                pkollision=k;
                                                                pkollisionreflektierend=kr;
                                                                pkollisionabgleitend=kg;
                                                                pkollisionanhaftend=ka;
};
void _partikel::kollisionz(const _tg o){
                                                                pkollisionz=true;
                                                                pkollisionzort=o;
};
void _partikel::textur(_textur<_tb>*t){
                                                                ptextur=t;
};
void _partikel::netz(_netz*n){
                                                                pnetz=n;
};
_netz* _partikel::netz(){
                                                                return(pnetz);
};
void _partikel::ort(const _vektor3<_tg>&o){
                                                                port=o;
};
void _partikel::vektor(const _vektor3<_tg>&v){
                                                                pvektor=v;
};
void _partikel::zentrum(const _vektor3<_tg>&z){
                                                                pzentrumbenutzen=true;
                                                                pzentrum=z;
};
void _partikel::lebensdauer(const _tg l){
                                                                _tg t=l;
                                                                if(t<0) t=0;
                                                                palter=0;
                                                                plebensdauermaximal=t;
                                                                plebensdauerstart=pzeit->system();
};

void _partikel::rotation(const _tg r){
                                                                protation=r;
};
_tg _partikel::rotation()const{
                                                                return(protation);
};
void _partikel::rotationvektor(const _tg v){
                                                                protationvektor=v;
};
void _partikel::rotationreibung(const _tg r){
                                                                protationreibung=r;
};
_vektor3<_tg>&_partikel::rotationachse(){
                                                                return(protationachse);

};  

void _partikel::groesse(const _tg h){
                                                                pgroesse=h;
};
void _partikel::masse(const _tg m){
                                                                pmasse=m;
};
void _partikel::skalierung(const _tg s){
                                                                pskalierung=true;
                                                                pskalierungwert=s;
};
void _partikel::feldkraftg(const _tg f){
                                                                pfeldkraftg=f;
};
void _partikel::feldkrafte(const _tg f){
                                                                pfeldkrafte=f;
};               
void _partikel::feldkraftb(const _tg f){
                                                                pfeldkraftb=f;
};
void _partikel::feldkraftm(const _tg f){
                                                                pfeldkraftm=f;
};





void _partikel::farbe(const _vektor4<_to>&f){
                                                                pfarbe=f;
};
_vektor4<_to>&_partikel::farbe(){
                                                                return(pfarbe);
};
void _partikel::opazitaet(const _to w){
                                                                pfarbe.w(w);
};
void _partikel::opazitaetexternekontrolle(const _to w){
                                                                popazitaetexternekontrolle=w;
};
void _partikel::kurvefarbe(const _kurvehermite4<_to>&k){
                                                                pkurvefarbebenutzen=true;
                                                                pkurvefarbe.kopieren(k);
};
void _partikel::einblenden(const bool b){
                                                                peinblenden=b;
};
void _partikel::ausblenden(const bool b){
                                                                pausblenden=b;
};
void _partikel::transparenz(bool additiv,bool multiplikativ){
                                                                ptransparenzadditiv=additiv;
                                                                ptransparenzmultiplikativ=multiplikativ;
                                                                
};


void _partikel::planarydivergenz(const _tg o,const _tg i){
                                                                pplanarydivergenz=true;
                                                                pplanarydivergenzort=o;
                                                                pplanarydivergenzintensitaet=i;
};
void _partikel::axialdivergenz(const _vektor3<_tg>&o,const _vektor3<_tg>&v){
                                                                paxialdivergenz=true;
                                                                paxialdivergenzort=o;
                                                                paxialdivergenzvektor=v;
};

void _partikel::schattenz(_textur<_tb>*st,_listebasis<_licht<_tg,_to> >*lichtliste){
                                                                pschattenliste.loeschen();
                                                                pschattenz=false;
                                                                if(pnetz==0) return;
                                                                pschattenz=true;
                                                                _licht<_tg,_to>*lit;
                                                                if(lichtliste->anfang(lit))do{
                                                                 new _schatteneinfach<_tg,_to>(pwelt,lit,pnetz,st);
                                                                }while(lichtliste->naechstes(lit));
};
void _partikel::opazitaetsinus(const _tg rate,const _tg ratedelta,const _tg phase){
                                                                popazitaetsinus=true;
                                                                popazitaetsinusrate=rate;
	                                                            popazitaetsinusratedelta=ratedelta;
	                                                            popazitaetsinusphase=phase;

};
void _partikel::tontod(_ton*t,_tg l,_tg b,bool d){
                                                                ptontod=t;
                                                                ptontodlautstaerke=l;
                                                                ptontodbeugung=b;
                                                                ptontodbeugungdoppler=d;
};

void _partikel::lichttod(_licht<_tg,_to>*l,_listebasis<_licht<_tg,_to> >*ll,const _tg a){
                                                                plichttod=l;
                                                               // plichttodliste=ll;
                                                                plichttodaddition=a;
};






























//******************************************************************************************************************************************************************************************************
//                                                              S P R I T E 
//******************************************************************************************************************************************************************************************************

_sprite::_sprite(_welt*w,_listebasis<_sprite >*sl,_vektor3<_tg> o,_vektor3<_tg> a,_vektor3<_tg> b,_textur<_tb>*t):_listenknotenbasis<_sprite >(sl){
                                                                port=o;
                                                                pwelt=w;
                                                                pebene[0]=a;
                                                                pebene[1]=b;
                                                                plaenge[0]=a.laenge();
                                                                plaenge[1]=b.laenge();
                                                                ptextur=t;
                                                                pebene[0].z(1);
                                                                pebene[1].z(1);
                                                                ptexvec[0].setzen(0,0);
                                                                ptexvec[1].setzen(1,0);
                                                                ptexvec[2].setzen(1,1);
                                                                ptexvec[3].setzen(0,1);
                                                                pfarbe.setzen(0,0,0,0);
                                                                protation=0;
};
_sprite::~_sprite(){
};

void _sprite::zeichnen(_grafik*gra,_kamera<_tg>*cam){
                                                                _vektor3<_tg> lt;
                                                                _vektor3<_tg> v0;
                                                                _vektor3<_tg> v1;
                                                                _vektor3<_tg> v2;
                                                                _vektor3<_tg> v3;
                                                                _bild<_tb>*bild;
                                                                _listenknoten<_bild<_tb> >*lnbild;
                                                                //--------------
                                                                gra->beleuchtung(false);
                                                                gra->material(false);
                                                                gra->textur(true);
                                                                gra->tiefenbufferkondition(true);
                                                                gra->tiefenbufferschreiben(false);
                                                                gra->transparenz(true);
                                                                if(pwelt->eigenetransformation()){
                                                                 lt=port;
                                                                 if(cam) cam->transformierenparallel(lt);
                                                                }else{
                                                                 lt=port;
                                                                };
                                                                if(ptextur){
                                                                 if(ptextur->bitmap()->anfang(lnbild)){
                                                                  bild=lnbild->objekt();
                                                                  gra->bindenbild(bild);//glBindTexture(GL_TEXTURE_2D,bild->bildidentifikation());
                                                                 };
                                                                 gra->textur(true);
                                                                };
                                                                _vektor3<_tg> hh;
                                                                if(cam) hh=cam->ebenenormalisiert(0); else hh.setzen(1,0,0);
                                                                pebene[0]=hh*0.5f*plaenge[0];
                                                                if(cam) hh=cam->ebenenormalisiert(1); else hh.setzen(0,1,0);
                                                                pebene[1]=hh*0.5f*plaenge[1];
                                                                v0= -pebene[0]-pebene[1];
                                                                v1= pebene[0]-pebene[1];
                                                                v2= pebene[0]+pebene[1];
                                                                v3= -pebene[0]+pebene[1];
                                                                _tg prot=protation;
                                                                if(prot!=0){
                                                                 v0.roty(prot);
                                                                 v1.roty(prot);
                                                                 v2.roty(prot);
                                                                 v3.roty(prot);
                                                                };
                                                                v0+=lt;
                                                                v1+=lt;
                                                                v2+=lt;
                                                                v3+=lt;
                                                                gra->zeichnen(v0,v1,v2,pfarbe,pfarbe,pfarbe,ptexvec[0],ptexvec[1],ptexvec[2]);
                                                                gra->zeichnen(v0,v2,v3,pfarbe,pfarbe,pfarbe,ptexvec[0],ptexvec[2],ptexvec[3]);
                                                                gra->tiefenbufferschreiben(true);
};
void _sprite::animieren(){
};
void _sprite::ort(const _vektor3<_tg> v){
                                                                port=v;
};
void _sprite::rotation(const _tg r){
                                                                protation=r;
};
void _sprite::farbe(const _vektor4<_to>&f){
                                                                pfarbe=f;
};
void _sprite::ebene(const _vektor3<_tg> p0,const _vektor3<_tg> p1){
                                                                pebene[0]=p0;
                                                                pebene[1]=p1;
                                                                pebene[0].z(1);
                                                                pebene[1].z(1);
                                                                
};
//******************************************************************************************************************************************************************************************************
//                                                              P A R T I K E L S P R I T E 
//******************************************************************************************************************************************************************************************************
_partikelsprite::_partikelsprite(_welt*w,_zeit*z,_partikelquelle*pq,_listebasis<_sprite >*sl,_vektor3<_tg> o,_vektor3<_tg> v,_vektor3<_tg> a,_vektor3<_tg> b,_tg life,_textur<_tb>*tex):_partikel(w,z,pq),_sprite(w,sl,o,a,b,tex){
                                                               // pa=a.laenge();
                                                               // pb=b.laenge();
                                                                _sprite::ort(o);
                                                                _partikel::ort(o);
                                                                _sprite::rotation(0);
                                                                _partikel::rotation(0);
                                                                rotationvektor(0);
                                                                vektor(v);
                                                                lebensdauer(life);
};
_partikelsprite::~_partikelsprite(){
};
/*
void _partikelsprite::rotationvektor(const _tg rv){
                                                                protvec=rv;
};
*/
/*
void _partikelsprite::animieren(){
                                                                _
                                                                beschleunigengravitation();
                                                                bewegen();
                                                                pruefenlebensdauer();
                                                                animierendarstellung();
};             
*/                                                   
void _partikelsprite::animierendarstellung(){
                                                                _vektor3<_tg> vx;
                                                                _vektor3<_tg> vy;
                                                                //------------------
                                                                _to tf=_to(alterprozent());
                                                                _sprite::farbe(_vektor4<_to>(tf,tf,tf,tf)); 
                                                                _sprite::rotation(_partikel::rotation());
                                                                _sprite::ort(_partikel::ort());
};
//******************************************************************************************************************************************************************************************************
//                                                              P A R T I K E L S P R I T E P H Y S I K A L I S C H 
//******************************************************************************************************************************************************************************************************
_partikelspritephysikalisch::_partikelspritephysikalisch(_welt*w,_zeit*z,_partikelquelle*pq,_listebasis<_sprite >*sl,_vektor3<_tg> o,_vektor3<_tg> v,_vektor3<_tg> a,_vektor3<_tg> b,_tg life,_textur<_tb>*tex, _tg d,_tg dm,_tg ld):_partikelsprite(w,z,pq,sl,o,v,a,b,life,tex){
                                                                //pqsp=pq;
                                                                pdichte=d;
                                                                pdurchmesser=dm;
                                                                pladungsdichte=ld;
                                                                poberflaeche=(4*_pi*(dm/2)*(dm/2))*100*1000000*1000000;
                                                                pladung=poberflaeche*pladungsdichte*1.602e-19;
};
_partikelspritephysikalisch::~_partikelspritephysikalisch(){
};

void _partikelspritephysikalisch::animieren(){
                                                                _vektor3<_tg> vx;
                                                                _vektor3<_tg> vy;
                                                                //_tg l;
                                                                //------------------
                                                                /*if(pqsp->feld()){
                                                                 l=vektor().laenge();
                                                                 vx=vektor()+(pqsp->feldvektor()%vektor())*0.1;//Feldkraft addieren
                                                                 vx.normalisieren();
                                                                 vx*=l;
                                                                 vektor(vx);
                                                                };*/
                                                                vy.zufall();
                                                                //vektor(vektor()+vy*pqsp->temperatur());  //temperatur, faktor
                                                                
                                                                //vektor(vektor()*pqsp->reibung());        //reibung, faktor zwischen 0..1, viskosität
                                                                animierenbewegung();                              //partikel bewegen
                                                                animierenlebensdauer();
                                                                animierenoptik();
};
