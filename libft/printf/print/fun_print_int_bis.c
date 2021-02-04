/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fun_print_int_bis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 21:51:09 by lle-briq          #+#    #+#             */
/*   Updated: 2020/11/28 23:42:02 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftfull.h"

void	fill_int_right_p(char **to_print, char *nb, t_print param, int size)
{
	int		len;
	int		sg;
	int		i;

	len = ft_strlen(nb);
	sg = (nb[0] == '-');
	i = len;
	while (--i >= sg)
		(*to_print)[size - len + i - 1] = nb[i];
	i = size - param.precision - 1;
	if (sg)
		(*to_print)[i - 1] = '-';
	i--;
	while (++i < size + sg - len - 1)
		(*to_print)[i] = '0';
	i = -1;
	while (++i < size - param.precision - 1 - sg)
		(*to_print)[i] = ' ';
}

void	fill_int_right(char **to_print, char *nb, int size)
{
	int		len;
	int		i;
	int		j;

	i = -1;
	while (++i < size)
		(*to_print)[i] = ' ';
	len = ft_strlen(nb);
	i = len;
	j = size - 1;
	while (--i >= 0 && --j >= 0)
		(*to_print)[j] = nb[i];
}

void	fill_int_left_p(char **to_print, char *nb, t_print param, int size)
{
	int		len;
	int		sg;
	int		i;
	int		j;
	int		nb_zero;

	len = ft_strlen(nb);
	sg = (nb[0] == '-');
	if (sg)
		(*to_print)[0] = '-';
	nb_zero = param.precision - len + sg;
	i = sg - 1;
	while (nb_zero > 0 && ++i < nb_zero + sg)
		(*to_print)[i] = '0';
	j = -1;
	while (++j + sg < len)
		(*to_print)[i + j] = nb[sg + j];
	while (i + j < size - 1)
		(*to_print)[i + j++] = ' ';
}

void	fill_int_left(char **to_print, char *nb, int size)
{
	int		len;
	int		i;

	len = ft_strlen(nb);
	i = -1;
	while (++i < len)
		(*to_print)[i] = nb[i];
	while (i < size - 1)
		(*to_print)[i++] = ' ';
}

void	fill_int_zero(char **to_print, char *nb, int size)
{
	int		len;
	int		i;
	int		sg;

	i = -1;
	sg = (nb[0] == '-');
	len = ft_strlen(nb);
	while (++i < size - 1)
		(*to_print)[i] = '0';
	i = -1;
	if (sg)
	{
		(*to_print)[0] = '-';
		i++;
	}
	while (++i <= len - sg)
		(*to_print)[size - 1 - i] = nb[len - i];
}
