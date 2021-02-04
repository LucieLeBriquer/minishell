/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fun_print_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 18:59:13 by lle-briq          #+#    #+#             */
/*   Updated: 2021/01/03 17:02:47 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftfull.h"

static void	fill_str_right(char **to_print, char *str, t_print param, int size)
{
	int		len;
	int		to_keep;
	int		i;

	len = ft_strlen(str);
	if (param.type == 2)
		to_keep = len;
	else
		to_keep = min_not_neg(param.precision, len);
	i = -1;
	(*to_print)[size - 1] = '\0';
	while (++i < to_keep)
		(*to_print)[size - to_keep + i - 1] = str[i];
	i = -1;
	while (++i < size - to_keep - 1)
		(*to_print)[i] = ' ';
}

static void	fill_str_left(char **to_print, char *str, t_print param, int size)
{
	int		len;
	int		to_keep;
	int		i;

	len = ft_strlen(str);
	if (param.type == 2)
		to_keep = len;
	else
		to_keep = min_not_neg(param.precision, len);
	(*to_print)[size - 1] = '\0';
	i = to_keep - 1;
	while (++i < size - 1)
		(*to_print)[i] = ' ';
	i = -1;
	while (++i < to_keep)
		(*to_print)[i] = str[i];
}

const char	*print_str_classic(const char *str, int *nb_char)
{
	char		*buf;
	const char	*save;
	int			i;

	i = 0;
	save = str;
	while (*str && (*str != '%'))
	{
		str++;
		i++;
	}
	buf = ft_substr(save, 0, i);
	if (!buf)
		return (NULL);
	ft_putstr(buf);
	free(buf);
	(*nb_char) += i;
	return (str);
}

void	fill_str_s(char **to_print, char *str, t_print param, int size)
{
	if (param.align)
		fill_str_left(to_print, str, param, size);
	else
		fill_str_right(to_print, str, param, size);
}
