#include "../Header/Mutex.h"

CMutex::CMutex()
{
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutex_init(&m_Mutex, &attr);
}

CMutex::~CMutex()
{
    pthread_mutex_destroy(&m_Mutex);
}

bool CMutex::Lock()
{
    bool bRes = false;
    int iRes = pthread_mutex_lock( &m_Mutex );
    bRes = (iRes == 0) ? true : false;

    return bRes;
}
bool CMutex::UnLock()
{
    bool bRes = false;
    int iRes = pthread_mutex_unlock( &m_Mutex );
    bRes = (iRes == 0) ? true : false;

    return bRes;
}
pthread_mutex_t* CMutex::Get()
{
    return &m_Mutex;
}


/*******************ScopeLock************************/
ScopeLock::ScopeLock( CMutex& mutex )
:m_Mutex(mutex)
{
    m_Mutex.Lock();
}

ScopeLock::~ScopeLock()
{
    m_Mutex.UnLock();
}