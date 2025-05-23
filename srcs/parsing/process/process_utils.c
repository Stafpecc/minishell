/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:58:07 by tarini            #+#    #+#             */
/*   Updated: 2025/05/23 14:28:40 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdbool.h>

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
