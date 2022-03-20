# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aionescu <aionescu@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/02 19:14:52 by aionescu          #+#    #+#              #
#    Updated: 2022/03/20 21:18:28 by aionescu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT = libft.a

SRC = minishell_main.c check_quotes.c minishell_utils_strings.c \
		minishell_utils_env.c minishell_quoted_to_text.c \
		join_quoted_and_adjacent.c input_to_strings.c

all: $(NAME)

$(NAME): $(LIBFT)
	$(CC) -Wall -Wextra -Werror $(SRC) $(LIBFT) -lreadline -L /usr/local/opt/readline/lib/ -I /usr/local/opt/readline/include/ -o $(NAME)
	rm -f *.o
	chmod a+x $(NAME)

$(LIBFT):
	cd libft && $(MAKE) fclean
	cd libft && $(MAKE)
	mv ./libft/libft.a libft.a

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re
