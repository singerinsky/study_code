#ifndef A0D0F94A_1930_4F43_B82F_9B79957DFFED
#define A0D0F94A_1930_4F43_B82F_9B79957DFFED

class IPrototype {
public:
  virtual IPrototype *Clone() = 0;
  virtual int GetId() = 0;

private:
  IPrototype &operator=(const IPrototype &src) = delete;
};

class SubPrototype : public IPrototype {
private:
  int id = 100;
  // SubPrototype(const SubPrototype &src) = delete;

public:
  int GetId() { return id; }
  virtual IPrototype *Clone() { return new SubPrototype(*this); }
};

#endif /* A0D0F94A_1930_4F43_B82F_9B79957DFFED */
