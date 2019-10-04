#include "stdafx.h"
#include "TcpProtocol.h"
#include "TcpServer.h"
#include "windows.h"
#include "PcToTgtIcd.h"

/****************************************************************************/
CTcpProtocol::CTcpProtocol()
{
}


/****************************************************************************/
CTcpProtocol::~CTcpProtocol()
{
}

/****************************************************************************/
int CTcpProtocol::Open()
{
	m_pTcpServer->Open(PC_TO_TGT_TCP_PORT);
	printf("Waiting for host connection...\n");

	m_pTcpServer->WaitForHandShake();
	printf("Connection established\n");

	return 0;
}

/****************************************************************************/
int CTcpProtocol::Init()
{
	CreateThread(NULL,			// default security attributes
			0,                      // use default stack size  
			Thread,     // thread function name
			this,					// argument to thread function 
			0,                      // use default creation flags 
			NULL);

	return 0;
}

/****************************************************************************/
int CTcpProtocol::Loop()
{
	PC_TO_TGT_HEADER *pHeader = (PC_TO_TGT_HEADER *)m_pPcToTgtRequest;
	int rc;

	while (1)
	{
		rc = m_pTcpServer->Receive(m_pPcToTgtRequest, sizeof(PC_TO_TGT_REQUEST_U));
		if (rc == 0)
		{
			printf("Host disconnected.\n");
			m_pTcpServer->WaitForHandShake();
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
DWORD CTcpProtocol::Thread(LPVOID lpParam)
{
	CTcpProtocol *pTcpProtocol = (CTcpProtocol *)lpParam;

	pTcpProtocol->Open();
	pTcpProtocol->Loop();

	return 0;
}