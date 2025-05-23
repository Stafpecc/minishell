/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_word_string.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:46:05 by tarini            #+#    #+#             */
/*   Updated: 2025/05/23 14:55:30 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int process_word_or_string(const char *input, size_t *i, t_token **head)
{
	if (input[*i] == '"' || input[*i] == '\'')
		return (process_string(input, i, head));
	else
		return (process_word(input, i, head));
}