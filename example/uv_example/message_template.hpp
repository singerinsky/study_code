#ifndef AA4190D0_BCDE_430B_9D80_4FAFAE416A70
#define AA4190D0_BCDE_430B_9D80_4FAFAE416A70

#include "glog/logging.h"
#include "message.pb.h"
#include <cstdint>
#include <google/protobuf/stubs/port.h>
#include <sys/types.h>

class MessageBase {
public:
  virtual bool ParseFromArray(uint32_t dwMsgType, const char *buffer,
                              uint32_t size) = 0;
  // virtual MessageBase *AllocNewMessage() = 0;
};

template <int MSG_TYPE, class T> class MessageTemplate : public MessageBase {
public:
  typedef T DataType;
  bool ParseFromArray(uint32_t dwMsgType, const char *buffer, uint32_t size) {
    LOG(INFO) << "parse from origin";
    _msgType = dwMsgType;
    return _data.ParseFromArray(buffer, size);
  }

  // MessageBase *AllocNewMessage() { return new }

  int _msgType;
  T _data;
};

template <int msgType, typename T>
class CustomizedMessageTemplate : public MessageTemplate<msgType, T> {
public:
  bool ParseFromArray(uint32_t dwMsgType, const char *buffer,
                      uint32_t size) override {
    LOG(INFO) << "custimized parse from origin with message type: "
              << dwMsgType;
    return this->_data.ParseFromArray(buffer, size);
  }
};

MessageBase *AllocNewMessage(uint32_t dwMsgType) {}

#endif /* AA4190D0_BCDE_430B_9D80_4FAFAE416A70 */
