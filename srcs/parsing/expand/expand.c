/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:58:15 by tarini            #+#    #+#             */
/*   Updated: 2025/07/21 10:12:51 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*append_exit_code(char *result, t_utils *utils)
{
	char	*exit_code;
	char	*tmp;

	exit_code = ft_itoa(utils->last_return);
	tmp = strjoin_and_free(result, exit_code, false);
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
	if (!value)
		tmp = strjoin_and_free(result, "", false);
	else
		tmp = strjoin_and_free(result, value, false);
	return (tmp);
}

char	*append_char(char *result, char c)
{
	char	buf[2];
	char	*tmp;

	buf[0] = c;
	buf[1] = '\0';
	tmp = strjoin_and_free(result, buf, false);
	return (tmp);
}

char	*expand_variables(char *input, t_utils *utils, bool *was_expanded)
{
	t_expand_ctx	ctx;

	ctx.input = input;
	ctx.utils = utils;
	ctx.was_expanded = was_expanded;
	ctx.i = 0;
	ctx.result = ft_strdup("");
	if (!ctx.result)
		return (NULL);
	ctx.result = expand_variables_utils(&ctx);
	if (!ctx.result)
		return (NULL);
	was_expanded = ctx.was_expanded;
	if (ctx.result[0] == '\0')
	{
		free(ctx.result);
		return (ft_strdup(""));
	}
	return (ctx.result);
}
