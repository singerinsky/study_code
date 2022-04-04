#ifndef __TEST_STD_H__
#define __TEST_STD_H__

#include "../header.h"
#include "test_template.h"
#include <initializer_list>
#include <mutex>
#include "../util/class_sample.h"
TEST(BaseTest,test_std_parition)
{
    std::vector<int> vec_value = {1,2,34,4,5,6,7};
    std::partition(vec_value.begin(),vec_value.end(),[](const auto& itr){
           return itr>=5; 
    });
    for_each(vec_value.begin(),vec_value.end(),[](auto& itr){
        LOG(INFO)<<itr;
    });

}

TEST(BaseTest,test_std_string)
{
    std::string name = "123456789";
    name = "123";
    name.reserve(1);
    LOG(INFO)<<name;
}

long long ustime(void) {
    struct timeval tv;
    long long ust;

    gettimeofday(&tv, NULL);
    ust = ((long long)tv.tv_sec)*1000000;
    ust += tv.tv_usec;
    return ust;
}

TEST(BaseTest,test_mstime)
{
    long long ms = ustime();
    LOG(INFO)<<ms;
}

template<class T>
void param_call(T&& t)
{
    LOG(INFO)<<t;
}

void param_call(const char* str)
{
    LOG(INFO)<<"call param!";
}


void param_call(std::string str)
{
    LOG(INFO)<<"call param!";
}

void param_call(SampleClass&& obejct)
{
    LOG(INFO)<<"call param &&!";
}

template<typename T,typename ...ArgPacks>
void function_params(T&& t,ArgPacks&& ... args)
{
    LOG(INFO)<<"1";
    (void)std::initializer_list<int>{(param_call(std::forward<ArgPacks>(args)),0) ...};
}

TEST(BaseTest,test_initlizelist)
{
    SampleClass object{1};
    function_params(1,"string",3,4,5,6,std::move(object));
}

const std::string& get_const_string()
{
    std::string temp= "name";
    return temp;
}

std::optional<std::string> get_ref_optional()
{
    std::string name = "guanlei";
    if(true)
    return {name};
    else
        return nullopt;
}

std::string get_ref_string()
{
    std::string temp= "name";
    return temp;
}
SampleClass get_sample_class_with_rvo()
{
   SampleClass object(1);
   return object;
}

//多个分支返回不同的局部对象，就无法优化
SampleClass get_sample_class_without_nrvo()
{
    SampleClass object;
    if(time(nullptr)/2 == 0)
      object.SetId(1);
      else {
          SampleClass object1;
          return object1;
      }
    return object;
}

//可以优化
SampleClass get_sample_class_with_nrvo()
{
    SampleClass object;
    if(time(nullptr)/2 == 0)
      object.SetId(1);
      else {
          return object;
      }
    return object;
}

void scope_class_function()
{
    struct __struct_tmp_{
        ~__struct_tmp_(){
            LOG(INFO)<<"release scope class!";
        }
    }scope_object;
}

template<class T>
void test_right(T&& i)
{
    LOG(INFO)<<i;
    i = i*2;
}

template<class T>
void test_right_1(T&& i)
{
    test_right(std::forward<T>(i));
}

TEST(BaseTest,scope_test)
{
    //scope_class_function();
    int i = 0;
    test_right(i);
    test_right_1(1);
    float j = 1.0f;
    float& ref  = j;
    test_right_1(ref);
    LOG(INFO)<<ref;
}

#include <list>
//测试std::optional 和rvo nrvo
TEST(BaseTest,test_ref_return)
{
    std::string ref = std::move(get_ref_string());
    const std::string& const_ref = get_ref_string();
    auto rst = get_ref_optional();

//    const SampleClass& object = get_sample_class();

    //rvo 优化
    {
        SampleClass object_rvo = get_sample_class_with_rvo();
    }
    LOG(INFO)<<"...................................with nrvo";
    //直接nrvo优化
    {
    SampleClass object = get_sample_class_with_nrvo();
    }
    LOG(INFO)<<"...................................";
    {
        SampleClass object1  = get_sample_class_without_nrvo();
    }
    LOG(INFO)<<"...................................";
    {
        //decltype(SampleClass())::value_type t;
    }
    LOG(INFO)<<"................................... with rvo";
    ClassWithFunctionReturnObject object;
    SampleClass object_return = object.GetObject();

    std::queue<int,std::list<int>> queue_int;

}

int partition(int arr[], int left, int right)  //找基准数 划分 
{     
int i = left;     
int j = right;     
int temp = arr[left];     
 while(i <= j)     
 {        
   while (arr[j] > temp && j >= i)         
    {          
        j--;        
    }       
    arr[left] = arr[j];
    while (arr[i] < temp && i <= j)         
    {           
        i++;         
    }         
    arr[j] = arr[i];
 }    
 swap(arr[j], arr[left]);   
 return j;  
} 
void quick_sort(int arr[], int left, int right)  {    
 if (left > right)         
    return;    
 int j = partition(arr, left, right);    
 quick_sort(arr, left, j - 1);     
 quick_sort(arr, j + 1, right); 
} 

#endif // __TEST_STD_H__