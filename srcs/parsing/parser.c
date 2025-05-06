/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:14:45 by tarini            #+#    #+#             */
/*   Updated: 2025/05/06 14:20:53 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "lexer.h"
#include "return_error.h"

#include "../../libft/includes/libft.h"

t_command *parse_tokens(t_token *tokens)
{
	t_command *head;
	t_command *curr;

	head = create_command();
	curr = head;
	if (!head)
		return (NULL);
	while (tokens && tokens->type != TOK_END)
	{
		if (process_parsing(tokens, curr, head) == RETURN_FAILURE)
			return (NULL);
	}
	return (head);
}
