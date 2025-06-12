/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:17:42 by stafpec           #+#    #+#             */
/*   Updated: 2025/06/12 14:18:19 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "stdio.h"

/*
 Fonction qui :
 - prend en argument une structure t_command représentant une 
 	commande utilisateur ;
 - regarde s’il y a des redirections qui se superpose :
     - un fichier redirigé avec "<" et un heredoc en même temps ;
     - ou encore une sortie ">" suivie d’un ">>".
 - retourne true si conflit détecté, sinon false.
*/
bool	has_conflicting_redirections(t_command *cmd)
{
	bool	has_in;
	bool	has_heredoc;
	bool	has_out;
	bool	has_append;
	int		i;

	has_in = false;
	has_heredoc = false;
	has_out = false;
	has_append = false;
	i = 0;
	while (cmd->redirect_in && cmd->redirect_in[i])
	{
		if (cmd->redirect_in[i]->heredoc)
			has_heredoc = true;
		else
			has_in = true;
		i++;
	}
	i = 0;
	while (cmd->redirect_out && cmd->redirect_out[i])
	{
		if (cmd->redirect_out[i]->append_redirect)
			has_append = true;
		else
			has_out = true;
		i++;
	}
	if ((has_in && has_heredoc) || (has_out && has_append))
		return (true);
	return (false);
}

/*
Fonction qui :
- prend une commande (t_command) et une structure utilitaire 
	(t_utils), e.g. pour le code retour ;
- vérifie s’il y a des redirections du même type juste après 
	une autre (deux ">" d'affilée) ;
- si c’est le cas, on affiche une erreur et on retourne RETURN_FAILURE ;
- sinon, tout va bien, on retourne RETURN_SUCCESS.
*/
int	redirect_parsing(t_command *curr, t_utils *utils)
{
	if (has_conflicting_redirections(curr))
		return (return_failure("ambiguous redirection", utils));
	return (RETURN_SUCCESS);
}

// TODO FIX USELESS FUNCTION THX BRO