#include "minishell.h"

int var_name_cmp(const char *env_var, const char *name)
{
    while (*env_var && *name && *env_var != '=')
    {
        if (*env_var != *name)
            return (*env_var - *name);
        env_var++;
        name++;
    }
    if (*name == '\0' && (*env_var == '=' || *env_var == '\0'))
        return (RETURN_SUCCESS);
    else
        return (RETURN_FAILURE);
}


int unset_builtin(t_command_exec *node, t_utils *utils)
{
    ft_printfd("%s\n",node->cmd_parts[0]);
    int i;
    i = 1;
	int j;
    j = 0;
    char **tmp_cp_env;

    if(!node->cmd_parts[1])
        return(RETURN_SUCCESS);
    tmp_cp_env = utils->env;
    while(tmp_cp_env[j])
    {
        while(node->cmd_parts[i])
        {
            if(ft_strncmp(node->cmd_parts[i], tmp_cp_env[j], ft_strlen(node->cmd_parts[i]))) //attention cas test!=tests
            {
                condense_env(utils);//secure

            }
            i++;
        }
        utils->env[i] = tmp_cp_env[j];
        i++;
        j++;
    }
    while(tmp_cp_env[i+1])
    {
        ft_printfd("%s\n",tmp_cp_env[i]);
        i++;
    }
    exit(0);
    // if(!node->cmd_parts[1])
    //     return(RETURN_SUCCESS);
    
    // if(!condense_env(utils))
    //     return(MALLOC_ERROR);
    // new_env = malloc(sizeof(char *) * (utils->size_env + 1));
    // if (!new_env)
    //     return (NULL);
    // i = 0;
    // j = 0;
    // while(node->cmd_parts[i])
    // {
    //     while (utils->env[i])
    //     {
    //         if (var_name_cmp(envp[i], name) != 0)
    //         {
    //             new_env[j++] = ft_strdup(envp[i]);
    //         }
    //         i++;
    //     }
    // }
    // new_env[j] = NULL;
    // return (new_env);
}

// char **unset_builtin(t_command_exec *node, t_utils *utils)
// {
//     int i;
// 	int j;
// 	int count;
//     char **new_env;
//     char **tmp_cp_env;

//     tmp_cp_env = utils->env;

//     if(!node->cmd_parts[1])
//         return(RETURN_SUCCESS);
    
//     if(!condense_env(utils))
//         return(MALLOC_ERROR);
//     new_env = malloc(sizeof(char *) * (utils->size_env + 1));
//     if (!new_env)
//         return (NULL);
//     i = 0;
//     j = 0;
//     while(node->cmd_parts[i])
//     {
//         while (utils->env[i])
//         {
//             if (var_name_cmp(envp[i], name) != 0)
//             {
//                 new_env[j++] = ft_strdup(envp[i]);
//             }
//             i++;
//         }
//     }
//     new_env[j] = NULL;
//     return (new_env);
// }
