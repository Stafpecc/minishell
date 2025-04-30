/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:22:27 by tarini            #+#    #+#             */
/*   Updated: 2024/11/17 13:46:28 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	count;

	count = -1;
	while (++count < n)
		((char *)s)[count] = 0;
}

/*
#include <stdio.h>
#include <stdlib.h>

int main() {
	int i_array[10]   = {7, 7, 7, 7, 7, 7, 7, 7, 7, 7};

	size_t count = -1;
	bzero(i_array, (6 * sizeof(int)));

	while(++count < 10)
		printf("%lu: %d\n", (count + !), i_array[count]);
	
	printf("\n");

	int ft_i_array[10]   = {7, 7, 7, 7, 7, 7, 7, 7, 7, 7};

	size_t ft_count = -1;
	ft_bzero(ft_i_array, (6 * sizeof(int)));
 
	while(++ft_count < 10)
		printf("%lu: %d\n", (ft_count + 1), ft_i_array[ft_count]);

	return 0;
}
*/
