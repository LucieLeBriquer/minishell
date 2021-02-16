#include "minishell.h"

int	exec_builtin(t_info *cmd, t_split *split, char **env)
{
	t_exec	builtin[NB_BUILTIN];
	
	builtin[ECHO] = &ft_echo; 
	builtin[CD] = &ft_cd; 
	builtin[PWD] = &ft_pwd; 
	builtin[EXPORT] = &ft_export; 
	builtin[UNSET] = &ft_unset; 
	builtin[ENV] = &ft_env; 
	builtin[EXIT] = &ft_exit; 
	return (builtin[cmd->builtin](cmd, split, env));
}

int	exec_executable(t_info *cmd, t_split *split, char **env)
{
	(void)cmd;
	(void)split;
	(void)env;
	ft_printf("\t> Executable ./\n");
	return (0);
}

int	exec_declaration(t_info *cmd, t_split *split, char **env)
{
	(void)cmd;
	(void)split;
	(void)env;
	ft_printf("\t> Declaration\n");
	return (0);
}

int	exec_execbin(t_info *cmd, t_split *split, char **env)
{
	int		fd;
	char	*file;
	char	**args;
	int		status;
	int		test;

	fd = open_executable(cmd, split, env, &file);
	if (fd < 0)
		return (-1);
	status = fork();
	if (status == 0)
	{
		close(fd);
		if (cmd->output != 1)
		{
			close(1);
			dup(cmd->output);
			close(cmd->input);
			close(cmd->output);
		}
		args = create_tab_args(cmd, split);
		args[1] = NULL;
		execve(file, args, env);
	}
	else
	{
		wait(&test);
	}
	return (0);
}
