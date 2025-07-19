/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 21:05:16 by tarini            #+#    #+#             */
/*   Updated: 2025/07/19 22:53:00 by stafpec          ###   ########.fr       */
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

static t_arg	*create_arg(const char *word, char **words)
{
	t_arg	*new_part;

	new_part = malloc(sizeof(t_arg));
	if (!new_part)
		return (NULL);
	ft_bzero(new_part, sizeof(t_arg));
	new_part->arg = ft_strdup(word);
	if (!new_part->arg)
	{
		free(new_part);
		ft_free_split(words);
		return (NULL);
	}
	return (new_part);
}

static int	add_arg_to_cmd(t_command *curr, t_arg *new_part, int index,
	char **words)
{
	int		count;
	t_arg	**new_array;

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
	curr->cmd_parts[index]->was_expanded = true;
	return (RETURN_SUCCESS);
}

int	reparse_expanded_string(char *expanded, t_command *curr, bool was_expanded)
{
	char	**words;
	t_arg	*new_part;
	int		i;

	words = ft_split(expanded, ' ');
	if (!words)
		return (RETURN_FAILURE);
	i = 0;
	while (words[i])
	{
		new_part = create_arg(words[i], words);
		if (!new_part)
			return (RETURN_FAILURE);
		if (add_arg_to_cmd(curr, new_part, i, words) == RETURN_FAILURE)
			return (RETURN_FAILURE);
		curr->cmd_parts[i]->was_expanded = was_expanded;
		i++;
	}
	ft_free_split(words);
	return (RETURN_SUCCESS);
}
