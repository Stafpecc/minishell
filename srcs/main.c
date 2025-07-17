/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 15:36:10 by stafpec           #+#    #+#             */
/*   Updated: 2025/07/17 14:32:14 by stafpec          ###   ########.fr       */
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
	int		last_return;

	(void)av;
	if (check_error(ac) == RETURN_FAILURE)
		return (RETURN_FAILURE);
	rl_event_hook = gotnotnull;
	set_signals();
	utils = init_utils_struct(env);
	if (!utils)
		return (RETURN_FAILURE);
	minishell_loop(utils);
	last_return = utils->last_return;
	free_utils(utils);
	return (last_return);
}
