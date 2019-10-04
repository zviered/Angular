
#include "stdafx.h"
#include "TcpServer.h"
#include "WriteLmkRequest.h"
#include "Gpr.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWriteLmkRequest::CWriteLmkRequest(CTcpServer *pTcpServer, CGpr *pGpr)
{
	m_pTcpServer = pTcpServer;
	m_pGpr = pGpr;
	m_RequestId = WRITE_LMK_REQUEST_CODE;
}

CWriteLmkRequest::~CWriteLmkRequest()
{

}

int CWriteLmkRequest::Execute(void *pRequest, void *pReply)
{
	PC_TO_TGT_WRITE_LMK_REQUEST *pRequestMsg = (PC_TO_TGT_WRITE_LMK_REQUEST *)pRequest;
	TGT_TO_PC_WRITE_LMK_REPLY *pReplyMsg = (TGT_TO_PC_WRITE_LMK_REPLY *)pReply;

	pReplyMsg->Header.Code = WRITE_PCI_REPLY_CODE;
	pReplyMsg->Header.Length = sizeof(TGT_TO_PC_WRITE_PCI_REPLY);
	pReplyMsg->Header.Magic = TGT_TO_PC_MAGIC;
	pReplyMsg->Header.Checksum = 0x0;

	m_pGpr->WriteLmk(pRequestMsg->Offset, pRequestMsg->Data);

	printf("WriteLmkRequest: Offset=0x%x Data=0x%x\n", pRequestMsg->Offset, pRequestMsg->Data);

	m_pTcpServer->Send(pReplyMsg, pReplyMsg->Header.Length);

	return 0;
}
