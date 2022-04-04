/**
 * @file general_timer.h
 * @copyright 2012 - 2028 ByteDance. All Rights Reserved
 * @date 2021/5/21
 * @author zhengyidong
 * @brief
 */

#ifndef W03_SERVER_GENERAL_TIMER_H
#define W03_SERVER_GENERAL_TIMER_H

/*
#include <memory>

#include "timer.h"
#include "logger_def.h"


class GeneralTimer : public wsengine::Timer
{
public:
    explicit GeneralTimer(wsengine::TimerManager *manager) : Timer(manager) {}
    ~GeneralTimer() {
        if (!Cancel()) {
            APPLOG_ERROR("GeneralTimer cancel error in dtor!");
        }
    }
    typedef std::function<void()> FunctionType;
    virtual void OnTimeout() override
    {
        should_cancel_ = Repeat() != 0;
        if (timeout_function_)
        {
            timeout_function_();
        }
        // timeout_function_()之后可能自身已经析构，不能有任何访问自身成员变量的操作
    }
    void SetTimeoutFunction(FunctionType function) { timeout_function_ = std::move(function); }

    bool Cancel() {
        if (!should_cancel_) {
            return true;
        }
        if (!Owner()->CancelTimer(this)) {
            should_cancel_ = false;
            return true;
        }
        // 不应该跑到这里
        return false;
    }

private:
    FunctionType timeout_function_;
    bool should_cancel_ = true;
};


// 使用者无需关心GeneralDelegatedTimer的生命周期
class GeneralDelegatedTimer : public wsengine::Timer {
public:
    explicit GeneralDelegatedTimer(wsengine::TimerManager *manager) : Timer(manager, true) {}
    typedef std::function<void()> FunctionType;
    virtual void OnTimeout() override
    {
        if (timeout_function_)
        {
            timeout_function_();
        }
    }
    void SetTimeoutFunction(FunctionType function) { timeout_function_ = std::move(function); }
private:
    FunctionType timeout_function_;
};


inline std::unique_ptr<GeneralTimer> CreateWTimer(std::function<void()> cb, int interval_in_milliseconds, int repeats)
{
    GeneralTimer* timer = GLOBAL_TIMERMANAGER_INST->CreateTimer<GeneralTimer>(interval_in_milliseconds, repeats);
    if (timer)
    {
        timer->SetTimeoutFunction(std::move(cb));
    }
    return std::unique_ptr<GeneralTimer>(timer);
}


inline std::unique_ptr<GeneralTimer> CreateOnceWTimer(std::function<void()> cb, int interval_in_milliseconds)
{
    GeneralTimer* timer = GLOBAL_TIMERMANAGER_INST->CreateOnceTimer<GeneralTimer>(interval_in_milliseconds);
    if (timer)
    {
        timer->SetTimeoutFunction(std::move(cb));
    }
    return std::unique_ptr<GeneralTimer>(timer);
}


inline std::unique_ptr<GeneralTimer> CreateForeverWTimer(std::function<void()> cb, int interval_in_milliseconds)
{
    GeneralTimer* timer = GLOBAL_TIMERMANAGER_INST->CreateForeverTimer<GeneralTimer>(interval_in_milliseconds);
    if (timer)
    {
        timer->SetTimeoutFunction(std::move(cb));
    }
    return std::unique_ptr<GeneralTimer>(timer);
}


inline GeneralDelegatedTimer* CreateOnceDelegatedWTimer(std::function<void()> cb, int interval_in_milliseconds)
{
    GeneralDelegatedTimer* timer = GLOBAL_TIMERMANAGER_INST->CreateOnceTimer<GeneralDelegatedTimer>(interval_in_milliseconds);
    if (timer)
    {
        timer->SetTimeoutFunction(std::move(cb));
    }
    return timer;
}

*/

#endif //W03_SERVER_GENERAL_TIMER_H