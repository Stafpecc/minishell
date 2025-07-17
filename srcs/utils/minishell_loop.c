/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:30:41 by tarini            #+#    #+#             */
/*   Updated: 2025/07/17 15:46:34 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_loop(t_utils *utils)
{
	char			*input;
	t_token			*token;
	t_command_exec	*command;

	while (utils->run)
	{
		input = read_input_with_quotes(utils);
		if (!input)
			break ;
		if (!handle_null_input(input, utils))
			break ;
		if (skip_empty_or_spaces(input))
			continue ;
		if (*input)
			add_history(input);
		token = process_lexer(input, utils);
		if (!token)
			continue ;
		utils->type_of_first_arg = token->type;
		command = parse_tokens(token, utils);
		if (!command)
		{
			free(input);
			free_tokens(token);
			break ;
		}
		execute_or_cleanup(command, token, input, utils);
		set_signals();
	}
}
