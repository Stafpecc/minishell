/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_gestionary.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 16:08:37 by tarini            #+#    #+#             */
/*   Updated: 2025/05/08 14:14:49 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../../libft/includes/libft.h"

char **add_argument(char **args, const char *value)
{
	size_t i;
	size_t j;
	char **new_args;

	i = 0;
	if (args)
	{
		while (args[i])
		   i++;
	}
	new_args = malloc(sizeof(char *) * (i + 2));
	if (!new_args)
		return (NULL);
	j = 0;
	while (j < i)
	{
		new_args[j] = args[j];
		j++;
	}
	new_args[i] = ft_strdup(value);
	new_args[i + 1] = NULL;
	free(args);
	return (new_args);
}

t_command *create_command()
{
	t_command *cmd;
	
	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return NULL;
	cmd->cmd = NULL;
	cmd->redirect_in = NULL;
	cmd->redirect_out = NULL;
	cmd->append_redirections = NULL;
	cmd->heredoc = NULL;
	cmd->next = NULL;
	cmd->in_double_quote = false;
	cmd->in_simple_quote = false;
	return (cmd);
}
