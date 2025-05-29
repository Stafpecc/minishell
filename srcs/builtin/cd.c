/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 13:52:47 by ldevoude          #+#    #+#             */
/*   Updated: 2025/05/29 17:16:41 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtin.h"
#include <limits.h> //TOMV

#define OLD 0
#define NEW 1

// static char* cd_builtin_strdup(t_utils *utils, int pwd_emplacement, int pwd_old_emplacement, int old_or_new)
// {
//     char *tmp;
//     char *tmp_pwd;
//     int i;
//     int j;

//     pwd_old_emplacement = 0; //TORM
//     old_or_new = 0;
//     j = 0;
    
//     i = 3;
//     tmp = malloc(sizeof(char) * (ft_strlen(utils->env[pwd_emplacement] + 4))); //SECURE
//     tmp_pwd = malloc(sizeof(char) * (ft_strlen(utils->env[pwd_emplacement] - 4))); //secure
//     while(utils->env[pwd_emplacement][i])
//     {
//         tmp_pwd[j] = utils->env[pwd_emplacement][i];
//         i++;
//         j++;
//     }
//     tmp =  ft_strjoin("OLDPWD", tmp_pwd); //SECURE
//     return(tmp);
// }

// static char* cd_builtin_update_oldpwd(t_utils *utils, int pwd_emplacement, int pwd_old_emplacement)
// {

//     char *tmp;
//     int i;
    
//     i = 0;

//     free(utils->env[pwd_old_emplacement]);
//     utils->env[pwd_old_emplacement] = NULL;
//     utils->env[pwd_old_emplacement] = cd_builtin_strdup(utils, pwd_emplacement, pwd_old_emplacement, OLD); //TOSECURE
//     ft_printfd("tmp = %s\n",utils->env[pwd_old_emplacement]);
//     tmp = getcwd(NULL, 0);
//     if(tmp)
//     {
//         printf("Current working directory: %s\n", tmp);
//     } 
//     else 
//     {
//         perror("getcwd() error");
//         return NULL;
//     }
//     //tmp possede pwd
    
//     exit(0);
    
    
// }

// static int cd_builtin_update_pwd(t_utils *utils, int pwd_emplacement)
// {
//     //find the env space to modify
//     int i;
    
//     pwd_emplacement = 0; //TORM
//     i = 0;
//     while(utils->env[i])
//     {
//         if (!ft_strncmp(utils->env[i], "PWD=", 4))
//         {
            
//         }
//         i++;
//     }
//     return (1); //torm
    
// }

static int cd_builtin_pwd_finder(t_utils *utils, int old_or_new)
{
    //ft_printfd("TEST %s\n",utils->env[0]);
    ft_printfd("TEST \n");
    int result;

    result = 0;
    
    if (old_or_new == NEW)
    {
        while (utils->env[result])
        {
            
            if(!ft_strncmp(utils->env[result], "PWD=", 4))
                return(result);
            result++;
        }
    }
    else if (old_or_new == OLD)
    {
        while (utils->env[result])
        {
            if(!ft_strncmp(utils->env[result], "OLDPWD=", 7))
                return(result);
            result++;
        }
    }
    return(-42);
}


int cd_builtin(t_command_exec *node, t_utils *utils, int pwd_emplacement, int pwd_old_emplacement)
{
    pwd_emplacement = cd_builtin_pwd_finder(utils, NEW);
    pwd_old_emplacement = cd_builtin_pwd_finder(utils, OLD);

    utils->env[pwd_old_emplacement] = getcwd(NULL, 0);
    if(utils->env[pwd_old_emplacement])
    {
        printf("OLDPDW: %s\n", utils->env[pwd_old_emplacement]);
    } 
    else 
    {
        perror("getcwd() error");
        return 0;
    }

    if(!node->cmd_parts || !node->cmd_parts[0] || !node->cmd_parts[1]) //TODO update when I'll get Tarini updated struct
    {
        ft_printfd("minishell: cd: works with only a relative or absolute path\n");
        return(EXIT_FAILURE);
    }
    if(node->cmd_parts[2])
    {
        ft_printfd("minishell: cd: too many arguments\n");
        return(EXIT_FAILURE);
    }
    if (chdir(node->cmd_parts[1]))
    {
        
        ft_printfd("minishell: cd: %s: ", node->cmd_parts[1]);
        perror("");
        return(EXIT_FAILURE);
    }
    
    utils->env[pwd_emplacement] = getcwd(NULL, 0);
    if(utils->env[pwd_emplacement])
    {
        printf("Current working directory: %s\n", utils->env[pwd_emplacement]);
    } 
    else 
    {
        perror("getcwd() error");
        return 0;
    }
    
    exit(0);
    // cd_builtin_update_oldpwd(utils, pwd_emplacement, pwd_old_emplacement);
    // cd_builtin_update_pwd(utils, 0);
    return (0);
}

    // update PWD
    //???update OLDPWD