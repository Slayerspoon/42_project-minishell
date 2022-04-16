/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aionescu <aionescu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 19:15:22 by aionescu          #+#    #+#             */
/*   Updated: 2022/04/06 22:35:36 by aionescu         ###   ########.fr       */
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

typedef struct s_data
{
	char	***commands; // format of [[command1, flag1, flag2, NULL], [command2, flag1, flag2, NULL], NULL], malloc'd
	char	***redirects; // format of [["<<", "frog"], [">", "file"], [NULL]] - NULL if no redirection for command at that index < infile cmd1 arg1 | cmd2 arg2 | cmd3 arg3 > outfile1 > outfile2 [[<, infile, NULL], [NULL], [>, outfile1, >, outfile2, NULL], NULL]
	char	**envp; // just envp
	char	**path; // path, malloc'd, used in execution
	char	*limiter; // limiter in case of '<<', otherwise NULL
	int		srcin; // 1 means '<' redirection, 2 means '<<' redirection
	int		srcout; // 1 means '>' redirection, 2 means '>>' redirection
	int		srcerr; // 1 means '>' redirection, 2 means '>>' redirection
	// Important to remember - 2> or 2>> redirects error instead of output
	// and in the same way &> redirects both out and err
	int		here_doc_fd; // used in execution
	char	*nameout; // name of the output file if needed, else NULL
	char	*namein; // name of the input file if needed, else NULL
	char	*namerr; // name of the error file if needed, else NULL
	int		pipes; // number of pipes
	int		exit_status; // exit status of last command, used in execution
}	t_data;

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

/* input_to_strings.c */
int		has_quote(char *start_ptr);
int		final_string_length(char *start_ptr);
int		count_needed_strings(char *input);
char	*generate_string(char *start_ptr, char **envp);
char	**input_to_strings(char *input, char **envp);

/* minishell_utils_strings.c */
char	*ft_strjoin_three(char *first, char *second, char *third);
char	*word_to_string(char *start_ptr);

/* minishell_utils_env.c */
char	*get_val_of_key(char *key_value_pair);
char	*get_env_var(char *var_name, char **envp);

//execute_utils.c and execute.c
char	*append_char(char *line, char c);
int		arr_length(char ***arr);
char	**get_path(char **envp);
void	execute_line(t_data *data);
void	free_arr(char **arr);
int		execute_built_in(t_data *data, int index);
void	exec_command(char **parsed, t_data *data);

//here_doc.c
int		open_file_write(char *name, int mode);
int		here_doc(t_data *data);

//input_output.c
int		redirect_input(t_data *data);
void	redirect_output(t_data *data);

//pipes.c
void	pipe_first_command(int *fd, t_data *data);
void	handle_pipes(int *fd, t_data *data);

#endif