#include "libft.h"

static void	ft_swap_s(char **s1, char **s2)
{
	char	*tmp;

	tmp = NULL;
	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

void		ft_bubble_sort(char **av, int start, int ac)
{
	int	i;
	int	j;

	i = start;
	while (i < ac)
	{
		j = start;
		while (j < ac)
		{
			if (ft_strcmp(av[i], av[j]) < 0)
			{
				ft_swap_s(&av[i], &av[j]);
			}
			j++;
		}
		i++;
	}
}