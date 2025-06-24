
// #include "../include/exec.h"
#include "../../include/exec.h"

static int exit_child_builtin(t_command_exec *node, t_utils *utils)
{
    int i;
    i = 0;
    while(node->cmd_parts[i])
    {
        free(node->cmd_parts[i]);
        node->cmd_parts[i] = NULL;
    }
    exit(utils->last_return);
}

static int built_in_child (t_command_exec *node, t_utils *utils)
{
	if (!ft_strcmp(node->cmd_parts[0], "cd"))
		utils->last_return = (cd_builtin(node, utils, 0, 0));
	else if (!ft_strcmp(node->cmd_parts[0], "echo"))
		utils->last_return = (echo_builtin(node,TRUE, 0));
	else if (!ft_strcmp(node->cmd_parts[0], "pwd"))
		utils->last_return = (pwd_builtin(node, utils, 0, 4));
	else if (!ft_strcmp(node->cmd_parts[0], "export"))
		utils->last_return = (export_builtin(node, utils, 1));
	else if (!ft_strcmp(node->cmd_parts[0], "unset"))
		utils->last_return = (unset_builtin(node, utils));
	else if (!ft_strcmp(node->cmd_parts[0], "env"))
		utils->last_return = (env_builtin(node, utils, 0));
	else if (!ft_strcmp(node->cmd_parts[0], "exit"))
		utils->last_return = (exit_builtin(node, utils));
	return(exit_child_builtin(node, utils));
}

void child_redirect(t_command_exec *node, t_utils *utils)
{

    char    *path;
    if (built_in_checker(node->cmd_parts[0]))
        built_in_child(node, utils);//ft_printfd("test");//TODO redirect to the right built_in followed by the right way to execute the child
    if(!ft_strchr(node->cmd_parts[0], '/'))
    {
        //ft_printfd("cmd_parts[0] = %s\n", node->cmd_parts[0]); //TORM
        //TODO CHILD DED IN PATHFINDER FIND THE REASON
        path = path_finder(utils->env, node->cmd_parts[0], NULL); //TODO replace cmd_parts[0] into the new cmd arg that Tarini will provide
        if (path == NULL)
        {
            //ft_printfd("TEST\n"); //ICI soucis avec Hola
            child_error(-42, NULL, 1, node->cmd_parts[0]);
        }
        execve(path, node->cmd_parts, utils->env); //Theo gonna give the right stuff later on
        perror("ERREUR:\n");
        free(path);
        exit(EXIT_FAILURE);//TODO check if I should put perror here
    }
    else
    {
        execve(node->cmd_parts[0], node->cmd_parts, utils->env);
        perror("execve");
        exit(EXIT_FAILURE);
    }
 
}