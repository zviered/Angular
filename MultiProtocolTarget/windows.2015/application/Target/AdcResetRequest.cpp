
#include "stdafx.h"
#include "TcpServer.h"
#include "AdcResetRequest.h"
#include "Gpr.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAdcResetRequest::CAdcResetRequest(CTcpServer *pTcpServer, CGpr *pGpr)
{
	m_pTcpServer = pTcpServer;
	m_pGpr = pGpr;
	m_RequestId = ADC_RESET_REQUEST_CODE;
}

CAdcResetRequest::~CAdcResetRequest()
{

}

int CAdcResetRequest::Execute(void *pRequest, void *pReply)
{
	PC_TO_TGT_ADC_RESET_REQUEST *pRequestMsg = (PC_TO_TGT_ADC_RESET_REQUEST *)pRequest;
	TGT_TO_PC_ADC_RESET_REPLY *pReplyMsg = (TGT_TO_PC_ADC_RESET_REPLY *)pReply;
	E_GPR_ADC_RESET_CONTROL Control;

	pReplyMsg->Header.Code = ADC_RESET_REPLY_CODE;
	pReplyMsg->Header.Length = sizeof(TGT_TO_PC_ADC_RESET_REPLY);
	pReplyMsg->Header.Magic = TGT_TO_PC_MAGIC;
	pReplyMsg->Header.Checksum = 0x0;

	Control = (pRequestMsg->Control == 1) ? GPR_ADC_RESET_ON : GPR_ADC_RESET_OFF;
	m_pGpr->WriteAdcHwReset(pRequestMsg->Device, Control);

	printf("AdcResetRequest: Device=%d Control=%d\n",
		pRequestMsg->Device,
		pRequestMsg->Control);

	m_pTcpServer->Send(pReplyMsg, pReplyMsg->Header.Length);

	return 0;
}
