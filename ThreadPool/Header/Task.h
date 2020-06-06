#pragma once

class CTask
{
public:
    CTask();
    virtual ~CTask();

    virtual void Execute() = 0;
    void Run();
};