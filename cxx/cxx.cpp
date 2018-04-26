#include "cxx.h"

#include <rtthread.h>

A::A()
    : a(0)
{
}

void A::setA(int value)
{
    a = value;
}

int A::getA(void)
{
    return a;
}

void A::toString()
{
    rt_kprintf("A::a = %d\n", a);
}

extern "C" {

int Atest(void)
{
    A a;

    a.setA(100);
    a.toString();

    return 0;
}

}
