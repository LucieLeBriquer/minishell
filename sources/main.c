/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 16:19:31 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/21 16:19:32 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		handler(int signo)
{
	if (g_signal != 6)
		ft_putstr("\b\b  \b\b");
	if (signo == SIGINT && (g_signal != 6))
	{
		ft_putstr("\n");
		if (g_signal != 5)
			prompt();
		g_signal = 2;
	}
	else if (signo == SIGQUIT && (g_signal != 6))
	{
		if (g_signal == 5)
			ft_putstr("\b\b  \b\bQuit (core dumped)\n");
		g_signal = 3;
	}
}

static void	parse_and_exec(t_list **envl, char *line)
{
	int		err;
	t_error	error;
	t_split	*split;

	err = 0;
	split = parse_command(line, &error);
	if (!split)
	{
		print_error_parsing(error);
		if (error.num != SUCCESS)
			update_return(envl, ERROR);
	}
	else
	{
		err = execute(split, envl, line);
		update_return(envl, err);
		update_last_arg(envl, NULL, split);
	}
	update_env(envl);
	free_all(line, split);
	prompt();
}

static int	waiting_command(t_list **envl)
{
	char	*line;

	signal(SIGINT, &handler);
	signal(SIGQUIT, &handler);
	line = NULL;
	g_signal = 0;
	update_return(envl, 0);
	prompt();
	while (reader(&line) > 0)
	{
		if (g_signal == 4)
			g_signal = 2;
		parse_and_exec(envl, line);
		g_signal = 0;
	}
	if (line)
		free(line);
	if (g_signal)
		return (128 + g_signal);
	return (SUCCESS);
}

int			main(int argc, char **argv, char **env)
{
	t_list	*envl;
	int		exit_value;

	(void)argv;
	(void)argc;
	header();
	parse_env(&envl, env);
	exit_value = waiting_command(&envl);
	if (!exit_value)
		exit_value = get_return(envl);
	ft_lstclear(&envl, &free_entry);
	ft_putstr("exit\n");
	return (exit_value);
}
