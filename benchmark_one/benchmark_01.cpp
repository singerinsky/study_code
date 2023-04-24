#include "../header.h"
#include "../util/class_sample.h"
#include <algorithm>
#include <benchmark/benchmark.h>
#include <cstdlib>
#include <cstring>
#include <map>
#include <memory>
#include <string>
#include <unistd.h>
#include <unordered_map>

std::unique_ptr<float> SingletonClassTemplate<float>::_ptr;
std::unique_ptr<unsigned int> SingletonClassTemplate<unsigned int>::_ptr;

void function_benchmark_1(benchmark::State &state) {
  auto length = state.range(0);
  for (auto _ : state) {
    for (int index = 0; index < length; index++) {
      int i = 0;
      int j = ++i;
    }
  }
}
// BENCHMARK(function_benchmark_1)->Arg(10000);

void function_benchmark_2(benchmark::State &state) {
  auto length = state.range(0);
  for (auto _ : state) {
    for (int index = 0; index < length; index++) {
      int i = 0;
      int j = i++;
    }
  }
}
// BENCHMARK(function_benchmark_2)->Arg(10000);

void function_benchmark_map(benchmark::State &state) {
  std::map<int, int> test_map;
  auto length = state.range(0);
  for (auto _ : state) {
    for (int index = 0; index < length; index++) {
      test_map[index] = index;
      // cpu_relax();
    }
  }
}
// BENCHMARK(function_benchmark_map)->Arg(10000);

void function_benchmark_hashmap(benchmark::State &state) {
  std::unordered_map<int, int> test_map;
  auto length = state.range(0);
  for (auto _ : state) {
    for (int index = 0; index < length; index++) {
      test_map[index] = index;
    }
  }
}
// BENCHMARK(function_benchmark_hashmap)->Arg(10000);

void function_benchmark_memory_stack(benchmark::State &state) {
  char srcbuff[128] = {1, 2, 34, 45, 65, 6, 7, 78, 8, 8, 9, 9, 9, 0, 0};
  for (auto _ : state) {
    char buff[1024] = {0};
    int i = std::rand() % 128;
    memcpy(buff, srcbuff, i);
  }
}
// BENCHMARK(function_benchmark_memory_stack)->Iterations(1000000);

void function_benchmark_memory_heap(benchmark::State &state) {
  char srcbuff[128] = {1, 2, 34, 45, 65, 6, 7, 78, 8, 8, 9, 9, 9, 0, 0};
  for (auto _ : state) {
    char *buff = new char[1024];
    int i = std::rand() % 128;
    memcpy(buff, srcbuff, i);
    delete[] buff;
  }
}
// BENCHMARK(function_benchmark_memory_heap)->Iterations(1000000);

void function_benchmark_memory_read(benchmark::State &state) {
  std::vector<float> large_memory_buffer;
  void *buff = malloc(sizeof(float) * 100000);
  float *point = static_cast<float *>(buff);
  std::vector<float *> vecs;
  for (int i = 0; i < 100000; i++) {
    vecs.push_back(point + i);
  }

  for (auto _ : state) {
    for (size_t i = 0; i < vecs.size(); ++i) {
      *(vecs[i]) = *(vecs[i]) * 2.0f;
      __builtin_prefetch(vecs[i + 1], 1, 3);
      __builtin_prefetch(vecs[i + 1], 0, 3);
    }
  }
}

BENCHMARK(function_benchmark_memory_read);

void function_benchmark_memory_read_with_rand(benchmark::State &state) {
  std::vector<float> large_memory_buffer;
  void *buff = malloc(sizeof(float) * 100000);
  float *point = static_cast<float *>(buff);
  std::vector<float *> vecs;
  for (int i = 0; i < 100000; i++) {
    vecs.push_back(point + i);
  }

  std::random_shuffle(vecs.begin(), vecs.end());

  int step = 10000;
  for (auto _ : state) {
    for (size_t i = 0; i < vecs.size(); ++i) {
      //__builtin_prefetch(vecs[i + step]);
      *(vecs[i]) = *(vecs[i]) * 2.0f;
    }
  }
}

BENCHMARK(function_benchmark_memory_read_with_rand);

void function_benchmark_singleton_with_mutex_class(benchmark::State &state) {
  for (auto _ : state) {
    auto &instance = SingletonClassTemplate<int>::GetInstance();
    instance++;
  }
}

BENCHMARK(function_benchmark_singleton_with_mutex_class);

void function_benchmark_singleton_without_mutex_class(benchmark::State &state) {
  for (auto _ : state) {
    auto &instance = SingletonClassTemplate<unsigned int>::GetInstance();
    instance++;
  }
}

BENCHMARK(function_benchmark_singleton_without_mutex_class);

void function_pass_ref(const std::string &str) {
  // LOG(INFO) << str;
}

void function_pass_value(std::string str) {
  // LOG(INFO) << str;
}

void function_test_pass_value(benchmark::State &state) {
  for (auto _ : state) {
    int value = rand();
    std::string str = std::to_string(value);
    function_pass_value(str);
  }
}

BENCHMARK(function_test_pass_value);

void function_test_pass_ref(benchmark::State &state) {
  for (auto _ : state) {
    int value = rand();
    std::string str = std::to_string(value);
    function_pass_ref(str);
  }
}

BENCHMARK(function_test_pass_ref);

void function_test_loop(benchmark::State &state) {
  for (auto _ : state) {
    int array[10000];
    int j = 10000;
    int i = 0;
    for (; i < (j & ((~(unsigned)0x7))); i += 8) {
      array[i] = i;
      array[i + 1] = i + 1;
      array[i + 2] = i + 2;
      array[i + 3] = i + 3;
      array[i + 4] = i + 4;
      array[i + 5] = i + 5;
      array[i + 6] = i + 6;
      array[i + 7] = i + 7;
    }
    switch (j & 0x07) {
    case 7:
      array[i++] = i + 1;
    case 6:
      array[i++] = i + 1;
    case 5:
      array[i++] = i + 1;
    case 4:
      array[i++] = i + 1;
    case 3:
      array[i++] = i + 1;
    case 2:
      array[i++] = i + 1;
    case 1:
      array[i++] = i + 1;
    }
  }
}
BENCHMARK(function_test_loop);

void function_test_loop_without_op(benchmark::State &state) {
  for (auto _ : state) {
    int array[10000];
    int j = 10000;
    int i = 0;
    for (; i < 10000; i++) {
      array[i] = i;
    }
  }
}
BENCHMARK(function_test_loop_without_op);

// BENCHMARK_MAIN()
// {
//     ::benchmark::Initialize(&argc, argv);
//     ::benchmark::RunSpecifiedBenchmarks();
//     return 1;
// }
int main(int argc, char **argv) {
  ::benchmark::Initialize(&argc, argv);
  ::benchmark::RunSpecifiedBenchmarks();
  return 1;
}
