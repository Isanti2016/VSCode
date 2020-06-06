#include "../Header/WorkThread.h"
#include "../Header/ThreadManager.h"

#include <iostream>

using namespace std;

CWorkThread::CWorkThread( CThreadManager* pThreadMgr )
:m_bQuit(false)
,m_pThreadMgr(pThreadMgr)
{
}
CWorkThread::~CWorkThread()
{

}

void CWorkThread::Run()
{
    while (true)
    {
        CTask* pTask = NULL;
        {
            ScopeLock gurad(m_stuMutex); //尽量缩小临界区范围
            if( m_queTask.empty() ){
                if( m_bQuit ){
                    break;  //暂停线程
                }
                else{
                    m_cond.Wait( m_stuMutex.Get() );  //没有任务时，会释放锁
                    continue;
                }
            }
            pTask = m_queTask.front();
            m_queTask.pop();
        }

        //具体工作区，非临界区域
        try
        {
            pTask->Run();
        }
        catch( std::exception& Error )
        {
            cout << "Exception: " << Error.what() << endl;
        }

        {
            ScopeLock gurad(m_stuMutex);
            m_pThreadMgr->OnIdle( GetId() ); //一个进程一旦干完活，就先结束吧
        }
    }
    
}
void CWorkThread::Stop()
{
    ScopeLock guard(m_stuMutex);
    m_bQuit = true;

    m_cond.Notify();
}

void CWorkThread::AddTask( CTask* task )
{
    ScopeLock guard(m_stuMutex);
    m_queTask.push( task );

    if( m_queTask.size() > 0 )
    {
        m_cond.Notify();
    }

}