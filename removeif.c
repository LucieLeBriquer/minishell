#include "ft_list.h"

void	remove_aux(t_list *prev, t_list **suppr, void (*free_fct)(void *))
{
	t_list	*save;

	save = (*suppr)->next;
	(*free_fct)((*suppr)->data);
	free(*suppr);
	prev->next = save;
	*suppr = prev;
}

void	ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(),
		void (*free_fct)(void *))
{
	t_list	*prev;
	t_list	*curr;
	t_list	*save;

	curr = *begin_list;
	while (curr && (*cmp)(curr->data, data_ref) == 0)
	{
		save = curr->next;
		(*free_fct)(curr->data);
		free(curr);
		curr = save;
	}
	*begin_list = curr;
	while (curr && curr->next)
	{
		prev = curr;
		curr = curr->next;
		if ((*cmp)(curr->data, data_ref) == 0)
			remove_aux(prev, &curr, free_fct);
	}
}
