/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 18:27:10 by lle-briq          #+#    #+#             */
/*   Updated: 2020/12/30 15:21:57 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftfull.h"

void	print_param(t_print param, va_list args, int *nb_char)
{
	t_func	print_fun[10];

	print_fun[0] = &print_0chr;
	print_fun[1] = &print_1str;
	print_fun[2] = &print_2ptr;
	print_fun[3] = &print_3dbl;
	print_fun[4] = &print_4int;
	print_fun[5] = &print_5uns;
	print_fun[6] = &print_6hex;
	print_fun[7] = &print_7hxx;
	print_fun[8] = &print_8pct;
	print_fun[9] = &print_9oct;
	*nb_char += (print_fun[param.type])(param, args);
}
