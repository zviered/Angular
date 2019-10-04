
#ifndef _CWritePciRequest
#define _CWritePciRequest

#include "PcRequest.h"

class CWritePciRequest : public CPcRequest  
{
private:

public:
	CWritePciRequest();
	virtual ~CWritePciRequest();
	virtual int   Execute(void *pRequest, void *pReply);
};

#endif 
