#ifndef _CLASS_SAMPLE_H_
#define _CLASS_SAMPLE_H_
#include "glog/logging.h"
#include <map>

class SampleClass
{
public:
    SampleClass()
    {
        static int id_index = 0;
        id = id_index;
        id_index++;
        LOG(INFO) << "Create New Sample Class" << id << " With Con";
    }

    SampleClass(int i)
    {
        static int id_index = 0;
        id_index = i;
        LOG(INFO) << "Create New Sample Class" << id << " With Con";
    }


    ~SampleClass()
    {
        LOG(INFO) << "Release Sample Class" << id;
    }

    SampleClass(const SampleClass& value)
    {
        LOG(INFO) << "Create New Sample Class" << id << " With Copy";
        id = value.id;
    }

    SampleClass& operator=(const SampleClass& value)
    {
        LOG(INFO) << "Set Sample Class" << id << " With =";
        id = value.id;
        return *this;
    }

    SampleClass(SampleClass&& src)
    {
        LOG(INFO) << "Create New Sample Class" << id << " With Move Constructor";
    }

    SampleClass& operator=(SampleClass&& value)
    {
        LOG(INFO) << "Create New Sample Class" << id << " With Move Copy";
        return *this;
    }

    void SetId(int id_param)
    {
        id = id_param;
    }

    int GetId()
    {
        return id;
    }

    void ModifyTest()const
    {
        modify_value++;
    }

    void DumpValue()
    {
        LOG(INFO) << "modify value " << modify_value;
    }
private:
    int id = 0;
    mutable int modify_value = 0;
};

class ClassWithFunctionReturnObject
{
public:
    SampleClass GetObject()
    {
        return object_;
    }
private:
    SampleClass object_;
};


class ClassWithUniquePtr
{
public:
    ClassWithUniquePtr() {}
    ~ClassWithUniquePtr()
    {
        LOG(INFO) << "Call class ClassWithUniquePtr descutor";
    }

public:
    std::unique_ptr<SampleClass> ptr_;
};

//简单类型
class PodSampleClass
{
public:
    int id_;
    int flag_;
    char str_value_[100];
    PodSampleClass()
    {
        //memset(this,0,sizeof(PodSampleClass));
    }
    PodSampleClass(int id, int flag): id_(id), flag_(flag)
    {
        LOG(INFO) << "Call base class constructor";
    }

    ~PodSampleClass()
    {
        LOG(INFO) << "DELETE POD OBJECT";
    }

    virtual bool IsValied()
    {
        if (!this)
        {
            return false;
        }
        return _value_flag ==  0x123456789ABCDE0;
    }

    int CheckClass()
    {
        return 1;
    }
private:
    long long _value_flag = 0x123456789ABCDE0;
};

class SubPodClass : public PodSampleClass
{
public:
    SubPodClass(int x, int y, int z): PodSampleClass(x, y)
    {
        LOG(INFO) << "Call Sub class special constructor";
    }
    using PodSampleClass::PodSampleClass;
    int CheckClass()
    {
        return 2;
    }
    int CheckClass(int i)
    {
        return 3;
    }
private:
    virtual bool check()
    {
        return 1;
    }
    int sub_value = 0;
    static int static_value;
    long long _value_flag = 0x123456789ABCDE0;
};

class SampleClassManager
{
protected:
    SampleClassManager() {}
    ~SampleClassManager()
    {
        LOG(INFO) << "release SampleClassManager!";
        LOG(INFO) << "current object size:" << all_object.size();
    }
public:
    static SampleClassManager* GetInstance()
    {
        static SampleClassManager instance;
        return &instance;
    }

    void AddSampleObject(int id, SampleClass* object)
    {
        all_object[id] = object;
    }
    SampleClass* GetObject(int id)
    {
        return all_object.end() != all_object.find(id) ? all_object.find(id)->second : nullptr;
    }
    void Dump()
    {
        LOG(INFO) << "Now Manager contain object number:" << all_object.size();
    }

private:
    std::map<int, SampleClass*> all_object;
};

template<typename T>
class TemplateClassBase
{
public:
    static T* Instance()
    {
        if (!instance_)
        {
            instance_ = new T;
        }
        return instance_;
    }
protected:
    static T* instance_;
};

template<typename T> T* TemplateClassBase<T>::instance_ = nullptr;


class SingletonClassOne: public TemplateClassBase<SingletonClassOne> {};


class SingletonClassTwo: public TemplateClassBase<SingletonClassTwo> {};

template<typename ...Mix>
class AnySubClass: public Mix...
{
public:
    const char* ClassName = "A";
};

class ClassWithTemplateFunction
{
public:
    template<typename T, void(*Func_Template)(T*)>
    void call(T* t)
    {
        Func_Template(t);
    }
};

class ClassWithData
{
public:
    char* buff;
};

class ClassWithInitializer
{
public:
    ClassWithInitializer(initializer_list<std::pair<string, string>> l)
    {
        for (auto& p : l)
        {
            data.push_back(p);
        }
    }
    void dump()
    {
        LOG(INFO) << "size is" << data.size();
    }

private:
    std::vector<std::pair<string, string>> data;
};


class SingleClass
{
public:
    static SingleClass* Instance(int sleep_sec)
    {
        static std::once_flag _flag;
        static std::unique_ptr<SingleClass> _ptr;
        std::call_once(_flag, [&]()
        {
            _ptr.reset(new SingleClass());
            return _ptr.get();
        });
        return _ptr.get();

    }
};

/*
template<typename T>
class SingletonClassTemplate
{
public:
    static T& GetInstance(){
        static std::once_flag s_flag;
        std::call_once(s_flag,[&]()
                       {
        _ptr.reset(new T);
        return *(_ptr.get());
                       });
        return *(_ptr.get());
    }
private:
    static std::unique_ptr<T> _ptr;
};


template<typename T>
std::unique_ptr<T> SingletonClassTemplate<T>::_ptr;

*/

template<typename T>
class SingletonClassTemplate
{
public:
    static T& GetInstance()
    {
        static std::once_flag s_flag;
        std::call_once(s_flag, [&]()
        {
            _ptr.reset(new T);
            return *(_ptr.get());
        });
        return *_ptr;
    }
private:
    static std::unique_ptr<T> _ptr;
};

template <typename T> std::unique_ptr<T> SingletonClassTemplate<T>::_ptr;

template<>
class SingletonClassTemplate<float>
{
public:
    static float& GetInstance()
    {
        if (_ptr == nullptr)
        {
            _ptr.reset(new float);
        }
        return *_ptr;
    }
private:
    static std::unique_ptr<float> _ptr;
};



template<>
class SingletonClassTemplate<unsigned int>
{
public:
    static unsigned int& GetInstance()
    {
        if (_ptr == nullptr)
        {
            _ptr.reset(new unsigned int);
        }
        return *_ptr;
    }
private:
    static std::unique_ptr<unsigned int> _ptr;
};


#endif
