
#include "stdafx.h"
#include "TcpServer.h"
#include "ReadNcoRequest.h"
#include "Gpr.h"
//#include "ModuleIn.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CReadNcoRequest::CReadNcoRequest(CTcpServer *pTcpServer, CGpr *pGpr)
{
	m_pTcpServer = pTcpServer;
	m_pGpr = pGpr;
	m_RequestId = READ_NCO_REQUEST_CODE;
}

CReadNcoRequest::~CReadNcoRequest()
{

}

int CReadNcoRequest::Execute(void *pRequest, void *pReply)
{
	PC_TO_TGT_READ_NCO_REQUEST *pRequestMsg = (PC_TO_TGT_READ_NCO_REQUEST *)pRequest;
	TGT_TO_PC_READ_NCO_REPLY *pReplyMsg = (TGT_TO_PC_READ_NCO_REPLY *)pReply;
	UINT32 NcoSelect, NcoFreq, NcoId;
	unsigned int Msb, Lsb;

	pReplyMsg->Header.Code = READ_NCO_REPLY_CODE;
	pReplyMsg->Header.Length = sizeof(TGT_TO_PC_READ_NCO_REPLY);
	pReplyMsg->Header.Magic = TGT_TO_PC_MAGIC;
	pReplyMsg->Header.Checksum = 0x0;

	NcoId = pRequestMsg->NcoId;

	//Read 2 registers
	m_pGpr->ReadAdc(pRequestMsg->Device,
		GPR_ADC_DECIMATION_FILTER_PAGE,
		(E_GPR_ADC_CHANNEL)pRequestMsg->Channel,
		NCO_FREQ_OFFSET[NcoId][0],
		&Lsb);

	m_pGpr->ReadAdc(pRequestMsg->Device,
		GPR_ADC_DECIMATION_FILTER_PAGE,
		(E_GPR_ADC_CHANNEL)pRequestMsg->Channel,
		NCO_FREQ_OFFSET[NcoId][1],
		&Msb);

	//Construct NCO frequency
	NcoFreq = (Msb << 8) | Lsb;
	pReplyMsg->Frequency = NcoFreq;

	printf("ReadNcoRequest: Device=%d Channel=%d Nco=%d Frequency=0x%x\n",
		pRequestMsg->Device,
		pRequestMsg->Channel,
		pRequestMsg->NcoId,
		pReplyMsg->Frequency);

	m_pTcpServer->Send(pReplyMsg, pReplyMsg->Header.Length);

	return 0;
}
