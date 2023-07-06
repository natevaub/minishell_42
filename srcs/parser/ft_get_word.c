#include "../includes/minishell.h"

int	ft_len_word(char *arg)
{
	int	i = 0;
	while (arg[i] != '\0')
		i++;
	ft_printf("YOOOo\n");
	return (i);
}
