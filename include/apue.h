#ifndef __APUE_H__
#define __APUE_H__

#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <signal.h>

#define MAXLINE 4096

void err_sys(const char *, ...);

void err_quit(const char*, ...);

void err_msg(const char*, ...);

long open_max(void);

void daemonize(const char* cmd);

#endif
