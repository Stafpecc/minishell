/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_to_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:09:50 by tarini            #+#    #+#             */
/*   Updated: 2025/07/17 13:47:45 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static void	*ret_free_command_exec(t_command_exec *node)
{
	if (!node)
		return (NULL);
	free_tab(node->cmd_parts);
	free_redirect_array(node->redirect_in);
	free_redirect_array(node->redirect_out);
	free(node);
	return (NULL);
}

t_command_exec	*struct_to_char_node(t_command *cmd)
{
	t_command_exec	*new_node;

	new_node = malloc(sizeof(t_command_exec)); // <-- lui il casse
	if (!new_node)
		return (NULL);
	new_node->cmd_parts = NULL;
	new_node->redirect_in = NULL;
	new_node->redirect_out = NULL;
	new_node->next = NULL;
	if (cmd_part_to_char(cmd, new_node) == RETURN_FAILURE)
		return (ret_free_command_exec(new_node));
	new_node->redirect_in = dup_targ_to_tredirect_array(cmd->redirect_in);
	if (cmd->redirect_in && !new_node->redirect_in)
		return (ret_free_command_exec(new_node));
	new_node->redirect_out = dup_targ_to_tredirect_array(cmd->redirect_out);
	if (cmd->redirect_out && !new_node->redirect_out)
		return (ret_free_command_exec(new_node));
	return (new_node);
}

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
t_command_exec	*struct_to_char(t_command *cmd)
{
	t_command_exec	*head;
	t_command_exec	*current;
	t_command_exec	*new_node;

	head = NULL;
	current = NULL;
	while (cmd)
	{
		new_node = struct_to_char_node(cmd);
		if (!new_node)
		{
			free_commands_exec(head);
			return (NULL);
		}
		if (!head)
			head = new_node;
		else
			current->next = new_node;
		current = new_node;
		cmd = cmd->next;
	}
	return (head);
}
