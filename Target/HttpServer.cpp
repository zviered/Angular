#include "StdAfx.h"
#include "HttpServer.h"
#include <winsock2.h>
#include "jsmn.h"
#include "WaveformRequest.h"


/*********************************************************************/
CHttpServer::CHttpServer(void)
{
	m_pInMsg = new char[MAX_IN_MSG_SIZE];
	m_pJsonParser = new jsmn_parser();
	m_pJsonToken = new jsmntok_t[MAX_JSON_TOKENS];

	memset(m_pJsonToken, 0, sizeof(jsmntok_t)*MAX_JSON_TOKENS);
	m_pWaveformRequest = new WaveformRequest();
}

/*********************************************************************/
CHttpServer::~CHttpServer(void)
{
}

/*********************************************************************/
int CHttpServer::Init (int Port)
{
	WSADATA wsa;
	struct sockaddr_in Server;
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
void CHttpServer::CopyToStream(void *pDest, char *pSrc)
{
	char *pBody;
	jsmntok_t *pToken = m_pJsonToken;
	char *pTokenStart;
	char Name[16]="";
	char TokenValueStr[8] = "";
	int  Value;
	UINT32 *pWord32 = (UINT32 *)pDest;

	//Point to start of tokens
	pBody = (char*)memchr(pSrc, '{', MAX_IN_MSG_SIZE);
	jsmn_parse(m_pJsonParser, pBody, strlen(pBody), m_pJsonToken, MAX_JSON_TOKENS);

	while (pToken->type != JSMN_UNDEFINED)
	{
		if (pToken->type == JSMN_STRING &&
			(pToken + 1)->type == JSMN_PRIMITIVE)
		{
			//Get token name. For debug purpose only
			//pTokenStart = pBody + pToken->start;
			//strncpy(Name, pTokenStart, pToken->end - pToken->start);

			//Go next token. 
			pToken++;
			pTokenStart = pBody + pToken->start;
			//Copy token value
			strncpy(TokenValueStr, pTokenStart, pToken->end - pToken->start);
			//Convert string to int
			sscanf(TokenValueStr, "%d", &Value);
			//printf("Name=%s Value=%d\n", Name, Value);
			*pWord32 = Value;
			pWord32++;
		}

		pToken++;
	}
}

/*********************************************************************/
int CHttpServer::Respond (void)
{
	int InMsgSize=0;
	char OkMsg[1024]="HTTP/1.1 200 OK\r\nAccess-Control-Allow-Origin: *\r\n";
	int rc;
	SYSTEMTIME SystemTime;
	char Date[64];
	char *pDest = m_pInMsg;
	int Rcvd;

	memset(m_pInMsg, 0, MAX_IN_MSG_SIZE);
	
	//Receive minimum message
	Rcvd = recv (m_AcceptSocket,pDest,MIN_REQUEST_SIZE,0);
	if (Rcvd<=0)
		return 0;
	//printf ("Rcvd=%d\n",Rcvd);

	pDest+=Rcvd;
	InMsgSize+=Rcvd;
	//Receive rest of message
	Rcvd = recv (m_AcceptSocket,pDest,MAX_IN_MSG_SIZE,0);
	//printf ("Rcvd=%d\n",Rcvd);

	//printf("InMsgSize=%d\n", InMsgSize);

	if (strstr (m_pInMsg, "POST"))
	{
		CopyToStream(m_pWaveformRequest, m_pInMsg);

		//Add date header
		GetSystemTime(&SystemTime);
		sprintf_s(Date, "Date: %s, %d %s %d %02d:%02d:%02d GMT\r\n\r\n",DAY[SystemTime.wDayOfWeek],
														SystemTime.wDay, MONTH[SystemTime.wMonth-1], SystemTime.wYear,
													    SystemTime.wHour, SystemTime.wMinute, SystemTime.wSecond);
		//strcat_s(OkMsg, Date);

		rc=send(m_AcceptSocket, OkMsg, strlen(OkMsg),0);
		if (rc != strlen(OkMsg))
			printf("send failed\n");
	}
	else if (strstr (m_pInMsg, "GET"))
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
