#include "minishell.h"

int	ft_pwd(t_info *cmd, t_split *split, char **env)
{
	char	cwd[SIZE_PATH];
	
	(void)cmd;
	(void)split;
	(void)env;
	getcwd(cwd, SIZE_PATH);
	ft_printf("%s\n", cwd);
	return (0);
}
