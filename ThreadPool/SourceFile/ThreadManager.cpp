#include "../Header/ThreadManager.h"

CThreadManager::CThreadManager( int iPoolSize )
{
    m_iPoolSize = iPoolSize;
}

CThreadManager::~CThreadManager()
{
    ClearAllThread();
}

bool CThreadManager::Start()
{
    bool bRes = true;
    ScopeLock stuGurad(m_stuMutex);
    for (int i = 0; i < m_iPoolSize; i++)
    {
        CWorkThread* pWorkTread = new CWorkThread(this);
        if ( pWorkTread != NULL )
        {
            bRes = pWorkTread->Start();
            if( bRes )
            {
                m_listThreadPool.push_back( pWorkTread );
            }
            else
            {
                break;
            }
        }
        
    }
    return bRes;
}

bool CThreadManager::Stop()
{
    bool bRes = true;
    ScopeLock gurad(m_stuMutex);
    list<CWorkThread*>::iterator it = m_listThreadPool.begin();
    for ( ; it  != m_listThreadPool.end(); ++it)
    {
        if( NULL != (*it) )
        {
            (*it)->Stop();
        }
    }

    it = m_DeadThreads.begin();
    for ( ; it  != m_DeadThreads.end(); ++it)
    {
        if( NULL != (*it) )
        {
            (*it)->Stop();
        }
    }

    return bRes;
}

bool CThreadManager::AddTask( CTask* pTask )
{
    bool bRes = false;
    ScopeLock gurad(m_stuMutex);
    for ( list<CWorkThread*>::iterator it = m_listThreadPool.begin(); it != m_listThreadPool.end(); ++it)
    {
        if( NULL != (*it) )
        {
            (*it)->AddTask( pTask );
            bRes = true;
            break;
        }
    }

    return bRes;
}
void CThreadManager::OnIdle(const pthread_t& stuTread_t)
{
    //子线程类有可能会反调会线程管理类，要加锁
    ScopeLock gurad(m_stuMutex);
    list<CWorkThread*>::iterator it = m_DeadThreads.begin();
    for ( ; it != m_DeadThreads.end(); ++it)
    {
        if( NULL != (*it) )
        {
            (*it)->Stop();
        }

    }
    m_DeadThreads.clear();

    if( (int)m_listThreadPool.size() <= m_iPoolSize )
    {
        return;
    }

    it = m_listThreadPool.begin();
    for( ; it != m_listThreadPool.end(); )
    {
        if( NULL != (*it) )
        {
            if( stuTread_t == (*it)->GetId() )
            {
                m_DeadThreads.push_back(*it);
                it = m_listThreadPool.erase(it);
            }
            else
            {
                ++it;
            }
        }
        else
        {
            ++it;
        }
    }
}

void CThreadManager::ClearAllThread()
{
    Stop();

    ScopeLock gurad(m_stuMutex);
    list<CWorkThread*>::iterator it = m_listThreadPool.begin();
    for( ; it != m_listThreadPool.end(); ++it )
    {
        delete (*it);
    }

    it = m_DeadThreads.begin();
    for ( ; it != m_DeadThreads.end(); ++it)
    {
        delete (*it);
    }
}