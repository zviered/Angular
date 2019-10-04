#include "stdafx.h"
#include "WriteWaveformRequest.h"
#include "TcpServer.h"
#include "Gpr.h"


/****************************************************************************************************/
CWriteWaveformRequest::CWriteWaveformRequest(CTcpServer *pTcpServer, CGpr *pGpr, CSmcTask *pSmcTask)
{
	m_pGpr = pGpr;
	m_pTcpServer = pTcpServer;
	m_RequestId = WRITE_WAVEFORM_REQUEST_CODE;
	m_pSmcTask = pSmcTask;
}

/***************************************************************************************************/
CWriteWaveformRequest::~CWriteWaveformRequest()
{
}

/***************************************************************************************************/
int CWriteWaveformRequest::Execute(void *pRequest, void *pReply)
{
	PC_TO_TGT_WRITE_WAVEFORM_REQUEST *pRequestMsg = (PC_TO_TGT_WRITE_WAVEFORM_REQUEST *)pRequest;
	TGT_TO_PC_WRITE_WAVEFORM_REPLY *pReplyMsg = (TGT_TO_PC_WRITE_WAVEFORM_REPLY *)pReply;

	pReplyMsg->Header.Code = WRITE_WAVEFORM_REPLY_CODE;
	pReplyMsg->Header.Length = sizeof(TGT_TO_PC_WRITE_WAVEFORM_REPLY);
	pReplyMsg->Header.Magic = TGT_TO_PC_MAGIC;
	pReplyMsg->Header.Checksum = 0x0;

	//m_pSmcTask->WriteWaveform(pRequestMsg);
	
		printf(" Num1=%d \n, Num2=%d \n, Num3=%d \n , Num4=%d \n ",
			pRequestMsg->Dwell[0].Timing.FirstPulseDelay,
			pRequestMsg->Dwell[0].Timing.LastPulseDelay,
			pRequestMsg->Dwell[0].Timing.PriLength,
			pRequestMsg->Dwell[0].Timing.NofPRIsInSmc);
		

		m_pGpr->WriteFirstPulseDelay(pRequestMsg->Dwell[0].Timing.FirstPulseDelay);
		m_pGpr->WriteLastPulseDelay(pRequestMsg->Dwell[0].Timing.LastPulseDelay);
		m_pGpr->WritePriLength(pRequestMsg->Dwell[0].Timing.PriLength);
		m_pGpr->WriteNofPRIsInSmc(pRequestMsg->Dwell[0].Timing.NofPRIsInSmc);
		m_pGpr->WriteA2dSamplingWindow(pRequestMsg->Dwell[0].Timing.A2dSamplingWindowStart, pRequestMsg->Dwell[0].Timing.A2dSamplingWindowLength);

		m_pGpr->WriteArtificialSmc();

		m_pTcpServer->Send(pReplyMsg, pReplyMsg->Header.Length);

	
	

	return 0;
}


