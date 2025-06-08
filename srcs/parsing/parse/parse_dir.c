/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:31:59 by tarini            #+#    #+#             */
/*   Updated: 2025/06/08 04:28:05 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

#include <stdbool.h>
#include <dirent.h>

/*
Fonction qui :
- tente d’ouvrir le chemin donné en tant que répertoire ;
- si l’ouverture réussit, ferme le répertoire et retourne true ;
- sinon retourne false, indiquant que ce n’est pas un répertoire.
*/
bool	is_directory(const char *path)
{
	DIR	*dir;

	dir = opendir(path);
	if (dir)
	{
		closedir(dir);
		return (true);
	}
	return (false);
}
