#include "../header.h"
#include <initializer_list>
#include <stdexcept>
#include <system_error>
#include <tuple>
#include <type_traits>

template <typename... T> void test_tuple(std::tuple<T...> &tmp) {
  LOG(INFO) << "left value tuple size is "
            << (std::tuple_size<
                   typename std::remove_reference<decltype(tmp)>::type>::value);
}

template <typename... T> void test_tuple(std::tuple<T...> &&tmp) {
  LOG(INFO) << "right value tuple size is "
            << (std::tuple_size<
                   typename std::remove_reference<decltype(tmp)>::type>::value);
}

template <int index, typename T>
constexpr auto get_initlist_ele(std::initializer_list<T> &tmp) {
  // static_assert(index < sizeof...(T));
  LOG(INFO) << sizeof(tmp);
  static_assert(index < sizeof(tmp));
  return *(tmp.begin() + index); /* return (index < tmp.size())
              ? *(tmp.begin() + index)
              : (throw std::logic_error("get index must less than size"));*/
}

template <typename... T> void test_initlist(std::initializer_list<T...> &&tmp) {
  LOG(INFO) << "right value tuple size is " << tmp.size()
            << "element in list:" << *(tmp.begin() + 3);
}

TEST(TestStd, test_tuple) {
  std::tuple<int, int> two_int = {1, 2};
  test_tuple(two_int);
  auto auto_int = {1, 2, 4, 4};
  test_initlist(std::move(auto_int));
  auto i = 0;
  auto j = 0;
  // std::tie(i,j) = two_int;
  LOG(INFO) << std::get<0>(two_int); //.get(1);
  auto result = get_initlist_ele<10>(auto_int);
  LOG(INFO) << "result find in initlizelist " << result;
  LOG(INFO) << "main change" << result;
}

TEST(TestStd,test_map_remove)
{
    std::map<int,int> int_map = {{1,2},{2,3},{3,4}};
    auto itr = int_map.begin();
    while(itr != int_map.end()){
        if(itr->second == 3){
            int_map.erase(itr++);
        }else{
            itr++;
        }
    }
    LOG(INFO)<<"test"<<int_map.size();


    std::vector<int> vec = {1,2,3,4,5,6};
    auto itr_vec = vec.begin();
    while(itr_vec != vec.end()){
        if(*itr_vec == 2){
            itr_vec = vec.erase(itr_vec);
        }else{
            itr_vec++;
        }
    }

    LOG(INFO)<<"vec test"<<vec.size();

}


//结论：std::initialzer_list
//本质和数组差不多，而且也是只能用同一种类型，不可以放入多个类型。在编译期无法得知其size，所以无法使用static_assert判断越界,而使用std::get<>
