/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_add_redirect.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 14:24:41 by stafpec           #+#    #+#             */
/*   Updated: 2025/07/17 13:34:05 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
//#include "../../../libft/includes/libft.h"

static int	handle_token_error(t_token **tokens, t_utils *utils)
{
	if (*tokens && !is_redirect_or_pipe(*tokens))
		print_syntax_error((*tokens)->value, utils);
	else
		print_syntax_error("newline", utils);
	return (RETURN_FAILURE);
}

static t_arg	**resize_redirect_array(t_arg ***redirect_array, int *i)
{
	t_arg	**new_redirect;
	size_t	new_size;
	size_t	old_size;

	*i = 0;
	while (*redirect_array && (*redirect_array)[*i])
		(*i)++;
	old_size = sizeof(t_arg *) * (*i);
	new_size = sizeof(t_arg *) * (*i + 2);
	new_redirect = ft_realloc(*redirect_array, old_size, new_size);
	if (!new_redirect)
		return (NULL);
	*redirect_array = new_redirect;
	return (new_redirect);
}

static int	fill_redirect(t_redir_params *params,
	t_token *token)
{
	t_arg	**array;

	array = *(params->redirect_array);
	array[params->i] = malloc(sizeof(t_arg));
	if (!array[params->i])
		return (RETURN_FAILURE);
	array[params->i + 1] = NULL;
	array[params->i]->arg = ft_strdup(token->value);
	if (!array[params->i]->arg)
	{
		free(array[params->i]);
		return (RETURN_FAILURE);
	}
	array[params->i]->heredoc = params->flags.is_heredoc;
	array[params->i]->append_redirect = params->flags.is_append;
	process_quotes(token, array[params->i]);
	return (RETURN_SUCCESS);
}

int	add_redirect(t_token **tokens, t_arg ***redirect_array,
						t_context *ctx, t_redirect_flags flags)
{
	int				i;
	t_redir_params	params;

	(*tokens) = (*tokens)->next;
	if (!(*tokens) || !is_word_like(*tokens))
		return (handle_token_error(tokens, ctx->utils));
	if (!resize_redirect_array(redirect_array, &i))
		return (RETURN_FAILURE);
	params.redirect_array = redirect_array;
	params.i = i;
	params.flags = flags;
	return (fill_redirect(&params, *tokens));
}
