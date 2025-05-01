/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:26:34 by tarini            #+#    #+#             */
/*   Updated: 2025/05/01 18:39:42 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "lexer.h"
#include "../../libft/includes/libft.h"

static t_token *create_token(t_token_type type, const char *value)
{
	t_token *token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = ft_strdup(value);
	if (!token->value)
		return (NULL);
	token->next = NULL;
	return (token);
}

static void add_token(t_token **head, t_token *new_token)
{
	t_token *curr;
	
	if (!*head)
		*head = new_token;
	else
	{
		curr = *head;
		while (curr->next)
			curr = curr->next;
		curr->next = new_token;
	}
}

void free_tokens(t_token *head)
{
	t_token *tmp;

	while (head) {
		tmp = head;
		head = head->next;
		free(tmp->value);
		free(tmp);
	}
}

t_token *lexer(const char *input)
{
	t_token *head;
	size_t i;
	char quote;
	size_t start;
	char *str;
	char *word;

	i = 0;
	head = NULL;

	while (input[i]) {
		if (ft_isspace(input[i]))
			i++;
		else if (input[i] == '|')
		{
			add_token(&head, create_token(TOK_PIPE, "|"));
			i++;
		}
		else if (input[i] == '>')
		{
			add_token(&head, create_token(TOK_REDIRECT_OUT, ">"));
			i++;
		}
		else if (input[i] == '<')
		{
			add_token(&head, create_token(TOK_REDIRECT_IN, "<"));
			i++;
		}
		else if (input[i] == '"' || input[i] == '\'')
		{
			quote = input[i++];
			start = i;
			while (input[i] && input[i] != quote)
				i++;
			str = ft_strndup(input + start, i - start);
			add_token(&head, create_token(TOK_STRING, str));
			free(str);
			if (input[i] == quote)
				i++;
		}
		else
		{
			start = i;
			while (input[i] && !ft_isspace(input[i]) && input[i] != '|'
				&& input[i] != '>' && input[i] != '<')
				i++;
			word = ft_strndup(input + start, i - start);
			add_token(&head, create_token(TOK_WORD, word));
			free(word);
		}
	}
	add_token(&head, create_token(TOK_END, ""));
	return (head);
}

void print_tokens(t_token *head) // DEBUG
{
	while (head)
	{
		printf("token: type=%d, value='%s'\n", head->type, head->value);
		head = head->next;
	}
}
