
#ifndef _CAdcResetRequest
#define _CAdcResetRequest

#include "PcRequest.h"

class CGpr;
class CTcpServer;

class CAdcResetRequest : public CPcRequest
{
private:
	CTcpServer *m_pTcpServer;
	CGpr *m_pGpr;

public:
	CAdcResetRequest(CTcpServer *pTcpServer, CGpr *m_pGpr);
	virtual ~CAdcResetRequest();
	virtual int   Execute(void *pRequest, void *pReply);
};

#endif 
