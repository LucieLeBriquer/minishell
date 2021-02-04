/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 10:14:10 by lle-briq          #+#    #+#             */
/*   Updated: 2020/10/20 10:14:20 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftfull.h"

void	*ft_bzero(void *s, size_t n)
{
	unsigned char	*mem;
	size_t			i;

	mem = (unsigned char *)s;
	i = -1;
	while (++i < n)
		mem[i] = '\0';
	return (s);
}
