/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 16:10:48 by tarini            #+#    #+#             */
/*   Updated: 2025/05/04 16:21:41 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "return_error.h"

static int process_word_string(t_token *tokens, t_command *curr)
{
	if (tokens->type == TOK_WORD || tokens->type == TOK_STRING)
	{
		if (!curr->cmd)
			curr->cmd = ft_strdup(tokens->value);
		else
			curr->args = add_argument(curr->args, tokens->value);
	}
}

static int process_redirect_in(t_token *tokens, t_command *curr, char *head)
{
	tokens = tokens->next;
	if (!tokens || (tokens->type != TOK_WORD && tokens->type != TOK_STRING))
	{
		free_commands(head);    
		return (RETURN_FAILURE);
	}   
	curr->redirect_in = ft_strdup(tokens->value);
	return (RETURN_SUCCESS);
}

static int process_redirect_out(t_token *tokens, t_command *curr, char *head)
{
	tokens = tokens->next;
	if (!tokens || (tokens->type != TOK_WORD && tokens->type != TOK_STRING))
	{
		free_commands(head);
		return (RETURN_FAILURE);
	}
	curr->redirect_out = ft_strdup(tokens->value);
	return (RETURN_SUCCESS);
}

static int process_pipe(t_command *curr, char *head)
{
	curr->next = create_command();
	if (!curr->next)
	{
		free_commands(head);
		return (NULL);
	}
	curr = curr->next;
}

int process_parsing(t_token *tokens, t_command *curr, char *head)
{
	if (tokens->type == TOK_WORD || tokens->type == TOK_STRING)
		process_word_string(&tokens, &curr);
	else if (tokens->type == TOK_REDIRECT_IN)
	{
		if (!process_redirect_in(&tokens, &curr, &head))
			return (NULL);
	}
	else if (tokens->type == TOK_REDIRECT_OUT)
	{
		if (!process_redirect_out(&tokens, &curr, &head))
			return (NULL);
	}
	else if (tokens->type == TOK_PIPE)
	{
			
	}
	tokens = tokens->next;
}








