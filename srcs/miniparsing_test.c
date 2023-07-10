#include "../includes/minishell.h"

int main(int ac, char **av, char **envp)
{
	char		*prompt;
	char		**option;
	char		*cmd;
	t_global	global;
	(void)		ac;
	(void)		av;
	(void)		envp;

	global.copy_env = new_env_list(envp);
	global.last_exit_status = 0;
	while (1)
	{
		prompt = readline(">> ");
		option = ft_split(prompt, ' ');
		cmd = option[0];
		if (option + 1)
			builtin_redirect(&global, cmd, (option + 1));
		else
			builtin_redirect(&global, cmd, NULL);
	}
	return (0);
}