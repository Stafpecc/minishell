/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:34:25 by tarini            #+#    #+#             */
/*   Updated: 2025/06/26 17:43:57 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "exec.h"
#include "../../../libft/includes/libft.h"

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
int	process_redirect_in(t_token **tokens, t_command *curr,
	t_command *head, t_utils *utils)
{
	t_context			ctx;
	t_redirect_flags	flags;

	ctx.head = head;
	ctx.utils = utils;
	flags.is_heredoc = false;
	flags.is_append = false;
	return (add_redirect(tokens, &curr->redirect_in, &ctx, flags));
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
int	process_redirect_out(t_token **tokens, t_command *curr,
	t_command *head, t_utils *utils)
{
	t_context			ctx;
	t_redirect_flags	flags;

	ctx.head = head;
	ctx.utils = utils;
	flags.is_heredoc = false;
	flags.is_append = false;
	return (add_redirect(tokens, &curr->redirect_out, &ctx, flags));
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
int	process_append_redirect(t_token **tokens, t_command *curr,
	t_command *head, t_utils *utils)
{
	t_context			ctx;
	t_redirect_flags	flags;

	ctx.head = head;
	ctx.utils = utils;
	flags.is_heredoc = false;
	flags.is_append = true;
	return (add_redirect(tokens, &curr->redirect_out, &ctx, flags));
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
int	process_heredoc(t_token **tokens, t_command *curr,
	t_command *head, t_utils *utils)
{
	t_context			ctx;
	t_redirect_flags	flags;
	int					i;
	int					fd;

	ctx.head = head;
	ctx.utils = utils;
	flags.is_heredoc = true;
	flags.is_append = false;
	i = 0;
	while (curr->redirect_in && curr->redirect_in[i])
		i++;
	if (add_redirect(tokens, &curr->redirect_in, &ctx, flags) != RETURN_SUCCESS)
		return (RETURN_FAILURE);
	process_quotes(*tokens, curr->redirect_in[i]);
	fd = here_doc(curr->redirect_in[i]->arg);
	if (fd < 0)
	{
		utils->last_return = fd * -1;
		return (RETURN_FAILURE);
	}
	curr->redirect_in[i]->fd = fd;
	return (RETURN_SUCCESS);
}
