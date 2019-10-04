
#include "stdafx.h"
#include "ReadInterrupt.h"
#include "TcpServer.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CReadInterrupt::CReadInterrupt(CTcpServer *pTcpServer)
{
	m_pTcpServer = pTcpServer;
	m_RequestId = READ_INTERRUPTS_REQUEST_CODE;
}

CReadInterrupt::~CReadInterrupt()
{

}

int CReadInterrupt::Execute(void *pRequest, void *pReply)
{
	PC_TO_TGT_READ_INTERRUPT_REQUEST *pRequestMsg = (PC_TO_TGT_READ_INTERRUPT_REQUEST *)pRequest;
	TGT_TO_PC_READ_INTERRUPT_REPLY *pReplyMsg = (TGT_TO_PC_READ_INTERRUPT_REPLY *)pReply;

	pReplyMsg->Header.Length = sizeof(TGT_TO_PC_READ_INTERRUPT_REPLY);
	

	printf("CReadInterrupt::Execute\n");

	m_pTcpServer->Send(pReplyMsg, pReplyMsg->Header.Length);

	return 0;
}
