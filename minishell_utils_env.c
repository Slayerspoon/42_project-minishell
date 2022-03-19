/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_env.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aionescu <aionescu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 18:55:30 by aionescu          #+#    #+#             */
/*   Updated: 2022/03/15 21:26:47 by aionescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include <stdio.h>

/* Returns the chars present AFTER the '=' sign in the KEY=VALUE pair. */
char	*get_val_of_key(char *key_value_pair)
{
	char	*value;
	size_t	index;
	size_t	useful_chars;

	index = 0;
	while (key_value_pair[index] != '=')
		index++;
	index++;
	useful_chars = ft_strlen(key_value_pair + index);
	value = ft_calloc(useful_chars + 1, sizeof(char));
	ft_strlcpy(value, key_value_pair + index, useful_chars + 1);
	return (value);
}

/* Returns the value stored in the environment variable. */
char	*get_env_var(char *var_name, char **envp)
{
	char	*var_value;
	size_t	index;

	printf("var_name is: §%s§\n", var_name);
	var_value = NULL;
	index = 0;
	while (envp[index] != NULL)
	{
		if (ft_strncmp(envp[index], var_name, ft_strlen(var_name))
			&& ft_strnstr(envp[index], "=", ft_strlen(var_name) + 1))
		{
			var_value = get_val_of_key(envp[index]);
			break ;
		}
		index++;
	}
	return (var_value);
}
