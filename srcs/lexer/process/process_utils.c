/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 16:53:34 by stafpec           #+#    #+#             */
/*   Updated: 2025/07/20 16:57:54 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "../../../libft/includes/libft.h"

size_t	find_simple_token_end(const char *input, size_t start)
{
	size_t	i;

	i = start;
	while (input[i]
		&& !ft_isspace(input[i])
		&& input[i] != '\''
		&& input[i] != '"'
		&& input[i] != '|'
		&& input[i] != '<'
		&& input[i] != '>')
	{
		i++;
	}
	return (i);
}
