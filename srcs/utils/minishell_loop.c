/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:30:41 by tarini            #+#    #+#             */
/*   Updated: 2025/07/12 15:53:54 by stafpec          ###   ########.fr       */
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

void	minishell_loop(t_utils *utils)
{
	char			*input;
	t_token			*token;
	t_command_exec	*command;

	while (utils->run)
	{
		//ft_printf("LAST RETURN =%d\n", utils->last_return);
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
		utils->type_of_first_arg = token->type;
		command = parse_tokens(token, utils);
		execute_or_cleanup(command, token, input, utils);
	}
}
