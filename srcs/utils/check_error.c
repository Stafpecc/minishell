/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:23:38 by stafpec           #+#    #+#             */
/*   Updated: 2025/06/26 12:54:51 by stafpec          ###   ########.fr       */
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
		ft_printfd(RED "Error: minishell must be run in an interactive \
terminal\n" RESET);
		return (RETURN_FAILURE);
	}
	if (getenv("MINISHELL_RUNNING") != NULL)
	{
		ft_printfd(RED "Error: minishell cannot be run recursively\n" RESET);
		return (RETURN_FAILURE);
	}
	return (RETURN_SUCCESS);
}
