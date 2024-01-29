#ifndef B6916E12_CA0F_4E45_A060_B0AE19C7CF62
#define B6916E12_CA0F_4E45_A060_B0AE19C7CF62
#include <string>
#include <vector>
using namespace std;

//输出n对括号的所有组合
vector<string> generate_kuohao(int n);

//回溯算法
void kuohao_backtrack(vector<string> &res, string &cur, int left, int right);

#endif /* B6916E12_CA0F_4E45_A060_B0AE19C7CF62 */
