/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:34:25 by tarini            #+#    #+#             */
/*   Updated: 2025/06/12 14:50:26 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
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

/*
Fonction qui :
- avance au token suivant après une redirection d’entrée (<) ;
- vérifie que ce token est un mot valide, sinon affiche une erreur de syntaxe ;
- alloue ou utilise le tableau redirect_in pour stocker l’argument de la
	redirection à la position statique location_of_the_table ;
- copie l’argument, traite les quotes, ajoute l’argument à cmd_parts, marque
	le dernier argument comme final ;
- avance le token et incrémente location_of_the_table ;
- retourne RETURN_SUCCESS ou libère et retourne une erreur en cas d’échec.
*/
int	process_redirect_in(t_token **tokens, t_command *curr, t_command *head,
	t_utils *utils)
{
	int		i;
	size_t	new_size;
	t_arg	**new_redirect_in;

	i = 0;
	(*tokens) = (*tokens)->next;
	if (!(*tokens) || !is_word_like(*tokens))
		return (handle_token_error(tokens, utils, head));
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
	curr->redirect_in[i]->heredoc = false;
	curr->redirect_in[i]->append_redirect = false;
	if (!curr->redirect_in[i]->arg)
		return (process_free_exit(head));
	process_quotes(*tokens, curr->redirect_in[i]);
	return (RETURN_SUCCESS);
}

/*
Fonction qui :
- avance au token suivant après une redirection de sortie (>) ;
- vérifie la validité du token, affiche une erreur si nécessaire ;
- alloue ou utilise le tableau redirect_out avec un index statique
	location_of_the_table pour stocker l’argument ;
- copie l’argument, traite les quotes, ajoute à cmd_parts, marque le
	dernier argument comme final ;
- incrémente location_of_the_table et retourne RETURN_SUCCESS ou erreur
	en cas de problème.
*/
int	process_redirect_out(t_token **tokens, t_command *curr, t_command *head,
	t_utils *utils)
{
	int		i;
	size_t	new_size;
	t_arg	**new_redirect_out;

	i = 0;
	(*tokens) = (*tokens)->next;
	if (!(*tokens) || !is_word_like(*tokens))
		return (handle_token_error(tokens, utils, head));
	while (curr->redirect_out && curr->redirect_out[i])
		i++;
	new_size = sizeof(t_arg *) * (i + 2);
	new_redirect_out = realloc(curr->redirect_out, new_size);
	if (!new_redirect_out)
		return (process_free_exit(head));
	curr->redirect_out = new_redirect_out;
	curr->redirect_out[i] = malloc(sizeof(t_arg));
	if (!curr->redirect_out[i])
		return (process_free_exit(head));
	curr->redirect_out[i + 1] = NULL;
	curr->redirect_out[i]->arg = ft_strdup((*tokens)->value);
	curr->redirect_out[i]->heredoc = false;
	curr->redirect_out[i]->append_redirect = false;
	if (!curr->redirect_out[i]->arg)
		return (process_free_exit(head));
	process_quotes(*tokens, curr->redirect_out[i]);
	return (RETURN_SUCCESS);
}

/*
Fonction qui :
- avance au token suivant après une redirection append (>>) ;
- vérifie que le token suivant est valide, sinon affiche une erreur ;
- alloue append_redirections si besoin, copie l’argument et traite
	les quotes ;
- ajoute l’argument à cmd_parts, marque le dernier argument comme final ;
- avance le token et retourne RETURN_SUCCESS ou une erreur si un problème
	survient.
*/
int	process_append_redirect(t_token **tokens, t_command *curr, t_command *head,
	t_utils *utils)
{
	int		i;
	size_t	new_size;
	t_arg	**new_redirect_out;

	(*tokens) = (*tokens)->next;
	if (!(*tokens) || !is_word_like(*tokens))
		return (handle_token_error(tokens, utils, head));
	i = 0;
	while (curr->redirect_out && curr->redirect_out[i])
		i++;
	new_size = sizeof(t_arg *) * (i + 2);
	new_redirect_out = realloc(curr->redirect_out, new_size);
	if (!new_redirect_out)
		return (process_free_exit(head));
	curr->redirect_out = new_redirect_out;
	curr->redirect_out[i] = malloc(sizeof(t_arg));
	if (!curr->redirect_out[i])
		return (process_free_exit(head));
	curr->redirect_out[i + 1] = NULL;
	curr->redirect_out[i]->arg = ft_strdup((*tokens)->value);
	if (!curr->redirect_out[i]->arg)
		return (process_free_exit(head));
	curr->redirect_out[i]->heredoc = false;
	curr->redirect_out[i]->append_redirect = true;
	process_quotes(*tokens, curr->redirect_out[i]);
	return (RETURN_SUCCESS);
}

/*{a fix} : se renseigner sur la gestion des redirections append (>>) et
	envisager 
de stocker les append_redirections dans un tableau, comme redirect_in et
	redirect_out, 
pour uniformiser le traitement et permettre la gestion de plusieurs append.*/
