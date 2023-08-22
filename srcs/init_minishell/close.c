#include "../includes/minishell.h"

void free_env_list(t_venv *env_list)
{
	t_venv *current;
	t_venv *next;

	current = env_list;
	while (current != NULL)
	{
		next = current->next;
		if (current->word)
			free(current->word);
		free(current);
		current = next;
	}
	env_list = NULL;
}

void	ft_finish_minishell(t_minishell *ms)
{
	if ((tcsetattr(STDIN_FILENO, TCSANOW, &ms->termios_default)) == -1)
		exit(EXIT_FAILURE);
	free_env_list(ms->copy_env);
	free(ms->p);
	exit(EXIT_SUCCESS);
}