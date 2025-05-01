/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:16:29 by tarini            #+#    #+#             */
/*   Updated: 2025/05/01 18:28:13 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"



int main(void)
{
	char *input;
	t_token *token;

	set_signals();
	while (1)
	{
		input = readline("minishell> ");
		if (input && *input)
		{
			add_history(input);
			printf("You entered the legendary command: '%s'\n", input);
			token = lexer(input);
			print_tokens(token);
		}
		free(input);
		free_tokens(token);
	}
	return (0);
}
