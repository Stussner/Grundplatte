//grundplatte : _editionwindows.hpp
//#pragma once
template<class _tg=typgeometrie> class _guirechteck;
template<class _tg=typgeometrie> class _guivektor;
template<class _tg=typgeometrie> class _guiort;
template<class _tg=typgeometrie> class _guigroesse;
class _guikonfiguration;
class _guiobjekt;
struct _guiereignismaus;
struct _guiereigniszeichnung;
struct _guiereignisdrop;
struct _guiereignisdaten;
class _guiereignis;
template <class T> class _guiereignistemplate;
class _guikontext;
class _guiuhr;
class _guiaccelerator;
class _guiacceleratortabelle;
class _guimenueeintrag;
class _guimenue;
class _guimenuebasis;
class _guimenueleiste;
class _guiknopf;
class _guiknopfcheckbasis;
class _guiknopfchecklinks;
class _guiknopfcheckrechts;
class _guiknopfdruck;
class _guiknopfradio;
class _guidialog;
class _guieditierbar;
class _guieditierbarsektion;
class _guidialogeditierbar;
class _guidialogdatei;
class _guidialogmodal;
class _guifenster;
class _guifensterkind;
class _guifensterhaupt;
class _guifenstersplash;
class _guifensterstatischbasis;
class _guifensterstatischlinks;
class _guifensterstatischrechts;
class _guifensterstatischzentriert;
class _guifensterkartei;
class _guifensterkarteiseite;
class _guifensterwerkzeug;
class _guitextfeldbasis;
class _guitextfeld;
class _guitextfeldmulti;
class _guicombobox;
class _guilistbox;
class _guiscrollbarbasis;
class _guiscrollbarvertikal;
class _guiscrollbarhorizontal;
class _guiteilerbasis;
class _guiteilerhorizontal;
class _guiteilervertikal;
class _guistatusleiste;
class _guiwerkzeugleiste;
class _guiwerkzeugleisteknopf;
template <class T> class _guibaumbox;
template <class T> class _guibaumboxast;
template <class T> class _guibaumboxeintrag;
template <class T> class _guibaumboxeintragbasis;

class _editionskopplung;
class _editionskopplungort;
class _editionskopplungvektor;
class _editionskopplungdialog;
class _dialogbesitzeraktualisierung;
class _dynamischerdialog;
class _editierbar;

#ifndef _editinionwindows_included
#define _editinionwindows_included
#include <_global.hpp>
#ifdef GRUNDPLATTE_UNTER_WINDOWS





#include <_struktur.hpp>
#include <_vektor.hpp>
#include <_text.hpp>
#include <_edition.hpp>
#include <_grafik.hpp>
#define WIN32_LEAN_AND_MEAN
//#include <windows.h>
#include <windowsx.h>
#include <zmouse.h>
#include <commctrl.h>
#include <commdlg.h>
//#include <resource.h>
#include <vector>



//using namespace GUI;
//#include <BCGUI/gui.hpp>
//#include <BCGUI/menu.hpp>
//#include <BCGUI/Dialogs/editabledialog.hpp>
//#include <BCGUI/Controls/statusbar.hpp>
//#include <BCGUI/Controls/toolbar.hpp>
//#include <BCGUI/Windows/tabwindow.hpp>
//#include <BCGUI/Windows/childwindow.hpp>
//#include <BCGUI/Controls/splitter.hpp>
//#include <BCGUI/rectangle.hpp>
//#include <BCGUI/hdc.hpp>
//#include <BCCore/Core.hpp>


#define HEIGHT_COMBOBOX  300
#define OBJECT_STARTID  1000
#define OBJECT_MAXID   30000
#define PERCENT_DESCRIPTION 0.4
#define HEIGHT_EDITABLE  20
#define SPACE_EDITABLE   15

T_String<wchar_t> ANSIToUnicode(T_String<char> const &ansi);
T_String<char> UnicodeToANSI(T_String<wchar_t> const &unicode);
T_String<wchar_t> UTF8ToUnicode(T_String<char> const &utf8);
T_String<wchar_t> UTF8ToUnicode(T_String<wchar_t> const &utf8);
T_String<char> UnicodeToUTF8(T_String<wchar_t> const &unicode);
T_String<char> UnicodeToUTF8(T_String<char> const &unicode);
/*
 // GDI-Stuff 
class _guigdiobjekt 
{ 
   public: 
     _guigdiobjekt() : pobj(0)  { } 
     virtual ~_guigdiobjekt()   { if(pobj) DeleteObject(pobj); } 
      
     HGDIOBJ objekt()           { return(pobj); } 
      
      
   protected: 
     HGDIOBJ  pobj; 
}; 
 
class _guistift : public _guigdiobjekt 
{ 
   public: 
     _guistift(unsigned char r, unsigned char g, unsigned char b); 
}; 
_guistift::_guistift(unsigned char r, unsigned char g, unsigned char b) 
{ 
   pobj = CreatePen(PS_SOLID, 1, RGB(r, g, b)); 
} 
 
class _guipinsel : public _guigdiobjekt 
{ 
   public: 
     _guipinsel(unsigned char r, unsigned char g, unsigned char b); 
}; 
_guipinsel::_guipinsel(unsigned char r, unsigned char g, unsigned char b) 
{ 
   pobj = CreateSolidBrush(RGB(r, g, b)); 
}*/
//******************************************************************************************************************************************************************************************************
//                                                              G U I R E C H T E C K 
//******************************************************************************************************************************************************************************************************
template <class _tg> class _guirechteck{
    public:
                _guirechteck(_tg left = 0, _tg top = 0, _tg right = 0, _tg bottom = 0);
                virtual ~_guirechteck();
                _tg links() const;
                _tg oben() const;
                _tg rechts() const;
                _tg unten() const;
                _tg breite() const;
                _tg hoehe() const;
                void setzen(_tg left,_tg top,_tg right,_tg bottom);
                void lesen(RECT*rect);
                _guirechteck<_tg> operator +(_guirechteck<_tg> const &other) const;  // Gibt das kleinste Rechteck zurück in welches beide Rechtecke passen (Union)
                _guirechteck<_tg> operator -(_guirechteck<_tg> const &other) const;  // Gibt das Rechteck zurück, welches in Beiden liegt (Difference)
    private:
                _tg pleft,ptop,pright,pbottom;
};
template <class _tg> _guirechteck<_tg>::_guirechteck(_tg left, _tg top, _tg right, _tg bottom){
                                                                setzen(left, top, right, bottom);
};
template <class _tg> _guirechteck<_tg>::~_guirechteck(){
};
template <class _tg> _tg _guirechteck<_tg>::links() const{
                                                                return(pleft);
};
template <class _tg> _tg _guirechteck<_tg>::oben() const{
                                                                return(ptop);
};
template <class _tg> _tg _guirechteck<_tg>::rechts() const{
                                                                return(pright);
};
template <class _tg> _tg _guirechteck<_tg>::unten() const{
                                                                return(pbottom);
};
template <class _tg> _tg _guirechteck<_tg>::breite() const{
                                                                return(pright - pleft);
};
template <class _tg> _tg _guirechteck<_tg>::hoehe() const{
                                                                return(pbottom - ptop);
};
template <class _tg> void _guirechteck<_tg>::setzen(_tg left,_tg top,_tg right,_tg bottom){
                                                                //Setzt das Rechteck
                                                                pleft = min(left, right);
                                                                ptop = min(top, bottom);
                                                                pright = max(left, right);
                                                                pbottom = max(top, bottom);
};

template <class _tg> void _guirechteck<_tg>::lesen(RECT*rect){
                                                                //Kopiert das Rechteck in eine Struktur für Windoze
                                                                rect->left   = (LONG)pleft;
                                                                rect->top    = (LONG)ptop;
                                                                rect->right  = (LONG)pright;
                                                                rect->bottom = (LONG)pbottom;
};

