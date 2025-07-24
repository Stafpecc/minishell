/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 01:55:30 by stafpec           #+#    #+#             */
/*   Updated: 2024/11/29 15:14:16 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_count(const char *str, char sep)
{
	int	count;
	int	in_substring;

	count = 0;
	in_substring = 0;
	while (*str)
	{
		if (*str == sep)
			in_substring = 0;
		else if (!in_substring)
		{
			count++;
			in_substring = 1;
		}
		str++;
	}
	return (count);
}

static void	free_split(char **result, size_t count)
{
	while (count > 0)
		free(result[--count]);
	free(result);
}

static const char	*find_next_segment(const char *str, char sep, int *length)
{
	while (*str && *str == sep)
		str++;
	*length = 0;
	while (str[*length] && str[*length] != sep)
		(*length)++;
	if (*length > 0)
		return (str);
	return (NULL);
}

char	**ft_split(const char *str, char sep)
{
	char	**result;
	int		segment_length;
	size_t	i;

	if (!str)
		return (NULL);
	result = malloc(sizeof(char *) * (ft_count(str, sep) + 1));
	if (!result)
		return (NULL);
	i = 0;
	str = find_next_segment(str, sep, &segment_length);
	while (str)
	{
		result[i] = ft_substr(str, 0, segment_length);
		if (!result[i])
		{
			free_split(result, i);
			return (NULL);
		}
		str += segment_length;
		i++;
		str = find_next_segment(str, sep, &segment_length);
	}
	result[i] = NULL;
	return (result);
}

/*
#include <stdio.h>

int	main(void)
{
	char	str[] = "Bonjour ! Je suis content, mais je dois faire split.";
	char	charset[] = "!,.";
	char	**result = ft_split(str, charset);
	int	i = 0;
	
	printf("nombre de str : %d\n", ft_count(str, charset));
	while (result[i])
	{
		printf("\n%s", result[i]);
		i++;
	}
	free(result);
	return (0);
}
*/
