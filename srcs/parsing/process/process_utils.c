/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:58:07 by tarini            #+#    #+#             */
/*   Updated: 2025/05/20 10:27:32 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int process_free_exit(t_command *head)
{
    free_commands(head);
    return (RETURN_FAILURE);
}

int is_word_like(t_token *token)
{
	return (token->type == TOK_WORD ||
			token->type == TOK_STRING ||
			token->type == TOK_SINGLE_QUOTES ||
			token->type == TOK_DOUBLE_QUOTES);
}
