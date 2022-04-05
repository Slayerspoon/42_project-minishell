/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpucylo <kpucylo@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:58:34 by kpucylo           #+#    #+#             */
/*   Updated: 2022/04/05 12:59:56 by kpucylo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

void	redirect_output(t_data *data)
{
	int	fd_file_out;
	int	fd_file_err;

	if (data->srcout != 0)
	{
		fd_file_out = open_file_write(data->nameout, data->srcout);
		if (fd_file_out == -1)
			perror(data->nameout);
		else
		{
			dup2(fd_file_out, 1);
			close(fd_file_out);
		}
	}
	if (data->srcerr != 0)
	{
		fd_file_err = open_file_write(data->namerr, data->srcerr);
		if (fd_file_err == -1)
			perror(data->namerr);
		else
		{
			dup2(fd_file_err, 2);
			close(fd_file_err);
		}
	}
}

int	redirect_input(t_data *data)
{
	int	fd_file_in;

	if (data->srcin != 0)
	{
		if (!access(data->namein, F_OK))
		{
			fd_file_in = open(data->namein, O_RDONLY, 0666);
			if (fd_file_in == -1)
			{
				perror(data->namein);
				return (1);
			}
			else
			{
				dup2(fd_file_in, 0);
				close(fd_file_in);
			}
		}
		else
		{
			perror(data->namein);
			return (1);
		}
	}
	return (0);
}
