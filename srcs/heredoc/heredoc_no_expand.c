/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_no_expand.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 19:54:02 by nvaubien          #+#    #+#             */
/*   Updated: 2023/08/24 11:40:13 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_ctrl_d(void)
{
	rl_replace_line("", 0);
	ft_output_command_line();
	rl_on_new_line();
	rl_redisplay();
	g_status = 1;
}

t_linked_list	*ft_store_heredoc_content(char *eof)
{
	t_linked_list	*node;
	char			*line;

	node = NULL;
	while (1)
	{
		line = readline("> ");
		if (!line)
			handle_ctrl_d();
		if (g_status != 0)
			return (NULL);
		if (ft_strncmp(line, eof, ft_strlen(eof)) == 0)
		{
			free(line);
			break ;
		}
		else
			node = ft_insert_at_tail(node, line);
	}
	return (node);
}

char	*ft_list_to_char(t_linked_list *head)
{
	int				total_size;
	t_linked_list	*curr;
	char			*str;

	curr = head;
	total_size = 0;
	if (curr == NULL)
		return (NULL);
	while (curr != NULL)
	{
		total_size += ft_strlen(curr->value) + 1;
		curr = curr->next;
	}
	str = (char *)malloc(sizeof(char) * (total_size + 1));
	if (str == NULL)
		ft_memory_allocation_failed();
	curr = head;
	str[0] = '\0';
	while (curr != NULL)
	{
		ft_strcat(str, curr->value);
		ft_strcat(str, "\n");
		curr = curr->next;
	}
	return (str);
}

void	ft_write_to_temp_file(char *content)
{
	int	fd;

	if (content == NULL)
		return ;
	fd = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		free(content);
		perror("Error opening .heredoc file\n");
		exit(EXIT_FAILURE);
	}
	if (write(fd, content, ft_strlen(content)) == -1)
	{
		free(content);
		perror("Error writing to .heredoc file\n");
		exit(EXIT_FAILURE);
	}
	free(content);
	close(fd);
}
