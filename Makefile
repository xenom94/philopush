# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iabboudi <iabboudi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/20 22:42:32 by iabboudi          #+#    #+#              #
#    Updated: 2024/12/23 22:23:16 by iabboudi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRCS = main.c init.c routine.c stop_and_join.c tools.c helper.c
OBJS = $(SRCS:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror 

all: $(NAME)	
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "\033[1;32m- philo compiled!\033[0m"
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJS)
	@echo "\033[1;33m- Object files removed!\033[0m"

fclean: clean
	rm -f $(NAME)
	@echo "\033[1;31m- philo deleted!\033[0m"

re: fclean all 

.PHONY: all clean fclean re
