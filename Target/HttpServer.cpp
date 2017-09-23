#include "StdAfx.h"
#include "HttpServer.h"
#include <winsock2.h>


/*********************************************************************/
CHttpServer::CHttpServer(void)
{
	m_pInMsg = new char[MAX_IN_MSG_SIZE];
	m_pToken = new char[MAX_TOKEN_SIZE];
	m_pJsonParser = new jsmn_parser();
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

	if (listen(Socket , 1000000)!=0)
	{
		printf ("listen failed. LastError=0x%x\n", WSAGetLastError());
		return -1;
	}

	jsmn_init(m_pJsonParser);

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
void CHttpServer::GetTokenName (char *pBody, jsmntok_t Token, char *pName)
{
	char *pTokenStart;

	pTokenStart = pBody + Token.start;
	strncpy (pName, pTokenStart, Token.end - Token.start);
}

/*********************************************************************/
int CHttpServer::GetTokenValue (char *pBody, jsmntok_t Token)
{
	char TokenValueStr[8]="";
	char *pTokenStart;
	int TokenValue;

	pTokenStart = pBody + Token.start;
	strncpy (TokenValueStr, pTokenStart, Token.end - Token.start);

	sscanf (TokenValueStr,"%d",&TokenValue);

	return TokenValue;
}

/*********************************************************************/
int CHttpServer::Respond (void)
{
	int InMsgSize=0;
	char *pNextToken=NULL;
	char OkMsg[1024] = "HTTP/1.1 200 OK\r\nContent-Length: 17\r\nServer: Microsoft-HTTPAPI/2.0\r\nAccess-Control-Allow-Origin: *\r\n";
	int rc;
	SYSTEMTIME SystemTime;
	char Date[64];
	char *pDest = m_pInMsg;
	int Rcvd;
	char *pBody;
	char TokenName[8]="";
	char *pTokenStart;

	memset(m_pInMsg, 0, MAX_IN_MSG_SIZE);
	
	//Receive minimum message
	Rcvd = recv (m_AcceptSocket,pDest,MIN_REQUEST_SIZE,0);
	if (Rcvd<=0)
		return 0;
	printf ("Rcvd=%d\n",Rcvd);

	pDest+=Rcvd;
	InMsgSize+=Rcvd;
	//Receive rest of message
	Rcvd = recv (m_AcceptSocket,pDest,MAX_IN_MSG_SIZE,0);
	printf ("Rcvd=%d\n",Rcvd);

	printf("InMsgSize=%d\n", InMsgSize);

	m_pToken = strtok_s (m_pInMsg, " \t\n", &pNextToken);

	if (strstr (m_pToken, "POST"))
	{
		pBody = (char*)memchr (m_pInMsg,'{',MAX_IN_MSG_SIZE);
		jsmn_parse (m_pJsonParser,pBody,strlen (pBody), m_JsonToken, MAX_JSON_TOKENS);

		//Check that the first token is a string
		if (m_JsonToken[1].type != JSMN_STRING)
		{
			printf ("Body=%s. First token is not a string\n");
			return 0;
		}

		GetTokenName (pBody, m_JsonToken[1], TokenName);
		int TokenVal = GetTokenValue (pBody, m_JsonToken[2]);

		//Add date header
		GetSystemTime(&SystemTime);
		sprintf_s(Date, "Date: %s, %d %s %d %02d:%02d:%02d GMT\r\n\r\n",DAY[SystemTime.wDayOfWeek],
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
