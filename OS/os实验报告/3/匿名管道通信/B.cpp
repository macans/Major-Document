#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

int main()
{
    char s[1001];
    while(1){
        scanf("%s", s);
        //B进程读入字符转成大写并输出
        for(int i = 0; i <= strlen(i); i++){
            if(s[i] > 'Z'){
                s[i] = s[i] - ('a' - 'A');
            }
        }
        return 0;

    }
    gets(s);
}
