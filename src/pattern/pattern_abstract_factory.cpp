#include "pattern_abstract_factory.h"

TEST(TestPattern, AbstractFactory) {
  IFactory *factory = new NewProducerFactory();
  IProducer *producer = factory->CreateProducer();
  producer->ToString();
}
