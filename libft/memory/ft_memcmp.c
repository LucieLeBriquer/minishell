/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 10:17:38 by lle-briq          #+#    #+#             */
/*   Updated: 2020/12/30 14:38:33 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftfull.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*mem1;
	unsigned char	*mem2;

	mem1 = (unsigned char *)s1;
	mem2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (i < n && mem1[i] == mem2[i])
		i++;
	if (i != n)
		return (mem1[i] - mem2[i]);
	return (0);
}
