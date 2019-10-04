
#ifndef _CIsAliveRequest
#define _CIsAliveRequest

#include "PcRequest.h"

//class CTcpServer;

class CIsAliveRequest : public CPcRequest  
{
private:

public:
	CIsAliveRequest();
	virtual ~CIsAliveRequest();
	virtual int   Execute(void *pRequest, void *pReply);
};

#endif 
