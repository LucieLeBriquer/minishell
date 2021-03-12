/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:36:55 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/12 17:31:31 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(void)
{
	char	cwd[SIZE_PATH];

	getcwd(cwd, SIZE_PATH);
	ft_putstr("\033[1;35mmini@shell \033[0;35m");
	ft_putstr(cwd);
	ft_putstr("\033[0m$ ");
}

void	handler(int signo)
{
	if (signo == SIGINT)
	{
		g_sigint = 1;
		ft_printf("\n");
		prompt();
	}
}

int		waiting_command(t_list **envl)
{
	char	*line;
	t_split	*split;
	t_error	error;
	int		err;

	signal(SIGINT, &handler);
	line = NULL;
	g_sigint = 0;
	add_env("?begin", ft_strdup("0"), envl, -1);
	prompt();
	while (reader(&line) > 0)
	{
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
	if (line)
		free(line);
	return (130 * g_sigint);
}

void	header_simple(void)
{
	ft_putstr("\033[1;35m  __  __ _       _     _          _ _\n");
	ft_putstr(" |  \\/  (_)_ __ (_)___| |__   ___| | |\n");
	ft_putstr(" | |\\/| | | '_ \\| / __| '_ \\ / _ \\ | |\n");
	ft_putstr(" | |  | | | | | | \\__ \\ | | |  __/ | |\n");
	ft_putstr(" |_|  |_|_|_| |_|_|___/_| |_|\\___|_|_|\033[0m\n\n");
}

int		main(int argc, char **argv, char **env)
{
	t_list	*envl;
	int		exit_value;

	(void)argv;
	if (argc > 1)
		g_print_all = 0;
	else
		g_print_all = 1;
	header_simple();
	parse_env(&envl, env);
	exit_value = waiting_command(&envl);
	if (!exit_value)
		exit_value = ft_atoi(search_in_env(envl, "?begin"));
	ft_lstclear(&envl, &free_entry);
	ft_printf("exit\n");
	return (exit_value);
}
