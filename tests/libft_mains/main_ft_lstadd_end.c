#include <stdlib.h>
#include <stdio.h>
#include "libft.h"



int     main(int ac, char **av)
{
    if (ac != 3)
        return 1;
    else
    {
            t_list  *mylist;
            t_list  *new_link;

            mylist = ft_lstnew(av[1], ft_strlen(av[1]));
            new_link = ft_lstnew(av[2], ft_strlen(av[2]));
            ft_lstadd_end(&mylist, new_link);
            printf("%s:", (char *) mylist->content);
            printf("%i", (int) mylist->content_size);
            printf("->");
            printf("%s:", (char *) mylist->next->content);
            printf("%i", (int) mylist->next->content_size);
    }
    return 0;
}