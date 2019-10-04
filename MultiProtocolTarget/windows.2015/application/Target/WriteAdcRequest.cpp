
#include "stdafx.h"
#include "TcpServer.h"
#include "WriteAdcRequest.h"
#include "Gpr.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWriteAdcRequest::CWriteAdcRequest(CTcpServer *pTcpServer, CGpr *pGpr)
{
	m_pTcpServer = pTcpServer;
	m_pGpr = pGpr;
	m_RequestId = WRITE_ADC_REQUEST_CODE;
}

CWriteAdcRequest::~CWriteAdcRequest()
{

}

int CWriteAdcRequest::Execute(void *pRequest, void *pReply)
{
	PC_TO_TGT_WRITE_ADC_REQUEST *pRequestMsg = (PC_TO_TGT_WRITE_ADC_REQUEST *)pRequest;
	TGT_TO_PC_WRITE_ADC_REPLY *pReplyMsg = (TGT_TO_PC_WRITE_ADC_REPLY *)pReply;

	pReplyMsg->Header.Code = WRITE_ADC_REPLY_CODE;
	pReplyMsg->Header.Length = sizeof(TGT_TO_PC_WRITE_ADC_REPLY);
	pReplyMsg->Header.Magic = TGT_TO_PC_MAGIC;
	pReplyMsg->Header.Checksum = 0x0;

	printf("WriteAdcRequest: Device=%d Page=%d Channel=%d Address=0x%x Data=0x%x\n",
		pRequestMsg->Device,
		pRequestMsg->Page,
		pRequestMsg->Channel,
		pRequestMsg->Address,
		pRequestMsg->Data);

	m_pGpr->WriteAdc(pRequestMsg->Device,
		(E_GPR_ADC_PAGE)pRequestMsg->Page,
		(E_GPR_ADC_CHANNEL)pRequestMsg->Channel,
		pRequestMsg->Address,
		pRequestMsg->Data);

	m_pTcpServer->Send(pReplyMsg, pReplyMsg->Header.Length);

	return 0;
}
