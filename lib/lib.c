#include <stdio.h>

int lib_func(void)
{
    printf("hello world from RTT::dynamic library!\n");

    return 0;
}

int add_func(int a, int b)
{
    return (a + b);
}

