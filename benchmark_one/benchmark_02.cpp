#include "../header.h"
#include "../util/class_sample.h"
#include "../util/thread_ring_buffer.h"
#include <algorithm>
#include <benchmark/benchmark.h>
#include <cstdlib>
#include <cstring>
#include <map>
#include <memory>
#include <string>
#include <unistd.h>
#include <unordered_map>

template class CRingBuffer<char, 4096>;

void function_test_ring_buffer(benchmark::State &state) {
  for (auto _ : state) {
    CRingBuffer<char, 4096> buffer;
    LOG(INFO) << buffer.GetSize();
  }
}
BENCHMARK(function_test_ring_buffer);

void function_test_calc_one(benchmark::State &state) {
  for (auto _ : state) {
    uint32_t size = 100;
    uint32_t head = 0;
    uint32_t tail = 0;
    tail = 11;
    head = 10;
    uint32_t free = size + tail - head;
  }
}
BENCHMARK(function_test_calc_one);

void function_test_calc_two(benchmark::State &state) {
  for (auto _ : state) {
    uint32_t size = 99;
    uint32_t head = 0;
    uint32_t tail = 0;
    tail = 10;
    head = 11;
    if (head > tail) {
      uint32_t free = size + tail - head;
    }
  }
}
BENCHMARK(function_test_calc_two);