/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 15:36:10 by stafpec           #+#    #+#             */
/*   Updated: 2025/07/20 18:03:58 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ascii_art(void)
{
	char	*line;

	line = NULL;
	ascii_minishell(line);
	ascii_tarini(line);
	ascii_ldevoude(line);
}

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
	ascii_art();
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
