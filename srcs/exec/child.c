
// typedef struct s_command {
//     char **cmd;
//     char *redirect_in;
//     char *redirect_out;
//     struct s_command *next;
// } t_command;

#include "../include/exec.h"

//TODO check my old pipex to see how to make it work in that case

void child_redirect(t_command *node, char **env)
{
    char    *path;
    if (built_in_checker(node->cmd[0]));
        //TODO redirect to the right built_in followed by the right way to execute the child
    if(!ft_strchr(node->cmd[0], '/'))
    {
        path = path_finder(env, node->cmd[0], NULL);
        if (path == NULL)
            child_error(-42, NULL, 1, node->cmd[0]);
        execve(path, node->cmd, env);
        free(path);
        exit(EXIT_FAILURE);
    }
    else
        //child_pathed_exec
}