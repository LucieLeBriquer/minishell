/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 16:21:03 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/21 16:21:04 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	sep_converter(char c, char *command, int k)
{
	if (c == '<' || c == '|' || c == '=' || c == ';' || c == '\'' || c == '\"')
		return (c);
	if (c == '>')
	{
		if (command[k + 1] == '>')
			return ('d');
		return (c);
	}
	return (' ');
}

int		is_operator(char c)
{
	if (c == '<' || c == '|')
		return (1);
	if (c == '=' || c == ';')
		return (2);
	if (c == '>')
		return (3);
	return (0);
}

int		is_spaceend(char c)
{
	if (ft_isspace(c) || is_operator(c) || c == '\'' || c == '\"')
		return (1);
	return (0);
}

int		is_state_ok(t_parse *p)
{
	if (p->state != OPERATOR || p->sep == '=' || p->sep == ';')
		return (p->nb);
	return (-1);
}

void	add_space(t_split *split, int i)
{
	if (i > 0)
		split[i - 1].space = 1;
	split[i].space = 1;
}
