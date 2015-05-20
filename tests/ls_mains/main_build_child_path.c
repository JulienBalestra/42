#include "ls.h"
#include <stdio.h>

int     main(int ac, char **av)
{
    t_args      *args;
    t_item      *cursor;

    args = ft_get_args(ac, av);
    cursor = get_start(args->items);
    if (cursor->child)
    {
        cursor = cursor->child;
        while (cursor)
        {
            printf("%s\n", cursor->path);
            cursor = cursor->next;
        }
    }
    clean_program(&args);
    return (0);
}