#ifndef D3BCBBF1_AD93_4EFA_B39B_54F0788B8486
#define D3BCBBF1_AD93_4EFA_B39B_54F0788B8486
#include <cstdint>
struct MsgHead {
  uint32_t dwMsgID;
  uint32_t dwMsgLen;
};

#define MSG_HEAD_SIZE sizeof(MsgHead)

#endif /* D3BCBBF1_AD93_4EFA_B39B_54F0788B8486 */
