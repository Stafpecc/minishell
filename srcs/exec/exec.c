/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:00:29 by ldevoude          #+#    #+#             */
/*   Updated: 2025/05/03 16:40:29 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

//TODO determine which type and parameters I need here lets imagine I'll receive

// void determine_built_in(void)
// {
//     //TODO strncmp to check what is the built-in cmd that is sent then launch the right one
// }

//That would be the main exec function for now it just call init_simple_cmd
//to do the job when there is only one cmd as an input
void exec(char *input, char **env)
{
        //TODO check if we are dealing with a built-in if yes go to a
        // determine_built-in else go next
        //WHY? because if we consider the following that the built-in 
        //doesnt require a chuld because no execve THO we should consider
        //also if we receive 
        //Pipelines redirection and wathever that will make a child needed.
        //TODO talk to eachothers about that specific case!!!
    init_simple_cmd(input, env);
    printf("dead child success\n");
    return;
}