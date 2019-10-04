
#include "windows.h"

union PC_TO_TGT_REQUEST_U;
union TGT_TO_PC_REPLY_U;

class CCatalog;
class CTcpServer;

class CServer
{
private:
	PC_TO_TGT_REQUEST_U *m_pPcToTgtRequest;
	TGT_TO_PC_REPLY_U	 *m_pTgtToPcReply;
	CCatalog *m_pCatalog;
	CTcpServer *m_pTcpSocket;
	CTcpServer *m_pHttpSocket;

	int Init (void);
	int Handle (int);
	int TcpInit(void);
	int TcpHandler(void);
	int HttpInit(void);
	int HttpHandler(void);
public:
	CServer (void);
	static DWORD WINAPI TcpThread(LPVOID lpParam);
	static DWORD WINAPI HttpThread(LPVOID lpParam);
};

