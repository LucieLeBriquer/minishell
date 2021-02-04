/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_0chr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 18:23:35 by lle-briq          #+#    #+#             */
/*   Updated: 2020/12/30 15:07:22 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftfull.h"

int	print_0chr(t_print param, va_list args)
{
	char	c;
	char	*to_print;
	int		size;
	int		i;

	c = va_arg(args, int);
	size = 1;
	if (param.field > 0)
		size = param.field;
	to_print = malloc((size + 1)*sizeof(char));
	if (!to_print)
		return (0);
	i = -1;
	while (++i < size)
		to_print[i] = ' ';
	to_print[size] = '\0';
	if (param.align)
		to_print[0] = c;
	else
		to_print[size - 1] = c;
	write(1, to_print, size);
	free(to_print);
	return (size);
}
