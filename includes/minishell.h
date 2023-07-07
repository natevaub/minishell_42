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
char	*ft_get_word_space(char **str);
char	*ft_get_word_red(char **str, char c);

/*
	UTILS
*/
/* utils1.c */
int	ft_strcmp(char *str, char *comp);

/*
	BUILTINS
*/
/*	---	builtin_decide.c	---*/
void	builtin_redirect(t_global *global, char *cmd, char *var);
int		builtin_check(char *cmd);
/*	---	builtin_echo.c	---*/
char	*get_value(t_venv *env, void *var);
int		cmd_echo(char **cmd, char *option, t_venv *head, bool single_quotes, bool double_quotes);
/*	---	builtin_env.c	---*/
int		find_c(char *str, char c);
int		print_env(t_venv *copy_env);
/*	---	builtin_exit.c	---*/
void	cmd_exit(int status);
/*	---	builtin_export.c	---*/
int	check_var_format(void *var);
char	*trim_back(void *var);
bool	existing_var_in_env(void *var, t_venv *head);
int		add_var_export(void *var, t_venv **head);
int		print_export(t_venv *env_for_export);
/*	---	builtin_pwd_cd.c	---*/
int		cmd_cd(char *to_go_path);
int		cmd_pwd(void);
/*	---	builtin_unset.c	---*/
int		cmd_unset(void *var, t_venv **head);
/*	---	utils_linked_list_1.c	---*/
int		list_size(t_venv *lst);
t_venv	*last_node(t_venv *lst);
t_venv	*first_node(t_venv *lst);
t_venv	*get_node(t_venv *head, int index);
void	list_append(t_venv **lst, char *element);
/*	---	utils_linked_list_2.c	---*/
t_venv	*new_env_list(char **tab);
void	content_swap(t_venv *one, t_venv *two);
void	bubble_sort(t_venv **head);


#endif