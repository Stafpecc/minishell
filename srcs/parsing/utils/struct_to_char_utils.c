/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_to_char_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 05:51:33 by stafpec           #+#    #+#             */
/*   Updated: 2025/06/12 10:08:58 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../../../libft/includes/libft.h"

void	free_str_array(char **arr, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

t_redirect	**dup_targ_to_tredirect_array(t_arg **arr)
{
	int			count;
	int			i;
	t_redirect	**new_arr;

	if (!arr)
		return (NULL);
	count = 0;
	while (arr[count])
		count++;
	new_arr = malloc(sizeof(t_redirect *) * (count + 1));
	if (!new_arr)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_arr[i] = malloc(sizeof(t_redirect));
		if (!new_arr[i])
		{
			while (--i >= 0)
			{
				free(new_arr[i]->arg);
				free(new_arr[i]);
			}
			free(new_arr);
			return (NULL);
		}
		new_arr[i]->arg = ft_strdup(arr[i]->arg);
		if (!new_arr[i]->arg)
		{
			while (--i >= 0)
			{
				free(new_arr[i]->arg);
				free(new_arr[i]);
			}
			free(new_arr);
			return (NULL);
		}
		new_arr[i]->fd = arr[i]->fd;
		new_arr[i]->heredoc = arr[i]->heredoc;
		new_arr[i]->append_redirect = arr[i]->append_redirect;
		i++;
	}
	new_arr[i] = NULL;
	return (new_arr);
}


t_redirect	*dup_heredoc_from_arg(t_arg *src)
{
	t_redirect	*copy;

	if (!src)
		return (NULL);
	copy = malloc(sizeof(t_redirect));
	if (!copy)
		return (NULL);
	copy->arg = ft_strdup(src->arg);
	if (!copy->arg)
	{
		free(copy);
		return (NULL);
	}
	copy->fd = src->fd;
	return (copy);
}

void	free_redirect_array(t_redirect **redirects)
{
	int	i = 0;

	if (!redirects)
		return;
	while (redirects[i])
	{
		free(redirects[i]->arg);
		free(redirects[i]);
		i++;
	}
	free(redirects);
}

int	cmd_part_to_char(t_command *cmd, t_command_exec *new_node)
{
	int	count;
	int	i;

	count = 0;
	while (cmd->cmd_parts && cmd->cmd_parts[count])
		count++;
	new_node->cmd_parts = malloc(sizeof(char *) * (count + 1));
	if (!new_node->cmd_parts)
		return (RETURN_FAILURE);
	i = 0;
	while (i < count)
	{
		new_node->cmd_parts[i] = ft_strdup(cmd->cmd_parts[i]->arg);
		if (!new_node->cmd_parts[i])
		{
			while (--i >= 0)
				free(new_node->cmd_parts[i]);
			free(new_node->cmd_parts);
			return (RETURN_FAILURE);
		}
		i++;
	}
	new_node->cmd_parts[i] = NULL;
	return (RETURN_SUCCESS);
}

