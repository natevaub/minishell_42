#include "../includes/minishell.h"

void	ft_memory_allocation_failed(void)
{
		perror("Memory allocation failed\n");
		exit(EXIT_FAILURE);
}