/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:58:15 by tarini            #+#    #+#             */
/*   Updated: 2025/06/10 18:08:39 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*append_exit_code(char *result, t_utils *utils)
{
	char	*exit_code;
	char	*tmp;

	exit_code = ft_itoa(utils->last_return);
	tmp = strjoin_and_free(result, exit_code);
	free(exit_code);
	return (tmp);
}

char	*append_env_var(char *result, char *input, int *i, char **env)
{
	int		start;
	char	*var_name;
	char	*value;
	char	*tmp;

	start = *i;
	while (ft_isalnum(input[*i]) || input[*i] == '_')
		(*i)++;
	var_name = ft_strndup(&input[start], *i - start);
	value = get_env_value(env, var_name);
	free(var_name);
	tmp = strjoin_and_free(result, value);
	return (tmp);
}

char	*append_char(char *result, char c)
{
	char	buf[2];
	char	*tmp;

	buf[0] = c;
	buf[1] = '\0';
	tmp = strjoin_and_free(result, buf);
	return (tmp);
}
