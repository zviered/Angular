
#include "stdafx.h"
#include "TcpServer.h"
#include "ReadAdcRequest.h"
#include "Gpr.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CReadAdcRequest::CReadAdcRequest(CTcpServer *pTcpServer, CGpr *CGpr)
{
	m_pTcpServer = pTcpServer;
	m_pGpr = CGpr;
	m_RequestId = READ_ADC_REQUEST_CODE;
}

CReadAdcRequest::~CReadAdcRequest()
{

}

int CReadAdcRequest::Execute(void *pRequest, void *pReply)
{
	PC_TO_TGT_READ_ADC_REQUEST *pRequestMsg = (PC_TO_TGT_READ_ADC_REQUEST *)pRequest;
	TGT_TO_PC_READ_ADC_REPLY *pReplyMsg = (TGT_TO_PC_READ_ADC_REPLY *)pReply;

	pReplyMsg->Header.Code = READ_ADC_REPLY_CODE;
	pReplyMsg->Header.Length = sizeof(TGT_TO_PC_READ_ADC_REPLY);
	pReplyMsg->Header.Magic = TGT_TO_PC_MAGIC;
	pReplyMsg->Header.Checksum = 0x0;

	m_pGpr->ReadAdc(pRequestMsg->Device,
		(E_GPR_ADC_PAGE)pRequestMsg->Page,
		(E_GPR_ADC_CHANNEL)pRequestMsg->Channel,
		pRequestMsg->Address,
		&pReplyMsg->Data);

	printf("ReadAdcRequest: Device=%d Page=%d Channel=%d Address=0x%x Data=0x%x\n",
		pRequestMsg->Device,
		pRequestMsg->Page,
		pRequestMsg->Channel,
		pRequestMsg->Address,
		pReplyMsg->Data);

	m_pTcpServer->Send(pReplyMsg, pReplyMsg->Header.Length);

	return 0;
}
