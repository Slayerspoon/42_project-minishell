/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_strings.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aionescu <aionescu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 19:14:08 by aionescu          #+#    #+#             */
/*   Updated: 2022/03/15 20:26:01 by aionescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"

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
