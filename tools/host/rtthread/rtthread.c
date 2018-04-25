#include "rtthread.h"

#include <time.h>

void rt_kprintf(const char *fmt, ...)
{
    va_list argptr;

    va_start(argptr,fmt);
    vprintf(fmt,argptr);
    va_end(argptr);

    return ;
}

rt_tick_t rt_tick_get(void)
{
    return 0;
}

void *rt_malloc(rt_size_t nbytes)
{
    void* ret = malloc(nbytes);
    
    return ret;
}

void rt_free(void *ptr)
{
    free(ptr);
}

int rt_hw_interrupt_disable(void)
{
    return 0;
}

void rt_hw_interrupt_enable(int level)
{
    return ;
}
