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

unsigned int exit_builtin(t_command *node, char **env, int i, int j)
{
    unsigned int return_value;

    //Exit = dernier retour TODO en parler a theo
    
    return_value = 0;
    if(!node->cmd_parts || !node->cmd_parts[0]) //may be useless
    {
        perror("ERROR\n");
        exit(EXIT_FAILURE);
    }
    if(!node->cmd_parts[1])
        exit(node->$?);
    if (node->cmd_parts[1] == '0')
        exit(0);
    return_value = ft_atoi(node->cmd_parts[1]); //TODO ask theo about that way 
    if (return_value == 0)
        exit(2);
    else
        exit(return_value);

}
