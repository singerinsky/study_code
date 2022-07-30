#include "Common.h"
#include "ConcurrentAlloc.h"

#define SIZE 16

void BenchmarkMalloc(size_t ntimes, size_t nworks, size_t rounds) {
  std::vector<std::thread> vthread(nworks);
  size_t malloc_costtime = 0;
  size_t free_costtime = 0;
  for (size_t k = 0; k < nworks; ++k) {
    vthread[k] = std::thread([&]() {
      std::vector<void *> v;
      v.reserve(ntimes);
      for (size_t j = 0; j < rounds; ++j) {
        size_t begin1 = clock();
        for (size_t i = 0; i < ntimes; i++) {
          v.push_back(malloc(SIZE));
        }
        size_t end1 = clock();
        size_t begin2 = clock();
        for (size_t i = 0; i < ntimes; i++) {
          free(v[i]);
        }
        size_t end2 = clock();
        v.clear();
        malloc_costtime += end1 - begin1;
        free_costtime += end2 - begin2;
      }
    });
  }
  for (auto &t : vthread) {
    t.join();
  }
  printf("%lu个线程并发执行%lu轮次，每轮次malloc %lu次: 花费：%lu ms\n", nworks,
         rounds, ntimes, malloc_costtime);
  printf("%lu个线程并发执行%lu轮次，每轮次free %lu次: 花费：%lu ms\n", nworks,
         rounds, ntimes, free_costtime);
  printf("%lu个线程并发malloc&free %lu次，总计花费：%lu ms\n", nworks,
         nworks * rounds * ntimes, malloc_costtime + free_costtime);
}

// 单轮次申请释放次数 线程数 轮次
void BenchmarkConcurrentMalloc(size_t ntimes, size_t nworks, size_t rounds) {
  std::vector<std::thread> vthread(nworks);
  size_t malloc_costtime = 0;
  size_t free_costtime = 0;
  for (size_t k = 0; k < nworks; ++k) {
    vthread[k] = std::thread([&]() {
      std::vector<void *> v;
      v.reserve(ntimes);
      for (size_t j = 0; j < rounds; ++j) {
        size_t begin1 = clock();
        for (size_t i = 0; i < ntimes; i++) {
          v.push_back(ConcurrentAlloc(SIZE));
        }
        size_t end1 = clock();
        size_t begin2 = clock();
        for (size_t i = 0; i < ntimes; i++) {
          ConcurrentFree(v[i]);
        }
        size_t end2 = clock();
        v.clear();
        malloc_costtime += end1 - begin1;
        free_costtime += end2 - begin2;
      }
    });
  }
  for (auto &t : vthread) {
    t.join();
  }
  printf("%lu个线程并发执行%lu轮次，每轮次concurrent alloc %lu次: 花费：%lu ms\n",
         nworks, rounds, ntimes, malloc_costtime);
  printf("%lu个线程并发执行%lu轮次，每轮次concurrent dealloc %lu次: 花费：%lu ms\n",
         nworks, rounds, ntimes, free_costtime);
  printf("%lu个线程并发concurrent alloc&dealloc %lu次，总计花费：%lu ms\n", nworks,
         nworks * rounds * ntimes, malloc_costtime + free_costtime);
}

int main_t() {
  cout << "==========================================================" << endl;

  // BenchmarkMalloc(100, 10000, 10);
  cout << endl;
  BenchmarkConcurrentMalloc(100, 10000, 10);
  cout << endl << endl;

  cout << "==========================================================" << endl;

  // system("pause");
  return 0;
}
