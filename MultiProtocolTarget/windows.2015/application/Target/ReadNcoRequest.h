
#ifndef _CReadNcoRequest
#define _CReadNcoRequest

#include "PcRequest.h"

class CGpr;
class CTcpServer;

class CReadNcoRequest : public CPcRequest
{
private:
	CTcpServer *m_pTcpServer;
	CGpr *m_pGpr;

public:
	CReadNcoRequest(CTcpServer *pTcpServer, CGpr *pGpr);
	virtual ~CReadNcoRequest();
	virtual int   Execute(void *pRequest, void *pReply);
};

#endif 
