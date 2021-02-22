/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:38:48 by lle-briq          #+#    #+#             */
/*   Updated: 2021/02/22 17:59:27 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*init_entry(char *line, int exported)
{
	t_list	*new;
	t_env	*cont;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	cont = malloc(sizeof(t_env));
	if (!cont)
	{
		free(new);
		return (NULL);
	}
	cont->var = ft_strdup(line);
	cont->exported = exported;
	new->content = cont;
	new->next = NULL;
	return (new);
}

void	free_entry(void *ventry)
{
	t_env	*entry;

	entry = (t_env *)ventry;
	//ft_printf("free %p %p\n", entry->var, entry);
	free(entry->var);
	free(entry);
}

int		size_of_list(t_list *list, int exported)
{
	int	i;

	i = 0;
	while (list)
	{
		if (((t_env *)list->content)->exported >= exported)
			i++;
		list = list->next;
	}
	return (i);
}

char	**create_env_tab(t_list *envl, int exported)
{
	int		size;
	int		i;
	char	**env;

	size = size_of_list(envl, exported);
	env = malloc((size + 1) * sizeof(char *));
	if (!env)
		return (NULL);
	i = 0;
	while (i < size)
	{
		if (((t_env *)envl->content)->exported >= exported)
		{
			env[i] = ((t_env *)envl->content)->var;
			i++;
		}
		envl = envl->next;
	}
	env[size] = NULL;
	return (env);
}

void	parse_env(t_list **envl, char **env)
{
	t_list	*new;
	int		i;

	i = 0;
	*envl = NULL;
	new = init_entry("?begin", 0);
	ft_lstadd_back(envl, new);
	while (env[i])
	{
		new = init_entry(env[i], 2);
		ft_lstadd_back(envl, new);
		i++;
	}
}
