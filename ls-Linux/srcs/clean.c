#include "ls.h"

void		clean_items(t_item *item)
{
	del_list(&item, 0);
}

void		clean_program(t_args **args)
{
	if ((*args)->items)
		clean_items((*args)->items);
	if ((*args)->options)
		free((*args)->options);
	if ((*args)->ld)
		free((*args)->ld);
	if ((*args)->sd)
		free((*args)->sd);
	if (*args)
	{
		free(*args);
		*args = NULL;
	}
}