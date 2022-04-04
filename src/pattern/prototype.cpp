#include "prototype.h"
#include "../header.h"

TEST(TestPattern, test_prototype) {
  SubPrototype typeobject;

  SubPrototype typeobject1 = typeobject;
  IPrototype *p = typeobject.Clone();
  LOG(INFO) << p->GetId();
  void *buff = malloc(sizeof(SubPrototype));
  IPrototype *newPoint = new (buff) SubPrototype;
}