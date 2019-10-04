// Catalog.cpp: implementation of the CCatalog class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Catalog.h"
#include "stdio.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

int CCatalog::RegisterObject (int Id,void *p)
{
	if (Id>N_OBJECTS-1)
	{
		printf ("Invalid Object Id (%d)\n",Id);
		return -1;
	}
	m_pObject[Id]=p;

	return 0;
}

void *CCatalog::GetObjectPtr (int Id)
{
	return m_pObject[Id];
}

CCatalog::CCatalog ()
{
	for (int i=0;i<N_OBJECTS;i++)
		m_pObject[i]=NULL;	
}
