# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/06 22:47:34 by dmlitvin          #+#    #+#              #
#    Updated: 2019/09/18 11:52:45 by dmlitvin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=minishell

LIBFT=libft/libft.a

INCLUDE=libft/include

FLAGS=-Wall -Wextra -Werror

CC=clang

SRC=main.c env.c execute.c built_ins1.c built_ins2.c \
	expansion.c find_executable.c minishell_split.c

SRO=$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(SRO) $(LIBFT)
	@$(CC) $(SRO) $(LIBFT) -o $(NAME) && printf '\x1b[32mBinary file compiled \
	succesfully!\nLaunch: ./$(NAME)\n\x1b[0m'

$(SRO): $(LIBFT) $(SRC) minishell.h
	@$(CC) -c $(SRC) $(FLAGS) -I $(INCLUDE) && \
	printf '\x1b[32mObject files compiled succesfully!\n\x1b[0m'

$(LIBFT):
	@make -C libft/

clean:
	@rm -f $(SRO) && printf '\x1b[31mObject files have been deleted!\n\x1b[0m'
	@make clean -C libft/

fclean: clean
	@rm -f $(NAME) && printf '\x1b[31mBinary file has been deleted!\n\x1b[0m'
	@make fclean -C libft/

re: fclean all

.PHONY: re clean fclean all
