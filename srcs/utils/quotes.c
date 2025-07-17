/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 14:46:11 by stafpec           #+#    #+#             */
/*   Updated: 2025/07/17 13:41:10 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

//#include "parsing.h"
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

static char	*read_first_line(t_utils *utils)
{
	char	*line;

	g_interrupted = 0;
	signal(SIGINT, sig_handler);
	line = readline("minishell> ");
	if (g_interrupted)
	{
		utils->last_return = 130;
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

char	*read_input_with_quotes(t_utils *utils)
{
	char	*line;
	char	quote;

	line = read_first_line(utils);
	if (!line)
		return (NULL);
	quote = quote_not_closed(line);
	return (read_until_quotes_closed(line, quote));
}
