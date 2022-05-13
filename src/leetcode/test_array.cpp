#include "../header.h"
#include <algorithm>
#include <array>

const std::array<int, 10> const_int_array = {1,  2, 34, 4,  455,
                                             34, 2, 90, 89, 3};

template <int ArraySize, class T, class elefunc>
std::array<T, ArraySize> build_array_sort(elefunc &func) {
  std::array<T, ArraySize> _array;

  for (auto &ele : _array) {
    ele = func();
  }
  std::sort(_array.begin(), _array.end());
  return _array;
}

int generate_random() {
  int data = rand() % 100;
  LOG(INFO) << "rand value" << data;
  return data;
}

//判断重复元素
bool containsDuplicate(vector<int> &nums) {
  int index = 0;
  int totoalsize = nums.size();
  if (totoalsize <= 1)
    return false;
  if (totoalsize == 2)
    return nums[0] == nums[1];

  int fastindex = (index + 2) % totoalsize;
  while (index != fastindex) {
    LOG(INFO) << "compare " << index << ":" << fastindex;
    if (nums[index] == nums[fastindex])
      return true;
    index = (index + 1) % totoalsize;
    fastindex = (fastindex + 2) % totoalsize;
  }
  return false;
}

TEST(Test_Array, array_unique) {
  srand(time(NULL));
  auto data = build_array_sort<10, int>(generate_random);
  int index = 0;
  for (auto &ele : data) {
    LOG(INFO) << "index " << index << ":" << ele;
    index++;
  }

  for (int i = 0; i < data.size(); i++) {
    for (int j = i + 1; j < data.size(); j++) {
      if (data[i] == data[j] && data[j] != -1) {
        LOG(INFO) << "data[" << i << "] == data[" << j << "]";
        data[j] = -1;
      }
    }
  }

  for (auto &ele : data) {
    LOG(INFO) << ele;
  }
}

TEST(Test_Array, array_duplicate) {
  std::vector<int> vec = {1, 2, 3, 4, 1};
  containsDuplicate(vec);
}

class TestRepeated
{
public:
    TestRepeated(){
        _value[0]=0;
        _value[1]=1;
        _value[2]=2;
        _value[3]=3;
        _value[4]=4;
        _value[5]=5;
        _value[6]=6;
        _value[7]=7;
        _value[8]=8;
        _value[9]=9;
    }
    using iterator=int*;
    iterator begin(){
        return _value;
    }
    iterator end(){
        return _value+10;
    }
private:
    int _value[10];
};

TEST(Test_Array,itr)
{
    TestRepeated repeated;
    for(auto i :repeated){
        LOG(INFO)<<i;
    }

}



