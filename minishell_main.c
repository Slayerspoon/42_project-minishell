/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aionescu <aionescu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 19:15:09 by aionescu          #+#    #+#             */
/*   Updated: 2022/03/15 21:25:26 by aionescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "./libft/libft.h"

int	count_char_occurence(char *str, char c, int size)
{
	int	index;
	int	count;

	index = 0;
	count = 0;
	while (index < size && str[index] != '\0')
	{
		if (str[index] == c)
			count++;
		index++;
	}
	return (count);
}

int	main(int argc, char **argv, char **envp)
{
	char	*example_str = "\" na $XXX na \"";
	char	*result_str;

	result_str = quoted_to_text(example_str, '\"', envp);
	printf("The quoted text was interpreted as: §%s§\n", result_str);
	printf("argc %d, argv %s, envp %s\n", argc, argv[0], envp[0]);
	while (ft_strncmp(readline("yourShitHere>"), "exit\0", 5))
	{
		printf("Your input was not 'exit'.\n");
	}
	return (0);
}
