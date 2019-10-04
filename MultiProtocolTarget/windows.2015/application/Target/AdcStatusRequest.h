
#ifndef _CAdcStatusRequest
#define _CAdcStatusRequest

#include "PcRequest.h"

class CGpr;
class CTcpServer;

class CAdcStatusRequest : public CPcRequest
{
private:
	CTcpServer *m_pTcpServer;
	CGpr *m_pGpr;

public:
	CAdcStatusRequest(CTcpServer *pTcpServer, CGpr *m_pGpr);
	virtual ~CAdcStatusRequest();
	virtual int   Execute(void *pRequest, void *pReply);
};

#endif 
