/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 13:52:47 by ldevoude          #+#    #+#             */
/*   Updated: 2025/05/14 14:12:15 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtin.h"

//need chdir  opendir  readdir closedir
//TODO OPTION : use env to handle that case, not asked in subject BUT can still do it quite easily
//same for OLD PWD (env | grep OLDPWD)
int cd_builtin(t_command *node, char **env)
{

    if(!node->cmd || !node->cmd[0] || node->cmd[2]) //TODO update when I'll get Tarini updated struct
        return(EXIT_FAILURE);
    if(!node->cmd[1])
        return(no_args_case(env)) 
    if (chdir(node->cmd[1]))
    {
        perror("no such file or directory\n");
        return(EXIT_FAILURE);
    }
    return (0);
}

    //check if there is an arg !!!DONE!!! 
    //test if the path is valid
    //save old repertory
    // do the chdir if it fail use errno and get out
    // update PWD
    //???update OLDPWD