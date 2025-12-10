//******************************************************************************************************************************************************************************************************
//  Project     : grundplatte
//  Library     : _grundplatte.lib
//  Module      : _bild.hpp
//  Date        : 27.12.2002
//  Description : 
//******************************************************************************************************************************************************************************************************
#ifndef _bild_included
#define _bild_included


//******************************************************************************************************************************************************************************************************
//                                                              F O R W A R D S 
//******************************************************************************************************************************************************************************************************
//template<class _tb=typoptik>class _filetga;
class _bildhardware;
template<class _tb=typbild>class _bild;
//template<class _tb=typoptik>class _bildtga;
//template<class _coloranim=typoptik,class _colordraw=char>class _maptgamap;
//template<class _color>class _mapbmp;
//template<class _color>class _mapjpg;
template<class _tb=typbild>class _texturverwaltung;
template<class _tb=typbild>class _textur;
template<class _tg=typgeometrie>class _texturvektor;
template<class _tg=typgeometrie>class _bildvektor;
//template<class _coloranim,class _colordraw>class _mapmapbmp;
//template<class _coloranim,class _colordraw>class _mapmapjpg;

//
//#define NEED_FAR_POINTERS
//

#include <windows.h>
//******************************************************************************************************************************************************************************************************
//                                                              J P G C O M P R E S S O R
//******************************************************************************************************************************************************************************************************
#include <stdio.h>
#undef FAR
//#undef boolean
extern "C"{ 
#define XMD_H
#define HAVE_BOOLEAN
#include <jpg/jpeglib.h>
}

#include <setjmp.h>
//#undef INT32


//******************************************************************************************************************************************************************************************************
//                                                              P N G W I X
//******************************************************************************************************************************************************************************************************
extern "C"{
#include <png/png.h>
#include <png/pngconf.h>
#include <png/zconf.h>
#include <png/zlib.h>
};
//  für PNG-Lib 
typedef struct { 
   unsigned char  *buffer; 
   size_t         pos; 
} pngFileBuffer_t; 
 
static void user_read_data(png_structp png_ptr, png_bytep data, png_size_t length) { 
   pngFileBuffer_t  *buffer = (pngFileBuffer_t *)png_get_io_ptr(png_ptr); 
   memcpy(data, buffer->buffer + buffer->pos, length); 
   buffer->pos += length; 
};
//******************************************************************************************************************************************************************************************************
//                                                              W I X
//******************************************************************************************************************************************************************************************************


#include <_global.hpp>
#include <_text.hpp>
#include <_vektor.hpp>
#include <_datei.hpp>
#include <_grafik.hpp>


struct my_error_mgr {
                struct jpeg_error_mgr pub;	/* "public" fields */
                jmp_buf setjmp_buffer;	/* for return to caller */
};
typedef struct my_error_mgr * my_error_ptr;
// Here's the routine that will replace the standard error_exit method:
METHODDEF(void)my_error_exit (j_common_ptr cinfo){
                                                                /* cinfo->err really points to a my_error_mgr struct, so coerce pointer */
                                                                my_error_ptr myerr = (my_error_ptr) cinfo->err;
                                                                /* Always display the message. */
                                                                /* We could postpone this until after returning, if we chose. */
                                                                (*cinfo->err->output_message) (cinfo);
																L->schreiben("Ein JPG decomprssionsfehler ist aufgetreten");
                                                                /* Return control to the setjmp point */
                                                                longjmp(myerr->setjmp_buffer, 1);
};








static void my_init_source(jpeg_decompress_struct *cinfo) { 
};
 
static boolean my_fill_input_buffer(jpeg_decompress_struct *cinfo) { 
   return(true); 
};
 
static void my_skip_input_data(jpeg_decompress_struct *cinfo, long num_bytes){ 
   jpeg_source_mgr  *src = cinfo->src;
   src->next_input_byte += num_bytes; 
   src->bytes_in_buffer -= num_bytes; 
};
 
static void my_term_source(jpeg_decompress_struct *cinfo){ 
};
 
static void jpeg_memory_src(jpeg_decompress_struct *cinfo, jpeg_source_mgr *src, _tb*buffer, unsigned int size){ 
   cinfo->src             = src; 
   src->init_source       = my_init_source; 
   src->fill_input_buffer = my_fill_input_buffer; 
   src->skip_input_data   = my_skip_input_data; 
   src->resync_to_restart = jpeg_resync_to_restart; 
   src->term_source       = my_term_source; 
   src->next_input_byte   = buffer; 
   src->bytes_in_buffer   = size; 
};







/*
template<class _tb>
class _filetga:public _datei<unsigned char>{
        protected:
                _filetga(_zeichenkette<unsigned char>);
                char laden();
                void speichern();
                void daten(_tb*);
                void groesse(unsigned int,unsigned int);
                void kanaele(unsigned int);
        private:
                unsigned int px;
                unsigned int py;
                unsigned int pchannels;
                _tb*pdata;
};
template<class _tb> _filetga<_tb>::_filetga(_zeichenkette<unsigned char> f):_datei<unsigned char>(f){
                                                                laden();
                                                                //int i;
                                                                //_zeichenkette<_typtext> s=gettypename(this);
                                                                //L->schreiben(gettypename(this));
                                                                //i=0;
                                                                //if(s.suchen("float",i)){
                                                                 //L->schreiben("ist float");
                                                                //};
                                                                //i=0;
                                                                //if(s.suchen("double",i)){
                                                                 //L->schreiben("ist double");
                                                                //};
};
template<class _tb> char _filetga<_tb>::laden(){
                                                                if(oeffnen()){
                                                                 schliessen();
                                                                };
                                                                return(0);
};
template<class _tb> void _filetga<_tb>::speichern(){
                                                                if(oeffnen()){
                                                                 loeschen();
                                                                 schliessen();
                                                                };
};
template<class _tb> void _filetga<_tb>::daten(_tb*d){
                                                                pdata=d;
};
template<class _tb> void _filetga<_tb>::groesse(unsigned int x,unsigned int y){
                                                                px=x;
                                                                py=y;
};
template<class _tb> void _filetga<_tb>::kanaele(unsigned int c){
                                                                pchannels=c;
};
*/
//******************************************************************************************************************************************************************************************************
//                                                              B I L D 
//******************************************************************************************************************************************************************************************************
template<class _tb>
class _bild:public _listenknotenbasis<_bild<_tb> >,public _datei,public _basis::_speicherbarargument<_bild<_tb> >{
        public:
        using         _datei::laden;
        using         _datei::speichern;
        public:
                //grundfunktionen
                _bild(unsigned int w,unsigned int h,unsigned int channels);
                _bild(const _zeichenkette<char>&);
                _bild(const _zeichenkette<char>&,unsigned int,unsigned int);
                _bild(const _bild<_tb>*);
                virtual ~_bild();
                
                
                
                void groesse(unsigned int x,unsigned int y);
                void groesse(unsigned int x,unsigned int y,unsigned int c);
                unsigned int speicherlast() const;
                //unsigned int groessex() const;
                //unsigned int groessey() const;
                unsigned int groesse(unsigned char);
                unsigned int breite()const;
                unsigned int hoehe()const;
                inline _tb*daten();
                void kanaele(unsigned int);
                unsigned int kanaele() const;
                bool ursprungrechts()const;
                bool ursprungunten()const;
                void tiefeloeschen(_tb);
                void tiefereskalieren(_tb);
                void depthclip(_tb);
                _tb tiefe() const;
                _zeichenkette<char> name() const;
                void name(_zeichenkette<char>);
                bool geladen() const;
                void entladen();
                //void bildidentifikation(const unsigned int,_grafik*);
                void bildhardware(_bildhardware*);
                _bildhardware*bildhardware();
                //inline unsigned int bildidentifikation() const;
                void loeschenbildhardware();
                void shaderid(const unsigned int);
                inline unsigned int shaderid() const;
                void index(const unsigned int);
                unsigned int index()const;
                void wiederholung(const unsigned int,const bool);
                inline bool wiederholung(const unsigned int) const;
                void mipmap(const bool);
                inline bool mipmap() const;
                //operatorüberladungen
                _vektor<_tb> operator[](unsigned int) const;
                inline operator _tb*();
                void notfallinitialisierung(unsigned int,unsigned int);
                void datentausch(unsigned int,unsigned int);
                void schreiben(const _vektor<_tb>&);
              
                void schreiben(unsigned int, unsigned int,const _vektor<_tb>&);
                void lesen(unsigned int,unsigned int,_vektor<_tb>&);
                //speichern
                virtual bool laden();
                virtual void speichern();
                bool ladentga();
                void speicherntga();
                bool ladenjpg();
                void speichernjpg(int quality);
                bool ladenpng();
                void speichernpng();

                virtual char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_bild>*);
                virtual void speichern(_speicherbardynamisch<_bild>*);
                virtual char assoziieren(_speicherbardynamisch<_bild>*);
                virtual _zeichenkette<char> typ()const;
        protected:
                void daten(_tb*,unsigned int,unsigned int,unsigned int,_tb);
        private:
                void init();
        private:
                unsigned int lx;//breite
                unsigned int ly;//höhe
                unsigned int lchannels;//Anzahl der Kanäle [1..*] (index 0..*)
                bool poriginxright;
                bool poriginydown;
                _tb pdepth;
                _tb*ldata; //datenfeld
                _zeichenkette<char> lname;//name opt.
               // unsigned int pmapid;
                unsigned int pshaderid;
                unsigned int pindex;
                bool prepeatx;
                bool prepeaty;
                bool pmipmap;
                _grafik*pgrafik;
                bool pwirdgeloescht;
                _bildhardware*pbildhardware;
                bool pjpg;
};
template<class _tb> _bild<_tb>::_bild(unsigned int w,unsigned int h,unsigned int channels):_datei("bild.tga"){
                                                                
                                                                init();
                                                                lchannels=channels;
                                                                groesse(w,h);
                                                                //pmapid=0;
                                                                pshaderid=0;
                                                                pindex=0;
                                                                prepeatx=true;
                                                                prepeaty=true;
                                                                pmipmap=true;
                                                                pgrafik=0;
                                                                pbildhardware=0;
};
template<class _tb> _bild<_tb>::_bild(const _zeichenkette<char>&n):_datei(n){
                                                                init();
                                                                groesse(1,1);
                                                                //pmapid=0;
                                                                pshaderid=0;
                                                                pindex=0;
                                                                prepeatx=true;
                                                                prepeaty=true;
                                                                pmipmap=true;
                                                                pgrafik=0;
                                                                pbildhardware=0;
                                                                if(laden()) {
                                                                 L->schreiben("_bildtga<_tb> : Laden eines Bildes erfolgreich.");
                                                                }else{
                                                                };
                                                                
};
template<class _tb> _bild<_tb>::_bild(const _zeichenkette<char>&n,unsigned int x,unsigned int y):_datei(n){
                                                                init();
                                                                groesse(x,y);
                                                                //pmapid=0;
                                                                pshaderid=0;
                                                                pindex=0;
                                                                prepeatx=true;
                                                                prepeaty=true;
                                                                pmipmap=true;
                                                                pgrafik=0;
                                                                pbildhardware=0;
                                                                if(laden()) {
                                                                 L->schreiben("_bildtga<_tb> : Laden eines Bildes erfolgreich.");
                                                                }else{
                                                                };
                                                                
};
template<class _tb> _bild<_tb>::_bild(const _bild<_tb>*m):_datei(m->dateiname()){
                                                                //pmapid=0;
                                                                pshaderid=0;
                                                                pindex=0;
                                                                prepeatx=m->prepeatx;
                                                                prepeaty=m->prepeaty;
                                                                pmipmap=m->pmipmap;
                                                                lx=m->lx;
                                                                ly=m->ly;
                                                                lchannels=m->lchannels;
                                                                pdepth=m->pdepth;
                                                                lname=m->lname;
                                                                pgrafik=0;
                                                                pbildhardware=0;
                                                                int z=lchannels*lx*ly;
                                                                ldata=new _tb[z];
                                                                int i;
                                                                for(i=0;i<z;i++) ldata[i]=m->ldata[i];
};
template<class _tb> _bild<_tb>::~_bild(){
                                                                pwirdgeloescht=true;
                                                                loeschenbildhardware();
                                                                if(ldata) delete[] ldata;
                                                                //if(pbildhardware){
                                                                // pbildhardware->bild(0);
                                                                //};
                                                                //if(pgrafik) if(pmapid) pgrafik->loeschenbild(this);
                                                                
};

