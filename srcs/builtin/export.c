

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

//need tarini for that case!!!

static int error_finder(t_command_exec *node)
{
    //TODO? if just export do like bash or follow manual? aka ask for arguments
    if (!node->cmd_parts || !node->cmd_parts[0] || !node->cmd_parts[1])
    {
        if(!node->cmd_parts[1])
        {
            ft_printfd("minishell: export: require an argument: \n");
            return(RETURN_FAILURE);
        }
    }
    if (ft_strcmp (&node->cmd_parts[1][0], "-"))
    {
        ft_printfd("minishell: export: '%s': export does not handle flags\n",node->cmd_parts[1]);
    }
    if (ft_strcmp (&node->cmd_parts[1][0], "_") && !ft_isalpha(node->cmd_parts[1][0]))
    { 
        ft_printfd("minishell: export: '%s': not a valid identifier\n", node->cmd_parts[1]);
        return(RETURN_FAILURE);
    }
    else
    {
        ft_printfd("C VALIDE\n"); //TODL
        return(RETURN_SUCCESS);
    }
}
// static int equal_sign_case(t_command_exec *node, t_utils *utils)
// {  
    
// }

int export_builtin(t_command_exec *node, t_utils *utils)
{
    utils->env = NULL;
    if (error_finder(node))
        return (RETURN_FAILURE);
    // if (ft_strcmp (&node->cmd_parts[2][0], "="))
    //     equal_sign_case(node, utils);
    //else case that doesnt hold an = sign
    return(RETURN_SUCCESS);
}