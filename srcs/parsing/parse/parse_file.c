/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:31:36 by tarini            #+#    #+#             */
/*   Updated: 2025/06/04 12:39:15 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <errno.h>

/*
Fonction qui :
- vérifie si un fichier donné existe et si le shell a le droit de le lire ;
- affiche un message d’erreur adapté si le fichier est introuvable ou inaccessible ;
- met à jour le code de retour dans utils et retourne RETURN_FAILURE en cas de problème, 
	sinon RETURN_SUCCESS.
*/
int check_file(const char *path, t_utils *utils)
{
	if (access(path, F_OK) != 0)
	{
		if (errno == ENOENT)
		{
			ft_printfd("minishell: %s: No such file or directory\n", path);
			utils->last_return = CMD_INVALID_ARGUMENT;
			return (RETURN_FAILURE);
		}
		else
		{
			ft_printfd("minishell: ");
			perror(path);
		}
		utils->last_return = CMD_INVALID_ARGUMENT;
		return (RETURN_FAILURE);
	}
	if (access(path, R_OK) != 0)
	{
		ft_printfd("minishell: %s: Permission denied\n", path);
		utils->last_return = CMD_INVALID_ARGUMENT;
		return (RETURN_FAILURE);
	}
	return (RETURN_SUCCESS);
}

/*{a fix} : modifier la fonction pour qu’elle vérifie différents types de droits (lecture, écriture, exécution)
en fonction du type de redirection et de la demande.*/