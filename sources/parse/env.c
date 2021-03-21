/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 16:20:53 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/21 16:20:55 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_entry(t_env *cont, char *line)
{
	char	*val;
	int		end;

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
}

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
	fill_entry(cont, line);
	cont->exported = exported;
	new->content = cont;
	new->next = NULL;
	return (new);
}

void	free_entry(void *ventry)
{
	t_env	*entry;

	entry = (t_env *)ventry;
	if (entry->var)
		free(entry->var);
	if (entry->value)
		free(entry->value);
	free(entry);
}

void	parse_env(t_list **envl, char **env)
{
	t_list	*new;
	int		shlvl;
	int		i;

	i = 0;
	*envl = NULL;
	new = init_entry("?begin", -1);
	ft_lstadd_back(envl, new);
	while (env[i])
	{
		new = init_entry(env[i], 2);
		if (ft_strcmp(((t_env *)new->content)->var, "SHLVL") == 0)
		{
			shlvl = ft_atoi(((t_env *)new->content)->value);
			shlvl++;
			free(((t_env *)new->content)->value);
			((t_env *)new->content)->value = ft_itoa(shlvl);
		}
		ft_lstadd_back(envl, new);
		i++;
	}
	add_env("_", ft_strdup("./minishell"), envl, 1);
}
