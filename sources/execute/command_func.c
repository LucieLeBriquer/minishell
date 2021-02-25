#include "minishell.h"

int	exec_builtin(t_info *cmd, t_split *split, t_list **envl)
{
	t_exec	builtin[NB_BUILTIN];

	if (PRINT_ALL)
		ft_printf("> builtin\n");
	builtin[ECHO] = &ft_echo; 
	builtin[CD] = &ft_cd; 
	builtin[PWD] = &ft_pwd; 
	builtin[EXPORT] = &ft_export; 
	builtin[UNSET] = &ft_unset; 
	builtin[ENV] = &ft_env; 
	builtin[EXIT] = &ft_exit; 
	return (builtin[cmd->builtin](cmd, split, envl));
}

int	exec_executable(t_info *cmd, t_split *split, t_list **envl)
{
	char	**args;
	int		pid;
	int		status;
	int		fd;
	char	**env;

	if (PRINT_ALL)
		ft_printf("> executable\n");
	fd = open(split[cmd->start].str, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("minishell: %s: %s\n", split[cmd->start].str, strerror(2));
		return (-1);
	}
	close(fd);
	env = create_env_tab(*envl, 0);
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
	free_tab(env);
	return (0);
}

int	exec_declaration(t_info *cmd, t_split *split, t_list **envl)
{
	t_list	*new;
	t_list	*beg;
	char	*var;

	if (PRINT_ALL)
		ft_printf("> declaration\n");
	new = *envl;
	if (!authorized_char(split[cmd->start].str))
		return (-1);
	var = ft_strcut(split[cmd->start].str, '=');
	while (new)
	{
		if (variable_match(new, var))
		{
			((t_env *)new->content)->value = join_all_arguments(split, cmd->start, cmd->number);
			if (((t_env *)new->content)->exported == 1)
				((t_env *)new->content)->exported = 2;
			free(var);
			return (0);
		}
		new = new->next;
	}
	new = init_entry(var, 0);
	free(var);
	((t_env *)new->content)->value = join_all_arguments(split, cmd->start, cmd->number);
	beg = *envl;
	while (beg && beg->next)
		beg = beg->next;
	beg->next = new;
	return (0);
}

int	exec_execbin(t_info *cmd, t_split *split, t_list **envl)
{
	char	*file;
	char	**args;
	int		pid;
	int		status;
	char	**env;

	if (PRINT_ALL)
		ft_printf("> execbin\n");
	if (open_executable(cmd, split, *envl, &file) < 0)
	{
		ft_printf("minishell: %s: command not found\n", split[cmd->start].str);
		return (-1);
	}
	args = NULL;
	pid = fork();
	env = create_env_tab(*envl, 0);
	if (pid == 0)
	{
		change_stdin_stdout(cmd);
		args = create_tab_args(cmd, split);
		execve(file, args, env);
	}
	else
	{
		wait(&status);
		free_tab(args);
		close_unused_fd(cmd);
		print_child_end(status);
	}
	free(file);
	free_tab(env);
	return (0);
}
