/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_1str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 18:59:13 by lle-briq          #+#    #+#             */
/*   Updated: 2020/12/30 15:07:38 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftfull.h"

static int	size_str(t_print param, int len)
{
	if (param.precision == -1 || param.precision >= len)
		return (ft_max(param.field, len) + 1);
	return (ft_max(param.precision, param.field) + 1);
}

static int	print_1str_null(t_print param)
{
	char	*str;
	char	*to_print;
	int		size;

	str = "(null)";
	size = size_str(param, ft_strlen(str));
	to_print = malloc(size * sizeof(char));
	if (!to_print)
		return (0);
	fill_str_s(&to_print, str, param, size);
	write(1, to_print, size - 1);
	free(to_print);
	return (size - 1);
}

int	print_1str(t_print param, va_list args)
{
	char	*str;
	char	*to_print;
	int		size;
	int		len;

	str = va_arg(args, char *);
	if (!str)
		return (print_1str_null(param));
	len = ft_strlen(str);
	size = size_str(param, len);
	if (size == 0)
		return (0);
	to_print = malloc(size * sizeof(char));
	if (!to_print)
		return (0);
	fill_str_s(&to_print, str, param, size);
	write(1, to_print, size - 1);
	free(to_print);
	return (size - 1);
}
