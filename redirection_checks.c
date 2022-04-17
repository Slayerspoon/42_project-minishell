/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_checks.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpucylo <kpucylo@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 21:02:03 by aionescu          #+#    #+#             */
/*   Updated: 2022/04/16 20:04:34 by kpucylo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "./libft/libft.h"

/* Returns the number of strings to skip from the index of the "<<" or ">>" */
int	check_double_brackets(char **term_input, int term_index)
{
	int	count;

	count = 0;
	if (ft_strlen(term_input[term_index]) == 2)
	{
		if (term_input[term_index + 1] != NULL)
			return (2);
		else
			return (1);
	}
	else
		return (1);
}

/* Returns the number of strings to skip from the index of the "<" or ">" */
int	check_single_brackets(char **term_input, int term_index)
{
	int	count;

	count = 0;
	if (ft_strlen(term_input[term_index]) == 1)
	{
		if (term_input[term_index + 1] != NULL)
			return (2);
		else
			return (1);
	}
	else
		return (1);
}

/* Checks if there is a redirection at the current index. */
/* It will return 2 in case of a space or tab after the operator. */
/* It will return 1 in case the operator and the file name are merged. */
/* It will return 0 in case there is no redirection at the given index. */
int	is_redirection(char **term_input, int term_index)
{
	int	count;

	count = 0;
	if (ft_strncmp(term_input[term_index], "<<", 2) == 0
		|| ft_strncmp(term_input[term_index], ">>", 2) == 0)
	{
		count = check_double_brackets(term_input, term_index);
	}
	else if (ft_strncmp(term_input[term_index], "<", 1) == 0
		|| ft_strncmp(term_input[term_index], ">", 1) == 0)
	{
		count = check_single_brackets(term_input, term_index);
	}
	return (count);
}

/* Checks if there is a redirection at the current index. */
/* Returns the number of indexes to skip in the array of strings. */
int	check_for_redirections(char **term_input, int term_index)
{
	int	count;

	count = 0;
	while (term_input[term_index] != NULL)
	{
		if (is_redirection(term_input, term_index) == 1)
		{
			term_index = term_index + 1;
			count = count + 1;
		}
		else if (is_redirection(term_input, term_index) == 2)
		{
			term_index = term_index + 2;
			count = count + 2;
		}
		else
			break ;
	}
	return (count);
}