#ifndef EXEC_H
# define EXEC_H

# include <stdlib.h>
# include <stdio.h> //TODELETE
# include <stdbool.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
#include  <sys/stat.h>
#include  <fcntl.h>
#include "minishell.h"
#include "lexer.h"
#include "parsing.h"
#include "signal_handler.h"
#include "../libft/includes/libft.h"

//child_dup.c
int		write_dup(char *redirect, int *pipe_fd, int fd);
int		read_dup(char *redirect, int *pipe_fd, int previous_pipe, int fd);
void	child_init_pipes_dup(t_command *node, int *pipe_fd, int previous_pipe);

//child_pathed.c
void	childs_pathed_exec_failed(char **split_args, char **split_result,
    char *path, char **result);
void	childs_pathed_exec_final(char **split_args, char **split_result,
    char *path, int *fd);
void	childs_pathed_exec(char *cmd, int *fd, char *path);
//child_utils.c
char	*search_executable_in_paths(char **path_dirs, char *path_prefix,
    char *cmd_name, char *full_path);
char	*prepare_path_resolution(char *path, char *cmd);
char	*path_finder(char **env, char *cmd, char *path);
char	*free_arrays(char **one, char **two, char *three, char *four);
void	child_error(int infile, int *fd, int error, char *cmd);

//child.c
void child_redirect(t_command *node, char **env);

//exec.c
void	child_maker(t_command *node, int number_nodes);
bool	built_in_checker(char *cmd);
int	count_commands(t_command *cmds, bool *is_alone);
void	exec(t_command *node);

#endif