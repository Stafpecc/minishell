/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 15:55:16 by tarini            #+#    #+#             */
/*   Updated: 2024/11/29 15:14:42 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

unsigned int	ft_strlcat(char *dest, const char *src, unsigned int size)
{
	size_t	dstlen;
	size_t	srclen;
	size_t	i;

	dstlen = ft_strlen(dest);
	srclen = ft_strlen(src);
	if (size <= dstlen)
		return (size + srclen);
	i = -1;
	while (src[++i] != '\0' && (dstlen + i) < (size - 1))
		dest[dstlen + i] = src[i];
	dest[dstlen + i] = '\0';
	return (dstlen + srclen);
}

/*
#include <stdio.h>

int	main(void) {
	char dest[5] = "Hello";
	char src[3] = "toi";
	printf("%d\n", ft_strlcat(dest,src, 4));
	printf("%s\n", dest);
	return (0);
}
*/