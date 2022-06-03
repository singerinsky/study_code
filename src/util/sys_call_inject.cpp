#include "../header.h"

#define HOOK_SYS_FUNC(name) if( !g_sys_##name##_func ) { g_sys_##name##_func = (name##_pfn_t)dlsym(RTLD_NEXT,#name); }

typedef struct timezone *__restrict __timezone_ptr_t;

typedef time_t (*time_pfn_t)(time_t*);
typedef time_t (*mktime_pfn_t)(tm*);

typedef struct tm*(*localtime_pfn_t)(const time_t*timer);
typedef struct tm*(*localtime_r_pfn_t)(const time_t*timer,struct tm*buf);
//typedef struct tm*(*localtime_s_pfn_t)(const time_t *restrict timer,struct tm*restrict buf);

typedef int(*gettimeofday_pfn_t)(struct timeval *__restrict __tv, __timezone_ptr_t __tz);

//time function
static time_pfn_t g_sys_time_func 	= (time_pfn_t)dlsym(RTLD_NEXT,"time");
//localtime_r
static localtime_pfn_t g_sys_localtime_func 	= (localtime_pfn_t)dlsym(RTLD_NEXT,"localtime");
static localtime_r_pfn_t g_sys_localtime_r_func 	= (localtime_r_pfn_t)dlsym(RTLD_NEXT,"localtime_r");
static gettimeofday_pfn_t g_sys_gettimeofday_func 	= (gettimeofday_pfn_t)dlsym(RTLD_NEXT,"gettimeofday");
//static localtime_s_pfn_t g_sys_localtime_s_func 	= (localtime_s_pfn_t)dlsym(RTLD_NEXT,"localtime_s");
static mktime_pfn_t g_sys_mktime_func 	= (mktime_pfn_t)dlsym(RTLD_NEXT,"mktime");


#define SEC_OFFSET 86400
time_t time(time_t *tloc)
{
    HOOK_SYS_FUNC( time );
    time_t real_time = g_sys_time_func(NULL);
    return real_time - SEC_OFFSET;
}

tm* localtime(const time_t* timer)
{
    HOOK_SYS_FUNC( localtime);
    if(timer == NULL)
    {
        time_t now_time = time(NULL);
        now_time = now_time - SEC_OFFSET;
        return g_sys_localtime_func(&now_time);
    }else{
        return g_sys_localtime_func(timer);
    }
}

tm* localtime_r(const time_t* timer,tm* buff)
{
    HOOK_SYS_FUNC( localtime_r);
    if(timer == NULL)
    {
        time_t now_time = time(NULL);
        now_time = now_time - SEC_OFFSET;
        return g_sys_localtime_r_func(&now_time,buff);
    }else{
        auto t = g_sys_localtime_r_func(timer,buff);
        buff->tm_mday -= 1;
        return t;
    }
}

int gettimeofday(timeval* __restrict __tv,__timezone_ptr_t __tz)
{
    HOOK_SYS_FUNC( gettimeofday);
    __tv->tv_sec -= SEC_OFFSET;
    return g_sys_gettimeofday_func(__tv,__tz);
}
/*
time_t mktime (struct tm *__tp)
{
    HOOK_SYS_FUNC( mktime);
    time_t now = g_sys_mktime_func(__tp);
    return now-86400*2;
}
*/

time_t __real_time(time_t* tloc);
time_t __warpper_time(time_t *tloc)
{
    return 100000000;
}


