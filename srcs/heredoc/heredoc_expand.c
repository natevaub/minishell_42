
#include "../includes/minishell.h"

bool	ft_heredoc_line_got_dollar(char *input)
{
	DBG("In ft heredoc got dollar\n");
	int	i;

	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '$')
		{
			return (true);
		}
		i++;
	}
	DBG("Before Return in ft heredoc got dollar\n");
	return (false);
}

char	*ft_get_line_with_expand(char *input)
{
	DBG("In ft get line with expand\n");
	int		i;
	int		j;
	char	*var;
	char	*var_value;
	char	*expand_input;
	char	str[2];

	i = 0;
	j = 0;
	expand_input = "";
	DBG("Before while\n");
	while (input[i] != '\0')
	{
		str[0] = input[i];
		str[1] = '\0';
		DBG("In while\n");
		if (input[i] == '$')
		{
			j = i;
			while (input[i] != '\0' && input[i] != ' ')
			{
				i++;
			}
			var = ft_substr(input, j + 1, i - j - 1);
			N_DBG(j + 1);
			N_DBG(i - j);
			var_value = getenv(var);
			DBG(var);
			if (var_value != NULL)
			{
				expand_input = ft_strjoin(expand_input, var_value);
				DBG("Var Value"); DBG(var_value);
			}
			else
			{
				expand_input = ft_strjoin(expand_input, var);
			}
			free(var);
		}
		else
		{
			expand_input = ft_strjoin(expand_input, str);
		}
		i++;
	}
	DBG("Before Return ft get line with expand\n");
	return (expand_input);
}