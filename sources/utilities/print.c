/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:39:04 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/02 20:05:35 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_title(char *s)
{
	ft_putstr(COLOR);
	ft_putstr(SQUARE);
	ft_putstr(s);
}

void	print_parsed_command(t_split *split)
{
	int		i;

	if (g_print_all == 0)
		return ;
	print_title("PARSING\n");
	ft_putstr(WHITE);
	i = 0;
	while (split[i].str)
	{
		ft_printf("\t[%c] [%d] [%s]\n", split[i].sep,
			split[i].space, split[i].str);
		i++;
	}
	ft_printf("\n");
}

void	print_child_end(int status)
{
	if (g_print_all == 0)
		return ;
	ft_putstr("\n");
	print_title("DONE");
	ft_printf("\t\t%d\n\n", status);
}

void	print_leave(t_info cmd, t_split *split)
{
	int	i;

	if (g_print_all == 0)
		return ;
	ft_putstr("\n");
	print_title("EXECUTE");
	ft_printf("\t\xE2\xAE\x9f%2d   ", cmd.input);
	ft_printf("\xE2\xAE\x9D%2d\t", cmd.output);
	i = -1;
	while (++i + 1 < cmd.number)
		ft_printf("%s ", split[cmd.start + i].str);
	ft_printf("%s\n", split[cmd.start + i].str);
	ft_putstr(WHITE);
}

void	print_tree(t_tree *tree, t_split *split)
{
	int	i;

	if (tree == NULL)
		return ;
	print_tree(tree->left, split);
	ft_printf("type : %d\t%d[%d]\t", tree->info->type, \
			tree->info->start, tree->info->number);
	ft_printf("operator : %c\t", split[tree->info->start].sep);
	i = -1;
	while (++i < tree->info->number)
		ft_printf("%s ", split[tree->info->start + i].str);
	ft_printf("\n");
	print_tree(tree->right, split);
}
