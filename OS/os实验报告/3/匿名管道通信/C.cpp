#include <afx.h>
#include <windows.h>
#include <cstdio>

HANDLE hPipeRead, hPipeWrite;
void CreateSecurityAttrbutes(PSECURITY_ATTRIBUTES pSa){
	pSa->bInheritHandle = TRUE;
	pSa->lpSecurityDescriptor = NULL;
	pSa->nLength = sizeof(SECURITY_ATTRIBUTES);
}

void CreateSInfo(LPSTARTUPINFO lpsInfo){
	memset(lpsInfo, 0, sizeof(STARTUPINFO));
	lpsInfo->cb = sizeof(STARTUPINFO);
	lpsInfo->dwFlags = STARTF_USESTDHANDLES;
	lpsInfo->hStdInput = hPipeRead;
	lpsInfo->hStdOutput = hPipeWrite;
	lpsInfo->hStdError = GetStdHandle(STD_ERROR_HANDLE);
}
void FromAToB(){
	DWORD dwRead, dwWrite;
	char* pReadBuf;
	CString cStrData;
	char* pSendData;
	while (1){
		pReadBuf = new char[101];
		//从匿名通道读入
		if (!ReadFile(hPipeRead, pReadBuf, 101, &dwRead, NULL)){
			printf("read failed\n");
		}
		cStrData.Empty();
		cStrData = pReadBuf;
		while (!cStrData.IsEmpty()){
			pSendData = new char[cStrData.GetLength() + 1];
			memset(pSendData, 0, cStrData.GetLength() + 1);
			for (int i = 0; i < cStrData.GetLength() + 1; i++){
				pSendData[i] = (char)cStrData.GetAt(i);
			}
			//将从A中读入的数据通过匿名通道写入B
			if (!WriteFile(hPipeWrite, pReadBuf, strlen(pReadBuf), &dwWrite, NULL)){
				printf("write failed\n");
			}
		}
	}
	
}
int main(){
	SECURITY_ATTRIBUTES sa;
	PROCESS_INFORMATION pInfo;
	STARTUPINFO sInfo;
	CreateSecurityAttrbutes(&sa);
	if (!CreatePipe(&hPipeRead, &hPipeWrite, &sa, 0)){
		printf("create pipe failed\n");
	}
	CreateSInfo(&sInfo);
	LPTSTR dir = new TCHAR[MAX_PATH];
	//依次生成A、B进程
	if (!CreateProcess(TEXT("E:\\Data\\Source\\acm\\os_3_three_A\\bin\\Release\\os_3_three_A.exe"),
					NULL, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &sInfo, &pInfo)){
		printf("create a failed\n");
	};
	if (!CreateProcess(TEXT("E:\\Data\\Source\\acm\\os_3_three_B\\bin\\Release\\os_3_three_B.exe"),
		NULL, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &sInfo, &pInfo)){
		printf("create b failed\n");
	};
	FromAToB();
	return 0;
}