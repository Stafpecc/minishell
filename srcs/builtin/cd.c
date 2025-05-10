/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 13:52:47 by ldevoude          #+#    #+#             */
/*   Updated: 2025/05/10 14:54:42 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtin.h"

//need chdir  opendir  readdir closedir

int cd_builtin(t_command *node)
{
    //check if there is an arg !!!DONE!!! 
    //test if the path is valid
    //save old repertory
    // do the chdir if it fail use errno and get out
    // update PWD
    //???update OLDPWD
    if(!node->cmd || !node->cmd[0] || !node->cmd[1]|| node->cmd[2])
        return(EXIT_FAILURE);
    if (chdir( node->cmd[1])
    
}