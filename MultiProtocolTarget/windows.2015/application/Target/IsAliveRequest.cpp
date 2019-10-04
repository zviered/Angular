
#include "stdafx.h"
#include "IsAliveRequest.h"
#include "TcpServer.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CIsAliveRequest::CIsAliveRequest()
{
	m_RequestId = IS_ALIVE_REQUEST_CODE;	
}

CIsAliveRequest::~CIsAliveRequest()
{

}

int CIsAliveRequest::Execute(void *pRequest, void *pReply)
{
	TGT_TO_PC_HEADER *pHeader = (TGT_TO_PC_HEADER *)pReply;
	pHeader->Code = IS_ALIVE_REPLY_CODE;
	pHeader->Length = sizeof(TGT_TO_PC_HEADER);

	printf ("CIsAliveRequest::Execute\n");

	//m_pTcpServer->Send (pReply,pHeader->Length);

	return 0;
}
