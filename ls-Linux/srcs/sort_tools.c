#include "ls.h"

void set_merge(t_sort *merge, t_item *list)
{
	if (merge)
	{
		merge->right = list;
		merge->temp = list;
		merge->last = list;
		merge->result = NULL;
		merge->next = NULL;
		merge->tail = NULL;
	}
}