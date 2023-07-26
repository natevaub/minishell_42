/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:38:36 by ckarl             #+#    #+#             */
/*   Updated: 2023/06/22 16:31:20 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_pipex_struct(int argc, char **argv, t_pipex *pipex)
{
	pipe(pipex->pipe_fd[0]);
	pipe(pipex->pipe_fd[1]);
	pipex->infile_fd = open(argv[1], O_RDONLY);
	pipex->outfile_fd = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (pipex->infile_fd < 0 || pipex->outfile_fd < 0)
		return ;																	//set errno
	pipex->commands = set_p_command_list(argc, argv, pipex);
	pipex->count_cmds = total_len_cmd(pipex->commands);
	pipex->idx = 0;
		// print_list_fds(pipex->commands);
}

//set command list & read/write fds
t_lcmd	*set_p_command_list(int argc, char **argv, t_pipex *pipex)
{
	t_lcmd	*list;
	int		i;
	int		w_pipe;
	int		r_pipe;

	i = 1;
	list = NULL;
	while (++i < (argc - 1))
	{
		if (i == 2)												//need to change this when switching to tokens from argv
			r_pipe = pipex->infile_fd;
		else if (i % 2 != 0)
			r_pipe = pipex->pipe_fd[0][0];
		else
			r_pipe = pipex->pipe_fd[1][0];
		if (i == argc - 2)										//need to change this when switching to tokens from argv
			w_pipe = pipex->outfile_fd;
		else if (i % 2 == 0 || i == 0)
			w_pipe = pipex->pipe_fd[0][1];
		else
			w_pipe = pipex->pipe_fd[1][1];
		list_append_pipes(&list, argv[i], w_pipe, r_pipe);
	}
	return (list);
}
