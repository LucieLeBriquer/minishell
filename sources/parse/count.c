#include "minishell.h"

int	new_state(char *command, int i)
{
	if (command[i] == '\"')
		return (DB_QUOTE);
	if (command[i] == '\'')
		return (QUOTE);
	if (is_operator(command[i]))
		return (OPERATOR);
	return (SPACE);
}

int	nb_words(char *command)
{
	t_parse	p;

	p.len_word = -1;
	p.sep = ' ';
	p.state = 0;
	p.nb = 0;
	return (state_reset(command, 0, &p));
}

int	len_of_word(char *command, int i, char *sep)
{
	t_parse	p;

	p.len_word = 0;
	p.sep = ' ';
	p.state = 0;
	p.nb = 0;
	(void)state_reset(command, i, &p);
	*sep = p.sep;
	return (p.len_word);
}
