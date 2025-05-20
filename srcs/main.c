/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:16:29 by tarini            #+#    #+#             */
/*   Updated: 2025/05/20 11:28:16 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../libft/includes/libft.h"

void exit_minishell_proprely(char *input, t_token *token)
{
	rl_clear_history();
	free(input);
	free_tokens(token);
	exit(0);
}

int main(void)
{
	char *input;
	t_token *token;

	set_signals();
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			write(1, "exit\n", 5);
			exit(0);
		}
		token = lexer(input);
		if (*input)
			add_history(input);
		if (!has_word_token(token))
			continue;
		if (ft_strcmp(input, "exit") == 0)
			exit_minishell_proprely(input, token);
		print_tokens(token);
		t_command *command = parse_tokens(token);
		(void)command;
		print_commands(command);
		t_command_exec *exec = struct_to_char(command);
		print_command_exec(exec);
		free(input);
		free_tokens(token);
	}
	return (0);
}
