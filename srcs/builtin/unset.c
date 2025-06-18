#include "minishell.h"
#include "builtin.h"

static char **cpy_env(t_utils *utils, char **cp_env, int index_overwrite)
{
    cp_env = malloc((utils->size_env + 1) * sizeof(char *)); //protect
    while(utils->env[index_overwrite])
    {
        cp_env[index_overwrite] = utils->env[index_overwrite];
        index_overwrite++;
    }
    cp_env[index_overwrite] = NULL;
    return(cp_env);
}

static bool check_if_pass_or_write(t_command_exec *node,t_utils *utils, char **tmp_cp_env, size_t index_cp_env)
{
    int index_WIP = 1;

    while(node->cmd_parts[index_WIP])
    {
        if(!ft_strncmp(node->cmd_parts[index_WIP], tmp_cp_env[index_cp_env], ft_strlen(node->cmd_parts[index_WIP])))
        {
            condense_env(utils); //secure
            return(TRUE);
        }
        index_WIP++;
    }
    return(FALSE);
}
//TODO A LA FIN FREE TMP_CP_ENV
int unset_builtin(t_command_exec *node, t_utils *utils)
{
    char **tmp_cp_env;
    bool pass_or_write;
    size_t index_cp_env;
    size_t index_overwrite;

    index_overwrite = 0;
    index_cp_env = 0;
    pass_or_write = FALSE;
    tmp_cp_env = NULL;
    if(!node->cmd_parts[1])
        return(RETURN_SUCCESS);
    tmp_cp_env = cpy_env(utils, tmp_cp_env, 0); //TODO PROTECT //nous avons bien copié l'env yeepee
    while(tmp_cp_env[index_cp_env])
    {
        ft_printfd("TEST\n");
        pass_or_write = check_if_pass_or_write(node, utils, tmp_cp_env, index_cp_env);
        if(pass_or_write == FALSE)
        {
            ft_printfd("TEST\n");
            utils->env[index_overwrite] = tmp_cp_env[index_cp_env];
            //ft_printfd("utils->env[%s]\n", index_overwrite, utils->env[index_overwrite]);
            ft_printfd("tmp_cp_prout[%d] = %s\n", index_cp_env, tmp_cp_env[index_cp_env]);
            index_overwrite++;
        }
        index_cp_env++;
    }
    return(0);    
}
