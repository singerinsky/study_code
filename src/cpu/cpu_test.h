#ifndef DBD84527_722C_48EC_A2C7_88FD0BFE8B16
#define DBD84527_722C_48EC_A2C7_88FD0BFE8B16
#include "../header.h"
#include <stdio.h>
#include <stdint.h>
#include <x86intrin.h>

TEST(TestCpu, cache)
{
    volatile uint8_t data[1000] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    volatile uint8_t* addr;
    uint64_t i;
    unsigned int junk = 0;
    uint64_t t1, t2;

    printf("data: %p\n", data);

    _mm_clflush((const void*)data);
    printf("accessing bytes in a cache line:\n");
    for (i = 0; i < 10; i = i + 1)
    {
        t1 = __rdtscp(&junk);
        addr = &data[i];
        junk = *addr;
        t2 = __rdtscp(&junk) - t1;
        printf("i = %2d, cycles: %ld\n", i, t2);
    }
    t1 = __rdtscp(&junk);
    int rand[1000][1000];
    int randvalue = time(NULL);
    int tmp = 0 ;
    //_mm_clflush((const void*)rand);
    for (int i = 0; i < 1000; i++)
    {
        for (int j = 0; j < 1000; j++)
        {
            rand[i][j] = i * j + randvalue;
            int* p = &rand[i][j];
            tmp = *p;
        }
    }
    t2 = __rdtscp(&junk) - t1;
    printf("cost cycles 1: %ld\n",  t2);
    t1 = __rdtscp(&junk);
    _mm_clflush((const void*)rand);
    for (int i = 0; i < 1000; i++)
    {
        for (int j = 0; j < 1000; j++)
        {
            rand[j][i] = i * j + randvalue;
            int* p = &rand[j][i];
            tmp = *p;
        }
    }
    t2 = __rdtscp(&junk) - t1;
    printf("cost cycles 2: %ld\n", t2);
}

#endif /* DBD84527_722C_48EC_A2C7_88FD0BFE8B16 */
