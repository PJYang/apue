#include "../include/apue.h"
#include <sys/shm.h>

using namespace std;

const int ARRAY_SIZE = 40000;
const int MALLOC_SIZE = 100000;
const int SHM_SIZE = 100000;
const int SHM_MODE = 0600;

char array[ARRAY_SIZE];

int main()
{
    int shmid; 
    char *ptr, *shmptr;
    
    //数组占据的内存范围, 在bss段中分配
    printf("array[] from %lx to %lx\n", (unsigned long)&array[0], (unsigned long)&array[ARRAY_SIZE-1]);
    
    
    if((ptr=(char*)malloc(MALLOC_SIZE))==NULL) //在堆上进行分配
    {
        err_sys("malloc error");
    }
    printf("malloced from address %lx to %lx\n", (unsigned long)ptr, (unsigned long)(ptr+MALLOC_SIZE));
    
    if((shmid=shmget(IPC_PRIVATE, SHM_SIZE, SHM_MODE))<0) //取得共享内存的id, 并初始化分配的共享内存
    {
        err_sys("shmget error");
    }

    printf("stack arround %lx\n", (unsigned long)&shmid);
    if((shmptr=(char*)shmat(shmid, 0, 0))==(void *) - 1) //连接共享内存标识符为shmid的共享内存，连接成功后把共享内存区对象映射到调用进程的地址空间，随后可像本地空间一样访问
    {
        err_sys("shmat error");
    }
    
    printf("shared memory attached from %lx to %lx\n", (unsigned long)shmptr, (unsigned long)shmptr+SHM_SIZE); //连接后本进程的地址空间
    
    if(shmctl(shmid, IPC_RMID, 0) < 0)
    {
        err_sys("shmctl error");
    }
    
    return(0);
}