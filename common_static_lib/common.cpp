#include <unistd.h>
#include <stdio.h>
#include <time.h>


int add_init(int param1,int param2)
{
    return param1+param2;
}

int get_my_time()
{
    return (int)(time(NULL));
}

