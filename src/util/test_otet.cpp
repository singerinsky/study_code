#include "../header.h"
#include "class_sample.h"
#include "octet.h"
#include <gtest/gtest.h>
#include "../cpp_proto/message.pb.h"

TEST(OtectTest,test_01)
{
    int size  = 1024;
    Octets octets(size);
    char buff[256];
    for(int i = 0;i<256;i++)
    {
        buff[i] = i;
    }
    octets.assign(buff, 256);
}

TEST(OtectTest,test_02)
{
    ClassWithData data[10];
    ClassWithData* pdata = &data[0];
    ClassWithData* pNext = pdata+1;
    ASSERT_EQ(pNext, &data[1]);
    ASSERT_EQ(++pNext,&data[2]);
    LOG(INFO)<<pNext<<":"<<&data[2];
}

TEST(OtectTest,test_03)
{
    gl::user user_data;
    user_data.set_age(100);
    user_data.set_name("name");
    Octets octets;
    octets.resize(user_data.ByteSizeLong());
    user_data.SerializePartialToArray(octets.begin(),user_data.ByteSizeLong());
    gl::user new_data;
    new_data.ParseFromArray(octets.begin(), octets.size());
    LOG(INFO)<<"after decodeing "<<new_data.name()<<":"<<new_data.age()<<" datalength:"<<user_data.ByteSizeLong();
    LOG(INFO)<<"octets size "<<octets.size();
}