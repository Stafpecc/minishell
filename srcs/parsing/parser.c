/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:14:45 by tarini            #+#    #+#             */
/*   Updated: 2025/06/14 15:18:12 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "lexer.h"
#include "return_error.h"
#include "minishell.h"

#include "../../libft/includes/libft.h"

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
			return (NULL);
	}
	if (parse_cmd(head, utils) == RETURN_FAILURE)
	{
		ft_printfd("TESTICI\n");
		return (NULL);
	}
	final = struct_to_char(head);
	free_commands(head);
	return (final);
}
