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

char *ft_strcat(char *dest, char *src)
{
	int i;
	int j;

	i = 0;
	while (dest[i] != '\0')
		i++;
	j = 0;
	while (src[j] != '\0')
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}