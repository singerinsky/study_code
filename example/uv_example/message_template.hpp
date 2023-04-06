#ifndef AA4190D0_BCDE_430B_9D80_4FAFAE416A70
#define AA4190D0_BCDE_430B_9D80_4FAFAE416A70

#include "../../message_include/message.pb.h"
#include "glog/logging.h"
#include <cstdint>
#include <google/protobuf/stubs/port.h>
#include <sys/types.h>
#include <type_traits>
#include <unordered_map>

class MessageBase {
public:
  virtual ~MessageBase() {}
  virtual bool ParseFromArray(uint32_t dwMsgType, const char *buffer,
                              uint32_t size) = 0;
};

template <int MSG_TYPE, typename T> class MessageTemplate : public MessageBase {
public:
  typedef T DataType;
  typedef MessageTemplate<MSG_TYPE, T> SelfClassType;
  bool ParseFromArray(uint32_t dwMsgType, const char *buffer,
                      uint32_t size) override {
    LOG(INFO) << "parse from origin";
    _msgType = dwMsgType;
    bool rst = _data.ParseFromArray(buffer, size);
    return rst;
  }

  int _msgType;
  T _data;
};

class UserInfoClass : public MessageTemplate<1, gl::CSRequireLogin> {};

template <typename T> struct is_derived_from_message_base {
  static constexpr bool value = std::is_base_of<MessageBase, T>::value;
};

template <typename T>
using EnableIfDerivedFromMessageBase =
    typename std::enable_if<is_derived_from_message_base<T>::value>::type;

template <class T, typename = EnableIfDerivedFromMessageBase<T>>
class MessageObjectTypeWrapper {
  typedef T MessageType;
};

template <>
class MessageObjectTypeWrapper<MessageTemplate<1, gl::CSRequireUserInfo>>;
using myclass =
    MessageObjectTypeWrapper<MessageTemplate<1, gl::CSRequireUserInfo>>;

template <>
class MessageObjectTypeWrapper<MessageTemplate<3, gl::CSRequireLogin>>;
using myclass1 =
    MessageObjectTypeWrapper<MessageTemplate<3, gl::CSRequireLogin>>;

MessageBase *AllocNewMessage(uint32_t dwMsgType);

#endif /* AA4190D0_BCDE_430B_9D80_4FAFAE416A70 */
