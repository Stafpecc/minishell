#include "builtin.h"
#include "minishell.h"
// typedef struct s_command_exec {
//     char        **env;
//     char        **cmd_parts;
//     char        *redirect_in;
//     char        *redirect_out;
//     char        *append_redirections;
//     char        *heredoc;
//     struct s_command_exec *next;
// } t_command_exec;

unsigned int exit_builtin(t_command_exec *node, t_utils *utils)
{
    unsigned int return_value;

    return_value = 0;

    //check si argument is nbr
    if(!node->cmd_parts || !node->cmd_parts[0]) //may be useless
    {
        perror("ERROR\n");
        exit(EXIT_FAILURE);
    }
    if(!node->cmd_parts[1])
        exit(utils->last_return);
    if (node->cmd_parts[1] == 0)
        exit(0);
    return_value = ft_atoi(node->cmd_parts[1]); //TODO ask theo about that way 
    if (return_value == 0)
        exit(2);
    else
        exit(return_value);

}
