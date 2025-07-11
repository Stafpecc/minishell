/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:23:38 by stafpec           #+#    #+#             */
/*   Updated: 2025/07/01 16:41:10 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
//check if there is any arguments when the user launched the program
//also check if the program was launched on a terminal
//if all the checks are good return 0 else return 1

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
