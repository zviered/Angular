
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the UDP_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// UDP_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef TCPSERVER_EXPORTS
#define TCPSERVER_API __declspec(dllexport)
#else
#define TCPSERVER_API __declspec(dllimport)
#endif

#include "Winsock.h"

class CTcpServer
{
private:
	int m_Socket;
	int m_ClientSocket;
	sockaddr_in  m_ServerAddress;

public:
	TCPSERVER_API int Open (int Port);

	TCPSERVER_API int WaitForHandShake (void);

	TCPSERVER_API int Send (void *pBuffer, int Size);

	TCPSERVER_API int Receive (void *pBuffer, int Size);
};