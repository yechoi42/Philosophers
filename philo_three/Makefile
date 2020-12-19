# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yechoi <yechoi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/04 19:10:20 by yechoi            #+#    #+#              #
#    Updated: 2020/12/20 01:00:19 by yechoi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	main.c init.c check.c utils.c utils2.c 

CC			=	gcc

FLAG		= 	-Wall -Wextra -Werror

INCLUDES	= 	-I./

NAME		=	philo_three

all			: $(NAME)

$(NAME)		: 
		$(CC) $(FLAG) $(SRCS) -o $(NAME) $(INCLUDES)

clean		:
		rm -rf $(OBJS)

fclean		: clean
		rm -rf $(NAME)

re			: fclean all

.PHONY 		: all clean fclean re