#pragma once

class CTcpServer;
union PC_TO_TGT_REQUEST_U;
union TGT_TO_PC_REPLY_U;
class CCatalog;

class CBaseProtocol
{
private:
	CCatalog			*m_pCatalog;

public:
	CBaseProtocol();
	~CBaseProtocol();
	int Handle(int Code);
	virtual int Init(void) = 0;
	int RegisterRequests();

protected:
	CTcpServer *m_pTcpServer;
	PC_TO_TGT_REQUEST_U *m_pPcToTgtRequest;
	TGT_TO_PC_REPLY_U	*m_pTgtToPcReply;
};