template<class _tb> void _bild<_tb>::bildhardware(_bildhardware*bhw){
                                                                //if (pbildhardware) loeschenbildhardware();
                                                                pbildhardware=bhw;
};
template<class _tb> _bildhardware* _bild<_tb>::bildhardware(){
                                                                return(pbildhardware);
};
template<class _tb> void _bild<_tb>::loeschenbildhardware(){
                                                                if (pbildhardware){
                                                                 delete pbildhardware;
                                                                 pbildhardware=0;
                                                                };
};                                                                
template<class _tb> void _bild<_tb>::init(){
                                                                pwirdgeloescht=false;
                                                                pjpg=false;
                                                                ldata=0;
                                                                lx=1;
                                                                ly=1;
                                                                lchannels=3;
                                                                poriginxright=false;
                                                                poriginydown=false;
                                                                
                                                                pdepth=1;
                                                                lname="bild name default";
};
template<class _tb> void _bild<_tb>::schreiben(const _vektor<_tb>&v){
                                                                if(v.holendimension()!=lchannels) return;
                                                               
                                                                unsigned int i=0;
                                                                for(unsigned int x=0;x<lx;x++)
                                                                for(unsigned int y=0;y<ly;y++) 
                                                                for(unsigned int c=0;c<lchannels;c++) {
                                                                 ldata[c+(y*lx+x)*lchannels]=v[c];
                                                                };
};
/*
template<class _tb> void _bild<_tb>::schreiben(const _vektor<_to>&v){
                                                                if(v.holendimension()!=lchannels) return;
                                                               
                                                                unsigned int i=0;
                                                                for(unsigned int x=0;x<lx;x++)
                                                                for(unsigned int y=0;y<ly;y++) 
                                                                for(unsigned int c=0;c<lchannels;c++) {
                                                                 ldata[c+(y*lx+x)*lchannels]=_tb(v[c]);
                                                                };
};*/
template<class _tb> void _bild<_tb>::schreiben(unsigned int x, unsigned int y,const _vektor<_tb>&v){
                                                                if (x>=lx || y>=ly || x<0 || y<0) return;
                                                                if (v.holendimension()!=lchannels) return;
                                                                for (unsigned int channel=0; channel<lchannels; channel++)
                                                                {
                                                                 ldata[channel+(y*lx+x)*lchannels] = v[channel];
                                                                }
};
template<class _tb> void _bild<_tb>::lesen(unsigned int x,unsigned int y,_vektor<_tb>&v){
                                                                if ((x>=lx) || (y>=ly)) return;
                                                             //   if (v.holendimension()!=lchannels) return;
                                                                for (unsigned int channel=0; channel<lchannels; channel++)
                                                                {
                                                                 v.setzenkomponente(channel,ldata[channel+(y*lx+x)*lchannels]);
                                                                }
};

template<class _tb> void _bild<_tb>::groesse(unsigned int x,unsigned int y){
                                                                lx=x;
                                                                ly=y;
                                                                if(lx==0)lx=1;
                                                                if(ly==0)ly=1;
                                                                if(ldata) delete[] ldata;
                                                                ldata=new _tb[lx*ly*lchannels];
};
template<class _tb> void _bild<_tb>::groesse(unsigned int x,unsigned int y,unsigned int c){
                                                                lx=x;
                                                                ly=y;
                                                                lchannels=c;
                                                                if(lx==0)lx=1;
                                                                if(ly==0)ly=1;
                                                                if(ldata) delete[] ldata;
                                                                ldata=new _tb[lx*ly*lchannels];
};
template<class _tb> unsigned int _bild<_tb>::speicherlast() const{
                                                                return(lchannels*sizeof(_tb)*lx*ly);
};
/*
template<class _tb> unsigned int _bild<_tb>::groessex() const{
                                                                return(lx);
};
template<class _tb> unsigned int _bild<_tb>::groessey() const{
                                                                return(ly);
};
*/
template<class _tb> unsigned int _bild<_tb>::groesse(unsigned char coordinate) {
                                                                switch(coordinate)
                                                                {
                                                                 case 0:
                                                                  return(lx);
                                                                 break;
                                                                 case 1:
                                                                  return(ly);
                                                                 break;
                                                                }
                                                                return(lx);
};
template<class _tb> unsigned int _bild<_tb>::breite()const{
                                                                return(lx);
};
template<class _tb> unsigned int _bild<_tb>::hoehe()const{
                                                                return(ly);
};

template<class _tb> _tb* _bild<_tb>::daten(){
                                                                return(ldata);
};
template<class _tb> void _bild<_tb>::daten(_tb*t,unsigned int wx,unsigned int wy,unsigned int ch,_tb pd){
                                                                if(t!=0){
                                                                 entladen();
                                                                 ldata=t;
                                                                 if(wx<1) wx=1;
                                                                 if(wy<1) wy=1;
                                                                 lx=wx;
                                                                 ly=wy;
                                                                 kanaele(ch);
                                                                 pdepth=pd;
                                                                };
};
template<class _tb> void _bild<_tb>::kanaele(unsigned int c){
                                                                if(c<=0) c=1;
                                                                lchannels=c;
};
template<class _tb> unsigned int _bild<_tb>::kanaele() const{
                                                                return(lchannels);
};
template<class _tb> bool _bild<_tb>::ursprungrechts()const{
                                                                return(poriginxright);
};
template<class _tb> bool _bild<_tb>::ursprungunten()const{
                                                                return(poriginydown);
};

template<class _tb> void _bild<_tb>::tiefeloeschen(_tb c){
                                                                unsigned long int i;
                                                                unsigned long int is;
                                                                //------------------------
                                                                if(c<1) c=1;
                                                                if(c!=pdepth){
                                                                 is=lx*ly*lchannels;
                                                                 for(i=0;i<is;i++){
                                                                  if(ldata[i]>c) ldata[i]=0; 
                                                                 };
                                                                 pdepth=c;
                                                                };
};
template<class _tb> void _bild<_tb>::tiefereskalieren(_tb c){
                                                                //redimensioniert den farbbereich (zb. 0-1 oder 0-255)  
                                                                //und scaliert alles mit einem faktor 
                                                                unsigned long int ix;
                                                                unsigned long int iy;
                                                                unsigned long int ic;
                                                                unsigned long int in;
                                                                double f;
                                                                //------------------
                                                                if(c<1) c=1;
                                                                if(c!=pdepth){
                                                                 f=double(c)/double(pdepth);
                                                                 for(iy=0;iy<ly;iy++)
                                                                 for(ix=0;ix<lx;ix++)
                                                                 for(ic=0;ic<lchannels;ic++){
                                                                  in=(iy*lx+ix)*lchannels+ic;
                                                                  ldata[in]=_tb(double(ldata[in])*f);
                                                                 };
                                                                 pdepth=c;
                                                                };
};
template<class _tb> void _bild<_tb>::depthclip(_tb c){
                                                                //redimensioniert den farbbereich (zb. 0-1 oder 0-255)  und clipt ggf. die werte auf die ober-
                                                                //grenze c ab
                                                                unsigned long int ix;
                                                                unsigned long int iy;
                                                                unsigned long int ic;
                                                                unsigned long int in;
                                                                //------------------
                                                                if(c!=pdepth){
                                                                 if(c<1) c=1;
                                                                 for(iy=0;iy<ly;iy++)
                                                                 for(ix=0;ix<lx;ix++)
                                                                 for(ic=0;ic<lchannels;ic++){
                                                                  in=(iy*lx+ix)*lchannels+ic;
                                                                  if(ldata[in]>c) ldata[in]=c;
                                                                 };
                                                                 pdepth=c;
                                                                };
};
template<class _tb> _tb _bild<_tb>::tiefe() const{
                                                                return(pdepth);
};
template<class _tb> void _bild<_tb>::name(_zeichenkette<char> s){
                                                                lname=s;
};
template<class _tb> _zeichenkette<char> _bild<_tb>::name() const{
                                                                return(lname);
};
template<class _tb> bool _bild<_tb>::geladen() const{
                                                                if(ldata!=0) return(true); else return(false);
};
template<class _tb> void _bild<_tb>::entladen(){
                                                                if(ldata){                
                                                                 delete[] ldata;
                                                                 ldata=0;
                                                                };
};
/*
template<class _tb> bool _bild<_tb>::laden(){
                                                                return(false);
};
template<class _tb> void _bild<_tb>::speichern(){
};
*/
template<class _tb> bool _bild<_tb>::laden(){
                                                                _zeichenkette<char> n=dateiname();
                                                                n.konvertiereninklein();
                                                                unsigned int i=0;
                                                                if(dateiexistiert(n)==false) return(false);
                                                                if(n.suchen(".tga",i)){
                                                                 return(ladentga());
                                                                }else{
                                                                 i=0;
                                                                 if(n.suchen(".png",i)){
                                                                  return(ladenpng());
                                                                 }else{
                                                                  return(ladenjpg());
                                                                 };
                                                                };
                                                                return(false);
};
template<class _tb> void _bild<_tb>::speichern(){
                                                                _zeichenkette<char> n=dateiname();
                                                                n.konvertiereninklein();
                                                                unsigned int i=0;
                                                                if(n.suchen(".tga",i)){
                                                                 speicherntga();
                                                                }else{
                                                                 i=0;
                                                                 if(n.suchen(".png",i)){
                                                                  speichernpng();
                                                                 }else{
                                                                  speichernjpg(10);
                                                                 };
                                                                };
};

template<class _tb> bool _bild<_tb>::ladenjpg(){
															   jpeg_decompress_struct  cinfo; 
															   jpeg_error_mgr          jerr; 
															   jpeg_source_mgr         jsrc; 
															   JSAMPARRAY              array; 
															   // ----------------------------------------------------- 
																_tb*buffer=0;
																unsigned int size=0;
																L->schreiben("JPG soll geladen werden : ",dateiname());
																L->schreiben("struct size decompress =",(int) sizeof(struct jpeg_decompress_struct));
																if(_datei::oeffnennurlesen()==false){
																 L->schreiben("_bild<_tb>::ladenjpg() : FEHLER Datei nicht gefunden",dateiname());
																 return(false);
																}else{
																 size=_datei::groesse();
																 L->schreiben("Dateigroesse : ",(int)size);
																 buffer=new _tb[size];
																 unsigned long int read=0;
																 if(_datei::laden((char*)buffer,size,read)==false) L->schreiben("_bild<_tb>::ladenjpg : Fehler beim Einladen der Rohdaten");
																 _datei::schliessen();
																};
															    
															   cinfo.err=jpeg_std_error(&jerr); 
															   jpeg_create_decompress(&cinfo); 
															   jpeg_memory_src(&cinfo,&jsrc,buffer,size); 
															   jpeg_read_header(&cinfo,TRUE); 
															   jpeg_start_decompress(&cinfo); 
															    
															   groesse(cinfo.output_width,cinfo.output_height,cinfo.output_components); 
															    
															   unsigned int rowsize=lx*lchannels; 
															   _tb*tempData=ldata+rowsize*(ly-1); 
															   array    = new unsigned char *[1]; 
															   array[0] = new unsigned char [rowsize]; 
															   while(cinfo.output_scanline < cinfo.output_height){ 
																jpeg_read_scanlines(&cinfo, array, 1); 
																memcpy(tempData, array[0], rowsize); 
																tempData -= rowsize; 
															   };
															   delete[] array[0]; 
															   delete[] array; 
															    
															   jpeg_finish_decompress(&cinfo); 
															   jpeg_destroy_decompress(&cinfo); 


															   delete[] buffer;
															   return(true); 
};

