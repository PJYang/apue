//协同进程，其实终端就相当于一个协同进程，当其调用一个可执行程序的时候，它向这个可执行程序的输入写数据，然后再从这个程序的输出读数据
#include "../include/apue.h"

int main(void)
{
    char line[MAXLINE];
    FILE *fpin;
    
    if((fpin = popen("./convert_uppercase", "r"))==NULL)
    {
        err_sys("popen error");
    }
    
    for(;;)
    {
        fputs("prompt> ", stdout);
        fflush(stdout);
        
        if(fgets(line, MAXLINE, fpin)==NULL) //从管道里的输出读取数据
            break;
            
        if(fputs(line, stdout) == EOF)
            err_sys("fputs error to pipe");
    }

    if(pclose(fpin) == -1)
    {
        err_sys("pclose error");
    }
    
    putchar('\n');
    
    exit(0);
}