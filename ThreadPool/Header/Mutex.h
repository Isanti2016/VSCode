#pragma once

#include <pthread.h>

class CMutex
{
public:
    CMutex();
    ~CMutex();

    bool Lock();
    bool UnLock();
    pthread_mutex_t* Get();

 private:
    pthread_mutex_t m_Mutex;
};

/*******************ScopeLock************************/
class ScopeLock
{
public:
    ScopeLock( CMutex& mutex );
    ~ScopeLock();

private:
    CMutex& m_Mutex;
};