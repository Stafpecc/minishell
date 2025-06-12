/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:35:58 by tarini            #+#    #+#             */
/*   Updated: 2025/06/12 09:55:02 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "exec.h"
#include "../../../libft/includes/libft.h"

static int	handle_token_error(t_token **tokens, t_utils *utils,
	t_command *head)
{
	if (*tokens && !is_redirect_or_pipe(*tokens))
		print_syntax_error((*tokens)->value, utils);
	else
		print_syntax_error("newline", utils);
	return (process_free_exit(head));
}

static int	ret_last_return_one(t_utils *utils)
{
	utils->last_return = 1;
	return (RETURN_FAILURE);
}

/*
Fonction qui :
- avance dans la liste de tokens pour traiter un heredoc après la redirection
	<< ;
- vérifie que le token suivant est valide (mot attendu) et gère les erreurs
	de syntaxe ;
- alloue et initialise la structure heredoc dans la commande courante avec
	la valeur du token ;
- traite les éventuelles quotes dans le token et ajoute l’argument à
	la commande ;
- marque le dernier argument comme finalisé et avance le token courant ;
- retourne RETURN_SUCCESS si tout s’est bien passé, sinon libère la mémoire
	et retourne une erreur.
*/
int	process_heredoc(t_token **tokens, t_command *curr, t_command *head, t_utils *utils)
{
	int		i;
	size_t	new_size;
	t_arg	**new_redirect_in;
	int		fd;

	(*tokens) = (*tokens)->next;
	if (!(*tokens) || !is_word_like(*tokens))
		return (handle_token_error(tokens, utils, head));
	i = 0;
	while (curr->redirect_in && curr->redirect_in[i])
		i++;
	new_size = sizeof(t_arg *) * (i + 2);
	new_redirect_in = realloc(curr->redirect_in, new_size);
	if (!new_redirect_in)
		return (process_free_exit(head));
	curr->redirect_in = new_redirect_in;
	curr->redirect_in[i] = malloc(sizeof(t_arg));
	if (!curr->redirect_in[i])
		return (process_free_exit(head));
	curr->redirect_in[i + 1] = NULL;
	curr->redirect_in[i]->arg = ft_strdup((*tokens)->value);
	if (!curr->redirect_in[i]->arg)
		return (process_free_exit(head));
	curr->redirect_in[i]->heredoc = true;
	curr->redirect_in[i]->append_redirect = false;
	process_quotes(*tokens, curr->redirect_in[i]);
	fd = here_doc(curr->redirect_in[i]->arg);
	if (fd < 0)
		return (ret_last_return_one(utils));
	curr->redirect_in[i]->fd = fd;
	*tokens = (*tokens)->next;
	return (RETURN_SUCCESS);
}


/*{a fix} : se renseigner sur la gestion des here-doc (<<) et envisager 
de stocker les here_doc dans un tableau, comme redirect_in et redirect_out, 
pour uniformiser le traitement et permettre la gestion de plusieurs Here_doc.*/
