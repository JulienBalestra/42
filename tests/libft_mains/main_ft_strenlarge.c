#include "libft.h"

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		return 1;
	}
	else
	{
		char 	*string;
		size_t	init_size = 5;
		size_t	size = ft_atoi(av[1]);
		size_t	total_size;
		size_t	i = 0;


		
		string = ft_strnew(init_size);
			
		while (i < init_size)
			string[i++] = '1';
		//ft_putstr(string);
			
		string = ft_strenlarge(&string, size);	
		//ft_putstr(string);
		total_size = size + init_size;

		while (init_size < total_size)
			string[init_size++] = '2';
		ft_putstr(string);
	}
	return 0;
}