#include "../includes/minishell.h"

void free_env_list(t_venv *env_list)
{
	t_venv *current = env_list;
	t_venv *next;

	while (current != NULL)
	{
		next = current->next;

		// Free the memory for the variables in the current node
		// Assuming that the 'name' field is a dynamically allocated string
		free(current->word);

		// Free the current node itself
		free(current);

		current = next;
	}
}