
#ifndef _CInfoStatusRequest
#define _CInfoStatusRequest

#include "PcRequest.h"


class CTcpServer;
class CGpr;

class CInfoStatusRequest : public CPcRequest
{
private:
	CTcpServer *m_pTcpServer;
	CGpr *m_pGpr;

public:
	CInfoStatusRequest(CTcpServer *pTcpServer,  CGpr *pGpr);
	virtual ~CInfoStatusRequest();
	virtual int   Execute(void *pRequest, void *pReply);
};

#endif 