#include "minishell.h"
#include "builtin.h"

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
    // ft_printfd("%s\n",node->cmd_parts[0]);
    int index_compare;
    int index_overwrite;
    
	int j;
    int l;
    index_compare = 1;
    j = 0;
    index_overwrite = 0;
    l = 0;
    bool test = FALSE;

    char **tmp_cp_env;



    //------
    tmp_cp_env = malloc((utils->size_env + 1) * sizeof(char *));
    while(utils->env[index_overwrite])
    {
        tmp_cp_env[index_overwrite] = utils->env[index_overwrite];
        index_overwrite++;
    }
    //tmp_cp_env = utils->env;
    while(tmp_cp_env[j + 1])
    {
        while(node->cmd_parts[index_compare])
        {
            //ft_printfd("TEST AVANT SEGFAULT\n");
            if(!ft_strncmp(node->cmd_parts[index_compare], tmp_cp_env[j], ft_strlen(node->cmd_parts[index_compare]))) //attention cas test!=tests
            {
                ft_printfd("je passe quand index_overwrite = %d\n",index_overwrite);
                condense_env(utils);//secure
                test = TRUE;
                break;
            }
            index_compare++;
        }
        ft_printfd("tmp_cp_env[l]%s",tmp_cp_env[0]);
        ///utils->env[k] = NULL;
        //ft_printfd("k= %d \n l= %d \n", index_overwrite, l);
        //ft_printfd("env[k] = %s\n tmp_cp[l] = %s\n", utils->env[k], tmp_cp_env[l]);
        if(test == TRUE)
        {
            //free(utils->env[index_overwrite]);
            utils->env[index_overwrite] = tmp_cp_env[l];
            index_overwrite++;
        }
        test = FALSE;
        l++;
        j++;
        index_compare = 1;
    }
    ft_printfd("test\n\n");
    // while(tmp_cp_env[i+1])
    // {
    //     ft_printfd("%s\n",tmp_cp_env[i]);
    //     i++;
    // }
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
