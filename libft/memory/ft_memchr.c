/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 10:17:19 by lle-briq          #+#    #+#             */
/*   Updated: 2020/11/16 12:02:26 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftfull.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*mem;

	mem = (unsigned char *)s;
	i = -1;
	while (++i < n)
	{
		if (mem[i] == (unsigned char)c)
			return (mem + i);
	}
	return (NULL);
}