template <class _tg> _guirechteck<_tg> _guirechteck<_tg>::operator +(_guirechteck<_tg> const &other) const{
                                                                //Gibt das kleinste Rechteck zurück in welches beide Rechtecke passen (Union)
                                                                _tg min[2],max[2];
                                                                min[0] = min(pleft, other.links());
                                                                min[1] = min(ptop, other.oben());
                                                                max[0] = max(pright, other.rechts());
                                                                max[1] = max(pbottom, other.unten());
                                                                return(_guirechteck<_tg>(min[0], min[1], max[0], max[1]));
};
template <class _tg> _guirechteck<_tg> _guirechteck<_tg>::operator -(_guirechteck<_tg> const &other) const{
                                                                //Gibt das Rechteck zurück, welches in Beiden liegt (Difference)
                                                                if(pright < other.links() || pleft > other.rechts() || pbottom < other.oben() || ptop > other.unten()) return(_guirechteck<_tg>(0, 0, 0, 0));
                                                                throw "_guirechteck<_tg>::operator -(_guirechteck<_tg> const &other) const -> FIXME: Implement";
};
//******************************************************************************************************************************************************************************************************
//                                                              G L O B A L E   T E M P L A T E S und F U N K T I O N E N
//******************************************************************************************************************************************************************************************************
template <class _tg> _guirechteck<_tg> DesktopRect(bool includetaskbar=false){
                                                                //Gibt die Größe des Desktops zurück
                                                                RECT rect;
                                                                if(includetaskbar)
                                                                 GetWindowRect(GetDesktopWindow(), &rect);
                                                                else
                                                                 SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, 0);
                                                                return(_guirechteck<_tg>((_tg)rect.left,(_tg)rect.top,(_tg)rect.right,(_tg)rect.bottom));
};
//void guishellcommand(T_String<> const &command, T_String<> const &file);
void guifensterhaupt(_guifensterhaupt*window);
void guianimieren();
void guiinitialisieren(_guikonfiguration*config);
void guideinitialisieren();
void guifehler();  // Bei einem Fehler werden keine Nachrichten mehr von uns verarbeitet
_guifenster*findenfenster(HWND handle);
unsigned int nachricht(T_String<> const &text, T_String<> const &title = L"Info", unsigned int flags = MB_OK);  // Nachricht ausgeben
unsigned int nachricht(_streamwide const &text, unsigned int flags = MB_OK);
unsigned int nachricht(_streamwide const &text, _streamwide const &title, unsigned int flags = MB_OK);
//******************************************************************************************************************************************************************************************************
//                                                              G U I K O N F I G U R A T I O N
//******************************************************************************************************************************************************************************************************
class _guikonfiguration{
    public:
                _guikonfiguration();
                virtual ~_guikonfiguration();
    public:
                unsigned int icon;
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I V E K T O R 
//******************************************************************************************************************************************************************************************************
template <class _tg> class _guivektor{
    public:
                _guivektor(_tg x=0,_tg y=0,bool a=true);
                virtual ~_guivektor();
                _tg x()const;
                _tg y()const;
                bool absolut();
    private:
                _tg px,py;
                bool pabsolut; //Wenn false, dann geht die Position und Größe von 0-1 (vom Parent aus gesehen)
};
template <class _tg> _guivektor<_tg>::_guivektor(_tg x,_tg y,bool a){
                                                                px=x;
                                                                py=y;
                                                                pabsolut=a;
};
template <class _tg> _guivektor<_tg>::~_guivektor(){

};
template <class _tg> _tg _guivektor<_tg>::x()const{
                                                                return(px);
};
template <class _tg> _tg _guivektor<_tg>::y()const{
                                                                return(py);
};
template <class _tg> bool _guivektor<_tg>::absolut(){
                                                                return(pabsolut);
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I O R T 
//******************************************************************************************************************************************************************************************************
template <class _tg> class _guiort:public _guivektor<_tg>,public _listenknotenbasis<_guiort<_tg> >{
    public:
                _guiort(_tg x=0,_tg y=0,bool a=true);
                virtual ~_guiort();
};
template <class _tg> _guiort<_tg>::_guiort(_tg x,_tg y,bool a):_guivektor<_tg>(x,y,a){
};
template <class _tg> _guiort<_tg>::~_guiort(){

};
//******************************************************************************************************************************************************************************************************
//                                                              G U I G R O E S S E 
//******************************************************************************************************************************************************************************************************
template <class _tg> class _guigroesse:public _guivektor<_tg>,public _listenknotenbasis<_guigroesse<_tg> >{
    public:
                _guigroesse(_tg x=0,_tg y=0,bool a=true);
                virtual ~_guigroesse();
                _tg breite()const;
                _tg hoehe()const;
};
template <class _tg> _guigroesse<_tg>::_guigroesse(_tg x,_tg y,bool a):_guivektor<_tg>(x,y,a){
};
template <class _tg> _guigroesse<_tg>::~_guigroesse(){

};
template <class _tg> _tg _guigroesse<_tg>::breite()const{
                                                                return(x());
};
template <class _tg> _tg _guigroesse<_tg>::hoehe()const{
                                                                return(y());
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I E R E I G N I S M A U S 
//******************************************************************************************************************************************************************************************************
struct _guiereignismaus{
                int x,y;
                int zDelta;
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I E R E I G N I S Z E I C H N U N G 
//******************************************************************************************************************************************************************************************************
struct _guiereigniszeichnung{
                HDC hdc;
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I E R E I G N I S D R O P 
//******************************************************************************************************************************************************************************************************
struct _guiereignisdrop{
                wchar_t fileName[1024];  //FIXME: Liste...
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I E R E I G N I S D A T E N
//******************************************************************************************************************************************************************************************************
struct _guiereignisdaten{
                _guifenster*fenster;
                _guiobjekt*objekt;
                _guiereignismaus maus;
                _guiereignisdrop drop;
                _guiereigniszeichnung zeichnung;
                _liste<_guiobjekt>*objektezumloeschen;
                WPARAM wParam;
                LPARAM lParam;
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I E R E I G N I S  (abstrakte Basisklasse für Events)
//******************************************************************************************************************************************************************************************************
class _guiereignis: public _listenknotenbasis<_guiereignis>{
                friend void bearbeitenereignisse(_guiobjekt*object,_listebasis<_guiereignis>*list, _guiereignisdaten*params);
    public:
                _guiereignis()           { memset(&ped, 0, sizeof(_guiereignisdaten)); };
                virtual ~_guiereignis()  {  };
    private:
                void setzen(_guiereignisdaten*ep)  {memcpy(&ped,ep,sizeof(_guiereignisdaten)); };
                virtual void ausfuehren()=0;
    protected:
                _guiereignisdaten ped;  // Brauchen wir selber, da bei der anderen Methode anscheinend irgendwas schiefgeht
};

//******************************************************************************************************************************************************************************************************
//                                                              G U I E R E I G N I S T E M P L A T E
//******************************************************************************************************************************************************************************************************
template <class T> class _guiereignistemplate:public _guiereignis{
    protected:
                typedef void (T::*mfp)(_guiereignisdaten*);
    public:
                _guiereignistemplate(T *c, mfp f) { 
                                                                pclass = c; 
                                                                pfunc = f; 
                                                                };
                virtual ~_guiereignistemplate() { };
    private:
                void ausfuehren()  { 
                                                                if(pclass && pfunc) (pclass->*pfunc)(&ped); 
                                                                };
    private:
                T*pclass;
                mfp pfunc;
};
//******************************************************************************************************************************************************************************************************
//                                                              M A K R O   E R E I G N I S S E 
//******************************************************************************************************************************************************************************************************
#define IMPLEMENT_BCGUIEVENT(__name) \
   template <class T> class _guiereignis##__name : public _guiereignistemplate<T> \
   { \
      public: \
        _guiereignis##__name(T *c, mfp f) : _guiereignistemplate<T>(c, f)  {  } \
        virtual ~_guiereignis##__name()  {  } \
   }
// end IMPLEMENT_BCGUIEVENT

IMPLEMENT_BCGUIEVENT(Create);
IMPLEMENT_BCGUIEVENT(MouseMove);
IMPLEMENT_BCGUIEVENT(LeftButtonDown);
IMPLEMENT_BCGUIEVENT(LeftButtonUp);
IMPLEMENT_BCGUIEVENT(LeftButtonDoubleClick);
IMPLEMENT_BCGUIEVENT(RightButtonDown);
IMPLEMENT_BCGUIEVENT(RightButtonUp);
IMPLEMENT_BCGUIEVENT(RightButtonDoubleClick);
IMPLEMENT_BCGUIEVENT(MiddleButtonDown);
IMPLEMENT_BCGUIEVENT(MiddleButtonUp);
IMPLEMENT_BCGUIEVENT(MiddleButtonDoubleClick);
IMPLEMENT_BCGUIEVENT(MouseWheel);
IMPLEMENT_BCGUIEVENT(KeyDown);
IMPLEMENT_BCGUIEVENT(KeyUp);
IMPLEMENT_BCGUIEVENT(Size);
IMPLEMENT_BCGUIEVENT(EraseBackground);
IMPLEMENT_BCGUIEVENT(Paint);
IMPLEMENT_BCGUIEVENT(Command);
IMPLEMENT_BCGUIEVENT(SelectionChange);  // für Tabfenster
IMPLEMENT_BCGUIEVENT(DropFiles);
IMPLEMENT_BCGUIEVENT(Timer);
IMPLEMENT_BCGUIEVENT(Close);
IMPLEMENT_BCGUIEVENT(Minimize);
IMPLEMENT_BCGUIEVENT(Maximize);
IMPLEMENT_BCGUIEVENT(Destroy);


//******************************************************************************************************************************************************************************************************
//                                                              G U I O B J E K T 
//******************************************************************************************************************************************************************************************************
class _guiobjekt: public _listelistenknotenbasis<_guiobjekt>,protected _listebasis<_guiort<_tg> >,protected _listebasis<_guigroesse<_tg> >{
    friend static LRESULT WINAPI WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    friend static LRESULT WINAPI EditSubProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
    public:
                _guiobjekt(T_String<> const &pn, _guiobjekt*parent = 0);
                virtual ~_guiobjekt();
     
                template <class T> T*Cast(bool generateError=true);
                unsigned int id() const;
                T_String<>name();
                virtual void name(T_String<> const &pn);  // Kann z.B. für Fenster überladen werden wenn man den Text für ein Fenster oder ähnliches ändern muss
                virtual T_String<>hilfe();
                virtual void bewegen();  // Für Dialoge
                virtual void skalieren();
     
                virtual void vorbereitenereignisse(_guiereignisdaten *ep){ };
                virtual void nachbereitenereignisse(_guiereignisdaten *ep){ };
     
                void operator+=(_guiort<_tg>*pos);
                void operator+=(_guigroesse<_tg>*size);
     
                // Funktionen zum Einhängen von Event-Handlern
                template <class T> void operator+=(_guiereignisMouseMove<T> *event);
                template <class T> void operator+=(_guiereignisLeftButtonDown<T> *event);
                template <class T> void operator+=(_guiereignisLeftButtonUp<T> *event);
                template <class T> void operator+=(_guiereignisLeftButtonDoubleClick<T> *event);
                template <class T> void operator+=(_guiereignisRightButtonDown<T> *event);
                template <class T> void operator+=(_guiereignisRightButtonUp<T> *event);
                template <class T> void operator+=(_guiereignisRightButtonDoubleClick<T> *event);
                template <class T> void operator+=(_guiereignisMiddleButtonDown<T> *event);
                template <class T> void operator+=(_guiereignisMiddleButtonUp<T> *event);
                template <class T> void operator+=(_guiereignisMiddleButtonDoubleClick<T> *event);
                template <class T> void operator+=(_guiereignisMouseWheel<T> *event);
                template <class T> void operator+=(_guiereignisKeyDown<T> *event);
                template <class T> void operator+=(_guiereignisKeyUp<T> *event);
                template <class T> void operator+=(_guiereignisSize<T> *event);
                template <class T> void operator+=(_guiereignisEraseBackground<T> *event);
                template <class T> void operator+=(_guiereignisPaint<T> *event);
                template <class T> void operator+=(_guiereignisCommand<T> *event);
                template <class T> void operator+=(_guiereignisSelectionChange<T> *event);
                template <class T> void operator+=(_guiereignisDropFiles<T> *event);
                template <class T> void operator+=(_guiereignisTimer<T> *event);
                template <class T> void operator+=(_guiereignisClose<T> *event);
                template <class T> void operator+=(_guiereignisMinimize<T> *event);
                template <class T> void operator+=(_guiereignisMaximize<T> *event);
                template <class T> void operator+=(_guiereignisDestroy<T> *event);
   
    private:
                // Alle Aufrufe die durch die Nachrichtenprozedur kommen können
                _listebasis<_guiereignis> pmouseMoveEvents;
                _listebasis<_guiereignis> pleftButtonDownEvents;
                _listebasis<_guiereignis> pleftButtonUpEvents;
                _listebasis<_guiereignis> pleftButtonDoubleClickEvents;
                _listebasis<_guiereignis> prightButtonDownEvents;
                _listebasis<_guiereignis> prightButtonUpEvents;
                _listebasis<_guiereignis> prightButtonDoubleClickEvents;
                _listebasis<_guiereignis> pmiddleButtonDownEvents;
                _listebasis<_guiereignis> pmiddleButtonUpEvents;
                _listebasis<_guiereignis> pmiddleButtonDoubleClickEvents;
                _listebasis<_guiereignis> pmouseWheelEvents;
                _listebasis<_guiereignis> pkeyDownEvents;
                _listebasis<_guiereignis> pkeyUpEvents;
                _listebasis<_guiereignis> psizeEvents;
                _listebasis<_guiereignis> peraseBackgroundEvents;
                _listebasis<_guiereignis> ppaintEvents;
                _listebasis<_guiereignis> pcommandEvents;
                _listebasis<_guiereignis> pselectionChangeEvents;  // Für Tabfenster
                _listebasis<_guiereignis> pdropFilesEvents;  // Drag & Drop
                _listebasis<_guiereignis> ptimerEvents;
                _listebasis<_guiereignis> pcloseEvents;
                _listebasis<_guiereignis> pminimizeEvents;
                _listebasis<_guiereignis> pmaximizeEvents;
                _listebasis<_guiereignis> pdestroyEvents;
    protected:
                unsigned int pid;  // ID des Objekts (für WM_COMMAND z.B.)
                T_String<> pname;  // Name des Objekts (Unicode)
};


template <class T> T *_guiobjekt::Cast(bcBool generateError){
                                                                //Castet das Objekt (wenn generateError == true, dann wird eine Exception geschmissen)
                                                                T*dest=dynamic_cast<T*>(this);
                                                                if(generateError && !dest) throw L"_guiobjekt::Cast(" + name() + L") -> Could not cast to destination-type!";
                                                                return(dest);
};
template <class T> void _guiobjekt::operator += (_guiereignisMouseMove<T> *e){
                                                                //Fügt einen neuen Handler hinzu (WM_MOUSEMOVE)
                                                                e->einhaengen(&pmouseMoveEvents);
};
template <class T> void _guiobjekt::operator += (_guiereignisLeftButtonDown<T> *e){
                                                                //Fügt einen neuen Handler hinzu (WpLBUTTONDOWN)
                                                                e->einhaengen(&pleftButtonDownEvents);
};
template <class T> void _guiobjekt::operator += (_guiereignisLeftButtonUp<T> *e){
                                                                //Fügt einen neuen Handler hinzu (WpLBUTTONUP)
                                                                e->einhaengen(&pleftButtonUpEvents);
};
template <class T> void _guiobjekt::operator += (_guiereignisLeftButtonDoubleClick<T> *e){
                                                                //Fügt einen neuen Handler hinzu (WpLBUTTONDBLCLK)
                                                                e->einhaengen(&pleftButtonDoubleClickEvents);
};
template <class T> void _guiobjekt::operator += (_guiereignisRightButtonDown<T> *e){
                                                                //Fügt einen neuen Handler hinzu (WpRBUTTONDOWN)
                                                                e->einhaengen(&prightButtonDownEvents);
};
template <class T> void _guiobjekt::operator += (_guiereignisRightButtonUp<T> *e){
                                                                //Fügt einen neuen Handler hinzu (WpRBUTTONUP)    
                                                                e->einhaengen(&prightButtonUpEvents);
};
template <class T> void _guiobjekt::operator += (_guiereignisRightButtonDoubleClick<T> *e){
                                                                //Fügt einen neuen Handler hinzu (WpRBUTTONDBLCLK)
                                                                e->einhaengen(&prightButtonDoubleClickEvents);
};
template <class T> void _guiobjekt::operator += (_guiereignisMiddleButtonDown<T> *e){
                                                                //Fügt einen neuen Handler hinzu (WpMBUTTONDOWN)
                                                                e->einhaengen(&pmiddleButtonDownEvents);
};
template <class T> void _guiobjekt::operator += (_guiereignisMiddleButtonUp<T> *e){
                                                                //Fügt einen neuen Handler hinzu (WpMBUTTONUP)
                                                                e->einhaengen(&pmiddleButtonUpEvents);
};
template <class T> void _guiobjekt::operator += (_guiereignisMiddleButtonDoubleClick<T> *e){
                                                                //Fügt einen neuen Handler hinzu (WpMBUTTONDBLCLK)
                                                                e->einhaengen(&pmiddleButtonDoubleClickEvents);
};
template <class T> void _guiobjekt::operator += (_guiereignisMouseWheel<T> *e){
                                                                //Fügt einen neuen Handler hinzu (WpMOUSEWHEEL)
                                                                e->einhaengen(&pmouseWheelEvents);
};
template <class T> void _guiobjekt::operator += (_guiereignisKeyDown<T> *e){
                                                                //Fügt einen neuen Handler hinzu (WpKEYDOWN)
                                                                e->einhaengen(&pkeyDownEvents);
};
template <class T> void _guiobjekt::operator += (_guiereignisKeyUp<T> *e){
                                                                //Fügt einen neuen Handler hinzu (WpKEYUP)
                                                                e->einhaengen(&pkeyUpEvents);
};
template <class T> void _guiobjekt::operator += (_guiereignisSize<T> *e){
                                                                //fügt einen neuen Handler hinzu (WpSIZE)
                                                                e->einhaengen(&psizeEvents);
};
template <class T> void _guiobjekt::operator += (_guiereignisEraseBackground<T> *e){
                                                                //Fügt einen neuen Handler hinzu (WpERASEBKGND)
                                                                e->einhaengen(&peraseBackgroundEvents);
};
template <class T> void _guiobjekt::operator += (_guiereignisPaint<T> *e){
                                                                //Fügt einen neuen Handler hinzu (WpPAINT)
                                                                e->einhaengen(&ppaintEvents);
};
template <class T> void _guiobjekt::operator += (_guiereignisCommand<T> *e){
                                                                //Fügt einen neuen Handler hinzu (WpCOMMAND)
                                                                e->einhaengen(&pcommandEvents);
};
template <class T> void _guiobjekt::operator += (_guiereignisSelectionChange<T> *e){
                                                                //Auswahl eines Tabfensters wurde geändert (TCN_SELCHANGE)
                                                                e->einhaengen(&pselectionChangeEvents);
};
template <class T> void _guiobjekt::operator += (_guiereignisDropFiles<T> *e){
                                                                //Drag & Drop (WpDROPFILES)    
                                                                e->einhaengen(&pdropFilesEvents);
};
template <class T> void _guiobjekt::operator += (_guiereignisTimer<T> *e){
                                                                //Fügt einen neuen Handler hinzu (WpTIMER)        
                                                                e->einhaengen(&ptimerEvents);
};
template <class T> void _guiobjekt::operator += (_guiereignisClose<T> *e){
                                                                //Fügt einen neuen Handler hinzu (WpCLOSE)
                                                                e->einhaengen(&pcloseEvents);
};
template <class T> void _guiobjekt::operator += (_guiereignisMinimize<T> *e){
                                                                //Fügt einen neuen Handler hinzu (WpMINIMIZE)
                                                                e->einhaengen(&pminimizeEvents);
};
template <class T> void _guiobjekt::operator += (_guiereignisMaximize<T> *e){
                                                                //Fügt einen neuen Handler hinzu (WpMAXIMIZE)
                                                                e->einhaengen(&pmaximizeEvents);
};
template <class T> void _guiobjekt::operator += (_guiereignisDestroy<T> *e){
                                                                //Fügt einen neuen Handler hinzu (WpDESTROY)
                                                                e->einhaengen(&pdestroyEvents);
};

//******************************************************************************************************************************************************************************************************
//                                                              G U I K O N T E X T
//******************************************************************************************************************************************************************************************************
class _guikontext{
    public:
                _guikontext(_guifenster*window);
                _guikontext(_guikontext*dc);
                virtual ~_guikontext();
                HDC kontext();
    private:
                HDC phdc;
                HWND phwnd;  // Muss gespeichert werden zum Freigeben
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I U H R
//******************************************************************************************************************************************************************************************************
class _guiuhr: public _guiobjekt{
    public:
                _guiuhr(unsigned int ms, _guifenster*window);
                virtual ~_guiuhr();
    private:
                _guifenster*pwindow;
};

//******************************************************************************************************************************************************************************************************
//                                                              G U I A C C E L E R A T O R T A B E L L E
//******************************************************************************************************************************************************************************************************
class _guiacceleratortabelle:public _guiobjekt{
    public:
                _guiacceleratortabelle(_guifensterhaupt*parent);
                virtual ~_guiacceleratortabelle();
                HACCEL tabelle();
                void erzeugentabelle();
                void operator+=(_guiaccelerator*accel);
    private:
                HACCEL phaccel;
                _liste<_guiaccelerator> plistAccelerators;
};

//******************************************************************************************************************************************************************************************************
//                                                              G U I A C C E L E R A T O R 
//******************************************************************************************************************************************************************************************************
class _guiaccelerator: public _guiobjekt{
    friend class _guiacceleratortabelle;
    public:
                template <class T> _guiaccelerator(unsigned char flags, unsigned short int vk,_guiereignisCommand<T>*ec);
                virtual ~_guiaccelerator();
    private:
                ACCEL paccel;
};
template <class T> _guiaccelerator::_guiaccelerator(unsigned char flags,unsigned short int vk,_guiereignisCommand<T> *ec):_guiobjekt(L"guiaccelerator"){
                                                                paccel.fVirt=flags|FVIRTKEY|FNOINVERT;
                                                                paccel.key=vk;
                                                                paccel.cmd=id();
                                                                *this+=ec;
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I M E N U E E I N T R A G
//******************************************************************************************************************************************************************************************************
class _guimenueeintrag:public _guiobjekt{
    friend class _guimenuebasis;
    public:
                template <class T> _guimenueeintrag(T_String<> const &pn,_guiereignisCommand<T> *ec);
                virtual ~_guimenueeintrag(){ };
                virtual void name(T_String<> const &pn);
                void gesetzt(bool check);
                bool gesetzt();
    private:
                _guimenuebasis*pmenu;  // Zum Deaktivieren usw.
};
template <class T> _guimenueeintrag::_guimenueeintrag(T_String<> const &pn,_guiereignisCommand<T>*ec):_guiobjekt(pn){
                                                                *this += ec;
} ;  

//******************************************************************************************************************************************************************************************************
//                                                              G U I M E N U E B A S I S
//******************************************************************************************************************************************************************************************************
class _guimenuebasis:public _guiobjekt{
    public:
                _guimenuebasis( T_String<>const &pn);
                virtual ~_guimenuebasis();
                HMENU handle();
                void operator += (_guimenue*menu);
                void operator += (_guimenueeintrag*item);
   protected:
                void erzeugen(bool popup);
   private:
                HMENU phandle;
};


//******************************************************************************************************************************************************************************************************
//                                                              G U I M E N U E 
//******************************************************************************************************************************************************************************************************
class _guimenue: public _guimenuebasis{
   public:
                _guimenue(T_String<> const &pn);
                virtual ~_guimenue();
                void separator();
                void popup(_guifenster*parent,int x,int y);
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I M E N U E L E I S T E
//******************************************************************************************************************************************************************************************************
class _guimenueleiste: public _guimenuebasis{
    public:
                _guimenueleiste();
                virtual ~_guimenueleiste();
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I F E N S T E R 
//******************************************************************************************************************************************************************************************************
class _guifenster:public _guiobjekt{
    friend static LRESULT WINAPI WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    public:
                _guifenster(T_String<> const &pn,_guifenster*parent=0,_guimenueleiste*menu=0);
                virtual ~_guifenster();
                HWND handle();
                _guifenster*besitzer();
                _guimenueleiste*menue();
                void menue(_guimenueleiste*menu);
                HCURSOR cursor();
                void cursor(LPCTSTR res);
                virtual void name(T_String<> const &pn);

				virtual _vektor2<unsigned int> ort() const;
                 
                unsigned int farbetext();
                void farbetext(unsigned int rgb);
                void farbetext(unsigned char r,unsigned char g,unsigned char b);
                
                void farbehintergrund(unsigned int  rgb);
                void farbehintergrund(unsigned char r,unsigned char g,unsigned char b);
                HBRUSH BackgroundBrush();
                 
                bool UseBeginPaint();
                void UseBeginPaint(bcBool use);
                 
                unsigned int stil();
                unsigned int stilerweitert();
                void stil(unsigned int style,unsigned int exstyle=0);
                void addierenstil(unsigned int style,unsigned int exstyle=0);
                void loeschenstil(unsigned int style,unsigned int exstyle=0);
                 
                void EnableDrag(bcBool enable);
                LRESULT Message(UINT message, WPARAM wParam = 0, LPARAM lParam = 0);
                 
                unsigned int breiteminimal();
                unsigned int hoeheminimal();
                void groesseminimal(_guigroesse<int> const &size);
                unsigned int breitemaximal();
                unsigned int hoehemaximal();
                void groessemaximal(_guigroesse<int> const &size);
                template <class T> _guirechteck<T> ClientRect();
                template <class T> _guirechteck<T> WindowRect();
                
                virtual void zeigen();  // virtual für Dialoge
                virtual void verstecken();  // dito

                void minimieren();
                void maximieren();
                void schliessen();
                void zerstoeren();
                void einschalten();
                void ausschalten();
                void activieren();
                bool activ();
                bool eingeschaltet();
                bool sichtbar();
                void fokus();
                bool hatfokus();
                void bewegen();  // Überladen vom Objekt
                void bewegen(int x,int y,int w,int h,bool repaint=true);
                void zentrieren(int w,int h,bool repaint=true);
                void neuzeichnen();
    protected:
                void erzeugen(unsigned int style, unsigned int exstyle=0,T_String<> const &classname=L"guiklasse");
    private:
                HWND phandle;           // Fensterhandle
                _guifenster*pparent;          // Zeiger auf Elternfenster
                _guimenueleiste*pmenu;            // Hat Zeiger auf Menü zum deaktivieren usw.
                HCURSOR pcursor;           // Cursor
                unsigned int pcolortext;        // Textfarbe
                HBRUSH pbrushBackground;  // Pinsel zum Löschen des Hintergrunds
                bool puseBeginPaint;   // BeginPaint() / EndPaint() verwenden? (Direct3D macht da Ärger, M$ I adore you...)
                _guigroesse<int> psizeMinimal;      // Minimalgröße
                _guigroesse<int> psizeMaximal;      // Maximalgröße
};
template <class T> _guirechteck<T> _guifenster::ClientRect(){
                                                                //Gibt die Größe des Client-Bereichs zurück
                                                                RECT rect;
                                                                GetClientRect(phandle, &rect);
                                                                return(_guirechteck<T>((T)rect.left, (T)rect.top, (T)rect.right, (T)rect.bottom));
};
template <class T> _guirechteck<T> _guifenster::WindowRect(){
                                                                //Gibt die Größe des gesamten Fensters zurück (inkl. Titelleiste und Rahmen)
                                                                RECT rect;
                                                                GetWindowRect(phandle, &rect);
                                                                return(_guirechteck<T>((T)rect.left, (T)rect.top, (T)rect.right, (T)rect.bottom));
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I F E N S T E R K I N D
//******************************************************************************************************************************************************************************************************
class _guifensterkind:public _guifenster{
    public:
                _guifensterkind(_guifenster*parent);
                virtual ~_guifensterkind();
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I F E N S T E R H A U P T
//******************************************************************************************************************************************************************************************************
class _guifensterhaupt:public _guifenster{
    public:
                _guifensterhaupt(T_String<> const &pn,bool keinemenueknoepfe=false,_guimenueleiste*menu=0);
                virtual ~_guifensterhaupt();
                _guiacceleratortabelle*acceleratortabelle();
    private:
                _guiacceleratortabelle*paccelTable;
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I F E N S T E R S P L A S H
//******************************************************************************************************************************************************************************************************
class _guifenstersplash:public _guifenster{
    public:
                _guifenstersplash(unsigned int bitmapid);
                virtual ~_guifenstersplash();
    private:
                void beiloeschenhintergrund(_guiereignisdaten*);
    private:
                HBITMAP pbmp;
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I F E N S T E R S T A T I S C H B A S I S 
//******************************************************************************************************************************************************************************************************
class _guifensterstatischbasis:public _guifenster{
    public:
                _guifensterstatischbasis(T_String<> const &pn,_guifenster*parent);
                virtual ~_guifensterstatischbasis();
                void zentrierentextvertikal(bool center);
};

//******************************************************************************************************************************************************************************************************
//                                                              G U I F E N S T E R S T A T I S C H L I N K S
//******************************************************************************************************************************************************************************************************
class _guifensterstatischlinks:public _guifensterstatischbasis{
    public:
                _guifensterstatischlinks(T_String<> const &pn,_guifenster*parent);
                virtual ~_guifensterstatischlinks();
};

//******************************************************************************************************************************************************************************************************
//                                                              G U I F E N S T E R S T A T I S C H R E C H T S 
//******************************************************************************************************************************************************************************************************
class _guifensterstatischrechts:public _guifensterstatischbasis{
    public:
                _guifensterstatischrechts(T_String<> const &pn,_guifenster*parent);
                virtual ~_guifensterstatischrechts();
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I F E N S T E R S T A T I S C H Z E N T R I E R T 
//******************************************************************************************************************************************************************************************************
class _guifensterstatischzentriert : public _guifensterstatischbasis{
    public:
                _guifensterstatischzentriert(T_String<> const &pn,_guifenster*parent);
                virtual ~_guifensterstatischzentriert();
};











//******************************************************************************************************************************************************************************************************
//                                                              G U I K N O P F
//******************************************************************************************************************************************************************************************************
class _guiknopf:public _guifenster{
    public:
                _guiknopf(T_String<> const &pn, _guifenster*parent);
                virtual ~_guiknopf();
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I K N O P F C H E C K B A S I S
//******************************************************************************************************************************************************************************************************
class _guiknopfcheckbasis: public _guiknopf{
    public:
                _guiknopfcheckbasis(T_String<> const &pn, _guifenster*parent);
                virtual ~_guiknopfcheckbasis();
                bool gesetzt();
                void gesetzt(bool check);
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I K N O P F C H E C K L I N K S
//******************************************************************************************************************************************************************************************************
class _guiknopfchecklinks:public _guiknopfcheckbasis{
    public:
                template <class T> _guiknopfchecklinks(T_String<> const &pn,_guifenster*parent, _guiereignisCommand<T> *ec);
                virtual ~_guiknopfchecklinks();
};
template <class T> _guiknopfchecklinks::_guiknopfchecklinks(T_String<> const &pn,_guifenster*parent,_guiereignisCommand<T> *ec):_guiknopfcheckbasis(pn,parent){
                                                                erzeugen(WS_CHILD|BS_AUTOCHECKBOX, 0, L"BUTTON");
                                                                farbehintergrund(GetSysColor(COLOR_BTNFACE));  // Standardhintergrund für Dialoge
                                                                *this+=ec;
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I K N O P F C H E C K R E C H T S
//******************************************************************************************************************************************************************************************************
class _guiknopfcheckrechts:public _guiknopfcheckbasis{
    public:
                template <class T> _guiknopfcheckrechts(T_String<> const &pn,_guifenster*parent,_guiereignisCommand<T>*ec);
                virtual ~_guiknopfcheckrechts();
};
template <class T> _guiknopfcheckrechts::_guiknopfcheckrechts(T_String<> const &pn,_guifenster*parent,_guiereignisCommand<T>*ec):_guiknopfcheckbasis(pn,parent){
                                                                erzeugen(WS_CHILD|BS_RIGHTBUTTON|BS_LEFT|BS_AUTOCHECKBOX,0,L"BUTTON");
                                                                farbehintergrund(GetSysColor(COLOR_BTNFACE));  // Standardhintergrund für Dialoge
                                                                *this+=ec;
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I K N O P F D R U C K 
//******************************************************************************************************************************************************************************************************
class _guiknopfdruck:public _guiknopf{
    public:
                template <class T> _guiknopfdruck(T_String<> const &pn,_guifenster*parent,_guiereignisCommand<T>*ec);
                virtual ~_guiknopfdruck();
};
template <class T> _guiknopfdruck::_guiknopfdruck(T_String<> const &pn,_guifenster*parent,_guiereignisCommand<T>*ec):_guiknopf(pn,parent){
                                                                erzeugen(WS_CHILD|BS_PUSHBUTTON,0,L"BUTTON");
                                                                *this+=ec;
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I K N O P F R A D I O 
//******************************************************************************************************************************************************************************************************
class _guiknopfradio: public _guiknopf{
    public:
                template <class T> _guiknopfradio(T_String<> const &pn,_guifenster*parent,_guiereignisCommand<T>*ec);
                virtual ~_guiknopfradio();
};
template <class T> _guiknopfradio::_guiknopfradio(T_String<> const &pn,_guifenster*parent,_guiereignisCommand<T>*ec):_guiknopf(pn,parent){
                                                                erzeugen(WS_CHILD|BS_RADIOBUTTON,0,L"BUTTON");
                                                                *this += ec;
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I D I A L O G
//******************************************************************************************************************************************************************************************************
class _guidialog:public _guifenster{
    public:
                    _guidialog(T_String<> const &pn,_guifenster*parent);
                    virtual ~_guidialog();
                    void besitzerzeichnung(bcBool od);
    private:
                    void beiskalieren(_guiereignisdaten*ep);
                    void beiloeschenhintergrund(_guiereignisdaten*ep);
    private:
                    bool pbesitzerzeichnung;
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I E D I T I E R B A R
//******************************************************************************************************************************************************************************************************
class _guieditierbar:public _guifensterkind{
    public:
                    _guieditierbar(_guidialogeditierbar*dialog,T_String<> const &section,T_String<> const &pn);
                    virtual ~_guieditierbar();
                    bool beruehrt() const;
                    void beruehrt(bool touched);
                    template <class T> T *objekt(unsigned int index);
                    void skalieren();
   protected:
                    _guifensterstatischlinks*pDescription;
   private:
                    bool ptouched;
};
template <class T> T *_guieditierbar::objekt(unsigned int index){
                                                                //  Holt ein Objekt aus dem Editable
                                                                unsigned int i=0;
                                                                _guiobjekt*oit;
                                                                // ----------------------------------
                                                                unsigned int ii=_listebasis<_guiobjekt>::anzahl();
                                                                if(++index >= ii)  // +1, weil die Beschreibung auch schon in der Liste hängt
                                                                 throw L"BCEditable::Object() -> Index out of Range!";
                                                                if(_listebasis<_guiobjekt>::anfang(oit))do{
                                                                 if(0==index) return(oit->Cast<T>(false));
                                                                 index--;
                                                                }while(_listebasis<_guiobjekt>::naechstes(oit));
                                                                throw L"BCEditable::Object() -> Index out of Range!";
};

//******************************************************************************************************************************************************************************************************
//                                                              G U I E D I T I E R B A R S E K T I O N 
//******************************************************************************************************************************************************************************************************
class _guieditierbarsektion : public _guiknopf{
    friend class _guidialogeditierbar;
    private:
                _guieditierbarsektion(_guidialogeditierbar*dialog,T_String<> const &pn);
                void beibefehl(_guiereignisdaten*);//Für den Button der die Sektion öffnet bzw. schließt
    public:
                virtual ~_guieditierbarsektion();
                bool offen() const;
                void offen(bool o);
                _guieditierbar*editierbar(T_String<> const &pn);
                template <class T> T*objekt(T_String<> const &pn,unsigned int index);
    private:
                T_String<> prealname;   // Echter Name (ohne + und -)
                bool popen;      // Gibt an ob die Sektion geöffnet ist
                _liste<_guieditierbar> peditables;  // Liste mit allen Editables
};
template <class T> T *_guieditierbarsektion::objekt(T_String<> const &pn,unsigned int index){
                                                                //Gibt ein Objekt eines Editable zurück
                                                                return(editierbar(pn)->objekt<T>(index));
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I D I A L O G E D I T I E R B A R
//******************************************************************************************************************************************************************************************************
class _guidialogeditierbar : public _guidialog{
    friend class _guieditierbartextfeld;
    friend class _guieditierbarcombobox;
    public:
                _guidialogeditierbar(T_String<> const &pn,_guifenster*parent);
                virtual ~_guidialogeditierbar();
                _guifensterkind*fenster();
                _guiscrollbarvertikal*scrollbar();
                _guieditierbarsektion *sektion(T_String<> const &section);
                void addiereneditierbarzusektion(T_String<> const &section,_guieditierbar*editable);
                void addierensektion(T_String<> const &section);
                void loeschensektion();
                virtual void zeigen();
                void neusetzen(T_String<> const &pn);
   private:
                void beiskalieren(_guiereignisdaten *);  // Für das innere Fenster
                void beizeichnen(_guiereignisdaten *);
                void beiloeschenhintergrund(_guiereignisdaten *);  // Für das innere Fenster
                void beimausrad(_guiereignisdaten *);
   protected:
                virtual void knopfok(_guiereignisdaten *);  // Muss in der Anwendung überladen werden können...
                virtual void knopfuebernehmen(_guiereignisdaten *);
                virtual void knopfabbruch(_guiereignisdaten *);
   private:
                _guifensterkind*pwindow;     // Inneres Fenster (das hat die ScrollBar und die Editables)
                _guiscrollbarvertikal*pscrollBar;  // u.A. zum Auslesen der Breite...
                _tg pdivide; // Hier wird die Ansicht geteilt (0-1)
                _liste<_guieditierbarsektion>  psectionList;  // Liste mit allen Sektionen
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I D I A L O G M O D A L 
//******************************************************************************************************************************************************************************************************
class _guidialogmodal:public _guidialog{
    public:
                _guidialogmodal(T_String<> const &pn,_guifenster*parent);
                virtual ~_guidialogmodal();
                virtual void zeigen();// Überladen damit wir das Parent wieder aktivieren können
                virtual void verstecken();
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I D I A L O G D A T E I F I L T E R 
//******************************************************************************************************************************************************************************************************
class _guidialogdateifilter{
    friend class _guidialogdatei;
    public:
                _guidialogdateifilter(T_String<> const &pn, T_String<> const &ext)  { pname = pn; pextension = ext; }
                virtual ~_guidialogdateifilter()  { }
    private:
                T_String<> pname,pextension;
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I D I A L O G D A T E I
//******************************************************************************************************************************************************************************************************
class _guidialogdatei:public _guidialogmodal{
    public:
                _guidialogdatei(_guifenster*parent);
                virtual ~_guidialogdatei();
                T_String<> dateititel() const;
                T_String<> dateiname() const;
                void dateiname(T_String<> const &fn);
                void loeschenfilter();
                void addierenfilter(T_String<> const &pn, T_String<> const &ext);
                void standarderweiterung(T_String<> const &ext);
                bool oeffnen(T_String<> const &dialogname = L"Datei öffnen");
                bool speichern(T_String<> const &dialogname = L"Datei speichern");
    private:
                void erzeugenfilter(std::vector<wchar_t> &buffer);
    private:
                OPENFILENAME ofn;
                _liste<_guidialogdateifilter> pfilterList;
                T_String<> pdefaultExtension;
                wchar_t  pfileTitle[1024],pfileName[1024];
};








//******************************************************************************************************************************************************************************************************
//                                                              G U I F E N S T E R K A R T E I
//******************************************************************************************************************************************************************************************************
class _guifensterkartei : public _guifenster{
    friend class _guifensterkarteiseite;
    public:
                _guifensterkartei(_guifenster*parent);
                virtual ~_guifensterkartei();
                unsigned int selektion();
                void selektion(unsigned int num);
    private:
                void beiselektion(_guiereignisdaten*);
    private:
                _liste<_guifensterkarteiseite> plistPages;
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I F E N S T E R K A R T E I S E I T E 
//******************************************************************************************************************************************************************************************************
class _guifensterkarteiseite:public _guidialog{
    public:
                _guifensterkarteiseite(T_String<> const &pn,_guifensterkartei*tw);
                virtual ~_guifensterkarteiseite();
                virtual void skalieren();  // Überladen vom Objekt, bzw. vom Fenster
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I F E N S T E R W E R K Z E U G 
//******************************************************************************************************************************************************************************************************
class _guifensterwerkzeug:public _guifenster{
    public:
                _guifensterwerkzeug(T_String<> const &pn,_guifenster*parent,_guimenueleiste*menu=0);
                virtual ~_guifensterwerkzeug();
};











//******************************************************************************************************************************************************************************************************
//                                                              G U I T E X T F E L D B A S I S
//******************************************************************************************************************************************************************************************************
class _guitextfeldbasis:public _guifenster{
    public:
                _guitextfeldbasis(T_String<> const &pn,_guifenster*parent);
                virtual ~_guitextfeldbasis();
                void nurlesen(bool ro);
                void nummer(bool nr);
                void passwort(bool pw);
                void begrenzentext(unsigned int numchars);
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I T E X T F E L D
//******************************************************************************************************************************************************************************************************
class _guitextfeld:public _guitextfeldbasis{
    public:
                _guitextfeld(T_String<> const &pn,_guifenster*parent);
                virtual ~_guitextfeld();
                int zuint();
                _tg zutg();
                T_String<> text();
                // Funktionen zum Setzen des Texts (in diversen Variationen)
                template <class T> void text(T const &var);
};
template <class T> void _guitextfeld::text(T const &var){
                                                                //Setzt den Text im Editfeld
                                                                _streamwide stream;
                                                                stream<<var;
                                                                _guifenster::name(stream.str().c_str());
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I T E X T F E L D M U L T I 
//******************************************************************************************************************************************************************************************************
class _guitextfeldmulti:public _guitextfeldbasis{
    public:
                _guitextfeldmulti(T_String<> const &pn,_guifenster*parent);
                virtual ~_guitextfeldmulti();
                void maximalezeilen(unsigned int ml);
                void schreibenzeile(T_String<> const &text);
    private:
                unsigned int pmaxLines;  // Maximale Anzahl der Linien (für Logfenster)
};


//******************************************************************************************************************************************************************************************************
//                                                              G U I C O M B O B O X
//******************************************************************************************************************************************************************************************************
class _guicombobox:public _guifenster{
    public:
                _guicombobox(_guifenster*parent);
                virtual ~_guicombobox();
                void addierentext(T_String<> const &string);
                unsigned int selektion();
                void selektion(unsigned int num);
                T_String<> selektiontext();
                void selektion(T_String<> const &string);
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I L I S T B O X
//******************************************************************************************************************************************************************************************************
class _guilistbox:public _guifenster{
    public:
                _guilistbox(_guifenster*parent);
                virtual ~_guilistbox();
                int selektion();
                void selektion(int i);
                T_String<> text(int i);
                void addierentext(T_String<> const &string);
                void loeschentext(int index);
                void loeschentext();
};

//******************************************************************************************************************************************************************************************************
//                                                              G U I S C R O L L B A R B A S I S
//******************************************************************************************************************************************************************************************************
class _guiscrollbarbasis: public _guifenster{
    public:
                _guiscrollbarbasis(_guifenster*parent);
                virtual ~_guiscrollbarbasis();
                int schritt();
                void schritt(int ss);
                int ort();
                void ort(int pos,bool redraw = true);
                int trackort();
                int seite();
                void seite(int page);
                int bereichminimal();
                int bereichmaximal();
                void bereich(int min, int max);
                void LineLeft();
                void LineRight();
                void PageLeft();
                void PageRight();
                void LineUp();
                void LineDown();
                void PageUp();
                void PageDown();
    private:
                int pstepSize;
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I S C R O L L H O R I Z O N T A L 
//******************************************************************************************************************************************************************************************************
class _guiscrollbarhorizontal:public _guiscrollbarbasis{
    public:
                _guiscrollbarhorizontal(_guifenster*parent);
                virtual ~_guiscrollbarhorizontal();
                virtual void skalieren();
};

//******************************************************************************************************************************************************************************************************
//                                                              G U I S C R O L L V E R T I K A L
//******************************************************************************************************************************************************************************************************
class _guiscrollbarvertikal:public _guiscrollbarbasis{
    public:
                _guiscrollbarvertikal(_guifenster*parent);
                virtual ~_guiscrollbarvertikal();
                virtual void skalieren();
};


//******************************************************************************************************************************************************************************************************
//                                                              G U I T E I L E R B A S I S
//******************************************************************************************************************************************************************************************************
class _guiteilerbasis:public _guifenster{
    public:
                _guiteilerbasis(_guifenster*parent,_guifenster*top,_guifenster*bottom);
                virtual ~_guiteilerbasis();
                void breite(int w);
                void hoehe(int h);
                _tg lesen() const;
                void setzen(_tg p);
                void minimal(_tg min);
                void maximal(_tg max);
                void einrastenlinks(_tg snap);
                void einrastenoben(_tg snap);
                void einrastenrechts(_tg snap);
                void einrastenunten(_tg snap);
                void links(_guifenster *left);
                void oben(_guifenster *top);
                void rechts(_guifenster *right);
                void unten(_guifenster *bottom);
                virtual void skalieren();
    private:
                void beiknopflinkshoch(_guiereignisdaten*ep);
                void beiloeschenhintergrund(_guiereignisdaten*ep);
    protected:
                bool pleftButtonDown;
                int pclickOffset;// Nur Spielerei, sieht aber schöner aus
                int pheight; // Höhe bzw. Breite (je nach Typ)
                _tg ppercent;// 0-1
                _tg pmin,pmax; // Minimale und Maximale Koordinaten
                _tg psnapTop,psnapBottom; // Abstand bei dem der Splitter ganz an den Rand geschoben wird (manche OpenGL-Karten kacken da ab...)
                _guifenster*ptop,*pbottom; // Linkes und rechtes Fenster
};

//******************************************************************************************************************************************************************************************************
//                                                              G U I T E I L E R H O R I Z O N T A L
//******************************************************************************************************************************************************************************************************
class _guiteilerhorizontal:public _guiteilerbasis{
    public:
                _guiteilerhorizontal(_guifenster*parent,_guifenster*top,_guifenster*bottom);  // Parent = Ausgangsgröße für das Verschieben!!
                virtual ~_guiteilerhorizontal();
    private:
                void beigroesse(_guiereignisdaten*ep);
                void beiknopflinksrunter(_guiereignisdaten*ep);
                void beimausbewegung(_guiereignisdaten*ep);
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I T E I L E R V E R T I K A L
//******************************************************************************************************************************************************************************************************
class _guiteilervertikal:public _guiteilerbasis{
    public:
                _guiteilervertikal(_guifenster*parent,_guifenster*left,_guifenster*right);  // Parent = Ausgangsgröße für das Verschieben!!
                virtual ~_guiteilervertikal();
    private:
                void beigroesse(_guiereignisdaten*ep);
                void beiknopflinksrunter(_guiereignisdaten*ep);
                void beimausbewegung(_guiereignisdaten*ep);
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I S T A T U S L E I S T E
//******************************************************************************************************************************************************************************************************
class _guistatusleiste:public _guifenster{
    public:
                _guistatusleiste(_guifenster*parent);
                virtual ~_guistatusleiste();
                void teile(int parts,int *info);
                void text(int part,T_String<> const &text);
                virtual void skalieren();
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I W E R K Z E U G L E I S T E K N O P F
//******************************************************************************************************************************************************************************************************
class _guiwerkzeugleisteknopf:public _guiobjekt{
    friend class _guiwerkzeugleiste;
    public:
                template <class T> _guiwerkzeugleisteknopf(_guiwerkzeugleiste*tb,unsigned int index,T_String<> const &tooltip,_guiereignisCommand<T>*ec);
                virtual ~_guiwerkzeugleisteknopf();
                unsigned int index();
                T_String<> hilfe();
                void hilfe(T_String<> const &tooltip);
                void stil(unsigned int style);
                bool gesetzt() const;
                void gesetzt(bool check);
    private:
                _guiwerkzeugleiste*ptoolBar;  // Zeiger auf ToolBar (zum Setzen des Stils usw.)
                unsigned int pindex;
                T_String<> ptoolTip;   // ToolTip
};
template <class T> _guiwerkzeugleisteknopf::_guiwerkzeugleisteknopf(_guiwerkzeugleiste*tb,unsigned int index, T_String<> const &tooltip,_guiereignisCommand<T> *ec):_guiobjekt(L"guiwerkzeugleisteknopf",tb){
                                                                ptoolBar=tb;
                                                                pindex=index;
                                                                ptoolTip=tooltip;
                                                                *tb+=this;
                                                                *this+=ec;
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I W E R K Z E U G L E I S T E 
//******************************************************************************************************************************************************************************************************
class _guiwerkzeugleiste:public _guifenster{
    public:
                _guiwerkzeugleiste(_guifenster*parent);
                virtual ~_guiwerkzeugleiste();
                virtual void skalieren();
                void knopfgroesse(unsigned short int width,unsigned short int height);
                void addierenbitmap(unsigned int num, HANDLE hbmp);
                void addierenbitmapresource(unsigned int num,unsigned int resid);
                void addierenbitmapsystem(unsigned int id);
                void separator(unsigned int size = 8);
                void operator+=(_guiwerkzeugleisteknopf*tbbutton);
};


//******************************************************************************************************************************************************************************************************
//                                                              G U I B A U M B O X E I N T R A G B A S I S
//******************************************************************************************************************************************************************************************************
template <class T> class _guibaumboxeintragbasis:public _guiobjekt{
    public:
                _guibaumboxeintragbasis(T_String<> const&pn,_guibaumbox<T>*tv);
                virtual ~_guibaumboxeintragbasis();
                T *data() { return(pdata); };
                void data(T *d){ pdata=d; };
                HTREEITEM eintrag()  {return(ptreeItem);};
   protected:
                HTREEITEM  ptreeItem;
   private:
                T*pdata;
};
template <class T> _guibaumboxeintragbasis<T>::_guibaumboxeintragbasis(T_String<>const &pn,_guibaumbox<T>*tv):_guiobjekt(pn, tv){
                                                                pdata=0;
                                                                ptreeItem=0;
                                                                tv->_liste<_guibaumboxeintragbasis<T> >::einhaengen(this);
};
template <class T> _guibaumboxeintragbasis<T>::~_guibaumboxeintragbasis(){
                                                                if(pdata)delete pdata;
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I B A U M B O X A S T
//******************************************************************************************************************************************************************************************************
template<class T> class _guibaumboxast:public _guibaumboxeintragbasis<T>{
    public:
            _guibaumboxast(T_String<> const &pn,_guibaumbox<T> *tv,_guibaumboxeintragbasis<T>*branch);
            virtual ~_guibaumboxast();
};
template<class T> _guibaumboxast<T>::_guibaumboxast(T_String<> const&pn,_guibaumbox<T>*tv,_guibaumboxeintragbasis<T>*branch):_guibaumboxeintragbasis<T>(pn,tv){
                                                                TV_INSERTSTRUCT tvi;
                                                                ZeroMemory(&tvi,sizeof(tvi));
                                                                if(!branch){
                                                                 tvi.hInsertAfter=TVI_ROOT;
                                                                }else{
                                                                 tvi.hParent=branch->eintrag();
                                                                 tvi.hInsertAfter=TVI_LAST;
                                                                };
                                                                tvi.itemex.stateMask=TVIS_BOLD|TVIS_EXPANDED;
                                                                tvi.itemex.state=TVIS_BOLD|TVIS_EXPANDED;
                                                                tvi.itemex.mask=TVIF_TEXT|TVIF_CHILDREN|TVIF_STATE;
                                                                tvi.itemex.pszText=(unsigned short int *)pn.Data();
                                                                tvi.itemex.cchTextMax=(int)(pn.Length() + 1);
                                                                tvi.itemex.cChildren=1;
                                                                   
                                                                // In die TreeView einhängen
                                                                ptreeItem=TreeView_InsertItem(tv->handle(),&tvi);
};
template<class T> _guibaumboxast<T>::~_guibaumboxast(){
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I B A U M B O X E I N T R A G 
//******************************************************************************************************************************************************************************************************
template <class T> class _guibaumboxeintrag:public _guibaumboxeintragbasis<T>{
    public:
                _guibaumboxeintrag(T_String<> const &pn,_guibaumbox<T>*tv,_guibaumboxeintragbasis<T>*branch);
                virtual ~_guibaumboxeintrag();
};
template <class T> _guibaumboxeintrag<T>::_guibaumboxeintrag(T_String<> const &pn,_guibaumbox<T>*tv,_guibaumboxeintragbasis<T>*branch):_guibaumboxeintragbasis<T>(pn,tv){
                                                                TV_INSERTSTRUCT tvi;
                                                                ZeroMemory(&tvi,sizeof(tvi));
                                                                if(!branch){
                                                                 tvi.hInsertAfter=TVI_ROOT;
                                                                }else{
                                                                 tvi.hParent=branch->eintrag();
                                                                 tvi.hInsertAfter=TVI_LAST;
                                                                };
                                                                tvi.itemex.mask=TVIF_TEXT;
                                                                tvi.itemex.pszText=(unsigned short int*)pn.Data();
                                                                tvi.itemex.cchTextMax=(int)(pn.Length()+1);
                                                                // In die TreeView einhängen
                                                                ptreeItem=TreeView_InsertItem(tv->handle(),&tvi);
};
template <class T> _guibaumboxeintrag<T>::~_guibaumboxeintrag(){
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I B A U M B O X 
//******************************************************************************************************************************************************************************************************
template <class T> class _guibaumbox:public _guifenster,private _liste<_guibaumboxeintragbasis<T> >{
    friend class _guibaumboxeintragbasis<T>;
    public:
                _guibaumbox(_guifenster*parent);
                virtual ~_guibaumbox();
                void farbehintergrundeintrag(unsigned int rgb);
                void farbehintergrundeintrag(unsigned char r,unsigned char g,unsigned char b);
                void farbetexteintrag(unsigned int rgb);
                void farbetexteintrag(unsigned char r,unsigned char g,unsigned char b);
                _guibaumboxeintragbasis<T>*selektion();
                void selektion(unsigned int pos);
                T*selektionsdaten();
};
template <class T> _guibaumbox<T>::_guibaumbox(_guifenster *parent) : _guifenster(L"", parent){
                                                                Create(WS_CHILD|WS_BORDER|TVS_HASLINES|TVS_LINESATROOT|TVS_HASBUTTONS|TVS_NOTOOLTIPS|TVS_DISABLEDRAGDROP|TVS_SHOWSELALWAYS,0,WC_TREEVIEW);
};
template <class T> _guibaumbox<T>::~_guibaumbox(){
                                                                _liste<_guibaumboxeintragbasis<T> >::aushaengen;
};
template <class T> void _guibaumbox<T>::farbehintergrundeintrag(unsigned int rgb){
                                                                //Setzt die Hintergrundfarbe der Items
                                                                TreeView_SetBkColor(handle(), rgb);
};

template <class T> void _guibaumbox<T>::farbehintergrundeintrag(unsigned char r,unsigned char g,unsigned char b){
                                                                farbehintergrundeintrag(RGB(r,g,b));
};

template <class T> void _guibaumbox<T>::farbetexteintrag(unsigned int rgb){
                                                                //  Setzt die Textfarbe der Items
                                                                TreeView_SetTextColor(handle(), rgb);
};

template <class T> void _guibaumbox<T>::farbetexteintrag(unsigned char r,unsigned char g,unsigned char b){
                                                                farbetexteintrag(RGB(r, g, b));
};
template <class T> _guibaumboxeintragbasis<T> *_guibaumbox<T>::selektion(){
                                                                //  Holt/Setzt das selektierte Objekt
                                                                HTREEITEM hItem=TreeView_GetSelection(handle());
                                                                _listenknoten<_guibaumboxeintragbasis<T> >*node;
                                                                // --------------------------------------------------------------------------
                                                                if(!hItem) return(0);
                                                                if(_liste<_guibaumboxeintragbasis<T> >::anfang(node))do{
                                                                 if(node->objekt()->eintrag()==hItem) return(node->objekt());
                                                                }while(_liste<_guibaumboxeintragbasis<T> >::naechstes(node));
                                                                return(0);
};
template <class T> void _guibaumbox<T>::selektion(unsigned int pos){
                                                                _listenknoten<_guibaumboxeintragbasis<T> >*node=_liste<_guibaumboxeintragbasis<T> >[pos];
                                                                if(node) TreeView_SelectItem(handle(),node->objekt()->eintrag());
};
template <class T> T*_guibaumbox<T>::selektionsdaten(){
                                                                //  Gibt die Daten des selektierten Objekts zurück
                                                                _guibaumboxeintragbasis<T>*sel=selektion();
                                                                if(!sel) return(0);
                                                                return(sel->Data());
};


















//******************************************************************************************************************************************************************************************************
//                                                              E D I T I O N S K O P P L U N G D I A L O G
//******************************************************************************************************************************************************************************************************
/*class _editionskopplungdialog:public _liste<_editionskopplung>{
        public:
                _editionskopplung();
                virtual ~_editionskopplung();
                void setzen(T_String<> const &section,T_String<> const &name);
        public:
                
};*/
//******************************************************************************************************************************************************************************************************
//                                                              E D I T I O N S K O P P L U N G
//******************************************************************************************************************************************************************************************************
class _editionskopplung:public _listenknotenbasis<_editionskopplung>{
        public:
                _editionskopplung(_dynamischerdialog*,T_String<> const &section,T_String<> const &name);
                virtual ~_editionskopplung();
                _dynamischerdialog*dialog();
                virtual void exportieren()=0;//dialoganzeige = grafisches element
                virtual void importieren()=0;//grafisches element = dialoganzeige
                virtual void zeichnen(_grafik*)=0;
                void aktiv(const bool b);
                bool aktiv()const;
                void farbe(const _vektor4<_to>&);
                _vektor4<_to> farbe()const;
                void editionsradius(const _tg);
                _tg editionsradius()const;
                _guieditierbar*editierbares();
                virtual void verschieben(const _vektor3<_tg>&)=0;
                virtual _vektor3<_tg> abstand(const _vektor3<_tg>&,const _vektor3<_tg>&)=0;
        private:
				_dynamischerdialog*pdialog;
                T_String<> psection;                
                T_String<> pname;  
                bool paktiv;
                _vektor4<_to> pfarbe;
                _tg peditionsradius;
                _guieditierbar*peditable;  
};
//******************************************************************************************************************************************************************************************************
//                                                              E D I T I O N S K O P P L U N G O R T
//******************************************************************************************************************************************************************************************************
class _editionskopplungort:public _editionskopplung{
        public:
                _editionskopplungort(_dynamischerdialog*,T_String<> const &section,T_String<> const &name);
                virtual ~_editionskopplungort();
                virtual void exportieren();//dialoganzeige = grafisches element
                virtual void importieren();//grafisches element = dialoganzeige
                _vektor3<_tg> ort()const;
                void ort(const _vektor3<_tg>&);
                virtual void zeichnen(_grafik*);
                virtual void verschieben(const _vektor3<_tg>&);
                virtual _vektor3<_tg> abstand(const _vektor3<_tg>&,const _vektor3<_tg>&);
        private:
                _vektor3<_tg> port;              
};
//******************************************************************************************************************************************************************************************************
//                                                              E D I T I O N S K O P P L U N G V E K T O R
//******************************************************************************************************************************************************************************************************
class _editionskopplungvektor:public _editionskopplung{
        public:
                _editionskopplungvektor(_dynamischerdialog*,T_String<> const &section,T_String<> const &name,_editionskopplungort*eort);
                virtual ~_editionskopplungvektor();
                virtual void exportieren();//dialoganzeige = grafisches element
                virtual void importieren();//grafisches element = dialoganzeige
                _vektor3<_tg> vektor()const;
                void vektor(const _vektor3<_tg>&);
                virtual void zeichnen(_grafik*);
                virtual void verschieben(const _vektor3<_tg>&);
                virtual _vektor3<_tg> abstand(const _vektor3<_tg>&,const _vektor3<_tg>&);		
        private: 
				_editionskopplungort*peort;              
				_vektor3<_tg> pvektor;
};
//******************************************************************************************************************************************************************************************************
//                                                              E D I T I E R B A R
//******************************************************************************************************************************************************************************************************
class _editierbar{
    public:
        virtual void einhaengendialog(_dynamischerdialog*)=0;
        virtual void auslesendialog(_dynamischerdialog*)=0;
        virtual void vorbereitenereignisprozess(_guiereignisdaten*);
        virtual void nachbereitenereignisprozess(_guiereignisdaten*);
};
class _besitzeraktualisierung{
        public:
                virtual void aktualisieren()=0;
};
//******************************************************************************************************************************************************************************************************
//                                                              D Y N A M I S C H E R  D I A L O G
//******************************************************************************************************************************************************************************************************
class _dynamischerdialog:public _guidialogeditierbar,public _listebasis<_editionskopplung>,public _listenknotenbasis<_dynamischerdialog>{
        public:
                _dynamischerdialog(T_String<> const &name,_guifenster *parent,_listebasis<_dynamischerdialog>*);
                virtual ~_dynamischerdialog();
                virtual void knopfok(_guiereignisdaten*);  // Muss in der Anwendung überladen werden können... 
                virtual void knopfuebernehmen(_guiereignisdaten*); 
                virtual void neusetzen(const T_String<>);
                virtual void zeigen();
                virtual void verstecken();
                void beitaste(_guiereignisdaten*);
                bool beruehrt(T_String<> const &section,T_String<> const &name);
                void beischliessen(_guiereignisdaten*);
                void beicomboboxberuehrt(_guiereignisdaten*);
                void beieditboxberuehrt(_guiereignisdaten*);
                void editierbar(_editierbar*);
                void addiereneditierbar(_editierbar*e);
                void einhaengen(T_String<> const &section,T_String<> const &n,const bool);
                void einhaengen(T_String<> const &section,T_String<> const &n,const unsigned char);
                void einhaengen(T_String<> const &section,T_String<> const &n,const signed char);
                void einhaengen(T_String<> const &section,T_String<> const &n,const unsigned short int);
                void einhaengen(T_String<> const &section,T_String<> const &n,const signed short int);
                void einhaengen(T_String<> const &section,T_String<> const &n,const unsigned int);
                void einhaengen(T_String<> const &section,T_String<> const &n,const signed int);
                void einhaengen(T_String<> const &section,T_String<> const &n,const unsigned long int);
                void einhaengen(T_String<> const &section,T_String<> const &n,const signed long int);
                void einhaengen(T_String<> const &section,T_String<> const &n,const float);
                void einhaengen(T_String<> const &section,T_String<> const &n,const double);
                void einhaengen(T_String<> const &section,T_String<> const &n,const _zeichenkette<char>&);
                template <class T>void einhaengenknopf(T_String<> const &section,T_String<> const &editablename,T_String<> const &buttonname,T*,void (T::*mfp)(_guiereignisdaten *));
                template <class T> void einhaengen(T_String<> const &section,T_String<> const &n,const _vektor<T>&);
                template <class T> void einhaengen(T_String<> const &section,T_String<> const &n,const _vektor2<T>&);
                template <class T> void einhaengen(T_String<> const &section,T_String<> const &n,const _vektor3<T>&);
                template <class T> void einhaengen(T_String<> const &section,T_String<> const &n,const _vektor4<T>&);
                void auslesen(T_String<> const &section,T_String<> const &n,bool&);
                void auslesen(T_String<> const &section,T_String<> const &n,unsigned char&);
                void auslesen(T_String<> const &section,T_String<> const &n,signed char&);
                void auslesen(T_String<> const &section,T_String<> const &n,unsigned short int&);
                void auslesen(T_String<> const &section,T_String<> const &n,signed short int&);
                void auslesen(T_String<> const &section,T_String<> const &n,unsigned int&);
                void auslesen(T_String<> const &section,T_String<> const &n,signed int&);
                void auslesen(T_String<> const &section,T_String<> const &n,unsigned long int&);
                void auslesen(T_String<> const &section,T_String<> const &n,signed long int&);
                void auslesen(T_String<> const &section,T_String<> const &n,float&);
                void auslesen(T_String<> const &section,T_String<> const &n,double&);
                void auslesen(T_String<> const &section,T_String<> const &n,_zeichenkette<char>&);
                template <class T> void auslesen(T_String<> const &section,T_String<> const &n,_vektor<T>&);
                template <class T> void auslesen(T_String<> const &section,T_String<> const &n,_vektor2<T>&);
                template <class T> void auslesen(T_String<> const &section,T_String<> const &n,_vektor3<T>&);
                template <class T> void auslesen(T_String<> const &section,T_String<> const &n,_vektor4<T>&);
        private:
                _liste<_editierbar> peditierbarliste;   
                _liste<_guieditierbar> editables; 
                _guifenster*pparent;
                
};

// dynamischer _vektor
template <class T> void _dynamischerdialog::einhaengen(T_String<> const &section,T_String<> const &n,const _vektor<T>&val){
                                _guitextfeld  *ef;
                                _guieditierbar    *editable=new _guieditierbar(this, section, n);
                                editables.einhaengen(editable);
                                _tg size=(1-PERCENT_DESCRIPTION)/(_tg)val.holendimension();
                                for(unsigned int i = 0; i < val.holendimension(); i++){
                                 ef = new _guitextfeld(L"", editable);
                                 *ef += new _guiort<>(PERCENT_DESCRIPTION + i * size, 0, false);
                                 *ef += new _guigroesse<>(size, 1, false);
                                 *ef += new _guiereignisCommand<_dynamischerdialog>(this,&_dynamischerdialog::beieditboxberuehrt);
                                 *ef += new _guiereignisKeyDown<_dynamischerdialog>(this,&_dynamischerdialog::beitaste);
                                 ef->farbehintergrund(150,150,150);
                                 ef->text(val[i]);
                                 ef->zeigen();
                                };
};
template <class T> void _dynamischerdialog::auslesen(T_String<> const &section,T_String<> const &n,_vektor<T>&val){
                                _guitextfeld*ef;
                                _guieditierbar*editable=sektion(section)->editierbar(n);
                                for(unsigned int i = 0; i < val.holendimension(); i++){
                                 ef = editable->objekt<_guitextfeld>(i);
                                 val.setzenkomponente(i, (T)ef->zutg());
                                 ef->farbehintergrund(150,150,150);
                                 ef->neuzeichnen();
                                };
                                editable->beruehrt(false);
};
#define IMPLEMENT_VEKTOREINHAENGEN(__type, __res) \
template <class T> void _dynamischerdialog::einhaengen(T_String<> const &section,T_String<> const &n,const __type&val){ \
                                _guitextfeld*ef; \
                                _guieditierbar*editable=new _guieditierbar(this,section,n); \
                                editables.einhaengen(editable);\
                                _tg size=(1 - PERCENT_DESCRIPTION) / (_tg)__res; \
                                for(unsigned int i = 0; i < __res; i++){ \
                                 ef=new _guitextfeld(L"", editable); \
                                 *ef+=new _guiort<>(PERCENT_DESCRIPTION + i * size, 0, false); \
                                 *ef+=new _guigroesse<>(size, 1, false); \
                                 *ef+=new _guiereignisCommand<_dynamischerdialog>(this,&_dynamischerdialog::beieditboxberuehrt);\
                                 *ef+=new _guiereignisKeyDown<_dynamischerdialog>(this,&_dynamischerdialog::beitaste);\
                                 ef->farbehintergrund(150,150,150);\
                                 ef->text(val[i]); \
                                 ef->zeigen(); \
                                }; \
};
#define IMPLEMENT_VEKTORAUSLESEN(__type, __res) \
template <class T> void _dynamischerdialog::auslesen(T_String<> const &section,T_String<> const &n,__type&val){ \
                                _guitextfeld*ef; \
                                _guieditierbar*editable=sektion(section)->editierbar(n); \
                                for(unsigned int i = 0; i < __res; i++){ \
                                 ef = editable->objekt<_guitextfeld>(i); \
                                 val.setzenkomponente(i, (T)ef->zutg()); \
                                 ef->farbehintergrund(150,150,150);\
                                 ef->neuzeichnen();\
                                }; \
                                editable->beruehrt(false);\
};
IMPLEMENT_VEKTOREINHAENGEN(_vektor2<T>, 2)
IMPLEMENT_VEKTOREINHAENGEN(_vektor3<T>, 3)
IMPLEMENT_VEKTOREINHAENGEN(_vektor4<T>, 4)
IMPLEMENT_VEKTORAUSLESEN(_vektor2<T>, 2)
IMPLEMENT_VEKTORAUSLESEN(_vektor3<T>, 3)
IMPLEMENT_VEKTORAUSLESEN(_vektor4<T>, 4)
template <class T>void _dynamischerdialog::einhaengenknopf(T_String<> const &section,T_String<> const &editablename,T_String<> const &buttonname,T*objekt,void (T::*mfp)(_guiereignisdaten *)){
                                _guieditierbar*editable=new _guieditierbar(this, section, editablename);
                                editables.einhaengen(editable);
                                _guiknopfdruck*pb=new _guiknopfdruck(buttonname, editable, new _guiereignisCommand<T>(objekt, mfp));
                                *pb += new _guiort<>(0.4, 0, false);
                                //*pb += new _guiort<>(-64, 0);
                                *pb += new _guigroesse<>(0, 1, false);
                                *pb += new _guigroesse<>(0.6, 0,false);
                                pb->zeigen();                    
};
#endif
#endif