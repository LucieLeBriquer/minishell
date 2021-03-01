/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:36:55 by lle-briq          #+#    #+#             */
/*   Updated: 2021/03/01 22:04:29 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(void)
{
	char	cwd[SIZE_PATH];

	getcwd(cwd, SIZE_PATH);
	ft_printf("\033[1;35m%s@%s \033[0;35m%s\033[0m$ ", "mini", "shell", cwd);
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

void	waiting_command(t_list **envl)
{
	char	*line;
	t_split	*split;
	int		err;

	prompt();
	signal(SIGINT, &handler);
	line = NULL;
	while (reader(&line) > 0)
	{
		g_sigint = 0;
		split = parse_command(line, &err);
		if (!split)
			print_error_parsing(err);
		else
		{
			print_parsed_command(split);
			execute(split, envl, line);
		}
		free_all(line, split);
		if (!g_sigint)
			prompt();
	}
	free(line);
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

	(void)argv;
	if (argc > 1)
		g_print_all = 0;
	else
		g_print_all = 1;
	header_simple();
	parse_env(&envl, env);
	waiting_command(&envl);
	ft_lstclear(&envl, &free_entry);
	ft_printf("exit\n");
	return (0);
}
