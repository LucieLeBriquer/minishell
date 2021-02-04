/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:36:55 by lle-briq          #+#    #+#             */
/*   Updated: 2021/02/03 11:40:49 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(char *cwd)
{
	ft_printf("\033[36m%s@%s \033[37m%s\033[0m$ ", "mini", "shell", cwd);
}

void	print_entry(void *ventry)
{
	t_env	*entry;

	entry = ventry;
	ft_printf("%s : %s\n", entry->name, entry->value);
}

int		main(int argc, char **argv, char **env)
{
	char	cwd[SIZE_PATH];
	char	*line;
	t_list	*env_list;
	t_split	*split;
	int		err;

	(void)argc;
	(void)argv;
	parse_env(&env_list, env);
	getcwd(cwd, SIZE_PATH);
	prompt(cwd);
	while (get_next_line(0, &line) > 0)
	{
		split = parse_quotes(line, &err);
		if (!split)
			print_error_parsing(err);
		else
		{
			print_parsed_command(split);
			execute(split, env);
		}
		free(line);
		free(split);
		prompt(cwd);
	}
	free(line);
	ft_lstclear(&env_list, &free_entry);
	return (0);
}
