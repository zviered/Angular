#pragma once

#include "windows.h"
class CGpr;
struct PC_TO_TGT_WRITE_WAVEFORM_REQUEST;

class CSmcTask
{
private:
	CGpr *m_pGpr;
	int WriteDwell(void);
	int SmcHandler(void);
	unsigned int m_DwellId;        //Inside waveform. Reset upon new waveform request
	unsigned int m_DwellSequence;  //Counts how many times the same dwell was written
	PC_TO_TGT_WRITE_WAVEFORM_REQUEST *m_pWaveformRequest;

public:
	CSmcTask(CGpr *pGpr);
	~CSmcTask();
	static DWORD WINAPI EntryPoint(void *pParam);
	int StopWaveform(void);
	int WriteWaveform(PC_TO_TGT_WRITE_WAVEFORM_REQUEST *pWaveformRequest);
};

