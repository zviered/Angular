
#ifndef _CReadInterrupt
#define _CReadInterrupt

#include "PcRequest.h"

class CGpr;
class CTcpServer;

class CReadInterrupt : public CPcRequest
{
private:
	CTcpServer *m_pTcpServer;
	CGpr *m_pGpr;

public:
	CReadInterrupt(CTcpServer *pTcpServer);
	virtual ~CReadInterrupt();
	virtual int   Execute(void *pRequest, void *pReply);
};

#endif 
