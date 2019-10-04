
#ifndef _CAdcPowerRequest
#define _CAdcPowerRequest

#include "PcRequest.h"

class CGpr;
class CTcpServer;

class CAdcPowerRequest : public CPcRequest
{
private:
	CTcpServer *m_pTcpServer;
	CGpr *m_pGpr;

public:
	CAdcPowerRequest(CTcpServer *pTcpServer, CGpr *m_pGpr);
	virtual ~CAdcPowerRequest();
	virtual int   Execute(void *pRequest, void *pReply);
};

#endif 
