/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 19:19:12 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/18 15:21:17 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	skip_var(char *str, int i, int l)
{
	if (str[i] == '?')
		i++;
	else
	{
		while (i < l && (ft_isalpha(str[i]) || str[i] == '_'))
			i++;
	}
	return (i);
}

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
				i = skip_var(str, i, l);
			}
		}
		res++;
		i++;
	}
	return (res + 1);
}

void	expand_simple(t_list **expansion, t_split curr, t_list *envl)
{
	int		size_tot;
	char	*new;

	size_tot = expanded_size(curr.str, envl);
	new = malloc(size_tot * sizeof(char));
	if (!new)
		return ;
	fill_expanded(new, curr.str, envl);
	ft_lstadd_back(expansion, new_entry(new, curr.sep, curr.space));
}

int		expand_hard(t_list **expansion, t_split curr, t_list *envl, int r)
{
	int		size_tot;
	int		i;
	char	**split;
	char	*new;

	size_tot = expanded_size(curr.str, envl);
	new = malloc(size_tot * sizeof(char));
	if (!new)
		return (ALLOCATION_FAIL);
	fill_expanded(new, curr.str, envl);
	split = ft_splitchar(new, ' ');
	free(new);
	i = 0;
	while (split[i])
	{
		if (split[i + 1])
			ft_lstadd_back(expansion, new_entry(ft_strdup(split[i]), ' ', 1));
		else
			ft_lstadd_back(expansion, new_entry(ft_strdup(split[i]), ' ', curr.space));
		i++;
	}
	free_tab(split);
	if (i > 1 && r)
		return (error_msg(AMBIGUOUS_REDIR, curr.str));
	return (SUCCESS);
}
