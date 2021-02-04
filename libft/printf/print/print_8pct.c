/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_8pct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 21:51:09 by lle-briq          #+#    #+#             */
/*   Updated: 2020/12/30 15:11:36 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftfull.h"

int	print_8pct(t_print param, va_list args)
{
	int		size;
	char	*to_print;
	int		i;

	(void)args;
	size = 1;
	if (param.field > 0)
		size = param.field;
	to_print = malloc(size * sizeof(char));
	if (!to_print)
		return (0);
	i = -1;
	while (++i < size)
	{
		to_print[i] = ' ';
		if (param.zero && !param.align)
			to_print[i] = '0';
	}
	if (param.align)
		to_print[0] = '%';
	else
		to_print[size - 1] = '%';
	write(1, to_print, size);
	free(to_print);
	return (size);
}
