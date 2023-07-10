	### COMPILATION ###
CC			:=	gcc -g
# CFLAGS		:=	-Wall -Wextra -Werror

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

UTILS_FILES	:=		utils_parsing.c				\
					utils_linked_list.c			\


PARSE_FILES	:=		get_token_type.c			\
					get_len_word.c				\
					get_word.c					\
					parsing_checker.c			\
					tokenize_prompt.c			\

BUILTIN_FILES :=	builtin_decide.c		\
					builtin_echo.c			\
					builtin_env.c			\
					builtin_exit.c			\
					builtin_export.c		\
					builtin_pwd_cd.c		\
					builtin_unset.c			\
					utils_linked_list_1.c	\
					utils_linked_list_2.c	\

	### OBJECTS ###
CMDLINE_FILES := $(addprefix $(OBJS_PATH)/cmd_line/, $(PARSE_FILES:.c=.o))
PARSE_FILES	:= $(addprefix $(OBJS_PATH)/parser/, $(PARSE_FILES:.c=.o))
UTILS_FILES := $(addprefix $(OBJS_PATH)/utils/, $(UTILS_FILES:.c=.o))
BUILTIN_FILES := $(addprefix $(OBJS_PATH)/builtins/, $(BUILTIN_FILES:.c=.o))
MAIN_FILE	:= $(addprefix $(OBJS_PATH)/, $(MAIN_FILE:.c=.o))
# PARSE_FILES	:= $(addprefix $(OBJS_PATH)/parser/, $(PARSE_FILES))

OBJS		:=	$(PARSE_FILES)	\
				$(UTILS_FILES)	\
				$(MAIN_FILE)	\
				$(BUILTIN_FILES)\
# OBJS		:= $(patsubst $(SRCS_PATH)/%.c, $(OBJS_PATH)/%.o, $(PARSE_FILES))


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
	echo compilating libft
	$(MAKE) -sC $(LIBFT_DIRECTORY)
	cp libs/libft/libft.a .

$(LIBPRINTF):
	echo "$(NAME): Creating $(LIBPRINTF)..."
	$(MAKE) -sC $(LIBPRINTF_DIRECTORY)
	cp libs/ftprintf/libftprintf.a .

$(NAME):	$(LIBFT) $(LIBPRINTF) $(OBJS)
			@$(CC) $(CFLAGS) -Llibs/ftprintf -lftprintf -Llibs/libft -lft -o $@ $(OBJS) $(LIBS)

tmp:
			@mkdir -p objs

$(OBJS_PATH)/%.o:	$(SRCS_PATH)/%.c
					@mkdir -p $(@D)
					@$(CC) $(CFLAGS) $(INCS_PATH) -c $< -o $@

	$(MAKE) -sC $(LIBPRINTF_DIRECTORY) clean

clean:
			$(MAKE) -sC $(LIBPRINTF_DIRECTORY) clean
			$(MAKE) -sC $(LIBFT_DIRECTORY) clean
			@rm -rf $(OBJS_PATH)
			# rm libft.a
			# rm libftprinf.a

fclean:		clean
			$(MAKE) -sC $(LIBFT_DIRECTORY) fclean
			$(MAKE) -sC $(LIBPRINTF_DIRECTORY) fclean
			rm -f libft.a
			rm -f libftprintf.a
			rm -f $(NAME)
			# @rm -rf $(NAME)

re:			fclean all

.PHONY: all clean fclean re
