/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:36:55 by lle-briq          #+#    #+#             */
/*   Updated: 2021/02/20 16:40:44 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(void)
{
	char	cwd[SIZE_PATH];
	
	getcwd(cwd, SIZE_PATH);
	ft_printf("\033[36m%s@%s \033[37m%s\033[0m$ ", "mini", "shell", cwd);
}

void	print_entry(void *ventry)
{
	t_env	*entry;

	entry = ventry;
	ft_printf("%s : %d\n", entry->var, entry->exported);
}

void	handler(int signo)
{
	(void)signo;
	ft_printf("\n");
	prompt();
}

void	free_all(char *line, t_split *split)
{
	int	i;

	if (line)
		free(line);
	if (!split)
		return ;
	i = 0;
	while (split[i].str)
	{
		free(split[i].str);
		i++;
	}
	free(split);
}

int		main(int argc, char **argv, char **env)
{
	char	*line;
	t_split	*split;
	int		err;
	t_list	*envl;

	(void)argv;
	if (argc > 1)
		PRINT_ALL = 0;
	else
		PRINT_ALL = 1;
	signal(SIGINT, handler);
	prompt();
	parse_env(&envl, env);
	while (get_next_line(0, &line) > 0)
	{
		split = parse_command(line, &err);
		if (!split)
			print_error_parsing(err);
		else
		{
			print_parsed_command(split);
			execute(split, envl);
		}
		free_all(line, split);
		prompt();
	}
	free(line);
	ft_lstiter(envl, &print_entry);
	ft_lstclear(&envl, &free_entry);
	return (0);
}
