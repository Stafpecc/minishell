
#include "minishell.h"
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

void print_tokens(t_token *head) // DEBUG
{
	while (head)
	{
		printf("token: type=%d, value='%s'\n", head->type, head->value);
		head = head->next;
	}
}