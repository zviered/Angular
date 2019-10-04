
#include "stdafx.h"
#include "TcpServer.h"
#include "InfoStatusRequest.h"
//#include "I2c.h"
#include "Gpr.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/***************************************************************************************/
CInfoStatusRequest::CInfoStatusRequest(CTcpServer *pTcpServer,  CGpr *pGpr)
{
	m_pTcpServer = pTcpServer;
//	m_pI2c = pI2c;
	m_pGpr = pGpr;
	m_RequestId = INFO_STATUS_REQUEST_CODE;
	
}

/***************************************************************************************/
CInfoStatusRequest::~CInfoStatusRequest()
{

}

/***************************************************************************************/
int CInfoStatusRequest::Execute(void *pRequest, void *pReply)
{
	PC_TO_TGT_INFO_STATUS_REQUEST *pRequestMsg = (PC_TO_TGT_INFO_STATUS_REQUEST *)pRequest;
	TGT_TO_PC_INFO_STATUS_REPLY *pReplyMsg = (TGT_TO_PC_INFO_STATUS_REPLY *)pReply;

	pReplyMsg->Header.Code = INFO_STATUS_REPLY_CODE;
	pReplyMsg->Header.Length = sizeof(TGT_TO_PC_INFO_STATUS_REPLY);
	pReplyMsg->Header.Magic = TGT_TO_PC_MAGIC;
	pReplyMsg->Header.Checksum = 0x0;

	printf("PartNumber =%d \n",&pReplyMsg->PartNumber);
	printf("Day =%d \n", &pReplyMsg->Day);
	
	m_pGpr->ReadPartNumber(&pReplyMsg->PartNumber);
	m_pGpr->ReadFirmwarePartNumber(&pReplyMsg->FirmwarePartNumber);
	m_pGpr->ReadFirmwareVersion(&pReplyMsg->CompilationSN, &pReplyMsg->Major, &pReplyMsg->Minor, &pReplyMsg->SubVersion);
	m_pGpr->ReadFirmwareDate(&pReplyMsg->Day, &pReplyMsg->Month, &pReplyMsg->Year);
	m_pGpr->ReadBuildNumber(&pReplyMsg->BuildNumber);
	
	
	

	m_pTcpServer->Send(pReplyMsg, pReplyMsg->Header.Length);

	return 0;
}
