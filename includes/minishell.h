#ifndef MINISHELL_H
# define MINISHELL_H
# include "libftfull.h"
# include <stdlib.h>
# define NB_CMD 3
# define SIZE_PATH 30

/*typedef enum
{
	ECHO,
	CD,
	PWD,
}	t_cmds;

char	commands[NB_CMD][10] = {"echo", "cd", "pwd"};

typedef struct
{
	t_cmds	name;
	int		option;
}			t_cmd;
*/
typedef struct
{
	char	*str;
	int		quotes;
}			t_split;

void	simple_parse(char *command);
t_split	*parse_quotes(char *command);
void	print_parse_quotes(char *command);

#endif
