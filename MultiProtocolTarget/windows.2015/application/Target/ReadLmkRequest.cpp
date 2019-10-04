
#include "stdafx.h"
#include "TcpServer.h"
#include "ReadLmkRequest.h"
#include "Gpr.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CReadLmkRequest::CReadLmkRequest(CTcpServer *pTcpServer, CGpr *pGpr)
{
	m_pTcpServer = pTcpServer;
	m_pGpr = pGpr;
	m_RequestId = READ_LMK_REQUEST_CODE;
}

CReadLmkRequest::~CReadLmkRequest()
{

}

int CReadLmkRequest::Execute(void *pRequest, void *pReply)
{
	PC_TO_TGT_READ_LMK_REQUEST *pRequestMsg = (PC_TO_TGT_READ_LMK_REQUEST *)pRequest;
	TGT_TO_PC_READ_LMK_REPLY *pReplyMsg = (TGT_TO_PC_READ_LMK_REPLY *)pReply;

	pReplyMsg->Header.Code = READ_LMK_REPLY_CODE;
	pReplyMsg->Header.Length = sizeof(TGT_TO_PC_READ_LMK_REPLY);
	pReplyMsg->Header.Magic = TGT_TO_PC_MAGIC;
	pReplyMsg->Header.Checksum = 0x0;

	m_pGpr->ReadLmk(pRequestMsg->Offset, &pReplyMsg->Data);

	printf("ReadLmkRequest: Offset=0x%x Data=0x%x\n", pRequestMsg->Offset, pReplyMsg->Data);

	m_pTcpServer->Send(pReplyMsg, pReplyMsg->Header.Length);

	return 0;
}
