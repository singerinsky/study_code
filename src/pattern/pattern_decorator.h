#ifndef C13942A0_2F01_4CFF_98EC_50FD8E821406
#define C13942A0_2F01_4CFF_98EC_50FD8E821406

#include "../header.h"

class ITalker {
public:
  virtual void talk() = 0;
};

class GLTalker : public ITalker {
public:
  void talk() { LOG(INFO) << "what are you talking about!"; }
};

class GLTalkerWithMicr : public ITalker {
protected:
  ITalker *m_pTalker;

public:
  GLTalkerWithMicr(ITalker *ptalker) : m_pTalker(ptalker) {}
  void talk() {
    if (m_pTalker) {
      LOG(INFO) << "i'am guanlei";
      m_pTalker->talk();
    }
  }
};

class CLTalkerWithMicrDecorator : public GLTalkerWithMicr {
public:
  CLTalkerWithMicrDecorator(ITalker *ptalker) : GLTalkerWithMicr(ptalker) {}
  void talk() {
    LOG(INFO) << "biiiiii";
    m_pTalker->talk();
  }
};

#endif /* C13942A0_2F01_4CFF_98EC_50FD8E821406 */
