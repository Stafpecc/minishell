/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 18:41:41 by tarini            #+#    #+#             */
/*   Updated: 2024/11/19 17:15:30 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	unsigned int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (unsigned char)c)
			return ((char *)(&str[i]));
		i++;
	}
	if (!(unsigned char)c)
		return ((char *)(&str[i]));
	return (NULL);
}

/*
#include <stdio.h>

int main(void) {
	const char *str = "Hello, world!";
	char c = 'w';
	char *result = ft_strchr(str, c);

	if (result != NULL) {
		printf("'%c' find in %ld.\n", c, result - str);
	} else {
		printf("'%c' not find\n", c);
	}
	return 0;
}
*/