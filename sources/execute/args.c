/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 18:02:50 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/18 15:38:18 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			number_of_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int			create_tab_args(t_info *cmd)
{
	char	c;
	int		i;
	int		j;

	cmd->argv = malloc((cmd->nb_args + 1) * sizeof(char *));
	if (!(cmd->argv))
		return (error_msg(ALLOCATION_FAIL));
	i = 0;
	j = cmd->offset;
	while (j < cmd->nb_args)
	{
		c = cmd->seps[j];
		if (c == 'd' || c == '>' || c == '<')
			j++;
		else
		{
			cmd->argv[i] = cmd->args[j];
			i++;
		}
		j++;
	}
	cmd->argv[i] = NULL;
	return (SUCCESS);
}

static int	count_arg(t_info cmd, t_split *split)
{
	int	nb_arg;
	int	i;

	nb_arg = 0;
	i = -1;
	while (++i < cmd.number)
	{
		if (split[cmd.start + i].space)
			nb_arg++;
	}
	if (!split[cmd.start + i].str)
		nb_arg++;
	return (nb_arg);
}

static void	fill_args(t_info cmd, t_split *split)
{
	int		i;
	int		j;
	int		end;
	char	*current;
	char	*save;

	i = -1;
	j = 0;
	while (++i < cmd.nb_args)
	{
		end = 0;
		current = ft_strdup("");
		while (j < cmd.number && !end)
		{
			save = current;
			current = ft_strjoin(cmd.args[i], split[cmd.start + j].str);
			free(save);
			if (split[cmd.start + j].space)
				end = 1;
			j++;
		}
		cmd.args[i] = ft_strdup(current);
		cmd.seps[i] = split[cmd.start + j - 1].sep;
		free(current);
	}
	cmd.args[i] = NULL;
}

int			join_words(t_info *cmd, t_split *split)
{
	cmd->nb_args = count_arg(*cmd, split);
	cmd->args = malloc((cmd->nb_args + 1) * sizeof(char *));
	cmd->seps = malloc((cmd->nb_args + 1) * sizeof(char));
	if (!(cmd->args) || !(cmd->seps))
		return (-1);
	fill_args(*cmd, split);
	return (0);
}
