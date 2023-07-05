# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/17 10:21:03 by nvaubien          #+#    #+#              #
#    Updated: 2022/11/17 11:31:56 by nvaubien         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libftprintf.a

CC		= cc

CFLAGS 	= -Wall -Wextra -Werror

SRCS	=	ft_printf_utils.c		\
			ft_printf.c				\
			ft_putnbr_base.c		\
			ft_count_size.c			\

OBJS	= ${SRCS:.c=.o}

RM		=	rm -f

all: ${NAME}

${NAME}: ${OBJS}
		ar rcs ${NAME} ${OBJS}

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		clean fclean all