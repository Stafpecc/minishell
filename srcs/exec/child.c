
// #include "../include/exec.h"
#include "../../include/exec.h"

void child_redirect(t_command_exec *node, t_utils *utils)
{

    char    *path;
    if (built_in_checker(node->cmd_parts[0]))
        ft_printfd("test");//TODO redirect to the right built_in followed by the right way to execute the child
    if(!ft_strchr(node->cmd_parts[0], '/'))
    {
        //TODO CHILD DED IN PATHFINDER FIND THE REASON
        path = path_finder(utils->env, node->cmd_parts[0], NULL); //TODO replace cmd_parts[0] into the new cmd arg that Tarini will provide
        if (path == NULL)
        {
            child_error(-42, NULL, 1, node->cmd_parts[0]);
        }

        //ft_printf("path = %s\n node->cmd_parts: %s\n, ", path, node->cmd_parts[0]);
        execve(path, node->cmd_parts, utils->env); //Theo gonna give the right stuff later on
        free(path);
        exit(EXIT_FAILURE);//TODO check if I should put perror here
    }
    else
    {
        //printf("test");
    }
 
}