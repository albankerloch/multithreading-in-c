#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akerloc- <akerloc-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/12 17:40:07 by akerloc-          #+#    #+#              #
#    Updated: 2020/01/26 13:14:04 by akerloc-         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

SRCS =	main.c \
	arg.c \
	thread_philo.c \
	ft_atoi.c \
	ft_putlnbr_mess.c \
	ft_strlen.c \
	ft_isdigit.c
OBJS = ${SRCS:.c=.o}
NAME = philo_one
HEADER = .
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I .
LIBS = -lpthread

all : ${NAME}

clean : 
		rm -f ${OBJS}

fclean : clean
		rm -f ${NAME}
		$(RM) $(NAME) $(MLX)

$(NAME) : ${OBJS}
		gcc -o ${NAME} ${OBJS} ${CFLAGS} ${LIBS}

re : fclean all

.PHONY : all clean re fclean
