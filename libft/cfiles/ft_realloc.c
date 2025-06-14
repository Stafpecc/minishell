/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:36:44 by tarini            #+#    #+#             */
/*   Updated: 2025/06/14 16:41:26 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


// void *ft_realloc(void *ptr, size_t old_size, size_t new_size)
// {
//     void *new_ptr;
//     size_t size_to_copy;

//     if (new_size == 0)
//     {
//         free(ptr);
//         return NULL;
//     }
//     if (!ptr)
//         return malloc(new_size);
//     new_ptr = malloc(new_size);
//     if (!new_ptr)
//         return NULL;
//     if (old_size < new_size)
//         size_to_copy = old_size;
//     else
//         size_to_copy = new_size;
//     ft_memcpy(new_ptr, ptr, size_to_copy);
//     free(ptr);
//     return new_ptr;
// }

void	*ft_realloc(void *ptr, size_t new_size)
{
	void	*new_ptr;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (!ptr)
		return (malloc(new_size));
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	ft_memcpy(new_ptr, ptr, new_size);
	free(ptr);
	return (new_ptr);
}
