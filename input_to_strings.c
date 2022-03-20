/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_to_strings.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aionescu <aionescu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 18:56:37 by aionescu          #+#    #+#             */
/*   Updated: 2022/03/20 21:38:34 by aionescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "minishell.h"

/* Determines whether the next potentially mergeable string has a quote. */
int	has_quote(char *start_ptr)
{
	int	quotes;
	int	index;

	index = 0;
	quotes = 0;
	while (start_ptr[index] != '\0')
	{
		if (start_ptr[index] == '\'' || start_ptr[index] == '\"')
			quotes++;
		if (start_ptr[index] == ' ')
		{
			if (quotes == 0)
				return (0);
			else
				return (1);
		}
		index++;
	}
	if (quotes == 0)
		return (0);
	else
		return (1);
}

/* Returns the length of the potentially mergeable string. */
int	final_string_length(char *start_ptr)
{
	int	quotes;
	int	index;
	int	length;

	index = 0;
	quotes = 0;
	length = 0;
	while (start_ptr[index] != '\0')
	{
		if (start_ptr[index] == '\'' || start_ptr[index] == '\"')
			quotes++;
		if (start_ptr[index] == ' ' && quotes % 2 == 0)
			return (length);
		length++;
		index++;
	}
	return (length);
}

/* Returns the number of strings needed for the final array of strings. */
int	count_needed_strings(char *input)
{
	int		count;
	size_t	index;

	count = 0;
	index = 0;
	while (input[index] != '\0')
	{
		if (input[index] == ' ')
			index++;
		else
		{
			count++;
			index = index + final_string_length(input + index);
		}
	}
	return (count);
}

/* Generates and returns the next string for the array of strings. */
char	*generate_string(char *start_ptr, char **envp)
{
	char	*new_str;
	char	quote;

	if (has_quote(start_ptr))
	{
		quote = what_is_next_quote(start_ptr);
		new_str = join_quoted_and_adjacent(start_ptr, quote, envp);
	}
	else
		new_str = word_to_string(start_ptr);
	return (new_str);
}

/* Generates an array of strings based on the terminal input. */
char	**input_to_strings(char *input, char **envp)
{
	char	**array_of_strings;
	size_t	index;
	int		count;

	count = count_needed_strings(input);
	array_of_strings = malloc(sizeof(char *) * (count + 1));
	count = 0;
	index = 0;
	while (input[index] != '\0')
	{
		if (input[index] == ' ' || input[index] == '\t')
			index++;
		else
		{
			array_of_strings[count] = generate_string(input + index, envp);
			count++;
			index = index + final_string_length(input + index);
		}
	}
	return (array_of_strings);
}
