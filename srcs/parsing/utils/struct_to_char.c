/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_to_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:09:50 by tarini            #+#    #+#             */
/*   Updated: 2025/06/08 05:54:06 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../../../libft/includes/libft.h"

#include <stdlib.h>
#include <stdbool.h>

/*
fonction qui :
- transforme une liste chaînée de t_command en une liste chaînée de
	t_command_exec ;
- duplique les chaînes présentes dans les champs cmd_parts, redirect_in,
	redirect_out, heredoc et append_redirections ;
- ne filtre plus les cmd_parts selon le champ final (supprimé) ;
- retourne un pointeur vers la tête de la nouvelle structure allouée
	dynamiquement, ou NULL en cas d’échec.
*/
t_command_exec *struct_to_char(t_command *cmd)
{
	t_command_exec *head;
	t_command_exec *current;
	t_command_exec *new_node;
	int i;
	int count;

	current = NULL;
	head = NULL;
	while (cmd)
	{
		new_node = malloc(sizeof(t_command_exec));
		if (!new_node)
			return (NULL);
		count = 0;
		while (cmd->cmd_parts && cmd->cmd_parts[count])
			count++;
		new_node->cmd_parts = malloc(sizeof(char *) * (count + 1));
		if (!new_node->cmd_parts)
		{
			free(new_node);
			return (NULL);
		}
		i = 0;
		while (i < count)
		{
			new_node->cmd_parts[i] = ft_strdup(cmd->cmd_parts[i]->arg);
			if (!new_node->cmd_parts[i])
			{
				while (--i >= 0)
					free(new_node->cmd_parts[i]);
				free(new_node->cmd_parts);
				free(new_node);
				return (NULL);
			}
			i++;
		}
		new_node->cmd_parts[i] = NULL;
		new_node->redirect_in = dup_targ_array(cmd->redirect_in);
		new_node->redirect_out = dup_targ_array(cmd->redirect_out);
		if (cmd->append_redirections && cmd->append_redirections->arg)
			new_node->append_redirections = ft_strdup(cmd->append_redirections->arg);
		else
			new_node->append_redirections = NULL;
		if (cmd->heredoc)
		{
			new_node->heredoc = dup_heredoc_from_arg(cmd->heredoc);
			if (!new_node->heredoc)
				return (NULL);
		}
		else
			new_node->heredoc = NULL;

		new_node->next = NULL;
		if (!head)
			head = new_node;
		else
			current->next = new_node;
		current = new_node;
		cmd = cmd->next;
	}
	return (head);
}
