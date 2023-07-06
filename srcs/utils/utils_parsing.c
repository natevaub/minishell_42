#include "../includes/minishell.h"

int	ft_strcmp(char *str, char *comp)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != comp[i])
			return (1);
		i++;
	}
	return (0);
}