/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_launch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:33:08 by tarini            #+#    #+#             */
/*   Updated: 2025/07/03 13:23:52 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../../../libft/includes/libft.h"

static int	parse_directory(t_command *curr, t_utils *utils)
{
	const char	*arg;

	arg = curr->cmd_parts[0]->arg;
	if (is_directory(arg))
	{
		ft_printfd("minishell: %s: Is a directory\n", arg);
		utils->last_return = CMD_PERMISSION_DENIED;
		return (RETURN_FAILURE);
	}
	if (ft_strchr(arg, '/'))
	{
		if (check_file(arg, utils, FILE_EXEC) == RETURN_FAILURE)
			return (RETURN_FAILURE);
	}
	return (RETURN_SUCCESS);
}

static int	parse_cmd_helper(t_command *prev, t_command *curr, t_utils *utils)
{
	if (is_empty_command(curr))
		return (return_failure("|", utils));
	if ((curr->redirect_in || curr->redirect_out)
		&& is_empty_command(curr))
		return (return_failure(">", utils));
	if (prev && is_empty_command(prev) && is_empty_command(curr))
		return (return_failure("|", utils));
	if (curr->cmd_parts && curr->cmd_parts[0] && curr->cmd_parts[0]->arg)
	{
		if (parse_directory(curr, utils) == RETURN_FAILURE)
			return (RETURN_FAILURE);
	}
	return (RETURN_SUCCESS);
}

/*
Fonction qui :
- parcourt une liste chaînée de commandes (t_command) pour valider leur syntaxe 
	et leurs redirections ;
- effectue plusieurs vérifications : commande vide, redirections conflictuelles, 
	redondantes, ou vers des fichiers/dossiers invalides ;
- retourne RETURN_FAILURE dès qu’un problème est détecté, sinon RETURN_SUCCESS 
	si tout est correct.
*/
int	parse_cmd(t_command *cmd, t_utils *utils)
{
	t_command	*prev;
	t_command	*curr;

	prev = NULL;
	curr = cmd;
	if (!curr)
		return (RETURN_FAILURE);
	while (curr)
	{
		if (parse_cmd_helper(prev, curr, utils) == RETURN_FAILURE)
			return (RETURN_FAILURE);
		prev = curr;
		curr = curr->next;
	}
	return (RETURN_SUCCESS);
}
