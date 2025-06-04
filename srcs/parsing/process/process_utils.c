/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:58:07 by tarini            #+#    #+#             */
/*   Updated: 2025/06/04 12:54:56 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "parsing.h"
#include "../../../libft/includes/libft.h"

/*
fonction qui :
- libère toute la liste de commandes passée en argument ;
- retourne toujours RETURN_FAILURE pour indiquer une erreur ou un arrêt.
*/
int process_free_exit(t_command *head)
{
	free_commands(head);
	return (RETURN_FAILURE);
}

/*
fonction qui :
- vérifie si un token est considéré comme un mot ou une chaîne valide dans le parsing ;
- retourne true si le type du token est un mot simple ou une chaîne entre quotes, false sinon.
*/
bool is_word_like(t_token *token)
{
	return (token->type == TOK_WORD ||
			token->type == TOK_STRING ||
			token->type == TOK_SINGLE_QUOTES ||
			token->type == TOK_DOUBLE_QUOTES);
}

/*
fonction qui :
- vérifie si un token correspond à une redirection (<<, >>, <, >) ou à un pipe (|) ;
- retourne RETURN_SUCCESS si c’est le cas, sinon RETURN_FAILURE.
*/
int is_redirect_or_pipe(t_token *token)
{
	if (!token)
		return (RETURN_FAILURE);
	if (ft_strcmp(token->value, "<<") == 0)
		return (RETURN_SUCCESS);
	if (ft_strcmp(token->value, ">>") == 0)
		return (RETURN_SUCCESS);
	if (ft_strcmp(token->value, "<") == 0)
		return (RETURN_SUCCESS);
	if (ft_strcmp(token->value, ">") == 0)
		return (RETURN_SUCCESS);
	if (ft_strcmp(token->value, "|") == 0)
		return (RETURN_SUCCESS);
	return (RETURN_FAILURE);
}

