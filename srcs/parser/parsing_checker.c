/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 01:46:40 by nvaubien          #+#    #+#             */
/*   Updated: 2023/08/23 11:08:05 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_print_tokens(t_tok *token)
{
	t_tok	*current;
	int		index;

	index = 1;
	current = token;
	printf("--- PRINTING TOKENS ---\n");
	while (current != NULL)
	{
		printf(" --- token[%d] ---\n", index++);
		printf("[%s] <- word\n", current->word);
		printf("[%d] <- type\n", current->type);
		printf("[%d] <- red\n", current->red);
		printf("[%d] <- quote\n", current->quote);
		current = current->next;
	}
}

void	ft_print_cmds(t_lcmd *cmd)
{
	t_lcmd	*test;
	int		i;
	int		j;

	i = 0;
	j = 1;
	test = cmd;
	printf("--- PARSING TOKEN -> ----\n");
	while (test != NULL)
	{
		printf(" --- cmd[%d] ---\n", j++);
		printf("[%s] <- cmd\n", test->cmd);
		if (test->cmd != NULL)
		{
			while (test->option[i] != NULL)
			{
				printf("[%s] <- option[%d]\n", test->option[i], i);
				i++;
			}
		}
		i = 0;
		printf("[%d] <- fd_read\n", test->fd_read);
		printf("[%d] <- fd_write\n", test->fd_write);
		test = test->next;
	}
}
