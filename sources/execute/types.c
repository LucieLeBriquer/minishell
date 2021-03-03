/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 19:49:15 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/03 18:50:33 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			exec_builtin(t_info *cmd, t_split *split, t_list **envl)
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

int			exec_executable(t_info *cmd, t_split *split, t_list **envl)
{
	int		fd;

	fd = open(split[cmd->start].str, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("minishell: %s: %s\n", split[cmd->start].str, strerror(2));
		return (-1);
	}
	close(fd);
	fork_and_exec(cmd, split, *envl, NULL);
	return (0);
}

static int	export_var(t_env *env_var, t_info *cmd, t_split *split)
{
	env_var->value = join_all_arguments(split, cmd->start, cmd->number);
	if (env_var->exported == 1)
		env_var->exported = 2;
	return (0);
}

int			exec_declaration(t_info *cmd, t_split *split, t_list **envl)
{
	t_list	*new;

	new = *envl;
	while (new)
	{
		if (variable_match(new, split[cmd->start].str, 0))
			return (export_var(new->content, cmd, split));
		new = new->next;
	}
	new = init_entry(split[cmd->start].str, 0);
	((t_env *)new->content)->value = join_all_arguments(split,
		cmd->start, cmd->number);
	ft_lstadd_back(envl, new);
	return (0);
}

int			exec_execbin(t_info *cmd, t_split *split, t_list **envl)
{
	char	*file;

	if (open_executable(cmd, split, *envl, &file) < 0)
	{
		ft_printf("minishell: %s: command not found\n", split[cmd->start].str);
		return (-1);
	}
	fork_and_exec(cmd, split, *envl, file);
	free(file);
	return (0);
}
