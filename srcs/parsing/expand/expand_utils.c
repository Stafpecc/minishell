/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 18:08:58 by tarini            #+#    #+#             */
/*   Updated: 2025/07/21 10:45:28 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

static void	handle_dollar_number_sequence(t_expand_ctx *ctx, bool *first_time)
{
	char	c;
	int		index;

	c = ctx->input[ctx->i + 1];
	if (c >= '0' && c <= '9')
	{
		index = c - '0';
		ctx->i += 2;
		if (c == '0' && ctx->utils->av[index] != NULL)
			ctx->result = strjoin_and_free(ctx->result,
					ft_strdup(ctx->utils->av[index]), true);
		else
			ctx->result = strjoin_and_free(ctx->result, ft_strdup(""), true);
		*first_time = false;
	}
}

static void	expand_variables_loop(t_expand_ctx *ctx)
{
	bool	first_time;
	char	current;

	first_time = true;
	while (ctx->input[ctx->i])
	{
		current = ctx->input[ctx->i];
		if (current == '$')
		{
			if (first_time && ctx->input[ctx->i + 1])
			{
				handle_dollar_number_sequence(ctx, &first_time);
				if (!first_time)
					continue ;
			}
			first_time = false;
			ctx->i++;
			process_dollar_sequence(ctx);
		}
		else
		{
			ctx->result = append_char(ctx->result, current);
			ctx->i++;
		}
	}
}

char	*expand_variables_utils(t_expand_ctx *ctx)
{
	if (!ctx->result)
		ctx->result = ft_strdup("");
	expand_variables_loop(ctx);
	return (ctx->result);
}
