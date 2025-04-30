/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:42:49 by tarini            #+#    #+#             */
/*   Updated: 2024/11/19 15:54:23 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	count;

	count = -1;
	while (++count < n)
		((char *)s)[count] = c;
	return (s);
}

/*
#include <stdio.h>

int main(void) {
	char buffer[] = "Shhhhht ! Sorry, I had no idea";
	printf("Before                 : %s\n", buffer);
	memset(buffer, '*', 7);
	printf("After origin function  : %s\n", buffer);
	char ft_buffer[] = "Shhhhht ! Sorry, I had no idea";
	ft_memset(buffer, '*', 7);
	printf("After 42 function      : %s\n", buffer);
}
*/