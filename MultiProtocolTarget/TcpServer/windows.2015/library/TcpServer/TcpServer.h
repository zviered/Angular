// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the TCPSERVER_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// TCPSERVER_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef TCPSERVER_EXPORTS
#define TCPSERVER_API __declspec(dllexport)
#else
#define TCPSERVER_API __declspec(dllimport)
#endif

#include "Winsock.h"

// This class is exported from the TcpServer.dll
class TCPSERVER_API CTcpServer {

private:
	int m_Socket;
	int m_ClientSocket;
	sockaddr_in  m_ServerAddress;

public:
	CTcpServer(void) {};
	// TODO: add your methods here.

	int Open(int Port, int Timeout = 0, char *IpAddress = NULL);

	int WaitForHandShake(void);

	int Send(void *pBuffer, int Size);

	int Receive(void *pBuffer, int Size);

	int Close(void);

};
