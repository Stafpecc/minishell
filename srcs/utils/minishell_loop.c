/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:30:41 by tarini            #+#    #+#             */
/*   Updated: 2025/07/20 16:18:49 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_user_input(t_utils *utils)
{
	char	*input;

	input = read_input_with_quotes(utils);
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
	return (token);
}

static bool	check_syntax_errors(t_token *token, t_utils *utils, char *input)
{
	t_token	*syntax_error_token;

	syntax_error_token = find_syntax_error(token);
	if (syntax_error_token)
	{
		print_syntax_error(syntax_error_token->value, utils);
		free_all(input, token);
		return (true);
	}
	return (false);
}

static t_command_exec	*parse_command(t_token *token, t_utils *utils,
	char *input)
{
	t_command_exec	*command;

	command = parse_tokens(token, utils);
	if (!command)
	{
		free_all(input, token);
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
		input = get_user_input(utils);
		if (!input)
			break ;
		token = lex_input(input, utils);
		if (!token)
		{
			free(input);
			continue ;
		}
		if (check_syntax_errors(token, utils, input))
			continue ;
		utils->type_of_first_arg = token->type;
		command = parse_command(token, utils, input);
		if (!command)
			continue ;
		execute_or_cleanup(command, token, input, utils);
	}
}
