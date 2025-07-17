/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 14:55:15 by ldevoude          #+#    #+#             */
/*   Updated: 2025/07/17 16:10:28 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
# include "minishell.h"

# define NOT_NUM_ARG 2
# define OLD 0
# define NEW 1

typedef enum e_error_msg
{
	ERR_CD_CHDIR,
	ERR_CD_GETCWD,
	ERR_CD_MALLOC,
	ERR_CD_NOMSG,
}	t_error_msg;

//cd_utils.c
int				return_errors(int return_value, int message,
					t_command_exec *node);

//cd.c
int				cd_builtin(t_command_exec *node, t_utils *utils,
					int pwd_emplacement, int pwd_old_emplacement);

//echo.c
int				echo_builtin(t_command_exec *node, bool newline, int i);

//env.c
int				env_builtin(t_command_exec *node, t_utils *utils, size_t i);

//exit_utils.c
int				is_arg_digit_and_overflow(char *arg, t_utils *utils);

//exit.c
int				print_exit(long long code, char *arg, bool too_many_arguments,
					t_utils *utils);
unsigned int	exit_builtin(t_command_exec *node, t_utils *utils);

//export.c
int				export_builtin(t_command_exec *node, t_utils *utils, size_t i,
					int return_value);

//export_utils.c
int				is_variable_already_in_env(t_utils *utils, char *variable_name,
					size_t i, bool is_equal);
char			*assign_variable_name(char *cmd, char *variable_name, size_t i,
					size_t j);

//pwd.c
int				pwd_builtin(t_command_exec *node);

//unset.c
int				unset_builtin(t_command_exec *node, t_utils *utils, size_t i,
					size_t j);

#endif