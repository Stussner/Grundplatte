//******************************************************************************************************************************************************************************************************
//  Project     : grundplatte
//  Library     : _grundplatte.lib
//  Module      : _textbuffer.hpp
//  Date        : 24.12.2002
//  Description : 
//******************************************************************************************************************************************************************************************************
#ifndef _textbufferh_included
#define _textbufferh_included
#include <_global.hpp>
#include <_struktur.hpp>
#include <_vektor.hpp>
#include <_text.hpp>
#include <_datei.hpp>
//******************************************************************************************************************************************************************************************************
//                                                              F O R W A R D S 
//******************************************************************************************************************************************************************************************************
template<class _typtext=typtext,class _typoptik=typoptik> class _textbuffer;
template<class _typtext=typtext,class _typoptik=typoptik> class _textbufferprotokoll;
template<class _typtext=typtext,class _typoptik=typoptik> class _textbufferprotokollknoten;
template<class _typtext=typtext,class _typoptik=typoptik> class _textbufferprotokollknoteneinzel;
template<class _typtext=typtext,class _typoptik=typoptik> class _textbufferprotokollknotenmulti;
template<class _typtext=typtext,class _typoptik=typoptik> class _textbufferprotokollknotenzeile;
//******************************************************************************************************************************************************************************************************
//                                                              T E X T B U F F E R P R O T O C O L 
//******************************************************************************************************************************************************************************************************
template<class _typtext,class _typoptik>
class _textbufferprotokoll:
public _listenknotenbasis<_textbufferprotokoll<_typtext,_typoptik> >,public _listebasis<_textbufferprotokollknoten<_typtext,_typoptik> >{
                /*using _listenknotenbasis<_textbufferprotokoll<_typtext,_typoptik> >::naechstes;
                using _listenknotenbasis<_textbufferprotokoll<_typtext,_typoptik> >::vorheriges;
                using _listebasis<_textbufferprotokollknoten<_typtext,_typoptik> >::naechstes;
                using _listebasis<_textbufferprotokollknoten<_typtext,_typoptik> >::vorheriges;*/
        public:
                _textbufferprotokoll(_textbuffer<_typtext,_typoptik>*);
                ~_textbufferprotokoll();
                _textbuffer<_typtext,_typoptik>*textbuffer();
                _textbufferprotokollknoteneinzel<_typtext,_typoptik>*extension(bool,int,int,_typtext);
                _textbufferprotokollknotenmulti<_typtext,_typoptik>*extension(bool,int,int,_zeichenkette<_typtext>&);
                _textbufferprotokollknotenzeile<_typtext,_typoptik>*extension(bool,int,_zeichenkette<_typtext>&);
                
                bool undo();
                bool redo();
        private:
                _textbuffer<_typtext,_typoptik>*ptextbuffer;
};
template<class _typtext,class _typoptik>_textbufferprotokoll<_typtext,_typoptik>::_textbufferprotokoll(_textbuffer<_typtext,_typoptik>*tb):_listenknotenbasis<_textbufferprotokoll<_typtext,_typoptik> >(tb){
                                                                ptextbuffer=tb;
};
template<class _typtext,class _typoptik>_textbufferprotokoll<_typtext,_typoptik>::~_textbufferprotokoll(){
};
template<class _typtext,class _typoptik>_textbuffer<_typtext,_typoptik>*_textbufferprotokoll<_typtext,_typoptik>::textbuffer(){
                                                                return(ptextbuffer);
};
template<class _typtext,class _typoptik>bool _textbufferprotokoll<_typtext,_typoptik>::undo(){
                                                                _textbufferprotokollknoten<_typtext,_typoptik>*it;
                                                                char rr=0;
                                                                //-------------------------
                                                                if(anfang(it)){
                                                                 vorheriges(it);
                                                                 do{
                                                                  if(it->undo()) rr=1; 
                                                                 }while(vorheriges(it));
                                                                };
                                                                if(rr) return(true); else return(false);//return(rr);

};
template<class _typtext,class _typoptik>bool _textbufferprotokoll<_typtext,_typoptik>::redo(){
                                                                _textbufferprotokollknoten<_typtext,_typoptik>*it;
                                                                char rr=0;
                                                                //-------------------------
                                                                if(anfang(it))do{
                                                                 if(it->redo()) rr=1;
                                                                }while(naechstes(it));
                                                                if(rr) return(true); else return(false);
};
template<class _typtext,class _typoptik>_textbufferprotokollknoteneinzel<_typtext,_typoptik>*_textbufferprotokoll<_typtext,_typoptik>::extension(bool b,int x,int y,_typtext c){
                                                                return(new _textbufferprotokollknoteneinzel<_typtext,_typoptik>(this,b,x,y,c));
};
template<class _typtext,class _typoptik>_textbufferprotokollknotenmulti<_typtext,_typoptik>*_textbufferprotokoll<_typtext,_typoptik>::extension(bool b,int x,int y,_zeichenkette<_typtext>&c){
                                                                return(new _textbufferprotokollknotenmulti<_typtext,_typoptik>(this,b,x,y,c));
};
template<class _typtext,class _typoptik>_textbufferprotokollknotenzeile<_typtext,_typoptik>*_textbufferprotokoll<_typtext,_typoptik>::extension(bool b,int y,_zeichenkette<_typtext>&c){
                                                                return(new _textbufferprotokollknotenzeile<_typtext,_typoptik>(this,b,y,c));
};

//******************************************************************************************************************************************************************************************************
//                                                              T E X T B U F F E R P R O T O C O L N O D E 
//******************************************************************************************************************************************************************************************************
template<class _typtext,class _typoptik>class _textbufferprotokollknoten:public _listenknotenbasis<_textbufferprotokollknoten<_typtext,_typoptik> >{
        public:
                _textbufferprotokollknoten(_textbufferprotokoll<_typtext,_typoptik>*,bool,int,int);
                virtual ~_textbufferprotokollknoten();
                virtual bool undo()=0;
                virtual bool redo()=0;
                bool inserting() const;
                void insertmodeinvert();
                int position(int) const;
                int x() const;
                int y() const;
                _textbuffer<_typtext,_typoptik>*textbuffer();
                _textbufferprotokoll<_typtext,_typoptik>*textbufferprotocol();
        private:
                bool pinserting;
                int px,py;
                _textbufferprotokoll<_typtext,_typoptik>*ptextbufferprotocol;
};
template<class _typtext,class _typoptik>_textbufferprotokollknoten<_typtext,_typoptik>::_textbufferprotokollknoten(_textbufferprotokoll<_typtext,_typoptik>*tbp,bool i,int x,int y){
                                                                ptextbufferprotocol=tbp;
                                                                pinserting=i;
                                                                px=x;
                                                                py=y;
};
template<class _typtext,class _typoptik>_textbufferprotokollknoten<_typtext,_typoptik>::~_textbufferprotokollknoten(){
};
template<class _typtext,class _typoptik>bool _textbufferprotokollknoten<_typtext,_typoptik>::inserting() const{
                                                                return(pinserting);
};
template<class _typtext,class _typoptik>void _textbufferprotokollknoten<_typtext,_typoptik>::insertmodeinvert(){
                                                                if(pinserting)pinserting=false; else pinserting=true;
};
template<class _typtext,class _typoptik>int _textbufferprotokollknoten<_typtext,_typoptik>::position(int i) const{
                                                                if(i==0) return(px); else return(py);
};
template<class _typtext,class _typoptik>int _textbufferprotokollknoten<_typtext,_typoptik>::x() const{
                                                                return(px);
};
template<class _typtext,class _typoptik>int _textbufferprotokollknoten<_typtext,_typoptik>::y() const{
                                                                return(py);
};
template<class _typtext,class _typoptik>_textbuffer<_typtext,_typoptik>*_textbufferprotokollknoten<_typtext,_typoptik>::textbuffer(){
                                                                return(ptextbufferprotocol->textbuffer());
};
template<class _typtext,class _typoptik>_textbufferprotokoll<_typtext,_typoptik>*_textbufferprotokollknoten<_typtext,_typoptik>::textbufferprotocol(){
                                                                return(ptextbufferprotocol);
};

//******************************************************************************************************************************************************************************************************
//                                                              T E X T B U F F E R P R O T O C O L N O D E S I N G L E 
//******************************************************************************************************************************************************************************************************
template<class _typtext,class _typoptik> class _textbufferprotokollknoteneinzel:public _textbufferprotokollknoten<_typtext,_typoptik>{
        public:
                _textbufferprotokollknoteneinzel(_textbufferprotokoll<_typtext,_typoptik>*,bool,int,int,_typtext);
                virtual ~_textbufferprotokollknoteneinzel();
                virtual bool undo();
                virtual bool redo();
        private:
               _typtext pchar;
};                
template<class _typtext,class _typoptik> _textbufferprotokollknoteneinzel<_typtext,_typoptik>::_textbufferprotokollknoteneinzel(_textbufferprotokoll<_typtext,_typoptik>*tb,bool i,int x,int y,_typtext c):_textbufferprotokollknoten<_typtext,_typoptik>(tb,i,x,y){
                                                                pchar=c;
};
template<class _typtext,class _typoptik> _textbufferprotokollknoteneinzel<_typtext,_typoptik>::~_textbufferprotokollknoteneinzel(){
};
template<class _typtext,class _typoptik> bool _textbufferprotokollknoteneinzel<_typtext,_typoptik>::undo(){
                                                                bool rr=false;
                                                                //---------
                                                                textbuffer()->protokollmodus(true);
                                                                if(inserting()){//zeichen c aushängen
                                                                 textbuffer()->cursor(x(),y());
                                                                 rr=textbuffer()->aushaengen(textbuffer()->cursor(0),textbuffer()->cursor(1),1);
                                                                }else{//zeichen c einfügen
                                                                 rr=textbuffer()->einhaengen(x(),y(),pchar);
                                                                 textbuffer()->cursor(x()+1,y());
                                                                };
                                                                textbuffer()->protokollmodus(false);
                                                                return(rr);
};
template<class _typtext,class _typoptik> bool _textbufferprotokollknoteneinzel<_typtext,_typoptik>::redo(){
                                                                bool rr;
                                                                insertmodeinvert();
                                                                rr=undo();
                                                                insertmodeinvert();
                                                                return(rr);
};

//******************************************************************************************************************************************************************************************************
//                                                              T E X T B U F F E R P R O T O C O L N O D E M U L T I 
//******************************************************************************************************************************************************************************************************
template<class _typtext,class _typoptik> class _textbufferprotokollknotenmulti:public _textbufferprotokollknoten<_typtext,_typoptik>{
        public:
                _textbufferprotokollknotenmulti(_textbufferprotokoll<_typtext,_typoptik>*,bool,int,int,_zeichenkette<_typtext>&);
                virtual ~_textbufferprotokollknotenmulti();
                virtual bool undo();
                virtual bool redo();
        private:
                _zeichenkette<_typtext> pstring;
                
};
template<class _typtext,class _typoptik> _textbufferprotokollknotenmulti<_typtext,_typoptik>::_textbufferprotokollknotenmulti(_textbufferprotokoll<_typtext,_typoptik>*tb,bool i,int x,int y,_zeichenkette<_typtext>&s):_textbufferprotokollknoten<_typtext,_typoptik>(tb,i,x,y){
                                                                pstring=s;
                                                                
};
template<class _typtext,class _typoptik> _textbufferprotokollknotenmulti<_typtext,_typoptik>::~_textbufferprotokollknotenmulti(){
};
template<class _typtext,class _typoptik> bool _textbufferprotokollknotenmulti<_typtext,_typoptik>::undo(){
                                                                bool rr=false;
                                                                //---------
                                                                textbuffer()->protokollmodus(true);
                                                                if(inserting()){//zeichenkette pstring aushängen
                                                                 textbuffer()->cursor(x(),y());
                                                                 rr=textbuffer()->aushaengen(textbuffer()->cursor(0),textbuffer()->cursor(1),pstring.groesse());
                                                                }else{//zeichenkette pstring einfügen
                                                                 rr=textbuffer()->einhaengen(x(),y(),pstring);
                                                                 textbuffer()->cursor(x()+1,y());
                                                                };
                                                                textbuffer()->protokollmodus(false);
                                                                return(rr);
};
template<class _typtext,class _typoptik> bool _textbufferprotokollknotenmulti<_typtext,_typoptik>::redo(){
                                                                bool rr;
                                                                insertmodeinvert();
                                                                rr=undo();
                                                                insertmodeinvert();
                                                                return(rr);
};

