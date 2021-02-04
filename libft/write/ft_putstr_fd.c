/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 15:36:13 by lle-briq          #+#    #+#             */
/*   Updated: 2020/11/23 15:39:54 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftfull.h"
#include <unistd.h>

void	ft_putstr_fd(char *s, int fd)
{
	size_t	l;

	if (!s)
		return ;
	l = ft_strlen(s);
	write(fd, s, l);
}
