/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 19:51:33 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/04 17:02:10 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		number_of_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int		authorized_char(char *s)
{
	int	i;

	i = 0;
	if (!ft_isalpha(s[0]) && (s[0] != '_'))
		return (0);
	while (s[i] && (s[i] != '='))
	{
		if (!ft_isalnum(s[i]) && (s[i] != '_'))
			return (0);
		i++;
	}
	return (1);
}

int		create_tab_args(t_info *cmd)
{
	char	c;
	int		i;
	int		j;

	cmd->argv = malloc((cmd->nb_args + 1) * sizeof(char *));
	if (!(cmd->argv))
		return (-1);
	i = 0;
	j = 0;
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
	return (0);
}

int		is_path(char *word)
{
	int	i;

	i = 0;
	while (word[i])
	{
		if (word[i] == '/')
			return (1);
		i++;
	}
	return (0);
}
