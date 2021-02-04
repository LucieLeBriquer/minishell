/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 11:09:48 by lle-briq          #+#    #+#             */
/*   Updated: 2020/11/23 15:38:10 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftfull.h"
#include <unistd.h>

void	ft_putendl(char *s)
{
	size_t	l;

	if (!s)
		return ;
	l = ft_strlen(s);
	write(0, s, l);
	write(0, "\n", 1);
}
