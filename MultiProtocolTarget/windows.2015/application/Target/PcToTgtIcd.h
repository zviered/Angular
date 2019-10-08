#define PC_TO_TGT_HTTP_PORT				8000
#define PC_TO_TGT_TCP_PORT				5100

#ifndef _UINT32
typedef unsigned int UINT32;
#endif

#define N_DWELL				16

typedef enum E_PC_TO_TGT_CODE
{
	IS_ALIVE_REQUEST_CODE			= 1,
	WRITE_PCI_REQUEST_CODE			= 2,
	READ_PCI_REQUEST_CODE			= 3,
	TELEMETRY_STATUS_REQUEST_CODE   = 4,
	WRITE_WAVEFORM_REQUEST_CODE		= 5,
	WRITE_ADC_REQUEST_CODE          = 6,
	READ_ADC_REQUEST_CODE           = 7,
	STOP_WAVEFORM_REQUEST_CODE		= 8,
	WRITE_LMK_REQUEST_CODE          = 9,
	READ_LMK_REQUEST_CODE           = 10,
	FIO_SETUP_REQUEST_CODE          = 11,
	WRITE_NCO_REQUEST_CODE          = 12,
	READ_NCO_REQUEST_CODE           = 13,
	ADC_RESET_REQUEST_CODE			= 14,
	ADC_POWER_REQUEST_CODE			= 15,
	READ_DATA_REQUEST_CODE			= 16,
	ADC_STATUS_REQUEST_CODE			= 17,
	READ_INTERRUPTS_REQUEST_CODE    = 18,
	INFO_STATUS_REQUEST_CODE        = 19,
    LAST_REQUEST_CODE				
}E_PC_TO_TGT_CODE;

#define TGT_TO_PC_MAGIC  0xCAFE2DAD

/***************************************************/
typedef struct PC_TO_TGT_HEADER
{
	UINT32				Magic;
	E_PC_TO_TGT_CODE	Code;
	UINT32				Length;
	UINT32				Checksum;
}PC_TO_TGT_HEADER;

/***************************************************/
typedef struct PC_TO_TGT_IS_ALIVE_REQUEST
{
	PC_TO_TGT_HEADER	Header;
}PC_TO_TGT_IS_ALIVE_REQUEST;

/***************************************************/
typedef struct PC_TO_TGT_WRITE_PCI_REQUEST
{
	PC_TO_TGT_HEADER	Header;
	UINT32				Bar;
	UINT32				Offset;
	UINT32 				Data;
}PC_TO_TGT_WRITE_PCI_REQUEST;

/***************************************************/
typedef struct PC_TO_TGT_READ_PCI_REQUEST
{
	PC_TO_TGT_HEADER	Header;
	UINT32				Bar;
	UINT32				Offset;
}PC_TO_TGT_READ_PCI_REQUEST;

/***************************************************/
typedef struct TIMING
{
	UINT32	FirstPulseDelay;
	UINT32	LastPulseDelay;
	UINT32	PriLength;
	UINT32  NofPRIsInSmc;
	UINT32	A2dSamplingWindowStart;
	UINT32	A2dSamplingWindowLength;
}TIMING;

/***************************************************/
typedef struct DWELL
{
	UINT32					NofTimes;
	TIMING					Timing;
}DWELL;

/***************************************************/
typedef struct PC_TO_TGT_WRITE_WAVEFORM_REQUEST
{
	PC_TO_TGT_HEADER	Header;
	UINT32				NofDwells;
	UINT32				Mode;
	DWELL  				Dwell[N_DWELL];
}PC_TO_TGT_WRITE_WAVEFORM_REQUEST;

/***************************************************/
typedef struct PC_TO_TGT_STOP_WAVEFORM_REQUEST
{
	PC_TO_TGT_HEADER	Header;
}PC_TO_TGT_STOP_WAVEFORM_REQUEST;

/***************************************************/
typedef struct PC_TO_TGT_ADC_POWER_REQUEST
{
	PC_TO_TGT_HEADER	Header;
	unsigned int		Device;
	unsigned int		Control;
}PC_TO_TGT_ADC_POWER_REQUEST;

/***************************************************/



typedef struct PC_TO_TGT_ADC_RESET_REQUEST
{
	PC_TO_TGT_HEADER	Header;
	unsigned int		Device;
	unsigned int		Control;
}PC_TO_TGT_ADC_RESET_REQUEST;


