#include <cstdio>
#include <iostream>
#include <pthread.h>
#include <windows.h>
#pragma comment(lib, "pthreadVC2.lib") 
#define N 5
#define THINKING 0
#define EATING 1
#define LEFT (i - 1) % N
#define RIGHT (i + 1) % N
using namespace std;
int status[N];
pthread_mutex_t  mutex = PTHREAD_MUTEX_INITIALIZER;

bool work(int i){
	if (status[LEFT] != EATING && status[RIGHT] != EATING){
		status[i] = EATING;
		return true;
	}
	return false;
}
void think(int i){
	if (status[i] == THINKING){
		printf("%d 号哲学家正在在思考\n");
		Sleep(100);
	}
}
void take_chopsticks(int i){
	pthread_mutex_lock(&mutex);
	work(i);
	pthread_mutex_unlock(&mutex);
}

void eat(int i){
	if (status[i] == EATING){
		printf("%d 号哲学家正在就餐\n");
		Sleep(100);
	}
}

void put_chopsticks(int i){
	status[i] = THINKING;

}

DWORD WINAPI ThreadProcA(LPVOID pParam){
	int *p =( int*)pParam;
	int i = *p;
	while (true){
		//思考
		think(i);
		//拿起筷子
		take_chopsticks(i);
		//开始吃饭
		eat(i);
		//放下筷子
		put_chopsticks(i);
	}
	return 0;
}
int main(){
	int i;
	HANDLE h[N];
	for (i = 1; i <= N; i++){
		//(LPTHREAD_START_ROUTINE)
		h[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcA, &i, 0, NULL);
	}
}