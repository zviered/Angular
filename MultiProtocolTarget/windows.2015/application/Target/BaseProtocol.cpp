#include "stdafx.h"
#include "BaseProtocol.h"
#include "Catalog.h"
#include "IsAliveRequest.h"
#include "ReadPciRequest.h"
#include "WritePciRequest.h"
#include "TcpServer.h"

/****************************************************************************/
CBaseProtocol::CBaseProtocol()
{
	m_pPcToTgtRequest = new PC_TO_TGT_REQUEST_U;
	m_pTgtToPcReply = new TGT_TO_PC_REPLY_U;
	m_pCatalog = new CCatalog;
	m_pTcpServer = new CTcpServer();

	RegisterRequests();
}

/****************************************************************************/
CBaseProtocol::~CBaseProtocol()
{
}

/****************************************************************************/
int CBaseProtocol::RegisterRequests(void)
{
	CIsAliveRequest *pIsAliveRequest = new CIsAliveRequest();
	m_pCatalog->RegisterObject(pIsAliveRequest->GetId(), pIsAliveRequest);

	CWritePciRequest *pWritePciRequest = new CWritePciRequest();
	m_pCatalog->RegisterObject(pWritePciRequest->GetId(), pWritePciRequest);

	CReadPciRequest *pReadPciRequest = new CReadPciRequest();
	m_pCatalog->RegisterObject(pReadPciRequest->GetId(), pReadPciRequest);

	return 0;
}

/****************************************************************************/
int CBaseProtocol::Handle(int Code)
{
	if (m_pCatalog->GetObjectPtr(Code) == NULL)
		return 0;

	CPcRequest *pRequest = (CPcRequest *)m_pCatalog->GetObjectPtr(Code);
	pRequest->Execute(m_pPcToTgtRequest, m_pTgtToPcReply);

	return 0;
}