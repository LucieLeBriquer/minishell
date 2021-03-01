/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 19:19:12 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/01 20:00:16 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	expanded_size(char *str, t_list *envl)
{
	int		i;
	int		res;
	int		l;
	char	*value;

	l = ft_strlen(str);
	res = 0;
	i = 0;
	while (i < l)
	{
		if (str[i] == '$')
		{
			if (i > 0 && str[i - 1] == '\\')
				i++;
			else
			{
				res += size_var(str + ++i, envl, &value);
				while (i < l && (ft_isalpha(str[i]) || str[i] == '_'))
					i++;
			}
		}
		res++;
		i++;
	}
	return (res + 1);
}

static void	expand_one(t_split *split, int i, t_list *envl)
{
	char	*old;
	int		size_tot;

	old = split[i].str;
	size_tot = expanded_size(split[i].str, envl);
	split[i].str = malloc(size_tot * sizeof(char));
	if (!split[i].str)
		return ;
	fill_expanded(split[i].str, old, envl);
	free(old);
}

void		expand(t_info *cmd, t_split *split, t_list *envl)
{
	int	i;

	i = -1;
	while (++i < cmd->number)
	{
		if (split[cmd->start + i].sep == '\"'
			|| split[cmd->start + i].sep == ' ')
			expand_one(split, cmd->start + i, envl);
	}
}
