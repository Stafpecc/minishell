#include "minishell.h"
#include "builtin.h"

static char **cpy_env(t_utils *utils, char **cp_env, int index_overwrite)
{
    cp_env = malloc((utils->size_env + 1) * sizeof(char *));
    if(!cp_env)
        return(NULL);
    while(utils->env[index_overwrite])
    {
        cp_env[index_overwrite] = utils->env[index_overwrite];
        index_overwrite++;
    }
    cp_env[index_overwrite] = NULL;
    return(cp_env);
}

static int check_if_match(t_command_exec *node,t_utils *utils, char **tmp_cp_env, size_t index_cp_env)
{
    int index_args_checker = 1;

    while(node->cmd_parts[index_args_checker])
    {
        if(!ft_strncmp(tmp_cp_env[index_cp_env],node->cmd_parts[index_args_checker], ft_strlen(node->cmd_parts[index_args_checker]))
         && tmp_cp_env[index_cp_env][ft_strlen(node->cmd_parts[index_args_checker])] == '=')
        {
            if (condense_env(utils))
                return(MALLOC_ERROR);
            return(TRUE);
        }
        index_args_checker++;
    }
    return(FALSE);
}
static void write_case(t_utils *utils, char **tmp_cp_env, size_t *index_overwrite, size_t index_cp_env)
{
    utils->env[*index_overwrite] = tmp_cp_env[index_cp_env];
    *index_overwrite += 1;
}

static int free_exit(char **tmp_cp_env, int return_value)
{
    if(tmp_cp_env)
        free(tmp_cp_env);
    return(return_value);
}

int unset_builtin(t_command_exec *node, t_utils *utils)
{
    char **tmp_cp_env;
    int match;
    size_t index_cp_env;
    size_t index_overwrite;

    index_overwrite = 0;
    index_cp_env = 0;
    match = FALSE;
    tmp_cp_env = NULL;
    if(!node->cmd_parts[1])
        return(RETURN_SUCCESS);
    tmp_cp_env = cpy_env(utils, tmp_cp_env, 0);
    if(!tmp_cp_env)
        return(MALLOC_ERROR);
    while(tmp_cp_env[index_cp_env])
    {
        match = check_if_match(node, utils, tmp_cp_env, index_cp_env);
        if(match == MALLOC_ERROR)
            return(free_exit(tmp_cp_env, MALLOC_ERROR));
        if(match == FALSE)
            write_case(utils, tmp_cp_env, &index_overwrite, index_cp_env);
        index_cp_env++;
    }
    return(free_exit(tmp_cp_env, RETURN_SUCCESS)); 
}
