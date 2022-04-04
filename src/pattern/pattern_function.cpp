#include "observer.h"
#include "pattern_adapter.h"
#include "pattern_builder.h"
#include "pattern_command.h"
#include "pattern_decorator.h"
#include "pattern_mediator.h"
#include "pattern_strategy.h"
#include "prototype.h"
#include <new>

TEST(TestPattern, adapter_pattern) {
  ClientCallClass object;
  AdapterOldService service;
  object.CallFunction(&service);
}

TEST(TestPattern, decorator_pattern) {
  GLTalker *talker = new GLTalker;
  GLTalkerWithMicr *p = new GLTalkerWithMicr(talker);
  CLTalkerWithMicrDecorator *p1 = new CLTalkerWithMicrDecorator(p);
  p1->talk();
}

TEST(TestPattern, observer_pattern) {
  Subject *psubject = new Subject();
  SomeObserver *pobserver = new SomeObserver(psubject);
  psubject->Subribe(pobserver);
  psubject->StateChange();
}

TEST(TestPattern, builder) {
  ManPersonBuilder *builder = new ManPersonBuilder;
  God *point = new God(builder);
  auto person = point->MakePerson();

  LOG(INFO) << "person make success! age:" << person->ToString();
}

TEST(TestPattern, command) {
  Receiver *peceiver = new Receiver();
  Command *cmd = new SimpleCommand(peceiver);
  Invoker *invoker = new Invoker();
  invoker->send_command_execute(cmd);
}

TEST(TestPattern, strategy) {
  Context *con = new Context;
  StrategyN1 *n1 = new StrategyN1;
  con->SetAlgorithm(n1);
  con->do_logic();
}

TEST(TestPattern, mediator) {
  AComponent *p = new AComponent(nullptr);
  CMediator *pmdiator = new CMediator(p);
  p->SetMediator(pmdiator);
  pmdiator->Notify(p, "A");
}