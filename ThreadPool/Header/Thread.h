#pragma once

#include <pthread.h>
#include <iostream>

using namespace std;

class CThread
{
public:
    CThread();
    virtual ~CThread();

    bool Start();
    static void* ThreadFunc(void *);
    virtual void Run() = 0;
    pthread_t GetId();
private:
    pthread_t       m_stuTid;
    pthread_attr_t  m_stuAtt;
};