/*

template<class _tb> bool _bild<_tb>::ladenjpg(){
                                                                struct jpeg_decompress_struct cinfo;
                                                                struct my_error_mgr jerr;
                                                                FILE * infile;		
                                                                JSAMPARRAY buffer;	
                                                                int row_stride;		
																L->schreiben("JPG soll geladen werden : ",dateiname());
                                                                if((infile = fopen(dateiname(), "rb")) == NULL) {
                                                                 fprintf(stderr, "can't open %s\n", dateiname());
																 L->schreiben("_bild<_tb>::ladenjpg() : FEHLER Datei nicht gefunden",dateiname());
                                                                 return(false);
                                                                };
                                                                cinfo.err=jpeg_std_error(&jerr.pub);
                                                                jerr.pub.error_exit=my_error_exit;
                                                                if(setjmp(jerr.setjmp_buffer)) {
                                                                 jpeg_destroy_decompress(&cinfo);
                                                                 fclose(infile);
																
                                                                 return(false);
                                                                };
                                                                jpeg_create_decompress(&cinfo);
                                                                jpeg_stdio_src(&cinfo, infile);
                                                                (void) jpeg_read_header(&cinfo, TRUE);
                                                                (void) jpeg_start_decompress(&cinfo);
                                                                L->schreiben("Hier");
                                                                
                                                                groesse(cinfo.output_width,cinfo.output_height,cinfo.output_components); 
                                                                _tb*td=ldata;
                                                                
                                                                row_stride = cinfo.output_width * cinfo.output_components;
                                                                buffer=(*cinfo.mem->alloc_sarray) ((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);
                                                                while (cinfo.output_scanline < cinfo.output_height){
                                                                 (void) jpeg_read_scanlines(&cinfo, buffer, 1);
                                                                  memcpy(td,buffer[0],row_stride); 
                                                                  td+=row_stride;
                                                                 //put_scanline_someplace(buffer[0], row_stride);
                                                                 
                                                                };
                                                                (void) jpeg_finish_decompress(&cinfo);
                                                                jpeg_destroy_decompress(&cinfo);
                                                                fclose(infile);
                                                                return(true);


};*/
template<class _tb> void _bild<_tb>::speichernjpg(int quality){
                                                                struct jpeg_compress_struct cinfo;
                                                                struct jpeg_error_mgr jerr;
                                                                FILE * outfile;		/* target file */
                                                                JSAMPROW row_pointer[1];	/* pointer to JSAMPLE row[s] */
                                                                int row_stride;		/* physical row width in image buffer */
                                                                cinfo.err = jpeg_std_error(&jerr);
                                                                jpeg_create_compress(&cinfo);
                                                                if ((outfile = fopen(dateiname(), "wb")) == NULL) {
                                                                 fprintf(stderr, "can't open %s\n", dateiname());
                                                                 exit(1);
                                                                }
                                                                jpeg_stdio_dest(&cinfo, outfile);
                                                                cinfo.image_width = lx; 	/* image width and height, in pixels */
                                                                cinfo.image_height = ly;
                                                                cinfo.input_components = 3;		/* # of color components per pixel */
                                                                cinfo.in_color_space = JCS_RGB; 	/* colorspace of input image */
                                                                jpeg_set_defaults(&cinfo);
                                                                jpeg_set_quality(&cinfo, quality, TRUE /* limit to baseline-JPEG values */);
                                                                jpeg_start_compress(&cinfo, TRUE);

                                                                row_stride = lx * 3;	/* JSAMPLEs per row in image_buffer */
                                                                while (cinfo.next_scanline < cinfo.image_height) {
                                                                 row_pointer[0] = & ldata[cinfo.next_scanline * row_stride];
                                                                 (void) jpeg_write_scanlines(&cinfo, row_pointer, 1);
                                                                };
                                                                jpeg_finish_compress(&cinfo);
                                                                fclose(outfile);
                                                                jpeg_destroy_compress(&cinfo);
};

template<class _tb> bool _bild<_tb>::ladentga(){
                                                                unsigned char origheader[12]={0,0,2,0,0,0,0,0,0,0,0,0};
                                                                unsigned char compareheader[12];
                                                                unsigned char infoheader[6];
                                                                unsigned long int bypp;
                                                                unsigned long int bpp;
                                                                unsigned long int imgsize;
                                                                unsigned long int wx;
                                                                unsigned long int wy;
                                                                unsigned long int geladen;
                                                                unsigned long int i;
                                                                _tb*cdata;
                                                                unsigned char*tempbytes;
                                                                //unsigned char*c;
                                                                //-----------------------------------------------------
                                                                entladen();
                                                                //c=dateiname();
                                                                //datei=fopen((char*)c,"rb");
                                                                //if(datei==0) {
                                                                if(oeffnen()==false){//dateiname ist fehlgeschlagen
                                                                 notfallinitialisierung(4,4);
                                                                 return(false);
                                                                };
                                                                position(0);
                                                                laden((char*)compareheader,12,geladen);
                                                                if(geladen!=12){//id-header nicht gültig
                                                                 notfallinitialisierung(4,4);
                                                                 schliessen();
                                                                 return(false);
                                                                };
                                                                if(memcmp(origheader,compareheader,12)!=0){//id-header ist ungültig
                                                                 notfallinitialisierung(4,4);
                                                                 schliessen();
                                                                 return(false);
                                                                };
                                                                laden((char*)infoheader,6,geladen);
                                                                if(geladen!=6){//infoheader nicht gültig
                                                                 notfallinitialisierung(4,4);
                                                                 schliessen();
                                                                 return(false);
                                                                };
                                                                //if(
                                                                //(fread(compareheader,1,sizeof(compareheader),datei)!=sizeof(compareheader))||
                                                                //(memcmp(origheader,compareheader,sizeof(origheader))!=0)||
                                                                //(fread(infoheader,1,sizeof(infoheader),datei)!=sizeof(infoheader))
                                                                //){
                                                                // fclose(datei);
                                                                // notfallinitialisierung(4,4);
                                                                // return(0);
                                                                //};
                                                                //wx,wy
                                                                wx=abs(infoheader[1]*256+infoheader[0]);
                                                                wy=abs(infoheader[3]*256+infoheader[2]);
                                                                if(wx<1){//infoheader-breite nicht gültig
                                                                 notfallinitialisierung(4,4);
                                                                 schliessen();
                                                                 return(false);
                                                                };
                                                                if(wy<1){//infoheader-höhe nicht gültig
                                                                 notfallinitialisierung(4,4);
                                                                 schliessen();
                                                                 return(false);
                                                                };
                                                                if((infoheader[4]!=24)&&(infoheader[4]!=32)) {//infoheader bezeichnet keine gültige kanalanzahl
                                                                 notfallinitialisierung(wx,wy);
                                                                 schliessen();
                                                                 return(false);
                                                                };
                                                                //daten laden
                                                                bpp=infoheader[4];
                                                                bypp=infoheader[4]/8;
                                                                imgsize=wy*wx*bypp;
                                                                tempbytes=new unsigned char[imgsize];
                                                                laden((char*)tempbytes,imgsize,geladen);
                                                                cdata=new _tb[imgsize];
                                                                //laden(cdata,wx*wy*bypp,geladen);
                                                                for(i=0;i<imgsize;i++){
                                                                 cdata[i]=_tb(tempbytes[i]);
                                                                };
                                                                char bf=infoheader[5];//0000E000
                                                                if ((1<<4)&bf) poriginxright=true; else poriginxright=false;
                                                                if ((1<<5)&bf) poriginydown=false; else poriginydown=true;
                                                                delete[] tempbytes;
                                                                if(geladen!=imgsize){//ladevorgang unvollständig
                                                                 schliessen();
                                                                 //datentausch();
                                                                 daten(cdata,wx,wy,bypp,255);
                                                                 return(false);
                                                                };
                                                                //G->tm->incloadcounter();
                                                                //if((cdata==0)||(fread(cdata,sizeof(_tb),imgsize,datei)!=imgsize)){
                                                                 //entladen();//delete daten;
                                                                // schliessen();
                                                                // return(0);
                                                                //};
                                                                schliessen();
                                                                //datentausch();
                                                               /* for(i=0;i<imgsize;i+=bypp){
                                                                 temp=cdata[i];
                                                                 cdata[i]=cdata[i+2];
                                                                 cdata[i+2]=temp;
                                                                };*/
                                                                daten(cdata,wx,wy,bypp,255);
																datentausch(0,2);
                                                                //G->fim->schreiben("_bitmap::laden mit ",name);
                                                                return(true);
                                                                //return(_filetga<_tb>::laden());
};
template<class _tb> void _bild<_tb>::speicherntga(){
                                                                unsigned char origheader[12]={0,0,2,0,0,0,0,0,0,0,0,0};
                                                                unsigned char infoheader[6];
                                                                unsigned char*tempbytes;
                                                                unsigned long int is;
                                                                unsigned long int i;
                                                                double f;
                                                                //-----------------------------
                                                                infoheader[1]=groesse(0)/256;
                                                                infoheader[0]=groesse(0)-(infoheader[1]*256);
                                                                infoheader[3]=groesse(1)/256;
                                                                infoheader[2]=groesse(1)-(infoheader[3]*256);
                                                                infoheader[4]=kanaele()*8;
                                                                infoheader[5]=8;
                                                                if(oeffnen()){
                                                                 datentausch(0, 2);
                                                                 loeschen();
                                                                 speichern((char*)origheader,12);
                                                                 speichern((char*)infoheader,6);
                                                                 is=groesse(0)*groesse(1)*kanaele();
                                                                 f=double(255)/double(tiefe());
                                                                 tempbytes=new unsigned char[is];
                                                                 for(i=0;i<is;i++) {
                                                                  tempbytes[i]=(char)(double(daten()[i])*f);
                                                                 };
                                                                 speichern((char*)tempbytes,groesse(0)*groesse(1)*kanaele());
                                                                 //speichern(daten(),groessex()*groessey()*kanaele());
                                                                 delete[] tempbytes;
                                                                 datentausch(0, 2);
                                                                 schliessen();
                                                                };
};

