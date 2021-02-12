/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:38:48 by lle-briq          #+#    #+#             */
/*   Updated: 2021/02/03 11:38:50 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** if environment not corrupted (= in each line)
*/

t_list	*cut_equal(char *line)
{
	int		i;
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
	i = 0;
	while (line[i] != '=')
		i++;
	line[i] = '\0';
	cont->name = ft_strdup(line);
	cont->value = ft_strdup(line + i + 1);
	new->content = cont;
	new->next = NULL;
	return (new);
}

void	free_entry(void *ventry)
{
	t_env	*entry;

	entry = (t_env *)ventry;
	free(entry->name);
	free(entry->value);
}

void	parse_env(t_list **env_list, char **env)
{
	t_list	*new;
	int		i;

	i = 0;
	*env_list = NULL;
	while (env[i])
	{
		new = cut_equal(env[i]);
		ft_lstadd_back(env_list, new);
		i++;
	}
}
