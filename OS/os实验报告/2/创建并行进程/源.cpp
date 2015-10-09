#include <windows.h>
#include <cstdio>

DWORD WINAPI ThreadProcA(LPVOID pParam){
	int i;
	//进程A输出
	for (i = 1; i <= 1000; i++){
		printf("Thread A is printing %d\n", i);
		Sleep(500);
	}
	//printf("A\n");
	return 0;
}
DWORD WINAPI ThreadProcB(LPVOID pParam){
	int i;
	//进程B输出
	for (i = 1000; i > 0; i--){
		printf("Thread B is printing %d\n", i);
		Sleep(500);
	}
	return 0;
}

int main(){
	LPDWORD lpThreadIdA, lpThreadIdB;
	HANDLE hA, hB;
	//创建并行进程
	hA = CreateThread(NULL, 0, ThreadProcA, NULL, 0, NULL);
	if (hA == NULL){
		printf("Create Failed!\n");
	}
	hB = CreateThread(NULL, 0, ThreadProcB, NULL, 0, NULL);
	if (hB == NULL){
		printf("Create Failed!\n");
	}
	system("pause");
}