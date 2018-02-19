#ifndef RTTHREAD_H__
#define RTTHREAD_H__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

#define RT_USING_DFS
#define RT_USING_DEVICE
#define RT_TICK_PER_SECOND  100
#define RT_CONSOLEBUF_SIZE  256

#define RT_NULL          NULL
#define RT_ASSERT(EX)       \
    if (!(EX))              \
    {                       \
        printf(#EX);        \
        exit(-1);           \
    }

#define rt_vsnprintf        vsnprintf

typedef size_t   rt_size_t;
typedef uint32_t rt_tick_t;

void rt_kprintf(const char *fmt, ...);
rt_tick_t rt_tick_get(void);

void *rt_malloc(rt_size_t nbytes);
void rt_free(void *ptr);

int rt_hw_interrupt_disable(void);
void rt_hw_interrupt_enable(int level);

#ifdef __cplusplus
}
#endif

#endif
