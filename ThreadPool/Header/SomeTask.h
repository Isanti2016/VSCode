#pragma once

#include "Task.h"

using namespace std;

class CTaskA : public CTask
{
private:
    /* data */
public:
    CTaskA();
    ~CTaskA();

    virtual void Execute();
};

class CTaskB : public CTask
{
private:
    /* data */
public:
    CTaskB();
    ~CTaskB();

    virtual void Execute();
};

