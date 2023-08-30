/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 01:46:40 by nvaubien          #+#    #+#             */
/*   Updated: 2023/08/30 12:23:25 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

//		### Linked List Token ###

typedef struct s_list_token
{
	char				*word;
	int					type;
	int					red;
	int					quote;
	struct s_list_token	*next;
	struct s_list_token	*prev;
}						t_tok;

//		### Linked List Var_env ####

typedef struct s_list_venv
{
	char				*word;
	int					len;
	struct s_list_venv	*next;
	struct s_list_venv	*prev;
}						t_venv;

//		### Linked List Cmd ###

typedef struct s_list_cmd
{
	char				*cmd;
	char				**option;
	int					fd_read;
	int					fd_write;
	char				*infile;
	char				*outfile;
	int					append;
	struct s_list_cmd	*next;
}						t_lcmd;

typedef struct s_cmd
{
	char				*cmd;
	char				**option;
	int					read;
	int					write;
	char				*infile;
	char				*outfile;
	int					append;
}						t_cmd;

//		### Pipe Structure ###
typedef struct s_pipex
{
	int			count_cmds;
	int			idx;
	int			pipe_fd[2][2];
}				t_pipex;

typedef struct s_linked_list
{
	char					*value;
	struct s_linked_list	*next;
}				t_linked_list;

//		### All Data ###

typedef struct s_minishell
{
	int					syntax;
	struct s_list_token	*token;
	struct s_list_cmd	*cmd;
	struct s_pipex		*p;
	t_venv				*copy_env;
	int					last_exit_status;
	int					heredoc;
	t_linked_list		*hd_docs;
	t_linked_list		*hd_words;
	struct termios		termios_default;
}						t_minishell;

#endif