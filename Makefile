	### COMPILATION ###
CC			:=	gcc
CFLAGS		:=	-Wall -Wextra -Werror

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

PARSE_FILES	:= ft_get_word.c

	### OBJECTS ###
PARSE_FILES	:= $(addprefix $(OBJS_PATH)/parser/, $(PARSE_FILES:.c=.o))
MAIN_FILE	:= $(addprefix $(OBJS_PATH)/, $(MAIN_FILE:.c=.o))
# PARSE_FILES	:= $(addprefix $(OBJS_PATH)/parser/, $(PARSE_FILES))

OBJS		:=	$(PARSE_FILES)	\
				$(MAIN_FILE)	\
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
			@$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

tmp:
			@mkdir -p objs

$(OBJS_PATH)/%.o:	$(SRCS_PATH)/%.c
					@mkdir -p $(@D)
					@$(CC) $(CFLAGS) $(INCS_PATH) -c $< -o $@

clean:
			@make fclean -C $(LIBFT)
			@make fclean -C $(FTPRINTF)
			@rm -rf $(OBJS_PATH)

fclean:		clean
			@rm -rf $(NAME)

re:			fclean all

.PHONY: all clean fclean re