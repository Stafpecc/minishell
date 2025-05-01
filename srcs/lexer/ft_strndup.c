/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:39:31 by tarini            #+#    #+#             */
/*   Updated: 2025/05/01 16:53:03 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strndup(const char *s, size_t n)
{
	size_t len;
	char *dup;
	size_t i;

	i = 0;
	len = 0;
	if (!s)
		return (NULL);
	while (s[len] && len < n)
		len++;
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[len] = '\0';
	return (dup);
}