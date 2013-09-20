#include "apue.h"
#include<errno.h>
#include<limits.h>
#include <sys/stat.h>
#include <syslog.h>
#include <fcntl.h>
#include <sys/resource.h>

#ifdef OPEN_MAX
static long openmax = OPEN_MAX;
#else
static long openmax = 0;
#endif

#define OPEN_MAX_GUESS 256

long open_max(void)
{
    if(openmax == 0)
    {
        errno = 0;
        if((openmax = sysconf(_SC_OPEN_MAX)) < 0)
        {
            if(errno == 0)
            {
                openmax = OPEN_MAX_GUESS;
            }
            else
            {
                err_sys("sysconf error for _SC_OPEN_MAX");
            }
        }
        
        return(openmax);
    }
}

void daemonize(const char *cmd)
{
	int i, fd0, fd1, fd2;
	pid_t pid;
	struct rlimit r1;
	struct sigaction sa;


	umask(0);


	if(getrlimit(RLIMIT_NOFILE, &r1) < 0)
	{
		err_quit("%s: can't get file limit", cmd);
	}

	if((pid = fork()) < 0)
	{
		err_quit("%s: can't fork", cmd);
	}
	else if(pid != 0)
	{
		exit(0);
	}
	
	setsid();

	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;

	if(sigaction(SIGHUP, &sa, NULL) < 0)
	{
		err_quit("%s: can't ignore SIGHUP");
	}

	if((pid=fork()) < 0)
	{
		err_quit("%s: can't fork", cmd);
	}
	else if(pid != 0)
	{
		exit(0);
	}

	if(chdir("/") < 0)
	{
		err_quit("%s: can't chage directory to /");
	}

	if(r1.rlim_max == RLIM_INFINITY)
	{
		r1.rlim_max = 1024;
	}

	for(i=0; i<r1.rlim_max; i++)
	{
		close(i);
	}

	fd0 = open("/dev/null", O_RDWR);
	fd1 = dup(0);
	fd2 = dup(0);

	openlog(cmd, LOG_CONS, LOG_DAEMON);
	if(fd0 !=0 || fd1 !=1 || fd2 != 2)
	{
		syslog(LOG_ERR, "unexpected file descriptors %d %d %d", fd0, fd1, fd2);
		exit(1);
	}
}
