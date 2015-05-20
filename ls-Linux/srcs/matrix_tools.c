#include "ls.h"

int      min(int a, int b)
{
    return (a >= b ? b : a);
}

int      round_up(int a, int b)
{
    int ret;

    ret = 0;
    ret = a / b;
    return (ret);
}