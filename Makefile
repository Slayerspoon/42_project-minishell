# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kpucylo <kpucylo@student.42wolfsburg.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/02 19:14:52 by aionescu          #+#    #+#              #
#    Updated: 2022/04/15 18:29:52 by kpucylo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT = libft.a

SRC = main.c check_quotes.c minishell_utils_strings.c \
		minishell_utils_env.c minishell_quoted_to_text.c \
		join_quoted_and_adjacent.c input_to_strings.c \
		execute_utils.c execute.c here_doc.c input_output.c \
		misc.c pipes.c redirects_utils.c redirects.c signals.c \
		struct_handling.c builtins.c export_unset.c export_unset2.c

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
