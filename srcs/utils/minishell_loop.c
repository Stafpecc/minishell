/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:30:41 by tarini            #+#    #+#             */
/*   Updated: 2025/07/17 15:13:49 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*read_and_handle_input(t_utils *utils)
{
	char	*input;

	input = read_input_with_quotes(utils);
	if (!input)
		return (NULL);
	if (!handle_null_input(input, utils))
	{
		free(input);
		return (NULL);
	}
	if (skip_empty_or_spaces(input))
	{
		free(input);
		return (NULL);
	}
	if (*input)
		add_history(input);
	return (input);
}

static t_token	*lex_input(char *input, t_utils *utils)
{
	t_token	*token;

	token = process_lexer(input, utils);
	if (!token)
	{
		free(input);
		return (NULL);
	}
	utils->type_of_first_arg = token->type;
	return (token);
}

static t_command_exec	*parse_token_list(t_token *token,
	char *input, t_utils *utils)
{
	t_command_exec	*command;

	command = parse_tokens(token, utils);
	if (!command)
	{
		free(input);
		free_tokens(token);
		return (NULL);
	}
	return (command);
}

void	minishell_loop(t_utils *utils)
{
	char			*input;
	t_token			*token;
	t_command_exec	*command;

	while (utils->run)
	{
		input = read_and_handle_input(utils);
		if (!input)
			break ;
		token = lex_input(input, utils);
		if (!token)
			break ;
		command = parse_token_list(token, input, utils);
		if (!command)
			break ;
		execute_or_cleanup(command, token, input, utils);
		set_signals();
	}
}
