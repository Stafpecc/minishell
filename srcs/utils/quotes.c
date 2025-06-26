/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:21:01 by stafpec           #+#    #+#             */
/*   Updated: 2025/06/26 13:13:42 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "exec.h"

static char	*strjoin_free(char *s1, const char *s2)
{
	char	*joined;

	if (!s1)
		return (ft_strdup(s2));
	joined = ft_strjoin(s1, s2);
	free(s1);
	return (joined);
}

static char	*handle_unexpected_eof(char *line, char quote)
{
	ft_printfd("minishell: unexpected EOF while looking for \
matching `%c'\n", quote);
	ft_printfd("minishell: syntax error: unexpected end of file\n");
	free(line);
	return (ft_strdup(""));
}

static char	*read_first_line(void)
{
	char	*line;

	g_interrupted = 0;
	signal(SIGINT, sigint_handler);
	line = readline("minishell> ");
	if (g_interrupted)
	{
		g_interrupted = 0;
		free(line);
		return (ft_strdup(""));
	}
	if (!line)
		return (NULL);
	return (line);
}

static char	*read_until_quotes_closed(char *line, char quote)
{
	char	*tmp;

	while (quote)
	{
		g_interrupted = 0;
		tmp = readline("> ");
		if (g_interrupted)
		{
			g_interrupted = 0;
			free(tmp);
			free(line);
			return (ft_strdup(""));
		}
		if (!tmp)
			return (handle_unexpected_eof(line, quote));
		line = strjoin_free(line, "\n");
		line = strjoin_free(line, tmp);
		quote = quote_not_closed(line);
	}
	return (line);
}

char	*read_input_with_quotes(void)
{
	char	*line;
	char	quote;

	line = read_first_line();
	if (!line)
		return (NULL);
	quote = quote_not_closed(line);
	return (read_until_quotes_closed(line, quote));
}
