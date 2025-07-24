/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:14:45 by tarini            #+#    #+#             */
/*   Updated: 2025/07/17 16:19:20 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command_exec	*parse_tokens(t_token *tokens, t_utils *utils)
{
	t_command		*head;
	t_command		*curr;
	t_command_exec	*final;

	head = create_command();
	curr = head;
	if (!head)
		return (NULL);
	while (tokens && tokens->type != TOK_END)
	{
		if (launch_commands(&tokens, &curr, head, utils) == RETURN_FAILURE)
		{
			free_commands(head);
			return (NULL);
		}
	}
	if (parse_cmd(head, utils) == RETURN_FAILURE)
	{
		free_commands(head);
		return (NULL);
	}
	final = struct_to_char(head);
	if (head)
		free_commands(head);
	return (final);
}
