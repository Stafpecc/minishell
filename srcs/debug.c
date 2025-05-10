/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 14:31:40 by tarini            #+#    #+#             */
/*   Updated: 2025/05/10 14:50:59 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_tokens(t_token *head) // DEBUG
{
	while (head)
	{
		printf("token: type=%d, value='%s'\n", head->type, head->value);
		head = head->next;
	}
}

void print_commands(t_command *cmd) // DEBUG
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
				const char *simple_quote_status;
				const char *double_quote_status;

				if (cmd->cmd_parts[i]->in_simple_quote)
					simple_quote_status = "true";
				else
					simple_quote_status = "false";

				if (cmd->cmd_parts[i]->in_double_quote)
					double_quote_status = "true";
				else
					double_quote_status = "false";

				printf("cmd_parts[%d]: \"%s\" (in_simple_quote: %s, in_double_quote: %s)\n",
					   i,
					   cmd->cmd_parts[i]->arg,
					   simple_quote_status,
					   double_quote_status);
				i++;
			}
		}
		else
			printf("No cmd_parts.\n");

		printf("redirect_in: %s\n", cmd->redirect_in ? cmd->redirect_in : "NULL");
		printf("redirect_out: %s\n", cmd->redirect_out ? cmd->redirect_out : "NULL");

		if (cmd->append_redirections)
		{
			const char *append_simple_status;
			const char *append_double_status;

			if (cmd->append_redirections->in_simple_quote)
				append_simple_status = "true";
			else
				append_simple_status = "false";

			if (cmd->append_redirections->in_double_quote)
				append_double_status = "true";
			else
				append_double_status = "false";

			printf("append_redirections: \"%s\" (in_simple_quote: %s, in_double_quote: %s)\n",
				   cmd->append_redirections->arg,
				   append_simple_status,
				   append_double_status);
		}
		else
			printf("No append_redirections.\n");

		if (cmd->heredoc)
		{
			const char *heredoc_simple_status;
			const char *heredoc_double_status;

			if (cmd->heredoc->in_simple_quote)
				heredoc_simple_status = "true";
			else
				heredoc_simple_status = "false";

			if (cmd->heredoc->in_double_quote)
				heredoc_double_status = "true";
			else
				heredoc_double_status = "false";

			printf("heredoc: \"%s\" (in_simple_quote: %s, in_double_quote: %s)\n",
				   cmd->heredoc->arg,
				   heredoc_simple_status,
				   heredoc_double_status);
		}
		else
			printf("No heredoc.\n");

		printf("\n");
		cmd = cmd->next;
	}
}
