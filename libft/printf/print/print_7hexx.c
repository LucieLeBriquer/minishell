/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_7hexx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 21:51:09 by lle-briq          #+#    #+#             */
/*   Updated: 2021/02/11 17:42:00 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftfull.h"

int	print_7hxx(t_print param, va_list args)
{
	unsigned int	nb;
	int				size;
	char			*nb_utoxx;
	char			*to_print;

	nb = (unsigned int)va_arg(args, int);
	nb_utoxx = ft_utoxx(nb);
	if (nb == 0 && param.precision == 0)
		nb_utoxx[0] = '\0';
	size = size_int(param, nb_utoxx);
	to_print = malloc(size * sizeof(char));
	if (!to_print)
		return (0);
	fill_int(&to_print, nb_utoxx, param, size);
	free(nb_utoxx);
	ft_putstr_fd(to_print, param.fd);
	free(to_print);
	return (size - 1);
}
