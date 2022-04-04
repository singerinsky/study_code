#ifndef CDCFF4A9_C6DC_46B8_9EE7_1C3B5BF9D929
#define CDCFF4A9_C6DC_46B8_9EE7_1C3B5BF9D929

#include <string>
class Person {
public:
  Person() = default;
  void SetAge(int age) { _age = age; }
  void SetSex(int sex) { _sex = sex; }
  std::string ToString() {
    std::string str =
        std::to_string(_age).append("_").append(std::to_string(_sex));
    return str;
  }

private:
  int _age;
  int _sex;
};

class PersonBuilder {
public:
  virtual void BuildAge() = 0;
  virtual void BuildSex() = 0;
  virtual Person *BuildPerson() = 0;
};

class ManPersonBuilder : public PersonBuilder {
private:
  Person *person;

public:
  ManPersonBuilder() { person = new Person; }
  void BuildAge() override { person->SetAge(37); }
  void BuildSex() override { person->SetSex(1); }
  Person *BuildPerson() override { return person; }
};

class God {
private:
  PersonBuilder *_builder;

public:
  God(PersonBuilder *builder) { _builder = builder; }
  Person *MakePerson() {
    _builder->BuildAge();
    _builder->BuildSex();
    return _builder->BuildPerson();
  }
};

#endif /* CDCFF4A9_C6DC_46B8_9EE7_1C3B5BF9D929 */
