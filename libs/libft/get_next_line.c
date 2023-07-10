/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 11:34:10 by nvaubien          #+#    #+#             */
/*   Updated: 2023/07/08 22:41:14 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	contains_newline(char *s, int *i, int n_bytes)
{
	int		j;
	char	u;

	j = 0;
	*i = 0;
	while (j < n_bytes)
	{
		u = s[j];
		j++;
		if (u == '\n')
		{
			return (1);
		}
		(*i) += 1;
	}
	*i = -1;
	return (0);
}

void	set_new_megabuff(char **mbuff, char **new_mbuff, char *buff, int bytes)
{
	*new_mbuff = ft_gnl_strjoin(*mbuff, buff, bytes);
	free(*mbuff);
	*mbuff = *new_mbuff;
}

int	extract_line(char **megabuff, char **line)
{
	int		j;
	int		i;
	int		has_newline;
	char	*new_megabuff;

	i = 0;
	has_newline = contains_newline(*megabuff, &i, ft_strlen(*megabuff));
	if (has_newline)
		j = i;
	else
		j = ft_strlen(*megabuff);
	*line = ft_gnl_substr(*megabuff, 0, j + 1);
	new_megabuff = ft_gnl_substr(*megabuff, j + 1, ft_strlen(*megabuff));
	free(*megabuff);
	*megabuff = new_megabuff;
	if (ft_strlen(*line) == 0)
	{
		free(*line);
		return (1);
	}
	return (0);
}

int	read_while_newline(int fd, char **megabuff)
{
	char	*buff;
	char	*new_megabuff;
	int		bytes;
	int		i;

	i = 0;
	if (contains_newline(*megabuff, &i, ft_strlen(*megabuff)))
		return (0);
	while (1)
	{
		buff = ft_gnl_calloc(BUFFER_SIZE, sizeof(char));
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(buff);
			return (1);
		}
		set_new_megabuff(megabuff, &new_megabuff, buff, bytes);
		if (contains_newline(buff, &i, bytes) || bytes == 0)
		{
			free(buff);
			return (0);
		}
		free(buff);
	}
}

char	*get_next_line(int fd)
{
	static char	*megabuff;
	char		*line;
	int			read_error;
	int			extract_error;

	if (megabuff == NULL)
	{
		megabuff = ft_gnl_calloc(1, sizeof(char));
	}
	read_error = read_while_newline(fd, &megabuff);
	if (read_error)
	{
		free(megabuff);
		megabuff = NULL;
		return (NULL);
	}
	extract_error = extract_line(&megabuff, &line);
	if (extract_error)
	{
		free(megabuff);
		megabuff = NULL;
		return (NULL);
	}
	return (line);
}
