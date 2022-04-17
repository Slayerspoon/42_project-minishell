/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_strings.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aionescu <aionescu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 19:14:08 by aionescu          #+#    #+#             */
/*   Updated: 2022/04/17 14:41:30 by aionescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "minishell.h"

char	*ft_strjoin_three(char *first, char *second, char *third)
{
	char	*final_str;
	size_t	str_len;
	size_t	index;

	str_len = 0;
	str_len = str_len + ft_strlen(first);
	str_len = str_len + ft_strlen(second);
	str_len = str_len + ft_strlen(third);
	final_str = ft_calloc(str_len + 1, sizeof(char));
	index = 0;
	ft_strlcpy(final_str, first, ft_strlen(first) + 1);
	ft_strlcat(final_str, second, ft_strlen(first) + ft_strlen(second) + 1);
	ft_strlcat(final_str, third, str_len + 1);
	return (final_str);
}

void	merge_chars_and_env_val(char *merged, char *start_ptr, char *env_val)
{
	int		index;

	index = 0;
	while (start_ptr[index] != '\0' && start_ptr[index] != ' '
		&& start_ptr[index] != '\t')
	{
		if (start_ptr[index] == '$')
		{
			ft_strlcat(merged, env_val, index + ft_strlen(env_val) + 1);
			free(env_val);
			break ;
		}
		merged[index] = start_ptr[index];
		index++;
	}
}

/* Reads until '\0' or ' ' or '\t' and creates and returns a string from it. */
char	*word_to_string(char *start_ptr, char **envp, t_data *data)
{
	char	*str;
	char	*env_var;
	char	*env_val;
	size_t	index;

	env_val = ft_calloc(1, sizeof(char));
	index = 0;
	while (start_ptr[index] != '\0' && start_ptr[index] != ' '
		&& start_ptr[index] != '\t')
	{
		if (start_ptr[index] == '$')
		{
			env_var = identify_env_var(start_ptr + index);
			free(env_val);
			env_val = get_env_var(env_var, envp, data);
			free(env_var);
			break ;
		}
		index++;
	}
	str = ft_calloc(index + ft_strlen(env_val) + 1, sizeof(char));
	merge_chars_and_env_val(str, start_ptr, env_val);
	return (str);
}

/* Returns the number of strings in an array of strings. */
int	count_strings(char **terminal_input)
{
	int	count;

	count = 0;
	if (terminal_input != NULL)
	{
		while (terminal_input[count] != NULL)
		count++;
	}
	return (count);
}
