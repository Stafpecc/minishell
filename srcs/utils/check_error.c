/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:23:38 by stafpec           #+#    #+#             */
/*   Updated: 2025/07/17 13:39:06 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	check_error(int ac)
{
	if (ac != 1)
	{
		ft_printfd(RED "Error: minishell does not take any arguments\n" RESET);
		return (RETURN_FAILURE);
	}
	if (!isatty(STDIN_FILENO))
	{
		ft_printfd(RED "Error: minishell must be run in an interactive\
terminal\n" RESET);
		return (RETURN_FAILURE);
	}
	if (!isatty(STDOUT_FILENO))
	{
		ft_printfd(RED "Error: stdout is not a terminal\n" RESET);
		return (RETURN_FAILURE);
	}
	return (RETURN_SUCCESS);
}
