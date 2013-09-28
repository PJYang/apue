#include "../include/apue.h"
#include <fcntl.h>

char buf1[] = "abcdefhhij";
char buf2[] = "ABCDEFHIJ";

int make_hole_file(void)
{
	int fd;

	if((fd = creat("file.hole", FILE_MODE)) < 0)
	{
		err_sys("create error");
	}

	if(write(fd, buf1, strlen(buf1)) != strlen(buf1))
	{
		err_sys("buf1 write error");
	}

	if(lseek(fd, 16384, SEEK_SET) == -1)
	{
		err_sys("lseek error");
	}

	if(write(fd, buf2, strlen(buf2)) != strlen(buf2))
	{
		err_sys("write error");
	}

	return 0;
}

int read_seek_write(void)
{
	int fd;

	if((fd = open("file.hole", O_RDWR)) < 0)
	{
		err_sys("open error");
	}

	printf("file desciptor: %d", fd);

	if(lseek(fd, 1000, SEEK_SET) == -1)
	{
		err_sys("lseek error");
	}

	if(write(fd, buf2, strlen(buf2)) != strlen(buf2))
	{
		err_sys("write error");
	}

	close(fd);
}

int read_in_write_out(void)
{
	int n;

	char buf[4096];

	while((n=read(STDIN_FILENO, buf, 4096)) > 0)
	{
		if(write(STDOUT_FILENO, buf, n) != n)
		{
			err_sys("write error");
		}
	}

	if(n < 0)
	{
		err_sys("read error");
	}

	return 0;
}

int main(int argc, char* argv[])
{
	read_in_write_out();

	return 0;
}

