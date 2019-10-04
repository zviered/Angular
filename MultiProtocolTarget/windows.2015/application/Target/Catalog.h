
#define N_OBJECTS 32

class CCatalog  
{
private:
	void *m_pObject[N_OBJECTS];
public:
	int RegisterObject (int Id,void *p);
	void *GetObjectPtr (int Id);
	CCatalog ();
};
