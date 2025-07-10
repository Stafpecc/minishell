#ifndef EXEC_H
# define EXEC_H
# define MALLOC_ERROR -42
# define NONE -42
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include "builtin.h"
# include "minishell.h"
# include "lexer.h"
# include "parsing.h"
# include "return_error.h"
# include "signal_handler.h"
# include "../libft/includes/libft.h"

# define MAX_HEREDOC_ATTEMPTS 100

//child_dup_utils.c
int		write_dup(t_redirect **redirect, int *pipe_fd);
int		read_dup(t_redirect **redirect, int previous_pipe);
int		redirect_write_browser(t_redirect **redirect, int i);
int		redirect_read_browser(t_redirect **redirect, int i);

//child_dup.c
void	child_init_pipes_dup(t_command_exec *node, int *pipe_fd,
			t_utils *utils);
void	only_child(t_command_exec *node, int *pipe_fd, t_utils *utils);

//child_execute.c
void	path_finder_fail(t_command_exec *node, t_utils *utils, bool execve_failed, int return_value);
void	close_free_utils(t_utils *utils, size_t i);
void	close_t_command_exec(t_command_exec *node, t_command_exec *tmp,
			size_t i);

//child_utils.c
char	*search_executable_in_paths(char **path_dirs, char *path_prefix,
			char *cmd_name, char *full_path);
//char	*prepare_path_resolution(char *path, char *cmd);
char	*path_finder(char **env, char *cmd, char *path);
char	*free_arrays(char **one, char **two, char *three, char *four);
void	child_error(int infile, int *fd, int error, char *cmd);

//child.c
void	child_redirect(t_command_exec *node, t_utils *utils);

//exec_utils.c
bool	built_in_checker(char *cmd);
int		count_commands(t_command_exec *cmds);
size_t	ft_env_len(char **env);
int		count_commands(t_command_exec *cmds);
int		expand_env(t_utils *utils);
int		condense_env(t_utils *utils);

//exec.c
int		child_maker(t_command_exec *node, t_utils *utils, int i);
int		exec(t_command_exec *node, t_utils *utils);

//here_doc.c
int		here_doc(char *delimiter);
//single_builtin.c
int		single_built_in(t_command_exec *node, t_utils *utils);

//exit.c
int		print_exit(long long code, char *arg, bool too_many_arguments,
			t_utils *utils);

//exit_utils.c
int			is_arg_digit_and_overflow(char *arg, t_utils *utils);

#endif