template<class _tb> bool _bild<_tb>::ladenpng(){
																if(_datei::oeffnennurlesen()){
																 std::vector<_tb> buffer;
																 unsigned int const size=_datei::groesse();
																 //------------------------------------------------------------- 
																 if(!_datei::laden(buffer, size)) return(false);
																 _datei::schliessen();
																 //check signature
																 if(png_sig_cmp(&buffer[0],0,8)) return(false);
																 //create read struct
																 png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
																 if(!png_ptr) return(false);
																 // create info struct
																 png_infop info_ptr=png_create_info_struct(png_ptr);
																 if(!info_ptr){
																  png_destroy_read_struct(&png_ptr,0,0);
																  return(false);
																 };
																 //setup file buffer
																 pngFileBuffer_t filebuffer;
																 filebuffer.buffer=&buffer[0];
																 filebuffer.pos=0;
																 png_set_read_fn(png_ptr,&filebuffer,user_read_data);
																 png_read_info(png_ptr,info_ptr);
																 
																 entladen();
																 lx=info_ptr->width;
																 ly=info_ptr->height;
																 lchannels=info_ptr->channels;
																 int const rowSize=lx*lchannels;
																 poriginxright=false;
																 poriginydown=true;
																 ldata=new _tb[rowSize*ly];
																 if((3!=lchannels) && (4!=lchannels)){
																  png_destroy_read_struct(&png_ptr,&info_ptr,0);
																  return(false);
																 };
																 _tb**rows=new _tb*[ly];
																 _tb*tempPixels=ldata+rowSize*(ly-1);
																 for(unsigned int i=0;i<ly;i++,tempPixels-=rowSize) rows[i]=tempPixels;
																 png_read_image(png_ptr,rows);
																 delete[] rows;
																 png_destroy_read_struct(&png_ptr,&info_ptr,0);
																 return(true);
																}else{
																 return(false);
																};
};
template<class _tb> void _bild<_tb>::speichernpng(){
};
/*
 bool Image::readPNG(StreamContainer &container) 
{ 

}










class BASE_API StreamContainer 
{ 
   public: 
     StreamContainer(std::istream *s = 0, bool del = true); 
     virtual ~StreamContainer(); 
      
     std::istream *getStream(); 
     void setStream(std::istream *s); 
      
     bool isGood() const; 
      
     Int32 getPos() const; 
     void setPos(Int32 pos); 
      
     void skipPos(Int32 amount); 
      
     Int32 getSize(); 
      
     bool read(void *dest, Int32 size); 
     bool read(std::vector<UInt8> &buffer, Int32 size); 
      
      
   private: 
     std::istream  *m_stream; 
     bool          m_delete; 
};

*/
/*
template<class _tb> void _bild<_tb>::bildidentifikation(const unsigned int pm,_grafik*g){
                                                                pmapid=pm;
                                                                pgrafik=g;
};
template<class _tb> unsigned int _bild<_tb>::bildidentifikation() const{
                                                                return(pmapid);
};
*/
template<class _tb> void _bild<_tb>::shaderid(const unsigned int ps){
                                                                pshaderid=ps;
};
template<class _tb> unsigned int _bild<_tb>::shaderid() const{
                                                                return(pshaderid);
};
template<class _tb> void _bild<_tb>::index(const unsigned int i){
                                                                pindex=i;
};
template<class _tb> unsigned int _bild<_tb>::index()const{
                                                                return(pindex);
};
template<class _tb> void _bild<_tb>::wiederholung(const unsigned int i,const bool b){
                                                                if(i==0) prepeatx=b; else prepeaty=b;
};
template<class _tb> bool _bild<_tb>::wiederholung(const unsigned int i) const{
                                                                if(i==0) return(prepeatx); else return(prepeaty);
};
template<class _tb> void _bild<_tb>::mipmap(const bool b){
                                                                pmipmap=b;
};
template<class _tb> bool _bild<_tb>::mipmap() const{
                                                                return(pmipmap);
};
template<class _tb> void _bild<_tb>::notfallinitialisierung(unsigned int wx,unsigned int wy){
                                                                unsigned long int i;
                                                                unsigned long int bpp;
                                                                unsigned long int groesse;
                                                                unsigned long int bypp;
                                                                unsigned long int ch=3;
                                                                //--------
                                                                entladen();
                                                                if(wx<1) wx=1;
                                                                if(wy<1) wy=1;
                                                                if(ch<1) ch=1;
                                                                //wx=4;
                                                                //wy=4;
                                                                bpp=ch*8;
                                                                bypp=ch;
                                                                kanaele(ch);
                                                                groesse=wx*wy*ch;
                                                                ldata=new _tb[groesse];
                                                                for(i=0;i<groesse;i+=bypp){
                                                                 if(((i/ch)%2)==0){
                                                                  ldata[i]=255;
                                                                  ldata[i+1]=255;
                                                                 }else{
                                                                  ldata[i]=0;
                                                                  ldata[i+1]=0;
                                                                 };
                                                                 ldata[i+2]=0;
                                                                };
                                                                lx=wx;
                                                                ly=wy;
};
template<class _tb> void _bild<_tb>::datentausch(unsigned int c0,unsigned int c1){                                                                
                                                                unsigned long int n;
                                                                unsigned long int groesse;
                                                                _tb c;
                                                                //-----------
                                                                if((c0>=0)&&(c0<lchannels)&&(c1>=0)&&(c1<lchannels)&&(c0!=c1)){
                                                                 groesse=lx*ly*lchannels;
                                                                 for(n=0;n<groesse;n+=lchannels){
                                                                  c=ldata[n+c0];
                                                                  ldata[n+c0]=ldata[n+c1];
                                                                  ldata[n+c1]=c;
                                                                 };
                                                                };
};

template<class _tb> char _bild<_tb>::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_bild>*sd){
                                                                char r=1;
                                                                _zeichenkette<char> fname;
                                                                _zeichenkette<char> mname;
                                                                r^=sd->ladenbeginn(fn);
                                                                r^=sd->ladenverschachtelung(fn);
                                                                //r^=sd->ladenwert(fname);
                                                                r^=sd->ladenwert(lname);
                                                                //r^=sd->ladenwert(f);
                                                                //r^=sd->ladenassoziation();
                                                                sd->ladenende();
                                                                return(r);
};

template<class _tb> void _bild<_tb>::speichern(_speicherbardynamisch<_bild>*sd){
                                                                sd->speichernbeginn();
                                                                sd->speichernverschachtelung();
                                                                //sd->speichernwert(_datei::dateiname());
                                                                sd->speichernwert(lname);
                                                                //sd->speichernwert(f);
                                                                //saveassociationargument(sd->datei(),sd,d);
                                                                sd->speichernende();
                                                                
};

template<class _tb> char _bild<_tb>::assoziieren(_speicherbardynamisch<_bild>*sd){
                                                                sd->assoziierenverschachtelung();
                                                                return(1);
};
template<class _tb> _zeichenkette<char> _bild<_tb>::typ()const{
                                                                return("_bild");
};                                                                



//******************************************************************************************************************************************************************************************************
//                                                              B I L D H A R D W A R E
//******************************************************************************************************************************************************************************************************
class _bildhardware:public _listenknotenbasis<_bildhardware>{
        public:
                _bildhardware(_grafik*g,_bild<_tb>*b);
                virtual ~_bildhardware();
                void bild(_bild<_tb>*);
                _bild<_tb>*bild();
                virtual void loeschen()=0;
                virtual bool binden()=0;
                virtual void wiederherstellen()=0;
                virtual void lesen(_to*)=0;
                virtual bool oeffnen()=0;
                virtual _tb*daten()=0;
                virtual void schliessen()=0;
				_tg skalierungx()const;
				_tg skalierungy()const;
		protected:
				void skalierungx(const _tg);
				void skalierungy(const _tg);
        private:
                _grafik*pgrafik;     
				_bild<_tb>*pbild;
				_tg pxscale;
				_tg pyscale;
};
//******************************************************************************************************************************************************************************************************
//                                                              M A P T G A 
//******************************************************************************************************************************************************************************************************
/*template<class _tb>
class _bildtga:public _bild<_tb>,public _datei{
        public:
        using         _datei::laden;
        using         _datei::speichern;
        using         _bild<_tb>::datentausch;
        public:
                _bildtga();//ladekonstruktor
                _bildtga(unsigned int,unsigned int);
                _bildtga(_zeichenkette<char>,unsigned int,unsigned int);
                virtual bool laden();
                virtual void speichern();
                //void datentausch();
                //speichern
                virtual char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_bild<_tb> >*);
                virtual void speichern(_speicherbardynamisch<_bild<_tb> >*);
                virtual char assoziieren(_speicherbardynamisch<_bild<_tb> >*);
                virtual _zeichenkette<char> typ()const;
};
template<class _tb> _bildtga<_tb>::_bildtga():_bild<_tb>(1,1),_datei("maptga.tga"){
};
template<class _tb> _bildtga<_tb>::_bildtga(unsigned int x,unsigned int y):_bild<_tb>(x,y),_datei("maptga.tga"){
};
template<class _tb> _bildtga<_tb>::_bildtga(_zeichenkette<char> f,unsigned int x,unsigned int y):_bild<_tb>(x,y),_datei(f){
                                                                if(laden()) {
                                                                 L->schreiben("_bildtga<_tb> : Laden eines Bildes erfolgreich.");
                                                                }else{
                                                                };
};
*/
/*
template<class _tb> char _bildtga<_tb>::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_bild<_tb> >*sd){
                                                                char r=1;
                                                                _zeichenkette<char> fname;
                                                                _zeichenkette<char> mname;
                                                                r^=sd->ladenbeginn(fn);
                                                                r^=sd->ladenverschachtelung(fn);
                                                                r^=sd->ladenwert(fname);
                                                                r^=sd->ladenwert(mname);
                                                                _datei::dateiname(fname);
                                                                _bild<_tb>::name(mname);
                                                                laden();
                                                                sd->ladenende();
                                                                return(r);
};
template<class _tb> void _bildtga<_tb>::speichern(_speicherbardynamisch<_bild<_tb> >*sd){
                                                                //unsigned int c;
                                                                _zeichenkette<char> fname;
                                                                _zeichenkette<char> mname;
                                                                
                                                                sd->speichernbeginn();
                                                                sd->speichernverschachtelung();
                                                                fname=_datei::dateiname();
                                                                mname=_bild<_tb>::name();
                                                                sd->speichernwert(fname);
                                                                sd->speichernwert(mname);
                                                                sd->speichernende();
                                                                
};
template<class _tb> char _bildtga<_tb>::assoziieren(_speicherbardynamisch<_bild<_tb> >*sd){
                                                                sd->assoziierenverschachtelung();
                                                                return(1);
};
template<class _tb> _zeichenkette<char> _bildtga<_tb>::typ()const{
                                                                return("_bildtga");
};
*/                                                                
/*
template<class _color=float> class _mapbmp:public _bild<_color>{
        public:
                _mapbmp(_zeichenkette&);
                _mapbmp(unsigned int,unsigned int);
                virtual char laden();
                virtual void speichern();
};
template<class _color=float> class _mapjpg:public _bild<_color>{
        public:
                _mapbmp(_zeichenkette&);
                _mapbmp(unsigned int,unsigned int);
                virtual char laden();
                virtual void speichern();
};
*/
/*
template<class _typtext,class _coloranim,class _colordraw>
class _maptgamap:public _bildtga<_typtext,_coloranim>,public _bild<_typtext,_colordraw>{
        public:
                _maptgamap(_zeichenkette<_typtext>);
                _maptgamap(_zeichenkette<_typtext>,unsigned int,unsigned int);
};
*/
/*
template<class _coloranim=float,class _colordraw=char> class _mapmaptga:public _mapmap<_coloranim,_colordraw>{
        public:
                _mapmaptga(_zeichenkette&);
                _mapmaptga(unsigned int,unsigned int);
};
*/
/*
template<class T>class _bitmapnode:public _bitmap<T>,public _listenknotenbasis<_bitmapnode<T> >{
        public:
                _bitmapnode(_zeichenkette&,_listebasis<_bitmapnode<T> >*);
};
*/
//******************************************************************************************************************************************************************************************************
//                                                              T E X T U R E 
//******************************************************************************************************************************************************************************************************
template<class _tb>
class _textur:public _listenknotenbasis<_textur<_tb> >,public _basis::_speicherbarargument<_textur<_tb> >,public _speicherbarbinaer{
		friend class _texturverwaltung<_tb>;
		public:
				using _listenknotenbasis<_textur<_tb> >::einhaengen;
        public:
                _textur();
                _textur(_textur<_tb>*);
                _textur(_listebasis<_textur<_tb> >*);
                _textur(_listebasis<_textur<_tb> >*,_zeichenkette<char>);//RH -> OOS : diesen konstruktopr benutzten, assoziation der polygon durch texturenamen
                _textur(_zeichenkette<char> );
                virtual ~_textur();
                
                void index(const unsigned int);
                unsigned int index()const;
                
                bool identischetextur(_textur<_tb>*t);
                
                void loeschen();

                void loeschenbitmap();
                void loeschenlightmap();
                void loeschenshadowmap();
                void loeschenbumpmap();
                void loeschentranslightmap();
                void loeschendetailmap();
                void loeschenmaskmap();
                void loeschenspecularmap();

                void einfuegenbitmap(_bild<_tb>*);
                void einfuegenlightmap(_bild<_tb>*);
                void einfuegenshadowmap(_bild<_tb>*);
                void einfuegenbumpmap(_bild<_tb>*);
                void einfuegentransmissionmap(_bild<_tb>*);
                void einfuegendetailmap(_bild<_tb>*);
                void einfuegenmaskmap(_bild<_tb>*);
                void einfuegenspecularmap(_bild<_tb>*);

                inline _liste<_bild<_tb> >*bitmap();
                inline _bild<_tb>*bitmap(unsigned int i);
                inline _liste<_bild<_tb> >*lightmap();
                inline _liste<_bild<_tb> >*shadowmap();
                inline _liste<_bild<_tb> >*bumpmap();
                inline _liste<_bild<_tb> >*translightmap();
                inline _liste<_bild<_tb> >*specularmap();
                inline _liste<_bild<_tb> >*detailmap();
                inline _liste<_bild<_tb> >*maskmap();
                _zeichenkette<char> name() const;
                void name(const _zeichenkette<char>);

