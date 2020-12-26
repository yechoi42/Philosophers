# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yechoi <yechoi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/04 19:10:20 by yechoi            #+#    #+#              #
#    Updated: 2020/12/26 21:46:10 by yechoi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	main.c init.c check.c utils.c utils2.c

OBJS		= 	$(SRCS:.c=.o)

CC			=	gcc

FLAG		= 	-Wall -Wextra -Werror

INCLUDES	= 	-I./

NAME		=	philo_one

.c.o		:
			$(CC) $(FLAG) -c $< -o $(<:.c=.o) $(INCLUDES)

all			: $(NAME)

$(NAME)		: $(OBJS)
		$(CC) $(FLAG) $(OBJS) -o $(NAME) $(INCLUDES)

clean		:
		rm -rf $(OBJS)

fclean		: clean
		rm -rf $(NAME)

re			: fclean all

.PHONY 		: all clean fclean re
