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
void		ft_init_minishell(t_minishell *shell, t_global *global, char **env);

/*	--- init_env.c	--- */
char		**ft_get_env(void);
void		free_two_dimension_array(char **arr);

<<<<<<< HEAD
/*	--- init_fd_redirection	--- */
int			ft_error_red_file(char	*file);
int			ft_get_infile_fd(t_tok **tk);
int			ft_get_outfile_fd(t_tok **tk);
int			ft_get_append_outfile_fd(t_tok **tk);
void		ft_open_files_redirection(t_tok **tk, t_cmd *cmd);


=======
>>>>>>> refs/remotes/origin/main
/*
	PARSER
*/
/*	---	get_len_word.c	---*/
int			ft_len_red(char *str, char c);
int			ft_len_space(char *str);
int			ft_len_word(char *str);
int			ft_len_quote(char *str, char c);
/*	---	get_token_type.c	--- */
int			ft_is_red(char *prompt);
int			ft_red_type(char *prompt);
int			ft_is_pipe(char *prompt);
int			ft_is_space(char *prompt);
/*	---	get_word.c	--- */
char		*ft_get_word_space(char **str);
char		*ft_get_word_red(char **str, char c);
char		*ft_get_word(char **str);

/*	--- parsing_checker.c	--- */
void		ft_printlist_tk(t_tok *global);

/*	---tokenize_prompt.c	--- */
void		ft_tokenize_prompt(t_minishell *global, char *prompt);
char		*ft_get_tk(char **prompt);
int			ft_get_tk_type(char *str);
int			ft_get_quoted_tk(char *prompt);

/*
	UTILS
*/

/*	--- utils1.c	--- */
int			ft_strcmp(char *str, char *comp);


/*	--- utils_linked_list.c	--- */
t_tok		*ft_newlst_token(char *word);
void		ft_lstadd_back_token(t_tok **lst, t_tok *nw);

/* utils1.c */
int			ft_strcmp(char *str, char *comp);
char 		*ft_strcat(char *dest, char *src);

/*
	BUILTINS
*/
/*	---	builtin_decide.c	---*/
void		builtin_redirect(t_global *global, char *cmd, char **option);
int			builtin_check(char *cmd);

/*	---	builtin_echo.c	---*/
char		*get_value(t_venv *env, void *var);
int			cmd_echo(char **option, t_global *global, bool single_quotes, bool double_quotes);

/*	---	builtin_env.c	---*/
int			find_c(char *str, char c);
int			print_env(t_venv *copy_env);

/*	---	builtin_exit.c	---*/
void		cmd_exit(int status);

/*	---	builtin_export.c	---*/
int			check_var_format(char *var);
char		*trim_back(char *var);
bool		existing_var_in_env(char *var, t_venv *head);
int			add_var_to_export(char **var, t_venv **head);
int			print_export(t_venv *env_for_export);

/*	---	builtin_pwd_cd.c	---*/
int			cmd_cd(t_venv *copy_env, char *to_go_path);
int			cmd_pwd(void);

/*	---	builtin_unset.c	---*/
int			cmd_unset(char **var, t_venv **head);

/*	---	utils_linked_list_1.c	---*/
int		list_size(t_venv *lst);
t_venv	*last_node(t_venv *lst);
t_venv	*first_node(t_venv *lst);
t_venv	*get_node(t_venv *head, int index);
void	list_append(t_venv **lst, char *element);

/*	---	utils_linked_list_2.c	---*/
t_venv		*new_env_list(char **tab);
void		content_swap(t_venv *one, t_venv *two);
void		bubble_sort(t_venv **head);
int			insert_node_in_list(char *var, t_venv **head);

/*
	SIGNALS
*/

/*	---	signals.c	---*/
void	init_signals(struct sigaction *s);
void	signal_handler(int signal);

#endif