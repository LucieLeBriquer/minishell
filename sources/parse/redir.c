/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 18:39:05 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/01 19:57:26 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	fill_input(t_info *cmd, t_split *split, int i)
{
	if (++i >= cmd->number || cmd->input != 0)
		return (-1);
	cmd->input = open(split[cmd->start + i].str, O_RDONLY);
	return (0);
}

static int	fill_out(t_info *cmd, t_split *split, int i)
{
	if (++i >= cmd->number || cmd->output != 1)
		return (-1);
	cmd->output = open(split[cmd->start + i].str, O_WRONLY
			| O_CREAT | O_TRUNC, 0666);
	return (0);
}

static int	fill_app(t_info *cmd, t_split *split, int i)
{
	if (++i >= cmd->number || cmd->output != 1)
		return (-1);
	cmd->output = open(split[cmd->start + i].str, O_WRONLY
			| O_CREAT | O_APPEND, 0666);
	return (0);
}

int			update_in_out(t_info *cmd, t_split *split)
{
	int	i;

	i = -1;
	while (++i < cmd->number)
	{
		if (split[cmd->start + i].sep == '<' && fill_input(cmd, split, i))
			return (-1);
		else if (split[cmd->start + i].sep == '>' && fill_out(cmd, split, i))
			return (-1);
		else if (split[cmd->start + i].sep == 'd' && fill_app(cmd, split, i))
			return (-1);
	}
	if (cmd->input < 0 || cmd->output < 0)
		return (-2);
	return (0);
}
