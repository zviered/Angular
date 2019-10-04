// Target.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "HttpServer.h"

#define PORT 80

int _tmain(int argc, _TCHAR* argv[])
{
	CHttpServer *pServer = new CHttpServer ();

	if (pServer->Init (PORT)!=0)
		return -1;

	while (true)
	{
		if (pServer->Receive ()!=0)
			return -1;

		pServer->Respond ();
	}

	return 0;
}

