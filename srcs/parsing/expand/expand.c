/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:58:15 by tarini            #+#    #+#             */
/*   Updated: 2025/07/19 21:02:31 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	*append_exit_code(char *result, t_utils *utils)
{
	char	*exit_code;
	char	*tmp;

	exit_code = ft_itoa(utils->last_return);
	tmp = strjoin_and_free(result, exit_code);
	free(exit_code);
	return (tmp);
}

static char	*append_env_var(char *result, char *input, int *i, char **env)
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
	if (!value)
		tmp = strjoin_and_free(result, "");
	else
		tmp = strjoin_and_free(result, value);
	return (tmp);
}

static char	*append_char(char *result, char c)
{
	char	buf[2];
	char	*tmp;

	buf[0] = c;
	buf[1] = '\0';
	tmp = strjoin_and_free(result, buf);
	return (tmp);
}

static char	*expand_variables_utils(int i, char *result, t_utils *utils,
	char *input, bool *was_expanded)
{
	while (input[i])
	{
		if (input[i] == '$')
		{
			i++;
			if (input[i] == '?')
			{
				i++;
				result = append_exit_code(result, utils);
				*was_expanded = true;
			}
			else if (ft_isalnum(input[i]) || input[i] == '_')
			{
				result = append_env_var(result, input, &i, utils->env);
				*was_expanded = true;
			}
			else
			{
				result = append_char(result, '$');
				if (input[i])
					result = append_char(result, input[i++]);
			}
		}
		else
			result = append_char(result, input[i++]);
	}
	return (result);
}

char	*expand_variables(char *input, t_utils *utils, bool *was_expanded)
{
	int		i;
	char	*result;

	i = 0;
	result = ft_strdup("");
	if (!result)
		return (NULL);
	result = expand_variables_utils(i, result, utils, input, was_expanded);
	if (!result)
		return (NULL);
	if (result[0] == '\0')
	{
		free(result);
		return (ft_strdup(""));
	}
	return (result);
}
