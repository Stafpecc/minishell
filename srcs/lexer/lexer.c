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
		if (!process_token(input, &i, &head))
			return (NULL);
	}
	if (!add_token(&head, TOK_END, ""))
		return (NULL);
	return (head);
}