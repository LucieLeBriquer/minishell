/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 18:02:50 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/18 15:23:15 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_arg(t_info cmd)
{
	int	nb_arg;
	int	i;

	nb_arg = 0;
	i = -1;
	while (++i < cmd.nb_args_tmp)
	{
		if (cmd.spaces_tmp[i])
			nb_arg++;
	}
	return (nb_arg);
}

static void	fill_args(t_info cmd)
{
	int		i;
	int		j;
	int		end;
	char	*current;

	i = -1;
	j = 0;
	while (++i < cmd.nb_args)
	{
		end = 0;
		current = ft_strdup("");
		while (j < cmd.nb_args_tmp && !end)
		{
			cmd.args[i] = current;
			current = ft_strjoin(cmd.args[i], cmd.args_tmp[j]);
			free(cmd.args[i]);
			if (cmd.spaces_tmp[j])
				end = 1;
			j++;
		}
		cmd.args[i] = ft_strdup(current);
		cmd.seps[i] = cmd.seps_tmp[j - 1];
		free(current);
	}
	cmd.args[i] = NULL;
}

int			join_args(t_info *cmd)
{
	cmd->nb_args = count_arg(*cmd);
	cmd->args = malloc((cmd->nb_args + 1) * sizeof(char *));
	cmd->seps = malloc((cmd->nb_args + 1) * sizeof(char));
	if (!cmd->args || !cmd->seps)
		return (error_msg(ALLOCATION_FAIL, NULL));
	fill_args(*cmd);
	return (SUCCESS);
}
