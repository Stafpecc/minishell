/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_handle_single.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 16:37:16 by stafpec           #+#    #+#             */
/*   Updated: 2025/07/20 16:50:53 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parsing.h"
#include "../../../libft/includes/libft.h"

char	*extract_quoted_part(const char *input, size_t *i, char quote)
{
	size_t	start;
	size_t	j;
	char	*part;

	start = *i + 1;
	j = start;
	while (input[j] && input[j] != quote)
		j++;
	if (input[j] != quote)
		return (NULL);
	part = ft_substr(input, start, j - start);
	if (!part)
		return (NULL);
	*i = j + 1;
	return (part);
}

char	*concat_buffer_part(char *buffer, char *part)
{
	char	*tmp;

	tmp = ft_strjoin(buffer, part);
	free(buffer);
	free(part);
	if (!tmp)
		return (NULL);
	return (tmp);
}
