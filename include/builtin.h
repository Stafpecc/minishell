/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 14:55:15 by ldevoude          #+#    #+#             */
/*   Updated: 2025/05/29 16:23:56 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"
#include "minishell.h"
#include "lexer.h"
#include "parsing.h"
#include "signal_handler.h"
#include "exec.h"

//cd.c
int cd_builtin(t_command_exec *node, t_utils *utils, int pwd_emplacement, int pwd_old_emplacement);

//pwd.c
int pwd_builtin(t_command_exec *node, t_utils *utils, int i, int j);

//echo.c
int	is_newline(t_command_exec *node, int *i, bool *newline);
int	echo_builtin(t_command_exec *node, bool newline, int i);

//env.c
int env_builtin(t_command_exec *node, t_utils *utils, int i);

//exit.c
unsigned int exit_builtin(t_command_exec *node, t_utils *utils);

//export.c
//int export_builtin(t_command *node, char **env, int i, int j);

//pwd.c
int pwd_builtin(t_command_exec *node, t_utils *utils, int i, int j);

//unset.c
//static int env_len(char **env);
int var_name_cmp(const char *env_var, const char *name);
char **unset_builtin(char **envp, const char *name);


