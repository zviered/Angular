
#ifndef _CTelemetryStatusRequest
#define _CTelemetryStatusRequest

#include "PcRequest.h"

class CI2c;
class CTcpServer;
class CGpr;

class CTelemetryStatusRequest : public CPcRequest
{
private:
	CTcpServer *m_pTcpServer;
	CI2c *m_pI2c;
	CGpr *m_pGpr;

public:
	CTelemetryStatusRequest(CTcpServer *pTcpServer, CI2c *pI2c, CGpr *pGpr);
	virtual ~CTelemetryStatusRequest();
	virtual int   Execute(void *pRequest, void *pReply);
};

#endif 

