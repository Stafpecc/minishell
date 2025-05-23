/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:51:27 by tarini            #+#    #+#             */
/*   Updated: 2025/05/23 14:56:39 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../../libft/includes/libft.h"

#include <stdlib.h>
#include <stdio.h>

char *get_env_value(const char *key, char **env)
{
	size_t len = ft_strlen(key);
	int i = 0;

	while (env[i])
	{
		if (ft_strncmp(env[i], key, len) == 0 && env[i][len] == '=')
			return env[i] + len + 1;
		i++;
	}
	return NULL;
}

char *expand_string(const char *input, char **env, int last_status)
{
	char *result = malloc(1);
	size_t res_len = 0;
	int i = 0;
	int in_squote = 0;
	int in_dquote = 0;

	result[0] = '\0';

   
}
