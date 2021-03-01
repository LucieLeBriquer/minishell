/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:38:58 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/01 17:28:44 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	is_operator(char c)
{
	if (c == '<' || c == '|')
		return (1);
	if (c == '=' || c == ';')
		return (2);
	if (c == '>')
		return (3);
	return (0);
}

int	is_spaceend(char c)
{
	if (ft_isspace(c) || is_operator(c) || c == '\'' || c == '\"')
		return (1);
	return (0);
}

int	is_state_ok(t_parse *p)
{
	if (p->state != OPERATOR || p->sep == '=' || p->sep == ';')
		return (p->nb);
	return (-1);
}

int	new_state(char *command, int i)
{
	if (command[i] == '\"')
		return (DB_QUOTE);
	if (command[i] == '\'')
		return (QUOTE);
	if (is_operator(command[i]))
		return (OPERATOR);
	return (SPACE);
}
