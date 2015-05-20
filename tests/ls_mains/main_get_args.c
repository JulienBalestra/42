#include "ls.h"
#include <stdio.h>

int     main(int ac, char **av)
{
    t_args      *args;

    args = ft_get_args(ac, av);
    while (args->items)
    {
        printf("%s", (char *)args->items->name);
        args->items = args->items->next;
    }
    if (args->options)
    {
        printf("%i", how_many_option(args->options));
    }
    clean_program(&args);
    return (0);
}