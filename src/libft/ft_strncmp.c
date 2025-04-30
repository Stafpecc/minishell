/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:22:04 by stafpec           #+#    #+#             */
/*   Updated: 2024/11/17 13:46:45 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = -1;
	while (++i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		if (s1[i] == '\0')
			return (0);
	}
	return (0);
}

/*
int main(void)
{
	char s1[] = "hello";
	char s2[] = "helli";
	int result = ft_strncmp(s1, s2, 5);

	if (result == 0)
		printf("The strings are equal.\n");
	else if (result < 0)
		printf("s1 is less than s2.\n");
	else
		printf("s1 is greater than s2.\n");

	return 0;
}
*/
