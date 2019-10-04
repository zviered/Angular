// Target.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Module.h"
#include "Server.h"
#include "stdio.h"
#include "TcpProtocol.h"
#include "HttpProtocol.h"

int _tmain(int argc, _TCHAR* argv[])
{
	printf ("GPR Remote agent\n");
	printf ("Initializing...\n");

	CModule *pModule = new CModule ();
	CBaseProtocol *pTcpProtocol = new CTcpProtocol ();
	CBaseProtocol *pHttpProtocol = new CHttpProtocol();

	pModule->Build ();
	pTcpProtocol->Init();
	pHttpProtocol->Init();

	while (1) { Sleep(1); };

	return 0;
}

