/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:05:46 by ldevoude          #+#    #+#             */
/*   Updated: 2025/06/19 16:27:58 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtin.h"

int return_errors(int return_value, int message)
{
    if(message == ERR_CD_CHDIR)
    {
        ft_printfd("minishell: cd: %s: ", node->cmd_parts[1]);
		perror("");
    }
    else if(message == ERR_CD_GETCWD)
        perror("getcwd() error");
    else if(message == ERR_CD_MALLOC)
        perror("Malloc error");
    return(return_value);
}