#ifndef F2F33161_467B_4F38_85B4_331FB630A8CA
#define F2F33161_467B_4F38_85B4_331FB630A8CA
#include "../header.h"

class IClientNeedInterface {
public:
  virtual std::string GetID() = 0;
};

class OldService {
public:
  std::string GetOpenID() { return "id"; }
};

class AdapterOldService : public IClientNeedInterface, OldService {
public:
  std::string GetID() { return this->GetOpenID(); }
};

class ClientCallClass {

public:
  void CallFunction(IClientNeedInterface *interface) {
    LOG(INFO) << "call interface function with adapter";
    LOG(INFO) << interface->GetID();
  }
};

#endif /* F2F33161_467B_4F38_85B4_331FB630A8CA */