/***************************************************/
typedef struct PC_TO_TGT_ADC_STATUS_REQUEST
{
	PC_TO_TGT_HEADER	Header;
	unsigned int		Device;
}PC_TO_TGT_ADC_STATUS_REQUEST;

/***************************************************/

typedef struct PC_TO_TGT_WRITE_ADC_REQUEST
{
	PC_TO_TGT_HEADER	Header;
	unsigned int		Device;
	unsigned int		Page;
	unsigned int		Channel;
	unsigned int		Address;
	unsigned int		Data;
}PC_TO_TGT_WRITE_ADC_REQUEST;

/***************************************************/
typedef struct PC_TO_TGT_WRITE_LMK_REQUEST
{
	PC_TO_TGT_HEADER	Header;
	unsigned int		Offset;
	unsigned int		Data;
}PC_TO_TGT_WRITE_LMK_REQUEST;

/***************************************************/
typedef struct PC_TO_TGT_READ_LMK_REQUEST
{
	PC_TO_TGT_HEADER	Header;
	unsigned int		Offset;
}PC_TO_TGT_READ_LMK_REQUEST;


/***************************************************/
typedef struct FIO_CHANELL_SETUP
{
	unsigned int		Control;
	unsigned int		DataSource;
	unsigned int		AdcDevice;
	unsigned int		AdcChannel;
	unsigned int		AdcSubChannel;
}FIO_CHANELL_SETUP;
/***************************************************/
typedef struct PC_TO_TGT_FIO_SETUP_REQUEST
{
	PC_TO_TGT_HEADER	Header;
	FIO_CHANELL_SETUP	Channel[8];
	unsigned int		HeaderSize;
	unsigned int		DataSize;
	unsigned int		TrailerSize;
	unsigned int		GapSize;
}PC_TO_TGT_FIO_SETUP_REQUEST;
/***************************************************/
typedef struct PC_TO_TGT_READ_NCO_REQUEST
{
	PC_TO_TGT_HEADER	Header;
	unsigned int		Device;
	unsigned int		Channel;
	unsigned int		NcoId;
}PC_TO_TGT_READ_NCO_REQUEST;

/***************************************************/
typedef struct PC_TO_TGT_READ_ADC_REQUEST
{
	PC_TO_TGT_HEADER	Header;
	unsigned int		Device;
	unsigned int		Page;
	unsigned int		Channel;
	unsigned int		Address;
}PC_TO_TGT_READ_ADC_REQUEST;

/***************************************************/
typedef struct PC_TO_TGT_TELEMETRY_STATUS_REQUEST
{
	PC_TO_TGT_HEADER	Header;
}PC_TO_TGT_TELEMETRY_STATUS_REQUEST;

/***************************************************/
typedef struct PC_TO_TGT_INFO_STATUS_REQUEST
{
	PC_TO_TGT_HEADER	Header;
}PC_TO_TGT_INFO_STATUS_REQUEST;

/***************************************************/
typedef struct PC_TO_TGT_READ_DATA_REQUEST
{
	PC_TO_TGT_HEADER	Header;
	unsigned int		Device;
	unsigned int		Channel;
	unsigned int		SubChannel;
	unsigned int		NofSamples;
}PC_TO_TGT_READ_DATA_REQUEST;
/***************************************************/
typedef struct PC_TO_TGT_WRITE_NCO_REQUEST
{
	PC_TO_TGT_HEADER	Header;
	unsigned int		Device;
	unsigned int		Channel;
	unsigned int		NcoId;
	unsigned int		Frequency;
}PC_TO_TGT_WRITE_NCO_REQUEST;

/***************************************************/

typedef struct PC_TO_TGT_READ_INTERRUPT_REQUEST
{
	PC_TO_TGT_HEADER	Header;
}PC_TO_TGT_READ_INTERRUPT_REQUEST;

/***************************************************/
typedef union PC_TO_TGT_REQUEST_U
{
	PC_TO_TGT_IS_ALIVE_REQUEST				IsAliveRequest;
	PC_TO_TGT_WRITE_PCI_REQUEST				WritePciRequest;
	PC_TO_TGT_READ_PCI_REQUEST				ReadPciRequest;
	PC_TO_TGT_WRITE_WAVEFORM_REQUEST		WriteWaveformRequest;
	PC_TO_TGT_INFO_STATUS_REQUEST			InfoStatusRequest;
	PC_TO_TGT_TELEMETRY_STATUS_REQUEST		TelemetryStatusRequest;
	PC_TO_TGT_READ_DATA_REQUEST             ReadDataRequest;
}PC_TO_TGT_REQUEST_U;

