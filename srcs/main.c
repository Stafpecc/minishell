/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:41:58 by stafpec           #+#    #+#             */
/*   Updated: 2025/07/02 13:28:27 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
#include "parsing.h"
#include "../libft/includes/libft.h"

static int	gotnotnull(void)
{
	return (1);
}

int	main(int ac, char **av, char **env)
{
	t_utils	*utils;

	(void)av;
	if (check_error(ac) == RETURN_FAILURE)
		return (RETURN_FAILURE);
	rl_event_hook = gotnotnull;
	set_signals();
	utils = init_utils_struct(env);
	minishell_loop(utils);
	return (utils->last_return);
}
