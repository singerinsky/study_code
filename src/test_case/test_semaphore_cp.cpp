#include "../header.h"
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

#define BUFF_SIZE 10
char buffer[BUFF_SIZE];
int cpcount;
sem_t sem_mutex;
sem_t p_sem_mutex;
sem_t c_sem_mutex;

void* p_funp(void* argc)
{
    sem_wait(&p_sem_mutex);
    sem_wait(&sem_mutex);

    cpcount++;
    LOG(INFO) << "p:" << cpcount;
    if (cpcount < BUFF_SIZE)
    {
        sem_post(&p_sem_mutex);
    }
    if (cpcount > 0)
    {
        sem_post(&c_sem_mutex);
    }
    sem_post(&sem_mutex);
    return nullptr;
}

void* c_func(void* arg)
{
    sem_wait(&c_sem_mutex);
    sem_wait(&sem_mutex);

    cpcount--;
    LOG(INFO) << "c:" << cpcount;
    if (cpcount > 0)
    {
        sem_post(&c_sem_mutex);
    }
    if (cpcount < BUFF_SIZE)
    {
        sem_post(&p_sem_mutex);
    }

    sem_post(&sem_mutex);
    return nullptr;
}

void test_main()
{
    pthread_t pid1, pid2;

    sem_init(&sem_mutex, 0, 1);
    sem_init(&p_sem_mutex, 0, 1);
    sem_init(&c_sem_mutex, 0, 0);

    pthread_create(&pid1, NULL, p_funp, NULL);
    pthread_create(&pid2, NULL, c_func, NULL);

    pthread_join(pid1, NULL);
    pthread_join(pid2, NULL);

    sem_destroy(&sem_mutex);
    sem_destroy(&c_sem_mutex);
    sem_destroy(&p_sem_mutex);
}
TEST(BaseTest, semaphore_cp)
{
    ASSERT_EXIT((test_main(), exit(0)), ::testing::ExitedWithCode(0), ".*");
}