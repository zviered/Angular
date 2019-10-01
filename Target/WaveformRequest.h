#pragma once

typedef unsigned int UINT32;

typedef struct HeaderRequest
{
	UINT32 Id;
	UINT32 Size;
}HeaderRequest;

typedef struct Timing
{
	UINT32 PriLength;
	UINT32 SmcPulseWidth;
}Timing;

typedef struct WaveformRequest
{
	HeaderRequest Header;
	Timing	Timing[2];
}WaveformRequest;