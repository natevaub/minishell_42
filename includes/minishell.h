/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 01:46:40 by nvaubien          #+#    #+#             */
/*   Updated: 2023/08/30 17:57:59 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <errno.h>
# include <stdbool.h>
# include <termios.h>
# include <sys/param.h>

# include "struct.h"
# include "define.h"
# include "../libs/libft/libft.h"
# include "../libs/ftprintf/ft_printf.h"

extern int	g_status;

/*
	cmd_line
*/
/*	--- prompt.c	--- */
char			*ft_get_command_line(void);
char			*ft_output_command_line(void);

/*
	init_minishell
*/
/*	--- init_global.c	--- */
char			**ft_get_opt(char **option, char **tmp);
int				ft_len_cmd_opt(char **options);
t_cmd			*ft_init_cmds(t_tok **tokens);
char			**ft_store_cmd_options(t_tok **tokens, t_cmd *cmd);
void			ft_init_minishell(t_minishell *shell, char **env, \
				int ac, char **av);

/*	--- init_env.c	--- */
char			**ft_get_env(void);
void			free_two_dimension_array(char **arr);

/*	--- init_fd_redirection	--- */
char			*ft_get_infile_fd(t_tok **tk);
char			*ft_get_outfile_fd(t_tok **tk);
void			ft_open_files_redirection(t_tok **tk, t_cmd *cmd);

/*	--- close.c	--- */
void			free_env_list(t_venv *env_list);
void			ft_finish_minishell(t_minishell *ms);

/*
	syntax
*/
/*	--- syntax_pipe.c	--- */
int				ft_syntax_pipe_check(t_tok *syntax);
int				ft_pipe_error(t_tok *syntax);

/*	--- syntax_red.c	--- */
int				ft_syntax_red_check(t_tok *tok);
int				ft_red_error(t_tok *tk);

/*	--- syntax_quote.c	--- */
int				ft_syntax_quote_check(char *str);
int				ft_syntax_open_quote_check(char *str, char c, int *i);

/*	--- syntax.c	--- */
int				ft_syntax_checker(t_minishell *shell);
int				ft_look_for_err(t_tok *tok);
void			ft_print_error(int err, t_minishell *ms);

/*
	parser
*/
/* ---	get_joined_token.c	--- */
int				ft_is_joinable(t_tok *token);
int				ft_join_tk(t_tok *tk);
void			ft_strcat_join_tk(char *s1, char *s2, int *i, int *j);
void			ft_get_joined_tk(t_tok *tok, char *n_tk);

/*	---	get_len_word.c	--- */
int				ft_len_red(char *str, char c);
int				ft_len_space(char *str);
int				ft_len_word(char *str);
int				ft_len_quote(char *str, char c);

/*	--- get_parsed_token.c	---*/
void			ft_parse_token(t_minishell *shell);
void			ft_parsing(t_minishell *shell, char *prompt);

/*	--- get_trimmed_quote	--- */
void			ft_trim_quote(t_minishell *shell);

/*	---	get_token_type.c	--- */
int				ft_is_builtins(char *prompt);
int				ft_is_red(char *prompt);
int				ft_red_type(char *prompt);
int				ft_is_pipe(char *prompt);
int				ft_is_space(char *prompt);
/*	---	get_word.c	--- */
char			*ft_get_word_quote(char **prompt, char c);
char			*ft_get_word_space(char **str);
char			*ft_get_word_red(char **str, char c);
char			*ft_get_word(char **str);

/*	--- parsing_checker.c	--- */
void			ft_print_tokens(t_tok *token);
void			ft_print_cmds(t_lcmd *cmd);

/*	--- parsing_free_memory.c	--- */
void			ft_free_token(t_minishell *shell);
void			ft_free_cmd(t_minishell *shell);
void			ft_free_parsing(t_minishell *shell, char *prompt);

/*	---tokenize_prompt.c	--- */
void			ft_tokenize_prompt(t_minishell *global, char *prompt);
char			*ft_get_tk(char **prompt);
int				ft_get_tk_type(char *str);
int				ft_get_quoted_tk(char *prompt);

/*
	utils
*/
/*	--- utils_linked_list.c	--- */
t_lcmd			*ft_newlst_cmd(t_cmd *cmd);
t_tok			*ft_newlst_token(char *word);
void			ft_lstadd_back_token(t_tok **lst, t_tok *nw);
void			ft_lstadd_back_cmd(t_lcmd **lst, t_lcmd *nw);

/* utils_parsing.c */
int				ft_strcmp(char *str, char *comp);
char			*ft_strcat(char *dest, char *src);
void			ft_permission_denied(t_lcmd *cmd, t_minishell *ms);
void			ft_open_failed(t_lcmd *cmd, t_minishell *ms);

/*
	builtins
*/
/*	---	builtin_decide.c	---*/
void			builtin_run(t_minishell *ms, t_lcmd *cmd);
int				builtin_check(char *cmd);

/*	---	builtin_echo.c	---*/
char			*get_value(t_venv *env, void *var);
int				cmd_echo(t_lcmd *cmd);

/*	---	builtin_env.c	---*/
int				find_c(char *str, char c);
int				print_env(t_minishell *ms, t_lcmd *cmd);

/*	---	builtin_exit.c	---*/
void			cmd_exit(t_lcmd *cmd, t_minishell *ms);
void			change_shvl_in_env(int nbr, t_minishell *ms);
void			ft_exit_error_msg(char *opt, t_minishell *ms, int option);
int				ft_exit_arg_check(char *str, t_minishell *ms, t_lcmd *cmd);

/*	---	builtin_exit_utils.	---*/
void			run_exit_atoi(char *str, t_minishell *ms);
long long int	ft_longatoi_for_shell(char *str);

