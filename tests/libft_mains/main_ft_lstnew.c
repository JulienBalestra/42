#include <stdlib.h>
#include <stdio.h>
#include "libft.h"



int     main(int ac, char **av)
{
    if (ac != 2)
        return 1;
    else
    {
            t_list  *mylist;
            t_list  *mylist_null;
            
            mylist = ft_lstnew(av[1], ft_strlen(av[1]));
            printf("%s:", (char *) mylist->content);
            printf("%i", (int) mylist->content_size);
            
            mylist_null = ft_lstnew(NULL, ft_strlen(av[1]));
            if (mylist_null->content != NULL)
                return 2;
            if (mylist_null->content_size != 0)
                return 3;
    }
    return 0;
}