/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:06:29 by ckarl             #+#    #+#             */
/*   Updated: 2023/08/07 16:55:19 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern t_global	global;

int	ft_set_fd(t_minishell *shell, t_pipex *p)
{
	if (p->idx == 0)
	{
		close(p->pipe_fd[0][0]);
		dup2(p->pipe_fd[0][1], STDOUT_FILENO);
	}
	else if (p->idx != p->count_cmds - 1)
	{
		close(p->pipe_fd[(p->idx - 1) % 2][1]);  // Close write end of previous pipe
		dup2(p->pipe_fd[(p->idx) - 1 % 2][0], STDIN_FILENO); // Set input from pipe
		close(p->pipe_fd[(p->idx) % 2][0]);
		dup2(p->pipe_fd[(p->idx) % 2][1], STDOUT_FILENO);
	}
	else
	{
		close(p->pipe_fd[(p->idx - 1) % 2][1]);
		dup2(p->pipe_fd[(p->idx - 1) % 2][0], STDIN_FILENO);
	}
	// close(p->pipe_fd[p->idx % 2][0]);				deplacé de apres ft_set_fds
	// close(p->pipe_fd[p->idx % 2][1]);
	return (0);
}

int	ft_exec_child(t_lcmd *cmd, char **envp)
{
	char	*cmd_with_path;
	cmd_with_path = ft_get_right_path(cmd->cmd);
	if (execve(cmd_with_path, cmd->option, envp) < 0)
	{
		printf("Ca n'a pas marcher\n");
		free(cmd_with_path);
		exit(1);
		return (1);
	}
	return (0);
}

void	ft_exec_parent(t_pipex *p, pid_t *pid)
{
	int	i;
	int	status;

	i = -1;
	close(p->pipe_fd[(p->idx - 1) % 2][0]);
	close(p->pipe_fd[(p->idx - 1) % 2][1]);
	close(p->pipe_fd[(p->idx) % 2][0]);
	close(p->pipe_fd[(p->idx) % 2][1]);
	while (++i < p->count_cmds)
	{
		waitpid(-1, &status, 0);
		if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGQUIT)
				write(1, "Quit: 3\n", 8);
			else if (WTERMSIG(status) == SIGINT)
				write(1, "\n", 1);
			global.last_exit_status = 128 + status;
		}
		if (WIFEXITED(status))
			global.last_exit_status = WEXITSTATUS(status);
	}
}

int	ft_pipeline_execution(t_minishell *shell, char **envp)
{
	t_lcmd	*cmd;
	t_pipex	*p;
	pid_t	pid;

	p = malloc(sizeof(t_pipex));
	ft_init_pipes_struct(shell, p);
	cmd = shell->cmd;
	while (cmd != NULL)
	{
		ft_pipe_dep_mod(p);
		pid = fork();
		if (pid == 0)
		{
			ft_set_fd(shell, p);
			ft_exec_child(cmd, envp);
		}
		else if (pid > 0)
		{
			if (p->idx != 0)
			{
				close(p->pipe_fd[(p->idx - 1) % 2][0]);
				close(p->pipe_fd[(p->idx - 1) % 2][1]);
			}
		}
		p->idx++;
		cmd = cmd->next;
	}
	ft_exec_parent(p, &pid);
	return (0);
}

		// close(p->pipe_fd[(p->idx - 1) % 2][0]);
		// close(p->pipe_fd[(p->idx - 1) % 2][1]);
		// close(p->pipe_fd[(p->idx - 1) % 2][1]);
char	*ft_get_path_line(void)
{
	char	*envp_path = NULL;
	t_venv	*head;

	head = global.copy_env;
	while (head)
	{
		if (ft_strncmp(head->word, "PATH", 4) == 0)
			envp_path = head->word;
		head = head->next;
	}
	return (envp_path + 5);
}

char	*ft_get_right_path(char *cmd)
{
	char	**all_paths;
	char	*temp_path;
	// printf("command to find = %s\n", cmd);

	all_paths = ft_split(ft_get_path_line(), ':');
	while (*all_paths)
	{
		temp_path = ft_join_path(*all_paths, cmd);
		if (access(temp_path, F_OK & X_OK) == 0)
		{
			// printf("Temp Path = %s\n", temp_path);
			return (temp_path);
		}
		free(temp_path);
		all_paths++;
	}
	return (NULL);
}

char	*ft_join_path(char const *s1, char const *s2)
{
	char			*copy;
	int				i;
	int				j;
	unsigned int	len1;
	unsigned int	len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	i = 0;
	j = 0;
	copy = (char *)malloc(sizeof(*copy) * (len1 + len2 + 1));
	if (!copy)
		return (NULL);
	while (s1[i])
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i++] = '/';
	while (s2[j])
		copy[i++] = s2[j++];
	copy[i] = '\0';
	return (copy);
}

char	**ft_env_list_to_env_tab(void)
{
	char	**env;
	int		len;
	t_venv	*head;
	int		i;

	i = 0;
	head = global.copy_env;
	len = list_size(head);
	env = (char **)malloc (sizeof(char *) * (len + 1));
	while (head)
	{
		env[i] = ft_strdup(head->word);
		if (!env[i])
			return (NULL);															//set error msg
		i++;
		head = head->next;
	}
	env[i] = 0;

	return (env);
}

char	**env_list_to_env_tab(void)
{
	char	**env;
	int		len;
	t_venv	*head;
	int		i;

	i = 0;
	head = global.copy_env;
	len = list_size(head);
	env = (char **)malloc (sizeof(char *) * (len + 1));
	while (head)
	{
		env[i] = ft_strdup(head->word);
		if (!env[i])
			return (NULL);															//set error msg
		i++;
		head = head->next;
	}
	env[i] = 0;

	return (env);
}

int	improved_dup2(int fildes, int fildes2)
{
	int	error;

	error = dup2(fildes, fildes2);
	if (error < 0)
	{
		perror("error dup2");
		exit(errno);
	}
	return (error);
}

int	improved_pipe(int fd[2])
{
	int	error;

	error = pipe(fd);
	if (error == -1)
	{
		perror("error pipe");
		exit(1);
	}
	return (error);
}

pid_t	improved_fork(void)
{
	pid_t	error;

	error = fork();
	if (error == -1)
	{
		perror("error fork");
		exit(1);
	}
	return (error);
}

void	sub_dup2(int read, int write)
{
	improved_dup2(read, STDIN_FILENO);
	improved_dup2(write, STDOUT_FILENO);
}