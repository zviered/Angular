#include "stdafx.h"
#include "StopWaveformRequest.h"


CStopWaveformRequest::CStopWaveformRequest(CTcpServer *pTcpServer, CGpr *pGpr, CSmcTask *pSmcTask)
{
	m_pTcpServer = pTcpServer;
	m_pGpr = pGpr;
	m_RequestId = STOP_WAVEFORM_REQUEST_CODE;
	m_pSmcTask = pSmcTask;
}


CStopWaveformRequest::~CStopWaveformRequest()
{
}
