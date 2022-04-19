/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aionescu <aionescu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 19:09:27 by aionescu          #+#    #+#             */
/*   Updated: 2022/04/19 18:47:24 by aionescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	what_is_next_quote(char *str)
{
	int	index;

	index = 0;
	while (str[index] != '\0')
	{
		if (str[index] == '\'' || str[index] == '\"')
			return (str[index]);
		index++;
	}
	return (str[index]);
}

char	*find_next_quote(char *str, char quote)
{
	int		index;

	index = 0;
	while (str[index] != '\0')
	{
		if (str[index] == quote)
			return (str + index);
		index++;
	}
	return (NULL);
}

/* Returns 0 (correct) if all quotes are closed OR if there are no quotes. */
int	check_all_quotes(char *str)
{
	char	quote;
	char	*current_char_ptr;

	current_char_ptr = str;
	while (42 == 42)
	{
		quote = what_is_next_quote(current_char_ptr);
		if (quote == '\0')
			return (0);
		current_char_ptr = find_next_quote(current_char_ptr, quote);
		if (*(current_char_ptr + 1) != '\0')
			current_char_ptr = find_next_quote(current_char_ptr + 1, quote);
		else
			return (1);
		if (current_char_ptr == NULL)
			return (1);
		current_char_ptr++;
	}
	return (0);
}
