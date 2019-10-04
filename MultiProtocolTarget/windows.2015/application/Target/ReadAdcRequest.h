
#ifndef _CReadAdcRequest
#define _CReadAdcRequest

#include "PcRequest.h"

class CGpr;
class CTcpServer;

class CReadAdcRequest : public CPcRequest
{
private:
	CTcpServer *m_pTcpServer;
	CGpr *m_pGpr;

public:
	CReadAdcRequest(CTcpServer *pTcpServer, CGpr *CGpr);
	virtual ~CReadAdcRequest();
	virtual int   Execute(void *pRequest, void *pReply);
};

#endif 
