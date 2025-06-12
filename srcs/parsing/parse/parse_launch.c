/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_launch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:33:08 by tarini            #+#    #+#             */
/*   Updated: 2025/06/12 13:56:34 by stafpec          ###   ########.fr       */
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
		utils->last_return = CMD_INVALID_ARGUMENT;
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
	if (has_conflicting_redirections(curr))
		return (return_failure(">", utils));
	if ((curr->redirect_in || curr->redirect_out)
		&& is_empty_command(curr))
		return (return_failure(">", utils));
	if (redirect_parsing(curr, utils) == RETURN_FAILURE)
		return (RETURN_FAILURE);
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
			return (RETURN_FAILURE);;
		prev = curr;
		curr = curr->next;
	}
	return (RETURN_SUCCESS);
}

// WITH CHECK FILE

// int parse_cmd(t_command *cmd, t_utils *utils)
// {
// 	t_command *prev = NULL;
// 	t_command *curr = cmd;
// 	//int last_redirect_in;
// 	//int last_redirect_out;
// 	const char *arg;

// 	if (!curr)
// 		return (RETURN_FAILURE);
// 	while (curr)
// 	{
// 		if (is_empty_command(curr))
// 			return (return_failure("|", utils));
// 		if (has_conflicting_redirections(curr))
// 			return (return_failure(">", utils));
// 		if ((curr->redirect_in || curr->redirect_out 
// 			|| curr->append_redirections || curr->heredoc) 
// 			&& is_empty_command(curr))
// 			return (return_failure(">", utils));
// 		if (redirect_parsing(curr, utils) == RETURN_FAILURE)
// 			return (RETURN_FAILURE);
// 		if (prev && is_empty_command(prev) && is_empty_command(curr))
// 			return (return_failure("|", utils));
// 		if (curr->cmd_parts && curr->cmd_parts[0] && curr->cmd_parts[0]->arg)
// 		{
// 			arg = curr->cmd_parts[0]->arg;
// 			if (is_directory(arg))
// 			{
// 				ft_printfd("minishell: %s: Is a directory\n", arg);
// 				utils->last_return = CMD_INVALID_ARGUMENT;
// 				return (RETURN_FAILURE);
// 			}
// 			if (ft_strchr(arg, '/'))
// 			{
// 				if (check_file(arg, utils, FILE_EXEC) == RETURN_FAILURE)
// 					return (RETURN_FAILURE);
// 			}
// 		}
// 		// last_redirect_in = get_size_of_redirect(curr->redirect_in);
// 		// // if (curr->redirect_in && last_redirect_in > 0
// 		// // 	&& curr->redirect_in[last_redirect_in - 1]
// 		// // 	&& curr->redirect_in[last_redirect_in - 1]->arg)
// 		// // {
// 		// // 	if (check_file(curr->redirect_in[last_redirect_in - 1]->arg,
	// 				utils, FILE_READ) == RETURN_FAILURE)
// 		// // 		return (RETURN_FAILURE);
// 		// // }
// 		// last_redirect_out = get_size_of_redirect(curr->redirect_out);
// 		// if (curr->redirect_out && last_redirect_out > 0
// 		// 	&& curr->redirect_out[last_redirect_out - 1]
// 		// 	&& curr->redirect_out[last_redirect_out - 1]->arg)
// 		// {
// 		// 	if (check_file(curr->redirect_out[last_redirect_out - 1]->arg,
//				utils, FILE_WRITE) == RETURN_FAILURE)
// 		// 		return (RETURN_FAILURE);
// 		// }
// 		// if (curr->append_redirections && curr->append_redirections->arg)
// 		// {
// 		// 	if (check_file(curr->append_redirections->arg, utils, FILE_WRITE)
//				== RETURN_FAILURE)
// 		// 		return (RETURN_FAILURE);
// 		// }
// 		prev = curr;
// 		curr = curr->next;
// 	}
// 	return (RETURN_SUCCESS);
// }
