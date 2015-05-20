#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

static t_list *lstmap_test_fn(t_list *elem)
{
	t_list	*l2;

	l2 = malloc(sizeof(t_list));
	bzero(l2, sizeof(t_list));
	l2->content = malloc(elem->content_size * 2);
	strcpy(l2->content, "1234");
	l2->content_size = elem->content_size * 2;
	return (l2);
}


int     main(int ac, char **av)
{
    if (ac != 3)
        return 1;
    else
    {
            t_list  *base_list;
            t_list  *new_list;

            base_list = ft_lstnew(av[1], ft_strlen(av[1]));

            new_list = ft_lstmap(base_list, lstmap_test_fn);

            printf("%s:", (char *) new_list->content);
            printf("%i", (int) new_list->content_size);
    }
    return 0;
}