//******************************************************************************************************************************************************************************************************
//                                                              T E X T B U F F E R P R O T O C O L N O D E L I N E 
//******************************************************************************************************************************************************************************************************
template<class _typtext,class _typoptik> class _textbufferprotokollknotenzeile:public _textbufferprotokollknoten<_typtext,_typoptik>{
        public:
                _textbufferprotokollknotenzeile(_textbufferprotokoll<_typtext,_typoptik>*,bool,int,_zeichenkette<_typtext>&);
                virtual ~_textbufferprotokollknotenzeile();
                virtual bool undo();
                virtual bool redo();
        private:
                _zeichenkette<_typtext> pstring;
};   
template<class _typtext,class _typoptik> _textbufferprotokollknotenzeile<_typtext,_typoptik>::_textbufferprotokollknotenzeile(_textbufferprotokoll<_typtext,_typoptik>*tb,bool i,int y,_zeichenkette<_typtext>&s):_textbufferprotokollknoten<_typtext,_typoptik>(tb,i,0,y){
                                                                pstring=s;
};
template<class _typtext,class _typoptik> _textbufferprotokollknotenzeile<_typtext,_typoptik>::~_textbufferprotokollknotenzeile(){
};
template<class _typtext,class _typoptik> bool _textbufferprotokollknotenzeile<_typtext,_typoptik>::undo(){
                                                                bool rr=false;
                                                                //---------
                                                                textbuffer()->protokollmodus(true);
                                                                if(inserting()){//zeile mit zeichenkette pstring aushängen
                                                                 rr=textbuffer()->entfernenzeile(y());
                                                                 textbuffer()->cursor(x(),y());
                                                                }else{//zeile mit zeichenkette pstring einfügen
                                                                 rr=textbuffer()->einfuegenzeile(y(),pstring);
                                                                 textbuffer()->cursor(x(),y());
                                                                };
                                                                textbuffer()->protokollmodus(false);
                                                                return(rr);
};
template<class _typtext,class _typoptik> bool _textbufferprotokollknotenzeile<_typtext,_typoptik>::redo(){
                                                                bool rr;
                                                                insertmodeinvert();
                                                                rr=undo();
                                                                insertmodeinvert();
                                                                return(rr);
};
//******************************************************************************************************************************************************************************************************
//                                                              T E X T B U F F E R 
//******************************************************************************************************************************************************************************************************
template<class _typtext,class _typoptik> class _textbuffer:public _datei,public _listebasis<_textbufferprotokoll<_typtext,_typoptik> >{
        public:
        using   _datei::laden;
        using   _datei::speichern;
        public:
                //------------------------------------- grundoperatoren ----------------------------------
                _textbuffer(_zeichenkette<_typtext>,_zeichenkette<char>,_zeichenkette<char>);//titel,pfad,datei
                _textbuffer(_zeichenkette<_typtext>);//titel
                virtual ~_textbuffer();//textbuffer löschen
                void init();
                void laden();//datei laden
                void speichern();//datei speichern
                _zeichenkette<_typtext> &holenzeile(int);//zeile zurückgeben anhand von 0-basierendem index
                _zeichenkette<_typtext> &holenzeile(int,_listenknoten<_zeichenkette<_typtext> >*&);//zeile und knoten zurückgeben anhand von 0-basierendem index
                int holenposition(_listenknoten<_zeichenkette<_typtext> >*);
                _liste<_zeichenkette<_typtext> >&liste();
                bool anfang(_listenknoten<_zeichenkette<_typtext> >*&);//externer iterator - anfang für zeileniteration
                bool iterator(_listenknoten<_zeichenkette<_typtext> >*,_typtext*,int);//externer iterator - lesen der momentanen zeile
                bool naechstes(_listenknoten<_zeichenkette<_typtext> >*&);//externer iterator - weiteriterieren
                virtual bool zeilenreset(_typtext*,_typtext*&,int&);//char-iterator-anfang bzw char* auf den anfang der zeile setzen - (buffer,iterator)
                virtual bool zeileniterator(_typtext*&,int&,_typtext*,_vektor<_typoptik>*&,_vektor<_typoptik>*&);//char-iterator auslesen - (buffer, iterator, rückgabebuffer und dessen farbe)
                //virtual char linenext(char*,char*&);//char-iterator weiteriterieren - (buffer,iterator)
                void loeschen();//textbufferinhalt löschen und datenelemente neuinitialisieren
                void loeschentext();
                //------------------------------------- protocolbuffer ------------------------------------
                _textbufferprotokoll<_typtext,_typoptik>*erzeugenprotokolleinzel(bool,int,int,_typtext);
                _textbufferprotokoll<_typtext,_typoptik>*erzeugenprotokollmulti(bool,int,int,_zeichenkette<_typtext>&);
                _textbufferprotokoll<_typtext,_typoptik>*erzeugenprotokollzeile(bool,int,_zeichenkette<_typtext>&);
                void undo();//führt ein undo, aus bzw iteriert plast nach vorne
                void redo();//führt ein redo aus bzw iteriert plast nach hinten
                bool undoable() const;//liefert zurück, ob ein undo momentan möglich ist
                bool redoable() const;//liefert zurück, ob ein redo momentan möglich ist
                void loeschenueberlappendesprotokoll();//wenn der last.iterator nicht erstes.vorheriges ist, dann alles, was hinter last ist, löschen
                //------------------------------------- zustand, eigenschaften ---------------------------
                _zeichenkette<_typtext>&titel();//textbuffer - titel
                _zeichenkette<char>&datei();//(pfad und) datei als arguent
                _zeichenkette<char>&pfad();//argumentpafd, kann netzwerk, localer oder relativer pfad sein
                void pfad(_zeichenkette<char>);
                _zeichenkette<char>&pfadabsolut();//absoluter netzwerkpfad
                _zeichenkette<char>&pfaddateiabsolut();//absoluter netzwerkpfad und dateiname
                virtual void aktualisieren();//generelles aktualisieren für alle arten von overheads
                int anzahl();//zeilenanzahl zurückgeben
                int groesse() const;//netto zeichenzahl zurückgeben
                int speicherlast() const;
                bool nurlesen() const;//nurlesen-status auslesen
                void nurlesen(bool);//nurlesen-status setzen 
                bool dateigebunden() const;//wenn true, dann ist der textbuffer speicherbar, ladbar
                void dateigebunden(_zeichenkette<char>,_zeichenkette<char>);//setzt speicherbarkeit 
                void dateiungebunden();//löscht speicherbarkeit 
                void veraendern(bool);//berührt den textbuffer, setzt status der Berührung
                bool veraendert() const;//berührungsstatus auslesen
                void einfuegemodus(bool);//einfügenmodus setzen
                bool einfuegemodus() const;//einfügenmodus auslesen
                void steuermodus(bool);
                bool steuermodus() const;
                void protokollmodus(bool);
                bool protokollmodus() const;
                _vektor<_typoptik>&farbetext(int);//textfarbe zurückgeben (0=vordergrund,1=hintergrund)
                _vektor<_typoptik>&farbetitel(int);//titlefarbe zurückgeben (0=vordergrund,1=hintergrund)
                _vektor<_typoptik>&farbeanwahl(int);//auswahlfarbe zurückgeben (0=vordergrund,1=hintergrund)
                //------------------------------------------------------------------------------------------------------ fundamentale textoperationen -----------------------------------
                bool einhaengen(int,int,_typtext);//zeichen bei position(x,y) einfügen
                bool einhaengen(int,int,_zeichenkette<_typtext>&);//zeichenketten bei position(dx,y) einfügen
                bool einfuegenzeile(int,_zeichenkette<_typtext>&);//zeile bei position(y) einfügen
                bool aushaengen(int,int,int);//anzahl - zeichen bei der cursorposition löschen
                bool entfernenzeile(int);//zeile bei position aushaengen
                //----------------------------------------------------------------------------------------------------- textoperationen ------------------------------------------------
                _zeichenkette<_typtext>*anhaengen(_typtext*);//zeile an den text anhängen
                void anhaengenchar(_typtext);//char an das ende des textes anhängen
                void einfuegenreturn();//zeile umbrechen bzw. neue zeile hinter der cursorposition einhaengen
                void einfuegenbackspace();//backspace ausführen
                void einbauen(int,int,_textbuffer<_typtext,_typoptik>*);
                void ersetzen(int,int,_zeichenkette<_typtext>&,_zeichenkette<_typtext>&);
                //----------------------------------------------------------------------------------------------------- textoperationen, suchen und ersetzen ---------------------------
                bool suchennaechstes(int&,int&,_zeichenkette<_typtext>&,bool);
                bool suchenvorheriges(int&,int&,_zeichenkette<_typtext>&,bool);
                //----------------------------------------------------------------------------------------------------- cursorpositionsoperationen -------------------------------------
                int cursor(int);//cursorposition 0(x) oder 1(y) zurückgeben
                void cursor(int,int);//cursorposition setzen
                void cursorrelansicht(int,int);//cursorposition relativ zu ansicht setzen
                bool cursorinnerhalbansicht(int,int);//wenn cursor nicht im ansicht , dann cursor in das ansicht setzen (maxcolumns,maxlines)
                void cursorbewegung(int,int,int,int);//cursor um einen vektor verschieben (maxcolumns,maxlines,deltax,deltay)
                //----------------------------------------------------------------------------------------------------- sichtbarer bereich ---------------------------------------------
                int ansicht(int) const;//ansicht-position auslesen 0=x,1=y
                void ansicht(int,int,int,int);//ansicht position setzen (maxcolumns,maxlines,x,y)
                void ansichtbewegung(int,int,int,int);//ansicht verschieben (maxcolumns,maylines,x,y)
                void ansichtyink(int,int,int);//ansicht nach unten bewegen (maxcolumns,maxlines,delta)
                void ansichtydek(int,int,int);//ansicht nach oben bewegen (maxcolumns,maxlines,delta)
                bool ansichtinnerhalbcursor(int,int);//wenn cursor ausserhalb des views, ansicht so setzen, dass dies dann der fall ist
                void ansichtmaximal(int,int);
                //------------------------------------ selektion -----------------------------------------
                bool anwahl() const;//ist selektion gesetzt ?
                int anwahlholen(int&,int&,int&,int&) const;//selektion auslesen
                void anwahlsetzen(int,int,int,int);//anwahl setzen (startx,starty,endx,endy)
                void anwahlsetzenbeginn(int,int);//selektionsstart setzen
                void anwahlsetzenende(int,int);//selektionsende setzen
                bool anwahlteilung(int,_typtext*,int, int,int,int,int, int&,_typtext*&,_typtext*&,_typtext*&,bool*);//char*part wird über max. 3 char* zerteilt durch die anwahl (zeilenindex,part,partindex, selx0,sely0,selx1,sely1,  anzahl, p0,p1,p2,sels)
                virtual void anwahlbeginn();
                virtual void selectionmove();
                virtual void anwahlende();
                bool anwahlmodus() const;
                void anwahlmodus(bool);
                void anwahlloeschen();//nur selektion selbst löschen, nicht den text löschen
                void anwahlenfernen();//angewählten text löschen,anwahl löschen
                void anwahlfrontleerraumeinfuegen();
                void anwahlfrontleerraumentfernen();
                void anwahlendleerraumentfernen();
                void anwahltabulatorenersetzen(_zeichenkette<_typtext>&);
                void anwahlfrontleerraumsetzen(int i);
                void anwahlkopieren(_textbuffer<_typtext,_typoptik>*);
                //-------------------------------------- sonstige---------------------------------------------
                int anzahlfrontleerzeichen(_zeichenkette<_typtext>&);                
        private:
                _zeichenkette<char> ppath;// argumentpafd, kann netzwerk, localer oder relativer pfad sein
                _zeichenkette<char> ppathabsolute;//absoluter netzwerkpfad
                _zeichenkette<char> ppathfileabsolute;//absoluter netzwerkpfad und dateiname
               // _zeichenkette<char> ppathcurrent;
                _zeichenkette<char> pfile;
                _zeichenkette<_typtext> ptitle;
                _liste<_zeichenkette<_typtext> > plist;
                int pviewx;
                int pviewy;
                int pmaxx;
                int pmaxy;
                int pcurx;
                int pcuroutx;
                int pcury;
                int pselectionstartx;
                int pselectionstarty;
                int pselectionendx;
                int pselectionendy;
                bool pfilebound;
                bool preadonly;
                bool pchanged;
                bool pinsertmode;
                bool pselectionmode;
                bool pcontrolmode;
                bool pprotocolmode;
                _vektor<_typoptik> pcolortext[2];
                _vektor<_typoptik> pcolortitle[2];
                _vektor<_typoptik> pcolorselection[2];
                _textbufferprotokoll<_typtext,_typoptik>*tbpnlast;
        public:
                //_textbufferprotokoll<_typtext,_typoptik>*tbpnfirst;
};
template<class _typtext,class _typoptik> _textbuffer<_typtext,_typoptik>::_textbuffer(_zeichenkette<_typtext> atitle,_zeichenkette<char> apath,_zeichenkette<char> afile):_datei(apath,afile){
                                                                //char bu[8192];
                                                                //char cu[8192];
                                                                //char*cit;
                                                                apath.konvertiereninklein();
                                                                afile.konvertiereninklein();
                                                                ppathabsolute=apath;
                                                                ppathfileabsolute=apath+(char*)"\\"+afile;
                                                                pfile=afile;
                                                                ptitle=atitle;
                                                                //GetFullPathName(pfile.holen(bu),8192,cu,&cit);
                                                               // ppathabsolute=cu;
                                                                //ppathabsolute.konvertiereninklein();
                                                                //ppathfileabsolute=ppathabsolute;
                                                                //ppathfileabsolute.konvertiereninklein();
                                                                pfilebound=true;
                                                                init();
                                                                laden();
                                                                init();
                                                               // tbpnfirst=0;
                                                                tbpnlast=0;
                                                                pmaxx=256;
                                                                pmaxy=80;
};
template<class _typtext,class _typoptik> _textbuffer<_typtext,_typoptik>::_textbuffer(_zeichenkette<_typtext> atitle):_datei(""){
                                                                ppathabsolute="";
                                                                ppathfileabsolute="";
                                                                pfile="";
                                                                ptitle="";
                                                                ptitle=atitle;
                                                                pfile.setzen("");
                                                                pfilebound=false;
                                                                init();
                                                               // tbpnfirst=0;
                                                                tbpnlast=0;
                                                                pmaxx=256;
                                                                pmaxy=80;
};
template<class _typtext,class _typoptik> _textbuffer<_typtext,_typoptik>::~_textbuffer(){
                                                                _listebasis<_textbufferprotokoll<_typtext,_typoptik> >::loeschen();//clear_ring(tbpnfirst);
                                                                plist.loeschen();
};
template<class _typtext,class _typoptik> void _textbuffer<_typtext,_typoptik>::init(){
                                                                pviewx=0;
                                                                pviewy=0;
                                                                pcurx=0;
                                                                pcuroutx=0;
                                                                pcury=0;
                                                                pselectionstartx=0;
                                                                pselectionstarty=0;
                                                                pselectionendx=0;
                                                                pselectionendy=0;
                                                                pselectionmode=false;
                                                                preadonly=false;
                                                                pchanged=false;
                                                                pinsertmode=false;
                                                                pcolortext[0].setzen(255,255,255);
                                                                pcolortext[1].setzen(0,0,0);
                                                                pcolortitle[0].setzen(0,0,0);
                                                                pcolortitle[1].setzen(255,255,255);
                                                                pcolorselection[0].setzen(0,0,0);
                                                                pcolorselection[1].setzen(255,255,255);
                                                                pcontrolmode=false;
                                                                pprotocolmode=false;
};
template<class _typtext,class _typoptik> void _textbuffer<_typtext,_typoptik>::laden(){
                                                                //LE*f;
                                                                _zeichenkette<_typtext> b;
                                                                //int n;
                                                                //---------
                                                                if(pfilebound){
                                                                 plist.loeschen();
                                                               //  oeffnen();
                                                                 
                                                                // f=fopen((char*)pfile,"rb");
                                                                // pfile.loeschencache();
                                                                 if(oeffnen()){
                                                                  position(0);
                                                                  bool ok;
                                                                  while(laden(b)){
                                                                  // n=strlen(b)-2;
                                                                  // if((b[n]==13)&&(b[n+1]==10)) b[n]=0;
                                                                   plist.einhaengen(new _zeichenkette<_typtext>(b));
                                                                  };
                                                                  schliessen();
                                                                  pchanged=false;
                                                                 }else{
                                                                  //error reading datei
                                                                 };
                                                                 //DEBUG
                                                                 //if(plist.anfang())do{
                                                                 // MessageBox(NULL,plist.it->objekt->holen(b),"fkgjdfk",MB_ICONEXCLAMATION);
                                                                 //}while(plist.naechstes());
                                                                };                                                                
};
template<class _typtext,class _typoptik> void _textbuffer<_typtext,_typoptik>::speichern(){
                                                                //FILE*f;
                                                                //_zeichenkette<_typtext> s;
                                                                _listenknoten<_zeichenkette<_typtext> >*sit;
                                                                //_typtext b[8192];
                                                                //_typtext eol[]={13,10,0,0};
                                                                //-------
                                                                if(pfilebound){
                                                                 
                                                                 //f=fopen(pfile,"wb");
                                                                 //pfile.loeschencache();
                                                                 if(oeffnen()){//if(f){
                                                                  if(plist.anfang(sit))do{
                                                                   /*strcpy(b,plist.it->objekt->holen(b,8192));
                                                                   strcat(b,eol);*/
                                                                   speicherneol(*sit->objekt());
                                                                   
                                                                 //  s+=eol;
                                                                 //  fwrite(s,s.speicherlast(),1,f);
                                                                  }while(plist.naechstes(sit));
                                                                  schliessen();
                                                                  pchanged=false;
                                                                 }else{
                                                                  //error creating datei
                                                                 };
                                                                };
};
template<class _typtext,class _typoptik> _liste<_zeichenkette<_typtext> >&_textbuffer<_typtext,_typoptik>::liste(){
                                                                return(plist);
};
template<class _typtext,class _typoptik> _zeichenkette<_typtext> &_textbuffer<_typtext,_typoptik>::holenzeile(int i){
                                                                int c=plist.anzahl();
                                                                _listenknoten<_zeichenkette<_typtext> >*tit;
                                                                int n;
                                                                _zeichenkette<_typtext>*s;   
                                                                //------------------
                                                                if(c>0){
                                                                 if(i<0) i=0;
                                                                 if(i>=c) i=c-1;
                                                                 if(plist.anfang(tit)){
                                                                  for(n=0;n<i;n++) plist.naechstes(tit);
                                                                  return(*tit->objekt());
                                                                 }else{
                                                                  s=new _zeichenkette<_typtext>((_typtext*)"");
                                                                  plist.einhaengen(s);
                                                                  return(*s);
                                                                 };
                                                                }else{
                                                                 s=new _zeichenkette<_typtext>((_typtext*)"");
                                                                 plist.einhaengen(s);
                                                                 return(*s);
                                                                };
};
template<class _typtext,class _typoptik> _zeichenkette<_typtext> &_textbuffer<_typtext,_typoptik>::holenzeile(int i,_listenknoten<_zeichenkette<_typtext> >*&tit){
                                                                int c=plist.anzahl();
                                                                //_listenknoten<_zeichenkette>*tit;
                                                                int n;
                                                                //------------------
                                                                tit=0;
                                                                if(c>0){
                                                                 if(i<0) i=0;
                                                                 if(i>=c) i=c-1;
                                                                 if(plist.anfang(tit)){
                                                                  for(n=0;n<i;n++) plist.naechstes(tit);
                                                                 }else{
                                                                  return(ptitle);
                                                                 };
                                                                 return(*tit->objekt);
                                                                };
                                                                return(ptitle);
};
template<class _typtext,class _typoptik> int _textbuffer<_typtext,_typoptik>::holenposition(_listenknoten<_zeichenkette<_typtext> >*it){
                                                                _listenknoten<_zeichenkette<_typtext> >*eit;
                                                                int i;
                                                                int r;
                                                                //------------------
                                                                i=0;
                                                                r=-1;
                                                                if(plist.anfang(eit))do{
                                                                 if(eit==it) r=i;
                                                                 i++;
                                                                }while((plist.naechstes(eit))&&(r==-1));
                                                                return(r);
};
template<class _typtext,class _typoptik> bool _textbuffer<_typtext,_typoptik>::anfang(_listenknoten<_zeichenkette<_typtext> >*&it){
                                                                int n;
                                                                bool c;
                                                                //---------
                                                                c=plist.anfang(it);
                                                                if(c){
                                                                 for(n=0;n<pviewy;n++) {
                                                                  if(plist.naechstes(it)==0) {
                                                                   n=pviewy;
                                                                   plist.vorheriges(it);
                                                                   break;
                                                                  };
                                                                 };
                                                                };
                                                                return(c);                                                                
};
template<class _typtext,class _typoptik> bool _textbuffer<_typtext,_typoptik>::iterator(_listenknoten<_zeichenkette<_typtext> >*it,_typtext*c,int exsize){
                                                                bool r;
                                                                //---------
                                                                r=true;
                                                               // strcpy(c,"");
                                                                it->objekt->holen(c,exsize);
                                                               /* if(pviewx<strlen(b)){
                                                                 bit=pviewx;
                                                                 cit=0;
                                                                 while(b[bit]!=0) c[cit++]=b[bit++];
                                                                 c[cit]=0;
                                                                 r=1;
                                                                };*/
                                                                return(r);
};
template<class _typtext,class _typoptik> bool _textbuffer<_typtext,_typoptik>::naechstes(_listenknoten<_zeichenkette<_typtext> >*&it){
                                                                return(plist.naechstes(it));
};
template<class _typtext,class _typoptik> bool _textbuffer<_typtext,_typoptik>::zeilenreset(_typtext*buffer,_typtext*&it,int&itindex){
                                                                if(buffer[0]==0)return(false); else{
                                                                 it=buffer;
                                                                 itindex=0;
                                                                };
                                                                return(true);
};
template<class _typtext,class _typoptik> bool _textbuffer<_typtext,_typoptik>::zeileniterator(_typtext*&it,int&itindex,_typtext*part,_vektor<_typoptik>*&v,_vektor<_typoptik>*&h){
                                                                _typtext*pit;
                                                                bool r;
                                                                //----------
                                                                r=false;
                                                                pit=part;
                                                                while(*it!=0) {
                                                                 *pit=*it;
                                                                 it++;
                                                                 itindex++;
                                                                 pit++;
                                                                 r=true;
                                                                };
                                                                *pit=0;
                                                                v=&pcolortext[0];
                                                                h=&pcolortext[1];
                                                                return(r);
};
template<class _typtext,class _typoptik> void _textbuffer<_typtext,_typoptik>::loeschen(){
                                                                _listebasis<_textbufferprotokoll<_typtext,_typoptik> >::loeschen();
                                                                //clear_ring(tbpnfirst);
                                                                tbpnlast=0;
                                                                //tbpnfirst=0;
                                                                plist.loeschen();
                                                                pchanged=true;
                                                                pviewx=0;
                                                                pviewy=0;
                                                                pcurx=0;
                                                                pcuroutx=0;
                                                                pcury=0;
                                                                pselectionstartx=0;
                                                                pselectionstarty=0;
                                                                pselectionendx=0;
                                                                pselectionendy=0;
};
template<class _typtext,class _typoptik> void _textbuffer<_typtext,_typoptik>::loeschentext(){
                                                                //clear_ring(tbpnfirst);
                                                                _listebasis<_textbufferprotokoll<_typtext,_typoptik> >::loeschen();
                                                                tbpnlast=0;
                                                                //tbpnfirst=0;
                                                                plist.loeschen();
                                                                pchanged=true;
};
//------------------------------------------------------------- protocolbufferfunktionen ------------------------------------------------------------------------------------------------------------------------------
template<class _typtext,class _typoptik> _textbufferprotokoll<_typtext,_typoptik>* _textbuffer<_typtext,_typoptik>::erzeugenprotokolleinzel(bool i,int x,int y,_typtext c){
                                                                loeschenueberlappendesprotokoll();
                                                                tbpnlast=new _textbufferprotokoll<_typtext,_typoptik>(this);
                                                                new _textbufferprotokollknoteneinzel<_typtext,_typoptik>(tbpnlast,i,x,y,c);
                                                                return(tbpnlast);
};
template<class _typtext,class _typoptik> _textbufferprotokoll<_typtext,_typoptik>*_textbuffer<_typtext,_typoptik>::erzeugenprotokollmulti(bool i,int x,int y,_zeichenkette<_typtext>&c){
                                                                loeschenueberlappendesprotokoll();
                                                                tbpnlast=new _textbufferprotokoll<_typtext,_typoptik>(this);
                                                                new _textbufferprotokollknotenmulti<_typtext,_typoptik>(tbpnlast,i,x,y,c);
                                                                return(tbpnlast);
};
template<class _typtext,class _typoptik> _textbufferprotokoll<_typtext,_typoptik>* _textbuffer<_typtext,_typoptik>::erzeugenprotokollzeile(bool i,int y,_zeichenkette<_typtext>&c){
                                                                loeschenueberlappendesprotokoll();
                                                                tbpnlast=new _textbufferprotokoll<_typtext,_typoptik>(this);
                                                                new _textbufferprotokollknotenzeile<_typtext,_typoptik>(tbpnlast,i,y,c);
                                                                return(tbpnlast);
};
template<class _typtext,class _typoptik> void _textbuffer<_typtext,_typoptik>::undo(){
                                                                if(tbpnlast!=0){
                                                                 if(tbpnlast->undo()) veraendern(true);
                                                                 if(tbpnlast==erstes()){
                                                                  tbpnlast=0;
                                                                 }else{
                                                                  tbpnlast=tbpnlast->vorheriges();
                                                                 };
                                                                };
};
template<class _typtext,class _typoptik> void _textbuffer<_typtext,_typoptik>::redo(){
                                                                if(tbpnlast==0){
                                                                 if(erstes()) {
                                                                  tbpnlast=erstes();
                                                                  if(tbpnlast->redo()) veraendern(true);
                                                                 };
                                                                }else{
                                                                 if(tbpnlast!=erstes()->vorheriges()){
                                                                  tbpnlast=tbpnlast->naechstes();
                                                                  if(tbpnlast->redo()) veraendern(true);
                                                                 };
                                                                };
};
template<class _typtext,class _typoptik> bool _textbuffer<_typtext,_typoptik>::undoable() const{
                                                                if(erstes()==0) return(false); 
                                                                if(tbpnlast!=0) return(true); else return(false);
};
template<class _typtext,class _typoptik> bool _textbuffer<_typtext,_typoptik>::redoable() const{
                                                                if(erstes()==0) return(false);
                                                                if(tbpnlast==0) return(true);
                                                                if(tbpnlast->naechstes()==erstes()) return(false); else return(true);
};
template<class _typtext,class _typoptik> void _textbuffer<_typtext,_typoptik>::loeschenueberlappendesprotokoll(){
                                                                _textbufferprotokoll<_typtext,_typoptik>*it;
                                                                //------------------
                                                                if(tbpnlast==0){
                                                                 _listebasis<_textbufferprotokoll<_typtext,_typoptik> >::loeschen();//clear_ring(tbpnfirst);
                                                                }else{
                                                                 if(tbpnlast->naechstes()!=erstes()){
                                                                  it=tbpnlast->naechstes();
                                                                  if(it)do{
                                                                   it->loeschmarkierung(true);
                                                                   //it=it->naechstes;
                                                                  }while(naechstes(it));
                                                                  loeschmarkierung();//::loeschenmarkiert(tbpnfirst);
                                                                  if(erstes()==0){
                                                                   tbpnlast=0;
                                                                  }else{
                                                                   tbpnlast=erstes()->vorheriges();
                                                                  };
                                                                 };
                                                                };
};
//------------------------------------------------------------- statusfunktionen ------------------------------------------------------------------------------------------------------------------------------
template<class _typtext,class _typoptik> _zeichenkette<_typtext>&_textbuffer<_typtext,_typoptik>::titel(){
                                                                return(ptitle);
};
template<class _typtext,class _typoptik> _zeichenkette<char>&_textbuffer<_typtext,_typoptik>::datei(){
                                                                return(pfile);
};
template<class _typtext,class _typoptik> _zeichenkette<char>&_textbuffer<_typtext,_typoptik>::pfad(){
                                                                return(ppath);
};
template<class _typtext,class _typoptik> void _textbuffer<_typtext,_typoptik>::pfad(_zeichenkette<char> p){
                                                                p.konvertiereninklein();
                                                                ppath=p;
                                                                ppathabsolute=p;
                                                                ppathfileabsolute=p+(char*)"\\"+pfile;
                                                                dateiname(ppathfileabsolute);
};
template<class _typtext,class _typoptik> _zeichenkette<char>&_textbuffer<_typtext,_typoptik>::pfadabsolut(){
                                                                return(ppathabsolute);
};
template<class _typtext,class _typoptik> _zeichenkette<char>&_textbuffer<_typtext,_typoptik>::pfaddateiabsolut(){
                                                                return(ppathfileabsolute);
};
template<class _typtext,class _typoptik> void _textbuffer<_typtext,_typoptik>::aktualisieren(){
};
template<class _typtext,class _typoptik> int _textbuffer<_typtext,_typoptik>::anzahl(){
                                                                return(plist.anzahl());
};
template<class _typtext,class _typoptik> int _textbuffer<_typtext,_typoptik>::groesse() const{
                                                                _listenknoten<_zeichenkette<_typtext> >*it;
                                                                int r;
                                                                //------------------
                                                                r=0;
                                                                if(plist.anfang(it))do{
                                                                 r+=it->objekt->groesse();
                                                                }while(plist.naechstes(it));
                                                                return(r);
};
template<class _typtext,class _typoptik> int _textbuffer<_typtext,_typoptik>::speicherlast() const{
                                                                return(groesse()*sizeof(_typtext));
};
template<class _typtext,class _typoptik> bool _textbuffer<_typtext,_typoptik>::nurlesen() const{
                                                                return(preadonly);
};
template<class _typtext,class _typoptik> void _textbuffer<_typtext,_typoptik>::nurlesen(bool b){
                                                                preadonly=b;
};
template<class _typtext,class _typoptik> bool _textbuffer<_typtext,_typoptik>::dateigebunden() const{
                                                                return(pfilebound);
};
template<class _typtext,class _typoptik> void _textbuffer<_typtext,_typoptik>::dateigebunden(_zeichenkette<char> apath,_zeichenkette<char> afile){
                                                                afile.konvertiereninklein();
                                                                apath.konvertiereninklein();
                                                                pfile=afile;        
                                                                ppath=apath;
                                                                ppathabsolute=apath;
                                                                ppathfileabsolute=ppathabsolute+"\\"+pfile;
                                                                pfilebound=true;
                                                                dateiname(ppathfileabsolute);
};
template<class _typtext,class _typoptik> void _textbuffer<_typtext,_typoptik>::dateiungebunden(){
                                                                pfile="";   
                                                                ppath="";
                                                                ppathabsolute="";
                                                                ppathfileabsolute=ppathabsolute;
                                                                pfilebound=false;
};
template<class _typtext,class _typoptik> bool _textbuffer<_typtext,_typoptik>::veraendert() const{
                                                                return(pchanged);
};
template<class _typtext,class _typoptik> void _textbuffer<_typtext,_typoptik>::veraendern(bool b){
                                                                pchanged=b;
                                                                aktualisieren();
};
template<class _typtext,class _typoptik> bool _textbuffer<_typtext,_typoptik>::einfuegemodus() const{
                                                                return(pinsertmode);
};
template<class _typtext,class _typoptik> void _textbuffer<_typtext,_typoptik>::einfuegemodus(bool b){
                                                                pinsertmode=b;
};
template<class _typtext,class _typoptik> bool _textbuffer<_typtext,_typoptik>::steuermodus() const{
                                                                return(pcontrolmode);
};
template<class _typtext,class _typoptik> void _textbuffer<_typtext,_typoptik>::steuermodus(bool b){
                                                                pcontrolmode=b;        
};
template<class _typtext,class _typoptik> bool _textbuffer<_typtext,_typoptik>::protokollmodus() const{
                                                                return(pprotocolmode);
};
template<class _typtext,class _typoptik> void _textbuffer<_typtext,_typoptik>::protokollmodus(bool b){
                                                                pprotocolmode=b;        
};
template<class _typtext,class _typoptik> _vektor<_typoptik>&_textbuffer<_typtext,_typoptik>::farbetext(int i){
                                                                if(i==0) return(pcolortext[0]); else return(pcolortext[1]);
};
template<class _typtext,class _typoptik> _vektor<_typoptik>&_textbuffer<_typtext,_typoptik>::farbetitel(int i){
                                                                if(i==0) return(pcolortitle[0]); else return(pcolortitle[1]);
};
template<class _typtext,class _typoptik> _vektor<_typoptik>&_textbuffer<_typtext,_typoptik>::farbeanwahl(int i){
                                                                if(i==0) return(pcolorselection[0]); else return(pcolorselection[1]);
};
//------------------------------------------------------------- fundamentale textoperationen ------------------------------------------------------------------------------------------------------------------------------
template<class _typtext,class _typoptik> bool _textbuffer<_typtext,_typoptik>::einhaengen(int x,int y,_typtext c){
                                                                _typtext b[4];
                                                                _zeichenkette<_typtext>*s;
                                                                bool rr=false;
                                                                //-------------------
                                                                if(preadonly==false){
                                                                 s=&holenzeile(y);
                                                                 b[0]=c;
                                                                 b[1]=0;
                                                                 s->einhaengen(b,x);
                                                                 rr=true;
                                                                 if(pprotocolmode==false){
                                                                  erzeugenprotokolleinzel(true,x,y,c);  
                                                                 };
                                                                 veraendern(true);
                                                                };
                                                                return(rr);
};
template<class _typtext,class _typoptik> bool _textbuffer<_typtext,_typoptik>::einhaengen(int x,int y,_zeichenkette<_typtext>&s){
                                                                _zeichenkette<_typtext>*si;
                                                                bool rr=false;
                                                                //-------------------
                                                                if(preadonly==false){
                                                                 si=&holenzeile(y);
                                                                 si->einhaengen(s,x);
                                                                 rr=true;
                                                                 if(pprotocolmode==false){
                                                                  erzeugenprotokollmulti(true,x,y,s);
                                                                 };
                                                                 veraendern(true);
                                                                };
                                                                return(rr);
};
template<class _typtext,class _typoptik> bool _textbuffer<_typtext,_typoptik>::einfuegenzeile(int y,_zeichenkette<_typtext>&s){
                                                                _zeichenkette<_typtext>*h;
                                                                _listenknoten<_zeichenkette<_typtext> >*it;
                                                                _listenknoten<_zeichenkette<_typtext> >*of;
                                                                bool rr=false;
                                                                //----------------
                                                                if(preadonly==false){
                                                                 if(plist.anzahl()==0){
                                                                  plist.einhaengen(new _zeichenkette<_typtext>(s));//neu initialisieren
                                                                  rr=true;
                                                                  if(pprotocolmode==false) {
                                                                   erzeugenprotokollzeile(true,y,s);
                                                                  };
                                                                  veraendern(true);
                                                                 }else{   
                                                                  if(y==0){
                                                                   plist.einhaengen(new _zeichenkette<_typtext>(s));//erstes verschieben
                                                                   rr=true;
                                                                   if(pprotocolmode==false) {
                                                                    erzeugenprotokollzeile(true,y,s);
                                                                   };
                                                                   plist.erstes=plist.erstes->vorheriges;
                                                                   veraendern(true);
                                                                  }else{
                                                                   it=0;
                                                                   h=&holenzeile(y,it);
                                                                   if(it){
                                                                    of=plist.erstes;
                                                                    plist.erstes=it/*->naechstes*/;
                                                                    plist.einhaengen(new _zeichenkette<_typtext>(s));//einfügen
                                                                    rr=true;
                                                                    if(pprotocolmode==false){
                                                                     erzeugenprotokollzeile(true,y,s);
                                                                    };
                                                                    //if(pprotocolmode==false) erzeugenprotokollzeile(true,y,s);  
                                                                    plist.erstes=of;
                                                                    veraendern(true);
                                                                   }else{
                                                                    plist.einhaengen(new _zeichenkette<_typtext>(s));//anhängen
                                                                    rr=true;
                                                                    if(pprotocolmode==false) {
                                                                     erzeugenprotokollzeile(true,y,s);
                                                                    };
                                                                    veraendern(true);
                                                                   };
                                                                  };
                                                                 };
                                                                };
                                                                return(rr);                                                             
};
template<class _typtext,class _typoptik> bool _textbuffer<_typtext,_typoptik>::aushaengen(int x,int y,int l){
                                                              //  int x,y;
                                                                _zeichenkette<_typtext>*s;
                                                                _listenknoten<_zeichenkette<_typtext> >*it;
                                                                _listenknoten<_zeichenkette<_typtext> >*nit;
                                                                _typtext c;
                                                                _typtext b[8192];
                                                                _textbufferprotokoll<_typtext,_typoptik>*knoten;
                                                                _zeichenkette<_typtext> h;
                                                                int i;
                                                                int bit;
                                                                bool rr=false;
                                                                //-------------------
                                                              //  peep(500);
                                                                if((preadonly==false)&&(l!=0)){
                                                                 //x=cursor(0);
                                                                 //y=cursor(1);
                                                                 s=&holenzeile(y,it);
                                                                 if(x<s->groesse()){//zeichen innerhalb einer zeile löschen
                                                                  if(l==1){
                                                                   c=(*(s))[x];
                                                                   s->aushaengen(x,1);
                                                                   rr=true;
                                                                   if(pprotocolmode==false){
                                                                    erzeugenprotokolleinzel(false,x,y,c);
                                                                   };
                                                                   veraendern(true);//pchanged=true;
                                                                  }else{
                                                                  // h="";
                                                                   bit=0;
                                                                   for(i=x;i<x+l;i++){
                                                                    c=(*(s))[x];
                                                                    b[bit++]=c;
                                                                   };
                                                                   b[bit]=0;
                                                                   h=b;
                                                                   s->aushaengen(x,l);
                                                                   rr=true;
                                                                   if(pprotocolmode==false){
                                                                    erzeugenprotokollmulti(false,x,y,h);
                                                                   };
                                                                   veraendern(true);//pchanged=true;
                                                                  };
                                                                 }else{
                                                                  if(it->naechstes==plist.erstes){//letzte zeile, nichts löschen
                                                                  }else{//naechstes-zeile hier (an iterator) anhängen und nextzeile löschen
                                                                   nit=it->naechstes;
                                                                   //nit->objekt->holen(b);
                                                                   s->anhaengen(nit->objekt);
                                                                   rr=true;
                                                                   if(pprotocolmode==false){
                                                                    knoten=erzeugenprotokollmulti(true,x,y,*nit->objekt);
                                                                    new _textbufferprotokollknotenzeile<_typtext,_typoptik>(knoten,false,y+1,*nit->objekt);//knoten->extension(false,0,y+1,b);
                                                                   // peep(1000);projector->window()->status->text(y+1);
                                                                   };
                                                                   delete nit->objekt;
                                                                   delete nit;
                                                                   veraendern(true);
                                                                   //veraendern(true);//pchanged=true;
                                                                  };   
                                                                 };
                                                                };
                                                                return(rr);
};
template<class _typtext,class _typoptik> bool _textbuffer<_typtext,_typoptik>::entfernenzeile(int y){
                                                                _zeichenkette<_typtext>*h;
                                                                _listenknoten<_zeichenkette<_typtext> >*it;
                                                                _listenknoten<_zeichenkette<_typtext> >*of;
                                                                bool rr=0;
                                                                //----------------
                                                              //  peep(20000);
                                                                if((preadonly==false)&&(plist.anzahl()>0)){
                                                                 if(y==0){
                                                                  
                                                                  of=plist.erstes->naechstes;
                                                                  if(of==plist.erstes){
                                                                   rr=true;                                                                 
                                                                   if(pprotocolmode==false){
                                                                    erzeugenprotokollmulti(false,0,y,*plist.erstes->objekt);
                                                                   };   
                                                                   plist.erstes->objekt->setzen("");   
                                                                   veraendern(true);
                                                                  }else{
                                                                   rr=true;                                                                 
                                                                   if(pprotocolmode==false){
                                                                    erzeugenprotokollzeile(false,y,*plist.erstes->objekt);
                                                                   };
                                                                   delete plist.erstes->objekt;
                                                                   delete plist.erstes;
                                                                   plist.erstes=of;
                                                                   veraendern(true);
                                                                  };
                                                                 }else{
                                                                  h=&holenzeile(y,it);
                                                                  if(it){
                                                                   rr=true;
                                                                   if(pprotocolmode==false){
                                                                    erzeugenprotokollzeile(false,y,*plist.erstes->objekt);
                                                                   };
                                                                   delete it->objekt;
                                                                   delete it;
                                                                   veraendern(true);
                                                                  };
                                                                 };
                                                                };
                                                                return(rr);                                                            
};
//------------------------------------------------------------- textoperationen ------------------------------------------------------------------------------------------------------------------------------
template<class _typtext,class _typoptik> _zeichenkette<_typtext>* _textbuffer<_typtext,_typoptik>::anhaengen(_typtext*c){
                                                                _zeichenkette<_typtext>*s=new _zeichenkette<_typtext>(c);
                                                               // projector->window()->schreiben("kfdjgk",c);
                                                                plist.einhaengen(s);
                                                                veraendern(true);
                                                                return(s);
                                                                //resetcommentmode();
};
template<class _typtext,class _typoptik> void _textbuffer<_typtext,_typoptik>::anhaengenchar(_typtext c){
                                                                _listenknoten<_zeichenkette<_typtext> >*tit;
                                                                _typtext h[2];
                                                                //---------------
                                                                if(plist.anfang(tit)){
                                                                 plist.vorheriges(tit);
                                                                 h[0]=c;
                                                                 h[1]=0;
                                                                 tit->objekt->anhaengen(h);   
                                                                 //plist.einhaengen(new _zeichenkette(c));
                                                                 //pchanged=true;
                                                                }else{
                                                                 anhaengen("");
                                                                 anhaengenchar(c);
                                                                };
                                                                veraendern(true);
                                                                //resetcommentmode();
};
template<class _typtext,class _typoptik> void _textbuffer<_typtext,_typoptik>::einfuegenreturn(){
                                                                int x,y,z,fs;
                                                                _typtext buffer[8192];
                                                                _typtext part[8192];
                                                                int pit;
                                                                int bit;
                                                                _listenknoten<_zeichenkette<_typtext> >*it;
                                                                _listenknoten<_zeichenkette<_typtext> >*nit;
                                                                _zeichenkette<_typtext>*s;
                                                                _listenknoten<_zeichenkette<_typtext> >*oldfirst;
                                                                _zeichenkette<_typtext> nullstring="";
                                                                _zeichenkette<_typtext> h;
                                                                _textbufferprotokoll<_typtext,_typoptik>*prot;
                                                                //---------
                                                                if(preadonly==false){
                                                                 x=cursor(0);
                                                                 y=cursor(1);
                                                                 s=&holenzeile(y,it);
                                                                 nit=it->naechstes;
                                                                 s->holen(buffer,8192);
                                                                 if(plist.erstes==0){
                                                                  plist.einhaengen(new _zeichenkette<_typtext>(""));
                                                                  if(pprotocolmode==false) prot=erzeugenprotokollzeile(true,0,nullstring);
                                                                  veraendern(true);//pchanged=true;
                                                                 }else{
                                                                  part[0]=0;
                                                                  pit=0;
                                                                  bit=x;
                                                                  if(((unsigned int)(x))<s->groesse()){
                                                                   while(buffer[bit]) part[pit++]=buffer[bit++];
                                                                   part[pit]=0;
                                                                   h=part;
                                                                   s->aushaengen(x,s->groesse()-x);
                                                                   if(pprotocolmode==false) prot=erzeugenprotokollmulti(false,x,y,h);
                                                                   oldfirst=plist.erstes;
                                                                   plist.erstes=nit;
                                                                   h="";
                                                                   fs=anzahlfrontleerzeichen(*s);
                                                                   for(z=0;z<fs;z++) h+=" ";
                                                                   h+=part;
                                                                   //h.holen(part);
                                                                   plist.einhaengen(new _zeichenkette<_typtext>(h));
                                                                   plist.erstes=oldfirst;
                                                                   if(pprotocolmode==false) new _textbufferprotokollknotenzeile<_typtext,_typoptik>(prot,true,y+1,h);
                                                                   veraendern(true);//pchanged=true;
                                                                  }else{//einfache eine neue zeile erstellen und die einrückung vornehmen
                                                                   oldfirst=plist.erstes;   
                                                                   plist.erstes=nit;
                                                                   h="";
                                                                   fs=anzahlfrontleerzeichen(*s);
                                                                   for(z=0;z<fs;z++) h+=" ";
                                                                   plist.einhaengen(new _zeichenkette<_typtext>(h));
                                                                   plist.erstes=oldfirst;
                                                                  /* h+=part;
                                                                   h.holen(part);*/
                                                                   if(pprotocolmode==false) prot=erzeugenprotokollzeile(true,y+1,h);
                                                                   veraendern(true);//pchanged=true;
                                                                  };
                                                                 };
                                                                };
};
template<class _typtext,class _typoptik> void _textbuffer<_typtext,_typoptik>::einfuegenbackspace(){
                                                                int x,y;
                                                                _listenknoten<_zeichenkette<_typtext> >*it;
                                                                _listenknoten<_zeichenkette<_typtext> >*pit;
                                                                _zeichenkette<_typtext>*s;
                                                                _textbufferprotokoll<_typtext,_typoptik>*prot;
                                                                _typtext c;
                                                                //-----------------
                                                                if(preadonly==false){
                                                                 x=cursor(0);
                                                                 y=cursor(1);
                                                                 s=&holenzeile(y,it);
                                                                 if(x==0){
                                                                  if(it!=plist.erstes){//
                                                                   pit=it->vorheriges;
                                                                   if(pprotocolmode==false){
                                                                    prot=erzeugenprotokollmulti(true,pit->objekt->groesse(),y-1,*it->objekt);
                                                                    new _textbufferprotokollknotenzeile<_typtext,_typoptik>(prot,false,y,*it->objekt);
                                                                   };
                                                                   pit->objekt->anhaengen(it->objekt);
                                                                   delete it->objekt;
                                                                   delete it;
                                                                   veraendern(true);//pchanged=true;
                                                                  }else{//anfang der Datei , nichts machen
                                                                  };
                                                                 }else{
                                                                  c=(*(s))[x-1];   
                                                                  s->aushaengen(x-1,1);
                                                                  if(pprotocolmode==false){
                                                                   prot=erzeugenprotokolleinzel(false,x-1,y,c);
                                                                  };
                                                                  veraendern(true);//pchanged=true;
                                                                 };
                                                                };
};
template<class _typtext,class _typoptik> void _textbuffer<_typtext,_typoptik>::ersetzen(int x,int y,_zeichenkette<_typtext>&f,_zeichenkette<_typtext>&r){
                                                                _listenknoten<_zeichenkette<_typtext> >*it;
                                                                _zeichenkette<_typtext>*s;
                                                                _textbufferprotokoll<_typtext,_typoptik>*prot=0;
                                                                //-----------------
                                                                if(preadonly==false){
                                                                 s=&holenzeile(y,it);
                                                                 s->aushaengen(x,f.groesse());
                                                                 s->einhaengen(r,x);
                                                                 if(pprotocolmode==false){
                                                                  prot=erzeugenprotokollmulti(false,x,y,f);
                                                                  new _textbufferprotokollknotenmulti<_typtext,_typoptik>(prot,true,x,y,r);
                                                                 };
                                                                 veraendern(true);
                                                                };
};
template<class _typtext,class _typoptik> void _textbuffer<_typtext,_typoptik>::einbauen(int x,int y,_textbuffer<_typtext,_typoptik>*tb){
                                                                _listenknoten<_zeichenkette<_typtext> >*tbit;
                                                                _listenknoten<_zeichenkette<_typtext> >*it;
                                                                _zeichenkette<_typtext> h;
                                                                _zeichenkette<_typtext> hh;
                                                                bool umbruch;
                                                                _listenknoten<_zeichenkette<_typtext> >*of;
                                                                bool beix;
                                                                _typtext buffer[8192];
                                                                _typtext part[8192];
                                                                int bit;
                                                                int pit;
                                                                int yit;
                                                                int cut;
                                                                _textbufferprotokoll<_typtext,_typoptik>*prot;
                                                                bool mod;
                                                                //----------------
                                                                if(preadonly==false){
                                                                 holenzeile(y,it);
                                                                 yit=y;
                                                                 prot=0;
                                                                 beix=true;
                                                                 mod=false;
                                                                 if(tb->anfang(tbit))do{
                                                                  h=*tbit->objekt;
                                                                  if(h[0]!=0){  
                                                                   if(h[h.groesse()-1]==10){
                                                                    h.aushaengen(h.groesse()-1,1);
                                                                    umbruch=true;
                                                                   }else{
                                                                    umbruch=false;   
                                                                   };
                                                                   if(beix){//-------------------------------------------------------------------------------------------------------- 1.zeile 
                                                                    if(pprotocolmode==false){
                                                                     if(prot==0){
                                                                      prot=erzeugenprotokollmulti(true,x,y,h);
                                                                     }else{
                                                                      new _textbufferprotokollknotenmulti<_typtext,_typoptik>(prot,true,x,y,h);
                                                                     };
                                                                    };
                                                                    it->objekt->einhaengen(h,x);//teil einhaengen bei x,y (buffering)
                                                                    mod=true;
                                                                    if(umbruch){//anfang der zeile hinter it schieben (neue zeile erzeugen)
                                                                     it->objekt->holen(buffer,8192);
                                                                     cut=x+h.groesse();
                                                                     bit=cut;
                                                                     pit=0;
                                                                     while(buffer[bit]!=0) part[pit++]=buffer[bit++];
                                                                     part[pit]=0;
                                                                     of=plist.erstes;
                                                                     plist.erstes=it->naechstes;
                                                                     hh=part;   
                                                                     if(pprotocolmode==false){
                                                                      new _textbufferprotokollknotenzeile<_typtext,_typoptik>(prot,true,y+1,hh);
                                                                     };
                                                                     plist.einhaengen(new _zeichenkette<_typtext>(part));//linie einhaengen bei 0,y+1 (buffering)
                                                                     plist.erstes=of;
                                                                     if(pprotocolmode==false){
                                                                      new _textbufferprotokollknotenmulti<_typtext,_typoptik>(prot,false,cut,y,hh);
                                                                     };
                                                                     it->objekt->aushaengen(cut,it->objekt->groesse()-cut);
                                                                     it=it->naechstes;
                                                                     yit++;//?????????????????????????????
                                                                    }; 
                                                                   }else{//-------------------------------------------------------------------------------------------------------------- rest
                                                                    if(umbruch){
                                                                     if(pprotocolmode==false){
                                                                      new _textbufferprotokollknotenzeile<_typtext,_typoptik>(prot,true,yit,h);
                                                                     };
                                                                     of=plist.erstes;
                                                                     plist.erstes=it;
                                                                     plist.einhaengen(new _zeichenkette<_typtext>(h));//linie einhaengen bei  0,yit (buffering)
                                                                     plist.erstes=of;
                                                                     yit++;
                                                                     mod=true;
                                                                    }else{//es kann sich nur um die letzte zeile handeln
                                                                     if(pprotocolmode==false){
                                                                      new _textbufferprotokollknotenmulti<_typtext,_typoptik>(prot,true,0,yit,h);
                                                                     };
                                                                     it->objekt->einhaengen(h,0);
                                                                     mod=true;
                                                                    };
                                                                   };
                                                                   beix=false;    
                                                                  };
                                                                 }while(tb->naechstes(tbit));
                                                                 if(mod) veraendern(true);
                                                                };    
};
//------------------------------------------------------------- textoperationen, suchen und ersetzen ------------------------------------------------------------------------------------------------------------------------------
template<class _typtext,class _typoptik> bool _textbuffer<_typtext,_typoptik>::suchenvorheriges(int&,int&,_zeichenkette<_typtext>&,bool){
                                                                return(false);
};
template<class _typtext,class _typoptik> bool _textbuffer<_typtext,_typoptik>::suchennaechstes(int&x,int&y,_zeichenkette<_typtext>&s,bool sensible){
                                                                _listenknoten<_zeichenkette<_typtext> >*it;
                                                                int xx=x;
                                                                int yy=y;
                                                                bool found;
                                                                //--------------------
                                                                holenzeile(y,it);
                                                                if(sensible){
                                                                 found=it->objekt->suchen(s,xx);
                                                                }else{
                                                                 found=it->objekt->suchenunsensibel(s,xx);
                                                                };
                                                                if(found){
                                                                 x=xx;
                                                                 return(true);   
                                                                }else{
                                                                 it=it->naechstes;
                                                                 yy++;
                                                                 while(it!=plist.erstes){
                                                                  xx=0;   
                                                                  if(sensible){
                                                                   found=it->objekt->suchen(s,xx);
                                                                  }else{
                                                                   found=it->objekt->suchenunsensibel(s,xx);
                                                                  };
                                                                  if(found){
                                                                   x=xx;
                                                                   y=yy;
                                                                   return(true);
                                                                  };
                                                                  it=it->naechstes;
                                                                  yy++;
                                                                 };   
                                                                };
                                                                return(false);                          
};
//------------------------------------------------------------- cursoroperationen ------------------------------------------------------------------------------------------------------------------------------
template<class _typtext,class _typoptik> int _textbuffer<_typtext,_typoptik>::cursor(int i){
                                                                //lesen
                                                                if(i==0){
                                                                 int l;
                                                                 l=holenzeile(pcury).groesse();
                                                                 if(pcurx>l) pcuroutx=l; else pcuroutx=pcurx;
                                                                 return(pcuroutx);
                                                                }else{
                                                                 return(pcury);
                                                                };
};
template<class _typtext,class _typoptik> void _textbuffer<_typtext,_typoptik>::cursor(int x,int y){
                                                                int l;
                                                                int c;
                                                                //setzen absolut
                                                                c=plist.anzahl()-1;
                                                                pcurx=pcuroutx=x;
                                                                pcury=y;
                                                                if(pcury>c) pcury=c;
                                                                if(pcury<0) pcury=0;
                                                                l=holenzeile(pcury).groesse();
                                                                if(pcurx>l) pcuroutx=l;
                                                                if(pcurx<0) pcurx=0;
                                                                ansichtinnerhalbcursor(pmaxx,pmaxy);
                                                                //if(pcury<pviewy) pcury=pviewy;
};
template<class _typtext,class _typoptik> void _textbuffer<_typtext,_typoptik>::cursorrelansicht(int x,int y){
                                                                cursor(x+pviewx,y+pviewy);
};
template<class _typtext,class _typoptik> void _textbuffer<_typtext,_typoptik>::cursorbewegung(int mx,int my,int c,int r){
                                                                int l;
                                                                if(c==0){
                                                                 l=holenzeile(pcury).groesse();
                                                                 if(pcurx>l) pcurx=pcuroutx=l;
                                                                 pcurx+=r;
                                                                 if(pcurx<0) pcurx=0;
                                                                 //pcuroutx=pcurx;
                                                                }else{
                                                                 pcury+=r;
                                                                 l=plist.anzahl();
                                                                 if(pcury<0) pcury=0;
                                                                 if(pcury>=l) pcury=l-1;
                                                           //      l=holenzeile(pcury).groesse();
                                                                };
                                                                ansichtinnerhalbcursor(mx,my);
};
template<class _typtext,class _typoptik> bool _textbuffer<_typtext,_typoptik>::cursorinnerhalbansicht(int mx,int my){
                                                                bool r;
                                                                int l;
                                                                int maxlines;
                                                                int maxcolumn;
                                                                //----------
                                                                r=true;
                                                                pcuroutx=pcurx;
                                                                maxlines=my-2;
                                                                maxcolumn=mx-2;
                                                                if(pcury<pviewy) {pcury=pviewy;r=0;};
                                                                if(pcury>pviewy+maxlines) {pcury=pviewy+maxlines;r=0;};
                                                                l=holenzeile(pcury).groesse();
                                                                if(pcurx>pviewx+maxcolumn) {pcurx=pviewx+maxcolumn;r=0;};
                                                                if(pcurx<=pviewx) {
                                                                 if(l>pviewx){
                                                                  pcurx=pviewx;
                                                                  r=false;
                                                                 }else{
                                                                  r=false;
                                                                 };
                                                                };
                                                                if(pcurx>l) pcuroutx=l;
                                                                return(r);
};
//------------------------------------------------------------- viewoperationen ------------------------------------------------------------------------------------------------------------------------------
template<class _typtext,class _typoptik> int _textbuffer<_typtext,_typoptik>::ansicht(int i) const{
                                                                if(i==0){
                                                                 return(pviewx);
                                                                }else{
                                                                 return(pviewy);
                                                                };
};
template<class _typtext,class _typoptik> void _textbuffer<_typtext,_typoptik>::ansicht(int mx,int my,int c,int r){
                                                                if(c==0){
                                                                 pviewx=r;
                                                                 if(pviewx<0) pviewx=0;
                                                                }else{
                                                                 pviewy=r;
                                                                 if(pviewy<0) pviewy=0;
                                                                 if(r>0){
                                                                  int ym=plist.anzahl();   
                                                                  if(pviewy>(ym-1)) pviewy=ym-1;
                                                                 };
                                                                };
                                                                cursorinnerhalbansicht(mx,my);
};
template<class _typtext,class _typoptik> void _textbuffer<_typtext,_typoptik>::ansichtbewegung(int mx,int my,int c,int r){
                                                                if(c==0){
                                                                 pviewx+=r;
                                                                 if(pviewx<0) pviewx=0;
                                                                }else{
                                                                 pviewy+=r;
                                                                 if(pviewy<0) pviewy=0;
                                                                 if(r>0){
                                                                  int ym=plist.anzahl();   
                                                                  if(pviewy>(ym-1)) pviewy=ym-1;
                                                                 };
                                                                };
                                                                cursorinnerhalbansicht(mx,my);
};
template<class _typtext,class _typoptik> void _textbuffer<_typtext,_typoptik>::ansichtyink(int mx,int my,int i){
                                                                int ym=plist.anzahl();
                                                                pviewy+=i;
                                                                if(pviewy>(ym-1)) pviewy=ym-1;
                                                                cursorinnerhalbansicht(mx,my);
};
template<class _typtext,class _typoptik> void _textbuffer<_typtext,_typoptik>::ansichtydek(int mx,int my,int i){
                                                                pviewy-=i;
                                                                if(pviewy<0) pviewy=0;
                                                                cursorinnerhalbansicht(mx,my);
};
template<class _typtext,class _typoptik> bool _textbuffer<_typtext,_typoptik>::ansichtinnerhalbcursor(int mx,int my){
                                                                bool r;
                                                                int maxlines;
                                                                int maxcolumn;
                                                                //-----------
                                                                maxlines=my-2;
                                                                maxcolumn=mx-2;
                                                                r=true;
                                                                if(pviewy>cursor(1)) pviewy=cursor(1);
                                                                if((pviewy+maxlines)<cursor(1)) pviewy=cursor(1)-maxlines;
                                                                if(pviewx>cursor(0)) pviewx=cursor(0);
                                                                if((pviewx+maxcolumn)<cursor(0)) pviewx=cursor(0)-maxcolumn;
                                                                return(r);
};
template<class _typtext,class _typoptik> void _textbuffer<_typtext,_typoptik>::ansichtmaximal(int x,int y){
                                                                if(x<0)x=0;
                                                                if(y<0)y=0;
                                                                pmaxx=x;
                                                                pmaxy=y;
};
//------------------------------------------------------------- selektionsperationen ------------------------------------------------------------------------------------------------------------------------------
template<class _typtext,class _typoptik> bool _textbuffer<_typtext,_typoptik>::anwahl() const{
                                                                if((pselectionendx==pselectionstartx)&&(pselectionendy==pselectionstarty)) return(false); else return(true);
                                                                
};
template<class _typtext,class _typoptik> int _textbuffer<_typtext,_typoptik>::anwahlholen(int&x0,int&y0,int&x1,int&y1) const{
                                                                int h;
                                                                int i;
                                                                x0=pselectionstartx;
                                                                y0=pselectionstarty;
                                                                x1=pselectionendx;
                                                                y1=pselectionendy;
                                                                i=+1;
                                                                if((y0==y1)&&(x0==x1)) i=0; else
                                                                if(y1<y0){
                                                                 h=y1;
                                                                 y1=y0;
                                                                 y0=h;
                                                                 h=x1;
                                                                 x1=x0;
                                                                 x0=h;
                                                                 i=-1;
                                                                }else
                                                                if(y1==y0){
                                                                 if(x1<x0){
                                                                  h=x1;
                                                                  x1=x0;
                                                                  x0=h;
                                                                  h=y1;
                                                                  y1=y0;
                                                                  y0=h;
                                                                 };
                                                                };
                                                                return(i);
};
template<class _typtext,class _typoptik> void _textbuffer<_typtext,_typoptik>::anwahlsetzen(int x0,int y0,int x1,int y1){
                                                                int lines=plist.anzahl()-1;
                                                                //----------------------
                                                                if(x0<0) x0=0;
                                                                if(y0<0) y0=0;
                                                                if(x1<0) x1=0;
                                                                if(y1<0) y1=0;
                                                                if(y0>lines) y0=lines;
                                                                if(y1>(lines+1)) y1=lines+1;
                                                                if(y1==lines+1){
                                                                 x1=0;
                                                                };
                                                                pselectionstartx=x0;
                                                                pselectionstarty=y0;
                                                                pselectionendx=x1;
                                                                pselectionendy=y1;
};
template<class _typtext,class _typoptik> void _textbuffer<_typtext,_typoptik>::anwahlsetzenbeginn(int x0,int y0){
                                                                anwahlsetzen(x0,y0,pselectionendx,pselectionendy);                                                                
};
template<class _typtext,class _typoptik> void _textbuffer<_typtext,_typoptik>::anwahlsetzenende(int x1,int y1){
                                                                anwahlsetzen(pselectionstartx,pselectionstarty,x1,y1);                                                                
                                                                        
};
template<class _typtext,class _typoptik> void _textbuffer<_typtext,_typoptik>::anwahlbeginn(){
                                                                int x,y;
                                                                x=cursor(0);
                                                                y=cursor(1);
                                                                pselectionmode=true;
                                                                anwahlsetzen(x,y,x,y);
                                                                anwahlsetzenbeginn(x,y);
};
template<class _typtext,class _typoptik> void _textbuffer<_typtext,_typoptik>::selectionmove(){
                                                                int x,y;
                                                                if(pselectionmode){
                                                                 x=cursor(0);
                                                                 y=cursor(1);        
                                                                 anwahlsetzenende(x,y);
                                                                }else{
                                                                 anwahlloeschen();
                                                                };
};
template<class _typtext,class _typoptik> void _textbuffer<_typtext,_typoptik>::anwahlende(){
                                                                pselectionmode=false;
};
template<class _typtext,class _typoptik> bool _textbuffer<_typtext,_typoptik>::anwahlmodus() const{
                                                                return(pselectionmode);
};
template<class _typtext,class _typoptik> void _textbuffer<_typtext,_typoptik>::anwahlmodus(bool b){
                                                                pselectionmode=b;
};
template<class _typtext,class _typoptik> void _textbuffer<_typtext,_typoptik>::anwahlloeschen(){
                                                                pselectionmode=false;
                                                                anwahlsetzen(0,0,0,0);
};
template<class _typtext,class _typoptik> bool _textbuffer<_typtext,_typoptik>::anwahlteilung(int zeile,_typtext*part,int partindex,int selx0,int sely0,int selx1,int sely1,int&anzahl,_typtext*&p0,_typtext*&p1,_typtext*&p2,bool*selected){
                                                                bool r;
                                                                int l;
                                                                //-------------
                                                                r=false;
                                                                anzahl=0;
                                                                if(part[0]!=0){
                                                                 if((zeile>=sely0)&&(zeile<=sely1)){
                                                                  if((zeile>sely0)&&(zeile<sely1)){//mittendrinne
                                                                   anzahl=1;
                                                                   p0=part;
                                                                   selected[0]=true;
                                                                  }else
                                                                  if((zeile==sely0)&&(zeile<sely1)){//kante oben
                                                                   if(selx0<=partindex){
                                                                    anzahl=1;
                                                                    p0=part;
                                                                    selected[0]=true;
                                                                   }else{
                                                                    l=strlen(part)+partindex;
                                                                    if(selx0<l){
                                                                     p0=part;
                                                                     selected[0]=false;
                                                                     p1=&part[selx0-partindex];
                                                                     selected[1]=true;
                                                                     anzahl=2;
                                                                    };
                                                                   };
                                                                  }else
                                                                  if((zeile>sely0)&&(zeile==sely1)){//kante unten
                                                                   l=strlen(part)+partindex;
                                                                   if(selx1>=l){
                                                                    anzahl=1;
                                                                    p0=part;
                                                                    selected[0]=true;
                                                                   }else
                                                                   if(selx1>partindex){
                                                                    p0=part;
                                                                    selected[0]=true;
                                                                    p1=&part[selx1-partindex];
                                                                    selected[1]=false;
                                                                    anzahl=2;      
                                                                   };  
                                                                  }else
                                                                  if((zeile==sely0)&&(zeile==sely1)){//zeile beinhaltet anwahl
                                                                   l=strlen(part)+partindex;
                                                                   if((selx0<=partindex)&&(selx1>=l)){//die ganze scheiße angewählt
                                                                    p0=part;
                                                                    selected[0]=true;
                                                                    anzahl=1;
                                                                   }else
                                                                   if((selx0<=partindex)&&(selx1>partindex)&&(selx1<l)){//die scheiße ist z.T. links angewählt, kann konguent sein
                                                                    p0=part;
                                                                    selected[0]=true;
                                                                    p1=&part[selx1-partindex];
                                                                    selected[1]=false;
                                                                    anzahl=2;
                                                                   }else
                                                                   if((selx0>partindex)&&(selx0<l)&&(selx1>=l)){//die scheiße ist z.T. rechts angewählt
                                                                    p0=part;
                                                                    selected[0]=false;
                                                                    p1=&part[selx0-partindex];
                                                                    selected[1]=true;
                                                                    anzahl=2;
                                                                   // char bb[1024];
                                                                   // itoa(partindex,bb,10);
                                                                   // projector->window()->status->text(bb);
                                                                   }else
                                                                   if((selx0>partindex)&&(selx1<l)){//die dscheiße ist innerhalb angewählt
                                                                    p0=part;
                                                                    selected[0]=false;
                                                                    p1=&part[selx0-partindex];
                                                                    selected[1]=true;
                                                                    p2=&part[selx1-partindex];
                                                                    selected[2]=false;
                                                                    anzahl=3;
                                                                   };
                                                                  };
                                                                 };
                                                                }else{
                                                                 if((zeile>=sely0)&&(zeile<=sely1)) {
                                                                  if(zeile<sely1){   
                                                                   p0=part;
                                                                   anzahl=1;
                                                                   selected[0]=true;
                                                                  };
                                                                 };
                                                                };
                                                                if(anzahl>0) r=true;
                                                                return(r);
};

