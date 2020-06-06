#include "../Header/Cond.h"

CCond::CCond(/* args */)
{
    pthread_cond_init( &m_cond, NULL );
}

CCond::~CCond()
{
    pthread_cond_destroy( &m_cond );
}
 
bool CCond::Wait( pthread_mutex_t* mutex)
{
    //a.释放锁,b等待条件改变
    return 0 == pthread_cond_wait( &m_cond, mutex );
}
bool CCond::Notify()
{
    return 0 == pthread_cond_signal( &m_cond );
}
bool CCond::NotifyAll()
{
    return 0 == pthread_cond_broadcast( &m_cond );
}