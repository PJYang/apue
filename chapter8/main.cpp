#include "../include/apue.h"
#include "chapter8.h"

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        printf("usage: %s program_index\n", argv[0]);
        return -1;
    }

    int pro_index = atoi(argv[1]);

    switch(pro_index)
    {
        case 6:
            chapter8_6();
            break;

        case 8:
            chapter8_8();
            break;

        default:
            break;
    }

    return 0;
}
