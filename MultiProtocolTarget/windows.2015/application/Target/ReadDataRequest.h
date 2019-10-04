
#ifndef _CReadDataRequest
#define _CReadDataRequest

#include "PcRequest.h"

class CGpr;
class CTcpServer;

#define MAX_DATA_SIZE  (2*1024*1024)

class CReadDataRequest : public CPcRequest
{
private:
	CTcpServer *m_pTcpServer;
	CGpr *m_pGpr;
	char *m_pData;
public:
	CReadDataRequest(CTcpServer *pTcpServer, CGpr *m_pGpr);
	virtual ~CReadDataRequest();
	virtual int   Execute(void *pRequest, void *pReply);
};

#endif 
