#include "minishell.h"

void	print_error_parsing(int err)
{
	if (err == 1)
		ft_printf("Wrong format\n");
	else if (err == 2)
		ft_printf("Allocation issue\n");
}

void	print_parsed_command(t_split *split)
{
	int		i;

	i = 0;
	while (split[i].str)
	{
		ft_printf("[%c] [%s]\n", split[i].quote, split[i].str);
		free(split[i].str);
		i++;
	}
}
