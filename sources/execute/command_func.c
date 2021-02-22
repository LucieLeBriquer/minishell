#include "minishell.h"

int	exec_builtin(t_info *cmd, t_split *split, t_list **envl)
{
	t_exec	builtin[NB_BUILTIN];

	builtin[ECHO] = &ft_echo; 
	builtin[CD] = &ft_cd; 
	builtin[PWD] = &ft_pwd; 
	builtin[EXPORT] = &ft_export; 
	builtin[UNSET] = &ft_unset; 
	builtin[ENV] = &ft_env; 
	builtin[EXIT] = &ft_exit; 
	return (builtin[cmd->builtin](cmd, split, envl));
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

int	exec_executable(t_info *cmd, t_split *split, t_list **envl)
{
	char	**args;
	int		pid;
	int		status;
	char	**env;

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
	free(env);
	return (0);
}

char	*join_all_arguments(t_split *split, int start, int number)
{
	int		i;
	char	*join;
	char	*last;

	join = ft_strdup(split[start].str);
	i = 0;
	while (++i < number)
	{
		last = join;
		join = ft_strjoin(last, split[start + i].str);
		free(last);
	}
	return (join);
}

int	exec_declaration(t_info *cmd, t_split *split, t_list **envl)
{
	t_list	*new;
	t_list	*beg;

	new = *envl;
	if (!authorized_char(split[cmd->start].str))
		return (-1);
	while (new)
	{
		if (variable_match(new, split[cmd->start].str))
		{
			((t_env *)new->content)->var = join_all_arguments(split, cmd->start, cmd->number);
			if (((t_env *)new->content)->exported == 1)
				((t_env *)new->content)->exported = 2;
			return (0);
		}
		new = new->next;
	}
	new = init_entry(split[cmd->start].str, 0);
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

	env = create_env_tab(*envl, 0);
	if (open_executable(cmd, split, env, &file) < 0)
		return (-1);
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
		free_tab(args);
		close_unused_fd(cmd);
		print_child_end(status);
	}
	free(file);
	free(env);
	return (0);
}
