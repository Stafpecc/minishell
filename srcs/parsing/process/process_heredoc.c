/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:35:58 by tarini            #+#    #+#             */
/*   Updated: 2025/06/04 16:55:26 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../../../libft/includes/libft.h"

/*
Fonction qui :
- avance dans la liste de tokens pour traiter un heredoc après la redirection << ;
- vérifie que le token suivant est valide (mot attendu) et gère les erreurs de syntaxe ;
- alloue et initialise la structure heredoc dans la commande courante avec la valeur du token ;
- traite les éventuelles quotes dans le token et ajoute l’argument à la commande ;
- marque le dernier argument comme finalisé et avance le token courant ;
- retourne RETURN_SUCCESS si tout s’est bien passé, sinon libère la mémoire et retourne une erreur.
*/
int process_heredoc(t_token **tokens, t_command *curr, t_command *head, t_utils *utils)
{
	(*tokens) = (*tokens)->next;
	if (!(*tokens) || !is_word_like(*tokens))
	{
		if (*tokens && !is_redirect_or_pipe(*tokens))
			print_syntax_error((*tokens)->value, utils);
		else
			print_syntax_error("newline", utils);
		return (process_free_exit(head));
	}
	if (!curr->heredoc)
	{
		curr->heredoc = malloc(sizeof(t_arg));
		if (!curr->heredoc)
			return (process_free_exit(head));
	}
	curr->heredoc->arg = ft_strdup((*tokens)->value);
	if (!curr->heredoc->arg)
		return (process_free_exit(head));
	process_quotes(*tokens, curr->heredoc);
	(*tokens) = (*tokens)->next;
	return (RETURN_SUCCESS);
}

/*{a fix} : se renseigner sur la gestion des here-doc (<<) et envisager 
de stocker les here_doc dans un tableau, comme redirect_in et redirect_out, 
pour uniformiser le traitement et permettre la gestion de plusieurs Here_doc.*/
