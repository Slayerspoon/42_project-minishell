/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_quoted_to_text.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpucylo <kpucylo@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 20:19:50 by aionescu          #+#    #+#             */
/*   Updated: 2022/04/05 19:22:27 by kpucylo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "./libft/libft.h"

/* Returns the name of an environment variable, interpreted just like bash. */
char	*identify_env_var(char *start_ptr)
{
	char	*identified_name;
	size_t	chars;

	start_ptr++;
	chars = 0;
	while (start_ptr[chars] != ' ' && start_ptr[chars] != '\"')
		chars++;
	identified_name = ft_calloc(chars + 1, sizeof(char));
	chars = 0;
	while (start_ptr[chars] != ' ' && start_ptr[chars] != '\"')
	{
		identified_name[chars] = start_ptr[chars];
		chars++;
	}
	printf("Here: %s\n", identified_name);
	return (identified_name);
}

char	*create_new_from_temp(char *temp)
{
	char	*new;

	new = ft_calloc(ft_strlen(temp) + 1, sizeof(char));
	ft_strlcpy(new, temp, ft_strlen(temp) + 1);
	return (new);
}

char	*single_quoted_to_text(char *original)
{
	char	*new;
	size_t	index;
	size_t	chars;

	chars = 0;
	index = 0;
	while (original[chars] != '\'')
		chars++;
	new = ft_calloc(chars + 1, sizeof(char));
	ft_strlcpy(new, original, chars + 1);
	return (new);
}

char	*double_quoted_to_text(char	*original, char **envp)
{
	char	*new;
	char	*temp;
	char	*env_var;
	size_t	index;

	temp = ft_calloc(1000000, 1);
	index = 0;
	while (original[index] != '\"')
	{
		if (original[index] != '$')
			ft_strlcat(temp, original + index, ft_strlen(temp) + 2);
		else
		{
			env_var = identify_env_var(original + index);
			ft_strlcat(temp, get_env_var(env_var, envp), 1000000);
			free(env_var);
			while (original[index] != ' ' && original[index] != '\"')
				index++;
			index--;
		}
		index++;
	}
	new = create_new_from_temp(temp);
	free(temp);
	return (new);
}

/* Generates a string from the quoted text containing VALUES instead of KEYS. */
/* Used on a pointer to the opening quote. */
char	*quoted_to_text(char *original, char quote, char **envp)
{
	char	*new;

	new = NULL;
	if (quote == '\'')
		new = single_quoted_to_text(original + 1);
	else
		new = double_quoted_to_text(original + 1, envp);
	return (new);
}
