/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:39:04 by lle-briq          #+#    #+#             */
/*   Updated: 2021/02/17 17:32:02 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error_parsing(int err)
{
	if (err == 0)
		return ;
	if (err == 1)
		ft_printf("Wrong format\n");
	else if (err == 2)
		ft_printf("Allocation issue\n");
}

void	print_parsed_command(t_split *split)
{
	int		i;

	if (PRINT_ALL == 0)
		return ;
	ft_printf("\033[33mPARSING\033[0m\n");
	i = 0;
	while (split[i].str)
	{
		ft_printf("\t[%c] [%s]\n", split[i].quote, split[i].str);
		i++;
	}
	ft_printf("\n");
}

void	print_child_end(int status)
{
	if (PRINT_ALL == 0)
		return ;
	ft_printf("\033[32mchild process finished [%d]\033[0m\n", status);
}

