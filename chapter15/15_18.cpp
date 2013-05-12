//协作进程是一个进程，与它相关的还有另一进程，这个进程向协同进程的标准输入写数据，并从标准输出读取数据
#include "../include/apue.h"

static void sig_pipe(int);

int main()
{
    int n, fd1[2], fd2[2];
    pid_t pid;
    char line[MAXLINE];
    
    if(signal(SIGPIPE, sig_pipe) == SIG_ERR) //为信号SIGPIPE注册信号处理函数
    {
        err_sys("signal error");
    }
    
    if(pipe(fd1) < 0 || pipe(fd2) < 0) //生成两个管道，用于双向通信
    {
        err_sys("pipe error");
    }
    
    if((pid=fork())<0)
    {
        err_sys("fork error");
    }
    else if(pid>0) //对于父进程
    {
        close(fd1[0]); //关闭管道１的读端
        close(fd2[1]); //关闭管理２的写端
        
        while(fgets(line, MAXLINE, stdin) != NULL)
        {
            n = strlen(line);
            if(write(fd1[1], line, n) != n) //父进程向管道１的写端写数据
            {
                err_sys("read error to pipe");
            }
            
            if((n=read(fd2[0], line, MAXLINE))<0) //父进程向管道２的读端读数据
            {
                err_sys("read error from pipe"); 
            }
            
            if(n==0)
            {
                err_msg("child closed pipe");
                break;
            }
            
            line[n] = 0;
            if(fputs(line, stdout) == EOF)
            {
                err_sys("fputs error");
            }            
        }
        
        if(ferror(stdin))
        {
            err_sys("fgets error on stdin");
        }
        
        exit(0);
    }
    else //子进程的输入输出分别设为标准输入输出
    {
        close(fd1[1]); //关闭管道１的写端
        close(fd2[0]); //关闭管理２的读端
        
        if(fd1[0] != STDIN_FILENO)
        {
            if(dup2(fd1[0], STDIN_FILENO) != STDIN_FILENO)
            {
                err_sys("dup2 error to stdin");
                close(fd1[0]);
            }
        }
        
        if(fd2[1] != STDOUT_FILENO)
        {
            if(dup2(fd2[1], STDOUT_FILENO) != STDOUT_FILENO)
            {
                err_sys("dup2 error to stdout");
                close(fd2[1]);
            }            
        }
        
        if(execl("./add2", "add2", (char*)0)<0)
        {
            err_sys("execl error");
        }
    }
}

static void sig_pipe(int signo)
{
    printf("SIGPIPE caught\n");
    exit(1);
}