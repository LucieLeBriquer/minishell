/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 17:37:50 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/11 21:47:28 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	free_split(t_split *split, int i)
{
	int	j;

	j = -1;
	while (++j < i)
		free(split[j].str);
	free(split);
	return (-1);
}

static void	fill_one_word(t_split *word, int word_len, const char *cmd)
{
	ft_strlcpy(word->str, cmd, word_len + 1);
	word->str[word_len + 1] = '\0';
	trim_seps(*word);
	word->space = 0;
}

static int	fill_words(t_split *split, int words, char *command)
{
	int		i;
	int		k;
	char	sep;
	int		size;
	int		word_len;

	size = ft_strlen(command);
	i = 0;
	k = 0;
	while (i < words)
	{
		while (ft_isspace(command[k]))
			k++;
		word_len = len_of_word(command, k, &sep);
		split[i].sep = sep_converter(sep, command, k);
		split[i].str = malloc((word_len + 2) * sizeof(char));
		if (!split[i].str)
			return (free_split(split, i));
		fill_one_word(&(split[i]), word_len, command + k);
		if (k + word_len < size && ft_isspace(command[k + word_len]))
			split[i].space = 1;
		k += word_len;
		i++;
	}
	return (0);
}

static int	add_virtual_spaces(t_split *split, int words)
{
	int		i;
	char	c;
	int		redir;

	i = -1;
	redir = 0;
	while (++i < words)
	{
		c = split[i].sep;
		if ((c == '>' || c == '<' || c == 'd'))
		{
			if (redir)
				return (1);
			redir = 1;
			if (i > 0)
				split[i - 1].space = 1;
			split[i].space = 1;
		}
		else
			redir = 0;
	}
	return (0);
}

t_split		*parse_command(char *command, int *err)
{
	int		l;
	int		words;
	t_split	*split;

	*err = SUCCESS;
	trim_spaces(command);
	l = ft_strlen(command);
	if (l == 0)
		return (NULL);
	words = nb_words(command);
	*err = SYNTAX_QUOTES;
	if (words < 0)
		return (NULL);
	split = malloc((words + 1) * sizeof(t_split));
	*err = ALLOCATION_FAIL;
	if (!split)
		return (NULL);
	if (fill_words(split, words, command) < 0)
		return (NULL);
	split[words].str = NULL;
	split[words].sep = '\0';
	*err = SYNTAX_REDIR;
	if (add_virtual_spaces(split, words) && free_split(split, words))
		return (NULL);
	return (split);
}
