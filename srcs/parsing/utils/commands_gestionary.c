/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_gestionary.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 16:08:37 by tarini            #+#    #+#             */
/*   Updated: 2025/05/23 14:09:32 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../../../libft/includes/libft.h"

t_arg **add_argument(t_arg **args, const char *value)
{
    size_t i;
    size_t j;
    t_arg **new_args;

    i = 0;
    j = 0;
    if (args)
    {
        while (args[i])
            i++;
    }
    new_args = malloc(sizeof(t_arg *) * (i + 2));
    if (!new_args)
        return NULL;
    while (j < i)
    {
        new_args[j] = args[j];
        j++;
    }
    new_args[i] = malloc(sizeof(t_arg));
    if (!new_args[i])
    {
        free(new_args);
        return NULL;
    }
    new_args[i]->arg = ft_strdup(value);
    new_args[i]->in_simple_quote = false;
    new_args[i]->in_double_quote = false;
    new_args[i + 1] = NULL;
    free(args);
    return new_args;
}

t_command *create_command(void)
{
	t_command *cmd = malloc(sizeof(t_command));
	if (!cmd)
		return NULL;
	cmd->cmd_parts = NULL;
	cmd->redirect_in = NULL;
	cmd->redirect_out = NULL;
	cmd->append_redirections = NULL;
	cmd->heredoc = NULL;
	cmd->next = NULL;
	return cmd;
}
