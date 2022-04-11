/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpucylo <kpucylo@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 14:50:25 by kpucylo           #+#    #+#             */
/*   Updated: 2022/04/11 15:36:35 by kpucylo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

char	*get_prompt(void)
{
	char	*cwd;
	char	*temp;
	char	*prompt;
	char	**temp_arr;
	int		i;

	cwd = NULL;
	cwd = getcwd(cwd, 0);
	temp_arr = ft_split(cwd, '/');
	free(cwd);
	i = 0;
	while (temp_arr[i])
		i++;
	if (!temp_arr[0])
		temp = ft_strjoin("minishell ", "/");
	else
		temp = ft_strjoin("minishell ", temp_arr[i - 1]);
	prompt = ft_strjoin(temp, " $ ");
	free(temp);
	free_arr(temp_arr);
	return (prompt);
}

char	**copy_array(char **array)
{
	char	**retval;
	int		i;

	i = 0;
	while (array[i])
		i++;
	retval = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (array[i])
	{
		retval[i] = ft_strdup(array[i]);
		i++;
	}
	retval[i] = 0;
	return (retval);
}

void	get_input(char **line)
{
	char	*prompt;
	catch_signal(SIGINT, handle_signal);
	catch_signal(SIGQUIT, handle_signal);
	prompt = get_prompt();
	line[0] = readline((const char *) prompt);
	free(prompt);
}

void	cleanup(char *line)
{
	free(line);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	char	*line;

	if (argc != 1 || argv[0] == 0)
		exit(1);
	data = malloc(sizeof(t_data));
	init(data, envp);
	while (!data->exit)
	{
		get_input(&line);
		if (!line)
			clean_exit(data, 0);
		if (*line)
		{
			add_history(line);
			//parsing goes here
			// execute_line(data);
			while (wait(0) != -1)
				continue ;
		}
		cleanup(line);
	}
}
