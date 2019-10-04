
#ifndef _CWriteNcoRequest
#define _CWriteNcoRequest

#include "PcRequest.h"

class CGpr;
class CTcpServer;

class CWriteNcoRequest : public CPcRequest
{
private:
	CTcpServer *m_pTcpServer;
	CGpr *m_pGpr;

public:
	CWriteNcoRequest(CTcpServer *pTcpServer, CGpr *pGpr);
	virtual ~CWriteNcoRequest();
	virtual int   Execute(void *pRequest, void *pReply);
};

#endif 
