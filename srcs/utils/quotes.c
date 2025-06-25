/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:21:01 by stafpec           #+#    #+#             */
/*   Updated: 2025/06/25 18:46:54 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "exec.h"

char	quote_not_closed(const char *str)
{
	char	quote = 0;
	int		i = 0;

	while (str[i])
	{
		if ((str[i] == '"' || str[i] == '\'') && quote == 0)
			quote = str[i];
		else if (str[i] == quote)
			quote = 0;
		i++;
	}
	return (quote);
}

static char	*strjoin_free(char *s1, const char *s2)
{
	char	*joined;
	
	if (!s1)
		return (ft_strdup(s2));
	joined = ft_strjoin(s1, s2);
	free(s1);
	return (joined);
}

char *read_input_with_quotes(void)
{
    char *line = NULL;
    char *tmp = NULL;
    char quote;

    g_interrupted = 0;
    signal(SIGINT, sigint_handler);

    line = readline("minishell> ");
    if (g_interrupted)
    {
        g_interrupted = 0;
        free(line);
        return ft_strdup("");
    }
    if (!line)
        return NULL;

    while ((quote = quote_not_closed(line)))
    {
        g_interrupted = 0;
        tmp = readline("> ");
        if (g_interrupted)
        {
            g_interrupted = 0;
            free(tmp);
            free(line);
            return ft_strdup("");
        }
        if (!tmp)
        {
            ft_printfd("minishell: unexpected EOF while looking for matching `%c'\n", quote);
            ft_printfd("minishell: syntax error: unexpected end of file\n");
            free(line);
            return ft_strdup("");
        }
        line = strjoin_free(line, "\n");
        line = strjoin_free(line, tmp);
    }
    return line;
}
