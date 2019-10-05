
#include "stdafx.h"
#include "TcpServer.h"
#include "ReadPciRequest.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CReadPciRequest::CReadPciRequest()
{
	m_RequestId = READ_PCI_REQUEST_CODE;	
}

CReadPciRequest::~CReadPciRequest()
{

}

int CReadPciRequest::Execute(void *pRequest, void *pReply)
{
	PC_TO_TGT_READ_PCI_REQUEST *pRequestMsg = (PC_TO_TGT_READ_PCI_REQUEST *)pRequest;
	TGT_TO_PC_READ_PCI_REPLY *pReplyMsg = (TGT_TO_PC_READ_PCI_REPLY *)pReply;

	pReplyMsg->Header.Code = READ_PCI_REPLY_CODE;
	pReplyMsg->Header.Length = sizeof(TGT_TO_PC_READ_PCI_REPLY);
	pReplyMsg->Header.Magic = TGT_TO_PC_MAGIC;
	pReplyMsg->Header.Checksum = 0x0;

	pReplyMsg->Data = 17;

	printf ("ReadPciRequest: Bar=%d Offset=0x%x Data=0x%x\n",
			 pRequestMsg->Bar,
			 pRequestMsg->Offset, 
			 pReplyMsg->Data);

	//m_pTcpServer->Send (pReplyMsg, pReplyMsg->Header.Length);

	return 0;
}
