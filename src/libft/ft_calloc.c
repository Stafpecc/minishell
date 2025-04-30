/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:18:07 by tarini            #+#    #+#             */
/*   Updated: 2024/11/21 16:27:24 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>

void	*ft_calloc(size_t elementCount, size_t elementSize)
{
	void	*ptr;
	size_t	product;

	if (elementCount == 0 || elementSize == 0)
		return (malloc(0));
	if (elementCount > SIZE_MAX / elementSize)
		return (NULL);
	product = elementCount * elementSize;
	ptr = malloc(product);
	if (!ptr)
		return (ptr);
	ft_bzero(ptr, product);
	return (ptr);
}

/*
#include <stdio.h>          
#include <stdlib.h>
#include <assert.h>

int main() {
	
	int i;
	int *pointer = (int *) calloc(10, sizeof(int));

	assert(pointer != NULL);
	for ( i=0; i<10-1; i++ ) {
		pointer[i] = i;
	}
	for (i = 0; i < 10; i++) {
		printf("%d ", pointer[i]);
	}
	printf("\n");
	free(pointer);
	return 0;
}
*/