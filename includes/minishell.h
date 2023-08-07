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


extern t_global	global;

# define ERR_CMD		"Enter valid command "
# define ERR_EXEC		"Execve "
# define DEBUG 0


/*
	CMD_LINE
*/
/*	--- prompt.c	--- */
char		*ft_get_command_line(void);
char		*ft_output_command_line(void);

/*
	INIT_MINISHELL
*/
/*	--- init_global.c	--- */
char		**ft_get_opt(char **option, char **tmp);
int			ft_len_cmd_opt(char **options);
t_cmd		*ft_init_cmds(t_tok **tokens);
char		**ft_store_cmd_options(t_tok **tokens, t_cmd *cmd);
void		ft_init_minishell(t_minishell *shell, char **env);

/*	--- init_env.c	--- */
char		**ft_get_env(void);
void		free_two_dimension_array(char **arr);

/*	--- init_fd_redirection	--- */
int			ft_error_red_file(char	*file);
int			ft_get_infile_fd(t_tok **tk);
int			ft_get_outfile_fd(t_tok **tk);
int			ft_get_append_outfile_fd(t_tok **tk);
void		ft_open_files_redirection(t_tok **tk, t_cmd *cmd);

/*	--- close.c	--- */
void 		free_env_list(t_venv *env_list);

/*
	SYNTAX
*/
/*	--- syntax_pipe.c	--- */
int			ft_syntax_pipe_check(t_tok *syntax);
int			ft_pipe_error(t_tok *syntax);

/*	--- syntax_red.c	--- */
int			ft_syntax_red_check(t_tok *tok);
int			ft_red_error(t_tok *tk);

/*	--- syntax_quote.c	--- */
int			ft_syntax_quote_check(char *str);
int			ft_syntax_open_quote_check(char *str, char c, int *i);

/*	--- syntax.c	--- */
int			ft_syntax_checker(t_minishell *shell);
int			ft_look_for_err(t_tok *tok);
void		ft_print_error(int err);

/*
	PARSER
*/

/* ---	get_joined_token.c	--- */
int			ft_is_joinable(t_tok *token);
int			ft_join_tk(t_tok *tk);
void		ft_strcat_join_tk(char *s1, char *s2, int *i, int *j);
void		ft_get_joined_tk(t_tok *tok, char *n_tk);

/*	---	get_len_word.c	--- */
int			ft_len_red(char *str, char c);
int			ft_len_space(char *str);
int			ft_len_word(char *str);
int			ft_len_quote(char *str, char c);

/*	--- get_parsed_token.c	---*/
void		ft_parse_token(t_minishell *shell);
void		ft_parsing(t_minishell *shell, char *prompt);

/*	--- get_trimmed_quote	--- */
void		ft_trim_quote(t_minishell *shell);

/*	---	get_token_type.c	--- */
int			ft_is_builtins(char *prompt);
int			ft_is_red(char *prompt);
int			ft_red_type(char *prompt);
int			ft_is_pipe(char *prompt);
int			ft_is_space(char *prompt);
/*	---	get_word.c	--- */
char		*ft_get_word_quote(char **prompt, char c);
char		*ft_get_word_space(char **str);
char		*ft_get_word_red(char **str, char c);
char		*ft_get_word(char **str);

/*	--- parsing_checker.c	--- */
void		ft_print_tokens(t_tok *token);
void		ft_print_cmds(t_lcmd *cmd);

/*	--- parsing_free_memory.c	--- */
void		ft_free_token(t_minishell **shell);
void		ft_free_cmd(t_minishell *shell);
void		ft_free_parsing(t_minishell *shell);

/*	---tokenize_prompt.c	--- */
void		ft_tokenize_prompt(t_minishell *global, char *prompt);
char		*ft_get_tk(char **prompt);
int			ft_get_tk_type(char *str);
int			ft_get_quoted_tk(char *prompt);

/*
	UTILS
*/
/*	--- utils_linked_list.c	--- */
t_lcmd		*ft_newlst_cmd(t_cmd *cmd);
t_tok		*ft_newlst_token(char *word);
void		ft_lstadd_back_token(t_tok **lst, t_tok *nw);
void		ft_lstadd_back_cmd(t_lcmd **lst, t_lcmd *nw);

/* utils1.c */
int			ft_strcmp(char *str, char *comp);
char 		*ft_strcat(char *dest, char *src);

/*
	BUILTINS
*/
/*	---	builtin_decide.c	---*/
void		builtin_redirect(t_lcmd *cmd);
int			builtin_check(char *cmd);

/*	---	builtin_echo.c	---*/
char		*get_value(t_venv *env, void *var);
int			cmd_echo(t_lcmd *cmd);

