
#include "stdafx.h"
#include "TcpServer.h"
#include "FioSetupRequest.h"
#include "Gpr.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFioSetupRequest::CFioSetupRequest(CTcpServer *pTcpServer, CGpr *pGpr)
{
	m_pTcpServer = pTcpServer;
	m_pGpr = pGpr;
	m_RequestId = FIO_SETUP_REQUEST_CODE;
}

CFioSetupRequest::~CFioSetupRequest()
{

}

int CFioSetupRequest::Execute(void *pRequest, void *pReply)
{
	PC_TO_TGT_FIO_SETUP_REQUEST *pRequestMsg = (PC_TO_TGT_FIO_SETUP_REQUEST *)pRequest;
	TGT_TO_PC_FIO_SETUP_REPLY *pReplyMsg = (TGT_TO_PC_FIO_SETUP_REPLY *)pReply;
	GPR_FIO_CHANNEL FioChannel[GPR_N_FIO_TX_CHANNELS];

	pReplyMsg->Header.Code = FIO_SETUP_REPLY_CODE;
	pReplyMsg->Header.Length = sizeof(TGT_TO_PC_FIO_SETUP_REPLY);
	pReplyMsg->Header.Magic = TGT_TO_PC_MAGIC;
	pReplyMsg->Header.Checksum = 0x0;

	//m_pWbr->WriteLong (pRequestMsg->Device, pRequestMsg->Bar, pRequestMsg->Offset, pRequestMsg->Data);
	for (int ChannelId = 0; ChannelId < GPR_N_FIO_TX_CHANNELS; ChannelId++)
	{
		FioChannel[ChannelId].Control = (E_GPR_FIO_CONTROL)pRequestMsg->Channel[ChannelId].Control;
		FioChannel[ChannelId].DataSource = (E_GPR_FIO_DATA_SOURCE)pRequestMsg->Channel[ChannelId].DataSource;
		FioChannel[ChannelId].AdcDevice = (E_GPR_ADC_DEVICE)pRequestMsg->Channel[ChannelId].AdcDevice;
		FioChannel[ChannelId].AdcChannel = (E_GPR_ADC_CHANNEL)pRequestMsg->Channel[ChannelId].AdcChannel;
		FioChannel[ChannelId].AdcSubChannel = (E_GPR_ADC_SUB_CHANNEL)pRequestMsg->Channel[ChannelId].AdcSubChannel;

		printf("Ch%d: Control=%d DataSource=%d AdcDevice=%d AdcChannel=%d Sub=%d\n", ChannelId, FioChannel[ChannelId].Control, FioChannel[ChannelId].DataSource,
			FioChannel[ChannelId].AdcDevice, FioChannel[ChannelId].AdcChannel, FioChannel[ChannelId].AdcSubChannel);

	}

	m_pGpr->WriteFioControl(FioChannel);

	printf("FioSetupRequest: HeaderSize=0x%x DataSize=0x%x TralierSize=0x%x GapSize=0x%x\n",
		pRequestMsg->HeaderSize,
		pRequestMsg->DataSize,
		pRequestMsg->TrailerSize,
		pRequestMsg->GapSize);

	m_pGpr->WriteFioTxSize(pRequestMsg->HeaderSize, pRequestMsg->DataSize, pRequestMsg->TrailerSize, pRequestMsg->GapSize);

	m_pTcpServer->Send(pReplyMsg, pReplyMsg->Header.Length);

	return 0;
}
