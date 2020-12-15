#include <stdio.h>

int main(int argc, char *argv[])
{
    rt_kprintf("device testing\n");

    extern int device_test(void);
    device_test();

    return 0;
}

