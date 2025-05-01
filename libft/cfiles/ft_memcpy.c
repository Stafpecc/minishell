/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 12:45:52 by tarini            #+#    #+#             */
/*   Updated: 2024/11/29 15:13:40 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	count;

	if (!dest && !src && n > 0)
		return (NULL);
	count = 0;
	while (count < n)
	{
		((unsigned char *)dest)[count] = ((const unsigned char *)src)[count];
		count++;
	}
	return (dest);
}

/*
#include <stdio.h>

int main(void) {
	char src[] = "B";
	char dest[] = "0";
	printf("Before : %s\n", dest);
	memcpy(dest, src, 10);
	printf("\nAfter origin function : \n%s", dest);

	char ft_src[] = "B";
	char ft_dest[] = "0";
	ft_memcpy(ft_dest, ft_src, 10);
	printf("\nAfter 42 function : \n%s\n", ft_dest);

	return 0;
}
*/