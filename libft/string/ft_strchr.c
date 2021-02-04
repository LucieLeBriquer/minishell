/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 11:21:33 by lle-briq          #+#    #+#             */
/*   Updated: 2020/10/20 11:21:50 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftfull.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	n;
	size_t	i;
	char	*str;

	n = ft_strlen(s);
	i = 0;
	str = (char *)s;
	while (i < n)
	{
		if (s[i] == (unsigned char)c)
			return (str + i);
		i++;
	}
	if (c == 0)
		return (str + n);
	return (NULL);
}
