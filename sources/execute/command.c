/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 19:48:01 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/04 17:25:36 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	cmd_type(t_info *cmd)
{
	cmd->builtin = is_builtin(cmd->args[0]);
	if (cmd->builtin > -1)
		return (BUILTIN);
	if (ft_strchr(cmd->args[0], '='))
		return (DECLARATION);
	if (is_path(cmd->args[0]))
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
	print_leave(*cmd, split);
	expand(cmd, split, *envl);
	if (join_words(cmd, split))
		return ;
	if (update_in_out(cmd) < 0)
	{
		if (cmd->err)
			ft_printf("minishell: %s: %s\n", cmd->file_error,\
				strerror(cmd->err));
		else
			ft_putstr("minishell: syntax error near unexpected token \
			`newline'\n");
		return ;
	}
	err = (exec_func[cmd_type(cmd)])(cmd, envl);
	if (g_print_all == 0)
		return ;
	ft_printf("%serr = %d%s\n", GREY, err, WHITE);
}

/*
** changer le type de cette fonction pour faire un retour d'erreur
*/
