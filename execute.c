/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpucylo <kpucylo@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:31:14 by kpucylo           #+#    #+#             */
/*   Updated: 2022/04/06 13:57:03 by kpucylo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"

void	exec_command(char **parsed, t_data *data)
{
	char	*full_path;
	int		i;

	data->path = get_path(data->envp);
	i = -1;
	execve(parsed[0], parsed, data->envp);
	if (data->path)
	{
		while (data->path[++i])
		{
			full_path = ft_strjoin(data->path[i], parsed[0]);
			execve(full_path, parsed, data->envp);
			free(full_path);
		}
	}
	perror(parsed[0]);
	free_arr(parsed);
	exit(1);
}

// to be done when built-ins are implemented
int	execute_built_in(t_data *data, int index)
{
	return (-1);
}

void	execute_single_command(t_data *data)
{
	pid_t	pid;
	int		wstatus;

	if (data->commands[0][0] == 0)
	{
		pid = fork();
		if (pid == -1)
			perror("fork error");
		if (!pid)
			exec_command(data->commands[0], data);
		wait(&wstatus);
		data->exit_status = WEXITSTATUS(wstatus);
		return ;
	}
	else if (execute_built_in(data, 0) == -1)
	{
		pid = fork();
		if (pid == -1)
			perror("fork error");
		if (!pid)
			exec_command(data->commands[0], data);
		wait(&wstatus);
		data->exit_status = WEXITSTATUS(wstatus);
	}
}

void	execute_pipes(int *fd, t_data *data)
{
	pid_t	pid;
	int		wstatus;

	if (pipe(fd) == -1)
		perror("pipe error");
	pid = fork();
	if (pid == -1)
		perror("fork error");
	if (!pid)
		pipe_first_command(fd, data);
	else
	{
		wait(&wstatus);
		data->exit_status = WEXITSTATUS(wstatus);
		handle_pipes(fd, data);
	}
}

void	execute_line(t_data *data)
{
	int	fd[2];
	int	ret_val;

	if (data->srcin == 2)
	{
		ret_val = here_doc(data);
		if (ret_val == -1)
			return ;
		data->here_doc_fd = open("temp_file_frog", O_RDONLY, 0666);
		dup2(data->here_doc_fd, 0);
		unlink("temp_file_frog");
	}
	if (arr_length(data->commands) == 1)
	{
		redirect_output(data);
		if (data->srcin == 1)
		{
			if (redirect_input(data))
				return ;
		}
		execute_single_command(data);
	}
	else
		execute_pipes(fd, data);
}
