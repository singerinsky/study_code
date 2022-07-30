#include "../header.h"

TEST(Test_stl, Time001)
{
    static const constexpr auto kInterval = 5ms;
    static const constexpr auto kSpin = 100us;
    static const constexpr auto kDuration = 1min;
    auto now = std::chrono::high_resolution_clock::now();
    LOG(INFO) << "std::chrono::high_resolution_clock::now();" << now.time_since_epoch().count();
    auto tick = now;
    auto final = now + kDuration;
    while (now < final)
    {
        tick += kInterval;
        std::this_thread::sleep_until(tick - kSpin);
        LOG(INFO) << "after sleep";
        while (now < tick)
        {
            std::this_thread::yield();
            now = std::chrono::high_resolution_clock::now();
        }
    }

}