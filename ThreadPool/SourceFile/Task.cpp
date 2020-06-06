#include "../Header/Task.h"

CTask::CTask()
{

}

CTask::~CTask()
{

}

void CTask::Run()
{
    Execute();
    delete this;
}