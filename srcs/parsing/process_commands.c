/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 16:10:48 by tarini            #+#    #+#             */
/*   Updated: 2025/05/07 16:54:38 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "return_error.h"
#include "../../libft/includes/libft.h"

static int is_word_like(t_token *token)
{
    return (token->type == TOK_WORD ||
            token->type == TOK_STRING ||
            token->type == TOK_SINGLE_QUOTES ||
            token->type == TOK_DOUBLE_QUOTES);
}

static int process_word_string(t_token **tokens, t_command *curr)
{
    if (is_word_like(*tokens))
        curr->cmd = add_argument(curr->cmd, (*tokens)->value);
    return (RETURN_SUCCESS);
}

static int process_redirect_in(t_token **tokens, t_command *curr, t_command *head)
{
    (*tokens) = (*tokens)->next;
    if (!(*tokens) || !is_word_like(*tokens))
    {
        free_commands(head);
        return (RETURN_FAILURE);
    }
    curr->redirect_in = ft_strdup((*tokens)->value);
    return (RETURN_SUCCESS);
}

static int process_redirect_out(t_token **tokens, t_command *curr, t_command *head)
{
    (*tokens) = (*tokens)->next;
    if (!(*tokens) || !is_word_like(*tokens))
    {
        free_commands(head);
        return (RETURN_FAILURE);
    }
    curr->redirect_out = ft_strdup((*tokens)->value);
    return (RETURN_SUCCESS);
}

static int process_heredoc(t_token **tokens, t_command *curr, t_command *head)
{
    (*tokens) = (*tokens)->next;
    if (!(*tokens) || !is_word_like(*tokens))
    {
        free_commands(head);
        return (RETURN_FAILURE);
    }
    curr->heredoc = ft_strdup((*tokens)->value);
    if (!curr->heredoc)
    {
        free_commands(head);
        return (RETURN_FAILURE);
    }
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

static int process_append_redirect(t_token **tokens, t_command *curr, t_command *head)
{
    (*tokens) = (*tokens)->next;
    if (!(*tokens) || !is_word_like(*tokens))
    {
        free_commands(head);
        return (RETURN_FAILURE);
    }
    curr->append_redirections = ft_strdup((*tokens)->value);
    if (!curr->append_redirections)
    {
        free_commands(head);
        return (RETURN_FAILURE);
    }
    return (RETURN_SUCCESS);
}

int process_parsing(t_token *tokens, t_command *curr, t_command *head)
{
    if (is_word_like(tokens))
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
    }
    else if (tokens->type == TOK_HEREDOC)
    {
        if (process_heredoc(&tokens, curr, head) == RETURN_FAILURE)
            return (RETURN_FAILURE);
    }
    else if (tokens->type == TOK_APPEND_REDIRECT)
    {
        if (process_append_redirect(&tokens, curr, head) == RETURN_FAILURE)
            return (RETURN_FAILURE);
    }
    return (RETURN_SUCCESS);
}
