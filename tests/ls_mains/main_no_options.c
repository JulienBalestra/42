#include "ls.h"
#include <stdio.h>

int     main(int ac, char **av)
{
    t_args      *args;

    args = ft_get_args(ac, av);
    if (how_many_option(args->options) == 0)
    {
        clean_program(&args);
        return (0);
    }
    else
    {
        clean_program(&args);
        return (1);
    }
}