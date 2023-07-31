/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:10:31 by ckarl             #+#    #+#             */
/*   Updated: 2023/06/22 16:22:32 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//append new node to t_lcmd command list, setting read & write fd
void	list_append_pipes(t_lcmd **lst, char *command, int w_pipe, int r_pipe)
{
	t_lcmd	*addback;
	t_lcmd	*copy;
	(void)	r_pipe;
	(void)	w_pipe;

	addback = (t_lcmd *)malloc(sizeof(t_lcmd));
	if (!addback)
		return ;
	addback->next = NULL;
	addback->option = ft_split(command, ' ');
	addback->cmd = addback->option[0];
	addback->fd_write = w_pipe;
	addback->fd_read = r_pipe;
	if (*lst == NULL)
	{
		*lst = addback;
		return ;
	}
	copy = last_node_pipes(*lst);
	copy->next = addback;
}

//go to last node of t_lcmd list
t_lcmd	*last_node_pipes(t_lcmd *lst)
{
	int	i;

	i = 0;
	while (lst->next)
		lst = lst->next;
	return (lst);
}

//get a node in the t_lcmd command list
t_lcmd	*get_node_pipes(t_lcmd *head, int index)
{
	t_lcmd	*copy;
	int			i;

	i = 0;
	copy = head;
	while (i < index && copy != NULL)
	{
		copy = copy->next;
		i++;
	}
	return (copy);
}

//total len of linked command list
int	total_len_cmd(t_lcmd *commands)
{
	int	i;

	i = 0;
	while (commands)
	{
		commands = commands->next;
		i++;
	}
	return (i);
}

//print all fds for t_lcmd list
void	print_list_fds(t_lcmd *list)
{
	while (list)
	{
		printf("list fd read: %d and write %d\n", list->fd_read, list->fd_write);
		printf("list cmd: %s\n", list->cmd);
		list = list->next;
	}
	printf("\n");
}
