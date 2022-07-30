#include "test_algorithm.h"
#include <algorithm>
#include <gtest/gtest.h>
#include <string>
#include <vector>

int calc_coin(std::vector<int> &coin_type, int remain_value) {
  LOG(INFO) << "remain value " << remain_value;
  if (remain_value == 0) {
    return 0;
  }

  if (std::find(coin_type.begin(), coin_type.end(), remain_value) !=
      coin_type.end()) {
    return 1;
  } else {
    int closest_index = -1;
    for (int index = 0; index < coin_type.size(); index++) {
      if (coin_type[index] > remain_value) {
        if (index == 0) {
          LOG(INFO) << "data " << index << ":" << remain_value;
          assert(false);
        }
        closest_index = index - 1;
        LOG(INFO) << "step " << closest_index << ":" << remain_value;
        break;
      }
    }

    if (closest_index == -1) {
      closest_index = coin_type.size() - 1;
    }
    std::vector<int> count_vec;
    for (int start = 0; start <= closest_index; start++) {
      count_vec.push_back(
          1 + calc_coin(coin_type, remain_value - coin_type[start]));
    }
    std::sort(count_vec.begin(), count_vec.end());
    LOG(INFO) << "begin....";
    for (auto i : count_vec) {
      LOG(INFO) << "---->" << i;
    }
    return count_vec[0];
  }
}

TEST(BaseTest, coin) {
  std::vector<int> coin_type = {1, 3, 5};
  int rst = calc_coin(coin_type, 23);
  LOG(INFO) << "result is " << rst;
}

void dump_vector(std::vector<int> &vec, int row, int col) {
  LOG(INFO) << "............................";
  for (int i = 0; i < col; i++) {
    std::string string_row;
    for (int j = 0; j < col; j++) {
      string_row.append(std::to_string(vec[i * col + j]));
      string_row.append(" ");
    }
    LOG(INFO) << string_row;
  }
}

std::vector<int> generat_from_array(int row, int col) {
  std::vector<int> vec_mth;

  std::vector<int> vec_mth_after_rotate;
  vec_mth_after_rotate.resize(row * col);
  vec_mth.resize(row * col);
  // pick row
  int row_index = std::rand() % col;
  for (int i = 0; i < col; i++) {
    vec_mth[row_index * col + i] = 1;
    vec_mth_after_rotate[i * col + row_index] = 1;
  }

  for (int i = 0; i < col; i++) {
    //随机的那一行不用判断
    if (i == row_index) {
      continue;
    }
    int zero_flag = false;
    for (int j = 0; j < row; j++) {
      int _tmp = std::rand() % 2;
      //这一行，最后一个元素，判断是否全是1,如果全部是1，要强制给0
      if (j == row - 1) {
        if (zero_flag == false) {
          vec_mth[col * i + j] = 0;
        } else {
          vec_mth[col * i + j] = _tmp;
        }
      } else {//已经出现过0，直接用随机数即可
        vec_mth[col * i + j] = _tmp;
        if(_tmp == 0)
        {
          zero_flag = true;
        }
      }
    }
  }
  //检查列
  for (int i = 0; i < row; i++) {
    std::vector<int> index_vec;
    bool zero_flag = false;
    for (int j = 0; j < col; j++) {
      if(j == row_index)
        continue;
      if (vec_mth[j * row + i] == 0) {
        zero_flag = true;
      }else{
        index_vec.push_back(j*row+i);
      }
    }

    if(zero_flag == false)
    {
      std::random_shuffle(index_vec.begin(),index_vec.end());
      vec_mth[index_vec[0]] = 0;
    }
  }

  //翻转
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      vec_mth_after_rotate[i* col + j] = vec_mth[j *col +i];
    }
  }

  //检查左对角线
  /**
  std::vector<int> left_vec;
  bool zero_flag = false;
  for (int i = 0; i < row; i++) {
    if(vec_mth_after_rotate[i + row*i] == 0)
    {
      zero_flag = true;
    }else{
      left_vec.push_back(i+row*i);
    }
  }
  **/
  dump_vector(vec_mth, 5,5);
  dump_vector(vec_mth_after_rotate, 5, 5);
  return vec_mth;
}
std::vector<std::vector<bool>> generate_mat(int size) {
  std::vector<std::vector<bool>> vec_math;
  vec_math.resize(size);
  for (auto &itr : vec_math) {
    itr.resize(size);
    std::fill(itr.begin(), itr.end(), 1);
  }
  //两种生成方式，因为是正方形矩阵。所以可以用一维数组只有一段row长度的连续1来表示，生成之后再反转
  //

  return vec_math;
}

