//grundplatte : _editionwindows.cpp
#include <_global.hpp>
//#ifdef GRUNDPLATTE_UNTER_WINDOWS
//#include <stdio.h>
//#include <stdlib.h>
//#include <conio.h>
#include <_editionwin.hpp>
static WNDPROC s_OldEditProc;


// =============================================  
//  Converts an ANSI-String to a Unicode-String  
// =============================================  
T_String<wchar_t> ANSIToUnicode(T_String<char> const &ansi)  
{  
   T_String<wchar_t>  string;  
   wchar_t            *widestring;  
   bcInt32            size = MultiByteToWideChar(CP_ACP, 0, ansi.Data(), -1, 0, 0);  
   // ----------------------------------------------------------------------------------------  
     
     
   widestring = new wchar_t [size];  
   MultiByteToWideChar(CP_ACP, 0, ansi.Data(), -1, widestring, size);  
   string = widestring;  
   delete[] widestring;  
     
   return(string);  
}  
  
// ===============================================  
//  Converts a Unicode-String to an ANSI-8-String  
// ===============================================  
T_String<char> UnicodeToANSI(T_String<wchar_t> const &unicode)  
{  
   T_String<char>  string;  
   char            *ansistring;  
   bcInt32         size = WideCharToMultiByte(CP_ACP, 0, unicode.Data(), -1, 0, 0, 0, 0);  
   // ----------------------------------------------------------------------------------------  
     
     
   ansistring = new char[size];  
   WideCharToMultiByte(CP_ACP, 0, unicode.Data(), -1, ansistring, size, 0, 0);  
   string = ansistring;  
   delete[] ansistring;  
     
   return(string);  
}  

// =============================================  
//  Converts a UTF-8-String to a Unicode-String  
// =============================================  
T_String<wchar_t> UTF8ToUnicode(T_String<char> const &utf8)  
{  
   T_String<wchar_t>  string;  
   wchar_t            *widestring;  
   bcInt32            size = MultiByteToWideChar(CP_UTF8, 0, utf8.Data(), -1, 0, 0);  
   // ----------------------------------------------------------------------------------------  
     
     
   widestring = new wchar_t [size];  
   MultiByteToWideChar(CP_UTF8, 0, utf8.Data(), -1, widestring, size);  
   string = widestring;  
   delete[] widestring;  
     
   return(string);  
}  
  
T_String<wchar_t> UTF8ToUnicode(T_String<wchar_t> const &utf8)  
{  
   return(utf8);  
}  
  
// =============================================  
//  Converts a Unicode-String to a UTF-8-String  
// =============================================  
 T_String<char> UnicodeToUTF8(T_String<wchar_t> const &unicode)  
{  
   T_String<char>  string;  
   char            *utf8string;  
   bcInt32         size = WideCharToMultiByte(CP_UTF8, 0, unicode.Data(), -1, 0, 0, 0, 0);  
   // ----------------------------------------------------------------------------------------  
     
     
   utf8string = new char[size];  
   WideCharToMultiByte(CP_UTF8, 0, unicode.Data(), -1, utf8string, size, 0, 0);  
   string = utf8string;  
   delete[] utf8string;  
     
   return(string);  
}  
  
T_String<char> UnicodeToUTF8(T_String<char> const &unicode)  
{  
   return(unicode);  
}  






//using namespace GUI;
//******************************************************************************************************************************************************************************************************
//                                                              G U I  G L O B A L E 
//******************************************************************************************************************************************************************************************************
static _listebasis<_guiobjekt> g_listObjects;    // Liste mit allen Objekten
static _liste<_guifenster> g_listWindows;
static unsigned char g_IDTable[OBJECT_MAXID / 8 + 1];
static _guiobjekt*g_foundObject;    // Wird zum Suchen der ID verwendet
static unsigned int g_recursionDepth;  // Wird nur zum Einrücken der Ausgabe verwendet
static bool guierror;      // Wird bei einem Fehler gesetzt (damit er keine Nachrichten mehr verarbeitet)
static _guifensterhaupt*g_mainWindow;  // Zeiger auf das Hauptfenster (Accelerators)

