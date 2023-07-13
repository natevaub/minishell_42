/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:38:36 by ckarl             #+#    #+#             */
/*   Updated: 2023/07/13 16:19:07 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern t_global	global;

//ENV WITH NO OPTIONS OR ARGUMENTS
/*If no utility is specified, env prints out the names and values
of the variables in the environment, with one name/value pair per line.*/

//find character c in string s, similar to ft_strchr
int	find_c(char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

//print environment when command env is called
int	print_env(void)
{
	t_venv	*head;

	head = global.copy_env;
	while (head)
	{
		if (find_c(head->word, '='))			//if var is undefined, it should not be printed
			ft_printf("%s\n", head->word);
		head = head->next;
	}
	ft_printf("_=/usr/bin/env\n");
	return(EXIT_SUCCESS);
	//make sure to change level if "minishell" is called again
}