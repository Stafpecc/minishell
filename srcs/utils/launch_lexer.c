/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:31:32 by stafpec           #+#    #+#             */
/*   Updated: 2025/06/26 13:12:49 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	quote_not_closed(const char *str)
{
	char	quote;
	int		i;

	quote = 0;
	i = 0;
	while (str[i])
	{
		if ((str[i] == '"' || str[i] == '\'') && quote == 0)
			quote = str[i];
		else if (str[i] == quote)
			quote = 0;
		i++;
	}
	return (quote);
}

t_token	*process_lexer(char *input, t_utils *utils)
{
	t_token	*token;

	token = lexer(input);
	if (!token)
	{
		free(input);
		return (NULL);
	}
	if (token->type != TOK_END && has_only_one_redirection(token))
	{
		print_syntax_error("newline", utils);
		free_tokens(token);
		free(input);
		return (NULL);
	}
	return (token);
}
