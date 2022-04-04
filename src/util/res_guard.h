#ifndef C5681C74_A281_4BFF_84A7_3E9A77142462
#define C5681C74_A281_4BFF_84A7_3E9A77142462


template<typename T>
class AutoGuard
{
using finally_cb = void(*)(T*);
public:
    AutoGuard(T* t,finally_cb cb):t_(t),cb_(cb)
    {}
    ~AutoGuard()
    {
        cb_(t_);
    }

private:
    T* t_;
    finally_cb cb_;
};


#endif /* C5681C74_A281_4BFF_84A7_3E9A77142462 */
