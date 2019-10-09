// TcpServer.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "Winsock2.h"
#include "TcpServer.h"
#include "stdio.h"

// This is the constructor of a class that has been exported.
// see TcpServer.h for the class definition
int CTcpServer::Open(int Port, int Timeout, char *IpAddress)
{
	WSADATA wsaData;
	int rc;
	DWORD RecvTimeout = 0;
	DWORD RecvBuf;
	int Size;
	int rcvbuf;
	int len = sizeof(rcvbuf);

	rc = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (rc != 0)
		return -1;

	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
	{
		WSACleanup();
		return -1;
	}

	m_Socket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_Socket < 0)
		return -1;

	memset((char *)&m_ServerAddress, 0, sizeof(sockaddr_in));

	m_ServerAddress.sin_family = AF_INET;
	m_ServerAddress.sin_port = htons(Port);
	m_ServerAddress.sin_addr.s_addr = htonl(INADDR_ANY);

	rc = bind(m_Socket, (struct sockaddr *) &m_ServerAddress, sizeof(m_ServerAddress));
	if (rc != 0)
		return -1;

	rc = listen(m_Socket, SOMAXCONN);
	if (rc != 0)
		return -1;

	if (setsockopt(m_Socket, SOL_SOCKET, SO_RCVTIMEO, (char*)&RecvTimeout, sizeof(DWORD))<0)
		return GetLastError();

	if (getsockopt(m_Socket, SOL_SOCKET, SO_RCVBUF, (char*)&rcvbuf, &len) < 0)
		return GetLastError();

	return 0;
}

/**********************************************************************/
int CTcpServer::WaitForHandShake(void)
{
	sockaddr_in  ClientAddress;
	int ClientLength = sizeof(ClientAddress);

	m_ClientSocket = accept(m_Socket, (struct sockaddr *) &ClientAddress, &ClientLength);
	if (m_ClientSocket<0)
	{
		return WSAGetLastError();
	}
	return 0;
}

/**********************************************************************/
int CTcpServer::Send(void *pBuffer, int Size)
{
	int rc;

	rc = sendto(m_ClientSocket, (const char*)pBuffer, Size, 0, (sockaddr*)&m_ServerAddress, sizeof(sockaddr));

	return Size;
}

/**********************************************************************/
int CTcpServer::Receive(void *pBuffer, int Size)
{
	int rc;

	rc = recv(m_ClientSocket, (char*)pBuffer, Size, 0);
	if (rc < 0)
	{
		printf("recv: rc=%d Error=0x%x\n", rc,GetLastError());
	}
	return rc;
}

/**********************************************************************/
int CTcpServer::Close(void)
{
	BOOL rc;

	rc = closesocket(m_ClientSocket);
	if (rc == FALSE)
		return GetLastError();

	return 0;
}