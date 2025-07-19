/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:30:41 by tarini            #+#    #+#             */
/*   Updated: 2025/07/19 22:46:07 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_all_spaces(const char *str)
{
	while (*str)
	{
		if (*str != ' ' && *str != '\t')
			return (RETURN_FAILURE);
		str++;
	}
	return (RETURN_SUCCESS);
}

static bool	skip_empty_or_spaces(char *input)
{
	if (input[0] == '\0' || !is_all_spaces(input))
	{
		free(input);
		return (true);
	}
	return (false);
}

static bool	handle_null_input(char *input, t_utils *utils)
{
	if (!input)
	{
		utils->run = 0;
		return (false);
	}
	return (true);
}

static void	free_all(char *input, t_token *token)
{
	free(input);
	free_tokens(token);
}

void	minishell_loop(t_utils *utils)
{
	char			*input;
	t_token			*token;
	t_command_exec	*command;
	t_token			*syntax_error_token;

	while (utils->run)
	{
		input = read_input_with_quotes(utils);
		if (!handle_null_input(input, utils))
			break ;
		if (skip_empty_or_spaces(input))
			continue ;
		if (*input)
			add_history(input);
		token = process_lexer(input, utils);
		if (!token)
			continue ;
		syntax_error_token = find_syntax_error(token);
		if (syntax_error_token)
		{
			print_syntax_error(syntax_error_token->value, utils);
			free_all(input, token);
			continue ;
		}
		utils->type_of_first_arg = token->type;
		command = parse_tokens(token, utils);
		if (!command)
		{
			free_all(input, token);
			continue ;
		}
		execute_or_cleanup(command, token, input, utils);
	}
}
