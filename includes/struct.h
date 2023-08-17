#ifndef STRUCT_H
# define STRUCT_H

//		### Linked List Token ###

typedef struct	s_list_token
{
	char				*word;
	int					type;
	int					red;
	int					quote;
	struct s_list_token	*next;
	struct s_list_token	*prev;
}						t_tok;

//		### Linked List Var_env ####

typedef struct	s_list_venv
{
	char				*word;
	struct s_list_venv	*next;
	struct s_list_venv	*prev;
}						t_venv;

//		### Linked List Cmd ###

typedef struct	s_list_cmd
{
	char				*cmd;
	char				**option;
	int					fd_read;
	int					fd_write;
	struct s_list_cmd	*next;
}						t_lcmd;

typedef struct	s_cmd
{
	char				*cmd;
	char				**option;
	int					read;
	int					write;
}						t_cmd;

// 		### Global Variable ###
typedef struct	s_global
{
	int	status;
}						g_global;						//need to call it g_global

//		### Pipe Structure ###
typedef struct	s_pipex
{
	// pid_t		pid;
	// int			infile_fd;
	// int			outfile_fd;
	int			count_cmds;
	int			idx;
	int			pipe_fd[2][2];
	// t_lcmd		*commands;
}				t_pipex;

//		### All Data ###

typedef struct	s_minishell
{
	int					syntax;
	struct s_list_token	*token;
	struct s_list_cmd	*cmd;
	struct s_pipex		*p;
	t_venv				*copy_env;
	int					last_exit_status;
	struct termios		termios_default;
}						t_minishell;

#endif