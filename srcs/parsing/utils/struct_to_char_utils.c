/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_to_char_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 05:51:33 by stafpec           #+#    #+#             */
/*   Updated: 2025/06/08 05:52:58 by stafpec          ###   ########.fr       */
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

char	**dup_targ_array(t_arg **arr)
{
	int		count;
	char	**new_arr;
	int		i;

	if (!arr)
		return (NULL);
	count = 0;
	while (arr[count])
		count++;
	new_arr = malloc(sizeof(char *) * (count + 1));
	if (!new_arr)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_arr[i] = ft_strdup(arr[i]->arg);
		if (!new_arr[i])
		{
			free_str_array(new_arr, i);
			return (NULL);
		}
		i++;
	}
	new_arr[count] = NULL;
	return (new_arr);
}

t_heredoc	*dup_heredoc_from_arg(t_arg *src)
{
	t_heredoc	*copy;

	if (!src)
		return (NULL);
	copy = malloc(sizeof(t_heredoc));
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
