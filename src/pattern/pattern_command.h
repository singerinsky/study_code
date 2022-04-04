#ifndef BCF8227A_57DB_4944_907D_DDE44910E910
#define BCF8227A_57DB_4944_907D_DDE44910E910

#include "../header.h"

class Command {
public:
  virtual void Execute() = 0;
};

class Receiver {
private:
public:
  void do_real_command() { LOG(INFO) << " do realy command!"; }
};

class SimpleCommand : public Command {
private:
  Receiver *pReceiver;

public:
  SimpleCommand(Receiver *recv) : pReceiver(recv) {}
  void Execute() {
    LOG(INFO) << " do execute....";
    if (pReceiver) {
      pReceiver->do_real_command();
    }
  }
};

class Invoker {
public:
  ~Invoker() {}
  void send_command_execute(Command *only_command) {
    if (only_command)
      only_command->Execute();
  }
};

#endif /* BCF8227A_57DB_4944_907D_DDE44910E910 */
