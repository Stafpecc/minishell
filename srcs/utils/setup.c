/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:26:16 by stafpec           #+#    #+#             */
/*   Updated: 2025/06/25 18:28:00 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <readline/readline.h>

static int gotnotnull(void)
{
	return (1);
}

void setup(void)
{
    rl_event_hook = gotnotnull;
	set_signals();
}