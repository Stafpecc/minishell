/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:17:42 by stafpec           #+#    #+#             */
/*   Updated: 2025/06/04 12:32:54 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*
 Fonction qui :
 - prend en entrée un tableau de chaînes représentant les redirections ;
 - compte combien d'éléments il y a dedans (jusqu'à NULL) ;
 - retourne ce nombre.
*/

/*
 Fonction qui :
 - prend en argument une structure t_command représentant une commande utilisateur ;
 - regarde s’il y a des redirections qui se superpose :
     - un fichier redirigé avec "<" et un heredoc en même temps ;
     - ou encore une sortie ">" suivie d’un ">>".
 - retourne true si conflit détecté, sinon false.
*/
bool has_conflicting_redirections(t_command *cmd)
{
	return ((cmd->redirect_in && cmd->heredoc) ||
			(cmd->redirect_out && cmd->append_redirections));
}

/*
 Fonction qui :
 - prend une commande (t_command) et une structure utilitaire (t_utils), e.g. pour le code retour ;
 - vérifie s’il y a des redirections du même type juste après une autre (deux ">" d'affilée) ;
 - si c’est le cas, on affiche une erreur et on retourne RETURN_FAILURE ;
 - sinon, tout va bien, on retourne RETURN_SUCCESS.
*/
int redirect_parsing(t_command *curr, t_utils *utils)
{
	if (curr->redirect_out != NULL &&
		curr->next && curr->next->redirect_out != NULL)
		return (return_failure(">", utils));
	if (curr->redirect_in != NULL &&
		curr->next && curr->next->redirect_in != NULL)
		return (return_failure("<", utils));
	if (curr->append_redirections != NULL &&
		curr->next && curr->next->append_redirections != NULL)
		return (return_failure(">>", utils));
	if (curr->heredoc != NULL &&
		curr->next && curr->next->heredoc != NULL)
		return (return_failure("<<", utils));
	return (RETURN_SUCCESS);
}