                bool geladen();
                void laden();
                void entladen();
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_textur>*);
                void speichern(_speicherbardynamisch<_textur>*);
                char assoziieren(_speicherbardynamisch<_textur>*);

				bool laden(_dateispeicherbarbinaer*);
				void speichern(_dateispeicherbarbinaer*);
				bool assoziieren();
				//void assoziieren(_texturverwaltung<_tb>*tb);
                
        private:
                bool geladen(_listebasis<_bild<_tb> >&);
                void laden(_listebasis<_bild<_tb> >&);
                void entladen(_listebasis<_bild<_tb> >&);
        private:
                _liste<_bild<_tb> > pbitmaps;
                _liste<_bild<_tb> > plightmaps;
                _liste<_bild<_tb> > pshadowmaps;
                _liste<_bild<_tb> > pbumpmaps;
                _liste<_bild<_tb> > ptranslightmaps;
                _liste<_bild<_tb> > pspecularmaps;
                _liste<_bild<_tb> > pdetailmaps;
                _liste<_bild<_tb> > pmaskmaps;
                _zeichenkette<char> pname;
                unsigned int pindex;
        public:                
                unsigned int pc[8];
                
		private:
				_liste<_zeichenkette<char> > pbitmapstrings;                
				_liste<_zeichenkette<char> > plightmapstrings;                
				_liste<_zeichenkette<char> > pshadowmapstrings;                
				_liste<_zeichenkette<char> > pbumpmapstrings;                
				_liste<_zeichenkette<char> > ptranslightmapstrings;                
				_liste<_zeichenkette<char> > pspecularmapstrings;                
				_liste<_zeichenkette<char> > pdetailmapstrings;                
				_liste<_zeichenkette<char> > pmaskmapstrings;                
};
template<class _tb>_textur<_tb>::_textur(){
                                                                pname="default textur name";
                                                                pindex=0;
};
template<class _tb>_textur<_tb>::_textur(_textur<_tb>*t){
																pname=t->pname;
																pindex=t->pindex;
																_listenknoten<_bild<_tb> >*b;
																iterierenliste((&t->pbitmaps),b,pbitmaps.einhaengen(b->objekt()));
																iterierenliste((&t->plightmaps),b,plightmaps.einhaengen(b->objekt()));
																iterierenliste((&t->pshadowmaps),b,pshadowmaps.einhaengen(b->objekt()));
																iterierenliste((&t->pbumpmaps),b,pbumpmaps.einhaengen(b->objekt()));
																iterierenliste((&t->ptranslightmaps),b,ptranslightmaps.einhaengen(b->objekt()));
																iterierenliste((&t->pspecularmaps),b,pspecularmaps.einhaengen(b->objekt()));
																iterierenliste((&t->pdetailmaps),b,pdetailmaps.einhaengen(b->objekt()));
																iterierenliste((&t->pmaskmaps),b,pmaskmaps.einhaengen(b->objekt()));
};

template<class _tb>_textur<_tb>::_textur(_listebasis<_textur<_tb> >*l):_listenknotenbasis<_textur<_tb> >(l){
                                                                pname="default textur name";
                                                                pindex=0;
};
template<class _tb>_textur<_tb>::_textur(_listebasis<_textur<_tb> >*l,_zeichenkette<char> s):_listenknotenbasis<_textur<_tb> >(l){
                                                                pname=s;
                                                                pindex=0;
};
template<class _tb>_textur<_tb>::_textur(_zeichenkette<char> s):_listenknotenbasis<_textur<_tb> >(0){
                                                                pname=s;
                                                                pindex=0;
};
template<class _tb>_textur<_tb>::~_textur(){
                                                                //loeschen();
};
template<class _tb>void _textur<_tb>::name(const _zeichenkette<char> s){
                                                                pname=s;
};
template<class _tb>_zeichenkette<char> _textur<_tb>::name() const{
                                                                return(pname);
};
template<class _tb>void _textur<_tb>::index(const unsigned int i){
                                                                pindex=i;
};
template<class _tb>unsigned int _textur<_tb>::index()const{
                                                                return(pindex);
};
template<class _tb>bool _textur<_tb>::identischetextur(_textur<_tb>*t){
																_listenknoten<_zeichenkette<char> >*zit;
																_listenknoten<_bild<_tb> >*bit;
																
																if(pbitmaps.anzahl()!=t->pbitmapstrings.anzahl()) return(false);
																if(plightmaps.anzahl()!=t->plightmapstrings.anzahl()) return(false);
																if(pshadowmaps.anzahl()!=t->pshadowmapstrings.anzahl()) return(false);
																if(pbumpmaps.anzahl()!=t->pbumpmapstrings.anzahl()) return(false);
																if(ptranslightmaps.anzahl()!=t->ptranslightmapstrings.anzahl()) return(false);
																if(pdetailmaps.anzahl()!=t->pdetailmapstrings.anzahl()) return(false);
																if(pmaskmaps.anzahl()!=t->pmaskmapstrings.anzahl()) return(false);
																if(pspecularmaps.anzahl()!=t->pspecularmapstrings.anzahl()) return(false);
																
																
																t->pbitmapstrings.anfang(zit);
																iterierenliste((&pbitmaps),bit,
																 if(bit->objekt()->dateiname()!=zit->objekt()) return(false);
																 zit=zit->naechstes();
																);
																
																t->plightmapstrings.anfang(zit);
																iterierenliste((&plightmaps),bit,
																 if(bit->objekt()->dateiname()!=zit->objekt()) return(false);
																 zit=zit->naechstes();
																);
																
																t->pshadowmapstrings.anfang(zit);
																iterierenliste((&pshadowmaps),bit,
																 if(bit->objekt()->dateiname()!=zit->objekt()) return(false);
																 zit=zit->naechstes();
																);
																
																t->pbumpmapstrings.anfang(zit);
																iterierenliste((&pbumpmaps),bit,
																 if(bit->objekt()->dateiname()!=zit->objekt()) return(false);
																 zit=zit->naechstes();
																);
																
																t->ptranslightmapstrings.anfang(zit);
																iterierenliste((&ptranslightmaps),bit,
																 if(bit->objekt()->dateiname()!=zit->objekt()) return(false);
																 zit=zit->naechstes();
																);
																
																t->pdetailmapstrings.anfang(zit);
																iterierenliste((&pdetailmaps),bit,
																 if(bit->objekt()->dateiname()!=zit->objekt()) return(false);
																 zit=zit->naechstes();
																);
																
																t->pmaskmapstrings.anfang(zit);
																iterierenliste((&pmaskmaps),bit,
																 if(bit->objekt()->dateiname()!=zit->objekt()) return(false);
																 zit=zit->naechstes();
																);
																
																t->pspecularmapstrings.anfang(zit);
																iterierenliste((&pspecularmaps),bit,
																 if(bit->objekt()->dateiname()!=zit->objekt()) return(false);
																 zit=zit->naechstes();
																);
																
																
																
																return(true);
};

