#pragma once

#include <list>
#include "WorkThread.h"
#include "Mutex.h"
#include "Task.h"

using namespace std;

class CThreadManager
{
private:
    int m_iPoolSize;
    CMutex m_stuMutex;
    list<CWorkThread*> m_listThreadPool;
    list<CWorkThread*> m_DeadThreads;

public:
    CThreadManager(int iPoolSize);
    ~CThreadManager();

    bool Start();
    bool Stop();
    bool AddTask( CTask* pTask );
    void OnIdle(const pthread_t& stuTread_t);

private:
    void ClearAllThread();
};