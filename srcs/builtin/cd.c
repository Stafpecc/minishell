/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 13:52:47 by ldevoude          #+#    #+#             */
/*   Updated: 2025/05/22 14:24:43 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtin.h"

//need chdir  opendir  readdir closedir
//TODO OPTION : use env to handle that case, not asked in subject BUT can still do it quite easily
//same for OLD PWD (env | grep OLDPWD)
int cd_builtin(t_command_exec *node, char **env)
{

    if(!node->cmd_parts || !node->cmd_parts[0] || node->cmd_parts[2]) //TODO update when I'll get Tarini updated struct
        return(EXIT_FAILURE);
    if(!node->cmd_parts[1])
        return(no_args_case(env));
    if (chdir(node->cmd_parts[1]))
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