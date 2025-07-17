/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_to_char_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 05:51:33 by stafpec           #+#    #+#             */
/*   Updated: 2025/07/17 13:37:04 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
//#include "../../../libft/includes/libft.h"

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

void	free_redirect_array(t_redirect **redirects)
{
	int	i;

	i = 0;
	if (!redirects)
		return ;
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
