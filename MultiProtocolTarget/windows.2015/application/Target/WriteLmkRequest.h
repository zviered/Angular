
#ifndef _CWriteLmkRequest
#define _CWriteLmkRequest

#include "PcRequest.h"

class CGpr;
class CTcpServer;

class CWriteLmkRequest : public CPcRequest
{
private:
	CTcpServer *m_pTcpServer;
	CGpr *m_pGpr;

public:
	CWriteLmkRequest(CTcpServer *pTcpServer, CGpr *pGpr);
	virtual ~CWriteLmkRequest();
	virtual int   Execute(void *pRequest, void *pReply);
};

#endif 

