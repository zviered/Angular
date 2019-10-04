
#ifndef _CFioSetupRequest
#define _CFioSetupRequest

#include "PcRequest.h"

class CGpr;
class CTcpServer;

class CFioSetupRequest : public CPcRequest
{
private:
	CTcpServer *m_pTcpServer;
	CGpr *m_pGpr;

public:
	CFioSetupRequest(CTcpServer *pTcpServer, CGpr *pGpr);
	virtual ~CFioSetupRequest();
	virtual int   Execute(void *pRequest, void *pReply);
};

#endif 
