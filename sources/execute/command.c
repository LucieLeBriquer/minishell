#include "minishell.h"

void	print_leave(t_info cmd, t_split *split)
{
	int	i;

	ft_printf("EXECUTE input %d\t\t", cmd.input);
	ft_printf("output %d\t\t", cmd.output);
	i = -1;
	while (++i < cmd.number)
		ft_printf("%s ", split[cmd.start + i].str);
	ft_printf("\n");
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
	else if (ft_strcmp("./", first_word) > 0)
		return (EXECUTABLE);
	else if (is_declaration(first_word))
		return (DECLARATION);
	else
		return (EXECBIN);
}

void	execute_cmd(t_info *cmd, t_split *split, char **env)
{
	t_exec	exec_func[NB_TYPES];
	int		err;

	(void)env;
	exec_func[BUILTIN] = &exec_builtin;
	exec_func[EXECUTABLE] = &exec_executable;
	exec_func[DECLARATION] = &exec_declaration;
	exec_func[EXECBIN] = &exec_execbin;
	print_leave(*cmd, split);
	err = (exec_func[cmd_type(split[cmd->start].str, cmd)])(cmd, split, env);
	ft_printf("\terr = %d\n", err);
}
