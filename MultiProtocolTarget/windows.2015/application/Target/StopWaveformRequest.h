#pragma once
#include "PcRequest.h"

class CTcpServer;
class CGpr;
class CSmcTask;

class CStopWaveformRequest :
	public CPcRequest
{
private:
	CTcpServer *m_pTcpServer;
	CGpr *m_pGpr;
	CSmcTask *m_pSmcTask;

public:
	CStopWaveformRequest(CTcpServer *pTcpServer, CGpr *pGpr, CSmcTask *pSmcTask);
	~CStopWaveformRequest();
};

