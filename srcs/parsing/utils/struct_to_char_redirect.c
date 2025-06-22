/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_to_char_redirect.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 10:01:13 by stafpec           #+#    #+#             */
/*   Updated: 2025/06/14 15:45:38 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../../../libft/includes/libft.h"

static t_redirect	*copy_redirect_elem(t_arg *src)
{
	t_redirect	*dest;

	if (!src)
		return (NULL);
	dest = malloc(sizeof(t_redirect));
	if (!dest)
		return (NULL);
	dest->arg = ft_strdup(src->arg);
	if (!dest->arg)
	{
		free(dest);
		return (NULL);
	}
	dest->fd = src->fd;
	dest->append_redirect = src->append_redirect;
	dest->heredoc = src->heredoc;
	return (dest);
}

static void	free_redirect_array_partial(t_redirect **arr, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(arr[i]->arg);
		free(arr[i]);
		i++;
	}
	free(arr);
}

static t_redirect	**copy_redirect_array(t_arg **src)
{
	t_redirect	**dest;
	int			i;
	int			count;

	if (!src)
		return (NULL);
	count = 0;
	while (src[count])
		count++;
	dest = malloc(sizeof(t_redirect *) * (count + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (src[i])
	{
		dest[i] = copy_redirect_elem(src[i]);
		if (!dest[i])
		{
			free_redirect_array_partial(dest, i);
			return (NULL);
		}
		i++;
	}
	dest[i] = NULL;
	return (dest);
}

int	redirect_to_char(t_command *cmd, t_command_exec *new_node)
{
	new_node->redirect_in = copy_redirect_array(cmd->redirect_in);
	if (cmd->redirect_in && !new_node->redirect_in)
		return (RETURN_FAILURE);
	new_node->redirect_out = copy_redirect_array(cmd->redirect_out);
	if (cmd->redirect_out && !new_node->redirect_out)
		return (RETURN_FAILURE);
	return (RETURN_SUCCESS);
}
