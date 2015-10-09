#include<stdio.h>
#include<time.h>
#include<windows.h>
#include<iostream>
using namespace std;

int main(){
	int i = 0;
	time_t t = time(NULL);
	char *time, *info, *c;
	c = (char*)malloc(100);
	time = ctime(&t);
	info = "本文件最后一次打开和运行日期是 ";
	FILE *fp;

	if ((fp = fopen("config.txt", "r+")) == NULL){
		printf("can not open this file\n");
		exit(0);
	}

	while (fgets(c, 100, fp)){
		if (i == 0){
			i++;
			continue;
		}

		c[strlen(c) - 1] = '\0'; 
		//初始化进程参数
		STARTUPINFO si;
		memset(&si, 0, sizeof(STARTUPINFO));
		si.cb = sizeof(STARTUPINFO);
		si.dwFlags = STARTF_USESHOWWINDOW;
		si.wShowWindow = SW_SHOW;
		PROCESS_INFORMATION pi; 
		//创建进程
		if (!CreateProcess((wchar_t*)c, NULL, NULL, NULL, false, 0, NULL, NULL, &si, &pi)){
			printf("%s打开失败\n", c);
		}
		else{
			printf("%s打开成功\n", c);
		}


	}
	fseek(fp, 0, 0);
	fputs(info, fp);
	fputs(time, fp);

	fclose(fp);

	return 0;
}
