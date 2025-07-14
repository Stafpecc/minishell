/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:35:37 by tarini            #+#    #+#             */
/*   Updated: 2025/07/14 15:55:55 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*
Function that:
- creates a new command and links it to the current command via the 'next' field;
- updates the current pointer to point to this new command;
- returns RETURN_SUCCESS if the creation succeeds, otherwise frees the memory
  and returns an error.
*/
int	process_pipe(t_command **curr, t_command *head)
{
	(*curr)->next = create_command();
	if (!(*curr)->next)
		return (process_free_exit(head));
	(*curr) = (*curr)->next;
	return (RETURN_SUCCESS);
}
