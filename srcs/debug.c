

#include "minishell.h"
#include "../libft/includes/libft.h"

const char *get_token_type_str(t_token_type type) // DEBUG
{
	switch (type)
	{
		case TOK_WORD: return "TOK_WORD";
		case TOK_PIPE: return "TOK_PIPE";
		case TOK_REDIRECT_OUT: return "TOK_REDIRECT_OUT";
		case TOK_REDIRECT_IN: return "TOK_REDIRECT_IN";
		case TOK_STRING: return "TOK_STRING";
		case TOK_HEREDOC: return "TOK_HEREDOC";
		case TOK_SINGLE_QUOTES: return "TOK_SINGLE_QUOTES";
		case TOK_DOUBLE_QUOTES: return "TOK_DOUBLE_QUOTES";
		case TOK_APPEND_REDIRECT: return "TOK_APPEND_REDIRECT";
		case TOK_END: return "TOK_END";
		default: return "UNKNOWN";
	}
}

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
    int node = 1;

    while (cmd)
    {
        ft_printf("\n---- Command Node %d ----\n", node++);

        // cmd_parts
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

        // redirect_in
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

        // redirect_out
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
        ft_printf("\n");
        cmd = cmd->next;
    }
}

void	print_command_exec(t_command_exec *cmd)
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
		{
			i = 0;
			while (cmd->redirect_in[i])
			{
				ft_printf("redirect_in[%d]: \"%s\"\n", i, cmd->redirect_in[i]->arg);
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
				ft_printf("redirect_out[%d]: \"%s\"\n", i, cmd->redirect_out[i]->arg);
				i++;
			}
			if (i == 0)
				ft_printf("redirect_out: (empty)\n");
		}
		else
			ft_printf("redirect_out: NULL\n");

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
