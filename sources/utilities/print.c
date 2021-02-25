/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:39:04 by lle-briq          #+#    #+#             */
/*   Updated: 2021/02/25 12:10:32 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	print_leave(t_info cmd, t_split *split)
{
	int	i;

	if (PRINT_ALL == 0)
		return ;
	ft_printf("\033[33mEXECUTE   input %2d   ", cmd.input);
	ft_printf("output %2d\t\t", cmd.output);
	i = -1;
	while (++i < cmd.number)
		ft_printf("%s ", split[cmd.start + i].str);
	ft_printf("\n\033[0m");
}
