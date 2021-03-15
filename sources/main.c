/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:36:55 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/15 18:52:43 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handler(int signo)
{
	ft_putstr("\b\b  \b\b");
	if (signo == SIGINT)
	{
		g_sigint = 1;
		ft_putstr("\n");
		prompt();
	}
	if (signo == SIGQUIT)
	{
		if (g_sigquit)
		{
			g_sigquit = 0;
			ft_putstr("Quit (core dumped)\n");
			// + exit 131
		}
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
		print_error_parsing(error);
	else
	{
		print_parsed_command(split);
		err = execute(split, envl, line);
	}
	add_env("?begin", ft_itoa(err), envl, -1);
	free_all(line, split);
	if (!g_sigint)
		prompt();
}

static int	waiting_command(t_list **envl)
{
	char	*line;

	signal(SIGINT, &handler);
	signal(SIGQUIT, &handler);
	line = NULL;
	g_sigint = 0;
	add_env("?begin", ft_strdup("0"), envl, -1);
	prompt();
	while (reader(&line) > 0)
	{
		g_sigquit = 0;
		parse_and_exec(envl, line);
	}
	if (line)
		free(line);
	return (CSIGINT * g_sigint);
}

int			main(int argc, char **argv, char **env)
{
	t_list	*envl;
	int		exit_value;

	(void)argv;
	if (argc > 1)
		g_print_all = 0;
	else
		g_print_all = 1;
	header();
	parse_env(&envl, env);
	exit_value = waiting_command(&envl);
	if (!exit_value)
		exit_value = ft_atoi(search_in_env(envl, "?begin"));
	ft_lstclear(&envl, &free_entry);
	ft_putstr("exit\n");
	return (exit_value);
}
