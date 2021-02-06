/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:38:58 by lle-briq          #+#    #+#             */
/*   Updated: 2021/02/06 14:45:26 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	trim_quotes(char *s)
{
	int	i;
	int	l;

	i = 0;
	l = ft_strlen(s);
	while (i + 2 < l)
	{
		s[i] = s[i + 1];
		i++;
	}
	s[i] = '\0';
}

void		trim_spaces_left(char *s)
{
	int	i;
	int	j;
	int	l;

	i = 0;
	l = ft_strlen(s);
	while (i < l && ft_isspace(s[i]))
		i++;
	j = -1;
	while (i + ++j < l)
		s[j] = s[i + j];
	while (j < l)
	{
		s[j] = '\0';
		j++;
	}
}

void		trim_spaces_right(char *s)
{
	int	l;

	l = ft_strlen(s);
	while (l > 0 && ft_isspace(s[l - 1]))
	{
		s[l - 1] = '\0';
		l--;
	}
}

void		trim_useless(t_split split)
{
	trim_spaces_left(split.str);
	if (split.quote == '\'' || split.quote == '\"')
		trim_quotes(split.str);
}
