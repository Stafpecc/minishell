/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:17:42 by stafpec           #+#    #+#             */
/*   Updated: 2025/06/06 16:16:35 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
int redirect_parsing(t_command *cmd, t_utils *utils)
{
	int out_count = 0;
	int in_count = 0;
	int append_count = 0;
	int heredoc_count = 0;

	if (cmd->redirect_out)
		out_count++;
	if (cmd->append_redirections)
		append_count++;
	if (cmd->redirect_in)
		in_count++;
	if (cmd->heredoc)
		heredoc_count++;

	if (out_count > 1)
		return (return_failure(">", utils));
	if (append_count > 1)
		return (return_failure(">>", utils));
	if (in_count > 1)
		return (return_failure("<", utils));
	if (heredoc_count > 1)
		return (return_failure("<<", utils));
	return (RETURN_SUCCESS);
}

