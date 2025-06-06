/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_to_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:09:50 by tarini            #+#    #+#             */
/*   Updated: 2025/06/04 17:00:46 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../../../libft/includes/libft.h"

#include <stdlib.h>
#include <stdbool.h>

static char **dup_targ_array(t_arg **arr)
{
	int count = 0;
	char **new_arr;
	int i;

	if (!arr)
		return NULL;
	while (arr[count])
		count++;
	new_arr = malloc(sizeof(char *) * (count + 1));
	if (!new_arr)
		return NULL;
	i = 0;
	while (i < count)
	{
		new_arr[i] = ft_strdup(arr[i]->arg);
		if (!new_arr[i])
		{
			int j = 0;
			while (j < i)
			{
				free(new_arr[j]);
				j++;
			}
			free(new_arr);
			return NULL;
		}
		i++;
	}
	new_arr[count] = NULL;
	return new_arr;
}

/*
fonction qui :
- transforme une liste chaînée de t_command en une liste chaînée de t_command_exec ;
- duplique les chaînes présentes dans les champs cmd_parts, redirect_in, redirect_out, heredoc et append_redirections ;
- ne filtre plus les cmd_parts selon le champ final (supprimé) ;
- retourne un pointeur vers la tête de la nouvelle structure allouée dynamiquement, ou NULL en cas d’échec.
*/

t_command_exec *struct_to_char(t_command *cmd)
{
	t_command_exec *head = NULL;
	t_command_exec *current = NULL;
	t_command_exec *new_node;
	int i, count;

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

		if (cmd->heredoc && cmd->heredoc->arg)
			new_node->heredoc = ft_strdup(cmd->heredoc->arg);
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
