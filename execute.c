/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpucylo <kpucylo@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:31:14 by kpucylo           #+#    #+#             */
/*   Updated: 2022/03/28 15:23:42 by kpucylo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"

//execute command
void	execute(char *cmd, char **flags, char **envp)
{
	char	**paths;
	char	*command;
	int		i;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		throw_error("Failed forking child", 1);
	else if (pid == 0)
	{
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
	wait(NULL);
}

//seperated because fuck you, thats why
void	pipe_child(char *cmd, char **flags, char **envp, int pipe_fd[2])
{
	int		i;
	char	*command;
	char	**paths;

	close(pipe_fd[0]);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
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

//bruh
void	pipe_second_child(char *cmd, char **flags, char **envp, int pipe_fd[2])
{
	int		i;
	char	*command;
	char	**paths;

	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
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

void	exec_piped(char *cmd, char **flags, char **envp)
{
	int		pipe_fd[2];
	pid_t	p1;
	pid_t	p2;

	if (pipe(pipe_fd) == -1)
		throw_error("Failed to create pipe", 1);
	p1 = fork();
	if (p1 == -1)
		throw_error("Failed forking child", 1);
	if (p1 == 0)
	{
		pipe_child(cmd, flags, envp, pipe_fd);
	}
	else
	{
		p2 = fork();
		if (p2 == -1)
			throw_error("Failed forking child", 1);
		if (p2 == 0)
		{
			pipe_second_child(cmd, flags, envp, pipe_fd);
		}
		else
			be_patient(2);
	}
}
