
typedef enum E_TGT_TO_PC_CODE
{
	IS_ALIVE_REPLY_CODE			= 1,
	WRITE_PCI_REPLY_CODE		= 2,
	READ_PCI_REPLY_CODE			= 3,
	TELEMETRY_STATUS_REPLY_CODE = 4,
	WRITE_WAVEFORM_REPLY_CODE	= 5,
	WRITE_ADC_REPLY_CODE        = 6,
	READ_ADC_REPLY_CODE         = 7,
	STOP_WAVEFORM_REPLY_CODE	= 8,
	WRITE_LMK_REPLY_CODE        = 9,
	READ_LMK_REPLY_CODE         = 10,
	FIO_SETUP_REPLY_CODE        = 11,
	WRITE_NCO_REPLY_CODE        = 12,
	READ_NCO_REPLY_CODE         = 13,
	ADC_RESET_REPLY_CODE        = 14,
	ADC_POWER_REPLY_CODE        = 15,
	READ_DATA_REPLY_CODE        = 16,
	ADC_STATUS_REPLY_CODE       = 17,
	READ_INTERRUPTS_REPLY_CODE  = 18,
	INFO_STATUS_REPLY_CODE      = 19,
    LAST_REPLY_CODE				
}E_TGT_TO_PC_CODE;

/***************************************************/
typedef struct TGT_TO_PC_HEADER
{
	unsigned long		Magic;
	E_TGT_TO_PC_CODE	Code;
	unsigned long		Length;
	unsigned long		Checksum;
}TGT_TO_PC_HEADER;

/***************************************************/
typedef struct TGT_TO_PC_IS_ALIVE_REPLY
{
	TGT_TO_PC_HEADER	Header;
}TGT_TO_PC_IS_ALIVE_REPLY;

/***************************************************/
typedef struct TGT_TO_PC_WRITE_PCI_REPLY
{
	TGT_TO_PC_HEADER	Header;
}TGT_TO_PC_WRITE_PCI_REPLY;

/***************************************************/
typedef struct TGT_TO_PC_READ_PCI_REPLY
{
	TGT_TO_PC_HEADER	Header;
	unsigned int		Data;
}TGT_TO_PC_READ_PCI_REPLY;

/***************************************************/
typedef struct TGT_TO_PC_WRITE_WAVEFORM_REPLY
{
	TGT_TO_PC_HEADER	Header;
}TGT_TO_PC_WRITE_WAVEFORM_REPLY;

/***************************************************/
typedef struct TGT_TO_PC_ADC_POWER_REPLY
{
	TGT_TO_PC_HEADER	Header;
}TGT_TO_PC_ADC_POWER_REPLY;

/***************************************************/
typedef struct TGT_TO_PC_ADC_RESET_REPLY
{
	TGT_TO_PC_HEADER	Header;
}TGT_TO_PC_ADC_RESET_REPLY;
/***************************************************/
typedef struct TGT_TO_PC_READ_DATA_REPLY
{
	TGT_TO_PC_HEADER	Header;
	unsigned int Offset;
	char Data[2 * 1024 * 1024];
	
}TGT_TO_PC_READ_DATA_REPLY;

/***************************************************/

typedef struct TGT_TO_PC_ADC_STATUS_REPLY
{
	TGT_TO_PC_HEADER	Header;
	unsigned int		Power;
	unsigned int		Reset;
}TGT_TO_PC_ADC_STATUS_REPLY;

/***************************************************/
typedef struct TGT_TO_PC_WRITE_ADC_REPLY
{
	TGT_TO_PC_HEADER	Header;
}TGT_TO_PC_WRITE_ADC_REPLY;
/***************************************************/

typedef struct TGT_TO_PC_FIO_SETUP_REPLY
{
	TGT_TO_PC_HEADER	Header;
}TGT_TO_PC_FIO_SETUP_REPLY;

/***************************************************/

typedef struct TGT_TO_PC_WRITE_LMK_REPLY
{
	TGT_TO_PC_HEADER	Header;
}TGT_TO_PC_WRITE_LMK_REPLY;

/***************************************************/
typedef struct TGT_TO_PC_READ_LMK_REPLY
{
	TGT_TO_PC_HEADER	Header;
	unsigned int		Data;
}TGT_TO_PC_READ_LMK_REPLY;

/***************************************************/
typedef struct TGT_TO_PC_READ_NCO_REPLY
{
	TGT_TO_PC_HEADER	Header;
	unsigned int		NcoId;
	unsigned int		Frequency;
}TGT_TO_PC_READ_NCO_REPLY;

/***************************************************/

typedef struct TGT_TO_PC_WRITE_NCO_REPLY
{
	TGT_TO_PC_HEADER	Header;
}TGT_TO_PC_WRITE_NCO_REPLY;


/***************************************************/

typedef struct TGT_TO_PC_READ_ADC_REPLY
{
	TGT_TO_PC_HEADER	Header;
	unsigned int		Data;
}TGT_TO_PC_READ_ADC_REPLY;

/***************************************************/
typedef struct TGT_TO_PC_TELEMETRY_STATUS_REPLY
{
	TGT_TO_PC_HEADER	Header;
	int AmibentTemp;
	int FpgaTemp;
	int SbcTemp;
	unsigned int VinDigital;
	unsigned int V3_3;
	unsigned int V3_0;
	unsigned int V3_0VCCA;
	unsigned int V2_5;
	unsigned int V1_8;
	unsigned int V1_5VCCH;
	unsigned int V1_5DDR3;
	unsigned int V1_05VCCT;
	unsigned int V1_05VCCR;
	unsigned int V0_85;
	unsigned int AdcStatus[4];
}TGT_TO_PC_TELEMETRY_STATUS_REPLY;

/***************************************************/
typedef struct TGT_TO_PC_INFO_STATUS_REPLY
{
	TGT_TO_PC_HEADER	Header;
	unsigned int PartNumber;
	unsigned int FirmwarePartNumber;
	unsigned int CompilationSN;
	unsigned int Major;
	unsigned int Minor;
	unsigned int SubVersion;
	unsigned int Day;
	unsigned int Month;
	unsigned int Year;
	unsigned int BuildNumber;
	
}TGT_TO_PC_INFO_STATUS_REPLY;
/***************************************************/
typedef struct TGT_TO_PC_READ_INTERRUPT_REPLY
{
	TGT_TO_PC_HEADER	Header;
}TGT_TO_PC_READ_INTERRUPT_REPLY;

/***************************************************/
typedef union TGT_TO_PC_REPLY_U
{
	TGT_TO_PC_IS_ALIVE_REPLY				IsAliveReply;
	TGT_TO_PC_WRITE_PCI_REPLY				WritePciReply;
	TGT_TO_PC_READ_PCI_REPLY				ReadPciReply;
	TGT_TO_PC_INFO_STATUS_REPLY				InfoStatusReply;
	TGT_TO_PC_TELEMETRY_STATUS_REPLY		TelemetryStatusReply;
	TGT_TO_PC_READ_DATA_REPLY               ReadDataReplay;
}TGT_TO_PC_REPLY_U;

