/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 14:55:15 by ldevoude          #+#    #+#             */
/*   Updated: 2025/06/25 17:15:51 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
#include "../libft/includes/libft.h"
#include "minishell.h"
#include "lexer.h"
#include "parsing.h"
#include "signal_handler.h"
#include "exec.h"

#define NOT_NUM_ARG 2

typedef enum e_error_msg {
	ERR_CD_CHDIR,
    ERR_CD_GETCWD,
    ERR_CD_MALLOC,
    ERR_CD_NOMSG,
} t_error_msg;



//cd_utils.c
int return_errors(int return_value, int message, t_command_exec *node);

//cd.c
int cd_builtin(t_command_exec *node, t_utils *utils, int pwd_emplacement, int pwd_old_emplacement);

//pwd.c
int pwd_builtin(t_command_exec *node, t_utils *utils, int i, int j);

//echo.c
int	is_newline(t_command_exec *node, int *i, bool *newline);
int	echo_builtin(t_command_exec *node, bool newline, int i);

//env.c
int env_builtin(t_command_exec *node, t_utils *utils, size_t i);

//exit.c
unsigned int exit_builtin(t_command_exec *node, t_utils *utils);

//export.c
int export_builtin(t_command_exec *node, t_utils *utils, size_t i);

//pwd.c
int pwd_builtin(t_command_exec *node, t_utils *utils, int i, int j);

//unset.c
//static int env_len(char **env);
int var_name_cmp(const char *env_var, const char *name);
int unset_builtin(t_command_exec *node, t_utils *utils);


#endif