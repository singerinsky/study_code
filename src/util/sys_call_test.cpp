#include "../header.h"
#include <sys/random.h>

int get_my_time();

TEST(Sys,hook)
{
    auto value = time(NULL);
    LOG(INFO)<<"after hook"<<value;
    LOG(INFO)<<"after hook"<<get_my_time();
}


#define BUFF_SIZE 16

TEST(Sys,random) {
    unsigned char buff[BUFF_SIZE];
    ssize_t ret = getrandom(buff, sizeof(buff), GRND_RANDOM);
    
    if (ret == -1) {
        LOG(ERROR)<<("Failed to generate random data");
        exit(1);
    }
    
    for (int i = 0; i < BUFF_SIZE; i++) {
        LOG(INFO)<<("%02x ", buff[i]);
    }
    LOG(INFO)<<("\n");
}
