/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 18:02:10 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/04 18:02:34 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	trim_spaces(char *s)
{
	int	l;
	int	i;

	l = ft_strlen(s);
	i = l - 1;
	while (i >= 0 && ft_isspace(s[i]))
	{
		s[i] = '\0';
		i--;
	}
}

void	trim_seps(t_split split)
{
	int	i;
	int	l;

	if (split.sep == '\'' || split.sep == '\"')
	{
		i = 0;
		l = ft_strlen(split.str);
		while (i + 2 < l)
		{
			split.str[i] = split.str[i + 1];
			i++;
		}
		split.str[i] = '\0';
		split.str[i + 1] = '\0';
	}
}
