#include "../header.h"

typedef time_t (*time_pfn_t)(time_t*);
#define HOOK_SYS_FUNC(name) if( !g_sys_##name##_func ) { g_sys_##name##_func = (name##_pfn_t)dlsym(RTLD_NEXT,#name); }
static time_pfn_t g_sys_time_func 	= (time_pfn_t)dlsym(RTLD_NEXT,"time");

time_t time(time_t *tloc)
{
    HOOK_SYS_FUNC( time );
    time_t real_time = g_sys_time_func(NULL);
    return real_time - 86400;
}


