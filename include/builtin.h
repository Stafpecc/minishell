/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 14:55:15 by ldevoude          #+#    #+#             */
/*   Updated: 2025/05/10 14:55:15 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"
#include "minishell.h"
#include "lexer.h"
#include "parsing.h"
#include "signal_handler.h"

//echo.c
int	is_newline(t_command *node, int *i, bool *newline);
int	echo_builtin(t_command *node, bool newline, int i);