/*
char _textbuffer::typ() const{
                                                                return(ptype);
};
bool _textbuffer::changed() const{
                                                                return(pchanged);
};*/
template<class _typtext,class _typoptik> void _textbuffer<_typtext,_typoptik>::anwahlenfernen(){
                                                                int x0,y0,x1,y1;
                                                                int y;
                                                                _typtext buffer[8192];
                                                                _listenknoten<_zeichenkette<_typtext> >*it;
                                                                _typtext*pi0;
                                                                _typtext*pi1;
                                                                _typtext*pi2;
                                                                bool sel[3];
                                                                int c;
                                                                _listenknoten<_zeichenkette<_typtext> >*eit;
                                                                _listenknoten<_zeichenkette<_typtext> >*neufirst;
                                                                _zeichenkette<_typtext>*s;
                                                                _listenknoten<_zeichenkette<_typtext> >*obenkante;
                                                                _listenknoten<_zeichenkette<_typtext> >*untenkante;
                                                                bool change=false;
                                                                _textbufferprotokoll<_typtext,_typoptik>*prot;
                                                                int countdestruction=0;
                                                                //-----------------
                                                                if(preadonly==false){
                                                                 prot=0;
                                                                 if(anwahlholen(x0,y0,x1,y1)){
                                                                  if(plist.anfang(eit)){
                                                                   eit->loeschenmarkiert=0;    
                                                                  }while(plist.naechstes(eit));
                                                                  obenkante=0;
                                                                  untenkante=0;
                                                                  for(y=y1;y>=y0;y--){
                                                                   s=&holenzeile(y,it);
                                                                   s->holen(buffer,8192);
                                                                   c=0;
                                                                   anwahlteilung(y,buffer,0,x0,y0,x1,y1,c,pi0,pi1,pi2,sel);
                                                                   if(c>0){
                                                                    //veraendern(true);//pchanged=true;
                                                                    if(c==1){//---------------------------------------------------------------------------zeile mitten 
                                                                     if(sel[0]){
                                                                      it->loeschenmarkiert=1;
                                                                      change=true;
                                                                     };
                                                                    }else
                                                                    if(c==2){
                                                                     if(sel[0]){//--------------------------------------------------------------------zeile kante unten
                                                                     if(pprotocolmode==false){
                                                                       _typtext cc;
                                                                       _zeichenkette<_typtext> hh="";
                                                                       cc=*pi1;
                                                                       *pi1=0;
                                                                       hh=pi0;
                                                                       *pi1=cc;
                                                                       if(prot){
                                                                        new _textbufferprotokollknotenmulti<_typtext,_typoptik>(prot,false,0,y,hh);
                                                                       }else{
                                                                        prot=erzeugenprotokollmulti(false,0,y,hh);
                                                                       };
                                                                      };
                                                                      s->aushaengen(0,int(pi1)-int(pi0));
                                                                      untenkante=it;
                                                                      change=true;
                                                                     }else
                                                                     if(sel[1]){//-----------------------------------------------------------------------zeile kante oben
                                                                      if(pprotocolmode==false){
                                                                       _zeichenkette<_typtext> hh="";
                                                                       hh=pi1;
                                                                       if(prot){
                                                                        new _textbufferprotokollknotenmulti<_typtext,_typoptik>(prot,false,x0,y,hh);
                                                                       }else{
                                                                        prot=erzeugenprotokollmulti(false,x0,y,hh);
                                                                       };
                                                                      };
                                                                      s->aushaengen(int(pi1)-int(pi0),s->groesse()-(int(pi1)-int(pi0)));
                                                                      obenkante=it;
                                                                      change=true;
                                                                     };
                                                                    }else
                                                                    if(c==3){//--------------------------------------------------------------------------zeile innerhalb
                                                                     if(sel[1]){
                                                                      if(pprotocolmode==false) {
                                                                       _zeichenkette<_typtext> h="";
                                                                       _typtext*hh=new _typtext[(x1-x0)+4];
                                                                       _typtext*hhit=hh;
                                                                       _typtext*ppit=pi1;
                                                                       while(ppit!=pi2) *hhit++=*ppit++;
                                                                       *hhit=0;
                                                                       h=hh;
                                                                       erzeugenprotokollmulti(false,x0,y0,h);
                                                                       delete[] hh;
                                                                      };
                                                                      s->aushaengen(int(pi1)-int(pi0),int(pi2)-int(pi1));
                                                                      change=true;
                                                                     };
                                                                    };
                                                                   };
                                                                  };
                                                                  neufirst=0;
                                                                  if(plist.erstes->loeschenmarkiert==1){
                                                                   if(plist.anfang(eit))do{
                                                                    if(eit->loeschenmarkiert==0) if(neufirst==0) neufirst=eit; 
                                                                   }while(plist.naechstes(eit));
                                                                   //if(neufirst==0)//es soll jede zeile gelöscht werden
                                                                  };
                                                                  y=y0;
                                                                  countdestruction=0;
                                                                  if(plist.anfang(eit))do{
                                                                   if(eit->loeschenmarkiert==1){
                                                                    countdestruction++;   
                                                                    if(pprotocolmode==false){
                                                                     if(prot){
                                                                      new _textbufferprotokollknotenzeile<_typtext,_typoptik>(prot,false,holenposition(eit),*eit->objekt);   
                                                                     }else{
                                                                      prot=erzeugenprotokollzeile(false,holenposition(eit),*eit->objekt);
                                                                     };
                                                                    };
                                                                   };
                                                                  }while(plist.vorheriges(eit));
                                                                  
                                                                  plist.loeschenmarkiert();
                                                                  if(plist.erstes==0) {
                                                                   plist.einhaengen(new _zeichenkette<_typtext>(""));
                                                                  }else{
                                                                   if(neufirst) plist.erstes=neufirst;
                                                                  };
                                                                  
                                                                  if(obenkante){
                                                                   if(untenkante){
                                                                    if(pprotocolmode==false){
                                                                     if(prot){
                                                                      new _textbufferprotokollknotenmulti<_typtext,_typoptik>(prot,true,x0,y0,*untenkante->objekt);
                                                                      new _textbufferprotokollknotenzeile<_typtext,_typoptik>(prot,false,y1-countdestruction,*untenkante->objekt);
                                                                      //peep(1000);
                                                                     }else{
                                                                      prot=erzeugenprotokollmulti(true,x0,y0,*untenkante->objekt);
                                                                      new _textbufferprotokollknotenzeile<_typtext,_typoptik>(prot,false,y1-countdestruction,*untenkante->objekt);
                                                                     };
                                                                    };
                                                                    obenkante->objekt->anhaengen(untenkante->objekt);
                                                                    delete untenkante->objekt;
                                                                    delete untenkante;
                                                                   };
                                                                  };
                                                                  if(change) veraendern(true);
                                                                  anwahlloeschen();
                                                                 };
                                                                };
};
template<class _typtext,class _typoptik> void _textbuffer<_typtext,_typoptik>::anwahlfrontleerraumsetzen(int i){
                                                                int y,c,n,d;
                                                                int x0,y0,x1,y1;
                                                                _listenknoten<_zeichenkette<_typtext> >*it;
                                                                _zeichenkette<_typtext> h;
                                                                _textbufferprotokoll<_typtext,_typoptik>*prot;
                                                                //----------
                                                                if(preadonly==false){
                                                                 if(anwahlholen(x0,y0,x1,y1)){
                                                                  prot=0;
                                                                  holenzeile(y0,it);
                                                                  if(x1==0) y1--;
                                                                  for(y=y0;y<=y1;y++){
                                                                   c=it->objekt->anzahlfrontleerzeichen();
                                                                   h="";
                                                                   d=i-c;
                                                                   if(d!=0){
                                                                    for(n=0;n<abs(d);n++) h+=" ";
                                                                    if(d>0){
                                                                     it->objekt->einhaengen(h,0);
                                                                     if(pprotocolmode==false) {
                                                                      if(prot==0) prot=erzeugenprotokollmulti(true,0,y,h); 
                                                                      else new _textbufferprotokollknotenmulti<_typtext,_typoptik>(prot,true,0,y,h);
                                                                     };
                                                                    }else if(d<0){
                                                                     it->objekt->aushaengen(0,h.groesse());
                                                                     if(pprotocolmode==false) {
                                                                      if(prot==0) prot=erzeugenprotokollmulti(false,0,y,h); 
                                                                      else new _textbufferprotokollknotenmulti<_typtext,_typoptik>(prot,false,0,y,h);
                                                                     };
                                                                    };
                                                                   };
                                                                   it=it->naechstes;
                                                                  };
                                                                  veraendern(true);
                                                                 };
                                                                };
};
template<class _typtext,class _typoptik> void _textbuffer<_typtext,_typoptik>::anwahlfrontleerraumeinfuegen(){
                                                                int y;
                                                                int x0,y0,x1,y1;
                                                                _listenknoten<_zeichenkette<_typtext> >*it;
                                                                _typtext b[2]={32,0};
                                                                _textbufferprotokoll<_typtext,_typoptik>*prot;
                                                                //----------
                                                                if(preadonly==false){
                                                                 if(anwahlholen(x0,y0,x1,y1)){
                                                                  prot=0;
                                                                  holenzeile(y0,it);
                                                                  if(x1==0) y1--;
                                                                  for(y=y0;y<=y1;y++){
                                                                   it->objekt->einhaengen(b,0);
                                                                   if(pprotocolmode==false) {
                                                                    if(prot==0) prot=erzeugenprotokolleinzel(true,0,y,32); 
                                                                    else new _textbufferprotokollknoteneinzel<_typtext,_typoptik>(prot,true,0,y,32);
                                                                   };
                                                                   it=it->naechstes;
                                                                  };
                                                                 veraendern(true);
                                                                 };
                                                                };
};
template<class _typtext,class _typoptik> void _textbuffer<_typtext,_typoptik>::anwahlfrontleerraumentfernen(){
                                                                int y;
                                                                int x0,y0,x1,y1;
                                                                _listenknoten<_zeichenkette<_typtext> >*it;
                                                                _textbufferprotokoll<_typtext,_typoptik>*prot;
                                                                //----------
                                                                if(preadonly==false){
                                                                 if(anwahlholen(x0,y0,x1,y1)){
                                                                  prot=0;
                                                                  holenzeile(y0,it);   
                                                                  if(x1==0) y1--;
                                                                  for(y=y0;y<=y1;y++){
                                                                   if(it->objekt->holen(0)==32) {
                                                                    it->objekt->aushaengen(0,1);   
                                                                    if(pprotocolmode==false) {
                                                                     if(prot==0) prot=erzeugenprotokolleinzel(false,0,y,32); 
                                                                     else new _textbufferprotokollknoteneinzel<_typtext,_typoptik>(prot,false,0,y,32);
                                                                    };
                                                                   };//aushaengen(0,y,1);
                                                                   it=it->naechstes;
                                                                  };
                                                                 veraendern(true);
                                                                 };
                                                                };
};
template<class _typtext,class _typoptik> void _textbuffer<_typtext,_typoptik>::anwahlendleerraumentfernen(){
                                                                int y;
                                                                int x0,y0,x1,y1;
                                                                int d0;
                                                                _zeichenkette<_typtext> h;
                                                                _listenknoten<_zeichenkette<_typtext> >*it;
                                                                _textbufferprotokoll<_typtext,_typoptik>*prot;
                                                                //----------
                                                                if(preadonly==false){
                                                                 if(anwahlholen(x0,y0,x1,y1)){
                                                                  prot=0;
                                                                  holenzeile(y0,it);   
                                                                  if(x1==0) y1--;
                                                                  for(y=y0;y<=y1;y++){
                                                                   if(it->objekt->entfernenendleerzeichen(d0,h)){   
                                                                    if(pprotocolmode==false) {
                                                                     if(prot==0) prot=erzeugenprotokollmulti(false,d0,y,h); 
                                                                     else new _textbufferprotokollknotenmulti<_typtext,_typoptik>(prot,false,d0,y,h);
                                                                    };
                                                                   };
                                                                   it=it->naechstes;
                                                                  };
                                                                 veraendern(true);
                                                                 };
                                                                };
};
template<class _typtext,class _typoptik> void _textbuffer<_typtext,_typoptik>::anwahltabulatorenersetzen(_zeichenkette<_typtext>&rs){
                                                                int y;
                                                                int x0,y0,x1,y1;
                                                                _zeichenkette<_typtext> h;
                                                                _listenknoten<_zeichenkette<_typtext> >*it;
                                                                _textbufferprotokoll<_typtext,_typoptik>*prot;
                                                                _zeichenkette<_typtext> old;
                                                                //----------
                                                                if(preadonly==false){
                                                                 if(anwahlholen(x0,y0,x1,y1)){
                                                                  prot=0;
                                                                  holenzeile(y0,it);
                                                                  if(x1==0) y1--;
                                                                  for(y=y0;y<=y1;y++){
                                                                   old=*it->objekt;   
                                                                   if(it->objekt->replacetabulator(rs)){   
                                                                    if(pprotocolmode==false) {
                                                                     if(prot==0) {
                                                                      prot=erzeugenprotokollzeile(false,y,old);
                                                                      new _textbufferprotokollknotenzeile<_typtext,_typoptik>(prot,true,y,*it->objekt);
                                                                     }else{
                                                                      new _textbufferprotokollknotenzeile<_typtext,_typoptik>(prot,false,y,old);
                                                                      new _textbufferprotokollknotenzeile<_typtext,_typoptik>(prot,true,y,*it->objekt);
                                                                     };
                                                                    };
                                                                   };
                                                                   it=it->naechstes;
                                                                  };
                                                                 veraendern(true);
                                                                 };
                                                                };
};
template<class _typtext,class _typoptik> void _textbuffer<_typtext,_typoptik>::anwahlkopieren(_textbuffer<_typtext,_typoptik>*tb){
                                                                int y;
                                                                _zeichenkette<_typtext>*s;
                                                                _listenknoten<_zeichenkette<_typtext> >*it;
                                                                _typtext buffer[8192];
                                                                _typtext*b;
                                                                _typtext h;
                                                                int c;
                                                                int x0,y0,x1,y1;
                                                                _typtext*pi0;
                                                                _typtext*pi2;
                                                                _typtext*pi1;
                                                                bool sel[3];
                                                                _typtext eol[2]={10,0};
                                                                _zeichenkette<_typtext>*n;
                                                                //----------
                                                                if(anwahlholen(x0,y0,x1,y1)){
                                                                 tb->loeschen();
                                                                 for(y=y0;y<=y1;y++){
                                                                  s=&holenzeile(y,it);
                                                                  s->holen(buffer,8192);
                                                                  c=0;
                                                                  anwahlteilung(y,buffer,0,x0,y0,x1,y1,c,pi0,pi1,pi2,sel);
                                                                  if(c>0){
                                                                   if(c==1){//---------------------------------------------------------------------------zeile mitten 
                                                                    if(sel[0]){
                                                                     n=tb->anhaengen(buffer);
                                                                     n->anhaengen(eol);
                                                                    };
                                                                   }else
                                                                   if(c==2){
                                                                    if(sel[0]){//--------------------------------------------------------------------zeile kante unten
                                                                     b=buffer;
                                                                     h=*pi1;
                                                                     *pi1=0;
                                                                     tb->anhaengen(b);
                                                                     *pi1=h;
                                                                    }else
                                                                    if(sel[1]){//-----------------------------------------------------------------------zeile kante oben
                                                                     b=pi1;//buffer;
                                                                     n=tb->anhaengen(b);
                                                                     if(y0!=y1){
                                                                      n->anhaengen(eol);
                                                                     };
                                                                    };
                                                                   }else
                                                                   if(c==3){//--------------------------------------------------------------------------zeile innerhalb
                                                                    if(sel[1]){
                                                                     b=pi1;
                                                                     h=*pi2;
                                                                     *pi2=0;
                                                                     tb->anhaengen(b);
                                                                     *pi2=h;
                                                                    };
                                                                   };
                                                                  };
                                                                 };
                                                                };
};
template<class _typtext,class _typoptik> int _textbuffer<_typtext,_typoptik>::anzahlfrontleerzeichen(_zeichenkette<_typtext>&s){
                                                                int i;
                                                                //--------
                                                                i=0;
                                                                while(s[i]==' ') i++;
                                                                return(i);
};
#endif
