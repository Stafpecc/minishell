/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 16:10:48 by tarini            #+#    #+#             */
/*   Updated: 2025/05/06 14:21:19 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "return_error.h"
#include "../../libft/includes/libft.h"

static int process_word_string(t_token **tokens, t_command *curr)
{
	if ((*tokens)->type == TOK_WORD || (*tokens)->type == TOK_STRING)
		curr->cmd = add_argument(curr->cmd, (*tokens)->value);
	(*tokens) = (*tokens)->next;
	return (RETURN_SUCCESS);
}

static int process_redirect_in(t_token **tokens, t_command *curr, t_command *head)
{
	(*tokens) = (*tokens)->next;
	if (!(*tokens) || ((*tokens)->type != TOK_WORD && (*tokens)->type != TOK_STRING))
	{
		free_commands(head);
		return (RETURN_FAILURE);
	}
	curr->redirect_in = ft_strdup((*tokens)->value);
	(*tokens) = (*tokens)->next;
	return (RETURN_SUCCESS);
}

static int process_redirect_out(t_token **tokens, t_command *curr, t_command *head)
{
	(*tokens) = (*tokens)->next;
	if (!(*tokens) || ((*tokens)->type != TOK_WORD && (*tokens)->type != TOK_STRING))
	{
		free_commands(head);
		return (RETURN_FAILURE);
	}
	curr->redirect_out = ft_strdup((*tokens)->value);
	(*tokens) = (*tokens)->next;
	return (RETURN_SUCCESS);
}

static int process_pipe(t_command **curr, t_command *head)
{
	(*curr)->next = create_command();
	if (!(*curr)->next)
	{
		free_commands(head);
		return (RETURN_FAILURE);
	}
	(*curr) = (*curr)->next;
	return (RETURN_SUCCESS);
}

int process_parsing(t_token *tokens, t_command *curr, t_command *head)
{
	while (tokens)
	{
		if (tokens->type == TOK_WORD || tokens->type == TOK_STRING)
		{
			if (process_word_string(&tokens, curr) == RETURN_FAILURE)
				return (RETURN_FAILURE);
		}
		else if (tokens->type == TOK_REDIRECT_IN)
		{
			if (process_redirect_in(&tokens, curr, head) == RETURN_FAILURE)
				return (RETURN_FAILURE);
		}
		else if (tokens->type == TOK_REDIRECT_OUT)
		{
			if (process_redirect_out(&tokens, curr, head) == RETURN_FAILURE)
				return (RETURN_FAILURE);
		}
		else if (tokens->type == TOK_PIPE)
		{
			if (process_pipe(&curr, head) == RETURN_FAILURE)
				return (RETURN_FAILURE);
			tokens = tokens->next;
		}
		else
			tokens = tokens->next;
	}
	return (RETURN_SUCCESS);
}





