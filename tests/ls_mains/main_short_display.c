#include "ls.h"

int     main(int ac, char **av)
{
    t_args      *args;
    t_item      *items;

    args = ft_get_args(ac, av);
    items = get_start(args->items);
    short_display(items, args);
    clean_program(&args);
    return (0);
}
