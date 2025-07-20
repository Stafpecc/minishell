/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:23:38 by stafpec           #+#    #+#             */
/*   Updated: 2025/07/20 18:13:31 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	check_error(int ac)
{
	if (ac != 1)
	{
		write(STDERR_FILENO, RED, strlen(RED));
		write(STDERR_FILENO, "Error: minishell does not take any arguments\n", 45);
		write(STDERR_FILENO, RESET, strlen(RESET));
		return (RETURN_FAILURE);
	}
	if (!isatty(STDIN_FILENO))
	{
		write(STDERR_FILENO, RED, strlen(RED));
		write(STDERR_FILENO, "Error: minishell must be run in an interactive terminal\n", 56);
		write(STDERR_FILENO, RESET, strlen(RESET));
		return (RETURN_FAILURE);
	}
	if (!isatty(STDOUT_FILENO))
	{
		write(STDERR_FILENO, RED, strlen(RED));
		write(STDERR_FILENO, "Error: stdout is not a terminal\n", 33);
		write(STDERR_FILENO, RESET, strlen(RESET));
		return (RETURN_FAILURE);
	}
	return (RETURN_SUCCESS);
}
