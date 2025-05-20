#include "../include/builtin.h"
// typedef struct s_command_exec {
//     char        **env;
//     char        **cmd_parts;
//     char        *redirect_in;
//     char        *redirect_out;
//     char        *append_redirections;
//     char        *heredoc;
//     struct s_command_exec *next;
// } t_command_exec;

//TODO check for the return values

int env_builtin(t_command *node, char **env, int i, int j)
{
    i = 0;

    if (!node->cmd_parts || !node ->cmd_parts[0])
    {
        perror("Error no cmd\n"); //may be completly useless
        return (EXIT_FAILURE);
    }
    if (node->cmd_parts[1])
    {
        perror("No arguments or options required for env\n");
        return (EXIT_FAILURE);
    }
    while(env[i])
    {
        ft_printf("%s\n",env[i]);
        i++;
    }
    return (EXIT_SUCCESS);
}