/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:42:46 by tarini            #+#    #+#             */
/*   Updated: 2024/11/18 20:41:19 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const char		*s;
	char			*d;
	size_t			count;

	s = (const char *)src;
	d = (char *)dest;
	if (dest == src)
		return (dest);
	if (d > s)
	{
		while (n--)
			d[n] = s[n];
	}
	else
	{
		count = 0;
		while (count < n)
		{
			d[count] = s[count];
			count++;
		}
	}
	return (dest);
}

/*
#include <stdio.h>

int main(void) {
	char src[] = "Hellooo";
	char dest[] = "Coucou";
	printf("Before : %s\n", dest);
	memmove(dest, src, 7);
	printf("After origin function : \n%s", dest);

	char ft_src[] = "Hellooo";
	char ft_dest[] = "Quiz";
	ft_memmove(ft_dest, ft_src, 5);
	printf("\nAfter 42 function : \n%s\n", ft_dest);

	return 0;
}

*/
