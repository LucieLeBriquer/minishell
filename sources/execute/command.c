/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 19:48:01 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/01 19:48:08 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_declaration(char *str, char sep)
{
	if (sep == '=' && authorized_char(str))
		return (1);
	return (0);
}

static int	is_builtin(char *str)
{
	if (ft_strcmp(str, "echo") == 0)
		return (ECHO);
	if (ft_strcmp(str, "cd") == 0)
		return (CD);
	if (ft_strcmp(str, "pwd") == 0)
		return (PWD);
	if (ft_strcmp(str, "export") == 0)
		return (EXPORT);
	if (ft_strcmp(str, "unset") == 0)
		return (UNSET);
	if (ft_strcmp(str, "env") == 0)
		return (ENV);
	if (ft_strcmp(str, "exit") == 0)
		return (EXIT);
	return (-1);
}

static int	cmd_type(char *first_word, char sep, t_info *cmd)
{
	cmd->builtin = is_builtin(first_word);
	(void)sep;
	if (is_declaration(first_word, sep))
		return (DECLARATION);
	if (cmd->builtin > -1)
		return (BUILTIN);
	else if (is_path(first_word))
		return (EXECUTABLE);
	else
		return (EXECBIN);
}

void		execute_cmd(t_info *cmd, t_split *split, t_list **envl)
{
	t_exec	exec_func[NB_TYPES];
	int		err;

	exec_func[BUILTIN] = &exec_builtin;
	exec_func[EXECUTABLE] = &exec_executable;
	exec_func[DECLARATION] = &exec_declaration;
	exec_func[EXECBIN] = &exec_execbin;
	err = update_in_out(cmd, split);
	if (err == -1)
	{
		ft_printf("parse error\n");
		return ;
	}
	if (err < -1)
	{
		ft_printf("file error\n");
		return ;
	}
	print_leave(*cmd, split);
	expand(cmd, split, *envl);
	err = (exec_func[cmd_type(split[cmd->start].str, \
		split[cmd->start + 1].sep, cmd)])(cmd, split, envl);
	if (g_print_all == 0)
		return ;
	ft_printf("\terr = %d\n", err);
}
