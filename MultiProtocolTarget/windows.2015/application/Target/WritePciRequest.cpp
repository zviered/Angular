
#include "stdafx.h"
#include "TcpServer.h"
#include "WritePciRequest.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWritePciRequest::CWritePciRequest()
{
	m_RequestId = WRITE_PCI_REQUEST_CODE;	
}

CWritePciRequest::~CWritePciRequest()
{

}

int CWritePciRequest::Execute(void *pRequest, void *pReply)
{
	PC_TO_TGT_WRITE_PCI_REQUEST *pRequestMsg = (PC_TO_TGT_WRITE_PCI_REQUEST *)pRequest;
	TGT_TO_PC_WRITE_PCI_REPLY *pReplyMsg = (TGT_TO_PC_WRITE_PCI_REPLY *)pReply;

	pReplyMsg->Header.Code = WRITE_PCI_REPLY_CODE;
	pReplyMsg->Header.Length = sizeof(TGT_TO_PC_WRITE_PCI_REPLY);
	pReplyMsg->Header.Magic = TGT_TO_PC_MAGIC;
	pReplyMsg->Header.Checksum = 0x0;

	printf ("WritePciRequest: Device=%d Bar=%d Offset=0x%x Data=0x%x\n",
			 pRequestMsg->Bar,
			 pRequestMsg->Offset, 
			 pRequestMsg->Data);

	//m_pTcpServer->Send (pReplyMsg, pReplyMsg->Header.Length);

	return 0;
}
