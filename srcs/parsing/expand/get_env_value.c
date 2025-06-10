/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:56:37 by tarini            #+#    #+#             */
/*   Updated: 2025/06/10 17:59:35 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*get_env_value(char **env, const char *var_name)
{
	size_t	len;
	int		i;
	
	len = ft_strlen(var_name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var_name, len) == 0 && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return ("");
}
