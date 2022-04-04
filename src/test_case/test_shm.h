#ifndef __TEST_SHM_H__
#define __TEST_SHM_H__

#include "../header.h"
#include "../shmmgr.h"
#include "../util/shm_util.h"
#include <cstdlib>
#include <gtest/gtest.h>

const int shm_str_handle = 1;
const int shm_pod_handle = 2;
const int shm_object_struct_handle = 3;

struct ShmInfoBlock
{
  int id_ = 0;
  int type_= 0;
  int size_ = 0;
};

class PodSampleManager
{
public:
  bool Init()
  {
    //TODO read data from shm 
    return true;
  }

  static PodSampleManager& Instance()
  {
    static PodSampleManager instance;
    return instance;
  }

  bool InitObjectStoreInShm()
  {
    void *shm_ptr;
    int size = sizeof(ShmInfoBlock) + 10 * sizeof(PodSampleClass);
    EWSShmErrCode code = WS_CreateShm(shm_object_struct_handle, size, &shm_ptr);
    if (code != WS_SUCCESS && code != WS_SHM_ALREADY_EXISTS) {
      LOG(ERROR) << "create shm failed! failed reason" << code;
      return false;
    }

    block_info = reinterpret_cast<ShmInfoBlock*>(shm_ptr);
    all_pod = reinterpret_cast<PodSampleClass*>(block_info + 1);
    if(code == WS_SHM_ALREADY_EXISTS)
    {
      for(int index = 0; index < block_info->size_ && index < 10; index++)
      {
        LOG(INFO) << "object info in shm " << all_pod[index].id_;
      }
      if(block_info->size_ < 10)
      {
         all_pod[block_info->size_].id_ = 1000+ block_info->size_;
         block_info->size_++ ;
      }
    } else {
      all_pod[0].id_ = 1999;
      block_info->size_ = 1;
    }
    return true;
  }

    int             object_size;
    PodSampleClass  *all_pod;
    ShmInfoBlock    *block_info;
};


TEST(ShmTest, test_1) {
  void *shm_ptr;
  int size = 100;

  void *shm_item_ptr = nullptr;
  EWSShmErrCode code = WS_CreateShm(shm_str_handle, size, &shm_ptr);
  if (code != WS_SUCCESS && code != WS_SHM_ALREADY_EXISTS) {
    LOG(ERROR) << "create shm failed! failed reason" << code;
    ASSERT_TRUE(false);
    return;
  }
  char mem_content[100] = {0};
  memcpy(mem_content, shm_ptr, 100);
  LOG(INFO) << mem_content;
  snprintf(mem_content, 100, "nice %ld", time(nullptr));
  memcpy(shm_ptr, mem_content, 100);
}

TEST(ShmTest, test_str) {
  std::string test_str = R"(c:\\programfiles)";
  LOG(INFO) << test_str;
}

TEST(ShmTest, test_pod) {
  void *shm_ptr;
  int size = sizeof(PodSampleClass) * 10;
  EWSShmErrCode code = WS_CreateShm(shm_pod_handle, size, &shm_ptr);
  if (code != WS_SUCCESS && code != WS_SHM_ALREADY_EXISTS) {
    LOG(ERROR) << "create shm failed! failed reason" << code;
    ASSERT_TRUE(false);
    return;
  }

  PodSampleClass *p_pod = nullptr;
  if (code != WS_SHM_ALREADY_EXISTS) {
    LOG(INFO) << "init shm first time!";
    p_pod = static_cast<PodSampleClass *>(shm_ptr);
    for (int index = 0; index < 10; index++) {
      (p_pod + index)->id_ = index;
    }
  }
   p_pod = static_cast<PodSampleClass*>(shm_ptr);
  for (int index = 0; index < 10; index++) {
    LOG(INFO) << "read object from share memory ,id :" << p_pod[index].id_;
  }
  ASSERT_TRUE(true);
}

TEST(ShmTest, test_pod_write) {
  void *shm_ptr;
  int size = sizeof(PodSampleClass) * 10;
  EWSShmErrCode code = WS_CreateShm(shm_pod_handle, size, &shm_ptr);
  if (code != WS_SUCCESS && code != WS_SHM_ALREADY_EXISTS) {
    LOG(ERROR) << "create shm failed! failed reason" << code;
    ASSERT_TRUE(false);
    return;
  }
  srand((unsigned int)time(NULL));
  PodSampleClass *p_pod = static_cast<PodSampleClass*>(shm_ptr);
  for (int index = 0; index < 10; index++) {
      p_pod[index].id_ = rand();
  }
  ASSERT_TRUE(true);
}

TEST(ShmTest, test_object_manager) {
  auto& instance = PodSampleManager::Instance();
  instance.InitObjectStoreInShm();
}


#endif // __TEST_SHM_H__