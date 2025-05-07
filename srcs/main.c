/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:16:29 by tarini            #+#    #+#             */
/*   Updated: 2025/05/07 08:06:29 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void exit_minishell_proprely(char *input, t_token *token)
{
	rl_clear_history();
	free(input);
	free_tokens(token);
	exit(0);
}

static void print_commands(t_command *cmd) // DEBUG
{
	int i;

	i = 0;
    while (cmd)
    {
        printf("Command: %s\n", cmd->cmd);
        if (cmd->args)
        {
            while (cmd->args[i])
            {
				printf("  Arg: %s\n", cmd->args[i]);
				i++;
			}
        }
        if (cmd->redirect_in)
            printf("  Redirect In: %s\n", cmd->redirect_in);
        if (cmd->redirect_out)
            printf("  Redirect Out: %s\n", cmd->redirect_out);
        cmd = cmd->next;
    }
}

static void print_tokens(t_token *head) // DEBUG
{
	while (head)
	{
		printf("token: type=%d, value='%s'\n", head->type, head->value);
		head = head->next;
	}
}

int main(int argc, char *argv[], char **env)
{
	char *input;
	t_token *token;
	
	env = NULL; //TORMASAP
	if (argc > 1)
		exit(1);
	argv = NULL;
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
		printf("You entered the legendary command: '%s'\n", input);
		print_tokens(token);
		t_command *command = parse_tokens(token);
		print_commands(command);
		exec(command);
		free(input);
		free_tokens(token);
	}
	return (0);
}
