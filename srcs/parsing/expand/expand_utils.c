/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 18:08:58 by tarini            #+#    #+#             */
/*   Updated: 2025/07/17 16:49:58 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	copy_strings_into(char *dest, char *s1, char *s2)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		dest[i + j] = s2[j];
		j++;
	}
	dest[i + j] = '\0';
}

char	*strjoin_and_free(char *s1, char *s2)
{
	char	*joined;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	joined = malloc(len1 + len2 + 1);
	if (!joined)
	{
		free(s1);
		return (NULL);
	}
	copy_strings_into(joined, s1, s2);
	free(s1);
	return (joined);
}
