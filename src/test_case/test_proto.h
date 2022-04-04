#ifndef E498981F_AA78_4A5E_8801_11A04C9C2836
#define E498981F_AA78_4A5E_8801_11A04C9C2836
#include "../header.h"
#include "message.pb.h"


void save_data_to_file(const gl::user& user_data,std::string& file_name);

void read_data_from_file(gl::user& user_data,const std::string& file_name);

gl::user create_test_data();


#endif /* E498981F_AA78_4A5E_8801_11A04C9C2836 */
