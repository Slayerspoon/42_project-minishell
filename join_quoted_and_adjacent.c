/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_quoted_and_adjacent.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aionescu <aionescu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 19:23:38 by aionescu          #+#    #+#             */
/*   Updated: 2022/03/19 19:45:52 by aionescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "minishell.h"

/* Creates a string containing only the characters before a quoted part. */
char	*createstr_beforequote(char *start_ptr)
{
	char	*beforequote;
	char	quote;
	size_t	index;

	index = 0;
	quote = what_is_next_quote(start_ptr);
	while (start_ptr[index] != quote)
		index++;
	beforequote = ft_calloc(index + 1, sizeof(char));
	index = 0;
	while (start_ptr[index] != quote)
	{
		beforequote[index] = start_ptr[index];
		index++;
	}
	return (beforequote);
}

/* Returns a pointer to the first adjacent character after a quoted part. */
char	*find_afterquote(char *start_ptr)
{
	char	*afterquote_ptr;
	char	quote;
	int		quote_no;
	size_t	index;

	index = 0;
	quote = what_is_next_quote(start_ptr);
	quote_no = 0;
	while (start_ptr[index] != '\0' && quote_no < 2)
	{
		if (start_ptr[index] == quote)
			quote_no++;
		index++;
	}
	afterquote_ptr = &(start_ptr[index]);
	return (afterquote_ptr);
}

/* Creates a string containing only the characters after a quoted part. */
char	*createstr_afterquote(char *start_ptr)
{
	char	*afterquote_str;
	char	*afterquote_ptr;
	size_t	index;

	afterquote_ptr = find_afterquote(start_ptr);
	index = 0;
	while (afterquote_ptr[index] != ' ' && afterquote_ptr[index] != '\0')
		index++;
	afterquote_str = ft_calloc(index + 1, sizeof(char));
	index = 0;
	while (afterquote_ptr[index] != ' ' && afterquote_ptr[index] != '\0')
	{
		afterquote_str[index] = afterquote_ptr[index];
		index++;
	}
	return (afterquote_str);
}

/* Creates one string containing a quoted part and its adjacent characters. */
/* !!! Input string has to be verified for adjacency BEFOREHAND !!! */
char	*join_quoted_and_adjacent(char *start_ptr, char quote, char **envp)
{
	char	*beforequote_ptr;
	char	*quoted_ptr;
	char	*afterquote_ptr;
	char	*joined;
	size_t	index;

	index = 0;
	while (start_ptr[index] != quote)
		index++;
	beforequote_ptr = createstr_beforequote(start_ptr);
	quoted_ptr = quoted_to_text(&(start_ptr[index]), quote, envp);
	afterquote_ptr = createstr_afterquote(start_ptr);
	joined = ft_strjoin_three(beforequote_ptr, quoted_ptr, afterquote_ptr);
	free(beforequote_ptr);
	free(quoted_ptr);
	free(afterquote_ptr);
	return (joined);
}
