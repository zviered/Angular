// udp.cpp : Defines the entry point for the DLL application.
//

#include "StdAfx.h"
#include "Winsock2.h"
#include "TcpServer.h"
#include "stdio.h"

/**********************************************************************/
TCPSERVER_API int CTcpServer::Open (int Port)
{
	WSADATA wsaData;
	int rc;

	rc = WSAStartup(MAKEWORD( 2, 2 ), &wsaData );
	if (rc!=0)
		return -1;

	if ( LOBYTE( wsaData.wVersion ) != 2 || HIBYTE( wsaData.wVersion ) != 2 ) 
	{
		WSACleanup( );
		return -1;
	}

	m_Socket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_Socket < 0)
	{
		printf ("udp_server_open: socket failed\n");
		return -1;
	}

	memset ((char *) &m_ServerAddress, 0,sizeof (sockaddr_in)); 
    
	m_ServerAddress.sin_family = AF_INET; 
    m_ServerAddress.sin_port = htons (Port); 
 	m_ServerAddress.sin_addr.s_addr = htonl(INADDR_ANY); 
	
	rc = bind(m_Socket, (struct sockaddr *) &m_ServerAddress, sizeof(m_ServerAddress));
	if (rc!=0)
		return -1;

	rc = listen(m_Socket, SOMAXCONN);
	if (rc!=0)
		return -1;

	return 0;
}

/**********************************************************************/
TCPSERVER_API int CTcpServer::WaitForHandShake (void)
{
	sockaddr_in  ClientAddress;
	int ClientLength=sizeof(ClientAddress);

	m_ClientSocket = accept (m_Socket,(struct sockaddr *) &ClientAddress, &ClientLength);
	if (m_ClientSocket<0)
	{
		return WSAGetLastError ();
	}
	return 0;
}

/**********************************************************************/
TCPSERVER_API int CTcpServer::Send (void *pBuffer, int Size)
{
	int rc;
	
	rc=sendto (m_ClientSocket,(const char*)pBuffer,Size,0,(sockaddr*)&m_ServerAddress,sizeof (sockaddr));

	return Size;
}

/**********************************************************************/
TCPSERVER_API int CTcpServer::Receive (void *pBuffer, int Size)
{
	return recv (m_ClientSocket,(char*)pBuffer,Size,0);
}