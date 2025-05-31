/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:58:07 by tarini            #+#    #+#             */
/*   Updated: 2025/05/31 16:53:12 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "parsing.h"
#include "../../../libft/includes/libft.h"

int process_free_exit(t_command *head)
{
	free_commands(head);
	return (RETURN_FAILURE);
}

bool is_word_like(t_token *token)
{
	return (token->type == TOK_WORD ||
			token->type == TOK_STRING ||
			token->type == TOK_SINGLE_QUOTES ||
			token->type == TOK_DOUBLE_QUOTES);
}

int is_redirect_or_pipe(t_token *token)
{
	if (!token)
		return (RETURN_FAILURE);
	if (ft_strcmp(token->value, "<<") == 0)
		return (RETURN_SUCCESS);
	if (ft_strcmp(token->value, ">>") == 0)
		return (RETURN_SUCCESS);
	if (ft_strcmp(token->value, "<") == 0)
		return (RETURN_SUCCESS);
	if (ft_strcmp(token->value, ">") == 0)
		return (RETURN_SUCCESS);
	if (ft_strcmp(token->value, "|") == 0)
		return (RETURN_SUCCESS);
	return (RETURN_FAILURE);
}