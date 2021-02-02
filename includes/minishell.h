#ifndef MINISHELL_H
# define MINISHELL_H
# include "libftfull.h"
# include <stdlib.h>
# define NB_CMD 3
# define SIZE_PATH 60

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
	char	quote;
}			t_split;

typedef struct
{
	char	sep;
	int		nb_words;
	int		state;
}			t_parse;

void	simple_parse(char *command);
t_split	*parse_quotes(char *command, int *err);
void	print_parse_quotes(char *command);
void	trim_spaces_right(char *s);
void	trim_useless(t_split split);
int		nb_words(char *s, int l);
int		len_of_word(char *s, char *sep, int l);

#endif
