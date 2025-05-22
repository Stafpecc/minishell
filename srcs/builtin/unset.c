#include "minishell.h"

static int env_len(char **env)
{
    int i = 0;
    while (env[i])
        i++;
    return i;
}

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


char **unset_builtin(char **envp, const char *name)
{
    int i;
	int j;
	int count;
    char **new_env;

    count = env_len(envp);
    new_env = malloc(sizeof(char *) * (count + 1));
    if (!new_env)
        return (NULL);
    i = 0;
    j = 0;
    while (envp[i])
    {
        if (var_name_cmp(envp[i], name) != 0)
        {
            new_env[j++] = ft_strdup(envp[i]);
        }
        i++;
    }
    new_env[j] = NULL;
    return (new_env);
}
