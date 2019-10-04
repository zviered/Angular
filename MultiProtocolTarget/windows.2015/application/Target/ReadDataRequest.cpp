
#include "stdafx.h"
#include "TcpServer.h"
#include "ReadDataRequest.h"
#include "Gpr.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CReadDataRequest::CReadDataRequest(CTcpServer *pTcpServer, CGpr *pGpr)
{
	m_pTcpServer = pTcpServer;
	m_pGpr = pGpr;
	m_RequestId = READ_DATA_REQUEST_CODE;
	m_pData = (char*)_aligned_malloc(MAX_DATA_SIZE, 32);
}

CReadDataRequest::~CReadDataRequest()
{

}

int CReadDataRequest::Execute(void *pRequest, void *pReply)
{
	PC_TO_TGT_READ_DATA_REQUEST *pRequestMsg = (PC_TO_TGT_READ_DATA_REQUEST *)pRequest;
	TGT_TO_PC_READ_DATA_REPLY *pReplyMsg = (TGT_TO_PC_READ_DATA_REPLY *)pReply;
	int DmaSize;
	char *pSrc = m_pData;
	char *pDest = pReplyMsg->Data;
	FILE *Handle;
	int rc;
	int DataSize;
	INT16 Sample;
	int DataSource;

	pReplyMsg->Header.Code = READ_DATA_REPLY_CODE;
	pReplyMsg->Header.Length = sizeof(TGT_TO_PC_READ_DATA_REPLY);
	pReplyMsg->Header.Magic = TGT_TO_PC_MAGIC;
	pReplyMsg->Header.Checksum = 0x0;

	//In case channel A or B were selected
	if (pRequestMsg->Channel <= 1)
	{
		DataSize = pRequestMsg->NofSamples * sizeof(UINT16);  //Sample = 16 bit, 2 bytes
		DataSource = GPR_DATA_SOURCE_ADC0_AI + pRequestMsg->Channel * 2 + pRequestMsg->SubChannel;
	}
	else
	{
		DataSize = pRequestMsg->NofSamples * sizeof(UINT64); //Sample = 2 bytes * 4
		DataSource = GPR_DATA_SOURCE_ADC0;
	}

	printf("ReadDataRequest: DataSource=%d NofSamples=%d Channel=%d SubChannel=%d\n",
		DataSource,
		pRequestMsg->NofSamples,
		pRequestMsg->Channel,
		pRequestMsg->SubChannel);
	
		pReplyMsg->Data[0] = 32;
	
	//m_pGpr->ReadData(m_pData, (E_GPR_DATA_SOURCE)DataSource, DataSize, 1000);

	//memcpy(pDest, pSrc, DataSize);

	/*fopen_s (&Handle, "Raw.txt","wt");
	for (int SampleId=0;SampleId<pRequestMsg->NofSamples;SampleId++)
	{
	Sample = *(UINT16*)pSrc;
	fprintf (Handle,"%d;\n",Sample);
	*(UINT16*)pDest = Sample;
	pSrc+=sizeof(UINT64);
	pDest+=sizeof(UINT16);
	}
	fclose (Handle);*/

	/*rc = fopen_s(&Handle, "Raw.bin", "wb");
	if (rc != 0)
	{
		printf("Failed to open Raw.bin\n");
		return -1;
	}

	fwrite(pReplyMsg->Data, 1, DataSize, Handle);
	fclose(Handle);*/

	m_pTcpServer->Send(pReplyMsg, pReplyMsg->Header.Length);

	return 0;
}
