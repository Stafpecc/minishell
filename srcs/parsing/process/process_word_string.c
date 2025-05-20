/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_word_string.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:37:21 by tarini            #+#    #+#             */
/*   Updated: 2025/05/20 10:27:26 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../../../libft/includes/libft.h"

int process_word_string(t_token **tokens, t_command *curr)
{
    t_arg *new_part;
    int i;
	int j;
	t_arg **new_array;

	i = 0;
    while (curr->cmd_parts && curr->cmd_parts[i])
        i++;
    new_part = malloc(sizeof(t_arg));
    if (!new_part)
        return (RETURN_FAILURE);
    new_part->arg = ft_strdup((*tokens)->value);
    if (!new_part->arg)
    {
        free(new_part);
        return (RETURN_FAILURE);
    }
    process_quotes(*tokens, new_part);
    new_array = malloc(sizeof(t_arg *) * (i + 2));
    if (!new_array)
    {
        free(new_part->arg);
        free(new_part);
        return (RETURN_FAILURE);
    }
	j = 0;
    while (j < i)
	{
        new_array[j] = curr->cmd_parts[j];
		j++;
	}
    new_array[i] = new_part;
    new_array[i + 1] = NULL;
    free(curr->cmd_parts);
    curr->cmd_parts = new_array;
    return (RETURN_SUCCESS);
}