void DumpObjectsRecursive(_guiobjekt*obj){
                                                                //Schreibt alle IDs ins Rekursiv
};
void DumpObjects(){
                                                                //Schreibt alle IDs ins LogFile
};
void loeschenobjekte(){
                                                                //Löscht alle Objekte (wird beim Beenden von Hand gemacht damit der Leak-Finder sich nicht überschlägt...)
                                                                g_listObjects.loeschen();
};
_guiobjekt *findenobjektrekursiv(_listebasis<_guiobjekt> *list,unsigned int id){
                                                                //Sucht ein Objekt rekursiv in den Listen
                                                                _guiobjekt*oit,*object;
                                                               // L->schreiben("Anzahl =",(int)list->anzahl());
                                                                if(list->anfang(oit))do{
                                                                 //ID prüfen
                                                                 if(oit->id()==id) return(oit);
                                                                 //Rekursion
                                                                 object=findenobjektrekursiv(oit,id);
                                                                 if(object) return(object);
                                                                }while(list->naechstes(oit));
                                                                return(0);
};
_guiobjekt*findenobjekt(unsigned int id){
                                                                //Sucht ein Objekt in der Liste (nach ID)
                                                                return(findenobjektrekursiv(&g_listObjects,id));
};
static unsigned int findenfreieid(){
                                                                //Sucht eine freie ID
                                                                for(unsigned int i=OBJECT_STARTID;i<OBJECT_MAXID;i++){
                                                                 if(!(g_IDTable[i >> 3] & (1 << (i & 7)))) {
                                                                  g_IDTable[i >> 3] |= 1 << (i & 7);
                                                                  return(i);
                                                                 };
                                                                };
                                                                throw L"Too many Object-IDs, alter and recompile!";
};
/*
void PrintWindows();
_guifenster*findenfenster(HWND handle);
_guiobjekt*findenobjekt(unsigned int id);
_guiaccelerator*findenaccelerator(unsigned short int vk);

void loeschenobjekte();//Sollte nicht rausgegeben werden, also nur in gui.cpp verwenden!
*/
void bearbeitenereignisse(_guiobjekt*object,_listebasis<_guiereignis>*list,_guiereignisdaten*params){
                                                                //Geht alle Events in der Liste durch
                                                                _liste<_guiobjekt> objektezumloeschen;
                                                                params->objektezumloeschen= &objektezumloeschen;
                                                                object->vorbereitenereignisse(params);
                                                                _guiereignis*eit;
                                                                if(list->anfang(eit))do{
                                                                 eit->setzen(params);
                                                                 eit->ausfuehren();
                                                                }while(list->naechstes(eit));
                                                                object->nachbereitenereignisse(params);
                                                                objektezumloeschen.loeschen();
}
unsigned int nachricht(T_String<> const &text, T_String<> const &title, unsigned int flags){
                                                                _streamwide  stream1, stream2;
                                                                stream1 << text;
                                                                stream2 << title;
                                                                return(nachricht(stream1, stream2, flags));
};
unsigned int nachricht(_streamwide const &text, unsigned int flags){
                                                                return(nachricht(text, _streamwide(L"Info"), flags));
};
unsigned int nachricht(_streamwide const &text, _streamwide const &title, unsigned int flags){
                                                                if(g_mainWindow)
                                                                 return(MessageBox(g_mainWindow->handle(), text.str().c_str(), title.str().c_str(), MB_TOPMOST | MB_SETFOREGROUND | flags));
                                                                else
                                                                 return(MessageBox(0, text.str().c_str(), title.str().c_str(), MB_TOPMOST | MB_SETFOREGROUND | flags));
};
/*
void ShellCommand(T_String<> const &command, T_String<> const &file){//  Führt ein Konsolenkommando aus
                                                                if(!g_mainWindow)
                                                                    {
                                                                        Message(L"ShellCommand() called without MainWindow!", L"Warning", MB_OK | MB_ICONWARNING);
                                                                        return;
                                                                    }
                                                                   
                                                                ShellExecute(g_mainWindow->Handle(), command.Data(), file.Data(), 0, 0, SW_SHOWDEFAULT);
}
*/
void fensterhaupt(_guifensterhaupt*window){
                                                                //  Setzt das Hauptfenster (muss gemacht werden damit die Accelerators funktionieren)
                                                                g_mainWindow = window;
};
void guianimieren(){
                                                                MSG msg;
                                                                while(GetMessage(&msg, 0, 0, 0)){
                                                                 if(g_mainWindow && g_mainWindow->handle() && g_mainWindow->activ() && g_mainWindow->acceleratortabelle()->tabelle()){
                                                                  if(TranslateAccelerator(g_mainWindow->handle(), g_mainWindow->acceleratortabelle()->tabelle(), &msg))
                                                                  continue;
                                                                 };
                                                                 TranslateMessage(&msg);
                                                                 DispatchMessage(&msg);
                                                                };
};
void guiinitialisieren(_guikonfiguration*config){
                                                                //CommonControls initialisieren
                                                                INITCOMMONCONTROLSEX cc;
                                                                cc.dwSize = sizeof(cc);
                                                                cc.dwICC = ICC_TAB_CLASSES | ICC_BAR_CLASSES | ICC_TREEVIEW_CLASSES | ICC_COOL_CLASSES;
                                                                if(!InitCommonControlsEx(&cc)) throw "guiinitialisieren() -> Could not initialize common controls!";
                                                                // Klasse anlegen
                                                                WNDCLASSEX  wc;
                                                                ZeroMemory(&wc, sizeof(wc));
                                                                wc.cbSize=sizeof(wc);
                                                                wc.style=CS_OWNDC|CS_DBLCLKS|CS_VREDRAW|CS_HREDRAW;
                                                                wc.hInstance=GetModuleHandle(0);
                                                                wc.lpszClassName=L"guiklasse";
                                                                wc.lpfnWndProc=WndProc;
                                                                if(config->icon){
                                                                 wc.hIcon = LoadIcon(GetModuleHandle(0), MAKEINTRESOURCE(config->icon));
                                                                 wc.hIconSm = wc.hIcon;//LoadIcon(GetModuleHandle(0), MAKEINTRESOURCE(config->icon));
                                                                };
                                                                if(!RegisterClassEx(&wc)) throw "GUI::RegisterClass() -> Could not register class!";
}
void guideinitialisieren(){
                                                                loeschenobjekte();  // Leak-Finder glücklich machen...
                                                                UnregisterClass(L"guiklasse",GetModuleHandle(0));
};
void guifehler(){
                                                                //  Wird bei einem Fehler aufgerufen (dann lässt er keine Nachrichten mehr durch!!)
                                                                guierror=true;
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I K O N T E X T
//******************************************************************************************************************************************************************************************************
_guikontext::_guikontext(_guifenster*window){
                                                                phwnd=window->handle();
                                                                if(!(phdc=GetDC(phwnd))) throw "Could not get device context!";
};
_guikontext::_guikontext(_guikontext*dc){
                                                                phwnd=0;
                                                                if(!(phdc=CreateCompatibleDC(dc->kontext()))) throw "Could not create memory device context!";
};
_guikontext::~_guikontext(){
                                                                if(!phwnd) DeleteDC(phdc); else ReleaseDC(phwnd,phdc);
};
HDC _guikontext::kontext(){
                                                                //Gibt den Device-Context zurück
                                                                return(phdc);
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I U H R 
//******************************************************************************************************************************************************************************************************
_guiuhr::_guiuhr(unsigned int ms,_guifenster*window):_guiobjekt(L"guiuhr",window){
                                                                pwindow=window;
                                                                SetTimer(window->handle(), id(), ms, 0);
};
_guiuhr::~_guiuhr(){
                                                                if(pwindow->handle()) KillTimer(pwindow->handle(), id());
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I K O N F I G U R A T I O N
//******************************************************************************************************************************************************************************************************
_guikonfiguration::_guikonfiguration(){
                                                                icon=0;
};
_guikonfiguration::~_guikonfiguration(){
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I O B J E K T 
//******************************************************************************************************************************************************************************************************
_guiobjekt::_guiobjekt(T_String<>const & pn,_guiobjekt*parent):_listelistenknotenbasis<_guiobjekt>(parent){
                                                                pname = pn;
                                                                pid = findenfreieid();
                                                                if(!parent) einhaengen(&g_listObjects);  // Globale Liste (wird erst beim Beenden gelöscht)
                                                                if(!parent){
                                                                 L->schreiben("id ohne parent=",(int)pid);
                                                                }else{
                                                                 L->schreiben("id mit parent=",(int)pid);
                                                                 L->schreiben("gioobjekt konstruktor : parent->guiobjektliste anzahl =",(int)parent->_listebasis<_guiobjekt>::anzahl());
                                                                };
                                                                L->schreiben("Texst liste =",(int)g_listObjects.anzahl());
                                                                L->schreiben("Text name =",UnicodeToANSI(pn.Data()).Data());
                                                                //else
                                                                // parent->_listebasis<_guiobjekt>::einhaengen(this);  // Liste des Parents (wird gelöscht wenn das Parent zerstört wird)
};
_guiobjekt::~_guiobjekt(){
                                                                g_IDTable[pid >> 3] &= ~(1 << (pid & 7));
                                                                //GLog << L"_guiobjekt::~_guiobjekt() -> 0x" << this << L"\n";  // FIXME
};
unsigned int _guiobjekt::id() const{
                                                                // Gibt die ID des Objekts zurück
                                                                return(pid);
};
T_String<> _guiobjekt::name(){
                                                                //Gibt den Namen des Objekts zurück
                                                                return(pname);
};
void _guiobjekt::name(T_String<> const &pn){
                                                                //Setzt den Namen des Objekts
                                                                pname=pn;
};
T_String<> _guiobjekt::hilfe(){
                                                                //Gibt den ToolTip zurück (muss überladen werden)
                                                                return(L"ToolTip");
};
void _guiobjekt::bewegen(){
                                                                //Bewegt das Objekt (muss überladen werden)
};
void _guiobjekt::skalieren(){
                                                                //Passt die Größe des Objekts an (inkl. aller Kinder)    
                                                                //Alle Kinder an die richtige Stelle schieben
                                                                _guiobjekt *oit;
                                                                if(_listebasis<_guiobjekt>::anfang(oit))do{
                                                                 oit->skalieren();
                                                                }while(_listebasis<_guiobjekt>::naechstes(oit));
                                                                //for(_guiobjekt *oit = _listebasis<_guiobjekt>::First(); oit; oit = oit->Next()) oit->skalieren();
};
void _guiobjekt::operator += (_guiort<_tg>*pos){
                                                                //Fügt eine neue Position ein
                                                                pos->einhaengen(this);//_listebasis<_guiort<_tg> >::einhaengen(pos);
};
void _guiobjekt::operator += (_guigroesse<_tg>*size){
                                                                //Fügt eine neue Größe ein
                                                                size->einhaengen(this);//_listebasis<_guigroesse<_tg> >::einhaengen(size);
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I A C C E L E R A T O R
//******************************************************************************************************************************************************************************************************
_guiaccelerator::~_guiaccelerator(){
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I A C C E L E R A T O R T A B E L L E
//******************************************************************************************************************************************************************************************************
_guiacceleratortabelle::_guiacceleratortabelle(_guifensterhaupt*parent):_guiobjekt(L"guiacceleratortabelle", parent){
                                                                phaccel=0;
};
_guiacceleratortabelle::~_guiacceleratortabelle(){
                                                                plistAccelerators.loeschen();
                                                                if(phaccel) DestroyAcceleratorTable(phaccel);
};
HACCEL _guiacceleratortabelle::tabelle(){
                                                                //Gibt das Handle auf die Accelerator-Tabelle zurück
                                                                return(phaccel);
};

void _guiacceleratortabelle::erzeugentabelle(){
                                                                //"Registriert" alle Accelerator und erzeugt das Table
                                                                if(!plistAccelerators.erstes()) return;
                                                                ACCEL*accel;
                                                                unsigned int i=0,num=plistAccelerators.anzahl();
                                                                accel=new ACCEL[num];
                                                                _listenknoten<_guiaccelerator>*ait;
                                                                if(plistAccelerators.anfang(ait))do{
                                                                 accel[i++]=ait->objekt()->paccel;
                                                                }while(plistAccelerators.naechstes(ait));
                                                                if(!(phaccel=CreateAcceleratorTable(accel, num))){
                                                                 delete[] accel;
                                                                 throw "Could not create accelerator table!";
                                                                };
                                                                delete[] accel;
                                                                /*
                                                                BCWideStringStream  stream;
                                                                stream << num << L" Accelerators registered\n";
                                                                Log.Write(stream.str());*/
};
//Fügt einen neuen Accelerator ein
void _guiacceleratortabelle::operator+=(_guiaccelerator*accel){
                                                                _listenknoten<_guiaccelerator>*ait;
                                                                
                                                                if(plistAccelerators.anfang(ait))do{
                                                                 if(ait->objekt()->paccel.fVirt == accel->paccel.fVirt && ait->objekt()->paccel.key == accel->paccel.key) throw "Fatal Error: Accelerator already defined!";
                                                                }while(plistAccelerators.naechstes(ait));
                                                                accel->einhaengen(this);//_listebasis<_guiobjekt>::einhaengen(accel);
                                                                plistAccelerators.einhaengen(accel);
};

//******************************************************************************************************************************************************************************************************
//                                                              G U I M E N U E E I N T R A G
//******************************************************************************************************************************************************************************************************
void _guimenueeintrag::name(T_String<> const &pn){
                                                                //Ändert den Namen des Menüitems
                                                                _guiobjekt::name(pn);
                                                                MENUITEMINFO  mii;
                                                                ZeroMemory(&mii, sizeof(mii));
                                                                mii.cbSize = sizeof(mii);
                                                                mii.fMask = MIIM_STRING;
                                                                T_String<>  string = _guiobjekt::name();
                                                                mii.dwTypeData = (LPWSTR)string.Data();
                                                                mii.cch = (UINT)string.Length();
                                                                    
                                                                SetMenuItemInfo(pmenu->handle(), id(), MF_BYCOMMAND, &mii);
};
void _guimenueeintrag::gesetzt(bool check){
                                                                //Setzt ob ein Haken vor dem Menüitem erscheint
                                                                CheckMenuItem(pmenu->handle(), id(), MF_BYCOMMAND | (check ? MF_CHECKED : MF_UNCHECKED));
};
bool _guimenueeintrag::gesetzt(){
                                                                //Gibt zurück ob der Haken des Menüitem gesetzt ist
                                                                MENUITEMINFO  mii;
                                                                ZeroMemory(&mii, sizeof(mii));
                                                                mii.cbSize = sizeof(mii);
                                                                mii.fMask = MIIM_STATE;
                                                                GetMenuItemInfo(pmenu->handle(), id(), MF_BYCOMMAND, &mii);
                                                                return(0 != (mii.fState & MFS_CHECKED));
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I M E N U E B A S I S
//******************************************************************************************************************************************************************************************************
_guimenuebasis::_guimenuebasis(T_String<> const &pn) : _guiobjekt(pn){
                                                                phandle = 0;
};
_guimenuebasis::~_guimenuebasis(){
                                                                if(phandle) DestroyMenu(phandle);
};
void _guimenuebasis::erzeugen(bool popup){
                                                                //Erzeugt das Menü
                                                                if(!popup)
                                                                 phandle=CreateMenu();
                                                                else
                                                                 phandle=CreatePopupMenu();
                                                                if(!phandle) throw "BCMenuBase::Create() -> Could not create menu!";
};
HMENU _guimenuebasis::handle(){
                                                                //Gibt das Menü-Handle zurück
                                                                return(phandle);
};
void _guimenuebasis::operator+=(_guimenue*menu){
                                                                //Fügt ein neues Untermenü ein
                                                                MENUITEMINFO  mii;
                                                                ZeroMemory(&mii, sizeof(mii));
                                                                mii.cbSize=sizeof(mii);
                                                                mii.fMask=MIIM_ID|MIIM_STRING | MIIM_SUBMENU;
                                                                mii.wID=menu->id();
                                                                mii.hSubMenu=menu->handle();
                                                                T_String<> string=menu->name();
                                                                mii.dwTypeData=(LPWSTR)string.Data();
                                                                mii.cch=(UINT)string.Length();
                                                                if(!InsertMenuItem(phandle, GetMenuItemCount(phandle), TRUE, &mii)) throw "Could not insert menu!";
                                                                // In die Liste mit Kindern hängen
                                                                menu->einhaengen(this);//_listebasis<_guiobjekt>::einhaengen(menu);
};
void _guimenuebasis::operator+=(_guimenueeintrag*item){ 
                                                                //Fügt ein neues Menüitem ein
                                                                MENUITEMINFO mii;
                                                                // ---------------------------------------
                                                                ZeroMemory(&mii,sizeof(mii));
                                                                mii.cbSize=sizeof(mii);
                                                                mii.fMask=MIIM_ID|MIIM_STRING;
                                                                mii.wID=item->id();
                                                                T_String<> string=item->_guiobjekt::name();
                                                                mii.dwTypeData=(LPWSTR)string.Data();
                                                                mii.cch=(UINT)string.Length();
                                                                if(!InsertMenuItem(handle(), GetMenuItemCount(phandle), TRUE, &mii))throw "Could not insert menu item!";
                                                                // In die Liste mit Kindern hängen
                                                                item->einhaengen(this);//_listebasis<_guiobjekt>::einhaengen(item);
                                                                item->pmenu=this;
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I M E N U E 
//******************************************************************************************************************************************************************************************************
_guimenue::_guimenue(T_String<> const &pn) : _guimenuebasis(pn){
                                                                erzeugen(true);
};
_guimenue::~_guimenue(){
};
void _guimenue::separator(){
                                                                //Fügt einen Separator ein
                                                                MENUITEMINFO  mii;
                                                                //-------------------------
                                                                ZeroMemory(&mii, sizeof(mii));
                                                                mii.cbSize = sizeof(mii);
                                                                mii.fMask = MIIM_FTYPE;
                                                                mii.fType = MFT_SEPARATOR;
                                                                if(!InsertMenuItem(handle(), GetMenuItemCount(handle()), TRUE, &mii)) throw "Could not insert menu item!";
};
void _guimenue::popup(_guifenster*parent,int x,int y){
                                                                //Zeigt das Menü als Popup-Menü an
                                                                if(parent && handle()){
                                                                 POINT  point;
                                                                 point.x = x;
                                                                 point.y = y;
                                                                 ClientToScreen(parent->handle(), &point);
                                                                 TrackPopupMenu(handle(), TPM_RIGHTBUTTON | TPM_LEFTALIGN | TPM_TOPALIGN, point.x, point.y, 0, parent->handle(), 0);
                                                                };
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I M E N U E L E I S T E
//******************************************************************************************************************************************************************************************************
_guimenueleiste::_guimenueleiste(): _guimenuebasis(L"guimenueleiste"){
                                                                erzeugen(false);
};
_guimenueleiste::~_guimenueleiste(){
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I K N O P F
//******************************************************************************************************************************************************************************************************
_guiknopf::_guiknopf(T_String<> const &pn, _guifenster *parent):_guifenster(pn, parent){

};
_guiknopf::~_guiknopf(){
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I K N O P F C H E C K B A S I S
//******************************************************************************************************************************************************************************************************
_guiknopfcheckbasis::_guiknopfcheckbasis(T_String<> const &pn, _guifenster *parent) : _guiknopf(pn, parent){

};
_guiknopfcheckbasis::~_guiknopfcheckbasis(){
};

bool _guiknopfcheckbasis::gesetzt(){    
                                                                //Gibt zurück ob der Haken gesetzt ist
                                                                return(BST_CHECKED==Message(BM_GETCHECK));
};
void _guiknopfcheckbasis::gesetzt(bool check){
                                                                //Setzt ob der Haken gesetzt ist
                                                                Message(BM_SETCHECK, check ? BST_CHECKED : BST_UNCHECKED);
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I K N O P F C H E C K L I N K S
//******************************************************************************************************************************************************************************************************
_guiknopfchecklinks::~_guiknopfchecklinks(){
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I K N O P F C H E C K R E C H T S
//******************************************************************************************************************************************************************************************************
_guiknopfcheckrechts::~_guiknopfcheckrechts(){
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I K N O P F D R U C K 
//******************************************************************************************************************************************************************************************************
_guiknopfdruck::~_guiknopfdruck(){
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I K N O P F R A D I O 
//******************************************************************************************************************************************************************************************************
_guiknopfradio::~_guiknopfradio(){
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I D I A L O G
//******************************************************************************************************************************************************************************************************
_guidialog::_guidialog(T_String<> const &pn,_guifenster*parent):_guifenster(pn,parent){
                                                                pbesitzerzeichnung=false;
                                                                farbehintergrund(GetSysColor(COLOR_BTNFACE));  // Standardhintergrund für Dialoge
                                                                *this+=new _guiereignisSize<_guidialog>(this, &_guidialog::beiskalieren);
                                                                *this+=new _guiereignisEraseBackground<_guidialog>(this, &_guidialog::beiloeschenhintergrund);
};
_guidialog::~_guidialog(){

};
void _guidialog::besitzerzeichnung(bool od){
                                                                //  Gibt an ob wir den Dialog selber zeichnen wollen (Flackern)
                                                                pbesitzerzeichnung=od;
};
void _guidialog::beiskalieren(_guiereignisdaten*ep){
                                                                // Größe wurde geändert (Dialoge passen sich automatisch an)        
                                                                // Alle Kinder an die richtige Stelle schieben
                                                                _guiobjekt*oit;
                                                                if(_listebasis<_guiobjekt>::anfang(oit))do{
                                                                 oit->bewegen();
                                                                }while(_listebasis<_guiobjekt>::naechstes(oit));
};
void _guidialog::beiloeschenhintergrund(_guiereignisdaten*ep){
                                                                //Hintergrund muss gelöscht werden
                                                                if(pbesitzerzeichnung)return;  // Wir zeichnen selber (so flackert es nicht)
                                                                RECT rect;
                                                                _guikontext hdc(this);
                                                                GetClientRect(handle(), &rect);
                                                                FillRect(hdc.kontext(),&rect,BackgroundBrush());
};

//******************************************************************************************************************************************************************************************************
//                                                              G U I E D I T I E R B A R
//******************************************************************************************************************************************************************************************************
_guieditierbar::_guieditierbar(_guidialogeditierbar*dialog,T_String<> const&section,T_String<> const &pn):_guifensterkind(dialog->fenster()){
                                                                name(pn);
                                                                ptouched = false;
                                                                pDescription = new _guifensterstatischlinks(pn, this);
                                                                *pDescription += new _guigroesse<>(PERCENT_DESCRIPTION,1,false);
                                                                pDescription->addierenstil(WS_BORDER);
                                                                pDescription->farbehintergrund(140, 140, 140);
                                                                pDescription->zentrierentextvertikal(true);
                                                                pDescription->zeigen();
                                                                dialog->addiereneditierbarzusektion(section, this);
};
_guieditierbar::~_guieditierbar(){
};
void _guieditierbar::skalieren(){
                                                                //  Passt die Größe des Editable an
                                                                // Alle Kinder an die richtige Stelle schieben
                                                                _guiobjekt*oit;
                                                                if(_listebasis<_guiobjekt>::anfang(oit))do{
                                                                 oit->bewegen();
                                                                }while(_listebasis<_guiobjekt>::naechstes(oit));
};
bool _guieditierbar::beruehrt() const{ 
                                                                return(ptouched); 
};
void _guieditierbar::beruehrt(bool touched){
                                                                ptouched=touched; 
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I E D I T I E R B A R S E K T I O N 
//******************************************************************************************************************************************************************************************************
_guieditierbarsektion::_guieditierbarsektion(_guidialogeditierbar*dialog,T_String<> const &pn):_guiknopf(L"+ " + pn, dialog->fenster()){
                                                                erzeugen(WS_CHILD | WS_VISIBLE | BS_LEFT | BS_FLAT, 0, L"BUTTON");
                                                                *this += new _guiereignisCommand<_guieditierbarsektion>(this, &_guieditierbarsektion::beibefehl);
                                                                prealname=pn;
                                                                popen=false;
};
_guieditierbarsektion::~_guieditierbarsektion(){
                                                                peditables.aushaengen();
};                                                                
bool _guieditierbarsektion::offen()const{
                                                                //Holt ob die Sektion geöffnet ist
                                                                return(popen);
};
void _guieditierbarsektion::offen(bool o){
                                                                //Setzt ob die Sektion geöffnet ist
                                                                popen=!o;
                                                                beibefehl(0);
};
_guieditierbar *_guieditierbarsektion::editierbar(T_String<> const &pn){
                                                                //Holt ein Editable aus der Sektion
                                                                _listenknoten<_guieditierbar>*node;
                                                                //----------------------------------
                                                                if(peditables.anfang(node))do{
                                                                 if(pn == node->objekt()->_guiobjekt::name()) return(node->objekt());
                                                                }while(peditables.naechstes(node));
                                                                //throw L"BCEditableSection::Editable() -> Editable '" + name + L"' not found in Section (" + m_realname + L")!";
                                                                return(0);
};
void _guieditierbarsektion::beibefehl(_guiereignisdaten*){
                                                                //  Button wurde gedrückt
                                                                T_String<> pn=_guiobjekt::name();
                                                                // ---------------------------------------------------
                                                                popen=!popen;
                                                                if(popen)
                                                                 pn.ReplaceChar(0, L'-');
                                                                else{
                                                                 pn.ReplaceChar(0, L'+');
                                                                 _listenknoten<_guieditierbar>*node;
                                                                 if(peditables.anfang(node))do{
                                                                  node->objekt()->verstecken();
                                                                 }while(peditables.naechstes(node));
                                                                 name(pn);
                                                                };
                                                                // Alle Editables neu einsortieren, weil jetzt ja wieder alles verrutscht ist
                                                                besitzer()->Message(WM_SIZE);
}

//******************************************************************************************************************************************************************************************************
//                                                              G U I D I A L O G E D I T I E R B A R
//******************************************************************************************************************************************************************************************************
_guidialogeditierbar::_guidialogeditierbar(T_String<> const &pn,_guifenster*parent):_guidialog(pn,parent){
                                                                erzeugen(WS_CAPTION|WS_SYSMENU|WS_THICKFRAME,WS_EX_TOOLWINDOW);
                                                                pdivide = 0.5;
                                                                *this += new _guiereignisPaint<_guidialogeditierbar>(this, &_guidialogeditierbar::beizeichnen);
                                                                *this += new _guiereignisMouseWheel<_guidialogeditierbar>(this, &_guidialogeditierbar::beimausrad);
                                                                // Inneres Fenster mit Bildlaufleisten
                                                                pwindow = new _guifensterkind(this);
                                                                pwindow->addierenstil(0, WS_EX_CLIENTEDGE);
                                                                *pwindow+=new _guigroesse<_tg>(1, 1, false);
                                                                *pwindow+=new _guigroesse<_tg>(0, -35);
                                                                *pwindow+=new _guiereignisSize<_guidialogeditierbar>(this, &_guidialogeditierbar::beiskalieren);
                                                                *pwindow+=new _guiereignisPaint<_guidialogeditierbar>(this, &_guidialogeditierbar::beizeichnen);
                                                                *pwindow+=new _guiereignisEraseBackground<_guidialogeditierbar>(this, &_guidialogeditierbar::beiloeschenhintergrund);
                                                                *pwindow+=new _guiereignisMouseWheel<_guidialogeditierbar>(this, &_guidialogeditierbar::beimausrad);
                                                                pwindow->farbehintergrund(140,140,140);
                                                                pwindow->zeigen();
                                                                   
                                                                // Scrollbar muss wieder neu erzeugt werden...
                                                                int sbwidth = GetSystemMetrics(SM_CXHSCROLL);
                                                                pscrollBar = new _guiscrollbarvertikal(pwindow);
                                                                pscrollBar->einhaengen(this);//_listebasis<_guiobjekt>::einhaengen(pscrollBar);  // In diese Liste einhängen, damit sie nicht bei den Editables gelöscht wird...
                                                                *pscrollBar+=new _guiort<_tg>(1, 0, false);
                                                                *pscrollBar+=new _guiort<_tg>(-sbwidth, 0);
                                                                *pscrollBar+=new _guigroesse<_tg>(0, 1, false);
                                                                *pscrollBar+=new _guigroesse<_tg>(sbwidth, 0);
                                                                //pscrollBar->StepSize(HEIGHT_EDITABLE);
                                                                pscrollBar->zeigen();
                                                                   
                                                                // OK, Übernehmen und Abbrechen
                                                                _guiknopfdruck*button;
                                                                   
                                                                // OK
                                                                button = new _guiknopfdruck(L"OK", this, new _guiereignisCommand<_guidialogeditierbar>(this, &_guidialogeditierbar::knopfok));
                                                                *button += new _guiort<_tg>(1, 1, false);
                                                                *button += new _guiort<_tg>(-86 - 86 - 86, -28);
                                                                *button += new _guigroesse<_tg>(80, 22);
                                                                button->zeigen();
                                                                   
                                                                // Übernehmen
                                                                button = new _guiknopfdruck(L"Übernehmen", this, new _guiereignisCommand<_guidialogeditierbar>(this, &_guidialogeditierbar::knopfuebernehmen));
                                                                *button += new _guiort<_tg>(1, 1, false);
                                                                *button += new _guiort<_tg>(-86 - 86, -28);
                                                                *button += new _guigroesse<_tg>(80, 22);
                                                                button->zeigen();
                                                                   
                                                                // Abbrechen
                                                                button = new _guiknopfdruck(L"Abbrechen", this, new _guiereignisCommand<_guidialogeditierbar>(this, &_guidialogeditierbar::knopfabbruch));
                                                                *button += new _guiort<_tg>(1, 1, false);
                                                                *button += new _guiort<_tg>(-86, -28);
                                                                *button += new _guigroesse<_tg>(80, 22);
                                                                button->zeigen();
};

_guidialogeditierbar::~_guidialogeditierbar(){
                                                                psectionList.aushaengen();
}
_guifensterkind*_guidialogeditierbar::fenster(){ 
                                                                return(pwindow); 
};
_guiscrollbarvertikal*_guidialogeditierbar::scrollbar(){ 
                                                                return(pscrollBar); 
};
_guieditierbarsektion *_guidialogeditierbar::sektion(T_String<> const &section){
                                                                //Gibt eine (vorhandene) Sektion zurück
                                                                _listenknoten<_guieditierbarsektion>*node;
                                                                //----------------------------------------
                                                                if(psectionList.anfang(node))do{
                                                                 if(node->objekt()->prealname==section) return(node->objekt());
                                                                }while(psectionList.naechstes(node));
                                                                throw L"_guidialogeditierbar::Section() -> Section not found (" + section + L")!";
};
void _guidialogeditierbar::addiereneditierbarzusektion(T_String<> const &section,_guieditierbar*editable){
                                                                //Fügt ein Editable in eine Sektion ein
                                                                sektion(section)->peditables.einhaengen(editable);
};
void _guidialogeditierbar::addierensektion(T_String<> const &section){
                                                                //Fügt eine neue Sektion hinzu
                                                                psectionList.einhaengen(new _guieditierbarsektion(this,section));
};
void _guidialogeditierbar::loeschensektion(){
                                                                //Löscht alle Sektionen
                                                                _listenknoten<_guieditierbarsektion>*node;
                                                                //----------------------------------------
                                                                if(psectionList.anfang(node))do{
                                                                 node->objekt()->peditables.loeschen();
                                                                }while(psectionList.naechstes(node));
                                                                psectionList.loeschen();
};
void _guidialogeditierbar::zeigen(){
                                                                _guifenster::zeigen();
                                                                pwindow->Message(WM_SIZE);
};
void _guidialogeditierbar::neusetzen(T_String<> const &pn){
                                                                //Resettet den Dialog (löscht alle Editables; einmal vor dem Editieren aufrufen)
                                                                _listenknoten<_guieditierbarsektion>*node;
                                                                //-----------------------------------------
                                                                // Alle Objekte (Editables) löschen   
                                                                if(psectionList.anfang(node))do{
                                                                 node->objekt()->peditables.loeschen();
                                                                }while(psectionList.naechstes(node));
                                                                // Neuen Namen für den Dialog setzen
                                                                name(pn);
}
void _guidialogeditierbar::beiskalieren(_guiereignisdaten*ep){
                                                                //Größe wurde geändert
                                                                _listenknoten<_guieditierbarsektion>*sectionnode;
                                                                _listenknoten<_guieditierbar>*editablenode;
                                                                _guirechteck<int> const rect=pwindow->ClientRect<int>();
                                                                _guirechteck<int> const scrollrect=pscrollBar->WindowRect<int>();
                                                                int width, num = 0, y = -pscrollBar->ort();
                                                                //----------------------------------------------
                                                                num=psectionList.anzahl();
                                                                width=rect.breite()-scrollrect.breite();
                                                                if(psectionList.anfang(sectionnode))do{   
                                                                 //Sektion an die richtige Stelle schieben
                                                                 sectionnode->objekt()->bewegen(0, y, width, HEIGHT_EDITABLE);
                                                                 y+=HEIGHT_EDITABLE;
                                                                 // Falls die Sektion geöffnet ist, alles anzeigen
                                                                 if(sectionnode->objekt()->offen()){
                                                                  if(sectionnode->objekt()->peditables.anfang(editablenode))do{
                                                                   editablenode->objekt()->bewegen(SPACE_EDITABLE,y,width-SPACE_EDITABLE,HEIGHT_EDITABLE);
                                                                   editablenode->objekt()->skalieren();
                                                                   editablenode->objekt()->zeigen();
                                                                   y+=HEIGHT_EDITABLE;
                                                                   num++;
                                                                  }while(sectionnode->objekt()->peditables.naechstes(editablenode));
                                                                 };
                                                                }while(psectionList.naechstes(sectionnode));   
                                                                if(ep){
                                                                 pscrollBar->bereich(0, (num + 1) * HEIGHT_EDITABLE);
                                                                 pscrollBar->skalieren();
                                                                };
};
void _guidialogeditierbar::beizeichnen(_guiereignisdaten*ep){
                                                                //Fenster wurde neu gezeichnet (hier onSize aufrufen, da es nur um die ScrollBars geht)
                                                                beiskalieren(0);
};
void _guidialogeditierbar::beiloeschenhintergrund(_guiereignisdaten*ep){
                                                                //Hintergrund muss gelöscht werden
                                                                RECT rect;
                                                                _guikontext hdc(pwindow);
                                                                // --------------------------------------------------
                                                                GetClientRect(pwindow->handle(), &rect);
                                                                FillRect(hdc.kontext(), &rect, pwindow->BackgroundBrush());
};
void _guidialogeditierbar::beimausrad(_guiereignisdaten *ep){
                                                                pscrollBar->ort(pscrollBar->ort() - ep->maus.zDelta * HEIGHT_EDITABLE);
};
void _guidialogeditierbar::knopfok(_guiereignisdaten*ep){
                                                                //OK-Button, Muss überladen werden
};
void _guidialogeditierbar::knopfuebernehmen(_guiereignisdaten*ep){
                                                                //Übernehmen-Button, Muss überladen werden
};
void _guidialogeditierbar::knopfabbruch(_guiereignisdaten*ep){
                                                                //Abbrechen-Button
                                                                verstecken();
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I D I A L O G D A T E I
//******************************************************************************************************************************************************************************************************
_guidialogdatei::_guidialogdatei(_guifenster*parent) : _guidialogmodal(L"guidialogdatei", parent){
                                                                ZeroMemory(&ofn, sizeof(ofn));
                                                                ZeroMemory(pfileTitle, sizeof(pfileTitle));
                                                                ZeroMemory(pfileName, sizeof(pfileName));
                                                                ofn.lStructSize=sizeof(OPENFILENAME);
                                                                ofn.hwndOwner=parent->handle();
                                                                ofn.hInstance=GetModuleHandle(0);
                                                                ofn.nMaxFile=1024;
                                                                ofn.nMaxFileTitle=1024;
                                                                ofn.lpstrFileTitle=pfileTitle;
                                                                ofn.lpstrFile=pfileName;
};
_guidialogdatei::~_guidialogdatei(){
																loeschenfilter();
};
T_String<> _guidialogdatei::dateititel() const{
                                                                //Gibt den Titel der ausgewählten Datei zurück
                                                                return(pfileTitle);
};
T_String<> _guidialogdatei::dateiname() const{
                                                                //Holt/Setzt den kompletten Namen der ausgewählten Datei
                                                                return(pfileName);
};
void _guidialogdatei::dateiname(T_String<> const &fn){
                                                                wcscpy(pfileName,fn.Data());
};
void _guidialogdatei::loeschenfilter(){
                                                                //Löscht alle Filter
                                                                pfilterList.loeschen();
};
void _guidialogdatei::addierenfilter(T_String<> const &pn, T_String<> const &ext){
                                                                //Fügt einen Dateifilter hinzu
                                                                pfilterList.einhaengen(new _guidialogdateifilter(pn, ext));
};
void _guidialogdatei::erzeugenfilter(std::vector<wchar_t> &buffer){
                                                                //Erzeugt den Buffer mit dem Filterstring (Null zwischen den Elementen, und 2 Nullen am Ende)
                                                                wchar_t temp[2] = L"\0";
                                                                _listenknoten<_guidialogdateifilter>*node;
                                                                if(pfilterList.anfang(node))do{   
                                                                 buffer.insert(buffer.end(), node->objekt()->pname.Data(),node->objekt()->pname.Data() + node->objekt()->pname.Length());
                                                                 buffer.insert(buffer.end(), temp, temp + 1);
                                                                 buffer.insert(buffer.end(), node->objekt()->pextension.Data(),node->objekt()->pextension.Data() + node->objekt()->pextension.Length());
                                                                 buffer.insert(buffer.end(), temp, temp + 1);
                                                                }while(pfilterList.naechstes(node));   
                                                                // Ende "terminieren"
                                                                buffer.insert(buffer.end(), temp, temp + 1);
};
void _guidialogdatei::standarderweiterung(T_String<> const &ext){
                                                                //Setzt die Default-Extension
                                                                pdefaultExtension=ext;
                                                                ofn.lpstrDefExt=pdefaultExtension.Data();
};
bool _guidialogdatei::oeffnen(T_String<> const &dialogname){
                                                                //Zeigt den Öffnen-Dialog an
                                                                std::vector<wchar_t> buffer;
                                                                erzeugenfilter(buffer);
                                                                ofn.lpstrFilter=&buffer[0];
                                                                ofn.lpstrTitle=dialogname.Data();
                                                                ofn.Flags=OFN_CREATEPROMPT;
                                                                wchar_t dir[1024];
                                                                GetCurrentDirectory(1024,dir);
                                                                BOOL ret=GetOpenFileName(&ofn);
                                                                SetCurrentDirectory(dir);
                                                                return(0!=ret);
};
bool _guidialogdatei::speichern(T_String<> const &dialogname){
                                                                //Zeigt den Speichern-Dialog an
                                                                std::vector<wchar_t>  buffer;
                                                                erzeugenfilter(buffer);
                                                                ofn.lpstrFilter=&buffer[0];
                                                                ofn.lpstrTitle=dialogname.Data();
                                                                ofn.Flags=OFN_CREATEPROMPT|OFN_OVERWRITEPROMPT;
                                                                wchar_t dir[1024];
                                                                GetCurrentDirectory(1024,dir);
                                                                BOOL ret=GetSaveFileName(&ofn);
                                                                SetCurrentDirectory(dir);
                                                                return(0!=ret);
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I D I A L O G M O D A L 
//******************************************************************************************************************************************************************************************************
_guidialogmodal::_guidialogmodal(T_String<> const &pn,_guifenster*parent) : _guidialog(pn, parent){
                                                                erzeugen(WS_CAPTION|WS_SYSMENU);
};
_guidialogmodal::~_guidialogmodal(){
};
void _guidialogmodal::zeigen(){
                                                                besitzer()->ausschalten();
                                                                _guifenster::zeigen();
};
void _guidialogmodal::verstecken(){
                                                                //  Dialog verbergen
                                                                besitzer()->einschalten();
                                                                _guifenster::verstecken();
};
//******************************************************************************************************************************************************************************************************
//                                                               F E N S T E R  -  F U N K T I O N E N
//******************************************************************************************************************************************************************************************************
_guifenster*findenfenster(HWND handle){
                                                                //Sucht ein Fenster in der Liste
                                                                _listenknoten<_guifenster>*wit;
                                                                if(g_listWindows.anfang(wit))do{
                                                                 if(wit->objekt()->handle()==handle) return(wit->objekt());
                                                                }while(g_listWindows.naechstes(wit));
                                                                return(0);
};
void PrintWindows(){
                                                                //Schreibt den Status der Fenster in die Logdatei
                                                                /*Log.Write("\n%d Windows:\n", g_listWindows.Size());
                                                                for(T_ListNode<BCWindow> *wit = g_listWindows.First(); wit; wit = wit->Next())
                                                                Log.Write("0x%08x: Name = %s, HWND = 0x%08x\n", wit->Data(), wit->Data()->BCObject::Name().Data(), wit->Data()->Handle());*/
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I F E N S T E R
//******************************************************************************************************************************************************************************************************
_guifenster::_guifenster(T_String<> const &pn,_guifenster*parent,_guimenueleiste*menu):_guiobjekt(pn,parent){
                                                                g_listWindows.einhaengen(this);
                                                                phandle=0;
                                                                pparent=parent;
                                                                pmenu=menu;
                                                                pcursor=LoadCursor(0, IDC_ARROW);
                                                                farbetext(0,0,0);
                                                                farbehintergrund(255,255,255);
                                                                puseBeginPaint = true;
                                                                groessemaximal(_guigroesse<int>(10000, 10000));  // Irgendein großer Wert...
};
_guifenster::~_guifenster(){
                                                                zerstoeren();
};
void _guifenster::erzeugen(unsigned int style,unsigned int exstyle,T_String<> const &classname){
                                                                //Erzeugt das Fenster
                                                                if(phandle) return;  // Anscheinend schon erzeugt worden
                                                                HWND  hwnd=0;
                                                                HMENU hmenu=0;
                                                                if(pparent) hwnd = pparent->handle();
                                                                if(pmenu) hmenu = pmenu->handle();
                                                                if(style & WS_CHILD) hmenu=(HMENU)(unsigned int)id();
                                                                style|=WS_CLIPCHILDREN|WS_CLIPSIBLINGS;  // Die wollen wir immer
                                                                if(!(phandle = CreateWindowEx(exstyle,classname.Data(),_guiobjekt::name().Data(), style, 0, 0, 0, 0, hwnd, hmenu, GetModuleHandle(0), 0))) throw "_guifenster::_guifenster() -> Could not create window!";
                                                                // Standard-Font setzen
                                                                Message(WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), 1);
};
HWND _guifenster::handle(){
                                                                //Gibt das Fensterhandle zurück
                                                                return(phandle);
};
_guifenster*_guifenster::besitzer(){
                                                                //Gibt das Parent zurück
                                                                return(pparent);
};
_guimenueleiste*_guifenster::menue(){
                                                                //Gibt das Menü zurück
                                                                return(pmenu);
};

void _guifenster::menue(_guimenueleiste*menu){
                                                                //Setzt das Menü
                                                                pmenu = menu;
                                                                if(phandle){
                                                                 if(menu) SetMenu((HWND)phandle,menu->handle()); else SetMenu((HWND)phandle,0);
                                                                };
};
HCURSOR _guifenster::cursor(){
                                                                //Gibt den Cursor des Fensters zurück
                                                                return(pcursor);
};
void _guifenster::cursor(LPCTSTR res){
                                                                //Setzt den Cursor des Fensters
                                                                pcursor = LoadCursor(0, res);
};
void _guifenster::name(T_String<> const &pn){
                                                                //Setzt den Namen des Fensters
                                                                pname=pn;
                                                                if(phandle){
                                                                 //T_String<>  widename = System::UTF8ToWide(name);
                                                                 //SetWindowtext(phandle, widename.Data());
                                                                 SetWindowText(phandle, _guiobjekt::name().Data());
                                                                };
};
_vektor2<unsigned int> _guifenster::ort() const{
																RECT r;
																GetWindowRect(phandle,&r);
																return(_vektor2<unsigned int>(r.left,r.top));
};
unsigned int _guifenster::farbetext(){
                                                                //Gibt die Textfarbe des Fensters zurück
                                                                return(pcolortext);
};
void _guifenster::farbetext(unsigned int rgb){
                                                                //Setzt die Textfarbe des Fensters
                                                                pcolortext=rgb;
};
void _guifenster::farbetext(unsigned char r, unsigned char g, unsigned char b){
                                                                pcolortext=RGB(r,g,b);
};
void _guifenster::farbehintergrund(unsigned int rgb){
                                                                //Setzt die Hintergrundfarbe des Fensters
                                                                if(pbrushBackground) DeleteObject(pbrushBackground);
                                                                pbrushBackground=CreateSolidBrush(rgb);
};
void _guifenster::farbehintergrund(unsigned char r, unsigned char g,unsigned char b){
                                                                if(pbrushBackground) DeleteObject(pbrushBackground);
                                                                pbrushBackground = CreateSolidBrush(RGB(r, g, b));
};
HBRUSH _guifenster::BackgroundBrush(){
                                                                //Gibt den Pinsel zum Löschen des Hintergrunds raus
                                                                return(pbrushBackground);
};
bool _guifenster::UseBeginPaint(){
                                                                //Gibt zurück ob wir BeginPaint() / EndPaint() verwenden
                                                                return(puseBeginPaint);
};
void _guifenster::UseBeginPaint(bool use){
                                                                //Setzt ob wir BeginPaint() / EndPaint() verwenden
                                                                puseBeginPaint=use;
};

//Gibt den aktuellen Style des Fensters zurück
unsigned int _guifenster::stil(){
                                                                if(phandle) return(GetWindowLong(phandle, GWL_STYLE));
                                                                return(0);
};
unsigned int _guifenster::stilerweitert(){
                                                                //Gibt den erweiterten Style des Fensters zurück
                                                                if(phandle) return(GetWindowLong(phandle, GWL_EXSTYLE));
                                                                return(0);
};
void _guifenster::stil(unsigned int style, unsigned int exstyle){
                                                                //Ändert den Style des Fensters
                                                                if(phandle){
                                                                 SetWindowLong(phandle,GWL_STYLE,style);
                                                                 SetWindowLong(phandle,GWL_EXSTYLE,exstyle);
                                                                };
};
void _guifenster::addierenstil(unsigned int style, unsigned int exstyle){
                                                                //Fügt einen Style hinzu
                                                                unsigned int  oldstyle = stil(), oldexstyle = stilerweitert();
                                                                stil(oldstyle | style, oldexstyle | exstyle);
};
void _guifenster::loeschenstil(unsigned int style, unsigned int exstyle){
                                                                //Entfernt einen Style
                                                                unsigned int  oldstyle = stil(), oldexstyle = stilerweitert();
                                                                stil(oldstyle & (~style), oldexstyle & (~exstyle));
};
void _guifenster::EnableDrag(bool enable){
                                                                //Setzt ob das Fenster Dateien per Drag-and-Drop akzeptiert
                                                                if(phandle) DragAcceptFiles(phandle, enable);
};
LRESULT _guifenster::Message(UINT message, WPARAM wParam, LPARAM lParam){
                                                                //  Schickt eine Nachricht an das Fenster
                                                                if(phandle)return(SendMessage(phandle, message, wParam, lParam));
                                                                return(0);
};
unsigned int _guifenster::breiteminimal(){
                                                                //Gibt die minimal erlaubte Breite des Fensters zurück
                                                                return(psizeMinimal.breite());
};
unsigned int _guifenster::hoeheminimal(){
                                                                //Gibt die minimal erlaubte Höhe des Fensters zurück
                                                                return(psizeMinimal.hoehe());
};
void _guifenster::groesseminimal(_guigroesse<int> const &size){
                                                                //Setzt die Minimalgröße
                                                                psizeMinimal=size;
};
unsigned int _guifenster::breitemaximal(){
                                                                //Gibt die maximal erlaubte Breite des Fensters zurück
                                                                return(psizeMaximal.breite());
};
unsigned int _guifenster::hoehemaximal(){
                                                                //Gibt die maximal erlaubte Höhe des Fensters zurück
                                                                return(psizeMaximal.hoehe());
};
void _guifenster::groessemaximal(_guigroesse<int> const &size){
                                                                //Setzt die Maximalgröße
                                                                psizeMaximal=size;
};
void _guifenster::zeigen(){
                                                                //Zeigt das Fenster an
                                                                if(phandle) ShowWindow(phandle,SW_SHOW);
};
void _guifenster::verstecken(){
                                                                //Verbirgt das Fenster
                                                                if(phandle){
                                                                 if(pparent) pparent->activieren();
                                                                 ShowWindow(phandle,SW_HIDE);
                                                                };
};
void _guifenster::minimieren(){
                                                                //Minimiert das Fenster
                                                                if(phandle) ShowWindow(phandle,SW_MINIMIZE);
};
void _guifenster::maximieren(){
                                                                //Maximiert das Fenster
                                                                if(phandle) ShowWindow(phandle,SW_SHOWMAXIMIZED);
};

void _guifenster::einschalten(){
                                                                //Aktiviert das Fenster
                                                                if(phandle) EnableWindow(phandle, TRUE);
};
void _guifenster::ausschalten(){
                                                                //Deaktiviert das Fenster
                                                                if(phandle) EnableWindow(phandle, FALSE);
};
void _guifenster::activieren(){
                                                                //Aktiviert das Fenster
                                                                if(phandle) SetActiveWindow(phandle);
};
bool _guifenster::activ(){
                                                                //Gibt zurück ob das Fenster gerade aktiv ist
                                                                return(phandle==GetActiveWindow());
};
bool _guifenster::eingeschaltet(){
                                                                //Gibt zurück ob das Fenster aktiviert ist (d.h. Maus- und Tastaturnachrichten sind gesperrt)
                                                                if(!phandle) return(false);
                                                                return(true==IsWindowEnabled(phandle));
};
bool _guifenster::sichtbar(){
                                                                //Gibt zurück ob das Fenster im Moment sichtbar ist
                                                                if(!phandle) return(false);
                                                                return(true==IsWindowVisible(phandle));
};
void _guifenster::fokus(){
                                                                if(phandle) SetFocus(phandle);
};
bool _guifenster::hatfokus(){
                                                                //Gibt zurück ob das Fenster den Eingabefokus hat
                                                                return(phandle==GetFocus());
};
void _guifenster::schliessen(){
                                                                //Schließt das Fenster
                                                                if(phandle) SendMessage(phandle, WM_CLOSE, 0, 0);
};
//  Zerstört das Fenster
void _guifenster::zerstoeren(){
                                                                //GLog << L"Window 0x" << this << L" destroyed, Name = " << _guiobjekt::Name().Data() << L", HWND = 0x" << phandle << L"\n";
                                                                // Alle Kinder löschen (muss vorher geschehen, damit die Handle noch gültig sind)
                                                                _listebasis<_guiobjekt>::loeschen();
                                                                // Pinsel vom Hintergrund löschen
                                                                if(pbrushBackground){
                                                                 DeleteObject(pbrushBackground);
                                                                 pbrushBackground = 0;
                                                                };
                                                                // Fenster selber zerstören
                                                                if(phandle){
                                                                 //GLog << L"DestroyWindow()\n";
                                                                 //if(0 == DestroyWindow(phandle))
                                                                 //GLog << L"FAILED! (" << GetLastError() << L")\n";
                                                                 DestroyWindow(phandle);
                                                                 phandle = 0;
                                                                };
                                                                //g_hashWindows.Delete(this, false);
                                                                _listenknoten<_guifenster>*git;
                                                                if(g_listWindows.suchen(this,git)){
                                                                 delete git;
                                                                };
                                                                //g_listWindows.DeleteObject(this, false);
};
void _guifenster::bewegen(){
                                                                //  Bewegt das Fenster (überladen vom Objekt)
                                                                if(!pparent)throw L"_guifenster::Move() called, but parent == 0!";
                                                                _tg x=0,y=0,w=0,h=0;
                                                                _guirechteck<_tg> rect=pparent->ClientRect<_tg>();
                                                                _guiort<_tg>*pit;
                                                                _guigroesse<_tg>*sit;
                                                                // Position rausfinden
                                                                if(_listebasis<_guiort<_tg> >::anfang(pit))do{
                                                                 if(pit->absolut()){
                                                                  x+=pit->x();
                                                                  y+=pit->y();
                                                                 }else{
                                                                  x+=rect.breite()*pit->x();
                                                                  y+=rect.hoehe()*pit->y();
                                                                 };
                                                                }while(_listebasis<_guiort<_tg> >::naechstes(pit));
                                                                // Größe rausfinden
                                                                if(_listebasis<_guigroesse<_tg> >::anfang(sit))do{
                                                                 if(sit->absolut()){
                                                                  w+=sit->breite();
                                                                  h+=sit->hoehe();
                                                                 }else{
                                                                  w+=rect.breite()*sit->breite();
                                                                  h+=rect.hoehe()*sit->hoehe();
                                                                 };
                                                                }while(_listebasis<_guigroesse<_tg> >::naechstes(sit));
                                                                   
                                                                bewegen((int)(x + 0.5), (int)(y + 0.5), (int)(w + 0.5), (int)(h + 0.5));
};
void _guifenster::bewegen(int x,int y,int w,int h,bool repaint){
                                                                //Bewegt das Fenster
                                                                if(phandle){
                                                                 if(w < psizeMinimal.breite()) w = psizeMinimal.breite();
                                                                 if(h < psizeMinimal.hoehe()) h = psizeMinimal.hoehe();
                                                                 if(w > psizeMaximal.breite()) w = psizeMaximal.breite();
                                                                 if(h > psizeMaximal.hoehe()) h = psizeMaximal.hoehe();
                                                                 MoveWindow(phandle, x, y, w, h, repaint);
                                                                };
};
void _guifenster::zentrieren(int w,int h,bool repaint){
                                                                //Zentriert das Fenster
                                                                if(phandle){
                                                                 if(w < psizeMinimal.breite()) w=psizeMinimal.breite();
                                                                 if(h < psizeMinimal.hoehe()) h=psizeMinimal.hoehe();
                                                                 if(w > psizeMaximal.breite()) w=psizeMaximal.breite();
                                                                 if(h > psizeMaximal.hoehe()) h=psizeMaximal.hoehe();
                                                                 _guirechteck<int> rect=DesktopRect<int>();
                                                                 RECT rect2;
                                                                 SetRect(&rect2, 0, 0, w, h);
                                                                 AdjustWindowRectEx(&rect2, GetWindowLong(handle(), GWL_STYLE), pmenu ? true : false, GetWindowLong(handle(), GWL_EXSTYLE));
                                                                 rect2.left=abs(rect2.right  - rect2.left);
                                                                 rect2.top=abs(rect2.bottom - rect2.top);
                                                                 int x=rect.links()+(rect.breite()>>1);
                                                                 int y=rect.oben()+(rect.hoehe()>>1);
                                                                 MoveWindow(phandle,x-(rect2.left >> 1),y-(rect2.top>>1),rect2.left,rect2.top,repaint);
                                                                };
};
void _guifenster::neuzeichnen(){
                                                                //  Zeichnet das komplette Fenster neu
                                                                if(phandle){
                                                                 InvalidateRect(phandle, 0, TRUE);
                                                                 UpdateWindow(phandle);
                                                                };
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I F E N S T E R K I N D
//******************************************************************************************************************************************************************************************************
_guifensterkind::_guifensterkind(_guifenster*parent):_guifenster(L"guifenster",parent){
                                                                erzeugen(WS_CHILD);
};
_guifensterkind::~_guifensterkind(){
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I F E N S T E R H A U P T
//******************************************************************************************************************************************************************************************************
_guifensterhaupt::_guifensterhaupt(T_String<> const &pn,bool keinemenueknoepfe,_guimenueleiste*menu) : _guifenster(pn,0,menu){
                                                                if(keinemenueknoepfe) erzeugen(0); else erzeugen(WS_OVERLAPPEDWINDOW);
                                                                paccelTable = new _guiacceleratortabelle(this);
                                                                fensterhaupt(this);  // Für die Accelerators
};
_guifensterhaupt::~_guifensterhaupt(){
};
_guiacceleratortabelle *_guifensterhaupt::acceleratortabelle(){
                                                                //Gibt das Accelerator-Table zurück
                                                                return(paccelTable);
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I F E N S T E R S P L A S H 
//******************************************************************************************************************************************************************************************************
_guifenstersplash::_guifenstersplash(bcUInt32 bitmapid) : _guifenster(L"guifenstersplash"){
                                                                BITMAP bmp;
                                                                unsigned int  style =WS_POPUP, exstyle=WS_EX_TOOLWINDOW|WS_EX_CLIENTEDGE;
                                                                erzeugen(style,exstyle);
                                                                pbmp = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(bitmapid));
                                                                GetObject(pbmp, sizeof(BITMAP), &bmp);
                                                                _guirechteck<int>  rect = DesktopRect<int>();
                                                                RECT rect2;
                                                                SetRect(&rect2,0,0,bmp.bmWidth, bmp.bmHeight);
                                                                AdjustWindowRectEx(&rect2, style, FALSE, exstyle);
                                                                rect2.left = rect2.right  - rect2.left;
                                                                rect2.top  = rect2.bottom - rect2.top;
                                                                bewegen(rect.links() + (rect.breite()  >> 1) - (rect2.left >> 1),
                                                                        rect.oben()  + (rect.hoehe() >> 1) - (rect2.top  >> 1), rect2.left, rect2.top);
                                                                *this += new _guiereignisEraseBackground<_guifenstersplash>(this, &_guifenstersplash::beiloeschenhintergrund);
};
_guifenstersplash::~_guifenstersplash(){
                                                                if(pbmp) DeleteObject(pbmp);
};
void _guifenstersplash::beiloeschenhintergrund(_guiereignisdaten*ep){
                                                                //Hintergrund muss gelöscht werden
                                                                HBITMAP hOldBmp;
                                                                _guikontext hDC(this),hMemoryDC(&hDC);
                                                                hOldBmp=(HBITMAP)SelectObject(hMemoryDC.kontext(),pbmp);
                                                                _guirechteck<int> rect=ClientRect<int>();
                                                                BitBlt(hDC.kontext(),0,0,rect.breite(),rect.hoehe(),hMemoryDC.kontext(),0,0,SRCCOPY);
                                                                SelectObject(hMemoryDC.kontext(), hOldBmp);
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I F E N S T E R S T A T I S C H B A S I S 
//******************************************************************************************************************************************************************************************************
_guifensterstatischbasis::_guifensterstatischbasis(T_String<> const &pn,_guifenster*parent):_guifenster(pn, parent){

}
_guifensterstatischbasis::~_guifensterstatischbasis(){
};

void _guifensterstatischbasis::zentrierentextvertikal(bool center){
                                                                //Gibt an ob der Text vertikal zentriert werden soll
                                                                if(center) addierenstil(BS_CENTER); else loeschenstil(BS_CENTER);
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I F E N S T E R S T A T I S C H L I N K S
//******************************************************************************************************************************************************************************************************
_guifensterstatischlinks::_guifensterstatischlinks(T_String<> const &pn,_guifenster*parent):_guifensterstatischbasis(pn,parent){
                                                                erzeugen(WS_CHILD | SS_LEFT, 0, L"STATIC");
                                                                farbehintergrund(GetSysColor(COLOR_BTNFACE));
};
_guifensterstatischlinks::~_guifensterstatischlinks(){
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I F E N S T E R S T A T I S C H R E C H T S 
//******************************************************************************************************************************************************************************************************
_guifensterstatischrechts::_guifensterstatischrechts(T_String<> const &pn,_guifenster*parent):_guifensterstatischbasis(pn,parent){
                                                                erzeugen(WS_CHILD | SS_RIGHT, 0, L"STATIC");
                                                                farbehintergrund(GetSysColor(COLOR_BTNFACE));
};
_guifensterstatischrechts::~_guifensterstatischrechts(){
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I F E N S T E R S T A T I S C H Z E N T R I E R T 
//******************************************************************************************************************************************************************************************************
_guifensterstatischzentriert::_guifensterstatischzentriert(T_String<> const &pn,_guifenster*parent):_guifensterstatischbasis(pn,parent){
                                                                erzeugen(WS_CHILD | SS_CENTER, 0, L"STATIC");
                                                                farbehintergrund(GetSysColor(COLOR_BTNFACE));
};
_guifensterstatischzentriert::~_guifensterstatischzentriert(){
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I F E N S T E R K A R T E I
//******************************************************************************************************************************************************************************************************
_guifensterkartei::_guifensterkartei(_guifenster*parent):_guifenster(L"guifensterkartei",parent){
                                                                erzeugen(WS_CHILD | TCS_MULTILINE, 0, WC_TABCONTROL);
                                                                *this += new _guiereignisSelectionChange<_guifensterkartei>(this, &_guifensterkartei::beiselektion);
};
_guifensterkartei::~_guifensterkartei(){
};
unsigned int _guifensterkartei::selektion(){
                                                                //Gibt die aktuelle Selektion zurück
                                                                return(TabCtrl_GetCurSel(handle()));
};
void _guifensterkartei::selektion(unsigned int num){
                                                                //Setzt die Selektion manuell (die Nachrichten werden nicht gesendet)
                                                                TabCtrl_SetCurSel(handle(),num);
                                                                beiselektion(0);  // Vorsicht wenn S_EventParams verwendet wird...
};
void _guifensterkartei::beiselektion(_guiereignisdaten*ep){
                                                                //Selektion wurde geändert
                                                                _listenknoten<_guifensterkarteiseite>*tpit;
                                                                unsigned int i=0,active=TabCtrl_GetCurSel(handle());
                                                                // Alle verstecken und aktive Seite anzeigen
                                                                if(plistPages.anfang(tpit))do{
                                                                 if(active == i++){
                                                                  tpit->objekt()->zeigen();
                                                                  tpit->objekt()->neuzeichnen();
                                                                 }else{
                                                                  tpit->objekt()->verstecken();
                                                                 };
                                                                }while(plistPages.naechstes(tpit));
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I F E N S T E R K A R T E I S E I T E 
//******************************************************************************************************************************************************************************************************
_guifensterkarteiseite::_guifensterkarteiseite(T_String<> const &pn, _guifensterkartei *tw) : _guidialog(pn, tw){
                                                                TCITEM  tie;
                                                                // ------------------------------------------------
                                                                erzeugen(WS_CHILD);
                                                                tw->plistPages.einhaengen(this);
                                                                tie.mask=TCIF_TEXT|TCIF_IMAGE;
                                                                tie.iImage=-1;
                                                                //char  *temp;
                                                                //temp = new char[name.length() + 1];
                                                                //strcpy(temp, name.Data());
                                                                tie.pszText=LPWSTR(pn.Data());//   temp;
                                                                TabCtrl_InsertItem(tw->handle(), TabCtrl_GetItemCount(tw->handle()), &tie);
                                                                //delete[] temp;
}
_guifensterkarteiseite::~_guifensterkarteiseite(){
};
void _guifensterkarteiseite::skalieren(){
                                                                //Ändert die Größe
                                                                _guirechteck<int> rect=besitzer()->ClientRect<int>();
                                                                RECT rect2;
                                                                SetRect(&rect2, rect.links(),rect.oben(),rect.rechts(),rect.unten());
                                                                TabCtrl_AdjustRect(besitzer()->handle(),FALSE,&rect2);
                                                                bewegen(rect2.left, rect2.top, rect2.right - rect2.left, rect2.bottom - rect2.top);
                                                                // Alle Kinder anpassen
                                                                _guidialog::skalieren();
}
//******************************************************************************************************************************************************************************************************
//                                                              G U I F E N S T E R W E R K Z E U G 
//******************************************************************************************************************************************************************************************************
_guifensterwerkzeug::_guifensterwerkzeug(T_String<>const &pn,_guifenster*parent, _guimenueleiste*menu):_guifenster(pn,parent,menu){
};
_guifensterwerkzeug::~_guifensterwerkzeug(){
};
//******************************************************************************************************************************************************************************************************
//                                                              SubProc für die Editfenster (wir wollen Tasten)
//******************************************************************************************************************************************************************************************************
//_guifenster*findenfenster(HWND handle);
//void ProcessEvents(BCObject *object, T_BaseList<BCEvent> *list, S_EventParams *params);
static LRESULT WINAPI EditSubProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
                                                                _guifenster*window =findenfenster(hwnd);
                                                                if(window){
                                                                 _guiereignisdaten params;
                                                                 params.fenster=window;
                                                                 params.wParam=wParam;
                                                                 params.lParam=lParam;
                                                                 switch(message){
                                                                  case WM_KEYDOWN:
                                                                   if(VK_RETURN==wParam){
                                                                    bearbeitenereignisse(window, &window->pkeyDownEvents,&params);
                                                                    return(0);
                                                                   };
                                                                   break;
                                                                 };
                                                                };
                                                                return(CallWindowProc(s_OldEditProc,hwnd,message,wParam,lParam));
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I T E X T F E L D B A S I S
//******************************************************************************************************************************************************************************************************
_guitextfeldbasis::_guitextfeldbasis(T_String<> const &pn,_guifenster*parent):_guifenster(pn,parent){
};
_guitextfeldbasis::~_guitextfeldbasis(){
};
void _guitextfeldbasis::nurlesen(bool ro){
                                                                //Setzt ob das Editfeld nur lesbar ist
                                                                Message(EM_SETREADONLY,ro);
};
void _guitextfeldbasis::nummer(bool nr){
                                                                //Setzt ob das Editfeld nur Nummern anzeigt
                                                                if(!nr) loeschenstil(ES_NUMBER); else addierenstil(ES_NUMBER);
};
void _guitextfeldbasis::passwort(bool pw){
                                                                //Setzt ob das Editfenster ein Passwort anzeigt
                                                                if(!pw) loeschenstil(ES_PASSWORD); else addierenstil(ES_PASSWORD);
};
void _guitextfeldbasis::begrenzentext(unsigned int numchars){
                                                                //Setzt das Limit für den Text (in Zeichen)
                                                                Message(EM_SETLIMITTEXT,numchars);
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I T E X T F E L D 
//******************************************************************************************************************************************************************************************************
_guitextfeld::_guitextfeld(T_String<> const &pn,_guifenster*parent):_guitextfeldbasis(pn,parent){
                                                                erzeugen(WS_CHILD | ES_AUTOHSCROLL, WS_EX_CLIENTEDGE, L"EDIT");
                                                                s_OldEditProc=(WNDPROC)GetWindowLong(handle(), GWL_WNDPROC);
                                                                SetWindowLong(handle(), GWL_WNDPROC, (LONG)EditSubProc);
};
_guitextfeld::~_guitextfeld(){
};
int _guitextfeld::zuint(){
                                                                //Liest das Editfeld aus und wandelt den Wert in eine Zahl um
                                                                int len=(int)_guifenster::Message(WM_GETTEXTLENGTH)+1;
                                                                wchar_t*temp = new wchar_t[len];
                                                                Message(WM_GETTEXT,len,(LPARAM)temp);
                                                                len=_wtoi(temp);
                                                                delete[] temp;
                                                                return(len);
};
_tg _guitextfeld::zutg(){
                                                                //Liest das Editfeld aus und wandelt den Wert in eine Fließkommazahl um
                                                                int  len = (int)_guifenster::Message(WM_GETTEXTLENGTH) + 1;
                                                                wchar_t*temp=new wchar_t[len];
                                                                Message(WM_GETTEXT, len, (LPARAM)temp);
                                                                T_String<>string(temp);
                                                                string.Replace(L',', L'.');
                                                                _tg val=(_tg)string.Float64();  // _wtof()
                                                                delete[] temp;
                                                                return(val);
};
T_String<> _guitextfeld::text(){
                                                                //Liest das Editfeld aus und gibt einen String zurück
                                                                int len=(int)_guifenster::Message(WM_GETTEXTLENGTH) + 1;
                                                                wchar_t*temp=new wchar_t[len];
                                                                Message(WM_GETTEXT,len,(LPARAM)temp);
                                                                T_String<>string=temp;
                                                                delete[] temp;
                                                                return(string);
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I T E X T F E L D M U L T I
//******************************************************************************************************************************************************************************************************
_guitextfeldmulti::_guitextfeldmulti(T_String<> const &pn, _guifenster *parent):_guitextfeldbasis(pn, parent){
                                                                erzeugen(WS_CHILD | WS_VSCROLL | ES_AUTOVSCROLL | ES_MULTILINE | ES_WANTRETURN, WS_EX_CLIENTEDGE, L"EDIT");
                                                                s_OldEditProc=(WNDPROC)GetWindowLong(handle(), GWL_WNDPROC);
                                                                SetWindowLong(handle(), GWL_WNDPROC, (long)EditSubProc);
                                                                pmaxLines=0xFFFFFFFF;
};
_guitextfeldmulti::~_guitextfeldmulti(){
};
void _guitextfeldmulti::maximalezeilen(unsigned int ml){
                                                                //Setzt die maximale Anzahl der Zeilen (für Logfenster)
                                                                pmaxLines=ml;
};
void _guitextfeldmulti::schreibenzeile(T_String<> const &text){
                                                                //Schreibt eine Zeile in das Editfenster (am Ende)
                                                                unsigned int uNumLines;
                                                                T_String<> string(text + L"\r\n");  // NewLine automatisch anhängen
                                                                LRESULT len=Message(WM_GETTEXTLENGTH);
                                                                //----------------------------------------------------
                                                                // Anzahl der Zeilen holen
                                                                uNumLines = (unsigned int)Message(EM_GETLINECOUNT);
                                                                // Haben wir schon die maximale Anzahl an Linien erreicht?
                                                                if(uNumLines>pmaxLines){
                                                                 wchar_t*temp = new wchar_t[len + string.Length() + 1];
                                                                 _guifenster::Message(WM_GETTEXT,len+1,(LPARAM)temp);
                                                                 wcscpy(&temp[len], string.Data());
                                                                 // Erste Linie abschneiden
																 int i=0;
                                                                 for(i=0;i<len-1;i++){
                                                                  if(L'\r' == temp[i] && L'\n' == temp[i + 1]){
                                                                   i+=2;
                                                                   break;
                                                                  };
                                                                 };
                                                                 Message(EM_SETSEL,0,-1);
                                                                 Message(EM_REPLACESEL,(WPARAM)FALSE,(LPARAM)&temp[i]);
                                                                 delete[] temp;
                                                                }else{
                                                                 Message(EM_SETSEL,(WPARAM)len, (LPARAM)len);
                                                                 Message(EM_REPLACESEL,(WPARAM)FALSE,(LPARAM)string.Data());
                                                                };
                                                                // Ganz ans Ende des Fensters scrollen
                                                                Message(EM_LINESCROLL,0,uNumLines+1);
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I C O M B O B O X
//******************************************************************************************************************************************************************************************************
_guicombobox::_guicombobox(_guifenster*parent):_guifenster(L"guicombobox",parent){
                                                                erzeugen(WS_CHILD|WS_VSCROLL|CBS_DROPDOWNLIST|CBS_HASSTRINGS,0,L"COMBOBOX");
};
_guicombobox::~_guicombobox(){
};
void _guicombobox::addierentext(T_String<> const &string){
                                                                //Fügt einen String in die Combobox ein (Unicode)
                                                                Message(CB_ADDSTRING,0,(LPARAM)string.Data());
};
unsigned int _guicombobox::selektion(){
                                                                //Holt die aktuelle Auswahl
                                                                return((unsigned int)Message(CB_GETCURSEL));
};
void _guicombobox::selektion(unsigned int num){
                                                                //Setzt die aktuelle Auswahl nach Index   
                                                                Message(CB_SETCURSEL,num);
};
T_String<> _guicombobox::selektiontext(){
                                                                //Holt die aktuelle Auswahl als String
                                                                wchar_t*temp;
                                                                T_String<>string;
                                                                unsigned int sel=selektion();
                                                                temp=new wchar_t[Message(CB_GETLBTEXTLEN, sel) + 1];
                                                                Message(CB_GETLBTEXT,sel,(LPARAM)temp);
                                                                string=temp;
                                                                delete[] temp;
                                                                return(string);
};
void _guicombobox::selektion(T_String<> const &string){
                                                                //Setzt die aktuelle Auswahl anhand eines Strings
                                                                Message(CB_SELECTSTRING,-1,(LPARAM)string.Data());
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I L I S T B O X
//******************************************************************************************************************************************************************************************************
_guilistbox::_guilistbox(_guifenster*parent):_guifenster(L"guilistbox",parent){
                                                                erzeugen(WS_CHILD|WS_BORDER|WS_HSCROLL|WS_VSCROLL|LBS_HASSTRINGS|LBS_NOINTEGRALHEIGHT,0,L"LISTBOX");
};
_guilistbox::~_guilistbox(){
};
int _guilistbox::selektion(){
                                                                //Gibt die aktuelle Selektion zurück
                                                                return((int)Message(LB_GETCURSEL));
};
void _guilistbox::selektion(int i){
                                                                //Setzt die aktuelle Selektion
                                                                Message(LB_SETCURSEL, i);
};
T_String<> _guilistbox::text(int i){
                                                                //Holt einen String (nach Index)
                                                                T_String<> string;
                                                                int len=(int)Message(LB_GETTEXTLEN,i);
                                                                wchar_t*buffer=new wchar_t[len+1];
                                                                Message(LB_GETTEXT,i,(LPARAM)buffer);
                                                                string=buffer;
                                                                delete[] buffer;
                                                                return(string);
};
void _guilistbox::addierentext(T_String<> const &string){
                                                                //Fügt einen String in die ListBox ein (Unicode)
                                                                Message(LB_ADDSTRING, 0, (LPARAM)string.Data());
};
void _guilistbox::loeschentext(int index){
                                                                //Löscht einen bestimmten String in der ListBox
                                                                Message(LB_DELETESTRING, index);
};
void _guilistbox::loeschentext(){
                                                                //Löscht ALLE Strings in der ListBox
                                                                Message(LB_RESETCONTENT);
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I S C R O L L B A R B A S I S
//******************************************************************************************************************************************************************************************************
_guiscrollbarbasis::_guiscrollbarbasis(_guifenster*parent):_guifenster(L"guiscrollbarbasis",parent){
                                                                pstepSize=1;
};
_guiscrollbarbasis::~_guiscrollbarbasis(){
};
int _guiscrollbarbasis::schritt(){
                                                                //Gibt die Größe eines Schritts zurück
                                                                return(pstepSize);
};
void _guiscrollbarbasis::schritt(int ss){
                                                                //Setzt die Größe eines Schritts
                                                                pstepSize=ss;
};
int _guiscrollbarbasis::ort(){
                                                                //Gibt die Position des "Daumens" zurück
                                                                SCROLLINFO si;
                                                                si.cbSize=sizeof(SCROLLINFO);
                                                                si.fMask=SIF_DISABLENOSCROLL|SIF_POS;
                                                                GetScrollInfo(handle(),SB_CTL,&si);
                                                                return(si.nPos);
};
void _guiscrollbarbasis::ort(int pos,bool redraw){
                                                                //Setzt die Position des "Daumens"
                                                                SCROLLINFO si;
                                                                if(seite()>(bereichmaximal()-bereichminimal()))return;
                                                                si.cbSize=sizeof(SCROLLINFO);
                                                                si.fMask=SIF_DISABLENOSCROLL|SIF_POS;
                                                                si.nPos=pos;
                                                                SetScrollInfo(handle(),SB_CTL,&si,true);
                                                                // Elternfenster neu zeichnen
                                                                if(redraw) besitzer()->neuzeichnen();
};
int _guiscrollbarbasis::trackort(){
                                                                //Gibt die Position des "Daumens" zurück
                                                                SCROLLINFO si;
                                                                si.cbSize=sizeof(SCROLLINFO);
                                                                si.fMask=SIF_DISABLENOSCROLL|SIF_TRACKPOS;
                                                                GetScrollInfo(handle(),SB_CTL,&si);
                                                                return(si.nTrackPos);
};
int _guiscrollbarbasis::seite(){
                                                                //Gibt die Größe einer Seite zurück
                                                                SCROLLINFO si;
                                                                si.cbSize=sizeof(SCROLLINFO);
                                                                si.fMask=SIF_DISABLENOSCROLL|SIF_PAGE;
                                                                GetScrollInfo(handle(),SB_CTL,&si);
                                                                return(si.nPage);
};
void _guiscrollbarbasis::seite(int page){
                                                                //Setzt die Größe einer Seite
                                                                SCROLLINFO si;
                                                                si.cbSize=sizeof(SCROLLINFO);
                                                                si.fMask=SIF_DISABLENOSCROLL|SIF_PAGE;
                                                                si.nPage=page;
                                                                SetScrollInfo(handle(),SB_CTL,&si,true);
};
int _guiscrollbarbasis::bereichminimal(){
                                                                //Gibt die minimale Position des "Daumens" zurück
                                                                SCROLLINFO si;
                                                                si.cbSize=sizeof(SCROLLINFO);
                                                                si.fMask=SIF_DISABLENOSCROLL|SIF_RANGE;
                                                                GetScrollInfo(handle(),SB_CTL,&si);
                                                                return(si.nMin);
};
int _guiscrollbarbasis::bereichmaximal(){
                                                                //Gibt die maximale Position des "Daumens" zurück
                                                                SCROLLINFO si;
                                                                si.cbSize=sizeof(SCROLLINFO);
                                                                si.fMask=SIF_DISABLENOSCROLL|SIF_RANGE;
                                                                GetScrollInfo(handle(),SB_CTL,&si);
                                                                return(si.nMax);
};
void _guiscrollbarbasis::bereich(int min, int max){
                                                                //Setzt die minimale- und maximale Position des "Daumens"
                                                                SCROLLINFO si;
                                                                si.cbSize=sizeof(SCROLLINFO);
                                                                si.fMask=SIF_DISABLENOSCROLL|SIF_RANGE;
                                                                si.nMin=min;
                                                                si.nMax=max;
                                                                SetScrollInfo(handle(),SB_CTL,&si,true);
};
void _guiscrollbarbasis::LineLeft(){
                                                                //Scrollt eine Linie nach links
                                                                ort(ort()-1);
};
void _guiscrollbarbasis::LineRight(){
                                                                //Scrollt eine Linie nach rechts
                                                                ort(ort()+1);
};
void _guiscrollbarbasis::PageLeft(){
                                                                //Scrollt eine Seite nach links
                                                                ort(ort()-seite());
};
void _guiscrollbarbasis::PageRight(){
                                                                //Scrollt eine Seite nach rechts
                                                                ort(ort()+seite());
};
void _guiscrollbarbasis::LineUp(){ 
                                                                LineLeft();
};
void _guiscrollbarbasis::LineDown(){ 
                                                                LineRight();
};
void _guiscrollbarbasis::PageUp(){
                                                                PageLeft();
};
void _guiscrollbarbasis::PageDown(){
                                                                PageRight();
};

//******************************************************************************************************************************************************************************************************
//                                                              G U I S C R O L L H O R I Z O N T A L 
//******************************************************************************************************************************************************************************************************
_guiscrollbarhorizontal::_guiscrollbarhorizontal(_guifenster*parent) : _guiscrollbarbasis(parent){
                                                                erzeugen(WS_CHILD|SBS_HORZ,0,L"SCROLLBAR");
};
_guiscrollbarhorizontal::~_guiscrollbarhorizontal(){
};
void _guiscrollbarhorizontal::skalieren(){
                                                                //Größe wurde geändert
                                                                _guirechteck<int> rect=besitzer()->ClientRect<int>();
                                                                seite(rect.breite()/schritt());
};

//******************************************************************************************************************************************************************************************************
//                                                              G U I S C R O L L V E R T I K A L
//******************************************************************************************************************************************************************************************************
_guiscrollbarvertikal::_guiscrollbarvertikal(_guifenster*parent) : _guiscrollbarbasis(parent){
                                                                erzeugen(WS_CHILD|SBS_VERT,0,L"SCROLLBAR");
};
_guiscrollbarvertikal::~_guiscrollbarvertikal(){
};
void _guiscrollbarvertikal::skalieren(){
                                                                //Größe wurde geändert
                                                                _guirechteck<int> rect=besitzer()->ClientRect<int>();
                                                                seite(rect.hoehe()/schritt());
};


//******************************************************************************************************************************************************************************************************
//                                                              G U I T E I L E R B A S I S
//******************************************************************************************************************************************************************************************************
_guiteilerbasis::_guiteilerbasis(_guifenster*parent,_guifenster*left,_guifenster*right):_guifenster(L"GUI::BCSplitterBase", parent){
                                                                erzeugen(WS_CHILD);
                                                                farbehintergrund(GetSysColor(COLOR_BTNFACE));  // Standardhintergrund für Dialoge
                                                                pheight=6;
                                                                ppercent=0.5;
                                                                pmin=psnapTop=0;
                                                                pmax=psnapBottom=1;
                                                                ptop=left;
                                                                pbottom=right;
                                                                pleftButtonDown=false;  // Wird bei MouseMove verwendet
                                                                pclickOffset=0;
                                                                *this+=new _guiereignisLeftButtonUp<_guiteilerbasis>(this,&_guiteilerbasis::beiknopflinkshoch);
                                                                *this+=new _guiereignisEraseBackground<_guiteilerbasis>(this,&_guiteilerbasis::beiloeschenhintergrund);
};
_guiteilerbasis::~_guiteilerbasis(){
};
void _guiteilerbasis::breite(int w){
                                                                //Setzt die Breite bzw. die Höhe (beides gleich, ist nur für die Anwendung)
                                                                pheight=w;
};
void _guiteilerbasis::hoehe(int h){
                                                                pheight=h;
};
_tg _guiteilerbasis::lesen()const{ 
                                                                return(ppercent); 
};
void _guiteilerbasis::setzen(_tg p){
                                                                //Setzt die Prozentzahl des Splitters (0-1)
                                                                if(p<pmin) p=pmin;
                                                                if(p>pmax) p=pmax;
                                                                if(p<=psnapTop) p=0;
                                                                if(p>=psnapBottom) p=pmax;
                                                                ppercent=p;
                                                                skalieren();
};
void _guiteilerbasis::minimal(_tg min){
                                                                //Setzt die minimale Position des Splitters
                                                                if(min<0) min=0;
                                                                if(min>1) min=1;
                                                                pmin=min;
};
void _guiteilerbasis::maximal(_tg max){
                                                                //Setzt die maximale Position des Splitters
                                                                if(max<0) max=0;
                                                                if(max>1) max=1;
                                                                pmax=max;
};

void _guiteilerbasis::einrastenlinks(_tg snap){
                                                                //Setzt den Abstand bei dem der Splitter links bzw. oben an den Rand springt    
                                                                einrastenoben(snap);
};
void _guiteilerbasis::einrastenoben(_tg snap){
                                                                if(snap<0) snap=0;
                                                                if(snap>1) snap=1;
                                                                psnapTop=snap;
};
void _guiteilerbasis::einrastenrechts(_tg snap){
                                                                //Setzt den Abstand bei dem der Splitter rechts bzw. unten an den Rand springt
                                                                einrastenunten(snap);
};

void _guiteilerbasis::einrastenunten(_tg snap){
                                                                if(snap<0) snap=0;
                                                                if(snap>1) snap=1;
                                                                psnapBottom=snap;
};
void _guiteilerbasis::links(_guifenster*left){
                                                                //Fügt ein Fenster auf der linken bzw. oberen Seite ein
                                                                if(left)ptop=left;
};
void _guiteilerbasis::oben(_guifenster*top){
                                                                if(top) ptop=top;
};
void _guiteilerbasis::rechts(_guifenster*right){
                                                                //Fügt ein Fenster auf der rechten bzw. unteren Seite ein
                                                                if(right) pbottom=right;
};
void _guiteilerbasis::unten(_guifenster*bottom){
                                                                if(bottom) pbottom=bottom;
};
void _guiteilerbasis::skalieren(){
                                                                //Passt die Größe an
                                                                SendMessage(handle(),WM_SIZE,0,0);
};
void _guiteilerbasis::beiknopflinkshoch(_guiereignisdaten*ep){
                                                                //Linke Maustaste wurde losgelassen
                                                                pleftButtonDown = false;
};
void _guiteilerbasis::beiloeschenhintergrund(_guiereignisdaten*ep){
                                                                //Hintergrund muss gelöscht werden
                                                                RECT rect;
                                                                _guikontext hdc(this);
                                                                GetClientRect(handle(),&rect);
                                                                FillRect(hdc.kontext(),&rect,BackgroundBrush());
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I T E I L E R H O R I Z O N T A L
//******************************************************************************************************************************************************************************************************
_guiteilerhorizontal::_guiteilerhorizontal(_guifenster*parent,_guifenster*top,_guifenster*bottom):_guiteilerbasis(parent,top,bottom){
                                                                cursor(IDC_SIZENS);
                                                                *this+=new _guiereignisSize<_guiteilerhorizontal>(this,&_guiteilerhorizontal::beigroesse);
                                                                *this+=new _guiereignisLeftButtonDown<_guiteilerhorizontal>(this,&_guiteilerhorizontal::beiknopflinksrunter);
                                                                *this+=new _guiereignisMouseMove<_guiteilerhorizontal>(this,&_guiteilerhorizontal::beimausbewegung);
};
_guiteilerhorizontal::~_guiteilerhorizontal(){
};
void _guiteilerhorizontal::beigroesse(_guiereignisdaten *ep){
                                                                //Größe wurde geändert
                                                                _guirechteck<int>  rect = besitzer()->ClientRect<int>();
                                                                _tg y=((_tg)rect.hoehe()-pheight)*ppercent;
                                                               // L->schreiben("TEILER HORIZONTAL beigroesse y=",y);
                                                                bewegen(rect.links(),rect.oben()+(int)y,rect.breite(),(int)pheight);
                                                                if(ptop) ptop->bewegen(rect.links(),rect.oben(),rect.breite(),(int)y);
                                                                if(pbottom){
                                                                 pbottom->bewegen(rect.links(),rect.oben()+(int)(y+pheight),rect.breite(),rect.hoehe()-(int)(y+pheight));
                                                               //  L->schreiben("TEILER HORIZONTAL beigroesse bottom top y=",rect.oben()+(int)(y+pheight));
                                                                 
                                                                };
};
void _guiteilerhorizontal::beiknopflinksrunter(_guiereignisdaten*ep){
                                                                //Linke Maustaste wurde gedrückt
                                                                pleftButtonDown=true;
                                                                pclickOffset=ep->maus.y;
};
void _guiteilerhorizontal::beimausbewegung(_guiereignisdaten*ep){
                                                                //Maus wurde bewegt
                                                                if(pleftButtonDown){
                                                                 _guirechteck<int> rect=besitzer()->ClientRect<int>();
                                                                 _tg y=(_tg)(rect.hoehe()-pheight)*ppercent;
                                                                 POINT pt={0, ep->maus.y };  // x wird nicht verwendet
                                                                 MapWindowPoints(handle(),besitzer()->handle(),&pt,1);
                                                                 y+=(pt.y-y)-pclickOffset;
                                                                 setzen(y/(_tg)(rect.hoehe() - pheight));
                                                                 //skalieren();
                                                                 //beigroesse(0);
                                                                };
}
//******************************************************************************************************************************************************************************************************
//                                                              G U I T E I L E R V E R T I K A L
//******************************************************************************************************************************************************************************************************
_guiteilervertikal::_guiteilervertikal(_guifenster*parent,_guifenster*left,_guifenster*right):_guiteilerbasis(parent,left,right){
                                                                cursor(IDC_SIZEWE);
                                                                *this+=new _guiereignisSize<_guiteilervertikal>(this,&_guiteilervertikal::beigroesse);
                                                                *this+=new _guiereignisLeftButtonDown<_guiteilervertikal>(this,&_guiteilervertikal::beiknopflinksrunter);
                                                                *this+=new _guiereignisMouseMove<_guiteilervertikal>(this,&_guiteilervertikal::beimausbewegung);
};
_guiteilervertikal::~_guiteilervertikal(){
};
void _guiteilervertikal::beigroesse(_guiereignisdaten*ep){
                                                                //Größe wurde geändert
                                                                _guirechteck<int> rect=besitzer()->ClientRect<int>();
                                                                _tg x=((_tg)rect.breite()-pheight)*ppercent;
                                                                bewegen(rect.links()+(int)x,rect.oben(),(int)pheight,rect.hoehe());
                                                                if(ptop) ptop->bewegen(rect.links(),rect.oben(),(int)x,rect.hoehe());
                                                                if(pbottom) pbottom->bewegen(rect.links()+(int)(x+pheight), rect.oben(), rect.breite()-(int)(x+pheight),rect.hoehe());
};
void _guiteilervertikal::beiknopflinksrunter(_guiereignisdaten*ep){
                                                                //Linke Maustaste wurde gedrückt
                                                                pleftButtonDown=true;
                                                                pclickOffset=ep->maus.x;
};
void _guiteilervertikal::beimausbewegung(_guiereignisdaten*ep){
                                                                //Maus wurde bewegt
                                                                if(pleftButtonDown){
                                                                 _guirechteck<int> rect=besitzer()->ClientRect<int>();
                                                                 _tg x=(_tg)(rect.breite()-pheight)*ppercent;
                                                                 POINT pt={ep->maus.x,0};  // y wird nicht verwendet
                                                                 MapWindowPoints(handle(),besitzer()->handle(),&pt,1);
                                                                 x+=(pt.x-x)-pclickOffset;
                                                                 setzen(x / (_tg)(rect.breite() - pheight));
                                                                 //skalieren();
                                                                // beigroesse(0);
                                                                }; 
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I S T A T U S L E I S T E
//******************************************************************************************************************************************************************************************************
_guistatusleiste::_guistatusleiste(_guifenster*parent):_guifenster(L"guistatusleiste",parent){
                                                                erzeugen(WS_CHILD|SBARS_SIZEGRIP,0,STATUSCLASSNAME);
};
_guistatusleiste::~_guistatusleiste(){
};
void _guistatusleiste::teile(int parts,int*info){
                                                                //Setzt die Anzahl der Textpassagen
                                                                SendMessage(handle(),SB_SETPARTS,parts,(LPARAM)info);
};
void _guistatusleiste::text(int part,T_String<> const &text){
                                                                //Setzt den Text für eine Passage (Unicode)
                                                                SendMessage(handle(),SB_SETTEXT,part,(LPARAM)text.Data());
};
void _guistatusleiste::skalieren(){
                                                                //Größenänderung (wird automatisch angepasst)
                                                                SendMessage(handle(),WM_SIZE,0,0);
};

//******************************************************************************************************************************************************************************************************
//                                                              G U I W E R K Z E U G L E I S T E K N O P F
//******************************************************************************************************************************************************************************************************
_guiwerkzeugleisteknopf::~_guiwerkzeugleisteknopf(){
};
unsigned int _guiwerkzeugleisteknopf::index(){
                                                                return(pindex);
};
T_String<> _guiwerkzeugleisteknopf::hilfe(){
                                                                //Gibt den ToolTip zurück
                                                                return(ptoolTip);
};
void _guiwerkzeugleisteknopf::hilfe(T_String<> const &tooltip){
                                                                //Setzt den ToolTip
                                                                ptoolTip=tooltip;
};
void _guiwerkzeugleisteknopf::stil(unsigned int style){
                                                                //Ändert den Style eines Buttons (Check...)
                                                                TBBUTTONINFO tbbi;
                                                                tbbi.cbSize=sizeof(TBBUTTONINFO);
                                                                tbbi.dwMask=TBIF_STYLE; //BTNS_CHECK
                                                                tbbi.fsStyle=style;
                                                                ptoolBar->Message(TB_SETBUTTONINFO,id(),(LPARAM)&tbbi);
};
bool _guiwerkzeugleisteknopf::gesetzt()const{
                                                                //Holt/Setzt ob der Button reingedrückt ist
                                                                TBBUTTONINFO tbbi;
                                                                tbbi.cbSize=sizeof(TBBUTTONINFO);
                                                                tbbi.dwMask=TBIF_STATE;
                                                                ptoolBar->Message(TB_GETBUTTONINFO, id(), (LPARAM)&tbbi);
                                                                return(0 != (tbbi.fsState & TBSTATE_CHECKED));
};
void _guiwerkzeugleisteknopf::gesetzt(bool check){
                                                                TBBUTTONINFO tbbi;
                                                                tbbi.cbSize=sizeof(TBBUTTONINFO);
                                                                tbbi.dwMask=TBIF_STATE;
                                                                tbbi.fsState=TBSTATE_ENABLED|(check?TBSTATE_CHECKED:0);
                                                                ptoolBar->Message(TB_SETBUTTONINFO,id(),(LPARAM)&tbbi);
};
//******************************************************************************************************************************************************************************************************
//                                                              G U I W E R K Z E U G L E I S T E
//******************************************************************************************************************************************************************************************************
_guiwerkzeugleiste::_guiwerkzeugleiste(_guifenster*parent):_guifenster(L"guiwerkzeugleiste",parent){
                                                                erzeugen(WS_CHILD|TBSTYLE_TOOLTIPS,0,TOOLBARCLASSNAME);
                                                                Message(TB_BUTTONSTRUCTSIZE,(WPARAM)sizeof(TBBUTTON));
};
_guiwerkzeugleiste::~_guiwerkzeugleiste(){
};
void _guiwerkzeugleiste::skalieren(){
                                                                //Passt die Größe der ToolBar an
                                                                Message(TB_AUTOSIZE,0,0);
};
void _guiwerkzeugleiste::knopfgroesse(unsigned short int width,unsigned short int height){
                                                                //Setzt die Buttongröße der ToolBar
                                                                Message(TB_SETBITMAPSIZE, 0, (LPARAM)MAKELONG(width, height));
};
void _guiwerkzeugleiste::addierenbitmap(unsigned int num, HANDLE hbmp){
                                                                //Fügt ein Bitmap hinzu (muss von Hand geladen werden)
                                                                TBADDBITMAP tbab;
                                                                tbab.hInst=0;
                                                                tbab.nID=(UINT_PTR)hbmp;
                                                                Message(TB_ADDBITMAP,num,(LPARAM)&tbab);
};
void _guiwerkzeugleiste::addierenbitmapresource(unsigned int num, unsigned int resid){
                                                                //Fügt ein Bitmap aus einer Ressourcen-Datei hinzu
                                                                TBADDBITMAP tbab;
                                                                tbab.hInst=GetModuleHandle(0);
                                                                tbab.nID=resid;
                                                                Message(TB_ADDBITMAP,num,(LPARAM)&tbab);
};
void _guiwerkzeugleiste::addierenbitmapsystem(unsigned int id){
                                                                //Fügt ein Standardbitmap vom System hinzu
                                                                TBADDBITMAP tbab;
                                                                tbab.hInst=HINST_COMMCTRL;
                                                                tbab.nID=id;
                                                                Message(TB_ADDBITMAP,1,(LPARAM)&tbab);
};
void _guiwerkzeugleiste::separator(unsigned int size){
                                                                //Fügt einen Separator ein
                                                                TBBUTTON tbb;
                                                                ZeroMemory(&tbb, sizeof(tbb));
                                                                tbb.iBitmap=size;
                                                                tbb.fsStyle=TBSTYLE_SEP;
                                                                _guifenster::Message(TB_ADDBUTTONS,1,(LPARAM)&tbb);
};
void _guiwerkzeugleiste::operator+=(_guiwerkzeugleisteknopf*tbbutton){
                                                                //Fügt einen Button hinzu
                                                                TBBUTTON tbb;
                                                                ZeroMemory(&tbb,sizeof(tbb));
                                                                tbb.fsState=TBSTATE_ENABLED;
                                                                tbb.iBitmap=tbbutton->index();
                                                                tbb.idCommand=tbbutton->id();
                                                                Message(TB_ADDBUTTONS,1,(LPARAM)&tbb);
                                                                tbbutton->ptoolBar=this;
                                                                //In die Liste mit Kindern einhängen
                                                                tbbutton->einhaengen(this);//_listebasis<_guiobjekt>::einhaengen(tbbutton);
};













//******************************************************************************************************************************************************************************************************
//                                                              E D I T I O N S K O P P L U N G D I A L O G
//******************************************************************************************************************************************************************************************************
//******************************************************************************************************************************************************************************************************
//                                                              E D I T I O N S K O P P L U N G
//******************************************************************************************************************************************************************************************************
_editionskopplung::_editionskopplung(_dynamischerdialog*ed,T_String<> const &section,T_String<> const &name):_listenknotenbasis<_editionskopplung>(ed){
                                pname=name;
                                pdialog=ed;
                                psection=section;  
                                peditable=0;
                                peditionsradius=0.25;
                                paktiv=false;
                                pfarbe.setzen(1,1,1,1);
                                _guidialogeditierbar*bced=dynamic_cast<_guidialogeditierbar*>(ed);
                                if(bced){
                                 
                                 peditable= bced->sektion(section)->editierbar(name);
                                 if(peditable) L->schreiben("editionskopplung=",UnicodeToANSI(name.Data()).Data());
                                }else{
                                 //fehler : kein bceditabledialog an dialogkopplung
                                 peditable=0;
                                };
};
_editionskopplung::~_editionskopplung(){
};
_dynamischerdialog*_editionskopplung::dialog(){
								return(pdialog);
};

_guieditierbar*_editionskopplung::editierbares(){
                                return(peditable);
};
void _editionskopplung::aktiv(const bool b){
                                paktiv=b;
};
bool _editionskopplung::aktiv()const{
                                return(paktiv);
};
void _editionskopplung::farbe(const _vektor4<_to>&f){
                                pfarbe=f;
};
_vektor4<_to> _editionskopplung::farbe()const{
                                return(pfarbe);
};
void _editionskopplung::editionsradius(const _tg r){
                                peditionsradius=r;
};
_tg _editionskopplung::editionsradius()const{
                                return(peditionsradius);
};
//******************************************************************************************************************************************************************************************************
//                                                              E D I T I O N S K O P P L U N G O R T
//******************************************************************************************************************************************************************************************************
_editionskopplungort::_editionskopplungort(_dynamischerdialog*edk,T_String<> const &section,T_String<> const &name):_editionskopplung(edk,section,name){
                                importieren();
};
_editionskopplungort::~_editionskopplungort(){
};
void _editionskopplungort::exportieren(){
                                _guitextfeld*ef;
                                for(unsigned int i=0;i<3;i++){
                                 ef = editierbares()->objekt<_guitextfeld>(i);
                                 ef->text(port[i]);
                                 ef->farbehintergrund(255,255,255);
                                 ef->neuzeichnen();
                                };
                                editierbares()->beruehrt(true);
};
void _editionskopplungort::importieren(){
                                _vektor3<_tg> val;
                                _guitextfeld*ef;
                                for(unsigned int i=0;i<3;i++){
                                 ef = editierbares()->objekt<_guitextfeld>(i);
                                 val.setzenkomponente(i, (_tg)ef->zutg());
                                }; 
                                port=val;                              
};
_vektor3<_tg> _editionskopplungort::ort()const{
                                return(port);
};
void _editionskopplungort::ort(const _vektor3<_tg>&o){
                                port=o;
                                exportieren();
};

void _editionskopplungort::verschieben(const _vektor3<_tg>&v){
                                port+=v;
                                exportieren();
};
_vektor3<_tg> _editionskopplungort::abstand(const _vektor3<_tg>&start,const _vektor3<_tg>&dir){
                                _vektoranalysis3<_tg> V3;
                                _vektor3<_tg> lot;
                                _tg para;
                                V3.lotpunktgerade(port,start,dir,lot,para);
                                return(lot);
};
void _editionskopplungort::zeichnen(_grafik*grafik){
								if(aktiv()){
								// L->schreiben("Ort zeichnugn");
                                 _vektor4<_to> c1;
                                 _tg s=editionsradius();
                                 c1.setzen(1,0,0,1);
                               
                                 _tg w=0;
                                 _vektor3<_tg> x0;
                                 _vektor3<_tg> x1;
                                 x1.setzen(s,0,0);
                                 for(w=0;w<360;w+=5){
                                  x0=x1;
                                  x1.setzen(cos((w+5)*_ph)*s,sin((w+5)*_ph)*s,0);
                                  grafik->zeichnen(port+x0,port+x1,farbe(),farbe());
                                 };
                                 x1.setzen(s,0,0);
                                 for(w=0;w<360;w+=5){
                                  x0=x1;
                                  x1.setzen(cos((w+5)*_ph)*s,0,sin((w+5)*_ph)*s);
                                  grafik->zeichnen(port+x0,port+x1,farbe(),farbe());
                                 };
                                 x1.setzen(0,s,0);
                                 for(w=0;w<360;w+=5){
                                  x0=x1;
                                  x1.setzen(0,cos((w+5)*_ph)*s,sin((w+5)*_ph)*s);
                                  grafik->zeichnen(port+x0,port+x1,farbe(),farbe());
                                 };
                                 grafik->zeichnen(port,port+_vektor3<_tg>(s,0,0),farbe(),c1);
                                 grafik->zeichnen(port,port+_vektor3<_tg>(-s,0,0),farbe(),c1);
                                 grafik->zeichnen(port,port+_vektor3<_tg>(0,s,0),farbe(),c1);
                                 grafik->zeichnen(port,port+_vektor3<_tg>(0,-s,0),farbe(),c1);
                                 grafik->zeichnen(port,port+_vektor3<_tg>(0,0,s),farbe(),c1);
                                 grafik->zeichnen(port,port+_vektor3<_tg>(0,0,-s),farbe(),c1);
                                };
};  
//******************************************************************************************************************************************************************************************************
//                                                              E D I T I O N S K O P P L U N G V E K T O R
//******************************************************************************************************************************************************************************************************
_editionskopplungvektor::_editionskopplungvektor(_dynamischerdialog*edk,T_String<> const &section,T_String<> const &name,_editionskopplungort*eort):_editionskopplung(edk,section,name){
								peort=eort;
								importieren();
							
};
_editionskopplungvektor::~_editionskopplungvektor(){
};
void _editionskopplungvektor::exportieren(){
                                _guitextfeld*ef;
                                for(unsigned int i=0;i<3;i++){
                                 ef = editierbares()->objekt<_guitextfeld>(i);
                                 ef->text(pvektor[i]);
                                 ef->farbehintergrund(255,255,255);
                                 ef->neuzeichnen();
                                };
                                editierbares()->beruehrt(true);
};
void _editionskopplungvektor::importieren(){
                                _vektor3<_tg> val;
                                _guitextfeld*ef;
                                for(unsigned int i=0;i<3;i++){
                                 ef = editierbares()->objekt<_guitextfeld>(i);
                                 val.setzenkomponente(i, (_tg)ef->zutg());
                                }; 
                                pvektor=val;                              
};
void _editionskopplungvektor::verschieben(const _vektor3<_tg>&v){
                                pvektor+=v;//pvektor+v;//port+=v;
                                exportieren();
};

_vektor3<_tg> _editionskopplungvektor::abstand(const _vektor3<_tg>&start,const _vektor3<_tg>&dir){
                                _vektoranalysis3<_tg> V3;
                                _vektor3<_tg> lot;
                                _tg para;
                                V3.lotpunktgerade(peort->ort()+pvektor,start,dir,lot,para);
                                return(lot);
};
void _editionskopplungvektor::zeichnen(_grafik*grafik){
								if(aktiv()){
								// L->schreiben("vektor zeichnugn");
								 _vektor3<_tg> plocus[2];
								 _vektor3<_tg> parrs[4];
								 _vektor4<_to> pcol0(1,1,0,1);
								 _vektor4<_to> pcol1(0.5,0.5,0,0.5);
								 _vektor3<_tg> v;
								 _vektor3<_tg> vo;
								 _vektor3<_tg> vu;
								 _vektor3<_tg> vi;
								 _vektoranalysis3<_tg> V3;
								 _tg plaenge=0.08;
								 _tg pbreite=0.06;								
								 plocus[0]=peort->ort();
								 plocus[1]=plocus[0]+pvektor;
								 v=plocus[1]-plocus[0];
								 v.normalisieren();
								 V3.berechnenorthogonalenvektor(v,vo);
								 vu=vo%v;
								 vi=-v;
								 parrs[0]=plocus[1]+(vi*plaenge)+(vo*pbreite);
								 parrs[1]=plocus[1]+(vi*plaenge)-(vo*pbreite);
								 parrs[2]=plocus[1]+(vi*plaenge)+(vu*pbreite);
								 parrs[3]=plocus[1]+(vi*plaenge)-(vu*pbreite);	
                                 grafik->zeichnen(plocus[0],plocus[1],pcol0,pcol1);
                                 grafik->zeichnen(plocus[1],parrs[0],pcol0,pcol1);
                                 grafik->zeichnen(plocus[1],parrs[1],pcol0,pcol1);
                                 grafik->zeichnen(plocus[1],parrs[2],pcol0,pcol1);
                                 grafik->zeichnen(plocus[1],parrs[3],pcol0,pcol1);		
                                };													
};
//******************************************************************************************************************************************************************************************************
//                                                              E D I T I E R B A R
//******************************************************************************************************************************************************************************************************
void _editierbar::vorbereitenereignisprozess(_guiereignisdaten*){
};
void _editierbar::nachbereitenereignisprozess(_guiereignisdaten*){
};
//******************************************************************************************************************************************************************************************************
//                                                              D Y N A M I S C H E R  D I A L O G
//******************************************************************************************************************************************************************************************************
_dynamischerdialog::_dynamischerdialog(T_String<> const &n,_guifenster*parent,_listebasis<_dynamischerdialog>*l):_guidialogeditierbar(n,parent),_listenknotenbasis<_dynamischerdialog>(l){
                                //peditierbar=0;
                                pparent=parent;
                                *this += new _guiereignisClose<_dynamischerdialog>(this,&_dynamischerdialog::beischliessen);
                                groesseminimal(_guigroesse<int>(275, 200)); 
                                groessemaximal(_guigroesse<int>(800, 900)); 
                                zentrieren(520, 450, false);
                                
                               // zeigen();
};
_dynamischerdialog::~_dynamischerdialog(){
};
void _dynamischerdialog::knopfok(_guiereignisdaten *){  
								_listenknoten<_editierbar>*eit;
								iterierenliste(&peditierbarliste,eit,eit->objekt()->auslesendialog(this));
                                verstecken();
};
void _dynamischerdialog::knopfuebernehmen(_guiereignisdaten *){
								_listenknoten<_editierbar>*eit;
								iterierenliste(&peditierbarliste,eit,eit->objekt()->auslesendialog(this));
                                //if(peditierbar) peditierbar->auslesendialog(this);
                                _besitzeraktualisierung*ba=dynamic_cast<_besitzeraktualisierung*>(pparent);
                                ba->aktualisieren();   
                                
}; 
void _dynamischerdialog::neusetzen(const T_String<>pn){
                                _guidialogeditierbar::neusetzen(pn);
                                _listebasis<_editionskopplung>::loeschen();
};
void _dynamischerdialog::zeigen(){
                                _guidialogeditierbar::zeigen();
                                _editionskopplung*eit;
                                if(_listebasis<_editionskopplung>::anfang(eit))do{
                                 eit->aktiv(true);
                                }while(_listebasis<_editionskopplung>::naechstes(eit));
                                _besitzeraktualisierung*ba=dynamic_cast<_besitzeraktualisierung*>(pparent);
                                ba->aktualisieren();                                
};
void _dynamischerdialog::verstecken(){
                                _guidialogeditierbar::verstecken();
                                _editionskopplung*eit;
                                if(_listebasis<_editionskopplung>::anfang(eit))do{
                                 eit->aktiv(false);
                                }while(_listebasis<_editionskopplung>::naechstes(eit));
                                _besitzeraktualisierung*ba=dynamic_cast<_besitzeraktualisierung*>(pparent);
                                ba->aktualisieren();                                
};

bool _dynamischerdialog::beruehrt(T_String<> const &section,T_String<> const &name){
                                return(sektion(section)->editierbar(name)->beruehrt());
};

void _dynamischerdialog::beischliessen(_guiereignisdaten *){
                                verstecken();
                                _listebasis<_editionskopplung>::loeschen();
};
void _dynamischerdialog::beicomboboxberuehrt(_guiereignisdaten *ep){
                               // unsigned int b=MB_OK;
                               // GUI::Message(L"beruehrt",L"bereuhrt",b);
                                _guiobjekt*o=ep->objekt;
                                _guicombobox*cb=dynamic_cast<_guicombobox*>(o);
                                if(cb){
                                 _guieditierbar*e=dynamic_cast<_guieditierbar*>(cb->besitzer());  
                                 cb->farbehintergrund(255,255,255);
                                 e->beruehrt(true);
                                };
};
void _dynamischerdialog::beieditboxberuehrt(_guiereignisdaten *ep){
                                if(HIWORD(ep->wParam) == EN_SETFOCUS){
                                // unsigned int b=MB_OK;
                                // GUI::Message(L"beruehrt",L"bereuhrt",b);
                                 _guiobjekt*o=ep->objekt;
                                 _guitextfeld*eb=dynamic_cast<_guitextfeld*>(o);
                                 if(eb){
                                  _guieditierbar*e=dynamic_cast<_guieditierbar*>(eb->besitzer());  
                                  eb->farbehintergrund(255,255,255);
                                  e->beruehrt(true);
                                  eb->neuzeichnen();
                                 };
                                };
};
void _dynamischerdialog::beitaste(_guiereignisdaten *ep){
                                if(VK_RETURN == ep->wParam){
                                 _guitextfeld*eb=dynamic_cast<_guitextfeld*>(ep->fenster);
                                 if(eb){
                                  _guieditierbar*e=dynamic_cast<_guieditierbar*>(eb->besitzer());                                   
                                  _editionskopplung*eit;
                                  if(_listebasis<_editionskopplung>::anfang(eit))do{
                                   if(eit->editierbares()==e) {
                                    eit->importieren();
                                    _besitzeraktualisierung*ba=dynamic_cast<_besitzeraktualisierung*>(pparent);
                                    ba->aktualisieren();
                                   };
                                  }while(_listebasis<_editionskopplung>::naechstes(eit));
                                 };
                                };
};
void _dynamischerdialog::editierbar(_editierbar*e){//setzt 1 editierbares in die liste
                                peditierbarliste.aushaengen();
                                if(e) peditierbarliste.einhaengen(e);
};
void _dynamischerdialog::addiereneditierbar(_editierbar*e){//addiert ein weiteres editierbares zur liste
								peditierbarliste.einhaengenunredundant(e);
};
void _dynamischerdialog::einhaengen(T_String<> const &section,T_String<> const &name,const bool val){
                                _guieditierbar  *editable = new _guieditierbar(this, section, name);
                                editables.einhaengen(editable);
                                _guicombobox  *cb = new _guicombobox(editable);
                                *cb += new _guiereignisCommand<_dynamischerdialog>(this,&_dynamischerdialog::beicomboboxberuehrt);
                                cb->farbehintergrund(150,150,150);
                                // ---------------------------------------------------------------------
                                *cb += new _guiort<>(PERCENT_DESCRIPTION, 0, false);
                                *cb += new _guigroesse<>(1 - PERCENT_DESCRIPTION, 0, false);
                                *cb += new _guigroesse<>(0, HEIGHT_COMBOBOX);
                                cb->addierentext(L" ");
                                cb->addierentext(L"#");
                                //cb->addierentextL"Falsch");
                                //cb->addierentextL"Wahr");
                                cb->selektion(val);
                                cb->zeigen();
};
void _dynamischerdialog::auslesen(T_String<> const &section,T_String<> const &name,bool&val){
                                _guicombobox  *cb = sektion(section)->objekt<_guicombobox>(name, 0);
                                val = (0 != cb->selektion());
                                _guifenster*w = cb->besitzer();
                                _guieditierbar*editable=dynamic_cast<_guieditierbar*>(w);
                                cb->farbehintergrund(150,150,150);
                                editable->beruehrt(false);
                                cb->neuzeichnen();
                                
};
//Zeichenkette 
void _dynamischerdialog::einhaengen(T_String<> const &section,T_String<> const &name,const _zeichenkette<char>&val){
                                _guitextfeld*ef;
                                _guieditierbar*editable = new _guieditierbar(this, section, name);
                                editables.einhaengen(editable);
                                
                                ef = new _guitextfeld(L"", editable);
                                *ef += new _guiereignisCommand<_dynamischerdialog>(this,&_dynamischerdialog::beieditboxberuehrt);
                                *ef += new _guiereignisKeyDown<_dynamischerdialog>(this,&_dynamischerdialog::beitaste);
                                ef->farbehintergrund(150,150,150);
                                *ef += new _guiort<>(PERCENT_DESCRIPTION, 0, false);
                                *ef += new _guigroesse<>(1 - PERCENT_DESCRIPTION, 1, false);
                                ef->text(ANSIToUnicode(val.daten()));
                                ef->zeigen();
};
void _dynamischerdialog::auslesen(T_String<> const &section,T_String<> const &name,_zeichenkette<char>&val){
                                _guitextfeld  *ef = sektion(section)->objekt<_guitextfeld>(name, 0);
                                val = UnicodeToANSI(ef->text()).Data();
                                _guifenster*w = ef->besitzer();
                                _guieditierbar  *editable=dynamic_cast<_guieditierbar*>(w);
                                ef->farbehintergrund(150,150,150);
                                editable->beruehrt(false);
                                ef->neuzeichnen();
};


#define IMPLEMENT_EINHAENGEN(__type) \
void _dynamischerdialog::einhaengen(T_String<> const &section,T_String<> const &name,const __type val){\
                                _guitextfeld  *ef;\
                                _guieditierbar    *editable = new _guieditierbar(this, section, name);\
                                editables.einhaengen(editable);\
                                ef = new _guitextfeld(L"", editable);\
                                *ef += new _guiort<>(PERCENT_DESCRIPTION, 0, false);\
                                *ef += new _guigroesse<>(1 - PERCENT_DESCRIPTION, 1, false);\
                                *ef += new _guiereignisCommand<_dynamischerdialog>(this,&_dynamischerdialog::beieditboxberuehrt);\
                                *ef += new _guiereignisKeyDown<_dynamischerdialog>(this,&_dynamischerdialog::beitaste);\
                                ef->farbehintergrund(150,150,150);\
                                ef->text(val);\
                                ef->zeigen();\
};


#define IMPLEMENT_AUSLESEN(__func, __type) \
void _dynamischerdialog::auslesen(T_String<> const &section,T_String<> const &name,__type &val){ \
                                _guitextfeld  *ef = sektion(section)->objekt<_guitextfeld>(name, 0); \
                                val = ef->##__func(); \
                                _guifenster*w = ef->besitzer();\
                                _guieditierbar  *editable=dynamic_cast<_guieditierbar*>(w);\
                                ef->farbehintergrund(150,150,150);\
                                editable->beruehrt(false);\
                                ef->neuzeichnen();\
};


IMPLEMENT_EINHAENGEN(unsigned char)
IMPLEMENT_EINHAENGEN(signed char)
IMPLEMENT_EINHAENGEN(unsigned short int)
IMPLEMENT_EINHAENGEN(signed short int)
IMPLEMENT_EINHAENGEN(unsigned int)
IMPLEMENT_EINHAENGEN(signed int)
IMPLEMENT_EINHAENGEN(unsigned long int)
IMPLEMENT_EINHAENGEN(signed long int)
IMPLEMENT_EINHAENGEN(float)
IMPLEMENT_EINHAENGEN(double)
IMPLEMENT_AUSLESEN(zuint, unsigned char)
IMPLEMENT_AUSLESEN(zuint, signed char)
IMPLEMENT_AUSLESEN(zuint, unsigned short int)
IMPLEMENT_AUSLESEN(zuint, signed short int)
IMPLEMENT_AUSLESEN(zuint, unsigned int)
IMPLEMENT_AUSLESEN(zuint, signed int)
IMPLEMENT_AUSLESEN(zuint, unsigned long int)
IMPLEMENT_AUSLESEN(zuint, signed long int)
IMPLEMENT_AUSLESEN(zutg, float)
IMPLEMENT_AUSLESEN(zutg, double)






//******************************************************************************************************************************************************************************************************
//                                                              W I N D O W S  N A C H R I C H T E N S C H L E I F E 
//******************************************************************************************************************************************************************************************************
static LRESULT WINAPI WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){

                                                                _guiereignisdaten params;
                                                                _guifenster*window=findenfenster(hWnd);
                                                                static bool s_LeftButton=false,s_RightButton=false,s_MiddleButton=false;
                                                                // ----------------------------------------------------------------------------------
                                                                if(!window || guierror) return(DefWindowProc(hWnd, message, wParam, lParam));// Die Nachricht war anscheinend nicht für uns
                                                                ZeroMemory(&params, sizeof(_guiereignisdaten));
                                                                // Für die ganzen Mausnachrichten können wir den Kram separat setzen
                                                               
                                                                switch(message){
                                                                 case WM_KEYDOWN:
                                                                  L->l("KEYDOWN");
                                                                  bearbeitenereignisse(window, &window->pkeyDownEvents, &params);
                                                                  return(0);
                                                                 case WM_KEYUP:
                                                                   L->l("KEYUP");
                                                                  bearbeitenereignisse(window, &window->pkeyUpEvents, &params);
                                                                  return(0);                                                                
                                                                
                                                                
                                                                 case WM_MOUSEMOVE:
                                                                 case WM_LBUTTONDOWN:
                                                                 case WM_LBUTTONUP:
                                                                 case WM_LBUTTONDBLCLK:
                                                                 case WM_RBUTTONDOWN:
                                                                 case WM_RBUTTONUP:
                                                                 case WM_RBUTTONDBLCLK:
                                                                 case WM_MBUTTONDOWN:
                                                                 case WM_MBUTTONUP:
                                                                 case WM_MBUTTONDBLCLK:
                                                                 case WM_MOUSEWHEEL:
                                                                  params.maus.x = GET_X_LPARAM(lParam);
                                                                  params.maus.y = GET_Y_LPARAM(lParam);
                                                                 break;
                                                                };
                                                                params.fenster = window;
                                                                params.wParam = wParam;
                                                                params.lParam = lParam;
                                                                // Jetzt die Nachrichten richtig verarbeiten
                                                                switch(message){
                                                                 case WM_MOUSEMOVE:  // Maus wurde bewegt
                                                                  SetCursor(window->cursor());
                                                                  bearbeitenereignisse(window,&window->pmouseMoveEvents, &params);
                                                                  return(0);
                                                                 case WM_LBUTTONDOWN:  // Linke Taste unten
                                                                  s_LeftButton = true;
                                                                  SetFocus(window->handle());
                                                                  SetCapture(window->handle());
                                                                  bearbeitenereignisse(window, &window->pleftButtonDownEvents, &params);
                                                                  return(0);
                                                                 case WM_LBUTTONUP:  // Linke Taste oben
                                                                  s_LeftButton = false;
                                                                  if(!s_RightButton && !s_MiddleButton)
                                                                   ReleaseCapture();
                                                                  bearbeitenereignisse(window, &window->pleftButtonUpEvents, &params);
                                                                  return(0);
                                                                 case WM_LBUTTONDBLCLK:  // Linke Taste doppelt geklickt
                                                                  s_LeftButton = true;
                                                                  SetFocus(window->handle());
                                                                  SetCapture(window->handle());
                                                                  bearbeitenereignisse(window, &window->pleftButtonDoubleClickEvents, &params);
                                                                  return(0);
                                                                 case WM_RBUTTONDOWN:  // Rechte Taste unten
                                                                  s_RightButton = true;
                                                                  SetFocus(window->handle());
                                                                  SetCapture(window->handle());
                                                                  bearbeitenereignisse(window, &window->prightButtonDownEvents, &params);
                                                                  return(0);
                                                                 case WM_RBUTTONUP:  // Rechte Taste oben
                                                                  s_RightButton = false;
                                                                  if(!s_LeftButton && !s_MiddleButton)
                                                                   ReleaseCapture();
                                                                  bearbeitenereignisse(window, &window->prightButtonUpEvents, &params);
                                                                  return(0);
                                                                 case WM_RBUTTONDBLCLK:  // Rechte Taste doppelt geklickt
                                                                  s_RightButton = true;
                                                                  SetFocus(window->handle());
                                                                  SetCapture(window->handle());
                                                                  bearbeitenereignisse(window, &window->prightButtonDoubleClickEvents, &params);
                                                                  return(0);
                                                                 case WM_MBUTTONDOWN:  // Mittlere Taste unten
                                                                  s_MiddleButton = true;
                                                                  SetFocus(window->handle());
                                                                  SetCapture(window->handle());
                                                                  bearbeitenereignisse(window, &window->pmiddleButtonDownEvents, &params);
                                                                  return(0);
                                                                 case WM_MBUTTONUP:  // Mittlere Taste oben
                                                                  s_MiddleButton = false;
                                                                  if(!s_LeftButton && !s_RightButton)
                                                                   ReleaseCapture();
                                                                  bearbeitenereignisse(window, &window->pmiddleButtonUpEvents, &params);
                                                                  return(0);
                                                                 case WM_MBUTTONDBLCLK:  // Mittlere Taste doppelt geklickt
                                                                 
                                                                 
                                                                 
                                                                  s_MiddleButton = true;
                                                                  SetFocus(window->handle());
                                                                  SetCapture(window->handle());
                                                                  bearbeitenereignisse(window, &window->pmiddleButtonDoubleClickEvents, &params);
                                                                  return(0);
                                                                 case WM_MOUSEWHEEL:  // Mausrad
                                                                  params.maus.zDelta = (short)HIWORD(wParam) / WHEEL_DELTA;
                                                                  bearbeitenereignisse(window, &window->pmouseWheelEvents, &params);
                                                                  return(0);

                                                                 case WM_COMMAND:{
                                                                  L->schreiben("COMMAND");
                                                                  _guiobjekt*object=findenobjekt(LOWORD(wParam));
                                                                  if(!object||LOWORD(wParam)<OBJECT_STARTID){
                                                                   DumpObjects();
                                                                   throw L"Object-ID not found! (see gui.log for error messages)";
                                                                  };
                                                                  //GLog << L"WM_COMMAND: 0x" << object << L", " << object->Name() << L"\n";
                                                                  params.objekt = object;
                                                                  bearbeitenereignisse(object, &object->pcommandEvents, &params);
                                                                  };
                                                                  return(0);
                                                                 case WM_SYSCOMMAND: 
																  switch(wParam & 0xFFF0){ 
																  case SC_SCREENSAVE: 
																	return(0); 
																  case SC_MINIMIZE: 
																	//new Event(EventType_Minimize); 
																	return(DefWindowProc(hWnd, message, wParam, lParam)); 
                  
																  case SC_MAXIMIZE: 
																	bearbeitenereignisse(window, &window->pmaximizeEvents, &params);//new Event(EventType_ToggleFullscreen); 
																	return(0); 
                  
																  case SC_CLOSE: 
																	bearbeitenereignisse(window, &window->pcloseEvents, &params);//new Event(EventType_Quit); 
																	return(0); 
																	} ;
																  break; 
                                                                 case WM_NOTIFY:
                                                                  switch (((LPNMHDR)lParam)->code){
                                                                   case TTN_NEEDTEXT: // ToolTip{ 
                                                                    LPTOOLTIPTEXT  lpttt; 
                                                                    _guiobjekt*object2;
                                                                    lpttt=(LPTOOLTIPTEXT)lParam;
                                                                    object2 =findenobjekt((unsigned int)lpttt->hdr.idFrom);
                                                                    if(object2){
                                                                     lpttt->hinst = NULL;
                                                                     wcsncpy(lpttt->szText, object2->hilfe().Data(), 80);
                                                                     lpttt->szText[79] = 0;
                                                                    };
                                                                    return(0);
                                                                    case TCN_SELCHANGE:// TabControl oder TreeView hat gewechselt
                                                                    case TVN_SELCHANGED:
                                                                     _guifenster*window2=findenfenster(((LPNMHDR)lParam)->hwndFrom);
                                                                     if(window2){
                                                                      params.fenster=window2;  // FIXME: Is this good?
                                                                      bearbeitenereignisse(window2, &window2->pselectionChangeEvents, &params);
                                                                     };
                                                                     return(0);
                                                                  };
                                                                  break;
                                                                 case WM_DROPFILES:{  // Drag-and-Drop
                                                                  unsigned int numChars = DragQueryFile((HDROP)wParam, 0, 0, 0);
                                                                  wchar_t*fileBuffer=new wchar_t[numChars+1];
                                                                  DragQueryFile((HDROP)wParam, 0, fileBuffer, numChars + 1);
                                                                  wcscpy(params.drop.fileName, fileBuffer);
                                                                  delete[] fileBuffer;
                                                                  bearbeitenereignisse(window, &window->pdropFilesEvents, &params);
                                                                  };
                                                                  return(0);
                                                                  
                                                                 case WM_SIZING:{
                                                                  RECT  *rect = (RECT *)lParam;
                                                                  // Minimalgröße
                                                                  if((rect->right - rect->left) < window->breiteminimal()){ // Linke und Rechte Seite
                                                                   if(WMSZ_LEFT == wParam || WMSZ_TOPLEFT == wParam || WMSZ_BOTTOMLEFT == wParam)  // Linke Seite
                                                                    rect->left -= window->breiteminimal() - (rect->right - rect->left);
                                                                   else  // Rechte Seite
                                                                    rect->right += window->breiteminimal() - (rect->right - rect->left);
                                                                  };
                                                                  if((rect->bottom - rect->top) < window->hoeheminimal()){  // Obere und Untere Seite
                                                                   if(WMSZ_TOP == wParam || WMSZ_TOPLEFT == wParam || WMSZ_TOPRIGHT == wParam)  // Obere Seite
                                                                    rect->top -= window->hoeheminimal() - (rect->bottom - rect->top);
                                                                   else  // Untere Seite
                                                                    rect->bottom += window->hoeheminimal() - (rect->bottom - rect->top);
                                                                  };
                                                                  // Maximalgröße
                                                                  if((rect->right - rect->left) > window->breitemaximal()){  // Linke und Rechte Seite
                                                                   if(WMSZ_LEFT == wParam || WMSZ_TOPLEFT == wParam || WMSZ_BOTTOMLEFT == wParam)  // Linke Seite
                                                                    rect->left += (rect->right - rect->left) - window->breitemaximal();
                                                                   else  // Rechte Seite
                                                                    rect->right -= (rect->right - rect->left) - window->breitemaximal();
                                                                  };
                                                                  if((rect->bottom - rect->top) > window->hoehemaximal()){  // Obere und Untere Seite
                                                                   if(WMSZ_TOP == wParam || WMSZ_TOPLEFT == wParam || WMSZ_TOPRIGHT == wParam)  // Obere Seite
                                                                    rect->top += (rect->bottom - rect->top) - window->hoehemaximal();
                                                                   else  // Untere Seite
                                                                    rect->bottom -= (rect->bottom - rect->top) - window->hoehemaximal();
                                                                  };
                                                                  };
                                                                  return(0);
                                                                  
                                                                 case WM_SIZE:
                                                                  bearbeitenereignisse(window, &window->psizeEvents, &params);
                                                                  return(0);
                                                                 case WM_HSCROLL:
                                                                 case WM_VSCROLL:
                                                                  if(0 == lParam) return(0);  // Not sent by ScrollBar
                                                                  _guiscrollbarbasis*sb;
                                                                  window=findenfenster((HWND)lParam);
                                                                  if(!window || !(sb = dynamic_cast<_guiscrollbarbasis*>(window)))throw "WM_HSCROLL/WM_VSCROLL sent, but not of type BCScrollBarBase!";
                                                                  switch(LOWORD(wParam)){
                                                                   case SB_LINELEFT:
                                                                    sb->LineLeft();
                                                                    break;
                                                                   case SB_LINERIGHT:
                                                                    sb->LineRight();
                                                                    break;
                                                                   case SB_PAGELEFT:
                                                                    sb->PageLeft();
                                                                    break;
                                                                   case SB_PAGERIGHT:
                                                                    sb->PageRight();
                                                                    break;
                                                                   case SB_THUMBPOSITION:
                                                                    case SB_THUMBTRACK:
                                                                     sb->ort(sb->trackort());
                                                                     break;
                                                                  };
                                                                  return(0);
                                                                 case WM_ERASEBKGND:
                                                                  bearbeitenereignisse(window, &window->peraseBackgroundEvents, &params);
                                                                  return(1);
                                                                 case WM_PAINT:
                                                                  if(window->UseBeginPaint()){
                                                                   PAINTSTRUCT ps;
                                                                   BeginPaint(hWnd, &ps);
                                                                   params.zeichnung.hdc = ps.hdc;
                                                                   bearbeitenereignisse(window, &window->ppaintEvents, &params);
                                                                   EndPaint(hWnd, &ps);
                                                                  }else{
                                                                   params.zeichnung.hdc = GetDC(window->handle());
                                                                   ValidateRect(window->handle(), 0);
                                                                   bearbeitenereignisse(window, &window->ppaintEvents, &params);
                                                                   ReleaseDC(window->handle(), params.zeichnung.hdc);
                                                                  };
                                                                  return(0);
                                                                     
                                                                 case WM_CTLCOLOREDIT:
                                                                 case WM_CTLCOLORSTATIC:{
                                                                  _guifenster*window2=findenfenster((HWND)lParam);
                                                                  if(window2){
                                                                   LOGBRUSH lb;
                                                                   GetObject(window2->BackgroundBrush(), sizeof(LOGBRUSH), &lb);
                                                                   SetBkColor((HDC)wParam, lb.lbColor);
                                                                   SetTextColor((HDC)wParam, window2->farbetext());
                                                                   return((LRESULT)window2->BackgroundBrush());
                                                                  };
                                                                  return((LRESULT)window->BackgroundBrush());
                                                                  };
                                                                 case WM_TIMER:
                                                                  bearbeitenereignisse(window, &window->ptimerEvents, &params);
                                                                  return(0);
                                                                 case WM_CLOSE:
                                                                  bearbeitenereignisse(window, &window->pcloseEvents, &params);
                                                                  return(0);
                                                                 case WM_DESTROY:
                                                                  bearbeitenereignisse(window, &window->pdestroyEvents, &params);
                                                                  //GLog << L"WM_DESTROY: 0x" << window->m_handle << L"\n";  // FIXME
                                                                  window->phandle = 0;  // Zur Sicherheit
                                                                  return(0);
                                                                };
                                                                return(DefWindowProc(hWnd, message, wParam, lParam));
};



//#endif
