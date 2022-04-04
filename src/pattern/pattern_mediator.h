#ifndef F6492CC4_CFE8_4127_B529_908BC7FC08C0
#define F6492CC4_CFE8_4127_B529_908BC7FC08C0
#include "../header.h"

class BaseComponent;

class Mediator {
public:
  virtual void Notify(BaseComponent *, std::string strParam) = 0;
};

class BaseComponent {
protected:
  Mediator *mediator_;

public:
  BaseComponent(Mediator *p = nullptr) { mediator_ = p; }
  void SetMediator(Mediator *p) { mediator_ = p; }
};

class AComponent : public BaseComponent {
public:
  AComponent(Mediator *p) : BaseComponent(p) {}
  void DoA() { this->mediator_->Notify(this, "sss"); }
};

class BComponent : public BaseComponent {
public:
  BComponent(Mediator *p) : BaseComponent(p) {}
  void DoA() { this->mediator_->Notify(this, "sss"); }
};

class CMediator : public Mediator {
protected:
  AComponent *pcomponent;

public:
  CMediator(AComponent *p) : pcomponent(p) {}
  void Notify(BaseComponent *p, std::string strParam) override {
    if (strParam == "A") {
      pcomponent->DoA();
    }
  }
};

#endif /* F6492CC4_CFE8_4127_B529_908BC7FC08C0 */
