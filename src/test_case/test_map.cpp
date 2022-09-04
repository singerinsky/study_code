#include <climits>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <unistd.h>
#include <algorithm>
#include "../header.h"
using namespace std;
//https://zhuanlan.zhihu.com/p/38733835

const std::vector<int>& get_vec(){
    return {};
}

void decode_server_id(uint64_t server_id)
{
    int zone_id = server_id>>32;
    int server_type = (server_id&0x00000000FFFF0000)>>16; 
    int id_server = server_id&0x000000000000FFFF;
    std::cout<<"zone_id"<<zone_id<<"server_type"<<server_type<<" id "<<id_server<<endl;
}


int main_one()
{
    auto i = (time(NULL));
    std::cout<<"after "<<i<<endl;
    int array[] = {1,2};
    decode_server_id(7052336562177);
    decode_server_id(4604205203457);
    return 1;
}

class clswithmap
{
public:
    clswithmap()
    {
        for(int i =0;i<10000;i++){
            _map[i] = i;
        }
    }
    std::map<int,int> _map;
};

class clswithhashmap
{
public:
    clswithhashmap()
    {
        for(int i =0;i<50000;i++){
            _map[i] = i;
        }
    }
    std::unordered_map<int,int> _map;
};

TEST(Test_Map,Test001)
{
    //clswithmap* pmap = new clswithmap();
    //printf("%d\n",sizeof(*pmap));
    //clswithhashmap* phashmap = new clswithhashmap();
    //printf("%d",sizeof(*phashmap));
    int i = 0;
    while(i < 5)
    {
        sleep(1);
        clswithmap* pmap = new clswithmap();
        i++;
    }
    auto generate_func = [](){
        return 1;
    };
    std::vector<int> data_to_fill(5);
    std::generate(data_to_fill.begin(),data_to_fill.end(),generate_func);
    for(auto i:data_to_fill)
    {
        printf("%d\n",i);
    }

}
