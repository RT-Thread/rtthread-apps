#include <rtthread.h>
#include "crt.h"

void *operator new(size_t size)
{
    return rt_malloc(size);
}

void *operator new[](size_t size)
{
    return rt_malloc(size);
}

void operator delete(void *ptr)
{
    rt_free(ptr);
}

void operator delete[] (void *ptr)
{
    return rt_free(ptr);
}

void __cxa_pure_virtual(void)
{
    RT_ASSERT(!"Illegal to call a pure virtual function.");
}

#ifdef __GNUC__
namespace std {

void __throw_bad_cast()
{
    RT_ASSERT(!"Bad cast.");
}

void __throw_bad_alloc()
{
    RT_ASSERT(!"Bad alloc.");
}

void __throw_bad_typeid()
{
    RT_ASSERT(!"Bad typeid.");
}

void __throw_ios_failure(char const* p)
{
    RT_ASSERT(!"iOS failure.");
}

void __throw_logic_error(char const* p)
{
    RT_ASSERT(!"Logic error.");
}

void __throw_range_error(char const* p)
{
    RT_ASSERT(!"Range error.");
}

void __throw_domain_error(char const* p)
{
    RT_ASSERT(!"Domain error.");
}

void __throw_future_error(int p)
{
    RT_ASSERT(!"Future error.");
}

void __throw_length_error(char const* p)
{
    RT_ASSERT(!"Length error.");
}

void __throw_out_of_range(char const* p)
{
    RT_ASSERT(!"Out of range error.");
}

void __throw_system_error(int p)
{
    RT_ASSERT(!"System error.");
}

void __throw_bad_exception()
{
    RT_ASSERT(!"Bad exception.");
}

void __throw_runtime_error(char const* p)
{
    RT_ASSERT(!"Runtime error.");
}

void __throw_overflow_error(char const* p)
{
    RT_ASSERT(!"Overflow error.");
}

void __throw_underflow_error(char const* p)
{
    RT_ASSERT(!"Underflow error.");
}

void __throw_invalid_argument(char const* p)
{
    RT_ASSERT(!"Invalid argument.");
}

void __throw_out_of_range_fmt(char const* p, ...)
{
    RT_ASSERT(!"Out of range fmt.");
}

}
#endif