TEST(BaseTest, generate_mat) {
  auto math = generate_mat(5);
  for (int index = 0; index < math.size(); index++) {
    std::string row_str;
    std::for_each(math[index].begin(), math[index].end(), [&](auto value) {
      row_str.append(std::to_string(value));
      row_str.append("-");
    });
    LOG(INFO) << row_str;
  }
  std::srand(std::time(nullptr));
  generat_from_array(5, 5);
  // int name[3][3] = {{1, 1, 1}, {2, 2, 2}, {3, 3, 3}};
  // LOG(INFO) << name[0][0] << " " << name[0][1] << " " << name[0][2];
}

void other_generate_function(int size)
{
  std::srand(std::time(nullptr));
  std::vector<int> vec_mth;
  vec_mth.resize(size* size);
  for (int i = 0; i < size ; i++) {
    for (int j = 0; j < size ; j++) {
        vec_mth[i*size + j] = std::rand()%2;
    }
  }

  //随机方式
  int generate_type = std::rand()%4;  
  std::vector<int> index;
  //LOG(INFO)<<generate_type;
 // generate_type = 1;
  LOG(INFO)<<generate_type;
  if(generate_type == 0) 
  {
    for (int i = 0; i < size; i++) {
      index.push_back( i * size+i);
      vec_mth[i*size + i] = 1;
    }
  }else if(generate_type == 1)
  {
    for (int i = size; i >0; i--) {
      index.push_back( ( size - 1) * i);
      vec_mth[ (i * size - i) ] = 1;
    }
  }else if(generate_type == 2)
  {
    int col = std::rand()%size;
    for (int i = 0; i < size; i++) {
      index.push_back(i * size + col);
      vec_mth[i * size + col] = 1;
    }
  }else if(generate_type == 3)
  {
    int row = std::rand() % size;
    for (int i = 0; i < size; i++) {
      index.push_back(row * size + i);
      vec_mth[row * size + i] = 1;
    }
  }

  dump_vector(vec_mth,4,4);
  //check row
  for(int i =0;i<size;i++)
  {
    bool zero_flag = false;
    bool is_math_result = true;
    std::vector<int> to_fix;
    for (int j = 0; j < size; j++)
    {
      if(vec_mth[i*size+j] ==0)
      {
        zero_flag = true;
        is_math_result = false;
        break;
      }
      if(std::find(index.begin(),index.end(),(i*size+j)) == index.end())
      {
        is_math_result = false;
        to_fix.push_back(i*size+j);
      }
    }
    if(zero_flag == false && is_math_result == false)
    {
        std::random_shuffle(to_fix.end(),to_fix.end());
        vec_mth[to_fix[0]] = 0;
    }
  }

  //check col
  for(int i =0;i<size;i++)
  {
    bool zero_flag = false;
    bool is_math_result = true;
    std::vector<int> to_fix;
    for (int j = 0; j < size; j++)
    {
      int value = j*size + i;
      if(vec_mth[value] ==0)
      {
        zero_flag = true;
        is_math_result = false;
        break;
      }
      if(std::find(index.begin(),index.end(),value) == index.end())
      {
        is_math_result = false;
        to_fix.push_back(value);
      }
    }
    if(zero_flag == false && is_math_result == false)
    {
        std::random_shuffle(to_fix.end(),to_fix.end());
        vec_mth[to_fix[0]] = 0;
    }
  }

  // check cornor
  {
    bool zero_flag = false;
    bool is_math_result = true;
    std::vector<int> to_fix;

    for (int i = 0; i < size; i++) {
      int value_index = i * size + i;
      if (vec_mth[value_index] == 0) {
        zero_flag = true;
        is_math_result = false;
        break;
      }
      if (std::find(index.begin(), index.end(), value_index) == index.end()) {
        is_math_result = false;
        to_fix.push_back(value_index);
      }
    }
    if (zero_flag == false && is_math_result == false) {
      std::random_shuffle(to_fix.end(), to_fix.end());
      vec_mth[to_fix[0]] = 0;
    }
  }
  {
    bool zero_flag = false;
    bool is_math_result = true;
    std::vector<int> to_fix;

    for (int i = 0; i < size; i++) {
      int value_index = (size - 1)*size + 1+i;
      if (vec_mth[value_index] == 0) {
        zero_flag = true;
        is_math_result = false;
        break;
      }
      if (std::find(index.begin(), index.end(), value_index) == index.end()) {
        is_math_result = false;
        to_fix.push_back(value_index);
      }
    }
    if (zero_flag == false && is_math_result == false) {
      std::random_shuffle(to_fix.end(), to_fix.end());
      vec_mth[to_fix[0]] = 0;
    }
  }
  dump_vector(vec_mth, 4,4);
}


TEST(TestBase, generator_other)
{
  other_generate_function(4);
}

//thread_local static int age;




