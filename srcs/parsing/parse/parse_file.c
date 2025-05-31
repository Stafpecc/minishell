/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:31:36 by tarini            #+#    #+#             */
/*   Updated: 2025/05/31 17:34:44 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <errno.h>

int check_file(const char *path, t_utils *utils)
{
    if (access(path, F_OK) != 0)
    {
        if (errno == ENOENT)
        {
            ft_printfd("minishell: %s: No such file or directory\n", path);
            utils->last_return = CMD_INVALID_ARGUMENT;
            return RETURN_FAILURE;
        }
        else
        {
            ft_printfd("minishell: %s: %s\n", path, strerror(errno));
            utils->last_return = CMD_INVALID_ARGUMENT;
            return RETURN_FAILURE;
        }
    }
    return RETURN_SUCCESS;
}