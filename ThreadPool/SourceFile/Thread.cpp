#include <iostream>
#include "../Header/Thread.h"

using namespace std;

CThread::CThread()
{
    m_stuTid = 0;
    pthread_attr_setdetachstate( &m_stuAtt, PTHREAD_CREATE_DETACHED );
}

CThread::~CThread()
{

}

bool CThread::Start()
{
    int iRes = pthread_create( &m_stuTid, &m_stuAtt, &CThread::ThreadFunc, (void*)this );
    if( iRes == 0 )
    {
        return true;
    }
    else
    {
        return false;
    }
    
}

void* CThread::ThreadFunc( void* arg )
{
    CThread* pSelf = (CThread*)arg;
    if( NULL != pSelf )
    {
        pSelf->Run();
    }

    return NULL;
}

pthread_t CThread::GetId()
{
    return m_stuTid;
}