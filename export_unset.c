/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpucylo <kpucylo@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 16:32:14 by kpucylo           #+#    #+#             */
/*   Updated: 2022/04/15 19:45:14 by kpucylo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

int	validity_check(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[0]))
		i = -1;
	while (i >= 0 && str[i])
	{
		if (str[i] == '=')
			return (i);
		if (!ft_isalnum(str[i]))
			break ;
		i++;
		if (i == (int)ft_strlen(str))
			return (0);
	}
	ft_putstr_fd("export: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": not a valid identifier", 2);
	return (0);
}

char	**append_array(char *str, char **array, int size)
{
	char	**temp;

	temp = malloc(sizeof(char *) * (size + 2));
	ft_memmove(temp, array, sizeof(char *) * size);
	temp[size] = str;
	temp[size + 1] = NULL;
	free(array);
	return (temp);
}

int	export2(char *cmd, t_data *data, int len, char *str)
{
	int	i;

	i = 0;
	while (data->envp[i])
	{
		if (!ft_strncmp(data->envp[i], cmd, len + 1))
		{
			free(data->envp[i]);
			data->envp[i] = str;
			return (0);
		}
		i++;
	}
	return (len);
}

int	export(char **cmd, t_data *data)
{
	int		i;
	int		len;
	int		retval;
	char	*str;

	i = 1;
	retval = 0;
	while (cmd[i])
	{
		len = validity_check(cmd[i]);
		if (!len)
		{
			retval = 1;
			continue ;
		}
		str = ft_strdup(cmd[i]);
		len = export2(cmd[i], data, len, str);
		if (len)
			data->envp = append_array(str, data->envp, i);
		i++;
		retval = 0;
	}
	return (retval);
}

int	unset(char **cmd, t_data *data)
{
	int	i;
	int	len;
	int	retval;

	retval = 0;
	i = 1;
	while (cmd[i])
	{
		retval = unset_error(cmd[i]);
		if (retval)
			continue ;
		i = 0;
		len = (int)ft_strlen(cmd[i]);
		unset2(data, cmd[i], len);
		i++;
	}
	return (retval);
}
