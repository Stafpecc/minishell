/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:35:37 by tarini            #+#    #+#             */
/*   Updated: 2025/05/08 17:32:11 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int process_pipe(t_command **curr, t_command *head)
{
    (*curr)->next = create_command();
    if (!(*curr)->next)
    {
        free_commands(head);
        return (RETURN_FAILURE);
    }
    (*curr) = (*curr)->next;
    return (RETURN_SUCCESS);
}