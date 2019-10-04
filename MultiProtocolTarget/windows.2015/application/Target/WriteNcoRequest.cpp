
#include "stdafx.h"
#include "TcpServer.h"
#include "WriteNcoRequest.h"
#include "Gpr.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWriteNcoRequest::CWriteNcoRequest(CTcpServer *pTcpServer, CGpr *pGpr)
{
	m_pTcpServer = pTcpServer;
	m_pGpr = pGpr;
	m_RequestId = WRITE_NCO_REQUEST_CODE;
}

CWriteNcoRequest::~CWriteNcoRequest()
{

}

int CWriteNcoRequest::Execute(void *pRequest, void *pReply)
{
	PC_TO_TGT_WRITE_NCO_REQUEST *pRequestMsg = (PC_TO_TGT_WRITE_NCO_REQUEST *)pRequest;
	TGT_TO_PC_WRITE_NCO_REPLY *pReplyMsg = (TGT_TO_PC_WRITE_NCO_REPLY *)pReply;
	unsigned int Msb, Lsb, NcoFreq, NcoId;

	pReplyMsg->Header.Code = WRITE_NCO_REPLY_CODE;
	pReplyMsg->Header.Length = sizeof(TGT_TO_PC_WRITE_NCO_REPLY);
	pReplyMsg->Header.Magic = TGT_TO_PC_MAGIC;
	pReplyMsg->Header.Checksum = 0x0;

	NcoId = pRequestMsg->NcoId;

	//Write NCO frequency
	Msb = (pRequestMsg->Frequency & 0xFF00) >> 8;
	Lsb = pRequestMsg->Frequency & 0xFF;

	printf("Freq=0x%x Msb=0x%x Lsb=0x%x\n", pRequestMsg->Frequency, Msb, Lsb);
	//Write 2 registers
	m_pGpr->WriteAdc(pRequestMsg->Device,
		GPR_ADC_DECIMATION_FILTER_PAGE,
		(E_GPR_ADC_CHANNEL)pRequestMsg->Channel,
		NCO_FREQ_OFFSET[NcoId][0],
		Lsb);

	m_pGpr->WriteAdc(pRequestMsg->Device,
		GPR_ADC_DECIMATION_FILTER_PAGE,
		(E_GPR_ADC_CHANNEL)pRequestMsg->Channel,
		NCO_FREQ_OFFSET[NcoId][1],
		Msb);

	//Construct NCO frequency
	printf("WriteNcoRequest: Device=%d Channel=%d Nco=%d Frequency=0x%x\n",
		pRequestMsg->Device,
		pRequestMsg->Channel,
		pRequestMsg->NcoId,
		pRequestMsg->Frequency);

	m_pTcpServer->Send(pReplyMsg, pReplyMsg->Header.Length);

	return 0;
}
