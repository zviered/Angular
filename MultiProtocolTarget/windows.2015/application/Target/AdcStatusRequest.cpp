
#include "stdafx.h"
#include "TcpServer.h"
#include "AdcStatusRequest.h"
#include "Gpr.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAdcStatusRequest::CAdcStatusRequest(CTcpServer *pTcpServer, CGpr *pGpr)
{
	m_pTcpServer = pTcpServer;
	m_pGpr = pGpr;
	m_RequestId = ADC_STATUS_REQUEST_CODE;
}

CAdcStatusRequest::~CAdcStatusRequest()
{

}

int CAdcStatusRequest::Execute(void *pRequest, void *pReply)
{
	PC_TO_TGT_ADC_STATUS_REQUEST *pRequestMsg = (PC_TO_TGT_ADC_STATUS_REQUEST *)pRequest;
	TGT_TO_PC_ADC_STATUS_REPLY *pReplyMsg = (TGT_TO_PC_ADC_STATUS_REPLY *)pReply;
	E_GPR_ADC_POWER_CONTROL Control;

	pReplyMsg->Header.Code = ADC_STATUS_REPLY_CODE;
	pReplyMsg->Header.Length = sizeof(TGT_TO_PC_ADC_POWER_REPLY);
	pReplyMsg->Header.Magic = TGT_TO_PC_MAGIC;
	pReplyMsg->Header.Checksum = 0x0;

	m_pGpr->ReadAdcHwReset(pRequestMsg->Device, (E_GPR_ADC_RESET_CONTROL *)&pReplyMsg->Reset);
	m_pGpr->ReadAdcPowerControl(pRequestMsg->Device, (E_GPR_ADC_POWER_CONTROL *)&pReplyMsg->Power);

	printf("AdcStatusRequest: Device=%d Power=%d Reset=%d\n",
		pRequestMsg->Device,
		pReplyMsg->Power,
		pReplyMsg->Reset);

	m_pTcpServer->Send(pReplyMsg, pReplyMsg->Header.Length);

	return 0;
}
