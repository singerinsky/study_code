#include "../header.h"
#include <tuple>
#include <type_traits>

template <typename... T> void test_tuple(std::tuple<T...> &tmp) {
  LOG(INFO) << "tuple size is "
            << (std::tuple_size<
                   typename std::remove_reference<decltype(tmp)>::type>::value);
}

TEST(TestStd, test_tuple) {
  std::tuple<int, int> two_int = {1, 2};
  test_tuple(two_int);
}
