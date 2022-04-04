#ifndef _PATTERN_VISITOR_H_
#define _PATTERN_VISITOR_H_

#include "../header.h"

class ComponentA;
class ComponentB;

class IVisitor {
public:
    virtual void Visit(ComponentA* componentA) = 0;
    virtual void Visit(ComponentB* componentB) = 0;
};

class Component {
public:
    virtual void Accept(IVisitor* visitor) = 0;
};

class ComponentA : public Component {
public:
    virtual void Accept(IVisitor* visitor)
    {
        LOG(INFO) << "Visitor visit component A";
    }
};

class ComponentB : public Component {
public:
    virtual void Accept(IVisitor* visitor)
    {
        LOG(INFO) << "Visitor visit component B";
    }
};


class VisitorEx : public IVisitor {
public:
    virtual void Visit(ComponentA* a)
    {
        a->Accept(this);
    }
    virtual void Visit(ComponentB* b)
    {
        b->Accept(this);
    }
};


TEST(PatternTest,visitor)
{
    VisitorEx* pv = new VisitorEx();
    ComponentA* pA = new ComponentA();
    ComponentB* pB = new ComponentB();
    std::vector<Component*> vec_com= {pA,pB};
    for(auto itr:vec_com){
        itr->Accept(pv);
    }
}

#endif
