/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 11:26:19 by lle-briq          #+#    #+#             */
/*   Updated: 2020/11/16 14:31:46 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftfull.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	b;
	size_t	l;

	i = 0;
	b = ft_strlen(big);
	l = ft_strlen(little);
	if (l == 0)
		return ((char *)big);
	if (len <= 0 || b < l)
		return (NULL);
	while (big[i])
	{
		j = 0;
		while (i + j < len && i + j < b && j < l && big[i + j] == little[j])
			j++;
		if (j == len || j == l)
			return ((char *)big + i);
		i++;
	}
	return (NULL);
}
