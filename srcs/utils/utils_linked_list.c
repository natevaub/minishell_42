/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_linked_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:38:12 by nvaubien          #+#    #+#             */
/*   Updated: 2023/08/21 16:38:41 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_lcmd	*ft_newlst_cmd(t_cmd *cmd)
{
	t_lcmd	*new;

	new = malloc(sizeof(t_lcmd));
	if (!new)
		return (NULL);
	new->cmd = cmd->cmd;
	new->option = cmd->option;
	new->fd_read = cmd->read;
	new->fd_write = cmd->write;
	new->next = NULL;
	free(cmd);
	return (new);
}

t_tok	*ft_newlst_token(char *word)
{
	t_tok	*new;

	new = malloc(sizeof(t_tok));
	if (!new)
		return (NULL);
	new->word = word;
	new->type = ft_get_tk_type(word);
	new->red = ft_red_type(word);
	new->quote = ft_get_quoted_tk(word);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	ft_lstadd_back_token(t_tok **lst, t_tok *nw)
{
	t_tok	*node;

	node = *lst;
	if (node == NULL)
		node = nw;
	else
	{
		while (node->next != NULL)
			node = node->next;
		node->next = nw;
		nw->prev = node;
	}
}

void	ft_lstadd_back_cmd(t_lcmd **lst, t_lcmd *nw)
{
	t_lcmd	*node;

	node = *lst;
	if (node == NULL)
		node = nw;
	else
	{
		while (node->next != NULL)
			node = node->next;
		node->next = nw;
	}
}
