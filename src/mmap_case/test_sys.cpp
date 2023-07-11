#include "../header.h"
#include "../util/class_sample.h"
#include <list>
#include <numeric>
#include <unistd.h>

TEST(TestSys, test_page_size) { LOG(INFO) << sysconf(_SC_PAGESIZE); }

TEST(TestSys, test_core) {

  int nprocs = sysconf(_SC_NPROCESSORS_ONLN);
  std::cout << "Number of logical processors: " << nprocs << std::endl
            << " _SC_NPROCESSORS_CONF:" << sysconf(_SC_NPROCESSORS_CONF);
}

static void *my_thread_func(void *arg) {
  int core_id = sched_getcpu(); // 获取当前线程所在的逻辑核编号
  printf("Thread running on core %d\n", core_id); // 输出逻辑核编号
  return NULL;
}

TEST(TestSys, run_core) {

  int core_id = 14; // 指定逻辑核的编号

  // 创建新线程
  pthread_t thread;
  pthread_create(&thread, NULL, my_thread_func, NULL);

  // 将新线程绑定到指定的逻辑核上
  cpu_set_t cpuset;
  CPU_ZERO(&cpuset);
  CPU_SET(core_id, &cpuset);
  pthread_setaffinity_np(thread, sizeof(cpu_set_t), &cpuset);

  // 等待线程结束
  pthread_join(thread, NULL);
}

// #include <numa.h>

// TEST(TestSys, get_numa) {
//   struct bitmask *cpu_mask;
//   int cpu_id, node;

//   // 初始化NUMA库
//   // numa_init();

//   // 获取系统中的CPU核数
//   int num_cpus = numa_num_configured_cpus();

//   // 遍历每个CPU核
//   int numNodes = numa_num_configured_nodes();
//   printf("Number of NUMA nodes: %d\n", numNodes);

//   // 获取每个NUMA节点的信息
//   for (int i = 0; i < numNodes; i++) {
//     struct bitmask *mask = numa_allocate_nodemask();
//     numa_node_to_cpus(i, mask);
//     printf("CPUs on NUMA node %d: ", i);
//     for (int j = 0; j < numa_num_possible_cpus(); j++) {
//       if (numa_bitmask_isbitset(mask, j)) {
//         printf("%d ", j);
//       }
//     }
//     printf("\n");
//     numa_bitmask_free(mask);
//   }
//   // 释放NUMA库资源
//   // numa_exit();
// }