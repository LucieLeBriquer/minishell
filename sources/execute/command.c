#include "minishell.h"

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

int		is_declaration(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int		is_builtin(char *str)
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

int		cmd_type(char *first_word, t_info *cmd)
{
	cmd->builtin = is_builtin(first_word);
	if (cmd->builtin > -1)
		return (BUILTIN);
	else if (is_path(first_word))
		return (EXECUTABLE);
	else if (is_declaration(first_word))
		return (DECLARATION);
	else
		return (EXECBIN);
}

void	execute_cmd(t_info *cmd, t_split *split, t_list **envl)
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
	expand_db(cmd, split, *envl);
	err = (exec_func[cmd_type(split[cmd->start].str, cmd)])(cmd, split, envl);
	if (PRINT_ALL == 0)
		return ;
	ft_printf("\terr = %d\n", err);
}
