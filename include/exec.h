/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 14:34:52 by stafpec           #+#    #+#             */
/*   Updated: 2025/07/16 17:24:41 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
# define MALLOC_ERROR -42
# define NONE -42
//# include "../libft/includes/libft.h"
# include "builtin.h"
//# include "lexer.h"
//# include "minishell.h"
//# include "parsing.h"
//# include "return_error.h"
//# include "signal_handler.h"
# include <errno.h>
# include <fcntl.h>
//# include <stdbool.h>
//# include <stdlib.h>
//# include <sys/stat.h>
//# include <sys/types.h>
# include <sys/wait.h>
//# include <unistd.h>

# define MAX_HEREDOC_ATTEMPTS 100

// child_dup_utils.c
int		write_dup(t_redirect **redirect, int *pipe_fd);
int		read_dup(t_redirect **redirect, int previous_pipe);
int		redirect_write_browser(t_redirect **redirect, int i);
int		redirect_read_browser(t_redirect **redirect, int i);

// child_dup.c
void	child_init_pipes_dup(t_command_exec *node, int *pipe_fd,
			t_utils *utils);
void	only_child(t_command_exec *node, int *pipe_fd, t_utils *utils);

// child_err_msg.c
bool	join_err_msg_and_write(char *part_one_msg, char *part_two_msg,
			char *part_three_msg);

// child_execute.c
void	path_finder_fail(t_command_exec *node, t_utils *utils,
			bool execve_failed, int return_value);
void	close_free_utils(t_utils *utils, size_t i);
void	close_t_command_exec(t_command_exec *node, t_command_exec *tmp,
			size_t i);

// child_pathed.c
void	childs_pathed_exec_failed(char **split_args, char **split_result,
			char *path, char **result);
void	childs_pathed_exec_final(char **split_args, char **split_result,
			char *path, int *fd);
void	childs_pathed_exec(char *cmd, int *fd, char *path);
// child_utils.c
char	*search_executable_in_paths(char **path_dirs, char *path_prefix,
			char *cmd_name, char *full_path);
char	*prepare_path_resolution(char *path, char *cmd);
char	*path_finder(char **env, char *cmd, char *path);
char	*free_arrays(char **one, char **two, char *three, char *four);
int		close_and_set_none(int previous_pipe, int *pipe_fd);
// child.c
void	child_redirect(t_command_exec *node, t_utils *utils);

// exec_utils.c
bool	built_in_checker(char *cmd);
int		count_commands(t_command_exec *cmds);
size_t	ft_env_len(char **env);
int		count_commands(t_command_exec *cmds);
int		expand_env(t_utils *utils);
int		condense_env(t_utils *utils);

// exec.c
int		child_maker(t_command_exec *node, t_utils *utils);
int		exec(t_command_exec *node, t_utils *utils);

// here_doc.c
int		here_doc(char *delimiter);
// single_builtin.c
int		single_built_in(t_command_exec *node, t_utils *utils);

// exit.c
int		print_exit(long long code, char *arg, bool too_many_arguments,
			t_utils *utils);

// exit_utils.c
int		is_arg_digit_and_overflow(char *arg, t_utils *utils);

// child_maker.c
int		wait_for_children_and_cleanup(t_utils *utils, int status, int *pipe_fd,
			pid_t child);
int		setup_coming_child_pipes(t_utils *utils, int *pipe_fd, int i);
pid_t	child_secure_fork(t_command_exec *node, t_utils *utils,
			int *pipe_fd, pid_t *child);
int		setup_next_child(t_utils *utils, int *pipe_fd, int i);

// child_maker_helper.c
int		initialize_child_maker(t_command_exec *node, t_utils *utils,
			int *pipe_fd);
int		fork_all_children(t_command_exec *node, t_utils *utils, int *pipe_fd,
			pid_t *child);
void	close_heredoc_fds(t_command_exec *head);

#endif