/*	---	builtin_env.c	---*/
int			find_c(char *str, char c);
int			print_env(t_lcmd *cmd);

/*	---	builtin_exit.c	---*/
void		cmd_exit(char *status);
void		change_shvl_in_env(int nbr);

/*	---	builtin_export.c	---*/
int			check_var_format(char *var);
char		*trim_back(char *var);
int			change_existing_var_in_env(char *var);
int			add_var_to_export(char **option);
int			print_export(t_lcmd *cmd);

/*	---	builtin_pwd_cd.c	---*/
int			cmd_cd(t_lcmd *cmd);
int			cmd_pwd(t_lcmd *cmd);

/*	---	builtin_unset.c	---*/
int			cmd_unset(char **var);

/*	---	utils_linked_list_1.c	---*/
int			list_size(t_venv *lst);
t_venv		*last_node(t_venv *lst);
t_venv		*first_node(t_venv *lst);
t_venv		*get_node(t_venv *head, int index);
void		list_append(t_venv **lst, char *element);

/*	---	utils_linked_list_2.c	---*/
t_venv		*new_env_list(char **tab);
void		content_swap(t_venv *one, t_venv *two);
void		bubble_sort(t_venv **head);
int			insert_node_in_list(char *var, t_venv **head);

/*	---	utils_tab.c	---*/
int			total_len_tab(char **tab);
int			tab_size(char **tab);
char		*ft_strndup(char *s, char n);

/*
	EXPAND
*/
/*	---	var_expand.c	---*/
char		*expanded_value(char *trimmed);
char		**expanded_tab(char *trimmed);
char		*expanded_exit_value(char *word);
char		*expanded_join(char *front, char **exp_tab, char *value);
char		*get_expand_var(char *var);

/*
	SIGNALS
*/

/*	---	signals.c	---*/
extern void	rl_replace_line(const char *, int);
void		init_signals(void);
void		signal_handler(int signal);

/*
	EXPAND
*/
void		ft_expand_token(t_minishell *shell);
void		ft_skip_dollar_alone(char *word);
int			ft_token_has_dollar(char *word);
char		*ft_expand_last_exit_status(void);
char		*ft_fill_word(char *word, int *start, int *i);
void		ft_expand_venv(t_minishell *shell, char	*word);
char		*ft_get_venv_value(char *word, int *start, int *i);
char		*ft_join_array(char *temp[256]);


/*
	EXECUTE
*/
void		ft_exec_no_pipe(t_minishell *ms);
void		child_exec_no_pipe(t_minishell *ms, char **env_tab);

/*
	PIPES
*/

/*	---	pipes_execution.c	---*/
int			exec_pipe(t_minishell *ms, char **envp);
void		child_exec(t_lcmd *cmd, char **env_tab, t_minishell *ms);
void		run_cmd(t_lcmd *cmd, t_minishell *ms, char **envp);

/*	---	pipes_init.c	---*/
void		init_pipex_struct(t_minishell *ms);
void		set_pipe_fds(t_minishell *ms);

/*	---	improved_syscalls.c	---*/
int			improved_dup2(int fildes, int fildes2);
void		sub_dup2(int read, int write);
int			improved_pipe(int fd[2]);
pid_t		improved_fork(void);

/*	---	utils_list_pipes.c	---*/
void		list_append_pipes(t_lcmd **lst, char *command, int w_pipe, int r_pipe);
t_lcmd		*last_node_pipes(t_lcmd *lst);
t_lcmd		*get_node_lcmd(t_lcmd *head, int index);
int			total_len_cmd(t_lcmd *commands);
void		print_list_fds(t_lcmd *list);

/*	---	utils_memory_pipes.c	---*/
int			error(char *str);
void		close_pipes(t_minishell *ms);
void		final_free_and_close(t_minishell *ms);

/*	---	utils_path_pipes.c	---*/
char		*get_path_line(void);
char		*get_right_path(char *cmd);

/*	---	utils_strings_pipes.c	---*/
char		*ft_join_path(char const *s1, char const *s2);
char		**env_list_to_env_tab(void);

/*
	PIPES2
*/
int			ft_count_cmds(t_lcmd *shell);
void		ft_init_pipes_struct(t_minishell *shell, t_pipex *pipe);
int			ft_pipeline_execution(t_minishell *shell, char **envp);
int			ft_set_fd(t_minishell *shell, t_pipex *p);
int			ft_exec_cmd(t_lcmd *cmd, char **envp);
char		*ft_get_right_path(char *cmd);
char		*ft_get_path_line(void);

#endif