/*	---	builtin_export.c	---*/
int				check_var_format(char *var);
char			*trim_back(char *var);
int				change_existing_var_in_env(char *var, t_minishell *ms);
int				add_var_to_export(char **option, t_minishell *ms);
int				print_export(t_lcmd *cmd, t_minishell *ms);

/*	---	builtin_pwd_cd.c	---*/
int				cmd_cd(t_lcmd *cmd, t_minishell *ms);
int				cmd_pwd(t_lcmd *cmd);

/*	---	builtin_unset.c	---*/
int				cmd_unset(char **var, t_minishell *ms);
void			remove_var_from_env(t_venv *list, t_minishell *ms);

/*	---	utils_linked_list_1.c	---*/
int				list_size(t_venv *lst);
t_venv			*last_node(t_venv *lst);
t_venv			*first_node(t_venv *lst);
t_venv			*get_node_venv(t_venv *head, int index);
void			list_append(t_venv **lst, char *element);

/*	---	utils_linked_list_2.c	---*/
t_venv			*new_env_list(char **tab);
void			content_swap(t_venv *one, t_venv *two);
void			bubble_sort(t_venv **head);
int				insert_node_in_list(char *var, t_venv *head);

/*	---	utils_tab.c	---*/
int				tab_size(char **tab);

/*
	signals
*/

/*	---	signals.c	---*/
void			ft_init_signals(void (*handle_signals)(int));
void			signal_exec_handler(int sig);
extern void		rl_replace_line(const char *, int);
void			signal_child_handler(int sig);
void			signal_heredoc_handler(int sig);
void			ft_init_hd_signals(void (*handle_signals)(int));

/*
	expand
*/
/*	---	expand.c	---*/
void			ft_expand_token(t_minishell *shell);
char			*ft_expand_last_exit_status(t_minishell *ms);
void			ft_expand_venv(t_minishell *shell, char	*word);
char			*ft_dollar_alone(char *word, int *start, int *i);
void			ft_replace_token_content(t_minishell *shell, char **tmp);

/*	---	expand_utils.c	---*/
char			*ft_fill_word(char *word, int *start, int *i);
char			*ft_fill_word_expand(char *word, int *start, int *i);
char			*ft_get_venv_value(char *word, int *start,
					int *i, t_minishell *ms);
int				ft_token_has_dollar(char *word);
char			*ft_join_array(char **temp);

/*	---	expand_utils.c	---*/
void			ft_safe_free(char *str);

/*
	execute
*/
/*	---		exec_no_pipes.c	---*/
void			ft_exec_no_pipe(t_minishell *ms, char **envp);
void			child_exec_no_pipe(t_minishell *ms, char **env_tab);
void			parent_exec_no_pipe(pid_t *pid, int *exit_status,
					t_minishell *ms);

/*	---		exec_no_pipe_utils.c	---*/
void			ft_open_files_single_cmd(t_lcmd *cmd, t_minishell *ms);
void			ft_permission_denied_single_cmd(t_lcmd *cmd, t_minishell *ms);
void			ft_open_failed_single_cmd(t_lcmd *cmd, t_minishell *ms);

/*
	pipes
*/
/*	---		exec_pipes.c	---*/
void			ft_pipeline_execution(t_minishell *shell, char **envp);
int				ft_exec_child(t_lcmd *cmd, char **envp, t_minishell *ms);
void			ft_exec_parent(t_minishell *ms, t_lcmd *cmd, pid_t *pid);
void			ft_set_fd(t_pipex *p, t_lcmd *node);

/*	---	utils_pipes_1.c	---*/
char			*ft_get_right_path(char *cmd, t_minishell *ms);
char			*ft_get_path_line(t_minishell *ms);
char			*ft_join_path(char const *s1, char const *s2);
int				ft_count_cmds(t_lcmd *shell);
void			close_all_fds(t_minishell *ms);

/*	---	utils_pipes_2.c	---*/
int				improved_dup2(int fildes, int fildes2);
int				improved_pipe(int fd[2]);
pid_t			improved_fork(void);
void			sub_dup2(int read, int write);

/*	---	utils_pipes_3.c	---*/
void			ft_init_pipes_struct(t_minishell *shell);
int				ft_pipe_dep_mod(t_pipex *p);
void			ft_parent_close(t_minishell *ms);
void			ft_path_failed(char *str);
void			ft_open_files(t_lcmd *cmd, t_minishell *ms);

/*	---	utils_pipes_4.c	---*/
void			ft_set_fd_first(t_pipex *p, t_lcmd *node);

/*
	heredoc
*/
/*	---	heredoc_error.c	---*/
void			ft_memory_allocation_failed(void);

/*	---	heredoc_expand.c	---*/
char			*ft_list_to_char_expands(t_linked_list *head);
void			ft_replace_node_content(t_linked_list *node, t_minishell *ms);

/*	---	heredoc_list_utils.c	---*/
t_linked_list	*ft_insert_at_tail(t_linked_list *head, char *content);
void			free_linked_list(t_linked_list *head);

/*	---	heredoc_no_expand.c	---*/
t_linked_list	*ft_store_heredoc_content(char *eof);
void			handle_ctrl_d(void);
char			*ft_list_to_char(t_linked_list *head);
void			ft_write_to_temp_file(char *content);

/*	---	heredoc_utils.c	---*/
char			*ft_get_heredoc_eof_util(t_tok *tok);
char			*ft_get_heredoc_eof(t_minishell *shell);
int				ft_heredoc_detected(t_minishell *shell);
bool			ft_eof_quoted(char *eof);
t_linked_list	*ft_get_heredocs(t_tok *tokens);

/*	---	heredoc.c	---*/
void			ft_heredoc(t_minishell *shell);
int				ft_get_heredoc_temp_fd(t_tok **tk);

#endif