#include "../include/apue.h"

#define BUFFSIZE 4096

void set_fl(int fd, int flags)
{
    int val;

    if((val=fcntl(fd, F_GETFL, 0)) < 0)
    {
        err_sys("fcntl F_GETFL error");
    }

    val |= flags;

    if(fcntl(fd, F_SETFL, val) < 0)
    {
        err_sys("fcntl F_SETFL error");
    }
}

int write_with_fsync()
{
    int n;
    char buf[BUFFSIZE];

    int f = open("/tmp/pjyang.3423",  O_WRONLY | O_CREAT);

    while((n=read(STDIN_FILENO, buf, BUFFSIZE))>0)
    {
        if(write(f, buf, n) != n)
        {
            err_sys("write error");
        }

        fsync(f);
    }

    if(n<0)
    {
        err_sys("read error");
    }

    close(f);
}

int write_with_normal()
{
    int n;
    char buf[BUFFSIZE];

    int f = open("/tmp/pjyang.3423",  O_WRONLY | O_CREAT);

    while((n=read(STDIN_FILENO, buf, BUFFSIZE))>0)
    {
        if(write(f, buf, n) != n)
        {
            err_sys("write error");
        }
    }

    if(n<0)
    {
        err_sys("read error");
    }

    close(f);
}

int write_with_fdatasync()
{
    int n;
    char buf[BUFFSIZE];

    int f = open("/tmp/pjyang.3423", O_WRONLY |  O_CREAT);

    while((n=read(STDIN_FILENO, buf, BUFFSIZE))>0)
    {
        if(write(f, buf, n) != n)
        {
            err_sys("write error");
        }

        fdatasync(f);
    }

    if(n<0)
    {
        err_sys("read error");
    }

    close(f);
}

int write_with_sync()
{
    int n;
    char buf[BUFFSIZE];

    int f = open("/tmp/pjyang.3423", O_WRONLY  | O_CREAT);

    while((n=read(STDIN_FILENO, buf, BUFFSIZE))>0)
    {
        if(write(f, buf, n) != n)
        {
            err_sys("write error");
        }

        sync();
    }

    if(n<0)
    {
        err_sys("read error");
    }

    close(f);
}

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        err_quit("usage %s [fsync|fdatasync|sync]", argv[0]);
    }

    if(strcmp(argv[1], "fsync") == 0)
    {
        write_with_fsync();
    }
    else if(strcmp(argv[1], "sync") == 0)
    {
        write_with_sync();
    }
    else if(strcmp(argv[1], "fdatasync") == 0)
    {
        write_with_fdatasync();
    }
    else if(strcmp(argv[1], "normal") == 0)
    {
        write_with_normal();
    }
    else
    {
        err_msg("unsupported sync method");
    }

    return(0);
}

