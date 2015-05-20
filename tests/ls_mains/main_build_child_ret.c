#include "ls.h"
#include <stdio.h>

int     main(int ac, char **av)
{
    t_args      *args;
    int         ret;

    args = ft_get_args(ac, av);
    get_parents_children(args);
    ret = args->ret;
    clean_program(&args);
    return (ret);
}