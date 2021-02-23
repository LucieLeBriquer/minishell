/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:38:48 by lle-briq          #+#    #+#             */
/*   Updated: 2021/02/23 14:45:16 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*init_entry(char *line, int exported)
{
	t_list	*new;
	t_env	*cont;
	char	*val;
	int		end;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	cont = malloc(sizeof(t_env));
	if (!cont)
	{
		free(new);
		return (NULL);
	}
	cont->value = NULL;
	end = ft_strlen(line);
	if (ft_strrchr(line, '=') != NULL)
	{
		val = ft_strchr(line, '=') + 1;
		end = ft_strlen(line) - ft_strlen(val) - 1;
		cont->value = ft_strdup(val);
	}
	cont->var = ft_strdup(line);
	(cont->var)[end] = '\0';
	cont->exported = exported;
	new->content = cont;
	new->next = NULL;
	return (new);
}

void	free_entry(void *ventry)
{
	t_env	*entry;

	entry = (t_env *)ventry;
	free(entry->var);
	if (entry->value)
		free(entry->value);
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
	char	*tmp;

	size = size_of_list(envl, exported);
	env = malloc((size + 1) * sizeof(char *));
	if (!env)
		return (NULL);
	i = 0;
	while (i < size)
	{
		if (((t_env *)envl->content)->exported >= exported)
		{
			tmp = ft_strjoin(((t_env *)envl->content)->var, "=");
			env[i] = ft_strjoin(tmp, ((t_env *)envl->content)->value);
			free(tmp);
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
