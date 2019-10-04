#include "stdafx.h"
#include "HttpProtocol.h"
#include "TcpServer.h"
#include "PcToTgtIcd.h"
#include "TgtToPcIcd.h"
#include "string.h"
#include "jsmn.h"

/****************************************************************************/
CHttpProtocol::CHttpProtocol()
{
	m_pRequestMsg = new char[MAX_IN_MSG_SIZE];
	m_pReplyMsg = new char[MAX_OUT_MSG_SIZE];
	m_pJsonParser = new jsmn_parser();
	m_pJsonToken = new jsmntok_t[MAX_JSON_TOKENS];
	m_pReplyBody = new char[MAX_OUT_MSG_SIZE];

	memset(m_pJsonToken, 0, sizeof(jsmntok_t)*MAX_JSON_TOKENS);
}

/****************************************************************************/
CHttpProtocol::~CHttpProtocol()
{
}

/****************************************************************************/
int CHttpProtocol::Open()
{
	m_pTcpServer->Open(PC_TO_TGT_HTTP_PORT);
	printf("Waiting for host connection...\n");

	jsmn_init(m_pJsonParser);

	return 0;
}

/****************************************************************************/
int CHttpProtocol::Init()
{
	CreateThread(NULL,			// default security attributes
		0,                      // use default stack size  
		Thread,     // thread function name
		this,					// argument to thread function 
		0,                      // use default creation flags 
		NULL);

	return 0;
}

/****************************************************************************/
int CHttpProtocol :: ReplyPost(void)
{
	SYSTEMTIME SystemTime;
	char Date[64];
	int rc;
	int ReplySize32;
	TGT_TO_PC_HEADER	*Header = (TGT_TO_PC_HEADER *)m_pTgtToPcReply;
	UINT32 *pWord32 = (UINT32 *)m_pTgtToPcReply;
	char NumStr[16];
	int BodyLength;
	char BodyLengthHeader[64];

	//Add date header
	GetSystemTime(&SystemTime);
	sprintf_s(Date, "Date: %s, %d %s %d %02d:%02d:%02d GMT\r\n", DAY[SystemTime.wDayOfWeek],
		SystemTime.wDay, MONTH[SystemTime.wMonth - 1], SystemTime.wYear,
		SystemTime.wHour, SystemTime.wMinute, SystemTime.wSecond);

	m_pReplyMsg[0] = 0;
	m_pReplyBody[0] = 0;

	strcat_s(m_pReplyMsg, MAX_OUT_MSG_SIZE, "HTTP/1.1 200 OK\r\n");

	//Build response body
	strcat_s(m_pReplyBody, MAX_OUT_MSG_SIZE, "[");
	ReplySize32 = Header->Length >> 2;
	for (int i = 0; i < ReplySize32; i++)
	{
		sprintf_s(NumStr, MAX_OUT_MSG_SIZE, "%d", *pWord32);
		strcat_s(m_pReplyBody, MAX_OUT_MSG_SIZE, NumStr);
		//Add , between body elements
		if (i<ReplySize32-1)
			strcat_s(m_pReplyBody, MAX_OUT_MSG_SIZE, ",");
		pWord32++;
	}
	strcat_s(m_pReplyBody, MAX_OUT_MSG_SIZE, "]");
	BodyLength = strlen(m_pReplyBody);
	sprintf_s(BodyLengthHeader, sizeof(BodyLengthHeader), "Content-Length: %d\r\n", BodyLength);

	strcat_s(m_pReplyMsg, MAX_OUT_MSG_SIZE, BodyLengthHeader);
	strcat_s(m_pReplyMsg, MAX_OUT_MSG_SIZE, "Content-Type: text/html\r\n");
	strcat_s(m_pReplyMsg, MAX_OUT_MSG_SIZE, "Server: Microsoft-HTTPAPI/2.0\r\n");
	strcat_s(m_pReplyMsg, MAX_OUT_MSG_SIZE, "Access-Control-Allow-Origin: *\r\n");
	strcat_s(m_pReplyMsg, MAX_OUT_MSG_SIZE, Date);
	strcat_s(m_pReplyMsg, MAX_OUT_MSG_SIZE, "\r\n");	
	strcat_s(m_pReplyMsg, MAX_OUT_MSG_SIZE, m_pReplyBody);

	rc = m_pTcpServer->Send (m_pReplyMsg, strlen(m_pReplyMsg));
	if (rc != strlen(m_pReplyMsg))
		printf("send failed\n");

	m_pTcpServer->Close();
	return 0;
}

/*********************************************************************/
void CHttpProtocol::CopyToStream(void *pDest, char *pSrc)
{
	char *pBody;
	jsmntok_t *pToken = m_pJsonToken;
	jsmntok_t *pNextToken;
	char *pTokenStart;
	char Name[256] = "";
	char TokenValueStr[16] = "";
	int  Value;
	UINT32 *pWord32 = (UINT32 *)pDest;

	//Point to start of tokens
	pBody = (char*)memchr(pSrc, '{', MAX_IN_MSG_SIZE);
	jsmn_parse(m_pJsonParser, pBody, strlen(pBody), m_pJsonToken, MAX_JSON_TOKENS);

	while (pToken->type != JSMN_UNDEFINED)
	{
		/*pTokenStart = pBody + pToken->start;
		strncpy_s(Name, pTokenStart, pToken->end - pToken->start);
		printf("Name=%s Type=%d\n", Name, pToken->type);
		pToken++;
		continue;*/

		pNextToken = pToken + 1;
		if (pToken->type == JSMN_STRING &&
			(pNextToken->type == JSMN_PRIMITIVE ||
			 pNextToken->type == JSMN_STRING))
		{
			//Get token name. For debug purpose only
			pTokenStart = pBody + pToken->start;
			strncpy_s(Name, pTokenStart, pToken->end - pToken->start);

			//Go next token. 
			pToken++;
			pTokenStart = pBody + pToken->start;
			//Copy token value
			strncpy_s(TokenValueStr, pTokenStart, pToken->end - pToken->start);
			//Convert string to int
			sscanf_s(TokenValueStr, "%d", &Value);
			//printf("Name=%s Value=%d\n", Name, Value);
			*pWord32 = Value;
			pWord32++;
		}

		pToken++;
	}
}

/****************************************************************************/
int CHttpProtocol::Loop()
{
	PC_TO_TGT_HEADER *pHeader = (PC_TO_TGT_HEADER *)m_pPcToTgtRequest;
	char *pDest = m_pRequestMsg;
	int rc;

	while (1)
	{
		m_pTcpServer->WaitForHandShake();

		//Receive min message
		rc = m_pTcpServer->Receive(pDest, MIN_REQUEST_SIZE);
		pDest += rc;
		
		//Receive rest of message
		rc = m_pTcpServer->Receive(pDest, MAX_IN_MSG_SIZE);

		if (strstr(m_pRequestMsg, "POST"))
		{
			CopyToStream(m_pPcToTgtRequest, m_pRequestMsg);

			if (pHeader->Code >= LAST_REQUEST_CODE)
				printf("Code=%x\n", pHeader->Code);
			else
				Handle(pHeader->Code);

			ReplyPost ();
		}
	}
}

/****************************************************************************/
DWORD CHttpProtocol::Thread(LPVOID lpParam)
{
	CHttpProtocol *pHttpProtocol = (CHttpProtocol *)lpParam;

	pHttpProtocol->Open();
	pHttpProtocol->Loop();

	return 0;
}