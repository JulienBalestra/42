#include <stdio.h>
#include "libft.h"


int	main(int ac, char **av)
{
	if (ac != 4)
		return 1;
	else
	{
		char	**split;
		int		nb_string = ft_atoi(av[3]);
		int		i;
		t_list  *lstsplit;
				
		split = ft_strsplit(av[1], av[2][0]);
		i = 0;
		lstsplit = ft_lstsplit(split);		
		while (lstsplit != NULL)
		{
			printf("%s", (char *)lstsplit->content);
			if (i < nb_string - 1)
				printf(":");
            i++;
			lstsplit = lstsplit->next;
		}
	}
	return 0;
}
