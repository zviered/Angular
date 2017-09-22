#include "StdAfx.h"
#include "HttpServer.h"
#include <winsock2.h>

/*********************************************************************/
CHttpServer::CHttpServer(void)
{
	m_pInMsg = new char[MAX_IN_MSG_SIZE];
	m_pToken = new char[MAX_TOKEN_SIZE];
}


/*********************************************************************/
CHttpServer::~CHttpServer(void)
{
}

/*********************************************************************/
int CHttpServer::Init (int Port)
{
	WSADATA wsa;
	struct sockaddr_in Server , Client;
	SOCKET Socket;

	m_Port = Port;

	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        printf("Failed. Error Code : %d",WSAGetLastError());
        return -1;
    }

	if((Socket = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
    {
        printf("socket failed. LastError=0x%x" , WSAGetLastError());
		return -1;
    }
       
	m_Socket = Socket;

    //Prepare the sockaddr_in structure
    Server.sin_family = AF_INET;
    Server.sin_addr.s_addr = INADDR_ANY;
	Server.sin_port = htons( Port );
  
    //Bind
    if( bind(Socket ,(struct sockaddr *)&Server , sizeof(Server)) == SOCKET_ERROR)
    {
        printf("bind failed. LastError=0x%x" , WSAGetLastError());
		return -1;
    }

	if (listen(Socket , 100000)!=0)
	{
		printf ("listen failed. LastError=0x%x\n", WSAGetLastError());
		return -1;
	}

	return 0;
}

/*********************************************************************/
int CHttpServer::Receive (void)
{
	int Length;
	struct sockaddr_in Client;
	Length = sizeof(struct sockaddr_in);
	
	m_AcceptSocket = accept(m_Socket , (struct sockaddr *)&Client, &Length);
	if (m_AcceptSocket == INVALID_SOCKET)
	{
		printf("accept failed. LastError=0x%x\n" , WSAGetLastError());
		return -1;
	}
	else
	{
		Respond  ();
	}

	return 0;
}

/*********************************************************************/
int CHttpServer::Respond (void)
{
	int InMsgSize;
	char *pNextToken=NULL;
	char OkMsg[1024] = "HTTP/1.1 200 OK\r\nContent-Length: 17\r\nServer: Microsoft-HTTPAPI/2.0\r\nAccess-Control-Allow-Origin: *\r\nDate: ";
	int rc;
	SYSTEMTIME SystemTime;
	char Date[64];

	memset(m_pInMsg, 0, MAX_IN_MSG_SIZE);

	InMsgSize = recv (m_AcceptSocket,m_pInMsg,MAX_IN_MSG_SIZE,0);
	printf("InMsgSize=%d\n", InMsgSize);

	m_pToken = strtok_s (m_pInMsg, " \t\n", &pNextToken);

	if (strstr (m_pToken, "POST"))
	{
		GetSystemTime(&SystemTime);
		sprintf_s(Date, "%s, %d %s %d %02d:%02d:%02d GMT\r\n\r\n",DAY[SystemTime.wDayOfWeek],
														SystemTime.wDay, MONTH[SystemTime.wMonth-1], SystemTime.wYear,
													    SystemTime.wHour, SystemTime.wMinute, SystemTime.wSecond);
		strcat_s(OkMsg, Date);
		strcat_s(OkMsg, "HTTP / 1.1 200 OK\n\n");

		rc=send(m_AcceptSocket, OkMsg, strlen(OkMsg),0);
		if (rc != strlen(OkMsg))
			printf("send failed\n");
	}
	else if (strstr (m_pToken, "GET"))
	{

	}
	else
	{
		printf ("Invalid HTTP command\n");
		return -1;
	}

	//closesocket(m_AcceptSocket);
	return 0;
}
