/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 13:00:52 by tarini            #+#    #+#             */
/*   Updated: 2024/11/29 15:12:16 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static size_t	ft_numlen(int n)
{
	size_t	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

void	sign(char *str, unsigned int *num, size_t *start, int n)
{
	if (n < 0)
	{
		str[0] = '-';
		*num = -n;
		*start = 1;
	}
	else
	{
		*num = n;
		*start = 0;
	}
}

char	*ft_itoa(int n)
{
	char			*str;
	size_t			len;
	unsigned int	num;
	size_t			start;

	len = ft_numlen(n);
	str = ft_calloc((len + 1), sizeof(char));
	if (!str)
		return (NULL);
	sign(str, &num, &start, n);
	while (len > start)
	{
		str[len - 1] = (num % 10) + '0';
		num /= 10;
		len--;
	}
	return (str);
}

/*
#include <stdio.h>

int	main(int ac, char **av) {
	int	test;

	(void)ac;
	test = ft_atoi(av[1]);
	printf("%s", ft_itoa(test));
	return (0);
}
*/