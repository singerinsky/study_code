#include "test_stack.h"
#include "../header.h"

void test_stack1() {
  WS_STACK_TRACK_ENQUEUE
  std::cout << "call test_stack1" << endl;
  assert(false);
}

void test_stack2() {
  test_stack1();
  WS_STACK_TRACK_ENQUEUE
  std::cout << "call test_stack2" << endl;
}

TEST(StackTest, test1) {
  WS_STACK_TRACK_ENQUEUE
  test_stack2();
  std::cout << "call StackTest" << endl;
  ASSERT_EQ(true, true);
}

void function_call(int index_dep, int &dep_rst) {
  dep_rst++;
  LOG(INFO) << "......" << dep_rst << " index_dep " << index_dep;
  if (index_dep == 2 || index_dep == 1 || index_dep == 0)
    return;
  function_call(index_dep / 2, dep_rst);
}

TEST(StackTest, test_function_1) {
  int dep_length = 0;
  function_call(100, dep_length);
  LOG(INFO) << "value 100 with dep :" << dep_length;
}

template <class T>
void PopStackFrame(std::vector<T> &vec, std::vector<T> &newVec) {
  if (vec.size() == 0) {
    return;
  } else {
    size_t dwFirstIndex = vec.size() - 1;
    T t = vec[dwFirstIndex];
    vec.pop_back();
    newVec.push_back(t);
    PopStackFrame(vec, newVec);
    // newVec.push_back(t);
    return;
  }
}

TEST(StackTest, test_resverse) {
  std::vector<int> vec = {1, 2, 3, 4};
  std::vector<int> newVec;
  PopStackFrame<int>(vec, newVec);
  EXPECT_EQ(newVec.size(), 4);
  EXPECT_EQ(newVec[0], 4);
  EXPECT_EQ(newVec[1], 3);
  EXPECT_EQ(newVec[2], 2);
  EXPECT_EQ(newVec[3], 1);
}
