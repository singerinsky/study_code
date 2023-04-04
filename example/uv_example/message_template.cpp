#include "message_template.hpp"
#include <unordered_map>

static std::unordered_map<uint32_t, MessageBase *> g_message_map;

// template <> class MessageTemplate<1, gl::CSRequireUserInfo>;

static void register_message_builder() {}

MessageBase *AllocNewMessage(uint32_t dwMsgType) {
  switch (dwMsgType) {
  case 1:
    return new UserInfoClass;
    break;

  default:
    return nullptr;
  }
}
