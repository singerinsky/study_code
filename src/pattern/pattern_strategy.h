#ifndef B446D3FD_0E54_48FC_B6BB_FC40AE267BC2
#define B446D3FD_0E54_48FC_B6BB_FC40AE267BC2
#include "../header.h"

class Strategy {
public:
  virtual std::string Doalgorithm() = 0;
};
class Context {
private:
  Strategy *pstrategy;

public:
  void SetAlgorithm(Strategy *ps) { pstrategy = ps; }
  void do_logic() { pstrategy->Doalgorithm(); }
};

class StrategyN1 : public Strategy {
public:
  std::string Doalgorithm() {
    LOG(INFO) << "O1";
    return "O1";
  }
};
class StrategyN2 : public Strategy {
public:
  std::string Doalgorithm() {
    LOG(INFO) << "OO";
    return "O2";
  }
};

#endif /* B446D3FD_0E54_48FC_B6BB_FC40AE267BC2 */
