/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 01:46:40 by nvaubien          #+#    #+#             */
/*   Updated: 2023/08/23 11:03:19 by ckarl            ###   ########.fr       */
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
