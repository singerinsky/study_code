#include "../header.h"
#include <optional>

template <class T> void make_heap(std::vector<T> &vec, int l) {
  int largest = l;
  int left = 2 * largest + 1;
  int right = 2 * largest + 2;

  if (left < vec.size() && vec[left] > vec[largest]) {
    largest = left;
  }

  if (right < vec.size() && vec[right] > vec[largest]) {
    largest = right;
  }

  if (largest != l) {
    std::swap(vec[largest], vec[l]);
    make_heap(vec, largest);
  }
}

void buildHeap(std::vector<int> &arr) {
  int n = arr.size();

  for (int i = n / 2 - 1; i >= 0; i--) {
    make_heap(arr, i);
  }
}
static int layout = 0;
template <class T> void TraversalHeap(std::vector<T> &heap, int nStart) {
  int nleft = nStart * 2 + 1;
  int nright = nStart * 2 + 2;
  if (nStart < heap.size()) {
    LOG(INFO) << "layout:" << layout << ":" << heap[nStart];
    layout++;
  }
  if (nleft < heap.size()) {
    TraversalHeap(heap, nleft);
  }
  if (nright < heap.size()) {
    TraversalHeap(heap, nright);
  }
  layout--;
}

TEST(AlgorithmTest, test_heap) {
  std::vector<int> arr = {9, 2, 5, 7, 1, 6, 3};

  // 构建最大堆
  buildHeap(arr);

  // 输出构建后的堆
  LOG(INFO) << "Max heap: ";
  for (const auto &num : arr) {
    LOG(INFO) << num << " ";
  }
  LOG(INFO) << "starting traversal....";
  TraversalHeap(arr, 0);
}