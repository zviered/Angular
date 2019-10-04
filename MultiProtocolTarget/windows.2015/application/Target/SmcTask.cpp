#include "stdafx.h"
#include "windows.h"
#include "SmcTask.h"
#include "Gpr.h"
#include "PcToTgtIcd.h"

/*************************************************************************/
CSmcTask::CSmcTask(CGpr *pGpr)
{
	m_pGpr = pGpr;
}

/******************************************************************/
int CSmcTask::SmcHandler(void)
{
	return 0;
}

/******************************************************************/
int CSmcTask::WriteDwell(void)
{
	DWELL *pDwell = &m_pWaveformRequest->Dwell[m_DwellId];

	m_pGpr->WriteFirstPulseDelay(pDwell->Timing.FirstPulseDelay);
	m_pGpr->WriteLastPulseDelay(pDwell->Timing.LastPulseDelay);
	m_pGpr->WritePriLength(pDwell->Timing.PriLength);
	m_pGpr->WriteNofPRIsInSmc (pDwell->Timing.NofPRIsInSmc);
	m_pGpr->WriteA2dSamplingWindow(pDwell->Timing.A2dSamplingWindowStart,
									pDwell->Timing.A2dSamplingWindowLength);

	return 0;
}

/******************************************************************/
int CSmcTask::WriteWaveform(PC_TO_TGT_WRITE_WAVEFORM_REQUEST *pWaveformRequest)
{
	DWELL *pDwell;

	printf("Writing new waveform...\n");
	m_DwellId = 0;
	m_DwellSequence = 0;
	memcpy(m_pWaveformRequest, pWaveformRequest, sizeof(PC_TO_TGT_WRITE_WAVEFORM_REQUEST));

	WriteDwell();

	m_pGpr->WriteArtificialSmc();

	pDwell = &m_pWaveformRequest->Dwell[m_DwellId];

	return 0;
}

/******************************************************************/
int CSmcTask::StopWaveform(void)
{
	return 0;
}

/*************************************************************************/
CSmcTask::~CSmcTask()
{
}

/*************************************************************************/
DWORD WINAPI CSmcTask::EntryPoint (void *pParam)
{
	CSmcTask *pSmcTask = (CSmcTask *)pParam;

	while (1)
	{
		pSmcTask->SmcHandler();
	}

}
