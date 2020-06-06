#pragma once

#include<pthread.h>

class CCond
{
private:
    pthread_cond_t m_cond;
public:
    CCond(/* args */);
    ~CCond();
    bool Wait( pthread_mutex_t* mutex);
    bool Notify();
    bool NotifyAll();

};
