/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_gestionary.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 16:08:37 by tarini            #+#    #+#             */
/*   Updated: 2025/06/10 16:24:52 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../../../libft/includes/libft.h"

static void	*return_free_args(t_arg **new_args)
{
	free(new_args);
	return (NULL);
}

static size_t	size_of_args(t_arg **args)
{
	size_t	i;

	i = 0;
	if (args)
	{
		while (args[i])
			i++;
	}
	return (i);
}

t_arg	**add_argument(t_arg **args, const char *value)
{
	size_t	j;
	size_t	i;
	t_arg	**new_args;

	i = size_of_args(args);
	j = 0;
	new_args = malloc(sizeof(t_arg *) * (i + 2));
	if (!new_args)
		return (NULL);
	while (j < i)
	{
		new_args[j] = args[j];
		j++;
	}
	new_args[i] = malloc(sizeof(t_arg));
	if (!new_args[i])
		return (return_free_args(new_args));
	new_args[i]->arg = ft_strdup(value);
	new_args[i]->in_simple_quote = false;
	new_args[i]->in_double_quote = false;
	new_args[i + 1] = NULL;
	free(args);
	return (new_args);
}

t_command	*create_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->cmd_parts = NULL;
	cmd->redirect_in = NULL;
	cmd->redirect_out = NULL;
	cmd->append_redirections = NULL;
	cmd->heredoc = NULL;
	cmd->next = NULL;
	return (cmd);
}

int	get_size_of_redirect(t_arg **redirect)
{
	int	i;

	i = 0;
	if (redirect)
	{
		while (redirect[i])
			i++;
	}
	return (i);
}

/*
	int last_redirect_in;
	int last_redirect_out;

	last_redirect_in = get_size_of_redirect(cmd->redirect_in);
	last_redirect_out = get_size_of_redirect(cmd->redirect_out);
*/
