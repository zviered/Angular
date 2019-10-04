#pragma once
#include "PcRequest.h"
#include "SmcTask.h"

class CTcpServer;
class CGpr;
class CSmcTask;

class CWriteWaveformRequest :
	public CPcRequest
{
private:
	CSmcTask *m_pSmcTask;
	CGpr *m_pGpr;
	CTcpServer *m_pTcpServer;

public:
	CWriteWaveformRequest(CTcpServer *pTcpServer, CGpr *pGpr, CSmcTask *pSmcTask);
	~CWriteWaveformRequest();
	virtual int   Execute(void *pRequest, void *pReply);

};

