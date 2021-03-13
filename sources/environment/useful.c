/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 19:19:16 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/13 18:39:39 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*search_in_env(t_list *envl, char *var)
{
	while (envl)
	{
		if (ft_strcmp(((t_env *)envl->content)->var, var) == 0)
			return (((t_env *)envl->content)->value);
		envl = envl->next;
	}
	return (NULL);
}

static int	list_size(t_list *begin_list)
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

void		ft_lstsort(t_list **begin_list, int (*cmp)())
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
			if ((*cmp)(current->content, current->next->content) > 0)
			{
				save = current->content;
				current->content = current->next->content;
				current->next->content = save;
			}
			current = current->next;
			j++;
		}
		i++;
	}
}

static char	*ft_strcut(char *line, char c)
{
	int		i;
	char	*res;

	i = 0;
	while (line[i] && line[i] != c)
		i++;
	res = malloc((i + 1) * sizeof(char));
	i = 0;
	while (line[i] && line[i] != c)
	{
		res[i] = line[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

int			variable_match(t_list *envl, char *var, int cut)
{
	char	*env_var;
	char	*to_find;

	if (cut)
		to_find = ft_strcut(var, '=');
	else
		to_find = ft_strdup(var);
	env_var = ((t_env *)envl->content)->var;
	if (ft_strcmp(env_var, to_find) == 0)
	{
		free(to_find);
		return (1);
	}
	free(to_find);
	return (0);
}
