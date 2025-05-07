/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:16:29 by tarini            #+#    #+#             */
/*   Updated: 2025/05/07 16:42:59 by tarini           ###   ########.fr       */
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
        if (cmd->cmd)
        {
            while (cmd->cmd[i])
            {
				printf("  Arg: %s\n", cmd->cmd[i]);
				i++;
			}
        }
        if (cmd->redirect_in)
            printf("  Redirect In: %s\n", cmd->redirect_in);
        if (cmd->redirect_out)
            printf("  Redirect Out: %s\n", cmd->redirect_out);
		if (cmd->heredoc)
            printf("  Heredoc pass: %s\n", cmd->heredoc);
		if (cmd->append_redirections)
            printf("  Append redirection out: %s\n", cmd->append_redirections);
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
		printf("You entered the legendary command: '%s'\n", input);
		print_tokens(token);
		t_command *command = parse_tokens(token);
		print_commands(command);
		free(input);
		free_tokens(token);
	}
	return (0);
}
