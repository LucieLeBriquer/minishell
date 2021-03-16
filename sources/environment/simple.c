/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 19:19:12 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/16 16:18:42 by lle-briq         ###   ########.fr       */
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

void	expand_simple(t_list **words, char *str, t_list *envl)
{
	int		size_tot;
	char	*new;
	t_list	*to_add;

	size_tot = expanded_size(str, envl);
	new = malloc(size_tot * sizeof(char));
	if (!new)
		return ;
	fill_expanded(new, str, envl);
	to_add = ft_lstnew(new);
	ft_lstadd_back(words, to_add);
}

void	expand_hard(t_list **words, char *str, t_list *envl, t_list **seps, t_list **spaces)
{
	int		size_tot;
	int		i;
	char	**split;
	char	*new;
	t_list	*to_add;

	size_tot = expanded_size(str, envl);
	new = malloc(size_tot * sizeof(char));
	if (!new)
		return ;
	fill_expanded(new, str, envl);
	split = ft_splitchar(new, ' ');
	i = 0;
	while (split[i])
	{
		to_add = ft_lstnew(split[i]);
		ft_lstadd_back(words, to_add);
		ft_lstadd_back(seps, ft_lstnew(" "));
		if (split[i + 1])
			ft_lstadd_back(spaces, ft_lstnew("1"));
		i++;
	}
}
