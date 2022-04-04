#ifndef AA8DB1FF_CED0_4682_A34F_23030971C8CC
#define AA8DB1FF_CED0_4682_A34F_23030971C8CC

#include "../header.h"

class IProducer {
public:
  virtual void ToString() = 0;
};

class IFactory {
public:
  virtual IProducer *CreateProducer() = 0;
};

class NewProducer : public IProducer {
public:
  virtual void ToString() { LOG(INFO) << "new producer"; }
};

class NewProducerFactory : public IFactory {
public:
  IProducer *CreateProducer() { return new NewProducer(); }
};
#endif /* AA8DB1FF_CED0_4682_A34F_23030971C8CC */
