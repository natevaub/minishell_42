#include "../includes/minishell.h"

int	ft_syntax_quote_check(char *str)
{
	int		i;
	int		open;

	open = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			open = ft_syntax_open_quote_check(str, str[i], &i);
		}
		else
			i++;
	}
	if (open == 1)
		return (1);
	return (0);
}

int	ft_syntax_open_quote_check(char *str, char c, int *i)
{
	printf("Here\n");
	(*i)++;
	while (str[*i] != '\0')
	{
		printf("str[%d] = %c\n", *i, str[*i]);
		if (str[*i] == c)
		{
			(*i)++;
			return (0);
		}
		(*i)++;
	}
	return (1);
}