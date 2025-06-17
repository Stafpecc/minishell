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
    int k;
    i = 1;
	int j;
    int l;
    j = 0;
    k = 0;
    l = 0;

    char **tmp_cp_env;

    if(!node->cmd_parts[1])
        return(RETURN_SUCCESS);
    tmp_cp_env = utils->env;
    while(tmp_cp_env[j])
    {
        while(node->cmd_parts[i])
        {
            ft_printfd("TEST AVANT SEGFAULT\n");
            if(!ft_strncmp(node->cmd_parts[i], tmp_cp_env[j], ft_strlen(node->cmd_parts[i]))) //attention cas test!=tests
            {
                condense_env(utils);//secure
                l++;
                break;
            }
            i++;
        }
        //free(utils->env[k]);
        ///utils->env[k] = NULL;
        ft_printfd("k= %d \n l= %d \n", k, l);
        //ft_printfd("env[k] = %s\n tmp_cp[l] = %s\n", utils->env[k], tmp_cp_env[l]);
        utils->env[k] = tmp_cp_env[l];
        k++;
        l++;
        j++;
        i = 1;
    }
    while(tmp_cp_env[i+1])
    {
        ft_printfd("%s\n",tmp_cp_env[i]);
        i++;
    }
    return(0);

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
