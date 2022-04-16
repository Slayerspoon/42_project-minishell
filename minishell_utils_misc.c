/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_misc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aionescu <aionescu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 19:49:47 by aionescu          #+#    #+#             */
/*   Updated: 2022/04/13 19:52:39 by aionescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "./libft/libft.h"

int	count_pipes(char **terminal_array)
{
	int	pipes;
	int	index;

	pipes = 0;
	index = 0;
	while (terminal_array[index] != NULL)
	{
		if (ft_strncmp(terminal_array[index], "|\0", 2) == 0)
			pipes++;
		index++;
	}
	return (pipes);
}
