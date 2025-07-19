/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 21:05:16 by tarini            #+#    #+#             */
/*   Updated: 2025/07/19 21:13:24 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	ft_free_split(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
		free(array[i++]);
	free(array);
}

static int	free_all()

int	reparse_expanded_string(char *expanded, t_command *curr, bool was_expanded)
{
	char	**words;
	int		count;
	int		i;
	t_arg	*new_part;
	t_arg	**new_array;

	words = ft_split(expanded, ' ');
	if (!words)
		return (RETURN_FAILURE);
	i = 0;
	while (words[i])
	{
		new_part = malloc(sizeof(t_arg));
		if (!new_part)
		{
			ft_free_split(words);
			return (RETURN_FAILURE);
		}
		ft_bzero(new_part, sizeof(t_arg));
		new_part->arg = ft_strdup(words[i]);
		if (!new_part->arg)
		{
			free(new_part);
			ft_free_split(words);
			return (RETURN_FAILURE);
		}
		count = get_cmd_parts_count(curr);
		new_array = extend_cmd_parts(curr->cmd_parts, count, new_part);
		if (!new_array)
		{
			free(new_part->arg);
			free(new_part);
			ft_free_split(words);
			return (RETURN_FAILURE);
		}
		curr->cmd_parts = new_array;
		curr->cmd_parts[i]->was_expanded = was_expanded;
		i++;
	}
	ft_free_split(words);
	return (RETURN_SUCCESS);
}
