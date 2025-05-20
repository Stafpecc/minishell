/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_to_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:09:50 by tarini            #+#    #+#             */
/*   Updated: 2025/05/19 11:31:04 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../../../libft/includes/libft.h"

#include <stdlib.h>
#include <stdbool.h>

t_command_exec *struct_to_char(t_command *cmd)
{
    t_command_exec *tmp_cmd;
    int i;
    int count;

    if (cmd == NULL)
        return NULL;
    tmp_cmd = malloc(sizeof(t_command_exec));
    if (tmp_cmd == NULL)
        return NULL;
    count = 0;
    while (cmd->cmd_parts && cmd->cmd_parts[count])
        count++;
    tmp_cmd->cmd_parts = malloc(sizeof(char *) * (count + 1));
    if (tmp_cmd->cmd_parts == NULL)
        return (NULL);
    i = 0;
    while (i < count)
    {
        if (cmd->cmd_parts[i] && cmd->cmd_parts[i]->arg)
            tmp_cmd->cmd_parts[i] = ft_strdup(cmd->cmd_parts[i]->arg);
        else
            tmp_cmd->cmd_parts[i] = NULL;
        i++;
    }
    tmp_cmd->cmd_parts[i] = NULL;
    if (cmd->redirect_in && cmd->redirect_in->arg)
        tmp_cmd->redirect_in = ft_strdup(cmd->redirect_in->arg);
    else
        tmp_cmd->redirect_in = NULL;
    if (cmd->redirect_out && cmd->redirect_out->arg)
        tmp_cmd->redirect_out = ft_strdup(cmd->redirect_out->arg);
    else
        tmp_cmd->redirect_out = NULL;
    if (cmd->append_redirections && cmd->append_redirections->arg)
        tmp_cmd->append_redirections = ft_strdup(cmd->append_redirections->arg);
    else
        tmp_cmd->append_redirections = NULL;
    if (cmd->heredoc && cmd->heredoc->arg)
        tmp_cmd->heredoc = ft_strdup(cmd->heredoc->arg);
    else
        tmp_cmd->heredoc = NULL;
    tmp_cmd->next = NULL;
    return tmp_cmd;
}
