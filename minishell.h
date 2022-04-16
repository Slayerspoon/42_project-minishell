/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aionescu <aionescu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 19:15:22 by aionescu          #+#    #+#             */
/*   Updated: 2022/04/16 19:26:35 by aionescu         ###   ########.fr       */
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
	char	***commands; // format of [[command1, flag1, flag2], [command2, flag1, flag2]], malloc'd
	char	***redirects; // format of [["<<", "frog"], [">", "file"], [NULL]] - NULL if no redirection for command at that index
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
	int		orig_fds[3];
}	t_data;

enum
{
	OUT,
	ERR,
	BOTH
};

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
int		count_strings(char **terminal_input);

/* minishell_utils_env.c */
char	*get_val_of_key(char *key_value_pair);
char	*get_env_var(char *var_name, char **envp);

/* minishell_utils_misc.c */
int		count_pipes(char **terminal_array);

/* redirection_checks.c */
int		check_double_brackets(char **term_input, int term_index);
int		check_single_brackets(char **term_input, int term_index);
int		is_redirection(char **term_input, int term_index);
int		check_for_redirections(char **term_input, int term_index);

/* generate_commands_array.c */
char	***init_commands_array(int nelem);
int		check_for_redirections(char **terminal_input, int terminal_index);
char	**generate_command(char **terminal_input, int terminal_index, int nel);
char	***generate_commands_array(char **term_input);

/* generate_redirections_array.c */
char	***init_redirections_array(int nelem);
void	insert_redirection(char **redir_arr, int nel, char **t_inp, int t_ind);
char	**generate_redirection(char **term_input, int term_i, int nelem);
char	***generate_redirections_array(char **term_input);

//execute_utils.c and execute.c
char	*append_char(char *line, char c);
int		arr_length(char ***arr);
char	**get_path(char **envp);
void	execute_line(t_data *data);
void	free_arr(char **arr);
int		execute_built_in(t_data *data, int index);
void	exec_command(char **parsed, t_data *data);
//error has to be equal to 0 - norm always finds a way to fuck with me
//for the same reason i has to be 0
int		set_data(t_data *data, int id, int error, int i);

//here_doc.c
int		open_file_write(char *name, int mode);
int		here_doc(t_data *data);

//input_output.c
int		redirect_input(t_data *data);
int		redirect_output(t_data *data);
int		is_err_append(char *str);
int		is_both_trunc(char *str);
int		is_both_append(char *str);

//pipes.c
void	pipe_first_command(int *fd, t_data *data);
void	handle_pipes(int *fd, t_data *data);

//redirects.c and redirects_utils.c
int		is_heredoc(char *str);
int		is_input(char *str);
int		is_out_trunc(char *str);
int		is_out_append(char *str);
int		is_err_trunc(char *str);
int		execute_heredoc(t_data *data, char *limiter);
int		execute_in(t_data *data, char *file);
int		execute_trunc(t_data *data, char *file, int fd);
int		execute_append(t_data *data, char *file, int fd);

//misc.c
int		throw_error(char *str, int code);
void	dup_and_close(int fd1, int fd2);
void	set_null(t_data *data);
void	clean_exit(t_data *data, int status, int flag);
void	free_3d_arr(char ***arr);

//signals.c
int		catch_signal(int sig, void (*handler)(int));
void	handle_signal(int sig);

//struct_handling.c
void	init(t_data *data, char **envp, int mode);

//builtins.c, export_unset.c and export_unset2.c
int		echo(char **cmd);
int		cd(char **cmd, t_data *data);
int		pwd(char **cmd);
int		env(char **cmd, t_data *data);
int		ft_exit(char **cmd, t_data *data);
int		export(char **cmd, t_data *data);
void	unset2(t_data *data, char *cmd, int len);
int		unset_error(char *str);

//main.c
char	**copy_array(char **array);
void	cleanup(char *line, t_data *data);

#endif