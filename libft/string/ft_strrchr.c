/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 11:22:15 by lle-briq          #+#    #+#             */
/*   Updated: 2020/10/20 11:22:27 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftfull.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	n;
	size_t	i;
	char	*str;
	char	*ret;

	n = ft_strlen(s);
	i = 0;
	str = (char *)s;
	ret = NULL;
	while (i < n)
	{
		if (s[i] == (unsigned char)c)
			ret = str + i;
		i++;
	}
	if (c == 0)
		return (str + n);
	return (ret);
}
