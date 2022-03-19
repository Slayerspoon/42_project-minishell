/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aionescu <aionescu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 19:15:22 by aionescu          #+#    #+#             */
/*   Updated: 2022/03/19 19:33:09 by aionescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include <signal.h>
# include <term.h>
# include <termios.h>

/* check_quotes.c */
char	what_is_next_quote(char *str);
char	*find_next_quote(char *str, char quote);
int		check_all_quotes(char *str);

/* minishell_quoted_to_text.c */
char	*identify_env_var(char *start_ptr);
char	*create_new_from_temp(char *temp);
char	*single_quoted_to_text(char *original);
char	*double_quoted_to_text(char	*original, char **envp);
char	*quoted_to_text(char *original, char quote, char **envp);

/* join_quoted_and_adjacent.c */
char	*createstr_beforequote(char *start_ptr);
char	*find_afterquote(char *start_ptr);
char	*createstr_afterquote(char *start_ptr);
char	*join_quoted_and_adjacent(char *start_ptr, char quote, char **envp);

/* minishell_utils_strings.c */
char	*ft_strjoin_three(char *first, char *second, char *third);

/* minishell_utils_env.c */
char	*get_val_of_key(char *key_value_pair);
char	*get_env_var(char *var_name, char **envp);

#endif