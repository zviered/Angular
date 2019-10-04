
#ifndef _CReadPciRequest
#define _CReadPciRequest

#include "PcRequest.h"

//class CTcpServer;

class CReadPciRequest : public CPcRequest  
{
private:

public:
	CReadPciRequest();
	virtual ~CReadPciRequest();
	virtual int   Execute(void *pRequest, void *pReply);
};

#endif 
