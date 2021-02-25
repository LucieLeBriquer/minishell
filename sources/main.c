/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:36:55 by lle-briq          #+#    #+#             */
/*   Updated: 2021/02/25 23:52:41 by lle-briq         ###   ########.fr       */
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
		ft_printf("\n");
		prompt();
	}
}

void	waiting_command(t_list **envl)
{
	char	*line;
	t_split	*split;
	int		err;

	signal(SIGINT, &handler);
	prompt();
	line = NULL;
	while (reader(&line) > 0)
	{
		split = parse_command(line, &err);
		if (!split)
			print_error_parsing(err);
		else
		{
			print_parsed_command(split);
			execute(split, envl, line);
		}
		free_all(line, split);
		prompt();
	}
	free(line);
}

int	main(int argc, char **argv, char **env)
{
	t_list	*envl;

	(void)argv;
	if (argc > 1)
		PRINT_ALL = 0;
	else
		PRINT_ALL = 1;
	header();
	parse_env(&envl, env);
	waiting_command(&envl);
	ft_lstclear(&envl, &free_entry);
	ft_printf("exit\n");
	return (0);
}
