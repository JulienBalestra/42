#include "ls.h"
#include <stdio.h>

int     main(int ac, char **av)
{
    t_item      *start;
    t_args      *args;

    args = ft_get_args(ac, av);
    start = args->items;
    while (args->items)
    {
        printf("%s,", (char *)args->items->name);
        args->items = args->items->next;
    }
    if (start->next)
        remove_link(start->next);
    printf("|");
    while (start)
    {        
        printf("%s,", start->name);
        start = start->next;
    }
    clean_program(&args);
    return (0);
}