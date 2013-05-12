/****************************************************************************
1. C语言的栈，栈顶为低地址，栈底为高地址。 C语言对参数的入栈方式是从右至左的， 从右至左的入栈方式使得可以处理可变参数， 如果是从左至右，试想，最后拿到的地址是第几个参数的，无从得知，而如果是从右至左的，可以肯定最后拿到的地址一定是第一个的，就可以往上加，一步步的拿到想要的参数
****************************************************************************/
#include "apue.h"

#include <errno.h>
#include <stdarg.h>

static void err_doit(int, int, const char *, va_list);

void err_sys(const char *fmt, ...)
{
    va_list ap;
    
    va_start(ap, fmt);
    err_doit(1, errno, fmt, ap);
    va_end(ap);
    
    exit(1);
}

void err_quit(const char *fmt, ...)
{
    va_list ap;
    
    va_start(ap, fmt);  //经va_start后， ap将指向第一个可变参数
    err_doit(0, 0, fmt, ap);
    va_end(ap);
    
    exit(1);
}

void err_msg(const char *fmt, ...)
{
    va_list ap;
    
    va_start(ap, fmt);
    err_doit(0, 0, fmt, ap);
    va_end(ap);
    
    exit(1);
}

static void err_doit(int errnoflag, int error, const char *fmt, va_list ap)
{
    char buf[MAXLINE];
    vsnprintf(buf, MAXLINE, fmt, ap); //属于可变参数。用于向字符串中打印数据、数据格式用户自定义, fmt指打印数据的格式
    if(errnoflag)
    {
        snprintf(buf+strlen(buf), MAXLINE-strlen(buf), ": %s", strerror(error));
    }
        
    strcat(buf, "\n");
    fflush(stdout);
    fputs(buf, stderr);
    fflush(NULL);
}

