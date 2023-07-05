# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/26 16:58:39 by nvaubien          #+#    #+#              #
#    Updated: 2023/06/26 17:32:12 by nvaubien         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC						= gcc -g

#CFLAGS					:= -Wall -Wextra -Werror

NAME					:= minishell

LIB_DIRECTORY			:= ./libs/

LIBFT					:= $(LIBFT_DIRECTORY)libft.a
LIBFT_DIRECTORY			:= $(LIB_DIRECTORY)libft/

LIBPRINTF				:= $(LIBPRINTF_DIRECTORY)libftprintf.a # /libs/libftprinf/libftprintf.a
LIBPRINTF_DIRECTORY		:= $(LIB_DIRECTORY)ftprintf/ #/libs/ftprintf

SOURCES_DIRECTORY		:= ./srcs/

SOURCES_LIST			:= main.c 

OBJECTS_DIRECTORY		:= objs/
OBJECTS_LIST			:= $(patsubst %.c, %.o, $(SOURCES_LIST))
OBJECTS					:= $(addprefix $(OBJECTS_DIRECTORY), $(OBJECTS_LIST))

all: $(NAME)

$(OBJECTS_DIRECTORY):
	mkdir -p $(OBJECTS_DIRECTORY)

$(OBJECTS_DIRECTORY)%.o : $(SOURCES_DIRECTORY)%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	echo compilating libft
	$(MAKE) -sC $(LIBFT_DIRECTORY)
	cp libs/libft/libft.a .

$(LIBPRINTF):
	echo "$(NAME): Creating $(LIBPRINTF)..."
	$(MAKE) -sC $(LIBPRINTF_DIRECTORY)
	cp libs/ftprintf/libftprintf.a .

$(NAME): $(LIBFT) $(LIBPRINTF) $(OBJECTS_DIRECTORY) $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -Llibs/ftprintf -lftprintf -Llibs/libft -lft -lreadline -o $(NAME)

clean:
	$(MAKE) -sC $(LIBPRINTF_DIRECTORY) clean
	$(MAKE) -sC $(LIBFT_DIRECTORY) clean
	rm -rf $(OBJECTS_DIRECTORY)

fclean: clean
	$(MAKE) -sC $(LIBFT_DIRECTORY) fclean
	$(MAKE) -sC $(LIBPRINTF_DIRECTORY) fclean
	rm -f libft.a
	rm -f libftprintf.a
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re