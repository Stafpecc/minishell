/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_word_string.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 12:46:38 by ldevoude          #+#    #+#             */
/*   Updated: 2025/07/20 16:13:22 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	get_cmd_parts_count(t_command *curr)
{
	int	i;

	i = 0;
	while (curr->cmd_parts && curr->cmd_parts[i])
		i++;
	return (i);
}

t_arg	**extend_cmd_parts(t_arg **old_array, int old_size,
		t_arg *new_part)
{
	t_arg	**new_array;
	int		j;

	new_array = malloc(sizeof(t_arg *) * (old_size + 2));
	if (!new_array)
		return (NULL);
	j = 0;
	while (j < old_size)
	{
		new_array[j] = old_array[j];
		j++;
	}
	new_array[old_size] = new_part;
	new_array[old_size + 1] = NULL;
	free(old_array);
	return (new_array);
}

/*
Function that:
- adds a new token of type word or string to a command's cmd_parts list;
- allocates a new t_arg structure and copies the token's value after
duplication;
- processes any quotes in the token to properly mark the new part;
- creates a new, larger t_arg* array, copies the old contents, adds the new
part, and terminates with NULL;
- frees the old cmd_parts array and updates the command with the new array;
- returns RETURN_SUCCESS if everything went well, otherwise RETURN_FAILURE 
on allocation error.
*/
int	process_word_string(t_token **tokens, t_command *curr, t_utils *utils)
{
	int		count;
	t_arg	*new_part;
	t_arg	**new_array;

	(void)utils;
	new_part = malloc(sizeof(t_arg));
	if (!new_part)
		return (RETURN_FAILURE);
	ft_bzero(new_part, sizeof(t_arg));
	new_part->arg = ft_strdup((*tokens)->value);
	if (!new_part->arg)
	{
		free(new_part);
		return (RETURN_FAILURE);
	}
	count = get_cmd_parts_count(curr);
	new_array = extend_cmd_parts(curr->cmd_parts, count, new_part);
	if (!new_array)
	{
		free(new_part->arg);
		free(new_part);
		return (RETURN_FAILURE);
	}
	curr->cmd_parts = new_array;
	return (RETURN_SUCCESS);
}
