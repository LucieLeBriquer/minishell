/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:39:04 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/16 17:14:50 by lle-briq         ###   ########.fr       */
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

void	print_leave(t_info cmd, t_split *split, int j)
{
	int	i;

	if (g_print_all == 0)
		return ;
	if (j == 0)
	{
		ft_putstr("\n");
		print_title("EXECUTE");
		ft_printf("\t\xE2\xAE\x9f%4d   ", cmd.input);
		ft_printf("\xE2\xAE\x9D%4d\t", cmd.output);
		ft_printf("sub=%d\t", cmd.is_subprocess);
	}
	else
		ft_printf("\t%safter expansion  \t", GREY);
	i = -1;
	while (++i + 1 < cmd.number)
		ft_printf("%s ", split[cmd.start + i].str);
	if (cmd.number)
		ft_printf("%s", split[cmd.start + i].str);
	ft_putstr("\n");
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

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		ft_printf("\t[%s]\n", tab[i]);
		i++;
	}
}

void	print_tabs(t_info cmd, int join)
{
	int	i;

	i = 0;
	if (join == 0)
	{
		while (cmd.args_tmp[i] && cmd.seps_tmp[i])
		{
			ft_printf("\t[%s] [%c] [%d]\n", cmd.args_tmp[i], cmd.seps_tmp[i], cmd.spaces_tmp[i]);
			i++;
		}
	}
	else
	{
		while (cmd.args[i] && cmd.seps[i])
		{
			ft_printf("\t[%s] [%c]\n", cmd.args[i], cmd.seps[i]);
			i++;
		}
	}
}

void	print_expand(t_info cmd)
{
	int	i;

	i = -1;
	while (++i < cmd.nb_args)
		ft_printf("[%c] [%s]\n", cmd.seps[i], cmd.args[i]);
}
