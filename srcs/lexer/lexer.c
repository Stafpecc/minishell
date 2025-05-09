

#include <stdio.h>

#include "lexer.h"

t_token *lexer(const char *input)
{
	t_token *head;
	size_t i;

	if (!input || !*input)
		return (NULL);
	i = 0;
	head = NULL;
	while (input[i])
	{
		if (ft_isspace(input[i]))
			i++;
		else if (ft_strchr(">|<", input[i]))
		{
			
		}
		else if (input[i] == '|')
		{
			if (!safe_add_token(&head, TOK_PIPE, "|"))
				return (NULL);
			i++;
		}
		else if (input[i] == '>')
		{
			if (!safe_add_token(&head, TOK_REDIRECT_OUT, ">"))
				return (NULL);
			i++;
		}
		else if (input[i] == '<')
		{
			if (!safe_add_token(&head, TOK_REDIRECT_IN, "<"))
				return (NULL);
			i++;
		}
		else if (input[i] == '"' || input[i] == '\'')
		{
			quote = input[i++];
			start = i;
			while (input[i] && input[i] != quote)
				i++;
			str = ft_strndup(input + start, i - start);
			if (!str || !safe_add_token(&head, TOK_STRING, str))
			{
				free(str);
				return (NULL);
			}
			free(str);
			if (input[i] == quote)
				i++;
		}
		else
		{
			start = i;
			while (input[i] && !ft_isspace(input[i]) && input[i] != '|' && input[i] != '>' && input[i] != '<')
				i++;
			word = ft_strndup(input + start, i - start);
			if (!word || !safe_add_token(&head, TOK_WORD, word))
			{
				free(word);
				return (NULL);
			}
			free(word);
		}
	}
	if (!add_token(&head, TOK_END, ""))
		return (NULL);
	return (head);
}