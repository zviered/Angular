// udp.cpp : Defines the entry point for the DLL application.
//

#include "vxworks.h"
#include "TcpServer.h"
#include "sockLib.h"
#include "inetLib.h"
#include "stdio.h"
#include "string.h"
#include "errnoLib.h"

/**********************************************************************/
int CTcpServer::Open (int Port)
{
	int sockAddrSize = sizeof (struct sockaddr_in);

	m_Socket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_Socket < 0)
	{
		printf ("CTcpServer::Open : socket failed\n");
		return -1;
	}

	memset ((char *) &m_ServerAddress, 0,sizeof (sockaddr_in)); 
    
	m_ServerAddress.sin_family = AF_INET; 
	m_ServerAddress.sin_len = sockAddrSize;
    m_ServerAddress.sin_port = htons (Port); 
 	m_ServerAddress.sin_addr.s_addr = htonl (INADDR_ANY);

	if (bind (m_Socket, (struct sockaddr *)&m_ServerAddress, sockAddrSize)==ERROR)
	{
		printf ("Open: bind failed. errno=%d\n",errnoGet ());
		return -1;
	}

	if (listen (m_Socket,1)==ERROR)
	{
		printf ("CTcpServer::Open : listen failed. errno=%d\n",errnoGet ());
		return -1;
	}

	return 0;
}

/**********************************************************************/
int CTcpServer::AcceptConnection (void)
{
	int sockAddrSize = sizeof (struct sockaddr_in);
	sockaddr_in  ClientAddress;

	m_ListenSocket = accept(m_Socket, (struct sockaddr *) &ClientAddress, &sockAddrSize);
	if (m_ListenSocket == ERROR)
	{
		printf ("CTcpClient::AcceptConnection : accept failed. errno=%d\n",errnoGet ());
		return -1;
	}

	return 0;
}

/**********************************************************************/
int CTcpServer::Send (void *pBuffer, int Size)
{
	int rc;
	int Total=0;
	char *pSrc = (char *)pBuffer;

	while (Total<Size)
	{
		rc=write (m_ListenSocket,(char*)pSrc,Size);
		if (rc<=0)
			break;

		Total+=rc;
		pSrc+=rc;
	}

	if (Total==Size)
		return Size;

	return rc;
}

/**********************************************************************/
int CTcpServer::Receive (void *pBuffer, int Size)
{
	int rc=0;
	int Total=0;
	char *pDest = (char *)pBuffer;

	while (Total<Size)
	{
		rc=recv (m_ListenSocket,(char*)pDest,Size,0);
		if (rc<=0)
			break;

		Total+=rc;
		pDest+=rc;
	}
	if (Total==Size)
		return Size;

	return rc;
}
