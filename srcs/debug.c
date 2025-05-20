/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
/*   Created: 2025/05/10 14:31:40 by tarini            #+#    #+#             */
/*   Updated: 2025/05/10 14:50:59 by tarini           ###   ########.fr       */
=======
/*   Created: 2025/05/10 18:01:42 by tarini            #+#    #+#             */
/*   Updated: 2025/05/20 10:35:18 by tarini           ###   ########.fr       */
>>>>>>> tarini
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
<<<<<<< HEAD
=======
#include "../libft/includes/libft.h"

void print_commands(t_command *cmd) // DEBUG
{
    int i;
    int node;

    node = 1;
    while (cmd)
    {
        ft_printf("\n---- Command Node %d ----\n", node++);
        if (cmd->cmd_parts)
        {
            i = 0;
            while (cmd->cmd_parts[i])
            {
                ft_printf("cmd_parts[%d]: \"%s\" (in_simple_quote: %s, in_double_quote: %s)\n",
                       i,
                       cmd->cmd_parts[i]->arg,
                       cmd->cmd_parts[i]->in_simple_quote ? "true" : "false",
                       cmd->cmd_parts[i]->in_double_quote ? "true" : "false");
                i++;
            }
        }
        else
            ft_printf("No cmd_parts.\n");
        if (cmd->redirect_in && cmd->redirect_in->arg)
        {
            ft_printf("redirect_in: \"%s\" (in_simple_quote: %s, in_double_quote: %s)\n",
                   cmd->redirect_in->arg,
                   cmd->redirect_in->in_simple_quote ? "true" : "false",
                   cmd->redirect_in->in_double_quote ? "true" : "false");
        }
        else
            ft_printf("redirect_in: NULL\n");
        if (cmd->redirect_out && cmd->redirect_out->arg)
        {
            ft_printf("redirect_out: \"%s\" (in_simple_quote: %s, in_double_quote: %s)\n",
                   cmd->redirect_out->arg,
                   cmd->redirect_out->in_simple_quote ? "true" : "false",
                   cmd->redirect_out->in_double_quote ? "true" : "false");
        }
        else
            ft_printf("redirect_out: NULL\n");
        if (cmd->append_redirections && cmd->append_redirections->arg)
        {
            ft_printf("append_redirections: \"%s\" (in_simple_quote: %s, in_double_quote: %s)\n",
                   cmd->append_redirections->arg,
                   cmd->append_redirections->in_simple_quote ? "true" : "false",
                   cmd->append_redirections->in_double_quote ? "true" : "false");
        }
        else
            ft_printf("No append_redirections.\n");
        if (cmd->heredoc && cmd->heredoc->arg)
        {
            ft_printf("heredoc: \"%s\" (in_simple_quote: %s, in_double_quote: %s)\n",
                   cmd->heredoc->arg,
                   cmd->heredoc->in_simple_quote ? "true" : "false",
                   cmd->heredoc->in_double_quote ? "true" : "false");
        }
        else
            ft_printf("No heredoc.\n");
        ft_printf("\n");
        cmd = cmd->next;
    }
}

void print_command_exec(t_command_exec *cmd)
{
    int node;
    int i;

    node = 1;
    ft_printf("\n-----------------------------------------------------------\n\n");
    while (cmd)
    {
        ft_printf("\n---- Command Exec Node %d ----\n", node++);
        if (cmd->cmd_parts)
        {
            i = 0;
            while (cmd->cmd_parts[i])
            {
                ft_printf("cmd_parts[%d]: \"%s\"\n", i, cmd->cmd_parts[i]);
                i++;
            }
        }
        else
            ft_printf("No cmd_parts.\n");

        if (cmd->redirect_in)
            ft_printf("redirect_in: \"%s\"\n", cmd->redirect_in);
        else
            ft_printf("redirect_in: NULL\n");

        if (cmd->redirect_out)
            ft_printf("redirect_out: \"%s\"\n", cmd->redirect_out);
        else
            ft_printf("redirect_out: NULL\n");

        if (cmd->append_redirections)
            ft_printf("append_redirections: \"%s\"\n", cmd->append_redirections);
        else
            ft_printf("append_redirections: NULL\n");

        if (cmd->heredoc)
            ft_printf("heredoc: \"%s\"\n", cmd->heredoc);
        else
            ft_printf("heredoc: NULL\n");

        ft_printf("\n");
        cmd = cmd->next;
    }
}
>>>>>>> tarini

void print_tokens(t_token *head) // DEBUG
{
	while (head)
	{
		printf("token: type=%d, value='%s'\n", head->type, head->value);
		head = head->next;
	}
<<<<<<< HEAD
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
=======
}
>>>>>>> tarini
