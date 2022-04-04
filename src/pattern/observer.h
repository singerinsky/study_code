#ifndef D0CB791F_EFA8_482D_8A74_80C03D1CECE2
#define D0CB791F_EFA8_482D_8A74_80C03D1CECE2

#include "../header.h"
#include <string>

class Subject;
class Observer {
protected:
  Subject *m_pSubject;

public:
  virtual void update() = 0;
};

class Subject {
private:
  std::string m_strState;
  std::vector<Observer *> vecObserver;

public:
  std::string GetState() { return m_strState; }
  void StateChange() {
    m_strState = std::to_string(time(NULL));
    Notify();
  }
  void Subribe(Observer *server) {
    auto itr = std::find(vecObserver.begin(), vecObserver.end(), server);
    if (itr == vecObserver.end()) {
      vecObserver.push_back(server);
    }
  }

  void Notify() {
    for (auto &itr : vecObserver) {
      itr->update();
    }
  }
};

class SomeObserver : public Observer {
public:
  SomeObserver(Subject *pSubject) { m_pSubject = pSubject; }
  void update() { LOG(INFO) << "receive message" << m_pSubject->GetState(); }
};

#endif /* D0CB791F_EFA8_482D_8A74_80C03D1CECE2 */
