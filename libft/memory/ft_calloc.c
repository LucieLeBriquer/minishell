/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 10:11:32 by lle-briq          #+#    #+#             */
/*   Updated: 2020/11/16 18:08:00 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftfull.h"
#include <stdlib.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*ptr;
	unsigned char	*mem;
	size_t			s;
	size_t			i;

	s = nmemb * size;
	ptr = malloc(s);
	if (!ptr)
		return (NULL);
	mem = (unsigned char *)ptr;
	i = -1;
	while (++i < s)
		mem[i] = '\0';
	return (ptr);
}