template<class _tb>void _textur<_tb>::loeschen(){
                                                                loeschenbitmap();
                                                                loeschenlightmap();
                                                                loeschenshadowmap();
                                                                loeschenbumpmap();
                                                                loeschentranslightmap();
                                                                loeschendetailmap();
                                                                loeschenmaskmap();
                                                                loeschenspecularmap();
};
template<class _tb>void _textur<_tb>::loeschenbitmap(){
                                                                pbitmaps.loeschen();
};
template<class _tb>void _textur<_tb>::loeschenlightmap(){
                                                                plightmaps.loeschen();
};
template<class _tb>void _textur<_tb>::loeschenshadowmap(){
                                                                pshadowmaps.loeschen();
};
template<class _tb>void _textur<_tb>::loeschenbumpmap(){
                                                                pbumpmaps.loeschen();
};
template<class _tb>void _textur<_tb>::loeschentranslightmap(){
                                                                ptranslightmaps.loeschen();
};
template<class _tb>void _textur<_tb>::loeschendetailmap(){
                                                                pdetailmaps.loeschen();
};
template<class _tb>void _textur<_tb>::loeschenmaskmap(){
                                                                pmaskmaps.loeschen();
};
template<class _tb>void _textur<_tb>::loeschenspecularmap(){
                                                                pspecularmaps.loeschen();
};
template<class _tb>void _textur<_tb>::einfuegenbitmap(_bild<_tb>*m){
                                                                //m->aushaengen();
                                                                pbitmaps.einhaengenunredundant(m);
};
template<class _tb>void _textur<_tb>::einfuegenlightmap(_bild<_tb>*m){
                                                                //m->aushaengen();
                                                                plightmaps.einhaengenunredundant(m);
};
template<class _tb>void _textur<_tb>::einfuegenshadowmap(_bild<_tb>*m){
                                                                //m->aushaengen();
                                                                pshadowmaps.einhaengenunredundant(m);
};
template<class _tb>void _textur<_tb>::einfuegenbumpmap(_bild<_tb>*m){
                                                                //m->aushaengen();
                                                                pbumpmaps.einhaengenunredundant(m);
};
template<class _tb>void _textur<_tb>::einfuegentransmissionmap(_bild<_tb>*m){
                                                                //m->aushaengen();
                                                                ptranslightmaps.einhaengenunredundant(m);
};
template<class _tb>void _textur<_tb>::einfuegendetailmap(_bild<_tb>*m){
                                                                //m->aushaengen();
                                                                pdetailmaps.einhaengenunredundant(m);
};
template<class _tb>void _textur<_tb>::einfuegenmaskmap(_bild<_tb>*m){
                                                                //m->aushaengen();
                                                                pmaskmaps.einhaengenunredundant(m);
};
template<class _tb>void _textur<_tb>::einfuegenspecularmap(_bild<_tb>*m){
                                                                //m->aushaengen();
                                                                pspecularmaps.einhaengenunredundant(m);
};
template<class _tb>bool _textur<_tb>::geladen(){
                                                                bool r;
                                                                //---------
                                                                r=true;
                                                                if(!geladen(pbitmaps)) r=false;
                                                                if(!geladen(plightmaps)) r=false;
                                                                if(!geladen(pshadowmaps)) r=false;
                                                                if(!geladen(pbumpmaps)) r=false;
                                                                if(!geladen(ptranslightmaps)) r=false;
                                                                if(!geladen(pdetailmaps)) r=false;
                                                                if(!geladen(pmaskmaps)) r=false;
                                                                if(!geladen(pspecularmaps)) r=false;
                                                                return(r);
};
template<class _tb>bool _textur<_tb>::geladen(_listebasis<_bild<_tb> >&l){
                                                                bool r;
                                                                _listenknoten<_bild<_tb> >*it;
                                                                //---------
                                                                r=true;
                                                                if(l.anfang(it))do{
                                                                 if(!it->objekt()->geladen()) r=false;
                                                                }while(l.naechstes(it));
                                                                return(r);
};
template<class _tb>void _textur<_tb>::laden(){
                                                                laden(pbitmaps);
                                                                laden(plightmaps);
                                                                laden(pshadowmaps);
                                                                laden(pbumpmaps);
                                                                laden(ptranslightmaps);
                                                                laden(pspecularmaps);
                                                                laden(pdetailmaps);
                                                                laden(pmaskmaps);
};
template<class _tb>void _textur<_tb>::laden(_listebasis<_bild<_tb> >&l){
                                                                _listenknoten<_bild<_tb> >*it;
                                                                //--------------
                                                                if(l.anfang(it))do{
                                                                 if(!it->objekt()->geladen()) it->objekt()->laden();
                                                                }while(l.naechstes(it));
};
template<class _tb>void _textur<_tb>::entladen(){
                                                                entladen(pbitmaps);
                                                                entladen(plightmaps);
                                                                entladen(pshadowmaps);
                                                                entladen(pbumpmaps);
                                                                entladen(ptranslightmaps);
                                                                entladen(pspecularmaps);
                                                                entladen(pdetailmaps);
                                                                entladen(pmaskmaps);
};
template<class _tb>void _textur<_tb>::entladen(_listebasis<_bild<_tb> >&l){
                                                                _listenknoten<_bild<_tb> >*it;
                                                                //--------------
                                                                if(l.anfang(it))do{
                                                                 if(it->objekt()->geladen()) it->objekt()->entladen();
                                                                }while(l.naechstes(it));
};
template<class _tb>
_liste<_bild<_tb> >*_textur<_tb>::bitmap(){
                                                                return(&pbitmaps);
};
template<class _tb>
_bild<_tb>*_textur<_tb>::bitmap(const unsigned int i){
                                                                return(pbitmaps[i]);
};
template<class _tb>
_liste<_bild<_tb> >*_textur<_tb>::lightmap(){
                                                                return(&plightmaps);
};
template<class _tb>
_liste<_bild<_tb> >*_textur<_tb>::shadowmap(){
                                                                return(&pshadowmaps);
};
template<class _tb>
_liste<_bild<_tb> >*_textur<_tb>::bumpmap(){
                                                                return(&pbumpmaps);
};
template<class _tb>
_liste<_bild<_tb> >*_textur<_tb>::translightmap(){
                                                                return(&ptranslightmaps);
};
template<class _tb>
_liste<_bild<_tb> >*_textur<_tb>::detailmap(){
                                                                return(&pdetailmaps);
};
template<class _tb>
_liste<_bild<_tb> >*_textur<_tb>::maskmap(){
                                                                return(&pmaskmaps);
};
template<class _tb>
_liste<_bild<_tb> >*_textur<_tb>::specularmap(){
                                                                return(&pspecularmaps);
};
template<class _tb>
char _textur<_tb>::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_textur>*sd){
                                                                char r=1;
                                                                r^=sd->ladenbeginn(fn);
                                                                r^=sd->ladenverschachtelung(fn);
                                                                r^=sd->ladenwert(pname);
                                                                r^=sd->ladenwert(pc[0]);
                                                                r^=sd->ladenwert(pc[1]);
                                                                r^=sd->ladenwert(pc[2]);
                                                                r^=sd->ladenwert(pc[3]);
                                                                r^=sd->ladenwert(pc[4]);
                                                                r^=sd->ladenwert(pc[5]);
                                                                r^=sd->ladenwert(pc[6]);
                                                                r^=sd->ladenwert(pc[7]);
                                                                //r^=sd->ladenwert(f);
                                                                //r^=sd->ladenassoziation();
                                                                sd->ladenende();
                                                                return(r);
};
template<class _tb>
void _textur<_tb>::speichern(_speicherbardynamisch<_textur>*sd){
                                                                unsigned int c;
                                                                sd->speichernbeginnblock();
                                                                sd->speichernverschachtelung();
                                                                sd->speichernwert(pname);
                                                                c=pbitmaps.anzahl();sd->speichernwert(c);
                                                                c=plightmaps.anzahl();sd->speichernwert(c);
                                                                c=pshadowmaps.anzahl();sd->speichernwert(c);
                                                                c=pbumpmaps.anzahl();sd->speichernwert(c);
                                                                c=ptranslightmaps.anzahl();sd->speichernwert(c);
                                                                c=pspecularmaps.anzahl();sd->speichernwert(c);
                                                                c=pdetailmaps.anzahl();sd->speichernwert(c);
                                                                c=pmaskmaps.anzahl();sd->speichernwert(c);
                                                                //sd->speichernwert(f);
                                                                //saveassociationargument(sd->datei(),sd,d);
                                                                sd->speichernendeblock();
                                                                
};
template<class _tb>
char _textur<_tb>::assoziieren(_speicherbardynamisch<_textur>*sd){
                                                                sd->assoziierenverschachtelung();
                                                                return(1);
};
template<class _tb>
bool _textur<_tb>::laden(_dateispeicherbarbinaer*d){
																
																einhaengenspeicherung(d);
																ladenbeginn();
																d->laden(speichername());
																L->l("Textur wird geladen : speichername =",speichername());
																d->laden(pindex);
																d->laden(pname);
																
																pbitmaps.aushaengen();
																plightmaps.aushaengen();
																pshadowmaps.aushaengen();
																pbumpmaps.aushaengen();
																ptranslightmaps.aushaengen();
																pspecularmaps.aushaengen();
																pdetailmaps.aushaengen();
																pmaskmaps.aushaengen();
																
																pbitmapstrings.loeschen();
																plightmapstrings.loeschen();
																pshadowmapstrings.loeschen();
																pbumpmapstrings.loeschen();
																ptranslightmapstrings.loeschen();
																pspecularmapstrings.loeschen();
																pdetailmapstrings.loeschen();
																pmaskmapstrings.loeschen();
																
																unsigned int a,i;
																_zeichenkette<char> hc;
																d->laden(a);
																for(i=0;i<a;i++){
																 d->laden(hc);
																 pbitmapstrings.einhaengen(new _zeichenkette<char>(hc));
																 L->l("butmapstring eingehaenget : ",hc);
																};
																d->laden(a);
																for(i=0;i<a;i++){
																 d->laden(hc);
																 plightmapstrings.einhaengen(new _zeichenkette<char>(hc));
																};
																d->laden(a);
																for(i=0;i<a;i++){
																 d->laden(hc);
																 pshadowmapstrings.einhaengen(new _zeichenkette<char>(hc));
																};
																d->laden(a);
																for(i=0;i<a;i++){
																 d->laden(hc);
																 pbumpmapstrings.einhaengen(new _zeichenkette<char>(hc));
																};
																d->laden(a);
																for(i=0;i<a;i++){
																 d->laden(hc);
																 ptranslightmapstrings.einhaengen(new _zeichenkette<char>(hc));
																};
																d->laden(a);
																for(i=0;i<a;i++){
																 d->laden(hc);
																 pspecularmapstrings.einhaengen(new _zeichenkette<char>(hc));
																};
																d->laden(a);
																for(i=0;i<a;i++){
																 d->laden(hc);
																 pdetailmapstrings.einhaengen(new _zeichenkette<char>(hc));
																};
																d->laden(a);
																for(i=0;i<a;i++){
																 d->laden(hc);
																 pmaskmapstrings.einhaengen(new _zeichenkette<char>(hc));
																};
																L->l("Textur wurde geladen ");
																return(true);
};
template<class _tb>
void _textur<_tb>::speichern(_dateispeicherbarbinaer*d){
																d->speichern(speichername());
																d->speichern(pindex);
																d->speichern(pname);
																_listenknoten<_bild<_tb> >*b;
																d->speichern(pbitmaps.anzahl());
																iterierenliste((&pbitmaps),b,d->speichern(b->objekt()->dateiname()));
																d->speichern(plightmaps.anzahl());
																iterierenliste((&plightmaps),b,d->speichern(b->objekt()->dateiname()));
																d->speichern(pshadowmaps.anzahl());
																iterierenliste((&pshadowmaps),b,d->speichern(b->objekt()->dateiname()));
																d->speichern(pbumpmaps.anzahl());
																iterierenliste((&pbumpmaps),b,d->speichern(b->objekt()->dateiname()));
																d->speichern(ptranslightmaps.anzahl());
																iterierenliste((&ptranslightmaps),b,d->speichern(b->objekt()->dateiname()));
																d->speichern(pspecularmaps.anzahl());
																iterierenliste((&pspecularmaps),b,d->speichern(b->objekt()->dateiname()));
																d->speichern(pdetailmaps.anzahl());
																iterierenliste((&pdetailmaps),b,d->speichern(b->objekt()->dateiname()));
																d->speichern(pmaskmaps.anzahl());
																iterierenliste((&pmaskmaps),b,d->speichern(b->objekt()->dateiname()));

};
template<class _tb>
bool _textur<_tb>::assoziieren(){
																if(zeigergeladen()){
																};
																loeschenzeiger();
																loeschenanzahl();
																return(true);
};
/*
template<class _tb>
void _textur<_tb>::assoziieren(_texturverwaltung<_tb>*tb){
																//hier werden die in der laden-funktion ermittelten bild-pfade in bild objekte umgesetzt
																//wobei _texturverwaltung::bild(_zeichenkette&) dann entscheidet, ob es geladen wird, oder ein vorhandenes assoziiert wird
																pbitmaps.aushaengen();
																plightmaps.aushaengen();
																pshadowmap.aushaengen();
																pbumpmaps.aushaengen();
																ptranslightmaps.aushaengen();
																pspecularmaps.aushaengen();
																pdetailmaps.aushaengen();
																pmaskmaps.aushaengen();																
																
																_listenknoten<_zeichenkette<char> >*z;
																iterierenliste((&pbitmapsstrings),z,pbitmaps.einhaengen(tb->bild(*z->objekt())));
																iterierenliste((&plightmapstrings),z,plightmaps.einhaengen(tb->bild(*z->objekt())));
																iterierenliste((&pshadowmapsstrings),z,pshadowmaps.einhaengen(tb->bild(*z->objekt())));
																iterierenliste((&pbumpmapsstrings),z,pbumpmaps.einhaengen(tb->bild(*z->objekt())));
																iterierenliste((&ptranslightmapsstrings),z,ptranslightmaps.einhaengen(tb->bild(*z->objekt())));
																iterierenliste((&pspecularmapsstrings),z,pspecularmaps.einhaengen(tb->bild(*z->objekt())));
																iterierenliste((&pdetailmapsstrings),z,pdetailmaps.einhaengen(tb->bild(*z->objekt())));
																iterierenliste((&pmaskmapsstrings),z,pmaskmaps.einhaengen(tb->bild(*z->objekt())));
																
																pbitmapstrings.loeschen();
																plightmapstrings.loeschen();
																pshadowmapstrings.loeschen();
																pbumpmapstrings.loeschen();
																ptranslightmapstrings.loeschen();
																pspecularmapstrings.loeschen();
																pdetailmapstrings.loeschen();
																pmaskmapstrings.loeschen();																
};*/

//******************************************************************************************************************************************************************************************************
//                                                              T E X T U R V E R W A L T U N G
//******************************************************************************************************************************************************************************************************
template<class _tb>
class _texturverwaltung:public _listebasis<_textur<_tb> >,public _listebasis<_bild<_tb> >{
        public:
                using _listebasis<_textur<_tb> >::anfang;
                using _listebasis<_textur<_tb> >::naechstes;
                using _listebasis<_textur<_tb> >::vorheriges;
                using _listebasis<_bild<_tb> >::anfang;
                using _listebasis<_bild<_tb> >::naechstes;
                using _listebasis<_bild<_tb> >::vorheriges;
        public:
                _texturverwaltung();
                virtual ~_texturverwaltung();
                void loeschen();
                _bild<_tb>* bild(const _zeichenkette<char>&dateiname);
                _textur<_tb>*erzeugentextur(const unsigned int,const _zeichenkette<char>&);
                _bild<_tb>* erzeugenbild(const unsigned int i,const _zeichenkette<char>&s);
                _textur<_tb>*operator[](const unsigned int);
                _textur<_tb>*textur(const unsigned int);
                _textur<_tb>*textur(const _zeichenkette<char>&);
                _textur<_tb>*textur(_textur<_tb>*t);
                void loeschentexturdynamisch(const _zeichenkette<char>&s);
        private:
};
template<class _tb>_texturverwaltung<_tb>::_texturverwaltung(){
};
template<class _tb>_texturverwaltung<_tb>::~_texturverwaltung(){
                                                                loeschen();
};
template<class _tb>void _texturverwaltung<_tb>::loeschen(){
                                                                _listebasis<_textur<_tb> >::loeschen();
                                                                _listebasis<_bild<_tb> >::loeschen();
};
template<class _tb>_bild<_tb>* _texturverwaltung<_tb>::bild(const _zeichenkette<char>&dateiname){
																_bild<_tb>*bit;
																iterieren(bit,if(bit->dateiname()==dateiname) return(bit));
																return(erzeugenbild(0,dateiname));
																
};
template<class _tb>_textur<_tb>* _texturverwaltung<_tb>::erzeugentextur(unsigned int i,const _zeichenkette<char>&s){
                                                                _textur<_tb>*t=new _textur<_tb>(this,s);
                                                                t->index(i);
                                                                return(t);
};
template<class _tb>_bild<_tb>* _texturverwaltung<_tb>::erzeugenbild(const unsigned int i,const _zeichenkette<char>&s){
                                                                _bild<_tb>*b=new _bild<_tb>(s);
                                                                b->index(i);
                                                                b->einhaengen(this);
                                                                return(b);
};
template<class _tb>_textur<_tb>* _texturverwaltung<_tb>::operator[](const unsigned int i){
                                                                return(textur(i));
};
template<class _tb>_textur<_tb>* _texturverwaltung<_tb>::textur(const unsigned int i){
                                                                _textur<_tb>*tit;
                                                                if(anfang(tit))do{
                                                                 if(tit->index()==i) return(tit);
                                                                }while(naechstes(tit));
                                                                return(0);
                                                                
};
template<class _tb>_textur<_tb>* _texturverwaltung<_tb>::textur(const _zeichenkette<char>&s){
                                                                _textur<_tb>*tit;
                                                                if(anfang(tit))do{
                                                                 if(tit->name()==s) return(tit);
                                                                }while(naechstes(tit));
                                                                return(0);
};
template<class _tb> _textur<_tb> * _texturverwaltung<_tb>::textur(_textur<_tb>*t){
																// es ist sache der texturverwaltung aus den lokalen texturen (nach dem laden) globale zu machen, t ist lokale textur.
																//Untersuchen, ob eine der geladenen texturen mit einer globalen in der verwaltung übereinstimmt (anhand der bildpfadlisten).
																//wenn nicht, dann erzeugen und zurückgeben
																_textur<_tb>*tit;
																//_bild<_tb>*b;
																iterieren(tit,if(tit->identischetextur(t)) return(tit));
																//erzeugen anhand der bildpfadlisten
																_textur<_tb>*nt=new _textur<_tb>(this);
																_listenknoten<_zeichenkette<char> >*zit;
																iterierenliste((&t->pbitmapstrings),zit,nt->bitmap()->einhaengen(bild(*(zit->objekt()))));
																iterierenliste((&t->plightmapstrings),zit,nt->lightmap()->einhaengen(bild(*(zit->objekt()))));
																iterierenliste((&t->pshadowmapstrings),zit,nt->shadowmap()->einhaengen(bild(*(zit->objekt()))));
																iterierenliste((&t->pbumpmapstrings),zit,nt->bumpmap()->einhaengen(bild(*(zit->objekt()))));
																iterierenliste((&t->ptranslightmapstrings),zit,nt->translightmap()->einhaengen(bild(*(zit->objekt()))));
																iterierenliste((&t->pspecularmapstrings),zit,nt->specularmap()->einhaengen(bild(*(zit->objekt()))));
																iterierenliste((&t->pdetailmapstrings),zit,nt->detailmap()->einhaengen(bild(*(zit->objekt()))));
																iterierenliste((&t->pmaskmapstrings),zit,nt->maskmap()->einhaengen(bild(*(zit->objekt()))));
																return(nt);
};
template<class _tb>void _texturverwaltung<_tb>::loeschentexturdynamisch(const _zeichenkette<char>&s){
                                                                _textur<_tb>*t;
                                                                bool raus=false;
                                                                do{
                                                                 t=textur(s);
                                                                 if(t){
                                                                  t->loeschen();
                                                                  delete t; 
                                                                 }else raus=true;
                                                                }while(raus==false);
};

