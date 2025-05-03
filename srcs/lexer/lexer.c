/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:26:34 by tarini            #+#    #+#             */
/*   Updated: 2025/05/03 11:41:55 by stafpec          ###   ########.fr       */
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
	{
		free(token);
		return (NULL);
	}
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

static int safe_add_token(t_token **head, t_token_type type, const char *value)
{
	t_token *new_token = create_token(type, value);
	if (!new_token)
	{
		free_tokens(*head);
		return (0);
	}
	add_token(head, new_token);
	return (1);
}

void free_tokens(t_token *head)
{
	t_token *tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->value);
		free(tmp);
	}
}

t_token *lexer(const char *input)
{
	t_token *head = NULL;
	size_t i = 0;
	char quote;
	size_t start;
	char *str;
	char *word;

	if (!input || !*input)
		return (NULL);

	while (input[i])
	{
		if (ft_isspace(input[i]))
			i++;
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

	if (!safe_add_token(&head, TOK_END, ""))
		return (NULL);

	return head;
}

int has_word_token(t_token *head)
{
	while (head)
	{
		if (head->type == TOK_WORD || head->type == TOK_STRING)
			return (1);
		head = head->next;
	}
	return (0);
}
