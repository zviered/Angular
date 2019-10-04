#ifndef _PcRequest
#define _PcRequest 

#include "PcToTgtIcd.h"
#include "TgtToPcIcd.h"

class CTcpServer;

class CPcRequest  
{
public:
	CPcRequest();
	virtual ~CPcRequest(){};
	virtual int   Execute(void *pRequest, void *pReply)=0;
	inline int GetId();
protected:
	int		m_RequestId;
	CTcpServer *m_pTcpServer;
};

int CPcRequest::GetId() { return m_RequestId; }

#endif 

