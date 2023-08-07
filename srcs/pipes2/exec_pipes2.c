#include "../../includes/minishell.h"

int	ft_count_cmds(t_lcmd *cmd)
{
	t_lcmd	*cpy;
	int		i;

	cpy = cmd;
	i = 0;
	while (cmd != NULL)
	{
		i++;
		cmd = cmd->next;
	}
	cmd = cpy;
	return (i);
}

void	ft_init_pipes_struct(t_minishell *shell, t_pipex *pipe)
{
	pipe->count_cmds = ft_count_cmds(shell->cmd);
	// printf("In ft_init_pipes_struct count = %d\n", pipe->count_cmds);
	pipe->idx = 0;
}

int		ft_pipe_dep_mod(t_pipex *p)
{
	if (p->idx % 2 == 0)
	{
		pipe(p->pipe_fd[0]);
	}
	else
	{
		pipe(p->pipe_fd[1]);
	}
	return (0);
}

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
	return (0);
}

int	ft_exec_cmd(t_lcmd *cmd, char **envp)
{
	char	*cmd_with_path;
	// printf("In ft_exec_cmd\n");
	cmd_with_path = ft_get_right_path(cmd->cmd);
	if (execve(cmd_with_path, cmd->option, envp) < 0)
	{
		printf("Ca n'a pas marcher\n");
		return (1);
	}
	return (0);
}

int	ft_pipeline_execution(t_minishell *shell, char **envp)
{
	// printf("In ft_pipeline_execution\n");
	t_lcmd	*cmd;
	t_pipex	*p;
	pid_t	pid;

	p = malloc(sizeof(t_pipex));
	ft_init_pipes_struct(shell, p);
	cmd = shell->cmd;
	
	while (cmd != NULL)
	{
		// printf("Working cmd = %s, Idx = %d\n", cmd->cmd, p->idx);
		ft_pipe_dep_mod(p);
		pid = fork();
		if (pid == 0)
		{
			// exit(1);
			ft_set_fd(shell, p);
			close(p->pipe_fd[p->idx % 2][0]);
			close(p->pipe_fd[p->idx % 2][1]);
			ft_exec_cmd(cmd, envp);
		}
		else if (pid > 0)
		{
			// printf("Parent Process\n");
			if (p->idx != 0)
			{
				close(p->pipe_fd[(p->idx - 1) % 2][0]);
				close(p->pipe_fd[(p->idx - 1) % 2][1]);
			}
		}
		// close(p->pipe_fd[(p->idx - 1) % 2][0]);
		// close(p->pipe_fd[(p->idx - 1) % 2][1]);
		// close(p->pipe_fd[(p->idx - 1) % 2][1]);


		p->idx++;
		cmd = cmd->next;
	}
	close(p->pipe_fd[(p->idx - 1) % 2][0]);
	close(p->pipe_fd[(p->idx - 1) % 2][1]);

	for (int i = 0; i < p->count_cmds; i++) {
		wait(NULL);
	}
	return (0);
}

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