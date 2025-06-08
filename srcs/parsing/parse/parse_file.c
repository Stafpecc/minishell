/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:31:36 by tarini            #+#    #+#             */
/*   Updated: 2025/06/08 04:51:33 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

#include <errno.h>

/*
	Vérifie l'existence et les droits d'accès à un fichier 
	selon le mode spécifié.
	Affiche un message d'erreur en cas d'échec et met à jour le code de retour.
	Retourne RETURN_SUCCESS si tout est OK, sinon RETURN_FAILURE.
*/
int	check_file(const char *path, t_utils *utils, t_file_mode mode)
{
	(void) mode;
	if (utils) //TORM
		ft_printfd("proutdansparse_file.c\n"); //TORM
	if (!path)
		return (RETURN_FAILURE);
	if (access(path, F_OK) != 0)
	{
		if (errno == ENOENT)
			ft_printfd("minishell: %s: No such file or directory\n", path);
		else
		{
			ft_printfd("minishell: ");
			perror(path);
		}
		utils->last_return = CMD_INVALID_ARGUMENT;
		return (RETURN_FAILURE);
	}
	return (RETURN_SUCCESS);
}

// int	check_file(const char *path, t_utils *utils, t_file_mode mode)
// {
// 	//int	access_mode;
// 	(void) mode;
// 	if (utils) //TORM
// 		ft_printfd("proutdansparse_file.c\n"); //TORM
// 	if (!path)
// 		return (RETURN_FAILURE);
// 	// if (mode == FILE_READ)
// 	// 	access_mode = R_OK;
// 	// else if (mode == FILE_WRITE)
// 	// 	access_mode = W_OK;
// 	// else if (mode == FILE_EXEC)
// 	// 	access_mode = X_OK;
// 	// else
// 	// 	return (RETURN_FAILURE);
// 	if (access(path, F_OK) != 0)
// 	{
// 		if (errno == ENOENT)
// 			ft_printfd("minishell: %s: No such file or directory\n", path);
// 		else
// 		{
// 			ft_printfd("minishell: ");
// 			perror(path);
// 		}
// 		utils->last_return = CMD_INVALID_ARGUMENT;
// 		return (RETURN_FAILURE);
// 	}
// 	// if (access(path, access_mode) != 0)
// 	// {
// 	// 	ft_printfd("minishell: %s: Permission denied\n", path);
// 	// 	utils->last_return = CMD_INVALID_ARGUMENT;
// 	// 	return (RETURN_FAILURE);
// 	// }
// 	return (RETURN_SUCCESS);
// }
