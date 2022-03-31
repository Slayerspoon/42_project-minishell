/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpucylo <kpucylo@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:19:13 by kpucylo           #+#    #+#             */
/*   Updated: 2022/03/31 11:14:05 by kpucylo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"

//for convenience
void	throw_error(char *message, int code)
{
	printf("%s\n", message);
	exit(code);
}

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

//recreation of execvp so i dont have to deal with this bullshit multiple times
//try as a relative and absolute path, instead of just envp
void	ft_execvp(char *cmd, char **flags, char **envp)
{
	char	**paths;
	char	*command;
	int		i;

	paths = get_path(envp);
	i = 0;
	execve(cmd, flags, envp);
	while (paths[i])
	{
		command = ft_strjoin(paths[i], cmd);
		execve(command, flags, envp);
		free(command);
		i++;
	}
}

//wait for *amount* of processes
void	be_patient(int amount)
{
	int	i;

	i = 0;
	while (i < amount)
	{
		wait(NULL);
		i++;
	}
}
