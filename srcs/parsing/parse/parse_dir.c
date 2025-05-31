/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:31:59 by tarini            #+#    #+#             */
/*   Updated: 2025/05/31 17:33:52 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

#include "stdbool.h"
#include "dirent.h"

bool is_directory(const char *path)
{
	DIR *dir;
	
	dir = opendir(path);
	if (dir)
	{
		closedir(dir);
		return true;
	}
	return false;
}