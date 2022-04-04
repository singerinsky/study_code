#include "../header.h"

using key_t = int;
const char* GetShmByKey(key_t shm_key, int &shm_id, size_t shm_size,
                          bool &already_exist, bool is_create) {
  if (-1 == shm_key ) {
    LOG(ERROR)<<"GetShmByKey:shm_key is error! key = "<<shm_key;
    return NULL;
  }
  already_exist = false;
  shm_id = -1;
  char *shm_head = NULL;

  shm_id = shmget(shm_key, shm_size, 0666);
  if (-1 == shm_id) {
    if (ENOENT == errno) {
      // shm不存在
      already_exist = false;
      if (false == is_create) {
        return NULL;
      }
      shm_id = shmget(shm_key, shm_size, 0666 | IPC_CREAT);
      if (-1 == shm_id) {
        LOG(ERROR)<<"shmget shmid: "<<strerror(errno);
        return NULL;
      }
      LOG(INFO)<<"shmget key:"<<shm_key<<" shmid:"<<shm_id;
    } else {
      //其他的错误
      LOG(ERROR)<<"shmget shmid "<<shm_id<<" error"<<strerror(errno);
      return NULL;
    }
  } else {
    // shm已经存在了
    already_exist = true;
  }

  shm_head = reinterpret_cast<char *>(shmat(shm_id, NULL, 0));
 if (reinterpret_cast<char *>(-1) == shm_head) {
    LOG(ERROR)<<"shmat return "<<strerror(errno);
    return NULL;
  }
  return shm_head;
}
