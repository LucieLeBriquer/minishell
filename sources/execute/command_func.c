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
	if (PRINT_ALL == 1)
		ft_printf("\t> Builtin\n");
	return (builtin[cmd->builtin](cmd, split, env));
}

void	change_stdin_stdout(t_info *cmd)
{
	if (cmd->output != 1)
	{
		close(1);
		dup2(cmd->output, 1);
	}
	if (cmd->input != 0)
	{
		close(0);
		dup2(cmd->input, 0);
	}
}

int	exec_executable(t_info *cmd, t_split *split, char **env)
{
	char	**args;
	int		pid;
	int		status;

	if (PRINT_ALL == 1)
		ft_printf("\t> Executable\n");
	pid = fork();
	args = NULL;
	if (pid == 0)
	{
		change_stdin_stdout(cmd);
		args = create_tab_args(cmd, split);
		execve(split[cmd->start].str, args, env);
	}
	else
	{
		wait(&status);
		free_tab(args);
		close_unused_fd(cmd);
		print_child_end(status);
	}
	return (0);
}

int	exec_declaration(t_info *cmd, t_split *split, char **env)
{
	(void)cmd;
	(void)split;
	(void)env;
	if (PRINT_ALL == 1)
		ft_printf("\t> Declaration\n");
	return (0);
}

int	exec_execbin(t_info *cmd, t_split *split, char **env)
{
	int		fd;
	char	*file;
	char	**args;
	int		pid;
	int		status;

	if (PRINT_ALL == 1)
		ft_printf("\t> Execbin\n");
	fd = open_executable(cmd, split, env, &file);
	if (fd < 0)
		return (-1);
	close(fd);
	args = NULL;
	pid = fork();
	if (pid == 0)
	{
		change_stdin_stdout(cmd);
		args = create_tab_args(cmd, split);
		execve(file, args, env);
	}
	else
	{
		wait(&status);
		free(file);
		free_tab(args);
		close_unused_fd(cmd);
		print_child_end(status);
	}
	return (0);
}
