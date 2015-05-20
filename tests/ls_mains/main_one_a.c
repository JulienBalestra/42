#include "ls.h"

int     main(int ac, char **av)
{
    t_args      *args;
    int         ret;
    t_item      *items;

    args = ft_get_args(ac, av);
    items = get_start(args->items);
    short_display(items, args);
    ret = args->ret;
    clean_program(&args);
    return (ret);
}
