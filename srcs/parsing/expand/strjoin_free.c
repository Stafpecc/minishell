/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:42:57 by stafpec           #+#    #+#             */
/*   Updated: 2025/07/21 10:44:05 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../libft/includes/libft.h"

#include <stdbool.h>

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

char	*strjoin_and_free(char *s1, char *s2, bool free_s2)
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
		if (free_s2)
			free(s2);
		return (NULL);
	}
	copy_strings_into(joined, s1, s2);
	free(s1);
	if (free_s2)
		free(s2);
	return (joined);
}
