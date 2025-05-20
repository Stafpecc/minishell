//Write what is at the env PWD=
//todo see if pwd | pwd works.

#include "../include/builtin.h"

int pwd_builtin(t_command *node, char **env, int i, int j)
{
    j = 4;
    if(!node->cmd || !node->cmd[0]) //TODO update when I'll get Tarini updated struct
        return(EXIT_FAILURE);
    if(node->cmd[1])
    {
        perror("pwd: too many arguments");
        return (EXIT_FAILURE);
    }
    if (!ft_strncmp(env[i], "PWD=", 4))
    {
        while(env[i][j])
        {
            ft_printf("%c", env[i][j]);
            j++;
        }
    }
    else
        return(EXIT_FAILURE);
    ft_printf("\n");
    return (EXIT_SUCCESS);
}
