/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:14:45 by tarini            #+#    #+#             */
/*   Updated: 2025/05/23 14:09:06 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "lexer.h"
#include "return_error.h"

#include "../../libft/includes/libft.h"

t_command_exec *parse_tokens(t_token *tokens)
{
	t_command *head;
	t_command *curr;
	t_command_exec *final;

	head = create_command();
	curr = head;
	if (!head)
		return (NULL);
	while (tokens && tokens->type != TOK_END)
	{
		if (launch_commands(&tokens, &curr, head) == RETURN_FAILURE)
			return (NULL);
	}
	if (parse_cmd(head) == RETURN_FAILURE)
		return (NULL);
	final = struct_to_char(head);
	free_commands(head);
	return (final);
}
