
#include "stdafx.h"
#include "TcpServer.h"
#include "TelemetryStatusRequest.h"
#include "I2c.h"
#include "Gpr.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/***************************************************************************************/
CTelemetryStatusRequest::CTelemetryStatusRequest(CTcpServer *pTcpServer, CI2c *pI2c, CGpr *pGpr)
{
	m_pTcpServer = pTcpServer;
	m_pI2c = pI2c;
	m_pGpr = pGpr;
	m_RequestId = TELEMETRY_STATUS_REQUEST_CODE;
}

/***************************************************************************************/
CTelemetryStatusRequest::~CTelemetryStatusRequest()
{

}

/***************************************************************************************/
int CTelemetryStatusRequest::Execute(void *pRequest, void *pReply)
{
	PC_TO_TGT_TELEMETRY_STATUS_REQUEST *pRequestMsg = (PC_TO_TGT_TELEMETRY_STATUS_REQUEST *)pRequest;
	TGT_TO_PC_TELEMETRY_STATUS_REPLY *pReplyMsg = (TGT_TO_PC_TELEMETRY_STATUS_REPLY *)pReply;
	int rc;

	pReplyMsg->Header.Code = TELEMETRY_STATUS_REPLY_CODE;
	pReplyMsg->Header.Length = sizeof(TGT_TO_PC_TELEMETRY_STATUS_REPLY);
	pReplyMsg->Header.Magic = TGT_TO_PC_MAGIC;
	pReplyMsg->Header.Checksum = 0x0;

//#ifdef I2C
	printf ("TelemetryStatusRequest\n");
	


	//printf("num =%d \n", (INT32 *)&pReplyMsg->V2_5);

	//pReplyMsg->VinDigital = 20;
	

	 m_pI2c->ReadVoltage(I2C_VIN_DIGITAL, (INT32 *)&pReplyMsg->VinDigital);
	 printf("num =%d \n", pReplyMsg->VinDigital);
	 m_pI2c->ReadVoltage(I2C_3_3V, (INT32 *)&pReplyMsg->V3_3);
	 printf("num =%d \n", pReplyMsg->V3_3);
	 m_pI2c->ReadVoltage(I2C_3_0V, (INT32 *)&pReplyMsg->V3_0);	
	 printf("num =%d \n", pReplyMsg->V3_0);
	 m_pI2c->ReadVoltage(I2C_3_0VCCA, (INT32 *)&pReplyMsg->V3_0VCCA);
	 printf("num =%d \n", pReplyMsg->V3_0VCCA);
	 m_pI2c->ReadVoltage(I2C_2_5V, (INT32 *)&pReplyMsg->V2_5);
	 printf("num =%d \n", pReplyMsg->V2_5);
	 m_pI2c->ReadVoltage(I2C_1_8V, (INT32 *)&pReplyMsg->V1_8);
	 printf("num =%d \n", pReplyMsg->V1_8);
	 m_pI2c->ReadVoltage(I2C_1_5V_VCCH, (INT32 *)&pReplyMsg->V1_5VCCH);
	 printf("num =%d \n", pReplyMsg->V1_5VCCH);
	 m_pI2c->ReadVoltage(I2C_1_5V_DDR3, (INT32 *)&pReplyMsg->V1_5DDR3);	
	 printf("num =%d \n", pReplyMsg->V1_5DDR3);
	 m_pI2c->ReadVoltage(I2C_1_05V_VCCT, (INT32 *)&pReplyMsg->V1_05VCCT);
	 printf("num =%d \n", pReplyMsg->V1_05VCCT);
	 m_pI2c->ReadVoltage(I2C_1_05V_VCCR, (INT32 *)&pReplyMsg->V1_05VCCR);
	 printf("num =%d \n", pReplyMsg->V1_05VCCR);
	 m_pI2c->ReadVoltage(I2C_0_85V, (INT32 *)&pReplyMsg->V0_85);
	 printf("num =%d \n", pReplyMsg->V0_85);

//#endif
	rc = m_pI2c->ReadTemeprature(&pReplyMsg->AmibentTemp, &pReplyMsg->FpgaTemp, &pReplyMsg->SbcTemp);
	if (rc != 0)
		printf("ReadTemeprature failed\n");
	printf("Amibent =%d \n", pReplyMsg->AmibentTemp);
	printf("Fpga =%d \n", pReplyMsg->FpgaTemp);
	printf("Sbc =%d \n", pReplyMsg->SbcTemp);
	m_pGpr->ReadAdcStatus((E_GPR_ADC_STATUS *)pReplyMsg->AdcStatus);

	m_pTcpServer->Send(pReplyMsg, pReplyMsg->Header.Length);

	return 0;
}
