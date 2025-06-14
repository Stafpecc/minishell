/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_to_char_redirect.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 10:01:13 by stafpec           #+#    #+#             */
/*   Updated: 2025/06/12 15:47:23 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../../../libft/includes/libft.h"

static t_redirect	**copy_redirect_array(t_arg **src)
{
	int			i;
	t_redirect	**dest;

	if (!src)
		return (NULL);
	i = 0;
	while (src[i])
		i++;
	dest = malloc(sizeof(t_redirect *) * (i + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (src[i])
	{
		dest[i] = malloc(sizeof(t_redirect));
		if (!dest[i])
			return (NULL);
		dest[i]->arg = ft_strdup(src[i]->arg);
		if (!dest[i]->arg)
			return (NULL);
		dest[i]->fd = src[i]->fd;
		dest[i]->append_redirect = src[i]->append_redirect;
		dest[i]->heredoc = src[i]->heredoc;
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
