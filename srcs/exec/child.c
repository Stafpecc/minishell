
#include "../include/exec.h"

void child_redirect(t_command *node, char **env)
{
    char    *path;
    
    if (built_in_checker(node->cmd_parts[0]->arg))
        printf("test");//TODO redirect to the right built_in followed by the right way to execute the child
    if(!ft_strchr(node->cmd_parts[0]->arg, '/'))
    {
        path = path_finder(env, node->cmd_parts[0]->arg, NULL); //TODO replace cmd_parts[0] into the new cmd arg that Tarini will provide
        if (path == NULL)
            child_error(-42, NULL, 1, node->cmd_parts[0]->arg);
        execve(path, &path, env); //Theo gonna give the right stuff later on
        free(path);
        exit(EXIT_FAILURE);//TODO check if I should put perror here
    }
    else
    {
        printf("test");
    }
 
}