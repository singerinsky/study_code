#include "../header.h"
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

int global_var;
sem_t sem_id;

void *thread_fun2(void *arg) {
  //偿试信号量是否大于0，如果是减1，如果不是等待
  sem_wait(&sem_id);
  printf("fun2\n");
  global_var--;
  printf("global_var = %d\n", global_var);
  //信号量加1
  sem_post(&sem_id);
  return nullptr;
}

void *thread_fun1(void *arg) {

  //偿试信号量是否大于0，如果是减1，如果不是等待
  sem_wait(&sem_id);
  printf("fun1\n");
  global_var--;
  printf("global_var = %d\n", global_var);
  //信号量加1
  sem_post(&sem_id);
  return nullptr;
}

TEST(BaseTest, semaphore_thread) {
  global_var = 1;
  pthread_t id1, id2;

  //初始化信号量
  sem_init(&sem_id, 0, 1);

  pthread_create(&id1, NULL, thread_fun1, NULL);
  pthread_create(&id2, NULL, thread_fun2, NULL);
  pthread_join(id1, NULL);
  pthread_join(id2, NULL);

  LOG(INFO) << "main...\n";
}
TEST(BaseTest, semaphore_process) {
  sem_t sem_id;
  //第二个参数为1
  sem_init(&sem_id, 1, 1);

  if (0 == fork()) {
    while (1) {
      sem_wait(&sem_id);
      printf("This child \n");
      sleep(2);
      sem_post(&sem_id);
    }
  }

  while (1) {
    sem_wait(&sem_id);
    printf("This father\n");
    sleep(2);
    sem_post(&sem_id);
  }
}

#define SHMSZ 27
#define SEM_NAME "vik3"

int process_one_deal_with_semaphore(void) {
  char ch;
  int shmid;
  key_t key;
  char *shm, *s;
  sem_t *mutex;

  key = 1000;

  mutex = sem_open(SEM_NAME, O_CREAT, 0644, 1);
  if (mutex == SEM_FAILED) {
    printf("unable to create semaphore");
    sem_unlink(SEM_NAME);
    return -1;
  }

  shmid = shmget(key, SHMSZ, IPC_CREAT | 0666);
  if (shmid < 0) {
    printf("failure in shmget");
    return -1;
  }

  shm = (char *)shmat(shmid, NULL, 0);
  s = shm;

  for (ch = 'A'; ch <= 'Z'; ch++) {
    sem_wait(mutex);
    *s++ = ch;
    sem_post(mutex);
  }

  while (*shm != '*') {
    sleep(1);
  }

  sem_close(mutex);
  sem_unlink(SEM_NAME);
  shmctl(shmid, IPC_RMID, 0);

  return -1;
}
TEST(BaseTest, process_one_deal_with_semaphore) {
  process_one_deal_with_semaphore();
}

int process_two_deal_with_semaphore(void) {
  char ch;
  int shmid;
  key_t key;
  char *shm, *s;
  sem_t *mutex;

  key = 1000;

  mutex = sem_open(SEM_NAME, 0, 0644, 0);
  if (mutex == SEM_FAILED) {
    printf("unable to execute semaphore\n");
    sem_close(mutex);
    return -1;
  }

  shmid = shmget(key, SHMSZ, 0666);
  if (shmid < 0) {
    printf("failure in shmget");
    return -1;
  }

  shm = (char *)shmat(shmid, NULL, 0);
  // s = shm;

  for (s = shm; *s != NULL; s++) {
    sem_wait(mutex);
    putchar(*s);
    sem_post(mutex);
  }
  putchar('\n');
  *shm = '*';

  sem_close(mutex);
  sem_unlink(SEM_NAME);
  shmctl(shmid, IPC_RMID, 0);

  return -1;
}
TEST(BaseTest, process_two_deal_with_semaphore) {
  process_one_deal_with_semaphore();
}