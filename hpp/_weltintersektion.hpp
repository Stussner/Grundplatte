//******************************************************************************************************************************************************************************************************
//  Project     : grundplatte
//  Library     : _grundplatte.lib
//  Module      : _weltintersektion.hpp
//  Date        : 5.1.2003
//  Description : dynamisches volumetrisches polygonales lineares intersecting mit drahtgittern
//******************************************************************************************************************************************************************************************************
#ifndef _dminterh_included
#define _dminterh_included
//******************************************************************************************************************************************************************************************************
//                                                              P R E D E K L A R A T I O N 
//******************************************************************************************************************************************************************************************************
 class _modifikationnetzintersektion;
 class _intersektion;
 class _verbinderisintro;
 class _verbinderisextro;
 class _statusrelevanz;
 class _statuskreuz;
 class _statussektion;
 class _ringsektion;
 class _ringpartition;
 class _verbindergeometrisch;
 class _verbindergeometrischiterator;
 class _rpintersektion;
#include <_global.hpp> 
#include <_struktur.hpp>
#include <_vektor.hpp>
#include <_datei.hpp>
#include <_grafik.hpp>
//******************************************************************************************************************************************************************************************************
//                                                              Z Y K L I S C H E 
//******************************************************************************************************************************************************************************************************
 //class _modifikation;
 class _geometrie;
 class _netz;
 class _polygon;
 class _polygontexturraum;
 class _vertex;
 class _verbindervertexpolygon;
 class _kantepolygon;
//************DEBUG************
 class _geometriequader;
 class _weltdebug;
 class _weltdebugpunkt;
 class _weltdebuglinie;
 class _weltdebugpfeil;
 class _weltdebugkreuz;
 class _weltdebugschirm;
template<class _tg> class _kamera;
#include <_welt.hpp>
#include <_weltgeometrie.hpp>

//**************DEBUG ****************
extern _welt*DW;
//************************************

