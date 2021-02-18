/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:36:55 by lle-briq          #+#    #+#             */
/*   Updated: 2021/02/18 15:22:03 by lle-briq         ###   ########.fr       */
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
	ft_printf("%s : %s\n", entry->name, entry->value);
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

	(void)argv;
	if (argc > 1)
		PRINT_ALL = 0;
	else
		PRINT_ALL = 1;
	//parse_env(&env_list, env);
	signal(SIGINT, handler);
	prompt();
	while (get_next_line(0, &line) > 0)
	{
		split = parse_command(line, &err);
		if (!split)
			print_error_parsing(err);
		else
		{
			print_parsed_command(split);
			execute(split, env);
		}
		free_all(line, split);
		prompt();
	}
	free(line);
	//ft_lstclear(&env_list, &free_entry);
	return (0);
}
