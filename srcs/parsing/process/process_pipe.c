/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:35:37 by tarini            #+#    #+#             */
/*   Updated: 2025/05/23 14:56:00 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int process_pipe(t_command **curr, t_command *head)
{
	(*curr)->next = create_command();
	if (!(*curr)->next)
		return (process_free_exit(head));
	(*curr) = (*curr)->next;
	return (RETURN_SUCCESS);
}