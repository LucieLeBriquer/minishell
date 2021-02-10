#include "minishell.h"

void	exec_builtin(t_info *cmd, t_split *split, char **env)
{
	(void)cmd;
	(void)split;
	(void)env;
	ft_printf("\t> Builtin %d\n", cmd->builtin);
}

void	exec_executable(t_info *cmd, t_split *split, char **env)
{
	(void)cmd;
	(void)split;
	(void)env;
	ft_printf("\t> Executable ./\n");
}

void	exec_declaration(t_info *cmd, t_split *split, char **env)
{
	(void)cmd;
	(void)split;
	(void)env;
	ft_printf("\t> Declaration\n");
}

void	exec_execbin(t_info *cmd, t_split *split, char **env)
{
	(void)cmd;
	(void)split;
	(void)env;
	ft_printf("\t> Executable $PATH\n");
}
