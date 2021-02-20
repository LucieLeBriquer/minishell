#include "ft_list.h"

int		list_size(t_list *begin_list)
{
	int		i;

	i = 0;
	while (begin_list)
	{
		begin_list = begin_list->next;
		i++;
	}
	return (i);
}

void	ft_list_sort(t_list **begin_list, int (*cmp)())
{
	t_list	*current;
	void	*save;
	int		size;
	int		i;
	int		j;

	i = 0;
	size = list_size(*begin_list);
	while (i < size)
	{
		j = 0;
		current = *begin_list;
		while (j < size - 1 - i)
		{
			if ((*cmp)(current->data, current->next->data) > 0)
			{
				save = current->data;
				current->data = current->next->data;
				current->next->data = save;
			}
			current = current->next;
			j++;
		}
		i++;
	}
}
