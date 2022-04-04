/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpucylo <kpucylo@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:19:13 by kpucylo           #+#    #+#             */
/*   Updated: 2022/04/04 17:26:00 by kpucylo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"

//get array of possible paths from PATH
char	**get_path(char **envp)
{
	int		i;
	char	*str;
	char	**path;

	i = 0;
	while (!ft_strnstr(envp[i], "PATH=", 5))
		i++;
	str = ft_strtrim(envp[i], "PATH=");
	path = ft_split(str, ':');
	free(str);
	i = 0;
	while (path[i])
	{
		str = ft_strjoin(path[i], "/");
		free(path[i]);
		path[i] = str;
		i++;
	}
	return (path);
}

char	*append_char(char *line, char c)
{
	char	*new_line;
	int		i;

	i = (int)ft_strlen(line);
	new_line = malloc(sizeof(char) * (i + 2));
	ft_memcpy(new_line, line, i);
	new_line[i] = c;
	new_line[i + 1] = 0;
	free(line);
	return (new_line);
}

int	arr_length(char ***arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	free_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}