//******************************************************************************************************************************************************************************************************
//                                                              M O D I F I K A T I O N N E T Z I N T E R S E K T I O N 
//******************************************************************************************************************************************************************************************************
class _modifikationnetzintersektion:public _modifikation{
        public:
        using _listenknotenbasis<_modifikation >::naechstes;
      //  using _listebasis<_geometrie >::naechstes;
        using _listenknotenbasis<_modifikation >::vorheriges;
      //  using _listebasis<_geometrie >::vorheriges;
        friend class _intersektion;
        friend class _verbinderisintro;
        friend class _verbinderisextro;
        friend class _statusrelevanz;
        friend class _statuskreuz;
        friend class _statussektion;
        friend class _ringsektion;
        friend class _ringpartition;
        friend class _verbindergeometrisch;
        friend class _verbindergeometrischiterator;
        friend class _rpintersektion;
        public:
                //********************************************** A P I **********************************************************
               // _modifikationnetzintersektion(_geometrie*,unsigned int);
                _modifikationnetzintersektion();
                virtual ~_modifikationnetzintersektion();
                char bearbeiten(_netz*);
                char bearbeiten(_netz*,_netz*,int);
                bool hatintersektion(_netz*test0,_netz*test1);
                bool hatintersektion(_netz*,_liste<_netz >*,_liste<_netz >*);
                bool netzinnerhalbnetz(_netz*,_netz*);
                void operation(const unsigned int);
                void searchiteratorcountmaximal(const unsigned int);
                void speadpartitiontry(const unsigned int,const bool);
                void vereinigenohneschnitt(const bool b);
                bool vereinigenohneschnitt()const;
                void nearzerovalue(const _tg);
                _tg  nearzerovalue() const;
                void schreibenlogbuch(bool);
                bool schreibenlogbuch()const;
                void debugwelt(_welt*);
                void debuganimwait();
        private:                                
                //********************************************** globale verwaltungsfunction ************************************
                void init(unsigned int);
                void createstatusstruct(_netz*);
                void clearstatusstruct(_netz*);
                //********************************************** intersektion-introconnector-generation *************************
                void determineintersection(_polygon*,_polygon*);
                void determineintersection();
                char determineintersectionoblique(_polygon*,_polygon*,_kantepolygon*);
                void determineintersectionparallel(_polygon*,_polygon*,_kantepolygon*);
                void completeintersection(_polygon*);
                void completeintersection(_polygon*,_kantepolygon*,_vertex*,_listebasis<_verbinderisintro >*);
                char searchintersection(_polygon*,_intersektion*,_polygon*);
                void clearintersection(_netz*);
                void clearisintroconnectors(_listebasis<_verbinderisintro >*);
                void createintersection(_polygon*,_polygon*,_kantepolygon*,_vektor3<_tg>,_tg);
                char createisintroconnector(_vertex*,_intersektion*,_polygon*,_tg);
                char createisintroconnector(_kantepolygon*,_intersektion*,_polygon*,_tg);
                char createisintroconnector(_polygon*,_intersektion*,_polygon*,_tg);
                char isintroconnectorexists(_intersektion*,_polygon*,_listebasis<_verbinderisintro >*);
                //********************************************** virtual intersektion generation  *******************************
                void createvertexintersections(_netz*,_polygon*);
                void clearvertexintersections(_polygon*);
                void initintersectionvertices(_netz*);
                //********************************************** intersectionring - prepare function ****************************
                void invertisintroconnectorrings(_polygon*);
                void integrateintersectionrings(_polygon*);
                void formvertexintersectionring(_polygon*);
                void uniteintersectionrings(_polygon*);
                void uniteintersectionrings(_intersektion*,_intersektion*);
                void flagintersection(_netz*,int);
                void flagintersection(_polygon*,int);
                void flagintersection(_listebasis<_verbinderisintro >*,int);
                //********************************************** statusdeterminationfunktionen **********************************
                void createstatuscrosses(_polygon*);
                void createstatuscrosses(_polygon*,_listebasis<_verbinderisintro >*);
                void createstatuscrosses(_polygon*,_intersektion*);
                void clearstatuscrosses(_polygon*);
                void clearstatuscrosses(_listebasis<_verbinderisintro >*);
                void getintersectionalpha(_polygon*,_intersektion*,_liste<_intersektion >*);
                char checkrightsided(_polygon*,_intersektion*,_intersektion*,_intersektion*,_tg,_tg,bool,bool);
                char isintersectionreferenzed(_intersektion*,_polygon*,_listebasis<_verbinderisintro >*&);
                char isintersectionreferenzed(_intersektion*,_listebasis<_verbinderisintro >*,_listebasis<_verbinderisintro >*&);
                //********************************************** ringpartition - construction ***********************************
                char createandcoverringpartition(_netz*);
                char createandcoverringpartition(_polygon*);
                void createringpartition(_polygon*,_intersektion*);
                void createringpartition(_polygon*,_listebasis<_verbinderisintro >*);
                void createringpartition(_polygon*,_statuskreuz*,_listebasis<_verbinderisintro >*);
                void clearringpartition(_netz*);
                char determinenextstatuscross(_polygon*,_intersektion*,_statuskreuz*&);
                void determinevirtualpartitionstatus(_polygon*);
                void determinevirtualpartitionstatus(_polygon*,_ringpartition*);
                void determinevirtualpartitionstatus(_ringpartition*,_listebasis<_rpintersektion >*);
                void determinevirtualintersectionstatus(_polygon*);
                void clearnegativepartition(_polygon*);
                char checkringpartitionisolation(_polygon*,_ringpartition*,_intersektion*);
                char collideringpartition(_polygon*,_ringpartition*,_vektor3<_tg>&,_vektor3<_tg>&,_listebasis<_rpintersektion >*);
                void filterbackfacedrpintersection(_polygon*,_vektor3<_tg>&,_listebasis<_rpintersektion >*);
       //char pointinpartition(_polygon*,_ringpartition*,_vektor<_tg>&,_vektor<_tg>&,_vektor<_tg>&,int&);
                char determinesurroundingringpartition(_polygon*,_ringpartition*);
                void uniteringpartition(_ringpartition*,_ringpartition*);
                //********************************************** cover ring partition *******************************************
                char coverringpartition(_polygon*,_liste<_polygon >*);
                void initstartiterator(_ringpartition*,_verbindergeometrischiterator*&);
                void getpossiblegeoconnectoriterators(_polygon*,_ringpartition*,_verbindergeometrischiterator*);
                char checkgeoconnectoriteratorisvalid(_polygon*,_verbindergeometrischiterator*,_verbindergeometrisch*,_tg&);
                void limitgeoconnectoriterators(unsigned int);
                void sortalphageoconnectoriterators(_polygon*);
                char searchvalidpartition(_polygon*,_ringpartition*);
                char checkpartitionisvalid(_polygon*,_ringpartition*);
                void spreadpartition(_polygon*,_ringpartition*);
                char getpartitionsequence();
                char checkpartitionisconvex(_polygon*);
                char checkpartitionhasnohit(_polygon*,_ringpartition*);
                char checkpartitionhasnohit(_polygon*,_ringpartition*,_ringsektion*,_ringsektion*);
                char checkpartitionhasnohit(_polygon*,_intersektion*,_intersektion*,_intersektion*,_intersektion*);
                char checkpartitionisuncovered(_polygon*,_ringpartition*);
                char checkpartitionisuncovered(_polygon*,_vektor3<_tg>,_vektor3<_tg>&);
                void createpoly(_polygon*,_ringpartition*,_liste<_polygon >*);
                void performconnectorstruct();
                void interpolatetexturecoordinates(_polygon*,_polygon*);
                //********************************************** duplicating & deleting *****************************************
                void spreadvirtualstatus(_netz*);
                void spreadvirtualstatus(_polygon*,int);
                void duplicatepoly(_netz*);
                void duplicatepoly(_polygon*);
                void destructpoly(_netz*);
                void getstatustotalduplicationanddestruction(int&,int&);
                void performtotalduplicationanddestruction(int,int);
                void duplicatemesh();
                void performpolygonoptimation();
                void performpolygonoptimation(_liste<_polygon >*);
                //********************************************* helpers *********************************************************
                //void dilatenearzero(_vektor<_tg>&,_vektor<_tg>&);
                void getlineparameter(const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor3<_tg>&,_tg&);
                void getlineparameter2d(const _vektor2<_tg>&,const _vektor2<_tg>&,const _vektor2<_tg>&,_tg&);
                void getlotpointline2d(_vektor2<_tg>&,_vektor2<_tg>&,_vektor2<_tg>&,_vektor2<_tg>&);
                char getdistance(const _vektor3<_tg>&,const _vektor3<_tg>&,_tg&);
                int invertnormalstatus(_netz*);
                _tg deltaalpha(_tg,_tg);
                //********************************************** debug **********************************************************
                void createdebugscreen();
                void cleardebugscreen();
                void visualizeintersection();
                void visualizeintersection(_netz*);
                void visualizeintersection(_listebasis<_verbinderisintro >*);
                void visualizeconnectorstruct();
                void visualizeintroconnectorstruct();
                void visualizeintroconnectorstruct(_netz*);
                void visualizeintroconnectorstruct(_netz*,_listebasis<_verbinderisintro >*,const _vektor3<_tg>&,const _vektor3<_tg>&,const _vektor3<_tg>&);
                void visualizeextroconnectorstruct();
                void visualizeextroconnectorstruct(_netz*);
                void visualizeextroconnectorstruct(_listebasis<_verbinderisintro >*,const _vektor3<_tg>&,const _vektor3<_tg>&);
                void visualizestatusstruct(_netz*);
                void visualizestatusstruct(_listebasis<_verbinderisintro >*);
                void visualizeintersectionsequence(_vertex*);
                void visualizeringpartition(_polygon*);
                void debuganimation();
               
               
        private:
                _netz*meshtointersect;
                _netz*intersectingmesh;
                _welt*W;
                _system*S;
                //schalter & regler
                int mainoperation;
                int maxgitentry;
                char spreadnexttry;
                char spreadprevtry;
                bool pvereinigungohneschnitt;
                //operationsunterstützung
                int poperation;
                _netz*thismesh;
                _listebasis<_verbindergeometrischiterator > geoconnectoriteratorrawlist;
                _listebasis<_verbindergeometrischiterator > geoconnectoriteratordistancelist;
                _listebasis<_verbindergeometrischiterator > geoconnectoriteratoralphalist;
                _liste<_ringsektion >*partitionsequence;
                _tg nahenull;
                _vektoranalysis2<_tg> V2;
                _vektoranalysis3<_tg> V3;
                char nointersection;
                bool plog;
                _liste<_liste<_polygon > > polygonoptimationlist;
                //debug
                _weltdebugschirm*dbscreen;
                _kamera<_tg>*dbcam;
               // _maus<_tg>*dbmo;
               // _grafik*dbgra;
                _vektor4<_to> pdbcolnote;
                _vektor4<_to> pdbcolfunc;
                _vektor4<_to> pdbcolerror;
                //_kamera<_tg>*cam;
                unsigned int debugskipcount;
                
};
//******************************************************************************************************************************************************************************************************
//                                                              V E R B I N D E R I S I N T R O 
//******************************************************************************************************************************************************************************************************
class _verbinderisintro:public _listenknotenbasissortiert<_verbinderisintro,_tg>{
        friend class _modifikationnetzintersektion;
        friend class _intersektion;
        friend class _statuskreuz;
        friend class _verbinderisextro;
        private:
                _verbinderisintro(_vertex*,_intersektion*,_polygon*,_kantepolygon*,_vertex*,_tg);//f. vertex
                _verbinderisintro(_kantepolygon*,_intersektion*,_polygon*,_kantepolygon*,_vertex*,_tg);//f. kante
                _verbinderisintro(_polygon*,_intersektion*,_polygon*,_kantepolygon*,_vertex*,_tg);//f. dreieck
                virtual ~_verbinderisintro();
                bool polygonedgebounded()const;
                inline _intersektion*intersektion();
                inline _polygon*causalpolygon();
                void visualisieren(_netz*,_vektor3<_tg>&,_vektor4<_to>&);
        private:
                _intersektion*pintersection; //mainref
                _polygon*pcausalpoly; //secref
                _kantepolygon*pcausaledge;
                _vertex*pcausalvertex;
                _polygon*ppoly; //backref
                _kantepolygon*pedge; //backref
                _vertex*pvertex; // backref
                _tg palpha;
                _verbinderisextro*pisextroconnector;
                //*************DEBUG***************
                _weltdebugkreuz*pdbcross;
                _weltdebuglinie*pdbtointersection;
                _weltdebugpfeil*pdbtopolyowner;
                _weltdebugpfeil*pdbtopolycausal;
                
};
//******************************************************************************************************************************************************************************************************
//                                                              V E R B I N D E R I S E X T R O
//******************************************************************************************************************************************************************************************************
class _verbinderisextro:public _listenknotenbasis<_verbinderisextro >{
        friend class _modifikationnetzintersektion;
        friend class _verbinderisintro;
        private:
                _verbinderisextro(_intersektion*,_verbinderisintro*);
                virtual ~_verbinderisextro();
                void clearisintroconnector();
                void visualisieren(_vektor3<_tg>);
        private:
                _verbinderisintro*pisintroconnector;
                _intersektion*pintersection;
                //*************DEBUG***************
                _weltdebugkreuz*debug;
                _weltdebuglinie*debugic;
                _weltdebuglinie*debugis;
};
//******************************************************************************************************************************************************************************************************
//                                                              S T A T U S K R E U Z
//******************************************************************************************************************************************************************************************************
class _statuskreuz:public _listenknotenbasis<_statuskreuz >{
        friend class _modifikationnetzintersektion;
        friend class _intersektion;
        friend class _ringsektion;
        private:
                _statuskreuz(_modifikationnetzintersektion*,_statussektion*,_intersektion*,_intersektion*,_tg,_tg,_polygon*,char);
                virtual ~_statuskreuz();
                void getmiddle();
                void visualisieren();
                void unvisualisieren();
                inline _statussektion*statussection();
                _vektor3<_tg> mitte() const;
                _intersektion*left(const unsigned int);
                _tg alpha(const unsigned int) const;
                void determinestatus(_polygon*,_listebasis<_verbinderisintro >*);
                int setstatus(int);
                int setstatuskomplanar(int);
                char determinecausalitytype(_intersektion*,_polygon*,_kantepolygon*&,_vertex*&,_vertex*&,_vertex*&);
                char determinecausalitytype(_intersektion*,_listebasis<_verbinderisintro >*);
                void collideinfinitiv(_vektor3<_tg>&,_polygon*,_tg&,int&);
                void collidetotalplanar(_polygon*,_vektor3<_tg>&,_vektor3<_tg>&,_vektor3<_tg>&,_vektor3<_tg>&,_tg&,int&);
                void collidesemiplanar(_polygon*,_kantepolygon*,_vektor3<_tg>&,_vektor3<_tg>&,_vektor3<_tg>&,_vektor3<_tg>&,_tg&,int&);
                void collidedoublesemiplanar(_polygon*,_vertex*,_vertex*,_vertex*,_vektor3<_tg>&,_vektor3<_tg>&,_vektor3<_tg>&,_vektor3<_tg>&,_tg&,int&);
        private:
                char virtualintersection;//statuscross wird von einer virtuellen intersektion verwaltet
                char komplanar;          //statuscross beschreibt eine komplanare Situation
                int markierung;
                int status;              //abdecken oder nicht ?              
                int rawstatus;           //innen oder nicht ?
                _polygon*pcausalpoly;
                _statussektion*pstatussection;
                _modifikationnetzintersektion*mmi;
                _vektor3<_tg> pmiddle;     //absolute position des statuscross in raumkoorinaten
                _tg palpha[2];            //2D - absolut-winkel von left0 und left1
                _intersektion*pleft[2];
                //*************DEBUG****************************
                _weltdebugkreuz*debugcross;
                _weltdebugpfeil*debugis;
                _weltdebugpfeil*debugle[2];

};
//******************************************************************************************************************************************************************************************************
//                                                              S T A T U S R E L E V A N Z
//******************************************************************************************************************************************************************************************************
class _statusrelevanz:public _listenknotenbasissortiert<_statusrelevanz,_tg >{
        friend class _intersektion;
        friend class _modifikationnetzintersektion;
        private:
                _statusrelevanz(_intersektion*,_intersektion*,_polygon*,_statusrelevanz*,bool,_tg);
                virtual ~_statusrelevanz();
                void visualisieren();
                void unvisualisieren();
        private:
                _intersektion*intersektion;
                _intersektion*verwalter;
                _polygon*causalpoly;
                _statusrelevanz*komplanar;
                bool autorelevant;
                _tg alpha;
                //DEBUG
                _weltdebugpfeil*pwl;
};
//******************************************************************************************************************************************************************************************************
//                                                              S T A T U S S E K T I O N 
//******************************************************************************************************************************************************************************************************
class _statussektion:public _listenknotenbasis<_statussektion >,public _listebasis<_statuskreuz >{
        public:
        using _listenknotenbasis<_statussektion >::naechstes;
        using _listebasis<_statuskreuz >::naechstes;
        using _listenknotenbasis<_statussektion >::vorheriges;
        using _listebasis<_statuskreuz >::vorheriges;
        friend class _intersektion;
        friend class _ringsektion;
        friend class _statuskreuz;
        friend class _modifikationnetzintersektion;
        private:
                _statussektion(_intersektion*,_polygon*);
                virtual ~_statussektion();
        private:
                _polygon*poly;
                _intersektion*intersektion;
};
//******************************************************************************************************************************************************************************************************
//                                                              I N T E R S E K T I O N 
//******************************************************************************************************************************************************************************************************
class _intersektion:
public _listenknotenbasis<_intersektion >,
public _listebasis<_statusrelevanz >,
public _listebasis<_statussektion >,
public _listebasis<_verbinderisextro >{
        public:
                using _listebasis<_statusrelevanz >::anfang;
                using _listebasis<_statussektion >::anfang;
                using _listebasis<_verbinderisextro >::anfang;
                using _listebasis<_statusrelevanz >::naechstes;
                using _listebasis<_statussektion >::naechstes;
                using _listebasis<_verbinderisextro >::naechstes;
                using _listenknotenbasis<_intersektion >::naechstes;
                using _listebasis<_statusrelevanz >::vorheriges;
                using _listebasis<_statussektion >::vorheriges;
                using _listebasis<_verbinderisextro >::vorheriges;
                using _listenknotenbasis<_intersektion >::vorheriges;
        public:
                _intersektion(_vektor3<_tg>);//für vertex,kante & dreieck
                _intersektion(_vektor3<_tg>,_vertex*);//virtuelle vertexintersection
                _intersektion(_listebasis<_intersektion >*,_vektor3<_tg>,_tg);//für vertexoutermesh-check
                virtual ~_intersektion();
                _vektor3<_tg>&ort();
                void clearrelevance();
                _tg deltaalpha(_tg,_tg)const;
                _tg differenz(_tg,_tg)const;
                void getrelevance(_modifikationnetzintersektion*,_polygon*,_listebasis<_verbinderisintro >*);
                void searchrelevance(_polygon*,_polygon*,_listesortiert<_intersektion,_tg>*);
                void searchrelevance(_polygon*,_listebasis<_verbinderisintro >*,_listesortiert<_intersektion,_tg>*);
                void determinealphagroups(_modifikationnetzintersektion*,_listesortiert<_intersektion,_tg>*,_liste<_tg>*);
                void limitrelevance(_modifikationnetzintersektion*,_polygon*,_listesortiert<_intersektion,_tg>*,_liste<_tg>*,_polygon*,bool,bool&);
                void transferrelevance(_modifikationnetzintersektion*,_listesortiert<_intersektion,_tg>*,_polygon*,bool,bool);
                char getcorrespondingisintroconnector(_polygon*,_verbinderisintro*,_verbinderisintro*&);
                char getcorrespondingisintroconnector(_polygon*,_verbinderisintro*,_listebasis<_verbinderisintro >*,_verbinderisintro*&);
                void switchsection(_polygon*);
                char checkedgekoherence(_polygon*);
                void visualizestatusstruct();
                void visualisieren();
               
        public:
                _vektor3<_tg> o;                                 //absolute raumkoordinate des schnittpunkts
                _vertex*vertex;                //wenn this eine virtuelle intersektion ist, dann ist er gesetzt
                _tg alpha;                                      //ein geradenparameter, der den schnittpunkt definiert
                //int koplanar;
                int markierung;
                int status;
                //*************DEBUG***************
                _weltdebugkreuz*debug;
};
//******************************************************************************************************************************************************************************************************
//                                                              R I N G P A R T I T I O N 
//******************************************************************************************************************************************************************************************************
class _ringpartition:public _listenknotenbasis<_ringpartition >,public _listebasis<_ringsektion >{
        public:
        using _listenknotenbasis<_ringpartition >::naechstes;
        using _listebasis<_ringsektion >::naechstes;
        using _listenknotenbasis<_ringpartition >::vorheriges;
        using _listebasis<_ringsektion >::vorheriges;
        public:
                _ringpartition(_polygon*);
                virtual ~_ringpartition();
                void setangle(_tg);
                void integrate();
                void flaggeoconnector(int);
                _polygon*polygon();
                bool punktinnerhalb(_vektor3<_tg>);
                void visualisieren();
                void unvisualisieren();
        public:
                int status;
                char isolated;
                _tg rightangle;
                _ringpartition*surroundingringpartition;
                _polygon*poly;
                // ******************DEBUG**************************
                _liste<_weltdebugkreuz > pdbcrosses;
                _liste<_weltdebugpfeil > pdbarrows;
};
//******************************************************************************************************************************************************************************************************
//                                                              R I N G S E K T I O N 
//******************************************************************************************************************************************************************************************************
class _ringsektion:public _listenknotenbasis<_ringsektion >,public _listebasis<_verbindergeometrisch >{
        public:
        using _listenknotenbasis<_ringsektion >::naechstes;
        using _listebasis<_verbindergeometrisch >::naechstes;
        using _listenknotenbasis<_ringsektion >::vorheriges;
        using _listebasis<_verbindergeometrisch >::vorheriges;
        public:
                _ringsektion(_ringpartition*,_statuskreuz*);
                virtual ~_ringsektion();
        public:
                int performed;
                _statuskreuz*statuscross;
                _intersektion*intersektion;
                _ringpartition*ringpartition;
};
//******************************************************************************************************************************************************************************************************
//                                                              V E R B I N D E R G E O M E T R I S C H
//******************************************************************************************************************************************************************************************************
class _verbindergeometrisch:public _listenknotenbasis<_verbindergeometrisch >{
        friend class _modifikationnetzintersektion;
        public:
                _verbindergeometrisch(_ringsektion*);
                _verbindergeometrisch(_ringsektion*,_verbindergeometrisch*,_verbindergeometrisch*);
                virtual ~_verbindergeometrisch();
                void init(_ringsektion*,_verbindergeometrisch*,_verbindergeometrisch*);
                void aktualisieren();
                _vektor3<_tg> middleanglevector();
                _verbindergeometrisch*getgeoconnector(int);
                void visualisieren();
                void unvisualisieren();
        public:
                _ringsektion*ringsection;
                _verbindergeometrisch*geoconnector[2];
                _tg alpha;
                _vektor3<_tg> vektor;
                _vektor3<_tg> mitte;
                _vektor3<_tg> normale;
                int markierung;
};
//******************************************************************************************************************************************************************************************************
//                                                              V E R B I N D E R G E O M E T R I S C H I T E R A T O R 
//******************************************************************************************************************************************************************************************************
class _verbindergeometrischiterator:public _listenknotenbasissortiert<_verbindergeometrischiterator,_tg>{
        public:
                _verbindergeometrischiterator(_listebasis<_verbindergeometrischiterator >*,_verbindergeometrischiterator*);
                _verbindergeometrischiterator(_listebasis<_verbindergeometrischiterator >*,_verbindergeometrisch*);
                _verbindergeometrischiterator(_listebasis<_verbindergeometrischiterator >*,_tg,char,_verbindergeometrisch*,_verbindergeometrisch*);
                virtual ~_verbindergeometrischiterator();
                _verbindergeometrisch*geoconnector(const unsigned int);
                _vektor3<_tg> mitte()const;
                char spread(int);
                char contract(int);
                void visualisieren(_vektor4<_to>);      
                void markierung(int);
                int markierung()const;
        private:
                void init(_tg,char);
        private:
                _verbindergeometrisch*pgeoconnector[2];
                char issave;
                _tg alpha;
                char singular[2];
                int pflag;
                //*********** DEBUG ******************
                _liste<_weltdebuglinie > listline;
                _weltdebugkreuz*pdbcross;
};
//******************************************************************************************************************************************************************************************************
//                                                              R P I N T E R S E K T I O N 
//******************************************************************************************************************************************************************************************************
class _rpintersektion:public _listenknotenbasissortiert<_rpintersektion,_tg>{
        public:
                _rpintersektion(_listebasis<_rpintersektion >*,_ringpartition*,_ringsektion*,_ringsektion*,_tg);
        public:
                _ringpartition*ringpartition;
                _ringsektion*ringsection[2];
                _tg alpha;
};


#endif


