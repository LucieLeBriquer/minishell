/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:38:48 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/04 13:17:42 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	size_of_list(t_list *list, int exported)
{
	int	i;

	i = 0;
	list = list->next;
	while (list)
	{
		if (((t_env *)list->content)->exported >= exported)
			i++;
		list = list->next;
	}
	return (i);
}

char		**create_env_tab(t_list *envl, int exported)
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
	envl = envl->next;
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
	env[i] = NULL;
	return (env);
}
