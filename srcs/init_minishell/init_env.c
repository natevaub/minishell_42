/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:28:27 by nvaubien          #+#    #+#             */
/*   Updated: 2023/08/21 16:28:29 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**ft_get_env(void)
{
	extern char	**environ;
	char		**var;
	int			i;
	int			k;

	i = 0;
	k = 0;
	while (environ[i] != NULL)
		i++;
	var = (char **)malloc(sizeof(char *) * (i + 1));
	if (!var)
		return (NULL);
	while (environ[k] != NULL)
	{
		var[k] = environ[k];
		k++;
	}
	var[k] = NULL;
	return (var);
}

void	free_two_dimension_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}