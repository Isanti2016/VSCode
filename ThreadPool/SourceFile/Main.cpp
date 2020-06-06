#include <iostream>
#include "../Header/ThreadManager.h"
#include "../Header/SomeTask.h"
#include <unistd.h>

using namespace std;

int main()
{
    int iRes = 0;
    CThreadManager* pThreadManager = new CThreadManager(10);

    if ( NULL != pThreadManager )
    {
        bool bStart = pThreadManager->Start();
        if( bStart )
        {
            for (int i = 0; i < 20; i++)
            {
                bool bRes = false;
                if ( i%2 == 0 )
                {
                    bRes = pThreadManager->AddTask( new CTaskA() );
                }
                else
                {
                    bRes = pThreadManager->AddTask( new CTaskB() );
                }

                // if (bRes)
                // {
                //     cout << "AddTask : " << i << "Seccess! " << endl;
                // }
                // else
                // {
                //     cout << "AddTask : " << i << "Fail! " << endl;
                // }
            }
        }
        else
        {
            cout << "Start Thread Fail !" << endl;
        }
        
    }

    pThreadManager->Stop();
    
    //不要太早结束，不然子线程也会挂了
    cin.get();

    return iRes;
}