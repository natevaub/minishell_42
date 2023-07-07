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
char	*ft_get_word(char **str);

/*	---tokenize_prompt.c	--- */
void	ft_tokenize_prompt(t_minishell *global, char *prompt);
char	*ft_get_tk(char **prompt);
int		ft_get_tk_type(char *str);

/*
	UTILS
*/

/*	--- utils1.c	--- */
int		ft_strcmp(char *str, char *comp);

/*	--- utils_linked_list.c --- */

/*
	BUILTINS
*/

/*	---	builtin_decide.c	---*/
// void	builtin_redirect(t_global *global, char *cmd, char *var);
// int		builtin_check(char *cmd);

#endif