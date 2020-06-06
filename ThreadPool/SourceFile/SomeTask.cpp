#include "../Header/SomeTask.h"
#include <unistd.h>
#include <iostream>

using namespace std;

CTaskA::CTaskA()
{

}

CTaskA::~CTaskA()
{

}

void CTaskA::Execute()
{
    cout << "CTaskA" << endl;
    sleep(0.5);
}


CTaskB::CTaskB()
{

}

CTaskB::~CTaskB()
{

}

void CTaskB::Execute()
{
    cout << "CTaskB" << endl;
    sleep(1);
}


