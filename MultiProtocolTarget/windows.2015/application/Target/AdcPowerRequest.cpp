
#include "stdafx.h"
#include "TcpServer.h"
#include "AdcPowerRequest.h"
#include "Gpr.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAdcPowerRequest::CAdcPowerRequest(CTcpServer *pTcpServer, CGpr *pGpr)
{
	m_pTcpServer = pTcpServer;
	m_pGpr = pGpr;
	m_RequestId = ADC_POWER_REQUEST_CODE;
}

CAdcPowerRequest::~CAdcPowerRequest()
{

}

int CAdcPowerRequest::Execute(void *pRequest, void *pReply)
{
	PC_TO_TGT_ADC_POWER_REQUEST *pRequestMsg = (PC_TO_TGT_ADC_POWER_REQUEST *)pRequest;
	TGT_TO_PC_ADC_POWER_REPLY *pReplyMsg = (TGT_TO_PC_ADC_POWER_REPLY *)pReply;
	E_GPR_ADC_POWER_CONTROL Control;

	pReplyMsg->Header.Code = ADC_POWER_REPLY_CODE;
	pReplyMsg->Header.Length = sizeof(TGT_TO_PC_ADC_POWER_REPLY);
	pReplyMsg->Header.Magic = TGT_TO_PC_MAGIC;
	pReplyMsg->Header.Checksum = 0x0;

	Control = (pRequestMsg->Control == 1) ? GPR_ADC_POWER_ON : GPR_ADC_POWER_OFF;
	m_pGpr->WriteAdcPowerControl(pRequestMsg->Device, Control);

	printf("AdcPowerRequest: Device=%d Control=%d\n",
		pRequestMsg->Device,
		pRequestMsg->Control);

	m_pTcpServer->Send(pReplyMsg, pReplyMsg->Header.Length);

	return 0;
}
