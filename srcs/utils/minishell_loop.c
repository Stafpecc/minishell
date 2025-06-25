/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:29:16 by stafpec           #+#    #+#             */
/*   Updated: 2025/06/25 18:30:43 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int is_all_spaces(const char *str)
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

static bool	handle_null_input(char *input)
{
	if (!input)
	{
		write(1, "exit\n", 5);
		return (false);
	}
	return (true);
}

void	minishell_loop(t_utils *utils)
{
	char	*input;
	t_token	*token;
	t_command_exec *command;

	while (1)
	{
		input = read_input_with_quotes();
		if (!handle_null_input(input))
			exit_proprely(0);
		if (skip_empty_or_spaces(input))
			continue;
		if (*input)
			add_history(input);
		if (!(token = process_lexer(input, utils)))
			continue;
		if (handle_exit_builtin(input, token, utils))
			return ;
		utils->type_of_first_arg = token->type;
		command = parse_tokens(token, utils);
		execute_or_cleanup(command, token, input, utils);
	}
}

