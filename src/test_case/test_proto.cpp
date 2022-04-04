#include "test_proto.h"
#include "message.pb.h"
#include <fstream>

void save_data_to_file(gl::user& user_data,std::string& file_name)
{
    std::ofstream stream;    
    stream.open(file_name.c_str(),ios::binary);
    if(!stream.is_open())
    {
        LOG(INFO)<<"open file "<<file_name<<" failed!";
        assert(false);
        return;
    }

    user_data.SerializeToOstream(&stream);
    stream.close();
}

void read_data_from_file(gl::user& user_data,const std::string& file_name)
{
    std::ifstream stream;
    stream.open(file_name.c_str(),ios::binary);
    if(!stream.is_open())
    {
        LOG(INFO)<<"open file "<<file_name<<" failed!";
        assert(false);
        return;
    }
   
    if(!user_data.ParseFromIstream(&stream)){
        LOG(INFO)<<"parse data from file failed!";
    }
    LOG(INFO)<<"read data from file ,user data"<<user_data.age();//.name();
    stream.close();
}

gl::user create_test_data()
{
    gl::user user_data;
    user_data.set_age(88);
    user_data.set_name("guanlei");
    return user_data;
}

TEST(BaseTest,pb_wr_file)
{
    gl::user user_data;
    user_data.set_age(37);
    user_data.set_name("guanlei");
    std::string file_name = "user_data.bin";
    save_data_to_file(user_data, file_name);
    gl::user new_data;
    read_data_from_file(new_data, file_name);
}
