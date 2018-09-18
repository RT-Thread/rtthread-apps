#include <stdio.h>
#include <dlmodule.h>

/* dlmodule initial function */
void module_init(struct rt_dlmodule *module)
{
    module->priority = 8;
    module->stack_size = 4096;

    printf("this is module %s initial function!\n",module->parent.name);
}

/* dlmodule cleanup function */
void module_cleanup(struct rt_dlmodule *module)
{
    printf("this is module %s cleanup function!\n",module->parent.name);
}

int main(int argc, char *argv[])
{
    int i;

    printf("hello world from RTT::dynamic module!\n");

    for(i = 0;i < argc;i ++)
    {
        printf("argv[%d]:%s\n",i,argv[i]);
    }

    return 0;
}

