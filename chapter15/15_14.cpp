//从标准输入读取一个字符，将其转换为小写字母，输出到屏幕上
#include "../include/apue.h"

#include <ctype.h>

int main()
{
    int c;
    
    while((c=getchar())!=EOF)
    {
        if(isupper(c))
        {
            c = tolower(c);
        }
        
        if (putchar(c) == EOF)
        {
            err_sys("output error");            
        }
        
        if(c=='\n')
        {
            fflush(stdout);
        }
        
        if(c=='q')
        {
            break;
        }
    }
    
    exit(0);
}