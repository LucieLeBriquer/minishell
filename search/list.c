/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:39:09 by lle-briq          #+#    #+#             */
/*   Updated: 2021/02/03 11:39:11 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_env(t_list *env, char *to_find)
{
	t_env	*content;

	while (env)
	{
		content = env->content;
		if (ft_strcmp(content->name, to_find) == 0)
			return (content->value);
		env = env->next;
	}
	return (NULL);
}
