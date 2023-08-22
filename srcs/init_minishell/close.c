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