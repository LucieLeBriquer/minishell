/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 19:57:33 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/01 19:57:34 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	state_operator(char *command, int i, t_parse *p)
{
	if (is_operator(command[i]) == 3 && command[i + 1] == '>')
	{
		if (p->len_word == 0)
			p->len_word = 2;
		return (state_reset(command, i + 2, p));
	}
	if (p->len_word == 0)
		p->len_word = 1;
	return (state_reset(command, i + 1, p));
}

int	state_db_quote(char *command, int i, t_parse *p)
{
	int	j;

	j = i;
	while (command[i] && command[i] != '\"')
	{
		if (command[i] == '\\')
		{
			i++;
			if (command[i] == '\0')
				return (-1);
		}
		i++;
	}
	if (command[i] == '\"')
	{
		if (p->len_word == 0)
			p->len_word = i - j + 2;
		return (state_reset(command, i + 1, p));
	}
	return (-1);
}

int	state_quote(char *command, int i, t_parse *p)
{
	int	j;

	j = i;
	while (command[i] && command[i] != '\'')
		i++;
	if (command[i] == '\'')
	{
		if (p->len_word == 0)
			p->len_word = i - j + 2;
		return (state_reset(command, i + 1, p));
	}
	return (-1);
}

int	state_space(char *command, int i, t_parse *p)
{
	int	j;

	j = i;
	while (command[i] && !is_spaceend(command[i]))
		i++;
	if (p->len_word == 0)
		p->len_word = i - j + 1;
	return (state_reset(command, i, p));
}

int	state_reset(char *command, int i, t_parse *p)
{
	int			l;

	l = ft_strlen(command);
	if (p->len_word > 0)
		return (is_state_ok(p));
	if (i >= l)
		return (is_state_ok(p));
	while (ft_isspace(command[i]))
		i++;
	if (command[i] == '\0')
		return (is_state_ok(p));
	p->state = new_state(command, i);
	p->sep = command[i];
	(p->nb)++;
	if (p->state == SPACE)
		return (state_space(command, i + 1, p));
	else if (p->state == QUOTE)
		return (state_quote(command, i + 1, p));
	else if (p->state == DB_QUOTE)
		return (state_db_quote(command, i + 1, p));
	else
		return (state_operator(command, i, p));
}
