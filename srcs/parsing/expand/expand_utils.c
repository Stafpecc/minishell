/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 18:08:58 by tarini            #+#    #+#             */
/*   Updated: 2025/07/17 15:25:55 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../../../libft/includes/libft.h"

static void	copy_strings_into(char *dest, char *s1, char *s2)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		dest[i + j] = s2[j];
		j++;
	}
	dest[i + j] = '\0';
}

char	*strjoin_and_free(char *s1, char *s2)
{
	char	*joined;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	joined = malloc(len1 + len2 + 1);
	if (!joined)
	{
		free(s1);
		return (NULL);
	}
	copy_strings_into(joined, s1, s2);
	free(s1);
	return (joined);
}

char	*handle_exit_code(char *result, int *i, t_utils *utils)
{
	(*i)++;
	result = append_exit_code(result, utils);
	if (!result)
		return (NULL);
	return (result);
}

char	*handle_env_var(char *result, int *i, char *input, char **env)
{
	result = append_env_var(result, input, i, env);
	if (!result)
		return (NULL);
	return (result);
}

char	*handle_other_cases(char *result, int *i, char *input)
{
	result = append_char(result, '$');
	if (!result)
		return (NULL);
	if (input[*i])
	{
		result = append_char(result, input[(*i)++]);
		if (!result)
			return (NULL);
	}
	return (result);
}
