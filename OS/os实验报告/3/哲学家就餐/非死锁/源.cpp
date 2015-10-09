#include <windows.h>
#include <process.h>
#include <time.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <iostream>
using namespace std;                     

const unsigned int NUM = 5;    
const char THINKING = 1;                  
const char HUNGERY = 2;
const char EAT = 3;

HANDLE hPhilosopher[5];                  

//筷子的状态，是否可用
HANDLE semaphore[NUM];       
//防止死锁
HANDLE mutex;                            

DWORD WINAPI philosopherProc(LPVOID lpParameter){
	int  myid;
	char idStr[128];
	char stateStr[128];
	char mystate;
	int  ret;

	unsigned int leftFork;                  //左筷子
	unsigned int rightFork;                 //右筷子

	myid = int(lpParameter);
	itoa(myid, idStr, 10);


	WaitForSingleObject(mutex, INFINITE);
	cout << "哲学家 " << myid << " 坐上了餐桌" << endl;
	ReleaseMutex(mutex);

	//初始化
	mystate = THINKING;                                    
	leftFork = (myid) % NUM;
	rightFork = (myid + 1) % NUM;

	while (true)
	{
		switch (mystate)
		{
			//每个哲学家考虑自己的状态 
		case THINKING:
			mystate = HUNGERY;                                      
			strcpy(stateStr, "饥饿");
			break;

		case HUNGERY:
			strcpy(stateStr, "饥饿");
			//左筷子是否可用
			ret = WaitForSingleObject(semaphore[leftFork], 0);   
			if (ret == WAIT_OBJECT_0)
			{
				//右筷子是否可用
				ret = WaitForSingleObject(semaphore[rightFork], 0);  
				if (ret == WAIT_OBJECT_0)
				{
					//开吃
					mystate = EAT;                                   
					strcpy(stateStr, "吃饭");
				}
				else
				{

					ReleaseSemaphore(semaphore[leftFork], 1, NULL);    
				}
			}
			break;

		case EAT:
			//放下筷子
			ReleaseSemaphore(semaphore[leftFork], 1, NULL);
			ReleaseSemaphore(semaphore[rightFork], 1, NULL);

			mystate = THINKING;          
			//更新自己的状态
			strcpy(stateStr, "思考");
			break;
		}

		// 输出状态
		WaitForSingleObject(mutex, INFINITE);
		cout << "哲学家 " << myid << " 正在" << stateStr << endl;
		//释放互斥锁
		ReleaseMutex(mutex);
		// sleep a random time : between 1 - 5 s
		int sleepTime;
		sleepTime = 1 + (int)(5.0*rand() / (RAND_MAX + 1.0));
		Sleep(sleepTime * 10);
	}
}


int main()
{
	int i;
	freopen("out.txt", "w", stdout);
	srand(time(0));
	mutex = CreateMutex(NULL, false, NULL);
	for (i = 0; i < NUM; i++)
	{
		//首先创建数个线程
		semaphore[i] = CreateSemaphore(NULL, 1, 1, NULL);
		hPhilosopher[i] = CreateThread(NULL, 0, philosopherProc, LPVOID(i), CREATE_SUSPENDED, 0);
	}
	for (i = 0; i < NUM; i++)
		ResumeThread(hPhilosopher[i]);
	Sleep(2000);
	return 0;
}
