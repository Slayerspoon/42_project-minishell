/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpucylo <kpucylo@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:31:14 by kpucylo           #+#    #+#             */
/*   Updated: 2022/03/21 16:48:13 by kpucylo          ###   ########.fr       */
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

//execute command (no pipes for now)
void	execute(char *cmd, char **flags, char **envp)
{
	char	**paths;
	char	*command;
	int		i;

	paths = get_path(envp);
	i = 0;
	while (paths[i])
	{
		command = ft_strjoin(paths[i], cmd);
		execve(command, flags, envp);
		free(command);
		i++;
	}
	perror(flags[0]);
	exit(1);
}
