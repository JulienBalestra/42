#include "ls.h"

int	how_many_option(t_opt *option)
{
	int i;

	i = 0;
	(option->one == 1) ? i++ : 0;
	(option->l == 1) ? i++ : 0;	
	(option->R == 1) ? i++ : 0;
	(option->a == 1) ? i++ : 0;
	(option->r == 1) ? i++ : 0;
	(option->t == 1) ? i++ : 0;
	(option->S == 1) ? i++ : 0;
	(option->Q == 1) ? i++ : 0;
	(option->U == 1) ? i++ : 0;
	(option->f == 1) ? i++ : 0;
	(option->g == 1) ? i++ : 0;
	(option->d == 1) ? i++ : 0;
	(option->G == 1) ? i++ : 0;
	(option->C == 1) ? i++ : 0;
	(option->color == 1) ? i++ : 0;
	return (i);
}

static void	find_options(t_opt *options, char *av)
{
	while (*av != '\0')
	{
		(*av == '1') ? (options->one = 1) : 0;
		(*av == '1') ? (options->C = 0) : 0;
		(*av == 'l') ? (options->l = 1) : 0;
		(*av == 'R') ? (options->R = 1) : 0;
		(*av == 'a') ? (options->a = 1) : 0;
		(*av == 'r') ? (options->r = 1) : 0;
		(*av == 't') ? (options->t = 1) : 0;
		(*av == 't') ? (options->S = 0) : 0;
		(*av == 'S') ? (options->S = 1) : 0;
		(*av == 'S') ? (options->t = 0) : 0;
		(*av == 'Q') ? (options->Q = 1) : 0;
		(*av == 'U') ? (options->U = 1) : 0;
		(*av == 'f') ? (options->f = 1) : 0;
		(*av == 'f') ? (options->U = 1) : 0;
		(*av == 'f') ? (options->a = 1) : 0;
		(*av == 'f') ? (options->color = 0) : 0;
		(*av == 'g') ? (options->g = 1) : 0;
		(*av == 'd') ? (options->d = 1) : 0;
		(*av == 'G') ? (options->G = 1) : 0;
		(*av == 'C') ? (options->C = 1) : 0;
		(*av == 'C') ? (options->one = 0) : 0;
		av++;
	}
}

static int match(char c)
{
	if (c == '1' || c == 'l' || c == 'R' || c == 'a' || c == 'r' || c == 't' || c == 'S'
			|| c == 'U' || c == 'f' || c == 'g' || c == 'd' || c == 'G' || c == 'C'|| c == 'Q')
		return (1);
	return (0);
}

static int	is_legal(char *av)
{
	int	i;
	int	n;

	i = 1;
	n = 1;
	while (av[i] != '\0')
	{
		n = n + match(av[i]);
		i++;
	}
	return (i == n ? 1 : 0);
}

void	ft_get_options(t_args *args, char *av)
{
	if (ft_strcmp(av, "--color") == 0)
	{
		if (args->options->f == 0)
			args->options->color = 1;
	}
	else if (is_legal(av) == 1)
		find_options(args->options, av);
	else
		invalid_option(args, av);
}