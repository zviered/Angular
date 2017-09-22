#include <winsock2.h>

#define MAX_IN_MSG_SIZE (1024*10)
#define MAX_TOKEN_SIZE 256
const char DAY[7][8] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };
const char MONTH[12][8] = { "Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec" };


#pragma once
class CHttpServer
{
private:
	int m_Port;
	SOCKET m_Socket;
	SOCKET m_AcceptSocket;
	char *m_pInMsg;
	char *m_pToken;
public:
	CHttpServer(void);
	~CHttpServer(void);
	int Init (int Port);
	int Receive (void);
	int Respond (void);
};

