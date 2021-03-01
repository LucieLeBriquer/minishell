#include "minishell.h"

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
