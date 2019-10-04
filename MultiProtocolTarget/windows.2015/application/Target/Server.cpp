
#include "stdafx.h"
#include "Catalog.h"
#include "Server.h"
#include "IsAliveRequest.h"
#include "ReadPciRequest.h"
#include "WritePciRequest.h"
#include "TcpServer.h"

/****************************************************************************/
CServer::CServer (void)
{
	m_pPcToTgtRequest = new PC_TO_TGT_REQUEST_U;
	m_pTgtToPcReply = new TGT_TO_PC_REPLY_U;
	m_pCatalog = new CCatalog;
	m_pTcpSocket = new CTcpServer ();
	m_pHttpSocket = new CTcpServer ();
}

/****************************************************************************/
int CServer::Handle (int Code)
{
	if (m_pCatalog->GetObjectPtr (Code)==NULL)
		return 0;

	CPcRequest *pRequest = (CPcRequest *)m_pCatalog->GetObjectPtr (Code);
	pRequest->Execute (m_pPcToTgtRequest,m_pTgtToPcReply);

	return 0;
}

/****************************************************************************/
int CServer::Init (void)
{
	//TCB
	CIsAliveRequest *pIsAliveRequest = new CIsAliveRequest();
	m_pCatalog->RegisterObject (pIsAliveRequest->GetId(),pIsAliveRequest);

	CWritePciRequest *pWritePciRequest = new CWritePciRequest();
	m_pCatalog->RegisterObject (pWritePciRequest->GetId(), pWritePciRequest);

	CReadPciRequest *pReadPciRequest = new CReadPciRequest();
	m_pCatalog->RegisterObject (pReadPciRequest->GetId(), pReadPciRequest);

	return 0;
}

/****************************************************************************/
int CServer::TcpInit (void)
{
	m_pTcpSocket->Open(PC_TO_TGT_TCP_PORT);
	printf("Waiting for host connection...\n");

	m_pTcpSocket->WaitForHandShake();
	printf("Connection established\n");

	return 0;
}

/****************************************************************************/
int CServer::TcpHandler(void)
{
	PC_TO_TGT_HEADER *pHeader = (PC_TO_TGT_HEADER *)m_pPcToTgtRequest;
	int rc;

	while (1)
	{
		rc = m_pTcpSocket->Receive(m_pPcToTgtRequest, sizeof(PC_TO_TGT_REQUEST_U));
		if (rc == 0)
		{
			printf("Host disconnected.\n");
			m_pTcpSocket->WaitForHandShake();
			continue;
		}

		if (pHeader->Length != rc)
		{
			printf("Code=%d Actual Size=%d Expected=%d\n", pHeader->Code, rc, pHeader->Length);
			continue;
		}

		printf("Code=%x\n", pHeader->Code);

		if (pHeader->Code >= LAST_REQUEST_CODE)
			printf("Code=%x\n", pHeader->Code);
		else
			Handle(pHeader->Code);
	}
}

/****************************************************************************/
int CServer::HttpInit(void)
{
	m_pHttpSocket->Open(PC_TO_TGT_HTTP_PORT);
	printf("Waiting for host connection...\n");

	m_pHttpSocket->WaitForHandShake();
	printf("Connection established\n");
	return 0;
}

/****************************************************************************/
int CServer::HttpHandler(void)
{
	while (1) { Sleep(1); };
	return 0;
}


/****************************************************************************/
DWORD WINAPI CServer::TcpThread (LPVOID lpParam)
{
	CServer *pServer = (CServer *)lpParam;
	
	pServer->TcpInit ();
	pServer->TcpHandler();
	
	return 0;
}

/****************************************************************************/
DWORD WINAPI CServer::HttpThread(LPVOID lpParam)
{
	CServer *pServer = (CServer *)lpParam;

	pServer->HttpInit();
	pServer->HttpHandler();

	return 0;
}