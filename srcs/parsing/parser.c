/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:14:45 by tarini            #+#    #+#             */
/*   Updated: 2025/05/03 11:40:07 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "lexer.h"
#include "../../libft/includes/libft.h"

static char **add_argument(char **args, const char *value)
{
	size_t i;
	size_t j;
	char **new_args;

	i = 0;
	if (args)
	{
		while (args[i])
		   i++;
	}
	new_args = malloc(sizeof(char *) * (i + 2));
	if (!new_args)
		return (NULL);
	j = 0;
	while (j < i)
	{
		new_args[j] = args[j];
		j++;
	}
	new_args[i] = ft_strdup(value);
	new_args[i + 1] = NULL;
	free(args);
	return (new_args);
}

static t_command *create_command()
{
	t_command *cmd;
	
	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return NULL;
	cmd->cmd = NULL;
	cmd->args = NULL;
	cmd->redirect_in = NULL;
	cmd->redirect_out = NULL;
	cmd->next = NULL;
	return cmd;
}

void free_commands(t_command *cmd)
{
	t_command *tmp;
	int i;

	i = 0;
	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		free(tmp->cmd);
		while (cmd->args[i])
		{
			free(cmd->args[i]);
			i++;
		}
		free(tmp->redirect_in);
		free(tmp->redirect_out);
		free(tmp);
	}
}

t_command *parse_tokens(t_token *tokens)
{
	t_command *head;
	t_command *curr;

	head = create_command();
	curr = head;
	if (!head)
		return (NULL);
	while (tokens && tokens->type != TOK_END)
	{
		if (tokens->type == TOK_WORD || tokens->type == TOK_STRING)
		{
			if (tokens->type == TOK_WORD || tokens->type == TOK_STRING)
			{
				if (!curr->cmd)
					curr->cmd = ft_strdup(tokens->value);
				else
					curr->args = add_argument(curr->args, tokens->value);
			}
		}
		else if (tokens->type == TOK_REDIRECT_IN)
		{
			tokens = tokens->next;
			if (!tokens || (tokens->type != TOK_WORD && tokens->type != TOK_STRING))
			{
				free_commands(head);    
				return (NULL);
			}   
			curr->redirect_in = ft_strdup(tokens->value);
		}
		else if (tokens->type == TOK_REDIRECT_OUT)
		{
			tokens = tokens->next;
			if (!tokens || (tokens->type != TOK_WORD && tokens->type != TOK_STRING))
			{
				free_commands(head);
				return (NULL);
			}
			curr->redirect_out = ft_strdup(tokens->value);
		}
		else if (tokens->type == TOK_PIPE)
		{
			curr->next = create_command();
			if (!curr->next)
			{
				free_commands(head);
				return (NULL);
			}
			curr = curr->next;
		}
		tokens = tokens->next;
	}
	return (head);
}
