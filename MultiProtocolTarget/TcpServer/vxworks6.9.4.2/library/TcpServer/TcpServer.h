#include "wrn\coreip\netinet\in.h"

class CTcpServer
{
private:
	int m_Socket;
	int m_ListenSocket;
	sockaddr_in  m_ServerAddress;

public:
	int Open (int Port);

	int AcceptConnection (void);

	int Send (void *pBuffer, int Size);

	int Receive (void *pBuffer, int Size);
};
