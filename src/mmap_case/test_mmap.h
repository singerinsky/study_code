#ifndef F06AD991_1473_40CE_B87D_D7845B1BBB80
#define F06AD991_1473_40CE_B87D_D7845B1BBB80

#include "../header.h"
#include "../util/class_sample.h"
#include <list>
#include <numeric>

void open_shared_mermory_by_mmap()
{
    int mmap_handler;
    mmap_handler = open("./share_memery_handler",O_RDWR|O_CREAT|O_TRUNC,0666);
    if(mmap_handler == -1)
    {
        LOG(INFO)<<"File exist!";
        mmap_handler = open("./share_memery_handler", O_RDWR|O_TRUNC,0066);
        LOG(INFO)<<"File reopen !"<<mmap_handler;
    }
    lseek(mmap_handler,sizeof(PodSampleClass)*10 -1,SEEK_SET);
    write(mmap_handler,"",1);
    PodSampleClass* p_object_in_shm = (PodSampleClass*)mmap(NULL,sizeof(PodSampleClass)*10,PROT_READ|PROT_WRITE,MAP_SHARED,mmap_handler,0);
    close(mmap_handler);
    const char* str_perperty = "hello";
    for(int i = 0;i<10;i++)
    {
        auto * temp_point = (p_object_in_shm+i);
        temp_point->id_ = i;
        strncpy(temp_point->str_value_,str_perperty,strlen(str_perperty));
        temp_point->str_value_[strlen(str_perperty)] = '\0';
    }
    munmap(p_object_in_shm,sizeof(PodSampleClass)*10);
    LOG(INFO)<<"after open";
}

void read_shared_memery_by_mmap()
{
     int mmap_handler;
    mmap_handler = open("./share_memery_handler",O_RDWR,0077);
    LOG(INFO)<<"FILE open rst "<<mmap_handler;// = open("./share_memery_handler",O_RDWR);
    if(mmap_handler == -1)
    {
        return;
    }
    PodSampleClass* p_object_in_shm = (PodSampleClass*)mmap(NULL,sizeof(PodSampleClass)*10,PROT_READ|PROT_WRITE,MAP_SHARED,mmap_handler,0);
    for(int i = 0;i<10;i++)
    {
        LOG(INFO)<<"name:"<<(p_object_in_shm+i)->str_value_;
    }
    munmap(p_object_in_shm,sizeof(PodSampleClass)*10);
}


TEST(Test_shm,test_mmap)
{
    open_shared_mermory_by_mmap();
    read_shared_memery_by_mmap();
}

TEST(Test_shm,test_string)
{
    char buff[100];
    std::string str_value = "hello";
    const char* const_str = "hello";
    LOG(INFO)<<strlen(const_str);
    LOG(INFO)<<str_value.size();
    LOG(INFO)<<str_value.length();
    strcpy(buff,const_str);
    LOG(INFO)<<strlen(buff);
    LOG(INFO)<<(buff);
    memset(buff,0,sizeof(buff));
    LOG(INFO)<<(buff);
    buff[5] = 'c';
    strncpy(buff,const_str,strlen(const_str));
    buff[strlen(const_str)] = '\0';
    LOG(INFO)<<(buff);
    memset(buff,0,sizeof(buff));
    buff[5] = 'c';
    memcpy(buff,(void*)const_str,strlen(const_str));
    LOG(INFO)<<(buff);
}

TEST(Test_shm,test_object_in_vec)
{
    /*
    std::vector<PodSampleClass> all_object_vec = {{1,2},{3,4},{5,6}};
    auto itr_0 = all_object_vec.begin();
    int value = itr_0->id_;
    for(auto& itr : all_object_vec)
    {
        LOG(INFO)<<(itr).id_;
    }
    for(auto itr : all_object_vec)
    {
        LOG(INFO)<<(itr).id_;
    }
    for(;itr_0 != all_object_vec.end(); itr_0++)
    {
        LOG(INFO)<<itr_0->id_;
    }
    for_each(all_object_vec.begin(),all_object_vec.end(),[](auto& itr){
        LOG(INFO)<<itr.id_;
    }
    );
    LOG(INFO)<<"distance between begin and end"<<std::distance(all_object_vec.begin(),all_object_vec.end());
    */
    std::vector<int> vec ={1,20,3,4,5,5};
    std::function<void(const std::string&)> name_call = [](const std::string& name){
        LOG(INFO)<<name;
    };
    std::string name = "an...";
    auto func_bind = std::bind(name_call,name);
    func_bind();

    //std::array<int,6> vec = {1,20,3,4,5,5};
    LOG(INFO)<<"distance"<<std::count(vec.begin(),vec.end(),5);
    std::make_heap(vec.begin(),vec.end());
    vec.push_back(40);
    std::push_heap(vec.begin(),vec.end(),std::less<int>());
    for(auto& itr:vec)
    {
        LOG(INFO)<<itr;
    }
    LOG(INFO)<<"top"<<vec.front();
    std::plus<float> add;
    float result = add(1.f,2.f);
    LOG(INFO)<<"............................................";
    std::vector<int> result_vec;
    result_vec.resize(vec.size());
    std::transform(vec.begin(),vec.end(),result_vec.begin(),[](auto& value)->int{return value + 1;});
    for (auto &itr : vec)
    {
        LOG(INFO)<<itr;
    }
    //float result = std::plus<float>(1.0f,1.4f);
    /*
    std::vector<std::unique_ptr<int>> vec_ptr;// ={1,2,3,4,5,5};
    auto ptr1 =std::make_unique<int>(1);
    vec_ptr.emplace_back(std::move(ptr1));
    auto ptr2 =std::make_unique<int>(2);
    vec_ptr.emplace_back(std::move(ptr2));
    auto ptr_itr = vec_ptr.begin();
    int i = **ptr_itr; 
    std::list<PodSampleClass> all_object_list = {{1,2},{3,4},{5,6}};
    */
   std::unordered_map<int,int> map_hash;
   map_hash.insert(std::make_pair<int,int>(1,2));
}


TEST(Test_shm,test_4)
{
    vector<int> v{1,3,4,5,6};
    auto result = std::accumulate(v.begin(),v.end(),0,std::plus<int>());
    LOG(INFO)<<result;
    PodSampleClass* p = new PodSampleClass();
    delete p;
    p->id_ = 11;
    LOG(INFO)<<p;
    LOG(INFO)<<p->IsValied();
}

TEST(Test_shm,test_5)
{
    PodSampleClass* p = new PodSampleClass();
    LOG(INFO)<<"size of PodSampleClass:"<<sizeof(PodSampleClass);
    LOG(INFO)<<"size of SubPodClass:"<<sizeof(SubPodClass);
    LOG(INFO)<<"size of Int :"<<sizeof(int);
}


#endif /* F06AD991_1473_40CE_B87D_D7845B1BBB80 */
