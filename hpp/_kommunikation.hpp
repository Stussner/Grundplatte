//grundplatte : _kommunikation.hpp
//Datum : 25.03.2009




#ifndef _kommunikationh_included
#define _kommunikationh_included

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>

//#undef AF_IPX
//#undef sockaddr
#include <winsock.h>
//#include <ws2tcpip.h>
//#include <iphlpapi.h>
//#include <stdio.h>


class _verbindungnetzwerk;
class _server;
class _clientverbindung;
class _client;




#include <_struktur.hpp>



//enum _nachrichtclient;
//*********************************************************************************************************************************************************************************************************
//																V E R B I N D U N G N E T Z W E R K
//*********************************************************************************************************************************************************************************************************
class _verbindungnetzwerk{
		public:
				_verbindungnetzwerk(bool type, bool bNonBlocking);
				virtual ~_verbindungnetzwerk();
				bool typ()const;     
				operator SOCKET() { return(psocket); };
     				
		private:
				bool ptype;
				SOCKET psocket;
};
//*********************************************************************************************************************************************************************************************************
//																C L I E N T V E R B I N D U N G 
//*********************************************************************************************************************************************************************************************************
class _clientverbindung:public _listenknotenbasis<_clientverbindung>{
		public:
				_clientverbindung(_server*s,unsigned int id,unsigned int addr);
				virtual ~_clientverbindung();
		private:
				unsigned int pid;			
				unsigned int paddresse;	
};
//*********************************************************************************************************************************************************************************************************
//																S E R V E R
//*********************************************************************************************************************************************************************************************************
class _server:public _listebasis<_clientverbindung>{
		public:
				_server();
				virtual ~_server();
				void aktualisieren();
		private:  
				_verbindungnetzwerk*psocket;
				SOCKET pconnectedSocket;
};

//*********************************************************************************************************************************************************************************************************
//																C L I E N T
//*********************************************************************************************************************************************************************************************************

class _client{
		public:
				_client();
				virtual ~_client();
			    void aktualisieren();
		private:				
				 _verbindungnetzwerk*psocket;  // Our Socket
				 sockaddr_in paddress;  // For UDP		
};



#endif
