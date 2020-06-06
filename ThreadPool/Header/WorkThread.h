#pragma once

#include <Queue>
#include "Thread.h"
#include "Task.h"
#include "Cond.h"
#include "Mutex.h"

class CThreadManager;

class CWorkThread : public CThread
{
public:
    CWorkThread( CThreadManager* pThreadMgr );
    virtual ~CWorkThread();

    virtual void Run();
    void Stop();
    void AddTask( CTask* task );

private:
    bool            m_bQuit;
    queue<CTask*>   m_queTask;
    CMutex          m_stuMutex;
    CCond           m_cond;

    CThreadManager* m_pThreadMgr;
};
