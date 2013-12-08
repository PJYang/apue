#include "chapter8.h"

int chapter8_6()
{
    pid_t pid;
    int status;

    if((pid = fork()) < 0)
    {
        err_sys("fork error");
    }
    else if(pid == 0)
    {
        exit(7);
    }

    if(wait(&status) != pid)
    {
        err_sys("wait error");
    }
    pr_exit(status);
   

    if((pid = fork()) < 0)
    {
        err_sys("fork error");
    }
    else if(pid == 0)
    {
        abort();
    }

    if(wait(&status) != pid)
    {
        err_sys("wait error");
    }
    pr_exit(status);
   

    if((pid = fork()) < 0)
    {
        err_sys("fork error");
    }
    else if(pid == 0)
    {
        status /= 0;
    }

    if(wait(&status) != pid)
    {
        err_sys("wait error");
    }
    pr_exit(status);

    exit(0);
}

int chapter8_8()
{
    pid_t pid;

    if((pid=fork()) < 0)
    {
        err_sys("fork error");
    }
    else if(pid == 0)
    {
        if((pid=fork()) < 0)
        {
            err_sys("fork error");
        }
        else if(pid > 0)
        {
            exit(0);
        }

        sleep(2);

        printf("second child, parent pid = %d\n", getppid());
        exit(0);
    }
    
    if(waitpid(pid, NULL, 0) != pid)
    {
        err_sys("waitpid error");
    }

    exit(0);
}
