/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:30:41 by tarini            #+#    #+#             */
/*   Updated: 2025/07/20 12:45:14 by ldevoude         ###   ########lyon.fr   */
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
		ft_printfd("exit\n");
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

static t_token *find_syntax_error(t_token *tokens)
{
	if (!tokens)
		return NULL;

	if (tokens->type == TOK_PIPE
		|| tokens->type == TOK_REDIRECT_IN
		|| tokens->type == TOK_REDIRECT_OUT
		|| tokens->type == TOK_APPEND_REDIRECT
		|| tokens->type == TOK_HEREDOC)
		return tokens;
	t_token *curr = tokens;
	while (curr && curr->next)
	{
		if (curr->type == TOK_PIPE && curr->next->type == TOK_PIPE)
			return curr->next;
		if ((curr->type == TOK_REDIRECT_IN || curr->type == TOK_REDIRECT_OUT
			 || curr->type == TOK_APPEND_REDIRECT || curr->type == TOK_HEREDOC))
		{
			if (curr->next->type != TOK_WORD && curr->next->type != TOK_STRING
				&& curr->next->type != TOK_SINGLE_QUOTES && curr->next->type != TOK_DOUBLE_QUOTES)
				return curr->next;
		}
		curr = curr->next;
	}
	return (NULL);
}

void minishell_loop(t_utils *utils)
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