//******************************************************************************************************************************************************************************************************
//                                                              T E X T U R E V E C T O R 
//******************************************************************************************************************************************************************************************************
template<class _tg>
class _texturvektor/*:public _basis::_speicherbarargument*/{
        friend class _bildvektor<_tg>;

        public:
                _texturvektor();
                virtual ~_texturvektor();
                unsigned int anzahlbildvektor() const;
                unsigned int listenanzahl()const;
                _listebasis<_bildvektor<_tg> >*liste(const unsigned int );
                void kopieren(_texturvektor*);
                void add(_texturvektor*);
                void sub(_texturvektor*);
                void mul(_tg);
                
                
                
                void einfuegenbitmapvektor(_vektor2<_tg>&);
                void einfuegenlightmapvektor(_vektor2<_tg>&);
                void einfuegenshadowmapvektor(_vektor2<_tg>&);
                void einfuegenbumpmapvektor(_vektor2<_tg>&);
                void einfuegentransmissionmapvektor(_vektor2<_tg>&);
                //void insertdetailmapvector(_vektor<_tg>&);
                //void insertmaskmapvector(_vektor<_tg>&);
                void einfuegenspecularmapvektor(_vektor2<_tg>&);

        
                void einfuegenvektor(unsigned int,_vektor2<_tg>&);
                void einfuegenvektor(_listebasis<_bildvektor<_tg> >*&,_vektor2<_tg>&);
                void setzenvektor(unsigned int,unsigned int,_vektor2<_tg>&);
                void setzenvektor(_listebasis<_bildvektor<_tg> >*,unsigned int,_vektor2<_tg>&);
                _bildvektor<_tg>&holenvektor(_listebasis<_bildvektor<_tg> >*,unsigned int);
                inline _bildvektor<_tg>&holenvektor(unsigned int,unsigned int);
                void loeschenvektor(unsigned int,unsigned int);
                void loeschenvektor(_listebasis<_bildvektor<_tg> >*&,unsigned int);
                void loeschen(unsigned int);
                void loeschen(_listebasis<_bildvektor<_tg> >*&);
                void loeschen();
        
                //speichern
                char laden(_dateispeicherbarknoten*,_speicherbardynamisch<_texturvektor>*);
                void speichern(_speicherbardynamisch<_texturvektor>*);
                char assoziieren(_speicherbardynamisch<_texturvektor>*);

                bool ladentexturvektor(_datei*d);
				void speicherntexturvektor(_datei*d);
        
        
        
        
        private:
        private:
                _listebasis<_bildvektor<_tg> >*pvectors[8];
                unsigned int plistcount;
                _bildvektor<_tg> zurnot;
                /*_listebasis<_bildvektor<_tg> >*plightmapvectors;
                _listebasis<_bildvektor<_tg> >*pshadowmapvectors;
                _listebasis<_bildvektor<_tg> >*pbumpmapvectors;
                _listebasis<_bildvektor<_tg> >*ptranslightmapvectors;
                _listebasis<_bildvektor<_tg> >*pdetailmapvectors;
                _listebasis<_bildvektor<_tg> >*pmaskmapvectors;
                _listebasis<_bildvektor<_tg> >*pspecularmapvectors;*/
                //0=bitmap
                //1=lightmap
                //2=shadowmap
                //3=bumpmap
                //4=transmissionmap
                //5=specularmap
};
template<class _tg>_texturvektor<_tg>::_texturvektor(){
                                                                plistcount=6;
                                                                for(unsigned int i=0;i<plistcount;i++){
                                                                 pvectors[i]=0;
                                                                };
                                                                
                                                                /*
                                                                pbitmapvectors=0;
                                                                plightmapvectors=0;
                                                                pshadowmapvectors=0;
                                                                pbumpmapvectors=0;
                                                                ptranslightmapvectors=0;
                                                                pdetailmapvectors=0;
                                                                pmaskmapvectors=0;
                                                                pspecularmapvectors=0;
                                                                */
};
template<class _tg>_texturvektor<_tg>::~_texturvektor(){
                                                                loeschen();
};
template<class _tg> unsigned int _texturvektor<_tg>::anzahlbildvektor()const {
                                                                unsigned int i;
                                                                unsigned int n;
                                                                //--------------------
                                                                i=0;
                                                                for(n=0;n<plistcount;n++){
                                                                 if(pvectors[n]!=0){
                                                                  i+=pvectors[n]->anzahl();
                                                                 };
                                                                };
                                                                return(i);
                                                                
};
template<class _tg> unsigned int _texturvektor<_tg>::listenanzahl()const {
                                                                return(plistcount);
}
template<class _tg> _listebasis<_bildvektor<_tg> >*_texturvektor<_tg>::liste(const unsigned int i){
                                                                if(i<plistcount){
                                                                 return(pvectors[i]);
                                                                }else return(0);
};
template<class _tg>void _texturvektor<_tg>::kopieren(_texturvektor<_tg>*tv){
                                                                _bildvektor<_tg>*mit;
                                                                //-------------------------------
                                                                loeschen();
                                                                for(unsigned int i=0;i<plistcount;i++){
                                                                 if(tv->pvectors[i]){
                                                                  pvectors[i]=new _listebasis<_bildvektor<_tg> >();
                                                                  if(tv->pvectors[i]->anfang(mit))do{
                                                                   new _bildvektor<_tg>(pvectors[i],*mit);
                                                                  }while(tv->pvectors[i]->naechstes(mit));
                                                                 };
                                                                };
};
template<class _tg>void _texturvektor<_tg>::add(_texturvektor<_tg>*tv){
                                                                _bildvektor<_tg>*mit;
                                                                _bildvektor<_tg>*tit;
                                                                _vektor2<_tg> h;
                                                                unsigned int i;
                                                                unsigned int j;
                                                                //------------------------------
                                                                for(i=0;i<plistcount;i++){
                                                                 if(tv->pvectors[i]){
                                                                  //ggf. neue liste anlegen
                                                                  if(pvectors[i]==0) pvectors[i]=new _listebasis<_bildvektor<_tg> >();
                                                                  j=0;
                                                                  //bestehende liste addieren, ggf. ergänzen
                                                                  if(tv->pvectors[i]->anfang(mit))do{
                                                                   h=*mit;
                                                                   h*=+1;
                                                                   tit=&holenvektor(pvectors[i],j);
                                                                   if(tit){
                                                                    *tit+=h;
                                                                   }else{
                                                                    new _bildvektor<_tg>(pvectors[i],h);
                                                                   };
                                                                   j++;
                                                                  }while(tv->pvectors[i]->naechstes(mit));
                                                                 };
                                                                };
};
template<class _tg>void _texturvektor<_tg>::sub(_texturvektor<_tg>*tv){
                                                                _bildvektor<_tg>*mit;
                                                                _bildvektor<_tg>*tit;
                                                                _vektor2<_tg> h;
                                                                unsigned int i;
                                                                unsigned int j;
                                                                //------------------------------
                                                                for(i=0;i<plistcount;i++){
                                                                 if(tv->pvectors[i]){
                                                                  //ggf. neue liste anlegen
                                                                  if(pvectors[i]==0) pvectors[i]=new _listebasis<_bildvektor<_tg> >();
                                                                  j=0;
                                                                  //bestehende liste addieren, ggf. ergänzen
                                                                  if(tv->pvectors[i]->anfang(mit))do{
                                                                   h=*mit;
                                                                   h*=-1;
                                                                   tit=&holenvektor(pvectors[i],j);
                                                                   if(tit){
                                                                    *tit+=h;
                                                                   }else{
                                                                    new _bildvektor<_tg>(pvectors[i],h);
                                                                   };
                                                                   j++;
                                                                  }while(tv->pvectors[i]->naechstes(mit));
                                                                 };
                                                                };
};
template<class _tg>void _texturvektor<_tg>::mul(_tg x){
                                                                _bildvektor<_tg>*mit;
                                                              // _bildvektor<_tg>*tit;
                                                                unsigned int i;
                                                                //------------------------------
                                                                for(i=0;i<plistcount;i++){
                                                                 if(pvectors[i]){
                                                                  //bestehende liste durchmultiplizieren
                                                                  if(pvectors[i]->anfang(mit))do{
                                                                   *mit*=x;
                                                                  }while(pvectors[i]->naechstes(mit));
                                                                 };
                                                                };
};

template<class _tg>void _texturvektor<_tg>::loeschen(){
                                                                for(unsigned int i=0;i<plistcount;i++){
                                                                 if(pvectors[i]){
                                                                  delete pvectors[i];
                                                                  pvectors[i]=0;
                                                                 };
                                                                };
                                                                /*
                                                                ::loeschen(pbitmapvectors);
                                                                ::loeschen(plightmapvectors);
                                                                ::loeschen(pshadowmapvectors);
                                                                ::loeschen(pbumpmapvectors);
                                                                ::loeschen(ptranslightmapvectors);
                                                                ::loeschen(pdetailmapvectors);
                                                                ::loeschen(pmaskmapvectors);
                                                                ::loeschen(pspecularmapvectors);
                                                                */
};
template<class _tg>void _texturvektor<_tg>::einfuegenbitmapvektor(_vektor2<_tg>&v){
                                                                einfuegenvektor(pvectors[0],v);
};
template<class _tg>void _texturvektor<_tg>::einfuegenlightmapvektor(_vektor2<_tg>&v){
                                                                einfuegenvektor(pvectors[1],v);
};
template<class _tg>void _texturvektor<_tg>::einfuegenshadowmapvektor(_vektor2<_tg>&v){
                                                                einfuegenvektor(pvectors[2],v);
};
template<class _tg>void _texturvektor<_tg>::einfuegenbumpmapvektor(_vektor2<_tg>&v){
                                                                einfuegenvektor(pvectors[3],v);
};
template<class _tg>void _texturvektor<_tg>::einfuegentransmissionmapvektor(_vektor2<_tg>&v){
                                                                einfuegenvektor(pvectors[4],v);
};
/*
template<class _tg>void _texturvektor<_tg>::insertdetailmapvector(_vektor<_tg>&v){
                                                                einfuegenvektor(pdetailmapvectors,v);
};
template<class _tg>void _texturvektor<_tg>::insertmaskmapvector(_vektor<_tg>&v){
                                                                einfuegenvektor(pmaskmapvectors,v);
};
*/
template<class _tg>void _texturvektor<_tg>::einfuegenspecularmapvektor(_vektor2<_tg>&v){
                                                                einfuegenvektor(pvectors[5],v);
};



