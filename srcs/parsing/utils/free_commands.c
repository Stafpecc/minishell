/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 16:04:41 by tarini            #+#    #+#             */
/*   Updated: 2025/05/08 15:21:06 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void free_commands(t_command *cmd)
{
    t_command *tmp;
    int i;

    while (cmd)
    {
        tmp = cmd;
        cmd = cmd->next;
        if (tmp->cmd_parts)
        {
            i = 0;
            while (tmp->cmd_parts[i])
            {
                free(tmp->cmd_parts[i]->content);
                free(tmp->cmd_parts[i]);
                i++;
            }
            free(tmp->cmd_parts);
        }
        free(tmp->redirect_in);
        free(tmp->redirect_out);
        free(tmp->append_redirections);
        if (tmp->heredoc)
        {
            free(tmp->heredoc->arg);
            free(tmp->heredoc);
        }
        free(tmp);
    }
}
