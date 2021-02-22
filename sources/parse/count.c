/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:38:32 by lle-briq          #+#    #+#             */
/*   Updated: 2021/02/22 17:19:38 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	new_state(char *s, int i)
{
	char	c;

	c = s[i];
	if ((c == '\'') || (c == '\"'))
		return (1);
	if ((c == '|') || (c == '<') || (c == '|') || (c == ';') ||
			(c == '>' && (!s[i + 1] || s[i + 1] != '>')))
		return (3);
	if (c == '>' && c && s[i + 1] && s[i + 1] == '>')
		return (4);
	return (0);
}

static int	is_operator(char c)
{
	if ((c == '|') || (c == '<') || (c == '>') || (c == ';'))
		return (1);
	return (0);
}

static int	close_sep(char c, char sep)
{
	if (c == sep)
		return (1);
	if (sep == ' ' && (c == '\"' || c == '\'' || ft_isspace(c)))
		return (1);
	return (0);
}

static char	find_separator(int i, int l, char *s, t_parse *current)
{
	while (i + 1 < l && ft_isspace(s[i]))
		i++;
	current->state = new_state(s, i);
	if (current->state == 0)
		current->sep = ' ';
	else if (current->state == 4)
		current->sep = 'd';
	else
		current->sep = s[i];
	(current->nb_words)++;
	if (i + 1 == l)
		(current->state) = 2;
	return (i);
}

int			nb_words(char *s, int l)
{
	int		i;
	t_parse	current;

	i = 0;
	current.state = 2;
	current.nb_words = 0;
	while (i < l)
	{
		if (current.state == 2)
		{
			i = find_separator(i, l, s, &current);
			if (i + 1 >= l && current.sep != ' ')
				return (-1);
		}
		else if (current.state == 0)
		{
			while (i < l && !is_operator(s[i]) && !close_sep(s[i], current.sep))
				i++;
			current.state = 2;
			if (is_operator(s[i]))
				i--;
			else if (close_sep(s[i], current.sep))
			{
				current.state = new_state(s, i);
				current.nb_words++;
			}
		}
		else if ((current.state == 3) || (current.state == 4))
		{
			i -= (current.state == 3);
			current.state = 2;
		}
		else if (current.sep == '\"' && i + 1 < l && s[i] == '\\')
			i++;
		else if (close_sep(s[i], current.sep))
		{
			current.state = 2;
			if (current.sep != ' ')
				i--;
		}
		i++;
	}
	if (current.state != 2)
		return (-1);
	return (current.nb_words);
}

int			len_of_word(char *s, char *sep)
{
	int		i;
	int		l;
	t_parse	current;

	i = 0;
	l = ft_strlen(s);
	i = find_separator(i, l, s, &current);
	*sep = current.sep;
	if (current.state == 0)
	{
		while (i < l && !is_operator(s[i]) && !close_sep(s[i], current.sep))
			i++;
		return (i);
	}
	if ((current.state == 3) || (current.state == 4))
		return (i + 1 + (current.state == 4));
	i++;
	while (i < l && !close_sep(s[i], current.sep))
	{
		if (current.sep == '\"' && i + 1 < l && s[i] == '\\')
			i++;
		i++;
	}
	return (i + 1);
}
