#include <windows.h>
#include <cstdio>

const char* a[5] = { "one", "two", "three", "four", "five" };

int main(){
	int i;
	//HANDLE hA, hB, hC;
	STARTUPINFO sInfo;
	PROCESS_INFORMATION pInfo;
	LPTSTR dir = new TCHAR[MAX_PATH];
	//A进程输出指定字符
	for (i = 0; i < 5; i++){
		printf("%s\n", a[i]);
	}
	char *s;
	scanf("%s", s);
	system("pause");
	return 0;
}
