/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 11:16:47 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/01 20:32:44 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftfull.h"
#include <stdlib.h>

static int	issep(char c, const char *charset)
{
	size_t	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

char		*ft_strtrim(const char *s1, const char *set)
{
	size_t	size;
	size_t	i;
	size_t	j;
	char	*trim;

	i = 0;
	if (!s1)
		return (NULL);
	while (s1[i] && issep(s1[i], set))
		i++;
	size = ft_strlen(s1);
	while (size > 0 && issep(s1[size - 1], set))
		size--;
	if (size == 0)
		trim = malloc(sizeof(char));
	else
		trim = malloc(sizeof(char) * (size - i + 1));
	if (!trim)
		return (NULL);
	j = -1;
	while (i + ++j < size)
		trim[j] = s1[i + j];
	trim[j] = '\0';
	return (trim);
}
