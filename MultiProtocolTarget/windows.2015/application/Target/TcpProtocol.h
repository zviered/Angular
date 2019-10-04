#include "BaseProtocol.h"
#include "windows.h"

#pragma once
class CTcpProtocol : public CBaseProtocol
{
public:
	CTcpProtocol();
	~CTcpProtocol();
	static DWORD WINAPI Thread(LPVOID lpParam);
	int Open();
	int Init();
	int Loop();
};

