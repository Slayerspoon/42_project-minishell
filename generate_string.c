/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aionescu <aionescu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 18:42:20 by aionescu          #+#    #+#             */
/*   Updated: 2022/04/21 21:23:55 by aionescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "minishell.h"

/* Generates and returns the next string for the array of strings. */
char	*parse_word(char *start_ptr, t_data *data)
{
	char	*new_str;
	int		index;
	char	*temp;

	index = 0;
	temp = ft_calloc(1000000, sizeof(char));
	while (start_ptr[index] != ' ' && start_ptr[index] != '\t'
		&& start_ptr[index] != '\0')
	{
		if (start_ptr[index] == '\'')
			index = index + handle_single_q(start_ptr + index, temp);
		else if (start_ptr[index] == '\"')
			index = index + handle_double_q(start_ptr + index, temp, data);
		else if (start_ptr[index] == '$')
			index = index + handle_env_var(start_ptr + index, temp, data);
		else
			ft_strlcat(temp, start_ptr + index, ft_strlen(temp) + 1 + 1);
		index++;
	}
	new_str = ft_strdup(temp);
	free(temp);
	return (new_str);
}
