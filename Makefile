# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aestraic <aestraic@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/22 13:20:07 by aestraic          #+#    #+#              #
#    Updated: 2023/02/06 19:15:21 by aestraic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRC = 	threads.c\
		time.c\
		init.c\
		routine.c\
		utils.c\
		libft.c\
		main.c\

OBJ  = $(SRC:.c=.o)

C_FLAGS = -Wall -Wextra -Werror
HEADER_PATH = header

all: $(NAME)

%.o : %.c
	gcc $(C_FLAGS) -I$(HEADER_PATH) -c $^
	
$(NAME): $(OBJ)
	gcc -g $(C_FLAGS) -Ofast -o $(NAME) $(SRC) -I$(HEADER_PATH) -pthread

val:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)

clean:
	@rm -f $(OBJ) $(OBJ_B)
	@echo Objectfiles removed

fclean: clean
	@rm -f $(NAME)
	@echo Libraries and exeutables removed
	
re: fclean all
	@echo REDONE

.PHONY: clean fclean re all bonus val