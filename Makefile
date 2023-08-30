	### COMPILATION ###
CC			:=	gcc
CFLAGS		:=	-Wall -Wextra -Werror #-fsanitize=address #-g3

	### EXECUTABLE ###
NAME		:=	minishell

	### PATH ###
SRCS_PATH	:= srcs
OBJS_PATH	:= objs
INCS_PATH	:= -Iincludes

	### LIBS ###
# LIBFT		:= ./libs/libft
# FTPRINTF	:= ./libs/ftprintf

LIB_DIRECTORY			:= ./libs/
LIBFT					:= $(LIBFT_DIRECTORY)libft.a
LIBFT_DIRECTORY			:= $(LIB_DIRECTORY)libft/

LIBPRINTF				:= $(LIBPRINTF_DIRECTORY)libftprintf.a #/libs/libftprinf/libftprintf.a
LIBPRINTF_DIRECTORY		:= $(LIB_DIRECTORY)ftprintf/ #/libs/ftprintf

	### SOURCE FILES ###
MAIN_FILE	:= minishell.c

CMDLINE_FILES	:=	prompt.c					\

SYNTAX_FILES	:=	syntax_pipe.c				\
					syntax_quote.c				\
					syntax_red.c				\
					syntax.c					\

UTILS_FILES	:=		utils_parsing.c				\
					utils_linked_list.c			\

INITMS_FILES	:=	init_global.c				\
					init_fd_redirection.c		\
					init_env.c					\
					close.c						\

EXEC_FILES	:=		exec_no_pipe.c				\
					exec_no_pipe_utils.c		\

EXPAND_FILES	:=	expand.c					\
					expand_utils.c				\
					expand_utils2.c				\

PARSE_FILES	:=		get_token_type.c			\
					get_joined_token.c			\
					get_parsed_token.c			\
					get_trimmed_token.c			\
					get_len_word.c				\
					get_word.c					\
					parsing_checker.c			\
					parsing_free_memory.c		\
					tokenize_prompt.c			\

BUILTIN_FILES :=	builtin_decide.c		\
					builtin_echo.c			\
					builtin_env.c			\
					builtin_exit.c			\
					builtin_exit_utils.c	\
					builtin_export.c		\
					builtin_pwd_cd.c		\
					builtin_unset.c			\
					utils_linked_list_1.c	\
					utils_linked_list_2.c	\
					utils_tab.c				\

SIGNAL_FILES :=		signals.c				\

PIPE_FILES :=		exec_pipes.c			\
					utils_pipes_1.c			\
					utils_pipes_2.c			\
					utils_pipes_3.c			\
					utils_pipes_4.c			\

HEREDOC_FILES :=	heredoc_error.c			\
					heredoc_expand.c		\
					heredoc_list_utils.c	\
					heredoc_no_expand.c		\
					heredoc_utils.c			\
					heredoc.c				\

	### OBJECTS ###
CMDLINE_FILES := $(addprefix $(OBJS_PATH)/cmd_line/, $(CMDLINE_FILES:.c=.o))
INITMS_FILES := $(addprefix $(OBJS_PATH)/init_minishell/, $(INITMS_FILES:.c=.o))
PARSE_FILES	:= $(addprefix $(OBJS_PATH)/parser/, $(PARSE_FILES:.c=.o))
EXEC_FILES	:= $(addprefix $(OBJS_PATH)/execute/, $(EXEC_FILES:.c=.o))
EXPAND_FILES	:= $(addprefix $(OBJS_PATH)/expand/, $(EXPAND_FILES:.c=.o))
UTILS_FILES := $(addprefix $(OBJS_PATH)/utils/, $(UTILS_FILES:.c=.o))
BUILTIN_FILES := $(addprefix $(OBJS_PATH)/builtins/, $(BUILTIN_FILES:.c=.o))
SIGNAL_FILES := $(addprefix $(OBJS_PATH)/signals/, $(SIGNAL_FILES:.c=.o))
SYNTAX_FILES := $(addprefix $(OBJS_PATH)/syntax/, $(SYNTAX_FILES:.c=.o))
MAIN_FILE	:= $(addprefix $(OBJS_PATH)/, $(MAIN_FILE:.c=.o))
PIPE_FILES :=	$(addprefix $(OBJS_PATH)/pipes/, $(PIPE_FILES:.c=.o))
HEREDOC_FILES := $(addprefix $(OBJS_PATH)/heredoc/, $(HEREDOC_FILES:.c=.o))

