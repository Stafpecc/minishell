/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:58:15 by tarini            #+#    #+#             */
/*   Updated: 2025/07/17 15:18:55 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../../../libft/includes/libft.h"

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
	if (!var_name)
		return (NULL);
	value = get_env_value(env, var_name);
	free(var_name);
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

static char	*expand_variables_utils(int i, char *result,
	t_utils *utils, char *input)
{
	while (input[i])
	{
		if (input[i] == '$')
		{
			i++;
			if (input[i] == '?')
				result = handle_exit_code(result, &i, utils, input);
			else if (ft_isalnum(input[i]) || input[i] == '_')
				result = handle_env_var(result, &i, input, utils->env);
			else
				result = handle_other_cases(result, &i, input);
			if (!result)
				return (NULL);
		}
		else
		{
			result = append_char(result, input[i++]);
			if (!result)
				return (NULL);
		}
	}
	return (result);
}

char	*expand_variables(char *input, t_utils *utils)
{
	int		i;
	char	*result;

	i = 0;
	result = ft_strdup("");
	if (!result)
		return (result);
	result = expand_variables_utils(i, result, utils, input);
	return (result);
}
