/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 19:48:01 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/04 14:10:51 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*static int	is_builtin(char *str)
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

void	join_first(t_info *cmd, t_split *split)
{
	char	*join;
	char	*tmp;
	int		end;
	int		i;

	join = ft_strdup("");
	end = 0;
	i = 0;
	while (i < cmd->number && !end)
	{
		tmp = join;
		join = ft_strjoin(tmp, split[cmd->start + i].str);
		free(tmp);
		if (split[cmd->start + i].space)
			end = 1;
		i++;
	}
	cmd->start_args = cmd->start + i;
	cmd->nb_args = cmd->number - i + 1;
	cmd->first_word = join;
	return ;
}

static int	cmd_type(t_info *cmd, t_split *split)
{
	join_first(cmd, split);
	cmd->builtin = is_builtin(cmd->first_word);
	if (cmd->builtin > -1)
		return (BUILTIN);
	if (ft_strchr(cmd->first_word, '='))
		return (DECLARATION);
	if (is_path(cmd->first_word))
		return (EXECUTABLE);
	else
		return (EXECBIN);
}*/

void		print_words(char **args)
{
	int	i;

	i = 0;
	ft_printf("WORD LIST\n");
	while (args[i])
	{
		ft_printf("%s\n", args[i]);
		i++;
	}
}

void		execute_cmd(t_info *cmd, t_split *split, t_list **envl)
{
	t_exec	exec_func[NB_TYPES];

	exec_func[BUILTIN] = &exec_builtin;
	exec_func[EXECUTABLE] = &exec_executable;
	exec_func[DECLARATION] = &exec_declaration;
	exec_func[EXECBIN] = &exec_execbin;
	print_leave(*cmd, split);
	expand(cmd, split, *envl);
	if (join_words(cmd, split))
		return ;
	print_words(cmd->args);
	return ;
	if (update_in_out(cmd, split) < 0)
	{
		if (cmd->err)
			ft_printf("minishell: %s: %s\n", cmd->file_error,\
				strerror(cmd->err));
		else
			ft_putstr("minishell: syntax error near unexpected token \
			`newline'\n");
		return ;
	}
	//err = (exec_func[cmd_type(cmd, split)])(cmd, split, envl);
	//if (g_print_all == 0)
//		return ;
//	ft_printf("%serr = %d%s\n", GREY, err, WHITE);
}
