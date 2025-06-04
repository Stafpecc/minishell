/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_to_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:09:50 by tarini            #+#    #+#             */
/*   Updated: 2025/06/01 17:04:13 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../../../libft/includes/libft.h"

#include <stdlib.h>
#include <stdbool.h>

t_command_exec *struct_to_char(t_command *cmd)
{
    t_command_exec *head = NULL;
    t_command_exec *current = NULL;
    t_command_exec *new_node;
    int i, j;
    int count, total;

    while (cmd)
    {
        new_node = malloc(sizeof(t_command_exec));
        if (new_node == NULL)
            return (NULL);

        count = 0;
        total = 0;
        while (cmd->cmd_parts && cmd->cmd_parts[total])
        {
            if (!cmd->cmd_parts[total]->final)
                count++;
            total++;
        }

        new_node->cmd_parts = malloc(sizeof(char *) * (count + 1));
        if (new_node->cmd_parts == NULL)
            return (NULL);

        i = 0;
        j = 0;
        while (cmd->cmd_parts && cmd->cmd_parts[i])
        {
            if (cmd->cmd_parts[i]->arg && !cmd->cmd_parts[i]->final)
            {
                new_node->cmd_parts[j] = ft_strdup(cmd->cmd_parts[i]->arg);
                j++;
            }
            i++;
        }
        new_node->cmd_parts[j] = NULL;

        if (cmd->redirect_in && cmd->redirect_in->arg)
            new_node->redirect_in = ft_strdup(cmd->redirect_in->arg);
        else
            new_node->redirect_in = NULL;

        if (cmd->redirect_out && cmd->redirect_out->arg)
            new_node->redirect_out = ft_strdup(cmd->redirect_out->arg);
        else
            new_node->redirect_out = NULL;

        if (cmd->append_redirections && cmd->append_redirections->arg)
            new_node->append_redirections = ft_strdup(cmd->append_redirections->arg);
        else
            new_node->append_redirections = NULL;

        if (cmd->heredoc && cmd->heredoc->arg)
            new_node->heredoc = ft_strdup(cmd->heredoc->arg);
        else
            new_node->heredoc = NULL;

        new_node->next = NULL;
        if (head == NULL)
            head = new_node;
        else
            current->next = new_node;
        current = new_node;
        cmd = cmd->next;
    }
    return (head);
}