OBJS		:=	$(PARSE_FILES)			\
				$(UTILS_FILES)			\
				$(MAIN_FILE)			\
				$(BUILTIN_FILES)		\
				$(CMDLINE_FILES)		\
				$(INITMS_FILES)			\
				$(SIGNAL_FILES)			\
				$(EXEC_FILES)			\
				$(SYNTAX_FILES)			\
				$(PIPE_FILES)			\
				$(EXPAND_FILES)			\
				$(HEREDOC_FILES)		\


	### COLORS ###
RED			= \033[1;31m
GREEN		= \033[1;32m
YELLOW		= \033[1;33m
BLUE		= \033[1;34m
VIOLET		= \033[1;35m
CYAN		= \033[1;36m
WHITE		= \033[1;37m
RESET		= \033[0m

	### LIBS PATH ###
# LIBS_PATH	:= -L$(LIBFT_DIRECTORY) -L$(LIBPRINTF_DIRECTORY)
LIBS		:= -L$(LIB_DIRECTORY) -lft -lftprintf -lreadline

all:	$(NAME)

$(LIBFT):
	@echo "$(GREEN)Compilating Libft$(RESET)"
	@$(MAKE) -sC $(LIBFT_DIRECTORY)
	@echo "$(CYAN)✔️  Compilation Done$(RESET)"
	@cp libs/libft/libft.a .

$(LIBPRINTF):
	@echo "$(GREEN)Compilating Libftprinf$(RESET)"
	@$(MAKE) -sC $(LIBPRINTF_DIRECTORY)
	@echo "$(CYAN)✔️  Compilation Done$(RESET)"
	@cp libs/ftprintf/libftprintf.a .

$(NAME):	$(LIBFT) $(LIBPRINTF) $(OBJS)
			@echo "$(GREEN)Compilating minishell$(RESET)"
			@$(CC) $(CFLAGS) -Llibs/ftprintf -Llibs/libft -L/Users/ckarl/homebrew/opt/readline/lib -I/Users/ckarl/homebrew/opt/readline/include/readline -Llibs/libft -o $@ $(OBJS) $(LIBS)
			@echo "$(CYAN)✔️  Compilation Done$(RESET)"
# -L/Users/ckarl/homebrew/opt/readline/lib -I/Users/ckarl/homebrew/opt/readline/include/readline
# -L/Users/nvaubien/.brew/Cellar/readline/8.2.1/lib -I/Users/nvaubien/.brew/Cellar/readline/8.2.1/include/readline
# -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include/readline

tmp:d
			@mkdir -p objs

$(OBJS_PATH)/%.o:	$(SRCS_PATH)/%.c
					@mkdir -p $(@D)
					@$(CC) $(CFLAGS) $(INCS_PATH) -c $< -o $@

clean:
			@echo "$(RED) Cleaning Directory /libs/libftprinf$(RESET)"
			@$(MAKE) -sC $(LIBPRINTF_DIRECTORY) clean
			@echo "$(RED) Cleaning Directory /libs/libft$(RESET)"
			@$(MAKE) -sC $(LIBFT_DIRECTORY) clean
			@echo "$(RED) Cleaning Directory /objs$(RESET)"
			@rm -rf $(OBJS_PATH)

fclean:		clean
			@$(MAKE) -sC $(LIBFT_DIRECTORY) fclean
			@$(MAKE) -sC $(LIBPRINTF_DIRECTORY) fclean
			@echo "$(RED) rm libft.a libftprintf.a minishell$(RESET)"
			@rm -f libft.a
			@rm -f libftprintf.a
			@rm -rf $(NAME)

re:			fclean all

.PHONY: all clean fclean re
