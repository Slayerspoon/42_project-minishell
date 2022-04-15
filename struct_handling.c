/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpucylo <kpucylo@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 14:04:44 by kpucylo           #+#    #+#             */
/*   Updated: 2022/04/15 16:00:07 by kpucylo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

void	init(t_data *data, char **envp, int mode)
{
	data->commands = NULL;
	data->redirects = NULL;
	if (mode == 0)
		data->envp = copy_array(envp);
	data->path = NULL;
	data->limiter = NULL;
	data->pipes = 0;
	data->nameout = NULL;
	data->namein = NULL;
	data->namerr = NULL;
	if (mode == 0)
		data->exit_status = 0;
	data->orig_fds[0] = dup(0);
	data->orig_fds[1] = dup(1);
	data->orig_fds[2] = dup(2);
}
