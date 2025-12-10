#include <_kommunikation.hpp>
#include <_datei.hpp>






//*********************************************************************************************************************************************************************************************************
//																V E R B I N D U N G N E T Z W E R K
//*********************************************************************************************************************************************************************************************************
_verbindungnetzwerk::_verbindungnetzwerk(bool tcp, bool bNonBlocking){
															    ptype=tcp;
															    // create a socket
															    if(tcp)
																 psocket=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
															    else
																 psocket=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
															    // bring the socket into non-blocking mode...
															    if(bNonBlocking)	{
														 	 	 u_long  value=1;
															 	 ioctlsocket(psocket, FIONBIO, &value);
															    };
};
_verbindungnetzwerk::~_verbindungnetzwerk(){
																closesocket(psocket);
};
bool _verbindungnetzwerk::typ()const{
																return(ptype);
};
//*********************************************************************************************************************************************************************************************************
//																C L I E N T V E R B I N D U N G 
//*********************************************************************************************************************************************************************************************************
_clientverbindung::_clientverbindung(_server*s,unsigned int id,unsigned int addr):_listenknotenbasis<_clientverbindung>(s){
																pid=id;			
																paddresse=addr;		
};
_clientverbindung::~_clientverbindung(){
};
//*********************************************************************************************************************************************************************************************************
//																S E R V E R
//*********************************************************************************************************************************************************************************************************
_server::_server(){
																WSADATA  wsa; 
															    if(0 == WSAStartup(MAKEWORD(1,0), &wsa)) 
																 L->l("_server : Winsock gestartet."); 
															    else 
																 L->l("_server : Winsock NICHT gestartet."); 
															    psocket=new _verbindungnetzwerk(true,false);
																sockaddr_in  sin;
															    memset(&sin, 0, sizeof(sin));
															    sin.sin_family      = AF_INET;
															    sin.sin_addr.s_addr = INADDR_ANY;
															    sin.sin_port        = htons(25000);
															   
															    if(SOCKET_ERROR == bind(*psocket,(SOCKADDR*)&sin,sizeof(sin))) L->l("_server : konnte nicht gestartet werden."); else L->l("_server : wurde gestartet.");
															    while(SOCKET_ERROR==listen(*psocket, SOMAXCONN));
															    if(SOCKET_ERROR!=(pconnectedSocket=accept(*psocket,0,0))) L->l("_server : Verbindung mit Client wurde hergestellt.");																 
};
_server::~_server(){
																delete psocket;
																WSACleanup();
};
void _server::aktualisieren(){
																_zeichenkette<char> h="Server an Tonne !";
																send(pconnectedSocket,h.daten(),h.groesse(),0);
};
//*********************************************************************************************************************************************************************************************************
//																C L I E N T
//*********************************************************************************************************************************************************************************************************
_client::_client(){
																WSADATA  wsa; 
															    if(0 == WSAStartup(MAKEWORD(1,0), &wsa)) 
																 L->l("Winsock gestartet."); 
															    else 
																 L->l("Winsock NICHT gestartet."); 
															    psocket=new _verbindungnetzwerk(true,false);
															    memset(&paddress,0,sizeof(paddress));
															    paddress.sin_family      = AF_INET;
															    paddress.sin_addr.s_addr = inet_addr("127.0.0.1");
															    paddress.sin_port        = htons(25000);
															   
															    // connect to the server
															    if(SOCKET_ERROR!=connect(*psocket,(sockaddr *)&paddress,sizeof(paddress))) L->l("Verbunden mit 127.0.0.1."); 
};
_client::~_client(){
																delete(psocket);
																WSACleanup();
};
void _client::aktualisieren(){
															    char  buffer[16];
															    memset(buffer,0,16);
															    if(SOCKET_ERROR!=recv(*psocket, buffer,5,0)) L->l("_client::aktualisieren: empfangen:", buffer);
};