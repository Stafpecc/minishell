/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_launch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:33:08 by tarini            #+#    #+#             */
/*   Updated: 2025/06/04 12:36:27 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../../../libft/includes/libft.h"

/*
Fonction qui :
- parcourt une liste chaînée de commandes (t_command) pour valider leur syntaxe 
	et leurs redirections ;
- effectue plusieurs vérifications : commande vide, redirections conflictuelles, 
	redondantes, ou vers des fichiers/dossiers invalides ;
- retourne RETURN_FAILURE dès qu’un problème est détecté, sinon RETURN_SUCCESS 
	si tout est correct.
*/
int parse_cmd(t_command *cmd, t_utils *utils)
{
	t_command *prev = NULL;
	t_command *curr = cmd;
	int last_redirect_in;
	const char *arg;

	if (!curr)
		return (RETURN_FAILURE);
	while (curr)
	{
		if (is_empty_command(curr))
			return (return_failure("|", utils));
		if (has_conflicting_redirections(curr))
			return (return_failure(">", utils));		
		if ((curr->redirect_in || curr->redirect_out 
			|| curr->append_redirections || curr->heredoc) 
			&& is_empty_command(curr))
			return (return_failure(">", utils));
		if (redirect_parsing(curr, utils) == RETURN_FAILURE)
			return (RETURN_FAILURE);
		if (prev && is_empty_command(prev) && is_empty_command(curr))
			return (return_failure("|", utils));
		if (curr->cmd_parts && curr->cmd_parts[0] && curr->cmd_parts[0]->arg)
		{
			if (curr->cmd_parts && curr->cmd_parts[0] && curr->cmd_parts[0]->arg)
			{
				arg = curr->cmd_parts[0]->arg;
				if (is_directory(arg))
				{
					ft_printfd("minishell: %s: Is a directory\n", arg);
					utils->last_return = CMD_INVALID_ARGUMENT;
					return (RETURN_FAILURE);
				}
				if (ft_strchr(arg, '/'))
				{
					if (check_file(arg, utils) == RETURN_FAILURE)
						return (RETURN_FAILURE);
				}
			}
		}
		last_redirect_in = get_size_of_redirect(cmd->redirect_in);
		if (curr->redirect_in && curr->redirect_in[last_redirect_in]->arg)
        {
            if (check_file(curr->redirect_in[last_redirect_in]->arg, utils) == RETURN_FAILURE)
                return RETURN_FAILURE;
        }
		prev = curr;
		curr = curr->next;
	}
	return (RETURN_SUCCESS);
}
