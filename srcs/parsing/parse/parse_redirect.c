/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:32:47 by tarini            #+#    #+#             */
/*   Updated: 2025/05/31 17:34:38 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool has_conflicting_redirections(t_command *cmd)
{
	return ((cmd->redirect_in && cmd->heredoc) ||
			(cmd->redirect_out && cmd->append_redirections));
}

int redirect_parsing(t_command *curr, t_utils *utils)
{
	if (curr->redirect_out != NULL &&
		curr->next && curr->next->redirect_out != NULL)
		return (return_failure(">", utils));
	if (curr->redirect_in != NULL &&
		curr->next && curr->next->redirect_in != NULL)
		return (return_failure("<", utils));
	if (curr->append_redirections != NULL &&
		curr->next && curr->next->append_redirections != NULL)
		return (return_failure(">>", utils));
	if (curr->heredoc != NULL &&
		curr->next && curr->next->heredoc != NULL)
		return (return_failure("<<", utils));
	return (RETURN_SUCCESS);
}