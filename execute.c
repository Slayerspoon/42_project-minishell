/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpucylo <kpucylo@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:31:14 by kpucylo           #+#    #+#             */
/*   Updated: 2022/03/29 15:00:10 by kpucylo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"

//execute command
void	execute(char **parsed, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		throw_error("Failed forking child", 1);
	else if (pid == 0)
	{
		ft_execvp(parsed[0], parsed, envp);
		perror(parsed[0]);
		exit(1);
	}
	wait(NULL);
}

//seperated because fuck you, thats why
void	pipe_child(char **parsed, char **envp, int pipe_fd[2])
{
	close(pipe_fd[0]);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	ft_execvp(parsed[0], parsed, envp);
	perror(parsed[0]);
	exit(1);
}

//bruh
void	pipe_second_child(char **parsed_pipe, char **envp, int pipe_fd[2])
{
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	ft_execvp(parsed_pipe[0], parsed_pipe, envp);
	perror(parsed_pipe[0]);
	exit(1);
}

//execute when piping (not sure how to indicate its needed yet)
//making a struct with the command and flags might work
//	linked list kinda thingie with indicators on pipes/redirections??
void	exec_piped(char **parsed, char **parsed_pipe, char **envp)
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
		pipe_child(parsed, envp, pipe_fd);
	}
	else
	{
		p2 = fork();
		if (p2 == -1)
			throw_error("Failed forking child", 1);
		if (p2 == 0)
		{
			pipe_second_child(parsed_pipe, envp, pipe_fd);
		}
		else
			be_patient(2);
	}
}
