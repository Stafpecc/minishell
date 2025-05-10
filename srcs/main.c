/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:16:29 by tarini            #+#    #+#             */
/*   Updated: 2025/05/10 17:52:47 by tarini           ###   ########.fr       */
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
    int node = 1;

    while (cmd)
    {
        printf("\n---- Command Node %d ----\n", node++);
        if (cmd->cmd_parts)
        {
            i = 0;
            while (cmd->cmd_parts[i])
            {
                printf("cmd_parts[%d]: \"%s\" (in_simple_quote: %s, in_double_quote: %s)\n",
                       i,
                       cmd->cmd_parts[i]->arg,
                       cmd->cmd_parts[i]->in_simple_quote ? "true" : "false",
                       cmd->cmd_parts[i]->in_double_quote ? "true" : "false");
                i++;
            }
        }
        else
        {
            printf("No cmd_parts.\n");
        }

        // redirect_in
        if (cmd->redirect_in && cmd->redirect_in->arg)
        {
            printf("redirect_in: \"%s\" (in_simple_quote: %s, in_double_quote: %s)\n",
                   cmd->redirect_in->arg,
                   cmd->redirect_in->in_simple_quote ? "true" : "false",
                   cmd->redirect_in->in_double_quote ? "true" : "false");
        }
        else
        {
            printf("redirect_in: NULL\n");
        }

        // redirect_out
        if (cmd->redirect_out && cmd->redirect_out->arg)
        {
            printf("redirect_out: \"%s\" (in_simple_quote: %s, in_double_quote: %s)\n",
                   cmd->redirect_out->arg,
                   cmd->redirect_out->in_simple_quote ? "true" : "false",
                   cmd->redirect_out->in_double_quote ? "true" : "false");
        }
        else
        {
            printf("redirect_out: NULL\n");
        }

        // append_redirections
        if (cmd->append_redirections && cmd->append_redirections->arg)
        {
            printf("append_redirections: \"%s\" (in_simple_quote: %s, in_double_quote: %s)\n",
                   cmd->append_redirections->arg,
                   cmd->append_redirections->in_simple_quote ? "true" : "false",
                   cmd->append_redirections->in_double_quote ? "true" : "false");
        }
        else
        {
            printf("No append_redirections.\n");
        }

        // heredoc
        if (cmd->heredoc && cmd->heredoc->arg)
        {
            printf("heredoc: \"%s\" (in_simple_quote: %s, in_double_quote: %s)\n",
                   cmd->heredoc->arg,
                   cmd->heredoc->in_simple_quote ? "true" : "false",
                   cmd->heredoc->in_double_quote ? "true" : "false");
        }
        else
        {
            printf("No heredoc.\n");
        }

        printf("\n");
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
		(void)command;
		print_commands(command);
		free(input);
		free_tokens(token);
	}
	return (0);
}
