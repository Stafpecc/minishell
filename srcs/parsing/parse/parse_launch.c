/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_launch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:33:08 by tarini            #+#    #+#             */
/*   Updated: 2025/07/12 16:17:24 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../../../libft/includes/libft.h"

static int	parse_directory(t_command *curr, t_utils *utils)
{
	const char	*arg;

	if (!curr || !curr->cmd_parts || !curr->cmd_parts[0])
		return (RETURN_SUCCESS);

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

static int check_redirect_in(char *filename, bool is_heredoc)
{
	if (is_heredoc)
        return (RETURN_SUCCESS);
	if (access(filename, F_OK) == -1)
	{
		ft_printfd("minisell: %s: No such file or directory\n", filename);
		return (RETURN_FAILURE);
	}
	if (access(filename, R_OK) == -1)
	{
		ft_printfd("minishell: %s: Permission denied\n", filename);
		return (RETURN_FAILURE);
	}
	return (RETURN_SUCCESS);
}

static int	parse_cmd_helper(t_command *prev, t_command *curr, t_utils *utils)
{
	int	i;

	if (curr->redirect_in)
	{
		i = 0;
		while (curr->redirect_in[i])
		{
			if (check_redirect_in(curr->redirect_in[i]->arg,
				curr->redirect_in[i]->heredoc) == RETURN_FAILURE)
			{
				utils->last_return = 1;
				return (RETURN_FAILURE);
			}
			i++;
		}
	}
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
