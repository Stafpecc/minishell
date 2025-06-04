

#include "minishell.h"
#include "../libft/includes/libft.h"


void print_utils_struct(t_utils *utils) // DEBUG
{
	int i;
	
	ft_printf("\n-----------------------------------------------------------\n");
	ft_printf("\n---- UTILS ----\n");
	if (!utils)
	{
		ft_printf("utils: (null)\n");
		return;
	}
	ft_printf("t_utils content:\n");
	ft_printf("  last_return       : %d\n", utils->last_return);
	ft_printf("  num_nodes         : %d\n", utils->num_nodes);
	ft_printf("  previous_pipes    : %d\n", utils->previous_pipes);
	ft_printf("  type of first cmd : %d\n", utils->type_of_first_arg);
	ft_printf("  env:\n");
	if (!utils->env)
	{
		ft_printf("    (null)\n");
		return;
	}
	for (i = 0; utils->env[i]; i++)
	{
		ft_printf("    [%d] %s\n", i, utils->env[i]);
	}
	ft_printf("\n-----------------------------------------------------------\n");
}

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
        if (cmd->redirect_in)
        {
            i = 0;
            while (cmd->redirect_in[i])
            {
                ft_printf("redirect_in[%d]: \"%s\"\n", i, cmd->redirect_in[i]);
                i++;
            }
        }
        else
            ft_printf("redirect_in: NULL\n");
        if (cmd->redirect_out)
        {
            i = 0;
            while (cmd->redirect_out[i])
            {
                ft_printf("redirect_out[%d]: \"%s\"\n", i, cmd->redirect_out[i]);
                i++;
            }
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
