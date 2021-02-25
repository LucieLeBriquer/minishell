/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 16:08:17 by lle-briq          #+#    #+#             */
/*   Updated: 2021/02/25 16:49:29 by lle-briq         ###   ########.fr       */
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

static int	fill_words(t_split *split, int words, char *command)
{
	int		i;
	int		k;
	int		word_len;
	char	sep;
	int		size;

	i = 0;
	k = 0;
	size = ft_strlen(command);
	while (i < words)
	{
		word_len = len_of_word(command + k, &sep);
		split[i].quote = sep;
		split[i].str = malloc((word_len + 2) * sizeof(char));
		if (!split[i].str)
			return (free_split(split, i));
		ft_strlcpy(split[i].str, command + k, word_len + 1);
		split[i].space = 0;
		if (k + word_len < size && command[k + word_len] == ' ')
			split[i].space = 1;
		split[i].str[word_len + 1] = '\0';
		trim_useless(split[i]);
		k += word_len;
		i++;
	}
	while (--i >= 0)
	{
		if (split[i].str[0] == '\0')
		{
			free(split[i].str);
			split[i].str = NULL;
		}
	}
	return (0);
}

t_split	*parse_command(char *command, int *err)
{
	int		l;
	int		words;
	t_split	*split;

	trim_spaces_right(command);
	trim_spaces_left(command);
	*err = 0;
	l = ft_strlen(command);
	if (l == 0)
		return (NULL);
	words = nb_words(command, l);
	*err = 1;
	if (words < 0)
		return (NULL);
	split = malloc((words + 1) * sizeof(t_split));
	*err = 2;
	if (!split)
		return (NULL);
	if (fill_words(split, words, command) < 0)
		return (NULL);
	split[words].str = NULL;
	return (split);
}
