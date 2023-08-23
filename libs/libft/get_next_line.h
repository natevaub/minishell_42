/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 11:34:18 by nvaubien          #+#    #+#             */
/*   Updated: 2023/08/23 10:52:38 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 41
# endif

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
// Utils functions
char	*ft_gnl_strjoin(char *s1, char *s2, int s2_size);
char	*ft_gnl_substr(char const *s, unsigned int start, size_t len);
void	*ft_gnl_calloc(size_t count, size_t size);
void	ft_gnl_bzero(void *s, size_t n);

void	set_new_megabuff(char **mbuff, char **new_mbuff, char *buff, int bytes);
int		contains_newline(char *s, int *i, int n_bytes);
int		extract_line(char **megabuff, char **line);
int		read_while_newline(int fd, char **megabuff);
char	*get_next_line(int fd);

#endif
