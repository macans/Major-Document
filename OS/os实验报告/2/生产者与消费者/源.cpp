#include <windows.h>
#include <iostream>

using namespace std;

const int BUFFER_SIZE = 5, pCount = 5, cCount = 5;
static int pID = 0, cID = 0;
HANDLE mutex, empty, full;
int in = 0, out = 0;
int buffer[BUFFER_SIZE];

DWORD WINAPI pThreadProc(LPVOID lparam);
DWORD WINAPI cThreadProc(LPVOID lparam);

int main()
{
	HANDLE pThread[pCount];
	HANDLE cThread[cCount];
	DWORD pId[pCount];
	DWORD  cId[cCount];

	mutex = CreateMutex(NULL, FALSE, NULL);
	empty = CreateSemaphore(NULL, BUFFER_SIZE, BUFFER_SIZE, NULL);
	full = CreateSemaphore(NULL, 0, BUFFER_SIZE, NULL);

	for (int i = 0; i < pCount; ++i){
		//生产者
		pThread[i] = CreateThread(NULL, 0, pThreadProc, NULL, 0, &pId[i]);
	}

	for (int i = 0; i < cCount; ++i){
		//消费者
		cThread[i] = CreateThread(NULL, 0, cThreadProc, NULL, 0, &cId[i]);
	}

	while (1);
}

DWORD WINAPI pThreadProc(LPVOID lparam)
{
	Sleep(100);

	WaitForSingleObject(empty, INFINITE);
	WaitForSingleObject(mutex, INFINITE);

	cout << "The producer ID is:" << pID << endl;
	//将产品存入缓冲区
	buffer[in] = pID;
	in = (in + 1) % BUFFER_SIZE;
	pID++;

	ReleaseMutex(mutex);
	ReleaseSemaphore(full, 1, NULL);

	return 0;
}

DWORD WINAPI cThreadProc(LPVOID lparam)
{
	Sleep(100);

	WaitForSingleObject(full, INFINITE);
	WaitForSingleObject(mutex, INFINITE);
	//从缓冲区读出产品
	cID = buffer[out];
	out = (out + 1) % BUFFER_SIZE;
	cout << "The consumer id is:" << cID << endl;

	ReleaseMutex(mutex);
	ReleaseSemaphore(empty, 1, NULL);

	return 0;
}