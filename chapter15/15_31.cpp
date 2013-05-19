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
    
    //����ռ�ݵ��ڴ淶Χ, ��bss���з���
    printf("array[] from %lx to %lx\n", (unsigned long)&array[0], (unsigned long)&array[ARRAY_SIZE-1]);
    
    
    if((ptr=(char*)malloc(MALLOC_SIZE))==NULL) //�ڶ��Ͻ��з���
    {
        err_sys("malloc error");
    }
    printf("malloced from address %lx to %lx\n", (unsigned long)ptr, (unsigned long)(ptr+MALLOC_SIZE));
    
    if((shmid=shmget(IPC_PRIVATE, SHM_SIZE, SHM_MODE))<0) //ȡ�ù����ڴ��id, ����ʼ������Ĺ����ڴ�
    {
        err_sys("shmget error");
    }

    printf("stack arround %lx\n", (unsigned long)&shmid);
    if((shmptr=(char*)shmat(shmid, 0, 0))==(void *) - 1) //���ӹ����ڴ��ʶ��Ϊshmid�Ĺ����ڴ棬���ӳɹ���ѹ����ڴ�������ӳ�䵽���ý��̵ĵ�ַ�ռ䣬�����񱾵ؿռ�һ������
    {
        err_sys("shmat error");
    }
    
    printf("shared memory attached from %lx to %lx\n", (unsigned long)shmptr, (unsigned long)shmptr+SHM_SIZE); //���Ӻ󱾽��̵ĵ�ַ�ռ�
    
    if(shmctl(shmid, IPC_RMID, 0) < 0)
    {
        err_sys("shmctl error");
    }
    
    return(0);
}