/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 18:08:58 by tarini            #+#    #+#             */
/*   Updated: 2025/07/21 09:50:07 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

char	*strjoin_and_free(char *s1, char *s2, bool free_s2)
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
		if (free_s2)
			free(s2);
		return (NULL);
	}
	copy_strings_into(joined, s1, s2);
	free(s1);
	if (free_s2)
		free(s2);
	return (joined);
}

static void	process_dollar_sequence(t_expand_ctx *ctx)
{
	if (ctx->input[ctx->i] == '?')
	{
		ctx->i++;
		ctx->result = append_exit_code(ctx->result, ctx->utils);
		*(ctx->was_expanded) = true;
	}
	else if (ft_isalnum(ctx->input[ctx->i]) || ctx->input[ctx->i] == '_')
	{
		ctx->result = append_env_var(ctx->result,
				ctx->input, &ctx->i, ctx->utils->env);
		*(ctx->was_expanded) = true;
	}
	else
	{
		ctx->result = append_char(ctx->result, '$');
		if (ctx->input[ctx->i])
			ctx->result = append_char(ctx->result, ctx->input[ctx->i++]);
	}
}

char	*expand_variables_utils(t_expand_ctx *ctx)
{
	bool	first_time = true;
	char	c;
	int		index;

	if (!ctx->result)
		ctx->result = ft_strdup("");
	while (ctx->input[ctx->i])
	{
		if (ctx->input[ctx->i] == '$')
		{
			if (first_time && ctx->input[ctx->i + 1])
			{
				c = ctx->input[ctx->i + 1];
				if (c >= '0' && c <= '9')
				{
					index = c - '0';
					ctx->i += 2;
					if (c == '0' && ctx->utils->av[index] != NULL)
					{
						ctx->result = strjoin_and_free(ctx->result,
							ft_strdup(ctx->utils->av[index]), true);
					}
					else
					{
						ctx->result = strjoin_and_free(ctx->result,
							ft_strdup(""), true);
					}
					first_time = false;
					continue;
				}
			}
			first_time = false;
			ctx->i++;
			process_dollar_sequence(ctx);
		}
		else
		{
			ctx->result = append_char(ctx->result, ctx->input[ctx->i]);
			ctx->i++;
		}
	}
	return (ctx->result);
}