template<class _tg>void _texturvektor<_tg>::einfuegenvektor(unsigned int typ,_vektor2<_tg>&v){
                                                                if((typ>=0)&&(typ<plistcount)) einfuegenvektor(pvectors[typ],v);
                                                               /*         
                                                                switch(typ){
                                                                 case 0:einfuegenvektor(pbitmapvectors,v);break;
                                                                 case 1:einfuegenvektor(plightmapvectors,v);break;
                                                                 case 2:einfuegenvektor(pshadowmapvectors,v);break;
                                                                 case 3:einfuegenvektor(pbumpmapvectors,v);break;
                                                                 case 4:einfuegenvektor(ptranslightmapvectors,v);break;
                                                                 case 5:einfuegenvektor(pdetailmapvectors,v);break;
                                                                 case 6:einfuegenvektor(pmaskmapvectors,v);break;
                                                                 case 7:einfuegenvektor(pspecularmapvectors,v);break;
                                                                };*/
};
template<class _tg>void _texturvektor<_tg>::einfuegenvektor(_listebasis<_bildvektor<_tg> >*&l,_vektor2<_tg>&v){
                                                                if(l==0){
                                                                 l=new _listebasis<_bildvektor<_tg> >();
                                                                };
                                                                new _bildvektor<_tg>(l,v);
};
template<class _tg>void _texturvektor<_tg>::setzenvektor(unsigned int typ,unsigned int index,_vektor2<_tg>&v){
                                                                if((typ>=0)&&(typ<plistcount)) setzenvektor(pvectors[typ],index,v);
                                                                /*
                                                                switch(typ){
                                                                 case 0:setzenvektor(pbitmapvectors,index,v);break;
                                                                 case 1:setzenvektor(plightmapvectors,index,v);break;
                                                                 case 2:setzenvektor(pshadowmapvectors,index,v);break;
                                                                 case 3:setzenvektor(pbumpmapvectors,index,v);break;
                                                                 case 4:setzenvektor(ptranslightmapvectors,index,v);break;
                                                                 case 5:setzenvektor(pdetailmapvectors,index,v);break;
                                                                 case 6:setzenvektor(pmaskmapvectors,index,v);break;
                                                                 case 7:setzenvektor(pspecularmapvectors,index,v);break;
                                                                };
                                                                */
};
template<class _tg>void _texturvektor<_tg>::setzenvektor(_listebasis<_bildvektor<_tg> >*l,unsigned int index,_vektor2<_tg>&v){
                                                                if(l->anzahl()>index){
                                                                 (*l)[index]->setzen(v);
                                                                }else{
                                                                 //error:ungültiger listenindex
                                                                };
};
template<class _tg>_bildvektor<_tg>& _texturvektor<_tg>::holenvektor(_listebasis<_bildvektor<_tg> >*l,unsigned int index){
                                                                if(index>=l->anzahl()){
                                                                 return(*(*l)[0]);
                                                                }else{
                                                                 return(*(*l)[index]);
                                                                };
};

template<class _tg>_bildvektor<_tg>& _texturvektor<_tg>::holenvektor(unsigned int listindex,unsigned int index){
                                                                _listebasis<_bildvektor<_tg> >*l;
                                                                //-----------------------------------------
                                                                if(listindex>(plistcount-1)) listindex=0;
                                                                l=pvectors[listindex];
                                                                if(l){
                                                                 if(index==0) return(*(l->erstes()));
                                                                 //if(index>=l->anzahl()){
                                                                 // return(*((*l)[0]));
                                                                 //}else{
                                                                  return(*((*l)[index]));
                                                                 //};
                                                                }else{ 
                                                                 return(zurnot);
                                                                };
                                                                
                                                                //return(*(pvectors[listindex]->erstes()));
};
template<class _tg>void _texturvektor<_tg>::loeschenvektor(unsigned int typ,unsigned int index){
                                                                if((typ>=0)&&(typ<plistcount)) loeschenvektor(pvectors[typ],index);
                                                                /*
                                                                switch(typ){
                                                                 case 0:loeschenvektor(pbitmapvectors,index);break;
                                                                 case 1:loeschenvektor(plightmapvectors,index);break;
                                                                 case 2:loeschenvektor(pshadowmapvectors,index);break;
                                                                 case 3:loeschenvektor(pbumpmapvectors,index);break;
                                                                 case 4:loeschenvektor(ptranslightmapvectors,index);break;
                                                                 case 5:loeschenvektor(pdetailmapvectors,index);break;
                                                                 case 6:loeschenvektor(pmaskmapvectors,index);break;
                                                                 case 7:loeschenvektor(pspecularmapvectors,index);break;
                                                                };*/
};
template<class _tg>void _texturvektor<_tg>::loeschenvektor(_listebasis<_bildvektor<_tg> >*&l,unsigned int index){
                                                                if(l->anzahl()>index){
                                                                 delete l[index];
                                                                 if(l.anzahl()==0) {
                                                                  delete l;
                                                                  l=0;
                                                                 };
                                                                }else{
                                                                 //error:ungülter listenindex
                                                                };
};
template<class _tg>void _texturvektor<_tg>::loeschen(unsigned int typ){
                                                                if((typ>=0)&&(typ<plistcount)){
                                                                 if(pvectors[typ]){
                                                                  delete pvectors[typ];
                                                                  pvectors[typ]=0;
                                                                 };
                                                                };
                                                                /*
                                                                switch(typ){
                                                                 case 0:loeschen(pbitmapvectors);break;
                                                                 case 1:loeschen(plightmapvectors);break;
                                                                 case 2:loeschen(pshadowmapvectors);break;
                                                                 case 3:loeschen(pbumpmapvectors);break;
                                                                 case 4:loeschen(ptranslightmapvectors);break;
                                                                 case 5:loeschen(pdetailmapvectors);break;
                                                                 case 6:loeschen(pmaskmapvectors);break;
                                                                 case 7:loeschen(pspecularmapvectors);break;
                                                                };
                                                                */
};
template<class _tg>void _texturvektor<_tg>::loeschen(_listebasis<_bildvektor<_tg> >*&l){
                                                                if(l!=0){
                                                                 l->loeschen();
                                                                 delete l;
                                                                 l=0;
                                                                };
};
template<class _tg>char _texturvektor<_tg>::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_texturvektor>*sd){
                                                                char r=1;
                                                                unsigned int i;
                                                                unsigned int j;
                                                                unsigned int n;
                                                                _vektor2<_tg> v;
                                                                //----------------------------
                                                                loeschen();
                                                                r^=sd->ladenbeginn(fn);
                                                                r^=sd->ladenverschachtelung(fn);
                                                                for(i=0;i<plistcount;i++){
                                                                 r^=sd->ladenwert(n);
                                                                 for(j=0;j<n;j++){
                                                                  r^=sd->ladenwert(v);
                                                                  einfuegenvektor(i,v);
                                                                 };
                                                                };
                                                                sd->ladenende();
                                                                return(r);
};
template<class _tg>void _texturvektor<_tg>::speichern(_speicherbardynamisch<_texturvektor>*sd){
                                                                _bildvektor<_tg>*mit;
                                                                unsigned int i;
                                                                //----------------------------
                                                                sd->speichernbeginn();
                                                                sd->speichernverschachtelung();
                                                                for(i=0;i<plistcount;i++){
                                                                 if(pvectors[i]){
                                                                  sd->speichernwert(pvectors[i]->anzahl());
                                                                  if(pvectors[i]->anfang(mit))do{
                                                                   sd->speichernwert(*mit);
                                                                  }while(pvectors[i]->naechstes(mit));
                                                                 }else{
                                                                  sd->speichernwert(0);
                                                                 };
                                                                };
                                                                sd->speichernende();
                                                                
};
template<class _tg>char _texturvektor<_tg>::assoziieren(_speicherbardynamisch<_texturvektor>*sd){
                                                                sd->assoziierenverschachtelung();
                                                                return(1);
};
template<class _tg>bool _texturvektor<_tg>::ladentexturvektor(_datei*d){
	                                                                
                                                                unsigned int i;
                                                                unsigned int j;
                                                                unsigned int n;
																unsigned char c;
                                                                _vektor2<_tg> v;
                                                                //----------------------------
                                                                loeschen();
                                                                for(i=0;i<plistcount;i++){
                                                                 d->laden(c);
																 n=c;
                                                                 for(j=0;j<n;j++){
                                                                  d->laden(v);
                                                                  einfuegenvektor(i,v);
                                                                 };
                                                                };
																return(true);
																
};
template<class _tg>void _texturvektor<_tg>::speicherntexturvektor(_datei*d){
                                                                _bildvektor<_tg>*mit;
                                                                unsigned int i;
                                                                //----------------------------
                                                                for(i=0;i<plistcount;i++){
                                                                 if(pvectors[i]){
                                                                  d->speichern((unsigned char)pvectors[i]->anzahl());
                                                                  if(pvectors[i]->anfang(mit))do{
                                                                   d->speichern((_vektor2<_tg>)(*mit));
                                                                  }while(pvectors[i]->naechstes(mit));
                                                                 }else{
                                                                  d->speichern((unsigned char)0);
                                                                 };
                                                                };
};
//
//******************************************************************************************************************************************************************************************************
//                                                              M A P V E C T O R 
//******************************************************************************************************************************************************************************************************
template<class _tg>
class _bildvektor:public _vektor2<_tg>,public _listenknotenbasis<_bildvektor<_tg> >{
        friend class _texturvektor<_tg>;
        private:
                _bildvektor();
                _bildvektor(_listebasis<_bildvektor>*,_vektor2<_tg>&);
                virtual ~_bildvektor();
        public:
                void blockzeiger(_tg*);                
                void aktualisierenblock();
                inline void setzen(_tg,_tg);
                inline void setzen(const _vektor2<_tg>&);
        private:
                _tg*pblockzeiger; //ohne offset zu verstehen
};
template<class _tg>_bildvektor<_tg>::_bildvektor():_listenknotenbasis<_bildvektor>(0){
                                                                pblockzeiger=0;
                                                                setzen(0.5,0.5);
                                                                
};
template<class _tg>_bildvektor<_tg>::_bildvektor(_listebasis<_bildvektor<_tg> >*l,_vektor2<_tg>&v):_vektor2<_tg>(v),_listenknotenbasis<_bildvektor>(l){
                                                                pblockzeiger=0;
};
template<class _tg>_bildvektor<_tg>::~_bildvektor(){
};
template<class _tg> void _bildvektor<_tg>::blockzeiger(_tg*pb){
                                                                pblockzeiger=pb;
};
template<class _tg> void _bildvektor<_tg>::aktualisierenblock(){
                                                                if(pblockzeiger){
                                                                 *(pblockzeiger+0)=(*this)[0];
                                                                 *(pblockzeiger+1)=(*this)[1];
                                                                };
};
template<class _tg> void _bildvektor<_tg>::setzen(_tg x,_tg y){
                                                                _vektor2<_tg>::setzen(x,y);
                                                                aktualisierenblock();
};
template<class _tg> void _bildvektor<_tg>::setzen(const _vektor2<_tg>&o){
                                                                _vektor2<_tg>::setzen(o);
                                                                aktualisierenblock();
};
#endif

