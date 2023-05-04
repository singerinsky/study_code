#ifndef E498981F_AA78_4A5E_8801_11A04C9C2836
#define E498981F_AA78_4A5E_8801_11A04C9C2836
#include "../header.h"
#include "message.pb.h"

void save_data_to_file(const gl::CSRequireUserInfo &user_data,
                       std::string &file_name);

void read_data_from_file(gl::CSRequireUserInfo &user_data,
                         const std::string &file_name);

gl::CSRequireUserInfo create_test_data();

#endif /* E498981F_AA78_4A5E_8801_11A04C9C2836 */
