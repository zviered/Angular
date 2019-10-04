
#ifndef _CReadLmkRequest
#define _CReadLmkRequest

#include "PcRequest.h"

class CGpr;
class CTcpServer;

class CReadLmkRequest : public CPcRequest
{
private:
	CTcpServer *m_pTcpServer;
	CGpr *m_pGpr;

public:
	CReadLmkRequest(CTcpServer *pTcpServer, CGpr *pGpr);
	virtual ~CReadLmkRequest();
	virtual int   Execute(void *pRequest, void *pReply);
};

#endif 