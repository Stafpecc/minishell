/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_targ_to_tredirect_array.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:37:58 by stafpec           #+#    #+#             */
/*   Updated: 2025/07/17 16:47:12 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
//#include "../../../libft/includes/libft.h"

static void	free_redirect(t_redirect **arr, int count)
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

static int	count_targ(t_arg **arr)
{
	int	count;

	if (!arr)
		return (0);
	count = 0;
	while (arr[count])
		count++;
	return (count);
}

static t_redirect	**return_new_arr(t_redirect **new_arr, int i)
{
	new_arr[i] = NULL;
	return (new_arr);
}

t_redirect	**dup_targ_to_tredirect_array(t_arg **arr)
{
	int			count;
	int			i;
	t_redirect	**new_arr;

	if (!arr)
		return (NULL);
	count = count_targ(arr);
	new_arr = malloc(sizeof(t_redirect *) * (count + 1));
	if (!new_arr)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_arr[i] = malloc(sizeof(t_redirect));
		if (!new_arr[i])
			return (free_redirect(new_arr, i), NULL);
		new_arr[i]->arg = ft_strdup(arr[i]->arg);
		if (!new_arr[i]->arg)
			return (free_redirect(new_arr, i), NULL);
		new_arr[i]->fd = arr[i]->fd;
		new_arr[i]->heredoc = arr[i]->heredoc;
		new_arr[i]->append_redirect = arr[i]->append_redirect;
		i++;
	}
	return (return_new_arr(new_arr, i));
}
