#ifndef A13B142C_9108_4EA0_8FA3_F19BD411B1172
#define A13B142C_9108_4EA0_8FA3_F19BD411B1172

#include <iostream>

template <class T> void test_split_define(T *t);
template <class T> void test_split_define(const T &t);
template <> void test_split_define(const std::string &t);
template <> void test_split_define(const int &t);
void test_reachable();
#endif /* A13B142C_9108_4EA0_8FA3_F19BD41B1172 */
