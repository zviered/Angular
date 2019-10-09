#pragma once

#include "windows.h"
#include "BaseProtocol.h"
#include "jsmn.h"

#define MAX_JSON_TOKENS 32
#define MAX_TOKEN_SIZE 256
#define MIN_REQUEST_SIZE 415
#define MAX_IN_MSG_SIZE (4096)
#define MAX_OUT_MSG_SIZE (1024*1024)

const char DAY[7][8] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };
const char MONTH[12][8] = { "Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec" };

class CHttpProtocol : public CBaseProtocol
{
private:
	char *m_pRequestMsg;
	char *m_pReplyMsg;
	char *m_pReplyBody;
	jsmn_parser *m_pJsonParser;
	jsmntok_t *m_pJsonToken;
	void CopyToStream(void *pDest, char *pSrc);
	int ReplyPost(void);
	int ReplyGet(void);

public:
	CHttpProtocol();
	~CHttpProtocol();
	static DWORD WINAPI Thread(LPVOID lpParam);
	int Open();
	int Init();
	int Loop();
};

