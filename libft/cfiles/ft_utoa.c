/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:49:41 by ldevoude          #+#    #+#             */
/*   Updated: 2025/07/17 13:49:54 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static char	*convert(long n, int i, char *result, char *buff)
{
	int	length;
	int	j;

	length = i;
	j = i;
	while (n > 0)
	{
		buff[i] = n % 10 + 48;
		n /= 10;
		i++;
	}
	i--;
	while (i != length - 1)
	{
		result[j++] = buff[i--];
	}
	result[j] = 0;
	return (result);
}

static char	*count_for_malloc(long *integer, int *is_negative)

{
	char	*result;
	int		count;
	long	buff;

	count = 0;
	if (*is_negative == 1)
		count++;
	if (*integer < 0)
	{
		(*is_negative) = 1;
		(*integer) = (*integer) * -1;
		count++;
	}
	buff = *integer;
	while (buff > 0)
	{
		buff /= 10;
		count++;
	}
	result = malloc((count + 1) * sizeof(char));
	if (!result)
		return (NULL);
	if (*is_negative > 0)
		result[0] = '-';
	return (result);
}

char	*ft_utoa(unsigned int n)
{
	char	*result;
	int		i;
	char	*buff;
	long	ln;

	i = 0;
	ln = n;
	if (n == 0)
	{
		result = ft_strdup("0");
		if (!result)
			return (NULL);
		return (result);
	}
	buff = count_for_malloc(&ln, &i);
	if (!buff)
		return (NULL);
	result = count_for_malloc(&ln, &i);
	if (!result)
		return (free(buff), NULL);
	result = convert(ln, i, result, buff);
	if (!result)
		return (free(buff), NULL);
	return (free(buff), result);
}
