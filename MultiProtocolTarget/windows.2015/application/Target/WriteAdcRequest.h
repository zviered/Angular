
#ifndef _CWriteAdcRequest
#define _CWriteAdcRequest

#include "PcRequest.h"

class CGpr;
class CTcpServer;

class CWriteAdcRequest : public CPcRequest
{
private:
	CTcpServer *m_pTcpServer;
	CGpr *m_pGpr;

public:
	CWriteAdcRequest(CTcpServer *pTcpServer, CGpr *pGpr);
	virtual ~CWriteAdcRequest();
	virtual int   Execute(void *pRequest, void *pReply);
};

#endif 
