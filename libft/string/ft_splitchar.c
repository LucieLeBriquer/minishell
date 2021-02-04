/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitchar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 11:37:23 by lle-briq          #+#    #+#             */
/*   Updated: 2021/01/05 21:14:11 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftfull.h"
#include <stdlib.h>

static int	nb_wrds(const char *s, char c, int *i, int *j)
{
	int	k;
	int	n;

	k = 0;
	n = 0;
	*i = -1;
	*j = 0;
	while (s[k])
	{
		while (s[k] && (s[k] == c))
			k++;
		if (s[k] && (s[k] != c))
			n++;
		while (s[k] && (s[k] != c))
			k++;
	}
	return (n);
}

static int	wrd_len(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && (s[i] != c))
		i++;
	return (i);
}

static char	**ft_free(char **strs, int i)
{
	int		j;

	j = -1;
	while (++j < i)
		free(strs[j]);
	free(strs);
	return (NULL);
}

char	**ft_splitchar(const char *s, char c)
{
	char	**strs;
	int		wrds;
	int		i;
	int		j;
	int		len;

	if (!s)
		return (NULL);
	wrds = nb_wrds(s, c, &i, &j);
	strs = malloc(sizeof(char *) * (wrds + 1));
	if (!strs)
		return (NULL);
	strs[wrds] = 0;
	while (++i < wrds)
	{
		while (s[j] && (s[j] == c))
			j++;
		len = wrd_len(s + j, c);
		strs[i] = malloc(sizeof(char) * (len + 1));
		if (!(strs[i]))
			return (ft_free(strs, i));
		(void)ft_strlcpy(strs[i], s + j, len + 1);
		j += len;
	}
	return (strs);
}
