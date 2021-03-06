#include <winsock2.h>
#include "jsmn.h"

#define MAX_IN_MSG_SIZE (10*1024)
#define MAX_TOKEN_SIZE 256
#define MIN_REQUEST_SIZE 415
#define MAX_JSON_TOKENS 32

const char DAY[7][8] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };
const char MONTH[12][8] = { "Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec" };

struct WaveformRequest;

#pragma once
class CHttpServer
{
private:
	WaveformRequest *m_pWaveformRequest;

	int m_Port;
	SOCKET m_Socket;
	SOCKET m_AcceptSocket;
	char *m_pInMsg;
	jsmn_parser *m_pJsonParser;
	jsmntok_t *m_pJsonToken;
	void GetToken (char *pBody, jsmntok_t *pToken);
	void CopyToStream(void *pDest, char *pSrc);

public:
	CHttpServer(void);
	~CHttpServer(void);
	int Init (int Port);
	int Receive (void);
	int Respond (void);
};

