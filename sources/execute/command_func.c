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
	char	**args;
	int		status;
	int		test;

	ft_printf("\t> Executable\n");
	status = fork();
	if (status == 0)
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
		args = create_tab_args(cmd, split);
		execve(split[cmd->start].str, args, env);
	}
	else
	{
		if (cmd->input != 0)
			close(cmd->input);
		if (cmd->output != 1)
			close(cmd->output);
		wait(&test);
		ft_printf("\033[32mchild process finished\033[0m\n");
	}
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
	close(fd);
	status = fork();
	if (status == 0)
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
		args = create_tab_args(cmd, split);
		execve(file, args, env);
	}
	else
	{
		if (cmd->input != 0)
			close(cmd->input);
		if (cmd->output != 1)
			close(cmd->output);
		wait(&test);
		ft_printf("\033[32mchild process finished\033[0m\n");
	}
	return (0);
}

/*
** maybe ajouter test (à renommer) à la structure de cmd avec un status qui indique si le child process est finito
*/
